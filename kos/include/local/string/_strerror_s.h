/* HASH CRC-32:0x8434abff */
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
#ifndef __local__strerror_s_defined
#define __local__strerror_s_defined 1
#include <__crt.h>
#include <parts/errno.h>
#ifdef __libc_geterrno
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: snprintf from stdio */
#ifndef __local___localdep_snprintf_defined
#define __local___localdep_snprintf_defined 1
#if __has_builtin(__builtin_snprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_snprintf) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character),
 * and never write more than `BUFLEN' characters to `BUF' */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_snprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...),snprintf,{ return __builtin_snprintf(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_snprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character),
 * and never write more than `BUFLEN' characters to `BUF' */
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_snprintf)(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...) __CASMNAME("snprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/stdio/snprintf.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character),
 * and never write more than `BUFLEN' characters to `BUF' */
#define __localdep_snprintf __LIBC_LOCAL_NAME(snprintf)
#endif /* !... */
#endif /* !__local___localdep_snprintf_defined */
/* Dependency: strerror_s from string */
#ifndef __local___localdep_strerror_s_defined
#define __local___localdep_strerror_s_defined 1
#ifdef __CRT_HAVE_strerror_s
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_strerror_s,(__errno_t __errnum),strerror_s,(__errnum))
#else /* __CRT_HAVE_strerror_s */
__NAMESPACE_LOCAL_END
#include <local/string/strerror_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strerror_s __LIBC_LOCAL_NAME(strerror_s)
#endif /* !__CRT_HAVE_strerror_s */
#endif /* !__local___localdep_strerror_s_defined */
__LOCAL_LIBC(_strerror_s) __ATTR_NONNULL((1)) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_strerror_s))(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__message) {
	char const *__string;
	__SIZE_TYPE__ __reqlen;
	__errno_t __eno = __libc_geterrno();
	__string = __localdep_strerror_s(__eno);
	if (__string) {
		if (__message) {
			__reqlen = __localdep_snprintf(__buf, __buflen, "%s: %s\n", __message, __string);
		} else {
			__reqlen = __localdep_snprintf(__buf, __buflen, "%s\n", __string);
		}
	} else if (__message) {
		__reqlen = __localdep_snprintf(__buf, __buflen, "%s: Unknown error %d\n", __message, __eno);
	} else {
		__reqlen = __localdep_snprintf(__buf, __buflen, "Unknown error %d\n", __eno);
	}
	if (__reqlen > __buflen) {
#ifdef __ERANGE
		return __ERANGE;
#else /* __ERANGE */
		return 1;
#endif /* !__ERANGE */
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__strerror_s_defined
#define __local___localdep__strerror_s_defined 1
#define __localdep__strerror_s __LIBC_LOCAL_NAME(_strerror_s)
#endif /* !__local___localdep__strerror_s_defined */
#else /* __libc_geterrno */
#undef __local__strerror_s_defined
#endif /* !__libc_geterrno */
#endif /* !__local__strerror_s_defined */
