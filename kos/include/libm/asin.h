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
#ifndef _LIBM_ASIN_H
#define _LIBM_ASIN_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fabs.h>
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
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0000000000e+00))     /* 0x3F800000 */
#endif /* !__libm_onef_defined */
#ifndef __libm_hugevalf_defined
#define __libm_hugevalf_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, hugevalf, __IEEE754_FLOAT_C(1.0000000000e+30))
#endif /* !__libm_hugevalf_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, asin_pio2_hif, __IEEE754_FLOAT_C(1.57079637050628662109375))
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, asin_pio2_lof, __IEEE754_FLOAT_C(-4.37113900018624283e-8))
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, asin_pio4_hif, __IEEE754_FLOAT_C(0.785398185253143310546875))
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, p0f, __IEEE754_FLOAT_C(1.666675248e-1))
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, p1f, __IEEE754_FLOAT_C(7.495297643e-2))
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, p2f, __IEEE754_FLOAT_C(4.547037598e-2))
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, p3f, __IEEE754_FLOAT_C(2.417951451e-2))
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, p4f, __IEEE754_FLOAT_C(4.216630880e-2))
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(asinf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_asinf)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __t, __w, __p, __q, __c, __r, __s;
	__int32_t __hx, __ix;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix == __INT32_C(0x3f800000)) {
		/* asin(1)=+-pi/2 with inexact */
		return __x * __LIBM_LOCAL_VALUE(asin_pio2_hif) + __x * __LIBM_LOCAL_VALUE(asin_pio2_lof);
	} else if (__ix > __INT32_C(0x3f800000)) { /* |x|>= 1 */
		return (__x - __x) / (__x - __x);            /* asin(|x|>1) is NaN */
	} else if (__ix < __INT32_C(0x3f000000)) { /* |x|<0.5 */
		if (__ix < __INT32_C(0x32000000)) {    /* if |x| < 2**-27 */
			if (__LIBM_LOCAL_VALUE(hugevalf) + __x > __LIBM_LOCAL_VALUE(onef))
				return __x; /* return x with inexact if x!=0 */
		} else {
			__t = __x * __x;
			__w = __t * (__LIBM_LOCAL_VALUE(p0f) +
			         __t * (__LIBM_LOCAL_VALUE(p1f) +
			              __t * (__LIBM_LOCAL_VALUE(p2f) +
			                   __t * (__LIBM_LOCAL_VALUE(p3f) +
			                        __t * __LIBM_LOCAL_VALUE(p4f)))));
			return __x + __x * __w;
		}
	}
	/* 1> |x|>= 0.5 */
	__w = __LIBM_LOCAL_VALUE(onef) - __ieee754_fabsf(__x);
	__t = __w * __IEEE754_FLOAT_C(0.5);
	__p = __t * (__LIBM_LOCAL_VALUE(p0f) +
	         __t * (__LIBM_LOCAL_VALUE(p1f) +
	              __t * (__LIBM_LOCAL_VALUE(p2f) +
	                   __t * (__LIBM_LOCAL_VALUE(p3f) +
	                        __t * __LIBM_LOCAL_VALUE(p4f)))));
	__s = __ieee754_sqrtf(__t);
	if (__ix >= __INT32_C(0x3F79999A)) { /* if |x| > 0.975 */
		__t = __LIBM_LOCAL_VALUE(asin_pio2_hif) - (__IEEE754_FLOAT_C(2.0) * (__s + __s * __p) - __LIBM_LOCAL_VALUE(asin_pio2_lof));
	} else {
		__int32_t iw;
		__w = __s;
		__LIBM_GET_FLOAT_WORD(iw, __w);
		__LIBM_SET_FLOAT_WORD(__w, iw & __INT32_C(0xfffff000));
		__c = (__t - __w * __w) / (__s + __w);
		__r = __p;
		__p = __IEEE754_FLOAT_C(2.0) * __s * __r - (__LIBM_LOCAL_VALUE(asin_pio2_lof) - __IEEE754_FLOAT_C(2.0) * __c);
		__q = __LIBM_LOCAL_VALUE(asin_pio4_hif) - __IEEE754_FLOAT_C(2.0) * __w;
		__t = __LIBM_LOCAL_VALUE(asin_pio4_hif) - (__p - __q);
	}
	if (__hx > 0)
		return __t;
	return -__t;
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
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.00000000000000000000e+00))     /* 0x3FF00000, 0x00000000 */
#endif /* !__libm_one_defined */
#ifndef __libm_hugeval_defined
#define __libm_hugeval_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, hugeval, __IEEE754_DOUBLE_C(1.00000000000000000000e+300))
#endif /* !__libm_hugeval_defined */
#ifndef __libm_pio2_hi_defined
#define __libm_pio2_hi_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pio2_hi, __IEEE754_DOUBLE_C(1.57079632679489655800e+00)) /* 0x3FF921FB, 0x54442D18 */
#endif /* !__libm_pio2_hi_defined */
#ifndef __libm_pio2_lo_defined
#define __libm_pio2_lo_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pio2_lo, __IEEE754_DOUBLE_C(6.12323399573676603587e-17)) /* 0x3C91A626, 0x33145C07 */
#endif /* !__libm_pio2_lo_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pio4_hi, __IEEE754_DOUBLE_C(7.85398163397448278999e-01)) /* 0x3FE921FB, 0x54442D18 */
#ifndef __libm_pS0_defined
#define __libm_pS0_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pS0, __IEEE754_DOUBLE_C(1.66666666666666657415e-01))     /* 0x3FC55555, 0x55555555 */
#endif /* !__libm_pS0_defined */
#ifndef __libm_pS1_defined
#define __libm_pS1_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pS1, __IEEE754_DOUBLE_C(-3.25565818622400915405e-01))    /* 0xBFD4D612, 0x03EB6F7D */
#endif /* !__libm_pS1_defined */
#ifndef __libm_pS2_defined
#define __libm_pS2_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pS2, __IEEE754_DOUBLE_C(2.01212532134862925881e-01))     /* 0x3FC9C155, 0x0E884455 */
#endif /* !__libm_pS2_defined */
#ifndef __libm_pS3_defined
#define __libm_pS3_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pS3, __IEEE754_DOUBLE_C(-4.00555345006794114027e-02))    /* 0xBFA48228, 0xB5688F3B */
#endif /* !__libm_pS3_defined */
#ifndef __libm_pS4_defined
#define __libm_pS4_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pS4, __IEEE754_DOUBLE_C(7.91534994289814532176e-04))     /* 0x3F49EFE0, 0x7501B288 */
#endif /* !__libm_pS4_defined */
#ifndef __libm_pS5_defined
#define __libm_pS5_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pS5, __IEEE754_DOUBLE_C(3.47933107596021167570e-05))     /* 0x3F023DE1, 0x0DFDF709 */
#endif /* !__libm_pS5_defined */
#ifndef __libm_qS1_defined
#define __libm_qS1_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, qS1, __IEEE754_DOUBLE_C(-2.40339491173441421878e+00))    /* 0xC0033A27, 0x1C8A2D4B */
#endif /* !__libm_qS1_defined */
#ifndef __libm_qS2_defined
#define __libm_qS2_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, qS2, __IEEE754_DOUBLE_C(2.02094576023350569471e+00))     /* 0x40002AE5, 0x9C598AC8 */
#endif /* !__libm_qS2_defined */
#ifndef __libm_qS3_defined
#define __libm_qS3_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, qS3, __IEEE754_DOUBLE_C(-6.88283971605453293030e-01))    /* 0xBFE6066C, 0x1B8D0159 */
#endif /* !__libm_qS3_defined */
#ifndef __libm_qS4_defined
#define __libm_qS4_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, qS4, __IEEE754_DOUBLE_C(7.70381505559019352791e-02))     /* 0x3FB3B8C5, 0xB12E9282 */
#endif /* !__libm_qS4_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(asin) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_asin)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __t, __w, __p, __q, __c, __r, __s;
	__int32_t __hx, __ix;
	__LIBM_GET_HIGH_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix >= __INT32_C(0x3ff00000)) { /* |x|>= 1 */
		__uint32_t lx;
		__LIBM_GET_LOW_WORD(lx, __x);
		if (((__ix - __INT32_C(0x3ff00000)) | lx) == 0)
			/* asin(1)=+-pi/2 with inexact */
			return __x * __LIBM_LOCAL_VALUE(pio2_hi) + __x * __LIBM_LOCAL_VALUE(pio2_lo);
		return (__x - __x) / (__x - __x);            /* asin(|x|>1) is NaN */
	} else if (__ix < __INT32_C(0x3fe00000)) { /* |x|<0.5 */
		if (__ix < __INT32_C(0x3e400000)) {    /* if |x| < 2**-27 */
			if (__LIBM_LOCAL_VALUE(hugeval) + __x > __LIBM_LOCAL_VALUE(one))
				return __x; /* return x with inexact if x!=0 */
		} else {
			__t = __x * __x;
			__p = __t * (__LIBM_LOCAL_VALUE(pS0) +
			         __t * (__LIBM_LOCAL_VALUE(pS1) +
			              __t * (__LIBM_LOCAL_VALUE(pS2) +
			                   __t * (__LIBM_LOCAL_VALUE(pS3) +
			                        __t * (__LIBM_LOCAL_VALUE(pS4) +
			                             __t * __LIBM_LOCAL_VALUE(pS5))))));
			__q = __LIBM_LOCAL_VALUE(one) +
			    __t * (__LIBM_LOCAL_VALUE(qS1) +
			         __t * (__LIBM_LOCAL_VALUE(qS2) +
			              __t * (__LIBM_LOCAL_VALUE(qS3) +
			                   __t * __LIBM_LOCAL_VALUE(qS4))));
			__w = __p / __q;
			return __x + __x * __w;
		}
	}
	/* 1> |x|>= 0.5 */
	__w = __LIBM_LOCAL_VALUE(one) - __ieee754_fabs(__x);
	__t = __w * __IEEE754_DOUBLE_C(0.5);
	__p = __t * (__LIBM_LOCAL_VALUE(pS0) +
	         __t * (__LIBM_LOCAL_VALUE(pS1) +
	              __t * (__LIBM_LOCAL_VALUE(pS2) +
	                   __t * (__LIBM_LOCAL_VALUE(pS3) +
	                        __t * (__LIBM_LOCAL_VALUE(pS4) +
	                             __t * __LIBM_LOCAL_VALUE(pS5))))));
	__q = __LIBM_LOCAL_VALUE(one) +
	    __t * (__LIBM_LOCAL_VALUE(qS1) +
	         __t * (__LIBM_LOCAL_VALUE(qS2) +
	              __t * (__LIBM_LOCAL_VALUE(qS3) +
	                   __t * __LIBM_LOCAL_VALUE(qS4))));
	__s = __ieee754_sqrt(__t);
	if (__ix >= __INT32_C(0x3FEF3333)) { /* if |x| > 0.975 */
		__w = __p / __q;
		__t = __LIBM_LOCAL_VALUE(pio2_hi) - (__IEEE754_DOUBLE_C(2.0) * (__s + __s * __w) - __LIBM_LOCAL_VALUE(pio2_lo));
	} else {
		__w = __s;
		__LIBM_SET_LOW_WORD(__w, 0);
		__c = (__t - __w * __w) / (__s + __w);
		__r = __p / __q;
		__p = __IEEE754_DOUBLE_C(2.0) * __s * __r - (__LIBM_LOCAL_VALUE(pio2_lo) - __IEEE754_DOUBLE_C(2.0) * __c);
		__q = __LIBM_LOCAL_VALUE(pio4_hi) - __IEEE754_DOUBLE_C(2.0) * __w;
		__t = __LIBM_LOCAL_VALUE(pio4_hi) - (__p - __q);
	}
	if (__hx > 0)
		return __t;
	return -__t;
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
#ifndef __libm_onel_defined
#define __libm_onel_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, onel, __IEEE854_LONG_DOUBLE_C(1.0))
#endif /* !__libm_onel_defined */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, asin_hugevall, __IEEE854_LONG_DOUBLE_C(1.0e+4932))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pio2_hil, __IEEE854_LONG_DOUBLE_C(0x1.921fb54442d1846ap+0))   /* pi/2 rounded to nearest to 64 bits.  */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pio2_lol, __IEEE854_LONG_DOUBLE_C(-0x7.6733ae8fe47c65d8p-68)) /* pi/2 - pio2_hi rounded to nearest to 64 bits.  */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pio4_hil, __IEEE854_LONG_DOUBLE_C(0xc.90fdaa22168c235p-4))    /* pi/4 rounded to nearest to 64 bits.  */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pS0l, __IEEE854_LONG_DOUBLE_C(-1.008714657938491626019651170502036851607E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pS1l, __IEEE854_LONG_DOUBLE_C(2.331460313214179572063441834101394865259E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pS2l, __IEEE854_LONG_DOUBLE_C(-1.863169762159016144159202387315381830227E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pS3l, __IEEE854_LONG_DOUBLE_C(5.930399351579141771077475766877674661747E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pS4l, __IEEE854_LONG_DOUBLE_C(-6.121291917696920296944056882932695185001E-1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pS5l, __IEEE854_LONG_DOUBLE_C(3.776934006243367487161248678019350338383E-3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, qS0l, __IEEE854_LONG_DOUBLE_C(-6.052287947630949712886794360635592886517E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, qS1l, __IEEE854_LONG_DOUBLE_C(1.671229145571899593737596543114258558503E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, qS2l, __IEEE854_LONG_DOUBLE_C(-1.707840117062586426144397688315411324388E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, qS3l, __IEEE854_LONG_DOUBLE_C(7.870295154902110425886636075950077640623E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, qS4l, __IEEE854_LONG_DOUBLE_C(-1.568433562487314651121702982333303458814E1))
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(asinl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_asinl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __t, __w, __p, __q, __c, __r, __s;
	__int32_t __ix;
	__uint32_t __se, __i0, __i1, __k;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__ix = __se & 0x7fff;
	__ix = (__ix << 16) | (__i0 >> 16);
	if (__ix >= __INT32_C(0x3fff8000)) { /* |x|>= 1 */
		if (__ix == __INT32_C(0x3fff8000) && ((__i0 - __UINT32_C(0x80000000)) | __i1) == 0)
			/* asin(1)=+-pi/2 with inexact */
			return __x * __LIBM_LOCAL_VALUE(pio2_hil) + __x * __LIBM_LOCAL_VALUE(pio2_lol);
		return (__x - __x) / (__x - __x);      /* asin(|x|>1) is NaN */
	} else if (__ix < __INT32_C(0x3ffe8000)) { /* |x|<0.5 */
		if (__ix < __INT32_C(0x3fde8000)) {    /* if |x| < 2**-33 */
			if (__LIBM_LOCAL_VALUE(asin_hugevall) + __x > __LIBM_LOCAL_VALUE(onel))
				return __x; /* return x with inexact if x!=0 */
		} else {
			__t = __x * __x;
			__p = __t * (__LIBM_LOCAL_VALUE(pS0l) +
			             __t * (__LIBM_LOCAL_VALUE(pS1l) +
			                    __t * (__LIBM_LOCAL_VALUE(pS2l) +
			                           __t * (__LIBM_LOCAL_VALUE(pS3l) +
			                                  __t * (__LIBM_LOCAL_VALUE(pS4l) +
			                                         __t * __LIBM_LOCAL_VALUE(pS5l))))));
			__q = __LIBM_LOCAL_VALUE(qS0l) +
			      __t * (__LIBM_LOCAL_VALUE(qS1l) +
			             __t * (__LIBM_LOCAL_VALUE(qS2l) +
			                    __t * (__LIBM_LOCAL_VALUE(qS3l) +
			                           __t * (__LIBM_LOCAL_VALUE(qS4l) +
			                                  __t))));
			__w = __p / __q;
			return __x + __x * __w;
		}
	}
	/* 1> |x|>= 0.5 */
	__w = __LIBM_LOCAL_VALUE(onel) - __ieee854_fabsl(__x);
	__t = __w * __IEEE854_LONG_DOUBLE_C(0.5);
	__p = __t * (__LIBM_LOCAL_VALUE(pS0l) +
	             __t * (__LIBM_LOCAL_VALUE(pS1l) +
	                    __t * (__LIBM_LOCAL_VALUE(pS2l) +
	                           __t * (__LIBM_LOCAL_VALUE(pS3l) +
	                                  __t * (__LIBM_LOCAL_VALUE(pS4l) +
	                                         __t * __LIBM_LOCAL_VALUE(pS5l))))));
	__q = __LIBM_LOCAL_VALUE(qS0l) +
	      __t * (__LIBM_LOCAL_VALUE(qS1l) +
	             __t * (__LIBM_LOCAL_VALUE(qS2l) +
	                    __t * (__LIBM_LOCAL_VALUE(qS3l) +
	                           __t * (__LIBM_LOCAL_VALUE(qS4l) +
	                                  __t))));
	__s = __ieee854_sqrtl(__t);
	if (__ix >= __INT32_C(0x3ffef999)) { /* if |x| > 0.975 */
		__w = __p / __q;
		__t = __LIBM_LOCAL_VALUE(pio2_hil) -
		      (__IEEE854_LONG_DOUBLE_C(2.0) * (__s + __s * __w) -
		       __LIBM_LOCAL_VALUE(pio2_lol));
	} else {
		__LIBM_GET_LDOUBLE_WORDS(__k, __i0, __i1, __s);
		__i1 = 0;
		__LIBM_SET_LDOUBLE_WORDS(__w, __k, __i0, __i1);
		__c = (__t - __w * __w) / (__s + __w);
		__r = __p / __q;
		__p = __IEEE854_LONG_DOUBLE_C(2.0) * __s * __r - (__LIBM_LOCAL_VALUE(pio2_lol) - __IEEE854_LONG_DOUBLE_C(2.0) * __c);
		__q = __LIBM_LOCAL_VALUE(pio4_hil) - __IEEE854_LONG_DOUBLE_C(2.0) * __w;
		__t = __LIBM_LOCAL_VALUE(pio4_hil) - (__p - __q);
	}
	if ((__se & 0x8000) == 0)
		return __t;
	return -__t;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ASIN_H */
