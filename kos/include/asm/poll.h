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
/* (#) Portability: Linux (/usr/include/[...]/asm/poll.h) */
#ifndef _ASM_POLL_H
#define _ASM_POLL_H 1

#include <asm/os/poll.h>
#include <bits/os/pollfd.h>

/* Flags for `struct pollfd::events' */
#if !defined(POLLIN) && defined(__POLLIN)
#define POLLIN  __POLLIN  /* There is data to read. (`read' & friends won't block when invoked) */
#endif /* !POLLIN && __POLLIN */
#if !defined(POLLPRI) && defined(__POLLPRI)
#define POLLPRI __POLLPRI /* There is urgent data to read. */
#endif /* !POLLPRI && __POLLPRI */
#if !defined(POLLOUT) && defined(__POLLOUT)
#define POLLOUT __POLLOUT /* Writing now will not block. (`write' & friends won't block when invoked) */
#endif /* !POLLOUT && __POLLOUT */

/* Event types always implicitly polled for.
 * These don't need to be set in `events', but they will appear
 * in  `revents' to indicate their respective status condition. */
#if !defined(POLLERR) && defined(__POLLERR)
#define POLLERR  __POLLERR  /* Error condition. */
#endif /* !POLLERR && __POLLERR */
#if !defined(POLLHUP) && defined(__POLLHUP)
#define POLLHUP  __POLLHUP  /* Hung up. (writes are no longer possible) */
#endif /* !POLLHUP && __POLLHUP */
#if !defined(POLLNVAL) && defined(__POLLNVAL)
#define POLLNVAL __POLLNVAL /* Invalid polling request. */
#endif /* !POLLNVAL && __POLLNVAL */

/* These values are defined in XPG4.2. */
#if !defined(POLLRDNORM) && defined(__POLLRDNORM)
#define POLLRDNORM __POLLRDNORM /* 100% identical to `POLLIN' (Normal data may be read). */
#endif /* !POLLRDNORM && __POLLRDNORM */
#if !defined(POLLRDBAND) && defined(__POLLRDBAND)
#define POLLRDBAND __POLLRDBAND /* Priority data may be read. */
#endif /* !POLLRDBAND && __POLLRDBAND */
#if !defined(POLLWRNORM) && defined(__POLLWRNORM)
#define POLLWRNORM __POLLWRNORM /* 100% identical to `POLLOUT' (Writing now will not block). */
#endif /* !POLLWRNORM && __POLLWRNORM */
#if !defined(POLLWRBAND) && defined(__POLLWRBAND)
#define POLLWRBAND __POLLWRBAND /* Priority data may be written. */
#endif /* !POLLWRBAND && __POLLWRBAND */

/* Linux (and KOS)-specific extensions. */
#if !defined(POLLMSG) && defined(__POLLMSG)
#define POLLMSG    __POLLMSG    /* Documented as unused */
#endif /* !POLLMSG && __POLLMSG */
#if !defined(POLLREMOVE) && defined(__POLLREMOVE)
#define POLLREMOVE __POLLREMOVE /* Undocumented & unused */
#endif /* !POLLREMOVE && __POLLREMOVE */
#if !defined(POLLRDHUP) && defined(__POLLRDHUP)
#define POLLRDHUP  __POLLRDHUP  /* Socket peer closed connection, or shut down writing half of its connection */
#endif /* !POLLRDHUP && __POLLRDHUP */

/* No idea what these 2 are supposed to be all about */
//#define POLLFREE       (__poll_t)0x4000
//#define POLL_BUSY_LOOP (__poll_t)0x8000

#endif /* !_ASM_POLL_H */
