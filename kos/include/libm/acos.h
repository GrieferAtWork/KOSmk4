/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBM_ACOS_H
#define _LIBM_ACOS_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/atan.h>
#include <libm/fdlibm.h>
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
#ifndef __libm_onef_defined
#define __libm_onef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0000000000e+00)) /* 0x3F800000 */
#endif /* !__libm_onef_defined */
#ifndef __libm_pif_defined
#define __libm_pif_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pif, __IEEE754_FLOAT_C(3.1415927410e+00)) /* 0x40490fdb */
#endif /* !__libm_pif_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, acos_pio2_hif, __IEEE754_FLOAT_C(1.5707962513e+00)) /* 0x3fc90fda */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, acos_pio2_lof, __IEEE754_FLOAT_C(7.5497894159e-08)) /* 0x33a22168 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pS0f, __IEEE754_FLOAT_C(1.6666667163e-01))          /* 0x3e2aaaab */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pS1f, __IEEE754_FLOAT_C(-3.2556581497e-01))         /* 0xbea6b090 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pS2f, __IEEE754_FLOAT_C(2.0121252537e-01))          /* 0x3e4e0aa8 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pS3f, __IEEE754_FLOAT_C(-4.0055535734e-02))         /* 0xbd241146 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pS4f, __IEEE754_FLOAT_C(7.9153501429e-04))          /* 0x3a4f7f04 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pS5f, __IEEE754_FLOAT_C(3.4793309169e-05))          /* 0x3811ef08 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, qS1f, __IEEE754_FLOAT_C(-2.4033949375e+00))         /* 0xc019d139 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, qS2f, __IEEE754_FLOAT_C(2.0209457874e+00))          /* 0x4001572d */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, qS3f, __IEEE754_FLOAT_C(-6.8828397989e-01))         /* 0xbf303361 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, qS4f, __IEEE754_FLOAT_C(7.7038154006e-02))          /* 0x3d9dc62e */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(acosf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_acosf)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __z, __p, __q, __r;
	__IEEE754_FLOAT_TYPE__ __w, __s, __c, __df;
	__int32_t __hx, __ix;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix == __INT32_C(0x3f800000)) { /* |x|==1 */
		if (__hx > 0) {
			return __IEEE754_FLOAT_C(0.0); /* acos(1) = 0  */
		} else {
			return __LIBM_LOCAL_VALUE(pif) +
			       __IEEE754_FLOAT_C(2.0) *
			       __LIBM_LOCAL_VALUE(acos_pio2_lof); /* acos(-1)= pi */
		}
	} else if (__ix > __INT32_C(0x3f800000)) { /* |x| >= 1 */
		return (__x - __x) / (__x - __x);    /* acos(|x|>1) is NaN */
	}
	if (__ix < __INT32_C(0x3f000000)) { /* |x| < 0.5 */
		if (__ix <= __INT32_C(0x32800000))
			return __LIBM_LOCAL_VALUE(acos_pio2_hif) + __LIBM_LOCAL_VALUE(acos_pio2_lof); /*if|x|<=2**-26 */
		__z = __x * __x;
		__p = __z * (__LIBM_LOCAL_VALUE(pS0f) +
		             __z * (__LIBM_LOCAL_VALUE(pS1f) +
		                    __z * (__LIBM_LOCAL_VALUE(pS2f) +
		                           __z * (__LIBM_LOCAL_VALUE(pS3f) +
		                                  __z * (__LIBM_LOCAL_VALUE(pS4f) +
		                                         __z * __LIBM_LOCAL_VALUE(pS5f))))));
		__q = __LIBM_LOCAL_VALUE(onef) +
		      __z * (__LIBM_LOCAL_VALUE(qS1f) +
		             __z * (__LIBM_LOCAL_VALUE(qS2f) +
		                    __z * (__LIBM_LOCAL_VALUE(qS3f) +
		                           __z * __LIBM_LOCAL_VALUE(qS4f))));
		__r = __p / __q;
		return __LIBM_LOCAL_VALUE(acos_pio2_hif) - (__x - (__LIBM_LOCAL_VALUE(acos_pio2_lof) - __x * __r));
	} else if (__hx < 0) { /* x < -0.5 */
		__z = (__LIBM_LOCAL_VALUE(onef) + __x) * __IEEE754_FLOAT_C(0.5);
		__p = __z * (__LIBM_LOCAL_VALUE(pS0f) +
		             __z * (__LIBM_LOCAL_VALUE(pS1f) +
		                    __z * (__LIBM_LOCAL_VALUE(pS2f) +
		                           __z * (__LIBM_LOCAL_VALUE(pS3f) +
		                                  __z * (__LIBM_LOCAL_VALUE(pS4f) +
		                                         __z * __LIBM_LOCAL_VALUE(pS5f))))));
		__q = __LIBM_LOCAL_VALUE(onef) +
		      __z * (__LIBM_LOCAL_VALUE(qS1f) +
		             __z * (__LIBM_LOCAL_VALUE(qS2f) +
		                    __z * (__LIBM_LOCAL_VALUE(qS3f) +
		                           __z * __LIBM_LOCAL_VALUE(qS4f))));
		__s = __ieee754_sqrtf(__z);
		__r = __p / __q;
		__w = __r * __s - __LIBM_LOCAL_VALUE(acos_pio2_lof);
		return __LIBM_LOCAL_VALUE(pif) - __IEEE754_FLOAT_C(2.0) * (__s + __w);
	} else { /* x > 0.5 */
		__int32_t __idf;
		__z  = (__LIBM_LOCAL_VALUE(onef) - __x) * __IEEE754_FLOAT_C(0.5);
		__s  = __ieee754_sqrtf(__z);
		__df = __s;
		__LIBM_GET_FLOAT_WORD(__idf, __df);
		__LIBM_SET_FLOAT_WORD(__df, __idf & __INT32_C(0xfffff000));
		__c = (__z - __df * __df) / (__s + __df);
		__p = __z * (__LIBM_LOCAL_VALUE(pS0f) +
		             __z * (__LIBM_LOCAL_VALUE(pS1f) +
		                    __z * (__LIBM_LOCAL_VALUE(pS2f) +
		                           __z * (__LIBM_LOCAL_VALUE(pS3f) +
		                                  __z * (__LIBM_LOCAL_VALUE(pS4f) +
		                                         __z * __LIBM_LOCAL_VALUE(pS5f))))));
		__q = __LIBM_LOCAL_VALUE(onef) +
		      __z * (__LIBM_LOCAL_VALUE(qS1f) +
		             __z * (__LIBM_LOCAL_VALUE(qS2f) +
		                    __z * (__LIBM_LOCAL_VALUE(qS3f) +
		                           __z * __LIBM_LOCAL_VALUE(qS4f))));
		__r = __p / __q;
		__w = __r * __s + __c;
		return __IEEE754_FLOAT_C(2.0) * (__df + __w);
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
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.00000000000000000000e+00)) /* 0x3FF00000, 0x00000000 */
#endif /* !__libm_one_defined */
#ifndef __libm_pi_defined
#define __libm_pi_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pi, __IEEE754_DOUBLE_C(3.1415926535897931160E+00)) /* 0x400921FB, 0x54442D18 */
#endif /* !__libm_pi_defined */
#ifndef __libm_pio2_hi_defined
#define __libm_pio2_hi_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pio2_hi, __IEEE754_DOUBLE_C(1.57079632679489655800e+00)) /* 0x3FF921FB, 0x54442D18 */
#endif /* !__libm_pio2_hi_defined */
#ifndef __libm_pio2_lo_defined
#define __libm_pio2_lo_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pio2_lo, __IEEE754_DOUBLE_C(6.12323399573676603587e-17)) /* 0x3C91A626, 0x33145C07 */
#endif /* !__libm_pio2_lo_defined */
#ifndef __libm_pS0_defined
#define __libm_pS0_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pS0, __IEEE754_DOUBLE_C(1.66666666666666657415e-01)) /* 0x3FC55555, 0x55555555 */
#endif /* !__libm_pS0_defined */
#ifndef __libm_pS1_defined
#define __libm_pS1_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pS1, __IEEE754_DOUBLE_C(-3.25565818622400915405e-01)) /* 0xBFD4D612, 0x03EB6F7D */
#endif /* !__libm_pS1_defined */
#ifndef __libm_pS2_defined
#define __libm_pS2_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pS2, __IEEE754_DOUBLE_C(2.01212532134862925881e-01)) /* 0x3FC9C155, 0x0E884455 */
#endif /* !__libm_pS2_defined */
#ifndef __libm_pS3_defined
#define __libm_pS3_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pS3, __IEEE754_DOUBLE_C(-4.00555345006794114027e-02)) /* 0xBFA48228, 0xB5688F3B */
#endif /* !__libm_pS3_defined */
#ifndef __libm_pS4_defined
#define __libm_pS4_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pS4, __IEEE754_DOUBLE_C(7.91534994289814532176e-04)) /* 0x3F49EFE0, 0x7501B288 */
#endif /* !__libm_pS4_defined */
#ifndef __libm_pS5_defined
#define __libm_pS5_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pS5, __IEEE754_DOUBLE_C(3.47933107596021167570e-05)) /* 0x3F023DE1, 0x0DFDF709 */
#endif /* !__libm_pS5_defined */
#ifndef __libm_qS1_defined
#define __libm_qS1_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, qS1, __IEEE754_DOUBLE_C(-2.40339491173441421878e+00)) /* 0xC0033A27, 0x1C8A2D4B */
#endif /* !__libm_qS1_defined */
#ifndef __libm_qS2_defined
#define __libm_qS2_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, qS2, __IEEE754_DOUBLE_C(2.02094576023350569471e+00)) /* 0x40002AE5, 0x9C598AC8 */
#endif /* !__libm_qS2_defined */
#ifndef __libm_qS3_defined
#define __libm_qS3_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, qS3, __IEEE754_DOUBLE_C(-6.88283971605453293030e-01)) /* 0xBFE6066C, 0x1B8D0159 */
#endif /* !__libm_qS3_defined */
#ifndef __libm_qS4_defined
#define __libm_qS4_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, qS4, __IEEE754_DOUBLE_C(7.70381505559019352791e-02)) /* 0x3FB3B8C5, 0xB12E9282 */
#endif /* !__libm_qS4_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(acos) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_acos)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __z, __p, __q, __r, __w, __s, __c, __df;
	__int32_t __hx, __ix;
	__LIBM_GET_HIGH_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix >= __INT32_C(0x3ff00000)) { /* |x| >= 1 */
		__uint32_t lx;
		__LIBM_GET_LOW_WORD(lx, __x);
		if (((__ix - __INT32_C(0x3ff00000)) | lx) == 0) { /* |x|==1 */
			if (__hx > 0) {
				return __IEEE754_DOUBLE_C(0.0); /* acos(1) = 0  */
			} else {
				return __LIBM_LOCAL_VALUE(pi) + __IEEE754_DOUBLE_C(2.0) * __LIBM_LOCAL_VALUE(pio2_lo); /* acos(-1)= pi */
			}
		}
		return (__x - __x) / (__x - __x); /* acos(|x|>1) is NaN */
	}

	if (__ix < __INT32_C(0x3fe00000)) { /* |x| < 0.5 */
		if (__ix <= __INT32_C(0x3c600000))
			return __LIBM_LOCAL_VALUE(pio2_hi) + __LIBM_LOCAL_VALUE(pio2_lo); /*if|x|<2**-57 */
		__z = __x * __x;
		__p = __z * (__LIBM_LOCAL_VALUE(pS0) +
		             __z * (__LIBM_LOCAL_VALUE(pS1) +
		                    __z * (__LIBM_LOCAL_VALUE(pS2) +
		                           __z * (__LIBM_LOCAL_VALUE(pS3) +
		                                  __z * (__LIBM_LOCAL_VALUE(pS4) +
		                                         __z * __LIBM_LOCAL_VALUE(pS5))))));
		__q = __LIBM_LOCAL_VALUE(one) +
		      __z * (__LIBM_LOCAL_VALUE(qS1) +
		             __z * (__LIBM_LOCAL_VALUE(qS2) +
		                    __z * (__LIBM_LOCAL_VALUE(qS3) +
		                           __z * __LIBM_LOCAL_VALUE(qS4))));
		__r = __p / __q;
		return __LIBM_LOCAL_VALUE(pio2_hi) - (__x - (__LIBM_LOCAL_VALUE(pio2_lo) - __x * __r));
	} else if (__hx < 0) { /* x < -0.5 */
		__z = (__LIBM_LOCAL_VALUE(one) + __x) * __IEEE754_DOUBLE_C(0.5);
		__p = __z * (__LIBM_LOCAL_VALUE(pS0) +
		             __z * (__LIBM_LOCAL_VALUE(pS1) +
		                    __z * (__LIBM_LOCAL_VALUE(pS2) +
		                           __z * (__LIBM_LOCAL_VALUE(pS3) +
		                                  __z * (__LIBM_LOCAL_VALUE(pS4) +
		                                         __z * __LIBM_LOCAL_VALUE(pS5))))));
		__q = __LIBM_LOCAL_VALUE(one) +
		      __z * (__LIBM_LOCAL_VALUE(qS1) +
		             __z * (__LIBM_LOCAL_VALUE(qS2) +
		                    __z * (__LIBM_LOCAL_VALUE(qS3) +
		                           __z * __LIBM_LOCAL_VALUE(qS4))));
		__s = __ieee754_sqrt(__z);
		__r = __p / __q;
		__w = __r * __s - __LIBM_LOCAL_VALUE(pio2_lo);
		return __LIBM_LOCAL_VALUE(pi) - __IEEE754_DOUBLE_C(2.0) * (__s + __w);
	} else { /* x > 0.5 */
		__z  = (__LIBM_LOCAL_VALUE(one) - __x) * __IEEE754_DOUBLE_C(0.5);
		__s  = __ieee754_sqrt(__z);
		__df = __s;
		__LIBM_SET_LOW_WORD(__df, 0);
		__c = (__z - __df * __df) / (__s + __df);
		__p = __z * (__LIBM_LOCAL_VALUE(pS0) +
		             __z * (__LIBM_LOCAL_VALUE(pS1) +
		                    __z * (__LIBM_LOCAL_VALUE(pS2) +
		                           __z * (__LIBM_LOCAL_VALUE(pS3) +
		                                  __z * (__LIBM_LOCAL_VALUE(pS4) +
		                                         __z * __LIBM_LOCAL_VALUE(pS5))))));
		__q = __LIBM_LOCAL_VALUE(one) +
		      __z * (__LIBM_LOCAL_VALUE(qS1) +
		             __z * (__LIBM_LOCAL_VALUE(qS2) +
		                    __z * (__LIBM_LOCAL_VALUE(qS3) +
		                           __z * __LIBM_LOCAL_VALUE(qS4))));
		__r = __p / __q;
		__w = __r * __s + __c;
		return __IEEE754_DOUBLE_C(2.0) * (__df + __w);
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
__LIBM_LOCAL_FUNC(acosl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_acosl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __y;
	if (__x == __IEEE854_LONG_DOUBLE_C(0.0))
		return __IEEE854_LONG_DOUBLE_C(1.570796326794896619231321691639751442); /* M_PI_2l */
	if (__x == __IEEE854_LONG_DOUBLE_C(1.0))
		return __IEEE854_LONG_DOUBLE_C(0.0);
	if (__x == -__IEEE854_LONG_DOUBLE_C(1.0))
		return __IEEE854_LONG_DOUBLE_C(3.141592653589793238462643383279502884); /* M_PIl */
	__y = __ieee854_atanl(__ieee854_sqrtl(__IEEE854_LONG_DOUBLE_C(1.0) - (__x * __x)) / __x);
	if (__x > __IEEE854_LONG_DOUBLE_C(0.0))
		return __y;
	return __y + __IEEE854_LONG_DOUBLE_C(3.141592653589793238462643383279502884); /* M_PIl */
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ACOS_H */
