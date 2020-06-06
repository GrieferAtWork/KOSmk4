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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(time_t   = __TM_TYPE(time))]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(timeval32  = __timeval32)]
%[define_replacement(timeval64  = __timeval64)]


%{
#include <features.h>
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

/*[[[enum]]]*/
#ifdef __CC__
typedef enum __itimer_which {
	ITIMER_REAL    = 0,
	ITIMER_VIRTUAL = 1,
	ITIMER_PROF    = 2
} __itimer_which_t;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define ITIMER_REAL    ITIMER_REAL
#define ITIMER_VIRTUAL ITIMER_VIRTUAL
#define ITIMER_PROF    ITIMER_PROF
#else /* __COMPILER_PREFERR_ENUMS */
#define ITIMER_REAL    0
#define ITIMER_VIRTUAL 1
#define ITIMER_PROF    2
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

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

}

[ignore][section(".text.crt.time")][doc_alias(gettimeofday)][alias(__gettimeofday)]
gettimeofday32:([[nonnull]] struct __timeval32 *__restrict tv,
                [[nullable]] __timezone_ptr_t tz) -> int = gettimeofday?;

[ignore][section(.text.crt.timer)][doc_alias(getitimer)]
getitimer32:(__itimer_which_t which, [[nonnull]] struct __itimerval32 *curr_value) -> int = getitimer?;

[ignore][section(.text.crt.timer)][doc_alias(setitimer)]
setitimer32:(__itimer_which_t which,
             [[nonnull]] struct __itimerval32 const *__restrict newval,
             [[nullable]] struct __itimerval32 *__restrict oldval) -> int = setitimer?;

[ignore][section(.text.crt.fs.modify_time)][doc_alias(utimes)]
utimes32:([[nonnull]] char const *file, [[nonnull]] struct __timeval32 const tvp[2]) -> int = utimes?;

[ignore][section(.text.crt.fs.modify_time)][doc_alias(futimesat)]
futimesat32:($fd_t fd, [[nonnull]] char const *file, [[nonnull]] struct __timeval32 const tvp[2]) -> int = futimesat?;

[ignore][section(.text.crt.system.adjtime)][doc_alias(settimeofday)]
settimeofday32:([[nullable]] struct __timeval32 const *tv, [[nullable]] struct timezone const *tz) -> int = settimeofday?;

[ignore][section(.text.crt.system.adjtime)][doc_alias(adjtime)]
adjtime32:([[nullable]] struct __timeval32 const *delta, [[nullable]] struct __timeval32 *olddelta) -> int = adjtime?;

[ignore][section(.text.crt.fs.modify_time)][doc_alias(lutimes)]
lutimes32:([[nonnull]] char const *file, [[nullable]] struct __timeval32 const tvp[2]) -> int = lutimes?;

[ignore][section(.text.crt.fs.modify_time)][doc_alias(lutimes)]
futimes32:($fd_t fd, [[nullable]] struct __timeval32 const tvp[2]) -> int = futimes?;



@@Get the current time of day and timezone information,
@@putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
@@Returns 0 on success, -1 on errors.
@@NOTE: This form of timezone information is obsolete.
@@Use the functions and variables declared in <time.h> instead
[section(".text.crt.time")][alternate_name(__gettimeofday), no_crt_self_import]
[if(defined(__USE_TIME_BITS64)), preferred_alias(gettimeofday64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(gettimeofday, __gettimeofday)]
[requires(defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE_gettimeofday64))]
gettimeofday:([[nonnull]] struct timeval *__restrict tv, [[nullable]] __timezone_ptr_t tz) -> int {
#ifdef __CRT_HAVE_gettimeofday
	int result;
	struct __timeval32 tv32;
	if (!tv)
		return gettimeofday32(NULL, tz);
	result = gettimeofday32(&tv32, tz);
	if likely(!result) {
		tv->tv_sec  = (time64_t)tv32.tv_sec;
		tv->tv_usec = tv32.tv_usec;
	}
	return result;
#else /* __CRT_HAVE_gettimeofday */
	int result;
	struct __timeval64 tv64;
	if (!tv)
		return gettimeofday64(NULL, tz);
	result = gettimeofday64(&tv64, tz);
	if likely(!result) {
		tv->tv_sec  = (time32_t)tv64.tv_sec;
		tv->tv_usec = tv64.tv_usec;
	}
	return result;
#endif /* !__CRT_HAVE_gettimeofday */
}


@@Set *VALUE to the current setting of timer WHICH.
@@Return 0 on success, -1 on errors
[section(".text.crt.time"), no_crt_self_import]
[if(defined(__USE_TIME_BITS64)), preferred_alias(getitimer64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(getitimer)]
[requires(defined(__CRT_HAVE_getitimer) || defined(__CRT_HAVE_getitimer64))]
getitimer:(__itimer_which_t which, [[nonnull]] struct itimerval *curr_value) -> int {
#ifdef __CRT_HAVE_getitimer
	int result;
	struct __itimerval32 tv32;
	result = getitimer32(which, &tv32);
	if likely(!result) {
		curr_value->@it_interval@.tv_sec  = (time64_t)tv32.@it_interval@.tv_sec;
		curr_value->@it_interval@.tv_usec = tv32.@it_interval@.tv_usec;
		curr_value->@it_value@.tv_sec     = (time64_t)tv32.@it_value@.tv_sec;
		curr_value->@it_value@.tv_usec    = tv32.@it_value@.tv_usec;
	}
	return result;
#else /* __CRT_HAVE_getitimer */
	int result;
	struct __timeval64 tv64;
	result = getitimer64(which, &tv64);
	if likely(!result) {
		curr_value->@it_interval@.tv_sec  = (time32_t)tv64.@it_interval@.tv_sec;
		curr_value->@it_interval@.tv_usec = tv64.@it_interval@.tv_usec;
		curr_value->@it_value@.tv_sec     = (time32_t)tv64.@it_value@.tv_sec;
		curr_value->@it_value@.tv_usec    = tv64.@it_value@.tv_usec;
	}
	return result;
#endif /* !__CRT_HAVE_getitimer */
}

@@Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
@@Returns 0 on success, -1 on errors
[section(".text.crt.time"), no_crt_self_import]
[if(defined(__USE_TIME_BITS64)), preferred_alias(setitimer64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(setitimer)]
[requires(defined(__CRT_HAVE_setitimer) || defined(__CRT_HAVE_setitimer64))]
setitimer:(__itimer_which_t which,
           [[nonnull]] struct itimerval const *newval,
           [[nullable]] struct itimerval *oldval) -> int {
#ifdef __CRT_HAVE_setitimer
	int result;
	struct __itimerval32 new32, old32;
	new32.@it_interval@.tv_sec  = (time32_t)newval->@it_interval@.tv_sec;
	new32.@it_interval@.tv_usec = newval->@it_interval@.tv_usec;
	new32.@it_value@.tv_sec     = (time32_t)newval->@it_value@.tv_sec;
	new32.@it_value@.tv_usec    = newval->@it_value@.tv_usec;
	result = setitimer32(which, &new32, oldval ? &old32 : NULL);
	if (likely(!result) && oldval) {
		oldval->@it_interval@.tv_sec  = (time64_t)old32.@it_interval@.tv_sec;
		oldval->@it_interval@.tv_usec = old32.@it_interval@.tv_usec;
		oldval->@it_value@.tv_sec     = (time64_t)old32.@it_value@.tv_sec;
		oldval->@it_value@.tv_usec    = old32.@it_value@.tv_usec;
	}
	return result;
#else /* __CRT_HAVE_setitimer */
	int result;
	struct __itimerval64 new64, old64;
	new64.@it_interval@.tv_sec  = (time64_t)newval->@it_interval@.tv_sec;
	new64.@it_interval@.tv_usec = newval->@it_interval@.tv_usec;
	new64.@it_value@.tv_sec     = (time64_t)newval->@it_value@.tv_sec;
	new64.@it_value@.tv_usec    = newval->@it_value@.tv_usec;
	result = setitimer64(which, &new64, oldval ? &old64 : NULL);
	if (likely(!result) && oldval) {
		oldval->@it_interval@.tv_sec  = (time32_t)old64.@it_interval@.tv_sec;
		oldval->@it_interval@.tv_usec = old64.@it_interval@.tv_usec;
		oldval->@it_value@.tv_sec     = (time32_t)old64.@it_value@.tv_sec;
		oldval->@it_value@.tv_usec    = old64.@it_value@.tv_usec;
	}
	return result;
#endif /* !__CRT_HAVE_setitimer */
}


@@Change the access time of FILE to TVP[0] and the modification time of
@@FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
@@Returns 0 on success, -1 on errors
[section(.text.crt.fs.modify_time), no_crt_self_import]
[if(defined(__USE_TIME_BITS64)), preferred_alias(utimes64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(utimes)]
[requires(defined(__CRT_HAVE_utimes) || defined(__CRT_HAVE_utimes64))]
utimes:([[nonnull]] char const *file, [[nullable]] struct timeval const tvp[2]) -> int {
#ifdef __CRT_HAVE_utimes
	struct __timeval32 tv32[2];
	if (!tvp)
		return utimes32(file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return utimes32(file, tv32);
#else /* __CRT_HAVE_utimes */
	struct __timeval64 tv64[2];
	if (!tvp)
		return utimes64(file, NULL);
	tv64[0].tv_sec  = (time64_t)tvp[0].tv_sec;
	tv64[0].tv_usec = tvp[0].tv_usec;
	tv64[1].tv_sec  = (time64_t)tvp[1].tv_sec;
	tv64[1].tv_usec = tvp[1].tv_usec;
	return utimes64(file, tv64);
#endif /* !__CRT_HAVE_utimes */
}

%
%#ifdef __USE_GNU
@@Same as `utimes', but takes an open file descriptor instead of a name
[section(.text.crt.fs.modify_time), no_crt_self_import]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futimesat64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futimesat)]
[requires(defined(__CRT_HAVE_futimesat) || defined(__CRT_HAVE_futimesat64))]
futimesat:($fd_t fd, [[nonnull]] char const *file, [[nullable]] struct timeval const tvp[2]) -> int {
#ifdef __CRT_HAVE_utimes
	struct __timeval32 tv32[2];
	if (!tvp)
		return futimesat32(fd, file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return futimesat32(fd, file, tv32);
#else /* __CRT_HAVE_utimes */
	struct __timeval64 tv64[2];
	if (!tvp)
		return futimesat64(fd, file, NULL);
	tv64[0].tv_sec  = (time64_t)tvp[0].tv_sec;
	tv64[0].tv_usec = tvp[0].tv_usec;
	tv64[1].tv_sec  = (time64_t)tvp[1].tv_sec;
	tv64[1].tv_usec = tvp[1].tv_usec;
	return futimesat64(fd, file, tv64);
#endif /* !__CRT_HAVE_utimes */
}
%#endif /* __USE_GNU */

%
%#ifdef __USE_MISC
@@Set the current time of day and timezone information.
@@This call is restricted to the super-user
[section(.text.crt.system.adjtime), no_crt_self_import]
[if(defined(__USE_TIME_BITS64)), preferred_alias(settimeofday64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(settimeofday)]
[requires(defined(__CRT_HAVE_settimeofday) || defined(__CRT_HAVE_settimeofday64))]
settimeofday:([[nullable]] struct timeval const *tv, [[nullable]] struct timezone const *tz) -> int {
#ifdef __CRT_HAVE_settimeofday
	struct __timeval32 tv32;
	if (!tv)
		return settimeofday32(NULL, tz);
	tv32.tv_sec  = (time32_t)tv->tv_sec;
	tv32.tv_usec = tv->tv_usec;
	return settimeofday32(&tv32, tz);
#else /* __CRT_HAVE_settimeofday */
	struct __timeval64 tv64;
	if (!tv)
		return settimeofday64(NULL, tz);
	tv64.tv_sec  = (time64_t)tv->tv_sec;
	tv64.tv_usec = tv->tv_usec;
	return settimeofday64(&tv64, tz);
#endif /* !__CRT_HAVE_settimeofday */
}

@@Adjust the current time of day by the amount in DELTA.
@@If OLDDELTA is not NULL, it is filled in with the amount of time
@@adjustment remaining to be done from the last `adjtime' call.
@@This call is restricted to the super-user
[section(.text.crt.system.adjtime), no_crt_self_import]
[if(defined(__USE_TIME_BITS64)), preferred_alias(adjtime64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(adjtime)]
[requires(defined(__CRT_HAVE_adjtime) || defined(__CRT_HAVE_adjtime64))]
adjtime:([[nullable]] struct timeval const *delta, [[nullable]] struct timeval *olddelta) -> int {
#ifdef __CRT_HAVE_adjtime
	int result;
	struct __timeval32 delta32, olddelta32;
	if (delta) {
		delta32.tv_sec  = (time32_t)delta->tv_sec;
		delta32.tv_usec = delta->tv_usec;
	}
	result = adjtime32(which, delta ? &delta32 : NULL, olddelta ? &olddelta32 : NULL);
	if (likely(!result) && olddelta) {
		olddelta->tv_sec  = (time64_t)olddelta32.tv_sec;
		olddelta->tv_usec = olddelta32.tv_usec;
	}
	return result;
#else /* __CRT_HAVE_adjtime */
	int result;
	struct __timeval64 delta64, olddelta64;
	if (delta) {
		delta64.tv_sec  = (time64_t)delta->tv_sec;
		delta64.tv_usec = delta->tv_usec;
	}
	result = adjtime64(which, delta ? &delta64 : NULL, olddelta ? &olddelta64 : NULL);
	if (likely(!result) && olddelta) {
		olddelta->tv_sec  = (time32_t)olddelta64.tv_sec;
		olddelta->tv_usec = olddelta64.tv_usec;
	}
	return result;
#endif /* !__CRT_HAVE_adjtime */
}

@@Same as `utimes', but does not follow symbolic links
[section(.text.crt.fs.modify_time), no_crt_self_import]
[if(defined(__USE_TIME_BITS64)), preferred_alias(lutimes64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(lutimes)]
[requires(defined(__CRT_HAVE_lutimes) || defined(__CRT_HAVE_lutimes64))]
lutimes:([[nonnull]] char const *file, [[nullable]] struct timeval const tvp[2]) -> int {
#ifdef __CRT_HAVE_utimes
	struct __timeval32 tv32[2];
	if (!tvp)
		return lutimes32(file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return lutimes32(file, tv32);
#else /* __CRT_HAVE_utimes */
	struct __timeval64 tv64[2];
	if (!tvp)
		return lutimes64(file, NULL);
	tv64[0].tv_sec  = (time64_t)tvp[0].tv_sec;
	tv64[0].tv_usec = tvp[0].tv_usec;
	tv64[1].tv_sec  = (time64_t)tvp[1].tv_sec;
	tv64[1].tv_usec = tvp[1].tv_usec;
	return lutimes64(file, tv64);
#endif /* !__CRT_HAVE_utimes */
}


@@Same as `utimes', but takes an open file descriptor instead of a name
[section(.text.crt.fs.modify_time), no_crt_self_import]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futimes64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futimes)]
[requires(defined(__CRT_HAVE_futimes) || defined(__CRT_HAVE_futimes64))]
futimes:($fd_t fd, [[nullable]] struct timeval const tvp[2]) -> int {
#ifdef __CRT_HAVE_utimes
	struct __timeval32 tv32[2];
	if (!tvp)
		return futimes32(fd, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return futimes32(fd, tv32);
#else /* __CRT_HAVE_utimes */
	struct __timeval64 tv64[2];
	if (!tvp)
		return futimes64(fd, NULL);
	tv64[0].tv_sec  = (time64_t)tvp[0].tv_sec;
	tv64[0].tv_usec = tvp[0].tv_usec;
	tv64[1].tv_sec  = (time64_t)tvp[1].tv_sec;
	tv64[1].tv_usec = tvp[1].tv_usec;
	return futimes64(fd, tv64);
#endif /* !__CRT_HAVE_utimes */
}

%#endif /* __USE_MISC */

%
%#ifdef __USE_TIME64
[time64_variant_of(gettimeofday)][section(".text.crt.time")]
[requires($has_function(gettimeofday32))]
gettimeofday64:([[nonnull]] struct timeval64 *__restrict tv, [[nullable]] __timezone_ptr_t tz) -> int {
	int result;
	struct __timeval32 tv32;
	if (!tv)
		return gettimeofday32(NULL, tz);
	result = gettimeofday32(&tv32, tz);
	if likely(!result) {
		tv->tv_sec  = (time64_t)tv32.tv_sec;
		tv->tv_usec = tv32.tv_usec;
	}
	return result;
}

[time64_variant_of(getitimer)][section(".text.crt.time")]
[requires($has_function(getitimer32))]
getitimer64:(__itimer_which_t which, [[nonnull]] struct itimerval64 *curr_value) -> int {
	int result;
	struct __itimerval32 tv32;
	result = getitimer32(which, &tv32);
	if likely(!result) {
		curr_value->@it_interval@.tv_sec  = (time64_t)tv32.@it_interval@.tv_sec;
		curr_value->@it_interval@.tv_usec = tv32.@it_interval@.tv_usec;
		curr_value->@it_value@.tv_sec     = (time64_t)tv32.@it_value@.tv_sec;
		curr_value->@it_value@.tv_usec    = tv32.@it_value@.tv_usec;
	}
	return result;
}

[time64_variant_of(setitimer)][section(".text.crt.time")]
[requires($has_function(setitimer32))]
setitimer64:(__itimer_which_t which,
             [[nonnull]] struct itimerval64 const *newval,
             [[nullable]] struct itimerval64 *oldval) -> int {
	int result;
	struct __itimerval32 new32, old32;
	new32.@it_interval@.tv_sec  = (time32_t)newval->@it_interval@.tv_sec;
	new32.@it_interval@.tv_usec = newval->@it_interval@.tv_usec;
	new32.@it_value@.tv_sec     = (time32_t)newval->@it_value@.tv_sec;
	new32.@it_value@.tv_usec    = newval->@it_value@.tv_usec;
	result = setitimer32(which, &new32, oldval ? &old32 : NULL);
	if (likely(!result) && oldval) {
		oldval->@it_interval@.tv_sec  = (time64_t)old32.@it_interval@.tv_sec;
		oldval->@it_interval@.tv_usec = old32.@it_interval@.tv_usec;
		oldval->@it_value@.tv_sec     = (time64_t)old32.@it_value@.tv_sec;
		oldval->@it_value@.tv_usec    = old32.@it_value@.tv_usec;
	}
	return result;
}


[section(.text.crt.fs.modify_time)]
[time64_variant_of(utimes)][requires(defined(__CRT_HAVE_utimes))]
utimes64:([[nonnull]] char const *file,
          [[nullable]] struct timeval64 const tvp[2]) -> int {
	struct __timeval32 tv32[2];
	if (!tvp)
		return utimes32(file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return utimes32(file, tv32);
}

%
%#ifdef __USE_MISC
[time64_variant_of(settimeofday)][section(.text.crt.system.adjtime)]
[requires(defined(__CRT_HAVE_settimeofday))]
settimeofday64:([[nullable]] struct timeval64 const *tv, [[nullable]] struct timezone const *tz) -> int {
	struct __timeval32 tv32;
	if (!tv)
		return settimeofday32(NULL, tz);
	tv32.tv_sec  = (time32_t)tv->tv_sec;
	tv32.tv_usec = tv->tv_usec;
	return settimeofday32(&tv32, tz);
}

[section(.text.crt.system.adjtime)][time64_variant_of(adjtime)]
[requires(defined(__CRT_HAVE_adjtime))]
adjtime64:([[nullable]] struct timeval64 const *delta, [[nullable]] struct timeval64 *olddelta) -> int {
	int result;
	struct __timeval32 delta32, olddelta32;
	if (delta) {
		delta32.tv_sec  = (time32_t)delta->tv_sec;
		delta32.tv_usec = delta->tv_usec;
	}
	result = adjtime32(which, delta ? &delta32 : NULL, olddelta ? &olddelta32 : NULL);
	if (likely(!result) && olddelta) {
		olddelta->tv_sec  = (time64_t)olddelta32.tv_sec;
		olddelta->tv_usec = olddelta32.tv_usec;
	}
	return result;
}

[section(.text.crt.fs.modify_time)]
[time64_variant_of(lutimes)][requires(defined(__CRT_HAVE_lutimes))]
lutimes64:([[nonnull]] char const *file, [[nullable]] struct timeval64 const tvp[2]) -> int {
	struct __timeval32 tv32[2];
	if (!tvp)
		return lutimes32(file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return lutimes32(file, tv32);
}


[section(.text.crt.fs.modify_time)]
[time64_variant_of(lutimes)][requires(defined(__CRT_HAVE_futimes))]
futimes64:($fd_t fd, [[nullable]] struct timeval64 const tvp[2]) -> int {
	struct __timeval32 tv32[2];
	if (!tvp)
		return futimes32(fd, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return futimes32(fd, tv32);
}

%#endif /* __USE_MISC */

%
%#ifdef __USE_GNU
[section(.text.crt.fs.modify_time)]
[time64_variant_of(futimesat)][requires(defined(__CRT_HAVE_futimesat))]
futimesat64:($fd_t fd, [[nonnull]] char const *file, [[nullable]] struct timeval64 const tvp[2]) -> int {
	struct __timeval32 tv32[2];
	if (!tvp)
		return futimesat32(fd, file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return futimesat32(fd, file, tv32);
}
%#endif /* __USE_GNU */
%#endif /* __USE_TIME64 */


%{

#ifdef __USE_MISC
#undef timerisset
#undef timerclear
#undef timercmp
#define timerisset(tvp) ((tvp)->tv_sec || (tvp)->tv_usec)
#define timerclear(tvp) ((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define timercmp(a, b, CMP) \
	(((a)->tv_sec == (b)->tv_sec)     \
	 ? ((a)->tv_usec CMP(b)->tv_usec) \
	 : ((a)->tv_sec CMP(b)->tv_sec))
#define timeradd(a, b, result) \
	do {                                                 \
		(result)->tv_sec  = (a)->tv_sec + (b)->tv_sec;   \
		(result)->tv_usec = (a)->tv_usec + (b)->tv_usec; \
		if ((result)->tv_usec >= 1000000) {              \
			++(result)->tv_sec;                          \
			(result)->tv_usec -= 1000000;                \
		}                                                \
	} __WHILE0
#define timersub(a, b, result) \
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

}
