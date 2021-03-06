/* HASH CRC-32:0x8429f636 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_KOS_SYS_STAT_H
#define GUARD_LIBC_AUTO_KOS_SYS_STAT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/sys/stat.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) void (LIBDCALL libd_Mkdir)(char const *pathname, mode_t mode) THROWS(...);
INTDEF NONNULL((1)) void (LIBDCALL libd_Chmod)(char const *filename, mode_t mode) THROWS(...);
INTDEF NONNULL((1)) void (LIBDCALL libd_LChmod)(char const *filename, mode_t mode) THROWS(...);
/* @param flags: Set of `0 | AT_DOSPATH' */
INTDEF NONNULL((2)) void (LIBDCALL libd_FMkdirAt)(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) THROWS(...);
/* @param flags: Set of `0 | AT_DOSPATH' */
INTDEF NONNULL((2)) void (LIBDCALL libd_FMknodAt)(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) THROWS(...);
INTDEF NONNULL((1)) void (LIBDCALL libd_Mkfifo)(char const *fifoname, mode_t mode) THROWS(...);
/* @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
INTDEF NONNULL((2)) void (LIBDCALL libd_FChmodAt)(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) THROWS(...);
INTDEF NONNULL((2)) void (LIBDCALL libd_MkdirAt)(fd_t dirfd, char const *pathname, mode_t mode) THROWS(...);
INTDEF NONNULL((2)) void (LIBDCALL libd_MkfifoAt)(fd_t dirfd, char const *fifoname, mode_t mode) THROWS(...);
INTDEF void (LIBDCALL libd_FChmod)(fd_t fd, mode_t mode) THROWS(...);
INTDEF NONNULL((1)) void (LIBDCALL libd_Mknod)(char const *nodename, mode_t mode, dev_t dev) THROWS(...);
INTDEF NONNULL((2)) void (LIBDCALL libd_MknodAt)(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) THROWS(...);
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
INTDEF NONNULL((2)) void (LIBDCALL libd_UTimensAt)(fd_t dirfd, char const *filename, struct timespec const times[2 /*or:3*/], atflag_t flags) THROWS(...);
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
INTDEF NONNULL((2)) void (LIBDCALL libd_UTimensAt64)(fd_t dirfd, char const *filename, struct timespec64 const times[2 /*or:3*/], atflag_t flags) THROWS(...);
INTDEF void (LIBDCALL libd_FUtimens)(fd_t fd, struct timespec const times[2 /*or:3*/]) THROWS(...);
INTDEF void (LIBDCALL libd_FUtimens64)(fd_t fd, struct timespec64 const times[2 /*or:3*/]) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_SYS_STAT_H */
