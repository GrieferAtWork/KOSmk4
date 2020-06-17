/* HASH CRC-32:0x991f8a33 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_KOS_SYS_STAT_C
#define GUARD_LIBC_AUTO_DOSABI_KOS_SYS_STAT_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/kos.sys.stat.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((1)) void
(LIBDCALL libd_Mkdir)(char const *pathname,
                      mode_t mode) THROWS(...) {
	libc_Mkdir(pathname, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((1)) void
(LIBDCALL libd_Chmod)(char const *filename,
                      mode_t mode) THROWS(...) {
	libc_Chmod(filename, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((1)) void
(LIBDCALL libd_LChmod)(char const *filename,
                       mode_t mode) THROWS(...) {
	libc_LChmod(filename, mode);
}
/* @param flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((2)) void
(LIBDCALL libd_FMkdirAt)(fd_t dirfd,
                         char const *pathname,
                         mode_t mode,
                         atflag_t flags) THROWS(...) {
	libc_FMkdirAt(dirfd, pathname, mode, flags);
}
/* @param flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((2)) void
(LIBDCALL libd_FMknodAt)(fd_t dirfd,
                         char const *nodename,
                         mode_t mode,
                         dev_t dev,
                         atflag_t flags) THROWS(...) {
	libc_FMknodAt(dirfd, nodename, mode, dev, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((1)) void
(LIBDCALL libd_Mkfifo)(char const *fifoname,
                       mode_t mode) THROWS(...) {
	libc_Mkfifo(fifoname, mode);
}
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((2)) void
(LIBDCALL libd_FChmodAt)(fd_t dirfd,
                         char const *filename,
                         mode_t mode,
                         atflag_t flags) THROWS(...) {
	libc_FChmodAt(dirfd, filename, mode, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((2)) void
(LIBDCALL libd_MkdirAt)(fd_t dirfd,
                        char const *pathname,
                        mode_t mode) THROWS(...) {
	libc_MkdirAt(dirfd, pathname, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((2)) void
(LIBDCALL libd_MkfifoAt)(fd_t dirfd,
                         char const *fifoname,
                         mode_t mode) THROWS(...) {
	libc_MkfifoAt(dirfd, fifoname, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") void
(LIBDCALL libd_FChmod)(fd_t fd,
                       mode_t mode) THROWS(...) {
	libc_FChmod(fd, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((1)) void
(LIBDCALL libd_Mknod)(char const *nodename,
                      mode_t mode,
                      dev_t dev) THROWS(...) {
	libc_Mknod(nodename, mode, dev);
}
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((2)) void
(LIBDCALL libd_MknodAt)(fd_t dirfd,
                        char const *nodename,
                        mode_t mode,
                        dev_t dev) THROWS(...) {
	libc_MknodAt(dirfd, nodename, mode, dev);
}
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify_time") NONNULL((2)) void
(LIBDCALL libd_UTimensAt)(fd_t dirfd,
                          char const *filename,
                          struct timespec const times[2 /*or:3*/],
                          atflag_t flags) THROWS(...) {
	libc_UTimensAt(dirfd, filename, times, flags);
}
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify_time") NONNULL((2)) void
(LIBDCALL libd_UTimensAt64)(fd_t dirfd,
                            char const *filename,
                            struct timespec64 const times[2 /*or:3*/],
                            atflag_t flags) THROWS(...) {
	libc_UTimensAt64(dirfd, filename, times, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify_time") void
(LIBDCALL libd_FUtimens)(fd_t fd,
                         struct timespec const times[2 /*or:3*/]) THROWS(...) {
	libc_FUtimens(fd, times);
}
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify_time") void
(LIBDCALL libd_FUtimens64)(fd_t fd,
                           struct timespec64 const times[2 /*or:3*/]) THROWS(...) {
	libc_FUtimens64(fd, times);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$Mkdir, libd_Mkdir);
DEFINE_PUBLIC_ALIAS(DOS$Chmod, libd_Chmod);
DEFINE_PUBLIC_ALIAS(DOS$LChmod, libd_LChmod);
DEFINE_PUBLIC_ALIAS(DOS$FMkdirAt, libd_FMkdirAt);
DEFINE_PUBLIC_ALIAS(DOS$FMknodAt, libd_FMknodAt);
DEFINE_PUBLIC_ALIAS(DOS$Mkfifo, libd_Mkfifo);
DEFINE_PUBLIC_ALIAS(DOS$FChmodAt, libd_FChmodAt);
DEFINE_PUBLIC_ALIAS(DOS$MkdirAt, libd_MkdirAt);
DEFINE_PUBLIC_ALIAS(DOS$MkfifoAt, libd_MkfifoAt);
DEFINE_PUBLIC_ALIAS(DOS$FChmod, libd_FChmod);
DEFINE_PUBLIC_ALIAS(DOS$Mknod, libd_Mknod);
DEFINE_PUBLIC_ALIAS(DOS$MknodAt, libd_MknodAt);
DEFINE_PUBLIC_ALIAS(DOS$UTimensAt, libd_UTimensAt);
DEFINE_PUBLIC_ALIAS(DOS$UTimensAt64, libd_UTimensAt64);
DEFINE_PUBLIC_ALIAS(DOS$FUtimens, libd_FUtimens);
DEFINE_PUBLIC_ALIAS(DOS$FUtimens64, libd_FUtimens64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_KOS_SYS_STAT_C */
