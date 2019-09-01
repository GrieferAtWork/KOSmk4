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
#ifndef GUARD_MODGDB_THREAD_C
#define GUARD_MODGDB_THREAD_C 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>
#include <kernel/vm.h>
#include <kernel/except.h>
#include <kernel/fpu.h>
#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/pid.h>
#include <hybrid/atomic.h>
#include <hybrid/unaligned.h>
#include <sched/rpc.h>
#include <alloca.h>
#include <assert.h>
#include <string.h>

#include "gdb.h"

#if defined(__x86_64__) || defined(__i386__)
#include <asm/intrin.h>
#endif


DECL_BEGIN

INTERN REF struct task *GDBThread_Current = NULL;
/* Signal broadcast when the current thread changes. */
INTERN struct sig GDBThread_CurrentChaned = SIG_INIT;

/* Initialize/Finalize the current-thread sub-system */
INTERN void NOTHROW(FCALL GDB_InitializeCurrentThread)(void) {
	struct task *thread = THIS_TASK;
	struct cpu *mycpu;
	pflag_t was;
	assert(GDBThread_Current == NULL);
	/* Special case: The user probably isn't too interested in IDLE threads,
	 *               however when it comes to random interrupts, it's very
	 *               likely that it is an IDLE thread that was active when
	 *               the interrupt got triggered.
	 *               In this case, simply use the first sleeping thread of
	 *               the current CPU (if any) */
	was = PREEMPTION_PUSHOFF();
	COMPILER_READ_BARRIER();
	mycpu = thread->t_cpu;
	if (thread == &FORCPU(mycpu, _this_idle) &&
	    mycpu->c_sleeping != NULL) {
		thread = incref(mycpu->c_sleeping);
	} else {
		incref(thread);
	}
	PREEMPTION_POP(was);
	GDBThread_Current = thread; /* Inherit reference. */
}

INTERN void NOTHROW(FCALL GDB_FinalizeCurrentThread)(void) {
	assert(GDBThread_Current != NULL);
	decref_unlikely(GDBThread_Current);
	GDBThread_Current = NULL;
}


/* Get/Set the GDB thread that is currently being debugged.
 * Note that this is also used to control the enumeration of
 * threads apart of some given process.
 * @return: false: [GDB_SetCurrentThread] The specified thread could not be suspended,
 *                                        because it has already terminated. */
INTERN WUNUSED ATTR_RETNONNULL struct task *
NOTHROW(FCALL GDB_GetCurrentThread)(void) {
	assert(GDBThread_Current != NULL);
	return GDBThread_Current;
}



/* TODO: Move this into an arch-specific header */
#ifdef __x86_64__
#define HAVE_ICPUSTATEUNSAVEDREGISTERS 1
typedef struct {
	/* TODO */
} ICpuStateUnsavedRegisters;
#elif defined(__i386__)
#define HAVE_ICPUSTATEUNSAVEDREGISTERS 1
typedef struct {
	u32 ics_unsaved_gs;
} ICpuStateUnsavedRegisters;
#define ICpuStateUnsavedRegisters_SAVE(x) \
	((x).ics_unsaved_gs = __rdgs())
#define ICpuStateUnsavedRegisters_LOAD(x) \
	(__wrgs((x).ics_unsaved_gs))
#endif


#ifdef HAVE_ICPUSTATEUNSAVEDREGISTERS
PRIVATE ICpuStateUnsavedRegisters GDB_SuspendedThreadUnsavedState;
#endif /* HAVE_ICPUSTATEUNSAVEDREGISTERS */
PRIVATE struct icpustate *GDB_SuspendedThreadCpuState = NULL;
PRIVATE struct sig GDB_SuspendedThreadCpuStateChanged = SIG_INIT;


PRIVATE NONNULL((2)) struct icpustate *FCALL
GDB_SuspendThreadForDebugging(void *UNUSED(arg),
                              struct icpustate *__restrict state,
                              unsigned int UNUSED(reason),
                              struct rpc_syscall_info const *UNUSED(sc_info)) {
	struct task_connections cons;
	struct task *me = THIS_TASK;
	uintptr_t old_flags;
	bool was;
	old_flags = ATOMIC_FETCHOR(me->t_flags, TASK_FKEEPCORE);
	task_pushconnections(&cons);
	fpustate_save(); /* Make sure that our FPU state is saved, so that GDB can modify it. */
	COMPILER_BARRIER();
	/* Make sure that preemption is enabled. */
	was = PREEMPTION_ENABLED();
	PREEMPTION_ENABLE();
	COMPILER_BARRIER();

	/* Store our return cpu state as the context for the suspended thread.
	 * Then, broadcast `GDB_SuspendedThreadCpuStateChanged' to acknowledge
	 * that we've become suspended. */
	while (!ATOMIC_CMPXCH(GDB_SuspendedThreadCpuState, NULL, state)) {
		/* Another thread is still being suspended. - Wait for it to resume execution. */
		task_connect(&GDB_SuspendedThreadCpuStateChanged);
		if unlikely(ATOMIC_CMPXCH(GDB_SuspendedThreadCpuState, NULL, state)) {
			task_disconnectall();
			break;
		}
		task_waitfor_norpc_nx();
	}

	COMPILER_BARRIER();
#ifdef HAVE_ICPUSTATEUNSAVEDREGISTERS
	ICpuStateUnsavedRegisters_SAVE(GDB_SuspendedThreadUnsavedState);
#endif /* HAVE_ICPUSTATEUNSAVEDREGISTERS */
	COMPILER_WRITE_BARRIER();
	sig_broadcast(&GDB_SuspendedThreadCpuStateChanged);

	COMPILER_BARRIER();
	while (ATOMIC_READ(GDBThread_Current) == me) {
		task_connect(&GDBThread_CurrentChaned);
		if unlikely(ATOMIC_READ(GDBThread_Current) != me) {
			task_disconnectall();
			break;
		}
		task_waitfor_norpc_nx();
	}
	COMPILER_BARRIER();

	/* Reload our state from the suspended-thread field and broadcast
	 * `GDB_SuspendedThreadCpuStateChanged' to acknowledge that we've
	 * resumed execution. */
#ifdef HAVE_ICPUSTATEUNSAVEDREGISTERS
	ICpuStateUnsavedRegisters_LOAD(GDB_SuspendedThreadUnsavedState);
#endif /* HAVE_ICPUSTATEUNSAVEDREGISTERS */
	state = ATOMIC_XCH(GDB_SuspendedThreadCpuState, NULL);
	sig_broadcast(&GDB_SuspendedThreadCpuStateChanged);

	COMPILER_BARRIER();
	if (!was)
		PREEMPTION_DISABLE();
	COMPILER_BARRIER();
	task_popconnections(&cons);
	if (!(old_flags & TASK_FKEEPCORE))
		ATOMIC_FETCHAND(me->t_flags, ~TASK_FKEEPCORE);
	return state;
}

/* Get/Set the GDB thread that is currently being debugged.
 * Note that this is also used to control the enumeration of
 * threads apart of some given process.
 * @return: false: [GDB_SetCurrentThread] The specified thread could not be suspended,
 *                                        because it has already terminated. */
INTERN NONNULL((1)) bool
NOTHROW(FCALL GDB_SetCurrentThread)(struct task *__restrict thread) {
	COMPILER_BARRIER();
	if (thread != GDBThread_Current) {
		incref(thread);
		if (!GDB_DidSuspendOtherCPUs) {
			/* Suspend/Resume threads in non-stop mode. */
			REF struct task *old_thread;
			struct icpustate *old_state;
			assert(PREEMPTION_ENABLED());
			old_state = ATOMIC_READ(GDB_SuspendedThreadCpuState);
			if (thread != THIS_TASK) {
				/* Must suspend the new thread.
				 * We do this first so that `task_exec_asynchronous_rpc()' is able to return
				 * false in case the new thread has already been terminated. */
				if (!task_exec_asynchronous_rpc(thread, &GDB_SuspendThreadForDebugging, NULL,
				                                TASK_RPC_FWAITFOR, NULL)) {
					decref_unlikely(thread);
					return false;
				}
			}
			/* Exchange the thread that is actively being debugged. */
			old_thread = ATOMIC_XCH(GDBThread_Current, thread);
			assert((old_state == NULL) == (old_thread == THIS_TASK));
			/* Indicate that the . */
			sig_broadcast(&GDBThread_CurrentChaned);
			if (old_thread != THIS_TASK || thread != THIS_TASK) {
				/* Wait for the old thread to acknowledge having been resumed,
				 * and the new thread to acknowledge having been suspended. */
				while (ATOMIC_READ(GDB_SuspendedThreadCpuState) == old_state) {
					task_connect(&GDB_SuspendedThreadCpuStateChanged);
					if unlikely(ATOMIC_READ(GDB_SuspendedThreadCpuState) != old_state) {
						task_disconnectall();
						break;
					}
					task_waitfor_norpc_nx();
				}
			}
			decref_unlikely(old_thread);
		} else {
			/* Check if the new thread has already terminated. */
			assert(!PREEMPTION_ENABLED());
			if unlikely(ATOMIC_READ(thread->t_flags) & (TASK_FTERMINATED | TASK_FTERMINATING)) {
				decref_unlikely(thread);
				return false;
			}
			decref_unlikely(GDBThread_Current);
			GDBThread_Current = thread;
		}
	}
	COMPILER_BARRIER();
	return true;
}

/* Return the current process leader.
 * if the currently thread is a kernel-thread, `&_bootidle' is returned. */
INTERN WUNUSED ATTR_RETNONNULL struct task *
NOTHROW(FCALL GDB_GetCurrentProcess)(void) {
	struct task *result;
	result = GDB_GetCurrentThread();
	if (result->t_flags & TASK_FKERNTHREAD)
		return &_bootidle;
	result = task_getprocess_of(result);
	if unlikely(!result) /* Shouldn't ~really~ happen... (but let's be careful) */
		return &_bootidle;
	return result;
}

/* Get/Set a register for the current thread.
 * @param: regno: One of `GDB_REGISTER_<ARCH>_*'
 * @return: 0 : Invalid `regno'. */
INTERN NONNULL((2)) size_t
NOTHROW(FCALL GDB_GetRegister)(uintptr_t regno, void *buf, size_t bufsize) {
	struct task *thread = GDB_GetCurrentThread();
	if (thread == THIS_TASK)
		return GDB_GetTrapRegister(regno, buf, bufsize, thread);
	if (!GDB_DidSuspendOtherCPUs) {
		/* TODO: Move this into an arch-specific header */
#ifdef __x86_64__
		/* TODO */
#elif defined(__i386__)
		if (regno == GDB_REGISTER_I386_GS) {
			if (bufsize >= 4)
				UNALIGNED_SET32((u32 *)buf, GDB_SuspendedThreadUnsavedState.ics_unsaved_gs);
			return 4;
		}
#endif
		return GDB_GetICpuStateRegister(regno, buf, bufsize, thread, GDB_SuspendedThreadCpuState);
	}
	return GDB_GetSCpuStateRegister(regno, buf, bufsize, thread, thread->t_sched.s_state);
}

INTERN NONNULL((2)) size_t
NOTHROW(FCALL GDB_SetRegister)(uintptr_t regno, void const *buf, size_t bufsize) {
	struct task *thread = GDB_GetCurrentThread();
	if (thread == THIS_TASK)
		return GDB_SetTrapRegister(regno, buf, bufsize, thread);
	if (!GDB_DidSuspendOtherCPUs) {
		/* TODO: Move this into an arch-specific header */
#ifdef __x86_64__
		/* TODO */
#elif defined(__i386__)
		if (regno == GDB_REGISTER_I386_GS) {
			if (bufsize == 4)
				GDB_SuspendedThreadUnsavedState.ics_unsaved_gs = UNALIGNED_GET32((u32 *)buf);
			return 4;
		}
#endif
		return GDB_SetICpuStateRegister(regno, buf, bufsize, thread, &GDB_SuspendedThreadCpuState);
	}
	return GDB_SetSCpuStateRegister(regno, buf, bufsize, thread, &thread->t_sched.s_state);
}


/* Read/Write virtual memory in the context of the current thread.
 * Note that these functions are able to by-pass the usual access restrictions
 * imposed on memory, allowing writes to read-only memory and the like.
 * @param: allow_faults: When true, memory may be faulted in order to emulate the access.
 *                       This includes copy-on-write and load-on-access, as well as VIO
 *                       memory access.
 * @return: * : The number of bytes that could not be copied due to being faulty.
 *              Even when `allow_faults' is `true', this may be non-zero when the
 *              given `addr' isn't mapped, or accessing it causes some other kind
 *              of error. */
INTERN NONNULL((2)) size_t
NOTHROW(FCALL GDB_ReadMemory)(vm_virt_t addr, void *buf,
                              size_t bufsize, bool allow_faults) {
	size_t result;
	struct task *thread = GDB_GetCurrentThread();
	assert(!task_isconnected());
	result = vm_read_nopf(buf, thread->t_vm, (void const *)addr, bufsize);
	if (result && allow_faults) {
		if (GDB_DidSuspendOtherCPUs)
			PREEMPTION_ENABLE();
		assert(PREEMPTION_ENABLED());
		TRY {
			/* TODO: vm_read() may invoke RPC callbacks, which may in
			 *       turn throw exceptions such as `E_EXIT_THREAD' */
			vm_read(buf, thread->t_vm, (void const *)addr, bufsize, true);
			result = 0;
		} EXCEPT {
		}
		assert(PREEMPTION_ENABLED());
		if (GDB_DidSuspendOtherCPUs)
			PREEMPTION_DISABLE();
	}
	assert(!task_isconnected());
	return result;
}

INTERN NONNULL((2)) size_t
NOTHROW(FCALL GDB_WriteMemory)(vm_virt_t addr, void const *buf,
                               size_t bufsize, bool allow_faults) {
	size_t result;
	struct task *thread = GDB_GetCurrentThread();
	assert(!task_isconnected());
	result = vm_write_nopf(thread->t_vm, (void *)addr, buf, bufsize);
	if (result && allow_faults) {
		if (GDB_DidSuspendOtherCPUs)
			PREEMPTION_ENABLE();
		assert(PREEMPTION_ENABLED());
		TRY {
			/* TODO: vm_write() may invoke RPC callbacks, which may in
			 *       turn throw exceptions such as `E_EXIT_THREAD' */
			vm_write(thread->t_vm, (void *)addr, buf, bufsize, true);
			result = 0;
		} EXCEPT {
		}
		assert(PREEMPTION_ENABLED());
		if (GDB_DidSuspendOtherCPUs)
			PREEMPTION_DISABLE();
	}
	assert(!task_isconnected());
	return result;
}

INTERN NONNULL((2)) size_t
NOTHROW(FCALL GDB_ReadMemoryWithoutSwBreak)(vm_virt_t addr, void *buf,
                                            size_t bufsize, bool allow_faults) {
	size_t result;
	result = GDB_ReadMemory(addr, buf, bufsize, allow_faults);
	GDB_ExcludeSwBreak(addr, buf, bufsize - result);
	return result;
}
INTERN NONNULL((2)) size_t
NOTHROW(FCALL GDB_WriteMemoryWithoutSwBreak)(vm_virt_t addr, void *buf,
                                             size_t bufsize, bool allow_faults) {
	size_t result;
	GDB_IncludeSwBreak(addr, buf, bufsize);
	result = GDB_WriteMemory(addr, buf, bufsize, allow_faults);
	return result;
}


#ifdef GDB_HAVE_READMEMORY_MEMMEM
/* Perform a memory search for `pattern...+=pattern_length' within the given address range.
 * @return: * :            The base address where a matching pattern was found.
 * @return: (vm_virt_t)-1: The pattern could not be located.
 * @return: (vm_virt_t)-2: A faulty memory location was encountered. */
INTERN NONNULL((3)) vm_virt_t
NOTHROW(FCALL GDB_ReadMemory_memmem)(vm_virt_t addr, size_t length,
                                     void const *pattern, size_t pattern_length,
                                     bool allow_faults) {
#error TODO
}
#endif /* GDB_HAVE_READMEMORY_MEMMEM */


DECL_END

#endif /* !GUARD_MODGDB_THREAD_C */
