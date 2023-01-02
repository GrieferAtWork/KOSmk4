/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/poll.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/poll.h) */
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
}

%[define_decl_include_implication("<bits/os/pollfd.h>" => ["<bits/types.h>"])]
%[define_decl_include("<bits/os/pollfd.h>": ["struct pollfd"])]

%[define_decl_include_implication("<bits/os/sigset.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/os/sigset.h>": ["struct __sigset_struct"])]
%[define_replacement(sigset_t = "struct __sigset_struct")]

%[define_replacement(nfds_t     = __UINTPTR_TYPE__)]
%[define_replacement(fd_t       = __fd_t)]
%[define_replacement(time_t     = "__time_t")]
%[define_replacement(time32_t   = __time32_t)]
%[define_replacement(time64_t   = __time64_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[default:section(".text.crt{|.dos}.io.poll")]


%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

}%[insert:prefix(
#include <asm/os/poll.h>
)]%[insert:prefix(
#include <bits/os/pollfd.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

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

}

%(auto_header,user){
#include <signal.h> /* sigset_t */
}

@@@param timeout: Timeout in milliseconds (or negative for infinity)
[[cp, export_alias("__poll"), decl_include("<bits/os/pollfd.h>")]]
int poll([[inout(nfds)]] struct pollfd *fds, nfds_t nfds, int timeout);

%#ifdef __USE_GNU

[[cp, doc_alias("ppoll"), ignore, nocrt, alias("ppoll")]]
[[decl_include("<bits/os/pollfd.h>", "<bits/os/timespec.h>", "<bits/os/sigset.h>")]]
int ppoll32([[inout(nfds)]] struct pollfd *fds, nfds_t nfds,
            [[in_opt]] struct $timespec32 const *timeout,
            [[in_opt]] $sigset_t const *ss);

[[cp, decl_include("<bits/os/pollfd.h>", "<bits/os/timespec.h>", "<bits/os/sigset.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ppoll")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ppoll64")]]
[[userimpl, requires($has_function(ppoll32) || $has_function(ppoll64))]]
int ppoll([[inout(nfds)]] struct pollfd *fds, nfds_t nfds,
          [[in_opt]] struct timespec const *timeout,
          [[in_opt]] $sigset_t const *ss) {
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
[[preferred_time64_variant_of(ppoll), doc_alias("ppoll")]]
[[cp, userimpl, requires_function(ppoll32)]]
[[decl_include("<bits/os/pollfd.h>", "<bits/os/timespec.h>", "<bits/os/sigset.h>")]]
int ppoll64([[inout(nfds)]] struct pollfd *fds, nfds_t nfds,
            [[in_opt]] struct timespec64 const *timeout,
            [[in_opt]] $sigset_t const *ss) {
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

__SYSDECL_END
#endif /* __CC__ */

}
