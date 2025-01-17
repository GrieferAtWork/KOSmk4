/* HASH CRC-32:0x9dae8d96 */
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
#ifndef __local_isinff_defined
#define __local_isinff_defined
#include <__crt.h>
#include <ieee754.h>
#include <bits/math-constants.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__INFINITYF) || defined(__HUGE_VALF) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
__NAMESPACE_LOCAL_BEGIN
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
__NAMESPACE_LOCAL_END
#include <libm/isinf.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(isinff) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(isinff))(float __x) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__INFINITYF) || defined(__HUGE_VALF)



	
#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(isinf, __x);
#elif defined(__INFINITYF)
	return __x == __INFINITYF;
#else /* ... */
	return __x == __HUGE_VALF;
#endif /* !... */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __INFINITYF || __HUGE_VALF */
	return (__NAMESPACE_LOCAL_SYM __localdep_isinf)((double)__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__INFINITYF && !__HUGE_VALF */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_isinff_defined
#define __local___localdep_isinff_defined
#define __localdep_isinff __LIBC_LOCAL_NAME(isinff)
#endif /* !__local___localdep_isinff_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __INFINITYF || __HUGE_VALF || __CRT_HAVE_isinf || __CRT_HAVE___isinf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __INFINITY || __HUGE_VAL */
#undef __local_isinff_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__INFINITYF && !__HUGE_VALF && !__CRT_HAVE_isinf && !__CRT_HAVE___isinf && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && !__INFINITY && !__HUGE_VAL */
#endif /* !__local_isinff_defined */
