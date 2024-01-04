/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBM_ISINF_H
#define _LIBM_ISINF_H 1

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

__LIBM_LOCAL_FUNC(isinff) __ATTR_WUNUSED __ATTR_CONST int
__NOTHROW(__LIBCCALL __ieee754_isinff)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __ix;
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	__ix &= 0x7fffffff;
	return __LIBM_FLT_UWORD_IS_INFINITE(__ix);
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

__LIBM_LOCAL_FUNC(isinf) __ATTR_WUNUSED __ATTR_CONST int
__NOTHROW(__LIBCCALL __ieee754_isinf)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __hx, __lx;
	__LIBM_EXTRACT_WORDS(__hx, __lx, __x);
	__hx &= 0x7fffffff;
	__hx |= (__uint32_t)(__lx | (-__lx)) >> 31;
	__hx = 0x7ff00000 - __hx;
	return 1 - (int)((__uint32_t)(__hx | (-__hx)) >> 31);
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Change for long double by Jakub Jelinek <jj@ultra.linux.cz>
 * Public domain.
 */

__LIBM_LOCAL_FUNC(isinfl) __ATTR_WUNUSED __ATTR_CONST int
__NOTHROW(__LIBCCALL __ieee854_isinfl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__int32_t __se, __hx, __lx;
	__LIBM_GET_LDOUBLE_WORDS(__se, __hx, __lx, __x);
	__lx |= (__hx & __UINT32_C(0x7fffffff)) | ((__se & 0x7fff) ^ 0x7fff);
	__lx |= -__lx;
	__se &= 0x8000;
	return (int)(~(__lx >> 31) & (1 - (__se >> 14)));
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ISINF_H */
