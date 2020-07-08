/* HASH CRC-32:0x2992a033 */
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
#ifndef _SYS_POLL_H
#define _SYS_POLL_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/typecore.h>

#include <asm/poll.h>
#include <bits/pollfd.h>
#include <bits/types.h>

#ifdef __USE_GNU
#include <bits/sigset.h>
#include <bits/timespec.h>
#endif /* __USE_GNU */

__SYSDECL_BEGIN

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

/* Event types that can be polled for. These bits may be set in `events'
 * to indicate the interesting event types; they will appear in `revents'
 * to indicate the status of the file descriptor. */
#ifdef __POLLIN
#define POLLIN __POLLIN /* There is data to read. */
#endif /* __POLLIN */
#ifdef __POLLPRI
#define POLLPRI __POLLPRI /* There is urgent data to read. */
#endif /* __POLLPRI */
#ifdef __POLLOUT
#define POLLOUT __POLLOUT /* Writing now will not block. */
#endif /* __POLLOUT */

#if ((defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)) && \
     !defined(__USE_KOS_PURE))
/* These values are defined in XPG4.2. */
#ifdef __POLLRDNORM
#define POLLRDNORM __POLLRDNORM /* 100% identical to `POLLIN' (Normal data may be read). */
#endif /* __POLLRDNORM */
#ifdef __POLLRDBAND
#define POLLRDBAND __POLLRDBAND /* Priority data may be read. */
#endif /* __POLLRDBAND */
#ifdef __POLLWRNORM
#define POLLWRNORM __POLLWRNORM /* 100% identical to `POLLOUT' (Writing now will not block). */
#endif /* __POLLWRNORM */
#ifdef __POLLWRBAND
#define POLLWRBAND __POLLWRBAND /* Priority data may be written. */
#endif /* __POLLWRBAND */
#endif /* (__USE_XOPEN || __USE_XOPEN2K8) && !__USE_KOS_PURE */

#ifdef __USE_GNU
/* These are extensions for Linux. */
#ifdef __POLLMSG
#define POLLMSG __POLLMSG /* Documented as unused */
#endif /* __POLLMSG */
#ifdef __POLLREMOVE
#define POLLREMOVE __POLLREMOVE /* Undocumented & unused */
#endif /* __POLLREMOVE */
#ifdef __POLLRDHUP
#define POLLRDHUP __POLLRDHUP /* Socket peer closed connection, or shut down writing half of its connection */
#endif /* __POLLRDHUP */
#endif /* __USE_GNU */

/* Event types always implicitly polled for. These bits need
 * not be set in `events', but they will appear in `revents'
 * to indicate the status of the file descriptor. */
#ifdef __POLLERR
#define POLLERR __POLLERR /* Error condition. */
#endif /* __POLLERR */
#ifdef __POLLHUP
#define POLLHUP __POLLHUP /* Hung up. (writes are no longer possible) */
#endif /* __POLLHUP */
#ifdef __POLLNVAL
#define POLLNVAL __POLLNVAL /* Invalid polling request. */
#endif /* __POLLNVAL */

/* Poll events are mapped by select(2) using these macros. */
#ifdef __USE_KOS
#ifdef __POLLSELECT_READFDS
#define POLLSELECT_READFDS __POLLSELECT_READFDS /* readfds */
#endif /* __POLLSELECT_READFDS */
#ifdef __POLLSELECT_WRITEFDS
#define POLLSELECT_WRITEFDS __POLLSELECT_WRITEFDS /* writefds */
#endif /* __POLLSELECT_WRITEFDS */
#ifdef __POLLSELECT_EXCEPTFDS
#define POLLSELECT_EXCEPTFDS __POLLSELECT_EXCEPTFDS /* exceptfds */
#endif /* __POLLSELECT_EXCEPTFDS */
#endif /* __USE_KOS */

#ifdef __USE_BSD
#ifndef INFTIM
#define INFTIM (-1)
#endif /* !INFTIM */
#endif /* __USE_BSD */

#ifdef __CC__
#ifndef __nfds_t_defined
#define __nfds_t_defined 1
typedef __UINTPTR_TYPE__ nfds_t;
#endif /* !__nfds_t_defined */

#ifdef __CRT_HAVE_poll
/* @param timeout: Timeout in milliseconds (or negative for infinity) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,poll,(struct pollfd *__fds, nfds_t __nfds, int __timeout),(__fds,__nfds,__timeout))
#elif defined(__CRT_HAVE___poll)
/* @param timeout: Timeout in milliseconds (or negative for infinity) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,poll,(struct pollfd *__fds, nfds_t __nfds, int __timeout),__poll,(__fds,__nfds,__timeout))
#endif /* ... */
#ifdef __USE_GNU
#if defined(__CRT_HAVE_ppoll) && defined(__USE_TIME_BITS64)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,ppoll,(struct pollfd *__fds, nfds_t __nfds, struct timespec const *__timeout, struct __sigset_struct const *__ss),(__fds,__nfds,__timeout,__ss))
#elif defined(__CRT_HAVE_ppoll64) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,ppoll,(struct pollfd *__fds, nfds_t __nfds, struct timespec const *__timeout, struct __sigset_struct const *__ss),ppoll64,(__fds,__nfds,__timeout,__ss))
#elif defined(__CRT_HAVE_ppoll64) || defined(__CRT_HAVE_ppoll)
#include <local/sys.poll/ppoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ppoll, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL ppoll)(struct pollfd *__fds, nfds_t __nfds, struct timespec const *__timeout, struct __sigset_struct const *__ss) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ppoll))(__fds, __nfds, __timeout, __ss); })
#endif /* ... */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_ppoll64
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,ppoll64,(struct pollfd *__fds, nfds_t __nfds, struct timespec64 const *__timeout, struct __sigset_struct const *__ss),(__fds,__nfds,__timeout,__ss))
#elif defined(__CRT_HAVE_ppoll) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,ppoll64,(struct pollfd *__fds, nfds_t __nfds, struct timespec64 const *__timeout, struct __sigset_struct const *__ss),ppoll,(__fds,__nfds,__timeout,__ss))
#elif defined(__CRT_HAVE_ppoll)
#include <local/sys.poll/ppoll64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ppoll64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL ppoll64)(struct pollfd *__fds, nfds_t __nfds, struct timespec64 const *__timeout, struct __sigset_struct const *__ss) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ppoll64))(__fds, __nfds, __timeout, __ss); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_GNU */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_POLL_H */
