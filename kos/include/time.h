/* HASH CRC-32:0xb8948491 */
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
#undef __STRUCT_TM
#define __STRUCT_TM struct tm
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
#ifdef __CRT_HAVE_clock
__NAMESPACE_STD_USING(clock)
#endif /* __CRT_HAVE_clock */
#if defined(__CRT_HAVE_time) || defined(__CRT_HAVE__time32) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64)
__NAMESPACE_STD_USING(time)
#endif /* __CRT_HAVE_time || __CRT_HAVE__time32 || __CRT_HAVE_time64 || __CRT_HAVE__time64 */
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

#if (defined(__USE_DOS) || \
     (!defined(__USE_XOPEN2K) && !defined(__USE_ISOC_PURE) && !defined(__STRICT_ANSI__)))
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
#ifndef __tm_defined
#define __tm_defined 1
#undef __STRUCT_TM
#define __STRUCT_TM struct tm
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
#endif /* !__CXX_SYSTEM_HEADER */



#ifdef __USE_POSIX199309
struct sigevent;
#endif /* __USE_POSIX199309 */

__NAMESPACE_STD_BEGIN
#ifdef __CRT_HAVE_clock
/* Time used by the program so far (user time + system time)
 * The result / CLOCKS_PER_SECOND is program time in seconds */
__CDECLARE(__ATTR_WUNUSED,clock_t,__NOTHROW_NCX,clock,(void),())
#endif /* __CRT_HAVE_clock */
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
#elif defined(__CRT_HAVE_time) || defined(__CRT_HAVE__time32) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64)
__NAMESPACE_STD_END
#include <local/time/time.h>
__NAMESPACE_STD_BEGIN
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__NAMESPACE_LOCAL_USING_OR_IMPL(time, __FORCELOCAL time_t __NOTHROW_NCX(__LIBCCALL time)(time_t *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(time))(__timer); })
#endif /* ... */
#ifndef __NO_FPU
#ifndef __std_difftime_defined
#define __std_difftime_defined 1
#ifdef __difftime_defined
__NAMESPACE_GLB_USING(difftime)
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
#include <local/time/difftime.h>
__NAMESPACE_STD_BEGIN
/* Return the difference between TIME1 and TIME0 */
__NAMESPACE_LOCAL_USING_OR_IMPL(difftime, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW_NCX(__LIBCCALL difftime)(time_t __time1, time_t __time0) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(difftime))(__time1, __time0); })
#endif /* !... */
#endif /* !__std_difftime_defined */
#endif /* !__NO_FPU */
#if defined(__CRT_HAVE_mktime64) && defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),time_t,__NOTHROW_NCX,mktime,(__STRUCT_TM __KOS_FIXED_CONST *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE__mktime64) && defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),time_t,__NOTHROW_NCX,mktime,(__STRUCT_TM __KOS_FIXED_CONST *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64) && defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),time_t,__NOTHROW_NCX,mktime,(__STRUCT_TM __KOS_FIXED_CONST *__tp),timelocal64,(__tp))
#elif defined(__CRT_HAVE_mktime) && !defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),time_t,__NOTHROW_NCX,mktime,(__STRUCT_TM __KOS_FIXED_CONST *__tp),(__tp))
#elif defined(__CRT_HAVE__mktime32) && !defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),time_t,__NOTHROW_NCX,mktime,(__STRUCT_TM __KOS_FIXED_CONST *__tp),_mktime32,(__tp))
#elif defined(__CRT_HAVE_timelocal) && !defined(__USE_TIME_BITS64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),time_t,__NOTHROW_NCX,mktime,(__STRUCT_TM __KOS_FIXED_CONST *__tp),timelocal,(__tp))
#else /* ... */
__NAMESPACE_STD_END
#include <local/time/mktime.h>
__NAMESPACE_STD_BEGIN
/* Return the `time_t' representation of TP and normalize TP */
__NAMESPACE_LOCAL_USING_OR_IMPL(mktime, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) time_t __NOTHROW_NCX(__LIBCCALL mktime)(__STRUCT_TM __KOS_FIXED_CONST *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime))(__tp); })
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
#include <local/time/ctime.h>
__NAMESPACE_STD_BEGIN
/* Equivalent to `asctime(localtime(timer))' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctime, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL ctime)(time_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime))(__timer); })
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
#include <local/time/gmtime.h>
__NAMESPACE_STD_BEGIN
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__NAMESPACE_LOCAL_USING_OR_IMPL(gmtime, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct tm *__NOTHROW_NCX(__LIBCCALL gmtime)(time_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime))(__timer); })
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
#include <local/time/localtime.h>
__NAMESPACE_STD_BEGIN
/* Return the `struct tm' representation of *TIMER in the local timezone */
__NAMESPACE_LOCAL_USING_OR_IMPL(localtime, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct tm *__NOTHROW_NCX(__LIBCCALL localtime)(time_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime))(__timer); })
#endif /* !... */
#if __has_builtin(__builtin_strftime) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strftime)
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__CEIDECLARE(__ATTR_NONNULL((1, 3, 4)),size_t,__NOTHROW_NCX,strftime,(char *__restrict __buf, size_t __bufsize, char const *__restrict __format, __STRUCT_TM const *__restrict __tp),{ return __builtin_strftime(__buf, __bufsize, __format, __tp); })
#elif defined(__CRT_HAVE_strftime)
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__CDECLARE(__ATTR_NONNULL((1, 3, 4)),size_t,__NOTHROW_NCX,strftime,(char *__restrict __buf, size_t __bufsize, char const *__restrict __format, __STRUCT_TM const *__restrict __tp),(__buf,__bufsize,__format,__tp))
#elif defined(__CRT_HAVE__Strftime)
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),size_t,__NOTHROW_NCX,strftime,(char *__restrict __buf, size_t __bufsize, char const *__restrict __format, __STRUCT_TM const *__restrict __tp),_Strftime,(__buf,__bufsize,__format,__tp))
#else /* ... */
__NAMESPACE_STD_END
#include <local/time/strftime.h>
__NAMESPACE_STD_BEGIN
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__NAMESPACE_LOCAL_USING_OR_IMPL(strftime, __FORCELOCAL __ATTR_NONNULL((1, 3, 4)) size_t __NOTHROW_NCX(__LIBCCALL strftime)(char *__restrict __buf, size_t __bufsize, char const *__restrict __format, __STRUCT_TM const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strftime))(__buf, __bufsize, __format, __tp); })
#endif /* !... */
#ifdef __CRT_HAVE_asctime
/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,asctime,(struct tm const *__tp),(__tp))
#else /* __CRT_HAVE_asctime */
__NAMESPACE_STD_END
#include <local/time/asctime.h>
__NAMESPACE_STD_BEGIN
/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
__NAMESPACE_LOCAL_USING_OR_IMPL(asctime, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL asctime)(struct tm const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asctime))(__tp); })
#endif /* !__CRT_HAVE_asctime */
#ifdef __USE_ISOC11
#ifndef __std_asctime_s_defined
#define __std_asctime_s_defined 1
#ifdef __asctime_s_defined
__NAMESPACE_GLB_USING(asctime_s)
#elif defined(__CRT_HAVE_asctime_s)
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,asctime_s,(char *__restrict __buf, size_t __buflen, struct tm const *__restrict __tp),(__buf,__buflen,__tp))
#else /* ... */
__NAMESPACE_STD_END
#include <local/time/asctime_s.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(asctime_s, __FORCELOCAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL asctime_s)(char *__restrict __buf, size_t __buflen, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asctime_s))(__buf, __buflen, __tp); })
#endif /* !... */
#endif /* !__std_asctime_s_defined */
#endif /* __USE_ISOC11 */
#ifdef __USE_ISOCXX17
#ifndef __std_timespec_get_defined
#define __std_timespec_get_defined 1
#ifdef __timespec_get_defined
__NAMESPACE_GLB_USING(timespec_get)
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
#if defined(__CRT_HAVE_time) || defined(__CRT_HAVE__time32) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64)
__NAMESPACE_STD_USING(time)
#endif /* __CRT_HAVE_time || __CRT_HAVE__time32 || __CRT_HAVE_time64 || __CRT_HAVE__time64 */
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
#elif defined(__CRT_HAVE_time) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CREDIRECT(,__time64_t,__NOTHROW_NCX,time64,(__time64_t *__timer),time,(__timer))
#elif defined(__CRT_HAVE__time64)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CREDIRECT(,__time64_t,__NOTHROW_NCX,time64,(__time64_t *__timer),_time64,(__timer))
#elif defined(__CRT_HAVE_time) || defined(__CRT_HAVE__time32)
#include <local/time/time64.h>
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__NAMESPACE_LOCAL_USING_OR_IMPL(time64, __FORCELOCAL __time64_t __NOTHROW_NCX(__LIBCCALL time64)(__time64_t *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(time64))(__timer); })
#endif /* ... */
#ifndef __NO_FPU
#ifndef __difftime64_defined
#define __difftime64_defined 1
#ifdef __CRT_HAVE_difftime64
/* Return the difference between TIME1 and TIME0 */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime64,(__time64_t __time1, __time64_t __time0),(__time1,__time0))
#elif defined(__CRT_HAVE_difftime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime64,(__time64_t __time1, __time64_t __time0),difftime,(__time1,__time0))
#elif defined(__CRT_HAVE__difftime64)
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime64,(__time64_t __time1, __time64_t __time0),_difftime64,(__time1,__time0))
#elif defined(__CRT_HAVE___difftime64)
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,difftime64,(__time64_t __time1, __time64_t __time0),__difftime64,(__time1,__time0))
#else /* ... */
#include <local/time/difftime64.h>
/* Return the difference between TIME1 and TIME0 */
__NAMESPACE_LOCAL_USING_OR_IMPL(difftime64, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW_NCX(__LIBCCALL difftime64)(__time64_t __time1, __time64_t __time0) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(difftime64))(__time1, __time0); })
#endif /* !... */
#endif /* !__difftime64_defined */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE_mktime64
/* Return the `time_t' representation of TP and normalize TP */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,mktime64,(__STRUCT_TM __KOS_FIXED_CONST *__tp),(__tp))
#elif defined(__CRT_HAVE_mktime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,mktime64,(__STRUCT_TM __KOS_FIXED_CONST *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE__mktime64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,mktime64,(__STRUCT_TM __KOS_FIXED_CONST *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,mktime64,(__STRUCT_TM __KOS_FIXED_CONST *__tp),timelocal64,(__tp))
#else /* ... */
#include <local/time/mktime64.h>
/* Return the `time_t' representation of TP and normalize TP */
__NAMESPACE_LOCAL_USING_OR_IMPL(mktime64, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __time64_t __NOTHROW_NCX(__LIBCCALL mktime64)(__STRUCT_TM __KOS_FIXED_CONST *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime64))(__tp); })
#endif /* !... */
#ifdef __CRT_HAVE_ctime64
/* Equivalent to `asctime(localtime(timer))' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,ctime64,(__time64_t const *__timer),(__timer))
#elif defined(__CRT_HAVE_ctime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,ctime64,(__time64_t const *__timer),ctime,(__timer))
#elif defined(__CRT_HAVE__ctime64)
/* Equivalent to `asctime(localtime(timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,ctime64,(__time64_t const *__timer),_ctime64,(__timer))
#else /* ... */
#include <local/time/ctime64.h>
/* Equivalent to `asctime(localtime(timer))' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctime64, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL ctime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime64))(__timer); })
#endif /* !... */
#ifdef __CRT_HAVE_gmtime64
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,gmtime64,(__time64_t const *__timer),(__timer))
#elif defined(__CRT_HAVE_gmtime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,gmtime64,(__time64_t const *__timer),gmtime,(__timer))
#elif defined(__CRT_HAVE__gmtime64)
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,gmtime64,(__time64_t const *__timer),_gmtime64,(__timer))
#else /* ... */
#include <local/time/gmtime64.h>
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
__NAMESPACE_LOCAL_USING_OR_IMPL(gmtime64, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STRUCT_TM *__NOTHROW_NCX(__LIBCCALL gmtime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime64))(__timer); })
#endif /* !... */
#ifdef __CRT_HAVE_localtime64
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,localtime64,(__time64_t const *__timer),(__timer))
#elif defined(__CRT_HAVE_localtime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,localtime64,(__time64_t const *__timer),localtime,(__timer))
#elif defined(__CRT_HAVE__localtime64)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,localtime64,(__time64_t const *__timer),_localtime64,(__timer))
#else /* ... */
#include <local/time/localtime64.h>
/* Return the `struct tm' representation of *TIMER in the local timezone */
__NAMESPACE_LOCAL_USING_OR_IMPL(localtime64, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STRUCT_TM *__NOTHROW_NCX(__LIBCCALL localtime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime64))(__timer); })
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
#ifdef __CRT_HAVE_tzset
/* Set time conversion information from the TZ environment variable.
 * If TZ is not defined, a locale-dependent default is used */
__CDECLARE_VOID(,__NOTHROW_NCX,tzset,(void),())
#endif /* __CRT_HAVE_tzset */
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
#if defined(__CRT_HAVE_stime64) && defined(__USE_TIME_BITS64)
/* Set the system time to *WHEN. This call is restricted to the superuser */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,stime,(__TM_TYPE(time) const *__when),stime64,(__when))
#elif defined(__CRT_HAVE_stime) && !defined(__USE_TIME_BITS64)
/* Set the system time to *WHEN. This call is restricted to the superuser */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,stime,(__TM_TYPE(time) const *__when),(__when))
#elif defined(__CRT_HAVE_stime) || defined(__CRT_HAVE_stime64)
#include <local/time/stime.h>
/* Set the system time to *WHEN. This call is restricted to the superuser */
__NAMESPACE_LOCAL_USING_OR_IMPL(stime, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL stime)(__TM_TYPE(time) const *__when) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stime))(__when); })
#endif /* ... */
#if defined(__CRT_HAVE_timegm64) && defined(__USE_TIME_BITS64)
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timegm,(__STRUCT_TM *__tp),timegm64,(__tp))
#elif defined(__CRT_HAVE_timegm) && !defined(__USE_TIME_BITS64)
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timegm,(__STRUCT_TM *__tp),(__tp))
#else /* ... */
#include <local/time/timegm.h>
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__NAMESPACE_LOCAL_USING_OR_IMPL(timegm, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __TM_TYPE(time) __NOTHROW_NCX(__LIBCCALL timegm)(__STRUCT_TM *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timegm))(__tp); })
#endif /* !... */
#if defined(__CRT_HAVE_mktime64) && defined(__USE_TIME_BITS64)
/* Another name for `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timelocal,(__STRUCT_TM __KOS_FIXED_CONST *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE__mktime64) && defined(__USE_TIME_BITS64)
/* Another name for `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timelocal,(__STRUCT_TM __KOS_FIXED_CONST *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64) && defined(__USE_TIME_BITS64)
/* Another name for `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timelocal,(__STRUCT_TM __KOS_FIXED_CONST *__tp),timelocal64,(__tp))
#elif defined(__CRT_HAVE_mktime) && !defined(__USE_TIME_BITS64)
/* Another name for `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timelocal,(__STRUCT_TM __KOS_FIXED_CONST *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE__mktime32) && !defined(__USE_TIME_BITS64)
/* Another name for `mktime' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timelocal,(__STRUCT_TM __KOS_FIXED_CONST *__tp),_mktime32,(__tp))
#elif defined(__CRT_HAVE_timelocal) && !defined(__USE_TIME_BITS64)
/* Another name for `mktime' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__TM_TYPE(time),__NOTHROW_NCX,timelocal,(__STRUCT_TM __KOS_FIXED_CONST *__tp),(__tp))
#else /* ... */
#include <local/time/mktime.h>
/* Another name for `mktime' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __TM_TYPE(time) __NOTHROW_NCX(__LIBCCALL timelocal)(__STRUCT_TM __KOS_FIXED_CONST *__tp) { return (__TM_TYPE(time))(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime))(__tp); }
#endif /* !... */
#ifdef __CRT_HAVE_dysize
/* Return the number of days in YEAR */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,dysize,(__STDC_INT_AS_UINT_T __year),(__year))
#else /* __CRT_HAVE_dysize */
#include <local/time/dysize.h>
/* Return the number of days in YEAR */
__NAMESPACE_LOCAL_USING_OR_IMPL(dysize, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL dysize)(__STDC_INT_AS_UINT_T __year) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dysize))(__year); })
#endif /* !__CRT_HAVE_dysize */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_stime64
/* Set the system time to *WHEN. This call is restricted to the superuser */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,stime64,(__time64_t const *__when),(__when))
#elif defined(__CRT_HAVE_stime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Set the system time to *WHEN. This call is restricted to the superuser */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,stime64,(__time64_t const *__when),stime,(__when))
#elif defined(__CRT_HAVE_stime)
#include <local/time/stime64.h>
/* Set the system time to *WHEN. This call is restricted to the superuser */
__NAMESPACE_LOCAL_USING_OR_IMPL(stime64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL stime64)(__time64_t const *__when) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stime64))(__when); })
#endif /* ... */
#ifdef __CRT_HAVE_timegm64
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,timegm64,(__STRUCT_TM *__tp),(__tp))
#elif defined(__CRT_HAVE_timegm) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,timegm64,(__STRUCT_TM *__tp),timegm,(__tp))
#else /* ... */
#include <local/time/timegm64.h>
/* Like `mktime', but TP represents Universal Time (UTC), not local time */
__NAMESPACE_LOCAL_USING_OR_IMPL(timegm64, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __time64_t __NOTHROW_NCX(__LIBCCALL timegm64)(__STRUCT_TM *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timegm64))(__tp); })
#endif /* !... */
#ifdef __CRT_HAVE_mktime64
/* Another name for `mktime64' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,timelocal64,(__STRUCT_TM __KOS_FIXED_CONST *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE_mktime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Another name for `mktime64' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,timelocal64,(__STRUCT_TM __KOS_FIXED_CONST *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE__mktime64)
/* Another name for `mktime64' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,timelocal64,(__STRUCT_TM __KOS_FIXED_CONST *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64)
/* Another name for `mktime64' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,timelocal64,(__STRUCT_TM __KOS_FIXED_CONST *__tp),(__tp))
#else /* ... */
#include <local/time/mktime64.h>
/* Another name for `mktime64' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __time64_t __NOTHROW_NCX(__LIBCCALL timelocal64)(__STRUCT_TM __KOS_FIXED_CONST *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mktime64))(__tp); }
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
#elif defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE_nanosleep64)
#include <local/time/nanosleep.h>
/* Pause execution for a number of nanoseconds */
__NAMESPACE_LOCAL_USING_OR_IMPL(nanosleep, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL nanosleep)(struct timespec const *__requested_time, struct timespec *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanosleep))(__requested_time, __remaining); })
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
#elif defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres) || defined(__CRT_HAVE_clock_getres64)
#include <local/time/clock_getres.h>
/* Get resolution of clock CLOCK_ID */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_getres, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL clock_getres)(clockid_t __clock_id, struct timespec *__res) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_getres))(__clock_id, __res); })
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
#elif defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime) || defined(__CRT_HAVE_clock_gettime64)
#include <local/time/clock_gettime.h>
/* Get current value of clock CLOCK_ID and store it in TP */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_gettime, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL clock_gettime)(clockid_t __clock_id, struct timespec *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_gettime))(__clock_id, __tp); })
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
#elif defined(__CRT_HAVE_clock_settime) || defined(__CRT_HAVE___clock_settime) || defined(__CRT_HAVE_clock_settime64)
#include <local/time/clock_settime.h>
/* Set clock CLOCK_ID to value TP */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_settime, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL clock_settime)(clockid_t __clock_id, struct timespec const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_settime))(__clock_id, __tp); })
#endif /* ... */
#ifdef __CRT_HAVE_timer_create
/* Create new per-process timer using CLOCK_ID */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timer_create,(clockid_t __clock_id, struct sigevent *__restrict __evp, timer_t *__restrict __timerid),(__clock_id,__evp,__timerid))
#endif /* __CRT_HAVE_timer_create */
#ifdef __CRT_HAVE_timer_delete
/* Delete timer TIMERID */
__CDECLARE(,int,__NOTHROW_NCX,timer_delete,(timer_t __timerid),(__timerid))
#endif /* __CRT_HAVE_timer_delete */
#if defined(__CRT_HAVE_timer_settime64) && defined(__USE_TIME_BITS64)
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timer_settime,(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__restrict __value, struct itimerspec *__restrict __ovalue),timer_settime64,(__timerid,__flags,__value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime) && !defined(__USE_TIME_BITS64)
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timer_settime,(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__restrict __value, struct itimerspec *__restrict __ovalue),(__timerid,__flags,__value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime) || defined(__CRT_HAVE_timer_settime64)
#include <local/time/timer_settime.h>
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__NAMESPACE_LOCAL_USING_OR_IMPL(timer_settime, __FORCELOCAL __ATTR_NONNULL((3)) int __NOTHROW_NCX(__LIBCCALL timer_settime)(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__restrict __value, struct itimerspec *__restrict __ovalue) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timer_settime))(__timerid, __flags, __value, __ovalue); })
#endif /* ... */
#if defined(__CRT_HAVE_timer_gettime64) && defined(__USE_TIME_BITS64)
/* Get current value of timer TIMERID and store it in VALUE */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,timer_gettime,(timer_t __timerid, struct itimerspec *__value),timer_gettime64,(__timerid,__value))
#elif defined(__CRT_HAVE_timer_gettime) && !defined(__USE_TIME_BITS64)
/* Get current value of timer TIMERID and store it in VALUE */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,timer_gettime,(timer_t __timerid, struct itimerspec *__value),(__timerid,__value))
#elif defined(__CRT_HAVE_timer_gettime) || defined(__CRT_HAVE_timer_gettime64)
#include <local/time/timer_gettime.h>
/* Get current value of timer TIMERID and store it in VALUE */
__NAMESPACE_LOCAL_USING_OR_IMPL(timer_gettime, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL timer_gettime)(timer_t __timerid, struct itimerspec *__value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timer_gettime))(__timerid, __value); })
#endif /* ... */
#ifdef __CRT_HAVE_timer_getoverrun
/* Get expiration overrun for timer TIMERID */
__CDECLARE(,int,__NOTHROW_NCX,timer_getoverrun,(timer_t __timerid),(__timerid))
#endif /* __CRT_HAVE_timer_getoverrun */

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
#elif defined(__CRT_HAVE_clock_nanosleep) || defined(__CRT_HAVE___clock_nanosleep) || defined(__CRT_HAVE_clock_nanosleep64)
#include <local/time/clock_nanosleep.h>
/* High-resolution sleep with the specified clock */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_nanosleep, __FORCELOCAL __ATTR_NONNULL((3)) int __NOTHROW_RPC(__LIBCCALL clock_nanosleep)(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec const *__restrict __requested_time, struct timespec *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_nanosleep))(__clock_id, __flags, __requested_time, __remaining); })
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
#elif defined(__CRT_HAVE_nanosleep) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Pause execution for a number of nanoseconds */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,nanosleep64,(struct timespec64 const *__restrict __requested_time, struct timespec64 *__remaining),nanosleep,(__requested_time,__remaining))
#elif defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep)
#include <local/time/nanosleep64.h>
/* Pause execution for a number of nanoseconds */
__NAMESPACE_LOCAL_USING_OR_IMPL(nanosleep64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL nanosleep64)(struct timespec64 const *__restrict __requested_time, struct timespec64 *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanosleep64))(__requested_time, __remaining); })
#endif /* ... */
#ifdef __CRT_HAVE_clock_getres64
/* Get resolution of clock CLOCK_ID */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_getres64,(clockid_t __clock_id, struct timespec64 *__res),(__clock_id,__res))
#elif defined(__CRT_HAVE_clock_getres) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Get resolution of clock CLOCK_ID */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_getres64,(clockid_t __clock_id, struct timespec64 *__res),clock_getres,(__clock_id,__res))
#elif defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres)
#include <local/time/clock_getres64.h>
/* Get resolution of clock CLOCK_ID */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_getres64, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL clock_getres64)(clockid_t __clock_id, struct timespec64 *__res) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_getres64))(__clock_id, __res); })
#endif /* ... */
#ifdef __CRT_HAVE_clock_gettime64
/* Get current value of clock CLOCK_ID and store it in TP */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_gettime64,(clockid_t __clock_id, struct timespec64 *__tp),(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Get current value of clock CLOCK_ID and store it in TP */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_gettime64,(clockid_t __clock_id, struct timespec64 *__tp),clock_gettime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_gettime) || defined(__CRT_HAVE___clock_gettime)
#include <local/time/clock_gettime64.h>
/* Get current value of clock CLOCK_ID and store it in TP */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_gettime64, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL clock_gettime64)(clockid_t __clock_id, struct timespec64 *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_gettime64))(__clock_id, __tp); })
#endif /* ... */
#ifdef __CRT_HAVE_clock_settime64
/* Set clock CLOCK_ID to value TP */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_settime64,(clockid_t __clock_id, struct timespec64 const *__tp),(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Set clock CLOCK_ID to value TP */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,clock_settime64,(clockid_t __clock_id, struct timespec64 const *__tp),clock_settime,(__clock_id,__tp))
#elif defined(__CRT_HAVE_clock_settime) || defined(__CRT_HAVE___clock_settime)
#include <local/time/clock_settime64.h>
/* Set clock CLOCK_ID to value TP */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_settime64, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL clock_settime64)(clockid_t __clock_id, struct timespec64 const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_settime64))(__clock_id, __tp); })
#endif /* ... */
#ifdef __CRT_HAVE_timer_settime64
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timer_settime64,(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec64 const *__restrict __value, struct itimerspec64 *__restrict __ovalue),(__timerid,__flags,__value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,timer_settime64,(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec64 const *__restrict __value, struct itimerspec64 *__restrict __ovalue),timer_settime,(__timerid,__flags,__value,__ovalue))
#elif defined(__CRT_HAVE_timer_settime)
#include <local/time/timer_settime64.h>
/* Set timer TIMERID to VALUE, returning old value in OVALUE */
__NAMESPACE_LOCAL_USING_OR_IMPL(timer_settime64, __FORCELOCAL __ATTR_NONNULL((3)) int __NOTHROW_NCX(__LIBCCALL timer_settime64)(timer_t __timerid, __STDC_INT_AS_UINT_T __flags, struct itimerspec64 const *__restrict __value, struct itimerspec64 *__restrict __ovalue) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timer_settime64))(__timerid, __flags, __value, __ovalue); })
#endif /* ... */
#ifdef __CRT_HAVE_timer_gettime64
/* Get current value of timer TIMERID and store it in VALUE */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,timer_gettime64,(timer_t __timerid, struct itimerspec64 *__value),(__timerid,__value))
#elif defined(__CRT_HAVE_timer_gettime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Get current value of timer TIMERID and store it in VALUE */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,timer_gettime64,(timer_t __timerid, struct itimerspec64 *__value),timer_gettime,(__timerid,__value))
#elif defined(__CRT_HAVE_timer_gettime)
#include <local/time/timer_gettime64.h>
/* Get current value of timer TIMERID and store it in VALUE */
__NAMESPACE_LOCAL_USING_OR_IMPL(timer_gettime64, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL timer_gettime64)(timer_t __timerid, struct itimerspec64 *__value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timer_gettime64))(__timerid, __value); })
#endif /* ... */

#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_clock_nanosleep64
/* High-resolution sleep with the specified clock */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,clock_nanosleep64,(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec64 const *__requested_time, struct timespec64 *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE_clock_nanosleep) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* High-resolution sleep with the specified clock */
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_RPC,clock_nanosleep64,(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec64 const *__requested_time, struct timespec64 *__remaining),clock_nanosleep,(__clock_id,__flags,__requested_time,__remaining))
#elif defined(__CRT_HAVE_clock_nanosleep) || defined(__CRT_HAVE___clock_nanosleep)
#include <local/time/clock_nanosleep64.h>
/* High-resolution sleep with the specified clock */
__NAMESPACE_LOCAL_USING_OR_IMPL(clock_nanosleep64, __FORCELOCAL __ATTR_NONNULL((3)) int __NOTHROW_RPC(__LIBCCALL clock_nanosleep64)(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags, struct timespec64 const *__requested_time, struct timespec64 *__remaining) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clock_nanosleep64))(__clock_id, __flags, __requested_time, __remaining); })
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

#ifdef __CRT_HAVE_getdate
/* Parse the given string as a date specification and return a value
 * representing the value.  The templates from the file identified by
 * the environment variable DATEMSK are used.  In case of an error
 * `getdate_err' is set */
__CDECLARE(__ATTR_NONNULL((1)),__STRUCT_TM *,__NOTHROW_NCX,getdate,(const char *__string),(__string))
#endif /* __CRT_HAVE_getdate */
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
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,getdate_r,(char const *__restrict __string, __STRUCT_TM *__restrict __resbufp),(__string,__resbufp))
#else /* __CRT_HAVE_getdate_r */
#include <local/time/getdate_r.h>
/* Since `getdate' is not reentrant because of the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The functionality is the same.  The result is returned in
 * the buffer pointed to by RESBUFP and in case of an error the return
 * value is != 0 with the same values as given above for `getdate_err'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(getdate_r, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL getdate_r)(char const *__restrict __string, __STRUCT_TM *__restrict __resbufp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdate_r))(__string, __resbufp); })
#endif /* !__CRT_HAVE_getdate_r */
#endif /* !__getdate_r_defined */
#endif /* __USE_GNU */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_strftime_l
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
__CDECLARE(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),(__buf,__bufsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE__strftime_l)
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),_strftime_l,(__buf,__bufsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE___strftime_l)
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),__strftime_l,(__buf,__bufsize,__format,__tp,__locale))
#else /* ... */
#include <local/time/strftime_l.h>
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
__NAMESPACE_LOCAL_USING_OR_IMPL(strftime_l, __FORCELOCAL __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strftime_l)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strftime_l))(__buf, __bufsize, __format, __tp, __locale); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_XOPEN
#ifdef __CRT_HAVE_strptime
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),char *,__NOTHROW_NCX,strptime,(char const *__restrict __s, char const *__restrict __format, __STRUCT_TM *__restrict __tp),(__s,__format,__tp))
#else /* __CRT_HAVE_strptime */
#include <local/time/strptime.h>
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
__NAMESPACE_LOCAL_USING_OR_IMPL(strptime, __FORCELOCAL __ATTR_NONNULL((1, 2, 3)) char *__NOTHROW_NCX(__LIBCCALL strptime)(char const *__restrict __s, char const *__restrict __format, __STRUCT_TM *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strptime))(__s, __format, __tp); })
#endif /* !__CRT_HAVE_strptime */
#endif /* __USE_XOPEN */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_strptime_l
/* Similar to `strptime' but take the information from
 * the provided locale and not the global locale */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),char *,__NOTHROW_NCX,strptime_l,(char const *__restrict __s, char const *__restrict __format, __STRUCT_TM *__restrict __tp, __locale_t __locale),(__s,__format,__tp,__locale))
#else /* __CRT_HAVE_strptime_l */
#include <local/time/strptime_l.h>
/* Similar to `strptime' but take the information from
 * the provided locale and not the global locale */
__NAMESPACE_LOCAL_USING_OR_IMPL(strptime_l, __FORCELOCAL __ATTR_NONNULL((1, 2, 3)) char *__NOTHROW_NCX(__LIBCCALL strptime_l)(char const *__restrict __s, char const *__restrict __format, __STRUCT_TM *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strptime_l))(__s, __format, __tp, __locale); })
#endif /* !__CRT_HAVE_strptime_l */
#ifndef __getdate_r_defined
#define __getdate_r_defined 1
#ifdef __CRT_HAVE_getdate_r
/* Since `getdate' is not reentrant because of the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The functionality is the same.  The result is returned in
 * the buffer pointed to by RESBUFP and in case of an error the return
 * value is != 0 with the same values as given above for `getdate_err'. */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,getdate_r,(char const *__restrict __string, __STRUCT_TM *__restrict __resbufp),(__string,__resbufp))
#else /* __CRT_HAVE_getdate_r */
#include <local/time/getdate_r.h>
/* Since `getdate' is not reentrant because of the use of `getdate_err'
 * and the static buffer to return the result in, we provide a thread-safe
 * variant.  The functionality is the same.  The result is returned in
 * the buffer pointed to by RESBUFP and in case of an error the return
 * value is != 0 with the same values as given above for `getdate_err'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(getdate_r, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL getdate_r)(char const *__restrict __string, __STRUCT_TM *__restrict __resbufp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdate_r))(__string, __resbufp); })
#endif /* !__CRT_HAVE_getdate_r */
#endif /* !__getdate_r_defined */
#endif /* __USE_GNU */

#ifdef __USE_POSIX
#ifdef __CRT_HAVE_gmtime_r
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CDECLARE(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,gmtime_r,(__TM_TYPE(time) const *__restrict __timer, __STRUCT_TM *__restrict __tp),(__timer,__tp))
#elif defined(__CRT_HAVE___gmtime_r)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,gmtime_r,(__TM_TYPE(time) const *__restrict __timer, __STRUCT_TM *__restrict __tp),__gmtime_r,(__timer,__tp))
#else /* ... */
#include <local/time/gmtime_r.h>
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(gmtime_r, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STRUCT_TM *__NOTHROW_NCX(__LIBCCALL gmtime_r)(__TM_TYPE(time) const *__restrict __timer, __STRUCT_TM *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime_r))(__timer, __tp); })
#endif /* !... */
#ifdef __CRT_HAVE_localtime_r
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CDECLARE(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,localtime_r,(__TM_TYPE(time) const *__restrict __timer, __STRUCT_TM *__restrict __tp),(__timer,__tp))
#else /* __CRT_HAVE_localtime_r */
#include <local/time/localtime_r.h>
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(localtime_r, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STRUCT_TM *__NOTHROW_NCX(__LIBCCALL localtime_r)(__TM_TYPE(time) const *__restrict __timer, __STRUCT_TM *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime_r))(__timer, __tp); })
#endif /* !__CRT_HAVE_localtime_r */
#ifdef __CRT_HAVE_ctime_r
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__CDECLARE(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,ctime_r,(__TM_TYPE(time) const *__restrict __timer, char __buf[26]),(__timer,__buf))
#else /* __CRT_HAVE_ctime_r */
#include <local/time/ctime_r.h>
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctime_r, __FORCELOCAL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL ctime_r)(__TM_TYPE(time) const *__restrict __timer, char __buf[26]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime_r))(__timer, __buf); })
#endif /* !__CRT_HAVE_ctime_r */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_gmtime64_r
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CDECLARE(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,gmtime64_r,(__time64_t const *__restrict __timer, __STRUCT_TM *__restrict __tp),(__timer,__tp))
#elif defined(__CRT_HAVE_gmtime_r) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,gmtime64_r,(__time64_t const *__restrict __timer, __STRUCT_TM *__restrict __tp),gmtime_r,(__timer,__tp))
#else /* ... */
#include <local/time/gmtime64_r.h>
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(gmtime64_r, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STRUCT_TM *__NOTHROW_NCX(__LIBCCALL gmtime64_r)(__time64_t const *__restrict __timer, __STRUCT_TM *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime64_r))(__timer, __tp); })
#endif /* !... */
#ifdef __CRT_HAVE_localtime64_r
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CDECLARE(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,localtime64_r,(__time64_t const *__restrict __timer, __STRUCT_TM *__restrict __tp),(__timer,__tp))
#elif defined(__CRT_HAVE_localtime_r) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,localtime64_r,(__time64_t const *__restrict __timer, __STRUCT_TM *__restrict __tp),localtime_r,(__timer,__tp))
#else /* ... */
#include <local/time/localtime64_r.h>
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__NAMESPACE_LOCAL_USING_OR_IMPL(localtime64_r, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STRUCT_TM *__NOTHROW_NCX(__LIBCCALL localtime64_r)(__time64_t const *__restrict __timer, __STRUCT_TM *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime64_r))(__timer, __tp); })
#endif /* !... */
#ifdef __CRT_HAVE_ctime64_r
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__CDECLARE(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,ctime64_r,(__time64_t const *__restrict __timer, char __buf[26]),(__timer,__buf))
#elif defined(__CRT_HAVE_ctime_r) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,ctime64_r,(__time64_t const *__restrict __timer, char __buf[26]),ctime_r,(__timer,__buf))
#else /* ... */
#include <local/time/ctime64_r.h>
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctime64_r, __FORCELOCAL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL ctime64_r)(__time64_t const *__restrict __timer, char __buf[26]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime64_r))(__timer, __buf); })
#endif /* !... */
#endif /* __USE_TIME64 */
#ifdef __CRT_HAVE_asctime_r
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
__CDECLARE(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,asctime_r,(__STRUCT_TM const *__restrict __tp, char __buf[26]),(__tp,__buf))
#else /* __CRT_HAVE_asctime_r */
#include <local/time/asctime_r.h>
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
__NAMESPACE_LOCAL_USING_OR_IMPL(asctime_r, __FORCELOCAL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL asctime_r)(__STRUCT_TM const *__restrict __tp, char __buf[26]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asctime_r))(__tp, __buf); })
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
