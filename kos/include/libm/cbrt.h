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
#ifndef _LIBM_CBRT_H
#define _LIBM_CBRT_H 1

#include <__crt.h>

#include <hybrid/typecore.h>

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


/* cbrtf(x)
 * Return cube root of x
 */

__LIBM_LOCAL_DECLARE_BEGIN
__LIBM_LOCAL_DECLARE(__uint32_t, B1f, 709958130) /* B1 = (84+2/3-0.03306235651)*2**23 */
__LIBM_LOCAL_DECLARE(__uint32_t, B2f, 642849266) /* B2 = (76+2/3-0.03306235651)*2**23 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Cf, __IEEE754_FLOAT_C(5.4285717010e-01))  /* 19/35     = 0x3f0af8b0 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Df, __IEEE754_FLOAT_C(-7.0530611277e-01)) /* -864/1225 = 0xbf348ef1 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Ef, __IEEE754_FLOAT_C(1.4142856598e+00))  /* 99/70     = 0x3fb50750 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Ff, __IEEE754_FLOAT_C(1.6071428061e+00))  /* 45/28     = 0x3fcdb6db */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Gf, __IEEE754_FLOAT_C(3.5714286566e-01))  /* 5/14      = 0x3eb6db6e */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_cbrtf)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __hx;
	__IEEE754_FLOAT_TYPE__ __r, __s, __t;
	__uint32_t __sign;
	__uint32_t __high;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__sign = __hx & 0x80000000; /* sign= sign(x) */
	__hx ^= __sign;
	if (!__LIBM_FLT_UWORD_IS_FINITE(__hx))
		return (__x + __x); /* cbrt(NaN,INF) is itself */
	if (__LIBM_FLT_UWORD_IS_ZERO(__hx))
		return (__x); /* cbrt(0) is itself */

	__LIBM_SET_FLOAT_WORD(__x, __hx); /* x <- |x| */
	/* rough cbrt to 5 bits */
	if (__LIBM_FLT_UWORD_IS_SUBNORMAL(__hx)) { /* subnormal number */
		__LIBM_SET_FLOAT_WORD(__t, 0x4b800000); /* set t= 2**24 */
		__t *= __x;
		__LIBM_GET_FLOAT_WORD(__high, __t);
		__LIBM_SET_FLOAT_WORD(__t, __high / 3 + __LIBM_LOCAL_VALUE(B2f));
	} else {
		__LIBM_SET_FLOAT_WORD(__t, __hx / 3 + __LIBM_LOCAL_VALUE(B1f));
	}

	/* new cbrt to 23 bits */
	__r = __t * __t / __x;
	__s = __LIBM_LOCAL_VALUE(Cf) + __r * __t;
	__t *= __LIBM_LOCAL_VALUE(Gf) + __LIBM_LOCAL_VALUE(Ff) / (__s + __LIBM_LOCAL_VALUE(Ef) + __LIBM_LOCAL_VALUE(Df) / __s);

	/* restore the sign bit */
	__LIBM_GET_FLOAT_WORD(__high, __t);
	__LIBM_SET_FLOAT_WORD(__t, __high | __sign);
	return (__t);
}

#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
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


/* cbrtf(x)
 * Return cube root of x
 */

__LIBM_LOCAL_DECLARE_BEGIN
__LIBM_LOCAL_DECLARE(__uint32_t, B1, 715094163) /* B1 = (682-0.03306235651)*2**20 */
__LIBM_LOCAL_DECLARE(__uint32_t, B2, 696219795) /* B2 = (664-0.03306235651)*2**20 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, C, __IEEE754_DOUBLE_C(5.42857142857142815906e-01)) /* 19/35     = 0x3FE15F15, 0xF15F15F1 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, D, __IEEE754_DOUBLE_C(7.05306122448979611050e-01)) /* -864/1225 = 0xBFE691DE, 0x2532C834 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, E, __IEEE754_DOUBLE_C(1.41428571428571436819e+00)) /* 99/70     = 0x3FF6A0EA, 0x0EA0EA0F */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, F, __IEEE754_DOUBLE_C(1.60714285714285720630e+00)) /* 45/28     = 0x3FF9B6DB, 0x6DB6DB6E */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, G, __IEEE754_DOUBLE_C(3.57142857142857150787e-01)) /* 5/14      = 0x3FD6DB6D, 0xB6DB6DB7 */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_cbrt)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __hx;
	__IEEE754_DOUBLE_TYPE__ __r, __s, __t = __IEEE754_DOUBLE_C(0.0), __w;
	__uint32_t __sign;
	__uint32_t __high, __low;
	__LIBM_GET_HIGH_WORD(__hx, __x);
	__sign = __hx & 0x80000000; /* sign= sign(x) */
	__hx ^= __sign;
	if (__hx >= 0x7ff00000)
		return (__x + __x); /* cbrt(NaN,INF) is itself */
	__LIBM_GET_LOW_WORD(__low, __x);
	if ((__hx | __low) == 0)
		return (__x); /* cbrt(0) is itself */

	__LIBM_SET_HIGH_WORD(__x, __hx); /* x <- |x| */
	/* rough cbrt to 5 bits */

	if (__hx < 0x00100000) { /* subnormal number */
		__LIBM_SET_HIGH_WORD(__t, 0x43500000); /* set t= 2**54 */
		__t *= __x;
		__LIBM_GET_HIGH_WORD(__high, __t);
		__LIBM_SET_HIGH_WORD(__t, __high / 3 + __LIBM_LOCAL_VALUE(B2));
	} else {
		__LIBM_SET_HIGH_WORD(__t, __hx / 3 + __LIBM_LOCAL_VALUE(B1));
	}

	/* new cbrt to 23 bits, may be implemented in single precision */
	__r = __t * __t / __x;
	__s = __LIBM_LOCAL_VALUE(C) + __r * __t;
	__t *= __LIBM_LOCAL_VALUE(G) + __LIBM_LOCAL_VALUE(F) / (__s + __LIBM_LOCAL_VALUE(E) + __LIBM_LOCAL_VALUE(D) / __s);

	/* chopped to 20 bits and make it larger than cbrt(x) */
	__LIBM_GET_HIGH_WORD(__high, __t);
	__LIBM_INSERT_WORDS(__t, __high + 0x00000001, 0);

	/* one step newton iteration to 53 bits with error less than 0.667 ulps */
	__s = __t * __t; /* t*t is exact */
	__r = __x / __s;
	__w = __t + __t;
	__r = (__r - __t) / (__w + __r); /* r-s is exact */
	__t = __t + __t * __r;

	/* restore the sign bit */
	__LIBM_GET_HIGH_WORD(__high, __t);
	__LIBM_SET_HIGH_WORD(__t, __high | __sign);
	return (__t);
}

#endif /* __IEEE754_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBM_CBRT_H */
