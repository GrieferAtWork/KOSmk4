/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/select.h) */
/* (#) Portability: FreeBSD       (/sys/sys/select.h) */
/* (#) Portability: GNU C Library (/misc/sys/select.h) */
/* (#) Portability: NetBSD        (/sys/sys/select.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/select.h) */
/* (#) Portability: OpenBSD       (/sys/sys/select.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/select.h) */
/* (#) Portability: diet libc     (/include/sys/select.h) */
/* (#) Portability: musl libc     (/include/sys/select.h) */
/* (#) Portability: uClibc        (/include/sys/select.h) */
}

%[define_replacement(sigset_t   = "struct __sigset_struct")]
%[define_replacement(time_t     = "__TM_TYPE(time)")]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(timeval32  = __timeval32)]
%[define_replacement(timeval64  = __timeval64)]
%[define_replacement(time32_t   = __time32_t)]
%[define_replacement(time64_t   = __time64_t)]
%[define_replacement(fd_set     = "struct __fd_set_struct")]
%[default:section(".text.crt{|.dos}.io.poll")]


%(auto_header,user){
#include <signal.h>
}



%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

}%[insert:prefix(
#include <bits/os/fd_set.h>   /* struct __fd_set_struct, __NFDBITS, __fd_mask, __FD_ELT, __FD_MASK, __SIZEOF_FD_SET */
)]%[insert:prefix(
#include <bits/os/sigset.h>   /* struct __sigset_struct */
)]%[insert:prefix(
#include <bits/os/timespec.h> /* struct timespec */
)]%[insert:prefix(
#include <bits/os/timeval.h>  /* struct timeval */
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifndef __INTELLISENSE__
#include <libc/string.h> /* __libc_bzero */
#endif /* !__INTELLISENSE__ */

#ifndef FD_SETSIZE
#define FD_SETSIZE __FD_SETSIZE /* 1+ the max FD which may be stored in a `fd_set' */
#endif /* FD_SETSIZE */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __time_t_defined
#define __time_t_defined  1
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __suseconds_t_defined
#define __suseconds_t_defined 1
typedef __suseconds_t suseconds_t;
#endif /* !__suseconds_t_defined */

typedef struct __fd_set_struct fd_set;
#ifdef __USE_MISC
typedef __fd_mask fd_mask;
#define NFDBITS __NFDBITS
#endif /* __USE_MISC */

#ifdef __INTELLISENSE__
__ATTR_NONNULL((2)) void (FD_SET)(__fd_t __fd, fd_set *__fdsetp);
__ATTR_NONNULL((2)) void (FD_CLR)(__fd_t __fd, fd_set *__fdsetp);
__ATTR_NONNULL((2)) __BOOL (FD_ISSET)(__fd_t __fd, fd_set const *__fdsetp);
__ATTR_NONNULL((1)) void (FD_ZERO)(fd_set *__fdsetp);
#define FD_SET   FD_SET
#define FD_CLR   FD_CLR
#define FD_ISSET FD_ISSET
#define FD_ZERO  FD_ZERO
#ifdef __USE_NETBSD
__ATTR_NONNULL((1)) void (FD_COPY)(fd_set const *__src, fd_set *__dst);
#define FD_COPY  FD_COPY
#endif /* __USE_NETBSD */
#else /* __INTELLISENSE__ */
#define FD_SET(fd, fdsetp)   (void)(__FDS_BITS(fdsetp)[__FD_ELT(fd)] |= __FD_MASK(fd))
#define FD_CLR(fd, fdsetp)   (void)(__FDS_BITS(fdsetp)[__FD_ELT(fd)] &= ~__FD_MASK(fd))
#define FD_ISSET(fd, fdsetp) ((__FDS_BITS(fdsetp)[__FD_ELT(fd)] & __FD_MASK(fd)) != 0)
#define FD_ZERO(fdsetp)      __libc_bzero(__FDS_BITS(fdsetp), __SIZEOF_FD_SET)
#ifdef __USE_NETBSD
#define FD_COPY(src, dst) (void)__libc_memcpy(dst, src, __SIZEOF_FD_SET)
#endif /* __USE_NETBSD */
#endif /* !__INTELLISENSE__ */

}

[[decl_include("<features.h>", "<bits/os/timeval.h>")]]
[[decl_include("<bits/os/fd_set.h>")]]
[[cp, ignore, nocrt, alias("select", "__select")]]
__STDC_INT_AS_SSIZE_T select32(__STDC_INT_AS_SIZE_T nfds,
                               [[nullable]] fd_set *__restrict readfds,
                               [[nullable]] fd_set *__restrict writefds,
                               [[nullable]] fd_set *__restrict exceptfds,
                               [[nullable]] struct $timeval32 *__restrict timeout);

[[decl_include("<features.h>", "<bits/os/timespec.h>")]]
[[decl_include("<bits/os/fd_set.h>")]]
[[cp, ignore, nocrt, alias("pselect")]]
__STDC_INT_AS_SSIZE_T pselect32(__STDC_INT_AS_SIZE_T nfds,
                                [[nullable]] fd_set *__restrict readfds,
                                [[nullable]] fd_set *__restrict writefds,
                                [[nullable]] fd_set *__restrict exceptfds,
                                [[nullable]] struct $timespec32 const *__restrict timeout,
                                [[nullable]] $sigset_t const *__restrict sigmask);


[[cp, decl_include("<features.h>", "<bits/os/timeval.h>", "<bits/os/fd_set.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("select", "__select")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("select64")]]
[[userimpl, requires($has_function(select32) || $has_function(select64))]]
[[export_as("__select")]]
__STDC_INT_AS_SSIZE_T select(__STDC_INT_AS_SIZE_T nfds,
                             [[nullable]] fd_set *__restrict readfds,
                             [[nullable]] fd_set *__restrict writefds,
                             [[nullable]] fd_set *__restrict exceptfds,
                             [[nullable]] struct timeval *__restrict timeout) {
@@pp_if $has_function(select64)@@
	struct timeval64 tmv;
	if (!timeout)
		return select64(nfds, readfds, writefds, exceptfds, NULL);
	tmv.tv_sec  = (time64_t)timeout->tv_sec;
	tmv.@tv_usec@ = timeout->@tv_usec@;
	return select64(nfds, readfds, writefds, exceptfds, &tmv);
@@pp_else@@
	struct timeval32 tmv;
	if (!timeout)
		return select32(nfds, readfds, writefds, exceptfds, NULL);
	tmv.tv_sec  = (time32_t)timeout->tv_sec;
	tmv.@tv_usec@ = timeout->@tv_usec@;
	return select32(nfds, readfds, writefds, exceptfds, &tmv);
@@pp_endif@@
}

%#ifdef __USE_XOPEN2K
[[cp, decl_include("<features.h>", "<bits/os/timespec.h>", "<bits/os/sigset.h>", "<bits/os/fd_set.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pselect")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("pselect64")]]
[[userimpl, requires($has_function(pselect32) || $has_function(pselect64))]]
__STDC_INT_AS_SSIZE_T pselect(__STDC_INT_AS_SIZE_T nfds,
                              [[nullable]] fd_set *__restrict readfds,
                              [[nullable]] fd_set *__restrict writefds,
                              [[nullable]] fd_set *__restrict exceptfds,
                              [[nullable]] struct timespec const *__restrict timeout,
                              [[nullable]] $sigset_t const *__restrict sigmask) {
@@pp_if $has_function(pselect64)@@
	struct timespec64 tmv;
	if (!timeout)
		return pselect64(nfds, readfds, writefds, exceptfds, NULL, sigmask);
	tms.tv_sec  = (time64_t)timeout->tv_sec;
	tms.tv_nsec = timeout->tv_nsec;
	return pselect64(nfds, readfds, writefds, exceptfds, &tms, sigmask);
@@pp_else@@
	struct timespec32 tms;
	if (!timeout)
		return pselect32(nfds, readfds, writefds, exceptfds, NULL, sigmask);
	tms.tv_sec  = (time32_t)timeout->tv_sec;
	tms.tv_nsec = timeout->tv_nsec;
	return pselect32(nfds, readfds, writefds, exceptfds, &tms, sigmask);
@@pp_endif@@
}
%#endif /* __USE_XOPEN2K */

%
%#ifdef __USE_TIME64
[[decl_include("<features.h>", "<bits/os/timeval.h>", "<bits/os/fd_set.h>")]]
[[cp, preferred_time64_variant_of(select), doc_alias("select")]]
[[userimpl, requires_function(select32)]]
__STDC_INT_AS_SSIZE_T select64(__STDC_INT_AS_SIZE_T nfds,
                               [[nullable]] fd_set *__restrict readfds,
                               [[nullable]] fd_set *__restrict writefds,
                               [[nullable]] fd_set *__restrict exceptfds,
                               [[nullable]] struct $timeval64 *__restrict timeout) {
	struct timeval32 tmv;
	if (!timeout)
		return select32(nfds, readfds, writefds, exceptfds, NULL);
	tmv.tv_sec  = (time32_t)timeout->tv_sec;
	tmv.tv_usec = timeout->@tv_usec@;
	return select32(nfds, readfds, writefds, exceptfds, &tmv);
}

%#ifdef __USE_XOPEN2K
[[decl_include("<features.h>", "<bits/os/timespec.h>", "<bits/os/sigset.h>", "<bits/os/fd_set.h>")]]
[[cp, preferred_time64_variant_of(pselect), doc_alias("pselect")]]
[[userimpl, requires_function(pselect32)]]
__STDC_INT_AS_SSIZE_T pselect64(__STDC_INT_AS_SIZE_T nfds,
                                [[nullable]] fd_set *__restrict readfds,
                                [[nullable]] fd_set *__restrict writefds,
                                [[nullable]] fd_set *__restrict exceptfds,
                                [[nullable]] struct $timespec64 const *__restrict timeout,
                                [[nullable]] $sigset_t const *__restrict sigmask) {
	struct timespec32 tms;
	if (!timeout)
		return pselect32(nfds, readfds, writefds, exceptfds, NULL, sigmask);
	tms.tv_sec  = (time32_t)timeout->tv_sec;
	tms.tv_nsec = timeout->tv_nsec;
	return pselect32(nfds, readfds, writefds, exceptfds, &tms, sigmask);
}
%#endif /* __USE_XOPEN2K */
%#endif /* __USE_TIME64 */

%{

__SYSDECL_END
#endif /* __CC__ */

}
