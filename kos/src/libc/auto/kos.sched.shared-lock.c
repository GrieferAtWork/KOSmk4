/* HASH CRC-32:0xa0493366 */
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
#ifndef GUARD_LIBC_AUTO_KOS_SCHED_SHARED_LOCK_C
#define GUARD_LIBC_AUTO_KOS_SCHED_SHARED_LOCK_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "kos.sched.shared-lock.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <kos/bits/shared-lock.h>
#include <hybrid/__atomic.h>
/* >> shared_lock_tryacquire(3)
 * Try to acquire a lock to a given `struct shared_lock *self'
 * @return: true:  success
 * @return: false: error */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_INOUT(1) bool
NOTHROW_NCX(__FCALL libc_shared_lock_tryacquire)(struct shared_lock *__restrict self) {



	unsigned int lockword;
	do {
		lockword = __hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE);
		if ((lockword & ~__SHARED_LOCK_UNLOCKED_WAITING) != 0)
			return false; /* Lock is acquired */
	} while (!__hybrid_atomic_cmpxch_weak(&self->sl_lock, lockword,
	                                      lockword ? 2 : 1, /* Set canonical lock state */
	                                      __ATOMIC_ACQUIRE, __ATOMIC_RELAXED));
	return true;

}
#include <kos/bits/shared-lock.h>
#include <hybrid/__atomic.h>
/* >> shared_lock_release_ex(3)
 * Release a lock from a given shared_lock.
 * @return: true:  A waiting thread was signaled.
 * @return: false: No thread was waiting for the lock. */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_INOUT(1) bool
NOTHROW_NCX(__FCALL libc_shared_lock_release_ex)(struct shared_lock *__restrict self) {
#ifdef __shared_lock_release_ex
	return __shared_lock_release_ex(self);
#else /* __shared_lock_release_ex */
	unsigned int lockword;
	do {
		lockword = __hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE);
		__hybrid_assertf(lockword > 0 && lockword < __SHARED_LOCK_UNLOCKED_WAITING,
		                 "Lock is not held by anyone (lockword: %#x)", lockword);
		if (lockword >= 2) {
			/* There (might be) are waiting threads */
			__hybrid_atomic_store(&self->sl_lock,
			                      __SHARED_LOCK_UNLOCKED_WAITING,
			                      __ATOMIC_RELEASE);
			if (__shared_lock_sendone(self))
				return true;

			/* Apparently, there actually aren't any waiting threads...
			 * -> Try to clear the waiting-threads-are-present flag */
			if (__hybrid_atomic_cmpxch(&self->sl_lock, __SHARED_LOCK_UNLOCKED_WAITING, 0,
			                           __ATOMIC_RELEASE, __ATOMIC_RELAXED)) {
				/* Make sure that  there really aren't  any waiting  threads
				 * (just in case a thread came by after we read the lockword
				 * above) */
				if (__shared_lock_sendall(self))
					return true;
			}
			break;
		}

		/* There are no waiting threads */
	} while (!__hybrid_atomic_cmpxch_weak(&self->sl_lock, 1, 0,
	                                      __ATOMIC_RELEASE,
	                                      __ATOMIC_RELAXED));
	/* No-one was waiting for the lock */
	return false;
#endif /* !__shared_lock_release_ex */
}
#endif /* !__KERNEL__ */
#include <kos/bits/shared-lock.h>
/* >> shared_lock_acquire(3)
 * Acquire a lock to the given shared_lock. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_lock_acquire)(struct shared_lock *__restrict self) THROWS(E_WOULDBLOCK, E_INTERRUPT) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (!__shared_lock_tryacquire(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (__shared_lock_tryacquire(self))
				goto success;
		});
		task_connect(&self->sl_sig);
		if unlikely(__shared_lock_tryacquire(self)) {
			task_disconnectall();
			break;
		}
		task_waitfor(KTIME_INFINITE);
	}
success:
	;
#else /* __KERNEL__ */
	__shared_lock_acquire_or_wait_impl(self, {
		__shared_lock_wait_impl(self);
	});
#endif /* !__KERNEL__ */
}
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_lock_acquire_with_timeout)(struct shared_lock *__restrict self,
                                                __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, E_INTERRUPT) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (!__shared_lock_tryacquire(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (__shared_lock_tryacquire(self))
				goto success;
		});
		task_connect(&self->sl_sig);
		if unlikely(__shared_lock_tryacquire(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(abs_timeout))
			return false;
	}
success:
#else /* __KERNEL__ */
	__shared_lock_acquire_or_wait_impl(self, {
		if (!__shared_lock_wait_impl_timeout(self, abs_timeout))
			return false; /* Timeout */
	});
#endif /* !__KERNEL__ */
	return true;
}
/* >> shared_lock_waitfor(3)
 * Wait for `self' to become available. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_lock_waitfor)(struct shared_lock *__restrict self) THROWS(E_WOULDBLOCK, E_INTERRUPT) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (!__shared_lock_available(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (__shared_lock_available(self))
				return;
		});
		task_connect_for_poll(&self->sl_sig);
		if unlikely(__shared_lock_available(self)) {
			task_disconnectall();
			break;
		}
		task_waitfor(KTIME_INFINITE);
	}
#else /* __KERNEL__ */
	__shared_lock_waitfor_or_wait_impl(self, {
		__shared_lock_wait_impl(self);
	});
#endif /* !__KERNEL__ */
}
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_lock_waitfor_with_timeout)(struct shared_lock *__restrict self,
                                                __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, E_INTERRUPT) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (!__shared_lock_available(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (__shared_lock_available(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_sig);
		if unlikely(__shared_lock_available(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(abs_timeout))
			return false;
	}
success:
#else /* __KERNEL__ */
	__shared_lock_waitfor_or_wait_impl(self, {
		if (!__shared_lock_wait_impl_timeout(self, abs_timeout))
			return false; /* Timeout */
	});
#endif /* !__KERNEL__ */
	return true;
}
#ifndef __KERNEL__
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_shared_lock_acquire_with_timeout64, libc_shared_lock_acquire_with_timeout);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool
(__FCALL libc_shared_lock_acquire_with_timeout64)(struct shared_lock *__restrict self,
                                                  struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, E_INTERRUPT) {
	__shared_lock_acquire_or_wait_impl(self, {
		if (!__shared_lock_wait_impl_timeout64(self, abs_timeout))
			return false; /* Timeout */
	});
	return true;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_shared_lock_waitfor_with_timeout64, libc_shared_lock_waitfor_with_timeout);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) ATTR_IN_OPT(2) bool
(__FCALL libc_shared_lock_waitfor_with_timeout64)(struct shared_lock *__restrict self,
                                                  struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, E_INTERRUPT) {
	__shared_lock_waitfor_or_wait_impl(self, {
		if (!__shared_lock_wait_impl_timeout64(self, abs_timeout))
			return false; /* Timeout */
	});
	return true;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */
#ifdef __KERNEL__
#include <hybrid/__assert.h>
#include <sched/sig.h>
/* >> shared_lock_acquire_nx(3)
 * Acquire a lock to the given shared_lock.
 * @return: true:  Successfully acquired a lock.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_lock_acquire_nx)(struct shared_lock *__restrict self) THROWS(E_WOULDBLOCK, E_INTERRUPT) {
	__hybrid_assert(!task_wasconnected());
	while (!__shared_lock_tryacquire(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (__shared_lock_tryacquire(self))
				goto success;
		});
		task_connect(&self->sl_sig);
		if unlikely(__shared_lock_tryacquire(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(KTIME_INFINITE))
			return false;
	}
success:
	return true;
}
#include <hybrid/__assert.h>
#include <sched/sig.h>
/* >> shared_lock_acquire_with_timeout_nx(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_lock_acquire_with_timeout_nx)(struct shared_lock *__restrict self,
                                                   __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, E_INTERRUPT) {
	__hybrid_assert(!task_wasconnected());
	while (!__shared_lock_tryacquire(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (__shared_lock_tryacquire(self))
				goto success;
		});
		task_connect(&self->sl_sig);
		if unlikely(__shared_lock_tryacquire(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(abs_timeout))
			return false;
	}
success:
	return true;
}
#include <hybrid/__assert.h>
#include <sched/sig.h>
/* >> shared_lock_waitfor_nx(3)
 * Wait that `self' becomes available.
 * @return: true:  The lock became available.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_lock_waitfor_nx)(struct shared_lock *__restrict self) THROWS(E_WOULDBLOCK, E_INTERRUPT) {
	__hybrid_assert(!task_wasconnected());
	while (!__shared_lock_available(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (__shared_lock_available(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_sig);
		if unlikely(__shared_lock_available(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(KTIME_INFINITE))
			return false;
	}
success:
	return true;
}
#include <hybrid/__assert.h>
#include <sched/sig.h>
/* >> shared_lock_waitfor_with_timeout_nx(3)
 * Wait that `self' becomes available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired.
 * @return: false: Preemption was disabled, and the operation would have blocked.
 * @return: false: There are pending X-RPCs that could not be serviced. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_lock_waitfor_with_timeout_nx)(struct shared_lock *__restrict self,
                                                   __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, E_INTERRUPT) {
	__hybrid_assert(!task_wasconnected());
	while (!__shared_lock_available(self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (__shared_lock_available(self))
				goto success;
		});
		task_connect_for_poll(&self->sl_sig);
		if unlikely(__shared_lock_available(self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(abs_timeout))
			return false;
	}
success:
	return true;
}
#endif /* __KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(shared_lock_tryacquire, libc_shared_lock_tryacquire);
DEFINE_PUBLIC_ALIAS(shared_lock_release_ex, libc_shared_lock_release_ex);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(shared_lock_acquire, libc_shared_lock_acquire);
DEFINE_PUBLIC_ALIAS(shared_lock_acquire_with_timeout, libc_shared_lock_acquire_with_timeout);
DEFINE_PUBLIC_ALIAS(shared_lock_waitfor, libc_shared_lock_waitfor);
DEFINE_PUBLIC_ALIAS(shared_lock_waitfor_with_timeout, libc_shared_lock_waitfor_with_timeout);
#ifndef __KERNEL__
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(shared_lock_acquire_with_timeout64, libc_shared_lock_acquire_with_timeout64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(shared_lock_waitfor_with_timeout64, libc_shared_lock_waitfor_with_timeout64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */
#ifdef __KERNEL__
DEFINE_PUBLIC_ALIAS(shared_lock_acquire_nx, libc_shared_lock_acquire_nx);
DEFINE_PUBLIC_ALIAS(shared_lock_acquire_with_timeout_nx, libc_shared_lock_acquire_with_timeout_nx);
DEFINE_PUBLIC_ALIAS(shared_lock_waitfor_nx, libc_shared_lock_waitfor_nx);
DEFINE_PUBLIC_ALIAS(shared_lock_waitfor_with_timeout_nx, libc_shared_lock_waitfor_with_timeout_nx);
#endif /* __KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_KOS_SCHED_SHARED_LOCK_C */
