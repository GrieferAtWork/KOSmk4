/* HASH CRC-32:0xeb51a71 */
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
#ifndef _SYS_EPOLL_H
#define _SYS_EPOLL_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/epoll.h>
#include <bits/sigset.h>
#include <bits/types.h>
#include <sys/types.h>

#include <stdint.h>


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

#ifndef __EPOLL_EVENTS_defined
#define __EPOLL_EVENTS_defined 1
#undef EPOLLIN
#undef EPOLLPRI
#undef EPOLLOUT
#undef EPOLLERR
#undef EPOLLHUP
#undef EPOLLRDNORM
#undef EPOLLRDBAND
#undef EPOLLWRNORM
#undef EPOLLWRBAND
#undef EPOLLMSG
#undef EPOLLRDHUP
#undef EPOLLWAKEUP
#undef EPOLLONESHOT
#undef EPOLLET
#ifdef __CC__
enum EPOLL_EVENTS {
	EPOLLIN      = 0x00000001,
	EPOLLPRI     = 0x00000002,
	EPOLLOUT     = 0x00000004,
	EPOLLERR     = 0x00000008,
	EPOLLHUP     = 0x00000010,
	EPOLLRDNORM  = 0x00000040,
	EPOLLRDBAND  = 0x00000080,
	EPOLLWRNORM  = 0x00000100,
	EPOLLWRBAND  = 0x00000200,
	EPOLLMSG     = 0x00000400,
	EPOLLRDHUP   = 0x00002000,
	EPOLLWAKEUP  = 0x20000000,
	EPOLLONESHOT = 0x40000000,
	EPOLLET      = 0x80000000
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define EPOLLIN      EPOLLIN
#define EPOLLPRI     EPOLLPRI
#define EPOLLOUT     EPOLLOUT
#define EPOLLERR     EPOLLERR
#define EPOLLHUP     EPOLLHUP
#define EPOLLRDNORM  EPOLLRDNORM
#define EPOLLRDBAND  EPOLLRDBAND
#define EPOLLWRNORM  EPOLLWRNORM
#define EPOLLWRBAND  EPOLLWRBAND
#define EPOLLMSG     EPOLLMSG
#define EPOLLRDHUP   EPOLLRDHUP
#define EPOLLWAKEUP  EPOLLWAKEUP
#define EPOLLONESHOT EPOLLONESHOT
#define EPOLLET      EPOLLET
#else /* __COMPILER_PREFERR_ENUMS */
#define EPOLLIN      0x00000001
#define EPOLLPRI     0x00000002
#define EPOLLOUT     0x00000004
#define EPOLLERR     0x00000008
#define EPOLLHUP     0x00000010
#define EPOLLRDNORM  0x00000040
#define EPOLLRDBAND  0x00000080
#define EPOLLWRNORM  0x00000100
#define EPOLLWRBAND  0x00000200
#define EPOLLMSG     0x00000400
#define EPOLLRDHUP   0x00002000
#define EPOLLWAKEUP  0x20000000
#define EPOLLONESHOT 0x40000000
#define EPOLLET      0x80000000
#endif /* !__COMPILER_PREFERR_ENUMS */
#endif /* !__EPOLL_EVENTS_defined */

/* Valid opcodes ( "op" parameter ) to issue to epoll_ctl().  */
#ifndef ____epoll_ctl_defined
#define ____epoll_ctl_defined 1
#undef EPOLL_CTL_ADD
#undef EPOLL_CTL_DEL
#undef EPOLL_CTL_MOD
#ifdef __CC__
enum __epoll_ctl {
	EPOLL_CTL_ADD = 1, /* Add a file descriptor to the interface. */
	EPOLL_CTL_DEL = 2, /* Remove a file descriptor from the interface. */
	EPOLL_CTL_MOD = 3 /* Change file descriptor epoll_event structure. */
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define EPOLL_CTL_ADD EPOLL_CTL_ADD /* Add a file descriptor to the interface. */
#define EPOLL_CTL_DEL EPOLL_CTL_DEL /* Remove a file descriptor from the interface. */
#define EPOLL_CTL_MOD EPOLL_CTL_MOD /* Change file descriptor epoll_event structure. */
#else /* __COMPILER_PREFERR_ENUMS */
#define EPOLL_CTL_ADD 1 /* Add a file descriptor to the interface. */
#define EPOLL_CTL_DEL 2 /* Remove a file descriptor from the interface. */
#define EPOLL_CTL_MOD 3 /* Change file descriptor epoll_event structure. */
#endif /* !__COMPILER_PREFERR_ENUMS */
#endif /* !____epoll_ctl_defined */

#ifdef __CC__

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef __sigset_t sigset_t;
#endif /* !__sigset_t_defined */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("ptr")
#pragma push_macro("fd")
#pragma push_macro("u32")
#pragma push_macro("u64")
#pragma push_macro("events")
#pragma push_macro("data")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef ptr
#undef fd
#undef u32
#undef u64
#undef events
#undef data
typedef union epoll_data {
	void      *ptr;
	int        fd;
	__uint32_t u32;
	__uint64_t u64;
} epoll_data_t;

#ifndef __EPOLL_PACKED
#define __EPOLL_PACKED /* nothing */
#endif /* !__EPOLL_PACKED */

struct __EPOLL_PACKED epoll_event {
	__uint32_t   events; /* Epoll events (Set of `EPOLL*'; s.a. `EPOLL_EVENTS') */
	epoll_data_t data;   /* User data variable */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("data")
#pragma pop_macro("events")
#pragma pop_macro("u64")
#pragma pop_macro("u32")
#pragma pop_macro("fd")
#pragma pop_macro("ptr")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifdef __CRT_HAVE_epoll_create
/* Creates an epoll instance.  Returns an fd for the new instance.
 * The "size" parameter is a hint specifying the number of file
 * descriptors to be associated with the new instance. The fd
 * returned by epoll_create() should be closed with close() */
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,epoll_create,(int __size),(__size))
#endif /* epoll_create... */
#ifdef __CRT_HAVE_epoll_create1
/* Same as epoll_create but with an FLAGS parameter.
 * The unused SIZE parameter has been dropped
 * @param: flags: Set of `EPOLL_*' */
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,epoll_create1,(int __flags),(__flags))
#endif /* epoll_create1... */
#ifdef __CRT_HAVE_epoll_ctl
/* Manipulate an epoll instance "epfd". Returns 0 in case of success,
 * -1 in case of error (the "errno" variable will contain the
 * specific error code) The "op" parameter is one of the EPOLL_CTL_*
 * constants defined above. The "fd" parameter is the target of the
 * operation. The "event" parameter describes which events the caller
 * is interested in and any associated user data */
__CDECLARE(,int,__NOTHROW_NCX,epoll_ctl,(__fd_t __epfd, enum __epoll_ctl __op, __fd_t __fd, struct epoll_event *__event),(__epfd,__op,__fd,__event))
#endif /* epoll_ctl... */
#ifdef __CRT_HAVE_epoll_wait
/* Wait for events on an epoll instance "epfd". Returns the number of
 * triggered events returned in "events" buffer. Or -1 in case of
 * error with the "errno" variable set to the specific error code. The
 * "events" parameter is a buffer that will contain triggered
 * events. The "maxevents" is the maximum number of events to be
 * returned (usually size of "events"). The "timeout" parameter
 * specifies the maximum wait time in milliseconds (-1 == infinite). */
__CDECLARE(,int,__NOTHROW_RPC,epoll_wait,(__fd_t __epfd, struct epoll_event *__events, int __maxevents, int __timeout),(__epfd,__events,__maxevents,__timeout))
#endif /* epoll_wait... */
#ifdef __CRT_HAVE_epoll_pwait
/* Same as epoll_wait, but the thread's signal mask is temporarily
 * and atomically replaced with the one provided as parameter */
__CDECLARE(,int,__NOTHROW_RPC,epoll_pwait,(__fd_t __epfd, struct epoll_event *__events, int __maxevents, int __timeout, sigset_t const *__ss),(__epfd,__events,__maxevents,__timeout,__ss))
#endif /* epoll_pwait... */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_EPOLL_H */
