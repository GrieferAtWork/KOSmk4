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
#ifndef _ASM_EPOLL_H
#define _ASM_EPOLL_H 1

#include <__crt.h>

#if defined(__KOS__) || defined(__linux__)

/* EPOLL_EVENTS */
#define __EPOLLIN       0x00000001 /* ... */
#define __EPOLLPRI      0x00000002 /* ... */
#define __EPOLLOUT      0x00000004 /* ... */
#define __EPOLLERR      0x00000008 /* ... */
#define __EPOLLHUP      0x00000010 /* ... */
#define __EPOLLRDNORM   0x00000040 /* ... */
#define __EPOLLRDBAND   0x00000080 /* ... */
#define __EPOLLWRNORM   0x00000100 /* ... */
#define __EPOLLWRBAND   0x00000200 /* ... */
#define __EPOLLMSG      0x00000400 /* ... */
#define __EPOLLRDHUP    0x00002000 /* ... */
#define __EPOLLWAKEUP   0x20000000 /* ... */
#define __EPOLLONESHOT  0x40000000 /* ... */
#define __EPOLLET       0x80000000 /* ... */

/* Valid opcodes ("op" parameter) to issue to `epoll_ctl()'. */
#define __EPOLL_CTL_ADD 1 /* Add a file descriptor to the interface. */
#define __EPOLL_CTL_DEL 2 /* Remove a file descriptor from the interface. */
#define __EPOLL_CTL_MOD 3 /* Change file descriptor epoll_event structure. */

/* Flags to be passed to `epoll_create1()'. */
#define __EPOLL_CLOEXEC 0x80000 /* Set the IO_CLOEXEC flag */

#endif /* __KOS__ || __linux__ */

#endif /* !_ASM_EPOLL_H */
