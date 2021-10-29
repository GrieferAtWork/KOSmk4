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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SHARED_LOCK_H
#define GUARD_KERNEL_INCLUDE_SCHED_SHARED_LOCK_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/signal.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

#ifdef __CC__
DECL_BEGIN

struct shared_lock {
	struct sig   sl_sig;  /* Signal send when the shared_lock is unlocked. */
	unsigned int sl_lock; /* Lock word. (non-zero if held) */
};
#define SHARED_LOCK_INIT               { SIG_INIT, 0 }
#define SHARED_LOCK_INIT_LOCKED        { SIG_INIT, 1 }
#define shared_lock_init(self)         (void)(sig_init(&(self)->sl_sig), (self)->sl_lock = 0)
#define shared_lock_init_locked(self)  (void)(sig_init(&(self)->sl_sig), (self)->sl_lock = 1)
#define shared_lock_cinit(self)        (void)(sig_cinit(&(self)->sl_sig), __hybrid_assert((self)->sl_lock == 0))
#define shared_lock_cinit_locked(self) (void)(sig_cinit(&(self)->sl_sig), (self)->sl_lock = 1)
#define shared_lock_acquired(self)     (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) != 0)
#define shared_lock_available(self)    (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) == 0)
#define shared_lock_broadcast_for_fini(self) \
	sig_broadcast_for_fini(&(self)->sl_sig)

#define shared_lock_tryacquire(self) \
	(__hybrid_atomic_xch((self)->sl_lock, 1, __ATOMIC_ACQUIRE) == 0)

/* Release a lock from a given shared_lock.
 * @return: true:  A waiting thread was signaled.
 * @return: false: Either no  thread was  signaled, or  the
 *                 lock remains held by the calling thread. */
#if defined(NDEBUG) || defined(NDEBUG_SYNC)
#define shared_lock_release(self)                                 \
	(__hybrid_atomic_store((self)->sl_lock, 0, __ATOMIC_RELEASE), \
	 sig_send(&(self)->sl_sig))
#else /* NDEBUG || NDEBUG_SYNC */
#define shared_lock_release(self)                                 \
	(__hybrid_assert((self)->sl_lock != 0),                       \
	 __hybrid_atomic_store((self)->sl_lock, 0, __ATOMIC_RELEASE), \
	 sig_send(&(self)->sl_sig))
#endif /* !NDEBUG || !NDEBUG_SYNC */


/* Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
FUNDEF NONNULL((1)) __BOOL KCALL
shared_lock_acquire(struct shared_lock *__restrict self,
                    ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_WOULDBLOCK, ...);

/* Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
FUNDEF WUNUSED NONNULL((1)) __BOOL
NOTHROW(KCALL shared_lock_acquire_nx)(struct shared_lock *__restrict self,
                                      ktime_t abs_timeout DFL(KTIME_INFINITE));

/* Shared-lock polling functions. */
#define shared_lock_pollconnect_ex(self, cb) cb(&(self)->sl_sig)
#define shared_lock_poll_unlikely_ex(self, cb) \
	(shared_lock_pollconnect_ex(self, cb),     \
	 shared_lock_available(self))
#ifdef __OPTIMIZE_SIZE__
#define shared_lock_poll_ex(self, cb) \
	shared_lock_poll_unlikely_ex(self, cb)
#else /* __OPTIMIZE_SIZE__ */
#define shared_lock_poll_ex(self, cb)       \
	(shared_lock_available(self) ||         \
	 (shared_lock_pollconnect_ex(self, cb), \
	  shared_lock_available(self)))
#endif /* !__OPTIMIZE_SIZE__ */
#define shared_lock_pollconnect(self)   shared_lock_pollconnect_ex(self, task_connect_for_poll)
#define shared_lock_poll(self)          shared_lock_poll_ex(self, task_connect_for_poll)
#define shared_lock_poll_unlikely(self) shared_lock_poll_unlikely_ex(self, task_connect_for_poll)


/* Integration into the sync_* API-system. */
__DEFINE_SYNC_MUTEX(struct shared_lock,
                    shared_lock_tryacquire,
                    shared_lock_acquire,
                    shared_lock_acquire_nx,
                    shared_lock_release,
                    shared_lock_acquired,
                    shared_lock_available)

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SHARED_LOCK_H */
