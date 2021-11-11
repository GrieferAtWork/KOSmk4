/* HASH CRC-32:0xe16cb4c5 */
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
#ifndef _KOS_SCHED_SHARED_RWLOCK_H
#define _KOS_SCHED_SHARED_RWLOCK_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <kos/bits/shared-rwlock.h>
#include <bits/types.h>
#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <kos/anno.h>

#ifdef __KERNEL__
#include <kernel/types.h> /* ktime_t */
#include <sched/signal.h>
#else /* __KERNEL__ */
#include <kos/bits/futex.h>
#include <kos/syscalls.h>
#include <bits/os/timespec.h>
#endif /* !__KERNEL__ */

#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */

#ifdef __CC__
__SYSDECL_BEGIN

/* `shared_rwlock' is the  same as an `atomic_rwlock', with the
 * addition that a `shared_rwlock' includes a signal with which
 * one can do blocking waits for the lock to become available. */

#ifdef __KERNEL__
#define SHARED_RWLOCK_INIT              { 0, SIG_INIT, SIG_INIT }
#define SHARED_RWLOCK_INIT_READ         { 1, SIG_INIT, SIG_INIT }
#define SHARED_RWLOCK_INIT_WRITE        { (__uintptr_t)-1, SIG_INIT, SIG_INIT }
#define shared_rwlock_init(self)        ((self)->sl_lock = 0, sig_init(&(self)->sl_rdwait), sig_init(&(self)->sl_wrwait))
#define shared_rwlock_init_read(self)   (void)((self)->sl_lock = 1, sig_init(&(self)->sl_rdwait), sig_init(&(self)->sl_wrwait))
#define shared_rwlock_init_write(self)  (void)((self)->sl_lock = (__uintptr_t)-1, sig_init(&(self)->sl_rdwait), sig_init(&(self)->sl_wrwait))
#define shared_rwlock_cinit(self)       (__hybrid_assert((self)->sl_lock == 0), sig_cinit(&(self)->sl_rdwait), sig_cinit(&(self)->sl_wrwait))
#define shared_rwlock_cinit_read(self)  (void)(__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = 1, sig_cinit(&(self)->sl_rdwait), sig_cinit(&(self)->sl_wrwait))
#define shared_rwlock_cinit_write(self) (void)(__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = (__uintptr_t)-1, sig_cinit(&(self)->sl_rdwait), sig_cinit(&(self)->sl_wrwait))
#define shared_rwlock_broadcast_for_fini(self)   \
	(sig_broadcast_for_fini(&(self)->sl_rdwait), \
	 sig_broadcast_for_fini(&(self)->sl_wrwait))
#else /* __KERNEL__ */
#define SHARED_RWLOCK_INIT              { 0, 0, 0 }
#define SHARED_RWLOCK_INIT_READ         { 1, 0, 0 }
#define SHARED_RWLOCK_INIT_WRITE        { (__uintptr_t)-1, 0, 0 }
#define shared_rwlock_init(self)        ((self)->sl_lock = 0, (self)->sl_rdwait = 0, (self)->sl_wrwait = 0)
#define shared_rwlock_init_read(self)   (void)((self)->sl_lock = 1, (self)->sl_rdwait = 0, (self)->sl_wrwait = 0)
#define shared_rwlock_init_write(self)  (void)((self)->sl_lock = (__uintptr_t)-1, (self)->sl_rdwait = 0, (self)->sl_wrwait = 0)
#define shared_rwlock_cinit(self)       (__hybrid_assert((self)->sl_lock == 0), __hybrid_assert((self)->sl_rdwait == 0), __hybrid_assert((self)->sl_wrwait == 0))
#define shared_rwlock_cinit_read(self)  (void)(__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = 1, __hybrid_assert((self)->sl_rdwait == 0), __hybrid_assert((self)->sl_wrwait == 0))
#define shared_rwlock_cinit_write(self) (void)(__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = (__uintptr_t)-1, __hybrid_assert((self)->sl_rdwait == 0), __hybrid_assert((self)->sl_wrwait == 0))
/* NOTE: we use `sys_Xlfutex()', because the only possible exception is E_SEGFAULT */
#define shared_rwlock_broadcast_for_fini(self)                                                                        \
	((self)->sl_rdwait ? (void)sys_Xlfutex(&(self)->sl_rdwait, LFUTEX_WAKE, (__uintptr_t)-1, __NULLPTR, 0) : (void)0, \
	 (self)->sl_rdwait ? (void)sys_Xlfutex(&(self)->sl_wrwait, LFUTEX_WAKE, (__uintptr_t)-1, __NULLPTR, 0) : (void)0)
#endif /* !__KERNEL__ */

/* Check if reading/writing is possible, or a read/write lock is being held. */
#define shared_rwlock_reading(self)  (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) != 0)
#define shared_rwlock_writing(self)  (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) == (__uintptr_t)-1)
#define shared_rwlock_canread(self)  (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) != (__uintptr_t)-1)
#define shared_rwlock_canwrite(self) (__hybrid_atomic_load((self)->sl_lock, __ATOMIC_ACQUIRE) == 0)

/* >> shared_rwlock_tryupgrade(3)
 * Try to upgrade a read-lock to a write-lock. Return `false' upon failure. */
#define shared_rwlock_tryupgrade(self) \
	__hybrid_atomic_cmpxch((self)->sl_lock, 1, (uintptr_t)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)

#ifdef __CRT_HAVE_shared_rwlock_tryread
/* >> shared_rwlock_tryread(3)
 * Try to acquire a read-lock to `self' */
__COMPILER_EIDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,shared_rwlock_tryread,(struct shared_rwlock *__restrict __self),{
	__UINTPTR_TYPE__ __temp;
	do {
		__temp = __hybrid_atomic_load(__self->sl_lock, __ATOMIC_ACQUIRE);
		if (__temp == (__UINTPTR_TYPE__)-1)
			return 0;
		__hybrid_assert(__temp != (__UINTPTR_TYPE__)-2);
	} while (!__hybrid_atomic_cmpxch_weak(__self->sl_lock, __temp, __temp + 1,
	                                      __ATOMIC_ACQUIRE, __ATOMIC_RELAXED));
	__COMPILER_READ_BARRIER();
	return 1;
})
#else /* __CRT_HAVE_shared_rwlock_tryread */
/* >> shared_rwlock_tryread(3)
 * Try to acquire a read-lock to `self' */
__LOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL shared_rwlock_tryread)(struct shared_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __temp;
	do {
		__temp = __hybrid_atomic_load(__self->sl_lock, __ATOMIC_ACQUIRE);
		if (__temp == (__UINTPTR_TYPE__)-1)
			return 0;
		__hybrid_assert(__temp != (__UINTPTR_TYPE__)-2);
	} while (!__hybrid_atomic_cmpxch_weak(__self->sl_lock, __temp, __temp + 1,
	                                      __ATOMIC_ACQUIRE, __ATOMIC_RELAXED));
	__COMPILER_READ_BARRIER();
	return 1;
}
#endif /* !__CRT_HAVE_shared_rwlock_tryread */
#ifdef __CRT_HAVE_shared_rwlock_trywrite
/* >> shared_rwlock_trywrite(3)
 * Try to acquire a write-lock to `self' */
__COMPILER_EIDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,shared_rwlock_trywrite,(struct shared_rwlock *__restrict __self),{
	if (!__hybrid_atomic_cmpxch(__self->sl_lock, 0, (__UINTPTR_TYPE__)-1,
	                            __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
		return 0;
	__COMPILER_BARRIER();
	return 1;
})
#else /* __CRT_HAVE_shared_rwlock_trywrite */
/* >> shared_rwlock_trywrite(3)
 * Try to acquire a write-lock to `self' */
__LOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL shared_rwlock_trywrite)(struct shared_rwlock *__restrict __self) {
	if (!__hybrid_atomic_cmpxch(__self->sl_lock, 0, (__UINTPTR_TYPE__)-1,
	                            __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
		return 0;
	__COMPILER_BARRIER();
	return 1;
}
#endif /* !__CRT_HAVE_shared_rwlock_trywrite */
#if defined(__CRT_HAVE_shared_rwlock_endwrite) && defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_endwrite(3)
 * Release a a write-lock from `self' */
__COMPILER_EIDECLARE(__NOBLOCK __ATTR_NONNULL((1)),void,__NOTHROW,__FCALL,shared_rwlock_endwrite,(struct shared_rwlock *__restrict __self),{
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->sl_lock == (__UINTPTR_TYPE__)-1, "Lock isn't in write-mode (%x)", __self->sl_lock);
	__hybrid_atomic_store(__self->sl_lock, 0, __ATOMIC_RELEASE);
	if (!__shared_rwlock_wrwait_send(__self))
		__shared_rwlock_rdwait_broadcast(__self);
})
#elif defined(__CRT_HAVE_shared_rwlock_endwrite)
/* >> shared_rwlock_endwrite(3)
 * Release a a write-lock from `self' */
__LIBC __NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(__FCALL shared_rwlock_endwrite)(struct shared_rwlock *__restrict __self) __CASMNAME_SAME("shared_rwlock_endwrite");
#elif defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_endwrite(3)
 * Release a a write-lock from `self' */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(__FCALL shared_rwlock_endwrite)(struct shared_rwlock *__restrict __self) {
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->sl_lock == (__UINTPTR_TYPE__)-1, "Lock isn't in write-mode (%x)", __self->sl_lock);
	__hybrid_atomic_store(__self->sl_lock, 0, __ATOMIC_RELEASE);
	if (!__shared_rwlock_wrwait_send(__self))
		__shared_rwlock_rdwait_broadcast(__self);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_endread) && defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_endread(3)
 * Release a read-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__COMPILER_EIDECLARE(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,shared_rwlock_endread,(struct shared_rwlock *__restrict __self),{
	__UINTPTR_TYPE__ __result;
	__COMPILER_READ_BARRIER();
	__hybrid_assertf(__self->sl_lock != (__UINTPTR_TYPE__)-1, "Lock is in write-mode (%x)", __self->sl_lock);
	__hybrid_assertf(__self->sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(__self->sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(__self);
	return __result == 0;
})
#elif defined(__CRT_HAVE_shared_rwlock_endread)
/* >> shared_rwlock_endread(3)
 * Release a read-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LIBC __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL shared_rwlock_endread)(struct shared_rwlock *__restrict __self) __CASMNAME_SAME("shared_rwlock_endread");
#elif defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_endread(3)
 * Release a read-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL shared_rwlock_endread)(struct shared_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __result;
	__COMPILER_READ_BARRIER();
	__hybrid_assertf(__self->sl_lock != (__UINTPTR_TYPE__)-1, "Lock is in write-mode (%x)", __self->sl_lock);
	__hybrid_assertf(__self->sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(__self->sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(__self);
	return __result == 0;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_end) && defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_end(3)
 * Release a read- or write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__COMPILER_EIDECLARE(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,shared_rwlock_end,(struct shared_rwlock *__restrict __self),{
	__COMPILER_BARRIER();
	if (__self->sl_lock != (__UINTPTR_TYPE__)-1) {
		/* Read-lock */
		__UINTPTR_TYPE__ __result;
		__hybrid_assertf(__self->sl_lock != 0, "No remaining read-locks");
		__result = __hybrid_atomic_decfetch(__self->sl_lock, __ATOMIC_RELEASE);
		if (__result == 0)
			__shared_rwlock_wrwait_send(__self);
		return __result == 0;
	}
	/* Write-lock */
	__hybrid_atomic_store(__self->sl_lock, 0, __ATOMIC_RELEASE);
	if (!__shared_rwlock_wrwait_send(__self))
		__shared_rwlock_rdwait_broadcast(__self);
	return 1;
})
#elif defined(__CRT_HAVE_shared_rwlock_end)
/* >> shared_rwlock_end(3)
 * Release a read- or write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LIBC __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL shared_rwlock_end)(struct shared_rwlock *__restrict __self) __CASMNAME_SAME("shared_rwlock_end");
#elif defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_end(3)
 * Release a read- or write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL shared_rwlock_end)(struct shared_rwlock *__restrict __self) {
	__COMPILER_BARRIER();
	if (__self->sl_lock != (__UINTPTR_TYPE__)-1) {
		/* Read-lock */
		__UINTPTR_TYPE__ __result;
		__hybrid_assertf(__self->sl_lock != 0, "No remaining read-locks");
		__result = __hybrid_atomic_decfetch(__self->sl_lock, __ATOMIC_RELEASE);
		if (__result == 0)
			__shared_rwlock_wrwait_send(__self);
		return __result == 0;
	}
	/* Write-lock */
	__hybrid_atomic_store(__self->sl_lock, 0, __ATOMIC_RELEASE);
	if (!__shared_rwlock_wrwait_send(__self))
		__shared_rwlock_rdwait_broadcast(__self);
	return 1;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_downgrade) && defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
__COMPILER_EIDECLARE(__NOBLOCK __ATTR_NONNULL((1)),void,__NOTHROW,__FCALL,shared_rwlock_downgrade,(struct shared_rwlock *__restrict __self),{
	__COMPILER_WRITE_BARRIER();
	__hybrid_assertf(__self->sl_lock == (__UINTPTR_TYPE__)-1, "Lock isn't in write-mode (%x)", __self->sl_lock);
	__hybrid_atomic_store(__self->sl_lock, 1, __ATOMIC_RELEASE);
	__shared_rwlock_rdwait_broadcast(__self); /* Allow for more readers. */
})
#elif defined(__CRT_HAVE_shared_rwlock_downgrade)
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
__LIBC __NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(__FCALL shared_rwlock_downgrade)(struct shared_rwlock *__restrict __self) __CASMNAME_SAME("shared_rwlock_downgrade");
#elif defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(__FCALL shared_rwlock_downgrade)(struct shared_rwlock *__restrict __self) {
	__COMPILER_WRITE_BARRIER();
	__hybrid_assertf(__self->sl_lock == (__UINTPTR_TYPE__)-1, "Lock isn't in write-mode (%x)", __self->sl_lock);
	__hybrid_atomic_store(__self->sl_lock, 1, __ATOMIC_RELEASE);
	__shared_rwlock_rdwait_broadcast(__self); /* Allow for more readers. */
}
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_read
/* >> shared_rwlock_read(3)
 * Acquire a read-lock to the given shared_rwlock. */
__LIBC __BLOCKING __ATTR_NONNULL((1)) void (__FCALL shared_rwlock_read)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_read");
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read.h>
/* >> shared_rwlock_read(3)
 * Acquire a read-lock to the given shared_rwlock. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_read, __FORCELOCAL __ATTR_ARTIFICIAL __BLOCKING __ATTR_NONNULL((1)) void (__FCALL shared_rwlock_read)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_read))(__self); })
#endif /* ... */

#ifdef __KERNEL__
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
#endif /* __KERNEL__ */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_SCHED_SHARED_RWLOCK_H */
