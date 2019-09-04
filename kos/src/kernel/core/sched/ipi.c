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
#ifndef GUARD_KERNEL_SRC_SCHED_IPI_C
#define GUARD_KERNEL_SRC_SCHED_IPI_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/printk.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/signal.h>
#include <sched/smp.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <assert.h>

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
PUBLIC ATTR_WEAK NOBLOCK NONNULL((2, 3)) ATTR_SECTION(".text.kernel.cpu_sendipi_cpuset") cpuid_t
NOTHROW(KCALL cpu_sendipi_cpuset)(cpuset_t targets, cpu_ipi_t func,
                                  void *args[CPU_IPI_ARGCOUNT], unsigned int flags) {
	cpuid_t i, result = 0;
	for (i = 0; i < cpu_count; ++i) {
		if (!CPUSET_CONTAINS(targets, i))
			continue;
		if (cpu_sendipi(cpu_vector[i], func, args, flags))
			++result;
	}
	return result;
}

/* Same as the regular IPI functions, however the IPI is broadcast to all CPUs.
 * @return: * : The number of successfully delivered IPIs. */
PUBLIC ATTR_WEAK NOBLOCK NONNULL((1, 2)) ATTR_SECTION(".text.kernel.cpu_broadcastipi") cpuid_t
NOTHROW(KCALL cpu_broadcastipi)(cpu_ipi_t func, void *args[CPU_IPI_ARGCOUNT], unsigned int flags) {
	cpuid_t result;
	cpuset_t set;
	CPUSET_SETFULL(set);
	result = cpu_sendipi_cpuset(set, func, args, flags);
	return result;
}

/* Same as `cpu_broadcastipi()', but don't send the IPI to the calling CPU. */
PUBLIC ATTR_WEAK NOBLOCK NONNULL((1, 2)) ATTR_SECTION(".text.kernel.cpu_broadcastipi_notthis") cpuid_t
NOTHROW(KCALL cpu_broadcastipi_notthis)(cpu_ipi_t func, void *args[CPU_IPI_ARGCOUNT], unsigned int flags) {
	cpuid_t result;
	cpuset_t set;
	pflag_t was;
	CPUSET_SETFULL(set);
	was = PREEMPTION_PUSHOFF();
	CPUSET_REMOVE(set, THIS_CPU->c_id);
	result = cpu_sendipi_cpuset(set, func, args, flags);
	PREEMPTION_POP(was);
	return result;
}

#endif /* !CONFIG_NO_SMP */




/* Add the given task as running / sleeping within the current CPU.
 * NOTE: These functions inherit a reference to `thread' from the caller!
 * NOTE: Preemption must be disabled before this function may be called! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL cpu_addrunningtask)(/*in*/REF struct task *__restrict thread) {
	struct cpu *me = thread->t_cpu;
	assert(!PREEMPTION_ENABLED());
	assert(me == THIS_CPU);
	assert(thread->t_flags & TASK_FRUNNING);
	cpu_assert_integrity(/*need_caller:*/thread != THIS_TASK);
	/* Schedule for execution after the current thread. */
	thread->t_sched.s_running.sr_runprv                              = me->c_current;
	thread->t_sched.s_running.sr_runnxt                              = me->c_current->t_sched.s_running.sr_runnxt;
	thread->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = thread;
	me->c_current->t_sched.s_running.sr_runnxt                       = thread;
	cpu_assert_integrity();
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL cpu_addsleepingtask)(/*in*/REF struct task *__restrict thread) {
	struct cpu *me = thread->t_cpu;
	struct task **pnext, *next;
	assert(!PREEMPTION_ENABLED());
	assert(me == THIS_CPU);
	assert(!(thread->t_flags & TASK_FRUNNING));
	cpu_assert_integrity(/*need_caller:*/thread != THIS_TASK);
	/* Schedule for execution after the current thread. */
	pnext = &me->c_sleeping;
	while ((next = *pnext) != NULL) {
		if (thread->t_sched.s_asleep.ss_timeout <=
		    next->t_sched.s_asleep.ss_timeout)
			break;
		pnext = &next->t_sched.s_asleep.ss_tmonxt;
	}
	*pnext                            = thread;
	thread->t_sched.s_asleep.ss_pself = pnext;
	if ((thread->t_sched.s_asleep.ss_tmonxt = next) != NULL)
		next->t_sched.s_asleep.ss_pself = &thread->t_sched.s_asleep.ss_tmonxt;
	cpu_assert_integrity();
}


/* Remove a running or sleeping task `thread' from the current CPU.
 * NOTE: This function returns with a reference to `thread' handed to the caller.
 * NOTE: Preemption must be disabled before this function may be called! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL cpu_delrunningtask)(/*out*/REF struct task *__restrict thread) {
	struct cpu *me = thread->t_cpu;
	assert(!PREEMPTION_ENABLED());
	assert(me == THIS_CPU);
	assertf(thread != &FORCPU(me, _this_idle),
	        "Cannot remove the IDLE thread from a CPU");
	assert(thread->t_sched.s_running.sr_runnxt != NULL);
	assert(thread->t_sched.s_running.sr_runprv != NULL);
	cpu_assert_integrity();
	if (thread == me->c_current) {
		me->c_current = thread->t_sched.s_running.sr_runnxt;
		if unlikely(thread == me->c_current) {
			assert(thread->t_sched.s_running.sr_runnxt == thread);
			assert(thread->t_sched.s_running.sr_runprv == thread);
			if (FORCPU(me, _this_idle).t_sched.s_asleep.ss_pself) {
				/* The IDLE thread had been sleeping (time it out) */
				ATOMIC_FETCHOR(FORCPU(me, _this_idle).t_flags, TASK_FTIMEOUT);
				if ((*FORCPU(me, _this_idle).t_sched.s_asleep.ss_pself = FORCPU(me, _this_idle).t_sched.s_asleep.ss_tmonxt) != NULL)
					FORCPU(me, _this_idle).t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = FORCPU(me, _this_idle).t_sched.s_asleep.ss_pself;
			}
			/* Remove the last thread (replacing it with the IDLE thread) */
			FORCPU(me, _this_idle).t_sched.s_running.sr_runprv = &FORCPU(me, _this_idle);
			FORCPU(me, _this_idle).t_sched.s_running.sr_runnxt = &FORCPU(me, _this_idle);
			ATOMIC_FETCHOR(FORCPU(me, _this_idle).t_flags, TASK_FRUNNING);
			me->c_current = &FORCPU(me, _this_idle);
			goto done;
		}
	}
	assert(thread != me->c_current);
	assert(thread->t_sched.s_running.sr_runprv != thread);
	assert(thread->t_sched.s_running.sr_runnxt != thread);
	thread->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = thread->t_sched.s_running.sr_runnxt;
	thread->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = thread->t_sched.s_running.sr_runprv;
done:
	/* Clear the scheduling pointers to indicate the thread no longer has a designated role */
	thread->t_sched.s_running.sr_runprv = NULL;
	thread->t_sched.s_running.sr_runnxt = NULL;
	cpu_assert_integrity(/*need_caller:*/thread != THIS_TASK);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL cpu_delsleepingtask)(/*out*/REF struct task *__restrict thread) {
	struct cpu *me = thread->t_cpu;
	assert(!PREEMPTION_ENABLED());
	assert(me == THIS_CPU);
	assert(thread->t_sched.s_asleep.ss_pself != NULL);
	cpu_assert_integrity();
	if ((*thread->t_sched.s_asleep.ss_pself = thread->t_sched.s_asleep.ss_tmonxt) != NULL)
		thread->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = thread->t_sched.s_asleep.ss_pself;
	/* Clear the scheduling pointers to indicate the thread no longer has a designated role */
	thread->t_sched.s_asleep.ss_pself  = NULL;
	thread->t_sched.s_asleep.ss_tmonxt = NULL;
	cpu_assert_integrity(/*need_caller:*/thread != THIS_TASK);
}


#ifndef CONFIG_NO_SMP
PUBLIC NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL cpu_addpendingtask)(struct cpu *__restrict target,
                                   REF struct task *__restrict thread) {
	struct task *next;
	assert(thread->t_cpu == target);
	assert(!(thread->t_flags & TASK_FRUNNING));
	assert(thread->t_flags & TASK_FPENDING);
	next = ATOMIC_READ(target->c_pending);
	assert(next != NULL);
	if (!ATOMIC_CMPXCH(thread->t_sched.s_pending.ss_pennxt, NULL, next))
		return false;
	while (!ATOMIC_CMPXCH_WEAK(target->c_pending, next, thread)) {
		next = ATOMIC_READ(target->c_pending);
		assert(next != NULL);
		ATOMIC_WRITE(thread->t_sched.s_pending.ss_pennxt, next);
	}
	cpu_assert_integrity();
	return true;
}
#endif /* !CONFIG_NO_SMP */


#ifndef CONFIG_NO_SMP
/* Load all pending threads within the calling CPU.
 * NOTE: Preemption must be disabled before this function may be called!
 * @return: true:  At least 1 new task was added to the execution ring.
 * @return: false: No tasks were pending. */
INTERN NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL cpu_loadpending_chain)(struct cpu *__restrict me,
                                     REF struct task *__restrict chain) {
	REF struct task *next;
	struct task *first_new, *last_new;
	struct task *first_before, *first_after;
	assert(!PREEMPTION_ENABLED());
	cpu_assert_integrity();
	first_new = last_new = chain;
	next = chain->t_sched.s_pending.ss_pennxt;
	for (;;) {
		assert(!(chain->t_flags & TASK_FRUNNING));
		assert(chain->t_flags & TASK_FPENDING);
		assert(chain->t_cpu == me);
		/* Unset the WAKING bit to indicate that the sporadic wake-up caused
		 * by the hosting CPU being changed, will also automatically serve
		 * any prior call to `task_wake()', which may have gotten lost in
		 * the associated `task_wake_ipi()' when the hosting CPU no longer
		 * matched the expected host. */
		ATOMIC_FETCHAND(chain->t_flags, ~(TASK_FPENDING | TASK_FWAKING));
		/* Set the RUNNING bit to indicate that the thread will be part
		 * of the chain of tasks that are actively executed by our CPU. */
		ATOMIC_FETCHOR(chain->t_flags, TASK_FRUNNING);
		chain = next;
		if (chain == CPU_PENDING_ENDOFCHAIN)
			break;
		next                                  = chain->t_sched.s_pending.ss_pennxt;
		last_new->t_sched.s_running.sr_runnxt = chain;
		chain->t_sched.s_running.sr_runprv    = last_new;
		last_new                              = chain;
	}
	/* Insert all of the new tasks to-be executed after the current one:
	 *      first_before | first_after
	 *                   ^
	 *     +-------------+-------------+
	 *     |                           |
	 *     first_new            last_new
	 */
	first_before                              = me->c_current;
	first_after                               = first_before->t_sched.s_running.sr_runnxt;
	first_new->t_sched.s_running.sr_runprv    = first_before;
	first_before->t_sched.s_running.sr_runnxt = first_new;
	last_new->t_sched.s_running.sr_runnxt     = first_after;
	first_after->t_sched.s_running.sr_runprv  = last_new;
	cpu_assert_integrity();
}

PUBLIC NOBLOCK bool NOTHROW(KCALL cpu_loadpending)(void) {
	REF struct task *chain;
	struct cpu *me = THIS_CPU;
	assert(!PREEMPTION_ENABLED());
	chain = ATOMIC_XCH(me->c_pending, CPU_PENDING_ENDOFCHAIN);
	if (chain == CPU_PENDING_ENDOFCHAIN)
		return false;
	cpu_loadpending_chain(me, chain);
	return true;
}
#endif /* !CONFIG_NO_SMP */



#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
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
		struct task *caller, *next;
		uintptr_t flags = thread->t_flags;
		/* Check if the thread has already terminated (in which case it can't be re-awoken) */
		IPI_DEBUG("task_wake_ipi:%#Ix\n", state);
		if (flags & TASK_FTERMINATED)
			return state;
		cpu_assert_integrity();
		caller = THIS_TASK;
		next   = caller->t_sched.s_running.sr_runnxt;
		if (flags & TASK_FRUNNING) {
			if ((unsigned int)(uintptr_t)args[1] & TASK_WAKE_FLOWPRIO)
				goto unset_waking;
			/* The thread is already running.
			 * In this case, re-schedule the thread to-be executed next. */
			thread->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = thread->t_sched.s_running.sr_runnxt;
			thread->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = thread->t_sched.s_running.sr_runprv;
		} else {
			ATOMIC_FETCHOR(thread->t_flags, TASK_FRUNNING);
			/* The thread was sleeping. - Wake it up (before you go go...) */
			if ((*thread->t_sched.s_asleep.ss_pself = thread->t_sched.s_asleep.ss_tmonxt) != NULL)
				thread->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = thread->t_sched.s_asleep.ss_pself;
		}
		thread->t_sched.s_running.sr_runprv = caller;
		thread->t_sched.s_running.sr_runnxt = next;
		caller->t_sched.s_running.sr_runnxt = thread;
		next->t_sched.s_running.sr_runprv   = thread;
unset_waking:
		ATOMIC_FETCHAND(thread->t_flags, ~TASK_FWAKING);
		cpu_assert_integrity();
		/* Indicate that we wish to switch tasks. */
		if ((unsigned int)(uintptr_t)args[1] & TASK_WAKE_FHIGHPRIO)
			return CPU_IPI_MODE_SWITCH_TASKS;
	}
#if 0 /* No need to send another IPI to the target CPU!                            \
       * Whenever a thread changes CPUs, a sporadic wakeup will be triggered,      \
       * which is the same thing we were trying to do. Additionally, that sporadic \
       * wake-up will have already unset the `TASK_FWAKING' bit for us! */
	else {
		while (!cpu_sendipi(thread_cpu, &task_wake_ipi, args, CPU_IPI_FWAKEUP))
			task_pause();
	}
#endif
	return state;
}
#endif /* !CONFIG_NO_SMP */


#ifndef CONFIG_NO_SMP
STATIC_ASSERT(CPU_IPI_FWAITFOR == TASK_WAKE_FWAITFOR);
#endif /* !CONFIG_NO_SMP */


/* Re-schedule the given `thread' if it was unscheduled (entered a sleeping state).
 * Using this function, a ~sporadic interrupt~ is implemented.
 * If the thread hasn't been unscheduled, this function is a no-op.
 * NOTE: This function is used in the implementation of `sig_send'
 * @return: true:  The task was woken, or wasn't sleeping.
 * @return: false: The given task has terminated. */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL task_wake)(struct task *__restrict thread,
                         unsigned int flags) {
	uintptr_t old_flags;
	pflag_t was;
	struct cpu *mycpu;
	assert(THIS_TASK->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv == THIS_TASK &&
	       THIS_TASK->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt == THIS_TASK);
	do {
		old_flags = ATOMIC_READ(thread->t_flags);
		if (old_flags & TASK_FTERMINATED) {
			IPI_DEBUG("task_wake(%p):terminated\n", thread);
			return false; /* The thread has already terminated. */
		}
		if (old_flags & TASK_FWAKING) {
			IPI_DEBUG("task_wake(%p):already\n", thread);
			return true; /* A wake-up is already pending. */
		}
	} while (!ATOMIC_CMPXCH_WEAK(thread->t_flags, old_flags, old_flags | TASK_FWAKING));
	/* Now we're responsible to see to it that the thread either gets
	 * woken, or that the `TASK_FTERMINATED' gets set before then.
	 * NOTE: We can't actually track the later happening on other cores,
	 *       but that's actually OK, since the wakeup simply got lost
	 *       while the task was already dying, which can only happen
	 *       when the thread was already in a state where it wasn't
	 *       guarantied to be responsive to wakeup commands. */
	was   = PREEMPTION_PUSHOFF();
	mycpu = THIS_CPU;
#ifndef CONFIG_NO_SMP
	if (thread->t_cpu != mycpu) {
		/* Use an IPI to wake up the thread! */
		void *args[CPU_IPI_ARGCOUNT];
		args[0] = thread;
		args[1] = (void *)(uintptr_t)flags;
		IPI_DEBUG("task_wake(%p):ipi\n", thread);
		while (!cpu_sendipi(thread->t_cpu, &task_wake_ipi, args,
		                    CPU_IPI_FWAKEUP | (flags & TASK_WAKE_FWAITFOR)))
			task_pause();
		PREEMPTION_POP(was);
	} else
#endif /* !CONFIG_NO_SMP */
	{
		/* Wake on the current thread. */
		struct task *caller, *next;
		uintptr_t thread_flags;
		IPI_DEBUG("task_wake(%p):me\n", thread);
		COMPILER_READ_BARRIER();
		thread_flags = thread->t_flags;
		COMPILER_READ_BARRIER();
#ifndef CONFIG_NO_SMP
		if (thread_flags & (TASK_FTERMINATED | TASK_FPENDING))
#else /* !CONFIG_NO_SMP */
		if (thread_flags & (TASK_FTERMINATED))
#endif /* CONFIG_NO_SMP */
		{
			/* The thread has already terminated, but the wake-up was requested at
			 * a time when the thread wasn't. So between then and now, the thread
			 * must have executed at least for a while, meaning it did get a wake-up
			 * for one reason or another, which is good enough for us!
			 *
			 * On the other hand, a task that is intended to, or already was added
			 * as a pending task within our CPU is guarantied to receive a wake-up
			 * once that request goes through (which may actually happen as soon as
			 * we re-enable preemption, which may be done by the next line) */
			IPI_DEBUG("task_wake(%p):terminated\n", thread);
			PREEMPTION_POP(was);
			return true;
		}
		cpu_assert_integrity();
		caller = THIS_TASK;
		next   = caller->t_sched.s_running.sr_runnxt;
		if (thread_flags & TASK_FRUNNING) {
			if (flags & TASK_WAKE_FLOWPRIO)
				goto unset_waking; /* Don't re-prioritize the target thread. */
			/* The thread is already running.
			 * In this case, re-schedule the thread to-be executed next. */
			thread->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = thread->t_sched.s_running.sr_runnxt;
			thread->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = thread->t_sched.s_running.sr_runprv;
			/* Must re-load `next', as that field may have been modified by the unlink process above
			 * (in case `thread' was already the successor of `caller') */
			next = caller->t_sched.s_running.sr_runnxt;
		} else {
			ATOMIC_FETCHOR(thread->t_flags, TASK_FRUNNING);
			/* The thread was sleeping. - Wake it up */
			if ((*thread->t_sched.s_asleep.ss_pself = thread->t_sched.s_asleep.ss_tmonxt) != NULL)
				thread->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = thread->t_sched.s_asleep.ss_pself;
		}
		thread->t_sched.s_running.sr_runprv = caller;
		thread->t_sched.s_running.sr_runnxt = next;
		caller->t_sched.s_running.sr_runnxt = thread;
		next->t_sched.s_running.sr_runprv   = thread;
		assert(caller->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv == caller &&
		       caller->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt == caller);
		assert(thread->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv == thread &&
		       thread->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt == thread);
unset_waking:
		ATOMIC_FETCHAND(thread->t_flags, ~TASK_FWAKING);
		cpu_assert_integrity();
		if (PREEMPTION_WASENABLED(was)) {
			if (flags & TASK_WAKE_FHIGHPRIO) {
				/* End the current quantum prematurely. */
				cpu_quantum_end();
				/* Directly switch execution to the thread in question,
				 * immediately allowing it to resume executing. */
				mycpu->c_current = thread;
				cpu_run_current_and_remember(caller);
				/* At this point, `thread' got to execute for a while, and we're
				 * back in business, with preemption enabled once again. */
			}
			PREEMPTION_ENABLE();
		}
		/*PREEMPTION_POP(was);*/
	}
	return true;
}





PUBLIC void NOTHROW(KCALL cpu_deepsleep)(void) {
	struct cpu *me = THIS_CPU;
	assertf(THIS_TASK == &FORCPU(me, _this_idle),
	        "cpu_deepsleep() may only be called form a cpu's IDLE thread!");
	assertf(me->c_current == &FORCPU(me, _this_idle),
	        "cpu_deepsleep() may only be called form a cpu's IDLE thread!");
	assert(FORCPU(me, _this_idle).t_flags & TASK_FRUNNING);
	assert(me->c_state == CPU_STATE_RUNNING);
again:
	PREEMPTION_DISABLE();
again_already_disabled:
	ATOMIC_WRITE(me->c_state, CPU_STATE_FALLING_ASLEEP);
	cpu_assert_integrity();
#ifndef CONFIG_NO_SMP
	assert(!PREEMPTION_ENABLED());
	if (cpu_loadpending())
		goto yield_and_return;
#endif /* !CONFIG_NO_SMP */
	assert((FORCPU(me, _this_idle).t_sched.s_running.sr_runnxt == &FORCPU(me, _this_idle)) ==
	       (FORCPU(me, _this_idle).t_sched.s_running.sr_runprv == &FORCPU(me, _this_idle)));
	if (FORCPU(me, _this_idle).t_sched.s_running.sr_runnxt != &FORCPU(me, _this_idle))
		goto yield_and_return; /* There are other threads that are pending. */
#ifndef CONFIG_NO_SMP
	/* Check if there are IPIs that are pending
	 * execution, as send from other cores. */
	if (cpu_hwipi_pending()) {
		ATOMIC_WRITE(me->c_state, CPU_STATE_RUNNING);
		cpu_ipi_service();
#ifdef PREEMPTION_ENABLE_P
		/* Use `PREEMPTION_ENABLE_P()' in order to ensure that interrupts had at least
		 * a single instruction during which they could be served, in case GCC decides
		 * to move the `PREEMPTION_DISABLE()' above in such a manner that it would follow
		 * our `PREEMPTION_ENABLE()' immediately. */
		PREEMPTION_ENABLE_P();
#else
		PREEMPTION_ENABLE();
#endif
		goto again;
	}
	/* TODO: Check `ipi_inuse' for allocated, but  */

#endif /* !CONFIG_NO_SMP */

	/* Check if there are any sleeping tasks with the FKEEPCORE flag set.
	 * NOTE: Because the `TASK_FKEEPCORE' flag is private to each thread,
	 *       alongside the fact that we're the ones that would allow those
	 *       threads to run, we know for a fact that the flag cannot possibly
	 *       change for any of our own, private sleeping thread. */
	{
		struct task *iter;
		iter = me->c_sleeping;
		for (; iter; iter = iter->t_sched.s_asleep.ss_tmonxt,
		             assert(iter != me->c_sleeping)) {
			assert(iter->t_sched.s_asleep.ss_pself);
			assert(*iter->t_sched.s_asleep.ss_pself == iter);
			if (!(iter->t_flags & TASK_FKEEPCORE))
				continue;
			/* There are sleeping threads with the KEEPCORE flag set... */
			ATOMIC_WRITE(me->c_state, CPU_STATE_RUNNING);
			if (cpu_swipi_pending()) {
				cpu_ipi_service();
				PREEMPTION_ENABLE();
				goto again;
			}
			PREEMPTION_ENABLE_WAIT();
			goto again;
		}
	}
#ifndef CONFIG_NO_SMP
	if (me != &_bootcpu) {
		struct cpu *transfer_target;
		struct task *pending_first;
		struct task *pending_last;
		struct task *pending_next;
		cpu_disable_preemptive_interrupts_nopr();

		if ((pending_first = me->c_sleeping) != NULL) {
			assert(!(pending_first->t_flags & TASK_FRUNNING));
			pending_last   = pending_first;
			me->c_sleeping = NULL;
			/* Secondary core: Transfer all remaining tasks to another core
			 * XXX: We can really use any core that's currently online for this,
			 *      but for now we always use the boot-core. */
			transfer_target = &_bootcpu;
			assert(transfer_target != me);
			for (;;) {
				assert(!(pending_last->t_flags & TASK_FRUNNING));
				ATOMIC_FETCHOR(pending_last->t_flags, TASK_FPENDING);
				ATOMIC_WRITE(pending_last->t_cpu, transfer_target);
				printk(KERN_INFO "[sched:cpu#%u] Transfer sleeping thread %p [pid=%u] to cpu #%u\n",
				       (unsigned int)me->c_id, pending_last, task_getroottid_of_s(pending_last),
				       (unsigned int)transfer_target->c_id);
				pending_next = pending_last->t_sched.s_asleep.ss_tmonxt;
				if (!pending_next)
					break;
				pending_last->t_sched.s_asleep.ss_tmonxt  = NULL;
				pending_last->t_sched.s_pending.ss_pennxt = pending_next;
				pending_last                              = pending_next;
			}
			do {
				pending_next = ATOMIC_READ(transfer_target->c_pending);
				pending_last->t_sched.s_pending.ss_pennxt = pending_next;
			} while (!ATOMIC_CMPXCH_WEAK(transfer_target->c_pending, pending_next, pending_first));
			/* Wake the target CPU, so it can continue working on our sleeping tasks. */
			cpu_wake(transfer_target);
		}
		cpu_assert_integrity();
		/* Enter deep-sleep mode. */
		printk(KERN_INFO "[sched:cpu#%u][+] Enter deep-sleep\n", (unsigned int)me->c_id);
		cpu_enter_deepsleep(me);
		printk(KERN_INFO "[sched:cpu#%u][-] Leave deep-sleep\n", (unsigned int)me->c_id);
		return;
	}
#endif /* !CONFIG_NO_SMP */
	/* We're the boot CPU, which means we're not allowed to go to sleep. */
	ATOMIC_WRITE(me->c_state, CPU_STATE_RUNNING);
	if (cpu_swipi_pending()) {
		cpu_ipi_service();
		PREEMPTION_ENABLE();
		goto again;
	}
	{
		struct task *iter;
		iter = me->c_sleeping;
		for (; iter; iter = iter->t_sched.s_asleep.ss_tmonxt,
		             assert(iter != me->c_sleeping)) {
			assert(iter->t_sched.s_asleep.ss_pself);
			assert(*iter->t_sched.s_asleep.ss_pself == iter);
			if (iter->t_sched.s_asleep.ss_timeout.q_jtime == (jtime_t)-1)
				continue;
			/* Must keep jiffies running so-as to be able to service timeouts. */
			PREEMPTION_ENABLE_WAIT();
			goto again;
		}
	}
#ifndef CONFIG_NO_SMP
	if (cpu_online_count > 1) {
		/* NOTE: Don't disable preemptive interrupts, so-as to keep jiffies running. */
		/* Re-enable preemption until the end of the current quantum. */
		PREEMPTION_ENABLE_WAIT_DISABLE();
	} else
#endif
	{
		cpu_disable_preemptive_interrupts_nopr();
		/* Wait for a single interrupt */
		PREEMPTION_ENABLE_WAIT_DISABLE();
		cpu_enable_preemptive_interrupts_nopr();
	}
	goto again_already_disabled;
yield_and_return:
	/* Switch back to a running state. */
	ATOMIC_WRITE(me->c_state, CPU_STATE_RUNNING);
	if (cpu_swipi_pending()) {
		cpu_ipi_service();
		PREEMPTION_ENABLE();
		goto again;
	}
	/* End the current quantum prematurely. */
	cpu_quantum_end();
	/* Remove the IDLE thread from the running-ring. */
	cpu_assert_integrity();
	me->c_current = FORCPU(me, _this_idle).t_sched.s_running.sr_runnxt;
	assert(FORCPU(me, _this_idle).t_flags & TASK_FRUNNING);
	ATOMIC_FETCHAND(FORCPU(me, _this_idle).t_flags, ~TASK_FRUNNING);
	assert(me->c_current != &FORCPU(me, _this_idle));
	FORCPU(me, _this_idle).t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = FORCPU(me, _this_idle).t_sched.s_running.sr_runprv;
	FORCPU(me, _this_idle).t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = FORCPU(me, _this_idle).t_sched.s_running.sr_runnxt;
	FORCPU(me, _this_idle).t_sched.s_running.sr_runnxt = NULL;
	FORCPU(me, _this_idle).t_sched.s_running.sr_runprv = NULL;
	cpu_assert_integrity(/*need_caller:*/false);
	/* Switch context to the next task. */
	cpu_run_current_and_remember(&FORCPU(me, _this_idle));
	assert(FORCPU(me, _this_idle).t_flags & TASK_FRUNNING);
}


FUNDEF NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct task *
NOTHROW(FCALL task_start)(struct task *__restrict thread, unsigned int flags) {
	pflag_t was;
#ifndef CONFIG_NO_SMP
	struct cpu *mycpu, *target_cpu;
#endif /* !CONFIG_NO_SMP */
	assertf(thread->t_sched.s_state != NULL,
	        "Task hasn't been given a restore-state at which execution can start");
#ifndef CONFIG_NO_SMP
	assertf(!(thread->t_flags & (TASK_FPENDING | TASK_FRUNNING)),
	        "Attempted to start a task with the `TASK_FPENDING' or `TASK_FRUNNING' flag already set");
#else /* !CONFIG_NO_SMP */
	assertf(!(thread->t_flags & TASK_FRUNNING),
	        "Attempted to start a task with the `TASK_FRUNNING' flag already set");
#endif /* CONFIG_NO_SMP */

	/* Create the reference that is then inherited
	 * by the target cpu's scheduler system. */
	incref(thread);

	was = PREEMPTION_PUSHOFF();
#ifndef CONFIG_NO_SMP
	mycpu      = THIS_CPU;
	target_cpu = ATOMIC_READ(thread->t_cpu);
	printk(KERN_INFO "[sched:cpu#%u] Starting thread %p (tid=%u)\n",
	       (unsigned int)target_cpu->c_id, thread,
	       (unsigned int)task_getroottid_of_s(thread));
	if (mycpu != target_cpu) {
		ATOMIC_FETCHOR(thread->t_flags, TASK_FPENDING);
#ifndef NDEBUG
		{
			bool ok = cpu_addpendingtask(target_cpu, thread);
			assert(ok);
		}
#else /* !NDEBUG */
		cpu_addpendingtask(target_cpu, thread);
#endif /* NDEBUG */
		/* Wake up the targeted CPU, forcing it to load pending tasks. */
		cpu_wake(target_cpu);
		PREEMPTION_POP(was);
	} else
#else /* !CONFIG_NO_SMP */
	printk(KERN_INFO "[sched] Starting thread %p (tid=%u)\n",
	       (unsigned int)task_getroottid_of_s(thread));
#endif /* CONFIG_NO_SMP */
	{
		struct task *caller, *next;
		/* Schedule on the current CPU. */
		ATOMIC_FETCHOR(thread->t_flags, TASK_FRUNNING);
		cpu_assert_integrity();
		caller = THIS_TASK;
		next   = caller->t_sched.s_running.sr_runnxt;
		caller->t_sched.s_running.sr_runnxt = thread;
		thread->t_sched.s_running.sr_runprv = caller;
		thread->t_sched.s_running.sr_runnxt = next;
		next->t_sched.s_running.sr_runprv   = thread;
		cpu_assert_integrity();
		if (PREEMPTION_WASENABLED(was)) {
			if (flags & TASK_START_FHIGHPRIO) {
				/* End the current quantum prematurely. */
				cpu_quantum_end();
				/* Directly switch execution to the new thread,
				 * immediately allowing it to start executing. */
				mycpu->c_current = thread;
				cpu_run_current_and_remember(caller);
				/* At this point, `thread' got to execute for a while, and we're
				 * back in business, with preemption enabled once again. */
				assert(PREEMPTION_ENABLED());
			}
			PREEMPTION_ENABLE();
		}
	}
	return thread;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_IPI_C */
