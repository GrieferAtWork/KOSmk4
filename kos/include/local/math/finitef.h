/* HASH CRC-32:0xaa2e60c1 */
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
#ifndef __local_finitef_defined
#include <ieee754.h>
#if defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf)) && (defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE___isnan) || defined(__CRT_HAVE__isnan))) || defined(__CRT_HAVE_finite) || defined(__CRT_HAVE___finite) || defined(__CRT_HAVE__finite)
#define __local_finitef_defined 1
#include <libm/finite.h>
/* Dependency: "isinf" from "math" */
#ifndef ____localdep_isinf_defined
#define ____localdep_isinf_defined 1
#if __has_builtin(__builtin_isinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinf)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),isinf,{ return __builtin_isinf(__x); })
#elif defined(__CRT_HAVE_isinf)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),isinf,(__x))
#elif defined(__CRT_HAVE___isinf)
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),__isinf,(__x))
#else /* LIBC: isinf */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/isinf.h>
/* Return 0 if VALUE is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
#define __localdep_isinf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinf))
#else /* CUSTOM: isinf */
#undef ____localdep_isinf_defined
#endif /* isinf... */
#endif /* isinf... */
#endif /* !____localdep_isinf_defined */

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

/* Dependency: "finite" from "math" */
#ifndef ____localdep_finite_defined
#define ____localdep_finite_defined 1
#if __has_builtin(__builtin_finite) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finite)
/* Return nonzero if VALUE is finite and not NaN */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finite,(double __x),finite,{ return __builtin_finite(__x); })
#elif defined(__CRT_HAVE_finite)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finite,(double __x),finite,(__x))
#elif defined(__CRT_HAVE___finite)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finite,(double __x),__finite,(__x))
#elif defined(__CRT_HAVE__finite)
/* Return nonzero if VALUE is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finite,(double __x),_finite,(__x))
#else /* LIBC: finite */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf)) && (defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE___isnan) || defined(__CRT_HAVE__isnan)))
#include <local/math/finite.h>
/* Return nonzero if VALUE is finite and not NaN */
#define __localdep_finite (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finite))
#else /* CUSTOM: finite */
#undef ____localdep_finite_defined
#endif /* finite... */
#endif /* finite... */
#endif /* !____localdep_finite_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return nonzero if VALUE is finite and not NaN */
__LOCAL_LIBC(finitef) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(finitef))(float __x) {
#line 1501 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(finite, __x);
#else /* __LIBM_MATHFUNI */
	return !__localdep_isinf(__x) && !__localdep_isnan(__x);
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNF */
	return __localdep_finite((double)__x);
#endif /* !__LIBM_MATHFUNF */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || ((__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_isinf || __CRT_HAVE___isinf) && (__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_isnan || __CRT_HAVE___isnan || __CRT_HAVE__isnan)) || __CRT_HAVE_finite || __CRT_HAVE___finite || __CRT_HAVE__finite */
#endif /* !__local_finitef_defined */
