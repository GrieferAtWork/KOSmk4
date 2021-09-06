/* HASH CRC-32:0x9e6490c */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_UIO_H
#define GUARD_LIBC_USER_SYS_UIO_H 1

#include "../api.h"
#include "../auto/sys.uio.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/uio.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> process_vm_readv(2)
 * Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
INTDEF WUNUSED ssize_t NOTHROW_RPC(LIBCCALL libc_process_vm_readv)(pid_t pid, struct iovec const *local_iov, ulongptr_t liovcnt, struct iovec const *remote_iov, ulongptr_t riovcnt, ulongptr_t flags);
/* >> process_vm_writev(2)
 * Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
INTDEF ssize_t NOTHROW_RPC(LIBCCALL libc_process_vm_writev)(pid_t pid, struct iovec const *local_iov, ulongptr_t liovcnt, struct iovec const *remote_iov, ulongptr_t riovcnt, ulongptr_t flags);
/* >> readv(2)
 * Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
INTDEF WUNUSED NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_readv)(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count);
/* >> writev(2)
 * Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_writev)(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count);
/* >> preadv(2)
 * Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
INTDEF WUNUSED NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_preadv)(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count, off_t offset);
/* >> pwritev(2)
 * Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pwritev)(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count, off_t offset);
/* >> preadv(2)
 * Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
INTDEF WUNUSED NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_preadv64)(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count, off64_t offset);
/* >> pwritev(2)
 * Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pwritev64)(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count, off64_t offset);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_UIO_H */
