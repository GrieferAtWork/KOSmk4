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
#ifndef _LIBM_KERNEL_SIN_H
#define _LIBM_KERNEL_SIN_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fabs.h>
#include <libm/fdlibm.h>
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
#ifndef __libm_halff_defined
#define __libm_halff_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, halff, __IEEE754_FLOAT_C(5.0000000000e-01)) /* 0x3f000000 */
#endif /* !__libm_halff_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, S1f, __IEEE754_FLOAT_C(-1.6666667163e-01))  /* 0xbe2aaaab */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, S2f, __IEEE754_FLOAT_C(8.3333337680e-03))   /* 0x3c088889 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, S3f, __IEEE754_FLOAT_C(-1.9841270114e-04))  /* 0xb9500d01 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, S4f, __IEEE754_FLOAT_C(2.7557314297e-06))   /* 0x3638ef1b */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, S5f, __IEEE754_FLOAT_C(-2.5050759689e-08))  /* 0xb2d72f34 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, S6f, __IEEE754_FLOAT_C(1.5896910177e-10))   /* 0x2f2ec9d3 */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(kernel_sinf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_kernel_sinf)(__IEEE754_FLOAT_TYPE__ __x, __IEEE754_FLOAT_TYPE__ __y, int __iy) {
	__IEEE754_FLOAT_TYPE__ __z, __r, __v;
	__int32_t __ix;
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	__ix &= __INT32_C(0x7fffffff);      /* high word of x */
	if (__ix < __INT32_C(0x32000000)) { /* |x| < 2**-27 */
		if ((__int32_t)__x == 0)
			return __x;
	} /* generate inexact */
	__z = __x * __x;
	__v = __z * __x;
	__r = __LIBM_LOCAL_VALUE(S2f) +
	      __z * (__LIBM_LOCAL_VALUE(S3f) +
	             __z * (__LIBM_LOCAL_VALUE(S4f) +
	                    __z * (__LIBM_LOCAL_VALUE(S5f) +
	                           __z * __LIBM_LOCAL_VALUE(S6f))));
	if (__iy == 0) {
		return __x + __v * (__LIBM_LOCAL_VALUE(S1f) + __z * __r);
	} else {
		return __x - ((__z * (__LIBM_LOCAL_VALUE(halff) * __y - __v * __r) - __y) - __v * __LIBM_LOCAL_VALUE(S1f));
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
#ifndef __libm_half_defined
#define __libm_half_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, half, __IEEE754_DOUBLE_C(5.00000000000000000000e-01)) /* 0x3FE00000, 0x00000000 */
#endif /* !__libm_half_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, S1, __IEEE754_DOUBLE_C(-1.66666666666666324348e-01))  /* 0xBFC55555, 0x55555549 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, S2, __IEEE754_DOUBLE_C(8.33333333332248946124e-03))   /* 0x3F811111, 0x1110F8A6 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, S3, __IEEE754_DOUBLE_C(-1.98412698298579493134e-04))  /* 0xBF2A01A0, 0x19C161D5 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, S4, __IEEE754_DOUBLE_C(2.75573137070700676789e-06))   /* 0x3EC71DE3, 0x57B1FE7D */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, S5, __IEEE754_DOUBLE_C(-2.50507602534068634195e-08))  /* 0xBE5AE5E6, 0x8A2B9CEB */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, S6, __IEEE754_DOUBLE_C(1.58969099521155010221e-10))   /* 0x3DE5D93A, 0x5ACFD57C */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(kernel_sin) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_kernel_sin)(__IEEE754_DOUBLE_TYPE__ __x, __IEEE754_DOUBLE_TYPE__ __y, int __iy) {
	__IEEE754_DOUBLE_TYPE__ __z, __r, __v;
	__int32_t __ix;
	__LIBM_GET_HIGH_WORD(__ix, __x);
	__ix &= __INT32_C(0x7fffffff);      /* high word of x */
	if (__ix < __INT32_C(0x3e400000)) { /* |x| < 2**-27 */
		if ((__int32_t)__x == 0)
			return __x; /* generate inexact */
	}
	__z = __x * __x;
	__v = __z * __x;
	__r = __LIBM_LOCAL_VALUE(S2) +
	      __z * (__LIBM_LOCAL_VALUE(S3) +
	             __z * (__LIBM_LOCAL_VALUE(S4) +
	                    __z * (__LIBM_LOCAL_VALUE(S5) +
	                           __z * __LIBM_LOCAL_VALUE(S6))));
	if (__iy == 0) {
		return __x + __v * (__LIBM_LOCAL_VALUE(S1) + __z * __r);
	} else {
		return __x - ((__z * (__LIBM_LOCAL_VALUE(half) * __y - __v * __r) - __y) - __v * __LIBM_LOCAL_VALUE(S1));
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
/* sin x ~ ONE * x + x^3 ( SIN1 + SIN2 * x^2 + ... + SIN7 * x^12 + SIN8 * x^14 ) x in <0,0.1484375>  */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SIN1l, __IEEE854_LONG_DOUBLE_C(-1.66666666666666666666666666666666538e-01))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SIN2l, __IEEE854_LONG_DOUBLE_C(8.33333333333333333333333333307532934e-03))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SIN3l, __IEEE854_LONG_DOUBLE_C(-1.98412698412698412698412534478712057e-04))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SIN4l, __IEEE854_LONG_DOUBLE_C(2.75573192239858906520896496653095890e-06))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SIN5l, __IEEE854_LONG_DOUBLE_C(-2.50521083854417116999224301266655662e-08))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SIN6l, __IEEE854_LONG_DOUBLE_C(1.60590438367608957516841576404938118e-10))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SIN7l, __IEEE854_LONG_DOUBLE_C(-7.64716343504264506714019494041582610e-13))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SIN8l, __IEEE854_LONG_DOUBLE_C(2.81068754939739570236322404393398135e-15))
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(kernel_sinl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_kernel_sinl)(__IEEE854_LONG_DOUBLE_TYPE__ __x, __IEEE854_LONG_DOUBLE_TYPE__ __y, int __iy) {
	__IEEE854_LONG_DOUBLE_TYPE__ __absx, __h, __l;
	__IEEE854_LONG_DOUBLE_TYPE__ __z, __sin_l, __cos_l_m1;
	int __index;
#define __LIBM_SINCOSL_COS_HI 0
#define __LIBM_SINCOSL_COS_LO 1
#define __LIBM_SINCOSL_SIN_HI 2
#define __LIBM_SINCOSL_SIN_LO 3
	__absx = __ieee854_fabsl(__x);
	if (__absx < __IEEE854_LONG_DOUBLE_C(0.1484375)) {
		/* Argument is small enough to approximate it by a Chebyshev
		 * polynomial of degree 17. */
		if (__absx < __IEEE854_LONG_DOUBLE_C(0x1p-33))
			if (!((__int32_t)__x))
				return __x; /* generate inexact */
		__z = __x * __x;
		return __x + (__x * (__z * (__LIBM_LOCAL_VALUE(SIN1l) +
		                            __z * (__LIBM_LOCAL_VALUE(SIN2l) +
		                                   __z * (__LIBM_LOCAL_VALUE(SIN3l) +
		                                          __z * (__LIBM_LOCAL_VALUE(SIN4l) +
		                                                 __z * (__LIBM_LOCAL_VALUE(SIN5l) +
		                                                        __z * (__LIBM_LOCAL_VALUE(SIN6l) +
		                                                               __z * (__LIBM_LOCAL_VALUE(SIN7l) +
		                                                                      __z * __LIBM_LOCAL_VALUE(SIN8l))))))))));
	} else {
		/* So  that we  don't have to  use too large  polynomial, we find
		 * l and h such that x = l + h, where fabsl(l) <= 1.0/256 with 83
		 * possible  values  for h.  We look  up  cosl(h) and  sinl(h) in
		 * pre-computed  tables,  compute  cosl(l)  and  sinl(l)  using a
		 * Chebyshev    polynomial   of   degree   10(11)   and   compute
		 * sinl(h+l) = sinl(h)cosl(l) + cosl(h)sinl(l). */
		__index = (int)(128 * (__absx - (__IEEE854_LONG_DOUBLE_C(0.1484375) -
		                                 __IEEE854_LONG_DOUBLE_C(1.0) / __IEEE854_LONG_DOUBLE_C(256.0))));
		__h     = __IEEE854_LONG_DOUBLE_C(0.1484375) + __index / __IEEE854_LONG_DOUBLE_C(128.0);
		__index *= 4;
		if (__iy) {
			__l = (__x < 0 ? -__y : __y) - (__h - __absx);
		} else {
			__l = __absx - __h;
		}
		__z     = __l * __l;
		__sin_l = __l * (__LIBM_LOCAL_VALUE(ONEl) +
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

		__z = __sincosl_table[__index + __LIBM_SINCOSL_SIN_HI] +
		      (__sincosl_table[__index + __LIBM_SINCOSL_SIN_LO] +
		       (__sincosl_table[__index + __LIBM_SINCOSL_SIN_HI] * __cos_l_m1) +
		       (__sincosl_table[__index + __LIBM_SINCOSL_COS_HI] * __sin_l));
		return (__x < 0) ? -__z : __z;
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

#endif /* !_LIBM_KERNEL_SIN_H */
