/* HASH CRC-32:0x7b5c68a5 */
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
#ifndef __local_logf_defined
#define __local_logf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_log_defined
#define __local___localdep_log_defined
#if __has_builtin(__builtin_log) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log)
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,__localdep_log,(double __x),log,{ return __builtin_log(__x); })
#elif defined(__CRT_HAVE_log)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,__localdep_log,(double __x),log,(__x))
#elif defined(__CRT_HAVE___log)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,__localdep_log,(double __x),__log,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/log.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_log __LIBC_LOCAL_NAME(log)
#else /* ... */
#undef __local___localdep_log_defined
#endif /* !... */
#endif /* !__local___localdep_log_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(logf) __ATTR_WUNUSED __DECL_SIMD_logf float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(logf))(float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)



	if (__LIBM_MATHFUNI2F(islessequal, __x, -1.0f) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (__x == -1.0f) {
			(__NAMESPACE_LOCAL_SYM __localdep_feraiseexcept)(FE_DIVBYZERO);
			return __kernel_standard_f(__x, __x, -__HUGE_VALF, __LIBM_KMATHERRF_LOG_ZERO); /* log(0) */
		} else {
			(__NAMESPACE_LOCAL_SYM __localdep_feraiseexcept)(FE_INVALID);
			return __kernel_standard_f(__x, __x, __LIBM_MATHFUN1IF(nan, ""), __LIBM_KMATHERRF_LOG_MINUS); /* log(x<0) */
		}
	}
	return __LIBM_MATHFUNF(log, __x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_log)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_logf_defined
#define __local___localdep_logf_defined
#define __localdep_logf __LIBC_LOCAL_NAME(logf)
#endif /* !__local___localdep_logf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_log || __CRT_HAVE___log || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_logf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_log && !__CRT_HAVE___log && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_logf_defined */
