/* HASH CRC-32:0xead86f57 */
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
#ifndef __local_timerfd_settime_defined
#define __local_timerfd_settime_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_timerfd_settime64) || defined(__CRT_HAVE___timerfd_settime64) || defined(__CRT_HAVE_timerfd_settime)
#include <features.h>
#include <bits/os/itimerspec.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_timerfd_settime32_defined) && defined(__CRT_HAVE_timerfd_settime)
#define __local___localdep_timerfd_settime32_defined
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,__localdep_timerfd_settime32,(__fd_t __ufd, __STDC_INT_AS_UINT_T __flags, struct __itimerspec32 const *__utmr, struct __itimerspec32 *__otmr),timerfd_settime,(__ufd,__flags,__utmr,__otmr))
#endif /* !__local___localdep_timerfd_settime32_defined && __CRT_HAVE_timerfd_settime */
#ifndef __local___localdep_timerfd_settime64_defined
#define __local___localdep_timerfd_settime64_defined
#if defined(__CRT_HAVE_timerfd_settime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,__localdep_timerfd_settime64,(__fd_t __ufd, __STDC_INT_AS_UINT_T __flags, struct __itimerspec64 const *__utmr, struct __itimerspec64 *__otmr),timerfd_settime,(__ufd,__flags,__utmr,__otmr))
#elif defined(__CRT_HAVE_timerfd_settime64)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,__localdep_timerfd_settime64,(__fd_t __ufd, __STDC_INT_AS_UINT_T __flags, struct __itimerspec64 const *__utmr, struct __itimerspec64 *__otmr),timerfd_settime64,(__ufd,__flags,__utmr,__otmr))
#elif defined(__CRT_HAVE___timerfd_settime64)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,__localdep_timerfd_settime64,(__fd_t __ufd, __STDC_INT_AS_UINT_T __flags, struct __itimerspec64 const *__utmr, struct __itimerspec64 *__otmr),__timerfd_settime64,(__ufd,__flags,__utmr,__otmr))
#elif defined(__CRT_HAVE_timerfd_settime)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.timerfd/timerfd_settime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_timerfd_settime64 __LIBC_LOCAL_NAME(timerfd_settime64)
#else /* ... */
#undef __local___localdep_timerfd_settime64_defined
#endif /* !... */
#endif /* !__local___localdep_timerfd_settime64_defined */
__LOCAL_LIBC(timerfd_settime) __ATTR_FDARG(1) __ATTR_IN(3) __ATTR_OUT_OPT(4) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timerfd_settime))(__fd_t __ufd, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__utmr, struct itimerspec *__otmr) {
#ifdef __CRT_HAVE_timerfd_settime
	int __result;
	struct __itimerspec32 __utmr32, __otmr32;
	__utmr32.__it_interval.tv_sec  = (__time32_t)__utmr->__it_interval.tv_sec;
	__utmr32.__it_interval.tv_nsec = __utmr->__it_interval.tv_nsec;
	__utmr32.__it_value.tv_sec     = (__time32_t)__utmr->__it_value.tv_sec;
	__utmr32.__it_value.tv_nsec    = __utmr->__it_value.tv_nsec;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_timerfd_settime32)(__ufd, __flags, &__utmr32, __otmr ? &__otmr32 : __NULLPTR);
	if (__result == 0 && __otmr) {
		__otmr->__it_interval.tv_sec  = (__time64_t)__otmr32.__it_interval.tv_sec;
		__otmr->__it_interval.tv_nsec = __otmr32.__it_interval.tv_nsec;
		__otmr->__it_value.tv_sec     = (__time64_t)__otmr32.__it_value.tv_sec;
		__otmr->__it_value.tv_nsec    = __otmr32.__it_value.tv_nsec;
	}
	return __result;
#else /* __CRT_HAVE_timerfd_settime */
	int __result;
	struct __itimerspec64 __utmr64, __otmr64;
	__utmr64.__it_interval.tv_sec  = (__time64_t)__utmr->__it_interval.tv_sec;
	__utmr64.__it_interval.tv_nsec = __utmr->__it_interval.tv_nsec;
	__utmr64.__it_value.tv_sec     = (__time64_t)__utmr->__it_value.tv_sec;
	__utmr64.__it_value.tv_nsec    = __utmr->__it_value.tv_nsec;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_timerfd_settime64)(__timerid, __flags, &__utmr64, __otmr ? &__otmr64 : __NULLPTR);
	if (__result == 0 && __otmr) {
		__otmr->__it_interval.tv_sec  = (__time32_t)__otmr64.__it_interval.tv_sec;
		__otmr->__it_interval.tv_nsec = __otmr64.__it_interval.tv_nsec;
		__otmr->__it_value.tv_sec     = (__time32_t)__otmr64.__it_value.tv_sec;
		__otmr->__it_value.tv_nsec    = __otmr64.__it_value.tv_nsec;
	}
	return __result;
#endif /* !__CRT_HAVE_timerfd_settime */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timerfd_settime_defined
#define __local___localdep_timerfd_settime_defined
#define __localdep_timerfd_settime __LIBC_LOCAL_NAME(timerfd_settime)
#endif /* !__local___localdep_timerfd_settime_defined */
#else /* __CRT_HAVE_timerfd_settime64 || __CRT_HAVE___timerfd_settime64 || __CRT_HAVE_timerfd_settime */
#undef __local_timerfd_settime_defined
#endif /* !__CRT_HAVE_timerfd_settime64 && !__CRT_HAVE___timerfd_settime64 && !__CRT_HAVE_timerfd_settime */
#endif /* !__local_timerfd_settime_defined */
