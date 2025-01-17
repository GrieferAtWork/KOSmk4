/* HASH CRC-32:0xf4831cec */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_adjtimex64_defined
#define __local_adjtimex64_defined
#include <__crt.h>
#if defined(__CRT_HAVE_adjtimex) || defined(__CRT_HAVE___adjtimex)
#include <bits/os/timex.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_adjtimex32_defined
#define __local___localdep_adjtimex32_defined
#ifdef __CRT_HAVE_adjtimex
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_adjtimex32,(struct __timex32 *__restrict __ntx),adjtimex,(__ntx))
#elif defined(__CRT_HAVE___adjtimex)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_adjtimex32,(struct __timex32 *__restrict __ntx),__adjtimex,(__ntx))
#else /* ... */
#undef __local___localdep_adjtimex32_defined
#endif /* !... */
#endif /* !__local___localdep_adjtimex32_defined */
__LOCAL_LIBC(adjtimex64) __ATTR_INOUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(adjtimex64))(struct __timex64 *__restrict __ntx) {
	int __result;
	struct __timex32 __nxtalt;
	__nxtalt.time.tv_sec  = (__time32_t)__ntx->time.tv_sec;
	__nxtalt.time.tv_usec = __ntx->time.tv_usec;
	__nxtalt.modes        = __ntx->modes;
	__nxtalt.offset       = (__time32_t)__ntx->offset;
	__nxtalt.freq         = (__time32_t)__ntx->freq;
	__nxtalt.maxerror     = (__time32_t)__ntx->maxerror;
	__nxtalt.esterror     = (__time32_t)__ntx->esterror;
	__nxtalt.status       = __ntx->status;
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
	__result = (__NAMESPACE_LOCAL_SYM __localdep_adjtimex32)(&__nxtalt);
	if __likely(__result == 0) {
		__ntx->time.tv_sec  = (__time64_t)__nxtalt.time.tv_sec;
		__ntx->time.tv_usec = __nxtalt.time.tv_usec;
		__ntx->modes        = __nxtalt.modes;
		__ntx->offset       = (__time64_t)__nxtalt.offset;
		__ntx->freq         = (__time64_t)__nxtalt.freq;
		__ntx->maxerror     = (__time64_t)__nxtalt.maxerror;
		__ntx->esterror     = (__time64_t)__nxtalt.esterror;
		__ntx->status       = __nxtalt.status;
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
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_adjtimex64_defined
#define __local___localdep_adjtimex64_defined
#define __localdep_adjtimex64 __LIBC_LOCAL_NAME(adjtimex64)
#endif /* !__local___localdep_adjtimex64_defined */
#else /* __CRT_HAVE_adjtimex || __CRT_HAVE___adjtimex */
#undef __local_adjtimex64_defined
#endif /* !__CRT_HAVE_adjtimex && !__CRT_HAVE___adjtimex */
#endif /* !__local_adjtimex64_defined */
