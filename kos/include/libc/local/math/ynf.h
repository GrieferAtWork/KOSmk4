/* HASH CRC-32:0xbad2d928 */
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
#ifndef __local_ynf_defined
#define __local_ynf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_yn) || defined(__CRT_HAVE__yn) || defined(__CRT_HAVE___yn) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_feraiseexcept_defined
#define __local___localdep_feraiseexcept_defined
#ifdef __CRT_HAVE_feraiseexcept
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__THROWING(...),__localdep_feraiseexcept,(int __excepts),feraiseexcept,(__excepts))
#else /* __CRT_HAVE_feraiseexcept */
__NAMESPACE_LOCAL_END
#include <libc/local/fenv/feraiseexcept.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_feraiseexcept __LIBC_LOCAL_NAME(feraiseexcept)
#endif /* !__CRT_HAVE_feraiseexcept */
#endif /* !__local___localdep_feraiseexcept_defined */
#ifndef __local___localdep_yn_defined
#define __local___localdep_yn_defined
#if __has_builtin(__builtin_yn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_yn)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_yn,(int __n, double __x),yn,{ return __builtin_yn(__n, __x); })
#elif defined(__CRT_HAVE_yn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_yn,(int __n, double __x),yn,(__n,__x))
#elif defined(__CRT_HAVE__yn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_yn,(int __n, double __x),_yn,(__n,__x))
#elif defined(__CRT_HAVE___yn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_yn,(int __n, double __x),__yn,(__n,__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/yn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_yn __LIBC_LOCAL_NAME(yn)
#else /* ... */
#undef __local___localdep_yn_defined
#endif /* !... */
#endif /* !__local___localdep_yn_defined */
__NAMESPACE_LOCAL_END
#include <libm/fcomp.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/yn.h>
#include <bits/crt/fenv.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ynf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(ynf))(int __n, float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)



	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2F(islessequal, __x, 0.0f) ||
	     __LIBM_MATHFUNI2F(isgreater, __x, 1.41484755040568800000e+16 /*X_TLOSS*/))) {
		if (__x < 0.0f) {
			(__NAMESPACE_LOCAL_SYM __localdep_feraiseexcept)(FE_INVALID);
			return __kernel_standard_f(__n, __x, -__HUGE_VALF, __LIBM_KMATHERRF_YN_MINUS);
		} else if (__x == 0.0f) {
			return __kernel_standard_f(__n, __x, -__HUGE_VALF, __LIBM_KMATHERRF_YN_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard_f(__n, __x, 0.0f, __LIBM_KMATHERRF_YN_TLOSS);
		}
	}
	return __LIBM_MATHFUNIMF(yn, __n, __x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_yn)(__n, (double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ynf_defined
#define __local___localdep_ynf_defined
#define __localdep_ynf __LIBC_LOCAL_NAME(ynf)
#endif /* !__local___localdep_ynf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_yn || __CRT_HAVE__yn || __CRT_HAVE___yn || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_ynf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_yn && !__CRT_HAVE__yn && !__CRT_HAVE___yn && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_ynf_defined */
