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
#ifndef _LIBM_REM_PIO2_H
#define _LIBM_REM_PIO2_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fdlibm.h>
#include <libm/kernel_rem_pio2.h>

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
/* This array is like the one in e_rem_pio2.c, but the numbers are
 * single  precision  and  the  last  8  bits  are  forced  to  0. */
__LIBM_LOCAL_DECLARE_ARRAY(__int32_t, npio2_hwf, 32) {
	__INT32_C(0x3fc90f00), __INT32_C(0x40490f00), __INT32_C(0x4096cb00), __INT32_C(0x40c90f00), __INT32_C(0x40fb5300), __INT32_C(0x4116cb00),
	__INT32_C(0x412fed00), __INT32_C(0x41490f00), __INT32_C(0x41623100), __INT32_C(0x417b5300), __INT32_C(0x418a3a00), __INT32_C(0x4196cb00),
	__INT32_C(0x41a35c00), __INT32_C(0x41afed00), __INT32_C(0x41bc7e00), __INT32_C(0x41c90f00), __INT32_C(0x41d5a000), __INT32_C(0x41e23100),
	__INT32_C(0x41eec200), __INT32_C(0x41fb5300), __INT32_C(0x4203f200), __INT32_C(0x420a3a00), __INT32_C(0x42108300), __INT32_C(0x4216cb00),
	__INT32_C(0x421d1400), __INT32_C(0x42235c00), __INT32_C(0x4229a500), __INT32_C(0x422fed00), __INT32_C(0x42363600), __INT32_C(0x423c7e00),
	__INT32_C(0x4242c700), __INT32_C(0x42490f00)
};
/* invpio2:  24 bits of 2/pi
 * pio2_1:   first  17 bit of pi/2
 * pio2_1t:  pi/2 - pio2_1
 * pio2_2:   second 17 bit of pi/2
 * pio2_2t:  pi/2 - (pio2_1+pio2_2)
 * pio2_3:   third  17 bit of pi/2
 * pio2_3t:  pi/2 - (pio2_1+pio2_2+pio2_3) */
#ifndef __libm_zerof_defined
#define __libm_zerof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, zerof, __IEEE754_FLOAT_C(0.0000000000e+00)) /* 0x00000000 */
#endif /* !__libm_zerof_defined */
#ifndef __libm_halff_defined
#define __libm_halff_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, halff, __IEEE754_FLOAT_C(5.0000000000e-01)) /* 0x3f000000 */
#endif /* !__libm_halff_defined */
#ifndef __libm_two8f_defined
#define __libm_two8f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, two8f, __IEEE754_FLOAT_C(2.5600000000e+02))  /* 0x43800000 */
#endif /* !__libm_two8f_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, invpio2f, __IEEE754_FLOAT_C(6.3661980629e-01)) /* 0x3f22f984 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pio2_1f, __IEEE754_FLOAT_C(1.5707855225e+00))  /* 0x3fc90f80 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pio2_1tf, __IEEE754_FLOAT_C(1.0804334124e-05)) /* 0x37354443 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pio2_2f, __IEEE754_FLOAT_C(1.0804273188e-05))  /* 0x37354400 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pio2_2tf, __IEEE754_FLOAT_C(6.0770999344e-11)) /* 0x2e85a308 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pio2_3f, __IEEE754_FLOAT_C(6.0770943833e-11))  /* 0x2e85a300 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pio2_3tf, __IEEE754_FLOAT_C(6.1232342629e-17)) /* 0x248d3132 */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(rem_pio2f) __ATTR_WUNUSED __ATTR_NONNULL((2)) __int32_t
(__LIBCCALL __ieee754_rem_pio2f)(__IEEE754_FLOAT_TYPE__ __x,
                                 __IEEE754_FLOAT_TYPE__ *__y) {
	__IEEE754_FLOAT_TYPE__ __z, __w, __t, __r, __fn;
	__IEEE754_FLOAT_TYPE__ __tx[3];
	__int32_t __e0, __i, __j, __nx, __n, __ix, __hx;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix <= __INT32_C(0x3f490fd8)) { /* |x| ~<= pi/4 , no need for reduction */
		__y[0] = __x;
		__y[1] = 0;
		return 0;
	}
	if (__ix < __INT32_C(0x4016cbe4)) { /* |x| < 3pi/4, special case with n=+-1 */
		if (__hx > 0) {
			__z = __x - __LIBM_LOCAL_VALUE(pio2_1f);
			if ((__ix & __INT32_C(0xfffffff0)) != __INT32_C(0x3fc90fd0)) { /* 24+24 bit pi OK */
				__y[0] = __z - __LIBM_LOCAL_VALUE(pio2_1tf);
				__y[1] = (__z - __y[0]) - __LIBM_LOCAL_VALUE(pio2_1tf);
			} else { /* near pi/2, use 24+24+24 bit pi */
				__z -= __LIBM_LOCAL_VALUE(pio2_2f);
				__y[0] = __z - __LIBM_LOCAL_VALUE(pio2_2tf);
				__y[1] = (__z - __y[0]) - __LIBM_LOCAL_VALUE(pio2_2tf);
			}
			return 1;
		} else { /* negative x */
			__z = __x + __LIBM_LOCAL_VALUE(pio2_1f);
			if ((__ix & __INT32_C(0xfffffff0)) != __INT32_C(0x3fc90fd0)) { /* 24+24 bit pi OK */
				__y[0] = __z + __LIBM_LOCAL_VALUE(pio2_1tf);
				__y[1] = (__z - __y[0]) + __LIBM_LOCAL_VALUE(pio2_1tf);
			} else { /* near pi/2, use 24+24+24 bit pi */
				__z += __LIBM_LOCAL_VALUE(pio2_2f);
				__y[0] = __z + __LIBM_LOCAL_VALUE(pio2_2tf);
				__y[1] = (__z - __y[0]) + __LIBM_LOCAL_VALUE(pio2_2tf);
			}
			return -1;
		}
	}
	if (__ix <= __INT32_C(0x43490f80)) { /* |x| ~<= 2^7*(pi/2), medium size */
		__t  = __ieee754_fabsf(__x);
		__n  = (__int32_t)(__t * __LIBM_LOCAL_VALUE(invpio2f) + __LIBM_LOCAL_VALUE(halff));
		__fn = (__IEEE754_FLOAT_TYPE__)__n;
		__r  = __t - __fn * __LIBM_LOCAL_VALUE(pio2_1f);
		__w  = __fn * __LIBM_LOCAL_VALUE(pio2_1tf); /* 1st round good to 40 bit */
		if (__n < 32 && (__int32_t)(__ix & __INT32_C(0xffffff00)) != __LIBM_LOCAL_VALUE(npio2_hwf)[__n - 1]) {
			__y[0] = __r - __w; /* quick check no cancellation */
		} else {
			__uint32_t __high;
			__j    = __ix >> __LIBM_IEEE754_FLOAT_SHIFT;
			__y[0] = __r - __w;
			__LIBM_GET_FLOAT_WORD(__high, __y[0]);
			__i = __j - ((__high >> __LIBM_IEEE754_FLOAT_SHIFT) & __LIBM_IEEE754_FLOAT_MAXEXP);
			if (__i > 8) { /* 2nd iteration needed, good to 57 */
				__t    = __r;
				__w    = __fn * __LIBM_LOCAL_VALUE(pio2_2f);
				__r    = __t - __w;
				__w    = __fn * __LIBM_LOCAL_VALUE(pio2_2tf) - ((__t - __r) - __w);
				__y[0] = __r - __w;
				__LIBM_GET_FLOAT_WORD(__high, __y[0]);
				__i = __j - ((__high >> __LIBM_IEEE754_FLOAT_SHIFT) & __LIBM_IEEE754_FLOAT_MAXEXP);
				if (__i > 25) {   /* 3rd iteration need, 74 bits acc */
					__t    = __r; /* will cover all possible cases */
					__w    = __fn * __LIBM_LOCAL_VALUE(pio2_3f);
					__r    = __t - __w;
					__w    = __fn * __LIBM_LOCAL_VALUE(pio2_3tf) - ((__t - __r) - __w);
					__y[0] = __r - __w;
				}
			}
		}
		__y[1] = (__r - __y[0]) - __w;
		if (__hx < 0) {
			__y[0] = -__y[0];
			__y[1] = -__y[1];
			return -__n;
		} else {
			return __n;
		}
	}
	/* all other (large) arguments */
	if (!__LIBM_FLT_UWORD_IS_FINITE(__ix)) { /* x is inf or NaN */
		__y[0] = __y[1] = __x - __x;
		return 0;
	}
	/* set z = scalbn(|x|,ilogb(x)-7) */
	__e0 = (__ix >> __LIBM_IEEE754_FLOAT_SHIFT) - (__LIBM_IEEE754_FLOAT_BIAS + 7); /* e0 = ilogb(z)-7; */
	__LIBM_SET_FLOAT_WORD(__z, __ix - (__e0 << __LIBM_IEEE754_FLOAT_SHIFT));
	for (__i = 0; __i < 2; __i++) {
		__tx[__i] = (__IEEE754_FLOAT_TYPE__)((__int32_t)(__z));
		__z       = (__z - __tx[__i]) * __LIBM_LOCAL_VALUE(two8f);
	}
	__tx[2] = __z;
	__nx    = 3;
	while (__tx[__nx - 1] == __LIBM_LOCAL_VALUE(zerof))
		__nx--; /* skip zero term */
	__n = __ieee754_kernel_rem_pio2f(__tx, __y, __e0, __nx, 2);
	if (__hx < 0) {
		__y[0] = -__y[0];
		__y[1] = -__y[1];
		return -__n;
	}
	return __n;
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
__LIBM_LOCAL_DECLARE_ARRAY(__int32_t, npio2_hw, 32) {
	__INT32_C(0x3FF921FB), __INT32_C(0x400921FB), __INT32_C(0x4012D97C), __INT32_C(0x401921FB), __INT32_C(0x401F6A7A), __INT32_C(0x4022D97C),
	__INT32_C(0x4025FDBB), __INT32_C(0x402921FB), __INT32_C(0x402C463A), __INT32_C(0x402F6A7A), __INT32_C(0x4031475C), __INT32_C(0x4032D97C),
	__INT32_C(0x40346B9C), __INT32_C(0x4035FDBB), __INT32_C(0x40378FDB), __INT32_C(0x403921FB), __INT32_C(0x403AB41B), __INT32_C(0x403C463A),
	__INT32_C(0x403DD85A), __INT32_C(0x403F6A7A), __INT32_C(0x40407E4C), __INT32_C(0x4041475C), __INT32_C(0x4042106C), __INT32_C(0x4042D97C),
	__INT32_C(0x4043A28C), __INT32_C(0x40446B9C), __INT32_C(0x404534AC), __INT32_C(0x4045FDBB), __INT32_C(0x4046C6CB), __INT32_C(0x40478FDB),
	__INT32_C(0x404858EB), __INT32_C(0x404921FB)
};

/* invpio2:  53 bits of 2/pi
 * pio2_1:   first  33 bit of pi/2
 * pio2_1t:  pi/2 - pio2_1
 * pio2_2:   second 33 bit of pi/2
 * pio2_2t:  pi/2 - (pio2_1+pio2_2)
 * pio2_3:   third  33 bit of pi/2
 * pio2_3t:  pi/2 - (pio2_1+pio2_2+pio2_3) */
#ifndef __libm_zero_defined
#define __libm_zero_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, zero, __IEEE754_DOUBLE_C(0.00000000000000000000e+00)) /* 0x00000000, 0x00000000 */
#endif /* !__libm_zero_defined */
#ifndef __libm_half_defined
#define __libm_half_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, half, __IEEE754_DOUBLE_C(5.00000000000000000000e-01)) /* 0x3FE00000, 0x00000000 */
#endif /* !__libm_half_defined */
#ifndef __libm_two24_defined
#define __libm_two24_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, two24, __IEEE754_DOUBLE_C(1.67772160000000000000e+07)) /* 0x41700000, 0x00000000 */
#endif /* !__libm_two24_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, invpio2, __IEEE754_DOUBLE_C(6.36619772367581382433e-01)) /* 0x3FE45F30, 0x6DC9C883 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pio2_1, __IEEE754_DOUBLE_C(1.57079632673412561417e+00))  /* 0x3FF921FB, 0x54400000 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pio2_1t, __IEEE754_DOUBLE_C(6.07710050650619224932e-11)) /* 0x3DD0B461, 0x1A626331 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pio2_2, __IEEE754_DOUBLE_C(6.07710050630396597660e-11))  /* 0x3DD0B461, 0x1A600000 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pio2_2t, __IEEE754_DOUBLE_C(2.02226624879595063154e-21)) /* 0x3BA3198A, 0x2E037073 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pio2_3, __IEEE754_DOUBLE_C(2.02226624871116645580e-21))  /* 0x3BA3198A, 0x2E000000 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pio2_3t, __IEEE754_DOUBLE_C(8.47842766036889956997e-32)) /* 0x397B839A, 0x252049C1 */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(rem_pio2) __ATTR_WUNUSED __ATTR_NONNULL((2)) __int32_t
(__LIBCCALL __ieee754_rem_pio2)(__IEEE754_DOUBLE_TYPE__ __x,
                                __IEEE754_DOUBLE_TYPE__ *__y) {
	__IEEE754_DOUBLE_TYPE__ __z, __w, __t, __r, __fn;
	__IEEE754_DOUBLE_TYPE__ __tx[3];
	__int32_t __e0, __i, __j, __nx, __n, __ix, __hx;
	__uint32_t __low;
	__LIBM_GET_HIGH_WORD(__hx, __x); /* high word of x */
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix <= __INT32_C(0x3fe921fb)) { /* |x| ~<= pi/4 , no need for reduction */
		__y[0] = __x;
		__y[1] = 0;
		return 0;
	}
	if (__ix < __INT32_C(0x4002d97c)) { /* |x| < 3pi/4, special case with n=+-1 */
		if (__hx > 0) {
			__z = __x - __LIBM_LOCAL_VALUE(pio2_1);
			if (__ix != __INT32_C(0x3ff921fb)) { /* 33+53 bit pi is good enough */
				__y[0] = __z - __LIBM_LOCAL_VALUE(pio2_1t);
				__y[1] = (__z - __y[0]) - __LIBM_LOCAL_VALUE(pio2_1t);
			} else { /* near pi/2, use 33+33+53 bit pi */
				__z -= __LIBM_LOCAL_VALUE(pio2_2);
				__y[0] = __z - __LIBM_LOCAL_VALUE(pio2_2t);
				__y[1] = (__z - __y[0]) - __LIBM_LOCAL_VALUE(pio2_2t);
			}
			return 1;
		} else { /* negative x */
			__z = __x + __LIBM_LOCAL_VALUE(pio2_1);
			if (__ix != __INT32_C(0x3ff921fb)) { /* 33+53 bit pi is good enough */
				__y[0] = __z + __LIBM_LOCAL_VALUE(pio2_1t);
				__y[1] = (__z - __y[0]) + __LIBM_LOCAL_VALUE(pio2_1t);
			} else { /* near pi/2, use 33+33+53 bit pi */
				__z += __LIBM_LOCAL_VALUE(pio2_2);
				__y[0] = __z + __LIBM_LOCAL_VALUE(pio2_2t);
				__y[1] = (__z - __y[0]) + __LIBM_LOCAL_VALUE(pio2_2t);
			}
			return -1;
		}
	}

	if (__ix <= __INT32_C(0x413921fb)) { /* |x| ~<= 2^19*(pi/2), medium size */
		__t  = __ieee754_fabs(__x);
		__n  = (__int32_t)(__t * __LIBM_LOCAL_VALUE(invpio2) + __LIBM_LOCAL_VALUE(half));
		__fn = (__IEEE754_DOUBLE_TYPE__)__n;
		__r  = __t - __fn * __LIBM_LOCAL_VALUE(pio2_1);
		__w  = __fn * __LIBM_LOCAL_VALUE(pio2_1t); /* 1st round good to 85 bit */
		if (__n < 32 && __ix != __LIBM_LOCAL_VALUE(npio2_hw)[__n - 1]) {
			__y[0] = __r - __w; /* quick check no cancellation */
		} else {
			__uint32_t __high;
			__j    = __ix >> __LIBM_IEEE754_DOUBLE_SHIFT;
			__y[0] = __r - __w;
			__LIBM_GET_HIGH_WORD(__high, __y[0]);
			__i = __j - ((__high >> __LIBM_IEEE754_DOUBLE_SHIFT) & __LIBM_IEEE754_DOUBLE_MAXEXP);
			if (__i > 16) { /* 2nd iteration needed, good to 118 */
				__t    = __r;
				__w    = __fn * __LIBM_LOCAL_VALUE(pio2_2);
				__r    = __t - __w;
				__w    = __fn * __LIBM_LOCAL_VALUE(pio2_2t) - ((__t - __r) - __w);
				__y[0] = __r - __w;
				__LIBM_GET_HIGH_WORD(__high, __y[0]);
				__i = __j - ((__high >> __LIBM_IEEE754_DOUBLE_SHIFT) & __LIBM_IEEE754_DOUBLE_MAXEXP);
				if (__i > 49) {   /* 3rd iteration need, 151 bits acc */
					__t    = __r; /* will cover all possible cases */
					__w    = __fn * __LIBM_LOCAL_VALUE(pio2_3);
					__r    = __t - __w;
					__w    = __fn * __LIBM_LOCAL_VALUE(pio2_3t) - ((__t - __r) - __w);
					__y[0] = __r - __w;
				}
			}
		}
		__y[1] = (__r - __y[0]) - __w;
		if (__hx < 0) {
			__y[0] = -__y[0];
			__y[1] = -__y[1];
			return -__n;
		} else {
			return __n;
		}
	}
	/* all other (large) arguments */
	if (__ix >= __INT32_C(0x7ff00000)) { /* x is inf or NaN */
		__y[0] = __y[1] = __x - __x;
		return 0;
	}
	/* set z = scalbn(|x|,ilogb(x)-23) */
	__LIBM_GET_LOW_WORD(__low, __x);
	__e0 = (__ix >> __LIBM_IEEE754_DOUBLE_SHIFT) - (__LIBM_IEEE754_DOUBLE_BIAS + 23); /* e0 = ilogb(z)-23; */
	__LIBM_INSERT_WORDS(__z, __ix - (__e0 << __LIBM_IEEE754_DOUBLE_SHIFT), __low);
	for (__i = 0; __i < 2; __i++) {
		__tx[__i] = (__IEEE754_DOUBLE_TYPE__)((__int32_t)(__z));
		__z       = (__z - __tx[__i]) * __LIBM_LOCAL_VALUE(two24);
	}
	__tx[2] = __z;
	__nx    = 3;
	while (__tx[__nx - 1] == __LIBM_LOCAL_VALUE(zero))
		__nx--; /* skip zero term */
	__n = __ieee754_kernel_rem_pio2(__tx, __y, __e0, __nx, 2);
	if (__hx < 0) {
		__y[0] = -__y[0];
		__y[1] = -__y[1];
		return -__n;
	}
	return __n;
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* Extended-precision floating point argument reduction.
   Copyright (C) 1999-2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Based on quad-precision code by Jakub Jelinek <jj@ultra.linux.cz>

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
__LIBM_LOCAL_FUNC(rem_pio2l) __ATTR_WUNUSED __ATTR_NONNULL((2)) __int32_t
(__LIBCCALL __ieee854_rem_pio2l)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                 __IEEE854_LONG_DOUBLE_TYPE__ *__y) {
	__IEEE754_DOUBLE_TYPE__ __tx[3], __ty[3];
	__int32_t __se, __j0;
	__uint32_t __i0, __i1;
	__int32_t __sx;
	__int32_t __n, __exp;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__sx = (__se >> 15) & 1;
	__j0 = (__se & __LIBM_IEEE854_LONG_DOUBLE_MAXEXP);
	if (__j0 < (-__INT32_C(1) + __LIBM_IEEE854_LONG_DOUBLE_BIAS)) {
		/* |x| < pi/4.  */
		__y[0] = __x;
		__y[1] = 0;
		return 0;
	}
	if (__j0 >= (__INT32_C(0x8000) + __LIBM_IEEE854_LONG_DOUBLE_BIAS)) {
		/* x is infinite or NaN.  */
		__y[0] = __x - __x;
		__y[1] = __y[0];
		return 0;
	}

	/* Split the 64 bits of the mantissa into three 24-bit integers
	 * stored in a __IEEE754_DOUBLE_TYPE__ array. */
	__exp   = (__j0 - __LIBM_IEEE854_LONG_DOUBLE_BIAS) - 23;
	__tx[0] = (__IEEE754_DOUBLE_TYPE__)(__i0 >> 8);
	__tx[1] = (__IEEE754_DOUBLE_TYPE__)(((__i0 << 16) | (__i1 >> 16)) & __INT32_C(0xffffff));
	__tx[2] = (__IEEE754_DOUBLE_TYPE__)((__i1 << 8) & __INT32_C(0xffffff));
	__n     = __ieee854_kernel_rem_pio2l(__tx, __ty, __exp, 3, 2);
	/* The result is now stored in two __IEEE754_DOUBLE_TYPE__ values, we need to convert
	 * it into two __IEEE854_LONG_DOUBLE_TYPE__ values. */
	if (__sx == 0) {
		__y[0] = (__IEEE854_LONG_DOUBLE_TYPE__)__ty[0] + (__IEEE854_LONG_DOUBLE_TYPE__)__ty[1];
		__y[1] = __ty[1] - (__y[0] - __ty[0]);
		return __n;
	} else {
		__y[0] = -((__IEEE854_LONG_DOUBLE_TYPE__)__ty[0] + (__IEEE854_LONG_DOUBLE_TYPE__)__ty[1]);
		__y[1] = -__ty[1] - (__y[0] + __ty[0]);
		return -__n;
	}
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_REM_PIO2_H */
