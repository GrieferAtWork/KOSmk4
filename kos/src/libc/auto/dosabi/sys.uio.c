/* HASH CRC-32:0xad0700c */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_UIO_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_UIO_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.uio.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.unsorted") WUNUSED ssize_t
NOTHROW_RPC(LIBDCALL libd_process_vm_readv)(pid_t pid,
                                            struct iovec const *local_iov,
                                            ulongptr_t liovcnt,
                                            struct iovec const *remote_iov,
                                            ulongptr_t riovcnt,
                                            ulongptr_t flags) {
	return libc_process_vm_readv(pid, local_iov, liovcnt, remote_iov, riovcnt, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.unsorted") ssize_t
NOTHROW_RPC(LIBDCALL libd_process_vm_writev)(pid_t pid,
                                             struct iovec const *local_iov,
                                             ulongptr_t liovcnt,
                                             struct iovec const *remote_iov,
                                             ulongptr_t riovcnt,
                                             ulongptr_t flags) {
	return libc_process_vm_writev(pid, local_iov, liovcnt, remote_iov, riovcnt, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.unsorted") WUNUSED NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_readv)(fd_t fd,
                                 struct iovec const *iov,
                                 __STDC_INT_AS_SIZE_T count) {
	return libc_readv(fd, iov, count);
}
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_writev)(fd_t fd,
                                  struct iovec const *iov,
                                  __STDC_INT_AS_SIZE_T count) {
	return libc_writev(fd, iov, count);
}
INTERN ATTR_SECTION(".text.crt.dos.unsorted") WUNUSED NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_preadv)(fd_t fd,
                                  struct iovec const *iov,
                                  __STDC_INT_AS_SIZE_T count,
                                  off_t offset) {
	return libc_preadv(fd, iov, count, offset);
}
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_pwritev)(fd_t fd,
                                   struct iovec const *iov,
                                   __STDC_INT_AS_SIZE_T count,
                                   off_t offset) {
	return libc_pwritev(fd, iov, count, offset);
}
INTERN ATTR_SECTION(".text.crt.dos.unsorted") WUNUSED NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_preadv64)(fd_t fd,
                                    struct iovec const *iov,
                                    __STDC_INT_AS_SIZE_T count,
                                    off64_t offset) {
	return libc_preadv64(fd, iov, count, offset);
}
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_pwritev64)(fd_t fd,
                                     struct iovec const *iov,
                                     __STDC_INT_AS_SIZE_T count,
                                     off64_t offset) {
	return libc_pwritev64(fd, iov, count, offset);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$process_vm_readv, libd_process_vm_readv);
DEFINE_PUBLIC_ALIAS(DOS$process_vm_writev, libd_process_vm_writev);
DEFINE_PUBLIC_ALIAS(DOS$readv, libd_readv);
DEFINE_PUBLIC_ALIAS(DOS$writev, libd_writev);
DEFINE_PUBLIC_ALIAS(DOS$preadv, libd_preadv);
DEFINE_PUBLIC_ALIAS(DOS$pwritev, libd_pwritev);
DEFINE_PUBLIC_ALIAS(DOS$preadv64, libd_preadv64);
DEFINE_PUBLIC_ALIAS(DOS$pwritev64, libd_pwritev64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_UIO_C */
