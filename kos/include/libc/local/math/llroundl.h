/* HASH CRC-32:0xeebab005 */
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
#ifndef __local_llroundl_defined
#define __local_llroundl_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: roundl from math */
#ifndef __local___localdep_roundl_defined
#define __local___localdep_roundl_defined 1
#if __has_builtin(__builtin_roundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_roundl,(__LONGDOUBLE __x),roundl,{ return __builtin_roundl(__x); })
#elif defined(__CRT_HAVE_roundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_roundl,(__LONGDOUBLE __x),roundl,(__x))
#elif defined(__CRT_HAVE___roundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_roundl,(__LONGDOUBLE __x),__roundl,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/roundl.h>
__NAMESPACE_LOCAL_BEGIN
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
#define __localdep_roundl __LIBC_LOCAL_NAME(roundl)
#endif /* !... */
#endif /* !__local___localdep_roundl_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <libm/lround.h>
__NAMESPACE_LOCAL_BEGIN
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__LOCAL_LIBC(llroundl) __ATTR_CONST __ATTR_WUNUSED __LONGLONG
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(llroundl))(__LONGDOUBLE __x) {
#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(llround, __x);
#else /* __LIBM_MATHFUNIL */
	return (__LONGLONG)__localdep_roundl(__x);
#endif /* !__LIBM_MATHFUNIL */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_llroundl_defined
#define __local___localdep_llroundl_defined 1
#define __localdep_llroundl __LIBC_LOCAL_NAME(llroundl)
#endif /* !__local___localdep_llroundl_defined */
#endif /* !__local_llroundl_defined */
