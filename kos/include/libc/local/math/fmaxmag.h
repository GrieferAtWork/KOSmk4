/* HASH CRC-32:0x1d2b379b */
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
#ifndef __local_fmaxmag_defined
#define __local_fmaxmag_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fmax_defined
#define __local___localdep_fmax_defined
#if __has_builtin(__builtin_fmax) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmax)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_fmax,(double __x, double __y),fmax,{ return __builtin_fmax(__x, __y); })
#elif defined(__CRT_HAVE_fmax)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_fmax,(double __x, double __y),fmax,(__x,__y))
#elif defined(__CRT_HAVE___fmax)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_fmax,(double __x, double __y),__fmax,(__x,__y))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/fmax.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fmax __LIBC_LOCAL_NAME(fmax)
#endif /* !... */
#endif /* !__local___localdep_fmax_defined */
__NAMESPACE_LOCAL_END
#include <libm/fcomp.h>
#include <libm/fabs.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fmaxmag) __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fmaxmag))(double __x, double __y) {
	double __x_abs = __LIBM_MATHFUN(fabs, __x);
	double __y_abs = __LIBM_MATHFUN(fabs, __y);
	if (__LIBM_MATHFUN2(isgreater, __x_abs, __y_abs))
		return __x;
	if (__LIBM_MATHFUN2(isless, __x_abs, __y_abs))
		return __y;
	return (__NAMESPACE_LOCAL_SYM __localdep_fmax)(__x, __y);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fmaxmag_defined
#define __local___localdep_fmaxmag_defined
#define __localdep_fmaxmag __LIBC_LOCAL_NAME(fmaxmag)
#endif /* !__local___localdep_fmaxmag_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_fmaxmag_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_fmaxmag_defined */
