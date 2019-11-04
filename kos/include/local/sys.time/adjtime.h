/* HASH CRC-32:0x797e22c8 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_adjtime_defined
#if defined(__CRT_HAVE_adjtime) || defined(__CRT_HAVE_adjtime64)
#define __local_adjtime_defined 1
/* Dependency: "adjtime32" from "sys.time" */
#ifndef ____localdep_adjtime32_defined
#define ____localdep_adjtime32_defined 1
#ifdef __CRT_HAVE_adjtime
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_adjtime32,(struct __timeval32 const *__delta, struct __timeval32 *__olddelta),adjtime,(__delta,__olddelta))
#else /* LIBC: adjtime */
#undef ____localdep_adjtime32_defined
#endif /* adjtime32... */
#endif /* !____localdep_adjtime32_defined */

/* Dependency: "adjtime64" from "sys.time" */
#ifndef ____localdep_adjtime64_defined
#define ____localdep_adjtime64_defined 1
#ifdef __CRT_HAVE_adjtime64
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_adjtime64,(struct __timeval64 const *__delta, struct __timeval64 *__olddelta),adjtime64,(__delta,__olddelta))
#elif defined(__CRT_HAVE_adjtime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_adjtime64,(struct __timeval64 const *__delta, struct __timeval64 *__olddelta),adjtime,(__delta,__olddelta))
#elif defined(__CRT_HAVE_adjtime)
#include <local/sys.time/adjtime64.h>
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
#define __localdep_adjtime64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(adjtime64))
#else /* CUSTOM: adjtime64 */
#undef ____localdep_adjtime64_defined
#endif /* adjtime64... */
#endif /* !____localdep_adjtime64_defined */

__NAMESPACE_LOCAL_BEGIN
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__LOCAL_LIBC(adjtime) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(adjtime))(struct __TM_TYPE(timeval) const *__delta,
                                                     struct __TM_TYPE(timeval) *__olddelta) {
#line 340 "kos/src/libc/magic/sys.time.c"
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
#endif /* defined(__CRT_HAVE_adjtime) || defined(__CRT_HAVE_adjtime64) */
#endif /* !__local_adjtime_defined */
