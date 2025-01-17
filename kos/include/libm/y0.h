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
#ifndef _LIBM_Y0_H
#define _LIBM_Y0_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/math-constants.h> /* TODO: Replace uses below with __IEEE754_ constants */
#include <bits/types.h>

#include <libm/cos.h>
#include <libm/fdlibm.h>
#include <libm/j0.h>
#include <libm/log.h>
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
#ifndef __libm_tpif_defined
#define __libm_tpif_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, tpif, __IEEE754_FLOAT_C(6.3661974669e-01)) /* 0x3f22f983 */
#endif /* !__libm_tpif_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y0_u00f, __IEEE754_FLOAT_C(-7.3804296553e-02))   /* 0xbd9726b5 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y0_u01f, __IEEE754_FLOAT_C(1.7666645348e-01))    /* 0x3e34e80d */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y0_u02f, __IEEE754_FLOAT_C(-1.3818567619e-02))   /* 0xbc626746 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y0_u03f, __IEEE754_FLOAT_C(3.4745343146e-04))    /* 0x39b62a69 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y0_u04f, __IEEE754_FLOAT_C(-3.8140706238e-06))   /* 0xb67ff53c */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y0_u05f, __IEEE754_FLOAT_C(1.9559013964e-08))    /* 0x32a802ba */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y0_u06f, __IEEE754_FLOAT_C(-3.9820518410e-11))   /* 0xae2f21eb */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y0_v01f, __IEEE754_FLOAT_C(1.2730483897e-02))    /* 0x3c509385 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y0_v02f, __IEEE754_FLOAT_C(7.6006865129e-05))    /* 0x389f65e0 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y0_v03f, __IEEE754_FLOAT_C(2.5915085189e-07))    /* 0x348b216c */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, y0_v04f, __IEEE754_FLOAT_C(4.4111031494e-10))    /* 0x2ff280c2 */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(y0f) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_y0f)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __z, __s, __c, __ss, __cc, __u, __v;
	__int32_t __hx, __ix;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __INT32_C(0x7fffffff) & __hx;
	/* Y0(NaN) is NaN, y0(-inf) is Nan, y0(inf) is 0, y0(0) is -inf.  */
	if (!__LIBM_FLT_UWORD_IS_FINITE(__ix))
		return __LIBM_LOCAL_VALUE(onef) / (__x + __x * __x);
	if (__LIBM_FLT_UWORD_IS_ZERO(__ix))
		return -__HUGE_VALF + __x; /* -inf and overflow exception.  */
	if (__hx < 0)
		return __LIBM_LOCAL_VALUE(zerof) / (__LIBM_LOCAL_VALUE(zerof) * __x);
	if (__ix >= __INT32_C(0x40000000)) { /* |x| >= 2.0 */
		/* y0(x) = sqrt(2/(pi*x))*(p0(x)*sin(x0)+q0(x)*cos(x0))
		 * where x0 = x-pi/4
		 *      Better formula:
		 *              cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
		 *                      =  1/sqrt(2) * (sin(x) + cos(x))
		 *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
		 *                      =  1/sqrt(2) * (sin(x) - cos(x))
		 * To avoid cancellation, use
		 *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
		 * to compute the worse one. */
		__ieee754_sincosf(__x, &__s, &__c);
		__ss = __s - __c;
		__cc = __s + __c;

		/* j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
		 * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x) */
		if (__ix <= __LIBM_FLT_UWORD_HALF_MAX) { /* make sure x+x not overflow */
			__z = -__ieee754_cosf(__x + __x);
			if ((__s * __c) < __LIBM_LOCAL_VALUE(zerof)) {
				__cc = __z / __ss;
			} else {
				__ss = __z / __cc;
			}
		}
		if (__ix > __INT32_C(0x48000000)) {
			__z = (__LIBM_LOCAL_VALUE(invsqrtpif) * __ss) /
			      __ieee754_sqrtf(__x);
		} else {
			__u = __ieee754_j0_y0_pzerof(__x);
			__v = __ieee754_j0_y0_qzerof(__x);
			__z = __LIBM_LOCAL_VALUE(invsqrtpif) *
			      (__u * __ss + __v * __cc) /
			      __ieee754_sqrtf(__x);
		}
		return __z;
	}
	if (__ix <= __INT32_C(0x39800000)) { /* x < 2**-13 */
		return (__LIBM_LOCAL_VALUE(y0_u00f) +
		        __LIBM_LOCAL_VALUE(tpif) * __ieee754_logf(__x));
	}
	__z = __x * __x;
	__u = __LIBM_LOCAL_VALUE(y0_u00f) +
	      __z * (__LIBM_LOCAL_VALUE(y0_u01f) +
	             __z * (__LIBM_LOCAL_VALUE(y0_u02f) +
	                    __z * (__LIBM_LOCAL_VALUE(y0_u03f) +
	                           __z * (__LIBM_LOCAL_VALUE(y0_u04f) +
	                                  __z * (__LIBM_LOCAL_VALUE(y0_u05f) +
	                                         __z * __LIBM_LOCAL_VALUE(y0_u06f))))));
	__v = __LIBM_LOCAL_VALUE(onef) +
	      __z * (__LIBM_LOCAL_VALUE(y0_v01f) +
	             __z * (__LIBM_LOCAL_VALUE(y0_v02f) +
	                    __z * (__LIBM_LOCAL_VALUE(y0_v03f) +
	                           __z * __LIBM_LOCAL_VALUE(y0_v04f))));
	return (__u / __v + __LIBM_LOCAL_VALUE(tpif) *
	                    (__ieee754_j0f(__x) *
	                     __ieee754_logf(__x)));
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
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y0_u00, __IEEE754_DOUBLE_C(-7.38042951086872317523e-02)) /* 0xBFB2E4D6, 0x99CBD01F */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y0_u01, __IEEE754_DOUBLE_C(1.76666452509181115538e-01))  /* 0x3FC69D01, 0x9DE9E3FC */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y0_u02, __IEEE754_DOUBLE_C(-1.38185671945596898896e-02)) /* 0xBF8C4CE8, 0xB16CFA97 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y0_u03, __IEEE754_DOUBLE_C(3.47453432093683650238e-04))  /* 0x3F36C54D, 0x20B29B6B */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y0_u04, __IEEE754_DOUBLE_C(-3.81407053724364161125e-06)) /* 0xBECFFEA7, 0x73D25CAD */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y0_u05, __IEEE754_DOUBLE_C(1.95590137035022920206e-08))  /* 0x3E550057, 0x3B4EABD4 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y0_u06, __IEEE754_DOUBLE_C(-3.98205194132103398453e-11)) /* 0xBDC5E43D, 0x693FB3C8 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y0_v01, __IEEE754_DOUBLE_C(1.27304834834123699328e-02))  /* 0x3F8A1270, 0x91C9C71A */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y0_v02, __IEEE754_DOUBLE_C(7.60068627350353253702e-05))  /* 0x3F13ECBB, 0xF578C6C1 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y0_v03, __IEEE754_DOUBLE_C(2.59150851840457805467e-07))  /* 0x3E91642D, 0x7FF202FD */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, y0_v04, __IEEE754_DOUBLE_C(4.41110311332675467403e-10))  /* 0x3DFE5018, 0x3BD6D9EF */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(y0) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_y0)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __z, __s, __c, __ss, __cc, __u, __v, __z2;
	__IEEE754_DOUBLE_TYPE__ __z4, __z6, __u1, __u2, __u3, __v1, __v2;
	__int32_t __hx, __ix, __lx;
	__LIBM_GET_DOUBLE_WORDS(__hx, __lx, __x);
	__ix = __INT32_C(0x7fffffff) & __hx;

	/* Y0(NaN) is NaN, y0(-inf) is Nan, y0(inf) is 0  */
	if (__ix >= __INT32_C(0x7ff00000))
		return __LIBM_LOCAL_VALUE(one) / (__x + __x * __x);
	if ((__ix | __lx) == 0)
		return -__HUGE_VAL + __x; /* -inf and overflow exception.  */
	if (__hx < 0)
		return __LIBM_LOCAL_VALUE(zero) / __LIBM_LOCAL_VALUE(zero);
	if (__ix >= __INT32_C(0x40000000)) { /* |x| >= 2.0 */
		/* y0(x) = sqrt(2/(pi*x))*(p0(x)*sin(x0)+q0(x)*cos(x0))
		 * where x0 = x-pi/4
		 *      Better formula:
		 *              cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
		 *                      =  1/sqrt(2) * (sin(x) + cos(x))
		 *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
		 *                      =  1/sqrt(2) * (sin(x) - cos(x))
		 * To avoid cancellation, use
		 *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
		 * to compute the worse one. */
		__ieee754_sincos(__x, &__s, &__c);
		__ss = __s - __c;
		__cc = __s + __c;

		/* j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
		 * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x) */
		if (__ix < __INT32_C(0x7fe00000)) { /* make sure x+x not overflow */
			__z = -__ieee754_cos(__x + __x);
			if ((__s * __c) < __LIBM_LOCAL_VALUE(zero)) {
				__cc = __z / __ss;
			} else {
				__ss = __z / __cc;
			}
		}
		if (__ix > __INT32_C(0x48000000)) {
			__z = (__LIBM_LOCAL_VALUE(invsqrtpi) * __ss) / __ieee754_sqrt(__x);
		} else {
			__u = __ieee754_j0_y0_pzero(__x);
			__v = __ieee754_j0_y0_qzero(__x);
			__z = __LIBM_LOCAL_VALUE(invsqrtpi) *
			      (__u * __ss + __v * __cc) /
			      __ieee754_sqrt(__x);
		}
		return __z;
	}
	if (__ix <= __INT32_C(0x3e400000)) { /* x < 2**-27 */
		return (__LIBM_LOCAL_VALUE(y0_u00) +
		        __LIBM_LOCAL_VALUE(tpi) * __ieee754_log(__x));
	}
	__z  = __x * __x;
	__u1 = __LIBM_LOCAL_VALUE(y0_u00) + __z * __LIBM_LOCAL_VALUE(y0_u01);
	__z2 = __z * __z;
	__u2 = __LIBM_LOCAL_VALUE(y0_u02) + __z * __LIBM_LOCAL_VALUE(y0_u03);
	__z4 = __z2 * __z2;
	__u3 = __LIBM_LOCAL_VALUE(y0_u04) + __z * __LIBM_LOCAL_VALUE(y0_u05);
	__z6 = __z4 * __z2;
	__u  = __u1 + __z2 * __u2 + __z4 * __u3 + __z6 * __LIBM_LOCAL_VALUE(y0_u06);
	__v1 = __LIBM_LOCAL_VALUE(one) + __z * __LIBM_LOCAL_VALUE(y0_v01);
	__v2 = __LIBM_LOCAL_VALUE(y0_v02) + __z * __LIBM_LOCAL_VALUE(y0_v03);
	__v  = __v1 + __z2 * __v2 + __z4 * __LIBM_LOCAL_VALUE(y0_v04);
	return (__u / __v +
	        __LIBM_LOCAL_VALUE(tpi) *
	        (__ieee754_j0(__x) * __ieee754_log(__x)));
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
/* y0(x) = 2/pi ln(x) J0(x) + U(x^2)/V(x^2)  0 < x <= 2  peak relative error 1.7e-21 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y0_U0l, __IEEE854_LONG_DOUBLE_C(-1.054912306975785573710813351985351350861E10))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y0_U1l, __IEEE854_LONG_DOUBLE_C(2.520192609749295139432773849576523636127E10))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y0_U2l, __IEEE854_LONG_DOUBLE_C(-1.856426071075602001239955451329519093395E9))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y0_U3l, __IEEE854_LONG_DOUBLE_C(4.079209129698891442683267466276785956784E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y0_U4l, __IEEE854_LONG_DOUBLE_C(-3.440684087134286610316661166492641011539E5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y0_U5l, __IEEE854_LONG_DOUBLE_C(1.005524356159130626192144663414848383774E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y0_V0l, __IEEE854_LONG_DOUBLE_C(1.429337283720789610137291929228082613676E11))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y0_V1l, __IEEE854_LONG_DOUBLE_C(2.492593075325119157558811370165695013002E9))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y0_V2l, __IEEE854_LONG_DOUBLE_C(2.186077620785925464237324417623665138376E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y0_V3l, __IEEE854_LONG_DOUBLE_C(1.238407896366385175196515057064384929222E5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, y0_V4l, __IEEE854_LONG_DOUBLE_C(4.693924035211032457494368947123233101664E2))
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(y0l) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_y0l)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __z, __s, __c, __ss, __cc, __u, __v;
	__int32_t __ix;
	__uint32_t __se, __i0, __i1;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__ix = __se & __LIBM_IEEE854_LONG_DOUBLE_MAXEXP;
	/* Y0(NaN) is NaN, y0(-inf) is Nan, y0(inf) is 0  */
	if (__se & 0x8000)
		return __LIBM_LOCAL_VALUE(zerol) / (__LIBM_LOCAL_VALUE(zerol) * __x);
	if (__ix >= __LIBM_IEEE854_LONG_DOUBLE_MAXEXP)
		return __LIBM_LOCAL_VALUE(onel) / (__x + __x * __x);
	if ((__i0 | __i1) == 0)
		return -__HUGE_VALL + __x; /* -inf and overflow exception.  */
	if (__ix >= 0x4000) {          /* |x| >= 2.0 */
		/* y0(x) = sqrt(2/(pi*x))*(p0(x)*sin(x0)+q0(x)*cos(x0))
		 * where x0 = x-pi/4
		 *      Better formula:
		 *              cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
		 *                      =  1/sqrt(2) * (sin(x) + cos(x))
		 *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
		 *                      =  1/sqrt(2) * (sin(x) - cos(x))
		 * To avoid cancellation, use
		 *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
		 * to compute the worse one. */
		__ieee854_sincosl(__x, &__s, &__c);
		__ss = __s - __c;
		__cc = __s + __c;

		/* j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
		 * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x) */
		if (__ix < 0x7ffe) { /* make sure x+x not overflow */
			__z = -__ieee854_cosl(__x + __x);
			if ((__s * __c) < __LIBM_LOCAL_VALUE(zerol)) {
				__cc = __z / __ss;
			} else {
				__ss = __z / __cc;
			}
		}
		if (__ix > 0x4080) { /* 1e39 */
			__z = (__LIBM_LOCAL_VALUE(invsqrtpil) * __ss) / __ieee854_sqrtl(__x);
		} else {
			__u = __ieee854_j0_y0_pzerol(__x);
			__v = __ieee854_j0_y0_qzerol(__x);
			__z = __LIBM_LOCAL_VALUE(invsqrtpil) *
			      (__u * __ss + __v * __cc) / __ieee854_sqrtl(__x);
		}
		return __z;
	}
	if (__ix <= 0x3fde) { /* x < 2^-33 */
		__z = __IEEE854_LONG_DOUBLE_C(-7.380429510868722527629822444004602747322E-2) +
		      __LIBM_LOCAL_VALUE(tpil) * __ieee854_logl(__x);
		return __z;
	}
	__z = __x * __x;
	__u = __LIBM_LOCAL_VALUE(y0_U0l) +
	      __z * (__LIBM_LOCAL_VALUE(y0_U1l) +
	             __z * (__LIBM_LOCAL_VALUE(y0_U2l) +
	                    __z * (__LIBM_LOCAL_VALUE(y0_U3l) +
	                           __z * (__LIBM_LOCAL_VALUE(y0_U4l) +
	                                  __z * __LIBM_LOCAL_VALUE(y0_U5l)))));
	__v = __LIBM_LOCAL_VALUE(y0_V0l) +
	      __z * (__LIBM_LOCAL_VALUE(y0_V1l) +
	             __z * (__LIBM_LOCAL_VALUE(y0_V2l) +
	                    __z * (__LIBM_LOCAL_VALUE(y0_V3l) +
	                           __z * (__LIBM_LOCAL_VALUE(y0_V4l) +
	                                  __z))));
	return (__u / __v +
	        __LIBM_LOCAL_VALUE(tpil) *
	        (__ieee854_j0l(__x) * __ieee854_logl(__x)));
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_Y0_H */
