/* HASH CRC-32:0x6a7b8ac */
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
#ifndef __local_sincosl_defined
#if defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos)
#define __local_sincosl_defined 1
#include <bits/math-vector.h>
#include <bits/math-vector.h>
/* Dependency: "sincos" */
#ifndef ____localdep_sincos_defined
#define ____localdep_sincos_defined 1
#if __has_builtin(__builtin_sincos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincos)
/* Cosine and sine of X */
__EXTERNINLINE __DECL_SIMD_sincos __ATTR_NONNULL((2, 3)) void __NOTHROW(__LIBCCALL __localdep_sincos)(double __x, double *__psinx, double *__pcosx) { return __builtin_sincos(__x, __psinx, __pcosx); }
#elif defined(__CRT_HAVE_sincos)
/* Cosine and sine of X */
__CREDIRECT_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,__localdep_sincos,(double __x, double *__psinx, double *__pcosx),sincos,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincos)
/* Cosine and sine of X */
__CREDIRECT_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,__localdep_sincos,(double __x, double *__psinx, double *__pcosx),__sincos,(__x,__psinx,__pcosx))
#else /* LIBC: sincos */
#undef ____localdep_sincos_defined
#endif /* sincos... */
#endif /* !____localdep_sincos_defined */

__NAMESPACE_LOCAL_BEGIN
/* Cosine and sine of X */
__LOCAL_LIBC(sincosl) __DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)) void
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sincosl))(long double __x,
                                                 long double *__psinx,
                                                 long double *__pcosx) {
#line 837 "kos/src/libc/magic/math.c"
	double __sinx, __cosx;
	__localdep_sincos((double)__x, &__sinx, &__cosx);
	*__psinx = (long double)__sinx;
	*__pcosx = (long double)__cosx;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_sincos || __CRT_HAVE___sincos */
#endif /* !__local_sincosl_defined */
