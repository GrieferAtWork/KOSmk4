/* HASH CRC-32:0x702c3b15 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_stime_defined
#if defined(__CRT_HAVE_stime) || defined(__CRT_HAVE_stime64)
#define __local_stime_defined 1
/* Dependency: "stime32" from "time" */
#ifndef ____localdep_stime32_defined
#define ____localdep_stime32_defined 1
#ifdef __CRT_HAVE_stime
/* Set the system time to *WHEN. This call is restricted to the superuser */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_stime32,(__time32_t const *__when),stime,(__when))
#else /* LIBC: stime */
#undef ____localdep_stime32_defined
#endif /* stime32... */
#endif /* !____localdep_stime32_defined */

/* Dependency: "stime64" from "time" */
#ifndef ____localdep_stime64_defined
#define ____localdep_stime64_defined 1
#ifdef __CRT_HAVE_stime64
/* Set the system time to *WHEN. This call is restricted to the superuser */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_stime64,(__time64_t const *__when),stime64,(__when))
#elif defined(__CRT_HAVE_stime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Set the system time to *WHEN. This call is restricted to the superuser */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_stime64,(__time64_t const *__when),stime,(__when))
#elif defined(__CRT_HAVE_stime)
#include <local/time/stime64.h>
/* Set the system time to *WHEN. This call is restricted to the superuser */
#define __localdep_stime64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stime64))
#else /* CUSTOM: stime64 */
#undef ____localdep_stime64_defined
#endif /* stime64... */
#endif /* !____localdep_stime64_defined */

__NAMESPACE_LOCAL_BEGIN
/* Set the system time to *WHEN. This call is restricted to the superuser */
__LOCAL_LIBC(stime) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(stime))(__TM_TYPE(time) const *__when) {
#line 859 "kos/src/libc/magic/time.c"
#ifdef __CRT_HAVE_stime
	__time32_t __tms = (__time32_t)*__when;
	return __localdep_stime32(&__tms);
#else /* __CRT_HAVE_stime */
	__time64_t __tms = (__time64_t)*__when;
	return __localdep_stime64(&__tms);
#endif /* !__CRT_HAVE_stime */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_stime || __CRT_HAVE_stime64 */
#endif /* !__local_stime_defined */
