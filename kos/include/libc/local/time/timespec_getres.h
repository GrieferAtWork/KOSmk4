/* HASH CRC-32:0x9e507b44 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_timespec_getres_defined
#define __local_timespec_getres_defined
#include <__crt.h>
#include <asm/os/clock.h>
#include <asm/crt/time.h>
#include <features.h>
#include <bits/types.h>
#if defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && (defined(__CRT_HAVE_clock_getres64) || defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres))
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_clock_getres_defined
#define __local___localdep_clock_getres_defined
#if defined(__CRT_HAVE_clock_getres) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_clock_getres,(__clockid_t __clock_id, struct timespec *__res),clock_getres,(__clock_id,__res))
#elif defined(__CRT_HAVE___clock_getres) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_clock_getres,(__clockid_t __clock_id, struct timespec *__res),__clock_getres,(__clock_id,__res))
#elif defined(__CRT_HAVE_clock_getres64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_clock_getres,(__clockid_t __clock_id, struct timespec *__res),clock_getres64,(__clock_id,__res))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/clock_getres.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_clock_getres __LIBC_LOCAL_NAME(clock_getres)
#endif /* !... */
#endif /* !__local___localdep_clock_getres_defined */
__LOCAL_LIBC(timespec_getres) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timespec_getres))(struct timespec *__ts, int __base) {
	if (__base == __TIME_UTC) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_clock_getres)(__CLOCK_REALTIME, __ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timespec_getres_defined
#define __local___localdep_timespec_getres_defined
#define __localdep_timespec_getres __LIBC_LOCAL_NAME(timespec_getres)
#endif /* !__local___localdep_timespec_getres_defined */
#else /* __CLOCK_REALTIME && __TIME_UTC && (__CRT_HAVE_clock_getres64 || __CRT_HAVE_clock_getres || __CRT_HAVE___clock_getres) */
#undef __local_timespec_getres_defined
#endif /* !__CLOCK_REALTIME || !__TIME_UTC || (!__CRT_HAVE_clock_getres64 && !__CRT_HAVE_clock_getres && !__CRT_HAVE___clock_getres) */
#endif /* !__local_timespec_getres_defined */
