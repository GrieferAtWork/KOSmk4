/* HASH CRC-32:0x293f1852 */
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
#ifndef GUARD_LIBC_USER_FCNTL_H
#define GUARD_LIBC_USER_FCNTL_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <fcntl.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ssize_t NOTHROW_NCX(LIBCCALL libc_readahead)(fd_t fd, off64_t offset, size_t count);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sync_file_range)(fd_t fd, off64_t offset, off64_t count, unsigned int flags);
INTDEF ssize_t NOTHROW_RPC(LIBCCALL libc_vmsplice)(fd_t fdout, struct iovec const *iov, size_t count, unsigned int flags);
INTDEF ssize_t NOTHROW_RPC(LIBCCALL libc_splice)(fd_t fdin, off64_t *offin, fd_t fdout, off64_t *offout, size_t length, unsigned int flags);
INTDEF ssize_t NOTHROW_RPC(LIBCCALL libc_tee)(fd_t fdin, fd_t fdout, size_t length, unsigned int flags);
INTDEF int NOTHROW_RPC(LIBCCALL libc_name_to_handle_at)(fd_t dirfd, char const *name, struct file_handle *handle, int *mnt_id, int flags);
INTDEF fd_t NOTHROW_RPC(LIBCCALL libc_open_by_handle_at)(fd_t mountdirfd, struct file_handle *handle, int flags);
INTDEF int NOTHROW_NCX(LIBCCALL libc_fallocate)(fd_t fd, int mode, off_t offset, off_t length);
INTDEF int NOTHROW_NCX(LIBCCALL libc_fallocate64)(fd_t fd, int mode, off64_t offset, off64_t length);
INTDEF __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc_fcntl)(fd_t fd, int cmd, ...);
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(VLIBCCALL libc_open)(char const *filename, oflag_t oflags, ...);
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(LIBCCALL libc_creat)(char const *filename, mode_t mode);
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(VLIBCCALL libc_open64)(char const *filename, oflag_t oflags, ...);
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(LIBCCALL libc_creat64)(char const *filename, mode_t mode);
INTDEF WUNUSED NONNULL((2)) fd_t NOTHROW_RPC(VLIBCCALL libc_openat)(fd_t dirfd, char const *filename, oflag_t oflags, ...);
INTDEF WUNUSED NONNULL((2)) fd_t NOTHROW_RPC(VLIBCCALL libc_openat64)(fd_t dirfd, char const *filename, oflag_t oflags, ...);
INTDEF int NOTHROW_NCX(LIBCCALL libc_posix_fadvise)(fd_t fd, off_t offset, off_t length, int advise);
INTDEF int NOTHROW_NCX(LIBCCALL libc_posix_fallocate)(fd_t fd, off_t offset, off_t length);
INTDEF int NOTHROW_NCX(LIBCCALL libc_posix_fadvise64)(fd_t fd, off64_t offset, off64_t length, int advise);
INTDEF int NOTHROW_NCX(LIBCCALL libc_posix_fallocate64)(fd_t fd, off64_t offset, off64_t length);
INTDEF int NOTHROW_RPC(LIBCCALL libc_lockf)(fd_t fd, int cmd, off_t length);
INTDEF int NOTHROW_RPC(LIBCCALL libc_lockf64)(fd_t fd, int cmd, off64_t length);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_FCNTL_H */
