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
#ifndef _BITS_POLL_H
#define _BITS_POLL_H 1

#include <__stdinc.h>
#include <features.h>

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

__SYSDECL_BEGIN

/* Event types that can be polled for. These bits may be set in `events'
 * to indicate the interesting event types; they will appear in `revents'
 * to indicate the status of the file descriptor. */
#ifndef POLLIN
#define POLLIN         0x001 /* There is data to read. */
#endif /* !POLLIN */
#ifndef POLLPRI
#define POLLPRI        0x002 /* There is urgent data to read. */
#endif /* !POLLPRI */
#ifndef POLLOUT
#define POLLOUT        0x004 /* Writing now will not block. */
#endif /* !POLLOUT */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
/* These values are defined in XPG4.2. */
#ifndef POLLRDNORM
#define POLLRDNORM  0x040 /* Normal data may be read. */
#endif /* !POLLRDNORM */
#ifndef POLLRDBAND
#define POLLRDBAND  0x080 /* Priority data may be read. */
#endif /* !POLLRDBAND */
#ifndef POLLWRNORM
#define POLLWRNORM  0x100 /* Writing now will not block. */
#endif /* !POLLWRNORM */
#ifndef POLLWRBAND
#define POLLWRBAND  0x200 /* Priority data may be written. */
#endif /* !POLLWRBAND */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

#ifdef __USE_GNU
/* These are extensions for Linux. */
#ifndef POLLMSG
#define POLLMSG     0x0400
#endif /* !POLLMSG */
#ifndef POLLREMOVE
#define POLLREMOVE  0x1000
#endif /* !POLLREMOVE */
#ifndef POLLRDHUP
#define POLLRDHUP   0x2000
#endif /* !POLLRDHUP */
#endif /* __USE_GNU */

/* Event types always implicitly polled for. These bits need
 * not be set in `events', but they will appear in `revents'
 * to indicate the status of the file descriptor. */
#ifndef POLLERR
#define POLLERR        0x008 /* Error condition. */
#endif /* !POLLERR */
#ifndef POLLHUP
#define POLLHUP        0x010 /* Hung up. */
#endif /* !POLLHUP */
#ifndef POLLNVAL
#define POLLNVAL       0x020 /* Invalid polling request. */
#endif /* !POLLNVAL */

__SYSDECL_END

#endif /* !_BITS_POLL_H */
