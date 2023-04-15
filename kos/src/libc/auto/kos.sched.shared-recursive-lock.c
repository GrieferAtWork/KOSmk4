/* HASH CRC-32:0x39200d53 */
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
#ifndef GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RECURSIVE_LOCK_C
#define GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RECURSIVE_LOCK_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "kos.sched.shared-recursive-lock.h"
#include "kos.sched.shared-lock.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/__atomic.h>
/* >> shared_recursive_lock_tryacquire(3)
 * Try to acquire a recursive lock to `self' */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __NOBLOCK ATTR_INOUT(1) bool
NOTHROW(__FCALL libc_shared_recursive_lock_tryacquire)(struct shared_recursive_lock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
#ifdef __shared_lock_tryacquire
	if (__shared_lock_tryacquire(&self->sr_lock))
#else /* __shared_lock_tryacquire */
	if (libc_shared_lock_tryacquire(&self->sr_lock))
#endif /* !__shared_lock_tryacquire */
	{
		__shared_recursive_lock_setown(self);
		return true;
	}
	if (__shared_recursive_lock_isown(self)) {
		++self->sr_rcnt;
		return true;
	}
	return false;
}
#include <hybrid/__atomic.h>
#include <hybrid/__assert.h>
#include <kos/asm/futex.h>
/* >> shared_recursive_lock_release_ex(3)
 * Release a recursive  lock from  `self'
 * @return: true:  The lock has become free.
 * @return: false: You're still holding the lock */
INTERN ATTR_SECTION(".text.crt.sched.futex") __NOBLOCK ATTR_INOUT(1) bool
NOTHROW(__FCALL libc_shared_recursive_lock_release_ex)(struct shared_recursive_lock *__restrict self) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	__COMPILER_BARRIER();
	__hybrid_assertf(self->sr_lock.sl_lock != 0, "Lock isn't acquired");
	__hybrid_assertf(__shared_recursive_lock_isown(self), "You're not the owner of this lock");
	if (self->sr_rcnt == 0) {
		self->sr_owner = __SHARED_RECURSIVE_LOCK_BADTID;
#ifdef __shared_lock_release_ex
		return __shared_lock_release_ex(&self->sr_lock);
#else /* __shared_lock_release_ex */
		return libc_shared_lock_release_ex(&self->sr_lock);
#endif /* !__shared_lock_release_ex */
	}
	--self->sr_rcnt;
	return false;
}
/* >> shared_recursive_lock_acquire(3)
 * Acquire a recursive lock to the given shared_recursive_lock. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_recursive_lock_acquire)(struct shared_recursive_lock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_lock_isown(self)) {
		++self->sr_rcnt; /* Recursive aquisition */
		return;
	}

	/* Lock the underlying (non-recursive) shared-lock */
	libc_shared_lock_acquire(&self->sr_lock);

	/* We're now the owner of `self' */
	__shared_recursive_lock_setown(self);
}
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_recursive_lock_acquire_with_timeout)(struct shared_recursive_lock *__restrict self,
                                                          __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	bool result;
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_lock_isown(self)) {
		++self->sr_rcnt; /* Recursive aquisition */
		return true;
	}

	/* Lock the underlying (non-recursive) shared-lock */
	result = libc_shared_lock_acquire_with_timeout(&self->sr_lock, abs_timeout);
	if (result) {
		/* We're now the owner of `self' */
		__shared_recursive_lock_setown(self);
	}
	return result;
}
/* >> shared_recursive_lock_waitfor(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_recursive_lock_waitfor)(struct shared_recursive_lock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_lock_isown(self))
		return;
	libc_shared_lock_waitfor(&self->sr_lock);
}
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_recursive_lock_waitfor_with_timeout)(struct shared_recursive_lock *__restrict self,
                                                          __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_lock_isown(self))
		return true;
	return libc_shared_lock_waitfor_with_timeout(&self->sr_lock, abs_timeout);
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_shared_recursive_lock_acquire_with_timeout64, libc_shared_recursive_lock_acquire_with_timeout);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> shared_recursive_lock_acquire_with_timeout(3), shared_recursive_lock_acquire_with_timeout64(3)
 * Acquire a recursive lock to the given shared_recursive_lock.
 * @return: true:  Successfully acquired a recursive lock.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool
(__FCALL libc_shared_recursive_lock_acquire_with_timeout64)(struct shared_recursive_lock *__restrict self,
                                                            struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	bool result;
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_lock_isown(self)) {
		++self->sr_rcnt; /* Recursive aquisition */
		return true;
	}

	/* Lock the underlying (non-recursive) shared-lock */
	result = libc_shared_lock_acquire_with_timeout64(&self->sr_lock, abs_timeout);
	if (result) {
		/* We're now the owner of `self' */
		__shared_recursive_lock_setown(self);
	}
	return result;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_shared_recursive_lock_waitfor_with_timeout64, libc_shared_recursive_lock_waitfor_with_timeout);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> shared_recursive_lock_waitfor_with_timeout(3), shared_recursive_lock_waitfor_with_timeout64(3)
 * Wait until acquiring a recursive lock to `self' no longer blocks
 * @return: true:  A lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool
(__FCALL libc_shared_recursive_lock_waitfor_with_timeout64)(struct shared_recursive_lock *__restrict self,
                                                            struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__COMPILER_WORKAROUND_GCC_105689(self);
	if (__shared_recursive_lock_isown(self))
		return true;
	return libc_shared_lock_waitfor_with_timeout64(&self->sr_lock, abs_timeout);
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(shared_recursive_lock_tryacquire, libc_shared_recursive_lock_tryacquire);
DEFINE_PUBLIC_ALIAS(shared_recursive_lock_release_ex, libc_shared_recursive_lock_release_ex);
DEFINE_PUBLIC_ALIAS(shared_recursive_lock_acquire, libc_shared_recursive_lock_acquire);
DEFINE_PUBLIC_ALIAS(shared_recursive_lock_acquire_with_timeout, libc_shared_recursive_lock_acquire_with_timeout);
DEFINE_PUBLIC_ALIAS(shared_recursive_lock_waitfor, libc_shared_recursive_lock_waitfor);
DEFINE_PUBLIC_ALIAS(shared_recursive_lock_waitfor_with_timeout, libc_shared_recursive_lock_waitfor_with_timeout);
DEFINE_PUBLIC_ALIAS(shared_recursive_lock_acquire_with_timeout64, libc_shared_recursive_lock_acquire_with_timeout64);
DEFINE_PUBLIC_ALIAS(shared_recursive_lock_waitfor_with_timeout64, libc_shared_recursive_lock_waitfor_with_timeout64);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_KOS_SCHED_SHARED_RECURSIVE_LOCK_C */
