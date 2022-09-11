/* HASH CRC-32:0x17484ca4 */
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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/time.h) */
/* (#) Portability: DJGPP         (/include/time.h) */
/* (#) Portability: DragonFly BSD (/include/time.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/time.h) */
/* (#) Portability: FreeBSD       (/include/time.h) */
/* (#) Portability: GNU C Library (/time/time.h) */
/* (#) Portability: MSVC          (/include/time.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/time.h) */
/* (#) Portability: NetBSD        (/include/time.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/time.h) */
/* (#) Portability: OpenBSD       (/include/time.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/time.h) */
/* (#) Portability: PDCLib        (/include/time.h) */
/* (#) Portability: Windows Kits  (/ucrt/time.h) */
/* (#) Portability: avr-libc      (/include/time.h) */
/* (#) Portability: diet libc     (/include/time.h) */
/* (#) Portability: libc4/5       (/include/time.h) */
/* (#) Portability: libc6         (/include/time.h) */
/* (#) Portability: libcmini      (/include/time.h) */
/* (#) Portability: mintlib       (/include/time.h) */
/* (#) Portability: musl libc     (/include/time.h) */
/* (#) Portability: uClibc        (/include/time.h) */
#ifndef _TIME_H
#define _TIME_H 1

#ifdef _CXX_STDONLY_CTIME
#ifdef __CXX_SYSTEM_HEADER
#undef _TIME_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "time.h" after "ctime" */
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __clock_t_defined
#define __clock_t_defined
__NAMESPACE_STD_USING(clock_t)
#endif /* !__clock_t_defined */
#ifndef __time_t_defined
#define __time_t_defined
__NAMESPACE_STD_USING(time_t)
#endif /* !__time_t_defined */
#ifndef __tm_defined
#define __tm_defined
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
#include <asm/os/clock.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_clock) || (defined(__CLOCK_PROCESS_CPUTIME_ID) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime))) || defined(__CRT_HAVE_times) || defined(__CRT_HAVE___times) || defined(__CRT_HAVE___libc_times)
__NAMESPACE_STD_USING(clock)
#endif /* __CRT_HAVE_clock || (__CLOCK_PROCESS_CPUTIME_ID && (__CRT_HAVE_clock_gettime64 || __CRT_HAVE_clock_gettime || __CRT_HAVE___clock_gettime)) || __CRT_HAVE_times || __CRT_HAVE___times || __CRT_HAVE___libc_times */
#include <features.h>
#if defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_STD_USING(time)
#endif /* __CRT_HAVE_time64 || __CRT_HAVE__time64 || __CRT_HAVE_time || __CRT_HAVE___time || __CRT_HAVE___libc_time || __CRT_HAVE__time32 */
#if !defined(__difftime_defined) && defined(__std_difftime_defined)
#define __difftime_defined
__NAMESPACE_STD_USING(difftime)
#endif /* !__difftime_defined && __std_difftime_defined */
__NAMESPACE_STD_USING(mktime)
__NAMESPACE_STD_USING(ctime)
__NAMESPACE_STD_USING(gmtime)
__NAMESPACE_STD_USING(localtime)
__NAMESPACE_STD_USING(strftime)
__NAMESPACE_STD_USING(asctime)
#if !defined(__asctime_s_defined) && defined(__std_asctime_s_defined)
#define __asctime_s_defined
__NAMESPACE_STD_USING(asctime_s)
#endif /* !__asctime_s_defined && __std_asctime_s_defined */
#include <asm/crt/time.h>
#if (defined(__CRT_HAVE_timespec_get) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE__timespec32_get) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_timespec_get64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE__timespec64_get) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime)))
__NAMESPACE_STD_USING(timespec_get)
#endif /* (__CRT_HAVE_timespec_get && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE__timespec32_get && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE_timespec_get64 && (__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE__timespec64_get && (__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CLOCK_REALTIME && __TIME_UTC && (__CRT_HAVE_clock_gettime64 || __CRT_HAVE_clock_gettime || __CRT_HAVE___clock_gettime)) */
#if (defined(__CRT_HAVE_timespec_getres) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE__timespec32_get) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_timespec_getres64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE__timespec64_get) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && (defined(__CRT_HAVE_clock_getres64) || defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres)))
__NAMESPACE_STD_USING(timespec_getres)
#endif /* (__CRT_HAVE_timespec_getres && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE__timespec32_get && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE_timespec_getres64 && (__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE__timespec64_get && (__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CLOCK_REALTIME && __TIME_UTC && (__CRT_HAVE_clock_getres64 || __CRT_HAVE_clock_getres || __CRT_HAVE___clock_getres)) */
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
#include <asm/crt/time.h>
#include <asm/os/clock.h>
#include <bits/types.h>
#include <hybrid/typecore.h>

#ifdef __USE_POSIX199309
#include <bits/os/timespec.h>
#include <bits/os/itimerspec.h>
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


#ifdef __USE_KOS
#define MSEC_PER_SEC  __UINT16_C(1000)
#define USEC_PER_MSEC __UINT16_C(1000)
#define NSEC_PER_USEC __UINT16_C(1000)
#define NSEC_PER_MSEC __UINT32_C(1000000)
#define USEC_PER_SEC  __UINT32_C(1000000)
#define NSEC_PER_SEC  __UINT32_C(1000000000)
#define FSEC_PER_SEC  __UINT64_C(1000000000000000)
#endif /* __USE_KOS */

/* Values for `timespec_get(3)::base' */
#ifdef __USE_ISOC11
#if !defined(TIME_UTC) && defined(__TIME_UTC)
#define TIME_UTC __TIME_UTC /* s.a. `CLOCK_REALTIME' */
#endif /* !TIME_UTC && __TIME_UTC */
#endif /* __USE_ISOC11 */

#ifndef __isleap
#define __isleap(year) ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
#endif /* !__isleap */

#ifndef __daystoyears
#define __daystoyears(n_days) ((400 * ((n_days) + 1)) / 146097)
#endif /* !__daystoyears */

#ifndef __yearstodays
#define __yearstodays(n_years) (((146097 * (n_years)) / 400) /*-1*/) /* rounding error? */
#endif /* !__yearstodays */

#ifndef NULL
#define NULL __NULLPTR
#endif /* NULL */

#if !defined(CLOCKS_PER_SEC) && defined(__CLOCKS_PER_SEC)
#define CLOCKS_PER_SEC  (__CCAST(clock_t)__CLOCKS_PER_SEC)
#endif /* !CLOCKS_PER_SEC && __CLOCKS_PER_SEC */

#if ((!defined(__STRICT_ANSI__) || defined(__USE_POSIX)) && \
     !defined(__USE_XOPEN2K) && defined(__CC__) && !defined(__USE_ISOC_PURE))
__SYSDECL_END
#include <asm/crt/confname.h>
__SYSDECL_BEGIN
#ifdef _SC_CLK_TCK
#ifndef ____os_sysconf_defined
#define ____os_sysconf_defined
#ifdef __CRT_HAVE_sysconf
/* >> sysconf(2)
 * @param: name: One of `_SC_*' from <asm/crt/confname.h>
 * Return   a   system    configuration   value    `name'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] `name'  refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,__os_sysconf,(__STDC_INT_AS_UINT_T __name),sysconf,(__name))
#elif defined(__CRT_HAVE___sysconf)
/* >> sysconf(2)
 * @param: name: One of `_SC_*' from <asm/crt/confname.h>
 * Return   a   system    configuration   value    `name'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] `name'  refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
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
/* Possible values for `clockid_t' arguments, as taken by:
 * - clock_getres(2), clock_getres64(2)
 * - clock_gettime(2), clock_gettime64(2)
 * - clock_settime(2), clock_settime64(2)
 * - clock_nanosleep(2), clock_nanosleep64(2)
 * - timer_create(2) */
#if !defined(CLOCK_REALTIME) && defined(__CLOCK_REALTIME)
#define CLOCK_REALTIME           __CLOCK_REALTIME           /* [rw] Realtime (wall) clock, in UTC (also used by `time(2)' and `gettimeofday(2)') */
#endif /* !CLOCK_REALTIME && __CLOCK_REALTIME */
#if !defined(CLOCK_MONOTONIC) && defined(__CLOCK_MONOTONIC)
#define CLOCK_MONOTONIC          __CLOCK_MONOTONIC          /* [ro] Time since system was booted (unaffected by system
                                                             * time  changes)  Paused while  the system  is suspended. */
#endif /* !CLOCK_MONOTONIC && __CLOCK_MONOTONIC */
#if !defined(CLOCK_PROCESS_CPUTIME_ID) && defined(__CLOCK_PROCESS_CPUTIME_ID)
#define CLOCK_PROCESS_CPUTIME_ID __CLOCK_PROCESS_CPUTIME_ID /* [ro] Sum of CPU time consumed by all threads in calling process */
#endif /* !CLOCK_PROCESS_CPUTIME_ID && __CLOCK_PROCESS_CPUTIME_ID */
#if !defined(CLOCK_THREAD_CPUTIME_ID) && defined(__CLOCK_THREAD_CPUTIME_ID)
#define CLOCK_THREAD_CPUTIME_ID  __CLOCK_THREAD_CPUTIME_ID  /* [ro] Sum of CPU time consumed by calling thread */
#endif /* !CLOCK_THREAD_CPUTIME_ID && __CLOCK_THREAD_CPUTIME_ID */
#if !defined(CLOCK_MONOTONIC_RAW) && defined(__CLOCK_MONOTONIC_RAW)
#define CLOCK_MONOTONIC_RAW      __CLOCK_MONOTONIC_RAW      /* [ro] Raw,  hardware time since  system was started (stopped
                                                             * while system is suspended), and unaffected by anything done
                                                             * by `adjtime(3)' */
#endif /* !CLOCK_MONOTONIC_RAW && __CLOCK_MONOTONIC_RAW */
#if !defined(CLOCK_REALTIME_COARSE) && defined(__CLOCK_REALTIME_COARSE)
#define CLOCK_REALTIME_COARSE    __CLOCK_REALTIME_COARSE    /* [ro] Same as `CLOCK_REALTIME', but may be less precise, yet faster to query. */
#endif /* !CLOCK_REALTIME_COARSE && __CLOCK_REALTIME_COARSE */
#if !defined(CLOCK_MONOTONIC_COARSE) && defined(__CLOCK_MONOTONIC_COARSE)
#define CLOCK_MONOTONIC_COARSE   __CLOCK_MONOTONIC_COARSE   /* [ro] Same as `CLOCK_MONOTONIC', but may be less precise, yet faster to query. */
#endif /* !CLOCK_MONOTONIC_COARSE && __CLOCK_MONOTONIC_COARSE */
#if !defined(CLOCK_BOOTTIME) && defined(__CLOCK_BOOTTIME)
#define CLOCK_BOOTTIME           __CLOCK_BOOTTIME           /* [ro] Same as `CLOCK_MONOTONIC', but includes time the system was suspended. */
#endif /* !CLOCK_BOOTTIME && __CLOCK_BOOTTIME */
#if !defined(CLOCK_REALTIME_ALARM) && defined(__CLOCK_REALTIME_ALARM)
#define CLOCK_REALTIME_ALARM     __CLOCK_REALTIME_ALARM     /* [ro] Like `CLOCK_REALTIME'. If used with `timer_create()', system will leave suspension when timer is triggered */
#endif /* !CLOCK_REALTIME_ALARM && __CLOCK_REALTIME_ALARM */
#if !defined(CLOCK_BOOTTIME_ALARM) && defined(__CLOCK_BOOTTIME_ALARM)
#define CLOCK_BOOTTIME_ALARM     __CLOCK_BOOTTIME_ALARM     /* [ro] Like `CLOCK_BOOTTIME'. If used with `timer_create()', system will leave suspension when timer is triggered */
#endif /* !CLOCK_BOOTTIME_ALARM && __CLOCK_BOOTTIME_ALARM */
#if !defined(CLOCK_TAI) && defined(__CLOCK_TAI)
#define CLOCK_TAI                __CLOCK_TAI                /* [ro] Time.Atomic.International -- Like `CLOCK_REALTIME', but isn't affected by leap seconds. */
#endif /* !CLOCK_TAI && __CLOCK_TAI */

/* Flag for `timer_settime(2)' */
#if !defined(TIMER_ABSTIME) && defined(__TIMER_ABSTIME)
#define TIMER_ABSTIME __TIMER_ABSTIME /* TODO: Doc */
#endif /* !TIMER_ABSTIME && __TIMER_ABSTIME */
#endif /* __USE_POSIX199309 */


#if (!defined(CLK_TCK) &&                                 \
     (defined(__USE_DOS) || (!defined(__USE_XOPEN2K) &&   \
                             !defined(__STRICT_ANSI__) && \
                             !defined(__USE_ISOC_PURE))))
#define CLK_TCK CLOCKS_PER_SEC
#endif /* !CLK_TCK && (__USE_DOS || (!__USE_XOPEN2K && !__STRICT_ANSI__ && !__USE_ISOC_PURE)) */


#ifdef __CC__
__SYSDECL_BEGIN

__NAMESPACE_STD_BEGIN
#ifndef __std_size_t_defined
#define __std_size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__std_size_t_defined */
#ifndef __std_clock_t_defined
#define __std_clock_t_defined
typedef __clock_t clock_t;
#endif /* !__std_clock_t_defined */
#ifndef __std_time_t_defined
#define __std_time_t_defined
typedef __time_t time_t;
#endif /* !__std_time_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __clock_t_defined
#define __clock_t_defined
__NAMESPACE_STD_USING(clock_t)
#endif /* !__clock_t_defined */
#ifndef __time_t_defined
#define __time_t_defined
__NAMESPACE_STD_USING(time_t)
#endif /* !__time_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_XOPEN2K
#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#endif /* __USE_XOPEN2K */

#ifdef __USE_TIME64
#ifndef __time64_t_defined
#define __time64_t_defined
typedef __time64_t time64_t;
#endif /* !__time64_t_defined */
#endif /* __USE_TIME64 */

#ifdef __USE_POSIX199309
#ifndef __clockid_t_defined
#define __clockid_t_defined
typedef __clockid_t clockid_t;
#endif /* !__clockid_t_defined */
#ifndef __timer_t_defined
#define __timer_t_defined
typedef __timer_t timer_t;
#endif /* !__timer_t_defined */
#endif /* __USE_POSIX199309 */


#ifndef __CXX_SYSTEM_HEADER
#ifndef __tm_defined
#define __tm_defined
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
#endif /* !__CXX_SYSTEM_HEADER */



#ifdef __USE_POSIX199309
struct sigevent;
#endif /* __USE_POSIX199309 */

__NAMESPACE_STD_BEGIN
#ifdef __CRT_HAVE_clock
/* >> clock(3)
 * Time used by the program so  far (user time + system  time)
 * The `result / CLOCKS_PER_SECOND' is program time in seconds */
__CDECLARE(__ATTR_WUNUSED,clock_t,__NOTHROW_NCX,clock,(void),())
#elif (defined(__CLOCK_PROCESS_CPUTIME_ID) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime))) || defined(__CRT_HAVE_times) || defined(__CRT_HAVE___times) || defined(__CRT_HAVE___libc_times)
__NAMESPACE_STD_END
#include <libc/local/time/clock.h>
__NAMESPACE_STD_BEGIN
/* >> clock(3)
 * Time used by the program so  far (user time + system  time)
 * The `result / CLOCKS_PER_SECOND' is program time in seconds */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED clock_t __NOTHROW_NCX(__LIBCCALL clock)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock))(); })
#endif /* ... */
#if defined(__CRT_HAVE_time) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CDECLARE(__ATTR_OUT_OPT(1),time_t,__NOTHROW_NCX,time,(time_t *__timer),(__timer))
#elif defined(__CRT_HAVE___time) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(__ATTR_OUT_OPT(1),time_t,__NOTHROW_NCX,time,(time_t *__timer),__time,(__timer))
#elif defined(__CRT_HAVE___libc_time) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(__ATTR_OUT_OPT(1),time_t,__NOTHROW_NCX,time,(time_t *__timer),__libc_time,(__timer))
#elif defined(__CRT_HAVE__time32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(__ATTR_OUT_OPT(1),time_t,__NOTHROW_NCX,time,(time_t *__timer),_time32,(__timer))
#elif defined(__CRT_HAVE_time64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(__ATTR_OUT_OPT(1),time_t,__NOTHROW_NCX,time,(time_t *__timer),time64,(__timer))
#elif defined(__CRT_HAVE__time64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(__ATTR_OUT_OPT(1),time_t,__NOTHROW_NCX,time,(time_t *__timer),_time64,(__timer))
#elif defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_STD_END
#include <libc/local/time/time.h>
__NAMESPACE_STD_BEGIN
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(time, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(1) time_t __NOTHROW_NCX(__LIBCCALL time)(time_t *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(time))(__timer); })
#endif /* ... */
#ifndef __NO_FPU
#ifndef __std_difftime_defined
#define __std_difftime_defined
#ifdef __difftime_defined
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__NAMESPACE_GLB_USING_OR_IMPL(difftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW_NCX(__LIBCCALL difftime)(time_t __time1, time_t __time0) { return :: difftime(__time1, __time0); })
#elif defined(__CRT_HAVE_difftime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime,(time_t __time1, time_t __time0),(__time1,__time0))
#elif defined(__CRT_HAVE__difftime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime,(time_t __time1, time_t __time0),_difftime32,(__time1,__time0))
#elif defined(__CRT_HAVE_difftime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime,(time_t __time1, time_t __time0),difftime64,(__time1,__time0))
#elif defined(__CRT_HAVE__difftime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime,(time_t __time1, time_t __time0),_difftime64,(__time1,__time0))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/difftime.h>
__NAMESPACE_STD_BEGIN
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__NAMESPACE_LOCAL_USING_OR_IMPL(difftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW_NCX(__LIBCCALL difftime)(time_t __time1, time_t __time0) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(difftime))(__time1, __time0); })
#endif /* !... */
#endif /* !__std_difftime_defined */
#endif /* !__NO_FPU */
#if defined(__CRT_HAVE_mktime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),time_t,__NOTHROW_NCX,mktime,(struct __NAMESPACE_STD_SYM tm *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE__mktime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),time_t,__NOTHROW_NCX,mktime,(struct __NAMESPACE_STD_SYM tm *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),time_t,__NOTHROW_NCX,mktime,(struct __NAMESPACE_STD_SYM tm *__tp),timelocal64,(__tp))
#elif defined(__CRT_HAVE_mktime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),time_t,__NOTHROW_NCX,mktime,(struct __NAMESPACE_STD_SYM tm *__tp),(__tp))
#elif defined(__CRT_HAVE__mktime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),time_t,__NOTHROW_NCX,mktime,(struct __NAMESPACE_STD_SYM tm *__tp),_mktime32,(__tp))
#elif defined(__CRT_HAVE_timelocal) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),time_t,__NOTHROW_NCX,mktime,(struct __NAMESPACE_STD_SYM tm *__tp),timelocal,(__tp))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/mktime.h>
__NAMESPACE_STD_BEGIN
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mktime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1) time_t __NOTHROW_NCX(__LIBCCALL mktime)(struct __NAMESPACE_STD_SYM tm *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime))(__tp); })
#endif /* !... */
#if defined(__CRT_HAVE_ctime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,ctime,(time_t const *__timer),(__timer))
#elif defined(__CRT_HAVE__ctime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,ctime,(time_t const *__timer),_ctime32,(__timer))
#elif defined(__CRT_HAVE_ctime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,ctime,(time_t const *__timer),ctime64,(__timer))
#elif defined(__CRT_HAVE__ctime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,ctime,(time_t const *__timer),_ctime64,(__timer))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/ctime.h>
__NAMESPACE_STD_BEGIN
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL ctime)(time_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime))(__timer); })
#endif /* !... */
#if defined(__CRT_HAVE_gmtime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime,(time_t const *__timer),(__timer))
#elif defined(__CRT_HAVE__gmtime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime,(time_t const *__timer),_gmtime32,(__timer))
#elif defined(__CRT_HAVE_gmtime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime,(time_t const *__timer),gmtime64,(__timer))
#elif defined(__CRT_HAVE__gmtime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime,(time_t const *__timer),_gmtime64,(__timer))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/gmtime.h>
__NAMESPACE_STD_BEGIN
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__NAMESPACE_LOCAL_USING_OR_IMPL(gmtime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL gmtime)(time_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime))(__timer); })
#endif /* !... */
#if defined(__CRT_HAVE_localtime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime,(time_t const *__timer),(__timer))
#elif defined(__CRT_HAVE__localtime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime,(time_t const *__timer),_localtime32,(__timer))
#elif defined(__CRT_HAVE_localtime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime,(time_t const *__timer),localtime64,(__timer))
#elif defined(__CRT_HAVE__localtime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime,(time_t const *__timer),_localtime64,(__timer))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/localtime.h>
__NAMESPACE_STD_BEGIN
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__NAMESPACE_LOCAL_USING_OR_IMPL(localtime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL localtime)(time_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime))(__timer); })
#endif /* !... */
#if __has_builtin(__builtin_strftime) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strftime)
/* >> strftime(3)
 * Format `tp' into `s' according to `format'.
 * Write no more than `maxsize' characters and return the number
 * of characters  written, or  0 if  it would  exceed  `maxsize' */
__CEIDECLARE_GCCNCX(__ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_STRFTIME(3, 0) __ATTR_OUTS(1, 2),size_t,__NOTHROW_NCX,strftime,(char *__restrict __buf, size_t __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp),{ return __builtin_strftime(__buf, __bufsize, __format, __tp); })
#elif defined(__CRT_HAVE_strftime)
/* >> strftime(3)
 * Format `tp' into `s' according to `format'.
 * Write no more than `maxsize' characters and return the number
 * of characters  written, or  0 if  it would  exceed  `maxsize' */
__CDECLARE_GCCNCX(__ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_STRFTIME(3, 0) __ATTR_OUTS(1, 2),size_t,__NOTHROW_NCX,strftime,(char *__restrict __buf, size_t __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp),(__buf,__bufsize,__format,__tp))
#elif defined(__CRT_HAVE__Strftime)
/* >> strftime(3)
 * Format `tp' into `s' according to `format'.
 * Write no more than `maxsize' characters and return the number
 * of characters  written, or  0 if  it would  exceed  `maxsize' */
__CREDIRECT_GCCNCX(__ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_STRFTIME(3, 0) __ATTR_OUTS(1, 2),size_t,__NOTHROW_NCX,strftime,(char *__restrict __buf, size_t __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp),_Strftime,(__buf,__bufsize,__format,__tp))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/strftime.h>
__NAMESPACE_STD_BEGIN
/* >> strftime(3)
 * Format `tp' into `s' according to `format'.
 * Write no more than `maxsize' characters and return the number
 * of characters  written, or  0 if  it would  exceed  `maxsize' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_STRFTIME(3, 0) __ATTR_OUTS(1, 2) size_t __NOTHROW_NCX(__LIBCCALL strftime)(char *__restrict __buf, size_t __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strftime))(__buf, __bufsize, __format, __tp); })
#endif /* !... */
#ifdef __CRT_HAVE_asctime
/* >> asctime(3)
 * Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is  the  representation  of  `tp'  in  this  format */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,asctime,(struct __NAMESPACE_STD_SYM tm const *__tp),(__tp))
#else /* __CRT_HAVE_asctime */
__NAMESPACE_STD_END
#include <libc/local/time/asctime.h>
__NAMESPACE_STD_BEGIN
/* >> asctime(3)
 * Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is  the  representation  of  `tp'  in  this  format */
__NAMESPACE_LOCAL_USING_OR_IMPL(asctime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL asctime)(struct __NAMESPACE_STD_SYM tm const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asctime))(__tp); })
#endif /* !__CRT_HAVE_asctime */
#ifdef __USE_ISOC11
#ifndef __std_asctime_s_defined
#define __std_asctime_s_defined
#ifdef __asctime_s_defined
/* >> asctime_s(3) */
__NAMESPACE_GLB_USING_OR_IMPL(asctime_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUTS(1, 2) __errno_t __NOTHROW_NCX(__LIBCCALL asctime_s)(char *__restrict __buf, size_t __buflen, struct __NAMESPACE_STD_SYM tm const *__restrict __tp) { return :: asctime_s(__buf, __buflen, __tp); })
#elif defined(__CRT_HAVE_asctime_s)
/* >> asctime_s(3) */
__CDECLARE(__ATTR_IN(3) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,asctime_s,(char *__restrict __buf, size_t __buflen, struct __NAMESPACE_STD_SYM tm const *__restrict __tp),(__buf,__buflen,__tp))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/time/asctime_s.h>
__NAMESPACE_STD_BEGIN
/* >> asctime_s(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(asctime_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUTS(1, 2) __errno_t __NOTHROW_NCX(__LIBCCALL asctime_s)(char *__restrict __buf, size_t __buflen, struct __NAMESPACE_STD_SYM tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asctime_s))(__buf, __buflen, __tp); })
#endif /* !... */
#endif /* !__std_asctime_s_defined */
#endif /* __USE_ISOC11 */
#if defined(__USE_ISOCXX17) || defined(__USE_ISOC11)
#if defined(__CRT_HAVE_timespec_get) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_get,(struct timespec *__ts, int __base),(__ts,__base))
#elif defined(__CRT_HAVE__timespec32_get) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_get,(struct timespec *__ts, int __base),_timespec32_get,(__ts,__base))
#elif defined(__CRT_HAVE_timespec_get64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_get,(struct timespec *__ts, int __base),timespec_get64,(__ts,__base))
#elif defined(__CRT_HAVE__timespec64_get) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_get,(struct timespec *__ts, int __base),_timespec64_get,(__ts,__base))
#elif defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime))
__NAMESPACE_STD_END
#include <libc/local/time/timespec_get.h>
__NAMESPACE_STD_BEGIN
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__NAMESPACE_LOCAL_USING_OR_IMPL(timespec_get, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL timespec_get)(struct timespec *__ts, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timespec_get))(__ts, __base); })
#endif /* ... */
#endif /* __USE_ISOCXX17 || __USE_ISOC11 */
#if defined(__USE_ISOC23)
#if defined(__CRT_HAVE_timespec_getres) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_getres,(struct timespec *__ts, int __base),(__ts,__base))
#elif defined(__CRT_HAVE__timespec32_get) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_getres,(struct timespec *__ts, int __base),_timespec32_get,(__ts,__base))
#elif defined(__CRT_HAVE_timespec_getres64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_getres,(struct timespec *__ts, int __base),timespec_getres64,(__ts,__base))
#elif defined(__CRT_HAVE__timespec64_get) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_getres,(struct timespec *__ts, int __base),_timespec64_get,(__ts,__base))
#elif defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && (defined(__CRT_HAVE_clock_getres64) || defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres))
__NAMESPACE_STD_END
#include <libc/local/time/timespec_getres.h>
__NAMESPACE_STD_BEGIN
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
__NAMESPACE_LOCAL_USING_OR_IMPL(timespec_getres, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL timespec_getres)(struct timespec *__ts, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timespec_getres))(__ts, __base); })
#endif /* ... */
#endif /* __USE_ISOC23 */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_clock) || (defined(__CLOCK_PROCESS_CPUTIME_ID) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime))) || defined(__CRT_HAVE_times) || defined(__CRT_HAVE___times) || defined(__CRT_HAVE___libc_times)
__NAMESPACE_STD_USING(clock)
#endif /* __CRT_HAVE_clock || (__CLOCK_PROCESS_CPUTIME_ID && (__CRT_HAVE_clock_gettime64 || __CRT_HAVE_clock_gettime || __CRT_HAVE___clock_gettime)) || __CRT_HAVE_times || __CRT_HAVE___times || __CRT_HAVE___libc_times */
#if defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_STD_USING(time)
#endif /* __CRT_HAVE_time64 || __CRT_HAVE__time64 || __CRT_HAVE_time || __CRT_HAVE___time || __CRT_HAVE___libc_time || __CRT_HAVE__time32 */
#if !defined(__difftime_defined) && defined(__std_difftime_defined)
#define __difftime_defined
__NAMESPACE_STD_USING(difftime)
#endif /* !__difftime_defined && __std_difftime_defined */
__NAMESPACE_STD_USING(mktime)
__NAMESPACE_STD_USING(ctime)
__NAMESPACE_STD_USING(gmtime)
__NAMESPACE_STD_USING(localtime)
__NAMESPACE_STD_USING(strftime)
__NAMESPACE_STD_USING(asctime)
#if !defined(__asctime_s_defined) && defined(__std_asctime_s_defined)
#define __asctime_s_defined
__NAMESPACE_STD_USING(asctime_s)
#endif /* !__asctime_s_defined && __std_asctime_s_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_time) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(__ATTR_OUT_OPT(1),__time64_t,__NOTHROW_NCX,time64,(__time64_t *__timer),time,(__timer))
#elif defined(__CRT_HAVE___time) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(__ATTR_OUT_OPT(1),__time64_t,__NOTHROW_NCX,time64,(__time64_t *__timer),__time,(__timer))
#elif defined(__CRT_HAVE___libc_time) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(__ATTR_OUT_OPT(1),__time64_t,__NOTHROW_NCX,time64,(__time64_t *__timer),__libc_time,(__timer))
#elif defined(__CRT_HAVE_time64)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CDECLARE(__ATTR_OUT_OPT(1),__time64_t,__NOTHROW_NCX,time64,(__time64_t *__timer),(__timer))
#elif defined(__CRT_HAVE__time64)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(__ATTR_OUT_OPT(1),__time64_t,__NOTHROW_NCX,time64,(__time64_t *__timer),_time64,(__timer))
#elif defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/time/time64.h>
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(time64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(1) __time64_t __NOTHROW_NCX(__LIBCCALL time64)(__time64_t *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(time64))(__timer); })
#endif /* ... */
#ifndef __NO_FPU
#ifndef __difftime64_defined
#define __difftime64_defined
#if defined(__CRT_HAVE_difftime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime64,(__time64_t __time1, __time64_t __time0),difftime,(__time1,__time0))
#elif defined(__CRT_HAVE_difftime64)
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime64,(__time64_t __time1, __time64_t __time0),(__time1,__time0))
#elif defined(__CRT_HAVE__difftime64)
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime64,(__time64_t __time1, __time64_t __time0),_difftime64,(__time1,__time0))
#elif defined(__CRT_HAVE___difftime64)
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime64,(__time64_t __time1, __time64_t __time0),__difftime64,(__time1,__time0))
#else /* ... */
#include <libc/local/time/difftime64.h>
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__NAMESPACE_LOCAL_USING_OR_IMPL(difftime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW_NCX(__LIBCCALL difftime64)(__time64_t __time1, __time64_t __time0) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(difftime64))(__time1, __time0); })
#endif /* !... */
#endif /* !__difftime64_defined */
#endif /* !__NO_FPU */
#if defined(__CRT_HAVE_mktime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE_mktime64)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),(__tp))
#elif defined(__CRT_HAVE__mktime64)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),timelocal64,(__tp))
#else /* ... */
#include <libc/local/time/mktime64.h>
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mktime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1) __time64_t __NOTHROW_NCX(__LIBCCALL mktime64)(struct __NAMESPACE_STD_SYM tm *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime64))(__tp); })
#endif /* !... */
#if defined(__CRT_HAVE_ctime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,ctime64,(__time64_t const *__timer),ctime,(__timer))
#elif defined(__CRT_HAVE_ctime64)
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,ctime64,(__time64_t const *__timer),(__timer))
#elif defined(__CRT_HAVE__ctime64)
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,ctime64,(__time64_t const *__timer),_ctime64,(__timer))
#else /* ... */
#include <libc/local/time/ctime64.h>
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL ctime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime64))(__timer); })
#endif /* !... */
#if defined(__CRT_HAVE_gmtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime64,(__time64_t const *__timer),gmtime,(__timer))
#elif defined(__CRT_HAVE_gmtime64)
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime64,(__time64_t const *__timer),(__timer))
#elif defined(__CRT_HAVE__gmtime64)
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime64,(__time64_t const *__timer),_gmtime64,(__timer))
#else /* ... */
#include <libc/local/time/gmtime64.h>
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__NAMESPACE_LOCAL_USING_OR_IMPL(gmtime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL gmtime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime64))(__timer); })
#endif /* !... */
#if defined(__CRT_HAVE_localtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime64,(__time64_t const *__timer),localtime,(__timer))
#elif defined(__CRT_HAVE_localtime64)
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime64,(__time64_t const *__timer),(__timer))
#elif defined(__CRT_HAVE__localtime64)
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime64,(__time64_t const *__timer),_localtime64,(__timer))
#else /* ... */
#include <libc/local/time/localtime64.h>
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__NAMESPACE_LOCAL_USING_OR_IMPL(localtime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL localtime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime64))(__timer); })
#endif /* !... */
#endif /* __USE_TIME64 */



#ifndef __tzname
#ifdef tzname
#define __tzname tzname
#elif defined(__LOCAL_tzname)
#define __tzname __LOCAL_tzname
#elif defined(__CRT_HAVE_tzname)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE2(,char *tzname[2],tzname)
#define tzname   tzname
#define __tzname tzname
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT2(,char *__tzname[2],__tzname,tzname)
#define __tzname __tzname
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE__tzname)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE2(,char *_tzname[2],_tzname)
#define _tzname  _tzname
#define __tzname _tzname
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT2(,char *__tzname[2],__tzname,_tzname)
#define __tzname __tzname
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___tzname) && !defined(__CRT_DOS)
__CSDECLARE2(,char *__tzname[2],__tzname)
#define __tzname __tzname
#elif defined(__CRT_HAVE___tzname) && defined(__CRT_DOS)
#ifndef ____dos_tzname_defined
#define ____dos_tzname_defined
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_CONST,char **,__NOTHROW_NCX,__dos_tzname,(void),__tzname,())
#endif /* !____dos_tzname_defined */
#define __tzname __dos_tzname()
#elif defined(__CRT_HAVE_DOS$__tzname)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_CONST,char **,__NOTHROW_NCX,__dos_tzname,(void),__tzname,())
#define __tzname __dos_tzname()
#endif /* ... */
#endif /* !__tzname */

#ifndef __daylight
#ifdef daylight
#define __daylight daylight
#elif defined(__LOCAL_daylight)
#define __daylight __LOCAL_daylight
#elif defined(__CRT_HAVE_daylight)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,int,daylight)
#define daylight   daylight
#define __daylight daylight
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,int,__daylight,daylight)
#define __daylight __daylight
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE__daylight)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,int,_daylight)
#define _daylight  _daylight
#define __daylight _daylight
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,int,__daylight,_daylight)
#define __daylight __daylight
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___daylight) && !defined(__CRT_DOS)
__CSDECLARE(,int,__daylight)
#define __daylight __daylight
#elif defined(__CRT_HAVE___daylight) && defined(__CRT_DOS)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_CONST,int *,__NOTHROW_NCX,__dos_daylight,(void),__daylight,())
#define __daylight (*__dos_daylight())
#elif defined(__CRT_HAVE_DOS$__daylight)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_CONST,int *,__NOTHROW_NCX,__dos_daylight,(void),__daylight,())
#define __daylight (*__dos_daylight())
#endif /* ... */
#endif /* !__daylight */

#ifndef __timezone
#ifdef timezone
#define __timezone timezone
#elif defined(__LOCAL_timezone)
#define __timezone __LOCAL_timezone
#elif defined(__CRT_HAVE_timezone)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,long,timezone)
#define timezone   timezone
#define __timezone timezone
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,long,__timezone,timezone)
#define __timezone __timezone
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE__timezone)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,long,_timezone)
#define _timezone  _timezone
#define __timezone _timezone
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,long,__timezone,_timezone)
#define __timezone __timezone
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___timezone) && !defined(__CRT_DOS)
__CSDECLARE(,long,__timezone)
#define __timezone __timezone
#elif defined(__CRT_HAVE___daylight) && defined(__CRT_DOS)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_CONST,long *,__NOTHROW_NCX,__dos_timezone,(void),__timezone,())
#define __timezone (*__dos_timezone())
#elif defined(__CRT_HAVE_DOS$__timezone)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_CONST,long *,__NOTHROW_NCX,__dos_timezone,(void),__timezone,())
#define __timezone (*__dos_timezone())
#endif /* ... */
#endif /* !__timezone */

#ifdef __USE_POSIX
#ifndef tzname
#ifdef __tzname
#define tzname __tzname
#elif defined(__LOCAL_tzname)
#define tzname __LOCAL_tzname
#elif defined(__CRT_HAVE_tzname)
__CSDECLARE2(,char *tzname[2],tzname)
#define tzname tzname
#elif defined(__CRT_HAVE___tzname) && !defined(__CRT_DOS)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE2(,char *__tzname[2],__tzname)
#define __tzname __tzname
#define tzname   __tzname
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT2(,char *tzname[2],tzname,__tzname)
#define tzname tzname
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___tzname) && defined(__CRT_DOS)
#ifndef ____dos_tzname_defined
#define ____dos_tzname_defined
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_CONST,char **,__NOTHROW_NCX,__dos_tzname,(void),__tzname,())
#endif /* !____dos_tzname_defined */
#define tzname __dos_tzname()
#elif defined(__CRT_HAVE_DOS$__tzname)
#ifndef ____dos_tzname_defined
#define ____dos_tzname_defined
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_CONST,char **,__NOTHROW_NCX,__dos_tzname,(void),__tzname,())
#endif /* !____dos_tzname_defined */
#define __tzname __dos_tzname()
#endif /* ... */
#endif /* !tzname */
#ifdef __CRT_HAVE_tzset
/* >> tzset(3)
 * Set time conversion information from the `$TZ' environment variable.
 * If  `$TZ'  is  not  defined,  a  locale-dependent  default  is  used */
__CDECLARE_VOID(,__NOTHROW_NCX,tzset,(void),())
#elif defined(__CRT_HAVE__tzset)
/* >> tzset(3)
 * Set time conversion information from the `$TZ' environment variable.
 * If  `$TZ'  is  not  defined,  a  locale-dependent  default  is  used */
__CREDIRECT_VOID(,__NOTHROW_NCX,tzset,(void),_tzset,())
#endif /* ... */
#endif /* __USE_POSIX */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef daylight
#ifdef __CRT_HAVE_daylight
__CSDECLARE(,int,daylight)
#define daylight daylight
#elif defined(__daylight)
#define daylight __daylight
#endif /* ... */
#endif /* !daylight */

#ifndef timezone
#ifdef __CRT_HAVE_timezone
__CSDECLARE(,long,timezone)
#elif defined(__CRT_HAVE__timezone) && !defined(__NO_COMPILER_SREDIRECT)
__CSREDIRECT(,long,timezone,_timezone)
#elif defined(__CRT_HAVE___timezone) && !defined(__NO_COMPILER_SREDIRECT) && !defined(__CRT_DOS)
__CSREDIRECT(,long,timezone,__timezone)
#elif defined(__timezone)
#define timezone __timezone
#ifdef __struct_timezone_defined
#ifdef __CRT_HAVE___timezone
#warning "Please #include <sys/time.h> after <time.h>, else `struct timezone' cannot be used"
#else /* __CRT_HAVE___timezone */
#warning "With the linked libc, `struct timezone' from <sys/time.h> cannot be used after <time.h> was included"
#endif /* !__CRT_HAVE___timezone */
#endif /* __struct_timezone_defined */
#endif /* ... */
#endif /* !timezone */

#endif /* __USE_MISC || __USE_XOPEN */

#ifdef __USE_MISC
#ifndef __stime_defined
#define __stime_defined
#if defined(__CRT_HAVE_stime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,stime,(__time_t const *__when),(__when))
#elif defined(__CRT_HAVE___stime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,stime,(__time_t const *__when),__stime,(__when))
#elif defined(__CRT_HAVE___libc_stime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,stime,(__time_t const *__when),__libc_stime,(__when))
#elif defined(__CRT_HAVE_stime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,stime,(__time_t const *__when),stime64,(__when))
#elif defined(__CRT_HAVE_stime64) || defined(__CRT_HAVE_stime) || defined(__CRT_HAVE___stime) || defined(__CRT_HAVE___libc_stime)
#include <libc/local/time/stime.h>
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__NAMESPACE_LOCAL_USING_OR_IMPL(stime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL stime)(__time_t const *__when) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stime))(__when); })
#else /* ... */
#undef __stime_defined
#endif /* !... */
#endif /* !__stime_defined */
#if defined(__CRT_HAVE_timegm) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time_t,__NOTHROW_NCX,timegm,(struct __NAMESPACE_STD_SYM tm *__tp),(__tp))
#elif defined(__CRT_HAVE__mkgmtime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time_t,__NOTHROW_NCX,timegm,(struct __NAMESPACE_STD_SYM tm *__tp),_mkgmtime,(__tp))
#elif defined(__CRT_HAVE__mkgmtime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time_t,__NOTHROW_NCX,timegm,(struct __NAMESPACE_STD_SYM tm *__tp),_mkgmtime32,(__tp))
#elif defined(__CRT_HAVE_timegm64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time_t,__NOTHROW_NCX,timegm,(struct __NAMESPACE_STD_SYM tm *__tp),timegm64,(__tp))
#elif defined(__CRT_HAVE__mkgmtime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time_t,__NOTHROW_NCX,timegm,(struct __NAMESPACE_STD_SYM tm *__tp),_mkgmtime64,(__tp))
#else /* ... */
#include <libc/local/time/timegm.h>
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__NAMESPACE_LOCAL_USING_OR_IMPL(timegm, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1) __time_t __NOTHROW_NCX(__LIBCCALL timegm)(struct __NAMESPACE_STD_SYM tm *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timegm))(__tp); })
#endif /* !... */
#if defined(__CRT_HAVE_mktime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timelocal(3), timelocal64(3)
 * Another   name   for   `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time_t,__NOTHROW_NCX,timelocal,(struct __NAMESPACE_STD_SYM tm *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE__mktime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timelocal(3), timelocal64(3)
 * Another   name   for   `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time_t,__NOTHROW_NCX,timelocal,(struct __NAMESPACE_STD_SYM tm *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timelocal(3), timelocal64(3)
 * Another   name   for   `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time_t,__NOTHROW_NCX,timelocal,(struct __NAMESPACE_STD_SYM tm *__tp),timelocal64,(__tp))
#elif defined(__CRT_HAVE_mktime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timelocal(3), timelocal64(3)
 * Another   name   for   `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time_t,__NOTHROW_NCX,timelocal,(struct __NAMESPACE_STD_SYM tm *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE__mktime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timelocal(3), timelocal64(3)
 * Another   name   for   `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time_t,__NOTHROW_NCX,timelocal,(struct __NAMESPACE_STD_SYM tm *__tp),_mktime32,(__tp))
#elif defined(__CRT_HAVE_timelocal) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timelocal(3), timelocal64(3)
 * Another   name   for   `mktime' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time_t,__NOTHROW_NCX,timelocal,(struct __NAMESPACE_STD_SYM tm *__tp),(__tp))
#else /* ... */
#include <libc/local/time/mktime.h>
/* >> timelocal(3), timelocal64(3)
 * Another   name   for   `mktime' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1) __time_t __NOTHROW_NCX(__LIBCCALL timelocal)(struct __NAMESPACE_STD_SYM tm *__tp) { return (__time_t)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime))(__tp); }
#endif /* !... */
#ifdef __CRT_HAVE_dysize
/* >> dysize(3)
 * Return the number of days in YEAR */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,dysize,(__STDC_INT_AS_UINT_T __year),(__year))
#else /* __CRT_HAVE_dysize */
#include <libc/local/time/dysize.h>
/* >> dysize(3)
 * Return the number of days in YEAR */
__NAMESPACE_LOCAL_USING_OR_IMPL(dysize, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL dysize)(__STDC_INT_AS_UINT_T __year) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dysize))(__year); })
#endif /* !__CRT_HAVE_dysize */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_stime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,stime64,(__time64_t const *__when),stime,(__when))
#elif defined(__CRT_HAVE___stime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,stime64,(__time64_t const *__when),__stime,(__when))
#elif defined(__CRT_HAVE___libc_stime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,stime64,(__time64_t const *__when),__libc_stime,(__when))
#elif defined(__CRT_HAVE_stime64)
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,stime64,(__time64_t const *__when),(__when))
#elif defined(__CRT_HAVE_stime) || defined(__CRT_HAVE___stime) || defined(__CRT_HAVE___libc_stime)
#include <libc/local/time/stime64.h>
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__NAMESPACE_LOCAL_USING_OR_IMPL(stime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL stime64)(__time64_t const *__when) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stime64))(__when); })
#endif /* ... */
#if defined(__CRT_HAVE_timegm) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,timegm64,(struct __NAMESPACE_STD_SYM tm *__tp),timegm,(__tp))
#elif defined(__CRT_HAVE_timegm64)
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,timegm64,(struct __NAMESPACE_STD_SYM tm *__tp),(__tp))
#elif defined(__CRT_HAVE__mkgmtime64)
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,timegm64,(struct __NAMESPACE_STD_SYM tm *__tp),_mkgmtime64,(__tp))
#else /* ... */
#include <libc/local/time/timegm64.h>
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__NAMESPACE_LOCAL_USING_OR_IMPL(timegm64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1) __time64_t __NOTHROW_NCX(__LIBCCALL timegm64)(struct __NAMESPACE_STD_SYM tm *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timegm64))(__tp); })
#endif /* !... */
#if defined(__CRT_HAVE_mktime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> timelocal(3), timelocal64(3)
 * Another   name   for   `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,timelocal64,(struct __NAMESPACE_STD_SYM tm *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE_mktime64)
/* >> timelocal(3), timelocal64(3)
 * Another   name   for   `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,timelocal64,(struct __NAMESPACE_STD_SYM tm *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE__mktime64)
/* >> timelocal(3), timelocal64(3)
 * Another   name   for   `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,timelocal64,(struct __NAMESPACE_STD_SYM tm *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64)
/* >> timelocal(3), timelocal64(3)
 * Another   name   for   `mktime' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,timelocal64,(struct __NAMESPACE_STD_SYM tm *__tp),(__tp))
#else /* ... */
#include <libc/local/time/mktime64.h>
/* >> timelocal(3), timelocal64(3)
 * Another   name   for   `mktime' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1) __time64_t __NOTHROW_NCX(__LIBCCALL timelocal64)(struct __NAMESPACE_STD_SYM tm *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime64))(__tp); }
#endif /* !... */
#endif /* __USE_TIME64 */
#endif /* __USE_MISC */

#ifdef __USE_POSIX199309
#if defined(__CRT_HAVE_nanosleep) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),(__requested_time,__remaining))
#elif defined(__CRT_HAVE___nanosleep) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),__nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE___libc_nanosleep) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),__libc_nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,nanosleep,(struct timespec const *__requested_time, struct timespec *__remaining),nanosleep64,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep)
#include <libc/local/time/nanosleep.h>
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
__NAMESPACE_LOCAL_USING_OR_IMPL(nanosleep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) int __NOTHROW_RPC(__LIBCCALL nanosleep)(struct timespec const *__requested_time, struct timespec *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanosleep))(__requested_time, __remaining); })
#endif /* ... */
#if defined(__CRT_HAVE_clock_getres) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_NCX,clock_getres,(clockid_t __clock_id, struct timespec *__res),(__clock_id,__res))
#elif defined(__CRT_HAVE___clock_getres) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,clock_getres,(clockid_t __clock_id, struct timespec *__res),__clock_getres,(__clock_id,__res))
#elif defined(__CRT_HAVE_clock_getres64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,clock_getres,(clockid_t __clock_id, struct timespec *__res),clock_getres64,(__clock_id,__res))
#elif defined(__CRT_HAVE_clock_getres64) || defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres)
#include <libc/local/time/clock_getres.h>
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_getres, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL clock_getres)(clockid_t __clock_id, struct timespec *__res) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_getres))(__clock_id, __res); })
#endif /* ... */
#if defined(__CRT_HAVE_clock_gettime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_NCX,clock_gettime,(clockid_t __clock_id, struct timespec *__tp),(__clock_id,__tp))
#elif defined(__CRT_HAVE___clock_gettime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,clock_gettime,(clockid_t __clock_id, struct timespec *__tp),__clock_gettime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,clock_gettime,(clockid_t __clock_id, struct timespec *__tp),clock_gettime64,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime)
#include <libc/local/time/clock_gettime.h>
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_gettime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL clock_gettime)(clockid_t __clock_id, struct timespec *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_gettime))(__clock_id, __tp); })
#endif /* ... */
#if defined(__CRT_HAVE_clock_settime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_settime(2), clock_settime64(2)
 * Set  clock  `clock_id'  to  value  `tp' */
__CDECLARE(__ATTR_IN(2),int,__NOTHROW_NCX,clock_settime,(clockid_t __clock_id, struct timespec const *__tp),(__clock_id,__tp))
#elif defined(__CRT_HAVE___clock_settime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_settime(2), clock_settime64(2)
 * Set  clock  `clock_id'  to  value  `tp' */
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,clock_settime,(clockid_t __clock_id, struct timespec const *__tp),__clock_settime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_settime(2), clock_settime64(2)
 * Set  clock  `clock_id'  to  value  `tp' */
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,clock_settime,(clockid_t __clock_id, struct timespec const *__tp),clock_settime64,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime64) || defined(__CRT_HAVE_clock_settime) || defined(__CRT_HAVE___clock_settime)
#include <libc/local/time/clock_settime.h>
/* >> clock_settime(2), clock_settime64(2)
 * Set  clock  `clock_id'  to  value  `tp' */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_settime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL clock_settime)(clockid_t __clock_id, struct timespec const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_settime))(__clock_id, __tp); })
#endif /* ... */
/* >> timer_create(2)
 * Create new per-process timer using `clock_id' */
__CDECLARE_OPT(__ATTR_IN_OPT(2) __ATTR_OUT(3),int,__NOTHROW_NCX,timer_create,(clockid_t __clock_id, struct sigevent *__restrict __evp, timer_t *__restrict __timerid),(__clock_id,__evp,__timerid))
/* >> timer_delete(2)
 * Delete timer `timerid' */
__CDECLARE_OPT(,int,__NOTHROW_NCX,timer_delete,(timer_t __timerid),(__timerid))
#if defined(__CRT_HAVE_timer_settime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
__CDECLARE(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,timer_settime,(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__restrict ___value, struct itimerspec *__restrict __ovalue),(__timerid,__flags,___value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
__CREDIRECT(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,timer_settime,(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__restrict ___value, struct itimerspec *__restrict __ovalue),timer_settime64,(__timerid,__flags,___value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime64) || defined(__CRT_HAVE_timer_settime)
#include <libc/local/time/timer_settime.h>
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
__NAMESPACE_LOCAL_USING_OR_IMPL(timer_settime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUT_OPT(4) int __NOTHROW_NCX(__LIBCCALL timer_settime)(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__restrict ___value, struct itimerspec *__restrict __ovalue) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timer_settime))(__timerid, __flags, ___value, __ovalue); })
#endif /* ... */
#if defined(__CRT_HAVE_timer_gettime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
__CDECLARE(__ATTR_OUT_OPT(2),int,__NOTHROW_NCX,timer_gettime,(timer_t __timerid, struct itimerspec *___value),(__timerid,___value))
#elif defined(__CRT_HAVE_timer_gettime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
__CREDIRECT(__ATTR_OUT_OPT(2),int,__NOTHROW_NCX,timer_gettime,(timer_t __timerid, struct itimerspec *___value),timer_gettime64,(__timerid,___value))
#elif defined(__CRT_HAVE_timer_gettime64) || defined(__CRT_HAVE_timer_gettime)
#include <libc/local/time/timer_gettime.h>
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
__NAMESPACE_LOCAL_USING_OR_IMPL(timer_gettime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(2) int __NOTHROW_NCX(__LIBCCALL timer_gettime)(timer_t __timerid, struct itimerspec *___value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timer_gettime))(__timerid, ___value); })
#endif /* ... */
/* >> timer_getoverrun(2)
 * Get expiration overrun for timer `timerid' */
__CDECLARE_OPT(,int,__NOTHROW_NCX,timer_getoverrun,(timer_t __timerid),(__timerid))

#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_clock_nanosleep) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME' */
__CDECLARE(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_RPC,clock_nanosleep,(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec const *__restrict __requested_time, struct timespec *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE___clock_nanosleep) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME' */
__CREDIRECT(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_RPC,clock_nanosleep,(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec const *__restrict __requested_time, struct timespec *__remaining),__clock_nanosleep,(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE_clock_nanosleep64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME' */
__CREDIRECT(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_RPC,clock_nanosleep,(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec const *__restrict __requested_time, struct timespec *__remaining),clock_nanosleep64,(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE_clock_nanosleep64) || defined(__CRT_HAVE_clock_nanosleep) || defined(__CRT_HAVE___clock_nanosleep)
#include <libc/local/time/clock_nanosleep.h>
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME' */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_nanosleep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUT_OPT(4) int __NOTHROW_RPC(__LIBCCALL clock_nanosleep)(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec const *__restrict __requested_time, struct timespec *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_nanosleep))(__clock_id, __flags, __requested_time, __remaining); })
#endif /* ... */
#ifdef __CRT_HAVE_clock_getcpuclockid
/* >> clock_getcpuclockid(2)
 * Return clock ID for CPU-time clock */
__CDECLARE(,int,__NOTHROW_NCX,clock_getcpuclockid,(pid_t __pid, clockid_t *__clock_id),(__pid,__clock_id))
#elif defined(__CRT_HAVE___clock_getcpuclockid)
/* >> clock_getcpuclockid(2)
 * Return clock ID for CPU-time clock */
__CREDIRECT(,int,__NOTHROW_NCX,clock_getcpuclockid,(pid_t __pid, clockid_t *__clock_id),__clock_getcpuclockid,(__pid,__clock_id))
#endif /* ... */
#endif /* __USE_XOPEN2K */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_nanosleep) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,nanosleep64,(struct timespec64 const *__restrict __requested_time, struct timespec64 *__remaining),nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE___nanosleep) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,nanosleep64,(struct timespec64 const *__restrict __requested_time, struct timespec64 *__remaining),__nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE___libc_nanosleep) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,nanosleep64,(struct timespec64 const *__restrict __requested_time, struct timespec64 *__remaining),__libc_nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep64)
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),int,__NOTHROW_RPC,nanosleep64,(struct timespec64 const *__restrict __requested_time, struct timespec64 *__remaining),(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep)
#include <libc/local/time/nanosleep64.h>
/* >> nanosleep(2), nanosleep64(2)
 * Pause execution for a number of nanoseconds */
__NAMESPACE_LOCAL_USING_OR_IMPL(nanosleep64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) int __NOTHROW_RPC(__LIBCCALL nanosleep64)(struct timespec64 const *__restrict __requested_time, struct timespec64 *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanosleep64))(__requested_time, __remaining); })
#endif /* ... */
#if defined(__CRT_HAVE_clock_getres) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,clock_getres64,(clockid_t __clock_id, struct timespec64 *__res),clock_getres,(__clock_id,__res))
#elif defined(__CRT_HAVE___clock_getres) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,clock_getres64,(clockid_t __clock_id, struct timespec64 *__res),__clock_getres,(__clock_id,__res))
#elif defined(__CRT_HAVE_clock_getres64)
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_NCX,clock_getres64,(clockid_t __clock_id, struct timespec64 *__res),(__clock_id,__res))
#elif defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres)
#include <libc/local/time/clock_getres64.h>
/* >> clock_getres(2), clock_getres64(2)
 * Get resolution of clock `clock_id' in `*res' */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_getres64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL clock_getres64)(clockid_t __clock_id, struct timespec64 *__res) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_getres64))(__clock_id, __res); })
#endif /* ... */
#if defined(__CRT_HAVE_clock_gettime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,clock_gettime64,(clockid_t __clock_id, struct timespec64 *__tp),clock_gettime,(__clock_id,__tp))
#elif defined(__CRT_HAVE___clock_gettime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,clock_gettime64,(clockid_t __clock_id, struct timespec64 *__tp),__clock_gettime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime64)
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_NCX,clock_gettime64,(clockid_t __clock_id, struct timespec64 *__tp),(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime)
#include <libc/local/time/clock_gettime64.h>
/* >> clock_gettime(2), clock_gettime64(2)
 * Get current value of clock `clock_id' and store it in `tp' */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_gettime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL clock_gettime64)(clockid_t __clock_id, struct timespec64 *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_gettime64))(__clock_id, __tp); })
#endif /* ... */
#if defined(__CRT_HAVE_clock_settime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> clock_settime(2), clock_settime64(2)
 * Set  clock  `clock_id'  to  value  `tp' */
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,clock_settime64,(clockid_t __clock_id, struct timespec64 const *__tp),clock_settime,(__clock_id,__tp))
#elif defined(__CRT_HAVE___clock_settime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> clock_settime(2), clock_settime64(2)
 * Set  clock  `clock_id'  to  value  `tp' */
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,clock_settime64,(clockid_t __clock_id, struct timespec64 const *__tp),__clock_settime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime64)
/* >> clock_settime(2), clock_settime64(2)
 * Set  clock  `clock_id'  to  value  `tp' */
__CDECLARE(__ATTR_IN(2),int,__NOTHROW_NCX,clock_settime64,(clockid_t __clock_id, struct timespec64 const *__tp),(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime) || defined(__CRT_HAVE___clock_settime)
#include <libc/local/time/clock_settime64.h>
/* >> clock_settime(2), clock_settime64(2)
 * Set  clock  `clock_id'  to  value  `tp' */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_settime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL clock_settime64)(clockid_t __clock_id, struct timespec64 const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_settime64))(__clock_id, __tp); })
#endif /* ... */
#if defined(__CRT_HAVE_timer_settime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
__CREDIRECT(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,timer_settime64,(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec64 const *__restrict ___value, struct itimerspec64 *__restrict __ovalue),timer_settime,(__timerid,__flags,___value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime64)
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
__CDECLARE(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,timer_settime64,(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec64 const *__restrict ___value, struct itimerspec64 *__restrict __ovalue),(__timerid,__flags,___value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime)
#include <libc/local/time/timer_settime64.h>
/* >> timer_settime(2), timer_settime64(2)
 * Set timer `timerid' to `value', returning old value in `ovalue' */
__NAMESPACE_LOCAL_USING_OR_IMPL(timer_settime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUT_OPT(4) int __NOTHROW_NCX(__LIBCCALL timer_settime64)(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec64 const *__restrict ___value, struct itimerspec64 *__restrict __ovalue) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timer_settime64))(__timerid, __flags, ___value, __ovalue); })
#endif /* ... */
#if defined(__CRT_HAVE_timer_gettime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,timer_gettime64,(timer_t __timerid, struct itimerspec64 *___value),timer_gettime,(__timerid,___value))
#elif defined(__CRT_HAVE_timer_gettime64)
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_NCX,timer_gettime64,(timer_t __timerid, struct itimerspec64 *___value),(__timerid,___value))
#elif defined(__CRT_HAVE_timer_gettime)
#include <libc/local/time/timer_gettime64.h>
/* >> timer_gettime(2), timer_gettime64(2)
 * Get current value of timer `timerid' and store it in `value' */
__NAMESPACE_LOCAL_USING_OR_IMPL(timer_gettime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL timer_gettime64)(timer_t __timerid, struct itimerspec64 *___value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timer_gettime64))(__timerid, ___value); })
#endif /* ... */

#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_clock_nanosleep) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME' */
__CREDIRECT(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_RPC,clock_nanosleep64,(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec64 const *__requested_time, struct timespec64 *__remaining),clock_nanosleep,(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE_clock_nanosleep64)
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME' */
__CDECLARE(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_RPC,clock_nanosleep64,(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec64 const *__requested_time, struct timespec64 *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE_clock_nanosleep) || defined(__CRT_HAVE___clock_nanosleep)
#include <libc/local/time/clock_nanosleep64.h>
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME' */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_nanosleep64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUT_OPT(4) int __NOTHROW_RPC(__LIBCCALL clock_nanosleep64)(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec64 const *__requested_time, struct timespec64 *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_nanosleep64))(__clock_id, __flags, __requested_time, __remaining); })
#endif /* ... */
#endif /* __USE_XOPEN2K */
#endif /* __USE_TIME64 */
#endif /* __USE_POSIX199309 */

/* timespec_get() is defined by both c11 and c++17 */
#if defined(__USE_ISOCXX17) || defined(__USE_ISOC11)
#ifndef __CXX_SYSTEM_HEADER
#if (defined(__CRT_HAVE_timespec_get) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE__timespec32_get) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_timespec_get64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE__timespec64_get) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime)))
__NAMESPACE_STD_USING(timespec_get)
#endif /* (__CRT_HAVE_timespec_get && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE__timespec32_get && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE_timespec_get64 && (__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE__timespec64_get && (__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CLOCK_REALTIME && __TIME_UTC && (__CRT_HAVE_clock_gettime64 || __CRT_HAVE_clock_gettime || __CRT_HAVE___clock_gettime)) */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_timespec_get) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_get64,(struct timespec64 *__ts, int __base),timespec_get,(__ts,__base))
#elif defined(__CRT_HAVE_timespec_get64)
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_get64,(struct timespec64 *__ts, int __base),(__ts,__base))
#elif defined(__CRT_HAVE__timespec64_get)
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_get64,(struct timespec64 *__ts, int __base),_timespec64_get,(__ts,__base))
#elif defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime))
#include <libc/local/time/timespec_get64.h>
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__NAMESPACE_LOCAL_USING_OR_IMPL(timespec_get64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL timespec_get64)(struct timespec64 *__ts, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timespec_get64))(__ts, __base); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_ISOCXX17 || __USE_ISOC11 */

#if defined(__USE_ISOC23)
#ifndef __CXX_SYSTEM_HEADER
#if (defined(__CRT_HAVE_timespec_getres) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE__timespec32_get) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE_timespec_getres64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CRT_HAVE__timespec64_get) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && (defined(__CRT_HAVE_clock_getres64) || defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres)))
__NAMESPACE_STD_USING(timespec_getres)
#endif /* (__CRT_HAVE_timespec_getres && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE__timespec32_get && (!__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE_timespec_getres64 && (__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CRT_HAVE__timespec64_get && (__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)) || (__CLOCK_REALTIME && __TIME_UTC && (__CRT_HAVE_clock_getres64 || __CRT_HAVE_clock_getres || __CRT_HAVE___clock_getres)) */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_timespec_getres) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_getres64,(struct timespec64 *__ts, int __base),timespec_getres,(__ts,__base))
#elif defined(__CRT_HAVE_timespec_getres64)
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_getres64,(struct timespec64 *__ts, int __base),(__ts,__base))
#elif defined(__CRT_HAVE__timespec64_get)
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,timespec_getres64,(struct timespec64 *__ts, int __base),_timespec64_get,(__ts,__base))
#elif defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && (defined(__CRT_HAVE_clock_getres64) || defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres))
#include <libc/local/time/timespec_getres64.h>
/* >> timespec_getres(3), timespec_getres64(3)
 * Set `ts' to calendar time based in time base `base' */
__NAMESPACE_LOCAL_USING_OR_IMPL(timespec_getres64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL timespec_getres64)(struct timespec64 *__ts, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timespec_getres64))(__ts, __base); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_ISOC23 */

#ifdef __USE_XOPEN_EXTENDED
/* Set to one of the following values to indicate an error.
     1  the DATEMSK environment variable is null or undefined,
     2  the template file cannot be opened for reading,
     3  failed to get file status information,
     4  the template file is not a regular file,
     5  an error is encountered while reading the template file,
     6  memory allocation failed (not enough memory available),
     7  there is no line in the template that matches the input,
     8  invalid input specification Example: February 31 or a time is
        specified that can not be represented in a time_t (representing
        the time in seconds since 00:00:00 UTC, January 1, 1970) */
#ifndef getdate_err
#ifdef __LOCAL_getdate_err
#define getdate_err __LOCAL_getdate_err
#elif defined(__CRT_HAVE_getdate_err)
__CSDECLARE(,int,getdate_err)
#define getdate_err getdate_err
#endif /* __CRT_HAVE_getdate_err */
#endif /* !getdate_err */
#ifdef __CRT_HAVE_getdate
/* >> getdate(3)
 * Parse the given string as a date specification and return a value
 * representing the value. The templates from the file identified by
 * the environment variable `$DATEMSK' are used. In case of an error
 * `getdate_err' is set */
__CDECLARE(__ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,getdate,(const char *__string),(__string))
#else /* __CRT_HAVE_getdate */
#include <libc/template/getdate_err.h>
#ifdef __LOCAL_getdate_err
#include <libc/local/time/getdate.h>
/* >> getdate(3)
 * Parse the given string as a date specification and return a value
 * representing the value. The templates from the file identified by
 * the environment variable `$DATEMSK' are used. In case of an error
 * `getdate_err' is set */
__NAMESPACE_LOCAL_USING_OR_IMPL(getdate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL getdate)(const char *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdate))(__string); })
#endif /* __LOCAL_getdate_err */
#endif /* !__CRT_HAVE_getdate */
#endif /* __USE_XOPEN_EXTENDED */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_strftime_l
/* >> strftime_l(3)
 * Similar to `strftime(3)' but take the information from
 * the   provided  locale  and   not  the  global  locale */
__CDECLARE(__ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_STRFTIME(3, 0) __ATTR_OUTS(1, 2),__SIZE_TYPE__,__NOTHROW_NCX,strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),(__buf,__bufsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE__strftime_l)
/* >> strftime_l(3)
 * Similar to `strftime(3)' but take the information from
 * the   provided  locale  and   not  the  global  locale */
__CREDIRECT(__ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_STRFTIME(3, 0) __ATTR_OUTS(1, 2),__SIZE_TYPE__,__NOTHROW_NCX,strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),_strftime_l,(__buf,__bufsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE___strftime_l)
/* >> strftime_l(3)
 * Similar to `strftime(3)' but take the information from
 * the   provided  locale  and   not  the  global  locale */
__CREDIRECT(__ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_STRFTIME(3, 0) __ATTR_OUTS(1, 2),__SIZE_TYPE__,__NOTHROW_NCX,strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),__strftime_l,(__buf,__bufsize,__format,__tp,__locale))
#else /* ... */
#include <libc/local/time/strftime_l.h>
/* >> strftime_l(3)
 * Similar to `strftime(3)' but take the information from
 * the   provided  locale  and   not  the  global  locale */
__NAMESPACE_LOCAL_USING_OR_IMPL(strftime_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_STRFTIME(3, 0) __ATTR_OUTS(1, 2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strftime_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strftime_l))(__buf, __bufsize, __format, __tp, __locale); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_XOPEN
#ifdef __CRT_HAVE_strptime
/* >> strptime(3)
 * Parse `s' according to `format' and store binary time information in `tp'.
 * The return  value is  a pointer  to the  first unparsed  character in  `s' */
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3),char *,__NOTHROW_NCX,strptime,(char const *__restrict __s, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm *__restrict __tp),(__s,__format,__tp))
#else /* __CRT_HAVE_strptime */
#include <libc/local/time/strptime.h>
/* >> strptime(3)
 * Parse `s' according to `format' and store binary time information in `tp'.
 * The return  value is  a pointer  to the  first unparsed  character in  `s' */
__NAMESPACE_LOCAL_USING_OR_IMPL(strptime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) char *__NOTHROW_NCX(__LIBCCALL strptime)(char const *__restrict __s, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strptime))(__s, __format, __tp); })
#endif /* !__CRT_HAVE_strptime */
#endif /* __USE_XOPEN */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_strptime_l
/* >> strptime_l(3)
 * Similar to `strptime' but take the information from
 * the  provided  locale  and  not  the  global locale */
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3),char *,__NOTHROW_NCX,strptime_l,(char const *__restrict __s, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm *__restrict __tp, __locale_t __locale),(__s,__format,__tp,__locale))
#else /* __CRT_HAVE_strptime_l */
#include <libc/local/time/strptime_l.h>
/* >> strptime_l(3)
 * Similar to `strptime' but take the information from
 * the  provided  locale  and  not  the  global locale */
__NAMESPACE_LOCAL_USING_OR_IMPL(strptime_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) char *__NOTHROW_NCX(__LIBCCALL strptime_l)(char const *__restrict __s, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strptime_l))(__s, __format, __tp, __locale); })
#endif /* !__CRT_HAVE_strptime_l */
#ifdef __CRT_HAVE_getdate_r
/* >> getdate_r(3)
 * Since  `getdate' is not  reentrant because of  the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The  functionality is  the same.  The  result is  returned in
 * the  buffer pointed to by `resbufp' and in case of an error, the return
 * value is != 0  with the same values  as given above for  `getdate_err'. */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,getdate_r,(char const *__restrict __string, struct __NAMESPACE_STD_SYM tm *__restrict __resbufp),(__string,__resbufp))
#else /* __CRT_HAVE_getdate_r */
#include <libc/local/time/getdate_r.h>
/* >> getdate_r(3)
 * Since  `getdate' is not  reentrant because of  the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The  functionality is  the same.  The  result is  returned in
 * the  buffer pointed to by `resbufp' and in case of an error, the return
 * value is != 0  with the same values  as given above for  `getdate_err'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(getdate_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL getdate_r)(char const *__restrict __string, struct __NAMESPACE_STD_SYM tm *__restrict __resbufp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdate_r))(__string, __resbufp); })
#endif /* !__CRT_HAVE_getdate_r */
#ifndef __clock_adjtime_defined
#define __clock_adjtime_defined
#if defined(__CRT_HAVE_clock_adjtime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_adjtime(2), clock_adjtime64(2) */
__CDECLARE(__ATTR_INOUT(2),int,__NOTHROW_NCX,clock_adjtime,(__clockid_t __clock_id, struct timex *__utx),(__clock_id,__utx))
#elif defined(__CRT_HAVE_clock_adjtime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> clock_adjtime(2), clock_adjtime64(2) */
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_NCX,clock_adjtime,(__clockid_t __clock_id, struct timex *__utx),clock_adjtime64,(__clock_id,__utx))
#else /* ... */
#undef __clock_adjtime_defined
#endif /* !... */
#endif /* !__clock_adjtime_defined */

#ifdef __USE_TIME64
#ifndef __clock_adjtime64_defined
#define __clock_adjtime64_defined
#if defined(__CRT_HAVE_clock_adjtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> clock_adjtime(2), clock_adjtime64(2) */
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_NCX,clock_adjtime64,(__clockid_t __clock_id, struct timex64 *__utx),clock_adjtime,(__clock_id,__utx))
#elif defined(__CRT_HAVE_clock_adjtime64)
/* >> clock_adjtime(2), clock_adjtime64(2) */
__CDECLARE(__ATTR_INOUT(2),int,__NOTHROW_NCX,clock_adjtime64,(__clockid_t __clock_id, struct timex64 *__utx),(__clock_id,__utx))
#else /* ... */
#undef __clock_adjtime64_defined
#endif /* !... */
#endif /* !__clock_adjtime64_defined */
#endif /* __USE_TIME64 */
#endif /* __USE_GNU */

#ifdef __USE_POSIX
#if defined(__CRT_HAVE_gmtime_r) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime_r,(__time_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),(__timer,__tp))
#elif defined(__CRT_HAVE___gmtime_r) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime_r,(__time_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),__gmtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE_gmtime64_r) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime_r,(__time_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime64_r,(__timer,__tp))
#else /* ... */
#include <libc/local/time/gmtime_r.h>
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(gmtime_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL gmtime_r)(__time_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime_r))(__timer, __tp); })
#endif /* !... */
#if defined(__CRT_HAVE_localtime_r) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime_r,(__time_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),(__timer,__tp))
#elif defined(__CRT_HAVE_localtime64_r) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime_r,(__time_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime64_r,(__timer,__tp))
#else /* ... */
#include <libc/local/time/localtime_r.h>
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(localtime_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL localtime_r)(__time_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime_r))(__timer, __tp); })
#endif /* !... */
#if defined(__CRT_HAVE_ctime_r) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,ctime_r,(__time_t const *__restrict __timer, char __buf[26]),(__timer,__buf))
#elif defined(__CRT_HAVE_ctime64_r) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,ctime_r,(__time_t const *__restrict __timer, char __buf[26]),ctime64_r,(__timer,__buf))
#else /* ... */
#include <libc/local/time/ctime_r.h>
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctime_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) char *__NOTHROW_NCX(__LIBCCALL ctime_r)(__time_t const *__restrict __timer, char __buf[26]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime_r))(__timer, __buf); })
#endif /* !... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_gmtime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE_gmtime64_r)
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,gmtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),(__timer,__tp))
#else /* ... */
#include <libc/local/time/gmtime64_r.h>
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(gmtime64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL gmtime64_r)(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime64_r))(__timer, __tp); })
#endif /* !... */
#if defined(__CRT_HAVE_localtime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE_localtime64_r)
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),(__timer,__tp))
#else /* ... */
#include <libc/local/time/localtime64_r.h>
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(localtime64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL localtime64_r)(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime64_r))(__timer, __tp); })
#endif /* !... */
#if defined(__CRT_HAVE_ctime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,ctime64_r,(__time64_t const *__restrict __timer, char __buf[26]),ctime_r,(__timer,__buf))
#elif defined(__CRT_HAVE_ctime64_r)
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,ctime64_r,(__time64_t const *__restrict __timer, char __buf[26]),(__timer,__buf))
#else /* ... */
#include <libc/local/time/ctime64_r.h>
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctime64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) char *__NOTHROW_NCX(__LIBCCALL ctime64_r)(__time64_t const *__restrict __timer, char __buf[26]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime64_r))(__timer, __buf); })
#endif /* !... */
#endif /* __USE_TIME64 */
#ifdef __CRT_HAVE_asctime_r
/* >> asctime_r(3)
 * Return in `buf' a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that   is   the   representation   of   `tp'   in   this   format */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,asctime_r,(struct __NAMESPACE_STD_SYM tm const *__restrict __tp, char __buf[26]),(__tp,__buf))
#else /* __CRT_HAVE_asctime_r */
#include <libc/local/time/asctime_r.h>
/* >> asctime_r(3)
 * Return in `buf' a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that   is   the   representation   of   `tp'   in   this   format */
__NAMESPACE_LOCAL_USING_OR_IMPL(asctime_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) char *__NOTHROW_NCX(__LIBCCALL asctime_r)(struct __NAMESPACE_STD_SYM tm const *__restrict __tp, char __buf[26]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asctime_r))(__tp, __buf); })
#endif /* !__CRT_HAVE_asctime_r */
#endif /* __USE_POSIX */


#ifdef __USE_DOS
#ifndef __ernno_t_defined
#define __ernno_t_defined
typedef __errno_t errno_t;
#endif /* !__ernno_t_defined */

#if !defined(_daylight) && defined(__daylight)
#define _daylight __daylight
#endif /* !_daylight && __daylight */
#if !defined(_timezone) && defined(__timezone)
#define _timezone __timezone
#endif /* !_timezone && __timezone */
#if !defined(_tzname) && defined(__tzname)
#define _tzname __tzname
#endif /* !_tzname && __tzname */
#if defined(__CRT_HAVE___dstbias) && defined(__CRT_DOS)
__LIBC __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED __LONG32_TYPE__ *__NOTHROW_NCX(__LIBDCALL __dstbias)(void) __CASMNAME_SAME("__dstbias");
#elif defined(__CRT_HAVE_DOS$__dstbias)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__LONG32_TYPE__ *,__NOTHROW_NCX,__dstbias,(void),__dstbias,())
#elif defined(__CRT_HAVE___p__dstbias)
__COMPILER_CREDIRECT(__LIBC,__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__LONG32_TYPE__ *,__NOTHROW_NCX,__LIBDCALL,__dstbias,(void),__p__dstbias,())
#else /* ... */
#include <libc/template/dstbias.h>
#ifdef __LOCAL_dstbias
#include <libc/local/time/__dstbias.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__dstbias, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED __LONG32_TYPE__ *__NOTHROW_NCX(__LIBDCALL __dstbias)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__dstbias))(); })
#endif /* __LOCAL_dstbias */
#endif /* !... */
#ifndef ___dstbias
#ifdef __LOCAL_dstbias
#define _dstbias __LOCAL_dstbias
#elif defined(__CRT_HAVE__dstbias)
__CSDECLARE(,__LONG32_TYPE__,_dstbias)
#define _dstbias _dstbias
#include <libc/template/dstbias.h>
#elif (defined(__CRT_HAVE___dstbias) && defined(__CRT_DOS)) || defined(__CRT_HAVE_DOS$__dstbias) || defined(__CRT_HAVE___p__dstbias)
#define _dstbias (*__dstbias())
#endif /* ... */
#endif /* !___dstbias */
#ifdef __CRT_HAVE__get_daylight
__CDECLARE(,errno_t,__NOTHROW_NCX,_get_daylight,(int *__p_result),(__p_result))
#else /* __CRT_HAVE__get_daylight */
#include <libc/template/daylight.h>
#ifdef __LOCAL_daylight
#include <libc/local/time/_get_daylight.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_daylight, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL _get_daylight)(int *__p_result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_daylight))(__p_result); })
#endif /* __LOCAL_daylight */
#endif /* !__CRT_HAVE__get_daylight */
#ifdef __CRT_HAVE__get_timezone
__CDECLARE(,errno_t,__NOTHROW_NCX,_get_timezone,(long *__p_seconds),(__p_seconds))
#else /* __CRT_HAVE__get_timezone */
#include <libc/template/timezone.h>
#ifdef __LOCAL_timezone
#include <libc/local/time/_get_timezone.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_timezone, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL _get_timezone)(long *__p_seconds) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_timezone))(__p_seconds); })
#endif /* __LOCAL_timezone */
#endif /* !__CRT_HAVE__get_timezone */
#ifdef __CRT_HAVE__get_dstbias
__CDECLARE(,errno_t,__NOTHROW_NCX,_get_dstbias,(__LONG32_TYPE__ *__p_result),(__p_result))
#else /* __CRT_HAVE__get_dstbias */
#include <libc/template/dstbias.h>
#ifdef __LOCAL_dstbias
#include <libc/local/time/_get_dstbias.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_dstbias, __FORCELOCAL __ATTR_ARTIFICIAL errno_t __NOTHROW_NCX(__LIBCCALL _get_dstbias)(__LONG32_TYPE__ *__p_result) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_dstbias))(__p_result); })
#endif /* __LOCAL_dstbias */
#endif /* !__CRT_HAVE__get_dstbias */
#ifdef __CRT_HAVE__get_tzname
__CDECLARE(__ATTR_OUT(1) __ATTR_OUT_OPT(2),errno_t,__NOTHROW_NCX,_get_tzname,(size_t *__result, char *__buf, size_t __bufsize, int __index),(__result,__buf,__bufsize,__index))
#else /* __CRT_HAVE__get_tzname */
#include <libc/template/tzname.h>
#ifdef __LOCAL_tzname
#include <libc/local/time/_get_tzname.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_get_tzname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) __ATTR_OUT_OPT(2) errno_t __NOTHROW_NCX(__LIBCCALL _get_tzname)(size_t *__result, char *__buf, size_t __bufsize, int __index) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_get_tzname))(__result, __buf, __bufsize, __index); })
#endif /* __LOCAL_tzname */
#endif /* !__CRT_HAVE__get_tzname */
#ifdef __CRT_HAVE_ctime
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,_ctime32,(__time32_t const *__timer),ctime,(__timer))
#elif defined(__CRT_HAVE__ctime32)
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,_ctime32,(__time32_t const *__timer),(__timer))
#endif /* ... */
#if defined(__CRT_HAVE_ctime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,_ctime64,(__time64_t const *__timer),ctime,(__timer))
#elif defined(__CRT_HAVE_ctime64)
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,_ctime64,(__time64_t const *__timer),ctime64,(__timer))
#elif defined(__CRT_HAVE__ctime64)
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,_ctime64,(__time64_t const *__timer),(__timer))
#else /* ... */
#include <libc/local/time/ctime64.h>
/* >> ctime(3), ctime64(3)
 * Equivalent to `asctime(localtime(timer))' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL _ctime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime64))(__timer); }
#endif /* !... */
#ifdef __CRT_HAVE_gmtime
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,_gmtime32,(__time32_t const *__timer),gmtime,(__timer))
#elif defined(__CRT_HAVE__gmtime32)
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,_gmtime32,(__time32_t const *__timer),(__timer))
#endif /* ... */
#if defined(__CRT_HAVE_gmtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,_gmtime64,(__time64_t const *__timer),gmtime,(__timer))
#elif defined(__CRT_HAVE_gmtime64)
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,_gmtime64,(__time64_t const *__timer),gmtime64,(__timer))
#elif defined(__CRT_HAVE__gmtime64)
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,_gmtime64,(__time64_t const *__timer),(__timer))
#else /* ... */
#include <libc/local/time/gmtime64.h>
/* >> gmtime(3), gmtime64(3)
 * Return  the  `struct tm'  representation  of   `*timer'
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL _gmtime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime64))(__timer); }
#endif /* !... */
#ifdef __CRT_HAVE__gmtime32_s
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
__CDECLARE(__ATTR_IN(2) __ATTR_OUT(1),errno_t,__NOTHROW_NCX,_gmtime32_s,(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time32_t const *__restrict __timer),(__tp,__timer))
#else /* __CRT_HAVE__gmtime32_s */
#include <libc/local/time/_gmtime32_s.h>
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(_gmtime32_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUT(1) errno_t __NOTHROW_NCX(__LIBCCALL _gmtime32_s)(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time32_t const *__restrict __timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_gmtime32_s))(__tp, __timer); })
#endif /* !__CRT_HAVE__gmtime32_s */
#ifdef __CRT_HAVE__gmtime64_s
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
__CDECLARE(__ATTR_IN(2) __ATTR_OUT(1),errno_t,__NOTHROW_NCX,_gmtime64_s,(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time64_t const *__restrict __timer),(__tp,__timer))
#else /* __CRT_HAVE__gmtime64_s */
#include <libc/local/time/_gmtime64_s.h>
/* >> gmtime_r(3), gmtime64_r(3)
 * Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(_gmtime64_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUT(1) errno_t __NOTHROW_NCX(__LIBCCALL _gmtime64_s)(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time64_t const *__restrict __timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_gmtime64_s))(__tp, __timer); })
#endif /* !__CRT_HAVE__gmtime64_s */
#ifdef __CRT_HAVE__localtime32_s
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
__CDECLARE(__ATTR_IN(2) __ATTR_OUT(1),errno_t,__NOTHROW_NCX,_localtime32_s,(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time32_t const *__restrict __timer),(__tp,__timer))
#else /* __CRT_HAVE__localtime32_s */
#include <libc/local/time/_localtime32_s.h>
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(_localtime32_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUT(1) errno_t __NOTHROW_NCX(__LIBCCALL _localtime32_s)(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time32_t const *__restrict __timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_localtime32_s))(__tp, __timer); })
#endif /* !__CRT_HAVE__localtime32_s */
#ifdef __CRT_HAVE__localtime64_s
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
__CDECLARE(__ATTR_IN(2) __ATTR_OUT(1),errno_t,__NOTHROW_NCX,_localtime64_s,(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time64_t const *__restrict __timer),(__tp,__timer))
#else /* __CRT_HAVE__localtime64_s */
#include <libc/local/time/_localtime64_s.h>
/* >> localtime_r(3), localtime64_r(3)
 * Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(_localtime64_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUT(1) errno_t __NOTHROW_NCX(__LIBCCALL _localtime64_s)(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time64_t const *__restrict __timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_localtime64_s))(__tp, __timer); })
#endif /* !__CRT_HAVE__localtime64_s */
#ifdef __CRT_HAVE__ctime32_s
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
__CDECLARE(__ATTR_IN(3) __ATTR_OUTS(1, 2),errno_t,__NOTHROW_NCX,_ctime32_s,(char __buf[26], __SIZE_TYPE__ __bufsize, __time32_t const *__restrict __timer),(__buf,__bufsize,__timer))
#else /* __CRT_HAVE__ctime32_s */
#include <libc/local/time/_ctime32_s.h>
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ctime32_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUTS(1, 2) errno_t __NOTHROW_NCX(__LIBCCALL _ctime32_s)(char __buf[26], __SIZE_TYPE__ __bufsize, __time32_t const *__restrict __timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ctime32_s))(__buf, __bufsize, __timer); })
#endif /* !__CRT_HAVE__ctime32_s */
#ifdef __CRT_HAVE__ctime64_s
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
__CDECLARE(__ATTR_IN(3) __ATTR_OUTS(1, 2),errno_t,__NOTHROW_NCX,_ctime64_s,(char __buf[26], __SIZE_TYPE__ __bufsize, __time64_t const *__restrict __timer),(__buf,__bufsize,__timer))
#else /* __CRT_HAVE__ctime64_s */
#include <libc/local/time/_ctime64_s.h>
/* >> ctime_r(3), ctime64_r(3)
 * Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ctime64_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUTS(1, 2) errno_t __NOTHROW_NCX(__LIBCCALL _ctime64_s)(char __buf[26], __SIZE_TYPE__ __bufsize, __time64_t const *__restrict __timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ctime64_s))(__buf, __bufsize, __timer); })
#endif /* !__CRT_HAVE__ctime64_s */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_difftime
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_difftime32,(__time32_t __time1, __time32_t __time0),difftime,(__time1,__time0))
#elif defined(__CRT_HAVE__difftime32)
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_difftime32,(__time32_t __time1, __time32_t __time0),(__time1,__time0))
#else /* ... */
#include <libc/local/time/difftime.h>
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL _difftime32)(__time32_t __time1, __time32_t __time0) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(difftime))((__time_t)__time1, (__time_t)__time0); }
#endif /* !... */
#if defined(__CRT_HAVE_difftime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,_difftime64,(__time64_t __time1, __time64_t __time0),difftime,(__time1,__time0))
#elif defined(__CRT_HAVE_difftime64)
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,_difftime64,(__time64_t __time1, __time64_t __time0),difftime64,(__time1,__time0))
#elif defined(__CRT_HAVE__difftime64)
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,_difftime64,(__time64_t __time1, __time64_t __time0),(__time1,__time0))
#elif defined(__CRT_HAVE___difftime64)
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,_difftime64,(__time64_t __time1, __time64_t __time0),__difftime64,(__time1,__time0))
#else /* ... */
#include <libc/local/time/difftime64.h>
/* >> difftime(3), difftime64(3)
 * Return the difference between `time1' and `time0' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW_NCX(__LIBCCALL _difftime64)(__time64_t __time1, __time64_t __time0) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(difftime64))(__time1, __time0); }
#endif /* !... */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE_localtime
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,_localtime32,(__time32_t const *__timer),localtime,(__timer))
#elif defined(__CRT_HAVE__localtime32)
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,_localtime32,(__time32_t const *__timer),(__timer))
#elif __SIZEOF_TIME_T__ == __SIZEOF_TIME32_T__
#include <libc/local/time/localtime.h>
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL _localtime32)(__time32_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime))((__time_t const *)__timer); }
#else /* ... */
#include <libc/local/time/_localtime32.h>
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__NAMESPACE_LOCAL_USING_OR_IMPL(_localtime32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL _localtime32)(__time32_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_localtime32))(__timer); })
#endif /* !... */
#if defined(__CRT_HAVE_localtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,_localtime64,(__time64_t const *__timer),localtime,(__timer))
#elif defined(__CRT_HAVE_localtime64)
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,_localtime64,(__time64_t const *__timer),localtime64,(__timer))
#elif defined(__CRT_HAVE__localtime64)
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,_localtime64,(__time64_t const *__timer),(__timer))
#else /* ... */
#include <libc/local/time/localtime64.h>
/* >> localtime(3), localtime64(3)
 * Return the `struct tm' representation of `*timer' in the local timezone */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct __NAMESPACE_STD_SYM tm *__NOTHROW_NCX(__LIBCCALL _localtime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime64))(__timer); }
#endif /* !... */
#ifdef __CRT_HAVE_time
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(,__time32_t,__NOTHROW_NCX,_time32,(__time32_t *__timer),time,(__timer))
#elif defined(__CRT_HAVE___time)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(,__time32_t,__NOTHROW_NCX,_time32,(__time32_t *__timer),__time,(__timer))
#elif defined(__CRT_HAVE___libc_time)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(,__time32_t,__NOTHROW_NCX,_time32,(__time32_t *__timer),__libc_time,(__timer))
#elif defined(__CRT_HAVE__time32)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CDECLARE(,__time32_t,__NOTHROW_NCX,_time32,(__time32_t *__timer),(__timer))
#elif __SIZEOF_TIME_T__ == __SIZEOF_TIME32_T__ && (defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64))
#include <libc/local/time/time.h>
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __time32_t __NOTHROW_NCX(__LIBCCALL _time32)(__time32_t *__timer) { return (__time32_t)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(time))((__time_t *)__timer); }
#elif defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64)
#include <libc/local/time/_time32.h>
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(_time32, __FORCELOCAL __ATTR_ARTIFICIAL __time32_t __NOTHROW_NCX(__LIBCCALL _time32)(__time32_t *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_time32))(__timer); })
#endif /* ... */
#if defined(__CRT_HAVE_time) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(__ATTR_OUT_OPT(1),__time64_t,__NOTHROW_NCX,_time64,(__time64_t *__timer),time,(__timer))
#elif defined(__CRT_HAVE___time) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(__ATTR_OUT_OPT(1),__time64_t,__NOTHROW_NCX,_time64,(__time64_t *__timer),__time,(__timer))
#elif defined(__CRT_HAVE___libc_time) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(__ATTR_OUT_OPT(1),__time64_t,__NOTHROW_NCX,_time64,(__time64_t *__timer),__libc_time,(__timer))
#elif defined(__CRT_HAVE_time64)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CREDIRECT(__ATTR_OUT_OPT(1),__time64_t,__NOTHROW_NCX,_time64,(__time64_t *__timer),time64,(__timer))
#elif defined(__CRT_HAVE__time64)
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__CDECLARE(__ATTR_OUT_OPT(1),__time64_t,__NOTHROW_NCX,_time64,(__time64_t *__timer),(__timer))
#elif defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/time/time64.h>
/* >> time(2), time64(2)
 * Return the current time and put it in `*timer' if `timer' is not `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(1) __time64_t __NOTHROW_NCX(__LIBCCALL _time64)(__time64_t *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(time64))(__timer); }
#endif /* ... */
#ifdef __CRT_HAVE_mktime
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time32_t,__NOTHROW_NCX,_mktime32,(struct __NAMESPACE_STD_SYM tm *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE__mktime32)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time32_t,__NOTHROW_NCX,_mktime32,(struct __NAMESPACE_STD_SYM tm *__tp),(__tp))
#elif defined(__CRT_HAVE_timelocal)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time32_t,__NOTHROW_NCX,_mktime32,(struct __NAMESPACE_STD_SYM tm *__tp),timelocal,(__tp))
#else /* ... */
#include <libc/local/time/mktime.h>
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1) __time32_t __NOTHROW_NCX(__LIBCCALL _mktime32)(struct __NAMESPACE_STD_SYM tm *__tp) { return (__time32_t)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime))(__tp); }
#endif /* !... */
#if defined(__CRT_HAVE_mktime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,_mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE_mktime64)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,_mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE__mktime64)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,_mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),(__tp))
#elif defined(__CRT_HAVE_timelocal64)
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,_mktime64,(struct __NAMESPACE_STD_SYM tm *__tp),timelocal64,(__tp))
#else /* ... */
#include <libc/local/time/mktime64.h>
/* >> mktime(3), mktime64(3)
 * Return the `time_t' representation of `tp' and normalize `tp' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1) __time64_t __NOTHROW_NCX(__LIBCCALL _mktime64)(struct __NAMESPACE_STD_SYM tm *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime64))(__tp); }
#endif /* !... */
#ifdef __CRT_HAVE_timegm
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time32_t,__NOTHROW_NCX,_mkgmtime32,(struct __NAMESPACE_STD_SYM tm *__tp),timegm,(__tp))
#elif defined(__CRT_HAVE__mkgmtime)
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time32_t,__NOTHROW_NCX,_mkgmtime32,(struct __NAMESPACE_STD_SYM tm *__tp),_mkgmtime,(__tp))
#elif defined(__CRT_HAVE__mkgmtime32)
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time32_t,__NOTHROW_NCX,_mkgmtime32,(struct __NAMESPACE_STD_SYM tm *__tp),(__tp))
#else /* ... */
#include <libc/local/time/timegm.h>
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1) __time32_t __NOTHROW_NCX(__LIBCCALL _mkgmtime32)(struct __NAMESPACE_STD_SYM tm *__tp) { return (__time32_t)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timegm))(__tp); }
#endif /* !... */
#if defined(__CRT_HAVE_timegm) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,_mkgmtime64,(struct __NAMESPACE_STD_SYM tm *__tp),timegm,(__tp))
#elif defined(__CRT_HAVE_timegm64)
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,_mkgmtime64,(struct __NAMESPACE_STD_SYM tm *__tp),timegm64,(__tp))
#elif defined(__CRT_HAVE__mkgmtime64)
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1),__time64_t,__NOTHROW_NCX,_mkgmtime64,(struct __NAMESPACE_STD_SYM tm *__tp),(__tp))
#else /* ... */
#include <libc/local/time/timegm64.h>
/* >> timegm(3), timegm64(3)
 * Like `mktime', but `tp' represents Universal Time (UTC), not local time */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INOUT(1) __time64_t __NOTHROW_NCX(__LIBCCALL _mkgmtime64)(struct __NAMESPACE_STD_SYM tm *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timegm64))(__tp); }
#endif /* !... */
#ifdef __CRT_HAVE_strftime_l
/* >> strftime_l(3)
 * Similar to `strftime(3)' but take the information from
 * the   provided  locale  and   not  the  global  locale */
__CREDIRECT(__ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_STRFTIME(3, 0) __ATTR_OUTS(1, 2),__SIZE_TYPE__,__NOTHROW_NCX,_strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),strftime_l,(__buf,__bufsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE__strftime_l)
/* >> strftime_l(3)
 * Similar to `strftime(3)' but take the information from
 * the   provided  locale  and   not  the  global  locale */
__CDECLARE(__ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_STRFTIME(3, 0) __ATTR_OUTS(1, 2),__SIZE_TYPE__,__NOTHROW_NCX,_strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),(__buf,__bufsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE___strftime_l)
/* >> strftime_l(3)
 * Similar to `strftime(3)' but take the information from
 * the   provided  locale  and   not  the  global  locale */
__CREDIRECT(__ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_STRFTIME(3, 0) __ATTR_OUTS(1, 2),__SIZE_TYPE__,__NOTHROW_NCX,_strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),__strftime_l,(__buf,__bufsize,__format,__tp,__locale))
#else /* ... */
#include <libc/local/time/strftime_l.h>
/* >> strftime_l(3)
 * Similar to `strftime(3)' but take the information from
 * the   provided  locale  and   not  the  global  locale */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_STRFTIME(3, 0) __ATTR_OUTS(1, 2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _strftime_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strftime_l))(__buf, __bufsize, __format, __tp, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE__strtime
__CDECLARE(__ATTR_OUT(1),char *,__NOTHROW_NCX,_strtime,(char __buf[9]),(__buf))
#elif defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/time/_strtime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strtime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) char *__NOTHROW_NCX(__LIBCCALL _strtime)(char __buf[9]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strtime))(__buf); })
#endif /* ... */
#ifdef __CRT_HAVE__strdate
__CDECLARE(__ATTR_OUT(1),char *,__NOTHROW_NCX,_strdate,(char __buf[9]),(__buf))
#elif defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/time/_strdate.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strdate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) char *__NOTHROW_NCX(__LIBCCALL _strdate)(char __buf[9]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strdate))(__buf); })
#endif /* ... */
#ifdef __CRT_HAVE__strtime_s
__CDECLARE(__ATTR_OUTS(1, 2),errno_t,__NOTHROW_NCX,_strtime_s,(char *__buf, size_t __bufsize),(__buf,__bufsize))
#elif defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/time/_strtime_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strtime_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) errno_t __NOTHROW_NCX(__LIBCCALL _strtime_s)(char *__buf, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strtime_s))(__buf, __bufsize); })
#endif /* ... */
#ifdef __CRT_HAVE__strdate_s
__CDECLARE(__ATTR_OUTS(1, 2),errno_t,__NOTHROW_NCX,_strdate_s,(char *__buf, size_t __bufsize),(__buf,__bufsize))
#elif defined(__CRT_HAVE__strdate) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/time/_strdate_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_strdate_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) errno_t __NOTHROW_NCX(__LIBCCALL _strdate_s)(char *__buf, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_strdate_s))(__buf, __bufsize); })
#endif /* ... */
#ifdef __CRT_HAVE_timespec_get
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_OUT(1),int,__NOTHROW_NCX,_timespec32_get,(struct __timespec32 *__ts, __STDC_INT_AS_UINT_T __base),timespec_get,(__ts,__base))
#elif defined(__CRT_HAVE__timespec32_get)
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_OUT(1),int,__NOTHROW_NCX,_timespec32_get,(struct __timespec32 *__ts, __STDC_INT_AS_UINT_T __base),(__ts,__base))
#endif /* ... */
#if defined(__CRT_HAVE_timespec_get) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,_timespec64_get,(struct timespec64 *__ts, int __base),timespec_get,(__ts,__base))
#elif defined(__CRT_HAVE_timespec_get64)
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,_timespec64_get,(struct timespec64 *__ts, int __base),timespec_get64,(__ts,__base))
#elif defined(__CRT_HAVE__timespec64_get)
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,_timespec64_get,(struct timespec64 *__ts, int __base),(__ts,__base))
#elif defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && (defined(__CRT_HAVE_clock_gettime64) || defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime))
#include <libc/local/time/timespec_get64.h>
/* >> timespec_get(3), timespec_get64(3)
 * Set `ts' to calendar time based in time base `base' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL _timespec64_get)(struct timespec64 *__ts, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timespec_get64))(__ts, __base); }
#endif /* ... */
#ifdef __CRT_HAVE_tzset
/* >> tzset(3)
 * Set time conversion information from the `$TZ' environment variable.
 * If  `$TZ'  is  not  defined,  a  locale-dependent  default  is  used */
__CREDIRECT_VOID(,__NOTHROW_NCX,_tzset,(void),tzset,())
#elif defined(__CRT_HAVE__tzset)
/* >> tzset(3)
 * Set time conversion information from the `$TZ' environment variable.
 * If  `$TZ'  is  not  defined,  a  locale-dependent  default  is  used */
__CDECLARE_VOID(,__NOTHROW_NCX,_tzset,(void),())
#endif /* ... */
#ifdef __CRT_HAVE__getsystime
__CDECLARE(__ATTR_OUT(1),unsigned int,__NOTHROW_NCX,_getsystime,(struct __NAMESPACE_STD_SYM tm *__tp),(__tp))
#elif defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday) || defined(__CRT_HAVE___libc_gettimeofday)
#include <libc/local/time/_getsystime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getsystime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) unsigned int __NOTHROW_NCX(__LIBCCALL _getsystime)(struct __NAMESPACE_STD_SYM tm *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getsystime))(__tp); })
#endif /* ... */
#ifdef __CRT_HAVE__setsystime
__CDECLARE(__ATTR_INOUT(1),unsigned int,__NOTHROW_NCX,_setsystime,(struct __NAMESPACE_STD_SYM tm *__tp, unsigned int __milliseconds),(__tp,__milliseconds))
#elif defined(__CRT_HAVE_settimeofday64) || defined(__CRT_HAVE_settimeofday) || defined(__CRT_HAVE___settimeofday) || defined(__CRT_HAVE___libc_settimeofday)
#include <libc/local/time/_setsystime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_setsystime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) unsigned int __NOTHROW_NCX(__LIBCCALL _setsystime)(struct __NAMESPACE_STD_SYM tm *__tp, unsigned int __milliseconds) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_setsystime))(__tp, __milliseconds); })
#endif /* ... */


#ifdef __USE_TIME_BITS64
#define _mkgmtime _mkgmtime64
#ifdef __USE_DOS_SLIB
#define ctime_s     _ctime64_s
#define gmtime_s    _gmtime64_s
#define localtime_s _localtime64_s
#endif /* __USE_DOS_SLIB */
#else /* __USE_TIME_BITS64 */
#define _mkgmtime _mkgmtime32
#ifdef __USE_DOS_SLIB
#define ctime_s     _ctime32_s
#define gmtime_s    _gmtime32_s
#define localtime_s _localtime32_s
#endif /* __USE_DOS_SLIB */
#endif /* !__USE_TIME_BITS64 */
#endif /* __USE_DOS */

__SYSDECL_END
#endif /* __CC__ */

#if defined(__USE_DOS) && !defined(__USE_DOS_CLEAN)
#include <corecrt_wtime.h> /* Include <wchar.h> instead */
#endif /* __USE_DOS && !__USE_DOS_CLEAN */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_TIME_H)
#include <parts/uchar/time.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_TIME_H */
#endif /* __USE_UTF */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CTIME
#undef _TIME_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CTIME */
#endif /* !_TIME_H */
