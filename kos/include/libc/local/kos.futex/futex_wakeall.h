/* HASH CRC-32:0xff032d19 */
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
#ifndef __local_futex_wakeall_defined
#define __local_futex_wakeall_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_futex_wake) || defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_futex_wake_defined
#define __local___localdep_futex_wake_defined
#ifdef __CRT_HAVE_futex_wake
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_futex_wake,(__uintptr_t *__uaddr, __SIZE_TYPE__ __max_wake),futex_wake,(__uaddr,__max_wake))
#elif defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.futex/futex_wake.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_futex_wake __LIBC_LOCAL_NAME(futex_wake)
#else /* ... */
#undef __local___localdep_futex_wake_defined
#endif /* !... */
#endif /* !__local___localdep_futex_wake_defined */
__LOCAL_LIBC(futex_wakeall) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(futex_wakeall))(__uintptr_t *__uaddr) {
	return (__NAMESPACE_LOCAL_SYM __localdep_futex_wake)(__uaddr, (__SIZE_TYPE__)-1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_futex_wakeall_defined
#define __local___localdep_futex_wakeall_defined
#define __localdep_futex_wakeall __LIBC_LOCAL_NAME(futex_wakeall)
#endif /* !__local___localdep_futex_wakeall_defined */
#else /* __CRT_HAVE_futex_wake || __CRT_HAVE_lfutex64 || __CRT_HAVE_lfutex */
#undef __local_futex_wakeall_defined
#endif /* !__CRT_HAVE_futex_wake && !__CRT_HAVE_lfutex64 && !__CRT_HAVE_lfutex */
#endif /* !__local_futex_wakeall_defined */
