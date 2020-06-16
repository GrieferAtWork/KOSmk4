/* HASH CRC-32:0x96dba9db */
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
#ifndef _SYS_TIMEX_H
#define _SYS_TIMEX_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <sys/time.h>
#include <bits/timex.h>
#include <bits/types.h>

/* Documentation taken from /usr/include/i386-linux-gnu/sys/timex.h */
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

#define NTP_API  4 /* NTP API version */

/* Clock states (time_state) */
#define TIME_OK     0          /* clock synchronized, no leap second */
#define TIME_INS    1          /* insert leap second */
#define TIME_DEL    2          /* delete leap second */
#define TIME_OOP    3          /* leap second in progress */
#define TIME_WAIT   4          /* leap second has occurred */
#define TIME_ERROR  5          /* clock not synchronized */
#define TIME_BAD    TIME_ERROR /* bw compat */

/* Maximum time constant of the PLL.  */
#define MAXTC       6


__SYSDECL_BEGIN

#ifdef __CC__

#if __TM_SIZEOF(TIME) <= 4
#define __ntptimeval64   __ntptimeval_alt
#define __ntptimeval32   ntptimeval
#else /* __TM_SIZEOF(TIME) <= 4 */
#define __ntptimeval64   ntptimeval
#define __ntptimeval32   __ntptimeval_alt
#endif /* __TM_SIZEOF(TIME) > 4 */

#ifdef __USE_TIME64
#if __TM_SIZEOF(TIME) <= 4
#define __ntptimeval_alt ntptimeval64
#else /* __TM_SIZEOF(TIME) <= 4 */
#define ntptimeval64     ntptimeval
#endif /* __TM_SIZEOF(TIME) > 4 */
#endif /* __USE_TIME64 */

#ifdef __USE_KOS
#if __TM_SIZEOF(TIME) <= 4
#define ntptimeval32 ntptimeval
#else /* __TM_SIZEOF(TIME) <= 4 */
#define ntptimeval32 __ntptimeval_alt
#endif /* __TM_SIZEOF(TIME) > 4 */
#endif /* __USE_KOS */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("time")
#pragma push_macro("maxerror")
#pragma push_macro("esterror")
#pragma push_macro("tai")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef time
#undef maxerror
#undef esterror
#undef tai
struct ntptimeval {
	struct timeval       time;            /* current time (ro) */
	__LONGPTR_TYPE__     maxerror;        /* maximum error (us) (ro) */
	__LONGPTR_TYPE__     esterror;        /* estimated error (us) (ro) */
	__LONGPTR_TYPE__     tai;             /* TAI offset (ro) */
	__LONGPTR_TYPE__   __glibc_reserved1; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved2; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved3; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved4; /* ... */
};
struct __ntptimeval_alt {
	struct __timeval_alt time;            /* current time (ro) */
	__LONGPTR_TYPE__     maxerror;        /* maximum error (us) (ro) */
	__LONGPTR_TYPE__     esterror;        /* estimated error (us) (ro) */
	__LONGPTR_TYPE__     tai;             /* TAI offset (ro) */
	__LONGPTR_TYPE__   __glibc_reserved1; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved2; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved3; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved4; /* ... */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("tai")
#pragma pop_macro("esterror")
#pragma pop_macro("maxerror")
#pragma pop_macro("time")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#if defined(__CRT_HAVE_adjtimex64) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__adjtimex,(struct timex *__restrict __ntx),adjtimex64,(__ntx))
#elif defined(__CRT_HAVE___adjtimex64) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__adjtimex,(struct timex *__restrict __ntx),__adjtimex64,(__ntx))
#elif defined(__CRT_HAVE_adjtimex) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__adjtimex,(struct timex *__restrict __ntx),adjtimex,(__ntx))
#elif defined(__CRT_HAVE___adjtimex) && !defined(__USE_TIME_BITS64)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__adjtimex,(struct timex *__restrict __ntx),(__ntx))
#elif defined(__CRT_HAVE_adjtimex64) || defined(__CRT_HAVE___adjtimex64) || defined(__CRT_HAVE_adjtimex) || defined(__CRT_HAVE___adjtimex)
#include <local/sys.timex/adjtimex.h>
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __adjtimex)(struct timex *__restrict __ntx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(adjtimex))(__ntx); }
#endif /* ... */
#if defined(__CRT_HAVE_adjtimex64) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,adjtimex,(struct timex *__restrict __ntx),adjtimex64,(__ntx))
#elif defined(__CRT_HAVE___adjtimex64) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,adjtimex,(struct timex *__restrict __ntx),__adjtimex64,(__ntx))
#elif defined(__CRT_HAVE_adjtimex) && !defined(__USE_TIME_BITS64)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,adjtimex,(struct timex *__restrict __ntx),(__ntx))
#elif defined(__CRT_HAVE___adjtimex) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,adjtimex,(struct timex *__restrict __ntx),__adjtimex,(__ntx))
#elif defined(__CRT_HAVE_adjtimex64) || defined(__CRT_HAVE___adjtimex64) || defined(__CRT_HAVE_adjtimex) || defined(__CRT_HAVE___adjtimex)
#include <local/sys.timex/adjtimex.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(adjtimex, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL adjtimex)(struct timex *__restrict __ntx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(adjtimex))(__ntx); })
#endif /* ... */
#if defined(__CRT_HAVE_ntp_gettimex64) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,ntp_gettime,(struct ntptimeval *__restrict __ntv),ntp_gettimex64,(__ntv))
#elif defined(__CRT_HAVE_ntp_gettimex) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,ntp_gettime,(struct ntptimeval *__restrict __ntv),ntp_gettimex,(__ntv))
#elif defined(__CRT_HAVE_ntp_gettimex64) || (defined(__CRT_HAVE_ntp_gettime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_ntp_gettimex)
#include <local/sys.timex/ntp_gettime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ntp_gettime, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL ntp_gettime)(struct ntptimeval *__restrict __ntv) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ntp_gettime))(__ntv); })
#endif /* ... */
#if defined(__CRT_HAVE_ntp_adjtime64) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,ntp_adjtime,(struct timex *__restrict __tntx),ntp_adjtime64,(__tntx))
#elif defined(__CRT_HAVE_ntp_adjtime) && !defined(__USE_TIME_BITS64)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,ntp_adjtime,(struct timex *__restrict __tntx),(__tntx))
#elif defined(__CRT_HAVE_ntp_adjtime64) || defined(__CRT_HAVE_ntp_adjtime)
#include <local/sys.timex/ntp_adjtime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ntp_adjtime, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL ntp_adjtime)(struct timex *__restrict __tntx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ntp_adjtime))(__tntx); })
#endif /* ... */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_adjtimex64
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,adjtimex64,(struct timex64 *__restrict __ntx),(__ntx))
#elif defined(__CRT_HAVE___adjtimex64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,adjtimex64,(struct timex64 *__restrict __ntx),__adjtimex64,(__ntx))
#elif defined(__CRT_HAVE_adjtimex) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,adjtimex64,(struct timex64 *__restrict __ntx),adjtimex,(__ntx))
#elif defined(__CRT_HAVE_adjtimex) || defined(__CRT_HAVE___adjtimex)
#include <local/sys.timex/adjtimex64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(adjtimex64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL adjtimex64)(struct timex64 *__restrict __ntx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(adjtimex64))(__ntx); })
#endif /* ... */
#ifdef __CRT_HAVE_ntp_adjtime64
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,ntp_adjtime64,(struct timex64 *__restrict __tntx),(__tntx))
#elif defined(__CRT_HAVE_ntp_adjtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,ntp_adjtime64,(struct timex64 *__restrict __tntx),ntp_adjtime,(__tntx))
#elif defined(__CRT_HAVE_ntp_adjtime)
#include <local/sys.timex/ntp_adjtime64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ntp_adjtime64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL ntp_adjtime64)(struct timex64 *__restrict __tntx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ntp_adjtime64))(__tntx); })
#endif /* ... */
#ifdef __CRT_HAVE_ntp_gettimex64
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,ntp_gettime64,(struct ntptimeval64 *__restrict __ntv),ntp_gettimex64,(__ntv))
#elif defined(__CRT_HAVE_ntp_gettime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,ntp_gettime64,(struct ntptimeval64 *__restrict __ntv),ntp_gettime,(__ntv))
#elif defined(__CRT_HAVE_ntp_gettimex)
#include <local/sys.timex/ntp_gettime64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ntp_gettime64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL ntp_gettime64)(struct ntptimeval64 *__restrict __ntv) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ntp_gettime64))(__ntv); })
#endif /* ... */
#endif /* __USE_TIME64 */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_TIMEX_H */
