/* HASH CRC-32:0xe78796e2 */
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
#ifndef __local_adjtime_defined
#define __local_adjtime_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_adjtime64) || defined(__CRT_HAVE_adjtime)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: adjtime32 from sys.time */
#if !defined(__local___localdep_adjtime32_defined) && defined(__CRT_HAVE_adjtime)
#define __local___localdep_adjtime32_defined 1
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_adjtime32,(struct __timeval32 const *__delta, struct __timeval32 *__olddelta),adjtime,(__delta,__olddelta))
#endif /* !__local___localdep_adjtime32_defined && __CRT_HAVE_adjtime */
/* Dependency: adjtime64 from sys.time */
#ifndef __local___localdep_adjtime64_defined
#define __local___localdep_adjtime64_defined 1
#ifdef __CRT_HAVE_adjtime64
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_adjtime64,(struct __timeval64 const *__delta, struct __timeval64 *__olddelta),adjtime64,(__delta,__olddelta))
#elif defined(__CRT_HAVE_adjtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_adjtime64,(struct __timeval64 const *__delta, struct __timeval64 *__olddelta),adjtime,(__delta,__olddelta))
#elif defined(__CRT_HAVE_adjtime)
__NAMESPACE_LOCAL_END
#include <local/sys.time/adjtime64.h>
__NAMESPACE_LOCAL_BEGIN
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
#define __localdep_adjtime64 __LIBC_LOCAL_NAME(adjtime64)
#else /* ... */
#undef __local___localdep_adjtime64_defined
#endif /* !... */
#endif /* !__local___localdep_adjtime64_defined */
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__LOCAL_LIBC(adjtime) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(adjtime))(struct timeval const *__delta, struct timeval *__olddelta) {
#ifdef __CRT_HAVE_adjtime
	int __result;
	struct __timeval32 __delta32, __olddelta32;
	if (__delta) {
		__delta32.tv_sec  = (__time32_t)__delta->tv_sec;
		__delta32.tv_usec = __delta->tv_usec;
	}
	__result = __localdep_adjtime32(__which, __delta ? &__delta32 : __NULLPTR, __olddelta ? &__olddelta32 : __NULLPTR);
	if (__likely(!__result) && __olddelta) {
		__olddelta->tv_sec  = (__time64_t)__olddelta32.tv_sec;
		__olddelta->tv_usec = __olddelta32.tv_usec;
	}
	return __result;
#else /* __CRT_HAVE_adjtime */
	int __result;
	struct __timeval64 __delta64, __olddelta64;
	if (__delta) {
		__delta64.tv_sec  = (__time64_t)__delta->tv_sec;
		__delta64.tv_usec = __delta->tv_usec;
	}
	__result = __localdep_adjtime64(__which, __delta ? &__delta64 : __NULLPTR, __olddelta ? &__olddelta64 : __NULLPTR);
	if (__likely(!__result) && __olddelta) {
		__olddelta->tv_sec  = (__time32_t)__olddelta64.tv_sec;
		__olddelta->tv_usec = __olddelta64.tv_usec;
	}
	return __result;
#endif /* !__CRT_HAVE_adjtime */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_adjtime_defined
#define __local___localdep_adjtime_defined 1
#define __localdep_adjtime __LIBC_LOCAL_NAME(adjtime)
#endif /* !__local___localdep_adjtime_defined */
#else /* __CRT_HAVE_adjtime64 || __CRT_HAVE_adjtime */
#undef __local_adjtime_defined
#endif /* !__CRT_HAVE_adjtime64 && !__CRT_HAVE_adjtime */
#endif /* !__local_adjtime_defined */
