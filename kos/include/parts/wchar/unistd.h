/* HASH CRC-32:0x129223a */
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
#ifndef _PARTS_WCHAR_UNISTD_H
#define _PARTS_WCHAR_UNISTD_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _UNISTD_H
#include <unistd.h>
#endif /* !_UNISTD_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#ifndef _PARTS_WCHAR_PROCESS_H
#include <parts/wchar/process.h>
#endif /* !_PARTS_WCHAR_PROCESS_H */

__SYSDECL_BEGIN

#ifdef __CC__

#ifdef __CRT_HAVE_wttyname
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CDECLARE(__ATTR_WUNUSED,wchar_t *,__NOTHROW_RPC,wttyname,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_DOS$wttyname) && __SIZEOF_WCHAR_T__ == 4
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED,wchar_t *,__NOTHROW_RPC,__LIBCCALL,wttyname,(__fd_t __fd),KOS$wttyname,(__fd))
#elif defined(__CRT_HAVE_DOS$wttyname) && __SIZEOF_WCHAR_T__ == 2
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED,wchar_t *,__NOTHROW_RPC,__LIBCCALL,wttyname,(__fd_t __fd),DOS$wttyname,(__fd))
#endif /* ... */
#ifdef __CRT_HAVE_wttyname_r
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,wttyname_r,(__fd_t __fd, wchar_t *__buf, size_t __buflen),(__fd,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wttyname_r) && __SIZEOF_WCHAR_T__ == 4
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBCCALL,wttyname_r,(__fd_t __fd, wchar_t *__buf, size_t __buflen),KOS$wttyname_r,(__fd,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wttyname_r) && __SIZEOF_WCHAR_T__ == 2
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBCCALL,wttyname_r,(__fd_t __fd, wchar_t *__buf, size_t __buflen),DOS$wttyname_r,(__fd,__buf,__buflen))
#endif /* ... */
#ifdef __CRT_HAVE_wgetlogin
__CDECLARE(__ATTR_WUNUSED,wchar_t *,__NOTHROW_NCX,wgetlogin,(void),())
#elif defined(__CRT_HAVE_DOS$wgetlogin) && __SIZEOF_WCHAR_T__ == 4
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED,wchar_t *,__NOTHROW_NCX,__LIBCCALL,wgetlogin,(void),KOS$wgetlogin,())
#elif defined(__CRT_HAVE_DOS$wgetlogin) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED,wchar_t *,__NOTHROW_NCX,__LIBCCALL,wgetlogin,(void),DOS$wgetlogin,())
#endif /* ... */
#ifdef __CRT_HAVE_wchown
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wchown,(wchar_t const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$wchown) && __SIZEOF_WCHAR_T__ == 4
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wchown,(wchar_t const *__file, __uid_t __owner, __gid_t __group),KOS$wchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$wchown) && __SIZEOF_WCHAR_T__ == 2
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wchown,(wchar_t const *__file, __uid_t __owner, __gid_t __group),DOS$wchown,(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_fchownat)
#include <local/parts.wchar.unistd/wchown.h>
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wchown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL wchown)(wchar_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchown))(__file, __owner, __group); })
#endif /* ... */
#ifdef __CRT_HAVE_wpathconf
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CDECLARE(__ATTR_NONNULL((1)),long int,__NOTHROW_RPC,wpathconf,(wchar_t const *__path, int __name),(__path,__name))
#elif defined(__CRT_HAVE_DOS$wpathconf) && __SIZEOF_WCHAR_T__ == 4
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),long int,__NOTHROW_RPC,__LIBCCALL,wpathconf,(wchar_t const *__path, int __name),KOS$wpathconf,(__path,__name))
#elif defined(__CRT_HAVE_DOS$wpathconf) && __SIZEOF_WCHAR_T__ == 2
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),long int,__NOTHROW_RPC,__LIBCCALL,wpathconf,(wchar_t const *__path, int __name),DOS$wpathconf,(__path,__name))
#endif /* ... */
#ifdef __CRT_HAVE_wlink
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wlink,(wchar_t const *__from, wchar_t const *__to),(__from,__to))
#elif defined(__CRT_HAVE_DOS$wlink) && __SIZEOF_WCHAR_T__ == 4
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__LIBCCALL,wlink,(wchar_t const *__from, wchar_t const *__to),KOS$wlink,(__from,__to))
#elif defined(__CRT_HAVE_DOS$wlink) && __SIZEOF_WCHAR_T__ == 2
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__LIBCCALL,wlink,(wchar_t const *__from, wchar_t const *__to),DOS$wlink,(__from,__to))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_linkat)
#include <local/parts.wchar.unistd/wlink.h>
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL wlink)(wchar_t const *__from, wchar_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlink))(__from, __to); })
#endif /* ... */
#ifdef __CRT_HAVE_waccess
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,waccess,(wchar_t const *__file, int __type),(__file,__type))
#elif defined(__CRT_HAVE_DOS$waccess) && __SIZEOF_WCHAR_T__ == 4
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,waccess,(wchar_t const *__file, int __type),KOS$waccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$waccess) && __SIZEOF_WCHAR_T__ == 2
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,waccess,(wchar_t const *__file, int __type),DOS$waccess,(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_faccessat)
#include <local/parts.wchar.unistd/waccess.h>
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(waccess, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL waccess)(wchar_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(waccess))(__file, __type); })
#endif /* ... */
#ifdef __CRT_HAVE_wchdir
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wchdir,(wchar_t const *__path),(__path))
#elif defined(__CRT_HAVE_DOS$wchdir) && __SIZEOF_WCHAR_T__ == 4
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wchdir,(wchar_t const *__path),KOS$wchdir,(__path))
#elif defined(__CRT_HAVE_DOS$_wchdir) && __SIZEOF_WCHAR_T__ == 2
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wchdir,(wchar_t const *__path),DOS$_wchdir,(__path))
#endif /* ... */
#ifdef __CRT_HAVE_wgetcwd
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CDECLARE(,wchar_t *,__NOTHROW_RPC,wgetcwd,(wchar_t *__buf, size_t __bufsize),(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$wgetcwd) && __SIZEOF_WCHAR_T__ == 4
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__COMPILER_REDIRECT(__LIBC,,wchar_t *,__NOTHROW_RPC,__LIBCCALL,wgetcwd,(wchar_t *__buf, size_t __bufsize),KOS$wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$_wgetcwd) && __SIZEOF_WCHAR_T__ == 2
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__COMPILER_REDIRECT(__LIBC,,wchar_t *,__NOTHROW_RPC,__LIBCCALL,wgetcwd,(wchar_t *__buf, size_t __bufsize),DOS$_wgetcwd,(__buf,__bufsize))
#endif /* ... */
#ifdef __CRT_HAVE_wunlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wunlink,(wchar_t const *__file),(__file))
#elif defined(__CRT_HAVE_DOS$wunlink) && __SIZEOF_WCHAR_T__ == 4
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wunlink,(wchar_t const *__file),KOS$wunlink,(__file))
#elif defined(__CRT_HAVE_DOS$_wunlink) && __SIZEOF_WCHAR_T__ == 2
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wunlink,(wchar_t const *__file),DOS$_wunlink,(__file))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/parts.wchar.unistd/wunlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wunlink, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL wunlink)(wchar_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wunlink))(__file); })
#endif /* ... */
#ifdef __CRT_HAVE_wrmdir
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wrmdir,(wchar_t const *__path),(__path))
#elif defined(__CRT_HAVE_DOS$wrmdir) && __SIZEOF_WCHAR_T__ == 4
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wrmdir,(wchar_t const *__path),KOS$wrmdir,(__path))
#elif defined(__CRT_HAVE_DOS$_wrmdir) && __SIZEOF_WCHAR_T__ == 2
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wrmdir,(wchar_t const *__path),DOS$_wrmdir,(__path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/parts.wchar.unistd/wrmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wrmdir, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL wrmdir)(wchar_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrmdir))(__path); })
#endif /* ... */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_weuidaccess
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,weuidaccess,(wchar_t const *__file, int __type),(__file,__type))
#elif defined(__CRT_HAVE_DOS$weuidaccess) && __SIZEOF_WCHAR_T__ == 4
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,weuidaccess,(wchar_t const *__file, int __type),KOS$weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$weuidaccess) && __SIZEOF_WCHAR_T__ == 2
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,weuidaccess,(wchar_t const *__file, int __type),DOS$weuidaccess,(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_faccessat)
#include <local/parts.wchar.unistd/weuidaccess.h>
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__NAMESPACE_LOCAL_USING_OR_IMPL(weuidaccess, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL weuidaccess)(wchar_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))(__file, __type); })
#endif /* ... */
#ifdef __CRT_HAVE_weuidaccess
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,weaccess,(wchar_t const *__file, int __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$weuidaccess) && __SIZEOF_WCHAR_T__ == 4
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,weaccess,(wchar_t const *__file, int __type),KOS$weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$weuidaccess) && __SIZEOF_WCHAR_T__ == 2
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,weaccess,(wchar_t const *__file, int __type),DOS$weuidaccess,(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_faccessat)
#include <local/parts.wchar.unistd/weuidaccess.h>
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL weaccess)(wchar_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))(__file, __type); }
#endif /* ... */
#ifdef __CRT_HAVE_wget_current_dir_name
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,wchar_t *,__NOTHROW_RPC,wget_current_dir_name,(void),())
#elif defined(__CRT_HAVE_DOS$wget_current_dir_name) && __SIZEOF_WCHAR_T__ == 4
__COMPILER_REDIRECT(__LIBC,__ATTR_MALLOC __ATTR_WUNUSED,wchar_t *,__NOTHROW_RPC,__LIBCCALL,wget_current_dir_name,(void),KOS$wget_current_dir_name,())
#elif defined(__CRT_HAVE_DOS$wget_current_dir_name) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_REDIRECT(__LIBC,__ATTR_MALLOC __ATTR_WUNUSED,wchar_t *,__NOTHROW_RPC,__LIBCCALL,wget_current_dir_name,(void),DOS$wget_current_dir_name,())
#elif defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
#include <local/parts.wchar.unistd/wget_current_dir_name.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wget_current_dir_name, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED wchar_t *__NOTHROW_RPC(__LIBCCALL wget_current_dir_name)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wget_current_dir_name))(); })
#endif /* ... */
#endif /* __USE_GNU */
#ifdef __USE_ATFILE
#ifdef __CRT_HAVE_wfaccessat
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,wfaccessat,(__fd_t __dfd, wchar_t const *__file, int __type, __atflag_t __flags),(__dfd,__file,__type,__flags))
#elif defined(__CRT_HAVE_DOS$wfaccessat) && __SIZEOF_WCHAR_T__ == 4
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBCCALL,wfaccessat,(__fd_t __dfd, wchar_t const *__file, int __type, __atflag_t __flags),KOS$wfaccessat,(__dfd,__file,__type,__flags))
#elif defined(__CRT_HAVE_DOS$wfaccessat) && __SIZEOF_WCHAR_T__ == 2
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBCCALL,wfaccessat,(__fd_t __dfd, wchar_t const *__file, int __type, __atflag_t __flags),DOS$wfaccessat,(__dfd,__file,__type,__flags))
#endif /* ... */
#ifdef __CRT_HAVE_wfchownat
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,wfchownat,(__fd_t __dfd, wchar_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_DOS$wfchownat) && __SIZEOF_WCHAR_T__ == 4
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBCCALL,wfchownat,(__fd_t __dfd, wchar_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),KOS$wfchownat,(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_DOS$wfchownat) && __SIZEOF_WCHAR_T__ == 2
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBCCALL,wfchownat,(__fd_t __dfd, wchar_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),DOS$wfchownat,(__dfd,__file,__owner,__group,__flags))
#endif /* ... */
#ifdef __CRT_HAVE_wlinkat
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__CDECLARE(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,wlinkat,(__fd_t __fromfd, wchar_t const *__from, __fd_t __tofd, wchar_t const *__to, __atflag_t __flags),(__fromfd,__from,__tofd,__to,__flags))
#elif defined(__CRT_HAVE_DOS$wlinkat) && __SIZEOF_WCHAR_T__ == 4
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,__LIBCCALL,wlinkat,(__fd_t __fromfd, wchar_t const *__from, __fd_t __tofd, wchar_t const *__to, __atflag_t __flags),KOS$wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#elif defined(__CRT_HAVE_DOS$wlinkat) && __SIZEOF_WCHAR_T__ == 2
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,__LIBCCALL,wlinkat,(__fd_t __fromfd, wchar_t const *__from, __fd_t __tofd, wchar_t const *__to, __atflag_t __flags),DOS$wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#endif /* ... */
#ifdef __CRT_HAVE_wsymlinkat
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CDECLARE(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,wsymlinkat,(wchar_t const *__link_text, __fd_t __tofd, wchar_t const *__target_path),(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_DOS$wsymlinkat) && __SIZEOF_WCHAR_T__ == 4
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__LIBCCALL,wsymlinkat,(wchar_t const *__link_text, __fd_t __tofd, wchar_t const *__target_path),KOS$wsymlinkat,(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_DOS$wsymlinkat) && __SIZEOF_WCHAR_T__ == 2
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__LIBCCALL,wsymlinkat,(wchar_t const *__link_text, __fd_t __tofd, wchar_t const *__target_path),DOS$wsymlinkat,(__link_text,__tofd,__target_path))
#endif /* ... */
#ifdef __CRT_HAVE_wreadlinkat
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CDECLARE(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,wreadlinkat,(__fd_t __dfd, wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen),(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlinkat) && __SIZEOF_WCHAR_T__ == 4
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,__LIBCCALL,wreadlinkat,(__fd_t __dfd, wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen),KOS$wreadlinkat,(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlinkat) && __SIZEOF_WCHAR_T__ == 2
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,__LIBCCALL,wreadlinkat,(__fd_t __dfd, wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen),DOS$wreadlinkat,(__dfd,__path,__buf,__buflen))
#endif /* ... */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_wfreadlinkat
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__CDECLARE(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,wfreadlinkat,(__fd_t __dfd, wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen, __atflag_t __flags),(__dfd,__path,__buf,__buflen,__flags))
#elif defined(__CRT_HAVE_DOS$wfreadlinkat) && __SIZEOF_WCHAR_T__ == 4
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,__LIBCCALL,wfreadlinkat,(__fd_t __dfd, wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen, __atflag_t __flags),KOS$wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#elif defined(__CRT_HAVE_DOS$wfreadlinkat) && __SIZEOF_WCHAR_T__ == 2
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,__LIBCCALL,wfreadlinkat,(__fd_t __dfd, wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen, __atflag_t __flags),DOS$wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#endif /* ... */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_wunlinkat
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,wunlinkat,(__fd_t __dfd, wchar_t const *__name, __atflag_t __flags),(__dfd,__name,__flags))
#elif defined(__CRT_HAVE_DOS$wunlinkat) && __SIZEOF_WCHAR_T__ == 4
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBCCALL,wunlinkat,(__fd_t __dfd, wchar_t const *__name, __atflag_t __flags),KOS$wunlinkat,(__dfd,__name,__flags))
#elif defined(__CRT_HAVE_DOS$wunlinkat) && __SIZEOF_WCHAR_T__ == 2
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBCCALL,wunlinkat,(__fd_t __dfd, wchar_t const *__name, __atflag_t __flags),DOS$wunlinkat,(__dfd,__name,__flags))
#endif /* ... */
#endif /* __USE_ATFILE */
#ifdef __CRT_HAVE_wlchown
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wlchown,(wchar_t const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$wlchown) && __SIZEOF_WCHAR_T__ == 4
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wlchown,(wchar_t const *__file, __uid_t __owner, __gid_t __group),KOS$wlchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$wlchown) && __SIZEOF_WCHAR_T__ == 2
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wlchown,(wchar_t const *__file, __uid_t __owner, __gid_t __group),DOS$wlchown,(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_fchownat)
#include <local/parts.wchar.unistd/wlchown.h>
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__NAMESPACE_LOCAL_USING_OR_IMPL(wlchown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL wlchown)(wchar_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlchown))(__file, __owner, __group); })
#endif /* ... */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET   __FS_TYPE(pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET   __FS_TYPE(off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
#if defined(__CRT_HAVE_wtruncate64) && defined(__USE_FILE_OFFSET64)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtruncate,(wchar_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate64) && defined(__USE_FILE_OFFSET64) && __SIZEOF_WCHAR_T__ == 4
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wtruncate,(wchar_t const *__file, __PIO_OFFSET __length),KOS$wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate64) && defined(__USE_FILE_OFFSET64) && __SIZEOF_WCHAR_T__ == 2
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wtruncate,(wchar_t const *__file, __PIO_OFFSET __length),DOS$wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) && !defined(__USE_FILE_OFFSET64)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtruncate,(wchar_t const *__file, __PIO_OFFSET __length),(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate) && !defined(__USE_FILE_OFFSET64) && __SIZEOF_WCHAR_T__ == 4
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wtruncate,(wchar_t const *__file, __PIO_OFFSET __length),KOS$wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate) && !defined(__USE_FILE_OFFSET64) && __SIZEOF_WCHAR_T__ == 2
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wtruncate,(wchar_t const *__file, __PIO_OFFSET __length),DOS$wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_truncate64) || defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate))) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && ((defined(__CRT_HAVE__chsize) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_chsize) && !defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s)))
#include <local/parts.wchar.unistd/wtruncate.h>
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wtruncate, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL wtruncate)(wchar_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate))(__file, __length); })
#endif /* ... */
#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_wtruncate64
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtruncate64,(wchar_t const *__file, __PIO_OFFSET64 __length),(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate64) && __SIZEOF_WCHAR_T__ == 4
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wtruncate64,(wchar_t const *__file, __PIO_OFFSET64 __length),KOS$wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate64) && __SIZEOF_WCHAR_T__ == 2
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wtruncate64,(wchar_t const *__file, __PIO_OFFSET64 __length),DOS$wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtruncate64,(wchar_t const *__file, __PIO_OFFSET64 __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && __SIZEOF_WCHAR_T__ == 4
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wtruncate64,(wchar_t const *__file, __PIO_OFFSET64 __length),KOS$wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && __SIZEOF_WCHAR_T__ == 2
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wtruncate64,(wchar_t const *__file, __PIO_OFFSET64 __length),DOS$wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate)))
#include <local/parts.wchar.unistd/wtruncate64.h>
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wtruncate64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL wtruncate64)(wchar_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate64))(__file, __length); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_wsymlink
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wsymlink,(wchar_t const *__link_text, wchar_t const *__target_path),(__link_text,__target_path))
#elif defined(__CRT_HAVE_DOS$wsymlink) && __SIZEOF_WCHAR_T__ == 4
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__LIBCCALL,wsymlink,(wchar_t const *__link_text, wchar_t const *__target_path),KOS$wsymlink,(__link_text,__target_path))
#elif defined(__CRT_HAVE_DOS$wsymlink) && __SIZEOF_WCHAR_T__ == 2
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__LIBCCALL,wsymlink,(wchar_t const *__link_text, wchar_t const *__target_path),DOS$wsymlink,(__link_text,__target_path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_symlinkat)
#include <local/parts.wchar.unistd/wsymlink.h>
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wsymlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL wsymlink)(wchar_t const *__link_text, wchar_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsymlink))(__link_text, __target_path); })
#endif /* ... */
#ifdef __CRT_HAVE_wreadlink
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CDECLARE(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,wreadlink,(wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen),(__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlink) && __SIZEOF_WCHAR_T__ == 4
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,__LIBCCALL,wreadlink,(wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen),KOS$wreadlink,(__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlink) && __SIZEOF_WCHAR_T__ == 2
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,__LIBCCALL,wreadlink,(wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen),DOS$wreadlink,(__path,__buf,__buflen))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_readlinkat)
#include <local/parts.wchar.unistd/wreadlink.h>
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wreadlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBCCALL wreadlink)(wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wreadlink))(__path, __buf, __buflen); })
#endif /* ... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
#ifdef __CRT_HAVE_wgetlogin_r
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wgetlogin_r,(wchar_t *__name, size_t __name_len),(__name,__name_len))
#elif defined(__CRT_HAVE_DOS$wgetlogin_r) && __SIZEOF_WCHAR_T__ == 4
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wgetlogin_r,(wchar_t *__name, size_t __name_len),KOS$wgetlogin_r,(__name,__name_len))
#elif defined(__CRT_HAVE_DOS$wgetlogin_r) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wgetlogin_r,(wchar_t *__name, size_t __name_len),DOS$wgetlogin_r,(__name,__name_len))
#endif /* ... */
#endif /* __USE_REENTRANT || __USE_POSIX199506 */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_wgethostname
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wgethostname,(wchar_t *__name, size_t __buflen),(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$wgethostname) && __SIZEOF_WCHAR_T__ == 4
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wgethostname,(wchar_t *__name, size_t __buflen),KOS$wgethostname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$wgethostname) && __SIZEOF_WCHAR_T__ == 2
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wgethostname,(wchar_t *__name, size_t __buflen),DOS$wgethostname,(__name,__buflen))
#endif /* ... */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_wsetlogin
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wsetlogin,(wchar_t const *__name),(__name))
#elif defined(__CRT_HAVE_DOS$wsetlogin) && __SIZEOF_WCHAR_T__ == 4
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wsetlogin,(wchar_t const *__name),KOS$wsetlogin,(__name))
#elif defined(__CRT_HAVE_DOS$wsetlogin) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wsetlogin,(wchar_t const *__name),DOS$wsetlogin,(__name))
#endif /* ... */
#ifdef __CRT_HAVE_wsethostname
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wsethostname,(wchar_t const *__name, size_t __len),(__name,__len))
#elif defined(__CRT_HAVE_DOS$wsethostname) && __SIZEOF_WCHAR_T__ == 4
/* >> sethostname(2)
 * Set the name of the hosting machine */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wsethostname,(wchar_t const *__name, size_t __len),KOS$wsethostname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$wsethostname) && __SIZEOF_WCHAR_T__ == 2
/* >> sethostname(2)
 * Set the name of the hosting machine */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wsethostname,(wchar_t const *__name, size_t __len),DOS$wsethostname,(__name,__len))
#endif /* ... */
#ifdef __CRT_HAVE_wgetdomainname
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wgetdomainname,(wchar_t *__name, size_t __buflen),(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$wgetdomainname) && __SIZEOF_WCHAR_T__ == 4
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wgetdomainname,(wchar_t *__name, size_t __buflen),KOS$wgetdomainname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$wgetdomainname) && __SIZEOF_WCHAR_T__ == 2
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wgetdomainname,(wchar_t *__name, size_t __buflen),DOS$wgetdomainname,(__name,__buflen))
#endif /* ... */
#ifdef __CRT_HAVE_wsetdomainname
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wsetdomainname,(wchar_t const *__name, size_t __len),(__name,__len))
#elif defined(__CRT_HAVE_DOS$wsetdomainname) && __SIZEOF_WCHAR_T__ == 4
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wsetdomainname,(wchar_t const *__name, size_t __len),KOS$wsetdomainname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$wsetdomainname) && __SIZEOF_WCHAR_T__ == 2
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBCCALL,wsetdomainname,(wchar_t const *__name, size_t __len),DOS$wsetdomainname,(__name,__len))
#endif /* ... */
#endif /* __USE_MISC */

#if (defined(__USE_MISC) || \
     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
#ifdef __CRT_HAVE_wchroot
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wchroot,(wchar_t const *__restrict __path),(__path))
#elif defined(__CRT_HAVE_DOS$wchroot) && __SIZEOF_WCHAR_T__ == 4
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wchroot,(wchar_t const *__restrict __path),KOS$wchroot,(__path))
#elif defined(__CRT_HAVE_DOS$wchroot) && __SIZEOF_WCHAR_T__ == 2
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBCCALL,wchroot,(wchar_t const *__restrict __path),DOS$wchroot,(__path))
#endif /* ... */
#endif /* ... */

#if (defined(_EVERY_SOURCE) || \
     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
#ifdef __CRT_HAVE_wctermid
__CDECLARE(,wchar_t *,__NOTHROW_NCX,wctermid,(wchar_t *__s),(__s))
#elif defined(__CRT_HAVE_DOS$wctermid) && __SIZEOF_WCHAR_T__ == 4
__COMPILER_REDIRECT(__LIBC,,wchar_t *,__NOTHROW_NCX,__LIBCCALL,wctermid,(wchar_t *__s),KOS$wctermid,(__s))
#elif defined(__CRT_HAVE_DOS$wctermid) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_REDIRECT(__LIBC,,wchar_t *,__NOTHROW_NCX,__LIBCCALL,wctermid,(wchar_t *__s),DOS$wctermid,(__s))
#endif /* ... */
#endif /* _EVERY_SOURCE || (__USE_XOPEN && !__USE_XOPEN2K) */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_WCHAR_UNISTD_H */
