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

%[define_replacement(nfds_t     = __UINTPTR_TYPE__)]
%[define_replacement(sigset_t   = "struct __sigset_struct")]
%[define_replacement(fd_t       = __fd_t)]
%[define_replacement(time_t     = "__TM_TYPE(time)")]
%[define_replacement(time32_t   = __time32_t)]
%[define_replacement(time64_t   = __time64_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[default:section(".text.crt{|.dos}.io.poll")]


%{
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

}

%(auto_header,user){
DECL_END
#include <bits/sigset.h>
DECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef __sigset_t sigset_t;
#endif /* !__sigset_t_defined */

}

@@@param timeout: Timeout in milliseconds (or negative for infinity)
[[cp, export_alias("__poll"), decl_include("<bits/pollfd.h>")]]
int poll([[inp(nfds)]] struct pollfd *fds, nfds_t nfds, int timeout);

%#ifdef __USE_GNU

[[cp, doc_alias("ppoll"), ignore, nocrt, alias("ppoll")]]
[[decl_include("<bits/pollfd.h>", "<bits/timespec.h>", "<bits/sigset.h>")]]
int ppoll32([[inp(nfds)]] struct pollfd *fds, nfds_t nfds,
            [[nullable]] struct $timespec32 const *timeout,
            [[nullable]] $sigset_t const *ss);

[[cp, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("ppoll")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("ppoll64")]]
[[userimpl, requires($has_function(ppoll32) || $has_function(ppoll64))]]
[[decl_include("<bits/pollfd.h>", "<bits/timespec.h>", "<bits/sigset.h>")]]
int ppoll([[inp(nfds)]] struct pollfd *fds, nfds_t nfds,
          [[nullable]] struct timespec const *timeout,
          [[nullable]] $sigset_t const *ss) {
@@pp_if $has_function(ppoll32)@@
	struct timespec32 tmo32;
	if (!timeout)
		return ppoll32(fds, nfds, NULL, ss);
	tmo32.tv_sec  = (time32_t)timeout->tv_sec;
	tmo32.tv_nsec = timeout->tv_nsec;
	return ppoll32(fds, nfds, &tmo32, ss);
@@pp_else@@
	struct timespec64 tmo64;
	if (!timeout)
		return ppoll64(fds, nfds, NULL, ss);
	tmo64.tv_sec  = (time64_t)timeout->tv_sec;
	tmo64.tv_nsec = timeout->tv_nsec;
	return ppoll64(fds, nfds, &tmo64, ss);
@@pp_endif@@
}

%
%#ifdef __USE_TIME64
[[doc_alias("ppoll"), time64_variant_of(ppoll)]]
[[cp, userimpl, requires_function(ppoll32)]]
[[decl_include("<bits/pollfd.h>", "<bits/timespec.h>", "<bits/sigset.h>")]]
int ppoll64([[inp(nfds)]] struct pollfd *fds, nfds_t nfds,
            [[nullable]] struct timespec64 const *timeout,
            [[nullable]] $sigset_t const *ss) {
	struct timespec32 tmo32;
	if (!timeout)
		return ppoll32(fds, nfds, NULL, ss);
	tmo32.tv_sec  = (time32_t)timeout->tv_sec;
	tmo32.tv_nsec = timeout->tv_nsec;
	return ppoll32(fds, nfds, &tmo32, ss);
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_GNU */

%{
#endif /* __CC__ */

__SYSDECL_END

}
