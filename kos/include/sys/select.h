/* HASH CRC-32:0x1b161714 */
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
#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

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

#if defined(__CRT_HAVE_select64) && defined(__USE_TIME_BITS64)
__CREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,select,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timeval *__restrict __timeout),select64,(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE_select) && !defined(__USE_TIME_BITS64)
__CDECLARE(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,select,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timeval *__restrict __timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE___select) && !defined(__USE_TIME_BITS64)
__CREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,select,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timeval *__restrict __timeout),__select,(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE_select64) || defined(__CRT_HAVE_select) || defined(__CRT_HAVE___select)
#include <local/sys.select/select.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(select, __FORCELOCAL __ATTR_ARTIFICIAL __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL select)(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timeval *__restrict __timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(select))(__nfds, __readfds, __writefds, __exceptfds, __timeout); })
#endif /* ... */
#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_pselect64) && defined(__USE_TIME_BITS64)
__CREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,pselect,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timespec const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),pselect64,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE_pselect) && !defined(__USE_TIME_BITS64)
__CDECLARE(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,pselect,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timespec const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE_pselect64) || defined(__CRT_HAVE_pselect)
#include <local/sys.select/pselect.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(pselect, __FORCELOCAL __ATTR_ARTIFICIAL __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL pselect)(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timespec const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pselect))(__nfds, __readfds, __writefds, __exceptfds, __timeout, __sigmask); })
#endif /* ... */
#endif /* __USE_XOPEN2K */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_select64
__CDECLARE(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,select64,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timeval64 *__restrict __timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE_select) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,select64,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timeval64 *__restrict __timeout),select,(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE_select) || defined(__CRT_HAVE___select)
#include <local/sys.select/select64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(select64, __FORCELOCAL __ATTR_ARTIFICIAL __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL select64)(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timeval64 *__restrict __timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(select64))(__nfds, __readfds, __writefds, __exceptfds, __timeout); })
#endif /* ... */
#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_pselect64
__CDECLARE(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,pselect64,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timespec64 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE_pselect) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,pselect64,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timespec64 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),pselect,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE_pselect)
#include <local/sys.select/pselect64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(pselect64, __FORCELOCAL __ATTR_ARTIFICIAL __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL pselect64)(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timespec64 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pselect64))(__nfds, __readfds, __writefds, __exceptfds, __timeout, __sigmask); })
#endif /* ... */
#endif /* __USE_XOPEN2K */
#endif /* __USE_TIME64 */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_SELECT_H */
