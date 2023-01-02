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
#ifndef _BITS_OS_KOS_RUSAGE_H
#define _BITS_OS_KOS_RUSAGE_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/os/timeval.h>
#include <bits/types.h>

#define __OFFSET_RUSAGE_UTIME    0
#define __OFFSET_RUSAGE_STIME    __SIZEOF_TIMEVAL
#define __OFFSET_RUSAGE_MAXRSS   (__SIZEOF_TIMEVAL * 2)
#define __OFFSET_RUSAGE_IXRSS    (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__)
#define __OFFSET_RUSAGE_IDRSS    (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__ * 2)
#define __OFFSET_RUSAGE_ISRSS    (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__ * 3)
#define __OFFSET_RUSAGE_MINFLT   (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__ * 4)
#define __OFFSET_RUSAGE_MAJFLT   (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__ * 5)
#define __OFFSET_RUSAGE_NSWAP    (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__ * 6)
#define __OFFSET_RUSAGE_INBLOCK  (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__ * 7)
#define __OFFSET_RUSAGE_OUBLOCK  (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__ * 8)
#define __OFFSET_RUSAGE_MSGSND   (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__ * 9)
#define __OFFSET_RUSAGE_MSGRCV   (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__ * 10)
#define __OFFSET_RUSAGE_NSIGNALS (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__ * 11)
#define __OFFSET_RUSAGE_NVCSW    (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__ * 12)
#define __OFFSET_RUSAGE_NIVCSW   (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__ * 13)
#define __SIZEOF_RUSAGE          (__SIZEOF_TIMEVAL * 2 + __SIZEOF_SYSCALL_LONG_T__ * 14)

#define __OFFSET_RUSAGE32_UTIME    0
#define __OFFSET_RUSAGE32_STIME    __SIZEOF_TIMEVAL32
#define __OFFSET_RUSAGE32_MAXRSS   (__SIZEOF_TIMEVAL32 * 2)
#define __OFFSET_RUSAGE32_IXRSS    (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__)
#define __OFFSET_RUSAGE32_IDRSS    (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 2)
#define __OFFSET_RUSAGE32_ISRSS    (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 3)
#define __OFFSET_RUSAGE32_MINFLT   (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 4)
#define __OFFSET_RUSAGE32_MAJFLT   (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 5)
#define __OFFSET_RUSAGE32_NSWAP    (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 6)
#define __OFFSET_RUSAGE32_INBLOCK  (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 7)
#define __OFFSET_RUSAGE32_OUBLOCK  (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 8)
#define __OFFSET_RUSAGE32_MSGSND   (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 9)
#define __OFFSET_RUSAGE32_MSGRCV   (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 10)
#define __OFFSET_RUSAGE32_NSIGNALS (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 11)
#define __OFFSET_RUSAGE32_NVCSW    (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 12)
#define __OFFSET_RUSAGE32_NIVCSW   (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 13)
#define __SIZEOF_RUSAGE32          (__SIZEOF_TIMEVAL32 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 14)

#define __OFFSET_RUSAGE64_UTIME    0
#define __OFFSET_RUSAGE64_STIME    __SIZEOF_TIMEVAL64
#define __OFFSET_RUSAGE64_MAXRSS   (__SIZEOF_TIMEVAL64 * 2)
#define __OFFSET_RUSAGE64_IXRSS    (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__)
#define __OFFSET_RUSAGE64_IDRSS    (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 2)
#define __OFFSET_RUSAGE64_ISRSS    (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 3)
#define __OFFSET_RUSAGE64_MINFLT   (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 4)
#define __OFFSET_RUSAGE64_MAJFLT   (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 5)
#define __OFFSET_RUSAGE64_NSWAP    (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 6)
#define __OFFSET_RUSAGE64_INBLOCK  (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 7)
#define __OFFSET_RUSAGE64_OUBLOCK  (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 8)
#define __OFFSET_RUSAGE64_MSGSND   (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 9)
#define __OFFSET_RUSAGE64_MSGRCV   (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 10)
#define __OFFSET_RUSAGE64_NSIGNALS (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 11)
#define __OFFSET_RUSAGE64_NVCSW    (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 12)
#define __OFFSET_RUSAGE64_NIVCSW   (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 13)
#define __SIZEOF_RUSAGE64          (__SIZEOF_TIMEVAL64 * 2 + __SIZEOF_SYSCALL_LONG_T__ * 14)

#ifdef __CC__
__DECL_BEGIN

struct rusage /*[PREFIX(ru_)]*/ {
	struct timeval ru_utime;  /* ??? */
	struct timeval ru_stime;  /* ??? */
#define __RU_MEMBER(x) __extension__ union { __LONGPTR_TYPE__ x; __syscall_slong_t __##x##_word; }
	__RU_MEMBER(ru_maxrss);   /* ??? */
	__RU_MEMBER(ru_ixrss);    /* ??? */
	__RU_MEMBER(ru_idrss);    /* ??? */
	__RU_MEMBER(ru_isrss);    /* ??? */
	__RU_MEMBER(ru_minflt);   /* ??? */
	__RU_MEMBER(ru_majflt);   /* ??? */
	__RU_MEMBER(ru_nswap);    /* ??? */
	__RU_MEMBER(ru_inblock);  /* ??? */
	__RU_MEMBER(ru_oublock);  /* ??? */
	__RU_MEMBER(ru_msgsnd);   /* ??? */
	__RU_MEMBER(ru_msgrcv);   /* ??? */
	__RU_MEMBER(ru_nsignals); /* ??? */
	__RU_MEMBER(ru_nvcsw);    /* ??? */
	__RU_MEMBER(ru_nivcsw);   /* ??? */
#undef __RU_MEMBER
};

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define _RUSAGE_MATCHES_RUSAGE64 1
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

#ifdef __USE_TIME64
#if (defined(__USE_TIME_BITS64) || defined(_RUSAGE_MATCHES_RUSAGE64)) && defined(__USE_STRUCT64_MACRO)
#define rusage64 rusage
#else /* (__USE_TIME_BITS64 || _RUSAGE_MATCHES_RUSAGE64) && __USE_STRUCT64_MACRO */
#define __rusage64 rusage64
#endif /* (!__USE_TIME_BITS64 && !_RUSAGE_MATCHES_RUSAGE64) || !__USE_STRUCT64_MACRO */
#endif /* __USE_TIME64 */

#if (defined(__USE_TIME_BITS64) || defined(_RUSAGE_MATCHES_RUSAGE64)) && defined(__USE_STRUCT64_MACRO)
#define __rusage64 rusage
#else /* (__USE_TIME_BITS64 || _RUSAGE_MATCHES_RUSAGE64) && __USE_STRUCT64_MACRO */
struct __rusage64 /*[NAME(rusage64)][PREFIX(ru_)]*/ {
	struct __timeval64 ru_utime; /* ??? */
	struct __timeval64 ru_stime; /* ??? */
#define __RU_MEMBER(x) __extension__ union { __LONGPTR_TYPE__ x; __syscall_slong_t __##x##_word; }
	__RU_MEMBER(ru_maxrss);   /* ??? */
	__RU_MEMBER(ru_ixrss);    /* ??? */
	__RU_MEMBER(ru_idrss);    /* ??? */
	__RU_MEMBER(ru_isrss);    /* ??? */
	__RU_MEMBER(ru_minflt);   /* ??? */
	__RU_MEMBER(ru_majflt);   /* ??? */
	__RU_MEMBER(ru_nswap);    /* ??? */
	__RU_MEMBER(ru_inblock);  /* ??? */
	__RU_MEMBER(ru_oublock);  /* ??? */
	__RU_MEMBER(ru_msgsnd);   /* ??? */
	__RU_MEMBER(ru_msgrcv);   /* ??? */
	__RU_MEMBER(ru_nsignals); /* ??? */
	__RU_MEMBER(ru_nvcsw);    /* ??? */
	__RU_MEMBER(ru_nivcsw);   /* ??? */
#undef __RU_MEMBER
};
#endif /* (!__USE_TIME_BITS64 && !_RUSAGE_MATCHES_RUSAGE64) || !__USE_STRUCT64_MACRO */

#ifdef __USE_KOS
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define rusage32 rusage
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define __rusage32 rusage32
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */

#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __rusage32 rusage
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __rusage32 /*[NAME(rusage32)][PREFIX(ru_)]*/ {
	struct __timeval32 ru_utime; /* ??? */
	struct __timeval32 ru_stime; /* ??? */
#define __RU_MEMBER(x) __extension__ union { __LONGPTR_TYPE__ x; __syscall_slong_t __##x##_word; }
	__RU_MEMBER(ru_maxrss);   /* ??? */
	__RU_MEMBER(ru_ixrss);    /* ??? */
	__RU_MEMBER(ru_idrss);    /* ??? */
	__RU_MEMBER(ru_isrss);    /* ??? */
	__RU_MEMBER(ru_minflt);   /* ??? */
	__RU_MEMBER(ru_majflt);   /* ??? */
	__RU_MEMBER(ru_nswap);    /* ??? */
	__RU_MEMBER(ru_inblock);  /* ??? */
	__RU_MEMBER(ru_oublock);  /* ??? */
	__RU_MEMBER(ru_msgsnd);   /* ??? */
	__RU_MEMBER(ru_msgrcv);   /* ??? */
	__RU_MEMBER(ru_nsignals); /* ??? */
	__RU_MEMBER(ru_nvcsw);    /* ??? */
	__RU_MEMBER(ru_nivcsw);   /* ??? */
#undef __RU_MEMBER
};
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_RUSAGE_H */
