/* HASH CRC-32:0xf6f1f02a */
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
#ifndef GUARD_LIBC_USER_SYS_STAT_H
#define GUARD_LIBC_USER_SYS_STAT_H 1

#include "../api.h"
#include "../auto/sys.stat.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/stat.h>

DECL_BEGIN

INTDEF ATTR_FDARG(1) NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_kos_fstat)(fd_t fd, struct __kos_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_kos_stat)(char const *__restrict filename, struct __kos_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_kos_lstat)(char const *__restrict filename, struct __kos_stat *__restrict buf);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_kos_fstatat)(fd_t dirfd, char const *__restrict filename, struct __kos_stat *__restrict buf, atflag_t flags);

INTDEF ATTR_FDARG(1) NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_cyg_fstat)(fd_t fd, struct __cyg_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_cyg_stat)(char const *__restrict filename, struct __cyg_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_cyg_lstat)(char const *__restrict filename, struct __cyg_stat *__restrict buf);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_cyg_fstatat)(fd_t dirfd, char const *__restrict filename, struct __cyg_stat *__restrict buf, atflag_t flags);

INTDEF ATTR_FDARG(1) NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_glc_fstat)(fd_t fd, struct __glc_stat *__restrict buf);
INTDEF ATTR_FDARG(1) NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_glc_fstat64)(fd_t fd, struct __glc_stat64 *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_stat)(char const *__restrict filename, struct __glc_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_stat64)(char const *__restrict filename, struct __glc_stat64 *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_lstat)(char const *__restrict filename, struct __glc_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_lstat64)(char const *__restrict filename, struct __glc_stat64 *__restrict buf);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_glc_fstatat)(fd_t dirfd, char const *__restrict filename, struct __glc_stat *__restrict buf, atflag_t flags);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_glc_fstatat64)(fd_t dirfd, char const *__restrict filename, struct __glc_stat64 *__restrict buf, atflag_t flags);

INTDEF ATTR_FDARG(1) NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_dos_fstat32)(fd_t fd, struct __dos_stat32 *__restrict buf); /* _fstat, _fstat32 */
INTDEF ATTR_FDARG(1) NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_dos_fstat32i64)(fd_t fd, struct __dos_stat32i64 *__restrict buf); /* _fstati64, _fstat32i64 */
INTDEF ATTR_FDARG(1) NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_dos_fstat64)(fd_t fd, struct __dos_stat64 *__restrict buf); /* _fstat64, _fstat64i32 */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dos_stat32)(char const *__restrict filename, struct __dos_stat32 *__restrict buf); /* _stat, _stat32 */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dos_stat32i64)(char const *__restrict filename, struct __dos_stat32i64 *__restrict buf); /* _stati64, _stat32i64 */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dos_stat64)(char const *__restrict filename, struct __dos_stat64 *__restrict buf); /* _stat64, _stat64i32 */


#ifndef __KERNEL__
/* >> mkdir(2) */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_mkdir)(char const *pathname, mode_t mode);
/* >> mkdir(2) */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBCCALL libc_mkdir)(char const *pathname, mode_t mode);
/* >> chmod(2) */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_chmod)(char const *filename, mode_t mode);
/* >> chmod(2) */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBCCALL libc_chmod)(char const *filename, mode_t mode);
/* >> lchmod(2) */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_lchmod)(char const *filename, mode_t mode);
/* >> lchmod(2) */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBCCALL libc_lchmod)(char const *filename, mode_t mode);
/* >> umask(2) */
INTDEF mode_t NOTHROW_NCX(LIBCCALL libc_umask)(mode_t mode);
/* >> getumask(2)
 * Return the current umask.
 * WARNING: This function isn't thread-safe */
INTDEF mode_t NOTHROW_NCX(LIBCCALL libc_getumask)(void);
/* >> fmkdirat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_fmkdirat)(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags);
/* >> fmkdirat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBCCALL libc_fmkdirat)(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags);
/* >> fmknodat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_fmknodat)(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags);
/* >> fmknodat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBCCALL libc_fmknodat)(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags);
/* >> fchmodat(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_fchmodat)(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags);
/* >> fchmodat(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBCCALL libc_fchmodat)(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags);
/* >> mkdirat(2) */
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_mkdirat)(fd_t dirfd, char const *pathname, mode_t mode);
/* >> mkdirat(2) */
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBCCALL libc_mkdirat)(fd_t dirfd, char const *pathname, mode_t mode);
/* >> fchmod(2) */
INTDEF ATTR_FDARG(1) int NOTHROW_RPC(LIBCCALL libc_fchmod)(fd_t fd, mode_t mode);
/* >> mknod(2) */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_mknod)(char const *nodename, mode_t mode, dev_t dev);
/* >> mknod(2) */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBCCALL libc_mknod)(char const *nodename, mode_t mode, dev_t dev);
/* >> mknodat(2) */
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_mknodat)(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev);
/* >> mknodat(2) */
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBCCALL libc_mknodat)(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev);
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) int NOTHROW_RPC(LIBDCALL libd_utimensat)(fd_t dirfd, char const *filename, struct timespec const times[2 /*or:3*/], atflag_t flags);
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) int NOTHROW_RPC(LIBCCALL libc_utimensat)(fd_t dirfd, char const *filename, struct timespec const times[2 /*or:3*/], atflag_t flags);
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) int NOTHROW_RPC(LIBDCALL libd_utimensat64)(fd_t dirfd, char const *filename, struct timespec64 const times[2 /*or:3*/], atflag_t flags);
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) int NOTHROW_RPC(LIBCCALL libc_utimensat64)(fd_t dirfd, char const *filename, struct timespec64 const times[2 /*or:3*/], atflag_t flags);
/* >> futimens(2), futimens64(2) */
INTDEF ATTR_FDARG(1) ATTR_IN_OPT(2) int NOTHROW_RPC(LIBCCALL libc_futimens)(fd_t fd, struct timespec const times[2 /*or:3*/]);
/* >> futimens(2), futimens64(2) */
INTDEF ATTR_FDARG(1) ATTR_IN_OPT(2) int NOTHROW_RPC(LIBCCALL libc_futimens64)(fd_t fd, struct timespec64 const times[2 /*or:3*/]);
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd__wstat32)(char16_t const *filename, struct __dos_stat32 *buf);
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBKCALL libc__wstat32)(char32_t const *filename, struct __dos_stat32 *buf);
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd__wstat64)(char16_t const *filename, struct __dos_stat64 *buf);
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBKCALL libc__wstat64)(char32_t const *filename, struct __dos_stat64 *buf);
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd__wstat32i64)(char16_t const *filename, struct __dos_stat32i64 *buf);
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBKCALL libc__wstat32i64)(char32_t const *filename, struct __dos_stat32i64 *buf);
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd__wstat64i32)(char16_t const *filename, struct __dos_stat64i32 *buf);
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBKCALL libc__wstat64i32)(char32_t const *filename, struct __dos_stat64i32 *buf);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_STAT_H */
