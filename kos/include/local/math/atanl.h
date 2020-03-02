/* HASH CRC-32:0x6490a332 */
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
#ifndef __local_atanl_defined
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan)
#define __local_atanl_defined 1
#include <libm/atan.h>
/* Dependency: "atan" from "math" */
#ifndef ____localdep_atan_defined
#define ____localdep_atan_defined 1
#if __has_builtin(__builtin_atan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan)
/* Arc tangent of X */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_atan,(double __x),atan,{ return __builtin_atan(__x); })
#elif defined(__CRT_HAVE_atan)
/* Arc tangent of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_atan,(double __x),atan,(__x))
#elif defined(__CRT_HAVE___atan)
/* Arc tangent of X */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_atan,(double __x),__atan,(__x))
#else /* LIBC: atan */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/atan.h>
/* Arc tangent of X */
#define __localdep_atan (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan))
#else /* CUSTOM: atan */
#undef ____localdep_atan_defined
#endif /* atan... */
#endif /* atan... */
#endif /* !____localdep_atan_defined */

__NAMESPACE_LOCAL_BEGIN
/* Arc tangent of X */
__LOCAL_LIBC(atanl) __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(atanl))(__LONGDOUBLE __x) {
#line 233 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee854_atanl((__IEEE854_LONG_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return (__LONGDOUBLE)__ieee754_atan((__IEEE754_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_atanf((__IEEE754_FLOAT_TYPE__)__x);
#else /* ... */
	return (__LONGDOUBLE)__localdep_atan((double)__x);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_atan || __CRT_HAVE___atan */
#endif /* !__local_atanl_defined */
