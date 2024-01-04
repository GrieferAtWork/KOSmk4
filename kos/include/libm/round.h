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
#ifndef _LIBM_ROUND_H
#define _LIBM_ROUND_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/asm/round.h>
#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_roundf
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

#ifndef __libm_hugef_defined
#define __libm_hugef_defined
__LIBM_LOCAL_DECLARE_BEGIN
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, hugef, __IEEE754_FLOAT_C(1.0e30))
__LIBM_LOCAL_DECLARE_END
#endif /* !__libm_hugef_defined */

__LIBM_LOCAL_FUNC(roundf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_roundf)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __i0, __j0;
	__LIBM_GET_FLOAT_WORD(__i0, __x);
	__j0 = ((__i0 >> IEEE754_FLOAT_SHIFT) & IEEE754_FLOAT_MAXEXP) - IEEE754_FLOAT_BIAS;
	if (__j0 < IEEE754_FLOAT_SHIFT) {
		if (__j0 < 0) {
			__libm_math_force_eval_r(__IEEE754_FLOAT_TYPE__, __LIBM_LOCAL_VALUE(hugef) + __x);
			__i0 &= __INT32_C(0x80000000);
			if (__j0 == -1)
				__i0 |= __INT32_C(0x3f800000);
		} else {
			__uint32_t i = __UINT32_C(0x007fffff) >> __j0;
			if ((__i0 & i) == 0)
				/* X is integral. */
				return __x;
			__libm_math_force_eval_r(__IEEE754_FLOAT_TYPE__, __LIBM_LOCAL_VALUE(hugef) + __x);
			/* Raise inexact if x != 0. */
			__i0 += __UINT32_C(0x00400000) >> __j0;
			__i0 &= ~i;
		}
	} else {
		if (__j0 == (IEEE754_FLOAT_MAXEXP - IEEE754_FLOAT_BIAS)) {
			return __x + __x; /* Inf or NaN. */
		} else {
			return __x;
		}
	}
	__LIBM_SET_FLOAT_WORD(__x, __i0);
	return __x;
}
#endif /* !__ieee754_roundf */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_round
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

#ifndef __libm_huge_defined
#define __libm_huge_defined
__LIBM_LOCAL_DECLARE_BEGIN
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, huge, __IEEE754_DOUBLE_C(1.0e300))
__LIBM_LOCAL_DECLARE_END
#endif /* !__libm_huge_defined */

__LIBM_LOCAL_FUNC(round) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_round)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __i0, __j0;
	__uint32_t __i1;
	__LIBM_GET_DOUBLE_WORDS(__i0, __i1, __x);
	__j0 = ((__i0 >> IEEE754_DOUBLE_SHIFT) & IEEE754_DOUBLE_MAXEXP) - IEEE754_DOUBLE_BIAS;
	if (__j0 < IEEE754_DOUBLE_SHIFT) {
		if (__j0 < 0) {
			__libm_math_force_eval_r(__IEEE754_DOUBLE_TYPE__, __LIBM_LOCAL_VALUE(huge) + __x);
			__i0 &= __UINT32_C(0x80000000);
			if (__j0 == -1) /* Result is +1.0 or -1.0. */
				__i0 |= __UINT32_C(0x3ff00000);
			__i1 = 0;
		} else {
			__uint32_t i = __UINT32_C(0x000fffff) >> __j0;
			if (((__i0 & i) | __i1) == 0)
				/* X is integral. */
				return __x;
			/* Raise inexact if x != 0. */
			__libm_math_force_eval_r(__IEEE754_DOUBLE_TYPE__, __LIBM_LOCAL_VALUE(huge) + __x);
			__i0 += __UINT32_C(0x00080000) >> __j0;
			__i0 &= ~i;
			__i1 = 0;
		}
	} else if (__j0 > 51) {
		if (__j0 == (IEEE754_DOUBLE_MAXEXP - IEEE754_DOUBLE_BIAS)) {
			return __x + __x; /* Inf or NaN. */
		} else {
			return __x;
		}
	} else {
		__uint32_t i = __UINT32_C(0xffffffff) >> (__j0 - IEEE754_DOUBLE_SHIFT);
		__uint32_t j;
		if ((__i1 & i) == 0)
			/* X is integral. */
			return __x;
		/* Raise inexact if x != 0. */
		__libm_math_force_eval_r(__IEEE754_DOUBLE_TYPE__, __LIBM_LOCAL_VALUE(huge) + __x);
		j = __i1 + (__UINT32_C(1) << (51 - __j0));
		if (j < __i1)
			__i0 += 1;
		__i1 = j;
		__i1 &= ~i;
	}
	__LIBM_INSERT_WORDS(__x, __i0, __i1);
	return __x;
}
#endif /* !__ieee754_round */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_roundl
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

#ifndef __libm_hugeval4930l_defined
#define __libm_hugeval4930l_defined
__LIBM_LOCAL_DECLARE_BEGIN
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, hugeval4930l, __IEEE854_LONG_DOUBLE_C(1.0e4930))
__LIBM_LOCAL_DECLARE_END
#endif /* !__libm_hugeval4930l_defined */

__LIBM_LOCAL_FUNC(roundl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_roundl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__int32_t __j0;
	__uint32_t se, __i1, __i0;
	__LIBM_GET_LDOUBLE_WORDS(se, __i0, __i1, __x);
	__j0 = (se & IEEE854_LONG_DOUBLE_MAXEXP) - IEEE854_LONG_DOUBLE_BIAS;
	if (__j0 < 31) {
		if (__j0 < 0) {
			__libm_math_force_eval_r(__IEEE854_LONG_DOUBLE_TYPE__, __LIBM_LOCAL_VALUE(hugeval4930l) + __x);
			se &= 0x8000;
			__i0 = __i1 = 0;
			if (__j0 == -1) {
				se |= 0x3fff;
				__i0 = __UINT32_C(0x80000000);
			}
		} else {
			__uint32_t i = __UINT32_C(0x7fffffff) >> __j0;
			__uint32_t j;
			if (((__i0 & i) | __i1) == 0)
				/* X is integral. */
				return __x;
			/* Raise inexact if x != 0. */
			__libm_math_force_eval_r(__IEEE854_LONG_DOUBLE_TYPE__, __LIBM_LOCAL_VALUE(hugeval4930l) + __x);
			j = __i0 + (__UINT32_C(0x40000000) >> __j0);
			if (j < __i0)
				se += 1;
			__i0 = (j & ~i) | __INT32_C(0x80000000);
			__i1 = 0;
		}
	} else if (__j0 > 62) {
		if (__j0 == (IEEE854_LONG_DOUBLE_MAXEXP - IEEE854_LONG_DOUBLE_BIAS)) {
			return __x + __x; /* Inf or NaN. */
		} else {
			return __x;
		}
	} else {
		__uint32_t i = __UINT32_C(0xffffffff) >> (__j0 - 31);
		__uint32_t j;
		if ((__i1 & i) == 0)
			return __x; /* X is integral. */
		/* Raise inexact if x != 0. */
		__libm_math_force_eval_r(__IEEE854_LONG_DOUBLE_TYPE__, __LIBM_LOCAL_VALUE(hugeval4930l) + __x);
		j = __i1 + (__UINT32_C(1) << (62 - __j0));
		if (j < __i1) {
			__uint32_t k = __i0 + 1;
			if (k < __i0) {
				se += 1;
				k |= __UINT32_C(0x80000000);
			}
			__i0 = k;
		}
		__i1 = j;
		__i1 &= ~i;
	}
	__LIBM_SET_LDOUBLE_WORDS(__x, se, __i0, __i1);
	return __x;
}
#endif /* !__ieee854_roundl */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ROUND_H */
