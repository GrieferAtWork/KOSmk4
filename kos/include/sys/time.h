/* HASH CRC-32:0x5df58fda */
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
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/time.h) */
/* (#) Portability: DJGPP         (/include/sys/time.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/time.h) */
/* (#) Portability: FreeBSD       (/sys/sys/time.h) */
/* (#) Portability: GNU C Library (/time/sys/time.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/sys/time.h) */
/* (#) Portability: NetBSD        (/sys/sys/time.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/time.h) */
/* (#) Portability: OpenBSD       (/sys/sys/time.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/time.h) */
/* (#) Portability: diet libc     (/include/sys/time.h) */
/* (#) Portability: libbsd        (/include/bsd/sys/time.h) */
/* (#) Portability: libc4/5       (/include/sys/time.h) */
/* (#) Portability: libcmini      (/include/sys/time.h) */
/* (#) Portability: mintlib       (/include/sys/time.h) */
/* (#) Portability: musl libc     (/include/sys/time.h) */
/* (#) Portability: uClibc        (/include/sys/time.h) */
#ifndef _SYS_TIME_H
#define _SYS_TIME_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/os/itimer.h>
#include <bits/types.h>
#include <bits/os/itimerval.h>
#include <sys/select.h>

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
#define __time_t_defined
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

#ifndef __suseconds_t_defined
#define __suseconds_t_defined
typedef __suseconds_t suseconds_t;
#endif /* !__suseconds_t_defined */

#ifdef __USE_GNU
#ifndef TIMEVAL_TO_TIMESPEC
#define TIMEVAL_TO_TIMESPEC(tv, ts) \
	(void)((ts)->tv_sec = (tv)->tv_sec, (ts)->tv_nsec = (tv)->tv_usec * 1000)
#endif /* !TIMEVAL_TO_TIMESPEC */
#ifndef TIMESPEC_TO_TIMEVAL
#define TIMESPEC_TO_TIMEVAL(tv, ts) \
	(void)((tv)->tv_sec = (ts)->tv_sec, (tv)->tv_usec = (ts)->tv_nsec / 1000)
#endif /* !TIMESPEC_TO_TIMEVAL */
#endif /* __USE_GNU */

#ifdef __USE_MISC
#ifndef __struct_timezone_defined
#define __struct_timezone_defined
#if !defined(timezone) || defined(__CRT_HAVE_timezone) || defined(__CRT_HAVE___timezone)
struct timezone {
	__INT32_TYPE__ tz_minuteswest; /* Minutes west of GMT. */
	__INT32_TYPE__ tz_dsttime;     /* Nonzero if daylight-savings-time can ever be effect. */
};
#else /* ... */
#undef __struct_timezone_defined
#warning "With the linked libc, `struct timezone' from <sys/time.h> cannot be used after <time.h> was included"
#endif /* !... */
#endif /* !__struct_timezone_defined */
#endif /* __USE_MISC */

#ifndef ____timezone_ptr_t_defined
#define ____timezone_ptr_t_defined
#ifdef __USE_MISC
typedef struct timezone *__restrict __timezone_ptr_t;
#else /* __USE_MISC */
typedef void *__restrict __timezone_ptr_t;
#endif /* !__USE_MISC */
#endif /* !____timezone_ptr_t_defined */

#if defined(__CRT_HAVE_gettimeofday) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> gettimeofday(2), gettimeofday64(2) */
__CDECLARE(__ATTR_ACCESS_WR_OPT(1) __ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,gettimeofday,(struct timeval *__restrict __tv, __timezone_ptr_t __tz),(__tv,__tz))
#elif defined(__CRT_HAVE___gettimeofday) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> gettimeofday(2), gettimeofday64(2) */
__CREDIRECT(__ATTR_ACCESS_WR_OPT(1) __ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,gettimeofday,(struct timeval *__restrict __tv, __timezone_ptr_t __tz),__gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___libc_gettimeofday) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> gettimeofday(2), gettimeofday64(2) */
__CREDIRECT(__ATTR_ACCESS_WR_OPT(1) __ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,gettimeofday,(struct timeval *__restrict __tv, __timezone_ptr_t __tz),__libc_gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> gettimeofday(2), gettimeofday64(2) */
__CREDIRECT(__ATTR_ACCESS_WR_OPT(1) __ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,gettimeofday,(struct timeval *__restrict __tv, __timezone_ptr_t __tz),gettimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday) || defined(__CRT_HAVE___libc_gettimeofday)
#include <libc/local/sys.time/gettimeofday.h>
/* >> gettimeofday(2), gettimeofday64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(gettimeofday, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR_OPT(1) __ATTR_ACCESS_WR_OPT(2) int __NOTHROW_NCX(__LIBCCALL gettimeofday)(struct timeval *__restrict __tv, __timezone_ptr_t __tz) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gettimeofday))(__tv, __tz); })
#endif /* ... */
#if defined(__CRT_HAVE_getitimer) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> getitimer(2), getitimer64(2) */
__CDECLARE(__ATTR_ACCESS_WR(2),int,__NOTHROW_NCX,getitimer,(__itimer_which_t __which, struct itimerval *__curr_value),(__which,__curr_value))
#elif defined(__CRT_HAVE___getitimer) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> getitimer(2), getitimer64(2) */
__CREDIRECT(__ATTR_ACCESS_WR(2),int,__NOTHROW_NCX,getitimer,(__itimer_which_t __which, struct itimerval *__curr_value),__getitimer,(__which,__curr_value))
#elif defined(__CRT_HAVE___libc_getitimer) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> getitimer(2), getitimer64(2) */
__CREDIRECT(__ATTR_ACCESS_WR(2),int,__NOTHROW_NCX,getitimer,(__itimer_which_t __which, struct itimerval *__curr_value),__libc_getitimer,(__which,__curr_value))
#elif defined(__CRT_HAVE_getitimer64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> getitimer(2), getitimer64(2) */
__CREDIRECT(__ATTR_ACCESS_WR(2),int,__NOTHROW_NCX,getitimer,(__itimer_which_t __which, struct itimerval *__curr_value),getitimer64,(__which,__curr_value))
#elif defined(__CRT_HAVE_getitimer64) || defined(__CRT_HAVE_getitimer) || defined(__CRT_HAVE___getitimer) || defined(__CRT_HAVE___libc_getitimer)
#include <libc/local/sys.time/getitimer.h>
/* >> getitimer(2), getitimer64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getitimer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(2) int __NOTHROW_NCX(__LIBCCALL getitimer)(__itimer_which_t __which, struct itimerval *__curr_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getitimer))(__which, __curr_value); })
#endif /* ... */
#if defined(__CRT_HAVE_setitimer) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> setitimer(2), setitimer64(2) */
__CDECLARE(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR_OPT(3),int,__NOTHROW_NCX,setitimer,(__itimer_which_t __which, struct itimerval const *__newval, struct itimerval *__oldval),(__which,__newval,__oldval))
#elif defined(__CRT_HAVE___setitimer) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> setitimer(2), setitimer64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR_OPT(3),int,__NOTHROW_NCX,setitimer,(__itimer_which_t __which, struct itimerval const *__newval, struct itimerval *__oldval),__setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE___libc_setitimer) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> setitimer(2), setitimer64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR_OPT(3),int,__NOTHROW_NCX,setitimer,(__itimer_which_t __which, struct itimerval const *__newval, struct itimerval *__oldval),__libc_setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE_setitimer64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> setitimer(2), setitimer64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR_OPT(3),int,__NOTHROW_NCX,setitimer,(__itimer_which_t __which, struct itimerval const *__newval, struct itimerval *__oldval),setitimer64,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE_setitimer64) || defined(__CRT_HAVE_setitimer) || defined(__CRT_HAVE___setitimer) || defined(__CRT_HAVE___libc_setitimer)
#include <libc/local/sys.time/setitimer.h>
/* >> setitimer(2), setitimer64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(setitimer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR_OPT(3) int __NOTHROW_NCX(__LIBCCALL setitimer)(__itimer_which_t __which, struct itimerval const *__newval, struct itimerval *__oldval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setitimer))(__which, __newval, __oldval); })
#endif /* ... */
#if defined(__CRT_HAVE_utimes) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utimes(2), utimes64(2) */
__CDECLARE(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,utimes,(char const *__file, struct timeval const __tvp[2]),(__file,__tvp))
#elif defined(__CRT_HAVE___utimes) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utimes(2), utimes64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,utimes,(char const *__file, struct timeval const __tvp[2]),__utimes,(__file,__tvp))
#elif defined(__CRT_HAVE_utimes64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utimes(2), utimes64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,utimes,(char const *__file, struct timeval const __tvp[2]),utimes64,(__file,__tvp))
#elif defined(__CRT_HAVE_utimes64) || defined(__CRT_HAVE_utimes) || defined(__CRT_HAVE___utimes)
#include <libc/local/sys.time/utimes.h>
/* >> utimes(2), utimes64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(utimes, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2) int __NOTHROW_NCX(__LIBCCALL utimes)(char const *__file, struct timeval const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(utimes))(__file, __tvp); })
#endif /* ... */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_futimesat) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futimesat(2), futimesat64(2) */
__CDECLARE(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3),int,__NOTHROW_NCX,futimesat,(__fd_t __fd, char const *__file, struct timeval const __tvp[2]),(__fd,__file,__tvp))
#elif defined(__CRT_HAVE_futimesat64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futimesat(2), futimesat64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3),int,__NOTHROW_NCX,futimesat,(__fd_t __fd, char const *__file, struct timeval const __tvp[2]),futimesat64,(__fd,__file,__tvp))
#elif defined(__CRT_HAVE_futimesat64) || defined(__CRT_HAVE_futimesat)
#include <libc/local/sys.time/futimesat.h>
/* >> futimesat(2), futimesat64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(futimesat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3) int __NOTHROW_NCX(__LIBCCALL futimesat)(__fd_t __fd, char const *__file, struct timeval const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futimesat))(__fd, __file, __tvp); })
#endif /* ... */
#endif /* __USE_GNU */

#ifdef __USE_MISC
#if defined(__CRT_HAVE_settimeofday) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> settimeofday(2), settimeofday64(2) */
__CDECLARE(__ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,settimeofday,(struct timeval const *__tv, struct timezone const *__tz),(__tv,__tz))
#elif defined(__CRT_HAVE___settimeofday) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> settimeofday(2), settimeofday64(2) */
__CREDIRECT(__ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,settimeofday,(struct timeval const *__tv, struct timezone const *__tz),__settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___libc_settimeofday) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> settimeofday(2), settimeofday64(2) */
__CREDIRECT(__ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,settimeofday,(struct timeval const *__tv, struct timezone const *__tz),__libc_settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_settimeofday64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> settimeofday(2), settimeofday64(2) */
__CREDIRECT(__ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,settimeofday,(struct timeval const *__tv, struct timezone const *__tz),settimeofday64,(__tv,__tz))
#elif defined(__CRT_HAVE_settimeofday64) || defined(__CRT_HAVE_settimeofday) || defined(__CRT_HAVE___settimeofday) || defined(__CRT_HAVE___libc_settimeofday)
#include <libc/local/sys.time/settimeofday.h>
/* >> settimeofday(2), settimeofday64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(settimeofday, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) int __NOTHROW_NCX(__LIBCCALL settimeofday)(struct timeval const *__tv, struct timezone const *__tz) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(settimeofday))(__tv, __tz); })
#endif /* ... */
#if defined(__CRT_HAVE_adjtime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> adjtime(3), adjtime64(3) */
__CDECLARE(__ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,adjtime,(struct timeval const *__delta, struct timeval *__olddelta),(__delta,__olddelta))
#elif defined(__CRT_HAVE___adjtime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> adjtime(3), adjtime64(3) */
__CREDIRECT(__ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,adjtime,(struct timeval const *__delta, struct timeval *__olddelta),__adjtime,(__delta,__olddelta))
#elif defined(__CRT_HAVE_adjtime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> adjtime(3), adjtime64(3) */
__CREDIRECT(__ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,adjtime,(struct timeval const *__delta, struct timeval *__olddelta),adjtime64,(__delta,__olddelta))
#elif defined(__CRT_HAVE_adjtime64) || defined(__CRT_HAVE_adjtime) || defined(__CRT_HAVE___adjtime)
#include <libc/local/sys.time/adjtime.h>
/* >> adjtime(3), adjtime64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(adjtime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_WR_OPT(2) int __NOTHROW_NCX(__LIBCCALL adjtime)(struct timeval const *__delta, struct timeval *__olddelta) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(adjtime))(__delta, __olddelta); })
#endif /* ... */
#if defined(__CRT_HAVE_lutimes) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> lutimes(2), lutimes64(2) */
__CDECLARE(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,lutimes,(char const *__file, struct timeval const __tvp[2]),(__file,__tvp))
#elif defined(__CRT_HAVE_lutimes64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> lutimes(2), lutimes64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,lutimes,(char const *__file, struct timeval const __tvp[2]),lutimes64,(__file,__tvp))
#elif defined(__CRT_HAVE_lutimes64) || defined(__CRT_HAVE_lutimes)
#include <libc/local/sys.time/lutimes.h>
/* >> lutimes(2), lutimes64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(lutimes, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2) int __NOTHROW_NCX(__LIBCCALL lutimes)(char const *__file, struct timeval const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lutimes))(__file, __tvp); })
#endif /* ... */
#if defined(__CRT_HAVE_futimes) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futimes(2), futimes64(2) */
__CDECLARE(__ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,futimes,(__fd_t __fd, struct timeval const __tvp[2]),(__fd,__tvp))
#elif defined(__CRT_HAVE_futimes64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futimes(2), futimes64(2) */
__CREDIRECT(__ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,futimes,(__fd_t __fd, struct timeval const __tvp[2]),futimes64,(__fd,__tvp))
#elif (defined(__CRT_HAVE_lutimes) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_futimes64) || defined(__CRT_HAVE_futimes)
#include <libc/local/sys.time/futimes.h>
/* >> futimes(2), futimes64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(futimes, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO_OPT(2) int __NOTHROW_NCX(__LIBCCALL futimes)(__fd_t __fd, struct timeval const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futimes))(__fd, __tvp); })
#endif /* ... */
#endif /* __USE_MISC */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_gettimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> gettimeofday(2), gettimeofday64(2) */
__CREDIRECT(__ATTR_ACCESS_WR_OPT(1) __ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,gettimeofday64,(struct timeval64 *__restrict __tv, __timezone_ptr_t __tz),gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday64)
/* >> gettimeofday(2), gettimeofday64(2) */
__CDECLARE(__ATTR_ACCESS_WR_OPT(1) __ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,gettimeofday64,(struct timeval64 *__restrict __tv, __timezone_ptr_t __tz),(__tv,__tz))
#elif defined(__CRT_HAVE___gettimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> gettimeofday(2), gettimeofday64(2) */
__CREDIRECT(__ATTR_ACCESS_WR_OPT(1) __ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,gettimeofday64,(struct timeval64 *__restrict __tv, __timezone_ptr_t __tz),__gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___libc_gettimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> gettimeofday(2), gettimeofday64(2) */
__CREDIRECT(__ATTR_ACCESS_WR_OPT(1) __ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,gettimeofday64,(struct timeval64 *__restrict __tv, __timezone_ptr_t __tz),__libc_gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday) || defined(__CRT_HAVE___libc_gettimeofday)
#include <libc/local/sys.time/gettimeofday64.h>
/* >> gettimeofday(2), gettimeofday64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(gettimeofday64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR_OPT(1) __ATTR_ACCESS_WR_OPT(2) int __NOTHROW_NCX(__LIBCCALL gettimeofday64)(struct timeval64 *__restrict __tv, __timezone_ptr_t __tz) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gettimeofday64))(__tv, __tz); })
#endif /* ... */
#if defined(__CRT_HAVE_getitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> getitimer(2), getitimer64(2) */
__CREDIRECT(__ATTR_ACCESS_WR(2),int,__NOTHROW_NCX,getitimer64,(__itimer_which_t __which, struct itimerval64 *__curr_value),getitimer,(__which,__curr_value))
#elif defined(__CRT_HAVE___getitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> getitimer(2), getitimer64(2) */
__CREDIRECT(__ATTR_ACCESS_WR(2),int,__NOTHROW_NCX,getitimer64,(__itimer_which_t __which, struct itimerval64 *__curr_value),__getitimer,(__which,__curr_value))
#elif defined(__CRT_HAVE___libc_getitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> getitimer(2), getitimer64(2) */
__CREDIRECT(__ATTR_ACCESS_WR(2),int,__NOTHROW_NCX,getitimer64,(__itimer_which_t __which, struct itimerval64 *__curr_value),__libc_getitimer,(__which,__curr_value))
#elif defined(__CRT_HAVE_getitimer64)
/* >> getitimer(2), getitimer64(2) */
__CDECLARE(__ATTR_ACCESS_WR(2),int,__NOTHROW_NCX,getitimer64,(__itimer_which_t __which, struct itimerval64 *__curr_value),(__which,__curr_value))
#elif defined(__CRT_HAVE_getitimer) || defined(__CRT_HAVE___getitimer) || defined(__CRT_HAVE___libc_getitimer)
#include <libc/local/sys.time/getitimer64.h>
/* >> getitimer(2), getitimer64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getitimer64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(2) int __NOTHROW_NCX(__LIBCCALL getitimer64)(__itimer_which_t __which, struct itimerval64 *__curr_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getitimer64))(__which, __curr_value); })
#endif /* ... */
#if defined(__CRT_HAVE_setitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> setitimer(2), setitimer64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR_OPT(3),int,__NOTHROW_NCX,setitimer64,(__itimer_which_t __which, struct itimerval64 const *__newval, struct itimerval64 *__oldval),setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE___setitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> setitimer(2), setitimer64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR_OPT(3),int,__NOTHROW_NCX,setitimer64,(__itimer_which_t __which, struct itimerval64 const *__newval, struct itimerval64 *__oldval),__setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE___libc_setitimer) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> setitimer(2), setitimer64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR_OPT(3),int,__NOTHROW_NCX,setitimer64,(__itimer_which_t __which, struct itimerval64 const *__newval, struct itimerval64 *__oldval),__libc_setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE_setitimer64)
/* >> setitimer(2), setitimer64(2) */
__CDECLARE(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR_OPT(3),int,__NOTHROW_NCX,setitimer64,(__itimer_which_t __which, struct itimerval64 const *__newval, struct itimerval64 *__oldval),(__which,__newval,__oldval))
#elif defined(__CRT_HAVE_setitimer) || defined(__CRT_HAVE___setitimer) || defined(__CRT_HAVE___libc_setitimer)
#include <libc/local/sys.time/setitimer64.h>
/* >> setitimer(2), setitimer64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(setitimer64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR_OPT(3) int __NOTHROW_NCX(__LIBCCALL setitimer64)(__itimer_which_t __which, struct itimerval64 const *__newval, struct itimerval64 *__oldval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setitimer64))(__which, __newval, __oldval); })
#endif /* ... */
#if defined(__CRT_HAVE_utimes) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utimes(2), utimes64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,utimes64,(char const *__file, struct timeval64 const __tvp[2]),utimes,(__file,__tvp))
#elif defined(__CRT_HAVE___utimes) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utimes(2), utimes64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,utimes64,(char const *__file, struct timeval64 const __tvp[2]),__utimes,(__file,__tvp))
#elif defined(__CRT_HAVE_utimes64)
/* >> utimes(2), utimes64(2) */
__CDECLARE(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,utimes64,(char const *__file, struct timeval64 const __tvp[2]),(__file,__tvp))
#elif defined(__CRT_HAVE_utimes) || defined(__CRT_HAVE___utimes)
#include <libc/local/sys.time/utimes64.h>
/* >> utimes(2), utimes64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(utimes64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2) int __NOTHROW_NCX(__LIBCCALL utimes64)(char const *__file, struct timeval64 const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(utimes64))(__file, __tvp); })
#endif /* ... */

#ifdef __USE_MISC
#if defined(__CRT_HAVE_settimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> settimeofday(2), settimeofday64(2) */
__CREDIRECT(__ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,settimeofday64,(struct timeval64 const *__tv, struct timezone const *__tz),settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___settimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> settimeofday(2), settimeofday64(2) */
__CREDIRECT(__ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,settimeofday64,(struct timeval64 const *__tv, struct timezone const *__tz),__settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___libc_settimeofday) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> settimeofday(2), settimeofday64(2) */
__CREDIRECT(__ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,settimeofday64,(struct timeval64 const *__tv, struct timezone const *__tz),__libc_settimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE_settimeofday64)
/* >> settimeofday(2), settimeofday64(2) */
__CDECLARE(__ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,settimeofday64,(struct timeval64 const *__tv, struct timezone const *__tz),(__tv,__tz))
#elif defined(__CRT_HAVE_settimeofday) || defined(__CRT_HAVE___settimeofday) || defined(__CRT_HAVE___libc_settimeofday)
#include <libc/local/sys.time/settimeofday64.h>
/* >> settimeofday(2), settimeofday64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(settimeofday64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(2) int __NOTHROW_NCX(__LIBCCALL settimeofday64)(struct timeval64 const *__tv, struct timezone const *__tz) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(settimeofday64))(__tv, __tz); })
#endif /* ... */
#if defined(__CRT_HAVE_adjtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> adjtime(3), adjtime64(3) */
__CREDIRECT(__ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,adjtime64,(struct timeval64 const *__delta, struct timeval64 *__olddelta),adjtime,(__delta,__olddelta))
#elif defined(__CRT_HAVE_adjtime64)
/* >> adjtime(3), adjtime64(3) */
__CDECLARE(__ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_WR_OPT(2),int,__NOTHROW_NCX,adjtime64,(struct timeval64 const *__delta, struct timeval64 *__olddelta),(__delta,__olddelta))
#elif defined(__CRT_HAVE_adjtime) || defined(__CRT_HAVE___adjtime)
#include <libc/local/sys.time/adjtime64.h>
/* >> adjtime(3), adjtime64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(adjtime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_WR_OPT(2) int __NOTHROW_NCX(__LIBCCALL adjtime64)(struct timeval64 const *__delta, struct timeval64 *__olddelta) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(adjtime64))(__delta, __olddelta); })
#endif /* ... */
#if defined(__CRT_HAVE_lutimes) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> lutimes(2), lutimes64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,lutimes64,(char const *__file, struct timeval64 const __tvp[2]),lutimes,(__file,__tvp))
#elif defined(__CRT_HAVE_lutimes64)
/* >> lutimes(2), lutimes64(2) */
__CDECLARE(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,lutimes64,(char const *__file, struct timeval64 const __tvp[2]),(__file,__tvp))
#elif defined(__CRT_HAVE_lutimes)
#include <libc/local/sys.time/lutimes64.h>
/* >> lutimes(2), lutimes64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(lutimes64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2) int __NOTHROW_NCX(__LIBCCALL lutimes64)(char const *__file, struct timeval64 const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lutimes64))(__file, __tvp); })
#endif /* ... */
#if defined(__CRT_HAVE_lutimes) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> lutimes(2), lutimes64(2) */
__CREDIRECT(__ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,futimes64,(__fd_t __fd, struct timeval64 const __tvp[2]),lutimes,(__fd,__tvp))
#elif defined(__CRT_HAVE_futimes64)
/* >> lutimes(2), lutimes64(2) */
__CDECLARE(__ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_NCX,futimes64,(__fd_t __fd, struct timeval64 const __tvp[2]),(__fd,__tvp))
#elif defined(__CRT_HAVE_futimes)
#include <libc/local/sys.time/futimes64.h>
/* >> lutimes(2), lutimes64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(futimes64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO_OPT(2) int __NOTHROW_NCX(__LIBCCALL futimes64)(__fd_t __fd, struct timeval64 const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futimes64))(__fd, __tvp); })
#endif /* ... */
#endif /* __USE_MISC */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_futimesat) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> futimesat(2), futimesat64(2) */
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3),int,__NOTHROW_NCX,futimesat64,(__fd_t __fd, char const *__file, struct timeval64 const __tvp[2]),futimesat,(__fd,__file,__tvp))
#elif defined(__CRT_HAVE_futimesat64)
/* >> futimesat(2), futimesat64(2) */
__CDECLARE(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3),int,__NOTHROW_NCX,futimesat64,(__fd_t __fd, char const *__file, struct timeval64 const __tvp[2]),(__fd,__file,__tvp))
#elif defined(__CRT_HAVE_futimesat)
#include <libc/local/sys.time/futimesat64.h>
/* >> futimesat(2), futimesat64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(futimesat64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3) int __NOTHROW_NCX(__LIBCCALL futimesat64)(__fd_t __fd, char const *__file, struct timeval64 const __tvp[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futimesat64))(__fd, __file, __tvp); })
#endif /* ... */
#endif /* __USE_GNU */
#endif /* __USE_TIME64 */

#ifdef __USE_MISC
#undef timerisset
#undef timerclear
#undef timercmp
#define timerisset(tvp) ((tvp)->tv_sec || (tvp)->tv_usec)
#define timerclear(tvp) ((tvp)->tv_sec = 0, (tvp)->tv_usec = 0)
#define timercmp(a, b, CMP)            \
	(((a)->tv_sec == (b)->tv_sec)      \
	 ? ((a)->tv_usec CMP (b)->tv_usec) \
	 : ((a)->tv_sec CMP (b)->tv_sec))
#define timeradd(a, b, result)                        \
	((result)->tv_sec  = (a)->tv_sec + (b)->tv_sec,   \
	 (result)->tv_usec = (a)->tv_usec + (b)->tv_usec, \
	 (result)->tv_usec >= 1000000                     \
	 ? (void)(++(result)->tv_sec,                     \
	          (result)->tv_usec -= 1000000)           \
	 : (void)0)
#define timersub(a, b, result)                        \
	((result)->tv_sec  = (a)->tv_sec - (b)->tv_sec,   \
	 (result)->tv_usec = (a)->tv_usec - (b)->tv_usec, \
	 (result)->tv_usec < 0                            \
	 ? (void)(--(result)->tv_sec,                     \
	          (result)->tv_usec += 1000000)           \
	 : (void)0)
#endif /* __USE_MISC */

#ifdef __USE_NETBSD
#undef timespecisset
#undef timespecclear
#undef timespeccmp
#define timespecisset(tsp) ((tsp)->tv_sec || (tsp)->tv_nsec)
#define timespecclear(tsp) ((tsp)->tv_sec = 0, (tsp)->tv_nsec = 0)
#define timespeccmp(a, b, CMP)         \
	(((a)->tv_sec == (b)->tv_sec)      \
	 ? ((a)->tv_nsec CMP (b)->tv_nsec) \
	 : ((a)->tv_sec CMP (b)->tv_sec))
#define timespecadd(tsp, usp, vsp)                     \
	((vsp)->tv_sec  = (tsp)->tv_sec + (usp)->tv_sec,   \
	 (vsp)->tv_nsec = (tsp)->tv_nsec + (usp)->tv_nsec, \
	 (vsp)->tv_nsec >= 1000000000L                     \
	 ? (void)(++(vsp)->tv_sec,                         \
	          (vsp)->tv_nsec -= 1000000000L)           \
	 : (void)0)
#define timespecsub(tsp, usp, vsp)                     \
	((vsp)->tv_sec  = (tsp)->tv_sec - (usp)->tv_sec,   \
	 (vsp)->tv_nsec = (tsp)->tv_nsec - (usp)->tv_nsec, \
	 (vsp)->tv_nsec < 0                                \
	 ? (void)(--(vsp)->tv_sec,                         \
	          (vsp)->tv_nsec += 1000000000L)           \
	 : (void)0)
#define timespec2ns(tsp) \
	(((__uint64_t)(tsp)->tv_sec) * 1000000000L + (tsp)->tv_nsec)
#endif /* __USE_NETBSD */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_TIME_H */
