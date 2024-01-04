/* HASH CRC-32:0xcde0d2a4 */
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
#ifndef __local_clock_getres_defined
#define __local_clock_getres_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_clock_getres64) || defined(__CRT_HAVE___clock_getres64) || defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres)
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_clock_getres32_defined
#define __local___localdep_clock_getres32_defined
#ifdef __CRT_HAVE_clock_getres
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_clock_getres32,(__clockid_t __clock_id, struct __timespec32 *__res),clock_getres,(__clock_id,__res))
#elif defined(__CRT_HAVE___clock_getres)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_clock_getres32,(__clockid_t __clock_id, struct __timespec32 *__res),__clock_getres,(__clock_id,__res))
#else /* ... */
#undef __local___localdep_clock_getres32_defined
#endif /* !... */
#endif /* !__local___localdep_clock_getres32_defined */
#ifndef __local___localdep_clock_getres64_defined
#define __local___localdep_clock_getres64_defined
#if defined(__CRT_HAVE_clock_getres) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_clock_getres64,(__clockid_t __clock_id, struct __timespec64 *__res),clock_getres,(__clock_id,__res))
#elif defined(__CRT_HAVE___clock_getres) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_clock_getres64,(__clockid_t __clock_id, struct __timespec64 *__res),__clock_getres,(__clock_id,__res))
#elif defined(__CRT_HAVE_clock_getres64)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_clock_getres64,(__clockid_t __clock_id, struct __timespec64 *__res),clock_getres64,(__clock_id,__res))
#elif defined(__CRT_HAVE___clock_getres64)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_clock_getres64,(__clockid_t __clock_id, struct __timespec64 *__res),__clock_getres64,(__clock_id,__res))
#elif defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres)
__NAMESPACE_LOCAL_END
#include <libc/local/time/clock_getres64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_clock_getres64 __LIBC_LOCAL_NAME(clock_getres64)
#else /* ... */
#undef __local___localdep_clock_getres64_defined
#endif /* !... */
#endif /* !__local___localdep_clock_getres64_defined */
__LOCAL_LIBC(clock_getres) __ATTR_OUT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(clock_getres))(__clockid_t __clock_id, struct timespec *__res) {
#if defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres)
	int __result;
	struct __timespec32 __res32;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_clock_getres32)(__clock_id, &__res32);
	if (__result == 0) {
		__res->tv_sec  = (__time64_t)__res32.tv_sec;
		__res->tv_nsec = __res32.tv_nsec;
	}
	return __result;
#else /* __CRT_HAVE_clock_getres || __CRT_HAVE___clock_getres */
	int __result;
	struct __timespec64 __res64;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_clock_getres64)(__clock_id, &__res64);
	if (__result == 0) {
		__res->tv_sec  = (__time32_t)__res64.tv_sec;
		__res->tv_nsec = __res64.tv_nsec;
	}
	return __result;
#endif /* !__CRT_HAVE_clock_getres && !__CRT_HAVE___clock_getres */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_clock_getres_defined
#define __local___localdep_clock_getres_defined
#define __localdep_clock_getres __LIBC_LOCAL_NAME(clock_getres)
#endif /* !__local___localdep_clock_getres_defined */
#else /* __CRT_HAVE_clock_getres64 || __CRT_HAVE___clock_getres64 || __CRT_HAVE_clock_getres || __CRT_HAVE___clock_getres */
#undef __local_clock_getres_defined
#endif /* !__CRT_HAVE_clock_getres64 && !__CRT_HAVE___clock_getres64 && !__CRT_HAVE_clock_getres && !__CRT_HAVE___clock_getres */
#endif /* !__local_clock_getres_defined */
