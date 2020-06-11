/* HASH CRC-32:0x3d29d92a */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_atanl_defined
#define __local_atanl_defined 1
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: atan from math */
#ifndef __local___localdep_atan_defined
#define __local___localdep_atan_defined 1
#if __has_builtin(__builtin_atan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan)
/* Arc tangent of X */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan,(double __x),atan,{ return __builtin_atan(__x); })
#elif defined(__CRT_HAVE_atan)
/* Arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan,(double __x),atan,(__x))
#elif defined(__CRT_HAVE___atan)
/* Arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan,(double __x),__atan,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <local/math/atan.h>
__NAMESPACE_LOCAL_BEGIN
/* Arc tangent of X */
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
/* Arc tangent of X */
__LOCAL_LIBC(atanl) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(atanl))(__LONGDOUBLE __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2L(isgreaterequal, __LIBM_MATHFUNL(fabs, __x), 1.0L)) {
		return __kernel_standard_l(__x, __x, __LIBM_MATHFUN0L(inf),
		                         __LIBM_MATHFUNL(fabs, __x) > 1.0L
		                         ? __LIBM_KMATHERR_ATANH_PLUSONE /* atanh(|x|>1) */
		                         : __LIBM_KMATHERR_ATANH_ONE);   /* atanh(|x|==1) */
	}
	return __LIBM_MATHFUNL(atan, __x);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)__localdep_atan((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_atanl_defined
#define __local___localdep_atanl_defined 1
#define __localdep_atanl __LIBC_LOCAL_NAME(atanl)
#endif /* !__local___localdep_atanl_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_atan || __CRT_HAVE___atan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_atanl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_atan && !__CRT_HAVE___atan && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_atanl_defined */
