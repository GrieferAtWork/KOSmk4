/* HASH CRC-32:0x7a4dda90 */
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
#ifndef GUARD_LIBC_AUTO_SYS_XATTR_H
#define GUARD_LIBC_AUTO_SYS_XATTR_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/xattr.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setxattr(2)
 * @param: flags: One of `XATTR_*', or `0' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INS(3, 4) int NOTHROW_RPC(LIBDCALL libd_setxattr)(char const *path, char const *name, void const *buf, size_t bufsize, __STDC_INT_AS_UINT_T flags);
/* >> lsetxattr(2)
 * @param: flags: One of `XATTR_*', or `0' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INS(3, 4) int NOTHROW_RPC(LIBDCALL libd_lsetxattr)(char const *path, char const *name, void const *buf, size_t bufsize, __STDC_INT_AS_UINT_T flags);
/* >> fsetxattr(2)
 * @param: flags: One of `XATTR_*', or `0' */
INTDEF ATTR_FDARG(1) ATTR_IN(2) ATTR_INS(3, 4) int NOTHROW_RPC(LIBDCALL libd_fsetxattr)(fd_t fd, char const *name, void const *buf, size_t bufsize, __STDC_INT_AS_UINT_T flags);
/* >> getxattr(2) */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t NOTHROW_RPC(LIBDCALL libd_getxattr)(char const *path, char const *name, void *buf, size_t bufsize);
/* >> lgetxattr(2) */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t NOTHROW_RPC(LIBDCALL libd_lgetxattr)(char const *path, char const *name, void *buf, size_t bufsize);
/* >> fgetxattr(2) */
INTDEF ATTR_FDARG(1) ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t NOTHROW_RPC(LIBDCALL libd_fgetxattr)(fd_t fd, char const *name, void *buf, size_t bufsize);
/* >> listxattr(2) */
INTDEF ATTR_IN(1) ATTR_OUTS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_listxattr)(char const *path, char *listbuf, size_t listbufsize);
/* >> llistxattr(2) */
INTDEF ATTR_IN(1) ATTR_OUTS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_llistxattr)(char const *path, char *listbuf, size_t listbufsize);
/* >> flistxattr(2) */
INTDEF ATTR_FDARG(1) ATTR_OUTS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_flistxattr)(fd_t fd, char *listbuf, size_t listbufsize);
/* >> removexattr(2) */
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_removexattr)(char const *path, char const *name);
/* >> lremovexattr(2) */
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_lremovexattr)(char const *path, char const *name);
/* >> fremovexattr(2) */
INTDEF ATTR_FDARG(1) ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_fremovexattr)(fd_t fd, char const *name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_XATTR_H */
