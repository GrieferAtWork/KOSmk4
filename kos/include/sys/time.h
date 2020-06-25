/* HASH CRC-32:0x989720cb */
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
#ifndef _SYS_TIME_H
#define _SYS_TIME_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/time.h>
#include <bits/types.h>
#include <bits/itimerval.h>
#include <sys/select.h>

/* Documentation taken from /usr/include/i386-linux-gnu/sys/time.h */
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

#if (defined(__ITIMER_REAL) || defined(__ITIMER_VIRTUAL) || \
     defined(__ITIMER_PROF))
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __itimer_which {
#ifdef __ITIMER_REAL
	ITIMER_REAL    = __ITIMER_REAL,
#endif /* __ITIMER_REAL */
#ifdef __ITIMER_VIRTUAL
	ITIMER_VIRTUAL = __ITIMER_VIRTUAL,
#endif /* __ITIMER_VIRTUAL */
#ifdef __ITIMER_PROF
	ITIMER_PROF    = __ITIMER_PROF
#endif /* __ITIMER_PROF */
} __itimer_which_t;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __ITIMER_REAL
#define ITIMER_REAL    ITIMER_REAL
#endif /* __ITIMER_REAL */
#ifdef __ITIMER_VIRTUAL
#define ITIMER_VIRTUAL ITIMER_VIRTUAL
#endif /* __ITIMER_VIRTUAL */
#ifdef __ITIMER_PROF
#define ITIMER_PROF    ITIMER_PROF
#endif /* __ITIMER_PROF */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __ITIMER_REAL
#define ITIMER_REAL    __ITIMER_REAL
#endif /* __ITIMER_REAL */
#ifdef __ITIMER_VIRTUAL
#define ITIMER_VIRTUAL __ITIMER_VIRTUAL
#endif /* __ITIMER_VIRTUAL */
#ifdef __ITIMER_PROF
#define ITIMER_PROF    __ITIMER_PROF
#endif /* __ITIMER_PROF */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

#ifdef __CC__

#ifndef __time_t_defined
#define __time_t_defined  1
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

#ifndef __suseconds_t_defined
#define __suseconds_t_defined
typedef __suseconds_t suseconds_t;
#endif /* !__suseconds_t_defined */

#ifdef __USE_GNU
#define TIMEVAL_TO_TIMESPEC(tv, ts) (void)((ts)->tv_sec = (tv)->tv_sec, (ts)->tv_nsec = (tv)->tv_usec * 1000)
#define TIMESPEC_TO_TIMEVAL(tv, ts) (void)((tv)->tv_sec = (ts)->tv_sec, (tv)->tv_usec = (ts)->tv_nsec / 1000)
#endif /* __USE_GNU */

#ifdef __USE_MISC
#ifndef __struct_timezone_defined
#define __struct_timezone_defined 1
struct timezone {
	__INT32_TYPE__ tz_minuteswest; /* Minutes west of GMT. */
	__INT32_TYPE__ tz_dsttime;     /* Nonzero if DST is ever in effect. */
};
#endif /* !__struct_timezone_defined */
#endif /* __USE_MISC */

#ifndef ____timezone_ptr_t_defined
#define ____timezone_ptr_t_defined 1
#ifdef __USE_MISC
typedef struct timezone *__restrict __timezone_ptr_t;
#else /* __USE_MISC */
typedef void *__restrict __timezone_ptr_t;
#endif /* !__USE_MISC */
#endif /* !____timezone_ptr_t_defined */

#if defined(__CRT_HAVE_gettimeofday64) && defined(__USE_TIME_BITS64)
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,gettimeofday,(struct timeval *__restrict __tv, __timezone_ptr_t __tz),gettimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday) && !defined(__USE_TIME_BITS64)
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,gettimeofday,(struct timeval *__restrict __tv, __timezone_ptr_t __tz),(__tv,__tz))
#elif defined(__CRT_HAVE___gettimeofday) && !defined(__USE_TIME_BITS64)
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,gettimeofday,(struct timeval *__restrict __tv, __timezone_ptr_t __tz),__gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday)
#include <local/sys.time/gettimeofday.h>
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__NAMESPACE_LOCAL_USING_OR_IMPL(gettimeofday, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL gettimeofday)(struct timeval *__restrict __tv, __timezone_ptr_t __tz) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gettimeofday))(__tv, __tz); })
#endif /* ... */
#if defined(__CRT_HAVE_getitimer64) && defined(__USE_TIME_BITS64)
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getitimer,(__itimer_which_t __which, struct itimerval *__curr_value),getitimer64,(__which,__curr_value))
#elif defined(__CRT_HAVE_getitimer) && !defined(__USE_TIME_BITS64)
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getitimer,(__itimer_which_t __which, struct itimerval *__curr_value),(__which,__curr_value))
#elif defined(__CRT_HAVE_getitimer64) || defined(__CRT_HAVE_getitimer)
#include <local/sys.time/getitimer.h>
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
__NAMESPACE_LOCAL_USING_OR_IMPL(getitimer, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL getitimer)(__itimer_which_t __which, struct itimerval *__curr_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getitimer))(__which, __curr_value); })
#endif /* ... */
#if defined(__CRT_HAVE_setitimer64) && defined(__USE_TIME_BITS64)
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,setitimer,(__itimer_which_t __which, struct itimerval const *__newval, struct itimerval *__oldval),setitimer64,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE_setitimer) && !defined(__USE_TIME_BITS64)
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,setitimer,(__itimer_which_t __which, struct itimerval const *__newval, struct itimerval *__oldval),(__which,__newval,__oldval))
#elif defined(__CRT_HAVE_setitimer64) || defined(__CRT_HAVE_setitimer)
#include <local/sys.time/setitimer.h>
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
__NAMESPACE_LOCAL_USING_OR_IMPL(setitimer, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL setitimer)(__itimer_which_t __which, struct itimerval const *__newval, struct itimerval *__oldval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setitimer))(__which, __newval, __oldval); })
#endif /* ... */
#if defined(__CRT_HAVE_utimes64) && defined(__USE_TIME_BITS64)
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,utimes,(char const *__file, struct timeval const __tvp[2]),utimes64,(__file,__tvp))
#elif defined(__CRT_HAVE_utimes) && !defined(__USE_TIME_BITS64)
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,utimes,(char const *__file, struct timeval const __tvp[2]),(__file,__tvp))
#elif defined(__CRT_HAVE_utimes64) || defined(__CRT_HAVE_utimes)
#include <local/sys.time/utimes.h>
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
__NAMESPACE_LOCAL_USING_OR_IMPL(utimes, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL utimes)(char const *__file, struct timeval const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(utimes))(__file, __tvp); })
#endif /* ... */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_futimesat64) && defined(__USE_TIME_BITS64)
/* Same as `utimes', but takes an open file descriptor instead of a name */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,futimesat,(__fd_t __fd, char const *__file, struct timeval const __tvp[2]),futimesat64,(__fd,__file,__tvp))
#elif defined(__CRT_HAVE_futimesat) && !defined(__USE_TIME_BITS64)
/* Same as `utimes', but takes an open file descriptor instead of a name */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,futimesat,(__fd_t __fd, char const *__file, struct timeval const __tvp[2]),(__fd,__file,__tvp))
#elif defined(__CRT_HAVE_futimesat64) || defined(__CRT_HAVE_futimesat)
#include <local/sys.time/futimesat.h>
/* Same as `utimes', but takes an open file descriptor instead of a name */
__NAMESPACE_LOCAL_USING_OR_IMPL(futimesat, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL futimesat)(__fd_t __fd, char const *__file, struct timeval const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futimesat))(__fd, __file, __tvp); })
#endif /* ... */
#endif /* __USE_GNU */

#ifdef __USE_MISC
#if defined(__CRT_HAVE_settimeofday64) && defined(__USE_TIME_BITS64)
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,settimeofday,(struct timeval const *__tv, struct timezone const *__tz),settimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE_settimeofday) && !defined(__USE_TIME_BITS64)
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
__CDECLARE(,int,__NOTHROW_NCX,settimeofday,(struct timeval const *__tv, struct timezone const *__tz),(__tv,__tz))
#elif defined(__CRT_HAVE_settimeofday64) || defined(__CRT_HAVE_settimeofday)
#include <local/sys.time/settimeofday.h>
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
__NAMESPACE_LOCAL_USING_OR_IMPL(settimeofday, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL settimeofday)(struct timeval const *__tv, struct timezone const *__tz) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(settimeofday))(__tv, __tz); })
#endif /* ... */
#if defined(__CRT_HAVE_adjtime64) && defined(__USE_TIME_BITS64)
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,adjtime,(struct timeval const *__delta, struct timeval *__olddelta),adjtime64,(__delta,__olddelta))
#elif defined(__CRT_HAVE_adjtime) && !defined(__USE_TIME_BITS64)
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__CDECLARE(,int,__NOTHROW_NCX,adjtime,(struct timeval const *__delta, struct timeval *__olddelta),(__delta,__olddelta))
#elif defined(__CRT_HAVE_adjtime64) || defined(__CRT_HAVE_adjtime)
#include <local/sys.time/adjtime.h>
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__NAMESPACE_LOCAL_USING_OR_IMPL(adjtime, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL adjtime)(struct timeval const *__delta, struct timeval *__olddelta) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(adjtime))(__delta, __olddelta); })
#endif /* ... */
#if defined(__CRT_HAVE_lutimes64) && defined(__USE_TIME_BITS64)
/* Same as `utimes', but does not follow symbolic links */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,lutimes,(char const *__file, struct timeval const __tvp[2]),lutimes64,(__file,__tvp))
#elif defined(__CRT_HAVE_lutimes) && !defined(__USE_TIME_BITS64)
/* Same as `utimes', but does not follow symbolic links */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,lutimes,(char const *__file, struct timeval const __tvp[2]),(__file,__tvp))
#elif defined(__CRT_HAVE_lutimes64) || defined(__CRT_HAVE_lutimes)
#include <local/sys.time/lutimes.h>
/* Same as `utimes', but does not follow symbolic links */
__NAMESPACE_LOCAL_USING_OR_IMPL(lutimes, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL lutimes)(char const *__file, struct timeval const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lutimes))(__file, __tvp); })
#endif /* ... */
#if defined(__CRT_HAVE_futimes64) && defined(__USE_TIME_BITS64)
/* Same as `utimes', but takes an open file descriptor instead of a name */
__CREDIRECT(,int,__NOTHROW_NCX,futimes,(__fd_t __fd, struct timeval const __tvp[2]),futimes64,(__fd,__tvp))
#elif defined(__CRT_HAVE_futimes) && !defined(__USE_TIME_BITS64)
/* Same as `utimes', but takes an open file descriptor instead of a name */
__CDECLARE(,int,__NOTHROW_NCX,futimes,(__fd_t __fd, struct timeval const __tvp[2]),(__fd,__tvp))
#elif defined(__CRT_HAVE_futimes64) || (defined(__CRT_HAVE_lutimes) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_futimes)
#include <local/sys.time/futimes.h>
/* Same as `utimes', but takes an open file descriptor instead of a name */
__NAMESPACE_LOCAL_USING_OR_IMPL(futimes, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL futimes)(__fd_t __fd, struct timeval const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futimes))(__fd, __tvp); })
#endif /* ... */
#endif /* __USE_MISC */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_gettimeofday64
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,gettimeofday64,(struct timeval64 *__restrict __tv, __timezone_ptr_t __tz),(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,gettimeofday64,(struct timeval64 *__restrict __tv, __timezone_ptr_t __tz),gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday)
#include <local/sys.time/gettimeofday64.h>
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__NAMESPACE_LOCAL_USING_OR_IMPL(gettimeofday64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL gettimeofday64)(struct timeval64 *__restrict __tv, __timezone_ptr_t __tz) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gettimeofday64))(__tv, __tz); })
#endif /* ... */
#ifdef __CRT_HAVE_getitimer64
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getitimer64,(__itimer_which_t __which, struct itimerval64 *__curr_value),(__which,__curr_value))
#elif defined(__CRT_HAVE_getitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getitimer64,(__itimer_which_t __which, struct itimerval64 *__curr_value),getitimer,(__which,__curr_value))
#elif defined(__CRT_HAVE_getitimer)
#include <local/sys.time/getitimer64.h>
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
__NAMESPACE_LOCAL_USING_OR_IMPL(getitimer64, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL getitimer64)(__itimer_which_t __which, struct itimerval64 *__curr_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getitimer64))(__which, __curr_value); })
#endif /* ... */
#ifdef __CRT_HAVE_setitimer64
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,setitimer64,(__itimer_which_t __which, struct itimerval64 const *__newval, struct itimerval64 *__oldval),(__which,__newval,__oldval))
#elif defined(__CRT_HAVE_setitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,setitimer64,(__itimer_which_t __which, struct itimerval64 const *__newval, struct itimerval64 *__oldval),setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE_setitimer)
#include <local/sys.time/setitimer64.h>
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
__NAMESPACE_LOCAL_USING_OR_IMPL(setitimer64, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL setitimer64)(__itimer_which_t __which, struct itimerval64 const *__newval, struct itimerval64 *__oldval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setitimer64))(__which, __newval, __oldval); })
#endif /* ... */
#ifdef __CRT_HAVE_utimes64
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,utimes64,(char const *__file, struct timeval64 const __tvp[2]),(__file,__tvp))
#elif defined(__CRT_HAVE_utimes) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,utimes64,(char const *__file, struct timeval64 const __tvp[2]),utimes,(__file,__tvp))
#elif defined(__CRT_HAVE_utimes)
#include <local/sys.time/utimes64.h>
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
__NAMESPACE_LOCAL_USING_OR_IMPL(utimes64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL utimes64)(char const *__file, struct timeval64 const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(utimes64))(__file, __tvp); })
#endif /* ... */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_settimeofday64
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
__CDECLARE(,int,__NOTHROW_NCX,settimeofday64,(struct timeval64 const *__tv, struct timezone const *__tz),(__tv,__tz))
#elif defined(__CRT_HAVE_settimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,settimeofday64,(struct timeval64 const *__tv, struct timezone const *__tz),settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_settimeofday)
#include <local/sys.time/settimeofday64.h>
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
__NAMESPACE_LOCAL_USING_OR_IMPL(settimeofday64, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL settimeofday64)(struct timeval64 const *__tv, struct timezone const *__tz) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(settimeofday64))(__tv, __tz); })
#endif /* ... */
#ifdef __CRT_HAVE_adjtime64
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__CDECLARE(,int,__NOTHROW_NCX,adjtime64,(struct timeval64 const *__delta, struct timeval64 *__olddelta),(__delta,__olddelta))
#elif defined(__CRT_HAVE_adjtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__CREDIRECT(,int,__NOTHROW_NCX,adjtime64,(struct timeval64 const *__delta, struct timeval64 *__olddelta),adjtime,(__delta,__olddelta))
#elif defined(__CRT_HAVE_adjtime)
#include <local/sys.time/adjtime64.h>
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
__NAMESPACE_LOCAL_USING_OR_IMPL(adjtime64, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL adjtime64)(struct timeval64 const *__delta, struct timeval64 *__olddelta) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(adjtime64))(__delta, __olddelta); })
#endif /* ... */
#ifdef __CRT_HAVE_lutimes64
/* Same as `utimes', but does not follow symbolic links */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,lutimes64,(char const *__file, struct timeval64 const __tvp[2]),(__file,__tvp))
#elif defined(__CRT_HAVE_lutimes) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Same as `utimes', but does not follow symbolic links */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,lutimes64,(char const *__file, struct timeval64 const __tvp[2]),lutimes,(__file,__tvp))
#elif defined(__CRT_HAVE_lutimes)
#include <local/sys.time/lutimes64.h>
/* Same as `utimes', but does not follow symbolic links */
__NAMESPACE_LOCAL_USING_OR_IMPL(lutimes64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL lutimes64)(char const *__file, struct timeval64 const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lutimes64))(__file, __tvp); })
#endif /* ... */
#ifdef __CRT_HAVE_futimes64
/* Same as `utimes', but does not follow symbolic links */
__CDECLARE(,int,__NOTHROW_NCX,futimes64,(__fd_t __fd, struct timeval64 const __tvp[2]),(__fd,__tvp))
#elif defined(__CRT_HAVE_lutimes) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Same as `utimes', but does not follow symbolic links */
__CREDIRECT(,int,__NOTHROW_NCX,futimes64,(__fd_t __fd, struct timeval64 const __tvp[2]),lutimes,(__fd,__tvp))
#elif defined(__CRT_HAVE_futimes)
#include <local/sys.time/futimes64.h>
/* Same as `utimes', but does not follow symbolic links */
__NAMESPACE_LOCAL_USING_OR_IMPL(futimes64, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL futimes64)(__fd_t __fd, struct timeval64 const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futimes64))(__fd, __tvp); })
#endif /* ... */
#endif /* __USE_MISC */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_futimesat64
/* Same as `utimes', but takes an open file descriptor instead of a name */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,futimesat64,(__fd_t __fd, char const *__file, struct timeval64 const __tvp[2]),(__fd,__file,__tvp))
#elif defined(__CRT_HAVE_futimesat) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Same as `utimes', but takes an open file descriptor instead of a name */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,futimesat64,(__fd_t __fd, char const *__file, struct timeval64 const __tvp[2]),futimesat,(__fd,__file,__tvp))
#elif defined(__CRT_HAVE_futimesat)
#include <local/sys.time/futimesat64.h>
/* Same as `utimes', but takes an open file descriptor instead of a name */
__NAMESPACE_LOCAL_USING_OR_IMPL(futimesat64, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_NCX(__LIBCCALL futimesat64)(__fd_t __fd, char const *__file, struct timeval64 const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futimesat64))(__fd, __file, __tvp); })
#endif /* ... */
#endif /* __USE_GNU */
#endif /* __USE_TIME64 */

#ifdef __USE_MISC
#undef timerisset
#undef timerclear
#undef timercmp
#define timerisset(tvp) ((tvp)->tv_sec || (tvp)->tv_usec)
#define timerclear(tvp) ((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define timercmp(a, b, CMP)           \
	(((a)->tv_sec == (b)->tv_sec)     \
	 ? ((a)->tv_usec CMP(b)->tv_usec) \
	 : ((a)->tv_sec CMP(b)->tv_sec))
#define timeradd(a, b, result)                           \
	do {                                                 \
		(result)->tv_sec  = (a)->tv_sec + (b)->tv_sec;   \
		(result)->tv_usec = (a)->tv_usec + (b)->tv_usec; \
		if ((result)->tv_usec >= 1000000) {              \
			++(result)->tv_sec;                          \
			(result)->tv_usec -= 1000000;                \
		}                                                \
	} __WHILE0
#define timersub(a, b, result)                           \
	do {                                                 \
		(result)->tv_sec  = (a)->tv_sec - (b)->tv_sec;   \
		(result)->tv_usec = (a)->tv_usec - (b)->tv_usec; \
		if ((result)->tv_usec < 0) {                     \
			--(result)->tv_sec;                          \
			(result)->tv_usec += 1000000;                \
		}                                                \
	} __WHILE0
#endif /* __USE_MISC */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_TIME_H */
