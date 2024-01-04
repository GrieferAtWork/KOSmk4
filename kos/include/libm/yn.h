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
#ifndef _LIBM_YN_H
#define _LIBM_YN_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/math-constants.h> /* TODO: Replace uses below with __IEEE754_ constants */
#include <bits/types.h>

#include <libm/fdlibm.h>
#include <libm/sincos.h>
#include <libm/y0.h>
#include <libm/y1.h>

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

__LIBM_LOCAL_FUNC(ynf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_ynf)(int __n, __IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __a, __b, __temp;
	__int32_t __i, __hx, __ix;
	__uint32_t __ib;
	int __sign;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __INT32_C(0x7fffffff) & __hx;
	/* if Y(n,NaN) is NaN */
	if (__LIBM_FLT_UWORD_IS_NAN(__ix))
		return __x + __x;
	if (__LIBM_FLT_UWORD_IS_ZERO(__ix))
		return -__HUGE_VALF + __x; /* -inf and overflow exception.  */
	if (__hx < 0)
		return __LIBM_LOCAL_VALUE(zerof) / (__LIBM_LOCAL_VALUE(zerof) * __x);
	__sign = 1;
	if (__n < 0) {
		__n    = -__n;
		__sign = 1 - ((__n & 1) << 1);
	}
	if (__n == 0)
		return (__ieee754_y0f(__x));
	if (__n == 1)
		return (__sign * __ieee754_y1f(__x));
	if (__LIBM_FLT_UWORD_IS_INFINITE(__ix))
		return __LIBM_LOCAL_VALUE(zerof);
	__a = __ieee754_y0f(__x);
	__b = __ieee754_y1f(__x);
	/* quit if b is -inf */
	__LIBM_GET_FLOAT_WORD(__ib, __b);
	for (__i = 1; __i < __n && __ib != __UINT32_C(0xff800000); ++__i) {
		__temp = __b;
		__b    = ((__IEEE754_FLOAT_TYPE__)(__i + __i) / __x) * __b - __a;
		__LIBM_GET_FLOAT_WORD(__ib, __b);
		__a = __temp;
	}
	if (__sign > 0)
		return __b;
	return -__b;
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
#ifndef __libm_invsqrtpi_defined
#define __libm_invsqrtpi_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, invsqrtpi, __IEEE754_DOUBLE_C(5.64189583547756279280e-01)) /* 0x3FE20DD7, 0x50429B6D */
#endif /* !__libm_invsqrtpi_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(yn) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_yn)(int __n, __IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __i, __hx, __ix, __lx;
	__int32_t __sign;
	__IEEE754_DOUBLE_TYPE__ __a, __b, __temp;
	__LIBM_GET_DOUBLE_WORDS(__hx, __lx, __x);
	__ix = __INT32_C(0x7fffffff) & __hx;
	/* if Y(n,NaN) is NaN */
	if ((__ix | (((__uint32_t)(__lx | -__lx)) >> 31)) > __INT32_C(0x7ff00000))
		return __x + __x;
	if ((__ix | __lx) == 0)
		return -__HUGE_VAL + __x; /* -inf and overflow exception.  */
	if (__hx < 0)
		return __LIBM_LOCAL_VALUE(zero) / __LIBM_LOCAL_VALUE(zero);
	__sign = 1;
	if (__n < 0) {
		__n  = -__n;
		__sign = 1 - ((__n & 1) << 1);
	}
	if (__n == 0)
		return __ieee754_y0(__x);
	if (__n == 1)
		return __sign * __ieee754_y1(__x);
	if (__ix == __INT32_C(0x7ff00000))
		return __LIBM_LOCAL_VALUE(zero);
	if (__ix >= __INT32_C(0x52D00000)) { /* x > 2**302 */
		/* (x >> n**2)
		 *      Jn(x) = cos(x-(2n+1)*pi/4)*sqrt(2/x*pi)
		 *      Yn(x) = sin(x-(2n+1)*pi/4)*sqrt(2/x*pi)
		 *      Let s=sin(x), c=cos(x),
		 *      xn=x-(2n+1)*pi/4, sqt2 = sqrt(2),then
		 *
		 *         n    sin(xn)*sqt2    cos(xn)*sqt2
		 *      ----------------------------------
		 *         0     s-c         c+s
		 *         1    -s-c        -c+s
		 *         2    -s+c        -c-s
		 *         3     s+c         c-s */
		__IEEE754_DOUBLE_TYPE__ __c, __s;
		__ieee754_sincos(__x, &__s, &__c);
		switch (__n & 3) {
		case 0:
			__temp = __s - __c;
			break;
		case 1:
			__temp = -__s - __c;
			break;
		case 2:
			__temp = -__s + __c;
			break;
		case 3:
			__temp = __s + __c;
			break;
		}
		__b = __LIBM_LOCAL_VALUE(invsqrtpi) * __temp / __ieee754_sqrt(__x);
	} else {
		__uint32_t __high;
		__a = __ieee754_y0(__x);
		__b = __ieee754_y1(__x);
		/* quit if b is -inf */
		__LIBM_GET_HIGH_WORD(__high, __b);
		for (__i = 1; __i < __n && __high != __UINT32_C(0xfff00000); __i++) {
			__temp = __b;
			__b    = ((__IEEE754_DOUBLE_TYPE__)(__i + __i) / __x) * __b - __a;
			__LIBM_GET_HIGH_WORD(__high, __b);
			__a = __temp;
		}
	}
	if (__sign > 0)
		return __b;
	return -__b;
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
#ifndef __libm_invsqrtpil_defined
#define __libm_invsqrtpil_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, invsqrtpil, __IEEE854_LONG_DOUBLE_C(5.6418958354775628694807945156077258584405e-1))
#endif /* !__libm_invsqrtpil_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(ynl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_ynl)(int __n, __IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __a, __b, __temp;
	__uint32_t __se, __i0, __i1;
	__int32_t __i, __ix;
	int __sign;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__ix = __se & IEEE854_LONG_DOUBLE_MAXEXP;
	/* if Y(n,NaN) is NaN */
	if ((__ix == IEEE854_LONG_DOUBLE_MAXEXP) && ((__i0 & __INT32_C(0x7fffffff)) != 0))
		return __x + __x;
	if ((__ix | __i0 | __i1) == 0)
		return -__HUGE_VALL + __x; /* -inf and overflow exception.  */
	if (__se & 0x8000)
		return __LIBM_LOCAL_VALUE(zerol) / (__LIBM_LOCAL_VALUE(zerol) * __x);
	__sign = 1;
	if (__n < 0) {
		__n  = -__n;
		__sign = 1 - ((__n & 1) << 1);
	}
	if (__n == 0)
		return (__ieee854_y0l(__x));
	if (__n == 1)
		return (__sign * __ieee854_y1l(__x));
	if (__ix == IEEE854_LONG_DOUBLE_MAXEXP)
		return __LIBM_LOCAL_VALUE(zerol);
	if (__ix >= 0x412D) { /* x > 2**302 */
		/* ??? See comment above on the possible futility of this.  */
		/* (x >> n**2)
		 *      Jn(x) = cos(x-(2n+1)*pi/4)*sqrt(2/x*pi)
		 *      Yn(x) = sin(x-(2n+1)*pi/4)*sqrt(2/x*pi)
		 *      Let s=sin(x), c=cos(x),
		 *          xn=x-(2n+1)*pi/4, sqt2 = sqrt(2),then
		 *
		 *             n    sin(xn)*sqt2    cos(xn)*sqt2
		 *          ----------------------------------
		 *             0     s-c             c+s
		 *             1    -s-c            -c+s
		 *             2    -s+c            -c-s
		 *             3     s+c             c-s */
		__IEEE854_LONG_DOUBLE_TYPE__ __s, __c;
		__ieee854_sincosl(__x, &__s, &__c);
		switch (__n & 3) {
		case 0:
			__temp = __s - __c;
			break;
		case 1:
			__temp = -__s - __c;
			break;
		case 2:
			__temp = -__s + __c;
			break;
		case 3:
			__temp = __s + __c;
			break;
		}
		__b = __LIBM_LOCAL_VALUE(invsqrtpil) * __temp / __ieee854_sqrtl(__x);
	} else {
		__a = __ieee854_y0l(__x);
		__b = __ieee854_y1l(__x);
		/* quit if b is -inf */
		__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __b);
		/* Use 0xffffffff since GET_LDOUBLE_WORDS sign-extends SE.  */
		for (__i = 1; __i < __n && __se != __UINT32_C(0xffffffff); __i++) {
			__temp = __b;
			__b    = ((__IEEE854_LONG_DOUBLE_TYPE__)(__i + __i) / __x) * __b - __a;
			__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __b);
			__a = __temp;
		}
	}
	if (__sign > 0)
		return __b;
	return -__b;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_YN_H */
