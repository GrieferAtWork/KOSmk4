/* HASH CRC-32:0x33b7f6ee */
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
#ifndef __local_sincosf_defined
#define __local_sincosf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos) || ((defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_sinf) || defined(__CRT_HAVE___sinf) || defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cosf) || defined(__CRT_HAVE___cosf) || defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_cosf_defined
#define __local___localdep_cosf_defined
#if __has_builtin(__builtin_cosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosf)
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosf,float,__NOTHROW,__localdep_cosf,(float __x),cosf,{ return __builtin_cosf(__x); })
#elif defined(__CRT_HAVE_cosf)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosf,float,__NOTHROW,__localdep_cosf,(float __x),cosf,(__x))
#elif defined(__CRT_HAVE___cosf)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosf,float,__NOTHROW,__localdep_cosf,(float __x),__cosf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/cosf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cosf __LIBC_LOCAL_NAME(cosf)
#else /* ... */
#undef __local___localdep_cosf_defined
#endif /* !... */
#endif /* !__local___localdep_cosf_defined */
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
#ifndef __local___localdep_sinf_defined
#define __local___localdep_sinf_defined
#if __has_builtin(__builtin_sinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinf)
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinf,float,__NOTHROW,__localdep_sinf,(float __x),sinf,{ return __builtin_sinf(__x); })
#elif defined(__CRT_HAVE_sinf)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinf,float,__NOTHROW,__localdep_sinf,(float __x),sinf,(__x))
#elif defined(__CRT_HAVE___sinf)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinf,float,__NOTHROW,__localdep_sinf,(float __x),__sinf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/sinf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sinf __LIBC_LOCAL_NAME(sinf)
#else /* ... */
#undef __local___localdep_sinf_defined
#endif /* !... */
#endif /* !__local___localdep_sinf_defined */
__NAMESPACE_LOCAL_END
#include <libm/sincos.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sincosf) __DECL_SIMD_sincosf __ATTR_OUT(2) __ATTR_OUT(3) void
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sincosf))(float __x, float *__psinx, float *__pcosx) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
	__LIBM_MATHFUNXF(sincos)(__x, (__LIBM_MATHFUNF_T *)__psinx, (__LIBM_MATHFUNF_T *)__pcosx);
#elif defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos) || ((defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)) && (defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos))) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
	double __sinx, __cosx;
	(__NAMESPACE_LOCAL_SYM __localdep_sincos)((double)__x, &__sinx, &__cosx);
	*__psinx = (float)__sinx;
	*__pcosx = (float)__cosx;
#else /* ... */
	*__psinx = (__NAMESPACE_LOCAL_SYM __localdep_sinf)(__x);
	*__pcosx = (__NAMESPACE_LOCAL_SYM __localdep_cosf)(__x);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sincosf_defined
#define __local___localdep_sincosf_defined
#define __localdep_sincosf __LIBC_LOCAL_NAME(sincosf)
#endif /* !__local___localdep_sincosf_defined */
#else /* __CRT_HAVE_sincos || __CRT_HAVE___sincos || ((__CRT_HAVE_sin || __CRT_HAVE___sin) && (__CRT_HAVE_cos || __CRT_HAVE___cos)) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || ((__CRT_HAVE_sinf || __CRT_HAVE___sinf || __CRT_HAVE_sin || __CRT_HAVE___sin) && (__CRT_HAVE_cosf || __CRT_HAVE___cosf || __CRT_HAVE_cos || __CRT_HAVE___cos)) || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
#undef __local_sincosf_defined
#endif /* !__CRT_HAVE_sincos && !__CRT_HAVE___sincos && ((!__CRT_HAVE_sin && !__CRT_HAVE___sin) || (!__CRT_HAVE_cos && !__CRT_HAVE___cos)) && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ && ((!__CRT_HAVE_sinf && !__CRT_HAVE___sinf && !__CRT_HAVE_sin && !__CRT_HAVE___sin) || (!__CRT_HAVE_cosf && !__CRT_HAVE___cosf && !__CRT_HAVE_cos && !__CRT_HAVE___cos)) && !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
#endif /* !__local_sincosf_defined */
