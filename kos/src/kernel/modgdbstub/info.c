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
#ifndef GUARD_MODGDB_INFO_C
#define GUARD_MODGDB_INFO_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "gdb.h"

#include <sched/cpu.h>
#include <sched/task.h>
#include <kernel/except.h>
#include <sched/pid.h>
#include <stdio.h>
#include <kos/kernel/paging.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <hybrid/atomic.h>
#include <kernel/compiler.h>
#include <kernel/vm/library.h>
#include <format-printer.h>

DECL_BEGIN

PRIVATE WUNUSED REF struct task *
NOTHROW(FCALL GDB_ThreadInRootPidNS)(struct task *thread) {
	size_t i;
	REF struct task *result;
	if (!GDB_DidSuspendOtherCPUs)
		sync_read(&pidns_root);
	for (i = 0; i <= pidns_root.pn_mask; ++i) {
		struct taskpid *pid;
		pid = pidns_root.pn_list[i].pe_pid;
		if (pid == NULL || pid == PIDNS_ENTRY_DELETED)
			continue;
		if (ATOMIC_READ(pid->tp_thread.m_pointer) != thread)
			continue;
		result = taskpid_gettask(pid);
		if (!result)
			continue;
		if unlikely(result != thread) {
			/* Really shouldn't happen, but let's be safe. */
			decref_unlikely(result);
			continue;
		}
		if (!GDB_DidSuspendOtherCPUs)
			sync_endread(&pidns_root);
		return result;
	}
	if (!GDB_DidSuspendOtherCPUs)
		sync_endread(&pidns_root);
	return NULL;
}

PRIVATE WUNUSED bool
NOTHROW(FCALL GDB_ThreadIsIdleTask)(struct task *thread) {
	cpuid_t i;
	for (i = 0; i < cpu_count; ++i) {
		if (thread == &FORCPU(cpu_vector[i], _this_idle))
			return true;
	}
	return false;
}


/* Make sure that `thread' is a valid thread. If it isn't, return NULL. */
INTERN WUNUSED REF struct task *
NOTHROW(FCALL GDB_VerifyThreadAndIncref)(struct task *thread) {
	REF struct task *result;
	result = GDB_ThreadInRootPidNS(thread);
	if (result)
		goto done;
	if (GDB_ThreadIsIdleTask(thread))
		goto known;
	if (thread == &_boottask)
		goto known;
	/* TODO: Go through all CPUs and check if `thread' is being hosted by any one of them.
	 *       When `GDB_DidSuspendOtherCPUs' is false, this part has to be done with the
	 *       help of some IPIs, but when `GDB_DidSuspendOtherCPUs' is true, we can access
	 *       the structures directly! */
done:
	return result;
known:
	return incref(thread);
}


INTERN WUNUSED REF struct task *
NOTHROW(FCALL GDB_GetProcessByPID)(upid_t pid) {
	if (!(GDB_RemoteFeatures & GDB_REMOTEFEATURE_MULTIPROCESS)) {
		REF struct task *result;
#ifdef HIGH_MEMORY_KERNEL
		result = (REF struct task *)((uintptr_t)(size_t)pid + KERNEL_BASE);
#else /* HIGH_MEMORY_KERNEL */
		result = (REF struct task *)(uintptr_t)(size_t)pid;
#endif /* !HIGH_MEMORY_KERNEL */
		return GDB_VerifyThreadAndIncref(result);
	}
	if (pid == GDB_MULTIPROCESS_KERNEL_PID)
		return incref(&_bootidle);
	return GDB_DidSuspendOtherCPUs
	       ? pidns_trylookup_task_locked(&pidns_root, pid)
	       : pidns_trylookup_task(&pidns_root, pid);
}


INTERN WUNUSED NONNULL((1, 2)) char *
NOTHROW(FCALL GDB_EncodeThreadID)(char *ptr, struct task *__restrict thread,
                                  bool need_p_prefix) {
	assert(ADDR_IS_KERNEL(thread));
	if (GDB_RemoteFeatures & GDB_REMOTEFEATURE_MULTIPROCESS) {
		upid_t pid, tid;
		if (thread->t_flags & TASK_FKERNTHREAD) {
set_kernel_thread:
			pid = GDB_MULTIPROCESS_KERNEL_PID;
#ifdef HIGH_MEMORY_KERNEL
			tid = (uintptr_t)thread - KERNEL_BASE;
#else  /* HIGH_MEMORY_KERNEL */
			tid = (uintptr_t)thread;
#endif /* !HIGH_MEMORY_KERNEL */
		} else {
			pid = task_getrootpid_of_s(thread);
			tid = task_getroottid_of_s(thread);
			if unlikely(!pid || !tid)
				goto set_kernel_thread; /* Shouldn't happen... */
		}
		if (need_p_prefix)
			*ptr++ = 'p';
		ptr += sprintf(ptr, "%Ix.%Ix", pid, tid);
	} else {
#ifdef HIGH_MEMORY_KERNEL
		ptr += sprintf(ptr, "%Ix", (uintptr_t)thread - KERNEL_BASE);
#else  /* HIGH_MEMORY_KERNEL */
		ptr += sprintf(ptr, "%Ix", (uintptr_t)thread);
#endif /* !HIGH_MEMORY_KERNEL */
	}
	return ptr;
}

INTERN WUNUSED NONNULL((1)) REF struct task *
NOTHROW(FCALL GDB_DecodeThreadID)(char **__restrict pptr,
                                  bool need_p_prefix) {
	REF struct task *result;
	char *ptr = *pptr;
	if (GDB_RemoteFeatures & GDB_REMOTEFEATURE_MULTIPROCESS) {
		s32 pid, tid;
		if (*ptr != 'p') {
			tid = strto32(ptr, &ptr, 16);
			if (tid == -1 || tid == 0 || tid == GDB_MULTIPROCESS_KERNEL_PID)
				result = incref(&_bootidle);
			else {
#ifdef HIGH_MEMORY_KERNEL
				result = (REF struct task *)((uintptr_t)(size_t)tid + KERNEL_BASE);
#else /* HIGH_MEMORY_KERNEL */
				result = (REF struct task *)(uintptr_t)(size_t)tid;
#endif /* !HIGH_MEMORY_KERNEL */
				result = GDB_VerifyThreadAndIncref(result);
			}
			goto done;
		}
		++ptr;
		pid = strto32(ptr, &ptr, 16);
		tid = -1;
		if (*ptr == '.')
			tid = strto32(ptr + 1, &ptr, 16);
		if (pid == GDB_MULTIPROCESS_KERNEL_PID) {
			/* Kernel thread */
			if (tid <= 0)
				result = incref(&_bootidle);
			else {
#ifdef HIGH_MEMORY_KERNEL
				result = (REF struct task *)((uintptr_t)tid + KERNEL_BASE);
#else /* HIGH_MEMORY_KERNEL */
				result = (REF struct task *)tid;
#endif /* !HIGH_MEMORY_KERNEL */
				result = GDB_VerifyThreadAndIncref(result);
			}
		} else {
			if (tid <= 0)
				tid = pid;
			if (!tid)
				result = incref(THIS_TASK); /* Any process/thread */
			else {
				result = GDB_GetProcessByPID((upid_t)tid);
				if (result && pid > 0 && task_getrootpid_of_s(result) != (upid_t)pid) {
					/* Different task selected. */
					decref_unlikely(result);
					result = NULL;
				}
			}
		}
	} else {
		ssize_t tid;
		tid = STRTOSSIZE(ptr, &ptr, 16);
		if (tid == -1)
			result = incref(&_bootidle);
		else if (tid == 0)
			result = incref(THIS_TASK);
		else {
#ifdef HIGH_MEMORY_KERNEL
			result = (REF struct task *)((uintptr_t)(size_t)tid + KERNEL_BASE);
#else /* HIGH_MEMORY_KERNEL */
			result = (REF struct task *)(uintptr_t)(size_t)tid;
#endif /* !HIGH_MEMORY_KERNEL */
			result = GDB_VerifyThreadAndIncref(result);
		}
	}
done:
	*pptr = ptr;
	return result;
}



#define DO(expr)    do{ if ((temp = (expr)) < 0) goto err; result += temp; }__WHILE0
#define PRINT(str)  DO((*printer)(arg, str, COMPILER_STRLEN(str)))
#define PRINTF(...) DO(format_printf(printer, arg, __VA_ARGS__))


PRIVATE NONNULL((1, 3)) ssize_t KCALL
GDB_PrintRemoteVMString(pformatprinter printer, void *arg,
                        struct vm *__restrict effective_vm,
                        USER CHECKED char const *string,
                        bool print_repr) {
	char buf[256];
	size_t temp, result = 0;
	size_t pagesize = pagedir_pagesize_p(PAGEDIR_P_SELFOFVM(effective_vm));
	for (;;) {
		size_t partlen, maxread;
		/* Stay within the same page when reading memory. */
		maxread = pagesize - ((uintptr_t)string & (pagesize - 1));
		if (maxread > sizeof(buf))
			maxread = sizeof(buf);
		vm_read(buf, effective_vm, string, maxread, true);
		partlen = strnlen(buf, maxread);
		assert(partlen <= maxread);
		DO(print_repr ? format_escape(printer, arg, buf, partlen, FORMAT_ESCAPE_FPRINTRAW)
		              : (*printer)(arg, buf, partlen));
		if (partlen < maxread)
			break;
		string += maxread;
	}
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1)) bool KCALL
GDB_IsRemoteALibraryFilename(struct vm *__restrict effective_vm,
                             USER CHECKED char const *string) {
	char buf[256];
	size_t leading = 0;
	size_t pagesize = pagedir_pagesize_p(PAGEDIR_P_SELFOFVM(effective_vm));
	for (;;) {
		size_t partlen, maxread;
		/* Stay within the same page when reading memory. */
		maxread = pagesize - ((uintptr_t)string & (pagesize - 1));
		if (maxread > sizeof(buf) - leading)
			maxread = sizeof(buf) - leading;
		vm_read(buf + leading, effective_vm, string, maxread, true);
		partlen = strnlen(buf + leading, maxread);
		assert(partlen <= maxread);
		if (partlen < maxread) {
			partlen += leading;
			if (partlen < 3)
				break; /* Too short */
			if (buf[partlen - 3] != '.')
				break;
			if (buf[partlen - 2] != 's')
				break;
			if (buf[partlen - 1] != 'p')
				break;
			return true;
		}
		leading = 3;
		if (leading > maxread)
			leading = maxread;
		memmove(buf, buf + maxread - leading, leading);
		string += maxread;
	}
	return false;
}



/* Print a human-readable name for `thread' */
INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadName)(pformatprinter printer, void *arg,
                                       struct task *__restrict thread) {
	/* TODO: More information? */
	return format_printf(printer, arg, "%p", thread);
}


/* `qXfer:exec-file:read': Print the absolute filename for the original binary passed to exec()
 *                         when the process of `thread' was started. (`/proc/${PID_OF(thread)}/exe') */
INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadExecFile)(pformatprinter printer, void *arg,
                                           struct task *__restrict thread) {
	ssize_t result;
	struct vm *effective_vm;
	if (thread == &_bootidle) {
		char const *filename;
do_print_kernel_thread:
		/* Special case: Kernel thread. */
		filename = kernel_driver.d_filename;
		if unlikely(!filename)
			return 0;
		return (*printer)(arg, filename, strlen(filename));
	}
	if (thread->t_flags & TASK_FKERNTHREAD)
		goto do_print_kernel_thread;
	/* XXX: `t_vm' is a read-private field (it can't safely be read without ensuring
	 *       that `thread' isn't currently modifying it when in non-stop mode) */
	effective_vm = incref(ATOMIC_READ(thread->t_vm));
	if (effective_vm == &vm_kernel) {
		decref_nokill(effective_vm);
		goto do_print_kernel_thread;
	}
	result = GDBInfo_PrintVMExecFile(printer, arg, effective_vm);
	decref_unlikely(effective_vm);
	return result;
}

typedef struct {
	pformatprinter ef_printer; /* Printer. */
	void          *ef_arg;     /* Printer argument. */
	ssize_t        ef_result;  /* Propagated result. */
} GDB_VMExecFilePrinterData;

PRIVATE NONNULL((1, 2)) ssize_t KCALL
GDB_VMExecFilePrinter(void *arg,
                      struct vm *__restrict effective_vm,
                      USER CHECKED char const *filename,
                      USER UNCHECKED void *UNUSED(loadaddr),
                      USER UNCHECKED void *UNUSED(loadstart),
                      bool UNUSED(filename_may_be_relative)) {
	GDB_VMExecFilePrinterData *closure;
	char buf[256]; /* Must be smaller than 1 page! */
	ssize_t result;
	size_t pagesize;
	size_t partlen, maxread;
	closure  = (GDB_VMExecFilePrinterData *)arg;
	pagesize = pagedir_pagesize_p(PAGEDIR_P_SELFOFVM(effective_vm));
	/* Stay within the same page when reading memory. */
	maxread = pagesize - ((uintptr_t)filename & (pagesize - 1));
	if (maxread > sizeof(buf))
		maxread = sizeof(buf);
	vm_read(buf, effective_vm, filename, maxread, true);
again_check_strnlen:
	partlen = strnlen(buf, maxread);
	assert(partlen <= maxread);
	if (partlen == maxread) {
		assert(maxread <= sizeof(buf));
		if (maxread < sizeof(buf)) {
			vm_read(buf + maxread, effective_vm,
			        filename + maxread,
			        sizeof(buf) - maxread, true);
			goto again_check_strnlen;
		}
		assert(maxread == sizeof(buf));
		/* String too long (must go the slow route) */
		if (GDB_IsRemoteALibraryFilename(effective_vm, filename + sizeof(buf) - 3))
			return 0;
		/* This is the one! */
		result = (*closure->ef_printer)(closure->ef_arg, buf, sizeof(buf));
		if (result >= 0) {
			ssize_t temp;
			temp = GDB_PrintRemoteVMString(closure->ef_printer,
			                               closure->ef_arg,
			                               effective_vm,
			                               filename + sizeof(buf),
			                               false);
			if unlikely(temp < 0)
				result = temp;
			else {
				result += temp;
			}
		}
		closure->ef_result = result;
		return -1;
	}
	/* Likely case: Short string. */
	if (partlen >= 3 && buf[partlen - 3] == '.' &&
		buf[partlen - 2] == 's' && buf[partlen - 1] == 'o')
		return 0; /* This one's a library file */
	result = (*closure->ef_printer)(closure->ef_arg, buf, partlen);
	closure->ef_result = result;
	return -1;
}

INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintVMExecFile)(pformatprinter printer, void *arg,
                                       struct vm *__restrict effective_vm) {
	GDB_VMExecFilePrinterData data;
	ssize_t error;
	data.ef_printer = printer;
	data.ef_arg     = arg;
	data.ef_result  = 0;
	/* XXX: This is a _really_ hacky and ugly way of doing this.
	 *      For one, it relies on user-space memory (which is fine), but it
	 *      also relies on the extension of file names (which is _not_ fine)
	 *      At the very latest once we get support for procfs, there will
	 *      have to be a proper mechanism (or maybe some additional flag in
	 *      the format used by `sys_set_library_list()') to determine which
	 *      is the original executable used to launch the application */
	TRY {
		error = vm_library_enumerate(effective_vm,
		                             &GDB_VMExecFilePrinter,
		                             &data);
	} EXCEPT {
		error = 0; /* Error while accessing user-space memory */
	}
	if (error < 0)
		return data.ef_result;
	/* Unknown filename. */
	return -EFAULT;
}


typedef struct {
	pformatprinter ll_printer; /* Printer. */
	void          *ll_arg;     /* Printer argument. */
} GDB_LibraryListPrinterData;

PRIVATE NONNULL((1, 2)) ssize_t KCALL
GDB_LibraryListPrinter(void *closure,
                       struct vm *__restrict effective_vm,
                       USER CHECKED char const *filename,
                       USER UNCHECKED void *UNUSED(loadaddr),
                       USER UNCHECKED void *loadstart,
                       bool UNUSED(filename_may_be_relative)) {
	ssize_t temp, result = 0;
	pformatprinter printer; void *arg;
	printer = ((GDB_LibraryListPrinterData *)closure)->ll_printer;
	arg     = ((GDB_LibraryListPrinterData *)closure)->ll_arg;
	PRINT("<library name=\"");
	TRY {
		DO(GDB_PrintRemoteVMString(printer, arg, effective_vm, filename, true));
	} EXCEPT {
	}
	PRINTF("\">"
	           "<segment address=\"%#Ix\"/>"
	       "</library>",
	       loadstart);
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintKernelDriverList)(pformatprinter printer, void *arg) {
	size_t i; ssize_t temp, result = 0;
	REF struct driver_state *state;
	state = driver_get_state();
	for (i = 0; i < state->ds_count; ++i) {
		struct driver *d = state->ds_drivers[i];
		Elf_Half j;
		size_t lowest_segment_offset;
		size_t alignment_offset;
		/* One would expect that GDB wants `d_loadaddr', but that is incorrect.
		 * One might also thing that GDB wants `d_loadstart', and that is ~mostly~ correct.
		 * But what GDB actually wants is the absolute address of the first segment, meaning
		 * we need to adjust the driver load address for the sub-page offset of the segment
		 * with the lowest vaddr offset. */
		alignment_offset      = 0;
		lowest_segment_offset = (size_t)-1;
		assert(d->d_phnum != 0);
		for (j = 0; j < d->d_phnum; ++j) {
			if (d->d_phdr[j].p_type != PT_LOAD)
				continue;
			if (d->d_phdr[j].p_offset >= lowest_segment_offset)
				continue;
			lowest_segment_offset = d->d_phdr[j].p_offset;
			alignment_offset      = lowest_segment_offset & (PAGESIZE - 1);
		}
		if (d->d_filename) {
			PRINTF("<library name=\"%#q\">", d->d_filename);
		} else {
			REF struct driver_library_path_string *libpath;
			libpath = driver_library_path.get();
			if (!strrchr(libpath->dlp_path, ':')) {
				/* Only a single library path was defined.
				 * In this case, we can pretty much assume where the driver originates from. */
				size_t len;
				char const *path = libpath->dlp_path;
				while (*path == '/')
					++path;
				len = strlen(path);
				while (len && path[len - 1] == '/')
					--len;
				PRINTF("<library name=\"/%#$q/%#q\">", len, path, d->d_name);
				decref_unlikely(libpath);
			} else {
				decref_unlikely(libpath);
				PRINTF("<library name=\"%#q\">", d->d_name);
			}
		}
		PRINTF("<segment address=\"%#Ix\"/>"
		       "</library>",
		       d->d_loadstart + alignment_offset);
	}
	decref_unlikely(state);
	return result;
err:
	decref_unlikely(state);
	return temp;
}

/* `qXfer:libraries:read': Print the list of library loaded into the current process. */
INTERN NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintLibraryList)(pformatprinter printer, void *arg) {
	ssize_t temp, result = 0;
	GDB_LibraryListPrinterData data;
	data.ll_printer = printer;
	data.ll_arg     = arg;
	PRINTF("<?xml version=\"1.0\"?>"
	       "<!DOCTYPE target SYSTEM \"library-list.dtd\">"
	       "<library-list>"
	           "<library name=%q>"
	               "<segment address=\"%#Ix\"/>"
	           "</library>",
	       kernel_driver.d_filename,
	       kernel_driver.d_loadstart);
	DO(GDBInfo_PrintKernelDriverList(printer, arg));
	{
		struct vm *myvm;
		myvm = GDB_GetCurrentThread()->t_vm;
		/* Print user-space library listings. */
		if (myvm != &vm_kernel) {
			TRY {
				DO(vm_library_enumerate(myvm, &GDB_LibraryListPrinter, &data));
			} EXCEPT {
			}
		}
	}
	PRINT("</library-list>");
	return result;
err:
	return temp;
}

/* `qXfer:threads:read': Print the list of threads apart of the current process. */
INTERN NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintThreadList)(pformatprinter printer, void *arg) {
	ssize_t temp, result = 0;
	GDBEnumThreadsIterator iter;
	REF struct task *thread;
	GDBEnumThreads_Init(&iter);
	PRINT("<?xml version=\"1.0\"?>"
	      "<threads>");
	while ((thread = GDBEnumThreads_Next(&iter)) != NULL) {
		char id_buf[GDB_ENCODETHREADID_MAXCHARS], *id_end;
		char const *description;
		uintptr_t flags;
		FINALLY_DECREF_UNLIKELY(thread);
		id_end = GDB_EncodeThreadID(id_buf, thread, true);
		assert((size_t)(id_end - id_buf) <= GDB_ENCODETHREADID_MAXCHARS);
		PRINTF("<thread id=\"%$s\" core=\"%u\" name=\"",
		       (size_t)(id_end - id_buf), id_buf,
		       thread->t_cpu->c_id);
		DO(GDBInfo_PrintThreadName(printer, arg, thread));
		flags = ATOMIC_READ(thread->t_flags);
		if (flags & TASK_FTERMINATED)
			description = "terminated";
		else if (flags & TASK_FTERMINATING)
			description = "terminating";
		else if (thread == &FORCPU(thread->t_cpu, _this_idle))
			description = "idle";
		else if (flags & TASK_FRUNNING)
			description = "running";
		else {
			description = "?";
		}
		PRINTF("\">%s</thread>", description);
	}
	PRINT("</threads>");
	GDBEnumThreads_Fini(&iter);
	return result;
err:
	GDBEnumThreads_Fini(&iter);
	return temp;
}

/* `qXfer:osdata:read:processes': Print the list of processes running on the system. */
INTERN NONNULL((1)) ssize_t
NOTHROW(FCALL GDBInfo_PrintProcessList)(pformatprinter printer, void *arg) {
	ssize_t temp, result = 0;
	GDBEnumProcessIterator iter;
	REF struct task *thread;
	GDBEnumProcess_Init(&iter);
	PRINT("<?xml version=\"1.0\"?>"
	      "<!DOCTYPE target SYSTEM \"osdata.dtd\">"
	      "<osdata type=\"processes\">");
	while ((thread = GDBEnumProcess_Next(&iter)) != NULL) {
		u32 pid;
		FINALLY_DECREF_UNLIKELY(thread);
		pid = thread == &_bootidle ? GDB_MULTIPROCESS_KERNEL_PID
		                           : task_getrootpid_of_s(thread);
		PRINTF("<item>"
		       "<column name=\"pid\">%I32x</column>"
		       "<column name=\"user\">root</column>"
		       "<column name=\"command\">", pid);
		DO(GDBInfo_PrintThreadExecFile(printer, arg, thread));
		PRINT("</column>"
		      /* XXX: <column name="cores">1,2,3</column> */
		      "</item>");
	}
	PRINT("</osdata>");
	GDBEnumProcess_Fini(&iter);
	return result;
err:
	GDBEnumProcess_Fini(&iter);
	return temp;
}



#ifdef __x86_64__
#elif defined(__i386__)
#define HAVE_GDBFeatures_target_xml 1
STATIC_ASSERT(GDB_REGISTER_I386_FSBASE == 48);
STATIC_ASSERT(GDB_REGISTER_I386_GSBASE == 49);
PRIVATE char const GDBFeatures_target_xml[] =
"<?xml version=\"1.0\"?>"
"<!DOCTYPE target SYSTEM \"gdb-target.dtd\">"
"<target>"
	"<architecture>i386</architecture>"
//	"<osabi>KOS</osabi>"
	"<xi:include href=\"32bit-core.xml\"/>"
	"<xi:include href=\"32bit-sse.xml\"/>"
	"<feature name=\"de.gdb.i386.kos\">"
		"<reg name=\"fs_base\" bitsize=\"32\" type=\"int\" regnum=\"48\"/>" /* GDB_REGISTER_I386_FSBASE */
		"<reg name=\"gs_base\" bitsize=\"32\" type=\"int\" regnum=\"49\"/>" /* GDB_REGISTER_I386_GSBASE */
	"</feature>"
"</target>"
;
#endif /* !__x86_64__ */

/* `qXfer:features:read': Print the named features file `filename' */
INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDBInfo_PrintFeaturesFile)(pformatprinter printer, void *arg,
                                         char const *__restrict filename) {
#ifdef HAVE_GDBFeatures_target_xml
	if (strcmp(filename, "target.xml") == 0)
		return (*printer)(arg, GDBFeatures_target_xml, COMPILER_STRLEN(GDBFeatures_target_xml));
#endif /* HAVE_GDBFeatures_target_xml */
	return -ENOENT;
}




DECL_END

#endif /* !GUARD_MODGDB_INFO_C */
