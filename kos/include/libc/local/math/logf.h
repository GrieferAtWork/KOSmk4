/* HASH CRC-32:0xd69e8a44 */
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
#ifndef __local_logf_defined
#define __local_logf_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_log_defined
#define __local___localdep_log_defined 1
#if __has_builtin(__builtin_log) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log)
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,__localdep_log,(double __x),log,{ return __builtin_log(__x); })
#elif defined(__CRT_HAVE_log)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,__localdep_log,(double __x),log,(__x))
#elif defined(__CRT_HAVE___log)
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,__localdep_log,(double __x),__log,(__x))
#else /* ... */
#undef __local___localdep_log_defined
#endif /* !... */
#endif /* !__local___localdep_log_defined */
__LOCAL_LIBC(logf) __ATTR_WUNUSED __DECL_SIMD_logf float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(logf))(float __x) {
	return (float)__localdep_log((double)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_logf_defined
#define __local___localdep_logf_defined 1
#define __localdep_logf __LIBC_LOCAL_NAME(logf)
#endif /* !__local___localdep_logf_defined */
#else /* __CRT_HAVE_log || __CRT_HAVE___log */
#undef __local_logf_defined
#endif /* !__CRT_HAVE_log && !__CRT_HAVE___log */
#endif /* !__local_logf_defined */
