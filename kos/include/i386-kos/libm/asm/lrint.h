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
#ifndef _I386_KOS_LIBM_ASM_LRINT_H
#define _I386_KOS_LIBM_ASM_LRINT_H 1

#include <__stdinc.h>

#include <libm/asm/builtin.h>

#if (!defined(__NO_FPU) && defined(__COMPILER_HAVE_GCC_ASM) && \
     !defined(__COMPILER_NO_GCC_ASM_FLOAT_CONSTRAINTS))
#include <__crt.h>

#include <hybrid/typecore.h>

#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_lrintf
#define __ieee754_lrintf __ieee754_lrintf
__LOCAL __ATTR_WUNUSED __ATTR_CONST long int
(__LIBCCALL __ieee754_lrintf)(__IEEE754_FLOAT_TYPE__ __x) {
	long int __res;
#if __SIZEOF_LONG__ >= 8
	__asm__("fistpll %0" : "=m" (__res) : "t" (__x) : "st");
#else /* __SIZEOF_LONG__ >= 8 */
	__asm__("fistpl %0" : "=m" (__res) : "t" (__x) : "st");
#endif /* __SIZEOF_LONG__ < 8 */
	return __res;
}
#endif /* !__ieee754_lrintf */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __ieee754_llrintf
#define __ieee754_llrintf __ieee754_llrintf
__LOCAL __ATTR_WUNUSED __ATTR_CONST __LONGLONG
(__LIBCCALL __ieee754_llrintf)(__IEEE754_FLOAT_TYPE__ __x) {
	__LONGLONG __res;
#if __SIZEOF_LONG_LONG__ >= 8
	__asm__("fistpll %0" : "=m" (__res) : "t" (__x) : "st");
#else /* __SIZEOF_LONG_LONG__ >= 8 */
	__asm__("fistpl %0" : "=m" (__res) : "t" (__x) : "st");
#endif /* __SIZEOF_LONG_LONG__ < 8 */
	return __res;
}
#endif /* !__ieee754_llrintf */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_lrint
#define __ieee754_lrint __ieee754_lrint
__LOCAL __ATTR_WUNUSED __ATTR_CONST long int
(__LIBCCALL __ieee754_lrint)(__IEEE754_DOUBLE_TYPE__ __x) {
	long int __res;
#if __SIZEOF_LONG__ >= 8
	__asm__("fistpll %0" : "=m" (__res) : "t" (__x) : "st");
#else /* __SIZEOF_LONG__ >= 8 */
	__asm__("fistpl %0" : "=m" (__res) : "t" (__x) : "st");
#endif /* __SIZEOF_LONG__ < 8 */
	return __res;
}
#endif /* !__ieee754_lrint */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __ieee754_llrint
#define __ieee754_llrint __ieee754_llrint
__LOCAL __ATTR_WUNUSED __ATTR_CONST __LONGLONG
(__LIBCCALL __ieee754_llrint)(__IEEE754_DOUBLE_TYPE__ __x) {
	__LONGLONG __res;
#if __SIZEOF_LONG_LONG__ >= 8
	__asm__("fistpll %0" : "=m" (__res) : "t" (__x) : "st");
#else /* __SIZEOF_LONG_LONG__ >= 8 */
	__asm__("fistpl %0" : "=m" (__res) : "t" (__x) : "st");
#endif /* __SIZEOF_LONG_LONG__ < 8 */
	return __res;
}
#endif /* !__ieee754_llrint */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_lrintl
#define __ieee854_lrintl __ieee854_lrintl
__LOCAL __ATTR_WUNUSED __ATTR_CONST long int
(__LIBCCALL __ieee854_lrintl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	long int __res;
#if __SIZEOF_LONG__ >= 8
	__asm__("fistpll %0" : "=m" (__res) : "t" (__x) : "st");
#else /* __SIZEOF_LONG__ >= 8 */
	__asm__("fistpl %0" : "=m" (__res) : "t" (__x) : "st");
#endif /* __SIZEOF_LONG__ < 8 */
	return __res;
}
#endif /* !__ieee854_lrintl */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __ieee854_llrintl
#define __ieee854_llrintl __ieee854_llrintl
__LOCAL __ATTR_WUNUSED __ATTR_CONST __LONGLONG
(__LIBCCALL __ieee854_llrintl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__LONGLONG __res;
#if __SIZEOF_LONG_LONG__ >= 8
	__asm__("fistpll %0" : "=m" (__res) : "t" (__x) : "st");
#else /* __SIZEOF_LONG_LONG__ >= 8 */
	__asm__("fistpl %0" : "=m" (__res) : "t" (__x) : "st");
#endif /* __SIZEOF_LONG_LONG__ < 8 */
	return __res;
}
#endif /* !__ieee854_llrintl */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU && __COMPILER_HAVE_GCC_ASM && !__COMPILER_NO_GCC_ASM_FLOAT_CONSTRAINTS */

#endif /* !_I386_KOS_LIBM_ASM_LRINT_H */
