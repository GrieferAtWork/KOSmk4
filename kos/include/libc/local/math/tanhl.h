/* HASH CRC-32:0xa0e41b04 */
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
#ifndef __local_tanhl_defined
#define __local_tanhl_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tanh_defined
#define __local___localdep_tanh_defined
#if __has_builtin(__builtin_tanh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanh)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_tanh,(double __x),tanh,{ return __builtin_tanh(__x); })
#elif defined(__CRT_HAVE_tanh)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_tanh,(double __x),tanh,(__x))
#elif defined(__CRT_HAVE___tanh)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_tanh,(double __x),__tanh,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/tanh.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tanh __LIBC_LOCAL_NAME(tanh)
#else /* ... */
#undef __local___localdep_tanh_defined
#endif /* !... */
#endif /* !__local___localdep_tanh_defined */
__NAMESPACE_LOCAL_END
#include <libm/tanh.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tanhl) __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(tanhl))(__LONGDOUBLE __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	return __LIBM_MATHFUNL(tanh, __x);
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)(__NAMESPACE_LOCAL_SYM __localdep_tanh)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tanhl_defined
#define __local___localdep_tanhl_defined
#define __localdep_tanhl __LIBC_LOCAL_NAME(tanhl)
#endif /* !__local___localdep_tanhl_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_tanh || __CRT_HAVE___tanh || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_tanhl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_tanh && !__CRT_HAVE___tanh && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_tanhl_defined */
