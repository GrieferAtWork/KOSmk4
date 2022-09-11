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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/timerfd.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/timerfd.h) */
/* (#) Portability: diet libc     (/include/sys/timerfd.h) */
/* (#) Portability: musl libc     (/include/sys/timerfd.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(itimerspec32 = __itimerspec32)]
%[define_replacement(itimerspec64 = __itimerspec64)]
%[default:section(".text.crt{|.dos}.timer")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/timerfd.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __USE_GLIBC_BLOAT
#include <time.h>
#endif /* __USE_GLIBC_BLOAT */

__SYSDECL_BEGIN

/* Values for the `flags' argument of `timerfd_create(2)'. */
#if (defined(__TFD_NONBLOCK) || defined(__TFD_CLOEXEC) || \
     (defined(__USE_KOS) && defined(__TFD_CLOFORK)))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __TFD_NONBLOCK
	TFD_NONBLOCK      = __TFD_NONBLOCK, /* Set the `IO_NONBLOCK' flag for the returned */
#endif /* __TFD_NONBLOCK */
#ifdef __TFD_CLOEXEC
	TFD_CLOEXEC       = __TFD_CLOEXEC,  /* Set the `IO_CLOEXEC' flag for the returned */
#endif /* __TFD_CLOEXEC */
#if defined(__USE_KOS) && defined(__TFD_CLOFORK)
	TFD_CLOFORK       = __TFD_CLOFORK,  /* Set the `IO_CLOFORK' flag for the returned */
#endif /* __USE_KOS && __TFD_CLOFORK */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __TFD_NONBLOCK
#define TFD_NONBLOCK TFD_NONBLOCK /* Set the `IO_NONBLOCK' flag for the returned */
#endif /* __TFD_NONBLOCK */
#ifdef __TFD_CLOEXEC
#define TFD_CLOEXEC  TFD_CLOEXEC  /* Set the `IO_CLOEXEC' flag for the returned */
#endif /* __TFD_CLOEXEC */
#if defined(__USE_KOS) && defined(__TFD_CLOFORK)
#define TFD_CLOFORK  TFD_CLOFORK  /* Set the `IO_CLOFORK' flag for the returned */
#endif /* __USE_KOS && __TFD_CLOFORK */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __TFD_NONBLOCK
#define TFD_NONBLOCK __TFD_NONBLOCK /* Set the `IO_NONBLOCK' flag for the returned */
#endif /* __TFD_NONBLOCK */
#ifdef __TFD_CLOEXEC
#define TFD_CLOEXEC  __TFD_CLOEXEC  /* Set the `IO_CLOEXEC' flag for the returned */
#endif /* __TFD_CLOEXEC */
#if defined(__USE_KOS) && defined(__TFD_CLOFORK)
#define TFD_CLOFORK  __TFD_CLOFORK  /* Set the `IO_CLOFORK' flag for the returned */
#endif /* __USE_KOS && __TFD_CLOFORK */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

/* Values for the `flags' argument of `timerfd_settime(2)'. */
#ifdef __TFD_TIMER_ABSTIME
/*[[[enum]]]*/
#ifdef __CC__
enum {
	TFD_TIMER_ABSTIME = __TFD_TIMER_ABSTIME /* Work with absolute timestamps. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define TFD_TIMER_ABSTIME TFD_TIMER_ABSTIME /* Work with absolute timestamps. */
#else /* __COMPILER_PREFERR_ENUMS */
#define TFD_TIMER_ABSTIME __TFD_TIMER_ABSTIME /* Work with absolute timestamps. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __TFD_TIMER_ABSTIME */



#ifdef __CC__

}


[[decl_include("<features.h>", "<bits/types.h>", "<bits/os/itimerspec.h>")]]
[[doc_alias("timerfd_settime"), ignore, nocrt, alias("timerfd_settime")]]
int timerfd_settime32($fd_t ufd, __STDC_INT_AS_UINT_T flags,
                      [[in]] struct $itimerspec32 const *utmr,
                      [[out_opt]] struct $itimerspec32 *otmr);

[[decl_include("<bits/types.h>", "<bits/os/itimerspec.h>")]]
[[doc_alias("timerfd_gettime"), ignore, nocrt, alias("timerfd_gettime")]]
int timerfd_gettime32($fd_t ufd, [[out]] struct $itimerspec32 *__restrict otmr);


@@>> timerfd_create(2)
@@@param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK'
[[nothrow, decl_include("<features.h>", "<bits/types.h>")]]
$fd_t timerfd_create(clockid_t clock_id, __STDC_INT_AS_UINT_T flags);

@@>> timerfd_settime(2), timerfd_settime64(2)
@@@param: flags: Set of `0 | TFD_TIMER_ABSTIME'
[[decl_include("<features.h>", "<bits/types.h>", "<bits/os/itimerspec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timerfd_settime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timerfd_settime64")]]
[[userimpl, requires($has_function(timerfd_settime32) || $has_function(timerfd_settime64))]]
int timerfd_settime($fd_t ufd, __STDC_INT_AS_UINT_T flags,
                     [[in]] struct itimerspec const *utmr,
                     [[out_opt]] struct itimerspec *otmr) {
@@pp_if $has_function(timerfd_settime32)@@
	int result;
	struct itimerspec32 utmr32, otmr32;
	utmr32.it_interval.tv_sec  = (time32_t)utmr->it_interval.tv_sec;
	utmr32.it_interval.tv_nsec = utmr->it_interval.tv_nsec;
	utmr32.it_value.tv_sec     = (time32_t)utmr->it_value.tv_sec;
	utmr32.it_value.tv_nsec    = utmr->it_value.tv_nsec;
	result = timerfd_settime32(ufd, flags, &utmr32, otmr ? &otmr32 : NULL);
	if (result == 0 && otmr) {
		otmr->it_interval.tv_sec  = (time64_t)otmr32.it_interval.tv_sec;
		otmr->it_interval.tv_nsec = otmr32.it_interval.tv_nsec;
		otmr->it_value.tv_sec     = (time64_t)otmr32.it_value.tv_sec;
		otmr->it_value.tv_nsec    = otmr32.it_value.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct itimerspec64 utmr64, otmr64;
	utmr64.it_interval.tv_sec  = (time64_t)utmr->it_interval.tv_sec;
	utmr64.it_interval.tv_nsec = utmr->it_interval.tv_nsec;
	utmr64.it_value.tv_sec     = (time64_t)utmr->it_value.tv_sec;
	utmr64.it_value.tv_nsec    = utmr->it_value.tv_nsec;
	result = timerfd_settime64(timerid, flags, &utmr64, otmr ? &otmr64 : NULL);
	if (result == 0 && otmr) {
		otmr->it_interval.tv_sec  = (time32_t)otmr64.it_interval.tv_sec;
		otmr->it_interval.tv_nsec = otmr64.it_interval.tv_nsec;
		otmr->it_value.tv_sec     = (time32_t)otmr64.it_value.tv_sec;
		otmr->it_value.tv_nsec    = otmr64.it_value.tv_nsec;
	}
	return result;
@@pp_endif@@
}

@@>> timerfd_gettime(2), timerfd_gettime64(2)
[[decl_include("<bits/types.h>", "<bits/os/itimerspec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timerfd_gettime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("timerfd_gettime64")]]
[[userimpl, requires($has_function(timerfd_gettime32) || $has_function(timerfd_gettime64))]]
int timerfd_gettime($fd_t ufd, [[out]] struct itimerspec *__restrict otmr) {
@@pp_if $has_function(timerfd_gettime32)@@
	int result;
	struct itimerspec32 otmr32;
	result = timerfd_gettime32(timerid, &otmr32);
	if (result == 0) {
		otmr->it_interval.tv_sec  = (time64_t)otmr32.it_interval.tv_sec;
		otmr->it_interval.tv_nsec = otmr32.it_interval.tv_nsec;
		otmr->it_value.tv_sec     = (time64_t)otmr32.it_value.tv_sec;
		otmr->it_value.tv_nsec    = otmr32.it_value.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct itimerspec64 otmr64;
	result = timerfd_gettime64(timerid, &otmr64);
	if (result == 0) {
		otmr->it_interval.tv_sec  = (time32_t)otmr64.it_interval.tv_sec;
		otmr->it_interval.tv_nsec = otmr64.it_interval.tv_nsec;
		otmr->it_value.tv_sec     = (time32_t)otmr64.it_value.tv_sec;
		otmr->it_value.tv_nsec    = otmr64.it_value.tv_nsec;
	}
	return result;
@@pp_endif@@
}

%
%#ifdef __USE_TIME64

[[decl_include("<features.h>", "<bits/types.h>", "<bits/os/itimerspec.h>")]]
[[preferred_time64_variant_of(timerfd_settime), doc_alias("timerfd_settime")]]
[[userimpl, requires_function(timerfd_settime32)]]
int timerfd_settime64($fd_t ufd, __STDC_INT_AS_UINT_T flags,
                      [[in]] struct itimerspec64 const *utmr,
                      [[out_opt]] struct itimerspec64 *otmr) {
	int result;
	struct itimerspec32 utmr32, otmr32;
	utmr32.it_interval.tv_sec  = (time32_t)utmr->it_interval.tv_sec;
	utmr32.it_interval.tv_nsec = utmr->it_interval.tv_nsec;
	utmr32.it_value.tv_sec     = (time32_t)utmr->it_value.tv_sec;
	utmr32.it_value.tv_nsec    = utmr->it_value.tv_nsec;
	result = timerfd_settime32(ufd, flags, &utmr32, otmr ? &otmr32 : NULL);
	if (result == 0 && otmr) {
		otmr->it_interval.tv_sec  = (time64_t)otmr32.it_interval.tv_sec;
		otmr->it_interval.tv_nsec = otmr32.it_interval.tv_nsec;
		otmr->it_value.tv_sec     = (time64_t)otmr32.it_value.tv_sec;
		otmr->it_value.tv_nsec    = otmr32.it_value.tv_nsec;
	}
	return result;
}

[[decl_include("<bits/types.h>", "<bits/os/itimerspec.h>")]]
[[preferred_time64_variant_of(timerfd_gettime), doc_alias("timerfd_gettime")]]
[[userimpl, requires_function(timerfd_gettime32)]]
int timerfd_gettime64($fd_t ufd, [[out]] struct itimerspec64 *__restrict otmr) {
	int result;
	struct itimerspec32 otmr32;
	result = timerfd_gettime32(timerid, &otmr32);
	if (result == 0) {
		otmr->it_interval.tv_sec  = (time64_t)otmr32.it_interval.tv_sec;
		otmr->it_interval.tv_nsec = otmr32.it_interval.tv_nsec;
		otmr->it_value.tv_sec     = (time64_t)otmr32.it_value.tv_sec;
		otmr->it_value.tv_nsec    = otmr32.it_value.tv_nsec;
	}
	return result;
}

%#endif /* __USE_TIME64 */

%{
#endif /* __CC__ */

__SYSDECL_END

}
