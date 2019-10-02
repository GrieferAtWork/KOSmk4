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
#ifdef __INTELLISENSE__
#include "cpu.c"
#define TASK_SLEEP_CPUTIME 1
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#ifdef TASK_SLEEP_CPUTIME
/* Same as `task_sleep()', but `abs_timeout' exists on the `cpu_quantum_time()' timeline */
PUBLIC bool NOTHROW(FCALL task_sleep_cputime)(qtime_t const *abs_timeout)
#else /* TASK_SLEEP_CPUTIME */
/* Enter a sleeping state and return once being woken (true),
 * or once the given `abs_timeout' (which must be global) expires (false)
 * WARNING: Even if the caller has disabled preemption prior to the call,
 *          it will be re-enabled once this function returns.
 * NOTE: This function is the bottom-most (and still task-level) API
 *       for conserving CPU cycles using preemption, in that this
 *       function is even used to implement `task_wait()'.
 *       The functions used to implement this one no longer work on tasks, but on CPUs!
 * NOTE: If the thread is transferred to a different CPU while sleeping, a
 *       sporadic wakeup will be triggered, causing `task_sleep()' to return
 *      `true'.
 * The proper way of using this function is as follows:
 * >> while (SHOULD_WAIT()) { // Test some condition for which to wait
 * >>     PREEMPTION_DISABLE();
 * >>     // Test again now that interrupts are disabled
 * >>     // This test is required to prevent a race condition
 * >>     // where the condition is signaled between it being
 * >>     // changed and interrupts being disabled.
 * >>     COMPILER_READ_BARRIER();
 * >>     if (!SHOULD_WAIT()) {
 * >>         PREEMPTION_ENABLE();
 * >>         break;
 * >>     }
 * >>     // Serve RPC functions (when TRUE is returned, preemption was re-enabled)
 * >>     if (task_serve()) continue;
 * >>     // Do the actual sleep.
 * >>     if (!task_sleep(TIMEOUT))
 * >>         return DID_TIME_OUT;
 * >> }
 * >> return WAS_SIGNALED;
 * The sleeping thread should then be woken as follows:
 * >> SET_SHOULD_WAIT(false);
 * >> task_wake(waiting_thread); */
PUBLIC bool NOTHROW(FCALL task_sleep)(qtime_t const *abs_timeout)
#endif /* !TASK_SLEEP_CPUTIME */
{
	struct task *me = THIS_TASK;
	struct cpu *mycpu;
	cpu_assert_integrity();
	if (abs_timeout) {
		qtime_t now;
		/* Check if we should immediately time out. */
		if (!abs_timeout->q_jtime && !abs_timeout->q_qtime)
			goto do_return_false;
		/* Copy the given timeout with preemption still enabled.
		 * That way, a faulty input pointer can be handled more easily. */
		memcpy(&me->t_sched.s_asleep.ss_timeout,
		       abs_timeout, sizeof(qtime_t));
		COMPILER_READ_BARRIER();
		PREEMPTION_DISABLE();
#ifdef TASK_SLEEP_CPUTIME
		/* The given timestamp is already given as cpu-relative */
		now = cpu_quantum_time();
#else /* TASK_SLEEP_CPUTIME */
		/* Adjust the timeout for the local CPU */
		now = quantum_global_to_local(&me->t_sched.s_asleep.ss_timeout);
#endif /* !TASK_SLEEP_CPUTIME */
		/* Check if the given timeout has already expired. */
		if (now >= me->t_sched.s_asleep.ss_timeout) {
do_return_false:
			PREEMPTION_ENABLE();
			return false;
		}
	} else {
		me->t_sched.s_asleep.ss_timeout.q_jtime = (jtime_t)-1;
		me->t_sched.s_asleep.ss_timeout.q_qtime = 0;
		me->t_sched.s_asleep.ss_timeout.q_qsize = 1;
		PREEMPTION_DISABLE();
	}
	/* End the current quantum prematurely. */
	cpu_quantum_end();

	mycpu = me->t_cpu;
	cpu_assert_running(me);
	if (me == mycpu->c_override)
		goto wait_a_bit;

	/* The caller is the only thread hosted by this cpu. */
	if likely(me->t_sched.s_running.sr_runnxt == me) {
		struct task *idle;
		/* Special case: blocking call made by the IDLE thread. */
		if unlikely(me == &FORCPU(mycpu, _this_idle)) {
wait_a_bit:
			/* Wait for the next interrupt. */
			PREEMPTION_ENABLE_WAIT();
			/* Indicate a sporadic wake-up. */
			return false;
		}
		/* Check if the IDLE thread had been sleeping. */
		idle = &FORCPU(mycpu, _this_idle);
		if (idle->t_sched.s_asleep.ss_pself) {
			/* The IDLE thread had been sleeping (time it out) */
			ATOMIC_FETCHOR(idle->t_flags, TASK_FTIMEOUT);
			if ((*idle->t_sched.s_asleep.ss_pself = idle->t_sched.s_asleep.ss_tmonxt) != NULL)
				idle->t_sched.s_asleep.ss_tmonxt->t_sched.s_asleep.ss_pself = idle->t_sched.s_asleep.ss_pself;
		}
		/* Unschedule the caller, and instead schedule the IDLE thread. */
		idle->t_sched.s_running.sr_runprv = idle;
		idle->t_sched.s_running.sr_runnxt = idle;
		ATOMIC_FETCHOR(idle->t_flags, TASK_FRUNNING);
		mycpu->c_current = idle;
	} else {
		/* Schedule the next task. */
		struct task *prev = me->t_sched.s_running.sr_runprv;
		struct task *next = me->t_sched.s_running.sr_runnxt;
		assert(prev->t_sched.s_running.sr_runnxt == me);
		assert(next->t_sched.s_running.sr_runprv == me);
		assert(prev != me);
		assert(next != me);
		mycpu->c_current = next;
		next->t_sched.s_running.sr_runprv = prev;
		prev->t_sched.s_running.sr_runnxt = next;
	}
	assert(mycpu->c_current->t_sched.s_running.sr_runnxt->t_sched.s_running.sr_runprv == mycpu->c_current);
	assert(mycpu->c_current->t_sched.s_running.sr_runprv->t_sched.s_running.sr_runnxt == mycpu->c_current);
	me->t_sched.s_running.sr_runprv = NULL;
	me->t_sched.s_running.sr_runnxt = NULL;
	assert(me->t_flags & TASK_FRUNNING);
	ATOMIC_FETCHAND(me->t_flags, ~TASK_FRUNNING);

	/* Register the calling task as a sleeper within the CPU. */
	cpu_addsleepingtask(me);

	/* Continue execution in the next thread. */
	cpu_run_current_and_remember(me);

	assert(PREEMPTION_ENABLED());

	/* HINT: If your debugger break here, it means that your
	 *       thread is probably waiting on some kind of signal. */
	cpu_assert_running(me);

	/* Check if we got timed out. */
	if (ATOMIC_FETCHAND(me->t_flags, ~TASK_FTIMEOUT) & TASK_FTIMEOUT)
		return false; /* Timeout... */

	return true;
}

DECL_END

#undef TASK_SLEEP_CPUTIME
