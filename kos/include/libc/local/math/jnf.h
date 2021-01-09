/* HASH CRC-32:0x927e48a6 */
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
#ifndef __local_jnf_defined
#define __local_jnf_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_jn) || defined(__CRT_HAVE___jn)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: jn from math */
#ifndef __local___localdep_jn_defined
#define __local___localdep_jn_defined 1
#if __has_builtin(__builtin_jn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_jn)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_jn,(int __n, double __x),jn,{ return __builtin_jn(__n, __x); })
#elif defined(__CRT_HAVE_jn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_jn,(int __n, double __x),jn,(__n,__x))
#elif defined(__CRT_HAVE___jn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_jn,(int __n, double __x),__jn,(__n,__x))
#else /* ... */
#undef __local___localdep_jn_defined
#endif /* !... */
#endif /* !__local___localdep_jn_defined */
__LOCAL_LIBC(jnf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(jnf))(int __n, float __x) {
	return (float)__localdep_jn(__n, (double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_jnf_defined
#define __local___localdep_jnf_defined 1
#define __localdep_jnf __LIBC_LOCAL_NAME(jnf)
#endif /* !__local___localdep_jnf_defined */
#else /* __CRT_HAVE_jn || __CRT_HAVE___jn */
#undef __local_jnf_defined
#endif /* !__CRT_HAVE_jn && !__CRT_HAVE___jn */
#endif /* !__local_jnf_defined */
