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
#ifndef _LIBM_TANH_H
#define _LIBM_TANH_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/expm1.h>
#include <libm/fabs.h>
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
#ifndef __libm_onef_defined
#define __libm_onef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0000000000e+00)) /* 0x3F800000 */
#endif /* !__libm_onef_defined */
#ifndef __libm_twof_defined
#define __libm_twof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, twof, __IEEE754_FLOAT_C(2.0))
#endif /* !__libm_twof_defined */
#ifndef __libm_tinyf_defined
#define __libm_tinyf_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, tinyf, __IEEE754_FLOAT_C(1.0e-30))
#endif /* !__libm_tinyf_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(tanhf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_tanhf)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __t, __z;
	__int32_t __jx, __ix;
	__LIBM_GET_FLOAT_WORD(__jx, __x);
	__ix = __jx & __INT32_C(0x7fffffff);

	/* x is INF or NaN */
	if (!__LIBM_FLT_UWORD_IS_FINITE(__ix)) {
		if (__jx >= 0) {
			return __LIBM_LOCAL_VALUE(onef) / __x + __LIBM_LOCAL_VALUE(onef); /* tanh(+-inf)=+-1 */
		} else {
			return __LIBM_LOCAL_VALUE(onef) / __x - __LIBM_LOCAL_VALUE(onef); /* tanh(NaN) = NaN */
		}
	}

	/* |x| < 22 */
	if (__ix < __INT32_C(0x41b00000)) { /* |x|<22 */
		if (__ix == 0)
			return __x;                                    /* x == +-0 */
		if (__ix < __INT32_C(0x24000000))                  /* |x|<2**-55 */
			return __x * (__LIBM_LOCAL_VALUE(onef) + __x); /* tanh(small) = small */
		if (__ix >= __INT32_C(0x3f800000)) {               /* |x|>=1  */
			__t = __ieee754_expm1f(__LIBM_LOCAL_VALUE(twof) * __ieee754_fabsf(__x));
			__z = __LIBM_LOCAL_VALUE(onef) - __LIBM_LOCAL_VALUE(twof) / (__t + __LIBM_LOCAL_VALUE(twof));
		} else {
			__t = __ieee754_expm1f(-__LIBM_LOCAL_VALUE(twof) * __ieee754_fabsf(__x));
			__z = -__t / (__t + __LIBM_LOCAL_VALUE(twof));
		}
		/* |x| > 22, return +-1 */
	} else {
		__z = __LIBM_LOCAL_VALUE(onef) - __LIBM_LOCAL_VALUE(tinyf); /* raised inexact flag */
	}
	return (__jx >= 0) ? __z : -__z;
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
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.00000000000000000000e+00)) /* 0x3FF00000, 0x00000000 */
#endif /* !__libm_one_defined */
#ifndef __libm_two_defined
#define __libm_two_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, two, __IEEE754_DOUBLE_C(2.0))
#endif /* !__libm_two_defined */
#ifndef __libm_tiny_defined
#define __libm_tiny_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, tiny, __IEEE754_DOUBLE_C(1.0e-300))
#endif /* !__libm_tiny_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(tanh) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_tanh)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __t, __z;
	__int32_t __jx, __ix, __lx;

	/* High word of |x|. */
	__LIBM_GET_DOUBLE_WORDS(__jx, __lx, __x);
	__ix = __jx & __INT32_C(0x7fffffff);

	/* x is INF or NaN */
	if (__ix >= __INT32_C(0x7ff00000)) {
		if (__jx >= 0) {
			return __LIBM_LOCAL_VALUE(one) / __x + __LIBM_LOCAL_VALUE(one); /* tanh(+-inf)=+-1 */
		} else {
			return __LIBM_LOCAL_VALUE(one) / __x - __LIBM_LOCAL_VALUE(one); /* tanh(NaN) = NaN */
		}
	}

	/* |x| < 22 */
	if (__ix < __INT32_C(0x40360000)) { /* |x|<22 */
		if ((__ix | __lx) == 0)
			return __x;                                   /* x == +-0 */
		if (__ix < __INT32_C(0x3c800000))                 /* |x|<2**-55 */
			return __x * (__LIBM_LOCAL_VALUE(one) + __x); /* tanh(small) = small */
		if (__ix >= __INT32_C(0x3ff00000)) {              /* |x|>=1  */
			__t = __ieee754_expm1(__LIBM_LOCAL_VALUE(two) * __ieee754_fabs(__x));
			__z = __LIBM_LOCAL_VALUE(one) - __LIBM_LOCAL_VALUE(two) / (__t + __LIBM_LOCAL_VALUE(two));
		} else {
			__t = __ieee754_expm1(-__LIBM_LOCAL_VALUE(two) * __ieee754_fabs(__x));
			__z = -__t / (__t + __LIBM_LOCAL_VALUE(two));
		}
		/* |x| > 22, return +-1 */
	} else {
		__z = __LIBM_LOCAL_VALUE(one) - __LIBM_LOCAL_VALUE(tiny); /* raised inexact flag */
	}
	return (__jx >= 0) ? __z : -__z;
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
#ifndef __libm_onel_defined
#define __libm_onel_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, onel, __IEEE854_LONG_DOUBLE_C(1.0))
#endif /* !__libm_onel_defined */
#ifndef __libm_tinyl_defined
#define __libm_tinyl_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, tinyl, __IEEE854_LONG_DOUBLE_C(1.0e-4900))
#endif /* !__libm_tinyl_defined */
#ifndef __libm_twol_defined
#define __libm_twol_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, twol, __IEEE854_LONG_DOUBLE_C(2.0))
#endif /* !__libm_twol_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(tanhl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_tanhl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __t, __z;
	__int32_t __se;
	__uint32_t __j0, __j1, __ix;

	/* High word of |x|. */
	__LIBM_GET_LDOUBLE_WORDS(__se, __j0, __j1, __x);
	__ix = __se & 0x7fff;

	/* x is INF or NaN */
	if (__ix == 0x7fff) {
		/* for NaN it's not important which branch: tanhl(NaN) = NaN */
		if (__se & 0x8000) {
			return __LIBM_LOCAL_VALUE(onel) / __x - __LIBM_LOCAL_VALUE(onel); /* tanhl(-inf)= -1; */
		} else {
			return __LIBM_LOCAL_VALUE(onel) / __x + __LIBM_LOCAL_VALUE(onel); /* tanhl(+inf)=+1 */
		}
	}

	/* |x| < 23 */
	if (__ix < 0x4003 || (__ix == 0x4003 && __j0 < __UINT32_C(0xb8000000))) { /* |x|<23 */
		if ((__ix | __j0 | __j1) == 0)
			return __x;                /* x == +- 0 */
		if (__ix < 0x3fc8)             /* |x|<2**-55 */
			return __x * (__LIBM_LOCAL_VALUE(onel) + __LIBM_LOCAL_VALUE(tinyl)); /* tanh(small) = small */
		if (__ix >= 0x3fff) {          /* |x|>=1  */
			__t = __ieee854_expm1l(__LIBM_LOCAL_VALUE(twol) * __ieee854_fabsl(__x));
			__z = __LIBM_LOCAL_VALUE(onel) - __LIBM_LOCAL_VALUE(twol) / (__t + __LIBM_LOCAL_VALUE(twol));
		} else {
			__t = __ieee854_expm1l(-__LIBM_LOCAL_VALUE(twol) * __ieee854_fabsl(__x));
			__z = -__t / (__t + __LIBM_LOCAL_VALUE(twol));
		}
		/* |x| > 23, return +-1 */
	} else {
		__z = __LIBM_LOCAL_VALUE(onel) - __LIBM_LOCAL_VALUE(tinyl); /* raised inexact flag */
	}
	return (__se & 0x8000) ? -__z : __z;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_TANH_H */
