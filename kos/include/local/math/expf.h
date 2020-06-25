/* HASH CRC-32:0x663a1d1d */
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
#ifndef __local_expf_defined
#define __local_expf_defined 1
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: exp from math */
#ifndef __local___localdep_exp_defined
#define __local___localdep_exp_defined 1
#if __has_builtin(__builtin_exp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp)
/* Exponential function of X */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,__localdep_exp,(double __x),exp,{ return __builtin_exp(__x); })
#elif defined(__CRT_HAVE_exp)
/* Exponential function of X */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,__localdep_exp,(double __x),exp,(__x))
#elif defined(__CRT_HAVE___exp)
/* Exponential function of X */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,__localdep_exp,(double __x),__exp,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <local/math/exp.h>
__NAMESPACE_LOCAL_BEGIN
/* Exponential function of X */
#define __localdep_exp __LIBC_LOCAL_NAME(exp)
#else /* ... */
#undef __local___localdep_exp_defined
#endif /* !... */
#endif /* !__local___localdep_exp_defined */
__NAMESPACE_LOCAL_END
#include <libm/signbit.h>
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/exp.h>
__NAMESPACE_LOCAL_BEGIN
/* Exponential function of X */
__LOCAL_LIBC(expf) __ATTR_WUNUSED __DECL_SIMD_expf float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(expf))(float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	float __result;
	__result = __LIBM_MATHFUNF(exp, __x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (!__LIBM_MATHFUNF(finite, __result) || __result == 0.0f) &&
	    __LIBM_MATHFUNF(finite, __x)) {
		return __kernel_standard_f(__x, __x, __result,
		                         __LIBM_MATHFUNF(signbit, __x)
		                         ? __LIBM_KMATHERR_EXP_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP_OVERFLOW);
	}
	return __result;
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)__localdep_exp((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_expf_defined
#define __local___localdep_expf_defined 1
#define __localdep_expf __LIBC_LOCAL_NAME(expf)
#endif /* !__local___localdep_expf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_exp || __CRT_HAVE___exp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_expf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_exp && !__CRT_HAVE___exp && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_expf_defined */
