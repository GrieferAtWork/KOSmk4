/* HASH CRC-32:0x9c976086 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_DIRENT_H
#define GUARD_LIBC_AUTO_DIRENT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <dirent.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> closedir(3)
 * Close a directory stream previously returned by `opendir(3)' and friends */
INTDEF ATTR_ACCESS_RW(1) int NOTHROW_NCX(LIBDCALL libd_closedir)(DIR *dirp);
/* >> fdclosedir(3)
 * Same as `closedir()', but instead of also closing the underlying file descriptor, return it */
INTDEF WUNUSED ATTR_ACCESS_RW(1) fd_t NOTHROW_NCX(LIBDCALL libd_fdclosedir)(DIR *dirp);
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
INTDEF ATTR_ACCESS_RW(1) struct dirent *NOTHROW_RPC(LIBDCALL libd_readdirk)(DIR *__restrict dirp);
/* >> rewinddir(3)
 * Rewind the given directory stream in such a way that the next call
 * to `readdir(3)' will once again  return the first directory  entry */
INTDEF ATTR_ACCESS_RW(1) void NOTHROW_NCX(LIBDCALL libd_rewinddir)(DIR *__restrict dirp);
/* >> fdopendir(3)
 * Create a new directory stream by inheriting the given `fd' as stream handle */
INTDEF WUNUSED DIR *NOTHROW_NCX(LIBDCALL libd_fdopendir)(fd_t fd);
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
INTDEF ATTR_ACCESS_RW(1) struct dirent64 *NOTHROW_RPC(LIBDCALL libd_readdirk64)(DIR *__restrict dirp);
/* >> readdir_r(3), readdir64_r(3)
 * Reentrant version of `readdir(3)'
 * NOTE: This ~reentrant~ version of readdir()  is strongly discouraged from being  used in KOS, as  the
 *       kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
 * >> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
 *    per-directory  buffer  of sufficient  size to  house any  directory entry  (s.a.: `READDIR_DEFAULT') */
INTDEF ATTR_ACCESS_RW(1) ATTR_ACCESS_WR(2) ATTR_ACCESS_WR(3) int NOTHROW_RPC(LIBDCALL libd_readdirk_r)(DIR *__restrict dirp, struct dirent *__restrict entry, struct dirent **__restrict result);
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
INTDEF ATTR_ACCESS_RW(1) ATTR_ACCESS_WR(2) ATTR_ACCESS_WR(3) int NOTHROW_RPC(LIBDCALL libd_readdirk64_r)(DIR *__restrict dirp, struct dirent64 *__restrict entry, struct dirent64 **__restrict result);
/* >> seekdir(3)
 * Get the directory stream position */
INTDEF ATTR_ACCESS_RW(1) void NOTHROW_NCX(LIBDCALL libd_seekdir)(DIR *__restrict dirp, longptr_t pos);
/* >> telldir(3)
 * Get the directory stream position */
INTDEF ATTR_ACCESS_RW(1) longptr_t NOTHROW_NCX(LIBDCALL libd_telldir)(DIR *__restrict dirp);
/* >> dirfd(3)
 * Return the underlying file descriptor of the given directory stream */
INTDEF ATTR_PURE ATTR_ACCESS_RO(1) fd_t NOTHROW_NCX(LIBDCALL libd_dirfd)(DIR __KOS_FIXED_CONST *__restrict dirp);
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
INTDEF ATTR_PURE ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_alphasortk)(struct dirent const **e1, struct dirent const **e2);
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
INTDEF ATTR_PURE ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_alphasortk64)(struct dirent64 const **e1, struct dirent64 const **e2);
/* >> getdirentries(2), getdirentries64(2)
 * Linux's underlying system call for reading the entries of a directory */
INTDEF ATTR_ACCESS_RW(4) ATTR_ACCESS_WRS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_getdirentries)(fd_t fd, char *__restrict buf, size_t nbytes, off_t *__restrict basep);
/* >> getdirentries(2), getdirentries64(2)
 * Linux's underlying system call for reading the entries of a directory */
INTDEF ATTR_ACCESS_RW(4) ATTR_ACCESS_WRS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_getdirentries64)(fd_t fd, char *__restrict buf, size_t nbytes, off64_t *__restrict basep);
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
INTDEF ATTR_PURE ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_versionsortk)(struct dirent const **e1, struct dirent const **e2);
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
INTDEF ATTR_PURE ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int NOTHROW_NCX(LIBDCALL libd_versionsortk64)(struct dirent64 const **e1, struct dirent64 const **e2);
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTDEF WUNUSED ssize_t NOTHROW_RPC(LIBDCALL libd_kreaddir)(fd_t fd, struct dirent *buf, size_t bufsize, unsigned int mode);
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTDEF WUNUSED ssize_t NOTHROW_RPC(LIBDCALL libd_kreaddirf)(fd_t fd, struct dirent *buf, size_t bufsize, unsigned int mode, oflag_t flags);
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTDEF WUNUSED ssize_t NOTHROW_RPC(LIBDCALL libd_kreaddir64)(fd_t fd, struct dirent64 *buf, size_t bufsize, unsigned int mode);
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTDEF WUNUSED ssize_t NOTHROW_RPC(LIBDCALL libd_kreaddirf64)(fd_t fd, struct dirent64 *buf, size_t bufsize, unsigned int mode, oflag_t flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_DIRENT_H */
