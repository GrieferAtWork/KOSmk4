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
#ifndef _I386_KOS_LIBM_ASM_SQRT_H
#define _I386_KOS_LIBM_ASM_SQRT_H 1

#include <__stdinc.h>

#include <libm/asm/builtin.h>

#if (!defined(__NO_FPU) && defined(__COMPILER_HAVE_GCC_ASM) && \
     !defined(__COMPILER_NO_GCC_ASM_FLOAT_CONSTRAINTS))
#include <__crt.h>

#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_sqrtf
#define __ieee754_sqrtf __ieee754_sqrtf
__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_sqrtf)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __res;
#ifdef __SSE__
	__asm__("sqrtss %1, %0" : "=x" (__res) : "xm" (__x));
#else /* __SSE__ */
	__asm__("fsqrt" : "=t" (__res) : "0" (__x));
#endif /* !__SSE__ */
	return __res;
}
#endif /* !__ieee754_sqrtf */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_sqrt
#define __ieee754_sqrt __ieee754_sqrt
__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_sqrt)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __res;
#ifdef __SSE__
	__asm__("sqrtsd %1, %0" : "=x" (__res) : "xm" (__x));
#else /* __SSE__ */
	__asm__("fsqrt" : "=t" (__res) : "0" (__x));
#endif /* !__SSE__ */
	return __res;
}
#endif /* !__ieee754_sqrt */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_sqrtl
#define __ieee854_sqrtl __ieee854_sqrtl
__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_sqrtl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __res;
	__asm__("fsqrt" : "=t" (__res) : "0" (__x));
	return __res;
}
#endif /* !__ieee854_sqrtl */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU && __COMPILER_HAVE_GCC_ASM && !__COMPILER_NO_GCC_ASM_FLOAT_CONSTRAINTS */

#endif /* !_I386_KOS_LIBM_ASM_SQRT_H */
