/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBM_FINITE_H
#define _LIBM_FINITE_H 1

#include <__crt.h>

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

__LOCAL __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee754_finitef)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __ix;
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	__ix &= 0x7fffffff;
	return __LIBM_FLT_UWORD_IS_FINITE(__ix);
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

__LOCAL __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee754_finite)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __hx;
	__LIBM_GET_HIGH_WORD(__hx, __x);
	return (int)((__uint32_t)((__hx & 0x7fffffff) - 0x7ff00000) >> 31);
}
#endif /* __IEEE754_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBM_FINITE_H */
