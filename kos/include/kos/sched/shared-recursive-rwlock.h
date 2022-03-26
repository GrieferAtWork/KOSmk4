/* HASH CRC-32:0x9a956fb4 */
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
#ifndef _KOS_SCHED_SHARED_RECURSIVE_RWLOCK_H
#define _KOS_SCHED_SHARED_RECURSIVE_RWLOCK_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <kos/bits/shared-rwlock.h>
#include <kos/bits/shared-recursive-rwlock.h>
#include <kos/sched/shared-rwlock.h>
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
 * `shared_recursive_rwlock' just like  `shared_rwlock', but allows  for
 * the owning thread to recursively acquire a write-lock multiple times.
 * WARNING: Trying to acquire a write-lock when holding a read-lock will
 *          DEADLOCK. The only way to safely do this is by making use of
 *          `shared_recursive_rwlock_upgrade(3)'!
 *
 * NOTE: This system is NOT available in kernel-space. It could easily be
 *       provided, using the same implementation as in user-space, but we
 *       intentionally don't do this as the necessity of recursive  locks
 *       indicates a flaw in your design.
 *       If  it's possible that you might need to recursively acquire the
 *       same lock, then that means that your function itself is able  to
 *       recurse. This fact alone violates the unspoken rule of trying to
 *       be  non-blocking about most of everything, and you should try to
 *       re-design your system, preferably using atomic locks!
 *
 * The only reason why the system is provided in user-space, is  because
 * it  is needed for stdio files, which  by design have to use recursive
 * locks, (s.a. `flockfile(3)',  `funlockfile(3)', and interaction  with
 * `funopen(3)').  And  because certain  stdio operations  are read-only
 * (ftell(3)), it stands to reason to use a read/write-lock that is also
 * able to do recursive write-locks.
 */

#define SHARED_RECURSIVE_RWLOCK_INIT              { SHARED_RWLOCK_INIT, __SHARED_RECURSIVE_RWLOCK_BADTID, 0 }
#define SHARED_RECURSIVE_RWLOCK_INIT_READ         { SHARED_RWLOCK_INIT_READ, __SHARED_RECURSIVE_RWLOCK_BADTID, 0 }
#define shared_recursive_rwlock_init(self)        (void)(shared_rwlock_init(&(self)->srr_lock), (self)->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID, (self)->srr_wrcnt = 0)
#define shared_recursive_rwlock_init_read(self)   (void)(shared_rwlock_init_read(&(self)->srr_lock), (self)->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID, (self)->srr_wrcnt = 0)
#define shared_recursive_rwlock_init_write(self)  (void)(shared_rwlock_init_write(&(self)->srr_lock), __shared_recursive_rwlock_setown(self))
#ifdef __SHARED_RECURSIVE_RWLOCK_BADTID_ISZERO
#define shared_recursive_rwlock_cinit(self)       (shared_rwlock_cinit(&(self)->srr_lock), __hybrid_assert((self)->srr_writer == __SHARED_RECURSIVE_RWLOCK_BADTID), __hybrid_assert((self)->srr_wrcnt == 0))
#define shared_recursive_rwlock_cinit_read(self)  (shared_rwlock_cinit_read(&(self)->srr_lock), __hybrid_assert((self)->srr_writer == __SHARED_RECURSIVE_RWLOCK_BADTID), __hybrid_assert((self)->srr_wrcnt == 0))
#else /* __SHARED_RECURSIVE_RWLOCK_BADTID_ISZERO */
#define shared_recursive_rwlock_cinit(self)       (shared_rwlock_cinit(&(self)->srr_lock), (self)->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID, __hybrid_assert((self)->srr_wrcnt == 0))
#define shared_recursive_rwlock_cinit_read(self)  (shared_rwlock_cinit_read(&(self)->srr_lock), (self)->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID, __hybrid_assert((self)->srr_wrcnt == 0))
#endif /* !__SHARED_RECURSIVE_RWLOCK_BADTID_ISZERO */
#define shared_recursive_rwlock_cinit_write(self) (void)(shared_rwlock_cinit_write(&(self)->srr_lock), __shared_recursive_rwlock_setown(self))
#define shared_recursive_rwlock_broadcast_for_fini(self) \
	shared_rwlock_broadcast_for_fini(&(self)->srr_lock)

/* Check if reading/writing is possible, or a read/write lock is being held. */
#define shared_recursive_rwlock_canread(self)  (shared_rwlock_canread(&(self)->srr_lock) || __shared_recursive_rwlock_isown(self))
#define shared_recursive_rwlock_canwrite(self) (shared_rwlock_canwrite(&(self)->srr_lock) || __shared_recursive_rwlock_isown(self))
#define shared_recursive_rwlock_reading(self)  shared_rwlock_reading(&(self)->srr_lock)
#define shared_recursive_rwlock_writing(self)  __shared_recursive_rwlock_isown(self)
/* #define shared_recursive_rwlock_writing(self) (shared_rwlock_writing(&(self)->srr_lock) && __shared_recursive_rwlock_isown(self)) */

/* >> shared_recursive_rwlock_tryupgrade(3)
 * Try to upgrade a read-lock to a recursive write-lock. Return `false' upon failure. */
#define shared_recursive_rwlock_tryupgrade(self)    \
	(shared_rwlock_tryupgrade(&(self)->srr_lock) && \
	 (__shared_recursive_rwlock_setown(self), 1))

#ifdef __CRT_HAVE_shared_recursive_rwlock_tryread
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_tryread_defined
#define __local___localdep_shared_rwlock_tryread_defined
#ifdef __CRT_HAVE_shared_rwlock_tryread
/* >> shared_rwlock_tryread(3)
 * Try to acquire a read-lock to `self' */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_rwlock_tryread,(struct shared_rwlock *__restrict __self),shared_rwlock_tryread,{
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
__LOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_rwlock_tryread)(struct shared_rwlock *__restrict __self) {
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
#endif /* !__local___localdep_shared_rwlock_tryread_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_tryread(3)
 * Try  to acquire a read-lock to `self' */
__COMPILER_CEIDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,shared_recursive_rwlock_tryread,(struct shared_recursive_rwlock *__restrict __self),{
	if ((__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_tryread)(&__self->srr_lock))
		return 1;
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	return 0;
})
#else /* __CRT_HAVE_shared_recursive_rwlock_tryread */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_tryread_defined
#define __local___localdep_shared_rwlock_tryread_defined
#ifdef __CRT_HAVE_shared_rwlock_tryread
/* >> shared_rwlock_tryread(3)
 * Try to acquire a read-lock to `self' */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_rwlock_tryread,(struct shared_rwlock *__restrict __self),shared_rwlock_tryread,{
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
__LOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_rwlock_tryread)(struct shared_rwlock *__restrict __self) {
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
#endif /* !__local___localdep_shared_rwlock_tryread_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_tryread(3)
 * Try  to acquire a read-lock to `self' */
__LOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL shared_recursive_rwlock_tryread)(struct shared_recursive_rwlock *__restrict __self) {
	if ((__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_tryread)(&__self->srr_lock))
		return 1;
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	return 0;
}
#endif /* !__CRT_HAVE_shared_recursive_rwlock_tryread */
#ifdef __CRT_HAVE_shared_recursive_rwlock_trywrite
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_trywrite_defined
#define __local___localdep_shared_rwlock_trywrite_defined
#ifdef __CRT_HAVE_shared_rwlock_trywrite
/* >> shared_rwlock_trywrite(3)
 * Try to acquire a write-lock to `self' */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_rwlock_trywrite,(struct shared_rwlock *__restrict __self),shared_rwlock_trywrite,{
	if (!__hybrid_atomic_cmpxch(__self->sl_lock, 0, (__UINTPTR_TYPE__)-1,
	                            __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
		return 0;
	__COMPILER_BARRIER();
	return 1;
})
#else /* __CRT_HAVE_shared_rwlock_trywrite */
/* >> shared_rwlock_trywrite(3)
 * Try to acquire a write-lock to `self' */
__LOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_rwlock_trywrite)(struct shared_rwlock *__restrict __self) {
	if (!__hybrid_atomic_cmpxch(__self->sl_lock, 0, (__UINTPTR_TYPE__)-1,
	                            __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
		return 0;
	__COMPILER_BARRIER();
	return 1;
}
#endif /* !__CRT_HAVE_shared_rwlock_trywrite */
#endif /* !__local___localdep_shared_rwlock_trywrite_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_trywrite(3)
 * Try to acquire a recursive write-lock to `self' */
__COMPILER_CEIDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,shared_recursive_rwlock_trywrite,(struct shared_recursive_rwlock *__restrict __self),{
	if ((__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_trywrite)(&__self->srr_lock)) {
		__shared_recursive_rwlock_setown(__self);
		return 1;
	}
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	return 0;
})
#else /* __CRT_HAVE_shared_recursive_rwlock_trywrite */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_trywrite_defined
#define __local___localdep_shared_rwlock_trywrite_defined
#ifdef __CRT_HAVE_shared_rwlock_trywrite
/* >> shared_rwlock_trywrite(3)
 * Try to acquire a write-lock to `self' */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_rwlock_trywrite,(struct shared_rwlock *__restrict __self),shared_rwlock_trywrite,{
	if (!__hybrid_atomic_cmpxch(__self->sl_lock, 0, (__UINTPTR_TYPE__)-1,
	                            __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
		return 0;
	__COMPILER_BARRIER();
	return 1;
})
#else /* __CRT_HAVE_shared_rwlock_trywrite */
/* >> shared_rwlock_trywrite(3)
 * Try to acquire a write-lock to `self' */
__LOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_rwlock_trywrite)(struct shared_rwlock *__restrict __self) {
	if (!__hybrid_atomic_cmpxch(__self->sl_lock, 0, (__UINTPTR_TYPE__)-1,
	                            __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
		return 0;
	__COMPILER_BARRIER();
	return 1;
}
#endif /* !__CRT_HAVE_shared_rwlock_trywrite */
#endif /* !__local___localdep_shared_rwlock_trywrite_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_trywrite(3)
 * Try to acquire a recursive write-lock to `self' */
__LOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL shared_recursive_rwlock_trywrite)(struct shared_recursive_rwlock *__restrict __self) {
	if ((__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_trywrite)(&__self->srr_lock)) {
		__shared_recursive_rwlock_setown(__self);
		return 1;
	}
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	return 0;
}
#endif /* !__CRT_HAVE_shared_recursive_rwlock_trywrite */
#if defined(__CRT_HAVE_shared_recursive_rwlock_endwrite) && defined(__shared_rwlock_wrwait_send)
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__COMPILER_CEIDECLARE(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,shared_recursive_rwlock_endwrite,(struct shared_recursive_rwlock *__restrict __self),{
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_endwrite)
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__LIBC __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL shared_recursive_rwlock_endwrite)(struct shared_recursive_rwlock *__restrict __self) __CASMNAME_SAME("shared_recursive_rwlock_endwrite");
#elif defined(__shared_rwlock_wrwait_send)
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL shared_recursive_rwlock_endwrite)(struct shared_recursive_rwlock *__restrict __self) {
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_endread) && defined(__shared_rwlock_wrwait_send)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_recursive_rwlock_endwrite_defined
#define __local___localdep_shared_recursive_rwlock_endwrite_defined
#ifdef __CRT_HAVE_shared_recursive_rwlock_endwrite
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_recursive_rwlock_endwrite,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endwrite,{
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
})
#else /* __CRT_HAVE_shared_recursive_rwlock_endwrite */
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_recursive_rwlock_endwrite)(struct shared_recursive_rwlock *__restrict __self) {
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
}
#endif /* !__CRT_HAVE_shared_recursive_rwlock_endwrite */
#endif /* !__local___localdep_shared_recursive_rwlock_endwrite_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__COMPILER_CEIDECLARE(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,shared_recursive_rwlock_endread,(struct shared_recursive_rwlock *__restrict __self),{
	__UINTPTR_TYPE__ __result;
	__COMPILER_READ_BARRIER();
	if (__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1)
		return (__NAMESPACE_LOCAL_SYM __localdep_shared_recursive_rwlock_endwrite)(__self);
	__hybrid_assertf(__self->srr_lock.sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(__self->srr_lock.sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(&__self->srr_lock);
	return __result == 0;
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_endread)
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LIBC __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL shared_recursive_rwlock_endread)(struct shared_recursive_rwlock *__restrict __self) __CASMNAME_SAME("shared_recursive_rwlock_endread");
#elif defined(__shared_rwlock_wrwait_send)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_recursive_rwlock_endwrite_defined
#define __local___localdep_shared_recursive_rwlock_endwrite_defined
#ifdef __CRT_HAVE_shared_recursive_rwlock_endwrite
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_recursive_rwlock_endwrite,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endwrite,{
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
})
#else /* __CRT_HAVE_shared_recursive_rwlock_endwrite */
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_recursive_rwlock_endwrite)(struct shared_recursive_rwlock *__restrict __self) {
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
}
#endif /* !__CRT_HAVE_shared_recursive_rwlock_endwrite */
#endif /* !__local___localdep_shared_recursive_rwlock_endwrite_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL shared_recursive_rwlock_endread)(struct shared_recursive_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __result;
	__COMPILER_READ_BARRIER();
	if (__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1)
		return (__NAMESPACE_LOCAL_SYM __localdep_shared_recursive_rwlock_endwrite)(__self);
	__hybrid_assertf(__self->srr_lock.sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(__self->srr_lock.sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(&__self->srr_lock);
	return __result == 0;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_endread) && defined(__shared_rwlock_wrwait_send)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_recursive_rwlock_endwrite_defined
#define __local___localdep_shared_recursive_rwlock_endwrite_defined
#ifdef __CRT_HAVE_shared_recursive_rwlock_endwrite
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_recursive_rwlock_endwrite,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endwrite,{
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
})
#else /* __CRT_HAVE_shared_recursive_rwlock_endwrite */
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_recursive_rwlock_endwrite)(struct shared_recursive_rwlock *__restrict __self) {
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
}
#endif /* !__CRT_HAVE_shared_recursive_rwlock_endwrite */
#endif /* !__local___localdep_shared_recursive_rwlock_endwrite_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,shared_recursive_rwlock_end,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endread,{
	__UINTPTR_TYPE__ __result;
	__COMPILER_READ_BARRIER();
	if (__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1)
		return (__NAMESPACE_LOCAL_SYM __localdep_shared_recursive_rwlock_endwrite)(__self);
	__hybrid_assertf(__self->srr_lock.sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(__self->srr_lock.sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(&__self->srr_lock);
	return __result == 0;
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_endread)
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__COMPILER_CREDIRECT(__LIBC,__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,shared_recursive_rwlock_end,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endread,(__self))
#elif defined(__shared_rwlock_wrwait_send)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_recursive_rwlock_endwrite_defined
#define __local___localdep_shared_recursive_rwlock_endwrite_defined
#ifdef __CRT_HAVE_shared_recursive_rwlock_endwrite
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_recursive_rwlock_endwrite,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endwrite,{
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
})
#else /* __CRT_HAVE_shared_recursive_rwlock_endwrite */
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_recursive_rwlock_endwrite)(struct shared_recursive_rwlock *__restrict __self) {
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
}
#endif /* !__CRT_HAVE_shared_recursive_rwlock_endwrite */
#endif /* !__local___localdep_shared_recursive_rwlock_endwrite_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL shared_recursive_rwlock_end)(struct shared_recursive_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __result;
	__COMPILER_READ_BARRIER();
	if (__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1)
		return (__NAMESPACE_LOCAL_SYM __localdep_shared_recursive_rwlock_endwrite)(__self);
	__hybrid_assertf(__self->srr_lock.sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(__self->srr_lock.sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(&__self->srr_lock);
	return __result == 0;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_downgrade) && (defined(__CRT_HAVE_shared_rwlock_downgrade) || defined(__shared_rwlock_wrwait_send))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_downgrade_defined
#define __local___localdep_shared_rwlock_downgrade_defined
#if defined(__CRT_HAVE_shared_rwlock_downgrade) && defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_NONNULL((1)),void,__NOTHROW,__FCALL,__localdep_shared_rwlock_downgrade,(struct shared_rwlock *__restrict __self),shared_rwlock_downgrade,{
	__COMPILER_WRITE_BARRIER();
	__hybrid_assertf(__self->sl_lock == (__UINTPTR_TYPE__)-1, "Lock isn't in write-mode (%x)", __self->sl_lock);
	__hybrid_atomic_store(__self->sl_lock, 1, __ATOMIC_RELEASE);
	__shared_rwlock_rdwait_broadcast(__self); /* Allow for more readers. */
})
#elif defined(__CRT_HAVE_shared_rwlock_downgrade)
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_NONNULL((1)),__NOTHROW,__FCALL,__localdep_shared_rwlock_downgrade,(struct shared_rwlock *__restrict __self),shared_rwlock_downgrade,(__self))
#elif defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(__FCALL __localdep_shared_rwlock_downgrade)(struct shared_rwlock *__restrict __self) {
	__COMPILER_WRITE_BARRIER();
	__hybrid_assertf(__self->sl_lock == (__UINTPTR_TYPE__)-1, "Lock isn't in write-mode (%x)", __self->sl_lock);
	__hybrid_atomic_store(__self->sl_lock, 1, __ATOMIC_RELEASE);
	__shared_rwlock_rdwait_broadcast(__self); /* Allow for more readers. */
}
#else /* ... */
#undef __local___localdep_shared_rwlock_downgrade_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_downgrade_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_downgrade(3)
 * Downgrade a recursive write-lock to a read-lock (Always succeeds, but you have
 * to ensure  that  you're only  holding  a  single write-lock  at  the  moment). */
__COMPILER_CEIDECLARE(__NOBLOCK __ATTR_NONNULL((1)),void,__NOTHROW,__FCALL,shared_recursive_rwlock_downgrade,(struct shared_recursive_rwlock *__restrict __self),{
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self), "You're not holding this lock");
	__hybrid_assertf(__self->srr_wrcnt > 0, "You're holding more than 1 write-lock");
	__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
	__COMPILER_WRITE_BARRIER();
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_downgrade)(&__self->srr_lock);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_downgrade)
/* >> shared_recursive_rwlock_downgrade(3)
 * Downgrade a recursive write-lock to a read-lock (Always succeeds, but you have
 * to ensure  that  you're only  holding  a  single write-lock  at  the  moment). */
__LIBC __NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(__FCALL shared_recursive_rwlock_downgrade)(struct shared_recursive_rwlock *__restrict __self) __CASMNAME_SAME("shared_recursive_rwlock_downgrade");
#elif defined(__CRT_HAVE_shared_rwlock_downgrade) || defined(__shared_rwlock_wrwait_send)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_downgrade_defined
#define __local___localdep_shared_rwlock_downgrade_defined
#if defined(__CRT_HAVE_shared_rwlock_downgrade) && defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_NONNULL((1)),void,__NOTHROW,__FCALL,__localdep_shared_rwlock_downgrade,(struct shared_rwlock *__restrict __self),shared_rwlock_downgrade,{
	__COMPILER_WRITE_BARRIER();
	__hybrid_assertf(__self->sl_lock == (__UINTPTR_TYPE__)-1, "Lock isn't in write-mode (%x)", __self->sl_lock);
	__hybrid_atomic_store(__self->sl_lock, 1, __ATOMIC_RELEASE);
	__shared_rwlock_rdwait_broadcast(__self); /* Allow for more readers. */
})
#elif defined(__CRT_HAVE_shared_rwlock_downgrade)
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_NONNULL((1)),__NOTHROW,__FCALL,__localdep_shared_rwlock_downgrade,(struct shared_rwlock *__restrict __self),shared_rwlock_downgrade,(__self))
#elif defined(__shared_rwlock_wrwait_send)
/* >> shared_rwlock_downgrade(3)
 * Downgrade a write-lock to a read-lock (Always succeeds). */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(__FCALL __localdep_shared_rwlock_downgrade)(struct shared_rwlock *__restrict __self) {
	__COMPILER_WRITE_BARRIER();
	__hybrid_assertf(__self->sl_lock == (__UINTPTR_TYPE__)-1, "Lock isn't in write-mode (%x)", __self->sl_lock);
	__hybrid_atomic_store(__self->sl_lock, 1, __ATOMIC_RELEASE);
	__shared_rwlock_rdwait_broadcast(__self); /* Allow for more readers. */
}
#else /* ... */
#undef __local___localdep_shared_rwlock_downgrade_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_downgrade_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_downgrade(3)
 * Downgrade a recursive write-lock to a read-lock (Always succeeds, but you have
 * to ensure  that  you're only  holding  a  single write-lock  at  the  moment). */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(__FCALL shared_recursive_rwlock_downgrade)(struct shared_recursive_rwlock *__restrict __self) {
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self), "You're not holding this lock");
	__hybrid_assertf(__self->srr_wrcnt > 0, "You're holding more than 1 write-lock");
	__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
	__COMPILER_WRITE_BARRIER();
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_downgrade)(&__self->srr_lock);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_upgrade) && (defined(__CRT_HAVE_shared_recursive_rwlock_endread) || defined(__shared_rwlock_wrwait_send)) && (defined(__CRT_HAVE_shared_recursive_rwlock_write) || defined(__CRT_HAVE_shared_rwlock_write) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_recursive_rwlock_endread_defined
#define __local___localdep_shared_recursive_rwlock_endread_defined
#if defined(__CRT_HAVE_shared_recursive_rwlock_endread) && defined(__shared_rwlock_wrwait_send)
#ifndef __local___localdep_shared_recursive_rwlock_endwrite_defined
#define __local___localdep_shared_recursive_rwlock_endwrite_defined
#ifdef __CRT_HAVE_shared_recursive_rwlock_endwrite
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_recursive_rwlock_endwrite,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endwrite,{
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
})
#else /* __CRT_HAVE_shared_recursive_rwlock_endwrite */
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_recursive_rwlock_endwrite)(struct shared_recursive_rwlock *__restrict __self) {
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
}
#endif /* !__CRT_HAVE_shared_recursive_rwlock_endwrite */
#endif /* !__local___localdep_shared_recursive_rwlock_endwrite_defined */
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_recursive_rwlock_endread,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endread,{
	__UINTPTR_TYPE__ __result;
	__COMPILER_READ_BARRIER();
	if (__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1)
		return (__localdep_shared_recursive_rwlock_endwrite)(__self);
	__hybrid_assertf(__self->srr_lock.sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(__self->srr_lock.sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(&__self->srr_lock);
	return __result == 0;
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_endread)
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__COMPILER_CREDIRECT(__LIBC,__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_recursive_rwlock_endread,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endread,(__self))
#elif defined(__shared_rwlock_wrwait_send)
#ifndef __local___localdep_shared_recursive_rwlock_endwrite_defined
#define __local___localdep_shared_recursive_rwlock_endwrite_defined
#ifdef __CRT_HAVE_shared_recursive_rwlock_endwrite
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_recursive_rwlock_endwrite,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endwrite,{
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
})
#else /* __CRT_HAVE_shared_recursive_rwlock_endwrite */
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_recursive_rwlock_endwrite)(struct shared_recursive_rwlock *__restrict __self) {
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
}
#endif /* !__CRT_HAVE_shared_recursive_rwlock_endwrite */
#endif /* !__local___localdep_shared_recursive_rwlock_endwrite_defined */
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_recursive_rwlock_endread)(struct shared_recursive_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __result;
	__COMPILER_READ_BARRIER();
	if (__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1)
		return (__localdep_shared_recursive_rwlock_endwrite)(__self);
	__hybrid_assertf(__self->srr_lock.sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(__self->srr_lock.sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(&__self->srr_lock);
	return __result == 0;
}
#else /* ... */
#undef __local___localdep_shared_recursive_rwlock_endread_defined
#endif /* !... */
#endif /* !__local___localdep_shared_recursive_rwlock_endread_defined */
#ifndef __local___localdep_shared_recursive_rwlock_write_defined
#define __local___localdep_shared_recursive_rwlock_write_defined
#if defined(__CRT_HAVE_shared_recursive_rwlock_write) && (defined(__CRT_HAVE_shared_rwlock_write) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
#ifndef __local___localdep_shared_rwlock_write_defined
#define __local___localdep_shared_rwlock_write_defined
#ifdef __CRT_HAVE_shared_rwlock_write
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_rwlock_write,(struct shared_rwlock *__restrict __self),shared_rwlock_write,(__self))
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
/* >> shared_recursive_rwlock_write(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock. */
__COMPILER_CEIREDIRECT(__BLOCKING __ATTR_NONNULL((1)),void,__THROWING,__FCALL,__localdep_shared_recursive_rwlock_write,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_write,{
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return;
	}
	(__localdep_shared_rwlock_write)(&__self->srr_lock);
	__shared_recursive_rwlock_setown(__self);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_write)
/* >> shared_recursive_rwlock_write(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_recursive_rwlock_write,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_write,(__self))
#elif defined(__CRT_HAVE_shared_rwlock_write) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
#ifndef __local___localdep_shared_rwlock_write_defined
#define __local___localdep_shared_rwlock_write_defined
#ifdef __CRT_HAVE_shared_rwlock_write
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_rwlock_write,(struct shared_rwlock *__restrict __self),shared_rwlock_write,(__self))
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
/* >> shared_recursive_rwlock_write(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock. */
__LOCAL __BLOCKING __ATTR_NONNULL((1)) void (__FCALL __localdep_shared_recursive_rwlock_write)(struct shared_recursive_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return;
	}
	(__localdep_shared_rwlock_write)(&__self->srr_lock);
	__shared_recursive_rwlock_setown(__self);
}
#else /* ... */
#undef __local___localdep_shared_recursive_rwlock_write_defined
#endif /* !... */
#endif /* !__local___localdep_shared_recursive_rwlock_write_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_upgrade(3)
 * Blocking-upgrade a read-lock into a recursive write-lock
 * NOTE: The lock is always upgraded, but when `false' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources.
 * @return: true:  Upgrade was performed without the read-lock being lost
 * @return: false: The read-lock had to be released before a recursive write-lock was acquired */
__COMPILER_CEIDECLARE(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_upgrade,(struct shared_recursive_rwlock *__restrict __self),{
	if (__hybrid_atomic_cmpxch(__self->srr_lock.sl_lock, 1, (__UINTPTR_TYPE__)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)) {
		__shared_recursive_rwlock_setown(__self);
		return 1; /* Lock wasn't lost */
	}
	(__NAMESPACE_LOCAL_SYM __localdep_shared_recursive_rwlock_endread)(__self);
	(__NAMESPACE_LOCAL_SYM __localdep_shared_recursive_rwlock_write)(__self);
	return 0; /* Lock was (temporarily) lost */
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_upgrade)
/* >> shared_recursive_rwlock_upgrade(3)
 * Blocking-upgrade a read-lock into a recursive write-lock
 * NOTE: The lock is always upgraded, but when `false' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources.
 * @return: true:  Upgrade was performed without the read-lock being lost
 * @return: false: The read-lock had to be released before a recursive write-lock was acquired */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_upgrade)(struct shared_recursive_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_rwlock_upgrade");
#elif (defined(__CRT_HAVE_shared_recursive_rwlock_endread) || defined(__shared_rwlock_wrwait_send)) && (defined(__CRT_HAVE_shared_recursive_rwlock_write) || defined(__CRT_HAVE_shared_rwlock_write) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_recursive_rwlock_endread_defined
#define __local___localdep_shared_recursive_rwlock_endread_defined
#if defined(__CRT_HAVE_shared_recursive_rwlock_endread) && defined(__shared_rwlock_wrwait_send)
#ifndef __local___localdep_shared_recursive_rwlock_endwrite_defined
#define __local___localdep_shared_recursive_rwlock_endwrite_defined
#ifdef __CRT_HAVE_shared_recursive_rwlock_endwrite
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_recursive_rwlock_endwrite,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endwrite,{
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
})
#else /* __CRT_HAVE_shared_recursive_rwlock_endwrite */
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_recursive_rwlock_endwrite)(struct shared_recursive_rwlock *__restrict __self) {
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
}
#endif /* !__CRT_HAVE_shared_recursive_rwlock_endwrite */
#endif /* !__local___localdep_shared_recursive_rwlock_endwrite_defined */
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_recursive_rwlock_endread,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endread,{
	__UINTPTR_TYPE__ __result;
	__COMPILER_READ_BARRIER();
	if (__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1)
		return (__localdep_shared_recursive_rwlock_endwrite)(__self);
	__hybrid_assertf(__self->srr_lock.sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(__self->srr_lock.sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(&__self->srr_lock);
	return __result == 0;
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_endread)
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__COMPILER_CREDIRECT(__LIBC,__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_recursive_rwlock_endread,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endread,(__self))
#elif defined(__shared_rwlock_wrwait_send)
#ifndef __local___localdep_shared_recursive_rwlock_endwrite_defined
#define __local___localdep_shared_recursive_rwlock_endwrite_defined
#ifdef __CRT_HAVE_shared_recursive_rwlock_endwrite
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_NONNULL((1)),__BOOL,__NOTHROW,__FCALL,__localdep_shared_recursive_rwlock_endwrite,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_endwrite,{
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
})
#else /* __CRT_HAVE_shared_recursive_rwlock_endwrite */
/* >> shared_recursive_rwlock_endwrite(3)
 * Release a recursive write-lock from `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_recursive_rwlock_endwrite)(struct shared_recursive_rwlock *__restrict __self) {
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1,
	                 "Lock isn't in write-mode (%x)",
	                 __self->srr_lock.sl_lock);
	__hybrid_assertf(__shared_recursive_rwlock_isown(__self),
	                 "You're not the owner of this lock");
	if (__self->srr_wrcnt == 0) {
		__self->srr_writer = __SHARED_RECURSIVE_RWLOCK_BADTID;
		__COMPILER_BARRIER();
		__hybrid_atomic_store(__self->srr_lock.sl_lock, 0, __ATOMIC_RELEASE);
		if (!__shared_rwlock_wrwait_send(&__self->srr_lock))
			__shared_rwlock_rdwait_broadcast(&__self->srr_lock);
		return 1;
	}
	--__self->srr_wrcnt;
	return 0;
}
#endif /* !__CRT_HAVE_shared_recursive_rwlock_endwrite */
#endif /* !__local___localdep_shared_recursive_rwlock_endwrite_defined */
/* >> shared_recursive_rwlock_endread(3)
 * Release  a   read-lock  from   `self'
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LOCAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL __NOTHROW(__FCALL __localdep_shared_recursive_rwlock_endread)(struct shared_recursive_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __result;
	__COMPILER_READ_BARRIER();
	if (__self->srr_lock.sl_lock == (__UINTPTR_TYPE__)-1)
		return (__localdep_shared_recursive_rwlock_endwrite)(__self);
	__hybrid_assertf(__self->srr_lock.sl_lock != 0, "Lock isn't held by anyone");
	__result = __hybrid_atomic_decfetch(__self->srr_lock.sl_lock, __ATOMIC_RELEASE);
	if (__result == 0)
		__shared_rwlock_wrwait_send(&__self->srr_lock);
	return __result == 0;
}
#else /* ... */
#undef __local___localdep_shared_recursive_rwlock_endread_defined
#endif /* !... */
#endif /* !__local___localdep_shared_recursive_rwlock_endread_defined */
#ifndef __local___localdep_shared_recursive_rwlock_write_defined
#define __local___localdep_shared_recursive_rwlock_write_defined
#if defined(__CRT_HAVE_shared_recursive_rwlock_write) && (defined(__CRT_HAVE_shared_rwlock_write) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
#ifndef __local___localdep_shared_rwlock_write_defined
#define __local___localdep_shared_rwlock_write_defined
#ifdef __CRT_HAVE_shared_rwlock_write
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_rwlock_write,(struct shared_rwlock *__restrict __self),shared_rwlock_write,(__self))
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
/* >> shared_recursive_rwlock_write(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock. */
__COMPILER_CEIREDIRECT(__BLOCKING __ATTR_NONNULL((1)),void,__THROWING,__FCALL,__localdep_shared_recursive_rwlock_write,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_write,{
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return;
	}
	(__localdep_shared_rwlock_write)(&__self->srr_lock);
	__shared_recursive_rwlock_setown(__self);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_write)
/* >> shared_recursive_rwlock_write(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_recursive_rwlock_write,(struct shared_recursive_rwlock *__restrict __self),shared_recursive_rwlock_write,(__self))
#elif defined(__CRT_HAVE_shared_rwlock_write) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
#ifndef __local___localdep_shared_rwlock_write_defined
#define __local___localdep_shared_rwlock_write_defined
#ifdef __CRT_HAVE_shared_rwlock_write
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_rwlock_write,(struct shared_rwlock *__restrict __self),shared_rwlock_write,(__self))
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
/* >> shared_recursive_rwlock_write(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock. */
__LOCAL __BLOCKING __ATTR_NONNULL((1)) void (__FCALL __localdep_shared_recursive_rwlock_write)(struct shared_recursive_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return;
	}
	(__localdep_shared_rwlock_write)(&__self->srr_lock);
	__shared_recursive_rwlock_setown(__self);
}
#else /* ... */
#undef __local___localdep_shared_recursive_rwlock_write_defined
#endif /* !... */
#endif /* !__local___localdep_shared_recursive_rwlock_write_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_upgrade(3)
 * Blocking-upgrade a read-lock into a recursive write-lock
 * NOTE: The lock is always upgraded, but when `false' is returned, no lock
 *       may  have been  held temporarily,  meaning that  the caller should
 *       re-load local copies of affected resources.
 * @return: true:  Upgrade was performed without the read-lock being lost
 * @return: false: The read-lock had to be released before a recursive write-lock was acquired */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_upgrade)(struct shared_recursive_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) {
	if (__hybrid_atomic_cmpxch(__self->srr_lock.sl_lock, 1, (__UINTPTR_TYPE__)-1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)) {
		__shared_recursive_rwlock_setown(__self);
		return 1; /* Lock wasn't lost */
	}
	(__NAMESPACE_LOCAL_SYM __localdep_shared_recursive_rwlock_endread)(__self);
	(__NAMESPACE_LOCAL_SYM __localdep_shared_recursive_rwlock_write)(__self);
	return 0; /* Lock was (temporarily) lost */
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_read) && (defined(__CRT_HAVE_shared_rwlock_read) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_read_defined
#define __local___localdep_shared_rwlock_read_defined
#ifdef __CRT_HAVE_shared_rwlock_read
/* >> shared_rwlock_read(3)
 * Acquire a read-lock to the given shared_rwlock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_rwlock_read,(struct shared_rwlock *__restrict __self),shared_rwlock_read,(__self))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_read(3)
 * Acquire a read-lock to the given shared_rwlock. */
#define __localdep_shared_rwlock_read __LIBC_LOCAL_NAME(shared_rwlock_read)
#else /* ... */
#undef __local___localdep_shared_rwlock_read_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_read_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_read(3)
 * Acquire a read-lock to the given shared_recursive_rwlock. */
__COMPILER_CEIDECLARE(__BLOCKING __ATTR_NONNULL((1)),void,__THROWING,__FCALL,shared_recursive_rwlock_read,(struct shared_recursive_rwlock *__restrict __self),{
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return;
	}
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_read)(&__self->srr_lock);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_read)
/* >> shared_recursive_rwlock_read(3)
 * Acquire a read-lock to the given shared_recursive_rwlock. */
__LIBC __BLOCKING __ATTR_NONNULL((1)) void (__FCALL shared_recursive_rwlock_read)(struct shared_recursive_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_rwlock_read");
#elif defined(__CRT_HAVE_shared_rwlock_read) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_read_defined
#define __local___localdep_shared_rwlock_read_defined
#ifdef __CRT_HAVE_shared_rwlock_read
/* >> shared_rwlock_read(3)
 * Acquire a read-lock to the given shared_rwlock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_rwlock_read,(struct shared_rwlock *__restrict __self),shared_rwlock_read,(__self))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_read(3)
 * Acquire a read-lock to the given shared_rwlock. */
#define __localdep_shared_rwlock_read __LIBC_LOCAL_NAME(shared_rwlock_read)
#else /* ... */
#undef __local___localdep_shared_rwlock_read_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_read_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_read(3)
 * Acquire a read-lock to the given shared_recursive_rwlock. */
__LOCAL __BLOCKING __ATTR_NONNULL((1)) void (__FCALL shared_recursive_rwlock_read)(struct shared_recursive_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return;
	}
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_read)(&__self->srr_lock);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_write) && (defined(__CRT_HAVE_shared_rwlock_write) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_write_defined
#define __local___localdep_shared_rwlock_write_defined
#ifdef __CRT_HAVE_shared_rwlock_write
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_rwlock_write,(struct shared_rwlock *__restrict __self),shared_rwlock_write,(__self))
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
/* >> shared_recursive_rwlock_write(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock. */
__COMPILER_CEIDECLARE(__BLOCKING __ATTR_NONNULL((1)),void,__THROWING,__FCALL,shared_recursive_rwlock_write,(struct shared_recursive_rwlock *__restrict __self),{
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return;
	}
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_write)(&__self->srr_lock);
	__shared_recursive_rwlock_setown(__self);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_write)
/* >> shared_recursive_rwlock_write(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock. */
__LIBC __BLOCKING __ATTR_NONNULL((1)) void (__FCALL shared_recursive_rwlock_write)(struct shared_recursive_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_rwlock_write");
#elif defined(__CRT_HAVE_shared_rwlock_write) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_write_defined
#define __local___localdep_shared_rwlock_write_defined
#ifdef __CRT_HAVE_shared_rwlock_write
/* >> shared_rwlock_write(3)
 * Acquire a write-lock to the given shared_rwlock. */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_rwlock_write,(struct shared_rwlock *__restrict __self),shared_rwlock_write,(__self))
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
/* >> shared_recursive_rwlock_write(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock. */
__LOCAL __BLOCKING __ATTR_NONNULL((1)) void (__FCALL shared_recursive_rwlock_write)(struct shared_recursive_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return;
	}
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_write)(&__self->srr_lock);
	__shared_recursive_rwlock_setown(__self);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_read_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && (defined(__CRT_HAVE_shared_rwlock_read_with_timeout) || (defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_read_with_timeout_defined
#define __local___localdep_shared_rwlock_read_with_timeout_defined
#ifdef __CRT_HAVE_shared_rwlock_read_with_timeout
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_read_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_read_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_read_with_timeout_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIDECLARE(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_read_with_timeout,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),{
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_read_with_timeout)(&__self->srr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_read_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_read_with_timeout)(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_rwlock_read_with_timeout");
#elif defined(__CRT_HAVE_shared_recursive_rwlock_read_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_read_with_timeout,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_rwlock_read_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_read_with_timeout_defined
#define __local___localdep_shared_rwlock_read_with_timeout_defined
#if defined(__CRT_HAVE_shared_rwlock_read_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_read_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_read_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_read_with_timeout_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_read_with_timeout)(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_read_with_timeout)(&__self->srr_lock, __abs_timeout);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_write_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && (defined(__CRT_HAVE_shared_rwlock_write_with_timeout) || (defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_write_with_timeout_defined
#define __local___localdep_shared_rwlock_write_with_timeout_defined
#ifdef __CRT_HAVE_shared_rwlock_write_with_timeout
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_write_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_write_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_write_with_timeout_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIDECLARE(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_write_with_timeout,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),{
	__BOOL __result;
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_write_with_timeout)(&__self->srr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_rwlock_setown(__self);
	return __result;
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_write_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_write_with_timeout)(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_rwlock_write_with_timeout");
#elif defined(__CRT_HAVE_shared_recursive_rwlock_write_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_write_with_timeout,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_rwlock_write_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_write_with_timeout_defined
#define __local___localdep_shared_rwlock_write_with_timeout_defined
#if defined(__CRT_HAVE_shared_rwlock_write_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_write_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_write_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_write_with_timeout_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_write_with_timeout)(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	__BOOL __result;
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_write_with_timeout)(&__self->srr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_rwlock_setown(__self);
	return __result;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_waitread) && (defined(__CRT_HAVE_shared_rwlock_waitread) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitread_defined
#define __local___localdep_shared_rwlock_waitread_defined
#ifdef __CRT_HAVE_shared_rwlock_waitread
/* >> shared_rwlock_waitread(3)
 * Wait until acquiring a read-lock to `self' no longer blocks */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_rwlock_waitread,(struct shared_rwlock *__restrict __self),shared_rwlock_waitread,(__self))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitread(3)
 * Wait until acquiring a read-lock to `self' no longer blocks */
#define __localdep_shared_rwlock_waitread __LIBC_LOCAL_NAME(shared_rwlock_waitread)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitread_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitread_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_waitread(3)
 * Wait until acquiring a read-lock to `self' no longer blocks */
__COMPILER_CEIDECLARE(__BLOCKING __ATTR_NONNULL((1)),void,__THROWING,__FCALL,shared_recursive_rwlock_waitread,(struct shared_recursive_rwlock *__restrict __self),{
	if (__shared_recursive_rwlock_isown(__self))
		return;
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitread)(&__self->srr_lock);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitread)
/* >> shared_recursive_rwlock_waitread(3)
 * Wait until acquiring a read-lock to `self' no longer blocks */
__LIBC __BLOCKING __ATTR_NONNULL((1)) void (__FCALL shared_recursive_rwlock_waitread)(struct shared_recursive_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_rwlock_waitread");
#elif defined(__CRT_HAVE_shared_rwlock_waitread) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitread_defined
#define __local___localdep_shared_rwlock_waitread_defined
#ifdef __CRT_HAVE_shared_rwlock_waitread
/* >> shared_rwlock_waitread(3)
 * Wait until acquiring a read-lock to `self' no longer blocks */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_rwlock_waitread,(struct shared_rwlock *__restrict __self),shared_rwlock_waitread,(__self))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitread(3)
 * Wait until acquiring a read-lock to `self' no longer blocks */
#define __localdep_shared_rwlock_waitread __LIBC_LOCAL_NAME(shared_rwlock_waitread)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitread_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitread_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_waitread(3)
 * Wait until acquiring a read-lock to `self' no longer blocks */
__LOCAL __BLOCKING __ATTR_NONNULL((1)) void (__FCALL shared_recursive_rwlock_waitread)(struct shared_recursive_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self))
		return;
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitread)(&__self->srr_lock);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite) && (defined(__CRT_HAVE_shared_rwlock_waitwrite) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitwrite_defined
#define __local___localdep_shared_rwlock_waitwrite_defined
#ifdef __CRT_HAVE_shared_rwlock_waitwrite
/* >> shared_rwlock_waitwrite(3)
 * Wait until acquiring a write-lock to `self' no longer blocks */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite,(struct shared_rwlock *__restrict __self),shared_rwlock_waitwrite,(__self))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitwrite(3)
 * Wait until acquiring a write-lock to `self' no longer blocks */
#define __localdep_shared_rwlock_waitwrite __LIBC_LOCAL_NAME(shared_rwlock_waitwrite)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitwrite_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitwrite_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_waitwrite(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks */
__COMPILER_CEIDECLARE(__BLOCKING __ATTR_NONNULL((1)),void,__THROWING,__FCALL,shared_recursive_rwlock_waitwrite,(struct shared_recursive_rwlock *__restrict __self),{
	if (__shared_recursive_rwlock_isown(__self))
		return;
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitwrite)(&__self->srr_lock);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite)
/* >> shared_recursive_rwlock_waitwrite(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks */
__LIBC __BLOCKING __ATTR_NONNULL((1)) void (__FCALL shared_recursive_rwlock_waitwrite)(struct shared_recursive_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_rwlock_waitwrite");
#elif defined(__CRT_HAVE_shared_rwlock_waitwrite) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitwrite_defined
#define __local___localdep_shared_rwlock_waitwrite_defined
#ifdef __CRT_HAVE_shared_rwlock_waitwrite
/* >> shared_rwlock_waitwrite(3)
 * Wait until acquiring a write-lock to `self' no longer blocks */
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_NONNULL((1)),__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite,(struct shared_rwlock *__restrict __self),shared_rwlock_waitwrite,(__self))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitwrite(3)
 * Wait until acquiring a write-lock to `self' no longer blocks */
#define __localdep_shared_rwlock_waitwrite __LIBC_LOCAL_NAME(shared_rwlock_waitwrite)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitwrite_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitwrite_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_waitwrite(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks */
__LOCAL __BLOCKING __ATTR_NONNULL((1)) void (__FCALL shared_recursive_rwlock_waitwrite)(struct shared_recursive_rwlock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self))
		return;
	(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitwrite)(&__self->srr_lock);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_waitread_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && (defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) || (defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitread_with_timeout_defined
#define __local___localdep_shared_rwlock_waitread_with_timeout_defined
#ifdef __CRT_HAVE_shared_rwlock_waitread_with_timeout
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitread_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitread_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitread_with_timeout_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIDECLARE(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitread_with_timeout,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),{
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitread_with_timeout)(&__self->srr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitread_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_waitread_with_timeout)(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_rwlock_waitread_with_timeout");
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitread_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitread_with_timeout,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitread_with_timeout_defined
#define __local___localdep_shared_rwlock_waitread_with_timeout_defined
#if defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitread_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitread_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitread_with_timeout_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_waitread_with_timeout)(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitread_with_timeout)(&__self->srr_lock, __abs_timeout);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && (defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) || (defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#define __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#ifdef __CRT_HAVE_shared_rwlock_waitwrite_with_timeout
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitwrite_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitwrite_with_timeout_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIDECLARE(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitwrite_with_timeout,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),{
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitwrite_with_timeout)(&__self->srr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_waitwrite_with_timeout)(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_rwlock_waitwrite_with_timeout");
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitwrite_with_timeout,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#define __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#if defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitwrite_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitwrite_with_timeout_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_waitwrite_with_timeout)(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitwrite_with_timeout)(&__self->srr_lock, __abs_timeout);
}
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_shared_recursive_rwlock_read_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__CRT_HAVE_shared_rwlock_read_with_timeout) || defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_read_with_timeout64_defined
#define __local___localdep_shared_rwlock_read_with_timeout64_defined
#ifdef __CRT_HAVE_shared_rwlock_read_with_timeout
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_read_with_timeout64)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_read_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_read_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_read_with_timeout64_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_read_with_timeout64,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_read_with_timeout,{
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_read_with_timeout64)(&__self->srr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_read_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_read_with_timeout64,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_rwlock_read_with_timeout64)
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_read_with_timeout64)(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_rwlock_read_with_timeout64");
#elif (defined(__CRT_HAVE_shared_rwlock_read_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_read_with_timeout64_defined
#define __local___localdep_shared_rwlock_read_with_timeout64_defined
#if defined(__CRT_HAVE_shared_rwlock_read_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_read_with_timeout64)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_read_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_read_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_read_with_timeout64_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_read_with_timeout64)(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_read_with_timeout64)(&__self->srr_lock, __abs_timeout);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_write_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__CRT_HAVE_shared_rwlock_write_with_timeout) || defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_write_with_timeout64_defined
#define __local___localdep_shared_rwlock_write_with_timeout64_defined
#ifdef __CRT_HAVE_shared_rwlock_write_with_timeout
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_write_with_timeout64)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_write_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_write_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_write_with_timeout64_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_write_with_timeout64,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_write_with_timeout,{
	__BOOL __result;
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_write_with_timeout64)(&__self->srr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_rwlock_setown(__self);
	return __result;
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_write_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_write_with_timeout64,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_rwlock_write_with_timeout64)
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_write_with_timeout64)(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_rwlock_write_with_timeout64");
#elif (defined(__CRT_HAVE_shared_rwlock_write_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_write_with_timeout64_defined
#define __local___localdep_shared_rwlock_write_with_timeout64_defined
#if defined(__CRT_HAVE_shared_rwlock_write_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_write_with_timeout64)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_write_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_write_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_write_with_timeout64_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_write_with_timeout64)(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	__BOOL __result;
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_write_with_timeout64)(&__self->srr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_rwlock_setown(__self);
	return __result;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_waitread_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) || defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitread_with_timeout64_defined
#define __local___localdep_shared_rwlock_waitread_with_timeout64_defined
#ifdef __CRT_HAVE_shared_rwlock_waitread_with_timeout
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitread_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitread_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitread_with_timeout64_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitread_with_timeout64,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_waitread_with_timeout,{
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitread_with_timeout64)(&__self->srr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitread_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitread_with_timeout64,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitread_with_timeout64)
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_waitread_with_timeout64)(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_rwlock_waitread_with_timeout64");
#elif (defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitread_with_timeout64_defined
#define __local___localdep_shared_rwlock_waitread_with_timeout64_defined
#if defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitread_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitread_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitread_with_timeout64_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_waitread_with_timeout64)(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitread_with_timeout64)(&__self->srr_lock, __abs_timeout);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) || defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitwrite_with_timeout64_defined
#define __local___localdep_shared_rwlock_waitwrite_with_timeout64_defined
#ifdef __CRT_HAVE_shared_rwlock_waitwrite_with_timeout
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitwrite_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitwrite_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitwrite_with_timeout64_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitwrite_with_timeout64,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_waitwrite_with_timeout,{
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitwrite_with_timeout64)(&__self->srr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitwrite_with_timeout64,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite_with_timeout64)
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LIBC __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_waitwrite_with_timeout64)(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) __CASMNAME_SAME("shared_recursive_rwlock_waitwrite_with_timeout64");
#elif (defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitwrite_with_timeout64_defined
#define __local___localdep_shared_rwlock_waitwrite_with_timeout64_defined
#if defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitwrite_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitwrite_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitwrite_with_timeout64_defined */
__NAMESPACE_LOCAL_END
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_waitwrite_with_timeout64)(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitwrite_with_timeout64)(&__self->srr_lock, __abs_timeout);
}
#endif /* ... */
#endif /* !__USE_TIME64 */
#ifdef __cplusplus
extern "C++" {
#if defined(__CRT_HAVE_shared_recursive_rwlock_read_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && (defined(__CRT_HAVE_shared_rwlock_read_with_timeout) || (defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64))))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_read_with_timeout_defined
#define __local___localdep_shared_rwlock_read_with_timeout_defined
#ifdef __CRT_HAVE_shared_rwlock_read_with_timeout
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_read_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_read_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_read_with_timeout_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_read,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_read_with_timeout,{
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_read_with_timeout)(&__self->srr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_read_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_read,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_rwlock_read_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_read,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_rwlock_read_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_read_with_timeout_defined
#define __local___localdep_shared_rwlock_read_with_timeout_defined
#if defined(__CRT_HAVE_shared_rwlock_read_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_read_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_read_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_read_with_timeout_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_read)(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_read_with_timeout)(&__self->srr_lock, __abs_timeout);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_write_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && (defined(__CRT_HAVE_shared_rwlock_write_with_timeout) || (defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64))))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_write_with_timeout_defined
#define __local___localdep_shared_rwlock_write_with_timeout_defined
#ifdef __CRT_HAVE_shared_rwlock_write_with_timeout
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_write_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_write_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_write_with_timeout_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_write,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_write_with_timeout,{
	__BOOL __result;
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_write_with_timeout)(&__self->srr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_rwlock_setown(__self);
	return __result;
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_write_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_write,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_rwlock_write_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_write,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_rwlock_write_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_write_with_timeout_defined
#define __local___localdep_shared_rwlock_write_with_timeout_defined
#if defined(__CRT_HAVE_shared_rwlock_write_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_write_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_write_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_write_with_timeout_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_write)(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	__BOOL __result;
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_write_with_timeout)(&__self->srr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_rwlock_setown(__self);
	return __result;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_waitread_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && (defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) || (defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64))))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitread_with_timeout_defined
#define __local___localdep_shared_rwlock_waitread_with_timeout_defined
#ifdef __CRT_HAVE_shared_rwlock_waitread_with_timeout
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitread_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitread_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitread_with_timeout_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitread,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_waitread_with_timeout,{
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitread_with_timeout)(&__self->srr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitread_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitread,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitread_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitread,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitread_with_timeout_defined
#define __local___localdep_shared_rwlock_waitread_with_timeout_defined
#if defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitread_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitread_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitread_with_timeout_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_waitread)(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitread_with_timeout)(&__self->srr_lock, __abs_timeout);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && (defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) || (defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64))))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#define __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#ifdef __CRT_HAVE_shared_rwlock_waitwrite_with_timeout
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitwrite_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitwrite_with_timeout_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitwrite,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_waitwrite_with_timeout,{
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitwrite_with_timeout)(&__self->srr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitwrite,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitwrite,(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_recursive_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#define __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#if defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) && (defined(__KERNEL__) || !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) && !defined(__KERNEL__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout,(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout),shared_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif defined(__KERNEL__) || defined(__CRT_HAVE_LFutexExprI) || defined(__CRT_HAVE_LFutexExprI64) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr) || defined(__CRT_HAVE_LFutexExpr64)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitwrite_with_timeout __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitwrite_with_timeout_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitwrite_with_timeout_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_waitwrite)(struct shared_recursive_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitwrite_with_timeout)(&__self->srr_lock, __abs_timeout);
}
#endif /* ... */
} /* extern "C++" */
#if defined(__USE_TIME64) && (!defined(__USE_STRUCT64_MACRO) || !defined(_TIMESPEC_MATCHES_TIMESPEC64))
extern "C++" {
#if defined(__CRT_HAVE_shared_recursive_rwlock_read_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__CRT_HAVE_shared_rwlock_read_with_timeout) || defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_read_with_timeout64_defined
#define __local___localdep_shared_rwlock_read_with_timeout64_defined
#ifdef __CRT_HAVE_shared_rwlock_read_with_timeout
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_read_with_timeout64)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_read_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_read_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_read_with_timeout64_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_read,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_read_with_timeout,{
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_read_with_timeout64)(&__self->srr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_read_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_read,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_rwlock_read_with_timeout64)
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_read,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_rwlock_read_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_shared_rwlock_read_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_read_with_timeout64_defined
#define __local___localdep_shared_rwlock_read_with_timeout64_defined
#if defined(__CRT_HAVE_shared_rwlock_read_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_read_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_read_with_timeout64)
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_read_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_read_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_read_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_read_with_timeout(3), shared_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_read_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_read_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_read_with_timeout64_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_read_with_timeout(3), shared_recursive_rwlock_read_with_timeout64(3)
 * Acquire a read-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a read-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_read)(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_read_with_timeout64)(&__self->srr_lock, __abs_timeout);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_write_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__CRT_HAVE_shared_rwlock_write_with_timeout) || defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_write_with_timeout64_defined
#define __local___localdep_shared_rwlock_write_with_timeout64_defined
#ifdef __CRT_HAVE_shared_rwlock_write_with_timeout
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_write_with_timeout64)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_write_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_write_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_write_with_timeout64_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_write,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_write_with_timeout,{
	__BOOL __result;
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_write_with_timeout64)(&__self->srr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_rwlock_setown(__self);
	return __result;
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_write_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_write,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_rwlock_write_with_timeout64)
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_write,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_rwlock_write_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_shared_rwlock_write_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_write_with_timeout64_defined
#define __local___localdep_shared_rwlock_write_with_timeout64_defined
#if defined(__CRT_HAVE_shared_rwlock_write_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_write_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_write_with_timeout64)
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_write_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_write_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_write_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_write_with_timeout(3), shared_rwlock_write_with_timeout64(3)
 * Acquire a write-lock to the given shared_rwlock.
 * @return: true:  Successfully acquired a write-lock.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_write_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_write_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_write_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_write_with_timeout64_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_write_with_timeout(3), shared_recursive_rwlock_write_with_timeout64(3)
 * Acquire a recursive write-lock to the given shared_recursive_rwlock.
 * @return: true:  Successfully acquired a recursive write-lock.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_write)(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	__BOOL __result;
	if (__shared_recursive_rwlock_isown(__self)) {
		++__self->srr_wrcnt;
		return 1;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_write_with_timeout64)(&__self->srr_lock, __abs_timeout);
	if (__result)
		__shared_recursive_rwlock_setown(__self);
	return __result;
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_waitread_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) || defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitread_with_timeout64_defined
#define __local___localdep_shared_rwlock_waitread_with_timeout64_defined
#ifdef __CRT_HAVE_shared_rwlock_waitread_with_timeout
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitread_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitread_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitread_with_timeout64_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitread,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_waitread_with_timeout,{
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitread_with_timeout64)(&__self->srr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitread_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitread,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitread_with_timeout64)
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitread,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitread_with_timeout64_defined
#define __local___localdep_shared_rwlock_waitread_with_timeout64_defined
#if defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitread_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitread_with_timeout64)
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitread_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitread_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitread_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitread_with_timeout(3), shared_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitread_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_waitread_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitread_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitread_with_timeout64_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_waitread_with_timeout(3), shared_recursive_rwlock_waitread_with_timeout64(3)
 * Wait until acquiring a read-lock to `self' no longer blocks
 * @return: true:  A read-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_waitread)(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitread_with_timeout64)(&__self->srr_lock, __abs_timeout);
}
#endif /* ... */
#if defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) || defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr))))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitwrite_with_timeout64_defined
#define __local___localdep_shared_rwlock_waitwrite_with_timeout64_defined
#ifdef __CRT_HAVE_shared_rwlock_waitwrite_with_timeout
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitwrite_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitwrite_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitwrite_with_timeout64_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitwrite,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_waitwrite_with_timeout,{
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitwrite_with_timeout64)(&__self->srr_lock, __abs_timeout);
})
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitwrite,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_recursive_rwlock_waitwrite_with_timeout64)
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,shared_recursive_rwlock_waitwrite,(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_recursive_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif (defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64) || defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
} /* extern "C++" */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_waitwrite_with_timeout64_defined
#define __local___localdep_shared_rwlock_waitwrite_with_timeout64_defined
#if defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitwrite_with_timeout,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_shared_rwlock_waitwrite_with_timeout64)
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)),__BOOL,__THROWING,__FCALL,__localdep_shared_rwlock_waitwrite_with_timeout64,(struct shared_rwlock *__restrict __self, struct timespec64 const *__abs_timeout),shared_rwlock_waitwrite_with_timeout64,(__self,__abs_timeout))
#elif defined(__CRT_HAVE_LFutexExprI64) || defined(__CRT_HAVE_LFutexExprI) || (defined(__cplusplus) && defined(__KOS__) && (defined(__CRT_HAVE_LFutexExpr64) || defined(__CRT_HAVE_LFutexExpr)))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-rwlock/shared_rwlock_waitwrite_with_timeout64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shared_rwlock_waitwrite_with_timeout(3), shared_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
#define __localdep_shared_rwlock_waitwrite_with_timeout64 __LIBC_LOCAL_NAME(shared_rwlock_waitwrite_with_timeout64)
#else /* ... */
#undef __local___localdep_shared_rwlock_waitwrite_with_timeout64_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_waitwrite_with_timeout64_defined */
__NAMESPACE_LOCAL_END
extern "C++" {
/* >> shared_recursive_rwlock_waitwrite_with_timeout(3), shared_recursive_rwlock_waitwrite_with_timeout64(3)
 * Wait until acquiring a recursive write-lock to `self' no longer blocks
 * @return: true:  A write-lock became available.
 * @return: false: The given `abs_timeout' has expired. */
__LOCAL __ATTR_WUNUSED __BLOCKING __ATTR_NONNULL((1)) __BOOL (__FCALL shared_recursive_rwlock_waitwrite)(struct shared_recursive_rwlock *__restrict __self, struct timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
	if (__shared_recursive_rwlock_isown(__self))
		return 1;
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_waitwrite_with_timeout64)(&__self->srr_lock, __abs_timeout);
}
#endif /* ... */
} /* extern "C++" */
#endif /* __USE_TIME64 && (!__USE_STRUCT64_MACRO || !_TIMESPEC_MATCHES_TIMESPEC64) */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
#define __PRIVATE_shared_recursive_rwlock_read_1      (shared_recursive_rwlock_read)
#define __PRIVATE_shared_recursive_rwlock_read_2      shared_recursive_rwlock_read_with_timeout
#define __PRIVATE_shared_recursive_rwlock_write_1     (shared_recursive_rwlock_write)
#define __PRIVATE_shared_recursive_rwlock_write_2     shared_recursive_rwlock_write_with_timeout
#define __PRIVATE_shared_recursive_rwlock_waitread_1  (shared_recursive_rwlock_waitread)
#define __PRIVATE_shared_recursive_rwlock_waitread_2  shared_recursive_rwlock_waitread_with_timeout
#define __PRIVATE_shared_recursive_rwlock_waitwrite_1 (shared_recursive_rwlock_waitwrite)
#define __PRIVATE_shared_recursive_rwlock_waitwrite_2 shared_recursive_rwlock_waitwrite_with_timeout
#define shared_recursive_rwlock_read(...)      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_read_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_rwlock_write(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_write_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_rwlock_waitread(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_waitread_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_rwlock_waitwrite(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_waitwrite_, (__VA_ARGS__))(__VA_ARGS__)
#ifdef __USE_TIME64
#define __PRIVATE_shared_recursive_rwlock_read64_1      (shared_recursive_rwlock_read)
#define __PRIVATE_shared_recursive_rwlock_read64_2      shared_recursive_rwlock_read_with_timeout64
#define __PRIVATE_shared_recursive_rwlock_write64_1     (shared_recursive_rwlock_write)
#define __PRIVATE_shared_recursive_rwlock_write64_2     shared_recursive_rwlock_write_with_timeout64
#define __PRIVATE_shared_recursive_rwlock_waitread64_1  (shared_recursive_rwlock_waitread)
#define __PRIVATE_shared_recursive_rwlock_waitread64_2  shared_recursive_rwlock_waitread_with_timeout64
#define __PRIVATE_shared_recursive_rwlock_waitwrite64_1 (shared_recursive_rwlock_waitwrite)
#define __PRIVATE_shared_recursive_rwlock_waitwrite64_2 shared_recursive_rwlock_waitwrite_with_timeout64
#define shared_recursive_rwlock_read64(...)      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_read64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_rwlock_write64(...)     __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_write64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_rwlock_waitread64(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_waitread64_, (__VA_ARGS__))(__VA_ARGS__)
#define shared_recursive_rwlock_waitwrite64(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_shared_recursive_rwlock_waitwrite64_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __USE_TIME64 */
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_SCHED_SHARED_RECURSIVE_RWLOCK_H */
