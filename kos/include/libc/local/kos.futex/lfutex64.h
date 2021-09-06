/* HASH CRC-32:0xa6feedfe */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_lfutex64_defined
#define __local_lfutex64_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_lfutex
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_lfutex32_defined
#define __local___localdep_lfutex32_defined 1
__CVREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_lfutex32,(__uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val),lfutex,(__uaddr,__futex_op,__val),__val,2,(__UINTPTR_TYPE__,__UINTPTR_TYPE__))
#endif /* !__local___localdep_lfutex32_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(lfutex64) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(lfutex64))(__uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val, ...) {
	__builtin_va_list __args;
	__uintptr_t __val2;
	struct __timespec32 __tms32;
	struct __timespec64 const *__timeout;
	__builtin_va_start(__args, __val);
	__timeout = __builtin_va_arg(__args, struct __timespec64 const *);
	__val2 = __builtin_va_arg(__args, __uintptr_t);
	__builtin_va_end(__args);
	if (!__timeout || !LFUTEX_USES_TIMEOUT(__futex_op))
		return __localdep_lfutex32(__uaddr, __futex_op, __val, (struct __timespec32 *)__NULLPTR, __val2);
	__tms32.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tms32.tv_nsec = __timeout->tv_nsec;
	return __localdep_lfutex32(__uaddr, __futex_op, __val, &__tms32, __val2);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lfutex64_defined
#define __local___localdep_lfutex64_defined 1
#define __localdep_lfutex64 __LIBC_LOCAL_NAME(lfutex64)
#endif /* !__local___localdep_lfutex64_defined */
#else /* __CRT_HAVE_lfutex */
#undef __local_lfutex64_defined
#endif /* !__CRT_HAVE_lfutex */
#endif /* !__local_lfutex64_defined */
