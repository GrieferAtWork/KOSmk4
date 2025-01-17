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
#ifndef _LIBM_ERF_H
#define _LIBM_ERF_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/exp.h>
#include <libm/fabs.h>
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
#ifndef __libm_tinyf_defined
#define __libm_tinyf_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, tinyf, __IEEE754_FLOAT_C(1.0e-30))
#endif /* !__libm_tinyf_defined */
#ifndef __libm_onef_defined
#define __libm_onef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0000000000e+00)) /* 0x3F800000 */
#endif /* !__libm_onef_defined */
#ifndef __libm_twof_defined
#define __libm_twof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, twof, __IEEE754_FLOAT_C(2.0))
#endif /* !__libm_twof_defined */
/* c = (subfloat)0.84506291151 */
#ifndef __libm_erxf_defined
#define __libm_erxf_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, erxf, __IEEE754_FLOAT_C(8.4506291151e-01)) /* 0x3f58560b */
#endif /* !__libm_erxf_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, efxf, __IEEE754_FLOAT_C(1.2837916613e-01)) /* 0x3e0375d4 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, efx8f, __IEEE754_FLOAT_C(1.0270333290e+00)) /* 0x3f8375d4 */
#ifndef __libm_t_erff_constants_defined
#define __libm_t_erff_constants_defined
/* Coefficients for approximation to  erf on [0,0.84375] */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_pp0f, __IEEE754_FLOAT_C(1.2837916613e-01))  /* 0x3e0375d4 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_pp1f, __IEEE754_FLOAT_C(-3.2504209876e-01)) /* 0xbea66beb */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_pp2f, __IEEE754_FLOAT_C(-2.8481749818e-02)) /* 0xbce9528f */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_pp3f, __IEEE754_FLOAT_C(-5.7702702470e-03)) /* 0xbbbd1489 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_pp4f, __IEEE754_FLOAT_C(-2.3763017452e-05)) /* 0xb7c756b1 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_qq1f, __IEEE754_FLOAT_C(3.9791721106e-01))  /* 0x3ecbbbce */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_qq2f, __IEEE754_FLOAT_C(6.5022252500e-02))  /* 0x3d852a63 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_qq3f, __IEEE754_FLOAT_C(5.0813062117e-03))  /* 0x3ba68116 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_qq4f, __IEEE754_FLOAT_C(1.3249473704e-04))  /* 0x390aee49 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_qq5f, __IEEE754_FLOAT_C(-3.9602282413e-06)) /* 0xb684e21a */
/* Coefficients for approximation to  erf  in [0.84375,1.25] */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_pa0f, __IEEE754_FLOAT_C(-2.3621185683e-03)) /* 0xbb1acdc6 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_pa1f, __IEEE754_FLOAT_C(4.1485610604e-01))  /* 0x3ed46805 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_pa2f, __IEEE754_FLOAT_C(-3.7220788002e-01)) /* 0xbebe9208 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_pa3f, __IEEE754_FLOAT_C(3.1834661961e-01))  /* 0x3ea2fe54 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_pa4f, __IEEE754_FLOAT_C(-1.1089469492e-01)) /* 0xbde31cc2 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_pa5f, __IEEE754_FLOAT_C(3.5478305072e-02))  /* 0x3d1151b3 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_pa6f, __IEEE754_FLOAT_C(-2.1663755178e-03)) /* 0xbb0df9c0 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_qa1f, __IEEE754_FLOAT_C(1.0642088205e-01))  /* 0x3dd9f331 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_qa2f, __IEEE754_FLOAT_C(5.4039794207e-01))  /* 0x3f0a5785 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_qa3f, __IEEE754_FLOAT_C(7.1828655899e-02))  /* 0x3d931ae7 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_qa4f, __IEEE754_FLOAT_C(1.2617121637e-01))  /* 0x3e013307 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_qa5f, __IEEE754_FLOAT_C(1.3637083583e-02))  /* 0x3c5f6e13 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_qa6f, __IEEE754_FLOAT_C(1.1984500103e-02))  /* 0x3c445aa3 */
/* Coefficients for approximation to  erfc in [1.25,1/0.35] */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_ra0f, __IEEE754_FLOAT_C(-9.8649440333e-03)) /* 0xbc21a093 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_ra1f, __IEEE754_FLOAT_C(-6.9385856390e-01)) /* 0xbf31a0b7 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_ra2f, __IEEE754_FLOAT_C(-1.0558626175e+01)) /* 0xc128f022 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_ra3f, __IEEE754_FLOAT_C(-6.2375331879e+01)) /* 0xc2798057 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_ra4f, __IEEE754_FLOAT_C(-1.6239666748e+02)) /* 0xc322658c */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_ra5f, __IEEE754_FLOAT_C(-1.8460508728e+02)) /* 0xc3389ae7 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_ra6f, __IEEE754_FLOAT_C(-8.1287437439e+01)) /* 0xc2a2932b */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_ra7f, __IEEE754_FLOAT_C(-9.8143291473e+00)) /* 0xc11d077e */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sa1f, __IEEE754_FLOAT_C(1.9651271820e+01))  /* 0x419d35ce */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sa2f, __IEEE754_FLOAT_C(1.3765776062e+02))  /* 0x4309a863 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sa3f, __IEEE754_FLOAT_C(4.3456588745e+02))  /* 0x43d9486f */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sa4f, __IEEE754_FLOAT_C(6.4538726807e+02))  /* 0x442158c9 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sa5f, __IEEE754_FLOAT_C(4.2900814819e+02))  /* 0x43d6810b */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sa6f, __IEEE754_FLOAT_C(1.0863500214e+02))  /* 0x42d9451f */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sa7f, __IEEE754_FLOAT_C(6.5702495575e+00))  /* 0x40d23f7c */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sa8f, __IEEE754_FLOAT_C(-6.0424413532e-02)) /* 0xbd777f97 */
/* Coefficients for approximation to  erfc in [1/.35,28] */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_rb0f, __IEEE754_FLOAT_C(-9.8649431020e-03)) /* 0xbc21a092 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_rb1f, __IEEE754_FLOAT_C(-7.9928326607e-01)) /* 0xbf4c9dd4 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_rb2f, __IEEE754_FLOAT_C(-1.7757955551e+01)) /* 0xc18e104b */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_rb3f, __IEEE754_FLOAT_C(-1.6063638306e+02)) /* 0xc320a2ea */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_rb4f, __IEEE754_FLOAT_C(-6.3756646729e+02)) /* 0xc41f6441 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_rb5f, __IEEE754_FLOAT_C(-1.0250950928e+03)) /* 0xc480230b */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_rb6f, __IEEE754_FLOAT_C(-4.8351919556e+02)) /* 0xc3f1c275 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sb1f, __IEEE754_FLOAT_C(3.0338060379e+01))  /* 0x41f2b459 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sb2f, __IEEE754_FLOAT_C(3.2579251099e+02))  /* 0x43a2e571 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sb3f, __IEEE754_FLOAT_C(1.5367296143e+03))  /* 0x44c01759 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sb4f, __IEEE754_FLOAT_C(3.1998581543e+03))  /* 0x4547fdbb */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sb5f, __IEEE754_FLOAT_C(2.5530502930e+03))  /* 0x451f90ce */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sb6f, __IEEE754_FLOAT_C(4.7452853394e+02))  /* 0x43ed43a7 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t_erf_sb7f, __IEEE754_FLOAT_C(-2.2440952301e+01)) /* 0xc1b38712 */
#endif /* !__libm_t_erff_constants_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(erff) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_erff)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __hx, __ix, __i;
	float __R, __S, __P_, __Q, __s, __y, __z, __r;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (!__LIBM_FLT_UWORD_IS_FINITE(__ix)) { /* erf(nan)=nan */
		__i = ((__uint32_t)__hx >> 31) << 1;
		return (float)(1 - __i) + __LIBM_LOCAL_VALUE(onef) / __x; /* erf(+-inf)=+-1 */
	}
	if (__ix < __INT32_C(0x3f580000)) {     /* |x|<0.84375 */
		if (__ix < __INT32_C(0x31800000)) { /* |x|<2**-28 */
			if (__ix < __INT32_C(0x04000000))
				return __IEEE754_FLOAT_C(0.125) * (__IEEE754_FLOAT_C(8.0) * __x + __LIBM_LOCAL_VALUE(efx8f) * __x); /*avoid underflow */
			return __x + __LIBM_LOCAL_VALUE(efxf) * __x;
		}
		__z = __x * __x;
		__r = __LIBM_LOCAL_VALUE(t_erf_pp0f) +
		      __z * (__LIBM_LOCAL_VALUE(t_erf_pp1f) +
		             __z * (__LIBM_LOCAL_VALUE(t_erf_pp2f) +
		                    __z * (__LIBM_LOCAL_VALUE(t_erf_pp3f) +
		                           __z * __LIBM_LOCAL_VALUE(t_erf_pp4f))));
		__s = __LIBM_LOCAL_VALUE(onef) +
		      __z * (__LIBM_LOCAL_VALUE(t_erf_qq1f) +
		             __z * (__LIBM_LOCAL_VALUE(t_erf_qq2f) +
		                    __z * (__LIBM_LOCAL_VALUE(t_erf_qq3f) +
		                           __z * (__LIBM_LOCAL_VALUE(t_erf_qq4f) +
		                                  __z * __LIBM_LOCAL_VALUE(t_erf_qq5f)))));
		__y = __r / __s;
		return __x + __x * __y;
	}
	if (__ix < __INT32_C(0x3fa00000)) { /* 0.84375 <= |x| < 1.25 */
		__s = __ieee754_fabsf(__x) - __LIBM_LOCAL_VALUE(onef);
		__P_ = __LIBM_LOCAL_VALUE(t_erf_pa0f) +
		       __s * (__LIBM_LOCAL_VALUE(t_erf_pa1f) +
		              __s * (__LIBM_LOCAL_VALUE(t_erf_pa2f) +
		                     __s * (__LIBM_LOCAL_VALUE(t_erf_pa3f) +
		                            __s * (__LIBM_LOCAL_VALUE(t_erf_pa4f) +
		                                   __s * (__LIBM_LOCAL_VALUE(t_erf_pa5f) +
		                                          __s * __LIBM_LOCAL_VALUE(t_erf_pa6f))))));
		__Q = __LIBM_LOCAL_VALUE(onef) +
		      __s * (__LIBM_LOCAL_VALUE(t_erf_qa1f) +
		             __s * (__LIBM_LOCAL_VALUE(t_erf_qa2f) +
		                    __s * (__LIBM_LOCAL_VALUE(t_erf_qa3f) +
		                           __s * (__LIBM_LOCAL_VALUE(t_erf_qa4f) +
		                                  __s * (__LIBM_LOCAL_VALUE(t_erf_qa5f) +
		                                         __s * __LIBM_LOCAL_VALUE(t_erf_qa6f))))));
		if (__hx >= 0) {
			return __LIBM_LOCAL_VALUE(erxf) + __P_ / __Q;
		} else {
			return -__LIBM_LOCAL_VALUE(erxf) - __P_ / __Q;
		}
	}
	if (__ix >= __INT32_C(0x40c00000)) { /* inf>|x|>=6 */
		if (__hx >= 0) {
			return __LIBM_LOCAL_VALUE(onef) - __LIBM_LOCAL_VALUE(tinyf);
		} else {
			return __LIBM_LOCAL_VALUE(tinyf) - __LIBM_LOCAL_VALUE(onef);
		}
	}
	__x = __ieee754_fabsf(__x);
	__s = __LIBM_LOCAL_VALUE(onef) / (__x * __x);
	if (__ix < __INT32_C(0x4036DB6E)) { /* |x| < 1/0.35 */
		__R = __LIBM_LOCAL_VALUE(t_erf_ra0f) +
		      __s * (__LIBM_LOCAL_VALUE(t_erf_ra1f) +
		             __s * (__LIBM_LOCAL_VALUE(t_erf_ra2f) +
		                    __s * (__LIBM_LOCAL_VALUE(t_erf_ra3f) +
		                           __s * (__LIBM_LOCAL_VALUE(t_erf_ra4f) +
		                                  __s * (__LIBM_LOCAL_VALUE(t_erf_ra5f) +
		                                         __s * (__LIBM_LOCAL_VALUE(t_erf_ra6f) +
		                                                __s * __LIBM_LOCAL_VALUE(t_erf_ra7f)))))));
		__S = __LIBM_LOCAL_VALUE(onef) +
		      __s * (__LIBM_LOCAL_VALUE(t_erf_sa1f) +
		             __s * (__LIBM_LOCAL_VALUE(t_erf_sa2f) +
		                    __s * (__LIBM_LOCAL_VALUE(t_erf_sa3f) +
		                           __s * (__LIBM_LOCAL_VALUE(t_erf_sa4f) +
		                                  __s * (__LIBM_LOCAL_VALUE(t_erf_sa5f) +
		                                         __s * (__LIBM_LOCAL_VALUE(t_erf_sa6f) +
		                                                __s * (__LIBM_LOCAL_VALUE(t_erf_sa7f) +
		                                                       __s * __LIBM_LOCAL_VALUE(t_erf_sa8f))))))));
	} else { /* |x| >= 1/0.35 */
		__R = __LIBM_LOCAL_VALUE(t_erf_rb0f) +
		      __s * (__LIBM_LOCAL_VALUE(t_erf_rb1f) +
		             __s * (__LIBM_LOCAL_VALUE(t_erf_rb2f) +
		                    __s * (__LIBM_LOCAL_VALUE(t_erf_rb3f) +
		                           __s * (__LIBM_LOCAL_VALUE(t_erf_rb4f) +
		                                  __s * (__LIBM_LOCAL_VALUE(t_erf_rb5f) +
		                                         __s * __LIBM_LOCAL_VALUE(t_erf_rb6f))))));
		__S = __LIBM_LOCAL_VALUE(onef) +
		      __s * (__LIBM_LOCAL_VALUE(t_erf_sb1f) +
		             __s * (__LIBM_LOCAL_VALUE(t_erf_sb2f) +
		                    __s * (__LIBM_LOCAL_VALUE(t_erf_sb3f) +
		                           __s * (__LIBM_LOCAL_VALUE(t_erf_sb4f) +
		                                  __s * (__LIBM_LOCAL_VALUE(t_erf_sb5f) +
		                                         __s * (__LIBM_LOCAL_VALUE(t_erf_sb6f) +
		                                                __s * __LIBM_LOCAL_VALUE(t_erf_sb7f)))))));
	}
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	__LIBM_SET_FLOAT_WORD(__z, __ix & __UINT32_C(0xfffff000));
	__r = __ieee754_expf(-__z * __z - __IEEE754_FLOAT_C(0.5625)) * __ieee754_expf((__z - __x) * (__z + __x) + __R / __S);
	if (__hx >= 0)
		return __LIBM_LOCAL_VALUE(onef) - __r / __x;
	return __r / __x - __LIBM_LOCAL_VALUE(onef);
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
#ifndef __libm_tiny_defined
#define __libm_tiny_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, tiny, __IEEE754_DOUBLE_C(1.0e-300))
#endif /* !__libm_tiny_defined */
#ifndef __libm_half_defined
#define __libm_half_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, half, __IEEE754_DOUBLE_C(5.00000000000000000000e-01)) /* 0x3FE00000, 0x00000000 */
#endif /* !__libm_half_defined */
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.00000000000000000000e+00)) /* 0x3FF00000, 0x00000000 */
#endif /* !__libm_one_defined */
#ifndef __libm_two_defined
#define __libm_two_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, two, __IEEE754_DOUBLE_C(2.0))
#endif /* !__libm_two_defined */
/* c = (__IEEE754_FLOAT_TYPE__)0.84506291151 */
#ifndef __libm_erx_defined
#define __libm_erx_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, erx, __IEEE754_DOUBLE_C(8.45062911510467529297e-01)) /* 0x3FEB0AC1, 0x60000000 */
#endif /* !__libm_erx_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, efx, __IEEE754_DOUBLE_C(1.28379167095512586316e-01)) /* 0x3FC06EBA, 0x8214DB69 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, efx8, __IEEE754_DOUBLE_C(1.02703333676410069053e+00)) /* 0x3FF06EBA, 0x8214DB69 */
#ifndef __libm_t_erf_constants_defined
#define __libm_t_erf_constants_defined
/* Coefficients for approximation to  erf on [0,0.84375] */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_pp0, __IEEE754_DOUBLE_C(1.28379167095512558561e-01))  /* 0x3FC06EBA, 0x8214DB68 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_pp1, __IEEE754_DOUBLE_C(-3.25042107247001499370e-01)) /* 0xBFD4CD7D, 0x691CB913 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_pp2, __IEEE754_DOUBLE_C(-2.84817495755985104766e-02)) /* 0xBF9D2A51, 0xDBD7194F */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_pp3, __IEEE754_DOUBLE_C(-5.77027029648944159157e-03)) /* 0xBF77A291, 0x236668E4 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_pp4, __IEEE754_DOUBLE_C(-2.37630166566501626084e-05)) /* 0xBEF8EAD6, 0x120016AC */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_qq1, __IEEE754_DOUBLE_C(3.97917223959155352819e-01))  /* 0x3FD97779, 0xCDDADC09 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_qq2, __IEEE754_DOUBLE_C(6.50222499887672944485e-02))  /* 0x3FB0A54C, 0x5536CEBA */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_qq3, __IEEE754_DOUBLE_C(5.08130628187576562776e-03))  /* 0x3F74D022, 0xC4D36B0F */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_qq4, __IEEE754_DOUBLE_C(1.32494738004321644526e-04))  /* 0x3F215DC9, 0x221C1A10 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_qq5, __IEEE754_DOUBLE_C(-3.96022827877536812320e-06)) /* 0xBED09C43, 0x42A26120 */
/* Coefficients for approximation to  erf  in [0.84375,1.25]  */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_pa0, __IEEE754_DOUBLE_C(-2.36211856075265944077e-03)) /* 0xBF6359B8, 0xBEF77538 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_pa1, __IEEE754_DOUBLE_C(4.14856118683748331666e-01))  /* 0x3FDA8D00, 0xAD92B34D */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_pa2, __IEEE754_DOUBLE_C(-3.72207876035701323847e-01)) /* 0xBFD7D240, 0xFBB8C3F1 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_pa3, __IEEE754_DOUBLE_C(3.18346619901161753674e-01))  /* 0x3FD45FCA, 0x805120E4 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_pa4, __IEEE754_DOUBLE_C(-1.10894694282396677476e-01)) /* 0xBFBC6398, 0x3D3E28EC */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_pa5, __IEEE754_DOUBLE_C(3.54783043256182359371e-02))  /* 0x3FA22A36, 0x599795EB */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_pa6, __IEEE754_DOUBLE_C(-2.16637559486879084300e-03)) /* 0xBF61BF38, 0x0A96073F */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_qa1, __IEEE754_DOUBLE_C(1.06420880400844228286e-01))  /* 0x3FBB3E66, 0x18EEE323 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_qa2, __IEEE754_DOUBLE_C(5.40397917702171048937e-01))  /* 0x3FE14AF0, 0x92EB6F33 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_qa3, __IEEE754_DOUBLE_C(7.18286544141962662868e-02))  /* 0x3FB2635C, 0xD99FE9A7 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_qa4, __IEEE754_DOUBLE_C(1.26171219808761642112e-01))  /* 0x3FC02660, 0xE763351F */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_qa5, __IEEE754_DOUBLE_C(1.36370839120290507362e-02))  /* 0x3F8BEDC2, 0x6B51DD1C */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_qa6, __IEEE754_DOUBLE_C(1.19844998467991074170e-02))  /* 0x3F888B54, 0x5735151D */
/* Coefficients for approximation to  erfc in [1.25,1/0.35] */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_ra0, __IEEE754_DOUBLE_C(-9.86494403484714822705e-03)) /* 0xBF843412, 0x600D6435 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_ra1, __IEEE754_DOUBLE_C(-6.93858572707181764372e-01)) /* 0xBFE63416, 0xE4BA7360 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_ra2, __IEEE754_DOUBLE_C(-1.05586262253232909814e+01)) /* 0xC0251E04, 0x41B0E726 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_ra3, __IEEE754_DOUBLE_C(-6.23753324503260060396e+01)) /* 0xC04F300A, 0xE4CBA38D */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_ra4, __IEEE754_DOUBLE_C(-1.62396669462573470355e+02)) /* 0xC0644CB1, 0x84282266 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_ra5, __IEEE754_DOUBLE_C(-1.84605092906711035994e+02)) /* 0xC067135C, 0xEBCCABB2 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_ra6, __IEEE754_DOUBLE_C(-8.12874355063065934246e+01)) /* 0xC0545265, 0x57E4D2F2 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_ra7, __IEEE754_DOUBLE_C(-9.81432934416914548592e+00)) /* 0xC023A0EF, 0xC69AC25C */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sa1, __IEEE754_DOUBLE_C(1.96512716674392571292e+01))  /* 0x4033A6B9, 0xBD707687 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sa2, __IEEE754_DOUBLE_C(1.37657754143519042600e+02))  /* 0x4061350C, 0x526AE721 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sa3, __IEEE754_DOUBLE_C(4.34565877475229228821e+02))  /* 0x407B290D, 0xD58A1A71 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sa4, __IEEE754_DOUBLE_C(6.45387271733267880336e+02))  /* 0x40842B19, 0x21EC2868 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sa5, __IEEE754_DOUBLE_C(4.29008140027567833386e+02))  /* 0x407AD021, 0x57700314 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sa6, __IEEE754_DOUBLE_C(1.08635005541779435134e+02))  /* 0x405B28A3, 0xEE48AE2C */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sa7, __IEEE754_DOUBLE_C(6.57024977031928170135e+00))  /* 0x401A47EF, 0x8E484A93 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sa8, __IEEE754_DOUBLE_C(-6.04244152148580987438e-02)) /* 0xBFAEEFF2, 0xEE749A62 */
/* Coefficients for approximation to  erfc in [1/.35,28] */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_rb0, __IEEE754_DOUBLE_C(-9.86494292470009928597e-03)) /* 0xBF843412, 0x39E86F4A */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_rb1, __IEEE754_DOUBLE_C(-7.99283237680523006574e-01)) /* 0xBFE993BA, 0x70C285DE */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_rb2, __IEEE754_DOUBLE_C(-1.77579549177547519889e+01)) /* 0xC031C209, 0x555F995A */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_rb3, __IEEE754_DOUBLE_C(-1.60636384855821916062e+02)) /* 0xC064145D, 0x43C5ED98 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_rb4, __IEEE754_DOUBLE_C(-6.37566443368389627722e+02)) /* 0xC083EC88, 0x1375F228 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_rb5, __IEEE754_DOUBLE_C(-1.02509513161107724954e+03)) /* 0xC0900461, 0x6A2E5992 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_rb6, __IEEE754_DOUBLE_C(-4.83519191608651397019e+02)) /* 0xC07E384E, 0x9BDC383F */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sb1, __IEEE754_DOUBLE_C(3.03380607434824582924e+01))  /* 0x403E568B, 0x261D5190 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sb2, __IEEE754_DOUBLE_C(3.25792512996573918826e+02))  /* 0x40745CAE, 0x221B9F0A */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sb3, __IEEE754_DOUBLE_C(1.53672958608443695994e+03))  /* 0x409802EB, 0x189D5118 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sb4, __IEEE754_DOUBLE_C(3.19985821950859553908e+03))  /* 0x40A8FFB7, 0x688C246A */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sb5, __IEEE754_DOUBLE_C(2.55305040643316442583e+03))  /* 0x40A3F219, 0xCEDF3BE6 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sb6, __IEEE754_DOUBLE_C(4.74528541206955367215e+02))  /* 0x407DA874, 0xE79FE763 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t_erf_sb7, __IEEE754_DOUBLE_C(-2.24409524465858183362e+01)) /* 0xC03670E2, 0x42712D62 */
#endif /* !__libm_t_erf_constants_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(erf) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_erf)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __hx, __ix, __i;
	__IEEE754_DOUBLE_TYPE__ __R, __S, __P_, __Q, __s, __y, __z, __r;
	__LIBM_GET_HIGH_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix >= __INT32_C(0x7ff00000)) { /* erf(nan)=nan */
		__i = ((__uint32_t)__hx >> 31) << 1;
		return (__IEEE754_DOUBLE_TYPE__)(1 - __i) + __LIBM_LOCAL_VALUE(one) / __x; /* erf(+-inf)=+-1 */
	}
	if (__ix < __INT32_C(0x3feb0000)) { /* |x|<0.84375 */
		__IEEE754_DOUBLE_TYPE__ r1, r2, s1, s2, s3, z2, z4;
		if (__ix < __INT32_C(0x3e300000)) { /* |x|<2**-28 */
			if (__ix < __INT32_C(0x00800000))
				return __IEEE754_DOUBLE_C(0.125) * (__IEEE754_DOUBLE_C(8.0) * __x + __LIBM_LOCAL_VALUE(efx8) * __x); /*avoid underflow */
			return __x + __LIBM_LOCAL_VALUE(efx) * __x;
		}
		__z = __x * __x;
		r1  = __LIBM_LOCAL_VALUE(t_erf_pp0) + __z * __LIBM_LOCAL_VALUE(t_erf_pp1);
		z2  = __z * __z;
		r2  = __LIBM_LOCAL_VALUE(t_erf_pp2) + __z * __LIBM_LOCAL_VALUE(t_erf_pp3);
		z4  = z2 * z2;
		s1  = __LIBM_LOCAL_VALUE(one) + __z * __LIBM_LOCAL_VALUE(t_erf_qq1);
		s2  = __LIBM_LOCAL_VALUE(t_erf_qq2) + __z * __LIBM_LOCAL_VALUE(t_erf_qq3);
		s3  = __LIBM_LOCAL_VALUE(t_erf_qq4) + __z * __LIBM_LOCAL_VALUE(t_erf_qq5);
		__r = r1 + z2 * r2 + z4 * __LIBM_LOCAL_VALUE(t_erf_pp4);
		__s = s1 + z2 * s2 + z4 * s3;
		__y = __r / __s;
		return __x + __x * __y;
	}
	if (__ix < __INT32_C(0x3ff40000)) { /* 0.84375 <= |x| < 1.25 */
		__IEEE754_DOUBLE_TYPE__ s2, s4, s6, P1, P2, P3, P4, Q1, Q2, Q3, Q4;
		__s  = __ieee754_fabs(__x) - __LIBM_LOCAL_VALUE(one);
		P1   = __LIBM_LOCAL_VALUE(t_erf_pa0) + __s * __LIBM_LOCAL_VALUE(t_erf_pa1);
		s2   = __s * __s;
		Q1   = __LIBM_LOCAL_VALUE(one) + __s * __LIBM_LOCAL_VALUE(t_erf_qa1);
		s4   = s2 * s2;
		P2   = __LIBM_LOCAL_VALUE(t_erf_pa2) + __s * __LIBM_LOCAL_VALUE(t_erf_pa3);
		s6   = s4 * s2;
		Q2   = __LIBM_LOCAL_VALUE(t_erf_qa2) + __s * __LIBM_LOCAL_VALUE(t_erf_qa3);
		P3   = __LIBM_LOCAL_VALUE(t_erf_pa4) + __s * __LIBM_LOCAL_VALUE(t_erf_pa5);
		Q3   = __LIBM_LOCAL_VALUE(t_erf_qa4) + __s * __LIBM_LOCAL_VALUE(t_erf_qa5);
		P4   = __LIBM_LOCAL_VALUE(t_erf_pa6);
		Q4   = __LIBM_LOCAL_VALUE(t_erf_qa6);
		__P_ = P1 + s2 * P2 + s4 * P3 + s6 * P4;
		__Q  = Q1 + s2 * Q2 + s4 * Q3 + s6 * Q4;
		if (__hx >= 0) {
			return __LIBM_LOCAL_VALUE(erx) + __P_ / __Q;
		} else {
			return -__LIBM_LOCAL_VALUE(erx) - __P_ / __Q;
		}
	}
	if (__ix >= __INT32_C(0x40180000)) { /* inf>|x|>=6 */
		if (__hx >= 0) {
			return __LIBM_LOCAL_VALUE(one) - __LIBM_LOCAL_VALUE(tiny);
		} else {
			return __LIBM_LOCAL_VALUE(tiny) - __LIBM_LOCAL_VALUE(one);
		}
	}
	__x = __ieee754_fabs(__x);
	__s = __LIBM_LOCAL_VALUE(one) / (__x * __x);
	if (__ix < __INT32_C(0x4006DB6E)) { /* |x| < 1/0.35 */
		__IEEE754_DOUBLE_TYPE__ __R1, __R2, __R3, __R4, __S1, __S2, __S3, __S4, __s2, __s4, __s6, __s8_;
		__R1  = __LIBM_LOCAL_VALUE(t_erf_ra0) + __s * __LIBM_LOCAL_VALUE(t_erf_ra1);
		__s2  = __s * __s;
		__S1  = __LIBM_LOCAL_VALUE(one) + __s * __LIBM_LOCAL_VALUE(t_erf_sa1);
		__s4  = __s2 * __s2;
		__R2  = __LIBM_LOCAL_VALUE(t_erf_ra2) + __s * __LIBM_LOCAL_VALUE(t_erf_ra3);
		__s6  = __s4 * __s2;
		__S2  = __LIBM_LOCAL_VALUE(t_erf_sa2) + __s * __LIBM_LOCAL_VALUE(t_erf_sa3);
		__s8_ = __s4 * __s4;
		__R3  = __LIBM_LOCAL_VALUE(t_erf_ra4) + __s * __LIBM_LOCAL_VALUE(t_erf_ra5);
		__S3  = __LIBM_LOCAL_VALUE(t_erf_sa4) + __s * __LIBM_LOCAL_VALUE(t_erf_sa5);
		__R4  = __LIBM_LOCAL_VALUE(t_erf_ra6) + __s * __LIBM_LOCAL_VALUE(t_erf_ra7);
		__S4  = __LIBM_LOCAL_VALUE(t_erf_sa6) + __s * __LIBM_LOCAL_VALUE(t_erf_sa7);
		__R   = __R1 + __s2 * __R2 + __s4 * __R3 + __s6 * __R4;
		__S   = __S1 + __s2 * __S2 + __s4 * __S3 + __s6 * __S4 + __s8_ * __LIBM_LOCAL_VALUE(t_erf_sa8);
	} else { /* |x| >= 1/0.35 */
		__IEEE754_DOUBLE_TYPE__ __R1, __R2, __R3, __S1, __S2, __S3, __S4, __s2, __s4, __s6;
		__R1 = __LIBM_LOCAL_VALUE(t_erf_rb0) + __s * __LIBM_LOCAL_VALUE(t_erf_rb1);
		__s2 = __s * __s;
		__S1 = __LIBM_LOCAL_VALUE(one) + __s * __LIBM_LOCAL_VALUE(t_erf_sb1);
		__s4 = __s2 * __s2;
		__R2 = __LIBM_LOCAL_VALUE(t_erf_rb2) + __s * __LIBM_LOCAL_VALUE(t_erf_rb3);
		__s6 = __s4 * __s2;
		__S2 = __LIBM_LOCAL_VALUE(t_erf_sb2) + __s * __LIBM_LOCAL_VALUE(t_erf_sb3);
		__R3 = __LIBM_LOCAL_VALUE(t_erf_rb4) + __s * __LIBM_LOCAL_VALUE(t_erf_rb5);
		__S3 = __LIBM_LOCAL_VALUE(t_erf_sb4) + __s * __LIBM_LOCAL_VALUE(t_erf_sb5);
		__S4 = __LIBM_LOCAL_VALUE(t_erf_sb6) + __s * __LIBM_LOCAL_VALUE(t_erf_sb7);
		__R  = __R1 + __s2 * __R2 + __s4 * __R3 + __s6 * __LIBM_LOCAL_VALUE(t_erf_rb6);
		__S  = __S1 + __s2 * __S2 + __s4 * __S3 + __s6 * __S4;
	}
	__z = __x;
	__LIBM_SET_LOW_WORD(__z, 0);
	__r = __ieee754_exp(-__z * __z - __IEEE754_DOUBLE_C(0.5625)) *
	      __ieee754_exp((__z - __x) * (__z + __x) + __R / __S);
	if (__hx >= 0) {
		return __LIBM_LOCAL_VALUE(one) - __r / __x;
	} else {
		return __r / __x - __LIBM_LOCAL_VALUE(one);
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
#ifndef __libm_halfl_defined
#define __libm_halfl_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, halfl, __IEEE854_LONG_DOUBLE_C(0.5));
#endif /* !__libm_halfl_defined */
#ifndef __libm_onel_defined
#define __libm_onel_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, onel, __IEEE854_LONG_DOUBLE_C(1.0))
#endif /* !__libm_onel_defined */
#ifndef __libm_erfc_tinyl_defined
#define __libm_erfc_tinyl_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, erfc_tinyl, __IEEE854_LONG_DOUBLE_C(1e-4931))
#endif /* !__libm_erfc_tinyl_defined */
/* c = (float)0.84506291151 */
#ifndef __libm_erxl_defined
#define __libm_erxl_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, erxl, __IEEE854_LONG_DOUBLE_C(0.845062911510467529296875))
#endif /* !__libm_erxl_defined */
/* Coefficients for approximation to  erf on [0,0.84375] */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, efxl, __IEEE854_LONG_DOUBLE_C(1.2837916709551257389615890312154517168810E-1)) /* 2/sqrt(pi) - 1 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, efx8l, __IEEE854_LONG_DOUBLE_C(1.0270333367641005911692712249723613735048E0)) /* 8 * (2/sqrt(pi) - 1) */
#ifndef __libm_t_erfl_constants_defined
#define __libm_t_erfl_constants_defined
/* erfc(1/__x) = __x exp (-1/__x^2 - 0.5625 + rc(__x^2)/sc(__x^2))  1/107 <= 1/__x <= 1/6.6666259765625  Peak relative error 1.1e-21  */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rc0l, __IEEE854_LONG_DOUBLE_C(-8.299617545269701963973537248996670806850E-5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rc1l, __IEEE854_LONG_DOUBLE_C(-6.243845685115818513578933902532056244108E-3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rc2l, __IEEE854_LONG_DOUBLE_C(-1.141667210620380223113693474478394397230E-1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rc3l, __IEEE854_LONG_DOUBLE_C(-7.521343797212024245375240432734425789409E-1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rc4l, __IEEE854_LONG_DOUBLE_C(-1.765321928311155824664963633786967602934E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rc5l, __IEEE854_LONG_DOUBLE_C(-1.029403473103215800456761180695263439188E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sc0l, __IEEE854_LONG_DOUBLE_C(8.413244363014929493035952542677768808601E-3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sc1l, __IEEE854_LONG_DOUBLE_C(2.065114333816877479753334599639158060979E-1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sc2l, __IEEE854_LONG_DOUBLE_C(1.639064941530797583766364412782135680148E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sc3l, __IEEE854_LONG_DOUBLE_C(4.936788463787115555582319302981666347450E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sc4l, __IEEE854_LONG_DOUBLE_C(5.005177727208955487404729933261347679090E0))
/* Coefficients for approximation to  erf on [0,0.84375] */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pp0l, __IEEE854_LONG_DOUBLE_C(1.122751350964552113068262337278335028553E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pp1l, __IEEE854_LONG_DOUBLE_C(-2.808533301997696164408397079650699163276E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pp2l, __IEEE854_LONG_DOUBLE_C(-3.314325479115357458197119660818768924100E5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pp3l, __IEEE854_LONG_DOUBLE_C(-6.848684465326256109712135497895525446398E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pp4l, __IEEE854_LONG_DOUBLE_C(-2.657817695110739185591505062971929859314E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pp5l, __IEEE854_LONG_DOUBLE_C(-1.655310302737837556654146291646499062882E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_qq0l, __IEEE854_LONG_DOUBLE_C(8.745588372054466262548908189000448124232E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_qq1l, __IEEE854_LONG_DOUBLE_C(3.746038264792471129367533128637019611485E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_qq2l, __IEEE854_LONG_DOUBLE_C(7.066358783162407559861156173539693900031E5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_qq3l, __IEEE854_LONG_DOUBLE_C(7.448928604824620999413120955705448117056E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_qq4l, __IEEE854_LONG_DOUBLE_C(4.511583986730994111992253980546131408924E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_qq5l, __IEEE854_LONG_DOUBLE_C(1.368902937933296323345610240009071254014E2))
/* Coefficients for approximation to  erf  in [0.84375,1.25] */
/* erf(__x+1) = 0.845062911510467529296875 + pa(__x)/qa(__x)  -0.15625 <= __x <= +.25  Peak relative error 8.5e-22  */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pa0l, __IEEE854_LONG_DOUBLE_C(-1.076952146179812072156734957705102256059E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pa1l, __IEEE854_LONG_DOUBLE_C(1.884814957770385593365179835059971587220E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pa2l, __IEEE854_LONG_DOUBLE_C(-5.339153975012804282890066622962070115606E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pa3l, __IEEE854_LONG_DOUBLE_C(4.435910679869176625928504532109635632618E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pa4l, __IEEE854_LONG_DOUBLE_C(1.683219516032328828278557309642929135179E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pa5l, __IEEE854_LONG_DOUBLE_C(-2.360236618396952560064259585299045804293E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pa6l, __IEEE854_LONG_DOUBLE_C(1.852230047861891953244413872297940938041E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_pa7l, __IEEE854_LONG_DOUBLE_C(9.394994446747752308256773044667843200719E-2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_qa0l, __IEEE854_LONG_DOUBLE_C(4.559263722294508998149925774781887811255E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_qa1l, __IEEE854_LONG_DOUBLE_C(3.289248982200800575749795055149780689738E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_qa2l, __IEEE854_LONG_DOUBLE_C(2.846070965875643009598627918383314457912E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_qa3l, __IEEE854_LONG_DOUBLE_C(1.398715859064535039433275722017479994465E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_qa4l, __IEEE854_LONG_DOUBLE_C(6.060190733759793706299079050985358190726E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_qa5l, __IEEE854_LONG_DOUBLE_C(2.078695677795422351040502569964299664233E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_qa6l, __IEEE854_LONG_DOUBLE_C(4.641271134150895940966798357442234498546E0))
/* Coefficients for approximation to  erfc in [1.25,1/0.35] */
/* erfc(1/__x) = __x exp (-1/__x^2 - 0.5625 + ra(__x^2)/sa(__x^2))  1/2.85711669921875 < 1/__x < 1/1.25  Peak relative error 3.1e-21  */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_ra0l, __IEEE854_LONG_DOUBLE_C(1.363566591833846324191000679620738857234E-1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_ra1l, __IEEE854_LONG_DOUBLE_C(1.018203167219873573808450274314658434507E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_ra2l, __IEEE854_LONG_DOUBLE_C(1.862359362334248675526472871224778045594E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_ra3l, __IEEE854_LONG_DOUBLE_C(1.411622588180721285284945138667933330348E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_ra4l, __IEEE854_LONG_DOUBLE_C(5.088538459741511988784440103218342840478E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_ra5l, __IEEE854_LONG_DOUBLE_C(8.928251553922176506858267311750789273656E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_ra6l, __IEEE854_LONG_DOUBLE_C(7.264436000148052545243018622742770549982E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_ra7l, __IEEE854_LONG_DOUBLE_C(2.387492459664548651671894725748959751119E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_ra8l, __IEEE854_LONG_DOUBLE_C(2.220916652813908085449221282808458466556E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sa0l, __IEEE854_LONG_DOUBLE_C(-1.382234625202480685182526402169222331847E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sa1l, __IEEE854_LONG_DOUBLE_C(-3.315638835627950255832519203687435946482E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sa2l, __IEEE854_LONG_DOUBLE_C(-2.949124863912936259747237164260785326692E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sa3l, __IEEE854_LONG_DOUBLE_C(-1.246622099070875940506391433635999693661E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sa4l, __IEEE854_LONG_DOUBLE_C(-2.673079795851665428695842853070996219632E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sa5l, __IEEE854_LONG_DOUBLE_C(-2.880269786660559337358397106518918220991E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sa6l, __IEEE854_LONG_DOUBLE_C(-1.450600228493968044773354186390390823713E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sa7l, __IEEE854_LONG_DOUBLE_C(-2.874539731125893533960680525192064277816E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sa8l, __IEEE854_LONG_DOUBLE_C(-1.402241261419067750237395034116942296027E2))
/* Coefficients for approximation to  erfc in [1/.35,107] */
/* erfc(1/__x) = __x exp (-1/__x^2 - 0.5625 + rb(__x^2)/sb(__x^2))  1/6.6666259765625 < 1/__x < 1/2.85711669921875  Peak relative error 4.2e-22  */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rb0l, __IEEE854_LONG_DOUBLE_C(-4.869587348270494309550558460786501252369E-5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rb1l, __IEEE854_LONG_DOUBLE_C(-4.030199390527997378549161722412466959403E-3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rb2l, __IEEE854_LONG_DOUBLE_C(-9.434425866377037610206443566288917589122E-2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rb3l, __IEEE854_LONG_DOUBLE_C(-9.319032754357658601200655161585539404155E-1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rb4l, __IEEE854_LONG_DOUBLE_C(-4.273788174307459947350256581445442062291E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rb5l, __IEEE854_LONG_DOUBLE_C(-8.842289940696150508373541814064198259278E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rb6l, __IEEE854_LONG_DOUBLE_C(-7.069215249419887403187988144752613025255E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_rb7l, __IEEE854_LONG_DOUBLE_C(-1.401228723639514787920274427443330704764E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sb0l, __IEEE854_LONG_DOUBLE_C(4.936254964107175160157544545879293019085E-3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sb1l, __IEEE854_LONG_DOUBLE_C(1.583457624037795744377163924895349412015E-1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sb2l, __IEEE854_LONG_DOUBLE_C(1.850647991850328356622940552450636420484E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sb3l, __IEEE854_LONG_DOUBLE_C(9.927611557279019463768050710008450625415E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sb4l, __IEEE854_LONG_DOUBLE_C(2.531667257649436709617165336779212114570E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sb5l, __IEEE854_LONG_DOUBLE_C(2.869752886406743386458304052862814690045E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, t_erf_sb6l, __IEEE854_LONG_DOUBLE_C(1.182059497870819562441683560749192539345E1))
#endif /* !__libm_t_erfl_constants_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(erfl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_erfl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __R, __S, __P_, __Q, __s, __y, __z, __r;
	__int32_t __ix, __i;
	__uint32_t __se, __i0, __i1;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__ix = __se & 0x7fff;
	if (__ix >= 0x7fff) { /* erf(nan)=nan */
		__i = ((__se & 0xffff) >> 15) << 1;
		return (__IEEE854_LONG_DOUBLE_TYPE__)(1 - __i) +
		       __LIBM_LOCAL_VALUE(onel) / __x; /* erf(+-inf)=+-1 */
	}
	__ix = (__ix << 16) | (__i0 >> 16);
	if (__ix < __INT32_C(0x3ffed800)) {     /* |x|<0.84375 */
		if (__ix < __INT32_C(0x3fde8000)) { /* |x|<2**-33 */
			if (__ix < __INT32_C(0x00080000))
				return __IEEE854_LONG_DOUBLE_C(0.125) * (__IEEE854_LONG_DOUBLE_C(8.0) * __x + __LIBM_LOCAL_VALUE(efx8l) * __x); /*avoid underflow */
			return __x + __LIBM_LOCAL_VALUE(efxl) * __x;
		}
		__z = __x * __x;
		__r = __LIBM_LOCAL_VALUE(t_erf_pp0l) +
		      __z * (__LIBM_LOCAL_VALUE(t_erf_pp1l) +
		             __z * (__LIBM_LOCAL_VALUE(t_erf_pp2l) +
		                    __z * (__LIBM_LOCAL_VALUE(t_erf_pp3l) +
		                           __z * (__LIBM_LOCAL_VALUE(t_erf_pp4l) +
		                                  __z * __LIBM_LOCAL_VALUE(t_erf_pp5l)))));
		__s = __LIBM_LOCAL_VALUE(t_erf_qq0l) +
		      __z * (__LIBM_LOCAL_VALUE(t_erf_qq1l) +
		             __z * (__LIBM_LOCAL_VALUE(t_erf_qq2l) +
		                    __z * (__LIBM_LOCAL_VALUE(t_erf_qq3l) +
		                           __z * (__LIBM_LOCAL_VALUE(t_erf_qq4l) +
		                                  __z * (__LIBM_LOCAL_VALUE(t_erf_qq5l) +
		                                         __z)))));
		__y = __r / __s;
		return __x + __x * __y;
	}
	if (__ix < __INT32_C(0x3fffa000)) { /* 1.25 */
		/* 0.84375 <= |x| < 1.25 */
		__s  = __ieee854_fabsl(__x) - __LIBM_LOCAL_VALUE(onel);
		__P_ = __LIBM_LOCAL_VALUE(t_erf_pa0l) +
		       __s * (__LIBM_LOCAL_VALUE(t_erf_pa1l) +
		              __s * (__LIBM_LOCAL_VALUE(t_erf_pa2l) +
		                     __s * (__LIBM_LOCAL_VALUE(t_erf_pa3l) +
		                            __s * (__LIBM_LOCAL_VALUE(t_erf_pa4l) +
		                                   __s * (__LIBM_LOCAL_VALUE(t_erf_pa5l) +
		                                          __s * (__LIBM_LOCAL_VALUE(t_erf_pa6l) +
		                                                 __s * __LIBM_LOCAL_VALUE(t_erf_pa7l)))))));
		__Q = __LIBM_LOCAL_VALUE(t_erf_qa0l) +
		      __s * (__LIBM_LOCAL_VALUE(t_erf_qa1l) +
		             __s * (__LIBM_LOCAL_VALUE(t_erf_qa2l) +
		                    __s * (__LIBM_LOCAL_VALUE(t_erf_qa3l) +
		                           __s * (__LIBM_LOCAL_VALUE(t_erf_qa4l) +
		                                  __s * (__LIBM_LOCAL_VALUE(t_erf_qa5l) +
		                                         __s * (__LIBM_LOCAL_VALUE(t_erf_qa6l) +
		                                                __s))))));
		if ((__se & 0x8000) == 0) {
			return __LIBM_LOCAL_VALUE(erxl) + __P_ / __Q;
		} else {
			return -__LIBM_LOCAL_VALUE(erxl) - __P_ / __Q;
		}
	}
	if (__ix >= __INT32_C(0x4001d555)) { /* 6.6666259765625 */
		/* inf>|x|>=6.666 */
		if ((__se & 0x8000) == 0) {
			return __LIBM_LOCAL_VALUE(onel) - __LIBM_LOCAL_VALUE(tinyl);
		} else {
			return __LIBM_LOCAL_VALUE(tinyl) - __LIBM_LOCAL_VALUE(onel);
		}
	}
	__x = __ieee854_fabsl(__x);
	__s = __LIBM_LOCAL_VALUE(onel) / (__x * __x);
	if (__ix < __INT32_C(0x4000b6db)) { /* 2.85711669921875 */
		__R = __LIBM_LOCAL_VALUE(t_erf_ra0l) +
		      __s * (__LIBM_LOCAL_VALUE(t_erf_ra1l) +
		             __s * (__LIBM_LOCAL_VALUE(t_erf_ra2l) +
		                    __s * (__LIBM_LOCAL_VALUE(t_erf_ra3l) +
		                           __s * (__LIBM_LOCAL_VALUE(t_erf_ra4l) +
		                                  __s * (__LIBM_LOCAL_VALUE(t_erf_ra5l) +
		                                         __s * (__LIBM_LOCAL_VALUE(t_erf_ra6l) +
		                                                __s * (__LIBM_LOCAL_VALUE(t_erf_ra7l) +
		                                                       __s * __LIBM_LOCAL_VALUE(t_erf_ra8l))))))));
		__S = __LIBM_LOCAL_VALUE(t_erf_sa0l) +
		      __s * (__LIBM_LOCAL_VALUE(t_erf_sa1l) +
		             __s * (__LIBM_LOCAL_VALUE(t_erf_sa2l) +
		                    __s * (__LIBM_LOCAL_VALUE(t_erf_sa3l) +
		                           __s * (__LIBM_LOCAL_VALUE(t_erf_sa4l) +
		                                  __s * (__LIBM_LOCAL_VALUE(t_erf_sa5l) +
		                                         __s * (__LIBM_LOCAL_VALUE(t_erf_sa6l) +
		                                                __s * (__LIBM_LOCAL_VALUE(t_erf_sa7l) +
		                                                       __s * (__LIBM_LOCAL_VALUE(t_erf_sa8l) +
		                                                              __s))))))));
	} else { /* |x| >= 1/0.35 */
		__R = __LIBM_LOCAL_VALUE(t_erf_rb0l) +
		      __s * (__LIBM_LOCAL_VALUE(t_erf_rb1l) +
		             __s * (__LIBM_LOCAL_VALUE(t_erf_rb2l) +
		                    __s * (__LIBM_LOCAL_VALUE(t_erf_rb3l) +
		                           __s * (__LIBM_LOCAL_VALUE(t_erf_rb4l) +
		                                  __s * (__LIBM_LOCAL_VALUE(t_erf_rb5l) +
		                                         __s * (__LIBM_LOCAL_VALUE(t_erf_rb6l) +
		                                                __s * __LIBM_LOCAL_VALUE(t_erf_rb7l)))))));
		__S = __LIBM_LOCAL_VALUE(t_erf_sb0l) +
		      __s * (__LIBM_LOCAL_VALUE(t_erf_sb1l) +
		             __s * (__LIBM_LOCAL_VALUE(t_erf_sb2l) +
		                    __s * (__LIBM_LOCAL_VALUE(t_erf_sb3l) +
		                           __s * (__LIBM_LOCAL_VALUE(t_erf_sb4l) +
		                                  __s * (__LIBM_LOCAL_VALUE(t_erf_sb5l) +
		                                         __s * (__LIBM_LOCAL_VALUE(t_erf_sb6l) +
		                                                __s))))));
	}
	__z = __x;
	__LIBM_GET_LDOUBLE_WORDS(__i, __i0, __i1, __z);
	__i1 = 0;
	__LIBM_SET_LDOUBLE_WORDS(__z, __i, __i0, __i1);
	__r = __ieee854_expl(-__z * __z - __IEEE854_LONG_DOUBLE_C(0.5625)) *
	      __ieee854_expl((__z - __x) * (__z + __x) + __R / __S);
	if ((__se & 0x8000) == 0) {
		return __LIBM_LOCAL_VALUE(onel) - __r / __x;
	} else {
		return __r / __x - __LIBM_LOCAL_VALUE(onel);
	}
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ERF_H */
