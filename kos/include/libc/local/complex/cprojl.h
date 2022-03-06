/* HASH CRC-32:0xc07fb65f */
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
#ifndef __local_cprojl_defined
#define __local_cprojl_defined
#include <__crt.h>
#include <ieee754.h>
#include <bits/math-constants.h>
#if defined(__CRT_HAVE_isinfl) || defined(__CRT_HAVE___isinfl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__INFINITYL) || defined(__HUGE_VALL) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL) || defined(__CRT_HAVE_cproj)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_cimagl_defined
#define __local___localdep_cimagl_defined
#ifdef __CRT_HAVE_cimagl
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,__localdep_cimagl,(long double _Complex __z),cimagl,(__z))
#else /* __CRT_HAVE_cimagl */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/cimagl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cimagl __LIBC_LOCAL_NAME(cimagl)
#endif /* !__CRT_HAVE_cimagl */
#endif /* !__local___localdep_cimagl_defined */
#ifndef __local___localdep_copysignl_defined
#define __local___localdep_copysignl_defined
#if __has_builtin(__builtin_copysignl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),copysignl,{ return __builtin_copysignl(__num, __sign); })
#elif defined(__CRT_HAVE_copysignl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),copysignl,(__num,__sign))
#elif defined(__CRT_HAVE___copysignl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),__copysignl,(__num,__sign))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/copysignl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_copysignl __LIBC_LOCAL_NAME(copysignl)
#endif /* !... */
#endif /* !__local___localdep_copysignl_defined */
#ifndef __local___localdep_cproj_defined
#define __local___localdep_cproj_defined
#ifdef __CRT_HAVE_cproj
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double _Complex,__NOTHROW_NCX,__localdep_cproj,(double _Complex __z),cproj,(__z))
#elif defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
__NAMESPACE_LOCAL_END
#include <libc/local/complex/cproj.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cproj __LIBC_LOCAL_NAME(cproj)
#else /* ... */
#undef __local___localdep_cproj_defined
#endif /* !... */
#endif /* !__local___localdep_cproj_defined */
#ifndef __local___localdep_creall_defined
#define __local___localdep_creall_defined
#ifdef __CRT_HAVE_creall
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,__localdep_creall,(long double _Complex __z),creall,(__z))
#else /* __CRT_HAVE_creall */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/creall.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_creall __LIBC_LOCAL_NAME(creall)
#endif /* !__CRT_HAVE_creall */
#endif /* !__local___localdep_creall_defined */
#ifndef __local___localdep_isinfl_defined
#define __local___localdep_isinfl_defined
#if __has_builtin(__builtin_isinfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinfl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(__LONGDOUBLE __x),isinfl,{ return __builtin_isinfl(__x); })
#elif defined(__CRT_HAVE_isinfl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(__LONGDOUBLE __x),isinfl,(__x))
#elif defined(__CRT_HAVE___isinfl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinfl,(__LONGDOUBLE __x),__isinfl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__INFINITYL) || defined(__HUGE_VALL) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isinfl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isinfl __LIBC_LOCAL_NAME(isinfl)
#else /* ... */
#undef __local___localdep_isinfl_defined
#endif /* !... */
#endif /* !__local___localdep_isinfl_defined */
__LOCAL_LIBC(cprojl) __ATTR_CONST __ATTR_WUNUSED long double _Complex
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cprojl))(long double _Complex __z) {
#if defined(__CRT_HAVE_isinfl) || defined(__CRT_HAVE___isinfl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__INFINITYL) || defined(__HUGE_VALL) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
	union {
		long double _Complex __x;
		__LONGDOUBLE __parts[2];
	} __v;
	__v.__x = __z;
	if ((__NAMESPACE_LOCAL_SYM __localdep_isinfl)((__NAMESPACE_LOCAL_SYM __localdep_creall)(__z)) || (__NAMESPACE_LOCAL_SYM __localdep_isinfl)((__NAMESPACE_LOCAL_SYM __localdep_cimagl)(__z))) {
		__v.__parts[0] = __HUGE_VALL;              /* Real-part */
		__v.__parts[1] = (__NAMESPACE_LOCAL_SYM __localdep_copysignl)(0.0L, (__NAMESPACE_LOCAL_SYM __localdep_cimagl)(__z)); /* Imag-part */
	}
	return __v.__x;
#else /* __CRT_HAVE_isinfl || __CRT_HAVE___isinfl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __INFINITYL || __HUGE_VALL || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL */
	return (long double _Complex)(__NAMESPACE_LOCAL_SYM __localdep_cproj)((double _Complex)__z);
#endif /* !__CRT_HAVE_isinfl && !__CRT_HAVE___isinfl && !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__INFINITYL && !__HUGE_VALL && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cprojl_defined
#define __local___localdep_cprojl_defined
#define __localdep_cprojl __LIBC_LOCAL_NAME(cprojl)
#endif /* !__local___localdep_cprojl_defined */
#else /* __CRT_HAVE_isinfl || __CRT_HAVE___isinfl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __INFINITYL || __HUGE_VALL || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL || __CRT_HAVE_cproj */
#undef __local_cprojl_defined
#endif /* !__CRT_HAVE_isinfl && !__CRT_HAVE___isinfl && !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__INFINITYL && !__HUGE_VALL && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL && !__CRT_HAVE_cproj */
#endif /* !__local_cprojl_defined */
