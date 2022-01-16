/* HASH CRC-32:0x69658f10 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_coshf_defined
#define __local_coshf_defined
#include <__crt.h>
#if defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_cosh_defined
#define __local___localdep_cosh_defined
#if __has_builtin(__builtin_cosh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosh)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_cosh,(double __x),cosh,{ return __builtin_cosh(__x); })
#elif defined(__CRT_HAVE_cosh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_cosh,(double __x),cosh,(__x))
#elif defined(__CRT_HAVE___cosh)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_cosh,(double __x),__cosh,(__x))
#else /* ... */
#undef __local___localdep_cosh_defined
#endif /* !... */
#endif /* !__local___localdep_cosh_defined */
__LOCAL_LIBC(coshf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(coshf))(float __x) {
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_cosh)((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_coshf_defined
#define __local___localdep_coshf_defined
#define __localdep_coshf __LIBC_LOCAL_NAME(coshf)
#endif /* !__local___localdep_coshf_defined */
#else /* __CRT_HAVE_cosh || __CRT_HAVE___cosh */
#undef __local_coshf_defined
#endif /* !__CRT_HAVE_cosh && !__CRT_HAVE___cosh */
#endif /* !__local_coshf_defined */
