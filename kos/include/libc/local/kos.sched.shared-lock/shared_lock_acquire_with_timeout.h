/* HASH CRC-32:0xc16fe46f */
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
#ifndef __local_shared_lock_acquire_with_timeout_defined
#define __local_shared_lock_acquire_with_timeout_defined
#include <__crt.h>
#include <kos/bits/shared-lock.h>
#if defined(__KERNEL__) || defined(__shared_lock_wait_timeout)
#include <kos/anno.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(shared_lock_acquire_with_timeout) __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL
(__FCALL __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout))(struct shared_lock *__restrict __self, __shared_lock_timespec __abs_timeout) __THROWS(__E_WOULDBLOCK, ...) {
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
		if (!task_waitfor(__abs_timeout))
			return 0;
	}
__success:
#else /* __KERNEL__ */
	while (__hybrid_atomic_fetchinc(__self->sl_lock, __ATOMIC_ACQUIRE) != 0) {
		__hybrid_atomic_store(__self->sl_lock, 2, __ATOMIC_SEQ_CST);
		if (!__shared_lock_wait_timeout(__self, __abs_timeout))
			return 0;
	}
#endif /* !__KERNEL__ */
	__COMPILER_BARRIER();
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shared_lock_acquire_with_timeout_defined
#define __local___localdep_shared_lock_acquire_with_timeout_defined
#define __localdep_shared_lock_acquire_with_timeout __LIBC_LOCAL_NAME(shared_lock_acquire_with_timeout)
#endif /* !__local___localdep_shared_lock_acquire_with_timeout_defined */
#else /* __KERNEL__ || __shared_lock_wait_timeout */
#undef __local_shared_lock_acquire_with_timeout_defined
#endif /* !__KERNEL__ && !__shared_lock_wait_timeout */
#endif /* !__local_shared_lock_acquire_with_timeout_defined */
