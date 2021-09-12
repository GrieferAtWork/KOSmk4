/* HASH CRC-32:0x9e67b282 */
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
#ifndef __local_tgammal_defined
#define __local_tgammal_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tgamma_defined
#define __local___localdep_tgamma_defined 1
#if __has_builtin(__builtin_tgamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgamma)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tgamma,(double __x),tgamma,{ return __builtin_tgamma(__x); })
#elif defined(__CRT_HAVE_tgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tgamma,(double __x),tgamma,(__x))
#elif defined(__CRT_HAVE___tgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tgamma,(double __x),__tgamma,(__x))
#else /* ... */
#undef __local___localdep_tgamma_defined
#endif /* !... */
#endif /* !__local___localdep_tgamma_defined */
__LOCAL_LIBC(tgammal) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(tgammal))(__LONGDOUBLE __x) {
	return (__LONGDOUBLE)__NAMESPACE_LOCAL_SYM __localdep_tgamma((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tgammal_defined
#define __local___localdep_tgammal_defined 1
#define __localdep_tgammal __LIBC_LOCAL_NAME(tgammal)
#endif /* !__local___localdep_tgammal_defined */
#else /* __CRT_HAVE_tgamma || __CRT_HAVE___tgamma */
#undef __local_tgammal_defined
#endif /* !__CRT_HAVE_tgamma && !__CRT_HAVE___tgamma */
#endif /* !__local_tgammal_defined */
