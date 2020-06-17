/* HASH CRC-32:0x8925b39a */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_DIRENT_C
#define GUARD_LIBC_AUTO_DOSABI_DIRENT_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/dirent.h"

DECL_BEGIN

/* Open and return a new directory stream for reading, referring to `name' */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1)) DIR *
NOTHROW_RPC(LIBDCALL libd_opendir)(char const *name) {
	return libc_opendir(name);
}
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((2)) DIR *
NOTHROW_RPC(LIBDCALL libd_fopendirat)(fd_t dirfd,
                                      char const *name,
                                      oflag_t oflags) {
	return libc_fopendirat(dirfd, name, oflags);
}
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((2)) DIR *
NOTHROW_RPC(LIBDCALL libd_opendirat)(fd_t dirfd,
                                     char const *name) {
	return libc_opendirat(dirfd, name);
}
/* Close a directory stream previously returned by `opendir(3)' and friends */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_closedir)(DIR *dirp) {
	return libc_closedir(dirp);
}
/* Same as `closedir()', but instead of closing the underlying file descriptor, return it */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1)) fd_t
NOTHROW_NCX(LIBDCALL libd_fdclosedir)(DIR *dirp) {
	return libc_fdclosedir(dirp);
}
/* Read and return the next pending directory entry of the given directory stream `DIRP'
 * @EXCEPT: Returns NULL for end-of-directory; throws an error if something else went wrong */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((1)) struct dirent *
NOTHROW_RPC(LIBDCALL libd_readdir)(DIR *__restrict dirp) {
	return libc_readdir(dirp);
}
/* Rewind the given directory stream in such a way that the next call
 * to `readdir(3)' will once again return the first directory entry */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_rewinddir)(DIR *__restrict dirp) {
	libc_rewinddir(dirp);
}
/* Create a new directory stream by inheriting the given `FD' as stream handle */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED DIR *
NOTHROW_NCX(LIBDCALL libd_fdopendir)(fd_t fd) {
	return libc_fdopendir(fd);
}
/* 64-bit equivalent of `readdir(3)'
 * @EXCEPT: Returns NULL for end-of-directory; throws an error if something else went wrong */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((1)) struct dirent64 *
NOTHROW_RPC(LIBDCALL libd_readdir64)(DIR *__restrict dirp) {
	return libc_readdir64(dirp);
}
/* Reentrant version of `readdir(3)' (Using this is not recommended in KOS) */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd_readdir_r)(DIR *__restrict dirp,
                                     struct dirent *__restrict entry,
                                     struct dirent **__restrict result) {
	return libc_readdir_r(dirp, entry, result);
}
/* NOTE: This ~reentrant~ version of readdir() is strongly discouraged from being used in KOS, as the
 *       kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
 * >> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
 *    per-directory buffer of sufficient size to house any directory entry (s.a.: `READDIR_DEFAULT') */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd_readdir64_r)(DIR *__restrict dirp,
                                       struct dirent64 *__restrict entry,
                                       struct dirent64 **__restrict result) {
	return libc_readdir64_r(dirp, entry, result);
}
/* Get the directory stream position */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_seekdir)(DIR *__restrict dirp,
                                   longptr_t pos) {
	libc_seekdir(dirp, pos);
}
/* Get the directory stream position */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((1)) long int
NOTHROW_NCX(LIBDCALL libd_telldir)(DIR *__restrict dirp) {
	return libc_telldir(dirp);
}
/* Return the underlying file descriptor of the given directory stream */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") ATTR_PURE NONNULL((1)) fd_t
NOTHROW_NCX(LIBDCALL libd_dirfd)(DIR __KOS_FIXED_CONST *__restrict dirp) {
	return libc_dirfd(dirp);
}
/* Scan a directory `DIR' for all contained directory entries */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_scandir)(char const *__restrict dir,
                                   struct dirent ***__restrict namelist,
                                   __scandir_selector_t selector,
                                   __scandir_cmp_t cmp) {
	return libc_scandir(dir, namelist, selector, cmp);
}
/* Sort the 2 given directory entries `E1' and `E2' the same way `strcmp(3)' would */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") ATTR_PURE NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_alphasort)(struct dirent const **e1,
                                     struct dirent const **e2) {
	return libc_alphasort(e1, e2);
}
/* 64-bit variant of `alphasort()' */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") ATTR_PURE NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_alphasort64)(struct dirent64 const **e1,
                                       struct dirent64 const **e2) {
	return libc_alphasort64(e1, e2);
}
/* Scan a directory `DIRFD:DIR' for all contained directory entries */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((2, 3)) int
NOTHROW_RPC(LIBDCALL libd_scandirat)(fd_t dirfd,
                                     char const *__restrict dir,
                                     struct dirent ***__restrict namelist,
                                     __scandir_selector_t selector,
                                     __scandir_cmp_t cmp) {
	return libc_scandirat(dirfd, dir, namelist, selector, cmp);
}
/* 64-bit variant of `scandir()' */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_scandir64)(char const *__restrict dir,
                                     struct dirent64 ***__restrict namelist,
                                     __scandir64_selector_t selector,
                                     __scandir64_cmp_t cmp) {
	return libc_scandir64(dir, namelist, selector, cmp);
}
/* 64-bit variant of `scandirat()' */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((2, 3)) int
NOTHROW_RPC(LIBDCALL libd_scandirat64)(fd_t dirfd,
                                       char const *__restrict dir,
                                       struct dirent64 ***__restrict namelist,
                                       __scandir64_selector_t selector,
                                       __scandir64_cmp_t cmp) {
	return libc_scandirat64(dirfd, dir, namelist, selector, cmp);
}
/* Linux's underlying system call for reading the entries of a directory */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((2, 4)) ssize_t
NOTHROW_RPC(LIBDCALL libd_getdirentries)(fd_t fd,
                                         char *__restrict buf,
                                         size_t nbytes,
                                         off_t *__restrict basep) {
	return libc_getdirentries(fd, buf, nbytes, basep);
}
/* 64-bit variant of `getdirentries()' */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((2, 4)) ssize_t
NOTHROW_RPC(LIBDCALL libd_getdirentries64)(fd_t fd,
                                           char *__restrict buf,
                                           size_t nbytes,
                                           off64_t *__restrict basep) {
	return libc_getdirentries64(fd, buf, nbytes, basep);
}
/* Sort the 2 given directory entries `E1' and `E2' the same way `strvercmp(3)' would. */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") ATTR_PURE NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_versionsort)(struct dirent const **e1,
                                       struct dirent const **e2) {
	return libc_versionsort(e1, e2);
}
/* 64-bit variant of `versionsort()' */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") ATTR_PURE NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_versionsort64)(struct dirent64 const **e1,
                                         struct dirent64 const **e2) {
	return libc_versionsort64(e1, e2);
}
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED ssize_t
NOTHROW_RPC(LIBDCALL libd_kreaddir)(fd_t fd,
                                    struct dirent *buf,
                                    size_t bufsize,
                                    unsigned int mode) {
	return libc_kreaddir(fd, buf, bufsize, mode);
}
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED ssize_t
NOTHROW_RPC(LIBDCALL libd_kreaddirf)(fd_t fd,
                                     struct dirent *buf,
                                     size_t bufsize,
                                     unsigned int mode,
                                     oflag_t flags) {
	return libc_kreaddirf(fd, buf, bufsize, mode, flags);
}
/* 64-bit variant of `kreaddir()' */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED ssize_t
NOTHROW_RPC(LIBDCALL libd_kreaddir64)(fd_t fd,
                                      struct dirent64 *buf,
                                      size_t bufsize,
                                      unsigned int mode) {
	return libc_kreaddir64(fd, buf, bufsize, mode);
}
/* 64-bit variant of `kreaddirf()' */
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED ssize_t
NOTHROW_RPC(LIBDCALL libd_kreaddirf64)(fd_t fd,
                                       struct dirent64 *buf,
                                       size_t bufsize,
                                       unsigned int mode,
                                       oflag_t flags) {
	return libc_kreaddirf64(fd, buf, bufsize, mode, flags);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$opendir, libd_opendir);
DEFINE_PUBLIC_ALIAS(DOS$fopendirat, libd_fopendirat);
DEFINE_PUBLIC_ALIAS(DOS$opendirat, libd_opendirat);
DEFINE_PUBLIC_ALIAS(DOS$closedir, libd_closedir);
DEFINE_PUBLIC_ALIAS(DOS$fdclosedir, libd_fdclosedir);
DEFINE_PUBLIC_ALIAS(DOS$readdir, libd_readdir);
DEFINE_PUBLIC_ALIAS(DOS$rewinddir, libd_rewinddir);
DEFINE_PUBLIC_ALIAS(DOS$fdopendir, libd_fdopendir);
DEFINE_PUBLIC_ALIAS(DOS$readdir64, libd_readdir64);
DEFINE_PUBLIC_ALIAS(DOS$readdir_r, libd_readdir_r);
DEFINE_PUBLIC_ALIAS(DOS$readdir64_r, libd_readdir64_r);
DEFINE_PUBLIC_ALIAS(DOS$seekdir, libd_seekdir);
DEFINE_PUBLIC_ALIAS(DOS$telldir, libd_telldir);
DEFINE_PUBLIC_ALIAS(DOS$dirfd, libd_dirfd);
DEFINE_PUBLIC_ALIAS(DOS$scandir, libd_scandir);
DEFINE_PUBLIC_ALIAS(DOS$alphasort, libd_alphasort);
DEFINE_PUBLIC_ALIAS(DOS$alphasort64, libd_alphasort64);
DEFINE_PUBLIC_ALIAS(DOS$scandirat, libd_scandirat);
DEFINE_PUBLIC_ALIAS(DOS$scandir64, libd_scandir64);
DEFINE_PUBLIC_ALIAS(DOS$scandirat64, libd_scandirat64);
DEFINE_PUBLIC_ALIAS(DOS$getdirentries, libd_getdirentries);
DEFINE_PUBLIC_ALIAS(DOS$getdirentries64, libd_getdirentries64);
DEFINE_PUBLIC_ALIAS(DOS$versionsort, libd_versionsort);
DEFINE_PUBLIC_ALIAS(DOS$versionsort64, libd_versionsort64);
DEFINE_PUBLIC_ALIAS(DOS$kreaddir, libd_kreaddir);
DEFINE_PUBLIC_ALIAS(DOS$kreaddirf, libd_kreaddirf);
DEFINE_PUBLIC_ALIAS(DOS$kreaddir64, libd_kreaddir64);
DEFINE_PUBLIC_ALIAS(DOS$kreaddirf64, libd_kreaddirf64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_DIRENT_C */
