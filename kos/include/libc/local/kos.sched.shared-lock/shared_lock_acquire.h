/* HASH CRC-32:0xf29ed64 */
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
#ifndef __local_shared_lock_acquire_defined
#define __local_shared_lock_acquire_defined
#include <__crt.h>
#include <kos/bits/shared-lock.h>
#if defined(__KERNEL__) || defined(__shared_lock_wait)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(shared_lock_acquire) __BLOCKING __ATTR_INOUT(1) void
(__FCALL __LIBC_LOCAL_NAME(shared_lock_acquire))(struct shared_lock *__restrict __self) __THROWS(__E_WOULDBLOCK, ...) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (__hybrid_atomic_xch(__self->sl_lock, 1, __ATOMIC_ACQUIRE) != 0) {
		TASK_POLL_BEFORE_CONNECT({
			if (__hybrid_atomic_xch(__self->sl_lock, 1, __ATOMIC_ACQUIRE) == 0)
				goto __success;
		});
		task_connect(&__self->sl_sig);
		if __unlikely(__hybrid_atomic_xch(__self->sl_lock, 1, __ATOMIC_ACQUIRE) == 0) {
			task_disconnectall();
			break;
		}
		task_waitfor(KTIME_INFINITE);
	}
__success:
#else /* __KERNEL__ */
	unsigned int __lockword;
__again:
	/* NOTE: If there suddenly were more than UINT_MAX threads trying to acquire the same
	 *       lock  all at the same time, this could overflow. -- But I think that's not a
	 *       thing that could ever happen... */
	while ((__lockword = __hybrid_atomic_fetchinc(__self->sl_lock, __ATOMIC_ACQUIRE)) != 0) {
		if __unlikely(__lockword != 1) {
			/* This can happen if multiple threads try to acquire the lock at the same time.
			 * In  this case, we must normalize the  lock-word back to `state = 2', but only
			 * for as long as the lock itself remains acquired by some-one.
			 *
			 * This code right here is also carefully written such that it always does
			 * the  right thing, no  matter how many  threads execute it concurrently. */
			++__lockword;
			while (!__hybrid_atomic_cmpxch(__self->sl_lock, __lockword, 2,
			                               __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
				__lockword = __hybrid_atomic_load(__self->sl_lock, __ATOMIC_ACQUIRE);
				if __unlikely(__lockword == 0)
					goto __again; /* Lock suddenly become available */
				if __unlikely(__lockword == 2)
					break; /* Some other thread did the normalize for us! */
			}
		}
		__shared_lock_wait(__self);
	}
#endif /* !__KERNEL__ */
	__COMPILER_BARRIER();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shared_lock_acquire_defined
#define __local___localdep_shared_lock_acquire_defined
#define __localdep_shared_lock_acquire __LIBC_LOCAL_NAME(shared_lock_acquire)
#endif /* !__local___localdep_shared_lock_acquire_defined */
#else /* __KERNEL__ || __shared_lock_wait */
#undef __local_shared_lock_acquire_defined
#endif /* !__KERNEL__ && !__shared_lock_wait */
#endif /* !__local_shared_lock_acquire_defined */
