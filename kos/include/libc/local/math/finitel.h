/* HASH CRC-32:0x406dc5ad */
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
#ifndef __local_finitel_defined
#define __local_finitel_defined
#include <__crt.h>
#include <ieee754.h>
#include <hybrid/typecore.h>
#include <bits/math-constants.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || ((defined(__CRT_HAVE_isinfl) || defined(__CRT_HAVE___isinfl) || defined(__INFINITYL) || defined(__HUGE_VALL) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnanl) || defined(__CRT_HAVE___isnanl) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan))) || defined(__CRT_HAVE_finite) || defined(__CRT_HAVE___finite) || defined(__CRT_HAVE__finite) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan)))
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
#ifndef __local___localdep_isinfl_defined
#define __local___localdep_isinfl_defined
#if __has_builtin(__builtin_isinfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinfl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(__LONGDOUBLE __x),isinfl,{ return __builtin_isinfl(__x); })
#elif defined(__CRT_HAVE_isinfl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(__LONGDOUBLE __x),isinfl,(__x))
#elif defined(__CRT_HAVE___isinfl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(__LONGDOUBLE __x),__isinfl,(__x))
#elif defined(__CRT_HAVE_isinf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(__LONGDOUBLE __x),isinf,(__x))
#elif defined(__CRT_HAVE___isinf) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(__LONGDOUBLE __x),__isinf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__INFINITYL) || defined(__HUGE_VALL) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isinfl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isinfl __LIBC_LOCAL_NAME(isinfl)
#else /* ... */
#undef __local___localdep_isinfl_defined
#endif /* !... */
#endif /* !__local___localdep_isinfl_defined */
#ifndef __local___localdep_isnanl_defined
#define __local___localdep_isnanl_defined
#if __has_builtin(__builtin_isnanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(__LONGDOUBLE __x),isnanl,{ return __builtin_isnanl(__x); })
#elif defined(__CRT_HAVE_isnanl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(__LONGDOUBLE __x),isnanl,(__x))
#elif defined(__CRT_HAVE___isnanl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(__LONGDOUBLE __x),__isnanl,(__x))
#elif defined(__CRT_HAVE_isnan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(__LONGDOUBLE __x),isnan,(__x))
#elif defined(__CRT_HAVE___isnan) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isnanl,(__LONGDOUBLE __x),__isnan,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isnanl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isnanl __LIBC_LOCAL_NAME(isnanl)
#else /* ... */
#undef __local___localdep_isnanl_defined
#endif /* !... */
#endif /* !__local___localdep_isnanl_defined */
__NAMESPACE_LOCAL_END
#include <libm/finite.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(finitel) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(finitel))(__LONGDOUBLE __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || ((defined(__CRT_HAVE_isinfl) || defined(__CRT_HAVE___isinfl) || defined(__INFINITYL) || defined(__HUGE_VALL) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnanl) || defined(__CRT_HAVE___isnanl) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)))



	
#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(finite, __x);
#else /* __LIBM_MATHFUNIL */
	return !(__NAMESPACE_LOCAL_SYM __localdep_isinfl)(__x) && !(__NAMESPACE_LOCAL_SYM __localdep_isnanl)(__x);
#endif /* !__LIBM_MATHFUNIL */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || ((__CRT_HAVE_isinfl || __CRT_HAVE___isinfl || __INFINITYL || __HUGE_VALL || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL) && (__CRT_HAVE_isnanl || __CRT_HAVE___isnanl || __CRT_HAVE_isnan || __CRT_HAVE__isnan || __CRT_HAVE___isnan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
	return (__NAMESPACE_LOCAL_SYM __localdep_finite)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && ((!__CRT_HAVE_isinfl && !__CRT_HAVE___isinfl && !__INFINITYL && !__HUGE_VALL && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL) || (!__CRT_HAVE_isnanl && !__CRT_HAVE___isnanl && !__CRT_HAVE_isnan && !__CRT_HAVE__isnan && !__CRT_HAVE___isnan && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_finitel_defined
#define __local___localdep_finitel_defined
#define __localdep_finitel __LIBC_LOCAL_NAME(finitel)
#endif /* !__local___localdep_finitel_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || ((__CRT_HAVE_isinfl || __CRT_HAVE___isinfl || __INFINITYL || __HUGE_VALL || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __INFINITY || __HUGE_VAL) && (__CRT_HAVE_isnanl || __CRT_HAVE___isnanl || __CRT_HAVE_isnan || __CRT_HAVE__isnan || __CRT_HAVE___isnan)) || __CRT_HAVE_finite || __CRT_HAVE___finite || __CRT_HAVE__finite || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || ((__CRT_HAVE_isinf || __CRT_HAVE___isinf || __INFINITY || __HUGE_VAL) && (__CRT_HAVE_isnan || __CRT_HAVE__isnan || __CRT_HAVE___isnan)) */
#undef __local_finitel_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && ((!__CRT_HAVE_isinfl && !__CRT_HAVE___isinfl && !__INFINITYL && !__HUGE_VALL && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__INFINITY && !__HUGE_VAL) || (!__CRT_HAVE_isnanl && !__CRT_HAVE___isnanl && !__CRT_HAVE_isnan && !__CRT_HAVE__isnan && !__CRT_HAVE___isnan)) && !__CRT_HAVE_finite && !__CRT_HAVE___finite && !__CRT_HAVE__finite && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && ((!__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__INFINITY && !__HUGE_VAL) || (!__CRT_HAVE_isnan && !__CRT_HAVE__isnan && !__CRT_HAVE___isnan)) */
#endif /* !__local_finitel_defined */
