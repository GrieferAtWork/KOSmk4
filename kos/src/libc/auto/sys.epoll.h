/* HASH CRC-32:0x8cf5bd4a */
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
 * Create a new epoll control descriptor which can be used for
 * monitoring of pollable events happening in registered files.
 * @param: flags: Set of `EPOLL_*'
 * @return: * :   The newly created epoll control descriptor.
 * @return: -1:   [errno=EINVAL] Invalid `flags'
 * @return: -1:   Error (s.a. `errno') */
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBDCALL libd_epoll_create1)(__STDC_INT_AS_UINT_T flags);
/* >> epoll_ctl(2)
 * Manipulate a given epoll controller `epfd', as previously returned by `epoll_create1(2)'
 * in order to register (`EPOLL_CTL_ADD'), remove (`EPOLL_CTL_DEL') or modify (`EPOLL_CTL_MOD')
 * the file descriptors being monitored
 * @param: op:    One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL' or `EPOLL_CTL_MOD'
 * @param: fd:    The file descriptor to add/remove/modify
 * @param: event: The new configuration for `fd' (ignored when `op' is `EPOLL_CTL_DEL')
 * @return: 0 :   Success
 * @return: -1:   Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_epoll_ctl)(fd_t epfd, __epoll_ctl_t op, fd_t fd, struct epoll_event *event);
/* >> epoll_wait(2)
 * Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
INTDEF NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBDCALL libd_epoll_wait)(fd_t epfd, struct epoll_event *events, __STDC_INT_AS_SIZE_T maxevents, int timeout);
/* >> epoll_pwait(2)
 * Same as `epoll_wait(2)', but change the calling thread's signal mask to `ss' while
 * waiting. Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @param: ss:        The signal mask to apply while waiting for an event to happen.
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
INTDEF NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBDCALL libd_epoll_pwait)(fd_t epfd, struct epoll_event *events, __STDC_INT_AS_SIZE_T maxevents, int timeout, sigset_t const *ss);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_EPOLL_H */
