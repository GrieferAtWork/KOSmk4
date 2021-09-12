/* HASH CRC-32:0x1685b9d0 */
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
#ifndef __local_timespec_get64_defined
#define __local_timespec_get64_defined 1
#include <__crt.h>
#include <asm/os/clock.h>
#if defined(__CLOCK_REALTIME) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime))
#include <features.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_clock_gettime64_defined
#define __local___localdep_clock_gettime64_defined 1
#ifdef __CRT_HAVE_clock_gettime64
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_clock_gettime64,(__clockid_t __clock_id, struct __timespec64 *__tp),clock_gettime64,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_clock_gettime64,(__clockid_t __clock_id, struct __timespec64 *__tp),clock_gettime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime)
__NAMESPACE_LOCAL_END
#include <libc/local/time/clock_gettime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_clock_gettime64 __LIBC_LOCAL_NAME(clock_gettime64)
#else /* ... */
#undef __local___localdep_clock_gettime64_defined
#endif /* !... */
#endif /* !__local___localdep_clock_gettime64_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/time.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(timespec_get64) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timespec_get64))(struct __timespec64 *__ts, __STDC_INT_AS_UINT_T __base) {
	if (__base == __TIME_UTC) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_clock_gettime64)(__CLOCK_REALTIME, __ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timespec_get64_defined
#define __local___localdep_timespec_get64_defined 1
#define __localdep_timespec_get64 __LIBC_LOCAL_NAME(timespec_get64)
#endif /* !__local___localdep_timespec_get64_defined */
#else /* __CLOCK_REALTIME && (__CRT_HAVE_clock_gettime64 || __CRT_HAVE_clock_gettime || __CRT_HAVE___clock_gettime) */
#undef __local_timespec_get64_defined
#endif /* !__CLOCK_REALTIME || (!__CRT_HAVE_clock_gettime64 && !__CRT_HAVE_clock_gettime && !__CRT_HAVE___clock_gettime) */
#endif /* !__local_timespec_get64_defined */
