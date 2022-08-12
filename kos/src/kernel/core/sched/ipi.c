/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_SCHED_IPI_C
#define GUARD_KERNEL_SRC_SCHED_IPI_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/mman.h>
#include <kernel/printk.h>
#include <sched/cpu.h>
#include <sched/group.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/scheduler.h>
#include <sched/sig.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/sched/preemption.h>

#include <assert.h>
#include <inttypes.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>

DECL_BEGIN

#if 0
#define IPI_DEBUG(...) printk(KERN_DEBUG __VA_ARGS__)
#else
#define IPI_DEBUG(...) (void)0
#endif

#ifndef CONFIG_NO_SMP
/* Send an IPI to a specific target CPU.
 * The sync-variant will wait for the IPI to be acknowledged and completed before continuing,
 * which is quite the expensive operation, as it requires a second follow-up IPI by the target
 * cpu, which is used for confirming the completion of an IPI.
 * @return: true:  IPI delivery successful.
 * @return: false: The IPI could not be scheduled because the target
  *                CPU is offline, and `CPU_IPI_FWAKEUP' was not set. */
PUBLIC NOBLOCK ATTR_WEAK NONNULL((2, 3)) ATTR_SECTION(".text.kernel.cpu_sendipi_cpuset") unsigned int
NOTHROW(KCALL cpu_sendipi_cpuset)(cpuset_t targets, cpu_ipi_t func,
                                  void *args[CPU_IPI_ARGCOUNT], unsigned int flags) {
	unsigned int i, result = 0;
	if (flags & CPU_IPI_FWAKEUP) {
		for (i = 0; i < cpu_count; ++i) {
			if (!CPUSET_CONTAINS(targets, i))
				continue;
			if (cpu_sendipi(cpu_vector[i], func, args, flags))
				++result;
		}
	} else {
		/* Must  keep track of all CPUs where the send was successful,
		 * so that we can double-check  during a second pass that  all
		 * CPUs that aren't in deep-sleep afterwards have received the
		 * IPI.
		 * if we find any CPU that isn't in deep-sleep, we try to send
		 * the  IPI  once  again,  so-as  to  ensure  that  all   CPUs */
		cpuset_t success_set;
		bool did_find_new_cpus;
		CPUSET_CLEAR(success_set);
		for (i = 0; i < cpu_count; ++i) {
			if (!CPUSET_CONTAINS(targets, i))
				continue;
			if (cpu_sendipi(cpu_vector[i], func, args, flags)) {
				CPUSET_INSERT(success_set, i);
				++result;
			}
		}
		/* Second pass: Check  for cpus not in deep-sleep mode, that
		 *              aren't apart of the set of CPUs successfully
		 *              contacted. */
		COMPILER_BARRIER();
		do {
			did_find_new_cpus = false;
			for (i = 0; i < cpu_count; ++i) {
				struct cpu *c;
				if (!CPUSET_CONTAINS(targets, i))
					continue; /* Not an intended target. */
				if (CPUSET_CONTAINS(success_set, i))
					continue; /* Already contacted. */
				c = cpu_vector[i];
again_check_cpu_state:
				if (ATOMIC_READ(c->c_state) == CPU_STATE_DREAMING)
					continue; /* CPU is in deep sleep mode. */
				/* Try to send the IPI.
				 * If doing so fails, re-check the CPU's state, since it
				 * may have entered  deep-sleep mode in  the mean  time. */
				if (!cpu_sendipi(c, func, args, flags)) {
					assertf(c != THIS_CPU || (flags & CPU_IPI_FNOINTR) || PREEMPTION_ENABLED(),
					        "Without `CPU_IPI_FWAKEUP' and preemption disabled, including your own "
					        "CPU as target for a cpuset IPI also requires you to set the `CPU_IPI_FNOINTR' "
					        "flag since the IPI can only be executed on your own CPU while keeping interrupts "
					        "disabled. By setting `CPU_IPI_FWAKEUP', this scenario is instead ignored.");
					task_pause();
					goto again_check_cpu_state;
				}
				CPUSET_INSERT(success_set, i);
				++result;
				/* Force another  pass after  this one,  since
				 * we've managed to find more CPUs to contact. */
				did_find_new_cpus = true;
			}
		} while (did_find_new_cpus);
	}
	return result;
}

/* Same as the regular IPI functions, however the IPI is broadcast to all CPUs.
 * @return: * : The number of successfully delivered IPIs. */
PUBLIC NOBLOCK ATTR_WEAK NONNULL((1, 2)) ATTR_SECTION(".text.kernel.cpu_broadcastipi") unsigned int
NOTHROW(KCALL cpu_broadcastipi)(cpu_ipi_t func, void *args[CPU_IPI_ARGCOUNT], unsigned int flags) {
	unsigned int result;
	cpuset_t set;
	CPUSET_SETFULL(set);
	result = cpu_sendipi_cpuset(set, func, args, flags);
	return result;
}

/* Same as `cpu_broadcastipi()', but don't send the IPI to the calling CPU. */
PUBLIC NOBLOCK ATTR_WEAK NONNULL((1, 2)) ATTR_SECTION(".text.kernel.cpu_broadcastipi_notthis") unsigned int
NOTHROW(KCALL cpu_broadcastipi_notthis)(cpu_ipi_t func, void *args[CPU_IPI_ARGCOUNT], unsigned int flags) {
	unsigned int result;
	cpuset_t set;
	uintptr_t old_flags;
	struct task *me = THIS_TASK;
	CPUSET_SETFULL(set);
	/* Prevent our own thread from being moved to a different core,
	 * thus  ensuring that we can guaranty that our own CPU doesn't
	 * get the IPI.
	 * We don't want  to do  this by disabling  preemption, since  that
	 * could lead to unintended race conditions, since it would prevent
	 * our own CPU from servicing interrupts send by other CPUs. */
	old_flags = ATOMIC_FETCHOR(me->t_flags, TASK_FKEEPCORE);
	CPUSET_REMOVE(set, THIS_CPU->c_id);
	result = cpu_sendipi_cpuset(set, func, args, flags);
	if (!(old_flags & TASK_FKEEPCORE))
		ATOMIC_AND(me->t_flags, ~TASK_FKEEPCORE);
	return result;
}

#endif /* !CONFIG_NO_SMP */




#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL task_wake_ipi)(struct icpustate *__restrict state,
                             void *args[CPU_IPI_ARGCOUNT]) {
	/* Check if the thread switched CPUs in the mean time. */
	struct task *thread    = (struct task *)args[0];
	struct cpu *thread_cpu = ATOMIC_READ(thread->t_cpu);
	assert(!PREEMPTION_ENABLED());
	IPI_DEBUG("task_wake_ipi:%p,%p\n", thread_cpu, THIS_CPU);
	if likely(thread_cpu == THIS_CPU) {
		/* We're the ones hosting the thread, so we're
		 * responsible for doing the sporadic wake-up. */
		struct task *caller;
		/* Check if the thread has already terminated (in which case it can't be re-awoken) */
		IPI_DEBUG("task_wake_ipi:%#" PRIxPTR "\n", state);
		if (thread->t_flags & TASK_FTERMINATED)
			return state;
		caller = THIS_TASK;
		thread = sched_intern_localwake(thread_cpu, caller, thread,
		                                ((uintptr_t)args[1] & TASK_WAKE_FHIGHPRIO) != 0);
		if (thread != caller) {
			FORCPU(thread_cpu, thiscpu_sched_current) = thread;
			return CPU_IPI_MODE_SWITCH_TASKS;
		}
	}
#if 0 /* No need to send another IPI to the target CPU!                       \
       * Whenever a thread changes CPUs, a sporadic wakeup will be triggered, \
       * which is the same thing we were trying to do. */
	else {
		while (!cpu_sendipi(thread_cpu, &task_wake_ipi, args, CPU_IPI_FWAKEUP))
			task_pause();
	}
#endif
	return state;
}
#endif /* !CONFIG_NO_SMP */


#ifndef CONFIG_NO_SMP
static_assert(CPU_IPI_FWAITFOR == TASK_WAKE_FWAITFOR);
#endif /* !CONFIG_NO_SMP */

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
trigger_clone_trap(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	struct debugtrap_reason r;
	r.dtr_signo   = SIGTRAP; /* New process. */
	r.dtr_reason  = DEBUGTRAP_REASON_CLONE;
	ctx->rc_state = kernel_debugtrap_r(ctx->rc_state, &r);
}

/* Default task start flags. */
PUBLIC unsigned int task_start_default_flags = TASK_START_FNORMAL;

/* Start executing the given task on the CPU it has been assigned.
 * @param: flags: Set of `TASK_START_F*' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_start)(struct task *__restrict thread, unsigned int flags) {
	preemption_flag_t was;
	struct cpu *me;
#ifndef CONFIG_NO_SMP
	struct cpu *target_cpu;
#endif /* !CONFIG_NO_SMP */
	assertf(FORTASK(thread, this_sstate) != NULL,
	        "Task hasn't been given a restore-state at which execution can start");
	if (!(ATOMIC_FETCHOR(thread->t_flags, TASK_FSTARTING) & TASK_FSTARTING)) {
		if (kernel_debugtrap_enabled()) {
			if (!task_isaprocess(thread)) {
				struct scpustate *state;
				/* New thread.
				 * -> In this case, we must trigger a clone()
				 *    trap once the thread begins  execution. */
				state = FORTASK(thread, this_sstate);
				state = task_asyncrpc_push(state, &trigger_clone_trap, NULL);
				FORTASK(thread, this_sstate) = state;
			} else {
				struct debugtrap_reason r;
				/* New process. */
				r.dtr_signo  = SIGTRAP;
				r.dtr_reason = DEBUGTRAP_REASON_FORK;
				r.dtr_ptrarg = thread;
				kernel_debugtrap(&r);
			}
		}
	}

	/* Create the reference that is then inherited
	 * by  the  target  cpu's  scheduler   system. */
	incref(thread);

	/* Schedule on the current CPU. */
	for (;;) {
		uintptr_t old_flags;
		old_flags = ATOMIC_READ(thread->t_flags);
		if (old_flags & (TASK_FSTARTED | TASK_FRUNNING)) {
			assertf(!(old_flags & TASK_FRUNNING) || (old_flags & TASK_FSTARTED),
			        "old_flags = %#" PRIxPTR, old_flags);
			return;
		}
		FORTASK(thread, this_starttime) = ktime();
		FORTASK(thread, this_stoptime)  = FORTASK(thread, this_starttime);
		if (ATOMIC_CMPXCH_WEAK(thread->t_flags, old_flags,
		                       old_flags | (TASK_FSTARTED |
		                                    TASK_FRUNNING)))
			break;
	}
	preemption_pushoff(&was);
	me  = THIS_CPU;
	printk(KERN_TRACE "[sched:cpu#%u] Starting thread %p [tid=%" PRIuN(__SIZEOF_PID_T__) "]\n",
	       (unsigned int)thread->t_cpu->c_id, thread,
	       (unsigned int)task_getroottid_of(thread));
#ifndef CONFIG_NO_SMP
	/* NOTE: Before being started, the thread's CPU shouldn't be subject to change yet,
	 *       so we're safe in assuming that the thread's CPU won't change before  we're
	 *       done here. */
	target_cpu = thread->t_cpu;
	if (me != target_cpu) {
		sched_intern_addpending(target_cpu, thread);
		/* Wake up the targeted CPU, forcing it to load pending tasks. */
		cpu_wake(target_cpu);
	} else
#endif /* !CONFIG_NO_SMP */
	{
		struct task *caller;
		caller = THIS_TASK;
		thread = sched_intern_localadd(me, caller, thread,
		                               (flags & TASK_START_FHIGHPRIO) != 0 &&
		                               preemption_wason(&was));
		if (thread != caller) {
			/* Directly switch execution to the new thread,
			 * immediately allowing it to start  executing. */
			FORCPU(me, thiscpu_sched_current) = thread;
			cpu_run_current_and_remember_nopr(caller);
		}
	}
	preemption_pop(&was);
}

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_task_wake
#include "ipi-task-wake.c.inl"
#define DEFINE_task_wake_as
#include "ipi-task-wake.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_SCHED_IPI_C */
