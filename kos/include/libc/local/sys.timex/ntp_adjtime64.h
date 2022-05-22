/* HASH CRC-32:0x8cf5825d */
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
#ifndef __local_ntp_adjtime64_defined
#define __local_ntp_adjtime64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_ntp_adjtime
#include <bits/os/timex.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ntp_adjtime32_defined
#define __local___localdep_ntp_adjtime32_defined
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,__localdep_ntp_adjtime32,(struct __timex32 *__restrict __tntx),ntp_adjtime,(__tntx))
#endif /* !__local___localdep_ntp_adjtime32_defined */
__LOCAL_LIBC(ntp_adjtime64) __ATTR_ACCESS_RW(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ntp_adjtime64))(struct __timex64 *__restrict __tntx) {
	int __result;
	struct __timex32 __nxtalt;
	__nxtalt.time.tv_sec  = (__time32_t)__tntx->time.tv_sec;
	__nxtalt.time.tv_usec = __tntx->time.tv_usec;
	__nxtalt.modes        = __tntx->modes;
	__nxtalt.offset       = (__time32_t)__tntx->offset;
	__nxtalt.freq         = (__time32_t)__tntx->freq;
	__nxtalt.maxerror     = (__time32_t)__tntx->maxerror;
	__nxtalt.esterror     = (__time32_t)__tntx->esterror;
	__nxtalt.status       = __tntx->status;
	__nxtalt.constant     = (__time32_t)__tntx->constant;
/*	nxtalt.@precision@    = (time32_t)tntx->@precision@; */
/*	nxtalt.@tolerance@    = (time32_t)tntx->@tolerance@; */
	__nxtalt.tick         = (__time32_t)__tntx->tick;
/*	nxtalt.@ppsfreq@      = (time32_t)tntx->@ppsfreq@; */
/*	nxtalt.@jitter@       = (time32_t)tntx->@jitter@; */
/*	nxtalt.@shift@        = (time32_t)tntx->@shift@; */
/*	nxtalt.@stabil@       = (time32_t)tntx->@stabil@; */
/*	nxtalt.@jitcnt@       = (time32_t)tntx->@jitcnt@; */
/*	nxtalt.@calcnt@       = (time32_t)tntx->@calcnt@; */
/*	nxtalt.@errcnt@       = (time32_t)tntx->@errcnt@; */
/*	nxtalt.@stbcnt@       = (time32_t)tntx->@stbcnt@; */
/*	nxtalt.@tai@          = (time32_t)tntx->@tai@; */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_ntp_adjtime32)(&__nxtalt);
	if __likely(__result == 0) {
		__tntx->time.tv_sec  = (__time64_t)__nxtalt.time.tv_sec;
		__tntx->time.tv_usec = __nxtalt.time.tv_usec;
		__tntx->modes        = __nxtalt.modes;
		__tntx->offset       = (__time64_t)__nxtalt.offset;
		__tntx->freq         = (__time64_t)__nxtalt.freq;
		__tntx->maxerror     = (__time64_t)__nxtalt.maxerror;
		__tntx->esterror     = (__time64_t)__nxtalt.esterror;
		__tntx->status       = __nxtalt.status;
		__tntx->constant     = (__time64_t)__nxtalt.constant;
		__tntx->precision    = (__time64_t)__nxtalt.precision;
		__tntx->tolerance    = (__time64_t)__nxtalt.tolerance;
		__tntx->tick         = (__time64_t)__nxtalt.tick;
		__tntx->ppsfreq      = (__time64_t)__nxtalt.ppsfreq;
		__tntx->jitter       = (__time64_t)__nxtalt.jitter;
		__tntx->shift        = (__time64_t)__nxtalt.shift;
		__tntx->stabil       = (__time64_t)__nxtalt.stabil;
		__tntx->jitcnt       = (__time64_t)__nxtalt.jitcnt;
		__tntx->calcnt       = (__time64_t)__nxtalt.calcnt;
		__tntx->errcnt       = (__time64_t)__nxtalt.errcnt;
		__tntx->stbcnt       = (__time64_t)__nxtalt.stbcnt;
		__tntx->tai          = (__time64_t)__nxtalt.tai;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ntp_adjtime64_defined
#define __local___localdep_ntp_adjtime64_defined
#define __localdep_ntp_adjtime64 __LIBC_LOCAL_NAME(ntp_adjtime64)
#endif /* !__local___localdep_ntp_adjtime64_defined */
#else /* __CRT_HAVE_ntp_adjtime */
#undef __local_ntp_adjtime64_defined
#endif /* !__CRT_HAVE_ntp_adjtime */
#endif /* !__local_ntp_adjtime64_defined */
