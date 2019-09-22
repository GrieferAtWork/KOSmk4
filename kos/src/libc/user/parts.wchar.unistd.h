/* HASH CRC-32:0x598acd2 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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

/* >> wttyname(3)
 * Return the name of a TTY given its file descriptor */
INTDEF WUNUSED char32_t *NOTHROW_RPC(LIBCCALL libc_wttyname)(fd_t fd);
/* >> wttyname(3)
 * Return the name of a TTY given its file descriptor */
INTDEF WUNUSED char16_t *NOTHROW_RPC(LIBDCALL libd_wttyname)(fd_t fd);
/* >> wttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_wttyname_r)(fd_t fd, char32_t *buf, size_t buflen);
/* >> wttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_wttyname_r)(fd_t fd, char16_t *buf, size_t buflen);
INTDEF WUNUSED char32_t *NOTHROW_NCX(LIBCCALL libc_wgetlogin)(void);
INTDEF WUNUSED char16_t *NOTHROW_NCX(LIBDCALL libd_wgetlogin)(void);
/* >> wchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_wchown)(char32_t const *file, uid_t owner, gid_t group);
/* >> wchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_wchown)(char16_t const *file, uid_t owner, gid_t group);
/* >> wpathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH' */
INTDEF NONNULL((1)) long int NOTHROW_RPC(LIBCCALL libc_wpathconf)(char32_t const *path, int name);
/* >> wpathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH' */
INTDEF NONNULL((1)) long int NOTHROW_RPC(LIBDCALL libd_wpathconf)(char16_t const *path, int name);
/* >> wlink(2)
 * Create a hard link from `FROM', leading to `TO' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_wlink)(char32_t const *from, char32_t const *to);
/* >> wlink(2)
 * Create a hard link from `FROM', leading to `TO' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_wlink)(char16_t const *from, char16_t const *to);
/* >> waccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_waccess)(char32_t const *file, int type);
/* >> waccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_waccess)(char16_t const *file, int type);
/* >> wchdir(2)
 * Change the current working directory to `PATH' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_wchdir)(char32_t const *path);
/* >> wchdir(2)
 * Change the current working directory to `PATH' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_wchdir)(char16_t const *path);
/* >> wgetcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `wchdir(2)' */
INTDEF char32_t *NOTHROW_RPC(LIBCCALL libc_wgetcwd)(char32_t *buf, size_t bufsize);
/* >> wgetcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `wchdir(2)' */
INTDEF char16_t *NOTHROW_RPC(LIBDCALL libd_wgetcwd)(char16_t *buf, size_t bufsize);
/* >> wunlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_wunlink)(char32_t const *file);
/* >> wunlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_wunlink)(char16_t const *file);
/* >> wrmdir(2)
 * Remove a directory referred to by `PATH' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_wrmdir)(char32_t const *path);
/* >> wrmdir(2)
 * Remove a directory referred to by `PATH' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_wrmdir)(char16_t const *path);
/* >> weuidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_weuidaccess)(char32_t const *file, int type);
/* >> weuidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_weuidaccess)(char16_t const *file, int type);
INTDEF WUNUSED ATTR_MALLOC char32_t *NOTHROW_RPC(LIBCCALL libc_wget_current_dir_name)(void);
INTDEF WUNUSED ATTR_MALLOC char16_t *NOTHROW_RPC(LIBDCALL libd_wget_current_dir_name)(void);
/* >> wfaccessat(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_wfaccessat)(fd_t dfd, char32_t const *file, int type, atflag_t flags);
/* >> wfaccessat(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_wfaccessat)(fd_t dfd, char16_t const *file, int type, atflag_t flags);
/* >> wfchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_wfchownat)(fd_t dfd, char32_t const *file, uid_t owner, gid_t group, atflag_t flags);
/* >> wfchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_wfchownat)(fd_t dfd, char16_t const *file, uid_t owner, gid_t group, atflag_t flags);
/* >> wlinkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBCCALL libc_wlinkat)(fd_t fromfd, char32_t const *from, fd_t tofd, char32_t const *to, atflag_t flags);
/* >> wlinkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBDCALL libd_wlinkat)(fd_t fromfd, char16_t const *from, fd_t tofd, char16_t const *to, atflag_t flags);
/* >> wsymlinkat(3)
 * Create a new symbolic link loaded with `FROM' as link
 * text, at the filesystem location referred to by `TOFD:TO' */
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBCCALL libc_wsymlinkat)(char32_t const *from, fd_t tofd, char32_t const *to);
/* >> wsymlinkat(3)
 * Create a new symbolic link loaded with `FROM' as link
 * text, at the filesystem location referred to by `TOFD:TO' */
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBDCALL libd_wsymlinkat)(char16_t const *from, fd_t tofd, char16_t const *to);
/* >> wreadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `wfreadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBCCALL libc_wreadlinkat)(fd_t dfd, char32_t const *__restrict path, char32_t *__restrict buf, size_t buflen);
/* >> wreadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `wfreadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBDCALL libd_wreadlinkat)(fd_t dfd, char16_t const *__restrict path, char16_t *__restrict buf, size_t buflen);
/* >> wfreadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBCCALL libc_wfreadlinkat)(fd_t dfd, char32_t const *__restrict path, char32_t *__restrict buf, size_t buflen, atflag_t flags);
/* >> wfreadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBDCALL libd_wfreadlinkat)(fd_t dfd, char16_t const *__restrict path, char16_t *__restrict buf, size_t buflen, atflag_t flags);
/* >> wunlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_wunlinkat)(fd_t dfd, char32_t const *name, atflag_t flags);
/* >> wunlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_wunlinkat)(fd_t dfd, char16_t const *name, atflag_t flags);
/* >> wlchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_wlchown)(char32_t const *file, uid_t owner, gid_t group);
/* >> wlchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_wlchown)(char16_t const *file, uid_t owner, gid_t group);
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_wtruncate)(char32_t const *file, __PIO_OFFSET length);
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wtruncate)(char16_t const *file, __PIO_OFFSET length);
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_wtruncate64)(char32_t const *file, __PIO_OFFSET64 length);
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wtruncate64)(char16_t const *file, __PIO_OFFSET64 length);
/* >> wsymlink(3)
 * Create a new symbolic link loaded with `FROM' as link
 * text, at the filesystem location referred to by `TO'.
 * Same as `wsymlinkat(FROM, AT_FDCWD, TO)' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_wsymlink)(char32_t const *from, char32_t const *to);
/* >> wsymlink(3)
 * Create a new symbolic link loaded with `FROM' as link
 * text, at the filesystem location referred to by `TO'.
 * Same as `wsymlinkat(FROM, AT_FDCWD, TO)' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_wsymlink)(char16_t const *from, char16_t const *to);
/* >> wreadlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `wreadlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `wfreadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_RPC(LIBCCALL libc_wreadlink)(char32_t const *__restrict path, char32_t *__restrict buf, size_t buflen);
/* >> wreadlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `wreadlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `wfreadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_RPC(LIBDCALL libd_wreadlink)(char16_t const *__restrict path, char16_t *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_wgetlogin_r)(char32_t *name, size_t name_len);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_wgetlogin_r)(char16_t *name, size_t name_len);
/* >> wgethostname(3)
 * Return the name assigned to the hosting machine, as set by `wsethostname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_wgethostname)(char32_t *name, size_t buflen);
/* >> wgethostname(3)
 * Return the name assigned to the hosting machine, as set by `wsethostname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wgethostname)(char16_t *name, size_t buflen);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_wsetlogin)(char32_t const *name);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wsetlogin)(char16_t const *name);
/* >> wsethostname(2)
 * Set the name of the hosting machine */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_wsethostname)(char32_t const *name, size_t len);
/* >> wsethostname(2)
 * Set the name of the hosting machine */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wsethostname)(char16_t const *name, size_t len);
/* >> wgetdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `wsetdomainname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_wgetdomainname)(char32_t *name, size_t buflen);
/* >> wgetdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `wsetdomainname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wgetdomainname)(char16_t *name, size_t buflen);
/* >> wsetdomainname(2)
 * Set the name of the hosting machine's domain */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_wsetdomainname)(char32_t const *name, size_t len);
/* >> wsetdomainname(2)
 * Set the name of the hosting machine's domain */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_wsetdomainname)(char16_t const *name, size_t len);
/* >> wchroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_wchroot)(char32_t const *__restrict path);
/* >> wchroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_wchroot)(char16_t const *__restrict path);
INTDEF char32_t *NOTHROW_NCX(LIBCCALL libc_wctermid)(char32_t *s);
INTDEF char16_t *NOTHROW_NCX(LIBDCALL libd_wctermid)(char16_t *s);

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_H */
