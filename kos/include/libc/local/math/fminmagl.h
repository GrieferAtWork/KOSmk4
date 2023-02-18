/* HASH CRC-32:0x4ccba50d */
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
#ifndef __local_fminmagl_defined
#define __local_fminmagl_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_fminmag) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fminl_defined
#define __local___localdep_fminl_defined
#if __has_builtin(__builtin_fminl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fminl,{ return __builtin_fminl(__x, __y); })
#elif defined(__CRT_HAVE_fminl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fminl,(__x,__y))
#elif defined(__CRT_HAVE___fminl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fminl,(__x,__y))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_fmin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmin,(__x,__y))
#elif defined(__CRT_HAVE___fmin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fmin,(__x,__y))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/fminl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fminl __LIBC_LOCAL_NAME(fminl)
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep_fminl_defined */
#ifndef __local___localdep_fminmag_defined
#define __local___localdep_fminmag_defined
#ifdef __CRT_HAVE_fminmag
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_fminmag,(double __x, double __y),fminmag,(__x,__y))
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
__LOCAL_LIBC(fminmagl) __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fminmagl))(__LONGDOUBLE __x, __LONGDOUBLE __y) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)



	__LONGDOUBLE __x_abs = __LIBM_MATHFUNL(fabs, __x);
	__LONGDOUBLE __y_abs = __LIBM_MATHFUNL(fabs, __y);
	if (__LIBM_MATHFUN2L(isless, __x_abs, __y_abs))
		return __x;
	if (__LIBM_MATHFUN2L(isgreater, __x_abs, __y_abs))
		return __y;
	return (__NAMESPACE_LOCAL_SYM __localdep_fminl)(__x, __y);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)(__NAMESPACE_LOCAL_SYM __localdep_fminmag)((double)__x, (double)__y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fminmagl_defined
#define __local___localdep_fminmagl_defined
#define __localdep_fminmagl __LIBC_LOCAL_NAME(fminmagl)
#endif /* !__local___localdep_fminmagl_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_fminmag || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_fminmagl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_fminmag && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_fminmagl_defined */
