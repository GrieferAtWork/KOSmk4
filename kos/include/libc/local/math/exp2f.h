/* HASH CRC-32:0x36c29f6b */
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
#ifndef __local_exp2f_defined
#define __local_exp2f_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_exp2_defined
#define __local___localdep_exp2_defined
#if __has_builtin(__builtin_exp2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_exp2,(double __x),exp2,{ return __builtin_exp2(__x); })
#elif defined(__CRT_HAVE_exp2)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_exp2,(double __x),exp2,(__x))
#elif defined(__CRT_HAVE___exp2)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_exp2,(double __x),__exp2,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/exp2.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_exp2 __LIBC_LOCAL_NAME(exp2)
#else /* ... */
#undef __local___localdep_exp2_defined
#endif /* !... */
#endif /* !__local___localdep_exp2_defined */
__NAMESPACE_LOCAL_END
#include <libm/exp2.h>
#include <libm/matherr.h>
#include <libm/finite.h>
#include <libm/signbit.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(exp2f) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(exp2f))(float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)



	float __result = __LIBM_MATHFUNF(exp2, __x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUNIF(finite, __result) && __LIBM_MATHFUNIF(finite, __x)) {
		return __kernel_standard_f(__x, __x, __result,
		                         __LIBM_MATHFUNIF(signbit, __x)
		                         ? __LIBM_KMATHERRF_EXP2_UNDERFLOW
		                         : __LIBM_KMATHERRF_EXP2_OVERFLOW);
	}
	return __result;
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_exp2)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_exp2f_defined
#define __local___localdep_exp2f_defined
#define __localdep_exp2f __LIBC_LOCAL_NAME(exp2f)
#endif /* !__local___localdep_exp2f_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_exp2 || __CRT_HAVE___exp2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_exp2f_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_exp2 && !__CRT_HAVE___exp2 && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_exp2f_defined */
