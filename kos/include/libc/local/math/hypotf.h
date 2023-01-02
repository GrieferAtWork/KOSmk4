/* HASH CRC-32:0xf281549f */
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
#ifndef __local_hypotf_defined
#define __local_hypotf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE__hypot) || defined(__CRT_HAVE___hypot) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_hypot_defined
#define __local___localdep_hypot_defined
#if __has_builtin(__builtin_hypot) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypot)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_hypot,(double __x, double __y),hypot,{ return __builtin_hypot(__x, __y); })
#elif defined(__CRT_HAVE_hypot)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_hypot,(double __x, double __y),hypot,(__x,__y))
#elif defined(__CRT_HAVE__hypot)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_hypot,(double __x, double __y),_hypot,(__x,__y))
#elif defined(__CRT_HAVE___hypot)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_hypot,(double __x, double __y),__hypot,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/hypot.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_hypot __LIBC_LOCAL_NAME(hypot)
#else /* ... */
#undef __local___localdep_hypot_defined
#endif /* !... */
#endif /* !__local___localdep_hypot_defined */
__NAMESPACE_LOCAL_END
#include <libm/finite.h>
#include <libm/matherr.h>
#include <libm/hypot.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(hypotf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(hypotf))(float __x, float __y) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	float __result = __LIBM_MATHFUN2F(hypot, __y, __x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUNIF(finite, __result) &&
	    __LIBM_MATHFUNIF(finite, __x) && __LIBM_MATHFUNIF(finite, __y))
		return __kernel_standard_f(__x, __y, __result, __LIBM_KMATHERRF_HYPOT); /* hypot overflow */
	return __result;
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_hypot)((double)__x, (double)__y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_hypotf_defined
#define __local___localdep_hypotf_defined
#define __localdep_hypotf __LIBC_LOCAL_NAME(hypotf)
#endif /* !__local___localdep_hypotf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_hypot || __CRT_HAVE__hypot || __CRT_HAVE___hypot || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_hypotf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_hypot && !__CRT_HAVE__hypot && !__CRT_HAVE___hypot && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_hypotf_defined */
