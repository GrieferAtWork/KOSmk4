/* HASH CRC-32:0xd153f165 */
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
#ifndef _PARTS_UCHAR_UNISTD_H
#define _PARTS_UCHAR_UNISTD_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _UNISTD_H
#include <unistd.h>
#endif /* !_UNISTD_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */
#ifndef _PARTS_UCHAR_PROCESS_H
#include <parts/uchar/process.h>
#endif /* !_PARTS_UCHAR_PROCESS_H */

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__CRT_HAVE_wttyname) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT(__ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,c16ttyname,(__fd_t __fd),wttyname,(__fd))
#elif defined(__CRT_HAVE_DOS$wttyname)
/* >> c16ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_DOS(__ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,c16ttyname,(__fd_t __fd),wttyname,(__fd))
#endif /* c16ttyname... */
#if defined(__CRT_HAVE_wttyname) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT(__ATTR_WUNUSED,char32_t *,__NOTHROW_RPC,c32ttyname,(__fd_t __fd),wttyname,(__fd))
#endif /* c32ttyname... */
#if defined(__CRT_HAVE_wttyname_r) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16ttyname_r,(__fd_t __fd, char16_t *__buf, size_t __buflen),wttyname_r,(__fd,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wttyname_r)
/* >> c16ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16ttyname_r,(__fd_t __fd, char16_t *__buf, size_t __buflen),wttyname_r,(__fd,__buf,__buflen))
#endif /* c16ttyname_r... */
#if defined(__CRT_HAVE_wttyname_r) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32ttyname_r,(__fd_t __fd, char32_t *__buf, size_t __buflen),wttyname_r,(__fd,__buf,__buflen))
#endif /* c32ttyname_r... */
#if defined(__CRT_HAVE_wgetlogin) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_WUNUSED,char16_t *,__NOTHROW_NCX,c16getlogin,(void),wgetlogin,())
#elif defined(__CRT_HAVE_DOS$wgetlogin)
__CREDIRECT_DOS(__ATTR_WUNUSED,char16_t *,__NOTHROW_NCX,c16getlogin,(void),wgetlogin,())
#endif /* c16getlogin... */
#if defined(__CRT_HAVE_wgetlogin) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_WUNUSED,char32_t *,__NOTHROW_NCX,c32getlogin,(void),wgetlogin,())
#endif /* c32getlogin... */
#if defined(__CRT_HAVE_wchown) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chown,(char16_t const *__file, __uid_t __owner, __gid_t __group),wchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$wchown)
/* >> c16chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chown,(char16_t const *__file, __uid_t __owner, __gid_t __group),wchown,(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfchownat)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.unistd/wchown.h>
/* >> c16chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16chown)(char16_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchown))((__WCHAR_TYPE__ const *)__file, __owner, __group); }
#else /* LIBC: c16chown */
#include <local/parts.wchar.unistd/c16chown.h>
/* >> c16chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16chown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16chown)(char16_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chown))(__file, __owner, __group); })
#endif /* LIBC: c16chown */
#endif /* c16chown... */
#if defined(__CRT_HAVE_wchown) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chown,(char32_t const *__file, __uid_t __owner, __gid_t __group),wchown,(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfchownat)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.unistd/wchown.h>
/* >> c32chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32chown)(char32_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchown))((__WCHAR_TYPE__ const *)__file, __owner, __group); }
#else /* LIBC: c32chown */
#include <local/parts.wchar.unistd/c32chown.h>
/* >> c32chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32chown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32chown)(char32_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chown))(__file, __owner, __group); })
#endif /* LIBC: c32chown */
#endif /* c32chown... */
#if defined(__CRT_HAVE_wpathconf) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),long int,__NOTHROW_RPC,c16pathconf,(char16_t const *__path, int __name),wpathconf,(__path,__name))
#elif defined(__CRT_HAVE_DOS$wpathconf)
/* >> c16pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),long int,__NOTHROW_RPC,c16pathconf,(char16_t const *__path, int __name),wpathconf,(__path,__name))
#endif /* c16pathconf... */
#if defined(__CRT_HAVE_wpathconf) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),long int,__NOTHROW_RPC,c32pathconf,(char32_t const *__path, int __name),wpathconf,(__path,__name))
#endif /* c32pathconf... */
#if defined(__CRT_HAVE_wlink) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16link(2)
 * Create a hard link from `FROM', leading to `TO' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16link,(char16_t const *__from, char16_t const *__to),wlink,(__from,__to))
#elif defined(__CRT_HAVE_DOS$wlink)
/* >> c16link(2)
 * Create a hard link from `FROM', leading to `TO' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16link,(char16_t const *__from, char16_t const *__to),wlink,(__from,__to))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wlinkat)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.unistd/wlink.h>
/* >> c16link(2)
 * Create a hard link from `FROM', leading to `TO' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL c16link)(char16_t const *__from, char16_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlink))((__WCHAR_TYPE__ const *)__from, (__WCHAR_TYPE__ const *)__to); }
#else /* LIBC: c16link */
#include <local/parts.wchar.unistd/c16link.h>
/* >> c16link(2)
 * Create a hard link from `FROM', leading to `TO' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16link, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL c16link)(char16_t const *__from, char16_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16link))(__from, __to); })
#endif /* LIBC: c16link */
#endif /* c16link... */
#if defined(__CRT_HAVE_wlink) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32link(2)
 * Create a hard link from `FROM', leading to `TO' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32link,(char32_t const *__from, char32_t const *__to),wlink,(__from,__to))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wlinkat)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.unistd/wlink.h>
/* >> c32link(2)
 * Create a hard link from `FROM', leading to `TO' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL c32link)(char32_t const *__from, char32_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlink))((__WCHAR_TYPE__ const *)__from, (__WCHAR_TYPE__ const *)__to); }
#else /* LIBC: c32link */
#include <local/parts.wchar.unistd/c32link.h>
/* >> c32link(2)
 * Create a hard link from `FROM', leading to `TO' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32link, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL c32link)(char32_t const *__from, char32_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32link))(__from, __to); })
#endif /* LIBC: c32link */
#endif /* c32link... */
#if defined(__CRT_HAVE_waccess) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16access,(char16_t const *__file, int __type),waccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$waccess)
/* >> c16access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16access,(char16_t const *__file, int __type),waccess,(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfaccessat)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.unistd/waccess.h>
/* >> c16access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16access)(char16_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(waccess))((__WCHAR_TYPE__ const *)__file, __type); }
#else /* LIBC: c16access */
#include <local/parts.wchar.unistd/c16access.h>
/* >> c16access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16access, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16access)(char16_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16access))(__file, __type); })
#endif /* LIBC: c16access */
#endif /* c16access... */
#if defined(__CRT_HAVE_waccess) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32access,(char32_t const *__file, int __type),waccess,(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfaccessat)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.unistd/waccess.h>
/* >> c32access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32access)(char32_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(waccess))((__WCHAR_TYPE__ const *)__file, __type); }
#else /* LIBC: c32access */
#include <local/parts.wchar.unistd/c32access.h>
/* >> c32access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32access, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32access)(char32_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32access))(__file, __type); })
#endif /* LIBC: c32access */
#endif /* c32access... */
#if defined(__CRT_HAVE_wchdir) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16chdir(2)
 * Change the current working directory to `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chdir,(char16_t const *__path),wchdir,(__path))
#elif defined(__CRT_HAVE_DOS$_wchdir)
/* >> c16chdir(2)
 * Change the current working directory to `PATH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chdir,(char16_t const *__path),_wchdir,(__path))
#endif /* c16chdir... */
#if defined(__CRT_HAVE_wchdir) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32chdir(2)
 * Change the current working directory to `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chdir,(char32_t const *__path),wchdir,(__path))
#endif /* c32chdir... */
#if defined(__CRT_HAVE_wgetcwd) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `c16chdir(2)' */
__CREDIRECT(,char16_t *,__NOTHROW_RPC,c16getcwd,(char16_t *__buf, size_t __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$_wgetcwd)
/* >> c16getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `c16chdir(2)' */
__CREDIRECT_DOS(,char16_t *,__NOTHROW_RPC,c16getcwd,(char16_t *__buf, size_t __bufsize),_wgetcwd,(__buf,__bufsize))
#endif /* c16getcwd... */
#if defined(__CRT_HAVE_wgetcwd) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `c32chdir(2)' */
__CREDIRECT(,char32_t *,__NOTHROW_RPC,c32getcwd,(char32_t *__buf, size_t __bufsize),wgetcwd,(__buf,__bufsize))
#endif /* c32getcwd... */
#if defined(__CRT_HAVE_wunlink) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16unlink,(char16_t const *__file),wunlink,(__file))
#elif defined(__CRT_HAVE_DOS$_wunlink)
/* >> c16unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16unlink,(char16_t const *__file),_wunlink,(__file))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wunlinkat)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.unistd/wunlink.h>
/* >> c16unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16unlink)(char16_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wunlink))((__WCHAR_TYPE__ const *)__file); }
#else /* LIBC: c16unlink */
#include <local/parts.wchar.unistd/c16unlink.h>
/* >> c16unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16unlink, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16unlink)(char16_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16unlink))(__file); })
#endif /* LIBC: c16unlink */
#endif /* c16unlink... */
#if defined(__CRT_HAVE_wunlink) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32unlink,(char32_t const *__file),wunlink,(__file))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wunlinkat)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.unistd/wunlink.h>
/* >> c32unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32unlink)(char32_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wunlink))((__WCHAR_TYPE__ const *)__file); }
#else /* LIBC: c32unlink */
#include <local/parts.wchar.unistd/c32unlink.h>
/* >> c32unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32unlink, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32unlink)(char32_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32unlink))(__file); })
#endif /* LIBC: c32unlink */
#endif /* c32unlink... */
#if defined(__CRT_HAVE_wrmdir) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16rmdir(2)
 * Remove a directory referred to by `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16rmdir,(char16_t const *__path),wrmdir,(__path))
#elif defined(__CRT_HAVE_DOS$_wrmdir)
/* >> c16rmdir(2)
 * Remove a directory referred to by `PATH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16rmdir,(char16_t const *__path),_wrmdir,(__path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wunlinkat)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.unistd/wrmdir.h>
/* >> c16rmdir(2)
 * Remove a directory referred to by `PATH' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16rmdir)(char16_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrmdir))((__WCHAR_TYPE__ const *)__path); }
#else /* LIBC: c16rmdir */
#include <local/parts.wchar.unistd/c16rmdir.h>
/* >> c16rmdir(2)
 * Remove a directory referred to by `PATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rmdir, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16rmdir)(char16_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rmdir))(__path); })
#endif /* LIBC: c16rmdir */
#endif /* c16rmdir... */
#if defined(__CRT_HAVE_wrmdir) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32rmdir(2)
 * Remove a directory referred to by `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32rmdir,(char32_t const *__path),wrmdir,(__path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wunlinkat)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.unistd/wrmdir.h>
/* >> c32rmdir(2)
 * Remove a directory referred to by `PATH' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32rmdir)(char32_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrmdir))((__WCHAR_TYPE__ const *)__path); }
#else /* LIBC: c32rmdir */
#include <local/parts.wchar.unistd/c32rmdir.h>
/* >> c32rmdir(2)
 * Remove a directory referred to by `PATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rmdir, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32rmdir)(char32_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rmdir))(__path); })
#endif /* LIBC: c32rmdir */
#endif /* c32rmdir... */
#ifdef __USE_GNU
#if defined(__CRT_HAVE_weuidaccess) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16euidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16euidaccess,(char16_t const *__file, int __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$weuidaccess)
/* >> c16euidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16euidaccess,(char16_t const *__file, int __type),weuidaccess,(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfaccessat)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.unistd/weuidaccess.h>
/* >> c16euidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16euidaccess)(char16_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))((__WCHAR_TYPE__ const *)__file, __type); }
#else /* LIBC: c16euidaccess */
#include <local/parts.wchar.unistd/c16euidaccess.h>
/* >> c16euidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16euidaccess, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16euidaccess)(char16_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16euidaccess))(__file, __type); })
#endif /* LIBC: c16euidaccess */
#endif /* c16euidaccess... */
#if defined(__CRT_HAVE_weuidaccess) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32euidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32euidaccess,(char32_t const *__file, int __type),weuidaccess,(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfaccessat)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.unistd/weuidaccess.h>
/* >> c32euidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32euidaccess)(char32_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))((__WCHAR_TYPE__ const *)__file, __type); }
#else /* LIBC: c32euidaccess */
#include <local/parts.wchar.unistd/c32euidaccess.h>
/* >> c32euidaccess(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32euidaccess, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32euidaccess)(char32_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32euidaccess))(__file, __type); })
#endif /* LIBC: c32euidaccess */
#endif /* c32euidaccess... */
#if defined(__CRT_HAVE_wget_current_dir_name) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,c16get_current_dir_name,(void),wget_current_dir_name,())
#elif defined(__CRT_HAVE_DOS$wget_current_dir_name)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,c16get_current_dir_name,(void),wget_current_dir_name,())
#elif defined(__CRT_HAVE_wgetcwd) || defined(__CRT_HAVE__wgetcwd)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.unistd/wget_current_dir_name.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED char16_t *__NOTHROW_RPC(__LIBCCALL c16get_current_dir_name)(void) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wget_current_dir_name))(); }
#else /* LIBC: c16get_current_dir_name */
#include <local/parts.wchar.unistd/c16get_current_dir_name.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16get_current_dir_name, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED char16_t *__NOTHROW_RPC(__LIBCCALL c16get_current_dir_name)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16get_current_dir_name))(); })
#endif /* LIBC: c16get_current_dir_name */
#endif /* c16get_current_dir_name... */
#if defined(__CRT_HAVE_wget_current_dir_name) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char32_t *,__NOTHROW_RPC,c32get_current_dir_name,(void),wget_current_dir_name,())
#elif defined(__CRT_HAVE_wgetcwd) || defined(__CRT_HAVE__wgetcwd)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.unistd/wget_current_dir_name.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED char32_t *__NOTHROW_RPC(__LIBCCALL c32get_current_dir_name)(void) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wget_current_dir_name))(); }
#else /* LIBC: c32get_current_dir_name */
#include <local/parts.wchar.unistd/c32get_current_dir_name.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32get_current_dir_name, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED char32_t *__NOTHROW_RPC(__LIBCCALL c32get_current_dir_name)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32get_current_dir_name))(); })
#endif /* LIBC: c32get_current_dir_name */
#endif /* c32get_current_dir_name... */
#endif /* __USE_GNU */
#ifdef __USE_ATFILE
#if defined(__CRT_HAVE_wfaccessat) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16faccessat(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16faccessat,(__fd_t __dfd, char16_t const *__file, int __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#elif defined(__CRT_HAVE_DOS$wfaccessat)
/* >> c16faccessat(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16faccessat,(__fd_t __dfd, char16_t const *__file, int __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#endif /* c16faccessat... */
#if defined(__CRT_HAVE_wfaccessat) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32faccessat(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32faccessat,(__fd_t __dfd, char32_t const *__file, int __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#endif /* c32faccessat... */
#if defined(__CRT_HAVE_wfchownat) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16fchownat,(__fd_t __dfd, char16_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_DOS$wfchownat)
/* >> c16fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16fchownat,(__fd_t __dfd, char16_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#endif /* c16fchownat... */
#if defined(__CRT_HAVE_wfchownat) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32fchownat,(__fd_t __dfd, char32_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#endif /* c32fchownat... */
#if defined(__CRT_HAVE_wlinkat) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__CREDIRECT(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,c16linkat,(__fd_t __fromfd, char16_t const *__from, __fd_t __tofd, char16_t const *__to, __atflag_t __flags),wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#elif defined(__CRT_HAVE_DOS$wlinkat)
/* >> c16linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,c16linkat,(__fd_t __fromfd, char16_t const *__from, __fd_t __tofd, char16_t const *__to, __atflag_t __flags),wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#endif /* c16linkat... */
#if defined(__CRT_HAVE_wlinkat) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__CREDIRECT(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,c32linkat,(__fd_t __fromfd, char32_t const *__from, __fd_t __tofd, char32_t const *__to, __atflag_t __flags),wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#endif /* c32linkat... */
#if defined(__CRT_HAVE_wsymlinkat) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,c16symlinkat,(char16_t const *__link_text, __fd_t __tofd, char16_t const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_DOS$wsymlinkat)
/* >> c16symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,c16symlinkat,(char16_t const *__link_text, __fd_t __tofd, char16_t const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#endif /* c16symlinkat... */
#if defined(__CRT_HAVE_wsymlinkat) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,c32symlinkat,(char32_t const *__link_text, __fd_t __tofd, char32_t const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#endif /* c32symlinkat... */
#if defined(__CRT_HAVE_wreadlinkat) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `c16freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c16readlinkat,(__fd_t __dfd, char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlinkat)
/* >> c16readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `c16freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c16readlinkat,(__fd_t __dfd, char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#endif /* c16readlinkat... */
#if defined(__CRT_HAVE_wreadlinkat) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `c32freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c32readlinkat,(__fd_t __dfd, char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#endif /* c32readlinkat... */
#ifdef __USE_KOS
#if defined(__CRT_HAVE_wfreadlinkat) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c16freadlinkat,(__fd_t __dfd, char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#elif defined(__CRT_HAVE_DOS$wfreadlinkat)
/* >> c16freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c16freadlinkat,(__fd_t __dfd, char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#endif /* c16freadlinkat... */
#if defined(__CRT_HAVE_wfreadlinkat) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c32freadlinkat,(__fd_t __dfd, char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#endif /* c32freadlinkat... */
#endif /* __USE_KOS */
#if defined(__CRT_HAVE_wunlinkat) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16unlinkat,(__fd_t __dfd, char16_t const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#elif defined(__CRT_HAVE_DOS$wunlinkat)
/* >> c16unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16unlinkat,(__fd_t __dfd, char16_t const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#endif /* c16unlinkat... */
#if defined(__CRT_HAVE_wunlinkat) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32unlinkat,(__fd_t __dfd, char32_t const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#endif /* c32unlinkat... */
#endif /* __USE_ATFILE */
#if defined(__CRT_HAVE_wlchown) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16lchown,(char16_t const *__file, __uid_t __owner, __gid_t __group),wlchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$wlchown)
/* >> c16lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16lchown,(char16_t const *__file, __uid_t __owner, __gid_t __group),wlchown,(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfchownat)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.unistd/wlchown.h>
/* >> c16lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16lchown)(char16_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlchown))((__WCHAR_TYPE__ const *)__file, __owner, __group); }
#else /* LIBC: c16lchown */
#include <local/parts.wchar.unistd/c16lchown.h>
/* >> c16lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16lchown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16lchown)(char16_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16lchown))(__file, __owner, __group); })
#endif /* LIBC: c16lchown */
#endif /* c16lchown... */
#if defined(__CRT_HAVE_wlchown) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32lchown,(char32_t const *__file, __uid_t __owner, __gid_t __group),wlchown,(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wfchownat)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.unistd/wlchown.h>
/* >> c32lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32lchown)(char32_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlchown))((__WCHAR_TYPE__ const *)__file, __owner, __group); }
#else /* LIBC: c32lchown */
#include <local/parts.wchar.unistd/c32lchown.h>
/* >> c32lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32lchown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32lchown)(char32_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32lchown))(__file, __owner, __group); })
#endif /* LIBC: c32lchown */
#endif /* c32lchown... */
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
#if defined(__CRT_HAVE_wtruncate64) && defined(__USE_FILE_OFFSET64) && __SIZEOF_WCHAR_T__ == 2
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate64) && defined(__USE_FILE_OFFSET64)
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) && !defined(__USE_FILE_OFFSET64) && __SIZEOF_WCHAR_T__ == 2
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate) && !defined(__USE_FILE_OFFSET64)
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate)
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate64) || defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE__open)) && (defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64)))
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.unistd/wtruncate.h>
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL c16truncate)(char16_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate))((__WCHAR_TYPE__ const *)__file, __length); }
#else /* LIBC: c16truncate */
#include <local/parts.wchar.unistd/c16truncate.h>
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16truncate, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL c16truncate)(char16_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16truncate))(__file, __length); })
#endif /* LIBC: c16truncate */
#endif /* c16truncate... */
#if defined(__CRT_HAVE_wtruncate64) && defined(__USE_FILE_OFFSET64) && __SIZEOF_WCHAR_T__ == 4
/* >> c32truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate,(char32_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) && !defined(__USE_FILE_OFFSET64) && __SIZEOF_WCHAR_T__ == 4
/* >> c32truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate,(char32_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate,(char32_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate64) || defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE__open)) && (defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64)))
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.unistd/wtruncate.h>
/* >> c32truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL c32truncate)(char32_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate))((__WCHAR_TYPE__ const *)__file, __length); }
#else /* LIBC: c32truncate */
#include <local/parts.wchar.unistd/c32truncate.h>
/* >> c32truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32truncate, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL c32truncate)(char32_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32truncate))(__file, __length); })
#endif /* LIBC: c32truncate */
#endif /* c32truncate... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_wtruncate64) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate64,(char16_t const *__file, __PIO_OFFSET64 __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate64)
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate64,(char16_t const *__file, __PIO_OFFSET64 __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE__open)) && (defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64)))
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.unistd/wtruncate64.h>
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL c16truncate64)(char16_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate64))((__WCHAR_TYPE__ const *)__file, __length); }
#else /* LIBC: c16truncate64 */
#include <local/parts.wchar.unistd/c16truncate64.h>
/* >> c16truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16truncate64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL c16truncate64)(char16_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16truncate64))(__file, __length); })
#endif /* LIBC: c16truncate64 */
#endif /* c16truncate64... */
#if defined(__CRT_HAVE_wtruncate64) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate64,(char32_t const *__file, __PIO_OFFSET64 __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE__open)) && (defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64)))
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.unistd/wtruncate64.h>
/* >> c32truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL c32truncate64)(char32_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate64))((__WCHAR_TYPE__ const *)__file, __length); }
#else /* LIBC: c32truncate64 */
#include <local/parts.wchar.unistd/c32truncate64.h>
/* >> c32truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32truncate64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL c32truncate64)(char32_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32truncate64))(__file, __length); })
#endif /* LIBC: c32truncate64 */
#endif /* c32truncate64... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_wsymlink) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `c16symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16symlink,(char16_t const *__link_text, char16_t const *__target_path),wsymlink,(__link_text,__target_path))
#elif defined(__CRT_HAVE_DOS$wsymlink)
/* >> c16symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `c16symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16symlink,(char16_t const *__link_text, char16_t const *__target_path),wsymlink,(__link_text,__target_path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wsymlinkat)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.unistd/wsymlink.h>
/* >> c16symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `c16symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL c16symlink)(char16_t const *__link_text, char16_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsymlink))((__WCHAR_TYPE__ const *)__link_text, (__WCHAR_TYPE__ const *)__target_path); }
#else /* LIBC: c16symlink */
#include <local/parts.wchar.unistd/c16symlink.h>
/* >> c16symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `c16symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16symlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL c16symlink)(char16_t const *__link_text, char16_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16symlink))(__link_text, __target_path); })
#endif /* LIBC: c16symlink */
#endif /* c16symlink... */
#if defined(__CRT_HAVE_wsymlink) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `c32symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32symlink,(char32_t const *__link_text, char32_t const *__target_path),wsymlink,(__link_text,__target_path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wsymlinkat)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.unistd/wsymlink.h>
/* >> c32symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `c32symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL c32symlink)(char32_t const *__link_text, char32_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsymlink))((__WCHAR_TYPE__ const *)__link_text, (__WCHAR_TYPE__ const *)__target_path); }
#else /* LIBC: c32symlink */
#include <local/parts.wchar.unistd/c32symlink.h>
/* >> c32symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `c32symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32symlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL c32symlink)(char32_t const *__link_text, char32_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32symlink))(__link_text, __target_path); })
#endif /* LIBC: c32symlink */
#endif /* c32symlink... */
#if defined(__CRT_HAVE_wreadlink) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `c16readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `c16freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,c16readlink,(char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen),wreadlink,(__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlink)
/* >> c16readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `c16readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `c16freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,c16readlink,(char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen),wreadlink,(__path,__buf,__buflen))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wreadlinkat)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.unistd/wreadlink.h>
/* >> c16readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `c16readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `c16freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBCCALL c16readlink)(char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wreadlink))((__WCHAR_TYPE__ const *)__path, (__WCHAR_TYPE__ *)__buf, __buflen); }
#else /* LIBC: c16readlink */
#include <local/parts.wchar.unistd/c16readlink.h>
/* >> c16readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `c16readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `c16freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16readlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBCCALL c16readlink)(char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16readlink))(__path, __buf, __buflen); })
#endif /* LIBC: c16readlink */
#endif /* c16readlink... */
#if defined(__CRT_HAVE_wreadlink) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `c32readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `c32freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,c32readlink,(char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen),wreadlink,(__path,__buf,__buflen))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wreadlinkat)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.unistd/wreadlink.h>
/* >> c32readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `c32readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `c32freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBCCALL c32readlink)(char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wreadlink))((__WCHAR_TYPE__ const *)__path, (__WCHAR_TYPE__ *)__buf, __buflen); }
#else /* LIBC: c32readlink */
#include <local/parts.wchar.unistd/c32readlink.h>
/* >> c32readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `c32readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `c32freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32readlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBCCALL c32readlink)(char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32readlink))(__path, __buf, __buflen); })
#endif /* LIBC: c32readlink */
#endif /* c32readlink... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */
#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
#if defined(__CRT_HAVE_wgetlogin_r) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16getlogin_r,(char16_t *__name, size_t __name_len),wgetlogin_r,(__name,__name_len))
#elif defined(__CRT_HAVE_DOS$wgetlogin_r)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16getlogin_r,(char16_t *__name, size_t __name_len),wgetlogin_r,(__name,__name_len))
#endif /* c16getlogin_r... */
#if defined(__CRT_HAVE_wgetlogin_r) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32getlogin_r,(char32_t *__name, size_t __name_len),wgetlogin_r,(__name,__name_len))
#endif /* c32getlogin_r... */
#endif /* __USE_REENTRANT || __USE_POSIX199506 */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_wgethostname) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16gethostname(3)
 * Return the name assigned to the hosting machine, as set by `c16sethostname(2)' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16gethostname,(char16_t *__name, size_t __buflen),wgethostname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$wgethostname)
/* >> c16gethostname(3)
 * Return the name assigned to the hosting machine, as set by `c16sethostname(2)' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16gethostname,(char16_t *__name, size_t __buflen),wgethostname,(__name,__buflen))
#endif /* c16gethostname... */
#if defined(__CRT_HAVE_wgethostname) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32gethostname(3)
 * Return the name assigned to the hosting machine, as set by `c32sethostname(2)' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32gethostname,(char32_t *__name, size_t __buflen),wgethostname,(__name,__buflen))
#endif /* c32gethostname... */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */
#ifdef __USE_MISC
#if defined(__CRT_HAVE_wsetlogin) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16setlogin,(char16_t const *__name),wsetlogin,(__name))
#elif defined(__CRT_HAVE_DOS$wsetlogin)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16setlogin,(char16_t const *__name),wsetlogin,(__name))
#endif /* c16setlogin... */
#if defined(__CRT_HAVE_wsetlogin) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32setlogin,(char32_t const *__name),wsetlogin,(__name))
#endif /* c32setlogin... */
#if defined(__CRT_HAVE_wsethostname) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16sethostname(2)
 * Set the name of the hosting machine */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16sethostname,(char16_t const *__name, size_t __len),wsethostname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$wsethostname)
/* >> c16sethostname(2)
 * Set the name of the hosting machine */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16sethostname,(char16_t const *__name, size_t __len),wsethostname,(__name,__len))
#endif /* c16sethostname... */
#if defined(__CRT_HAVE_wsethostname) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32sethostname(2)
 * Set the name of the hosting machine */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32sethostname,(char32_t const *__name, size_t __len),wsethostname,(__name,__len))
#endif /* c32sethostname... */
#if defined(__CRT_HAVE_wgetdomainname) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `c16setdomainname(2)' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16getdomainname,(char16_t *__name, size_t __buflen),wgetdomainname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$wgetdomainname)
/* >> c16getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `c16setdomainname(2)' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16getdomainname,(char16_t *__name, size_t __buflen),wgetdomainname,(__name,__buflen))
#endif /* c16getdomainname... */
#if defined(__CRT_HAVE_wgetdomainname) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `c32setdomainname(2)' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32getdomainname,(char32_t *__name, size_t __buflen),wgetdomainname,(__name,__buflen))
#endif /* c32getdomainname... */
#if defined(__CRT_HAVE_wsetdomainname) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16setdomainname(2)
 * Set the name of the hosting machine's domain */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16setdomainname,(char16_t const *__name, size_t __len),wsetdomainname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$wsetdomainname)
/* >> c16setdomainname(2)
 * Set the name of the hosting machine's domain */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16setdomainname,(char16_t const *__name, size_t __len),wsetdomainname,(__name,__len))
#endif /* c16setdomainname... */
#if defined(__CRT_HAVE_wsetdomainname) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32setdomainname(2)
 * Set the name of the hosting machine's domain */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32setdomainname,(char32_t const *__name, size_t __len),wsetdomainname,(__name,__len))
#endif /* c32setdomainname... */
#endif /* __USE_MISC */
#if defined(__USE_MISC) || \
   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#if defined(__CRT_HAVE_wchroot) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chroot,(char16_t const *__restrict __path),wchroot,(__path))
#elif defined(__CRT_HAVE_DOS$wchroot)
/* >> c16chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chroot,(char16_t const *__restrict __path),wchroot,(__path))
#endif /* c16chroot... */
#if defined(__CRT_HAVE_wchroot) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chroot,(char32_t const *__restrict __path),wchroot,(__path))
#endif /* c32chroot... */
#endif /* ... */

#if defined(_ALL_SOURCE) || \
   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#if defined(__CRT_HAVE_wctermid) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(,char16_t *,__NOTHROW_NCX,c16ctermid,(char16_t *__s),wctermid,(__s))
#elif defined(__CRT_HAVE_DOS$wctermid)
__CREDIRECT_DOS(,char16_t *,__NOTHROW_NCX,c16ctermid,(char16_t *__s),wctermid,(__s))
#endif /* c16ctermid... */
#if defined(__CRT_HAVE_wctermid) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(,char32_t *,__NOTHROW_NCX,c32ctermid,(char32_t *__s),wctermid,(__s))
#endif /* c32ctermid... */
#endif /* _ALL_SOURCE || (__USE_XOPEN && !__USE_XOPEN2K) */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_UCHAR_UNISTD_H */
