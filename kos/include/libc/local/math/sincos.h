/* HASH CRC-32:0xb24f4509 */
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
#ifndef __local_sincos_defined
#define __local_sincos_defined
#include <__crt.h>
#include <ieee754.h>
#if ((defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_cos_defined
#define __local___localdep_cos_defined
#if __has_builtin(__builtin_cos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cos)
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,__localdep_cos,(double __x),cos,{ return __builtin_cos(__x); })
#elif defined(__CRT_HAVE_cos)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,__localdep_cos,(double __x),cos,(__x))
#elif defined(__CRT_HAVE___cos)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,__localdep_cos,(double __x),__cos,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/cos.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cos __LIBC_LOCAL_NAME(cos)
#else /* ... */
#undef __local___localdep_cos_defined
#endif /* !... */
#endif /* !__local___localdep_cos_defined */
#ifndef __local___localdep_sin_defined
#define __local___localdep_sin_defined
#if __has_builtin(__builtin_sin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sin)
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sin,double,__NOTHROW,__localdep_sin,(double __x),sin,{ return __builtin_sin(__x); })
#elif defined(__CRT_HAVE_sin)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sin,double,__NOTHROW,__localdep_sin,(double __x),sin,(__x))
#elif defined(__CRT_HAVE___sin)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sin,double,__NOTHROW,__localdep_sin,(double __x),__sin,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/sin.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sin __LIBC_LOCAL_NAME(sin)
#else /* ... */
#undef __local___localdep_sin_defined
#endif /* !... */
#endif /* !__local___localdep_sin_defined */
__NAMESPACE_LOCAL_END
#include <libm/sincos.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sincos) __DECL_SIMD_sincos __ATTR_OUT(2) __ATTR_OUT(3) void
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sincos))(double __x, double *__psinx, double *__pcosx) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	__LIBM_MATHFUNX(sincos)(__x, (__LIBM_MATHFUN_T *)__psinx, (__LIBM_MATHFUN_T *)__pcosx);
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
	*__psinx = (__NAMESPACE_LOCAL_SYM __localdep_sin)(__x);
	*__pcosx = (__NAMESPACE_LOCAL_SYM __localdep_cos)(__x);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sincos_defined
#define __local___localdep_sincos_defined
#define __localdep_sincos __LIBC_LOCAL_NAME(sincos)
#endif /* !__local___localdep_sincos_defined */
#else /* ((__CRT_HAVE_sin || __CRT_HAVE___sin) && (__CRT_HAVE_cos || __CRT_HAVE___cos)) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_sincos_defined
#endif /* ((!__CRT_HAVE_sin && !__CRT_HAVE___sin) || (!__CRT_HAVE_cos && !__CRT_HAVE___cos)) && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_sincos_defined */
