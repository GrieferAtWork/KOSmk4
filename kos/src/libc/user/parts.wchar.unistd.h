/* HASH CRC-32:0xc2711926 */
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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_H
#define GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/unistd.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTDEF WUNUSED char16_t *NOTHROW_RPC(LIBDCALL libd_wttyname)(fd_t fd);
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTDEF WUNUSED char32_t *NOTHROW_RPC(LIBKCALL libc_wttyname)(fd_t fd);
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_wttyname_r)(fd_t fd, char16_t *buf, size_t buflen);
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBKCALL libc_wttyname_r)(fd_t fd, char32_t *buf, size_t buflen);
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_wchown)(char16_t const *file, uid_t owner, gid_t group);
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBKCALL libc_wchown)(char32_t const *file, uid_t owner, gid_t group);
/* >> pathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTDEF NONNULL((1)) longptr_t NOTHROW_RPC(LIBDCALL libd_wpathconf)(char16_t const *path, __STDC_INT_AS_UINT_T name);
/* >> pathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTDEF NONNULL((1)) longptr_t NOTHROW_RPC(LIBKCALL libc_wpathconf)(char32_t const *path, __STDC_INT_AS_UINT_T name);
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_wlink)(char16_t const *from, char16_t const *to);
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBKCALL libc_wlink)(char32_t const *from, char32_t const *to);
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_waccess)(char16_t const *file, __STDC_INT_AS_UINT_T type);
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBKCALL libc_waccess)(char32_t const *file, __STDC_INT_AS_UINT_T type);
/* >> chdir(2)
 * Change the current working directory to `path' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_wchdir)(char16_t const *path);
/* >> chdir(2)
 * Change the current working directory to `path' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBKCALL libc_wchdir)(char32_t const *path);
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTDEF char16_t *NOTHROW_RPC(LIBDCALL libd_wgetcwd)(char16_t *buf, size_t bufsize);
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTDEF char32_t *NOTHROW_RPC(LIBKCALL libc_wgetcwd)(char32_t *buf, size_t bufsize);
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_wunlink)(char16_t const *file);
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBKCALL libc_wunlink)(char32_t const *file);
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_wrmdir)(char16_t const *path);
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBKCALL libc_wrmdir)(char32_t const *path);
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_weuidaccess)(char16_t const *file, __STDC_INT_AS_UINT_T type);
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBKCALL libc_weuidaccess)(char32_t const *file, __STDC_INT_AS_UINT_T type);
INTDEF ATTR_MALLOC WUNUSED char16_t *NOTHROW_RPC(LIBDCALL libd_wget_current_dir_name)(void);
INTDEF ATTR_MALLOC WUNUSED char32_t *NOTHROW_RPC(LIBKCALL libc_wget_current_dir_name)(void);
/* >> faccessat(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `dfd:file', testing for `type' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_wfaccessat)(fd_t dfd, char16_t const *file, __STDC_INT_AS_UINT_T type, atflag_t flags);
/* >> faccessat(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `dfd:file', testing for `type' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBKCALL libc_wfaccessat)(fd_t dfd, char32_t const *file, __STDC_INT_AS_UINT_T type, atflag_t flags);
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_wfchownat)(fd_t dfd, char16_t const *file, uid_t owner, gid_t group, atflag_t flags);
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBKCALL libc_wfchownat)(fd_t dfd, char32_t const *file, uid_t owner, gid_t group, atflag_t flags);
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBDCALL libd_wlinkat)(fd_t fromfd, char16_t const *from, fd_t tofd, char16_t const *to, atflag_t flags);
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBKCALL libc_wlinkat)(fd_t fromfd, char32_t const *from, fd_t tofd, char32_t const *to, atflag_t flags);
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBDCALL libd_wsymlinkat)(char16_t const *link_text, fd_t tofd, char16_t const *target_path);
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBKCALL libc_wsymlinkat)(char32_t const *link_text, fd_t tofd, char32_t const *target_path);
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBDCALL libd_wreadlinkat)(fd_t dfd, char16_t const *path, char16_t *buf, size_t buflen);
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBKCALL libc_wreadlinkat)(fd_t dfd, char32_t const *path, char32_t *buf, size_t buflen);
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBDCALL libd_wfreadlinkat)(fd_t dfd, char16_t const *path, char16_t *buf, size_t buflen, atflag_t flags);
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBKCALL libc_wfreadlinkat)(fd_t dfd, char32_t const *path, char32_t *buf, size_t buflen, atflag_t flags);
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_wunlinkat)(fd_t dfd, char16_t const *name, atflag_t flags);
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBKCALL libc_wunlinkat)(fd_t dfd, char32_t const *name, atflag_t flags);
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_wlchown)(char16_t const *file, uid_t owner, gid_t group);
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBKCALL libc_wlchown)(char32_t const *file, uid_t owner, gid_t group);
/* >> truncate(2)
 * Truncate the given file `file' to a length of `length' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wtruncate)(char16_t const *file, __PIO_OFFSET length);
/* >> truncate(2)
 * Truncate the given file `file' to a length of `length' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc_wtruncate)(char32_t const *file, __PIO_OFFSET length);
/* >> truncate64(2)
 * Truncate the given file `file' to a length of `length' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wtruncate64)(char16_t const *file, __PIO_OFFSET64 length);
/* >> truncate64(2)
 * Truncate the given file `file' to a length of `length' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc_wtruncate64)(char32_t const *file, __PIO_OFFSET64 length);
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_wsymlink)(char16_t const *link_text, char16_t const *target_path);
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBKCALL libc_wsymlink)(char32_t const *link_text, char32_t const *target_path);
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_RPC(LIBDCALL libd_wreadlink)(char16_t const *path, char16_t *buf, size_t buflen);
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_RPC(LIBKCALL libc_wreadlink)(char32_t const *path, char32_t *buf, size_t buflen);
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wgethostname)(char16_t *name, size_t buflen);
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc_wgethostname)(char32_t *name, size_t buflen);
/* >> setlogin(3) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wsetlogin)(char16_t const *name);
/* >> setlogin(3) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc_wsetlogin)(char32_t const *name);
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wsethostname)(char16_t const *name, size_t len);
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc_wsethostname)(char32_t const *name, size_t len);
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wgetdomainname)(char16_t *name, size_t buflen);
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc_wgetdomainname)(char32_t *name, size_t buflen);
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wsetdomainname)(char16_t const *name, size_t len);
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBKCALL libc_wsetdomainname)(char32_t const *name, size_t len);
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_wchroot)(char16_t const *__restrict path);
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBKCALL libc_wchroot)(char32_t const *__restrict path);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_H */
