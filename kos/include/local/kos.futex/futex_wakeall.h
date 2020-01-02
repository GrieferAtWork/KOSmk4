/* HASH CRC-32:0x3434a8af */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_futex_wakeall_defined
#if defined(__CRT_HAVE_lfutex) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_futex_wake)
#define __local_futex_wakeall_defined 1
#include <bits/types.h>
#include <bits/types.h>
/* Dependency: "futex_wake" from "kos.futex" */
#ifndef ____localdep_futex_wake_defined
#define ____localdep_futex_wake_defined 1
#ifdef __CRT_HAVE_futex_wake
/* Wake up to `MAX_WAKE' threads waiting for `*UADDR'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_futex_wake,(__uintptr_t *__uaddr, __SIZE_TYPE__ __max_wake),futex_wake,(__uaddr,__max_wake))
#elif defined(__CRT_HAVE_lfutex) || defined(__CRT_HAVE_lfutex64)
#include <local/kos.futex/futex_wake.h>
/* Wake up to `MAX_WAKE' threads waiting for `*UADDR'
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
#define __localdep_futex_wake (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futex_wake))
#else /* CUSTOM: futex_wake */
#undef ____localdep_futex_wake_defined
#endif /* futex_wake... */
#endif /* !____localdep_futex_wake_defined */

__NAMESPACE_LOCAL_BEGIN
/* Wake all threads waiting for `*UADDR' (same as `futex_wake(uaddr, (size_t)-1)')
 * @return: * : The number of woken threads
 * @return: -1:EFAULT: A faulty pointer was given */
__LOCAL_LIBC(futex_wakeall) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(futex_wakeall))(__uintptr_t *__uaddr) {
#line 342 "kos/src/libc/magic/kos.futex.c"
	return __localdep_futex_wake(__uaddr, (__SIZE_TYPE__)-1);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_lfutex || __CRT_HAVE_lfutex64 || __CRT_HAVE_futex_wake */
#endif /* !__local_futex_wakeall_defined */
