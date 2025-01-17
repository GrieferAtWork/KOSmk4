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
#ifndef _LIBM_FREXP_H
#define _LIBM_FREXP_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_two25f_defined
#define __libm_two25f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, two25f, __IEEE754_FLOAT_C(3.355443200e+07)) /* 0x4c000000 */
#endif /* !__libm_two25f_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(frexpf) __ATTR_WUNUSED __ATTR_NONNULL((2)) __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_frexpf)(__IEEE754_FLOAT_TYPE__ __x, int *__pexponent) {
	__int32_t __hx, __ix;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix         = __UINT32_C(0x7fffffff) & __hx;
	*__pexponent = 0;
	if (!__LIBM_FLT_UWORD_IS_FINITE(__ix) || __LIBM_FLT_UWORD_IS_ZERO(__ix))
		return __x; /* 0,inf,nan */
#ifndef _FLT_NO_DENORMALS
	if (__LIBM_FLT_UWORD_IS_SUBNORMAL(__ix)) { /* subnormal */
		__x *= __LIBM_LOCAL_VALUE(two25f);
		__LIBM_GET_FLOAT_WORD(__hx, __x);
		__ix         = __hx & __UINT32_C(0x7fffffff);
		*__pexponent = -25;
	}
#endif /* !_FLT_NO_DENORMALS */
	*__pexponent += (int)(__ix >> 23) - 126;
	__hx = (__hx & __UINT32_C(0x807fffff)) | __UINT32_C(0x3f000000);
	__LIBM_SET_FLOAT_WORD(__x, __hx);
	return __x;
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
#ifndef __libm_two54_defined
#define __libm_two54_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, two54, __IEEE754_DOUBLE_C(1.80143985094819840000e+16)) /* 0x43500000, 0x00000000 */
#endif /* !__libm_two54_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(frexp) __ATTR_WUNUSED __ATTR_NONNULL((2)) __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_frexp)(__IEEE754_DOUBLE_TYPE__ __x, int *__pexponent) {
	__int32_t __hx, __ix, __lx;
	__LIBM_GET_DOUBLE_WORDS(__hx, __lx, __x);
	__ix         = __UINT32_C(0x7fffffff) & __hx;
	*__pexponent = 0;
	if (__ix >= __INT32_C(0x7ff00000) || ((__ix | __lx) == 0))
		return __x;                     /* 0,inf,nan */
	if (__ix < __INT32_C(0x00100000)) { /* subnormal */
		__x *= __LIBM_LOCAL_VALUE(two54);
		__LIBM_GET_HIGH_WORD(__hx, __x);
		__ix         = __hx & __UINT32_C(0x7fffffff);
		*__pexponent = -54;
	}
	*__pexponent += (int)(__ix >> 20) - 1022;
	__hx = (__hx & __UINT32_C(0x800fffff)) | __UINT32_C(0x3fe00000);
	__LIBM_SET_HIGH_WORD(__x, __hx);
	return __x;
}

#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_DECLARE_BEGIN
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, two65, __IEEE754_DOUBLE_C(3.68934881474191032320e+19)) /* 0x4040, 0x80000000, 0x00000000 */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(frexpl) __ATTR_WUNUSED __ATTR_NONNULL((2)) __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_frexpl)(__IEEE854_LONG_DOUBLE_TYPE__ __x, int *__pexponent) {
	__uint32_t __se, __hx, __ix, __lx;
	__LIBM_GET_LDOUBLE_WORDS(__se, __hx, __lx, __x);
	__ix         = 0x7fff & __se;
	*__pexponent = 0;
	if (__ix == 0x7fff || ((__ix | __hx | __lx) == 0))
		return __x;       /* 0,inf,nan */
	if (__ix == 0x0000) { /* subnormal */
		__x *= __LIBM_LOCAL_VALUE(two65);
		__LIBM_GET_LDOUBLE_EXP(__se, __x);
		__ix         = __se & 0x7fff;
		*__pexponent = -65;
	}
	*__pexponent += (int)(__ix - 16382);
	__se = (__se & 0x8000) | 0x3ffe;
	__LIBM_SET_LDOUBLE_EXP(__x, __se);
	return __x;
}

#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_FREXP_H */
