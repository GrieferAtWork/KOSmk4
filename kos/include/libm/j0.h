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
#ifndef _LIBM_J0_H
#define _LIBM_J0_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/math-constants.h> /* TODO: Replace uses below with __IEEE754_ constants */
#include <bits/types.h>

#include <libm/cos.h>
#include <libm/fdlibm.h>
#include <libm/pzero.h>
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
/* R0/S0 on [0, 2.00] */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j0_R02f, __IEEE754_FLOAT_C(1.5625000000e-02))  /* 0x3c800000 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j0_R03f, __IEEE754_FLOAT_C(-1.8997929874e-04)) /* 0xb947352e */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j0_R04f, __IEEE754_FLOAT_C(1.8295404516e-06))  /* 0x35f58e88 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j0_R05f, __IEEE754_FLOAT_C(-4.6183270541e-09)) /* 0xb19eaf3c */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j0_S01f, __IEEE754_FLOAT_C(1.5619102865e-02))  /* 0x3c7fe744 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j0_S02f, __IEEE754_FLOAT_C(1.1692678527e-04))  /* 0x38f53697 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j0_S03f, __IEEE754_FLOAT_C(5.1354652442e-07))  /* 0x3509daa6 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, j0_S04f, __IEEE754_FLOAT_C(1.1661400734e-09))  /* 0x30a045e8 */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(j0f) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_j0f)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __z, __s, __c, __ss, __cc, __r, __u, __v;
	__int32_t __hx, __ix;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (!__LIBM_FLT_UWORD_IS_FINITE(__ix))
		return __LIBM_LOCAL_VALUE(onef) / (__x * __x);
	__x = __ieee754_fabsf(__x);
	if (__ix >= __INT32_C(0x40000000)) { /* |x| >= 2.0 */
		__ieee754_sincosf(__x, &__s, &__c);
		__ss = __s - __c;
		__cc = __s + __c;
		if (__ix <= __LIBM_FLT_UWORD_HALF_MAX) { /* make sure x+x not overflow */
			__z = -__ieee754_cosf(__x + __x);
			if ((__s * __c) < __LIBM_LOCAL_VALUE(zerof)) {
				__cc = __z / __ss;
			} else {
				__ss = __z / __cc;
			}
		}

		/* j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
		 * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x) */
		if (__ix > __INT32_C(0x48000000)) {
			__z = (__LIBM_LOCAL_VALUE(invsqrtpif) * __cc) / __ieee754_sqrtf(__x);
		} else {
			__u = __ieee754_j0_y0_pzerof(__x);
			__v = __ieee754_j0_y0_qzerof(__x);
			__z = __LIBM_LOCAL_VALUE(invsqrtpif) *
			      (__u * __cc - __v * __ss) /
			      __ieee754_sqrtf(__x);
		}
		return __z;
	}
	if (__ix < __INT32_C(0x39000000)) { /* |x| < 2**-13 */
		/* raise inexact if x != 0 */
		__libm_math_force_eval_r(__IEEE754_FLOAT_TYPE__,
		                         __LIBM_LOCAL_VALUE(hugevalf) + __x);
		if (__ix < __INT32_C(0x32000000)) {
			return __LIBM_LOCAL_VALUE(onef); /* |x|<2**-27 */
		} else {
			return __LIBM_LOCAL_VALUE(onef) - __IEEE754_FLOAT_C(0.25) * __x * __x;
		}
	}
	__z = __x * __x;
	__r = __z * (__LIBM_LOCAL_VALUE(j0_R02f) +
	             __z * (__LIBM_LOCAL_VALUE(j0_R03f) +
	                    __z * (__LIBM_LOCAL_VALUE(j0_R04f) +
	                           __z * __LIBM_LOCAL_VALUE(j0_R05f))));
	__s = __LIBM_LOCAL_VALUE(onef) +
	      __z * (__LIBM_LOCAL_VALUE(j0_S01f) +
	             __z * (__LIBM_LOCAL_VALUE(j0_S02f) +
	                    __z * (__LIBM_LOCAL_VALUE(j0_S03f) +
	                           __z * __LIBM_LOCAL_VALUE(j0_S04f))));
	if (__ix < __INT32_C(0x3F800000)) { /* |x| < 1.00 */
		return __LIBM_LOCAL_VALUE(onef) +
		       __z * (__IEEE754_FLOAT_C(-0.25) + (__r / __s));
	} else {
		__u = __IEEE754_FLOAT_C(0.5) * __x;
		return ((__LIBM_LOCAL_VALUE(onef) + __u) *
		        (__LIBM_LOCAL_VALUE(onef) - __u) +
		        __z * (__r / __s));
	}
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
/* R0/S0 on [0, 2.00] */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j0_R02, __IEEE754_DOUBLE_C(1.56249999999999947958e-02))  /* 0x3F8FFFFF, 0xFFFFFFFD */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j0_R03, __IEEE754_DOUBLE_C(-1.89979294238854721751e-04)) /* 0xBF28E6A5, 0xB61AC6E9 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j0_R04, __IEEE754_DOUBLE_C(1.82954049532700665670e-06))  /* 0x3EBEB1D1, 0x0C503919 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j0_R05, __IEEE754_DOUBLE_C(-4.61832688532103189199e-09)) /* 0xBE33D5E7, 0x73D63FCE */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j0_S01, __IEEE754_DOUBLE_C(1.56191029464890010492e-02))  /* 0x3F8FFCE8, 0x82C8C2A4 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j0_S02, __IEEE754_DOUBLE_C(1.16926784663337450260e-04))  /* 0x3F1EA6D2, 0xDD57DBF4 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j0_S03, __IEEE754_DOUBLE_C(5.13546550207318111446e-07))  /* 0x3EA13B54, 0xCE84D5A9 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, j0_S04, __IEEE754_DOUBLE_C(1.16614003333790000205e-09))  /* 0x3E1408BC, 0xF4745D8F */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(j0) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_j0)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __z, __s, __c, __ss, __cc, __r, __u, __v;
	__IEEE754_DOUBLE_TYPE__ __r1, __r2, __s1, __s2, __z2, __z4;
	__int32_t __hx, __ix;
	__LIBM_GET_HIGH_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix >= __INT32_C(0x7ff00000))
		return __LIBM_LOCAL_VALUE(one) / (__x * __x);
	__x = __ieee754_fabs(__x);
	if (__ix >= __INT32_C(0x40000000)) { /* |x| >= 2.0 */
		__ieee754_sincos(__x, &__s, &__c);
		__ss = __s - __c;
		__cc = __s + __c;
		if (__ix < __INT32_C(0x7fe00000)) { /* make sure x+x not overflow */
			__z = -__ieee754_cos(__x + __x);
			if ((__s * __c) < __LIBM_LOCAL_VALUE(zero)) {
				__cc = __z / __ss;
			} else {
				__ss = __z / __cc;
			}
		}

		/* j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
		 * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x) */
		if (__ix > __INT32_C(0x48000000)) {
			__z = (__LIBM_LOCAL_VALUE(invsqrtpi) * __cc) / __ieee754_sqrt(__x);
		} else {
			__u = __ieee754_j0_y0_pzero(__x);
			__v = __ieee754_j0_y0_qzero(__x);
			__z = __LIBM_LOCAL_VALUE(invsqrtpi) * (__u * __cc - __v * __ss) / __ieee754_sqrt(__x);
		}
		return __z;
	}
	if (__ix < __INT32_C(0x3f200000)) { /* |x| < 2**-13 */
		__libm_math_force_eval_r(__IEEE754_DOUBLE_TYPE__,
		                         __LIBM_LOCAL_VALUE(hugeval) + __x); /* raise inexact if x != 0 */
		if (__ix < __INT32_C(0x3e400000)) {
			return __LIBM_LOCAL_VALUE(one); /* |x|<2**-27 */
		} else {
			return __LIBM_LOCAL_VALUE(one) -
			       __IEEE754_DOUBLE_C(0.25) * __x * __x;
		}
	}
	__z = __x * __x;
	__r1 = __z * __LIBM_LOCAL_VALUE(j0_R02);
	__z2 = __z * __z;
	__r2 = __LIBM_LOCAL_VALUE(j0_R03) + __z * __LIBM_LOCAL_VALUE(j0_R04);
	__z4 = __z2 * __z2;
	__r  = __r1 + __z2 * __r2 + __z4 * __LIBM_LOCAL_VALUE(j0_R05);
	__s1 = __LIBM_LOCAL_VALUE(one) + __z * __LIBM_LOCAL_VALUE(j0_S01);
	__s2 = __LIBM_LOCAL_VALUE(j0_S02) + __z * __LIBM_LOCAL_VALUE(j0_S03);
	__s  = __s1 + __z2 * __s2 + __z4 * __LIBM_LOCAL_VALUE(j0_S04);
	if (__ix < __INT32_C(0x3FF00000)) { /* |x| < 1.00 */
		return __LIBM_LOCAL_VALUE(one) + __z * (__IEEE754_DOUBLE_C(-0.25) + (__r / __s));
	} else {
		__u = __IEEE754_DOUBLE_C(0.5) * __x;
		return ((__LIBM_LOCAL_VALUE(one) + __u) *
		        (__LIBM_LOCAL_VALUE(one) - __u) +
		        __z * (__r / __s));
	}
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
/* J0(x) = 1 - x^2 / 4 + x^4 R0(x^2) / S0(x^2)  0 <= x <= 2  peak relative error 1.41e-22 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j0_R0l, __IEEE854_LONG_DOUBLE_C(4.287176872744686992880841716723478740566E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j0_R1l, __IEEE854_LONG_DOUBLE_C(-6.652058897474241627570911531740907185772E5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j0_R2l, __IEEE854_LONG_DOUBLE_C(7.011848381719789863458364584613651091175E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j0_R3l, __IEEE854_LONG_DOUBLE_C(-3.168040850193372408702135490809516253693E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j0_R4l, __IEEE854_LONG_DOUBLE_C(6.030778552661102450545394348845599300939E-2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j0_S0l, __IEEE854_LONG_DOUBLE_C(2.743793198556599677955266341699130654342E9))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j0_S1l, __IEEE854_LONG_DOUBLE_C(3.364330079384816249840086842058954076201E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j0_S2l, __IEEE854_LONG_DOUBLE_C(1.924119649412510777584684927494642526573E5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, j0_S3l, __IEEE854_LONG_DOUBLE_C(6.239282256012734914211715620088714856494E2))
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(j0l) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_j0l)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __z, __s, __c, __ss;
	__IEEE854_LONG_DOUBLE_TYPE__ __cc, __r, __u, __v;
	__int32_t __ix;
	__uint32_t __se;
	__LIBM_GET_LDOUBLE_EXP(__se, __x);
	__ix = __se & 0x7fff;
	if (__ix >= 0x7fff)
		return __LIBM_LOCAL_VALUE(onel) / (__x * __x);
	__x = __ieee854_fabsl(__x);
	if (__ix >= 0x4000) { /* |x| >= 2.0 */
		__ieee854_sincosl(__x, &__s, &__c);
		__ss = __s - __c;
		__cc = __s + __c;
		if (__ix < 0x7ffe) { /* make sure x+x not overflow */
			__z = -__ieee854_cosl(__x + __x);
			if ((__s * __c) < __LIBM_LOCAL_VALUE(zerol)) {
				__cc = __z / __ss;
			} else {
				__ss = __z / __cc;
			}
		}

		/* j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
		 * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x) */
		if (__ix > 0x4080) { /* 2^129 */
			__z = (__LIBM_LOCAL_VALUE(invsqrtpil) * __cc) / __ieee854_sqrtl(__x);
		} else {
			__u = __ieee854_j0_y0_pzerol(__x);
			__v = __ieee854_j0_y0_qzerol(__x);
			__z = __LIBM_LOCAL_VALUE(invsqrtpil) *
			      (__u * __cc - __v * __ss) /
			      __ieee854_sqrtl(__x);
		}
		return __z;
	}
	if (__ix < 0x3fef) { /* |x| < 2**-16 */
		/* raise inexact if x != 0 */
		__libm_math_force_eval_r(__IEEE854_LONG_DOUBLE_TYPE__,
		                         __LIBM_LOCAL_VALUE(hugevall) + __x);
		if (__ix < 0x3fde) { /* |x| < 2^-33 */
			return __LIBM_LOCAL_VALUE(onel);
		} else {
			return __LIBM_LOCAL_VALUE(onel) -
			       __IEEE854_LONG_DOUBLE_C(0.25) * __x * __x;
		}
	}
	__z = __x * __x;
	__r = __z * (__LIBM_LOCAL_VALUE(j0_R0l) +
	             __z * (__LIBM_LOCAL_VALUE(j0_R1l) +
	                    __z * (__LIBM_LOCAL_VALUE(j0_R2l) +
	                           __z * (__LIBM_LOCAL_VALUE(j0_R3l) +
	                                  __z * __LIBM_LOCAL_VALUE(j0_R4l)))));
	__s = __LIBM_LOCAL_VALUE(j0_S0l) +
	      __z * (__LIBM_LOCAL_VALUE(j0_S1l) +
	             __z * (__LIBM_LOCAL_VALUE(j0_S2l) +
	                    __z * (__LIBM_LOCAL_VALUE(j0_S3l) +
	                           __z)));
	if (__ix < 0x3fff) { /* |x| < 1.00 */
		return (__LIBM_LOCAL_VALUE(onel) -
		        __IEEE854_LONG_DOUBLE_C(0.25) * __z +
		        __z * (__r / __s));
	} else {
		__u = __IEEE854_LONG_DOUBLE_C(0.5) * __x;
		return ((__LIBM_LOCAL_VALUE(onel) + __u) *
		        (__LIBM_LOCAL_VALUE(onel) - __u) +
		        __z * (__r / __s));
	}
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_J0_H */
