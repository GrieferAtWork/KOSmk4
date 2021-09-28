/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MISC_EXCEPT_HANDLER_C
#define GUARD_KERNEL_SRC_MISC_EXCEPT_HANDLER_C 1

/* High-level exception handlers for translating exceptions thrown through
 * system calls or interrupts that  point to user-space return  locations.
 *
 * This also facilitates the handling of RPCs! */

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_RPC
#include <kernel/coredump.h>
#include <kernel/except.h>
#include <kernel/rt/except-handler.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/posix-signal.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/scheduler.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <signal.h>
#include <stddef.h>

DECL_BEGIN

/* TODO */




#ifdef CONFIG_NO_SMP
#define mycpu (&bootcpu)
#else /* CONFIG_NO_SMP */
#undef IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST
#if 0 /* Allow `userexcept_sysret_inject_safe()' to "heist" the quantum of unrelated threads */
#define IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST 1
#endif

PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_userexcept_sysret_inject_safe)(struct icpustate *__restrict state,
                                                 void *args[CPU_IPI_ARGCOUNT]) {
	REF struct task *target;
	struct cpu *mycpu, *target_cpu;
	struct task *caller;
	target = (REF struct task *)args[0];
	/* Re-check that the target thread has yet to start terminating. */
	if unlikely(ATOMIC_READ(target->t_flags) & (TASK_FTERMINATING | TASK_FTERMINATED)) {
		decref(target);
		return state;
	}
	caller     = THIS_TASK;
	mycpu      = caller->t_cpu;
	target_cpu = ATOMIC_READ(target->t_cpu);
	if unlikely(target_cpu != mycpu) {
		/* Re-deliver the IPI to yet another CPU (letting it bounce until we get it right) */
		while (!cpu_sendipi(target_cpu,
		                    &ipi_userexcept_sysret_inject_safe,
		                    args, /* inherit:reference:target */
		                    CPU_IPI_FWAKEUP))
			task_pause();
		return state;
	}
	userexcept_sysret_inject(target);
	if (caller != target) {
		struct task *next_thread;
#ifdef IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST
		next_thread = sched_intern_localwake(mycpu, caller, target,
		                                     ((syscall_ulong_t)(uintptr_t)args[1] & RPC_PRIORITY_F_HIGH) != 0);
#else /* IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST */
		next_thread = sched_intern_localwake(mycpu, caller, target, false);
#endif /* !IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST */
		if (next_thread != caller) {
			FORCPU(mycpu, thiscpu_sched_current) = next_thread;
			decref_unlikely(target);
			return CPU_IPI_MODE_SWITCH_TASKS;
		}
	}
	decref_unlikely(target);
	return state;
}
#endif /* !CONFIG_NO_SMP */


/* High-level wrapper for `userexcept_sysret_inject()' that makes all of
 * the right decisions to only ever call `userexcept_sysret_inject()' in
 * a valid context: using IPIs to make the call from the same CPU as the
 * one  currently hosting `thread', and ensuring that the thread has yet
 * to terminate.
 * Additionally, this function will make a call to `task_wake()'  once
 * the injection has completed, meaning that `thread' will wake up and
 * either immediatly  start executing  `userexcept_sysret()', or  will
 * handle a sporadic interrupt via a call to `task_serve()'.
 *
 * Note that the  actual injection may  complete asynchronously when  an
 * IPI  is used. Because of this, there is no way to check if the inject
 * was actually successful, or might have failed due to `thread' exiting
 * before the inject could be made.
 *
 * This function is used by `task_rpc_schedule()' (s.a. <kos/rpc.md>)
 *
 * @param: rpc_flags: Set of `0 | RPC_PRIORITY_F_HIGH', or one of
 *                    `RPC_PRIORITY_NORMAL',  `RPC_PRIORITY_HIGH'
 *                    Other flags are silently ignored. */
PUBLIC WUNUSED NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_inject_safe)(struct task *__restrict thread,
                                             syscall_ulong_t rpc_flags) {
	pflag_t was;
#ifndef CONFIG_NO_SMP
	struct cpu *mycpu;
	struct cpu *target_cpu;
	was        = PREEMPTION_PUSHOFF();
	mycpu      = THIS_CPU;
	target_cpu = ATOMIC_READ(thread->t_cpu);
	if (mycpu != target_cpu) {
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = (void *)incref(thread);
#ifdef IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST
		args[1] = (void *)rpc_flags;
#endif /* IPI_USEREXCEPT_SYSRET_INJECT_SAFE_ALLOW_QUANTUM_HEIST */
		while (!cpu_sendipi(target_cpu, &ipi_userexcept_sysret_inject_safe,
		                    args, CPU_IPI_FWAKEUP))
			task_pause();
		PREEMPTION_POP(was);
	} else
#endif /* !CONFIG_NO_SMP */
	{
		struct task *caller = THIS_TASK;
#ifdef CONFIG_NO_SMP
		was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		/* check if the thread has already terminated */
		if (thread->t_flags & (TASK_FTERMINATING | TASK_FTERMINATED)) {
			PREEMPTION_POP(was);
			return;
		}
		userexcept_sysret_inject(thread);
		if (caller != thread) {
			thread = sched_intern_localwake(mycpu, caller, thread,
			                                (rpc_flags & RPC_PRIORITY_F_HIGH) != 0 &&
			                                PREEMPTION_WASENABLED(was));
			if (thread != caller) {
				/* Immediately switch to the next thread thread. */
				FORCPU(mycpu, thiscpu_sched_current) = thread;
				cpu_run_current_and_remember_nopr(caller);
			}
		}
		PREEMPTION_POP(was);
	}
}


DECL_END
#endif /* CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_SRC_MISC_EXCEPT_HANDLER_C */
