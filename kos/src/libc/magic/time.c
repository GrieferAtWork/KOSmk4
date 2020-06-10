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

%[define_ccompat_header("ctime")]
%[default_impl_section(".text.crt.time")]

%[define_replacement(time_t    = "__TM_TYPE(time)")]
%[define_replacement(time32_t  = __time32_t)]
%[define_replacement(time64_t  = __time64_t)]
%[define_replacement(clock_t   = __typedef_clock_t)]
%[define_replacement(pid_t     = __pid_t)]
%[define_replacement(clockid_t = __clockid_t)]
%[define_replacement(timer_t   = __timer_t)]

%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(timeval32  = __timeval32)]
%[define_replacement(timeval64  = __timeval64)]
%[define_replacement(itimerspec32 = __itimerspec32)]
%[define_replacement(itimerspec64 = __itimerspec64)]


%{
#include <features.h>
#include <bits/time.h>
#include <bits/types.h>

#ifdef __USE_POSIX199309
#include <bits/timespec.h>
#include <bits/itimerval.h>
#endif /* __USE_POSIX199309 */

#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */


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
#define MSEC_PER_SEC    1000l
#define USEC_PER_MSEC   1000l
#define NSEC_PER_USEC   1000l
#define NSEC_PER_MSEC   1000000l
#define USEC_PER_SEC    1000000l
#define NSEC_PER_SEC    1000000000l
#define FSEC_PER_SEC    1000000000000000ll
#endif

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

#if defined(__USE_DOS) || \
  (!defined(__USE_XOPEN2K) && !defined(__USE_ISOC_PURE) && !defined(__STRICT_ANSI__))
#ifndef CLK_TCK
#define CLK_TCK CLOCKS_PER_SEC
#endif /* !CLK_TCK */
#endif /* __USE_DOS || (!__USE_XOPEN2K && !__USE_ISOC_PURE && !__STRICT_ANSI__) */


#ifdef __CC__

__NAMESPACE_STD_BEGIN
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__std_size_t_defined */
#ifndef __std_clock_t_defined
#define __std_clock_t_defined 1
typedef __typedef_clock_t clock_t;
#endif /* !__std_clock_t_defined */
#ifndef __std_time_t_defined
#define __std_time_t_defined 1
typedef __TM_TYPE(time) time_t;
#endif /* !__std_time_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
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
}%{
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


/* Used by other time functions.  */
#ifndef __std_tm_defined
#define __std_tm_defined 1
__NAMESPACE_STD_BEGIN
#ifdef __tm_defined
__NAMESPACE_GLB_USING(tm)
#else /* __tm_defined */
struct tm {
	int         tm_sec;      /* seconds [0, 61]. */
	int         tm_min;      /* minutes [0, 59]. */
	int         tm_hour;     /* hour [0, 23]. */
	int         tm_mday;     /* day of month [1, 31]. */
	int         tm_mon;      /* month of year [0, 11]. */
	int         tm_year;     /* years since 1900. */
	int         tm_wday;     /* day of week [0, 6] (Sunday = 0). */
	int         tm_yday;     /* day of year [0, 365]. */
	int         tm_isdst;    /* daylight savings flag. */
#ifdef __CRT_GLC
#ifdef __USE_MISC
	__LONGPTR_TYPE__ tm_gmtoff;   /* Seconds east of UTC. */
	char const      *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	__LONGPTR_TYPE__ __tm_gmtoff; /* Seconds east of UTC. */
	char const      *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* __CRT_GLC */
};
#endif /* !__tm_defined */
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */

#ifndef __STRUCT_TM
#define __STRUCT_TM struct __NAMESPACE_STD_SYM tm
#endif /* !__STRUCT_TM */

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __tm_defined
#define __tm_defined 1
#undef __STRUCT_TM
#define __STRUCT_TM struct tm
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */



#ifdef __USE_POSIX199309
struct sigevent;
#endif /* __USE_POSIX199309 */

}

%[define_replacement(tm = "__NAMESPACE_STD_SYM tm")];

%[define(DEFINE_STRUCT_TM =
#ifndef __STRUCT_TM
#ifdef __tm_defined
#define __STRUCT_TM struct tm
#else /* __tm_defined */
#define __STRUCT_TM struct __NAMESPACE_STD_SYM tm
#ifndef __std_tm_defined
#define __std_tm_defined 1
__NAMESPACE_STD_BEGIN
struct tm {
	int         tm_sec;      /* seconds [0, 61]. */
	int         tm_min;      /* minutes [0, 59]. */
	int         tm_hour;     /* hour [0, 23]. */
	int         tm_mday;     /* day of month [1, 31]. */
	int         tm_mon;      /* month of year [0, 11]. */
	int         tm_year;     /* years since 1900. */
	int         tm_wday;     /* day of week [0, 6] (Sunday = 0). */
	int         tm_yday;     /* day of year [0, 365]. */
	int         tm_isdst;    /* daylight savings flag. */
#ifdef __CRT_GLC
#ifdef __USE_MISC
	__LONGPTR_TYPE__ tm_gmtoff;   /* Seconds east of UTC. */
	char const      *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	__LONGPTR_TYPE__ __tm_gmtoff; /* Seconds east of UTC. */
	char const      *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* __CRT_GLC */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
)]



[[doc_alias("gmtime_r"), decl_prefix(DEFINE_STRUCT_TM)]]
[[ignore, nocrt, alias("_gmtime32_s")]]
$errno_t dos_gmtime32_s([[nonnull]] __STRUCT_TM *__restrict tp,
                        [[nonnull]] $time32_t const *__restrict timer);

[[doc_alias("localtime_r"), decl_prefix(DEFINE_STRUCT_TM)]]
[[ignore, nocrt, alias("_localtime32_s")]]
$errno_t dos_localtime32_s([[nonnull]] __STRUCT_TM *__restrict tp,
                           [[nonnull]] $time32_t const *__restrict timer);

@@Equivalent to `asctime_s(buf, bufsize, localtime_r(timer, *TMP*))'
[[ignore, nocrt, alias("_ctime32_s")]]
$errno_t dos_ctime32_s([[nonnull]] char buf[26], $size_t bufsize,
                       [[nonnull]] $time32_t const *__restrict timer);

[[ignore, nocrt, doc_alias("gmtime_r"), decl_prefix(DEFINE_STRUCT_TM)]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("_gmtime32_s")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("_gmtime64_s")]]
[[requires($has_function(dos_gmtime32_s) || $has_function(dos_gmtime64_s))]]
$errno_t dos_gmtime_s([[nonnull]] __STRUCT_TM *__restrict tp,
                      [[nonnull]] $time_t const *__restrict timer) {
@@pp_if $has_function(dos_gmtime64_s)@@
	time64_t tm64 = *timer;
	return dos_gmtime64_s(tp, &tm64);
@@pp_else@@
	time32_t tm32 = *timer;
	return dos_gmtime32_s(tp, &tm32);
@@pp_endif@@
}

[[ignore, nocrt, doc_alias("localtime_r"), decl_prefix(DEFINE_STRUCT_TM)]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("_localtime32_s")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("_localtime64_s")]]
[[userimpl, requires($has_function(dos_localtime32_s) || $has_function(dos_localtime64_s))]]
$errno_t dos_localtime_s([[nonnull]] __STRUCT_TM *__restrict tp,
                         [[nonnull]] $time_t const *__restrict timer) {
@@pp_if $has_function(dos_localtime64_s)@@
	time64_t tm64 = *timer;
	return dos_localtime64_s(tp, &tm64);
@@pp_else@@
	time32_t tm32 = *timer;
	return dos_localtime32_s(tp, &tm32);
@@pp_endif@@
}

[[ignore, nocrt, doc_alias("ctime_r"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("_ctime32_s")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("_ctime64_s")]]
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

[[ignore, nocrt, alias("_gmtime64_s"), decl_prefix(DEFINE_STRUCT_TM)]]
[[requires_function(dos_gmtime32_s)]]
$errno_t dos_gmtime64_s([[nonnull]] __STRUCT_TM *__restrict tp,
                        [[nonnull]] $time64_t const *__restrict timer) {
	time32_t tm32 = *timer;
	return dos_gmtime32_s(tp, &tm32);
}

[[ignore, nocrt, alias("_localtime64_s"), decl_prefix(DEFINE_STRUCT_TM)]]
[[requires_function(dos_localtime32_s)]]
$errno_t dos_localtime64_s([[nonnull]] __STRUCT_TM *__restrict tp,
                           [[nonnull]] $time64_t const *__restrict timer) {
	time32_t tm32 = *timer;
	return dos_localtime32_s(tp, &tm32);
}

[[ignore, nocrt, alias("_ctime64_s"), doc_alias("dos_ctime32_s")]]
[[requires_function(dos_ctime32_s)]]
$errno_t dos_ctime64_s([[nonnull]] char buf[26], $size_t bufsize,
                       [[nonnull]] $time64_t const *__restrict timer) {
	time32_t tm32 = *timer;
	return dos_ctime32_s(buf, bufsize, &tm64);
}



[[doc_alias("time"), ignore, nocrt, alias("time", "_time32")]]
$time32_t time32([[nullable]] $time32_t *timer);

[[ATTR_WUNUSED, ATTR_CONST, nothrow, doc_alias("difftime")]]
[[ignore, nocrt, alias("difftime", "_difftime32")]]
double difftime32($time32_t time1, $time32_t time0);

[[ATTR_WUNUSED, decl_prefix(DEFINE_STRUCT_TM), doc_alias("localtime")]]
[[ignore, nocrt, alias("localtime", "_localtime32")]]
[[nonnull]] __STRUCT_TM *localtime32([[nonnull]] $time64_t const *timer);

%[define_c_language_keyword(__KOS_FIXED_CONST)];

[[decl_prefix(DEFINE_STRUCT_TM)]]
[[ATTR_PURE, ATTR_WUNUSED, doc_alias(mktime)]]
[[ignore, nocrt, alias("mktime", "_mktime32", "timelocal")]]
$time32_t mktime32([[nonnull]] __STRUCT_TM __KOS_FIXED_CONST *tp);







%[insert:std]

@@Time used by the program so far (user time + system time)
@@The result / CLOCKS_PER_SECOND is program time in seconds
[[std, ATTR_WUNUSED]] clock_t clock();

@@Return the current time and put it in *TIMER if TIMER is not NULL
[[std, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("time64", "_time64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("time", "_time32")]]
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
@@Return the difference between TIME1 and TIME0
[[ATTR_WUNUSED, ATTR_CONST, std, guard, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("difftime64", "_difftime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("difftime", "_difftime32")]]
double difftime(time_t time1, time_t time0) {
@@pp_ifdef __BUILDING_LIBC@@
	return time1 > time0 ? time1 - time0 : time0 - time1;
@@pp_elif $has_function(difftime32)@@
	return difftime32((time32_t)time1, (time32_t)time0);
@@pp_elif $has_function(difftime64)@@
	return difftime64((time32_t)time1, (time32_t)time0);
@@pp_else@@
	return time1 > time0 ? time1 - time0 : time0 - time1;
@@pp_endif@@
}
%(std)#endif /* !__NO_FPU */



@@Return the `time_t' representation of TP and normalize TP
[[ATTR_WUNUSED, ATTR_PURE, std]]
[[decl_prefix(DEFINE_STRUCT_TM), impl_prefix(DEFINE_YEARSTODAYS), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("mktime64", "_mktime64", "timelocal64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("mktime", "_mktime32", "timelocal")]]
time_t mktime([[nonnull]] __STRUCT_TM __KOS_FIXED_CONST *tp) {
@@pp_ifdef __BUILDING_LIBC@@
	__TM_TYPE(@time@) result;
	result = @__yearstodays@(tp->@tm_year@) - @__yearstodays@(1970); /* LINUX_TIME_START_YEAR */
	result += tp->@tm_yday@;
	result *= 86400; /* SECONDS_PER_DAY */
	result += tp->@tm_hour@*60*60;
	result += tp->@tm_min@*60;
	result += tp->@tm_sec@;
	return result;
@@pp_elif $has_function(mktime64)@@
	return (time_t)mktime64(tp);
@@pp_elif $has_function(mktime32)@@
	return (time_t)mktime32(tp);
@@pp_else@@
	__TM_TYPE(@time@) result;
	result = @__yearstodays@(tp->@tm_year@) - @__yearstodays@(1970); /* LINUX_TIME_START_YEAR */
	result += tp->@tm_yday@;
	result *= 86400; /* SECONDS_PER_DAY */
	result += tp->@tm_hour@*60*60;
	result += tp->@tm_min@*60;
	result += tp->@tm_sec@;
	return result;
@@pp_endif@@
}



[[ATTR_WUNUSED, doc_alias("ctime")]]
[[ignore, nocrt, alias("ctime", "_ctime32")]]
[[nonnull]] char *ctime32([[nonnull]] $time32_t const *timer);

[[ATTR_WUNUSED, doc_alias("gmtime"), decl_prefix(DEFINE_STRUCT_TM)]]
[[ignore, nocrt, alias("gmtime", "_gmtime32")]]
[[nonnull]] __STRUCT_TM *gmtime32([[nonnull]] $time32_t const *timer);


@@Equivalent to `asctime(localtime(timer))'
[[std, impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || (!$has_function(ctime32) && !$has_function(ctime32))@@
DEFINE_CTIME_BUFFER
@@pp_endif@@
), ATTR_WUNUSED, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("ctime64", "_ctime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("ctime", "_ctime32")]]
[[nonnull]] char *ctime([[nonnull]] time_t const *timer) {
@@pp_ifdef __BUILDING_LIBC@@
	return ctime_r(timer, @__ctime_buf@);
@@pp_elif $has_function(ctime64)@@
	time64_t tm64 = (time64_t)*timer;
	return ctime64(&tm64);
@@pp_elif $has_function(ctime32)@@
	time32_t tm32 = (time32_t)*timer;
	return ctime32(&tm32);
@@pp_else@@
	return ctime_r(timer, @__ctime_buf@);
@@pp_endif@@
}


%[define(DEFINE_GMTIME_BUFFER =
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK __STRUCT_TM __gmtime_buf = {0};
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY __STRUCT_TM __gmtime_buf = {0};
#else
__PRIVATE __ATTR_UNUSED __STRUCT_TM __gmtime_buf = {0};
#endif
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
)]


@@Return the `struct tm' representation of *TIMER
@@in Universal Coordinated Time (aka Greenwich Mean Time)
[[std, decl_prefix(DEFINE_STRUCT_TM)]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || (!$has_function(gmtime32) && !$has_function(gmtime64))@@
DEFINE_GMTIME_BUFFER
@@pp_endif@@
), ATTR_WUNUSED, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("gmtime64", "_gmtime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("gmtime", "_gmtime32")]]
[[nonnull]] struct tm *gmtime([[nonnull]] time_t const *timer) {
@@pp_ifdef __BUILDING_LIBC@@
	return gmtime_r(timer, &@__gmtime_buf@);
@@pp_elif $has_function(gmtime64)@@
	time64_t tm64 = (time64_t)*timer;
	return gmtime64(&tm64);
@@pp_elif $has_function(gmtime32)@@
	time32_t tm32 = (time32_t)*timer;
	return gmtime32(&tm32);
@@pp_else@@
	return gmtime_r(timer, &@__gmtime_buf@);
@@pp_endif@@
}


@@Return the `struct tm' representation of *TIMER in the local timezone
[[std, decl_prefix(DEFINE_STRUCT_TM)]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || (!$has_function(localtime32) && !$has_function(localtime64))@@
DEFINE_GMTIME_BUFFER
@@pp_endif@@
), ATTR_WUNUSED, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("localtime64", "_localtime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("localtime", "_localtime32")]]
[[nonnull]] struct tm *localtime([[nonnull]] time_t const *timer) {
@@pp_ifdef __BUILDING_LIBC@@
	return localtime_r(timer, &@__gmtime_buf@);
@@pp_elif $has_function(localtime64)@@
	time64_t tm64 = (time64_t)*timer;
	return localtime64(&tm64);
@@pp_elif $has_function(localtime64)@@
	time32_t tm32 = (time32_t)*timer;
	return localtime32(&tm32);
@@pp_else@@
	return localtime_r(timer, &@__gmtime_buf@);
@@pp_endif@@
}


@@Similar to `strftime' but take the information from
@@the provided locale and not the global locale
[[decl_prefix(DEFINE_STRUCT_TM)]]
[[ignore, nocrt, alias("strftime_l", "_strftime_l", "__strftime_l")]]
$size_t crt_strftime_l([[outp(bufsize)]] char *__restrict buf, $size_t bufsize,
                       [[nonnull]] char const *__restrict format,
                       [[nonnull]] __STRUCT_TM const *__restrict tp,
                       $locale_t locale);


@@Format TP into S according to FORMAT.
@@Write no more than MAXSIZE characters and return the number
@@of characters written, or 0 if it would exceed MAXSIZE
[[std, decl_prefix(DEFINE_STRUCT_TM), crtbuiltin, alias("_Strftime")]]
size_t strftime([[outp(bufsize)]] char *__restrict buf, size_t bufsize,
                [[nonnull]] char const *__restrict format,
                [[nonnull]] __STRUCT_TM const *__restrict tp) {
@@pp_ifdef __BUILDING_LIBC@@
	/* TODO */
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)tp;
	COMPILER_IMPURE();
	return 0;
@@pp_elif $has_function(crt_strftime_l)@@
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
#ifndef __LIBC_CTIME_BUFFER_DEFINED
#define __LIBC_CTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK char __ctime_buf[26] = {0};
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY char __ctime_buf[26] = {0};
#else
__PRIVATE __ATTR_UNUSED char __ctime_buf[26] = {0};
#endif
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_CTIME_BUFFER_DEFINED */
)]

@@Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
@@that is the representation of TP in this format
[[std, ATTR_WUNUSED, impl_prefix(DEFINE_CTIME_BUFFER)]]
[[nonnull]] char *asctime([[nonnull]] struct tm const *tp) {
	return asctime_r(tp, @__ctime_buf@);
}

%(std)#ifdef __USE_ISOC11
[[std, guard, impl_include("<parts/errno.h>")]]
$errno_t asctime_s([[outp(buflen)]] char *__restrict buf, size_t buflen,
                   [[nonnull]] struct tm const *__restrict tp) {
	if (buflen < 26)
		return __ERANGE;
	asctime_r(tp, buf);
	return 0;
}
%(std)#endif /* __USE_ISOC11 */




%#ifdef __USE_TIME64
[[doc_alias("time"), time64_variant_of(time), export_alias("_time64")]]
[[userimpl, requires_function(time32)]]
$time64_t time64($time64_t *timer) {
	time32_t tm32 = time32(NULL);
	if (timer)
		*timer = (time_t)tm32;
	return (time_t)tm32;
}

%#ifndef __NO_FPU
[[ATTR_WUNUSED, ATTR_CONST, guard, doc_alias("difftime"), time64_variant_of(difftime)]]
[[export_alias("_difftime64", "__difftime64")]]
double difftime64($time64_t time1, $time64_t time0) {
@@pp_ifdef __BUILDING_LIBC@@
	return time1 > time0 ? time1 - time0 : time0 - time1;
@@pp_elif $has_function(difftime32)@@
	return difftime32((time32_t)time1, (time32_t)time0);
@@pp_else@@
	return time1 > time0 ? time1 - time0 : time0 - time1;
@@pp_endif@@
}
%#endif /* !__NO_FPU */



[[doc_alias("mktime"), time64_variant_of(mktime)]]
[[decl_prefix(DEFINE_STRUCT_TM), impl_prefix(
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097*(n_years))/400)/*-1*/) /* rounding error? */
#endif /* !__yearstodays */
), export_alias("_mktime64", "timelocal64")]]
[[ATTR_WUNUSED, ATTR_PURE]]
$time64_t mktime64([[nonnull]] __STRUCT_TM __KOS_FIXED_CONST *tp) {
@@pp_ifdef __BUILDING_LIBC@@
	time64_t result;
	result = @__yearstodays@(tp->@tm_year@) - @__yearstodays@(1970); /* LINUX_TIME_START_YEAR */
	result += tp->@tm_yday@;
	result *= 86400; /* SECONDS_PER_DAY */
	result += tp->@tm_hour@*60*60;
	result += tp->@tm_min@*60;
	result += tp->@tm_sec@;
	return result;
@@pp_elif $has_function(mktime32)@@
	return (time64_t)mktime32(tp);
@@pp_else@@
	time64_t result;
	result = @__yearstodays@(tp->@tm_year@) - @__yearstodays@(1970); /* LINUX_TIME_START_YEAR */
	result += tp->@tm_yday@;
	result *= 86400; /* SECONDS_PER_DAY */
	result += tp->@tm_hour@*60*60;
	result += tp->@tm_min@*60;
	result += tp->@tm_sec@;
	return result;
@@pp_endif@@
}

[[doc_alias("ctime"), time64_variant_of(ctime), impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || !$has_function(ctime32)@@
DEFINE_CTIME_BUFFER
@@pp_endif@@
), ATTR_WUNUSED, export_alias("_ctime64")]]
[[nonnull]] char *ctime64([[nonnull]] $time64_t const *timer) {
@@pp_ifdef __BUILDING_LIBC@@
	return ctime64_r(timer, @__ctime_buf@);
@@pp_elif $has_function(ctime32)@@
	time32_t tm32 = (time32_t)*timer;
	return ctime32(&tm32);
@@pp_else@@
	return ctime64_r(timer, @__ctime_buf@);
@@pp_endif@@
}

[[doc_alias("gmtime"), time64_variant_of(gmtime)]]
[[decl_prefix(DEFINE_STRUCT_TM)]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || !$has_function(gmtime32)@@
DEFINE_GMTIME_BUFFER
@@pp_endif@@
), ATTR_WUNUSED, export_alias("_gmtime64")]]
[[nonnull]] __STRUCT_TM *gmtime64([[nonnull]] $time64_t const *timer) {
@@pp_ifdef __BUILDING_LIBC@@
	return gmtime64_r(timer, &@__gmtime_buf@);
@@pp_elif $has_function(gmtime32)@@
	time32_t tm32 = (time32_t)*timer;
	return gmtime32(&tm32);
@@pp_else@@
	return gmtime64_r(timer, &@__gmtime_buf@);
@@pp_endif@@
}


[[doc_alias("localtime"), time64_variant_of(localtime)]]
[[decl_prefix(DEFINE_STRUCT_TM)]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || !$has_function(localtime32)@@
DEFINE_GMTIME_BUFFER
@@pp_endif@@
), ATTR_WUNUSED, export_alias("_localtime64")]]
[[nonnull]] __STRUCT_TM *localtime64([[nonnull]] $time64_t const *timer) {
@@pp_ifdef __BUILDING_LIBC@@
	return localtime64_r(timer, &@__gmtime_buf@);
@@pp_elif $has_function(localtime32)@@
	time32_t tm32 = (time32_t)*timer;
	return localtime32(&tm32);
@@pp_else@@
	return localtime64_r(timer, &@__gmtime_buf@);
@@pp_endif@@
}

%#endif /* __USE_TIME64 */

%{



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

}


%{
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
}

@@Set time conversion information from the TZ environment variable.
@@If TZ is not defined, a locale-dependent default is used
void tzset();
%#endif /* __USE_POSIX */

%
%{
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
}


%
%#ifdef __USE_MISC

[[doc_alias("stime"), ignore, nocrt, alias("stime")]]
int stime32([[nonnull]] $time32_t const *when);

@@Set the system time to *WHEN. This call is restricted to the superuser
[[no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("stime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("stime")]]
[[requires($has_function(stime32) || $has_function("stime64"))]]
int stime([[nonnull]] $time_t const *when) {
@@pp_if $has_function(stime32)@@
	time32_t tms = (time32_t)*when;
	return stime32(&tms);
@@pp_else@@
	time64_t tms = (time64_t)*when;
	return stime64(&tms);
@@pp_endif@@
}

@@Like `mktime', but TP represents Universal Time (UTC), not local time
[[no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("timegm64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("timegm")]]
[[ATTR_WUNUSED, ATTR_PURE, decl_prefix(DEFINE_STRUCT_TM)]]
$time_t timegm([[nonnull]] __STRUCT_TM *tp) {
@@pp_ifdef __BUILDING_LIBC@@
	/* TODO: Timezones */
	return mktime(tp);
@@pp_elif $has_function(timegm64)@@
	return (time_t)timegm64(tp);
@@pp_else@@
	/* TODO: Timezones */
	return mktime(tp);
@@pp_endif@@
}

@@Another name for `mktime'
[[ATTR_WUNUSED, ATTR_PURE]]
$time_t timelocal([[nonnull]] __STRUCT_TM __KOS_FIXED_CONST *tp) = mktime;


%[define(DEFINE_ISLEAP =
#ifndef __isleap
#define __isleap(year) ((year)%4 == 0 && ((year)%100 != 0 || (year)%400 == 0))
#endif /* !__isleap */
)]

%[define(DEFINE_DAYSTOYEARS =
#ifndef __daystoyears
#define __daystoyears(n_days)  ((400*((n_days)+1))/146097)
#endif /* !__daystoyears */
)]

%[define(DEFINE_YEARSTODAYS =
#ifndef __yearstodays
#define __yearstodays(n_years) (((146097*(n_years))/400)/*-1*/) /* rounding error? */
#endif /* !__yearstodays */
)]



@@Return the number of days in YEAR
[[ATTR_CONST, ATTR_WUNUSED, impl_prefix(DEFINE_ISLEAP)]]
int dysize(__STDC_INT_AS_UINT_T year) {
	return __isleap(year) ? 366 : 365;
}

%
%#ifdef __USE_TIME64
[[doc_alias("stime"), time64_variant_of(stime), userimpl, requires_function(stime32)]]
int stime64([[nonnull]] $time64_t const *when) {
	time32_t tms = (time32_t)*when;
	return stime32(&tms);
}

[[ATTR_WUNUSED, ATTR_PURE, doc_alias("timegm"), decl_prefix(DEFINE_STRUCT_TM)]]
[[ignore, nocrt, alias("timegm")]]
$time32_t timegm32([[nonnull]] __STRUCT_TM *tp);


[[decl_prefix(DEFINE_STRUCT_TM)]]
[[ATTR_WUNUSED, ATTR_PURE, doc_alias("timegm"), time64_variant_of(timegm)]]
$time64_t timegm64([[nonnull]] __STRUCT_TM *tp) {
@@pp_ifdef __BUILDING_LIBC@@
	/* TODO: Timezones */
	return mktime64(tp);
@@pp_elif $has_function(timegm32)@@
	return (time64_t)timegm32(tp);
@@pp_else@@
	/* TODO: Timezones */
	return mktime64(tp);
@@pp_endif@@
}

@@Another name for `mktime64'
timelocal64(*) = mktime64;
%#endif /* __USE_TIME64 */
%#endif /* __USE_MISC */




%
%#ifdef __USE_POSIX199309

[[cp, doc_alias("nanosleep"), ignore, nocrt, alias("nanosleep", "__nanosleep")]]
int nanosleep32([[nonnull]] struct timespec const *requested_time,
                [[nullable]] struct $timespec32 *remaining);

@@Pause execution for a number of nanoseconds
[[cp, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("nanosleep64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("nanosleep")]]
[[userimpl, requires($has_function(nanosleep32) || $has_function(nanosleep64))]]
[[export_alias("__nanosleep")]]
int nanosleep([[nonnull]] struct timespec const *requested_time,
              [[nullable]] struct timespec *remaining) {
@@pp_if $has_function(nanosleep32)@@
	int result;
	struct timespec32 req32, rem32;
	req32.tv_sec  = (__time32_t)requested_time->tv_sec;
	req32.tv_nsec = requested_time->tv_nsec;
	result = nanosleep32(&req32, &rem32);
	if (!result && remaining) {
		remaining->tv_sec  = (__time64_t)rem32.tv_sec;
		remaining->tv_nsec = rem32.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct timespec64 req64, rem64;
	req64.tv_sec  = (__time64_t)requested_time->tv_sec;
	req64.tv_nsec = requested_time->tv_nsec;
	result = nanosleep64(&req64, &rem64);
	if (!result && remaining) {
		remaining->tv_sec  = (__time32_t)rem64.tv_sec;
		remaining->tv_nsec = rem64.tv_nsec;
	}
	return result;
@@pp_endif@@
}

[[doc_alias("clock_getres")]]
[[ignore, nocrt, alias("clock_getres", "__clock_getres")]]
int clock_getres32(clockid_t clock_id, [[nonnull]] struct $timespec32 *res);

@@Get resolution of clock CLOCK_ID
[[no_crt_self_import, export_as("__clock_getres")]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("clock_getres64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("clock_getres", "__clock_getres")]]
[[userimpl, requires($has_function(clock_getres32) || $has_function(clock_getres64))]]
int clock_getres(clockid_t clock_id, [[nonnull]] struct timespec *res) {
@@pp_if $has_function(clock_getres32)@@
	int result;
	struct timespec32 res32;
	result = clock_getres32(clock_id, &res32);
	if (!result) {
		res->tv_sec  = (__time64_t)res32.tv_sec;
		res->tv_nsec = res32.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct timespec64 res64;
	result = clock_getres64(clock_id, &res64);
	if (!result) {
		res->tv_sec  = (__time32_t)res64.tv_sec;
		res->tv_nsec = res64.tv_nsec;
	}
	return result;
@@pp_endif@@
}

[[doc_alias("clock_gettime"), ignore, nocrt, alias("clock_gettime", "__clock_gettime")]]
int clock_gettime32(clockid_t clock_id, [[nonnull]] struct $timespec32 *tp);

@@Get current value of clock CLOCK_ID and store it in TP
[[no_crt_self_import, export_as("__clock_gettime")]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("clock_gettime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("clock_gettime", "__clock_gettime")]]
[[userimpl, requires($has_function(clock_gettime32) || $has_function(clock_gettime64))]]
int clock_gettime(clockid_t clock_id, [[nonnull]] struct timespec *tp) {
@@pp_if $has_function(clock_gettime32)@@
	int result;
	struct timespec32 res32;
	result = clock_gettime32(clock_id, &res32);
	if (!result) {
		tp->tv_sec  = (__time64_t)res32.tv_sec;
		tp->tv_nsec = res32.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct timespec64 res64;
	result = clock_gettime64(clock_id, &res64);
	if (!result) {
		tp->tv_sec  = (__time32_t)res64.tv_sec;
		tp->tv_nsec = res64.tv_nsec;
	}
	return result;
@@pp_endif@@
}



[[doc_alias(clock_settime), ignore, nocrt, alias("clock_settime", "__clock_settime")]]
int clock_settime32(clockid_t clock_id, [[nonnull]] struct $timespec32 const *tp);

@@Set clock CLOCK_ID to value TP
[[no_crt_self_import, export_as(__clock_settime)]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("clock_settime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("clock_settime", "__clock_settime")]]
[[userimpl, requires($has_function(clock_settime32) || $has_function(clock_settime64))]]
int clock_settime(clockid_t clock_id, [[nonnull]] struct timespec const *tp) {
@@pp_if $has_function(clock_settime32)@@
	struct timespec32 tp32;
	tp32.tv_sec  = (__time32_t)tp->tv_sec;
	tp32.tv_nsec = tp->tv_nsec;
	return clock_settime32(clock_id, &tp32);
@@pp_else@@
	struct timespec64 tp64;
	tp64.tv_sec  = (__time64_t)tp->tv_sec;
	tp64.tv_nsec = tp->tv_nsec;
	return clock_settime64(clock_id, &tp64);
@@pp_endif@@
}


@@Create new per-process timer using CLOCK_ID
[[section(".text.crt.timer")]]
int timer_create(clockid_t clock_id,
                 [[nullable]] struct sigevent *__restrict evp,
                 [[nonnull]] timer_t *__restrict timerid);

@@Delete timer TIMERID
[section(".text.crt.timer")]
int timer_delete(timer_t timerid);

@@Set timer TIMERID to VALUE, returning old value in OVALUE
[[decl_include("<bits/itimerspec.h>"), ignore, nocrt, alias("timer_settime")]]
int timer_settime32(timer_t timerid, __STDC_INT_AS_UINT_T flags,
                    [[nonnull]] struct $itimerspec32 const *__restrict value,
                    [[nullable]] struct $itimerspec32 *ovalue);

@@Set timer TIMERID to VALUE, returning old value in OVALUE
[[no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("timer_settime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("timer_settime")]]
[[userimpl, requires($has_function(timer_settime32) || $has_function(timer_settime64))]]
[[section(".text.crt.timer"), decl_include("<bits/itimerspec.h>")]]
int timer_settime(timer_t timerid, __STDC_INT_AS_UINT_T flags,
                  [[nonnull]] struct itimerspec const *__restrict value,
                  [[nullable]] struct itimerspec *__restrict ovalue) {
@@pp_if $has_function(timer_settime32)@@
	int result;
	struct $itimerspec32 value32, ovalue32;
	value32.it_interval.tv_sec  = (__time32_t)value->it_interval.tv_sec;
	value32.it_interval.tv_nsec = value->it_interval.tv_nsec;
	value32.it_value.tv_sec     = (__time32_t)value->it_value.tv_sec;
	value32.it_value.tv_nsec    = value->it_value.tv_nsec;
	result = timer_settime32(timerid, flags, &value32, ovalue ? &ovalue32 : NULL);
	if (!result && ovalue) {
		ovalue->it_interval.tv_sec  = (__time64_t)ovalue32.it_interval.tv_sec;
		ovalue->it_interval.tv_nsec = ovalue32.it_interval.tv_nsec;
		ovalue->it_value.tv_sec     = (__time64_t)ovalue32.it_value.tv_sec;
		ovalue->it_value.tv_nsec    = ovalue32.it_value.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct $itimerspec64 value64, ovalue64;
	value64.it_interval.tv_sec  = (__time64_t)value->it_interval.tv_sec;
	value64.it_interval.tv_nsec = value->it_interval.tv_nsec;
	value64.it_value.tv_sec     = (__time64_t)value->it_value.tv_sec;
	value64.it_value.tv_nsec    = value->it_value.tv_nsec;
	result = timer_settime64(timerid, flags, &value64, ovalue ? &ovalue64 : NULL);
	if (!result && ovalue) {
		ovalue->it_interval.tv_sec  = (__time32_t)ovalue64.it_interval.tv_sec;
		ovalue->it_interval.tv_nsec = ovalue64.it_interval.tv_nsec;
		ovalue->it_value.tv_sec     = (__time32_t)ovalue64.it_value.tv_sec;
		ovalue->it_value.tv_nsec    = ovalue64.it_value.tv_nsec;
	}
	return result;
@@pp_endif@@
}

[[decl_include("<bits/itimerspec.h>"), doc_alias("timer_gettime"), ignore, nocrt, alias("timer_gettime")]]
int timer_gettime32(timer_t timerid, [[nonnull]] struct itimerspec *value);

@@Get current value of timer TIMERID and store it in VALUE
[[no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("timer_gettime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("timer_gettime")]]
[[requires($has_function(timer_gettime32) || $has_function(timer_gettime64))]]
[[section(".text.crt.timer"), decl_include("<bits/itimerspec.h>")]]
int timer_gettime(timer_t timerid, [[nonnull]] struct itimerspec *value) {
@@pp_if $has_function(timer_gettime32)@@
	int result;
	struct $itimerspec32 value32;
	result = timer_gettime32(timerid, &value32);
	if (!result) {
		value->it_interval.tv_sec  = (__time64_t)value32.it_interval.tv_sec;
		value->it_interval.tv_nsec = value32.it_interval.tv_nsec;
		value->it_value.tv_sec     = (__time64_t)value32.it_value.tv_sec;
		value->it_value.tv_nsec    = value32.it_value.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct $itimerspec64 value64;
	result = timer_gettime64(timerid, &value64);
	if (!result) {
		value->it_interval.tv_sec  = (__time32_t)value64.it_interval.tv_sec;
		value->it_interval.tv_nsec = value64.it_interval.tv_nsec;
		value->it_value.tv_sec     = (__time32_t)value64.it_value.tv_sec;
		value->it_value.tv_nsec    = value64.it_value.tv_nsec;
	}
	return result;
@@pp_endif@@
}

@@Get expiration overrun for timer TIMERID
[[section(".text.crt.timer")]]
int timer_getoverrun(timer_t timerid);

%
%#ifdef __USE_XOPEN2K
[[cp, doc_alias("clock_nanosleep"), ignore, nocrt, alias("clock_nanosleep", "__clock_nanosleep")]]
int clock_nanosleep32(clockid_t clock_id, __STDC_INT_AS_UINT_T flags,
                      [[nonnull]] struct $timespec32 const *__restrict requested_time,
                      [[nullable]] struct $timespec32 *remaining);

@@High-resolution sleep with the specified clock
[[cp, no_crt_self_import, export_as("__clock_nanosleep")]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("clock_nanosleep64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("clock_nanosleep", "__clock_nanosleep")]]
[[userimpl, requires($has_function(clock_nanosleep32) || $has_function(clock_nanosleep64))]]
int clock_nanosleep(clockid_t clock_id, __STDC_INT_AS_UINT_T flags,
                    [[nonnull]] struct timespec const *__restrict requested_time,
                    [[nullable]] struct timespec *remaining) {
@@pp_if $has_function(clock_nanosleep32)@@
	int result;
	struct @__timespec32 @req32, rem32;
	req32.tv_sec  = (__time32_t)requested_time->tv_sec;
	req32.tv_nsec = requested_time->tv_nsec;
	result = clock_nanosleep32(clock_id, flags, &req32, &rem32);
	if (!result && remaining) {
		remaining->tv_sec  = (__time64_t)rem32.tv_sec;
		remaining->tv_nsec = rem32.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct @__timespec64 @req64, rem64;
	req64.tv_sec  = (__time64_t)requested_time->tv_sec;
	req64.tv_nsec = requested_time->tv_nsec;
	result = clock_nanosleep64(clock_id, flags, &req64, &rem64);
	if (!result && remaining) {
		remaining->tv_sec  = (__time32_t)rem64.tv_sec;
		remaining->tv_nsec = rem64.tv_nsec;
	}
	return result;
@@pp_endif@@
}

@@Return clock ID for CPU-time clock
[[export_alias("__clock_getcpuclockid")]]
int clock_getcpuclockid(pid_t pid, clockid_t *clock_id);
%#endif /* __USE_XOPEN2K */

%
%#ifdef __USE_TIME64
[[cp, doc_alias("nanosleep"), time64_variant_of(nanosleep)]]
[[userimpl, requires_function(nanosleep32)]]
int nanosleep64([[nonnull]] struct timespec64 const *__restrict requested_time,
                [[nullable]] struct timespec64 *remaining) {
	int result;
	struct timespec32 req32, rem32;
	req32.tv_sec  = (__time32_t)requested_time->tv_sec;
	req32.tv_nsec = requested_time->tv_nsec;
	result = nanosleep32(&req32, &rem32);
	if (!result && remaining) {
		remaining->tv_sec  = (__time64_t)rem32.tv_sec;
		remaining->tv_nsec = rem32.tv_nsec;
	}
	return result;
}

[[doc_alias("clock_getres"), time64_variant_of(clock_getres)]]
[[userimpl, requires($has_function(clock_getres32))]]
int clock_getres64(clockid_t clock_id, [[nonnull]] struct timespec64 *res) {
	int result;
	struct timespec32 res32;
	result = clock_getres32(clock_id, &res32);
	if (!result) {
		res->tv_sec  = (__time64_t)res32.tv_sec;
		res->tv_nsec = res32.tv_nsec;
	}
	return result;
}

[[doc_alias("clock_gettime"), time64_variant_of(clock_gettime)]]
[[userimpl, requires_function(clock_gettime32)]]
int clock_gettime64(clockid_t clock_id, [[nonnull]] struct timespec64 *tp) {
	int result;
	struct timespec32 res32;
	result = clock_gettime32(clock_id, &res32);
	if (!result) {
		tp->tv_sec  = (__time64_t)res32.tv_sec;
		tp->tv_nsec = res32.tv_nsec;
	}
	return result;
}

[[doc_alias("clock_settime"), time64_variant_of(clock_settime)]]
[[userimpl, requires_function(clock_settime32)]]
int clock_settime64(clockid_t clock_id, [[nonnull]] struct timespec64 const *tp) {
	struct timespec32 tp32;
	tp32.tv_sec  = (__time32_t)tp->tv_sec;
	tp32.tv_nsec = tp->tv_nsec;
	return clock_settime32(clock_id, &tp32);
}

[[decl_include("<bits/itimerspec.h>")]]
[[doc_alias("timer_settime"), time64_variant_of(timer_settime), section(".text.crt.timer")]]
[[userimpl, requires_function(timer_settime32)]]
int timer_settime64(timer_t timerid, __STDC_INT_AS_UINT_T flags,
                    [[nonnull]] struct itimerspec64 const *__restrict value,
                    [[nullable]] struct itimerspec64 *__restrict ovalue) {
	int result;
	struct $itimerspec32 value32, ovalue32;
	value32.it_interval.tv_sec  = (__time32_t)value->it_interval.tv_sec;
	value32.it_interval.tv_nsec = value->it_interval.tv_nsec;
	value32.it_value.tv_sec     = (__time32_t)value->it_value.tv_sec;
	value32.it_value.tv_nsec    = value->it_value.tv_nsec;
	result = timer_settime32(timerid, flags, &value32, ovalue ? &ovalue32 : NULL);
	if (!result && ovalue) {
		ovalue->it_interval.tv_sec  = (__time64_t)ovalue32.it_interval.tv_sec;
		ovalue->it_interval.tv_nsec = ovalue32.it_interval.tv_nsec;
		ovalue->it_value.tv_sec     = (__time64_t)ovalue32.it_value.tv_sec;
		ovalue->it_value.tv_nsec    = ovalue32.it_value.tv_nsec;
	}
	return result;
}

[[decl_include("<bits/itimerspec.h>")]]
[[doc_alias("timer_gettime"), time64_variant_of(timer_gettime), section(".text.crt.timer")]]
[[userimpl, requires_function(timer_gettime32)]]
int timer_gettime64(timer_t timerid, [[nonnull]] struct itimerspec64 *value) {
	int result;
	struct $itimerspec32 value32;
	result = timer_gettime32(timerid, &value32);
	if (!result) {
		value->it_interval.tv_sec  = (__time64_t)value32.it_interval.tv_sec;
		value->it_interval.tv_nsec = value32.it_interval.tv_nsec;
		value->it_value.tv_sec     = (__time64_t)value32.it_value.tv_sec;
		value->it_value.tv_nsec    = value32.it_value.tv_nsec;
	}
	return result;
}

%
%#ifdef __USE_XOPEN2K
[[cp, doc_alias("clock_nanosleep"), time64_variant_of(clock_nanosleep)]]
[[userimpl, requires_function(clock_nanosleep32)]]
int clock_nanosleep64(clockid_t clock_id, __STDC_INT_AS_UINT_T flags,
                      [[nonnull]] struct timespec64 const *requested_time,
                      [[nullable]] struct timespec64 *remaining) {
	int result;
	struct timespec32 req32, rem32;
	req32.tv_sec  = (__time32_t)requested_time->tv_sec;
	req32.tv_nsec = requested_time->tv_nsec;
	result = clock_nanosleep32(clock_id, flags, &req32, &rem32);
	if (!result && remaining) {
		remaining->tv_sec  = (__time64_t)rem32.tv_sec;
		remaining->tv_nsec = rem32.tv_nsec;
	}
	return result;
}
%#endif /* __USE_XOPEN2K */
%#endif /* __USE_TIME64 */
%#endif /* __USE_POSIX199309 */


%
%(c,std)#ifdef __USE_ISOCXX17
@@Set TS to calendar time based in time base BASE
[[std, guard]]
int timespec_get([[nonnull]] struct timespec *ts,
                 __STDC_INT_AS_UINT_T base);
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

%
@@Parse the given string as a date specification and return a value
@@representing the value.  The templates from the file identified by
@@the environment variable DATEMSK are used.  In case of an error
@@`getdate_err' is set
[[decl_prefix(DEFINE_STRUCT_TM)]]
__STRUCT_TM *getdate([[nonnull]] const char *string);
%#endif /* __USE_XOPEN_EXTENDED */

%
%#ifdef __USE_GNU
%[insert:extern(getdate_r)]
%#endif /* __USE_GNU */







%(user)INTDEF char *libc_tzname[2];
%(user)INTDEF int libc_daylight;
%(user)INTDEF longptr_t libc_timezone;


%
%#ifdef __USE_XOPEN2K8

@@Similar to `strftime' but take the information from
@@the provided locale and not the global locale
[[decl_prefix(DEFINE_STRUCT_TM), export_alias("_strftime_l", "__strftime_l")]]
$size_t strftime_l([[outp(bufsize)]] char *__restrict buf, $size_t bufsize,
                   [[nonnull]] char const *__restrict format,
                   [[nonnull]] __STRUCT_TM const *__restrict tp, $locale_t locale) {
	(void)locale;
	return strftime(buf, bufsize, format, tp);
}
%#endif /* __USE_XOPEN2K8 */


[[decl_prefix(DEFINE_STRUCT_TM), doc_alias("strptime_l"), ignore, nocrt, alias("strptime_l")]]
char *crt_strptime_l([[nonnull]] char const *__restrict s,
                     [[nonnull]] char const *__restrict format,
                     [[nonnull]] __STRUCT_TM *__restrict tp,
                     $locale_t locale);


%
%#ifdef __USE_XOPEN
@@Parse S according to FORMAT and store binary time information in TP.
@@The return value is a pointer to the first unparsed character in S
[[decl_prefix(DEFINE_STRUCT_TM)]]
char *strptime([[nonnull]] char const *__restrict s,
               [[nonnull]] char const *__restrict format,
               [[nonnull]] __STRUCT_TM *__restrict tp) {
@@pp_ifdef __BUILDING_LIBC@@
	/* TODO */
	(void)s;
	(void)format;
	(void)tp;
	COMPILER_IMPURE();
	return NULL;
@@pp_elif $has_function(crt_strptime_l)@@
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
@@Similar to `strptime' but take the information from
@@the provided locale and not the global locale
[[decl_prefix(DEFINE_STRUCT_TM)]]
char *strptime_l([[nonnull]] char const *__restrict s,
                 [[nonnull]] char const *__restrict format,
                 [[nonnull]] __STRUCT_TM *__restrict tp,
                 $locale_t locale) {
	(void)locale;
	return strptime(s, format, tp);
}

@@Since `getdate' is not reentrant because of the use of `getdate_err'
@@and the static buffer to return the result in, we provide a thread-safe
@@variant.  The functionality is the same.  The result is returned in
@@the buffer pointed to by RESBUFP and in case of an error the return
@@value is != 0 with the same values as given above for `getdate_err'.
[[guard, decl_prefix(DEFINE_STRUCT_TM)]]
int getdate_r([[nonnull]] char const *__restrict string,
              [[nonnull]] __STRUCT_TM *__restrict resbufp) {
	/* TODO */
	(void)string;
	(void)resbufp;
	COMPILER_IMPURE();
	return 0;
}
%#endif /* __USE_GNU */



%
%#ifdef __USE_POSIX

@@Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result
[[decl_prefix(DEFINE_STRUCT_TM)]]
[[impl_prefix(
@@pp_ifdef __BUILDING_LIBC@@
DEFINE_ISLEAP
DEFINE_DAYSTOYEARS
DEFINE_YEARSTODAYS
DEFINE_TIME_MONTHSTART_YDAY
@@pp_endif@@
), export_alias("__gmtime_r")]]
__STRUCT_TM *gmtime_r([[nonnull]] $time_t const *__restrict timer,
                      [[nonnull]] __STRUCT_TM *__restrict tp) {
@@pp_ifdef __BUILDING_LIBC@@
	time_t t; int i;
	u16 const *monthvec;
	t = *timer;
	tp->@tm_sec@  = (int)(t % 60);
	tp->@tm_min@  = (int)((t/60) % 60);
	tp->@tm_hour@ = (int)((t/(60*60)) % 24);
	t /= 86400; /* SECONDS_PER_DAY */
	t += __yearstodays(1970); /* LINUX_TIME_START_YEAR */
	tp->@tm_wday@ = (int)(t % 7); /* DAYS_PER_WEEK */
	tp->@tm_year@ = (int)__daystoyears(t);
	t -= __yearstodays(tp->@tm_year@);
	tp->@tm_yday@ = (int)t;
	monthvec = @__time_monthstart_yday@[__isleap(tp->@tm_year@)];
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
			//That means the previous Sunday must be before the 1st.
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

@@Return the `struct tm' representation of *TIMER in local time, using *TP to store the result
[[decl_prefix(DEFINE_STRUCT_TM)]]
__STRUCT_TM *localtime_r([[nonnull]] $time_t const *__restrict timer,
                         [[nonnull]] __STRUCT_TM *__restrict tp) {
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

@@Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)'
[[decl_prefix(DEFINE_STRUCT_TM)]]
char *ctime_r([[nonnull]] $time_t const *__restrict timer,
              [[nonnull]] char buf[26]) {
@@pp_ifdef __BUILDING_LIBC@@
	struct tm ltm;
	return asctime_r(localtime_r(timer, &ltm), buf);
@@pp_elif $has_function(dos_ctime_s)@@
	return dos_ctime_s(buf, 26, timer) ? NULL : __buf;
@@pp_else@@
	struct tm ltm;
	return asctime_r(localtime_r(timer, &ltm), buf);
@@pp_endif@@
}

%
%#ifdef __USE_TIME64

%[define(DEFINE_TIME_MONTHSTART_YDAY =
#ifndef ____TIME_MONTHSTART_YDAY_DEFINED
#define ____TIME_MONTHSTART_YDAY_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN_CONST __ATTR_UNUSED __ATTR_WEAK __UINT16_TYPE__ const __time_monthstart_yday[2][13] =
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN_CONST __ATTR_UNUSED __ATTR_SELECTANY __UINT16_TYPE__ const __time_monthstart_yday[2][13] =
#else
__PRIVATE __ATTR_UNUSED __UINT16_TYPE__ const __time_monthstart_yday[2][13] =
#endif
{
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};
__NAMESPACE_LOCAL_END
#endif /* !____TIME_MONTHSTART_YDAY_DEFINED */
)]


[[doc_alias("gmtime_r"), time64_variant_of(gmtime_r)]]
[[decl_prefix(DEFINE_STRUCT_TM)]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || !$has_function(dos_gmtime64_s)@@
DEFINE_TIME_MONTHSTART_YDAY
@@pp_endif@@
)]]
[[impl_prefix(DEFINE_ISLEAP)]]
[[impl_prefix(DEFINE_DAYSTOYEARS)]]
[[impl_prefix(DEFINE_YEARSTODAYS)]]
__STRUCT_TM *gmtime64_r([[nonnull]] $time64_t const *__restrict timer,
                        [[nonnull]] __STRUCT_TM *__restrict tp) {
@@pp_ifdef __BUILDING_LIBC@@
	time_t t; int i;
	u16 const *monthvec;
	t = *timer;
	tp->@tm_sec@  = (int)(t % 60);
	tp->@tm_min@  = (int)((t/60) % 60);
	tp->@tm_hour@ = (int)((t/(60*60)) % 24);
	t /= 86400; /* SECONDS_PER_DAY */
	t += __yearstodays(1970); /* LINUX_TIME_START_YEAR */
	tp->@tm_wday@ = (int)(t % 7); /* DAYS_PER_WEEK */
	tp->@tm_year@ = (int)__daystoyears(t);
	t -= __yearstodays(tp->@tm_year@);
	tp->@tm_yday@ = (int)t;
	monthvec = @__time_monthstart_yday@[__isleap(tp->@tm_year@)];
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
			//That means the previous Sunday must be before the 1st.
			tp->@tm_isdst@ = previousSunday <= 0;
		}
	}
	tp->@tm_year@ -= 1900;
	return tp;
@@pp_elif $has_function(dos_gmtime64_s)@@
	return dos_gmtime64_s(tp, timer) ? NULL : tp;
@@pp_else@@
	time64_t t; int i;
	u16 const *monthvec;
	t = *timer;
	tp->@tm_sec@  = (int)(t % 60);
	tp->@tm_min@  = (int)((t/60) % 60);
	tp->@tm_hour@ = (int)((t/(60*60)) % 24);
	t /= 86400; /* SECONDS_PER_DAY */
	t += __yearstodays(1970); /* LINUX_TIME_START_YEAR */
	tp->@tm_wday@ = (int)(t % 7); /* DAYS_PER_WEEK */
	tp->@tm_year@ = (int)__daystoyears(t);
	t -= __yearstodays(tp->@tm_year@);
	tp->@tm_yday@ = (int)t;
	monthvec = @__time_monthstart_yday@[__isleap(tp->@tm_year@)];
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
			//That means the previous Sunday must be before the 1st.
			tp->@tm_isdst@ = previousSunday <= 0;
		}
	}
	tp->@tm_year@ -= 1900;
	return tp;
@@pp_endif@@
}

[[decl_prefix(DEFINE_STRUCT_TM)]]
[[doc_alias("localtime_r"), time64_variant_of(localtime_r)]]
__STRUCT_TM *localtime64_r([[nonnull]] $time64_t const *__restrict timer,
                           [[nonnull]] __STRUCT_TM *__restrict tp) {
@@pp_ifdef __BUILDING_LIBC@@
	/* XXX: Timezone support? */
	return gmtime64_r(timer, tp);
@@pp_elif $has_function(dos_localtime64_s)@@
	return dos_localtime64_s(tp, timer) ? NULL : tp;
@@pp_else@@
	/* XXX: Timezone support? */
	return gmtime64_r(timer, tp);
@@pp_endif@@
}

[[doc_alias("ctime_r"), time64_variant_of(ctime_r)]]
[[decl_prefix(DEFINE_STRUCT_TM)]]
char *ctime64_r([[nonnull]] $time64_t const *__restrict timer,
                [[nonnull]] char buf[26]) {
@@pp_ifdef __BUILDING_LIBC@@
	struct tm ltm;
	return asctime_r(localtime64_r(timer, &ltm), buf);
@@pp_elif $has_function(dos_ctime64_s)@@
	return dos_ctime64_s(buf, 26, timer) ? NULL : __buf;
@@pp_else@@
	struct tm ltm;
	return asctime_r(localtime64_r(timer, &ltm), buf);
@@pp_endif@@
}
%#endif /* __USE_TIME64 */

[[decl_prefix(DEFINE_STRUCT_TM), doc_alias("asctime_r"), ignore, nocrt, alias("asctime_s")]]
$errno_t crt_asctime_s([[outp(buflen)]] char *__restrict buf, $size_t buflen,
                       [[nonnull]] __STRUCT_TM const *__restrict tp);

%[define(DEFINE_TIME_ABBR_WDAY_NAMES =
#ifndef __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED
#define __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN_CONST __ATTR_UNUSED __ATTR_WEAK char const __abbr_wday_names[7][4] =
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN_CONST __ATTR_UNUSED __ATTR_SELECTANY char const __abbr_wday_names[7][4] =
#else
__PRIVATE __ATTR_UNUSED char const __abbr_wday_names[7][4] =
#endif
	{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_TIME_ABBR_WDAY_NAMES_DEFINED */
)]

%[define(DEFINE_TIME_ABBR_MONTH_NAMES =
#ifndef __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED
#define __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN_CONST __ATTR_UNUSED __ATTR_WEAK char const __abbr_month_names[12][4] =
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN_CONST __ATTR_UNUSED __ATTR_SELECTANY char const __abbr_month_names[12][4] =
#else
__PRIVATE __ATTR_UNUSED char const __abbr_month_names[12][4] =
#endif
	{ "Jan", "Feb", "Mar", "Apr", "May", "Jun",  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_TIME_ABBR_MONTH_NAMES_DEFINED */
)]


@@Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
@@that is the representation of TP in this format
[[decl_prefix(DEFINE_STRUCT_TM)]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || !$has_function(crt_asctime_s)@@
DEFINE_TIME_ABBR_WDAY_NAMES
DEFINE_TIME_ABBR_MONTH_NAMES
@@pp_endif@@
)]]
char *asctime_r([[nonnull]] __STRUCT_TM const *__restrict tp,
                [[nonnull]] char buf[26]) {
@@pp_ifdef __BUILDING_LIBC@@
	sprintf(buf,
	        "%.3s %.3s%3u %.2u:%.2u:%.2u %u\n",
	       (unsigned int)tp->@tm_wday@ >= 7 ? "??" "?" :
	        @__abbr_wday_names@[tp->@tm_wday@],
	       (unsigned int)tp->@tm_mon@ >= 12 ? "??" "?" :
	        @__abbr_month_names@[tp->@tm_mon@],
	       (unsigned int)tp->@tm_mday@,
	       (unsigned int)tp->@tm_hour@,
	       (unsigned int)tp->@tm_min@,
	       (unsigned int)tp->@tm_sec@,
	       (unsigned int)tp->@tm_year@ + 1900);
	return buf;
@@pp_elif $has_function(crt_asctime_s)@@
	return crt_asctime_s(buf, 26, tp) ? NULL : buf;
@@pp_else@@
	sprintf(buf,
	        "%.3s %.3s%3u %.2u:%.2u:%.2u %u\n",
	       (unsigned int)tp->@tm_wday@ >= 7 ? "??" "?" :
	        @__abbr_wday_names@[tp->@tm_wday@],
	       (unsigned int)tp->@tm_mon@ >= 12 ? "??" "?" :
	        @__abbr_month_names@[tp->@tm_mon@],
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

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_TIME_H)
#include <parts/uchar/time.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_TIME_H */
#endif /* __USE_UTF */

}