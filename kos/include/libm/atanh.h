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
#ifndef _LIBM_ATANH_H
#define _LIBM_ATANH_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/copysign.h>
#include <libm/fcomp.h>
#include <libm/fdlibm.h>
#include <libm/log.h>
#include <libm/log1p.h>

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
#ifdef __ieee754_log1pf
__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_hugevalf_defined
#define __libm_hugevalf_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, hugevalf, __IEEE754_FLOAT_C(1.0000000000e+30))
#endif /* !__libm_hugevalf_defined */
__LIBM_LOCAL_DECLARE_END
#elif !defined(__ieee754_logf)
__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_onef_defined
#define __libm_onef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0000000000e+00)) /* 0x3F800000 */
#endif /* !__libm_onef_defined */
#ifndef __libm_hugevalf_defined
#define __libm_hugevalf_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, hugevalf, __IEEE754_FLOAT_C(1.0000000000e+30))
#endif /* !__libm_hugevalf_defined */
#ifndef __libm_zerof_defined
#define __libm_zerof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, zerof, __IEEE754_FLOAT_C(0.0000000000e+00)) /* 0x00000000 */
#endif /* !__libm_zerof_defined */
__LIBM_LOCAL_DECLARE_END
#endif /* !__ieee754_log1pf && !__ieee754_logf */

__LIBM_LOCAL_FUNC(atanhf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_atanhf)(__IEEE754_FLOAT_TYPE__ __x) {
#ifdef __ieee754_log1pf
	__IEEE754_FLOAT_TYPE__ __xa = __ieee754_fabsf(__x);
	__IEEE754_FLOAT_TYPE__ __t;
	if (__ieee754_islessf(__xa, 0.5f)) {
		if (__xa < __IEEE754_FLOAT_C(0x1.0p-28) /*hexconstf(0x1.0p-28f, 3.7252902984619140625000e-09F, UC(0x31800000))*/) {
			__libm_math_force_eval_r(__IEEE754_FLOAT_TYPE__, __LIBM_LOCAL_VALUE(hugevalf) + __x);
			return __x;
		}
		__t = __xa + __xa;
		__t = __IEEE754_FLOAT_C(0.5) * __ieee754_log1pf(__t + __t * __xa / (__IEEE754_FLOAT_C(1.0) - __xa));
	} else if (__ieee754_islessf(__xa, __IEEE754_FLOAT_C(1.0))) {
		__t = __IEEE754_FLOAT_C(0.5) * __ieee754_log1pf((__xa + __xa) / (__IEEE754_FLOAT_C(1.0) - __xa));
	} else {
		if (__ieee754_isgreaterf(__xa, __IEEE754_FLOAT_C(1.0)))
			return (__x - __x) / (__x - __x);
		return __x / __IEEE754_FLOAT_C(0.0);
	}
	return __ieee754_copysignf(__t, __x);
#elif defined(__ieee754_logf)
	return __IEEE754_FLOAT_C(0.5) * __ieee754_logf((__IEEE754_FLOAT_C(1.0) + __x) /
	                                               (__IEEE754_FLOAT_C(1.0) - __x));
#else /* ... */
	__IEEE754_FLOAT_TYPE__ __t;
	__int32_t __hx, __ix;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix > __INT32_C(0x3f800000)) /* |x|>1 */
		return (__x - __x) / (__x - __x);
	if (__ix == __INT32_C(0x3f800000))
		return __x / __LIBM_LOCAL_VALUE(zerof);
	if (__ix < __INT32_C(0x31800000) && (__LIBM_LOCAL_VALUE(hugevalf) + __x) > __LIBM_LOCAL_VALUE(zerof))
		return __x; /* x<2**-28 */
	__LIBM_SET_FLOAT_WORD(__x, __ix);
	if (__ix < __INT32_C(0x3f000000)) { /* x < 0.5 */
		__t = __x + __x;
		__t = __IEEE754_FLOAT_C(0.5) * __ieee754_log1pf(__t + __t * __x / (__LIBM_LOCAL_VALUE(onef) - __x));
	} else {
		__t = __IEEE754_FLOAT_C(0.5) * __ieee754_log1pf((__x + __x) / (__LIBM_LOCAL_VALUE(onef) - __x));
	}
	if (__hx >= 0)
		return __t;
	return -__t;
#endif /* !... */
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
#ifdef __ieee754_log1p
__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_hugeval_defined
#define __libm_hugeval_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, hugeval, __IEEE754_DOUBLE_C(1.00000000000000000000e+300))
#endif /* !__libm_hugeval_defined */
__LIBM_LOCAL_DECLARE_END
#elif !defined(__ieee754_log)
__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.00000000000000000000e+00)) /* 0x3FF00000, 0x00000000 */
#endif /* !__libm_one_defined */
#ifndef __libm_hugeval_defined
#define __libm_hugeval_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, hugeval, __IEEE754_DOUBLE_C(1.00000000000000000000e+300))
#endif /* !__libm_hugeval_defined */
#ifndef __libm_zero_defined
#define __libm_zero_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, zero, __IEEE754_DOUBLE_C(0.00000000000000000000e+00)) /* 0x00000000, 0x00000000 */
#endif /* !__libm_zero_defined */
__LIBM_LOCAL_DECLARE_END
#endif /* !__ieee754_log1p && !__ieee754_log */

__LIBM_LOCAL_FUNC(atanh) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_atanh)(__IEEE754_DOUBLE_TYPE__ __x) {
#ifdef __ieee754_log1p
	__IEEE754_DOUBLE_TYPE__ __xa = __ieee754_fabs(__x);
	__IEEE754_DOUBLE_TYPE__ __t;
	if (__ieee754_isless(__xa, __IEEE754_DOUBLE_C(0.5))) {
		if (__xa < __IEEE754_DOUBLE_C(0x1.0p-28)) {
			__libm_math_force_eval_r(__IEEE754_FLOAT_TYPE__, __LIBM_LOCAL_VALUE(hugeval) + __x);
			return __x;
		}
		__t = __xa + __xa;
		__t = __IEEE754_DOUBLE_C(0.5) * __ieee754_log1p(__t + __t * __xa / (__IEEE754_DOUBLE_C(1.0) - __xa));
	} else if (__ieee754_isless(__xa, __IEEE754_DOUBLE_C(1.0))) {
		__t = __IEEE754_DOUBLE_C(0.5) * __ieee754_log1p((__xa + __xa) / (__IEEE754_DOUBLE_C(1.0) - __xa));
	} else {
		if (__ieee754_isgreater(__xa, __IEEE754_DOUBLE_C(1.0)))
			return (__x - __x) / (__x - __x);
		return __x / __IEEE754_DOUBLE_C(0.0);
	}
	return __ieee754_copysign(__t, __x);
#elif defined(__ieee754_log)
	return __IEEE754_DOUBLE_C(0.5) * __ieee754_log((__IEEE754_DOUBLE_C(1.0) + __x) /
	                                               (__IEEE754_DOUBLE_C(1.0) - __x));
#else /* ... */
	__IEEE754_DOUBLE_TYPE__ __t;
	__int32_t __hx, __ix;
	__uint32_t __lx;
	__LIBM_GET_DOUBLE_WORDS(__hx, __lx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if ((__ix | ((__lx | (-__lx)) >> 31)) > __INT32_C(0x3ff00000)) /* |x|>1 */
		return (__x - __x) / (__x - __x);
	if (__ix == __INT32_C(0x3ff00000))
		return __x / __LIBM_LOCAL_VALUE(zero);
	if (__ix < __INT32_C(0x3e300000) && (__LIBM_LOCAL_VALUE(hugeval) + __x) > __LIBM_LOCAL_VALUE(zero))
		return __x; /* x<2**-28 */
	__LIBM_SET_HIGH_WORD(__x, __ix);
	if (__ix < __INT32_C(0x3fe00000)) { /* x < 0.5 */
		__t = __x + __x;
		__t = __IEEE754_DOUBLE_C(0.5) * __ieee754_log1p(__t + __t * __x / (__LIBM_LOCAL_VALUE(one) - __x));
	} else {
		__t = __IEEE754_DOUBLE_C(0.5) * __ieee754_log1p((__x + __x) / (__LIBM_LOCAL_VALUE(one) - __x));
	}
	if (__hx >= 0)
		return __t;
	return -__t;
#endif /* !... */
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
#ifndef __libm_zerol_defined
#define __libm_zerol_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, zerol, __IEEE854_LONG_DOUBLE_C(0.0))
#endif /* !__libm_zerol_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(atanhl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_atanhl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __t;
	__int32_t __ix;
	__uint32_t __i0, __i1;
	__int32_t __se;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__ix = __se & 0x7fff;
	if ((__ix + ((((__i0 & __INT32_C(0x7fffffff)) | __i1) |
	              (-((__i0 & __INT32_C(0x7fffffff)) | __i1))) >>
	             31)) > 0x3fff)
		return (__x - __x) / (__x - __x); /* |x|>1 */
	if (__ix == 0x3fff)
		return __x / __LIBM_LOCAL_VALUE(zerol);
	if (__ix < 0x3fe3) {
		__libm_math_force_eval_r(__IEEE854_LONG_DOUBLE_TYPE__, __LIBM_LOCAL_VALUE(hugevall) + __x);
		return __x; /* x<2**-28 */
	}
	__LIBM_SET_LDOUBLE_EXP(__x, __ix);
	if (__ix < 0x3ffe) { /* x < 0.5 */
		__t = __x + __x;
		__t = __IEEE854_LONG_DOUBLE_C(0.5) *
		      __ieee854_log1pl(__t + __t * __x / (__LIBM_LOCAL_VALUE(onel) - __x));
	} else {
		__t = __IEEE854_LONG_DOUBLE_C(0.5) *
		      __ieee854_log1pl((__x + __x) / (__LIBM_LOCAL_VALUE(onel) - __x));
	}
	if (__se < 0)
		__t = -__t;
	return __t;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ATANH_H */
