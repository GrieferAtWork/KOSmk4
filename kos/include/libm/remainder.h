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
#ifndef _LIBM_REMAINDER_H
#define _LIBM_REMAINDER_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fdlibm.h>
#include <libm/fmod.h>
#include <libm/fabs.h>

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
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_remainderf)(__IEEE754_FLOAT_TYPE__ __x,
                                  __IEEE754_FLOAT_TYPE__ __p) {
	__int32_t __hx, __hp;
	__uint32_t __sx;
	__IEEE754_FLOAT_TYPE__ __p_half;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__LIBM_GET_FLOAT_WORD(__hp, __p);
	__sx = __hx & __UINT32_C(0x80000000);
	__hp &= __UINT32_C(0x7fffffff);
	__hx &= __UINT32_C(0x7fffffff);
	/* purge off exception values */
	if (__LIBM_FLT_UWORD_IS_ZERO(__hp) ||
	    !__LIBM_FLT_UWORD_IS_FINITE(__hx) ||
	    __LIBM_FLT_UWORD_IS_NAN(__hp))
		return (__x * __p) / (__x * __p);
	if (__hp <= __LIBM_FLT_UWORD_HALF_MAX)
		__x = __ieee754_fmodf(__x, __p + __p); /* now x < 2p */
	if ((__hx - __hp) == 0)
		return __LIBM_LOCAL_VALUE(zerof) * __x;
	__x = __ieee754_fabsf(__x);
	__p = __ieee754_fabsf(__p);
	if (__hp < __UINT32_C(0x01000000)) {
		if (__x + __x > __p) {
			__x -= __p;
			if (__x + __x >= __p)
				__x -= __p;
		}
	} else {
		__p_half = __IEEE754_FLOAT_C(0.5) * __p;
		if (__x > __p_half) {
			__x -= __p;
			if (__x >= __p_half)
				__x -= __p;
		}
	}
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__LIBM_SET_FLOAT_WORD(__x, __hx ^ __sx);
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
#ifndef __libm_zero_defined
#define __libm_zero_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, zero, __IEEE754_DOUBLE_C(0.00000000000000000000e+00)) /* 0x00000000, 0x00000000 */
#endif /* !__libm_zero_defined */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_remainder)(__IEEE754_DOUBLE_TYPE__ __x,
                                 __IEEE754_DOUBLE_TYPE__ __p) {
	__int32_t __hx, __hp;
	__uint32_t __sx, __lx, __lp;
	__IEEE754_DOUBLE_TYPE__ __p_half;
	__LIBM_GET_DOUBLE_WORDS(__hx, __lx, __x);
	__LIBM_GET_DOUBLE_WORDS(__hp, __lp, __p);
	__sx = __hx & __UINT32_C(0x80000000);
	__hp &= __UINT32_C(0x7fffffff);
	__hx &= __UINT32_C(0x7fffffff);

	/* purge off exception values */
	if ((__hp | __lp) == 0)
		return (__x * __p) / (__x * __p);  /* p = 0 */
	if ((__hx >= __UINT32_C(0x7ff00000)) ||  /* x not finite */
	    ((__hp >= __UINT32_C(0x7ff00000)) && /* p is NaN */
	     (((__hp - __UINT32_C(0x7ff00000)) | __lp) != 0)))
		return (__x * __p) / (__x * __p);

	if (__hp <= __UINT32_C(0x7fdfffff))
		__x = __ieee754_fmod(__x, __p + __p); /* now x < 2p */
	if (((__hx - __hp) | (__lx - __lp)) == 0)
		return __LIBM_LOCAL_VALUE(zero) * __x;
	__x = __ieee754_fabs(__x);
	__p = __ieee754_fabs(__p);
	if (__hp < __UINT32_C(0x00200000)) {
		if (__x + __x > __p) {
			__x -= __p;
			if (__x + __x >= __p)
				__x -= __p;
		}
	} else {
		__p_half = __IEEE754_DOUBLE_C(0.5) * __p;
		if (__x > __p_half) {
			__x -= __p;
			if (__x >= __p_half)
				__x -= __p;
		}
	}
	__LIBM_GET_HIGH_WORD(__hx, __x);
	__LIBM_SET_HIGH_WORD(__x, __hx ^ __sx);
	return __x;
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
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_remainderl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                  __IEEE854_LONG_DOUBLE_TYPE__ __p) {
	__uint32_t __sx, __sex, __sep, __x0, __x1, __p0, __p1;
	__IEEE854_LONG_DOUBLE_TYPE__ __p_half;
	__LIBM_GET_LDOUBLE_WORDS(__sex, __x0, __x1, __x);
	__LIBM_GET_LDOUBLE_WORDS(__sep, __p0, __p1, __p);
	__sx = __sex & __UINT32_C(0x8000);
	__sep &= IEEE854_LONG_DOUBLE_MAXEXP;
	__sex &= IEEE854_LONG_DOUBLE_MAXEXP;

	/* purge off exception values */
	if ((__sep | __p0 | __p1) == 0)
		return (__x * __p) / (__x * __p);               /* p = 0 */
	if ((__sex == IEEE854_LONG_DOUBLE_MAXEXP) ||  /* x not finite */
	    ((__sep == IEEE854_LONG_DOUBLE_MAXEXP) && /* p is NaN */
	     (((__p0 & __UINT32_C(0x7fffffff)) | __p1) != 0)))
		return (__x * __p) / (__x * __p);

	if (__sep < (IEEE854_LONG_DOUBLE_MAXEXP - 1))
		__x = __ieee854_fmodl(__x, __p + __p); /* now x < 2p */
	if (((__sex - __sep) | ((__x0 - __p0) & __UINT32_C(0x7fffffff)) | (__x1 - __p1)) == 0)
		return __LIBM_LOCAL_VALUE(zerol) * __x;
	__x = __ieee854_fabsl(__x);
	__p = __ieee854_fabsl(__p);
	if (__sep < 0x0002) {
		if (__x + __x > __p) {
			__x -= __p;
			if (__x + __x >= __p)
				__x -= __p;
		}
	} else {
		__p_half = __IEEE854_LONG_DOUBLE_C(0.5) * __p;
		if (__x > __p_half) {
			__x -= __p;
			if (__x >= __p_half)
				__x -= __p;
		}
	}
	__LIBM_GET_LDOUBLE_EXP(__sex, __x);
	__LIBM_SET_LDOUBLE_EXP(__x, __sex ^ __sx);
	return __x;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_REMAINDER_H */
