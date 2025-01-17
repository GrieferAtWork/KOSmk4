/* HASH CRC-32:0x5175f6cc */
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
#ifndef __local_sincosl_defined
#define __local_sincosl_defined
#include <__crt.h>
#include <ieee754.h>
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos) || ((defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_sinl) || defined(__CRT_HAVE___sinl) || defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cosl) || defined(__CRT_HAVE___cosl) || defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_cosl_defined
#define __local___localdep_cosl_defined
#if __has_builtin(__builtin_cosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosl)
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,__localdep_cosl,(__LONGDOUBLE __x),cosl,{ return __builtin_cosl(__x); })
#elif defined(__CRT_HAVE_cosl)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,__localdep_cosl,(__LONGDOUBLE __x),cosl,(__x))
#elif defined(__CRT_HAVE___cosl)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,__localdep_cosl,(__LONGDOUBLE __x),__cosl,(__x))
#elif defined(__CRT_HAVE_cos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,__localdep_cosl,(__LONGDOUBLE __x),cos,(__x))
#elif defined(__CRT_HAVE___cos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,__localdep_cosl,(__LONGDOUBLE __x),__cos,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/cosl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cosl __LIBC_LOCAL_NAME(cosl)
#else /* ... */
#undef __local___localdep_cosl_defined
#endif /* !... */
#endif /* !__local___localdep_cosl_defined */
#ifndef __local___localdep_sincos_defined
#define __local___localdep_sincos_defined
#if __has_builtin(__builtin_sincos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincos)
__CEIREDIRECT(__DECL_SIMD_sincos __ATTR_OUT(2) __ATTR_OUT(3),void,__NOTHROW,__localdep_sincos,(double __x, double *__psinx, double *__pcosx),sincos,{ __builtin_sincos(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincos)
__CREDIRECT_VOID(__DECL_SIMD_sincos __ATTR_OUT(2) __ATTR_OUT(3),__NOTHROW,__localdep_sincos,(double __x, double *__psinx, double *__pcosx),sincos,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincos)
__CREDIRECT_VOID(__DECL_SIMD_sincos __ATTR_OUT(2) __ATTR_OUT(3),__NOTHROW,__localdep_sincos,(double __x, double *__psinx, double *__pcosx),__sincos,(__x,__psinx,__pcosx))
#elif ((defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/sincos.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sincos __LIBC_LOCAL_NAME(sincos)
#else /* ... */
#undef __local___localdep_sincos_defined
#endif /* !... */
#endif /* !__local___localdep_sincos_defined */
#ifndef __local___localdep_sinl_defined
#define __local___localdep_sinl_defined
#if __has_builtin(__builtin_sinl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinl)
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,__localdep_sinl,(__LONGDOUBLE __x),sinl,{ return __builtin_sinl(__x); })
#elif defined(__CRT_HAVE_sinl)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,__localdep_sinl,(__LONGDOUBLE __x),sinl,(__x))
#elif defined(__CRT_HAVE___sinl)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,__localdep_sinl,(__LONGDOUBLE __x),__sinl,(__x))
#elif defined(__CRT_HAVE_sin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,__localdep_sinl,(__LONGDOUBLE __x),sin,(__x))
#elif defined(__CRT_HAVE___sin) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,__localdep_sinl,(__LONGDOUBLE __x),__sin,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/sinl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sinl __LIBC_LOCAL_NAME(sinl)
#else /* ... */
#undef __local___localdep_sinl_defined
#endif /* !... */
#endif /* !__local___localdep_sinl_defined */
__NAMESPACE_LOCAL_END
#include <libm/sincos.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sincosl) __DECL_SIMD_sincosl __ATTR_OUT(2) __ATTR_OUT(3) void
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sincosl))(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)
	__LIBM_MATHFUNXL(sincos)(__x, (__LIBM_MATHFUNL_T *)__psinx, (__LIBM_MATHFUNL_T *)__pcosx);
#elif defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos) || ((defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	double __sinx, __cosx;
	(__NAMESPACE_LOCAL_SYM __localdep_sincos)((double)__x, &__sinx, &__cosx);
	*__psinx = (__LONGDOUBLE)__sinx;
	*__pcosx = (__LONGDOUBLE)__cosx;
#else /* ... */
	*__psinx = (__NAMESPACE_LOCAL_SYM __localdep_sinl)(__x);
	*__pcosx = (__NAMESPACE_LOCAL_SYM __localdep_cosl)(__x);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sincosl_defined
#define __local___localdep_sincosl_defined
#define __localdep_sincosl __LIBC_LOCAL_NAME(sincosl)
#endif /* !__local___localdep_sincosl_defined */
#else /* __CRT_HAVE_sincos || __CRT_HAVE___sincos || ((__CRT_HAVE_sin || __CRT_HAVE___sin) && (__CRT_HAVE_cos || __CRT_HAVE___cos)) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || ((__CRT_HAVE_sinl || __CRT_HAVE___sinl || __CRT_HAVE_sin || __CRT_HAVE___sin) && (__CRT_HAVE_cosl || __CRT_HAVE___cosl || __CRT_HAVE_cos || __CRT_HAVE___cos)) || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
#undef __local_sincosl_defined
#endif /* !__CRT_HAVE_sincos && !__CRT_HAVE___sincos && ((!__CRT_HAVE_sin && !__CRT_HAVE___sin) || (!__CRT_HAVE_cos && !__CRT_HAVE___cos)) && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && ((!__CRT_HAVE_sinl && !__CRT_HAVE___sinl && !__CRT_HAVE_sin && !__CRT_HAVE___sin) || (!__CRT_HAVE_cosl && !__CRT_HAVE___cosl && !__CRT_HAVE_cos && !__CRT_HAVE___cos)) && !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
#endif /* !__local_sincosl_defined */
