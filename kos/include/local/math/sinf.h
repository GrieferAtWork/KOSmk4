/* HASH CRC-32:0x3c2eeb9c */
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
#ifndef __local_sinf_defined
#define __local_sinf_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
#include <bits/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: sin from math */
#ifndef __local___localdep_sin_defined
#define __local___localdep_sin_defined 1
#if __has_builtin(__builtin_sin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sin)
/* Sine of X */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sin,double,__NOTHROW,__localdep_sin,(double __x),sin,{ return __builtin_sin(__x); })
#elif defined(__CRT_HAVE_sin)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sin,double,__NOTHROW,__localdep_sin,(double __x),sin,(__x))
#elif defined(__CRT_HAVE___sin)
/* Sine of X */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sin,double,__NOTHROW,__localdep_sin,(double __x),__sin,(__x))
#else /* ... */
#undef __local___localdep_sin_defined
#endif /* !... */
#endif /* !__local___localdep_sin_defined */
/* Sine of X */
__LOCAL_LIBC(sinf) __ATTR_WUNUSED __DECL_SIMD_sinf float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(sinf))(float __x) {
	return (float)__localdep_sin((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sinf_defined
#define __local___localdep_sinf_defined 1
#define __localdep_sinf __LIBC_LOCAL_NAME(sinf)
#endif /* !__local___localdep_sinf_defined */
#else /* __CRT_HAVE_sin || __CRT_HAVE___sin */
#undef __local_sinf_defined
#endif /* !__CRT_HAVE_sin && !__CRT_HAVE___sin */
#endif /* !__local_sinf_defined */
