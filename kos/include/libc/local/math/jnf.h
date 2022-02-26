/* HASH CRC-32:0xb65d070f */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_jnf_defined
#define __local_jnf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_jn) || defined(__CRT_HAVE___jn) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_jn_defined
#define __local___localdep_jn_defined
#if __has_builtin(__builtin_jn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_jn)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_jn,(int __n, double __x),jn,{ return __builtin_jn(__n, __x); })
#elif defined(__CRT_HAVE_jn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_jn,(int __n, double __x),jn,(__n,__x))
#elif defined(__CRT_HAVE___jn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_jn,(int __n, double __x),__jn,(__n,__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/jn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_jn __LIBC_LOCAL_NAME(jn)
#else /* ... */
#undef __local___localdep_jn_defined
#endif /* !... */
#endif /* !__local___localdep_jn_defined */
__NAMESPACE_LOCAL_END
#include <libm/jn.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
#include <libm/fabs.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(jnf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(jnf))(int __n, float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_LIB_VERSION != __LIBM_POSIX &&
	    __LIBM_MATHFUNI2F(isgreater, __LIBM_MATHFUNF(fabs, __x), 1.41484755040568800000e+16 /*X_TLOSS*/))
		return __kernel_standard_f(__n, __x, 0.0f, __LIBM_KMATHERRF_JN_TLOSS); /* jn(n,|x|>X_TLOSS) */
	return __LIBM_MATHFUNIMF(jn, __n, __x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_jn)(__n, (double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_jnf_defined
#define __local___localdep_jnf_defined
#define __localdep_jnf __LIBC_LOCAL_NAME(jnf)
#endif /* !__local___localdep_jnf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_jn || __CRT_HAVE___jn || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_jnf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_jn && !__CRT_HAVE___jn && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_jnf_defined */
