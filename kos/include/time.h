/* HASH CRC-32:0x772dec35 */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _TIME_H
#define _TIME_H 1

#ifdef _CXX_STDONLY_CTIME
#ifdef __CXX_SYSTEM_HEADER
#undef _TIME_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "time.h" after "ctime" */
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __clock_t_defined
#define __clock_t_defined 1
__NAMESPACE_STD_USING(clock_t)
#endif /* !__clock_t_defined */
#ifndef __time_t_defined
#define __time_t_defined 1
__NAMESPACE_STD_USING(time_t)
#endif /* !__time_t_defined */
#ifndef __tm_defined
#define __tm_defined 1
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
#ifdef __CRT_HAVE_clock
__NAMESPACE_STD_USING(clock)
#endif /* __CRT_HAVE_clock */
#if defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_STD_USING(time)
#endif /* __CRT_HAVE_time64 || __CRT_HAVE__time64 || __CRT_HAVE_time || __CRT_HAVE__time32 */
#if !defined(__difftime_defined) && defined(__std_difftime_defined)
#define __difftime_defined 1
__NAMESPACE_STD_USING(difftime)
#endif /* !__difftime_defined && __std_difftime_defined */
__NAMESPACE_STD_USING(mktime)
__NAMESPACE_STD_USING(ctime)
__NAMESPACE_STD_USING(gmtime)
__NAMESPACE_STD_USING(localtime)
__NAMESPACE_STD_USING(strftime)
__NAMESPACE_STD_USING(asctime)
#if !defined(__asctime_s_defined) && defined(__std_asctime_s_defined)
#define __asctime_s_defined 1
__NAMESPACE_STD_USING(asctime_s)
#endif /* !__asctime_s_defined && __std_asctime_s_defined */
#if !defined(__timespec_get_defined) && defined(__std_timespec_get_defined)
#define __timespec_get_defined 1
__NAMESPACE_STD_USING(timespec_get)
#endif /* !__timespec_get_defined && __std_timespec_get_defined */
#undef _CXX_STDONLY_CTIME
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CTIME */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/crt/tm.h>
#include <asm/os/clock.h>
#include <bits/types.h>
#include <hybrid/typecore.h>

#ifdef __USE_POSIX199309
#include <bits/os/timespec.h>
#include <bits/os/itimerval.h>
#endif /* __USE_POSIX199309 */

#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_GNU
#include <asm/os/timex.h>
#include <bits/os/timex.h>

/* Mode code flags (for `struct timex::mode') */
#if !defined(ADJ_OFFSET) && defined(__ADJ_OFFSET)
#define ADJ_OFFSET            __ADJ_OFFSET            /* ??? */
#endif /* !ADJ_OFFSET && __ADJ_OFFSET */
#if !defined(ADJ_FREQUENCY) && defined(__ADJ_FREQUENCY)
#define ADJ_FREQUENCY         __ADJ_FREQUENCY         /* ??? */
#endif /* !ADJ_FREQUENCY && __ADJ_FREQUENCY */
#if !defined(ADJ_MAXERROR) && defined(__ADJ_MAXERROR)
#define ADJ_MAXERROR          __ADJ_MAXERROR          /* ??? */
#endif /* !ADJ_MAXERROR && __ADJ_MAXERROR */
#if !defined(ADJ_ESTERROR) && defined(__ADJ_ESTERROR)
#define ADJ_ESTERROR          __ADJ_ESTERROR          /* ??? */
#endif /* !ADJ_ESTERROR && __ADJ_ESTERROR */
#if !defined(ADJ_STATUS) && defined(__ADJ_STATUS)
#define ADJ_STATUS            __ADJ_STATUS            /* ??? */
#endif /* !ADJ_STATUS && __ADJ_STATUS */
#if !defined(ADJ_TIMECONST) && defined(__ADJ_TIMECONST)
#define ADJ_TIMECONST         __ADJ_TIMECONST         /* ??? */
#endif /* !ADJ_TIMECONST && __ADJ_TIMECONST */
#if !defined(ADJ_TAI) && defined(__ADJ_TAI)
#define ADJ_TAI               __ADJ_TAI               /* ??? */
#endif /* !ADJ_TAI && __ADJ_TAI */
#if !defined(ADJ_SETOFFSET) && defined(__ADJ_SETOFFSET)
#define ADJ_SETOFFSET         __ADJ_SETOFFSET         /* ??? */
#endif /* !ADJ_SETOFFSET && __ADJ_SETOFFSET */
#if !defined(ADJ_MICRO) && defined(__ADJ_MICRO)
#define ADJ_MICRO             __ADJ_MICRO             /* ??? */
#endif /* !ADJ_MICRO && __ADJ_MICRO */
#if !defined(ADJ_NANO) && defined(__ADJ_NANO)
#define ADJ_NANO              __ADJ_NANO              /* ??? */
#endif /* !ADJ_NANO && __ADJ_NANO */
#if !defined(ADJ_TICK) && defined(__ADJ_TICK)
#define ADJ_TICK              __ADJ_TICK              /* ??? */
#endif /* !ADJ_TICK && __ADJ_TICK */
#if !defined(ADJ_OFFSET_SINGLESHOT) && defined(__ADJ_OFFSET_SINGLESHOT)
#define ADJ_OFFSET_SINGLESHOT __ADJ_OFFSET_SINGLESHOT /* ??? */
#endif /* !ADJ_OFFSET_SINGLESHOT && __ADJ_OFFSET_SINGLESHOT */
#if !defined(ADJ_OFFSET_SS_READ) && defined(__ADJ_OFFSET_SS_READ)
#define ADJ_OFFSET_SS_READ    __ADJ_OFFSET_SS_READ    /* ??? */
#endif /* !ADJ_OFFSET_SS_READ && __ADJ_OFFSET_SS_READ */

/* Status code flags (for `struct timex::status') */
#if !defined(STA_PLL) && defined(__STA_PLL)
#define STA_PLL       __STA_PLL       /* ??? */
#endif /* !STA_PLL && __STA_PLL */
#if !defined(STA_PPSFREQ) && defined(__STA_PPSFREQ)
#define STA_PPSFREQ   __STA_PPSFREQ   /* ??? */
#endif /* !STA_PPSFREQ && __STA_PPSFREQ */
#if !defined(STA_PPSTIME) && defined(__STA_PPSTIME)
#define STA_PPSTIME   __STA_PPSTIME   /* ??? */
#endif /* !STA_PPSTIME && __STA_PPSTIME */
#if !defined(STA_FLL) && defined(__STA_FLL)
#define STA_FLL       __STA_FLL       /* ??? */
#endif /* !STA_FLL && __STA_FLL */
#if !defined(STA_INS) && defined(__STA_INS)
#define STA_INS       __STA_INS       /* ??? */
#endif /* !STA_INS && __STA_INS */
#if !defined(STA_DEL) && defined(__STA_DEL)
#define STA_DEL       __STA_DEL       /* ??? */
#endif /* !STA_DEL && __STA_DEL */
#if !defined(STA_UNSYNC) && defined(__STA_UNSYNC)
#define STA_UNSYNC    __STA_UNSYNC    /* ??? */
#endif /* !STA_UNSYNC && __STA_UNSYNC */
#if !defined(STA_FREQHOLD) && defined(__STA_FREQHOLD)
#define STA_FREQHOLD  __STA_FREQHOLD  /* ??? */
#endif /* !STA_FREQHOLD && __STA_FREQHOLD */
#if !defined(STA_PPSSIGNAL) && defined(__STA_PPSSIGNAL)
#define STA_PPSSIGNAL __STA_PPSSIGNAL /* ??? */
#endif /* !STA_PPSSIGNAL && __STA_PPSSIGNAL */
#if !defined(STA_PPSJITTER) && defined(__STA_PPSJITTER)
#define STA_PPSJITTER __STA_PPSJITTER /* ??? */
#endif /* !STA_PPSJITTER && __STA_PPSJITTER */
#if !defined(STA_PPSWANDER) && defined(__STA_PPSWANDER)
#define STA_PPSWANDER __STA_PPSWANDER /* ??? */
#endif /* !STA_PPSWANDER && __STA_PPSWANDER */
#if !defined(STA_PPSERROR) && defined(__STA_PPSERROR)
#define STA_PPSERROR  __STA_PPSERROR  /* ??? */
#endif /* !STA_PPSERROR && __STA_PPSERROR */
#if !defined(STA_CLOCKERR) && defined(__STA_CLOCKERR)
#define STA_CLOCKERR  __STA_CLOCKERR  /* ??? */
#endif /* !STA_CLOCKERR && __STA_CLOCKERR */
#if !defined(STA_NANO) && defined(__STA_NANO)
#define STA_NANO      __STA_NANO      /* ??? */
#endif /* !STA_NANO && __STA_NANO */
#if !defined(STA_MODE) && defined(__STA_MODE)
#define STA_MODE      __STA_MODE      /* ??? */
#endif /* !STA_MODE && __STA_MODE */
#if !defined(STA_CLK) && defined(__STA_CLK)
#define STA_CLK       __STA_CLK       /* ??? */
#endif /* !STA_CLK && __STA_CLK */

/* Read-only bits */
#if !defined(STA_RONLY) && defined(__STA_RONLY)
#define STA_RONLY __STA_RONLY
#endif /* !STA_RONLY && __STA_RONLY */

/* Old alias names */
#if !defined(MOD_OFFSET) && defined(__ADJ_OFFSET)
#define MOD_OFFSET    __ADJ_OFFSET
#endif /* !MOD_OFFSET && __ADJ_OFFSET */
#if !defined(MOD_FREQUENCY) && defined(__ADJ_FREQUENCY)
#define MOD_FREQUENCY __ADJ_FREQUENCY
#endif /* !MOD_FREQUENCY && __ADJ_FREQUENCY */
#if !defined(MOD_MAXERROR) && defined(__ADJ_MAXERROR)
#define MOD_MAXERROR  __ADJ_MAXERROR
#endif /* !MOD_MAXERROR && __ADJ_MAXERROR */
#if !defined(MOD_ESTERROR) && defined(__ADJ_ESTERROR)
#define MOD_ESTERROR  __ADJ_ESTERROR
#endif /* !MOD_ESTERROR && __ADJ_ESTERROR */
#if !defined(MOD_STATUS) && defined(__ADJ_STATUS)
#define MOD_STATUS    __ADJ_STATUS
#endif /* !MOD_STATUS && __ADJ_STATUS */
#if !defined(MOD_TIMECONST) && defined(__ADJ_TIMECONST)
#define MOD_TIMECONST __ADJ_TIMECONST
#endif /* !MOD_TIMECONST && __ADJ_TIMECONST */
#if !defined(MOD_CLKB) && defined(__ADJ_TICK)
#define MOD_CLKB      __ADJ_TICK
#endif /* !MOD_CLKB && __ADJ_TICK */
#if !defined(MOD_CLKA) && defined(__ADJ_OFFSET_SINGLESHOT)
#define MOD_CLKA      __ADJ_OFFSET_SINGLESHOT
#endif /* !MOD_CLKA && __ADJ_OFFSET_SINGLESHOT */
#if !defined(MOD_TAI) && defined(__ADJ_TAI)
#define MOD_TAI       __ADJ_TAI
#endif /* !MOD_TAI && __ADJ_TAI */
#if !defined(MOD_MICRO) && defined(__ADJ_MICRO)
#define MOD_MICRO     __ADJ_MICRO
#endif /* !MOD_MICRO && __ADJ_MICRO */
#if !defined(MOD_NANO) && defined(__ADJ_NANO)
#define MOD_NANO      __ADJ_NANO
#endif /* !MOD_NANO && __ADJ_NANO */
#endif /* __USE_GNU */


/* Some documentation comments are taken from /usr/include/time.h on a linux machine.
 * The following copyright notice can be found at the top of that file: */
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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


__SYSDECL_BEGIN


#ifdef __USE_KOS
#define MSEC_PER_SEC  __UINT16_C(1000)
#define USEC_PER_MSEC __UINT16_C(1000)
#define NSEC_PER_USEC __UINT16_C(1000)
#define NSEC_PER_MSEC __UINT32_C(1000000)
#define USEC_PER_SEC  __UINT32_C(1000000)
#define NSEC_PER_SEC  __UINT32_C(1000000000)
#define FSEC_PER_SEC  __UINT64_C(1000000000000000)
#endif /* __USE_KOS */

#ifdef __USE_ISOC11
#define TIME_UTC 1
#endif /* __USE_ISOC11 */

/* Nonzero if YEAR is a leap year (every 4 years, except every 100th isn't, and every 400th is). */
#ifndef __isleap
#define __isleap(year) ((year)%4 == 0 && ((year)%100 != 0 || (year)%400 == 0))
#endif /* !__isleap */

#ifndef __daystoyears
#define __daystoyears(n_days)  ((400*((n_days)+1))/146097)
#endif /* !__daystoyears */

#ifndef __yearstodays
#define __yearstodays(n_years) (((146097*(n_years))/400)/*-1*/) /* rounding error? */
#endif /* !__yearstodays */

#ifndef NULL
#define NULL __NULLPTR
#endif /* NULL */

#if !defined(CLOCKS_PER_SEC) && defined(__CLOCKS_PER_SEC)
#define CLOCKS_PER_SEC  (__CCAST(clock_t)__CLOCKS_PER_SEC)
#endif /* !CLOCKS_PER_SEC && __CLOCKS_PER_SEC */

#if (!defined(__STRICT_ANSI__) || defined(__USE_POSIX)) && \
     !defined(__USE_XOPEN2K) && defined(__CC__) && !defined(__USE_ISOC_PURE)
__SYSDECL_END
#include <asm/crt/confname.h>
__SYSDECL_BEGIN
#ifdef _SC_CLK_TCK
#ifndef ____os_sysconf_defined
#define ____os_sysconf_defined 1
#ifdef __CRT_HAVE_sysconf
/* >> sysconf(2)
 * @param: NAME: One of `_SC_*' from <asm/crt/confname.h>
 * Return a system configuration value `NAME'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] `NAME' refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,__os_sysconf,(__STDC_INT_AS_UINT_T __name),sysconf,(__name))
#elif defined(__CRT_HAVE__sysconf)
/* >> sysconf(2)
 * @param: NAME: One of `_SC_*' from <asm/crt/confname.h>
 * Return a system configuration value `NAME'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] `NAME' refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,__os_sysconf,(__STDC_INT_AS_UINT_T __name),_sysconf,(__name))
#elif defined(__CRT_HAVE___sysconf)
/* >> sysconf(2)
 * @param: NAME: One of `_SC_*' from <asm/crt/confname.h>
 * Return a system configuration value `NAME'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] `NAME' refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,__os_sysconf,(__STDC_INT_AS_UINT_T __name),__sysconf,(__name))
#else /* ... */
#undef ____os_sysconf_defined
#endif /* !... */
#endif /* !____os_sysconf_defined */
#endif /* _SC_CLK_TCK */
#if defined(____os_sysconf_defined) && defined(_SC_CLK_TCK)
#define CLK_TCK ((__clock_t)__os_sysconf(_SC_CLK_TCK))
#else /* ____os_sysconf_defined && _SC_CLK_TCK */
#define CLK_TCK CLOCKS_PER_SEC
#endif /* !____os_sysconf_defined || !_SC_CLK_TCK */
#endif /* ... */


#ifdef __USE_POSIX199309
#if !defined(CLOCK_REALTIME) && defined(__CLOCK_REALTIME)
#define CLOCK_REALTIME           __CLOCK_REALTIME           /* TODO: Doc */
#endif /* !CLOCK_REALTIME && __CLOCK_REALTIME */
#if !defined(CLOCK_MONOTONIC) && defined(__CLOCK_MONOTONIC)
#define CLOCK_MONOTONIC          __CLOCK_MONOTONIC          /* TODO: Doc */
#endif /* !CLOCK_MONOTONIC && __CLOCK_MONOTONIC */
#if !defined(CLOCK_PROCESS_CPUTIME_ID) && defined(__CLOCK_PROCESS_CPUTIME_ID)
#define CLOCK_PROCESS_CPUTIME_ID __CLOCK_PROCESS_CPUTIME_ID /* TODO: Doc */
#endif /* !CLOCK_PROCESS_CPUTIME_ID && __CLOCK_PROCESS_CPUTIME_ID */
#if !defined(CLOCK_THREAD_CPUTIME_ID) && defined(__CLOCK_THREAD_CPUTIME_ID)
#define CLOCK_THREAD_CPUTIME_ID  __CLOCK_THREAD_CPUTIME_ID  /* TODO: Doc */
#endif /* !CLOCK_THREAD_CPUTIME_ID && __CLOCK_THREAD_CPUTIME_ID */
#if !defined(CLOCK_MONOTONIC_RAW) && defined(__CLOCK_MONOTONIC_RAW)
#define CLOCK_MONOTONIC_RAW      __CLOCK_MONOTONIC_RAW      /* TODO: Doc */
#endif /* !CLOCK_MONOTONIC_RAW && __CLOCK_MONOTONIC_RAW */
#if !defined(CLOCK_REALTIME_COARSE) && defined(__CLOCK_REALTIME_COARSE)
#define CLOCK_REALTIME_COARSE    __CLOCK_REALTIME_COARSE    /* TODO: Doc */
#endif /* !CLOCK_REALTIME_COARSE && __CLOCK_REALTIME_COARSE */
#if !defined(CLOCK_MONOTONIC_COARSE) && defined(__CLOCK_MONOTONIC_COARSE)
#define CLOCK_MONOTONIC_COARSE   __CLOCK_MONOTONIC_COARSE   /* TODO: Doc */
#endif /* !CLOCK_MONOTONIC_COARSE && __CLOCK_MONOTONIC_COARSE */
#if !defined(CLOCK_BOOTTIME) && defined(__CLOCK_BOOTTIME)
#define CLOCK_BOOTTIME           __CLOCK_BOOTTIME           /* TODO: Doc */
#endif /* !CLOCK_BOOTTIME && __CLOCK_BOOTTIME */
#if !defined(CLOCK_REALTIME_ALARM) && defined(__CLOCK_REALTIME_ALARM)
#define CLOCK_REALTIME_ALARM     __CLOCK_REALTIME_ALARM     /* TODO: Doc */
#endif /* !CLOCK_REALTIME_ALARM && __CLOCK_REALTIME_ALARM */
#if !defined(CLOCK_BOOTTIME_ALARM) && defined(__CLOCK_BOOTTIME_ALARM)
#define CLOCK_BOOTTIME_ALARM     __CLOCK_BOOTTIME_ALARM     /* TODO: Doc */
#endif /* !CLOCK_BOOTTIME_ALARM && __CLOCK_BOOTTIME_ALARM */
#if !defined(CLOCK_TAI) && defined(__CLOCK_TAI)
#define CLOCK_TAI                __CLOCK_TAI                /* TODO: Doc */
#endif /* !CLOCK_TAI && __CLOCK_TAI */
#if !defined(TIMER_ABSTIME) && defined(__TIMER_ABSTIME)
#define TIMER_ABSTIME            __TIMER_ABSTIME            /* TODO: Doc */
#endif /* !TIMER_ABSTIME && __TIMER_ABSTIME */
#endif /* __USE_POSIX199309 */


#if (!defined(CLK_TCK) &&                                 \
     (defined(__USE_DOS) || (!defined(__USE_XOPEN2K) &&   \
                             !defined(__STRICT_ANSI__) && \
                             !defined(__USE_ISOC_PURE))))
#define CLK_TCK CLOCKS_PER_SEC
#endif /* !CLK_TCK && (__USE_DOS || (!__USE_XOPEN2K && !__STRICT_ANSI__ && !__USE_ISOC_PURE)) */


#ifdef __CC__

__NAMESPACE_STD_BEGIN
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__std_size_t_defined */
#ifndef __std_clock_t_defined
#define __std_clock_t_defined 1
typedef __clock_t clock_t;
#endif /* !__std_clock_t_defined */
#ifndef __std_time_t_defined
#define __std_time_t_defined 1
typedef __TM_TYPE(time) time_t;
#endif /* !__std_time_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __clock_t_defined
#define __clock_t_defined 1
__NAMESPACE_STD_USING(clock_t)
#endif /* !__clock_t_defined */
#ifndef __time_t_defined
#define __time_t_defined 1
__NAMESPACE_STD_USING(time_t)
#endif /* !__time_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_XOPEN2K
#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#endif /* __USE_XOPEN2K */

#ifdef __USE_TIME64
#ifndef __time64_t_defined
#define __time64_t_defined 1
typedef __time64_t time64_t;
#endif /* !__time64_t_defined */
#endif /* __USE_TIME64 */

#ifdef __USE_POSIX199309
#ifndef __clockid_t_defined
#define __clockid_t_defined 1
typedef __clockid_t clockid_t;
#endif /* !__clockid_t_defined */
#ifndef __timer_t_defined
#define __timer_t_defined 1
typedef __timer_t timer_t;
#endif /* !__timer_t_defined */
#endif /* __USE_POSIX199309 */


#ifndef __CXX_SYSTEM_HEADER
#ifndef __tm_defined
#define __tm_defined 1
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
#endif /* !__CXX_SYSTEM_HEADER */



#ifdef __USE_POSIX199309
struct sigevent;
#endif /* __USE_POSIX199309 */

__NAMESPACE_STD_BEGIN
/* Time used by the program so far (user time + system time)
 * The result / CLOCKS_PER_SECOND is program time in seconds */
__CDECLARE_OPT(__ATTR_WUNUSED,clock_t,__NOTHROW_NCX,clock,(void),())
#if defined(__CRT_HAVE_time64) && defined(__USE_TIME_BITS64)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CREDIRECT(,time_t,__NOTHROW_NCX,time,(time_t *__timer),time64,(__timer))
#elif defined(__CRT_HAVE__time64) && defined(__USE_TIME_BITS64)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CREDIRECT(,time_t,__NOTHROW_NCX,time,(time_t *__timer),_time64,(__timer))
#elif defined(__CRT_HAVE_time) && !defined(__USE_TIME_BITS64)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CDECLARE(,time_t,__NOTHROW_NCX,time,(time_t *__timer),(__timer))
#elif defined(__CRT_HAVE__time32) && !defined(__USE_TIME_BITS64)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CREDIRECT(,time_t,__NOTHROW_NCX,time,(time_t *__timer),_time32,(__timer))
#elif defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_STD_END
#include <libc/local/time/time.h>
__NAMESPACE_STD_BEGIN
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__NAMESPACE_LOCAL_USING_OR_IMPL(time, __FORCELOCAL __ATTR_ARTIFICIAL time_t __NOTHROW_NCX(__LIBCCALL time)(time_t *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(time))(__timer); })
#endif /* ... */
#ifndef __NO_FPU
#ifndef __std_difftime_defined
#define __std_difftime_defined 1
#ifdef __difftime_defined
/* Return the difference between TIME1 and TIME0 */
__NAMESPACE_GLB_USING_OR_IMPL(difftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW_NCX(__LIBCCALL difftime)(time_t __time1, time_t __time0) { return (:: difftime)(__time1, __time0); })
#elif defined(__CRT_HAVE_difftime64) && defined(__USE_TIME_BITS64)
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime,(time_t __time1, time_t __time0),difftime64,(__time1,__time0))
#elif defined(__CRT_HAVE__difftime64) && defined(__USE_TIME_BITS64)
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime,(time_t __time1, time_t __time0),_difftime64,(__time1,__time0))
#elif defined(__CRT_HAVE_difftime) && !defined(__USE_TIME_BITS64)
/* Return the difference between TIME1 and TIME0 */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime,(time_t __time1, time_t __time0),(__time1,__time0))
#elif defined(__CRT_HAVE__difftime32) && !defined(__USE_TIME_BITS64)
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime,(time_t __time1, time_t __time0),_difftime32,(__time1,__time0))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/difftime.h>
__NAMESPACE_STD_BEGIN
/* Return the difference between TIME1 and TIME0 */
__NAMESPACE_LOCAL_USING_OR_IMPL(difftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW_NCX(__LIBCCALL difftime)(time_t __time1, time_t __time0) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(difftime))(__time1, __time0); })
#endif /* !... */
#endif /* !__std_difftime_defined */
#endif /* !__NO_FPU */
#if defined(__CRT_HAVE_mktime64) && defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),time_t,__NOTHROW_NCX,mktime,(struct tm __KOS_FIXED_CONST *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE__mktime64) && defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),time_t,__NOTHROW_NCX,mktime,(struct tm __KOS_FIXED_CONST *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64) && defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),time_t,__NOTHROW_NCX,mktime,(struct tm __KOS_FIXED_CONST *__tp),timelocal64,(__tp))
#elif defined(__CRT_HAVE_mktime) && !defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),time_t,__NOTHROW_NCX,mktime,(struct tm __KOS_FIXED_CONST *__tp),(__tp))
#elif defined(__CRT_HAVE__mktime32) && !defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),time_t,__NOTHROW_NCX,mktime,(struct tm __KOS_FIXED_CONST *__tp),_mktime32,(__tp))
#elif defined(__CRT_HAVE_timelocal) && !defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),time_t,__NOTHROW_NCX,mktime,(struct tm __KOS_FIXED_CONST *__tp),timelocal,(__tp))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/mktime.h>
__NAMESPACE_STD_BEGIN
/* Return the `time_t' representation of TP and normalize TP */
__NAMESPACE_LOCAL_USING_OR_IMPL(mktime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) time_t __NOTHROW_NCX(__LIBCCALL mktime)(struct tm __KOS_FIXED_CONST *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime))(__tp); })
#endif /* !... */
#if defined(__CRT_HAVE_ctime64) && defined(__USE_TIME_BITS64)
/* Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,ctime,(time_t const *__timer),ctime64,(__timer))
#elif defined(__CRT_HAVE__ctime64) && defined(__USE_TIME_BITS64)
/* Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,ctime,(time_t const *__timer),_ctime64,(__timer))
#elif defined(__CRT_HAVE_ctime) && !defined(__USE_TIME_BITS64)
/* Equivalent to `asctime(localtime(timer))' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,ctime,(time_t const *__timer),(__timer))
#elif defined(__CRT_HAVE__ctime32) && !defined(__USE_TIME_BITS64)
/* Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,ctime,(time_t const *__timer),_ctime32,(__timer))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/ctime.h>
__NAMESPACE_STD_BEGIN
/* Equivalent to `asctime(localtime(timer))' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL ctime)(time_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime))(__timer); })
#endif /* !... */
#if defined(__CRT_HAVE_gmtime64) && defined(__USE_TIME_BITS64)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct tm *,__NOTHROW_NCX,gmtime,(time_t const *__timer),gmtime64,(__timer))
#elif defined(__CRT_HAVE__gmtime64) && defined(__USE_TIME_BITS64)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct tm *,__NOTHROW_NCX,gmtime,(time_t const *__timer),_gmtime64,(__timer))
#elif defined(__CRT_HAVE_gmtime) && !defined(__USE_TIME_BITS64)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct tm *,__NOTHROW_NCX,gmtime,(time_t const *__timer),(__timer))
#elif defined(__CRT_HAVE__gmtime32) && !defined(__USE_TIME_BITS64)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct tm *,__NOTHROW_NCX,gmtime,(time_t const *__timer),_gmtime32,(__timer))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/gmtime.h>
__NAMESPACE_STD_BEGIN
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__NAMESPACE_LOCAL_USING_OR_IMPL(gmtime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct tm *__NOTHROW_NCX(__LIBCCALL gmtime)(time_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime))(__timer); })
#endif /* !... */
#if defined(__CRT_HAVE_localtime64) && defined(__USE_TIME_BITS64)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct tm *,__NOTHROW_NCX,localtime,(time_t const *__timer),localtime64,(__timer))
#elif defined(__CRT_HAVE__localtime64) && defined(__USE_TIME_BITS64)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct tm *,__NOTHROW_NCX,localtime,(time_t const *__timer),_localtime64,(__timer))
#elif defined(__CRT_HAVE_localtime) && !defined(__USE_TIME_BITS64)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct tm *,__NOTHROW_NCX,localtime,(time_t const *__timer),(__timer))
#elif defined(__CRT_HAVE__localtime32) && !defined(__USE_TIME_BITS64)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct tm *,__NOTHROW_NCX,localtime,(time_t const *__timer),_localtime32,(__timer))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/localtime.h>
__NAMESPACE_STD_BEGIN
/* Return the `struct tm' representation of *TIMER in the local timezone */
__NAMESPACE_LOCAL_USING_OR_IMPL(localtime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct tm *__NOTHROW_NCX(__LIBCCALL localtime)(time_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime))(__timer); })
#endif /* !... */
#if __has_builtin(__builtin_strftime) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strftime)
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__CEIDECLARE_GCCNCX(__ATTR_NONNULL((1, 3, 4)),size_t,__NOTHROW_NCX,strftime,(char *__restrict __buf, size_t __bufsize, char const *__restrict __format, struct tm const *__restrict __tp),{ return __builtin_strftime(__buf, __bufsize, __format, __tp); })
#elif defined(__CRT_HAVE_strftime)
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__CDECLARE_GCCNCX(__ATTR_NONNULL((1, 3, 4)),size_t,__NOTHROW_NCX,strftime,(char *__restrict __buf, size_t __bufsize, char const *__restrict __format, struct tm const *__restrict __tp),(__buf,__bufsize,__format,__tp))
#elif defined(__CRT_HAVE__Strftime)
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__CREDIRECT_GCCNCX(__ATTR_NONNULL((1, 3, 4)),size_t,__NOTHROW_NCX,strftime,(char *__restrict __buf, size_t __bufsize, char const *__restrict __format, struct tm const *__restrict __tp),_Strftime,(__buf,__bufsize,__format,__tp))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/strftime.h>
__NAMESPACE_STD_BEGIN
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__NAMESPACE_LOCAL_USING_OR_IMPL(strftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3, 4)) size_t __NOTHROW_NCX(__LIBCCALL strftime)(char *__restrict __buf, size_t __bufsize, char const *__restrict __format, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strftime))(__buf, __bufsize, __format, __tp); })
#endif /* !... */
#ifdef __CRT_HAVE_asctime
/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,asctime,(struct tm const *__tp),(__tp))
#else /* __CRT_HAVE_asctime */
__NAMESPACE_STD_END
#include <libc/local/time/asctime.h>
__NAMESPACE_STD_BEGIN
/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
__NAMESPACE_LOCAL_USING_OR_IMPL(asctime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL asctime)(struct tm const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asctime))(__tp); })
#endif /* !__CRT_HAVE_asctime */
#ifdef __USE_ISOC11
#ifndef __std_asctime_s_defined
#define __std_asctime_s_defined 1
#ifdef __asctime_s_defined
__NAMESPACE_GLB_USING_OR_IMPL(asctime_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL asctime_s)(char *__restrict __buf, size_t __buflen, struct tm const *__restrict __tp) { return (:: asctime_s)(__buf, __buflen, __tp); })
#elif defined(__CRT_HAVE_asctime_s)
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,asctime_s,(char *__restrict __buf, size_t __buflen, struct tm const *__restrict __tp),(__buf,__buflen,__tp))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/asctime_s.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(asctime_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL asctime_s)(char *__restrict __buf, size_t __buflen, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asctime_s))(__buf, __buflen, __tp); })
#endif /* !... */
#endif /* !__std_asctime_s_defined */
#endif /* __USE_ISOC11 */
#ifdef __USE_ISOCXX17
#ifndef __std_timespec_get_defined
#define __std_timespec_get_defined 1
#ifdef __timespec_get_defined
/* Set TS to calendar time based in time base BASE */
__NAMESPACE_GLB_USING_OR_IMPL(timespec_get, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL timespec_get)(struct timespec *__ts, __STDC_INT_AS_UINT_T __base) { return (:: timespec_get)(__ts, __base); })
#elif defined(__CRT_HAVE_timespec_get)
/* Set TS to calendar time based in time base BASE */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,timespec_get,(struct timespec *__ts, __STDC_INT_AS_UINT_T __base),(__ts,__base))
#else /* ... */
#undef __std_timespec_get_defined
#endif /* !... */
#endif /* !__std_timespec_get_defined */
#endif /* __USE_ISOCXX17 */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
#ifdef __CRT_HAVE_clock
__NAMESPACE_STD_USING(clock)
#endif /* __CRT_HAVE_clock */
#if defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_STD_USING(time)
#endif /* __CRT_HAVE_time64 || __CRT_HAVE__time64 || __CRT_HAVE_time || __CRT_HAVE__time32 */
#if !defined(__difftime_defined) && defined(__std_difftime_defined)
#define __difftime_defined 1
__NAMESPACE_STD_USING(difftime)
#endif /* !__difftime_defined && __std_difftime_defined */
__NAMESPACE_STD_USING(mktime)
__NAMESPACE_STD_USING(ctime)
__NAMESPACE_STD_USING(gmtime)
__NAMESPACE_STD_USING(localtime)
__NAMESPACE_STD_USING(strftime)
__NAMESPACE_STD_USING(asctime)
#if !defined(__asctime_s_defined) && defined(__std_asctime_s_defined)
#define __asctime_s_defined 1
__NAMESPACE_STD_USING(asctime_s)
#endif /* !__asctime_s_defined && __std_asctime_s_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_time64
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CDECLARE(,__time64_t,__NOTHROW_NCX,time64,(__time64_t *__timer),(__timer))
#elif defined(__CRT_HAVE_time) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CREDIRECT(,__time64_t,__NOTHROW_NCX,time64,(__time64_t *__timer),time,(__timer))
#elif defined(__CRT_HAVE__time64)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CREDIRECT(,__time64_t,__NOTHROW_NCX,time64,(__time64_t *__timer),_time64,(__timer))
#elif defined(__CRT_HAVE_time) || defined(__CRT_HAVE__time32)
#include <libc/local/time/time64.h>
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__NAMESPACE_LOCAL_USING_OR_IMPL(time64, __FORCELOCAL __ATTR_ARTIFICIAL __time64_t __NOTHROW_NCX(__LIBCCALL time64)(__time64_t *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(time64))(__timer); })
#endif /* ... */
#ifndef __NO_FPU
#ifndef __difftime64_defined
#define __difftime64_defined 1
#ifdef __CRT_HAVE_difftime64
/* Return the difference between TIME1 and TIME0 */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime64,(__time64_t __time1, __time64_t __time0),(__time1,__time0))
#elif defined(__CRT_HAVE_difftime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime64,(__time64_t __time1, __time64_t __time0),difftime,(__time1,__time0))
#elif defined(__CRT_HAVE__difftime64)
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime64,(__time64_t __time1, __time64_t __time0),_difftime64,(__time1,__time0))
#elif defined(__CRT_HAVE___difftime64)
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime64,(__time64_t __time1, __time64_t __time0),__difftime64,(__time1,__time0))
#else /* ... */
#include <libc/local/time/difftime64.h>
/* Return the difference between TIME1 and TIME0 */
__NAMESPACE_LOCAL_USING_OR_IMPL(difftime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW_NCX(__LIBCCALL difftime64)(__time64_t __time1, __time64_t __time0) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(difftime64))(__time1, __time0); })
#endif /* !... */
#endif /* !__difftime64_defined */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE_mktime64
/* Return the `time_t' representation of TP and normalize TP */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,mktime64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),(__tp))
#elif defined(__CRT_HAVE_mktime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,mktime64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE__mktime64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,mktime64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,mktime64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),timelocal64,(__tp))
#else /* ... */
#include <libc/local/time/mktime64.h>
/* Return the `time_t' representation of TP and normalize TP */
__NAMESPACE_LOCAL_USING_OR_IMPL(mktime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __time64_t __NOTHROW_NCX(__LIBCCALL mktime64)(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime64))(__tp); })
#endif /* !... */
#ifdef __CRT_HAVE_ctime64
/* Equivalent to `asctime(localtime(timer))' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,ctime64,(__time64_t const *__timer),(__timer))
#elif defined(__CRT_HAVE_ctime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,ctime64,(__time64_t const *__timer),ctime,(__timer))
#elif defined(__CRT_HAVE__ctime64)
/* Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,ctime64,(__time64_t const *__timer),_ctime64,(__timer))
#else /* ... */
#include <libc/local/time/ctime64.h>
/* Equivalent to `asctime(localtime(timer))' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL ctime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime64))(__timer); })
#endif /* !... */
#ifdef __CRT_HAVE_gmtime64
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime64,(__time64_t const *__timer),(__timer))
#elif defined(__CRT_HAVE_gmtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime64,(__time64_t const *__timer),gmtime,(__timer))
#elif defined(__CRT_HAVE__gmtime64)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime64,(__time64_t const *__timer),_gmtime64,(__timer))
#else /* ... */
#include <libc/local/time/gmtime64.h>
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__NAMESPACE_LOCAL_USING_OR_IMPL(gmtime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL gmtime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime64))(__timer); })
#endif /* !... */
#ifdef __CRT_HAVE_localtime64
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime64,(__time64_t const *__timer),(__timer))
#elif defined(__CRT_HAVE_localtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime64,(__time64_t const *__timer),localtime,(__timer))
#elif defined(__CRT_HAVE__localtime64)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime64,(__time64_t const *__timer),_localtime64,(__timer))
#else /* ... */
#include <libc/local/time/localtime64.h>
/* Return the `struct tm' representation of *TIMER in the local timezone */
__NAMESPACE_LOCAL_USING_OR_IMPL(localtime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL localtime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime64))(__timer); })
#endif /* !... */
#endif /* __USE_TIME64 */



#undef __tzname
#undef __daylight
#undef __timezone
#if defined(__CRT_HAVE_tzname) && !defined(__NO_ASMNAME)
__LIBC char *(__tzname)[2] __ASMNAME("tzname");
#elif defined(__CRT_HAVE___tzname)
__LIBC char *(__tzname)[2];
#elif defined(__CRT_HAVE_tzname)
#define __tzname tzname
#ifndef __tzname_defined
#define __tzname_defined 1
#undef tzname
__LIBC char *(tzname)[2];
#endif /* !__tzname_defined */
#elif defined(__CRT_HAVE_DOS$__tzname)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_CONST,char **,__NOTHROW_NCX,__dos_tzname,(void),__tzname,())
#define __tzname  (__dos_tzname())
#endif

#if defined(__CRT_HAVE_daylight) && !defined(__NO_ASMNAME)
__LIBC int (__daylight) __ASMNAME("daylight");
#elif defined(__CRT_HAVE___daylight)
__LIBC int (__daylight);
#elif defined(__CRT_HAVE_daylight)
#define __daylight daylight
#ifndef __daylight_defined
#define __daylight_defined 1
#undef daylight
__LIBC int (daylight);
#endif /* !__daylight_defined */
#elif defined(__CRT_HAVE_DOS$__daylight)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_CONST,int *,__NOTHROW_NCX,__dos_daylight,(void),__daylight,())
#define __daylight (*__dos_daylight())
#endif

#if defined(__CRT_HAVE_timezone) && !defined(__NO_ASMNAME)
__LIBC __LONGPTR_TYPE__ (__timezone) __ASMNAME("timezone");
#elif defined(__CRT_HAVE___timezone)
__LIBC __LONGPTR_TYPE__ (__timezone);
#elif defined(__CRT_HAVE_timezone)
#define __timezone timezone
#ifndef __timezone_defined
#define __timezone_defined 1
#undef timezone
__LIBC __LONGPTR_TYPE__ (timezone);
#endif /* !__timezone_defined */
#elif defined(__CRT_HAVE_DOS$__timezone)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_CONST,long *,__NOTHROW_NCX,__dos_timezone,(void),__timezone,())
#define __timezone (*__dos_timezone())
#endif

#ifdef __USE_POSIX
#ifndef __tzname_defined
#define __tzname_defined 1
#undef tzname
#ifdef __CRT_HAVE_tzname
__LIBC char *(tzname)[2];
#elif defined(__CRT_HAVE___tzname) && !defined(__NO_ASMNAME)
__LIBC char *(tzname)[2] __ASMNAME("__tzname");
#elif defined(__CRT_HAVE___tzname)
#define tzname  __tzname
#elif defined(__CRT_HAVE_DOS$__tzname)
#define tzname  (__dos_tzname())
#else
#undef __tzname_defined
#endif
#endif /* !__tzname_defined */
/* Set time conversion information from the TZ environment variable.
 * If TZ is not defined, a locale-dependent default is used */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,tzset,(void),())
#endif /* __USE_POSIX */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef __daylight_defined
#define __daylight_defined 1
#undef daylight
#ifdef __CRT_HAVE_daylight
__LIBC int (daylight);
#elif defined(__CRT_HAVE___daylight) && !defined(__NO_ASMNAME)
__LIBC int (daylight) __ASMNAME("__daylight");
#elif defined(__CRT_HAVE___daylight)
#define daylight  __daylight
#elif defined(__CRT_HAVE_DOS$__daylight)
#define daylight  (*__dos_daylight())
#else
#undef __daylight_defined
#endif
#endif /* !__daylight_defined */

#ifndef __timezone_defined
#define __timezone_defined 1
#undef timezone
#ifdef __CRT_HAVE_timezone
__LIBC __LONGPTR_TYPE__ (timezone);
#elif defined(__CRT_HAVE___timezone) && !defined(__NO_ASMNAME)
__LIBC __LONGPTR_TYPE__ (timezone) __ASMNAME("__timezone");
#elif defined(__CRT_HAVE___timezone)
#define timezone  __timezone
#ifdef __struct_timezone_defined
#warning "Please #include <sys/time.h> after <time.h>, else `struct timezone' cannot be used"
#endif /* __struct_timezone_defined */
#elif defined(__CRT_HAVE_DOS$__timezone)
#define timezone  (*__dos_timezone())
#ifdef __struct_timezone_defined
#warning "With the linked libc, `struct timezone' from <sys/time.h> cannot be used after <time.h> was included"
#endif /* __struct_timezone_defined */
#else
#undef __timezone_defined
#endif
#endif /* !__timezone_defined */

#endif /* __USE_MISC || __USE_XOPEN */

#ifdef __USE_MISC
#ifndef __stime_defined
#define __stime_defined 1
#if defined(__CRT_HAVE_stime64) && defined(__USE_TIME_BITS64)
/* Set the system time to *WHEN. This call is restricted to the superuser */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,stime,(__TM_TYPE(time) const *__when),stime64,(__when))
#elif defined(__CRT_HAVE_stime) && !defined(__USE_TIME_BITS64)
/* Set the system time to *WHEN. This call is restricted to the superuser */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,stime,(__TM_TYPE(time) const *__when),(__when))
#elif defined(__CRT_HAVE_stime64) || defined(__CRT_HAVE_stime)
#include <libc/local/time/stime.h>
/* Set the system time to *WHEN. This call is restricted to the superuser */
__NAMESPACE_LOCAL_USING_OR_IMPL(stime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL stime)(__TM_TYPE(time) const *__when) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stime))(__when); })
#else /* ... */
#undef __stime_defined
#endif /* !... */
#endif /* !__stime_defined */
#if defined(__CRT_HAVE_timegm64) && defined(__USE_TIME_BITS64)
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timegm,(struct __NAMESPACE_STD_SYM tm *__tp),timegm64,(__tp))
#elif defined(__CRT_HAVE_timegm) && !defined(__USE_TIME_BITS64)
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timegm,(struct __NAMESPACE_STD_SYM tm *__tp),(__tp))
#else /* ... */
#include <libc/local/time/timegm.h>
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__NAMESPACE_LOCAL_USING_OR_IMPL(timegm, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __TM_TYPE(time) __NOTHROW_NCX(__LIBCCALL timegm)(struct __NAMESPACE_STD_SYM tm *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timegm))(__tp); })
#endif /* !... */
#if defined(__CRT_HAVE_mktime64) && defined(__USE_TIME_BITS64)
/* Another name for `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timelocal,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE__mktime64) && defined(__USE_TIME_BITS64)
/* Another name for `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timelocal,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64) && defined(__USE_TIME_BITS64)
/* Another name for `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timelocal,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),timelocal64,(__tp))
#elif defined(__CRT_HAVE_mktime) && !defined(__USE_TIME_BITS64)
/* Another name for `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timelocal,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE__mktime32) && !defined(__USE_TIME_BITS64)
/* Another name for `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timelocal,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),_mktime32,(__tp))
#elif defined(__CRT_HAVE_timelocal) && !defined(__USE_TIME_BITS64)
/* Another name for `mktime' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timelocal,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),(__tp))
#else /* ... */
#include <libc/local/time/mktime.h>
/* Another name for `mktime' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __TM_TYPE(time) __NOTHROW_NCX(__LIBCCALL timelocal)(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp) { return (__TM_TYPE(time))(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime))((struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *)__tp); }
#endif /* !... */
#ifdef __CRT_HAVE_dysize
/* Return the number of days in YEAR */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,dysize,(__STDC_INT_AS_UINT_T __year),(__year))
#else /* __CRT_HAVE_dysize */
#include <libc/local/time/dysize.h>
/* Return the number of days in YEAR */
__NAMESPACE_LOCAL_USING_OR_IMPL(dysize, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL dysize)(__STDC_INT_AS_UINT_T __year) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dysize))(__year); })
#endif /* !__CRT_HAVE_dysize */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_stime64
/* Set the system time to *WHEN. This call is restricted to the superuser */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,stime64,(__time64_t const *__when),(__when))
#elif defined(__CRT_HAVE_stime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Set the system time to *WHEN. This call is restricted to the superuser */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,stime64,(__time64_t const *__when),stime,(__when))
#elif defined(__CRT_HAVE_stime)
#include <libc/local/time/stime64.h>
/* Set the system time to *WHEN. This call is restricted to the superuser */
__NAMESPACE_LOCAL_USING_OR_IMPL(stime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL stime64)(__time64_t const *__when) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stime64))(__when); })
#endif /* ... */
#ifdef __CRT_HAVE_timegm64
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,timegm64,(struct __NAMESPACE_STD_SYM tm *__tp),(__tp))
#elif defined(__CRT_HAVE_timegm) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,timegm64,(struct __NAMESPACE_STD_SYM tm *__tp),timegm,(__tp))
#else /* ... */
#include <libc/local/time/timegm64.h>
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__NAMESPACE_LOCAL_USING_OR_IMPL(timegm64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __time64_t __NOTHROW_NCX(__LIBCCALL timegm64)(struct __NAMESPACE_STD_SYM tm *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timegm64))(__tp); })
#endif /* !... */
#ifdef __CRT_HAVE_mktime64
/* Another name for `mktime64' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,timelocal64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE_mktime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Another name for `mktime64' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,timelocal64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE__mktime64)
/* Another name for `mktime64' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,timelocal64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64)
/* Another name for `mktime64' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,timelocal64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),(__tp))
#else /* ... */
#include <libc/local/time/mktime64.h>
/* Another name for `mktime64' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __time64_t __NOTHROW_NCX(__LIBCCALL timelocal64)(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime64))(__tp); }
#endif /* !... */
#endif /* __USE_TIME64 */
#endif /* __USE_MISC */

#ifdef __USE_POSIX199309
#if defined(__CRT_HAVE_nanosleep64) && defined(__USE_TIME_BITS64)
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),nanosleep64,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep) && !defined(__USE_TIME_BITS64)
/* Pause execution for a number of nanoseconds */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),(__requested_time,__remaining))
#elif defined(__CRT_HAVE___nanosleep)
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),__nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep)
#include <libc/local/time/nanosleep.h>
/* Pause execution for a number of nanoseconds */
__NAMESPACE_LOCAL_USING_OR_IMPL(nanosleep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL nanosleep)(struct timespec const *__requested_time, struct timespec *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanosleep))(__requested_time, __remaining); })
#endif /* ... */
#if defined(__CRT_HAVE_clock_getres64) && defined(__USE_TIME_BITS64)
/* Get resolution of clock CLOCK_ID */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_getres,(clockid_t __clock_id, struct timespec *__res),clock_getres64,(__clock_id,__res))
#elif defined(__CRT_HAVE_clock_getres) && !defined(__USE_TIME_BITS64)
/* Get resolution of clock CLOCK_ID */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_getres,(clockid_t __clock_id, struct timespec *__res),(__clock_id,__res))
#elif defined(__CRT_HAVE___clock_getres) && !defined(__USE_TIME_BITS64)
/* Get resolution of clock CLOCK_ID */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_getres,(clockid_t __clock_id, struct timespec *__res),__clock_getres,(__clock_id,__res))
#elif defined(__CRT_HAVE_clock_getres64) || defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres)
#include <libc/local/time/clock_getres.h>
/* Get resolution of clock CLOCK_ID */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_getres, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL clock_getres)(clockid_t __clock_id, struct timespec *__res) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_getres))(__clock_id, __res); })
#endif /* ... */
#if defined(__CRT_HAVE_clock_gettime64) && defined(__USE_TIME_BITS64)
/* Get current value of clock CLOCK_ID and store it in TP */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_gettime,(clockid_t __clock_id, struct timespec *__tp),clock_gettime64,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime) && !defined(__USE_TIME_BITS64)
/* Get current value of clock CLOCK_ID and store it in TP */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_gettime,(clockid_t __clock_id, struct timespec *__tp),(__clock_id,__tp))
#elif defined(__CRT_HAVE___clock_gettime) && !defined(__USE_TIME_BITS64)
/* Get current value of clock CLOCK_ID and store it in TP */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_gettime,(clockid_t __clock_id, struct timespec *__tp),__clock_gettime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime)
#include <libc/local/time/clock_gettime.h>
/* Get current value of clock CLOCK_ID and store it in TP */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_gettime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL clock_gettime)(clockid_t __clock_id, struct timespec *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_gettime))(__clock_id, __tp); })
#endif /* ... */
#if defined(__CRT_HAVE_clock_settime64) && defined(__USE_TIME_BITS64)
/* Set clock CLOCK_ID to value TP */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_settime,(clockid_t __clock_id, struct timespec const *__tp),clock_settime64,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime) && !defined(__USE_TIME_BITS64)
/* Set clock CLOCK_ID to value TP */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_settime,(clockid_t __clock_id, struct timespec const *__tp),(__clock_id,__tp))
#elif defined(__CRT_HAVE___clock_settime) && !defined(__USE_TIME_BITS64)
/* Set clock CLOCK_ID to value TP */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_settime,(clockid_t __clock_id, struct timespec const *__tp),__clock_settime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime64) || defined(__CRT_HAVE_clock_settime) || defined(__CRT_HAVE___clock_settime)
#include <libc/local/time/clock_settime.h>
/* Set clock CLOCK_ID to value TP */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_settime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL clock_settime)(clockid_t __clock_id, struct timespec const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_settime))(__clock_id, __tp); })
#endif /* ... */
/* Create new per-process timer using CLOCK_ID */
__CDECLARE_OPT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timer_create,(clockid_t __clock_id, struct sigevent *__restrict __evp, timer_t *__restrict __timerid),(__clock_id,__evp,__timerid))
/* Delete timer TIMERID */
__CDECLARE_OPT(,int,__NOTHROW_NCX,timer_delete,(timer_t __timerid),(__timerid))
#if defined(__CRT_HAVE_timer_settime64) && defined(__USE_TIME_BITS64)
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timer_settime,(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__restrict __value, struct itimerspec *__restrict __ovalue),timer_settime64,(__timerid,__flags,__value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime) && !defined(__USE_TIME_BITS64)
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timer_settime,(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__restrict __value, struct itimerspec *__restrict __ovalue),(__timerid,__flags,__value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime64) || defined(__CRT_HAVE_timer_settime)
#include <libc/local/time/timer_settime.h>
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__NAMESPACE_LOCAL_USING_OR_IMPL(timer_settime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3)) int __NOTHROW_NCX(__LIBCCALL timer_settime)(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__restrict __value, struct itimerspec *__restrict __ovalue) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timer_settime))(__timerid, __flags, __value, __ovalue); })
#endif /* ... */
#if defined(__CRT_HAVE_timer_gettime64) && defined(__USE_TIME_BITS64)
/* Get current value of timer TIMERID and store it in VALUE */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,timer_gettime,(timer_t __timerid, struct itimerspec *__value),timer_gettime64,(__timerid,__value))
#elif defined(__CRT_HAVE_timer_gettime) && !defined(__USE_TIME_BITS64)
/* Get current value of timer TIMERID and store it in VALUE */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,timer_gettime,(timer_t __timerid, struct itimerspec *__value),(__timerid,__value))
#elif defined(__CRT_HAVE_timer_gettime64) || defined(__CRT_HAVE_timer_gettime)
#include <libc/local/time/timer_gettime.h>
/* Get current value of timer TIMERID and store it in VALUE */
__NAMESPACE_LOCAL_USING_OR_IMPL(timer_gettime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL timer_gettime)(timer_t __timerid, struct itimerspec *__value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timer_gettime))(__timerid, __value); })
#endif /* ... */
/* Get expiration overrun for timer TIMERID */
__CDECLARE_OPT(,int,__NOTHROW_NCX,timer_getoverrun,(timer_t __timerid),(__timerid))

#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_clock_nanosleep64) && defined(__USE_TIME_BITS64)
/* High-resolution sleep with the specified clock */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,clock_nanosleep,(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec const *__restrict __requested_time, struct timespec *__remaining),clock_nanosleep64,(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE_clock_nanosleep) && !defined(__USE_TIME_BITS64)
/* High-resolution sleep with the specified clock */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,clock_nanosleep,(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec const *__restrict __requested_time, struct timespec *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE___clock_nanosleep) && !defined(__USE_TIME_BITS64)
/* High-resolution sleep with the specified clock */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,clock_nanosleep,(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec const *__restrict __requested_time, struct timespec *__remaining),__clock_nanosleep,(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE_clock_nanosleep64) || defined(__CRT_HAVE_clock_nanosleep) || defined(__CRT_HAVE___clock_nanosleep)
#include <libc/local/time/clock_nanosleep.h>
/* High-resolution sleep with the specified clock */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_nanosleep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3)) int __NOTHROW_RPC(__LIBCCALL clock_nanosleep)(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec const *__restrict __requested_time, struct timespec *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_nanosleep))(__clock_id, __flags, __requested_time, __remaining); })
#endif /* ... */
#ifdef __CRT_HAVE_clock_getcpuclockid
/* Return clock ID for CPU-time clock */
__CDECLARE(,int,__NOTHROW_NCX,clock_getcpuclockid,(pid_t __pid, clockid_t *__clock_id),(__pid,__clock_id))
#elif defined(__CRT_HAVE___clock_getcpuclockid)
/* Return clock ID for CPU-time clock */
__CREDIRECT(,int,__NOTHROW_NCX,clock_getcpuclockid,(pid_t __pid, clockid_t *__clock_id),__clock_getcpuclockid,(__pid,__clock_id))
#endif /* ... */
#endif /* __USE_XOPEN2K */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_nanosleep64
/* Pause execution for a number of nanoseconds */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,nanosleep64,(struct timespec64 const *__restrict __requested_time, struct timespec64 *__remaining),(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,nanosleep64,(struct timespec64 const *__restrict __requested_time, struct timespec64 *__remaining),nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep)
#include <libc/local/time/nanosleep64.h>
/* Pause execution for a number of nanoseconds */
__NAMESPACE_LOCAL_USING_OR_IMPL(nanosleep64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL nanosleep64)(struct timespec64 const *__restrict __requested_time, struct timespec64 *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanosleep64))(__requested_time, __remaining); })
#endif /* ... */
#ifdef __CRT_HAVE_clock_getres64
/* Get resolution of clock CLOCK_ID */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_getres64,(clockid_t __clock_id, struct timespec64 *__res),(__clock_id,__res))
#elif defined(__CRT_HAVE_clock_getres) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Get resolution of clock CLOCK_ID */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_getres64,(clockid_t __clock_id, struct timespec64 *__res),clock_getres,(__clock_id,__res))
#elif defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres)
#include <libc/local/time/clock_getres64.h>
/* Get resolution of clock CLOCK_ID */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_getres64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL clock_getres64)(clockid_t __clock_id, struct timespec64 *__res) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_getres64))(__clock_id, __res); })
#endif /* ... */
#ifdef __CRT_HAVE_clock_gettime64
/* Get current value of clock CLOCK_ID and store it in TP */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_gettime64,(clockid_t __clock_id, struct timespec64 *__tp),(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Get current value of clock CLOCK_ID and store it in TP */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_gettime64,(clockid_t __clock_id, struct timespec64 *__tp),clock_gettime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime)
#include <libc/local/time/clock_gettime64.h>
/* Get current value of clock CLOCK_ID and store it in TP */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_gettime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL clock_gettime64)(clockid_t __clock_id, struct timespec64 *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_gettime64))(__clock_id, __tp); })
#endif /* ... */
#ifdef __CRT_HAVE_clock_settime64
/* Set clock CLOCK_ID to value TP */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_settime64,(clockid_t __clock_id, struct timespec64 const *__tp),(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Set clock CLOCK_ID to value TP */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_settime64,(clockid_t __clock_id, struct timespec64 const *__tp),clock_settime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime) || defined(__CRT_HAVE___clock_settime)
#include <libc/local/time/clock_settime64.h>
/* Set clock CLOCK_ID to value TP */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_settime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL clock_settime64)(clockid_t __clock_id, struct timespec64 const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_settime64))(__clock_id, __tp); })
#endif /* ... */
#ifdef __CRT_HAVE_timer_settime64
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timer_settime64,(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec64 const *__restrict __value, struct itimerspec64 *__restrict __ovalue),(__timerid,__flags,__value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timer_settime64,(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec64 const *__restrict __value, struct itimerspec64 *__restrict __ovalue),timer_settime,(__timerid,__flags,__value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime)
#include <libc/local/time/timer_settime64.h>
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__NAMESPACE_LOCAL_USING_OR_IMPL(timer_settime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3)) int __NOTHROW_NCX(__LIBCCALL timer_settime64)(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec64 const *__restrict __value, struct itimerspec64 *__restrict __ovalue) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timer_settime64))(__timerid, __flags, __value, __ovalue); })
#endif /* ... */
#ifdef __CRT_HAVE_timer_gettime64
/* Get current value of timer TIMERID and store it in VALUE */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,timer_gettime64,(timer_t __timerid, struct itimerspec64 *__value),(__timerid,__value))
#elif defined(__CRT_HAVE_timer_gettime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Get current value of timer TIMERID and store it in VALUE */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,timer_gettime64,(timer_t __timerid, struct itimerspec64 *__value),timer_gettime,(__timerid,__value))
#elif defined(__CRT_HAVE_timer_gettime)
#include <libc/local/time/timer_gettime64.h>
/* Get current value of timer TIMERID and store it in VALUE */
__NAMESPACE_LOCAL_USING_OR_IMPL(timer_gettime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL timer_gettime64)(timer_t __timerid, struct itimerspec64 *__value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timer_gettime64))(__timerid, __value); })
#endif /* ... */

#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_clock_nanosleep64
/* High-resolution sleep with the specified clock */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,clock_nanosleep64,(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec64 const *__requested_time, struct timespec64 *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE_clock_nanosleep) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* High-resolution sleep with the specified clock */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,clock_nanosleep64,(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec64 const *__requested_time, struct timespec64 *__remaining),clock_nanosleep,(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE_clock_nanosleep) || defined(__CRT_HAVE___clock_nanosleep)
#include <libc/local/time/clock_nanosleep64.h>
/* High-resolution sleep with the specified clock */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_nanosleep64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3)) int __NOTHROW_RPC(__LIBCCALL clock_nanosleep64)(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec64 const *__requested_time, struct timespec64 *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_nanosleep64))(__clock_id, __flags, __requested_time, __remaining); })
#endif /* ... */
#endif /* __USE_XOPEN2K */
#endif /* __USE_TIME64 */
#endif /* __USE_POSIX199309 */

#ifdef __USE_ISOCXX17
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__timespec_get_defined) && defined(__std_timespec_get_defined)
#define __timespec_get_defined 1
__NAMESPACE_STD_USING(timespec_get)
#endif /* !__timespec_get_defined && __std_timespec_get_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOCXX17 */

/* timespec_get() is defined by both c11 and c++17 */
#ifdef __USE_ISOC11
#ifndef __timespec_get_defined
#define __timespec_get_defined 1
#ifdef __std_timespec_get_defined
/* Set TS to calendar time based in time base BASE */
__NAMESPACE_STD_USING(timespec_get)
#elif defined(__CRT_HAVE_timespec_get)
/* Set TS to calendar time based in time base BASE */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,timespec_get,(struct timespec *__ts, __STDC_INT_AS_UINT_T __base),(__ts,__base))
#else /* ... */
#undef __timespec_get_defined
#endif /* !... */
#endif /* !__timespec_get_defined */
#endif /* __USE_ISOC11 */

#ifdef __USE_XOPEN_EXTENDED
/* Set to one of the following values to indicate an error.
     1  the DATEMSK environment variable is null or undefined,
     2  the template file cannot be opened for reading,
     3  failed to get file status information,
     4  the template file is not a regular file,
     5  an error is encountered while reading the template file,
     6  memory allication failed (not enough memory available),
     7  there is no line in the template that matches the input,
     8  invalid input specification Example: February 31 or a time is
        specified that can not be represented in a time_t (representing
        the time in seconds since 00:00:00 UTC, January 1, 1970) */
#ifdef __CRT_HAVE_getdate_err
__LIBC int getdate_err;
#endif /* __CRT_HAVE_getdate_err */

/* Parse the given string as a date specification and return a value
 * representing the value.  The templates from the file identified by
 * the environment variable DATEMSK are used.  In case of an error
 * `getdate_err' is set */
__CDECLARE_OPT(__ATTR_NONNULL((1)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,getdate,(const char *__string),(__string))
#endif /* __USE_XOPEN_EXTENDED */

#ifdef __USE_GNU
#ifndef __getdate_r_defined
#define __getdate_r_defined 1
#ifdef __CRT_HAVE_getdate_r
/* Since `getdate' is not reentrant because of the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The functionality is the same.  The result is returned in
 * the buffer pointed to by RESBUFP and in case of an error the return
 * value is != 0 with the same values as given above for `getdate_err'. */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,getdate_r,(char const *__restrict __string, struct __NAMESPACE_STD_SYM tm *__restrict __resbufp),(__string,__resbufp))
#else /* __CRT_HAVE_getdate_r */
#include <libc/local/time/getdate_r.h>
/* Since `getdate' is not reentrant because of the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The functionality is the same.  The result is returned in
 * the buffer pointed to by RESBUFP and in case of an error the return
 * value is != 0 with the same values as given above for `getdate_err'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(getdate_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL getdate_r)(char const *__restrict __string, struct __NAMESPACE_STD_SYM tm *__restrict __resbufp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdate_r))(__string, __resbufp); })
#endif /* !__CRT_HAVE_getdate_r */
#endif /* !__getdate_r_defined */
#endif /* __USE_GNU */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_strftime_l
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
__CDECLARE(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),(__buf,__bufsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE__strftime_l)
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),_strftime_l,(__buf,__bufsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE___strftime_l)
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),__strftime_l,(__buf,__bufsize,__format,__tp,__locale))
#else /* ... */
#include <libc/local/time/strftime_l.h>
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
__NAMESPACE_LOCAL_USING_OR_IMPL(strftime_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strftime_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strftime_l))(__buf, __bufsize, __format, __tp, __locale); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_XOPEN
#ifdef __CRT_HAVE_strptime
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),char *,__NOTHROW_NCX,strptime,(char const *__restrict __s, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm *__restrict __tp),(__s,__format,__tp))
#else /* __CRT_HAVE_strptime */
#include <libc/local/time/strptime.h>
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
__NAMESPACE_LOCAL_USING_OR_IMPL(strptime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) char *__NOTHROW_NCX(__LIBCCALL strptime)(char const *__restrict __s, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strptime))(__s, __format, __tp); })
#endif /* !__CRT_HAVE_strptime */
#endif /* __USE_XOPEN */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_strptime_l
/* Similar to `strptime' but take the information from
 * the provided locale and not the global locale */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),char *,__NOTHROW_NCX,strptime_l,(char const *__restrict __s, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm *__restrict __tp, __locale_t __locale),(__s,__format,__tp,__locale))
#else /* __CRT_HAVE_strptime_l */
#include <libc/local/time/strptime_l.h>
/* Similar to `strptime' but take the information from
 * the provided locale and not the global locale */
__NAMESPACE_LOCAL_USING_OR_IMPL(strptime_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) char *__NOTHROW_NCX(__LIBCCALL strptime_l)(char const *__restrict __s, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strptime_l))(__s, __format, __tp, __locale); })
#endif /* !__CRT_HAVE_strptime_l */
#ifndef __getdate_r_defined
#define __getdate_r_defined 1
#ifdef __CRT_HAVE_getdate_r
/* Since `getdate' is not reentrant because of the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The functionality is the same.  The result is returned in
 * the buffer pointed to by RESBUFP and in case of an error the return
 * value is != 0 with the same values as given above for `getdate_err'. */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,getdate_r,(char const *__restrict __string, struct __NAMESPACE_STD_SYM tm *__restrict __resbufp),(__string,__resbufp))
#else /* __CRT_HAVE_getdate_r */
#include <libc/local/time/getdate_r.h>
/* Since `getdate' is not reentrant because of the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The functionality is the same.  The result is returned in
 * the buffer pointed to by RESBUFP and in case of an error the return
 * value is != 0 with the same values as given above for `getdate_err'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(getdate_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL getdate_r)(char const *__restrict __string, struct __NAMESPACE_STD_SYM tm *__restrict __resbufp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdate_r))(__string, __resbufp); })
#endif /* !__CRT_HAVE_getdate_r */
#endif /* !__getdate_r_defined */
#ifndef __clock_adjtime_defined
#define __clock_adjtime_defined 1
#if defined(__CRT_HAVE_clock_adjtime64) && defined(__USE_TIME_BITS64)
__CREDIRECT(,int,__NOTHROW_NCX,clock_adjtime,(__clockid_t __clock_id, struct timex *__utx),clock_adjtime64,(__clock_id,__utx))
#elif defined(__CRT_HAVE_clock_adjtime) && !defined(__USE_TIME_BITS64)
__CDECLARE(,int,__NOTHROW_NCX,clock_adjtime,(__clockid_t __clock_id, struct timex *__utx),(__clock_id,__utx))
#else /* ... */
#undef __clock_adjtime_defined
#endif /* !... */
#endif /* !__clock_adjtime_defined */

#ifdef __USE_TIME64
#ifndef __clock_adjtime64_defined
#define __clock_adjtime64_defined 1
#ifdef __CRT_HAVE_clock_adjtime64
__CDECLARE(,int,__NOTHROW_NCX,clock_adjtime64,(__clockid_t __clock_id, struct timex64 *__utx),(__clock_id,__utx))
#elif defined(__CRT_HAVE_clock_adjtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(,int,__NOTHROW_NCX,clock_adjtime64,(__clockid_t __clock_id, struct timex64 *__utx),clock_adjtime,(__clock_id,__utx))
#else /* ... */
#undef __clock_adjtime64_defined
#endif /* !... */
#endif /* !__clock_adjtime64_defined */
#endif /* __USE_TIME64 */
#endif /* __USE_GNU */

#ifdef __USE_POSIX
#ifdef __CRT_HAVE_gmtime_r
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CDECLARE(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime_r,(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),(__timer,__tp))
#elif defined(__CRT_HAVE___gmtime_r)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime_r,(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),__gmtime_r,(__timer,__tp))
#else /* ... */
#include <libc/local/time/gmtime_r.h>
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(gmtime_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL gmtime_r)(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime_r))(__timer, __tp); })
#endif /* !... */
#ifdef __CRT_HAVE_localtime_r
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CDECLARE(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime_r,(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),(__timer,__tp))
#else /* __CRT_HAVE_localtime_r */
#include <libc/local/time/localtime_r.h>
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(localtime_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL localtime_r)(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime_r))(__timer, __tp); })
#endif /* !__CRT_HAVE_localtime_r */
#ifdef __CRT_HAVE_ctime_r
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__CDECLARE(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,ctime_r,(__TM_TYPE(time) const *__restrict __timer, char __buf[26]),(__timer,__buf))
#else /* __CRT_HAVE_ctime_r */
#include <libc/local/time/ctime_r.h>
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctime_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL ctime_r)(__TM_TYPE(time) const *__restrict __timer, char __buf[26]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime_r))(__timer, __buf); })
#endif /* !__CRT_HAVE_ctime_r */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_gmtime64_r
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CDECLARE(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),(__timer,__tp))
#elif defined(__CRT_HAVE_gmtime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime_r,(__timer,__tp))
#else /* ... */
#include <libc/local/time/gmtime64_r.h>
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(gmtime64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL gmtime64_r)(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime64_r))(__timer, __tp); })
#endif /* !... */
#ifdef __CRT_HAVE_localtime64_r
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CDECLARE(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),(__timer,__tp))
#elif defined(__CRT_HAVE_localtime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime_r,(__timer,__tp))
#else /* ... */
#include <libc/local/time/localtime64_r.h>
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(localtime64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL localtime64_r)(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime64_r))(__timer, __tp); })
#endif /* !... */
#ifdef __CRT_HAVE_ctime64_r
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__CDECLARE(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,ctime64_r,(__time64_t const *__restrict __timer, char __buf[26]),(__timer,__buf))
#elif defined(__CRT_HAVE_ctime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,ctime64_r,(__time64_t const *__restrict __timer, char __buf[26]),ctime_r,(__timer,__buf))
#else /* ... */
#include <libc/local/time/ctime64_r.h>
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctime64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL ctime64_r)(__time64_t const *__restrict __timer, char __buf[26]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime64_r))(__timer, __buf); })
#endif /* !... */
#endif /* __USE_TIME64 */
#ifdef __CRT_HAVE_asctime_r
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
__CDECLARE(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,asctime_r,(struct __NAMESPACE_STD_SYM tm const *__restrict __tp, char __buf[26]),(__tp,__buf))
#else /* __CRT_HAVE_asctime_r */
#include <libc/local/time/asctime_r.h>
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
__NAMESPACE_LOCAL_USING_OR_IMPL(asctime_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL asctime_r)(struct __NAMESPACE_STD_SYM tm const *__restrict __tp, char __buf[26]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asctime_r))(__tp, __buf); })
#endif /* !__CRT_HAVE_asctime_r */
#endif /* __USE_POSIX */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_TIME_H)
#include <parts/uchar/time.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_TIME_H */
#endif /* __USE_UTF */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CTIME 1
#undef _TIME_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CTIME */
#endif /* !_TIME_H */
