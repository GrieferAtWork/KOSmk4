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
#ifndef _LIBM_SINH_H
#define _LIBM_SINH_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/exp.h>
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
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, shugef, __IEEE754_FLOAT_C(1.0e37))
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(sinhf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_sinhf)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __t, __w, __h;
	__int32_t __ix, __jx;
	__LIBM_GET_FLOAT_WORD(__jx, __x);
	__ix = __jx & __INT32_C(0x7fffffff);

	/* x is INF or NaN */
	if (!__LIBM_FLT_UWORD_IS_FINITE(__ix))
		return __x + __x;

	__h = __IEEE754_FLOAT_C(0.5);
	if (__jx < 0)
		__h = -__h;
	/* |x| in [0,22], return sign(x)*0.5*(E+E/(E+1))) */
	if (__ix < __INT32_C(0x41b00000)) {   /* |x|<22 */
		if (__ix < __INT32_C(0x31800000)) /* |x|<2**-28 */
			if (__LIBM_LOCAL_VALUE(shugef) + __x > __LIBM_LOCAL_VALUE(onef))
				return __x; /* sinh(tiny) = tiny with inexact */
		__t = __ieee754_expm1f(__ieee754_fabsf(__x));
		if (__ix < __INT32_C(0x3f800000))
			return __h * (__IEEE754_FLOAT_C(2.0) * __t - __t * __t / (__t + __LIBM_LOCAL_VALUE(onef)));
		return __h * (__t + __t / (__t + __LIBM_LOCAL_VALUE(onef)));
	}

	/* |x| in [22, log(maxdouble)] return 0.5*exp(|x|) */
	if (__ix <= __LIBM_FLT_UWORD_LOG_MAX)
		return __h * __ieee754_expf(__ieee754_fabsf(__x));

	/* |x| in [log(maxdouble), overflowthresold] */
	if (__ix <= __LIBM_FLT_UWORD_LOG_2MAX) {
		__w = __ieee754_expf(__IEEE754_FLOAT_C(0.5) * __ieee754_fabsf(__x));
		__t = __h * __w;
		return __t * __w;
	}

	/* |x| > overflowthresold, sinh(x) overflow */
	return __x * __LIBM_LOCAL_VALUE(shugef);
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
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, shuge, __IEEE754_DOUBLE_C(1.0e307))
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(sinh) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_sinh)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __t, __w, __h;
	__int32_t __ix, __jx;
	__uint32_t __lx;

	/* High word of |x|. */
	__LIBM_GET_HIGH_WORD(__jx, __x);
	__ix = __jx & __INT32_C(0x7fffffff);

	/* x is INF or NaN */
	if (__ix >= __INT32_C(0x7ff00000))
		return __x + __x;

	__h = __IEEE754_DOUBLE_C(0.5);
	if (__jx < 0)
		__h = -__h;
	/* |x| in [0,22], return sign(x)*0.5*(E+E/(E+1))) */
	if (__ix < __INT32_C(0x40360000)) {   /* |x|<22 */
		if (__ix < __INT32_C(0x3e300000)) /* |x|<2**-28 */
			if (__LIBM_LOCAL_VALUE(shuge) + __x > __LIBM_LOCAL_VALUE(one))
				return __x; /* sinh(tiny) = tiny with inexact */
		__t = __ieee754_expm1(__ieee754_fabs(__x));
		if (__ix < __INT32_C(0x3ff00000))
			return __h * (__IEEE754_DOUBLE_C(2.0) * __t - __t * __t / (__t + __LIBM_LOCAL_VALUE(one)));
		return __h * (__t + __t / (__t + __LIBM_LOCAL_VALUE(one)));
	}

	/* |x| in [22, log(maxdouble)] return 0.5*exp(|x|) */
	if (__ix < __INT32_C(0x40862e42))
		return __h * __ieee754_exp(__ieee754_fabs(__x));

	/* |x| in [log(maxdouble), overflowthresold] */
	__LIBM_GET_LOW_WORD(__lx, __x);
	if (__ix < __INT32_C(0x408633ce) || (__ix == __INT32_C(0x408633ce) && __lx <= __UINT32_C(0x8fb9f87d))) {
		__w = __ieee754_exp(__IEEE754_DOUBLE_C(0.5) * __ieee754_fabs(__x));
		__t = __h * __w;
		return __t * __w;
	}

	/* |x| > overflowthresold, sinh(x) overflow */
	return __x * __LIBM_LOCAL_VALUE(shuge);
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
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, shugel, __IEEE854_LONG_DOUBLE_C(1.0e4931))
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(sinhl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_sinhl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __t, __w, __h;
	__uint32_t __jx, __ix, __i0, __i1;

	/* Words of |x|. */
	__LIBM_GET_LDOUBLE_WORDS(__jx, __i0, __i1, __x);
	__ix = __jx & IEEE854_LONG_DOUBLE_MAXEXP;

	/* x is INF or NaN */
	if (__ix == IEEE854_LONG_DOUBLE_MAXEXP)
		return __x + __x;

	__h = __IEEE854_LONG_DOUBLE_C(0.5);
	if (__jx & 0x8000)
		__h = -__h;
	/* |x| in [0,25], return sign(x)*0.5*(E+E/(E+1))) */
	if (__ix < 0x4003 || (__ix == 0x4003 && __i0 <= __UINT32_C(0xc8000000))) { /* |x|<25 */
		if (__ix < 0x3fdf)                                         /* |x|<2**-32 */
			if (__LIBM_LOCAL_VALUE(shugel) + __x > __LIBM_LOCAL_VALUE(onel))
				return __x; /* sinh(tiny) = tiny with inexact */
		__t = __ieee854_expm1l(__ieee854_fabsl(__x));
		if (__ix < 0x3fff)
			return __h * (__IEEE854_LONG_DOUBLE_C(2.0) * __t - __t * __t / (__t + __LIBM_LOCAL_VALUE(onel)));
		return __h * (__t + __t / (__t + __LIBM_LOCAL_VALUE(onel)));
	}

	/* |x| in [25, log(maxdouble)] return 0.5*exp(|x|) */
	if (__ix < 0x400c || (__ix == 0x400c && __i0 < __UINT32_C(0xb17217f7)))
		return __h * __ieee854_expl(__ieee854_fabsl(__x));

	/* |x| in [log(maxdouble), overflowthreshold] */
	if (__ix < 0x400c || (__ix == 0x400c && (__i0 < __UINT32_C(0xb174ddc0) || (__i0 == __UINT32_C(0xb174ddc0) && __i1 <= __UINT32_C(0x31aec0ea))))) {
		__w = __ieee854_expl(__IEEE854_LONG_DOUBLE_C(0.5) * __ieee854_fabsl(__x));
		__t = __h * __w;
		return __t * __w;
	}

	/* |x| > overflowthreshold, sinhl(x) overflow */
	return __x * __LIBM_LOCAL_VALUE(shugel);
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_SINH_H */
