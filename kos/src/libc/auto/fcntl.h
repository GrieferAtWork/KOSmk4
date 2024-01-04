/* HASH CRC-32:0x249b1c75 */
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
#ifndef GUARD_LIBC_AUTO_FCNTL_H
#define GUARD_LIBC_AUTO_FCNTL_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <fcntl.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_FDREAD(1) ssize_t NOTHROW_NCX(LIBDCALL libd_readahead)(fd_t fd, __PIO_OFFSET64 offset, size_t count);
INTDEF ATTR_FDWRITE(1) int NOTHROW_NCX(LIBDCALL libd_sync_file_range)(fd_t fd, __PIO_OFFSET64 offset, __PIO_OFFSET64 count, unsigned int flags);
INTDEF ATTR_FDWRITE(1) ssize_t NOTHROW_RPC(LIBDCALL libd_vmsplice)(fd_t fdout, struct iovec const *iov, size_t count, unsigned int flags);
INTDEF ATTR_FDREAD(1) ATTR_FDWRITE(3) ATTR_INOUT(2) ATTR_INOUT(4) ssize_t NOTHROW_RPC(LIBDCALL libd_splice)(fd_t fdin, __PIO_OFFSET64 *offin, fd_t fdout, __PIO_OFFSET64 *offout, size_t length, unsigned int flags);
INTDEF ATTR_FDREAD(1) ATTR_FDWRITE(2) ssize_t NOTHROW_RPC(LIBDCALL libd_tee)(fd_t fdin, fd_t fdout, size_t length, unsigned int flags);
INTDEF ATTR_OUT(3) int NOTHROW_RPC(LIBDCALL libd_name_to_handle_at)(fd_t dirfd, char const *name, struct file_handle *handle, int *mnt_id, int flags);
INTDEF ATTR_FDARG(1) ATTR_IN(2) fd_t NOTHROW_RPC(LIBDCALL libd_open_by_handle_at)(fd_t mountdirfd, struct file_handle *handle, int flags);
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBDCALL libd_fallocate)(fd_t fd, __STDC_INT_AS_UINT_T mode, __PIO_OFFSET offset, __PIO_OFFSET length);
INTDEF ATTR_FDWRITE(1) int NOTHROW_NCX(LIBDCALL libd_fallocate64)(fd_t fd, __STDC_INT_AS_UINT_T mode, __PIO_OFFSET64 offset, __PIO_OFFSET64 length);
INTDEF ATTR_FDARG(1) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd_fcntl)(fd_t fd, fcntl_t cmd, ...);
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBDCALL libd_posix_fadvise)(fd_t fd, __PIO_OFFSET offset, __PIO_OFFSET length, __STDC_INT_AS_UINT_T advise);
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBDCALL libd_posix_fallocate)(fd_t fd, __PIO_OFFSET offset, __PIO_OFFSET length);
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBDCALL libd_posix_fadvise64)(fd_t fd, __PIO_OFFSET64 offset, __PIO_OFFSET64 length, __STDC_INT_AS_UINT_T advise);
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBDCALL libd_posix_fallocate64)(fd_t fd, __PIO_OFFSET64 offset, __PIO_OFFSET64 length);
INTDEF ATTR_FDARG(1) int NOTHROW_RPC(LIBDCALL libd_lockf)(fd_t fd, __STDC_INT_AS_UINT_T cmd, __PIO_OFFSET length);
INTDEF ATTR_FDARG(1) int NOTHROW_RPC(LIBDCALL libd_lockf64)(fd_t fd, __STDC_INT_AS_UINT_T cmd, __PIO_OFFSET64 length);
/* >> directio(3)
 * Enable or disable optional direct-I/O for  `fd'. Optional direct I/O behaves  the
 * same as mandatory direct I/O (s.a. `O_DIRECT'), but those cases where the  buffer
 * or file position/length provided in a call to `read(2)' or `write(2)' don't match
 * the requirements imposed by the  backing hardware (s.a. `FILE_IOC_BLKSHIFT')  are
 * handled  not by throwing an `E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BAD*' exception,
 * but by falling back to doing non-direct I/O (as if `O_DIRECT') hasn't been set.
 *
 * Note that when optional direct-I/O is enabled, the O_DIRECT bit will also be set
 * for  the  given  `fd'  (in   addition  to  the  internal  `IO_OPTDIRECT'   bit).
 *
 * PORTABILITY WARNING: On OpenSolaris, this optional direct  I/O isn't used for file  ranges
 *                      of the given `fd' that have been mmap'd. This is NOT the case on KOS,
 *                      where direct I/O is always use if possible.
 *
 * @param: fd:   The file for which direct-I/O should be enabled/disabled
 * @param: mode: One of `DIRECTIO_*' from `<sys/fcntl.h>'
 * @return:  0: Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBDCALL libd_directio)(fd_t fd, int mode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> directio(3)
 * Enable or disable optional direct-I/O for  `fd'. Optional direct I/O behaves  the
 * same as mandatory direct I/O (s.a. `O_DIRECT'), but those cases where the  buffer
 * or file position/length provided in a call to `read(2)' or `write(2)' don't match
 * the requirements imposed by the  backing hardware (s.a. `FILE_IOC_BLKSHIFT')  are
 * handled  not by throwing an `E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BAD*' exception,
 * but by falling back to doing non-direct I/O (as if `O_DIRECT') hasn't been set.
 *
 * Note that when optional direct-I/O is enabled, the O_DIRECT bit will also be set
 * for  the  given  `fd'  (in   addition  to  the  internal  `IO_OPTDIRECT'   bit).
 *
 * PORTABILITY WARNING: On OpenSolaris, this optional direct  I/O isn't used for file  ranges
 *                      of the given `fd' that have been mmap'd. This is NOT the case on KOS,
 *                      where direct I/O is always use if possible.
 *
 * @param: fd:   The file for which direct-I/O should be enabled/disabled
 * @param: mode: One of `DIRECTIO_*' from `<sys/fcntl.h>'
 * @return:  0: Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBCCALL libc_directio)(fd_t fd, int mode);
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_NCX(VLIBDCALL libd___open_nocancel)(char const *filename, oflag_t oflags, ...);
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_NCX(VLIBCCALL libc___open_nocancel)(char const *filename, oflag_t oflags, ...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_FCNTL_H */
