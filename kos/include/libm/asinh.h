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
#ifndef _LIBM_ASINH_H
#define _LIBM_ASINH_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fdlibm.h>
#include <libm/log.h>
#include <libm/log1p.h>
#include <libm/sqrt.h>

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
#ifndef __libm_ln2f_defined
#define __libm_ln2f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, ln2f, __IEEE754_FLOAT_C(6.9314718246e-01)) /* 0x3f317218 */
#endif /* !__libm_ln2f_defined */
#ifndef __libm_hugevalf_defined
#define __libm_hugevalf_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, hugevalf, __IEEE754_FLOAT_C(1.0000000000e+30))
#endif /* !__libm_hugevalf_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(asinhf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_asinhf)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __w;
	__int32_t __hx, __ix;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix < __INT32_C(0x38000000)) { /* |x|<2**-14 */
		if (__LIBM_LOCAL_VALUE(hugevalf) + __x > __LIBM_LOCAL_VALUE(onef))
			return __x; /* return x inexact except 0 */
	}
	if (__ix > __INT32_C(0x47000000)) { /* |x| > 2**14 */
		if (!__LIBM_FLT_UWORD_IS_FINITE(__ix))
			return __x + __x; /* x is inf or NaN */
		__w = __ieee754_logf(__ieee754_fabsf(__x)) + __LIBM_LOCAL_VALUE(ln2f);
	} else {
		__IEEE754_FLOAT_TYPE__ __xa = __ieee754_fabsf(__x);
		if (__ix > __INT32_C(0x40000000)) { /* 2**14 > |x| > 2.0 */
			__w = __ieee754_logf(__IEEE754_FLOAT_C(2.0) * __xa +
			                     __LIBM_LOCAL_VALUE(onef) /
			                     (__ieee754_sqrtf(__xa * __xa + __LIBM_LOCAL_VALUE(onef)) + __xa));
		} else { /* 2.0 > |x| > 2**-14 */
			__IEEE754_FLOAT_TYPE__ __t = __xa * __xa;
			__w = __ieee754_log1pf(__xa + __t / (__LIBM_LOCAL_VALUE(onef) +
			                                     __ieee754_sqrtf(__LIBM_LOCAL_VALUE(onef) + __t)));
		}
	}
	if (__hx > 0)
		return __w;
	return -__w;
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
#ifndef __libm_ln2_defined
#define __libm_ln2_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, ln2, __IEEE754_DOUBLE_C(6.93147180559945286227e-01)) /* 0x3FE62E42, 0xFEFA39EF */
#endif /* !__libm_ln2_defined */
#ifndef __libm_hugeval_defined
#define __libm_hugeval_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, hugeval, __IEEE754_DOUBLE_C(1.00000000000000000000e+300))
#endif /* !__libm_hugeval_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(asinh) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_asinh)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __w;
	__int32_t __hx, __ix;
	__LIBM_GET_HIGH_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix < __INT32_C(0x3e300000)) { /* |x|<2**-28 */
		if (__LIBM_LOCAL_VALUE(hugeval) + __x > __LIBM_LOCAL_VALUE(one))
			return __x; /* return x inexact except 0 */
	}
	if (__ix > __INT32_C(0x41b00000)) { /* |x| > 2**28 */
		if (__ix >= __INT32_C(0x7ff00000))
			return __x + __x; /* x is inf or NaN */
		__w = __ieee754_log(__ieee754_fabs(__x)) + __LIBM_LOCAL_VALUE(ln2);
	} else {
		__IEEE754_DOUBLE_TYPE__ xa = __ieee754_fabs(__x);
		if (__ix > __INT32_C(0x40000000)) { /* 2**28 > |x| > 2.0 */
			__w = __ieee754_log(2.0 * xa + __LIBM_LOCAL_VALUE(one) / (__ieee754_sqrt(xa * xa + __LIBM_LOCAL_VALUE(one)) + xa));
		} else { /* 2.0 > |x| > 2**-28 */
			__IEEE754_DOUBLE_TYPE__ __t = xa * xa;
			__w = __ieee754_log1p(xa + __t / (__LIBM_LOCAL_VALUE(one) +
			                                  __ieee754_sqrt(__LIBM_LOCAL_VALUE(one) + __t)));
		}
	}
	if (__hx > 0)
		return __w;
	return -__w;
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
#ifndef __libm_ln2l_defined
#define __libm_ln2l_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, ln2l, __IEEE854_LONG_DOUBLE_C(6.931471805599453094287e-01)) /* 0x3FFE, 0xB17217F7, 0xD1CF79AC */
#endif /* !__libm_ln2l_defined */
#ifndef __libm_hugevall_defined
#define __libm_hugevall_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, hugevall, __IEEE854_LONG_DOUBLE_C(1.000000000000000000e+4900));
#endif /* !__libm_hugevall_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(asinhl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_asinhl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __t, __w;
	__int32_t __hx, __ix;
	__LIBM_GET_LDOUBLE_EXP(__hx, __x);
	__ix = __hx & IEEE854_LONG_DOUBLE_MAXEXP;
	if (__ix < 0x3fde) { /* |x|<2**-34 */
		if (__LIBM_LOCAL_VALUE(hugevall) + __x > __LIBM_LOCAL_VALUE(onel))
			return __x; /* return x inexact except 0 */
	}
	if (__ix > 0x4020) { /* |x| > 2**34 */
		if (__ix == IEEE854_LONG_DOUBLE_MAXEXP)
			return __x + __x; /* x is inf or NaN */
		__w = __ieee854_logl(__ieee854_fabsl(__x)) + __LIBM_LOCAL_VALUE(ln2l);
	} else {
		__IEEE854_LONG_DOUBLE_TYPE__ __xa = __ieee854_fabsl(__x);
		if (__ix > 0x4000) { /* 2**34 > |x| > 2.0 */
			__w = __ieee854_logl(2.0L * __xa +
			                     __LIBM_LOCAL_VALUE(onel) /
			                     (__ieee854_sqrtl(__xa * __xa + __LIBM_LOCAL_VALUE(onel)) + __xa));
		} else { /* 2.0 > |x| > 2**-28 */
			__t = __xa * __xa;
			__w = __ieee854_log1pl(__xa + __t / (__LIBM_LOCAL_VALUE(onel) +
			                                     __ieee854_sqrtl(__LIBM_LOCAL_VALUE(onel) + __t)));
		}
	}
	if (__hx > 0)
		return __w;
	return -__w;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ASINH_H */
