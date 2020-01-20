/* HASH CRC-32:0x98cedeb5 */
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
#ifndef __local_strerror_defined
#define __local_strerror_defined 1
/* Dependency: "strerror_s" from "string" */
#ifndef ____localdep_strerror_s_defined
#define ____localdep_strerror_s_defined 1
#ifdef __CRT_HAVE_strerror_s
__CREDIRECT(__ATTR_CONST __ATTR_PURE __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_strerror_s,(int __errnum),strerror_s,(__errnum))
#else /* LIBC: strerror_s */
#include <local/string/strerror_s.h>
#define __localdep_strerror_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerror_s))
#endif /* strerror_s... */
#endif /* !____localdep_strerror_s_defined */

/* Dependency: "strncpy" from "string" */
#ifndef ____localdep_strncpy_defined
#define ____localdep_strncpy_defined 1
#if __has_builtin(__builtin_strncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncpy)
__EXTERNINLINE __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __localdep_strncpy)(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen) { return __builtin_strncpy(__buf, __src, __buflen); }
#elif defined(__CRT_HAVE_strncpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),strncpy,(__buf,__src,__buflen))
#else /* LIBC: strncpy */
#include <local/string/strncpy.h>
#define __localdep_strncpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncpy))
#endif /* strncpy... */
#endif /* !____localdep_strncpy_defined */

/* Dependency: "sprintf" from "stdio" */
#ifndef ____localdep_sprintf_defined
#define ____localdep_sprintf_defined 1
#if __has_builtin(__builtin_sprintf) && __has_builtin(__builtin_va_arg_pack) && !defined(__NO_EXTERNINLINE) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__EXTERNINLINE __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) { return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); }
#elif defined(__CRT_HAVE_sprintf) && !defined(__NO_ASMNAME)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__LIBC __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("sprintf");
#elif defined(__CRT_HAVE__IO_sprintf) && !defined(__NO_ASMNAME)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__LIBC __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("_IO_sprintf");
#else /* LIBC: sprintf */
#include <local/stdio/sprintf.h>
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
#define __localdep_sprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sprintf))
#endif /* sprintf... */
#endif /* !____localdep_sprintf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__strerror_buf) char __strerror_buf[64] = { 0 };
__LOCAL_LIBC(strerror) __ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strerror))(int __errnum) {
#line 433 "kos/src/libc/magic/string.c"
	char *__result = __strerror_buf;
	char const *__string;
	__string = __localdep_strerror_s(__errnum);
	if (__string) {
		/* Copy the descriptor text. */
		__result[__COMPILER_LENOF(__strerror_buf) - 1] = '\0';
		__localdep_strncpy(__result, __string, __COMPILER_LENOF(__strerror_buf) - 1);
	} else {
		__localdep_sprintf(__result, "Unknown error %d", __errnum);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strerror_defined */
