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
#ifndef _BITS_TIMEX_H
#define _BITS_TIMEX_H 1

#include <__stdinc.h>
#include <bits/types.h>
#include <bits/timeval.h>

/* Documentation taken from Glibc /usr/include/i386-linux-gnu/bits/timex.h */
/* Copyright (C) 1995-2016 Free Software Foundation, Inc.
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

/* Mode codes (timex.mode) */
#define ADJ_OFFSET            0x0001 /* time offset */
#define ADJ_FREQUENCY         0x0002 /* frequency offset */
#define ADJ_MAXERROR          0x0004 /* maximum time error */
#define ADJ_ESTERROR          0x0008 /* estimated time error */
#define ADJ_STATUS            0x0010 /* clock status */
#define ADJ_TIMECONST         0x0020 /* pll time constant */
#define ADJ_TAI               0x0080 /* set TAI offset */
#define ADJ_SETOFFSET         0x0100 /* add 'time' to current time */
#define ADJ_MICRO             0x1000 /* select microsecond resolution */
#define ADJ_NANO              0x2000 /* select nanosecond resolution */
#define ADJ_TICK              0x4000 /* tick value */
#define ADJ_OFFSET_SINGLESHOT 0x8001 /* old-fashioned adjtime */
#define ADJ_OFFSET_SS_READ    0xa001 /* read-only adjtime */

/* xntp 3.4 compatibility names */
#define MOD_OFFSET    ADJ_OFFSET
#define MOD_FREQUENCY ADJ_FREQUENCY
#define MOD_MAXERROR  ADJ_MAXERROR
#define MOD_ESTERROR  ADJ_ESTERROR
#define MOD_STATUS    ADJ_STATUS
#define MOD_TIMECONST ADJ_TIMECONST
#define MOD_CLKB      ADJ_TICK
#define MOD_CLKA      ADJ_OFFSET_SINGLESHOT /* 0x8000 in original */
#define MOD_TAI       ADJ_TAI
#define MOD_MICRO     ADJ_MICRO
#define MOD_NANO      ADJ_NANO


/* Status codes (timex.status) */
#define STA_PLL       0x0001 /* enable PLL updates (rw) */
#define STA_PPSFREQ   0x0002 /* enable PPS freq discipline (rw) */
#define STA_PPSTIME   0x0004 /* enable PPS time discipline (rw) */
#define STA_FLL       0x0008 /* select frequency-lock mode (rw) */

#define STA_INS       0x0010 /* insert leap (rw) */
#define STA_DEL       0x0020 /* delete leap (rw) */
#define STA_UNSYNC    0x0040 /* clock unsynchronized (rw) */
#define STA_FREQHOLD  0x0080 /* hold frequency (rw) */

#define STA_PPSSIGNAL 0x0100 /* PPS signal present (ro) */
#define STA_PPSJITTER 0x0200 /* PPS signal jitter exceeded (ro) */
#define STA_PPSWANDER 0x0400 /* PPS signal wander exceeded (ro) */
#define STA_PPSERROR  0x0800 /* PPS signal calibration error (ro) */

#define STA_CLOCKERR  0x1000 /* clock hardware fault (ro) */
#define STA_NANO      0x2000 /* resolution (0 = us, 1 = ns) (ro) */
#define STA_MODE      0x4000 /* mode (0 = PLL, 1 = FLL) (ro) */
#define STA_CLK       0x8000 /* clock source (0 = A, 1 = B) (ro) */

/* Read-only bits */
#define STA_RONLY \
       (STA_PPSSIGNAL | STA_PPSJITTER | STA_PPSWANDER | STA_PPSERROR | \
        STA_CLOCKERR | STA_NANO | STA_MODE | STA_CLK)

#ifdef __CC__

#if __TM_SIZEOF(TIME) <= 4
#define __timex64  __timex_alt
#define __timex32  timex
#else
#define __timex64  timex
#define __timex32  __timex_alt
#endif

#ifdef __USE_TIME64
#if __TM_SIZEOF(TIME) <= 4
#define __timex_alt timex64
#else
#define timex64     timex
#endif
#endif /* __USE_TIME64 */


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
struct timex {
	__UINT32_TYPE__      modes;     /* mode selector */
	__TM_TYPE(time)      offset;    /* time offset (usec) */
	__TM_TYPE(time)      freq;      /* frequency offset (scaled ppm) */
	__TM_TYPE(time)      maxerror;  /* maximum error (usec) */
	__TM_TYPE(time)      esterror;  /* estimated error (usec) */
	__INT32_TYPE__       status;    /* clock command/status */
	__TM_TYPE(time)      constant;  /* pll time constant */
	__TM_TYPE(time)      precision; /* clock precision (usec) (ro) */
	__TM_TYPE(time)      tolerance; /* clock frequency tolerance (ppm) (ro) */
	struct timeval       time;      /* (read only, except for ADJ_SETOFFSET) */
	__TM_TYPE(time)      tick;      /* (modified) usecs between clock ticks */
	__TM_TYPE(time)      ppsfreq;   /* pps frequency (scaled ppm) (ro) */
	__TM_TYPE(time)      jitter;    /* pps jitter (us) (ro) */
	__TM_TYPE(time)      shift;     /* interval duration (s) (shift) (ro) */
	__TM_TYPE(time)      stabil;    /* pps stability (scaled ppm) (ro) */
	__TM_TYPE(time)      jitcnt;    /* jitter limit exceeded (ro) */
	__TM_TYPE(time)      calcnt;    /* calibration intervals (ro) */
	__TM_TYPE(time)      errcnt;    /* calibration errors (ro) */
	__TM_TYPE(time)      stbcnt;    /* stability limit exceeded (ro) */
	__TM_TYPE(time)      tai;       /* TAI offset (ro) */
	__UINT32_TYPE__    __pad[11];   /* ... */
};

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#if defined(__USE_TIME64) && __TM_SIZEOF(TIME) <= 4
#define timex64     timex
#else
#define __timex_alt timex
#endif
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __timex_alt {
#if __TM_SIZEOF(TIME) <= 4
	__UINT32_TYPE__      modes;     /* mode selector */
	__time64_t           offset;    /* time offset (usec) */
	__time64_t           freq;      /* frequency offset (scaled ppm) */
	__time64_t           maxerror;  /* maximum error (usec) */
	__time64_t           esterror;  /* estimated error (usec) */
	__INT32_TYPE__       status;    /* clock command/status */
	__time64_t           constant;  /* pll time constant */
	__time64_t           precision; /* clock precision (usec) (ro) */
	__time64_t           tolerance; /* clock frequency tolerance (ppm) (ro) */
	struct __timeval_alt time;      /* (read only, except for ADJ_SETOFFSET) */
	__time64_t           tick;      /* (modified) usecs between clock ticks */
	__time64_t           ppsfreq;   /* pps frequency (scaled ppm) (ro) */
	__time64_t           jitter;    /* pps jitter (us) (ro) */
	__time64_t           shift;     /* interval duration (s) (shift) (ro) */
	__time64_t           stabil;    /* pps stability (scaled ppm) (ro) */
	__time64_t           jitcnt;    /* jitter limit exceeded (ro) */
	__time64_t           calcnt;    /* calibration intervals (ro) */
	__time64_t           errcnt;    /* calibration errors (ro) */
	__time64_t           stbcnt;    /* stability limit exceeded (ro) */
	__time64_t           tai;       /* TAI offset (ro) */
	__UINT32_TYPE__    __pad[11];   /* ... */
#else
	__UINT32_TYPE__      modes;     /* mode selector */
	__time32_t           offset;    /* time offset (usec) */
	__time32_t           freq;      /* frequency offset (scaled ppm) */
	__time32_t           maxerror;  /* maximum error (usec) */
	__time32_t           esterror;  /* estimated error (usec) */
	__INT32_TYPE__       status;    /* clock command/status */
	__time32_t           constant;  /* pll time constant */
	__time32_t           precision; /* clock precision (usec) (ro) */
	__time32_t           tolerance; /* clock frequency tolerance (ppm) (ro) */
	struct __timeval_alt time;      /* (read only, except for ADJ_SETOFFSET) */
	__time32_t           tick;      /* (modified) usecs between clock ticks */
	__time32_t           ppsfreq;   /* pps frequency (scaled ppm) (ro) */
	__time32_t           jitter;    /* pps jitter (us) (ro) */
	__time32_t           shift;     /* interval duration (s) (shift) (ro) */
	__time32_t           stabil;    /* pps stability (scaled ppm) (ro) */
	__time32_t           jitcnt;    /* jitter limit exceeded (ro) */
	__time32_t           calcnt;    /* calibration intervals (ro) */
	__time32_t           errcnt;    /* calibration errors (ro) */
	__time32_t           stbcnt;    /* stability limit exceeded (ro) */
	__time32_t           tai;       /* TAI offset (ro) */
	__UINT32_TYPE__    __pad[11];   /* ... */
#endif
};
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

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
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_TIMEX_H */
