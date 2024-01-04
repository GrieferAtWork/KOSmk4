/* HASH CRC-32:0x2a75e6d5 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_shared_lock_tryacquire_defined
#define __local_shared_lock_tryacquire_defined
#include <__crt.h>
#include <kos/bits/shared-lock.h>
#include <hybrid/__atomic.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(shared_lock_tryacquire) __ATTR_INOUT(1) __BOOL
__NOTHROW_NCX(__FCALL __LIBC_LOCAL_NAME(shared_lock_tryacquire))(struct shared_lock *__restrict __self) {
#ifdef __KERNEL__
	return __shared_lock_tryacquire(__self);
#else /* __KERNEL__ */
	unsigned int __lockword;
	do {
		__lockword = __hybrid_atomic_load(&__self->sl_lock, __ATOMIC_ACQUIRE);
		if ((__lockword & ~__SHARED_LOCK_UNLOCKED_WAITING) != 0)
			return 0; /* Lock is acquired */
	} while (!__hybrid_atomic_cmpxch_weak(&__self->sl_lock, __lockword,
	                                      __lockword ? 2 : 1, /* Set canonical lock state */
	                                      __ATOMIC_ACQUIRE, __ATOMIC_RELAXED));
	return 1;
#endif /* !__KERNEL__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shared_lock_tryacquire_defined
#define __local___localdep_shared_lock_tryacquire_defined
#define __localdep_shared_lock_tryacquire __LIBC_LOCAL_NAME(shared_lock_tryacquire)
#endif /* !__local___localdep_shared_lock_tryacquire_defined */
#endif /* !__local_shared_lock_tryacquire_defined */
