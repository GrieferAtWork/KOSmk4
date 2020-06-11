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

%[define_replacement(fd_t = __fd_t)]
%[default_impl_section(".text.crt.io.poll")]

%{
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

/*[[[enum]]]*/
#ifdef __CC__
enum EPOLL_EVENTS {
	EPOLLIN       = 0x00000001,
	EPOLLPRI      = 0x00000002,
	EPOLLOUT      = 0x00000004,
	EPOLLERR      = 0x00000008,
	EPOLLHUP      = 0x00000010,
	EPOLLRDNORM   = 0x00000040,
	EPOLLRDBAND   = 0x00000080,
	EPOLLWRNORM   = 0x00000100,
	EPOLLWRBAND   = 0x00000200,
	EPOLLMSG      = 0x00000400,
	EPOLLRDHUP    = 0x00002000,
	EPOLLWAKEUP   = 0x20000000,
	EPOLLONESHOT  = 0x40000000,
	EPOLLET       = 0x80000000
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
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
/*[[[end]]]*/

/* Valid opcodes ( "op" parameter ) to issue to epoll_ctl().  */
/*[[[enum]]]*/
#ifdef __CC__
enum __epoll_ctl {
	EPOLL_CTL_ADD = 1, /* Add a file descriptor to the interface.  */
	EPOLL_CTL_DEL = 2, /* Remove a file descriptor from the interface.  */
	EPOLL_CTL_MOD = 3  /* Change file descriptor epoll_event structure.  */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define EPOLL_CTL_ADD EPOLL_CTL_ADD /* Add a file descriptor to the interface.  */
#define EPOLL_CTL_DEL EPOLL_CTL_DEL /* Remove a file descriptor from the interface.  */
#define EPOLL_CTL_MOD EPOLL_CTL_MOD /* Change file descriptor epoll_event structure.  */
#else /* __COMPILER_PREFERR_ENUMS */
#define EPOLL_CTL_ADD 1 /* Add a file descriptor to the interface.  */
#define EPOLL_CTL_DEL 2 /* Remove a file descriptor from the interface.  */
#define EPOLL_CTL_MOD 3 /* Change file descriptor epoll_event structure.  */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#ifdef __CC__

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef __sigset_t sigset_t;
#endif /* !__sigset_t_defined */

}%[push_macro @undef { ptr fd u32 u64 events data }]%{
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
}%[pop_macro]%{

}


@@Creates an epoll instance.  Returns an fd for the new instance.
@@The "size" parameter is a hint specifying the number of file
@@descriptors to be associated with the new instance. The fd
@@returned by epoll_create() should be closed with close()
[[ATTR_WUNUSED, decl_include("<features.h>")]]
$fd_t epoll_create(__STDC_INT_AS_SIZE_T size);

@@Same as epoll_create but with an FLAGS parameter.
@@The unused SIZE parameter has been dropped
@@@param: flags: Set of `EPOLL_*'
[[ATTR_WUNUSED, decl_include("<features.h>")]]
$fd_t epoll_create1(__STDC_INT_AS_UINT_T flags);


@@Manipulate an epoll instance "epfd". Returns 0 in case of success,
@@-1 in case of error (the "errno" variable will contain the
@@specific error code) The "op" parameter is one of the EPOLL_CTL_*
@@constants defined above. The "fd" parameter is the target of the
@@operation. The "event" parameter describes which events the caller
@@is interested in and any associated user data
int epoll_ctl($fd_t epfd, enum __epoll_ctl op,
              $fd_t fd, struct epoll_event *event);


@@Wait for events on an epoll instance "epfd". Returns the number of
@@triggered events returned in "events" buffer. Or -1 in case of
@@error with the "errno" variable set to the specific error code. The
@@"events" parameter is a buffer that will contain triggered
@@events. The "maxevents" is the maximum number of events to be
@@returned (usually size of "events"). The "timeout" parameter
@@specifies the maximum wait time in milliseconds (-1 == infinite).
[[cp, decl_include("<features.h>")]]
int epoll_wait($fd_t epfd, struct epoll_event *events,
               __STDC_INT_AS_SIZE_T maxevents, int timeout);

@@Same as epoll_wait, but the thread's signal mask is temporarily
@@and atomically replaced with the one provided as parameter
[[cp, decl_include("<features.h>")]]
int epoll_pwait($fd_t epfd, struct epoll_event *events,
                __STDC_INT_AS_SIZE_T maxevents, int timeout,
                sigset_t const *ss);



%{
#endif /* __CC__ */

__SYSDECL_END

}