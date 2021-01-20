/* HASH CRC-32:0x7029bc8b */
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
#ifndef __local_scalblnf_defined
#define __local_scalblnf_defined 1
#include <__crt.h>
#include <ieee754.h>
#include <hybrid/typecore.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: scalbln from math */
#ifndef __local___localdep_scalbln_defined
#define __local___localdep_scalbln_defined 1
#if __has_builtin(__builtin_scalbln) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbln)
/* Return X times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_scalbln,(double __x, long int __n),scalbln,{ return __builtin_scalbln(__x, __n); })
#elif defined(__CRT_HAVE_scalbln)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_scalbln,(double __x, long int __n),scalbln,(__x,__n))
#elif defined(__CRT_HAVE___scalbln)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_scalbln,(double __x, long int __n),__scalbln,(__x,__n))
#elif defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_scalbln,(double __x, long int __n),scalbn,(__x,__n))
#elif defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_scalbln,(double __x, long int __n),__scalbn,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/scalbln.h>
__NAMESPACE_LOCAL_BEGIN
/* Return X times (2 to the Nth power) */
#define __localdep_scalbln __LIBC_LOCAL_NAME(scalbln)
#else /* ... */
#undef __local___localdep_scalbln_defined
#endif /* !... */
#endif /* !__local___localdep_scalbln_defined */
__NAMESPACE_LOCAL_END
#include <libm/scalbn.h>
__NAMESPACE_LOCAL_BEGIN
/* Return X times (2 to the Nth power) */
__LOCAL_LIBC(scalblnf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(scalblnf))(float __x, long int __n) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	
#ifdef __IEEE754_DOUBLE_TYPE_IS_FLOAT__
	return (float)__ieee754_scalbln((__IEEE754_DOUBLE_TYPE__)__x, __n);
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
	return (float)__ieee754_scalblnf((__IEEE754_FLOAT_TYPE__)__x, __n);
#else /* ... */
	return (float)__ieee854_scalblnl((__IEEE854_LONG_DOUBLE_TYPE__)__x, __n);
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)__localdep_scalbln((double)__x, __n);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_scalblnf_defined
#define __local___localdep_scalblnf_defined 1
#define __localdep_scalblnf __LIBC_LOCAL_NAME(scalblnf)
#endif /* !__local___localdep_scalblnf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_scalbln || __CRT_HAVE___scalbln || (__CRT_HAVE_scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_scalblnf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_scalbln && !__CRT_HAVE___scalbln && (!__CRT_HAVE_scalbn || __SIZEOF_INT__ != __SIZEOF_LONG__) && (!__CRT_HAVE___scalbn || __SIZEOF_INT__ != __SIZEOF_LONG__) && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_scalblnf_defined */
