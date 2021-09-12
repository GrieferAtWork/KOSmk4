/* HASH CRC-32:0x767cf682 */
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
#ifndef __local_stime_defined
#define __local_stime_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_stime64) || defined(__CRT_HAVE_stime)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_stime32_defined) && defined(__CRT_HAVE_stime)
#define __local___localdep_stime32_defined 1
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_stime32,(__time32_t const *__when),stime,(__when))
#endif /* !__local___localdep_stime32_defined && __CRT_HAVE_stime */
#ifndef __local___localdep_stime64_defined
#define __local___localdep_stime64_defined 1
#ifdef __CRT_HAVE_stime64
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_stime64,(__time64_t const *__when),stime64,(__when))
#elif defined(__CRT_HAVE_stime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_stime64,(__time64_t const *__when),stime,(__when))
#elif defined(__CRT_HAVE_stime)
__NAMESPACE_LOCAL_END
#include <libc/local/time/stime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_stime64 __LIBC_LOCAL_NAME(stime64)
#else /* ... */
#undef __local___localdep_stime64_defined
#endif /* !... */
#endif /* !__local___localdep_stime64_defined */
__LOCAL_LIBC(stime) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(stime))(__TM_TYPE(time) const *__when) {
#ifdef __CRT_HAVE_stime
	__time32_t __tms = (__time32_t)*__when;
	return (__NAMESPACE_LOCAL_SYM __localdep_stime32)(&__tms);
#else /* __CRT_HAVE_stime */
	__time64_t __tms = (__time64_t)*__when;
	return (__NAMESPACE_LOCAL_SYM __localdep_stime64)(&__tms);
#endif /* !__CRT_HAVE_stime */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_stime_defined
#define __local___localdep_stime_defined 1
#define __localdep_stime __LIBC_LOCAL_NAME(stime)
#endif /* !__local___localdep_stime_defined */
#else /* __CRT_HAVE_stime64 || __CRT_HAVE_stime */
#undef __local_stime_defined
#endif /* !__CRT_HAVE_stime64 && !__CRT_HAVE_stime */
#endif /* !__local_stime_defined */
