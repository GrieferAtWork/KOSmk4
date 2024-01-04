/* HASH CRC-32:0xa421a6de */
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
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_SYS_STAT_H
#define GUARD_LIBC_AUTO_PARTS_WCHAR_SYS_STAT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/sys/stat.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_wmkdir)(char16_t const *pathname, mode_t mode);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_wmkdir)(char32_t const *pathname, mode_t mode);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_wchmod)(char16_t const *filename, mode_t mode);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_wchmod)(char32_t const *filename, mode_t mode);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_wlchmod)(char16_t const *filename, mode_t mode);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_wlchmod)(char32_t const *filename, mode_t mode);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wfmkdirat)(fd_t dirfd, char16_t const *pathname, mode_t mode, atflag_t flags);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wfmkdirat)(fd_t dirfd, char32_t const *pathname, mode_t mode, atflag_t flags);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wfmknodat)(fd_t dirfd, char16_t const *nodename, mode_t mode, dev_t dev, atflag_t flags);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wfmknodat)(fd_t dirfd, char32_t const *nodename, mode_t mode, dev_t dev, atflag_t flags);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_wmkfifo)(char16_t const *fifoname, mode_t mode);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_wmkfifo)(char32_t const *fifoname, mode_t mode);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wfchmodat)(fd_t dirfd, char16_t const *filename, mode_t mode, atflag_t flags);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wfchmodat)(fd_t dirfd, char32_t const *filename, mode_t mode, atflag_t flags);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wmkdirat)(fd_t dirfd, char16_t const *pathname, mode_t mode);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wmkdirat)(fd_t dirfd, char32_t const *pathname, mode_t mode);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wmkfifoat)(fd_t dirfd, char16_t const *fifoname, mode_t mode);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wmkfifoat)(fd_t dirfd, char32_t const *fifoname, mode_t mode);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_wmknod)(char16_t const *nodename, mode_t mode, dev_t dev);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_wmknod)(char32_t const *nodename, mode_t mode, dev_t dev);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wmknodat)(fd_t dirfd, char16_t const *nodename, mode_t mode, dev_t dev);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wmknodat)(fd_t dirfd, char32_t const *nodename, mode_t mode, dev_t dev);
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) int NOTHROW_RPC(LIBDCALL libd_wutimensat)(fd_t dirfd, char16_t const *filename, struct timespec const times[2 /*or:3*/], atflag_t flags);
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) int NOTHROW_RPC(LIBKCALL libc_wutimensat)(fd_t dirfd, char32_t const *filename, struct timespec const times[2 /*or:3*/], atflag_t flags);
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) int NOTHROW_RPC(LIBDCALL libd_wutimensat64)(fd_t dirfd, char16_t const *filename, struct timespec64 const times[2 /*or:3*/], atflag_t flags);
INTDEF ATTR_IN(2) ATTR_IN_OPT(3) int NOTHROW_RPC(LIBKCALL libc_wutimensat64)(fd_t dirfd, char32_t const *filename, struct timespec64 const times[2 /*or:3*/], atflag_t flags);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_SYS_STAT_H */
