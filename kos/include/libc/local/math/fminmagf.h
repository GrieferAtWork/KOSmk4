/* HASH CRC-32:0x4c54c43a */
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
#ifndef __local_fminmagf_defined
#define __local_fminmagf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_fminmag) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fminf_defined
#define __local___localdep_fminf_defined
#if __has_builtin(__builtin_fminf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_fminf,(float __x, float __y),fminf,{ return __builtin_fminf(__x, __y); })
#elif defined(__CRT_HAVE_fminf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_fminf,(float __x, float __y),fminf,(__x,__y))
#elif defined(__CRT_HAVE___fminf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_fminf,(float __x, float __y),__fminf,(__x,__y))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/fminf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fminf __LIBC_LOCAL_NAME(fminf)
#endif /* !... */
#endif /* !__local___localdep_fminf_defined */
#ifndef __local___localdep_fminmag_defined
#define __local___localdep_fminmag_defined
#ifdef __CRT_HAVE_fminmag
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_fminmag,(double __x, double __y),fminmag,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/fminmag.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fminmag __LIBC_LOCAL_NAME(fminmag)
#else /* ... */
#undef __local___localdep_fminmag_defined
#endif /* !... */
#endif /* !__local___localdep_fminmag_defined */
__NAMESPACE_LOCAL_END
#include <libm/fcomp.h>
#include <libm/fabs.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fminmagf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(fminmagf))(float __x, float __y) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)



	float __x_abs = __LIBM_MATHFUNF(fabs, __x);
	float __y_abs = __LIBM_MATHFUNF(fabs, __y);
	if (__LIBM_MATHFUN2F(isless, __x_abs, __y_abs))
		return __x;
	if (__LIBM_MATHFUN2F(isgreater, __x_abs, __y_abs))
		return __y;
	return (__NAMESPACE_LOCAL_SYM __localdep_fminf)(__x, __y);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_fminmag)((double)__x, (double)__y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fminmagf_defined
#define __local___localdep_fminmagf_defined
#define __localdep_fminmagf __LIBC_LOCAL_NAME(fminmagf)
#endif /* !__local___localdep_fminmagf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_fminmag || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_fminmagf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_fminmag && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_fminmagf_defined */
