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
#ifndef GUARD_MODGDB_GDB_C
#define GUARD_MODGDB_GDB_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "gdb.h"

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/driver-callbacks.h>
#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>
#include <hybrid/unaligned.h>

#include <kos/kernel/paging.h>

#include <assert.h>
#include <errno.h>
#include <format-printer.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#if !defined(__x86_64__) && defined(__i386__)
#include <kernel/gdt.h>
#endif

DECL_BEGIN


INTERN u32 GDB_RemoteFeatures = 0; /* Set of `GDB_REMOTEFEATURE_*' */

/* Signal broadcast when a GDB remote has been attacked for the first time. */
PRIVATE struct sig GDBRemote_AttachedChanged = SIG_INIT;

LOCAL void NOTHROW(FCALL GDBRemote_SetAttached)(void) {
	if (!(GDB_RemoteFeatures & GDB_REMOTEFEATURE_ATTACHED)) {
		if (!(ATOMIC_FETCHOR(GDB_RemoteFeatures,
		                     GDB_REMOTEFEATURE_ATTACHED) &
		      GDB_REMOTEFEATURE_ATTACHED)) {
			GDB_DEBUG("[gdb] Mark as attached\n");
			sig_broadcast(&GDBRemote_AttachedChanged);
		}
	}
}
LOCAL void NOTHROW(FCALL GDBRemote_SetDetached)(void) {
	if (ATOMIC_FETCHAND(GDB_RemoteFeatures,
	                    ~GDB_REMOTEFEATURE_ATTACHED) &
	    GDB_REMOTEFEATURE_ATTACHED) {
		GDB_DEBUG("[gdb] Mark as detached\n");
		sig_broadcast(&GDBRemote_AttachedChanged);
	}
}




PRIVATE char *
NOTHROW(FCALL GDB_EncodeHex)(char *ptr, void const *data, size_t datalen) {
	size_t i;
	for (i = 0; i < datalen; ++i) {
		byte_t b = ((byte_t *)data)[i];
		*ptr++ = tohex(b >> 4);
		*ptr++ = tohex(b & 0xf);
	}
	return ptr;
}

PRIVATE char *
NOTHROW(FCALL GDB_DecodeHex)(char const *ptr, void *data, size_t datalen) {
	size_t i;
	for (i = 0; i < datalen; ++i) {
		byte_t b;
		b  = fromhex(*ptr++) << 4;
		b |= fromhex(*ptr++);
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
		*dst++ = tohex(b >> 4);
		*dst++ = tohex(b & 0xf);
	}
	*(char **)arg = dst;
	return (ssize_t)datalen;
}

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



#define STPCAT(buf, str) ((char *)mempcpy(buf, str, COMPILER_STRLEN(str) * sizeof(char)))

#ifdef __x86_64__
#define REASON_REGISTER_MAXSIZE 8
#define FOREACH_REASON_REGISTER(callback)  \
	callback("4", GDB_REGISTER_X86_64_RSP) \
	callback("5", GDB_REGISTER_X86_64_RBP) \
	callback("10", GDB_REGISTER_X86_64_RIP)
#elif defined(__i386__)
#define REASON_REGISTER_MAXSIZE 4
#define FOREACH_REASON_REGISTER(callback) \
	callback("5", GDB_REGISTER_I386_EBP)  \
	callback("4", GDB_REGISTER_I386_ESP)  \
	callback("8", GDB_REGISTER_I386_EIP)
#endif


/* Inform the remote GDB client that KOS has been interrupted
 * This function is called when the remote GDB client sends an
 * interrupt to us, as well as when KOS itself causes a breakpoint
 * to be triggered, or manages to get into a PANIC situation. */
PRIVATE char *NOTHROW(FCALL GDB_ConstructStopReply)(char *ptr) {
	struct task *thread;
	thread = GDB_GetCurrentThread();
	*ptr++ = 'T';
	*ptr++ = tohex((GDBReason_TrapNo >> 4) & 0xf);
	*ptr++ = tohex(GDBReason_TrapNo & 0xf);
	/* Always include a select number of registers in the response. */
#ifdef FOREACH_REASON_REGISTER
#ifndef REASON_REGISTER_MAXSIZE
#define REASON_REGISTER_MAXSIZE GDB_REGISTER_MAXSIZE
#endif /* !REASON_REGISTER_MAXSIZE */
	{
		size_t reglen;
		byte_t regbuf[REASON_REGISTER_MAXSIZE];
#define ENCODE_GENERIC_REGISTER(hex, regno)                      \
		ptr    = STPCAT(ptr, hex);                               \
		*ptr++ = ':';                                            \
		reglen = GDB_GetRegister(regno, regbuf, sizeof(regbuf)); \
		ptr    = GDB_EncodeHex(ptr, regbuf, reglen);             \
		*ptr++ = ';';
		FOREACH_REASON_REGISTER(ENCODE_GENERIC_REGISTER)
#undef ENCODE_GENERIC_REGISTER
	}
#endif /* FOREACH_REASON_REGISTER */

	ptr    = STPCAT(ptr, "thread:");
	ptr    = GDB_EncodeThreadID(ptr, thread, true);
	*ptr++ = ';';
#ifndef CONFIG_NO_SMP
	ptr += sprintf(ptr, "core:%x;", thread->t_cpu->c_id);
#endif /* !CONFIG_NO_SMP */

	/* Include additional trap registers. */
	if (GDBReason_Registers) {
		ptr = stpcpy(ptr, GDBReason_Registers);
		/* Make sure that the register list is properly terminated.
		 * If it isn't, GDB will print an error, then hang itself. */
		if (ptr[-1] != ';')
			*ptr++ = ';';
	}
	return ptr;
}

PRIVATE bool NOTHROW(FCALL GDB_TransmitInterruptReason)(void) {
	char *ptr;
	ptr = GDBPacket_Start();
	ptr = GDB_ConstructStopReply(ptr);
	return GDBPacket_Transmit(ptr);
}

PRIVATE void NOTHROW(FCALL GDB_TransmitStopNotification)(void) {
	char *ptr;
	ptr = GDBPacket_Start();
	*ptr++ = 'S';
	*ptr++ = 't';
	*ptr++ = 'o';
	*ptr++ = 'p';
	*ptr++ = ':';
	ptr = GDB_ConstructStopReply(ptr);
	GDBPacket_TransmitNotification(ptr);
}



/* Buffer for incoming GDB command packets */
INTERN char GDBCommand_Buffer[GDB_PACKET_MAXLEN];


#define GDB_HANDLECOMMAND_OK                 0 /* Continue handling commands */
#define GDB_HANDLECOMMAND_RESUME             1 /* Resume execution */
#define GDB_HANDLECOMMAND_RESUME_NO_ATTACHED 2 /* Resume execution, but don't change the ATTACHED bit */
#define GDB_HANDLECOMMAND_ERROR              3 /* Error executing the command (Handled the same as `GDB_HANDLECOMMAND_OK') */
#define GDB_HANDLECOMMAND_UNKNOWN            4 /* Unknown packet */


PRIVATE REF struct task *GDB_ThreadForStepAndContinue = NULL;

/* Enumerator for `qsThreadInfo' and `qfThreadInfo' */
PRIVATE GDBEnumThreadsIterator GDB_IteratorFor_qfsThreadInfo = { 0, NULL };


PRIVATE bool
NOTHROW(FCALL GDB_ThreadForStepAndContinue_SetPCAndSingleStep)(void *pc,
                                                               bool single_step_enabled) {
	if (GDB_ThreadForStepAndContinue) {
		REF struct task *oldme;
		oldme = incref(GDB_GetCurrentThread());
		if (GDB_SetCurrentThread(GDB_ThreadForStepAndContinue)) {
			GDB_SetRegister(GDB_REGISTER_PC, &pc, sizeof(pc));
			GDB_SetSingleStep(single_step_enabled);
			GDB_SetCurrentThread(oldme);
			decref_unlikely(oldme);
			return true;
		}
		decref_unlikely(oldme);
		return false;
	}
	GDB_SetRegister(GDB_REGISTER_PC, &pc, sizeof(pc));
	GDB_SetSingleStep(single_step_enabled);
	return true;
}

PRIVATE bool
NOTHROW(FCALL GDB_ThreadForStepAndContinue_SetSingleStep)(bool single_step_enabled) {
	if (GDB_ThreadForStepAndContinue) {
		REF struct task *oldme;
		oldme = incref(GDB_GetCurrentThread());
		if (GDB_SetCurrentThread(GDB_ThreadForStepAndContinue)) {
			GDB_SetSingleStep(single_step_enabled);
			GDB_SetCurrentThread(oldme);
			decref_unlikely(oldme);
			return true;
		}
		decref_unlikely(oldme);
		return false;
	}
	GDB_SetSingleStep(single_step_enabled);
	return true;
}

PRIVATE bool
NOTHROW(FCALL GDB_TerminateThread)(struct task *__restrict thread) {
	/* TODO: Schedule a synchronous RPC to throw an E_EXIT_THREAD
	 *       exception the next time this thread calls `task_serve()'
	 * NOTE: Must take special care when `thread' is the one that is
	 *       hosting us (aka `thread == THIS_TASK'). In this case, we
	 *       have to schedule the RPC as non-interrupting (and really
	 *       make sure that no RPCs get executed while we're inside of
	 *       GDB by finally adding a `TASK_FNORPC' flag that is always
	 *       set for the hosting thread) */
	return true;
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

PRIVATE u32
NOTHROW(FCALL GDB_GetThreadIdForRemote)(struct task *__restrict thread) {
	u32 result;
	if (GDB_RemoteFeatures & GDB_REMOTEFEATURE_MULTIPROCESS) {
		if (thread->t_flags & TASK_FKERNTHREAD) {
set_kernel_thread:
#ifdef HIGH_MEMORY_KERNEL
			result = (u32)((uintptr_t)thread - KERNEL_BASE);
#else  /* HIGH_MEMORY_KERNEL */
			result = (u32)(uintptr_t)thread;
#endif /* !HIGH_MEMORY_KERNEL */
		} else {
			upid_t pid, tid;
			pid = task_getrootpid_of_s(thread);
			tid = task_getroottid_of_s(thread);
			if unlikely(!pid || !tid)
				goto set_kernel_thread; /* Shouldn't happen... */
			result = (u32)tid;
		}
	} else {
		goto set_kernel_thread;
	}
	return result;
}

#ifdef HAVE_GDB_DEBUG
#define ERROR(label)       do{ GDB_DEBUG("%s(%d) : Error : " #label "\n", __FILE__, __LINE__); goto label; }__WHILE0
#define ERRORF(label, ...) do{ GDB_DEBUG("%s(%d) : Error : " #label " : ", __FILE__, __LINE__); GDB_DEBUG(__VA_ARGS__); goto label; }__WHILE0
#else /* HAVE_GDB_DEBUG */
#define ERROR(label)       goto label
#define ERRORF(label, ...) goto label
#endif /* !HAVE_GDB_DEBUG */


/* Check if the hosting thread is the given `thread', or when `thread' is a
 * process leader, check if the hosting thread is apart of its process. */
PRIVATE bool
NOTHROW(FCALL GDB_IsHostApartOf)(struct task *__restrict thread) {
	struct task *me = THIS_TASK;
	if (thread == me)
		return true;
	if (task_getprocess_of(me) == thread)
		return true;
	if (thread == &_bootidle) {
		if (me->t_flags & TASK_FKERNTHREAD)
			return true;
		if (me == &_boottask && !(GDB_RemoteFeatures & GDB_REMOTEFEATURE_ATTACHED))
			return true; /* Special case: Before GDB is attached, the boot task is considered apart of the kernel! */
	}
	return false;
}



/* Handle a given GDB command
 * @return: * : One of `GDB_HANDLECOMMAND_*' */
PRIVATE unsigned int NOTHROW(FCALL GDB_HandleCommand)(char *endptr) {
	char command, *p = GDBCommand_Buffer;
	command = *p++;
	switch (command) {

	case '!':
		/* Extended mode (would allow GDB to restart the application being debugged)
		 * However, since we can't very well restart the kernel, don't do anything to
		 * let GDB think that this function isn't supported (but don't log a warning
		 * about this) */
		goto send_ok;

	case '?':
		if unlikely(!GDB_TransmitInterruptReason())
			ERROR(gdb_exit);
		break;

	case 'B': {
		void *addr;
		errno_t error;
		/* Old-style breakpoint packet */
		addr = STRTOADDR(p, &p, 16);
		if (*p++ != ',')
			ERROR(err_syntax);
		if (p != endptr - 1)
			ERROR(err_syntax);
		if (*p == 'S') {
			error = GDB_AddBreak(GDB_BREAKPOINT_TYPE_SWBREAK, addr, 0);
		} else if (*p == 'C') {
			error = GDB_DelBreak(GDB_BREAKPOINT_TYPE_SWBREAK, addr, 0);
		} else {
			ERROR(err_syntax);
		}
		if (error == ENOSYS || error == ENOMEM)
			ERROR(err_breakpoint_not_supported); /* Not supported */
		if (error != EOK) {
			if (!GDBPacket_SendError((u8)error))
				ERROR(gdb_exit);
			break;
		}
send_ok:
		if (!GDBPacket_Send("OK"))
			ERROR(gdb_exit);
	}	break;

	case 'c': {
		if (p != endptr) {
			void *addr;
parse_pc_and_resume_nostep:
			addr = STRTOADDR(p, &p, 16);
			if (p != endptr)
				ERROR(err_syntax);
			GDB_ThreadForStepAndContinue_SetPCAndSingleStep(addr, false);
		} else {
resume_nostep:
			GDB_ThreadForStepAndContinue_SetSingleStep(false);
		}
resume_if_host_is_step_or_continue:
		if (GDB_IsHostApartOf(GDB_ThreadForStepAndContinue ? GDB_ThreadForStepAndContinue
		                                                   : GDB_GetCurrentThread()))
			return GDB_HANDLECOMMAND_RESUME;
	}	break;

	case 'C': {
		strtoul(p, &p, 16); /* Signal number to continue with??? */
		if (p != endptr) {
			if (*p++ != ';')
				ERROR(err_syntax);
			goto parse_pc_and_resume_nostep;
		}
		goto resume_nostep;
	}	break;

	case 'd': /* Toggle debugging??? */
		goto send_empty;

	case 'D': {
		if (p != endptr) {
			if (*p++ != ';')
				ERROR(err_syntax);
			strtoul(p, &p, 16); /* PID */
			if (p != endptr)
				ERROR(err_syntax);
			/* Detach form pid is implemented as a no-op
			 * We only support detaching the  */
			goto send_ok;
		}
		/* Detach */
		GDB_RemoveAllBreakpoints();
		GDBRemote_SetDetached();
		if (!GDBPacket_Send("OK"))
			ERROR(gdb_exit);
		return GDB_HANDLECOMMAND_RESUME_NO_ATTACHED;
	}	break;

	case 'g': {
		struct gdb_cpustate st;
		char *dst;
		GDB_GetRegisters(&st);
		dst = GDBPacket_Start();
		dst = GDB_EncodeHex(dst, &st, sizeof(st));
		if (!GDBPacket_Transmit(dst))
			ERROR(gdb_exit);
	}	break;

	case 'G': {
		struct gdb_cpustate st;
		p = GDB_DecodeHex(p, &st, sizeof(st));
		if (p != endptr)
			ERROR(err_syntax);
		GDB_SetRegisters(&st);
		goto send_ok;
	}	break;

	case 'H': {
		char op = *p++;
		REF struct task *thread;
		if (op != 'c' && op != 'g')
			ERROR(err_syntax);
		thread = GDB_DecodeThreadID(&p, true);
		if unlikely(!thread)
			ERROR(err_unknown_thread);
		if (p != endptr) {
			decref_unlikely(thread);
			ERROR(err_syntax);
		}
		if (op == 'c') {
			xdecref(GDB_ThreadForStepAndContinue);
			GDB_ThreadForStepAndContinue = thread; /* Inherit reference */
		} else {
			bool set_ok;
			set_ok = GDB_SetCurrentThread(thread);
			decref_unlikely(thread);
			if (!set_ok)
				ERROR(err_unknown_thread);
		}
		goto send_ok;
	}	break;

	case 'i':
	case 's': {
		if (p != endptr) {
			void *addr;
		parse_pc_and_resume_dostep:
			addr = STRTOADDR(p, &p, 16);
#if 0 /* i [addr[,nnn]] -- nnn can be given to specify how often to step before breaking again. \
       * TODO: Maybe add support for this? */
			if (p != endptr)
				ERROR(err_syntax);
#endif
			GDB_ThreadForStepAndContinue_SetPCAndSingleStep(addr, true);
		} else {
resume_dostep:
			GDB_ThreadForStepAndContinue_SetSingleStep(true);
		}
		goto resume_if_host_is_step_or_continue;
	}	break;

	case 'I':
	case 'S': {
		strtoul(p, &p, 16); /* Signal number to continue with??? */
		if (p != endptr) {
			if (*p++ != ';')
				ERROR(err_syntax);
			goto parse_pc_and_resume_dostep;
		}
		goto resume_dostep;
	}	break;

	case 'k': {
		if (p != endptr)
			ERROR(err_syntax);
		GDB_KillKernel();
	}	break;

	case 'm': {
		void *addr;
		size_t length, error, i;
		char *dst;
		addr = STRTOADDR(p, &p, 16);
		if (*p++ != ',')
			ERROR(err_syntax);
		length = STRTOSIZE(p, &p, 16);
		if (p != endptr)
			ERROR(err_syntax);
		if unlikely(length > GDB_PACKET_MAXLEN / 2)
			ERROR(err_buffer_too_large);
		dst   = GDBPacket_Start();
		error = GDB_ReadMemoryWithoutSwBreak((vm_virt_t)addr, dst, length, true);
		if (error != 0)
			ERROR(err_faulty_memory);
		/* Encode memory as hex. */
		i = length;
		while (i--) {
			byte_t b         = ((byte_t *)dst)[i];
			dst[(i * 2) + 0] = tohex(b >> 4);
			dst[(i * 2) + 1] = tohex(b & 0xf);
		}
		if (!GDBPacket_Transmit(dst + length * 2))
			ERROR(gdb_exit);
	}	break;

	case 'M': {
		void *addr;
		size_t length, error, i;
		addr = STRTOADDR(p, &p, 16);
		if (*p++ != ',')
			ERROR(err_syntax);
		length = STRTOSIZE(p, &p, 16);
		if (*p++ != ':')
			ERROR(err_syntax);
		if ((p + (length * 2)) != endptr)
			ERROR(err_syntax);
		/* Decode memory from hex. */
		for (i = 0; i < length; ++i) {
			byte_t b;
			b  = fromhex(p[(i * 2) + 0]) << 4;
			b |= fromhex(p[(i * 2) + 1]);
			p[i] = b;
		}
		error = GDB_WriteMemoryWithoutSwBreak((vm_virt_t)addr, p, length, true);
		if (error != 0)
			ERROR(err_faulty_memory);
		goto send_ok;
	}	break;

	case 'p': {
		uintptr_t regno;
		size_t reqlen;
		byte_t regbuf[GDB_REGISTER_MAXSIZE];
		char *dst;
		regno = (uintptr_t)strtoul(p, &p, 16);
		if (p != endptr)
			ERROR(err_syntax);
		reqlen = GDB_GetRegister(regno, regbuf, sizeof(regbuf));
		if (!reqlen)
			ERROR(err_unknown_register);
		dst = GDBPacket_Start();
		dst = GDB_EncodeHex(dst, regbuf, reqlen);
		if (!GDBPacket_Transmit(dst))
			ERROR(gdb_exit);
	}	break;

	case 'P': {
		uintptr_t regno;
		size_t reqlen, reglen;
		byte_t regbuf[GDB_REGISTER_MAXSIZE];
		regno = (uintptr_t)strtoul(p, &p, 16);
		if (*p++ != '=')
			ERROR(err_syntax);
		if (p >= endptr)
			ERROR(err_syntax); /* Buffer too small */
		if ((p + (2 * GDB_REGISTER_MAXSIZE)) < endptr)
			ERROR(err_syntax); /* Buffer too large */
		if ((size_t)(endptr - p) & 1)
			ERROR(err_syntax); /* Dangling digit */
		reglen = (size_t)(endptr - p) / 2;
		GDB_DecodeHex(p, regbuf, reglen);
		reqlen = GDB_SetRegister(regno, regbuf, reglen);
		if (!reqlen)
			ERROR(err_unknown_register);
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
			GDB_SetRegister(regno, regbuf, reqlen);
		}
		goto send_ok;
	}	break;


	case 't': {
		void *addr;
		u32 pattern, mask;
		addr = STRTOADDR(p, &p, 16);
		if (*p++ != ':')
			ERROR(err_syntax);
		pattern = (u32)strtoul(p, &p, 16);
		if (*p++ != ',')
			ERROR(err_syntax);
		mask = (u32)strtoul(p, &p, 16);
		if (p != endptr)
			ERROR(err_syntax);
		/* Really weird packet, but easy enough to implement... */
		for (;;) {
			uintptr_t pagebase, search_size;
			pagebase    = ((uintptr_t)addr - 3) & ~(pagedir_pagesize() - 1);
			search_size = ((uintptr_t)addr - pagebase) + 3;
			if (GDB_ReadMemoryWithoutSwBreak((vm_virt_t)pagebase, GDBCommand_Buffer, search_size, true))
				ERROR(err_faulty_memory);
			while (search_size--) {
				u32 value;
				value = UNALIGNED_GET32((u32 *)(GDBCommand_Buffer + search_size));
				if ((value & mask) != pattern)
					continue; /* Different value... */
				/* The docs don't say how to respond, but try to mirror `qSearch:memory' */
				if (!GDBPacket_Sendf("1,%p", pagebase + search_size))
					ERROR(gdb_exit);
				goto done;
			}
		}
	}	break;

	case 'T': {
		REF struct task *thread;
		thread = GDB_DecodeThreadID(&p, true);
		if (p != endptr) {
			xdecref_unlikely(thread);
			ERROR(err_syntax);
		}
		if (!thread)
			ERROR(err_unknown_thread);
		decref_unlikely(thread);
		goto send_ok;
	}	break;

	case 'v': {
		char *nameEnd;
		size_t nameLen;
		nameEnd = p;
		for (;;) {
			char ch = *nameEnd;
			if (ch == ';' || ch == '?' || (!ch && nameEnd == endptr))
				break;
			++nameEnd;
		}
		nameLen = (size_t)(nameEnd - p);
#define ISNAME(name) (nameLen == COMPILER_STRLEN(name) && memcmp(p, name, COMPILER_STRLEN(name) * sizeof(char)) == 0)
		if (ISNAME("Attach") && *nameEnd == ';') {
			/* Attach/detach is ignored... */
			goto send_empty;
		} else if (ISNAME("Cont")) {
			bool someThreadWasAlive = false;
			bool didResumeHostThread = false;
			struct task *didSetStep = NULL;
			p = nameEnd;
			if (*p == '?') {
				if (p + 1 != endptr)
					ERROR(err_syntax);
				if (!GDBPacket_Send("vCont;c;C;s;S;t;r"))
					ERROR(gdb_exit);
				break;
			}
			while (*p == ';') {
				char action;
				++p;
				action = *p++;
				switch (action) {

				case 'C':
				case 'S':
					strtoul(p, &p, 16); /* signo? */
					ATTR_FALLTHROUGH
				case 'c':
				case 's':
					if (*p == ':') {
						REF struct task *thread;
						++p;
						thread = GDB_DecodeThreadID(&p, true);
						if likely(thread) {
							if (thread != didSetStep) {
								REF struct task *oldThread;
								oldThread = incref(GDB_GetCurrentThread());
								if (GDB_SetCurrentThread(thread)) {
									if (action == 's' || action == 'S')
										didSetStep = thread;
									GDB_SetSingleStep(action == 's' || action == 'S');
									GDB_SetCurrentThread(oldThread);
									someThreadWasAlive = true;
								}
								if (GDB_IsHostApartOf(thread))
									didResumeHostThread = true;
								decref_unlikely(oldThread);
							}
							decref_unlikely(thread);
						}
					} else {
						struct task *thread;
						thread = GDB_ThreadForStepAndContinue ? GDB_ThreadForStepAndContinue
						                                      : GDB_GetCurrentThread();
						if (GDB_IsHostApartOf(thread))
							didResumeHostThread = true;
						if (thread != didSetStep) {
							if (action == 's' || action == 'S')
								didSetStep = thread;
							if (GDB_ThreadForStepAndContinue_SetSingleStep(action == 's' || action == 'S'))
								someThreadWasAlive = true;
						}
					}
					break;

				case 't': {
					if (*p == ':') {
						REF struct task *thread;
						++p;
						thread = GDB_DecodeThreadID(&p, true);
						if likely(thread) {
							if (GDB_TerminateThread(thread))
								someThreadWasAlive = true;
							decref_unlikely(thread);
						}
						if (GDB_IsHostApartOf(thread))
							didResumeHostThread = true;
					} else {
						struct task *thread;
						thread = GDB_ThreadForStepAndContinue
						         ? GDB_ThreadForStepAndContinue
						         : GDB_GetCurrentThread();
						if (GDB_IsHostApartOf(thread))
							didResumeHostThread = true;
						if (GDB_TerminateThread(thread))
							someThreadWasAlive = true;
					}
				}	break;

				case 'r': {
					void *start, *end;
					start = STRTOADDR(p, &p, 16);
					if (*p++ != ',')
						ERROR(err_syntax);
					end = STRTOADDR(p, &p, 16);
					if (*p == ':') {
						REF struct task *thread;
						++p;
						thread = GDB_DecodeThreadID(&p, true);
						if likely(thread) {
							REF struct task *oldThread;
							oldThread = incref(GDB_GetCurrentThread());
							if (GDB_SetCurrentThread(thread)) {
								GDB_SetSingleStep(true);
								GDB_SetSingleStepIgnoredRange(thread, start, end);
								GDB_SetCurrentThread(oldThread);
								someThreadWasAlive = true;
								didSetStep    = thread;
							}
							if (GDB_IsHostApartOf(thread))
								didResumeHostThread = true;
							decref_unlikely(oldThread);
							decref_unlikely(thread);
						}
					} else {
						if (GDB_ThreadForStepAndContinue_SetSingleStep(true)) {
							struct task *thread;
							thread = GDB_ThreadForStepAndContinue
							         ? GDB_ThreadForStepAndContinue
							         : GDB_GetCurrentThread();
							if (GDB_IsHostApartOf(thread))
								didResumeHostThread = true;
							GDB_SetSingleStepIgnoredRange(thread, start, end);
							someThreadWasAlive = true;
							didSetStep = thread;
						}
					}
				}	break;

				default:
					ERROR(err_syntax);
				}
			}
			if (p != endptr)
				ERROR(err_syntax);
			if (!someThreadWasAlive)
				ERROR(err_unknown_thread);
			if (GDB_Features & GDB_FEATURE_NONSTOP_MODE) {
				if unlikely(!GDBPacket_Send("OK"))
					ERROR(gdb_exit);
				if (didResumeHostThread)
					return GDB_HANDLECOMMAND_RESUME;
			} else {
				return GDB_HANDLECOMMAND_RESUME;
			}
		} else if (ISNAME("CtrlC")) {
			if (nameEnd != endptr)
				ERROR(err_syntax);
			/* Make sure that full-stop mode has been activated. */
			GDB_SuspendAllOtherCPUsNow();
			goto send_ok;
		} else if (ISNAME("Kill") && *nameEnd == ';') {
			pid_t pid;
			p   = nameEnd + 1;
			pid = strto32(p, &p, 16);
			if (pid == GDB_MULTIPROCESS_KERNEL_PID) {
				if (!GDBPacket_Send("OK"))
					ERROR(gdb_exit);
				GDB_KillKernel();
			} else {
				REF struct task *thread;
				bool term_ok;
				thread = GDB_GetProcessByPID((upid_t)pid);
				if unlikely(!thread)
					ERROR(err_unknown_thread);
				term_ok = GDB_TerminateThread(thread);
				decref_unlikely(thread);
				if unlikely(!term_ok)
					ERROR(err_unknown_thread);
				if (!GDBPacket_Send("OK"))
					ERROR(gdb_exit);
			}
		} else if (ISNAME("MustReplyEmpty")) {
			if (nameEnd != endptr)
				ERROR(err_syntax);
			/* Reply empty... */
send_empty:
			if (!GDBPacket_SendEmpty())
				ERROR(gdb_exit);
		} else if (ISNAME("Stopped")) {
#if 0
			if unlikely(!GDB_TransmitInterruptReason())
				ERROR(gdb_exit);
#else
			goto send_ok;
#endif
		} else {
			ERROR(err_unknown_command);
		}
#undef ISNAME
	}	break;

	case 'q': {
		char *nameEnd;
		size_t nameLen;
		nameEnd = p;
		for (;;) {
			char ch = *nameEnd;
			if (ch == ',' || ch == ':' || ch == ';' || (!ch && nameEnd == endptr))
				break;
			++nameEnd;
		}
		nameLen = (size_t)(nameEnd - p);
#define ISNAME(name) (nameLen == COMPILER_STRLEN(name) && memcmp(p, name, COMPILER_STRLEN(name) * sizeof(char)) == 0)
		if (ISNAME("C")) {
			char *dst;
			if (nameEnd != endptr)
				ERROR(err_syntax);
			dst    = GDBPacket_Start();
			*dst++ = 'Q';
			*dst++ = 'C';
			dst    = GDB_EncodeThreadID(dst, GDB_GetCurrentThread(), true);
			if (!GDBPacket_Transmit(dst))
				ERROR(gdb_exit);
		} else if (nameLen == 1 + COMPILER_STRLEN("ThreadInfo") &&
		           memcmp(p + 1, "ThreadInfo", COMPILER_STRLEN("ThreadInfo") * sizeof(char)) == 0 &&
		           (p[0] == 'f' || p[0] == 's')) {
			char *dst, action = p[0];
			REF struct task *thread;
			if (nameEnd != endptr)
				ERROR(err_syntax);
			if (action == 'f') {
				if (GDB_IteratorFor_qfsThreadInfo.eti_next)
					GDBEnumThreads_Fini(&GDB_IteratorFor_qfsThreadInfo);
				GDBEnumThreads_Init(&GDB_IteratorFor_qfsThreadInfo);
			}
			dst    = GDBPacket_Start();
			thread = GDBEnumThreads_Next(&GDB_IteratorFor_qfsThreadInfo);
			if (!thread)
				*dst++ = 'l';
			else {
				char *bufmax;
				bufmax = (dst + GDB_PACKET_MAXLEN) - (GDB_ENCODETHREADID_MAXCHARS + 1);
				*dst++ = 'm';
				dst = GDB_EncodeThreadID(dst, thread, true);
				decref_unlikely(thread);
				while (dst < bufmax) {
					thread = GDBEnumThreads_Next(&GDB_IteratorFor_qfsThreadInfo);
					if (!thread)
						break;
					*dst++ = ',';
					dst    = GDB_EncodeThreadID(dst, thread, true);
					decref_unlikely(thread);
				}
			}
			if (!GDBPacket_Transmit(dst))
				ERROR(gdb_exit);
#if 0 /* TODO */
		} else if (ISNAME("GetTLSAddr") && *nameEnd == ':') {
#endif
#if defined(__x86_64__) || defined(__i386__)
		} else if (ISNAME("GetTIBAddr") && *nameEnd == ':') {
			REF struct task *thread;
			uintptr_t addr;
			p      = nameEnd + 1;
			thread = GDB_DecodeThreadID(&p, true);
			if unlikely(p != endptr) {
				xdecref_unlikely(thread);
				ERROR(err_syntax);
			}
			if unlikely(!thread)
				ERROR(err_unknown_thread);
#ifdef __x86_64__
			{
				REF struct task *oldthread;
				oldthread = incref(GDB_GetCurrentThread());
				if unlikely(!GDB_SetCurrentThread(thread)) {
					decref_unlikely(oldthread);
					ERROR(err_unknown_thread);
				}
				GDB_GetRegister(GDB_REGISTER_X86_64_FSBASE, &addr, sizeof(addr));
				GDB_SetCurrentThread(oldthread);
				decref_unlikely(oldthread);
			}
#else /* __x86_64__ */
			addr = ATOMIC_READ(FORTASK(thread, x86_this_user_gsbase));
#endif /* !__x86_64__ */
			decref_unlikely(thread);
			if (!GDBPacket_Sendf("%p", addr))
				ERROR(gdb_exit);
#endif /* __x86_64__ || __i386__ */
		} else if (p[0] == 'L' && p + 12 == endptr && (p[1] == '0' || p[1] == '1')) {
			char *dst, *pcount; u8 count;
//			bool startflag = p[1] == '1';
			u8 maxCount = fromhex(p[2]) << 4 | fromhex(p[3]);
			u32 nextThread = (u32)fromhex(p[4]) << 28 | (u32)fromhex(p[5]) << 24 |
			                 (u32)fromhex(p[6]) << 20 | (u32)fromhex(p[7]) << 16 |
			                 (u32)fromhex(p[8]) << 12 | (u32)fromhex(p[9]) << 8 |
			                 (u32)fromhex(p[10]) << 4 | (u32)fromhex(p[11]);
			GDBEnumThreadsIterator iter;
			GDBEnumThreads_Init(&iter);
			while (nextThread--) {
				REF struct task *thread;
				thread = GDBEnumThreads_Next(&iter);
				if (!thread) {
					/* EOF */
					GDBEnumThreads_Fini(&iter);
					if (!GDBPacket_Sendf("qM001%.8I32x", nextThread))
						ERROR(gdb_exit);
					goto done;
				}
				decref_unlikely(thread);
			}
			dst = GDBPacket_Start();
			*dst++ = 'q';
			*dst++ = 'M';
			pcount = dst;
			dst += 3; /* Filled in later. */
			dst += sprintf(dst, "%.8I32x", nextThread);
			for (count = 0; count < maxCount; ++count) {
				REF struct task *thread;
				u32 threadid;
				thread = GDBEnumThreads_Next(&iter);
				if (!thread)
					break;
				threadid = GDB_GetThreadIdForRemote(thread);
				decref_unlikely(thread);
				dst += sprintf(dst, "%.8I32x", threadid);
			}
			pcount[0] = tohex(count >> 4);
			pcount[1] = tohex(count & 0xf);
			pcount[2] = iter.eti_next ? '0' : '1'; /* done-flag */
			GDBEnumThreads_Fini(&iter);
			if (!GDBPacket_Transmit(dst))
				ERROR(gdb_exit);
		} else if (p[0] == 'P' && p + 9 > endptr) {
			/* These macros are taken from the GDB source.
			 * `remote.c:remote_unpack_thread_info_response()' */
#define TAG_THREADID    0x01 /* Echo the thread identifier.  */
#define TAG_EXISTS      0x02 /* Is this process defined enough to fetch registers and its stack?  */
#define TAG_DISPLAY     0x04 /* A short thing maybe to put on a window */
#define TAG_THREADNAME  0x08 /* string, maps 1-to-1 with a thread is.  */
#define TAG_MOREDISPLAY 0x10 /* Whatever the kernel wants to say about the process.  */
			REF struct task *thread;
			char *dst;
			u32 mode = (u32)fromhex(p[1]) << 28 | (u32)fromhex(p[2]) << 24 |
			           (u32)fromhex(p[3]) << 20 | (u32)fromhex(p[4]) << 16 |
			           (u32)fromhex(p[5]) << 12 | (u32)fromhex(p[6]) << 8 |
			           (u32)fromhex(p[7]) << 4 | (u32)fromhex(p[8]);
			p += 9;
			thread = GDB_DecodeThreadID(&p, true);
			if (p != endptr) {
				xdecref_unlikely(thread);
				ERROR(err_syntax);
			}
			if unlikely(!thread)
				ERROR(err_unknown_thread);
			dst = GDBPacket_Start();
			mode &= 0x1f;
			*dst++ = 'q';
			*dst++ = 'M';
			dst += sprintf(dst, "%.8I32x", mode);
			dst += sprintf(dst, "%.8I32x", GDB_GetThreadIdForRemote(thread));
			if (mode & TAG_THREADID) {
				dst += sprintf(dst, "%.8I32x", TAG_THREADID);
				/* The GDB source asserts 16 for length this for some
				 * reason (even though only 8 bytes are processed) */
				dst += sprintf(dst, "%.8I32x", 16);
				dst += sprintf(dst, "%.8I32x", GDB_GetThreadIdForRemote(thread));
			}
			if (mode & TAG_EXISTS) {
				dst += sprintf(dst, "%.8I32x", TAG_EXISTS);
				dst += sprintf(dst, "%.8I32x", 8);
				dst += sprintf(dst, "%.8I32x", (thread->t_flags & (TASK_FTERMINATED | TASK_FTERMINATING)) ? 0 : 1);
			}
			if (mode & TAG_THREADNAME) {
				char *namebuf; ssize_t namelen;
				dst += sprintf(dst, "%.8I32x", TAG_THREADNAME);
				namebuf = dst + 8;
				namelen = GDBInfo_PrintThreadName(&format_sprintf_printer,
				                                  &namebuf, thread);
				if unlikely(namelen < 0) {
					decref_unlikely(thread);
					ERROR(err_unknown_thread);
				}
				sprintf(dst, "%.8I32x", namelen);
				dst = namebuf;
			}
			decref_unlikely(thread);
			if (!GDBPacket_Transmit(dst))
				ERROR(gdb_exit);
		} else if (ISNAME("NonStop")) {
			if (nameEnd != endptr)
				ERROR(err_syntax);
			if (!GDBPacket_Sendf("%x", GDB_DidSuspendOtherCPUs ? 0 : 1))
				ERROR(gdb_exit);
		} else if (ISNAME("Supported")) {
			char *dst;
			p = nameEnd;
			GDB_RemoteFeatures &= GDB_REMOTEFEATURE_ATTACHED;
			if (*p == ':') {
				++p;
				for (;;) {
					nameEnd = strchrnul(p, ';');
					nameLen = (size_t)(nameEnd - p);
					if (nameEnd[-1] == '+') {
						--nameLen;
						if (ISNAME("multiprocess"))
							/*GDB_RemoteFeatures |= GDB_REMOTEFEATURE_MULTIPROCESS*/;
						else if (ISNAME("swbreak"))
							GDB_RemoteFeatures |= GDB_REMOTEFEATURE_SWBREAK;
						else if (ISNAME("hwbreak"))
							GDB_RemoteFeatures |= GDB_REMOTEFEATURE_HWBREAK;
						else if (ISNAME("fork-events"))
							GDB_RemoteFeatures |= GDB_REMOTEFEATURE_FORK_EVENTS;
						else if (ISNAME("vfork-events"))
							GDB_RemoteFeatures |= GDB_REMOTEFEATURE_VFORK_EVENTS;
						else if (ISNAME("exec-events"))
							GDB_RemoteFeatures |= GDB_REMOTEFEATURE_EXEC_EVENTS;
					}
					p = nameEnd;
					if (*nameEnd != ';')
						break;
					++p;
				}
			}
			if (p != endptr)
				ERRORF(err_syntax, "p=%$q, %Iu\n", (size_t)(endptr - p), p, (size_t)(endptr - p));
			dst = GDBPacket_Start();
			dst += sprintf(dst, "PacketSize=%Ix", GDB_PACKET_MAXLEN + 4);
/*			dst = STPCAT(dst, ";QNonStop+"); // It's just not ready, yet... */
			dst = STPCAT(dst, ";QStartNoAckMode+");
			if (GDB_RemoteFeatures & GDB_REMOTEFEATURE_MULTIPROCESS)
				dst = STPCAT(dst, ";multiprocess+");
			if (GDB_RemoteFeatures & GDB_REMOTEFEATURE_SWBREAK)
				dst = STPCAT(dst, ";swbreak+");
			if (GDB_RemoteFeatures & GDB_REMOTEFEATURE_HWBREAK)
				dst = STPCAT(dst, ";hwbreak+");
			if (GDB_RemoteFeatures & GDB_REMOTEFEATURE_FORK_EVENTS)
				dst = STPCAT(dst, ";fork-events+");
			if (GDB_RemoteFeatures & GDB_REMOTEFEATURE_EXEC_EVENTS)
				dst = STPCAT(dst, ";exec-events+");
/*			dst = STPCAT(dst, ";QCatchSyscalls+"); // TODO */
/*			dst = STPCAT(dst, ";QThreadEvents+"); // TODO */
			dst = STPCAT(dst, ";QDisableRandomization+");
			dst = STPCAT(dst, ";qXfer:exec-file:read+");
/*			dst = STPCAT(dst, ";qXfer:features:read+"); // I don't really understand what this is good for (yet) */
			dst = STPCAT(dst, ";qXfer:libraries:read+");
			dst = STPCAT(dst, ";qXfer:threads:read+");
			dst = STPCAT(dst, ";qXfer:osdata:read+");
			dst = STPCAT(dst, ";vContSupported+");
			if (!GDBPacket_Transmit(dst))
				ERROR(gdb_exit);
		} else if (ISNAME("Symbol")) {
			if (nameEnd != endptr && *nameEnd != ':')
				ERROR(err_syntax);
			/* NOTE: Intentionally don't check the exact arguments, since those are variable. */
			goto send_ok;
		} else if (ISNAME("ThreadExtraInfo")) {
			REF struct task *thread;
			char *dst;
			p = nameEnd;
			if (*p++ != ',')
				ERROR(err_syntax);
			thread = GDB_DecodeThreadID(&p, true);
			if (p != endptr) {
				xdecref_unlikely(thread);
				ERROR(err_syntax);
			}
			if unlikely(!thread)
				ERROR(err_unknown_thread);
			dst = GDBPacket_Start();
			GDBInfo_PrintThreadName(&GDB_HexPrinter, &dst, thread);
			decref_unlikely(thread);
			if unlikely(!GDBPacket_Transmit(dst))
				ERROR(gdb_exit);
		} else if (ISNAME("Xfer")) {
			char *annex, *packetBuffer;
			ssize_t error;
			GDB_OffsetAndLengthPrinterData dst;
			bool isReadOperation = true;
			p = nameEnd;
			if (*p++ != ':')
				ERROR(err_qXfer_syntax);
			nameEnd = strchr(p, ':');
			if unlikely(!nameEnd)
				ERROR(err_qXfer_syntax);
			nameLen = (size_t)(nameEnd - p);
			++nameEnd;
			if (*nameEnd == 'r') {
				++nameEnd;
				if unlikely(*nameEnd++ != 'e') ERROR(err_qXfer_syntax);
				if unlikely(*nameEnd++ != 'a') ERROR(err_qXfer_syntax);
				if unlikely(*nameEnd++ != 'd') ERROR(err_qXfer_syntax);
			} else if (*nameEnd == 'w') {
				++nameEnd;
				if unlikely(*nameEnd++ != 'r') ERROR(err_qXfer_syntax);
				if unlikely(*nameEnd++ != 'i') ERROR(err_qXfer_syntax);
				if unlikely(*nameEnd++ != 't') ERROR(err_qXfer_syntax);
				if unlikely(*nameEnd++ != 'e') ERROR(err_qXfer_syntax);
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
			dst.ol_offset = STRTOSIZE(nameEnd, &nameEnd, 16);
			if unlikely(*nameEnd++ != ',') ERROR(err_qXfer_syntax);
			dst.ol_size = STRTOSIZE(nameEnd, &nameEnd, 16);
			if unlikely(nameEnd != endptr) ERROR(err_qXfer_syntax);
			packetBuffer = GDBPacket_Start();
			dst.ol_buf = packetBuffer + 1;
			/* Handle reading from different objects. */
			if (ISNAME("exec-file") && isReadOperation) {
				REF struct task *thread;
				thread = GDB_DecodeThreadID(&annex, true);
				if unlikely(*annex != 0) {
					xdecref_unlikely(thread);
					ERROR(err_qXfer_syntax);
				}
				if unlikely(!thread)
					error = -ESRCH;
				else {
					error = GDBInfo_PrintThreadExecFile(&GDB_OffsetAndLengthPrinter, &dst, thread);
					decref_unlikely(thread);
				}
			} else if (ISNAME("features") && isReadOperation) {
				error = GDBInfo_PrintFeaturesFile(&GDB_OffsetAndLengthPrinter, &dst, annex);
			} else if (ISNAME("libraries") && isReadOperation) {
				if (*annex != 0) ERROR(err_qXfer_syntax);
				error = GDBInfo_PrintLibraryList(&GDB_OffsetAndLengthPrinter, &dst);
			} else if (ISNAME("threads") && isReadOperation) {
				if (*annex != 0) ERROR(err_qXfer_syntax);
				error = GDBInfo_PrintThreadList(&GDB_OffsetAndLengthPrinter, &dst);
			} else if (ISNAME("osdata") && isReadOperation) {
				if (strcmp(annex, "processes") == 0) {
					error = GDBInfo_PrintProcessList(&GDB_OffsetAndLengthPrinter, &dst);
				} else {
					ERROR(err_unknown_command);
				}
			} else {
				ERROR(err_unknown_command);
			}
			if (error == __SSIZE_MIN__)
				*packetBuffer = 'm'; /* There is more data... */
			else if (error < 0) {
				/* Assume that a negative value indicate a negative ERRNO value */
				if (!GDBPacket_SendError((u8)-error))
					ERROR(gdb_exit);
				return GDB_HANDLECOMMAND_ERROR;
			} else {
				*packetBuffer = 'l'; /* This is the last packet */
			}
			/* QXFER uses the escape-transmit mechanism to deliver data. */
			if (!GDBPacket_TransmitEscape(dst.ol_buf))
				ERROR(gdb_exit);
		} else if (ISNAME("Attached")) {
			p = nameEnd;
			if (*p == ':') {
				pid_t pid;
				REF struct task *thread;
				++p;
				pid = strto32(p, &p, 16);
				if (p != endptr)
					ERROR(err_syntax);
				/* Verify that the thread exists. */
				thread = GDB_GetProcessByPID(pid);
				if (!thread)
					ERROR(err_unknown_thread);
				decref_unlikely(thread);
			} else {
				if (p != endptr)
					ERROR(err_syntax);
			}
#if 1
			if (!GDBPacket_Send("0")) /* Created a new process */
				ERROR(gdb_exit);
#else
			if (!GDBPacket_Send("1")) /* Attached to an existing process */
				ERROR(gdb_exit);
#endif
		} else if (ISNAME("Offsets")) {
			goto send_empty; /* Not supported, but probed by GDB */
		} else if (ISNAME("TStatus")) {
			if (nameEnd != endptr)
				ERROR(err_syntax);
			goto send_empty; /* We don't support tracing, but GDB probes this packet... */
		} else {
			ERROR(err_unknown_command);
		}
#undef ISNAME
	}	break;

	case 'Q': {
		char *nameEnd;
		size_t nameLen;
		nameEnd = p;
		for (;;) {
			char ch = *nameEnd;
			if (ch == ',' || ch == ':' || ch == ';' || (!ch && nameEnd == endptr))
				break;
			++nameEnd;
		}
		nameLen = (size_t)(nameEnd - p);
#define ISNAME(name) (nameLen == COMPILER_STRLEN(name) && memcmp(p, name, COMPILER_STRLEN(name) * sizeof(char)) == 0)
		if (ISNAME("DisableRandomization") && *nameEnd == ':') {
			unsigned long mode;
			p    = nameEnd + 1;
			mode = strtoul(p, &p, 16);
			if (p != endptr)
				ERROR(err_syntax);
			vm_set_aslr_disabled(mode != 0);
			goto send_ok;
		} else if (ISNAME("NonStop") && *nameEnd == ':') {
			unsigned long mode;
			p    = nameEnd + 1;
			mode = strtoul(p, &p, 16);
			if (p != endptr)
				ERROR(err_syntax);
			if (mode) {
				/* Enable */
				ATOMIC_FETCHOR(GDB_Features, GDB_FEATURE_NONSTOP_MODE);
			} else {
				/* Disable */
				ATOMIC_FETCHAND(GDB_Features, ~GDB_FEATURE_NONSTOP_MODE);
				GDB_SuspendAllOtherCPUsNow();
			}
			goto send_ok;
#ifdef GDB_HAVE_READMEMORY_MEMMEM
		} else if (ISNAME("qSearch") && *nameEnd == ':' &&
		           memcmp(nameEnd + 1, "memory:", COMPILER_STRLEN("memory:") * sizeof(char)) == 0) {
			void *addr; char *dst;
			size_t i, length, pattern_length;
			vm_virt_t result;
			p = nameEnd + COMPILER_STRLEN("memory:");
			addr = STRTOADDR(p, &p, 16);
			if (*p++ != ';')
				ERROR(err_syntax);
			length = STRTOSIZE(p, &p, 16);
			if (*p++ != ';')
				ERROR(err_syntax);
			pattern_length = (size_t)(endptr - p);
			if (pattern_length & 1)
				ERROR(err_syntax);
			pattern_length /= 2;
			/* Decode memory from hex. */
			for (i = 0; i < pattern_length; ++i) {
				byte_t b;
				b  = fromhex(p[(i * 2) + 0]) << 4;
				b |= fromhex(p[(i * 2) + 1]);
				p[i] = b;
			}
			result = GDB_ReadMemory_memmem((vm_virt_t)addr, length, p, pattern_length, true);
			if (result == (vm_virt_t)-2)
				ERROR(err_faulty_memory);
			if (result == (vm_virt_t)-1) {
				if (!GDBPacket_Send("0"))
					ERROR(gdb_exit);
				goto done;
			}
			if (!GDBPacket_Sendf("1,%p", (void *)result))
				ERROR(gdb_exit);
			goto done;
#endif /* GDB_HAVE_READMEMORY_MEMMEM */
		} else if (ISNAME("StartNoAckMode") && nameEnd == endptr) {
			ATOMIC_FETCHOR(GDB_Features, GDB_FEATURE_NOACK_MODE);
			goto send_ok;
		} else {
			/* TODO: Support for `QCatchSyscalls' (could be implemented by using system call tracing...) */
			/* TODO: Support for `QThreadEvents' (enabled/disable thread start/stop notifications) */
			ERROR(err_unknown_command);
		}
#undef ISNAME
	}	break;


	case 'X': {
		void *addr;
		size_t length, error;
		addr = STRTOADDR(p, &p, 16);
		if (*p++ != ',')
			ERROR(err_syntax);
		length = STRTOSIZE(p, &p, 16);
		if (*p++ != ':')
			ERROR(err_syntax);
		error = GDB_DecodeEscapedBinary(p, endptr);
		if (length != error)
			ERROR(err_syntax);
		error = GDB_WriteMemoryWithoutSwBreak((vm_virt_t)addr, p, length, true);
		if (error != 0)
			ERROR(err_faulty_memory);
		goto send_ok;
	}	break;

	case 'z':
	case 'Z': {
		unsigned int type;
		unsigned int kind;
		void *addr;
		errno_t error;
		if (!(*p >= '0' && *p <= '4'))
			ERROR(err_syntax);
		type = (unsigned int)(*p++ - '0');
		if (*p++ != ',')
			ERROR(err_syntax);
		addr = STRTOADDR(p, &p, 16);
		if (*p++ != ',')
			ERROR(err_syntax);
		kind = (unsigned int)strtoul(p, &p, 16);
		if (p != endptr)
			ERROR(err_syntax);
		error = command == 'Z'
		        ? GDB_AddBreak(type, addr, kind)
		        : GDB_DelBreak(type, addr, kind);
		if (error == EOK)
			goto send_ok;
		if (error == ENOSYS || error == ENOMEM)
			goto send_empty; /* Respond empty if adding a breakpoint failed, or the system isn't supported. */
		if (!GDBPacket_SendError((u8)error))
			ERROR(gdb_exit);
	}	break;


	default:
err_unknown_command:
		printk(KERN_WARNING "[gdb] Unknown command: %$q\n",
		       (size_t)(endptr - GDBCommand_Buffer), GDBCommand_Buffer);
		if (!GDBPacket_SendEmpty())
			goto gdb_exit;
		return GDB_HANDLECOMMAND_UNKNOWN;
	}
done:
	return GDB_HANDLECOMMAND_OK;
err_syntax:
	printk(KERN_WARNING "[gdb] Syntax error in packet: %$q\n",
	       (size_t)(endptr - GDBCommand_Buffer), GDBCommand_Buffer);
	if (!GDBPacket_SendError(EINVAL))
		ERROR(gdb_exit);
	return GDB_HANDLECOMMAND_ERROR;
err_buffer_too_large:
	printk(KERN_WARNING "[gdb] Buffer by packet is too large: %$q\n",
	       (size_t)(endptr - GDBCommand_Buffer), GDBCommand_Buffer);
	if (!GDBPacket_SendError(EMSGSIZE))
		ERROR(gdb_exit);
	return GDB_HANDLECOMMAND_ERROR;
err_qXfer_syntax:
	printk(KERN_WARNING "[gdb] Syntax error in qXfer packet: %$q\n",
	       (size_t)(endptr - GDBCommand_Buffer), GDBCommand_Buffer);
/*err_qXfer_invalid:*/
	if (!GDBPacket_SendError(0))
		ERROR(gdb_exit);
	return GDB_HANDLECOMMAND_ERROR;
err_unknown_thread:
	if (!GDBPacket_SendError(ESRCH))
		ERROR(gdb_exit);
	return GDB_HANDLECOMMAND_ERROR;
err_faulty_memory:
	if (!GDBPacket_SendError(EFAULT))
		ERROR(gdb_exit);
	return GDB_HANDLECOMMAND_ERROR;
err_unknown_register:
	printk(KERN_WARNING "[gdb] Unknown register accessed by packet: %$q\n",
	       (size_t)(endptr - GDBCommand_Buffer), GDBCommand_Buffer);
	if (!GDBPacket_SendError(EPERM))
		ERROR(gdb_exit);
	return GDB_HANDLECOMMAND_ERROR;
err_invalid_register_size:
	printk(KERN_WARNING "[gdb] Invalid register size used by packet: %$q\n",
	       (size_t)(endptr - GDBCommand_Buffer), GDBCommand_Buffer);
	if (!GDBPacket_SendError(ENOBUFS))
		ERROR(gdb_exit);
	return GDB_HANDLECOMMAND_ERROR;
err_breakpoint_not_supported:
	/* Don't give any response when setting a breakpoint fails,
	 * thus acting like we simply don't supporting breakpoints. */
	if (!GDBPacket_SendEmpty())
		goto gdb_exit;
	return GDB_HANDLECOMMAND_ERROR;
gdb_exit:
	return GDB_HANDLECOMMAND_RESUME_NO_ATTACHED;
}







PRIVATE char const ACK[]  = { '+' };
PRIVATE char const NACK[] = { '-' };


/* Main interpreter loop */
PRIVATE void NOTHROW(FCALL GDB_InterpreterLoop)(void) {
	bool isFirst = true;
	if (GDB_RemoteFeatures & GDB_REMOTEFEATURE_ATTACHED) {
		/* If we're already attached to a remote, tell them what's going on.
		 * Otherwise, we got here as part of initialization. */
		if (GDB_Features & GDB_FEATURE_NONSTOP_MODE) {
			/* The %Stop notification gets send asynchronously, and must
			 * be followed by us re-syncing with GDB by sending `OK' */
			GDB_TransmitStopNotification();
		} else {
			if unlikely(!GDB_TransmitInterruptReason())
				return;
#if 0
			if (GDBReason_Registers &&
				memcmp(GDBReason_Registers, "fork:", 5) == 0) {
				char *buf;
				buf = GDBPacket_Start();
				buf += sprintf(buf, "T05thread:");
				buf = GDB_EncodeThreadID(buf, &_bootidle, true);
				buf += sprintf(buf, ";core:0;%s", GDBReason_Registers);
				if unlikely(!GDBPacket_Transmit(buf))
					return;
			}
#endif
		}
	}
	for (;;) {
		int byte;
		char *endptr;
		unsigned int error;
		assert(!task_isconnected());
		byte = (int)GDBRemote_GetByte();
		if (byte == 0x03) {
			/* Interrupt request */
			printk(KERN_INFO "[gdb] Interrupt request\n");
			if (!isFirst) {
				/* GDB may have gotten a bit confused about where we are.
				 * If we get an interrupt request somewhere in the middle
				 * of a session, tell GDB about why were here once again. */
				if unlikely(!GDB_TransmitInterruptReason())
					return;
			}
			GDB_SuspendAllOtherCPUsNow();
			isFirst = false;
			continue;
		}
		isFirst = false;
		if (byte != '$') {
			if (byte == '+' && (GDB_Features & GDB_FEATURE_NOACK_MODE))
				continue; /* Even though it promises no to, GDB sends one last + after enabling NOACK mode... */
			printk(KERN_WARNING "[gdb] Unexpected byte in interpreter loop: %#I8x\n", byte);
			if (byte == '-' || byte == '+')
				continue; /* Maybe we've just desynced (let's try to give this another chance...) */
			return;
		}
		endptr = GDBCommand_Buffer;
		/* Begin packet. */
		for (;;) {
			byte = GDBRemote_TimedGetByte();
			if unlikely(byte < 0) {
err_incomplete_packet:
				printk(KERN_WARNING "[gdb] Incomplete packet %$q\n",
				       (size_t)(endptr - GDBCommand_Buffer), GDBCommand_Buffer);
				return;
			}
			if ((byte_t)byte == '#') {
				byte_t checksum, expected_checksum;
				*endptr = 0;
				byte = GDBRemote_TimedGetByte();
				if unlikely(byte < 0)
					ERROR(err_incomplete_packet);
				checksum = (byte_t)fromhex((u8)byte) << 4;
				byte = GDBRemote_TimedGetByte();
				if unlikely(byte < 0)
					ERROR(err_incomplete_packet);
				checksum |= (byte_t)fromhex((u8)byte);
				expected_checksum = GDBPacket_GetCheckSum(GDBCommand_Buffer,
				                                          (size_t)(endptr - GDBCommand_Buffer));
				if (checksum != expected_checksum) {
					printk(KERN_ERR "[gdb] Checksum missmatch (remote(%#I8x) != local(%#I8x)) on packet \"%#$q[...]\"\n",
					       checksum, expected_checksum,
					       (size_t)(endptr - GDBCommand_Buffer), GDBCommand_Buffer);
					goto send_nack_and_wait_for_next_packet;
				}
				/* Always send ACK when having received a valid packet. */
				if (!(GDB_Features & GDB_FEATURE_NOACK_MODE))
					GDBRemote_PutData(ACK, sizeof(ACK));
				/* Handle the received packet */
				GDB_DEBUG("[gdb] command:%$q\n",
				          (size_t)(endptr - GDBCommand_Buffer),
				          GDBCommand_Buffer);
				assert(!task_isconnected());
				error = GDB_HandleCommand(endptr);
				assert(!task_isconnected());
				if (error == GDB_HANDLECOMMAND_RESUME)
					goto done;
				if (error == GDB_HANDLECOMMAND_RESUME_NO_ATTACHED)
					goto done_noattach;
				goto next_packet;
			}
			if ((byte_t)byte == '}') {
				/* Escaped the next byte. */
				if unlikely(endptr >= COMPILER_ENDOF(GDBCommand_Buffer) - 2)
					ERROR(err_command_length_overflow_escape);
				*endptr++ = byte;
				byte      = GDBRemote_TimedGetByte();
				if unlikely(byte < 0)
					ERROR(err_incomplete_packet);
				*endptr++ = byte;
				continue;
			}
			if unlikely(endptr >= COMPILER_ENDOF(GDBCommand_Buffer) - 1) {
				/* Command packet too large. */
/*err_command_length_overflow:*/
				/* Wait until the command packet has terminated. */
				for (;;) {
					byte = GDBRemote_TimedGetByte();
					if unlikely(byte < 0)
						ERROR(err_incomplete_packet);
					if ((byte_t)byte == '#') {
						if unlikely(GDBRemote_TimedGetByte() < 0)
							ERROR(err_incomplete_packet);
						if unlikely(GDBRemote_TimedGetByte() < 0)
							ERROR(err_incomplete_packet);
						break;
					}
					if ((byte_t)byte == '}') {
err_command_length_overflow_escape:
						byte = GDBRemote_TimedGetByte();
						if unlikely(byte < 0)
							ERROR(err_incomplete_packet);
					}
				}
				printk(KERN_ERR "[gdb] Command packet \"%#$q[...]\" is too large\n",
				       COMPILER_LENOF(GDBCommand_Buffer) - 1, GDBCommand_Buffer);
send_nack_and_wait_for_next_packet:
				if (!(GDB_Features & GDB_FEATURE_NOACK_MODE))
					GDBRemote_PutData(NACK, sizeof(NACK));
				goto next_packet;
			}
			*endptr++ = byte;
		}
next_packet:
		;
	}
done:
	GDBRemote_SetAttached();
done_noattach:
	;
}


INTDEF REF struct task *GDBThread_Current;

/* Main function called to transmit the trap reason,
 * before entering the GDB interpreter loop.
 * The interpreter loop itself is executed  */
INTERN void NOTHROW(FCALL GDB_Main)(void) {
	if unlikely(GDBThread_Current != NULL) {
		printk(KERN_WARNING "[gdb] Recursion detected: Not entering interpreter loop\n");
		return; /* Another precaution against recursive invocation... */
	}
	GDB_DEBUG("[gdb] Enter interpreter loop on thread %p\n", THIS_TASK);
	GDB_InitializeCurrentThread();
	GDB_ClearSingleStepIgnoredRange();
	GDB_ThreadForStepAndContinue           = NULL;
	GDB_IteratorFor_qfsThreadInfo.eti_next = NULL;
	GDB_InterpreterLoop();
	if (GDB_ThreadForStepAndContinue) {
		decref_unlikely(GDB_ThreadForStepAndContinue);
		GDB_ThreadForStepAndContinue = NULL;
	}
	if (GDB_IteratorFor_qfsThreadInfo.eti_next) {
		GDBEnumThreads_Fini(&GDB_IteratorFor_qfsThreadInfo);
		GDB_IteratorFor_qfsThreadInfo.eti_next = NULL;
	}
	GDB_FinalizeCurrentThread();
	GDB_DEBUG("[gdb] Exit interpreter loop on thread %p\n", THIS_TASK);
}


INTERN struct kernel_debugtraps GDB_DebugTraps = {
	.dt_trap_icpustate = &GDB_TrapICpuState,
	.dt_trap_scpustate = &GDB_TrapSCpuState,
	.dt_trap_ucpustate = &GDB_TrapUCpuState,
	.dt_trap_kcpustate = &GDB_TrapKCpuState,
	.dt_trap_lcpustate = &GDB_TrapLCpuState,
	.dt_trap_fcpustate = &GDB_TrapFCpuState
};


PRIVATE void KCALL my_vm_onexec(void) {
	GDB_ClearAllKernelAndUserBreakpointsFromVM(THIS_VM);
}

/* Initialize/Finalize the GDB driver. */
INTERN DRIVER_INIT void KCALL GDB_Initialize(void) {
	vm_onexec_callbacks.insert(&my_vm_onexec);
	TRY {
		vm_onfini_callbacks.insert(&GDB_ClearAllKernelAndUserBreakpointsFromVM);
		TRY {
			GDBInterrupt_Initialize();
			TRY {
				GDBRemote_Initialize();
				TRY {
					kernel_debugtraps_install(&GDB_DebugTraps);
				} EXCEPT {
					GDBRemote_Finalize();
					RETHROW();
				}
			} EXCEPT {
				GDBInterrupt_Finalize();
				RETHROW();
			}
		} EXCEPT {
			vm_onfini_callbacks.remove(&GDB_ClearAllKernelAndUserBreakpointsFromVM);
			RETHROW();
		}
	} EXCEPT {
		vm_onexec_callbacks.remove(&my_vm_onexec);
		RETHROW();
	}
	/* Wait for the initial connection to be made. */
	kernel_debugtrap(SIGTRAP, NULL);

	/* Now that we're connected, inform GDB about the boot process,
	 * since during initialization GDB only learned about the kernel
	 * process.
	 * We're actually quite lucky that GDB starts initialization by
	 * issuing `Hgp0.0' (switch to any thread in any process), which
	 * we interpret as <switch to _bootidle>, so GDB learned about
	 * the kernel then. */
#if 1
	if (GDB_RemoteFeatures & GDB_REMOTEFEATURE_FORK_EVENTS) {
		printk(KERN_INFO "[gdb] Issuing fork() for `_boottask'\n");
		/* FIXME: Actually telling GDB about the correct thread ID, causes GDB to freeze with its
		 *        process taking up 100% cpu usage (though mind you, only using a single core of
		 *        my host which equates to 8%) However, just putting in the multiprocess-compliant
		 *        pid=1;tid=1 seems to prevent it from hanging itself...
		 *        Looking at the GDB source code I've started to get the feeling that it expects 2
		 *        trap interrupts when a fork happens (???), however this can only ever be done in
		 *        non-stop mode (which is a way bigger thing of weirdness that the online documentation
		 *        fails to let me comprehend), so I don't really know what GDB wants from me...
		 *        Anyways, the online documentation of the `fork' stop reply packet ...
		 *        https://sourceware.org/gdb/onlinedocs/gdb/Stop-Reply-Packets.html#Stop-Reply-Packets
		 *        ... doesn't even mention the fact that a fork always implies there being 2 processes,
		 *        nor does it mention which of them should send the stop reply.
		 *        Inference from other stop reply packets also doesn't help:
		 *         #1: Since a vfork() reply exists, and a vfork() always implies that the parent process
		 *             remains suspended until the child exit()- or exec()s would imply that it is the
		 *             child process (and only the child?) which is supposed to send fork notifications
		 *             However, since the docs _do_ mention that the fork stop reason should be followed
		 *             by the _child_ thread-id, GDB would never know who the parent is, so while vfork()
		 *             isn't even on the table, its similarity poses more questions than it answers
		 *         #2: Since fork() should include the thread-ID of the child process, it would seem
		 *             obvious that the parent process should send a packet like:
		 *             $T05[...]thread:<PARENT_THREAD_ID>;[...]fork:<CHILD_THREAD_ID>;#[...]
		 *             However, having tried this, it is what causes GDB to hang itself, so either I'm
		 *             doing this part wrong, or this isn't the answer either.
		 * NOTE: This FIXME is mirrored in `/kos/src/kernel/core/arch/i386/task-clone.c'
		 */
		kernel_debugtrap(SIGTRAP, DEBUG_TRAP_REGISTER_FORK ":p1.1");
	}
#endif
	printk(KERN_INFO "[gdb] Initialization complete\n");
}

INTERN DRIVER_FINI void KCALL GDB_Finalize(void) {
	kernel_debugtraps_uninstall(&GDB_DebugTraps);
	GDBRemote_Finalize();
	GDBInterrupt_Finalize();
	vm_onfini_callbacks.remove(&GDB_ClearAllKernelAndUserBreakpointsFromVM);
	vm_onexec_callbacks.remove(&my_vm_onexec);
}



DECL_END

#endif /* !GUARD_MODGDB_GDB_C */
