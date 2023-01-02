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
#ifndef _LIBM_SCALBN_H
#define _LIBM_SCALBN_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/limitcore.h> /* __INT_MAX__ */
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fdlibm.h>
#include <libm/copysign.h>

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
#ifndef __libm_two25f_defined
#define __libm_two25f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, two25f, __IEEE754_FLOAT_C(3.355443200e+07))   /* 0x4c000000 */
#endif /* !__libm_two25f_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, twom25f, __IEEE754_FLOAT_C(2.9802322388e-08)) /* 0x33000000 */
#ifndef __libm_hugef_defined
#define __libm_hugef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, hugef, __IEEE754_FLOAT_C(1.0e+30))
#endif /* !__libm_hugef_defined */
#ifndef __libm_tinyf_defined
#define __libm_tinyf_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, tinyf, __IEEE754_FLOAT_C(1.0e-30))
#endif /* !__libm_tinyf_defined */
__LIBM_LOCAL_DECLARE_END

#ifndef __LIBM_OVERFLOW_INT
#if __INT_MAX__ > 50000
#define __LIBM_OVERFLOW_INT 50000
#else /* __INT_MAX__ > 50000 */
#define __LIBM_OVERFLOW_INT 30000
#endif /* __INT_MAX__ <= 50000 */
#endif /* !__LIBM_OVERFLOW_INT */

__LIBM_LOCAL_FUNC(scalbnf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_scalbnf)(__IEEE754_FLOAT_TYPE__ __x, int __n) {
	__int32_t __k, __ix;
	__uint32_t __hx;
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	__hx = __ix & 0x7fffffff;
	__k  = __hx >> 23; /* extract exponent */
	if (__LIBM_FLT_UWORD_IS_ZERO(__hx))
		return __x;
	if (!__LIBM_FLT_UWORD_IS_FINITE(__hx))
		return __x + __x; /* NaN or Inf */
#ifndef _FLT_NO_DENORMALS
	if (__LIBM_FLT_UWORD_IS_SUBNORMAL(__hx)) {
		__x *= __LIBM_LOCAL_VALUE(two25f);
		__LIBM_GET_FLOAT_WORD(__ix, __x);
		__k = ((__ix & 0x7f800000) >> 23) - 25;
		if (__n < -50000)
			return __LIBM_LOCAL_VALUE(tinyf) * __x; /*underflow*/
	}
#endif /* !_FLT_NO_DENORMALS */
	__k = __k + __n;
	if (__k > __LIBM_FLT_LARGEST_EXP)
		return __LIBM_LOCAL_VALUE(hugef) * __ieee754_copysignf(__LIBM_LOCAL_VALUE(hugef), __x); /* overflow  */
	if (__k > 0) { /* normal result */
		__LIBM_SET_FLOAT_WORD(__x, (__ix & 0x807fffff) | (__k << 23));
		return __x;
	}
	if (__k < __LIBM_FLT_SMALLEST_EXP) {
		/* in case integer overflow in n+k */
		if (__n > __LIBM_OVERFLOW_INT) {
			return __LIBM_LOCAL_VALUE(hugef) * __ieee754_copysignf(__LIBM_LOCAL_VALUE(hugef), __x); /*overflow*/
		} else {
			return __LIBM_LOCAL_VALUE(tinyf) * __ieee754_copysignf(__LIBM_LOCAL_VALUE(tinyf), __x); /*underflow*/
		}
	}
	__k += 25; /* subnormal result */
	__LIBM_SET_FLOAT_WORD(__x, (__ix & 0x807fffff) | (__k << 23));
	return __x * __LIBM_LOCAL_VALUE(twom25f);
}

__LIBM_LOCAL_FUNC(scalblnf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_scalblnf)(__IEEE754_FLOAT_TYPE__ __x, long int __n) {
	__int32_t __k, __ix;
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	__k = (__ix & 0x7f800000) >> 23; /* extract exponent */
	if (__k == 0) {                /* 0 or subnormal x */
		if ((__ix & 0x7fffffff) == 0)
			return __x; /* +-0 */
		__x *= __LIBM_LOCAL_VALUE(two25f);
		__LIBM_GET_FLOAT_WORD(__ix, __x);
		__k = ((__ix & 0x7f800000) >> 23) - 25;
	}
	if (__k == 0xff)
		return __x + __x; /* NaN or Inf */
	__k = __k + __n;
	if (__n > 50000 || __k > 0xfe)
		return __LIBM_LOCAL_VALUE(hugef) * __ieee754_copysignf(__LIBM_LOCAL_VALUE(hugef), __x); /* overflow  */
	if (__n < -50000)
		return __LIBM_LOCAL_VALUE(tinyf) * __ieee754_copysignf(__LIBM_LOCAL_VALUE(tinyf), __x); /*underflow*/
	if (__k > 0) {
		/* normal result */
		__LIBM_SET_FLOAT_WORD(__x, (__ix & 0x807fffff) | (__k << 23));
		return __x;
	}
	if (__k <= -25)
		return __LIBM_LOCAL_VALUE(tinyf) * __ieee754_copysignf(__LIBM_LOCAL_VALUE(tinyf), __x); /*underflow*/
	__k += 25; /* subnormal result */
	__LIBM_SET_FLOAT_WORD(__x, (__ix & 0x807fffff) | (__k << 23));
	return __x * __LIBM_LOCAL_VALUE(twom25f);
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
#ifndef __libm_two54_defined
#define __libm_two54_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, two54, __IEEE754_DOUBLE_C(1.80143985094819840000e+16)) /* 0x43500000, 0x00000000 */
#endif /* !__libm_two54_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, twom54, __IEEE754_DOUBLE_C(5.55111512312578270212e-17)) /* 0x3C900000, 0x00000000 */
#ifndef __libm_huge_defined
#define __libm_huge_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, huge, __IEEE754_DOUBLE_C(1.0e+300))
#endif /* !__libm_huge_defined */
#ifndef __libm_tiny_defined
#define __libm_tiny_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, tiny, __IEEE754_DOUBLE_C(1.0e-300))
#endif /* !__libm_tiny_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(scalbn) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_scalbn)(__IEEE754_DOUBLE_TYPE__ __x, int __n) {
	__int32_t __k, __hx, __lx;
	__LIBM_EXTRACT_WORDS(__hx, __lx, __x);
	__k = (__hx & 0x7ff00000) >> 20; /* extract exponent */
	if (__k == 0) { /* 0 or subnormal x */
		if ((__lx | (__hx & 0x7fffffff)) == 0)
			return __x; /* +-0 */
		__x *= __LIBM_LOCAL_VALUE(two54);
		__LIBM_GET_HIGH_WORD(__hx, __x);
		__k = ((__hx & 0x7ff00000) >> 20) - 54;
		if (__n < -50000)
			return __LIBM_LOCAL_VALUE(tiny) * __x; /*underflow*/
	}
	if (__k == 0x7ff)
		return __x + __x; /* NaN or Inf */
	__k = __k + __n;
	if (__k > 0x7fe)
		return __LIBM_LOCAL_VALUE(huge) * __ieee754_copysign(__LIBM_LOCAL_VALUE(huge), __x); /* overflow  */
	if (__k > 0) { /* normal result */
		__LIBM_SET_HIGH_WORD(__x, (__hx & 0x800fffff) | (__k << 20));
		return __x;
	}
	if (__k <= -54) {
		if (__n > 50000) { /* in case integer overflow in n+k */
			return __LIBM_LOCAL_VALUE(huge) * __ieee754_copysign(__LIBM_LOCAL_VALUE(huge), __x); /*overflow*/
		} else {
			return __LIBM_LOCAL_VALUE(tiny) * __ieee754_copysign(__LIBM_LOCAL_VALUE(tiny), __x); /*underflow*/
		}
	}
	__k += 54; /* subnormal result */
	__LIBM_SET_HIGH_WORD(__x, (__hx & 0x800fffff) | (__k << 20));
	return __x * __LIBM_LOCAL_VALUE(twom54);
}

__LIBM_LOCAL_FUNC(scalbln) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_scalbln)(__IEEE754_DOUBLE_TYPE__ __x, long int __n) {
	__int32_t __k, __hx, __lx;
	__LIBM_EXTRACT_WORDS(__hx, __lx, __x);
	__k = (__hx & 0x7ff00000) >> 20; /* extract exponent */
	if (__k == 0) { /* 0 or subnormal x */
		if ((__lx | (__hx & 0x7fffffff)) == 0)
			return __x; /* +-0 */
		__x *= __LIBM_LOCAL_VALUE(two54);
		__LIBM_GET_HIGH_WORD(__hx, __x);
		__k = ((__hx & 0x7ff00000) >> 20) - 54;
	}
	if (__k == 0x7ff)
		return __x + __x; /* NaN or Inf */
	__k = __k + __n;
	if (__n > 50000 || __k > 0x7fe)
		return __LIBM_LOCAL_VALUE(huge) * __ieee754_copysign(__LIBM_LOCAL_VALUE(huge), __x); /* overflow  */
	if (__n < -50000)
		return __LIBM_LOCAL_VALUE(tiny) * __ieee754_copysign(__LIBM_LOCAL_VALUE(tiny), __x); /*underflow*/
	if (__k > 0) { /* normal result */
		__LIBM_SET_HIGH_WORD(__x, (__hx & 0x800fffff) | (__k << 20));
		return __x;
	}
	if (__k <= -54)
		return __LIBM_LOCAL_VALUE(tiny) * __ieee754_copysign(__LIBM_LOCAL_VALUE(tiny), __x); /*underflow*/
	__k += 54; /* subnormal result */
	__LIBM_SET_HIGH_WORD(__x, (__hx & 0x800fffff) | (__k << 20));
	return __x * __LIBM_LOCAL_VALUE(twom54);
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
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, two64l, __IEEE854_LONG_DOUBLE_C(1.8446744073709551616e19))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, twom64l, __IEEE854_LONG_DOUBLE_C(5.421010862427522170037e-20))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, hugeval4900l, __IEEE854_LONG_DOUBLE_C(1.0e+4900))
#ifndef __libm_tinyl_defined
#define __libm_tinyl_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, tinyl, __IEEE854_LONG_DOUBLE_C(1.0e-4900))
#endif /* !__libm_tinyl_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(scalbnl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_scalbnl)(__IEEE854_LONG_DOUBLE_TYPE__ __x, int __n) {
	__int32_t __k, __es, __hx, __lx;
	__LIBM_GET_LDOUBLE_WORDS(__es, __hx, __lx, __x);
	__k = __es & IEEE854_LONG_DOUBLE_MAXEXP; /* extract exponent */
	if (__k == 0) { /* 0 or subnormal x */
		if ((__lx | (__hx & __UINT32_C(0x7fffffff))) == 0)
			return __x; /* +-0 */
		__x *= __LIBM_LOCAL_VALUE(two64l);
		__LIBM_GET_LDOUBLE_EXP(__hx, __x);
		__k = (__hx & IEEE854_LONG_DOUBLE_MAXEXP) - 64;
	}
	if (__k == IEEE854_LONG_DOUBLE_MAXEXP)
		return __x + __x; /* NaN or Inf */
	if ((__int32_t)__n < -__INT32_C(30000))
		return __LIBM_LOCAL_VALUE(tinyl) * __ieee854_copysignl(__LIBM_LOCAL_VALUE(tinyl), __x);
	if ((__int32_t)__n > __INT32_C(30000) || (__k + __n) > 0x7ffe)
		return __LIBM_LOCAL_VALUE(hugeval4900l) * __ieee854_copysignl(__LIBM_LOCAL_VALUE(hugeval4900l), __x); /* overflow  */
	/* Now k and n are bounded we know that k = k+n does not
	   overflow.  */
	__k = __k + __n;
	if (__k > 0) { /* normal result */
		__LIBM_SET_LDOUBLE_EXP(__x, (__es & 0x8000) | __k);
		return __x;
	}
	if (__k <= -64)
		return __LIBM_LOCAL_VALUE(tinyl) * __ieee854_copysignl(__LIBM_LOCAL_VALUE(tinyl), __x); /*underflow */
	__k += 64;                              /* subnormal result */
	__LIBM_SET_LDOUBLE_EXP(__x, (__es & 0x8000) | __k);
	return __x * __LIBM_LOCAL_VALUE(twom64l);
}

__LIBM_LOCAL_FUNC(scalblnl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_scalblnl)(__IEEE854_LONG_DOUBLE_TYPE__ x, long int n) {
	__int32_t k, es, hx, lx;
	__LIBM_GET_LDOUBLE_WORDS(es, hx, lx, x);
	k = es & IEEE854_LONG_DOUBLE_MAXEXP; /* extract exponent */
	if (k == 0) {                        /* 0 or subnormal x */
		if ((lx | (hx & __UINT32_C(0x7fffffff))) == 0)
			return x; /* +-0 */
		x *= __LIBM_LOCAL_VALUE(two64l);
		__LIBM_GET_LDOUBLE_EXP(hx, x);
		k = (hx & IEEE854_LONG_DOUBLE_MAXEXP) - 64;
	}
	if (k == IEEE854_LONG_DOUBLE_MAXEXP)
		return x + x; /* NaN or Inf */
	if (n < __INT32_C(-50000))
		return __LIBM_LOCAL_VALUE(tiny) * __ieee854_copysignl(__LIBM_LOCAL_VALUE(tiny), x);
	if (n > __INT32_C(50000) || k + n > 0x7ffe)
		return __LIBM_LOCAL_VALUE(hugeval4900l) * __ieee854_copysignl(__LIBM_LOCAL_VALUE(hugeval4900l), x); /* overflow  */
	/* Now k and n are bounded we know that k = k+n does not
	   overflow.  */
	k = k + n;
	if (k > 0) { /* normal result */
		__LIBM_SET_LDOUBLE_EXP(x, (es & 0x8000) | k);
		return x;
	}
	if (k <= -64)
		return __LIBM_LOCAL_VALUE(tinyl) * __ieee854_copysignl(__LIBM_LOCAL_VALUE(tinyl), x); /* underflow */
	k += 64; /* subnormal result */
	__LIBM_SET_LDOUBLE_EXP(x, (es & 0x8000) | k);
	return x * __LIBM_LOCAL_VALUE(twom64l);
}

#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_SCALBN_H */
