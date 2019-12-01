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
#ifndef _BITS_TIMESPEC_H
#define _BITS_TIMESPEC_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/timespec-cxx-support.h>
#include <bits/types.h>

#define __OFFSET_TIMESPEC_SEC     0
#if __TM_SIZEOF(TIME) >= 8 || __SIZEOF_SYSCALL_LONG_T__ >= 8
#define __OFFSET_TIMESPEC_NSEC    8
#define __SIZEOF_TIMESPEC         16
#else /* __TM_SIZEOF(TIME) >= 8 || __SIZEOF_SYSCALL_LONG_T__ >= 8 */
#define __OFFSET_TIMESPEC_NSEC    4
#define __SIZEOF_TIMESPEC         8
#endif /* __TM_SIZEOF(TIME) < 8 && __SIZEOF_SYSCALL_LONG_T__ <8 */
#define __OFFSET_TIMESPEC64_SEC   0
#define __OFFSET_TIMESPEC64_NSEC  8
#define __SIZEOF_TIMESPEC64       16


#if 0
struct timespec /*[PREFIX(tv_)]*/ {};
struct timespec64 /*[PREFIX(tv_)]*/ {};
#endif


#ifdef __CC__
__SYSDECL_BEGIN
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("timespec")
#pragma push_macro("tv_sec")
#pragma push_macro("tv_nsec")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef timespec
#undef tv_sec
#undef tv_nsec

__TIMESPEC_CXX_DECL_BEGIN
struct timespec {
	__TM_TYPE(time)   tv_sec;   /* Seconds */
#if __TM_SIZEOF(TIME) <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __TM_SIZEOF(TIME) <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4 */
	__syscall_ulong_t tv_nsec;  /* Nano seconds (<= 1000000000 == 1_000_000_000) */
#if __TM_SIZEOF(TIME) > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif /* __TM_SIZEOF(TIME) > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4 */
	__TIMESPEC_CXX_SUPPORT(struct timespec, __TM_TYPE(time), __syscall_ulong_t)
};
__TIMESPEC_CXX_SUPPORT2(struct timespec, __TM_TYPE(time), __syscall_ulong_t)
__TIMESPEC_CXX_DECL_END


#if __TM_SIZEOF(TIME) <= 4
#define __timespec64  __timespec_alt
#define __timespec32  timespec
#else /* __TM_SIZEOF(TIME) <= 4 */
#define __timespec64  timespec
#define __timespec32  __timespec_alt
#endif /* __TM_SIZEOF(TIME) > 4 */

#ifdef __USE_TIME64
#if __TM_SIZEOF(TIME) <= 4
#define __timespec_alt timespec64
#else /* __TM_SIZEOF(TIME) <= 4 */
#define timespec64     timespec
#endif /* __TM_SIZEOF(TIME) > 4 */
#endif /* __USE_TIME64 */

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#if defined(__USE_TIME64) && __TM_SIZEOF(TIME) <= 4
#define timespec64     timespec
#else /* __USE_TIME64 && __TM_SIZEOF(TIME) <= 4 */
#define __timespec_alt timespec
#endif /* !__USE_TIME64 || __TM_SIZEOF(TIME) > 4 */
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
__TIMESPEC_CXX_DECL_BEGIN
struct __timespec_alt
/*Keep an empty line here*/
{
#if __TM_SIZEOF(TIME) <= 4
	__time64_t        tv_sec;   /* Seconds */
#else /* __TM_SIZEOF(TIME) <= 4 */
	__time32_t        tv_sec;   /* Seconds */
#if __SIZEOF_SYSCALL_LONG_T__ > 4
	__UINT32_TYPE__ __tv_pad;   /* ... */
#endif /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#endif /* __TM_SIZEOF(TIME) > 4 */
	__syscall_ulong_t tv_nsec;  /* Nano seconds (<= 1000000000 == 1_000_000_000) */
#if __SIZEOF_SYSCALL_LONG_T__ <= 4 && __TM_SIZEOF(TIME) <= 4
	__UINT32_TYPE__ __tv_pad;   /* ... */
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 && __TM_SIZEOF(TIME) <= 4 */
#if __TM_SIZEOF(TIME) <= 4
	__TIMESPEC_CXX_SUPPORT(struct __timespec_alt, __time64_t, __syscall_ulong_t)
#else /* __TM_SIZEOF(TIME) <= 4 */
	__TIMESPEC_CXX_SUPPORT(struct __timespec_alt, __time32_t, __syscall_ulong_t)
#endif /* __TM_SIZEOF(TIME) > 4 */
};
#if __TM_SIZEOF(TIME) <= 4
__TIMESPEC_CXX_SUPPORT2(struct __timespec_alt, __time64_t, __syscall_ulong_t)
#else /* __TM_SIZEOF(TIME) <= 4 */
__TIMESPEC_CXX_SUPPORT2(struct __timespec_alt, __time32_t, __syscall_ulong_t)
#endif /* __TM_SIZEOF(TIME) > 4 */
__TIMESPEC_CXX_DECL_END
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("tv_nsec")
#pragma pop_macro("tv_sec")
#pragma pop_macro("timespec")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_BITS_TIMESPEC_H */
