/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_KOS_POLL_H
#define _ASM_OS_KOS_POLL_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

/* Flags for `struct pollfd::events' */
#define __POLLIN     0x0001 /* There is data to read. (`read' & friends won't block when invoked) */
#define __POLLPRI    0x0002 /* There is urgent data to read. */
#define __POLLOUT    0x0004 /* Writing now will not block. (`write' & friends won't block when invoked) */
#define __POLLRDNORM 0x0040 /* 100% identical to `POLLIN' (Normal data may be read). */
#define __POLLRDBAND 0x0080 /* Priority data may be read. */
#define __POLLWRNORM 0x0100 /* 100% identical to `POLLOUT' (Writing now will not block). */
#define __POLLWRBAND 0x0200 /* Priority data may be written. */
#define __POLLMSG    0x0400 /* Documented as unused */
#define __POLLREMOVE 0x1000 /* Undocumented & unused */
#define __POLLRDHUP  0x2000 /* Socket peer closed connection, or shut down writing half of its connection */

/* Event types always implicitly polled for.
 * These don't need to be set in `events', but they will appear
 * in  `revents' to indicate their respective status condition. */
#define __POLLERR  0x008 /* Error condition. */
#define __POLLHUP  0x010 /* Hung up. (writes are no longer possible) */
#define __POLLNVAL 0x020 /* Invalid polling request. */

/* Poll events are mapped by select(2) using these macros. */
#define __POLLSELECT_READFDS   (__POLLRDNORM | __POLLRDBAND | __POLLIN | __POLLHUP | __POLLERR) /* select(2).readfds */
#define __POLLSELECT_WRITEFDS  (__POLLWRBAND | __POLLWRNORM | __POLLOUT | __POLLERR)            /* select(2).writefds */
#define __POLLSELECT_EXCEPTFDS (__POLLPRI)                                                      /* select(2).exceptfds */

#endif /* !_ASM_OS_KOS_POLL_H */
