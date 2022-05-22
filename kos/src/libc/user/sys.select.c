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
#ifndef GUARD_LIBC_USER_SYS_SELECT_C
#define GUARD_LIBC_USER_SYS_SELECT_C 1

#include "../api.h"
/**/

#include <bits/os/sigset_with_size.h>
#include <kos/syscalls.h>

#include <syscall.h> /* SYS_* */

#include "sys.select.h"

#ifndef SYS__newselect
/* Pull in information to figure out what kind of
 * select() function is  exported by the  kernel. */
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_COUNT
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#include <asm/syscalls-proto.h>
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_COUNT */
#endif /* !SYS__newselect */

DECL_BEGIN

/*[[[head:libc_select,hash:CRC-32=0xb57124a7]]]*/
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first  `nfds' elementes  of the  respective sets  are considered, thus
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
INTERN ATTR_SECTION(".text.crt.io.poll") ATTR_INOUT_OPT(2) ATTR_INOUT_OPT(3) ATTR_INOUT_OPT(4) ATTR_INOUT_OPT(5) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_select)(__STDC_INT_AS_SIZE_T nfds,
                                  fd_set *__restrict readfds,
                                  fd_set *__restrict writefds,
                                  fd_set *__restrict exceptfds,
                                  struct timeval *__restrict timeout)
/*[[[body:libc_select]]]*/
{
	ssize_t result;
#ifdef SYS__newselect
	result = sys__newselect(nfds, readfds, writefds, exceptfds, timeout);
#elif __NRAC_select == 5
	result = sys_select(nfds, readfds, writefds, exceptfds, timeout);
#elif __NRAC_select == 1
	/* Must use `struct sel_arg_struct' */
	struct sel_arg_struct arg;
	arg.n    = (ulongptr_t)nfds;
	arg.inp  = readfds;
	arg.outp = writefds;
	arg.exp  = exceptfds;
	arg.tvp  = timeout;
	result   = sys_select(&arg);
#else /* ... */
#error "Unrecognized sys_select() variant"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_select]]]*/


/*[[[head:libc_pselect,hash:CRC-32=0xdd223bbb]]]*/
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first  `nfds' elementes  of the  respective sets  are considered, thus
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
INTERN ATTR_SECTION(".text.crt.io.poll") ATTR_INOUT_OPT(2) ATTR_INOUT_OPT(3) ATTR_INOUT_OPT(4) ATTR_IN_OPT(5) ATTR_IN_OPT(6) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_pselect)(__STDC_INT_AS_SIZE_T nfds,
                                   fd_set *__restrict readfds,
                                   fd_set *__restrict writefds,
                                   fd_set *__restrict exceptfds,
                                   struct timespec const *__restrict timeout,
                                   sigset_t const *__restrict sigmask)
/*[[[body:libc_pselect]]]*/
{
	ssize_t result;
	struct sigset_with_size ss;
	ss.sws_sigset = (sigset_t *)sigmask;
	ss.sws_sigsiz = sizeof(sigset_t);
	result = sys_pselect6(nfds, readfds, writefds, exceptfds, timeout, &ss);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_pselect]]]*/

/*[[[head:libc_select64,hash:CRC-32=0xc8ac12b1]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_select64, libc_select);
#else /* MAGIC:alias */
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first  `nfds' elementes  of the  respective sets  are considered, thus
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
INTERN ATTR_SECTION(".text.crt.io.poll") ATTR_INOUT_OPT(2) ATTR_INOUT_OPT(3) ATTR_INOUT_OPT(4) ATTR_INOUT_OPT(5) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_select64)(__STDC_INT_AS_SIZE_T nfds,
                                    fd_set *__restrict readfds,
                                    fd_set *__restrict writefds,
                                    fd_set *__restrict exceptfds,
                                    struct timeval64 *__restrict timeout)
/*[[[body:libc_select64]]]*/
{
	ssize_t result;
#ifdef SYS_select64
	result = sys_select64(nfds, readfds, writefds, exceptfds, timeout);
#elif defined(SYS_select_time64)
	result = sys_select_time64(nfds, readfds, writefds, exceptfds, timeout);
#else /* ... */
#error "No way to implement `select64()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_select64]]]*/

/*[[[head:libc_pselect64,hash:CRC-32=0x525c0335]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pselect64, libc_pselect);
#else /* MAGIC:alias */
/* >> select(2), select64(2), pselect(2), pselect64(2)
 * Wait for read/write/other events to become possible (without blocking)
 * on the file descriptors within  any given non-NULL `fd_set'. Only  the
 * first  `nfds' elementes  of the  respective sets  are considered, thus
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
INTERN ATTR_SECTION(".text.crt.io.poll") ATTR_INOUT_OPT(2) ATTR_INOUT_OPT(3) ATTR_INOUT_OPT(4) ATTR_IN_OPT(5) ATTR_IN_OPT(6) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_pselect64)(__STDC_INT_AS_SIZE_T nfds,
                                     fd_set *__restrict readfds,
                                     fd_set *__restrict writefds,
                                     fd_set *__restrict exceptfds,
                                     struct timespec64 const *__restrict timeout,
                                     sigset_t const *__restrict sigmask)
/*[[[body:libc_pselect64]]]*/
{
	ssize_t result;
	struct sigset_with_size ss;
	ss.sws_sigset = (sigset_t *)sigmask;
	ss.sws_sigsiz = sizeof(sigset_t);
#ifdef SYS_pselect6_64
	result = sys_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, &ss);
#elif defined(SYS_pselect6_time64)
	result = sys_pselect6_time64(nfds, readfds, writefds, exceptfds, timeout, &ss);
#else /* ... */
#error "No way to implement `pselect64()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pselect64]]]*/





/*[[[start:exports,hash:CRC-32=0x80a21f10]]]*/
DEFINE_PUBLIC_ALIAS(__select, libc_select);
DEFINE_PUBLIC_ALIAS(select, libc_select);
DEFINE_PUBLIC_ALIAS(pselect, libc_pselect);
DEFINE_PUBLIC_ALIAS(select64, libc_select64);
DEFINE_PUBLIC_ALIAS(pselect64, libc_pselect64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SELECT_C */
