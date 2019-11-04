/* HASH CRC-32:0xe114a9b9 */
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
#ifndef __local_clock_settime_defined
#if defined(__CRT_HAVE_clock_settime) || defined(__CRT_HAVE_clock_settime64)
#define __local_clock_settime_defined 1
/* Dependency: "clock_settime32" from "time" */
#ifndef ____localdep_clock_settime32_defined
#define ____localdep_clock_settime32_defined 1
#ifdef __CRT_HAVE_clock_settime
/* Set clock CLOCK_ID to value TP */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_clock_settime32,(__clockid_t __clock_id, struct __timespec32 const *__tp),clock_settime,(__clock_id,__tp))
#elif defined(__CRT_HAVE___clock_settime)
/* Set clock CLOCK_ID to value TP */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_clock_settime32,(__clockid_t __clock_id, struct __timespec32 const *__tp),__clock_settime,(__clock_id,__tp))
#else /* LIBC: clock_settime */
#undef ____localdep_clock_settime32_defined
#endif /* clock_settime32... */
#endif /* !____localdep_clock_settime32_defined */

/* Dependency: "clock_settime64" from "time" */
#ifndef ____localdep_clock_settime64_defined
#define ____localdep_clock_settime64_defined 1
#ifdef __CRT_HAVE_clock_settime64
/* Set clock CLOCK_ID to value TP */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_clock_settime64,(__clockid_t __clock_id, struct __timespec64 const *__tp),clock_settime64,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Set clock CLOCK_ID to value TP */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_clock_settime64,(__clockid_t __clock_id, struct __timespec64 const *__tp),clock_settime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime) || defined(__CRT_HAVE___clock_settime)
#include <local/time/clock_settime64.h>
/* Set clock CLOCK_ID to value TP */
#define __localdep_clock_settime64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_settime64))
#else /* CUSTOM: clock_settime64 */
#undef ____localdep_clock_settime64_defined
#endif /* clock_settime64... */
#endif /* !____localdep_clock_settime64_defined */

__NAMESPACE_LOCAL_BEGIN
/* Set clock CLOCK_ID to value TP */
__LOCAL_LIBC(clock_settime) __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(clock_settime))(__clockid_t __clock_id,
                                                           struct __TM_TYPE(timespec) const *__tp) {
#line 1040 "kos/src/libc/magic/time.c"
#ifdef __CRT_HAVE_clock_settime
	struct __timespec32 __tp32;
	__tp32.tv_sec  = (__time32_t)__tp->tv_sec;
	__tp32.tv_nsec = __tp->tv_nsec;
	return __localdep_clock_settime32(__clock_id, &__tp32);
#else
	struct __timespec64 __tp64;
	__tp64.tv_sec  = (__time64_t)__tp->tv_sec;
	__tp64.tv_nsec = __tp->tv_nsec;
	return __localdep_clock_settime64(__clock_id, &__tp64);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_clock_settime) || defined(__CRT_HAVE_clock_settime64) */
#endif /* !__local_clock_settime_defined */
