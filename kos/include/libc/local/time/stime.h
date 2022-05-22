/* HASH CRC-32:0x80c7a6c */
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
#ifndef __local_stime_defined
#define __local_stime_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_stime64) || defined(__CRT_HAVE_stime) || defined(__CRT_HAVE___stime) || defined(__CRT_HAVE___libc_stime)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_stime32_defined
#define __local___localdep_crt_stime32_defined
#ifdef __CRT_HAVE_stime
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_NCX,__localdep_crt_stime32,(__time32_t const *__when),stime,(__when))
#elif defined(__CRT_HAVE___stime)
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_NCX,__localdep_crt_stime32,(__time32_t const *__when),__stime,(__when))
#elif defined(__CRT_HAVE___libc_stime)
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_NCX,__localdep_crt_stime32,(__time32_t const *__when),__libc_stime,(__when))
#else /* ... */
#undef __local___localdep_crt_stime32_defined
#endif /* !... */
#endif /* !__local___localdep_crt_stime32_defined */
#ifndef __local___localdep_stime64_defined
#define __local___localdep_stime64_defined
#if defined(__CRT_HAVE_stime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_NCX,__localdep_stime64,(__time64_t const *__when),stime,(__when))
#elif defined(__CRT_HAVE___stime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_NCX,__localdep_stime64,(__time64_t const *__when),__stime,(__when))
#elif defined(__CRT_HAVE___libc_stime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_NCX,__localdep_stime64,(__time64_t const *__when),__libc_stime,(__when))
#elif defined(__CRT_HAVE_stime64)
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_NCX,__localdep_stime64,(__time64_t const *__when),stime64,(__when))
#elif defined(__CRT_HAVE_stime) || defined(__CRT_HAVE___stime) || defined(__CRT_HAVE___libc_stime)
__NAMESPACE_LOCAL_END
#include <libc/local/time/stime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_stime64 __LIBC_LOCAL_NAME(stime64)
#else /* ... */
#undef __local___localdep_stime64_defined
#endif /* !... */
#endif /* !__local___localdep_stime64_defined */
__LOCAL_LIBC(stime) __ATTR_ACCESS_RO(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(stime))(__TM_TYPE(time) const *__when) {
#if defined(__CRT_HAVE_stime) || defined(__CRT_HAVE___stime) || defined(__CRT_HAVE___libc_stime)
	__time32_t __when32 = (__time32_t)*__when;
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_stime32)(&__when32);
#else /* __CRT_HAVE_stime || __CRT_HAVE___stime || __CRT_HAVE___libc_stime */
	__time64_t __when64 = (__time64_t)*__when;
	return (__NAMESPACE_LOCAL_SYM __localdep_stime64)(&__when64);
#endif /* !__CRT_HAVE_stime && !__CRT_HAVE___stime && !__CRT_HAVE___libc_stime */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_stime_defined
#define __local___localdep_stime_defined
#define __localdep_stime __LIBC_LOCAL_NAME(stime)
#endif /* !__local___localdep_stime_defined */
#else /* __CRT_HAVE_stime64 || __CRT_HAVE_stime || __CRT_HAVE___stime || __CRT_HAVE___libc_stime */
#undef __local_stime_defined
#endif /* !__CRT_HAVE_stime64 && !__CRT_HAVE_stime && !__CRT_HAVE___stime && !__CRT_HAVE___libc_stime */
#endif /* !__local_stime_defined */
