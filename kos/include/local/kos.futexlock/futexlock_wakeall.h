/* HASH CRC-32:0xa61b44d3 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_futexlock_wakeall_defined
#if defined(__CRT_HAVE_futex_wake) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex) || defined(__CRT_HAVE_futex_wakeall)
#define __local_futexlock_wakeall_defined 1
#include <bits/types.h>
#include <bits/types.h>
#include <hybrid/__atomic.h>

#include <kos/bits/futex.h>
/* Dependency: "futex_wakeall" from "kos.futex" */
#ifndef ____localdep_futex_wakeall_defined
#define ____localdep_futex_wakeall_defined 1
#if defined(__CRT_HAVE_futex_wakeall)
/* Wake all threads waiting for `*UADDR' (same as `futex_wake(uaddr, (size_t)-1)')
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_futex_wakeall,(__uintptr_t *__uaddr),futex_wakeall,(__uaddr))
#elif defined(__CRT_HAVE_futex_wake) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
#include <local/kos.futex/futex_wakeall.h>
/* Wake all threads waiting for `*UADDR' (same as `futex_wake(uaddr, (size_t)-1)')
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
#define __localdep_futex_wakeall (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_wakeall))
#else /* CUSTOM: futex_wakeall */
#undef ____localdep_futex_wakeall_defined
#endif /* futex_wakeall... */
#endif /* !____localdep_futex_wakeall_defined */

__NAMESPACE_LOCAL_BEGIN
/* A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
 * on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
 * system call when no thread is waiting on the given lock */
__LOCAL_LIBC(futexlock_wakeall) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(futexlock_wakeall))(__uintptr_t *__ulockaddr) {
#line 160 "kos/src/libc/magic/kos.futexlock.c"
	if (!(__hybrid_atomic_load(*__ulockaddr, __ATOMIC_ACQUIRE) & __LFUTEX_WAIT_LOCK_WAITERS))
		return 0; /* No waiting threads. */
	if (!(__hybrid_atomic_fetchand(*__ulockaddr, ~__LFUTEX_WAIT_LOCK_WAITERS, __ATOMIC_SEQ_CST) & __LFUTEX_WAIT_LOCK_WAITERS))
		return 0; /* No waiting threads. */
	return __localdep_futex_wakeall(__ulockaddr);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_futex_wake) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex) || defined(__CRT_HAVE_futex_wakeall) */
#endif /* !__local_futexlock_wakeall_defined */
