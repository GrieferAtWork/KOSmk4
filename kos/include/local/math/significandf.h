/* HASH CRC-32:0xea72ee18 */
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
#ifndef __local_significandf_defined
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_significand) || defined(__CRT_HAVE___significand)
#define __local_significandf_defined 1
#include <libm/significand.h>
/* Dependency: "significand" from "math" */
#ifndef ____localdep_significand_defined
#define ____localdep_significand_defined 1
#if __has_builtin(__builtin_significand) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_significand)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_significand,(double __x),significand,{ return __builtin_significand(__x); })
#elif defined(__CRT_HAVE_significand)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_significand,(double __x),significand,(__x))
#elif defined(__CRT_HAVE___significand)
/* Return the fractional part of X after dividing out `ilogb(X)' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_significand,(double __x),__significand,(__x))
#else /* LIBC: significand */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/significand.h>
/* Return the fractional part of X after dividing out `ilogb(X)' */
#define __localdep_significand (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(significand))
#else /* CUSTOM: significand */
#undef ____localdep_significand_defined
#endif /* significand... */
#endif /* significand... */
#endif /* !____localdep_significand_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the fractional part of X after dividing out `ilogb(X)' */
__LOCAL_LIBC(significandf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(significandf))(float __x) {
#line 1506 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(significand, __x);
#else /* __LIBM_MATHFUNF */
	return (float)__localdep_significand((double)__x);
#endif /* !__LIBM_MATHFUNF */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_significand || __CRT_HAVE___significand */
#endif /* !__local_significandf_defined */
