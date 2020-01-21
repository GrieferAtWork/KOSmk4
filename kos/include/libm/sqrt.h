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
#ifndef _LIBM_SQRT_H
#define _LIBM_SQRT_H 1

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

__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_onef_defined
#define __libm_onef_defined 1
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0))
#endif /* !__libm_onef_defined */
#ifndef __libm_tinyf_defined
#define __libm_tinyf_defined 1
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, tinyf, __IEEE754_FLOAT_C(1.0e-30))
#endif /* !__libm_tinyf_defined */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_sqrtf)(__IEEE754_FLOAT_TYPE__ x) {
	__IEEE754_FLOAT_TYPE__ __z;
	__uint32_t __r, __hx;
	__int32_t __ix, __s, __q, __m, __t, _i;
	__LIBM_GET_FLOAT_WORD(__ix, x);
	__hx = __ix & 0x7fffffff;
	/* take care of Inf and NaN */
	if (!__LIBM_FLT_UWORD_IS_FINITE(__hx))
		return x * x + x; /* sqrt(NaN)=NaN, sqrt(+inf)=+inf sqrt(-inf)=sNaN */
	/* take care of zero and -ves */
	if (__LIBM_FLT_UWORD_IS_ZERO(__hx))
		return x; /* sqrt(+-0) = +-0 */
	if (__ix < 0)
		return (x - x) / (x - x); /* sqrt(-ve) = sNaN */
	/* normalize x */
	__m = (__ix >> 23);
	if (__LIBM_FLT_UWORD_IS_SUBNORMAL(__hx)) { /* subnormal x */
		for (_i = 0; (__ix & 0x00800000L) == 0; _i++)
			__ix <<= 1;
		__m -= _i - 1;
	}
	__m -= 127; /* unbias exponent */
	__ix = (__ix & 0x007fffffL) | 0x00800000L;
	if (__m & 1) /* odd m, double x to make it even */
		__ix += __ix;
	__m >>= 1; /* m = [m/2] */

	/* generate sqrt(x) bit by bit */
	__ix += __ix;
	__q = __s = 0;           /* q = sqrt(x) */
	__r       = 0x01000000L; /* r = moving bit from right to left */

	while (__r != 0) {
		__t = __s + __r;
		if (__t <= __ix) {
			__s = __t + __r;
			__ix -= __t;
			__q += __r;
		}
		__ix += __ix;
		__r >>= 1;
	}

	/* use floating add to find out rounding direction */
	if (__ix != 0) {
		__z = __LIBM_LOCAL_VALUE(onef) - __LIBM_LOCAL_VALUE(tinyf); /* trigger inexact flag */
		if (__z >= __LIBM_LOCAL_VALUE(onef)) {
			__z = __LIBM_LOCAL_VALUE(onef) + __LIBM_LOCAL_VALUE(tinyf);
			if (__z > __LIBM_LOCAL_VALUE(onef))
				__q += 2;
			else {
				__q += (__q & 1);
			}
		}
	}
	__ix = (__q >> 1) + 0x3f000000L;
	__ix += (__m << 23);
	__LIBM_SET_FLOAT_WORD(__z, __ix);
	return __z;
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

__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_one_defined
#define __libm_one_defined 1
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.0))
#endif /* !__libm_one_defined */
#ifndef __libm_tiny_defined
#define __libm_tiny_defined 1
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, tiny, __IEEE754_DOUBLE_C(1.0e-300))
#endif /* !__libm_tiny_defined */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_sqrt)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ z;
	__int32_t __sign = 0x80000000;
	__uint32_t __r, __t1, __s1, __ix1, __q1;
	__int32_t __ix0, __s0, __q, __m, __t, __i;
	__LIBM_EXTRACT_WORDS(__ix0, __ix1, __x);

	/* take care of Inf and NaN */
	if ((__ix0 & 0x7ff00000) == 0x7ff00000) {
		return __x * __x + __x; /* sqrt(NaN)=NaN, sqrt(+inf)=+inf sqrt(-inf)=sNaN */
	}
	/* take care of zero */
	if (__ix0 <= 0) {
		if (((__ix0 & (~__sign)) | __ix1) == 0)
			return __x; /* sqrt(+-0) = +-0 */
		else if (__ix0 < 0) {
			return (__x - __x) / (__x - __x); /* sqrt(-ve) = sNaN */
		}
	}
	/* normalize x */
	__m = (__ix0 >> 20);
	if (__m == 0) { /* subnormal x */
		while (__ix0 == 0) {
			__m -= 21;
			__ix0 |= (__ix1 >> 11);
			__ix1 <<= 21;
		}
		for (__i = 0; (__ix0 & 0x00100000) == 0; __i++)
			__ix0 <<= 1;
		__m -= __i - 1;
		__ix0 |= (__ix1 >> (32 - __i));
		__ix1 <<= __i;
	}
	__m -= 1023; /* unbias exponent */
	__ix0 = (__ix0 & 0x000fffff) | 0x00100000;
	if (__m & 1) { /* odd m, double x to make it even */
		__ix0 += __ix0 + ((__ix1 & __sign) >> 31);
		__ix1 += __ix1;
	}
	__m >>= 1; /* m = [m/2] */

	/* generate sqrt(x) bit by bit */
	__ix0 += __ix0 + ((__ix1 & __sign) >> 31);
	__ix1 += __ix1;
	__q = __q1 = __s0 = __s1 = 0; /* [q,q1] = sqrt(x) */
	__r = 0x00200000; /* r = moving bit from right to left */

	while (__r != 0) {
		__t = __s0 + __r;
		if (__t <= __ix0) {
			__s0 = __t + __r;
			__ix0 -= __t;
			__q += __r;
		}
		__ix0 += __ix0 + ((__ix1 & __sign) >> 31);
		__ix1 += __ix1;
		__r >>= 1;
	}

	__r = __sign;
	while (__r != 0) {
		__t1 = __s1 + __r;
		__t  = __s0;
		if ((__t < __ix0) || ((__t == __ix0) && (__t1 <= __ix1))) {
			__s1 = __t1 + __r;
			if (((__t1 & __sign) == __sign) && (__s1 & __sign) == 0)
				__s0 += 1;
			__ix0 -= __t;
			if (__ix1 < __t1)
				__ix0 -= 1;
			__ix1 -= __t1;
			__q1 += __r;
		}
		__ix0 += __ix0 + ((__ix1 & __sign) >> 31);
		__ix1 += __ix1;
		__r >>= 1;
	}

	/* use floating add to find out rounding direction */
	if ((__ix0 | __ix1) != 0) {
		z = __LIBM_LOCAL_VALUE(one) - __LIBM_LOCAL_VALUE(tiny); /* trigger inexact flag */
		if (z >= __LIBM_LOCAL_VALUE(one)) {
			z = __LIBM_LOCAL_VALUE(one) + __LIBM_LOCAL_VALUE(tiny);
			if (__q1 == (__uint32_t)0xffffffff) {
				__q1 = 0;
				__q += 1;
			} else if (z > __LIBM_LOCAL_VALUE(one)) {
				if (__q1 == (__uint32_t)0xfffffffe)
					__q += 1;
				__q1 += 2;
			} else {
				__q1 += (__q1 & 1);
			}
		}
	}
	__ix0 = (__q >> 1) + 0x3fe00000;
	__ix1 = __q1 >> 1;
	if ((__q & 1) == 1)
		__ix1 |= __sign;
	__ix0 += (__m << 20);
	__LIBM_INSERT_WORDS(z, __ix0, __ix1);
	return z;
}

#endif /* __IEEE754_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBM_SQRT_H */
