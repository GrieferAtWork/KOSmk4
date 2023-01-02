/* HASH CRC-32:0x2791e9ff */
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
#ifndef __local_cprojf_defined
#define __local_cprojf_defined
#include <__crt.h>
#include <ieee754.h>
#include <bits/math-constants.h>
#if defined(__CRT_HAVE_isinff) || defined(__CRT_HAVE___isinff) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__INFINITYF) || defined(__HUGE_VALF) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL) || defined(__CRT_HAVE_cproj)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_cimagf_defined
#define __local___localdep_cimagf_defined
#ifdef __CRT_HAVE_cimagf
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW_NCX,__localdep_cimagf,(float _Complex __z),cimagf,(__z))
#else /* __CRT_HAVE_cimagf */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/cimagf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cimagf __LIBC_LOCAL_NAME(cimagf)
#endif /* !__CRT_HAVE_cimagf */
#endif /* !__local___localdep_cimagf_defined */
#ifndef __local___localdep_copysignf_defined
#define __local___localdep_copysignf_defined
#if __has_builtin(__builtin_copysignf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_copysignf,(float __num, float __sign),copysignf,{ return __builtin_copysignf(__num, __sign); })
#elif defined(__CRT_HAVE_copysignf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_copysignf,(float __num, float __sign),copysignf,(__num,__sign))
#elif defined(__CRT_HAVE__copysignf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_copysignf,(float __num, float __sign),_copysignf,(__num,__sign))
#elif defined(__CRT_HAVE___copysignf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_copysignf,(float __num, float __sign),__copysignf,(__num,__sign))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/copysignf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_copysignf __LIBC_LOCAL_NAME(copysignf)
#endif /* !... */
#endif /* !__local___localdep_copysignf_defined */
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
#ifndef __local___localdep_crealf_defined
#define __local___localdep_crealf_defined
#ifdef __CRT_HAVE_crealf
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW_NCX,__localdep_crealf,(float _Complex __z),crealf,(__z))
#else /* __CRT_HAVE_crealf */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/crealf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_crealf __LIBC_LOCAL_NAME(crealf)
#endif /* !__CRT_HAVE_crealf */
#endif /* !__local___localdep_crealf_defined */
#ifndef __local___localdep_isinff_defined
#define __local___localdep_isinff_defined
#if __has_builtin(__builtin_isinff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinff)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinff,(float __x),isinff,{ return __builtin_isinff(__x); })
#elif defined(__CRT_HAVE_isinff)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinff,(float __x),isinff,(__x))
#elif defined(__CRT_HAVE___isinff)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isinff,(float __x),__isinff,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__INFINITYF) || defined(__HUGE_VALF) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
__NAMESPACE_LOCAL_END
#include <libc/local/math/isinff.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isinff __LIBC_LOCAL_NAME(isinff)
#else /* ... */
#undef __local___localdep_isinff_defined
#endif /* !... */
#endif /* !__local___localdep_isinff_defined */
__LOCAL_LIBC(cprojf) __ATTR_CONST __ATTR_WUNUSED float _Complex
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cprojf))(float _Complex __z) {
#if defined(__CRT_HAVE_isinff) || defined(__CRT_HAVE___isinff) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__INFINITYF) || defined(__HUGE_VALF) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
	union {
		float _Complex __x;
		float __parts[2];
	} __v;
	__v.__x = __z;
	if ((__NAMESPACE_LOCAL_SYM __localdep_isinff)((__NAMESPACE_LOCAL_SYM __localdep_crealf)(__z)) || (__NAMESPACE_LOCAL_SYM __localdep_isinff)((__NAMESPACE_LOCAL_SYM __localdep_cimagf)(__z))) {
		__v.__parts[0] = __HUGE_VALF;              /* Real-part */
		__v.__parts[1] = (__NAMESPACE_LOCAL_SYM __localdep_copysignf)(0.0f, (__NAMESPACE_LOCAL_SYM __localdep_cimagf)(__z)); /* Imag-part */
	}
	return __v.__x;
#else /* __CRT_HAVE_isinff || __CRT_HAVE___isinff || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __INFINITYF || __HUGE_VALF || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL */
	return (float _Complex)(__NAMESPACE_LOCAL_SYM __localdep_cproj)((double _Complex)__z);
#endif /* !__CRT_HAVE_isinff && !__CRT_HAVE___isinff && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__INFINITYF && !__HUGE_VALF && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cprojf_defined
#define __local___localdep_cprojf_defined
#define __localdep_cprojf __LIBC_LOCAL_NAME(cprojf)
#endif /* !__local___localdep_cprojf_defined */
#else /* __CRT_HAVE_isinff || __CRT_HAVE___isinff || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __INFINITYF || __HUGE_VALF || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL || __CRT_HAVE_cproj */
#undef __local_cprojf_defined
#endif /* !__CRT_HAVE_isinff && !__CRT_HAVE___isinff && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__INFINITYF && !__HUGE_VALF && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL && !__CRT_HAVE_cproj */
#endif /* !__local_cprojf_defined */
