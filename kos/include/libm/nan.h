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
#ifndef _LIBM_NAN_H
#define _LIBM_NAN_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <ieee754.h>

#include <libm/asm/nan.h>
#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_nanf
__LIBM_LOCAL_FUNC(nanf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_nanf)(char const *__UNUSED(__tagb)) {
	__IEEE754_FLOAT_TYPE__ __res;
	__LIBM_SET_FLOAT_WORD(__res, __UINT32_C(0x7fc00000));
	return __res;
}
#endif /* !__ieee754_nanf */
#ifndef __ieee754_snanf
__LIBM_LOCAL_FUNC(snanf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_snanf)(void) {
	__IEEE754_FLOAT_TYPE__ __res;
	__LIBM_SET_FLOAT_WORD(__res, __UINT32_C(0x7fa00000));
	return __res;
}
#endif /* !__ieee754_snanf */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_nan
__LIBM_LOCAL_FUNC(nan) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_nan)(char const *__UNUSED(__tagb)) {
	__IEEE754_DOUBLE_TYPE__ __res;
	__LIBM_INSERT_WORDS(__res,
	                    __UINT32_C(0x7ff80000),
	                    __UINT32_C(0x00000000));
	return __res;
}
#endif /* !__ieee754_nan */
#ifndef __ieee754_snan
__LIBM_LOCAL_FUNC(snan) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_snan)(void) {
	__IEEE754_DOUBLE_TYPE__ __res;
	__LIBM_INSERT_WORDS(__res,
	                    __UINT32_C(0x7ff40000),
	                    __UINT32_C(0x00000000));
	return __res;
}
#endif /* !__ieee754_snan */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_nanl
__LIBM_LOCAL_FUNC(nanl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_nanl)(char const *__UNUSED(__tagb)) {
	__IEEE854_LONG_DOUBLE_TYPE__ __res;
	__LIBM_SET_LDOUBLE_WORDS(__res,
	                         __UINT16_C(0x7fff),
	                         __UINT32_C(0xc0000000),
	                         __UINT32_C(0));
	return __res;
}
#endif /* !__ieee854_nanl */
#ifndef __ieee854_snanl
__LIBM_LOCAL_FUNC(snanl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_snanl)(void) {
	__IEEE854_LONG_DOUBLE_TYPE__ __res;
	__LIBM_SET_LDOUBLE_WORDS(__res,
	                         __UINT16_C(0x7fff),
	                         __UINT32_C(0xa0000000),
	                         __UINT32_C(0));
	return __res;
}
#endif /* !__ieee854_snanl */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_NAN_H */
