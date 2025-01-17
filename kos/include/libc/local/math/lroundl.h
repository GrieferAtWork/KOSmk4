/* HASH CRC-32:0xf0e5baf1 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_lroundl_defined
#define __local_lroundl_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_roundl_defined
#define __local___localdep_roundl_defined
#if __has_builtin(__builtin_roundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_roundl,(__LONGDOUBLE __x),roundl,{ return __builtin_roundl(__x); })
#elif defined(__CRT_HAVE_roundl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_roundl,(__LONGDOUBLE __x),roundl,(__x))
#elif defined(__CRT_HAVE___roundl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_roundl,(__LONGDOUBLE __x),__roundl,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_round) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_roundl,(__LONGDOUBLE __x),round,(__x))
#elif defined(__CRT_HAVE___round) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_roundl,(__LONGDOUBLE __x),__round,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/roundl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_roundl __LIBC_LOCAL_NAME(roundl)
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep_roundl_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <libm/lround.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(lroundl) __ATTR_CONST __ATTR_WUNUSED long int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(lroundl))(__LONGDOUBLE __x) {
#ifdef __LIBM_MATHFUNIL
	return __LIBM_MATHFUNIL(lround, __x);
#else /* __LIBM_MATHFUNIL */
	return (long int)(__NAMESPACE_LOCAL_SYM __localdep_roundl)(__x);
#endif /* !__LIBM_MATHFUNIL */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lroundl_defined
#define __local___localdep_lroundl_defined
#define __localdep_lroundl __LIBC_LOCAL_NAME(lroundl)
#endif /* !__local___localdep_lroundl_defined */
#endif /* !__local_lroundl_defined */
