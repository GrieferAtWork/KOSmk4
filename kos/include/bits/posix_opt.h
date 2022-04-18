/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: GNU C Library (/bits/posix_opt.h) */
/* (#) Portability: mintlib       (/include/bits/posix_opt.h) */
#ifndef _BITS_POSIX_OPT_H
#define _BITS_POSIX_OPT_H 1

/* NOTE: This file must _always_ be kept for GLibc compatibility! */

#include <__stdinc.h>
#include <__crt.h>
#include <asm/os/termios.h> /* __VDISABLE */

#ifndef __VDISABLE
#define __VDISABLE '\0'
#endif /* !__VDISABLE */

#if defined(__CRT_HAVE_setpgid)
#define _POSIX_JOB_CONTROL                   1 /* Job control is supported. */
#endif
#if defined(__CRT_HAVE_setreuid)
#define _POSIX_SAVED_IDS                     1 /* Processes have a saved set-user-ID and a saved set-group-ID. */
#endif
#if defined(__CRT_HAVE_nice) || 1
#define _POSIX_PRIORITY_SCHEDULING           200809L /* Priority scheduling is supported. */
#endif
#if defined(__CRT_HAVE_fsync) || defined(__CRT_HAVE_fdatasync) || defined(__CRT_HAVE__commit) || 1
#define _POSIX_SYNCHRONIZED_IO               200809L /* Synchronizing file data is supported. */
#define _POSIX_FSYNC                         200809L /* The fsync function is present. */
#endif
#if defined(__CRT_HAVE_mmap) || defined(__CRT_HAVE_mmap64)
#define _POSIX_MAPPED_FILES                  200809L /* Mapping of files to memory is supported. */
#endif
#if defined(__CRT_HAVE_mlock)
#define _POSIX_MEMLOCK                       200809L /* Locking of all memory is supported. */
#define _POSIX_MEMLOCK_RANGE                 200809L /* Locking of ranges of memory is supported. */
#endif
#if defined(__CRT_HAVE_mprotect)
#define _POSIX_MEMORY_PROTECTION             200809L /* Setting of memory protections is supported. */
#endif
#define _POSIX_CHOWN_RESTRICTED              0       /* Some filesystems allow all users to change file ownership. */
#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE                      __VDISABLE /* `c_cc' member of `struct termios' structure can be disabled by using the value _POSIX_VDISABLE. */
#endif /* !_POSIX_VDISABLE */
#define _POSIX_NO_TRUNC                      1       /* Filenames are not silently truncated. */
#if 0
#define _XOPEN_REALTIME                      1       /* X/Open realtime support is available. */
#define _XOPEN_REALTIME_THREADS              1       /* X/Open thread realtime support is available. */
#endif
#define _XOPEN_SHM                           1       /* XPG4.2 shared memory is supported. */
#if defined(__CRT_HAVE_pthread_self)
#define _POSIX_THREADS                       200809L /* Tell we have POSIX threads. */
#endif
#define _POSIX_REENTRANT_FUNCTIONS           1       /* We have the reentrant functions described in POSIX. */
#define _POSIX_THREAD_SAFE_FUNCTIONS         200809L
#define _POSIX_THREAD_PRIORITY_SCHEDULING    200809L /* We provide priority scheduling for threads. */
#define _POSIX_THREAD_ATTR_STACKSIZE         200809L /* We support user-defined stack sizes. */
#define _POSIX_THREAD_ATTR_STACKADDR         200809L /* We support user-defined stacks. */
#define _POSIX_THREAD_PRIO_INHERIT           200809L /* We support priority inheritance. */
#define _POSIX_THREAD_PRIO_PROTECT           200809L /* We support priority protection, though only for non-robust mutexes. */
#ifdef __USE_XOPEN2K8
#define _POSIX_THREAD_ROBUST_PRIO_INHERIT    200809L /* We support priority inheritance for robust mutexes. */
#define _POSIX_THREAD_ROBUST_PRIO_PROTECT   (-1)     /* We do not support priority protection for robust mutexes. */
#endif
#if defined(__CRT_HAVE_sem_init)
#define _POSIX_SEMAPHORES                    200809L /* We support POSIX.1b semaphores. */
#endif
#if defined(__CRT_HAVE___libc_allocate_rtsig) || 1
#define _POSIX_REALTIME_SIGNALS              200809L /* Real-time signals are supported. */
#endif
#if defined(__CRT_HAVE_aio_read) || 1
#define _POSIX_ASYNCHRONOUS_IO               200809L /* We support asynchronous I/O. */
#define _POSIX_ASYNC_IO                      1
#define _LFS_ASYNCHRONOUS_IO                 1       /* Alternative name for Unix98. */
#endif
#define _POSIX_PRIORITIZED_IO                200809L /* Support for prioritization is also available. */
#if defined(__CRT_HAVE_open64)
#ifdef _LFS_ASYNCHRONOUS_IO
#define _LFS64_ASYNCHRONOUS_IO               1       /* The LFS support in asynchronous I/O is also available. */
#endif /* _LFS_ASYNCHRONOUS_IO */
#define _LFS_LARGEFILE                       1       /* The rest of the LFS is also available. */
#define _LFS64_LARGEFILE                     1
#endif
#if defined(__CRT_HAVE_fopen64)
#define _LFS64_STDIO                         1
#endif
#if defined(__CRT_HAVE_shm_open)
#define _POSIX_SHARED_MEMORY_OBJECTS         200809L /* POSIX shared memory objects are implemented. */
#endif
#define _POSIX_CPUTIME                       0       /* CPU-time clocks support needs to be checked at runtime. */
#define _POSIX_THREAD_CPUTIME                0       /* Clock support in threads must be also checked at runtime. */
#define _POSIX_REGEXP                        1       /* GNU libc provides regular expression handling. */
#define _POSIX_READER_WRITER_LOCKS           200809L /* Reader/Writer locks are available. */
#if defined(__CRT_HAVE_system)
#define _POSIX_SHELL                         1       /* We have a POSIX shell. */
#endif
#define _POSIX_TIMEOUTS                      200809L /* We support the Timeouts option. */
#define _POSIX_SPIN_LOCKS                    200809L /* We support spinlocks. */
#ifdef __CRT_HAVE_posix_spawn
#define _POSIX_SPAWN                         200809L /* The `spawn' function family is supported. */
#endif /* __CRT_HAVE_posix_spawn */
#define _POSIX_TIMERS                        200809L /* We have POSIX timers. */
#define _POSIX_BARRIERS                      200809L /* The barrier functions are available. */
#define _POSIX_MESSAGE_PASSING               200809L /* POSIX message queues are available. */
#define _POSIX_THREAD_PROCESS_SHARED         200809L /* Thread process-shared synchronization is supported. */
#define _POSIX_MONOTONIC_CLOCK               0       /* The monotonic clock might be available. */
#define _POSIX_CLOCK_SELECTION               200809L /* The clock selection interfaces are available. */
#define _POSIX_ADVISORY_INFO                 200809L /* Advisory information interfaces are available. */
#define _POSIX_IPV6                          200809L /* IPv6 support is available. */
#define _POSIX_RAW_SOCKETS                   200809L /* Raw socket support is available. */
#if defined(__CRT_HAVE_isatty) || defined(__CRT_HAVE__isatty)
#define _POSIX2_CHAR_TERM                    200809L /* We have at least one terminal. */
#endif
#define _POSIX_SPORADIC_SERVER             (-1)      /* Neither process nor thread sporadic server interfaces is available. */
#define _POSIX_THREAD_SPORADIC_SERVER      (-1)      /* Neither process nor thread sporadic server interfaces is available. */
#define _POSIX_TRACE                       (-1)      /* trace.h is not available. */
#define _POSIX_TRACE_EVENT_FILTER          (-1)
#define _POSIX_TRACE_INHERIT               (-1)
#define _POSIX_TRACE_LOG                   (-1)
#define _POSIX_TYPED_MEMORY_OBJECTS        (-1)      /* Typed memory objects are not available. */

#endif /* !_BITS_POSIX_OPT_H */
