/* HASH CRC-32:0xe8b5f4d */
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
#ifndef __local_thrd_sleep64_defined
#if defined(__CRT_HAVE_thrd_sleep)
#define __local_thrd_sleep64_defined 1
#include <bits/timespec.h>
#include <bits/timespec.h>
/* Dependency: "thrd_sleep32" from "threads" */
#ifndef ____localdep_thrd_sleep32_defined
#define ____localdep_thrd_sleep32_defined 1
#if defined(__CRT_HAVE_thrd_sleep)
/* Block current thread execution for at least the time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The given `time_point' has passed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_thrd_sleep32,(struct __timespec32 const *__time_point, struct __timespec32 *__remaining),thrd_sleep,(__time_point,__remaining))
#else /* LIBC: thrd_sleep */
#undef ____localdep_thrd_sleep32_defined
#endif /* thrd_sleep32... */
#endif /* !____localdep_thrd_sleep32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Block current thread execution for at least the time pointed by TIME_POINT.
 * The current thread may resume if receives a signal. In that case, if REMAINING
 * is not NULL, the remaining time is stored in the object pointed by it
 * @return:     0: The given `time_point' has passed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
__LOCAL_LIBC(thrd_sleep64) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(thrd_sleep64))(struct __timespec64 const *__time_point,
                                                          struct __timespec64 *__remaining) {
#line 170 "kos/src/libc/magic/threads.c"
	int __result;
	struct __timespec32 __tp32;
	struct __timespec32 __rem32;
	__tp32.tv_sec  = (__time32_t)__time_point->tv_sec;
	__tp32.tv_nsec = __time_point->tv_nsec;
	__result = __localdep_thrd_sleep32(&__tp32, __remaining ? &__rem32 : __NULLPTR);
	if (__result == -1 && __remaining) {
		__remaining->tv_sec = (__time64_t)__rem32.tv_sec;
		__remaining->tv_nsec = __rem32.tv_nsec;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_thrd_sleep) */
#endif /* !__local_thrd_sleep64_defined */
