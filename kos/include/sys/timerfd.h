/* HASH CRC-32:0xe3b087c5 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef _SYS_TIMERFD_H
#define _SYS_TIMERFD_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <time.h>
#include <bits/timerfd.h>
#include <bits/types.h>

__SYSDECL_BEGIN

/* Documentation taken from Glibc /usr/include/i386-linux-gnu/sys/timerfd.h */
/* Copyright (C) 2008-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* Bits to be set in the FLAGS parameter of `timerfd_settime'.  */
#ifdef __COMPILER_PREFERR_ENUMS
enum {
	TFD_TIMER_ABSTIME = 1
#define TFD_TIMER_ABSTIME TFD_TIMER_ABSTIME
};
#else /* __COMPILER_PREFERR_ENUMS */
#define TFD_TIMER_ABSTIME 1
#endif /* !__COMPILER_PREFERR_ENUMS */


#ifdef __CC__

#ifdef __CRT_HAVE_timerfd_create
/* Return file descriptor for new interval timer source */
__CDECLARE(,__fd_t,__NOTHROW,timerfd_create,(clockid_t __clock_id, int __flags),(__clock_id,__flags))
#endif /* timerfd_create... */
#if defined(__CRT_HAVE_timerfd_settime64) && defined(__USE_TIME_BITS64)
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout utmr
 * is absolute. Optionally return the old expiration time in OTMR */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timerfd_settime,(__fd_t __ufd, int __flags, struct itimerspec const *__utmr, struct itimerspec *__otmr),timerfd_settime64,(__ufd,__flags,__utmr,__otmr))
#elif defined(__CRT_HAVE_timerfd_settime) && !defined(__USE_TIME_BITS64)
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout utmr
 * is absolute. Optionally return the old expiration time in OTMR */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timerfd_settime,(__fd_t __ufd, int __flags, struct itimerspec const *__utmr, struct itimerspec *__otmr),(__ufd,__flags,__utmr,__otmr))
#elif defined(__CRT_HAVE_timerfd_settime) || defined(__CRT_HAVE_timerfd_settime64)
#include <local/sys.timerfd/timerfd_settime.h>
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout utmr
 * is absolute. Optionally return the old expiration time in OTMR */
__NAMESPACE_LOCAL_USING_OR_IMPL(timerfd_settime, __FORCELOCAL __ATTR_NONNULL((3)) int __NOTHROW_NCX(__LIBCCALL timerfd_settime)(__fd_t __ufd, int __flags, struct itimerspec const *__utmr, struct itimerspec *__otmr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timerfd_settime))(__ufd, __flags, __utmr, __otmr); })
#endif /* timerfd_settime... */
#if defined(__CRT_HAVE_timerfd_gettime64) && defined(__USE_TIME_BITS64)
/* Return the next expiration time of UFD */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,timerfd_gettime,(__fd_t __ufd, struct itimerspec *__restrict __otmr),timerfd_gettime64,(__ufd,__otmr))
#elif defined(__CRT_HAVE_timerfd_gettime) && !defined(__USE_TIME_BITS64)
/* Return the next expiration time of UFD */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,timerfd_gettime,(__fd_t __ufd, struct itimerspec *__restrict __otmr),(__ufd,__otmr))
#elif defined(__CRT_HAVE_timerfd_gettime) || defined(__CRT_HAVE_timerfd_gettime64)
#include <local/sys.timerfd/timerfd_gettime.h>
/* Return the next expiration time of UFD */
__NAMESPACE_LOCAL_USING_OR_IMPL(timerfd_gettime, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL timerfd_gettime)(__fd_t __ufd, struct itimerspec *__restrict __otmr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timerfd_gettime))(__ufd, __otmr); })
#endif /* timerfd_gettime... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_timerfd_settime64
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout utmr
 * is absolute. Optionally return the old expiration time in OTMR */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timerfd_settime64,(__fd_t __ufd, int __flags, struct itimerspec64 const *__utmr, struct itimerspec64 *__otmr),(__ufd,__flags,__utmr,__otmr))
#elif defined(__CRT_HAVE_timerfd_settime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout utmr
 * is absolute. Optionally return the old expiration time in OTMR */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timerfd_settime64,(__fd_t __ufd, int __flags, struct itimerspec64 const *__utmr, struct itimerspec64 *__otmr),timerfd_settime,(__ufd,__flags,__utmr,__otmr))
#elif defined(__CRT_HAVE_timerfd_settime)
#include <local/sys.timerfd/timerfd_settime64.h>
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout utmr
 * is absolute. Optionally return the old expiration time in OTMR */
__NAMESPACE_LOCAL_USING_OR_IMPL(timerfd_settime64, __FORCELOCAL __ATTR_NONNULL((3)) int __NOTHROW_NCX(__LIBCCALL timerfd_settime64)(__fd_t __ufd, int __flags, struct itimerspec64 const *__utmr, struct itimerspec64 *__otmr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timerfd_settime64))(__ufd, __flags, __utmr, __otmr); })
#endif /* timerfd_settime64... */
#ifdef __CRT_HAVE_timerfd_gettime64
/* Return the next expiration time of UFD */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,timerfd_gettime64,(__fd_t __ufd, struct itimerspec64 *__restrict __otmr),(__ufd,__otmr))
#elif defined(__CRT_HAVE_timerfd_gettime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the next expiration time of UFD */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,timerfd_gettime64,(__fd_t __ufd, struct itimerspec64 *__restrict __otmr),timerfd_gettime,(__ufd,__otmr))
#elif defined(__CRT_HAVE_timerfd_gettime)
#include <local/sys.timerfd/timerfd_gettime64.h>
/* Return the next expiration time of UFD */
__NAMESPACE_LOCAL_USING_OR_IMPL(timerfd_gettime64, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL timerfd_gettime64)(__fd_t __ufd, struct itimerspec64 *__restrict __otmr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timerfd_gettime64))(__ufd, __otmr); })
#endif /* timerfd_gettime64... */
#endif /* __USE_TIME64 */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_TIMERFD_H */
