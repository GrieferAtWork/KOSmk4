/* HASH CRC-32:0x4ea099d9 */
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
#ifndef __local_clock_nanosleep_defined
#if defined(__CRT_HAVE_clock_nanosleep) || defined(__CRT_HAVE___clock_nanosleep) || defined(__CRT_HAVE_clock_nanosleep64)
#define __local_clock_nanosleep_defined 1
/* Dependency: "clock_nanosleep32" from "time" */
#ifndef ____localdep_clock_nanosleep32_defined
#define ____localdep_clock_nanosleep32_defined 1
#ifdef __CRT_HAVE_clock_nanosleep
/* High-resolution sleep with the specified clock */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,__localdep_clock_nanosleep32,(__clockid_t __clock_id, int __flags, struct __timespec32 const *__restrict __requested_time, struct __timespec32 *__remaining),clock_nanosleep,(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE___clock_nanosleep)
/* High-resolution sleep with the specified clock */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,__localdep_clock_nanosleep32,(__clockid_t __clock_id, int __flags, struct __timespec32 const *__restrict __requested_time, struct __timespec32 *__remaining),__clock_nanosleep,(__clock_id,__flags,__requested_time,__remaining))
#else /* LIBC: clock_nanosleep */
#undef ____localdep_clock_nanosleep32_defined
#endif /* clock_nanosleep32... */
#endif /* !____localdep_clock_nanosleep32_defined */

/* Dependency: "clock_nanosleep64" from "time" */
#ifndef ____localdep_clock_nanosleep64_defined
#define ____localdep_clock_nanosleep64_defined 1
#ifdef __CRT_HAVE_clock_nanosleep64
/* High-resolution sleep with the specified clock */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,__localdep_clock_nanosleep64,(__clockid_t __clock_id, int __flags, struct __timespec64 const *__requested_time, struct __timespec64 *__remaining),clock_nanosleep64,(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE_clock_nanosleep) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* High-resolution sleep with the specified clock */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,__localdep_clock_nanosleep64,(__clockid_t __clock_id, int __flags, struct __timespec64 const *__requested_time, struct __timespec64 *__remaining),clock_nanosleep,(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE_clock_nanosleep) || defined(__CRT_HAVE___clock_nanosleep)
#include <local/time/clock_nanosleep64.h>
/* High-resolution sleep with the specified clock */
#define __localdep_clock_nanosleep64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_nanosleep64))
#else /* CUSTOM: clock_nanosleep64 */
#undef ____localdep_clock_nanosleep64_defined
#endif /* clock_nanosleep64... */
#endif /* !____localdep_clock_nanosleep64_defined */

__NAMESPACE_LOCAL_BEGIN
/* High-resolution sleep with the specified clock */
__LOCAL_LIBC(clock_nanosleep) __ATTR_NONNULL((3)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(clock_nanosleep))(__clockid_t __clock_id,
                                                             int __flags,
                                                             struct timespec const *__restrict __requested_time,
                                                             struct timespec *__remaining) {
#line 1187 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_clock_nanosleep) || defined(__CRT_HAVE___clock_nanosleep)
	int __result;
	struct __timespec32 __req32, __rem32;
	__req32.tv_sec  = (__time32_t)__requested_time->tv_sec;
	__req32.tv_nsec = __requested_time->tv_nsec;
	__result = __localdep_clock_nanosleep32(__clock_id, __flags, &__req32, &__rem32);
	if (!__result && __remaining) {
		__remaining->tv_sec  = (__time64_t)__rem32.tv_sec;
		__remaining->tv_nsec = __rem32.tv_nsec;
	}
	return __result;
#else /* __CRT_HAVE_clock_nanosleep || __CRT_HAVE___clock_nanosleep */
	int __result;
	struct __timespec64 __req64, __rem64;
	__req64.tv_sec  = (__time64_t)__requested_time->tv_sec;
	__req64.tv_nsec = __requested_time->tv_nsec;
	__result = __localdep_clock_nanosleep64(__clock_id, __flags, &__req64, &__rem64);
	if (!__result && __remaining) {
		__remaining->tv_sec  = (__time32_t)__rem64.tv_sec;
		__remaining->tv_nsec = __rem64.tv_nsec;
	}
	return __result;
#endif /* !__CRT_HAVE_clock_nanosleep && !__CRT_HAVE___clock_nanosleep */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_clock_nanosleep || __CRT_HAVE___clock_nanosleep || __CRT_HAVE_clock_nanosleep64 */
#endif /* !__local_clock_nanosleep_defined */
