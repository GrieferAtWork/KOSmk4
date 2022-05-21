/* HASH CRC-32:0x1857129d */
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
#ifndef __local__strerror_s_defined
#define __local__strerror_s_defined
#include <__crt.h>
#include <libc/errno.h>
#ifdef __libc_geterrno
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_snprintf_defined
#define __local___localdep_snprintf_defined
#if __has_builtin(__builtin_snprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_snprintf) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_snprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...),snprintf,{ return __builtin_snprintf(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_snprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_snprintf)(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...) __CASMNAME("snprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/snprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_snprintf __LIBC_LOCAL_NAME(snprintf)
#endif /* !... */
#endif /* !__local___localdep_snprintf_defined */
#ifndef __local___localdep_strerrordesc_np_defined
#define __local___localdep_strerrordesc_np_defined
#ifdef __CRT_HAVE_strerrordesc_np
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_strerrordesc_np,(__errno_t __errnum),strerrordesc_np,(__errnum))
#else /* __CRT_HAVE_strerrordesc_np */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strerrordesc_np.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strerrordesc_np __LIBC_LOCAL_NAME(strerrordesc_np)
#endif /* !__CRT_HAVE_strerrordesc_np */
#endif /* !__local___localdep_strerrordesc_np_defined */
__LOCAL_LIBC(_strerror_s) __ATTR_ACCESS_RO_OPT(3) __ATTR_ACCESS_WRS(1, 2) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_strerror_s))(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__message) {
	char const *__string;
	__SIZE_TYPE__ __reqlen;
	__errno_t __eno = __libc_geterrno();
	__string = (__NAMESPACE_LOCAL_SYM __localdep_strerrordesc_np)(__eno);
	if (__string) {
		if (__message) {
			__reqlen = (__NAMESPACE_LOCAL_SYM __localdep_snprintf)(__buf, __buflen, "%s: %s\n", __message, __string);
		} else {
			__reqlen = (__NAMESPACE_LOCAL_SYM __localdep_snprintf)(__buf, __buflen, "%s\n", __string);
		}
	} else if (__message) {
		__reqlen = (__NAMESPACE_LOCAL_SYM __localdep_snprintf)(__buf, __buflen, "%s: Unknown error %d\n", __message, __eno);
	} else {
		__reqlen = (__NAMESPACE_LOCAL_SYM __localdep_snprintf)(__buf, __buflen, "Unknown error %d\n", __eno);
	}
	if (__reqlen > __buflen)
		return 34;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__strerror_s_defined
#define __local___localdep__strerror_s_defined
#define __localdep__strerror_s __LIBC_LOCAL_NAME(_strerror_s)
#endif /* !__local___localdep__strerror_s_defined */
#else /* __libc_geterrno */
#undef __local__strerror_s_defined
#endif /* !__libc_geterrno */
#endif /* !__local__strerror_s_defined */
