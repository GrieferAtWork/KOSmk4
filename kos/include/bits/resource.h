/* HASH CRC-32:0x4ea88666 */
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
#ifndef _BITS_RESOURCE_H
#define _BITS_RESOURCE_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <bits/timeval.h>
#include <bits/rusage-struct.h>

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


/* Kinds of resource limit. */
/*[[[enum]]]*/
#ifdef __CC__
enum __rlimit_resource {
	RLIMIT_CPU        = 0,  /* Per-process CPU limit, in seconds. */
	RLIMIT_FSIZE      = 1,  /* Largest file that can be created, in bytes. */
	RLIMIT_DATA       = 2,  /* Maximum size of data segment, in bytes. */
	RLIMIT_STACK      = 3,  /* Maximum size of stack segment, in bytes. */
	RLIMIT_CORE       = 4,  /* Largest core file that can be created, in bytes. */
	RLIMIT_RSS        = 5,  /* Largest resident set size, in bytes. This affects swapping;
	                         * processes that are exceeding their resident set size will
	                         * be more likely to have physical memory taken from them. */
	RLIMIT_NPROC      = 6,  /* Number of processes. */
	RLIMIT_NOFILE     = 7,  /* Number of open files. */
	RLIMIT_OFILE      = 7,  /* BSD name for RLIMIT_NOFILE. */
	RLIMIT_MEMLOCK    = 8,  /* Locked-in-memory address space. */
	RLIMIT_AS         = 9,  /* Address space limit. */
	RLIMIT_LOCKS      = 10, /* Maximum number of file locks. */
	RLIMIT_SIGPENDING = 11, /* Maximum number of pending signals. */
	RLIMIT_MSGQUEUE   = 12, /* Maximum bytes in POSIX message queues. */
	RLIMIT_NICE       = 13, /* Maximum nice priority allowed to raise to. Nice levels
	                         * 19 .. -20 correspond to 0 .. 39 values of this resource
	                         * limit. */
	RLIMIT_RTPRIO     = 14, /* Maximum realtime priority allowed for non-privileged processes. */
	RLIMIT_RTTIME     = 15, /* Maximum CPU time in µs that a process scheduled under a real-time
	                         * scheduling policy may consume without making a blocking system call
	                         * before being forcibly descheduled. */
	RLIMIT_NLIMITS    = 16,
	RLIM_NLIMITS      = 16
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define RLIMIT_CPU        RLIMIT_CPU        /* Per-process CPU limit, in seconds. */
#define RLIMIT_FSIZE      RLIMIT_FSIZE      /* Largest file that can be created, in bytes. */
#define RLIMIT_DATA       RLIMIT_DATA       /* Maximum size of data segment, in bytes. */
#define RLIMIT_STACK      RLIMIT_STACK      /* Maximum size of stack segment, in bytes. */
#define RLIMIT_CORE       RLIMIT_CORE       /* Largest core file that can be created, in bytes. */
#define RLIMIT_RSS        RLIMIT_RSS        /* Largest resident set size, in bytes. This affects swapping;
                                             * processes that are exceeding their resident set size will
                                             * be more likely to have physical memory taken from them. */
#define RLIMIT_NPROC      RLIMIT_NPROC      /* Number of processes. */
#define RLIMIT_NOFILE     RLIMIT_NOFILE     /* Number of open files. */
#define RLIMIT_OFILE      RLIMIT_OFILE      /* BSD name for RLIMIT_NOFILE. */
#define RLIMIT_MEMLOCK    RLIMIT_MEMLOCK    /* Locked-in-memory address space. */
#define RLIMIT_AS         RLIMIT_AS         /* Address space limit. */
#define RLIMIT_LOCKS      RLIMIT_LOCKS      /* Maximum number of file locks. */
#define RLIMIT_SIGPENDING RLIMIT_SIGPENDING /* Maximum number of pending signals. */
#define RLIMIT_MSGQUEUE   RLIMIT_MSGQUEUE   /* Maximum bytes in POSIX message queues. */
#define RLIMIT_NICE       RLIMIT_NICE       /* Maximum nice priority allowed to raise to. Nice levels
                                             * 19 .. -20 correspond to 0 .. 39 values of this resource
                                             * limit. */
#define RLIMIT_RTPRIO     RLIMIT_RTPRIO     /* Maximum realtime priority allowed for non-privileged processes. */
#define RLIMIT_RTTIME     RLIMIT_RTTIME     /* Maximum CPU time in µs that a process scheduled under a real-time
                                             * scheduling policy may consume without making a blocking system call
                                             * before being forcibly descheduled. */
#define RLIMIT_NLIMITS    RLIMIT_NLIMITS
#define RLIM_NLIMITS      RLIM_NLIMITS
#else /* __COMPILER_PREFERR_ENUMS */
#define RLIMIT_CPU        0  /* Per-process CPU limit, in seconds. */
#define RLIMIT_FSIZE      1  /* Largest file that can be created, in bytes. */
#define RLIMIT_DATA       2  /* Maximum size of data segment, in bytes. */
#define RLIMIT_STACK      3  /* Maximum size of stack segment, in bytes. */
#define RLIMIT_CORE       4  /* Largest core file that can be created, in bytes. */
#define RLIMIT_RSS        5  /* Largest resident set size, in bytes. This affects swapping;
                              * processes that are exceeding their resident set size will
                              * be more likely to have physical memory taken from them. */
#define RLIMIT_NPROC      6  /* Number of processes. */
#define RLIMIT_NOFILE     7  /* Number of open files. */
#define RLIMIT_OFILE      7  /* BSD name for RLIMIT_NOFILE. */
#define RLIMIT_MEMLOCK    8  /* Locked-in-memory address space. */
#define RLIMIT_AS         9  /* Address space limit. */
#define RLIMIT_LOCKS      10 /* Maximum number of file locks. */
#define RLIMIT_SIGPENDING 11 /* Maximum number of pending signals. */
#define RLIMIT_MSGQUEUE   12 /* Maximum bytes in POSIX message queues. */
#define RLIMIT_NICE       13 /* Maximum nice priority allowed to raise to. Nice levels
                              * 19 .. -20 correspond to 0 .. 39 values of this resource
                              * limit. */
#define RLIMIT_RTPRIO     14 /* Maximum realtime priority allowed for non-privileged processes. */
#define RLIMIT_RTTIME     15 /* Maximum CPU time in µs that a process scheduled under a real-time
                              * scheduling policy may consume without making a blocking system call
                              * before being forcibly descheduled. */
#define RLIMIT_NLIMITS    16
#define RLIM_NLIMITS      16
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* Value to indicate that there is no limit. */
#define RLIM_INFINITY     (__CCAST(__FS_TYPE(rlim))-1)
#ifdef __USE_LARGEFILE64
#define RLIM64_INFINITY   (__CCAST(__rlim64_t)-1)
#endif /* __USE_LARGEFILE64 */

/* We can represent all limits. */
#ifndef RLIM_SAVED_MAX
#define RLIM_SAVED_MAX    RLIM_INFINITY
#endif /* !RLIM_SAVED_MAX */
#ifndef RLIM_SAVED_CUR
#define RLIM_SAVED_CUR    RLIM_INFINITY
#endif /* !RLIM_SAVED_CUR */


/* The type of the WHICH argument to `getpriority' and `setpriority',
 * indicating what flavor of entity the WHO argument specifies. */
/*[[[enum]]]*/
#ifdef __CC__
enum __priority_which {
	PRIO_PROCESS = 0, /* WHO is a process ID. */
	PRIO_PGRP    = 1, /* WHO is a process group ID. */
	PRIO_USER    = 2  /* WHO is a user ID. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define PRIO_PROCESS PRIO_PROCESS /* WHO is a process ID. */
#define PRIO_PGRP    PRIO_PGRP    /* WHO is a process group ID. */
#define PRIO_USER    PRIO_USER    /* WHO is a user ID. */
#else /* __COMPILER_PREFERR_ENUMS */
#define PRIO_PROCESS 0 /* WHO is a process ID. */
#define PRIO_PGRP    1 /* WHO is a process group ID. */
#define PRIO_USER    2 /* WHO is a user ID. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


/* Whose usage statistics do you want?  */
/*[[[enum]]]*/
#ifdef __CC__
enum __rusage_who {
	RUSAGE_SELF     =  0,   /* The calling process. */
	RUSAGE_CHILDREN = (-1), /* All of its terminated child processes. */
#ifdef __USE_GNU
	RUSAGE_THREAD   =  1    /* The calling thread. */
#endif /* __USE_GNU */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define RUSAGE_SELF     RUSAGE_SELF     /* The calling process. */
#define RUSAGE_CHILDREN RUSAGE_CHILDREN /* All of its terminated child processes. */
#ifdef __USE_GNU
#define RUSAGE_THREAD   RUSAGE_THREAD   /* The calling thread. */
#endif /* __USE_GNU */
#else /* __COMPILER_PREFERR_ENUMS */
#define RUSAGE_SELF     0    /* The calling process. */
#define RUSAGE_CHILDREN (-1) /* All of its terminated child processes. */
#ifdef __USE_GNU
#define RUSAGE_THREAD   1    /* The calling thread. */
#endif /* __USE_GNU */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* Priority limits. */
#ifndef PRIO_MIN
#define PRIO_MIN  (-20) /* Minimum priority a process can have. */
#endif /* !PRIO_MIN */
#ifndef PRIO_MAX
#define PRIO_MAX    20  /* Maximum priority a process can have. */
#endif /* !PRIO_MAX */


#ifdef __CC__

/* Type for resource quantity measurement. */
#ifndef __rlim_t_defined
#define __rlim_t_defined 1
typedef __FS_TYPE(rlim) rlim_t;
#endif /* !__rlim_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __rlim64_t_defined
#define __rlim64_t_defined 1
typedef __rlim64_t rlim64_t;
#endif /* !__rlim64_t_defined */
#endif /* __USE_LARGEFILE64 */

#ifndef __rlimit_defined
#define __rlimit_defined 1
struct rlimit {
	rlim_t rlim_cur; /* The current (soft) limit. */
	rlim_t rlim_max; /* The hard limit. */
};
#endif /* !__rlimit_defined */

#ifdef __USE_LARGEFILE64
#ifndef __rlimit64_defined
#define __rlimit64_defined 1
struct rlimit64 {
	rlim64_t rlim_cur; /* The current (soft) limit. */
	rlim64_t rlim_max; /* The hard limit. */
};
#endif /* !__rlimit64_defined */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_GNU
#ifdef __COMPILER_PREFERR_ENUMS
typedef enum __rlimit_resource __rlimit_resource_t;
#else /* __COMPILER_PREFERR_ENUMS */
typedef int __rlimit_resource_t;
#endif /* !__COMPILER_PREFERR_ENUMS */

#ifdef __CRT_HAVE_prlimit
__CDECLARE(,int,__NOTHROW_NCX,prlimit,(__pid_t __pid, __rlimit_resource_t __resource, struct rlimit const *__new_limit, struct rlimit *__old_limit),(__pid,__resource,__new_limit,__old_limit))
#endif /* __CRT_HAVE_prlimit */
#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_prlimit64
__CDECLARE(,int,__NOTHROW_NCX,prlimit64,(__pid_t __pid, __rlimit_resource_t __resource, struct rlimit64 const *__new_limit, struct rlimit64 *__old_limit),(__pid,__resource,__new_limit,__old_limit))
#elif defined(__CRT_HAVE_prlimit) && (__SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)
__CREDIRECT(,int,__NOTHROW_NCX,prlimit64,(__pid_t __pid, __rlimit_resource_t __resource, struct rlimit64 const *__new_limit, struct rlimit64 *__old_limit),prlimit,(__pid,__resource,__new_limit,__old_limit))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_GNU */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_RESOURCE_H */
