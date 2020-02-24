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
#ifndef _ASM_POLL_H
#define _ASM_POLL_H 1

#include <__crt.h>
#include <__stdinc.h>

/* Documentation derived from GLibc, but later modified */
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
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

#if defined(__KOS__) || defined(__linux__) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL) || defined(__CRT_GLC)

/* Event types that can be polled for. These bits may be set in `events'
 * to indicate the interesting event types; they will appear in `revents'
 * to indicate the status of the file descriptor. */
#define __POLLIN  0x001 /* There is data to read. */
#define __POLLPRI 0x002 /* There is urgent data to read. */
#define __POLLOUT 0x004 /* Writing now will not block. */

/* These values are defined in XPG4.2. */
#define __POLLRDNORM 0x040 /* 100% identical to `POLLIN' (Normal data may be read). */
#define __POLLRDBAND 0x080 /* Priority data may be read. */
#define __POLLWRNORM 0x100 /* 100% identical to `POLLOUT' (Writing now will not block). */
#define __POLLWRBAND 0x200 /* Priority data may be written. */

/* These are extensions for Linux. */
#define __POLLMSG    0x0400 /* Documented as unused */
#define __POLLREMOVE 0x1000 /* Undocumented & unused */
#define __POLLRDHUP  0x2000 /* Socket peer closed connection, or shut down writing half of its connection */

/* Event types always implicitly polled for. These bits need
 * not be set in `events', but they will appear in `revents'
 * to indicate the status of the file descriptor. */
#define __POLLERR  0x008 /* Error condition. */
#define __POLLHUP  0x010 /* Hung up. (writes are no longer possible) */
#define __POLLNVAL 0x020 /* Invalid polling request. */

/* Poll events are mapped by select(2) using these macros. */
#define __POLLSELECT_READFDS   (__POLLRDNORM | __POLLRDBAND | __POLLIN | __POLLHUP | __POLLERR) /* readfds */
#define __POLLSELECT_WRITEFDS  (__POLLWRBAND | __POLLWRNORM | __POLLOUT | __POLLERR) /* writefds */
#define __POLLSELECT_EXCEPTFDS (__POLLPRI) /* exceptfds */

#endif /* ... */

#endif /* !_ASM_POLL_H */
