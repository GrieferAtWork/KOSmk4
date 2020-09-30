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
#ifndef GUARD_KERNEL_SRC_SCHED_SCHED_C
#define GUARD_KERNEL_SRC_SCHED_SCHED_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/printk.h>
#include <sched/cpu.h>
#include <sched/sched.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <time.h>

DECL_BEGIN

/* Min/max bounds for how long a quantum can be.
 *
 * These values are required since the length of a quantum is calculated
 * dynamically, and is based on how long a thread has already waiting for
 * something to happen, meaning that these limits are necessary to prevent
 * a rouge thread from sleeping for a couple of hours, then proceeding to
 * go into an infinite loop ala `for(;;) {}'. Since the normal length of
 * a quantum directly reflects how long a thread has been waiting for, this
 * would mean that the system may remain unresponsive for quite some time.
 *
 * Similarly, the quantum minimum is needed in a situation where there are
 * hundreds upon thousands of threads running, to the point where the time
 * the kernel needs to switch from one thread to another would already make
 * up most, if not all of the time a single thread is assigned.
 *
 * NOTE: These values are measured in nano-seconds.
 * Also note that `sched_quantum_max' only applies for non-infinite quanta,
 * and that `sched_quantum_min' doesn't apply to short delays as the result
 * of accounting to the timeouts of sleeping threads. */
PUBLIC ktime_t sched_quantum_min = NSEC_PER_SEC / 10000;
PUBLIC ktime_t sched_quantum_max = NSEC_PER_SEC / 20;

/* Delay before a CPU (other than the boot CPU)
 * is shut down in order to save energy. */
PUBLIC ktime_t sched_shutdown_delay = (ktime_t)10 * NSEC_PER_SEC;


#define prev_task_from_pself(pself)                 \
	((struct task *)((byte_t *)(pself) -            \
	                 ((uintptr_t)&this_sched_link + \
	                  offsetof(_sched_link_t, ln_next))))

/* Helper macros. */
#define sched               FORCPU(me, thiscpu_scheduler)
#define sched_idle          FORCPU(me, thiscpu_idle)
#define sched_s_waiting     scheduler_s_waiting(&sched)
#define sched_link(thread)  FORTASK(thread, this_sched_link)
#define sched_pself(thread) FORTASK(thread, this_sched_link.ln_pself)
#define sched_next(thread)  FORTASK(thread, this_sched_link.ln_next)
#define sched_prev(thread)  prev_task_from_pself(sched_pself(thread))
#define sched_stoptime(thread)   FORTASK(thread, this_stoptime)
#define sched_activetime(thread) FORTASK(thread, this_activetime)
#define sched_timeout(thread)    FORTASK(thread, this_sched_timeout)

#define LINK2(first, second)         \
	(sched_next(first)   = (second), \
	 sched_pself(second) = &sched_next(first))


#ifndef NDEBUG
#define sched_assert() _sched_assert(me)
PRIVATE NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL _sched_assert)(struct cpu *__restrict me) {
	size_t num_running;
	struct task *iter, **pself;
	ktime_t prev_time;
	assertf(!PREEMPTION_ENABLED(),
	        "Preemption wasn't disabled");
	assertf(sched.s_runcount,
	        "Error: No running threads");
	assertf(sched.s_running,
	        "Inconsistency: runcount=%" PRIuSIZ ", but s_running=NULL",
	        sched.s_runcount);
	assertf(sched.s_running_last,
	        "Inconsistency: s_running_last is NULL when s_running=%p (runcount=%" PRIuSIZ ")",
	        sched.s_running, sched.s_runcount);
	assertf((sched_s_waiting != NULL) ==
	        (sched.s_waiting_last != NULL),
	        "Inconsistency: s_waiting=%p, but s_waiting_last=%p",
	        sched_s_waiting, sched.s_waiting_last);
	num_running = 0;
	pself = &sched.s_running;
	prev_time = 0;
	/* Enumerate running threads. */
	for (;;) {
		iter = *pself;
		assertf(iter != NULL,
		        "Bad chain: `sched.s_running_last' (%p) not reachable\n"
		        "Last reachable thread was: %p",
		        sched.s_running_last, prev_task_from_pself(pself));
		assertf(sched_pself(iter) == pself,
		        "Bad link: Self-pointer of running thread %p doesn't match\n"
		        "ADDROF(prev->next) = %p\n"
		        "thread->pself      = %p",
		        pself, sched_pself(iter));
		assertf(iter->t_flags & TASK_FRUNNING,
		        "Should-be running thread %p doesn't have "
		        "the running flag set (flags: %#" PRIxSIZ ")",
		        iter, iter->t_flags);
		assertf(prev_time <= sched_stoptime(iter),
		        "Wrong running thread order:\n"
		        "\tThread %p has stop_time=%#" PRIxN(__SIZEOF_KTIME_T__) "\n"
		        "\tThread %p has stop_time=%#" PRIxN(__SIZEOF_KTIME_T__) "\n",
		        sched_prev(iter), prev_time,
		        iter, sched_stoptime(iter));
		++num_running;
		if (iter == sched.s_running_last)
			break;
		prev_time = sched_stoptime(iter);
		pself = &sched_next(iter);
	}
	assertf(num_running == sched.s_runcount,
	        "num_running      = %" PRIuSIZ "\n"
	        "sched.s_runcount = %" PRIuSIZ,
	        num_running, sched.s_runcount);
	pself = &sched_next(iter);
	iter  = *pself;
	prev_time = 0;
	/* Enumerate waiting threads. */
	while ((iter = *pself) != NULL) {
		assertf(sched_pself(iter) == pself,
		        "Bad link: Self-pointer of waiting thread %p doesn't match\n"
		        "ADDROF(prev->next) = %p\n"
		        "thread->pself      = %p",
		        pself, sched_pself(iter));
		assertf(!(iter->t_flags & TASK_FRUNNING),
		        "Should-be waiting thread %p has the "
		        "running flag set (flags: %#" PRIxSIZ ")",
		        iter, iter->t_flags);
		if (iter == sched.s_waiting_last) {
			assertf(sched_next(iter) == NULL,
			        "Inconsistency: last waiting thread %p has a non-NULL next-link to %p",
			        iter, sched_next(iter));
		} else {
			assertf(sched_next(iter) != NULL,
			        "Inconsistency: last waiting thread %p isn't reachable "
			        "(last reachable thread is %p, which has a NULL next-link)",
			        sched.s_waiting_last, iter);
		}
		assertf(prev_time <= sched_timeout(iter),
		        "Wrong waiting thread order:\n"
		        "\tThread %p has stop_time=%#" PRIxN(__SIZEOF_KTIME_T__) "\n"
		        "\tThread %p has stop_time=%#" PRIxN(__SIZEOF_KTIME_T__) "\n",
		        sched_prev(iter), prev_time,
		        iter, sched_timeout(iter));
		prev_time = sched_timeout(iter);
		pself     = &sched_next(iter);
	}
}
#else /* !NDEBUG */
#define SCHED_ASSERT_IS_NOOP
#define sched_assert() (void)0
#endif /* NDEBUG */


/* [lock(PRIVATE(THIS_CPU))]
 * Linked-list node for other threads. Used internally by scheduling. */
PUBLIC ATTR_PERTASK REF _sched_link_t this_sched_link = LLIST_INITNODE;

/* [lock(PRIVATE(THIS_TASK))][valid_if(!TASK_FRUNNING)]
 * Timeout for when this thread should resume execution
 * by setting `TASK_FRUNNING | TASK_FTIMEOUT'. */
PUBLIC ATTR_PERTASK ktime_t this_sched_timeout = (ktime_t)-1;

/* [1..1][lock(PRIVATE(THIS_CPU))] The currently running thread. */
PUBLIC ATTR_PERCPU struct task *thiscpu_sched_current = NULL;

/* [lock(PRIVATE(THIS_CPU))] The scheduler for the associated CPU */
PUBLIC ATTR_PERCPU struct scheduler thiscpu_scheduler = {
	/* .s_running      = */ NULL,
	/* .s_running_last = */ NULL,
	/* .s_runcount     = */ 1,
	/* .s_waiting_last = */ NULL
};

/* [0..1][lock(PRIVATE(THIS_CPU))]
 * [if(!= NULL, [== FORCPU(., thiscpu_sched_current)])]
 * A scheduling override for this CPU. When non-NULL, the specified
 * thread must be the calling thread, in which case the caller will
 * never be preempted until this field is once again set to NULL.
 * Note however that this variable should not be written directly, but
 * rather through use of `sched_override_start()' and `sched_override_end()',
 * which will automatically account for the TSC deadline and the like. */
PUBLIC ATTR_PERCPU struct task *thiscpu_sched_override = NULL;




#ifndef CONFIG_NO_SMP
/* [0..1][lock(APPEND(ATOMIC), CLEAR(ATOMIC && THIS_CPU))]
 * [CHAIN(KEY_thiscpu_pending__next)]
 * Chain of tasks that are pending for being executed.
 * This chain is loaded by the CPU itself, which can be
 * provoked by another CPU calling `cpu_wake()' */
PUBLIC ATTR_PERCPU WEAK REF struct task *thiscpu_sched_pending = NULL;

/* Add `thread' to the chain of threads that are pending to be loaded by `target_cpu'
 * The caller should follow this by with a call to `cpu_wake(target_cpu)' in order to
 * request that `target_cpu' load its chain of pending threads. */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL sched_intern_addpending)(struct cpu *__restrict target_cpu,
                                       /*inherit*/ REF struct task *__restrict thread) {
	struct task *next;
	assert(thread->t_cpu == target_cpu);
	assert(thread->t_flags & TASK_FRUNNING);
	do {
		next = ATOMIC_READ(FORCPU(target_cpu, thiscpu_sched_pending));
		ATOMIC_WRITE(KEY_thiscpu_pending__next(thread), next);
	} while (!ATOMIC_CMPXCH_WEAK(FORCPU(target_cpu, thiscpu_sched_pending),
	                             next, thread));
}

/* Load a chain of pending threads */
PUBLIC NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct task *
NOTHROW(FCALL sched_intern_loadpending)(struct cpu *__restrict me,
                                        struct task *__restrict caller,
                                        /*inherit*/ REF struct task *__restrict chain) {
	struct task *next;
	for (;;) {
		next = KEY_thiscpu_pending__next(chain);
		/* Locally add each of the threads to our CPU */
		caller = sched_intern_localadd(me, caller, chain, false);
		if (!next)
			break;
		chain = next;
	}
	return caller;
}
#endif /* !CONFIG_NO_SMP */

/* Insert the given `thread' into `s_running' at the appropriate position.
 * The caller is responsible to set the TASK_FRUNNING flag for `thread',
 * but this function is responsible for insert the thread at its proper
 * position, as well as updating the scheduler state. */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL sched_intern_add_to_runqueue)(struct cpu *__restrict me,
                                            /*in*/ REF struct task *__restrict thread) {
	ktime_t thread_stoptime;
	struct task *neighbor;
	sched_assert();
	assert(thread->t_flags & TASK_FRUNNING);
	neighbor = sched.s_running_last;
	thread_stoptime = sched_stoptime(thread);
	if (thread_stoptime >= sched_stoptime(neighbor)) {
		/* Append at the very end. */
		LLIST_INSERT_AFTER_P(neighbor, thread, sched_link);
		sched.s_running_last = thread;
	} else {
		neighbor = sched.s_running;
		/* Append before some other thread prior to the last running thread.
		 * NOTE: At this point, we already know that `thread' should be inserted
		 *       before the last running thread, since it has a higher priority
		 *       that said last running thread! */
		while (thread_stoptime >= sched_stoptime(neighbor))
			neighbor = sched_next(neighbor);
		/* Insert the new thread before its neighbor. */
		LLIST_INSERT_BEFORE_P(thread, neighbor, sched_link);
	}
	++sched.s_runcount;
	sched_assert();
}

/* Add the given `thread' to the wait queue. */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL sched_intern_add_to_waitqueue)(struct cpu *__restrict me,
                                             /*in*/ REF struct task *__restrict thread,
                                             ktime_t timeout) {
	struct task *last_waiting;
	sched_assert();
	assert(!(thread->t_flags & TASK_FRUNNING));
	last_waiting = sched.s_waiting_last;
	assert((last_waiting != NULL) ==
	       (sched_s_waiting != NULL));
	if (last_waiting) {
		if likely(timeout >= sched_timeout(last_waiting)) {
			/* Simple case (for when `timeout' is infinite,
			 * or greater than any other active timeout) */
			LINK2(last_waiting, thread);
			sched_next(thread)   = NULL;
			sched.s_waiting_last = thread;
		} else {
			struct task *first_waiting;
			first_waiting = sched_s_waiting;
			/* Find the first thread with a greater timeout
			 * than the given `timeout'. We know that such
			 * a thread exists, since we also know that the
			 * last waiting thread doesn't qualify for this
			 * property. */
			while (!(timeout < sched_timeout(first_waiting)))
				first_waiting = sched_next(first_waiting);
			LLIST_INSERT_BEFORE_P(thread, first_waiting, sched_link);
		}
	} else {
		/* Special case: first waiting thread. */
		struct task *last_running;
		last_running = sched.s_running_last;
		sched_next(last_running) = thread;
		sched_pself(thread)      = &sched_next(last_running);
		sched_next(thread)       = NULL;
		sched.s_waiting_last     = thread;
	}
	sched_timeout(thread) = timeout;
	sched_assert();
}

/* Unlink the given `thread' from the waiting-chain */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL sched_intern_unlink_from_waiting)(struct cpu *__restrict me,
                                                /*out*/REF struct task *__restrict thread) {
	struct task *next;
	sched_assert();
	assert(sched_s_waiting != NULL);
	assert(!(thread->t_flags & TASK_FRUNNING));
	next = sched_next(thread);
	if ((*sched_pself(thread) = next) != NULL) {
		assert(sched.s_waiting_last != NULL);
		assert(sched.s_waiting_last != thread);
		sched_pself(next) = sched_pself(thread);
	} else {
		/* Last waiting thread. */
		assert(sched.s_waiting_last == thread);
		sched.s_waiting_last = sched_prev(thread);
		/* Check for special case: The last waiting thread has gone away. */
		if (sched.s_waiting_last == sched.s_running_last)
			sched.s_waiting_last = NULL;
	}
	sched_assert();
}

/* Move a given pair of thread `caller+thread' to the back of the run queue
 * by changing the stop_time timestamps of either thread to `new_stop_time'
 * Special handling is done for the case where `caller == &sched_idle', in
 * which case the function doesn't do anything other than doing some assertions. */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) void
NOTHROW(FCALL move_thread_pair_to_back_of_runqueue)(struct cpu *__restrict me,
                                                    struct task *__restrict caller,
                                                    struct task *__restrict thread,
                                                    ktime_t new_stop_time) {
	/* Update stop timestamps of `caller' and `thread' */
	assert(sched.s_runcount >= 2);
	if (sched.s_runcount == 2) {
		struct task *waiting;
		/* Special case: Set the running queue to `{ caller, thread }' */
		waiting = sched_s_waiting;
		sched.s_running      = caller;
		sched.s_running_last = thread;
		sched_next(caller)   = thread;
		sched_pself(caller)  = &sched.s_running;
		sched_next(thread)   = waiting;
		sched_pself(thread)  = &sched_next(caller);
		if (waiting)
			sched_pself(waiting) = &sched_next(thread);
	} else {
		struct task *last_running;
		assert(sched.s_runcount >= 3);
		/* Unlink `thread' and `caller' from somewhere within the running queue. */
		LLIST_REMOVE_P(thread, sched_link);
		if unlikely(sched.s_running_last == thread)
			sched.s_running_last = sched_prev(thread);
		LLIST_REMOVE_P(caller, sched_link);
		if unlikely(sched.s_running_last == caller)
			sched.s_running_last = sched_prev(caller);
		LINK2(caller, thread);
		last_running = sched.s_running_last;
		if likely(new_stop_time >= sched_stoptime(last_running)) {
			struct task *first_waiting;
			/* Insert `caller'+`thread' at the back of the running queue. */
			first_waiting = sched_next(last_running);
			assert((first_waiting != NULL) == (sched.s_waiting_last != NULL));
			if ((sched_next(thread) = first_waiting) != NULL)
				sched_pself(first_waiting) = &sched_next(thread);
			LINK2(last_running, caller);
			sched.s_running_last = thread;
		} else {
			struct task *first_running;
			first_running = sched.s_running;
			/* Unlikely case: There is a thread in the runqueue with a stop-time
			 * that is located in the future from our point of view. - This is
			 * something that is allowed, but not something that would normally
			 * happen.
			 * In this case, we must manually insert caller+thread into the queue. */
			if unlikely(new_stop_time < sched_stoptime(first_running)) {
				/* All threads except for `caller'+`thread' have stopped in the future...
				 * In this case, re-insert caller+thread at the front. */
				LINK2(thread, first_running);
				sched_pself(caller) = &sched.s_running;
				sched.s_running     = caller;
			} else {
				/* Find the thread before which we should insert caller+thread */
				struct task *before_last_running;
				do {
					last_running = sched_prev(last_running);
				} while (new_stop_time < sched_stoptime(last_running));
				before_last_running = sched_prev(last_running);
				LINK2(before_last_running, caller);
				LINK2(thread, last_running);
			}
		}
	}
	sched_stoptime(caller) = new_stop_time;
	sched_stoptime(thread) = new_stop_time;
}

/* Move a single thread to the back of the run queue */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL move_thread_to_back_of_runqueue)(struct cpu *__restrict me,
                                               struct task *__restrict thread,
                                               ktime_t new_stop_time) {
	/* Update stop timestamp of `thread' */
	if unlikely(sched.s_runcount == 1) {
		assert(sched.s_running == thread);
		assert(sched.s_running_last == thread);
		assert(sched_pself(thread) == &sched.s_running);
	} else {
		struct task *last_running;
		assert(sched.s_runcount >= 2);
		/* Re-insert `thread' */
		LLIST_REMOVE_P(thread, sched_link);
		last_running = sched.s_running_last;
		if unlikely(last_running == thread) {
			last_running         = sched_prev(thread);
			sched.s_running_last = last_running;
		}
		if likely(new_stop_time >= sched_stoptime(last_running)) {
			struct task *first_waiting;
			/* Insert `caller'+`thread' at the back of the running queue. */
			first_waiting = sched_next(last_running);
			assert((first_waiting != NULL) == (sched.s_waiting_last != NULL));
			if ((sched_next(thread) = first_waiting) != NULL)
				sched_pself(first_waiting) = &sched_next(thread);
			LINK2(last_running, thread);
			sched.s_running_last = thread;
		} else {
			struct task *first_running;
			first_running = sched.s_running;
			/* Unlikely case: There is a thread in the runqueue with a stop-time
			 * that is located in the future from our point of view. - This is
			 * something that is allowed, but not something that would normally
			 * happen.
			 * In this case, we must manually insert caller+thread into the queue. */
			if unlikely(new_stop_time < sched_stoptime(first_running)) {
				/* All threads except for `caller'+`thread' have stopped in the future...
				 * In this case, re-insert caller+thread at the front. */
				LINK2(thread, first_running);
				sched_pself(thread) = &sched.s_running;
				sched.s_running     = thread;
			} else {
				/* Find the thread before which we should insert caller+thread */
				do {
					last_running = sched_prev(last_running);
				} while (new_stop_time < sched_stoptime(last_running));
				LLIST_INSERT_BEFORE_P(thread, last_running, sched_link);
			}
		}
	}
	sched_stoptime(thread) = new_stop_time;
}


/* Re-load the deadline for when `caller' should stop execution. */
PRIVATE NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct task *
NOTHROW(FCALL sched_intern_reload_deadline)(struct cpu *__restrict me,
                                            struct task *__restrict caller,
                                            ktime_t quantum_start,
                                            ktime_t now) {
	struct task *thread;
	ktime_t deadline;
	tsc_t tsc_deadline_value;
	deadline = (now - quantum_start) / sched.s_runcount;
	if (deadline < sched_quantum_min)
		deadline = sched_quantum_min;
	if (deadline > sched_quantum_max)
		deadline = sched_quantum_max;
	deadline += now;
	/* Check if we should cut the quantum short due to a sleeping thread. */
	FOREACH_thiscpu_sleeping(thread, me) {
		ktime_t distance;
		ktime_t next_priorty_then;
		ktime_t thrd_priorty_then;
		if unlikely(sched_timeout(thread) >= deadline)
			break; /* No sleeping thread will time out before our quantum ends */
		/* Check if the thread will have a greater priority than `NEXT' when it times out. */
		distance = deadline - sched_timeout(thread);
		if unlikely(OVERFLOW_USUB(quantum_start, distance, &next_priorty_then))
			goto do_use_sleeping_thread_timeout;
		thrd_priorty_then = sched_stoptime(thread) + distance;
		if (thrd_priorty_then > next_priorty_then) {
do_use_sleeping_thread_timeout:
			deadline = sched_timeout(thread);
			break;
		}
	}
	if unlikely(deadline <= now)
		goto deadline_passed;

	/* Convert the effective deadline into a TSC value. */
	tsc_deadline_value = ktime_future_to_tsc(me, deadline);
	/* Set the final TSC deadline to indicate when
	 * to trigger the next preemptive interrupt. */
	if (tsc_deadline_value == TSC_MAX) {
		tsc_nodeadline(me);
	} else {
		tsc_t tsc_now;
		tsc_now = tsc_deadline(me, tsc_deadline_value);
		if (tsc_now >= tsc_deadline_value) {
			/* Deadline has already expired... */
deadline_passed:
			caller = tsc_deadline_passed(me, caller, tsc_now);
		}
	}
	return caller;
}

/* Perform a high-priority switch to `thread',
 * returning the thread to which to actually switch. */
PRIVATE NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct task *
NOTHROW(FCALL sched_intern_high_priority_switch)(struct cpu *__restrict me,
                                                 struct task *__restrict caller,
                                                 struct task *__restrict thread,
                                                 tsc_t tsc_now,
                                                 bool reload_deadline) {
	ktime_t now, quantum_start;
	assert(caller != thread);
	now = tsc_now_to_ktime(me, tsc_now);
	/* Gift the remainder of `caller's quantum to `thread' */
	quantum_start = sched_stoptime(caller);
	if unlikely(quantum_start >= now)
		return caller; /* Shouldn't happen... */
	/* Account for time spent being active. */
	sched_activetime(caller) += now - quantum_start;
	/* Update the stop timestamps of both `caller' and `next' */
	move_thread_pair_to_back_of_runqueue(me, caller, thread, now);
	/* If requested to, reload the current deadline. */
	if (reload_deadline)
		thread = sched_intern_reload_deadline(me, thread, quantum_start, now);
	return thread;
}


/* Wake-up a thread associated with the current CPU
 * @param: flags: Set of `TASK_WAKE_FNORMAL | TASK_WAKE_FHIGHPRIO'
 * @return: * :  The new thread with which to continue execution. */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct task *
NOTHROW(FCALL sched_intern_localwake)(struct cpu *__restrict me,
                                      struct task *__restrict caller,
                                      struct task *__restrict thread,
                                      bool high_priority) {
	struct task *result = caller;
	uintptr_t flags;
	assert(caller->t_cpu == me);
	assert(thread->t_cpu == me);
	sched_assert();
	flags = thread->t_flags;
	switch (__builtin_expect(flags & (TASK_FRUNNING |
	                                  TASK_FSTARTED |
	                                  TASK_FTERMINATED),
	                         TASK_FSTARTED)) {

	case TASK_FSTARTED:
		assert(caller != thread);
		/* Check for special case: wakeup the IDLE thread, when
		 *                         the IDLE thread isn't loaded.
		 * -> handle this as a no-op. */
		if unlikely(thread == &sched_idle && sched_pself(thread) == NULL)
			break;
		/* Unlink the thread from the waiting list. */
		sched_intern_unlink_from_waiting(me, thread);
		/* Resume execution of the thread. */
		ATOMIC_OR(thread->t_flags, TASK_FRUNNING);
		/* Insert the thread into the run-queue */
		sched_intern_add_to_runqueue(me, thread);
		if likely(!FORCPU(me, thiscpu_sched_override)) {
			tsc_t tsc_now;
			/* Reload the scheduler deadline, or (optionally)
			 * perform a high-priority switch to the named `thread'. */
			tsc_now = tsc_get(me);
			/* TODO: `sched_intern_localwake()' should never return something other
			 *       than the original caller, unless doing a high-priority wake.
			 * Do this by adding a new function `tsc_deadline_f()' that will force
			 * the new deadline to be set, even if it's already been expired. In the
			 * later case, that function will then set-up an interrupt that will be
			 * triggered as soon as preemption gets re-enabled. */
			if (high_priority)
				result = sched_intern_high_priority_switch(me, caller, thread, tsc_now, true);
			else {
				result = sched_intern_reload_deadline(me, result, tsc_now, ktime_with_cpu(me));
			}
		}
		break;

	case TASK_FRUNNING | TASK_FSTARTED:
		if unlikely(caller == thread)
			break;
		if (!high_priority)
			break; /* Simple case... (nothing actually changed) */
		if likely(!FORCPU(me, thiscpu_sched_override)) {
			tsc_t tsc_now;
			/* Perform a high-priority thread switch. */
			tsc_now = tsc_get(me);
			result  = sched_intern_high_priority_switch(me, caller, thread, tsc_now, false);
		}
		break;

	default:
		/* no-op (Thread not started, or already terminated) */
		break;
	}
	sched_assert();
	return result;
}


/* Add a new (running) thread to current CPU.
 * @return: * :  The new thread with which to continue execution. */
PUBLIC NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct task *
NOTHROW(FCALL sched_intern_localadd)(struct cpu *__restrict me,
                                     struct task *__restrict caller,
                                     /*inherit*/ REF struct task *__restrict thread,
                                     bool high_priority) {
	struct task *result = caller;
	sched_assert();
	assert(thread->t_flags & TASK_FRUNNING);
	/* Insert the given `thread' into the run-queue */
	sched_intern_add_to_runqueue(me, thread);
	if likely(!FORCPU(me, thiscpu_sched_override)) {
		tsc_t tsc_now;
		/* Reload the scheduler deadline, or perform a
		 * high-priority switch to the named `thread'. */
		tsc_now = tsc_get(me);
		if (high_priority)
			result = sched_intern_high_priority_switch(me, caller, thread, tsc_now, true);
		else {
			result = sched_intern_reload_deadline(me, caller, tsc_now, ktime_with_cpu(me));
		}
	}
	sched_assert();
	return result;
}


/* Yield execution to some other thread, returning the switch to which to switch.
 * If it is impossible to yield to anyone, simply re-return `caller'. */
PUBLIC NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct task *
NOTHROW(FCALL sched_intern_yield)(struct cpu *__restrict me,
                                  struct task *__restrict caller) {
	struct task *result;
	sched_assert();
	result = FORCPU(me, thiscpu_sched_override);
	if likely(!result) {
		result = sched.s_running;
		if (result != caller) {
			tsc_t tsc_now;
do_switch_to_result:
			/* Essentially do a high-priority switch to `result' (without reloading the deadline) */
			tsc_now = tsc_get(me);
			result  = sched_intern_high_priority_switch(me, caller, result, tsc_now, false);
		} else if (result != sched.s_running_last) {
			result = sched_next(result);
			assert(result != caller);
			goto do_switch_to_result;
		}
	}
	sched_assert();
	return result;
}


/* Same as `sched_intern_yield()', but ensure that `caller' doesn't get re-returned.
 * Additionally, this function will unlink `caller' from the run-queue, and if doing
 * so were to cause the run queue to become empty, then the IDLE thread will be added
 * to the run queue, as well as be switched to.
 * Note that it is illegal to call this function as the IDLE thread! */
PUBLIC NOPREEMPT NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct task *
NOTHROW(FCALL sched_intern_yield_onexit)(struct cpu *__restrict me,
                                         struct task *__restrict caller) {
	ktime_t now, quantum_start;
	struct task *result;
	sched_assert();
	assert(caller != &sched_idle);
	assert(caller->t_flags & TASK_FRUNNING);
	assert(!FORCPU(me, thiscpu_sched_override));

	/* Unlink the thread from the run queue. */
	if unlikely(sched.s_runcount == 1) {
		struct task *first_waiting_thread;
		assert(caller == sched.s_running);
		assert(caller == sched.s_running_last);
		assert(sched_pself(caller) == &sched.s_running);
		/* Special case: Must switch to the IDLE thread. */
		result = &sched_idle;
		sched.s_running      = result;
		sched.s_running_last = result;
		sched_pself(result)  = &sched.s_running;
		first_waiting_thread = sched_next(caller);
		assert((first_waiting_thread != NULL) ==
		       (sched.s_waiting_last != NULL));
		if ((sched_next(result) = first_waiting_thread) != NULL)
			sched_pself(first_waiting_thread) = &sched_next(result);
		assert(!(result->t_flags & TASK_FRUNNING));
		ATOMIC_OR(result->t_flags, TASK_FRUNNING);
	} else {
		/* Unlink from the run queue. */
		assert(sched.s_runcount >= 2);
		if (sched.s_running_last == caller)
			sched.s_running_last = sched_prev(caller);
		LLIST_REMOVE_P(caller, sched_link);
		--sched.s_runcount;
		/* Just switch to whatever thread comes next. */
		result = sched.s_running;
	}
	/* Perform something similar to a high-priority switch */
	assert(caller != result);
	now = ktime_with_cpu(me);
	/* Gift the remainder of `caller's quantum to `thread' */
	quantum_start = sched_stoptime(caller);
	if unlikely(quantum_start > now)
		quantum_start = now; /* Shouldn't happen... */
	/* Account for time spent being active. */
	sched_activetime(caller) += now - quantum_start;
	sched_stoptime(caller) = now;
	/* Update the stop timestamp of `next' */
	move_thread_to_back_of_runqueue(me, result, now);
	/* Reload the current deadline. */
	result = sched_intern_reload_deadline(me, result, quantum_start, now);
	sched_assert();
	return result;
}

/* Wait for a sporadic interrupt, or the given `deadline' to expire.
 * return `false' if the deadline has expired, and `true' if the
 * caller was woken up by a sporadic interrupt. */
PRIVATE NOPREEMPT bool
NOTHROW(FCALL waitfor_tsc_deadline_or_interrupt)(struct cpu *__restrict me,
                                                 tsc_t deadline) {
	tsc_t now;
	if (deadline == TSC_MAX) {
		tsc_nodeadline(me);
		/* Wait for a sporadic interrupt. */
		PREEMPTION_ENABLE_WAIT();
		return true;
	}
	/* Set the given deadline. */
	now = tsc_deadline(me, deadline);
	if (now < deadline) {
		/* Wait for the next interrupt to fire. */
		PREEMPTION_ENABLE_WAIT_DISABLE();
		/* Disable the deadline once again.
		 * Note that in the event that the interrupt was the
		 * result of the deadline elapsing, the initial check
		 * for a scheduling override in `tsc_deadline_passed()'
		 * will have prevented that interrupt handler from
		 * changing the deadline before we got here! */
		tsc_nodeadline(me);
		now = tsc_get(me);
	}
	PREEMPTION_ENABLE();
	return now < deadline;
}

/* Same as `waitfor_tsc_deadline_or_interrupt()', but wait
 * for a ktime timestamp, rather than a TSC value. */
PRIVATE NOPREEMPT bool
NOTHROW(FCALL waitfor_ktime_or_interrupt)(struct cpu *__restrict me,
                                          ktime_t deadline) {
	tsc_t tsc_deadline_value;
	tsc_deadline_value = ktime_to_tsc(me, deadline);
	return waitfor_tsc_deadline_or_interrupt(me, tsc_deadline_value);
}

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
PUBLIC bool NOTHROW(FCALL task_sleep)(struct timespec const *abs_timeout) {
	struct task *next;
	struct task *caller = THIS_TASK;
	struct cpu *me;
	ktime_t now, timeout, quantum_start;
	PREEMPTION_DISABLE();
	me = ATOMIC_READ(caller->t_cpu);
	sched_assert();
	assert(caller->t_flags & TASK_FRUNNING);
	/* TODO: Change the task_sleep() API to use `ktime_t' instead of timespec! */
	timeout = abs_timeout ? timespec_to_ktime(abs_timeout)
	                      : (ktime_t)-1;
	if unlikely(FORCPU(me, thiscpu_sched_override)) {
		/* Scheduler override has been set.
		 * -> Wait for the given timeout to expire, or a sporadic interrupt */
		return waitfor_ktime_or_interrupt(me, timeout);
	}
	/* Unlink the thread from the run queue. */
	if unlikely(sched.s_runcount == 1) {
		struct task *first_waiting_thread;
		first_waiting_thread = sched_next(caller);
		assert(caller == sched.s_running);
		assert(caller == sched.s_running_last);
		assert(sched_pself(caller) == &sched.s_running);
		if unlikely(caller == &sched_idle) {
			/* Special case: wait within the IDLE thread, when no other
			 *               threads exist to which we can switch.
			 * In this case, we must wait until either `timeout', or the
			 * timeout of our CPU's first waiting thread has expired. */
			ktime_t used_timeout = timeout;
			if (first_waiting_thread) {
				ktime_t other_timeout;
				other_timeout = sched_timeout(first_waiting_thread);
				if (used_timeout > other_timeout)
					used_timeout = other_timeout;
			}
			/* Wait for the next closest timeout to expire, or a sporadic interrupt */
			return waitfor_ktime_or_interrupt(me, used_timeout);
		}
		/* Special case: Must switch to the IDLE thread. */
		next = &sched_idle;
		sched.s_running      = next;
		sched.s_running_last = next;
		sched_pself(next)    = &sched.s_running;
		if ((sched_next(next) = first_waiting_thread) != NULL)
			sched_pself(first_waiting_thread) = &sched_next(next);
		assert(!(next->t_flags & TASK_FRUNNING));
		ATOMIC_OR(next->t_flags, TASK_FRUNNING);
		sched_assert();
	} else {
		/* Unlink from the run queue. */
		assert(caller != &sched_idle);
		assert(sched.s_runcount >= 2);
		if (sched.s_running_last == caller)
			sched.s_running_last = sched_prev(caller);
		LLIST_REMOVE_P(caller, sched_link);
		--sched.s_runcount;
		/* Just switch to whatever thread comes next. */
		next = sched.s_running;
		sched_assert();
	}
	/* Perform something similar to a high-priority switch */
	assert(next);
	assert(next != caller);
	assert(next->t_flags & TASK_FRUNNING);
	now = ktime_with_cpu(me);

	/* Gift the remainder of `caller's quantum to `thread' */
	quantum_start = sched_stoptime(caller);
	if unlikely(quantum_start > now)
		quantum_start = now; /* Shouldn't happen... */

	/* Account for time spent being active. */
	sched_activetime(caller) += now - quantum_start;
	sched_stoptime(caller) = now;

	/* Update the stop timestamps of both `caller' and `next' */
	move_thread_to_back_of_runqueue(me, next, now);

	/* Insert `caller' into the queue of waiting threads. */
	ATOMIC_AND(caller->t_flags, ~TASK_FRUNNING);
	sched_intern_add_to_waitqueue(me, caller, timeout);

	/* Reload the current deadline. */
	next = sched_intern_reload_deadline(me, next, quantum_start, now);

	/* Continue execution in the next thread. */
	assert(next->t_flags & TASK_FRUNNING);

	/* Check for special case: The switch wasn't actually done.
	 * This can happen when `caller' is the only running thread (aside
	 * of the IDLE thread), and the timeout delay was so small that the
	 * scheduler decided that it wouldn't make sense to switch execution
	 * until the timeout was exceeded. */
	if likely(next != caller) {
		FORCPU(me, thiscpu_sched_current) = next;
		sched_assert();
		cpu_run_current_and_remember_nopr(caller);

		/* HINT: If your debugger break here, it means that your
		 *       thread is probably waiting on some kind of signal. */
		assert(caller->t_flags & TASK_FRUNNING);
		assert(FORCPU(me, thiscpu_sched_current) == caller);
#ifndef SCHED_ASSERT_IS_NOOP
		PREEMPTION_DISABLE();
		sched_assert();
		PREEMPTION_ENABLE();
#endif /* !SCHED_ASSERT_IS_NOOP */
	} else {
		sched_assert();
		PREEMPTION_ENABLE();
	}

	/* Check if we got timed out. */
	if (ATOMIC_FETCHAND(caller->t_flags, ~TASK_FTIMEOUT) & TASK_FTIMEOUT) {
		assertf(abs_timeout, "TASK_FTIMEOUT set, but no timeout given?");
		return false; /* Timeout... */
	}
	return true;
}






/* Interrupt handler callback for `tsc_deadline()'.
 * This function is called from arch-specific code as the result of a
 * previously set deadline, and will be invoked no sooner than the point
 * in time when `tsc_get() >= deadline' */
PUBLIC NOPREEMPT NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct task *
NOTHROW(FCALL tsc_deadline_passed)(struct cpu *__restrict me,
                                   struct task *__restrict caller,
                                   tsc_t tsc_now) {
	ktime_t now, next_priority, deadline;
	struct task *next, *thread;
	tsc_t tsc_deadline_value;
	/* Check for special case: a scheduler override is present.
	 * Note that this should really happen, since setting a scheduler
	 * override should call `tsc_nodeadline()' */
	if unlikely(FORCPU(me, thiscpu_sched_override))
		return FORCPU(me, thiscpu_sched_override);
	sched_assert();
	/* Calculate the current scheduler time. */
again_with_tsc_now:
	now = tsc_now_to_ktime(me, tsc_now);
again:
	/* Select the thread with the lowest stop-time as successor. */
	next          = sched.s_running;
	next_priority = sched_stoptime(next);
	/* Check the timeouts of sleeping threads. */
	FOREACH_thiscpu_sleeping(thread, me) {
		assert(!(thread->t_flags & TASK_FRUNNING));
		if (sched_timeout(thread) > now)
			break; /* No more threads that have timed out. */
		if unlikely(sched_stoptime(thread) > next_priority)
			break; /* Thread priority too low for a wake-up */
		/* Wake-up the thread. */
		sched_intern_unlink_from_waiting(me, thread);
		ATOMIC_OR(thread->t_flags, TASK_FRUNNING | TASK_FTIMEOUT);
		sched_intern_add_to_runqueue(me, thread);
		goto again;
	}
	/* This is the primary deadline formula that
	 * enables us to do preemptive multitasking. */
	deadline = /*now + */ (now - next_priority) / sched.s_runcount;
	/* Clamp the relative deadline to prevent situations where all of
	 * a thread's designated time is spent doing context switches. */
	if (deadline < sched_quantum_min)
		deadline = sched_quantum_min;
	/* Update thread state flags. */
	if (next != caller) {
		/* Clamp the relative deadline to prevent situations where a
		 * rouge threads waiting for a couple of hours before directly
		 * jumping into an infinite loop. */
		if (deadline > sched_quantum_max)
			deadline = sched_quantum_max;
		deadline += now;

		/* Account for time spent being active. */
		sched_activetime(caller) += now - sched_stoptime(caller);

		/* Update the stop timestamps of both `caller' and `next' */
		move_thread_pair_to_back_of_runqueue(me, caller, next, now);
	} else {
		/* The current thread didn't change. - Check if we can use an infinite timeout. */
		deadline += now;
		if (sched.s_runcount == 1) {
			deadline = (ktime_t)-1;
		}
	}
	/* Check if we should cut the quantum short due to a sleeping thread. */
	FOREACH_thiscpu_sleeping(thread, me) {
		ktime_t distance;
		ktime_t next_priorty_then;
		ktime_t thrd_priorty_then;
		if unlikely(sched_timeout(thread) >= deadline)
			break; /* No sleeping thread will time out before our quantum ends */
		/* Check if the thread will have a greater priority than `NEXT' when it times out. */
		distance = deadline - sched_timeout(thread);
		if unlikely(OVERFLOW_USUB(next_priority, distance, &next_priorty_then))
			goto do_use_sleeping_thread_timeout;
		thrd_priorty_then = sched_stoptime(thread) + distance;
		if (thrd_priorty_then > next_priorty_then) {
do_use_sleeping_thread_timeout:
			deadline = sched_timeout(thread);
			break;
		}
	}
	assert(deadline >= now);

	/* Convert the effective deadline into a TSC value. */
	tsc_deadline_value = ktime_future_to_tsc(me, deadline);

	/* Set the final TSC deadline to indicate when
	 * to trigger the next preemptive interrupt. */
	if (tsc_deadline_value == TSC_MAX) {
		tsc_nodeadline(me);
	} else {
		tsc_now = tsc_deadline(me, tsc_deadline_value);
		if (tsc_now >= tsc_deadline_value) {
			/* Deadline has already expired... */
			caller = next;
			goto again_with_tsc_now;
		}
	}
	/* Switch execution to the next thread. */
	sched_assert();
	return next;
}




PUBLIC void NOTHROW(KCALL cpu_deepsleep)(void) {
#if 1
	/* TODO: Unload the IDLE thread or setup a timeout using
	 *       `sched_shutdown_delay' for when we should shut-
	 *       down the CPU. */
	PREEMPTION_ENABLE();
	while (task_tryyield() == TASK_TRYYIELD_SUCCESS);
	PREEMPTION_WAIT();
#else
	struct task *next;
	struct cpu *me = THIS_CPU;
	assertf(THIS_TASK == &sched_idle,
	        "cpu_deepsleep() may only be called form a cpu's IDLE thread!");
	assertf(FORCPU(me, thiscpu_sched_current) == &sched_idle,
	        "cpu_deepsleep() may only be called form a cpu's IDLE thread!");
	assertf(FORCPU(me, thiscpu_sched_override) == NULL,
	        "cpu_deepsleep() cannot be called while a scheduling override is active");
	assert(sched_idle.t_flags & TASK_FRUNNING);
	assert(me->c_state == CPU_STATE_RUNNING);
again:
	PREEMPTION_DISABLE();
again_already_disabled:
	ATOMIC_WRITE(me->c_state, CPU_STATE_FALLING_ASLEEP);
	assert(!PREEMPTION_ENABLED());
#ifndef CONFIG_NO_SMP
	/* Check for pending threads, and if there are some,
	 * load them and directly yield to the first of them. */
	{
		REF struct task *chain;
		chain = ATOMIC_XCH(FORCPU(me, thiscpu_sched_pending), NULL);
		if (chain != NULL) {
			next = sched_intern_loadpending(me, &sched_idle, chain);
			if (next != &sched_idle)
				goto yield_to_next;
		}
	}
	/* Check if there are IPIs that are pending execution, as send from other cores.
	 * For this, check for both hardware (interrupting), as well as software (pending) IPIs.
	 * NOTE: Software IPIs must be checked to prevent the following race condition:
	 *
	 *  #1  CPU#0: cpu_sendipi:     SCHEDULE_SW_IPI();
	 *  #2  CPU#0: cpu_sendipi:     ATOMIC_READ(CPU[1].c_state) == CPU_STATE_RUNNING;
	 *  #3  CPU#1: cpu_deepsleep:   PREEMPTION_DISABLE();
	 *  #4  CPU#1: cpu_deepsleep:   ATOMIC_WRITE(me->c_state, CPU_STATE_FALLING_ASLEEP);
	 *  #5  CPU#1: cpu_deepsleep:   arch_cpu_hwipi_pending_nopr(me) == false;
	 *  #6  CPU#1: cpu_deepsleep:   cpu_enter_deepsleep(me);
	 *  #7  CPU#1: cpu_deepsleep:   ATOMIC_WRITE(me->c_state, CPU_STATE_DREAMING);
	 *  #8  CPU#0: cpu_sendipi:     SCHEDULE_HW_IPI();
	 *  #9  CPU#1: cpu_sendipi:     ---                    The hardware IPI never arrives, because we've gone into deep sleep
	 *  #10 CPU#0: cpu_sendipi:     return true;           As far as CPU#0 can tell, everything worked.
	 *
	 * -> The IPI never arrives because CPU#1 doesn't get woken up.
	 *
	 * The solution is to simply check for `arch_cpu_swipi_pending_nopr()' in
	 * step #5, since those types of interrupts will have already become visible
	 * following step #1!
	 *
	 * As such, the SWIPI check forms an interlocked check for pending IPIs in
	 * situations where a software-IPI was already scheduled, but a hardware
	 * IPI hasn't been generated yet, would get generated at a later point in
	 * time (i.e. after this call to `arch_cpu_hwipi_pending_nopr()' already
	 * returned `false'), or would not get generated at all.
	 */
	if (arch_cpu_hwipi_pending_nopr() || arch_cpu_swipi_pending_nopr(me)) {
		ATOMIC_WRITE(me->c_state, CPU_STATE_RUNNING);
		cpu_ipi_service_nopr();
#ifdef PREEMPTION_ENABLE_P
		/* Use `PREEMPTION_ENABLE_P()' in order to ensure that interrupts had at least
		 * a single instruction during which they could be served, in case GCC decides
		 * to move the `PREEMPTION_DISABLE()' above in such a manner that it would follow
		 * our `PREEMPTION_ENABLE()' immediately. */
		PREEMPTION_ENABLE_P();
#else /* PREEMPTION_ENABLE_P */
		PREEMPTION_ENABLE();
#endif /* !PREEMPTION_ENABLE_P */
		goto again;
	}
#endif /* !CONFIG_NO_SMP */

	/* Check if there are other running threads. */
	assert(sched.s_runcount >= 1);
	if (sched.s_runcount > 1 || sched.s_running != &sched_idle)
		goto yield_and_return;

	TODO;

	goto again_already_disabled;
yield_and_return:
	assert(sched.s_runcount > 1 || sched.s_running != &sched_idle);
	TODO;

yield_to_next:
	FORCPU(me, thiscpu_sched_current) = next;
	cpu_run_current_and_remember_nopr(&sched_idle);
#endif
}

DECL_END


#endif /* !GUARD_KERNEL_SRC_SCHED_SCHED_C */
