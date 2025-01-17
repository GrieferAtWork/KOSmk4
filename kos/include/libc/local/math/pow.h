/* HASH CRC-32:0x576054c */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_pow_defined
#define __local_pow_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <bits/crt/math-vector.h>
#include <libm/finite.h>
#include <libm/isnan.h>
#include <libm/matherr.h>
#include <libm/pow.h>
#include <libm/signbit.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pow) __ATTR_WUNUSED __DECL_SIMD_pow double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(pow))(double __x, double __y) {
	double __result;
	__result = __LIBM_MATHFUN2(pow, __x, __y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission  to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice
	 * is preserved.
	 * ====================================================
	 */
	if (!__LIBM_MATHFUNI(finite, __result)) {
		if (__LIBM_MATHFUNI(isnan, __y) && __x == 1.0) {
			__result = 1.0;
		} else if (__LIBM_LIB_VERSION != __LIBM_IEEE) {
			if (__LIBM_MATHFUNI(isnan, __x)) {
				if (__y == 0.0) /* pow(NaN,0.0) */
					return __kernel_standard(__x, __y, __result, __LIBM_KMATHERR_POW_NAN);
			} else if (__LIBM_MATHFUNI(finite, __x) && __LIBM_MATHFUNI(finite, __y)) {
				if (__LIBM_MATHFUNI(isnan, __result)) { /* pow neg**non-int */
					return __kernel_standard(__x, __y, __result, __LIBM_KMATHERR_POW_NONINT);
				} else if (__x == 0.0 && __y < 0.0) {
					if (__LIBM_MATHFUNI(signbit, __x) && __LIBM_MATHFUNI(signbit, __result)) { /* pow(-0.0,negative) */
						return __kernel_standard(__x, __y, __result, __LIBM_KMATHERR_POW_MINUS);
					} else { /* pow(+0.0,negative) */
						return __kernel_standard(__x, __y, __result, __LIBM_KMATHERR_POW_ZEROMINUS);
					}
				} else {
					/* pow overflow */
					return __kernel_standard(__x, __y, __result, __LIBM_KMATHERR_POW_OVERFLOW);
				}
			}
		}
	} else if (__result == 0.0 &&
	           __LIBM_MATHFUNI(finite, __x) &&
	           __LIBM_MATHFUNI(finite, __y) &&
	           __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (__x == 0.0) {
			if (__y == 0.0) {
				/* pow(0.0, 0.0) */
				return __kernel_standard(__x, __y, __result, __LIBM_KMATHERR_POW_ZERO);
			}
		} else {
			/* pow underflow */
			return __kernel_standard(__x, __y, __result, __LIBM_KMATHERR_POW_UNDERFLOW);
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pow_defined
#define __local___localdep_pow_defined
#define __localdep_pow __LIBC_LOCAL_NAME(pow)
#endif /* !__local___localdep_pow_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_pow_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_pow_defined */
