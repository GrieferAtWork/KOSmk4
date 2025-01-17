/* HASH CRC-32:0x30a4a0ce */
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
#ifndef __local_remainderf_defined
#define __local_remainderf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_remainder_defined
#define __local___localdep_remainder_defined
#if __has_builtin(__builtin_remainder) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainder)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_remainder,(double __x, double __p),remainder,{ return __builtin_remainder(__x, __p); })
#elif __has_builtin(__builtin_drem) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_drem)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_remainder,(double __x, double __p),drem,{ return __builtin_drem(__x, __p); })
#elif defined(__CRT_HAVE_remainder)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_remainder,(double __x, double __p),remainder,(__x,__p))
#elif defined(__CRT_HAVE_drem)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_remainder,(double __x, double __p),drem,(__x,__p))
#elif defined(__CRT_HAVE___remainder)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_remainder,(double __x, double __p),__remainder,(__x,__p))
#elif defined(__CRT_HAVE___drem)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_remainder,(double __x, double __p),__drem,(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/remainder.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_remainder __LIBC_LOCAL_NAME(remainder)
#else /* ... */
#undef __local___localdep_remainder_defined
#endif /* !... */
#endif /* !__local___localdep_remainder_defined */
__NAMESPACE_LOCAL_END
#include <libm/matherr.h>
#include <libm/isnan.h>
#include <libm/isinf.h>
#include <libm/remainder.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(remainderf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(remainderf))(float __x, float __p) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	if (((__p == 0.0f && !__LIBM_MATHFUNIF(isnan, __x)) ||
	     (__LIBM_MATHFUNIF(isinf, __x) && !__LIBM_MATHFUNIF(isnan, __p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard_f(__x, __p, __p, __LIBM_KMATHERRF_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2F(remainder, __x, __p);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_remainder)((double)__x, (double)__p);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_remainderf_defined
#define __local___localdep_remainderf_defined
#define __localdep_remainderf __LIBC_LOCAL_NAME(remainderf)
#endif /* !__local___localdep_remainderf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_remainder || __CRT_HAVE_drem || __CRT_HAVE___remainder || __CRT_HAVE___drem || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_remainderf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_remainder && !__CRT_HAVE_drem && !__CRT_HAVE___remainder && !__CRT_HAVE___drem && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_remainderf_defined */
