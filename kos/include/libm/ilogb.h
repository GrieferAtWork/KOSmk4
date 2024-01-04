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
#ifndef _LIBM_ILOGB_H
#define _LIBM_ILOGB_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/crt/mathdef.h> /* __FP_ILOGB0, __FP_ILOGBNAN */
#include <bits/types.h>

#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

__LIBM_LOCAL_FUNC(ilogbf) __ATTR_CONST __ATTR_WUNUSED int
(__LIBCCALL __ieee754_ilogbf)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __hx, __ix;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__hx &= __INT32_C(0x7fffffff);
	if (__hx < __INT32_C(0x00800000)) {
		if (__hx == 0)
			return __FP_ILOGB0; /* ilogb(0) = FP_ILOGB0 */
		/* subnormal x */
		for (__ix = -126, __hx <<= 8; __hx > 0; __hx <<= 1)
			__ix -= 1;
		return (int)__ix;
	}
	if (__hx < __INT32_C(0x7f800000))
		return (int)((__hx >> IEEE754_FLOAT_SHIFT) - IEEE754_FLOAT_BIAS);
#if __FP_ILOGBNAN != __INT_MAX__
	/* ISO C99 requires ilogbf(+-Inf) == INT_MAX.  */
	if (__hx == __INT32_C(0x7f800000))
		return __INT_MAX__;
#endif /* __FP_ILOGBNAN != __INT_MAX__ */
	return __FP_ILOGBNAN;
}

#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

__LIBM_LOCAL_FUNC(ilogb) __ATTR_CONST __ATTR_WUNUSED int
(__LIBCCALL __ieee754_ilogb)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __hx, __lx, __ix;
	__LIBM_GET_HIGH_WORD(__hx, __x);
	__hx &= __INT32_C(0x7fffffff);
	if (__hx < __INT32_C(0x00100000)) {
		__LIBM_GET_LOW_WORD(__lx, __x);
		if ((__hx | __lx) == 0)
			return __FP_ILOGB0; /* ilogb(0) = FP_ILOGB0 */
		/* subnormal x */
		if (__hx == 0) {
			for (__ix = -1043; __lx > 0; __lx <<= 1)
				__ix -= 1;
		} else {
			for (__ix = -1022, __hx <<= 11; __hx > 0; __hx <<= 1)
				__ix -= 1;
		}
		return (int)__ix;
	}
	if (__hx < __INT32_C(0x7ff00000))
		return (int)((__hx >> IEEE754_DOUBLE_SHIFT) - IEEE754_DOUBLE_BIAS);
#if __FP_ILOGBNAN != __INT_MAX__
	/* ISO C99 requires ilogb(+-Inf) == INT_MAX.  */
	__LIBM_GET_LOW_WORD(__lx, __x);
	if (((__hx ^ __INT32_C(0x7ff00000)) | __lx) == 0)
		return __INT_MAX__;
#endif /* __FP_ILOGBNAN != __INT_MAX__ */
	return __FP_ILOGBNAN;
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

__LIBM_LOCAL_FUNC(ilogbl) __ATTR_CONST __ATTR_WUNUSED int
(__LIBCCALL __ieee854_ilogbl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__int32_t __es, __hx, __lx, __ix;
	__LIBM_GET_LDOUBLE_EXP(__es, __x);
	__es &= 0x7fff;
	if (__es == 0) {
		__LIBM_GET_LDOUBLE_WORDS(__es, __hx, __lx, __x);
		__hx &= __INT32_C(0x7fffffff);
		if ((__hx | __lx) == 0)
			return __FP_ILOGB0; /* ilogbl(0) = FP_ILOGB0 */
		/* subnormal x */
		if (__hx == 0) {
			for (__ix = -16414; __lx > 0; __lx <<= 1)
				__ix -= 1;
		} else {
			for (__ix = -16383, __hx <<= 1; __hx > 0; __hx <<= 1)
				__ix -= 1;
		}
		return (int)__ix;
	}
	if (__es < 0x7fff)
		return (int)__es - 0x3fff;
#if __FP_ILOGBNAN != __INT_MAX__
	__LIBM_GET_LDOUBLE_WORDS(__es, __hx, __lx, __x);
	if (((__hx & __INT32_C(0x7fffffff)) | __lx) == 0)
		/* ISO C99 requires ilogbl(+-Inf) == INT_MAX.  */
		return __INT_MAX__;
#endif /* __FP_ILOGBNAN != __INT_MAX__ */
	return __FP_ILOGBNAN;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ILOGB_H */
