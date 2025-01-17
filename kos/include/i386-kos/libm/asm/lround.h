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
#ifndef _I386_KOS_LIBM_ASM_LROUND_H
#define _I386_KOS_LIBM_ASM_LROUND_H 1

#include <__stdinc.h>

#include <libm/asm/builtin.h>

#if (!defined(__NO_FPU) && defined(__COMPILER_HAVE_GCC_ASM) && \
     !defined(__COMPILER_NO_GCC_ASM_FLOAT_CONSTRAINTS))
#include <__crt.h>

#include <hybrid/typecore.h>

#include <asm/intrin-fpu.h>

#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_lroundf
#define __ieee754_lroundf __ieee754_lroundf
__LOCAL __ATTR_WUNUSED __ATTR_CONST long int
(__LIBCCALL __ieee754_lroundf)(__IEEE754_FLOAT_TYPE__ __x) {
	__UINT16_TYPE__ __cw;
	long int __res;
	__cw = __fnstcw();
	__fldcw((__cw & ~__UINT16_C(0x0c00) /* FCW_RC */) | __UINT16_C(0x0000) /* FCW_RC_NEAREST */);
#if __SIZEOF_LONG__ >= 8
	__asm__("fistpll %0" : "=m" (__res) : "t" (__x) : "st");
#else /* __SIZEOF_LONG__ >= 8 */
	__asm__("fistpl %0" : "=m" (__res) : "t" (__x) : "st");
#endif /* __SIZEOF_LONG__ < 8 */
	__fldcw(__cw);
	return __res;
}
#endif /* !__ieee754_lroundf */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __ieee754_llroundf
#define __ieee754_llroundf __ieee754_llroundf
__LOCAL __ATTR_WUNUSED __ATTR_CONST __LONGLONG
(__LIBCCALL __ieee754_llroundf)(__IEEE754_FLOAT_TYPE__ __x) {
	__UINT16_TYPE__ __cw;
	__LONGLONG __res;
	__cw = __fnstcw();
	__fldcw((__cw & ~__UINT16_C(0x0c00) /* FCW_RC */) | __UINT16_C(0x0000) /* FCW_RC_NEAREST */);
#if __SIZEOF_LONG_LONG__ >= 8
	__asm__("fistpll %0" : "=m" (__res) : "t" (__x) : "st");
#else /* __SIZEOF_LONG_LONG__ >= 8 */
	__asm__("fistpl %0" : "=m" (__res) : "t" (__x) : "st");
#endif /* __SIZEOF_LONG_LONG__ < 8 */
	__fldcw(__cw);
	return __res;
}
#endif /* !__ieee754_llroundf */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_lround
#define __ieee754_lround __ieee754_lround
__LOCAL __ATTR_WUNUSED __ATTR_CONST long int
(__LIBCCALL __ieee754_lround)(__IEEE754_DOUBLE_TYPE__ __x) {
	__UINT16_TYPE__ __cw;
	long int __res;
	__cw = __fnstcw();
	__fldcw((__cw & ~__UINT16_C(0x0c00) /* FCW_RC */) | __UINT16_C(0x0000) /* FCW_RC_NEAREST */);
#if __SIZEOF_LONG__ >= 8
	__asm__("fistpll %0" : "=m" (__res) : "t" (__x) : "st");
#else /* __SIZEOF_LONG__ >= 8 */
	__asm__("fistpl %0" : "=m" (__res) : "t" (__x) : "st");
#endif /* __SIZEOF_LONG__ < 8 */
	__fldcw(__cw);
	return __res;
}
#endif /* !__ieee754_lround */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __ieee754_llround
#define __ieee754_llround __ieee754_llround
__LOCAL __ATTR_WUNUSED __ATTR_CONST __LONGLONG
(__LIBCCALL __ieee754_llround)(__IEEE754_DOUBLE_TYPE__ __x) {
	__UINT16_TYPE__ __cw;
	__LONGLONG __res;
	__cw = __fnstcw();
	__fldcw((__cw & ~__UINT16_C(0x0c00) /* FCW_RC */) | __UINT16_C(0x0000) /* FCW_RC_NEAREST */);
#if __SIZEOF_LONG_LONG__ >= 8
	__asm__("fistpll %0" : "=m" (__res) : "t" (__x) : "st");
#else /* __SIZEOF_LONG_LONG__ >= 8 */
	__asm__("fistpl %0" : "=m" (__res) : "t" (__x) : "st");
#endif /* __SIZEOF_LONG_LONG__ < 8 */
	__fldcw(__cw);
	return __res;
}
#endif /* !__ieee754_llround */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_lroundl
#define __ieee854_lroundl __ieee854_lroundl
__LOCAL __ATTR_WUNUSED __ATTR_CONST long int
(__LIBCCALL __ieee854_lroundl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__UINT16_TYPE__ __cw;
	long int __res;
	__cw = __fnstcw();
	__fldcw((__cw & ~__UINT16_C(0x0c00) /* FCW_RC */) | __UINT16_C(0x0000) /* FCW_RC_NEAREST */);
#if __SIZEOF_LONG__ >= 8
	__asm__("fistpll %0" : "=m" (__res) : "t" (__x) : "st");
#else /* __SIZEOF_LONG__ >= 8 */
	__asm__("fistpl %0" : "=m" (__res) : "t" (__x) : "st");
#endif /* __SIZEOF_LONG__ < 8 */
	__fldcw(__cw);
	return __res;
}
#endif /* !__ieee854_lroundl */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __ieee854_llroundl
#define __ieee854_llroundl __ieee854_llroundl
__LOCAL __ATTR_WUNUSED __ATTR_CONST __LONGLONG
(__LIBCCALL __ieee854_llroundl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__UINT16_TYPE__ __cw;
	__LONGLONG __res;
	__cw = __fnstcw();
	__fldcw((__cw & ~__UINT16_C(0x0c00) /* FCW_RC */) | __UINT16_C(0x0000) /* FCW_RC_NEAREST */);
#if __SIZEOF_LONG_LONG__ >= 8
	__asm__("fistpll %0" : "=m" (__res) : "t" (__x) : "st");
#else /* __SIZEOF_LONG_LONG__ >= 8 */
	__asm__("fistpl %0" : "=m" (__res) : "t" (__x) : "st");
#endif /* __SIZEOF_LONG_LONG__ < 8 */
	__fldcw(__cw);
	return __res;
}
#endif /* !__ieee854_llroundl */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU && __COMPILER_HAVE_GCC_ASM && !__COMPILER_NO_GCC_ASM_FLOAT_CONSTRAINTS */

#endif /* !_I386_KOS_LIBM_ASM_LROUND_H */
