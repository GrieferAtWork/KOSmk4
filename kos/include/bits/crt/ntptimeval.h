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
#ifndef _BITS_CRT_NTPTIMEVAL_H
#define _BITS_CRT_NTPTIMEVAL_H 1

/* File:
 *    <bits/crt/ntptimeval.h>
 *
 * Definitions:
 *    struct ntptimeval {
 *        ...
 *    };
 *    #ifdef   __USE_TIME64
 *    struct ntptimeval64 {
 *        ...
 *    };
 *    #endif // __USE_TIME64
 */

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/timeval.h>
#include <bits/types.h>

#define __OFFSET_NTPTIMEVAL_TIME       0
#define __OFFSET_NTPTIMEVAL_MAXERROR   __SIZEOF_TIMEVAL
#define __OFFSET_NTPTIMEVAL_ESTERROR   (__SIZEOF_TIMEVAL + __SIZEOF_POINTER__)
#define __OFFSET_NTPTIMEVAL_TAI        (__SIZEOF_TIMEVAL + __SIZEOF_POINTER__ * 2)
#define __SIZEOF_NTPTIMEVAL            ((__SIZEOF_TIMEVAL + __SIZEOF_POINTER__ * 7 + (__ALIGNOF_TIMEVAL - 1)) & ~(__ALIGNOF_TIMEVAL - 1))
#define __ALIGNOF_NTPTIMEVAL           __ALIGNOF_TIMEVAL
#define __OFFSET_NTPTIMEVAL32_TIME     0
#define __OFFSET_NTPTIMEVAL32_MAXERROR __SIZEOF_TIMEVAL32
#define __OFFSET_NTPTIMEVAL32_ESTERROR (__SIZEOF_TIMEVAL32 + __SIZEOF_POINTER__)
#define __OFFSET_NTPTIMEVAL32_TAI      (__SIZEOF_TIMEVAL32 + __SIZEOF_POINTER__ * 2)
#define __SIZEOF_NTPTIMEVAL32          ((__SIZEOF_TIMEVAL32 + __SIZEOF_POINTER__ * 7 + (__ALIGNOF_TIMEVAL32 - 1)) & ~(__ALIGNOF_TIMEVAL32 - 1))
#define __ALIGNOF_NTPTIMEVAL32         __ALIGNOF_TIMEVAL32
#define __OFFSET_NTPTIMEVAL64_TIME     0
#define __OFFSET_NTPTIMEVAL64_MAXERROR __SIZEOF_TIMEVAL64
#define __OFFSET_NTPTIMEVAL64_ESTERROR (__SIZEOF_TIMEVAL64 + __SIZEOF_POINTER__)
#define __OFFSET_NTPTIMEVAL64_TAI      (__SIZEOF_TIMEVAL64 + __SIZEOF_POINTER__ * 2)
#define __SIZEOF_NTPTIMEVAL64          ((__SIZEOF_TIMEVAL64 + __SIZEOF_POINTER__ * 7 + (__ALIGNOF_TIMEVAL64 - 1)) & ~(__ALIGNOF_TIMEVAL64 - 1))
#define __ALIGNOF_NTPTIMEVAL64         __ALIGNOF_TIMEVAL64

#ifdef __CC__
__SYSDECL_BEGIN
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

struct ntptimeval /*[PREFIX()]*/ {
	struct timeval       time;            /* ??? */
	__LONGPTR_TYPE__     maxerror;        /* ??? */
	__LONGPTR_TYPE__     esterror;        /* ??? */
	__LONGPTR_TYPE__     tai;             /* ??? */
	__LONGPTR_TYPE__   __glibc_reserved1; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved2; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved3; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved4; /* ... */
};

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define _NTPTIMEVAL_MATCHES_NTPTIMEVAL64 1
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

#ifdef __USE_TIME64
#if (defined(__USE_TIME_BITS64) || defined(_NTPTIMEVAL_MATCHES_NTPTIMEVAL64)) && defined(__USE_STRUCT64_MACRO)
#define ntptimeval64 ntptimeval
#else /* (__USE_TIME_BITS64 || _NTPTIMEVAL_MATCHES_NTPTIMEVAL64) && __USE_STRUCT64_MACRO */
#define __ntptimeval64 ntptimeval64
#endif /* (!__USE_TIME_BITS64 && !_NTPTIMEVAL_MATCHES_NTPTIMEVAL64) || !__USE_STRUCT64_MACRO */
#endif /* __USE_TIME64 */

#if (defined(__USE_TIME_BITS64) || defined(_NTPTIMEVAL_MATCHES_NTPTIMEVAL64)) && defined(__USE_STRUCT64_MACRO)
#define __ntptimeval64 ntptimeval
#else /* (__USE_TIME_BITS64 || _NTPTIMEVAL_MATCHES_NTPTIMEVAL64) && __USE_STRUCT64_MACRO */
struct __ntptimeval64 /*[NAME(ntptimeval64)][PREFIX()]*/ {
	struct __timeval64   time;            /* ??? */
	__LONGPTR_TYPE__     maxerror;        /* ??? */
	__LONGPTR_TYPE__     esterror;        /* ??? */
	__LONGPTR_TYPE__     tai;             /* ??? */
	__LONGPTR_TYPE__   __glibc_reserved1; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved2; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved3; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved4; /* ... */
};
#endif /* (!__USE_TIME_BITS64 && !_NTPTIMEVAL_MATCHES_NTPTIMEVAL64) || !__USE_STRUCT64_MACRO */

#ifdef __USE_KOS
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define ntptimeval32 ntptimeval
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define __ntptimeval32 ntptimeval32
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */

#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __ntptimeval32 ntptimeval
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __ntptimeval32 /*[NAME(ntptimeval32)][PREFIX()]*/ {
	struct __timeval32   time;            /* ??? */
	__LONGPTR_TYPE__     maxerror;        /* ??? */
	__LONGPTR_TYPE__     esterror;        /* ??? */
	__LONGPTR_TYPE__     tai;             /* ??? */
	__LONGPTR_TYPE__   __glibc_reserved1; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved2; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved3; /* ... */
	__LONGPTR_TYPE__   __glibc_reserved4; /* ... */
};
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("tai")
#pragma pop_macro("esterror")
#pragma pop_macro("maxerror")
#pragma pop_macro("time")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_NTPTIMEVAL_H */
