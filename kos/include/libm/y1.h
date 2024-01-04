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
#ifndef _LIBM_Y1_H
#define _LIBM_Y1_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/math-constants.h> /* TODO: Replace uses below with __IEEE754_ constants */
#include <bits/types.h>

#include <libm/cos.h>
#include <libm/fdlibm.h>
#include <libm/j1.h>
#include <libm/log.h>
#include <libm/pone.h>
#include <libm/sincos.h>
#include <libm/sqrt.h>

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
#ifndef __libm_zerof_defined
#define __libm_zerof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, zerof, __IEEE754_FLOAT_C(0.0000000000e+00)) /* 0x00000000 */
#endif /* !__libm_zerof_defined */
#ifndef __libm_onef_defined
#define __libm_onef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0000000000e+00)) /* 0x3F800000 */
#endif /* !__libm_onef_defined */
#ifndef __libm_invsqrtpif_defined
#define __libm_invsqrtpif_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, invsqrtpif, __IEEE754_FLOAT_C(5.6418961287e-01)) /* 0x3f106ebb */
#endif /* !__libm_invsqrtpif_defined */
#ifndef __libm_tpif_defined
#define __libm_tpif_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, tpif, __IEEE754_FLOAT_C(6.3661974669e-01)) /* 0x3f22f983 */
#endif /* !__libm_tpif_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y1_U00f, __IEEE754_FLOAT_C(-1.9605709612e-01)) /* 0xbe48c331 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y1_U01f, __IEEE754_FLOAT_C(5.0443872809e-02))  /* 0x3d4e9e3c */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y1_U02f, __IEEE754_FLOAT_C(-1.9125689287e-03)) /* 0xbafaaf2a */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y1_U03f, __IEEE754_FLOAT_C(2.3525259166e-05))  /* 0x37c5581c */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y1_U04f, __IEEE754_FLOAT_C(-9.1909917899e-08)) /* 0xb3c56003 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y1_V00f, __IEEE754_FLOAT_C(1.9916731864e-02))  /* 0x3ca3286a */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y1_V01f, __IEEE754_FLOAT_C(2.0255257550e-04))  /* 0x3954644b */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y1_V02f, __IEEE754_FLOAT_C(1.3560879779e-06))  /* 0x35b602d4 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y1_V03f, __IEEE754_FLOAT_C(6.2274145840e-09))  /* 0x31d5f8eb */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y1_V04f, __IEEE754_FLOAT_C(1.6655924903e-11))  /* 0x2d9281cf */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(y1f) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_y1f)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __z, __s, __c, __ss, __cc, __u, __v;
	__int32_t __hx, __ix;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __INT32_C(0x7fffffff) & __hx;
	/* if Y1(NaN) is NaN, Y1(-inf) is NaN, Y1(inf) is 0 */
	if (!__LIBM_FLT_UWORD_IS_FINITE(__ix))
		return __LIBM_LOCAL_VALUE(onef) / (__x + __x * __x);
	if (__LIBM_FLT_UWORD_IS_ZERO(__ix))
		return -__HUGE_VALF + __x; /* -inf and overflow exception.  */
	if (__hx < 0)
		return __LIBM_LOCAL_VALUE(zerof) / (__LIBM_LOCAL_VALUE(zerof) * __x);
	if (__ix >= __INT32_C(0x40000000)) { /* |x| >= 2.0 */
		__ieee754_sincosf(__x, &__s, &__c);
		__ss = -__s - __c;
		__cc = __s - __c;
		if (__ix <= __LIBM_FLT_UWORD_HALF_MAX) { /* make sure x+x not overflow */
			__z = __ieee754_cosf(__x + __x);
			if ((__s * __c) > __LIBM_LOCAL_VALUE(zerof)) {
				__cc = __z / __ss;
			} else {
				__ss = __z / __cc;
			}
		}

		/* y1(x) = sqrt(2/(pi*x))*(p1(x)*sin(x0)+q1(x)*cos(x0))
		 * where x0 = x-3pi/4
		 *      Better formula:
		 *              cos(x0) = cos(x)cos(3pi/4)+sin(x)sin(3pi/4)
		 *                      =  1/sqrt(2) * (sin(x) - cos(x))
		 *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
		 *                      = -1/sqrt(2) * (cos(x) + sin(x))
		 * To avoid cancellation, use
		 *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
		 * to compute the worse one. */
		if (__ix > __INT32_C(0x48000000)) {
			__z = (__LIBM_LOCAL_VALUE(invsqrtpif) * __ss) / __ieee754_sqrtf(__x);
		} else {
			__u = __ieee754_j1_y1_ponef(__x);
			__v = __ieee754_j1_y1_qonef(__x);
			__z = __LIBM_LOCAL_VALUE(invsqrtpif) * (__u * __ss + __v * __cc) / __ieee754_sqrtf(__x);
		}
		return __z;
	}
	if (__ix <= __INT32_C(0x33000000)) /* x < 2**-25 */
		return (-__LIBM_LOCAL_VALUE(tpif) / __x);
	__z = __x * __x;
	__u = __LIBM_LOCAL_VALUE(y1_U00f) +
	      __z * (__LIBM_LOCAL_VALUE(y1_U01f) +
	             __z * (__LIBM_LOCAL_VALUE(y1_U02f) +
	                    __z * (__LIBM_LOCAL_VALUE(y1_U03f) +
	                           __z * __LIBM_LOCAL_VALUE(y1_U04f))));
	__v = __LIBM_LOCAL_VALUE(onef) +
	      __z * (__LIBM_LOCAL_VALUE(y1_V00f) +
	             __z * (__LIBM_LOCAL_VALUE(y1_V01f) +
	                    __z * (__LIBM_LOCAL_VALUE(y1_V02f) +
	                           __z * (__LIBM_LOCAL_VALUE(y1_V03f) +
	                                  __z * __LIBM_LOCAL_VALUE(y1_V04f)))));
	return (__x * (__u / __v) +
	        __LIBM_LOCAL_VALUE(tpif) *
	        (__ieee754_j1f(__x) * __ieee754_logf(__x) -
	         __LIBM_LOCAL_VALUE(onef) / __x));
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
__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_zero_defined
#define __libm_zero_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, zero, __IEEE754_DOUBLE_C(0.00000000000000000000e+00)) /* 0x00000000, 0x00000000 */
#endif /* !__libm_zero_defined */
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.00000000000000000000e+00)) /* 0x3FF00000, 0x00000000 */
#endif /* !__libm_one_defined */
#ifndef __libm_invsqrtpi_defined
#define __libm_invsqrtpi_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, invsqrtpi, __IEEE754_DOUBLE_C(5.64189583547756279280e-01)) /* 0x3FE20DD7, 0x50429B6D */
#endif /* !__libm_invsqrtpi_defined */
#ifndef __libm_tpi_defined
#define __libm_tpi_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, tpi, __IEEE754_DOUBLE_C(6.36619772367581382433e-01)) /* 0x3FE45F30, 0x6DC9C883 */
#endif /* !__libm_tpi_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y1_U00, __IEEE754_DOUBLE_C(-1.96057090646238940668e-01)) /* 0xBFC91866, 0x143CBC8A */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y1_U01, __IEEE754_DOUBLE_C(5.04438716639811282616e-02))  /* 0x3FA9D3C7, 0x76292CD1 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y1_U02, __IEEE754_DOUBLE_C(-1.91256895875763547298e-03)) /* 0xBF5F55E5, 0x4844F50F */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y1_U03, __IEEE754_DOUBLE_C(2.35252600561610495928e-05))  /* 0x3EF8AB03, 0x8FA6B88E */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y1_U04, __IEEE754_DOUBLE_C(-9.19099158039878874504e-08)) /* 0xBE78AC00, 0x569105B8 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y1_V00, __IEEE754_DOUBLE_C(1.99167318236649903973e-02))  /* 0x3F94650D, 0x3F4DA9F0 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y1_V01, __IEEE754_DOUBLE_C(2.02552581025135171496e-04))  /* 0x3F2A8C89, 0x6C257764 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y1_V02, __IEEE754_DOUBLE_C(1.35608801097516229404e-06))  /* 0x3EB6C05A, 0x894E8CA6 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y1_V03, __IEEE754_DOUBLE_C(6.22741452364621501295e-09))  /* 0x3E3ABF1D, 0x5BA69A86 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y1_V04, __IEEE754_DOUBLE_C(1.66559246207992079114e-11))  /* 0x3DB25039, 0xDACA772A */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(y1) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_y1)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __z, __s, __c, __ss, __cc, __u, __v, __u1;
	__IEEE754_DOUBLE_TYPE__ __u2, __v1, __v2, __v3, __z2, __z4;
	__int32_t __hx, __ix, __lx;
	__LIBM_GET_DOUBLE_WORDS(__hx, __lx, __x);
	__ix = __INT32_C(0x7fffffff) & __hx;
	/* if Y1(NaN) is NaN, Y1(-inf) is NaN, Y1(inf) is 0 */
	if (__ix >= __INT32_C(0x7ff00000))
		return __LIBM_LOCAL_VALUE(one) / (__x + __x * __x);
	if ((__ix | __lx) == 0)
		return -__HUGE_VAL + __x; /* -inf and overflow exception.  */
	if (__hx < 0)
		return __LIBM_LOCAL_VALUE(zero) / __LIBM_LOCAL_VALUE(zero);
	if (__ix >= __INT32_C(0x40000000)) { /* |x| >= 2.0 */
		__ieee754_sincos(__x, &__s, &__c);
		__ss = -__s - __c;
		__cc = __s - __c;
		if (__ix < __INT32_C(0x7fe00000)) { /* make sure x+x not overflow */
			__z = __ieee754_cos(__x + __x);
			if ((__s * __c) > __LIBM_LOCAL_VALUE(zero)) {
				__cc = __z / __ss;
			} else {
				__ss = __z / __cc;
			}
		}

		/* y1(x) = sqrt(2/(pi*x))*(p1(x)*sin(x0)+q1(x)*cos(x0))
		 * where x0 = x-3pi/4
		 *      Better formula:
		 *              cos(x0) = cos(x)cos(3pi/4)+sin(x)sin(3pi/4)
		 *                      =  1/sqrt(2) * (sin(x) - cos(x))
		 *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
		 *                      = -1/sqrt(2) * (cos(x) + sin(x))
		 * To avoid cancellation, use
		 *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
		 * to compute the worse one. */
		if (__ix > __INT32_C(0x48000000)) {
			__z = (__LIBM_LOCAL_VALUE(invsqrtpi) * __ss) / __ieee754_sqrt(__x);
		} else {
			__u = __ieee754_j1_y1_pone(__x);
			__v = __ieee754_j1_y1_qone(__x);
			__z = __LIBM_LOCAL_VALUE(invsqrtpi) * (__u * __ss + __v * __cc) / __ieee754_sqrt(__x);
		}
		return __z;
	}
	if (__ix <= __INT32_C(0x3c900000)) /* x < 2**-54 */
		return (-__LIBM_LOCAL_VALUE(tpi) / __x);
	__z  = __x * __x;
	__u1 = __LIBM_LOCAL_VALUE(y1_U00) + __z * __LIBM_LOCAL_VALUE(y1_U01);
	__z2 = __z * __z;
	__u2 = __LIBM_LOCAL_VALUE(y1_U02) + __z * __LIBM_LOCAL_VALUE(y1_U03);
	__z4 = __z2 * __z2;
	__u  = __u1 + __z2 * __u2 + __z4 * __LIBM_LOCAL_VALUE(y1_U04);
	__v1 = __LIBM_LOCAL_VALUE(one) + __z * __LIBM_LOCAL_VALUE(y1_V00);
	__v2 = __LIBM_LOCAL_VALUE(y1_V01) + __z * __LIBM_LOCAL_VALUE(y1_V02);
	__v3 = __LIBM_LOCAL_VALUE(y1_V03) + __z * __LIBM_LOCAL_VALUE(y1_V04);
	__v  = __v1 + __z2 * __v2 + __z4 * __v3;
	return (__x * (__u / __v) +
	        __LIBM_LOCAL_VALUE(tpi) *
	        (__ieee754_j1(__x) * __ieee754_log(__x) -
	         __LIBM_LOCAL_VALUE(one) / __x));
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
__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_zerol_defined
#define __libm_zerol_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, zerol, __IEEE854_LONG_DOUBLE_C(0.0))
#endif /* !__libm_zerol_defined */
#ifndef __libm_onel_defined
#define __libm_onel_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, onel, __IEEE854_LONG_DOUBLE_C(1.0))
#endif /* !__libm_onel_defined */
#ifndef __libm_invsqrtpil_defined
#define __libm_invsqrtpil_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, invsqrtpil, __IEEE854_LONG_DOUBLE_C(5.6418958354775628694807945156077258584405e-1))
#endif /* !__libm_invsqrtpil_defined */
#ifndef __libm_tpil_defined
#define __libm_tpil_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, tpil, __IEEE854_LONG_DOUBLE_C(6.3661977236758134307553505349005744813784e-1))
#endif /* !__libm_tpil_defined */
/* Y1(x) = 2/pi * (log(x) * j1(x) - 1/x) + x R(x^2)  0 <= x <= 2  Peak relative error 2.3e-23 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y1_U00l, __IEEE854_LONG_DOUBLE_C(-5.908077186259914699178903164682444848615E10))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y1_U01l, __IEEE854_LONG_DOUBLE_C(1.546219327181478013495975514375773435962E10))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y1_U02l, __IEEE854_LONG_DOUBLE_C(-6.438303331169223128870035584107053228235E8))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y1_U03l, __IEEE854_LONG_DOUBLE_C(9.708540045657182600665968063824819371216E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y1_U04l, __IEEE854_LONG_DOUBLE_C(-6.138043997084355564619377183564196265471E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y1_U05l, __IEEE854_LONG_DOUBLE_C(1.418503228220927321096904291501161800215E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y1_V00l, __IEEE854_LONG_DOUBLE_C(3.013447341682896694781964795373783679861E11))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y1_V01l, __IEEE854_LONG_DOUBLE_C(4.669546565705981649470005402243136124523E9))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y1_V02l, __IEEE854_LONG_DOUBLE_C(3.595056091631351184676890179233695857260E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y1_V03l, __IEEE854_LONG_DOUBLE_C(1.761554028569108722903944659933744317994E5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y1_V04l, __IEEE854_LONG_DOUBLE_C(5.668480419646516568875555062047234534863E2))
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(y1l) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_y1l)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __z, __s, __c, __ss, __cc, __u, __v;
	__int32_t __ix;
	__uint32_t __se, __i0, __i1;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__ix = __se & IEEE854_LONG_DOUBLE_MAXEXP;
	/* if Y1(NaN) is NaN, Y1(-inf) is NaN, Y1(inf) is 0 */
	if (__se & 0x8000)
		return __LIBM_LOCAL_VALUE(zerol) / (__LIBM_LOCAL_VALUE(zerol) * __x);
	if (__ix >= IEEE854_LONG_DOUBLE_MAXEXP)
		return __LIBM_LOCAL_VALUE(onel) / (__x + __x * __x);
	if ((__i0 | __i1) == 0)
		return -__HUGE_VALL + __x; /* -inf and overflow exception.  */
	if (__ix >= 0x4000) {        /* |x| >= 2.0 */
		__ieee854_sincosl(__x, &__s, &__c);
		__ss = -__s - __c;
		__cc = __s - __c;
		if (__ix < 0x7ffe) { /* make sure x+x not overflow */
			__z = __ieee854_cosl(__x + __x);
			if ((__s * __c) > __LIBM_LOCAL_VALUE(zerol)) {
				__cc = __z / __ss;
			} else {
				__ss = __z / __cc;
			}
		}

		/* y1(x) = sqrt(2/(pi*x))*(p1(x)*sin(x0)+q1(x)*cos(x0))
		 * where x0 = x-3pi/4
		 *      Better formula:
		 *              cos(x0) = cos(x)cos(3pi/4)+sin(x)sin(3pi/4)
		 *                      =  1/sqrt(2) * (sin(x) - cos(x))
		 *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
		 *                      = -1/sqrt(2) * (cos(x) + sin(x))
		 * To avoid cancellation, use
		 *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
		 * to compute the worse one. */
		if (__ix > 0x4080) {
			__z = (__LIBM_LOCAL_VALUE(invsqrtpil) * __ss) / __ieee854_sqrtl(__x);
		} else {
			__u = __ieee854_j1_y1_ponel(__x);
			__v = __ieee854_j1_y1_qonel(__x);
			__z = __LIBM_LOCAL_VALUE(invsqrtpil) * (__u * __ss + __v * __cc) / __ieee854_sqrtl(__x);
		}
		return __z;
	}
	if (__ix <= 0x3fbe) /* x < 2**-65 */
		return (-__LIBM_LOCAL_VALUE(tpil) / __x);
	__z = __x * __x;
	__u = __LIBM_LOCAL_VALUE(y1_U00l) +
	      __z * (__LIBM_LOCAL_VALUE(y1_U01l) +
	             __z * (__LIBM_LOCAL_VALUE(y1_U02l) +
	                    __z * (__LIBM_LOCAL_VALUE(y1_U03l) +
	                           __z * (__LIBM_LOCAL_VALUE(y1_U04l) +
	                                  __z * __LIBM_LOCAL_VALUE(y1_U05l)))));
	__v = __LIBM_LOCAL_VALUE(y1_V00l) +
	      __z * (__LIBM_LOCAL_VALUE(y1_V01l) +
	             __z * (__LIBM_LOCAL_VALUE(y1_V02l) +
	                    __z * (__LIBM_LOCAL_VALUE(y1_V03l) +
	                           __z * (__LIBM_LOCAL_VALUE(y1_V04l) +
	                                  __z))));
	return (__x * (__u / __v) +
	        __LIBM_LOCAL_VALUE(tpil) *
	        (__ieee854_j1l(__x) * __ieee854_logl(__x) -
	         __LIBM_LOCAL_VALUE(onel) / __x));
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_Y1_H */
