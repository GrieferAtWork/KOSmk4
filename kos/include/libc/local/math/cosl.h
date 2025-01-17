/* HASH CRC-32:0xe3047cfa */
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
#ifndef __local_cosl_defined
#define __local_cosl_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_cos_defined
#define __local___localdep_cos_defined
#if __has_builtin(__builtin_cos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cos)
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,__localdep_cos,(double __x),cos,{ return __builtin_cos(__x); })
#elif defined(__CRT_HAVE_cos)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,__localdep_cos,(double __x),cos,(__x))
#elif defined(__CRT_HAVE___cos)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,__localdep_cos,(double __x),__cos,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/cos.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cos __LIBC_LOCAL_NAME(cos)
#else /* ... */
#undef __local___localdep_cos_defined
#endif /* !... */
#endif /* !__local___localdep_cos_defined */
__NAMESPACE_LOCAL_END
#include <libm/isnan.h>
#include <libm/cos.h>
#include <libm/matherr.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cosl) __ATTR_WUNUSED __DECL_SIMD_cosl __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(cosl))(__LONGDOUBLE __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	__LONGDOUBLE __result = __LIBM_MATHFUNL(cos, __x);
	if (__LIBM_MATHFUNIL(isnan, __result) && !__LIBM_MATHFUNIL(isnan, __x))
		__result = __kernel_standard_l(__x, __x, __result, __LIBM_KMATHERRL_COS_INF);
	return __result;
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)(__NAMESPACE_LOCAL_SYM __localdep_cos)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cosl_defined
#define __local___localdep_cosl_defined
#define __localdep_cosl __LIBC_LOCAL_NAME(cosl)
#endif /* !__local___localdep_cosl_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_cos || __CRT_HAVE___cos || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_cosl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_cos && !__CRT_HAVE___cos && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_cosl_defined */
