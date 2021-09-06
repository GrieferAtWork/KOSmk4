/* HASH CRC-32:0x17cc5b97 */
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
#ifndef __local_asinhf_defined
#define __local_asinhf_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_asinh_defined
#define __local___localdep_asinh_defined 1
#if __has_builtin(__builtin_asinh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinh)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_asinh,(double __x),asinh,{ return __builtin_asinh(__x); })
#elif defined(__CRT_HAVE_asinh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_asinh,(double __x),asinh,(__x))
#elif defined(__CRT_HAVE___asinh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_asinh,(double __x),__asinh,(__x))
#else /* ... */
#undef __local___localdep_asinh_defined
#endif /* !... */
#endif /* !__local___localdep_asinh_defined */
__LOCAL_LIBC(asinhf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(asinhf))(float __x) {
	return (float)__localdep_asinh((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_asinhf_defined
#define __local___localdep_asinhf_defined 1
#define __localdep_asinhf __LIBC_LOCAL_NAME(asinhf)
#endif /* !__local___localdep_asinhf_defined */
#else /* __CRT_HAVE_asinh || __CRT_HAVE___asinh */
#undef __local_asinhf_defined
#endif /* !__CRT_HAVE_asinh && !__CRT_HAVE___asinh */
#endif /* !__local_asinhf_defined */
