/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SEMAPHORE_H
#define GUARD_KERNEL_INCLUDE_SCHED_SEMAPHORE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>
#include <sched/sig.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

#ifdef __CC__
DECL_BEGIN

struct semaphore {
	struct sig s_avail; /* Signal send for every ticket made available. */
	uintptr_t  s_count; /* [lock(ATOMIC)] # of available tickets. */
};

#define SEMAPHORE_INIT(n) \
	{ SIG_INIT, n }
#define semaphore_init(x, n) \
	(void)(sig_init(&(x)->s_avail), (x)->s_count = (n))
#define semaphore_cinit(x, n)               \
	(sig_cinit(&(x)->s_avail),              \
	 (__builtin_constant_p(n) && (n) == 0)  \
	 ? (__hybrid_assert((x)->s_count == 0)) \
	 : (void)((x)->s_count = (n)))
#define semaphore_count(x) \
	__hybrid_atomic_load(&(x)->s_count, __ATOMIC_ACQUIRE)

/* Try to acquire a tick to the given semaphore. */
LOCAL NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOBLOCK(FCALL semaphore_trywait)(struct semaphore *__restrict self) {
	uintptr_t count;
	do {
		count = __hybrid_atomic_load(&self->s_count, __ATOMIC_ACQUIRE);
		if (!count)
			return 0;
	} while (!__hybrid_atomic_cmpxch_weak(&self->s_count, count, count - 1,
	                                      __ATOMIC_SEQ_CST,
	                                      __ATOMIC_SEQ_CST));
	return 1;
}

/* Acquire a ticked from the given semaphore, or block until `abs_timeout'.
 * @return: true:  Successfully acquired a ticket.
 * @return: false: The given `abs_timeout' has expired. */
FUNDEF BLOCKING NONNULL((1)) __BOOL FCALL
semaphore_wait(struct semaphore *__restrict self,
               ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_WOULDBLOCK);


/* Acquire a ticked from the given semaphore, or block until `abs_timeout'.
 * @return: true:  Successfully acquired a ticket.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
FUNDEF BLOCKING WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL semaphore_wait_nx)(struct semaphore *__restrict self,
                                 ktime_t abs_timeout DFL(KTIME_INFINITE));


/* Make a single ticket available to the given semaphore.
 * @return: true:  A waiting thread was signaled.
 * @return: false: There were no waiting threads, but the ticket was added. */
LOCAL NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL semaphore_post)(struct semaphore *__restrict self) {
	__hybrid_atomic_inc(&self->s_count, __ATOMIC_SEQ_CST);

	/* Wake up exactly one thread for every ticket added. */
	return sig_send(&self->s_avail);
}

/* Post multiple tickets to the semaphore and wake up the same # of threads.
 * @return: * : The # of tickets that will (likely) be consumed immediately. */
LOCAL NOBLOCK NONNULL((1)) size_t
NOTHROW(FCALL semaphore_postmany)(struct semaphore *__restrict self, size_t count) {
	__hybrid_atomic_add(&self->s_count, count, __ATOMIC_SEQ_CST);
	/* Wake up exactly one thread for every ticket added. */
	return sig_sendmany(&self->s_avail, count);
}

/* Semaphore polling functions. */
#define semaphore_available(x)             (semaphore_count(x) != 0)
#define semaphore_pollconnect_ex(self, cb) cb(&(self)->s_avail)
#ifdef __OPTIMIZE_SIZE__
#define semaphore_poll_ex(self, cb)      \
	(semaphore_pollconnect_ex(self, cb), \
	 semaphore_available(self))
#else /* __OPTIMIZE_SIZE__ */
#define semaphore_poll_ex(self, cb)       \
	(semaphore_available(self) ||         \
	 (semaphore_pollconnect_ex(self, cb), \
	  semaphore_available(self)))
#endif /* !__OPTIMIZE_SIZE__ */
#define semaphore_pollconnect(self) semaphore_pollconnect_ex(self, task_connect_for_poll)
#define semaphore_poll(self)        semaphore_poll_ex(self, task_connect_for_poll)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SEMAPHORE_H */
