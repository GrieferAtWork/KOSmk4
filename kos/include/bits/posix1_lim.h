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
#ifndef	_BITS_POSIX1_LIM_H
#define	_BITS_POSIX1_LIM_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/i386-linux-gnu/bits/posix1_lim.h' */

#include <__stdinc.h>

/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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

/* These are the standard-mandated minimum values.
 * >> KOS implements most of these as dynamic re-configurables,
 *    or infinites only restricted by available memory. */

#ifndef _POSIX_AIO_LISTIO_MAX
#define _POSIX_AIO_LISTIO_MAX  2    /* Minimum number of operations in one list I/O call. */
#endif /* !_POSIX_AIO_LISTIO_MAX */
#ifndef _POSIX_AIO_MAX
#define _POSIX_AIO_MAX         1    /* Minimal number of outstanding asynchronous I/O operations. */
#endif /* !_POSIX_AIO_MAX */
#ifndef _POSIX_ARG_MAX
#define _POSIX_ARG_MAX         4096 /* Maximum length of arguments to `execve', including environment. */
#endif /* !_POSIX_ARG_MAX */
#ifndef _POSIX_DELAYTIMER_MAX
#define _POSIX_DELAYTIMER_MAX  32   /* Minimal number of timer expiration overruns. */
#endif /* !_POSIX_DELAYTIMER_MAX */
#ifndef _POSIX_HOST_NAME_MAX
#define _POSIX_HOST_NAME_MAX   255  /* Maximum length of a host name (not including the terminating null) as returned from the GETHOSTNAME function. */
#endif /* !_POSIX_HOST_NAME_MAX */
#ifndef _POSIX_LINK_MAX
#define _POSIX_LINK_MAX        8    /* Maximum link count of a file. */
#endif /* !_POSIX_LINK_MAX */
#ifndef _POSIX_LOGIN_NAME_MAX
#define _POSIX_LOGIN_NAME_MAX  9    /* Maximum length of login name. */
#endif /* !_POSIX_LOGIN_NAME_MAX */
#ifndef _POSIX_MAX_CANON
#define _POSIX_MAX_CANON       255  /* Number of bytes in a terminal canonical input queue. */
#endif /* !_POSIX_MAX_CANON */
#ifndef _POSIX_MAX_INPUT
#define _POSIX_MAX_INPUT       255  /* Number of bytes for which space will be available in a terminal input queue. */
#endif /* !_POSIX_MAX_INPUT */
#ifndef _POSIX_MQ_OPEN_MAX
#define _POSIX_MQ_OPEN_MAX     8    /* Maximum number of message queues open for a process. */
#endif /* !_POSIX_MQ_OPEN_MAX */
#ifndef _POSIX_MQ_PRIO_MAX
#define _POSIX_MQ_PRIO_MAX     32   /* Maximum number of supported message priorities. */
#endif /* !_POSIX_MQ_PRIO_MAX */
#ifndef _POSIX_NAME_MAX
#define _POSIX_NAME_MAX        14   /* Number of bytes in a filename. */
#endif /* !_POSIX_NAME_MAX */
#ifdef __USE_XOPEN2K
#ifndef _POSIX_CHILD_MAX
#define _POSIX_CHILD_MAX    25   /* Maximum simultaneous processes per real user ID. */
#endif /* !_POSIX_CHILD_MAX */
#ifndef _POSIX_NGROUPS_MAX
#define _POSIX_NGROUPS_MAX  8    /* Number of simultaneous supplementary group IDs per process. */
#endif /* !_POSIX_NGROUPS_MAX */
#ifndef _POSIX_OPEN_MAX
#define _POSIX_OPEN_MAX     20   /* Number of files one process can have open at once. */
#endif /* !_POSIX_OPEN_MAX */
#ifndef _POSIX_TZNAME_MAX
#define _POSIX_TZNAME_MAX   6   /* Maximum length of a timezone name (element of `tzname'). */
#endif /* !_POSIX_TZNAME_MAX */
#else /* !__USE_XOPEN2K */
#ifndef _POSIX_CHILD_MAX
#define _POSIX_CHILD_MAX    6    /* Maximum simultaneous processes per real user ID. */
#endif /* !_POSIX_CHILD_MAX */
#ifndef _POSIX_NGROUPS_MAX
#define _POSIX_NGROUPS_MAX  0    /* Number of simultaneous supplementary group IDs per process. */
#endif /* !_POSIX_NGROUPS_MAX */
#ifndef _POSIX_OPEN_MAX
#define _POSIX_OPEN_MAX     16   /* Number of files one process can have open at once. */
#endif /* !_POSIX_OPEN_MAX */
#ifndef _POSIX_TZNAME_MAX
#define _POSIX_TZNAME_MAX   3   /* Maximum length of a timezone name (element of `tzname'). */
#endif /* !_POSIX_TZNAME_MAX */
#endif /* !__USE_XOPEN2K */
#if !defined(__USE_XOPEN2K) || defined(__USE_GNU)
#ifndef _POSIX_FD_SETSIZE
#define _POSIX_FD_SETSIZE   _POSIX_OPEN_MAX /* Number of descriptors that a process may examine with `pselect' or `select'. */
#endif /* !_POSIX_FD_SETSIZE */
#ifndef _POSIX_QLIMIT
#define _POSIX_QLIMIT       1   /* Maximum number of connections that can be queued on a socket. */
#endif /* !_POSIX_QLIMIT */
#ifndef _POSIX_HIWAT
#define _POSIX_HIWAT        _POSIX_PIPE_BUF /* Maximum number of bytes that can be buffered on a socket for send or receive. */
#endif /* !_POSIX_HIWAT */
#ifndef _POSIX_UIO_MAXIOV
#define _POSIX_UIO_MAXIOV    16 /* Maximum number of elements in an `iovec' array. */
#endif /* !_POSIX_UIO_MAXIOV */
#endif /* !__USE_XOPEN2K || __USE_GNU */
#ifndef _POSIX_PATH_MAX
#define _POSIX_PATH_MAX        256 /* Number of bytes in a pathname. */
#endif /* !_POSIX_PATH_MAX */
#ifndef _POSIX_PIPE_BUF
#define _POSIX_PIPE_BUF        512 /* Number of bytes than can be written atomically to a pipe. */
#endif /* !_POSIX_PIPE_BUF */
#ifndef _POSIX_RE_DUP_MAX
#define _POSIX_RE_DUP_MAX      255 /* The number of repeated occurrences of a BRE permitted by the REGEXEC and REGCOMP functions when using the interval notation. */
#endif /* !_POSIX_RE_DUP_MAX */
#ifndef _POSIX_RTSIG_MAX
#define _POSIX_RTSIG_MAX       8   /* Minimal number of realtime signals reserved for the application. */
#endif /* !_POSIX_RTSIG_MAX */
#ifndef _POSIX_SEM_NSEMS_MAX
#define _POSIX_SEM_NSEMS_MAX   256 /* Number of semaphores a process can have. */
#endif /* !_POSIX_SEM_NSEMS_MAX */
#ifndef _POSIX_SEM_VALUE_MAX
#define _POSIX_SEM_VALUE_MAX   32767 /* Maximal value of a semaphore. */
#endif /* !_POSIX_SEM_VALUE_MAX */
#ifndef _POSIX_SIGQUEUE_MAX
#define _POSIX_SIGQUEUE_MAX    32  /* Number of pending realtime signals. */
#endif /* !_POSIX_SIGQUEUE_MAX */
#ifndef _POSIX_SSIZE_MAX
#define _POSIX_SSIZE_MAX       32767 /* Largest value of a `ssize_t'. */
#endif /* !_POSIX_SSIZE_MAX */
#ifndef _POSIX_STREAM_MAX
#define _POSIX_STREAM_MAX      8   /* Number of streams a process can have open at once. */
#endif /* !_POSIX_STREAM_MAX */
#ifndef _POSIX_SYMLINK_MAX
#define _POSIX_SYMLINK_MAX     255 /* The number of bytes in a symbolic link. */
#endif /* !_POSIX_SYMLINK_MAX */
#ifndef _POSIX_SYMLOOP_MAX
#define _POSIX_SYMLOOP_MAX     8   /* The number of symbolic links that can be traversed in the resolution of a pathname in the absence of a loop. */
#endif /* !_POSIX_SYMLOOP_MAX */
#ifndef _POSIX_TIMER_MAX
#define _POSIX_TIMER_MAX       32  /* Number of timer for a process. */
#endif /* !_POSIX_TIMER_MAX */
#ifndef _POSIX_TTY_NAME_MAX
#define _POSIX_TTY_NAME_MAX    9   /* Maximum number of characters in a tty name. */
#endif /* !_POSIX_TTY_NAME_MAX */
#ifndef _POSIX_CLOCKRES_MIN
#define _POSIX_CLOCKRES_MIN    20000000 /* Maximum clock resolution in nanoseconds. */
#endif /* !_POSIX_CLOCKRES_MIN */

/* Get the implementation-specific values for the above. */
#include <bits/local_lim.h>

#ifndef SSIZE_MAX
#include <hybrid/typecore.h>
#define SSIZE_MAX              __SSIZE_MAX__
#endif /* !SSIZE_MAX */

#ifndef NGROUPS_MAX
/* This value is a guaranteed minimum maximum.
 * The current maximum can be got from `sysconf'. */
#define NGROUPS_MAX            8
#endif /* !NGROUPS_MAX */

#endif /* !_BITS_POSIX1_LIM_H */
