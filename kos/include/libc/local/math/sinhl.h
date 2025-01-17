/* HASH CRC-32:0xe2827a68 */
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
#ifndef __local_sinhl_defined
#define __local_sinhl_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sinh_defined
#define __local___localdep_sinh_defined
#if __has_builtin(__builtin_sinh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinh)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sinh,(double __x),sinh,{ return __builtin_sinh(__x); })
#elif defined(__CRT_HAVE_sinh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sinh,(double __x),sinh,(__x))
#elif defined(__CRT_HAVE___sinh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_sinh,(double __x),__sinh,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/sinh.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sinh __LIBC_LOCAL_NAME(sinh)
#else /* ... */
#undef __local___localdep_sinh_defined
#endif /* !... */
#endif /* !__local___localdep_sinh_defined */
__NAMESPACE_LOCAL_END
#include <libm/finite.h>
#include <libm/sinh.h>
#include <libm/matherr.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sinhl) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sinhl))(__LONGDOUBLE __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)


	__LONGDOUBLE __result = __LIBM_MATHFUNL(sinh, __x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		!__LIBM_MATHFUNIL(finite, __result) && __LIBM_MATHFUNIL(finite, __x))
		__result = __kernel_standard_l(__x, __x, __result, __LIBM_KMATHERRL_SINH);
	return __result;
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
	return (__LONGDOUBLE)(__NAMESPACE_LOCAL_SYM __localdep_sinh)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sinhl_defined
#define __local___localdep_sinhl_defined
#define __localdep_sinhl __LIBC_LOCAL_NAME(sinhl)
#endif /* !__local___localdep_sinhl_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_sinh || __CRT_HAVE___sinh || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_sinhl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_sinh && !__CRT_HAVE___sinh && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_sinhl_defined */
