/* HASH CRC-32:0x64926b37 */
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
#ifndef __local_cosf_defined
#define __local_cosf_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: cos from math */
#ifndef __local___localdep_cos_defined
#define __local___localdep_cos_defined 1
#if __has_builtin(__builtin_cos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cos)
/* Cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,__localdep_cos,(double __x),cos,{ return __builtin_cos(__x); })
#elif defined(__CRT_HAVE_cos)
/* Cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,__localdep_cos,(double __x),cos,(__x))
#elif defined(__CRT_HAVE___cos)
/* Cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,__localdep_cos,(double __x),__cos,(__x))
#else /* ... */
#undef __local___localdep_cos_defined
#endif /* !... */
#endif /* !__local___localdep_cos_defined */
/* Cosine of `x' */
__LOCAL_LIBC(cosf) __ATTR_WUNUSED __DECL_SIMD_cosf float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(cosf))(float __x) {
	return (float)__localdep_cos((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cosf_defined
#define __local___localdep_cosf_defined 1
#define __localdep_cosf __LIBC_LOCAL_NAME(cosf)
#endif /* !__local___localdep_cosf_defined */
#else /* __CRT_HAVE_cos || __CRT_HAVE___cos */
#undef __local_cosf_defined
#endif /* !__CRT_HAVE_cos && !__CRT_HAVE___cos */
#endif /* !__local_cosf_defined */
