/* Copyright (c) 2019 Griefer@Work                                            *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODGDBSERVER_SERVER_C
#define GUARD_MODGDBSERVER_SERVER_C 1
#define _KOS_SOURCE 1

#include "server.h"

#include <kernel/compiler.h>

#include <kernel/driver-param.h> /* DEFINE_CMDLINE_FLAG_VAR() */
#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/unaligned.h>

#include <kos/kernel/gdb-cpu-state.h>
#include <sys/wait.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__x86_64__) || defined(__i386__)
#include <kernel/gdt.h>
#endif /* __x86_64__ || __i386__ */

#include "gdb-info.h"
#include "gdb.h"
#include "thread-enum.h"

#define STPCAT(buf, str) ((char *)mempcpy(buf, str, COMPILER_STRLEN(str) * sizeof(char)))

#if __SIZEOF_POINTER__ > 4
#define strtou   (uintptr_t)strtou64
#define strtos   (intptr_t)strto64
#else /* __SIZEOF_POINTER__ > 4 */
#define strtou   (uintptr_t)strtou32
#define strtos   (intptr_t)strto32
#endif /* __SIZEOF_POINTER__ <= 4 */

DECL_BEGIN

typedef struct {
	size_t ol_offset; /* Remaining number of bytes to skip */
	size_t ol_size;   /* Remaining number of bytes to print */
	char  *ol_buf;    /* Destination buffer. */
} GDB_OffsetAndLengthPrinterData;

PRIVATE ssize_t
NOTHROW(KCALL GDB_OffsetAndLengthPrinter)(void *arg, char const *__restrict data, size_t datalen) {
	GDB_OffsetAndLengthPrinterData *closure;
	ssize_t result = (ssize_t)datalen;
	closure = (GDB_OffsetAndLengthPrinterData *)arg;
	if (closure->ol_offset != 0) {
		if (closure->ol_offset >= datalen) {
			closure->ol_offset -= datalen;
			goto done;
		}
		data    += closure->ol_offset;
		datalen -= closure->ol_offset;
		closure->ol_offset = 0;
	}
	if (datalen >= closure->ol_size) {
		memcpy(closure->ol_buf, data, closure->ol_size);
		closure->ol_buf += closure->ol_size;
		closure->ol_size = 0;
		return __SSIZE_MIN__; /* Stop printing (we've gotten everything) */
	}
	/* Print everything */
	memcpy(closure->ol_buf, data, datalen);
	closure->ol_size -= datalen;
	closure->ol_buf  += datalen;
done:
	return result;
}


#ifdef HAVE_GDB_DEBUG
#define ERROR(label)       do{ GDB_DEBUG("%s(%d) : Error : " #label "\n", __FILE__, __LINE__); goto label; }__WHILE0
#define ERRORF(label, ...) do{ GDB_DEBUG("%s(%d) : Error : " #label " : ", __FILE__, __LINE__); GDB_DEBUG(__VA_ARGS__); goto label; }__WHILE0
#else /* HAVE_GDB_DEBUG */
#define ERROR(label)       goto label
#define ERRORF(label, ...) goto label
#endif /* !HAVE_GDB_DEBUG */

INTERN uintptr_t GDBRemote_Features = 0;
INTERN uintptr_t GDBServer_Features = 0;

/* Set to true after an async stop notification is send
 * Set to false after vStopped was called when no more stop notifications were pending.
 * -> When `false', GDB_Main() is allowed to send out stop notifications
 *    when waiting for the first byte of some new packet. */
PRIVATE bool GDBServer_DidSendAsyncStopNotification = false;

/* Set to true when a detach command was issued that implies detach-from-everything
 * Set to false when a command other than detach-something or select-thread is encountered. */
PRIVATE bool GDBServer_DidDetachFromEverything = false;

#define GDBTHREADSEL_MODE_SINGLE  0 /* Only a single thread */
#define GDBTHREADSEL_MODE_PROCESS 1 /* The entire process that `ts_thread' is apart of */
#define GDBTHREADSEL_MODE_ALL     2 /* Everything, everywhere (`ts_thread' is a fallback thread) */

typedef struct {
	REF struct task *ts_thread; /* [1..1] The selected thread */
	unsigned int     ts_mode;   /* The used thread selection mode (One of `GDBTHREADSEL_MODE_*').  */
} GDBThreadSel;

#define GDBThreadSel_Copy(dst, src) (*(dst) = *(src), incref((dst)->ts_thread))
#define GDBThreadSel_MoveAssign(dst, src) (decref_unlikely((dst)->ts_thread), *(dst) = *(src))
#define GDBThreadSel_CopyAssign(dst, src) (incref((src)->ts_thread), decref_unlikely((dst)->ts_thread), *(dst) = *(src))
#define GDBThreadSel_Fini(self) decref_unlikely((self)->ts_thread)

PRIVATE GDBThreadSel GDB_CurrentThread_general  = { NULL, 0 };
PRIVATE GDBThreadSel GDB_CurrentThread_continue = { NULL, 0 };


PRIVATE char *
NOTHROW(FCALL GDB_EncodeError)(char *ptr, errno_t err) {
	*ptr++ = 'E';
	*ptr++ = GDB_ToHex((err >> 4) & 0xf);
	*ptr++ = GDB_ToHex(err & 0xf);
	return ptr;
}


PRIVATE char *
NOTHROW(FCALL GDB_EncodeHex)(char *ptr, void const *data, size_t datalen) {
	size_t i;
	for (i = 0; i < datalen; ++i) {
		byte_t b = ((byte_t *)data)[i];
		*ptr++ = GDB_ToHex(b >> 4);
		*ptr++ = GDB_ToHex(b & 0xf);
	}
	return ptr;
}

PRIVATE char *
NOTHROW(FCALL GDB_DecodeHex)(char const *ptr, void *data, size_t datalen) {
	size_t i;
	for (i = 0; i < datalen; ++i) {
		byte_t b;
		b  = GDB_FromHex(*ptr++) << 4;
		b |= GDB_FromHex(*ptr++);
		((byte_t *)data)[i] = b;
	}
	return (char *)ptr;
}

PRIVATE ssize_t
NOTHROW(KCALL GDB_HexPrinter)(void *arg, char const *__restrict data, size_t datalen) {
	size_t i;
	char *dst = *(char **)arg;
	for (i = 0; i < datalen; ++i) {
		byte_t b = ((byte_t *)data)[i];
		*dst++ = GDB_ToHex(b >> 4);
		*dst++ = GDB_ToHex(b & 0xf);
	}
	*(char **)arg = dst;
	return (ssize_t)datalen;
}

/* Inplace-decode escaped binary data and return the number of decoded bytes. */
PRIVATE size_t
NOTHROW(FCALL GDB_DecodeEscapedBinary)(char *buf, char *endptr) {
	char *dst = buf;
	char *flush_start = buf;
	size_t result = (size_t)(endptr - buf);
	while (buf < endptr) {
		size_t num_unescaped;
		char ch = *buf++;
		if (ch != '}')
			continue;
		num_unescaped = (size_t)((buf - 1) - flush_start);
		ch = *buf++;
		if (dst != flush_start)
			memmove(dst, flush_start, num_unescaped);
		dst += num_unescaped;
		*dst++ = ch ^ 0x20;
		flush_start = buf;
		--result;
	}
	if (dst != flush_start)
		memmove(dst, flush_start, (size_t)(endptr - flush_start));
	return result;
}


PRIVATE char *
NOTHROW(FCALL GDBEncode_IntAsHex)(char *buf, int v) {
	if (v < 0) {
		*buf++ = '-';
		v = -v;
	}
	buf += sprintf(buf, "%x", (unsigned int)v);
	return buf;
}

LOCAL pid_t NOTHROW(FCALL GDBThread_GetPID)(struct task *__restrict thread) {
	pid_t pid, tid;
	pid = task_getrootpid_of_s(thread);
	tid = task_getroottid_of_s(thread);
	if unlikely(!pid || !tid)
		pid = GDB_KERNEL_PID; /* Kernel thread. */
	return pid;
}

LOCAL pid_t NOTHROW(FCALL GDBThread_GetTID)(struct task *__restrict thread) {
	pid_t pid, tid;
	pid = task_getrootpid_of_s(thread);
	tid = task_getroottid_of_s(thread);
	if unlikely(!pid || !tid)
		tid = GDB_KERNEL_TID(thread); /* Kernel thread. */
	return tid;
}

INTERN char *
NOTHROW(FCALL GDBThread_EncodeThreadID)(char *buf, struct task *__restrict thread) {
	pid_t pid, tid;
	pid = task_getrootpid_of_s(thread);
	tid = task_getroottid_of_s(thread);
	if unlikely(!pid || !tid) {
		/* Kernel thread. */
		pid = GDB_KERNEL_PID;
		tid = GDB_KERNEL_TID(thread);
	}
	if (GDBServer_Features & GDB_SERVER_FEATURE_MULTIPROCESS) {
		*buf++ = 'p';
		buf = GDBEncode_IntAsHex(buf, pid);
		*buf++ = '.';
	}
	buf = GDBEncode_IntAsHex(buf, tid);
	return buf;
}

#define GDBTHREAD_ENCODETHREADID_MAXCHARS 21 /* p-12345678.-12345678\0 */
PRIVATE char *
NOTHROW(FCALL GDBThreadSel_EncodeThreadID)(char *buf,
                                           GDBThreadSel const *__restrict thread) {
	if (thread->ts_mode == GDBTHREADSEL_MODE_ALL) {
		if (GDBServer_Features & GDB_SERVER_FEATURE_MULTIPROCESS)
			buf = STPCAT(buf, "p-1.");
		buf = STPCAT(buf, "-1");
	} else if (thread->ts_mode == GDBTHREADSEL_MODE_PROCESS) {
		if (GDBServer_Features & GDB_SERVER_FEATURE_MULTIPROCESS) {
			*buf++ = 'p';
			buf = GDBEncode_IntAsHex(buf, GDBThread_GetPID(thread->ts_thread));
			*buf++ = '.';
		}
		buf = STPCAT(buf, "-1");
	} else {
		buf = GDBThread_EncodeThreadID(buf, thread->ts_thread);
	}
	return buf;
}

PRIVATE ssize_t
NOTHROW(FCALL GDBThread_VerifyPointer_Callback)(void *arg,
                                                struct task *__restrict thread) {
	if ((struct task *)arg == thread) {
		incref(thread);
		return -1; /* Found it! */
	}
	return 0;
}


DEFINE_CMDLINE_FLAG_VAR(opt_trust_pointers, "trust_pointers");

/* Verify that `thread' is a valid thread pointer, and return a new
 * reference to it if this is the case. - Otherwise, return `NULL'. */
PRIVATE WUNUSED REF struct task *
NOTHROW(FCALL GDBThread_VerifyPointer)(struct task *__restrict thread) {
	/* Don't do the (costly) enumeration if we think that we can trust the remote. */
	if (opt_trust_pointers)
		return incref(thread);
	/* Enumerate all threads, searching for the given `thread' in particular. */
	if (GDBThread_Enumerate(&GDBThread_VerifyPointer_Callback, thread) < 0)
		return thread;
	return NULL;
}

PRIVATE WUNUSED REF struct task *
NOTHROW(FCALL GDBThread_DoLookupPID)(upid_t pid) {
	if (pid == 0) /* Any thread */
		return incref(GDB_CurrentThread_general.ts_thread);
	if (pid == GDB_KERNEL_PID)
		return incref(&_bootidle);
	if (GDBThread_IsAllStopModeActive)
		return pidns_trylookup_task_locked(&pidns_root, (upid_t)pid);
	/* FIXME: What if one of the suspended threads is holding the PIDNS lock?
	 *        We should have some kind of timeout here, and switch to all-stop
	 *        mode if the timeout expires. */
	return pidns_trylookup_task(&pidns_root, (upid_t)pid);
}

PRIVATE WUNUSED REF struct task *
NOTHROW(FCALL GDBThread_DoLookupTID)(upid_t tid) {
	if (tid == 0) /* Any thread */
		return incref(GDB_CurrentThread_general.ts_thread);
	if (GDBThread_IsAllStopModeActive)
		return pidns_trylookup_task_locked(&pidns_root, (upid_t)tid);
	/* FIXME: What if one of the suspended threads is holding the PIDNS lock?
	 *        We should have some kind of timeout here, and switch to all-stop
	 *        mode if the timeout expires. */
	return pidns_trylookup_task(&pidns_root, (upid_t)tid);
}

/* Decode a thread ID, filling in `*result'.
 * @return: true:  Success
 * @return: false: Thread could not be found */
PRIVATE WUNUSED bool
NOTHROW(FCALL GDBThread_DecodeThreadID)(char **__restrict preader,
                                        GDBThreadSel *__restrict result) {
	char *reader = *preader;
	if ((GDBServer_Features & GDB_SERVER_FEATURE_MULTIPROCESS) && (*reader == 'p')) {
		pid_t pid, tid = -1;
		++reader;
		pid = strto32(reader, &reader, 16);
		if (*reader == '.') {
			++reader;
			tid = strto32(reader, &reader, 16);
		}
		if (pid == -1) {
			result->ts_mode   = GDBTHREADSEL_MODE_ALL;
			result->ts_thread = incref(GDB_CurrentThread_general.ts_thread);
		} else if (pid == GDB_KERNEL_PID) {
			if (tid == -1) {
				/* Select the entire kernel */
				result->ts_mode   = GDBTHREADSEL_MODE_PROCESS;
				result->ts_thread = incref(&_bootidle);
			} else if (tid == 0) {
				/* Select any thread. */
				result->ts_mode   = GDBTHREADSEL_MODE_SINGLE;
				result->ts_thread = incref(GDB_CurrentThread_general.ts_thread);
			} else {
				/* Select a specific kernel thread. */
				result->ts_mode   = GDBTHREADSEL_MODE_SINGLE;
				result->ts_thread = GDB_KERNEL_TID_GET(tid);
				result->ts_thread = GDBThread_VerifyPointer(result->ts_thread);
			}
		} else if (pid == 0) {
			/* Arbitrary process. */
			if (tid == 0) {
				/* Arbitrary thread. */
				result->ts_mode   = GDBTHREADSEL_MODE_SINGLE;
				result->ts_thread = incref(GDB_CurrentThread_general.ts_thread);
			} else if (tid == -1) {
				/* All threads of some arbitrary process. */
				result->ts_mode   = GDBTHREADSEL_MODE_PROCESS;
				result->ts_thread = incref(GDB_CurrentThread_general.ts_thread);
			} else {
				/* Specific thread of arbitrary process. */
				result->ts_mode   = GDBTHREADSEL_MODE_SINGLE;
				result->ts_thread = GDBThread_DoLookupTID((upid_t)tid);
				if (!result->ts_thread && GDB_KERNEL_TID_CHK(tid)) {
					result->ts_thread = GDB_KERNEL_TID_GET(tid);
					result->ts_thread = GDBThread_VerifyPointer(result->ts_thread);
				}
			}
		} else {
			if (tid == -1) {
				/* All threads of a specific process */
				result->ts_thread = GDBThread_DoLookupTID((upid_t)pid);
				result->ts_mode   = GDBTHREADSEL_MODE_PROCESS;
			} else if (tid == 0) {
				/* Any thread of a specific process */
				result->ts_thread = GDBThread_DoLookupTID((upid_t)pid);
				result->ts_mode   = GDBTHREADSEL_MODE_SINGLE;
			} else {
				/* Select a specific thread. */
				result->ts_thread = GDBThread_DoLookupTID((upid_t)tid);
				/* Verify the associated PID */
				if (result->ts_thread &&
				    unlikely(GDBThread_GetPID(result->ts_thread) != pid)) {
					decref_unlikely(result->ts_thread);
					result->ts_thread = NULL;
				}
			}
		}
	} else {
		pid_t tid;
		tid = strto32(reader, &reader, 16);
		if (tid == -1) {
			result->ts_mode   = GDBTHREADSEL_MODE_ALL;
			result->ts_thread = incref(GDB_CurrentThread_general.ts_thread);
		} else if (tid == 0) {
			result->ts_mode   = GDBTHREADSEL_MODE_SINGLE;
			result->ts_thread = incref(GDB_CurrentThread_general.ts_thread);
		} else {
			result->ts_mode   = GDBTHREADSEL_MODE_SINGLE;
			result->ts_thread = GDBThread_DoLookupTID((upid_t)tid);
			if (!result->ts_thread && GDB_KERNEL_TID_CHK(tid)) {
				result->ts_thread = GDB_KERNEL_TID_GET(tid);
				result->ts_thread = GDBThread_VerifyPointer(result->ts_thread);
			}
		}
	}
	if (!result->ts_thread)
		return false;
	*preader = reader;
	return true;
}

LOCAL NONNULL((1)) void
NOTHROW(FCALL GDBThreadSel_Stop)(GDBThreadSel *__restrict thread,
                                 bool generateAsyncStopEvents DFL(false)) {
	if (thread->ts_mode == GDBTHREADSEL_MODE_ALL) {
		if (generateAsyncStopEvents && (GDBServer_Features & GDB_SERVER_FEATURE_NONSTOP)) {
			GDBThread_StopAllAndGenerateAsyncStopEvents();
		} else {
			GDBThread_StopAllCpus();
		}
	} else if (thread->ts_mode == GDBTHREADSEL_MODE_PROCESS) {
		GDBThread_StopProcess(thread->ts_thread, generateAsyncStopEvents);
	} else {
		GDBThread_Stop(thread->ts_thread, generateAsyncStopEvents);
	}
}

/* Pop all stop events for threads described by `thread'.
 * As far as call-semantics go, this function behaves
 * identical to `GDBThread_PopStopEventProcess()' */
LOCAL NONNULL((1)) GDBThreadStopEvent *
NOTHROW(FCALL GDBThreadSel_PopStopEvents)(GDBThreadSel *__restrict thread,
                                          GDBThreadStopEvent **__restrict plastevent) {
	GDBThreadStopEvent *result;
	if (thread->ts_mode == GDBTHREADSEL_MODE_ALL) {
		GDBThreadStopEvent *last;
		/* Capture all stop events. */
		result = last = GDBThread_Stopped;
		GDBThread_Stopped = NULL;
		if (last) {
			while (last->tse_next)
				last = last->tse_next;
		}
		*plastevent = last;
	} else if (thread->ts_mode == GDBTHREADSEL_MODE_PROCESS) {
		result = GDBThread_PopStopEventProcess(thread->ts_thread, plastevent);
	} else {
		result = GDBThread_PopStopEvent(thread->ts_thread);
		*plastevent = result;
	}
	return result;
}

LOCAL NONNULL((1)) void
NOTHROW(FCALL GDBThreadSel_Resume)(GDBThreadSel *__restrict thread) {
	if (thread->ts_mode == GDBTHREADSEL_MODE_ALL) {
		GDBThread_ResumeEverything();
	} else if (thread->ts_mode == GDBTHREADSEL_MODE_PROCESS) {
		GDBThread_ResumeProcess(thread->ts_thread);
	} else {
		GDBThread_Resume(thread->ts_thread);
	}
}



/* Buffer used to store the contents of remote command packets. */
INTERN char GDBRemote_CommandBuffer[CONFIG_GDBSERVER_PACKET_MAXLEN + 1];

LOCAL void NOTHROW(FCALL GDBServer_SetRemoteAttached)(void) {
	if (GDBServer_Features & GDB_SERVER_FEATURE_ATTACHED)
		return;
	printk(KERN_INFO "[gdb] Attached to remote\n");
	GDBServer_Features |= GDB_SERVER_FEATURE_ATTACHED;
	kernel_debugtraps_install(&GDBServer_DebugTraps);
}

LOCAL void NOTHROW(FCALL GDBServer_SetRemoteDetached)(void) {
	if (!(GDBServer_Features & GDB_SERVER_FEATURE_ATTACHED))
		return;
	printk(KERN_INFO "[gdb] Detached from remote\n");
	kernel_debugtraps_uninstall(&GDBServer_DebugTraps);
	GDBServer_Features &= ~GDB_SERVER_FEATURE_ATTACHED;
}


#ifdef __x86_64__
#define REASON_REGISTER_MAXSIZE 8
#define FOREACH_REASON_REGISTER(callback)   \
	callback("05", GDB_REGISTER_X86_64_RBP) \
	callback("04", GDB_REGISTER_X86_64_RSP) \
	callback("10", GDB_REGISTER_X86_64_RIP)
#elif defined(__i386__)
#define REASON_REGISTER_MAXSIZE 4
#define FOREACH_REASON_REGISTER(callback) \
	callback("05", GDB_REGISTER_I386_EBP) \
	callback("04", GDB_REGISTER_I386_ESP) \
	callback("08", GDB_REGISTER_I386_EIP)
#endif



PRIVATE char *
NOTHROW(FCALL GDB_ConstructStopReply)(char *ptr,
                                      GDBThreadStopEvent *__restrict notif) {
	struct debugtrap_reason *reason;
	struct task *thread;
	reason = notif->tse_reason;
	thread = notif->tse_thread;
	if likely(reason) {
		u8 signo = (u8)reason->dtr_signo;
		/* Handle the special cases of thread/process exit events */
		switch (reason->dtr_reason) {

		case DEBUGTRAP_REASON_TEXITED:
			ptr += sprintf(ptr, "w%x;", reason->dtr_signo);
			ptr = GDBThread_EncodeThreadID(ptr, (struct task *)reason->dtr_ptrarg);
			goto done;

		case DEBUGTRAP_REASON_PEXITED: {
			union wait w;
			w.w_status = (int)(unsigned int)reason->dtr_signo;
			if (WIFSIGNALED(w)) {
				if (GDBServer_Features & GDB_SERVER_FEATURE_MULTIPROCESS) {
					ptr += sprintf(ptr, "X%x;process:", WTERMSIG(w));
					ptr = GDBEncode_IntAsHex(ptr, GDBThread_GetPID((struct task *)reason->dtr_ptrarg));
				} else {
					*ptr++ = 'X';
					*ptr++ = GDB_ToHex((WTERMSIG(w) >> 4) & 0xf);
					*ptr++ = GDB_ToHex(WTERMSIG(w) & 0xf);
				}
			} else {
				if (GDBServer_Features & GDB_SERVER_FEATURE_MULTIPROCESS) {
					ptr += sprintf(ptr, "W%x;process:", WEXITSTATUS(w));
					ptr = GDBEncode_IntAsHex(ptr, GDBThread_GetPID((struct task *)reason->dtr_ptrarg));
				} else {
					*ptr++ = 'W';
					*ptr++ = GDB_ToHex((WEXITSTATUS(w) >> 4) & 0xf);
					*ptr++ = GDB_ToHex(WEXITSTATUS(w) & 0xf);
				}
				ptr += sprintf(ptr, "W%x", reason->dtr_signo);
			}
			ptr = GDBThread_EncodeThreadID(ptr, (struct task *)reason->dtr_ptrarg);
		}	goto done;

		/* GDB expects certain signals for specific reasons. */

		case DEBUGTRAP_REASON_FORK:
			if (GDBRemote_Features & GDB_REMOTE_FEATURE_FORKEVENTS)
				signo = SIGTRAP;
			break;

		case DEBUGTRAP_REASON_VFORK:
		case DEBUGTRAP_REASON_VFORKDONE:
			if (GDBRemote_Features & GDB_REMOTE_FEATURE_VFORKEVENTS)
				signo = SIGTRAP;
			break;

		case DEBUGTRAP_REASON_EXEC:
			if (GDBRemote_Features & GDB_REMOTE_FEATURE_EXECEVENTS)
				signo = SIGTRAP;
			break;

		case DEBUGTRAP_REASON_CLONE:
			if (GDBRemote_Features & GDB_REMOTE_FEATURE_THREADEVENTS)
				signo = SIGTRAP;
			break;

		case DEBUGTRAP_REASON_SC_ENTRY:
		case DEBUGTRAP_REASON_SC_EXIT:
			signo = SIGTRAP;
			break;

		default:
			break;
		}
		*ptr++ = 'T';
		*ptr++ = GDB_ToHex(signo >> 4);
		*ptr++ = GDB_ToHex(signo & 0xf);
		switch (reason->dtr_reason) {

		case DEBUGTRAP_REASON_FORK:
			if (GDBRemote_Features & GDB_REMOTE_FEATURE_FORKEVENTS) {
do_fork_event:
				/* Make sure that the child process has been stopped */
				if (GDBThread_IsNonStopModeActive)
					GDBThread_Stop((struct task *)reason->dtr_ptrarg);
				ptr = STPCAT(ptr, "fork:");
				ptr = GDBThread_EncodeThreadID(ptr, (struct task *)reason->dtr_ptrarg);
				*ptr++ = ';';
			}
			break;

		case DEBUGTRAP_REASON_VFORK:
			if (GDBRemote_Features & GDB_REMOTE_FEATURE_VFORKEVENTS) {
				*ptr++ = 'v';
				goto do_fork_event;
			}
			break;

		case DEBUGTRAP_REASON_VFORKDONE:
			if (GDBRemote_Features & GDB_REMOTE_FEATURE_VFORKEVENTS) {
				ptr = STPCAT(ptr, "vforkdone:;");
			}
			break;

		case DEBUGTRAP_REASON_EXEC:
			if (GDBRemote_Features & GDB_REMOTE_FEATURE_EXECEVENTS) {
				char const *path;
				size_t i, pathlen;
				ptr = STPCAT(ptr, "exec:");
				path    = reason->dtr_strarg;
				pathlen = strlen(path);
				for (i = 0; i < pathlen; ++i) {
					byte_t b = (byte_t)path[i];
					*ptr++ = GDB_ToHex(b >> 4);
					*ptr++ = GDB_ToHex(b & 0xf);
				}
				*ptr++ = ';';
			}
			break;

		case DEBUGTRAP_REASON_CLONE:
			if (GDBRemote_Features & GDB_REMOTE_FEATURE_THREADEVENTS) {
				ptr = STPCAT(ptr, "create:;");
			}
			break;

		case DEBUGTRAP_REASON_SC_ENTRY:
		case DEBUGTRAP_REASON_SC_EXIT: {
			if (reason->dtr_reason == DEBUGTRAP_REASON_SC_ENTRY) {
				ptr = STPCAT(ptr, "syscall_entry:");
			} else {
				ptr = STPCAT(ptr, "syscall_return:");
			}
			*ptr++ = ':';
			ptr = GDBEncode_IntAsHex(ptr, (int)(unsigned int)reason->dtr_intarg);
			*ptr++ = ';';
		}	break;

		case DEBUGTRAP_REASON_WATCHR:
			*ptr++ = 'r';
			goto do_reason_watch;
		case DEBUGTRAP_REASON_WATCHRW:
			*ptr++ = 'a';
			ATTR_FALLTHROUGH
		case DEBUGTRAP_REASON_WATCHW:
do_reason_watch:
			ptr = STPCAT(ptr, "watch:");
			ptr += sprintf(ptr, "%x", reason->dtr_ptrarg);
			*ptr++ = ';';
			break;

		case DEBUGTRAP_REASON_SWBREAK:
			*ptr++ = 's';
			goto do_wbreak;
		case DEBUGTRAP_REASON_HWBREAK:
			*ptr++ = 'h';
do_wbreak:
			ptr = STPCAT(ptr, "wbreak:;");
			break;

		case DEBUGTRAP_REASON_LIBRARY:
			ptr = STPCAT(ptr, "library:;");
			break;

		default:
			break;
		}

	} else {
		/* Shouldn't actually get here, since stop events without reason should
		 * never cause stop replies to be constructed in the first place! */
		ptr = STPCAT(ptr, "T05"); /* SIGTRAP */
	}

	/* Additional registers. */
	ptr = STPCAT(ptr, "thread:");
	ptr = GDBThread_EncodeThreadID(ptr, thread);
	*ptr++ = ';';
	ptr += sprintf(ptr, "core:%x;", thread->t_cpu->c_id);

	/* Always include a select number of registers in the response. */
#ifdef FOREACH_REASON_REGISTER
#ifndef REASON_REGISTER_MAXSIZE
#define REASON_REGISTER_MAXSIZE GDB_REGISTER_MAXSIZE
#endif /* !REASON_REGISTER_MAXSIZE */
	{
		size_t reglen;
		byte_t regbuf[REASON_REGISTER_MAXSIZE];
#define ENCODE_GENERIC_REGISTER(hex, regno)                              \
		ptr    = STPCAT(ptr, hex);                                       \
		*ptr++ = ':';                                                    \
		reglen = GDB_GetRegister(thread, regno, regbuf, sizeof(regbuf)); \
		ptr    = GDB_EncodeHex(ptr, regbuf, reglen);                     \
		*ptr++ = ';';
		FOREACH_REASON_REGISTER(ENCODE_GENERIC_REGISTER)
#undef ENCODE_GENERIC_REGISTER
	}
#endif /* FOREACH_REASON_REGISTER */

done:
	return ptr;
}



#define GDB_HANDLECOMMAND_CONT 0 /* Continue handling command packets */
#define GDB_HANDLECOMMAND_EXIT 1 /* Check if we should return from GDB_Main() */
#define GDB_HANDLECOMMAND_DTCH 2 /* Detach from the GDB remote, then return from GDB_Main() */



LOCAL bool NOTHROW(FCALL GDB_GetNoAckModeEnabled)(void) {
	return (GDBServer_Features & GDB_SERVER_FEATURE_NOACK) != 0;
}

LOCAL void NOTHROW(FCALL GDB_SetNoAckModeEnabled)(bool enabled) {
	if (enabled) {
		ATOMIC_FETCHOR(GDBServer_Features, GDB_SERVER_FEATURE_NOACK);
	} else {
		ATOMIC_FETCHAND(GDBServer_Features, ~GDB_SERVER_FEATURE_NOACK);
	}
}

LOCAL bool NOTHROW(FCALL GDB_GetDisableRandomization)(void) {
	return vm_get_aslr_disabled();
}

LOCAL void NOTHROW(FCALL GDB_SetDisableRandomization)(bool enabled) {
	vm_set_aslr_disabled(enabled);
}

LOCAL bool NOTHROW(FCALL GDB_GetNonStopModeEnabled)(void) {
	return GDBThread_IsNonStopModeActive;
}

LOCAL void NOTHROW(FCALL GDB_SetNonStopModeEnabled)(bool enabled) {
	if (enabled) {
		/* Enable non-stop mode. */
		ATOMIC_FETCHOR(GDBServer_Features, GDB_SERVER_FEATURE_NONSTOP);
		GDBThread_ResumeAllCpus();
	} else {
		/* Disable non-stop mode (and enter all-stop mode) */
		ATOMIC_FETCHAND(GDBServer_Features, ~GDB_SERVER_FEATURE_NONSTOP);
		GDBThread_StopAllCpus();
	}
}

LOCAL bool NOTHROW(FCALL GDB_GetThreadEventsEnabled)(void) {
	return (GDBRemote_Features & GDB_REMOTE_FEATURE_THREADEVENTS) != 0;
}

LOCAL void NOTHROW(FCALL GDB_SetThreadEventsEnabled)(bool enabled) {
	if (enabled) {
		ATOMIC_FETCHOR(GDBRemote_Features, GDB_REMOTE_FEATURE_THREADEVENTS);
	} else {
		ATOMIC_FETCHAND(GDBRemote_Features, ~GDB_REMOTE_FEATURE_THREADEVENTS);
	}
}

PRIVATE bool
NOTHROW(FCALL GDBServer_CreateMissingAsyncStopNotificationForSomeThread)(void) {
	struct task *notif_thread;
	notif_thread = GDB_CurrentThread_general.ts_thread;
	return GDBThread_CreateMissingAsyncStopNotification(notif_thread);
}




/* Handle a received GDB command
 * @return: * : One of `GDB_HANDLECOMMAND_*' */
PRIVATE unsigned int
NOTHROW(FCALL GDB_HandleCommand)(char *endptr) {
	char *o = GDBPacket_Start();
	char *i = GDBRemote_CommandBuffer;
	bool old_GDBServer_DidDetachFromEverything;
	GDBThreadSel newThread;
	old_GDBServer_DidDetachFromEverything = GDBServer_DidDetachFromEverything;
	GDBServer_DidDetachFromEverything = false;
	switch (*i++) {

	case '!':
		/* Extended mode (would allow GDB to restart the application being debugged)
		 * However, since we can't very well restart the kernel, don't do anything to
		 * let GDB think that this function isn't supported (but don't log a warning
		 * about this) */
		goto send_ok;

	case '?': {
		GDBThreadStopEvent *notif;
		/* Use this command to set the attached-state */
		GDBServer_SetRemoteAttached();
again_handle_questionmark:
		/* Re-create notifications for all stopped threads. */
		GDBThread_RestoreAllAsyncNotifEvents();
		/* Consume the first pending async notification event. */
		notif = GDBThread_ConsumeAsyncNotifEvent();
		if (notif) {
			o = GDB_ConstructStopReply(o, notif);
		} else if (GDBServer_Features & GDB_SERVER_FEATURE_NONSTOP) {
			/* Send OK if there are no stopped threads. */
			goto send_ok;
		} else {
			/* Make sure that everything is stopped. */
			GDBThread_StopAllCpus();
			/* Nothing was stopped in particular, but GDB still want's ~something~ to be stopped. */
			if (GDBServer_CreateMissingAsyncStopNotificationForSomeThread())
				goto again_handle_questionmark;
			/* Shouldn't really get here, but tell GDB 
			 * that there are no running threads. */
			*o++ = 'W';
			*o++ = '0';
			*o++ = '0';
		}
	}	break;

	case 'B': {
		vm_virt_t addr;
		errno_t error;
		/* Old-style breakpoint packet */
		addr = (vm_virt_t)strtou(i, &i, 16);
		if (*i++ != ',')
			ERROR(err_syntax);
		if (i != endptr - 1)
			ERROR(err_syntax);
		if (*i == 'S') {
			error = GDB_AddBreak(GDB_CurrentThread_general.ts_thread,
			                     GDB_BREAKPOINT_TYPE_SWBREAK, addr, 0);
		} else if (*i == 'C') {
			error = GDB_DelBreak(GDB_CurrentThread_general.ts_thread,
			                     GDB_BREAKPOINT_TYPE_SWBREAK, addr, 0);
		} else {
			ERROR(err_syntax);
		}
		if (error == ENOSYS || error == ENOMEM)
			ERROR(err_breakpoint_not_supported); /* Not supported */
		if (error != EOK) {
			o = GDB_EncodeError(o, error);
		} else {
send_ok:
			*o++ = 'O';
			*o++ = 'K';
		}
	}	break;

	case 'c':
parse_pc_and_resume_nostep:
		if (i != endptr) {
			void *addr;
			addr = (void *)strtou(i, &i, 16);
			if (i != endptr)
				ERROR(err_syntax);
			GDBThread_Stop(GDB_CurrentThread_continue.ts_thread);
			GDB_SetPC(GDB_CurrentThread_continue.ts_thread, addr);
		}
resume_nostep:
		GDB_SetSingleStep(GDB_CurrentThread_continue.ts_thread, false);
		GDBThreadSel_Resume(&GDB_CurrentThread_continue);
		return GDB_HANDLECOMMAND_EXIT;

	case 'C':
		strtoul(i, &i, 16); /* Signal number to continue with??? */
		if (i != endptr) {
			if (*i++ != ';')
				ERROR(err_syntax);
			goto parse_pc_and_resume_nostep;
		}
		goto resume_nostep;

	case 'd': /* Toggle debugging??? */
		break;

	case 'D': {
		pid_t pid;
		GDBServer_DidDetachFromEverything = old_GDBServer_DidDetachFromEverything;
		if (i == endptr) {
			/* Gracefully detach */
send_ok_and_detach:
			GDBServer_DidDetachFromEverything = true;
			if (!GDBPacket_Send("OK")) /* Prevent WUNUSED warning */
				return GDB_HANDLECOMMAND_DTCH;
			return GDB_HANDLECOMMAND_DTCH;
		}
		if (*i++ != ';')
			ERROR(err_syntax);
		pid = strto32(i, &i, 16); /* PID */
		if (i != endptr)
			ERROR(err_syntax);
		if (pid == -1)
			goto send_ok_and_detach; /* Detach from everything */
		if (pid == 0)
			goto send_ok_and_detach; /* Detach from anything */
		if (pid == GDB_KERNEL_PID)
			goto send_ok_and_detach; /* Detach from the kernel (also implies detach-from-everything) */
		/* For anything else, we handle detach as a
		 * command to resume execution of that process. */
		{
			REF struct task *proc;
			proc = GDBThread_DoLookupPID(pid);
			if unlikely(!proc)
				ERROR(err_ESRCH);
			GDBThread_ResumeProcess(proc);
			decref_unlikely(proc);
		}
		if (GDBServer_DidDetachFromEverything)
			goto send_ok_and_detach; /* Just keep on detaching... */
		goto send_ok;
	}	break;

	case 'g': {
		struct gdb_cpustate st;
		GDB_GetRegisters(GDB_CurrentThread_general.ts_thread, &st);
		o = GDB_EncodeHex(o, &st, sizeof(st));
	}	break;

	case 'G': {
		struct gdb_cpustate st;
		i = GDB_DecodeHex(i, &st, sizeof(st));
		if (i != endptr)
			ERROR(err_syntax);
		GDB_SetRegisters(GDB_CurrentThread_general.ts_thread, &st);
	}	goto send_ok;

	case 'H': {
		char op = *i++;
		GDBServer_DidDetachFromEverything = old_GDBServer_DidDetachFromEverything;
		if (op != 'c' && op != 'g')
			ERROR(err_syntax);
		if (!GDBThread_DecodeThreadID(&i, &newThread))
			ERROR(err_ESRCH);
		if (i != endptr)
			ERROR(err_syntax_newthread);
		if (op == 'c') {
			GDBThreadSel_MoveAssign(&GDB_CurrentThread_continue, &newThread);
		} else {
			GDBThreadSel_MoveAssign(&GDB_CurrentThread_general, &newThread);
		}
	}	goto send_ok;

	case 'i':
	case 's':
parse_pc_and_resume_dostep:
		if (i != endptr) {
			void *addr;
			addr = (void *)strtou(i, &i, 16);
#if 0 /* i [addr[,nnn]] -- nnn can be given to specify how often to step before breaking again. \
       * TODO: Maybe add support for this? */
			if (p != endptr)
				ERROR(err_syntax);
#endif
			GDBThread_Stop(GDB_CurrentThread_continue.ts_thread);
			GDB_SetPC(GDB_CurrentThread_continue.ts_thread, addr);
		}
resume_dostep:
		GDB_SetSingleStep(GDB_CurrentThread_continue.ts_thread, true);
		GDBThreadSel_Resume(&GDB_CurrentThread_continue);
		return GDB_HANDLECOMMAND_EXIT;

	case 'I':
	case 'S':
		strtoul(i, &i, 16); /* Signal number to continue with??? */
		if (i != endptr) {
			if (*i++ != ';')
				ERROR(err_syntax);
			goto parse_pc_and_resume_dostep;
		}
		goto resume_dostep;

	case 'k':
		if (i != endptr)
			ERROR(err_syntax);
		GDBThread_KillKernel();
		break;

	case 'm': {
		vm_virt_t addr;
		size_t length, error, j;
		addr = (vm_virt_t)strtou(i, &i, 16);
		if (*i++ != ',')
			ERROR(err_syntax);
		length = strtou(i, &i, 16);
		if (i != endptr)
			ERROR(err_syntax);
		if unlikely(length > CONFIG_GDBSERVER_PACKET_MAXLEN / 2)
			ERROR(err_MSGSIZE);
		error = GDB_ReadMemory(GDB_CurrentThread_general.ts_thread,
		                       addr, o, length);
		if (error != 0)
			ERROR(err_EFAULT);
		/* Encode memory as hex. */
		j = length;
		while (j--) {
			byte_t b = ((byte_t *)o)[j];
			o[(j * 2) + 0] = GDB_ToHex(b >> 4);
			o[(j * 2) + 1] = GDB_ToHex(b & 0xf);
		}
		o += length * 2;
	}	break;

	case 'M': {
		vm_virt_t addr;
		size_t length, error, j;
		addr = (vm_virt_t)strtou(i, &i, 16);
		if (*i++ != ',')
			ERROR(err_syntax);
		length = strtou(i, &i, 16);
		if (*i++ != ':')
			ERROR(err_syntax);
		if ((i + (length * 2)) != endptr)
			ERROR(err_syntax);
		/* Decode memory from hex. */
		for (j = 0; j < length; ++j) {
			byte_t b;
			b  = GDB_FromHex(i[(j * 2) + 0]) << 4;
			b |= GDB_FromHex(i[(j * 2) + 1]);
			i[j] = b;
		}
		error = GDB_WriteMemory(GDB_CurrentThread_general.ts_thread,
		                        addr, i, length);
		if (error != 0)
			ERROR(err_EFAULT);
		goto send_ok;
	}	break;

	case 'p': {
		uintptr_t regno;
		size_t reqlen;
		byte_t regbuf[GDB_REGISTER_MAXSIZE];
		regno = strtou(i, &i, 16);
		if (i != endptr)
			ERROR(err_syntax);
		reqlen = GDB_GetRegister(GDB_CurrentThread_general.ts_thread,
		                         regno, regbuf, sizeof(regbuf));
		if (!reqlen)
			ERROR(err_unknown_register);
		o = GDB_EncodeHex(o, regbuf, reqlen);
	}	break;

	case 'P': {
		uintptr_t regno;
		size_t reqlen, reglen;
		byte_t regbuf[GDB_REGISTER_MAXSIZE];
		regno = strtou(i, &i, 16);
		if (*i++ != '=')
			ERROR(err_syntax);
		if (i >= endptr)
			ERROR(err_syntax); /* Buffer too small */
		if ((i + (2 * GDB_REGISTER_MAXSIZE)) < endptr)
			ERROR(err_syntax); /* Buffer too large */
		if ((size_t)(endptr - i) & 1)
			ERROR(err_syntax); /* Dangling digit */
		reglen = (size_t)(endptr - i) / 2;
		GDB_DecodeHex(i, regbuf, reglen);
		reqlen = GDB_SetRegister(GDB_CurrentThread_general.ts_thread,
		                         regno, regbuf, reglen);
		if (!reqlen) {
			if (GDBThread_HasTerminated(GDB_CurrentThread_general.ts_thread))
				goto send_ok;
			ERROR(err_unknown_register);
		}
		if (reqlen != reglen) {
			if (reqlen > reglen) {
				/* zero-extend */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
				memmove(regbuf, regbuf + (reqlen - reglen), reglen);
				memset(regbuf, 0, reqlen - reglen);
#else  /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
				memset(regbuf + reglen, 0, reqlen - reglen);
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
			} else {
				/* Try to trim zero/sign extensions. */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
				if (regbuf[reglen - 1] == 0xff) {
					/* Sign-extension */
					do {
						--reglen;
					} while (reglen > reqlen && regbuf[reglen - 1] == 0xff);
					if (!(regbuf[reglen - 1] & 0x80))
						ERROR(err_invalid_register_size); /* Wasn't sign-extended */
				} else if (regbuf[reglen - 1] == 0x00) {
					/* Zero-extension */
					do {
						--reglen;
					} while (reglen > reqlen && regbuf[reglen - 1] == 0x00);
				} else {
					ERROR(err_invalid_register_size);
				}
#else  /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
				if (regbuf[0] == 0xff) {
					/* Sign-extension */
					do {
						--reglen;
						memmove(regbuf, regbuf + 1, reglen);
					} while (reglen > reqlen && regbuf[0] == 0xff);
					if (!(regbuf[0] & 0x80))
						ERROR(err_invalid_register_size); /* Wasn't sign-extended */
				} else if (regbuf[0] == 0x00) {
					/* Zero-extension */
					do {
						--reglen;
						memmove(regbuf, regbuf + 1, reglen);
					} while (reglen > reqlen && regbuf[0] == 0x00);
				} else {
					ERROR(err_invalid_register_size);
				}
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
				if (reglen != reqlen)
					ERROR(err_invalid_register_size);
			}
			GDB_SetRegister(GDB_CurrentThread_general.ts_thread,
			                regno, regbuf, reqlen);
		}
		goto send_ok;
	}	break;

	case 't': {
		vm_virt_t addr;
		u32 pattern, mask;
		addr = (vm_virt_t)strtou(i, &i, 16);
		if (*i++ != ':')
			ERROR(err_syntax);
		pattern = (u32)strtoul(i, &i, 16);
		if (*i++ != ',')
			ERROR(err_syntax);
		mask = (u32)strtoul(i, &i, 16);
		if (i != endptr)
			ERROR(err_syntax);
		/* Really weird packet, but easy enough to implement... */
		for (;;) {
			uintptr_t pagebase, search_size;
			pagebase    = ((uintptr_t)addr - 3) & ~(pagedir_pagesize() - 1);
			search_size = ((uintptr_t)addr - pagebase) + 3;
			if (GDB_ReadMemory(GDB_CurrentThread_general.ts_thread,
			                   (vm_virt_t)pagebase,
			                   GDBRemote_CommandBuffer, search_size))
				ERROR(err_EFAULT);
			while (search_size--) {
				u32 value;
				value = UNALIGNED_GET32((u32 *)(GDBRemote_CommandBuffer + search_size));
				if ((value & mask) != pattern)
					continue; /* Different value... */
				/* The docs don't say how to respond, but try to mirror `qSearch:memory' */
				o += sprintf(o, "1,%p", pagebase + search_size);
				goto do_transmit;
			}
		}
	}	break;

	case 'T': {
		if (!GDBThread_DecodeThreadID(&i, &newThread))
			ERROR(err_ESRCH);
		if (i != endptr)
			ERROR(err_syntax_newthread);
		GDBThreadSel_Fini(&newThread);
	}	goto send_ok;

	case 'v': {
		char *nameEnd;
		size_t nameLen;
		nameEnd = i;
		for (;;) {
			char ch = *nameEnd;
			if (ch == ';' || ch == '?' || (!ch && nameEnd == endptr))
				break;
			++nameEnd;
		}
		nameLen = (size_t)(nameEnd - i);
#define ISNAME(name)                         \
		(nameLen == COMPILER_STRLEN(name) && \
		 memcmp(i, name, COMPILER_STRLEN(name) * sizeof(char)) == 0)
		if (ISNAME("Attach") && *nameEnd == ';') {
			/* Attach/detach is ignored... */
			goto send_empty;
		} else if (ISNAME("Cont")) {
			GDBThreadStopEvent *keepStoppedFirst = NULL;
			GDBThreadStopEvent *keepStoppedLast = NULL;
			bool didSetSingleStepHint = false;
			i = nameEnd;
			if (*i == '?') {
				if (i + 1 != endptr)
					ERROR(err_syntax);
				o = STPCAT(o, "vCont;c;C;s;S;t;r");
				goto do_transmit;
			}
			while (*i == ';') {
				char action;
				++i;
				action = *i++;
				switch (action) {

				case 'C':
				case 'S':
					strtoul(i, &i, 16); /* signo? */
					action += 'a' - 'A';
					ATTR_FALLTHROUGH
				case 'c':
				case 's':
					if (*i == ':') {
						++i;
						if (!GDBThread_DecodeThreadID(&i, &newThread))
							newThread.ts_thread = NULL;
						if likely(newThread.ts_thread) {
do_set_step_newThread:
							if (newThread.ts_mode == GDBTHREADSEL_MODE_ALL) {
								GDBThreadSel_Fini(&newThread);
								goto set_single_step_all_threads;
							}
							if (newThread.ts_mode == GDBTHREADSEL_MODE_PROCESS) {
								GDBThreadStopEvent *iter;
								struct task *proc = task_getprocess_of(newThread.ts_thread);
								for (iter = GDBThread_Stopped; iter;
								     iter = iter->tse_next) {
									if (task_getprocess_of(iter->tse_thread) != proc)
										continue; /* Different process */
									GDB_SetSingleStep(iter->tse_thread, action == 's');
								}
							} else {
								GDBThread_Stop(newThread.ts_thread);
								GDB_SetSingleStep(newThread.ts_thread, action == 's');
							}
							GDBThreadSel_Resume(&newThread);
							GDBThreadSel_Fini(&newThread);
						}
					} else {
						/* Match all stopped threads */
set_single_step_all_threads:
						if (GDBThread_Stopped) {
							GDBThreadStopEvent *iter;
							for (iter = GDBThread_Stopped; iter;
							     iter = iter->tse_next) {
								GDB_SetSingleStep(iter->tse_thread, action == 's');
							}
						}
						GDBThread_ResumeEverything();
						goto done_vCont;
					}
					break;

				case 't': {
					GDBThreadStopEvent *first, *last;
					first = last = NULL;
					if (*i == ':') {
						++i;
						if (!GDBThread_DecodeThreadID(&i, &newThread))
							newThread.ts_thread = NULL;
						if likely(newThread.ts_thread) {
							/* Stop threads, and generate async stop notifications */
							GDBThreadSel_Stop(&newThread, true);
							/* Capture all fully stopped threads, such that they don't
							 * get resumed by additional commands which may be found later
							 * on the commandline. */
							first = GDBThreadSel_PopStopEvents(&newThread, &last);
							GDBThreadSel_Fini(&newThread);
						}
					} else {
						if (GDBServer_Features & GDB_SERVER_FEATURE_NONSTOP) {
							GDBThread_StopAllAndGenerateAsyncStopEvents();
						} else {
							GDBThread_StopAllCpus();
						}
						goto done_vCont;
					}
					assert((first != NULL) == (last != NULL));
					if (first) {
						last->tse_next = keepStoppedFirst;
						keepStoppedFirst = first;
						if (!keepStoppedLast)
							keepStoppedLast = last;
					}
				}	break;

				case 'r': {
					vm_virt_t start, end;
					start = (vm_virt_t)strtou(i, &i, 16);
					if (*i++ != ',')
						ERROR(err_syntax);
					end = (vm_virt_t)strtou(i, &i, 16);
					action = 's';
					if (*i == ':') {
						++i;
						if (!GDBThread_DecodeThreadID(&i, &newThread))
							newThread.ts_thread = NULL;
						if likely(newThread.ts_thread) {
							GDB_SetSingleStepIgnoredRange(newThread.ts_thread, start, end);
							didSetSingleStepHint = true;
							goto do_set_step_newThread;
						}
					} else {
						/* Technically, we'd have to accept any thread at this point,
						 * but this feature is optional anyways, so using a specific
						 * thread for this purpose is also OK. */
						GDB_SetSingleStepIgnoredRange(GDB_CurrentThread_continue.ts_thread,
						                              start, end);
						didSetSingleStepHint = true;
						goto set_single_step_all_threads;
					}
				}	break;

				default:
					ERROR(err_syntax);
				}
			}
done_vCont:
			if (!didSetSingleStepHint)
				GDB_DelSingleStepIgnoredRange();
			assert((keepStoppedFirst != NULL) ==
			       (keepStoppedLast != NULL));
			/* Restore stopped threads. */
			if (keepStoppedFirst) {
				keepStoppedLast->tse_next = GDBThread_Stopped;
				GDBThread_Stopped = keepStoppedFirst;
			}
			/* In non-stop mode, we must respond with `OK' */
			if (GDBServer_Features & GDB_SERVER_FEATURE_NONSTOP) {
				if (!GDBPacket_Send("OK"))
					return GDB_HANDLECOMMAND_DTCH;
			}
			return GDB_HANDLECOMMAND_EXIT;
		} else if (ISNAME("CtrlC")) {
			if (nameEnd != endptr)
				ERROR(err_syntax);
			/* Make sure that full-stop mode has been activated. */
			GDBThread_StopAllCpus();
			goto send_ok;
//		} else if (ISNAME("Kill") && *nameEnd == ';') { // TODO
		} else if (ISNAME("MustReplyEmpty")) {
			if (nameEnd != endptr)
				ERROR(err_syntax);
send_empty:
			;
		} else if (ISNAME("Stopped")) {
			GDBThreadStopEvent *notif;
			/* Send additional async stop notifications to GDB */
			notif = GDBThread_ConsumeAsyncNotifEvent();
			if (!notif) {
				GDBServer_DidSendAsyncStopNotification = false;
				goto send_ok;
			}
			o = GDB_ConstructStopReply(o, notif);
		} else {
			ERROR(unknown);
		}
#undef ISNAME
	}	break;

		/* General query packet */
	case 'q': {
		char *nameEnd;
		size_t nameLen;
		nameEnd = i;
		for (;;) {
			char ch = *nameEnd;
			if (ch == ',' || ch == ':' || ch == ';' || (!ch && nameEnd == endptr))
				break;
			++nameEnd;
		}
		nameLen = (size_t)(nameEnd - i);
#define ISNAME(name)                         \
		(nameLen == COMPILER_STRLEN(name) && \
		 memcmp(i, name, COMPILER_STRLEN(name) * sizeof(char)) == 0)
		if (ISNAME("C")) {
			if (nameEnd != endptr)
				ERROR(err_syntax);
			*o++ = 'Q';
			*o++ = 'C';
			o = GDBThreadSel_EncodeThreadID(o, &GDB_CurrentThread_general);
		} else if (ISNAME("Xfer")) {
			char *annex;
			ssize_t error;
			GDB_OffsetAndLengthPrinterData dst;
			bool isReadOperation = true;
			i = nameEnd;
			if (*i++ != ':')
				ERROR(err_qXfer_syntax);
			nameEnd = strchr(i, ':');
			if unlikely(!nameEnd)
				ERROR(err_qXfer_syntax);
			nameLen = (size_t)(nameEnd - i);
			++nameEnd;
			if (*nameEnd == 'r') {
				++nameEnd;
				if unlikely(*nameEnd++ != 'e')
					ERROR(err_qXfer_syntax);
				if unlikely(*nameEnd++ != 'a')
					ERROR(err_qXfer_syntax);
				if unlikely(*nameEnd++ != 'd')
					ERROR(err_qXfer_syntax);
			} else if (*nameEnd == 'w') {
				++nameEnd;
				if unlikely(*nameEnd++ != 'r')
					ERROR(err_qXfer_syntax);
				if unlikely(*nameEnd++ != 'i')
					ERROR(err_qXfer_syntax);
				if unlikely(*nameEnd++ != 't')
					ERROR(err_qXfer_syntax);
				if unlikely(*nameEnd++ != 'e')
					ERROR(err_qXfer_syntax);
				isReadOperation = false;
			} else {
				ERROR(err_qXfer_syntax);
			}
			if unlikely(*nameEnd++ != ':') ERROR(err_qXfer_syntax);
			annex = nameEnd;
			nameEnd = strchr(nameEnd, ':');
			if unlikely(!nameEnd)
				ERROR(err_qXfer_syntax);
			*nameEnd++ = '\0';
			dst.ol_offset = strtou(nameEnd, &nameEnd, 16);
			if unlikely(*nameEnd++ != ',') ERROR(err_qXfer_syntax);
			dst.ol_size = strtou(nameEnd, &nameEnd, 16);
			if unlikely(nameEnd != endptr) ERROR(err_qXfer_syntax);
			dst.ol_buf = o + 1;
			/* Handle reading from different objects. */
			if (ISNAME("exec-file") && isReadOperation) {
				pid_t pid;
				REF struct task *proc;
				pid = strto32(annex, &annex, 16);
				if unlikely(*annex != 0)
					ERROR(err_qXfer_syntax);
				proc = GDBThread_DoLookupPID(pid);
				if unlikely(!proc)
					error = -ESRCH;
				else {
					error = GDBInfo_PrintThreadExecFile(&GDB_OffsetAndLengthPrinter,
					                                    &dst, proc, false);
					decref_unlikely(proc);
				}
			} else if (ISNAME("features") && isReadOperation) {
				error = GDBInfo_PrintFeaturesFile(&GDB_OffsetAndLengthPrinter, &dst, annex);
			} else if (ISNAME("libraries") && isReadOperation) {
				if (*annex != 0)
					ERROR(err_qXfer_syntax);
				error = GDBInfo_PrintLibraryList(&GDB_OffsetAndLengthPrinter, &dst,
				                                 GDB_CurrentThread_general.ts_thread);
			} else if (ISNAME("threads") && isReadOperation) {
				if (*annex != 0)
					ERROR(err_qXfer_syntax);
				error = GDBInfo_PrintThreadList(&GDB_OffsetAndLengthPrinter, &dst);
			} else if (ISNAME("osdata") && isReadOperation) {
				error = GDBInfo_PrintOSData(&GDB_OffsetAndLengthPrinter, &dst, annex);
			} else {
				ERROR(unknown);
			}
			if (error == __SSIZE_MIN__) {
				*o = 'm'; /* There is more data... */
				o = dst.ol_buf;
			} else if (error < 0) {
				/* Assume that a negative value indicate a negative ERRNO value */
				o = GDB_EncodeError(o, -error);
			} else {
				*o = 'l'; /* This is the last packet */
				o = dst.ol_buf;
			}
			/* QXFER uses the escape-transmit mechanism to deliver data. */
			if (!GDBPacket_Transmit(o))
				return GDB_HANDLECOMMAND_DTCH;
			return GDB_HANDLECOMMAND_CONT;
		} else if (ISNAME("ThreadExtraInfo")) {
			i = nameEnd;
			if (*i++ != ',')
				ERROR(err_syntax);
			if (!GDBThread_DecodeThreadID(&i, &newThread))
				newThread.ts_thread = NULL;
			if (i != endptr)
				ERROR(err_syntax_newthread);
			if unlikely(!newThread.ts_thread)
				ERROR(err_ESRCH);
			o = GDBPacket_Start();
			GDBInfo_PrintThreadName(&GDB_HexPrinter, &o, newThread.ts_thread);
			GDBThreadSel_Fini(&newThread);
		} else if (ISNAME("Attached")) {
			i = nameEnd;
			if (*i == ':') {
				pid_t pid;
				REF struct task *thread;
				++i;
				pid = strto32(i, &i, 16);
				if (i != endptr)
					ERROR(err_syntax);
				/* Verify that the thread exists. */
				thread = GDBThread_DoLookupPID(pid);
				if (!thread)
					ERROR(err_ESRCH);
				decref_unlikely(thread);
			} else {
				if (i != endptr)
					ERROR(err_syntax);
			}
#if 0
			*o++ = '0'; /* Created a new process */
#else
			*o++ = '1'; /* Attached to an existing process */
#endif
#if 0 /* TODO */
		} else if (ISNAME("GetTLSAddr") && *nameEnd == ':') {
#endif
#if defined(__x86_64__) || defined(__i386__)
		} else if (ISNAME("GetTIBAddr") && *nameEnd == ':') {
			uintptr_t addr;
			i      = nameEnd + 1;
			if (!GDBThread_DecodeThreadID(&i, &newThread))
				newThread.ts_thread = NULL;
			if unlikely(i != endptr)
				ERROR(err_syntax_newthread);
			if unlikely(!newThread.ts_thread)
				ERROR(err_ESRCH);
#ifdef __x86_64__
			if (!GDB_GetRegister(newThread.ts_thread,
			                     GDB_REGISTER_X86_64_FSBASE,
			                     &addr, sizeof(addr))) {
				GDBThreadSel_Fini(&newThread);
				ERROR(err_ESRCH);
			}
#else /* __x86_64__ */
			addr = ATOMIC_READ(FORTASK(newThread.ts_thread, x86_this_user_gsbase));
#endif /* !__x86_64__ */
			GDBThreadSel_Fini(&newThread);
			o += sprintf(o, "%p", addr);
#endif /* __x86_64__ || __i386__ */
		} else if (i[0] == 'L' && i + 12 == endptr && (i[1] == '0' || i[1] == '1')) {
			char *pcount; u8 count;
			bool hasNext = true;
//			bool startflag = i[1] == '1';
			u8 maxCount = GDB_FromHex(i[2]) << 4 | GDB_FromHex(i[3]);
			u32 nextThread = (u32)GDB_FromHex(i[4]) << 28 | (u32)GDB_FromHex(i[5]) << 24 |
			                 (u32)GDB_FromHex(i[6]) << 20 | (u32)GDB_FromHex(i[7]) << 16 |
			                 (u32)GDB_FromHex(i[8]) << 12 | (u32)GDB_FromHex(i[9]) << 8 |
			                 (u32)GDB_FromHex(i[10]) << 4 | (u32)GDB_FromHex(i[11]);
			o = GDBPacket_Start();
			*o++ = 'q';
			*o++ = 'M';
			pcount = o;
			o += 3; /* Filled in later. */
			o += sprintf(o, "%.8I32x", nextThread);
			for (count = 0; count < maxCount; ++count) {
				REF struct task *thread;
				u32 threadid;
				thread = GDBThread_GetNth(nextThread + count);
				if (!thread) {
					hasNext = false;
					break;
				}
				threadid = GDBThread_GetTID(thread);
				decref_unlikely(thread);
				o += sprintf(o, "%.8I32x", threadid);
			}
			if (hasNext) {
				REF struct task *thread;
				thread = GDBThread_GetNth(nextThread + maxCount);
				hasNext = thread != NULL;
				xdecref_unlikely(thread);
			}
			pcount[0] = GDB_ToHex(count >> 4);
			pcount[1] = GDB_ToHex(count & 0xf);
			pcount[2] = hasNext ? '0' : '1'; /* done-flag */
		} else if (i[0] == 'P' && i + 9 > endptr) {
			/* These macros are taken from the GDB source.
			 * `remote.c:remote_unpack_thread_info_response()' */
#define TAG_THREADID    0x01 /* Echo the thread identifier.  */
#define TAG_EXISTS      0x02 /* Is this process defined enough to fetch registers and its stack?  */
#define TAG_DISPLAY     0x04 /* A short thing maybe to put on a window */
#define TAG_THREADNAME  0x08 /* string, maps 1-to-1 with a thread is.  */
#define TAG_MOREDISPLAY 0x10 /* Whatever the kernel wants to say about the process.  */
			u32 mode = (u32)GDB_FromHex(i[1]) << 28 | (u32)GDB_FromHex(i[2]) << 24 |
			           (u32)GDB_FromHex(i[3]) << 20 | (u32)GDB_FromHex(i[4]) << 16 |
			           (u32)GDB_FromHex(i[5]) << 12 | (u32)GDB_FromHex(i[6]) << 8 |
			           (u32)GDB_FromHex(i[7]) << 4 | (u32)GDB_FromHex(i[8]);
			i += 9;
			if (!GDBThread_DecodeThreadID(&i, &newThread))
				newThread.ts_thread = NULL;
			if (i != endptr)
				ERROR(err_syntax_newthread);
			if unlikely(!newThread.ts_thread)
				ERROR(err_ESRCH);
			mode &= 0x1f;
			*o++ = 'q';
			*o++ = 'M';
			o += sprintf(o, "%.8I32x", mode);
			o += sprintf(o, "%.8I32x", GDBThread_GetTID(newThread.ts_thread));
			if (mode & TAG_THREADID) {
				o += sprintf(o, "%.8I32x", TAG_THREADID);
				/* The GDB source asserts 16 for length this for some
				 * reason (even though only 8 bytes are processed) */
				o += sprintf(o, "%.8I32x", 16);
				o += sprintf(o, "%.8I32x", GDBThread_GetTID(newThread.ts_thread));
			}
			if (mode & TAG_EXISTS) {
				o += sprintf(o, "%.8I32x", TAG_EXISTS);
				o += sprintf(o, "%.8I32x", 8);
				o += sprintf(o, "%.8I32x", (newThread.ts_thread->t_flags & (TASK_FTERMINATED | TASK_FTERMINATING)) ? 0 : 1);
			}
			if (mode & TAG_THREADNAME) {
				char *namebuf; ssize_t namelen;
				o += sprintf(o, "%.8I32x", TAG_THREADNAME);
				namebuf = o + 8;
				namelen = GDBInfo_PrintThreadName(&format_sprintf_printer,
				                                  &namebuf, newThread.ts_thread);
				if unlikely(namelen < 0) {
					GDBThreadSel_Fini(&newThread);
					ERROR(err_ESRCH);
				}
				sprintf(o, "%.8I32x", namelen);
				o = namebuf;
			}
			GDBThreadSel_Fini(&newThread);
		} else if (ISNAME("Supported")) {
			i = nameEnd;
			GDBRemote_Features = 0;
			ATOMIC_FETCHAND(GDBServer_Features, ~(GDB_SERVER_FEATURE_MULTIPROCESS));
			if (*i == ':') {
				++i;
				for (;;) {
					nameEnd = strchrnul(i, ';');
					nameLen = (size_t)(nameEnd - i);
					if (nameEnd[-1] == '+') {
						--nameLen;
						if (ISNAME("multiprocess"))
							ATOMIC_FETCHOR(GDBServer_Features, GDB_SERVER_FEATURE_MULTIPROCESS);
						else if (ISNAME("swbreak"))
							ATOMIC_FETCHOR(GDBRemote_Features, GDB_REMOTE_FEATURE_SWBREAK);
						else if (ISNAME("hwbreak"))
							ATOMIC_FETCHOR(GDBRemote_Features, GDB_REMOTE_FEATURE_HWBREAK);
						else if (ISNAME("fork-events"))
							ATOMIC_FETCHOR(GDBRemote_Features, GDB_REMOTE_FEATURE_FORKEVENTS);
						else if (ISNAME("vfork-events"))
							ATOMIC_FETCHOR(GDBRemote_Features, GDB_REMOTE_FEATURE_VFORKEVENTS);
						else if (ISNAME("exec-events")) {
							ATOMIC_FETCHOR(GDBRemote_Features, GDB_REMOTE_FEATURE_EXECEVENTS);
						}
					}
					i = nameEnd;
					if (*nameEnd != ';')
						break;
					++i;
				}
			}
			if (i != endptr)
				ERRORF(err_syntax, "i=%$q, %Iu\n", (size_t)(endptr - i), i, (size_t)(endptr - i));
			o += sprintf(o, "PacketSize=%Ix", CONFIG_GDBSERVER_PACKET_MAXLEN/* + 4*/);
			o = STPCAT(o, ";QNonStop+");
			o = STPCAT(o, ";QStartNoAckMode+");
			if (GDBServer_Features & GDB_SERVER_FEATURE_MULTIPROCESS)
				o = STPCAT(o, ";multiprocess+");
			if (GDBRemote_Features & GDB_REMOTE_FEATURE_SWBREAK)
				o = STPCAT(o, ";swbreak+");
			if (GDBRemote_Features & GDB_REMOTE_FEATURE_HWBREAK)
				o = STPCAT(o, ";hwbreak+");
			if (GDBRemote_Features & GDB_REMOTE_FEATURE_FORKEVENTS)
				o = STPCAT(o, ";fork-events+");
			if (GDBRemote_Features & GDB_REMOTE_FEATURE_EXECEVENTS)
				o = STPCAT(o, ";exec-events+");
/*			o = STPCAT(o, ";QCatchSyscalls+"); // TODO */
			o = STPCAT(o, ";QThreadEvents+");
			o = STPCAT(o, ";QDisableRandomization+");
			o = STPCAT(o, ";qXfer:exec-file:read+");
			o = STPCAT(o, ";qXfer:libraries:read+");
			o = STPCAT(o, ";qXfer:threads:read+");
			o = STPCAT(o, ";qXfer:osdata:read+");
/*			o = STPCAT(o, ";qXfer:features:read+"); // I don't really understand what this is good for (yet) */
			o = STPCAT(o, ";vContSupported+");
		} else if (nameLen == 1 + COMPILER_STRLEN("ThreadInfo") &&
		           memcmp(i + 1, "ThreadInfo", COMPILER_STRLEN("ThreadInfo") * sizeof(char)) == 0 &&
		           (i[0] == 'f' || i[0] == 's')) {
			REF struct task *thread;
			char action = i[0];
			PRIVATE size_t threadinfo_nth = 0;
			if (action == 'f')
				threadinfo_nth = 0;
			thread = GDBThread_GetNth(threadinfo_nth);
			if (!thread) {
				*o++ = 'l';
				threadinfo_nth = (size_t)-1;
			} else {
#undef CONFIG_GDBSERVER_QTHREADINFO_ONE_PER_PACKET
//#define CONFIG_GDBSERVER_QTHREADINFO_ONE_PER_PACKET 1

#ifndef CONFIG_GDBSERVER_QTHREADINFO_ONE_PER_PACKET
				char *bufmax;
#endif /* !CONFIG_GDBSERVER_QTHREADINFO_ONE_PER_PACKET */
				++threadinfo_nth;
#ifndef CONFIG_GDBSERVER_QTHREADINFO_ONE_PER_PACKET
				bufmax = (o + CONFIG_GDBSERVER_PACKET_MAXLEN) -
				         (GDBTHREAD_ENCODETHREADID_MAXCHARS + 1);
#endif /* !CONFIG_GDBSERVER_QTHREADINFO_ONE_PER_PACKET */
				*o++ = 'm';
				o = GDBThread_EncodeThreadID(o, thread);
				decref_unlikely(thread);
#ifndef CONFIG_GDBSERVER_QTHREADINFO_ONE_PER_PACKET
				while (o < bufmax) {
					thread = GDBThread_GetNth(threadinfo_nth);
					if (!thread) {
						threadinfo_nth = (size_t)-1;
						break;
					}
					++threadinfo_nth;
					*o++ = ',';
					o    = GDBThread_EncodeThreadID(o, thread);
					decref_unlikely(thread);
				}
#endif /* !CONFIG_GDBSERVER_QTHREADINFO_ONE_PER_PACKET */
			}
		} else if (ISNAME("DisableRandomization")) {
			if (nameEnd != endptr)
				ERROR(err_syntax);
			*o++ = GDB_GetDisableRandomization() ? '1' : '0';
		} else if (ISNAME("Offsets")) {
			if (nameEnd != endptr)
				ERROR(err_syntax);
			/* Not supported (and not required) */
		} else if (ISNAME("Symbol")) {
			/* Not supported (and not required)
			 * This packet simply informs us that the GDB remote is able to service
			 * symbol lookup requests (something like name2addr("memcpy") == &memcpy)
			 * Some other implementation may need this in order to inject code into
			 * specific functions (such as `pthread_create()') in order to allow for
			 * tracing of special events such as the creation of a thread.
			 * However, we won't need to so something like that, so we can just
			 * ignore this packet. */
		} else if (ISNAME("TStatus")) {
			if (nameEnd != endptr)
				ERROR(err_syntax);
			/* This packet is used by GDB to probe support for tracepoint packets.
			 * Since we don't support something like this (yet?), just ignore the
			 * packet to prevent it from showing up as an `Unknown command' warning. */
		} else if (ISNAME("NoAckMode")) {
			if (nameEnd != endptr)
				ERROR(err_syntax);
			*o++ = GDB_GetNoAckModeEnabled() ? '1' : '0';
		} else if (ISNAME("NonStop")) {
			if (nameEnd != endptr)
				ERROR(err_syntax);
			*o++ = GDB_GetNonStopModeEnabled() ? '1' : '0';
		} else if (ISNAME("ThreadEvents")) {
			if (nameEnd != endptr)
				ERROR(err_syntax);
			*o++ = GDB_GetThreadEventsEnabled() ? '1' : '0';
		} else {
			goto unknown;
		}
#undef ISNAME
	}	break;

		/* General set packet */
	case 'Q': {
		char *nameEnd;
		size_t nameLen;
		nameEnd = i;
		for (;;) {
			char ch = *nameEnd;
			if (ch == ',' || ch == ':' || ch == ';' || (!ch && nameEnd == endptr))
				break;
			++nameEnd;
		}
		nameLen = (size_t)(nameEnd - i);
#define ISNAME(name)                         \
		(nameLen == COMPILER_STRLEN(name) && \
		 memcmp(i, name, COMPILER_STRLEN(name) * sizeof(char)) == 0)
		if (ISNAME("DisableRandomization") && *nameEnd == ':') {
			unsigned long mode;
			i    = nameEnd + 1;
			mode = strtoul(i, &i, 16);
			if (i != endptr)
				ERROR(err_syntax);
			GDB_SetDisableRandomization(mode != 0);
			goto send_ok;
		} else if (ISNAME("ThreadEvents")) {
			unsigned long mode;
			i    = nameEnd + 1;
			mode = strtoul(i, &i, 16);
			if (i != endptr)
				ERROR(err_syntax);
			GDB_SetThreadEventsEnabled(mode != 0);
			goto send_ok;
		} else if (ISNAME("StartNoAckMode") && nameEnd == endptr) {
			/* Send the response while still in ack-mode
			 * GDB still responds with a `+' for this one! */
			if (!GDBPacket_Send("OK"))
				return GDB_HANDLECOMMAND_DTCH;
			GDB_SetNoAckModeEnabled(true);
			return GDB_HANDLECOMMAND_CONT;
		} else if (ISNAME("NoAckMode") && *nameEnd == ':') {
			unsigned long mode;
			i    = nameEnd + 1;
			mode = strtoul(i, &i, 16);
			if (i != endptr)
				ERROR(err_syntax);
			GDB_SetNoAckModeEnabled(mode != 0);
			goto send_ok;
		} else if (ISNAME("NonStop") && *nameEnd == ':') {
			unsigned long mode;
			i    = nameEnd + 1;
			mode = strtoul(i, &i, 16);
			if (i != endptr)
				ERROR(err_syntax);
			GDB_SetNonStopModeEnabled(mode != 0);
			goto send_ok;
		} else if (ISNAME("C") && *nameEnd == ':') {
			GDBServer_DidDetachFromEverything = old_GDBServer_DidDetachFromEverything;
			i = nameEnd + 1;
			if (!GDBThread_DecodeThreadID(&i, &newThread))
				goto err_ESRCH;
			if (nameEnd != endptr)
				ERROR(err_syntax_newthread);
			GDBThreadSel_MoveAssign(&GDB_CurrentThread_general, &newThread);
		} else {
			goto unknown;
		}
#undef ISNAME
	}	break;

	case 'X': {
		vm_virt_t addr;
		size_t length, error;
		addr = (vm_virt_t)strtou(i, &i, 16);
		if (*i++ != ',')
			ERROR(err_syntax);
		length = strtou(i, &i, 16);
		if (*i++ != ':')
			ERROR(err_syntax);
		error = GDB_DecodeEscapedBinary(i, endptr);
		if (length != error)
			ERROR(err_syntax);
		error = GDB_WriteMemory(GDB_CurrentThread_general.ts_thread,
		                        (vm_virt_t)addr, i, length);
		if (error != 0)
			ERROR(err_EFAULT);
		goto send_ok;
	}	break;

	case 'z':
	case 'Z': {
		unsigned int type;
		unsigned int kind;
		vm_virt_t addr;
		errno_t error;
		if (!(*i >= '0' && *i <= '4'))
			ERROR(err_syntax);
		type = (unsigned int)(*i++ - '0');
		if (*i++ != ',')
			ERROR(err_syntax);
		addr = (vm_virt_t)strtou(i, &i, 16);
		if (*i++ != ',')
			ERROR(err_syntax);
		kind = (unsigned int)strtoul(i, &i, 16);
		if (i != endptr)
			ERROR(err_syntax);
		error = GDBRemote_CommandBuffer[0] == 'Z'
		        ? GDB_AddBreak(GDB_CurrentThread_general.ts_thread, type, addr, kind)
		        : GDB_DelBreak(GDB_CurrentThread_general.ts_thread, type, addr, kind);
		if (error == EOK)
			goto send_ok;
		if (error == ENOSYS || error == ENOMEM)
			goto send_empty; /* Respond empty if adding a breakpoint failed, or the system isn't supported. */
		o = GDB_EncodeError(o, error);
	}	break;

	default:
unknown:
		/* Unknown command packet */
		printk(KERN_WARNING "[gdb] Unknown command: %$q\n",
		       (size_t)(endptr - GDBRemote_CommandBuffer),
		       GDBRemote_CommandBuffer);
		break;
	}
err_breakpoint_not_supported:
	/* Don't give any response when setting a breakpoint fails,
	 * thus acting like we simply don't supporting breakpoints. */
do_transmit:
	if (!GDBPacket_Transmit(o))
		return GDB_HANDLECOMMAND_DTCH;
	return GDB_HANDLECOMMAND_CONT;
err_unknown_register:
	printk(KERN_WARNING "[gdb] Unknown register accessed by packet: %$q\n",
	       (size_t)(endptr - GDBRemote_CommandBuffer), GDBRemote_CommandBuffer);
/*err_EPERM:*/
	o = GDB_EncodeError(o, EPERM);
	goto do_transmit;
err_invalid_register_size:
	printk(KERN_WARNING "[gdb] Invalid register size used by packet: %$q\n",
	       (size_t)(endptr - GDBRemote_CommandBuffer), GDBRemote_CommandBuffer);
/*err_ERANGE:*/
err_qXfer_syntax:
	o = GDB_EncodeError(o, ERANGE);
	goto do_transmit;
	printk(KERN_WARNING "[gdb] Syntax error in qXfer packet: %$q\n",
	       (size_t)(endptr - GDBRemote_CommandBuffer), GDBRemote_CommandBuffer);
/*err_EOK:*/
	o = GDB_EncodeError(o, 0);
	goto do_transmit;
err_syntax_newthread:
	if (newThread.ts_thread)
		GDBThreadSel_Fini(&newThread);
err_syntax:
	printk(KERN_ERR "[gdb] Syntax error in: %$q\n",
	       (size_t)(endptr - GDBRemote_CommandBuffer),
	       GDBRemote_CommandBuffer);
/*err_EINVAL:*/
	o = GDB_EncodeError(o, EINVAL);
	goto do_transmit;
err_ESRCH:
	o = GDB_EncodeError(o, ESRCH);
	goto do_transmit;
err_EFAULT:
	o = GDB_EncodeError(o, EFAULT);
	goto do_transmit;
err_MSGSIZE:
	printk(KERN_WARNING "[gdb] Buffer required by packet is too large: %$q\n",
	       (size_t)(endptr - GDBRemote_CommandBuffer), GDBRemote_CommandBuffer);
	o = GDB_EncodeError(o, EMSGSIZE);
	goto do_transmit;
}









PRIVATE char const ack[]  = { '+' };
PRIVATE char const nack[] = { '-' };

/* The main GDB function
 * This function is called from the GDB host thread once locking is done. */
INTERN void NOTHROW(FCALL GDB_Main)(void) {
	char *endptr;
	struct exception_info saved_exceptions;
	GDBThreadStopEvent *notif;
	assert(PREEMPTION_ENABLED());
	memcpy(&saved_exceptions, error_info(), sizeof(saved_exceptions));
again:
	/* Determine the initial current thread. */
	GDB_CurrentThread_general.ts_mode = GDBTHREADSEL_MODE_SINGLE;
	if (GDBServer_Host != GDBServer_FallbackHost) {
		GDB_CurrentThread_general.ts_thread = incref(GDBServer_Host);
	} else {
		GDBThreadStopEvent *notif;
		/* Use the first pending stop notification, or stopped thread */
		notif = ATOMIC_READ(GDBThread_AsyncNotifStopEvents);
		if (!notif)
			notif = ATOMIC_READ(GDBThread_Stopped);
		if (notif) {
			while (notif->tse_next)
				notif = notif->tse_next;
			GDB_CurrentThread_general.ts_thread = incref(notif->tse_thread);
		} else {
			/* If nothing is stopped, default to /bin/init */
			GDB_CurrentThread_general.ts_thread = incref(&_boottask);
		}
	}
	if (!(GDBServer_Features & GDB_SERVER_FEATURE_SHOWKERNEL) &&
	    GDBThread_IsKernelThread(GDB_CurrentThread_general.ts_thread)) {
		decref_unlikely(GDB_CurrentThread_general.ts_thread);
		GDB_CurrentThread_general.ts_thread = NULL;
		/* Must select a thread that isn't apart of the kernel. */
		{
			GDBThreadStopEvent *notif;
			notif = ATOMIC_READ(GDBThread_AsyncNotifStopEvents);
			if (!notif)
				notif = ATOMIC_READ(GDBThread_Stopped);
			/* Try to use the oldest non-kernel thread from stop notifications. */
			for (; notif; notif = notif->tse_next) {
				if (!GDBThread_IsKernelThread(notif->tse_thread))
					GDB_CurrentThread_general.ts_thread = notif->tse_thread;
			}
		}
		/* Fallback: Just use /bin/init */
		if (!GDB_CurrentThread_general.ts_thread)
			GDB_CurrentThread_general.ts_thread = &_boottask;
		incref(GDB_CurrentThread_general.ts_thread);
	}
	GDB_CurrentThread_continue = GDB_CurrentThread_general;
	incref(GDB_CurrentThread_continue.ts_thread);
	if (GDBServer_Features & GDB_SERVER_FEATURE_ATTACHED) {
		/* Transmit the initial stop notification/stop reason, if the exchange
		 * was instigated by the kernel (or, in the case of non-stop mode: if
		 * there are any pending stop notifications, send the next one) */
do_capture_notif:
		notif = GDBThread_ConsumeAsyncNotifEvent();
		if (notif) {
			char *buf;
do_process_notif:
			buf = GDBPacket_Start();
			if (GDBServer_Features & GDB_SERVER_FEATURE_NONSTOP) {
				/* Use an ASYNC notification. */
				buf = STPCAT(buf, "Stop:");
				buf = GDB_ConstructStopReply(buf, notif);
				GDBPacket_TransmitNotification(buf);
				GDBServer_DidSendAsyncStopNotification = true;
			} else {
				buf = GDB_ConstructStopReply(buf, notif);
				if (!GDBPacket_Transmit(buf))
					goto do_detach;
			}
		} else if (!(GDBServer_Features & GDB_SERVER_FEATURE_NONSTOP)) {
			/* Make sure that everything is stopped. */
			GDBThread_StopAllCpus();
			if (GDBServer_CreateMissingAsyncStopNotificationForSomeThread())
				goto do_capture_notif;
		}
	}

	/* The GDB main loop */
	for (;;) {
		byte_t b;
next_packet:
		assert(!task_isconnected());
		assert(PREEMPTION_ENABLED());
		if (((GDBServer_Features &
		      (GDB_SERVER_FEATURE_ATTACHED | GDB_SERVER_FEATURE_NONSTOP)) ==
		     (GDB_SERVER_FEATURE_ATTACHED | GDB_SERVER_FEATURE_NONSTOP)) &&
		    !GDBServer_DidSendAsyncStopNotification) {
			int bi;
check_for_notif_or_remote_byte:
			assert(!task_isconnected());
			/* In non-stop mode, we must wait for both:
			 *  - The GDB remote to send us something
			 *  - A new async stop notification to arrive (which we would have)
			 * For more information, see `https://sourceware.org/gdb/onlinedocs/gdb/Notification-Packets.html#Notification-Packets'
			 * But as TLDR: we can send async notifications whenever we want, but:
			 *   - We can only send 1 notification at a time (though are allowed to re-send that one multiple times)
			 *   - GDB can acknowledge having received that notification with `vStopped', until the point
			 *     when `vStopped' will return `OK', which then re-enables us to send future notifications.
			 */
			notif = GDBThread_ConsumeAsyncNotifEvent();
			if (notif)
				goto do_process_notif;
			bi = GDBRemote_TryGetByte();
			if (bi < 0) {
				/* No incoming data, nor outgoing notification packets.
				 * -> connect to both signals, and wait for either one. */
				task_connect(&GDBThread_AsyncNotifStopEventsAdded);
				task_connect(&GDBServer_RemoteDataAvailable);
				/* Re-try the checks above, now that we've become interlocked. */
				notif = GDBThread_ConsumeAsyncNotifEvent();
				if unlikely(notif) {
					task_disconnectall();
					goto do_process_notif;
				}
				bi = GDBRemote_TryGetByte();
				if likely(bi < 0) {
					/* Wait for something to happen. */
					if (!task_waitfor_norpc_nx(NULL))
						task_disconnectall();
					goto check_for_notif_or_remote_byte;
				}
				task_disconnectall();
			}
			b = (byte_t)bi;
		} else {
			/* In all-stop mode, there are no async notifications, so we only
			 * ever have to wait for the GDB remote to send over commands. */
			b = GDBRemote_GetByte();
		}
		if (b == 3) {
			/* Remote interrupt request */
			printk(KERN_INFO "[gdb] Interrupt request\n");
			GDBThread_StopAllCpus();
			continue;
		}
		if (b != '$') {
			printk(KERN_WARNING "[gdb] Unrecognized out-of-band byte: %Q (0x%.2I8x)\n", b, b);
			if (b == '+' || b == '-') {
				ATOMIC_FETCHAND(GDBServer_Features, ~GDB_SERVER_FEATURE_NOACK);
			}
			continue;
		}
		endptr = GDBRemote_CommandBuffer;
		for (;;) {
			int bi;
			bi = GDBRemote_TimedGetByte();
			if (bi < 0)
				goto err_timeout_during_packet_receive;
			if (bi == '#') {
				unsigned int action;
				byte_t checksum, expected_checksum;
				*endptr = 0;
				expected_checksum = GDBPacket_GetCheckSum(GDBRemote_CommandBuffer,
				                                          (size_t)(endptr - GDBRemote_CommandBuffer));
				bi = GDBRemote_TimedGetByte();
				if unlikely(bi < 0)
					goto err_timeout_during_packet_receive;
				checksum = (byte_t)GDB_FromHex((u8)bi) << 4;
				bi = GDBRemote_TimedGetByte();
				if unlikely(bi < 0)
					goto err_timeout_during_packet_receive;
				checksum |= (byte_t)GDB_FromHex((u8)bi);
				if (checksum != expected_checksum) {
					printk(KERN_ERR "[gdb] Checksum missmatch (remote(%#I8x) != local(%#I8x)) on packet \"%#$q[...]\"\n",
					       checksum, expected_checksum,
					       (size_t)(endptr - GDBRemote_CommandBuffer),
					       GDBRemote_CommandBuffer);
send_nack_and_wait_for_next_packet:
					if (!(GDBServer_Features & GDB_SERVER_FEATURE_NOACK))
						GDBRemote_PutData(nack, sizeof(nack));
					goto next_packet;
				}
				/* Always send ACK when having received a valid packet. */
				if (!(GDBServer_Features & GDB_SERVER_FEATURE_NOACK))
					GDBRemote_PutData(ack, sizeof(ack));
				/* Actually handle the command. */
				GDB_DEBUG("[gdb] command:%$q\n",
				          (size_t)(endptr - GDBRemote_CommandBuffer),
				          GDBRemote_CommandBuffer);
				action = GDB_HandleCommand(endptr);
				if (action == GDB_HANDLECOMMAND_CONT)
					goto next_packet;
				if (action == GDB_HANDLECOMMAND_EXIT) {
					/* If our hosting thread is no longer stopped, then resume execution. */
					if (!GDBThread_IsStoppedExplicitly(GDBServer_Host))
						goto done;
					/* If we are the fallback host, also exit the active GDB loop, so-as
					 * to give future async threads a chance to become hosts themself. */
					if (GDBServer_Host == GDBServer_FallbackHost)
						goto done;
					/* We ourself are one of the async-suspended threads,
					 * however GDB doesn't actually want us to resume execution.
					 * With this in mind, keep on being the host, and wait for either:
					 *  - New stop notifications (which we can then tell GDB about)
					 *  - GDB to send more data (which we can then immediatly process to process)
					 */
					GDBThreadSel_Fini(&GDB_CurrentThread_general);
					GDBThreadSel_Fini(&GDB_CurrentThread_continue);
					for (;;) {
						/* Wait for more pending stop notifications / a response from the GDB remote. */
						if (ATOMIC_READ(GDBThread_AsyncNotifStopEvents) != NULL ||
						    GDBRemote_HasPendingBytes())
							goto again;
						task_connect(&GDBThread_AsyncNotifStopEventsAdded);
						task_connect(&GDBServer_RemoteDataAvailable);
						if (ATOMIC_READ(GDBThread_AsyncNotifStopEvents) != NULL ||
						    GDBRemote_HasPendingBytes()) {
							task_disconnectall();
							goto again;
						}
						if (!task_waitfor_norpc_nx(NULL))
							task_disconnectall();
					}
				}
				goto do_detach;
			}
			if (bi == '}') {
				/* Escaped the next byte. */
				if unlikely(endptr >= COMPILER_ENDOF(GDBRemote_CommandBuffer) - 2)
					goto err_command_length_overflow_escape;
				*endptr++ = (char)(byte_t)bi;
				bi = GDBRemote_TimedGetByte();
				if unlikely(bi < 0)
					goto err_timeout_during_packet_receive;
				*endptr++ = (char)(byte_t)bi;
				continue;
			}
			if unlikely(endptr >= COMPILER_ENDOF(GDBRemote_CommandBuffer) - 1) {
				/* Command packet too large. */
/*err_command_length_overflow:*/
				/* Wait until the command packet has terminated. */
				for (;;) {
					bi = GDBRemote_TimedGetByte();
					if unlikely(bi < 0)
						goto err_timeout_during_packet_receive;
					if (bi == '#') {
						if unlikely(GDBRemote_TimedGetByte() < 0)
							goto err_timeout_during_packet_receive;
						if unlikely(GDBRemote_TimedGetByte() < 0)
							goto err_timeout_during_packet_receive;
						break;
					}
					if (bi == '}') {
err_command_length_overflow_escape:
						bi = GDBRemote_TimedGetByte();
						if unlikely(bi < 0)
							goto err_timeout_during_packet_receive;
					}
				}
				printk(KERN_ERR "[gdb] Command packet \"%#$q[...]\" is too large\n",
				       CONFIG_GDBSERVER_PACKET_MAXLEN, GDBRemote_CommandBuffer);
				goto send_nack_and_wait_for_next_packet;
			}
			*endptr++ = (char)(byte_t)bi;
		} /* packet receive loop */
	} /* oob receive loop */
done:
	GDB_DEBUG("[gdb] Exiting GDB_Main()\n");
	if likely(GDB_CurrentThread_general.ts_thread) {
		GDBThreadSel_Fini(&GDB_CurrentThread_general);
		GDB_CurrentThread_general.ts_thread = NULL;
	}
	if likely(GDB_CurrentThread_continue.ts_thread) {
		GDBThreadSel_Fini(&GDB_CurrentThread_continue);
		GDB_CurrentThread_continue.ts_thread = NULL;
	}
	memcpy(error_info(), &saved_exceptions, sizeof(saved_exceptions));
	return;
err_timeout_during_packet_receive:
	printk(KERN_ERR "[gdb] Timeout while receiving packet %$q (assume detached)\n",
	       (size_t)(endptr - GDBRemote_CommandBuffer), GDBRemote_CommandBuffer);
do_detach:
	/* Remove all breakpoints. */
	GDB_RemoveAllBreakpoints();
	/* Set the remote-state as detached. */
	GDBServer_SetRemoteDetached();
	/* Discard all pending async notifications. */
	GDBThread_DiscardAllAsyncNotifEvents();
	/* Resume execution of all stopped threads (including
	 * those that had pending stop notifications). */
	GDBThread_ResumeEverything();
	goto done;
}



DECL_END

#endif /* !GUARD_MODGDBSERVER_SERVER_C */
