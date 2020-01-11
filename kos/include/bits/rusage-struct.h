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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_RUSAGE_STRUCT_H
#define _BITS_RUSAGE_STRUCT_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/timeval.h>
#include <bits/types.h>

__SYSDECL_BEGIN

/* Documentation taken from GLibc /usr/include/i386-linux-gnu/bits/resource.h */
/* Bit values & structures for resource limits.  Linux version.
   Copyright (C) 1994-2016 Free Software Foundation, Inc.
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

#ifndef __rusage_defined
#define __rusage_defined 1
struct rusage /*[PREFIX(ru_)]*/ {
	struct timeval ru_utime; /* Total amount of user time used. */
	struct timeval ru_stime; /* Total amount of system time used. */
#define __RU_MEMBER(x) __extension__ union { __LONGPTR_TYPE__ x; __syscall_slong_t __##x##_word; }
	__RU_MEMBER(ru_maxrss);   /* Maximum resident set size (in kilobytes). */
	/* Amount of sharing of text segment memory with other processes (kilobyte-seconds). */
	__RU_MEMBER(ru_ixrss);    /* Maximum resident set size (in kilobytes). */
	__RU_MEMBER(ru_idrss);    /* Amount of data segment memory used (kilobyte-seconds). */
	__RU_MEMBER(ru_isrss);    /* Amount of stack memory used (kilobyte-seconds). */
	__RU_MEMBER(ru_minflt);   /* Number of soft page faults (i.e. those serviced by reclaiming a page from the list of pages awaiting reallocation. */
	__RU_MEMBER(ru_majflt);   /* Number of hard page faults (i.e. those that required I/O). */
	__RU_MEMBER(ru_nswap);    /* Number of times a process was swapped out of physical memory. */
	__RU_MEMBER(ru_inblock);  /* Number of input operations via the file system.
	                           * NOTE: This and `ru_oublock' do not include operations with the cache. */
	__RU_MEMBER(ru_oublock);  /* Number of output operations via the file system. */
	__RU_MEMBER(ru_msgsnd);   /* Number of IPC messages sent. */
	__RU_MEMBER(ru_msgrcv);   /* Number of IPC messages received. */
	__RU_MEMBER(ru_nsignals); /* Number of signals delivered. */
	__RU_MEMBER(ru_nvcsw);    /* Number of voluntary context switches, i.e. because the process gave up the
	                           * process before it had to (usually to wait for some resource to be available). */
	__RU_MEMBER(ru_nivcsw);   /* Number of involuntary context switches, i.e. a higher priority process
	                           * became runnable or the current process used up its time slice. */
#undef __RU_MEMBER
};
#endif /* !__rusage_defined */

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define _RUSAGE_MATCHES_RUSAGE64 1
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

#ifdef __USE_TIME64
#ifndef __rusage64_defined
#define __rusage64_defined 1
#if (defined(__USE_TIME_BITS64) || defined(_RUSAGE_MATCHES_RUSAGE64)) && defined(__USE_STRUCT64_MACRO)
#define rusage64 rusage
#else /* (__USE_TIME_BITS64 || _RUSAGE_MATCHES_RUSAGE64) && __USE_STRUCT64_MACRO */
#define __rusage64 rusage64
#endif /* (!__USE_TIME_BITS64 && !_RUSAGE_MATCHES_RUSAGE64) || !__USE_STRUCT64_MACRO */
#endif /* !__rusage64_defined */
#endif /* __USE_TIME64 */

#if (defined(__USE_TIME_BITS64) || defined(_RUSAGE_MATCHES_RUSAGE64)) && defined(__USE_STRUCT64_MACRO)
#define __rusage64 rusage
#else /* (__USE_TIME_BITS64 || _RUSAGE_MATCHES_RUSAGE64) && __USE_STRUCT64_MACRO */
struct __rusage64 /*[NAME(rusage64)][PREFIX(ru_)]*/ {
	struct __timeval64 ru_utime;  /* Total amount of user time used. */
	struct __timeval64 ru_stime;  /* Total amount of system time used. */
#define __RU_MEMBER(x) __extension__ union { __LONGPTR_TYPE__ x; __syscall_slong_t __##x##_word; }
	__RU_MEMBER(ru_maxrss);   /* Maximum resident set size (in kilobytes). */
	/* Amount of sharing of text segment memory with other processes (kilobyte-seconds). */
	__RU_MEMBER(ru_ixrss);    /* Maximum resident set size (in kilobytes). */
	__RU_MEMBER(ru_idrss);    /* Amount of data segment memory used (kilobyte-seconds). */
	__RU_MEMBER(ru_isrss);    /* Amount of stack memory used (kilobyte-seconds). */
	__RU_MEMBER(ru_minflt);   /* Number of soft page faults (i.e. those serviced by reclaiming a page from the list of pages awaiting reallocation. */
	__RU_MEMBER(ru_majflt);   /* Number of hard page faults (i.e. those that required I/O). */
	__RU_MEMBER(ru_nswap);    /* Number of times a process was swapped out of physical memory. */
	__RU_MEMBER(ru_inblock);  /* Number of input operations via the file system.
	                           * NOTE: This and `ru_oublock' do not include operations with the cache. */
	__RU_MEMBER(ru_oublock);  /* Number of output operations via the file system. */
	__RU_MEMBER(ru_msgsnd);   /* Number of IPC messages sent. */
	__RU_MEMBER(ru_msgrcv);   /* Number of IPC messages received. */
	__RU_MEMBER(ru_nsignals); /* Number of signals delivered. */
	__RU_MEMBER(ru_nvcsw);    /* Number of voluntary context switches, i.e. because the process gave up the
	                           * process before it had to (usually to wait for some resource to be available). */
	__RU_MEMBER(ru_nivcsw);   /* Number of involuntary context switches, i.e. a higher priority process
	                           * became runnable or the current process used up its time slice. */
#undef __RU_MEMBER
};
#endif /* (!__USE_TIME_BITS64 && !_RUSAGE_MATCHES_RUSAGE64) || !__USE_STRUCT64_MACRO */

#ifdef __USE_KOS
#ifndef __rusage32_defined
#define __rusage32_defined 1
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define rusage32 rusage
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define __rusage32 rusage32
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__rusage32_defined */
#endif /* __USE_KOS */

#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __rusage32 rusage
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __rusage32 /*[NAME(rusage32)][PREFIX(ru_)]*/ {
	struct timeval32 ru_utime;  /* Total amount of user time used. */
	struct timeval32 ru_stime;  /* Total amount of system time used. */
#define __RU_MEMBER(x) __extension__ union { __LONGPTR_TYPE__ x; __syscall_slong_t __##x##_word; }
	__RU_MEMBER(ru_maxrss);   /* Maximum resident set size (in kilobytes). */
	/* Amount of sharing of text segment memory with other processes (kilobyte-seconds). */
	__RU_MEMBER(ru_ixrss);    /* Maximum resident set size (in kilobytes). */
	__RU_MEMBER(ru_idrss);    /* Amount of data segment memory used (kilobyte-seconds). */
	__RU_MEMBER(ru_isrss);    /* Amount of stack memory used (kilobyte-seconds). */
	__RU_MEMBER(ru_minflt);   /* Number of soft page faults (i.e. those serviced by reclaiming a page from the list of pages awaiting reallocation. */
	__RU_MEMBER(ru_majflt);   /* Number of hard page faults (i.e. those that required I/O). */
	__RU_MEMBER(ru_nswap);    /* Number of times a process was swapped out of physical memory. */
	__RU_MEMBER(ru_inblock);  /* Number of input operations via the file system.
	                           * NOTE: This and `ru_oublock' do not include operations with the cache. */
	__RU_MEMBER(ru_oublock);  /* Number of output operations via the file system. */
	__RU_MEMBER(ru_msgsnd);   /* Number of IPC messages sent. */
	__RU_MEMBER(ru_msgrcv);   /* Number of IPC messages received. */
	__RU_MEMBER(ru_nsignals); /* Number of signals delivered. */
	__RU_MEMBER(ru_nvcsw);    /* Number of voluntary context switches, i.e. because the process gave up the
	                           * process before it had to (usually to wait for some resource to be available). */
	__RU_MEMBER(ru_nivcsw);   /* Number of involuntary context switches, i.e. a higher priority process
	                           * became runnable or the current process used up its time slice. */
#undef __RU_MEMBER
};
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BITS_RUSAGE_STRUCT_H */
