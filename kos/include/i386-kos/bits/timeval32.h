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
#ifndef _I386_KOS_BITS_TIMEVAL32_H
#define _I386_KOS_BITS_TIMEVAL32_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/timeval-cxx-support.h>

#ifdef __x86_64__
#define timevalx32    __timevalx32
#define timevalx32_64 __timevalx32_64
#else /* __x86_64__ */
#include <features.h>
#ifdef __USE_TIME_BITS64
/* Configure:
 *   - `timevalx32_64' as `timeval'
 *   - `timevalx32' as `__timeval32' */

#define timevalx32      __timeval32
#define timevalx32_64   timeval
#define __timevalx32    __timeval32
#define __timevalx32_64 timeval
#define __timeval32     __timeval32
#define __timeval64     timeval
#define __timeval_alt   __timeval32
#ifdef __USE_KOS
#define timeval32       __timeval32
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#define timeval64       timeval
#endif /* __USE_TIME64 */

#define __OFFSET_TIMEVAL_SEC    __OFFSET_TIMEVALX32_64_SEC
#define __OFFSET_TIMEVAL_USEC   __OFFSET_TIMEVALX32_64_USEC
#define __SIZEOF_TIMEVAL        __SIZEOF_TIMEVALX32_64
#define __OFFSET_TIMEVAL64_SEC  __OFFSET_TIMEVALX32_64_SEC
#define __OFFSET_TIMEVAL64_USEC __OFFSET_TIMEVALX32_64_USEC
#define __SIZEOF_TIMEVAL64      __SIZEOF_TIMEVALX32_64

#else /* __USE_TIME_BITS64 */
/* Configure:
 *   - `timevalx32_64' as `timeval64' or `__timeval64'
 *   - `timevalx32' as `timeval' */
#define timevalx32      timeval
#define __timeval32     timeval
#define __timevalx32    timeval
#ifdef __USE_TIME64
#define __timevalx32_64 timeval64
#define timevalx32_64   timeval64
#define __timeval64     timeval64
#define __timeval_alt   timeval64
#else /* __USE_TIME64 */
#define __timevalx32_64 __timeval64
#define timevalx32_64   __timeval64
#define __timeval64     __timeval64
#define __timeval_alt   __timeval64
#endif /* __USE_TIME64 */
#ifdef __USE_KOS
#define timeval32       timeval
#endif /* __USE_KOS */

#define __OFFSET_TIMEVAL_SEC    __OFFSET_TIMEVALX32_SEC
#define __OFFSET_TIMEVAL_USEC   __OFFSET_TIMEVALX32_USEC
#define __SIZEOF_TIMEVAL        __SIZEOF_TIMEVALX32
#define __OFFSET_TIMEVAL64_SEC  __OFFSET_TIMEVALX32_64_SEC
#define __OFFSET_TIMEVAL64_USEC __OFFSET_TIMEVALX32_64_USEC
#define __SIZEOF_TIMEVAL64      __SIZEOF_TIMEVALX32_64

#endif /* !__USE_TIME_BITS64 */
#define __timeval_defined 1
#endif /* !__x86_64__ */


#define __OFFSET_TIMEVALX32_SEC      0
#define __OFFSET_TIMEVALX32_USEC     4
#define __SIZEOF_TIMEVALX32          8
#define __OFFSET_TIMEVALX32_64_SEC   0
#define __OFFSET_TIMEVALX32_64_USEC  8
#define __SIZEOF_TIMEVALX32_64       16

#ifdef __CC__
__DECL_BEGIN
__TIMEVAL_CXX_DECL_BEGIN

/* 32-bit timeval for i386 */
struct timevalx32 /*[PREFIX(tv_)]*/ {
	__INT32_TYPE__  tv_sec;   /* Seconds */
	__UINT32_TYPE__ tv_usec;  /* Micro seconds (<= 1000000 == 1_000_000) */
	__TIMEVAL_CXX_SUPPORT(struct timevalx32, __INT32_TYPE__, __UINT32_TYPE__)
};
__TIMEVAL_CXX_SUPPORT2(struct timevalx32, __INT32_TYPE__, __UINT32_TYPE__)

/* 64-bit timeval for i386 */
struct timevalx32_64 /*[PREFIX(tv_)]*/ {
	__INT64_TYPE__    tv_sec;   /* Seconds */
	__UINT32_TYPE__   tv_usec;  /* Micro seconds (<= 1000000 == 1_000_000) */
	__UINT32_TYPE__ __tv_pad;   /* ... */
	__TIMEVAL_CXX_SUPPORT(struct timevalx32_64, __INT64_TYPE__, __UINT32_TYPE__)
};
__TIMEVAL_CXX_SUPPORT2(struct timevalx32_64, __INT64_TYPE__, __UINT32_TYPE__)

__TIMEVAL_CXX_DECL_END
__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS
#undef timevalx32
#undef timevalx32_64
#endif /* !__USE_KOS */

#endif /* !_I386_KOS_BITS_TIMEVAL32_H */
