/* HASH CRC-32:0x9b4186e */
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
#ifndef __local_shared_lock_release_ex_defined
#define __local_shared_lock_release_ex_defined
#include <__crt.h>
#include <kos/bits/shared-lock.h>
#if defined(__shared_lock_release_ex) || (defined(__shared_lock_sendone) && defined(__shared_lock_sendall))
#include <hybrid/__atomic.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(shared_lock_release_ex) __ATTR_INOUT(1) __BOOL
__NOTHROW_NCX(__FCALL __LIBC_LOCAL_NAME(shared_lock_release_ex))(struct shared_lock *__restrict __self) {
#ifdef __shared_lock_release_ex
	return __shared_lock_release_ex(__self);
#else /* __shared_lock_release_ex */
	unsigned int __lockword;
	do {
		__lockword = __hybrid_atomic_load(&__self->sl_lock, __ATOMIC_ACQUIRE);
		__hybrid_assertf(__lockword > 0 && __lockword < __SHARED_LOCK_UNLOCKED_WAITING,
		                 "Lock is not held by anyone (lockword: %#x)", __lockword);
		if (__lockword >= 2) {
			/* There (might be) are waiting threads */
			__hybrid_atomic_store(&__self->sl_lock,
			                      __SHARED_LOCK_UNLOCKED_WAITING,
			                      __ATOMIC_RELEASE);
			if (__shared_lock_sendone(__self))
				return 1;

			/* Apparently, there actually aren't any waiting threads...
			 * -> Try to clear the waiting-threads-are-present flag */
			if (__hybrid_atomic_cmpxch(&__self->sl_lock, __SHARED_LOCK_UNLOCKED_WAITING, 0,
			                           __ATOMIC_RELEASE, __ATOMIC_RELAXED)) {
				/* Make sure that  there really aren't  any waiting  threads
				 * (just in case a thread came by after we read the lockword
				 * above) */
				if (__shared_lock_sendall(__self))
					return 1;
			}
			break;
		}

		/* There are no waiting threads */
	} while (!__hybrid_atomic_cmpxch_weak(&__self->sl_lock, 1, 0,
	                                      __ATOMIC_RELEASE,
	                                      __ATOMIC_RELAXED));
	/* No-one was waiting for the lock */
	return 0;
#endif /* !__shared_lock_release_ex */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shared_lock_release_ex_defined
#define __local___localdep_shared_lock_release_ex_defined
#define __localdep_shared_lock_release_ex __LIBC_LOCAL_NAME(shared_lock_release_ex)
#endif /* !__local___localdep_shared_lock_release_ex_defined */
#else /* __shared_lock_release_ex || (__shared_lock_sendone && __shared_lock_sendall) */
#undef __local_shared_lock_release_ex_defined
#endif /* !__shared_lock_release_ex && (!__shared_lock_sendone || !__shared_lock_sendall) */
#endif /* !__local_shared_lock_release_ex_defined */
