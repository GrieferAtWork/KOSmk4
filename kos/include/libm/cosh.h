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
#ifndef _LIBM_COSH_H
#define _LIBM_COSH_H 1

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
#ifndef __libm_hugevalf_defined
#define __libm_hugevalf_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, hugevalf, __IEEE754_FLOAT_C(1.0000000000e+30))
#endif /* !__libm_hugevalf_defined */
#ifndef __libm_halff_defined
#define __libm_halff_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, halff, __IEEE754_FLOAT_C(5.0000000000e-01)) /* 0x3f000000 */
#endif /* !__libm_halff_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(coshf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_coshf)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __t, __w;
	__int32_t __ix;
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	__ix &= __INT32_C(0x7fffffff);

	/* x is INF or NaN */
	if (!__LIBM_FLT_UWORD_IS_FINITE(__ix))
		return __x * __x;

	/* |x| in [0.5*ln2,22], return (exp(|x|)+1/exp(|x|)/2; */
	if (__ix < __INT32_C(0x41b00000)) {
		/* |x| in [0,0.5*ln2], return 1+expm1(|x|)^2/(2*exp(|x|)) */
		if (__ix < __INT32_C(0x3eb17218)) {
			__t = __ieee754_expm1f(__ieee754_fabsf(__x));
			__w = __LIBM_LOCAL_VALUE(onef) + __t;
			if (__ix < __INT32_C(0x24000000))
				return __w; /* cosh(tiny) = 1 */
			return __LIBM_LOCAL_VALUE(onef) + (__t * __t) / (__w + __w);
		}

		/* |x| in [0,22] */
		__t = __ieee754_expf(__ieee754_fabsf(__x));
		return __LIBM_LOCAL_VALUE(halff) * __t +
		       __LIBM_LOCAL_VALUE(halff) / __t;
	}

	/* |x| in [22, log(maxdouble)] return half*exp(|x|) */
	if (__ix <= __LIBM_FLT_UWORD_LOG_MAX)
		return __LIBM_LOCAL_VALUE(halff) * __ieee754_expf(__ieee754_fabsf(__x));

	/* |x| in [log(maxdouble), overflowthresold] */
	if (__ix <= __LIBM_FLT_UWORD_LOG_2MAX) {
		__w = __ieee754_expf(__LIBM_LOCAL_VALUE(halff) * __ieee754_fabsf(__x));
		__t = __LIBM_LOCAL_VALUE(halff) * __w;
		return __t * __w;
	}

	/* |x| > overflowthresold, cosh(x) overflow */
	return __LIBM_LOCAL_VALUE(hugevalf) *
	       __LIBM_LOCAL_VALUE(hugevalf);
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
#ifndef __libm_hugeval_defined
#define __libm_hugeval_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, hugeval, __IEEE754_DOUBLE_C(1.00000000000000000000e+300))
#endif /* !__libm_hugeval_defined */
#ifndef __libm_half_defined
#define __libm_half_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, half, __IEEE754_DOUBLE_C(5.00000000000000000000e-01)) /* 0x3FE00000, 0x00000000 */
#endif /* !__libm_half_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(cosh) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_cosh)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __t, __w;
	__int32_t __ix;
	__uint32_t __lx;

	/* High word of |x|. */
	__LIBM_GET_HIGH_WORD(__ix, __x);
	__ix &= __INT32_C(0x7fffffff);

	/* x is INF or NaN */
	if (__ix >= __INT32_C(0x7ff00000))
		return __x * __x;

	/* |x| in [0,22] */
	if (__ix < __INT32_C(0x40360000)) {
		/* |x| in [0,0.5*ln2], return 1+expm1(|x|)^2/(2*exp(|x|)) */
		if (__ix < __INT32_C(0x3fd62e43)) {
			__t = __ieee754_expm1(__ieee754_fabs(__x));
			__w = __LIBM_LOCAL_VALUE(one) + __t;
			if (__ix < __INT32_C(0x3c800000))
				return __w; /* cosh(tiny) = 1 */
			return __LIBM_LOCAL_VALUE(one) + (__t * __t) / (__w + __w);
		}

		/* |x| in [0.5*ln2,22], return (exp(|x|)+1/exp(|x|)/2; */
		__t = __ieee754_exp(__ieee754_fabs(__x));
		return __LIBM_LOCAL_VALUE(half) * __t +
		       __LIBM_LOCAL_VALUE(half) / __t;
	}

	/* |x| in [22, log(maxdouble)] return half*exp(|x|) */
	if (__ix < __INT32_C(0x40862E42))
		return __LIBM_LOCAL_VALUE(half) * __ieee754_exp(__ieee754_fabs(__x));

	/* |x| in [log(maxdouble), overflowthresold] */
	__LIBM_GET_LOW_WORD(__lx, __x);
	if (__ix < __INT32_C(0x408633ce) || (__ix == __INT32_C(0x408633ce) && __lx <= __UINT32_C(0x8fb9f87d))) {
		__w = __ieee754_exp(__LIBM_LOCAL_VALUE(half) * __ieee754_fabs(__x));
		__t = __LIBM_LOCAL_VALUE(half) * __w;
		return __t * __w;
	}

	/* |x| > overflowthresold, cosh(x) overflow */
	return __LIBM_LOCAL_VALUE(hugeval) *
	       __LIBM_LOCAL_VALUE(hugeval);
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
#ifndef __libm_hugevall_defined
#define __libm_hugevall_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, hugevall, __IEEE854_LONG_DOUBLE_C(1.000000000000000000e+4900));
#endif /* !__libm_hugevall_defined */
#ifndef __libm_halfl_defined
#define __libm_halfl_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, halfl, __IEEE854_LONG_DOUBLE_C(0.5));
#endif /* !__libm_halfl_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(coshl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_coshl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __t, __w;
	__int32_t __ex;
	__uint32_t __mx, __lx;

	/* High word of |x|. */
	__LIBM_GET_LDOUBLE_WORDS(__ex, __mx, __lx, __x);
	__ex &= 0x7fff;

	/* x is INF or NaN */
	if (__ex == 0x7fff)
		return __x * __x;

	/* |x| in [0,22] */
	if (__ex < 0x4003 || (__ex == 0x4003 && __mx < __UINT32_C(0xb0000000))) {
		/* |x| in [0,0.5*ln2], return 1+expm1l(|x|)^2/(2*expl(|x|)) */
		if (__ex < 0x3ffd || (__ex == 0x3ffd && __mx < __UINT32_C(0xb17217f7))) {
			__t = __ieee854_expm1l(__ieee854_fabsl(__x));
			__w = __LIBM_LOCAL_VALUE(onel) + __t;
			if (__ex < 0x3fbc)
				return __w; /* cosh(tiny) = 1 */
			return __LIBM_LOCAL_VALUE(onel) + (__t * __t) / (__w + __w);
		}

		/* |x| in [0.5*ln2,22], return (exp(|x|)+1/exp(|x|)/2; */
		__t = __ieee854_expl(__ieee854_fabsl(__x));
		return __LIBM_LOCAL_VALUE(halfl) * __t +
		       __LIBM_LOCAL_VALUE(halfl) / __t;
	}

	/* |x| in [22, ln(maxdouble)] return half*exp(|x|) */
	if (__ex < 0x400c || (__ex == 0x400c && __mx < __UINT32_C(0xb1700000)))
		return __LIBM_LOCAL_VALUE(halfl) * __ieee854_expl(__ieee854_fabsl(__x));

	/* |x| in [log(maxdouble), log(2*maxdouble)) */
	if (__ex == 0x400c &&
	    (__mx < __UINT32_C(0xb174ddc0) ||
	     (__mx == __UINT32_C(0xb174ddc0) &&
	      __lx < __UINT32_C(0x31aec0eb)))) {
		__w = __ieee854_expl(__LIBM_LOCAL_VALUE(halfl) * __ieee854_fabsl(__x));
		__t = __LIBM_LOCAL_VALUE(halfl) * __w;
		return __t * __w;
	}

	/* |x| >= log(2*maxdouble), cosh(x) overflow */
	return __LIBM_LOCAL_VALUE(hugevall) *
	       __LIBM_LOCAL_VALUE(hugevall);
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_COSH_H */
