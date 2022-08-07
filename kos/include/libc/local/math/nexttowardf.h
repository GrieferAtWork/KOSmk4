/* HASH CRC-32:0x98e1c09c */
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
#ifndef __local_nexttowardf_defined
#define __local_nexttowardf_defined
#include <__crt.h>
#include <ieee754.h>
#include <hybrid/typecore.h>
#if ((defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)) && defined(__IEEE854_LONG_DOUBLE_TYPE__)) || defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_nextafterl_defined
#define __local___localdep_nextafterl_defined
#if __has_builtin(__builtin_nextafterl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,{ return __builtin_nextafterl(__x, __y); })
#elif __has_builtin(__builtin_nexttowardl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttowardl,{ return __builtin_nexttowardl(__x); })
#elif defined(__CRT_HAVE_nextafterl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,(__x,__y))
#elif defined(__CRT_HAVE_nexttowardl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttowardl,(__x,__y))
#elif defined(__CRT_HAVE___nextafterl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nexttowardl,(__x,__y))
#elif defined(__CRT_HAVE_nextafter) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafter,(__x,__y))
#elif defined(__CRT_HAVE_nexttoward) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttoward,(__x,__y))
#elif defined(__CRT_HAVE___nextafter) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nextafter,(__x,__y))
#elif defined(__CRT_HAVE___nexttoward) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nexttoward,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/nextafterl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_nextafterl __LIBC_LOCAL_NAME(nextafterl)
#else /* ... */
#undef __local___localdep_nextafterl_defined
#endif /* !... */
#endif /* !__local___localdep_nextafterl_defined */
__NAMESPACE_LOCAL_END
#include <libm/nexttoward.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(nexttowardf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(nexttowardf))(float __x, __LONGDOUBLE __y) {
#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__
	return (float)__ieee754_nexttowardf((__IEEE754_FLOAT_TYPE__)__x, (__IEEE854_LONG_DOUBLE_TYPE__)__y);
#else /* __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
	return (float)__ieee754_nexttoward((__IEEE754_DOUBLE_TYPE__)__x, (__IEEE854_LONG_DOUBLE_TYPE__)__y);
#endif /* !__IEEE754_FLOAT_TYPE_IS_FLOAT__ */
#else /* __IEEE854_LONG_DOUBLE_TYPE__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_nextafterl)((__LONGDOUBLE)__x, __y);
#endif /* !__IEEE854_LONG_DOUBLE_TYPE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_nexttowardf_defined
#define __local___localdep_nexttowardf_defined
#define __localdep_nexttowardf __LIBC_LOCAL_NAME(nexttowardf)
#endif /* !__local___localdep_nexttowardf_defined */
#else /* ((__IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_FLOAT__) && __IEEE854_LONG_DOUBLE_TYPE__) || __CRT_HAVE_nextafterl || __CRT_HAVE_nexttowardl || __CRT_HAVE___nextafterl || __CRT_HAVE___nexttowardl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_nextafter || __CRT_HAVE_nexttoward || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter || __CRT_HAVE___nexttoward || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_nexttowardf_defined
#endif /* ((!__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || !__IEEE854_LONG_DOUBLE_TYPE__) && !__CRT_HAVE_nextafterl && !__CRT_HAVE_nexttowardl && !__CRT_HAVE___nextafterl && !__CRT_HAVE___nexttowardl && !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_nextafter && !__CRT_HAVE_nexttoward && !__CRT_HAVE___nextafter && !__CRT_HAVE__nextafter && !__CRT_HAVE___nexttoward && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_nexttowardf_defined */
