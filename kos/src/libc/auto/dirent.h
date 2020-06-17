/* HASH CRC-32:0x53b76b29 */
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
#ifndef GUARD_LIBC_AUTO_DIRENT_H
#define GUARD_LIBC_AUTO_DIRENT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <dirent.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Open and return a new directory stream for reading, referring to `name' */
INTDEF WUNUSED NONNULL((1)) DIR *NOTHROW_RPC(LIBDCALL libd_opendir)(char const *name);
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTDEF WUNUSED NONNULL((2)) DIR *NOTHROW_RPC(LIBDCALL libd_fopendirat)(fd_t dirfd, char const *name, oflag_t oflags);
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTDEF WUNUSED NONNULL((2)) DIR *NOTHROW_RPC(LIBDCALL libd_opendirat)(fd_t dirfd, char const *name);
/* Close a directory stream previously returned by `opendir(3)' and friends */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_closedir)(DIR *dirp);
/* Same as `closedir()', but instead of closing the underlying file descriptor, return it */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_NCX(LIBDCALL libd_fdclosedir)(DIR *dirp);
/* Read and return the next pending directory entry of the given directory stream `DIRP'
 * @EXCEPT: Returns NULL for end-of-directory; throws an error if something else went wrong */
INTDEF NONNULL((1)) struct dirent *NOTHROW_RPC(LIBDCALL libd_readdir)(DIR *__restrict dirp);
/* Rewind the given directory stream in such a way that the next call
 * to `readdir(3)' will once again return the first directory entry */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_rewinddir)(DIR *__restrict dirp);
/* Create a new directory stream by inheriting the given `FD' as stream handle */
INTDEF WUNUSED DIR *NOTHROW_NCX(LIBDCALL libd_fdopendir)(fd_t fd);
/* 64-bit equivalent of `readdir(3)'
 * @EXCEPT: Returns NULL for end-of-directory; throws an error if something else went wrong */
INTDEF NONNULL((1)) struct dirent64 *NOTHROW_RPC(LIBDCALL libd_readdir64)(DIR *__restrict dirp);
/* Reentrant version of `readdir(3)' (Using this is not recommended in KOS) */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBDCALL libd_readdir_r)(DIR *__restrict dirp, struct dirent *__restrict entry, struct dirent **__restrict result);
/* NOTE: This ~reentrant~ version of readdir() is strongly discouraged from being used in KOS, as the
 *       kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
 * >> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
 *    per-directory buffer of sufficient size to house any directory entry (s.a.: `READDIR_DEFAULT') */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBDCALL libd_readdir64_r)(DIR *__restrict dirp, struct dirent64 *__restrict entry, struct dirent64 **__restrict result);
/* Get the directory stream position */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_seekdir)(DIR *__restrict dirp, longptr_t pos);
/* Get the directory stream position */
INTDEF NONNULL((1)) long int NOTHROW_NCX(LIBDCALL libd_telldir)(DIR *__restrict dirp);
/* Return the underlying file descriptor of the given directory stream */
INTDEF ATTR_PURE NONNULL((1)) fd_t NOTHROW_NCX(LIBDCALL libd_dirfd)(DIR __KOS_FIXED_CONST *__restrict dirp);
/* Scan a directory `DIR' for all contained directory entries */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_scandir)(char const *__restrict dir, struct dirent ***__restrict namelist, __scandir_selector_t selector, __scandir_cmp_t cmp);
/* Sort the 2 given directory entries `E1' and `E2' the same way `strcmp(3)' would */
INTDEF ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_alphasort)(struct dirent const **e1, struct dirent const **e2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Sort the 2 given directory entries `E1' and `E2' the same way `strcmp(3)' would */
INTDEF ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_alphasort)(struct dirent const **e1, struct dirent const **e2);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* 64-bit variant of `alphasort()' */
INTDEF ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_alphasort64)(struct dirent64 const **e1, struct dirent64 const **e2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* 64-bit variant of `alphasort()' */
INTDEF ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_alphasort64)(struct dirent64 const **e1, struct dirent64 const **e2);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Scan a directory `DIRFD:DIR' for all contained directory entries */
INTDEF NONNULL((2, 3)) int NOTHROW_RPC(LIBDCALL libd_scandirat)(fd_t dirfd, char const *__restrict dir, struct dirent ***__restrict namelist, __scandir_selector_t selector, __scandir_cmp_t cmp);
/* 64-bit variant of `scandir()' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_scandir64)(char const *__restrict dir, struct dirent64 ***__restrict namelist, __scandir64_selector_t selector, __scandir64_cmp_t cmp);
/* 64-bit variant of `scandirat()' */
INTDEF NONNULL((2, 3)) int NOTHROW_RPC(LIBDCALL libd_scandirat64)(fd_t dirfd, char const *__restrict dir, struct dirent64 ***__restrict namelist, __scandir64_selector_t selector, __scandir64_cmp_t cmp);
/* Linux's underlying system call for reading the entries of a directory */
INTDEF NONNULL((2, 4)) ssize_t NOTHROW_RPC(LIBDCALL libd_getdirentries)(fd_t fd, char *__restrict buf, size_t nbytes, off_t *__restrict basep);
/* 64-bit variant of `getdirentries()' */
INTDEF NONNULL((2, 4)) ssize_t NOTHROW_RPC(LIBDCALL libd_getdirentries64)(fd_t fd, char *__restrict buf, size_t nbytes, off64_t *__restrict basep);
/* Sort the 2 given directory entries `E1' and `E2' the same way `strvercmp(3)' would. */
INTDEF ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_versionsort)(struct dirent const **e1, struct dirent const **e2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Sort the 2 given directory entries `E1' and `E2' the same way `strvercmp(3)' would. */
INTDEF ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_versionsort)(struct dirent const **e1, struct dirent const **e2);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* 64-bit variant of `versionsort()' */
INTDEF ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_versionsort64)(struct dirent64 const **e1, struct dirent64 const **e2);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* 64-bit variant of `versionsort()' */
INTDEF ATTR_PURE NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_versionsort64)(struct dirent64 const **e1, struct dirent64 const **e2);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTDEF WUNUSED ssize_t NOTHROW_RPC(LIBDCALL libd_kreaddir)(fd_t fd, struct dirent *buf, size_t bufsize, unsigned int mode);
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTDEF WUNUSED ssize_t NOTHROW_RPC(LIBDCALL libd_kreaddirf)(fd_t fd, struct dirent *buf, size_t bufsize, unsigned int mode, oflag_t flags);
/* 64-bit variant of `kreaddir()' */
INTDEF WUNUSED ssize_t NOTHROW_RPC(LIBDCALL libd_kreaddir64)(fd_t fd, struct dirent64 *buf, size_t bufsize, unsigned int mode);
/* 64-bit variant of `kreaddirf()' */
INTDEF WUNUSED ssize_t NOTHROW_RPC(LIBDCALL libd_kreaddirf64)(fd_t fd, struct dirent64 *buf, size_t bufsize, unsigned int mode, oflag_t flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_DIRENT_H */
