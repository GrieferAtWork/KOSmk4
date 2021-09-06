/* HASH CRC-32:0x7450da55 */
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
#ifndef __local_lrintl_defined
#define __local_lrintl_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_rintl_defined
#define __local___localdep_rintl_defined 1
#if __has_builtin(__builtin_rintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_rintl,(__LONGDOUBLE __x),rintl,{ return __builtin_rintl(__x); })
#elif __has_builtin(__builtin_nearbyintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_rintl,(__LONGDOUBLE __x),nearbyintl,{ return __builtin_nearbyintl(__x); })
#elif defined(__CRT_HAVE_rintl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_rintl,(__LONGDOUBLE __x),rintl,(__x))
#elif defined(__CRT_HAVE_nearbyintl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_rintl,(__LONGDOUBLE __x),nearbyintl,(__x))
#elif defined(__CRT_HAVE___rintl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_rintl,(__LONGDOUBLE __x),__rintl,(__x))
#elif defined(__CRT_HAVE___nearbyintl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_rintl,(__LONGDOUBLE __x),__nearbyintl,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <ieee754.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/rintl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rintl __LIBC_LOCAL_NAME(rintl)
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_rint || __CRT_HAVE_nearbyint || __CRT_HAVE___rint || __CRT_HAVE___nearbyint || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local___localdep_rintl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_rint && !__CRT_HAVE_nearbyint && !__CRT_HAVE___rint && !__CRT_HAVE___nearbyint && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !... */
#endif /* !__local___localdep_rintl_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <libm/lrint.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(lrintl) __ATTR_CONST __ATTR_WUNUSED long int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(lrintl))(__LONGDOUBLE __x) {
#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(lrint, __x);
#else /* __LIBM_MATHFUNIL */
	return (long int)__localdep_rintl(__x);
#endif /* !__LIBM_MATHFUNIL */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lrintl_defined
#define __local___localdep_lrintl_defined 1
#define __localdep_lrintl __LIBC_LOCAL_NAME(lrintl)
#endif /* !__local___localdep_lrintl_defined */
#endif /* !__local_lrintl_defined */
