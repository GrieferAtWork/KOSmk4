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
#ifndef _LIBM_INF_H
#define _LIBM_INF_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <ieee754.h>

#include <libm/asm/inf.h>
#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_inff
__LIBM_LOCAL_FUNC(inff) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
__NOTHROW(__LIBCCALL __ieee754_inff)(void) {
	__IEEE754_FLOAT_TYPE__ __res;
	__LIBM_SET_FLOAT_WORD(__res, __UINT32_C(0x7f800000));
	return __res;
}
#endif /* !__ieee754_inff */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_inf
__LIBM_LOCAL_FUNC(inf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
__NOTHROW(__LIBCCALL __ieee754_inf)(void) {
	__IEEE754_DOUBLE_TYPE__ __res;
	__LIBM_INSERT_WORDS(__res,
	                    __UINT32_C(0x7ff00000),
	                    __UINT32_C(0x00000000));
	return __res;
}
#endif /* !__ieee754_inf */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_infl
__LIBM_LOCAL_FUNC(infl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
__NOTHROW(__LIBCCALL __ieee854_infl)(void) {
	__IEEE854_LONG_DOUBLE_TYPE__ __res;
	__LIBM_SET_LDOUBLE_WORDS(__res,
	                         __UINT16_C(0x7fff),
	                         __UINT32_C(0x80000000),
	                         __UINT32_C(0x00000000));
	return __res;
}
#endif /* !__ieee854_infl */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_INF_H */
