/* HASH CRC-32:0x58ba8d59 */
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
#ifndef __local_exp2f_defined
#define __local_exp2f_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: exp2 from math */
#ifndef __local___localdep_exp2_defined
#define __local___localdep_exp2_defined 1
#if __has_builtin(__builtin_exp2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2)
/* Compute base-2 exponential of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_exp2,(double __x),exp2,{ return __builtin_exp2(__x); })
#elif defined(__CRT_HAVE_exp2)
/* Compute base-2 exponential of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_exp2,(double __x),exp2,(__x))
#elif defined(__CRT_HAVE___exp2)
/* Compute base-2 exponential of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_exp2,(double __x),__exp2,(__x))
#else /* ... */
#undef __local___localdep_exp2_defined
#endif /* !... */
#endif /* !__local___localdep_exp2_defined */
/* Compute base-2 exponential of `x' */
__LOCAL_LIBC(exp2f) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(exp2f))(float __x) {
	return (float)__localdep_exp2((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_exp2f_defined
#define __local___localdep_exp2f_defined 1
#define __localdep_exp2f __LIBC_LOCAL_NAME(exp2f)
#endif /* !__local___localdep_exp2f_defined */
#else /* __CRT_HAVE_exp2 || __CRT_HAVE___exp2 */
#undef __local_exp2f_defined
#endif /* !__CRT_HAVE_exp2 && !__CRT_HAVE___exp2 */
#endif /* !__local_exp2f_defined */
