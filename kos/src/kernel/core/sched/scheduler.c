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
#ifndef GUARD_KERNEL_SRC_SCHED_SCHEDULER_C
#define GUARD_KERNEL_SRC_SCHED_SCHEDULER_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/entropy.h>
#include <kernel/printk.h>
#include <sched/cpu.h>
#include <sched/scheduler.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/preemption.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <time.h>

DECL_BEGIN

/* Min/max bounds for how long a quantum can be.
 *
 * These  values are required  since the length of  a quantum is calculated
 * dynamically,  and is based on how long  a thread has already waiting for
 * something  to happen, meaning that these limits are necessary to prevent
 * a  rouge thread from sleeping for a  couple of hours, then proceeding to
 * go  into an infinite  loop ala `for(;;) {}'. Since  the normal length of
 * a quantum directly reflects how long a thread has been waiting for, this
 * would mean that the system may remain unresponsive for quite some  time.
 *
 * Similarly, the quantum minimum is needed in a situation where there  are
 * hundreds upon thousands of threads running, to the point where the  time
 * the kernel needs to switch from one thread to another would already make
 * up most, if not all of the time a single thread is assigned.
 *
 * NOTE: These values are measured in nano-seconds.
 * Also note that `sched_quantum_max' only applies for non-infinite quanta,
 * and that `sched_quantum_min' doesn't apply to short delays as the result
 * of accounting to the timeouts of sleeping threads. */
PUBLIC ktime_t sched_quantum_min = NSEC_PER_SEC / 1000;
PUBLIC ktime_t sched_quantum_max = NSEC_PER_SEC / 20;

/* Delay before a CPU (other than the boot CPU)
 * is  shut  down  in  order  to  save  energy. */
PUBLIC ktime_t sched_shutdown_delay = (ktime_t)10 * NSEC_PER_SEC;


#define prev_task_from_pself(pself)                 \
	((struct task *)((byte_t *)(pself) -            \
	                 ((uintptr_t)&this_sched_link + \
	                  offsetof(_sched_link_t, le_next))))

/* Helper macros. */
#define sched                    FORCPU(me, thiscpu_scheduler)
#define sched_idle               FORCPU(me, thiscpu_idle)
#define sched_s_waiting          scheduler_s_waiting(&sched)
#define sched_override           FORCPU(me, thiscpu_sched_override)
#define sched_link(thread)       FORTASK(thread, this_sched_link)
#define sched_pself(thread)      FORTASK(thread, this_sched_link.le_prev)
#define sched_next(thread)       FORTASK(thread, this_sched_link.le_next)
#define sched_prev(thread)       prev_task_from_pself(sched_pself(thread))
#define sched_stoptime(thread)   FORTASK(thread, this_stoptime)
#define sched_activetime(thread) FORTASK(thread, this_activetime)
#define sched_timeout(thread)    FORTASK(thread, this_sched_timeout)
#define sched_s_running_first    sched.s_running.lh_first

#define LINK2(first, second)         \
	(sched_next(first)   = (second), \
	 sched_pself(second) = &sched_next(first))


#if !defined(NDEBUG) && 1
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
	assertf(!LIST_EMPTY(&sched.s_running),
	        "Inconsistency: runcount=%" PRIuSIZ ", but s_running=NULL",
	        sched.s_runcount);
	assertf(sched.s_running_last,
	        "Inconsistency: s_running_last is NULL when s_running=%p (runcount=%" PRIuSIZ ")",
	        sched_s_running_first, sched.s_runcount);
	assertf((sched_s_waiting != NULL) ==
	        (sched.s_waiting_last != NULL),
	        "Inconsistency: s_waiting=%p, but s_waiting_last=%p",
	        sched_s_waiting, sched.s_waiting_last);
	num_running = 0;
	pself = &sched_s_running_first;
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

#define sched_assert_in_runqueue(thread) _sched_assert_in_runqueue(me, thread)
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL _sched_assert_in_runqueue)(struct cpu *__restrict me,
                                         struct task *__restrict thread) {
	do {
		struct task *iter;
		FOREACH_thiscpu_running(iter, me) {
			if (iter == thread)
				return;
		}
	} while (__assertion_checkf("thread IN sched.s_running",
	                            "Thread %p isn't apart of the run-queue of cpu #%u",
	                            thread, me->c_id));
}

#define sched_assert_not_in_runqueue(thread) _sched_assert_not_in_runqueue(me, thread)
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL _sched_assert_not_in_runqueue)(struct cpu *__restrict me,
                                             struct task *__restrict thread) {
	struct task *iter;
again:
	FOREACH_thiscpu_running(iter, me) {
		if (iter == thread) {
			if (!__assertion_checkf("thread !IN sched.s_running",
			                        "Thread %p is apart of the run-queue of cpu #%u",
			                        thread, me->c_id))
				return;
			goto again;
		}
	}
}

#define sched_assert_in_waitqueue(thread) _sched_assert_in_waitqueue(me, thread)
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL _sched_assert_in_waitqueue)(struct cpu *__restrict me,
                                          struct task *__restrict thread) {
	do {
		struct task *iter;
		FOREACH_thiscpu_waiting(iter, me) {
			if (iter == thread)
				return;
		}
	} while (__assertion_checkf("thread IN sched.s_waiting",
	                            "Thread %p isn't apart of the wait-queue of cpu #%u",
	                            thread, me->c_id));
}

#define sched_assert_not_in_waitqueue(thread) _sched_assert_not_in_waitqueue(me, thread)
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL _sched_assert_not_in_waitqueue)(struct cpu *__restrict me,
                                             struct task *__restrict thread) {
	struct task *iter;
again:
	FOREACH_thiscpu_waiting(iter, me) {
		if (iter == thread) {
			if (!__assertion_checkf("thread !IN sched.s_waiting",
			                        "Thread %p is apart of the wait-queue of cpu #%u",
			                        thread, me->c_id))
				return;
			goto again;
		}
	}
}

#else /* !NDEBUG */
#define SCHED_ASSERT_IS_NOOP
#define sched_assert()                        (void)0
#define sched_assert_in_runqueue(thread)      (void)0
#define sched_assert_in_waitqueue(thread)     (void)0
#define sched_assert_not_in_runqueue(thread)  (void)0
#define sched_assert_not_in_waitqueue(thread) (void)0
#endif /* NDEBUG */


/* [lock(PRIVATE(THIS_CPU))]
 * Linked-list node for other threads. Used internally by scheduling. */
PUBLIC ATTR_PERTASK ATTR_ALIGN(REF _sched_link_t) this_sched_link = LIST_ENTRY_UNBOUND_INITIALIZER;

/* [lock(PRIVATE(THIS_TASK))][valid_if(!TASK_FRUNNING)]
 * Timeout for when this thread should resume execution
 * by setting `TASK_FRUNNING | TASK_FTIMEOUT'. */
PUBLIC ATTR_PERTASK ATTR_ALIGN(ktime_t) this_sched_timeout = KTIME_INFINITE;

/* [1..1][lock(PRIVATE(THIS_CPU))] The currently running thread. */
PUBLIC ATTR_PERCPU struct task *thiscpu_sched_current = NULL;

/* [lock(PRIVATE(THIS_CPU))] The scheduler for the associated CPU */
PUBLIC ATTR_PERCPU struct scheduler thiscpu_scheduler = {
	.s_running      = LIST_HEAD_INITIALIZER(thiscpu_scheduler.s_running),
	.s_running_last = NULL,
	.s_runcount     = 1,
	.s_waiting_last = NULL
};

/* [0..1][lock(PRIVATE(THIS_CPU))]
 * [if(!= NULL, [== FORCPU(., thiscpu_sched_current)])]
 * A  scheduling  override  for  this  CPU.  When  non-NULL,  the   specified
 * thread must  be  the  calling  thread,  in  which  case  the  caller  will
 * never  be  preempted  until  this  field  is  once  again  set  to   NULL.
 * Note  however  that  this variable  should  not be  written  directly, but
 * rather through use of `sched_override_start()' and `sched_override_end()',
 * which  will  automatically  account for  the  TSC deadline  and  the like. */
PUBLIC ATTR_PERCPU struct task *thiscpu_sched_override = NULL;




#ifndef CONFIG_NO_SMP
/* [0..1][lock(APPEND(ATOMIC), CLEAR(ATOMIC && THIS_CPU))]
 * [CHAIN(KEY__thiscpu_pending_next)]
 * Chain of tasks that are pending for being  executed.
 * This chain is loaded by the CPU itself, which can be
 * provoked by another CPU calling `cpu_wake()' */
PUBLIC ATTR_PERCPU WEAK REF struct task *thiscpu_sched_pending = NULL;

/* Add `thread' to the chain of threads that are pending to be loaded by `target_cpu'
 * The caller should follow this up with a call to `cpu_wake(target_cpu)' in order to
 * request that `target_cpu' load its chain of pending threads. */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL sched_intern_addpending)(struct cpu *__restrict target_cpu,
                                       /*inherit*/ REF struct task *__restrict thread) {
	struct task *next;
	assert(thread->t_cpu == target_cpu);
	assert(thread->t_flags & TASK_FRUNNING);
	do {
		next = ATOMIC_READ(FORCPU(target_cpu, thiscpu_sched_pending));
		ATOMIC_WRITE(KEY__thiscpu_pending_next(thread), next);
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
		next = KEY__thiscpu_pending_next(chain);

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
 * The caller is responsible to  set the TASK_FRUNNING flag for  `thread',
 * but  this function is  responsible for insert the  thread at its proper
 * position, as well as updating the scheduler state. */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL sched_intern_add_to_runqueue)(struct cpu *__restrict me,
                                            /*in*/ REF struct task *__restrict thread) {
	ktime_t thread_stoptime;
	struct task *neighbor;
	sched_assert();
	sched_assert_not_in_runqueue(thread);
	assert(thread->t_flags & TASK_FRUNNING);
	neighbor = sched.s_running_last;
	thread_stoptime = sched_stoptime(thread);
	if (thread_stoptime >= sched_stoptime(neighbor)) {

		/* Append at the very end. */
		LIST_INSERT_AFTER_P(/* predecessor: */ neighbor,
		                    /* elem:        */ thread,
		                    /* key:         */ sched_link);
		sched.s_running_last = thread;
	} else {
		neighbor = sched_s_running_first;

		/* Append before some other thread prior to the last running thread.
		 * NOTE: At this point, we already know that `thread' should be inserted
		 *       before  the last running thread, since it has a higher priority
		 *       that said last running thread! */
		while (thread_stoptime >= sched_stoptime(neighbor))
			neighbor = sched_next(neighbor);

		/* Insert the new thread before its neighbor. */
		LIST_INSERT_BEFORE_P(/* successor: */ neighbor,
		                     /* elem:      */ thread,
		                     /* key:       */ sched_link);
	}
	++sched.s_runcount;
	sched_assert_in_runqueue(thread);
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
	sched_assert_not_in_waitqueue(thread);
	last_waiting = sched.s_waiting_last;
	assert((last_waiting != NULL) ==
	       (sched_s_waiting != NULL));
	if (last_waiting) {
		if likely(timeout >= sched_timeout(last_waiting)) {
			/* Simple case (for when `timeout' is infinite,
			 * or greater  than any  other active  timeout) */
			LINK2(last_waiting, thread);
			sched_next(thread)   = NULL;
			sched.s_waiting_last = thread;
		} else {
			struct task *first_waiting;
			first_waiting = sched_s_waiting;

			/* Find the first thread with a greater timeout
			 * than  the given `timeout'. We know that such
			 * a thread exists, since we also know that the
			 * last waiting thread doesn't qualify for this
			 * property. */
			while (!(timeout < sched_timeout(first_waiting)))
				first_waiting = sched_next(first_waiting);
			LIST_INSERT_BEFORE_P(/* successor: */ first_waiting,
			                     /* elem:      */ thread,
			                     /* key:       */ sched_link);
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
	sched_assert_in_waitqueue(thread);
	sched_assert();
}

/* Unlink the given `thread' from the waiting-chain */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL sched_intern_unlink_from_waiting)(struct cpu *__restrict me,
                                                /*out*/REF struct task *__restrict thread) {
	struct task *next;
	sched_assert();
	sched_assert_in_waitqueue(thread);
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
	sched_assert_not_in_waitqueue(thread);
	sched_assert();
}

/* Move a given  pair of thread  `caller+thread' to  the back of  the run  queue
 * by changing  the stop_time  timestamps of  either thread  to  `new_stop_time'
 * Special  handling  is done  for  the case  where  `caller == &sched_idle', in
 * which case the function doesn't do anything other than doing some assertions. */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) void
NOTHROW(FCALL move_thread_pair_to_back_of_runqueue)(struct cpu *__restrict me,
                                                    struct task *__restrict caller,
                                                    struct task *__restrict thread,
                                                    ktime_t new_stop_time) {
	/* Update stop timestamps of `caller' and `thread' */
	sched_assert();
	sched_assert_in_runqueue(thread);
	sched_assert_in_runqueue(caller);
	assert(sched.s_runcount >= 2);
	if (sched.s_runcount == 2) {
		struct task *waiting;

		/* Special case: Set the running queue to `{ caller, thread }' */
		waiting = sched_s_waiting;
		sched_s_running_first = caller;
		sched.s_running_last  = thread;
		sched_next(caller)    = thread;
		sched_pself(caller)   = &sched_s_running_first;
		sched_next(thread)    = waiting;
		sched_pself(thread)   = &sched_next(caller);
		if (waiting)
			sched_pself(waiting) = &sched_next(thread);
	} else {
		struct task *last_running;
		assert(sched.s_runcount >= 3);

		/* Unlink `thread' and `caller' from somewhere within the running queue. */
		if unlikely(sched.s_running_last == thread)
			sched.s_running_last = sched_prev(thread);
		LIST_REMOVE_P(thread, sched_link);
		if unlikely(sched.s_running_last == caller)
			sched.s_running_last = sched_prev(caller);
		LIST_REMOVE_P(caller, sched_link);
		LINK2(caller, thread);
		last_running = sched.s_running_last;
		assert(last_running != thread && last_running != caller);
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
			first_running = sched_s_running_first;

			/* Unlikely case: There is a thread in the runqueue with a stop-time
			 * that is located in the future from  our point of view. - This  is
			 * something that is allowed, but not something that would  normally
			 * happen.
			 * In this case, we must manually insert caller+thread into the queue. */
			if unlikely(new_stop_time < sched_stoptime(first_running)) {
				/* All threads except for `caller'+`thread' have stopped in the future...
				 * In this case, re-insert caller+thread at the front. */
				LINK2(thread, first_running);
				sched_pself(caller)   = &sched_s_running_first;
				sched_s_running_first = caller;
			} else {
				/* Find the thread after which we should insert caller+thread */
				struct task *after_last_running;
				do {
					last_running = sched_prev(last_running);
				} while (new_stop_time < sched_stoptime(last_running));
				/* NOTE: new_stop_time >= sched_stoptime(last_running) */
				after_last_running = sched_next(last_running);
				LINK2(last_running, caller);
				LINK2(thread, after_last_running);
			}
		}
	}
	sched_stoptime(caller) = new_stop_time;
	sched_stoptime(thread) = new_stop_time;
	sched_assert();
}

/* Move a single thread to the back of the run queue */
PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) void
NOTHROW(FCALL move_thread_to_back_of_runqueue)(struct cpu *__restrict me,
                                               struct task *__restrict thread,
                                               ktime_t new_stop_time) {
	sched_assert();
	sched_assert_in_runqueue(thread);
	/* Update stop timestamp of `thread' */
	if unlikely(sched.s_runcount == 1) {
		assert(thread == sched_s_running_first);
		assert(thread == sched.s_running_last);
		assert(sched_pself(thread) == &sched_s_running_first);
	} else {
		struct task *last_running;
		assert(sched.s_runcount >= 2);
		last_running = sched.s_running_last;
		if unlikely(last_running == thread) {
			last_running = sched_prev(thread);
			assert(last_running != thread);
			sched.s_running_last = last_running;
		}
		LIST_REMOVE_P(thread, sched_link);

		/* Re-insert `thread' */
		if likely(new_stop_time >= sched_stoptime(last_running)) {
			struct task *first_waiting;

			/* Insert `thread' at the back of the running queue. */
			first_waiting = sched_next(last_running);
			assert((first_waiting != NULL) == (sched.s_waiting_last != NULL));
			if ((sched_next(thread) = first_waiting) != NULL)
				sched_pself(first_waiting) = &sched_next(thread);
			LINK2(last_running, thread);
			sched.s_running_last = thread;
		} else {
			struct task *first_running;
			first_running = sched_s_running_first;

			/* Unlikely case: There is a thread in the runqueue with a stop-time
			 * that is located in the future from  our point of view. - This  is
			 * something that is allowed, but not something that would  normally
			 * happen.
			 * In this case, we must manually insert thread into the queue. */
			if unlikely(new_stop_time < sched_stoptime(first_running)) {
				/* All threads except for `thread' have stopped in the future...
				 * In this case, re-insert thread at the front. */
				LINK2(thread, first_running);
				sched_pself(thread)   = &sched_s_running_first;
				sched_s_running_first = thread;
			} else {
				/* Find the thread after which we should insert our's */
				do {
					last_running = sched_prev(last_running);
				} while (new_stop_time < sched_stoptime(last_running));
				/* NOTE: new_stop_time >= sched_stoptime(last_running) */
				LIST_INSERT_AFTER_P(/* predecessor: */ last_running,
				                    /* elem:        */ thread,
				                    /* key:         */ sched_link);
			}
		}
	}
	sched_stoptime(thread) = new_stop_time;
	sched_assert();
}


/* Re-load the deadline for when `caller' should stop execution. */
PRIVATE NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct task *
NOTHROW(FCALL sched_intern_reload_deadline)(struct cpu *__restrict me,
                                            struct task *__restrict caller,
                                            ktime_t quantum_start,
                                            ktime_t priority_boost,
                                            ktime_t now,
                                            tsc_t tsc_now,
                                            bool delay_deadline_passed) {
	struct task *thread;
	ktime_t deadline;
	tsc_t tsc_deadline_value;
	if unlikely(quantum_start > now)
		quantum_start = now;
	deadline = ((now - quantum_start) + priority_boost) / sched.s_runcount;
	if (deadline < sched_quantum_min)
		deadline = sched_quantum_min;
	if (deadline > sched_quantum_max)
		deadline = sched_quantum_max;
	deadline += now;
	assert(deadline >= now);

	/* Check if we should cut the quantum short due to a sleeping thread. */
	FOREACH_thiscpu_waiting(thread, me) {
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
			if unlikely(deadline <= now) {
				if (delay_deadline_passed) {
					/* TODO: tsc_deadline_setpending(); */
					return caller;
				} else {
					return tsc_deadline_passed(me, caller, tsc_now);
				}
			}
			break;
		}
	}

	/* Convert the effective deadline into a TSC value. */
	tsc_deadline_value = ktime_future_to_tsc(me, deadline);

	/* Set the final TSC deadline to indicate when
	 * to trigger the  next preemptive  interrupt. */
	if (tsc_deadline_value == TSC_MAX) {
		tsc_nodeadline(me);
	} else {
		tsc_t tsc_now;
		tsc_now = tsc_deadline(me, tsc_deadline_value);
		if (tsc_now >= tsc_deadline_value) {
			/* Deadline has already expired... */
			if (delay_deadline_passed) {
				/* `sched_intern_localwake()' should never return something other
				 * than the original caller,  unless doing a high-priority  wake.
				 *
				 * Do this by  calling a  function `tsc_deadline_setpending()'  that
				 * forces a deadline interrupt to be triggered as soon as preemption
				 * gets re-enabled. */
				/* TODO: tsc_deadline_setpending(); */
			} else {
				caller = tsc_deadline_passed(me, caller, tsc_now);
			}
		}
	}
	return caller;
}

/* Perform  a  high-priority  switch  to   `thread',
 * returning the thread to which to actually switch. */
PRIVATE NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct task *
NOTHROW(FCALL sched_intern_high_priority_switch)(struct cpu *__restrict me,
                                                 struct task *__restrict caller,
                                                 struct task *__restrict thread,
                                                 tsc_t tsc_now,
                                                 bool reload_deadline) {
	ktime_t now, quantum_start;
	ktime_t priority_boost;
	assert(caller != thread);
	now = tsc_now_to_ktime(me, tsc_now);

	/* Gift the remainder of `caller's quantum to `thread' */
	quantum_start = sched_stoptime(caller);
	if unlikely(quantum_start >= now)
		return caller; /* Shouldn't happen... */

	/* If the caller only had a really short amount of time left for
	 * their current quantum, and `thread' has already been  waiting
	 * for a  really long  time, then  `thread' must  still get  its
	 * priority boost! */
	if (OVERFLOW_USUB(now, sched_stoptime(thread), &priority_boost))
		priority_boost = 0;

	/* Account for time spent being active. */
	sched_activetime(caller) += now - quantum_start;

	/* Update the stop timestamps of both `caller' and `next' */
	move_thread_pair_to_back_of_runqueue(me, caller, thread, now);

	/* If requested to, reload the current deadline. */
	if (reload_deadline) {
		thread = sched_intern_reload_deadline(me, thread,
		                                      quantum_start,
		                                      priority_boost,
		                                      now, tsc_now,
		                                      false);
	}
	return thread;
}


/* Wake-up a thread associated with the current CPU
 * @param: flags: Set of `TASK_WAKE_FNORMAL | TASK_WAKE_FHIGHPRIO'
 * @return: * : The new thread with which to continue execution. */
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
		/* Check for special case: wakeup the IDLE thread,  when
		 *                         the IDLE thread isn't loaded.
		 * -> handle this as a no-op. */
		if unlikely(thread == &sched_idle && sched_pself(thread) == NULL) {
			/* IDLE wasn't apart of the run-queue, so don't try to unlink it! */
		} else {
			/* Unlink the thread from the waiting list. */
			sched_intern_unlink_from_waiting(me, thread);
		}

		/* Resume execution of the thread. */
		ATOMIC_OR(thread->t_flags, TASK_FRUNNING);

		/* Insert the thread into the run-queue */
		sched_intern_add_to_runqueue(me, thread);
		if likely(!sched_override) {
			tsc_t tsc_now;
			/* Reload  the  scheduler   deadline,  or   (optionally)
			 * perform a high-priority switch to the named `thread'. */
			tsc_now = tsc_get(me);
			if (high_priority) {
				result = sched_intern_high_priority_switch(me, caller, thread,
				                                           tsc_now, true);
			} else {
				result = sched_intern_reload_deadline(me, result,
				                                      sched_stoptime(caller), 0,
				                                      tsc_now_to_ktime(me, tsc_now),
				                                      tsc_now, true);
				assert(result == caller);
			}
		}
		break;

	case TASK_FRUNNING | TASK_FSTARTED:
		if unlikely(caller == thread)
			break;
		if (!high_priority)
			break; /* Simple case... (nothing actually changed) */
		if likely(!sched_override) {
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


/* Add a new (running) thread to the current CPU.
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
	if likely(!sched_override) {
		tsc_t tsc_now;

		/* Reload the scheduler deadline, or perform a
		 * high-priority switch to the named `thread'. */
		tsc_now = tsc_get(me);
		if (high_priority) {
			result = sched_intern_high_priority_switch(me, caller, thread,
			                                           tsc_now, true);
		} else {
			result = sched_intern_reload_deadline(me, caller,
			                                      sched_stoptime(caller), 0,
			                                      tsc_now_to_ktime(me, tsc_now),
			                                      tsc_now, false);
		}
	}
	sched_assert();
	return result;
}


/* Yield execution to some other thread, returning the thread to which to switch.
 * If  it  is  impossible  to   yield  to  anyone,  simply  re-return   `caller'. */
PUBLIC NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct task *
NOTHROW(FCALL sched_intern_yield)(struct cpu *__restrict me,
                                  struct task *__restrict caller) {
	struct task *result;
	sched_assert();
	result = sched_override;
	if likely(!result) {
		result = sched_s_running_first;
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


/* Same as `sched_intern_yield()', but ensure that `caller' doesn't get  re-returned.
 * Additionally, this function will unlink `caller' from the run-queue, and if  doing
 * so were to cause the run queue to become empty, then the IDLE thread will be added
 * to the run queue, as well as be returned.
 * Note that it is illegal to call this function as the IDLE thread! */
PUBLIC NOBLOCK NOPREEMPT ATTR_RETNONNULL NONNULL((1, 2)) struct task *
NOTHROW(FCALL sched_intern_yield_onexit)(struct cpu *__restrict me,
                                         struct task *__restrict caller) {
	tsc_t tsc_now;
	ktime_t now, quantum_start, priority_boost;
	struct task *result;
	sched_assert();
	assert(caller != &sched_idle);
	assert(caller->t_flags & TASK_FRUNNING);
	assert(!sched_override);

	/* Unlink the thread from the run queue. */
	if unlikely(sched.s_runcount == 1) {
		struct task *first_waiting_thread;
		assert(caller == sched_s_running_first);
		assert(caller == sched.s_running_last);
		assert(sched_pself(caller) == &sched_s_running_first);

		/* Special case: Must switch to the IDLE thread. */
		result = &sched_idle;
		sched_s_running_first = result;
		sched.s_running_last  = result;
		sched_pself(result)   = &sched_s_running_first;
		first_waiting_thread  = sched_next(caller);
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
		LIST_REMOVE_P(caller, sched_link);
		--sched.s_runcount;

		/* Just switch to whatever thread comes next. */
		result = sched_s_running_first;
	}

	/* Perform something similar to a high-priority switch */
	assert(caller != result);
	tsc_now = tsc_get(me);
	now     = tsc_now_to_ktime(me, tsc_now);

	/* Gift the remainder of `caller's quantum to `thread' */
	quantum_start = sched_stoptime(caller);
	if unlikely(quantum_start > now)
		quantum_start = now; /* Shouldn't happen... */

	/* Account for time spent being active. */
	sched_activetime(caller) += now - quantum_start;
	sched_stoptime(caller) = now;

	/* If the caller only had a really short amount of time left for
	 * their current quantum, and `thread' has already been  waiting
	 * for a  really long  time, then  `thread' must  still get  its
	 * priority boost! */
	if (OVERFLOW_USUB(now, sched_stoptime(result), &priority_boost))
		priority_boost = 0;

	/* Update the stop timestamp of `next' */
	move_thread_to_back_of_runqueue(me, result, now);

	/* Reload the current deadline. */
	result = sched_intern_reload_deadline(me, result, quantum_start,
	                                      priority_boost, now,
	                                      tsc_now, false);
	sched_assert();
	assert(result != caller);
	return result;
}

/* Wait for a sporadic interrupt, or the given `deadline' to expire.
 * return `false' if  the deadline  has expired, and  `true' if  the
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
		 * Note that in  the event that  the interrupt was  the
		 * result  of the deadline  elapsing, the initial check
		 * for a scheduling override in `tsc_deadline_passed()'
		 * will have  prevented  that  interrupt  handler  from
		 * changing the deadline before we got here! */
		tsc_nodeadline(me);
		now = tsc_get(me);
	}
	PREEMPTION_ENABLE();
	return now < deadline;
}

/* Same as `waitfor_tsc_deadline_or_interrupt()', but wait
 * for  a  ktime  timestamp,  rather  than  a  TSC  value. */
PRIVATE NOPREEMPT bool
NOTHROW(FCALL waitfor_ktime_or_interrupt)(struct cpu *__restrict me,
                                          ktime_t deadline) {
	tsc_t tsc_deadline_value;
	tsc_deadline_value = ktime_to_tsc(me, deadline);
	return waitfor_tsc_deadline_or_interrupt(me, tsc_deadline_value);
}

/* Enter  a  sleeping state  and return  once  being woken  (true), or
 * once the given `abs_timeout' (which must be global) expires (false)
 * NOTES:
 *   - Special values for `abs_timeout' are:
 *     - KTIME_NONBLOCK (or anything `< ktime()'): Essentially does the same as task_yield()
 *     - KTIME_INFINITE:                           Never times out
 *   - Even if the caller has disabled preemption prior to the call,
 *     it   will   be   re-enabled  once   this   function  returns.
 *   - This function is the bottom-most (and still task-level) API
 *     for conserving CPU  cycles using preemption,  in that  this
 *     function is even used to implement `task_waitfor()'.
 *     The functions used to implement this one no longer work on tasks, but on CPUs!
 *   - If the thread is transferred to a different CPU while sleeping, a sporadic
 *     wakeup  will  be  triggered,  causing  `task_sleep()'  to  return  `true'.
 *   - When this function  returns as the  result of a  timeout, then you  may
 *     act as though  that `ktime() > abs_timeout' (but  note that this  isn't
 *     actually an invariant, as your task may have been moved to a  different
 *     CPU after waking up, at which point `ktime()' may have a slight offset)
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
PUBLIC bool NOTHROW(FCALL task_sleep)(ktime_t abs_timeout) {
	struct task *next;
	struct task *caller;
	struct cpu *me;
	ktime_t now, quantum_start, priority_boost;
	tsc_t tsc_now;
	caller = THIS_TASK;
	PREEMPTION_DISABLE();
	me = caller->t_cpu;
	sched_assert();
	assert(caller->t_flags & TASK_FRUNNING);
	if unlikely(sched_override) {
		/* Scheduler override has been set.
		 * -> Wait for the given timeout to expire, or a sporadic interrupt to take place */
		return waitfor_ktime_or_interrupt(me, abs_timeout);
	}

	/* Unlink the thread from the run queue. */
	if unlikely(sched.s_runcount == 1) {
		struct task *first_waiting_thread;
		first_waiting_thread = sched_next(caller);
		assert(caller == sched_s_running_first);
		assert(caller == sched.s_running_last);
		assert(sched_pself(caller) == &sched_s_running_first);
		if unlikely(caller == &sched_idle) {
			/* Special case: wait within the IDLE thread, when no other
			 *               threads exist  to  which  we  can  switch.
			 * In this case, we must wait until either `abs_timeout', or the
			 * timeout of our CPU's first  waiting thread (if any)  expires. */
			ktime_t used_timeout = abs_timeout;
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
		sched_s_running_first = next;
		sched.s_running_last  = next;
		sched_pself(next)     = &sched_s_running_first;
		if ((sched_next(next) = first_waiting_thread) != NULL)
			sched_pself(first_waiting_thread) = &sched_next(next);
		assert(!(next->t_flags & TASK_FRUNNING));
		ATOMIC_OR(next->t_flags, TASK_FRUNNING);
		sched_assert();
	} else {
		/* Unlink from the run queue. */
		assert(sched.s_runcount >= 2);
		if (sched.s_running_last == caller)
			sched.s_running_last = sched_prev(caller);
		LIST_REMOVE_P(caller, sched_link);
		--sched.s_runcount;

		/* Just switch to whatever thread comes next. */
		next = sched_s_running_first;
		sched_assert();
	}

	/* Perform something similar to a high-priority switch */
	assert(next);
	assert(next != caller);
	assert(next->t_flags & TASK_FRUNNING);
	tsc_now = tsc_get(me);
	now     = tsc_now_to_ktime(me, tsc_now);

	/* Gift the remainder of `caller's quantum to `thread' */
	quantum_start = sched_stoptime(caller);
	if unlikely(quantum_start > now)
		quantum_start = now; /* Shouldn't happen... */

	/* Account for time spent being active. */
	sched_activetime(caller) += now - quantum_start;
	sched_stoptime(caller) = now;

	/* If the caller only had a really short amount of time left for
	 * their current quantum, and `thread' has already been  waiting
	 * for a  really long  time, then  `thread' must  still get  its
	 * priority boost! */
	if (OVERFLOW_USUB(now, sched_stoptime(next), &priority_boost))
		priority_boost = 0;

	/* Update the stop timestamp of `next' */
	move_thread_to_back_of_runqueue(me, next, now);

	/* Insert `caller' into the queue of waiting threads. */
	ATOMIC_AND(caller->t_flags, ~TASK_FRUNNING);
	sched_intern_add_to_waitqueue(me, caller, abs_timeout);

	/* Reload the current deadline. */
	next = sched_intern_reload_deadline(me, next, quantum_start,
	                                    priority_boost, now,
	                                    tsc_now, false);

	/* Continue execution in the next thread. */
	assert(next->t_flags & TASK_FRUNNING);

	/* Check  for  special  case:  The  switch  wasn't  actually   done.
	 * This can happen when `caller'  is the only running thread  (aside
	 * of the IDLE thread), and the timeout delay was so small that  the
	 * scheduler decided that it wouldn't make sense to switch execution
	 * until the timeout was exceeded. */
	if likely(next != caller) {
		FORCPU(me, thiscpu_sched_current) = next;
		sched_assert();
		cpu_run_current_and_remember_nopr(caller);

		/* HINT: If your debugger breaks  here, it means that  your
		 *       thread is probably waiting on some kind of signal. */
		assert(caller->t_flags & TASK_FRUNNING);
#if 0 /* Can't be asserted: We may have switched CPUs in the mean time! */
		assert(FORCPU(me, thiscpu_sched_current) == caller);
#ifndef SCHED_ASSERT_IS_NOOP
		PREEMPTION_DISABLE();
		sched_assert();
		PREEMPTION_ENABLE();
#endif /* !SCHED_ASSERT_IS_NOOP */
#endif
	} else {
		sched_assert();
		PREEMPTION_ENABLE();
	}

	/* Check if we got timed out. */
	if (ATOMIC_FETCHAND(caller->t_flags, ~TASK_FTIMEOUT) & TASK_FTIMEOUT) {
		assertf(abs_timeout != KTIME_INFINITE,
		        "TASK_FTIMEOUT set, but no timeout given?");
		return false; /* Timeout... */
	}
	return true;
}






/* Interrupt handler callback for `tsc_deadline()'.
 * This  function is called  from arch-specific code as  the result of a
 * previously set deadline, and will be invoked no sooner than the point
 * in time when `tsc_get() >= deadline' */
PUBLIC NOBLOCK NOPREEMPT ATTR_RETNONNULL NONNULL((1, 2)) struct task *
NOTHROW(FCALL tsc_deadline_passed)(struct cpu *__restrict me,
                                   struct task *__restrict caller,
                                   tsc_t tsc_now) {
	ktime_t now, next_priority, deadline;
	struct task *next, *thread;
	tsc_t tsc_deadline_value;

	/* Check for  special  case:  a scheduler  override  is  present.
	 * Note that this should really happen, since setting a scheduler
	 * override  should  have  already  called  `tsc_nodeadline()'...
	 * We check this anyways to  prevent race conditions, as well  as
	 * to allow a scheduler override to use TSC deadlines. */
	if unlikely(sched_override)
		return sched_override;
	sched_assert();

	/* Calculate the current scheduler time. */
again_with_tsc_now:
	entropy_giveint_nopr(tsc_now, 3); /* Feed a little bit of entropy */
	now = tsc_now_to_ktime(me, tsc_now);
again:

	/* Select the thread with the lowest stop-time as successor. */
	next          = sched_s_running_first;
	next_priority = sched_stoptime(next);

	/* Check the timeouts of sleeping threads. */
	FOREACH_thiscpu_waiting(thread, me) {
		assert(!(thread->t_flags & TASK_FRUNNING));

		/* Must  compare  `<timeout> >= now' such  that `<timeout>=-1'
		 * isn't considered as something that could actually time out. */
		if (sched_timeout(thread) >= now)
			break; /* No more threads that have timed out. */
		if unlikely(sched_stoptime(thread) > next_priority)
			break; /* Thread priority too low for a wake-up */

		/* Wake-up the thread. */
do_timeout_thread:
		sched_intern_unlink_from_waiting(me, thread);
		ATOMIC_OR(thread->t_flags, TASK_FRUNNING | TASK_FTIMEOUT);
		sched_intern_add_to_runqueue(me, thread);
		goto again;
	}
	if unlikely(next_priority > now)
		next_priority = now; /* Shouldn't happen (TM) */

	/* This is the primary deadline formula that
	 * enables us to do preemptive multitasking. */
	deadline = /*now + */ (now - next_priority) / sched.s_runcount;

	/* Clamp the relative deadline to prevent situations where all of
	 * a thread's designated  time is spent  doing context  switches. */
	if (deadline < sched_quantum_min)
		deadline = sched_quantum_min;

	/* Update thread state flags. */
	if (next != caller) {
		/* Clamp the relative deadline  to prevent situations where  a
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
			deadline = KTIME_INFINITE;
		} else {
			/* Account for time spent being active. */
			sched_activetime(caller) += now - sched_stoptime(caller);

			/* Update the stop timestamp of `caller' */
			move_thread_to_back_of_runqueue(me, caller, now);
		}
	}
	assert(deadline >= now);

	/* Check if we should cut the quantum short due to a sleeping thread. */
	FOREACH_thiscpu_waiting(thread, me) {
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

			/* Must compare `TIMEOUT < NOW' such that TIMEOUT=-1 isn't
			 * considered  as something that  could actually time out. */
			if unlikely(deadline < now) {
				caller = next;
				goto do_timeout_thread;
			}
			break;
		}
	}
	assert(deadline >= now);

	/* Convert the effective deadline into a TSC value. */
	tsc_deadline_value = ktime_future_to_tsc(me, deadline);

	/* Set the final TSC deadline to indicate when
	 * to trigger the  next preemptive  interrupt. */
	if (tsc_deadline_value == TSC_MAX) {
		tsc_nodeadline(me);
	} else {
		tsc_now = tsc_deadline(me, tsc_deadline_value);
		if (tsc_now >= tsc_deadline_value) {
			/* Deadline has already expired... */
			caller = next;
			deadline -= now;
			if unlikely(deadline == sched_quantum_min) {
				ktime_t new_quantum_min;
				/* TODO: We might get here due to an SMM interrupt, in which case
				 *       it  wasn't  actually the  fault  of `sched_quantum_min'! */
				new_quantum_min = sched_quantum_min * 2;
				printk(KERN_WARNING "[sched] Raise minimum quantum "
				                    "%" PRIuN(__SIZEOF_KTIME_T__) " -> "
				                    "%" PRIuN(__SIZEOF_KTIME_T__) "\n",
				       sched_quantum_min, new_quantum_min);
				sched_quantum_min = new_quantum_min;
			}
			if unlikely(deadline == sched_quantum_max) {
				ktime_t new_quantum_max;
				new_quantum_max = sched_quantum_max * 2;
				printk(KERN_WARNING "[sched] Raise maximum quantum "
				                    "%" PRIuN(__SIZEOF_KTIME_T__) " -> "
				                    "%" PRIuN(__SIZEOF_KTIME_T__) "\n",
				       sched_quantum_max, new_quantum_max);
				sched_quantum_max = new_quantum_max;
			}
			goto again_with_tsc_now;
		}
	}
	/* Switch execution to the next thread. */
	sched_assert();
	return next;
}



/* Unload  the IDLE thread (who must be  the caller), and switch to `next'
 * This function returns the next time the IDLE thread is loaded, at which
 * point preemption will have been re-enabled. */
PRIVATE NOPREEMPT NONNULL((1, 2, 3)) void
NOTHROW(FCALL idle_unload_and_switch_to)(struct cpu *__restrict me,
                                         struct task *__restrict caller,
                                         struct task *__restrict next) {
	ktime_t now, quantum_start, priority_boost;
	tsc_t tsc_now;
	assert(caller == &sched_idle);
	assert(next);
	assert(next->t_flags & TASK_FRUNNING);
	assert(sched.s_runcount >= 2);

	/* Remove caller (the IDLE thread) from the run queue */
	if (sched.s_running_last == caller)
		sched.s_running_last = sched_prev(caller);
	LIST_REMOVE_P(caller, sched_link);
	--sched.s_runcount;
	ATOMIC_AND(caller->t_flags, ~TASK_FRUNNING);

	/* Mark the IDLE thread as unloaded, as documented in,
	 * and   required   by   `struct scheduler::s_running' */
	sched_pself(caller) = NULL;
	sched_next(caller)  = NULL;

	tsc_now = tsc_get(me);
	now     = tsc_now_to_ktime(me, tsc_now);

	/* Gift the remainder of `caller's quantum to `thread' */
	quantum_start = sched_stoptime(caller);
	if unlikely(quantum_start > now)
		quantum_start = now; /* Shouldn't happen... */

	/* Account for time spent being active. */
	sched_activetime(caller) += now - quantum_start;
	sched_stoptime(caller) = now;

	/* If the caller only had a really short amount of time left for
	 * their current quantum, and `thread' has already been  waiting
	 * for a  really long  time, then  `thread' must  still get  its
	 * priority boost! */
	if (OVERFLOW_USUB(now, sched_stoptime(next), &priority_boost))
		priority_boost = 0;

	/* Update the stop timestamp of `next' */
	move_thread_to_back_of_runqueue(me, next, now);

	/* Reload the current deadline. */
	next = sched_intern_reload_deadline(me, next, quantum_start,
	                                    priority_boost, now,
	                                    tsc_now, false);

	/* Continue execution in the next thread. */
	assert(next->t_flags & TASK_FRUNNING);

	/* Check for special case: The switch wasn't actually done. */
	if likely(next != caller) {
		FORCPU(me, thiscpu_sched_current) = next;
		sched_assert();
		cpu_run_current_and_remember_nopr(caller);
		/* HINT: If your debugger  break here, it  means that  your
		 *       thread is probably waiting on some kind of signal. */
		assert(caller->t_flags & TASK_FRUNNING);
	} else {
		sched_assert();
		PREEMPTION_ENABLE();
	}
}

#ifndef CONFIG_NO_SMP
/* Transfer `thread' to some CPU other than `me'
 * Returns `false' if doing so is impossible due to the affinity of `thread',
 * or if the scheduler decides that the  caller should keep on holding on  to
 * `thread' for the time being.
 *
 * NOTE: When `true' is returned, then this function will have inherited a
 *       reference to `thread'! */
PRIVATE NOBLOCK bool
NOTHROW(FCALL task_transfer_thread_to_other_cpu)(struct cpu *__restrict me,
                                                 struct task *__restrict thread,
                                                 cpuset_ptr_t pnotify_cpus) {
	struct cpu *target;
	assert(!(thread->t_flags & TASK_FRUNNING));
	assert(thread != &sched_idle);
	if (thread->t_flags & (TASK_FKEEPCORE | TASK_FTERMINATING))
		return false; /* Thread cannot be transferred. */
	target = &bootcpu; /* TODO: Dynamically determine based on recent load. */
	assert(thread->t_cpu == me);
	if unlikely(target == me)
		return false; /* Must be a different thread. */
	/* Schedule `thread' as pending on `target'
	 * NOTE: The  order in which we set the RUNNING flag, and change
	 *       the thread's CPU doesn't matter, but both modifications
	 *       individually must be atomic! */
	ATOMIC_OR(thread->t_flags, TASK_FRUNNING);
	ATOMIC_WRITE(thread->t_cpu, target);
	sched_intern_addpending(target, thread);
	/* Schedule the target CPU to receive a wake-up once our caller is finished. */
	CPUSET_INSERT(CPUSET_IND(pnotify_cpus), target->c_id);
	return true;
}

/* Send wake-up requests to each of the given `cpus' */
PRIVATE NOBLOCK void
NOTHROW(FCALL cpuset_wake)(cpuset_t cpus) {
	unsigned int i;
	for (i = 0; i < cpu_count; ++i) {
		if (CPUSET_CONTAINS(cpus, i))
			cpu_wake(cpu_vector[i]);
	}
}

#endif /* !CONFIG_NO_SMP */



PUBLIC void NOTHROW(KCALL cpu_deepsleep)(void) {
	struct task *caller = THIS_TASK;
	struct cpu *me = FORTASK(caller, this_cpu);
again:
	assertf(caller == &sched_idle,
	        "cpu_deepsleep() may only be called form a cpu's IDLE thread!");
	assertf(FORCPU(me, thiscpu_sched_current) == caller,
	        "cpu_deepsleep() may only be called form a cpu's IDLE thread!");
	assertf(FORCPU(me, thiscpu_sched_override) == NULL,
	        "cpu_deepsleep() cannot be called while a scheduling override is active");
	assert(caller->t_flags & TASK_FRUNNING);
	assert(me->c_state == CPU_STATE_RUNNING);
	PREEMPTION_DISABLE();
	sched_assert();
	sched_assert_in_runqueue(caller);

	/* First check: Are there any running threads we can switch to? */
	if (sched.s_runcount >= 2) {
		struct task *next;
		next = sched_s_running_first;
		if (next == caller)
			next = sched_next(next);
		assert(next != caller);

		/* Switch to the next available thread. */
		idle_unload_and_switch_to(me, caller, next);
		return;
	}


#ifndef CONFIG_NO_SMP
	/* Check for pending threads, and if there are  some,
	 * load them and directly yield to the first of them. */
	{
		REF struct task *chain;
		chain = ATOMIC_XCH(FORCPU(me, thiscpu_sched_pending), NULL);
		if (chain != NULL) {
			struct task *next;
			next = sched_intern_loadpending(me, caller, chain);
			if (next != caller) {
				FORCPU(me, thiscpu_sched_current) = next;
				cpu_run_current_and_remember_nopr(caller);
				return;
			}
			/* Additional threads were loaded.
			 * -> Try to yield to one of them. */
			goto again;
		}
	}

	/* Check if there are any pending soft- or hard-ware IPIs */
	if (arch_cpu_hwipi_pending_nopr() || arch_cpu_swipi_pending_nopr(me)) {
		cpu_ipi_service_nopr();
#ifdef PREEMPTION_ENABLE_P
		PREEMPTION_ENABLE_P();
#else /* PREEMPTION_ENABLE_P */
		PREEMPTION_ENABLE();
#endif /* !PREEMPTION_ENABLE_P */
		goto again;
	}
	if (me != &bootcpu) {
		/* We're not the boot CPU,  so we can be shut  off.
		 * For this purpose, `sched_shutdown_delay' exists. */
		struct task *thread;
		ktime_t timeout, now, shutdown_timeout;
		tsc_t deadline, tsc_now;
		assert(sched.s_runcount == 1); /* The IDLE thread */

		/* We're only allowed  to shut down  if there  aren't
		 * any  sleeping threads with the TASK_FKEEPCORE flag
		 * set, since we'll need to transfer sleeping threads
		 * to another CPU before shutting down! */
		FOREACH_thiscpu_waiting(thread, me) {
			if (thread->t_flags & (TASK_FKEEPCORE | TASK_FTERMINATING))
				goto cannot_shut_down;
		}

		/* Set-up a timeout before actually shutting down the CPU.
		 * Also: If any of the waiting threads would time out before
		 *       `sched_shutdown_delay' has  passed, don't  actually
		 *       shut down the CPU. */
		timeout = KTIME_INFINITE;
		if (sched.s_waiting_last)
			timeout = sched_timeout(sched_s_waiting);
		tsc_now = tsc_get(me);
		now     = tsc_now_to_ktime(me, tsc_now);
		shutdown_timeout = now + sched_shutdown_delay;
		if (shutdown_timeout >= timeout)
			goto cannot_shut_down; /* Don't shut down the CPU! */

		/* Figure out the deadline for when we're allowed to shut down the CPU. */
		deadline = ktime_future_to_tsc(me, shutdown_timeout);
		tsc_now  = tsc_deadline(me, deadline);
		if likely(tsc_now < deadline) {
			/* Must set ourselves as the  scheduler override to prevent  the
			 * deadline-expired interrupt from changing our custom deadline. */
			FORCPU(me, thiscpu_sched_override) = caller;

			/* TODO: Somehow tell other CPUs that we don't have anything to do.
			 *       Other  CPUs could then make use of that info, and off-load
			 *       threads  with a lot of active-time to us, allowing load to
			 *       be balanced automatically! */

			/* Wait for the deadline to  expire, but still handle  sporadic
			 * interrupts in the mean time.  If new work arrives before  we
			 * get there, roll back everything and resume normal execution. */
			for (;;) {
				PREEMPTION_ENABLE_WAIT_DISABLE();

				/* Check if more work has arrived.
				 * NOTE: Scheduled threads may have changed in the mean time  due
				 *       to another CPU sending an IPI that directly modified our
				 *       CPU's scheduler controller.
				 *       One example for this would be `task_wake()' */
				if (sched.s_runcount > 1) {
disable_custom_deadline_and_start_over:
					FORCPU(me, thiscpu_sched_override) = NULL;
					tsc_nodeadline(me);
					goto again;
				}
				if (FORCPU(me, thiscpu_sched_pending) != NULL)
					goto disable_custom_deadline_and_start_over;
#if 0 /* No need to check for IPIs: If there were any, they would have already been
       * handled while preemption was enabled above, and if there are new ones now,
       * they'll  be handled the next time we get  to the above code, or they'll be
       * noticed by the IPI-check that follows `CPU_STATE_FALLING_ASLEEP' below. */
				if (arch_cpu_hwipi_pending_nopr() || arch_cpu_swipi_pending_nopr(me))
					goto disable_custom_deadline_and_start_over;
#endif
				/* Check if a waiting thread has popped up that  has
				 * a timeout which expires before `shutdown_timeout' */
				if (sched.s_waiting_last != NULL &&
				    sched_timeout(sched_s_waiting) < shutdown_timeout)
					goto disable_custom_deadline_and_start_over;

				/* Re-instate our custom deadline.
				 * Note however that the deadline should still be active... */
				tsc_now = tsc_deadline(me, deadline);
				if (tsc_now >= deadline)
					break; /* The shutdown-timeout has expired. */
			}
			FORCPU(me, thiscpu_sched_override) = NULL;
		}

		/* Yes: Shut down this CPU! */
		ATOMIC_WRITE(me->c_state, CPU_STATE_FALLING_ASLEEP);

		/* Transfer all remaining sleeping threads to other CPUs. */
		{
			cpuset_t pending_cpu_wake;
			struct task **pself, *self, *next;
			pself = &sched_s_waiting;
			CPUSET_CLEAR(pending_cpu_wake);
			while ((self = *pself) != NULL) {
				assert(sched_pself(self) == pself);
				next = sched_next(self);
				assert((sched.s_waiting_last == self) == (next == NULL));
				if (task_transfer_thread_to_other_cpu(me, self, CPUSET_PTR(pending_cpu_wake))) {
					/* Thread was transferred (fix-up our CPU's wait-queue chain) */
					if ((*pself = next) != NULL)
						sched_pself(next) = pself;
					continue;
				}

				/* Thread wasn't transferred.
				 * This means that we won't be able to shut down, so
				 * we might as well stop trying and just get back to
				 * normal execution. */
				ATOMIC_WRITE(me->c_state, CPU_STATE_RUNNING);

				/* Must still send wake-up requests to all CPUs that
				 * received  threads before we've failed to transfer
				 * the most recent thread. */
				cpuset_wake(pending_cpu_wake);
				goto again;
			}

			/* With all sleeping threads transferred, fix-up the waiting-last pointer. */
			assert(sched_s_waiting == NULL);
			sched.s_waiting_last = NULL;

			/* Wake-up all CPUs that received our old threads. */
			cpuset_wake(pending_cpu_wake);
		}

		/* Do  one more check  if new work arrived  since we've changed state,
		 * thus ensuring that the state-transition is interlocked with pending
		 * threads, as well as pending hard- and software IPIs. */
		if (FORCPU(me, thiscpu_sched_pending) != NULL ||
		    arch_cpu_hwipi_pending_nopr() ||
		    arch_cpu_swipi_pending_nopr(me)) {
			ATOMIC_WRITE(me->c_state, CPU_STATE_RUNNING);
			goto again;
		}
		printk(KERN_INFO "[sched:cpu#%u][+] Enter deep-sleep\n", me->c_id);
		cpu_enter_deepsleep(me);
		printk(KERN_INFO "[sched:cpu#%u][-] Leave deep-sleep\n", me->c_id);
		return;
	}
cannot_shut_down:
#endif /* !CONFIG_NO_SMP */

	/* It has been decided that our CPU can't be turned
	 * off for one reason or another.
	 *
	 * Setup the TSC deadline to trigger an interrupt
	 * once  the first waiting  thread has timed out. */
	if (sched.s_waiting_last) {
		struct task *first_waiting;
		ktime_t timeout;
		tsc_t deadline, now;
		first_waiting = sched_s_waiting;
		assert(first_waiting);
		timeout  = sched_timeout(first_waiting);
		deadline = ktime_to_tsc(me, timeout);
		now      = tsc_deadline(me, deadline);
		if (now >= deadline) {
			/* Deadline has already expired! */
			struct task *next;
			next = tsc_deadline_passed(me, caller, now);
			if (next != caller) {
				FORCPU(me, thiscpu_sched_current) = next;
				cpu_run_current_and_remember_nopr(caller);
				return;
			}
		}
	} else {
		/* Nothing to wait for -> Disable the TSC deadline so it doesn't wake us up. */
		tsc_nodeadline(me);
	}

	/* Re-enable preemption and wait until something happens. */
	PREEMPTION_ENABLE_WAIT();
}




/* Acquire/release the scheduler override lock for the calling  CPU,
 * thereby effectively seizing control over  the calling CPU to  the
 * point where regular scheduling mechanism will not let the calling
 * thread hand over control to anyone else:
 *   - task_yield()
 *   - task_wake()
 *   - tsc_deadline_passed()
 *
 * Note that this is quite similar to disabling preemption,  however
 * many cases exist where disabling preemption is overkill, or maybe
 * even be counter-productive  (i.e. certain functionality  requires
 * that preemption remain enabled, such as disk-, user-, or network-
 * I/O)
 *
 * Another similar mechanism  is to set  the TASK_FKEEPCORE flag  for
 * one's own thread, which, while not getting set explicitly by these
 * functions,  is implicitly  set whenever  a thread  is a scheduling
 * override.
 *
 * Note that other CPUs will continue to run normally, meaning that
 * these functions would only seize complete control of the  system
 * when `cpu_count == 1'
 *
 * NOTE: These functions can be called both with and without preemption
 *       enabled, however `sched_override_yieldto()' may only be called
 *       when preemption is enabled, additionally leaving this check up
 *       to the caller by only repeating it as an internal assertion.
 *
 * HINT: When a scheduler override  is active, the scheduler's  preemptive
 *       interrupt handler will not modify the currently set TSC deadline,
 *       leaving that facility up for use by the caller!
 *
 * WARNING: These function do not operate recursively. Calling...
 *     ... `sched_override_start()' with  `thiscpu_sched_override != NULL'  isn't  allowed
 *     ... `sched_override_end()' with `thiscpu_sched_override == NULL' also isn't allowed
 * @return: * : The CPU that the calling thread managed to seize (same as `THIS_CPU') */
PUBLIC NOBLOCK ATTR_RETNONNULL struct cpu *
NOTHROW(FCALL sched_override_start)(void) {
	struct task *caller;
	struct cpu *me;
	preemption_flag_t was;
	caller = THIS_TASK;
	preemption_pushoff(&was);
	COMPILER_READ_BARRIER();
	me = caller->t_cpu;
	assert(!sched_override);

	/* Set the calling thread as scheduling override. */
	ATOMIC_WRITE(sched_override, caller);

	/* Disable any previously set deadline. */
	tsc_nodeadline(me);
	preemption_pop(&was);
	return me;
}

PUBLIC NOBLOCK void
NOTHROW(FCALL sched_override_end)(void) {
	struct task *caller, *next;
	struct cpu *me;
	tsc_t tsc_now;
	preemption_flag_t was;
	caller = THIS_TASK;
	me     = caller->t_cpu;
	assert(sched_override == caller);
	preemption_pushoff(&was);
	ATOMIC_WRITE(sched_override, NULL);
	tsc_now = tsc_get(me);

	/* Reload the TSC deadline for the calling thread, thus accounting for
	 * the additional time  it spent being  an active scheduler  override. */
	next = sched_intern_reload_deadline(me, caller, sched_stoptime(caller),
	                                    0, tsc_now_to_ktime(me, tsc_now),
	                                    tsc_now, !preemption_wason(&was));
	if (next != caller) {
		assert(preemption_wason(&was));

		/* Directly resume execution in `next' */
		FORCPU(me, thiscpu_sched_current) = next;
		sched_assert();

		/* Switch over to the next thread. */
		cpu_run_current_and_remember_nopr(caller);
	}
	preemption_pop(&was);
}

/* While the caller is holding a scheduler override, pass over that
 * privilege to `thread', and continue execution in the context  of
 * that thread.
 * This  function will only  return when `thread'  switches back to the
 * caller's thread, or when `thread', or whoever it passes the override
 * to ends up calling `sched_override_end()'
 * NOTE: This function must be called with preemption enabled.
 *       Otherwise,  an  internal assertion  check  will fail.
 * NOTE: When `thread == THIS_TASK', this function behaves as a no-op
 *       In this case, the function doesn't assert that preemption is
 *       enabled when called.
 * NOTE: The caller must ensure that `thread' has the `TASK_FRUNNING'
 *       flag set (meaning that `thread' must be apart of the current
 *       CPU's run-queue). */
PUBLIC NONNULL((1)) void
NOTHROW(FCALL sched_override_yieldto)(struct task *__restrict thread) {
	struct cpu *me;
	struct task *caller;
	caller = THIS_TASK;
	me     = caller->t_cpu;
	assert(sched_override == caller);
	if (thread == caller)
		return; /* No-op */
	assert(PREEMPTION_ENABLED());
	assert(thread->t_cpu == me);
	assert(thread->t_flags & TASK_FRUNNING);
	PREEMPTION_DISABLE();

	/* Directly switch over to  continue execution on `thread',  while
	 * simultaneously passing over control of the scheduling override. */
	FORCPU(me, thiscpu_sched_override) = thread;
	FORCPU(me, thiscpu_sched_current)  = thread;
	cpu_run_current_and_remember_nopr(caller);
}


#ifdef CONFIG_NO_SMP
DEFINE_PUBLIC_ALIAS(sched_super_override_start, sched_override_start);
DEFINE_PUBLIC_ALIAS(sched_super_override_end, sched_override_end);

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(FCALL sched_super_override_trystart)(void) {
	sched_override_start();
	return true;
}

PUBLIC NOBLOCK ATTR_PURE bool
NOTHROW(FCALL sched_super_override_active)(void) {
	return FORCPU(&bootcpu, thiscpu_sched_override) != NULL;
}
#endif /* !CONFIG_NO_SMP */

DECL_END


#endif /* !GUARD_KERNEL_SRC_SCHED_SCHEDULER_C */
