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
/* (#) Portability: DragonFly BSD (/sys/sys/timex.h) */
/* (#) Portability: FreeBSD       (/sys/sys/timex.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/timex.h) */
/* (#) Portability: NetBSD        (/sys/sys/timex.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/timex.h) */
/* (#) Portability: diet libc     (/include/sys/timex.h) */
/* (#) Portability: libc4/5       (/include/sys/timex.h) */
/* (#) Portability: musl libc     (/include/sys/timex.h) */
/* (#) Portability: uClibc        (/include/sys/timex.h) */
}

%[define_replacement(fd_t         = __fd_t)]
%[define_replacement(time_t       = "__time_t")]
%[define_replacement(time32_t     = __time32_t)]
%[define_replacement(time64_t     = __time64_t)]
%[define_replacement(timespec32   = __timespec32)]
%[define_replacement(timespec64   = __timespec64)]
%[define_replacement(timeval32    = __timeval32)]
%[define_replacement(timeval64    = __timeval64)]
%[define_replacement(ntptimeval32 = __ntptimeval32)]
%[define_replacement(ntptimeval64 = __ntptimeval64)]
%[define_replacement(timex32      = __timex32)]
%[define_replacement(timex64      = __timex64)]


%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/timex.h>
)]%[insert:prefix(
#include <bits/os/timex.h>
)]%[insert:prefix(
#include <bits/crt/ntptimeval.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#include <sys/time.h>

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


/* What about these? Are these asm/os or asm/crt? */
#define NTP_API 4 /* ??? */

#define TIME_OK    0          /* ??? */
#define TIME_INS   1          /* ??? */
#define TIME_DEL   2          /* ??? */
#define TIME_OOP   3          /* ??? */
#define TIME_WAIT  4          /* ??? */
#define TIME_ERROR 5          /* ??? */
#define TIME_BAD   TIME_ERROR /* ??? */

#define MAXTC 6 /* ??? */


#ifdef __CC__
__SYSDECL_BEGIN

}

[[ignore, nocrt, alias("adjtimex", "__adjtimex")]]
[[decl_include("<bits/os/timex.h>")]]
int adjtimex32([[inout]] struct $timex32 *__restrict __ntx);

[[ignore, nocrt, alias("ntp_gettimex")]]
[[decl_include("<bits/crt/ntptimeval.h>")]]
int ntp_gettime32([[out]] struct $ntptimeval32 *__restrict ntv);

[[ignore, nocrt, alias("ntp_adjtime")]]
[[decl_include("<bits/os/timex.h>")]]
int ntp_adjtime32([[inout]] struct $timex32 *__restrict tntx);



%[insert:function(__adjtimex = adjtimex)]

@@>> adjtimex(2), adjtimex64(2)
[[decl_include("<bits/os/timex.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("adjtimex", "__adjtimex", "__libc_adjtimex")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("adjtimex64", "__adjtimex64")]]
[[userimpl, requires($has_function(adjtimex32) || $has_function(adjtimex64))]]
[[export_as("__adjtimex", "__libc_adjtimex")]]
int adjtimex([[inout]] struct timex *__restrict ntx) {
	int result;
@@pp_if $has_function(adjtimex32)@@
	struct timex32 nxtalt;
	nxtalt.@time@.tv_sec  = (time32_t)ntx->@time@.tv_sec;
	nxtalt.@time@.tv_usec = ntx->@time@.tv_usec;
	nxtalt.@offset@       = (time32_t)ntx->@offset@;
	nxtalt.@freq@         = (time32_t)ntx->@freq@;
	nxtalt.@maxerror@     = (time32_t)ntx->@maxerror@;
	nxtalt.@esterror@     = (time32_t)ntx->@esterror@;
	nxtalt.@constant@     = (time32_t)ntx->@constant@;
/*	nxtalt.@precision@    = (time32_t)ntx->@precision@; */
/*	nxtalt.@tolerance@    = (time32_t)ntx->@tolerance@; */
	nxtalt.@tick@         = (time32_t)ntx->@tick@;
/*	nxtalt.@ppsfreq@      = (time32_t)ntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time32_t)ntx->@jitter@; */
/*	nxtalt.@shift@        = (time32_t)ntx->@shift@; */
/*	nxtalt.@stabil@       = (time32_t)ntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time32_t)ntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time32_t)ntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time32_t)ntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time32_t)ntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time32_t)ntx->@tai@; */
@@pp_else@@
	struct timex64 nxtalt;
	nxtalt.@time@.tv_sec  = (time64_t)ntx->@time@.tv_sec;
	nxtalt.@time@.tv_usec = ntx->@time@.tv_usec;
	nxtalt.@offset@       = (time64_t)ntx->@offset@;
	nxtalt.@freq@         = (time64_t)ntx->@freq@;
	nxtalt.@maxerror@     = (time64_t)ntx->@maxerror@;
	nxtalt.@esterror@     = (time64_t)ntx->@esterror@;
	nxtalt.@constant@     = (time64_t)ntx->@constant@;
/*	nxtalt.@precision@    = (time64_t)ntx->@precision@; */
/*	nxtalt.@tolerance@    = (time64_t)ntx->@tolerance@; */
	nxtalt.@tick@         = (time64_t)ntx->@tick@;
/*	nxtalt.@ppsfreq@      = (time64_t)ntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time64_t)ntx->@jitter@; */
/*	nxtalt.@shift@        = (time64_t)ntx->@shift@; */
/*	nxtalt.@stabil@       = (time64_t)ntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time64_t)ntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time64_t)ntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time64_t)ntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time64_t)ntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time64_t)ntx->@tai@; */
@@pp_endif@@
	nxtalt.@modes@  = ntx->@modes@;
	nxtalt.@status@ = ntx->@status@;
@@pp_if $has_function(adjtimex32)@@
	result = adjtimex32(&nxtalt);
@@pp_else@@
	result = adjtimex64(&nxtalt);
@@pp_endif@@
	if likely(result == 0) {
@@pp_if $has_function(adjtimex32)@@
		ntx->@time@.tv_sec  = (time64_t)nxtalt.@time@.tv_sec;
		ntx->@time@.tv_usec = nxtalt.@time@.tv_usec;
		ntx->@offset@       = (time64_t)nxtalt.@offset@;
		ntx->@freq@         = (time64_t)nxtalt.@freq@;
		ntx->@maxerror@     = (time64_t)nxtalt.@maxerror@;
		ntx->@esterror@     = (time64_t)nxtalt.@esterror@;
		ntx->@constant@     = (time64_t)nxtalt.@constant@;
		ntx->@precision@    = (time64_t)nxtalt.@precision@;
		ntx->@tolerance@    = (time64_t)nxtalt.@tolerance@;
		ntx->@tick@         = (time64_t)nxtalt.@tick@;
		ntx->@ppsfreq@      = (time64_t)nxtalt.@ppsfreq@;
		ntx->@jitter@       = (time64_t)nxtalt.@jitter@;
		ntx->@shift@        = (time64_t)nxtalt.@shift@;
		ntx->@stabil@       = (time64_t)nxtalt.@stabil@;
		ntx->@jitcnt@       = (time64_t)nxtalt.@jitcnt@;
		ntx->@calcnt@       = (time64_t)nxtalt.@calcnt@;
		ntx->@errcnt@       = (time64_t)nxtalt.@errcnt@;
		ntx->@stbcnt@       = (time64_t)nxtalt.@stbcnt@;
		ntx->@tai@          = (time64_t)nxtalt.@tai@;
@@pp_else@@
		ntx->@time@.tv_sec  = (time32_t)nxtalt.@time@.tv_sec;
		ntx->@time@.tv_usec = nxtalt.@time@.tv_usec;
		ntx->@offset@       = (time32_t)nxtalt.@offset@;
		ntx->@freq@         = (time32_t)nxtalt.@freq@;
		ntx->@maxerror@     = (time32_t)nxtalt.@maxerror@;
		ntx->@esterror@     = (time32_t)nxtalt.@esterror@;
		ntx->@constant@     = (time32_t)nxtalt.@constant@;
		ntx->@precision@    = (time32_t)nxtalt.@precision@;
		ntx->@tolerance@    = (time32_t)nxtalt.@tolerance@;
		ntx->@tick@         = (time32_t)nxtalt.@tick@;
		ntx->@ppsfreq@      = (time32_t)nxtalt.@ppsfreq@;
		ntx->@jitter@       = (time32_t)nxtalt.@jitter@;
		ntx->@shift@        = (time32_t)nxtalt.@shift@;
		ntx->@stabil@       = (time32_t)nxtalt.@stabil@;
		ntx->@jitcnt@       = (time32_t)nxtalt.@jitcnt@;
		ntx->@calcnt@       = (time32_t)nxtalt.@calcnt@;
		ntx->@errcnt@       = (time32_t)nxtalt.@errcnt@;
		ntx->@stbcnt@       = (time32_t)nxtalt.@stbcnt@;
		ntx->@tai@          = (time32_t)nxtalt.@tai@;
@@pp_endif@@
		ntx->@modes@  = nxtalt.@modes@;
		ntx->@status@ = nxtalt.@status@;
	}
	return result;
}


@@>> ntp_gettime(3), ntp_gettime64(3)
[[crt_name("ntp_gettimex"), decl_include("<bits/crt/ntptimeval.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ntp_gettimex")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ntp_gettimex64")]]
[[userimpl, requires($has_function(ntp_gettime32) || $has_function(ntp_gettime64))]]
int ntp_gettime([[out]] struct ntptimeval *__restrict ntv) {
@@pp_if $has_function(ntp_gettime32)@@
	struct ntptimeval32 ntv32;
	int result = ntp_gettime32(&ntv32);
	if likely(result == 0) {
		ntv->@time@.tv_sec       = (time64_t)ntv32.@time@.tv_sec;
		ntv->@time@.tv_usec      = ntv32.@time@.tv_usec;
		ntv->@maxerror@          = ntv32.@maxerror@;
		ntv->@esterror@          = ntv32.@esterror@;
		ntv->@tai@               = ntv32.@tai@;
		ntv->@__glibc_reserved1@ = ntv32.@__glibc_reserved1@;
		ntv->@__glibc_reserved2@ = ntv32.@__glibc_reserved2@;
		ntv->@__glibc_reserved3@ = ntv32.@__glibc_reserved3@;
		ntv->@__glibc_reserved4@ = ntv32.@__glibc_reserved4@;
	}
	return result;
@@pp_else@@
	struct ntptimeval64 ntv64;
	int result = ntp_gettime64(&ntv64);
	if likely(result == 0) {
		ntv->@time@.tv_sec       = (time32_t)ntv64.@time@.tv_sec;
		ntv->@time@.tv_usec      = ntv64.@time@.tv_usec;
		ntv->@maxerror@          = ntv64.@maxerror@;
		ntv->@esterror@          = ntv64.@esterror@;
		ntv->@tai@               = ntv64.@tai@;
		ntv->@__glibc_reserved1@ = ntv64.@__glibc_reserved1@;
		ntv->@__glibc_reserved2@ = ntv64.@__glibc_reserved2@;
		ntv->@__glibc_reserved3@ = ntv64.@__glibc_reserved3@;
		ntv->@__glibc_reserved4@ = ntv64.@__glibc_reserved4@;
	}
	return result;
@@pp_endif@@
}

@@>> ntp_adjtime(3), ntp_adjtime64(3)
[[no_crt_self_import, decl_include("<bits/os/timex.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ntp_adjtime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ntp_adjtime64")]]
[[userimpl, requires($has_function(ntp_adjtime32) || $has_function(ntp_adjtime64))]]
int ntp_adjtime([[inout]] struct timex *__restrict tntx) {
	int result;
@@pp_if $has_function(ntp_adjtime32)@@
	struct timex32 nxtalt;
	nxtalt.@time@.tv_sec  = (time32_t)ntx->@time@.tv_sec;
	nxtalt.@time@.tv_usec = ntx->@time@.tv_usec;
	nxtalt.@offset@       = (time32_t)ntx->@offset@;
	nxtalt.@freq@         = (time32_t)ntx->@freq@;
	nxtalt.@maxerror@     = (time32_t)ntx->@maxerror@;
	nxtalt.@esterror@     = (time32_t)ntx->@esterror@;
	nxtalt.@constant@     = (time32_t)ntx->@constant@;
/*	nxtalt.@precision@    = (time32_t)ntx->@precision@; */
/*	nxtalt.@tolerance@    = (time32_t)ntx->@tolerance@; */
	nxtalt.@tick@         = (time32_t)ntx->@tick@;
/*	nxtalt.@ppsfreq@      = (time32_t)ntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time32_t)ntx->@jitter@; */
/*	nxtalt.@shift@        = (time32_t)ntx->@shift@; */
/*	nxtalt.@stabil@       = (time32_t)ntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time32_t)ntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time32_t)ntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time32_t)ntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time32_t)ntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time32_t)ntx->@tai@; */
@@pp_else@@
	struct timex64 nxtalt;
	nxtalt.@time@.tv_sec  = (time64_t)ntx->@time@.tv_sec;
	nxtalt.@time@.tv_usec = ntx->@time@.tv_usec;
	nxtalt.@offset@       = (time64_t)ntx->@offset@;
	nxtalt.@freq@         = (time64_t)ntx->@freq@;
	nxtalt.@maxerror@     = (time64_t)ntx->@maxerror@;
	nxtalt.@esterror@     = (time64_t)ntx->@esterror@;
	nxtalt.@constant@     = (time64_t)ntx->@constant@;
/*	nxtalt.@precision@    = (time64_t)ntx->@precision@; */
/*	nxtalt.@tolerance@    = (time64_t)ntx->@tolerance@; */
	nxtalt.@tick@         = (time64_t)ntx->@tick@;
/*	nxtalt.@ppsfreq@      = (time64_t)ntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time64_t)ntx->@jitter@; */
/*	nxtalt.@shift@        = (time64_t)ntx->@shift@; */
/*	nxtalt.@stabil@       = (time64_t)ntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time64_t)ntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time64_t)ntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time64_t)ntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time64_t)ntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time64_t)ntx->@tai@; */
@@pp_endif@@
	nxtalt.@modes@  = ntx->@modes@;
	nxtalt.@status@ = ntx->@status@;
@@pp_if $has_function(ntp_adjtime32)@@
	result = ntp_adjtime32(&nxtalt);
@@pp_else@@
	result = ntp_adjtime64(&nxtalt);
@@pp_endif@@
	if likely(result == 0) {
@@pp_if $has_function(ntp_adjtime32)@@
		ntx->@time@.tv_sec  = (time64_t)nxtalt.@time@.tv_sec;
		ntx->@time@.tv_usec = nxtalt.@time@.tv_usec;
		ntx->@offset@       = (time64_t)nxtalt.@offset@;
		ntx->@freq@         = (time64_t)nxtalt.@freq@;
		ntx->@maxerror@     = (time64_t)nxtalt.@maxerror@;
		ntx->@esterror@     = (time64_t)nxtalt.@esterror@;
		ntx->@constant@     = (time64_t)nxtalt.@constant@;
		ntx->@precision@    = (time64_t)nxtalt.@precision@;
		ntx->@tolerance@    = (time64_t)nxtalt.@tolerance@;
		ntx->@tick@         = (time64_t)nxtalt.@tick@;
		ntx->@ppsfreq@      = (time64_t)nxtalt.@ppsfreq@;
		ntx->@jitter@       = (time64_t)nxtalt.@jitter@;
		ntx->@shift@        = (time64_t)nxtalt.@shift@;
		ntx->@stabil@       = (time64_t)nxtalt.@stabil@;
		ntx->@jitcnt@       = (time64_t)nxtalt.@jitcnt@;
		ntx->@calcnt@       = (time64_t)nxtalt.@calcnt@;
		ntx->@errcnt@       = (time64_t)nxtalt.@errcnt@;
		ntx->@stbcnt@       = (time64_t)nxtalt.@stbcnt@;
		ntx->@tai@          = (time64_t)nxtalt.@tai@;
@@pp_else@@
		ntx->@time@.tv_sec  = (time32_t)nxtalt.@time@.tv_sec;
		ntx->@time@.tv_usec = nxtalt.@time@.tv_usec;
		ntx->@offset@       = (time32_t)nxtalt.@offset@;
		ntx->@freq@         = (time32_t)nxtalt.@freq@;
		ntx->@maxerror@     = (time32_t)nxtalt.@maxerror@;
		ntx->@esterror@     = (time32_t)nxtalt.@esterror@;
		ntx->@constant@     = (time32_t)nxtalt.@constant@;
		ntx->@precision@    = (time32_t)nxtalt.@precision@;
		ntx->@tolerance@    = (time32_t)nxtalt.@tolerance@;
		ntx->@tick@         = (time32_t)nxtalt.@tick@;
		ntx->@ppsfreq@      = (time32_t)nxtalt.@ppsfreq@;
		ntx->@jitter@       = (time32_t)nxtalt.@jitter@;
		ntx->@shift@        = (time32_t)nxtalt.@shift@;
		ntx->@stabil@       = (time32_t)nxtalt.@stabil@;
		ntx->@jitcnt@       = (time32_t)nxtalt.@jitcnt@;
		ntx->@calcnt@       = (time32_t)nxtalt.@calcnt@;
		ntx->@errcnt@       = (time32_t)nxtalt.@errcnt@;
		ntx->@stbcnt@       = (time32_t)nxtalt.@stbcnt@;
		ntx->@tai@          = (time32_t)nxtalt.@tai@;
@@pp_endif@@
		ntx->@modes@  = nxtalt.@modes@;
		ntx->@status@ = nxtalt.@status@;
	}
	return result;
}

%
%#ifdef __USE_TIME64
[[decl_include("<bits/os/timex.h>")]]
[[preferred_time64_variant_of(adjtimex), doc_alias("adjtimex")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__adjtimex", "__libc_adjtimex")]]
[[export_alias("__adjtimex64"), userimpl, requires_function(adjtimex32)]]
int adjtimex64([[inout]] struct timex64 *__restrict ntx) {
	int result;
	struct timex32 nxtalt;
	nxtalt.@time@.tv_sec  = (time32_t)ntx->@time@.tv_sec;
	nxtalt.@time@.tv_usec = ntx->@time@.tv_usec;
	nxtalt.@modes@        = ntx->@modes@;
	nxtalt.@offset@       = (time32_t)ntx->@offset@;
	nxtalt.@freq@         = (time32_t)ntx->@freq@;
	nxtalt.@maxerror@     = (time32_t)ntx->@maxerror@;
	nxtalt.@esterror@     = (time32_t)ntx->@esterror@;
	nxtalt.@status@       = ntx->@status@;
	nxtalt.@constant@     = (time32_t)ntx->@constant@;
/*	nxtalt.@precision@    = (time32_t)ntx->@precision@; */
/*	nxtalt.@tolerance@    = (time32_t)ntx->@tolerance@; */
	nxtalt.@tick@         = (time32_t)ntx->@tick@;
/*	nxtalt.@ppsfreq@      = (time32_t)ntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time32_t)ntx->@jitter@; */
/*	nxtalt.@shift@        = (time32_t)ntx->@shift@; */
/*	nxtalt.@stabil@       = (time32_t)ntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time32_t)ntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time32_t)ntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time32_t)ntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time32_t)ntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time32_t)ntx->@tai@; */
	result = adjtimex32(&nxtalt);
	if likely(result == 0) {
		ntx->@time@.tv_sec  = (time64_t)nxtalt.@time@.tv_sec;
		ntx->@time@.tv_usec = nxtalt.@time@.tv_usec;
		ntx->@modes@        = nxtalt.@modes@;
		ntx->@offset@       = (time64_t)nxtalt.@offset@;
		ntx->@freq@         = (time64_t)nxtalt.@freq@;
		ntx->@maxerror@     = (time64_t)nxtalt.@maxerror@;
		ntx->@esterror@     = (time64_t)nxtalt.@esterror@;
		ntx->@status@       = nxtalt.@status@;
		ntx->@constant@     = (time64_t)nxtalt.@constant@;
		ntx->@precision@    = (time64_t)nxtalt.@precision@;
		ntx->@tolerance@    = (time64_t)nxtalt.@tolerance@;
		ntx->@tick@         = (time64_t)nxtalt.@tick@;
		ntx->@ppsfreq@      = (time64_t)nxtalt.@ppsfreq@;
		ntx->@jitter@       = (time64_t)nxtalt.@jitter@;
		ntx->@shift@        = (time64_t)nxtalt.@shift@;
		ntx->@stabil@       = (time64_t)nxtalt.@stabil@;
		ntx->@jitcnt@       = (time64_t)nxtalt.@jitcnt@;
		ntx->@calcnt@       = (time64_t)nxtalt.@calcnt@;
		ntx->@errcnt@       = (time64_t)nxtalt.@errcnt@;
		ntx->@stbcnt@       = (time64_t)nxtalt.@stbcnt@;
		ntx->@tai@          = (time64_t)nxtalt.@tai@;
	}
	return result;
}

[[preferred_time64_variant_of(ntp_adjtime), doc_alias("ntp_adjtime")]]
[[userimpl, requires_function(ntp_adjtime32)]]
[[decl_include("<bits/os/timex.h>")]]
int ntp_adjtime64([[inout]] struct timex64 *__restrict tntx) {
	int result;
	struct timex32 nxtalt;
	nxtalt.@time@.tv_sec  = (time32_t)tntx->@time@.tv_sec;
	nxtalt.@time@.tv_usec = tntx->@time@.tv_usec;
	nxtalt.@modes@        = tntx->@modes@;
	nxtalt.@offset@       = (time32_t)tntx->@offset@;
	nxtalt.@freq@         = (time32_t)tntx->@freq@;
	nxtalt.@maxerror@     = (time32_t)tntx->@maxerror@;
	nxtalt.@esterror@     = (time32_t)tntx->@esterror@;
	nxtalt.@status@       = tntx->@status@;
	nxtalt.@constant@     = (time32_t)tntx->@constant@;
/*	nxtalt.@precision@    = (time32_t)tntx->@precision@; */
/*	nxtalt.@tolerance@    = (time32_t)tntx->@tolerance@; */
	nxtalt.@tick@         = (time32_t)tntx->@tick@;
/*	nxtalt.@ppsfreq@      = (time32_t)tntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time32_t)tntx->@jitter@; */
/*	nxtalt.@shift@        = (time32_t)tntx->@shift@; */
/*	nxtalt.@stabil@       = (time32_t)tntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time32_t)tntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time32_t)tntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time32_t)tntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time32_t)tntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time32_t)tntx->@tai@; */
	result = ntp_adjtime32(&nxtalt);
	if likely(result == 0) {
		tntx->@time@.tv_sec  = (time64_t)nxtalt.@time@.tv_sec;
		tntx->@time@.tv_usec = nxtalt.@time@.tv_usec;
		tntx->@modes@        = nxtalt.@modes@;
		tntx->@offset@       = (time64_t)nxtalt.@offset@;
		tntx->@freq@         = (time64_t)nxtalt.@freq@;
		tntx->@maxerror@     = (time64_t)nxtalt.@maxerror@;
		tntx->@esterror@     = (time64_t)nxtalt.@esterror@;
		tntx->@status@       = nxtalt.@status@;
		tntx->@constant@     = (time64_t)nxtalt.@constant@;
		tntx->@precision@    = (time64_t)nxtalt.@precision@;
		tntx->@tolerance@    = (time64_t)nxtalt.@tolerance@;
		tntx->@tick@         = (time64_t)nxtalt.@tick@;
		tntx->@ppsfreq@      = (time64_t)nxtalt.@ppsfreq@;
		tntx->@jitter@       = (time64_t)nxtalt.@jitter@;
		tntx->@shift@        = (time64_t)nxtalt.@shift@;
		tntx->@stabil@       = (time64_t)nxtalt.@stabil@;
		tntx->@jitcnt@       = (time64_t)nxtalt.@jitcnt@;
		tntx->@calcnt@       = (time64_t)nxtalt.@calcnt@;
		tntx->@errcnt@       = (time64_t)nxtalt.@errcnt@;
		tntx->@stbcnt@       = (time64_t)nxtalt.@stbcnt@;
		tntx->@tai@          = (time64_t)nxtalt.@tai@;
	}
	return result;
}


[[crt_name("ntp_gettimex64"), decl_include("<bits/crt/ntptimeval.h>")]]
[[preferred_time64_variant_of(ntp_gettimex), doc_alias("ntp_gettime")]]
[[userimpl, requires_function(ntp_gettime32)]]
int ntp_gettime64([[out]] struct ntptimeval64 *__restrict ntv) {
	struct ntptimeval32 ntv32;
	int result = ntp_gettime32(&ntv32);
	if likely(result == 0) {
		ntv->@time@.tv_sec       = (time64_t)ntv32.@time@.tv_sec;
		ntv->@time@.tv_usec      = ntv32.@time@.tv_usec;
		ntv->@maxerror@          = ntv32.@maxerror@;
		ntv->@esterror@          = ntv32.@esterror@;
		ntv->@tai@               = ntv32.@tai@;
		ntv->@__glibc_reserved1@ = ntv32.@__glibc_reserved1@;
		ntv->@__glibc_reserved2@ = ntv32.@__glibc_reserved2@;
		ntv->@__glibc_reserved3@ = ntv32.@__glibc_reserved3@;
		ntv->@__glibc_reserved4@ = ntv32.@__glibc_reserved4@;
	}
	return result;
}
%#endif /* __USE_TIME64 */


%{

__SYSDECL_END
#endif /* __CC__ */

}
