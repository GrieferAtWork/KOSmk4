/* HASH CRC-32:0xdc170f04 */
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
#ifndef __local___fpclassifyl_defined
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE___fpclassify) || defined(__CRT_HAVE__dclass) || defined(__CRT_HAVE_fpclassify)
#define __local___fpclassifyl_defined 1
#include <libm/fpclassify.h>
/* Dependency: "__fpclassify" from "math" */
#ifndef ____localdep___fpclassify_defined
#define ____localdep___fpclassify_defined 1
#ifdef __CRT_HAVE___fpclassify
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassify,(double __x),__fpclassify,(__x))
#elif defined(__CRT_HAVE__dclass)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassify,(double __x),_dclass,(__x))
#elif defined(__CRT_HAVE_fpclassify)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassify,(double __x),fpclassify,(__x))
#else /* LIBC: __fpclassify */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/__fpclassify.h>
#define __localdep___fpclassify (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__fpclassify))
#else /* CUSTOM: __fpclassify */
#undef ____localdep___fpclassify_defined
#endif /* __fpclassify... */
#endif /* __fpclassify... */
#endif /* !____localdep___fpclassify_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__fpclassifyl) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(__fpclassifyl))(__LONGDOUBLE __x) {
#line 2780 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return __ieee854_fpclassifyl((__IEEE854_LONG_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_fpclassify((__IEEE754_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return __ieee754_fpclassifyf((__IEEE754_FLOAT_TYPE__)__x);
#else /* ... */
	return __localdep___fpclassify((double)__x);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE___fpclassify || __CRT_HAVE__dclass || __CRT_HAVE_fpclassify */
#endif /* !__local___fpclassifyl_defined */
