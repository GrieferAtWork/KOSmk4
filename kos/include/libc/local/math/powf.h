/* HASH CRC-32:0x40629602 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_powf_defined
#define __local_powf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pow_defined
#define __local___localdep_pow_defined
#if __has_builtin(__builtin_pow) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow)
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,__localdep_pow,(double __x, double __y),pow,{ return __builtin_pow(__x, __y); })
#elif defined(__CRT_HAVE_pow)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,__localdep_pow,(double __x, double __y),pow,(__x,__y))
#elif defined(__CRT_HAVE___pow)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,__localdep_pow,(double __x, double __y),__pow,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/pow.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pow __LIBC_LOCAL_NAME(pow)
#else /* ... */
#undef __local___localdep_pow_defined
#endif /* !... */
#endif /* !__local___localdep_pow_defined */
__NAMESPACE_LOCAL_END
#include <libm/finite.h>
#include <libm/isnan.h>
#include <libm/matherr.h>
#include <libm/pow.h>
#include <libm/signbit.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(powf) __ATTR_WUNUSED __DECL_SIMD_powf float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(powf))(float __x, float __y) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	float __result;
	__result = __LIBM_MATHFUN2F(pow, __x, __y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission  to use, copy, modify, and distribute this
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
					return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERRF_POW_NAN);
			} else if (__LIBM_MATHFUNIF(finite, __x) && __LIBM_MATHFUNIF(finite, __y)) {
				if (__LIBM_MATHFUNIF(isnan, __result)) { /* pow neg**non-int */
					return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERRF_POW_NONINT);
				} else if (__x == 0.0f && __y < 0.0f) {
					if (__LIBM_MATHFUNIF(signbit, __x) && __LIBM_MATHFUNIF(signbit, __result)) { /* pow(-0.0,negative) */
						return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERRF_POW_MINUS);
					} else { /* pow(+0.0,negative) */
						return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERRF_POW_ZEROMINUS);
					}
				} else {
					/* pow overflow */
					return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERRF_POW_OVERFLOW);
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
				return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERRF_POW_ZERO);
			}
		} else {
			/* pow underflow */
			return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERRF_POW_UNDERFLOW);
		}
	}
	return __result;
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_pow)((double)__x, (double)__y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_powf_defined
#define __local___localdep_powf_defined
#define __localdep_powf __LIBC_LOCAL_NAME(powf)
#endif /* !__local___localdep_powf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_pow || __CRT_HAVE___pow || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_powf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_pow && !__CRT_HAVE___pow && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_powf_defined */
