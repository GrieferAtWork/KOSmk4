/* HASH CRC-32:0x941be98b */
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
#ifndef __local_log1pl_defined
#define __local_log1pl_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
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
#ifndef __local___localdep_log1p_defined
#define __local___localdep_log1p_defined
#if __has_builtin(__builtin_log1p) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1p)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_log1p,(double __x),log1p,{ return __builtin_log1p(__x); })
#elif defined(__CRT_HAVE_log1p)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_log1p,(double __x),log1p,(__x))
#elif defined(__CRT_HAVE___log1p)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_log1p,(double __x),__log1p,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/log1p.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_log1p __LIBC_LOCAL_NAME(log1p)
#else /* ... */
#undef __local___localdep_log1p_defined
#endif /* !... */
#endif /* !__local___localdep_log1p_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log1p.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(log1pl) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(log1pl))(__LONGDOUBLE __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)



	if (__LIBM_MATHFUNI2L(islessequal, __x, -1.0L) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (__x == -1.0L) {
			(__NAMESPACE_LOCAL_SYM __localdep_feraiseexcept)(FE_DIVBYZERO);
			return __kernel_standard_l(__x, __x, -__HUGE_VALL, __LIBM_KMATHERRL_LOG_ZERO); /* log(0) */
		} else {
			(__NAMESPACE_LOCAL_SYM __localdep_feraiseexcept)(FE_INVALID);
			return __kernel_standard_l(__x, __x, __LIBM_MATHFUN1IL(nan, ""), __LIBM_KMATHERRL_LOG_MINUS); /* log(x<0) */
		}
	}
	return __LIBM_MATHFUNL(log1p, __x);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)(__NAMESPACE_LOCAL_SYM __localdep_log1p)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_log1pl_defined
#define __local___localdep_log1pl_defined
#define __localdep_log1pl __LIBC_LOCAL_NAME(log1pl)
#endif /* !__local___localdep_log1pl_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_log1p || __CRT_HAVE___log1p || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_log1pl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_log1p && !__CRT_HAVE___log1p && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_log1pl_defined */
