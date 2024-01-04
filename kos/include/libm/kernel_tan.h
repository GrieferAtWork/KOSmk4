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
#ifndef _LIBM_KERNEL_TAN_H
#define _LIBM_KERNEL_TAN_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fabs.h>
#include <libm/fdlibm.h>
#include <libm/signbit.h>

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
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pio4f, __IEEE754_FLOAT_C(7.8539812565e-01))   /* 0x3f490fda */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pio4lof, __IEEE754_FLOAT_C(3.7748947079e-08)) /* 0x33222168 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, T0f, __IEEE754_FLOAT_C(3.3333334327e-01))     /* 0x3eaaaaab */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, T1f, __IEEE754_FLOAT_C(1.3333334029e-01))     /* 0x3e088889 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, T2f, __IEEE754_FLOAT_C(5.3968254477e-02))     /* 0x3d5d0dd1 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, T3f, __IEEE754_FLOAT_C(2.1869488060e-02))     /* 0x3cb327a4 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, T4f, __IEEE754_FLOAT_C(8.8632395491e-03))     /* 0x3c11371f */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, T5f, __IEEE754_FLOAT_C(3.5920790397e-03))     /* 0x3b6b6916 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, T6f, __IEEE754_FLOAT_C(1.4562094584e-03))     /* 0x3abede48 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, T7f, __IEEE754_FLOAT_C(5.8804126456e-04))     /* 0x3a1a26c8 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, T8f, __IEEE754_FLOAT_C(2.4646313977e-04))     /* 0x398137b9 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, T9f, __IEEE754_FLOAT_C(7.8179444245e-05))     /* 0x38a3f445 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, T10f, __IEEE754_FLOAT_C(7.1407252108e-05))    /* 0x3895c07a */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, T11f, __IEEE754_FLOAT_C(-1.8558637748e-05))   /* 0xb79bae5f */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, T12f, __IEEE754_FLOAT_C(2.5907305826e-05))    /* 0x37d95384 */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(kernel_tanf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_kernel_tanf)(__IEEE754_FLOAT_TYPE__ __x,
                                   __IEEE754_FLOAT_TYPE__ __y, int __iy) {
	__IEEE754_FLOAT_TYPE__ __z, __r, __v, __w, __s;
	__int32_t __ix, __hx;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff); /* high word of |x| */
	if (__ix < __INT32_C(0x31800000)) {  /* x < 2**-28 */
		if ((__int32_t)__x == 0) { /* generate inexact */
			if ((__ix | (__iy + 1)) == 0) {
				return __LIBM_LOCAL_VALUE(onef) / __ieee754_fabsf(__x);
			} else {
				return (__iy == 1) ? __x : -__LIBM_LOCAL_VALUE(onef) / __x;
			}
		}
	}
	if (__ix >= __INT32_C(0x3f2ca140)) { /* |x|>=0.6744 */
		if (__hx < 0) {
			__x = -__x;
			__y = -__y;
		}
		__z = __LIBM_LOCAL_VALUE(pio4f) - __x;
		__w = __LIBM_LOCAL_VALUE(pio4lof) - __y;
		__x = __z + __w;
		__y = __IEEE754_FLOAT_C(0.0);
		if (__ieee754_fabsf(__x) < 0x1p-13f)
			return (1 - ((__hx >> 30) & 2)) * __iy * (__IEEE754_FLOAT_C(1.0) - 2 * __iy * __x);
	}
	__z = __x * __x;
	__w = __z * __z;
	/* Break x^5*(T[1]+x^2*T[2]+...) into
	 *    x^5(T[1]+x^4*T[3]+...+x^20*T[11])     +
	 *    x^5(x^2*(T[2]+x^4*T[4]+...+x^22*[T12]))
	 */
	__r = __LIBM_LOCAL_VALUE(T1f) +
	      __w * (__LIBM_LOCAL_VALUE(T3f) +
	             __w * (__LIBM_LOCAL_VALUE(T5f) +
	                    __w * (__LIBM_LOCAL_VALUE(T7f) +
	                           __w * (__LIBM_LOCAL_VALUE(T9f) +
	                                  __w * __LIBM_LOCAL_VALUE(T11f)))));
	__v = __z * (__LIBM_LOCAL_VALUE(T2f) +
	             __w * (__LIBM_LOCAL_VALUE(T4f) +
	                    __w * (__LIBM_LOCAL_VALUE(T6f) +
	                           __w * (__LIBM_LOCAL_VALUE(T8f) +
	                                  __w * (__LIBM_LOCAL_VALUE(T10f) +
	                                         __w * __LIBM_LOCAL_VALUE(T12f))))));
	__s = __z * __x;
	__r = __y + __z * (__s * (__r + __v) + __y);
	__r += __LIBM_LOCAL_VALUE(T0f) * __s;
	__w = __x + __r;
	if (__ix >= __INT32_C(0x3f2ca140)) {
		__v = (__IEEE754_FLOAT_TYPE__)__iy;
		return (__IEEE754_FLOAT_TYPE__)(1 - ((__hx >> 30) & 2)) *
		       (__v - __IEEE754_FLOAT_C(2.0) * (__x - (__w * __w / (__w + __v) - __r)));
	}
	if (__iy == 1) {
		return __w;
	} else { /* if allow error up to 2 ulp, simply return -1.0/(x+r) here */
		/* compute -1.0/(x+r) accurately */
		__IEEE754_FLOAT_TYPE__ __a, __t;
		__int32_t __i;
		__z = __w;
		__LIBM_GET_FLOAT_WORD(__i, __z);
		__LIBM_SET_FLOAT_WORD(__z, __i & __UINT32_C(0xfffff000));
		__v = __r - (__z - __x); /* z+v = r+x */
		__t = __a = __IEEE754_FLOAT_C(-1.0) / __w; /* a = -1.0/w */
		__LIBM_GET_FLOAT_WORD(__i, __t);
		__LIBM_SET_FLOAT_WORD(__t, __i & __UINT32_C(0xfffff000));
		__s = __IEEE754_FLOAT_C(1.0) + __t * __z;
		return __t + __a * (__s + __t * __v);
	}
}
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
/*
 * ====================================================
 * Copyright 2004 Sun Microsystems, Inc. All Rights Reserved.
 *
 * Permission  to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.00000000000000000000e+00)) /* 0x3FF00000, 0x00000000 */
#endif /* !__libm_one_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pio4, __IEEE754_DOUBLE_C(7.85398163397448278999e-01))   /* 0x3FE921FB, 0x54442D18 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pio4lo, __IEEE754_DOUBLE_C(3.06161699786838301793e-17)) /* 0x3C81A626, 0x33145C07 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, T0, __IEEE754_DOUBLE_C(3.33333333333334091986e-01))     /* 0x3FD55555, 0x55555563 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, T1, __IEEE754_DOUBLE_C(1.33333333333201242699e-01))     /* 0x3FC11111, 0x1110FE7A */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, T2, __IEEE754_DOUBLE_C(5.39682539762260521377e-02))     /* 0x3FABA1BA, 0x1BB341FE */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, T3, __IEEE754_DOUBLE_C(2.18694882948595424599e-02))     /* 0x3F9664F4, 0x8406D637 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, T4, __IEEE754_DOUBLE_C(8.86323982359930005737e-03))     /* 0x3F8226E3, 0xE96E8493 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, T5, __IEEE754_DOUBLE_C(3.59207910759131235356e-03))     /* 0x3F6D6D22, 0xC9560328 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, T6, __IEEE754_DOUBLE_C(1.45620945432529025516e-03))     /* 0x3F57DBC8, 0xFEE08315 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, T7, __IEEE754_DOUBLE_C(5.88041240820264096874e-04))     /* 0x3F4344D8, 0xF2F26501 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, T8, __IEEE754_DOUBLE_C(2.46463134818469906812e-04))     /* 0x3F3026F7, 0x1A8D1068 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, T9, __IEEE754_DOUBLE_C(7.81794442939557092300e-05))     /* 0x3F147E88, 0xA03792A6 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, T10, __IEEE754_DOUBLE_C(7.14072491382608190305e-05))    /* 0x3F12B80F, 0x32F0A7E9 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, T11, __IEEE754_DOUBLE_C(-1.85586374855275456654e-05))   /* 0xBEF375CB, 0xDB605373 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, T12, __IEEE754_DOUBLE_C(2.59073051863633712884e-05))    /* 0x3EFB2A70, 0x74BF7AD4 */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(kernel_tan) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_kernel_tan)(__IEEE754_DOUBLE_TYPE__ __x,
                                  __IEEE754_DOUBLE_TYPE__ __y, int __iy) {
	__IEEE754_DOUBLE_TYPE__ __z, __r, __v, __w, __s;
	__int32_t __ix, __hx;
	__LIBM_GET_HIGH_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff); /* high word of |x| */
	if (__ix < __INT32_C(0x3e300000)) {  /* x < 2**-28 */
		if ((__int32_t)__x == 0) { /* generate inexact */
			__uint32_t __low;
			__LIBM_GET_LOW_WORD(__low, __x);
			if (((__ix | __low) | (__iy + 1)) == 0) {
				return __LIBM_LOCAL_VALUE(one) / __ieee754_fabs(__x);
			} else {
				return (__iy == 1) ? __x : -__LIBM_LOCAL_VALUE(one) / __x;
			}
		}
	}
	if (__ix >= __INT32_C(0x3FE59428)) { /* |x| >= 0.6744 */
		if (__hx < 0) {
			__x = -__x;
			__y = -__y;
		}
		__z = __LIBM_LOCAL_VALUE(pio4) - __x;
		__w = __LIBM_LOCAL_VALUE(pio4lo) - __y;
		__x = __z + __w;
		__y = __IEEE754_DOUBLE_C(0.0);
	}
	__z = __x * __x;
	__w = __z * __z;
	/*
	 * Break   x^5*(T[1]+x^2*T[2]+...)    into
	 * x^5(T[1]+x^4*T[3]+...+x^20*T[11])     +
	 * x^5(x^2*(T[2]+x^4*T[4]+...+x^22*[T12]))
	 */
	__r = __LIBM_LOCAL_VALUE(T1) +
	      __w * (__LIBM_LOCAL_VALUE(T3) +
	             __w * (__LIBM_LOCAL_VALUE(T5) +
	                    __w * (__LIBM_LOCAL_VALUE(T7) +
	                           __w * (__LIBM_LOCAL_VALUE(T9) +
	                                  __w * __LIBM_LOCAL_VALUE(T11)))));
	__v = __z * (__LIBM_LOCAL_VALUE(T2) +
	             __w * (__LIBM_LOCAL_VALUE(T4) +
	                    __w * (__LIBM_LOCAL_VALUE(T6) +
	                           __w * (__LIBM_LOCAL_VALUE(T8) +
	                                  __w * (__LIBM_LOCAL_VALUE(T10) +
	                                         __w * __LIBM_LOCAL_VALUE(T12))))));
	__s = __z * __x;
	__r = __y + __z * (__s * (__r + __v) + __y);
	__r += __LIBM_LOCAL_VALUE(T0) * __s;
	__w = __x + __r;
	if (__ix >= __INT32_C(0x3FE59428)) {
		__v = (__IEEE754_DOUBLE_TYPE__)__iy;
		return (__IEEE754_DOUBLE_TYPE__)(1 - ((__hx >> 30) & 2)) *
		       (__v - __IEEE754_DOUBLE_C(2.0) * (__x - (__w * __w / (__w + __v) - __r)));
	}
	if (__iy == 1) {
		return __w;
	} else {
		/* if allow error up to 2 ulp, simply return -1.0 / (x+r) here */
		/* compute -1.0 / (x+r) accurately */
		__IEEE754_DOUBLE_TYPE__ __a, __t;
		__z = __w;
		__LIBM_SET_LOW_WORD(__z, 0);
		__v = __r - (__z - __x);                    /* z+v = r+x */
		__t = __a = __IEEE754_DOUBLE_C(-1.0) / __w; /* a = -1.0/w */
		__LIBM_SET_LOW_WORD(__t, 0);
		__s = __IEEE754_DOUBLE_C(1.0) + __t * __z;
		return __t + __a * (__s + __t * __v);
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
#ifndef __libm_onel_defined
#define __libm_onel_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, onel, __IEEE854_LONG_DOUBLE_C(1.0))
#endif /* !__libm_onel_defined */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pio4hil, __IEEE854_LONG_DOUBLE_C(0xc.90fdaa22168c235p-4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pio4lol, __IEEE854_LONG_DOUBLE_C(-0x3.b399d747f23e32ecp-68))
/* tan x = x + x^3 / 3 + x^5 T(x^2)/U(x^2)  0 <= x <= 0.6743316650390625  Peak relative error 8.0e-36  */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, THl, __IEEE854_LONG_DOUBLE_C(3.333333333333333333333333333333333333333E-1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, T0l, __IEEE854_LONG_DOUBLE_C(-1.813014711743583437742363284336855889393E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, T1l, __IEEE854_LONG_DOUBLE_C(1.320767960008972224312740075083259247618E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, T2l, __IEEE854_LONG_DOUBLE_C(-2.626775478255838182468651821863299023956E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, T3l, __IEEE854_LONG_DOUBLE_C(1.764573356488504935415411383687150199315E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, T4l, __IEEE854_LONG_DOUBLE_C(-3.333267763822178690794678978979803526092E-1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, U0l, __IEEE854_LONG_DOUBLE_C(-1.359761033807687578306772463253710042010E8))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, U1l, __IEEE854_LONG_DOUBLE_C(6.494370630656893175666729313065113194784E7))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, U2l, __IEEE854_LONG_DOUBLE_C(-4.180787672237927475505536849168729386782E6))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, U3l, __IEEE854_LONG_DOUBLE_C(8.031643765106170040139966622980914621521E4))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, U4l, __IEEE854_LONG_DOUBLE_C(-5.323131271912475695157127875560667378597E2))
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(kernel_tanl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_kernel_tanl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                   __IEEE854_LONG_DOUBLE_TYPE__ __y, int __iy) {
	__IEEE854_LONG_DOUBLE_TYPE__ __z, __r, __v, __w, __s;
	__IEEE854_LONG_DOUBLE_TYPE__ __absx;
	int __sign;
	__absx = __ieee854_fabsl(__x);
	__sign = 0;
	if (__absx < __IEEE854_LONG_DOUBLE_C(0x1p-33)) {
		if ((__int32_t)__x == 0) { /* generate inexact */
			if (__x == 0 && __iy == -1) {
				return __LIBM_LOCAL_VALUE(one) / __ieee854_fabsl(__x);
			} else {
				return (__iy == 1) ? __x : -__LIBM_LOCAL_VALUE(one) / __x;
			}
		}
	}
	if (__absx >= 0.6743316650390625L) {
		if (__ieee854_signbitl(__x)) {
			__x    = -__x;
			__y    = -__y;
			__sign = -1;
		} else {
			__sign = 1;
		}
		__z = __LIBM_LOCAL_VALUE(pio4hil) - __x;
		__w = __LIBM_LOCAL_VALUE(pio4lol) - __y;
		__x = __z + __w;
		__y = __IEEE854_LONG_DOUBLE_C(0.0);
	}
	__z = __x * __x;
	__r = __LIBM_LOCAL_VALUE(T0l) +
	      __z * (__LIBM_LOCAL_VALUE(T1l) +
	             __z * (__LIBM_LOCAL_VALUE(T2l) +
	                    __z * (__LIBM_LOCAL_VALUE(T3l) +
	                           __z * __LIBM_LOCAL_VALUE(T4l))));
	__v = __LIBM_LOCAL_VALUE(U0l) +
	      __z * (__LIBM_LOCAL_VALUE(U1l) +
	             __z * (__LIBM_LOCAL_VALUE(U2l) +
	                    __z * (__LIBM_LOCAL_VALUE(U3l) +
	                           __z * (__LIBM_LOCAL_VALUE(U4l) +
	                                  __z))));
	__r = __r / __v;
	__s = __z * __x;
	__r = __y + __z * (__s * __r + __y);
	__r += __LIBM_LOCAL_VALUE(THl) * __s;
	__w = __x + __r;
	if (__sign != 0) {
		__v = (__IEEE854_LONG_DOUBLE_TYPE__)__iy;
		__w = (__v - __IEEE854_LONG_DOUBLE_C(2.0) * (__x - (__w * __w / (__w + __v) - __r)));
		if (__sign < 0)
			__w = -__w;
		return __w;
	}
	if (__iy == 1) {
		return __w;
	} else {
		return __IEEE854_LONG_DOUBLE_C(-1.0) / (__x + __r);
	}
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_KERNEL_TAN_H */
