/* HASH CRC-32:0x1416764b */
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
#ifndef __local_nanosleep_defined
#if defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE_nanosleep64)
#define __local_nanosleep_defined 1
/* Dependency: "nanosleep32" from "time" */
#ifndef ____localdep_nanosleep32_defined
#define ____localdep_nanosleep32_defined 1
#ifdef __CRT_HAVE_nanosleep
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_nanosleep32,(struct __TM_TYPE(timespec) const *__requested_time, struct __timespec32 *__remaining),nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE___nanosleep)
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_nanosleep32,(struct __TM_TYPE(timespec) const *__requested_time, struct __timespec32 *__remaining),__nanosleep,(__requested_time,__remaining))
#else /* LIBC: nanosleep */
#undef ____localdep_nanosleep32_defined
#endif /* nanosleep32... */
#endif /* !____localdep_nanosleep32_defined */

/* Dependency: "nanosleep64" from "time" */
#ifndef ____localdep_nanosleep64_defined
#define ____localdep_nanosleep64_defined 1
#ifdef __CRT_HAVE_nanosleep64
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_nanosleep64,(struct __timespec64 const *__restrict __requested_time, struct __timespec64 *__remaining),nanosleep64,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_nanosleep64,(struct __timespec64 const *__restrict __requested_time, struct __timespec64 *__remaining),nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep)
#include <local/time/nanosleep64.h>
/* Pause execution for a number of nanoseconds */
#define __localdep_nanosleep64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanosleep64))
#else /* CUSTOM: nanosleep64 */
#undef ____localdep_nanosleep64_defined
#endif /* nanosleep64... */
#endif /* !____localdep_nanosleep64_defined */

__NAMESPACE_LOCAL_BEGIN
/* Pause execution for a number of nanoseconds */
__LOCAL_LIBC(nanosleep) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(nanosleep))(struct __TM_TYPE(timespec) const *__requested_time,
                                                       struct __TM_TYPE(timespec) *__remaining) {
#line 924 "kos/src/libc/magic/time.c"
#ifdef __CRT_HAVE_nanosleep
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
#else /* __CRT_HAVE_nanosleep */
	int __result;
	struct __timespec64 __req64, __rem64;
	__req64.tv_sec  = (__time64_t)__requested_time->tv_sec;
	__req64.tv_nsec = __requested_time->tv_nsec;
	__result = __localdep_nanosleep64(&__req64, &__rem64);
	if (!__result && __remaining) {
		__remaining->tv_sec  = (__time32_t)__rem64.tv_sec;
		__remaining->tv_nsec = __rem64.tv_nsec;
	}
	return __result;
#endif /* !__CRT_HAVE_nanosleep */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_nanosleep || __CRT_HAVE_nanosleep64 */
#endif /* !__local_nanosleep_defined */
