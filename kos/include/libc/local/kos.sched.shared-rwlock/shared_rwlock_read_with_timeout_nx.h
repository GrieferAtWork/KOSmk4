/* HASH CRC-32:0x4da1e700 */
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
#ifndef __local_shared_rwlock_read_with_timeout_nx_defined
#define __local_shared_rwlock_read_with_timeout_nx_defined
#include <__crt.h>
#ifdef __KERNEL__
#include <kos/anno.h>
#include <kos/bits/shared-rwlock.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_tryread_defined
#define __local___localdep_shared_rwlock_tryread_defined
#ifdef __CRT_HAVE_shared_rwlock_tryread
__NAMESPACE_LOCAL_END
#include <hybrid/__atomic.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT(1),__BOOL,__NOTHROW,__FCALL,__localdep_shared_rwlock_tryread,(struct shared_rwlock *__restrict __self),shared_rwlock_tryread,{
	__UINTPTR_TYPE__ __temp;
	__COMPILER_WORKAROUND_GCC_105689(__self);
	do {
		__temp = __hybrid_atomic_load(&__self->sl_lock, __ATOMIC_ACQUIRE);
		if (__temp == (__UINTPTR_TYPE__)-1)
			return 0;
		__hybrid_assert(__temp != (__UINTPTR_TYPE__)-2);
	} while (!__hybrid_atomic_cmpxch_weak(&__self->sl_lock, __temp, __temp + 1,
	                                      __ATOMIC_ACQUIRE, __ATOMIC_RELAXED));
	__COMPILER_READ_BARRIER();
	return 1;
})
#else /* __CRT_HAVE_shared_rwlock_tryread */
__NAMESPACE_LOCAL_END
#include <hybrid/__atomic.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT(1) __BOOL __NOTHROW(__FCALL __localdep_shared_rwlock_tryread)(struct shared_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __temp;
	__COMPILER_WORKAROUND_GCC_105689(__self);
	do {
		__temp = __hybrid_atomic_load(&__self->sl_lock, __ATOMIC_ACQUIRE);
		if (__temp == (__UINTPTR_TYPE__)-1)
			return 0;
		__hybrid_assert(__temp != (__UINTPTR_TYPE__)-2);
	} while (!__hybrid_atomic_cmpxch_weak(&__self->sl_lock, __temp, __temp + 1,
	                                      __ATOMIC_ACQUIRE, __ATOMIC_RELAXED));
	__COMPILER_READ_BARRIER();
	return 1;
}
#endif /* !__CRT_HAVE_shared_rwlock_tryread */
#endif /* !__local___localdep_shared_rwlock_tryread_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__assert.h>
#include <sched/sig.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(shared_rwlock_read_with_timeout_nx) __ATTR_WUNUSED __BLOCKING __ATTR_INOUT(1) __BOOL
(__FCALL __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout_nx))(struct shared_rwlock *__restrict __self, __shared_rwlock_timespec __abs_timeout) __THROWS(E_WOULDBLOCK, ...) {
	__hybrid_assert(!task_wasconnected());
	while (!(__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_tryread)(__self)) {
		TASK_POLL_BEFORE_CONNECT({
			if ((__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_tryread)(__self))
				goto __success;
		});
		task_connect(&__self->sl_rdwait);
		if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_tryread)(__self)) {
			task_disconnectall();
			break;
		}
		if (!task_waitfor_nx(__abs_timeout))
			return 0;
	}
__success:
	__COMPILER_READ_BARRIER();
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shared_rwlock_read_with_timeout_nx_defined
#define __local___localdep_shared_rwlock_read_with_timeout_nx_defined
#define __localdep_shared_rwlock_read_with_timeout_nx __LIBC_LOCAL_NAME(shared_rwlock_read_with_timeout_nx)
#endif /* !__local___localdep_shared_rwlock_read_with_timeout_nx_defined */
#else /* __KERNEL__ */
#undef __local_shared_rwlock_read_with_timeout_nx_defined
#endif /* !__KERNEL__ */
#endif /* !__local_shared_rwlock_read_with_timeout_nx_defined */
