/* HASH CRC-32:0x474c7420 */
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
#ifndef __local_nanf_defined
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nan) || defined(__CRT_HAVE___nan)
#define __local_nanf_defined 1
#include <__crt.h>
#include <libm/nan.h>
/* Dependency: "nan" from "math" */
#ifndef ____localdep_nan_defined
#define ____localdep_nan_defined 1
#if __has_builtin(__builtin_nan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nan)
/* Return representation of qNaN for double type */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_nan,(char const *__tagb),nan,{ return __builtin_nan(__tagb); })
#elif defined(__CRT_HAVE_nan)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_nan,(char const *__tagb),nan,(__tagb))
#elif defined(__CRT_HAVE___nan)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_nan,(char const *__tagb),__nan,(__tagb))
#else /* LIBC: nan */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/nan.h>
/* Return representation of qNaN for double type */
#define __localdep_nan (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nan))
#else /* CUSTOM: nan */
#undef ____localdep_nan_defined
#endif /* nan... */
#endif /* nan... */
#endif /* !____localdep_nan_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return representation of qNaN for double type */
__LOCAL_LIBC(nanf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(nanf))(char const *__tagb) {
#line 772 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUN1IF(nan, __tagb);
#else /* __LIBM_MATHFUNF */
	return (float)__localdep_nan(__tagb);
#endif /* !__LIBM_MATHFUNF */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_nan || __CRT_HAVE___nan */
#endif /* !__local_nanf_defined */
