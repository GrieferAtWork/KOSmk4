/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/time.h) */
/* (#) Portability: DJGPP         (/include/sys/time.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/time.h) */
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
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(time_t   = "__time_t")]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(timeval32  = __timeval32)]
%[define_replacement(timeval64  = __timeval64)]
%[define_replacement(itimerval32 = __itimerval32)]
%[define_replacement(itimerval64 = __itimerval64)]


%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/os/itimer.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <bits/os/itimerval.h>
)]%[insert:prefix(
#include <sys/select.h>
)]%{

__SYSDECL_BEGIN

#if ((!defined(ITIMER_REAL) && defined(__ITIMER_REAL)) ||    \
     (!defined(ITIMER_VIRTUAL) && defined(__ITIMER_VIRTUAL)) || \
     (!defined(ITIMER_PROF) && defined(__ITIMER_PROF)))
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __itimer_which {
#if !defined(ITIMER_REAL) && defined(__ITIMER_REAL)
	ITIMER_REAL    = __ITIMER_REAL,
#endif /* !ITIMER_REAL && __ITIMER_REAL */
#if !defined(ITIMER_VIRTUAL) && defined(__ITIMER_VIRTUAL)
	ITIMER_VIRTUAL = __ITIMER_VIRTUAL,
#endif /* !ITIMER_VIRTUAL && __ITIMER_VIRTUAL */
#if !defined(ITIMER_PROF) && defined(__ITIMER_PROF)
	ITIMER_PROF    = __ITIMER_PROF
#endif /* !ITIMER_PROF && __ITIMER_PROF */
} __itimer_which_t;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(ITIMER_REAL) && defined(__ITIMER_REAL)
#define ITIMER_REAL    ITIMER_REAL
#endif /* !ITIMER_REAL && __ITIMER_REAL */
#if !defined(ITIMER_VIRTUAL) && defined(__ITIMER_VIRTUAL)
#define ITIMER_VIRTUAL ITIMER_VIRTUAL
#endif /* !ITIMER_VIRTUAL && __ITIMER_VIRTUAL */
#if !defined(ITIMER_PROF) && defined(__ITIMER_PROF)
#define ITIMER_PROF    ITIMER_PROF
#endif /* !ITIMER_PROF && __ITIMER_PROF */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(ITIMER_REAL) && defined(__ITIMER_REAL)
#define ITIMER_REAL    __ITIMER_REAL
#endif /* !ITIMER_REAL && __ITIMER_REAL */
#if !defined(ITIMER_VIRTUAL) && defined(__ITIMER_VIRTUAL)
#define ITIMER_VIRTUAL __ITIMER_VIRTUAL
#endif /* !ITIMER_VIRTUAL && __ITIMER_VIRTUAL */
#if !defined(ITIMER_PROF) && defined(__ITIMER_PROF)
#define ITIMER_PROF    __ITIMER_PROF
#endif /* !ITIMER_PROF && __ITIMER_PROF */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

#ifdef __CC__

#ifndef __time_t_defined
#define __time_t_defined
typedef __time_t time_t;
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

}

%[define_replacement(__timezone_ptr_t = "void *")]
%[define_replacement(__itimer_which_t = int)]


[[ignore, nocrt, doc_alias("gettimeofday")]]
[[alias("gettimeofday", "__gettimeofday", "__libc_gettimeofday")]]
[[decl_include("<bits/os/timeval.h>")]]
int gettimeofday32([[out_opt]] struct $timeval32 *__restrict tv,
                   [[out_opt]] __timezone_ptr_t tz);

[[ignore, nocrt, doc_alias("getitimer")]]
[[alias("getitimer", "__getitimer", "__libc_getitimer")]]
[[decl_include("<bits/os/itimerval.h>")]]
int getitimer32(__itimer_which_t which, [[out]] struct $itimerval32 *curr_value);

[[ignore, nocrt, doc_alias("setitimer")]]
[[alias("setitimer", "__setitimer", "__libc_setitimer")]]
[[decl_include("<bits/os/itimerval.h>")]]
int setitimer32(__itimer_which_t which,
                [[in_opt]] struct $itimerval32 const *__restrict newval,
                [[out_opt]] struct $itimerval32 *__restrict oldval);

[[ignore, nocrt, doc_alias("utimes"), alias("utimes", "__utimes")]]
[[decl_include("<bits/os/timeval.h>")]]
int utimes32([[in]] char const *file,
             [[in_opt]] struct $timeval32 const tvp[2]);

[[ignore, nocrt, doc_alias("futimesat"), alias("futimesat")]]
[[decl_include("<bits/os/timeval.h>", "<bits/types.h>")]]
int futimesat32([[fdarg]] $fd_t fd, [[in]] char const *file,
                [[in_opt]] struct $timeval32 const tvp[2]);

[[ignore, nocrt, doc_alias("settimeofday")]]
[[alias("settimeofday", "__settimeofday", "__libc_settimeofday")]]
[[decl_include("<bits/os/timeval.h>"), decl_prefix(struct timezone;)]]
int settimeofday32([[in_opt]] struct $timeval32 const *tv,
                   [[in_opt]] struct timezone const *tz);

[[ignore, nocrt, doc_alias("adjtime"), alias("adjtime", "__adjtime")]]
[[decl_include("<bits/os/timeval.h>")]]
int adjtime32([[in_opt]] struct $timeval32 const *delta,
              [[out_opt]] struct $timeval32 *olddelta);

[[ignore, nocrt, doc_alias("lutimes"), alias("lutimes")]]
[[decl_include("<bits/os/timeval.h>")]]
int lutimes32([[in]] char const *file, [[in_opt]] struct $timeval32 const tvp[2]);

[[ignore, nocrt, doc_alias("lutimes"), alias("futimes")]]
[[decl_include("<bits/os/timeval.h>", "<bits/types.h>")]]
int futimes32([[fdarg]] $fd_t fd, [[in_opt]] struct $timeval32 const tvp[2]);



@@>> gettimeofday(2), gettimeofday64(2)
[[decl_include("<bits/os/timeval.h>")]]
[[no_crt_self_import, export_as("__gettimeofday", "__libc_gettimeofday")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("gettimeofday", "__gettimeofday", "__libc_gettimeofday")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("gettimeofday64", "__gettimeofday64")]]
[[requires($has_function(gettimeofday32) || $has_function(gettimeofday64))]]
[[userimpl, section(".text.crt{|.dos}.time")]]
int gettimeofday([[out_opt]] struct timeval *__restrict tv,
                 [[out_opt]] __timezone_ptr_t tz) {
@@pp_if $has_function(gettimeofday32)@@
	int result;
	struct timeval32 tv32;
	if (!tv)
		return gettimeofday32(NULL, tz);
	result = gettimeofday32(&tv32, tz);
	if likely(!result) {
		tv->tv_sec  = (time64_t)tv32.tv_sec;
		tv->tv_usec = tv32.tv_usec;
	}
	return result;
@@pp_else@@
	int result;
	struct timeval64 tv64;
	if (!tv)
		return gettimeofday64(NULL, tz);
	result = gettimeofday64(&tv64, tz);
	if likely(!result) {
		tv->tv_sec  = (time32_t)tv64.tv_sec;
		tv->tv_usec = tv64.tv_usec;
	}
	return result;
@@pp_endif@@
}


@@>> getitimer(2), getitimer64(2)
[[decl_include("<bits/os/itimerval.h>")]]
[[no_crt_self_import, export_as("__getitimer", "__libc_getitimer")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("getitimer", "__getitimer", "__libc_getitimer")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("getitimer64", "__getitimer64")]]
[[requires($has_function(getitimer32) || $has_function(getitimer64))]]
[[userimpl, section(".text.crt{|.dos}.time")]]
int getitimer(__itimer_which_t which,
              [[out]] struct itimerval *curr_value) {
@@pp_if $has_function(getitimer32)@@
	int result;
	struct itimerval32 tv32;
	result = getitimer32(which, &tv32);
	if likely(!result) {
		curr_value->@it_interval@.tv_sec  = (time64_t)tv32.@it_interval@.tv_sec;
		curr_value->@it_interval@.tv_usec = tv32.@it_interval@.tv_usec;
		curr_value->@it_value@.tv_sec     = (time64_t)tv32.@it_value@.tv_sec;
		curr_value->@it_value@.tv_usec    = tv32.@it_value@.tv_usec;
	}
	return result;
@@pp_else@@
	int result;
	struct timeval64 tv64;
	result = getitimer64(which, &tv64);
	if likely(!result) {
		curr_value->@it_interval@.tv_sec  = (time32_t)tv64.@it_interval@.tv_sec;
		curr_value->@it_interval@.tv_usec = tv64.@it_interval@.tv_usec;
		curr_value->@it_value@.tv_sec     = (time32_t)tv64.@it_value@.tv_sec;
		curr_value->@it_value@.tv_usec    = tv64.@it_value@.tv_usec;
	}
	return result;
@@pp_endif@@
}

@@>> setitimer(2), setitimer64(2)
[[decl_include("<bits/os/itimerval.h>")]]
[[no_crt_self_import, export_as("__setitimer", "__libc_setitimer")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("setitimer", "__setitimer", "__libc_setitimer")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("setitimer64", "__setitimer64")]]
[[requires($has_function(setitimer32) || $has_function(setitimer64))]]
[[userimpl, section(".text.crt{|.dos}.time")]]
int setitimer(__itimer_which_t which,
              [[in_opt]] struct itimerval const *newval,
              [[out_opt]] struct itimerval *oldval) {
@@pp_if $has_function(setitimer32)@@
	int result;
	struct itimerval32 old32;
	if (newval) {
		struct itimerval32 new32;
		new32.@it_interval@.tv_sec  = (time32_t)newval->@it_interval@.tv_sec;
		new32.@it_interval@.tv_usec = newval->@it_interval@.tv_usec;
		new32.@it_value@.tv_sec     = (time32_t)newval->@it_value@.tv_sec;
		new32.@it_value@.tv_usec    = newval->@it_value@.tv_usec;
		result = setitimer32(which, &new32, oldval ? &old32 : NULL);
	} else {
		result = setitimer32(which, NULL, oldval ? &old32 : NULL);
	}
	if (likely(!result) && oldval) {
		oldval->@it_interval@.tv_sec  = (time64_t)old32.@it_interval@.tv_sec;
		oldval->@it_interval@.tv_usec = old32.@it_interval@.tv_usec;
		oldval->@it_value@.tv_sec     = (time64_t)old32.@it_value@.tv_sec;
		oldval->@it_value@.tv_usec    = old32.@it_value@.tv_usec;
	}
	return result;
@@pp_else@@
	int result;
	struct itimerval64 old64;
	if (newval) {
		struct itimerval64 new64;
		new64.@it_interval@.tv_sec  = (time64_t)newval->@it_interval@.tv_sec;
		new64.@it_interval@.tv_usec = newval->@it_interval@.tv_usec;
		new64.@it_value@.tv_sec     = (time64_t)newval->@it_value@.tv_sec;
		new64.@it_value@.tv_usec    = newval->@it_value@.tv_usec;
		result = setitimer64(which, &new64, oldval ? &old64 : NULL);
	} else {
		result = setitimer64(which, NULL, oldval ? &old64 : NULL);
	}
	if (likely(!result) && oldval) {
		oldval->@it_interval@.tv_sec  = (time32_t)old64.@it_interval@.tv_sec;
		oldval->@it_interval@.tv_usec = old64.@it_interval@.tv_usec;
		oldval->@it_value@.tv_sec     = (time32_t)old64.@it_value@.tv_sec;
		oldval->@it_value@.tv_usec    = old64.@it_value@.tv_usec;
	}
	return result;
@@pp_endif@@
}


@@>> utimes(2), utimes64(2)
[[decl_include("<bits/os/timeval.h>")]]
[[no_crt_self_import, export_as("__utimes")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("utimes", "__utimes")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("utimes64", "__utimes64")]]
[[requires($has_function(utimes32) || $has_function(utimes64))]]
[[userimpl, section(".text.crt{|.dos}.fs.modify_time")]]
int utimes([[in]] char const *file,
           [[in_opt]] struct timeval const tvp[2]) {
@@pp_if $has_function(utimes32)@@
	struct timeval32 tv32[2];
	if (!tvp)
		return utimes32(file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return utimes32(file, tv32);
@@pp_else@@
	struct timeval64 tv64[2];
	if (!tvp)
		return utimes64(file, NULL);
	tv64[0].tv_sec  = (time64_t)tvp[0].tv_sec;
	tv64[0].tv_usec = tvp[0].tv_usec;
	tv64[1].tv_sec  = (time64_t)tvp[1].tv_sec;
	tv64[1].tv_usec = tvp[1].tv_usec;
	return utimes64(file, tv64);
@@pp_endif@@
}

%
%#ifdef __USE_GNU
@@>> futimesat(2), futimesat64(2)
[[decl_include("<bits/os/timeval.h>", "<bits/types.h>")]]
[[no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futimesat")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futimesat64", "__futimesat64")]]
[[requires($has_function(futimesat32) || $has_function(futimesat64))]]
[[userimpl, section(".text.crt{|.dos}.fs.modify_time")]]
int futimesat([[fdarg]] $fd_t fd, [[in]] char const *file,
              [[in_opt]] struct timeval const tvp[2]) {
@@pp_if $has_function(utimes32)@@
	struct timeval32 tv32[2];
	if (!tvp)
		return futimesat32(fd, file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return futimesat32(fd, file, tv32);
@@pp_else@@
	struct timeval64 tv64[2];
	if (!tvp)
		return futimesat64(fd, file, NULL);
	tv64[0].tv_sec  = (time64_t)tvp[0].tv_sec;
	tv64[0].tv_usec = tvp[0].tv_usec;
	tv64[1].tv_sec  = (time64_t)tvp[1].tv_sec;
	tv64[1].tv_usec = tvp[1].tv_usec;
	return futimesat64(fd, file, tv64);
@@pp_endif@@
}
%#endif /* __USE_GNU */

%
%#ifdef __USE_MISC
@@>> settimeofday(2), settimeofday64(2)
[[decl_include("<bits/os/timeval.h>"), decl_prefix(struct timezone;)]]
[[no_crt_self_import, export_as("__settimeofday", "__libc_settimeofday")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("settimeofday", "__settimeofday", "__libc_settimeofday")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("settimeofday64", "__settimeofday64")]]
[[requires($has_function(settimeofday32) || $has_function(settimeofday64))]]
[[userimpl, section(".text.crt{|.dos}.system.adjtime")]]
int settimeofday([[in_opt]] struct timeval const *tv,
                 [[in_opt]] struct timezone const *tz) {
@@pp_if $has_function(settimeofday32)@@
	struct timeval32 tv32;
	if (!tv)
		return settimeofday32(NULL, tz);
	tv32.tv_sec  = (time32_t)tv->tv_sec;
	tv32.tv_usec = tv->tv_usec;
	return settimeofday32(&tv32, tz);
@@pp_else@@
	struct timeval64 tv64;
	if (!tv)
		return settimeofday64(NULL, tz);
	tv64.tv_sec  = (time64_t)tv->tv_sec;
	tv64.tv_usec = tv->tv_usec;
	return settimeofday64(&tv64, tz);
@@pp_endif@@
}

@@>> adjtime(3), adjtime64(3)
[[decl_include("<bits/os/timeval.h>")]]
[[no_crt_self_import, export_as("__adjtime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("adjtime", "__adjtime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("adjtime64", "__adjtime64")]]
[[requires($has_function(adjtime32) || $has_function(adjtime64))]]
[[userimpl, section(".text.crt{|.dos}.system.adjtime")]]
int adjtime([[in_opt]] struct timeval const *delta,
            [[out_opt]] struct timeval *olddelta) {
@@pp_if $has_function(adjtime32)@@
	int result;
	struct timeval32 delta32, olddelta32;
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
@@pp_else@@
	int result;
	struct timeval64 delta64, olddelta64;
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
@@pp_endif@@
}

@@>> lutimes(2), lutimes64(2)
[[decl_include("<bits/os/timeval.h>")]]
[[no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("lutimes")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("lutimes64", "__lutimes64")]]
[[requires($has_function(lutimes32) || $has_function(lutimes64))]]
[[userimpl, section(".text.crt{|.dos}.fs.modify_time")]]
int lutimes([[in]] char const *file,
            [[in_opt]] struct timeval const tvp[2]) {
@@pp_if $has_function(utimes32)@@
	struct timeval32 tv32[2];
	if (!tvp)
		return lutimes32(file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return lutimes32(file, tv32);
@@pp_else@@
	struct timeval64 tv64[2];
	if (!tvp)
		return lutimes64(file, NULL);
	tv64[0].tv_sec  = (time64_t)tvp[0].tv_sec;
	tv64[0].tv_usec = tvp[0].tv_usec;
	tv64[1].tv_sec  = (time64_t)tvp[1].tv_sec;
	tv64[1].tv_usec = tvp[1].tv_usec;
	return lutimes64(file, tv64);
@@pp_endif@@
}


@@>> futimes(2), futimes64(2)
[[decl_include("<bits/os/timeval.h>", "<bits/types.h>")]]
[[no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futimes")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futimes64", "__futimes64")]]
[[requires($has_function(futimes32) || $has_function(futimes64))]]
[[userimpl, section(".text.crt{|.dos}.fs.modify_time")]]
int futimes([[fdarg]] $fd_t fd, [[in_opt]] struct timeval const tvp[2]) {
@@pp_if $has_function(futimes32)@@
	struct timeval32 tv32[2];
	if (!tvp)
		return futimes32(fd, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return futimes32(fd, tv32);
@@pp_else@@
	struct timeval64 tv64[2];
	if (!tvp)
		return futimes64(fd, NULL);
	tv64[0].tv_sec  = (time64_t)tvp[0].tv_sec;
	tv64[0].tv_usec = tvp[0].tv_usec;
	tv64[1].tv_sec  = (time64_t)tvp[1].tv_sec;
	tv64[1].tv_usec = tvp[1].tv_usec;
	return futimes64(fd, tv64);
@@pp_endif@@
}

%#endif /* __USE_MISC */

%
%#ifdef __USE_TIME64
[[decl_include("<bits/os/timeval.h>")]]
[[preferred_time64_variant_of(gettimeofday), doc_alias("gettimeofday")]]
[[time64_export_alias("__gettimeofday64")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("__gettimeofday", "__libc_gettimeofday")]]
[[requires_function(gettimeofday32)]]
[[userimpl, section(".text.crt{|.dos}.time")]]
int gettimeofday64([[out_opt]] struct timeval64 *__restrict tv,
                   [[out_opt]] __timezone_ptr_t tz) {
	int result;
	struct timeval32 tv32;
	if (!tv)
		return gettimeofday32(NULL, tz);
	result = gettimeofday32(&tv32, tz);
	if likely(!result) {
		tv->tv_sec  = (time64_t)tv32.tv_sec;
		tv->tv_usec = tv32.tv_usec;
	}
	return result;
}

[[decl_include("<bits/os/itimerval.h>")]]
[[preferred_time64_variant_of(getitimer), doc_alias("getitimer")]]
[[time64_export_alias("__getitimer64")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__getitimer", "__libc_getitimer")]]
[[requires_function(getitimer32)]]
[[userimpl, section(".text.crt{|.dos}.time")]]
int getitimer64(__itimer_which_t which,
                [[out]] struct itimerval64 *curr_value) {
	int result;
	struct itimerval32 tv32;
	result = getitimer32(which, &tv32);
	if likely(!result) {
		curr_value->@it_interval@.tv_sec  = (time64_t)tv32.@it_interval@.tv_sec;
		curr_value->@it_interval@.tv_usec = tv32.@it_interval@.tv_usec;
		curr_value->@it_value@.tv_sec     = (time64_t)tv32.@it_value@.tv_sec;
		curr_value->@it_value@.tv_usec    = tv32.@it_value@.tv_usec;
	}
	return result;
}

[[decl_include("<bits/os/itimerval.h>")]]
[[preferred_time64_variant_of(setitimer), doc_alias("setitimer")]]
[[time64_export_alias("__setitimer64")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__setitimer", "__libc_setitimer")]]
[[requires_function(setitimer32)]]
[[userimpl, section(".text.crt{|.dos}.time")]]
int setitimer64(__itimer_which_t which,
                [[in_opt]] struct itimerval64 const *newval,
                [[out_opt]] struct itimerval64 *oldval) {
	int result;
	struct itimerval32 old32;
	if (newval) {
		struct itimerval32 new32;
		new32.@it_interval@.tv_sec  = (time32_t)newval->@it_interval@.tv_sec;
		new32.@it_interval@.tv_usec = newval->@it_interval@.tv_usec;
		new32.@it_value@.tv_sec     = (time32_t)newval->@it_value@.tv_sec;
		new32.@it_value@.tv_usec    = newval->@it_value@.tv_usec;
		result = setitimer32(which, &new32, oldval ? &old32 : NULL);
	} else {
		result = setitimer32(which, NULL, oldval ? &old32 : NULL);
	}
	if (likely(!result) && oldval) {
		oldval->@it_interval@.tv_sec  = (time64_t)old32.@it_interval@.tv_sec;
		oldval->@it_interval@.tv_usec = old32.@it_interval@.tv_usec;
		oldval->@it_value@.tv_sec     = (time64_t)old32.@it_value@.tv_sec;
		oldval->@it_value@.tv_usec    = old32.@it_value@.tv_usec;
	}
	return result;
}


[[decl_include("<bits/os/timeval.h>")]]
[[preferred_time64_variant_of(utimes), doc_alias("utimes")]]
[[time64_export_alias("__utimes64")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__utimes")]]
[[requires_function(utimes32)]]
[[userimpl, section(".text.crt{|.dos}.fs.modify_time")]]
int utimes64([[in]] char const *file,
             [[in_opt]] struct timeval64 const tvp[2]) {
	struct timeval32 tv32[2];
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
[[decl_include("<bits/os/timeval.h>"), decl_prefix(struct timezone;)]]
[[preferred_time64_variant_of(settimeofday), doc_alias("settimeofday")]]
[[time64_export_alias("__settimeofday64")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__settimeofday", "__libc_settimeofday")]]
[[requires_function(settimeofday32)]]
[[userimpl, section(".text.crt{|.dos}.system.adjtime")]]
int settimeofday64([[in_opt]] struct timeval64 const *tv,
                   [[in_opt]] struct timezone const *tz) {
	struct timeval32 tv32;
	if (!tv)
		return settimeofday32(NULL, tz);
	tv32.tv_sec  = (time32_t)tv->tv_sec;
	tv32.tv_usec = tv->tv_usec;
	return settimeofday32(&tv32, tz);
}

[[decl_include("<bits/os/timeval.h>")]]
[[preferred_time64_variant_of(adjtime), doc_alias("adjtime")]]
[[time64_export_alias("__adjtime64")]]
[[requires_function(adjtime32)]]
[[userimpl, section(".text.crt{|.dos}.system.adjtime")]]
int adjtime64([[in_opt]] struct timeval64 const *delta,
              [[out_opt]] struct timeval64 *olddelta) {
	int result;
	struct timeval32 delta32, olddelta32;
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

[[decl_include("<bits/os/timeval.h>")]]
[[preferred_time64_variant_of(lutimes), doc_alias("lutimes")]]
[[time64_export_alias("__lutimes64")]]
[[requires_function(lutimes32)]]
[[userimpl, section(".text.crt{|.dos}.fs.modify_time")]]
int lutimes64([[in]] char const *file,
              [[in_opt]] struct timeval64 const tvp[2]) {
	struct timeval32 tv32[2];
	if (!tvp)
		return lutimes32(file, NULL);
	tv32[0].tv_sec  = (time32_t)tvp[0].tv_sec;
	tv32[0].tv_usec = tvp[0].tv_usec;
	tv32[1].tv_sec  = (time32_t)tvp[1].tv_sec;
	tv32[1].tv_usec = tvp[1].tv_usec;
	return lutimes32(file, tv32);
}


[[decl_include("<bits/os/timeval.h>", "<bits/types.h>")]]
[[preferred_time64_variant_of(lutimes), doc_alias("lutimes")]]
[[time64_export_alias("__futimes64")]]
[[requires_function(futimes32)]]
[[userimpl, section(".text.crt{|.dos}.fs.modify_time")]]
int futimes64([[fdarg]] $fd_t fd, [[in_opt]] struct timeval64 const tvp[2]) {
	struct timeval32 tv32[2];
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
[[decl_include("<bits/os/timeval.h>", "<bits/types.h>")]]
[[preferred_time64_variant_of(futimesat), doc_alias("futimesat")]]
[[time64_export_alias("__futimesat64")]]
[[requires_function(futimesat32)]]
[[userimpl, section(".text.crt{|.dos}.fs.modify_time")]]
int futimesat64([[fdarg]] $fd_t fd, [[in]] char const *file,
                [[in_opt]] struct timeval64 const tvp[2]) {
	struct timeval32 tv32[2];
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

}
