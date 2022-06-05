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
#ifndef _LIBM_ISNAN_H
#define _LIBM_ISNAN_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

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

__LIBM_LOCAL_FUNC(isnanf) __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee754_isnanf)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __ix;
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	__ix &= 0x7fffffff;
	return __LIBM_FLT_UWORD_IS_NAN(__ix);
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

__LIBM_LOCAL_FUNC(isnan) __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee754_isnan)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __hx, __lx;
	__LIBM_EXTRACT_WORDS(__hx, __lx, __x);
	__hx &= 0x7fffffff;
	__hx |= (__int32_t)((__uint32_t)(__lx | (-__lx)) >> 31);
	__hx = 0x7ff00000 - __hx;
	return (int)(((__uint32_t)(__hx)) >> 31);
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(isnanl) __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee854_isnanl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__int32_t __se, __hx, __lx;
	__LIBM_GET_LDOUBLE_WORDS(__se, __hx, __lx, __x);
	__se = (__se & 0x7fff) << 1;
	__lx |= __hx & __INT32_C(0x7fffffff);
	__se |= (__int32_t)((__uint32_t)(__lx | (-__lx)) >> 31);
	__se = 0xfffe - __se;
	return (int)(((__uint32_t)(__se)) >> 31);
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ISNAN_H */
