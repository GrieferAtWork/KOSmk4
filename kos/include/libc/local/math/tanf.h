/* HASH CRC-32:0xae6e302e */
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
#ifndef __local_tanf_defined
#define __local_tanf_defined
#include <__crt.h>
#if defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tan_defined
#define __local___localdep_tan_defined
#if __has_builtin(__builtin_tan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tan)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tan,(double __x),tan,{ return __builtin_tan(__x); })
#elif defined(__CRT_HAVE_tan)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tan,(double __x),tan,(__x))
#elif defined(__CRT_HAVE___tan)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tan,(double __x),__tan,(__x))
#else /* ... */
#undef __local___localdep_tan_defined
#endif /* !... */
#endif /* !__local___localdep_tan_defined */
__LOCAL_LIBC(tanf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(tanf))(float __x) {
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_tan)((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tanf_defined
#define __local___localdep_tanf_defined
#define __localdep_tanf __LIBC_LOCAL_NAME(tanf)
#endif /* !__local___localdep_tanf_defined */
#else /* __CRT_HAVE_tan || __CRT_HAVE___tan */
#undef __local_tanf_defined
#endif /* !__CRT_HAVE_tan && !__CRT_HAVE___tan */
#endif /* !__local_tanf_defined */
