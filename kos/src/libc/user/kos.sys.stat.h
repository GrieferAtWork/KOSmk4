/* HASH CRC-32:0x599fab72 */
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
#ifndef GUARD_LIBC_USER_KOS_SYS_STAT_H
#define GUARD_LIBC_USER_KOS_SYS_STAT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/sys/stat.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> mkdir(2) */
INTDEF ATTR_IN(1) void (LIBCCALL libc_MkDir)(char const *pathname, mode_t mode) THROWS(...);
/* >> chmod(2) */
INTDEF ATTR_IN(1) void (LIBCCALL libc_ChMod)(char const *filename, mode_t mode) THROWS(...);
/* >> lchmod(2) */
INTDEF ATTR_IN(1) void (LIBCCALL libc_LChMod)(char const *filename, mode_t mode) THROWS(...);
/* >> fmkdirat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
INTDEF ATTR_IN(2) void (LIBCCALL libc_FMkDirAt)(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) THROWS(...);
/* >> fmknodat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
INTDEF ATTR_IN(2) void (LIBCCALL libc_FMkNodAt)(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) THROWS(...);
/* >> mkfifo(2) */
INTDEF ATTR_IN(1) void (LIBCCALL libc_MkFiFo)(char const *fifoname, mode_t mode) THROWS(...);
/* >> fchmodat(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
INTDEF ATTR_IN(2) void (LIBCCALL libc_FChModAt)(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) THROWS(...);
/* >> mkdirat(2) */
INTDEF ATTR_IN(2) void (LIBCCALL libc_MkDirAt)(fd_t dirfd, char const *pathname, mode_t mode) THROWS(...);
/* >> mkfifoat(2) */
INTDEF ATTR_IN(2) void (LIBCCALL libc_MkFiFoAt)(fd_t dirfd, char const *fifoname, mode_t mode) THROWS(...);
/* >> fchmod(2) */
INTDEF ATTR_FDARG(1) void (LIBCCALL libc_FChMod)(fd_t fd, mode_t mode) THROWS(...);
/* >> mknod(2) */
INTDEF ATTR_IN(1) void (LIBCCALL libc_MkNod)(char const *nodename, mode_t mode, dev_t dev) THROWS(...);
/* >> mknodat(2) */
INTDEF ATTR_IN(2) void (LIBCCALL libc_MkNodAt)(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) THROWS(...);
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) void (LIBCCALL libc_UTimensAt)(fd_t dirfd, char const *filename, struct timespec const times[2 /*or:3*/], atflag_t flags) THROWS(...);
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) void (LIBCCALL libc_UTimensAt64)(fd_t dirfd, char const *filename, struct timespec64 const times[2 /*or:3*/], atflag_t flags) THROWS(...);
/* >> futimens(2), futimens64(2) */
INTDEF ATTR_FDARG(1) ATTR_IN_OPT(2) void (LIBCCALL libc_FUTimens)(fd_t fd, struct timespec const times[2 /*or:3*/]) THROWS(...);
/* >> futimens(2), futimens64(2) */
INTDEF ATTR_FDARG(1) ATTR_IN_OPT(2) void (LIBCCALL libc_FUTimens64)(fd_t fd, struct timespec64 const times[2 /*or:3*/]) THROWS(...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_SYS_STAT_H */
