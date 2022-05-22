/* HASH CRC-32:0xc31cb6fc */
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
#ifndef _KOS_SCHED_SHARED_RECURSIVE_LOCK_H
#define _KOS_SCHED_SHARED_RECURSIVE_LOCK_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <kos/bits/shared-lock.h>
#include <kos/bits/shared-recursive-lock.h>
#include <kos/sched/shared-lock.h>
#include <bits/types.h>
#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <bits/os/timespec.h>
#include <kos/asm/futex.h>
#include <kos/anno.h>

#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */

#ifdef __CC__
__SYSDECL_BEGIN

/*
 * `shared_recursive_lock' just like `shared_lock', but remembers
 * the thread that acquired the lock, thus allowing for recursion
 *
 * NOTE: This interface is not available in kernel-space. For the
 *       rationale, see  `<kos/sched/shared-recursive-rwlock.h>'.
 */

#define SHARED_RECURSIVE_LOCK_INIT        { SHARED_LOCK_INIT, __SHARED_RECURSIVE_LOCK_BADTID, 0 }
#define shared_recursive_lock_init(self)  (void)(shared_lock_init(&(self)->sr_lock), (self)->sr_owner = __SHARED_RECURSIVE_LOCK_BADTID, (self)->sr_rcnt = 0)
#ifdef __SHARED_RECURSIVE_LOCK_BADTID_ISZERO
#define shared_recursive_lock_cinit(self) (shared_lock_cinit(&(self)->sr_lock), __hybrid_assert((self)->sr_owner == __SHARED_RECURSIVE_LOCK_BADTID), __hybrid_assert((self)->sr_rcnt == 0))
#else /* __SHARED_RECURSIVE_LOCK_BADTID_ISZERO */
#define shared_recursive_lock_cinit(self) (shared_lock_cinit(&(self)->sr_lock), (self)->sr_owner = __SHARED_RECURSIVE_LOCK_BADTID, __hybrid_assert((self)->sr_rcnt == 0))
#endif /* !__SHARED_RECURSIVE_LOCK_BADTID_ISZERO */
#ifdef shared_lock_broadcast_for_fini
#define shared_recursive_lock_broadcast_for_fini(self) \
	shared_lock_broadcast_for_fini(&(self)->sr_lock)
#endif /* shared_lock_broadcast_for_fini */

/* Check if locking is possible, or a lock is being held. */
#define shared_recursive_lock_available(self) (shared_lock_available(&(self)->sr_lock) || __shared_recursive_lock_isown(self))
#define shared_recursive_lock_acquired(self)  __shared_recursive_lock_isown(self)
/* #define shared_recursive_lock_acquired(self) (shared_lock_acquired(&(self)->sr_lock) && __shared_recursive_lock_isown(self)) */

#ifdef __CRT_HAVE_shared_recursive_lock_tryacquire
/* >> shared_recursive_lock_tryacquire(3)
 * Try to acquire a recursive lock to `self' */
__COMPILER_CEIDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT(1),__BOOL,__NOTHROW,__FCALL,shared_recursive_lock_tryacquire,(struct shared_recursive_lock *__restrict __self),{
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__hybrid_atomic_xch(__self->sr_lock.sl_lock, 1, __ATOMIC_ACQUIRE) == 0) {
		__shared_recursive_lock_setown(__self);
		return 1;
	}
	if (__shared_recursive_lock_isown(__self)) {
		++__self->sr_rcnt;
		return 1;
	}
	return 0;
})
#else /* __CRT_HAVE_shared_recursive_lock_tryacquire */
/* >> shared_recursive_lock_tryacquire(3)
 * Try to acquire a recursive lock to `self' */
__LOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT(1) __BOOL __NOTHROW(__FCALL shared_recursive_lock_tryacquire)(struct shared_recursive_lock *__restrict __self) {
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__hybrid_atomic_xch(__self->sr_lock.sl_lock, 1, __ATOMIC_ACQUIRE) == 0) {
		__shared_recursive_lock_setown(__self);
		return 1;
	}
	if (__shared_recursive_lock_isown(__self)) {
		++__self->sr_rcnt;
		return 1;
	}
	return 0;
}
#endif /* !__CRT_HAVE_shared_recursive_lock_tryacquire */
#if defined(__CRT_HAVE_shared_recursive_lock_release) && defined(__shared_lock_send)
/* >> shared_recursive_lock_release(3)
 * Release a recursive lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__COMPILER_CEIDECLARE(__NOBLOCK __ATTR_INOUT(1),__BOOL,__NOTHROW,__FCALL,shared_recursive_lock_release,(struct shared_recursive_lock *__restrict __self),{
	__COMPILER_WORKAROUND_GCC_105689(__self);
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->sr_lock.sl_lock != 0, "Lock isn't acquired");
	__hybrid_assertf(__shared_recursive_lock_isown(__self), "You're not the owner of this lock");
	if (__self->sr_rcnt == 0) {
		__self->sr_owner = __SHARED_RECURSIVE_LOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->sr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		__shared_lock_send(&__self->sr_lock);
		return 1;
	}
	--__self->sr_rcnt;
	return 0;
})
#elif defined(__CRT_HAVE_shared_recursive_lock_release)
/* >> shared_recursive_lock_release(3)
 * Release a recursive lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__LIBC __NOBLOCK __ATTR_INOUT(1) __BOOL __NOTHROW(__FCALL shared_recursive_lock_release)(struct shared_recursive_lock *__restrict __self) __CASMNAME_SAME("shared_recursive_lock_release");
#elif defined(__shared_lock_send)
/* >> shared_recursive_lock_release(3)
 * Release a recursive lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__LOCAL __NOBLOCK __ATTR_INOUT(1) __BOOL __NOTHROW(__FCALL shared_recursive_lock_release)(struct shared_recursive_lock *__restrict __self) {
	__COMPILER_WORKAROUND_GCC_105689(__self);
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->sr_lock.sl_lock != 0, "Lock isn't acquired");
	__hybrid_assertf(__shared_recursive_lock_isown(__self), "You're not the owner of this lock");
	if (__self->sr_rcnt == 0) {
		__self->sr_owner = __SHARED_RECURSIVE_LOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->sr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		__shared_lock_send(&__self->sr_lock);
		return 1;
	}
	--__self->sr_rcnt;
	return 0;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_lock_acquire) && (defined(__CRT_HAVE_shared_lock_acquire) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_acquire_defined
#define __local___localdep_shared_lock_acquire_defined
#ifdef __CRT_HAVE_shared_lock_acquire
/* >> shared_lock_acquire(3)
 * Acquire a lock to the given shared_lock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_INOUT(1),__THROWING,__FCALL,__localdep_shared_lock_acquire,(struct shared_lock *__restrict __self),shared_lock_acquire,(__self))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_acquire(3)
 * Acquire a lock to the given shared_lock. */
#define __localdep_shared_lock_acquire __LIBC_LOCAL_NAME(shared_lock_acquire)
#else /* ... */
#undef __local___localdep_shared_lock_acquire_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_acquire_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_lock_acquire(3)
 * Acquire a recursive lock to the given shared_recursive_lock. */
__COMPILER_CEIDECLARE(__BLOCKING __ATTR_INOUT(1),void,__THROWING,__FCALL,shared_recursive_lock_acquire,(struct shared_recursive_lock *__restrict __self),{
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self)) {
		++__self->sr_rcnt;
		return;
	}
	(__NAMESPACE_LOCAL_SYM __localdep_shared_lock_acquire)(&__self->sr_lock);
	__shared_recursive_lock_setown(__self);
})
#elif defined(__CRT_HAVE_shared_recursive_lock_acquire)
/* >> shared_recursive_lock_acquire(3)
 * Acquire a recursive lock to the given shared_recursive_lock. */
__LIBC __BLOCKING __ATTR_INOUT(1) void (__FCALL shared_recursive_lock_acquire)(struct shared_recursive_lock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_lock_acquire");
#elif defined(__CRT_HAVE_shared_lock_acquire) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_acquire_defined
#define __local___localdep_shared_lock_acquire_defined
#ifdef __CRT_HAVE_shared_lock_acquire
/* >> shared_lock_acquire(3)
 * Acquire a lock to the given shared_lock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_INOUT(1),__THROWING,__FCALL,__localdep_shared_lock_acquire,(struct shared_lock *__restrict __self),shared_lock_acquire,(__self))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_acquire(3)
 * Acquire a lock to the given shared_lock. */
#define __localdep_shared_lock_acquire __LIBC_LOCAL_NAME(shared_lock_acquire)
#else /* ... */
#undef __local___localdep_shared_lock_acquire_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_acquire_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_lock_acquire(3)
 * Acquire a recursive lock to the given shared_recursive_lock. */
__LOCAL __BLOCKING __ATTR_INOUT(1) void (__FCALL shared_recursive_lock_acquire)(struct shared_recursive_lock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self)) {
		++__self->sr_rcnt;
		return;
	}
	(__NAMESPACE_LOCAL_SYM __localdep_shared_lock_acquire)(&__self->sr_lock);
	__shared_recursive_lock_setown(__self);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_lock_acquire_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && (defined(__CRT_HAVE_shared_lock_acquire_with_timeout) || (defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_acquire_with_timeout_defined
#define __local___localdep_shared_lock_acquire_with_timeout_defined
#ifdef __CRT_HAVE_shared_lock_acquire_with_timeout
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_acquire_with_timeout __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout)
#else /* ... */
#undef __local___localdep_shared_lock_acquire_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_acquire_with_timeout_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIDECLARE(__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,shared_recursive_lock_acquire_with_timeout,(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout),{
	__BOOL __result;
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self)) {
		++__self->sr_rcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_acquire_with_timeout)(&__self->sr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_lock_setown(__self);
	return __result;
})
#elif defined(__CRT_HAVE_shared_recursive_lock_acquire_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_recursive_lock_acquire_with_timeout)(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_lock_acquire_with_timeout");
#elif defined(__CRT_HAVE_shared_recursive_lock_acquire_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,shared_recursive_lock_acquire_with_timeout,(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_recursive_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_lock_acquire_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_acquire_with_timeout_defined
#define __local___localdep_shared_lock_acquire_with_timeout_defined
#if defined(__CRT_HAVE_shared_lock_acquire_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_acquire_with_timeout __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout)
#else /* ... */
#undef __local___localdep_shared_lock_acquire_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_acquire_with_timeout_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_recursive_lock_acquire_with_timeout)(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	__BOOL __result;
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self)) {
		++__self->sr_rcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_acquire_with_timeout)(&__self->sr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_lock_setown(__self);
	return __result;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_lock_waitfor) && (defined(__CRT_HAVE_shared_lock_waitfor) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_waitfor_defined
#define __local___localdep_shared_lock_waitfor_defined
#ifdef __CRT_HAVE_shared_lock_waitfor
/* >> shared_lock_waitfor(3)
 * Wait for `self' to become available. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_INOUT(1),__THROWING,__FCALL,__localdep_shared_lock_waitfor,(struct shared_lock *__restrict __self),shared_lock_waitfor,(__self))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_waitfor(3)
 * Wait for `self' to become available. */
#define __localdep_shared_lock_waitfor __LIBC_LOCAL_NAME(shared_lock_waitfor)
#else /* ... */
#undef __local___localdep_shared_lock_waitfor_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_waitfor_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_lock_waitfor(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks */
__COMPILER_CEIDECLARE(__BLOCKING __ATTR_INOUT(1),void,__THROWING,__FCALL,shared_recursive_lock_waitfor,(struct shared_recursive_lock *__restrict __self),{
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self))
		return;
	(__NAMESPACE_LOCAL_SYM __localdep_shared_lock_waitfor)(&__self->sr_lock);
})
#elif defined(__CRT_HAVE_shared_recursive_lock_waitfor)
/* >> shared_recursive_lock_waitfor(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks */
__LIBC __BLOCKING __ATTR_INOUT(1) void (__FCALL shared_recursive_lock_waitfor)(struct shared_recursive_lock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_lock_waitfor");
#elif defined(__CRT_HAVE_shared_lock_waitfor) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_waitfor_defined
#define __local___localdep_shared_lock_waitfor_defined
#ifdef __CRT_HAVE_shared_lock_waitfor
/* >> shared_lock_waitfor(3)
 * Wait for `self' to become available. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_INOUT(1),__THROWING,__FCALL,__localdep_shared_lock_waitfor,(struct shared_lock *__restrict __self),shared_lock_waitfor,(__self))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_waitfor(3)
 * Wait for `self' to become available. */
#define __localdep_shared_lock_waitfor __LIBC_LOCAL_NAME(shared_lock_waitfor)
#else /* ... */
#undef __local___localdep_shared_lock_waitfor_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_waitfor_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_lock_waitfor(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks */
__LOCAL __BLOCKING __ATTR_INOUT(1) void (__FCALL shared_recursive_lock_waitfor)(struct shared_recursive_lock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self))
		return;
	(__NAMESPACE_LOCAL_SYM __localdep_shared_lock_waitfor)(&__self->sr_lock);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_lock_waitfor_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && (defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) || (defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_waitfor_with_timeout_defined
#define __local___localdep_shared_lock_waitfor_with_timeout_defined
#ifdef __CRT_HAVE_shared_lock_waitfor_with_timeout
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_waitfor_with_timeout __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout)
#else /* ... */
#undef __local___localdep_shared_lock_waitfor_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_waitfor_with_timeout_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIDECLARE(__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,shared_recursive_lock_waitfor_with_timeout,(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout),{
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_waitfor_with_timeout)(&__self->sr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_lock_waitfor_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_recursive_lock_waitfor_with_timeout)(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_lock_waitfor_with_timeout");
#elif defined(__CRT_HAVE_shared_recursive_lock_waitfor_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,shared_recursive_lock_waitfor_with_timeout,(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_recursive_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_waitfor_with_timeout_defined
#define __local___localdep_shared_lock_waitfor_with_timeout_defined
#if defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_waitfor_with_timeout __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout)
#else /* ... */
#undef __local___localdep_shared_lock_waitfor_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_waitfor_with_timeout_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_recursive_lock_waitfor_with_timeout)(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_waitfor_with_timeout)(&__self->sr_lock, __abs_timeout);
}
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_shared_recursive_lock_acquire_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__CRT_HAVE_shared_lock_acquire_with_timeout) || defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_acquire_with_timeout64_defined
#define __local___localdep_shared_lock_acquire_with_timeout64_defined
#ifdef __CRT_HAVE_shared_lock_acquire_with_timeout
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_acquire_with_timeout64)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_acquire_with_timeout64 __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_lock_acquire_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_acquire_with_timeout64_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,shared_recursive_lock_acquire_with_timeout64,(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_lock_acquire_with_timeout,{
	__BOOL __result;
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self)) {
		++__self->sr_rcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_acquire_with_timeout64)(&__self->sr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_lock_setown(__self);
	return __result;
})
#elif defined(__CRT_HAVE_shared_recursive_lock_acquire_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,shared_recursive_lock_acquire_with_timeout64,(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_lock_acquire_with_timeout64)
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2) __BOOL (__FCALL shared_recursive_lock_acquire_with_timeout64)(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_lock_acquire_with_timeout64");
#elif (defined(__CRT_HAVE_shared_lock_acquire_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_acquire_with_timeout64_defined
#define __local___localdep_shared_lock_acquire_with_timeout64_defined
#if defined(__CRT_HAVE_shared_lock_acquire_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_acquire_with_timeout64)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_acquire_with_timeout64 __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_lock_acquire_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_acquire_with_timeout64_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2) __BOOL (__FCALL shared_recursive_lock_acquire_with_timeout64)(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	__BOOL __result;
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self)) {
		++__self->sr_rcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_acquire_with_timeout64)(&__self->sr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_lock_setown(__self);
	return __result;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_lock_waitfor_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) || defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_waitfor_with_timeout64_defined
#define __local___localdep_shared_lock_waitfor_with_timeout64_defined
#ifdef __CRT_HAVE_shared_lock_waitfor_with_timeout
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_waitfor_with_timeout64 __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_lock_waitfor_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_waitfor_with_timeout64_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,shared_recursive_lock_waitfor_with_timeout64,(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_lock_waitfor_with_timeout,{
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_waitfor_with_timeout64)(&__self->sr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_lock_waitfor_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,shared_recursive_lock_waitfor_with_timeout64,(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_lock_waitfor_with_timeout64)
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2) __BOOL (__FCALL shared_recursive_lock_waitfor_with_timeout64)(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_lock_waitfor_with_timeout64");
#elif (defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_waitfor_with_timeout64_defined
#define __local___localdep_shared_lock_waitfor_with_timeout64_defined
#if defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_waitfor_with_timeout64 __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_lock_waitfor_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_waitfor_with_timeout64_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2) __BOOL (__FCALL shared_recursive_lock_waitfor_with_timeout64)(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_waitfor_with_timeout64)(&__self->sr_lock, __abs_timeout);
}
#endif /* ... */
#endif /* !__USE_TIME64 */
#ifdef __cplusplus
extern "C++" {
#if defined(__CRT_HAVE_shared_recursive_lock_acquire_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && (defined(__CRT_HAVE_shared_lock_acquire_with_timeout) || (defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64))))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_acquire_with_timeout_defined
#define __local___localdep_shared_lock_acquire_with_timeout_defined
#ifdef __CRT_HAVE_shared_lock_acquire_with_timeout
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_acquire_with_timeout __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout)
#else /* ... */
#undef __local___localdep_shared_lock_acquire_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_acquire_with_timeout_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,shared_recursive_lock_acquire,(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_recursive_lock_acquire_with_timeout,{
	__BOOL __result;
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self)) {
		++__self->sr_rcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_acquire_with_timeout)(&__self->sr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_lock_setown(__self);
	return __result;
})
#elif defined(__CRT_HAVE_shared_recursive_lock_acquire_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,shared_recursive_lock_acquire,(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_recursive_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_lock_acquire_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,shared_recursive_lock_acquire,(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_recursive_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_lock_acquire_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_acquire_with_timeout_defined
#define __local___localdep_shared_lock_acquire_with_timeout_defined
#if defined(__CRT_HAVE_shared_lock_acquire_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_acquire_with_timeout __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout)
#else /* ... */
#undef __local___localdep_shared_lock_acquire_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_acquire_with_timeout_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_recursive_lock_acquire)(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	__BOOL __result;
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self)) {
		++__self->sr_rcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_acquire_with_timeout)(&__self->sr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_lock_setown(__self);
	return __result;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_lock_waitfor_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && (defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) || (defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64))))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_waitfor_with_timeout_defined
#define __local___localdep_shared_lock_waitfor_with_timeout_defined
#ifdef __CRT_HAVE_shared_lock_waitfor_with_timeout
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_waitfor_with_timeout __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout)
#else /* ... */
#undef __local___localdep_shared_lock_waitfor_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_waitfor_with_timeout_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,shared_recursive_lock_waitfor,(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_recursive_lock_waitfor_with_timeout,{
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_waitfor_with_timeout)(&__self->sr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_lock_waitfor_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,shared_recursive_lock_waitfor,(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_recursive_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_lock_waitfor_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,shared_recursive_lock_waitfor,(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_recursive_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_waitfor_with_timeout_defined
#define __local___localdep_shared_lock_waitfor_with_timeout_defined
#if defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout,(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout),shared_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_waitfor_with_timeout __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout)
#else /* ... */
#undef __local___localdep_shared_lock_waitfor_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_waitfor_with_timeout_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL (__FCALL shared_recursive_lock_waitfor)(struct shared_recursive_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_waitfor_with_timeout)(&__self->sr_lock, __abs_timeout);
}
#endif /* ... */
} /* extern "C++" */
#if defined(__USE_TIME64) && (!defined(__USE_STRUCT64_MACRO) || !defined(_TIMESPEC_MATCHES_TIMESPEC64))
extern "C++" {
#if defined(__CRT_HAVE_shared_recursive_lock_acquire_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__CRT_HAVE_shared_lock_acquire_with_timeout) || defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_acquire_with_timeout64_defined
#define __local___localdep_shared_lock_acquire_with_timeout64_defined
#ifdef __CRT_HAVE_shared_lock_acquire_with_timeout
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_acquire_with_timeout64)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_acquire_with_timeout64 __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_lock_acquire_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_acquire_with_timeout64_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,shared_recursive_lock_acquire,(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_lock_acquire_with_timeout,{
	__BOOL __result;
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self)) {
		++__self->sr_rcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_acquire_with_timeout64)(&__self->sr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_lock_setown(__self);
	return __result;
})
#elif defined(__CRT_HAVE_shared_recursive_lock_acquire_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,shared_recursive_lock_acquire,(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_lock_acquire_with_timeout64)
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,shared_recursive_lock_acquire,(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_lock_acquire_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_shared_lock_acquire_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_acquire_with_timeout64_defined
#define __local___localdep_shared_lock_acquire_with_timeout64_defined
#if defined(__CRT_HAVE_shared_lock_acquire_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_acquire_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_acquire_with_timeout64)
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_acquire_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_acquire_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_acquire_with_timeout64 __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_lock_acquire_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_acquire_with_timeout64_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2) __BOOL (__FCALL shared_recursive_lock_acquire)(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	__BOOL __result;
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self)) {
		++__self->sr_rcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_acquire_with_timeout64)(&__self->sr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_lock_setown(__self);
	return __result;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_lock_waitfor_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) || defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_waitfor_with_timeout64_defined
#define __local___localdep_shared_lock_waitfor_with_timeout64_defined
#ifdef __CRT_HAVE_shared_lock_waitfor_with_timeout
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_waitfor_with_timeout64 __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_lock_waitfor_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_waitfor_with_timeout64_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,shared_recursive_lock_waitfor,(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_lock_waitfor_with_timeout,{
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_waitfor_with_timeout64)(&__self->sr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_lock_waitfor_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,shared_recursive_lock_waitfor,(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_lock_waitfor_with_timeout64)
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,shared_recursive_lock_waitfor,(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_waitfor_with_timeout64_defined
#define __local___localdep_shared_lock_waitfor_with_timeout64_defined
#if defined(__CRT_HAVE_shared_lock_waitfor_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_waitfor_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_lock_waitfor_with_timeout64)
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2),__BOOL,__THROWING,__FCALL,__localdep_shared_lock_waitfor_with_timeout64,(struct shared_lock *__restrict __self, struct timespec64 const *__abs_timeout),shared_lock_waitfor_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_waitfor_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_lock_waitfor_with_timeout64 __LIBC_LOCAL_NAME(shared_lock_waitfor_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_lock_waitfor_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_waitfor_with_timeout64_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2) __BOOL (__FCALL shared_recursive_lock_waitfor)(struct shared_recursive_lock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (__shared_recursive_lock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_waitfor_with_timeout64)(&__self->sr_lock, __abs_timeout);
}
#endif /* ... */
} /* extern "C++" */
#endif /* __USE_TIME64 && (!__USE_STRUCT64_MACRO || !_TIMESPEC_MATCHES_TIMESPEC64) */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
#define __PRIVATE_shared_recursive_lock_acquire_1 (shared_recursive_lock_acquire)
#define __PRIVATE_shared_recursive_lock_acquire_2 shared_recursive_lock_acquire_with_timeout
#define __PRIVATE_shared_recursive_lock_waitfor_1 (shared_recursive_lock_waitfor)
#define __PRIVATE_shared_recursive_lock_waitfor_2 shared_recursive_lock_waitfor_with_timeout
#define shared_recursive_lock_acquire(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_lock_acquire_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_lock_waitfor(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_lock_waitfor_, (__VA_ARGS__))(__VA_ARGS__)
#ifdef __USE_TIME64
#define __PRIVATE_shared_recursive_lock_acquire64_1 (shared_recursive_lock_acquire)
#define __PRIVATE_shared_recursive_lock_acquire64_2 shared_recursive_lock_acquire_with_timeout64
#define __PRIVATE_shared_recursive_lock_waitfor64_1 (shared_recursive_lock_waitfor)
#define __PRIVATE_shared_recursive_lock_waitfor64_2 shared_recursive_lock_waitfor_with_timeout64
#define shared_recursive_lock_acquire64(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_lock_acquire64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_lock_waitfor64(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_lock_waitfor64_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __USE_TIME64 */
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_SCHED_SHARED_RECURSIVE_LOCK_H */
