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
#ifndef _BITS_TIMEVAL_H
#define _BITS_TIMEVAL_H 1

#include <__stdinc.h>
#include <features.h>
#include <bits/types.h>
#include <bits/timeval-cxx-support.h>
#include <hybrid/typecore.h>

#define __OFFSET_TIMEVAL_SEC     0
#if __TM_SIZEOF(TIME) >= 8 || __SIZEOF_SYSCALL_LONG_T__ >= 8
#define __OFFSET_TIMEVAL_USEC    8
#define __SIZEOF_TIMEVAL         16
#else
#define __OFFSET_TIMEVAL_USEC    4
#define __SIZEOF_TIMEVAL         8
#endif
#define __OFFSET_TIMEVAL64_SEC   0
#define __OFFSET_TIMEVAL64_USEC  8
#define __SIZEOF_TIMEVAL64       16


#if 0
struct timeval /*[PREFIX(tv_)]*/ {};
struct timeval64 /*[PREFIX(tv_)]*/ {};
#endif


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
struct timeval {
	__TM_TYPE(time)   tv_sec;   /* Seconds */
#if __TM_SIZEOF(TIME) <= 4 && __SIZEOF_SYSCALL_LONG_T__ > 4
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif
	__syscall_ulong_t tv_usec;  /* Micro seconds (<= 1000000 == 1_000_000) */
#if __TM_SIZEOF(TIME) > 4 && __SIZEOF_SYSCALL_LONG_T__ <= 4
	__UINT32_TYPE__ __tv_pad; /* ... */
#endif
	__TIMEVAL_CXX_SUPPORT(struct timeval, __TM_TYPE(time), __syscall_ulong_t)
};
__TIMEVAL_CXX_SUPPORT2(struct timeval, __TM_TYPE(time), __syscall_ulong_t)
__TIMEVAL_CXX_DECL_END


#if __TM_SIZEOF(TIME) <= 4
#define __timeval64  __timeval_alt
#define __timeval32  timeval
#else
#define __timeval64  timeval
#define __timeval32  __timeval_alt
#endif

#ifdef __USE_TIME64
#if __TM_SIZEOF(TIME) <= 4
#define __timeval_alt timeval64
#else
#define timeval64     timeval
#endif
#endif /* __USE_TIME64 */

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#if defined(__USE_TIME64) && __TM_SIZEOF(TIME) <= 4
#define timeval64     timeval
#else
#define __timeval_alt timeval
#endif
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
__TIMEVAL_CXX_DECL_BEGIN
struct __timeval_alt
/*Keep an empty line here*/
{
#if __TM_SIZEOF(TIME) <= 4
	__time64_t        tv_sec;   /* Seconds */
#else
	__time32_t        tv_sec;   /* Seconds */
#if __SIZEOF_SYSCALL_LONG_T__ > 4
	__UINT32_TYPE__ __tv_pad;   /* ... */
#endif
#endif
	__syscall_ulong_t tv_usec;  /* Micro seconds (<= 1000000 == 1_000_000) */
#if __SIZEOF_SYSCALL_LONG_T__ <= 4 && __TM_SIZEOF(TIME) <= 4
	__UINT32_TYPE__ __tv_pad;   /* ... */
#endif
#if __TM_SIZEOF(TIME) <= 4
	__TIMEVAL_CXX_SUPPORT(struct __timeval_alt, __time64_t, __syscall_ulong_t)
#else
	__TIMEVAL_CXX_SUPPORT(struct __timeval_alt, __time32_t, __syscall_ulong_t)
#endif
};
#if __TM_SIZEOF(TIME) <= 4
__TIMEVAL_CXX_SUPPORT2(struct __timeval_alt, __time64_t, __syscall_ulong_t)
#else
__TIMEVAL_CXX_SUPPORT2(struct __timeval_alt, __time32_t, __syscall_ulong_t)
#endif
__TIMEVAL_CXX_DECL_END
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("tv_usec")
#pragma pop_macro("tv_sec")
#pragma pop_macro("timeval")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_BITS_TIMEVAL_H */
