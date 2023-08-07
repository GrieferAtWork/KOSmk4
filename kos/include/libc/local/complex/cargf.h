/* HASH CRC-32:0x1a8e1ece */
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
#ifndef __local_cargf_defined
#define __local_cargf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__CRT_HAVE_atan2f) || defined(__CRT_HAVE___atan2f) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_carg)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_atan2f_defined
#define __local___localdep_atan2f_defined
#if __has_builtin(__builtin_atan2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2f)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_atan2f,(float __y, float __x),atan2f,{ return __builtin_atan2f(__y, __x); })
#elif defined(__CRT_HAVE_atan2f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_atan2f,(float __y, float __x),atan2f,(__y,__x))
#elif defined(__CRT_HAVE___atan2f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__localdep_atan2f,(float __y, float __x),__atan2f,(__y,__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/atan2f.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_atan2f __LIBC_LOCAL_NAME(atan2f)
#else /* ... */
#undef __local___localdep_atan2f_defined
#endif /* !... */
#endif /* !__local___localdep_atan2f_defined */
#ifndef __local___localdep_carg_defined
#define __local___localdep_carg_defined
#ifdef __CRT_HAVE_carg
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_carg,(double _Complex __z),carg,(__z))
#elif defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/complex/carg.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_carg __LIBC_LOCAL_NAME(carg)
#else /* ... */
#undef __local___localdep_carg_defined
#endif /* !... */
#endif /* !__local___localdep_carg_defined */
#ifndef __local___localdep_cimagf_defined
#define __local___localdep_cimagf_defined
#ifdef __CRT_HAVE_cimagf
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_cimagf,(float _Complex __z),cimagf,(__z))
#else /* __CRT_HAVE_cimagf */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/cimagf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cimagf __LIBC_LOCAL_NAME(cimagf)
#endif /* !__CRT_HAVE_cimagf */
#endif /* !__local___localdep_cimagf_defined */
#ifndef __local___localdep_crealf_defined
#define __local___localdep_crealf_defined
#ifdef __CRT_HAVE_crealf
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_crealf,(float _Complex __z),crealf,(__z))
#else /* __CRT_HAVE_crealf */
__NAMESPACE_LOCAL_END
#include <libc/local/complex/crealf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_crealf __LIBC_LOCAL_NAME(crealf)
#endif /* !__CRT_HAVE_crealf */
#endif /* !__local___localdep_crealf_defined */
__LOCAL_LIBC(cargf) __ATTR_WUNUSED float
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cargf))(float _Complex __z) {
#if defined(__CRT_HAVE_atan2f) || defined(__CRT_HAVE___atan2f) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	return (__NAMESPACE_LOCAL_SYM __localdep_atan2f)((__NAMESPACE_LOCAL_SYM __localdep_cimagf)(__z), (__NAMESPACE_LOCAL_SYM __localdep_crealf)(__z));
#else /* __CRT_HAVE_atan2f || __CRT_HAVE___atan2f || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_carg)((double _Complex)__z);
#endif /* !__CRT_HAVE_atan2f && !__CRT_HAVE___atan2f && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_atan2 && !__CRT_HAVE___atan2 && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cargf_defined
#define __local___localdep_cargf_defined
#define __localdep_cargf __LIBC_LOCAL_NAME(cargf)
#endif /* !__local___localdep_cargf_defined */
#else /* __CRT_HAVE_atan2f || __CRT_HAVE___atan2f || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_carg */
#undef __local_cargf_defined
#endif /* !__CRT_HAVE_atan2f && !__CRT_HAVE___atan2f && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_atan2 && !__CRT_HAVE___atan2 && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__CRT_HAVE_carg */
#endif /* !__local_cargf_defined */
