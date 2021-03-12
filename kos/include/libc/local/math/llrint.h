/* HASH CRC-32:0x4c5a6c0 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_llrint_defined
#define __local_llrint_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: rint from math */
#ifndef __local___localdep_rint_defined
#define __local___localdep_rint_defined 1
#if __has_builtin(__builtin_rint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_rint,(double __x),rint,{ return __builtin_rint(__x); })
#elif __has_builtin(__builtin_nearbyint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_rint,(double __x),nearbyint,{ return __builtin_nearbyint(__x); })
#elif defined(__CRT_HAVE_rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_rint,(double __x),rint,(__x))
#elif defined(__CRT_HAVE_nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_rint,(double __x),nearbyint,(__x))
#elif defined(__CRT_HAVE___rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_rint,(double __x),__rint,(__x))
#elif defined(__CRT_HAVE___nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_rint,(double __x),__nearbyint,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <ieee754.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/rint.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
#define __localdep_rint __LIBC_LOCAL_NAME(rint)
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local___localdep_rint_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !... */
#endif /* !__local___localdep_rint_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <libm/lrint.h>
__NAMESPACE_LOCAL_BEGIN
/* Round `x' to nearest integral value according to current rounding direction */
__LOCAL_LIBC(llrint) __ATTR_CONST __ATTR_WUNUSED __LONGLONG
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(llrint))(double __x) {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(llrint, __x);
#else /* __LIBM_MATHFUNI */
	return (__LONGLONG)__localdep_rint(__x);
#endif /* !__LIBM_MATHFUNI */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_llrint_defined
#define __local___localdep_llrint_defined 1
#define __localdep_llrint __LIBC_LOCAL_NAME(llrint)
#endif /* !__local___localdep_llrint_defined */
#endif /* !__local_llrint_defined */
