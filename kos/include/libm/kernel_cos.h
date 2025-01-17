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
#ifndef _LIBM_KERNEL_COS_H
#define _LIBM_KERNEL_COS_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fabs.h>
#include <libm/fdlibm.h>
#include <libm/signbit.h>
#include <libm/sincos_table.h>

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
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, C1f, __IEEE754_FLOAT_C(4.1666667908e-02))  /* 0x3d2aaaab */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, C2f, __IEEE754_FLOAT_C(-1.3888889225e-03)) /* 0xbab60b61 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, C3f, __IEEE754_FLOAT_C(2.4801587642e-05))  /* 0x37d00d01 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, C4f, __IEEE754_FLOAT_C(-2.7557314297e-07)) /* 0xb493f27c */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, C5f, __IEEE754_FLOAT_C(2.0875723372e-09))  /* 0x310f74f6 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, C6f, __IEEE754_FLOAT_C(-1.1359647598e-11)) /* 0xad47d74e */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(cosf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_kernel_cosf)(__IEEE754_FLOAT_TYPE__ __x,
                                   __IEEE754_FLOAT_TYPE__ __y) {
	__IEEE754_FLOAT_TYPE__ __a, __hz, __z, __r, __qx;
	__int32_t __ix;
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	__ix &= __INT32_C(0x7fffffff);      /* ix = |x|'s high word */
	if (__ix < __INT32_C(0x32000000)) { /* if x < 2**27 */
		if (((__int32_t)__x) == 0)
			return __LIBM_LOCAL_VALUE(onef); /* generate inexact */
	}
	__z = __x * __x;
	__r = __z * (__LIBM_LOCAL_VALUE(C1f) +
	             __z * (__LIBM_LOCAL_VALUE(C2f) +
	                    __z * (__LIBM_LOCAL_VALUE(C3f) +
	                           __z * (__LIBM_LOCAL_VALUE(C4f) +
	                                  __z * (__LIBM_LOCAL_VALUE(C5f) +
	                                         __z * __LIBM_LOCAL_VALUE(C6f))))));
	if (__ix < __INT32_C(0x3e99999a)) { /* if |x| < 0.3 */
		return __LIBM_LOCAL_VALUE(onef) - (__IEEE754_FLOAT_C(0.5) * __z - (__z * __r - __x * __y));
	} else {
		if (__ix > __INT32_C(0x3f480000)) { /* x > 0.78125 */
			__qx = __IEEE754_FLOAT_C(0.28125);
		} else {
			__LIBM_SET_FLOAT_WORD(__qx, __ix - __INT32_C(0x01000000)); /* x/4 */
		}
		__hz = __IEEE754_FLOAT_C(0.5) * __z - __qx;
		__a  = __LIBM_LOCAL_VALUE(onef) - __qx;
		return __a - (__hz - (__z * __r - __x * __y));
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
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, C1, __IEEE754_DOUBLE_C(4.16666666666666019037e-02))  /* 0x3FA55555, 0x5555554C */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, C2, __IEEE754_DOUBLE_C(-1.38888888888741095749e-03)) /* 0xBF56C16C, 0x16C15177 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, C3, __IEEE754_DOUBLE_C(2.48015872894767294178e-05))  /* 0x3EFA01A0, 0x19CB1590 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, C4, __IEEE754_DOUBLE_C(-2.75573143513906633035e-07)) /* 0xBE927E4F, 0x809C52AD */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, C5, __IEEE754_DOUBLE_C(2.08757232129817482790e-09))  /* 0x3E21EE9E, 0xBDB4B1C4 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, C6, __IEEE754_DOUBLE_C(-1.13596475577881948265e-11)) /* 0xBDA8FAE9, 0xBE8838D4 */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(cos) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_kernel_cos)(__IEEE754_DOUBLE_TYPE__ __x,
                                  __IEEE754_DOUBLE_TYPE__ __y) {
	__IEEE754_DOUBLE_TYPE__ __a, __hz, __z, __r, __qx;
	__int32_t __ix;
	__LIBM_GET_HIGH_WORD(__ix, __x);
	__ix &= __INT32_C(0x7fffffff);      /* ix = |x|'s high word */
	if (__ix < __INT32_C(0x3e400000)) { /* if x < 2**27 */
		if (((int)__x) == 0)
			return __LIBM_LOCAL_VALUE(one); /* generate inexact */
	}
	__z = __x * __x;
	__r = __z * (__LIBM_LOCAL_VALUE(C1) +
	             __z * (__LIBM_LOCAL_VALUE(C2) +
	                    __z * (__LIBM_LOCAL_VALUE(C3) +
	                           __z * (__LIBM_LOCAL_VALUE(C4) +
	                                  __z * (__LIBM_LOCAL_VALUE(C5) +
	                                         __z * __LIBM_LOCAL_VALUE(C6))))));
	if (__ix < __INT32_C(0x3FD33333)) { /* if |x| < 0.3 */
		return __LIBM_LOCAL_VALUE(one) - (__IEEE754_DOUBLE_C(0.5) * __z - (__z * __r - __x * __y));
	} else {
		if (__ix > __INT32_C(0x3fe90000)) { /* x > 0.78125 */
			__qx = 0.28125;
		} else {
			__LIBM_INSERT_WORDS(__qx, __ix - __INT32_C(0x00200000), 0); /* x/4 */
		}
		__hz = __IEEE754_DOUBLE_C(0.5) * __z - __qx;
		__a  = __LIBM_LOCAL_VALUE(one) - __qx;
		return __a - (__hz - (__z * __r - __x * __y));
	}
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* Quad-precision floating point sine on <-pi/4,pi/4>.
   Copyright (C) 1999-2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Based on quad-precision sine by Jakub Jelinek <jj@ultra.linux.cz>

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_ONEl_defined
#define __libm_ONEl_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, ONEl, __IEEE854_LONG_DOUBLE_C(1.00000000000000000000000000000000000E+00))
#endif /* !__libm_ONEl_defined */
/* cos x ~ ONE + x^2 ( SCOS1 + SCOS2 * x^2 + ... + SCOS4 * x^6 + SCOS5 * x^8 ) x in <0,1/256>  */
#ifndef __libm_SCOS1l_defined
#define __libm_SCOS1l_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SCOS1l, __IEEE854_LONG_DOUBLE_C(-5.00000000000000000000000000000000000E-01))
#endif /* !__libm_SCOS1l_defined */
#ifndef __libm_SCOS2l_defined
#define __libm_SCOS2l_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SCOS2l, __IEEE854_LONG_DOUBLE_C(4.16666666666666666666666666556146073E-02))
#endif /* !__libm_SCOS2l_defined */
#ifndef __libm_SCOS3l_defined
#define __libm_SCOS3l_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SCOS3l, __IEEE854_LONG_DOUBLE_C(-1.38888888888888888888309442601939728E-03))
#endif /* !__libm_SCOS3l_defined */
#ifndef __libm_SCOS4l_defined
#define __libm_SCOS4l_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SCOS4l, __IEEE854_LONG_DOUBLE_C(2.48015873015862382987049502531095061E-05))
#endif /* !__libm_SCOS4l_defined */
#ifndef __libm_SCOS5l_defined
#define __libm_SCOS5l_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SCOS5l, __IEEE854_LONG_DOUBLE_C(-2.75573112601362126593516899592158083E-07))
#endif /* !__libm_SCOS5l_defined */
/* sin x ~ ONE * x + x^3 ( SSIN1 + SSIN2 * x^2 + ... + SSIN4 * x^6 + SSIN5 * x^8 ) x in <0,1/256>  */
#ifndef __libm_SSIN1l_defined
#define __libm_SSIN1l_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SSIN1l, __IEEE854_LONG_DOUBLE_C(-1.66666666666666666666666666666666659E-01))
#endif /* !__libm_SSIN1l_defined */
#ifndef __libm_SSIN2l_defined
#define __libm_SSIN2l_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SSIN2l, __IEEE854_LONG_DOUBLE_C(8.33333333333333333333333333146298442E-03))
#endif /* !__libm_SSIN2l_defined */
#ifndef __libm_SSIN3l_defined
#define __libm_SSIN3l_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SSIN3l, __IEEE854_LONG_DOUBLE_C(-1.98412698412698412697726277416810661E-04))
#endif /* !__libm_SSIN3l_defined */
#ifndef __libm_SSIN4l_defined
#define __libm_SSIN4l_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SSIN4l, __IEEE854_LONG_DOUBLE_C(2.75573192239848624174178393552189149E-06))
#endif /* !__libm_SSIN4l_defined */
#ifndef __libm_SSIN5l_defined
#define __libm_SSIN5l_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SSIN5l, __IEEE854_LONG_DOUBLE_C(-2.50521016467996193495359189395805639E-08))
#endif /* !__libm_SSIN5l_defined */
/* cos x ~ ONE + x^2 ( COS1 + COS2 * x^2 + ... + COS7 * x^12 + COS8 * x^14 ) x in <0,0.1484375>  */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, COS1l, __IEEE854_LONG_DOUBLE_C(-4.99999999999999999999999999999999759E-01))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, COS2l, __IEEE854_LONG_DOUBLE_C(4.16666666666666666666666666651287795E-02))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, COS3l, __IEEE854_LONG_DOUBLE_C(-1.38888888888888888888888742314300284E-03))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, COS4l, __IEEE854_LONG_DOUBLE_C(2.48015873015873015867694002851118210E-05))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, COS5l, __IEEE854_LONG_DOUBLE_C(-2.75573192239858811636614709689300351E-07))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, COS6l, __IEEE854_LONG_DOUBLE_C(2.08767569877762248667431926878073669E-09))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, COS7l, __IEEE854_LONG_DOUBLE_C(-1.14707451049343817400420280514614892E-11))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, COS8l, __IEEE854_LONG_DOUBLE_C(4.77810092804389587579843296923533297E-14))
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(cosl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_kernel_cosl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                   __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	__IEEE854_LONG_DOUBLE_TYPE__ __h, __l, __z;
	__IEEE854_LONG_DOUBLE_TYPE__ __sin_l, __cos_l_m1;
	int __index;
#define __LIBM_SINCOSL_COS_HI 0
#define __LIBM_SINCOSL_COS_LO 1
#define __LIBM_SINCOSL_SIN_HI 2
#define __LIBM_SINCOSL_SIN_LO 3
	if (__ieee854_signbitl(__x)) {
		__x = -__x;
		__y = -__y;
	}
	if (__x < __IEEE754_DOUBLE_C(0.1484375)) {
		/* Argument is small enough to approximate it by a Chebyshev
		 * polynomial of degree 16. */
		if (__x < __IEEE754_DOUBLE_C(0x1p-33)) {
			if (!((__int32_t)__x))
				return __LIBM_LOCAL_VALUE(ONEl); /* generate inexact */
		}
		__z = __x * __x;
		return __LIBM_LOCAL_VALUE(ONEl) +
		       (__z * (__LIBM_LOCAL_VALUE(COS1l) +
		               __z * (__LIBM_LOCAL_VALUE(COS2l) +
		                      __z * (__LIBM_LOCAL_VALUE(COS3l) +
		                             __z * (__LIBM_LOCAL_VALUE(COS4l) +
		                                    __z * (__LIBM_LOCAL_VALUE(COS5l) +
		                                           __z * (__LIBM_LOCAL_VALUE(COS6l) +
		                                                  __z * (__LIBM_LOCAL_VALUE(COS7l) +
		                                                         __z * __LIBM_LOCAL_VALUE(COS8l)))))))));
	} else {
		/* So  that we  don't have to  use too large  polynomial, we find
		 * l and h such that x = l + h, where fabsl(l) <= 1.0/256 with 83
		 * possible  values  for h.  We look  up  cosl(h) and  sinl(h) in
		 * pre-computed  tables,  compute  cosl(l)  and  sinl(l)  using a
		 * Chebyshev    polynomial   of   degree   10(11)   and   compute
		 * cosl(h+l) = cosl(h)cosl(l) - sinl(h)sinl(l). */
		__index = (int)(128 * (__x - (__IEEE854_LONG_DOUBLE_C(0.1484375) -
		                              __IEEE854_LONG_DOUBLE_C(1.0) / __IEEE854_LONG_DOUBLE_C(256.0))));
		__h     = __IEEE854_LONG_DOUBLE_C(0.1484375) + __index / __IEEE854_LONG_DOUBLE_C(128.0);
		__index *= 4;
		__l        = __y - (__h - __x);
		__z        = __l * __l;
		__sin_l    = __l * (__LIBM_LOCAL_VALUE(ONEl) +
                         __z * (__LIBM_LOCAL_VALUE(SSIN1l) +
                                __z * (__LIBM_LOCAL_VALUE(SSIN2l) +
                                       __z * (__LIBM_LOCAL_VALUE(SSIN3l) +
                                              __z * (__LIBM_LOCAL_VALUE(SSIN4l) +
                                                     __z * __LIBM_LOCAL_VALUE(SSIN5l))))));
		__cos_l_m1 = __z * (__LIBM_LOCAL_VALUE(SCOS1l) +
		                    __z * (__LIBM_LOCAL_VALUE(SCOS2l) +
		                           __z * (__LIBM_LOCAL_VALUE(SCOS3l) +
		                                  __z * (__LIBM_LOCAL_VALUE(SCOS4l) +
		                                         __z * __LIBM_LOCAL_VALUE(SCOS5l)))));
		return __sincosl_table[__index + __LIBM_SINCOSL_COS_HI] +
		       (__sincosl_table[__index + __LIBM_SINCOSL_COS_LO] -
		        (__sincosl_table[__index + __LIBM_SINCOSL_SIN_HI] * __sin_l -
		         __sincosl_table[__index + __LIBM_SINCOSL_COS_HI] * __cos_l_m1));
	}
#undef __LIBM_SINCOSL_COS_HI
#undef __LIBM_SINCOSL_COS_LO
#undef __LIBM_SINCOSL_SIN_HI
#undef __LIBM_SINCOSL_SIN_LO
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_KERNEL_COS_H */
