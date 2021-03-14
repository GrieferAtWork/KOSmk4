/* HASH CRC-32:0xb82c13ae */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_timespec_get_defined
#define __local_timespec_get_defined 1
#include <__crt.h>
#include <asm/os/clock.h>
#if defined(__CLOCK_REALTIME) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime))
#include <features.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: clock_gettime from time */
#ifndef __local___localdep_clock_gettime_defined
#define __local___localdep_clock_gettime_defined 1
#if defined(__CRT_HAVE_clock_gettime64) && defined(__USE_TIME_BITS64)
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_clock_gettime,(__clockid_t __clock_id, struct timespec *__tp),clock_gettime64,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime) && !defined(__USE_TIME_BITS64)
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_clock_gettime,(__clockid_t __clock_id, struct timespec *__tp),clock_gettime,(__clock_id,__tp))
#elif defined(__CRT_HAVE___clock_gettime) && !defined(__USE_TIME_BITS64)
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_clock_gettime,(__clockid_t __clock_id, struct timespec *__tp),__clock_gettime,(__clock_id,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/clock_gettime.h>
__NAMESPACE_LOCAL_BEGIN
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
#define __localdep_clock_gettime __LIBC_LOCAL_NAME(clock_gettime)
#endif /* !... */
#endif /* !__local___localdep_clock_gettime_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/time.h>
__NAMESPACE_LOCAL_BEGIN
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__LOCAL_LIBC(timespec_get) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timespec_get))(struct timespec *__ts, __STDC_INT_AS_UINT_T __base) {
	if (__base == __TIME_UTC) {
		if (__localdep_clock_gettime(__CLOCK_REALTIME, __ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timespec_get_defined
#define __local___localdep_timespec_get_defined 1
#define __localdep_timespec_get __LIBC_LOCAL_NAME(timespec_get)
#endif /* !__local___localdep_timespec_get_defined */
#else /* __CLOCK_REALTIME && (__CRT_HAVE_clock_gettime64 || __CRT_HAVE_clock_gettime || __CRT_HAVE___clock_gettime) */
#undef __local_timespec_get_defined
#endif /* !__CLOCK_REALTIME || (!__CRT_HAVE_clock_gettime64 && !__CRT_HAVE_clock_gettime && !__CRT_HAVE___clock_gettime) */
#endif /* !__local_timespec_get_defined */
