/* HASH CRC-32:0x532faf47 */
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
#ifndef __local_fmaxmagl_defined
#define __local_fmaxmagl_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_fmaxmag) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fmaxl_defined
#define __local___localdep_fmaxl_defined
#if __has_builtin(__builtin_fmaxl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaxl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmaxl,{ return __builtin_fmaxl(__x, __y); })
#elif defined(__CRT_HAVE_fmaxl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmaxl,(__x,__y))
#elif defined(__CRT_HAVE___fmaxl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fmaxl,(__x,__y))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_fmax) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmax,(__x,__y))
#elif defined(__CRT_HAVE___fmax) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fmax,(__x,__y))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/fmaxl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fmaxl __LIBC_LOCAL_NAME(fmaxl)
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep_fmaxl_defined */
#ifndef __local___localdep_fmaxmag_defined
#define __local___localdep_fmaxmag_defined
#ifdef __CRT_HAVE_fmaxmag
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_fmaxmag,(double __x, double __y),fmaxmag,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/fmaxmag.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fmaxmag __LIBC_LOCAL_NAME(fmaxmag)
#else /* ... */
#undef __local___localdep_fmaxmag_defined
#endif /* !... */
#endif /* !__local___localdep_fmaxmag_defined */
__NAMESPACE_LOCAL_END
#include <libm/fcomp.h>
#include <libm/fabs.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fmaxmagl) __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(fmaxmagl))(__LONGDOUBLE __x, __LONGDOUBLE __y) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)



	__LONGDOUBLE __x_abs = __LIBM_MATHFUNL(fabs, __x);
	__LONGDOUBLE __y_abs = __LIBM_MATHFUNL(fabs, __y);
	if (__LIBM_MATHFUN2L(isgreater, __x_abs, __y_abs))
		return __x;
	if (__LIBM_MATHFUN2L(isless, __x_abs, __y_abs))
		return __y;
	return (__NAMESPACE_LOCAL_SYM __localdep_fmaxl)(__x, __y);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)(__NAMESPACE_LOCAL_SYM __localdep_fmaxmag)((double)__x, (double)__y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fmaxmagl_defined
#define __local___localdep_fmaxmagl_defined
#define __localdep_fmaxmagl __LIBC_LOCAL_NAME(fmaxmagl)
#endif /* !__local___localdep_fmaxmagl_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_fmaxmag || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_fmaxmagl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_fmaxmag && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_fmaxmagl_defined */
