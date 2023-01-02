/* HASH CRC-32:0xe66687bd */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_sqrtl_defined
#define __local_sqrtl_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sqrt_defined
#define __local___localdep_sqrt_defined
#if __has_builtin(__builtin_sqrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrt)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sqrt,(double __x),sqrt,{ return __builtin_sqrt(__x); })
#elif defined(__CRT_HAVE_sqrt)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sqrt,(double __x),sqrt,(__x))
#elif defined(__CRT_HAVE___sqrt)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sqrt,(double __x),__sqrt,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/sqrt.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sqrt __LIBC_LOCAL_NAME(sqrt)
#else /* ... */
#undef __local___localdep_sqrt_defined
#endif /* !... */
#endif /* !__local___localdep_sqrt_defined */
__NAMESPACE_LOCAL_END
#include <libm/fcomp.h>
#include <libm/nan.h>
#include <libm/matherr.h>
#include <libm/sqrt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sqrtl) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sqrtl))(__LONGDOUBLE __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2L(isless, __x, 0.0L))
		return __kernel_standard_l(__x, __x, __LIBM_MATHFUN1IL(nan, ""), __LIBM_KMATHERRL_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUNL(sqrt, __x);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)(__NAMESPACE_LOCAL_SYM __localdep_sqrt)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sqrtl_defined
#define __local___localdep_sqrtl_defined
#define __localdep_sqrtl __LIBC_LOCAL_NAME(sqrtl)
#endif /* !__local___localdep_sqrtl_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_sqrtl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_sqrt && !__CRT_HAVE___sqrt && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_sqrtl_defined */
