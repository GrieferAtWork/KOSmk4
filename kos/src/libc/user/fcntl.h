/* HASH CRC-32:0xab838c6e */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_FCNTL_H
#define GUARD_LIBC_USER_FCNTL_H 1

#include "../api.h"
#include "../auto/fcntl.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <fcntl.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_FDREAD(1) ssize_t NOTHROW_NCX(LIBCCALL libc_readahead)(fd_t fd, __PIO_OFFSET64 offset, size_t count);
INTDEF ATTR_FDWRITE(1) int NOTHROW_NCX(LIBCCALL libc_sync_file_range)(fd_t fd, __PIO_OFFSET64 offset, __PIO_OFFSET64 count, unsigned int flags);
INTDEF ATTR_FDWRITE(1) ssize_t NOTHROW_RPC(LIBCCALL libc_vmsplice)(fd_t fdout, struct iovec const *iov, size_t count, unsigned int flags);
INTDEF ATTR_FDREAD(1) ATTR_FDWRITE(3) ATTR_INOUT(2) ATTR_INOUT(4) ssize_t NOTHROW_RPC(LIBCCALL libc_splice)(fd_t fdin, __PIO_OFFSET64 *offin, fd_t fdout, __PIO_OFFSET64 *offout, size_t length, unsigned int flags);
INTDEF ATTR_FDREAD(1) ATTR_FDWRITE(2) ssize_t NOTHROW_RPC(LIBCCALL libc_tee)(fd_t fdin, fd_t fdout, size_t length, unsigned int flags);
INTDEF ATTR_OUT(3) int NOTHROW_RPC(LIBCCALL libc_name_to_handle_at)(fd_t dirfd, char const *name, struct file_handle *handle, int *mnt_id, int flags);
INTDEF ATTR_FDARG(1) ATTR_IN(2) fd_t NOTHROW_RPC(LIBCCALL libc_open_by_handle_at)(fd_t mountdirfd, struct file_handle *handle, int flags);
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBCCALL libc_fallocate)(fd_t fd, __STDC_INT_AS_UINT_T mode, __PIO_OFFSET offset, __PIO_OFFSET length);
INTDEF ATTR_FDWRITE(1) int NOTHROW_NCX(LIBCCALL libc_fallocate64)(fd_t fd, __STDC_INT_AS_UINT_T mode, __PIO_OFFSET64 offset, __PIO_OFFSET64 length);
INTDEF ATTR_FDARG(1) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc_fcntl)(fd_t fd, fcntl_t cmd, ...);
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(VLIBDCALL libd_open)(char const *filename, oflag_t oflags, ...);
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(VLIBCCALL libc_open)(char const *filename, oflag_t oflags, ...);
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(LIBDCALL libd_creat)(char const *filename, mode_t mode);
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(LIBCCALL libc_creat)(char const *filename, mode_t mode);
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(VLIBDCALL libd_open64)(char const *filename, oflag_t oflags, ...);
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(VLIBCCALL libc_open64)(char const *filename, oflag_t oflags, ...);
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(LIBDCALL libd_creat64)(char const *filename, mode_t mode);
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(LIBCCALL libc_creat64)(char const *filename, mode_t mode);
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
INTDEF WUNUSED ATTR_IN(2) fd_t NOTHROW_RPC(VLIBDCALL libd_openat)(fd_t dirfd, char const *filename, oflag_t oflags, ...);
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
INTDEF WUNUSED ATTR_IN(2) fd_t NOTHROW_RPC(VLIBCCALL libc_openat)(fd_t dirfd, char const *filename, oflag_t oflags, ...);
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
INTDEF WUNUSED ATTR_IN(2) fd_t NOTHROW_RPC(VLIBDCALL libd_openat64)(fd_t dirfd, char const *filename, oflag_t oflags, ...);
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
INTDEF WUNUSED ATTR_IN(2) fd_t NOTHROW_RPC(VLIBCCALL libc_openat64)(fd_t dirfd, char const *filename, oflag_t oflags, ...);
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBCCALL libc_posix_fadvise)(fd_t fd, __PIO_OFFSET offset, __PIO_OFFSET length, __STDC_INT_AS_UINT_T advise);
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBCCALL libc_posix_fallocate)(fd_t fd, __PIO_OFFSET offset, __PIO_OFFSET length);
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBCCALL libc_posix_fadvise64)(fd_t fd, __PIO_OFFSET64 offset, __PIO_OFFSET64 length, __STDC_INT_AS_UINT_T advise);
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBCCALL libc_posix_fallocate64)(fd_t fd, __PIO_OFFSET64 offset, __PIO_OFFSET64 length);
INTDEF ATTR_FDARG(1) int NOTHROW_RPC(LIBCCALL libc_lockf)(fd_t fd, __STDC_INT_AS_UINT_T cmd, __PIO_OFFSET length);
INTDEF ATTR_FDARG(1) int NOTHROW_RPC(LIBCCALL libc_lockf64)(fd_t fd, __STDC_INT_AS_UINT_T cmd, __PIO_OFFSET64 length);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_FCNTL_H */
