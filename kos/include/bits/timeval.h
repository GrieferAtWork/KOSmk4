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
#ifndef _BITS_TIMEVAL_H
#define _BITS_TIMEVAL_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/timeval-cxx-support.h>
#include <bits/types.h>

#define __OFFSET_TIMEVAL_SEC     0
#if __TM_SIZEOF(TIME) <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
#define __OFFSET_TIMEVAL_USEC    (__TM_SIZEOF(TIME) + 4)
#else /* __TM_SIZEOF(TIME) <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __OFFSET_TIMEVAL_USEC    __TM_SIZEOF(TIME)
#endif /* __TM_SIZEOF(TIME) > 4 || __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#if __TM_SIZEOF(TIME) > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
#define __SIZEOF_TIMEVAL         (__OFFSET_TIMEVAL_USEC + __SIZEOF_SYSCALL_LONG_T__ + 4)
#else /* __TM_SIZEOF(TIME) > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#define __SIZEOF_TIMEVAL         (__OFFSET_TIMEVAL_USEC + __SIZEOF_SYSCALL_LONG_T__)
#endif /* __TM_SIZEOF(TIME) <= 4 || __SIZEOF_SYSCALL_LONG_T__ > 4 */

#define __OFFSET_TIMEVAL32_SEC     0
#if __SIZEOF_TIME32_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
#define __OFFSET_TIMEVAL32_USEC    (__SIZEOF_TIME32_T__ + 4)
#else /* __SIZEOF_TIME32_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __OFFSET_TIMEVAL32_USEC    __SIZEOF_TIME32_T__
#endif /* __SIZEOF_TIME32_T__ > 4 || __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#if __SIZEOF_TIME32_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
#define __SIZEOF_TIMEVAL32         (__OFFSET_TIMEVAL32_USEC + __SIZEOF_SYSCALL_LONG_T__ + 4)
#else /* __SIZEOF_TIME32_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#define __SIZEOF_TIMEVAL32         (__OFFSET_TIMEVAL32_USEC + __SIZEOF_SYSCALL_LONG_T__)
#endif /* __SIZEOF_TIME32_T__ <= 4 || __SIZEOF_SYSCALL_LONG_T__ > 4 */

#define __OFFSET_TIMEVAL64_SEC     0
#if __SIZEOF_TIME64_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
#define __OFFSET_TIMEVAL64_USEC    (__SIZEOF_TIME64_T__ + 4)
#else /* __SIZEOF_TIME64_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __OFFSET_TIMEVAL64_USEC    __SIZEOF_TIME64_T__
#endif /* __SIZEOF_TIME64_T__ > 4 || __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#if __SIZEOF_TIME64_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
#define __SIZEOF_TIMEVAL64         (__OFFSET_TIMEVAL64_USEC + __SIZEOF_SYSCALL_LONG_T__ + 4)
#else /* __SIZEOF_TIME64_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#define __SIZEOF_TIMEVAL64         (__OFFSET_TIMEVAL64_USEC + __SIZEOF_SYSCALL_LONG_T__)
#endif /* __SIZEOF_TIME64_T__ <= 4 || __SIZEOF_SYSCALL_LONG_T__ > 4 */


#ifdef __CC__
__SYSDECL_BEGIN
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("timeval")
#pragma push_macro("tv_sec")
#pragma push_macro("tv_usec")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef timeval
#undef tv_sec
#undef tv_usec

__TIMEVAL_CXX_DECL_BEGIN

#ifndef __timeval_defined
#define __timeval_defined 1
struct timeval /*[PREFIX(tv_)]*/ {
	__TM_TYPE(time)   tv_sec;   /* Seconds */
#if __TM_SIZEOF(TIME) <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __TM_SIZEOF(TIME) <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4 */
	__syscall_ulong_t tv_usec;  /* Micro seconds (<= 1000000 == 1_000_000) */
#if __TM_SIZEOF(TIME) > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __TM_SIZEOF(TIME) > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4 */
	__TIMEVAL_CXX_SUPPORT(struct timeval, __TM_TYPE(time), __syscall_ulong_t)
};
__TIMEVAL_CXX_SUPPORT2(struct timeval, __TM_TYPE(time), __syscall_ulong_t)
#endif /* !__timeval_defined */

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define _TIMEVAL_MATCHES_TIMEVAL64 1
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

#ifdef __USE_TIME64
#ifndef __timeval64_defined
#define __timeval64_defined 1
#if (defined(__USE_TIME_BITS64) || defined(_TIMEVAL_MATCHES_TIMEVAL64)) && defined(__USE_STRUCT64_MACRO)
#define timeval64 timeval
#else /* (__USE_TIME_BITS64 || _TIMEVAL_MATCHES_TIMEVAL64) && __USE_STRUCT64_MACRO */
#define __timeval64 timeval64
#endif /* (!__USE_TIME_BITS64 && !_TIMEVAL_MATCHES_TIMEVAL64) || !__USE_STRUCT64_MACRO */
#endif /* !__timeval64_defined */
#endif /* __USE_TIME64 */

#if (defined(__USE_TIME_BITS64) || defined(_TIMEVAL_MATCHES_TIMEVAL64)) && defined(__USE_STRUCT64_MACRO)
#define __timeval64 timeval
#else /* (__USE_TIME_BITS64 || _TIMEVAL_MATCHES_TIMEVAL64) && __USE_STRUCT64_MACRO */
struct __timeval64 /*[NAME(timeval64)][PREFIX(tv_)]*/ {
	__time64_t        tv_sec;   /* Seconds */
#if __SIZEOF_TIME64_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __SIZEOF_TIME64_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4 */
	__syscall_ulong_t tv_usec;  /* Micro seconds (<= 1000000 == 1_000_000) */
#if __SIZEOF_TIME64_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __SIZEOF_TIME64_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4 */
	__TIMEVAL_CXX_SUPPORT(struct __timeval64, __time64_t, __syscall_ulong_t)
};
__TIMEVAL_CXX_SUPPORT2(struct __timeval64, __time64_t, __syscall_ulong_t)
#endif /* (!__USE_TIME_BITS64 && !_TIMEVAL_MATCHES_TIMEVAL64) || !__USE_STRUCT64_MACRO */

#ifdef __USE_KOS
#ifndef __timeval32_defined
#define __timeval32_defined 1
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define timeval32 timeval
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define __timeval32 timeval32
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__timeval32_defined */
#endif /* __USE_KOS */

#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __timeval32 timeval
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __timeval32 /*[NAME(timeval32)][PREFIX(tv_)]*/ {
	__time32_t        tv_sec;   /* Seconds */
#if __SIZEOF_TIME32_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __SIZEOF_TIME32_T__ <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4 */
	__syscall_ulong_t tv_usec;  /* Micro seconds (<= 1000000 == 1_000_000) */
#if __SIZEOF_TIME32_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __SIZEOF_TIME32_T__ > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4 */
	__TIMEVAL_CXX_SUPPORT(struct __timeval32, __time32_t, __syscall_ulong_t)
};
__TIMEVAL_CXX_SUPPORT2(struct __timeval32, __time32_t, __syscall_ulong_t)
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

__TIMEVAL_CXX_DECL_END

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("tv_usec")
#pragma pop_macro("tv_sec")
#pragma pop_macro("timeval")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_BITS_TIMEVAL_H */
