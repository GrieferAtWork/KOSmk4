/* HASH CRC-32:0xa7dd1bd2 */
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
#ifndef __local_gettimeofday_defined
#define __local_gettimeofday_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: gettimeofday32 from sys.time */
#ifndef __local___localdep_gettimeofday32_defined
#define __local___localdep_gettimeofday32_defined 1
#ifdef __CRT_HAVE_gettimeofday
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_gettimeofday32,(struct __timeval32 *__restrict __tv, void * __tz),gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___gettimeofday)
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_gettimeofday32,(struct __timeval32 *__restrict __tv, void * __tz),__gettimeofday,(__tv,__tz))
#else /* ... */
#undef __local___localdep_gettimeofday32_defined
#endif /* !... */
#endif /* !__local___localdep_gettimeofday32_defined */
/* Dependency: gettimeofday64 from sys.time */
#ifndef __local___localdep_gettimeofday64_defined
#define __local___localdep_gettimeofday64_defined 1
#ifdef __CRT_HAVE_gettimeofday64
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),gettimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_gettimeofday64,(struct __timeval64 *__restrict __tv, void * __tz),gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.time/gettimeofday64.h>
__NAMESPACE_LOCAL_BEGIN
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
#define __localdep_gettimeofday64 __LIBC_LOCAL_NAME(gettimeofday64)
#else /* ... */
#undef __local___localdep_gettimeofday64_defined
#endif /* !... */
#endif /* !__local___localdep_gettimeofday64_defined */
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__LOCAL_LIBC(gettimeofday) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gettimeofday))(struct timeval *__restrict __tv, void * __tz) {
#if defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday)
	int __result;
	struct __timeval32 __tv32;
	if (!__tv)
		return __localdep_gettimeofday32(__NULLPTR, __tz);
	__result = __localdep_gettimeofday32(&__tv32, __tz);
	if __likely(!__result) {
		__tv->tv_sec  = (__time64_t)__tv32.tv_sec;
		__tv->tv_usec = __tv32.tv_usec;
	}
	return __result;
#else /* __CRT_HAVE_gettimeofday || __CRT_HAVE___gettimeofday */
	int __result;
	struct __timeval64 __tv64;
	if (!__tv)
		return __localdep_gettimeofday64(__NULLPTR, __tz);
	__result = __localdep_gettimeofday64(&__tv64, __tz);
	if __likely(!__result) {
		__tv->tv_sec  = (__time32_t)__tv64.tv_sec;
		__tv->tv_usec = __tv64.tv_usec;
	}
	return __result;
#endif /* !__CRT_HAVE_gettimeofday && !__CRT_HAVE___gettimeofday */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_gettimeofday_defined
#define __local___localdep_gettimeofday_defined 1
#define __localdep_gettimeofday __LIBC_LOCAL_NAME(gettimeofday)
#endif /* !__local___localdep_gettimeofday_defined */
#else /* __CRT_HAVE_gettimeofday64 || __CRT_HAVE_gettimeofday || __CRT_HAVE___gettimeofday */
#undef __local_gettimeofday_defined
#endif /* !__CRT_HAVE_gettimeofday64 && !__CRT_HAVE_gettimeofday && !__CRT_HAVE___gettimeofday */
#endif /* !__local_gettimeofday_defined */
