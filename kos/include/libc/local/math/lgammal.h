/* HASH CRC-32:0xe272847 */
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
#ifndef __local_lgammal_defined
#define __local_lgammal_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: lgamma from math */
#ifndef __local___localdep_lgamma_defined
#define __local___localdep_lgamma_defined 1
#if __has_builtin(__builtin_lgamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgamma)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_lgamma,(double __x),lgamma,{ return __builtin_lgamma(__x); })
#elif __has_builtin(__builtin_gamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gamma)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_lgamma,(double __x),gamma,{ return __builtin_gamma(__x); })
#elif defined(__CRT_HAVE_lgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_lgamma,(double __x),lgamma,(__x))
#elif defined(__CRT_HAVE_gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_lgamma,(double __x),gamma,(__x))
#elif defined(__CRT_HAVE___lgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_lgamma,(double __x),__lgamma,(__x))
#elif defined(__CRT_HAVE___gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_lgamma,(double __x),__gamma,(__x))
#else /* ... */
#undef __local___localdep_lgamma_defined
#endif /* !... */
#endif /* !__local___localdep_lgamma_defined */
__LOCAL_LIBC(lgammal) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(lgammal))(__LONGDOUBLE __x) {
	return (__LONGDOUBLE)__localdep_lgamma((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lgammal_defined
#define __local___localdep_lgammal_defined 1
#define __localdep_lgammal __LIBC_LOCAL_NAME(lgammal)
#endif /* !__local___localdep_lgammal_defined */
#else /* __CRT_HAVE_lgamma || __CRT_HAVE_gamma || __CRT_HAVE___lgamma || __CRT_HAVE___gamma */
#undef __local_lgammal_defined
#endif /* !__CRT_HAVE_lgamma && !__CRT_HAVE_gamma && !__CRT_HAVE___lgamma && !__CRT_HAVE___gamma */
#endif /* !__local_lgammal_defined */
