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
#ifndef _I386_KOS_LIBM_ASM_CEIL_H
#define _I386_KOS_LIBM_ASM_CEIL_H 1

#include <__stdinc.h>

#include <libm/asm/builtin.h>

#if (!defined(__NO_FPU) && defined(__COMPILER_HAVE_GCC_ASM) && \
     !defined(__COMPILER_NO_GCC_ASM_FLOAT_CONSTRAINTS))
#include <__crt.h>

#include <asm/intrin-fpu.h>

#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_ceilf
#define __ieee754_ceilf __ieee754_ceilf
__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_ceilf)(__IEEE754_FLOAT_TYPE__ __x) {
	__UINT16_TYPE__ __cw;
	__IEEE754_FLOAT_TYPE__ __res;
	__cw = __fnstcw();
	__fldcw((__cw & ~__UINT16_C(0x0c00) /* FCW_RC */) | __UINT16_C(0x0800) /* FCW_RC_UP */);
	__asm__ __volatile__("frndint" : "=t" (__res) : "0" (__x));
	__fldcw(__cw);
	return __res;
}
#endif /* !__ieee754_ceilf */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_ceil
#define __ieee754_ceil __ieee754_ceil
__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_ceil)(__IEEE754_DOUBLE_TYPE__ __x) {
	__UINT16_TYPE__ __cw;
	__IEEE754_DOUBLE_TYPE__ __res;
	__cw = __fnstcw();
	__fldcw((__cw & ~__UINT16_C(0x0c00) /* FCW_RC */) | __UINT16_C(0x0800) /* FCW_RC_UP */);
	__asm__ __volatile__("frndint" : "=t" (__res) : "0" (__x));
	__fldcw(__cw);
	return __res;
}
#endif /* !__ieee754_ceil */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_ceill
#define __ieee854_ceill __ieee854_ceill
__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_ceill)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__UINT16_TYPE__ __cw;
	__IEEE854_LONG_DOUBLE_TYPE__ __res;
	__cw = __fnstcw();
	__fldcw((__cw & ~__UINT16_C(0x0c00) /* FCW_RC */) | __UINT16_C(0x0800) /* FCW_RC_UP */);
	__asm__ __volatile__("frndint" : "=t" (__res) : "0" (__x));
	__fldcw(__cw);
	return __res;
}
#endif /* !__ieee854_ceill */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU && __COMPILER_HAVE_GCC_ASM && !__COMPILER_NO_GCC_ASM_FLOAT_CONSTRAINTS */

#endif /* !_I386_KOS_LIBM_ASM_CEIL_H */
