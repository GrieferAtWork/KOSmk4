/* HASH CRC-32:0xa0c56d6c */
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
#ifndef __local_erfcf_defined
#define __local_erfcf_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_erfc_defined
#define __local___localdep_erfc_defined 1
#if __has_builtin(__builtin_erfc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfc)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_erfc,(double __x),erfc,{ return __builtin_erfc(__x); })
#elif defined(__CRT_HAVE_erfc)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_erfc,(double __x),erfc,(__x))
#elif defined(__CRT_HAVE___erfc)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_erfc,(double __x),__erfc,(__x))
#else /* ... */
#undef __local___localdep_erfc_defined
#endif /* !... */
#endif /* !__local___localdep_erfc_defined */
__LOCAL_LIBC(erfcf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(erfcf))(float __x) {
	return (float)__NAMESPACE_LOCAL_SYM __localdep_erfc((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_erfcf_defined
#define __local___localdep_erfcf_defined 1
#define __localdep_erfcf __LIBC_LOCAL_NAME(erfcf)
#endif /* !__local___localdep_erfcf_defined */
#else /* __CRT_HAVE_erfc || __CRT_HAVE___erfc */
#undef __local_erfcf_defined
#endif /* !__CRT_HAVE_erfc && !__CRT_HAVE___erfc */
#endif /* !__local_erfcf_defined */
