/* HASH CRC-32:0x78f60420 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_atanf_defined
#define __local_atanf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_atan_defined
#define __local___localdep_atan_defined
#if __has_builtin(__builtin_atan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan,(double __x),atan,{ return __builtin_atan(__x); })
#elif defined(__CRT_HAVE_atan)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan,(double __x),atan,(__x))
#elif defined(__CRT_HAVE___atan)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan,(double __x),__atan,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/atan.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_atan __LIBC_LOCAL_NAME(atan)
#else /* ... */
#undef __local___localdep_atan_defined
#endif /* !... */
#endif /* !__local___localdep_atan_defined */
__NAMESPACE_LOCAL_END
#include <libm/fcomp.h>
#include <libm/fabs.h>
#include <libm/matherr.h>
#include <libm/inf.h>
#include <libm/atan.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(atanf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(atanf))(float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2F(isgreaterequal, __LIBM_MATHFUNF(fabs, __x), 1.0f)) {
		return __kernel_standard_f(__x, __x, __LIBM_MATHFUN0F(inf),
		                         __LIBM_MATHFUNF(fabs, __x) > 1.0f
		                         ? __LIBM_KMATHERRF_ATANH_PLUSONE /* atanh(|x|>1) */
		                         : __LIBM_KMATHERRF_ATANH_ONE);   /* atanh(|x|==1) */
	}
	return __LIBM_MATHFUNF(atan, __x);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_atan)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_atanf_defined
#define __local___localdep_atanf_defined
#define __localdep_atanf __LIBC_LOCAL_NAME(atanf)
#endif /* !__local___localdep_atanf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_atan || __CRT_HAVE___atan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_atanf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_atan && !__CRT_HAVE___atan && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_atanf_defined */
