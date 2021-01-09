/* HASH CRC-32:0x6810153b */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_frexpl_defined
#define __local_frexpl_defined 1
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: frexp from math */
#ifndef __local___localdep_frexp_defined
#define __local___localdep_frexp_defined 1
#if __has_builtin(__builtin_frexp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexp)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CEIREDIRECT(__ATTR_NONNULL((2)),double,__NOTHROW_NCX,__localdep_frexp,(double __x, int *__pexponent),frexp,{ return __builtin_frexp(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexp)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_NONNULL((2)),double,__NOTHROW_NCX,__localdep_frexp,(double __x, int *__pexponent),frexp,(__x,__pexponent))
#elif defined(__CRT_HAVE___frexp)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_NONNULL((2)),double,__NOTHROW_NCX,__localdep_frexp,(double __x, int *__pexponent),__frexp,(__x,__pexponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/frexp.h>
__NAMESPACE_LOCAL_BEGIN
/* Break VALUE into a normalized fraction and an integral power of 2 */
#define __localdep_frexp __LIBC_LOCAL_NAME(frexp)
#else /* ... */
#undef __local___localdep_frexp_defined
#endif /* !... */
#endif /* !__local___localdep_frexp_defined */
__NAMESPACE_LOCAL_END
#include <libm/frexp.h>
__NAMESPACE_LOCAL_BEGIN
/* Break VALUE into a normalized fraction and an integral power of 2 */
__LOCAL_LIBC(frexpl) __ATTR_NONNULL((2)) __LONGDOUBLE
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(frexpl))(__LONGDOUBLE __x, int *__pexponent) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee754_frexp((__IEEE754_DOUBLE_TYPE__)__x, __pexponent);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_frexpf((__IEEE754_FLOAT_TYPE__)__x, __pexponent);
#else /* ... */
	return (__LONGDOUBLE)__ieee854_frexpl((__IEEE854_LONG_DOUBLE_TYPE__)__x, __pexponent);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)__localdep_frexp((double)__x, __pexponent);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_frexpl_defined
#define __local___localdep_frexpl_defined 1
#define __localdep_frexpl __LIBC_LOCAL_NAME(frexpl)
#endif /* !__local___localdep_frexpl_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_frexp || __CRT_HAVE___frexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_frexpl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_frexp && !__CRT_HAVE___frexp && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_frexpl_defined */
