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
#ifndef _LIBM_SIN_H
#define _LIBM_SIN_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fdlibm.h>
#include <libm/kernel_cos.h>
#include <libm/kernel_sin.h>
#include <libm/rem_pio2.h>

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
__LIBM_LOCAL_FUNC(sinf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_sinf)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __y[2], __z = 0.0;
	__int32_t __n, __ix;
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	/* |x| ~< pi/4 */
	__ix &= __INT32_C(0x7fffffff);
	if (__ix <= __INT32_C(0x3f490fd8)) {
		return __ieee754_kernel_sinf(__x, __z, 0);
	} else if (!__LIBM_FLT_UWORD_IS_FINITE(__ix)) {
		/* sin(Inf or NaN) is NaN */
		return __x - __x;
	} else {
		/* argument reduction needed */
		__n = __ieee754_rem_pio2f(__x, __y);
		switch ((int)(__n & 3)) {
		case 0:
			return __ieee754_kernel_sinf(__y[0], __y[1], 1);
		case 1:
			return __ieee754_kernel_cosf(__y[0], __y[1]);
		case 2:
			return -__ieee754_kernel_sinf(__y[0], __y[1], 1);
		default:
			return -__ieee754_kernel_cosf(__y[0], __y[1]);
		}
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
__LIBM_LOCAL_FUNC(sin) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_sin)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __y[2], __z = 0.0;
	__int32_t __n, __ix;

	/* High word of x. */
	__LIBM_GET_HIGH_WORD(__ix, __x);

	/* |x| ~< pi/4 */
	__ix &= __INT32_C(0x7fffffff);
	if (__ix <= __INT32_C(0x3fe921fb)) {
		return __ieee754_kernel_sin(__x, __z, 0);
	} else if (__ix >= __INT32_C(0x7ff00000)) {
		/* sin(Inf or NaN) is NaN */
		return __x - __x;
	} else {
		/* argument reduction needed */
		__n = __ieee754_rem_pio2(__x, __y);
		switch ((int)(__n & 3)) {
		case 0:
			return __ieee754_kernel_sin(__y[0], __y[1], 1);
		case 1:
			return __ieee754_kernel_cos(__y[0], __y[1]);
		case 2:
			return -__ieee754_kernel_sin(__y[0], __y[1], 1);
		default:
			return -__ieee754_kernel_cos(__y[0], __y[1]);
		}
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
__LIBM_LOCAL_FUNC(sinl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_sinl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __y[2], __z = 0.0;
	__int32_t __n, __se;
	__uint32_t __i0, __i1;

	/* High word of x. */
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	(void)__i1;

	/* |x| ~< pi/4 */
	__se &= 0x7fff;
	if (__se < 0x3ffe || (__se == 0x3ffe && __i0 <= __UINT32_C(0xc90fdaa2))) {
		return __ieee854_kernel_sinl(__x, __z, 0);
	} else if (__se == 0x7fff) {
		/* sin(Inf or NaN) is NaN */
		return __x - __x;
	} else {
		/* argument reduction needed */
		__n = __ieee854_rem_pio2l(__x, __y);
		switch ((int)(__n & 3)) {
		case 0:
			return __ieee854_kernel_sinl(__y[0], __y[1], 1);
		case 1:
			return __ieee854_kernel_cosl(__y[0], __y[1]);
		case 2:
			return -__ieee854_kernel_sinl(__y[0], __y[1], 1);
		default:
			return -__ieee854_kernel_cosl(__y[0], __y[1]);
		}
	}
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_SIN_H */
