/* HASH CRC-32:0xd877eac */
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
#ifndef __local_nextafterl_defined
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter)
#define __local_nextafterl_defined 1
#include <libm/nextafter.h>
/* Dependency: "nextafter" from "math" */
#ifndef ____localdep_nextafter_defined
#define ____localdep_nextafter_defined 1
#if __has_builtin(__builtin_nextafter) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafter)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_nextafter,(double __x, double __y),nextafter,{ return __builtin_nextafter(__x, __y); })
#elif defined(__CRT_HAVE_nextafter)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_nextafter,(double __x, double __y),nextafter,(__x,__y))
#elif defined(__CRT_HAVE___nextafter)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_nextafter,(double __x, double __y),__nextafter,(__x,__y))
#elif defined(__CRT_HAVE__nextafter)
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_nextafter,(double __x, double __y),_nextafter,(__x,__y))
#else /* LIBC: nextafter */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/nextafter.h>
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
#define __localdep_nextafter (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafter))
#else /* CUSTOM: nextafter */
#undef ____localdep_nextafter_defined
#endif /* nextafter... */
#endif /* nextafter... */
#endif /* !____localdep_nextafter_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return X + epsilon if X < Y, X - epsilon if X > Y */
__LOCAL_LIBC(nextafterl) __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(nextafterl))(__LONGDOUBLE __x,
                                                    __LONGDOUBLE __y) {
#line 907 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUN2L
	return __LIBM_MATHFUN2L(nextafter, __x, __y);
#else /* __LIBM_MATHFUN2L */
	return (__LONGDOUBLE)__localdep_nextafter((double)__x, (double)__y);
#endif /* !__LIBM_MATHFUN2L */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_nextafter || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter */
#endif /* !__local_nextafterl_defined */
