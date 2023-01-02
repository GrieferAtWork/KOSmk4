/* HASH CRC-32:0x512ee675 */
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
#ifndef GUARD_LIBC_USER_SYS_POLL_H
#define GUARD_LIBC_USER_SYS_POLL_H 1

#include "../api.h"
#include "../auto/sys.poll.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/poll.h>

DECL_BEGIN

#include <signal.h> /* sigset_t */
#ifndef __KERNEL__
/* @param timeout: Timeout in milliseconds (or negative for infinity) */
INTDEF ATTR_INOUTS(1, 2) int NOTHROW_RPC(LIBCCALL libc_poll)(struct pollfd *fds, nfds_t nfds, int timeout);
INTDEF ATTR_INOUTS(1, 2) ATTR_IN_OPT(3) ATTR_IN_OPT(4) int NOTHROW_RPC(LIBCCALL libc_ppoll)(struct pollfd *fds, nfds_t nfds, struct timespec const *timeout, sigset_t const *ss);
INTDEF ATTR_INOUTS(1, 2) ATTR_IN_OPT(3) ATTR_IN_OPT(4) int NOTHROW_RPC(LIBCCALL libc_ppoll64)(struct pollfd *fds, nfds_t nfds, struct timespec64 const *timeout, sigset_t const *ss);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_POLL_H */
