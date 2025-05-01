/* HASH CRC-32:0x3d56005c */
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
#ifndef __local_y1l_defined
#define __local_y1l_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_y1) || defined(__CRT_HAVE__y1) || defined(__CRT_HAVE___y1) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
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
#ifndef __local___localdep_y1_defined
#define __local___localdep_y1_defined
#if __has_builtin(__builtin_y1) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y1)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_y1,(double __x),y1,{ return __builtin_y1(__x); })
#elif defined(__CRT_HAVE_y1)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_y1,(double __x),y1,(__x))
#elif defined(__CRT_HAVE__y1)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_y1,(double __x),_y1,(__x))
#elif defined(__CRT_HAVE___y1)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_y1,(double __x),__y1,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/y1.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_y1 __LIBC_LOCAL_NAME(y1)
#else /* ... */
#undef __local___localdep_y1_defined
#endif /* !... */
#endif /* !__local___localdep_y1_defined */
__NAMESPACE_LOCAL_END
#include <libm/fcomp.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/y1.h>
#include <asm/crt/fenv.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(y1l) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(y1l))(__LONGDOUBLE __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2L(islessequal, __x, 0.0L) ||
	     __LIBM_MATHFUNI2L(isgreater, __x, 1.41484755040568800000e+16 /*X_TLOSS*/))) {
		if (__x < 0.0L) {
#if (defined(__CRT_HAVE_feraiseexcept) || defined(__arch_feraiseexcept)) && defined(__FE_INVALID)
			(__NAMESPACE_LOCAL_SYM __localdep_feraiseexcept)(__FE_INVALID);
#endif /* (__CRT_HAVE_feraiseexcept || __arch_feraiseexcept) && __FE_INVALID */
			return __kernel_standard_l(__x, __x, -__HUGE_VALL, __LIBM_KMATHERRL_Y1_MINUS);
		} else if (__x == 0.0L) {
			return __kernel_standard_l(__x, __x, -__HUGE_VALL, __LIBM_KMATHERRL_Y1_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard_l(__x, __x, 0.0f, __LIBM_KMATHERRL_Y1_TLOSS);
		}
	}
	return __LIBM_MATHFUNL(y1, __x);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)(__NAMESPACE_LOCAL_SYM __localdep_y1)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_y1l_defined
#define __local___localdep_y1l_defined
#define __localdep_y1l __LIBC_LOCAL_NAME(y1l)
#endif /* !__local___localdep_y1l_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_y1 || __CRT_HAVE__y1 || __CRT_HAVE___y1 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_y1l_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_y1 && !__CRT_HAVE__y1 && !__CRT_HAVE___y1 && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_y1l_defined */
