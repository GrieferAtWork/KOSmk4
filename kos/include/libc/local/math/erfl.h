/* HASH CRC-32:0xd63ac948 */
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
#ifndef __local_erfl_defined
#define __local_erfl_defined
#include <__crt.h>
#if defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_erf_defined
#define __local___localdep_erf_defined
#if __has_builtin(__builtin_erf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erf)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_erf,(double __x),erf,{ return __builtin_erf(__x); })
#elif defined(__CRT_HAVE_erf)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_erf,(double __x),erf,(__x))
#elif defined(__CRT_HAVE___erf)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_erf,(double __x),__erf,(__x))
#else /* ... */
#undef __local___localdep_erf_defined
#endif /* !... */
#endif /* !__local___localdep_erf_defined */
__LOCAL_LIBC(erfl) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(erfl))(__LONGDOUBLE __x) {
	return (__LONGDOUBLE)(__NAMESPACE_LOCAL_SYM __localdep_erf)((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_erfl_defined
#define __local___localdep_erfl_defined
#define __localdep_erfl __LIBC_LOCAL_NAME(erfl)
#endif /* !__local___localdep_erfl_defined */
#else /* __CRT_HAVE_erf || __CRT_HAVE___erf */
#undef __local_erfl_defined
#endif /* !__CRT_HAVE_erf && !__CRT_HAVE___erf */
#endif /* !__local_erfl_defined */
