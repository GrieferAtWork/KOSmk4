/* HASH CRC-32:0x27acc72c */
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
#ifndef __local_exp10f_defined
#define __local_exp10f_defined
#include <__crt.h>
#if defined(__CRT_HAVE_exp10) || defined(__CRT_HAVE___exp10)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_exp10_defined
#define __local___localdep_exp10_defined
#if __has_builtin(__builtin_exp10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp10)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_exp10,(double __x),exp10,{ return __builtin_exp10(__x); })
#elif defined(__CRT_HAVE_exp10)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_exp10,(double __x),exp10,(__x))
#elif defined(__CRT_HAVE___exp10)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_exp10,(double __x),__exp10,(__x))
#else /* ... */
#undef __local___localdep_exp10_defined
#endif /* !... */
#endif /* !__local___localdep_exp10_defined */
__LOCAL_LIBC(exp10f) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(exp10f))(float __x) {
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_exp10)((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_exp10f_defined
#define __local___localdep_exp10f_defined
#define __localdep_exp10f __LIBC_LOCAL_NAME(exp10f)
#endif /* !__local___localdep_exp10f_defined */
#else /* __CRT_HAVE_exp10 || __CRT_HAVE___exp10 */
#undef __local_exp10f_defined
#endif /* !__CRT_HAVE_exp10 && !__CRT_HAVE___exp10 */
#endif /* !__local_exp10f_defined */
