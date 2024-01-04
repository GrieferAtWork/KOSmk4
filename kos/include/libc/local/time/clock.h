/* HASH CRC-32:0x44a25e9d */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_clock_defined
#define __local_clock_defined
#include <__crt.h>
#include <asm/os/clock.h>
#include <bits/types.h>
#if (defined(__CLOCK_PROCESS_CPUTIME_ID) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE___clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime))) || defined(__CRT_HAVE_times) || defined(__CRT_HAVE___times) || defined(__CRT_HAVE___libc_times)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_clock_gettime64_defined
#define __local___localdep_clock_gettime64_defined
#if defined(__CRT_HAVE_clock_gettime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_clock_gettime64,(__clockid_t __clock_id, struct __timespec64 *__tp),clock_gettime,(__clock_id,__tp))
#elif defined(__CRT_HAVE___clock_gettime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_clock_gettime64,(__clockid_t __clock_id, struct __timespec64 *__tp),__clock_gettime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime64)
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_clock_gettime64,(__clockid_t __clock_id, struct __timespec64 *__tp),clock_gettime64,(__clock_id,__tp))
#elif defined(__CRT_HAVE___clock_gettime64)
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_clock_gettime64,(__clockid_t __clock_id, struct __timespec64 *__tp),__clock_gettime64,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime)
__NAMESPACE_LOCAL_END
#include <libc/local/time/clock_gettime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_clock_gettime64 __LIBC_LOCAL_NAME(clock_gettime64)
#else /* ... */
#undef __local___localdep_clock_gettime64_defined
#endif /* !... */
#endif /* !__local___localdep_clock_gettime64_defined */
#ifndef __local___localdep_times_defined
#define __local___localdep_times_defined
#ifdef __CRT_HAVE_times
__NAMESPACE_LOCAL_END
#include <bits/os/tms.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1),__clock_t,__NOTHROW_NCX,__localdep_times,(struct tms *__buffer),times,(__buffer))
#elif defined(__CRT_HAVE___times)
__NAMESPACE_LOCAL_END
#include <bits/os/tms.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1),__clock_t,__NOTHROW_NCX,__localdep_times,(struct tms *__buffer),__times,(__buffer))
#elif defined(__CRT_HAVE___libc_times)
__NAMESPACE_LOCAL_END
#include <bits/os/tms.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1),__clock_t,__NOTHROW_NCX,__localdep_times,(struct tms *__buffer),__libc_times,(__buffer))
#else /* ... */
#undef __local___localdep_times_defined
#endif /* !... */
#endif /* !__local___localdep_times_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/timespec.h>
#include <bits/os/tms.h>
#include <hybrid/__overflow.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(clock) __ATTR_WUNUSED __clock_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(clock))(void) {
	__clock_t __result;
#if defined(__CLOCK_PROCESS_CPUTIME_ID) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE___clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime))
	struct __timespec64 __ts;
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_clock_gettime64)(__CLOCK_PROCESS_CPUTIME_ID, &__ts))
		return -1;
	__STATIC_IF((__clock_t)-1 < 0) {
		if (__hybrid_overflow_scast(__ts.tv_sec, &__result))
			goto __overflow;
		if (__hybrid_overflow_smul(__result, __CLOCKS_PER_SEC, &__result))
			goto __overflow;
		if (__hybrid_overflow_sadd(__result, __ts.tv_nsec / (1000000000 / __CLOCKS_PER_SEC), &__result))
			goto __overflow;
	} __STATIC_ELSE((__clock_t)-1 < 0) {
		if (__hybrid_overflow_ucast(__ts.tv_sec, &__result))
			goto __overflow;
		if (__hybrid_overflow_umul(__result, __CLOCKS_PER_SEC, &__result))
			goto __overflow;
		if (__hybrid_overflow_uadd(__result, __ts.tv_nsec / (1000000000 / __CLOCKS_PER_SEC), &__result))
			goto __overflow;
	}
#else /* __CLOCK_PROCESS_CPUTIME_ID && (__CRT_HAVE_clock_gettime64 || __CRT_HAVE___clock_gettime64 || __CRT_HAVE_clock_gettime || __CRT_HAVE___clock_gettime) */
	struct tms __ts;
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_times)(&__ts))
		return -1;
	__STATIC_IF((__clock_t)-1 < 0) {
		if (__hybrid_overflow_scast(__ts.tms_utime, &__result))
			goto __overflow;
		if (__hybrid_overflow_sadd(__result, __ts.tms_stime, &__result))
			goto __overflow;
	} __STATIC_ELSE((__clock_t)-1 < 0) {
		if (__hybrid_overflow_ucast(__ts.tms_utime, &__result))
			goto __overflow;
		if (__hybrid_overflow_uadd(__result, __ts.tms_stime, &__result))
			goto __overflow;
	}
#endif /* !__CLOCK_PROCESS_CPUTIME_ID || (!__CRT_HAVE_clock_gettime64 && !__CRT_HAVE___clock_gettime64 && !__CRT_HAVE_clock_gettime && !__CRT_HAVE___clock_gettime) */
	return __result;
__overflow:
	return (__clock_t)-1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_clock_defined
#define __local___localdep_clock_defined
#define __localdep_clock __LIBC_LOCAL_NAME(clock)
#endif /* !__local___localdep_clock_defined */
#else /* (__CLOCK_PROCESS_CPUTIME_ID && (__CRT_HAVE_clock_gettime64 || __CRT_HAVE___clock_gettime64 || __CRT_HAVE_clock_gettime || __CRT_HAVE___clock_gettime)) || __CRT_HAVE_times || __CRT_HAVE___times || __CRT_HAVE___libc_times */
#undef __local_clock_defined
#endif /* (!__CLOCK_PROCESS_CPUTIME_ID || (!__CRT_HAVE_clock_gettime64 && !__CRT_HAVE___clock_gettime64 && !__CRT_HAVE_clock_gettime && !__CRT_HAVE___clock_gettime)) && !__CRT_HAVE_times && !__CRT_HAVE___times && !__CRT_HAVE___libc_times */
#endif /* !__local_clock_defined */
