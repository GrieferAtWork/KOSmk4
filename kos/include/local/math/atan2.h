/* HASH CRC-32:0xba693cc */
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
#ifndef __local_atan2_defined
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#define __local_atan2_defined 1
#include <bits/huge_val.h>

#include <libm/matherr.h>

#include <libm/atan2.h>
__NAMESPACE_LOCAL_BEGIN
/* Arc tangent of Y/X */
__LOCAL_LIBC(atan2) __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(atan2))(double __y,
                                               double __x) {
#line 144 "kos/src/libc/magic/math.c"
	if (__LIBM_LIB_VERSION == __LIBM_SVID && __x == 0.0 && __y == 0.0)
		return __kernel_standard(__y, __x, HUGE_VAL, __LIBM_KMATHERR_ATAN2); /* atan2(+-0,+-0) */
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_atan2((__IEEE754_DOUBLE_TYPE__)__y, (__IEEE754_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_atan2f((__IEEE754_FLOAT_TYPE__)__y, (__IEEE754_FLOAT_TYPE__)__x);
#else /* ... */
	return (double)__ieee854_atan2l((__IEEE854_LONG_DOUBLE_TYPE__)__y, (__IEEE854_LONG_DOUBLE_TYPE__)__x);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_atan2_defined */
