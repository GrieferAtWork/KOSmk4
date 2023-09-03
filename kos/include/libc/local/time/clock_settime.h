/* HASH CRC-32:0x50e0ba28 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_clock_settime_defined
#define __local_clock_settime_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_clock_settime64) || defined(__CRT_HAVE___clock_settime64) || defined(__CRT_HAVE_clock_settime) || defined(__CRT_HAVE___clock_settime)
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_clock_settime32_defined
#define __local___localdep_clock_settime32_defined
#ifdef __CRT_HAVE_clock_settime
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,__localdep_clock_settime32,(__clockid_t __clock_id, struct __timespec32 const *__tp),clock_settime,(__clock_id,__tp))
#elif defined(__CRT_HAVE___clock_settime)
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,__localdep_clock_settime32,(__clockid_t __clock_id, struct __timespec32 const *__tp),__clock_settime,(__clock_id,__tp))
#else /* ... */
#undef __local___localdep_clock_settime32_defined
#endif /* !... */
#endif /* !__local___localdep_clock_settime32_defined */
#ifndef __local___localdep_clock_settime64_defined
#define __local___localdep_clock_settime64_defined
#if defined(__CRT_HAVE_clock_settime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,__localdep_clock_settime64,(__clockid_t __clock_id, struct __timespec64 const *__tp),clock_settime,(__clock_id,__tp))
#elif defined(__CRT_HAVE___clock_settime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,__localdep_clock_settime64,(__clockid_t __clock_id, struct __timespec64 const *__tp),__clock_settime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime64)
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,__localdep_clock_settime64,(__clockid_t __clock_id, struct __timespec64 const *__tp),clock_settime64,(__clock_id,__tp))
#elif defined(__CRT_HAVE___clock_settime64)
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,__localdep_clock_settime64,(__clockid_t __clock_id, struct __timespec64 const *__tp),__clock_settime64,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime) || defined(__CRT_HAVE___clock_settime)
__NAMESPACE_LOCAL_END
#include <libc/local/time/clock_settime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_clock_settime64 __LIBC_LOCAL_NAME(clock_settime64)
#else /* ... */
#undef __local___localdep_clock_settime64_defined
#endif /* !... */
#endif /* !__local___localdep_clock_settime64_defined */
__LOCAL_LIBC(clock_settime) __ATTR_IN(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(clock_settime))(__clockid_t __clock_id, struct timespec const *__tp) {
#if defined(__CRT_HAVE_clock_settime) || defined(__CRT_HAVE___clock_settime)
	struct __timespec32 __tp32;
	__tp32.tv_sec  = (__time32_t)__tp->tv_sec;
	__tp32.tv_nsec = __tp->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_clock_settime32)(__clock_id, &__tp32);
#else /* __CRT_HAVE_clock_settime || __CRT_HAVE___clock_settime */
	struct __timespec64 __tp64;
	__tp64.tv_sec  = (__time64_t)__tp->tv_sec;
	__tp64.tv_nsec = __tp->tv_nsec;
	return (__NAMESPACE_LOCAL_SYM __localdep_clock_settime64)(__clock_id, &__tp64);
#endif /* !__CRT_HAVE_clock_settime && !__CRT_HAVE___clock_settime */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_clock_settime_defined
#define __local___localdep_clock_settime_defined
#define __localdep_clock_settime __LIBC_LOCAL_NAME(clock_settime)
#endif /* !__local___localdep_clock_settime_defined */
#else /* __CRT_HAVE_clock_settime64 || __CRT_HAVE___clock_settime64 || __CRT_HAVE_clock_settime || __CRT_HAVE___clock_settime */
#undef __local_clock_settime_defined
#endif /* !__CRT_HAVE_clock_settime64 && !__CRT_HAVE___clock_settime64 && !__CRT_HAVE_clock_settime && !__CRT_HAVE___clock_settime */
#endif /* !__local_clock_settime_defined */
