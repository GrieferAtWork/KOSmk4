/* HASH CRC-32:0x79445411 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_shared_lock_acquire_defined
#define __local_shared_lock_acquire_defined
#include <__crt.h>
#include <kos/bits/shared-lock.h>
#if defined(__KERNEL__) || defined(__shared_lock_wait_impl)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(shared_lock_acquire) __BLOCKING __ATTR_INOUT(1) void
(__FCALL __LIBC_LOCAL_NAME(shared_lock_acquire))(struct shared_lock *__restrict __self) __THROWS(E_WOULDBLOCK, E_INTERRUPT) {
#ifdef __KERNEL__
	__hybrid_assert(!task_wasconnected());
	while (!__shared_lock_tryacquire(__self)) {
		TASK_POLL_BEFORE_CONNECT({
			if (__shared_lock_tryacquire(__self))
				goto __success;
		});
		task_connect(&__self->sl_sig);
		if __unlikely(__shared_lock_tryacquire(__self)) {
			task_disconnectall();
			break;
		}
		task_waitfor(KTIME_INFINITE);
	}
__success:
	;
#else /* __KERNEL__ */
	__shared_lock_acquire_or_wait_impl(__self, {
		__shared_lock_wait_impl(__self);
	});
#endif /* !__KERNEL__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shared_lock_acquire_defined
#define __local___localdep_shared_lock_acquire_defined
#define __localdep_shared_lock_acquire __LIBC_LOCAL_NAME(shared_lock_acquire)
#endif /* !__local___localdep_shared_lock_acquire_defined */
#else /* __KERNEL__ || __shared_lock_wait_impl */
#undef __local_shared_lock_acquire_defined
#endif /* !__KERNEL__ && !__shared_lock_wait_impl */
#endif /* !__local_shared_lock_acquire_defined */
