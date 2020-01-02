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

%[define_replacement(pid_t = __pid_t)]
%[default_impl_section(.text.crt.sched.resource)]

%{
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
}%[enum @guard @undef @macro __rlimit_resource {
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
}]%{

/* Value to indicate that there is no limit. */
#define RLIM_INFINITY     (__CCAST(__FS_TYPE(rlim))-1)
#ifdef __USE_LARGEFILE64
#define RLIM64_INFINITY   (__CCAST(__rlim64_t)-1)
#endif

/* We can represent all limits. */
#ifndef RLIM_SAVED_MAX
#define RLIM_SAVED_MAX    RLIM_INFINITY
#endif /* !RLIM_SAVED_MAX */
#ifndef RLIM_SAVED_CUR
#define RLIM_SAVED_CUR    RLIM_INFINITY
#endif /* !RLIM_SAVED_CUR */


/* The type of the WHICH argument to `getpriority' and `setpriority',
 * indicating what flavor of entity the WHO argument specifies. */
}%[enum @guard @undef @macro __priority_which {
	PRIO_PROCESS = 0, /* WHO is a process ID. */
	PRIO_PGRP    = 1, /* WHO is a process group ID. */
	PRIO_USER    = 2  /* WHO is a user ID. */
}]%{


/* Whose usage statistics do you want?  */
}%[enum @guard @undef @macro __rusage_who {
	RUSAGE_SELF     =  0, /* The calling process. */
	RUSAGE_CHILDREN = -1, /* All of its terminated child processes. */
%#ifdef __USE_GNU
	RUSAGE_THREAD   =  1  /* The calling thread. */
%#endif /* __USE_GNU */
}]%{

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

}

%#ifdef __USE_GNU
%#ifdef __COMPILER_PREFERR_ENUMS
%typedef enum __rlimit_resource __rlimit_resource_t;
%#else /* __COMPILER_PREFERR_ENUMS */
%typedef int __rlimit_resource_t;
%#endif /* !__COMPILER_PREFERR_ENUMS */
%
prlimit:($pid_t pid, __rlimit_resource_t resource, struct rlimit const *new_limit, struct rlimit *old_limit) -> int;
%#ifdef __USE_LARGEFILE64
[rlim64_variant_of(prlimit)]
prlimit64:($pid_t pid, __rlimit_resource_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) -> int;
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_GNU */


%{

#endif /* __CC__ */

__SYSDECL_END

}