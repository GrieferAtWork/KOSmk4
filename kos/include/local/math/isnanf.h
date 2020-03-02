/* HASH CRC-32:0x297d3f01 */
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
#ifndef __local_isnanf_defined
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE___isnan) || defined(__CRT_HAVE__isnan)
#define __local_isnanf_defined 1
#include <libm/isnan.h>
/* Dependency: "isnan" from "math" */
#ifndef ____localdep_isnan_defined
#define ____localdep_isnan_defined 1
#if __has_builtin(__builtin_isnan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnan)
/* Return nonzero if VALUE is not a number */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnan,(double __x),isnan,{ return __builtin_isnan(__x); })
#elif defined(__CRT_HAVE_isnan)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnan,(double __x),isnan,(__x))
#elif defined(__CRT_HAVE___isnan)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnan,(double __x),__isnan,(__x))
#elif defined(__CRT_HAVE__isnan)
/* Return nonzero if VALUE is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnan,(double __x),_isnan,(__x))
#else /* LIBC: isnan */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/isnan.h>
/* Return nonzero if VALUE is not a number */
#define __localdep_isnan (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnan))
#else /* CUSTOM: isnan */
#undef ____localdep_isnan_defined
#endif /* isnan... */
#endif /* isnan... */
#endif /* !____localdep_isnan_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return nonzero if VALUE is not a number */
__LOCAL_LIBC(isnanf) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(isnanf))(float __x) {
#line 1504 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNIF(isnan, __x);
#else /* __LIBM_MATHFUNF */
	return __localdep_isnan((double)__x);
#endif /* !__LIBM_MATHFUNF */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_isnan || __CRT_HAVE___isnan || __CRT_HAVE__isnan */
#endif /* !__local_isnanf_defined */
