/* HASH CRC-32:0x3ba0e7f9 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_FCNTL_C
#define GUARD_LIBC_AUTO_DOSABI_FCNTL_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/fcntl.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.io.utility") ssize_t
NOTHROW_NCX(LIBDCALL libd_readahead)(fd_t fd,
                                     off64_t offset,
                                     size_t count) {
	return libc_readahead(fd, offset, count);
}
INTERN ATTR_SECTION(".text.crt.dos.io.utility") int
NOTHROW_NCX(LIBDCALL libd_sync_file_range)(fd_t fd,
                                           off64_t offset,
                                           off64_t count,
                                           unsigned int flags) {
	return libc_sync_file_range(fd, offset, count, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.io.utility") ssize_t
NOTHROW_RPC(LIBDCALL libd_vmsplice)(fd_t fdout,
                                    struct iovec const *iov,
                                    size_t count,
                                    unsigned int flags) {
	return libc_vmsplice(fdout, iov, count, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.io.utility") ssize_t
NOTHROW_RPC(LIBDCALL libd_splice)(fd_t fdin,
                                  off64_t *offin,
                                  fd_t fdout,
                                  off64_t *offout,
                                  size_t length,
                                  unsigned int flags) {
	return libc_splice(fdin, offin, fdout, offout, length, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.io.utility") ssize_t
NOTHROW_RPC(LIBDCALL libd_tee)(fd_t fdin,
                               fd_t fdout,
                               size_t length,
                               unsigned int flags) {
	return libc_tee(fdin, fdout, length, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.io.utility") int
NOTHROW_RPC(LIBDCALL libd_name_to_handle_at)(fd_t dirfd,
                                             char const *name,
                                             struct file_handle *handle,
                                             int *mnt_id,
                                             int flags) {
	return libc_name_to_handle_at(dirfd, name, handle, mnt_id, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.io.utility") fd_t
NOTHROW_RPC(LIBDCALL libd_open_by_handle_at)(fd_t mountdirfd,
                                             struct file_handle *handle,
                                             int flags) {
	return libc_open_by_handle_at(mountdirfd, handle, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.io.utility") int
NOTHROW_NCX(LIBDCALL libd_fallocate)(fd_t fd,
                                     int mode,
                                     off_t offset,
                                     off_t length) {
	return libc_fallocate(fd, mode, offset, length);
}
INTERN ATTR_SECTION(".text.crt.dos.io.utility") int
NOTHROW_NCX(LIBDCALL libd_fallocate64)(fd_t fd,
                                       int mode,
                                       off64_t offset,
                                       off64_t length) {
	return libc_fallocate64(fd, mode, offset, length);
}
INTERN ATTR_SECTION(".text.crt.dos.io.utility") __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd_fcntl)(fd_t fd,
                                  int cmd,
                                  ...) {
	va_list args;
	void *v0;
	va_start(args, cmd);
	v0 = va_arg(args, void *);
	va_end(args);
	return libc_fcntl(fd, cmd, v0);
}
INTERN ATTR_SECTION(".text.crt.dos.io.utility") int
NOTHROW_NCX(LIBDCALL libd_posix_fadvise)(fd_t fd,
                                         off_t offset,
                                         off_t length,
                                         int advise) {
	return libc_posix_fadvise(fd, offset, length, advise);
}
INTERN ATTR_SECTION(".text.crt.dos.io.utility") int
NOTHROW_NCX(LIBDCALL libd_posix_fallocate)(fd_t fd,
                                           off_t offset,
                                           off_t length) {
	return libc_posix_fallocate(fd, offset, length);
}
INTERN ATTR_SECTION(".text.crt.dos.io.large.utility") int
NOTHROW_NCX(LIBDCALL libd_posix_fadvise64)(fd_t fd,
                                           off64_t offset,
                                           off64_t length,
                                           int advise) {
	return libc_posix_fadvise64(fd, offset, length, advise);
}
INTERN ATTR_SECTION(".text.crt.dos.io.large.utility") int
NOTHROW_NCX(LIBDCALL libd_posix_fallocate64)(fd_t fd,
                                             off64_t offset,
                                             off64_t length) {
	return libc_posix_fallocate64(fd, offset, length);
}
INTERN ATTR_SECTION(".text.crt.dos.io.lock") int
NOTHROW_RPC(LIBDCALL libd_lockf)(fd_t fd,
                                 int cmd,
                                 off_t length) {
	return libc_lockf(fd, cmd, length);
}
INTERN ATTR_SECTION(".text.crt.dos.io.large.lock") int
NOTHROW_RPC(LIBDCALL libd_lockf64)(fd_t fd,
                                   int cmd,
                                   off64_t length) {
	return libc_lockf64(fd, cmd, length);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$readahead, libd_readahead);
DEFINE_PUBLIC_ALIAS(DOS$sync_file_range, libd_sync_file_range);
DEFINE_PUBLIC_ALIAS(DOS$vmsplice, libd_vmsplice);
DEFINE_PUBLIC_ALIAS(DOS$splice, libd_splice);
DEFINE_PUBLIC_ALIAS(DOS$tee, libd_tee);
DEFINE_PUBLIC_ALIAS(DOS$name_to_handle_at, libd_name_to_handle_at);
DEFINE_PUBLIC_ALIAS(DOS$open_by_handle_at, libd_open_by_handle_at);
DEFINE_PUBLIC_ALIAS(DOS$fallocate, libd_fallocate);
DEFINE_PUBLIC_ALIAS(DOS$fallocate64, libd_fallocate64);
DEFINE_PUBLIC_ALIAS(DOS$__fcntl, libd_fcntl);
DEFINE_PUBLIC_ALIAS(DOS$fcntl, libd_fcntl);
DEFINE_PUBLIC_ALIAS(DOS$posix_fadvise, libd_posix_fadvise);
DEFINE_PUBLIC_ALIAS(DOS$posix_fallocate, libd_posix_fallocate);
DEFINE_PUBLIC_ALIAS(DOS$posix_fadvise64, libd_posix_fadvise64);
DEFINE_PUBLIC_ALIAS(DOS$posix_fallocate64, libd_posix_fallocate64);
DEFINE_PUBLIC_ALIAS(DOS$_locking, libd_lockf);
DEFINE_PUBLIC_ALIAS(DOS$lockf, libd_lockf);
DEFINE_PUBLIC_ALIAS(DOS$lockf64, libd_lockf64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_FCNTL_C */
