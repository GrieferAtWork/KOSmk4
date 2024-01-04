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
#ifndef _LIBM_JN_H
#define _LIBM_JN_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/math-constants.h> /* TODO: Replace uses below with __IEEE754_ constants */
#include <bits/types.h>

#include <libm/fabs.h>
#include <libm/fdlibm.h>
#include <libm/j0.h>
#include <libm/j1.h>
#include <libm/log.h>

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
#ifndef __libm_onef_defined
#define __libm_onef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0000000000e+00)) /* 0x3F800000 */
#endif /* !__libm_onef_defined */
#ifndef __libm_twof_defined
#define __libm_twof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, twof, __IEEE754_FLOAT_C(2.0))
#endif /* !__libm_twof_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(jnf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_jnf)(int __n, __IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __i, __hx, __ix;
	__IEEE754_FLOAT_TYPE__ __a, __b, __temp, __di;
	__IEEE754_FLOAT_TYPE__ __z, __w;
	int __sgn;
	/* J(-n,x) = (-1)^n * J(n, x), J(n, -x) = (-1)^n * J(n, x)
	 * Thus, J(-n,x) = J(n,-x) */
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __INT32_C(0x7fffffff) & __hx;
	/* if J(n,NaN) is NaN */
	if (__LIBM_FLT_UWORD_IS_NAN(__ix))
		return __x + __x;
	if (__n < 0) {
		__n = -__n;
		__x = -__x;
		__hx ^= __INT32_C(0x80000000);
	}
	if (__n == 0)
		return (__ieee754_j0f(__x));
	if (__n == 1)
		return (__ieee754_j1f(__x));
	__sgn = (int)((__n & 1) & (__hx >> 31)); /* even n -- 0, odd n -- sign(x) */
	__x   = __ieee754_fabsf(__x);
	if (__LIBM_FLT_UWORD_IS_ZERO(__ix) || __LIBM_FLT_UWORD_IS_INFINITE(__ix)) {
		__b = __LIBM_LOCAL_VALUE(zerof);
	} else if ((__IEEE754_FLOAT_TYPE__)__n <= __x) {
		/* Safe to use J(n+1,x)=2n/x *J(n,x)-J(n-1,x) */
		__a = __ieee754_j0f(__x);
		__b = __ieee754_j1f(__x);
		for (__i = 1; __i < __n; ++__i) {
			__temp = __b;
			__b    = __b * ((__IEEE754_FLOAT_TYPE__)(__i + __i) / __x) - __a; /* avoid underflow */
			__a    = __temp;
		}
	} else {
		if (__ix < __INT32_C(0x30800000)) { /* x < 2**-29 */
			/* x is tiny, return the first Taylor expansion of J(n,x)
			 * J(n,x) = 1/n!*(x/2)^n - ... */
			if (__n > 33) { /* underflow */
				__b = __LIBM_LOCAL_VALUE(zerof);
			} else {
				__temp = __x * 0.5f;
				__b    = __temp;
				for (__a = __LIBM_LOCAL_VALUE(onef), __i = 2; __i <= __n; ++__i) {
					__a *= (__IEEE754_FLOAT_TYPE__)__i; /* a = n! */
					__b *= __temp;                      /* b = (x/2)^n */
				}
				__b = __b / __a;
			}
		} else {
			/* use backward recurrence */
			/*          x      x^2      x^2
			 *  J(n,x)/J(n-1,x) =  ----   ------   ------   .....
			 *          2n  - 2(n+1) - 2(n+2)
			 *
			 *          1      1        1
			 *  (for large x)   =  ----  ------   ------   .....
			 *          2n   2(n+1)   2(n+2)
			 *          -- - ------ - ------ -
			 *           x     x         x
			 *
			 * Let w = 2n/x and h=2/x, then the above quotient
			 * is equal to the continued fraction:
			 *          1
			 *  = -----------------------
			 *             1
			 *     w - -----------------
			 *            1
			 *          w+h - ---------
			 *             w+2h - ...
			 *
			 * To determine how many terms needed, let
			 * Q(0) = w, Q(1) = w(w+h) - 1,
			 * Q(k)  =  (w+k*h)*Q(k-1)  -  Q(k-2),
			 * When  Q(k)  > 1e4  good  for single
			 * When  Q(k)  > 1e9  good  for double
			 * When Q(k) > 1e17 good for quadruple */
			/* determine k */
			__IEEE754_FLOAT_TYPE__ __t, __v;
			__IEEE754_FLOAT_TYPE__ __q0, __q1, __h, __tmp;
			__int32_t __k, __m;
			__w = (__n + __n) / (__IEEE754_FLOAT_TYPE__)__x;
			__h   = __IEEE754_FLOAT_C(2.0) / __x;
			__q0  = __w;
			__z = __w + __h;
			__q1  = __w * __z - __IEEE754_FLOAT_C(1.0);
			__k   = 1;
			while (__q1 < __IEEE754_FLOAT_C(1.0e9)) {
				__k += 1;
				__z += __h;
				__tmp = __z * __q1 - __q0;
				__q0  = __q1;
				__q1  = __tmp;
			}
			__m = __n + __n;
			for (__t = __LIBM_LOCAL_VALUE(zerof), __i = 2 * (__n + __k); __i >= __m; __i -= 2)
				__t = __LIBM_LOCAL_VALUE(onef) / (__i / __x - __t);
			__a = __t;
			__b = __LIBM_LOCAL_VALUE(onef);
			/* estimate log((2/x)^n*n!) = n*log(2/x)+n*ln(n)
			 * Hence, if n*(log(2n/x)) > ...
			 * single 8.8722839355e+01
			 * double 7.09782712893383973096e+02
			 * __IEEE854_LONG_DOUBLE_TYPE__ 1.1356523406294143949491931077970765006170e+04
			 * then recurrent value may overflow and the result is
			 * likely underflow to zero */
			__tmp = __n;
			__v   = __LIBM_LOCAL_VALUE(twof) / __x;
			__tmp = __tmp * __ieee754_logf(__ieee754_fabsf(__v * __tmp));
			if (__tmp < 8.8721679688e+01f) {
				for (__i = __n - 1, __di = (__IEEE754_FLOAT_TYPE__)(__i + __i); __i > 0; --__i) {
					__temp = __b;
					__b *= __di;
					__b = __b / __x - __a;
					__a = __temp;
					__di -= __LIBM_LOCAL_VALUE(twof);
				}
			} else {
				for (__i = __n - 1, __di = (__IEEE754_FLOAT_TYPE__)(__i + __i); __i > 0; --__i) {
					__temp = __b;
					__b *= __di;
					__b = __b / __x - __a;
					__a = __temp;
					__di -= __LIBM_LOCAL_VALUE(twof);
					/* scale b to avoid spurious overflow */
					if (__b > __IEEE754_FLOAT_C(1e10)) {
						__a /= __b;
						__t /= __b;
						__b = __LIBM_LOCAL_VALUE(onef);
					}
				}
			}
			/* j0() and j1() suffer enormous  loss of precision at  and
			 * near zero; however, we know that their zero points never
			 * coincide, so just choose the one further away from zero. */
			__z = __ieee754_j0f(__x);
			__w = __ieee754_j1f(__x);
			if (__ieee754_fabsf(__z) >= __ieee754_fabsf(__w)) {
				__b = (__t * __z / __b);
			} else {
				__b = (__t * __w / __a);
			}
		}
	}
	if (__sgn)
		return -__b;
	return __b;
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
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.00000000000000000000e+00)) /* 0x3FF00000, 0x00000000 */
#endif /* !__libm_one_defined */
#ifndef __libm_invsqrtpi_defined
#define __libm_invsqrtpi_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, invsqrtpi, __IEEE754_DOUBLE_C(5.64189583547756279280e-01)) /* 0x3FE20DD7, 0x50429B6D */
#endif /* !__libm_invsqrtpi_defined */
#ifndef __libm_two_defined
#define __libm_two_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, two, __IEEE754_DOUBLE_C(2.0))
#endif /* !__libm_two_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(jn) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_jn)(int __n, __IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __a, __b, __temp, __di;
	__IEEE754_DOUBLE_TYPE__ __z, __w;
	__int32_t __i, __hx, __ix, __lx;
	int __sgn;

	/* J(-n,x) = (-1)^n * J(n, x), J(n, -x) = (-1)^n * J(n, x)
	 * Thus, J(-n,x) = J(n,-x) */
	__LIBM_GET_DOUBLE_WORDS(__hx, __lx, __x);
	__ix = __INT32_C(0x7fffffff) & __hx;

	/* if J(n,NaN) is NaN */
	if ((__ix | (((__uint32_t)(__lx | -__lx)) >> 31)) > __INT32_C(0x7ff00000))
		return __x + __x;
	if (__n < 0) {
		__n = -__n;
		__x = -__x;
		__hx ^= __INT32_C(0x80000000);
	}
	if (__n == 0)
		return (__ieee754_j0(__x));
	if (__n == 1)
		return (__ieee754_j1(__x));
	__sgn = (int)((__n & 1) & (__hx >> 31)); /* even n -- 0, odd n -- sign(x) */
	__x = __ieee754_fabs(__x);
	if ((__ix | __lx) == 0 || __ix >= __INT32_C(0x7ff00000)) { /* if x is 0 or inf */
		__b = __LIBM_LOCAL_VALUE(zero);
	} else if ((__IEEE754_DOUBLE_TYPE__)__n <= __x) {
		/* Safe to use J(n+1,x)=2n/x *J(n,x)-J(n-1,x) */
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
			__IEEE754_DOUBLE_TYPE__ __s;
			__IEEE754_DOUBLE_TYPE__ __c;
			__ieee754_sincos(__x, &__s, &__c);
			switch (__n & 3) {
			case 0:
				__temp = __c + __s;
				break;
			case 1:
				__temp = -__c + __s;
				break;
			case 2:
				__temp = -__c - __s;
				break;
			case 3:
				__temp = __c - __s;
				break;
			}
			__b = __LIBM_LOCAL_VALUE(invsqrtpi) * __temp / __ieee754_sqrt(__x);
		} else {
			__a = __ieee754_j0(__x);
			__b = __ieee754_j1(__x);
			for (__i = 1; __i < __n; __i++) {
				__temp = __b;
				__b    = __b * ((__IEEE754_DOUBLE_TYPE__)(__i + __i) / __x) - __a; /* avoid underflow */
				__a    = __temp;
			}
		}
	} else {
		if (__ix < __INT32_C(0x3e100000)) { /* x < 2**-29 */
			/* x is tiny, return the first Taylor expansion of J(n,x)
			 * J(n,x) = 1/n!*(x/2)^n - ... */
			if (__n > 33) { /* underflow */
				__b = __LIBM_LOCAL_VALUE(zero);
			} else {
				__temp = __x * __IEEE754_DOUBLE_C(0.5);
				__b    = __temp;
				for (__a = __LIBM_LOCAL_VALUE(one), __i = 2; __i <= __n; ++__i) {
					__a *= (__IEEE754_DOUBLE_TYPE__)__i; /* a = n! */
					__b *= __temp;                       /* b = (x/2)^n */
				}
				__b = __b / __a;
			}
		} else {
			/* use backward recurrence */
			/*          x      x^2      x^2
			 *  J(n,x)/J(n-1,x) =  ----   ------   ------   .....
			 *          2n  - 2(n+1) - 2(n+2)
			 *
			 *          1      1        1
			 *  (for large x)   =  ----  ------   ------   .....
			 *          2n   2(n+1)   2(n+2)
			 *          -- - ------ - ------ -
			 *           x     x         x
			 *
			 * Let w = 2n/x and h=2/x, then the above quotient
			 * is equal to the continued fraction:
			 *          1
			 *  = -----------------------
			 *             1
			 *     w - -----------------
			 *            1
			 *          w+h - ---------
			 *             w+2h - ...
			 *
			 * To determine how many terms needed, let
			 * Q(0) = w, Q(1) = w(w+h) - 1,
			 * Q(k)  =  (w+k*h)*Q(k-1)  -  Q(k-2),
			 * When  Q(k)  > 1e4  good  for single
			 * When  Q(k)  > 1e9  good  for double
			 * When Q(k) > 1e17 good for quadruple */
			/* determine k */
			__IEEE754_DOUBLE_TYPE__ __t, __v;
			__IEEE754_DOUBLE_TYPE__ __q0, __q1, __h, __tmp;
			__int32_t __k, __m;
			__w  = (__n + __n) / (__IEEE754_DOUBLE_TYPE__)__x;
			__h  = __IEEE754_DOUBLE_C(2.0) / (__IEEE754_DOUBLE_TYPE__)__x;
			__q0 = __w;
			__z  = __w + __h;
			__q1 = __w * __z - __IEEE754_DOUBLE_C(1.0);
			__k  = 1;
			while (__q1 < __IEEE754_DOUBLE_C(1.0e9)) {
				__k += 1;
				__z += __h;
				__tmp = __z * __q1 - __q0;
				__q0  = __q1;
				__q1  = __tmp;
			}
			__m = __n + __n;
			for (__t = __LIBM_LOCAL_VALUE(zero), __i = 2 * (__n + __k); __i >= __m; __i -= 2)
				__t = __LIBM_LOCAL_VALUE(one) / (__i / __x - __t);
			__a = __t;
			__b = __LIBM_LOCAL_VALUE(one);
			/* estimate log((2/x)^n*n!) = n*log(2/x)+n*ln(n)
			 * Hence, if n*(log(2n/x)) > ...
			 * single 8.8722839355e+01
			 * double 7.09782712893383973096e+02
			 * long double 1.1356523406294143949491931077970765006170e+04
			 * then recurrent  value  may  overflow  and  the  result  is
			 * likely underflow to zero */
			__tmp = __n;
			__v   = __LIBM_LOCAL_VALUE(two) / __x;
			__tmp = __tmp * __ieee754_log(__ieee754_fabs(__v * __tmp));
			if (__tmp < __IEEE754_DOUBLE_C(7.09782712893383973096e+02)) {
				for (__i = __n - 1, __di = (__IEEE754_DOUBLE_TYPE__)(__i + __i); __i > 0; --__i) {
					__temp = __b;
					__b *= __di;
					__b = __b / __x - __a;
					__a = __temp;
					__di -= __LIBM_LOCAL_VALUE(two);
				}
			} else {
				for (__i = __n - 1, __di = (__IEEE754_DOUBLE_TYPE__)(__i + __i); __i > 0; --__i) {
					__temp = __b;
					__b *= __di;
					__b = __b / __x - __a;
					__a = __temp;
					__di -= __LIBM_LOCAL_VALUE(two);
					/* scale b to avoid spurious overflow */
					if (__b > __IEEE754_DOUBLE_C(1e100)) {
						__a /= __b;
						__t /= __b;
						__b = __LIBM_LOCAL_VALUE(one);
					}
				}
			}
			/* j0() and j1() suffer enormous  loss of precision at  and
			 * near zero; however, we know that their zero points never
			 * coincide, so just choose the one further away from zero. */
			__z = __ieee754_j0(__x);
			__w = __ieee754_j1(__x);
			if (__ieee754_fabs(__z) >= __ieee754_fabs(__w)) {
				__b = (__t * __z / __b);
			} else {
				__b = (__t * __w / __a);
			}
		}
	}
	if (__sgn)
		return -__b;
	return __b;
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
#ifndef __libm_onel_defined
#define __libm_onel_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, onel, __IEEE854_LONG_DOUBLE_C(1.0))
#endif /* !__libm_onel_defined */
#ifndef __libm_invsqrtpil_defined
#define __libm_invsqrtpil_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, invsqrtpil, __IEEE854_LONG_DOUBLE_C(5.6418958354775628694807945156077258584405e-1))
#endif /* !__libm_invsqrtpil_defined */
#ifndef __libm_twol_defined
#define __libm_twol_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, twol, __IEEE854_LONG_DOUBLE_C(2.0))
#endif /* !__libm_twol_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(jnl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_jnl)(int __n, __IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __a, __b, __temp, __di;
	__IEEE854_LONG_DOUBLE_TYPE__ __z, __w;
	__uint32_t __se, __i0, __i1;
	__int32_t __i, __ix;
	int sgn;
	/* J(-n,x) = (-1)^n * J(n, x), J(n, -x) = (-1)^n * J(n, x)
	 * Thus, J(-n,x) = J(n,-x) */
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__ix = __se & 0x7fff;
	/* if J(n,NaN) is NaN */
	if ((__ix == 0x7fff) && ((__i0 & __INT32_C(0x7fffffff)) != 0))
		return __x + __x;
	if (__n < 0) {
		__n = -__n;
		__x = -__x;
		__se ^= 0x8000;
	}
	if (__n == 0)
		return (__ieee854_j0l(__x));
	if (__n == 1)
		return (__ieee854_j1l(__x));
	sgn = (int)((__n & 1) & (__se >> 15));			/* even n -- 0, odd n -- sign(x) */
	__x = __ieee854_fabsl(__x);
	if ((__ix | __i0 | __i1) == 0 || __ix >= 0x7fff) {
		/* if x is 0 or inf */
		__b = __LIBM_LOCAL_VALUE(zerol);
	} else if ((__IEEE854_LONG_DOUBLE_TYPE__)__n <= __x) {
		/* Safe to use J(n+1,x)=2n/x *J(n,x)-J(n-1,x) */
		if (__ix >= 0x412D) { /* x > 2**302 */
			/* ??? This might be a futile gesture.
			 * If x exceeds X_TLOSS anyway, the wrapper function
			 * will set the result to zero. */
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
			 *             3     s+c             c-s
			 */
			__IEEE854_LONG_DOUBLE_TYPE__ __s;
			__IEEE854_LONG_DOUBLE_TYPE__ __c;
			__ieee854_sincosl(__x, &__s, &__c);
			switch (__n & 3) {
			case 0:
				__temp = __c + __s;
				break;
			case 1:
				__temp = -__c + __s;
				break;
			case 2:
				__temp = -__c - __s;
				break;
			case 3:
				__temp = __c - __s;
				break;
			}
			__b = __LIBM_LOCAL_VALUE(invsqrtpil) * __temp / __ieee854_sqrtl(__x);
		} else {
			__a = __ieee854_j0l(__x);
			__b = __ieee854_j1l(__x);
			for (__i = 1; __i < __n; __i++) {
				__temp = __b;
				__b    = __b * ((__IEEE854_LONG_DOUBLE_TYPE__)(__i + __i) / __x) - __a; /* avoid underflow */
				__a    = __temp;
			}
		}
	} else {
		if (__ix < 0x3fde) { /* x < 2**-33 */
			/* x is tiny, return the first Taylor expansion of J(n,x)
			 * J(n,x) = 1/n!*(x/2)^n - ... */
			if (__n >= 400) { /* underflow, result < 10^-4952 */
				__b = __LIBM_LOCAL_VALUE(zerol);
			} else {
				__temp = __x * __IEEE854_LONG_DOUBLE_C(0.5);
				__b    = __temp;
				for (__a = __LIBM_LOCAL_VALUE(onel), __i = 2; __i <= __n; ++__i) {
					__a *= (__IEEE854_LONG_DOUBLE_TYPE__)__i; /* a = n! */
					__b *= __temp;                            /* b = (x/2)^n */
				}
				__b = __b / __a;
			}
		} else {
			/* use backward recurrence */
			/*                      x      x^2      x^2
			 *  J(n,x)/J(n-1,x) =  ----   ------   ------   .....
			 *                      2n  - 2(n+1) - 2(n+2)
			 *
			 *                      1      1        1
			 *  (for large x)   =  ----  ------   ------   .....
			 *                      2n   2(n+1)   2(n+2)
			 *                      -- - ------ - ------ -
			 *                       x     x         x
			 *
			 * Let w = 2n/x and h=2/x, then the above quotient
			 * is equal to the continued fraction:
			 *                  1
			 *      = -----------------------
			 *                     1
			 *         w - -----------------
			 *                        1
			 *              w+h - ---------
			 *                     w+2h - ...
			 *
			 * To determine how many terms needed, let
			 * Q(0) = w, Q(1) = w(w+h) - 1,
			 * Q(k) = (w+k*h)*Q(k-1) - Q(k-2),
			 * When Q(k) > 1e4      good for single
			 * When Q(k) > 1e9      good for double
			 * When Q(k) > 1e17     good for quadruple */
			/* determine k */
			__IEEE854_LONG_DOUBLE_TYPE__ __t, __v;
			__IEEE854_LONG_DOUBLE_TYPE__ __q0, __q1, __h, __tmp;
			__int32_t __k, __m;
			__w = (__n + __n) / (__IEEE854_LONG_DOUBLE_TYPE__)__x;
			__h   = __IEEE854_LONG_DOUBLE_C(2.0) / (__IEEE854_LONG_DOUBLE_TYPE__)__x;
			__q0  = __w;
			__z = __w + __h;
			__q1  = __w * __z - __IEEE854_LONG_DOUBLE_C(1.0);
			__k   = 1;
			while (__q1 < __IEEE854_LONG_DOUBLE_C(1.0e11)) {
				__k += 1;
				__z += __h;
				__tmp = __z * __q1 - __q0;
				__q0  = __q1;
				__q1  = __tmp;
			}
			__m = __n + __n;
			for (__t = __LIBM_LOCAL_VALUE(zerol), __i = 2 * (__n + __k); __i >= __m; __i -= 2)
				__t = __LIBM_LOCAL_VALUE(onel) / (__i / __x - __t);
			__a = __t;
			__b = __LIBM_LOCAL_VALUE(onel);
			/* estimate log((2/x)^n*n!) = n*log(2/x)+n*ln(n)
			 * Hence, if n*(log(2n/x)) > ...
			 * single 8.8722839355e+01
			 * double 7.09782712893383973096e+02
			 * long double 1.1356523406294143949491931077970765006170e+04
			 * then recurrent  value  may  overflow  and  the  result  is
			 * likely underflow to zero */
			__tmp = __n;
			__v   = __LIBM_LOCAL_VALUE(twol) / __x;
			__tmp = __tmp * __ieee854_logl(__ieee854_fabsl(__v * __tmp));
			if (__tmp < __IEEE854_LONG_DOUBLE_C(1.1356523406294143949491931077970765006170e+04)) {
				for (__i = __n - 1, __di = (__IEEE854_LONG_DOUBLE_TYPE__)(__i + __i); __i > 0; __i--) {
					__temp = __b;
					__b *= __di;
					__b = __b / __x - __a;
					__a = __temp;
					__di -= __LIBM_LOCAL_VALUE(twol);
				}
			} else {
				for (__i = __n - 1, __di = (__IEEE854_LONG_DOUBLE_TYPE__)(__i + __i); __i > 0; __i--) {
					__temp = __b;
					__b *= __di;
					__b = __b / __x - __a;
					__a = __temp;
					__di -= __LIBM_LOCAL_VALUE(twol);
					/* scale b to avoid spurious overflow */
					if (__b > __IEEE854_LONG_DOUBLE_C(1e100)) {
						__a /= __b;
						__t /= __b;
						__b = __LIBM_LOCAL_VALUE(onel);
					}
				}
			}
			/* j0() and j1() suffer enormous  loss of precision at  and
			 * near zero; however, we know that their zero points never
			 * coincide, so just choose the one further away from zero. */
			__z = __ieee854_j0l(__x);
			__w = __ieee854_j1l(__x);
			if (__ieee854_fabsl(__z) >= __ieee854_fabsl(__w)) {
				__b = (__t * __z / __b);
			} else {
				__b = (__t * __w / __a);
			}
		}
	}
	if (sgn)
		return -__b;
	return __b;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_JN_H */
