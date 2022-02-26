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
#ifndef _LIBM_TRUNC_H
#define _LIBM_TRUNC_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/asm/trunc.h>
#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_truncf
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(truncf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_truncf)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __i0, __j0;
	__int32_t __sx;
	__LIBM_GET_FLOAT_WORD(__i0, __x);
	__sx = __i0 & __UINT32_C(0x80000000);
	__j0 = ((__i0 >> IEEE754_FLOAT_SHIFT) & IEEE754_FLOAT_MAXEXP) - IEEE754_FLOAT_BIAS;
	if (__j0 < IEEE754_FLOAT_SHIFT) {
		if (__j0 < 0) {
			/* The magnitude of the number is < 1 so the result is +-0.  */
			__LIBM_SET_FLOAT_WORD(__x, __sx);
		} else {
			__LIBM_SET_FLOAT_WORD(__x, __sx | (__i0 & ~(__UINT32_C(0x007fffff) >> __j0)));
		}
	} else {
		if (__j0 == (IEEE754_FLOAT_MAXEXP - IEEE754_FLOAT_BIAS))
			/* x is inf or NaN.  */
			return __x + __x;
	}
	return __x;
}
#endif /* !__ieee754_truncf */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_trunc
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(trunc) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_trunc)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __i0, __j0;
	__uint32_t __i1;
	__int32_t __sx;
	__LIBM_GET_DOUBLE_WORDS(__i0, __i1, __x);
	__sx = __i0 & __INT32_C(0x80000000);
	__j0 = ((__i0 >> IEEE754_DOUBLE_SHIFT) & IEEE754_DOUBLE_MAXEXP) - IEEE754_DOUBLE_BIAS;
	if (__j0 < IEEE754_DOUBLE_SHIFT) {
		if (__j0 < 0) {
			/* The magnitude of the number is < 1 so the result is +-0.  */
			__LIBM_INSERT_WORDS(__x, __sx, 0);
		} else {
			__LIBM_INSERT_WORDS(__x, __sx | (__i0 & ~(__UINT32_C(0x000fffff) >> __j0)), 0);
		}
	} else if (__j0 > 51) {
		if (__j0 == (IEEE754_DOUBLE_MAXEXP - IEEE754_DOUBLE_BIAS))
			/* x is inf or NaN.  */
			return __x + __x;
	} else {
		__LIBM_INSERT_WORDS(__x, __i0, __i1 & ~(__UINT32_C(0xffffffff) >> (__j0 - IEEE754_DOUBLE_SHIFT)));
	}
	return __x;
}
#endif /* !__ieee754_trunc */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_truncl
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(truncl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_truncl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__int32_t __i0, __j0;
	__uint32_t __se, __i1;
	__int32_t __sx;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__sx = __se & 0x8000;
	__j0 = (__se & IEEE854_LONG_DOUBLE_MAXEXP) - IEEE854_LONG_DOUBLE_BIAS;
	if (__j0 < 31) {
		if (__j0 < 0) {
			/* The magnitude of the number is < 1 so the result is +-0.  */
			__LIBM_SET_LDOUBLE_WORDS(__x, __sx, 0, 0);
		} else {
			__LIBM_SET_LDOUBLE_WORDS(__x, __se, __i0 & ~(__UINT32_C(0x7fffffff) >> __j0), 0);
		}
	} else if (__j0 > 63) {
		if (__j0 == (IEEE854_LONG_DOUBLE_MAXEXP - IEEE854_LONG_DOUBLE_BIAS))
			/* x is inf or NaN.  */
			return __x + __x;
	} else {
		/* avoid undefined behaviour for shift-count == 32 */
		if (__j0 != 63)
			__LIBM_SET_LDOUBLE_WORDS(__x, __se, __i0, __i1 & ~(__UINT32_C(0xffffffff) >> (__j0 - 31)));
	}
	return __x;
}
#endif /* !__ieee854_truncl */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_TRUNC_H */
