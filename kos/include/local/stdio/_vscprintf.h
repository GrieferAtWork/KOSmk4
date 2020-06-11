/* HASH CRC-32:0x59e9dfd6 */
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
#ifndef __local__vscprintf_defined
#define __local__vscprintf_defined 1
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vsnprintf from stdio */
#ifndef __local___localdep_vsnprintf_defined
#define __local___localdep_vsnprintf_defined 1
#ifdef __vsnprintf_defined
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__NAMESPACE_GLB_USING(vsnprintf)
#define __localdep_vsnprintf vsnprintf
#elif defined(__std_vsnprintf_defined)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__NAMESPACE_STD_USING(vsnprintf)
#define __localdep_vsnprintf vsnprintf
#elif __has_builtin(__builtin_vsnprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsnprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),vsnprintf,{ return __builtin_vsnprintf(__buf, __buflen, __format, __args); })
#elif defined(__CRT_HAVE_vsnprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),vsnprintf,(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE___vsnprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),__vsnprintf,(__buf,__buflen,__format,__args))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/stdio/vsnprintf.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
#define __localdep_vsnprintf __LIBC_LOCAL_NAME(vsnprintf)
#endif /* !... */
#endif /* !__local___localdep_vsnprintf_defined */
__LOCAL_LIBC(_vscprintf) __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vscprintf))(char const *__restrict __format, __builtin_va_list __args) {
	return __localdep_vsnprintf(__NULLPTR, 0, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vscprintf_defined
#define __local___localdep__vscprintf_defined 1
#define __localdep__vscprintf __LIBC_LOCAL_NAME(_vscprintf)
#endif /* !__local___localdep__vscprintf_defined */
#endif /* !__local__vscprintf_defined */
