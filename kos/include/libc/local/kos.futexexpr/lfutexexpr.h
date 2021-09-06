/* HASH CRC-32:0x98689f0e */
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
#ifndef __local_lfutexexpr_defined
#define __local_lfutexexpr_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_lfutexexpr64) || defined(__CRT_HAVE_lfutexexpr)
#include <bits/types.h>
#include <bits/os/timespec.h>
#include <kos/bits/futex-expr.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_lfutexexpr32_defined) && defined(__CRT_HAVE_lfutexexpr)
#define __local___localdep_lfutexexpr32_defined 1
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,__localdep_lfutexexpr32,(void *__base, __SIZE_TYPE__ __exprc, struct lfutexexpr const *__exprv, struct __timespec64 const *__timeout, unsigned int __timeout_flags),lfutexexpr,(__base,__exprc,__exprv,__timeout,__timeout_flags))
#endif /* !__local___localdep_lfutexexpr32_defined && __CRT_HAVE_lfutexexpr */
#ifndef __local___localdep_lfutexexpr64_defined
#define __local___localdep_lfutexexpr64_defined 1
#ifdef __CRT_HAVE_lfutexexpr64
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,__localdep_lfutexexpr64,(void *__base, __SIZE_TYPE__ __exprc, struct lfutexexpr const *__exprv, struct __timespec64 const *__timeout, unsigned int __timeout_flags),lfutexexpr64,(__base,__exprc,__exprv,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_lfutexexpr) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,__localdep_lfutexexpr64,(void *__base, __SIZE_TYPE__ __exprc, struct lfutexexpr const *__exprv, struct __timespec64 const *__timeout, unsigned int __timeout_flags),lfutexexpr,(__base,__exprc,__exprv,__timeout,__timeout_flags))
#elif defined(__CRT_HAVE_lfutexexpr)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.futexexpr/lfutexexpr64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lfutexexpr64 __LIBC_LOCAL_NAME(lfutexexpr64)
#else /* ... */
#undef __local___localdep_lfutexexpr64_defined
#endif /* !... */
#endif /* !__local___localdep_lfutexexpr64_defined */
__LOCAL_LIBC(lfutexexpr) __ATTR_NONNULL((3)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(lfutexexpr))(void *__base, __SIZE_TYPE__ __exprc, struct lfutexexpr const *__exprv, struct timespec const *__timeout, unsigned int __timeout_flags) {
#ifdef __CRT_HAVE_lfutexexpr
	struct __timespec32 __tms32;
	if (!__timeout)
		return __localdep_lfutexexpr32(__base, __exprc, __exprv, __NULLPTR, 0);
	__tms32.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tms32.tv_nsec = __timeout->tv_nsec;
	return __localdep_lfutexexpr32(__base, __exprc, __exprv, &__tms32, __timeout_flags);
#else /* __CRT_HAVE_lfutexexpr */
	struct __timespec64 __tms64;
	if (!__timeout)
		return __localdep_lfutexexpr64(__base, __exprc, __exprv, __NULLPTR, 0);
	__tms64.tv_sec  = (__time64_t)__timeout->tv_sec;
	__tms64.tv_nsec = __timeout->tv_nsec;
	return __localdep_lfutexexpr64(__base, __exprc, __exprv, &__tms64, __timeout_flags);
#endif /* !__CRT_HAVE_lfutexexpr */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lfutexexpr_defined
#define __local___localdep_lfutexexpr_defined 1
#define __localdep_lfutexexpr __LIBC_LOCAL_NAME(lfutexexpr)
#endif /* !__local___localdep_lfutexexpr_defined */
#else /* __CRT_HAVE_lfutexexpr64 || __CRT_HAVE_lfutexexpr */
#undef __local_lfutexexpr_defined
#endif /* !__CRT_HAVE_lfutexexpr64 && !__CRT_HAVE_lfutexexpr */
#endif /* !__local_lfutexexpr_defined */
