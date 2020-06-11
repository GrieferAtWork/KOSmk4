/* HASH CRC-32:0xa1b371a7 */
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
#ifndef GUARD_LIBC_USER_SYS_STAT_H
#define GUARD_LIBC_USER_SYS_STAT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/stat.h>

DECL_BEGIN

INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_kos_fstat)(fd_t fd, struct __kos_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_kos_stat)(char const *__restrict filename, struct __kos_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_kos_lstat)(char const *__restrict filename, struct __kos_stat *__restrict buf);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_kos_fstatat)(fd_t dirfd, char const *__restrict filename, struct __kos_stat *__restrict buf, atflag_t flags);

INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_cyg_fstat)(fd_t fd, struct __cyg_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_cyg_stat)(char const *__restrict filename, struct __cyg_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_cyg_lstat)(char const *__restrict filename, struct __cyg_stat *__restrict buf);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_cyg_fstatat)(fd_t dirfd, char const *__restrict filename, struct __cyg_stat *__restrict buf, atflag_t flags);

INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_glc_fstat)(fd_t fd, struct __glc_stat *__restrict buf);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_glc_fstat64)(fd_t fd, struct __glc_stat64 *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_stat)(char const *__restrict filename, struct __glc_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_stat64)(char const *__restrict filename, struct __glc_stat64 *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_lstat)(char const *__restrict filename, struct __glc_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_lstat64)(char const *__restrict filename, struct __glc_stat64 *__restrict buf);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_glc_fstatat)(fd_t dirfd, char const *__restrict filename, struct __glc_stat *__restrict buf, atflag_t flags);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_glc_fstatat64)(fd_t dirfd, char const *__restrict filename, struct __glc_stat64 *__restrict buf, atflag_t flags);

INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_dos_fstat32)(fd_t fd, struct __dos_stat32 *__restrict buf); /* _fstat, _fstat32 */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_dos_fstat32i64)(fd_t fd, struct __dos_stat32i64 *__restrict buf); /* _fstati64, _fstat32i64 */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_dos_fstat64)(fd_t fd, struct __dos_stat64 *__restrict buf); /* _fstat64, _fstat64i32 */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dos_stat32)(char const *__restrict filename, struct __dos_stat32 *__restrict buf); /* _stat, _stat32 */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dos_stat32i64)(char const *__restrict filename, struct __dos_stat32i64 *__restrict buf); /* _stati64, _stat32i64 */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dos_stat64)(char const *__restrict filename, struct __dos_stat64 *__restrict buf); /* _stat64, _stat64i32 */


#ifndef __KERNEL__
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_mkdir)(char const *pathname, mode_t mode);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_chmod)(char const *filename, mode_t mode);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_lchmod)(char const *filename, mode_t mode);
INTDEF mode_t NOTHROW_NCX(LIBCCALL libc_umask)(mode_t mode);
/* Return the current umask.
 * WARNING: This function isn't thread-safe */
INTDEF mode_t NOTHROW_NCX(LIBCCALL libc_getumask)(void);
/* @param flags: Set of `0 | AT_DOSPATH' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_fmkdirat)(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags);
/* @param flags: Set of `0 | AT_DOSPATH' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_fmknodat)(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_mkfifo)(char const *fifoname, mode_t mode);
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_fchmodat)(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags);
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_mkdirat)(fd_t dirfd, char const *pathname, mode_t mode);
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_mkfifoat)(fd_t dirfd, char const *fifoname, mode_t mode);
INTDEF int NOTHROW_RPC(LIBCCALL libc_fchmod)(fd_t fd, mode_t mode);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_mknod)(char const *nodename, mode_t mode, dev_t dev);
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_mknodat)(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev);
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_utimensat)(fd_t dirfd, char const *filename, struct timespec const times[2 /*or:3*/], atflag_t flags);
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_utimensat64)(fd_t dirfd, char const *filename, struct timespec64 const times[2 /*or:3*/], atflag_t flags);
INTDEF int NOTHROW_RPC(LIBCCALL libc_futimens)(fd_t fd, struct timespec const times[2 /*or:3*/]);
INTDEF int NOTHROW_RPC(LIBCCALL libc_futimens64)(fd_t fd, struct timespec64 const times[2 /*or:3*/]);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__wstat32)(char16_t const *filename, struct __dos_stat32 *buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc__wstat32)(char32_t const *filename, struct __dos_stat32 *buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__wstat64)(char16_t const *filename, struct __dos_stat64 *buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc__wstat64)(char32_t const *filename, struct __dos_stat64 *buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__wstat32i64)(char16_t const *filename, struct __dos_stat32i64 *buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc__wstat32i64)(char32_t const *filename, struct __dos_stat32i64 *buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd__wstat64i32)(char16_t const *filename, struct __dos_stat64i32 *buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBKCALL libc__wstat64i32)(char32_t const *filename, struct __dos_stat64i32 *buf);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_STAT_H */
