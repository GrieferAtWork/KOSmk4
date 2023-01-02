/* HASH CRC-32:0xbe1b8453 */
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
#ifndef __local_sqrtf_defined
#define __local_sqrtf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
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
__LOCAL_LIBC(sqrtf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sqrtf))(float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2F(isless, __x, 0.0f))
		return __kernel_standard_f(__x, __x, __LIBM_MATHFUN1IF(nan, ""), __LIBM_KMATHERRF_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUNF(sqrt, __x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_sqrt)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sqrtf_defined
#define __local___localdep_sqrtf_defined
#define __localdep_sqrtf __LIBC_LOCAL_NAME(sqrtf)
#endif /* !__local___localdep_sqrtf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_sqrtf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_sqrt && !__CRT_HAVE___sqrt && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_sqrtf_defined */
