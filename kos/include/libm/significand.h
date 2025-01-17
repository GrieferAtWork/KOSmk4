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
#ifndef _LIBM_SIGNIFICAND_H
#define _LIBM_SIGNIFICAND_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/asm/significand.h>
#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_significandf
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(significandf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_significandf)(__IEEE754_FLOAT_TYPE__ __x) {
	__uint32_t __hx, __ix;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __hx & __UINT32_C(0x7f800000);
	if (__ix != 0 && __ix != __UINT32_C(0x7f800000)) {
		__LIBM_SET_FLOAT_WORD(__x, (__hx & __UINT32_C(0x807fffff)) |
		                           /*   */ __UINT32_C(0x3f800000));
	}
	return __x;
}
#endif /* !__ieee754_significandf */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_significand
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

__LIBM_LOCAL_FUNC(significand) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_significand)(__IEEE754_DOUBLE_TYPE__ __x) {
	__uint32_t __hx, __ix;
	__LIBM_GET_HIGH_WORD(__hx, __x);
	__ix = __hx & __UINT32_C(0x7ff00000);
	if (__ix != 0 && __ix != __UINT32_C(0x7ff00000)) {
		__LIBM_SET_HIGH_WORD(__x, (__hx & __UINT32_C(0x800fffff)) |
		                          /*   */ __UINT32_C(0x3ff00000));
	}
	return __x;
}
#endif /* !__ieee754_significand */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_significandl
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(significandl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_significandl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__uint32_t __exp, __ix;
	__LIBM_GET_LDOUBLE_EXP(__exp, __x);
	__ix = __exp & 0x7fff;
	if (__ix != 0 && __ix != 0x7fff)
		__LIBM_SET_LDOUBLE_EXP(__x, (__exp & 0x8000) | 0x3fff);
	return __x;
}
#endif /* !__ieee854_significandl */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_SIGNIFICAND_H */
