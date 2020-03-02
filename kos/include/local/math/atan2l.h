/* HASH CRC-32:0x1c695238 */
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
#ifndef __local_atan2l_defined
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2)
#define __local_atan2l_defined 1
#include <bits/huge_vall.h>

#include <libm/matherr.h>

#include <libm/atan2.h>
/* Dependency: "atan2" from "math" */
#ifndef ____localdep_atan2_defined
#define ____localdep_atan2_defined 1
#if __has_builtin(__builtin_atan2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2)
/* Arc tangent of Y/X */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan2,(double __y, double __x),atan2,{ return __builtin_atan2(__y, __x); })
#elif defined(__CRT_HAVE_atan2)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan2,(double __y, double __x),atan2,(__y,__x))
#elif defined(__CRT_HAVE___atan2)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan2,(double __y, double __x),__atan2,(__y,__x))
#else /* LIBC: atan2 */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/atan2.h>
/* Arc tangent of Y/X */
#define __localdep_atan2 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2))
#else /* CUSTOM: atan2 */
#undef ____localdep_atan2_defined
#endif /* atan2... */
#endif /* atan2... */
#endif /* !____localdep_atan2_defined */

__NAMESPACE_LOCAL_BEGIN
/* Arc tangent of Y/X */
__LOCAL_LIBC(atan2l) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(atan2l))(__LONGDOUBLE __y,
                                                __LONGDOUBLE __x) {
#line 259 "kos/src/libc/magic/math.c"
	if (__LIBM_LIB_VERSION == __LIBM_SVID && __x == 0.0L && __y == 0.0L)
		return __kernel_standard_l(__y, __x, HUGE_VALL, __LIBM_KMATHERR_ATAN2); /* atan2(+-0,+-0) */
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
	return (__LONGDOUBLE)__ieee854_atan2l((__IEEE854_LONG_DOUBLE_TYPE__)__y, (__IEEE854_LONG_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
	return (__LONGDOUBLE)__ieee754_atan2((__IEEE754_DOUBLE_TYPE__)__y, (__IEEE754_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
	return (__LONGDOUBLE)__ieee754_atan2f((__IEEE754_FLOAT_TYPE__)__y, (__IEEE754_FLOAT_TYPE__)__x);
#else /* ... */
	return (__LONGDOUBLE)__localdep_atan2((double)__y, (double)__x);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_atan2 || __CRT_HAVE___atan2 */
#endif /* !__local_atan2l_defined */
