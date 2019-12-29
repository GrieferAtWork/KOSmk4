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
#ifndef _I386_KOS_BITS_RUSAGE_STRUCT32_H
#define _I386_KOS_BITS_RUSAGE_STRUCT32_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/timeval32.h>

#ifdef __x86_64__
#define rusagex32    __rusagex32
#define rusagex32_64 __rusagex32_64
#else /* __x86_64__ */
#include <features.h>
#ifdef __USE_TIME_BITS64
/* Configure:
 *   - `rusagex32_64' as `rusage'
 *   - `rusagex32' as `__rusage32' */

#define rusagex32      __rusage32
#define rusagex32_64   rusage
#define __rusagex32    __rusage32
#define __rusagex32_64 rusage
#define __rusage32     __rusage32
#define __rusage64     rusage
#define __rusage_alt   __rusage32
#ifdef __USE_KOS
#define rusage32       __rusage32
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#define rusage64       rusage
#endif /* __USE_TIME64 */

#define __OFFSET_RUSAGE_UTIME      __OFFSET_RUSAGEX32_64_UTIME
#define __OFFSET_RUSAGE_STIME      __OFFSET_RUSAGEX32_64_STIME
#define __OFFSET_RUSAGE_MAXRSS     __OFFSET_RUSAGEX32_64_MAXRSS
#define __OFFSET_RUSAGE_IXRSS      __OFFSET_RUSAGEX32_64_IXRSS
#define __OFFSET_RUSAGE_IDRSS      __OFFSET_RUSAGEX32_64_IDRSS
#define __OFFSET_RUSAGE_ISRSS      __OFFSET_RUSAGEX32_64_ISRSS
#define __OFFSET_RUSAGE_MINFLT     __OFFSET_RUSAGEX32_64_MINFLT
#define __OFFSET_RUSAGE_MAJFLT     __OFFSET_RUSAGEX32_64_MAJFLT
#define __OFFSET_RUSAGE_NSWAP      __OFFSET_RUSAGEX32_64_NSWAP
#define __OFFSET_RUSAGE_INBLOCK    __OFFSET_RUSAGEX32_64_INBLOCK
#define __OFFSET_RUSAGE_OUBLOCK    __OFFSET_RUSAGEX32_64_OUBLOCK
#define __OFFSET_RUSAGE_MSGSND     __OFFSET_RUSAGEX32_64_MSGSND
#define __OFFSET_RUSAGE_MSGRCV     __OFFSET_RUSAGEX32_64_MSGRCV
#define __OFFSET_RUSAGE_NSIGNALS   __OFFSET_RUSAGEX32_64_NSIGNALS
#define __OFFSET_RUSAGE_NVCSW      __OFFSET_RUSAGEX32_64_NVCSW
#define __OFFSET_RUSAGE_NIVCSW     __OFFSET_RUSAGEX32_64_NIVCSW
#define __SIZEOF_RUSAGE            __SIZEOF_RUSAGEX32_64
#define __OFFSET_RUSAGE64_UTIME    __OFFSET_RUSAGEX32_64_UTIME
#define __OFFSET_RUSAGE64_STIME    __OFFSET_RUSAGEX32_64_STIME
#define __OFFSET_RUSAGE64_MAXRSS   __OFFSET_RUSAGEX32_64_MAXRSS
#define __OFFSET_RUSAGE64_IXRSS    __OFFSET_RUSAGEX32_64_IXRSS
#define __OFFSET_RUSAGE64_IDRSS    __OFFSET_RUSAGEX32_64_IDRSS
#define __OFFSET_RUSAGE64_ISRSS    __OFFSET_RUSAGEX32_64_ISRSS
#define __OFFSET_RUSAGE64_MINFLT   __OFFSET_RUSAGEX32_64_MINFLT
#define __OFFSET_RUSAGE64_MAJFLT   __OFFSET_RUSAGEX32_64_MAJFLT
#define __OFFSET_RUSAGE64_NSWAP    __OFFSET_RUSAGEX32_64_NSWAP
#define __OFFSET_RUSAGE64_INBLOCK  __OFFSET_RUSAGEX32_64_INBLOCK
#define __OFFSET_RUSAGE64_OUBLOCK  __OFFSET_RUSAGEX32_64_OUBLOCK
#define __OFFSET_RUSAGE64_MSGSND   __OFFSET_RUSAGEX32_64_MSGSND
#define __OFFSET_RUSAGE64_MSGRCV   __OFFSET_RUSAGEX32_64_MSGRCV
#define __OFFSET_RUSAGE64_NSIGNALS __OFFSET_RUSAGEX32_64_NSIGNALS
#define __OFFSET_RUSAGE64_NVCSW    __OFFSET_RUSAGEX32_64_NVCSW
#define __OFFSET_RUSAGE64_NIVCSW   __OFFSET_RUSAGEX32_64_NIVCSW
#define __SIZEOF_RUSAGE64          __SIZEOF_RUSAGEX32_64

#else /* __USE_TIME_BITS64 */
/* Configure:
 *   - `rusagex32_64' as `rusage64' or `__rusage64'
 *   - `rusagex32' as `rusage' */
#define rusagex32      rusage
#define __rusage32     rusage
#define __rusagex32    rusage
#ifdef __USE_TIME64
#define __rusagex32_64 rusage64
#define rusagex32_64   rusage64
#define __rusage64     rusage64
#define __rusage_alt   rusage64
#else /* __USE_TIME64 */
#define __rusagex32_64 __rusage64
#define rusagex32_64   __rusage64
#define __rusage64     __rusage64
#define __rusage_alt   __rusage64
#endif /* __USE_TIME64 */
#ifdef __USE_KOS
#define rusage32       rusage
#endif /* __USE_KOS */

#define __OFFSET_RUSAGE_UTIME      __OFFSET_RUSAGEX32_UTIME
#define __OFFSET_RUSAGE_STIME      __OFFSET_RUSAGEX32_STIME
#define __OFFSET_RUSAGE_MAXRSS     __OFFSET_RUSAGEX32_MAXRSS
#define __OFFSET_RUSAGE_IXRSS      __OFFSET_RUSAGEX32_IXRSS
#define __OFFSET_RUSAGE_IDRSS      __OFFSET_RUSAGEX32_IDRSS
#define __OFFSET_RUSAGE_ISRSS      __OFFSET_RUSAGEX32_ISRSS
#define __OFFSET_RUSAGE_MINFLT     __OFFSET_RUSAGEX32_MINFLT
#define __OFFSET_RUSAGE_MAJFLT     __OFFSET_RUSAGEX32_MAJFLT
#define __OFFSET_RUSAGE_NSWAP      __OFFSET_RUSAGEX32_NSWAP
#define __OFFSET_RUSAGE_INBLOCK    __OFFSET_RUSAGEX32_INBLOCK
#define __OFFSET_RUSAGE_OUBLOCK    __OFFSET_RUSAGEX32_OUBLOCK
#define __OFFSET_RUSAGE_MSGSND     __OFFSET_RUSAGEX32_MSGSND
#define __OFFSET_RUSAGE_MSGRCV     __OFFSET_RUSAGEX32_MSGRCV
#define __OFFSET_RUSAGE_NSIGNALS   __OFFSET_RUSAGEX32_NSIGNALS
#define __OFFSET_RUSAGE_NVCSW      __OFFSET_RUSAGEX32_NVCSW
#define __OFFSET_RUSAGE_NIVCSW     __OFFSET_RUSAGEX32_NIVCSW
#define __SIZEOF_RUSAGE            __SIZEOF_RUSAGEX32
#define __OFFSET_RUSAGE64_UTIME    __OFFSET_RUSAGEX32_64_UTIME
#define __OFFSET_RUSAGE64_STIME    __OFFSET_RUSAGEX32_64_STIME
#define __OFFSET_RUSAGE64_MAXRSS   __OFFSET_RUSAGEX32_64_MAXRSS
#define __OFFSET_RUSAGE64_IXRSS    __OFFSET_RUSAGEX32_64_IXRSS
#define __OFFSET_RUSAGE64_IDRSS    __OFFSET_RUSAGEX32_64_IDRSS
#define __OFFSET_RUSAGE64_ISRSS    __OFFSET_RUSAGEX32_64_ISRSS
#define __OFFSET_RUSAGE64_MINFLT   __OFFSET_RUSAGEX32_64_MINFLT
#define __OFFSET_RUSAGE64_MAJFLT   __OFFSET_RUSAGEX32_64_MAJFLT
#define __OFFSET_RUSAGE64_NSWAP    __OFFSET_RUSAGEX32_64_NSWAP
#define __OFFSET_RUSAGE64_INBLOCK  __OFFSET_RUSAGEX32_64_INBLOCK
#define __OFFSET_RUSAGE64_OUBLOCK  __OFFSET_RUSAGEX32_64_OUBLOCK
#define __OFFSET_RUSAGE64_MSGSND   __OFFSET_RUSAGEX32_64_MSGSND
#define __OFFSET_RUSAGE64_MSGRCV   __OFFSET_RUSAGEX32_64_MSGRCV
#define __OFFSET_RUSAGE64_NSIGNALS __OFFSET_RUSAGEX32_64_NSIGNALS
#define __OFFSET_RUSAGE64_NVCSW    __OFFSET_RUSAGEX32_64_NVCSW
#define __OFFSET_RUSAGE64_NIVCSW   __OFFSET_RUSAGEX32_64_NIVCSW
#define __SIZEOF_RUSAGE64          __SIZEOF_RUSAGEX32_64

#endif /* !__USE_TIME_BITS64 */
#define __rusage_defined 1
#endif /* !__x86_64__ */

#define __OFFSET_RUSAGEX32_UTIME       0
#define __OFFSET_RUSAGEX32_STIME       8
#define __OFFSET_RUSAGEX32_MAXRSS      16
#define __OFFSET_RUSAGEX32_IXRSS       20
#define __OFFSET_RUSAGEX32_IDRSS       24
#define __OFFSET_RUSAGEX32_ISRSS       28
#define __OFFSET_RUSAGEX32_MINFLT      32
#define __OFFSET_RUSAGEX32_MAJFLT      36
#define __OFFSET_RUSAGEX32_NSWAP       40
#define __OFFSET_RUSAGEX32_INBLOCK     44
#define __OFFSET_RUSAGEX32_OUBLOCK     48
#define __OFFSET_RUSAGEX32_MSGSND      52
#define __OFFSET_RUSAGEX32_MSGRCV      56
#define __OFFSET_RUSAGEX32_NSIGNALS    60
#define __OFFSET_RUSAGEX32_NVCSW       64
#define __OFFSET_RUSAGEX32_NIVCSW      68
#define __SIZEOF_RUSAGEX32             72
#define __OFFSET_RUSAGEX32_64_UTIME    0
#define __OFFSET_RUSAGEX32_64_STIME    16
#define __OFFSET_RUSAGEX32_64_MAXRSS   32
#define __OFFSET_RUSAGEX32_64_IXRSS    36
#define __OFFSET_RUSAGEX32_64_IDRSS    40
#define __OFFSET_RUSAGEX32_64_ISRSS    44
#define __OFFSET_RUSAGEX32_64_MINFLT   48
#define __OFFSET_RUSAGEX32_64_MAJFLT   52
#define __OFFSET_RUSAGEX32_64_NSWAP    56
#define __OFFSET_RUSAGEX32_64_INBLOCK  60
#define __OFFSET_RUSAGEX32_64_OUBLOCK  64
#define __OFFSET_RUSAGEX32_64_MSGSND   68
#define __OFFSET_RUSAGEX32_64_MSGRCV   72
#define __OFFSET_RUSAGEX32_64_NSIGNALS 76
#define __OFFSET_RUSAGEX32_64_NVCSW    80
#define __OFFSET_RUSAGEX32_64_NIVCSW   84
#define __SIZEOF_RUSAGEX32_64          88

#ifdef __CC__
__DECL_BEGIN

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

/* 32-bit rusage for i386 */
struct rusagex32 /*[PREFIX(ru_)]*/ {
	struct __timevalx32 ru_utime;    /* Total amount of user time used. */
	struct __timevalx32 ru_stime;    /* Total amount of system time used. */
	__LONG32_TYPE__     ru_maxrss;   /* Maximum resident set size (in kilobytes). */
	/* Amount of sharing of text segment memory with other processes (kilobyte-seconds). */
	__LONG32_TYPE__     ru_ixrss;    /* Maximum resident set size (in kilobytes). */
	__LONG32_TYPE__     ru_idrss;    /* Amount of data segment memory used (kilobyte-seconds). */
	__LONG32_TYPE__     ru_isrss;    /* Amount of stack memory used (kilobyte-seconds). */
	__LONG32_TYPE__     ru_minflt;   /* Number of soft page faults (i.e. those serviced by reclaiming a page from the list of pages awaiting reallocation. */
	__LONG32_TYPE__     ru_majflt;   /* Number of hard page faults (i.e. those that required I/O). */
	__LONG32_TYPE__     ru_nswap;    /* Number of times a process was swapped out of physical memory. */
	__LONG32_TYPE__     ru_inblock;  /* Number of input operations via the file system.
	                                  * NOTE: This and `ru_oublock' do not include operations with the cache. */
	__LONG32_TYPE__     ru_oublock;  /* Number of output operations via the file system. */
	__LONG32_TYPE__     ru_msgsnd;   /* Number of IPC messages sent. */
	__LONG32_TYPE__     ru_msgrcv;   /* Number of IPC messages received. */
	__LONG32_TYPE__     ru_nsignals; /* Number of signals delivered. */
	__LONG32_TYPE__     ru_nvcsw;    /* Number of voluntary context switches, i.e. because the process gave up the
	                                  * process before it had to (usually to wait for some resource to be available). */
	__LONG32_TYPE__     ru_nivcsw;   /* Number of involuntary context switches, i.e. a higher priority process
	                                  * became runnable or the current process used up its time slice. */
};

/* 64-bit rusage for i386 */
struct rusagex32_64 /*[PREFIX(ru_)]*/ {
	struct __timevalx32_64 ru_utime;    /* Total amount of user time used. */
	struct __timevalx32_64 ru_stime;    /* Total amount of system time used. */
	__LONG32_TYPE__        ru_maxrss;   /* Maximum resident set size (in kilobytes). */
	/* Amount of sharing of text segment memory with other processes (kilobyte-seconds). */
	__LONG32_TYPE__        ru_ixrss;    /* Maximum resident set size (in kilobytes). */
	__LONG32_TYPE__        ru_idrss;    /* Amount of data segment memory used (kilobyte-seconds). */
	__LONG32_TYPE__        ru_isrss;    /* Amount of stack memory used (kilobyte-seconds). */
	__LONG32_TYPE__        ru_minflt;   /* Number of soft page faults (i.e. those serviced by reclaiming a page from the list of pages awaiting reallocation. */
	__LONG32_TYPE__        ru_majflt;   /* Number of hard page faults (i.e. those that required I/O). */
	__LONG32_TYPE__        ru_nswap;    /* Number of times a process was swapped out of physical memory. */
	__LONG32_TYPE__        ru_inblock;  /* Number of input operations via the file system.
	                                     * NOTE: This and `ru_oublock' do not include operations with the cache. */
	__LONG32_TYPE__        ru_oublock;  /* Number of output operations via the file system. */
	__LONG32_TYPE__        ru_msgsnd;   /* Number of IPC messages sent. */
	__LONG32_TYPE__        ru_msgrcv;   /* Number of IPC messages received. */
	__LONG32_TYPE__        ru_nsignals; /* Number of signals delivered. */
	__LONG32_TYPE__        ru_nvcsw;    /* Number of voluntary context switches, i.e. because the process gave up the
	                                     * process before it had to (usually to wait for some resource to be available). */
	__LONG32_TYPE__        ru_nivcsw;   /* Number of involuntary context switches, i.e. a higher priority process
	                                     * became runnable or the current process used up its time slice. */
};

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS
#undef rusagex32
#undef rusagex32_64
#endif /* !__USE_KOS */

#endif /* !_I386_KOS_BITS_RUSAGE_STRUCT32_H */
