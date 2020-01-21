/* HASH CRC-32:0xf54986d1 */
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
#ifndef __local_isinfl_defined
#define __local_isinfl_defined 1
#include <libm/isinf.h>

#include <bits/huge_vall.h>
/* Dependency: "isinf" from "math" */
#ifndef ____localdep_isinf_defined
#define ____localdep_isinf_defined 1
#if __has_builtin(__builtin_isinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinf)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__EXTERNINLINE __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isinf)(double __x) { return __builtin_isinf(__x); }
#elif defined(__CRT_HAVE_isinf)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),isinf,(__x))
#elif defined(__CRT_HAVE___isinf)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),__isinf,(__x))
#else /* LIBC: isinf */
#include <local/math/isinf.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
#define __localdep_isinf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinf))
#endif /* isinf... */
#endif /* !____localdep_isinf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__LOCAL_LIBC(isinfl) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(isinfl))(__LONGDOUBLE __x) {
#line 1341 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee854_isinfl((__IEEE854_LONG_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_isinff((__IEEE754_FLOAT_TYPE__)__x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_isinf((__IEEE754_DOUBLE_TYPE__)__x);
#elif 1
	return __localdep_isinf((double)__x);
#else /* ... */
	return __x == HUGE_VALL;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_isinfl_defined */
