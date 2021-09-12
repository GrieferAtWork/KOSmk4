/* HASH CRC-32:0xd12f295 */
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
#ifndef __local_acosf_defined
#define __local_acosf_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_acos_defined
#define __local___localdep_acos_defined 1
#if __has_builtin(__builtin_acos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acos)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_acos,(double __x),acos,{ return __builtin_acos(__x); })
#elif defined(__CRT_HAVE_acos)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_acos,(double __x),acos,(__x))
#elif defined(__CRT_HAVE___acos)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_acos,(double __x),__acos,(__x))
#else /* ... */
#undef __local___localdep_acos_defined
#endif /* !... */
#endif /* !__local___localdep_acos_defined */
__LOCAL_LIBC(acosf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(acosf))(float __x) {
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_acos)((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_acosf_defined
#define __local___localdep_acosf_defined 1
#define __localdep_acosf __LIBC_LOCAL_NAME(acosf)
#endif /* !__local___localdep_acosf_defined */
#else /* __CRT_HAVE_acos || __CRT_HAVE___acos */
#undef __local_acosf_defined
#endif /* !__CRT_HAVE_acos && !__CRT_HAVE___acos */
#endif /* !__local_acosf_defined */
