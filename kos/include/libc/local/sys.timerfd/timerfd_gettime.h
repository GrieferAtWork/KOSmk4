/* HASH CRC-32:0x6b615e56 */
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
#ifndef __local_timerfd_gettime_defined
#define __local_timerfd_gettime_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_timerfd_gettime64) || defined(__CRT_HAVE___timerfd_gettime64) || defined(__CRT_HAVE_timerfd_gettime)
#include <bits/os/itimerspec.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_timerfd_gettime32_defined) && defined(__CRT_HAVE_timerfd_gettime)
#define __local___localdep_timerfd_gettime32_defined
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_timerfd_gettime32,(__fd_t __ufd, struct __itimerspec32 *__restrict __otmr),timerfd_gettime,(__ufd,__otmr))
#endif /* !__local___localdep_timerfd_gettime32_defined && __CRT_HAVE_timerfd_gettime */
#ifndef __local___localdep_timerfd_gettime64_defined
#define __local___localdep_timerfd_gettime64_defined
#if defined(__CRT_HAVE_timerfd_gettime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_timerfd_gettime64,(__fd_t __ufd, struct __itimerspec64 *__restrict __otmr),timerfd_gettime,(__ufd,__otmr))
#elif defined(__CRT_HAVE_timerfd_gettime64)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_timerfd_gettime64,(__fd_t __ufd, struct __itimerspec64 *__restrict __otmr),timerfd_gettime64,(__ufd,__otmr))
#elif defined(__CRT_HAVE___timerfd_gettime64)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_timerfd_gettime64,(__fd_t __ufd, struct __itimerspec64 *__restrict __otmr),__timerfd_gettime64,(__ufd,__otmr))
#elif defined(__CRT_HAVE_timerfd_gettime)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.timerfd/timerfd_gettime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_timerfd_gettime64 __LIBC_LOCAL_NAME(timerfd_gettime64)
#else /* ... */
#undef __local___localdep_timerfd_gettime64_defined
#endif /* !... */
#endif /* !__local___localdep_timerfd_gettime64_defined */
__LOCAL_LIBC(timerfd_gettime) __ATTR_FDARG(1) __ATTR_OUT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timerfd_gettime))(__fd_t __ufd, struct itimerspec *__restrict __otmr) {
#ifdef __CRT_HAVE_timerfd_gettime
	int __result;
	struct __itimerspec32 __otmr32;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_timerfd_gettime32)(__timerid, &__otmr32);
	if (__result == 0) {
		__otmr->__it_interval.tv_sec  = (__time64_t)__otmr32.__it_interval.tv_sec;
		__otmr->__it_interval.tv_nsec = __otmr32.__it_interval.tv_nsec;
		__otmr->__it_value.tv_sec     = (__time64_t)__otmr32.__it_value.tv_sec;
		__otmr->__it_value.tv_nsec    = __otmr32.__it_value.tv_nsec;
	}
	return __result;
#else /* __CRT_HAVE_timerfd_gettime */
	int __result;
	struct __itimerspec64 __otmr64;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_timerfd_gettime64)(__timerid, &__otmr64);
	if (__result == 0) {
		__otmr->__it_interval.tv_sec  = (__time32_t)__otmr64.__it_interval.tv_sec;
		__otmr->__it_interval.tv_nsec = __otmr64.__it_interval.tv_nsec;
		__otmr->__it_value.tv_sec     = (__time32_t)__otmr64.__it_value.tv_sec;
		__otmr->__it_value.tv_nsec    = __otmr64.__it_value.tv_nsec;
	}
	return __result;
#endif /* !__CRT_HAVE_timerfd_gettime */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timerfd_gettime_defined
#define __local___localdep_timerfd_gettime_defined
#define __localdep_timerfd_gettime __LIBC_LOCAL_NAME(timerfd_gettime)
#endif /* !__local___localdep_timerfd_gettime_defined */
#else /* __CRT_HAVE_timerfd_gettime64 || __CRT_HAVE___timerfd_gettime64 || __CRT_HAVE_timerfd_gettime */
#undef __local_timerfd_gettime_defined
#endif /* !__CRT_HAVE_timerfd_gettime64 && !__CRT_HAVE___timerfd_gettime64 && !__CRT_HAVE_timerfd_gettime */
#endif /* !__local_timerfd_gettime_defined */
