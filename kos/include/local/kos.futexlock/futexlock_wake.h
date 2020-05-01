/* HASH CRC-32:0xeb0a7e3f */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_futexlock_wake_defined
#if defined(__CRT_HAVE_lfutex) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_futex_wakemask)
#define __local_futexlock_wake_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <bits/types.h>
#include <hybrid/__atomic.h>

#include <kos/bits/futex.h>
/* Dependency: "futex_wakemask" from "kos.futex" */
#ifndef ____localdep_futex_wakemask_defined
#define ____localdep_futex_wakemask_defined 1
#ifdef __CRT_HAVE_futex_wakemask
/* Similar to `futex_wake()', however once there are no more threads that
 * can be awoken, perform the following operation: `*uaddr = (*uaddr & mask_and) | mask_or'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_futex_wakemask,(__uintptr_t *__uaddr, __SIZE_TYPE__ __max_wake, __uintptr_t __mask_and, __uintptr_t __mask_or),futex_wakemask,(__uaddr,__max_wake,__mask_and,__mask_or))
#elif defined(__CRT_HAVE_lfutex) || defined(__CRT_HAVE_lfutex64)
#include <local/kos.futex/futex_wakemask.h>
/* Similar to `futex_wake()', however once there are no more threads that
 * can be awoken, perform the following operation: `*uaddr = (*uaddr & mask_and) | mask_or'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
#define __localdep_futex_wakemask (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_wakemask))
#else /* CUSTOM: futex_wakemask */
#undef ____localdep_futex_wakemask_defined
#endif /* futex_wakemask... */
#endif /* !____localdep_futex_wakemask_defined */

__NAMESPACE_LOCAL_BEGIN
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
__LOCAL_LIBC(futexlock_wake) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(futexlock_wake))(__uintptr_t *__ulockaddr,
                                                            __SIZE_TYPE__ __max_wake) {
#line 149 "kos/src/libc/magic/kos.futexlock.c"
	if (!(__hybrid_atomic_load(*__ulockaddr, __ATOMIC_ACQUIRE) & __LFUTEX_WAIT_LOCK_WAITERS))
		return 0; /* No waiting threads. */
	return __localdep_futex_wakemask(&__ulockaddr, 1, (__uintptr_t)~__LFUTEX_WAIT_LOCK_WAITERS, 0);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_lfutex || __CRT_HAVE_lfutex64 || __CRT_HAVE_futex_wakemask */
#endif /* !__local_futexlock_wake_defined */
