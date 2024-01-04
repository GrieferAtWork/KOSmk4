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
#ifndef _LIBM_SQRT_H
#define _LIBM_SQRT_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/asm/sqrt.h>
#include <libm/fdlibm.h>

#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_sqrtl
#include <libm/isnan.h>
#include <libm/frexp.h>
#include <libm/ldexp.h>
#endif /* !__ieee854_sqrtl */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_sqrtf
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
#define __libm_onef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0))
#endif /* !__libm_onef_defined */
#ifndef __libm_tinyf_defined
#define __libm_tinyf_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, tinyf, __IEEE754_FLOAT_C(1.0e-30))
#endif /* !__libm_tinyf_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(sqrtf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_sqrtf)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __z;
	__uint32_t __r, __hx;
	__int32_t __ix, __s, __q, __m, __t, _i;
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	__hx = __ix & 0x7fffffff;
	/* take care of Inf and NaN */
	if (!__LIBM_FLT_UWORD_IS_FINITE(__hx))
		return __x * __x + __x; /* sqrt(NaN)=NaN, sqrt(+inf)=+inf sqrt(-inf)=sNaN */
	/* take care of zero and -ves */
	if (__LIBM_FLT_UWORD_IS_ZERO(__hx))
		return __x; /* sqrt(+-0) = +-0 */
	if (__ix < 0)
		return (__x - __x) / (__x - __x); /* sqrt(-ve) = sNaN */
	/* normalize x */
	__m = (__ix >> 23);
#ifndef _FLT_NO_DENORMALS
	if (__LIBM_FLT_UWORD_IS_SUBNORMAL(__hx)) { /* subnormal x */
		for (_i = 0; (__ix & 0x00800000L) == 0; _i++)
			__ix <<= 1;
		__m -= _i - 1;
	}
#endif /* !_FLT_NO_DENORMALS */
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
			if (__z > __LIBM_LOCAL_VALUE(onef)) {
				__q += 2;
			} else {
				__q += (__q & 1);
			}
		}
	}
	__ix = (__q >> 1) + 0x3f000000L;
	__ix += (__m << 23);
	__LIBM_SET_FLOAT_WORD(__z, __ix);
	return __z;
}
#endif /* !__ieee754_sqrtf */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_sqrt
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
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.0))
#endif /* !__libm_one_defined */
#ifndef __libm_tiny_defined
#define __libm_tiny_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, tiny, __IEEE754_DOUBLE_C(1.0e-300))
#endif /* !__libm_tiny_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(sqrt) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
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
		if (((__ix0 & (~__sign)) | __ix1) == 0) {
			return __x; /* sqrt(+-0) = +-0 */
		} else if (__ix0 < 0) {
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
#endif /* !__ieee754_sqrt */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_sqrtl
/* Emulation for sqrtl.
   Contributed by Paolo Bonzini

   Copyright 2002-2003, 2007, 2009-2013 Free Software Foundation, Inc.

   This file was taken from gnulib.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

__LIBM_LOCAL_FUNC(sqrtl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_sqrtl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __delta, __y;
	int __exponent;
	/* Check for NaN */
	if (__ieee854_isnanl(__x))
		return __x;
	/* Check for negative numbers */
	if (__x < __IEEE854_LONG_DOUBLE_C(0.0)) {
#ifdef __IEEE754_DOUBLE_C
		return (__IEEE854_LONG_DOUBLE_TYPE__)__ieee754_sqrt(__IEEE754_DOUBLE_C(-1.0));
#else /* __IEEE754_DOUBLE_C */
		return (__IEEE854_LONG_DOUBLE_TYPE__)__ieee754_sqrtf(__IEEE754_FLOAT_C(-1.0));
#endif /* !__IEEE754_DOUBLE_C */
	}
	/* Check for zero and infinites */
	if (__x + __x == __x)
		return __x;
	__ieee854_frexpl(__x, &__exponent);
	__y = __ieee854_ldexpl(__x, -__exponent / 2);
	do {
		__delta = __y;
		__y     = (__y + __x / __y) * 0.5L;
		__delta -= __y;
	} while (__delta != 0.0L);
	return __y;
}
#endif /* !__ieee854_sqrtl */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_SQRT_H */
