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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SHARED_RWLOCK_H
#define GUARD_KERNEL_INCLUDE_SCHED_SHARED_RWLOCK_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/signal.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/byteorder.h>
#include <hybrid/sched/__yield.h>

#ifdef __CC__
DECL_BEGIN

/* Same  as the regular `struct rwlock', however neither read-after-write,
 * nor write-after-read is  allowed. However  read-after-read is  allowed,
 * and unlike with `struct rwlock', read/write-locks created by one thread
 * can be inherited by another.
 * Essentially, a `shared_rwlock' is the  same as an `atomic_rwlock',  with
 * the addition that a `shared_rwlock' includes a signal with which one can
 * do blocking waits for the lock to become available. */

#if __SIZEOF_POINTER__ >= 8
#define SHARED_RWLOCK_RMASK __UINT64_C(0x7fffffffffffffff)
#define SHARED_RWLOCK_WFLAG __UINT64_C(0x8000000000000000)
#else /* __SIZEOF_POINTER__ >= 8 */
#define SHARED_RWLOCK_RMASK __UINT32_C(0x7fffffff)
#define SHARED_RWLOCK_WFLAG __UINT32_C(0x80000000)
#endif /* __SIZEOF_POINTER__ < 8 */

struct shared_rwlock {
	WEAK uintptr_t sl_lock;   /* Lock state (Set of `SHARED_RWLOCK_*') */
	struct sig     sl_rdwait; /* Signal broadcast to wake-up readers. */
	struct sig     sl_wrwait; /* Signal broadcast to wake-up writers. */
};

#define SHARED_RWLOCK_INIT              { 0, SIG_INIT, SIG_INIT }
#define SHARED_RWLOCK_INIT_READ         { 1, SIG_INIT, SIG_INIT }
#define SHARED_RWLOCK_INIT_WRITE        { SHARED_RWLOCK_WFLAG, SIG_INIT, SIG_INIT }
#define shared_rwlock_init(self)        ((self)->sl_lock = 0, sig_init(&(self)->sl_rdwait), sig_init(&(self)->sl_wrwait))
#define shared_rwlock_init_read(self)   (void)((self)->sl_lock = 1, sig_init(&(self)->sl_rdwait), sig_init(&(self)->sl_wrwait))
#define shared_rwlock_init_write(self)  (void)((self)->sl_lock = SHARED_RWLOCK_WFLAG, sig_init(&(self)->sl_rdwait), sig_init(&(self)->sl_wrwait))
#define shared_rwlock_cinit(self)       (__hybrid_assert((self)->sl_lock == 0), sig_cinit(&(self)->sl_rdwait), sig_cinit(&(self)->sl_wrwait))
#define shared_rwlock_cinit_read(self)  (void)(__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = 1, sig_cinit(&(self)->sl_rdwait), sig_cinit(&(self)->sl_wrwait))
#define shared_rwlock_cinit_write(self) (void)(__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = SHARED_RWLOCK_WFLAG, sig_cinit(&(self)->sl_rdwait), sig_cinit(&(self)->sl_wrwait))
#define shared_rwlock_broadcast_for_fini(self)   \
	(sig_broadcast_for_fini(&(self)->sl_rdwait), \
	 sig_broadcast_for_fini(&(self)->sl_wrwait))

#define shared_rwlock_reading(self)  (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) != 0)
#define shared_rwlock_writing(self)  (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) & SHARED_RWLOCK_WFLAG)
#define shared_rwlock_canread(self)  (!(__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) & SHARED_RWLOCK_WFLAG))
#define shared_rwlock_canwrite(self) (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) == 0)

LOCAL NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_tryread)(struct shared_rwlock *__restrict self);
LOCAL NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_trywrite)(struct shared_rwlock *__restrict self);
FUNDEF NONNULL((1)) void FCALL shared_rwlock_read(struct shared_rwlock *__restrict self, ktime_t abs_timeout DFL(KTIME_INFINITE)) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) void FCALL shared_rwlock_write(struct shared_rwlock *__restrict self, ktime_t abs_timeout DFL(KTIME_INFINITE)) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_read_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout DFL(KTIME_INFINITE));
FUNDEF NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_write_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout DFL(KTIME_INFINITE));

/* Try to upgrade a read-lock to a write-lock. Return `FALSE' upon failure. */
LOCAL NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL shared_rwlock_tryupgrade)(struct shared_rwlock *__restrict self);

/* NOTE: The lock is always upgraded, but when `FALSE' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources. */
LOCAL NONNULL((1)) __BOOL
(FCALL shared_rwlock_upgrade)(struct shared_rwlock *__restrict self,
                              ktime_t abs_timeout DFL(KTIME_INFINITE))
		THROWS(E_WOULDBLOCK);

/* NOTE: The lock is always upgraded for `return != 0', but when `2' is returned,
 *       no lock may have been held  temporarily, meaning that the caller  should
 *       re-load local copies of affected resources.
 * NOTE: When `0' is returned, the original read-lock created by the caller has
 *       already been released. */
LOCAL NONNULL((1)) unsigned int
NOTHROW(FCALL shared_rwlock_upgrade_nx)(struct shared_rwlock *__restrict self,
                                        ktime_t abs_timeout DFL(KTIME_INFINITE));

/* Downgrade a write-lock to a read-lock (Always succeeds). */
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL shared_rwlock_downgrade)(struct shared_rwlock *__restrict self);

/* End reading/writing/either.
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL shared_rwlock_endwrite)(struct shared_rwlock *__restrict self);
LOCAL NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL shared_rwlock_endread)(struct shared_rwlock *__restrict self);
LOCAL NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL shared_rwlock_end)(struct shared_rwlock *__restrict self);

/* Shared R/W-lock polling functions. */
#define shared_rwlock_pollconnect_read_ex(self, cb)  cb(&(self)->sl_rdwait)
#define shared_rwlock_pollconnect_write_ex(self, cb) cb(&(self)->sl_wrwait)
#ifdef __OPTIMIZE_SIZE__
#define shared_rwlock_pollread_ex(self, cb)       \
	(shared_rwlock_pollconnect_read_ex(self, cb), \
	 shared_rwlock_canread(self))
#define shared_rwlock_pollwrite_ex(self, cb)       \
	(shared_rwlock_pollconnect_write_ex(self, cb), \
	 shared_rwlock_canwrite(self))
#else /* __OPTIMIZE_SIZE__ */
#define shared_rwlock_pollread_ex(self, cb)        \
	(shared_rwlock_canread(self) ||                \
	 (shared_rwlock_pollconnect_read_ex(self, cb), \
	  shared_rwlock_canread(self)))
#define shared_rwlock_pollwrite_ex(self, cb)        \
	(shared_rwlock_canwrite(self) ||                \
	 (shared_rwlock_pollconnect_write_ex(self, cb), \
	  shared_rwlock_canwrite(self)))
#endif /* !__OPTIMIZE_SIZE__ */
#define shared_rwlock_pollconnect_read(self)  shared_rwlock_pollconnect_read_ex(self, task_connect_for_poll)
#define shared_rwlock_pollconnect_write(self) shared_rwlock_pollconnect_write_ex(self, task_connect_for_poll)
#define shared_rwlock_pollread(self)          shared_rwlock_pollread_ex(self, task_connect_for_poll)
#define shared_rwlock_pollwrite(self)         shared_rwlock_pollwrite_ex(self, task_connect_for_poll)


#if !defined(__INTELLISENSE__)
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL shared_rwlock_endwrite)(struct shared_rwlock *__restrict self) {
	COMPILER_BARRIER();
#ifdef NDEBUG
	__hybrid_atomic_store(self->sl_lock, 0, __ATOMIC_RELEASE);
#else /* NDEBUG */
	uintptr_t f;
	do {
		f = __hybrid_atomic_load(self->sl_lock, __ATOMIC_ACQUIRE);
		__hybrid_assertf(f & SHARED_RWLOCK_WFLAG, "Lock isn't in write-mode (%x)", f);
	} while (!__hybrid_atomic_cmpxch_weak(self->sl_lock, f, 0, __ATOMIC_RELEASE, __ATOMIC_RELAXED));
#endif /* !NDEBUG */
	if (!sig_send(&self->sl_wrwait))
		sig_broadcast(&self->sl_rdwait);
}

LOCAL NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL shared_rwlock_endread)(struct shared_rwlock *__restrict self) {
	COMPILER_READ_BARRIER();
#ifdef NDEBUG
	uintptr_t result;
	result = __hybrid_atomic_decfetch(self->sl_lock, __ATOMIC_RELEASE);
	if (result == 0)
		sig_send(&self->sl_wrwait);
	return result == 0;
#else /* NDEBUG */
	uintptr_t f;
	do {
		f = __hybrid_atomic_load(self->sl_lock, __ATOMIC_ACQUIRE);
		__hybrid_assertf(!(f & SHARED_RWLOCK_WFLAG), "Lock is in write-mode (%x)", f);
		__hybrid_assertf(f != 0, "Lock isn't held by anyone");
	} while (!__hybrid_atomic_cmpxch_weak(self->sl_lock, f, f - 1,
	                                      __ATOMIC_RELEASE, __ATOMIC_RELAXED));
	if (f == 1)
		sig_send(&self->sl_wrwait);
	return f == 1;
#endif /* !NDEBUG */
}

LOCAL NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL shared_rwlock_end)(struct shared_rwlock *__restrict self) {
	uintptr_t __temp, __newval;
	COMPILER_BARRIER();
	do {
		__temp = __hybrid_atomic_load(self->sl_lock, __ATOMIC_ACQUIRE);
		if (__temp & SHARED_RWLOCK_WFLAG) {
			__hybrid_assert(!(__temp & SHARED_RWLOCK_RMASK));
			__newval = 0;
		} else {
			__hybrid_assertf(__temp != 0, "No remaining read-locks");
			__newval = __temp - 1;
		}
	} while (!__hybrid_atomic_cmpxch_weak(self->sl_lock, __temp, __newval,
	                                      __ATOMIC_RELEASE, __ATOMIC_RELAXED));
	if (!__newval) {
		if (!sig_send(&self->sl_wrwait))
			sig_broadcast(&self->sl_rdwait);
	}
	return __newval == 0;
}

LOCAL NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL shared_rwlock_tryread)(struct shared_rwlock *__restrict self) {
	uintptr_t __temp;
	do {
		__temp = __hybrid_atomic_load(self->sl_lock, __ATOMIC_ACQUIRE);
		if (__temp & SHARED_RWLOCK_WFLAG)
			return 0;
		__hybrid_assert((__temp & SHARED_RWLOCK_RMASK) != SHARED_RWLOCK_RMASK);
	} while (!__hybrid_atomic_cmpxch_weak(self->sl_lock, __temp, __temp + 1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED));
	COMPILER_READ_BARRIER();
	return 1;
}

LOCAL NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL shared_rwlock_trywrite)(struct shared_rwlock *__restrict self) {
	if (!__hybrid_atomic_cmpxch(self->sl_lock, 0, SHARED_RWLOCK_WFLAG, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED))
		return 0;
	COMPILER_BARRIER();
	return 1;
}

/* Try to upgrade a read-lock to a write-lock. Return `FALSE' upon failure. */
LOCAL NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL shared_rwlock_tryupgrade)(struct shared_rwlock *__restrict self) {
	uintptr_t __temp;
	do {
		__temp = __hybrid_atomic_load(self->sl_lock, __ATOMIC_ACQUIRE);
		if (__temp != 1)
			return 0;
	} while (!__hybrid_atomic_cmpxch_weak(self->sl_lock, __temp, SHARED_RWLOCK_WFLAG,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_RELAXED));
	COMPILER_WRITE_BARRIER();
	return 1;
}

/* NOTE: The lock is always upgraded, but when `FALSE' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources. */
LOCAL NONNULL((1)) __BOOL
(FCALL shared_rwlock_upgrade)(struct shared_rwlock *__restrict self,
                              ktime_t abs_timeout)
		THROWS(E_WOULDBLOCK) {
	if (shared_rwlock_tryupgrade(self))
		return 1;
	shared_rwlock_endread(self);
	shared_rwlock_write(self, abs_timeout);
	return 0;
}

/* NOTE: The lock is always upgraded for `return != 0', but when `2' is returned,
 *       no lock may have been held  temporarily, meaning that the caller  should
 *       re-load local copies of affected resources.
 * NOTE: When `0' is returned, the original read-lock created by the caller has
 *       already been released. */
LOCAL NONNULL((1)) unsigned int
NOTHROW(FCALL shared_rwlock_upgrade_nx)(struct shared_rwlock *__restrict self,
                                        ktime_t abs_timeout) {
	if (shared_rwlock_tryupgrade(self))
		return 1;
	shared_rwlock_endread(self);
	if (!shared_rwlock_write_nx(self, abs_timeout))
		return 0;
	return 2;
}

/* Downgrade a write-lock to a read-lock (Always succeeds). */
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL shared_rwlock_downgrade)(struct shared_rwlock *__restrict self) {
#ifdef NDEBUG
	__hybrid_atomic_store(self->sl_lock, 1, __ATOMIC_ACQ_REL);
#else /* NDEBUG */
	uintptr_t f;
	COMPILER_WRITE_BARRIER();
	do {
		f = __hybrid_atomic_load(self->sl_lock, __ATOMIC_ACQUIRE);
		__hybrid_assertf(f == SHARED_RWLOCK_WFLAG, "Lock not in write-mode (%x)", f);
	} while (!__hybrid_atomic_cmpxch_weak(self->sl_lock, f, 1,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_RELAXED));
	sig_broadcast(&self->sl_rdwait); /* Allow for more readers. */
#endif /* !NDEBUG */
}
#endif /* !__INTELLISENSE__ */

__DEFINE_SYNC_RWLOCK(struct shared_rwlock,
                     shared_rwlock_tryread,
                     shared_rwlock_read,
                     shared_rwlock_read_nx,
                     shared_rwlock_endread,
                     shared_rwlock_reading,
                     shared_rwlock_canread,
                     shared_rwlock_trywrite,
                     shared_rwlock_write,
                     shared_rwlock_write_nx,
                     shared_rwlock_endwrite,
                     shared_rwlock_writing,
                     shared_rwlock_canwrite,
                     shared_rwlock_end,
                     shared_rwlock_tryupgrade,
                     shared_rwlock_upgrade,
                     shared_rwlock_upgrade_nx,
                     shared_rwlock_downgrade)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SHARED_RWLOCK_H */
