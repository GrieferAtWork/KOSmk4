/* HASH CRC-32:0xce411dbe */
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
#ifndef __local__vsnprintf_defined
#define __local__vsnprintf_defined 1
/* Dependency: "vsnprintf" from "stdio" */
#ifndef ____localdep_vsnprintf_defined
#define ____localdep_vsnprintf_defined 1
#ifdef __std___localdep_vsnprintf_defined
__NAMESPACE_STD_USING(__localdep_vsnprintf)
#elif __has_builtin(__builtin_vsnprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsnprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__EXTERNINLINE __ATTR_NONNULL((3)) __ATTR_LIBC_PRINTF(3, 0) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL __localdep_vsnprintf)(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args) { return __builtin_vsnprintf(__buf, __buflen, __format, __args); }
#elif defined(__CRT_HAVE_vsnprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CREDIRECT(__ATTR_NONNULL((3)) __ATTR_LIBC_PRINTF(3, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),vsnprintf,(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE___vsnprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
__CREDIRECT(__ATTR_NONNULL((3)) __ATTR_LIBC_PRINTF(3, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),__vsnprintf,(__buf,__buflen,__format,__args))
#else /* LIBC: vsnprintf */
#include <local/stdio/vsnprintf.h>
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character), and never write more than `BUFLEN' characters to `BUF' */
#define __localdep_vsnprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsnprintf))
#endif /* vsnprintf... */
#endif /* !____localdep_vsnprintf_defined */

__NAMESPACE_LOCAL_BEGIN
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
__LOCAL_LIBC(_vsnprintf) __ATTR_NONNULL((3)) __ATTR_LIBC_PRINTF(3, 0) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vsnprintf))(char *__restrict __buf,
                                                        __SIZE_TYPE__ __bufsize,
                                                        char const *__restrict __format,
                                                        __builtin_va_list __args) {
#line 2476 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__result = __localdep_vsnprintf(__buf, __bufsize, __format, __args);
	if (__result > __bufsize)
		__result = __bufsize;
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__vsnprintf_defined */
