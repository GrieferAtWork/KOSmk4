/* HASH CRC-32:0x79633764 */
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
#ifndef GUARD_LIBC_USER_SYS_POLL_H
#define GUARD_LIBC_USER_SYS_POLL_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/poll.h>

DECL_BEGIN

DECL_END
#include <bits/sigset.h>
DECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef __sigset_t sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __KERNEL__
/* @param timeout: Timeout in milliseconds (or negative for infinity) */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_poll)(struct pollfd *fds, nfds_t nfds, int timeout);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_ppoll)(struct pollfd *fds, nfds_t nfds, struct timespec const *timeout, sigset_t const *ss);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_ppoll64)(struct pollfd *fds, nfds_t nfds, struct timespec64 const *timeout, sigset_t const *ss);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_POLL_H */
