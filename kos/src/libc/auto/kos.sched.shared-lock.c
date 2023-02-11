/* HASH CRC-32:0xa195fef8 */
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

#include <kos/bits/shared-lock.h>
/* >> shared_lock_acquire(3)
 * Acquire a lock to the given shared_lock. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_lock_acquire)(struct shared_lock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_xch(&self->sl_lock, 1, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_xch(&self->sl_lock, 1, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		task_connect(&self->sl_sig);
		if unlikely(__hybrid_atomic_xch(&self->sl_lock, 1, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		task_waitfor(KTIME_INFINITE);
	}
success:
#else /* __KERNEL__ */
	unsigned int lockword;
again:
	/* NOTE: If there suddenly were more than UINT_MAX threads trying to acquire the same
	 *       lock  all at the same time, this could overflow. -- But I think that's not a
	 *       thing that could ever happen... */
	while ((lockword = __hybrid_atomic_fetchinc(&self->sl_lock, __ATOMIC_ACQUIRE)) != 0) {
		if unlikely(lockword != 1) {
			/* This can happen if multiple threads try to acquire the lock at the same time.
			 * In  this case, we must normalize the  lock-word back to `state = 2', but only
			 * for as long as the lock itself remains acquired by some-one.
			 *
			 * This code right here is also carefully written such that it always does
			 * the  right thing, no  matter how many  threads execute it concurrently. */
			++lockword;
			while (!__hybrid_atomic_cmpxch(&self->sl_lock, lockword, 2,
			                               __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
				lockword = __hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE);
				if unlikely(lockword == 0)
					goto again; /* Lock suddenly become available */
				if unlikely(lockword == 2)
					break; /* Some other thread did the normalize for us! */
			}
		}
		__shared_lock_wait(self);
	}
#endif /* !__KERNEL__ */
	COMPILER_BARRIER();
}
/* >> shared_lock_acquire_with_timeout(3), shared_lock_acquire_with_timeout64(3)
 * Acquire a lock to the given shared_lock, and block until `abs_timeout' or indefinitely.
 * @return: true:  Successfully acquired a lock.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_lock_acquire_with_timeout)(struct shared_lock *__restrict self,
                                                __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_xch(&self->sl_lock, 1, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_xch(&self->sl_lock, 1, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		task_connect(&self->sl_sig);
		if unlikely(__hybrid_atomic_xch(&self->sl_lock, 1, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(abs_timeout))
			return false;
	}
success:
#else /* __KERNEL__ */
	unsigned int lockword;
again:
	/* NOTE: If there suddenly were more than UINT_MAX threads trying to acquire the same
	 *       lock  all at the same time, this could overflow. -- But I think that's not a
	 *       thing that could ever happen... */
	while ((lockword = __hybrid_atomic_fetchinc(&self->sl_lock, __ATOMIC_ACQUIRE)) != 0) {
		if unlikely(lockword != 1) {
			/* This can happen if multiple threads try to acquire the lock at the same time.
			 * In  this case, we must normalize the  lock-word back to `state = 2', but only
			 * for as long as the lock itself remains acquired by some-one.
			 *
			 * This code right here is also carefully written such that it always does
			 * the  right thing, no  matter how many  threads execute it concurrently. */
			++lockword;
			while (!__hybrid_atomic_cmpxch(&self->sl_lock, lockword, 2,
			                               __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
				lockword = __hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE);
				if unlikely(lockword == 0)
					goto again; /* Lock suddenly become available */
				if unlikely(lockword == 2)
					break; /* Some other thread did the normalize for us! */
			}
		}
		if (!__shared_lock_wait_timeout(self, abs_timeout))
			return false; /* Timeout */
	}
#endif /* !__KERNEL__ */
	COMPILER_BARRIER();
	return true;
}
/* >> shared_lock_waitfor(3)
 * Wait for `self' to become available. */
INTERN ATTR_SECTION(".text.crt.sched.futex") __BLOCKING ATTR_INOUT(1) void
(__FCALL libc_shared_lock_waitfor)(struct shared_lock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0)
				return;
		});
		task_connect_for_poll(&self->sl_sig);
		if unlikely(__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		task_waitfor(KTIME_INFINITE);
	}
#else /* __KERNEL__ */
	if (__hybrid_atomic_cmpxch(&self->sl_lock, 1, 2, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE))
		__shared_lock_wait(self);
#endif /* !__KERNEL__ */
}
/* >> shared_lock_waitfor_with_timeout(3), shared_lock_waitfor_with_timeout64(3)
 * Wait for `self' to become available, blocking until `abs_timeout' or indefinitely.
 * @return: true:  The lock became available.
 * @return: false: The given `abs_timeout' has expired. */
INTERN ATTR_SECTION(".text.crt.sched.futex") WUNUSED __BLOCKING ATTR_INOUT(1) bool
(__FCALL libc_shared_lock_waitfor_with_timeout)(struct shared_lock *__restrict self,
                                                __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		task_connect_for_poll(&self->sl_sig);
		if unlikely(__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor(abs_timeout))
			return false;
	}
success:
#else /* __KERNEL__ */
	if (__hybrid_atomic_cmpxch(&self->sl_lock, 1, 2, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE))
		return __shared_lock_wait_timeout(self, abs_timeout);
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
                                                  struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	unsigned int lockword;
again:
	/* NOTE: If there suddenly were more than UINT_MAX threads trying to acquire the same
	 *       lock  all at the same time, this could overflow. -- But I think that's not a
	 *       thing that could ever happen... */
	while ((lockword = __hybrid_atomic_fetchinc(&self->sl_lock, __ATOMIC_ACQUIRE)) != 0) {
		if unlikely(lockword != 1) {
			/* This can happen if multiple threads try to acquire the lock at the same time.
			 * In  this case, we must normalize the  lock-word back to `state = 2', but only
			 * for as long as the lock itself remains acquired by some-one.
			 *
			 * This code right here is also carefully written such that it always does
			 * the  right thing, no  matter how many  threads execute it concurrently. */
			++lockword;
			while (!__hybrid_atomic_cmpxch(&self->sl_lock, lockword, 2,
			                               __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
				lockword = __hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE);
				if unlikely(lockword == 0)
					goto again; /* Lock suddenly become available */
				if unlikely(lockword == 2)
					break; /* Some other thread did the normalize for us! */
			}
		}
		if (!__shared_lock_wait_timeout64(self, abs_timeout))
			return false; /* Timeout */
	}
	COMPILER_BARRIER();
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
                                                  struct timespec64 const *abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	if (__hybrid_atomic_cmpxch(&self->sl_lock, 1, 2, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE))
		return __shared_lock_wait_timeout64(self, abs_timeout);
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
(__FCALL libc_shared_lock_acquire_nx)(struct shared_lock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_xch(&self->sl_lock, 1, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_xch(&self->sl_lock, 1, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		task_connect(&self->sl_sig);
		if unlikely(__hybrid_atomic_xch(&self->sl_lock, 1, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(KTIME_INFINITE))
			return false;
	}
success:
	COMPILER_BARRIER();
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
                                                   __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_xch(&self->sl_lock, 1, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_xch(&self->sl_lock, 1, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		task_connect(&self->sl_sig);
		if unlikely(__hybrid_atomic_xch(&self->sl_lock, 1, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(abs_timeout))
			return false;
	}
success:
	COMPILER_BARRIER();
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
(__FCALL libc_shared_lock_waitfor_nx)(struct shared_lock *__restrict self) THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		task_connect_for_poll(&self->sl_sig);
		if unlikely(__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(KTIME_INFINITE))
			return false;
	}
success:
	COMPILER_BARRIER();
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
                                                   __shared_lock_timespec abs_timeout) THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0)
				goto success;
		});
		task_connect_for_poll(&self->sl_sig);
		if unlikely(__hybrid_atomic_load(&self->sl_lock, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(abs_timeout))
			return false;
	}
success:
	COMPILER_BARRIER();
	return true;
}
#endif /* __KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__spin_lock, libc_shared_lock_acquire);
DEFINE_PUBLIC_ALIAS(__mutex_lock, libc_shared_lock_acquire);
DEFINE_PUBLIC_ALIAS(__mutex_lock_solid, libc_shared_lock_acquire);
DEFINE_PUBLIC_ALIAS(mutex_wait_lock, libc_shared_lock_acquire);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(shared_lock_acquire, libc_shared_lock_acquire);
DEFINE_PUBLIC_ALIAS(shared_lock_acquire_with_timeout, libc_shared_lock_acquire_with_timeout);
DEFINE_PUBLIC_ALIAS(shared_lock_waitfor, libc_shared_lock_waitfor);
DEFINE_PUBLIC_ALIAS(shared_lock_waitfor_with_timeout, libc_shared_lock_waitfor_with_timeout);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(shared_lock_acquire_with_timeout64, libc_shared_lock_acquire_with_timeout64);
DEFINE_PUBLIC_ALIAS(shared_lock_waitfor_with_timeout64, libc_shared_lock_waitfor_with_timeout64);
#endif /* !__KERNEL__ */
#ifdef __KERNEL__
DEFINE_PUBLIC_ALIAS(shared_lock_acquire_nx, libc_shared_lock_acquire_nx);
DEFINE_PUBLIC_ALIAS(shared_lock_acquire_with_timeout_nx, libc_shared_lock_acquire_with_timeout_nx);
DEFINE_PUBLIC_ALIAS(shared_lock_waitfor_nx, libc_shared_lock_waitfor_nx);
DEFINE_PUBLIC_ALIAS(shared_lock_waitfor_with_timeout_nx, libc_shared_lock_waitfor_with_timeout_nx);
#endif /* __KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_KOS_SCHED_SHARED_LOCK_C */
