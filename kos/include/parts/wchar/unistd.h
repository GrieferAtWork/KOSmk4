/* HASH CRC-32:0xa7b5a9ef */
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
/* >> wttyname(3)
 * Return the name of a TTY given its file descriptor */
__CDECLARE(__ATTR_WUNUSED,wchar_t *,__NOTHROW_RPC,wttyname,(__fd_t __fd),(__fd))
#endif /* wttyname... */
#ifdef __CRT_HAVE_wttyname_r
/* >> wttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,wttyname_r,(__fd_t __fd, wchar_t *__buf, size_t __buflen),(__fd,__buf,__buflen))
#endif /* wttyname_r... */
#ifdef __CRT_HAVE_wgetlogin
__CDECLARE(__ATTR_WUNUSED,wchar_t *,__NOTHROW_NCX,wgetlogin,(void),())
#endif /* wgetlogin... */
#ifdef __CRT_HAVE_wchown
/* >> wchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wchown,(wchar_t const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfchownat)
#include <local/parts.wchar.unistd/wchown.h>
/* >> wchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wchown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL wchown)(wchar_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchown))(__file, __owner, __group); })
#endif /* wchown... */
#ifdef __CRT_HAVE_wpathconf
/* >> wpathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CDECLARE(__ATTR_NONNULL((1)),long int,__NOTHROW_RPC,wpathconf,(wchar_t const *__path, int __name),(__path,__name))
#endif /* wpathconf... */
#ifdef __CRT_HAVE_wlink
/* >> wlink(2)
 * Create a hard link from `FROM', leading to `TO' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wlink,(wchar_t const *__from, wchar_t const *__to),(__from,__to))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wlinkat)
#include <local/parts.wchar.unistd/wlink.h>
/* >> wlink(2)
 * Create a hard link from `FROM', leading to `TO' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL wlink)(wchar_t const *__from, wchar_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlink))(__from, __to); })
#endif /* wlink... */
#ifdef __CRT_HAVE_waccess
/* >> waccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,waccess,(wchar_t const *__file, int __type),(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfaccessat)
#include <local/parts.wchar.unistd/waccess.h>
/* >> waccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(waccess, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL waccess)(wchar_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(waccess))(__file, __type); })
#endif /* waccess... */
#ifdef __CRT_HAVE_wchdir
/* >> wchdir(2)
 * Change the current working directory to `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wchdir,(wchar_t const *__path),(__path))
#elif defined(__CRT_HAVE__wchdir)
/* >> wchdir(2)
 * Change the current working directory to `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wchdir,(wchar_t const *__path),_wchdir,(__path))
#endif /* wchdir... */
#ifdef __CRT_HAVE_wgetcwd
/* >> wgetcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `wchdir(2)' */
__CDECLARE(,wchar_t *,__NOTHROW_RPC,wgetcwd,(wchar_t *__buf, size_t __bufsize),(__buf,__bufsize))
#elif defined(__CRT_HAVE__wgetcwd)
/* >> wgetcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `wchdir(2)' */
__CREDIRECT(,wchar_t *,__NOTHROW_RPC,wgetcwd,(wchar_t *__buf, size_t __bufsize),_wgetcwd,(__buf,__bufsize))
#endif /* wgetcwd... */
#ifdef __CRT_HAVE_wunlink
/* >> wunlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wunlink,(wchar_t const *__file),(__file))
#elif defined(__CRT_HAVE__wunlink)
/* >> wunlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wunlink,(wchar_t const *__file),_wunlink,(__file))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wunlinkat)
#include <local/parts.wchar.unistd/wunlink.h>
/* >> wunlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wunlink, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL wunlink)(wchar_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wunlink))(__file); })
#endif /* wunlink... */
#ifdef __CRT_HAVE_wrmdir
/* >> wrmdir(2)
 * Remove a directory referred to by `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wrmdir,(wchar_t const *__path),(__path))
#elif defined(__CRT_HAVE__wrmdir)
/* >> wrmdir(2)
 * Remove a directory referred to by `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wrmdir,(wchar_t const *__path),_wrmdir,(__path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wunlinkat)
#include <local/parts.wchar.unistd/wrmdir.h>
/* >> wrmdir(2)
 * Remove a directory referred to by `PATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wrmdir, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL wrmdir)(wchar_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrmdir))(__path); })
#endif /* wrmdir... */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_weuidaccess
/* >> weuidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,weuidaccess,(wchar_t const *__file, int __type),(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfaccessat)
#include <local/parts.wchar.unistd/weuidaccess.h>
/* >> weuidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__NAMESPACE_LOCAL_USING_OR_IMPL(weuidaccess, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL weuidaccess)(wchar_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))(__file, __type); })
#endif /* weuidaccess... */
#ifdef __CRT_HAVE_weaccess
/* >> weuidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,weaccess,(wchar_t const *__file, int __type),(__file,__type))
#elif defined(__CRT_HAVE_weuidaccess)
/* >> weuidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,weaccess,(wchar_t const *__file, int __type),weuidaccess,(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfaccessat)
#include <local/parts.wchar.unistd/weuidaccess.h>
/* >> weuidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL weaccess)(wchar_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))(__file, __type); }
#endif /* weaccess... */
#ifdef __CRT_HAVE_wget_current_dir_name
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,wchar_t *,__NOTHROW_RPC,wget_current_dir_name,(void),())
#elif defined(__CRT_HAVE_wgetcwd) || defined(__CRT_HAVE__wgetcwd)
#include <local/parts.wchar.unistd/wget_current_dir_name.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wget_current_dir_name, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED wchar_t *__NOTHROW_RPC(__LIBCCALL wget_current_dir_name)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wget_current_dir_name))(); })
#endif /* wget_current_dir_name... */
#endif /* __USE_GNU */
#ifdef __USE_ATFILE
#ifdef __CRT_HAVE_wfaccessat
/* >> wfaccessat(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,wfaccessat,(__fd_t __dfd, wchar_t const *__file, int __type, __atflag_t __flags),(__dfd,__file,__type,__flags))
#endif /* wfaccessat... */
#ifdef __CRT_HAVE_wfchownat
/* >> wfchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,wfchownat,(__fd_t __dfd, wchar_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),(__dfd,__file,__owner,__group,__flags))
#endif /* wfchownat... */
#ifdef __CRT_HAVE_wlinkat
/* >> wlinkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__CDECLARE(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,wlinkat,(__fd_t __fromfd, wchar_t const *__from, __fd_t __tofd, wchar_t const *__to, __atflag_t __flags),(__fromfd,__from,__tofd,__to,__flags))
#endif /* wlinkat... */
#ifdef __CRT_HAVE_wsymlinkat
/* >> wsymlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CDECLARE(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,wsymlinkat,(wchar_t const *__link_text, __fd_t __tofd, wchar_t const *__target_path),(__link_text,__tofd,__target_path))
#endif /* wsymlinkat... */
#ifdef __CRT_HAVE_wreadlinkat
/* >> wreadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `wfreadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CDECLARE(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,wreadlinkat,(__fd_t __dfd, wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen),(__dfd,__path,__buf,__buflen))
#endif /* wreadlinkat... */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_wfreadlinkat
/* >> wfreadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__CDECLARE(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,wfreadlinkat,(__fd_t __dfd, wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen, __atflag_t __flags),(__dfd,__path,__buf,__buflen,__flags))
#endif /* wfreadlinkat... */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_wunlinkat
/* >> wunlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,wunlinkat,(__fd_t __dfd, wchar_t const *__name, __atflag_t __flags),(__dfd,__name,__flags))
#endif /* wunlinkat... */
#endif /* __USE_ATFILE */
#ifdef __CRT_HAVE_wlchown
/* >> wlchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wlchown,(wchar_t const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfchownat)
#include <local/parts.wchar.unistd/wlchown.h>
/* >> wlchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__NAMESPACE_LOCAL_USING_OR_IMPL(wlchown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL wlchown)(wchar_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlchown))(__file, __owner, __group); })
#endif /* wlchown... */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif
#endif /* !__PIO_OFFSET */
#if defined(__CRT_HAVE_wtruncate64) && defined(__USE_FILE_OFFSET64)
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtruncate,(wchar_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) && !defined(__USE_FILE_OFFSET64)
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtruncate,(wchar_t const *__file, __PIO_OFFSET __length),(__file,__length))
#elif defined(__CRT_HAVE_wtruncate64) || defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE__open)) && (defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64)))
#include <local/parts.wchar.unistd/wtruncate.h>
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wtruncate, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL wtruncate)(wchar_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate))(__file, __length); })
#endif /* wtruncate... */
#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_wtruncate64
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtruncate64,(wchar_t const *__file, __PIO_OFFSET64 __length),(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wtruncate64,(wchar_t const *__file, __PIO_OFFSET64 __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE__open)) && (defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64)))
#include <local/parts.wchar.unistd/wtruncate64.h>
/* >> wtruncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wtruncate64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL wtruncate64)(wchar_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate64))(__file, __length); })
#endif /* wtruncate64... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_wsymlink
/* >> wsymlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `wsymlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wsymlink,(wchar_t const *__link_text, wchar_t const *__target_path),(__link_text,__target_path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wsymlinkat)
#include <local/parts.wchar.unistd/wsymlink.h>
/* >> wsymlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `wsymlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wsymlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL wsymlink)(wchar_t const *__link_text, wchar_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsymlink))(__link_text, __target_path); })
#endif /* wsymlink... */
#ifdef __CRT_HAVE_wreadlink
/* >> wreadlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `wreadlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `wfreadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CDECLARE(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,wreadlink,(wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen),(__path,__buf,__buflen))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wreadlinkat)
#include <local/parts.wchar.unistd/wreadlink.h>
/* >> wreadlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `wreadlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `wfreadlinkat(2)' with `AT_READLINK_REQSIZE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wreadlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBCCALL wreadlink)(wchar_t const *__restrict __path, wchar_t *__restrict __buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wreadlink))(__path, __buf, __buflen); })
#endif /* wreadlink... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */
#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
#ifdef __CRT_HAVE_wgetlogin_r
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wgetlogin_r,(wchar_t *__name, size_t __name_len),(__name,__name_len))
#endif /* wgetlogin_r... */
#endif /* __USE_REENTRANT || __USE_POSIX199506 */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_wgethostname
/* >> wgethostname(3)
 * Return the name assigned to the hosting machine, as set by `wsethostname(2)' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wgethostname,(wchar_t *__name, size_t __buflen),(__name,__buflen))
#endif /* wgethostname... */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */
#ifdef __USE_MISC
#ifdef __CRT_HAVE_wsetlogin
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wsetlogin,(wchar_t const *__name),(__name))
#endif /* wsetlogin... */
#ifdef __CRT_HAVE_wsethostname
/* >> wsethostname(2)
 * Set the name of the hosting machine */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wsethostname,(wchar_t const *__name, size_t __len),(__name,__len))
#endif /* wsethostname... */
#ifdef __CRT_HAVE_wgetdomainname
/* >> wgetdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `wsetdomainname(2)' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wgetdomainname,(wchar_t *__name, size_t __buflen),(__name,__buflen))
#endif /* wgetdomainname... */
#ifdef __CRT_HAVE_wsetdomainname
/* >> wsetdomainname(2)
 * Set the name of the hosting machine's domain */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,wsetdomainname,(wchar_t const *__name, size_t __len),(__name,__len))
#endif /* wsetdomainname... */
#endif /* __USE_MISC */
#if defined(__USE_MISC) || \
   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#ifdef __CRT_HAVE_wchroot
/* >> wchroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wchroot,(wchar_t const *__restrict __path),(__path))
#endif /* wchroot... */
#endif /* ... */

#if (defined(_EVERY_SOURCE) || \
     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
#ifdef __CRT_HAVE_wctermid
__CDECLARE(,wchar_t *,__NOTHROW_NCX,wctermid,(wchar_t *__s),(__s))
#endif /* wctermid... */
#endif /* _EVERY_SOURCE || (__USE_XOPEN && !__USE_XOPEN2K) */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_WCHAR_UNISTD_H */
