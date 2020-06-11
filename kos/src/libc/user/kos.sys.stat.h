/* HASH CRC-32:0x88d3b4c2 */
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
#ifndef GUARD_LIBC_USER_KOS_SYS_STAT_H
#define GUARD_LIBC_USER_KOS_SYS_STAT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/sys/stat.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF NONNULL((1)) void (LIBCCALL libc_Mkdir)(char const *pathname, mode_t mode) THROWS(...);
INTDEF NONNULL((1)) void (LIBCCALL libc_Chmod)(char const *filename, mode_t mode) THROWS(...);
INTDEF NONNULL((1)) void (LIBCCALL libc_LChmod)(char const *filename, mode_t mode) THROWS(...);
/* @param flags: Set of `0 | AT_DOSPATH' */
INTDEF NONNULL((2)) void (LIBCCALL libc_FMkdirAt)(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) THROWS(...);
/* @param flags: Set of `0 | AT_DOSPATH' */
INTDEF NONNULL((2)) void (LIBCCALL libc_FMknodAt)(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) THROWS(...);
INTDEF NONNULL((1)) void (LIBCCALL libc_Mkfifo)(char const *fifoname, mode_t mode) THROWS(...);
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
INTDEF NONNULL((2)) void (LIBCCALL libc_FChmodAt)(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) THROWS(...);
INTDEF NONNULL((2)) void (LIBCCALL libc_MkdirAt)(fd_t dirfd, char const *pathname, mode_t mode) THROWS(...);
INTDEF NONNULL((2)) void (LIBCCALL libc_MkfifoAt)(fd_t dirfd, char const *fifoname, mode_t mode) THROWS(...);
INTDEF void (LIBCCALL libc_FChmod)(fd_t fd, mode_t mode) THROWS(...);
INTDEF NONNULL((1)) void (LIBCCALL libc_Mknod)(char const *nodename, mode_t mode, dev_t dev) THROWS(...);
INTDEF NONNULL((2)) void (LIBCCALL libc_MknodAt)(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) THROWS(...);
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
INTDEF NONNULL((2)) void (LIBCCALL libc_UTimensAt)(fd_t dirfd, char const *filename, struct timespec const times[2 /*or:3*/], atflag_t flags) THROWS(...);
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
INTDEF NONNULL((2)) void (LIBCCALL libc_UTimensAt64)(fd_t dirfd, char const *filename, struct timespec64 const times[2 /*or:3*/], atflag_t flags) THROWS(...);
INTDEF void (LIBCCALL libc_FUtimens)(fd_t fd, struct timespec const times[2 /*or:3*/]) THROWS(...);
INTDEF void (LIBCCALL libc_FUtimens64)(fd_t fd, struct timespec64 const times[2 /*or:3*/]) THROWS(...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_SYS_STAT_H */
