/* HASH CRC-32:0x25c254e0 */
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
#ifndef __local_cosf_defined
#if defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
#define __local_cosf_defined 1
#include <bits/math-vector.h>
/* Dependency: "cos" */
#ifndef ____localdep_cos_defined
#define ____localdep_cos_defined 1
#if __has_builtin(__builtin_cos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cos)
/* Cosine of X */
__EXTERNINLINE __DECL_SIMD_cos __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_cos)(double __x) { return __builtin_cos(__x); }
#elif defined(__CRT_HAVE_cos)
/* Cosine of X */
__CREDIRECT(__DECL_SIMD_cos __ATTR_WUNUSED,double,__NOTHROW,__localdep_cos,(double __x),cos,(__x))
#elif defined(__CRT_HAVE___cos)
/* Cosine of X */
__CREDIRECT(__DECL_SIMD_cos __ATTR_WUNUSED,double,__NOTHROW,__localdep_cos,(double __x),__cos,(__x))
#else /* LIBC: cos */
#undef ____localdep_cos_defined
#endif /* cos... */
#endif /* !____localdep_cos_defined */

__NAMESPACE_LOCAL_BEGIN
/* Cosine of X */
__LOCAL_LIBC(cosf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(cosf))(float __x) {
#line 210 "kos/src/libc/magic/math.c"
	return (float)__localdep_cos((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_cos || __CRT_HAVE___cos */
#endif /* !__local_cosf_defined */
