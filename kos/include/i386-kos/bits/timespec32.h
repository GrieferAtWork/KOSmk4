/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_TIMESPEC32_H
#define _I386_KOS_BITS_TIMESPEC32_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <bits/timespec-cxx-support.h>

#ifndef __x86_64__
#include <features.h>
#ifdef __USE_TIME_BITS64
/* Configure to use `timespec32_64' as `timespec' */

#define timespec32     __timespec32
#define timespec32_64  timespec
#define __timespec64   timespec
#define __timespec_alt __timespec32
#ifdef __USE_TIME64
#define timespec64    timespec
#endif /* __USE_TIME64 */

#define __OFFSET_TIMESPEC_SEC    __OFFSET_TIMESPEC32_64_SEC
#define __OFFSET_TIMESPEC_NSEC   __OFFSET_TIMESPEC32_64_NSEC
#define __SIZEOF_TIMESPEC        __SIZEOF_TIMESPEC32_64
#define __OFFSET_TIMESPEC64_SEC  __OFFSET_TIMESPEC32_64_SEC
#define __OFFSET_TIMESPEC64_NSEC __OFFSET_TIMESPEC32_64_NSEC
#define __SIZEOF_TIMESPEC64      __SIZEOF_TIMESPEC32_64

#else /* __USE_TIME_BITS64 */
/* Configure to use `timespec32' as `timespec' */

#define __timespec32  timespec
#define timespec32    timespec
#ifdef __USE_TIME64
#define timespec32_64  timespec64
#define __timespec64   timespec64
#define __timespec_alt timespec64
#else /* __USE_TIME64 */
#define timespec32_64  __timespec64
#define __timespec_alt __timespec64
#endif /* __USE_TIME64 */

#define __OFFSET_TIMESPEC_SEC    __OFFSET_TIMESPEC32_SEC
#define __OFFSET_TIMESPEC_NSEC   __OFFSET_TIMESPEC32_NSEC
#define __SIZEOF_TIMESPEC        __SIZEOF_TIMESPEC32
#define __OFFSET_TIMESPEC64_SEC  __OFFSET_TIMESPEC32_64_SEC
#define __OFFSET_TIMESPEC64_NSEC __OFFSET_TIMESPEC32_64_NSEC
#define __SIZEOF_TIMESPEC64      __SIZEOF_TIMESPEC32_64

#endif /* !__USE_TIME_BITS64 */
#define __timespec_defined 1
#endif /* !__x86_64__ */


#define __OFFSET_TIMESPEC32_SEC      0
#define __OFFSET_TIMESPEC32_NSEC     4
#define __SIZEOF_TIMESPEC32          8
#define __OFFSET_TIMESPEC32_64_SEC   0
#define __OFFSET_TIMESPEC32_64_NSEC  8
#define __SIZEOF_TIMESPEC32_64       16

#ifdef __CC__
__DECL_BEGIN
__TIMESPEC_CXX_DECL_BEGIN

/* 32-bit timespec for i386 */
struct timespec32 /*[PREFIX(tv_)]*/ {
	__INT32_TYPE__  tv_sec;   /* Seconds */
	__UINT32_TYPE__ tv_nsec;  /* Nano seconds (<= 1000000000 == 1_000_000_000) */
	__TIMESPEC_CXX_SUPPORT(struct timespec32, __INT32_TYPE__, __UINT32_TYPE__)
};
__TIMESPEC_CXX_SUPPORT2(struct timespec32, __INT32_TYPE__, __UINT32_TYPE__)

/* 64-bit timespec for i386 */
struct timespec32_64 /*[PREFIX(tv_)]*/ {
	__INT64_TYPE__    tv_sec;   /* Seconds */
	__UINT32_TYPE__   tv_nsec;  /* Nano seconds (<= 1000000000 == 1_000_000_000) */
	__UINT32_TYPE__ __tv_pad;   /* ... */
	__TIMESPEC_CXX_SUPPORT(struct timespec32_64, __INT64_TYPE__, __UINT32_TYPE__)
};
__TIMESPEC_CXX_SUPPORT2(struct timespec32_64, __INT64_TYPE__, __UINT32_TYPE__)

__TIMESPEC_CXX_DECL_END
__DECL_END
#endif /* __CC__ */

#ifndef __x86_64__
#ifndef __USE_KOS
#undef timespec32
#undef timespec32_64
#endif /* !__USE_KOS */
#endif /* !__x86_64__ */


#endif /* !_I386_KOS_BITS_TIMESPEC32_H */
