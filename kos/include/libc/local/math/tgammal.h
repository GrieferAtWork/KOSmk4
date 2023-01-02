/* HASH CRC-32:0xf65eb5ae */
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
#ifndef __local_tgammal_defined
#define __local_tgammal_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tgamma_defined
#define __local___localdep_tgamma_defined
#if __has_builtin(__builtin_tgamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgamma)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tgamma,(double __x),tgamma,{ return __builtin_tgamma(__x); })
#elif defined(__CRT_HAVE_tgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tgamma,(double __x),tgamma,(__x))
#elif defined(__CRT_HAVE___tgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tgamma,(double __x),__tgamma,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/tgamma.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tgamma __LIBC_LOCAL_NAME(tgamma)
#else /* ... */
#undef __local___localdep_tgamma_defined
#endif /* !... */
#endif /* !__local___localdep_tgamma_defined */
__NAMESPACE_LOCAL_END
#include <libm/fcomp.h>
#include <libm/isinf.h>
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/tgamma.h>
#include <libm/floor.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tgammal) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(tgammal))(__LONGDOUBLE __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	int __my_signgam;
	__LONGDOUBLE __result = __LIBM_MATHFUN2IL(tgamma, __x, &__my_signgam);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUN1IL(finite, __result) &&
	    (__LIBM_MATHFUN1IL(finite, __x) || __LIBM_MATHFUN1IL(isinf, __x) < 0)) {
		if (__x == 0.0L)
			return __kernel_standard_l(__x, __x, __result, __LIBM_KMATHERRL_TGAMMA_ZERO); /* tgamma pole */
		if (__LIBM_MATHFUNL(floor, __x) == __x && __x < 0.0L)
			return __kernel_standard_l(__x, __x, __result, __LIBM_KMATHERRL_TGAMMA_MINUS); /* tgamma domain */
		if (__result == 0.0L)
			return __kernel_standard_l(__x, __x, __result, __LIBM_KMATHERRL_TGAMMA_UNDERFLOW); /* tgamma underflow */
		return __kernel_standard_l(__x, __x, __result, __LIBM_KMATHERRL_TGAMMA_OVERFLOW);      /* tgamma overflow */
	}
	return __my_signgam < 0 ? -__result : __result;
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)(__NAMESPACE_LOCAL_SYM __localdep_tgamma)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tgammal_defined
#define __local___localdep_tgammal_defined
#define __localdep_tgammal __LIBC_LOCAL_NAME(tgammal)
#endif /* !__local___localdep_tgammal_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_tgamma || __CRT_HAVE___tgamma || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_tgammal_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_tgamma && !__CRT_HAVE___tgamma && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_tgammal_defined */
