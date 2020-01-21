/* HASH CRC-32:0x8cbc8db */
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
#ifndef __local_pow10_defined
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
#define __local_pow10_defined 1
#include <bits/math-vector.h>
#include <libm/pow.h>
/* Dependency: "pow" from "math" */
#ifndef ____localdep_pow_defined
#define ____localdep_pow_defined 1
#if __has_builtin(__builtin_pow) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow)
/* Return X to the Y power */
__EXTERNINLINE __DECL_SIMD_pow __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_pow)(double __x, double __y) { return __builtin_pow(__x, __y); }
#elif defined(__CRT_HAVE_pow)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_pow __ATTR_WUNUSED,double,__NOTHROW,__localdep_pow,(double __x, double __y),pow,(__x,__y))
#elif defined(__CRT_HAVE___pow)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_pow __ATTR_WUNUSED,double,__NOTHROW,__localdep_pow,(double __x, double __y),__pow,(__x,__y))
#else /* LIBC: pow */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#include <local/math/pow.h>
/* Return X to the Y power */
#define __localdep_pow (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow))
#else /* CUSTOM: pow */
#undef ____localdep_pow_defined
#endif /* pow... */
#endif /* pow... */
#endif /* !____localdep_pow_defined */

__NAMESPACE_LOCAL_BEGIN
/* Another name occasionally used */
__LOCAL_LIBC(pow10) __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(pow10))(double __x) {
#line 1260 "kos/src/libc/magic/math.c"
	return __localdep_pow(10.0, __x);
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __CRT_HAVE_pow || __CRT_HAVE___pow */
#endif /* !__local_pow10_defined */
