/* HASH CRC-32:0x6c4a0967 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_finite_defined
#define __local_finite_defined
#include <__crt.h>
#include <ieee754.h>
#include <bits/math-constants.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isinf_defined
#define __local___localdep_isinf_defined
#if __has_builtin(__builtin_isinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),isinf,{ return __builtin_isinf(__x); })
#elif defined(__CRT_HAVE_isinf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),isinf,(__x))
#elif defined(__CRT_HAVE___isinf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),__isinf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isinf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isinf __LIBC_LOCAL_NAME(isinf)
#else /* ... */
#undef __local___localdep_isinf_defined
#endif /* !... */
#endif /* !__local___localdep_isinf_defined */
#ifndef __local___localdep_isnan_defined
#define __local___localdep_isnan_defined
#if __has_builtin(__builtin_isnan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnan)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnan,(double __x),isnan,{ return __builtin_isnan(__x); })
#elif defined(__CRT_HAVE_isnan)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnan,(double __x),isnan,(__x))
#elif defined(__CRT_HAVE__isnan)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnan,(double __x),_isnan,(__x))
#elif defined(__CRT_HAVE___isnan)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnan,(double __x),__isnan,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isnan.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isnan __LIBC_LOCAL_NAME(isnan)
#else /* ... */
#undef __local___localdep_isnan_defined
#endif /* !... */
#endif /* !__local___localdep_isnan_defined */
__NAMESPACE_LOCAL_END
#include <libm/finite.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(finite) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(finite))(double __x) {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(finite, __x);
#else /* __LIBM_MATHFUNI */
	return !(__NAMESPACE_LOCAL_SYM __localdep_isinf)(__x) && !(__NAMESPACE_LOCAL_SYM __localdep_isnan)(__x);
#endif /* !__LIBM_MATHFUNI */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_finite_defined
#define __local___localdep_finite_defined
#define __localdep_finite __LIBC_LOCAL_NAME(finite)
#endif /* !__local___localdep_finite_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || ((__CRT_HAVE_isinf || __CRT_HAVE___isinf || __INFINITY || __HUGE_VAL) && (__CRT_HAVE_isnan || __CRT_HAVE__isnan || __CRT_HAVE___isnan)) */
#undef __local_finite_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && ((!__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__INFINITY && !__HUGE_VAL) || (!__CRT_HAVE_isnan && !__CRT_HAVE__isnan && !__CRT_HAVE___isnan)) */
#endif /* !__local_finite_defined */
