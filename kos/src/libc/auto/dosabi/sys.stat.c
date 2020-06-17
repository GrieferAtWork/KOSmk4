/* HASH CRC-32:0xef88b0f3 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_STAT_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_STAT_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.stat.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_mkdir)(char const *pathname,
                                 mode_t mode) {
	return libc_mkdir(pathname, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_chmod)(char const *filename,
                                 mode_t mode) {
	return libc_chmod(filename, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_lchmod)(char const *filename,
                                  mode_t mode) {
	return libc_lchmod(filename, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.basic_property") mode_t
NOTHROW_NCX(LIBDCALL libd_umask)(mode_t mode) {
	return libc_umask(mode);
}
/* @param flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_fmkdirat)(fd_t dirfd,
                                    char const *pathname,
                                    mode_t mode,
                                    atflag_t flags) {
	return libc_fmkdirat(dirfd, pathname, mode, flags);
}
/* @param flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_fmknodat)(fd_t dirfd,
                                    char const *nodename,
                                    mode_t mode,
                                    dev_t dev,
                                    atflag_t flags) {
	return libc_fmknodat(dirfd, nodename, mode, dev, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_mkfifo)(char const *fifoname,
                                  mode_t mode) {
	return libc_mkfifo(fifoname, mode);
}
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_fchmodat)(fd_t dirfd,
                                    char const *filename,
                                    mode_t mode,
                                    atflag_t flags) {
	return libc_fchmodat(dirfd, filename, mode, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_mkdirat)(fd_t dirfd,
                                   char const *pathname,
                                   mode_t mode) {
	return libc_mkdirat(dirfd, pathname, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_mkfifoat)(fd_t dirfd,
                                    char const *fifoname,
                                    mode_t mode) {
	return libc_mkfifoat(dirfd, fifoname, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") int
NOTHROW_RPC(LIBDCALL libd_fchmod)(fd_t fd,
                                  mode_t mode) {
	return libc_fchmod(fd, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_mknod)(char const *nodename,
                                 mode_t mode,
                                 dev_t dev) {
	return libc_mknod(nodename, mode, dev);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_mknodat)(fd_t dirfd,
                                   char const *nodename,
                                   mode_t mode,
                                   dev_t dev) {
	return libc_mknodat(dirfd, nodename, mode, dev);
}
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_utimensat)(fd_t dirfd,
                                     char const *filename,
                                     struct timespec const times[2 /*or:3*/],
                                     atflag_t flags) {
	return libc_utimensat(dirfd, filename, times, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_utimensat64)(fd_t dirfd,
                                       char const *filename,
                                       struct timespec64 const times[2 /*or:3*/],
                                       atflag_t flags) {
	return libc_utimensat64(dirfd, filename, times, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") int
NOTHROW_RPC(LIBDCALL libd_futimens)(fd_t fd,
                                    struct timespec const times[2 /*or:3*/]) {
	return libc_futimens(fd, times);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") int
NOTHROW_RPC(LIBDCALL libd_futimens64)(fd_t fd,
                                      struct timespec64 const times[2 /*or:3*/]) {
	return libc_futimens64(fd, times);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$mkdir, libd_mkdir);
DEFINE_PUBLIC_ALIAS(DOS$_chmod, libd_chmod);
DEFINE_PUBLIC_ALIAS(DOS$chmod, libd_chmod);
DEFINE_PUBLIC_ALIAS(DOS$lchmod, libd_lchmod);
DEFINE_PUBLIC_ALIAS(DOS$_umask, libd_umask);
DEFINE_PUBLIC_ALIAS(DOS$umask, libd_umask);
DEFINE_PUBLIC_ALIAS(DOS$fmkdirat, libd_fmkdirat);
DEFINE_PUBLIC_ALIAS(DOS$fmknodat, libd_fmknodat);
DEFINE_PUBLIC_ALIAS(DOS$mkfifo, libd_mkfifo);
DEFINE_PUBLIC_ALIAS(DOS$fchmodat, libd_fchmodat);
DEFINE_PUBLIC_ALIAS(DOS$mkdirat, libd_mkdirat);
DEFINE_PUBLIC_ALIAS(DOS$mkfifoat, libd_mkfifoat);
DEFINE_PUBLIC_ALIAS(DOS$fchmod, libd_fchmod);
DEFINE_PUBLIC_ALIAS(DOS$mknod, libd_mknod);
DEFINE_PUBLIC_ALIAS(DOS$mknodat, libd_mknodat);
DEFINE_PUBLIC_ALIAS(DOS$utimensat, libd_utimensat);
DEFINE_PUBLIC_ALIAS(DOS$utimensat64, libd_utimensat64);
DEFINE_PUBLIC_ALIAS(DOS$futimens, libd_futimens);
DEFINE_PUBLIC_ALIAS(DOS$futimens64, libd_futimens64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_STAT_C */
