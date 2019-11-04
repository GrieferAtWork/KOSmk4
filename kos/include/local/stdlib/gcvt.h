/* HASH CRC-32:0xd14f4df7 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef __local_gcvt_defined
#define __local_gcvt_defined 1
/* Dependency: "sprintf" from "stdio" */
#ifndef ____localdep_sprintf_defined
#define ____localdep_sprintf_defined 1
#if __has_builtin(__builtin_sprintf) && __has_builtin(__builtin_va_arg_pack) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) { return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); }
#elif defined(__CRT_HAVE_sprintf) && (!defined(__NO_ASMNAME))
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__LIBC __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("sprintf");
#else /* LIBC: sprintf */
#include <local/stdio/sprintf.h>
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
#define __localdep_sprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sprintf))
#endif /* sprintf... */
#endif /* !____localdep_sprintf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(gcvt) __ATTR_WUNUSED __ATTR_NONNULL((3)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gcvt))(double __val,
                                                  int __ndigit,
                                                  char *__buf) {
#line 1005 "kos/src/libc/magic/stdlib.c"
#ifndef __DBL_NDIGIT_MAX
#if __DBL_MANT_DIG__ == 53
#define __DBL_NDIGIT_MAX 17
#elif __DBL_MANT_DIG__ == 24
#define __DBL_NDIGIT_MAX 9
#elif __DBL_MANT_DIG__ == 56
#define __DBL_NDIGIT_MAX 18
#else
	/* ceil (M_LN2 / M_LN10 * DBL_MANT_DIG + 1.0) */
#define __DBL_NDIGIT_MAX (__DBL_MANT_DIG__ / 4)
#endif
#endif /* !LDBG_NDIGIT_MAX */
	if (__ndigit > __DBL_NDIGIT_MAX)
		__ndigit = __DBL_NDIGIT_MAX;
	__localdep_sprintf(__buf, "%.*g", __ndigit, __val);
	return __buf;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_gcvt_defined */
