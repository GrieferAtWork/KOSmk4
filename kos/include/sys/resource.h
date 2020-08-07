/* HASH CRC-32:0xbfd2f583 */
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
#ifndef _SYS_RESOURCE_H
#define _SYS_RESOURCE_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/resource.h>
#include <bits/resource.h>
#include <bits/rusage-struct.h>
#include <bits/timeval.h>
#include <bits/types.h>

__SYSDECL_BEGIN

/* Documentation taken from Glibc /usr/include/i386-linux-gnu/sys/resource.h */
/* Copyright (C) 1992-2016 Free Software Foundation, Inc.
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

#if (defined(__RLIMIT_CPU) || defined(__RLIMIT_FSIZE) ||           \
     defined(__RLIMIT_DATA) || defined(__RLIMIT_STACK) ||          \
     defined(__RLIMIT_CORE) || defined(__RLIMIT_RSS) ||            \
     defined(__RLIMIT_NPROC) || defined(__RLIMIT_NOFILE) ||        \
     defined(__RLIMIT_OFILE) || defined(__RLIMIT_MEMLOCK) ||       \
     defined(__RLIMIT_AS) || defined(__RLIMIT_LOCKS) ||            \
     defined(__RLIMIT_SIGPENDING) || defined(__RLIMIT_MSGQUEUE) || \
     defined(__RLIMIT_NICE) || defined(__RLIMIT_RTPRIO) ||         \
     defined(__RLIMIT_RTTIME) || defined(__RLIMIT_NLIMITS) ||      \
     defined(__RLIM_NLIMITS))
/* Kinds of resource limit. */
/*[[[enum]]]*/
#ifdef __CC__
enum __rlimit_resource {
#ifdef __RLIMIT_CPU
	RLIMIT_CPU = __RLIMIT_CPU, /* Per-process CPU limit, in seconds. */
#endif /* __RLIMIT_CPU */
#ifdef __RLIMIT_FSIZE
	RLIMIT_FSIZE = __RLIMIT_FSIZE, /* Largest file that can be created, in bytes. */
#endif /* __RLIMIT_FSIZE */
#ifdef __RLIMIT_DATA
	RLIMIT_DATA = __RLIMIT_DATA, /* Maximum size of data segment, in bytes. */
#endif /* __RLIMIT_DATA */
#ifdef __RLIMIT_STACK
	RLIMIT_STACK = __RLIMIT_STACK, /* Maximum size of stack segment, in bytes. */
#endif /* __RLIMIT_STACK */
#ifdef __RLIMIT_CORE
	RLIMIT_CORE = __RLIMIT_CORE, /* Largest core file that can be created, in bytes. */
#endif /* __RLIMIT_CORE */
#ifdef __RLIMIT_RSS
	RLIMIT_RSS = __RLIMIT_RSS, /* Largest resident set size, in bytes. This affects swapping;
	                            * processes that are exceeding their resident set size will
	                            * be more likely to have physical memory taken from them. */
#endif /* __RLIMIT_RSS */
#ifdef __RLIMIT_NPROC
	RLIMIT_NPROC = __RLIMIT_NPROC, /* Number of processes. */
#endif /* __RLIMIT_NPROC */
#ifdef __RLIMIT_NOFILE
	RLIMIT_NOFILE = __RLIMIT_NOFILE, /* Number of open files. */
#endif /* __RLIMIT_NOFILE */
#ifdef __RLIMIT_OFILE
	RLIMIT_OFILE = __RLIMIT_OFILE, /* BSD name for RLIMIT_NOFILE. */
#endif /* __RLIMIT_OFILE */
#ifdef __RLIMIT_MEMLOCK
	RLIMIT_MEMLOCK = __RLIMIT_MEMLOCK, /* Locked-in-memory address space. */
#endif /* __RLIMIT_MEMLOCK */
#ifdef __RLIMIT_AS
	RLIMIT_AS = __RLIMIT_AS, /* Address space limit. */
#endif /* __RLIMIT_AS */
#ifdef __RLIMIT_LOCKS
	RLIMIT_LOCKS = __RLIMIT_LOCKS, /* Maximum number of file locks. */
#endif /* __RLIMIT_LOCKS */
#ifdef __RLIMIT_SIGPENDING
	RLIMIT_SIGPENDING = __RLIMIT_SIGPENDING, /* Maximum number of pending signals. */
#endif /* __RLIMIT_SIGPENDING */
#ifdef __RLIMIT_MSGQUEUE
	RLIMIT_MSGQUEUE = __RLIMIT_MSGQUEUE, /* Maximum bytes in POSIX message queues. */
#endif /* __RLIMIT_MSGQUEUE */
#ifdef __RLIMIT_NICE
	RLIMIT_NICE = __RLIMIT_NICE, /* Maximum nice priority allowed to raise to. Nice levels
	                              * 19 .. -20 correspond to 0 .. 39 values of this resource
	                              * limit. */
#endif /* __RLIMIT_NICE */
#ifdef __RLIMIT_RTPRIO
	RLIMIT_RTPRIO = __RLIMIT_RTPRIO, /* Maximum realtime priority allowed for non-privileged processes. */
#endif /* __RLIMIT_RTPRIO */
#ifdef __RLIMIT_RTTIME
	RLIMIT_RTTIME = __RLIMIT_RTTIME, /* Maximum CPU time in µs that a process scheduled under a real-time
	                                  * scheduling policy may consume without making a blocking system call
	                                  * before being forcibly descheduled. */
#endif /* __RLIMIT_RTTIME */
#ifdef __RLIMIT_NLIMITS
	RLIMIT_NLIMITS = __RLIMIT_NLIMITS,
#endif /* __RLIMIT_NLIMITS */
#ifdef __RLIM_NLIMITS
	RLIM_NLIMITS = __RLIM_NLIMITS,
#endif /* __RLIM_NLIMITS */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __RLIMIT_CPU
#define RLIMIT_CPU        RLIMIT_CPU        /* Per-process CPU limit, in seconds. */
#endif /* __RLIMIT_CPU */
#ifdef __RLIMIT_FSIZE
#define RLIMIT_FSIZE      RLIMIT_FSIZE      /* Largest file that can be created, in bytes. */
#endif /* __RLIMIT_FSIZE */
#ifdef __RLIMIT_DATA
#define RLIMIT_DATA       RLIMIT_DATA       /* Maximum size of data segment, in bytes. */
#endif /* __RLIMIT_DATA */
#ifdef __RLIMIT_STACK
#define RLIMIT_STACK      RLIMIT_STACK      /* Maximum size of stack segment, in bytes. */
#endif /* __RLIMIT_STACK */
#ifdef __RLIMIT_CORE
#define RLIMIT_CORE       RLIMIT_CORE       /* Largest core file that can be created, in bytes. */
#endif /* __RLIMIT_CORE */
#ifdef __RLIMIT_RSS
#define RLIMIT_RSS        RLIMIT_RSS        /* Largest resident set size, in bytes. This affects swapping;
                                             * processes that are exceeding their resident set size will
                                             * be more likely to have physical memory taken from them. */
#endif /* __RLIMIT_RSS */
#ifdef __RLIMIT_NPROC
#define RLIMIT_NPROC      RLIMIT_NPROC      /* Number of processes. */
#endif /* __RLIMIT_NPROC */
#ifdef __RLIMIT_NOFILE
#define RLIMIT_NOFILE     RLIMIT_NOFILE     /* Number of open files. */
#endif /* __RLIMIT_NOFILE */
#ifdef __RLIMIT_OFILE
#define RLIMIT_OFILE      RLIMIT_OFILE      /* BSD name for RLIMIT_NOFILE. */
#endif /* __RLIMIT_OFILE */
#ifdef __RLIMIT_MEMLOCK
#define RLIMIT_MEMLOCK    RLIMIT_MEMLOCK    /* Locked-in-memory address space. */
#endif /* __RLIMIT_MEMLOCK */
#ifdef __RLIMIT_AS
#define RLIMIT_AS         RLIMIT_AS         /* Address space limit. */
#endif /* __RLIMIT_AS */
#ifdef __RLIMIT_LOCKS
#define RLIMIT_LOCKS      RLIMIT_LOCKS      /* Maximum number of file locks. */
#endif /* __RLIMIT_LOCKS */
#ifdef __RLIMIT_SIGPENDING
#define RLIMIT_SIGPENDING RLIMIT_SIGPENDING /* Maximum number of pending signals. */
#endif /* __RLIMIT_SIGPENDING */
#ifdef __RLIMIT_MSGQUEUE
#define RLIMIT_MSGQUEUE   RLIMIT_MSGQUEUE   /* Maximum bytes in POSIX message queues. */
#endif /* __RLIMIT_MSGQUEUE */
#ifdef __RLIMIT_NICE
#define RLIMIT_NICE       RLIMIT_NICE       /* Maximum nice priority allowed to raise to. Nice levels
                                             * 19 .. -20 correspond to 0 .. 39 values of this resource
                                             * limit. */
#endif /* __RLIMIT_NICE */
#ifdef __RLIMIT_RTPRIO
#define RLIMIT_RTPRIO     RLIMIT_RTPRIO     /* Maximum realtime priority allowed for non-privileged processes. */
#endif /* __RLIMIT_RTPRIO */
#ifdef __RLIMIT_RTTIME
#define RLIMIT_RTTIME     RLIMIT_RTTIME     /* Maximum CPU time in µs that a process scheduled under a real-time
                                             * scheduling policy may consume without making a blocking system call
                                             * before being forcibly descheduled. */
#endif /* __RLIMIT_RTTIME */
#ifdef __RLIMIT_NLIMITS
#define RLIMIT_NLIMITS    RLIMIT_NLIMITS
#endif /* __RLIMIT_NLIMITS */
#ifdef __RLIM_NLIMITS
#define RLIM_NLIMITS      RLIM_NLIMITS
#endif /* __RLIM_NLIMITS */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __RLIMIT_CPU
#define RLIMIT_CPU        __RLIMIT_CPU        /* Per-process CPU limit, in seconds. */
#endif /* __RLIMIT_CPU */
#ifdef __RLIMIT_FSIZE
#define RLIMIT_FSIZE      __RLIMIT_FSIZE      /* Largest file that can be created, in bytes. */
#endif /* __RLIMIT_FSIZE */
#ifdef __RLIMIT_DATA
#define RLIMIT_DATA       __RLIMIT_DATA       /* Maximum size of data segment, in bytes. */
#endif /* __RLIMIT_DATA */
#ifdef __RLIMIT_STACK
#define RLIMIT_STACK      __RLIMIT_STACK      /* Maximum size of stack segment, in bytes. */
#endif /* __RLIMIT_STACK */
#ifdef __RLIMIT_CORE
#define RLIMIT_CORE       __RLIMIT_CORE       /* Largest core file that can be created, in bytes. */
#endif /* __RLIMIT_CORE */
#ifdef __RLIMIT_RSS
#define RLIMIT_RSS        __RLIMIT_RSS        /* Largest resident set size, in bytes. This affects swapping;
                                               * processes that are exceeding their resident set size will
                                               * be more likely to have physical memory taken from them. */
#endif /* __RLIMIT_RSS */
#ifdef __RLIMIT_NPROC
#define RLIMIT_NPROC      __RLIMIT_NPROC      /* Number of processes. */
#endif /* __RLIMIT_NPROC */
#ifdef __RLIMIT_NOFILE
#define RLIMIT_NOFILE     __RLIMIT_NOFILE     /* Number of open files. */
#endif /* __RLIMIT_NOFILE */
#ifdef __RLIMIT_OFILE
#define RLIMIT_OFILE      __RLIMIT_OFILE      /* BSD name for RLIMIT_NOFILE. */
#endif /* __RLIMIT_OFILE */
#ifdef __RLIMIT_MEMLOCK
#define RLIMIT_MEMLOCK    __RLIMIT_MEMLOCK    /* Locked-in-memory address space. */
#endif /* __RLIMIT_MEMLOCK */
#ifdef __RLIMIT_AS
#define RLIMIT_AS         __RLIMIT_AS         /* Address space limit. */
#endif /* __RLIMIT_AS */
#ifdef __RLIMIT_LOCKS
#define RLIMIT_LOCKS      __RLIMIT_LOCKS      /* Maximum number of file locks. */
#endif /* __RLIMIT_LOCKS */
#ifdef __RLIMIT_SIGPENDING
#define RLIMIT_SIGPENDING __RLIMIT_SIGPENDING /* Maximum number of pending signals. */
#endif /* __RLIMIT_SIGPENDING */
#ifdef __RLIMIT_MSGQUEUE
#define RLIMIT_MSGQUEUE   __RLIMIT_MSGQUEUE   /* Maximum bytes in POSIX message queues. */
#endif /* __RLIMIT_MSGQUEUE */
#ifdef __RLIMIT_NICE
#define RLIMIT_NICE       __RLIMIT_NICE       /* Maximum nice priority allowed to raise to. Nice levels
                                               * 19 .. -20 correspond to 0 .. 39 values of this resource
                                               * limit. */
#endif /* __RLIMIT_NICE */
#ifdef __RLIMIT_RTPRIO
#define RLIMIT_RTPRIO     __RLIMIT_RTPRIO     /* Maximum realtime priority allowed for non-privileged processes. */
#endif /* __RLIMIT_RTPRIO */
#ifdef __RLIMIT_RTTIME
#define RLIMIT_RTTIME     __RLIMIT_RTTIME     /* Maximum CPU time in µs that a process scheduled under a real-time
                                               * scheduling policy may consume without making a blocking system call
                                               * before being forcibly descheduled. */
#endif /* __RLIMIT_RTTIME */
#ifdef __RLIMIT_NLIMITS
#define RLIMIT_NLIMITS    __RLIMIT_NLIMITS
#endif /* __RLIMIT_NLIMITS */
#ifdef __RLIM_NLIMITS
#define RLIM_NLIMITS      __RLIM_NLIMITS
#endif /* __RLIM_NLIMITS */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

/* Value to indicate that there is no limit. */
#define RLIM_INFINITY   (__CCAST(__FS_TYPE(rlim))-1)
#ifdef __USE_LARGEFILE64
#define RLIM64_INFINITY (__CCAST(__rlim64_t)-1)
#endif /* __USE_LARGEFILE64 */

/* We can represent all limits. */
#ifndef RLIM_SAVED_MAX
#define RLIM_SAVED_MAX RLIM_INFINITY
#endif /* !RLIM_SAVED_MAX */
#ifndef RLIM_SAVED_CUR
#define RLIM_SAVED_CUR RLIM_INFINITY
#endif /* !RLIM_SAVED_CUR */


#if defined(__PRIO_PROCESS) || defined(__PRIO_PGRP) || defined(__PRIO_USER)
/* The type of the WHICH argument to `getpriority' and `setpriority',
 * indicating what flavor of entity the WHO argument specifies. */
/*[[[enum]]]*/
#ifdef __CC__
enum __priority_which {
#ifdef __PRIO_PROCESS
	PRIO_PROCESS = __PRIO_PROCESS, /* WHO is a process ID. */
#endif /* __PRIO_PROCESS */
#ifdef __PRIO_PGRP
	PRIO_PGRP = __PRIO_PGRP, /* WHO is a process group ID. */
#endif /* __PRIO_PGRP */
#ifdef __PRIO_USER
	PRIO_USER = __PRIO_USER /* WHO is a user ID. */
#endif /* __PRIO_USER */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __PRIO_PROCESS
#define PRIO_PROCESS PRIO_PROCESS /* WHO is a process ID. */
#endif /* __PRIO_PROCESS */
#ifdef __PRIO_PGRP
#define PRIO_PGRP    PRIO_PGRP    /* WHO is a process group ID. */
#endif /* __PRIO_PGRP */
#ifdef __PRIO_USER
#define PRIO_USER    PRIO_USER    /* WHO is a user ID. */
#endif /* __PRIO_USER */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __PRIO_PROCESS
#define PRIO_PROCESS __PRIO_PROCESS /* WHO is a process ID. */
#endif /* __PRIO_PROCESS */
#ifdef __PRIO_PGRP
#define PRIO_PGRP    __PRIO_PGRP    /* WHO is a process group ID. */
#endif /* __PRIO_PGRP */
#ifdef __PRIO_USER
#define PRIO_USER    __PRIO_USER    /* WHO is a user ID. */
#endif /* __PRIO_USER */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */


#if (defined(__RUSAGE_SELF) || defined(__RUSAGE_CHILDREN) || \
     (defined(__USE_GNU) && defined(__RUSAGE_THREAD)))
/* Whose usage statistics do you want?  */
/*[[[enum]]]*/
#ifdef __CC__
enum __rusage_who {
#ifdef __RUSAGE_SELF
	RUSAGE_SELF = __RUSAGE_SELF,         /* The calling process. */
#endif /* __RUSAGE_SELF */
#ifdef __RUSAGE_CHILDREN
	RUSAGE_CHILDREN = __RUSAGE_CHILDREN, /* All of its terminated child processes. */
#endif /* __RUSAGE_CHILDREN */
#ifdef __USE_GNU
#ifdef __RUSAGE_THREAD
	RUSAGE_THREAD = __RUSAGE_THREAD /* The calling thread. */
#endif /* __RUSAGE_THREAD */
#endif /* __USE_GNU */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __RUSAGE_SELF
#define RUSAGE_SELF     RUSAGE_SELF     /* The calling process. */
#endif /* __RUSAGE_SELF */
#ifdef __RUSAGE_CHILDREN
#define RUSAGE_CHILDREN RUSAGE_CHILDREN /* All of its terminated child processes. */
#endif /* __RUSAGE_CHILDREN */
#ifdef __USE_GNU
#ifdef __RUSAGE_THREAD
#define RUSAGE_THREAD   RUSAGE_THREAD   /* The calling thread. */
#endif /* __RUSAGE_THREAD */
#endif /* __USE_GNU */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __RUSAGE_SELF
#define RUSAGE_SELF     __RUSAGE_SELF     /* The calling process. */
#endif /* __RUSAGE_SELF */
#ifdef __RUSAGE_CHILDREN
#define RUSAGE_CHILDREN __RUSAGE_CHILDREN /* All of its terminated child processes. */
#endif /* __RUSAGE_CHILDREN */
#ifdef __USE_GNU
#ifdef __RUSAGE_THREAD
#define RUSAGE_THREAD   __RUSAGE_THREAD   /* The calling thread. */
#endif /* __RUSAGE_THREAD */
#endif /* __USE_GNU */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

/* Priority limits. */
#ifdef __PRIO_MIN
#define PRIO_MIN __PRIO_MIN /* Minimum priority a process can have. */
#endif /* __PRIO_MIN */
#ifdef __PRIO_MAX
#define PRIO_MAX __PRIO_MAX /* Maximum priority a process can have. */
#endif /* __PRIO_MAX */


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

#ifndef __id_t_defined
#define __id_t_defined
typedef __id_t id_t;
#endif /* !__id_t_defined */

#if defined(__USE_GNU) && defined(__COMPILER_PREFERR_ENUMS)
typedef enum __rlimit_resource __rlimit_resource_t;
typedef enum __rusage_who      __rusage_who_t;
typedef enum __priority_which  __priority_which_t;
#else /* __USE_GNU && __COMPILER_PREFERR_ENUMS */
typedef int __rlimit_resource_t;
typedef int __rusage_who_t;
typedef int __priority_which_t;
#endif /* !__USE_GNU || !__COMPILER_PREFERR_ENUMS */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_prlimit64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(,int,__NOTHROW_NCX,prlimit,(__pid_t __pid, __rlimit_resource_t __resource, struct rlimit const *__new_limit, struct rlimit *__old_limit),prlimit64,(__pid,__resource,__new_limit,__old_limit))
#elif defined(__CRT_HAVE_prlimit) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(,int,__NOTHROW_NCX,prlimit,(__pid_t __pid, __rlimit_resource_t __resource, struct rlimit const *__new_limit, struct rlimit *__old_limit),(__pid,__resource,__new_limit,__old_limit))
#endif /* ... */
#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_prlimit64
__CDECLARE(,int,__NOTHROW_NCX,prlimit64,(__pid_t __pid, __rlimit_resource_t __resource, struct rlimit64 const *__new_limit, struct rlimit64 *__old_limit),(__pid,__resource,__new_limit,__old_limit))
#elif defined(__CRT_HAVE_prlimit) && __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__
__CREDIRECT(,int,__NOTHROW_NCX,prlimit64,(__pid_t __pid, __rlimit_resource_t __resource, struct rlimit64 const *__new_limit, struct rlimit64 *__old_limit),prlimit,(__pid,__resource,__new_limit,__old_limit))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_GNU */
#if defined(__CRT_HAVE_getrlimit64) && defined(__USE_FILE_OFFSET64)
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrlimit,(__rlimit_resource_t __resource, struct rlimit *__rlimits),getrlimit64,(__resource,__rlimits))
#elif defined(__CRT_HAVE_getrlimit) && !defined(__USE_FILE_OFFSET64)
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrlimit,(__rlimit_resource_t __resource, struct rlimit *__rlimits),(__resource,__rlimits))
#elif defined(__CRT_HAVE___getrlimit) && !defined(__USE_FILE_OFFSET64)
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrlimit,(__rlimit_resource_t __resource, struct rlimit *__rlimits),__getrlimit,(__resource,__rlimits))
#endif /* ... */
#if defined(__CRT_HAVE_setrlimit64) && defined(__USE_FILE_OFFSET64)
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,setrlimit,(__rlimit_resource_t __resource, struct rlimit const *__rlimits),setrlimit64,(__resource,__rlimits))
#elif defined(__CRT_HAVE_setrlimit) && !defined(__USE_FILE_OFFSET64)
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,setrlimit,(__rlimit_resource_t __resource, struct rlimit const *__rlimits),(__resource,__rlimits))
#endif /* ... */
#if defined(__CRT_HAVE_getrusage64) && defined(__USE_FILE_OFFSET64)
/* Return resource usage information on process indicated by WHO
 * and put it in *USAGE. Returns 0 for success, -1 for failure */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrusage,(__rusage_who_t __who, struct rusage *__usage),getrusage64,(__who,__usage))
#elif defined(__CRT_HAVE_getrusage) && !defined(__USE_FILE_OFFSET64)
/* Return resource usage information on process indicated by WHO
 * and put it in *USAGE. Returns 0 for success, -1 for failure */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrusage,(__rusage_who_t __who, struct rusage *__usage),(__who,__usage))
#endif /* ... */
#ifdef __USE_TIME_BITS64
#ifdef __CRT_HAVE_getrusage64
/* Return resource usage information on process indicated by WHO
 * and put it in *USAGE. Returns 0 for success, -1 for failure */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrusage64,(__rusage_who_t __who, struct rusage64 *__usage),(__who,__usage))
#elif defined(__CRT_HAVE_getrusage) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Return resource usage information on process indicated by WHO
 * and put it in *USAGE. Returns 0 for success, -1 for failure */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrusage64,(__rusage_who_t __who, struct rusage64 *__usage),getrusage,(__who,__usage))
#endif /* ... */
#endif /* __USE_TIME_BITS64 */
/* Return the highest priority of any process specified by WHICH and
 * WHO (see above); if WHO is zero, the current process, process group,
 * or user (as specified by WHO) is used.  A lower priority number means
 * higher priority. Priorities range from PRIO_MIN to PRIO_MAX (above) */
__CDECLARE_OPT(,int,__NOTHROW_NCX,getpriority,(__priority_which_t __which, id_t __who),(__which,__who))
/* Set the priority of all processes specified by WHICH and WHO (see above) to PRIO.
 * Returns 0 on success, -1 on errors */
__CDECLARE_OPT(,int,__NOTHROW_NCX,setpriority,(__priority_which_t __which, id_t __who, int __prio),(__which,__who,__prio))

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_getrlimit64
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrlimit64,(__rlimit_resource_t __resource, struct rlimit64 *__rlimits),(__resource,__rlimits))
#elif defined(__CRT_HAVE_getrlimit) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,getrlimit64,(__rlimit_resource_t __resource, struct rlimit64 *__rlimits),getrlimit,(__resource,__rlimits))
#endif /* ... */
#ifdef __CRT_HAVE_setrlimit64
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,setrlimit64,(__rlimit_resource_t __resource, struct rlimit64 const *__rlimits),(__resource,__rlimits))
#elif defined(__CRT_HAVE_setrlimit) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,setrlimit64,(__rlimit_resource_t __resource, struct rlimit64 const *__rlimits),setrlimit,(__resource,__rlimits))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_RESOURCE_H */
