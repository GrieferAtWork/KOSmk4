/* HASH CRC-32:0xc15a88f2 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_sincosl_defined
#define __local_sincosl_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos)
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: sincos from math */
#ifndef __local___localdep_sincos_defined
#define __local___localdep_sincos_defined 1
#if __has_builtin(__builtin_sincos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincos)
/* Cosine and sine of `x' */
__CEIREDIRECT(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),void,__NOTHROW,__localdep_sincos,(double __x, double *__psinx, double *__pcosx),sincos,{ return __builtin_sincos(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincos)
/* Cosine and sine of `x' */
__CREDIRECT_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,__localdep_sincos,(double __x, double *__psinx, double *__pcosx),sincos,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincos)
/* Cosine and sine of `x' */
__CREDIRECT_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,__localdep_sincos,(double __x, double *__psinx, double *__pcosx),__sincos,(__x,__psinx,__pcosx))
#else /* ... */
#undef __local___localdep_sincos_defined
#endif /* !... */
#endif /* !__local___localdep_sincos_defined */
/* Cosine and sine of `x' */
__LOCAL_LIBC(sincosl) __DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)) void
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sincosl))(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx) {
	double __sinx, __cosx;
	__localdep_sincos((double)__x, &__sinx, &__cosx);
	*__psinx = (__LONGDOUBLE)__sinx;
	*__pcosx = (__LONGDOUBLE)__cosx;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sincosl_defined
#define __local___localdep_sincosl_defined 1
#define __localdep_sincosl __LIBC_LOCAL_NAME(sincosl)
#endif /* !__local___localdep_sincosl_defined */
#else /* __CRT_HAVE_sincos || __CRT_HAVE___sincos */
#undef __local_sincosl_defined
#endif /* !__CRT_HAVE_sincos && !__CRT_HAVE___sincos */
#endif /* !__local_sincosl_defined */
