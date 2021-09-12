/* HASH CRC-32:0xc4042f09 */
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
#ifndef __local_ynl_defined
#define __local_ynl_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_yn) || defined(__CRT_HAVE___yn)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_yn_defined
#define __local___localdep_yn_defined 1
#if __has_builtin(__builtin_yn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_yn)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_yn,(int __n, double __x),yn,{ return __builtin_yn(__n, __x); })
#elif defined(__CRT_HAVE_yn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_yn,(int __n, double __x),yn,(__n,__x))
#elif defined(__CRT_HAVE___yn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_yn,(int __n, double __x),__yn,(__n,__x))
#else /* ... */
#undef __local___localdep_yn_defined
#endif /* !... */
#endif /* !__local___localdep_yn_defined */
__LOCAL_LIBC(ynl) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(ynl))(int __n, __LONGDOUBLE __x) {
	return (__LONGDOUBLE)__NAMESPACE_LOCAL_SYM __localdep_yn(__n, (double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ynl_defined
#define __local___localdep_ynl_defined 1
#define __localdep_ynl __LIBC_LOCAL_NAME(ynl)
#endif /* !__local___localdep_ynl_defined */
#else /* __CRT_HAVE_yn || __CRT_HAVE___yn */
#undef __local_ynl_defined
#endif /* !__CRT_HAVE_yn && !__CRT_HAVE___yn */
#endif /* !__local_ynl_defined */
