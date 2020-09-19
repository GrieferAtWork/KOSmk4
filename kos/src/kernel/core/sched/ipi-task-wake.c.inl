/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "ipi.c"
//#define DEFINE_task_wake
#define DEFINE_task_wake_as
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_task_wake) + defined(DEFINE_task_wake_as)) != 1
#error "Invalid configuration (must define exactly one of these macros)"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_task_wake
/* Re-schedule the given `thread' if it was unscheduled (entered a sleeping state).
 * Using this function, a ~sporadic interrupt~ is implemented.
 * If the thread hasn't been unscheduled, this function is a no-op.
 * NOTE: This function is used in the implementation of `sig_send'
 * @param: flags:  Set of `TASK_WAKE_F*'
 * @return: true:  The task was woken, or wasn't sleeping.
 * @return: false: The given task has terminated. */
PUBLIC NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL task_wake)(struct task *__restrict thread,
                         unsigned int flags)
#elif defined(DEFINE_task_wake_as)
/* Wake `thread' while impersonating `caller', where `caller' must some
 * running thread from the calling CPU. - This function is used to wake
 * up waiting threads during task exit, where at the point where the exit
 * status is broadcast, the exiting thread (THIS_TASK) can no longer be
 * used to send signals (since `task_wake()' has to look at things such
 * as the prev/next thread within the scheduler ring, which would have
 * already become invalid at that point, since the true calling thread
 * could no longer be considered apart of the scheduler ring)
 *
 * When calling this function, the caller must ensure that their current
 * CPU will no change, which can be done most easily by simply disabling
 * preemption, or setting the `TASK_FKEEPCORE' flag.
 *
 * The given `caller' is used when `thread' is running on `THIS_CPU',
 * in which case `thread' will be re-scheduled in relation to `caller',
 * where-as the regular `task_wake()' does this re-scheduling in relation
 * to `THIS_TASK'
 *
 * @param: flags:  Set of `TASK_WAKE_F*'
 * @return: true:  The task was woken, or wasn't sleeping.
 * @return: false: The given task has terminated. */
PUBLIC NOBLOCK NONNULL((1, 2)) __BOOL
NOTHROW(FCALL task_wake_as)(struct task *thread, struct task *caller,
                            unsigned int flags)
#endif /* ... */
{
	uintptr_t old_flags;
	pflag_t was;
	struct cpu *mycpu;
#ifdef DEFINE_task_wake_as
	assertf(!PREEMPTION_ENABLED() || (PERTASK_GET(this_task.t_flags) & TASK_FKEEPCORE),
	        "You must ensure that you're core won't change before calling `task_wake_as()'");
	assertf(caller && caller->t_cpu == THIS_CPU,
	        "You may only impersonate other threads from your own CPU");
	assert(caller->t_sched.s_running.sr_runnxt &&
	       caller->t_sched.s_running.sr_runprv &&
	       caller->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv == caller &&
	       caller->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt == caller);
#else /* DEFINE_task_wake_as */
	assert(PERTASK_GET(this_task.t_sched.s_running.sr_runnxt) &&
	       PERTASK_GET(this_task.t_sched.s_running.sr_runprv) &&
	       PERTASK_GET(this_task.t_sched.s_running.sr_runnxt)->t_sched.s_running.sr_runprv == THIS_TASK &&
	       PERTASK_GET(this_task.t_sched.s_running.sr_runprv)->t_sched.s_running.sr_runnxt == THIS_TASK);
#endif /* !DEFINE_task_wake_as */
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
	was = PREEMPTION_PUSHOFF();
#ifdef DEFINE_task_wake_as
	mycpu = caller->t_cpu;
#else /* DEFINE_task_wake_as */
	mycpu = THIS_CPU;
#endif /* !DEFINE_task_wake_as */
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
#ifndef DEFINE_task_wake_as
		struct task *caller;
#endif /* !DEFINE_task_wake_as */
		struct task *next;
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
#ifndef DEFINE_task_wake_as
		caller = THIS_TASK;
#endif /* !DEFINE_task_wake_as */
		if (thread_flags & TASK_FRUNNING) {
#ifndef DEFINE_task_wake_as
			cpu_assert_running(thread);
#endif /* !DEFINE_task_wake_as */
			if (flags & TASK_WAKE_FLOWPRIO)
				goto unset_waking; /* Don't re-prioritize the target thread. */
			if unlikely(caller == thread) {
				/* Special (and _very_ unlikely) case: The calling thread is trying to wake itself.
				 * This could? happen under very rare circumstances, and is actually allowed behavior,
				 * so handle it by operating as a no-op, other than unsetting our own `TASK_FWAKING'
				 * flag. */
#ifdef NDEBUG
				PREEMPTION_POP(was);
				ATOMIC_AND(thread->t_flags, ~TASK_FWAKING);
#else /* NDEBUG */
				ATOMIC_AND(thread->t_flags, ~TASK_FWAKING);
#ifndef DEFINE_task_wake_as
				cpu_assert_running(thread);
#endif /* !DEFINE_task_wake_as */
				PREEMPTION_POP(was);
#endif /* !NDEBUG */
				return true;
			}
			/* The thread is already running.
			 * In this case, re-schedule the thread to-be executed next. */
			thread->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt = thread->t_sched.s_running.sr_runnxt;
			thread->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv = thread->t_sched.s_running.sr_runprv;
		} else {
			assert(caller != thread);
#ifndef DEFINE_task_wake_as
			cpu_assert_sleeping(thread);
#endif /* !DEFINE_task_wake_as */
			ATOMIC_OR(thread->t_flags, TASK_FRUNNING);
			/* The thread was sleeping. - Wake it up */
			if ((*thread->t_sched.s_asleep.ss_pself = thread->t_sched.s_asleep.ss_tmonxt) != NULL)
				thread->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = thread->t_sched.s_asleep.ss_pself;
		}
		next = caller->t_sched.s_running.sr_runnxt;
		assert(next);
		thread->t_sched.s_running.sr_runprv = caller;
		thread->t_sched.s_running.sr_runnxt = next;
		caller->t_sched.s_running.sr_runnxt = thread;
		next->t_sched.s_running.sr_runprv   = thread;
		assert(caller->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv == caller &&
		       caller->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt == caller);
		assert(thread->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv == thread &&
		       thread->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt == thread);
unset_waking:
		ATOMIC_AND(thread->t_flags, ~TASK_FWAKING);
#ifndef DEFINE_task_wake_as
		cpu_assert_running(thread);
#endif /* !DEFINE_task_wake_as */
		if (PREEMPTION_WASENABLED(was)) {
			if ((flags & TASK_WAKE_FHIGHPRIO) &&
			    mycpu->c_override != caller) {
				/* End the current quantum prematurely. */
				cpu_quantum_end_nopr(caller, thread);
				/* Directly switch execution to the thread in question,
				 * immediately allowing it to resume executing. */
				mycpu->c_current = thread;
				cpu_run_current_and_remember_nopr(caller);
				/* At this point, `thread' got to execute for a while, and we're
				 * back in business, with preemption enabled once again. */
			}
			PREEMPTION_ENABLE();
		}
		/*PREEMPTION_POP(was);*/
	}
	return true;
}

DECL_END

#undef DEFINE_task_wake_as
#undef DEFINE_task_wake
