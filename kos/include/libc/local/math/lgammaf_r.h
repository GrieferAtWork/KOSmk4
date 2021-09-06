/* HASH CRC-32:0x3aa39d43 */
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
#ifndef __local_lgammaf_r_defined
#define __local_lgammaf_r_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_lgamma_r) || defined(__CRT_HAVE___lgamma_r)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_lgamma_r_defined
#define __local___localdep_lgamma_r_defined 1
#if __has_builtin(__builtin_lgamma_r) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgamma_r)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_lgamma_r,(double __x, int *__signgamp),lgamma_r,{ return __builtin_lgamma_r(__x, __signgamp); })
#elif defined(__CRT_HAVE_lgamma_r)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_lgamma_r,(double __x, int *__signgamp),lgamma_r,(__x,__signgamp))
#elif defined(__CRT_HAVE___lgamma_r)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_lgamma_r,(double __x, int *__signgamp),__lgamma_r,(__x,__signgamp))
#else /* ... */
#undef __local___localdep_lgamma_r_defined
#endif /* !... */
#endif /* !__local___localdep_lgamma_r_defined */
__LOCAL_LIBC(lgammaf_r) __ATTR_WUNUSED float
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(lgammaf_r))(float __x, int *__signgamp) {
	return (float)__localdep_lgamma_r((double)__x, __signgamp);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lgammaf_r_defined
#define __local___localdep_lgammaf_r_defined 1
#define __localdep_lgammaf_r __LIBC_LOCAL_NAME(lgammaf_r)
#endif /* !__local___localdep_lgammaf_r_defined */
#else /* __CRT_HAVE_lgamma_r || __CRT_HAVE___lgamma_r */
#undef __local_lgammaf_r_defined
#endif /* !__CRT_HAVE_lgamma_r && !__CRT_HAVE___lgamma_r */
#endif /* !__local_lgammaf_r_defined */
