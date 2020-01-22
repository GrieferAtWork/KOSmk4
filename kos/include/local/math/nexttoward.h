/* HASH CRC-32:0xc455189c */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_nexttoward_defined
#include <ieee754.h>
#if ((defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)) && defined(__IEEE854_LONG_DOUBLE_TYPE__)) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter)
#define __local_nexttoward_defined 1
#include <libm/nexttoward.h>
/* Dependency: "nexttowardl" from "math" */
#ifndef ____localdep_nexttowardl_defined
#define ____localdep_nexttowardl_defined 1
#if __has_builtin(__builtin_nexttowardl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardl)
__EXTERNINLINE __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __localdep_nexttowardl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return __builtin_nexttowardl(__x, __y); }
#elif defined(__CRT_HAVE_nexttowardl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttowardl,(__x,__y))
#elif defined(__CRT_HAVE_nextafterl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nexttowardl,(__x,__y))
#else /* LIBC: nextafterl */
#include <ieee754.h>
#if defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter)
#include <local/math/nextafterl.h>
#define __localdep_nexttowardl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterl))
#else /* CUSTOM: nextafterl */
#undef ____localdep_nexttowardl_defined
#endif /* nexttowardl... */
#endif /* nexttowardl... */
#endif /* !____localdep_nexttowardl_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(nexttoward) __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(nexttoward))(double __x,
                                                    __LONGDOUBLE __y) {
#line 1342 "kos/src/libc/magic/math.c"
#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_nexttoward((__IEEE754_DOUBLE_TYPE__)__x, (__IEEE854_LONG_DOUBLE_TYPE__)__y);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
	return (double)__ieee754_nexttowardf((__IEEE754_FLOAT_TYPE__)__x, (__IEEE854_LONG_DOUBLE_TYPE__)__y);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
#else /* __IEEE854_LONG_DOUBLE_TYPE__ */
	return (double)__localdep_nexttowardl((__LONGDOUBLE)__x, __y);
#endif /* !__IEEE854_LONG_DOUBLE_TYPE__ */
}
__NAMESPACE_LOCAL_END
#endif /* ((__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__) && __IEEE854_LONG_DOUBLE_TYPE__) || __CRT_HAVE_nexttowardl || __CRT_HAVE_nextafterl || __CRT_HAVE___nexttowardl || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __CRT_HAVE_nextafter || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter */
#endif /* !__local_nexttoward_defined */
