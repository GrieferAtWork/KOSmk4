/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_KOS_TIMEX_H
#define _BITS_OS_KOS_TIMEX_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/timeval.h>
#include <bits/types.h>


#define __OFFSET_TIMEX_MODES     0
#if __ALIGNOF_TIME_T__ > 4
#define __OFFSET_TIMEX_OFFSET    __ALIGNOF_TIME_T__
#else /* __SIZEOF_TIME_T__ > 4 */
#define __OFFSET_TIMEX_OFFSET    4
#endif /* __SIZEOF_TIME_T__ <= 4 */
#define __OFFSET_TIMEX_FREQ      (__OFFSET_TIMEX_OFFSET + __SIZEOF_TIME_T__)
#define __OFFSET_TIMEX_MAXERROR  (__OFFSET_TIMEX_OFFSET + __SIZEOF_TIME_T__ * 2)
#define __OFFSET_TIMEX_ESTERROR  (__OFFSET_TIMEX_OFFSET + __SIZEOF_TIME_T__ * 3)
#define __OFFSET_TIMEX_STATUS    (__OFFSET_TIMEX_OFFSET + __SIZEOF_TIME_T__ * 4)
#if __ALIGNOF_TIME_T__ > 4
#define __OFFSET_TIMEX_CONSTANT  (__OFFSET_TIMEX_OFFSET + __SIZEOF_TIME_T__ * 5)
#else /* __SIZEOF_TIME_T__ > 4 */
#define __OFFSET_TIMEX_CONSTANT  (__OFFSET_TIMEX_OFFSET + __SIZEOF_TIME_T__ * 4 + 4)
#endif /* __SIZEOF_TIME_T__ <= 4 */
#define __OFFSET_TIMEX_PRECISION (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__)
#define __OFFSET_TIMEX_TOLERANCE (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 2)
#define __OFFSET_TIMEX_TIME      (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 3)
#define __OFFSET_TIMEX_TICK      (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 3 + __SIZEOF_TIMEVAL)
#define __OFFSET_TIMEX_PPSFREQ   (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 4 + __SIZEOF_TIMEVAL)
#define __OFFSET_TIMEX_JITTER    (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 5 + __SIZEOF_TIMEVAL)
#define __OFFSET_TIMEX_SHIFT     (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 6 + __SIZEOF_TIMEVAL)
#define __OFFSET_TIMEX_STABIL    (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 7 + __SIZEOF_TIMEVAL)
#define __OFFSET_TIMEX_JITCNT    (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 8 + __SIZEOF_TIMEVAL)
#define __OFFSET_TIMEX_CALCNT    (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 9 + __SIZEOF_TIMEVAL)
#define __OFFSET_TIMEX_ERRCNT    (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 10 + __SIZEOF_TIMEVAL)
#define __OFFSET_TIMEX_STBCNT    (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 11 + __SIZEOF_TIMEVAL)
#define __OFFSET_TIMEX_TAI       (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 12 + __SIZEOF_TIMEVAL)
#define __OFFSET_TIMEX___PAD     (__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 13 + __SIZEOF_TIMEVAL)
#define __SIZEOF_TIMEX           ((__OFFSET_TIMEX_CONSTANT + __SIZEOF_TIME_T__ * 13 + __SIZEOF_TIMEVAL + 44 + (__ALIGNOF_TIMEVAL - 1)) & ~(__ALIGNOF_TIMEVAL - 1))
#define __ALIGNOF_TIMEX          __ALIGNOF_TIMEVAL

#define __OFFSET_TIMEX32_MODES     0
#if __ALIGNOF_TIME32_T__ > 4
#define __OFFSET_TIMEX32_OFFSET    __ALIGNOF_TIME32_T__
#else /* __SIZEOF_TIME32_T__ > 4 */
#define __OFFSET_TIMEX32_OFFSET    4
#endif /* __SIZEOF_TIME32_T__ <= 4 */
#define __OFFSET_TIMEX32_FREQ      (__OFFSET_TIMEX32_OFFSET + __SIZEOF_TIME32_T__)
#define __OFFSET_TIMEX32_MAXERROR  (__OFFSET_TIMEX32_OFFSET + __SIZEOF_TIME32_T__ * 2)
#define __OFFSET_TIMEX32_ESTERROR  (__OFFSET_TIMEX32_OFFSET + __SIZEOF_TIME32_T__ * 3)
#define __OFFSET_TIMEX32_STATUS    (__OFFSET_TIMEX32_OFFSET + __SIZEOF_TIME32_T__ * 4)
#if __ALIGNOF_TIME32_T__ > 4
#define __OFFSET_TIMEX32_CONSTANT  (__OFFSET_TIMEX32_OFFSET + __SIZEOF_TIME32_T__ * 5)
#else /* __SIZEOF_TIME32_T__ > 4 */
#define __OFFSET_TIMEX32_CONSTANT  (__OFFSET_TIMEX32_OFFSET + __SIZEOF_TIME32_T__ * 4 + 4)
#endif /* __SIZEOF_TIME32_T__ <= 4 */
#define __OFFSET_TIMEX32_PRECISION (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__)
#define __OFFSET_TIMEX32_TOLERANCE (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 2)
#define __OFFSET_TIMEX32_TIME      (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 3)
#define __OFFSET_TIMEX32_TICK      (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 3 + __SIZEOF_TIMEVAL32)
#define __OFFSET_TIMEX32_PPSFREQ   (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 4 + __SIZEOF_TIMEVAL32)
#define __OFFSET_TIMEX32_JITTER    (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 5 + __SIZEOF_TIMEVAL32)
#define __OFFSET_TIMEX32_SHIFT     (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 6 + __SIZEOF_TIMEVAL32)
#define __OFFSET_TIMEX32_STABIL    (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 7 + __SIZEOF_TIMEVAL32)
#define __OFFSET_TIMEX32_JITCNT    (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 8 + __SIZEOF_TIMEVAL32)
#define __OFFSET_TIMEX32_CALCNT    (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 9 + __SIZEOF_TIMEVAL32)
#define __OFFSET_TIMEX32_ERRCNT    (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 10 + __SIZEOF_TIMEVAL32)
#define __OFFSET_TIMEX32_STBCNT    (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 11 + __SIZEOF_TIMEVAL32)
#define __OFFSET_TIMEX32_TAI       (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 12 + __SIZEOF_TIMEVAL32)
#define __OFFSET_TIMEX32___PAD     (__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 13 + __SIZEOF_TIMEVAL32)
#define __SIZEOF_TIMEX32           ((__OFFSET_TIMEX32_CONSTANT + __SIZEOF_TIME32_T__ * 13 + __SIZEOF_TIMEVAL32 + 44 + (__ALIGNOF_TIMEVAL32 - 1)) & ~(__ALIGNOF_TIMEVAL32 - 1))
#define __ALIGNOF_TIMEX32          __ALIGNOF_TIMEVAL32

#define __OFFSET_TIMEX64_MODES     0
#if __ALIGNOF_TIME64_T__ > 4
#define __OFFSET_TIMEX64_OFFSET    __ALIGNOF_TIME64_T__
#else /* __SIZEOF_TIME64_T__ > 4 */
#define __OFFSET_TIMEX64_OFFSET    4
#endif /* __SIZEOF_TIME64_T__ <= 4 */
#define __OFFSET_TIMEX64_FREQ      (__OFFSET_TIMEX64_OFFSET + __SIZEOF_TIME64_T__)
#define __OFFSET_TIMEX64_MAXERROR  (__OFFSET_TIMEX64_OFFSET + __SIZEOF_TIME64_T__ * 2)
#define __OFFSET_TIMEX64_ESTERROR  (__OFFSET_TIMEX64_OFFSET + __SIZEOF_TIME64_T__ * 3)
#define __OFFSET_TIMEX64_STATUS    (__OFFSET_TIMEX64_OFFSET + __SIZEOF_TIME64_T__ * 4)
#if __ALIGNOF_TIME64_T__ > 4
#define __OFFSET_TIMEX64_CONSTANT  (__OFFSET_TIMEX64_OFFSET + __SIZEOF_TIME64_T__ * 5)
#else /* __SIZEOF_TIME64_T__ > 4 */
#define __OFFSET_TIMEX64_CONSTANT  (__OFFSET_TIMEX64_OFFSET + __SIZEOF_TIME64_T__ * 4 + 4)
#endif /* __SIZEOF_TIME64_T__ <= 4 */
#define __OFFSET_TIMEX64_PRECISION (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__)
#define __OFFSET_TIMEX64_TOLERANCE (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 2)
#define __OFFSET_TIMEX64_TIME      (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 3)
#define __OFFSET_TIMEX64_TICK      (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 3 + __SIZEOF_TIMEVAL64)
#define __OFFSET_TIMEX64_PPSFREQ   (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 4 + __SIZEOF_TIMEVAL64)
#define __OFFSET_TIMEX64_JITTER    (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 5 + __SIZEOF_TIMEVAL64)
#define __OFFSET_TIMEX64_SHIFT     (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 6 + __SIZEOF_TIMEVAL64)
#define __OFFSET_TIMEX64_STABIL    (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 7 + __SIZEOF_TIMEVAL64)
#define __OFFSET_TIMEX64_JITCNT    (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 8 + __SIZEOF_TIMEVAL64)
#define __OFFSET_TIMEX64_CALCNT    (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 9 + __SIZEOF_TIMEVAL64)
#define __OFFSET_TIMEX64_ERRCNT    (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 10 + __SIZEOF_TIMEVAL64)
#define __OFFSET_TIMEX64_STBCNT    (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 11 + __SIZEOF_TIMEVAL64)
#define __OFFSET_TIMEX64_TAI       (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 12 + __SIZEOF_TIMEVAL64)
#define __OFFSET_TIMEX64___PAD     (__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 13 + __SIZEOF_TIMEVAL64)
#define __SIZEOF_TIMEX64           ((__OFFSET_TIMEX64_CONSTANT + __SIZEOF_TIME64_T__ * 13 + __SIZEOF_TIMEVAL64 + 44 + (__ALIGNOF_TIMEVAL64 - 1)) & ~(__ALIGNOF_TIMEVAL64 - 1))
#define __ALIGNOF_TIMEX64          __ALIGNOF_TIMEVAL64


#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("modes")
#pragma push_macro("offset")
#pragma push_macro("freq")
#pragma push_macro("maxerror")
#pragma push_macro("esterror")
#pragma push_macro("status")
#pragma push_macro("constant")
#pragma push_macro("precision")
#pragma push_macro("tolerance")
#pragma push_macro("time")
#pragma push_macro("tick")
#pragma push_macro("ppsfreq")
#pragma push_macro("jitter")
#pragma push_macro("shift")
#pragma push_macro("stabil")
#pragma push_macro("jitcnt")
#pragma push_macro("calcnt")
#pragma push_macro("errcnt")
#pragma push_macro("stbcnt")
#pragma push_macro("tai")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef modes
#undef offset
#undef freq
#undef maxerror
#undef esterror
#undef status
#undef constant
#undef precision
#undef tolerance
#undef time
#undef tick
#undef ppsfreq
#undef jitter
#undef shift
#undef stabil
#undef jitcnt
#undef calcnt
#undef errcnt
#undef stbcnt
#undef tai

struct timex /*[PREFIX()]*/ {
	__UINT32_TYPE__      modes;     /* ??? */
	__time_t             offset;    /* ??? */
	__time_t             freq;      /* ??? */
	__time_t             maxerror;  /* ??? */
	__time_t             esterror;  /* ??? */
	__INT32_TYPE__       status;    /* ??? */
	__time_t             constant;  /* ??? */
	__time_t             precision; /* ??? */
	__time_t             tolerance; /* ??? */
	struct timeval       time;      /* ??? */
	__time_t             tick;      /* ??? */
	__time_t             ppsfreq;   /* ??? */
	__time_t             jitter;    /* ??? */
	__time_t             shift;     /* ??? */
	__time_t             stabil;    /* ??? */
	__time_t             jitcnt;    /* ??? */
	__time_t             calcnt;    /* ??? */
	__time_t             errcnt;    /* ??? */
	__time_t             stbcnt;    /* ??? */
	__time_t             tai;       /* ??? */
	__UINT32_TYPE__    __pad[11];   /* ... */
};

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define _TIMEX_MATCHES_TIMEX64 1
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

#ifdef __USE_TIME64
#if (defined(__USE_TIME_BITS64) || defined(_TIMEX_MATCHES_TIMEX64)) && defined(__USE_STRUCT64_MACRO)
#define timex64 timex
#else /* (__USE_TIME_BITS64 || _TIMEX_MATCHES_TIMEX64) && __USE_STRUCT64_MACRO */
#define __timex64 timex64
#endif /* (!__USE_TIME_BITS64 && !_TIMEX_MATCHES_TIMEX64) || !__USE_STRUCT64_MACRO */
#endif /* __USE_TIME64 */

#if (defined(__USE_TIME_BITS64) || defined(_TIMEX_MATCHES_TIMEX64)) && defined(__USE_STRUCT64_MACRO)
#define __timex64 timex
#else /* (__USE_TIME_BITS64 || _TIMEX_MATCHES_TIMEX64) && __USE_STRUCT64_MACRO */
struct __timex64 /*[NAME(timex64)][PREFIX()]*/ {
	__UINT32_TYPE__      modes;     /* ??? */
	__time64_t           offset;    /* ??? */
	__time64_t           freq;      /* ??? */
	__time64_t           maxerror;  /* ??? */
	__time64_t           esterror;  /* ??? */
	__INT32_TYPE__       status;    /* ??? */
	__time64_t           constant;  /* ??? */
	__time64_t           precision; /* ??? */
	__time64_t           tolerance; /* ??? */
	struct __timeval64   time;      /* ??? */
	__time64_t           tick;      /* ??? */
	__time64_t           ppsfreq;   /* ??? */
	__time64_t           jitter;    /* ??? */
	__time64_t           shift;     /* ??? */
	__time64_t           stabil;    /* ??? */
	__time64_t           jitcnt;    /* ??? */
	__time64_t           calcnt;    /* ??? */
	__time64_t           errcnt;    /* ??? */
	__time64_t           stbcnt;    /* ??? */
	__time64_t           tai;       /* ??? */
	__UINT32_TYPE__    __pad[11];   /* ... */
};
#endif /* (!__USE_TIME_BITS64 && !_TIMEX_MATCHES_TIMEX64) || !__USE_STRUCT64_MACRO */

#ifdef __USE_KOS
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define timex32 timex
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define __timex32 timex32
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */

#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __timex32 timex
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __timex32 /*[NAME(timex32)][PREFIX()]*/ {
	__UINT32_TYPE__      modes;     /* ??? */
	__time32_t           offset;    /* ??? */
	__time32_t           freq;      /* ??? */
	__time32_t           maxerror;  /* ??? */
	__time32_t           esterror;  /* ??? */
	__INT32_TYPE__       status;    /* ??? */
	__time32_t           constant;  /* ??? */
	__time32_t           precision; /* ??? */
	__time32_t           tolerance; /* ??? */
	struct __timeval32   time;      /* ??? */
	__time32_t           tick;      /* ??? */
	__time32_t           ppsfreq;   /* ??? */
	__time32_t           jitter;    /* ??? */
	__time32_t           shift;     /* ??? */
	__time32_t           stabil;    /* ??? */
	__time32_t           jitcnt;    /* ??? */
	__time32_t           calcnt;    /* ??? */
	__time32_t           errcnt;    /* ??? */
	__time32_t           stbcnt;    /* ??? */
	__time32_t           tai;       /* ??? */
	__UINT32_TYPE__    __pad[11];   /* ... */
};
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("tai")
#pragma pop_macro("stbcnt")
#pragma pop_macro("errcnt")
#pragma pop_macro("calcnt")
#pragma pop_macro("jitcnt")
#pragma pop_macro("stabil")
#pragma pop_macro("shift")
#pragma pop_macro("jitter")
#pragma pop_macro("ppsfreq")
#pragma pop_macro("tick")
#pragma pop_macro("time")
#pragma pop_macro("tolerance")
#pragma pop_macro("precision")
#pragma pop_macro("constant")
#pragma pop_macro("status")
#pragma pop_macro("esterror")
#pragma pop_macro("maxerror")
#pragma pop_macro("freq")
#pragma pop_macro("offset")
#pragma pop_macro("modes")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_TIMEX_H */
