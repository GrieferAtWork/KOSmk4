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
#ifndef _I386_KOS_LIBM_ASM_ATAN_H
#define _I386_KOS_LIBM_ASM_ATAN_H 1

#include <__stdinc.h>

#include <libm/asm/builtin.h>

#if (!defined(__NO_FPU) && defined(__COMPILER_HAVE_GCC_ASM) && \
     !defined(__COMPILER_NO_GCC_ASM_FLOAT_CONSTRAINTS))
#include <__crt.h>

#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

/* NOTE: We manually encode `fld1' because having gcc fill in that
 *       register  for  us  produces sub-optimal  text  on x86_64:
 * >> __asm__("fpatan" : "=t" (__res) : "u" (__x), "0" (1.0) : "st(1)");
 * x86_64:
 *     movsd  CSWTCH.3+0xae0, %xmm1   # Loads 1.0 into %xmm1
 *     movsd  %xmm1, -0x10(%rsp)      # Convert %xmm1 (1.0) into float register
 *     fldl   -0x10(%rsp)             # push(1.0)
 *     movsd  %xmm0, -0x10(%rsp)      # Convert %xmm0 (x) into float register
 *     fldl   -0x10(%rsp)             # push(x)
 *     fxch   %st(1)                  # Exchange %st(0) (x) and %st(1) (1.0), so the FPU stack is { 1.0, x }
 *     fpatan                         # Do the thing!
 *     ...
 * i386:
 *     fldl   0x4(%esp)  # push(x)
 *     fld1              # push(1.0)
 *     fpatan            # Do the thing!
 *     ...
 * In other words: GCC thinks that it has to load the 1.0 as an xmm register...
 * So because of this, use different assembly when __SSE__ is enabled, so  that
 * the  x86_64  variant doesn't  do  the unnecessary  SSE  register conversion.
 * s.a. this bug report that I've filed:
 *     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=93985
 */

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_atanf
#define __ieee754_atanf __ieee754_atanf
__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_atanf)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __res;
#ifdef __SSE__
	__asm__("fld1\n\tfpatan" : "=t" (__res) : "0" (__x) : "st(1)");
#else /* __SSE__ */
	__asm__("fpatan" : "=t" (__res) : "u" (__x), "0" (1.0f) : "st(1)");
#endif /* !__SSE__ */
	return __res;
}
#endif /* !__ieee754_atanf */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_atan
#define __ieee754_atan __ieee754_atan
__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_atan)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __res;
#ifdef __SSE__
	__asm__("fld1\n\tfpatan" : "=t" (__res) : "0" (__x) : "st(1)");
#else /* __SSE__ */
	__asm__("fpatan" : "=t" (__res) : "u" (__x), "0" (1.0) : "st(1)");
#endif /* !__SSE__ */
	return __res;
}
#endif /* !__ieee754_atan */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_atanl
#define __ieee854_atanl __ieee854_atanl
__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_atanl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __res;
#ifdef __SSE__
	__asm__("fld1\n\tfpatan" : "=t" (__res) : "0" (__x) : "st(1)");
#else /* __SSE__ */
	__asm__("fpatan" : "=t" (__res) : "u" (__x), "0" (1.0L) : "st(1)");
#endif /* !__SSE__ */
	return __res;
}
#endif /* !__ieee854_atanl */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU && __COMPILER_HAVE_GCC_ASM && !__COMPILER_NO_GCC_ASM_FLOAT_CONSTRAINTS */

#endif /* !_I386_KOS_LIBM_ASM_ATAN_H */
