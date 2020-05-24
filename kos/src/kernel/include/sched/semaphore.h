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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SEMAPHORE_H
#define GUARD_KERNEL_INCLUDE_SCHED_SEMAPHORE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>
#include <sched/signal.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

#include <stdbool.h>

DECL_BEGIN

#ifdef __CC__
struct task;
struct timespec;

struct semaphore {
	struct sig s_avail; /* Signal send for every ticket made available. */
	uintptr_t  s_count; /* # of available tickets. */
};

#define SEMAPHORE_INIT(n) { SIG_INIT, n }
#define semaphore_init(x, n) (void)(sig_init(&(x)->s_avail), (x)->s_count = (n))
#define semaphore_cinit(x, n)               \
	(sig_cinit(&(x)->s_avail),              \
	 (__builtin_constant_p(n) && (n) == 0)  \
	 ? (__hybrid_assert((x)->s_count == 0)) \
	 : (void)((x)->s_count = (n)))
#define semaphore_count(x) __hybrid_atomic_load((x)->s_count, __ATOMIC_ACQUIRE)
#define semaphore_available(x) (semaphore_count(x) != 0)

/* Try to acquire a tick to the given semaphore. */
LOCAL NOBLOCK WUNUSED NONNULL((1)) bool
NOBLOCK(FCALL semaphore_trywait)(struct semaphore *__restrict self) {
	uintptr_t count;
	do {
		count = __hybrid_atomic_load(self->s_count, __ATOMIC_ACQUIRE);
		if (!count)
			return false;
	} while (!__hybrid_atomic_cmpxch_weak(self->s_count, count, count - 1,
	                                      __ATOMIC_SEQ_CST,
	                                      __ATOMIC_SEQ_CST));
	return true;
}

/* Acquire a ticked from the given semaphore, or block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a ticket.
 * @return: false: The given `abs_timeout' has expired. */
LOCAL NONNULL((1)) bool
(FCALL semaphore_wait)(struct semaphore *__restrict self,
                       struct timespec const *abs_timeout DFL(__NULLPTR))
                       THROWS(E_BADALLOC, E_WOULDBLOCK) {
	uintptr_t count;
again:
	do {
		count = __hybrid_atomic_load(self->s_count, __ATOMIC_ACQUIRE);
		if (!count) {
			TASK_POLL_BEFORE_CONNECT({
				count = __hybrid_atomic_load(self->s_count, __ATOMIC_ACQUIRE);
				if (count != 0)
					goto do_exchange;
			});
			task_connect(&self->s_avail);
			count = __hybrid_atomic_load(self->s_count, __ATOMIC_ACQUIRE);
			if likely(!count) {
				if unlikely(!task_waitfor(abs_timeout))
					return false;
				goto again;
			}
			task_disconnectall();
		}
#ifdef CONFIG_YIELD_BEFORE_CONNECT
do_exchange:
		;
#endif
	} while (!__hybrid_atomic_cmpxch_weak(self->s_count, count, count - 1,
	                                      __ATOMIC_SEQ_CST,
	                                      __ATOMIC_SEQ_CST));
	return true;
}


/* Acquire a ticked from the given semaphore, or block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a ticket.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
LOCAL WUNUSED NONNULL((1)) bool
NOTHROW(FCALL semaphore_wait_nx)(struct semaphore *__restrict self,
                                 struct timespec const *abs_timeout DFL(__NULLPTR)) {
	uintptr_t count;
again:
	do {
		count = __hybrid_atomic_load(self->s_count, __ATOMIC_ACQUIRE);
		if (!count) {
			TASK_POLL_BEFORE_CONNECT({
				count = __hybrid_atomic_load(self->s_count, __ATOMIC_ACQUIRE);
				if (count != 0)
					goto do_exchange;
			});
			task_connect(&self->s_avail);
			count = __hybrid_atomic_load(self->s_count, __ATOMIC_ACQUIRE);
			if likely(!count) {
				if unlikely(!task_waitfor_nx(abs_timeout))
					return false;
				goto again;
			}
			task_disconnectall();
		}
#ifdef CONFIG_YIELD_BEFORE_CONNECT
do_exchange:
		;
#endif
	} while (!__hybrid_atomic_cmpxch_weak(self->s_count, count, count - 1,
	                                      __ATOMIC_SEQ_CST,
	                                      __ATOMIC_SEQ_CST));
	return true;
}


/* Make a single ticket available to the given semaphore.
 * @return: true:  A waiting thread was signaled.
 * @return: false: There were no waiting threads, but the ticket was added. */
LOCAL NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL semaphore_post)(struct semaphore *__restrict self) {
	if (__hybrid_atomic_fetchinc(self->s_count, __ATOMIC_SEQ_CST) == 0)
		return sig_send(&self->s_avail); /* Signal a single thread when the first ticket gets added. */
	return false;
}
LOCAL NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL semaphore_altpost)(struct semaphore *__restrict self, struct sig *sender) {
	if (__hybrid_atomic_fetchinc(self->s_count, __ATOMIC_SEQ_CST) == 0)
		return sig_altsend(&self->s_avail, sender); /* Signal a single thread when the first ticket gets added. */
	return false;
}
LOCAL NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL semaphore_postb)(struct semaphore *__restrict self) {
	__hybrid_atomic_fetchinc(self->s_count, __ATOMIC_SEQ_CST);
	return sig_broadcast(&self->s_avail); /* Signal all waiting threads. */
}
LOCAL NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL semaphore_altpostb)(struct semaphore *__restrict self, struct sig *sender) {
	__hybrid_atomic_fetchinc(self->s_count, __ATOMIC_SEQ_CST);
	return sig_altbroadcast(&self->s_avail, sender); /* Signal all waiting threads. */
}


/* Poll the given semaphore for being available, returning `true'
 * if it is, or `false' after connecting to the signal used to
 * indicate a ticket being available. */
LOCAL WUNUSED NONNULL((1)) bool
(FCALL semaphore_poll)(struct semaphore *__restrict self) THROWS(E_BADALLOC) {
	uintptr_t count;
	count = __hybrid_atomic_load(self->s_count, __ATOMIC_ACQUIRE);
	if (count)
		return true;
	task_connect_ghost(&self->s_avail);
	/* Must check again, now that we're connected. */
	count = __hybrid_atomic_load(self->s_count, __ATOMIC_ACQUIRE);
	if unlikely(count)
		return true;
	return false;
}

__DEFINE_SYNC_SEMAPHORE(struct semaphore,
                        semaphore_trywait,
                        semaphore_wait,
                        semaphore_wait_nx,
                        semaphore_post,
                        semaphore_available)
__DEFINE_SYNC_POLL(struct semaphore,
                   semaphore_poll,
                   semaphore_poll)


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SEMAPHORE_H */
