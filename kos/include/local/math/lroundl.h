/* HASH CRC-32:0xcd87d242 */
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
#ifndef __local_lroundl_defined
#define __local_lroundl_defined 1
/* Dependency: "roundl" from "math" */
#ifndef ____localdep_roundl_defined
#define ____localdep_roundl_defined 1
#if __has_builtin(__builtin_roundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST long double __NOTHROW(__LIBCCALL __localdep_roundl)(long double __x) { return __builtin_roundl(__x); }
#elif defined(__CRT_HAVE_roundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_WUNUSED __ATTR_CONST,long double,__NOTHROW,__localdep_roundl,(long double __x),roundl,(__x))
#elif defined(__CRT_HAVE___roundl)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_WUNUSED __ATTR_CONST,long double,__NOTHROW,__localdep_roundl,(long double __x),__roundl,(__x))
#else /* LIBC: roundl */
#include <local/math/roundl.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
#define __localdep_roundl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundl))
#endif /* roundl... */
#endif /* !____localdep_roundl_defined */

__NAMESPACE_LOCAL_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
__LOCAL_LIBC(lroundl) __ATTR_WUNUSED __ATTR_CONST long int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(lroundl))(long double __x) {
#line 521 "kos/src/libc/magic/math.c"
	return (long int)__localdep_roundl(__x);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_lroundl_defined */
