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
#ifndef _ASM_OS_KOS_RESOURCE_H
#define _ASM_OS_KOS_RESOURCE_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __RLIMIT_CPU        0  /* Per-process CPU limit, in seconds. */
#define __RLIMIT_FSIZE      1  /* Largest file that can be created, in bytes. */
#define __RLIMIT_DATA       2  /* Maximum size of data segment, in bytes. */
#define __RLIMIT_STACK      3  /* Maximum size of stack segment, in bytes. */
#define __RLIMIT_CORE       4  /* Largest core file that can be created, in bytes. */
#define __RLIMIT_RSS        5  /* Largest resident set size, in bytes. This affects swapping;
                                * processes that are exceeding their resident set size will
                                * be more likely to have physical memory taken from them. */
#define __RLIMIT_NPROC      6  /* Number of processes. */
#define __RLIMIT_NOFILE     7  /* Number of open files. */
#define __RLIMIT_OFILE      7  /* BSD name for RLIMIT_NOFILE. */
#define __RLIMIT_MEMLOCK    8  /* Locked-in-memory address space. */
#define __RLIMIT_AS         9  /* Address space limit. */
#define __RLIMIT_LOCKS      10 /* Maximum number of file locks. */
#define __RLIMIT_SIGPENDING 11 /* Maximum number of pending signals. */
#define __RLIMIT_MSGQUEUE   12 /* Maximum bytes in POSIX message queues. */
#define __RLIMIT_NICE       13 /* Maximum nice priority allowed to raise to. Nice levels
                                * 19 .. -20 correspond to 0 .. 39 values of this resource
                                * limit. */
#define __RLIMIT_RTPRIO     14 /* Maximum realtime priority allowed for non-privileged processes. */
#define __RLIMIT_RTTIME     15 /* Maximum CPU time in µs that a process scheduled under a real-time
                                * scheduling policy may consume without making a blocking system call
                                * before being forcibly descheduled. */
#define __RLIMIT_NLIMITS    16
#define __RLIM_NLIMITS      16

/* The type of the WHICH argument to `getpriority' and `setpriority',
 * indicating what flavor of entity the WHO argument specifies. */
#define __PRIO_PROCESS 0 /* WHO is a process ID. */
#define __PRIO_PGRP    1 /* WHO is a process group ID. */
#define __PRIO_USER    2 /* WHO is a user ID. */

/* Whose usage statistics do you want?  */
#define __RUSAGE_SELF     0    /* The calling process. */
#define __RUSAGE_CHILDREN (-1) /* All of its terminated child processes. */
#define __RUSAGE_THREAD   1    /* The calling thread. */

/* Priority limits. */
#define __PRIO_MIN (-20) /* Minimum priority a process can have. */
#define __PRIO_MAX 20    /* Maximum priority a process can have. */

#endif /* !_ASM_OS_KOS_RESOURCE_H */
