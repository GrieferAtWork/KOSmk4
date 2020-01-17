/* HASH CRC-32:0x9e93f374 */
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
#ifndef __local_settimeofday_defined
#if defined(__CRT_HAVE_settimeofday) || defined(__CRT_HAVE_settimeofday64)
#define __local_settimeofday_defined 1
/* Dependency: "settimeofday32" from "sys.time" */
#ifndef ____localdep_settimeofday32_defined
#define ____localdep_settimeofday32_defined 1
#ifdef __CRT_HAVE_settimeofday
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_settimeofday32,(struct __timeval32 const *__tv, struct timezone const *__tz),settimeofday,(__tv,__tz))
#else /* LIBC: settimeofday */
#undef ____localdep_settimeofday32_defined
#endif /* settimeofday32... */
#endif /* !____localdep_settimeofday32_defined */

/* Dependency: "settimeofday64" from "sys.time" */
#ifndef ____localdep_settimeofday64_defined
#define ____localdep_settimeofday64_defined 1
#ifdef __CRT_HAVE_settimeofday64
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_settimeofday64,(struct __timeval64 const *__tv, struct timezone const *__tz),settimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE_settimeofday) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_settimeofday64,(struct __timeval64 const *__tv, struct timezone const *__tz),settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_settimeofday)
#include <local/sys.time/settimeofday64.h>
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
#define __localdep_settimeofday64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(settimeofday64))
#else /* CUSTOM: settimeofday64 */
#undef ____localdep_settimeofday64_defined
#endif /* settimeofday64... */
#endif /* !____localdep_settimeofday64_defined */

__NAMESPACE_LOCAL_BEGIN
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
__LOCAL_LIBC(settimeofday) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(settimeofday))(struct timeval const *__tv,
                                                          struct timezone const *__tz) {
#line 313 "kos/src/libc/magic/sys.time.c"
#ifdef __CRT_HAVE_settimeofday
	struct __timeval32 __tv32;
	if (!__tv)
		return __localdep_settimeofday32(__NULLPTR, __tz);
	__tv32.tv_sec  = (__time32_t)__tv->tv_sec;
	__tv32.tv_usec = __tv->tv_usec;
	return __localdep_settimeofday32(&__tv32, __tz);
#else /* __CRT_HAVE_settimeofday */
	struct __timeval64 __tv64;
	if (!__tv)
		return __localdep_settimeofday64(__NULLPTR, __tz);
	__tv64.tv_sec  = (__time64_t)__tv->tv_sec;
	__tv64.tv_usec = __tv->tv_usec;
	return __localdep_settimeofday64(&__tv64, __tz);
#endif /* !__CRT_HAVE_settimeofday */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_settimeofday || __CRT_HAVE_settimeofday64 */
#endif /* !__local_settimeofday_defined */
