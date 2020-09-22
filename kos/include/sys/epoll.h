/* HASH CRC-32:0x8cf2a8aa */
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
#ifndef _SYS_EPOLL_H
#define _SYS_EPOLL_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/epoll.h>
#include <bits/os/epoll.h>
#include <bits/os/sigset.h> /* struct __sigset_struct */
#include <bits/types.h>

#ifdef __USE_GLIBC
#include <sys/types.h>
#include <stdint.h>
#endif /* __USE_GLIBC */


/* Documentation taken from Glibc /usr/include/i386-linux-gnu/sys/epoll.h */
/* Copyright (C) 2002-2016 Free Software Foundation, Inc.
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

__SYSDECL_BEGIN

/* Flags to be passed to `epoll_create1()'. */
#ifdef __EPOLL_CLOEXEC
/*[[[enum]]]*/
#ifdef __CC__
enum {
	EPOLL_CLOEXEC = __EPOLL_CLOEXEC /* Set the IO_CLOEXEC flag */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define EPOLL_CLOEXEC EPOLL_CLOEXEC /* Set the IO_CLOEXEC flag */
#else /* __COMPILER_PREFERR_ENUMS */
#define EPOLL_CLOEXEC __EPOLL_CLOEXEC /* Set the IO_CLOEXEC flag */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __EPOLL_CLOEXEC */

#if (defined(__EPOLLIN) || defined(__EPOLLPRI) ||        \
     defined(__EPOLLOUT) || defined(__EPOLLERR) ||       \
     defined(__EPOLLHUP) || defined(__EPOLLRDNORM) ||    \
     defined(__EPOLLRDBAND) || defined(__EPOLLWRNORM) || \
     defined(__EPOLLWRBAND) || defined(__EPOLLMSG) ||    \
     defined(__EPOLLRDHUP) || defined(__EPOLLWAKEUP) ||  \
     defined(__EPOLLONESHOT) || defined(__EPOLLET))
/*[[[enum]]]*/
#ifdef __CC__
enum EPOLL_EVENTS {
#ifdef __EPOLLIN
	EPOLLIN = __EPOLLIN, /* ... */
#endif /* __EPOLLIN */
#ifdef __EPOLLPRI
	EPOLLPRI = __EPOLLPRI, /* ... */
#endif /* __EPOLLPRI */
#ifdef __EPOLLOUT
	EPOLLOUT = __EPOLLOUT, /* ... */
#endif /* __EPOLLOUT */
#ifdef __EPOLLERR
	EPOLLERR = __EPOLLERR, /* ... */
#endif /* __EPOLLERR */
#ifdef __EPOLLHUP
	EPOLLHUP = __EPOLLHUP, /* ... */
#endif /* __EPOLLHUP */
#ifdef __EPOLLRDNORM
	EPOLLRDNORM = __EPOLLRDNORM, /* ... */
#endif /* __EPOLLRDNORM */
#ifdef __EPOLLRDBAND
	EPOLLRDBAND = __EPOLLRDBAND, /* ... */
#endif /* __EPOLLRDBAND */
#ifdef __EPOLLWRNORM
	EPOLLWRNORM = __EPOLLWRNORM, /* ... */
#endif /* __EPOLLWRNORM */
#ifdef __EPOLLWRBAND
	EPOLLWRBAND = __EPOLLWRBAND, /* ... */
#endif /* __EPOLLWRBAND */
#ifdef __EPOLLMSG
	EPOLLMSG = __EPOLLMSG, /* ... */
#endif /* __EPOLLMSG */
#ifdef __EPOLLRDHUP
	EPOLLRDHUP = __EPOLLRDHUP, /* ... */
#endif /* __EPOLLRDHUP */
#ifdef __EPOLLWAKEUP
	EPOLLWAKEUP = __EPOLLWAKEUP, /* ... */
#endif /* __EPOLLWAKEUP */
#ifdef __EPOLLONESHOT
	EPOLLONESHOT = __EPOLLONESHOT, /* ... */
#endif /* __EPOLLONESHOT */
#ifdef __EPOLLET
	EPOLLET = __EPOLLET /* ... */
#endif /* __EPOLLET */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __EPOLLIN
#define EPOLLIN      EPOLLIN      /* ... */
#endif /* __EPOLLIN */
#ifdef __EPOLLPRI
#define EPOLLPRI     EPOLLPRI     /* ... */
#endif /* __EPOLLPRI */
#ifdef __EPOLLOUT
#define EPOLLOUT     EPOLLOUT     /* ... */
#endif /* __EPOLLOUT */
#ifdef __EPOLLERR
#define EPOLLERR     EPOLLERR     /* ... */
#endif /* __EPOLLERR */
#ifdef __EPOLLHUP
#define EPOLLHUP     EPOLLHUP     /* ... */
#endif /* __EPOLLHUP */
#ifdef __EPOLLRDNORM
#define EPOLLRDNORM  EPOLLRDNORM  /* ... */
#endif /* __EPOLLRDNORM */
#ifdef __EPOLLRDBAND
#define EPOLLRDBAND  EPOLLRDBAND  /* ... */
#endif /* __EPOLLRDBAND */
#ifdef __EPOLLWRNORM
#define EPOLLWRNORM  EPOLLWRNORM  /* ... */
#endif /* __EPOLLWRNORM */
#ifdef __EPOLLWRBAND
#define EPOLLWRBAND  EPOLLWRBAND  /* ... */
#endif /* __EPOLLWRBAND */
#ifdef __EPOLLMSG
#define EPOLLMSG     EPOLLMSG     /* ... */
#endif /* __EPOLLMSG */
#ifdef __EPOLLRDHUP
#define EPOLLRDHUP   EPOLLRDHUP   /* ... */
#endif /* __EPOLLRDHUP */
#ifdef __EPOLLWAKEUP
#define EPOLLWAKEUP  EPOLLWAKEUP  /* ... */
#endif /* __EPOLLWAKEUP */
#ifdef __EPOLLONESHOT
#define EPOLLONESHOT EPOLLONESHOT /* ... */
#endif /* __EPOLLONESHOT */
#ifdef __EPOLLET
#define EPOLLET      EPOLLET      /* ... */
#endif /* __EPOLLET */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __EPOLLIN
#define EPOLLIN      __EPOLLIN      /* ... */
#endif /* __EPOLLIN */
#ifdef __EPOLLPRI
#define EPOLLPRI     __EPOLLPRI     /* ... */
#endif /* __EPOLLPRI */
#ifdef __EPOLLOUT
#define EPOLLOUT     __EPOLLOUT     /* ... */
#endif /* __EPOLLOUT */
#ifdef __EPOLLERR
#define EPOLLERR     __EPOLLERR     /* ... */
#endif /* __EPOLLERR */
#ifdef __EPOLLHUP
#define EPOLLHUP     __EPOLLHUP     /* ... */
#endif /* __EPOLLHUP */
#ifdef __EPOLLRDNORM
#define EPOLLRDNORM  __EPOLLRDNORM  /* ... */
#endif /* __EPOLLRDNORM */
#ifdef __EPOLLRDBAND
#define EPOLLRDBAND  __EPOLLRDBAND  /* ... */
#endif /* __EPOLLRDBAND */
#ifdef __EPOLLWRNORM
#define EPOLLWRNORM  __EPOLLWRNORM  /* ... */
#endif /* __EPOLLWRNORM */
#ifdef __EPOLLWRBAND
#define EPOLLWRBAND  __EPOLLWRBAND  /* ... */
#endif /* __EPOLLWRBAND */
#ifdef __EPOLLMSG
#define EPOLLMSG     __EPOLLMSG     /* ... */
#endif /* __EPOLLMSG */
#ifdef __EPOLLRDHUP
#define EPOLLRDHUP   __EPOLLRDHUP   /* ... */
#endif /* __EPOLLRDHUP */
#ifdef __EPOLLWAKEUP
#define EPOLLWAKEUP  __EPOLLWAKEUP  /* ... */
#endif /* __EPOLLWAKEUP */
#ifdef __EPOLLONESHOT
#define EPOLLONESHOT __EPOLLONESHOT /* ... */
#endif /* __EPOLLONESHOT */
#ifdef __EPOLLET
#define EPOLLET      __EPOLLET      /* ... */
#endif /* __EPOLLET */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

#if (defined(__EPOLL_CTL_ADD) || defined(__EPOLL_CTL_DEL) || \
     defined(__EPOLL_CTL_MOD))
/* Valid opcodes ("op" parameter) to issue to `epoll_ctl()'. */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __epoll_ctl {
#ifdef __EPOLL_CTL_ADD
	EPOLL_CTL_ADD = __EPOLL_CTL_ADD, /* Add a file descriptor to the interface.  */
#endif /* __EPOLL_CTL_ADD */
#ifdef __EPOLL_CTL_DEL
	EPOLL_CTL_DEL = __EPOLL_CTL_DEL, /* Remove a file descriptor from the interface.  */
#endif /* __EPOLL_CTL_DEL */
#ifdef __EPOLL_CTL_MOD
	EPOLL_CTL_MOD = __EPOLL_CTL_MOD  /* Change file descriptor epoll_event structure.  */
#endif /* __EPOLL_CTL_MOD */
} __epoll_ctl_t;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __EPOLL_CTL_ADD
#define EPOLL_CTL_ADD EPOLL_CTL_ADD /* Add a file descriptor to the interface.  */
#endif /* __EPOLL_CTL_ADD */
#ifdef __EPOLL_CTL_DEL
#define EPOLL_CTL_DEL EPOLL_CTL_DEL /* Remove a file descriptor from the interface.  */
#endif /* __EPOLL_CTL_DEL */
#ifdef __EPOLL_CTL_MOD
#define EPOLL_CTL_MOD EPOLL_CTL_MOD /* Change file descriptor epoll_event structure.  */
#endif /* __EPOLL_CTL_MOD */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __EPOLL_CTL_ADD
#define EPOLL_CTL_ADD __EPOLL_CTL_ADD /* Add a file descriptor to the interface.  */
#endif /* __EPOLL_CTL_ADD */
#ifdef __EPOLL_CTL_DEL
#define EPOLL_CTL_DEL __EPOLL_CTL_DEL /* Remove a file descriptor from the interface.  */
#endif /* __EPOLL_CTL_DEL */
#ifdef __EPOLL_CTL_MOD
#define EPOLL_CTL_MOD __EPOLL_CTL_MOD /* Change file descriptor epoll_event structure.  */
#endif /* __EPOLL_CTL_MOD */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#elif defined(__CC__)
typedef int __epoll_ctl_t;
#endif /* ... */

#ifdef __CC__

typedef union epoll_data epoll_data_t;

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

/* Creates an epoll instance.  Returns an fd for the new instance.
 * The "size" parameter is a hint specifying the number of file
 * descriptors to be associated with the new instance. The fd
 * returned by epoll_create() should be closed with close() */
__CDECLARE_OPT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,epoll_create,(__STDC_INT_AS_SIZE_T __size),(__size))
/* Same as epoll_create but with an FLAGS parameter.
 * The unused SIZE parameter has been dropped
 * @param: flags: Set of `EPOLL_*' */
__CDECLARE_OPT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,epoll_create1,(__STDC_INT_AS_UINT_T __flags),(__flags))
/* Manipulate an epoll instance "epfd". Returns 0 in case of success,
 * -1 in case of error (the "errno" variable will contain the
 * specific error code) The "op" parameter is one of the EPOLL_CTL_*
 * constants defined above. The "fd" parameter is the target of the
 * operation. The "event" parameter describes which events the caller
 * is interested in and any associated user data */
__CDECLARE_OPT(,int,__NOTHROW_NCX,epoll_ctl,(__fd_t __epfd, __epoll_ctl_t __op, __fd_t __fd, struct epoll_event *__event),(__epfd,__op,__fd,__event))
/* Wait for events on an epoll instance "epfd". Returns the number of
 * triggered events returned in "events" buffer. Or -1 in case of
 * error with the "errno" variable set to the specific error code. The
 * "events" parameter is a buffer that will contain triggered
 * events. The "maxevents" is the maximum number of events to be
 * returned (usually size of "events"). The "timeout" parameter
 * specifies the maximum wait time in milliseconds (-1 == infinite). */
__CDECLARE_OPT(,int,__NOTHROW_RPC,epoll_wait,(__fd_t __epfd, struct epoll_event *__events, __STDC_INT_AS_SIZE_T __maxevents, int __timeout),(__epfd,__events,__maxevents,__timeout))
/* Same as epoll_wait, but the thread's signal mask is temporarily
 * and atomically replaced with the one provided as parameter */
__CDECLARE_OPT(,int,__NOTHROW_RPC,epoll_pwait,(__fd_t __epfd, struct epoll_event *__events, __STDC_INT_AS_SIZE_T __maxevents, int __timeout, sigset_t const *__ss),(__epfd,__events,__maxevents,__timeout,__ss))
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_EPOLL_H */
