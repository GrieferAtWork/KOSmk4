/* HASH CRC-32:0xcd91c99c */
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
/* (#) Portability: FreeBSD       (/sys/sys/timex.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/timex.h) */
/* (#) Portability: NetBSD        (/sys/sys/timex.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/timex.h) */
/* (#) Portability: diet libc     (/include/sys/timex.h) */
/* (#) Portability: libc4/5       (/include/sys/timex.h) */
/* (#) Portability: musl libc     (/include/sys/timex.h) */
/* (#) Portability: uClibc        (/include/sys/timex.h) */
#ifndef _SYS_TIMEX_H
#define _SYS_TIMEX_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/timex.h>
#include <bits/os/timex.h>
#include <bits/crt/ntptimeval.h>
#include <bits/types.h>

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

#if defined(__CRT_HAVE_adjtimex) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> adjtimex(2), adjtimex64(2) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,__adjtimex,(struct timex *__restrict __ntx),adjtimex,(__ntx))
#elif defined(__CRT_HAVE___adjtimex) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> adjtimex(2), adjtimex64(2) */
__CDECLARE(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,__adjtimex,(struct timex *__restrict __ntx),(__ntx))
#elif defined(__CRT_HAVE___libc_adjtimex) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> adjtimex(2), adjtimex64(2) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,__adjtimex,(struct timex *__restrict __ntx),__libc_adjtimex,(__ntx))
#elif defined(__CRT_HAVE_adjtimex64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> adjtimex(2), adjtimex64(2) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,__adjtimex,(struct timex *__restrict __ntx),adjtimex64,(__ntx))
#elif defined(__CRT_HAVE___adjtimex64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> adjtimex(2), adjtimex64(2) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,__adjtimex,(struct timex *__restrict __ntx),__adjtimex64,(__ntx))
#elif (defined(__CRT_HAVE___libc_adjtimex) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_adjtimex64) || defined(__CRT_HAVE___adjtimex64) || defined(__CRT_HAVE_adjtimex) || defined(__CRT_HAVE___adjtimex)
#include <libc/local/sys.timex/adjtimex.h>
/* >> adjtimex(2), adjtimex64(2) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RW(1) int __NOTHROW_NCX(__LIBCCALL __adjtimex)(struct timex *__restrict __ntx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(adjtimex))(__ntx); }
#endif /* ... */
#if defined(__CRT_HAVE_adjtimex) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> adjtimex(2), adjtimex64(2) */
__CDECLARE(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,adjtimex,(struct timex *__restrict __ntx),(__ntx))
#elif defined(__CRT_HAVE___adjtimex) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> adjtimex(2), adjtimex64(2) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,adjtimex,(struct timex *__restrict __ntx),__adjtimex,(__ntx))
#elif defined(__CRT_HAVE___libc_adjtimex) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> adjtimex(2), adjtimex64(2) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,adjtimex,(struct timex *__restrict __ntx),__libc_adjtimex,(__ntx))
#elif defined(__CRT_HAVE_adjtimex64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> adjtimex(2), adjtimex64(2) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,adjtimex,(struct timex *__restrict __ntx),adjtimex64,(__ntx))
#elif defined(__CRT_HAVE___adjtimex64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> adjtimex(2), adjtimex64(2) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,adjtimex,(struct timex *__restrict __ntx),__adjtimex64,(__ntx))
#elif (defined(__CRT_HAVE___libc_adjtimex) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_adjtimex64) || defined(__CRT_HAVE___adjtimex64) || defined(__CRT_HAVE_adjtimex) || defined(__CRT_HAVE___adjtimex)
#include <libc/local/sys.timex/adjtimex.h>
/* >> adjtimex(2), adjtimex64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(adjtimex, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RW(1) int __NOTHROW_NCX(__LIBCCALL adjtimex)(struct timex *__restrict __ntx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(adjtimex))(__ntx); })
#endif /* ... */
#if defined(__CRT_HAVE_ntp_gettimex) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> ntp_gettime(3), ntp_gettime64(3) */
__CREDIRECT(__ATTR_ACCESS_WR(1),int,__NOTHROW_NCX,ntp_gettime,(struct ntptimeval *__restrict __ntv),ntp_gettimex,(__ntv))
#elif defined(__CRT_HAVE_ntp_gettimex64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> ntp_gettime(3), ntp_gettime64(3) */
__CREDIRECT(__ATTR_ACCESS_WR(1),int,__NOTHROW_NCX,ntp_gettime,(struct ntptimeval *__restrict __ntv),ntp_gettimex64,(__ntv))
#elif defined(__CRT_HAVE_ntp_gettimex64) || defined(__CRT_HAVE_ntp_gettimex)
#include <libc/local/sys.timex/ntp_gettime.h>
/* >> ntp_gettime(3), ntp_gettime64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ntp_gettime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(1) int __NOTHROW_NCX(__LIBCCALL ntp_gettime)(struct ntptimeval *__restrict __ntv) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ntp_gettime))(__ntv); })
#endif /* ... */
#if defined(__CRT_HAVE_ntp_adjtime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> ntp_adjtime(3), ntp_adjtime64(3) */
__CDECLARE(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,ntp_adjtime,(struct timex *__restrict __tntx),(__tntx))
#elif defined(__CRT_HAVE_ntp_adjtime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> ntp_adjtime(3), ntp_adjtime64(3) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,ntp_adjtime,(struct timex *__restrict __tntx),ntp_adjtime64,(__tntx))
#elif defined(__CRT_HAVE_ntp_adjtime64) || defined(__CRT_HAVE_ntp_adjtime)
#include <libc/local/sys.timex/ntp_adjtime.h>
/* >> ntp_adjtime(3), ntp_adjtime64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ntp_adjtime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RW(1) int __NOTHROW_NCX(__LIBCCALL ntp_adjtime)(struct timex *__restrict __tntx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ntp_adjtime))(__tntx); })
#endif /* ... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_adjtimex) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> adjtimex(2), adjtimex64(2) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,adjtimex64,(struct timex64 *__restrict __ntx),adjtimex,(__ntx))
#elif defined(__CRT_HAVE___adjtimex) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> adjtimex(2), adjtimex64(2) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,adjtimex64,(struct timex64 *__restrict __ntx),__adjtimex,(__ntx))
#elif defined(__CRT_HAVE___libc_adjtimex) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> adjtimex(2), adjtimex64(2) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,adjtimex64,(struct timex64 *__restrict __ntx),__libc_adjtimex,(__ntx))
#elif defined(__CRT_HAVE_adjtimex64)
/* >> adjtimex(2), adjtimex64(2) */
__CDECLARE(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,adjtimex64,(struct timex64 *__restrict __ntx),(__ntx))
#elif defined(__CRT_HAVE___adjtimex64)
/* >> adjtimex(2), adjtimex64(2) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,adjtimex64,(struct timex64 *__restrict __ntx),__adjtimex64,(__ntx))
#elif defined(__CRT_HAVE_adjtimex) || defined(__CRT_HAVE___adjtimex)
#include <libc/local/sys.timex/adjtimex64.h>
/* >> adjtimex(2), adjtimex64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(adjtimex64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RW(1) int __NOTHROW_NCX(__LIBCCALL adjtimex64)(struct timex64 *__restrict __ntx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(adjtimex64))(__ntx); })
#endif /* ... */
#if defined(__CRT_HAVE_ntp_adjtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> ntp_adjtime(3), ntp_adjtime64(3) */
__CREDIRECT(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,ntp_adjtime64,(struct timex64 *__restrict __tntx),ntp_adjtime,(__tntx))
#elif defined(__CRT_HAVE_ntp_adjtime64)
/* >> ntp_adjtime(3), ntp_adjtime64(3) */
__CDECLARE(__ATTR_ACCESS_RW(1),int,__NOTHROW_NCX,ntp_adjtime64,(struct timex64 *__restrict __tntx),(__tntx))
#elif defined(__CRT_HAVE_ntp_adjtime)
#include <libc/local/sys.timex/ntp_adjtime64.h>
/* >> ntp_adjtime(3), ntp_adjtime64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ntp_adjtime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RW(1) int __NOTHROW_NCX(__LIBCCALL ntp_adjtime64)(struct timex64 *__restrict __tntx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ntp_adjtime64))(__tntx); })
#endif /* ... */
#if defined(__CRT_HAVE_ntp_gettimex) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> ntp_gettime(3), ntp_gettime64(3) */
__CREDIRECT(__ATTR_ACCESS_WR(1),int,__NOTHROW_NCX,ntp_gettime64,(struct ntptimeval64 *__restrict __ntv),ntp_gettimex,(__ntv))
#elif defined(__CRT_HAVE_ntp_gettimex64)
/* >> ntp_gettime(3), ntp_gettime64(3) */
__CREDIRECT(__ATTR_ACCESS_WR(1),int,__NOTHROW_NCX,ntp_gettime64,(struct ntptimeval64 *__restrict __ntv),ntp_gettimex64,(__ntv))
#elif defined(__CRT_HAVE_ntp_gettimex)
#include <libc/local/sys.timex/ntp_gettime64.h>
/* >> ntp_gettime(3), ntp_gettime64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ntp_gettime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(1) int __NOTHROW_NCX(__LIBCCALL ntp_gettime64)(struct ntptimeval64 *__restrict __ntv) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ntp_gettime64))(__ntv); })
#endif /* ... */
#endif /* __USE_TIME64 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_TIMEX_H */
