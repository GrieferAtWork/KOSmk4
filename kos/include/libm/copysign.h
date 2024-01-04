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
#ifndef _LIBM_COPYSIGN_H
#define _LIBM_COPYSIGN_H 1

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

__LIBM_LOCAL_FUNC(copysignf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_copysignf)(__IEEE754_FLOAT_TYPE__ __num,
                                 __IEEE754_FLOAT_TYPE__ __sign) {
	__uint32_t __ix, __iy;
	__LIBM_GET_FLOAT_WORD(__ix, __num);
	__LIBM_GET_FLOAT_WORD(__iy, __sign);
	__LIBM_SET_FLOAT_WORD(__num, (__ix & 0x7fffffff) | (__iy & 0x80000000));
	return __num;
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

__LIBM_LOCAL_FUNC(copysign) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_copysign)(__IEEE754_DOUBLE_TYPE__ __num,
                                __IEEE754_DOUBLE_TYPE__ __sign) {
	__uint32_t __hx, __hy;
	__LIBM_GET_HIGH_WORD(__hx, __num);
	__LIBM_GET_HIGH_WORD(__hy, __sign);
	__LIBM_SET_HIGH_WORD(__num, (__hx & 0x7fffffff) | (__hy & 0x80000000));
	return __num;
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(copysignl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_copysignl)(__IEEE854_LONG_DOUBLE_TYPE__ __num,
                                 __IEEE854_LONG_DOUBLE_TYPE__ __sign) {
	__uint32_t __es1, __es2;
	__LIBM_GET_LDOUBLE_EXP(__es1, __num);
	__LIBM_GET_LDOUBLE_EXP(__es2, __sign);
	__LIBM_SET_LDOUBLE_EXP(__num, (__es1 & 0x7fff) | (__es2 & 0x8000));
	return __num;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_COPYSIGN_H */
