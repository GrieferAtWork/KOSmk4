/* HASH CRC-32:0x2f3a8051 */
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
#ifndef __local___issignalingl_defined
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE___issignaling) || defined(__CRT_HAVE_issignaling)
#define __local___issignalingl_defined 1
#include <libm/issignaling.h>
/* Dependency: "__issignaling" from "math" */
#ifndef ____localdep___issignaling_defined
#define ____localdep___issignaling_defined 1
#ifdef __CRT_HAVE___issignaling
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___issignaling,(double __x),__issignaling,(__x))
#elif defined(__CRT_HAVE_issignaling)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___issignaling,(double __x),issignaling,(__x))
#else /* LIBC: __issignaling */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/__issignaling.h>
#define __localdep___issignaling (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__issignaling))
#else /* CUSTOM: __issignaling */
#undef ____localdep___issignaling_defined
#endif /* __issignaling... */
#endif /* __issignaling... */
#endif /* !____localdep___issignaling_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__issignalingl) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(__issignalingl))(__LONGDOUBLE __x) {
#line 2141 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNL
	#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee754_issignaling((__IEEE754_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_issignalingf((__IEEE754_FLOAT_TYPE__)__x);
#else /* ... */
	return __ieee854_issignalingl((__IEEE854_LONG_DOUBLE_TYPE__)__x);
#endif /* !... */
#else /* __LIBM_MATHFUNL */
	return __localdep___issignaling((double)__x);
#endif /* !__LIBM_MATHFUNL */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE___issignaling || __CRT_HAVE_issignaling */
#endif /* !__local___issignalingl_defined */
