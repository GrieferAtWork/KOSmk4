/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/time.h) */
/* (#) Portability: DJGPP         (/include/time.h) */
/* (#) Portability: DragonFly BSD (/include/time.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/time.h) */
/* (#) Portability: FreeBSD       (/include/time.h) */
/* (#) Portability: GNU C Library (/time/time.h) */
/* (#) Portability: GNU Hurd      (/usr/include/time.h) */
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
/*!always_includes <bits/types/NULL.h>*/
/*!always_includes <bits/types/std_size_t.h>*/
/*!always_includes <bits/types/std_time_t.h>*/
/*!always_includes <bits/types/std_clock_t.h>*/
/*!always_includes <bits/types/size_t.h>*/
/*!always_includes <bits/types/time_t.h>*/
/*!always_includes <bits/types/clock_t.h>*/
}

%[define_ccompat_header("ctime")]
%[default:section(".text.crt{|.dos}.time")]

%[define_decl_include("<bits/crt/tm.h>": ["struct tm", "struct __NAMESPACE_STD_SYM tm"])]
%[define_decl_include("<bits/os/sigevent.h>": ["struct sigevent"])]
%[define_decl_include("<bits/os/timex.h>": ["struct timex", "struct timex64"])]

%[define_replacement(time_t    = "__time_t")]
%[define_replacement(time32_t  = __time32_t)]
%[define_replacement(time64_t  = __time64_t)]
%[define_replacement(clock_t   = __clock_t)]
%[define_replacement(pid_t     = __pid_t)]
%[define_replacement(clockid_t = __clockid_t)]
%[define_replacement(timer_t   = __timer_t)]

%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(timeval32  = __timeval32)]
%[define_replacement(timeval64  = __timeval64)]
%[define_replacement(itimerspec32 = __itimerspec32)]
%[define_replacement(itimerspec64 = __itimerspec64)]

%(auto_source){
#include "../libc/globals.h"
#include <stdlib.h>
}


%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/crt/tm.h>
)]%[insert:prefix(
#include <asm/crt/time.h>
)]%[insert:prefix(
#include <asm/os/clock.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

#ifdef __INTELLISENSE__
#include <bits/types/NULL.h>
#ifdef __USE_XOPEN2K
#include <bits/types/pid_t.h>
#endif /* __USE_XOPEN2K */
#ifdef __USE_POSIX199309
#include <bits/types/clockid_t.h>
#include <bits/types/timer_t.h>
#endif /* __USE_POSIX199309 */
#endif /* __INTELLISENSE__ */

#ifdef __USE_POSIX199309
#include <bits/os/timespec.h>
#include <bits/os/itimerspec.h>
#endif /* __USE_POSIX199309 */

#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */


/* susv4-2018: Inclusion  of  the  <time.h>  header  may  make
 *             visible all symbols from the <signal.h> header. */
#ifdef __USE_POSIX_BLOAT
#ifndef _SIGNAL_H
#include <signal.h>
#endif /* !_SIGNAL_H */
#endif /* __USE_POSIX_BLOAT */

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
}
%[insert:guarded_function(__os_sysconf = sysconf)]
%{
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
}%(c, ccompat){
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
}%{
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
}%(c, ccompat){
#ifndef __tm_defined
#define __tm_defined
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */



#ifdef __USE_POSIX199309
struct sigevent;
#endif /* __USE_POSIX199309 */

}

%[define_replacement(tm = "__NAMESPACE_STD_SYM tm")];

%[define(MSEC_PER_SEC  = __UINT16_C(1000))]
%[define(USEC_PER_MSEC = __UINT16_C(1000))]
%[define(NSEC_PER_USEC = __UINT16_C(1000))]
%[define(NSEC_PER_MSEC = __UINT32_C(1000000))]
%[define(USEC_PER_SEC  = __UINT32_C(1000000))]
%[define(NSEC_PER_SEC  = __UINT32_C(1000000000))]
%[define(FSEC_PER_SEC  = __UINT64_C(1000000000000000))]

%[define(SECONDS_PER_MINUTE   = 60)]
%[define(SECONDS_PER_HOUR     = 360)]
%[define(SECONDS_PER_DAY      = 86400)]
%[define(MINUTES_PER_HOUR     = 60)]
%[define(HOURS_PER_DAY        = 24)]
%[define(UNIX_TIME_START_YEAR = 1970)]
%[define(DAYS_PER_WEEK        = 7)]




%[define_c_language_keyword(__KOS_FIXED_CONST)];



[[ignore, nocrt, doc_alias("ctime"),             alias("ctime",       "_ctime32"),                  decl_include("<bits/types.h>"), wunused, nonnull]] char *crt_ctime32([[in]] $time32_t const *timer);
[[ignore, nocrt, doc_alias("ctime64"),           alias("ctime64",     "_ctime64", "__ctime64"),     decl_include("<bits/types.h>"), wunused, nonnull]] char *crt_ctime64([[in]] $time64_t const *timer);
[[ignore, nocrt, doc_alias("gmtime"),            alias("gmtime",      "_gmtime32"),                 decl_include("<bits/types.h>", "<bits/crt/tm.h>"), wunused, nonnull]] struct $tm *crt_gmtime32([[in]] $time32_t const *timer);
[[ignore, nocrt, doc_alias("gmtime64"),          alias("gmtime64",    "_gmtime64", "__gmtime64"),   decl_include("<bits/types.h>", "<bits/crt/tm.h>"), wunused, nonnull]] struct $tm *crt_gmtime64([[in]] $time64_t const *timer);
[[ignore, nocrt, doc_alias("gmtime_r"),          alias("gmtime_r"),                                 decl_include("<bits/types.h>", "<bits/crt/tm.h>")]] $errno_t crt_gmtime32_r([[in]] $time32_t const *__restrict timer, [[out]] struct $tm *__restrict tp);
[[ignore, nocrt, doc_alias("gmtime64_r"),        alias("gmtime64_r", "__gmtime64_r"),               decl_include("<bits/types.h>", "<bits/crt/tm.h>")]] $errno_t crt_gmtime64_r([[in]] $time64_t const *__restrict timer, [[out]] struct $tm *__restrict tp);
[[ignore, nocrt, doc_alias("gmtime_r"),          alias(               "_gmtime32_s"),               decl_include("<bits/types.h>", "<bits/crt/tm.h>")]] $errno_t crt_gmtime32_s([[out]] struct $tm *__restrict tp, [[in]] $time32_t const *__restrict timer);
[[ignore, nocrt, doc_alias("gmtime64_r"),        alias(               "_gmtime64_s"),               decl_include("<bits/types.h>", "<bits/crt/tm.h>")]] $errno_t crt_gmtime64_s([[out]] struct $tm *__restrict tp, [[in]] $time64_t const *__restrict timer);
[[ignore, nocrt, doc_alias("localtime"),         alias("localtime",   "_localtime32"),              decl_include("<bits/types.h>", "<bits/crt/tm.h>"), wunused, nonnull]] struct $tm *crt_localtime32([[in]] $time32_t const *timer);
[[ignore, nocrt, doc_alias("localtime64"),       alias("localtime64", "_localtime64", "__localtime64"), decl_include("<bits/types.h>", "<bits/crt/tm.h>"), wunused, nonnull]] struct $tm *crt_localtime64([[in]] $time64_t const *timer);
[[ignore, nocrt, doc_alias("localtime_r"),       alias("localtime_r"),                              decl_include("<bits/types.h>", "<bits/crt/tm.h>")]] $errno_t crt_localtime32_r([[in]] $time32_t const *__restrict timer, [[out]] struct $tm *__restrict tp);
[[ignore, nocrt, doc_alias("localtime64_r"),     alias("localtime64_r", "__localtime64_r"),         decl_include("<bits/types.h>", "<bits/crt/tm.h>")]] $errno_t crt_localtime64_r([[in]] $time64_t const *__restrict timer, [[out]] struct $tm *__restrict tp);
[[ignore, nocrt, doc_alias("localtime_r"),       alias(               "_localtime32_s"),            decl_include("<bits/types.h>", "<bits/crt/tm.h>")]] $errno_t crt_localtime32_s([[out]] struct $tm *__restrict tp, [[in]] $time32_t const *__restrict timer);
[[ignore, nocrt, doc_alias("localtime64_r"),     alias(               "_localtime64_s"),            decl_include("<bits/types.h>", "<bits/crt/tm.h>")]] $errno_t crt_localtime64_s([[out]] struct $tm *__restrict tp, [[in]] $time64_t const *__restrict timer);
[[ignore, nocrt, doc_alias("ctime_r"),           alias("ctime_r"),                                  decl_include("<bits/types.h>")]] $errno_t crt_ctime32_r([[in]] $time32_t const *__restrict timer, [[out]] char buf[26]);
[[ignore, nocrt, doc_alias("ctime64_r"),         alias("ctime64_r",   "__ctime64_r"),               decl_include("<bits/types.h>")]] $errno_t crt_ctime64_r([[in]] $time64_t const *__restrict timer, [[out]] char buf[26]);
[[ignore, nocrt, doc_alias("ctime_r"),           alias(               "_ctime32_s"),                decl_include("<bits/types.h>")]] $errno_t crt_ctime32_s([[out(? <= bufsize)]] char buf[26], $size_t bufsize, [[in]] $time32_t const *__restrict timer);
[[ignore, nocrt, doc_alias("ctime64_r"),         alias(               "_ctime64_s"),                decl_include("<bits/types.h>")]] $errno_t crt_ctime64_s([[out(? <= bufsize)]] char buf[26], $size_t bufsize, [[in]] $time64_t const *__restrict timer);
[[ignore, nocrt, doc_alias("difftime"),          alias("difftime",    "_difftime32"),               decl_include("<bits/types.h>"), const, wunused, nothrow]] double crt_difftime32($time32_t time1, $time32_t time0);
[[ignore, nocrt, doc_alias("difftime64"),        alias("difftime64",  "_difftime64", "__difftime64"), decl_include("<bits/types.h>"), const, wunused, nothrow]] double crt_difftime64($time64_t time1, $time64_t time0);
[[ignore, nocrt, doc_alias("time"),              alias("time", "__time", "__libc_time", "_time32"), decl_include("<bits/types.h>")]] $time32_t crt_time32([[out_opt]] $time32_t *timer);
[[ignore, nocrt, doc_alias("time64"),            alias("time64",      "_time64", "__time64"),       decl_include("<bits/types.h>")]] $time64_t crt_time64([[out_opt]] $time64_t *timer);
[[ignore, nocrt, doc_alias("mktime"),            alias("mktime", "timelocal", "_mktime32"),         decl_include("<bits/types.h>", "<features.h>", "<bits/crt/tm.h>"), pure, wunused]] $time32_t crt_mktime32([[inout]] struct $tm *tp);
[[ignore, nocrt, doc_alias("mktime64"),          alias("mktime64", "timelocal64", "_mktime64", "__mktime64"), decl_include("<bits/types.h>", "<features.h>", "<bits/crt/tm.h>"), pure, wunused]] $time64_t crt_mktime64([[inout]] struct $tm *tp);
[[ignore, nocrt, doc_alias("timegm"),            alias("timegm",      "_mkgmtime", "_mkgmtime32"),  decl_include("<bits/types.h>", "<features.h>", "<bits/crt/tm.h>"), pure, wunused]] $time32_t crt_timegm32([[inout]] struct $tm *tp);
[[ignore, nocrt, doc_alias("mktime64"),          alias("timegm64",    "_mkgmtime64", "__timegm64"), decl_include("<bits/types.h>", "<features.h>", "<bits/crt/tm.h>"), pure, wunused]] $time64_t crt_timegm64([[inout]] struct $tm *tp);
[[ignore, nocrt, doc_alias("timespec_get"),      alias("timespec_get", "_timespec32_get"), wunused, decl_include("<features.h>", "<bits/os/timespec.h>")]] int crt_timespec32_get([[out]] struct __timespec32 *ts, int base);
[[ignore, nocrt, doc_alias("timespec_get64"),    alias("timespec_get64", "_timespec64_get", "__timespec_get64"), wunused, decl_include("<features.h>", "<bits/os/timespec.h>")]] int crt_timespec64_get([[out]] struct __timespec64 *ts, int base);
[[ignore, nocrt, doc_alias("timespec_getres"),   alias("timespec_getres", "_timespec32_getres"), pure, wunused, decl_include("<features.h>", "<bits/os/timespec.h>")]] int crt_timespec32_getres([[out]] struct __timespec32 *ts, int base);
[[ignore, nocrt, doc_alias("timespec_getres64"), alias("timespec_getres64", "_timespec64_getres", "__timespec_getres64"), pure, wunused, decl_include("<features.h>", "<bits/os/timespec.h>")]] int crt_timespec64_getres([[out]] struct __timespec64 *ts, int base);
[[ignore, nocrt, doc_alias("stime"),             alias("stime", "__stime", "__libc_stime"),         decl_include("<bits/types.h>")]] int crt_stime32([[in]] $time32_t const *when);
[[ignore, nocrt, doc_alias("stime64"),           alias("stime64"),                                  decl_include("<bits/types.h>")]] int crt_stime64([[in]] $time64_t const *when);





[[ignore, nocrt, doc_alias("asctime_s"), alias("asctime_s")]]
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
$errno_t crt_asctime_s([[out(? <= buflen)]] char *__restrict buf, size_t buflen,
                       [[in]] struct $tm const *__restrict tp);


%[define(DEFINE_TIME_MONTH_NUMDAYS =
@@pp_ifndef ____TIME_MONTH_NUMDAYS_DEFINED@@
#define ____TIME_MONTH_NUMDAYS_DEFINED 1
@@push_namespace(local)@@
__LOCAL_LIBC_CONST_DATA(__time_month_numdays)
__UINT8_TYPE__ const __time_month_numdays[2][12] = {
	{ 30, 31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31 },
	{ 30, 31, 29, 31, 30, 31, 30, 31, 30, 31, 30, 31 }
};
@@pop_namespace@@
@@pp_endif@@
)]


%[define(DEFINE_TIME_MONTHSTART_YDAY =
@@pp_ifndef ____TIME_MONTHSTART_YDAY_DEFINED@@
#define ____TIME_MONTHSTART_YDAY_DEFINED 1
@@push_namespace(local)@@
__LOCAL_LIBC_CONST_DATA(__time_monthstart_yday)
__UINT16_TYPE__ const __time_monthstart_yday[2][13] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};
@@pop_namespace@@
@@pp_endif@@
)]




[[static]]
[[impl_prefix(DEFINE_TIME_MONTH_NUMDAYS)]]
[[impl_prefix(DEFINE_TIME_MONTHSTART_YDAY)]]
[[impl_prefix(DEFINE_ISLEAP)]]
//[[impl_prefix(DEFINE_DAYSTOYEARS)]]
[[impl_prefix(DEFINE_YEARSTODAYS)]]
[[decl_include("<bits/crt/tm.h>")]]
[[impl_include("<bits/crt/tm.h>")]]
[[nonnull]]
struct $tm *normalize_struct_tm([[inout]] struct $tm *__restrict tp) {
	/* Normalize seconds. */
	if (tp->@tm_sec@ < 0) {
		unsigned int delta;
		delta = ((unsigned int)-tp->@tm_sec@ + 59) / 60;
		tp->@tm_min@ -= delta;
		tp->@tm_sec@ += delta * 60;
	} else if (tp->@tm_sec@ > 59) {
		unsigned int delta;
		delta = (unsigned int)tp->@tm_sec@ / 60;
		tp->@tm_min@ += delta;
		tp->@tm_sec@ -= delta * 60;
	}

	/* Normalize minutes. */
	if (tp->@tm_min@ < 0) {
		unsigned int delta;
		delta = ((unsigned int)-tp->@tm_min@ + 59) / 60;
		tp->@tm_hour@ -= delta;
		tp->@tm_min@ += delta * 60;
	} else if (tp->@tm_min@ > 59) {
		unsigned int delta;
		delta = (unsigned int)tp->@tm_min@ / 60;
		tp->@tm_hour@ += delta;
		tp->@tm_min@ -= delta * 60;
	}

	/* Normalize hours. */
	if (tp->@tm_hour@ < 0) {
		unsigned int delta;
		delta = ((unsigned int)-tp->@tm_sec@ + 23) / 24;
		tp->@tm_mday@ -= delta;
		tp->@tm_hour@ += delta * 24;
	} else if (tp->@tm_hour@ > 23) {
		unsigned int delta;
		delta = (unsigned int)tp->@tm_hour@ / 24;
		tp->@tm_mday@ += delta;
		tp->@tm_hour@ -= delta * 24;
	}

	for (;;) {
		/* Normalize month. */
		if (tp->@tm_mon@ < 0) {
			unsigned int delta;
			delta = ((unsigned int)-tp->@tm_mon@ + 11) / 12;
			tp->@tm_year@ -= delta;
			tp->@tm_mon@ += delta * 12;
		} else if (tp->@tm_mon@ > 11) {
			unsigned int delta;
			delta = (unsigned int)tp->@tm_mon@ / 12;
			tp->@tm_year@ += delta;
			tp->@tm_mon@ -= delta * 12;
		}

		/* Normalize day-of-the-month.
		 * Note that because of February (and leap years), we can only adjust by 1 month every time. */
		if (tp->@tm_mday@ < 1) {
			--tp->@tm_mon@;
			COMPILER_BARRIER(); /* Prevent GCC warning about sign stuff */
			if (tp->@tm_mon@ < 0) {
				tp->@tm_mon@ = 11;
				--tp->@tm_year@;
			}
			tp->@tm_mday@ += __NAMESPACE_LOCAL_SYM __time_month_numdays[__isleap(1900 + tp->@tm_year@)][tp->@tm_mon@];
			continue;
		} else {
			unsigned int current_month_days;
			current_month_days = __NAMESPACE_LOCAL_SYM __time_month_numdays[__isleap(1900 + tp->@tm_year@)][tp->@tm_mon@];
			if ((unsigned int)(tp->@tm_mday@ - 1) >= current_month_days) {
				tp->@tm_mday@ -= current_month_days;
				++tp->@tm_mon@;
				continue;
			}
		}
		break;
	}

	/* Figure out the year-day. */
	tp->@tm_yday@ = __NAMESPACE_LOCAL_SYM __time_monthstart_yday[__isleap(1900 + tp->@tm_year@)][tp->@tm_mon@];
	tp->@tm_yday@ += tp->@tm_mday@;

	/* Figure out the week-day. */
	{
		uint64_t total_days;
		total_days = __yearstodays(1900 + tp->@tm_year@);
		total_days += tp->@tm_yday@;
		tp->@tm_wday@ = (int)(total_days % DAYS_PER_WEEK);
	}

	/* Figure out if daylight savings time is currently on. */
	/* found here: "http://stackoverflow.com/questions/5590429/calculating-daylight-savings-time-from-only-date" */
	if (tp->@tm_mon@ < 2 || tp->@tm_mon@ > 10) {
		//January, February, and December are out.
		tp->@tm_isdst@ = 0;
	} else if (tp->@tm_mon@ > 2 && tp->@tm_mon@ < 10) {
		//April to October are in
		tp->@tm_isdst@ = 1;
	} else {
		int previousSunday;
		previousSunday = tp->@tm_mday@ - tp->@tm_wday@;
		if (tp->@tm_mon@ == 2) {
			//In march, we are DST if our previous Sunday was on or after the 8th.
			tp->@tm_isdst@ = previousSunday >= 8;
		} else {
			//In November we must be before the first Sunday to be dst.
			//That means the  previous Sunday must  be before the  1st.
			tp->@tm_isdst@ = previousSunday <= 0;
		}
	}
	return tp;
}






%[insert:std]

@@>> clock(3)
@@Time used by the program so  far (user time + system  time)
@@The `result / CLOCKS_PER_SECOND' is program time in seconds
[[std, wunused, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/clock.h>")]]
[[requires((defined(__CLOCK_PROCESS_CPUTIME_ID) && $has_function(clock_gettime64)) ||
           $has_function(times))]]
[[impl_include("<bits/os/timespec.h>", "<bits/os/tms.h>", "<hybrid/__overflow.h>")]]
clock_t clock() {
	clock_t result;
@@pp_if defined(__CLOCK_PROCESS_CPUTIME_ID) && $has_function(clock_gettime64)@@
	struct timespec64 ts;
	if unlikely(clock_gettime64(__CLOCK_PROCESS_CPUTIME_ID, &ts))
		return -1;
	__STATIC_IF((clock_t)-1 < 0) {
		if (__hybrid_overflow_scast(ts.@tv_sec@, &result))
			goto overflow;
		if (__hybrid_overflow_smul(result, __CLOCKS_PER_SEC, &result))
			goto overflow;
		if (__hybrid_overflow_sadd(result, ts.@tv_nsec@ / (1000000000 / __CLOCKS_PER_SEC), &result))
			goto overflow;
	} __STATIC_ELSE((clock_t)-1 < 0) {
		if (__hybrid_overflow_ucast(ts.@tv_sec@, &result))
			goto overflow;
		if (__hybrid_overflow_umul(result, __CLOCKS_PER_SEC, &result))
			goto overflow;
		if (__hybrid_overflow_uadd(result, ts.@tv_nsec@ / (1000000000 / __CLOCKS_PER_SEC), &result))
			goto overflow;
	}
@@pp_else@@
	struct tms ts;
	if unlikely(times(&ts))
		return -1;
	__STATIC_IF((clock_t)-1 < 0) {
		if (__hybrid_overflow_scast(ts.@tms_utime@, &result))
			goto overflow;
		if (__hybrid_overflow_sadd(result, ts.@tms_stime@, &result))
			goto overflow;
	} __STATIC_ELSE((clock_t)-1 < 0) {
		if (__hybrid_overflow_ucast(ts.@tms_utime@, &result))
			goto overflow;
		if (__hybrid_overflow_uadd(result, ts.@tms_stime@, &result))
			goto overflow;
	}
@@pp_endif@@
	return result;
overflow:
	return (clock_t)-1;
}

@@>> time(2), time64(2)
@@Return the current time and put it in `*timer' if `timer' is not `NULL'
[[std, decl_include("<bits/types.h>"), no_crt_self_import, export_as("__time", "__libc_time"), dos_only_export_as("_time32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("time", "__time", "__libc_time", "_time32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("time64", "_time64", "__time64")]]
[[userimpl, requires($has_function(crt_time32) || $has_function(time64))]]
time_t time([[out_opt]] time_t *timer) {
@@pp_if $has_function(crt_time32)@@
	time32_t tm32 = crt_time32(NULL);
	if (timer)
		*timer = (time_t)tm32;
	return (time_t)tm32;
@@pp_else@@
	time64_t tm64 = time64(NULL);
	if (timer)
		*timer = (time_t)tm64;
	return (time_t)tm64;
@@pp_endif@@
}


%(std)#ifndef __NO_FPU
@@>> difftime(3), difftime64(3)
@@Return the difference between `time1' and `time0'
[[const, nothrow, wunused, std, guard, decl_include("<bits/types.h>"), no_crt_self_import, dos_only_export_as("_difftime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("difftime", "_difftime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("difftime64", "_difftime64", "__difftime64")]]
double difftime(time_t time1, time_t time0) {
@@pp_if $has_function(crt_difftime32) && !defined(__BUILDING_LIBC)@@
	return crt_difftime32((time32_t)time1, (time32_t)time0);
@@pp_elif $has_function(difftime64) && !defined(__BUILDING_LIBC)@@
	return difftime64((time32_t)time1, (time32_t)time0);
@@pp_else@@
	return time1 > time0 ? time1 - time0 : time0 - time1;
@@pp_endif@@
}
%(std)#endif /* !__NO_FPU */



@@>> mktime(3), mktime64(3)
@@Return the `time_t' representation of `tp' and normalize `tp'
[[pure, wunused, std, decl_include("<features.h>", "<bits/types.h>", "<bits/crt/tm.h>")]]
[[no_crt_self_import, dos_only_export_as("_mktime32"), export_as("timelocal")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("mktime", "timelocal")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("mktime64", "timelocal64")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("_mktime64", "__mktime64")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("_mktime32")]]
[[requires_function(timegm)]]
time_t mktime([[inout]] struct $tm *tp) {
	/* TODO: Support for localtime? */
	return timegm(tp);
}



@@>> ctime(3), ctime64(3)
@@Equivalent to `asctime(localtime(timer))'
[[std, wunused, decl_include("<bits/types.h>"), no_crt_self_import, dos_only_export_as("_ctime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ctime", "_ctime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ctime64", "_ctime64", "__ctime64")]]
[[nonnull]] char *ctime([[in]] time_t const *timer) {
@@pp_if $has_function(ctime64) && !defined(__BUILDING_LIBC)@@
	time64_t tm64 = (time64_t)*timer;
	return ctime64(&tm64);
@@pp_elif $has_function(crt_ctime32) && !defined(__BUILDING_LIBC)@@
	time32_t tm32 = (time32_t)*timer;
	return crt_ctime32(&tm32);
@@pp_else@@
	@@static char ctime_buf[26] = {0}@@
	return ctime_r(timer, ctime_buf);
@@pp_endif@@
}


@@>> gmtime(3), gmtime64(3)
@@Return  the  `struct tm'  representation  of   `*timer'
@@in Universal Coordinated Time (aka Greenwich Mean Time)
[[std, wunused, decl_include("<bits/types.h>", "<bits/crt/tm.h>"), no_crt_self_import, dos_only_export_as("_gmtime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("gmtime", "_gmtime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("gmtime64", "_gmtime64", "__gmtime64")]]
[[nonnull]] struct $tm *gmtime([[in]] time_t const *timer) {
@@pp_if $has_function(gmtime64) && !defined(__BUILDING_LIBC)@@
	time64_t tm64 = (time64_t)*timer;
	return gmtime64(&tm64);
@@pp_elif $has_function(crt_gmtime32) && !defined(__BUILDING_LIBC)@@
	time32_t tm32 = (time32_t)*timer;
	return crt_gmtime32(&tm32);
@@pp_else@@
	@@static struct tm tmbuf = {0}@@
	return gmtime_r(timer, &tmbuf);
@@pp_endif@@
}


@@>> localtime(3), localtime64(3)
@@Return the `struct tm' representation of `*timer' in the local timezone
[[std, wunused, decl_include("<bits/types.h>", "<bits/crt/tm.h>"), no_crt_self_import, dos_only_export_as("_localtime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("localtime", "_localtime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("localtime64", "_localtime64", "__localtime64")]]
[[nonnull]] struct $tm *localtime([[in]] time_t const *timer) {
@@pp_if $has_function(localtime64) && !defined(__BUILDING_LIBC)@@
	time64_t tm64 = (time64_t)*timer;
	return localtime64(&tm64);
@@pp_elif $has_function(crt_localtime32) && !defined(__BUILDING_LIBC)@@
	time32_t tm32 = (time32_t)*timer;
	return crt_localtime32(&tm32);
@@pp_else@@
	@@static struct tm tmbuf = {0}@@
	return localtime_r(timer, &tmbuf);
@@pp_endif@@
}


[[decl_include("<bits/crt/tm.h>", "<hybrid/typecore.h>"), doc_alias("strftime_l")]]
[[ignore, nocrt, alias("strftime_l", "_strftime_l", "__strftime_l")]]
$size_t crt_strftime_l([[out(return <= bufsize)]] char *__restrict buf, $size_t bufsize,
                       [[in, format("strftime")]] char const *__restrict format,
                       [[in]] struct $tm const *__restrict tp,
                       $locale_t locale);


@@>> strftime(3)
@@Format `tp' into `s' according to `format'.
@@Write no more than `maxsize' characters and return the number
@@of characters  written, or  0 if  it would  exceed  `maxsize'
[[std, decl_include("<bits/crt/tm.h>", "<hybrid/typecore.h>"), crtbuiltin, alias("_Strftime")]]
size_t strftime([[out(? <= bufsize)]] char *__restrict buf, size_t bufsize,
                [[in, format("strftime")]] char const *__restrict format,
                [[in]] struct $tm const *__restrict tp) {
@@pp_if $has_function(crt_strftime_l) && !defined(__BUILDING_LIBC)@@
	return crt_strftime_l(buf, bufsize, format, tp, NULL);
@@pp_else@@
	/* TODO */
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)tp;
	COMPILER_IMPURE();
	return 0;
@@pp_endif@@
}

@@>> asctime(3)
@@Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
@@that is  the  representation  of  `tp'  in  this  format
[[std, wunused, decl_include("<bits/crt/tm.h>")]]
[[nonnull]] char *asctime([[in]] struct $tm const *tp) {
	@@static char ctime_buf[26] = {0}@@
	return asctime_r(tp, ctime_buf);
}

%(std)#ifdef __USE_ISOC11
@@>> asctime_s(3)
[[std, guard, impl_include("<libc/errno.h>")]]
[[decl_include("<bits/crt/tm.h>", "<bits/types.h>")]]
$errno_t asctime_s([[out(? <= buflen)]] char *__restrict buf, size_t buflen,
                   [[in]] struct $tm const *__restrict tp) {
	if (buflen < 26)
		return __ERANGE;
	asctime_r(tp, buf);
	return 0;
}
%(std)#endif /* __USE_ISOC11 */




%#ifdef __USE_TIME64
[[decl_include("<bits/types.h>")]]
[[preferred_time64_variant_of(time), doc_alias("time")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__time", "__libc_time")]]
[[dos_only_export_alias("_time64"), time64_export_alias("__time64")]]
[[userimpl, requires_function(crt_time32)]]
$time64_t time64([[out_opt]] $time64_t *timer) {
	time32_t tm32 = crt_time32(NULL);
	if (timer)
		*timer = (time64_t)tm32;
	return (time64_t)tm32;
}

%#ifndef __NO_FPU
[[const, nothrow, wunused, guard, decl_include("<bits/types.h>")]]
[[preferred_time64_variant_of(difftime), doc_alias("difftime")]]
[[dos_only_export_alias("_difftime64"), time64_export_alias("__difftime64")]]
double difftime64($time64_t time1, $time64_t time0) {
@@pp_if $has_function(crt_difftime32) && !defined(__BUILDING_LIBC)@@
	return crt_difftime32((time32_t)time1, (time32_t)time0);
@@pp_else@@
	return time1 > time0 ? time1 - time0 : time0 - time1;
@@pp_endif@@
}
%#endif /* !__NO_FPU */



[[pure, wunused, decl_include("<bits/types.h>", "<features.h>")]]
[[preferred_time64_variant_of(mktime), doc_alias("mktime")]]
[[decl_include("<bits/crt/tm.h>")]]
[[requires_function(timegm64)]]
[[time64_export_alias("timelocal64", "__mktime64")]]
[[dos_only_export_alias("_mktime64")]]
$time64_t mktime64([[inout]] struct $tm *tp) {
	/* TODO: Support for localtime? */
	return timegm64(tp);
}

[[wunused, decl_include("<bits/types.h>")]]
[[preferred_time64_variant_of(ctime), doc_alias("ctime")]]
[[time64_export_alias("__ctime64")]]
[[dos_only_export_alias("_ctime64")]]
[[nonnull]] char *ctime64([[in]] $time64_t const *timer) {
@@pp_if $has_function(crt_ctime32) && !defined(__BUILDING_LIBC)@@
	time32_t tm32 = (time32_t)*timer;
	return crt_ctime32(&tm32);
@@pp_else@@
	@@static char ctime_buf[26] = {0}@@
	return ctime64_r(timer, ctime_buf);
@@pp_endif@@
}

[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[preferred_time64_variant_of(gmtime), doc_alias("gmtime")]]
[[time64_export_alias("__gmtime64")]]
[[wunused, dos_only_export_alias("_gmtime64")]]
[[nonnull]] struct $tm *gmtime64([[in]] $time64_t const *timer) {
@@pp_if $has_function(crt_gmtime32) && !defined(__BUILDING_LIBC)@@
	time32_t tm32 = (time32_t)*timer;
	return crt_gmtime32(&tm32);
@@pp_else@@
	@@static struct tm tmbuf = {0}@@
	return gmtime64_r(timer, &tmbuf);
@@pp_endif@@
}


[[wunused, decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[preferred_time64_variant_of(localtime), doc_alias("localtime")]]
[[dos_only_export_alias("_localtime64")]]
[[time64_export_alias("__localtime64")]]
[[nonnull]] struct $tm *localtime64([[in]] $time64_t const *timer) {
@@pp_if $has_function(crt_localtime32) && !defined(__BUILDING_LIBC)@@
	time32_t tm32 = (time32_t)*timer;
	return crt_localtime32(&tm32);
@@pp_else@@
	@@static struct tm tmbuf = {0}@@
	return localtime64_r(timer, &tmbuf);
@@pp_endif@@
}

%#endif /* __USE_TIME64 */

%{



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

}


%{
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
}

@@>> tzset(3)
@@Set time conversion information from the `$TZ' environment variable.
@@If  `$TZ'  is  not  defined,  a  locale-dependent  default  is  used
[[dos_only_export_alias("_tzset")]]
[[export_as("__tzset")]] /* From Glibc 2.0.4 */
void tzset();
%#endif /* __USE_POSIX */

%
%{
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
}


%
%#ifdef __USE_MISC

@@>> stime(2), stime64(2)
@@Set the system time to `*when'. This call is restricted to the superuser
[[guard, decl_include("<bits/types.h>"), no_crt_self_import, export_as("__stime", "__libc_stime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("stime", "__stime", "__libc_stime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("stime64")]]
[[userimpl, requires($has_function(crt_stime32) || $has_function(stime64))]]
int stime([[in]] $time_t const *when) {
@@pp_if $has_function(crt_stime32)@@
	time32_t when32 = (time32_t)*when;
	return crt_stime32(&when32);
@@pp_else@@
	time64_t when64 = (time64_t)*when;
	return stime64(&when64);
@@pp_endif@@
}

@@>> timegm(3), timegm64(3)
@@Like `mktime', but `tp' represents Universal Time (UTC), not local time
[[decl_include("<bits/types.h>"), no_crt_self_import, dos_only_export_as("_mkgmtime", "_mkgmtime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timegm", "_mkgmtime", "_mkgmtime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timegm64", "_mkgmtime64", "__timegm64")]]
[[pure, wunused, decl_include("<bits/crt/tm.h>"), impl_prefix(DEFINE_YEARSTODAYS), impl_include("<libc/errno.h>")]]
$time_t timegm([[inout]] struct $tm *tp) {
	time64_t result;
@@pp_if !defined(__BUILDING_LIBC) || __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__@@
	result = timegm64(tp);
@@pp_else@@
	/* Normalize `tp' */
	tp = normalize_struct_tm(tp);
	/* Calculate current time. */
	result = __yearstodays(tp->@tm_year@) - __yearstodays(UNIX_TIME_START_YEAR);
	result += tp->@tm_yday@;
	result *= SECONDS_PER_DAY;
	result += tp->@tm_hour@ * SECONDS_PER_HOUR;
	result += tp->@tm_min@ * SECONDS_PER_MINUTE;
	result += tp->@tm_sec@;
@@pp_endif@@

	/* EOVERFLOW if result gets truncated */
@@pp_if __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__@@
	if ((time64_t)(time_t)result != result) {
@@pp_ifdef EOVERFLOW@@
		return (time_t)__libc_seterrno(EOVERFLOW);
@@pp_else@@
		return (time_t)__libc_seterrno(1);
@@pp_endif@@
	}
@@pp_endif@@

	return (time_t)result;
}

@@>> timelocal(3), timelocal64(3)
@@Another   name   for   `mktime'
[[pure, wunused, decl_include("<bits/types.h>", "<features.h>", "<bits/crt/tm.h>")]]
$time_t timelocal([[inout]] struct $tm *tp) = mktime;


%[define(DEFINE_ISLEAP =
@@pp_ifndef __isleap@@
#define __isleap(year) ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
@@pp_endif@@
)]

%[define(DEFINE_DAYSTOYEARS =
@@pp_ifndef __daystoyears@@
#define __daystoyears(n_days) ((400 * ((n_days) + 1)) / 146097)
@@pp_endif@@
)]

%[define(DEFINE_YEARSTODAYS =
@@pp_ifndef __yearstodays@@
#define __yearstodays(n_years) (((146097 * (n_years)) / 400) /*-1*/) /* rounding error? */
@@pp_endif@@
)]



@@>> dysize(3)
@@Return the number of days in YEAR
[[decl_include("<features.h>")]]
[[const, wunused, nothrow, impl_prefix(DEFINE_ISLEAP)]]
int dysize(__STDC_INT_AS_UINT_T year) {
	return __isleap(year) ? 366 : 365;
}

%
%#ifdef __USE_TIME64
[[decl_include("<bits/types.h>")]]
[[preferred_time64_variant_of(stime), doc_alias("stime")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__stime", "__libc_stime")]]
[[userimpl, requires_function(crt_stime32)]]
int stime64([[in]] $time64_t const *when) {
	time32_t when32 = (time32_t)*when;
	return crt_stime32(&when32);
}

[[pure, wunused, decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[preferred_time64_variant_of(timegm), doc_alias("timegm")]]
[[time64_export_alias("__timegm64")]]
[[dos_only_export_alias("_mkgmtime64"), impl_prefix(DEFINE_YEARSTODAYS)]]
$time64_t timegm64([[inout]] struct $tm *tp) {
@@pp_if !defined(__BUILDING_LIBC) && $has_function(crt_timegm32)@@
	return (time64_t)crt_timegm32(tp);
@@pp_else@@
	time64_t result;
	/* Normalize `tp' */
	tp = normalize_struct_tm(tp);
	/* Calculate current time. */
	result = __yearstodays(tp->@tm_year@) - __yearstodays(UNIX_TIME_START_YEAR);
	result += tp->@tm_yday@;
	result *= SECONDS_PER_DAY;
	result += tp->@tm_hour@ * SECONDS_PER_HOUR;
	result += tp->@tm_min@ * SECONDS_PER_MINUTE;
	result += tp->@tm_sec@;
	return result;
@@pp_endif@@
}

[[doc_alias("timelocal")]]
timelocal64(*) = mktime64;
%#endif /* __USE_TIME64 */
%#endif /* __USE_MISC */




%
%#ifdef __USE_POSIX199309

[[cp, ignore, doc_alias("nanosleep"), decl_include("<bits/os/timespec.h>")]]
[[nocrt, alias("nanosleep", "__nanosleep", "__libc_nanosleep")]]
int nanosleep32([[in]] struct $timespec32 const *requested_time,
                [[out_opt]] struct $timespec32 *remaining);

@@>> nanosleep(2), nanosleep64(2)
@@Pause execution for a number of nanoseconds
@@@return: 0 : Success
@@@return: -1: [errno=EINTR]  System call was interrupted (if non-NULL, `*remaining' holds the amount of time not slept)
@@@return: -1: [errno=EINVAL] Invalid `requested_time->tv_nsec'
[[cp, decl_include("<bits/os/timespec.h>"), no_crt_self_import, export_as("__nanosleep", "__libc_nanosleep")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("nanosleep", "__nanosleep", "__libc_nanosleep")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("nanosleep64", "__nanosleep64")]]
[[userimpl, requires($has_function(nanosleep32) || $has_function(nanosleep64))]]
[[export_as("__libc_nanosleep")]] /* From Glibc 2.3.2 */
[[impl_include("<bits/os/timespec.h>")]]
int nanosleep([[in]] struct timespec const *requested_time,
              [[out_opt]] struct timespec *remaining) {
@@pp_if $has_function(nanosleep32)@@
	int result;
	struct timespec32 req32, rem32;
	req32.tv_sec  = (time32_t)requested_time->tv_sec;
	req32.tv_nsec = requested_time->tv_nsec;
	result = nanosleep32(&req32, &rem32);
	if (result == 0 && remaining) {
		remaining->tv_sec  = (time64_t)rem32.tv_sec;
		remaining->tv_nsec = rem32.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct timespec64 req64, rem64;
	req64.tv_sec  = (time64_t)requested_time->tv_sec;
	req64.tv_nsec = requested_time->tv_nsec;
	result = nanosleep64(&req64, &rem64);
	if (result == 0 && remaining) {
		remaining->tv_sec  = (time32_t)rem64.tv_sec;
		remaining->tv_nsec = rem64.tv_nsec;
	}
	return result;
@@pp_endif@@
}

[[doc_alias("clock_getres"), decl_include("<bits/os/timespec.h>")]]
[[ignore, nocrt, alias("clock_getres", "__clock_getres")]]
int clock_getres32(clockid_t clock_id, [[out]] struct $timespec32 *res);

@@>> clock_getres(2), clock_getres64(2)
@@Get resolution of clock `clock_id' in `*res'
[[decl_include("<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_getres", "__clock_getres")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_getres64", "__clock_getres64")]]
[[userimpl, requires($has_function(clock_getres32) || $has_function(clock_getres64))]]
[[export_as("__clock_getres")]]
[[impl_include("<bits/os/timespec.h>")]]
int clock_getres(clockid_t clock_id, [[out]] struct timespec *res) {
@@pp_if $has_function(clock_getres32)@@
	int result;
	struct timespec32 res32;
	result = clock_getres32(clock_id, &res32);
	if (result == 0) {
		res->tv_sec  = (time64_t)res32.tv_sec;
		res->tv_nsec = res32.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct timespec64 res64;
	result = clock_getres64(clock_id, &res64);
	if (result == 0) {
		res->tv_sec  = (time32_t)res64.tv_sec;
		res->tv_nsec = res64.tv_nsec;
	}
	return result;
@@pp_endif@@
}

[[decl_include("<bits/os/timespec.h>")]]
[[doc_alias("clock_gettime"), ignore, nocrt, alias("clock_gettime", "__clock_gettime")]]
int clock_gettime32(clockid_t clock_id, [[out]] struct $timespec32 *tp);

@@>> clock_gettime(2), clock_gettime64(2)
@@Get current value of clock `clock_id' and store it in `tp'
[[decl_include("<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_gettime", "__clock_gettime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_gettime64", "__clock_gettime64")]]
[[userimpl, requires($has_function(clock_gettime32) || $has_function(clock_gettime64))]]
[[export_as("__clock_gettime")]]
[[impl_include("<bits/os/timespec.h>")]]
int clock_gettime(clockid_t clock_id, [[out]] struct timespec *tp) {
@@pp_if $has_function(clock_gettime32)@@
	int result;
	struct timespec32 res32;
	result = clock_gettime32(clock_id, &res32);
	if (result == 0) {
		tp->tv_sec  = (time64_t)res32.tv_sec;
		tp->tv_nsec = res32.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct timespec64 res64;
	result = clock_gettime64(clock_id, &res64);
	if (result == 0) {
		tp->tv_sec  = (time32_t)res64.tv_sec;
		tp->tv_nsec = res64.tv_nsec;
	}
	return result;
@@pp_endif@@
}



[[ignore, nocrt, decl_include("<bits/os/timespec.h>")]]
[[doc_alias("clock_settime"), alias("clock_settime", "__clock_settime")]]
int clock_settime32(clockid_t clock_id, [[in]] struct $timespec32 const *tp);

@@>> clock_settime(2), clock_settime64(2)
@@Set  clock  `clock_id'  to  value  `tp'
[[decl_include("<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_settime", "__clock_settime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_settime64", "__clock_settime64")]]
[[userimpl, requires($has_function(clock_settime32) || $has_function(clock_settime64))]]
[[export_as("__clock_settime")]]
[[impl_include("<bits/os/timespec.h>")]]
int clock_settime(clockid_t clock_id, [[in]] struct timespec const *tp) {
@@pp_if $has_function(clock_settime32)@@
	struct timespec32 tp32;
	tp32.tv_sec  = (time32_t)tp->tv_sec;
	tp32.tv_nsec = tp->tv_nsec;
	return clock_settime32(clock_id, &tp32);
@@pp_else@@
	struct timespec64 tp64;
	tp64.tv_sec  = (time64_t)tp->tv_sec;
	tp64.tv_nsec = tp->tv_nsec;
	return clock_settime64(clock_id, &tp64);
@@pp_endif@@
}


@@>> timer_create(2)
@@Create new per-process timer using `clock_id'
[[decl_include("<bits/os/sigevent.h>", "<bits/types.h>")]]
[[section(".text.crt{|.dos}.timer")]]
int timer_create(clockid_t clock_id,
                 [[in_opt]] struct sigevent *__restrict evp,
                 [[out]] timer_t *__restrict timerid);

@@>> timer_delete(2)
@@Delete timer `timerid'
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.timer")]]
int timer_delete(timer_t timerid);

[[ignore, nocrt, alias("timer_settime"), doc_alias("timer_settime")]]
[[decl_include("<features.h>", "<bits/os/itimerspec.h>", "<bits/types.h>")]]
int timer_settime32(timer_t timerid, __STDC_INT_AS_UINT_T flags,
                    [[in]] struct $itimerspec32 const *__restrict value,
                    [[out_opt]] struct $itimerspec32 *ovalue);

@@>> timer_settime(2), timer_settime64(2)
@@Set timer `timerid' to `value', returning old value in `ovalue'
[[decl_include("<features.h>", "<bits/os/itimerspec.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timer_settime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timer_settime64", "__timer_settime64")]]
[[userimpl, requires($has_function(timer_settime32) || $has_function(timer_settime64))]]
[[section(".text.crt{|.dos}.timer")]]
[[impl_include("<bits/os/itimerspec.h>")]]
int timer_settime(timer_t timerid, __STDC_INT_AS_UINT_T flags,
                  [[in]] struct itimerspec const *__restrict value,
                  [[out_opt]] struct itimerspec *__restrict ovalue) {
@@pp_if $has_function(timer_settime32)@@
	int result;
	struct itimerspec32 value32, ovalue32;
	value32.it_interval.tv_sec  = (time32_t)value->it_interval.tv_sec;
	value32.it_interval.tv_nsec = value->it_interval.tv_nsec;
	value32.it_value.tv_sec     = (time32_t)value->it_value.tv_sec;
	value32.it_value.tv_nsec    = value->it_value.tv_nsec;
	result = timer_settime32(timerid, flags, &value32, ovalue ? &ovalue32 : NULL);
	if (!result && ovalue) {
		ovalue->it_interval.tv_sec  = (time64_t)ovalue32.it_interval.tv_sec;
		ovalue->it_interval.tv_nsec = ovalue32.it_interval.tv_nsec;
		ovalue->it_value.tv_sec     = (time64_t)ovalue32.it_value.tv_sec;
		ovalue->it_value.tv_nsec    = ovalue32.it_value.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct itimerspec64 value64, ovalue64;
	value64.it_interval.tv_sec  = (time64_t)value->it_interval.tv_sec;
	value64.it_interval.tv_nsec = value->it_interval.tv_nsec;
	value64.it_value.tv_sec     = (time64_t)value->it_value.tv_sec;
	value64.it_value.tv_nsec    = value->it_value.tv_nsec;
	result = timer_settime64(timerid, flags, &value64, ovalue ? &ovalue64 : NULL);
	if (!result && ovalue) {
		ovalue->it_interval.tv_sec  = (time32_t)ovalue64.it_interval.tv_sec;
		ovalue->it_interval.tv_nsec = ovalue64.it_interval.tv_nsec;
		ovalue->it_value.tv_sec     = (time32_t)ovalue64.it_value.tv_sec;
		ovalue->it_value.tv_nsec    = ovalue64.it_value.tv_nsec;
	}
	return result;
@@pp_endif@@
}

[[ignore, nocrt, decl_include("<bits/os/itimerspec.h>", "<bits/types.h>")]]
[[doc_alias("timer_gettime"), alias("timer_gettime")]]
int timer_gettime32(timer_t timerid, [[out_opt]] struct itimerspec *value);

@@>> timer_gettime(2), timer_gettime64(2)
@@Get current value of timer `timerid' and store it in `value'
[[decl_include("<bits/os/itimerspec.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timer_gettime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timer_gettime64", "__timer_gettime64")]]
[[userimpl, requires($has_function(timer_gettime32) || $has_function(timer_gettime64))]]
[[section(".text.crt{|.dos}.timer")]]
[[impl_include("<bits/os/itimerspec.h>")]]
int timer_gettime(timer_t timerid, [[out_opt]] struct itimerspec *value) {
@@pp_if $has_function(timer_gettime32)@@
	int result;
	struct itimerspec32 value32;
	result = timer_gettime32(timerid, &value32);
	if (result == 0) {
		value->it_interval.tv_sec  = (time64_t)value32.it_interval.tv_sec;
		value->it_interval.tv_nsec = value32.it_interval.tv_nsec;
		value->it_value.tv_sec     = (time64_t)value32.it_value.tv_sec;
		value->it_value.tv_nsec    = value32.it_value.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct itimerspec64 value64;
	result = timer_gettime64(timerid, &value64);
	if (result == 0) {
		value->it_interval.tv_sec  = (time32_t)value64.it_interval.tv_sec;
		value->it_interval.tv_nsec = value64.it_interval.tv_nsec;
		value->it_value.tv_sec     = (time32_t)value64.it_value.tv_sec;
		value->it_value.tv_nsec    = value64.it_value.tv_nsec;
	}
	return result;
@@pp_endif@@
}

@@>> timer_getoverrun(2)
@@Get expiration overrun for timer `timerid'
[[section(".text.crt{|.dos}.timer"), decl_include("<bits/types.h>")]]
int timer_getoverrun(timer_t timerid);

%
%#ifdef __USE_XOPEN2K
[[cp, ignore, doc_alias("clock_nanosleep")]]
[[decl_include("<features.h>", "<bits/os/timespec.h>", "<bits/types.h>")]]
[[nocrt, alias("clock_nanosleep", "__clock_nanosleep")]]
$errno_t clock_nanosleep32(clockid_t clock_id, __STDC_INT_AS_UINT_T flags,
                           [[in]] struct $timespec32 const *__restrict requested_time,
                           [[out_opt]] struct $timespec32 *remaining);

@@>> clock_nanosleep(2), clock_nanosleep64(2)
@@High-resolution sleep with the specified clock
@@@param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
@@                  Other clock IDs cannot be used with this system call!
@@@param: flags:    Set of `0 | TIMER_ABSTIME'
@@@return: 0 :      Success
@@@return: EINTR:   System call was interrupted (if non-NULL, `*remaining' holds the amount of time not slept)
@@@return: EINVAL:  Invalid `clock_id', `flags' or `requested_time->tv_nsec'
@@@return: ENOTSUP: Clock specified by `clock_id' isn't supported.
[[cp, decl_include("<features.h>", "<bits/os/timespec.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_nanosleep", "__clock_nanosleep")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_nanosleep64", "__clock_nanosleep_time64")]]
[[userimpl, requires($has_function(clock_nanosleep32) || $has_function(clock_nanosleep64))]]
[[export_as("__clock_nanosleep")]]
[[impl_include("<bits/os/timespec.h>", "<bits/types.h>")]]
$errno_t clock_nanosleep(clockid_t clock_id, __STDC_INT_AS_UINT_T flags,
                         [[in]] struct timespec const *__restrict requested_time,
                         [[out_opt]] struct timespec *remaining) {
@@pp_if $has_function(clock_nanosleep32)@@
	$errno_t result;
	struct timespec32 req32, rem32;
	req32.tv_sec  = (time32_t)requested_time->tv_sec;
	req32.tv_nsec = requested_time->tv_nsec;
	result = clock_nanosleep32(clock_id, flags, &req32, &rem32);
	if (result == 0 && remaining) {
		remaining->tv_sec  = (time64_t)rem32.tv_sec;
		remaining->tv_nsec = rem32.tv_nsec;
	}
	return result;
@@pp_else@@
	$errno_t result;
	struct timespec64 req64, rem64;
	req64.tv_sec  = (time64_t)requested_time->tv_sec;
	req64.tv_nsec = requested_time->tv_nsec;
	result = clock_nanosleep64(clock_id, flags, &req64, &rem64);
	if (result == 0 && remaining) {
		remaining->tv_sec  = (time32_t)rem64.tv_sec;
		remaining->tv_nsec = rem64.tv_nsec;
	}
	return result;
@@pp_endif@@
}

@@>> clock_getcpuclockid(2)
@@Return clock ID for CPU-time clock
@@@return: 0 :     Success
@@@return: ENOSYS: Not supported
@@@return: EPERM:  You're not allowed to read the CPU-time clock of `pid'
@@@return: ESRCH:  No such process `pid'
[[decl_include("<bits/types.h>")]]
[[export_alias("__clock_getcpuclockid")]]
$errno_t clock_getcpuclockid(pid_t pid, clockid_t *clock_id);
%#endif /* __USE_XOPEN2K */

%
%#ifdef __USE_TIME64
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>"), doc_alias("nanosleep")]]
[[preferred_time64_variant_of(nanosleep), time64_export_alias("__nanosleep64")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__nanosleep", "__libc_nanosleep")]]
[[userimpl, requires_function(nanosleep32)]]
[[impl_include("<bits/os/timespec.h>")]]
int nanosleep64([[in]] struct timespec64 const *__restrict requested_time,
                [[out_opt]] struct timespec64 *remaining) {
	int result;
	struct timespec32 req32, rem32;
	req32.tv_sec  = (time32_t)requested_time->tv_sec;
	req32.tv_nsec = requested_time->tv_nsec;
	result = nanosleep32(&req32, &rem32);
	if (result == 0 && remaining) {
		remaining->tv_sec  = (time64_t)rem32.tv_sec;
		remaining->tv_nsec = rem32.tv_nsec;
	}
	return result;
}

[[decl_include("<bits/types.h>", "<bits/os/timespec.h>"), doc_alias("clock_getres")]]
[[preferred_time64_variant_of(clock_getres), time64_export_alias("__clock_getres64")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__clock_getres")]]
[[userimpl, requires($has_function(clock_getres32))]]
[[impl_include("<bits/os/timespec.h>")]]
int clock_getres64(clockid_t clock_id, [[out]] struct timespec64 *res) {
	int result;
	struct timespec32 res32;
	result = clock_getres32(clock_id, &res32);
	if (result == 0) {
		res->tv_sec  = (time64_t)res32.tv_sec;
		res->tv_nsec = res32.tv_nsec;
	}
	return result;
}

[[decl_include("<bits/types.h>", "<bits/os/timespec.h>"), doc_alias("clock_gettime")]]
[[preferred_time64_variant_of(clock_gettime), time64_export_alias("__clock_gettime64")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__clock_gettime")]]
[[userimpl, requires_function(clock_gettime32)]]
[[impl_include("<bits/os/timespec.h>")]]
int clock_gettime64(clockid_t clock_id, [[out]] struct timespec64 *tp) {
	int result;
	struct timespec32 res32;
	result = clock_gettime32(clock_id, &res32);
	if (result == 0) {
		tp->tv_sec  = (time64_t)res32.tv_sec;
		tp->tv_nsec = res32.tv_nsec;
	}
	return result;
}

[[decl_include("<bits/types.h>", "<bits/os/timespec.h>"), doc_alias("clock_settime")]]
[[preferred_time64_variant_of(clock_settime), time64_export_alias("__clock_settime64")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__clock_settime")]]
[[userimpl, requires_function(clock_settime32)]]
[[impl_include("<bits/os/timespec.h>")]]
int clock_settime64(clockid_t clock_id, [[in]] struct timespec64 const *tp) {
	struct timespec32 tp32;
	tp32.tv_sec  = (time32_t)tp->tv_sec;
	tp32.tv_nsec = tp->tv_nsec;
	return clock_settime32(clock_id, &tp32);
}

[[decl_include("<features.h>", "<bits/os/itimerspec.h>", "<bits/types.h>")]]
[[preferred_time64_variant_of(timer_settime), doc_alias("timer_settime")]]
[[time64_export_alias("__timer_settime64")]]
[[userimpl, requires_function(timer_settime32)]]
[[section(".text.crt{|.dos}.timer")]]
[[impl_include("<bits/os/itimerspec.h>")]]
int timer_settime64(timer_t timerid, __STDC_INT_AS_UINT_T flags,
                    [[in]] struct itimerspec64 const *__restrict value,
                    [[out_opt]] struct itimerspec64 *__restrict ovalue) {
	int result;
	struct itimerspec32 value32, ovalue32;
	value32.it_interval.tv_sec  = (time32_t)value->it_interval.tv_sec;
	value32.it_interval.tv_nsec = value->it_interval.tv_nsec;
	value32.it_value.tv_sec     = (time32_t)value->it_value.tv_sec;
	value32.it_value.tv_nsec    = value->it_value.tv_nsec;
	result = timer_settime32(timerid, flags, &value32, ovalue ? &ovalue32 : NULL);
	if (!result && ovalue) {
		ovalue->it_interval.tv_sec  = (time64_t)ovalue32.it_interval.tv_sec;
		ovalue->it_interval.tv_nsec = ovalue32.it_interval.tv_nsec;
		ovalue->it_value.tv_sec     = (time64_t)ovalue32.it_value.tv_sec;
		ovalue->it_value.tv_nsec    = ovalue32.it_value.tv_nsec;
	}
	return result;
}

[[decl_include("<bits/os/itimerspec.h>", "<bits/types.h>")]]
[[preferred_time64_variant_of(timer_gettime), doc_alias("timer_gettime")]]
[[time64_export_alias("__timer_gettime64")]]
[[userimpl, requires_function(timer_gettime32)]]
[[section(".text.crt{|.dos}.timer")]]
[[impl_include("<bits/os/itimerspec.h>")]]
int timer_gettime64(timer_t timerid, [[out]] struct itimerspec64 *value) {
	int result;
	struct itimerspec32 value32;
	result = timer_gettime32(timerid, &value32);
	if (result == 0) {
		value->it_interval.tv_sec  = (time64_t)value32.it_interval.tv_sec;
		value->it_interval.tv_nsec = value32.it_interval.tv_nsec;
		value->it_value.tv_sec     = (time64_t)value32.it_value.tv_sec;
		value->it_value.tv_nsec    = value32.it_value.tv_nsec;
	}
	return result;
}

%
%#ifdef __USE_XOPEN2K
[[cp, decl_include("<features.h>", "<bits/os/timespec.h>", "<bits/types.h>")]]
[[preferred_time64_variant_of(clock_nanosleep), doc_alias("clock_nanosleep")]]
[[time64_export_alias("__clock_nanosleep_time64")]]
[[userimpl, requires_function(clock_nanosleep32)]]
[[impl_include("<bits/os/timespec.h>", "<bits/types.h>")]]
$errno_t clock_nanosleep64(clockid_t clock_id, __STDC_INT_AS_UINT_T flags,
                           [[in]] struct timespec64 const *requested_time,
                           [[out_opt]] struct timespec64 *remaining) {
	$errno_t result;
	struct timespec32 req32, rem32;
	req32.tv_sec  = (time32_t)requested_time->tv_sec;
	req32.tv_nsec = requested_time->tv_nsec;
	result = clock_nanosleep32(clock_id, flags, &req32, &rem32);
	if (result == 0 && remaining) {
		remaining->tv_sec  = (time64_t)rem32.tv_sec;
		remaining->tv_nsec = rem32.tv_nsec;
	}
	return result;
}
%#endif /* __USE_XOPEN2K */
%#endif /* __USE_TIME64 */
%#endif /* __USE_POSIX199309 */


%
%/* timespec_get() is defined by both c11 and c++17 */
%(c,std,ccompat)#if defined(__USE_ISOCXX17) || defined(__USE_ISOC11)
@@>> timespec_get(3), timespec_get64(3)
@@Set `ts' to calendar time based in time base `base'
[[std, decl_include("<bits/os/timespec.h>"), no_crt_self_import, dos_only_export_as("_timespec32_get")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timespec_get", "_timespec32_get")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timespec_get64", "_timespec64_get")]]
[[requires_include("<asm/os/clock.h>", "<asm/crt/time.h>")]]
[[requires(defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && $has_function(clock_gettime))]]
int timespec_get([[out]] struct timespec *ts, int base) {
	if (base == __TIME_UTC) {
		if (clock_gettime(__CLOCK_REALTIME, ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}

%#ifdef __USE_TIME64
[[decl_include("<bits/os/timespec.h>"), dos_only_export_alias("_timespec64_get")]]
[[preferred_time64_variant_of(timespec_get), doc_alias("timespec_get")]]
[[time64_export_alias("__timespec_get64")]]
[[requires_include("<asm/os/clock.h>", "<asm/crt/time.h>")]]
[[requires(defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && $has_function(clock_gettime64))]]
int timespec_get64([[out]] struct timespec64 *ts, int base) {
	if (base == __TIME_UTC) {
		if (clock_gettime64(__CLOCK_REALTIME, ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}
%#endif /* __USE_TIME64 */

%(c,std,ccompat)#endif /* __USE_ISOCXX17 || __USE_ISOC11 */

%
%(c,std,ccompat)#if defined(__USE_ISOC23)
@@>> timespec_getres(3), timespec_getres64(3)
@@Set `ts' to calendar time based in time base `base'
[[std, decl_include("<bits/os/timespec.h>"), no_crt_self_import, dos_only_export_as("_timespec32_get")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timespec_getres", "_timespec32_getres")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timespec_getres64", "_timespec64_getres", "__timespec_getres64")]]
[[requires_include("<asm/os/clock.h>", "<asm/crt/time.h>")]]
[[requires(defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && $has_function(clock_getres))]]
int timespec_getres([[out]] struct timespec *ts, int base) {
	if (base == __TIME_UTC) {
		if (clock_getres(__CLOCK_REALTIME, ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}

%#ifdef __USE_TIME64
[[decl_include("<bits/os/timespec.h>"), dos_only_export_alias("_timespec64_get")]]
[[preferred_time64_variant_of(timespec_getres), doc_alias("timespec_getres")]]
[[time64_export_alias("__timespec_getres64")]]
[[requires_include("<asm/os/clock.h>", "<asm/crt/time.h>")]]
[[requires(defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && $has_function(clock_getres64))]]
int timespec_getres64([[out]] struct timespec64 *ts, int base) {
	if (base == __TIME_UTC) {
		if (clock_getres64(__CLOCK_REALTIME, ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}
%#endif /* __USE_TIME64 */

%(c,std,ccompat)#endif /* __USE_ISOC23 */



%
%#ifdef __USE_XOPEN_EXTENDED
%{
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
}


%(auto_source){
#ifndef __KERNEL__
#undef getdate_err
INTERN ATTR_SECTION(".bss.crt.time") int libc_getdate_err = 0;
DEFINE_PUBLIC_ALIAS(getdate_err, libc_getdate_err);
#define getdate_err GET_NOREL_GLOBAL(getdate_err)
#endif /* !__KERNEL__ */
}

@@>> getdate(3)
@@Parse the given string as a date specification and return a value
@@representing the value. The templates from the file identified by
@@the environment variable `$DATEMSK' are used. In case of an error
@@`getdate_err' is set
[[decl_include("<bits/crt/tm.h>")]]
[[requires_include("<libc/template/getdate_err.h>")]]
[[requires($has_function(getdate_r) && defined(__LOCAL_getdate_err))]]
[[impl_include("<bits/crt/tm.h>")]]
struct $tm *getdate([[in]] char const *string) {
	@@static struct tm tmbuf = {0}@@
	int error = getdate_r(string, &tmbuf);
	if (error == 0)
		return &tmbuf;
	/* Caution: this part here is still thread-unsafe! */
	__LOCAL_getdate_err = error;
	return NULL;
}
%#endif /* __USE_XOPEN_EXTENDED */







%(user){
INTDEF char *libc_tzname[2];
INTDEF int libc_daylight;
INTDEF longptr_t libc_timezone;
}


%
%#ifdef __USE_XOPEN2K8

@@>> strftime_l(3)
@@Similar to `strftime(3)' but take the information from
@@the   provided  locale  and   not  the  global  locale
[[decl_include("<bits/crt/tm.h>", "<hybrid/typecore.h>")]]
[[dos_only_export_alias("_strftime_l"), export_alias("__strftime_l")]]
$size_t strftime_l([[out(return <= bufsize)]] char *__restrict buf, $size_t bufsize,
                   [[in, format("strftime")]] char const *__restrict format,
                   [[in]] struct $tm const *__restrict tp, $locale_t locale) {
	(void)locale;
	return strftime(buf, bufsize, format, tp);
}
%#endif /* __USE_XOPEN2K8 */


[[ignore, nocrt, alias("strptime_l")]]
[[decl_include("<bits/crt/tm.h>"), doc_alias("strptime_l")]]
char *crt_strptime_l([[in]] char const *__restrict s,
                     [[in]] char const *__restrict format,
                     [[out]] struct $tm *__restrict tp,
                     $locale_t locale);


%
%#ifdef __USE_XOPEN
@@>> strptime(3)
@@Parse `s' according to `format' and store binary time information in `tp'.
@@The return  value is  a pointer  to the  first unparsed  character in  `s'
[[decl_include("<bits/crt/tm.h>")]]
char *strptime([[in]] char const *__restrict s,
               [[in]] char const *__restrict format,
               [[out]] struct $tm *__restrict tp) {
@@pp_if $has_function(crt_strptime_l) && !defined(__BUILDING_LIBC)@@
	return crt_strptime_l(s, format, tp, NULL);
@@pp_else@@
	/* TODO */
	(void)s;
	(void)format;
	(void)tp;
	COMPILER_IMPURE();
	return NULL;
@@pp_endif@@
}
%#endif /* __USE_XOPEN */


%
%#ifdef __USE_GNU
@@>> strptime_l(3)
@@Similar to `strptime' but take the information from
@@the  provided  locale  and  not  the  global locale
[[decl_include("<bits/crt/tm.h>")]]
char *strptime_l([[in]] char const *__restrict s,
                 [[in]] char const *__restrict format,
                 [[out]] struct $tm *__restrict tp,
                 $locale_t locale) {
	(void)locale;
	return strptime(s, format, tp);
}

@@>> getdate_r(3)
@@Since  `getdate' is not  reentrant because of  the use of `getdate_err'
@@and the static buffer to return the result in, we provide a thread-safe
@@variant.  The  functionality is  the same.  The  result is  returned in
@@the  buffer pointed to by `resbufp' and in case of an error, the return
@@value is != 0  with the same values  as given above for  `getdate_err'.
[[decl_include("<bits/crt/tm.h>")]]
int getdate_r([[in]] char const *__restrict string,
              [[out]] struct $tm *__restrict resbufp) {
	/* TODO */
	(void)string;
	(void)resbufp;
	COMPILER_IMPURE();
	return 0;
}

@@>> clock_adjtime(2), clock_adjtime64(2)
[[guard, no_crt_self_import, decl_include("<bits/types.h>", "<bits/os/timex.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_adjtime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_adjtime64", "__clock_adjtime64")]]
int clock_adjtime($clockid_t clock_id, [[inout]] struct timex *utx);

%
%#ifdef __USE_TIME64
[[guard, decl_include("<bits/types.h>", "<bits/os/timex.h>")]]
[[time64_export_alias("__clock_adjtime64")]]
[[preferred_time64_variant_of(clock_adjtime), doc_alias("clock_adjtime")]]
int clock_adjtime64($clockid_t clock_id, [[inout]] struct timex64 *utx);
%#endif /* __USE_TIME64 */

%#endif /* __USE_GNU */




%
%#ifdef __USE_POSIX

@@>> gmtime_r(3), gmtime64_r(3)
@@Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>"), no_crt_self_import, export_as("__gmtime_r")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("gmtime_r", "__gmtime_r")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("gmtime64_r", "__gmtime64_r")]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__@@
DEFINE_TIME_MONTHSTART_YDAY
DEFINE_ISLEAP
DEFINE_DAYSTOYEARS
DEFINE_YEARSTODAYS
@@pp_endif@@
)]]
struct $tm *gmtime_r([[in]] $time_t const *__restrict timer,
                     [[out]] struct $tm *__restrict tp) {
@@pp_if !defined(__BUILDING_LIBC) && $has_function(crt_gmtime32_s) && !defined(__USE_TIME_BITS64)@@
	return crt_gmtime32_s(tp, timer) ? NULL : tp;
@@pp_elif !defined(__BUILDING_LIBC) && $has_function(crt_gmtime64_s) && defined(__USE_TIME_BITS64)@@
	return crt_gmtime64_s(tp, timer) ? NULL : tp;
@@pp_elif !defined(__BUILDING_LIBC) && $has_function(crt_gmtime32_r)@@
	time32_t timer2 = (time32_t)*timer;
	return crt_gmtime32_r(&timer2, tp);
@@pp_elif defined(__BUILDING_LIBC) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__@@
	time_t t = *timer;
	u16 const *monthvec;
	int i;
	tp->@tm_sec@  = (int)(t % SECONDS_PER_MINUTE);
	tp->@tm_min@  = (int)((t / SECONDS_PER_MINUTE) % MINUTES_PER_HOUR);
	tp->@tm_hour@ = (int)((t / SECONDS_PER_HOUR) % HOURS_PER_DAY);
	t /= SECONDS_PER_DAY;
	t += __yearstodays(UNIX_TIME_START_YEAR);
	tp->@tm_wday@ = (int)(t % DAYS_PER_WEEK);
	tp->@tm_year@ = (int)__daystoyears(t); /* TODO: This doesn't work for exact dates! (s.a. `deemon:time') */
	t -= __yearstodays(tp->@tm_year@);
	tp->@tm_yday@ = (int)t;
	monthvec = __NAMESPACE_LOCAL_SYM __time_monthstart_yday[__isleap(tp->@tm_year@)];
	for (i = 1; i < 12; ++i)
		if (monthvec[i] >= t)
			break;
	tp->@tm_mon@ = i - 1;
	t -= monthvec[i - 1];
	tp->@tm_mday@ = t + 1;
	/* found here: "http://stackoverflow.com/questions/5590429/calculating-daylight-savings-time-from-only-date" */
	if (tp->@tm_mon@ < 2 || tp->@tm_mon@ > 10) {
		//January, February, and December are out.
		tp->@tm_isdst@ = 0;
	} else if (tp->@tm_mon@ > 2 && tp->@tm_mon@ < 10) {
		//April to October are in
		tp->@tm_isdst@ = 1;
	} else {
		int previousSunday;
		previousSunday = tp->@tm_mday@ - tp->@tm_wday@;
		if (tp->@tm_mon@ == 2) {
			//In march, we are DST if our previous Sunday was on or after the 8th.
			tp->@tm_isdst@ = previousSunday >= 8;
		} else {
			//In November we must be before the first Sunday to be dst.
			//That means the  previous Sunday must  be before the  1st.
			tp->@tm_isdst@ = previousSunday <= 0;
		}
	}
	tp->@tm_year@ -= 1900;
	return tp;
@@pp_else@@
	time64_t timer2 = (time64_t)*timer;
	return gmtime64_r(&timer2, tp);
@@pp_endif@@
}

@@>> localtime_r(3), localtime64_r(3)
@@Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("localtime_r")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("localtime64_r", "__localtime64_r")]]
[[export_as("__localtime_r")]] /* From Glibc 2.0.4 */
struct $tm *localtime_r([[in]] $time_t const *__restrict timer,
                        [[out]] struct $tm *__restrict tp) {
@@pp_if !defined(__BUILDING_LIBC) && $has_function(crt_localtime32_s) && !defined(__USE_TIME_BITS64)@@
	return crt_localtime32_s(tp, timer) ? NULL : tp;
@@pp_elif !defined(__BUILDING_LIBC) && $has_function(crt_localtime64_s) && defined(__USE_TIME_BITS64)@@
	return crt_localtime64_s(tp, timer) ? NULL : tp;
@@pp_elif !defined(__BUILDING_LIBC) && $has_function(crt_localtime32_r)@@
	time32_t timer2 = (time32_t)*timer;
	return crt_localtime32_r(&timer2, tp);
@@pp_elif defined(__BUILDING_LIBC) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__@@
	/* XXX: Timezone support? */
	return gmtime_r(timer, tp);
@@pp_else@@
	time64_t timer2 = (time64_t)*timer;
	return localtime64_r(&timer2, tp);
@@pp_endif@@
}

@@>> ctime_r(3), ctime64_r(3)
@@Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)'
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ctime_r")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ctime64_r", "__ctime64_r")]]
char *ctime_r([[in]] $time_t const *__restrict timer,
              [[out]] char buf[26]) {
@@pp_if !defined(__BUILDING_LIBC) && $has_function(crt_ctime32_s) && !defined(__USE_TIME_BITS64)@@
	return crt_ctime32_s(buf, 26, timer) ? NULL : buf;
@@pp_elif !defined(__BUILDING_LIBC) && $has_function(crt_ctime64_s) && defined(__USE_TIME_BITS64)@@
	return crt_ctime64_s(buf, 26, timer) ? NULL : buf;
@@pp_elif !defined(__BUILDING_LIBC) && $has_function(crt_ctime32_r)@@
	time32_t timer2 = (time32_t)*timer;
	return crt_ctime32_r(&timer2, buf);
@@pp_elif defined(__BUILDING_LIBC) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__@@
	struct tm ltm;
	return asctime_r(localtime_r(timer, &ltm), buf);
@@pp_else@@
	time64_t timer2 = (time64_t)*timer;
	return ctime64_r(&timer2, buf);
@@pp_endif@@
}

%
%#ifdef __USE_TIME64

[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[preferred_time64_variant_of(gmtime_r), doc_alias("gmtime_r")]]
[[time64_export_alias("__gmtime64_r")]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || !$has_function(crt_gmtime64_s)@@
DEFINE_TIME_MONTHSTART_YDAY
DEFINE_ISLEAP
DEFINE_DAYSTOYEARS
DEFINE_YEARSTODAYS
@@pp_endif@@
)]]
struct $tm *gmtime64_r([[in]] $time64_t const *__restrict timer,
                       [[out]] struct $tm *__restrict tp) {
@@pp_if !defined(__BUILDING_LIBC) && $has_function(crt_gmtime64_s)@@
	return crt_gmtime64_s(tp, timer) ? NULL : tp;
@@pp_else@@
	time64_t t = *timer;
	u16 const *monthvec;
	int i;
	tp->@tm_sec@  = (int)(t % 60);
	tp->@tm_min@  = (int)((t / 60) % 60);
	tp->@tm_hour@ = (int)((t / (60 * 60)) % 24);
	t /= SECONDS_PER_DAY;
	t += __yearstodays(UNIX_TIME_START_YEAR);
	tp->@tm_wday@ = (int)(t % DAYS_PER_WEEK);
	tp->@tm_year@ = (int)__daystoyears(t); /* TODO: This doesn't work for exact dates! (s.a. `deemon:time') */
	t -= __yearstodays(tp->@tm_year@);
	tp->@tm_yday@ = (int)t;
	monthvec = __NAMESPACE_LOCAL_SYM __time_monthstart_yday[__isleap(tp->@tm_year@)];
	for (i = 1; i < 12; ++i) {
		if (monthvec[i] >= t)
			break;
	}
	tp->@tm_mon@ = i - 1;
	t -= monthvec[i - 1];
	tp->@tm_mday@ = t + 1;
	/* found here: "http://stackoverflow.com/questions/5590429/calculating-daylight-savings-time-from-only-date" */
	if (tp->@tm_mon@ < 2 || tp->@tm_mon@ > 10) {
		//January, February, and December are out.
		tp->@tm_isdst@ = 0;
	} else if (tp->@tm_mon@ > 2 && tp->@tm_mon@ < 10) {
		//April to October are in
		tp->@tm_isdst@ = 1;
	} else {
		int previousSunday;
		previousSunday = tp->@tm_mday@ - tp->@tm_wday@;
		if (tp->@tm_mon@ == 2) {
			//In march, we are DST if our previous Sunday was on or after the 8th.
			tp->@tm_isdst@ = previousSunday >= 8;
		} else {
			//In November we must be before the first Sunday to be dst.
			//That means the  previous Sunday must  be before the  1st.
			tp->@tm_isdst@ = previousSunday <= 0;
		}
	}
	tp->@tm_year@ -= 1900;
	return tp;
@@pp_endif@@
}

[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[preferred_time64_variant_of(localtime_r), doc_alias("localtime_r")]]
[[time64_export_alias("__localtime64_r")]]
struct $tm *localtime64_r([[in]] $time64_t const *__restrict timer,
                          [[out]] struct $tm *__restrict tp) {
@@pp_if !defined(__BUILDING_LIBC) && $has_function(crt_localtime64_s)@@
	return crt_localtime64_s(tp, timer) ? NULL : tp;
@@pp_else@@
	/* XXX: Timezone support? */
	return gmtime64_r(timer, tp);
@@pp_endif@@
}

[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[preferred_time64_variant_of(ctime_r), doc_alias("ctime_r")]]
[[time64_export_alias("__ctime64_r")]]
char *ctime64_r([[in]] $time64_t const *__restrict timer,
                [[out]] char buf[26]) {
@@pp_if !defined(__BUILDING_LIBC) && $has_function(crt_ctime64_s)@@
	return crt_ctime64_s(buf, 26, timer) ? NULL : buf;
@@pp_else@@
	struct tm ltm;
	return asctime_r(localtime64_r(timer, &ltm), buf);
@@pp_endif@@
}
%#endif /* __USE_TIME64 */

%[define(DEFINE_TIME_ABBR_WDAY_NAMES =
@@pp_ifndef __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED@@
#define __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED
@@push_namespace(local)@@
__LOCAL_LIBC_CONST_DATA(__abbr_wday_names) char const __abbr_wday_names[7][4] =
	{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_TIME_ABBR_MONTH_NAMES =
@@pp_ifndef __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED@@
#define __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED
@@push_namespace(local)@@
__LOCAL_LIBC_CONST_DATA(__abbr_month_names) char const __abbr_month_names[12][4] =
	{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
@@pop_namespace@@
@@pp_endif@@
)]


@@>> asctime_r(3)
@@Return in `buf' a string of the form "Day Mon dd hh:mm:ss yyyy\n"
@@that   is   the   representation   of   `tp'   in   this   format
[[decl_include("<bits/crt/tm.h>")]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || !$has_function(crt_asctime_s)@@
DEFINE_TIME_ABBR_WDAY_NAMES
DEFINE_TIME_ABBR_MONTH_NAMES
@@pp_endif@@
)]]
[[export_as("__asctime_r")]] /* From Glibc 2.0.4 */
char *asctime_r([[in]] struct $tm const *__restrict tp,
                [[out]] char buf[26]) {
@@pp_if !defined(__BUILDING_LIBC) && $has_function(crt_asctime_s)@@
	return crt_asctime_s(buf, 26, tp) ? NULL : buf;
@@pp_else@@
	sprintf(buf, "%.3s %.3s%3u %.2u:%.2u:%.2u %u\n",
	        (unsigned int)tp->@tm_wday@ >= 7 ? "??" "?" :
	        __NAMESPACE_LOCAL_SYM __abbr_wday_names[tp->@tm_wday@],
	        (unsigned int)tp->@tm_mon@ >= 12 ? "??" "?" :
	        __NAMESPACE_LOCAL_SYM __abbr_month_names[tp->@tm_mon@],
	        (unsigned int)tp->@tm_mday@,
	        (unsigned int)tp->@tm_hour@,
	        (unsigned int)tp->@tm_min@,
	        (unsigned int)tp->@tm_sec@,
	        (unsigned int)tp->@tm_year@ + 1900);
	return buf;
@@pp_endif@@
}

%#endif /* __USE_POSIX */


%
%
%#ifdef __USE_DOS

%{
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
}

/* Under true DOS, these functions are actually exposed. However, Glibc already
 * defines symbols like `__daylight' to be the actual data objects, whereas DOS
 * defines them as functions returning pointers to the data objects.
 *
 * This namespace collision can easily be resolved by declaring DOS$__daylight, but
 * the header-symbol collision cannot be resolved. As a result, we only declare the
 * Glibc variant, so-as to guaranty a uniform meaning for `__daylight' */
[[ignore, nodos, cc(LIBDCALL), no_crt_self_export, no_crt_self_import]]
[[export_alias("DOS$__daylight"), if(defined(__CRT_DOS)), preferred_alias("__daylight")]]
[[requires_include("<libc/template/daylight.h>"), requires(defined(__LOCAL_daylight))]]
[[impl_include("<libc/template/daylight.h>"), export_alias("__p__daylight")]]
[[wunused, const, nothrow, nonnull]] int *__daylight(void) {
	return &__LOCAL_daylight;
}

[[ignore, nodos, cc(LIBDCALL), no_crt_self_export, no_crt_self_import]]
[[export_alias("DOS$__timezone"), if(defined(__CRT_DOS)), preferred_alias("__timezone")]]
[[requires_include("<libc/template/timezone.h>"), requires(defined(__LOCAL_timezone))]]
[[impl_include("<libc/template/timezone.h>"), export_alias("__p__timezone")]]
[[wunused, const, nothrow, nonnull]] long *__timezone(void) {
	return (long *)&__LOCAL_timezone;
}

[[ignore, nodos, cc(LIBDCALL), no_crt_self_export, no_crt_self_import]]
[[export_alias("DOS$__tzname"), if(defined(__CRT_DOS)), preferred_alias("__tzname")]]
[[requires_include("<libc/template/tzname.h>"), requires(defined(__LOCAL_tzname))]]
[[impl_include("<libc/template/tzname.h>"), export_alias("__p__tzname")]]
[[wunused, const, nothrow, nonnull]] char **__tzname(void) {
	return __LOCAL_tzname;
}


/* Glibc doesn't have `__dstbias', so this one we can expose. */
[[nodos, cc(LIBDCALL), no_crt_self_export, no_crt_self_import, decl_include("<hybrid/typecore.h>")]]
[[export_alias("DOS$__dstbias"), if(defined(__CRT_DOS)), preferred_alias("__dstbias")]]
[[requires_include("<libc/template/dstbias.h>"), requires(defined(__LOCAL_dstbias))]]
[[impl_include("<libc/template/dstbias.h>"), export_alias("__p__dstbias")]]
[[wunused, const, nothrow, nonnull]] __LONG32_TYPE__ *__dstbias(void) {
	return &__LOCAL_dstbias;
}

%[insert:pp_if(!defined(_dstbias))]
%[insert:pp_if(defined(__LOCAL_dstbias))]
%#define _dstbias __LOCAL_dstbias
%[insert:pp_elif(defined(__CRT_HAVE__dstbias))]
%__CSDECLARE(,__LONG32_TYPE__,_dstbias)
%#define _dstbias _dstbias
%[insert:pp_elif($has_function(__dstbias))]
%#define _dstbias (*__dstbias())
%[insert:pp_endif]
%[insert:pp_endif]

[[section(".text.crt.dos.time.timezone")]]
[[requires_include("<libc/template/daylight.h>")]]
[[requires(defined(__LOCAL_daylight))]]
[[impl_include("<libc/template/daylight.h>")]]
[[decl_include("<bits/types.h>")]]
errno_t _get_daylight(int *p_result) {
	*p_result = __LOCAL_daylight;
	return 0;
}

[[section(".text.crt.dos.time.timezone")]]
[[requires_include("<libc/template/timezone.h>")]]
[[requires(defined(__LOCAL_timezone))]]
[[impl_include("<libc/template/timezone.h>")]]
[[decl_include("<bits/types.h>")]]
errno_t _get_timezone(long *p_seconds) {
	*p_seconds = __LOCAL_timezone;
	return 0;
}

[[section(".text.crt.dos.time.timezone")]]
[[requires_include("<libc/template/dstbias.h>")]]
[[requires(defined(__LOCAL_dstbias))]]
[[impl_include("<libc/template/dstbias.h>")]]
[[decl_include("<bits/types.h>")]]
errno_t _get_dstbias(__LONG32_TYPE__ *p_result) {
	*p_result = __LOCAL_dstbias;
	return 0;
}

[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[requires_include("<libc/template/tzname.h>")]]
[[requires(defined(__LOCAL_tzname))]]
[[crt_dos_variant({ impl: libd_errno_kos2dos(%[invoke_libc]) })]]
errno_t _get_tzname([[out]] size_t *result,
                    [[out_opt/*(*result <= bufsize)*/]] char *buf,
                    size_t bufsize, int index) {
	char *reqstr;
	size_t reqsiz;
	if (index < 0 || index > 1 || !result || (!buf && bufsize)) {
@@pp_ifdef EINVAL@@
		return $EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
@@pp_if $has_function(tzset)@@
	tzset(); /* Update state of `tzname' */
@@pp_endif@@
	reqstr  = __LOCAL_tzname[(unsigned int)index];
	reqsiz  = (strlen(reqstr) + 1) * sizeof(char);
	*result = reqsiz;
	if (bufsize > reqsiz)
		bufsize = reqsiz;
	memcpy(buf, reqstr, bufsize);
	return 0;
}


[[nocrt, wunused, decl_include("<bits/types.h>")]]
[[doc_alias("ctime"), alias("ctime", "_ctime32")]]
[[nonnull]] char *_ctime32([[in]] $time32_t const *timer);

%[insert:function(_ctime64 = ctime64)]

[[nocrt, wunused, decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[doc_alias("gmtime"), alias("gmtime", "_gmtime32")]]
[[nonnull]] struct $tm *_gmtime32([[in]] $time32_t const *timer);

%[insert:function(_gmtime64 = gmtime64)]


[[doc_alias("gmtime_r"), decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[impl_include("<libc/errno.h>")]]
errno_t _gmtime32_s([[out]] struct $tm *__restrict tp,
                    [[in]] $time32_t const *__restrict timer) {
@@pp_if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__@@
@@pp_ifdef __BUILDING_LIBC@@
	gmtime_r(timer, tp);
@@pp_else@@
	if unlikely(!gmtime_r(timer, tp))
		return __libc_geterrno_or(1);
@@pp_endif@@
@@pp_else@@
	time_t ttimer = (time_t)*timer;
@@pp_ifdef __BUILDING_LIBC@@
	gmtime_r(&ttimer, tp);
@@pp_else@@
	if unlikely(!gmtime_r(&ttimer, tp))
		return __libc_geterrno_or(1);
@@pp_endif@@
@@pp_endif@@
	return 0;
}

[[doc_alias("gmtime64_r"), decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[impl_include("<libc/errno.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), crt_intern_alias("_gmtime32_s")]]
errno_t _gmtime64_s([[out]] struct $tm *__restrict tp,
                    [[in]] $time64_t const *__restrict timer) {
@@pp_ifdef __BUILDING_LIBC@@
	gmtime64_r(timer, tp);
@@pp_else@@
	if unlikely(!gmtime64_r(timer, tp))
		return __libc_geterrno_or(1);
@@pp_endif@@
	return 0;
}

[[doc_alias("localtime_r"), decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[impl_include("<libc/errno.h>")]]
errno_t _localtime32_s([[out]] struct $tm *__restrict tp,
                       [[in]] $time32_t const *__restrict timer) {
@@pp_if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__@@
@@pp_ifdef __BUILDING_LIBC@@
	localtime_r(timer, tp);
@@pp_else@@
	if unlikely(!localtime_r(timer, tp))
		return __libc_geterrno_or(1);
@@pp_endif@@
@@pp_else@@
	time_t ttimer = (time_t)*timer;
@@pp_ifdef __BUILDING_LIBC@@
	localtime_r(&ttimer, tp);
@@pp_else@@
	if unlikely(!localtime_r(&ttimer, tp))
		return __libc_geterrno_or(1);
@@pp_endif@@
@@pp_endif@@
	return 0;
}

[[doc_alias("localtime64_r"), decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), crt_intern_alias("_localtime32_s")]]
errno_t _localtime64_s([[out]] struct $tm *__restrict tp,
                       [[in]] $time64_t const *__restrict timer) {
	localtime64_r(timer, tp);
	return 0;
}

[[doc_alias("ctime_r"), decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
errno_t _ctime32_s([[out(? <= bufsize)]] char buf[26], $size_t bufsize,
                   [[in]] $time32_t const *__restrict timer) {
	if unlikely(bufsize < 26)
		return DOS_ERANGE;
@@pp_if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__@@
@@pp_ifdef __BUILDING_LIBC@@
	ctime_r(timer, buf);
@@pp_else@@
	if unlikely(!ctime_r(timer, buf))
		return __libc_geterrno_or(1);
@@pp_endif@@
@@pp_else@@
	{
		time_t timer2 = (time_t)*timer;
@@pp_ifdef __BUILDING_LIBC@@
		ctime_r(&timer2, buf);
@@pp_else@@
		if unlikely(!ctime_r(&timer2, buf))
			return __libc_geterrno_or(1);
@@pp_endif@@
	}
@@pp_endif@@
	return 0;
}

[[doc_alias("ctime64_r"), decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), crt_intern_alias("_ctime32_s")]]
errno_t _ctime64_s([[out(? <= bufsize)]] char buf[26], $size_t bufsize,
                   [[in]] $time64_t const *__restrict timer) {
	if unlikely(bufsize < 26)
		return DOS_ERANGE;
@@pp_ifdef __BUILDING_LIBC@@
	ctime64_r(timer, buf);
@@pp_else@@
	if unlikely(!ctime64_r(timer, buf))
		return __libc_geterrno_or(1);
@@pp_endif@@
	return 0;
}


%#ifndef __NO_FPU
[[nocrt, const, wunused, nothrow, alias("difftime", "_difftime32")]]
[[decl_include("<bits/types.h>"), doc_alias("difftime")]]
[[bind_local_function("difftime")]]
double _difftime32($time32_t time1, $time32_t time0);

%[insert:function(_difftime64 = difftime64)]
%#endif /* !__NO_FPU */

[[nocrt, wunused, alias("localtime", "_localtime32")]]
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>"), doc_alias("localtime")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME_T__ == __SIZEOF_TIME32_T__), bind_local_function(localtime)]]
[[requires_function(localtime)]]
[[nonnull]] struct $tm *_localtime32([[in]] $time32_t const *timer) {
	time_t timer2 = (time_t)*timer;
	return localtime(&timer2);
}

%[insert:function(_localtime64 = localtime64)]

[[nocrt, alias("time", "__time", "__libc_time", "_time32")]]
[[decl_include("<bits/types.h>"), doc_alias("time")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME_T__ == __SIZEOF_TIME32_T__ && ($has_function(crt_time32) || $has_function(time64))), bind_local_function(time)]]
[[requires_function(time)]]
$time32_t _time32([[nullable]] $time32_t *timer) {
	time32_t result = (time32_t)time(NULL);
	if (timer != NULL)
		*timer = result;
	return result;
}

%[insert:function(_time64 = time64)]

[[nocrt, pure, wunused, alias("mktime", "_mktime32", "timelocal")]]
[[decl_include("<bits/types.h>", "<features.h>", "<bits/crt/tm.h>"), doc_alias("mktime")]]
[[bind_local_function("mktime")]]
$time32_t _mktime32([[inout]] struct $tm *tp);

%[insert:function(_mktime64 = mktime64)]

[[nocrt, pure, wunused, alias("timegm", "_mkgmtime", "_mkgmtime32")]]
[[decl_include("<bits/types.h>", "<features.h>", "<bits/crt/tm.h>"), doc_alias("timegm")]]
[[bind_local_function("timegm")]]
$time32_t _mkgmtime32([[inout]] struct $tm *tp);

%[insert:function(_mkgmtime64 = timegm64)]

%[insert:function(_strftime_l = strftime_l)]

[[requires_function(time64, localtime64_r)]]
[[impl_include("<bits/crt/tm.h>")]]
[[impl_include("<libc/template/itoa_digits.h>")]]
char *_strtime([[out]] char buf[9]) {
	time64_t now = time64(NULL);
	struct tm now_tm, *tp;
	tp = localtime64_r(&now, &now_tm);
	buf[0] = itoa_decimal(tp->@tm_hour@ / 10);
	buf[1] = itoa_decimal(tp->@tm_hour@ % 10);
	buf[2] = ':';
	buf[3] = itoa_decimal(tp->@tm_min@ / 10);
	buf[4] = itoa_decimal(tp->@tm_min@ % 10);
	buf[5] = ':';
	buf[6] = itoa_decimal(tp->@tm_sec@ / 10);
	buf[7] = itoa_decimal(tp->@tm_sec@ % 10);
	buf[8] = '\0';
	return 0;
}

[[requires_function(time64, localtime64_r)]]
[[impl_include("<bits/crt/tm.h>")]]
[[impl_include("<libc/template/itoa_digits.h>")]]
char *_strdate([[out]] char buf[9]) {
	time64_t now = time64(NULL);
	struct tm now_tm, *tp;
	tp = localtime64_r(&now, &now_tm);
	buf[0] = itoa_decimal(tp->@tm_mon@ / 10);
	buf[1] = itoa_decimal(tp->@tm_mon@ % 10);
	buf[2] = '/';
	buf[3] = itoa_decimal(tp->@tm_mday@ / 10);
	buf[4] = itoa_decimal(tp->@tm_mday@ % 10);
	buf[5] = '/';
	buf[6] = itoa_decimal((tp->@tm_year@ / 10) % 10);
	buf[7] = itoa_decimal(tp->@tm_year@ % 10);
	buf[8] = '\0';
	return buf;
}

[[decl_include("<bits/types.h>"), requires_function(_strtime)]]
[[impl_include("<libc/errno.h>")]]
[[crt_dos_variant({ impl: libd_errno_kos2dos(%[invoke_libc]) })]]
errno_t _strtime_s([[out(? <= bufsize)]] char *buf, size_t bufsize) {
	if unlikely(bufsize < 9) {
@@pp_ifdef ERANGE@@
		return $ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
@@pp_ifdef __BUILDING_LIBC@@
	_strtime(buf);
@@pp_else@@
	if unlikely(!_strtime(buf))
		return __libc_geterrno_or(1);
@@pp_endif@@
	return 0;
}

[[decl_include("<bits/types.h>"), requires_function(_strdate)]]
[[impl_include("<libc/errno.h>")]]
[[crt_dos_variant({ impl: libd_errno_kos2dos(%[invoke_libc]) })]]
errno_t _strdate_s([[out(? <= bufsize)]] char *buf, size_t bufsize) {
	if unlikely(bufsize < 9) {
@@pp_ifdef ERANGE@@
		return $ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
@@pp_ifdef __BUILDING_LIBC@@
	_strdate(buf);
@@pp_else@@
	if unlikely(!_strdate(buf))
		return __libc_geterrno_or(1);
@@pp_endif@@
	return 0;
}

[[nocrt, pure, wunused, alias("timespec_get", "_timespec32_get")]]
[[doc_alias("timespec_get"), decl_include("<features.h>", "<bits/os/timespec.h>")]]
int _timespec32_get([[out]] struct __timespec32 *ts, __STDC_INT_AS_UINT_T base);

%[insert:function(_timespec64_get = timespec_get64)]


%[insert:function(_tzset = tzset)]

[[decl_include("<bits/crt/tm.h>")]]
[[requires_function(gettimeofday64)]]
[[impl_include("<bits/os/timeval.h>")]]
unsigned int _getsystime([[out]] struct $tm *tp) {
	struct timeval64 tv;
	if unlikely(gettimeofday64(&tv, NULL) != 0) {
		tv.@tv_sec@  = 0;
		tv.@tv_usec@ = 0;
	}
	localtime64_r(&tv.@tv_sec@, tp);
	return tv.@tv_usec@ / 1000;
}

[[decl_include("<features.h>", "<bits/crt/tm.h>")]]
[[requires_function(settimeofday64)]]
[[impl_include("<bits/os/timeval.h>")]]
unsigned int _setsystime([[inout]] struct $tm *tp,
                         unsigned int milliseconds) {
	struct timeval64 tv;
	tv.@tv_sec@  = mktime64(tp);
	tv.@tv_usec@ = milliseconds * 1000;
	return (unsigned int)settimeofday64(&tv, NULL);
}


%
%
%{
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
}
%(auto_source){
#undef _mkgmtime
#undef ctime_s
#undef gmtime_s
#undef localtime_s
}

%#endif /* __USE_DOS */

%{

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

}


/* *_nocancel functions */
[[hidden, decl_include("<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("__nanosleep_nocancel")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("__nanosleep64_nocancel")]]
[[requires_include("<bits/os/signal.h>")]]
[[requires(defined(__SIGRPC) && defined(__SIG_BLOCK) && defined(__SIG_SETMASK) &&
           $has_function(nanosleep, sigprocmask))]]
[[impl_include("<bits/os/sigset.h>", "<bits/os/timespec.h>")]]
[[section(".text.crt{|.dos}.compat.glibc")]]
int __nanosleep_nocancel([[in]] struct timespec const *requested_time,
                         [[out_opt]] struct timespec *remaining) {
	fd_t result;
	struct __sigset_struct oss;
	struct __sigset_struct nss;
	(void)sigemptyset(&nss);
	(void)sigaddset(&nss, __SIGRPC);
	result = sigprocmask(__SIG_BLOCK, &nss, &oss);
	if likely(result == 0) {
		result = nanosleep(requested_time, remaining);
		(void)sigprocmask(__SIG_SETMASK, &oss, NULL);
	}
	return result;
}

[[hidden, decl_include("<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(__nanosleep_nocancel), doc_alias("__nanosleep_nocancel")]]
[[requires_include("<bits/os/signal.h>")]]
[[requires(defined(__SIGRPC) && defined(__SIG_BLOCK) && defined(__SIG_SETMASK) &&
           $has_function(nanosleep64, sigprocmask))]]
[[impl_include("<bits/os/sigset.h>", "<bits/os/timespec.h>")]]
[[section(".text.crt{|.dos}.compat.glibc")]]
int __nanosleep64_nocancel([[in]] struct timespec64 const *requested_time,
                           [[out_opt]] struct timespec64 *remaining) {
	fd_t result;
	struct __sigset_struct oss;
	struct __sigset_struct nss;
	(void)sigemptyset(&nss);
	(void)sigaddset(&nss, __SIGRPC);
	result = sigprocmask(__SIG_BLOCK, &nss, &oss);
	if likely(result == 0) {
		result = nanosleep64(requested_time, remaining);
		(void)sigprocmask(__SIG_SETMASK, &oss, NULL);
	}
	return result;
}
