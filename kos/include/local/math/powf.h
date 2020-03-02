/* HASH CRC-32:0x55567fe6 */
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
#ifndef __local_powf_defined
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
#define __local_powf_defined 1
#include <bits/math-vector.h>
#include <bits/math-vector.h>
#include <libm/finite.h>

#include <libm/isnan.h>

#include <libm/matherr.h>

#include <libm/pow.h>
/* Dependency: "pow" from "math" */
#ifndef ____localdep_pow_defined
#define ____localdep_pow_defined 1
#if __has_builtin(__builtin_pow) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow)
/* Return X to the Y power */
__CEIREDIRECT(__DECL_SIMD_pow __ATTR_WUNUSED,double,__NOTHROW,__localdep_pow,(double __x, double __y),pow,{ return __builtin_pow(__x, __y); })
#elif defined(__CRT_HAVE_pow)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_pow __ATTR_WUNUSED,double,__NOTHROW,__localdep_pow,(double __x, double __y),pow,(__x,__y))
#elif defined(__CRT_HAVE___pow)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_pow __ATTR_WUNUSED,double,__NOTHROW,__localdep_pow,(double __x, double __y),__pow,(__x,__y))
#else /* LIBC: pow */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/pow.h>
/* Return X to the Y power */
#define __localdep_pow (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow))
#else /* CUSTOM: pow */
#undef ____localdep_pow_defined
#endif /* pow... */
#endif /* pow... */
#endif /* !____localdep_pow_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return X to the Y power */
__LOCAL_LIBC(powf) __DECL_SIMD_powf __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(powf))(float __x,
                                              float __y) {
#line 601 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUN2F
	float __result;
	__result = __LIBM_MATHFUN2F(pow, __x, __y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice 
	 * is preserved.
	 * ====================================================
	 */
	if (!__LIBM_MATHFUNIF(finite, __result)) {
		if (__LIBM_MATHFUNIF(isnan, __y) && __x == 1.0f) {
			__result = 1.0f;
		} else if (__LIBM_LIB_VERSION != __LIBM_IEEE) {
			if (__LIBM_MATHFUNIF(isnan, __x)) {
				if (__y == 0.0f) /* pow(NaN,0.0) */
					return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERR_POW_NAN);
			} else if (__LIBM_MATHFUNIF(finite, __x) && __LIBM_MATHFUNIF(finite, __y)) {
				if (__LIBM_MATHFUNIF(isnan, __result)) { /* pow neg**non-int */
					return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERR_POW_NONINT);
				} else if (__x == 0.0f && __y < 0.0f) {
					if (__LIBM_MATHFUNIF(signbit, __x) && __LIBM_MATHFUNIF(signbit, __result)) { /* pow(-0.0,negative) */
						return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERR_POW_MINUS);
					} else { /* pow(+0.0,negative) */
						return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERR_POW_ZEROMINUS);
					}
				} else {
					/* pow overflow */
					return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERR_POW_OVERFLOW);
				}
			}
		}
	} else if (__result == 0.0f &&
	           __LIBM_MATHFUNIF(finite, __x) &&
	           __LIBM_MATHFUNIF(finite, __y) &&
	           __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (__x == 0.0f) {
			if (__y == 0.0f) {
				/* pow(0.0, 0.0) */
				return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERR_POW_ZERO);
			}
		} else {
			/* pow underflow */
			return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERR_POW_UNDERFLOW);
		}
	}
	return __result;
#else /* __LIBM_MATHFUN2F */
	return (float)__localdep_pow((double)__x, (double)__y);
#endif /* !__LIBM_MATHFUN2F */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_pow || __CRT_HAVE___pow */
#endif /* !__local_powf_defined */
