/* HASH CRC-32:0x1f4bd0bc */
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
#ifndef __local_ntp_adjtime_defined
#define __local_ntp_adjtime_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_ntp_adjtime64) || defined(__CRT_HAVE_ntp_adjtime)
#include <bits/os/timex.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_ntp_adjtime32_defined) && defined(__CRT_HAVE_ntp_adjtime)
#define __local___localdep_ntp_adjtime32_defined
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_ntp_adjtime32,(struct __timex32 *__restrict __tntx),ntp_adjtime,(__tntx))
#endif /* !__local___localdep_ntp_adjtime32_defined && __CRT_HAVE_ntp_adjtime */
#ifndef __local___localdep_ntp_adjtime64_defined
#define __local___localdep_ntp_adjtime64_defined
#if defined(__CRT_HAVE_ntp_adjtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_ntp_adjtime64,(struct __timex64 *__restrict __tntx),ntp_adjtime,(__tntx))
#elif defined(__CRT_HAVE_ntp_adjtime64)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_ntp_adjtime64,(struct __timex64 *__restrict __tntx),ntp_adjtime64,(__tntx))
#elif defined(__CRT_HAVE_ntp_adjtime)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.timex/ntp_adjtime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ntp_adjtime64 __LIBC_LOCAL_NAME(ntp_adjtime64)
#else /* ... */
#undef __local___localdep_ntp_adjtime64_defined
#endif /* !... */
#endif /* !__local___localdep_ntp_adjtime64_defined */
__LOCAL_LIBC(ntp_adjtime) __ATTR_INOUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ntp_adjtime))(struct timex *__restrict __tntx) {
	int __result;
#ifdef __CRT_HAVE_ntp_adjtime
	struct __timex32 __nxtalt;
	__nxtalt.time.tv_sec  = (__time32_t)__ntx->time.tv_sec;
	__nxtalt.time.tv_usec = __ntx->time.tv_usec;
	__nxtalt.offset       = (__time32_t)__ntx->offset;
	__nxtalt.freq         = (__time32_t)__ntx->freq;
	__nxtalt.maxerror     = (__time32_t)__ntx->maxerror;
	__nxtalt.esterror     = (__time32_t)__ntx->esterror;
	__nxtalt.constant     = (__time32_t)__ntx->constant;
/*	nxtalt.@precision@    = (time32_t)ntx->@precision@; */
/*	nxtalt.@tolerance@    = (time32_t)ntx->@tolerance@; */
	__nxtalt.tick         = (__time32_t)__ntx->tick;
/*	nxtalt.@ppsfreq@      = (time32_t)ntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time32_t)ntx->@jitter@; */
/*	nxtalt.@shift@        = (time32_t)ntx->@shift@; */
/*	nxtalt.@stabil@       = (time32_t)ntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time32_t)ntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time32_t)ntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time32_t)ntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time32_t)ntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time32_t)ntx->@tai@; */
#else /* __CRT_HAVE_ntp_adjtime */
	struct __timex64 __nxtalt;
	__nxtalt.time.tv_sec  = (__time64_t)__ntx->time.tv_sec;
	__nxtalt.time.tv_usec = __ntx->time.tv_usec;
	__nxtalt.offset       = (__time64_t)__ntx->offset;
	__nxtalt.freq         = (__time64_t)__ntx->freq;
	__nxtalt.maxerror     = (__time64_t)__ntx->maxerror;
	__nxtalt.esterror     = (__time64_t)__ntx->esterror;
	__nxtalt.constant     = (__time64_t)__ntx->constant;
/*	nxtalt.@precision@    = (time64_t)ntx->@precision@; */
/*	nxtalt.@tolerance@    = (time64_t)ntx->@tolerance@; */
	__nxtalt.tick         = (__time64_t)__ntx->tick;
/*	nxtalt.@ppsfreq@      = (time64_t)ntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time64_t)ntx->@jitter@; */
/*	nxtalt.@shift@        = (time64_t)ntx->@shift@; */
/*	nxtalt.@stabil@       = (time64_t)ntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time64_t)ntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time64_t)ntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time64_t)ntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time64_t)ntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time64_t)ntx->@tai@; */
#endif /* !__CRT_HAVE_ntp_adjtime */
	__nxtalt.modes  = __ntx->modes;
	__nxtalt.status = __ntx->status;
#ifdef __CRT_HAVE_ntp_adjtime
	__result = (__NAMESPACE_LOCAL_SYM __localdep_ntp_adjtime32)(&__nxtalt);
#else /* __CRT_HAVE_ntp_adjtime */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_ntp_adjtime64)(&__nxtalt);
#endif /* !__CRT_HAVE_ntp_adjtime */
	if __likely(__result == 0) {
#ifdef __CRT_HAVE_ntp_adjtime
		__ntx->time.tv_sec  = (__time64_t)__nxtalt.time.tv_sec;
		__ntx->time.tv_usec = __nxtalt.time.tv_usec;
		__ntx->offset       = (__time64_t)__nxtalt.offset;
		__ntx->freq         = (__time64_t)__nxtalt.freq;
		__ntx->maxerror     = (__time64_t)__nxtalt.maxerror;
		__ntx->esterror     = (__time64_t)__nxtalt.esterror;
		__ntx->constant     = (__time64_t)__nxtalt.constant;
		__ntx->precision    = (__time64_t)__nxtalt.precision;
		__ntx->tolerance    = (__time64_t)__nxtalt.tolerance;
		__ntx->tick         = (__time64_t)__nxtalt.tick;
		__ntx->ppsfreq      = (__time64_t)__nxtalt.ppsfreq;
		__ntx->jitter       = (__time64_t)__nxtalt.jitter;
		__ntx->shift        = (__time64_t)__nxtalt.shift;
		__ntx->stabil       = (__time64_t)__nxtalt.stabil;
		__ntx->jitcnt       = (__time64_t)__nxtalt.jitcnt;
		__ntx->calcnt       = (__time64_t)__nxtalt.calcnt;
		__ntx->errcnt       = (__time64_t)__nxtalt.errcnt;
		__ntx->stbcnt       = (__time64_t)__nxtalt.stbcnt;
		__ntx->tai          = (__time64_t)__nxtalt.tai;
#else /* __CRT_HAVE_ntp_adjtime */
		__ntx->time.tv_sec  = (__time32_t)__nxtalt.time.tv_sec;
		__ntx->time.tv_usec = __nxtalt.time.tv_usec;
		__ntx->offset       = (__time32_t)__nxtalt.offset;
		__ntx->freq         = (__time32_t)__nxtalt.freq;
		__ntx->maxerror     = (__time32_t)__nxtalt.maxerror;
		__ntx->esterror     = (__time32_t)__nxtalt.esterror;
		__ntx->constant     = (__time32_t)__nxtalt.constant;
		__ntx->precision    = (__time32_t)__nxtalt.precision;
		__ntx->tolerance    = (__time32_t)__nxtalt.tolerance;
		__ntx->tick         = (__time32_t)__nxtalt.tick;
		__ntx->ppsfreq      = (__time32_t)__nxtalt.ppsfreq;
		__ntx->jitter       = (__time32_t)__nxtalt.jitter;
		__ntx->shift        = (__time32_t)__nxtalt.shift;
		__ntx->stabil       = (__time32_t)__nxtalt.stabil;
		__ntx->jitcnt       = (__time32_t)__nxtalt.jitcnt;
		__ntx->calcnt       = (__time32_t)__nxtalt.calcnt;
		__ntx->errcnt       = (__time32_t)__nxtalt.errcnt;
		__ntx->stbcnt       = (__time32_t)__nxtalt.stbcnt;
		__ntx->tai          = (__time32_t)__nxtalt.tai;
#endif /* !__CRT_HAVE_ntp_adjtime */
		__ntx->modes  = __nxtalt.modes;
		__ntx->status = __nxtalt.status;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ntp_adjtime_defined
#define __local___localdep_ntp_adjtime_defined
#define __localdep_ntp_adjtime __LIBC_LOCAL_NAME(ntp_adjtime)
#endif /* !__local___localdep_ntp_adjtime_defined */
#else /* __CRT_HAVE_ntp_adjtime64 || __CRT_HAVE_ntp_adjtime */
#undef __local_ntp_adjtime_defined
#endif /* !__CRT_HAVE_ntp_adjtime64 && !__CRT_HAVE_ntp_adjtime */
#endif /* !__local_ntp_adjtime_defined */
