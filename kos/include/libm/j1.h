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
#ifndef _LIBM_J1_H
#define _LIBM_J1_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/math-constants.h> /* TODO: Replace uses below with __IEEE754_ constants */
#include <bits/types.h>

#include <libm/cos.h>
#include <libm/fabs.h>
#include <libm/fdlibm.h>
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
#ifndef __libm_hugevalf_defined
#define __libm_hugevalf_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, hugevalf, __IEEE754_FLOAT_C(1.0000000000e+30))
#endif /* !__libm_hugevalf_defined */
/* R0/S0 on [0,2] */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j1_r00f, __IEEE754_FLOAT_C(-6.2500000000e-02)) /* 0xbd800000 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j1_r01f, __IEEE754_FLOAT_C(1.4070566976e-03))  /* 0x3ab86cfd */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j1_r02f, __IEEE754_FLOAT_C(-1.5995563444e-05)) /* 0xb7862e36 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j1_r03f, __IEEE754_FLOAT_C(4.9672799207e-08))  /* 0x335557d2 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j1_s01f, __IEEE754_FLOAT_C(1.9153760746e-02))  /* 0x3c9ce859 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j1_s02f, __IEEE754_FLOAT_C(1.8594678841e-04))  /* 0x3942fab6 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j1_s03f, __IEEE754_FLOAT_C(1.1771846857e-06))  /* 0x359dffc2 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j1_s04f, __IEEE754_FLOAT_C(5.0463624390e-09))  /* 0x31ad6446 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j1_s05f, __IEEE754_FLOAT_C(1.2354227016e-11))  /* 0x2d59567e */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(j1f) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_j1f)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __z, __s, __c, __ss, __cc;
	__IEEE754_FLOAT_TYPE__ __r, __u, __v, __y;
	__int32_t __hx, __ix;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (!__LIBM_FLT_UWORD_IS_FINITE(__ix))
		return __LIBM_LOCAL_VALUE(onef) / __x;
	__y = __ieee754_fabsf(__x);
	if (__ix >= __INT32_C(0x40000000)) { /* |x| >= 2.0 */
		__ieee754_sincosf(__y, &__s, &__c);
		__ss = -__s - __c;
		__cc = __s - __c;
		if (__ix <= __LIBM_FLT_UWORD_HALF_MAX) { /* make sure y+y not overflow */
			__z = __ieee754_cosf(__y + __y);
			if ((__s * __c) > __LIBM_LOCAL_VALUE(zerof)) {
				__cc = __z / __ss;
			} else {
				__ss = __z / __cc;
			}
		}

		/* j1(x) = 1/sqrt(pi) * (P(1,x)*cc - Q(1,x)*ss) / sqrt(x)
		 * y1(x) = 1/sqrt(pi) * (P(1,x)*ss + Q(1,x)*cc) / sqrt(x) */
		if (__ix > __INT32_C(0x48000000)) {
			__z = (__LIBM_LOCAL_VALUE(invsqrtpif) * __cc) / __ieee754_sqrtf(__y);
		} else {
			__u = __ieee754_j1_y1_ponef(__y);
			__v = __ieee754_j1_y1_qonef(__y);
			__z = __LIBM_LOCAL_VALUE(invsqrtpif) * (__u * __cc - __v * __ss) / __ieee754_sqrtf(__y);
		}
		if (__hx < 0) {
			return -__z;
		} else {
			return __z;
		}
	}
	if (__ix < __INT32_C(0x32000000)) { /* |x|<2**-27 */
		if (__LIBM_LOCAL_VALUE(hugevalf) + __x > __LIBM_LOCAL_VALUE(onef))
			return __IEEE754_FLOAT_C(0.5) * __x; /* inexact if x!=0 necessary */
	}
	__z = __x * __x;
	__r = __z * (__LIBM_LOCAL_VALUE(j1_r00f) +
	             __z * (__LIBM_LOCAL_VALUE(j1_r01f) +
	                    __z * (__LIBM_LOCAL_VALUE(j1_r02f) +
	                           __z * __LIBM_LOCAL_VALUE(j1_r03f))));
	__s = __LIBM_LOCAL_VALUE(onef) +
	      __z * (__LIBM_LOCAL_VALUE(j1_s01f) +
	             __z * (__LIBM_LOCAL_VALUE(j1_s02f) +
	                    __z * (__LIBM_LOCAL_VALUE(j1_s03f) +
	                           __z * (__LIBM_LOCAL_VALUE(j1_s04f) +
	                                  __z * __LIBM_LOCAL_VALUE(j1_s05f)))));
	__r *= __x;
	return (__x * __IEEE754_FLOAT_C(0.5) + __r / __s);
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
#ifndef __libm_hugeval_defined
#define __libm_hugeval_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, hugeval, __IEEE754_DOUBLE_C(1.00000000000000000000e+300))
#endif /* !__libm_hugeval_defined */
#ifndef __libm_invsqrtpi_defined
#define __libm_invsqrtpi_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, invsqrtpi, __IEEE754_DOUBLE_C(5.64189583547756279280e-01)) /* 0x3FE20DD7, 0x50429B6D */
#endif /* !__libm_invsqrtpi_defined */
/* R0/S0 on [0,2] */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j1_r00, __IEEE754_DOUBLE_C(-6.25000000000000000000e-02)) /* 0xBFB00000, 0x00000000 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j1_r01, __IEEE754_DOUBLE_C(1.40705666955189706048e-03))  /* 0x3F570D9F, 0x98472C61 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j1_r02, __IEEE754_DOUBLE_C(-1.59955631084035597520e-05)) /* 0xBEF0C5C6, 0xBA169668 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j1_r03, __IEEE754_DOUBLE_C(4.96727999609584448412e-08))  /* 0x3E6AAAFA, 0x46CA0BD9 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j1_s01, __IEEE754_DOUBLE_C(1.91537599538363460805e-02))  /* 0x3F939D0B, 0x12637E53 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j1_s02, __IEEE754_DOUBLE_C(1.85946785588630915560e-04))  /* 0x3F285F56, 0xB9CDF664 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j1_s03, __IEEE754_DOUBLE_C(1.17718464042623683263e-06))  /* 0x3EB3BFF8, 0x333F8498 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j1_s04, __IEEE754_DOUBLE_C(5.04636257076217042715e-09))  /* 0x3E35AC88, 0xC97DFF2C */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j1_s05, __IEEE754_DOUBLE_C(1.23542274426137913908e-11))  /* 0x3DAB2ACF, 0xCFB97ED8 */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(j1) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_j1)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __z, __s, __c, __ss, __cc, __r, __u, __v;
	__IEEE754_DOUBLE_TYPE__ __y, __r1, __r2, __s1, __s2, __s3, __z2, __z4;
	__int32_t __hx, __ix;
	__LIBM_GET_HIGH_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix >= __INT32_C(0x7ff00000))
		return __LIBM_LOCAL_VALUE(one) / __x;
	__y = __ieee754_fabs(__x);
	if (__ix >= __INT32_C(0x40000000)) { /* |x| >= 2.0 */
		__ieee754_sincos(__y, &__s, &__c);
		__ss = -__s - __c;
		__cc = __s - __c;
		if (__ix < __INT32_C(0x7fe00000)) { /* make sure y+y not overflow */
			__z = __ieee754_cos(__y + __y);
			if ((__s * __c) > __LIBM_LOCAL_VALUE(zero)) {
				__cc = __z / __ss;
			} else {
				__ss = __z / __cc;
			}
		}

		/* j1(x) = 1/sqrt(pi) * (P(1,x)*cc - Q(1,x)*ss) / sqrt(x)
		 * y1(x) = 1/sqrt(pi) * (P(1,x)*ss + Q(1,x)*cc) / sqrt(x) */
		if (__ix > __INT32_C(0x48000000)) {
			__z = (__LIBM_LOCAL_VALUE(invsqrtpi) * __cc) / __ieee754_sqrt(__y);
		} else {
			__u = __ieee754_j1_y1_pone(__y);
			__v = __ieee754_j1_y1_qone(__y);
			__z = __LIBM_LOCAL_VALUE(invsqrtpi) * (__u * __cc - __v * __ss) / __ieee754_sqrt(__y);
		}
		if (__hx < 0) {
			return -__z;
		} else {
			return __z;
		}
	}
	if (__ix < __INT32_C(0x3e400000)) { /* |x|<2**-27 */
		if (__LIBM_LOCAL_VALUE(hugeval) + __x > __LIBM_LOCAL_VALUE(one))
			return __IEEE754_DOUBLE_C(0.5) * __x; /* inexact if x!=0 necessary */
	}
	__z  = __x * __x;
	__r1 = __z * __LIBM_LOCAL_VALUE(j1_r00);
	__z2 = __z * __z;
	__r2 = __LIBM_LOCAL_VALUE(j1_r01) + __z * __LIBM_LOCAL_VALUE(j1_r02);
	__z4 = __z2 * __z2;
	__r  = __r1 + __z2 * __r2 + __z4 * __LIBM_LOCAL_VALUE(j1_r03);
	__r *= __x;
	__s1 = __LIBM_LOCAL_VALUE(one) + __z * __LIBM_LOCAL_VALUE(j1_s01);
	__s2 = __LIBM_LOCAL_VALUE(j1_s02) + __z * __LIBM_LOCAL_VALUE(j1_s03);
	__s3 = __LIBM_LOCAL_VALUE(j1_s04) + __z * __LIBM_LOCAL_VALUE(j1_s05);
	__s  = __s1 + __z2 * __s2 + __z4 * __s3;
	return (__x * __IEEE754_DOUBLE_C(0.5) + __r / __s);
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
#ifndef __libm_hugevall_defined
#define __libm_hugevall_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, hugevall, __IEEE854_LONG_DOUBLE_C(1.000000000000000000e+4900));
#endif /* !__libm_hugevall_defined */
/* J1(x) = .5 x + x x^2 R(x^2) / S(x^2)  0 <= x <= 2  Peak relative error 4.5e-21 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j1_R0l, __IEEE854_LONG_DOUBLE_C(-9.647406112428107954753770469290757756814E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j1_R1l, __IEEE854_LONG_DOUBLE_C(2.686288565865230690166454005558203955564E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j1_R2l, __IEEE854_LONG_DOUBLE_C(-3.689682683905671185891885948692283776081E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j1_R3l, __IEEE854_LONG_DOUBLE_C(2.195031194229176602851429567792676658146E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j1_R4l, __IEEE854_LONG_DOUBLE_C(-5.124499848728030297902028238597308971319E-1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j1_S0l, __IEEE854_LONG_DOUBLE_C(1.543584977988497274437410333029029035089E9))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j1_S1l, __IEEE854_LONG_DOUBLE_C(2.133542369567701244002565983150952549520E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j1_S2l, __IEEE854_LONG_DOUBLE_C(1.394077011298227346483732156167414670520E5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j1_S3l, __IEEE854_LONG_DOUBLE_C(5.252401789085732428842871556112108446506E2))
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(j1l) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_j1l)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __z, __c, __r, __s, __ss;
	__IEEE854_LONG_DOUBLE_TYPE__ __cc, __u, __v, __y;
	__int32_t __ix;
	__uint32_t __se;
	__LIBM_GET_LDOUBLE_EXP(__se, __x);
	__ix = __se & 0x7fff;
	if (__ix >= 0x7fff)
		return __LIBM_LOCAL_VALUE(onel) / __x;
	__y = __ieee854_fabsl(__x);
	if (__ix >= 0x4000) { /* |x| >= 2.0 */
		__ieee854_sincosl(__y, &__s, &__c);
		__ss = -__s - __c;
		__cc = __s - __c;
		if (__ix < 0x7ffe) { /* make sure y+y not overflow */
			__z = __ieee854_cosl(__y + __y);
			if ((__s * __c) > __LIBM_LOCAL_VALUE(zerol)) {
				__cc = __z / __ss;
			} else {
				__ss = __z / __cc;
			}
		}

		/* j1(x) = 1/sqrt(pi) * (P(1,x)*cc - Q(1,x)*ss) / sqrt(x)
		 * y1(x) = 1/sqrt(pi) * (P(1,x)*ss + Q(1,x)*cc) / sqrt(x) */
		if (__ix > 0x4080) {
			__z = (__LIBM_LOCAL_VALUE(invsqrtpil) * __cc) / __ieee854_sqrtl(__y);
		} else {
			__u = __ieee854_j1_y1_ponel(__y);
			__v = __ieee854_j1_y1_qonel(__y);
			__z = __LIBM_LOCAL_VALUE(invsqrtpil) * (__u * __cc - __v * __ss) / __ieee854_sqrtl(__y);
		}
		if (__se & 0x8000) {
			return -__z;
		} else {
			return __z;
		}
	}
	if (__ix < 0x3fde) { /* |x| < 2^-33 */
		if (__LIBM_LOCAL_VALUE(hugevall) + __x > __LIBM_LOCAL_VALUE(onel))
			return __IEEE854_LONG_DOUBLE_C(0.5) * __x; /* inexact if x!=0 necessary */
	}
	__z = __x * __x;
	__r = __z * (__LIBM_LOCAL_VALUE(j1_R0l) +
	             __z * (__LIBM_LOCAL_VALUE(j1_R1l) +
	                    __z * (__LIBM_LOCAL_VALUE(j1_R2l) +
	                           __z * (__LIBM_LOCAL_VALUE(j1_R3l) +
	                                  __z * __LIBM_LOCAL_VALUE(j1_R4l)))));
	__s = __LIBM_LOCAL_VALUE(j1_S0l) +
	      __z * (__LIBM_LOCAL_VALUE(j1_S1l) +
	             __z * (__LIBM_LOCAL_VALUE(j1_S2l) +
	                    __z * (__LIBM_LOCAL_VALUE(j1_S3l) +
	                           __z)));
	__r *= __x;
	return (__x * __IEEE854_LONG_DOUBLE_C(0.5) + __r / __s);
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_J1_H */
