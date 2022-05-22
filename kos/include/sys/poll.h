/* HASH CRC-32:0x7a1832ae */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/poll.h) */
/* (#) Portability: FreeBSD       (/sys/sys/poll.h) */
/* (#) Portability: GNU C Library (/io/sys/poll.h) */
/* (#) Portability: NetBSD        (/sys/sys/poll.h) */
/* (#) Portability: OpenBSD       (/sys/sys/poll.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/poll.h) */
/* (#) Portability: diet libc     (/include/sys/poll.h) */
/* (#) Portability: libbsd        (/include/bsd/sys/poll.h) */
/* (#) Portability: mintlib       (/include/sys/poll.h) */
/* (#) Portability: musl libc     (/include/sys/poll.h) */
/* (#) Portability: uClibc        (/include/sys/poll.h) */
#ifndef _SYS_POLL_H
#define _SYS_POLL_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/typecore.h>

#include <asm/os/poll.h>
#include <bits/os/pollfd.h>
#include <bits/types.h>

#ifdef __USE_GNU
#include <bits/os/sigset.h> /* struct __sigset_struct */
#include <bits/os/timespec.h>
#endif /* __USE_GNU */



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

#if ((defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)) && !defined(__USE_KOS_PURE))
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
#endif /* (__USE_XOPEN || __USE_XOPEN2K8) && !__USE_KOS_PURE */

#ifdef __USE_GNU
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
#endif /* __USE_GNU */

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

/* Poll events are mapped by select(2) using these macros. */
#ifdef __USE_KOS
#if !defined(POLLSELECT_READFDS) && defined(__POLLSELECT_READFDS)
#define POLLSELECT_READFDS   __POLLSELECT_READFDS   /* select(2).readfds */
#endif /* !POLLSELECT_READFDS && __POLLSELECT_READFDS */
#if !defined(POLLSELECT_WRITEFDS) && defined(__POLLSELECT_WRITEFDS)
#define POLLSELECT_WRITEFDS  __POLLSELECT_WRITEFDS  /* select(2).writefds */
#endif /* !POLLSELECT_WRITEFDS && __POLLSELECT_WRITEFDS */
#if !defined(POLLSELECT_EXCEPTFDS) && defined(__POLLSELECT_EXCEPTFDS)
#define POLLSELECT_EXCEPTFDS __POLLSELECT_EXCEPTFDS /* select(2).exceptfds */
#endif /* !POLLSELECT_EXCEPTFDS && __POLLSELECT_EXCEPTFDS */
#endif /* __USE_KOS */

#ifdef __USE_BSD
#ifndef INFTIM
#define INFTIM (-1) /* Infinite timeout (pass for the `timeout' argument of `poll(2)') */
#endif /* !INFTIM */
#endif /* __USE_BSD */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __nfds_t_defined
#define __nfds_t_defined
typedef __UINTPTR_TYPE__ nfds_t;
#endif /* !__nfds_t_defined */

#ifdef __CRT_HAVE_poll
/* @param timeout: Timeout in milliseconds (or negative for infinity) */
__CDECLARE(__ATTR_INOUTS(1, 2),int,__NOTHROW_RPC,poll,(struct pollfd *__fds, nfds_t __nfds, int __timeout),(__fds,__nfds,__timeout))
#elif defined(__CRT_HAVE___poll)
/* @param timeout: Timeout in milliseconds (or negative for infinity) */
__CREDIRECT(__ATTR_INOUTS(1, 2),int,__NOTHROW_RPC,poll,(struct pollfd *__fds, nfds_t __nfds, int __timeout),__poll,(__fds,__nfds,__timeout))
#endif /* ... */
#ifdef __USE_GNU
#if defined(__CRT_HAVE_ppoll) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CDECLARE(__ATTR_INOUTS(1, 2) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4),int,__NOTHROW_RPC,ppoll,(struct pollfd *__fds, nfds_t __nfds, struct timespec const *__timeout, struct __sigset_struct const *__ss),(__fds,__nfds,__timeout,__ss))
#elif defined(__CRT_HAVE_ppoll64) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_INOUTS(1, 2) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4),int,__NOTHROW_RPC,ppoll,(struct pollfd *__fds, nfds_t __nfds, struct timespec const *__timeout, struct __sigset_struct const *__ss),ppoll64,(__fds,__nfds,__timeout,__ss))
#elif defined(__CRT_HAVE_ppoll64) || defined(__CRT_HAVE_ppoll)
#include <libc/local/sys.poll/ppoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ppoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUTS(1, 2) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) int __NOTHROW_RPC(__LIBCCALL ppoll)(struct pollfd *__fds, nfds_t __nfds, struct timespec const *__timeout, struct __sigset_struct const *__ss) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ppoll))(__fds, __nfds, __timeout, __ss); })
#endif /* ... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_ppoll) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_INOUTS(1, 2) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4),int,__NOTHROW_RPC,ppoll64,(struct pollfd *__fds, nfds_t __nfds, struct timespec64 const *__timeout, struct __sigset_struct const *__ss),ppoll,(__fds,__nfds,__timeout,__ss))
#elif defined(__CRT_HAVE_ppoll64)
__CDECLARE(__ATTR_INOUTS(1, 2) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4),int,__NOTHROW_RPC,ppoll64,(struct pollfd *__fds, nfds_t __nfds, struct timespec64 const *__timeout, struct __sigset_struct const *__ss),(__fds,__nfds,__timeout,__ss))
#elif defined(__CRT_HAVE_ppoll)
#include <libc/local/sys.poll/ppoll64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ppoll64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUTS(1, 2) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) int __NOTHROW_RPC(__LIBCCALL ppoll64)(struct pollfd *__fds, nfds_t __nfds, struct timespec64 const *__timeout, struct __sigset_struct const *__ss) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ppoll64))(__fds, __nfds, __timeout, __ss); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_GNU */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_POLL_H */
