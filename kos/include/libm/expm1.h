/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBM_EXPM1_H
#define _LIBM_EXPM1_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/crt/fenv.h>
#include <bits/types.h>

#include <libm/asm/expm1.h>
#include <libm/floor.h>
#include <libm/ldexp.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_expm1f
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
#ifndef __libm_hugef_defined
#define __libm_hugef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, hugef, __IEEE754_FLOAT_C(1.0e30))
#endif /* !__libm_hugef_defined */
#ifndef __libm_onef_defined
#define __libm_onef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0))
#endif /* !__libm_onef_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, o_thresholdf, __IEEE754_FLOAT_C(8.8721679688e+01)) /* 0x42b17180 */
#ifndef __libm_ln2_hif_defined
#define __libm_ln2_hif_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, ln2_hif, __IEEE754_FLOAT_C(6.9313812256e-01))      /* 0x3f317180 */
#endif /* !__libm_ln2_hif_defined */
#ifndef __libm_ln2_lof_defined
#define __libm_ln2_lof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, ln2_lof, __IEEE754_FLOAT_C(9.0580006145e-06))      /* 0x3717f7d1 */
#endif /* !__libm_ln2_lof_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, invln2f, __IEEE754_FLOAT_C(1.4426950216e+00))      /* 0x3fb8aa3b */
/* scaled coefficients related to expm1 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Q1f, __IEEE754_FLOAT_C(-3.3333335072e-02)) /* 0xbd088889 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Q2f, __IEEE754_FLOAT_C(1.5873016091e-03))  /* 0x3ad00d01 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Q3f, __IEEE754_FLOAT_C(-7.9365076090e-05)) /* 0xb8a670cd */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Q4f, __IEEE754_FLOAT_C(4.0082177293e-06))  /* 0x36867e54 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Q5f, __IEEE754_FLOAT_C(-2.0109921195e-07)) /* 0xb457edbb */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_expm1f)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __y, __hi, __lo, __c, __t;
	__IEEE754_FLOAT_TYPE__ __e, __hxs, __hfx, __r1;
	__int32_t __k, __xsb;
	__uint32_t __hx;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__xsb = __hx & __UINT32_C(0x80000000); /* sign bit of x */
	if (__xsb == 0)
		__y = __x;
	else {
		__y = -__x; /* y = |x| */
	}
	__hx &= __UINT32_C(0x7fffffff); /* high word of |x| */
	/* filter out huge and non-finite argument */
	if (__hx >= __UINT32_C(0x4195b844)) {     /* if |x| >= 27 * ln2 */
		if (__hx >= __UINT32_C(0x42b17218)) { /* if |x| >= 88.721... */
			if (__hx > __UINT32_C(0x7f800000))
				return __x + __x; /* NaN */
			if (__hx == __UINT32_C(0x7f800000))
				return (__xsb == 0) ? __x : -__LIBM_LOCAL_VALUE(onef); /* exp(+-inf) = {inf, -1} */
			if (__x > __LIBM_LOCAL_VALUE(o_thresholdf)) {
				__libc_feraiseexcept(FE_OVERFLOW);
				return __ieee754_inff(); /* overflow */
			}
		}
		if (__xsb != 0) {                     /* x < -27 * ln2, return -1.0 with inexact */
			__libc_feraiseexcept(FE_INEXACT); /* raise inexact */
			return -__LIBM_LOCAL_VALUE(onef); /* return -1 */
		}
	}

	/* argument reduction */
	if (__hx > __UINT32_C(0x3eb17218)) {     /* if  |x| > 0.5 ln2 */
		if (__hx < __UINT32_C(0x3F851592)) { /* and |x| < 1.5 ln2 */
			if (__xsb == 0) {
				__hi = __x - __LIBM_LOCAL_VALUE(ln2_hif);
				__lo = __LIBM_LOCAL_VALUE(ln2_lof);
				__k  = 1;
			} else {
				__hi = __x + __LIBM_LOCAL_VALUE(ln2_hif);
				__lo = -__LIBM_LOCAL_VALUE(ln2_lof);
				__k  = -1;
			}
		} else {
			__k  = __LIBM_LOCAL_VALUE(invln2f) * __x + ((__xsb == 0) ? __IEEE754_FLOAT_C(0.5) : -__IEEE754_FLOAT_C(0.5));
			__t  = __k;
			__hi = __x - __t * __LIBM_LOCAL_VALUE(ln2_hif); /* t*ln2_hi is exact here */
			__lo = __t * __LIBM_LOCAL_VALUE(ln2_lof);
		}
		__x = __hi - __lo;
		__c = (__hi - __x) - __lo;
	} else if (__hx < __UINT32_C(0x33000000)) { /* when |x| < 2 ** -25, return x */
		__t = __LIBM_LOCAL_VALUE(hugef) + __x;  /* return x with inexact flags when x != 0 */
		return __x - (__t - (__LIBM_LOCAL_VALUE(hugef) + __x));
	} else {
		__k = 0;
		__c = 0;
	}
	/* x is now in primary range */
	__hfx = __IEEE754_FLOAT_C(0.5) * __x;
	__hxs = __x * __hfx;
	__r1  = __LIBM_LOCAL_VALUE(onef) +
	       __hxs * (__LIBM_LOCAL_VALUE(Q1f) +
	                __hxs * (__LIBM_LOCAL_VALUE(Q2f) +
	                         __hxs * (__LIBM_LOCAL_VALUE(Q3f) +
	                                  __hxs * (__LIBM_LOCAL_VALUE(Q4f) +
	                                           __hxs * __LIBM_LOCAL_VALUE(Q5f)))));
	__t   = __IEEE754_FLOAT_C(3.0) - __r1 * __hfx;
	__e   = __hxs * ((__r1 - __t) / (__IEEE754_FLOAT_C(6.0) - __x * __t));
	if (__k == 0)
		return __x - (__x * __e - __hxs); /* c is 0 */
	else {
		__e = (__x * (__e - __c) - __c);
		__e -= __hxs;
		if (__k == -1)
			return __IEEE754_FLOAT_C(0.5) * (__x - __e) - __IEEE754_FLOAT_C(0.5);

		if (__k == 1) {
			if (__x < -__IEEE754_FLOAT_C(0.25))
				return -__IEEE754_FLOAT_C(2.0) * (__e - (__x + __IEEE754_FLOAT_C(0.5)));
			else {
				return __LIBM_LOCAL_VALUE(onef) +
				       __IEEE754_FLOAT_C(2.0) * (__x - __e);
			}
		}
		if (__k <= -2 || __k > 56) { /* suffice to return exp(x)-1 */
			__int32_t __i;
			__y = __LIBM_LOCAL_VALUE(onef) - (__e - __x);
			__LIBM_GET_FLOAT_WORD(__i, __y);
			__LIBM_SET_FLOAT_WORD(__y, __i + (__k << 23)); /* add k to y's exponent */
			return __y - __LIBM_LOCAL_VALUE(onef);
		}
		__t = __LIBM_LOCAL_VALUE(onef);
		if (__k < 23) {
			__int32_t __i;
			__LIBM_SET_FLOAT_WORD(__t, __UINT32_C(0x3f800000) - (__UINT32_C(0x1000000) >> __k)); /* t=1-2^-k */
			__y = __t - (__e - __x);
			__LIBM_GET_FLOAT_WORD(__i, __y);
			__LIBM_SET_FLOAT_WORD(__y, __i + (__k << 23)); /* add k to y's exponent */
		} else {
			__int32_t __i;
			__LIBM_SET_FLOAT_WORD(__t, ((__UINT32_C(0x7f) - __k) << 23)); /* 2^-k */
			__y = __x - (__e + __t);
			__y += __LIBM_LOCAL_VALUE(onef);
			__LIBM_GET_FLOAT_WORD(__i, __y);
			__LIBM_SET_FLOAT_WORD(__y, __i + (__k << 23)); /* add k to y's exponent */
		}
	}
	return __y;
}
#endif /* !__ieee754_expm1f */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_expm1
/*
 * ====================================================
 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_huge_defined
#define __libm_huge_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, huge, __IEEE754_DOUBLE_C(1.0e300))
#endif /* !__libm_huge_defined */
#ifndef __libm_o_threshold_defined
#define __libm_o_threshold_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, o_threshold, __IEEE754_DOUBLE_C(7.09782712893383973096e+02)) /* 0x40862E42, 0xFEFA39EF */
#endif /* !__libm_o_threshold_defined */
#ifndef __libm_ln2_hi_defined
#define __libm_ln2_hi_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, ln2_hi, __IEEE754_DOUBLE_C(6.93147180369123816490e-01)) /* 0x3fe62e42, 0xfee00000 */
#endif /* !__libm_ln2_hi_defined */
#ifndef __libm_ln2_lo_defined
#define __libm_ln2_lo_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, ln2_lo, __IEEE754_DOUBLE_C(1.90821492927058770002e-10)) /* 0x3dea39ef, 0x35793c76 */
#endif /* !__libm_ln2_lo_defined */
#ifndef __libm_invln2_defined
#define __libm_invln2_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, invln2, __IEEE754_DOUBLE_C(1.44269504088896338700e+00)) /* 0x3ff71547, 0x652b82fe */
#endif /* !__libm_invln2_defined */
/* scaled coefficients related to expm1 */
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, Q, 6) {
	__IEEE754_DOUBLE_C(1.0),
	__IEEE754_DOUBLE_C(-3.33333333333331316428e-02), /* BFA11111 111110F4 */
	__IEEE754_DOUBLE_C(1.58730158725481460165e-03),  /* 3F5A01A0 19FE5585 */
	__IEEE754_DOUBLE_C(-7.93650757867487942473e-05), /* BF14CE19 9EAADBB7 */
	__IEEE754_DOUBLE_C(4.00821782732936239552e-06),  /* 3ED0CFCA 86E65239 */
	__IEEE754_DOUBLE_C(-2.01099218183624371326e-07)  /* BE8AFDB7 6E09C32D */
};
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_expm1)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __y, __hi, __lo, __c, __t, __e, __hxs;
	__IEEE754_DOUBLE_TYPE__ __hfx, __r1, __h2, __h4, __R1, __R2, __R3;
	__int32_t __k, __xsb;
	__uint32_t __hx;
	__LIBM_GET_HIGH_WORD(__hx, __x);
	__xsb = __hx & __INT32_C(0x80000000); /* sign bit of x */
	if (__xsb == 0)
		__y = __x;
	else {
		__y = -__x; /* y = |x| */
	}
	__hx &= __UINT32_C(0x7fffffff); /* high word of |x| */
	/* filter out hugeval and non-finite argument */
	if (__hx >= __UINT32_C(0x4043687A)) {     /* if |x| >= 56 * ln2 */
		if (__hx >= __UINT32_C(0x40862E42)) { /* if |x| >= 709.78... */
			if (__hx >= __UINT32_C(0x7ff00000)) {
				__uint32_t __low;
				__LIBM_GET_LOW_WORD(__low, __x);
				if (((__hx & __UINT32_C(0xfffff)) | __low) != 0)
					return __x + __x; /* NaN */
				return __xsb == 0
				       ? __x /* exp(+-inf) = {inf, -1} */
				       : -__LIBM_LOCAL_VALUE(Q)[0];
			}
			if (__x > __LIBM_LOCAL_VALUE(o_threshold)) {
				__libc_feraiseexcept(FE_OVERFLOW);
				return __ieee754_inf(); /* overflow */
			}
		}
		if (__xsb != 0) {                     /* x < -56 * ln2, return -1.0 with inexact */
			__libc_feraiseexcept(FE_INEXACT); /* raise inexact */
			return -__LIBM_LOCAL_VALUE(Q)[0]; /* return -1 */
		}
	}

	/* argument reduction */
	if (__hx > __UINT32_C(0x3fd62e42)) {     /* if  |x| > 0.5 ln2 */
		if (__hx < __UINT32_C(0x3FF0A2B2)) { /* and |x| < 1.5 ln2 */
			if (__xsb == 0) {
				__hi = __x - __LIBM_LOCAL_VALUE(ln2_hi);
				__lo = __LIBM_LOCAL_VALUE(ln2_lo);
				__k  = 1;
			} else {
				__hi = __x + __LIBM_LOCAL_VALUE(ln2_hi);
				__lo = -__LIBM_LOCAL_VALUE(ln2_lo);
				__k  = -1;
			}
		} else {
			__k  = __LIBM_LOCAL_VALUE(invln2) * __x + ((__xsb == 0) ? 0.5 : -0.5);
			__t  = __k;
			__hi = __x - __t * __LIBM_LOCAL_VALUE(ln2_hi); /* t*ln2_hi is exact here */
			__lo = __t * __LIBM_LOCAL_VALUE(ln2_lo);
		}
		__x = __hi - __lo;
		__c = (__hi - __x) - __lo;
	} else if (__hx < __UINT32_C(0x3c900000)) { /* when |x| < 2 ** -54, return x */
		__t = __LIBM_LOCAL_VALUE(huge) + __x;   /* return x with inexact flags when x != 0 */
		return __x - (__t - (__LIBM_LOCAL_VALUE(huge) + __x));
	} else {
		__k = 0;
		__c = 0;
	}

	/* x is now in primary range */
	__hfx = 0.5 * __x;
	__hxs = __x * __hfx;
	__R1 = __LIBM_LOCAL_VALUE(Q)[0] + __hxs * __LIBM_LOCAL_VALUE(Q)[1];
	__h2 = __hxs * __hxs;
	__R2 = __LIBM_LOCAL_VALUE(Q)[2] + __hxs * __LIBM_LOCAL_VALUE(Q)[3];
	__h4 = __h2 * __h2;
	__R3 = __LIBM_LOCAL_VALUE(Q)[4] + __hxs * __LIBM_LOCAL_VALUE(Q)[5];
	__r1 = __R1 + __h2 * __R2 + __h4 * __R3;
	__t = 3.0 - __r1 * __hfx;
	__e = __hxs * ((__r1 - __t) / (6.0 - __x * __t));
	if (__k == 0)
		return __x - (__x * __e - __hxs); /* c is 0 */
	else {
		__e = (__x * (__e - __c) - __c);
		__e -= __hxs;
		if (__k == -1)
			return 0.5 * (__x - __e) - 0.5;
		if (__k == 1) {
			if (__x < -0.25)
				return -2.0 * (__e - (__x + 0.5));
			else {
				return __LIBM_LOCAL_VALUE(Q)[0] + 2.0 * (__x - __e);
			}
		}
		if (__k <= -2 || __k > 56) { /* suffice to return exp(x)-1 */
			__uint32_t __high;
			__y = __LIBM_LOCAL_VALUE(Q)[0] - (__e - __x);
			__LIBM_GET_HIGH_WORD(__high, __y);
			__LIBM_SET_HIGH_WORD(__y, __high + (__k << 20)); /* add k to y's exponent */
			return __y - __LIBM_LOCAL_VALUE(Q)[0];
		}
		__t = __LIBM_LOCAL_VALUE(Q)[0];
		if (__k < 20) {
			__uint32_t __high;
			__LIBM_SET_HIGH_WORD(__t, __UINT32_C(0x3ff00000) - (__UINT32_C(0x200000) >> __k)); /* t=1-2^-k */
			__y = __t - (__e - __x);
			__LIBM_GET_HIGH_WORD(__high, __y);
			__LIBM_SET_HIGH_WORD(__y, __high + (__k << 20)); /* add k to y's exponent */
		} else {
			__uint32_t __high;
			__LIBM_SET_HIGH_WORD(__t, ((__UINT32_C(0x3ff) - __k) << 20)); /* 2^-k */
			__y = __x - (__e + __t);
			__y += __LIBM_LOCAL_VALUE(Q)[0];
			__LIBM_GET_HIGH_WORD(__high, __y);
			__LIBM_SET_HIGH_WORD(__y, __high + (__k << 20)); /* add k to y's exponent */
		}
	}
	return __y;
}
#endif /* !__ieee754_expm1 */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_expm1l
/* Copyright 2001 by Stephen L. Moshier

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, see
    <http://www.gnu.org/licenses/>.  */

__LIBM_LOCAL_DECLARE_BEGIN
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, P0l, __IEEE854_LONG_DOUBLE_C(2.943520915569954073888921213330863757240E8))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, P1l, __IEEE854_LONG_DOUBLE_C(-5.722847283900608941516165725053359168840E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, P2l, __IEEE854_LONG_DOUBLE_C(8.944630806357575461578107295909719817253E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, P3l, __IEEE854_LONG_DOUBLE_C(-7.212432713558031519943281748462837065308E5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, P4l, __IEEE854_LONG_DOUBLE_C(4.578962475841642634225390068461943438441E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, P5l, __IEEE854_LONG_DOUBLE_C(-1.716772506388927649032068540558788106762E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, P6l, __IEEE854_LONG_DOUBLE_C(4.401308817383362136048032038528753151144E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, P7l, __IEEE854_LONG_DOUBLE_C(-4.888737542888633647784737721812546636240E-1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, Q0l, __IEEE854_LONG_DOUBLE_C(1.766112549341972444333352727998584753865E9))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, Q1l, __IEEE854_LONG_DOUBLE_C(-7.848989743695296475743081255027098295771E8))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, Q2l, __IEEE854_LONG_DOUBLE_C(1.615869009634292424463780387327037251069E8))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, Q3l, __IEEE854_LONG_DOUBLE_C(-2.019684072836541751428967854947019415698E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, Q4l, __IEEE854_LONG_DOUBLE_C(1.682912729190313538934190635536631941751E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, Q5l, __IEEE854_LONG_DOUBLE_C(-9.615511549171441430850103489315371768998E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, Q6l, __IEEE854_LONG_DOUBLE_C(3.697714952261803935521187272204485251835E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, Q7l, __IEEE854_LONG_DOUBLE_C(-8.802340681794263968892934703309274564037E1))
/* Q8 = 1.000000000000000000000000000000000000000E0 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, C1l, __IEEE854_LONG_DOUBLE_C(6.93145751953125E-1)) /* C1 + C2 = ln 2 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, C2l, __IEEE854_LONG_DOUBLE_C(1.428606820309417232121458176568075500134E-6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, maxlogl, __IEEE854_LONG_DOUBLE_C(1.1356523406294143949491931077970764891253E4)) /* ln (2^16384 * (1 - 2^-113)) */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, minargl, __IEEE854_LONG_DOUBLE_C(-7.9018778583833765273564461846232128760607E1)) /* ln 2^-114 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, bigl, __IEEE854_LONG_DOUBLE_C(1e4932))
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_expm1l)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __px, __qx, __xx;
	__int32_t __ix, __sign;
	__uint32_t __msw, __lsw;
	__int32_t __k;
	/* Detect infinity and NaN.  */
	__LIBM_GET_LDOUBLE_WORDS(__ix, __msw, __lsw, __x);
	__sign = __ix & 0x8000;
	__ix &= 0x7fff;
	__lsw |= __msw & __INT32_C(0x7fffffff);
	if (__ix >= 0x7fff) {
		/* Infinity. */
		if (__lsw == 0) {
			if (__sign)
				return -1.0L;
			else {
				return __x;
			}
		}
		/* NaN. No invalid exception. */
		return __x;
	}
	/* expm1(+- 0) = +- 0.  */
	if (__ix == 0 && __lsw == 0)
		return __x;
	/* Overflow.  */
	if (__x > __LIBM_LOCAL_VALUE(maxlogl)) {
		__libc_feraiseexcept(FE_OVERFLOW);
		return __ieee854_infl();
	}
	/* Minimum value.  */
	if (__x < __LIBM_LOCAL_VALUE(minargl)) {
		return (__IEEE854_LONG_DOUBLE_C(4.0) / __LIBM_LOCAL_VALUE(bigl) -
		        __IEEE854_LONG_DOUBLE_C(1.0));
	}
	/* Express x = ln 2 (k + remainder), remainder not exceeding 1/2. */
	__xx = __LIBM_LOCAL_VALUE(C1l) + __LIBM_LOCAL_VALUE(C2l); /* ln 2. */
	__px = __ieee854_floorl(__IEEE854_LONG_DOUBLE_C(0.5) + __x / __xx);
	__k  = __px;
	/* remainder times ln 2 */
	__x -= __px * __LIBM_LOCAL_VALUE(C1l);
	__x -= __px * __LIBM_LOCAL_VALUE(C2l);
	/* Approximate exp(remainder ln 2).  */
	__px = (((((((__LIBM_LOCAL_VALUE(P7l) * __x +
	              __LIBM_LOCAL_VALUE(P6l)) *
	             __x +
	             __LIBM_LOCAL_VALUE(P5l)) *
	            __x +
	            __LIBM_LOCAL_VALUE(P4l)) *
	           __x +
	           __LIBM_LOCAL_VALUE(P3l)) *
	          __x +
	          __LIBM_LOCAL_VALUE(P2l)) *
	         __x +
	         __LIBM_LOCAL_VALUE(P1l)) *
	        __x +
	        __LIBM_LOCAL_VALUE(P0l)) *
	       __x;
	__qx = (((((((__x +
	              __LIBM_LOCAL_VALUE(Q7l)) *
	             __x +
	             __LIBM_LOCAL_VALUE(Q6l)) *
	            __x +
	            __LIBM_LOCAL_VALUE(Q5l)) *
	           __x +
	           __LIBM_LOCAL_VALUE(Q4l)) *
	          __x +
	          __LIBM_LOCAL_VALUE(Q3l)) *
	         __x +
	         __LIBM_LOCAL_VALUE(Q2l)) *
	        __x +
	        __LIBM_LOCAL_VALUE(Q1l)) *
	       __x +
	       __LIBM_LOCAL_VALUE(Q0l);
	__xx = __x * __x;
	__qx = __x + (__IEEE854_LONG_DOUBLE_C(0.5) * __xx + __xx * __px / __qx);
	/* exp(x) = exp(k ln 2) exp(remainder ln 2) = 2^k exp(remainder ln 2).
	 * We have qx = exp(remainder ln 2) - 1, so
	 * exp(x) - 1 = 2^k (qx + 1) - 1
	 * = 2^k qx + 2^k - 1. */
	if (__k == 16384) {
		__px = __ieee854_ldexpl(__IEEE854_LONG_DOUBLE_C(1.0), (int)__k - 2);
		__x  = (__px * __qx + (__px - __IEEE854_LONG_DOUBLE_C(0.25))) * __IEEE854_LONG_DOUBLE_C(4.0);
	} else {
		__px = __ieee854_ldexpl(__IEEE854_LONG_DOUBLE_C(1.0), (int)__k);
		__x  = __px * __qx + (__px - __IEEE854_LONG_DOUBLE_C(1.0));
	}
	return __x;
}
#endif /* !__ieee854_expm1l */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_EXPM1_H */
