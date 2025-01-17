/* HASH CRC-32:0x817c6c25 */
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
#ifndef GUARD_LIBC_USER_DIRENT_H
#define GUARD_LIBC_USER_DIRENT_H 1

#include "../api.h"
#include "../auto/dirent.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <dirent.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> opendir(3)
 * Open and return a new directory stream for reading, referring to `name' */
INTDEF WUNUSED ATTR_IN(1) DIR *NOTHROW_RPC(LIBDCALL libd_opendir)(char const *name);
/* >> opendir(3)
 * Open and return a new directory stream for reading, referring to `name' */
INTDEF WUNUSED ATTR_IN(1) DIR *NOTHROW_RPC(LIBCCALL libc_opendir)(char const *name);
/* >> fopendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTDEF WUNUSED ATTR_IN(2) DIR *NOTHROW_RPC(LIBDCALL libd_fopendirat)(fd_t dirfd, char const *name, oflag_t oflags);
/* >> fopendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTDEF WUNUSED ATTR_IN(2) DIR *NOTHROW_RPC(LIBCCALL libc_fopendirat)(fd_t dirfd, char const *name, oflag_t oflags);
/* >> opendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTDEF WUNUSED ATTR_IN(2) DIR *NOTHROW_RPC(LIBDCALL libd_opendirat)(fd_t dirfd, char const *name);
/* >> opendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTDEF WUNUSED ATTR_IN(2) DIR *NOTHROW_RPC(LIBCCALL libc_opendirat)(fd_t dirfd, char const *name);
/* >> closedir(3)
 * Close a directory stream previously returned by `opendir(3)' and friends */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_closedir)(DIR *dirp);
/* >> fdclosedir(3)
 * Same as `closedir()', but instead of also closing the underlying file descriptor, return it */
INTDEF WUNUSED ATTR_INOUT(1) fd_t NOTHROW_NCX(LIBCCALL libc_fdclosedir)(DIR *dirp);
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
INTDEF ATTR_INOUT(1) struct dirent *NOTHROW_RPC(LIBCCALL libc_readdirk)(DIR *__restrict dirp);
/* >> rewinddir(3)
 * Rewind the given directory stream in such a way that the next call
 * to `readdir(3)' will once again  return the first directory  entry */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBCCALL libc_rewinddir)(DIR *__restrict dirp);
/* >> fdopendir(3)
 * Create a new directory stream by inheriting the given `fd' as stream handle */
INTDEF WUNUSED ATTR_FDREAD(1) DIR *NOTHROW_NCX(LIBCCALL libc_fdopendir)(fd_t fd);
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
INTDEF ATTR_INOUT(1) struct dirent64 *NOTHROW_RPC(LIBCCALL libc_readdirk64)(DIR *__restrict dirp);
/* >> readdir_r(3), readdir64_r(3)
 * Reentrant version of `readdir(3)'
 * NOTE: This ~reentrant~ version of readdir()  is strongly discouraged from being  used in KOS, as  the
 *       kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
 * >> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
 *    per-directory  buffer  of sufficient  size to  house any  directory entry  (s.a.: `READDIR_DEFAULT') */
INTDEF ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(3) int NOTHROW_RPC(LIBCCALL libc_readdirk_r)(DIR *__restrict dirp, struct dirent *__restrict entry, struct dirent **__restrict result);
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
INTDEF ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(3) int NOTHROW_RPC(LIBCCALL libc_readdirk64_r)(DIR *__restrict dirp, struct dirent64 *__restrict entry, struct dirent64 **__restrict result);
/* >> seekdir(3)
 * Get the directory stream position */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBCCALL libc_seekdir)(DIR *__restrict dirp, longptr_t pos);
/* >> telldir(3)
 * Get the directory stream position */
INTDEF ATTR_INOUT(1) longptr_t NOTHROW_NCX(LIBCCALL libc_telldir)(DIR *__restrict dirp);
/* >> dirfd(3)
 * Return the underlying file descriptor of the given directory stream */
INTDEF ATTR_PURE ATTR_IN(1) fd_t NOTHROW_NCX(LIBCCALL libc_dirfd)(DIR __KOS_FIXED_CONST *__restrict dirp);
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
INTDEF ATTR_IN(1) ATTR_OUT(2) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_scandirk)(char const *__restrict dir, struct dirent ***__restrict namelist, int (LIBKCALL *selector)(struct dirent const *entry), int (LIBKCALL *cmp)(struct dirent const **a, struct dirent const **b));
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
INTDEF ATTR_PURE ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_alphasortk)(struct dirent const **e1, struct dirent const **e2);
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
INTDEF ATTR_PURE ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_alphasortk64)(struct dirent64 const **e1, struct dirent64 const **e2);
/* >> scandirat(3), scandirat64(3)
 * Scan a directory `dirfd:dir' for all contained directory entries */
INTDEF ATTR_IN(2) ATTR_OUT(3) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_scandiratk)(fd_t dirfd, char const *__restrict dir, struct dirent ***__restrict namelist, int (LIBKCALL *selector)(struct dirent const *entry), int (LIBKCALL *cmp)(struct dirent const **a, struct dirent const **b));
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
INTDEF ATTR_IN(1) ATTR_OUT(2) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_scandirk64)(char const *__restrict dir, struct dirent64 ***__restrict namelist, int (LIBKCALL *selector)(struct dirent64 const *entry), int (LIBKCALL *cmp)(struct dirent64 const **a, struct dirent64 const **b));
/* >> scandirat(3), scandirat64(3)
 * Scan a directory `dirfd:dir' for all contained directory entries */
INTDEF ATTR_IN(2) ATTR_OUT(3) __STDC_INT_AS_SSIZE_T NOTHROW_RPC(LIBCCALL libc_scandiratk64)(fd_t dirfd, char const *__restrict dir, struct dirent64 ***__restrict namelist, int (LIBKCALL *selector)(struct dirent64 const *entry), int (LIBKCALL *cmp)(struct dirent64 const **a, struct dirent64 const **b));
/* >> getdirentries(2), getdirentries64(2)
 * Linux's underlying system call for reading the entries of a directory */
INTDEF ATTR_FDREAD(1) ATTR_INOUT(4) ATTR_OUTS(2, 3) ssize_t NOTHROW_RPC(LIBCCALL libc_getdirentries)(fd_t fd, char *__restrict buf, size_t nbytes, off_t *__restrict basep);
/* >> getdirentries(2), getdirentries64(2)
 * Linux's underlying system call for reading the entries of a directory */
INTDEF ATTR_FDREAD(1) ATTR_INOUT(4) ATTR_OUTS(2, 3) ssize_t NOTHROW_RPC(LIBCCALL libc_getdirentries64)(fd_t fd, char *__restrict buf, size_t nbytes, off64_t *__restrict basep);
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
INTDEF ATTR_PURE ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_versionsortk)(struct dirent const **e1, struct dirent const **e2);
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
INTDEF ATTR_PURE ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_versionsortk64)(struct dirent64 const **e1, struct dirent64 const **e2);
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTDEF WUNUSED ATTR_FDREAD(1) ssize_t NOTHROW_RPC(LIBCCALL libc_kreaddir)(fd_t fd, struct dirent *buf, size_t bufsize, unsigned int mode);
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTDEF WUNUSED ATTR_FDREAD(1) ssize_t NOTHROW_RPC(LIBCCALL libc_kreaddirf)(fd_t fd, struct dirent *buf, size_t bufsize, unsigned int mode, oflag_t flags);
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTDEF WUNUSED ATTR_FDREAD(1) ssize_t NOTHROW_RPC(LIBCCALL libc_kreaddir64)(fd_t fd, struct dirent64 *buf, size_t bufsize, unsigned int mode);
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTDEF WUNUSED ATTR_FDREAD(1) ssize_t NOTHROW_RPC(LIBCCALL libc_kreaddirf64)(fd_t fd, struct dirent64 *buf, size_t bufsize, unsigned int mode, oflag_t flags);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_DIRENT_H */
