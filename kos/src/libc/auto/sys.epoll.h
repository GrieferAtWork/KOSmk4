/* HASH CRC-32:0x8d0827c5 */
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
#ifndef GUARD_LIBC_AUTO_SYS_EPOLL_H
#define GUARD_LIBC_AUTO_SYS_EPOLL_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/epoll.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> epoll_create(2)
 * Deprecated alias for `epoll_create1(0)' (the `size' argument is ignored)
 * @return: * : The newly created epoll control descriptor.
 * @return: -1: Error (s.a. `errno') */
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBDCALL libd_epoll_create)(__STDC_INT_AS_SIZE_T size);
/* >> epoll_create1(2)
 * Create  a new epoll control descriptor which can be used for
 * monitoring of pollable events happening in registered files.
 * @param: flags: Set of `EPOLL_CLOEXEC | EPOLL_CLOFORK'
 * @return: * :   The newly created epoll control descriptor.
 * @return: -1:   Error (s.a. `errno')
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS: [...] */
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBDCALL libd_epoll_create1)(__STDC_INT_AS_UINT_T flags);
/* >> epoll_ctl(2)
 * Manipulate a given  epoll controller  `epfd', as previously  returned by  `epoll_create1(2)'
 * in order to register (`EPOLL_CTL_ADD'), remove (`EPOLL_CTL_DEL') or modify (`EPOLL_CTL_MOD')
 * the file descriptors being monitored
 * @param: op:    One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL' or `EPOLL_CTL_MOD'
 * @param: fd:    The file descriptor to add/remove/modify
 * @param: event: The new configuration for `fd' (ignored when `op' is `EPOLL_CTL_DEL')
 * @return: 0 :   Success
 * @return: -1:   [errno=EEXIST][op=EPOLL_CTL_ADD] The given `fd' (and its kernel object) has already been registered
 * @return: -1:   [errno=ENOENT][op=EPOLL_CTL_MOD|EPOLL_CTL_DEL] The given `fd' (and its kernel object) aren't registered
 * @return: -1:   Error (s.a. `errno')
 * @throw: E_ILLEGAL_REFERENCE_LOOP: The  given  `fd'  is  another  epoll  that either
 *                                   forms a loop with `epfd', or has too many nested.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP: [...] */
INTDEF ATTR_FDARG(1) ATTR_FDARG(3) int NOTHROW_NCX(LIBDCALL libd_epoll_ctl)(fd_t epfd, __epoll_ctl_t op, fd_t fd, struct epoll_event *event);
/* >> epoll_wait(2)
 * Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
INTDEF ATTR_FDARG(1) ATTR_OUTS(2, 3) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBDCALL libd_epoll_wait)(fd_t epfd, struct epoll_event *events, __STDC_INT_AS_SIZE_T maxevents, int timeout);
/* >> epoll_pwait(2)
 * Same as `epoll_wait(2)', but change the calling thread's signal mask to `ss' while
 * waiting.  Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @param: ss:        The signal mask to apply while waiting for an event to happen.
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
INTDEF ATTR_FDARG(1) ATTR_OUTS(2, 3) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBDCALL libd_epoll_pwait)(fd_t epfd, struct epoll_event *events, __STDC_INT_AS_SIZE_T maxevents, int timeout, sigset_t const *ss);
/* >> epoll_rpc_exec(3)
 * Helper wrapper for  `EPOLL_CTL_RPC_PROG' that  automatically provides  the
 * necessary arch-specific RPC program to invoke `func(..., event->data.ptr)'
 * as  soon as any of `event->events' become  raised in `fd'. The monitor for
 * this is associated with `epfd' and the RPC (if not already delivered)  can
 * be canceled  by `epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL)'.  Note that  as
 * soon  as the RPC  is send, the associated  monitor will have automatically
 * been deleted.
 *
 * This  function can be used to implement asynchronous notification of file
 * events to-be  delivered  to  arbitrary threads.  Using  this,  you  could
 * implement asynchronous, non-blocking I/O by sending RPCs to an I/O worker
 * thread  that will perform  reads/writes as soon  as they become possible.
 * @param: epfd:       Epoll controller file descriptor
 * @param: fd:         The file to monitor for events
 * @param: event:      Epoll event information, including monitored  events,
 *                     and the cookie argument that will be passed to `func'
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of `RPC_DOMAIN_*'
 * @param: func:       The function executed by the RPC
 * @return: 0 :                Success
 * @return: -1: [errno=ESRCH]  The  target  thread has  already  terminated, or
 *                             doesn't exist. Note  though that  if the  target
 *                             thread  exits prior to  any monitored file event
 *                             happening, the epoll  monitor will still  remain
 *                             intact, and the  RPC will be  discarded as  soon
 *                             as an attempt to send it is made, or the monitor
 *                             is manually deleted via `EPOLL_CTL_DEL' */
INTDEF ATTR_FDARG(1) ATTR_FDARG(2) ATTR_IN(3) NONNULL((6)) int NOTHROW_NCX(LIBDCALL libd_epoll_rpc_exec)(fd_t epfd, fd_t fd, struct epoll_event const *event, pid_t target_tid, unsigned int mode, prpc_exec_callback_t func);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_EPOLL_H */
