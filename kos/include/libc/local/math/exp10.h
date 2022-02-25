/* HASH CRC-32:0x47455961 */
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
#ifndef __local_exp10_defined
#define __local_exp10_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___signbit_defined
#define __local___localdep___signbit_defined
#ifdef __CRT_HAVE___signbit
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___signbit,(double __x),__signbit,(__x))
#elif defined(__CRT_HAVE__dsign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___signbit,(double __x),_dsign,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/__signbit.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___signbit __LIBC_LOCAL_NAME(__signbit)
#endif /* !... */
#endif /* !__local___localdep___signbit_defined */
#ifndef __local___localdep_exp_defined
#define __local___localdep_exp_defined
#if __has_builtin(__builtin_exp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,__localdep_exp,(double __x),exp,{ return __builtin_exp(__x); })
#elif defined(__CRT_HAVE_exp)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,__localdep_exp,(double __x),exp,(__x))
#elif defined(__CRT_HAVE___exp)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,__localdep_exp,(double __x),__exp,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/exp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_exp __LIBC_LOCAL_NAME(exp)
#else /* ... */
#undef __local___localdep_exp_defined
#endif /* !... */
#endif /* !__local___localdep_exp_defined */
#ifndef __local___localdep_feraiseexcept_defined
#define __local___localdep_feraiseexcept_defined
#ifdef __CRT_HAVE_feraiseexcept
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__THROWING,__localdep_feraiseexcept,(int __excepts),feraiseexcept,(__excepts))
#else /* __CRT_HAVE_feraiseexcept */
__NAMESPACE_LOCAL_END
#include <libc/local/fenv/feraiseexcept.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_feraiseexcept __LIBC_LOCAL_NAME(feraiseexcept)
#endif /* !__CRT_HAVE_feraiseexcept */
#endif /* !__local___localdep_feraiseexcept_defined */
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
#else /* ... */
__NAMESPACE_LOCAL_END
#include <bits/math-constants.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan)))
__NAMESPACE_LOCAL_END
#include <libc/local/math/finite.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_finite __LIBC_LOCAL_NAME(finite)
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || ((__CRT_HAVE_isinf || __CRT_HAVE___isinf || __INFINITY || __HUGE_VAL) && (__CRT_HAVE_isnan || __CRT_HAVE__isnan || __CRT_HAVE___isnan)) */
#undef __local___localdep_finite_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && ((!__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__INFINITY && !__HUGE_VAL) || (!__CRT_HAVE_isnan && !__CRT_HAVE__isnan && !__CRT_HAVE___isnan)) */
#endif /* !... */
#endif /* !__local___localdep_finite_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/floatcore.h>
#include <bits/crt/fenv.h>
#include <libm/matherr.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(exp10) __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(exp10))(double __x) {
	double __result;
	if ((__NAMESPACE_LOCAL_SYM __localdep_finite)(__x) && __x < __DBL_MIN_10_EXP__ - __DBL_DIG__ - 10) {
		(__NAMESPACE_LOCAL_SYM __localdep_feraiseexcept)(FE_UNDERFLOW);
		return 0.0;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_exp)(2.30258509299404568402 * __x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !(__NAMESPACE_LOCAL_SYM __localdep_finite)(__result) && (__NAMESPACE_LOCAL_SYM __localdep_finite)(__x)) {
		/* exp10 overflow (46) if x > 0, underflow (47) if x < 0. */
		return __kernel_standard(__x, __x, __result, (__NAMESPACE_LOCAL_SYM __localdep___signbit)(__x)
		                         ? __LIBM_KMATHERR_EXP10_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP10_OVERFLOW);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_exp10_defined
#define __local___localdep_exp10_defined
#define __localdep_exp10 __LIBC_LOCAL_NAME(exp10)
#endif /* !__local___localdep_exp10_defined */
#else /* __CRT_HAVE_exp || __CRT_HAVE___exp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_exp10_defined
#endif /* !__CRT_HAVE_exp && !__CRT_HAVE___exp && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_exp10_defined */
