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
#ifndef _LIBM_LGAMMA_H
#define _LIBM_LGAMMA_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/cos.h>
#include <libm/fdlibm.h>
#include <libm/floor.h>
#include <libm/fmod.h>
#include <libm/kernel_cos.h>
#include <libm/kernel_sin.h>
#include <libm/log.h>
#include <libm/sin.h>

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
#ifndef __libm_pif_defined
#define __libm_pif_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pif, __IEEE754_FLOAT_C(3.1415927410e+00)) /* 0x40490fdb */
#endif /* !__libm_pif_defined */
#ifndef __libm_halff_defined
#define __libm_halff_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, halff, __IEEE754_FLOAT_C(5.0000000000e-01)) /* 0x3f000000 */
#endif /* !__libm_halff_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, two23f, __IEEE754_FLOAT_C(8.3886080000e+06)) /* 0x4b000000 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, a0f, __IEEE754_FLOAT_C(7.7215664089e-02))    /* 0x3d9e233f */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, a1f, __IEEE754_FLOAT_C(3.2246702909e-01))    /* 0x3ea51a66 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, a2f, __IEEE754_FLOAT_C(6.7352302372e-02))    /* 0x3d89f001 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, a3f, __IEEE754_FLOAT_C(2.0580807701e-02))    /* 0x3ca89915 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, a4f, __IEEE754_FLOAT_C(7.3855509982e-03))    /* 0x3bf2027e */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, a5f, __IEEE754_FLOAT_C(2.8905137442e-03))    /* 0x3b3d6ec6 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, a6f, __IEEE754_FLOAT_C(1.1927076848e-03))    /* 0x3a9c54a1 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, a7f, __IEEE754_FLOAT_C(5.1006977446e-04))    /* 0x3a05b634 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, a8f, __IEEE754_FLOAT_C(2.2086278477e-04))    /* 0x39679767 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, a9f, __IEEE754_FLOAT_C(1.0801156895e-04))    /* 0x38e28445 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, a10f, __IEEE754_FLOAT_C(2.5214456400e-05))   /* 0x37d383a2 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, a11f, __IEEE754_FLOAT_C(4.4864096708e-05))   /* 0x383c2c75 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, tcf, __IEEE754_FLOAT_C(1.4616321325e+00))    /* 0x3fbb16c3 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, tff, __IEEE754_FLOAT_C(-1.2148628384e-01))   /* 0xbdf8cdcd */
/* tt = -(tail of tf) */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, ttf, __IEEE754_FLOAT_C(6.6971006518e-09))   /* 0x31e61c52 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t0f, __IEEE754_FLOAT_C(4.8383611441e-01))   /* 0x3ef7b95e */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t1f, __IEEE754_FLOAT_C(-1.4758771658e-01))  /* 0xbe17213c */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t2f, __IEEE754_FLOAT_C(6.4624942839e-02))   /* 0x3d845a15 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t3f, __IEEE754_FLOAT_C(-3.2788541168e-02))  /* 0xbd064d47 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t4f, __IEEE754_FLOAT_C(1.7970675603e-02))   /* 0x3c93373d */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t5f, __IEEE754_FLOAT_C(-1.0314224288e-02))  /* 0xbc28fcfe */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t6f, __IEEE754_FLOAT_C(6.1005386524e-03))   /* 0x3bc7e707 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t7f, __IEEE754_FLOAT_C(-3.6845202558e-03))  /* 0xbb7177fe */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t8f, __IEEE754_FLOAT_C(2.2596477065e-03))   /* 0x3b141699 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t9f, __IEEE754_FLOAT_C(-1.4034647029e-03))  /* 0xbab7f476 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t10f, __IEEE754_FLOAT_C(8.8108185446e-04))  /* 0x3a66f867 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t11f, __IEEE754_FLOAT_C(-5.3859531181e-04)) /* 0xba0d3085 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t12f, __IEEE754_FLOAT_C(3.1563205994e-04))  /* 0x39a57b6b */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t13f, __IEEE754_FLOAT_C(-3.1275415677e-04)) /* 0xb9a3f927 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, t14f, __IEEE754_FLOAT_C(3.3552918467e-04))  /* 0x39afe9f7 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, u0f, __IEEE754_FLOAT_C(-7.7215664089e-02))  /* 0xbd9e233f */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, u1f, __IEEE754_FLOAT_C(6.3282704353e-01))   /* 0x3f2200f4 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, u2f, __IEEE754_FLOAT_C(1.4549225569e+00))   /* 0x3fba3ae7 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, u3f, __IEEE754_FLOAT_C(9.7771751881e-01))   /* 0x3f7a4bb2 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, u4f, __IEEE754_FLOAT_C(2.2896373272e-01))   /* 0x3e6a7578 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, u5f, __IEEE754_FLOAT_C(1.3381091878e-02))   /* 0x3c5b3c5e */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, v1f, __IEEE754_FLOAT_C(2.4559779167e+00))   /* 0x401d2ebe */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, v2f, __IEEE754_FLOAT_C(2.1284897327e+00))   /* 0x4008392d */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, v3f, __IEEE754_FLOAT_C(7.6928514242e-01))   /* 0x3f44efdf */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, v4f, __IEEE754_FLOAT_C(1.0422264785e-01))   /* 0x3dd572af */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, v5f, __IEEE754_FLOAT_C(3.2170924824e-03))   /* 0x3b52d5db */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, s0f, __IEEE754_FLOAT_C(-7.7215664089e-02))  /* 0xbd9e233f */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, s1f, __IEEE754_FLOAT_C(2.1498242021e-01))   /* 0x3e5c245a */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, s2f, __IEEE754_FLOAT_C(3.2577878237e-01))   /* 0x3ea6cc7a */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, s3f, __IEEE754_FLOAT_C(1.4635047317e-01))   /* 0x3e15dce6 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, s4f, __IEEE754_FLOAT_C(2.6642270386e-02))   /* 0x3cda40e4 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, s5f, __IEEE754_FLOAT_C(1.8402845599e-03))   /* 0x3af135b4 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, s6f, __IEEE754_FLOAT_C(3.1947532989e-05))   /* 0x3805ff67 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, r1f, __IEEE754_FLOAT_C(1.3920053244e+00))   /* 0x3fb22d3b */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, r2f, __IEEE754_FLOAT_C(7.2193557024e-01))   /* 0x3f38d0c5 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, r3f, __IEEE754_FLOAT_C(1.7193385959e-01))   /* 0x3e300f6e */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, r4f, __IEEE754_FLOAT_C(1.8645919859e-02))   /* 0x3c98bf54 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, r5f, __IEEE754_FLOAT_C(7.7794247773e-04))   /* 0x3a4beed6 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, r6f, __IEEE754_FLOAT_C(7.3266842264e-06))   /* 0x36f5d7bd */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, w0f, __IEEE754_FLOAT_C(4.1893854737e-01))   /* 0x3ed67f1d */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, w1f, __IEEE754_FLOAT_C(8.3333335817e-02))   /* 0x3daaaaab */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, w2f, __IEEE754_FLOAT_C(-2.7777778450e-03))  /* 0xbb360b61 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, w3f, __IEEE754_FLOAT_C(7.9365057172e-04))   /* 0x3a500cfd */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, w4f, __IEEE754_FLOAT_C(-5.9518753551e-04))  /* 0xba1c065c */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, w5f, __IEEE754_FLOAT_C(8.3633989561e-04))   /* 0x3a5b3dd2 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, w6f, __IEEE754_FLOAT_C(-1.6309292987e-03))  /* 0xbad5c4e8 */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(lgamma_sin_pif) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_lgamma_sin_pif)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __y, __z;
	__int32_t __n, __ix;
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	__ix &= __INT32_C(0x7fffffff);
	if (__ix < __INT32_C(0x3e800000))
#ifdef __ieee754_sinf
		return __ieee754_sinf(__LIBM_LOCAL_VALUE(pif) * __x);
#else /* __ieee754_sinf */
		return __ieee754_kernel_sinf(__LIBM_LOCAL_VALUE(pif) * __x, __LIBM_LOCAL_VALUE(zerof), 0);
#endif /* !__ieee754_sinf */
	__y = -__x; /* x is assume negative */
	/* argument reduction, make sure inexact flag not raised if input is an integer */
	__z = __ieee754_floorf(__y);
	if (__z != __y) { /* inexact anyway */
		__y *= __IEEE754_FLOAT_C(0.5);
		__y = __IEEE754_FLOAT_C(2.0) * (__y - __ieee754_floorf(__y)); /* y = |x| mod 2.0 */
		__n = (__int32_t)(__y * __IEEE754_FLOAT_C(4.0));
	} else {
		if (__ix >= __INT32_C(0x4b800000)) {
			__y = __LIBM_LOCAL_VALUE(zerof);
			__n = 0; /* y must be even */
		} else {
			if (__ix < __INT32_C(0x4b000000))
				__z = __y + __LIBM_LOCAL_VALUE(two23f); /* exact */
			__LIBM_GET_FLOAT_WORD(__n, __z);
			__n &= 1;
			__y = __n;
			__n <<= 2;
		}
	}
#ifdef __ieee754_sinf
	switch ((int)__n) {
	case 0:
		__y = __ieee754_sinf(__LIBM_LOCAL_VALUE(pif) * __y);
		break;
	case 1:
	case 2:
		__y = __ieee754_cosf(__LIBM_LOCAL_VALUE(pif) * (__IEEE754_FLOAT_C(0.5) - __y));
		break;
	case 3:
	case 4:
		__y = __ieee754_sinf(__LIBM_LOCAL_VALUE(pif) * (__LIBM_LOCAL_VALUE(onef) - __y));
		break;
	case 5:
	case 6:
		__y = -__ieee754_cosf(__LIBM_LOCAL_VALUE(pif) * (__y - __IEEE754_FLOAT_C(1.5)));
		break;
	default:
		__y = __ieee754_sinf(__LIBM_LOCAL_VALUE(pif) * (__y - __IEEE754_FLOAT_C(2.0)));
		break;
	}
#else  /* __ieee754_sinf */
	switch ((int)__n) {
	case 0:
		__y = __ieee754_kernel_sinf(__LIBM_LOCAL_VALUE(pif) * __y, __LIBM_LOCAL_VALUE(zerof), 0);
		break;
	case 1:
	case 2:
		__y = __ieee754_kernel_cosf(__LIBM_LOCAL_VALUE(pif) * (__IEEE754_FLOAT_C(0.5) - __y), __LIBM_LOCAL_VALUE(zerof));
		break;
	case 3:
	case 4:
		__y = __ieee754_kernel_sinf(__LIBM_LOCAL_VALUE(pif) * (__LIBM_LOCAL_VALUE(onef) - __y), __LIBM_LOCAL_VALUE(zerof), 0);
		break;
	case 5:
	case 6:
		__y = -__ieee754_kernel_cosf(__LIBM_LOCAL_VALUE(pif) * (__y - __IEEE754_FLOAT_C(1.5)), __LIBM_LOCAL_VALUE(zerof));
		break;
	default:
		__y = __ieee754_kernel_sinf(__LIBM_LOCAL_VALUE(pif) * (__y - __IEEE754_FLOAT_C(2.0)), __LIBM_LOCAL_VALUE(zerof), 0);
		break;
	}
#endif /* !__ieee754_sinf */
	return -__y;
}

__LIBM_LOCAL_FUNC(lgammaf) __ATTR_WUNUSED __ATTR_NONNULL((2)) __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_lgammaf)(__IEEE754_FLOAT_TYPE__ __x, int *__signgamp) {
	__IEEE754_FLOAT_TYPE__ __t, __y, __z, __nadj = 0;
	__IEEE754_FLOAT_TYPE__ __p, __p1, __p2, __p3, __q, __r, __w;
	__int32_t __i, __hx, __ix;
	__LIBM_GET_FLOAT_WORD(__hx, __x);

	/* purge off +-inf, NaN, +-0, and negative arguments */
	*__signgamp = 1;
	__ix        = __hx & __INT32_C(0x7fffffff);
	if (__ix >= __INT32_C(0x7f800000))
		return __x * __x;
	if (__ix == 0) {
		if (__hx < 0)
			*__signgamp = -1;
		return __LIBM_LOCAL_VALUE(onef) / __ieee754_fabsf(__x);
	}
	if (__ix < __INT32_C(0x1c800000)) {
		/* |x|<2**-70, return -log(|x|) */
		if (__hx < 0) {
			*__signgamp = -1;
			return -__ieee754_logf(-__x);
		} else {
			return -__ieee754_logf(__x);
		}
	}
	if (__hx < 0) {
		if (__ix >= __INT32_C(0x4b000000)) /* |x|>=2**23, must be -integer */
			return __x / __LIBM_LOCAL_VALUE(zerof);
		__t = __ieee754_lgamma_sin_pif(__x);
		if (__t == __LIBM_LOCAL_VALUE(zerof))
			return __LIBM_LOCAL_VALUE(onef) / __ieee754_fabsf(__t); /* -integer */
		__nadj = __ieee754_logf(__LIBM_LOCAL_VALUE(pif) / __ieee754_fabsf(__t * __x));
		if (__t < __LIBM_LOCAL_VALUE(zerof))
			*__signgamp = -1;
		__x = -__x;
	}

	/* purge off 1 and 2 */
	if (__ix == __INT32_C(0x3f800000) || __ix == __INT32_C(0x40000000)) {
		__r = 0;
	} else if (__ix < __INT32_C(0x40000000)) {
		/* for x < 2.0 */
		if (__ix <= __INT32_C(0x3f666666)) { /* lgamma(x) = lgamma(x+1)-log(x) */
			__r = -__ieee754_logf(__x);
			if (__ix >= __INT32_C(0x3f3b4a20)) {
				__y = __LIBM_LOCAL_VALUE(onef) - __x;
				__i = 0;
			} else if (__ix >= __INT32_C(0x3e6d3308)) {
				__y = __x - (__LIBM_LOCAL_VALUE(tcf) - __LIBM_LOCAL_VALUE(onef));
				__i = 1;
			} else {
				__y = __x;
				__i = 2;
			}
		} else {
			__r = __LIBM_LOCAL_VALUE(zerof);
			if (__ix >= __INT32_C(0x3fdda618)) {
				__y = __IEEE754_FLOAT_C(2.0) - __x;
				__i = 0;
			} /* [1.7316,2] */
			else if (__ix >= __INT32_C(0x3F9da620)) {
				__y = __x - __LIBM_LOCAL_VALUE(tcf);
				__i = 1;
			} /* [1.23,1.73] */
			else {
				__y = __x - __LIBM_LOCAL_VALUE(onef);
				__i = 2;
			}
		}
		switch ((int)__i) {
		case 0:
			__z  = __y * __y;
			__p1 = __LIBM_LOCAL_VALUE(a0f) +
			       __z * (__LIBM_LOCAL_VALUE(a2f) +
			              __z * (__LIBM_LOCAL_VALUE(a4f) +
			                     __z * (__LIBM_LOCAL_VALUE(a6f) +
			                            __z * (__LIBM_LOCAL_VALUE(a8f) +
			                                   __z * __LIBM_LOCAL_VALUE(a10f)))));
			__p2 = __z * (__LIBM_LOCAL_VALUE(a1f) +
			              __z * (__LIBM_LOCAL_VALUE(a3f) +
			                     __z * (__LIBM_LOCAL_VALUE(a5f) +
			                            __z * (__LIBM_LOCAL_VALUE(a7f) +
			                                   __z * (__LIBM_LOCAL_VALUE(a9f) +
			                                          __z * __LIBM_LOCAL_VALUE(a11f))))));
			__p  = __y * __p1 + __p2;
			__r += (__p - __IEEE754_FLOAT_C(0.5) * __y);
			break;
		case 1:
			__z  = __y * __y;
			__w  = __z * __y;
			__p1 = __LIBM_LOCAL_VALUE(t0f) +
			       __w * (__LIBM_LOCAL_VALUE(t3f) +
			              __w * (__LIBM_LOCAL_VALUE(t6f) +
			                     __w * (__LIBM_LOCAL_VALUE(t9f) +
			                            __w * __LIBM_LOCAL_VALUE(t12f)))); /* parallel comp */
			__p2 = __LIBM_LOCAL_VALUE(t1f) +
			       __w * (__LIBM_LOCAL_VALUE(t4f) +
			              __w * (__LIBM_LOCAL_VALUE(t7f) +
			                     __w * (__LIBM_LOCAL_VALUE(t10f) +
			                            __w * __LIBM_LOCAL_VALUE(t13f))));
			__p3 = __LIBM_LOCAL_VALUE(t2f) +
			       __w * (__LIBM_LOCAL_VALUE(t5f) +
			              __w * (__LIBM_LOCAL_VALUE(t8f) +
			                     __w * (__LIBM_LOCAL_VALUE(t11f) +
			                            __w * __LIBM_LOCAL_VALUE(t14f))));
			__p  = __z * __p1 - (__LIBM_LOCAL_VALUE(ttf) - __w * (__p2 + __y * __p3));
			__r += (__LIBM_LOCAL_VALUE(tff) + __p);
			break;
		case 2:
			__p1 = __y * (__LIBM_LOCAL_VALUE(u0f) +
			              __y * (__LIBM_LOCAL_VALUE(u1f) +
			                     __y * (__LIBM_LOCAL_VALUE(u2f) +
			                            __y * (__LIBM_LOCAL_VALUE(u3f) +
			                                   __y * (__LIBM_LOCAL_VALUE(u4f) +
			                                          __y * __LIBM_LOCAL_VALUE(u5f))))));
			__p2 = __LIBM_LOCAL_VALUE(onef) +
			       __y * (__LIBM_LOCAL_VALUE(v1f) +
			              __y * (__LIBM_LOCAL_VALUE(v2f) +
			                     __y * (__LIBM_LOCAL_VALUE(v3f) +
			                            __y * (__LIBM_LOCAL_VALUE(v4f) +
			                                   __y * __LIBM_LOCAL_VALUE(v5f)))));
			__r += (-__IEEE754_FLOAT_C(0.5) * __y + __p1 / __p2);
			break;
		}
	} else if (__ix < __INT32_C(0x41000000)) { /* x < 8.0 */
		__i = (__int32_t)__x;
		__t = __LIBM_LOCAL_VALUE(zerof);
		__y = __x - (__IEEE754_FLOAT_TYPE__)__i;
		__p = __y * (__LIBM_LOCAL_VALUE(s0f) +
		             __y * (__LIBM_LOCAL_VALUE(s1f) +
		                    __y * (__LIBM_LOCAL_VALUE(s2f) +
		                           __y * (__LIBM_LOCAL_VALUE(s3f) +
		                                  __y * (__LIBM_LOCAL_VALUE(s4f) +
		                                         __y * (__LIBM_LOCAL_VALUE(s5f) +
		                                                __y * __LIBM_LOCAL_VALUE(s6f)))))));
		__q = __LIBM_LOCAL_VALUE(onef) +
		      __y * (__LIBM_LOCAL_VALUE(r1f) +
		             __y * (__LIBM_LOCAL_VALUE(r2f) +
		                    __y * (__LIBM_LOCAL_VALUE(r3f) +
		                           __y * (__LIBM_LOCAL_VALUE(r4f) +
		                                  __y * (__LIBM_LOCAL_VALUE(r5f) +
		                                         __y * __LIBM_LOCAL_VALUE(r6f))))));
		__r = __LIBM_LOCAL_VALUE(halff) * __y + __p / __q;
		__z = __LIBM_LOCAL_VALUE(onef); /* lgamma(1+s) = log(s) + lgamma(s) */
		switch ((int)__i) {
		case 7:
			__z *= (__y + __IEEE754_FLOAT_C(6.0));
			__ATTR_FALLTHROUGH
		case 6:
			__z *= (__y + __IEEE754_FLOAT_C(5.0));
			__ATTR_FALLTHROUGH
		case 5:
			__z *= (__y + __IEEE754_FLOAT_C(4.0));
			__ATTR_FALLTHROUGH
		case 4:
			__z *= (__y + __IEEE754_FLOAT_C(3.0));
			__ATTR_FALLTHROUGH
		case 3:
			__z *= (__y + __IEEE754_FLOAT_C(2.0));
			__r += __ieee754_logf(__z);
			break;
		}
	} else if (__ix < __INT32_C(0x5c800000)) {
		/* 8.0 <= __x < 2**58 */
		__t = __ieee754_logf(__x);
		__z = __LIBM_LOCAL_VALUE(onef) / __x;
		__y = __z * __z;
		__w = __LIBM_LOCAL_VALUE(w0f) +
		      __z * (__LIBM_LOCAL_VALUE(w1f) +
		             __y * (__LIBM_LOCAL_VALUE(w2f) +
		                    __y * (__LIBM_LOCAL_VALUE(w3f) +
		                           __y * (__LIBM_LOCAL_VALUE(w4f) +
		                                  __y * (__LIBM_LOCAL_VALUE(w5f) +
		                                         __y * __LIBM_LOCAL_VALUE(w6f))))));
		__r = (__x - __LIBM_LOCAL_VALUE(halff)) *
		      (__t - __LIBM_LOCAL_VALUE(onef)) +
		      __w;
	} else {
		/* 2**58 <= __x <= inf */
		__r = __x * (__ieee754_logf(__x) - __LIBM_LOCAL_VALUE(onef));
	}
	if (__hx < 0)
		__r = __nadj - __r;
	return __r;
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
#ifndef __libm_zero_defined
#define __libm_zero_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, zero, __IEEE754_DOUBLE_C(0.00000000000000000000e+00)) /* 0x00000000, 0x00000000 */
#endif /* !__libm_zero_defined */
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.00000000000000000000e+00)) /* 0x3FF00000, 0x00000000 */
#endif /* !__libm_one_defined */
#ifndef __libm_pi_defined
#define __libm_pi_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pi, __IEEE754_DOUBLE_C(3.1415926535897931160E+00)) /* 0x400921FB, 0x54442D18 */
#endif /* !__libm_pi_defined */
#ifndef __libm_half_defined
#define __libm_half_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, half, __IEEE754_DOUBLE_C(5.00000000000000000000e-01)) /* 0x3FE00000, 0x00000000 */
#endif /* !__libm_half_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, two52, __IEEE754_DOUBLE_C(4.50359962737049600000e+15)) /* 0x43300000, 0x00000000 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, a0, __IEEE754_DOUBLE_C(7.72156649015328655494e-02))    /* 0x3FB3C467, 0xE37DB0C8 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, a1, __IEEE754_DOUBLE_C(3.22467033424113591611e-01))    /* 0x3FD4A34C, 0xC4A60FAD */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, a2, __IEEE754_DOUBLE_C(6.73523010531292681824e-02))    /* 0x3FB13E00, 0x1A5562A7 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, a3, __IEEE754_DOUBLE_C(2.05808084325167332806e-02))    /* 0x3F951322, 0xAC92547B */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, a4, __IEEE754_DOUBLE_C(7.38555086081402883957e-03))    /* 0x3F7E404F, 0xB68FEFE8 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, a5, __IEEE754_DOUBLE_C(2.89051383673415629091e-03))    /* 0x3F67ADD8, 0xCCB7926B */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, a6, __IEEE754_DOUBLE_C(1.19270763183362067845e-03))    /* 0x3F538A94, 0x116F3F5D */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, a7, __IEEE754_DOUBLE_C(5.10069792153511336608e-04))    /* 0x3F40B6C6, 0x89B99C00 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, a8, __IEEE754_DOUBLE_C(2.20862790713908385557e-04))    /* 0x3F2CF2EC, 0xED10E54D */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, a9, __IEEE754_DOUBLE_C(1.08011567247583939954e-04))    /* 0x3F1C5088, 0x987DFB07 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, a10, __IEEE754_DOUBLE_C(2.52144565451257326939e-05))   /* 0x3EFA7074, 0x428CFA52 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, a11, __IEEE754_DOUBLE_C(4.48640949618915160150e-05))   /* 0x3F07858E, 0x90A45837 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, tc, __IEEE754_DOUBLE_C(1.46163214496836224576e+00))    /* 0x3FF762D8, 0x6356BE3F */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, tf, __IEEE754_DOUBLE_C(-1.21486290535849611461e-01))   /* 0xBFBF19B9, 0xBCC38A42 */
/* tt = -(tail of tf) */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, tt, __IEEE754_DOUBLE_C(-3.63867699703950536541e-18))  /* 0xBC50C7CA, 0xA48A971F */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t0, __IEEE754_DOUBLE_C(4.83836122723810047042e-01))   /* 0x3FDEF72B, 0xC8EE38A2 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t1, __IEEE754_DOUBLE_C(-1.47587722994593911752e-01))  /* 0xBFC2E427, 0x8DC6C509 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t2, __IEEE754_DOUBLE_C(6.46249402391333854778e-02))   /* 0x3FB08B42, 0x94D5419B */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t3, __IEEE754_DOUBLE_C(-3.27885410759859649565e-02))  /* 0xBFA0C9A8, 0xDF35B713 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t4, __IEEE754_DOUBLE_C(1.79706750811820387126e-02))   /* 0x3F9266E7, 0x970AF9EC */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t5, __IEEE754_DOUBLE_C(-1.03142241298341437450e-02))  /* 0xBF851F9F, 0xBA91EC6A */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t6, __IEEE754_DOUBLE_C(6.10053870246291332635e-03))   /* 0x3F78FCE0, 0xE370E344 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t7, __IEEE754_DOUBLE_C(-3.68452016781138256760e-03))  /* 0xBF6E2EFF, 0xB3E914D7 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t8, __IEEE754_DOUBLE_C(2.25964780900612472250e-03))   /* 0x3F6282D3, 0x2E15C915 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t9, __IEEE754_DOUBLE_C(-1.40346469989232843813e-03))  /* 0xBF56FE8E, 0xBF2D1AF1 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t10, __IEEE754_DOUBLE_C(8.81081882437654011382e-04))  /* 0x3F4CDF0C, 0xEF61A8E9 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t11, __IEEE754_DOUBLE_C(-5.38595305356740546715e-04)) /* 0xBF41A610, 0x9C73E0EC */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t12, __IEEE754_DOUBLE_C(3.15632070903625950361e-04))  /* 0x3F34AF6D, 0x6C0EBBF7 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t13, __IEEE754_DOUBLE_C(-3.12754168375120860518e-04)) /* 0xBF347F24, 0xECC38C38 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, t14, __IEEE754_DOUBLE_C(3.35529192635519073543e-04))  /* 0x3F35FD3E, 0xE8C2D3F4 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, u0, __IEEE754_DOUBLE_C(-7.72156649015328655494e-02))  /* 0xBFB3C467, 0xE37DB0C8 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, u1, __IEEE754_DOUBLE_C(6.32827064025093366517e-01))   /* 0x3FE4401E, 0x8B005DFF */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, u2, __IEEE754_DOUBLE_C(1.45492250137234768737e+00))   /* 0x3FF7475C, 0xD119BD6F */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, u3, __IEEE754_DOUBLE_C(9.77717527963372745603e-01))   /* 0x3FEF4976, 0x44EA8450 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, u4, __IEEE754_DOUBLE_C(2.28963728064692451092e-01))   /* 0x3FCD4EAE, 0xF6010924 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, u5, __IEEE754_DOUBLE_C(1.33810918536787660377e-02))   /* 0x3F8B678B, 0xBF2BAB09 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, v1, __IEEE754_DOUBLE_C(2.45597793713041134822e+00))   /* 0x4003A5D7, 0xC2BD619C */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, v2, __IEEE754_DOUBLE_C(2.12848976379893395361e+00))   /* 0x40010725, 0xA42B18F5 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, v3, __IEEE754_DOUBLE_C(7.69285150456672783825e-01))   /* 0x3FE89DFB, 0xE45050AF */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, v4, __IEEE754_DOUBLE_C(1.04222645593369134254e-01))   /* 0x3FBAAE55, 0xD6537C88 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, v5, __IEEE754_DOUBLE_C(3.21709242282423911810e-03))   /* 0x3F6A5ABB, 0x57D0CF61 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, s0, __IEEE754_DOUBLE_C(-7.72156649015328655494e-02))  /* 0xBFB3C467, 0xE37DB0C8 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, s1, __IEEE754_DOUBLE_C(2.14982415960608852501e-01))   /* 0x3FCB848B, 0x36E20878 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, s2, __IEEE754_DOUBLE_C(3.25778796408930981787e-01))   /* 0x3FD4D98F, 0x4F139F59 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, s3, __IEEE754_DOUBLE_C(1.46350472652464452805e-01))   /* 0x3FC2BB9C, 0xBEE5F2F7 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, s4, __IEEE754_DOUBLE_C(2.66422703033638609560e-02))   /* 0x3F9B481C, 0x7E939961 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, s5, __IEEE754_DOUBLE_C(1.84028451407337715652e-03))   /* 0x3F5E26B6, 0x7368F239 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, s6, __IEEE754_DOUBLE_C(3.19475326584100867617e-05))   /* 0x3F00BFEC, 0xDD17E945 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, r1, __IEEE754_DOUBLE_C(1.39200533467621045958e+00))   /* 0x3FF645A7, 0x62C4AB74 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, r2, __IEEE754_DOUBLE_C(7.21935547567138069525e-01))   /* 0x3FE71A18, 0x93D3DCDC */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, r3, __IEEE754_DOUBLE_C(1.71933865632803078993e-01))   /* 0x3FC601ED, 0xCCFBDF27 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, r4, __IEEE754_DOUBLE_C(1.86459191715652901344e-02))   /* 0x3F9317EA, 0x742ED475 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, r5, __IEEE754_DOUBLE_C(7.77942496381893596434e-04))   /* 0x3F497DDA, 0xCA41A95B */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, r6, __IEEE754_DOUBLE_C(7.32668430744625636189e-06))   /* 0x3EDEBAF7, 0xA5B38140 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, w0, __IEEE754_DOUBLE_C(4.18938533204672725052e-01))   /* 0x3FDACFE3, 0x90C97D69 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, w1, __IEEE754_DOUBLE_C(8.33333333333329678849e-02))   /* 0x3FB55555, 0x5555553B */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, w2, __IEEE754_DOUBLE_C(-2.77777777728775536470e-03))  /* 0xBF66C16C, 0x16B02E5C */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, w3, __IEEE754_DOUBLE_C(7.93650558643019558500e-04))   /* 0x3F4A019F, 0x98CF38B6 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, w4, __IEEE754_DOUBLE_C(-5.95187557450339963135e-04))  /* 0xBF4380CB, 0x8C0FE741 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, w5, __IEEE754_DOUBLE_C(8.36339918996282139126e-04))   /* 0x3F4B67BA, 0x4CDAD5D1 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, w6, __IEEE754_DOUBLE_C(-1.63092934096575273989e-03))  /* 0xBF5AB89D, 0x0B9E43E4 */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(lgamma_sin_pi) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_lgamma_sin_pi)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __y, __z;
	__int32_t __n, __ix;
	__LIBM_GET_HIGH_WORD(__ix, __x);
	__ix &= __INT32_C(0x7fffffff);
	if (__ix < __INT32_C(0x3fd00000))
		return __ieee754_sin(__LIBM_LOCAL_VALUE(pi) * __x);
	__y = -__x; /* x is assume negative */
	/* argument reduction, make sure inexact flag not raised if input is an integer */
	__z = __ieee754_floor(__y);
	if (__z != __y) { /* inexact anyway */
		__y *= __IEEE754_DOUBLE_C(0.5);
		__y = __IEEE754_DOUBLE_C(2.0) * (__y - __ieee754_floor(__y)); /* y = |x| mod 2.0 */
		__n = (__int32_t)(__y * __IEEE754_DOUBLE_C(4.0));
	} else {
		if (__ix >= __INT32_C(0x43400000)) {
			__y = __LIBM_LOCAL_VALUE(zero);
			__n   = 0; /* y must be even */
		} else {
			if (__ix < __INT32_C(0x43300000))
				__z = __y + __LIBM_LOCAL_VALUE(two52); /* exact */
			__LIBM_GET_LOW_WORD(__n, __z);
			__n &= 1;
			__y = __n;
			__n <<= 2;
		}
	}
#ifdef __ieee754_sin
	switch ((int)__n) {
	case 0:
		__y = __ieee754_sin(__LIBM_LOCAL_VALUE(pi) * __y);
		break;
	case 1:
	case 2:
		__y = __ieee754_cos(__LIBM_LOCAL_VALUE(pi) * (__IEEE754_DOUBLE_C(0.5) - __y));
		break;
	case 3:
	case 4:
		__y = __ieee754_sin(__LIBM_LOCAL_VALUE(pi) * (__LIBM_LOCAL_VALUE(one) - __y));
		break;
	case 5:
	case 6:
		__y = -__ieee754_cos(__LIBM_LOCAL_VALUE(pi) * (__y - __IEEE754_DOUBLE_C(1.5)));
		break;
	default:
		__y = __ieee754_sin(__LIBM_LOCAL_VALUE(pi) * (__y - __IEEE754_DOUBLE_C(2.0)));
		break;
	}
#else /* __ieee754_sin */
	switch ((int)__n) {
	case 0:
		__y = __ieee754_kernel_sin(__LIBM_LOCAL_VALUE(pi) * __y, __LIBM_LOCAL_VALUE(zero), 0);
		break;
	case 1:
	case 2:
		__y = __ieee754_kernel_cos(__LIBM_LOCAL_VALUE(pi) * (__IEEE754_DOUBLE_C(0.5) - __y), __LIBM_LOCAL_VALUE(zero));
		break;
	case 3:
	case 4:
		__y = __ieee754_kernel_sin(__LIBM_LOCAL_VALUE(pi) * (__LIBM_LOCAL_VALUE(one) - __y), __LIBM_LOCAL_VALUE(zero), 0);
		break;
	case 5:
	case 6:
		__y = -__ieee754_kernel_cos(__LIBM_LOCAL_VALUE(pi) * (__y - __IEEE754_DOUBLE_C(1.5)), __LIBM_LOCAL_VALUE(zero));
		break;
	default:
		__y = __ieee754_kernel_sin(__LIBM_LOCAL_VALUE(pi) * (__y - __IEEE754_DOUBLE_C(2.0)), __LIBM_LOCAL_VALUE(zero), 0);
		break;
	}
#endif /* !__ieee754_sin */
	return -__y;
}

__LIBM_LOCAL_FUNC(lgamma) __ATTR_WUNUSED __ATTR_NONNULL((2)) __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_lgamma)(__IEEE754_DOUBLE_TYPE__ __x, int *__signgamp) {
	__IEEE754_DOUBLE_TYPE__ __t, __y, __z, __nadj = 0;
	__IEEE754_DOUBLE_TYPE__ __p, __p1, __p2, __p3, __q, __r, __w;
	__int32_t __i, __hx, lx, __ix;
	__LIBM_GET_DOUBLE_WORDS(__hx, lx, __x);
	/* purge off +-inf, NaN, +-0, and negative arguments */
	*__signgamp = 1;
	__ix        = __hx & __INT32_C(0x7fffffff);
	if (__ix >= __INT32_C(0x7ff00000))
		return __x * __x;
	if ((__ix | lx) == 0) {
		if (__hx < 0)
			*__signgamp = -1;
		return __LIBM_LOCAL_VALUE(one) / __ieee754_fabs(__x);
	}
	if (__ix < __INT32_C(0x3b900000)) {
		/* |x|<2**-70, return -log(|x|) */
		if (__hx < 0) {
			*__signgamp = -1;
			return -__ieee754_log(-__x);
		} else {
			return -__ieee754_log(__x);
		}
	}
	if (__hx < 0) {
		if (__ix >= __INT32_C(0x43300000)) /* |x|>=2**52, must be -integer */
			return __x / __LIBM_LOCAL_VALUE(zero);
		__t = __ieee754_lgamma_sin_pi(__x);
		if (__t == __LIBM_LOCAL_VALUE(zero))
			return __LIBM_LOCAL_VALUE(one) / __ieee754_fabs(__t); /* -integer */
		__nadj = __ieee754_log(__LIBM_LOCAL_VALUE(pi) / __ieee754_fabs(__t * __x));
		if (__t < __LIBM_LOCAL_VALUE(zero))
			*__signgamp = -1;
		__x = -__x;
	}
	/* purge off 1 and 2 */
	if ((((__ix - __INT32_C(0x3ff00000)) | lx) == 0) ||
	    (((__ix - __INT32_C(0x40000000)) | lx) == 0)) {
		__r = 0;
	} else if (__ix < __INT32_C(0x40000000)) {
		/* for x < 2.0 */
		if (__ix <= __INT32_C(0x3feccccc)) { /* lgamma(__x) = lgamma(__x+1)-log(__x) */
			__r = -__ieee754_log(__x);
			if (__ix >= __INT32_C(0x3FE76944)) {
				__y = __LIBM_LOCAL_VALUE(one) - __x;
				__i = 0;
			} else if (__ix >= __INT32_C(0x3FCDA661)) {
				__y = __x - (__LIBM_LOCAL_VALUE(tc) - __LIBM_LOCAL_VALUE(one));
				__i = 1;
			} else {
				__y = __x;
				__i = 2;
			}
		} else {
			__r = __LIBM_LOCAL_VALUE(zero);
			if (__ix >= __INT32_C(0x3FFBB4C3)) {
				/* [1.7316,2] */
				__y = __IEEE754_DOUBLE_C(2.0) - __x;
				__i = 0;
			} else if (__ix >= __INT32_C(0x3FF3B4C4)) {
				/* [1.23,1.73] */
				__y = __x - __LIBM_LOCAL_VALUE(tc);
				__i = 1;
			} else {
				__y = __x - __LIBM_LOCAL_VALUE(one);
				__i = 2;
			}
		}
		switch ((int)__i) {
		case 0:
			__z  = __y * __y;
			__p1 = __LIBM_LOCAL_VALUE(a0) +
			       __z * (__LIBM_LOCAL_VALUE(a2) +
			              __z * (__LIBM_LOCAL_VALUE(a4) +
			                     __z * (__LIBM_LOCAL_VALUE(a6) +
			                            __z * (__LIBM_LOCAL_VALUE(a8) +
			                                   __z * __LIBM_LOCAL_VALUE(a10)))));
			__p2 = __z * (__LIBM_LOCAL_VALUE(a1) +
			              __z * (__LIBM_LOCAL_VALUE(a3) +
			                     __z * (__LIBM_LOCAL_VALUE(a5) +
			                            __z * (__LIBM_LOCAL_VALUE(a7) +
			                                   __z * (__LIBM_LOCAL_VALUE(a9) +
			                                          __z * __LIBM_LOCAL_VALUE(a11))))));
			__p  = __y * __p1 + __p2;
			__r += (__p - __IEEE754_DOUBLE_C(0.5) * __y);
			break;
		case 1:
			__z  = __y * __y;
			__w  = __z * __y;
			__p1 = __LIBM_LOCAL_VALUE(t0) +
			       __w * (__LIBM_LOCAL_VALUE(t3) +
			              __w * (__LIBM_LOCAL_VALUE(t6) +
			                     __w * (__LIBM_LOCAL_VALUE(t9) +
			                            __w * __LIBM_LOCAL_VALUE(t12)))); /* parallel comp */
			__p2 = __LIBM_LOCAL_VALUE(t1) +
			       __w * (__LIBM_LOCAL_VALUE(t4) +
			              __w * (__LIBM_LOCAL_VALUE(t7) +
			                     __w * (__LIBM_LOCAL_VALUE(t10) +
			                            __w * __LIBM_LOCAL_VALUE(t13))));
			__p3 = __LIBM_LOCAL_VALUE(t2) +
			       __w * (__LIBM_LOCAL_VALUE(t5) +
			              __w * (__LIBM_LOCAL_VALUE(t8) +
			                     __w * (__LIBM_LOCAL_VALUE(t11) +
			                            __w * __LIBM_LOCAL_VALUE(t14))));
			__p  = __z * __p1 - (__LIBM_LOCAL_VALUE(tt) - __w * (__p2 + __y * __p3));
			__r += (__LIBM_LOCAL_VALUE(tf) +
			        __p);
			break;
		case 2:
			__p1 = __y * (__LIBM_LOCAL_VALUE(u0) +
			              __y * (__LIBM_LOCAL_VALUE(u1) +
			                     __y * (__LIBM_LOCAL_VALUE(u2) +
			                            __y * (__LIBM_LOCAL_VALUE(u3) +
			                                   __y * (__LIBM_LOCAL_VALUE(u4) +
			                                          __y * __LIBM_LOCAL_VALUE(u5))))));
			__p2 = __LIBM_LOCAL_VALUE(one) +
			       __y * (__LIBM_LOCAL_VALUE(v1) +
			              __y * (__LIBM_LOCAL_VALUE(v2) +
			                     __y * (__LIBM_LOCAL_VALUE(v3) +
			                            __y * (__LIBM_LOCAL_VALUE(v4) +
			                                   __y * __LIBM_LOCAL_VALUE(v5)))));
			__r += (-__IEEE754_DOUBLE_C(0.5) * __y + __p1 / __p2);
			break;
		}
	} else if (__ix < __INT32_C(0x40200000)) { /* x < 8.0 */
		__i = (__int32_t)__x;
		__t = __LIBM_LOCAL_VALUE(zero);
		__y = __x - (__IEEE754_DOUBLE_TYPE__)__i;
		__p = __y * (__LIBM_LOCAL_VALUE(s0) +
		             __y * (__LIBM_LOCAL_VALUE(s1) +
		                    __y * (__LIBM_LOCAL_VALUE(s2) +
		                           __y * (__LIBM_LOCAL_VALUE(s3) +
		                                  __y * (__LIBM_LOCAL_VALUE(s4) +
		                                         __y * (__LIBM_LOCAL_VALUE(s5) +
		                                                __y * __LIBM_LOCAL_VALUE(s6)))))));
		__q = __LIBM_LOCAL_VALUE(one) +
		      __y * (__LIBM_LOCAL_VALUE(r1) +
		             __y * (__LIBM_LOCAL_VALUE(r2) +
		                    __y * (__LIBM_LOCAL_VALUE(r3) +
		                           __y * (__LIBM_LOCAL_VALUE(r4) +
		                                  __y * (__LIBM_LOCAL_VALUE(r5) +
		                                         __y * __LIBM_LOCAL_VALUE(r6))))));
		__r = __LIBM_LOCAL_VALUE(half) * __y + __p / __q;
		__z = __LIBM_LOCAL_VALUE(one); /* lgamma(1+s) = log(s) + lgamma(s) */
		switch ((int)__i) {
		case 7:
			__z *= (__y + __IEEE754_DOUBLE_C(6.0));
			__ATTR_FALLTHROUGH
		case 6:
			__z *= (__y + __IEEE754_DOUBLE_C(5.0));
			__ATTR_FALLTHROUGH
		case 5:
			__z *= (__y + __IEEE754_DOUBLE_C(4.0));
			__ATTR_FALLTHROUGH
		case 4:
			__z *= (__y + __IEEE754_DOUBLE_C(3.0));
			__ATTR_FALLTHROUGH
		case 3:
			__z *= (__y + __IEEE754_DOUBLE_C(2.0));
			__r += __ieee754_log(__z);
			break;
		}
		/* 8.0 <= __x < 2**58 */
	} else if (__ix < __INT32_C(0x43900000)) {
		__t = __ieee754_log(__x);
		__z = __LIBM_LOCAL_VALUE(one) / __x;
		__y = __z * __z;
		__w = __LIBM_LOCAL_VALUE(w0) +
		      __z * (__LIBM_LOCAL_VALUE(w1) +
		             __y * (__LIBM_LOCAL_VALUE(w2) +
		                    __y * (__LIBM_LOCAL_VALUE(w3) +
		                           __y * (__LIBM_LOCAL_VALUE(w4) +
		                                  __y * (__LIBM_LOCAL_VALUE(w5) +
		                                         __y * __LIBM_LOCAL_VALUE(w6))))));
		__r = (__x - __LIBM_LOCAL_VALUE(half)) *
		      (__t - __LIBM_LOCAL_VALUE(one)) +
		      __w;
	} else {
		/* 2**58 <= __x <= inf */
		__r = __x * (__ieee754_log(__x) - __LIBM_LOCAL_VALUE(one));
	}
	if (__hx < 0)
		__r = __nadj - __r;
	return __r;
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
#ifndef __libm_halfl_defined
#define __libm_halfl_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, halfl, __IEEE854_LONG_DOUBLE_C(0.5));
#endif /* !__libm_halfl_defined */
#ifndef __libm_onel_defined
#define __libm_onel_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, onel, __IEEE854_LONG_DOUBLE_C(1.0))
#endif /* !__libm_onel_defined */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, lgamma_pil, __IEEE854_LONG_DOUBLE_C(3.14159265358979323846264))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, two63l, __IEEE854_LONG_DOUBLE_C(9.223372036854775808e18))
/* lgam(1+__x) = 0.5 __x + __x a(__x)/b(__x)  -0.268402099609375 <= __x <= 0  peak relative error 6.6e-22 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, a0l, __IEEE854_LONG_DOUBLE_C(-6.343246574721079391729402781192128239938E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, a1l, __IEEE854_LONG_DOUBLE_C(1.856560238672465796768677717168371401378E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, a2l, __IEEE854_LONG_DOUBLE_C(2.404733102163746263689288466865843408429E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, a3l, __IEEE854_LONG_DOUBLE_C(8.804188795790383497379532868917517596322E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, a4l, __IEEE854_LONG_DOUBLE_C(1.135361354097447729740103745999661157426E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, a5l, __IEEE854_LONG_DOUBLE_C(3.766956539107615557608581581190400021285E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, b0l, __IEEE854_LONG_DOUBLE_C(8.214973713960928795704317259806842490498E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, b1l, __IEEE854_LONG_DOUBLE_C(1.026343508841367384879065363925870888012E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, b2l, __IEEE854_LONG_DOUBLE_C(4.553337477045763320522762343132210919277E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, b3l, __IEEE854_LONG_DOUBLE_C(8.506975785032585797446253359230031874803E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, b4l, __IEEE854_LONG_DOUBLE_C(6.042447899703295436820744186992189445813E1))
/* __LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, b5l, __IEEE854_LONG_DOUBLC(1.000000000000000000000000000000000000000E0)) */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, tcl, __IEEE854_LONG_DOUBLE_C(1.4616321449683623412626595423257213284682E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, tfl, __IEEE854_LONG_DOUBLE_C(-1.2148629053584961146050602565082954242826E-1)) /* double precision */
/* tt = (tail of tf), __i.e. tf + tt has extended precision. */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, ttl, __IEEE854_LONG_DOUBLE_C(3.3649914684731379602768989080467587736363E-18))
/* lgam ( 1.4616321449683623412626595423257213284682E0 ) = -1.2148629053584960809551455717769158215135617312999903886372437313313530E-1 */
/* lgam (__x + tc) = tf + tt + __x g(__x)/h(__x) - 0.230003726999612341262659542325721328468 <= __x <= 0.2699962730003876587373404576742786715318  peak relative error 2.1e-21 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, g0l, __IEEE854_LONG_DOUBLE_C(3.645529916721223331888305293534095553827E-18))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, g1l, __IEEE854_LONG_DOUBLE_C(5.126654642791082497002594216163574795690E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, g2l, __IEEE854_LONG_DOUBLE_C(8.828603575854624811911631336122070070327E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, g3l, __IEEE854_LONG_DOUBLE_C(5.464186426932117031234820886525701595203E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, g4l, __IEEE854_LONG_DOUBLE_C(1.455427403530884193180776558102868592293E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, g5l, __IEEE854_LONG_DOUBLE_C(1.541735456969245924860307497029155838446E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, g6l, __IEEE854_LONG_DOUBLE_C(4.335498275274822298341872707453445815118E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, h0l, __IEEE854_LONG_DOUBLE_C(1.059584930106085509696730443974495979641E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, h1l, __IEEE854_LONG_DOUBLE_C(2.147921653490043010629481226937850618860E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, h2l, __IEEE854_LONG_DOUBLE_C(1.643014770044524804175197151958100656728E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, h3l, __IEEE854_LONG_DOUBLE_C(5.869021995186925517228323497501767586078E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, h4l, __IEEE854_LONG_DOUBLE_C(9.764244777714344488787381271643502742293E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, h5l, __IEEE854_LONG_DOUBLE_C(6.442485441570592541741092969581997002349E1))
/* __LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, h6l, __IEEE854_LONG_DOUBLC(1.000000000000000000000000000000000000000E0)) */
/* lgam (__x+1) = -0.5 __x + __x u(__x)/v(__x)  -0.100006103515625 <= __x <= 0.231639862060546875  peak relative error 1.3e-21 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, u0l, __IEEE854_LONG_DOUBLE_C(-8.886217500092090678492242071879342025627E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, u1l, __IEEE854_LONG_DOUBLE_C(6.840109978129177639438792958320783599310E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, u2l, __IEEE854_LONG_DOUBLE_C(2.042626104514127267855588786511809932433E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, u3l, __IEEE854_LONG_DOUBLE_C(1.911723903442667422201651063009856064275E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, u4l, __IEEE854_LONG_DOUBLE_C(7.447065275665887457628865263491667767695E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, u5l, __IEEE854_LONG_DOUBLE_C(1.132256494121790736268471016493103952637E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, u6l, __IEEE854_LONG_DOUBLE_C(4.484398885516614191003094714505960972894E0))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, v0l, __IEEE854_LONG_DOUBLE_C(1.150830924194461522996462401210374632929E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, v1l, __IEEE854_LONG_DOUBLE_C(3.399692260848747447377972081399737098610E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, v2l, __IEEE854_LONG_DOUBLE_C(3.786631705644460255229513563657226008015E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, v3l, __IEEE854_LONG_DOUBLE_C(1.966450123004478374557778781564114347876E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, v4l, __IEEE854_LONG_DOUBLE_C(4.741359068914069299837355438370682773122E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, v5l, __IEEE854_LONG_DOUBLE_C(4.508989649747184050907206782117647852364E1))
/* __LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, v6l, __IEEE854_LONG_DOUBLC(1.000000000000000000000000000000000000000E0)) */
/* lgam (__x+2) = .5 __x + __x s(__x)/__r(__x)  0 <= __x <= 1  peak relative error 7.2e-22 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, s0l, __IEEE854_LONG_DOUBLE_C(1.454726263410661942989109455292824853344E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, s1l, __IEEE854_LONG_DOUBLE_C(-3.901428390086348447890408306153378922752E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, s2l, __IEEE854_LONG_DOUBLE_C(-6.573568698209374121847873064292963089438E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, s3l, __IEEE854_LONG_DOUBLE_C(-3.319055881485044417245964508099095984643E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, s4l, __IEEE854_LONG_DOUBLE_C(-7.094891568758439227560184618114707107977E5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, s5l, __IEEE854_LONG_DOUBLE_C(-6.263426646464505837422314539808112478303E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, s6l, __IEEE854_LONG_DOUBLE_C(-1.684926520999477529949915657519454051529E3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, r0l, __IEEE854_LONG_DOUBLE_C(-1.883978160734303518163008696712983134698E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, r1l, __IEEE854_LONG_DOUBLE_C(-2.815206082812062064902202753264922306830E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, r2l, __IEEE854_LONG_DOUBLE_C(-1.600245495251915899081846093343626358398E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, r3l, __IEEE854_LONG_DOUBLE_C(-4.310526301881305003489257052083370058799E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, r4l, __IEEE854_LONG_DOUBLE_C(-5.563807682263923279438235987186184968542E5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, r5l, __IEEE854_LONG_DOUBLE_C(-3.027734654434169996032905158145259713083E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, r6l, __IEEE854_LONG_DOUBLE_C(-4.501995652861105629217250715790764371267E2))
/* __LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, r6l, __IEEE854_LONG_DOUBLC(1.000000000000000000000000000000000000000E0)) */
/* lgam(__x) = ( __x - 0.5 ) * log(__x) - __x + LS2PI + 1/__x __w(1/__x^2)  __x >= 8  Peak relative error 1.51e-21  w0 = LS2PI - 0.5 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, w0l, __IEEE854_LONG_DOUBLE_C(4.189385332046727417803e-1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, w1l, __IEEE854_LONG_DOUBLE_C(8.333333333333331447505E-2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, w2l, __IEEE854_LONG_DOUBLE_C(-2.777777777750349603440E-3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, w3l, __IEEE854_LONG_DOUBLE_C(7.936507795855070755671E-4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, w4l, __IEEE854_LONG_DOUBLE_C(-5.952345851765688514613E-4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, w5l, __IEEE854_LONG_DOUBLE_C(8.412723297322498080632E-4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, w6l, __IEEE854_LONG_DOUBLE_C(-1.880801938119376907179E-3))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, w7l, __IEEE854_LONG_DOUBLE_C(4.885026142432270781165E-3))
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(lgamma_sin_pil) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_lgamma_sin_pil)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __y, __z;
	__int32_t __n, __ix;
	__uint32_t __se, __i0, __i1;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__ix = __se & 0x7fff;
	__ix = (__ix << 16) | (__i0 >> 16);
	if (__ix < __INT32_C(0x3ffd8000)) /* 0.25 */
		return __ieee854_sinl(__LIBM_LOCAL_VALUE(lgamma_pil) * __x);
	__y = -__x; /* x is assume negative */
	/* argument reduction, make sure inexact flag not raised if input is an integer */
	__z = __ieee854_floorl(__y);
	if (__z != __y) { /* inexact anyway */
		__y *= __IEEE854_LONG_DOUBLE_C(0.5);
		__y = __IEEE854_LONG_DOUBLE_C(2.0) * (__y - __ieee854_floorl(__y)); /* y = |x| mod 2.0 */
		__n = (__int32_t)(__y * __IEEE854_LONG_DOUBLE_C(4.0));
	} else {
		if (__ix >= __INT32_C(0x403f8000)) { /* 2^64 */
			__y = __LIBM_LOCAL_VALUE(zerol);
			__n = 0; /* y must be even */
		} else {
			if (__ix < __INT32_C(0x403e8000))           /* 2^63 */
				__z = __y + __LIBM_LOCAL_VALUE(two63l); /* exact */
			__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __z);
			__n = __i1 & 1;
			__y = __n;
			__n <<= 2;
		}
	}
	switch ((int)__n) {
	case 0:
		__y = __ieee854_sinl(__LIBM_LOCAL_VALUE(lgamma_pil) * __y);
		break;
	case 1:
	case 2:
		__y = __ieee854_cosl(__LIBM_LOCAL_VALUE(lgamma_pil) * (__LIBM_LOCAL_VALUE(halfl) - __y));
		break;
	case 3:
	case 4:
		__y = __ieee854_sinl(__LIBM_LOCAL_VALUE(lgamma_pil) * (__LIBM_LOCAL_VALUE(onel) - __y));
		break;
	case 5:
	case 6:
		__y = -__ieee854_cosl(__LIBM_LOCAL_VALUE(lgamma_pil) * (__y - __IEEE854_LONG_DOUBLE_C(1.5)));
		break;
	default:
		__y = __ieee854_sinl(__LIBM_LOCAL_VALUE(lgamma_pil) * (__y - __IEEE854_LONG_DOUBLE_C(2.0)));
		break;
	}
	return -__y;
}

__LIBM_LOCAL_FUNC(lgammal) __ATTR_WUNUSED __ATTR_NONNULL((2)) __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_lgammal)(__IEEE854_LONG_DOUBLE_TYPE__ __x, int *__signgamp) {
	__IEEE854_LONG_DOUBLE_TYPE__ __t, __y, __z, __nadj = 0;
	__IEEE854_LONG_DOUBLE_TYPE__ __p, __p1, __p2, __q, __r, __w;
	__int32_t __i, __ix;
	__uint32_t se, i0, i1;
	*__signgamp = 1;
	__LIBM_GET_LDOUBLE_WORDS(se, i0, i1, __x);
	__ix = se & 0x7fff;
	if ((__ix | i0 | i1) == 0) {
		if (se & 0x8000)
			*__signgamp = -1;
		return __LIBM_LOCAL_VALUE(onel) / __ieee854_fabsl(__x);
	}
	__ix = (__ix << 16) | (i0 >> 16);
	/* purge off +-inf, NaN, +-0, and negative arguments */
	if (__ix >= __INT32_C(0x7fff0000))
		return __x * __x;
	if (__ix < __INT32_C(0x3fc08000)) { /* 2^-63 */
		/* |x|<2**-63, return -log(|x|) */
		if (se & 0x8000) {
			*__signgamp = -1;
			return -__ieee854_logl(-__x);
		} else {
			return -__ieee854_logl(__x);
		}
	}
	if (se & 0x8000) {
		__t = __ieee854_lgamma_sin_pil(__x);
		if (__t == __LIBM_LOCAL_VALUE(zerol))
			return __LIBM_LOCAL_VALUE(onel) / __ieee854_fabsl(__t); /* -integer */
		__nadj = __ieee854_logl(__LIBM_LOCAL_VALUE(lgamma_pil) / __ieee854_fabsl(__t * __x));
		if (__t < __LIBM_LOCAL_VALUE(zerol))
			*__signgamp = -1;
		__x = -__x;
	}

	/* purge off 1 and 2 */
	if ((((__ix - __INT32_C(0x3fff8000)) | i0 | i1) == 0) ||
	    (((__ix - __INT32_C(0x40008000)) | i0 | i1) == 0)) {
		__r = 0;
	} else if (__ix < __INT32_C(0x40008000)) { /* 2.0 */
		/* x < 2.0 */
		if (__ix <= __INT32_C(0x3ffee666)) { /* 8.99993896484375e-1 */
			/* lgamma(__x) = lgamma(__x+1) - log(__x) */
			__r = -__ieee854_logl(__x);
			if (__ix >= __INT32_C(0x3ffebb4a)) { /* 7.31597900390625e-1 */
				__y = __x - __LIBM_LOCAL_VALUE(onel);
				__i = 0;
			} else if (__ix >= __INT32_C(0x3ffced33)) { /* 2.31639862060546875e-1 */
				__y = __x - (__LIBM_LOCAL_VALUE(tcl) - __LIBM_LOCAL_VALUE(onel));
				__i = 1;
			} else {
				/* x < 0.23 */
				__y = __x;
				__i = 2;
			}
		} else {
			__r = __LIBM_LOCAL_VALUE(zerol);
			if (__ix >= __INT32_C(0x3fffdda6)) { /* 1.73162841796875 */
				/* [1.7316,2] */
				__y = __x - __IEEE854_LONG_DOUBLE_C(2.0);
				__i = 0;
			} else if (__ix >= __INT32_C(0x3fff9da6)) { /* 1.23162841796875 */
				/* [1.23,1.73] */
				__y = __x - __LIBM_LOCAL_VALUE(tcl);
				__i = 1;
			} else {
				/* [0.9, 1.23] */
				__y = __x - __LIBM_LOCAL_VALUE(onel);
				__i = 2;
			}
		}
		switch ((int)__i) {
		case 0:
			__p1 = __LIBM_LOCAL_VALUE(a0l) +
			       __y * (__LIBM_LOCAL_VALUE(a1l) +
			              __y * (__LIBM_LOCAL_VALUE(a2l) +
			                     __y * (__LIBM_LOCAL_VALUE(a3l) +
			                            __y * (__LIBM_LOCAL_VALUE(a4l) +
			                                   __y * __LIBM_LOCAL_VALUE(a5l)))));
			__p2 = __LIBM_LOCAL_VALUE(b0l) +
			       __y * (__LIBM_LOCAL_VALUE(b1l) +
			              __y * (__LIBM_LOCAL_VALUE(b2l) +
			                     __y * (__LIBM_LOCAL_VALUE(b3l) +
			                            __y * (__LIBM_LOCAL_VALUE(b4l) +
			                                   __y))));
			__r += __LIBM_LOCAL_VALUE(halfl) * __y + __y * __p1 / __p2;
			break;
		case 1:
			__p1 = __LIBM_LOCAL_VALUE(g0l) +
			       __y * (__LIBM_LOCAL_VALUE(g1l) +
			              __y * (__LIBM_LOCAL_VALUE(g2l) +
			                     __y * (__LIBM_LOCAL_VALUE(g3l) +
			                            __y * (__LIBM_LOCAL_VALUE(g4l) +
			                                   __y * (__LIBM_LOCAL_VALUE(g5l) +
			                                          __y * __LIBM_LOCAL_VALUE(g6l))))));
			__p2 = __LIBM_LOCAL_VALUE(h0l) +
			       __y * (__LIBM_LOCAL_VALUE(h1l) +
			              __y * (__LIBM_LOCAL_VALUE(h2l) +
			                     __y * (__LIBM_LOCAL_VALUE(h3l) +
			                            __y * (__LIBM_LOCAL_VALUE(h4l) +
			                                   __y * (__LIBM_LOCAL_VALUE(h5l) +
			                                          __y)))));
			__p = __LIBM_LOCAL_VALUE(ttl) + __y * __p1 / __p2;
			__r += (__LIBM_LOCAL_VALUE(tfl) + __p);
			break;
		case 2:
			__p1 = __y * (__LIBM_LOCAL_VALUE(u0l) +
			              __y * (__LIBM_LOCAL_VALUE(u1l) +
			                     __y * (__LIBM_LOCAL_VALUE(u2l) +
			                            __y * (__LIBM_LOCAL_VALUE(u3l) +
			                                   __y * (__LIBM_LOCAL_VALUE(u4l) +
			                                          __y * (__LIBM_LOCAL_VALUE(u5l) +
			                                                 __y * __LIBM_LOCAL_VALUE(u6l)))))));
			__p2 = __LIBM_LOCAL_VALUE(v0l) +
			       __y * (__LIBM_LOCAL_VALUE(v1l) +
			              __y * (__LIBM_LOCAL_VALUE(v2l) +
			                     __y * (__LIBM_LOCAL_VALUE(v3l) +
			                            __y * (__LIBM_LOCAL_VALUE(v4l) +
			                                   __y * (__LIBM_LOCAL_VALUE(v5l) +
			                                          __y)))));
			__r += (-__LIBM_LOCAL_VALUE(halfl) * __y + __p1 / __p2);
			break;
		}
	} else if (__ix < __INT32_C(0x40028000)) { /* 8.0 */
		/* x < 8.0 */
		__i = (__int32_t)__x;
		__t = __LIBM_LOCAL_VALUE(zerol);
		__y = __x - (__IEEE854_LONG_DOUBLE_TYPE__)__i;
		__p = __y * (__LIBM_LOCAL_VALUE(s0l) +
		             __y * (__LIBM_LOCAL_VALUE(s1l) +
		                    __y * (__LIBM_LOCAL_VALUE(s2l) +
		                           __y * (__LIBM_LOCAL_VALUE(s3l) +
		                                  __y * (__LIBM_LOCAL_VALUE(s4l) +
		                                         __y * (__LIBM_LOCAL_VALUE(s5l) +
		                                                __y * __LIBM_LOCAL_VALUE(s6l)))))));
		__q = __LIBM_LOCAL_VALUE(r0l) +
		      __y * (__LIBM_LOCAL_VALUE(r1l) +
		             __y * (__LIBM_LOCAL_VALUE(r2l) +
		                    __y * (__LIBM_LOCAL_VALUE(r3l) +
		                           __y * (__LIBM_LOCAL_VALUE(r4l) +
		                                  __y * (__LIBM_LOCAL_VALUE(r5l) +
		                                         __y * (__LIBM_LOCAL_VALUE(r6l) +
		                                                __y))))));
		__r = __LIBM_LOCAL_VALUE(halfl) * __y + __p / __q;
		__z = __LIBM_LOCAL_VALUE(onel); /* lgamma(1+s) = log(s) + lgamma(s) */
		switch ((int)__i) {
		case 7:
			__z *= (__y + __IEEE854_LONG_DOUBLE_C(6.0));
			__ATTR_FALLTHROUGH
		case 6:
			__z *= (__y + __IEEE854_LONG_DOUBLE_C(5.0));
			__ATTR_FALLTHROUGH
		case 5:
			__z *= (__y + __IEEE854_LONG_DOUBLE_C(4.0));
			__ATTR_FALLTHROUGH
		case 4:
			__z *= (__y + __IEEE854_LONG_DOUBLE_C(3.0));
			__ATTR_FALLTHROUGH
		case 3:
			__z *= (__y + __IEEE854_LONG_DOUBLE_C(2.0));
			__r += __ieee854_logl(__z);
			break;
		}
	} else if (__ix < __INT32_C(0x40418000)) { /* 2^66 */
		/* 8.0 <= __x < 2**66 */
		__t = __ieee854_logl(__x);
		__z = __LIBM_LOCAL_VALUE(onel) / __x;
		__y = __z * __z;
		__w = __LIBM_LOCAL_VALUE(w0l) +
		      __z * (__LIBM_LOCAL_VALUE(w1l) +
		             __y * (__LIBM_LOCAL_VALUE(w2l) +
		                    __y * (__LIBM_LOCAL_VALUE(w3l) +
		                           __y * (__LIBM_LOCAL_VALUE(w4l) +
		                                  __y * (__LIBM_LOCAL_VALUE(w5l) +
		                                         __y * (__LIBM_LOCAL_VALUE(w6l) +
		                                                __y * __LIBM_LOCAL_VALUE(w7l)))))));
		__r = (__x - __LIBM_LOCAL_VALUE(halfl)) *
		      (__t - __LIBM_LOCAL_VALUE(onel)) +
		      __w;
	} else {
		/* 2**66 <= __x <= inf */
		__r = __x * (__ieee854_logl(__x) - __LIBM_LOCAL_VALUE(onel));
	}
	if (se & 0x8000)
		__r = __nadj - __r;
	return __r;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_LGAMMA_H */
