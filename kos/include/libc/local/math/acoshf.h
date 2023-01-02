/* HASH CRC-32:0xe9065b59 */
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
#ifndef __local_acoshf_defined
#define __local_acoshf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_acosh_defined
#define __local___localdep_acosh_defined
#if __has_builtin(__builtin_acosh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosh)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_acosh,(double __x),acosh,{ return __builtin_acosh(__x); })
#elif defined(__CRT_HAVE_acosh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_acosh,(double __x),acosh,(__x))
#elif defined(__CRT_HAVE___acosh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_acosh,(double __x),__acosh,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/acosh.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_acosh __LIBC_LOCAL_NAME(acosh)
#else /* ... */
#undef __local___localdep_acosh_defined
#endif /* !... */
#endif /* !__local___localdep_acosh_defined */
__NAMESPACE_LOCAL_END
#include <libm/fcomp.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/acosh.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(acoshf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(acoshf))(float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		__LIBM_MATHFUNI2F(isless, __x, 1.0f)) /* acosh(x<1) */
		return __kernel_standard_f(__x, __x, __LIBM_MATHFUN1IF(nan, ""), __LIBM_KMATHERRF_ACOSH);
	return __LIBM_MATHFUNF(acosh, __x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_acosh)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_acoshf_defined
#define __local___localdep_acoshf_defined
#define __localdep_acoshf __LIBC_LOCAL_NAME(acoshf)
#endif /* !__local___localdep_acoshf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_acosh || __CRT_HAVE___acosh || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_acoshf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_acosh && !__CRT_HAVE___acosh && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_acoshf_defined */
