/* HASH CRC-32:0x5256a9df */
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
#ifndef __local_sqrtl_defined
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt)
#define __local_sqrtl_defined 1
#include <libm/pow.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the square root of X */
__LOCAL_LIBC(sqrtl) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sqrtl))(__LONGDOUBLE __x) {
#line 909 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNL
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2L(isless, __x, 0.0L))
		return __kernel_standard_l(__x, __x, __LIBM_MATHFUN1IL(nan, ""), __LIBM_KMATHERR_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUNL(__sqrt, __x);
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)__sqrt((double)__x);
#endif /* !__LIBM_MATHFUNL */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_sqrt || __CRT_HAVE___sqrt */
#endif /* !__local_sqrtl_defined */
