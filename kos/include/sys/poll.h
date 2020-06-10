/* HASH CRC-32:0xb4aec850 */
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
#include <bits/types.h>
#include <bits/poll.h>
#include <hybrid/typecore.h>
#ifdef __USE_GNU
#include <bits/sigset.h>
#include <bits/timespec.h>
#endif /* __USE_GNU */

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __nfds_t_defined
#define __nfds_t_defined 1
typedef __UINTPTR_TYPE__ nfds_t;
#endif /* !__nfds_t_defined */

#ifndef __pollfd_defined
#define __pollfd_defined 1
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("fd")
#pragma push_macro("events")
#pragma push_macro("revents")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef fd
#undef events
#undef revents
struct pollfd {
	__fd_t         fd;      /* File descriptor to poll.  */
	__INT16_TYPE__ events;  /* Types of events poller cares about (Set of 'POLL*'). */
	__INT16_TYPE__ revents; /* Types of events that actually occurred (Set of 'POLL*'). */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("revents")
#pragma pop_macro("events")
#pragma pop_macro("fd")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !__pollfd_defined */

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
#elif defined(__CRT_HAVE_ppoll) || defined(__CRT_HAVE_ppoll64)
#include <local/sys.poll/ppoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ppoll, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL ppoll)(struct pollfd *__fds, nfds_t __nfds, struct timespec const *__timeout, struct __sigset_struct const *__ss) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ppoll))(__fds, __nfds, __timeout, __ss); })
#endif /* ... */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_ppoll64
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,ppoll64,(struct pollfd *__fds, nfds_t __nfds, struct timespec64 const *__timeout, struct __sigset_struct const *__ss),(__fds,__nfds,__timeout,__ss))
#elif defined(__CRT_HAVE_ppoll) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
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
