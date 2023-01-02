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
#ifndef _BITS_OS_KOS_TIMESPEC_H
#define _BITS_OS_KOS_TIMESPEC_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>
#include <parts/timespec-cxx-support.h>

#define __OFFSET_TIMESPEC_SEC     0
#if __SIZEOF_TIME_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
#define __OFFSET_TIMESPEC_NSEC    (__SIZEOF_TIME_T__ + 4)
#else /* __SIZEOF_TIME_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __OFFSET_TIMESPEC_NSEC    __SIZEOF_TIME_T__
#endif /* __SIZEOF_TIME_T__ > 4 || __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#if __SIZEOF_TIME_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
#define __SIZEOF_TIMESPEC         (__OFFSET_TIMESPEC_NSEC + __SIZEOF_SYSCALL_LONG_T__ + 4)
#else /* __SIZEOF_TIME_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#define __SIZEOF_TIMESPEC         (__OFFSET_TIMESPEC_NSEC + __SIZEOF_SYSCALL_LONG_T__)
#endif /* __SIZEOF_TIME_T__ <= 4 || __SIZEOF_SYSCALL_LONG_T__ > 4 */

#define __OFFSET_TIMESPEC32_SEC     0
#if __SIZEOF_TIME32_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
#define __OFFSET_TIMESPEC32_NSEC    (__SIZEOF_TIME32_T__ + 4)
#else /* __SIZEOF_TIME32_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __OFFSET_TIMESPEC32_NSEC    __SIZEOF_TIME32_T__
#endif /* __SIZEOF_TIME32_T__ > 4 || __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#if __SIZEOF_TIME32_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
#define __SIZEOF_TIMESPEC32         (__OFFSET_TIMESPEC32_NSEC + __SIZEOF_SYSCALL_LONG_T__ + 4)
#else /* __SIZEOF_TIME32_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#define __SIZEOF_TIMESPEC32         (__OFFSET_TIMESPEC32_NSEC + __SIZEOF_SYSCALL_LONG_T__)
#endif /* __SIZEOF_TIME32_T__ <= 4 || __SIZEOF_SYSCALL_LONG_T__ > 4 */

#define __OFFSET_TIMESPEC64_SEC     0
#if __SIZEOF_TIME64_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
#define __OFFSET_TIMESPEC64_NSEC    (__SIZEOF_TIME64_T__ + 4)
#else /* __SIZEOF_TIME64_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __OFFSET_TIMESPEC64_NSEC    __SIZEOF_TIME64_T__
#endif /* __SIZEOF_TIME64_T__ > 4 || __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#if __SIZEOF_TIME64_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
#define __SIZEOF_TIMESPEC64         (__OFFSET_TIMESPEC64_NSEC + __SIZEOF_SYSCALL_LONG_T__ + 4)
#else /* __SIZEOF_TIME64_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#define __SIZEOF_TIMESPEC64         (__OFFSET_TIMESPEC64_NSEC + __SIZEOF_SYSCALL_LONG_T__)
#endif /* __SIZEOF_TIME64_T__ <= 4 || __SIZEOF_SYSCALL_LONG_T__ > 4 */


#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("timespec")
#pragma push_macro("tv_sec")
#pragma push_macro("tv_nsec")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef timespec
#undef tv_sec
#undef tv_nsec

__TIMESPEC_CXX_DECL_BEGIN

struct timespec /*[PREFIX(tv_)]*/ {
	__time_t          tv_sec;   /* Seconds */
#if __SIZEOF_TIME_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
#define __TIMESPEC_HAVE_TV_PAD
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __SIZEOF_TIME_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4 */
#ifdef __USE_KOS_ALTERATIONS
	__syscall_ulong_t tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#else /* __USE_KOS_ALTERATIONS */
	__syscall_slong_t tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#endif /* !__USE_KOS_ALTERATIONS */
#if __SIZEOF_TIME_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
#define __TIMESPEC_HAVE_TV_PAD
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __SIZEOF_TIME_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4 */
	__TIMESPEC_CXX_SUPPORT(struct timespec, __time_t, __syscall_ulong_t)
};
__TIMESPEC_CXX_SUPPORT2(struct timespec, __time_t, __syscall_ulong_t)

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define _TIMESPEC_MATCHES_TIMESPEC64 1
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

#ifdef __USE_TIME64
#if (defined(__USE_TIME_BITS64) || defined(_TIMESPEC_MATCHES_TIMESPEC64)) && defined(__USE_STRUCT64_MACRO)
#define timespec64 timespec
#else /* (__USE_TIME_BITS64 || _TIMESPEC_MATCHES_TIMESPEC64) && __USE_STRUCT64_MACRO */
#define __timespec64 timespec64
#endif /* (!__USE_TIME_BITS64 && !_TIMESPEC_MATCHES_TIMESPEC64) || !__USE_STRUCT64_MACRO */
#endif /* __USE_TIME64 */

#if (defined(__USE_TIME_BITS64) || defined(_TIMESPEC_MATCHES_TIMESPEC64)) && defined(__USE_STRUCT64_MACRO)
#define __timespec64 timespec
#else /* (__USE_TIME_BITS64 || _TIMESPEC_MATCHES_TIMESPEC64) && __USE_STRUCT64_MACRO */
struct __timespec64 /*[NAME(timespec64)][PREFIX(tv_)]*/ {
	__time64_t        tv_sec;   /* Seconds */
#if __SIZEOF_TIME64_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
#define __TIMESPEC64_HAVE_TV_PAD
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __SIZEOF_TIME64_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4 */
#ifdef __USE_KOS_ALTERATIONS
	__syscall_ulong_t tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#else /* __USE_KOS_ALTERATIONS */
	__syscall_slong_t tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#endif /* !__USE_KOS_ALTERATIONS */
#if __SIZEOF_TIME64_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
#define __TIMESPEC64_HAVE_TV_PAD
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __SIZEOF_TIME64_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4 */
	__TIMESPEC_CXX_SUPPORT(struct __timespec64, __time64_t, __syscall_ulong_t)
};
__TIMESPEC_CXX_SUPPORT2(struct __timespec64, __time64_t, __syscall_ulong_t)
#endif /* (!__USE_TIME_BITS64 && !_TIMESPEC_MATCHES_TIMESPEC64) || !__USE_STRUCT64_MACRO */

#ifdef __USE_KOS
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define timespec32 timespec
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define __timespec32 timespec32
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */

#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#ifdef __TIMESPEC_HAVE_TV_PAD
#define __TIMESPEC32_HAVE_TV_PAD
#endif /* __TIMESPEC_HAVE_TV_PAD */
#define __timespec32 timespec
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __timespec32 /*[NAME(timespec32)][PREFIX(tv_)]*/ {
	__time32_t        tv_sec;   /* Seconds */
#if __SIZEOF_TIME32_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
#define __TIMESPEC32_HAVE_TV_PAD
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __SIZEOF_TIME32_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4 */
#ifdef __USE_KOS_ALTERATIONS
	__syscall_ulong_t tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#else /* __USE_KOS_ALTERATIONS */
	__syscall_slong_t tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#endif /* !__USE_KOS_ALTERATIONS */
#if __SIZEOF_TIME32_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
#define __TIMESPEC32_HAVE_TV_PAD
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __SIZEOF_TIME32_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4 */
	__TIMESPEC_CXX_SUPPORT(struct __timespec32, __time32_t, __syscall_ulong_t)
};
__TIMESPEC_CXX_SUPPORT2(struct __timespec32, __time32_t, __syscall_ulong_t)
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

__TIMESPEC_CXX_DECL_END

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("tv_nsec")
#pragma pop_macro("tv_sec")
#pragma pop_macro("timespec")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_OS_KOS_TIMESPEC_H */
