/* HASH CRC-32:0xce3b791e */
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
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/select.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/select.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/select.h) */
/* (#) Portability: FreeBSD       (/sys/sys/select.h) */
/* (#) Portability: GNU C Library (/misc/sys/select.h) */
/* (#) Portability: NetBSD        (/sys/sys/select.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/select.h) */
/* (#) Portability: OpenBSD       (/sys/sys/select.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/select.h) */
/* (#) Portability: diet libc     (/include/sys/select.h) */
/* (#) Portability: mintlib       (/include/sys/select.h) */
/* (#) Portability: musl libc     (/include/sys/select.h) */
/* (#) Portability: uClibc        (/include/sys/select.h) */
#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/fd_set.h>   /* struct __fd_set_struct, __NFDBITS, __fd_mask, __FD_ELT, __FD_MASK, __SIZEOF_FD_SET */
#include <bits/os/sigset.h>   /* struct __sigset_struct */
#include <bits/os/timespec.h> /* struct timespec */
#include <bits/os/timeval.h>  /* struct timeval */
#include <bits/types.h>

#ifndef __INTELLISENSE__
#include <libc/string.h> /* __libc_bzero */
#endif /* !__INTELLISENSE__ */

#ifndef FD_SETSIZE
#define FD_SETSIZE __FD_SETSIZE /* 1+ the max FD which may be stored in a `fd_set' */
#endif /* FD_SETSIZE */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __time_t_defined
#define __time_t_defined
typedef __time_t time_t;
#endif /* !__time_t_defined */

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __suseconds_t_defined
#define __suseconds_t_defined
typedef __suseconds_t suseconds_t;
#endif /* !__suseconds_t_defined */

typedef struct __fd_set_struct fd_set;
#ifdef __USE_MISC
typedef __fd_mask fd_mask;
#define NFDBITS __NFDBITS
#endif /* __USE_MISC */

#ifdef __INTELLISENSE__
__ATTR_FDARG(1) __ATTR_NONNULL((2)) void (FD_SET)(__fd_t __fd, fd_set *__fdsetp);
__ATTR_FDARG(1) __ATTR_NONNULL((2)) void (FD_CLR)(__fd_t __fd, fd_set *__fdsetp);
__ATTR_FDARG(1) __ATTR_NONNULL((2)) __BOOL (FD_ISSET)(__fd_t __fd, fd_set const *__fdsetp);
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
#if (!defined(NDEBUG) && !defined(NDEBUG_BOUNDS) && \
     !defined(NDEBUG_FDELT) && !defined(__OPTIMIZE_SIZE__))
#ifdef __CRT_HAVE___fdelt_chk
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW,__fdelt_chk,(__LONGPTR_TYPE__ __fd),(__fd))
#elif defined(__CRT_HAVE___fdelt_warn)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW,__fdelt_chk,(__LONGPTR_TYPE__ __fd),__fdelt_warn,(__fd))
#else /* ... */
#include <libc/local/sys.select/__fdelt_chk.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__fdelt_chk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGPTR_TYPE__ __NOTHROW(__LIBCCALL __fdelt_chk)(__LONGPTR_TYPE__ __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__fdelt_chk))(__fd); })
#endif /* !... */

/* Override `__FD_ELT()' with an argument-checking variant. */
#undef __FD_ELT
#ifdef __NO_builtin_constant_p
#define __FD_ELT __fdelt_chk
#elif !defined(__NO_ATTR_WARNING) && (defined(__CRT_HAVE___fdelt_chk) || defined(__CRT_HAVE___fdelt_warn))
#ifdef __CRT_HAVE___fdelt_chk
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED __ATTR_WARNING("fd number cannot be used with `fd_set'"),__LONGPTR_TYPE__,__NOTHROW,__fdelt_warn,(__LONGPTR_TYPE__ __fd),__fdelt_chk,(__fd))
#else /* __CRT_HAVE___fdelt_chk */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED __ATTR_WARNING("fd number cannot be used with `fd_set'"),__LONGPTR_TYPE__,__NOTHROW,__fdelt_warn,(__LONGPTR_TYPE__ __fd),(__fd))
#endif /* !__CRT_HAVE___fdelt_chk */
#define __FD_ELT(fd)                                                      \
	(__builtin_constant_p(fd)                                             \
	 ? ((__ULONGPTR_TYPE__)(fd) < __FD_SETSIZE ? (fd) : __fdelt_warn(fd)) \
	 : __fdelt_chk(fd))
#else /* __NO_builtin_constant_p */
#define __FD_ELT(fd) \
	((__builtin_constant_p(fd) && (__ULONGPTR_TYPE__)(fd) < __FD_SETSIZE) ? (fd) : __fdelt_chk(fd))
#endif /* !__NO_builtin_constant_p */
#endif /* !NDEBUG && !NDEBUG_BOUNDS && !NDEBUG_FDELT && !__OPTIMIZE_SIZE__ */

#define FD_SET(fd, fdsetp)   (void)(__FDS_BITS(fdsetp)[__FD_ELT(fd)] |= __FD_MASK(fd))
#define FD_CLR(fd, fdsetp)   (void)(__FDS_BITS(fdsetp)[__FD_ELT(fd)] &= ~__FD_MASK(fd))
#define FD_ISSET(fd, fdsetp) ((__FDS_BITS(fdsetp)[__FD_ELT(fd)] & __FD_MASK(fd)) != 0)
#define FD_ZERO(fdsetp)      __libc_bzero(__FDS_BITS(fdsetp), __SIZEOF_FD_SET)
#ifdef __USE_NETBSD
#define FD_COPY(src, dst) (void)__libc_memcpy(dst, src, __SIZEOF_FD_SET)
#endif /* __USE_NETBSD */
#endif /* !__INTELLISENSE__ */

#if defined(__CRT_HAVE_select) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CDECLARE(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,select,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timeval *__restrict __timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE___select) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,select,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timeval *__restrict __timeout),__select,(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE_select64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,select,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timeval *__restrict __timeout),select64,(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE___select64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,select,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timeval *__restrict __timeout),__select64,(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE_select64) || defined(__CRT_HAVE___select64) || defined(__CRT_HAVE_select) || defined(__CRT_HAVE___select)
#include <libc/local/sys.select/select.h>
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__NAMESPACE_LOCAL_USING_OR_IMPL(select, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL select)(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timeval *__restrict __timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(select))(__nfds, __readfds, __writefds, __exceptfds, __timeout); })
#endif /* ... */
#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_pselect) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CDECLARE(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_IN_OPT(5) __ATTR_IN_OPT(6),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,pselect,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timespec const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE___pselect) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_IN_OPT(5) __ATTR_IN_OPT(6),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,pselect,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timespec const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),__pselect,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE_pselect64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_IN_OPT(5) __ATTR_IN_OPT(6),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,pselect,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timespec const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),pselect64,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE___pselect64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_IN_OPT(5) __ATTR_IN_OPT(6),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,pselect,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timespec const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),__pselect64,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif (defined(__CRT_HAVE___pselect) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || defined(__CRT_HAVE_pselect64) || defined(__CRT_HAVE___pselect64) || defined(__CRT_HAVE_pselect)
#include <libc/local/sys.select/pselect.h>
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__NAMESPACE_LOCAL_USING_OR_IMPL(pselect, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_IN_OPT(5) __ATTR_IN_OPT(6) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL pselect)(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct timespec const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pselect))(__nfds, __readfds, __writefds, __exceptfds, __timeout, __sigmask); })
#endif /* ... */
#endif /* __USE_XOPEN2K */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_select) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,select64,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timeval64 *__restrict __timeout),select,(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE_select64)
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CDECLARE(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,select64,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timeval64 *__restrict __timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE___select64)
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,select64,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timeval64 *__restrict __timeout),__select64,(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE_select) || defined(__CRT_HAVE___select)
#include <libc/local/sys.select/select64.h>
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__NAMESPACE_LOCAL_USING_OR_IMPL(select64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL select64)(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timeval64 *__restrict __timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(select64))(__nfds, __readfds, __writefds, __exceptfds, __timeout); })
#endif /* ... */
#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_pselect) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_IN_OPT(5) __ATTR_IN_OPT(6),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,pselect64,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timespec64 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),pselect,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE___pselect) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_IN_OPT(5) __ATTR_IN_OPT(6),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,pselect64,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timespec64 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),__pselect,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE_pselect64)
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CDECLARE(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_IN_OPT(5) __ATTR_IN_OPT(6),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,pselect64,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timespec64 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE___pselect64)
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_IN_OPT(5) __ATTR_IN_OPT(6),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,pselect64,(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timespec64 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask),__pselect64,(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask))
#elif defined(__CRT_HAVE_pselect)
#include <libc/local/sys.select/pselect64.h>
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first `nfds'  elements of  the respective  sets are  considered,  thus
 * representing  the  upper limit  on how  much  memory the  kernel might
 * touch in the given sets.
 *
 * Upon return, all  bits from all  given fd sets  will be cleared,  except
 * for those which are associated with files where the respective condition
 * has become available.
 *
 * This system call is implemented in terms of `poll(2)', and individual
 * sets translate to `struct pollfd::events':
 *  - readfds:   POLLSELECT_READFDS    (POLLRDNORM | POLLRDBAND | POLLIN | POLLHUP | POLLERR)
 *  - writefds:  POLLSELECT_WRITEFDS   (POLLWRBAND | POLLWRNORM | POLLOUT | POLLERR)
 *  - exceptfds: POLLSELECT_EXCEPTFDS  (POLLPRI)
 *
 * @param: nfds:      The max fd index to probe in any of the given sets
 * @param: readfds:   [0..1] Files to test for reading (s.a. `POLLSELECT_READFDS')
 * @param: writefds:  [0..1] Files to test for writing (s.a. `POLLSELECT_WRITEFDS')
 * @param: exceptfds: [0..1] Files to test for exceptional conditions (s.a. `POLLSELECT_EXCEPTFDS')
 * @param: timeout:   [0..1] Timeout for how long to keep waiting
 * @param: sigmask:   [0..1] When non-NULL, set of signals that should _NOT_ be allowed to interrupt the system call
 *                           Semantically speaking, this mask is atomically  `SIG_SETMASK'd for the duration of  the
 *                           call being made.
 * @return: * : The # of distinct files for which a `1'-bit was written to at least one of the given sets
 * @return: 0 : The given `timeout' expired
 * @return: -1: [errno=EBADF]  One of the given sets contains an invalid file descriptor
 * @return: -1: [errno=EINTR]  The system call was interrupted
 * @return: -1: [errno=EINVAL] `timeout->tv_nsec' is invalid
 * @return: -1: [errno=ENOMEM] Insufficient kernel memory to form task connections */
__NAMESPACE_LOCAL_USING_OR_IMPL(pselect64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_IN_OPT(5) __ATTR_IN_OPT(6) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL pselect64)(__STDC_INT_AS_SIZE_T __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timespec64 const *__restrict __timeout, struct __sigset_struct const *__restrict __sigmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pselect64))(__nfds, __readfds, __writefds, __exceptfds, __timeout, __sigmask); })
#endif /* ... */
#endif /* __USE_XOPEN2K */
#endif /* __USE_TIME64 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_SELECT_H */
