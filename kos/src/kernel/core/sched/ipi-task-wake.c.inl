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
#ifdef __INTELLISENSE__
#include "ipi.c"
#define DEFINE_task_wake
//#define DEFINE_task_wake_as
#endif /* __INTELLISENSE__ */

#include <hybrid/sched/preemption.h>

#if (defined(DEFINE_task_wake) + defined(DEFINE_task_wake_as)) != 1
#error "Invalid configuration (must define exactly one of these macros)"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_task_wake
/* Re-schedule the given `thread' if it was unscheduled (entered a sleeping state).
 * Using this function, a ~sporadic interrupt~ is implemented.
 * If the thread hasn't been unscheduled, this function is a no-op.
 * NOTE: This function is used in the implementation of  `sig_send'
 * @param: flags:  Set of `TASK_WAKE_F*'
 * @return: true:  The task was woken, or wasn't sleeping.
 * @return: false: The given task has terminated. */
PUBLIC NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL task_wake)(struct task *__restrict thread,
                         unsigned int flags)
#elif defined(DEFINE_task_wake_as)
/* Wake `thread' while impersonating  `caller', where `caller' must  some
 * running  thread from the calling CPU. -  This function is used to wake
 * up waiting threads during task exit, where at the point where the exit
 * status is broadcast, the exiting  thread (THIS_TASK) can no longer  be
 * used to send signals (since `task_wake()'  has to look at things  such
 * as  the prev/next thread  within the scheduler  ring, which would have
 * already  become invalid at  that point, since  the true calling thread
 * could no longer be considered apart of the scheduler ring)
 *
 * When calling this function, the caller must ensure that their current
 * CPU will no change, which can be done most easily by simply disabling
 * preemption, or setting the `TASK_FKEEPCORE' flag.
 *
 * The given `caller'  is used  when `thread' is  running on  `THIS_CPU',
 * in which case `thread' will  be re-scheduled in relation to  `caller',
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
	preemption_flag_t was;
	struct cpu *me;
#ifndef CONFIG_NO_SMP
	struct cpu *target;
#endif /* !CONFIG_NO_SMP */
#ifdef DEFINE_task_wake_as
	assertf(!PREEMPTION_ENABLED() || PERTASK_TESTMASK(this_task.t_flags, TASK_FKEEPCORE),
	        "You must ensure that you're core won't change before calling `task_wake_as()'");
	assertf(caller && caller->t_cpu == THIS_CPU,
	        "You may only impersonate other threads from your own CPU");
#endif /* DEFINE_task_wake_as */
	/* Now we're responsible to see to it that the thread either gets
	 * woken, or that  the `TASK_FTERMINATED' gets  set before  then.
	 * NOTE: We can't actually track the later happening on other cores,
	 *       but that's actually  OK, since the  wakeup simply got  lost
	 *       while  the task  was already  dying, which  can only happen
	 *       when the  thread was  already in  a state  where it  wasn't
	 *       guarantied to be responsive to wakeup commands. */
	preemption_pushoff(&was);
#ifdef DEFINE_task_wake_as
	me = caller->t_cpu;
#else /* DEFINE_task_wake_as */
	me = THIS_CPU;
#endif /* !DEFINE_task_wake_as */
#ifndef CONFIG_NO_SMP
	/* Read the CPU field _once_ since it might change before the next read. */
	target = ATOMIC_READ(thread->t_cpu);
	if (target != me) {
		/* Use an IPI to wake up the thread! */
		void *args[CPU_IPI_ARGCOUNT];
		if (ATOMIC_READ(thread->t_flags) & TASK_FTERMINATED) {
			IPI_DEBUG("task_wake(%p):terminated\n", thread);
			return false; /* The thread has already terminated. */
		}
		args[0] = thread;
		args[1] = (void *)(uintptr_t)flags;
		IPI_DEBUG("task_wake(%p):ipi\n", thread);
		while (!cpu_sendipi(target, &task_wake_ipi, args,
		                    CPU_IPI_FWAKEUP | (flags & TASK_WAKE_FWAITFOR)))
			task_pause();
		preemption_pop(&was);
	} else
#endif /* !CONFIG_NO_SMP */
	{
		/* Wake on the current thread. */
#ifndef DEFINE_task_wake_as
		struct task *caller;
#endif /* !DEFINE_task_wake_as */
		IPI_DEBUG("task_wake(%p):me\n", thread);
		COMPILER_READ_BARRIER();
		if (thread->t_flags & TASK_FTERMINATED) {
			/* The thread has already terminated,  but the wake-up was requested  at
			 * a time when the  thread wasn't. So between  then and now, the  thread
			 * must have executed at least for a while, meaning it did get a wake-up
			 * for one reason or another, which is good enough for us!
			 *
			 * On  the other hand, a task that is intended to, or already was added
			 * as a pending task within our CPU is guarantied to receive a  wake-up
			 * once that request goes through (which may actually happen as soon as
			 * we re-enable preemption, which may be done by the next line) */
			IPI_DEBUG("task_wake(%p):terminated\n", thread);
		} else {
#ifndef DEFINE_task_wake_as
			caller = THIS_TASK;
#endif /* !DEFINE_task_wake_as */
			thread = sched_intern_localwake(me, caller, thread,
			                                (flags & TASK_WAKE_FHIGHPRIO) != 0 &&
			                                preemption_wason(&was));
			if (thread != caller) {
				/* Directly switch execution to the thread in question,
				 * immediately   allowing   it  to   resume  executing. */
				FORCPU(me, thiscpu_sched_current) = thread;
				cpu_run_current_and_remember_nopr(caller);
				/* At this point, `thread' got to execute for a while, and we're
				 * back   in  business,  with  preemption  enabled  once  again. */
				return true;
			}
		}
		preemption_pop(&was);
	}
	return true;
}

DECL_END

#undef DEFINE_task_wake_as
#undef DEFINE_task_wake
