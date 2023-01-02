/* HASH CRC-32:0x5332a23e */
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
#ifndef GUARD_LIBC_AUTO_KOS_FCNTL_H
#define GUARD_LIBC_AUTO_KOS_FCNTL_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/fcntl.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF __STDC_INT_AS_SSIZE_T (VLIBDCALL libd_Fcntl)(fd_t fd, int cmd, ...) THROWS(...);
INTDEF WUNUSED NONNULL((1)) fd_t (VLIBDCALL libd_Open)(char const *filename, oflag_t oflags, ...) THROWS(...);
INTDEF WUNUSED NONNULL((1)) fd_t (LIBDCALL libd_Creat)(char const *filename, mode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) fd_t (VLIBDCALL libd_Open64)(char const *filename, oflag_t oflags, ...) THROWS(...);
INTDEF WUNUSED NONNULL((1)) fd_t (LIBDCALL libd_Creat64)(char const *filename, mode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((2)) fd_t (VLIBDCALL libd_OpenAt)(fd_t dirfd, char const *filename, oflag_t oflags, ...) THROWS(...);
INTDEF WUNUSED NONNULL((2)) fd_t (VLIBDCALL libd_OpenAt64)(fd_t dirfd, char const *filename, oflag_t oflags, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_FCNTL_H */
