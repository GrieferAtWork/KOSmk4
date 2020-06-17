/* HASH CRC-32:0x4153ccb5 */
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
#ifndef GUARD_LIBC_AUTO_SYS_UIO_H
#define GUARD_LIBC_AUTO_SYS_UIO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/uio.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ssize_t NOTHROW_RPC(LIBDCALL libd_process_vm_readv)(pid_t pid, struct iovec const *local_iov, ulongptr_t liovcnt, struct iovec const *remote_iov, ulongptr_t riovcnt, ulongptr_t flags);
INTDEF ssize_t NOTHROW_RPC(LIBDCALL libd_process_vm_writev)(pid_t pid, struct iovec const *local_iov, ulongptr_t liovcnt, struct iovec const *remote_iov, ulongptr_t riovcnt, ulongptr_t flags);
INTDEF WUNUSED NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_readv)(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count);
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_writev)(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count);
INTDEF WUNUSED NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_preadv)(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count, off_t offset);
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_pwritev)(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count, off_t offset);
INTDEF WUNUSED NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_preadv64)(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count, off64_t offset);
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_pwritev64)(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count, off64_t offset);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_UIO_H */
