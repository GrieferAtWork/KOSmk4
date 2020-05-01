/* HASH CRC-32:0x788d9ca5 */
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
#ifndef __local_expl_defined
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp)
#define __local_expl_defined 1
#include <__crt.h>
#include <bits/math-vector.h>
#include <bits/math-vector.h>
#include <libm/signbit.h>

#include <libm/matherr.h>

#include <libm/finite.h>

#include <libm/exp.h>
/* Dependency: "exp" from "math" */
#ifndef ____localdep_exp_defined
#define ____localdep_exp_defined 1
#if __has_builtin(__builtin_exp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp)
/* Exponential function of X */
__CEIREDIRECT(__DECL_SIMD_exp __ATTR_WUNUSED,double,__NOTHROW,__localdep_exp,(double __x),exp,{ return __builtin_exp(__x); })
#elif defined(__CRT_HAVE_exp)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_exp __ATTR_WUNUSED,double,__NOTHROW,__localdep_exp,(double __x),exp,(__x))
#elif defined(__CRT_HAVE___exp)
/* Exponential function of X */
__CREDIRECT(__DECL_SIMD_exp __ATTR_WUNUSED,double,__NOTHROW,__localdep_exp,(double __x),__exp,(__x))
#else /* LIBC: exp */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <local/math/exp.h>
/* Exponential function of X */
#define __localdep_exp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp))
#else /* CUSTOM: exp */
#undef ____localdep_exp_defined
#endif /* exp... */
#endif /* exp... */
#endif /* !____localdep_exp_defined */

__NAMESPACE_LOCAL_BEGIN
/* Exponential function of X */
__LOCAL_LIBC(expl) __DECL_SIMD_expl __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(expl))(__LONGDOUBLE __x) {
#line 420 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNL
	__LONGDOUBLE __result;
	__result = __LIBM_MATHFUNL(exp, __x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (!__LIBM_MATHFUNL(finite, __result) || __result == 0.0L) &&
	    __LIBM_MATHFUNL(finite, __x)) {
		return __kernel_standard_l(__x, __x, __result,
		                         __LIBM_MATHFUNL(signbit, __x)
		                         ? __LIBM_KMATHERR_EXP_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP_OVERFLOW);
	}
	return __result;
#else /* __LIBM_MATHFUNL */
	return (__LONGDOUBLE)__localdep_exp((double)__x);
#endif /* !__LIBM_MATHFUNL */
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_exp || __CRT_HAVE___exp */
#endif /* !__local_expl_defined */
