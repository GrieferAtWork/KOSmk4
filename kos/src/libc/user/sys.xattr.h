/* HASH CRC-32:0xa8d691dc */
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
#ifndef GUARD_LIBC_USER_SYS_XATTR_H
#define GUARD_LIBC_USER_SYS_XATTR_H 1

#include "../api.h"
#include "../auto/sys.xattr.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/xattr.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Set the attribute NAME of the file pointed to by PATH to VALUE
 * (which is SIZE bytes long). Return 0 on success, -1 for errors
 * @param: flags: 0, or a one of `XATTR_*' */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBCCALL libc_setxattr)(char const *path, char const *name, void const *buf, size_t bufsize, __STDC_INT_AS_UINT_T flags);
/* Set the attribute NAME of the file pointed to by PATH to VALUE (which is
 * SIZE bytes long), not following symlinks for the last pathname component.
 * Return 0 on success, -1 for errors
 * @param: flags: 0, or a one of `XATTR_*' */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBCCALL libc_lsetxattr)(char const *path, char const *name, void const *buf, size_t bufsize, __STDC_INT_AS_UINT_T flags);
/* Set the attribute NAME of the file descriptor FD to VALUE
 * (which is SIZE bytes long). Return 0 on success, -1 for errors
 * @param: flags: 0, or a one of `XATTR_*' */
INTDEF NONNULL((2, 3)) int NOTHROW_RPC(LIBCCALL libc_fsetxattr)(fd_t fd, char const *name, void const *buf, size_t bufsize, __STDC_INT_AS_UINT_T flags);
/* Get the attribute NAME of the file pointed to by PATH to VALUE
 * (which is SIZE bytes long). Return 0 on success, -1 for errors */
INTDEF NONNULL((1, 2, 3)) ssize_t NOTHROW_RPC(LIBCCALL libc_getxattr)(char const *path, char const *name, void *buf, size_t bufsize);
/* Get the attribute NAME of the file pointed to by PATH to VALUE (which is
 * SIZE bytes long), not following symlinks for the last pathname component.
 * Return 0 on success, -1 for errors */
INTDEF NONNULL((1, 2, 3)) ssize_t NOTHROW_RPC(LIBCCALL libc_lgetxattr)(char const *path, char const *name, void *buf, size_t bufsize);
/* Get the attribute NAME of the file descriptor FD to VALUE
 * (which is SIZE bytes long). Return 0 on success, -1 for errors */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBCCALL libc_fgetxattr)(fd_t fd, char const *name, void *buf, size_t bufsize);
/* List attributes of the file pointed to by PATH into the
 * user-supplied buffer LIST (which is SIZE bytes big).
 * Return 0 on success, -1 for errors */
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_RPC(LIBCCALL libc_listxattr)(char const *path, char *listbuf, size_t listbufsize);
/* List attributes of the file pointed to by PATH into the user-supplied
 * buffer LIST (which is SIZE bytes big), not following symlinks for the
 * last pathname component. Return 0 on success, -1 for errors */
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_RPC(LIBCCALL libc_llistxattr)(char const *path, char *listbuf, size_t listbufsize);
/* List attributes of the file descriptor FD into the user-supplied buffer
 * LIST (which is SIZE bytes big). Return 0 on success, -1 for errors */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_flistxattr)(fd_t fd, char *listbuf, size_t listbufsize);
/* Remove the attribute NAME from the file pointed to by PATH.
 * Return 0 on success, -1 for errors */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_removexattr)(char const *path, char const *name);
/* Remove the attribute NAME from the file pointed to by PATH, not
 * following symlinks for the last pathname component.
 * Return 0 on success, -1 for errors */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_lremovexattr)(char const *path, char const *name);
/* Remove the attribute NAME from the file descriptor FD.
 * Return 0 on success, -1 for errors */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_fremovexattr)(fd_t fd, char const *name);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_XATTR_H */
