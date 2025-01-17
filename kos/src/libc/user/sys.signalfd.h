/* HASH CRC-32:0xcaacc0fd */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_SIGNALFD_H
#define GUARD_LIBC_USER_SYS_SIGNALFD_H 1

#include "../api.h"
#include "../auto/sys.signalfd.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/signalfd.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> signalfd(2)
 * Create or update a poll(2)-able file descriptor which can be used to
 * wait for the delivery of signals masked by `sigmask' to the  waiting
 * thread/process.
 * @param: fd:    When `-1', create a new signalfd object; Otherwise,
 *                the FD number of  the signalfd object who's  signal
 *                mask should be updated to `sigmask'.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK'
 *                Meaningless,  but  still  validated  when  `fd != -1' */
INTDEF WUNUSED ATTR_IN(2) fd_t NOTHROW_NCX(LIBCCALL libc_signalfd)(fd_t fd, sigset_t const *sigmask, __STDC_INT_AS_UINT_T flags);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SIGNALFD_H */
