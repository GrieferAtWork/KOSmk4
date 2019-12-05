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
#ifndef _BITS_TIME_H
#define _BITS_TIME_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>

__SYSDECL_BEGIN

/* System-dependent timing definitions.  Linux version.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
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

#ifndef __DOS_CLOCKS_PER_SEC
#define __DOS_CLOCKS_PER_SEC  ((clock_t)1000)
#endif /* !__DOS_CLOCKS_PER_SEC */

#ifndef __KOS_CLOCKS_PER_SEC
#define __KOS_CLOCKS_PER_SEC  ((clock_t)1000000)
#endif /* !__KOS_CLOCKS_PER_SEC */

#ifndef CLOCKS_PER_SEC
#ifdef __CRT_DOS_PRIMARY
#define CLOCKS_PER_SEC  __DOS_CLOCKS_PER_SEC
#else /* __CRT_DOS_PRIMARY */
#define CLOCKS_PER_SEC  __KOS_CLOCKS_PER_SEC
#endif /* !__CRT_DOS_PRIMARY */
#endif /* !CLOCKS_PER_SEC */

#if (!defined(__STRICT_ANSI__) || defined(__USE_POSIX)) && \
     !defined(__USE_XOPEN2K) && defined(__CC__) && !defined(__USE_ISOC_PURE)
#ifdef __CRT_HAVE___sysconf
__CDECLARE(__ATTR_WUNUSED,long int,__NOTHROW,__sysconf,(int __confno),(__confno))
#define CLK_TCK ((__typedef_clock_t)__sysconf(2))
#elif defined(__CRT_HAVE_sysconf)
__CREDIRECT(__ATTR_WUNUSED,long int,__NOTHROW,__sysconf,(int __confno),sysconf,(__confno))
#define CLK_TCK ((__typedef_clock_t)__sysconf(2))
#else
#define CLK_TCK   CLOCKS_PER_SEC
#endif
#endif


#ifdef __USE_POSIX199309
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME           0 /* Identifier for system-wide realtime clock. */
#endif /* !CLOCK_REALTIME */
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC          1 /* Monotonic system-wide clock. */
#endif /* !CLOCK_MONOTONIC */
#ifndef CLOCK_PROCESS_CPUTIME_ID
#define CLOCK_PROCESS_CPUTIME_ID 2 /* High-resolution timer from the CPU. */
#endif /* !CLOCK_PROCESS_CPUTIME_ID */
#ifndef CLOCK_THREAD_CPUTIME_ID
#define CLOCK_THREAD_CPUTIME_ID  3 /* Thread-specific CPU-time clock. */
#endif /* !CLOCK_THREAD_CPUTIME_ID */
#ifndef CLOCK_MONOTONIC_RAW
#define CLOCK_MONOTONIC_RAW      4 /* Monotonic system-wide clock, not adjusted for frequency scaling. */
#endif /* !CLOCK_MONOTONIC_RAW */
#ifndef CLOCK_REALTIME_COARSE
#define CLOCK_REALTIME_COARSE    5 /* Identifier for system-wide realtime clock, updated only on ticks. */
#endif /* !CLOCK_REALTIME_COARSE */
#ifndef CLOCK_MONOTONIC_COARSE
#define CLOCK_MONOTONIC_COARSE   6 /* Monotonic system-wide clock, updated only on ticks. */
#endif /* !CLOCK_MONOTONIC_COARSE */
#ifndef CLOCK_BOOTTIME
#define CLOCK_BOOTTIME           7 /* Monotonic system-wide clock that includes time spent in suspension. */
#endif /* !CLOCK_BOOTTIME */
#ifndef CLOCK_REALTIME_ALARM
#define CLOCK_REALTIME_ALARM     8 /* Like CLOCK_REALTIME but also wakes suspended system. */
#endif /* !CLOCK_REALTIME_ALARM */
#ifndef CLOCK_BOOTTIME_ALARM
#define CLOCK_BOOTTIME_ALARM     9 /* Like CLOCK_BOOTTIME but also wakes suspended system. */
#endif /* !CLOCK_BOOTTIME_ALARM */
#ifndef CLOCK_TAI
#define CLOCK_TAI               11 /* Like CLOCK_REALTIME but in International Atomic Time. */
#endif /* !CLOCK_TAI */
#ifndef TIMER_ABSTIME
#define TIMER_ABSTIME            1 /* Flag to indicate time is absolute. */
#endif /* !TIMER_ABSTIME */
#endif /* __USE_POSIX199309 */

#ifdef __CC__
#ifdef __USE_GNU
#ifdef __CRT_HAVE_clock_adjtime
struct timex;
__CDECLARE(,int,__NOTHROW_NCX,clock_adjtime,(__clockid_t __clock_id, struct timex *__utx),(__clock_id,__utx))
#endif /* __CRT_HAVE_clock_adjtime */
#endif /* __USE_GNU */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_TIME_H */
