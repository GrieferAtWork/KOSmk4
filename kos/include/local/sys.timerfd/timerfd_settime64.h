/* HASH CRC-32:0xea4d3751 */
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
#ifndef __local_timerfd_settime64_defined
#if defined(__CRT_HAVE_timerfd_settime)
#define __local_timerfd_settime64_defined 1
/* Dependency: "timerfd_settime32" from "sys.timerfd" */
#ifndef ____localdep_timerfd_settime32_defined
#define ____localdep_timerfd_settime32_defined 1
#if defined(__CRT_HAVE_timerfd_settime)
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout utmr
 * is absolute. Optionally return the old expiration time in OTMR */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,__localdep_timerfd_settime32,(__fd_t __ufd, int __flags, struct __itimerspec32 const *__utmr, struct __itimerspec32 *__otmr),timerfd_settime,(__ufd,__flags,__utmr,__otmr))
#else /* LIBC: timerfd_settime */
#undef ____localdep_timerfd_settime32_defined
#endif /* timerfd_settime32... */
#endif /* !____localdep_timerfd_settime32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout utmr
 * is absolute. Optionally return the old expiration time in OTMR */
__LOCAL_LIBC(timerfd_settime64) __ATTR_NONNULL((3)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timerfd_settime64))(__fd_t __ufd,
                                                               int __flags,
                                                               struct itimerspec64 const *__utmr,
                                                               struct itimerspec64 *__otmr) {
#line 155 "kos/src/libc/magic/sys.timerfd.c"
	int __result;
	struct __itimerspec32 __utmr32, __otmr32;
	__utmr32.__it_interval.tv_sec  = (__time32_t)__utmr->__it_interval.tv_sec;
	__utmr32.__it_interval.tv_nsec = __utmr->__it_interval.tv_nsec;
	__utmr32.__it_value.tv_sec     = (__time32_t)__utmr->__it_value.tv_sec;
	__utmr32.__it_value.tv_nsec    = __utmr->__it_value.tv_nsec;
	__result = __localdep_timerfd_settime32(__ufd, __flags, &__utmr32, __otmr ? &__otmr32 : __NULLPTR);
	if (!__result && __otmr) {
		__otmr->__it_interval.tv_sec  = (__time64_t)__otmr32.__it_interval.tv_sec;
		__otmr->__it_interval.tv_nsec = __otmr32.__it_interval.tv_nsec;
		__otmr->__it_value.tv_sec     = (__time64_t)__otmr32.__it_value.tv_sec;
		__otmr->__it_value.tv_nsec    = __otmr32.__it_value.tv_nsec;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_timerfd_settime) */
#endif /* !__local_timerfd_settime64_defined */
