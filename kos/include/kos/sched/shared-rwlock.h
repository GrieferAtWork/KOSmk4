/* HASH CRC-32:0x65f83d8f */
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
#include <sched/sig.h>
#else /* __KERNEL__ */
#include <bits/os/timespec.h>
#include <kos/asm/futex.h>
#include <kos/syscalls.h>
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
#define shared_rwlock_init(self)        (void)((self)->sl_lock = 0, (self)->sl_rdwait = 0, (self)->sl_wrwait = 0)
#define shared_rwlock_init_read(self)   (void)((self)->sl_lock = 1, (self)->sl_rdwait = 0, (self)->sl_wrwait = 0)
#define shared_rwlock_init_write(self)  (void)((self)->sl_lock = (__uintptr_t)-1, (self)->sl_rdwait = 0, (self)->sl_wrwait = 0)
#define shared_rwlock_cinit(self)       (__hybrid_assert((self)->sl_lock == 0), __hybrid_assert((self)->sl_rdwait == 0), __hybrid_assert((self)->sl_wrwait == 0))
#define shared_rwlock_cinit_read(self)  (__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = 1, __hybrid_assert((self)->sl_rdwait == 0), __hybrid_assert((self)->sl_wrwait == 0))
#define shared_rwlock_cinit_write(self) (__hybrid_assert((self)->sl_lock == 0), (self)->sl_lock = (__uintptr_t)-1, __hybrid_assert((self)->sl_rdwait == 0), __hybrid_assert((self)->sl_wrwait == 0))
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
	__hybrid_atomic_cmpxch((self)->sl_lock, 1, (__uintptr_t)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)

#ifdef __CRT_HAVE_shared_rwlock_tryread
/* >> shared_rwlock_tryread(3)
 * Try to acquire a read-lock to `self' */
__COMPILER_CEIDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_ACCESS_RW(1),__BOOL,__NOTHROW,__FCALL,shared_rwlock_tryread,(struct shared_rwlock *__restrict __self),{
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
__LOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_ACCESS_RW(1) __BOOL __NOTHROW(__FCALL shared_rwlock_tryread)(struct shared_rwlock *__restrict __self) {
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
__COMPILER_CEIDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_ACCESS_RW(1),__BOOL,__NOTHROW,__FCALL,shared_rwlock_trywrite,(struct shared_rwlock *__restrict __self),{
	if (!__hybrid_atomic_cmpxch(__self->sl_lock, 0, (__UINTPTR_TYPE__)-1,
	                            __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
		return 0;
	__COMPILER_BARRIER();
	return 1;
})
#else /* __CRT_HAVE_shared_rwlock_trywrite */
/* >> shared_rwlock_trywrite(3)
 * Try to acquire a write-lock to `self' */
__LOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_ACCESS_RW(1) __BOOL __NOTHROW(__FCALL shared_rwlock_trywrite)(struct shared_rwlock *__restrict __self) {
	if (!__hybrid_atomic_cmpxch(__self->sl_lock, 0, (__UINTPTR_TYPE__)-1,
	                            __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
		return 0;
	__COMPILER_BARRIER();
	return 1;
}
#endif /* !__CRT_HAVE_shared_rwlock_trywrite */
#if defined(__CRT_HAVE_shared_rwlock_endwrite) && defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_endwrite(3)
 * Release a write-lock from `self' */
__COMPILER_CEIDECLARE(__NOBLOCK __ATTR_ACCESS_RW(1),void,__NOTHROW,__FCALL,shared_rwlock_endwrite,(struct shared_rwlock *__restrict __self),{
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->sl_lock == (__UINTPTR_TYPE__)-1, "Lock isn't in write-mode (%x)", __self->sl_lock);
	__hybrid_atomic_store(__self->sl_lock, 0, __ATOMIC_RELEASE);
	if (!__shared_rwlock_wrwait_send(__self))
		__shared_rwlock_rdwait_broadcast(__self);
})
#elif defined(__CRT_HAVE_shared_rwlock_endwrite)
/* >> shared_rwlock_endwrite(3)
 * Release a write-lock from `self' */
__LIBC __NOBLOCK __ATTR_ACCESS_RW(1) void __NOTHROW(__FCALL shared_rwlock_endwrite)(struct shared_rwlock *__restrict __self) __CASMNAME_SAME("shared_rwlock_endwrite");
#elif defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_endwrite(3)
 * Release a write-lock from `self' */
__LOCAL __NOBLOCK __ATTR_ACCESS_RW(1) void __NOTHROW(__FCALL shared_rwlock_endwrite)(struct shared_rwlock *__restrict __self) {
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
__COMPILER_CEIDECLARE(__NOBLOCK __ATTR_ACCESS_RW(1),__BOOL,__NOTHROW,__FCALL,shared_rwlock_endread,(struct shared_rwlock *__restrict __self),{
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
__LIBC __NOBLOCK __ATTR_ACCESS_RW(1) __BOOL __NOTHROW(__FCALL shared_rwlock_endread)(struct shared_rwlock *__restrict __self) __CASMNAME_SAME("shared_rwlock_endread");
#elif defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_endread(3)
 * Release a read-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LOCAL __NOBLOCK __ATTR_ACCESS_RW(1) __BOOL __NOTHROW(__FCALL shared_rwlock_endread)(struct shared_rwlock *__restrict __self) {
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
__COMPILER_CEIDECLARE(__NOBLOCK __ATTR_ACCESS_RW(1),__BOOL,__NOTHROW,__FCALL,shared_rwlock_end,(struct shared_rwlock *__restrict __self),{
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
__LIBC __NOBLOCK __ATTR_ACCESS_RW(1) __BOOL __NOTHROW(__FCALL shared_rwlock_end)(struct shared_rwlock *__restrict __self) __CASMNAME_SAME("shared_rwlock_end");
#elif defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_end(3)
 * Release a read- or write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LOCAL __NOBLOCK __ATTR_ACCESS_RW(1) __BOOL __NOTHROW(__FCALL shared_rwlock_end)(struct shared_rwlock *__restrict __self) {
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
__COMPILER_CEIDECLARE(__NOBLOCK __ATTR_ACCESS_RW(1),void,__NOTHROW,__FCALL,shared_rwlock_downgrade,(struct shared_rwlock *__restrict __self),{
	__COMPILER_WRITE_BARRIER();
	__hybrid_assertf(__self->sl_lock == (__UINTPTR_TYPE__)-1, "Lock isn't in write-mode (%x)", __self->sl_lock);
	__hybrid_atomic_store(__self->sl_lock, 1, __ATOMIC_RELEASE);
	__shared_rwlock_rdwait_broadcast(__self); /* Allow for more readers. */
})
#elif defined(__CRT_HAVE_shared_rwlock_downgrade)
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
__LIBC __NOBLOCK __ATTR_ACCESS_RW(1) void __NOTHROW(__FCALL shared_rwlock_downgrade)(struct shared_rwlock *__restrict __self) __CASMNAME_SAME("shared_rwlock_downgrade");
#elif defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
__LOCAL __NOBLOCK __ATTR_ACCESS_RW(1) void __NOTHROW(__FCALL shared_rwlock_downgrade)(struct shared_rwlock *__restrict __self) {
	__COMPILER_WRITE_BARRIER();
	__hybrid_assertf(__self->sl_lock == (__UINTPTR_TYPE__)-1, "Lock isn't in write-mode (%x)", __self->sl_lock);
	__hybrid_atomic_store(__self->sl_lock, 1, __ATOMIC_RELEASE);
	__shared_rwlock_rdwait_broadcast(__self); /* Allow for more readers. */
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_upgrade) && (defined(__CRT_HAVE_shared_rwlock_endread) || defined(__shared_rwlock_wrwait_send)) && (defined(__CRT_HAVE_shared_rwlock_write) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_endread_defined
#define __local___localdep_shared_rwlock_endread_defined
#if defined(__CRT_HAVE_shared_rwlock_endread) && defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_endread(3)
 * Release a read-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_ACCESS_RW(1),__BOOL,__NOTHROW,__FCALL,__localdep_shared_rwlock_endread,(struct shared_rwlock *__restrict __self),shared_rwlock_endread,{
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
__COMPILER_CREDIRECT(__LIBC,__NOBLOCK __ATTR_ACCESS_RW(1),__BOOL,__NOTHROW,__FCALL,__localdep_shared_rwlock_endread,(struct shared_rwlock *__restrict __self),shared_rwlock_endread,(__self))
#elif defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_endread(3)
 * Release a read-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LOCAL __NOBLOCK __ATTR_ACCESS_RW(1) __BOOL __NOTHROW(__FCALL __localdep_shared_rwlock_endread)(struct shared_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __result;
	__COMPILER_READ_BARRIER();
	__hybrid_assertf(__self->sl_lock != (__UINTPTR_TYPE__)-1, "Lock is in write-mode (%x)", __self->sl_lock);
	__hybrid_assertf(__self->sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(__self->sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(__self);
	return __result == 0;
}
#else /* ... */
#undef __local___localdep_shared_rwlock_endread_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_endread_defined */
#ifndef __local___localdep_shared_rwlock_write_defined
#define __local___localdep_shared_rwlock_write_defined
#ifdef __CRT_HAVE_shared_rwlock_write
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_ACCESS_RW(1),__THROWING,__FCALL,__localdep_shared_rwlock_write,(struct shared_rwlock *__restrict __self),shared_rwlock_write,(__self))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
#define __localdep_shared_rwlock_write __LIBC_LOCAL_NAME(shared_rwlock_write)
#else /* ... */
#undef __local___localdep_shared_rwlock_write_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_write_defined */
__NAMESPACE_LOCAL_END
/* >> shared_rwlock_upgrade(3)
 * Blocking-upgrade a read-lock into a write-lock
 * NOTE: The lock is always upgraded, but when `false' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources.
 * @return: true:  Upgrade was performed without the read-lock being lost
 * @return: false: The read-lock had to be released before a write-lock was acquired */
__COMPILER_CEIDECLARE(__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_upgrade,(struct shared_rwlock *__restrict __self),{
	if (__hybrid_atomic_cmpxch(__self->sl_lock, 1, (__UINTPTR_TYPE__)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED))
		return 1; /* Lock wasn't lost */
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_endread)(__self);
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_write)(__self);
	return 0; /* Lock was (temporarily) lost */
})
#elif defined(__CRT_HAVE_shared_rwlock_upgrade)
/* >> shared_rwlock_upgrade(3)
 * Blocking-upgrade a read-lock into a write-lock
 * NOTE: The lock is always upgraded, but when `false' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources.
 * @return: true:  Upgrade was performed without the read-lock being lost
 * @return: false: The read-lock had to be released before a write-lock was acquired */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_upgrade)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_upgrade");
#elif (defined(__CRT_HAVE_shared_rwlock_endread) || defined(__shared_rwlock_wrwait_send)) && (defined(__CRT_HAVE_shared_rwlock_write) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_endread_defined
#define __local___localdep_shared_rwlock_endread_defined
#if defined(__CRT_HAVE_shared_rwlock_endread) && defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_endread(3)
 * Release a read-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_ACCESS_RW(1),__BOOL,__NOTHROW,__FCALL,__localdep_shared_rwlock_endread,(struct shared_rwlock *__restrict __self),shared_rwlock_endread,{
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
__COMPILER_CREDIRECT(__LIBC,__NOBLOCK __ATTR_ACCESS_RW(1),__BOOL,__NOTHROW,__FCALL,__localdep_shared_rwlock_endread,(struct shared_rwlock *__restrict __self),shared_rwlock_endread,(__self))
#elif defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_endread(3)
 * Release a read-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LOCAL __NOBLOCK __ATTR_ACCESS_RW(1) __BOOL __NOTHROW(__FCALL __localdep_shared_rwlock_endread)(struct shared_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __result;
	__COMPILER_READ_BARRIER();
	__hybrid_assertf(__self->sl_lock != (__UINTPTR_TYPE__)-1, "Lock is in write-mode (%x)", __self->sl_lock);
	__hybrid_assertf(__self->sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(__self->sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(__self);
	return __result == 0;
}
#else /* ... */
#undef __local___localdep_shared_rwlock_endread_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_endread_defined */
#ifndef __local___localdep_shared_rwlock_write_defined
#define __local___localdep_shared_rwlock_write_defined
#ifdef __CRT_HAVE_shared_rwlock_write
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_ACCESS_RW(1),__THROWING,__FCALL,__localdep_shared_rwlock_write,(struct shared_rwlock *__restrict __self),shared_rwlock_write,(__self))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
#define __localdep_shared_rwlock_write __LIBC_LOCAL_NAME(shared_rwlock_write)
#else /* ... */
#undef __local___localdep_shared_rwlock_write_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_write_defined */
__NAMESPACE_LOCAL_END
/* >> shared_rwlock_upgrade(3)
 * Blocking-upgrade a read-lock into a write-lock
 * NOTE: The lock is always upgraded, but when `false' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources.
 * @return: true:  Upgrade was performed without the read-lock being lost
 * @return: false: The read-lock had to be released before a write-lock was acquired */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_upgrade)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) {
	if (__hybrid_atomic_cmpxch(__self->sl_lock, 1, (__UINTPTR_TYPE__)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED))
		return 1; /* Lock wasn't lost */
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_endread)(__self);
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_write)(__self);
	return 0; /* Lock was (temporarily) lost */
}
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_read
/* >> shared_rwlock_read(3)
 * Acquire a read-lock to the given shared_rwlock. */
__LIBC __BLOCKING __ATTR_ACCESS_RW(1) void (__FCALL shared_rwlock_read)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_read");
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read.h>
/* >> shared_rwlock_read(3)
 * Acquire a read-lock to the given shared_rwlock. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_read, __FORCELOCAL __ATTR_ARTIFICIAL __BLOCKING __ATTR_ACCESS_RW(1) void (__FCALL shared_rwlock_read)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_read))(__self); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_write
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
__LIBC __BLOCKING __ATTR_ACCESS_RW(1) void (__FCALL shared_rwlock_write)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_write");
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write.h>
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_write, __FORCELOCAL __ATTR_ARTIFICIAL __BLOCKING __ATTR_ACCESS_RW(1) void (__FCALL shared_rwlock_write)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_write))(__self); })
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_read_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_read_with_timeout)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_read_with_timeout");
#elif defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_read_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout.h>
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_read_with_timeout, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_read_with_timeout)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout))(__self, __abs_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_write_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_write_with_timeout)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_write_with_timeout");
#elif defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_write_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout.h>
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_write_with_timeout, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_write_with_timeout)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout))(__self, __abs_timeout); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_waitread
/* >> shared_rwlock_waitread(3)
 * Wait until acquiring a read-lock to `self' no longer blocks */
__LIBC __BLOCKING __ATTR_ACCESS_RW(1) void (__FCALL shared_rwlock_waitread)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_waitread");
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread.h>
/* >> shared_rwlock_waitread(3)
 * Wait until acquiring a read-lock to `self' no longer blocks */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_waitread, __FORCELOCAL __ATTR_ARTIFICIAL __BLOCKING __ATTR_ACCESS_RW(1) void (__FCALL shared_rwlock_waitread)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitread))(__self); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_waitwrite
/* >> shared_rwlock_waitwrite(3)
 * Wait until acquiring a write-lock to `self' no longer blocks */
__LIBC __BLOCKING __ATTR_ACCESS_RW(1) void (__FCALL shared_rwlock_waitwrite)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_waitwrite");
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite.h>
/* >> shared_rwlock_waitwrite(3)
 * Wait until acquiring a write-lock to `self' no longer blocks */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_waitwrite, __FORCELOCAL __ATTR_ARTIFICIAL __BLOCKING __ATTR_ACCESS_RW(1) void (__FCALL shared_rwlock_waitwrite)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitwrite))(__self); })
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitread_with_timeout)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_waitread_with_timeout");
#elif defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitread_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout.h>
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_waitread_with_timeout, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitread_with_timeout)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout))(__self, __abs_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitwrite_with_timeout)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_waitwrite_with_timeout");
#elif defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitwrite_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout.h>
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_waitwrite_with_timeout, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitwrite_with_timeout)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout))(__self, __abs_timeout); })
#endif /* ... */
#if !defined(__KERNEL__) && defined(__USE_TIME64)
#if defined(__CRT_HAVE_shared_rwlock_read_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_read_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_read_with_timeout64)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_read_with_timeout64)(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_read_with_timeout64");
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout64.h>
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_read_with_timeout64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_read_with_timeout64)(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout64))(__self, __abs_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_write_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_write_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_write_with_timeout64)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_write_with_timeout64)(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_write_with_timeout64");
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout64.h>
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_write_with_timeout64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_write_with_timeout64)(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout64))(__self, __abs_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitread_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitread_with_timeout64)(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_waitread_with_timeout64");
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout64.h>
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_waitread_with_timeout64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitread_with_timeout64)(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout64))(__self, __abs_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitwrite_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitwrite_with_timeout64)(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_waitwrite_with_timeout64");
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout64.h>
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_waitwrite_with_timeout64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitwrite_with_timeout64)(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout64))(__self, __abs_timeout); })
#endif /* ... */
#endif /* !__KERNEL__ && __USE_TIME64 */
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
#ifdef __CRT_HAVE_shared_rwlock_read_nx
/* >> shared_rwlock_read_nx(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_read_nx)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_read_nx");
#elif defined(__KERNEL__)
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_nx.h>
/* >> shared_rwlock_read_nx(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_read_nx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_read_nx)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_read_nx))(__self); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_write_nx
/* >> shared_rwlock_write_nx(3)
 * Acquire a write-lock to the given shared_rwlock.
 * Acquire  a  lock   to  the  given   shared_lock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_write_nx)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_write_nx");
#elif defined(__KERNEL__)
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_nx.h>
/* >> shared_rwlock_write_nx(3)
 * Acquire a write-lock to the given shared_rwlock.
 * Acquire  a  lock   to  the  given   shared_lock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_write_nx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_write_nx)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_write_nx))(__self); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_read_with_timeout_nx
/* >> shared_rwlock_read_with_timeout_nx(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_read_with_timeout_nx)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_read_with_timeout_nx");
#elif defined(__KERNEL__)
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout_nx.h>
/* >> shared_rwlock_read_with_timeout_nx(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_read_with_timeout_nx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_read_with_timeout_nx)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout_nx))(__self, __abs_timeout); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_write_with_timeout_nx
/* >> shared_rwlock_write_with_timeout_nx(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_write_with_timeout_nx)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_write_with_timeout_nx");
#elif defined(__KERNEL__)
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout_nx.h>
/* >> shared_rwlock_write_with_timeout_nx(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_write_with_timeout_nx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_write_with_timeout_nx)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout_nx))(__self, __abs_timeout); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_waitread_nx
/* >> shared_rwlock_waitread_nx(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitread_nx)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_waitread_nx");
#elif defined(__KERNEL__)
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_nx.h>
/* >> shared_rwlock_waitread_nx(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_waitread_nx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitread_nx)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitread_nx))(__self); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_waitwrite_nx
/* >> shared_rwlock_waitwrite_nx(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * Acquire a lock to the given shared_lock.
 * @return: true:  A write-lock became available.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitwrite_nx)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_waitwrite_nx");
#elif defined(__KERNEL__)
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_nx.h>
/* >> shared_rwlock_waitwrite_nx(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * Acquire a lock to the given shared_lock.
 * @return: true:  A write-lock became available.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_waitwrite_nx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitwrite_nx)(struct shared_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_nx))(__self); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_waitread_with_timeout_nx
/* >> shared_rwlock_waitread_with_timeout_nx(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitread_with_timeout_nx)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_waitread_with_timeout_nx");
#elif defined(__KERNEL__)
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout_nx.h>
/* >> shared_rwlock_waitread_with_timeout_nx(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_waitread_with_timeout_nx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitread_with_timeout_nx)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout_nx))(__self, __abs_timeout); })
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_waitwrite_with_timeout_nx
/* >> shared_rwlock_waitwrite_with_timeout_nx(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitwrite_with_timeout_nx)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_rwlock_waitwrite_with_timeout_nx");
#elif defined(__KERNEL__)
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout_nx.h>
/* >> shared_rwlock_waitwrite_with_timeout_nx(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__NAMESPACE_LOCAL_USING_OR_IMPL(shared_rwlock_waitwrite_with_timeout_nx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitwrite_with_timeout_nx)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout_nx))(__self, __abs_timeout); })
#endif /* ... */
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */
#ifdef __cplusplus
extern "C++" {
#if defined(__CRT_HAVE_shared_rwlock_read_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_read,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_read,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
} /* extern "C++" */
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout.h>
extern "C++" {
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_read)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout))(__self, __abs_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_write_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_write,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_write,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
} /* extern "C++" */
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout.h>
extern "C++" {
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_write)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout))(__self, __abs_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitread,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitread,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
} /* extern "C++" */
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout.h>
extern "C++" {
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitread)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout))(__self, __abs_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitwrite,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitwrite,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
} /* extern "C++" */
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout.h>
extern "C++" {
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitwrite)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout))(__self, __abs_timeout); }
#endif /* ... */
} /* extern "C++" */
#if !defined(__KERNEL__) && defined(__USE_TIME64) && (!defined(__USE_STRUCT64_MACRO) || !defined(_TIMESPEC_MATCHES_TIMESPEC64))
extern "C++" {
#if defined(__CRT_HAVE_shared_rwlock_read_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_read,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_read_with_timeout64)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_read,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
} /* extern "C++" */
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout64.h>
extern "C++" {
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_read)(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout64))(__self, __abs_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_write_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_write,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_write_with_timeout64)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_write,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
} /* extern "C++" */
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout64.h>
extern "C++" {
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_write)(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout64))(__self, __abs_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitread,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitread,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
} /* extern "C++" */
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout64.h>
extern "C++" {
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitread)(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout64))(__self, __abs_timeout); }
#endif /* ... */
#if defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitwrite,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitwrite,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
} /* extern "C++" */
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout64.h>
extern "C++" {
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RO_OPT(2) __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitwrite)(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout64))(__self, __abs_timeout); }
#endif /* ... */
} /* extern "C++" */
#endif /* !__KERNEL__ && __USE_TIME64 && (!__USE_STRUCT64_MACRO || !_TIMESPEC_MATCHES_TIMESPEC64) */
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
extern "C++" {
#ifdef __CRT_HAVE_shared_rwlock_read_with_timeout_nx
/* >> shared_rwlock_read_with_timeout_nx(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_read_nx,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_read_with_timeout_nx,(__self,__abs_timeout))
#elif defined(__KERNEL__)
} /* extern "C++" */
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout_nx.h>
extern "C++" {
/* >> shared_rwlock_read_with_timeout_nx(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_read_nx)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout_nx))(__self, __abs_timeout); }
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_write_with_timeout_nx
/* >> shared_rwlock_write_with_timeout_nx(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_write_nx,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_write_with_timeout_nx,(__self,__abs_timeout))
#elif defined(__KERNEL__)
} /* extern "C++" */
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout_nx.h>
extern "C++" {
/* >> shared_rwlock_write_with_timeout_nx(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_write_nx)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout_nx))(__self, __abs_timeout); }
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_waitread_with_timeout_nx
/* >> shared_rwlock_waitread_with_timeout_nx(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitread_nx,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitread_with_timeout_nx,(__self,__abs_timeout))
#elif defined(__KERNEL__)
} /* extern "C++" */
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout_nx.h>
extern "C++" {
/* >> shared_rwlock_waitread_with_timeout_nx(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitread_nx)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout_nx))(__self, __abs_timeout); }
#endif /* ... */
#ifdef __CRT_HAVE_shared_rwlock_waitwrite_with_timeout_nx
/* >> shared_rwlock_waitwrite_with_timeout_nx(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1),__BOOL,__THROWING,__FCALL,shared_rwlock_waitwrite_nx,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitwrite_with_timeout_nx,(__self,__abs_timeout))
#elif defined(__KERNEL__)
} /* extern "C++" */
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout_nx.h>
extern "C++" {
/* >> shared_rwlock_waitwrite_with_timeout_nx(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __BLOCKING __ATTR_ACCESS_RW(1) __BOOL (__FCALL shared_rwlock_waitwrite_nx)(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout_nx))(__self, __abs_timeout); }
#endif /* ... */
} /* extern "C++" */
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
#define __PRIVATE_shared_rwlock_read_1      (shared_rwlock_read)
#define __PRIVATE_shared_rwlock_read_2      shared_rwlock_read_with_timeout
#define __PRIVATE_shared_rwlock_write_1     (shared_rwlock_write)
#define __PRIVATE_shared_rwlock_write_2     shared_rwlock_write_with_timeout
#define __PRIVATE_shared_rwlock_waitread_1  (shared_rwlock_waitread)
#define __PRIVATE_shared_rwlock_waitread_2  shared_rwlock_waitread_with_timeout
#define __PRIVATE_shared_rwlock_waitwrite_1 (shared_rwlock_waitwrite)
#define __PRIVATE_shared_rwlock_waitwrite_2 shared_rwlock_waitwrite_with_timeout
#define shared_rwlock_read(...)      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_read_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_write(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_write_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_waitread(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_waitread_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_waitwrite(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_waitwrite_, (__VA_ARGS__))(__VA_ARGS__)
#if !defined(__KERNEL__) && defined(__USE_TIME64)
#define __PRIVATE_shared_rwlock_read64_1      (shared_rwlock_read)
#define __PRIVATE_shared_rwlock_read64_2      shared_rwlock_read_with_timeout64
#define __PRIVATE_shared_rwlock_write64_1     (shared_rwlock_write)
#define __PRIVATE_shared_rwlock_write64_2     shared_rwlock_write_with_timeout64
#define __PRIVATE_shared_rwlock_waitread64_1  (shared_rwlock_waitread)
#define __PRIVATE_shared_rwlock_waitread64_2  shared_rwlock_waitread_with_timeout64
#define __PRIVATE_shared_rwlock_waitwrite64_1 (shared_rwlock_waitwrite)
#define __PRIVATE_shared_rwlock_waitwrite64_2 shared_rwlock_waitwrite_with_timeout64
#define shared_rwlock_read64(...)      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_read64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_write64(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_write64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_waitread64(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_waitread64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_waitwrite64(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_waitwrite64_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* !__KERNEL__ && __USE_TIME64 */
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
#define __PRIVATE_shared_rwlock_read_nx_1      (shared_rwlock_read_nx)
#define __PRIVATE_shared_rwlock_read_nx_2      shared_rwlock_read_with_timeout_nx
#define __PRIVATE_shared_rwlock_write_nx_1     (shared_rwlock_write_nx)
#define __PRIVATE_shared_rwlock_write_nx_2     shared_rwlock_write_with_timeout_nx
#define __PRIVATE_shared_rwlock_waitread_nx_1  (shared_rwlock_waitread_nx)
#define __PRIVATE_shared_rwlock_waitread_nx_2  shared_rwlock_waitread_with_timeout_nx
#define __PRIVATE_shared_rwlock_waitwrite_nx_1 (shared_rwlock_waitwrite_nx)
#define __PRIVATE_shared_rwlock_waitwrite_nx_2 shared_rwlock_waitwrite_with_timeout_nx
#define shared_rwlock_read_nx(...)      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_read_nx_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_write_nx(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_write_nx_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_waitread_nx(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_waitread_nx_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_rwlock_waitwrite_nx(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_rwlock_waitwrite_nx_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */
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
