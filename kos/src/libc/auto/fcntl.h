/* HASH CRC-32:0xdbb64a37 */
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
#ifndef GUARD_LIBC_AUTO_FCNTL_H
#define GUARD_LIBC_AUTO_FCNTL_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <fcntl.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ssize_t NOTHROW_NCX(LIBDCALL libd_readahead)(fd_t fd, off64_t offset, size_t count);
INTDEF int NOTHROW_NCX(LIBDCALL libd_sync_file_range)(fd_t fd, off64_t offset, off64_t count, unsigned int flags);
INTDEF ssize_t NOTHROW_RPC(LIBDCALL libd_vmsplice)(fd_t fdout, struct iovec const *iov, size_t count, unsigned int flags);
INTDEF ssize_t NOTHROW_RPC(LIBDCALL libd_splice)(fd_t fdin, off64_t *offin, fd_t fdout, off64_t *offout, size_t length, unsigned int flags);
INTDEF ssize_t NOTHROW_RPC(LIBDCALL libd_tee)(fd_t fdin, fd_t fdout, size_t length, unsigned int flags);
INTDEF int NOTHROW_RPC(LIBDCALL libd_name_to_handle_at)(fd_t dirfd, char const *name, struct file_handle *handle, int *mnt_id, int flags);
INTDEF fd_t NOTHROW_RPC(LIBDCALL libd_open_by_handle_at)(fd_t mountdirfd, struct file_handle *handle, int flags);
INTDEF int NOTHROW_NCX(LIBDCALL libd_fallocate)(fd_t fd, int mode, off_t offset, off_t length);
INTDEF int NOTHROW_NCX(LIBDCALL libd_fallocate64)(fd_t fd, int mode, off64_t offset, off64_t length);
INTDEF __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd_fcntl)(fd_t fd, int cmd, ...);
INTDEF int NOTHROW_NCX(LIBDCALL libd_posix_fadvise)(fd_t fd, off_t offset, off_t length, int advise);
INTDEF int NOTHROW_NCX(LIBDCALL libd_posix_fallocate)(fd_t fd, off_t offset, off_t length);
INTDEF int NOTHROW_NCX(LIBDCALL libd_posix_fadvise64)(fd_t fd, off64_t offset, off64_t length, int advise);
INTDEF int NOTHROW_NCX(LIBDCALL libd_posix_fallocate64)(fd_t fd, off64_t offset, off64_t length);
INTDEF int NOTHROW_RPC(LIBDCALL libd_lockf)(fd_t fd, int cmd, off_t length);
INTDEF int NOTHROW_RPC(LIBDCALL libd_lockf64)(fd_t fd, int cmd, off64_t length);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_FCNTL_H */
