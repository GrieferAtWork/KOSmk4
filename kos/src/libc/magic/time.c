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
%(c_prefix){
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/time.h) */
/* (#) Portability: DJGPP         (/include/time.h) */
/* (#) Portability: FreeBSD       (/include/time.h) */
/* (#) Portability: GNU C Library (/time/time.h) */
/* (#) Portability: MSVC          (/include/time.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/time.h) */
/* (#) Portability: NetBSD        (/include/time.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/time.h) */
/* (#) Portability: OpenBSD       (/include/time.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/time.h) */
/* (#) Portability: Windows Kits  (/ucrt/time.h) */
/* (#) Portability: diet libc     (/include/time.h) */
/* (#) Portability: libc4/5       (/include/time.h) */
/* (#) Portability: libc6         (/include/time.h) */
/* (#) Portability: musl libc     (/include/time.h) */
/* (#) Portability: uClibc        (/include/time.h) */
}

%[define_ccompat_header("ctime")]
%[default:section(".text.crt{|.dos}.time")]

%[define_replacement(time_t    = "__TM_TYPE(time)")]
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
typedef __TM_TYPE(time) time_t;
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



[[ignore, nocrt]]
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[doc_alias("gmtime_r"), alias("_gmtime32_s")]]
$errno_t dos_gmtime32_s([[nonnull]] struct $tm *__restrict tp,
                        [[nonnull]] $time32_t const *__restrict timer);

[[ignore, nocrt]]
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[doc_alias("localtime_r"), alias("_localtime32_s")]]
$errno_t dos_localtime32_s([[nonnull]] struct $tm *__restrict tp,
                           [[nonnull]] $time32_t const *__restrict timer);

@@>> _ctime32_s(3)
@@Equivalent to `asctime_s(buf, bufsize, localtime_r(timer, <tmp>))'
[[ignore, nocrt, decl_include("<bits/types.h>"), alias("_ctime32_s")]]
$errno_t dos_ctime32_s([[nonnull]] char buf[26], $size_t bufsize,
                       [[nonnull]] $time32_t const *__restrict timer);

[[ignore, nocrt, doc_alias("gmtime_r")]]
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("_gmtime32_s")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("_gmtime64_s")]]
[[requires($has_function(dos_gmtime32_s) || $has_function(dos_gmtime64_s))]]
$errno_t dos_gmtime_s([[nonnull]] struct $tm *__restrict tp,
                      [[nonnull]] $time_t const *__restrict timer) {
@@pp_if $has_function(dos_gmtime64_s)@@
	time64_t tm64 = *timer;
	return dos_gmtime64_s(tp, &tm64);
@@pp_else@@
	time32_t tm32 = *timer;
	return dos_gmtime32_s(tp, &tm32);
@@pp_endif@@
}

[[ignore, nocrt, doc_alias("localtime_r")]]
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("_localtime32_s")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("_localtime64_s")]]
[[userimpl, requires($has_function(dos_localtime32_s) || $has_function(dos_localtime64_s))]]
$errno_t dos_localtime_s([[nonnull]] struct $tm *__restrict tp,
                         [[nonnull]] $time_t const *__restrict timer) {
@@pp_if $has_function(dos_localtime64_s)@@
	time64_t tm64 = *timer;
	return dos_localtime64_s(tp, &tm64);
@@pp_else@@
	time32_t tm32 = *timer;
	return dos_localtime32_s(tp, &tm32);
@@pp_endif@@
}

[[ignore, nocrt, decl_include("<bits/types.h>")]]
[[doc_alias("ctime_r"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("_ctime32_s")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("_ctime64_s")]]
[[userimpl, requires($has_function(dos_ctime32_s) || $has_function(dos_ctime64_s))]]
$errno_t dos_ctime_s([[nonnull]] char buf[26], $size_t bufsize,
                     [[nonnull]] $time_t const *__restrict timer) {
@@pp_if $has_function(dos_ctime64_s)@@
	time64_t tm64 = *timer;
	return dos_ctime64_s(tp, &tm64);
@@pp_else@@
	time32_t tm32 = *timer;
	return dos_ctime32_s(tp, &tm32);
@@pp_endif@@
}

[[ignore, nocrt, alias("_gmtime64_s")]]
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[requires_function(dos_gmtime32_s)]]
$errno_t dos_gmtime64_s([[nonnull]] struct $tm *__restrict tp,
                        [[nonnull]] $time64_t const *__restrict timer) {
	time32_t tm32 = *timer;
	return dos_gmtime32_s(tp, &tm32);
}

[[ignore, nocrt, alias("_localtime64_s")]]
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[requires_function(dos_localtime32_s)]]
$errno_t dos_localtime64_s([[nonnull]] struct $tm *__restrict tp,
                           [[nonnull]] $time64_t const *__restrict timer) {
	time32_t tm32 = *timer;
	return dos_localtime32_s(tp, &tm32);
}

[[ignore, nocrt, decl_include("<bits/types.h>")]]
[[alias("_ctime64_s"), doc_alias("dos_ctime32_s")]]
[[requires_function(dos_ctime32_s)]]
$errno_t dos_ctime64_s([[nonnull]] char buf[26], $size_t bufsize,
                       [[nonnull]] $time64_t const *__restrict timer) {
	time32_t tm32 = *timer;
	return dos_ctime32_s(buf, bufsize, &tm64);
}



[[ignore, nocrt, decl_include("<bits/types.h>")]]
[[doc_alias("time"), alias("time", "__time", "__libc_time", "_time32")]]
$time32_t time32([[nullable]] $time32_t *timer);

[[decl_include("<bits/types.h>")]]
[[ignore, nocrt, const, wunused, nothrow]]
[[doc_alias("difftime"), alias("difftime", "_difftime32")]]
double difftime32($time32_t time1, $time32_t time0);

[[ignore, nocrt, wunused]]
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[doc_alias("localtime"), alias("localtime", "_localtime32")]]
[[nonnull]] struct $tm *localtime32([[nonnull]] $time64_t const *timer);

%[define_c_language_keyword(__KOS_FIXED_CONST)];

[[ignore, nocrt, pure, wunused]]
[[decl_include("<features.h>", "<bits/crt/tm.h>")]]
[[doc_alias("mktime"), alias("mktime", "_mktime32", "timelocal")]]
$time32_t mktime32([[nonnull]] struct $tm __KOS_FIXED_CONST *tp);







%[insert:std]

@@>> clock(3)
@@Time used by the program so  far (user time + system  time)
@@The `result / CLOCKS_PER_SECOND' is program time in seconds
[[std, wunused]] clock_t clock();

@@>> time(2), time64(2)
@@Return the current time and put it in `*timer' if `timer' is not `NULL'
[[std, decl_include("<bits/types.h>"), no_crt_self_import, export_as("__time", "__libc_time"), dos_only_export_as("_time32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("time", "__time", "__libc_time", "_time32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("time64", "_time64")]]
[[userimpl, requires($has_function(time32) || $has_function(time64))]]
time_t time(time_t *timer) {
@@pp_if $has_function(time32)@@
	time32_t tm32 = time32(NULL);
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
[[const, wunused, std, guard, decl_include("<bits/types.h>"), no_crt_self_import, dos_only_export_as("_difftime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("difftime", "_difftime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("difftime64", "_difftime64")]]
double difftime(time_t time1, time_t time0) {
@@pp_if $has_function(difftime32) && !defined(__BUILDING_LIBC)@@
	return difftime32((time32_t)time1, (time32_t)time0);
@@pp_elif $has_function(difftime64) && !defined(__BUILDING_LIBC)@@
	return difftime64((time32_t)time1, (time32_t)time0);
@@pp_else@@
	return time1 > time0 ? time1 - time0 : time0 - time1;
@@pp_endif@@
}
%(std)#endif /* !__NO_FPU */



@@>> mktime(3), mktime64(3)
@@Return the `time_t' representation of `tp' and normalize `tp'
[[pure, wunused, std, decl_include("<features.h>", "<bits/types.h>", "<bits/crt/tm.h>"), no_crt_self_import, dos_only_export_as("_mktime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("mktime64", "_mktime64", "timelocal64")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("mktime", "_mktime32", "timelocal")]]
[[impl_prefix(DEFINE_YEARSTODAYS), export_as("timelocal")]]
time_t mktime([[nonnull]] struct tm __KOS_FIXED_CONST *tp) {
@@pp_if $has_function(mktime64) && !defined(__BUILDING_LIBC)@@
	return (time_t)mktime64(tp);
@@pp_elif $has_function(mktime32) && !defined(__BUILDING_LIBC)@@
	return (time_t)mktime32(tp);
@@pp_else@@
	time_t result;
	result = __yearstodays(tp->@tm_year@) - __yearstodays(1970); /* UNIX_TIME_START_YEAR */
	result += tp->@tm_yday@;
	result *= 86400; /* SECONDS_PER_DAY */
	result += tp->@tm_hour@ * 60 * 60;
	result += tp->@tm_min@ * 60;
	result += tp->@tm_sec@;
	return result;
@@pp_endif@@
}



[[ignore, nocrt, wunused]]
[[decl_include("<bits/types.h>")]]
[[doc_alias("ctime"), alias("ctime", "_ctime32")]]
[[nonnull]] char *ctime32([[nonnull]] $time32_t const *timer);

[[ignore, nocrt, wunused]]
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[doc_alias("gmtime"), alias("gmtime", "_gmtime32")]]
[[nonnull]] struct $tm *gmtime32([[nonnull]] $time32_t const *timer);


@@>> ctime(3), ctime64(3)
@@Equivalent to `asctime(localtime(timer))'
[[std, wunused, decl_include("<bits/types.h>"), no_crt_self_import, dos_only_export_alias("_ctime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ctime", "_ctime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ctime64", "_ctime64")]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || (!$has_function(ctime32) && !$has_function(ctime32))@@
DEFINE_CTIME_BUFFER
@@pp_endif@@
)]]
[[nonnull]] char *ctime([[nonnull]] time_t const *timer) {
@@pp_if $has_function(ctime64) && !defined(__BUILDING_LIBC)@@
	time64_t tm64 = (time64_t)*timer;
	return ctime64(&tm64);
@@pp_elif $has_function(ctime32) && !defined(__BUILDING_LIBC)@@
	time32_t tm32 = (time32_t)*timer;
	return ctime32(&tm32);
@@pp_else@@
	return ctime_r(timer, __NAMESPACE_LOCAL_SYM __ctime_buf);
@@pp_endif@@
}


%[define(DEFINE_GMTIME_BUFFER =
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
@@push_namespace(local)@@
__LOCAL_LIBC_DATA(__gmtime_buf) struct tm __gmtime_buf = { 0 };
@@pop_namespace@@
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
)]


@@>> gmtime(3), gmtime64(3)
@@Return  the  `struct tm'  representation  of   `*timer'
@@in Universal Coordinated Time (aka Greenwich Mean Time)
[[std, wunused, decl_include("<bits/types.h>", "<bits/crt/tm.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("gmtime", "_gmtime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("gmtime64", "_gmtime64")]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || (!$has_function(gmtime32) && !$has_function(gmtime64))@@
DEFINE_GMTIME_BUFFER
@@pp_endif@@
)]]
[[nonnull]] struct tm *gmtime([[nonnull]] time_t const *timer) {
@@pp_if $has_function(gmtime64) && !defined(__BUILDING_LIBC)@@
	time64_t tm64 = (time64_t)*timer;
	return gmtime64(&tm64);
@@pp_elif $has_function(gmtime32) && !defined(__BUILDING_LIBC)@@
	time32_t tm32 = (time32_t)*timer;
	return gmtime32(&tm32);
@@pp_else@@
	return gmtime_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
@@pp_endif@@
}


@@>> localtime(3), localtime64(3)
@@Return the `struct tm' representation of `*timer' in the local timezone
[[std, wunused, decl_include("<bits/types.h>", "<bits/crt/tm.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("localtime", "_localtime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("localtime64", "_localtime64")]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || (!$has_function(localtime32) && !$has_function(localtime64))@@
DEFINE_GMTIME_BUFFER
@@pp_endif@@
)]]
[[nonnull]] struct tm *localtime([[nonnull]] time_t const *timer) {
@@pp_if $has_function(localtime64) && !defined(__BUILDING_LIBC)@@
	time64_t tm64 = (time64_t)*timer;
	return localtime64(&tm64);
@@pp_elif $has_function(localtime64) && !defined(__BUILDING_LIBC)@@
	time32_t tm32 = (time32_t)*timer;
	return localtime32(&tm32);
@@pp_else@@
	return localtime_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
@@pp_endif@@
}


[[decl_include("<bits/crt/tm.h>"), doc_alias("strftime_l")]]
[[ignore, nocrt, alias("strftime_l", "_strftime_l", "__strftime_l")]]
$size_t crt_strftime_l([[outp(bufsize)]] char *__restrict buf, $size_t bufsize,
                       [[nonnull]] char const *__restrict format,
                       [[nonnull]] struct $tm const *__restrict tp,
                       $locale_t locale);


@@>> strftime(3)
@@Format `tp' into `s' according to `format'.
@@Write no more than `maxsize' characters and return the number
@@of characters  written, or  0 if  it would  exceed  `maxsize'
[[std, decl_include("<bits/crt/tm.h>"), crtbuiltin, alias("_Strftime")]]
size_t strftime([[outp(bufsize)]] char *__restrict buf, size_t bufsize,
                [[nonnull]] char const *__restrict format,
                [[nonnull]] struct tm const *__restrict tp) {
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

%[define(DEFINE_CTIME_BUFFER =
@@pp_ifndef __LIBC_CTIME_BUFFER_DEFINED@@
#define __LIBC_CTIME_BUFFER_DEFINED 1
@@push_namespace(local)@@
__LOCAL_LIBC_DATA(__ctime_buf) char __ctime_buf[26] = { 0 };
@@pop_namespace@@
@@pp_endif@@
)]

@@>> asctime(3)
@@Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
@@that is  the  representation  of  `tp'  in  this  format
[[std, wunused, impl_prefix(DEFINE_CTIME_BUFFER)]]
[[nonnull]] char *asctime([[nonnull]] struct tm const *tp) {
	return asctime_r(tp, __NAMESPACE_LOCAL_SYM __ctime_buf);
}

%(std)#ifdef __USE_ISOC11
@@>> asctime_s(3)
[[std, guard, impl_include("<libc/errno.h>")]]
$errno_t asctime_s([[outp(buflen)]] char *__restrict buf, size_t buflen,
                   [[nonnull]] struct tm const *__restrict tp) {
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
[[dos_only_export_alias("_time64")]]
[[userimpl, requires_function(time32)]]
$time64_t time64($time64_t *timer) {
	time32_t tm32 = time32(NULL);
	if (timer)
		*timer = (time_t)tm32;
	return (time_t)tm32;
}

%#ifndef __NO_FPU
[[const, wunused, guard, decl_include("<bits/types.h>")]]
[[preferred_time64_variant_of(difftime), doc_alias("difftime")]]
[[dos_only_export_alias("_difftime64"), export_alias("__difftime64")]]
double difftime64($time64_t time1, $time64_t time0) {
@@pp_if $has_function(difftime32) && !defined(__BUILDING_LIBC)@@
	return difftime32((time32_t)time1, (time32_t)time0);
@@pp_else@@
	return time1 > time0 ? time1 - time0 : time0 - time1;
@@pp_endif@@
}
%#endif /* !__NO_FPU */



[[decl_include("<bits/types.h>", "<features.h>")]]
[[preferred_time64_variant_of(mktime), doc_alias("mktime")]]
[[decl_include("<bits/crt/tm.h>"), impl_prefix(
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097*(n_years))/400)/*-1*/) /* rounding error? */
#endif /* !__yearstodays */
), dos_only_export_alias("_mktime64"), export_alias("timelocal64")]]
[[pure, wunused]]
$time64_t mktime64([[nonnull]] struct $tm __KOS_FIXED_CONST *tp) {
@@pp_if $has_function(mktime32) && !defined(__BUILDING_LIBC)@@
	return (time64_t)mktime32(tp);
@@pp_else@@
	time64_t result;
	result = __yearstodays(tp->@tm_year@) - __yearstodays(1970); /* UNIX_TIME_START_YEAR */
	result += tp->@tm_yday@;
	result *= 86400; /* SECONDS_PER_DAY */
	result += tp->@tm_hour@ * 60 * 60;
	result += tp->@tm_min@ * 60;
	result += tp->@tm_sec@;
	return result;
@@pp_endif@@
}

[[decl_include("<bits/types.h>")]]
[[preferred_time64_variant_of(ctime), doc_alias("ctime")]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || !$has_function(ctime32)@@
DEFINE_CTIME_BUFFER
@@pp_endif@@
), wunused, dos_only_export_alias("_ctime64")]]
[[nonnull]] char *ctime64([[nonnull]] $time64_t const *timer) {
@@pp_if $has_function(ctime32) && !defined(__BUILDING_LIBC)@@
	time32_t tm32 = (time32_t)*timer;
	return ctime32(&tm32);
@@pp_else@@
	return ctime64_r(timer, __NAMESPACE_LOCAL_SYM __ctime_buf);
@@pp_endif@@
}

[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[preferred_time64_variant_of(gmtime), doc_alias("gmtime")]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || !$has_function(gmtime32)@@
DEFINE_GMTIME_BUFFER
@@pp_endif@@
), wunused, dos_only_export_alias("_gmtime64")]]
[[nonnull]] struct $tm *gmtime64([[nonnull]] $time64_t const *timer) {
@@pp_if $has_function(gmtime32) && !defined(__BUILDING_LIBC)@@
	time32_t tm32 = (time32_t)*timer;
	return gmtime32(&tm32);
@@pp_else@@
	return gmtime64_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
@@pp_endif@@
}


[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[preferred_time64_variant_of(localtime), doc_alias("localtime")]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || !$has_function(localtime32)@@
DEFINE_GMTIME_BUFFER
@@pp_endif@@
), wunused, dos_only_export_alias("_localtime64")]]
[[nonnull]] struct $tm *localtime64([[nonnull]] $time64_t const *timer) {
@@pp_if $has_function(localtime32) && !defined(__BUILDING_LIBC)@@
	time32_t tm32 = (time32_t)*timer;
	return localtime32(&tm32);
@@pp_else@@
	return localtime64_r(timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
@@pp_endif@@
}

%#endif /* __USE_TIME64 */

%{



#ifndef __tzname
#if defined(__CRT_HAVE_tzname) && !defined(__NO_ASMNAME)
__LIBC char *__tzname[2] __ASMNAME("tzname");
#elif defined(__CRT_HAVE___tzname)
__LIBC char *__tzname[2];
#elif defined(tzname)
#define __tzname tzname
#elif defined(__CRT_HAVE_tzname)
#define __tzname tzname
#ifndef __tzname_defined
#define __tzname_defined
__LIBC char *tzname[2];
#endif /* !__tzname_defined */
#elif defined(__CRT_HAVE_DOS$__tzname)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_CONST,char **,__NOTHROW_NCX,__dos_tzname,(void),__tzname,())
#define __tzname (__dos_tzname())
#endif /* ... */
#endif /* !__tzname */

#ifndef __daylight
#if defined(__CRT_HAVE_daylight) && !defined(__NO_ASMNAME)
__LIBC int __daylight __ASMNAME("daylight");
#elif defined(__CRT_HAVE___daylight)
__LIBC int __daylight;
#elif defined(daylight)
#define __daylight daylight
#elif defined(__CRT_HAVE_daylight)
#define __daylight daylight
#ifndef __daylight_defined
#define __daylight_defined
__LIBC int daylight;
#endif /* !__daylight_defined */
#elif defined(__CRT_HAVE_DOS$__daylight)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_CONST,int *,__NOTHROW_NCX,__dos_daylight,(void),__daylight,())
#define __daylight (*__dos_daylight())
#endif /* ... */
#endif /* !__daylight */

#ifndef __timezone
#if defined(__CRT_HAVE_timezone) && !defined(__NO_ASMNAME)
__LIBC __LONGPTR_TYPE__ __timezone __ASMNAME("timezone");
#elif defined(__CRT_HAVE___timezone)
__LIBC __LONGPTR_TYPE__ __timezone;
#elif defined(timezone)
#define __timezone timezone
#elif defined(__CRT_HAVE_timezone)
#define __timezone timezone
#ifndef __timezone_defined
#define __timezone_defined
__LIBC __LONGPTR_TYPE__ timezone;
#endif /* !__timezone_defined */
#elif defined(__CRT_HAVE_DOS$__timezone)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_CONST,long *,__NOTHROW_NCX,__dos_timezone,(void),__timezone,())
#define __timezone (*__dos_timezone())
#endif /* ... */
#endif /* !__timezone */

}


%{
#ifdef __USE_POSIX
#ifndef __tzname_defined
#define __tzname_defined
#ifndef tzname
#ifdef __CRT_HAVE_tzname
__LIBC char *tzname[2];
#elif defined(__CRT_HAVE___tzname) && !defined(__NO_ASMNAME)
__LIBC char *tzname[2] __ASMNAME("__tzname");
#elif defined(__CRT_HAVE___tzname)
#define tzname __tzname
#elif defined(__CRT_HAVE_DOS$__tzname)
#define tzname (__dos_tzname())
#elif defined(__tzname)
#define tzname __tzname
#else /* ... */
#undef __tzname_defined
#endif /* !... */
#endif /* !tzname */
#endif /* !__tzname_defined */
}

@@>> tzset(3)
@@Set time conversion information from the `$TZ' environment variable.
@@If  `$TZ'  is  not  defined,  a  locale-dependent  default  is  used
[[dos_only_export_alias("_tzset")]]
void tzset();
%#endif /* __USE_POSIX */

%
%{
#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef __daylight_defined
#define __daylight_defined
#ifndef daylight
#ifdef __CRT_HAVE_daylight
__LIBC int daylight;
#elif defined(__CRT_HAVE___daylight) && !defined(__NO_ASMNAME)
__LIBC int daylight __ASMNAME("__daylight");
#elif defined(__CRT_HAVE___daylight)
#define daylight __daylight
#elif defined(__CRT_HAVE_DOS$__daylight)
#define daylight (*__dos_daylight())
#elif defined(__daylight)
#define daylight __daylight
#else /* ... */
#undef __daylight_defined
#endif /* !... */
#endif /* !daylight */
#endif /* !__daylight_defined */

#ifndef __timezone_defined
#define __timezone_defined
#ifndef timezone
#ifdef __CRT_HAVE_timezone
__LIBC __LONGPTR_TYPE__ timezone;
#elif defined(__CRT_HAVE___timezone) && !defined(__NO_ASMNAME)
__LIBC __LONGPTR_TYPE__ timezone __ASMNAME("__timezone");
#elif defined(__CRT_HAVE___timezone)
#define timezone __timezone
#ifdef __struct_timezone_defined
#warning "Please #include <sys/time.h> after <time.h>, else `struct timezone' cannot be used"
#endif /* __struct_timezone_defined */
#elif defined(__CRT_HAVE_DOS$__timezone)
#define timezone (*__dos_timezone())
#ifdef __struct_timezone_defined
#warning "With the linked libc, `struct timezone' from <sys/time.h> cannot be used after <time.h> was included"
#endif /* __struct_timezone_defined */
#elif defined(__timezone)
#define timezone __timezone
#ifdef __struct_timezone_defined
#warning "Please #include <sys/time.h> after <time.h>, else `struct timezone' cannot be used"
#endif /* __struct_timezone_defined */
#else /* ... */
#undef __timezone_defined
#endif /* !... */
#endif /* !timezone */
#endif /* !__timezone_defined */

#endif /* __USE_MISC || __USE_XOPEN */
}


%
%#ifdef __USE_MISC

[[decl_include("<bits/types.h>")]]
[[doc_alias("stime"), ignore, nocrt, alias("stime", "__stime", "__libc_stime")]]
int stime32([[nonnull]] $time32_t const *when);

@@>> stime(2), stime64(2)
@@Set the system time to `*when'. This call is restricted to the superuser
[[guard, decl_include("<bits/types.h>"), no_crt_self_import, export_as("__stime", "__libc_stime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("stime", "__stime", "__libc_stime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("stime64")]]
[[userimpl, requires($has_function(stime32) || $has_function("stime64"))]]
int stime([[nonnull]] $time_t const *when) {
@@pp_if $has_function(stime32)@@
	time32_t tms = (time32_t)*when;
	return stime32(&tms);
@@pp_else@@
	time64_t tms = (time64_t)*when;
	return stime64(&tms);
@@pp_endif@@
}

@@>> timegm(3), timegm64(3)
@@Like `mktime', but `tp' represents Universal Time (UTC), not local time
[[decl_include("<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timegm")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timegm64")]]
[[pure, wunused, decl_include("<bits/crt/tm.h>")]]
$time_t timegm([[nonnull]] struct $tm *tp) {
@@pp_if $has_function(timegm64) && !defined(__BUILDING_LIBC)@@
	return (time_t)timegm64(tp);
@@pp_else@@
	/* TODO: Timezones */
	return mktime(tp);
@@pp_endif@@
}

@@>> timelocal(3), timelocal64(3)
@@Another   name   for   `mktime'
[[pure, wunused, decl_include("<bits/types.h>", "<features.h>")]]
$time_t timelocal([[nonnull]] struct $tm __KOS_FIXED_CONST *tp) = mktime;


%[define(DEFINE_ISLEAP =
#ifndef __isleap
#define __isleap(year) ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
#endif /* !__isleap */
)]

%[define(DEFINE_DAYSTOYEARS =
#ifndef __daystoyears
#define __daystoyears(n_days) ((400 * ((n_days) + 1)) / 146097)
#endif /* !__daystoyears */
)]

%[define(DEFINE_YEARSTODAYS =
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097 * (n_years)) / 400) /*-1*/) /* rounding error? */
#endif /* !__yearstodays */
)]



@@>> dysize(3)
@@Return the number of days in YEAR
[[decl_include("<features.h>")]]
[[const, wunused, impl_prefix(DEFINE_ISLEAP)]]
int dysize(__STDC_INT_AS_UINT_T year) {
	return __isleap(year) ? 366 : 365;
}

%
%#ifdef __USE_TIME64
[[decl_include("<bits/types.h>")]]
[[preferred_time64_variant_of(stime), doc_alias("stime")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__stime", "__libc_stime")]]
[[userimpl, requires_function(stime32)]]
int stime64([[nonnull]] $time64_t const *when) {
	time32_t tms = (time32_t)*when;
	return stime32(&tms);
}

[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[ignore, nocrt, pure, wunused]]
[[doc_alias("timegm"), alias("timegm")]]
$time32_t timegm32([[nonnull]] struct $tm *tp);


[[pure, wunused, decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[preferred_time64_variant_of(timegm), doc_alias("timegm")]]
$time64_t timegm64([[nonnull]] struct $tm *tp) {
@@pp_if $has_function(timegm32) && !defined(__BUILDING_LIBC)@@
	return (time64_t)timegm32(tp);
@@pp_else@@
	/* TODO: Timezones */
	return mktime64(tp);
@@pp_endif@@
}

[[doc_alias("timelocal")]]
timelocal64(*) = mktime64;
%#endif /* __USE_TIME64 */
%#endif /* __USE_MISC */




%
%#ifdef __USE_POSIX199309

[[cp, doc_alias("nanosleep"), ignore, nocrt, alias("nanosleep", "__nanosleep", "__libc_nanosleep")]]
int nanosleep32([[nonnull]] struct timespec const *requested_time,
                [[nullable]] struct $timespec32 *remaining);

@@>> nanosleep(2), nanosleep64(2)
@@Pause execution for a number of nanoseconds
[[cp, decl_include("<bits/os/timespec.h>"), no_crt_self_import, export_as("__nanosleep", "__libc_nanosleep")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("nanosleep", "__nanosleep", "__libc_nanosleep")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("nanosleep64")]]
[[userimpl, requires($has_function(nanosleep32) || $has_function(nanosleep64))]]
int nanosleep([[nonnull]] struct timespec const *requested_time,
              [[nullable]] struct timespec *remaining) {
@@pp_if $has_function(nanosleep32)@@
	int result;
	struct timespec32 req32, rem32;
	req32.tv_sec  = (time32_t)requested_time->tv_sec;
	req32.tv_nsec = requested_time->tv_nsec;
	result = nanosleep32(&req32, &rem32);
	if (!result && remaining) {
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
	if (!result && remaining) {
		remaining->tv_sec  = (time32_t)rem64.tv_sec;
		remaining->tv_nsec = rem64.tv_nsec;
	}
	return result;
@@pp_endif@@
}

[[doc_alias("clock_getres"), decl_include("<bits/os/timespec.h>")]]
[[ignore, nocrt, alias("clock_getres", "__clock_getres")]]
int clock_getres32(clockid_t clock_id, [[nonnull]] struct $timespec32 *res);

@@>> clock_getres(2), clock_getres64(2)
@@Get resolution of clock `clock_id' in `*res'
[[decl_include("<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_getres", "__clock_getres")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_getres64")]]
[[userimpl, requires($has_function(clock_getres32) || $has_function(clock_getres64))]]
[[export_as("__clock_getres")]]
int clock_getres(clockid_t clock_id, [[nonnull]] struct timespec *res) {
@@pp_if $has_function(clock_getres32)@@
	int result;
	struct timespec32 res32;
	result = clock_getres32(clock_id, &res32);
	if (!result) {
		res->tv_sec  = (time64_t)res32.tv_sec;
		res->tv_nsec = res32.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct timespec64 res64;
	result = clock_getres64(clock_id, &res64);
	if (!result) {
		res->tv_sec  = (time32_t)res64.tv_sec;
		res->tv_nsec = res64.tv_nsec;
	}
	return result;
@@pp_endif@@
}

[[decl_include("<bits/os/timespec.h>")]]
[[doc_alias("clock_gettime"), ignore, nocrt, alias("clock_gettime", "__clock_gettime")]]
int clock_gettime32(clockid_t clock_id, [[nonnull]] struct $timespec32 *tp);

@@>> clock_gettime(2), clock_gettime64(2)
@@Get current value of clock `clock_id' and store it in `tp'
[[decl_include("<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_gettime", "__clock_gettime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_gettime64")]]
[[userimpl, requires($has_function(clock_gettime32) || $has_function(clock_gettime64))]]
[[export_as("__clock_gettime")]]
int clock_gettime(clockid_t clock_id, [[nonnull]] struct timespec *tp) {
@@pp_if $has_function(clock_gettime32)@@
	int result;
	struct timespec32 res32;
	result = clock_gettime32(clock_id, &res32);
	if (!result) {
		tp->tv_sec  = (time64_t)res32.tv_sec;
		tp->tv_nsec = res32.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct timespec64 res64;
	result = clock_gettime64(clock_id, &res64);
	if (!result) {
		tp->tv_sec  = (time32_t)res64.tv_sec;
		tp->tv_nsec = res64.tv_nsec;
	}
	return result;
@@pp_endif@@
}



[[ignore, nocrt, decl_include("<bits/os/timespec.h>")]]
[[doc_alias("clock_settime"), alias("clock_settime", "__clock_settime")]]
int clock_settime32(clockid_t clock_id, [[nonnull]] struct $timespec32 const *tp);

@@>> clock_settime(2), clock_settime64(2)
@@Set  clock  `clock_id'  to  value  `tp'
[[decl_include("<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_settime", "__clock_settime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_settime64")]]
[[userimpl, requires($has_function(clock_settime32) || $has_function(clock_settime64))]]
[[export_as("__clock_settime")]]
int clock_settime(clockid_t clock_id, [[nonnull]] struct timespec const *tp) {
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
                 [[nullable]] struct sigevent *__restrict evp,
                 [[nonnull]] timer_t *__restrict timerid);

@@>> timer_delete(2)
@@Delete timer `timerid'
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.timer")]]
int timer_delete(timer_t timerid);

[[ignore, nocrt, alias("timer_settime"), doc_alias("timer_settime")]]
[[decl_include("<features.h>", "<bits/os/itimerspec.h>", "<bits/types.h>")]]
int timer_settime32(timer_t timerid, __STDC_INT_AS_UINT_T flags,
                    [[nonnull]] struct $itimerspec32 const *__restrict value,
                    [[nullable]] struct $itimerspec32 *ovalue);

@@>> timer_settime(2), timer_settime64(2)
@@Set timer `timerid' to `value', returning old value in `ovalue'
[[decl_include("<features.h>", "<bits/os/itimerspec.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timer_settime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timer_settime64")]]
[[userimpl, requires($has_function(timer_settime32) || $has_function(timer_settime64))]]
[[section(".text.crt{|.dos}.timer")]]
int timer_settime(timer_t timerid, __STDC_INT_AS_UINT_T flags,
                  [[nonnull]] struct itimerspec const *__restrict value,
                  [[nullable]] struct itimerspec *__restrict ovalue) {
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
int timer_gettime32(timer_t timerid, [[nonnull]] struct itimerspec *value);

@@>> timer_gettime(2), timer_gettime64(2)
@@Get current value of timer `timerid' and store it in `value'
[[decl_include("<bits/os/itimerspec.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timer_gettime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timer_gettime64")]]
[[userimpl, requires($has_function(timer_gettime32) || $has_function(timer_gettime64))]]
[[section(".text.crt{|.dos}.timer")]]
int timer_gettime(timer_t timerid, [[nonnull]] struct itimerspec *value) {
@@pp_if $has_function(timer_gettime32)@@
	int result;
	struct itimerspec32 value32;
	result = timer_gettime32(timerid, &value32);
	if (!result) {
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
	if (!result) {
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
[[decl_include("<features.h>", "<bits/os/timespec.h>", "<bits/types.h>")]]
[[cp, doc_alias("clock_nanosleep"), ignore, nocrt, alias("clock_nanosleep", "__clock_nanosleep")]]
int clock_nanosleep32(clockid_t clock_id, __STDC_INT_AS_UINT_T flags,
                      [[nonnull]] struct $timespec32 const *__restrict requested_time,
                      [[nullable]] struct $timespec32 *remaining);

@@>> clock_nanosleep(2), clock_nanosleep64(2)
@@High-resolution sleep with the specified clock
[[cp, decl_include("<features.h>", "<bits/os/timespec.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_nanosleep", "__clock_nanosleep")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_nanosleep64")]]
[[userimpl, requires($has_function(clock_nanosleep32) || $has_function(clock_nanosleep64))]]
[[export_as("__clock_nanosleep")]]
int clock_nanosleep(clockid_t clock_id, __STDC_INT_AS_UINT_T flags,
                    [[nonnull]] struct timespec const *__restrict requested_time,
                    [[nullable]] struct timespec *remaining) {
@@pp_if $has_function(clock_nanosleep32)@@
	int result;
	struct timespec32 req32, rem32;
	req32.tv_sec  = (time32_t)requested_time->tv_sec;
	req32.tv_nsec = requested_time->tv_nsec;
	result = clock_nanosleep32(clock_id, flags, &req32, &rem32);
	if (!result && remaining) {
		remaining->tv_sec  = (time64_t)rem32.tv_sec;
		remaining->tv_nsec = rem32.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct timespec64 req64, rem64;
	req64.tv_sec  = (time64_t)requested_time->tv_sec;
	req64.tv_nsec = requested_time->tv_nsec;
	result = clock_nanosleep64(clock_id, flags, &req64, &rem64);
	if (!result && remaining) {
		remaining->tv_sec  = (time32_t)rem64.tv_sec;
		remaining->tv_nsec = rem64.tv_nsec;
	}
	return result;
@@pp_endif@@
}

@@>> clock_getcpuclockid(2)
@@Return clock ID for CPU-time clock
[[decl_include("<bits/types.h>")]]
[[export_alias("__clock_getcpuclockid")]]
int clock_getcpuclockid(pid_t pid, clockid_t *clock_id);
%#endif /* __USE_XOPEN2K */

%
%#ifdef __USE_TIME64
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(nanosleep), doc_alias("nanosleep")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__nanosleep", "__libc_nanosleep")]]
[[userimpl, requires_function(nanosleep32)]]
int nanosleep64([[nonnull]] struct timespec64 const *__restrict requested_time,
                [[nullable]] struct timespec64 *remaining) {
	int result;
	struct timespec32 req32, rem32;
	req32.tv_sec  = (time32_t)requested_time->tv_sec;
	req32.tv_nsec = requested_time->tv_nsec;
	result = nanosleep32(&req32, &rem32);
	if (!result && remaining) {
		remaining->tv_sec  = (time64_t)rem32.tv_sec;
		remaining->tv_nsec = rem32.tv_nsec;
	}
	return result;
}

[[decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(clock_getres), doc_alias("clock_getres")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__clock_getres")]]
[[userimpl, requires($has_function(clock_getres32))]]
int clock_getres64(clockid_t clock_id, [[nonnull]] struct timespec64 *res) {
	int result;
	struct timespec32 res32;
	result = clock_getres32(clock_id, &res32);
	if (!result) {
		res->tv_sec  = (time64_t)res32.tv_sec;
		res->tv_nsec = res32.tv_nsec;
	}
	return result;
}

[[decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(clock_gettime), doc_alias("clock_gettime")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__clock_gettime")]]
[[userimpl, requires_function(clock_gettime32)]]
int clock_gettime64(clockid_t clock_id, [[nonnull]] struct timespec64 *tp) {
	int result;
	struct timespec32 res32;
	result = clock_gettime32(clock_id, &res32);
	if (!result) {
		tp->tv_sec  = (time64_t)res32.tv_sec;
		tp->tv_nsec = res32.tv_nsec;
	}
	return result;
}

[[decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(clock_settime), doc_alias("clock_settime")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__clock_settime")]]
[[userimpl, requires_function(clock_settime32)]]
int clock_settime64(clockid_t clock_id, [[nonnull]] struct timespec64 const *tp) {
	struct timespec32 tp32;
	tp32.tv_sec  = (time32_t)tp->tv_sec;
	tp32.tv_nsec = tp->tv_nsec;
	return clock_settime32(clock_id, &tp32);
}

[[decl_include("<features.h>", "<bits/os/itimerspec.h>", "<bits/types.h>")]]
[[preferred_time64_variant_of(timer_settime), doc_alias("timer_settime")]]
[[userimpl, requires_function(timer_settime32)]]
[[section(".text.crt{|.dos}.timer")]]
int timer_settime64(timer_t timerid, __STDC_INT_AS_UINT_T flags,
                    [[nonnull]] struct itimerspec64 const *__restrict value,
                    [[nullable]] struct itimerspec64 *__restrict ovalue) {
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
[[userimpl, requires_function(timer_gettime32)]]
[[section(".text.crt{|.dos}.timer")]]
int timer_gettime64(timer_t timerid, [[nonnull]] struct itimerspec64 *value) {
	int result;
	struct itimerspec32 value32;
	result = timer_gettime32(timerid, &value32);
	if (!result) {
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
[[userimpl, requires_function(clock_nanosleep32)]]
int clock_nanosleep64(clockid_t clock_id, __STDC_INT_AS_UINT_T flags,
                      [[nonnull]] struct timespec64 const *requested_time,
                      [[nullable]] struct timespec64 *remaining) {
	int result;
	struct timespec32 req32, rem32;
	req32.tv_sec  = (time32_t)requested_time->tv_sec;
	req32.tv_nsec = requested_time->tv_nsec;
	result = clock_nanosleep32(clock_id, flags, &req32, &rem32);
	if (!result && remaining) {
		remaining->tv_sec  = (time64_t)rem32.tv_sec;
		remaining->tv_nsec = rem32.tv_nsec;
	}
	return result;
}
%#endif /* __USE_XOPEN2K */
%#endif /* __USE_TIME64 */
%#endif /* __USE_POSIX199309 */


%
%(c,std)#ifdef __USE_ISOCXX17
@@>> timespec_get(3), timespec_get64(3)
@@Set `ts' to calendar time based in time base `base'
[[std, guard, decl_include("<features.h>", "<bits/os/timespec.h>"), no_crt_self_import, dos_only_export_alias("_timespec32_get")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timespec_get", "_timespec32_get")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timespec_get64", "_timespec64_get")]]
[[requires_include("<asm/os/clock.h>", "<asm/crt/time.h>")]]
[[requires(defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && $has_function(clock_gettime))]]
int timespec_get([[nonnull]] struct timespec *ts,
                 __STDC_INT_AS_UINT_T base) {
	if (base == __TIME_UTC) {
		if (clock_gettime(__CLOCK_REALTIME, ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}

%#ifdef __USE_TIME64
[[decl_include("<features.h>", "<bits/os/timespec.h>"), dos_only_export_alias("_timespec64_get")]]
[[preferred_time64_variant_of(timespec_get), doc_alias("timespec_get")]]
[[requires_include("<asm/os/clock.h>", "<asm/crt/time.h>")]]
[[requires(defined(__CLOCK_REALTIME) && defined(__TIME_UTC) && $has_function(clock_gettime64))]]
int timespec_get64([[nonnull]] struct timespec64 *ts,
                   __STDC_INT_AS_UINT_T base) {
	if (base == __TIME_UTC) {
		if (clock_gettime64(__CLOCK_REALTIME, ts) == 0)
			return __TIME_UTC;
	}
	/* Unsupported base... */
	return 0;
}
%#endif /* __USE_TIME64 */

%(c,std)#endif /* __USE_ISOCXX17 */

%
%/* timespec_get() is defined by both c11 and c++17 */
%#ifdef __USE_ISOC11
%[insert:extern(timespec_get)]
%#endif /* __USE_ISOC11 */



%
%#ifdef __USE_XOPEN_EXTENDED
%/* Set to one of the following values to indicate an error.
%     1  the DATEMSK environment variable is null or undefined,
%     2  the template file cannot be opened for reading,
%     3  failed to get file status information,
%     4  the template file is not a regular file,
%     5  an error is encountered while reading the template file,
%     6  memory allication failed (not enough memory available),
%     7  there is no line in the template that matches the input,
%     8  invalid input specification Example: February 31 or a time is
%        specified that can not be represented in a time_t (representing
%        the time in seconds since 00:00:00 UTC, January 1, 1970) */
%#ifdef __CRT_HAVE_getdate_err
%__LIBC int getdate_err;
%#endif /* __CRT_HAVE_getdate_err */

@@>> getdate(3)
@@Parse the given string as a date specification and return a value
@@representing the value. The templates from the file identified by
@@the environment variable `$DATEMSK' are used. In case of an error
@@`getdate_err' is set
[[decl_include("<bits/crt/tm.h>")]]
struct $tm *getdate([[nonnull]] const char *string);
%#endif /* __USE_XOPEN_EXTENDED */

%
%#ifdef __USE_GNU
%[insert:extern(getdate_r)]
%#endif /* __USE_GNU */







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
[[decl_include("<bits/crt/tm.h>")]]
[[dos_only_export_alias("_strftime_l"), export_alias("__strftime_l")]]
$size_t strftime_l([[outp(bufsize)]] char *__restrict buf, $size_t bufsize,
                   [[nonnull]] char const *__restrict format,
                   [[nonnull]] struct $tm const *__restrict tp, $locale_t locale) {
	(void)locale;
	return strftime(buf, bufsize, format, tp);
}
%#endif /* __USE_XOPEN2K8 */


[[ignore, nocrt, alias("strptime_l")]]
[[decl_include("<bits/crt/tm.h>"), doc_alias("strptime_l")]]
char *crt_strptime_l([[nonnull]] char const *__restrict s,
                     [[nonnull]] char const *__restrict format,
                     [[nonnull]] struct $tm *__restrict tp,
                     $locale_t locale);


%
%#ifdef __USE_XOPEN
@@>> strptime(3)
@@Parse `s' according to `format' and store binary time information in `tp'.
@@The return  value is  a pointer  to the  first unparsed  character in  `s'
[[decl_include("<bits/crt/tm.h>")]]
char *strptime([[nonnull]] char const *__restrict s,
               [[nonnull]] char const *__restrict format,
               [[nonnull]] struct $tm *__restrict tp) {
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
char *strptime_l([[nonnull]] char const *__restrict s,
                 [[nonnull]] char const *__restrict format,
                 [[nonnull]] struct $tm *__restrict tp,
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
[[guard, decl_include("<bits/crt/tm.h>")]]
int getdate_r([[nonnull]] char const *__restrict string,
              [[nonnull]] struct $tm *__restrict resbufp) {
	/* TODO */
	(void)string;
	(void)resbufp;
	COMPILER_IMPURE();
	return 0;
}

@@>> clock_adjtime(2), clock_adjtime64(2)
[[guard, no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_adjtime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("clock_adjtime64")]]
int clock_adjtime($clockid_t clock_id, struct timex *utx);

%
%#ifdef __USE_TIME64
[[guard]]
[[preferred_time64_variant_of(clock_adjtime), doc_alias("clock_adjtime")]]
int clock_adjtime64($clockid_t clock_id, struct timex64 *utx);
%#endif /* __USE_TIME64 */

%#endif /* __USE_GNU */



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





%
%#ifdef __USE_POSIX

@@>> gmtime_r(3), gmtime64_r(3)
@@Return the `struct tm' representation of `*timer' in UTC, using `*tp' to store the result
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[impl_prefix(
@@pp_ifdef __BUILDING_LIBC@@
DEFINE_ISLEAP
DEFINE_DAYSTOYEARS
DEFINE_YEARSTODAYS
DEFINE_TIME_MONTHSTART_YDAY
@@pp_endif@@
), export_alias("__gmtime_r")]]
struct $tm *gmtime_r([[nonnull]] $time_t const *__restrict timer,
                     [[nonnull]] struct $tm *__restrict tp) {
@@pp_ifdef __BUILDING_LIBC@@
	time_t t; int i;
	u16 const *monthvec;
	t = *timer;
	tp->@tm_sec@  = (int)(t % 60);
	tp->@tm_min@  = (int)((t / 60) % 60);
	tp->@tm_hour@ = (int)((t / (60 * 60)) % 24);
	t /= 86400; /* SECONDS_PER_DAY */
	t += __yearstodays(1970); /* UNIX_TIME_START_YEAR */
	tp->@tm_wday@ = (int)(t % 7); /* DAYS_PER_WEEK */
	tp->@tm_year@ = (int)__daystoyears(t);
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
@@pp_elif $has_function(dos_gmtime_s)@@
	return dos_gmtime_s(tp, timer) ? NULL : tp;
@@pp_elif defined(__USE_TIME_BITS64)@@
	return gmtime64_r(timer, tp);
@@pp_else@@
	time64_t tm64 = (time64_t)*timer;
	return gmtime64_r(&tm64, tp);
@@pp_endif@@
}

@@>> localtime_r(3), localtime64_r(3)
@@Return the `struct tm' representation of `*timer' in local time, using `*tp' to store the result
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
struct $tm *localtime_r([[nonnull]] $time_t const *__restrict timer,
                        [[nonnull]] struct $tm *__restrict tp) {
@@pp_ifdef __BUILDING_LIBC@@
	/* XXX: Timezone support? */
	return gmtime_r(timer, tp);
@@pp_elif $has_function(dos_localtime_s)@@
	return dos_localtime_s(tp, timer) ? NULL : tp;
@@pp_elif defined(__USE_TIME_BITS64)@@
	return localtime64_r(timer, tp);
@@pp_else@@
	time64_t tm64 = (time64_t)*timer;
	return localtime64_r(&tm64, tp);
@@pp_endif@@
}

@@>> ctime_r(3), ctime64_r(3)
@@Equivalent to `asctime_r(localtime_r(timer, <tmp>), buf)'
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
char *ctime_r([[nonnull]] $time_t const *__restrict timer,
              [[nonnull]] char buf[26]) {
@@pp_if $has_function(dos_ctime_s) && !defined(__BUILDING_LIBC)@@
	return dos_ctime_s(buf, 26, timer) ? NULL : __buf;
@@pp_else@@
	struct tm ltm;
	return asctime_r(localtime_r(timer, &ltm), buf);
@@pp_endif@@
}

%
%#ifdef __USE_TIME64

[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[preferred_time64_variant_of(gmtime_r), doc_alias("gmtime_r")]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || !$has_function(dos_gmtime64_s)@@
DEFINE_TIME_MONTHSTART_YDAY
@@pp_endif@@
)]]
[[impl_prefix(DEFINE_ISLEAP)]]
[[impl_prefix(DEFINE_DAYSTOYEARS)]]
[[impl_prefix(DEFINE_YEARSTODAYS)]]
struct $tm *gmtime64_r([[nonnull]] $time64_t const *__restrict timer,
                       [[nonnull]] struct $tm *__restrict tp) {
@@pp_if $has_function(dos_gmtime64_s) && !defined(__BUILDING_LIBC)@@
	return dos_gmtime64_s(tp, timer) ? NULL : tp;
@@pp_else@@
	time64_t t; int i;
	u16 const *monthvec;
	t = *timer;
	tp->@tm_sec@  = (int)(t % 60);
	tp->@tm_min@  = (int)((t / 60) % 60);
	tp->@tm_hour@ = (int)((t / (60 * 60)) % 24);
	t /= 86400; /* SECONDS_PER_DAY */
	t += __yearstodays(1970); /* UNIX_TIME_START_YEAR */
	tp->@tm_wday@ = (int)(t % 7); /* DAYS_PER_WEEK */
	tp->@tm_year@ = (int)__daystoyears(t);
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
@@pp_endif@@
}

[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[preferred_time64_variant_of(localtime_r), doc_alias("localtime_r")]]
struct $tm *localtime64_r([[nonnull]] $time64_t const *__restrict timer,
                          [[nonnull]] struct $tm *__restrict tp) {
@@pp_if $has_function(dos_localtime64_s) && !defined(__BUILDING_LIBC)@@
	return dos_localtime64_s(tp, timer) ? NULL : tp;
@@pp_else@@
	/* XXX: Timezone support? */
	return gmtime64_r(timer, tp);
@@pp_endif@@
}

[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
[[preferred_time64_variant_of(ctime_r), doc_alias("ctime_r")]]
char *ctime64_r([[nonnull]] $time64_t const *__restrict timer,
                [[nonnull]] char buf[26]) {
@@pp_if $has_function(dos_ctime64_s) && !defined(__BUILDING_LIBC)@@
	return dos_ctime64_s(buf, 26, timer) ? NULL : __buf;
@@pp_else@@
	struct tm ltm;
	return asctime_r(localtime64_r(timer, &ltm), buf);
@@pp_endif@@
}
%#endif /* __USE_TIME64 */

[[ignore, nocrt, decl_include("<bits/crt/tm.h>")]]
[[doc_alias("asctime_r"), alias("asctime_s")]]
$errno_t crt_asctime_s([[outp(buflen)]] char *__restrict buf, $size_t buflen,
                       [[nonnull]] struct $tm const *__restrict tp);

%[define(DEFINE_TIME_ABBR_WDAY_NAMES =
#ifndef __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED
#define __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED 1
@@push_namespace(local)@@
__LOCAL_LIBC_CONST_DATA(__abbr_wday_names) char const __abbr_wday_names[7][4] =
	{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
@@pop_namespace@@
#endif /* !__LIBC_TIME_ABBR_WDAY_NAMES_DEFINED */
)]

%[define(DEFINE_TIME_ABBR_MONTH_NAMES =
#ifndef __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED
#define __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED 1
@@push_namespace(local)@@
__LOCAL_LIBC_CONST_DATA(__abbr_month_names) char const __abbr_month_names[12][4] =
	{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
@@pop_namespace@@
#endif /* !__LIBC_TIME_ABBR_MONTH_NAMES_DEFINED */
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
char *asctime_r([[nonnull]] struct $tm const *__restrict tp,
                [[nonnull]] char buf[26]) {
@@pp_if $has_function(crt_asctime_s) && !defined(__BUILDING_LIBC)@@
	return crt_asctime_s(buf, 26, tp) ? NULL : buf;
@@pp_else@@
	sprintf(buf,
	        "%.3s %.3s%3u %.2u:%.2u:%.2u %u\n",
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


%{

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_TIME_H)
#include <parts/uchar/time.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_TIME_H */
#endif /* __USE_UTF */

}
