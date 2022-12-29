/* HASH CRC-32:0x2c946bba */
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
#ifndef __local_shared_lock_acquire_with_timeout64_defined
#define __local_shared_lock_acquire_with_timeout64_defined
#include <__crt.h>
#include <kos/bits/shared-lock.h>
#ifdef __shared_lock_wait_timeout64
#include <kos/anno.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(shared_lock_acquire_with_timeout64) __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __ATTR_IN_OPT(2) __BOOL
(__FCALL __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout64))(struct shared_lock *__restrict __self, struct __timespec64 const *__abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
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
		if (!__shared_lock_wait_timeout64(__self, __abs_timeout))
			return 0; /* Timeout */
	}
	__COMPILER_BARRIER();
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shared_lock_acquire_with_timeout64_defined
#define __local___localdep_shared_lock_acquire_with_timeout64_defined
#define __localdep_shared_lock_acquire_with_timeout64 __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout64)
#endif /* !__local___localdep_shared_lock_acquire_with_timeout64_defined */
#else /* __shared_lock_wait_timeout64 */
#undef __local_shared_lock_acquire_with_timeout64_defined
#endif /* !__shared_lock_wait_timeout64 */
#endif /* !__local_shared_lock_acquire_with_timeout64_defined */
