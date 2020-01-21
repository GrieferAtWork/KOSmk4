/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBM_RINT_H
#define _LIBM_RINT_H 1

#include <__crt.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

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
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_FLOAT_TYPE__, TWO23f, 2, { __IEEE754_FLOAT_C(8.3886080000e+06), __IEEE754_FLOAT_C(-8.3886080000e+06) }) /* 0x4b000000 0xcb000000 */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_rintf)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __i0, __j0, __sx;
	__uint32_t __i, __i1, __ix;
	__IEEE754_FLOAT_TYPE__ __t;
	volatile __IEEE754_FLOAT_TYPE__ __w;
	__LIBM_GET_FLOAT_WORD(__i0, __x);
	__sx = (__i0 >> 31) & 1;
	__ix = (__i0 & 0x7fffffff);
	__j0 = (__ix >> 23) - 0x7f;
	if (__j0 < 23) {
		if (__LIBM_FLT_UWORD_IS_ZERO(__ix))
			return __x;
		if (__j0 < 0) {
			__i1 = (__i0 & 0x07fffff);
			__i0 &= 0xfff00000;
			__i0 |= ((__i1 | -__i1) >> 9) & 0x400000;
			__LIBM_SET_FLOAT_WORD(__x, __i0);
			__w = __LIBM_LOCAL_VALUE(TWO23f)[__sx] + __x;
			__t = __w - __LIBM_LOCAL_VALUE(TWO23f)[__sx];
			__LIBM_GET_FLOAT_WORD(__i0, __t);
			__LIBM_SET_FLOAT_WORD(__t, (__i0 & 0x7fffffff) | (__sx << 31));
			return __t;
		} else {
			__i = (0x007fffff) >> __j0;
			if ((__i0 & __i) == 0)
				return __x; /* x is integral */
			__i >>= 1;
			if ((__i0 & __i) != 0)
				__i0 = (__i0 & (~__i)) | ((0x200000) >> __j0);
		}
	} else {
		if (!__LIBM_FLT_UWORD_IS_FINITE(__ix))
			return __x + __x; /* inf or NaN */
		else {
			return __x; /* x is integral */
		}
	}
	__LIBM_SET_FLOAT_WORD(__x, __i0);
	__w = __LIBM_LOCAL_VALUE(TWO23f)[__sx] + __x;
	return __w - __LIBM_LOCAL_VALUE(TWO23f)[__sx];
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
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, TWO52, 2, { __IEEE754_DOUBLE_C(4.50359962737049600000e+15), __IEEE754_DOUBLE_C(-4.50359962737049600000e+15) }) /* 0x43300000 0x00000000, 0xC3300000, 0x00000000 */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_rint)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __i0, __j0, __sx;
	__uint32_t __i, __i1;
	__IEEE754_DOUBLE_TYPE__ __t;
	volatile __IEEE754_DOUBLE_TYPE__ __w;
	__LIBM_EXTRACT_WORDS(__i0, __i1, __x);
	__sx = (__i0 >> 31) & 1;               /* sign */
	__j0 = ((__i0 >> 20) & 0x7ff) - 0x3ff; /* exponent */
	if (__j0 < 20) {                       /* no integral bits in LS part */
		if (__j0 < 0) {                    /* x is fractional or 0 */
			if (((__i0 & 0x7fffffff) | __i1) == 0)
				return __x; /* x == 0 */
			__i1 |= (__i0 & 0x0fffff);
			__i0 &= 0xfffe0000;
			__i0 |= ((__i1 | -__i1) >> 12) & 0x80000;
			__LIBM_SET_HIGH_WORD(__x, __i0);
			__w = __LIBM_LOCAL_VALUE(TWO52)[__sx] + __x;
			__t = __w - __LIBM_LOCAL_VALUE(TWO52)[__sx];
			__LIBM_GET_HIGH_WORD(__i0, __t);
			__LIBM_SET_HIGH_WORD(__t, (__i0 & 0x7fffffff) | (__sx << 31));
			return __t;
		} else { /* x has integer and maybe fraction */
			__i = (0x000fffff) >> __j0;
			if (((__i0 & __i) | __i1) == 0)
				return __x; /* x is integral */
			__i >>= 1;
			if (((__i0 & __i) | __i1) != 0) {
				/* 2nd or any later bit after radix is set */
				if (__j0 == 19)
					__i1 = 0x80000000;
				else
					__i1 = 0;
				__i0 = (__i0 & (~__i)) | ((0x40000) >> __j0);
			}
		}
	} else if (__j0 > 51) {
		if (__j0 == 0x400)
			return __x + __x; /* inf or NaN */
		else {
			return __x; /* x is integral */
		}
	} else {
		__i = ((__uint32_t)(0xffffffff)) >> (__j0 - 20);
		if ((__i1 & __i) == 0)
			return __x; /* x is integral */
		__i >>= 1;
		if ((__i1 & __i) != 0)
			__i1 = (__i1 & (~__i)) | ((0x40000000) >> (__j0 - 20));
	}
	__LIBM_INSERT_WORDS(__x, __i0, __i1);
	__w = __LIBM_LOCAL_VALUE(TWO52)[__sx] + __x;
	return __w - __LIBM_LOCAL_VALUE(TWO52)[__sx];
}

#endif /* __IEEE754_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBM_RINT_H */
