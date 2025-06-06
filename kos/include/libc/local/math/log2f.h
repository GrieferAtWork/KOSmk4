/* HASH CRC-32:0xd77a2ad5 */
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
#ifndef __local_log2f_defined
#define __local_log2f_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_feraiseexcept_defined
#define __local___localdep_feraiseexcept_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/fenv-impl.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_feraiseexcept) && defined(__arch_feraiseexcept)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(,int,__THROWING(...),__localdep_feraiseexcept,(int __excepts),feraiseexcept,{ return __arch_feraiseexcept(__excepts); })
#elif defined(__CRT_HAVE_feraiseexcept)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__THROWING(...),__localdep_feraiseexcept,(int __excepts),feraiseexcept,(__excepts))
#elif defined(__arch_feraiseexcept)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL int (__LIBCCALL __localdep_feraiseexcept)(int __excepts) __THROWS(...) { return __arch_feraiseexcept(__excepts); }
#else /* ... */
#undef __local___localdep_feraiseexcept_defined
#endif /* !... */
#endif /* !__local___localdep_feraiseexcept_defined */
#ifndef __local___localdep_log2_defined
#define __local___localdep_log2_defined
#if __has_builtin(__builtin_log2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_log2,(double __x),log2,{ return __builtin_log2(__x); })
#elif defined(__CRT_HAVE_log2)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_log2,(double __x),log2,(__x))
#elif defined(__CRT_HAVE___log2)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_log2,(double __x),__log2,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/log2.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_log2 __LIBC_LOCAL_NAME(log2)
#else /* ... */
#undef __local___localdep_log2_defined
#endif /* !... */
#endif /* !__local___localdep_log2_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log2.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(log2f) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(log2f))(float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2F(islessequal, __x, 0.0f)) {
		if (__x == 0.0f) {
#if (defined(__CRT_HAVE_feraiseexcept) || defined(__arch_feraiseexcept)) && defined(__FE_DIVBYZERO)
			(__NAMESPACE_LOCAL_SYM __localdep_feraiseexcept)(__FE_DIVBYZERO);
#endif /* (__CRT_HAVE_feraiseexcept || __arch_feraiseexcept) && __FE_DIVBYZERO */
			return __kernel_standard_f(__x, __x, -__HUGE_VALF,
			                         __LIBM_KMATHERRF_LOG2_ZERO); /* log2(0) */
		} else {
#if (defined(__CRT_HAVE_feraiseexcept) || defined(__arch_feraiseexcept)) && defined(__FE_INVALID)
			(__NAMESPACE_LOCAL_SYM __localdep_feraiseexcept)(__FE_INVALID);
#endif /* (__CRT_HAVE_feraiseexcept || __arch_feraiseexcept) && __FE_INVALID */
			return __kernel_standard_f(__x, __x, __LIBM_MATHFUN1IF(nan, ""),
			                         __LIBM_KMATHERRF_LOG2_MINUS); /* log2(x<0) */
		}
	}
	return __LIBM_MATHFUNF(log2, __x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_log2)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_log2f_defined
#define __local___localdep_log2f_defined
#define __localdep_log2f __LIBC_LOCAL_NAME(log2f)
#endif /* !__local___localdep_log2f_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_log2 || __CRT_HAVE___log2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_log2f_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_log2 && !__CRT_HAVE___log2 && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_log2f_defined */
