/* HASH CRC-32:0xe1753d54 */
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
#ifndef __local_atanhf_defined
#define __local_atanhf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_atanh_defined
#define __local___localdep_atanh_defined
#if __has_builtin(__builtin_atanh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanh)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atanh,(double __x),atanh,{ return __builtin_atanh(__x); })
#elif defined(__CRT_HAVE_atanh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atanh,(double __x),atanh,(__x))
#elif defined(__CRT_HAVE___atanh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atanh,(double __x),__atanh,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/atanh.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_atanh __LIBC_LOCAL_NAME(atanh)
#else /* ... */
#undef __local___localdep_atanh_defined
#endif /* !... */
#endif /* !__local___localdep_atanh_defined */
__NAMESPACE_LOCAL_END
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <bits/math-constants.h>
#include <libm/matherr.h>
#include <libm/nan.h>
#include <libm/atanh.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(atanhf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(atanhf))(float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2F(isgreaterequal, __LIBM_MATHFUNF(fabs, __x), 1.0f))
		return __kernel_standard_f(__x, __x, __HUGE_VALF,
		                         __LIBM_MATHFUNF(fabs, __x) > 1.0f ? __LIBM_KMATHERRF_ATANH_PLUSONE /* atanh(|x|>1) */
		                                                         : __LIBM_KMATHERRF_ATANH_ONE);   /* atanh(|x|==1) */
	return __LIBM_MATHFUNF(atanh, __x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_atanh)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_atanhf_defined
#define __local___localdep_atanhf_defined
#define __localdep_atanhf __LIBC_LOCAL_NAME(atanhf)
#endif /* !__local___localdep_atanhf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_atanh || __CRT_HAVE___atanh || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_atanhf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_atanh && !__CRT_HAVE___atanh && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_atanhf_defined */
