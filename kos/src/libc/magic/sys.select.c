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



%{
#include <features.h>

#include <hybrid/typecore.h>

#include <asm/select.h> /* __FD_SETSIZE */
#include <bits/sigset.h> /* struct __sigset_struct */
#include <bits/time.h>
#include <bits/timespec.h> /* struct timespec */
#include <bits/timeval.h>  /* struct timeval */
#include <bits/types.h>

#ifndef __INTELLISENSE__
#include <libc/string.h> /* __libc_bzero */
#endif /* !__INTELLISENSE__ */

#ifndef __FD_SETSIZE
#define __FD_SETSIZE 1024
#endif /* !__FD_SETSIZE */

#ifdef __FD_SETSIZE
#define FD_SETSIZE __FD_SETSIZE
#endif /* __FD_SETSIZE */

__SYSDECL_BEGIN

#define __SIZEOF_FD_MASK __SIZEOF_POINTER__
#define __SIZEOF_FD_SET  (__FD_SETSIZE / __CHAR_BIT__)
#define __NFDBITS        (__SIZEOF_FD_MASK * __CHAR_BIT__)
#define __FD_ELT(d)      ((d) / __NFDBITS)
#define __FD_MASK(d)     (__CCAST(__fd_mask)1 << ((d) % __NFDBITS))

#ifdef __CC__

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

typedef __intptr_t __fd_mask;

typedef struct __fd_set_struct {
#ifdef __USE_XOPEN
	__fd_mask fds_bits[__FD_SETSIZE / __NFDBITS];
#define __FDS_BITS(set) ((set)->fds_bits)
#else /* __USE_XOPEN */
	__fd_mask __fds_bits[__FD_SETSIZE / __NFDBITS];
#define __FDS_BITS(set) ((set)->__fds_bits)
#endif /* !__USE_XOPEN */
} fd_set;

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
#else /* __INTELLISENSE__ */
#define FD_SET(fd, fdsetp)   (void)(__FDS_BITS(set)[__FD_ELT(d)] |= __FD_MASK(d))
#define FD_CLR(fd, fdsetp)   (void)(__FDS_BITS(set)[__FD_ELT(d)] &= ~__FD_MASK(d))
#define FD_ISSET(fd, fdsetp) ((__FDS_BITS(set)[__FD_ELT(d)] & __FD_MASK(d)) != 0)
#define FD_ZERO(fdsetp)      __libc_bzero(__FDS_BITS(__arr), __SIZEOF_FD_SET)
#endif /* !__INTELLISENSE__ */

}

[[decl_include("<features.h>", "<bits/timeval.h>")]]
[[decl_prefix(struct __fd_set_struct;)]]
[[cp, ignore, nocrt, alias("select", "__select")]]
__STDC_INT_AS_SSIZE_T select32(__STDC_INT_AS_SIZE_T nfds,
                               [[nullable]] fd_set *__restrict readfds,
                               [[nullable]] fd_set *__restrict writefds,
                               [[nullable]] fd_set *__restrict exceptfds,
                               [[nullable]] struct $timeval32 *__restrict timeout);

[[decl_include("<features.h>", "<bits/timespec.h>")]]
[[decl_prefix(struct __fd_set_struct;)]]
[[cp, ignore, nocrt, alias("pselect")]]
__STDC_INT_AS_SSIZE_T pselect32(__STDC_INT_AS_SIZE_T nfds,
                                [[nullable]] fd_set *__restrict readfds,
                                [[nullable]] fd_set *__restrict writefds,
                                [[nullable]] fd_set *__restrict exceptfds,
                                [[nullable]] struct $timespec32 const *__restrict timeout,
                                [[nullable]] $sigset_t const *__restrict sigmask);


[[decl_include("<features.h>", "<bits/timeval.h>")]]
[[decl_prefix(struct __fd_set_struct;)]]
[[cp, no_crt_self_import, export_as("__select")]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("select64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("select", "__select")]]
[[userimpl, requires($has_function(select32) || $has_function(select64))]]
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
	tmv.tv_usec = timeout->tv_usec;
	return select64(nfds, readfds, writefds, exceptfds, &tmv);
@@pp_else@@
	struct timeval32 tmv;
	if (!timeout)
		return select32(nfds, readfds, writefds, exceptfds, NULL);
	tmv.tv_sec  = (time32_t)timeout->tv_sec;
	tmv.tv_usec = timeout->tv_usec;
	return select32(nfds, readfds, writefds, exceptfds, &tmv);
@@pp_endif@@
}

%#ifdef __USE_XOPEN2K
[[decl_include("<features.h>", "<bits/timespec.h>", "<bits/sigset.h>")]]
[[decl_prefix(struct __fd_set_struct;)]]
[[cp, no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("pselect64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("pselect")]]
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
[[decl_include("<features.h>", "<bits/timeval.h>")]]
[[decl_prefix(struct __fd_set_struct;)]]
[[cp, doc_alias("select"), time64_variant_of(select)]]
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
	tmv.tv_usec = timeout->tv_usec;
	return select32(nfds, readfds, writefds, exceptfds, &tmv);
}

%#ifdef __USE_XOPEN2K
[[decl_include("<features.h>", "<bits/timespec.h>", "<bits/sigset.h>")]]
[[decl_prefix(struct __fd_set_struct;)]]
[[doc_alias("pselect"), time64_variant_of(pselect)]]
[[cp, userimpl, requires_function(pselect32)]]
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

#endif /* __CC__ */

__SYSDECL_END

}