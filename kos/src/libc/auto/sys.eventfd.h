/* HASH CRC-32:0x1b4d0199 */
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
#ifndef GUARD_LIBC_AUTO_SYS_EVENTFD_H
#define GUARD_LIBC_AUTO_SYS_EVENTFD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/eventfd.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> eventfd(2)
 * Construct a new kernel event object, and return a handle for it.
 * @param: count: The initial # of available events.
 * @param: flags: Set of `EFD_*'
 * @return: * : The newly constructed file handle. */
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBDCALL libd_eventfd)(__STDC_UINT_AS_SIZE_T count, __STDC_INT_AS_UINT_T flags);
/* >> eventfd_read(3)
 * Read the event counter, and (if not `O_NONBLOCK'), wait for an event to happen */
INTDEF ATTR_FDREAD(1) int NOTHROW_RPC(LIBDCALL libd_eventfd_read)(fd_t fd, eventfd_t *value);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> eventfd_read(3)
 * Read the event counter, and (if not `O_NONBLOCK'), wait for an event to happen */
INTDEF ATTR_FDREAD(1) int NOTHROW_RPC(LIBCCALL libc_eventfd_read)(fd_t fd, eventfd_t *value);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> eventfd_write(3)
 * Increment the event counter */
INTDEF ATTR_FDWRITE(1) int NOTHROW_RPC(LIBDCALL libd_eventfd_write)(fd_t fd, eventfd_t value);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> eventfd_write(3)
 * Increment the event counter */
INTDEF ATTR_FDWRITE(1) int NOTHROW_RPC(LIBCCALL libc_eventfd_write)(fd_t fd, eventfd_t value);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_EVENTFD_H */
