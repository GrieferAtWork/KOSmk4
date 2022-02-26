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
#ifndef _LIBM_SIGNBIT_H
#define _LIBM_SIGNBIT_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <ieee754.h>

#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("f")
#pragma push_macro("d")
#pragma push_macro("ieee")
#pragma push_macro("negative")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef f
#undef d
#undef ieee
#undef negative

#ifdef __IEEE754_FLOAT_TYPE__
/* Written for KOS */
__LIBM_LOCAL_FUNC(signbitf) __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee754_signbitf)(__IEEE754_FLOAT_TYPE__ __x) {
	union ieee754_float __d;
	__d.f = __x;
	return __d.ieee.negative;
}
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
/* Written for KOS */
__LIBM_LOCAL_FUNC(signbit) __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee754_signbit)(__IEEE754_DOUBLE_TYPE__ __x) {
	union ieee754_double __d;
	__d.d = __x;
	return __d.ieee.negative;
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* Written for KOS */
__LIBM_LOCAL_FUNC(signbitl) __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee854_signbitl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	union ieee854_long_double __d;
	__d.d = __x;
	return __d.ieee.negative;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("negative")
#pragma pop_macro("ieee")
#pragma pop_macro("d")
#pragma pop_macro("f")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_SIGNBIT_H */
