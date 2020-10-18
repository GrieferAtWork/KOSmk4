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
#ifndef _ASM_OS_KOS_EPOLL_H
#define _ASM_OS_KOS_EPOLL_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

/* EPOLL_EVENTS */
#define __EPOLLIN       0x00000001 /* There is data to read. (`read' & friends won't block when invoked) */
#define __EPOLLPRI      0x00000002 /* There is urgent data to read. */
#define __EPOLLOUT      0x00000004 /* Writing now will not block. (`write' & friends won't block when invoked) */
#define __EPOLLRDNORM   0x00000040 /* 100% identical to `POLLIN' (Normal data may be read). */
#define __EPOLLRDBAND   0x00000080 /* Priority data may be read. */
#define __EPOLLWRNORM   0x00000100 /* 100% identical to `POLLOUT' (Writing now will not block). */
#define __EPOLLWRBAND   0x00000200 /* Priority data may be written. */
#define __EPOLLMSG      0x00000400 /* Documented as unused */
#define __EPOLLRDHUP    0x00002000 /* Socket peer closed connection, or shut down writing half of its connection */
#define __EPOLLWAKEUP   0x20000000 /* Currently ignored */
#define __EPOLLONESHOT  0x40000000 /* Automatically stop monitoring the file descriptor once it's condition is met. */
#define __EPOLLET       0x80000000 /* Enable edge-triggered monitoring (not supported on KOS) */

/* Event types always implicitly polled for. */
#define __EPOLLERR      0x00000008 /* Error condition. */
#define __EPOLLHUP      0x00000010 /* Hung up. (writes are no longer possible) */

/* Command codes for the `op' argument of `epoll_ctl(2)'. */
#define __EPOLL_CTL_ADD 1 /* Add a new file to-be monitored. */
#define __EPOLL_CTL_DEL 2 /* Stop monitoring a given file. */
#define __EPOLL_CTL_MOD 3 /* Change the `struct epoll_event' associated with a given file descriptor. */

/* Flags accepted by `epoll_create1(2)'. */
#define __EPOLL_CLOEXEC 0x80000 /* Set the IO_CLOEXEC flag */

#endif /* !_ASM_OS_KOS_EPOLL_H */
