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
#ifndef GUARD_MODGDB_TRAP_C
#define GUARD_MODGDB_TRAP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/driver.h>
#include <kos/debugtrap.h>
#include <hybrid/atomic.h>
#include <sched/cpu.h>
#include <sched/signal.h>
#include <sched/mutex.h>
#include <assert.h>
#include <string.h>
#include <signal.h>
#include <kos/kernel/paging.h> /* KERNEL_DEBUG_STACKSIZE */

#include "gdb.h"

#if defined(__x86_64__) || defined(__i386__)
#include <asm/intrin.h>
#define GETSP() __rdsp()
#else
#error TODO
#endif


DECL_BEGIN

/* Register encoding for returning from a trap. */
#define GDB_RETURNMODE_NONE      0
#define GDB_RETURNMODE_ICPUSTATE 1
#define GDB_RETURNMODE_SCPUSTATE 2
#define GDB_RETURNMODE_UCPUSTATE 3
#define GDB_RETURNMODE_KCPUSTATE 4
#define GDB_RETURNMODE_LCPUSTATE 5
#define GDB_RETURNMODE_FCPUSTATE 6
#define GDB_RETURNMODE_MAX GDB_RETURNMODE_FCPUSTATE

INTERN void *GDB_ReturnStateAddress     = NULL;
INTERN unsigned int GDB_ReturnStateKind = GDB_RETURNMODE_NONE;
INTERN syscall_ulong_t GDBReason_TrapNo = 0;
INTERN char const *GDBReason_Registers  = NULL;

/* Set of `GDB_FEATURE_*' */
INTERN u32 GDB_Features = 0;

/* The master lock that must be held while GDB debugging is active. */
PRIVATE struct mutex GDB_TrapLock = MUTEX_INIT;

/* The stack used to host the GDB interpreter. */
INTERN byte_t GDB_TrapStack[KERNEL_DEBUG_STACKSIZE];


/* Get/Set a register of the cpu state with which GDB was entered. (aka.
 * the `state' argument passed to the original `GDB_Trap*CpuState()' function) */
INTERN NONNULL((2, 4)) size_t
NOTHROW(FCALL GDB_GetTrapRegister)(uintptr_t regno, void *buf, size_t bufsize,
                                   struct task *__restrict thread) {
	size_t result;
	switch (GDB_ReturnStateKind) {

	case GDB_RETURNMODE_ICPUSTATE:
		result = GDB_GetICpuStateRegister(regno, buf, bufsize, thread,
		                                  (struct icpustate *)GDB_ReturnStateAddress);
		break;

	case GDB_RETURNMODE_SCPUSTATE:
		result = GDB_GetSCpuStateRegister(regno, buf, bufsize, thread,
		                                  (struct scpustate *)GDB_ReturnStateAddress);
		break;

	case GDB_RETURNMODE_UCPUSTATE:
		result = GDB_GetUCpuStateRegister(regno, buf, bufsize, thread,
		                                  (struct ucpustate *)GDB_ReturnStateAddress);
		break;

	case GDB_RETURNMODE_KCPUSTATE:
		result = GDB_GetKCpuStateRegister(regno, buf, bufsize, thread,
		                                  (struct kcpustate *)GDB_ReturnStateAddress);
		break;

	case GDB_RETURNMODE_LCPUSTATE:
		result = GDB_GetLCpuStateRegister(regno, buf, bufsize, thread,
		                                  (struct lcpustate *)GDB_ReturnStateAddress);
		break;

	case GDB_RETURNMODE_FCPUSTATE:
		result = GDB_GetFCpuStateRegister(regno, buf, bufsize, thread,
		                                  (struct fcpustate *)GDB_ReturnStateAddress);
		break;

	default:
		result = 0;
		break;
	}
	return result;
}

INTERN NONNULL((2, 4)) size_t
NOTHROW(FCALL GDB_SetTrapRegister)(uintptr_t regno, void const *buf, size_t bufsize,
                                   struct task *__restrict thread) {
	size_t result;
	switch (GDB_ReturnStateKind) {

	case GDB_RETURNMODE_ICPUSTATE:
		result = GDB_SetICpuStateRegister(regno, buf, bufsize, thread,
		                                  (struct icpustate **)&GDB_ReturnStateAddress);
		break;

	case GDB_RETURNMODE_SCPUSTATE:
		result = GDB_SetSCpuStateRegister(regno, buf, bufsize, thread,
		                                  (struct scpustate **)&GDB_ReturnStateAddress);
		break;

	case GDB_RETURNMODE_UCPUSTATE:
		result = GDB_SetUCpuStateRegister(regno, buf, bufsize, thread,
		                                  (struct ucpustate **)&GDB_ReturnStateAddress);
		break;

	case GDB_RETURNMODE_KCPUSTATE:
		result = GDB_SetKCpuStateRegister(regno, buf, bufsize, thread,
		                                  (struct kcpustate **)&GDB_ReturnStateAddress);
		break;

	case GDB_RETURNMODE_LCPUSTATE:
		result = GDB_SetLCpuStateRegister(regno, buf, bufsize, thread,
		                                  (struct lcpustate **)&GDB_ReturnStateAddress);
		break;

	case GDB_RETURNMODE_FCPUSTATE:
		result = GDB_SetFCpuStateRegister(regno, buf, bufsize, thread,
		                                  (struct fcpustate **)&GDB_ReturnStateAddress);
		break;

	default:
		result = 0;
		break;
	}
	return result;
}

PRIVATE cpuid_t GDB_SleepingCPUs = 0;

PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL GDB_WaitForResume)(struct icpustate *__restrict state,
                                 void *args[CPU_IPI_ARGCOUNT]) {
	struct task_connections oldcon;
	struct task *me = THIS_TASK;
	uintptr_t old_flags;
	(void)args;
	old_flags = ATOMIC_FETCHOR(me->t_flags, TASK_FKEEPCORE);
	cpu_disable_preemptive_interrupts_nopr();
	task_pushconnections(&oldcon);
	COMPILER_BARRIER();
	ATOMIC_FETCHINC(GDB_SleepingCPUs);
	COMPILER_BARRIER();

	PREEMPTION_ENABLE();
	while (ATOMIC_READ(GDB_TrapLock.m_count) != 0) {
		task_connect(&GDB_TrapLock.m_unlock);
		if unlikely(ATOMIC_READ(GDB_TrapLock.m_count) == 0) {
			task_disconnectall();
			break;
		}
		task_waitfor_norpc_nx();
	}
	PREEMPTION_DISABLE();

	COMPILER_BARRIER();
	ATOMIC_FETCHDEC(GDB_SleepingCPUs);
	COMPILER_BARRIER();
	task_popconnections(&oldcon);
	cpu_enable_preemptive_interrupts_nopr();
	if (!(old_flags & TASK_FKEEPCORE))
		ATOMIC_FETCHAND(me->t_flags, ~TASK_FKEEPCORE);
	return state;
}


INTERN bool GDB_DidSuspendOtherCPUs = false;


/* Suspend all other CPUs now in order to enter full-stop mode.
 * No-Op if `GDB_DidSuspendOtherCPUs' was already set to `true' */
INTERN void NOTHROW(FCALL GDB_SuspendAllOtherCPUsNow)(void) {
	cpuid_t count;
	void *args[CPU_IPI_ARGCOUNT];
	if (GDB_DidSuspendOtherCPUs)
		return;
	assert(PREEMPTION_ENABLED());
	PREEMPTION_DISABLE();
	/* Disable preemptive interrupts (thus suspending all threads hosted by our own CPU) */
	cpu_disable_preemptive_interrupts_nopr();
	/* Broadcast an IPI to all other CPUS instructing them to wait for GDB to resume execution. */
	count = cpu_broadcastipi_notthis(&GDB_WaitForResume, args, CPU_IPI_FWAITFOR);
	while (ATOMIC_READ(GDB_SleepingCPUs) < count)
		task_pause();
	assert(ATOMIC_READ(GDB_SleepingCPUs) == count);
	ATOMIC_WRITE(GDB_DidSuspendOtherCPUs, true);
}


INTDEF struct kernel_debugtraps GDB_DebugTraps;

#ifdef __assertion_checkf
#define FAILF  __assertion_checkf
#else /* __assertion_checkf */
#define FAILF  __assertion_failedf
#endif /* !__assertion_checkf */


/* Saved error information of the host thread. */
PRIVATE struct exception_info GDB_OldErrorInfo;

/* Saved connections information of the host thread. */
PRIVATE struct task_connections GDB_OldConnections;


/* High-level function called from `GDB_TrapWithState' */
INTERN WUNUSED ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW(FCALL GDB_TrapWithStateImpl)(void *__restrict state, syscall_ulong_t trapNo,
                                     char const *trapRegs, unsigned int encoding) {
	uintptr_t old_flags;
	if unlikely(!((!trapRegs || ADDR_IS_KERNEL(trapRegs)) &&
	              ADDR_IS_KERNEL(state) &&
	              trapNo != 0 && trapNo < NSIG &&
	              encoding != GDB_RETURNMODE_NONE &&
	              encoding <= GDB_RETURNMODE_MAX)) {
		/* This check should really be an assertion, however if we did
		 * that and the problem was something to do with how another
		 * debug trap got here, we'd just recurse indefinitely.
		 * So to try and be a little bit more save, temporarily uninstall
		 * the trap handler used to integrate the GDB stub into the rest
		 * of the kernel, so we don't recurse.
		 * We should be save to assume that this would (normally) work,
		 * since `kernel_debugtraps_install()' already gets called during
		 * initialization of this driver, and one would assume that its
		 * counterpart `kernel_debugtraps_uninstall()' would work the same.
		 * (Yeesh, it gets real ugly when you're starting to mistrust the
		 *  systems meant to tell you who to mistrust...) */
		kernel_debugtraps_uninstall(&GDB_DebugTraps);
		FAILF("(!trapRegs || ADDR_IS_KERNEL(trapRegs)) && ADDR_IS_KERNEL(state) && trapNo != 0 && "
		      "trapNo < NSIG && encoding != GDB_RETURNMODE_NONE && encoding <= GDB_RETURNMODE_MAX",
		      "trapRegs = %p\n"
		      "state    = %p\n"
		      "trapNo   = %Iu\n"
		      "encoding = %u\n",
		      trapRegs, state,
		      trapNo, encoding);
		kernel_debugtraps_install(&GDB_DebugTraps);
		return state;
	}
	COMPILER_BARRIER();
	/* These assertions _really_ should never fail since the only scenario where they could
	 * would be when another assertion within our GDB stub gets triggered, and the kernel
	 * panic handler would try to recurse into our handlers.
	 * However this case already gets caught earlier on by the stack-checks below which are
	 * check if GDB gets invoked from the context of our dedicated stack (in which case they
	 * simply no-op out and let the normal panic handling to all the work) */
	assert(GDB_ReturnStateAddress == NULL);
	assert(GDB_ReturnStateKind == GDB_RETURNMODE_NONE);
	assert(GDBReason_TrapNo == 0);
	assert(GDBReason_Registers == NULL);
	COMPILER_BARRIER();
	GDB_ReturnStateAddress = state;
	GDB_ReturnStateKind    = encoding;
	GDBReason_TrapNo       = trapNo;
	GDBReason_Registers    = trapRegs;
	/* Though things like accessing faulty memory, the GDB interpreter
	 * loop may clobber the currently active exceptions.
	 * For this reason, save+restore error_info() while inside. */
	memcpy(&GDB_OldErrorInfo, error_info(), sizeof(struct exception_info));
	task_pushconnections(&GDB_OldConnections);
	COMPILER_BARRIER();

	COMPILER_BARRIER();
	/* Set the KEEPCORE flag for our hosting thread. */
	old_flags = ATOMIC_FETCHOR(THIS_TASK->t_flags, TASK_FKEEPCORE);
	COMPILER_BARRIER();

#if 0
	/* Clear the buffer of */
	GDBRemote_ClearBuffer();
	COMPILER_BARRIER();
#endif

	/* Disable preemption, preemptive interrupts, and suspend
	 * all other CPUs when GDB isn't running in non-stop mode. */
	if (GDB_Features & GDB_FEATURE_NONSTOP_MODE) {
		/* In non-stop mode, preemption has to be enabled at all times.
		 * Note that we can only enable preemption now, because if we
		 * were called by `GDBRemote_PutByte()', then we have to wait
		 * until our setup allows for `GDB_IsActive() == true' in order
		 * to correctly handle more data send by the GDB remote. */
		PREEMPTION_ENABLE();
		assert(!GDB_DidSuspendOtherCPUs);
	} else {
		cpuid_t count;
		void *args[CPU_IPI_ARGCOUNT];
		PREEMPTION_DISABLE();
		cpu_disable_preemptive_interrupts_nopr();
		count = cpu_broadcastipi_notthis(&GDB_WaitForResume, args, CPU_IPI_FWAITFOR);
		while (ATOMIC_READ(GDB_SleepingCPUs) < count)
			task_pause();
		assert(ATOMIC_READ(GDB_SleepingCPUs) == count);
		ATOMIC_WRITE(GDB_DidSuspendOtherCPUs, true);
	}
	COMPILER_BARRIER();

	/* Invoke the main GDB interpreter loop */
	GDB_Main();

	COMPILER_BARRIER();
	if (!(old_flags & TASK_FKEEPCORE))
		ATOMIC_FETCHAND(THIS_TASK->t_flags, ~TASK_FKEEPCORE);
	COMPILER_BARRIER();

	/* Make sure that we're no longer connected to anything! */
	COMPILER_BARRIER();
	task_disconnectall();
	COMPILER_BARRIER();

	COMPILER_BARRIER();
	/* Restore the currently active exceptions saved before. */
	task_popconnections(&GDB_OldConnections);
	memcpy(error_info(), &GDB_OldErrorInfo, sizeof(struct exception_info));
	state = GDB_ReturnStateAddress;
	GDBReason_Registers    = NULL;
	GDBReason_TrapNo       = 0;
	GDB_ReturnStateKind    = GDB_RETURNMODE_NONE;
	GDB_ReturnStateAddress = NULL;
	COMPILER_BARRIER();
	return state;
}

/* Low-level (assembly) wrapper around `GDB_TrapWithStateImpl'
 * This wrapper will load `GDB_TrapStack' before forwarding to `GDB_TrapWithStateImpl'
 * Then, once `GDB_TrapWithStateImpl' returns, it will restore the old stack and return. */
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW(FCALL GDB_TrapWithState)(void *__restrict state, syscall_ulong_t trapNo,
                                 char const *trapRegs, unsigned int encoding);



/* Special case: Dismiss attempts to recursively trap into GDB while already inside.
 *               While technically, this should never happen, if there's something
 *               wrong with our GDB stub driver, and it triggers one of this assertions,
 *               the kernel's panic handler would still try to invoke a debug trap,
 *               at which point we'd be right back here (since the GDB mutex would
 *               grant us access since we're still the same thread)
 *               For this reason, check if it looks like we're already inside of
 *               the GDB sub-system by looking at our stack pointer. */
LOCAL WUNUSED bool NOTHROW(FCALL GDB_IsRunningFromDebugStack)(void) {
	byte_t *sp = (byte_t *)GETSP();
	return unlikely(sp >= GDB_TrapStack && sp <= COMPILER_ENDOF(GDB_TrapStack));
}

PRIVATE void NOTHROW(FCALL GDB_AcquireTrapLock)(void) {
	if (!mutex_tryacquire(&GDB_TrapLock)) {
		struct task_connections cons;
		task_pushconnections(&cons);
again_connect:
		task_connect(&GDB_TrapLock.m_unlock);
		if (mutex_tryacquire(&GDB_TrapLock)) {
			task_disconnectall();
		} else {
			/* This literally is the only place I can think of that one
			 * can (and has to) use the NORPC variant of task_waitfor() */
			task_waitfor_norpc_nx();
			if (!mutex_tryacquire(&GDB_TrapLock))
				goto again_connect;
		}
		task_popconnections(&cons);
	}
	COMPILER_BARRIER();
}

PRIVATE NOBLOCK void NOTHROW(FCALL GDB_ReleaseTrapLock)(void) {
	bool didSuspend;
	didSuspend = ATOMIC_XCH(GDB_DidSuspendOtherCPUs, false);
	COMPILER_BARRIER();
	if (mutex_release_r(&GDB_TrapLock)) {
		COMPILER_BARRIER();
		if (didSuspend) {
			assert(!PREEMPTION_ENABLED());
			cpu_enable_preemptive_interrupts_nopr();
			PREEMPTION_ENABLE();
			while (ATOMIC_READ(GDB_SleepingCPUs) != 0)
				task_pause();
		}
		COMPILER_BARRIER();
	}
}



/* Check if the GDB sub-system is active.
 * This, alongside the `GDB_Trap*CpuState' are the only functions
 * which may be called from a context other than the active GDB thread.
 * The main purpose of this function is for the communications driver
 * to check if GDB is already running, and generate an explicit trap
 * if it isn't. */
INTERN WUNUSED bool FCALL GDB_IsActive(void) {
	return ATOMIC_READ(GDB_ReturnStateAddress) != NULL;
}


/* Try to trap into GDB, but return `NULL' if GDB is already active. */
INTERN NOBLOCK WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL GDB_TryTrapICpuState)(struct icpustate *__restrict state,
                                    syscall_ulong_t trapNo, char const *trapRegs) {
	struct icpustate *result;
	if (GDB_IsRunningFromDebugStack())
		return NULL;
	if (!mutex_tryacquire(&GDB_TrapLock))
		return NULL;
	result = (struct icpustate *)GDB_TrapWithState(state, trapNo, trapRegs,
	                                               GDB_RETURNMODE_ICPUSTATE);
	GDB_ReleaseTrapLock();
	return result;
}


/* Trigger GDB from the calling thread with the given register state.
 * GDB may update the given register state before returning its updated form to the caller. */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL GDB_TrapICpuState)(struct icpustate *__restrict state,
                                 syscall_ulong_t trapNo, char const *trapRegs) {
	struct icpustate *result;
	if (GDB_IsRunningFromDebugStack())
		return state;
	GDB_AcquireTrapLock();
	result = (struct icpustate *)GDB_TrapWithState(state, trapNo, trapRegs,
	                                               GDB_RETURNMODE_ICPUSTATE);
	GDB_ReleaseTrapLock();
	return result;
}

INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct scpustate *
NOTHROW(FCALL GDB_TrapSCpuState)(struct scpustate *__restrict state,
                                 syscall_ulong_t trapNo, char const *trapRegs) {
	struct scpustate *result;
	if (GDB_IsRunningFromDebugStack())
		return state;
	GDB_AcquireTrapLock();
	result = (struct scpustate *)GDB_TrapWithState(state, trapNo, trapRegs,
	                                               GDB_RETURNMODE_SCPUSTATE);
	GDB_ReleaseTrapLock();
	return result;
}

INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct ucpustate *
NOTHROW(FCALL GDB_TrapUCpuState)(struct ucpustate *__restrict state,
                                 syscall_ulong_t trapNo, char const *trapRegs) {
	struct ucpustate *result;
	if (GDB_IsRunningFromDebugStack())
		return state;
	GDB_AcquireTrapLock();
	result = (struct ucpustate *)GDB_TrapWithState(state, trapNo, trapRegs,
	                                               GDB_RETURNMODE_UCPUSTATE);
	GDB_ReleaseTrapLock();
	return result;
}

INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct kcpustate *
NOTHROW(FCALL GDB_TrapKCpuState)(struct kcpustate *__restrict state,
                                 syscall_ulong_t trapNo, char const *trapRegs) {
	struct kcpustate *result;
	if (GDB_IsRunningFromDebugStack())
		return state;
	GDB_AcquireTrapLock();
	result = (struct kcpustate *)GDB_TrapWithState(state, trapNo, trapRegs,
	                                               GDB_RETURNMODE_KCPUSTATE);
	GDB_ReleaseTrapLock();
	return result;
}

INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct lcpustate *
NOTHROW(FCALL GDB_TrapLCpuState)(struct lcpustate *__restrict state,
                                 syscall_ulong_t trapNo, char const *trapRegs) {
	struct lcpustate *result;
	if (GDB_IsRunningFromDebugStack())
		return state;
	GDB_AcquireTrapLock();
	result = (struct lcpustate *)GDB_TrapWithState(state, trapNo, trapRegs,
	                                               GDB_RETURNMODE_LCPUSTATE);
	GDB_ReleaseTrapLock();
	return result;
}

INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct fcpustate *
NOTHROW(FCALL GDB_TrapFCpuState)(struct fcpustate *__restrict state,
                                 syscall_ulong_t trapNo, char const *trapRegs) {
	struct fcpustate *result;
	if (GDB_IsRunningFromDebugStack())
		return state;
	GDB_AcquireTrapLock();
	result = (struct fcpustate *)GDB_TrapWithState(state, trapNo, trapRegs,
	                                               GDB_RETURNMODE_FCPUSTATE);
	GDB_ReleaseTrapLock();
	return result;
}



DECL_END

#endif /* !GUARD_MODGDB_TRAP_C */
