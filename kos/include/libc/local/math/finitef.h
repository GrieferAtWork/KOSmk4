/* HASH CRC-32:0x8b7d4174 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_finitef_defined
#define __local_finitef_defined
#include <__crt.h>
#include <ieee754.h>
#include <bits/math-constants.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || ((defined(__CRT_HAVE_isinff) || defined(__CRT_HAVE___isinff) || defined(__INFINITYF) || defined(__HUGE_VALF) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnanf) || defined(__CRT_HAVE___isnanf) || defined(__CRT_HAVE__isnanf) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan))) || defined(__CRT_HAVE_finite) || defined(__CRT_HAVE___finite) || defined(__CRT_HAVE__finite) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_finite_defined
#define __local___localdep_finite_defined
#if __has_builtin(__builtin_finite) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finite)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finite,(double __x),finite,{ return __builtin_finite(__x); })
#elif defined(__CRT_HAVE_finite)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finite,(double __x),finite,(__x))
#elif defined(__CRT_HAVE___finite)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finite,(double __x),__finite,(__x))
#elif defined(__CRT_HAVE__finite)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finite,(double __x),_finite,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan)))
__NAMESPACE_LOCAL_END
#include <libc/local/math/finite.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_finite __LIBC_LOCAL_NAME(finite)
#else /* ... */
#undef __local___localdep_finite_defined
#endif /* !... */
#endif /* !__local___localdep_finite_defined */
#ifndef __local___localdep_isinff_defined
#define __local___localdep_isinff_defined
#if __has_builtin(__builtin_isinff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinff)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinff,(float __x),isinff,{ return __builtin_isinff(__x); })
#elif defined(__CRT_HAVE_isinff)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinff,(float __x),isinff,(__x))
#elif defined(__CRT_HAVE___isinff)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinff,(float __x),__isinff,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__INFINITYF) || defined(__HUGE_VALF) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isinff.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isinff __LIBC_LOCAL_NAME(isinff)
#else /* ... */
#undef __local___localdep_isinff_defined
#endif /* !... */
#endif /* !__local___localdep_isinff_defined */
#ifndef __local___localdep_isnanf_defined
#define __local___localdep_isnanf_defined
#if __has_builtin(__builtin_isnanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanf,(float __x),isnanf,{ return __builtin_isnanf(__x); })
#elif defined(__CRT_HAVE_isnanf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanf,(float __x),isnanf,(__x))
#elif defined(__CRT_HAVE___isnanf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanf,(float __x),__isnanf,(__x))
#elif defined(__CRT_HAVE__isnanf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanf,(float __x),_isnanf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isnanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isnanf __LIBC_LOCAL_NAME(isnanf)
#else /* ... */
#undef __local___localdep_isnanf_defined
#endif /* !... */
#endif /* !__local___localdep_isnanf_defined */
__NAMESPACE_LOCAL_END
#include <libm/finite.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(finitef) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(finitef))(float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || ((defined(__CRT_HAVE_isinff) || defined(__CRT_HAVE___isinff) || defined(__INFINITYF) || defined(__HUGE_VALF) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnanf) || defined(__CRT_HAVE___isnanf) || defined(__CRT_HAVE__isnanf) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)))



	
#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(finite, __x);
#else /* __LIBM_MATHFUNIF */
	return !(__NAMESPACE_LOCAL_SYM __localdep_isinff)(__x) && !(__NAMESPACE_LOCAL_SYM __localdep_isnanf)(__x);
#endif /* !__LIBM_MATHFUNIF */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || ((__CRT_HAVE_isinff || __CRT_HAVE___isinff || __INFINITYF || __HUGE_VALF || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL) && (__CRT_HAVE_isnanf || __CRT_HAVE___isnanf || __CRT_HAVE__isnanf || __CRT_HAVE_isnan || __CRT_HAVE__isnan || __CRT_HAVE___isnan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
	return (__NAMESPACE_LOCAL_SYM __localdep_finite)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && ((!__CRT_HAVE_isinff && !__CRT_HAVE___isinff && !__INFINITYF && !__HUGE_VALF && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL) || (!__CRT_HAVE_isnanf && !__CRT_HAVE___isnanf && !__CRT_HAVE__isnanf && !__CRT_HAVE_isnan && !__CRT_HAVE__isnan && !__CRT_HAVE___isnan && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_finitef_defined
#define __local___localdep_finitef_defined
#define __localdep_finitef __LIBC_LOCAL_NAME(finitef)
#endif /* !__local___localdep_finitef_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || ((__CRT_HAVE_isinff || __CRT_HAVE___isinff || __INFINITYF || __HUGE_VALF || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __INFINITY || __HUGE_VAL) && (__CRT_HAVE_isnanf || __CRT_HAVE___isnanf || __CRT_HAVE__isnanf || __CRT_HAVE_isnan || __CRT_HAVE__isnan || __CRT_HAVE___isnan)) || __CRT_HAVE_finite || __CRT_HAVE___finite || __CRT_HAVE__finite || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || ((__CRT_HAVE_isinf || __CRT_HAVE___isinf || __INFINITY || __HUGE_VAL) && (__CRT_HAVE_isnan || __CRT_HAVE__isnan || __CRT_HAVE___isnan)) */
#undef __local_finitef_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && ((!__CRT_HAVE_isinff && !__CRT_HAVE___isinff && !__INFINITYF && !__HUGE_VALF && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__INFINITY && !__HUGE_VAL) || (!__CRT_HAVE_isnanf && !__CRT_HAVE___isnanf && !__CRT_HAVE__isnanf && !__CRT_HAVE_isnan && !__CRT_HAVE__isnan && !__CRT_HAVE___isnan)) && !__CRT_HAVE_finite && !__CRT_HAVE___finite && !__CRT_HAVE__finite && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && ((!__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__INFINITY && !__HUGE_VAL) || (!__CRT_HAVE_isnan && !__CRT_HAVE__isnan && !__CRT_HAVE___isnan)) */
#endif /* !__local_finitef_defined */
