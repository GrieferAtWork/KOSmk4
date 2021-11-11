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

/* `shared_rwlock' is the  same as an `atomic_rwlock', with the
 * addition that a `shared_rwlock' includes a signal with which
 * one can do blocking waits for the lock to become available. */

struct shared_rwlock {
	WEAK uintptr_t sl_lock;   /* Lock state (Set of `SHARED_RWLOCK_*') */
	struct sig     sl_rdwait; /* Signal broadcast to wake-up readers. */
	struct sig     sl_wrwait; /* Signal broadcast to wake-up writers. */
};

#define SHARED_RWLOCK_INIT              { 0, SIG_INIT, SIG_INIT }
#define SHARED_RWLOCK_INIT_READ         { 1, SIG_INIT, SIG_INIT }
#define SHARED_RWLOCK_INIT_WRITE        { (uintptr_t)-1, SIG_INIT, SIG_INIT }
#define shared_rwlock_init(self)        ((self)->sl_lock = 0, sig_init(&(self)->sl_rdwait), sig_init(&(self)->sl_wrwait))
#define shared_rwlock_init_read(self)   (void)((self)->sl_lock = 1, sig_init(&(self)->sl_rdwait), sig_init(&(self)->sl_wrwait))
#define shared_rwlock_init_write(self)  (void)((self)->sl_lock = (uintptr_t)-1, sig_init(&(self)->sl_rdwait), sig_init(&(self)->sl_wrwait))
#define shared_rwlock_cinit(self)       (__hybrid_assert((self)->sl_lock == 0), sig_cinit(&(self)->sl_rdwait), sig_cinit(&(self)->sl_wrwait))
#define shared_rwlock_cinit_read(self)  (void)(__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = 1, sig_cinit(&(self)->sl_rdwait), sig_cinit(&(self)->sl_wrwait))
#define shared_rwlock_cinit_write(self) (void)(__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = (uintptr_t)-1, sig_cinit(&(self)->sl_rdwait), sig_cinit(&(self)->sl_wrwait))
#define shared_rwlock_broadcast_for_fini(self)   \
	(sig_broadcast_for_fini(&(self)->sl_rdwait), \
	 sig_broadcast_for_fini(&(self)->sl_wrwait))

#define shared_rwlock_reading(self)  (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) != 0)
#define shared_rwlock_writing(self)  (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) == (uintptr_t)-1)
#define shared_rwlock_canread(self)  (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) != (uintptr_t)-1)
#define shared_rwlock_canwrite(self) (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) == 0)

LOCAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_tryread)(struct shared_rwlock *__restrict self);
LOCAL NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_trywrite)(struct shared_rwlock *__restrict self);
FUNDEF BLOCKING NOCONNECT NONNULL((1)) void FCALL shared_rwlock_read(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT NONNULL((1)) void FCALL shared_rwlock_write(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_read_nx)(struct shared_rwlock *__restrict self);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_write_nx)(struct shared_rwlock *__restrict self);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_read_with_timeout(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_write_with_timeout(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_read_with_timeout_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_write_with_timeout_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout);
FUNDEF BLOCKING NOCONNECT NONNULL((1)) void FCALL shared_rwlock_waitread(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT NONNULL((1)) void FCALL shared_rwlock_waitwrite(struct shared_rwlock *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_waitread_nx)(struct shared_rwlock *__restrict self);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_waitwrite_nx)(struct shared_rwlock *__restrict self);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_waitread_with_timeout(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_waitwrite_with_timeout(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_waitread_with_timeout_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout);
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_waitwrite_with_timeout_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout);
#ifdef __cplusplus
extern "C++" {
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_read(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK) ASMNAME("shared_rwlock_read_with_timeout");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_write(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK) ASMNAME("shared_rwlock_write_with_timeout");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_read_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout) ASMNAME("shared_rwlock_read_with_timeout_nx");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_write_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout) ASMNAME("shared_rwlock_write_with_timeout_nx");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_waitread(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK) ASMNAME("shared_rwlock_waitread_with_timeout");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL FCALL shared_rwlock_waitwrite(struct shared_rwlock *__restrict self, ktime_t abs_timeout) THROWS(E_WOULDBLOCK) ASMNAME("shared_rwlock_waitwrite_with_timeout");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_waitread_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout) ASMNAME("shared_rwlock_waitread_with_timeout_nx");
FUNDEF BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL shared_rwlock_waitwrite_nx)(struct shared_rwlock *__restrict self, ktime_t abs_timeout) ASMNAME("shared_rwlock_waitwrite_with_timeout_nx");
} /* extern "C++" */
#endif /* __cplusplus */

/* Try to upgrade a read-lock to a write-lock. Return `FALSE' upon failure. */
#define shared_rwlock_tryupgrade(self) \
	__hybrid_atomic_cmpxch((self)->sl_lock, 1, (uintptr_t)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)

/* NOTE: The lock is always upgraded, but when `FALSE' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources. */
LOCAL BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL
(FCALL shared_rwlock_upgrade)(struct shared_rwlock *__restrict self)
		THROWS(E_WOULDBLOCK);

/* NOTE: The lock is always upgraded for `return != 0', but when `2' is returned,
 *       no lock may have been held  temporarily, meaning that the caller  should
 *       re-load local copies of affected resources.
 * NOTE: When `0' is returned, the original read-lock created by the caller has
 *       already been released. */
LOCAL NOCONNECT NONNULL((1)) unsigned int
NOTHROW(FCALL shared_rwlock_upgrade_nx)(struct shared_rwlock *__restrict self);

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
	__hybrid_assertf(self->sl_lock == (uintptr_t)-1, "Lock isn't in write-mode (%x)", self->sl_lock);
	__hybrid_atomic_store(self->sl_lock, 0, __ATOMIC_RELEASE);
	if (!sig_send(&self->sl_wrwait))
		sig_broadcast(&self->sl_rdwait);
}

LOCAL NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL shared_rwlock_endread)(struct shared_rwlock *__restrict self) {
	uintptr_t __result;
	COMPILER_READ_BARRIER();
	__hybrid_assertf(self->sl_lock != (uintptr_t)-1, "Lock is in write-mode (%x)", self->sl_lock);
	__hybrid_assertf(self->sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(self->sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		sig_send(&self->sl_wrwait);
	return __result == 0;
}

LOCAL NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL shared_rwlock_end)(struct shared_rwlock *__restrict self) {
	COMPILER_BARRIER();
	if (self->sl_lock != (uintptr_t)-1) {
		/* Read-lock */
		uintptr_t __result;
		__hybrid_assertf(self->sl_lock != 0, "No remaining read-locks");
		__result = __hybrid_atomic_decfetch(self->sl_lock, __ATOMIC_RELEASE);
		if (__result == 0)
			sig_send(&self->sl_wrwait);
		return __result == 0;
	}
	/* Write-lock */
	__hybrid_atomic_store(self->sl_lock, 0, __ATOMIC_RELEASE);
	if (!sig_send(&self->sl_wrwait))
		sig_broadcast(&self->sl_rdwait);
	return true;
}

LOCAL NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL shared_rwlock_tryread)(struct shared_rwlock *__restrict self) {
	uintptr_t __temp;
	do {
		__temp = __hybrid_atomic_load(self->sl_lock, __ATOMIC_ACQUIRE);
		if (__temp == (uintptr_t)-1)
			return 0;
		__hybrid_assert(__temp != (uintptr_t)-2);
	} while (!__hybrid_atomic_cmpxch_weak(self->sl_lock, __temp, __temp + 1,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_RELAXED));
	COMPILER_READ_BARRIER();
	return 1;
}

LOCAL NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL shared_rwlock_trywrite)(struct shared_rwlock *__restrict self) {
	if (!__hybrid_atomic_cmpxch(self->sl_lock, 0, (uintptr_t)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED))
		return 0;
	COMPILER_BARRIER();
	return 1;
}

/* NOTE: The lock is always upgraded, but when `FALSE' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources. */
LOCAL BLOCKING NOCONNECT WUNUSED NONNULL((1)) __BOOL
(FCALL shared_rwlock_upgrade)(struct shared_rwlock *__restrict self)
		THROWS(E_WOULDBLOCK) {
	if (shared_rwlock_tryupgrade(self))
		return 1;
	shared_rwlock_endread(self);
	shared_rwlock_write(self);
	return 0;
}

/* NOTE: The lock is always upgraded for `return != 0', but when `2' is returned,
 *       no lock may have been held  temporarily, meaning that the caller  should
 *       re-load local copies of affected resources.
 * NOTE: When `0' is returned, the original read-lock created by the caller has
 *       already been released. */
LOCAL NOCONNECT NONNULL((1)) unsigned int
NOTHROW(FCALL shared_rwlock_upgrade_nx)(struct shared_rwlock *__restrict self) {
	if (shared_rwlock_tryupgrade(self))
		return 1;
	shared_rwlock_endread(self);
	if (!shared_rwlock_write_nx(self))
		return 0;
	return 2;
}

/* Downgrade a write-lock to a read-lock (Always succeeds). */
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL shared_rwlock_downgrade)(struct shared_rwlock *__restrict self) {
	COMPILER_WRITE_BARRIER();
	__hybrid_assertf(self->sl_lock == (uintptr_t)-1, "Lock isn't in write-mode (%x)", self->sl_lock);
	__hybrid_atomic_store(self->sl_lock, 1, __ATOMIC_RELEASE);
	sig_broadcast(&self->sl_rdwait); /* Allow for more readers. */
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
