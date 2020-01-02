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
#ifndef	_BITS_LOCAL_LIM_H
#define	_BITS_LOCAL_LIM_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/i386-linux-gnu/bits/local_lim.h' */

#include <__stdinc.h>

/* Minimum guaranteed maximum values for system limits.  Linux version.
   Copyright (C) 1993-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If
   not, see <http://www.gnu.org/licenses/>.  */

#ifndef NR_OPEN
#define __undef_NR_OPEN
#endif /* !NR_OPEN */
#ifndef LINK_MAX
#define __undef_LINK_MAX
#endif /* !LINK_MAX */
#ifndef OPEN_MAX
#define __undef_OPEN_MAX
#endif /* !OPEN_MAX */
#ifndef ARG_MAX
#define __undef_ARG_MAX
#endif /* !ARG_MAX */

#include <linux/limits.h>

#ifdef __undef_NR_OPEN
#undef __undef_NR_OPEN
#undef NR_OPEN
#endif /* __undef_NR_OPEN */
#ifdef __undef_LINK_MAX
#undef __undef_LINK_MAX
#undef LINK_MAX
#endif /* __undef_LINK_MAX */
#ifdef __undef_OPEN_MAX
#undef __undef_OPEN_MAX
#undef OPEN_MAX
#endif /* __undef_OPEN_MAX */
#ifdef __undef_ARG_MAX
#undef __undef_ARG_MAX
#undef ARG_MAX
#endif /* __undef_ARG_MAX */

#define _POSIX_THREAD_KEYS_MAX              128         /* The number of data keys per process. */
#define PTHREAD_KEYS_MAX                    1024        /* This is the value this implementation supports. */
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS 4           /* Controlling the iterations of destructors for thread-specific data. */
#define PTHREAD_DESTRUCTOR_ITERATIONS       _POSIX_THREAD_DESTRUCTOR_ITERATIONS /* Number of iterations this implementation does. */
#define _POSIX_THREAD_THREADS_MAX           64          /* The number of threads per process. */
#undef  PTHREAD_THREADS_MAX                             /* We have no predefined limit on the number of threads. */
#define AIO_PRIO_DELTA_MAX                  20          /* Maximum amount by which a process can decrease its asynchronous I/O priority level. */
#define PTHREAD_STACK_MIN                   16384       /* Minimum size for a thread.  We are free to choose a reasonable value. */
#define DELAYTIMER_MAX                      2147483647  /* Maximum number of timer expiration overruns. */
#define TTY_NAME_MAX                        32          /* Maximum tty name length. */
#define LOGIN_NAME_MAX                      256         /* Maximum login name length.  This is arbitrary. */
#define HOST_NAME_MAX                       64          /* Maximum host name length. */
#define MQ_PRIO_MAX                         32768       /* Maximum message queue priority level. */
#define SEM_VALUE_MAX                       2147483647  /* Maximum value the semaphore can have. */

#endif /* !_BITS_LOCAL_LIM_H */
