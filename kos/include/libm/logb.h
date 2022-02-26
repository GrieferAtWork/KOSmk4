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
#ifndef _LIBM_LOGB_H
#define _LIBM_LOGB_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

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

__LIBM_LOCAL_FUNC(logbf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_logbf)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __ix, __rix;
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	__ix &= __INT32_C(0x7fffffff);
	if (__ix == 0)
		return (__IEEE754_FLOAT_TYPE__)-1.0 / __ieee754_fabsf(__x);
	if (__ix >= __INT32_C(0x7f800000))
		return __x * __x;
	if ((__rix = __ix >> __LIBM_IEEE754_FLOAT_SHIFT) == 0) {
		__rix -= __hybrid_clz32(__ix) - 9;
	}
	return (__IEEE754_FLOAT_TYPE__)(__rix - __LIBM_IEEE754_FLOAT_BIAS);
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

__LIBM_LOCAL_FUNC(logb) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_logb)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __lx, __ix, __rix;
	__LIBM_GET_DOUBLE_WORDS(__ix, __lx, __x);
	__ix &= __INT32_C(0x7fffffff);
	if ((__ix | __lx) == 0)
		return -1.0 / __ieee754_fabs(__x);
	if (__ix >= __INT32_C(0x7ff00000))
		return __x * __x;
	if ((__rix = __ix >> __LIBM_IEEE754_DOUBLE_SHIFT) == 0) {
		__int32_t __ma;
		if (__ix == 0) {
			__ma = __hybrid_clz32(__lx) + 32;
		} else {
			__ma = __hybrid_clz32(__ix);
		}
		__rix -= __ma - 12;
	}
	return (__IEEE754_DOUBLE_TYPE__)(__rix - __LIBM_IEEE754_DOUBLE_BIAS);
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

__LIBM_LOCAL_FUNC(logbl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_logbl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__int32_t __es, __lx, __ix;
	__LIBM_GET_LDOUBLE_WORDS(__es, __ix, __lx, __x);
	__es &= __LIBM_IEEE854_LONG_DOUBLE_MAXEXP;
	if ((__es | __ix | __lx) == 0)
		return -1.0 / __ieee854_fabsl(__x);
	if (__es == __LIBM_IEEE854_LONG_DOUBLE_MAXEXP)
		return __x * __x;
	if (__es == 0) {
		__int32_t __ma;
		if (__ix == 0) {
			__ma = __hybrid_clz32(__lx) + 32;
		} else {
			__ma = __hybrid_clz32(__ix);
		}
		__es -= __ma - 1;
	}
	return (__IEEE854_LONG_DOUBLE_TYPE__)(__es - __LIBM_IEEE854_LONG_DOUBLE_BIAS);
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_LOGB_H */
