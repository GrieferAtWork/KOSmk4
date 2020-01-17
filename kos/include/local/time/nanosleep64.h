/* HASH CRC-32:0xc93422d0 */
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
#ifndef __local_nanosleep64_defined
#if defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep)
#define __local_nanosleep64_defined 1
/* Dependency: "nanosleep32" from "time" */
#ifndef ____localdep_nanosleep32_defined
#define ____localdep_nanosleep32_defined 1
#ifdef __CRT_HAVE_nanosleep
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_nanosleep32,(struct timespec const *__requested_time, struct __timespec32 *__remaining),nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE___nanosleep)
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_nanosleep32,(struct timespec const *__requested_time, struct __timespec32 *__remaining),__nanosleep,(__requested_time,__remaining))
#else /* LIBC: nanosleep */
#undef ____localdep_nanosleep32_defined
#endif /* nanosleep32... */
#endif /* !____localdep_nanosleep32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Pause execution for a number of nanoseconds */
__LOCAL_LIBC(nanosleep64) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(nanosleep64))(struct __timespec64 const *__restrict __requested_time,
                                                         struct __timespec64 *__remaining) {
#line 1222 "kos/src/libc/magic/time.c"
	int __result;
	struct __timespec32 __req32, __rem32;
	__req32.tv_sec  = (__time32_t)__requested_time->tv_sec;
	__req32.tv_nsec = __requested_time->tv_nsec;
	__result = __localdep_nanosleep32(&__req32, &__rem32);
	if (!__result && __remaining) {
		__remaining->tv_sec  = (__time64_t)__rem32.tv_sec;
		__remaining->tv_nsec = __rem32.tv_nsec;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_nanosleep || __CRT_HAVE___nanosleep */
#endif /* !__local_nanosleep64_defined */
