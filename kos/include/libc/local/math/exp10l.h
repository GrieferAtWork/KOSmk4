/* HASH CRC-32:0x1114a90a */
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
#ifndef __local_exp10l_defined
#define __local_exp10l_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__CRT_HAVE_expl) || defined(__CRT_HAVE___expl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___signbitl_defined
#define __local___localdep___signbitl_defined
#ifdef __CRT_HAVE___signbitl
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___signbitl,(__LONGDOUBLE __x),__signbitl,(__x))
#elif defined(__CRT_HAVE__ldsign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___signbitl,(__LONGDOUBLE __x),_ldsign,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/__signbitl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___signbitl __LIBC_LOCAL_NAME(__signbitl)
#endif /* !... */
#endif /* !__local___localdep___signbitl_defined */
#ifndef __local___localdep_expl_defined
#define __local___localdep_expl_defined
#if __has_builtin(__builtin_expl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expl)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expl,__LONGDOUBLE,__NOTHROW,__localdep_expl,(__LONGDOUBLE __x),expl,{ return __builtin_expl(__x); })
#elif defined(__CRT_HAVE_expl)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expl,__LONGDOUBLE,__NOTHROW,__localdep_expl,(__LONGDOUBLE __x),expl,(__x))
#elif defined(__CRT_HAVE___expl)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expl,__LONGDOUBLE,__NOTHROW,__localdep_expl,(__LONGDOUBLE __x),__expl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/expl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_expl __LIBC_LOCAL_NAME(expl)
#else /* ... */
#undef __local___localdep_expl_defined
#endif /* !... */
#endif /* !__local___localdep_expl_defined */
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
#ifndef __local___localdep_finitel_defined
#define __local___localdep_finitel_defined
#if __has_builtin(__builtin_finitel) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finitel)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finitel,(__LONGDOUBLE __x),finitel,{ return __builtin_finitel(__x); })
#elif defined(__CRT_HAVE_finitel)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finitel,(__LONGDOUBLE __x),finitel,(__x))
#elif defined(__CRT_HAVE___finitel)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_finitel,(__LONGDOUBLE __x),__finitel,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <bits/math-constants.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || ((defined(__CRT_HAVE_isinfl) || defined(__CRT_HAVE___isinfl) || defined(__INFINITYL) || defined(__HUGE_VALL) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnanl) || defined(__CRT_HAVE___isnanl) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan))) || defined(__CRT_HAVE_finite) || defined(__CRT_HAVE___finite) || defined(__CRT_HAVE__finite) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan)))
__NAMESPACE_LOCAL_END
#include <libc/local/math/finitel.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_finitel __LIBC_LOCAL_NAME(finitel)
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || ((__CRT_HAVE_isinfl || __CRT_HAVE___isinfl || __INFINITYL || __HUGE_VALL || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __INFINITY || __HUGE_VAL) && (__CRT_HAVE_isnanl || __CRT_HAVE___isnanl || __CRT_HAVE_isnan || __CRT_HAVE__isnan || __CRT_HAVE___isnan)) || __CRT_HAVE_finite || __CRT_HAVE___finite || __CRT_HAVE__finite || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || ((__CRT_HAVE_isinf || __CRT_HAVE___isinf || __INFINITY || __HUGE_VAL) && (__CRT_HAVE_isnan || __CRT_HAVE__isnan || __CRT_HAVE___isnan)) */
#undef __local___localdep_finitel_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && ((!__CRT_HAVE_isinfl && !__CRT_HAVE___isinfl && !__INFINITYL && !__HUGE_VALL && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__INFINITY && !__HUGE_VAL) || (!__CRT_HAVE_isnanl && !__CRT_HAVE___isnanl && !__CRT_HAVE_isnan && !__CRT_HAVE__isnan && !__CRT_HAVE___isnan)) && !__CRT_HAVE_finite && !__CRT_HAVE___finite && !__CRT_HAVE__finite && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && ((!__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__INFINITY && !__HUGE_VAL) || (!__CRT_HAVE_isnan && !__CRT_HAVE__isnan && !__CRT_HAVE___isnan)) */
#endif /* !... */
#endif /* !__local___localdep_finitel_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/floatcore.h>
#include <bits/crt/fenv.h>
#include <libm/matherr.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(exp10l) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(exp10l))(__LONGDOUBLE __x) {
	__LONGDOUBLE __result;
	if ((__NAMESPACE_LOCAL_SYM __localdep_finitel)(__x) && __x < __LDBL_MIN_10_EXP__ - __LDBL_DIG__ - 10) {
		(__NAMESPACE_LOCAL_SYM __localdep_feraiseexcept)(FE_UNDERFLOW);
		return 0.0L;
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_expl)(2.302585092994045684017991454684364208L * __x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !(__NAMESPACE_LOCAL_SYM __localdep_finitel)(__result) && (__NAMESPACE_LOCAL_SYM __localdep_finitel)(__x)) {
		/* exp10 overflow (46) if x > 0, underflow (47) if x < 0.  */
		return __kernel_standard_l(__x, __x, __result, (__NAMESPACE_LOCAL_SYM __localdep___signbitl)(__x)
		                           ? __LIBM_KMATHERRL_EXP10_UNDERFLOW
		                           : __LIBM_KMATHERRL_EXP10_OVERFLOW);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_exp10l_defined
#define __local___localdep_exp10l_defined
#define __localdep_exp10l __LIBC_LOCAL_NAME(exp10l)
#endif /* !__local___localdep_exp10l_defined */
#else /* __CRT_HAVE_expl || __CRT_HAVE___expl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_exp || __CRT_HAVE___exp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_exp10l_defined
#endif /* !__CRT_HAVE_expl && !__CRT_HAVE___expl && !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_exp && !__CRT_HAVE___exp && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_exp10l_defined */
