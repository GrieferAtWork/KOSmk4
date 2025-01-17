/* HASH CRC-32:0xef32c9a2 */
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
#ifndef __local_cproj_defined
#define __local_cproj_defined
#include <__crt.h>
#include <ieee754.h>
#include <bits/math-constants.h>
#if defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_cimag_defined
#define __local___localdep_cimag_defined
#ifdef __CRT_HAVE_cimag
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_cimag,(double _Complex __z),cimag,(__z))
#else /* __CRT_HAVE_cimag */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/cimag.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cimag __LIBC_LOCAL_NAME(cimag)
#endif /* !__CRT_HAVE_cimag */
#endif /* !__local___localdep_cimag_defined */
#ifndef __local___localdep_copysign_defined
#define __local___localdep_copysign_defined
#if __has_builtin(__builtin_copysign) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysign)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_copysign,(double __num, double __sign),copysign,{ return __builtin_copysign(__num, __sign); })
#elif defined(__CRT_HAVE_copysign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_copysign,(double __num, double __sign),copysign,(__num,__sign))
#elif defined(__CRT_HAVE___copysign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_copysign,(double __num, double __sign),__copysign,(__num,__sign))
#elif defined(__CRT_HAVE__copysign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_copysign,(double __num, double __sign),_copysign,(__num,__sign))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/copysign.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_copysign __LIBC_LOCAL_NAME(copysign)
#endif /* !... */
#endif /* !__local___localdep_copysign_defined */
#ifndef __local___localdep_creal_defined
#define __local___localdep_creal_defined
#ifdef __CRT_HAVE_creal
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_creal,(double _Complex __z),creal,(__z))
#else /* __CRT_HAVE_creal */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/creal.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_creal __LIBC_LOCAL_NAME(creal)
#endif /* !__CRT_HAVE_creal */
#endif /* !__local___localdep_creal_defined */
#ifndef __local___localdep_isinf_defined
#define __local___localdep_isinf_defined
#if __has_builtin(__builtin_isinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),isinf,{ return __builtin_isinf(__x); })
#elif defined(__CRT_HAVE_isinf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),isinf,(__x))
#elif defined(__CRT_HAVE___isinf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinf,(double __x),__isinf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isinf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isinf __LIBC_LOCAL_NAME(isinf)
#else /* ... */
#undef __local___localdep_isinf_defined
#endif /* !... */
#endif /* !__local___localdep_isinf_defined */
__LOCAL_LIBC(cproj) __ATTR_CONST __ATTR_WUNUSED double _Complex
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(cproj))(double _Complex __z) {
	union {
		double _Complex __x;
		double __parts[2];
	} __v;
	__v.__x = __z;
	if ((__NAMESPACE_LOCAL_SYM __localdep_isinf)((__NAMESPACE_LOCAL_SYM __localdep_creal)(__z)) || (__NAMESPACE_LOCAL_SYM __localdep_isinf)((__NAMESPACE_LOCAL_SYM __localdep_cimag)(__z))) {
		__v.__parts[0] = __HUGE_VAL;              /* Real-part */
		__v.__parts[1] = (__NAMESPACE_LOCAL_SYM __localdep_copysign)(0.0, (__NAMESPACE_LOCAL_SYM __localdep_cimag)(__z)); /* Imag-part */
	}
	return __v.__x;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cproj_defined
#define __local___localdep_cproj_defined
#define __localdep_cproj __LIBC_LOCAL_NAME(cproj)
#endif /* !__local___localdep_cproj_defined */
#else /* __CRT_HAVE_isinf || __CRT_HAVE___isinf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL */
#undef __local_cproj_defined
#endif /* !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL */
#endif /* !__local_cproj_defined */
