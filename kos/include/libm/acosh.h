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
#ifndef _LIBM_ACOSH_H
#define _LIBM_ACOSH_H 1

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
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(acoshf) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_acoshf)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __t;
	__int32_t __hx;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	if (__hx < __INT32_C(0x3f800000)) { /* x < 1 */
		return (__x - __x) / (__x - __x);
	} else if (__hx >= __INT32_C(0x4d800000)) {  /* x > 2**28 */
		if (!__LIBM_FLT_UWORD_IS_FINITE(__hx)) { /* x is inf of NaN */
			return __x + __x;
		}
		return __ieee754_logf(__x) + __LIBM_LOCAL_VALUE(ln2f); /* acosh(huge)=log(2x) */
	} else if (__hx == __INT32_C(0x3f800000)) {
		return __IEEE754_FLOAT_C(0.0);         /* acosh(1) = 0 */
	} else if (__hx > __INT32_C(0x40000000)) { /* 2**28 > x > 2 */
		__t = __x * __x;
		return __ieee754_logf(__IEEE754_FLOAT_C(2.0) * __x -
		                      __LIBM_LOCAL_VALUE(onef) / (__x + __ieee754_sqrtf(__t - __LIBM_LOCAL_VALUE(onef))));
	} else { /* 1<x<2 */
		__t = __x - __LIBM_LOCAL_VALUE(onef);
		return __ieee754_log1pf(__t + __ieee754_sqrtf(__IEEE754_FLOAT_C(2.0) * __t + __t * __t));
	}
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
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(acosh) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_acosh)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __t;
	__int32_t __hx;
	__uint32_t __lx;
	__LIBM_GET_DOUBLE_WORDS(__hx, __lx, __x);
	if (__hx < __INT32_C(0x3ff00000)) { /* x < 1 */
		return (__x - __x) / (__x - __x);
	} else if (__hx >= __INT32_C(0x41b00000)) { /* x > 2**28 */
		if (__hx >= __INT32_C(0x7ff00000))      /* x is inf of NaN */
			return __x + __x;
		return __ieee754_log(__x) + __LIBM_LOCAL_VALUE(ln2); /* acosh(huge)=log(2x) */
	} else if (((__hx - __INT32_C(0x3ff00000)) | __lx) == 0) {
		return __IEEE754_DOUBLE_C(0.0);        /* acosh(1) = 0 */
	} else if (__hx > __INT32_C(0x40000000)) { /* 2**28 > x > 2 */
		__t = __x * __x;
		return __ieee754_log(__IEEE754_DOUBLE_C(2.0) * __x -
		                     __LIBM_LOCAL_VALUE(one) / (__x + __ieee754_sqrt(__t - __LIBM_LOCAL_VALUE(one))));
	} else { /* 1<x<2 */
		__t = __x - __LIBM_LOCAL_VALUE(one);
		return __ieee754_log1p(__t + __ieee754_sqrt(__IEEE754_DOUBLE_C(2.0) * __t + __t * __t));
	}
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
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(acoshl) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_acoshl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __t;
	__uint32_t __se, __i0, __i1;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	if (__se < 0x3fff || (__se & 0x8000)) { /* x < 1 */
		return (__x - __x) / (__x - __x);
	} else if (__se >= 0x401d) { /* x > 2**30 */
		if (__se >= 0x7fff) {    /* x is inf of NaN */
			return __x + __x;
		} else {
			return __ieee854_logl(__x) + __LIBM_LOCAL_VALUE(ln2l); /* acoshl(huge)=logl(2x) */
		}
	} else if (((__se - 0x3fff) | __i0 | __i1) == 0) {
		return __IEEE854_LONG_DOUBLE_C(0.0); /* acosh(1) = 0 */
	} else if (__se > 0x4000) {              /* 2**28 > x > 2 */
		__t = __x * __x;
		return __ieee854_logl(__IEEE854_LONG_DOUBLE_C(2.0) * __x -
		                      __LIBM_LOCAL_VALUE(onel) / (__x + __ieee854_sqrtl(__t - __LIBM_LOCAL_VALUE(onel))));
	} else { /* 1<x<2 */
		__t = __x - __LIBM_LOCAL_VALUE(onel);
		return __ieee854_log1pl(__t + __ieee854_sqrtl(__IEEE854_LONG_DOUBLE_C(2.0) * __t + __t * __t));
	}
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ACOSH_H */
