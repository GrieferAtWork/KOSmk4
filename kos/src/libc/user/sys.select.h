/* HASH CRC-32:0x4cfd0cae */
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
#ifndef GUARD_LIBC_USER_SYS_SELECT_H
#define GUARD_LIBC_USER_SYS_SELECT_H 1

#include "../api.h"
#include "../auto/sys.select.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/select.h>

DECL_BEGIN

#include <signal.h>
#ifndef __KERNEL__
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
INTDEF ATTR_INOUT_OPT(2) ATTR_INOUT_OPT(3) ATTR_INOUT_OPT(4) ATTR_INOUT_OPT(5) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_select)(__STDC_INT_AS_SIZE_T nfds, fd_set *__restrict readfds, fd_set *__restrict writefds, fd_set *__restrict exceptfds, struct timeval *__restrict timeout);
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
INTDEF ATTR_INOUT_OPT(2) ATTR_INOUT_OPT(3) ATTR_INOUT_OPT(4) ATTR_IN_OPT(5) ATTR_IN_OPT(6) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_pselect)(__STDC_INT_AS_SIZE_T nfds, fd_set *__restrict readfds, fd_set *__restrict writefds, fd_set *__restrict exceptfds, struct timespec const *__restrict timeout, sigset_t const *__restrict sigmask);
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
INTDEF ATTR_INOUT_OPT(2) ATTR_INOUT_OPT(3) ATTR_INOUT_OPT(4) ATTR_INOUT_OPT(5) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_select64)(__STDC_INT_AS_SIZE_T nfds, fd_set *__restrict readfds, fd_set *__restrict writefds, fd_set *__restrict exceptfds, struct timeval64 *__restrict timeout);
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
INTDEF ATTR_INOUT_OPT(2) ATTR_INOUT_OPT(3) ATTR_INOUT_OPT(4) ATTR_IN_OPT(5) ATTR_IN_OPT(6) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_pselect64)(__STDC_INT_AS_SIZE_T nfds, fd_set *__restrict readfds, fd_set *__restrict writefds, fd_set *__restrict exceptfds, struct timespec64 const *__restrict timeout, sigset_t const *__restrict sigmask);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SELECT_H */
