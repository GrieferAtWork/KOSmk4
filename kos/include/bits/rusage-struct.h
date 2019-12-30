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

#ifdef __CC__

/* TODO: `struct rusage64' (based on __USE_TIME_BITS64) */
//#if 0 /* For assert_types.c */
//struct rusage /*[PREFIX(ru_)]*/ {};
//struct rusage32 /*[PREFIX(ru_)]*/ {};
//struct rusage64 /*[PREFIX(ru_)]*/ {};
//#endif

#ifndef __rusage_defined
#define __rusage_defined 1
struct rusage {
	struct timeval ru_utime;  /* Total amount of user time used. */
	struct timeval ru_stime;  /* Total amount of system time used. */
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

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BITS_RUSAGE_STRUCT_H */
