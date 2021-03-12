/* HASH CRC-32:0x17f97a6a */
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
#ifndef __local_tanhf_defined
#define __local_tanhf_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: tanh from math */
#ifndef __local___localdep_tanh_defined
#define __local___localdep_tanh_defined 1
#if __has_builtin(__builtin_tanh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanh)
/* Hyperbolic tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tanh,(double __x),tanh,{ return __builtin_tanh(__x); })
#elif defined(__CRT_HAVE_tanh)
/* Hyperbolic tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tanh,(double __x),tanh,(__x))
#elif defined(__CRT_HAVE___tanh)
/* Hyperbolic tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tanh,(double __x),__tanh,(__x))
#else /* ... */
#undef __local___localdep_tanh_defined
#endif /* !... */
#endif /* !__local___localdep_tanh_defined */
/* Hyperbolic tangent of `x' */
__LOCAL_LIBC(tanhf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(tanhf))(float __x) {
	return (float)__localdep_tanh((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tanhf_defined
#define __local___localdep_tanhf_defined 1
#define __localdep_tanhf __LIBC_LOCAL_NAME(tanhf)
#endif /* !__local___localdep_tanhf_defined */
#else /* __CRT_HAVE_tanh || __CRT_HAVE___tanh */
#undef __local_tanhf_defined
#endif /* !__CRT_HAVE_tanh && !__CRT_HAVE___tanh */
#endif /* !__local_tanhf_defined */
