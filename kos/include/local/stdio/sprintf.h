/* HASH CRC-32:0x71d7866e */
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
#ifndef __local_sprintf_defined
#define __local_sprintf_defined 1
/* Dependency: "vsprintf" from "stdio" */
#ifndef ____localdep_vsprintf_defined
#define ____localdep_vsprintf_defined 1
#if __has_builtin(__builtin_vsprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__EXTERNINLINE __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __localdep_vsprintf)(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args) { return __builtin_vsprintf(__dest, __format, __args); }
#elif defined(__CRT_HAVE_vsprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_vsprintf,(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args),vsprintf,(__dest,__format,__args))
#elif defined(__CRT_HAVE__IO_vsprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_vsprintf,(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args),_IO_vsprintf,(__dest,__format,__args))
#else /* LIBC: vsprintf */
#include <local/stdio/vsprintf.h>
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
#define __localdep_vsprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsprintf))
#endif /* vsprintf... */
#endif /* !____localdep_vsprintf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__LOCAL_LIBC(sprintf) __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(sprintf))(char *__restrict __buf,
                                                      char const *__restrict __format,
                                                      ...) {
#line 1002 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vsprintf(__buf, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_sprintf_defined */
