/* HASH CRC-32:0x2f9f50fc */
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
#ifndef __local_thrd_sleep_defined
#define __local_thrd_sleep_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_thrd_sleep) || defined(__CRT_HAVE_thrd_sleep64) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE_nanosleep64)
#include <bits/timespec.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: crt_thrd_sleep64 from threads */
#if !defined(__local___localdep_crt_thrd_sleep64_defined) && defined(__CRT_HAVE_thrd_sleep64)
#define __local___localdep_crt_thrd_sleep64_defined 1
/* Block current thread execution for at least the (relative) time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_thrd_sleep64,(struct __timespec64 const *__time_point, struct __timespec64 *__remaining),thrd_sleep64,(__time_point,__remaining))
#endif /* !__local___localdep_crt_thrd_sleep64_defined && __CRT_HAVE_thrd_sleep64 */
/* Dependency: nanosleep from time */
#ifndef __local___localdep_nanosleep_defined
#define __local___localdep_nanosleep_defined 1
#if defined(__CRT_HAVE_nanosleep64) && defined(__USE_TIME_BITS64)
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),nanosleep64,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep) && !defined(__USE_TIME_BITS64)
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE___nanosleep)
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),__nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE_nanosleep64)
__NAMESPACE_LOCAL_END
#include <local/time/nanosleep.h>
__NAMESPACE_LOCAL_BEGIN
/* Pause execution for a number of nanoseconds */
#define __localdep_nanosleep __LIBC_LOCAL_NAME(nanosleep)
#else /* ... */
#undef __local___localdep_nanosleep_defined
#endif /* !... */
#endif /* !__local___localdep_nanosleep_defined */
/* Dependency: thrd_sleep32 from threads */
#if !defined(__local___localdep_thrd_sleep32_defined) && defined(__CRT_HAVE_thrd_sleep)
#define __local___localdep_thrd_sleep32_defined 1
/* Block current thread execution for at least the (relative) time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_thrd_sleep32,(struct __timespec32 const *__time_point, struct __timespec32 *__remaining),thrd_sleep,(__time_point,__remaining))
#endif /* !__local___localdep_thrd_sleep32_defined && __CRT_HAVE_thrd_sleep */
__NAMESPACE_LOCAL_END
#include <asm/threads.h>
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* Block current thread execution for at least the (relative) time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__LOCAL_LIBC(thrd_sleep) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(thrd_sleep))(struct timespec const *__time_point, struct timespec *__remaining) {
#ifdef __CRT_HAVE_thrd_sleep
	int __result;
	struct __timespec32 __tp32, __rem32;
	__tp32.tv_sec  = (__time32_t)__time_point->tv_sec;
	__tp32.tv_nsec = __time_point->tv_nsec;
	__result = __localdep_thrd_sleep32(&__tp32, __remaining ? &__rem32 : __NULLPTR);
	if (__result == -1 && __remaining) {
		__remaining->tv_sec = (__time64_t)__rem32.tv_sec;
		__remaining->tv_nsec = __rem32.tv_nsec;
	}
	return __result;
#elif defined(__CRT_HAVE_thrd_sleep64)
	int __result;
	struct __timespec64 __tp64, __rem64;
	__tp64.tv_sec  = (__time64_t)__time_point->tv_sec;
	__tp64.tv_nsec = __time_point->tv_nsec;
	__result = __localdep_crt_thrd_sleep64(&__tp64, __remaining ? &__rem64 : __NULLPTR);
	if (__result == -1 && __remaining) {
		__remaining->tv_sec = (__time32_t)__rem64.tv_sec;
		__remaining->tv_nsec = __rem64.tv_nsec;
	}
	return __result;
#else /* ... */
	int __error;
	__error = __localdep_nanosleep(__time_point, __remaining);
	if __likely(__error == 0)
		return 0;
#if defined(__libc_geterrno) && defined(__EINTR)
	if (__libc_geterrno() == __EINTR)
		return -1;
#endif /* __libc_geterrno && __EINTR */
	return -2;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_thrd_sleep_defined
#define __local___localdep_thrd_sleep_defined 1
#define __localdep_thrd_sleep __LIBC_LOCAL_NAME(thrd_sleep)
#endif /* !__local___localdep_thrd_sleep_defined */
#else /* __CRT_HAVE_thrd_sleep || __CRT_HAVE_thrd_sleep64 || __CRT_HAVE___nanosleep || __CRT_HAVE_nanosleep || __CRT_HAVE_nanosleep64 */
#undef __local_thrd_sleep_defined
#endif /* !__CRT_HAVE_thrd_sleep && !__CRT_HAVE_thrd_sleep64 && !__CRT_HAVE___nanosleep && !__CRT_HAVE_nanosleep && !__CRT_HAVE_nanosleep64 */
#endif /* !__local_thrd_sleep_defined */
