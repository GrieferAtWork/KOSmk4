/* HASH CRC-32:0x98a75d37 */
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
#ifndef GUARD_LIBC_AUTO_SYS_STAT_H
#define GUARD_LIBC_AUTO_SYS_STAT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/stat.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> umask(2) */
INTDEF mode_t NOTHROW_NCX(LIBDCALL libd_umask)(mode_t mode);
/* >> fchmod(2) */
INTDEF int NOTHROW_RPC(LIBDCALL libd_fchmod)(fd_t fd, mode_t mode);
/* >> futimens(2), futimens64(2) */
INTDEF int NOTHROW_RPC(LIBDCALL libd_futimens)(fd_t fd, struct timespec const times[2 /*or:3*/]);
/* >> futimens(2), futimens64(2) */
INTDEF int NOTHROW_RPC(LIBDCALL libd_futimens64)(fd_t fd, struct timespec64 const times[2 /*or:3*/]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_STAT_H */
