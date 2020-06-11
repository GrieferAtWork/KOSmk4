/* HASH CRC-32:0xd54a9061 */
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

#if defined(__CRT_HAVE_wttyname) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,__LIBDCALL,c16ttyname,(__fd_t __fd),wttyname,(__fd))
#elif defined(__CRT_HAVE_DOS$wttyname) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_DOS(__ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,c16ttyname,(__fd_t __fd),wttyname,(__fd))
#elif defined(__CRT_HAVE_DOS$DOS$wttyname)
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_DOS(__ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,c16ttyname,(__fd_t __fd),DOS$wttyname,(__fd))
#endif /* ... */
#if defined(__CRT_HAVE_wttyname) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED,char32_t *,__NOTHROW_RPC,__LIBKCALL,c32ttyname,(__fd_t __fd),wttyname,(__fd))
#elif defined(__CRT_HAVE_DOS$wttyname) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_KOS(__ATTR_WUNUSED,char32_t *,__NOTHROW_RPC,c32ttyname,(__fd_t __fd),wttyname,(__fd))
#elif defined(__CRT_HAVE_DOS$KOS$wttyname)
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_KOS(__ATTR_WUNUSED,char32_t *,__NOTHROW_RPC,c32ttyname,(__fd_t __fd),KOS$wttyname,(__fd))
#endif /* ... */
#if defined(__CRT_HAVE_wttyname_r) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBDCALL,c16ttyname_r,(__fd_t __fd, char16_t *__buf, size_t __buflen),wttyname_r,(__fd,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wttyname_r) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16ttyname_r,(__fd_t __fd, char16_t *__buf, size_t __buflen),wttyname_r,(__fd,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$DOS$wttyname_r)
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16ttyname_r,(__fd_t __fd, char16_t *__buf, size_t __buflen),DOS$wttyname_r,(__fd,__buf,__buflen))
#endif /* ... */
#if defined(__CRT_HAVE_wttyname_r) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBKCALL,c32ttyname_r,(__fd_t __fd, char32_t *__buf, size_t __buflen),wttyname_r,(__fd,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wttyname_r) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32ttyname_r,(__fd_t __fd, char32_t *__buf, size_t __buflen),wttyname_r,(__fd,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$KOS$wttyname_r)
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32ttyname_r,(__fd_t __fd, char32_t *__buf, size_t __buflen),KOS$wttyname_r,(__fd,__buf,__buflen))
#endif /* ... */
#if defined(__CRT_HAVE_wgetlogin) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED,char16_t *,__NOTHROW_NCX,__LIBDCALL,c16getlogin,(void),wgetlogin,())
#elif defined(__CRT_HAVE_DOS$wgetlogin) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_WUNUSED,char16_t *,__NOTHROW_NCX,c16getlogin,(void),wgetlogin,())
#elif defined(__CRT_HAVE_DOS$DOS$wgetlogin)
__CREDIRECT_DOS(__ATTR_WUNUSED,char16_t *,__NOTHROW_NCX,c16getlogin,(void),DOS$wgetlogin,())
#endif /* ... */
#if defined(__CRT_HAVE_wgetlogin) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED,char32_t *,__NOTHROW_NCX,__LIBKCALL,c32getlogin,(void),wgetlogin,())
#elif defined(__CRT_HAVE_DOS$wgetlogin) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_WUNUSED,char32_t *,__NOTHROW_NCX,c32getlogin,(void),wgetlogin,())
#elif defined(__CRT_HAVE_DOS$KOS$wgetlogin)
__CREDIRECT_KOS(__ATTR_WUNUSED,char32_t *,__NOTHROW_NCX,c32getlogin,(void),KOS$wgetlogin,())
#endif /* ... */
#if defined(__CRT_HAVE_wchown) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBDCALL,c16chown,(char16_t const *__file, __uid_t __owner, __gid_t __group),wchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$wchown) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chown,(char16_t const *__file, __uid_t __owner, __gid_t __group),wchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$DOS$wchown)
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chown,(char16_t const *__file, __uid_t __owner, __gid_t __group),DOS$wchown,(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_fchownat) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.unistd/wchown.h>
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16chown)(char16_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchown))((__WCHAR_TYPE__ const *)__file, __owner, __group); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_fchownat)
#include <local/parts.wchar.unistd/c16chown.h>
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16chown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16chown)(char16_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chown))(__file, __owner, __group); })
#endif /* ... */
#if defined(__CRT_HAVE_wchown) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBKCALL,c32chown,(char32_t const *__file, __uid_t __owner, __gid_t __group),wchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$wchown) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chown,(char32_t const *__file, __uid_t __owner, __gid_t __group),wchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$KOS$wchown)
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chown,(char32_t const *__file, __uid_t __owner, __gid_t __group),KOS$wchown,(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_fchownat) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.unistd/wchown.h>
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32chown)(char32_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchown))((__WCHAR_TYPE__ const *)__file, __owner, __group); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_fchownat)
#include <local/parts.wchar.unistd/c32chown.h>
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32chown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32chown)(char32_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chown))(__file, __owner, __group); })
#endif /* ... */
#if defined(__CRT_HAVE_wpathconf) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),long int,__NOTHROW_RPC,__LIBDCALL,c16pathconf,(char16_t const *__path, int __name),wpathconf,(__path,__name))
#elif defined(__CRT_HAVE_DOS$wpathconf) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),long int,__NOTHROW_RPC,c16pathconf,(char16_t const *__path, int __name),wpathconf,(__path,__name))
#elif defined(__CRT_HAVE_DOS$DOS$wpathconf)
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),long int,__NOTHROW_RPC,c16pathconf,(char16_t const *__path, int __name),DOS$wpathconf,(__path,__name))
#endif /* ... */
#if defined(__CRT_HAVE_wpathconf) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),long int,__NOTHROW_RPC,__LIBKCALL,c32pathconf,(char32_t const *__path, int __name),wpathconf,(__path,__name))
#elif defined(__CRT_HAVE_DOS$wpathconf) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),long int,__NOTHROW_RPC,c32pathconf,(char32_t const *__path, int __name),wpathconf,(__path,__name))
#elif defined(__CRT_HAVE_DOS$KOS$wpathconf)
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),long int,__NOTHROW_RPC,c32pathconf,(char32_t const *__path, int __name),KOS$wpathconf,(__path,__name))
#endif /* ... */
#if defined(__CRT_HAVE_wlink) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__LIBDCALL,c16link,(char16_t const *__from, char16_t const *__to),wlink,(__from,__to))
#elif defined(__CRT_HAVE_DOS$wlink) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16link,(char16_t const *__from, char16_t const *__to),wlink,(__from,__to))
#elif defined(__CRT_HAVE_DOS$DOS$wlink)
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16link,(char16_t const *__from, char16_t const *__to),DOS$wlink,(__from,__to))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_linkat) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.unistd/wlink.h>
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBDCALL c16link)(char16_t const *__from, char16_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlink))((__WCHAR_TYPE__ const *)__from, (__WCHAR_TYPE__ const *)__to); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_linkat)
#include <local/parts.wchar.unistd/c16link.h>
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16link, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBDCALL c16link)(char16_t const *__from, char16_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16link))(__from, __to); })
#endif /* ... */
#if defined(__CRT_HAVE_wlink) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__LIBKCALL,c32link,(char32_t const *__from, char32_t const *__to),wlink,(__from,__to))
#elif defined(__CRT_HAVE_DOS$wlink) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32link,(char32_t const *__from, char32_t const *__to),wlink,(__from,__to))
#elif defined(__CRT_HAVE_DOS$KOS$wlink)
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32link,(char32_t const *__from, char32_t const *__to),KOS$wlink,(__from,__to))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_linkat) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.unistd/wlink.h>
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBKCALL c32link)(char32_t const *__from, char32_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlink))((__WCHAR_TYPE__ const *)__from, (__WCHAR_TYPE__ const *)__to); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_linkat)
#include <local/parts.wchar.unistd/c32link.h>
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32link, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBKCALL c32link)(char32_t const *__from, char32_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32link))(__from, __to); })
#endif /* ... */
#if defined(__CRT_HAVE_waccess) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBDCALL,c16access,(char16_t const *__file, int __type),waccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$waccess) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16access,(char16_t const *__file, int __type),waccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$DOS$waccess)
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16access,(char16_t const *__file, int __type),DOS$waccess,(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_faccessat) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.unistd/waccess.h>
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16access)(char16_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(waccess))((__WCHAR_TYPE__ const *)__file, __type); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_faccessat)
#include <local/parts.wchar.unistd/c16access.h>
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16access, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16access)(char16_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16access))(__file, __type); })
#endif /* ... */
#if defined(__CRT_HAVE_waccess) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBKCALL,c32access,(char32_t const *__file, int __type),waccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$waccess) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32access,(char32_t const *__file, int __type),waccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$KOS$waccess)
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32access,(char32_t const *__file, int __type),KOS$waccess,(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_faccessat) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.unistd/waccess.h>
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32access)(char32_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(waccess))((__WCHAR_TYPE__ const *)__file, __type); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_faccessat)
#include <local/parts.wchar.unistd/c32access.h>
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32access, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32access)(char32_t const *__file, int __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32access))(__file, __type); })
#endif /* ... */
#if defined(__CRT_HAVE_wchdir) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBDCALL,c16chdir,(char16_t const *__path),wchdir,(__path))
#elif defined(__CRT_HAVE_DOS$_wchdir) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chdir,(char16_t const *__path),_wchdir,(__path))
#elif defined(__CRT_HAVE_DOS$DOS$_wchdir)
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chdir,(char16_t const *__path),DOS$_wchdir,(__path))
#endif /* ... */
#if defined(__CRT_HAVE_wchdir) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBKCALL,c32chdir,(char32_t const *__path),wchdir,(__path))
#elif defined(__CRT_HAVE_DOS$wchdir) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chdir,(char32_t const *__path),wchdir,(__path))
#elif defined(__CRT_HAVE_DOS$KOS$wchdir)
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chdir,(char32_t const *__path),KOS$wchdir,(__path))
#endif /* ... */
#if defined(__CRT_HAVE_wgetcwd) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__COMPILER_REDIRECT(__LIBC,,char16_t *,__NOTHROW_RPC,__LIBDCALL,c16getcwd,(char16_t *__buf, size_t __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$_wgetcwd) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT_DOS(,char16_t *,__NOTHROW_RPC,c16getcwd,(char16_t *__buf, size_t __bufsize),_wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$DOS$_wgetcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT_DOS(,char16_t *,__NOTHROW_RPC,c16getcwd,(char16_t *__buf, size_t __bufsize),DOS$_wgetcwd,(__buf,__bufsize))
#endif /* ... */
#if defined(__CRT_HAVE_wgetcwd) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__COMPILER_REDIRECT(__LIBC,,char32_t *,__NOTHROW_RPC,__LIBKCALL,c32getcwd,(char32_t *__buf, size_t __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$wgetcwd) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT_KOS(,char32_t *,__NOTHROW_RPC,c32getcwd,(char32_t *__buf, size_t __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$KOS$wgetcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT_KOS(,char32_t *,__NOTHROW_RPC,c32getcwd,(char32_t *__buf, size_t __bufsize),KOS$wgetcwd,(__buf,__bufsize))
#endif /* ... */
#if defined(__CRT_HAVE_wunlink) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBDCALL,c16unlink,(char16_t const *__file),wunlink,(__file))
#elif defined(__CRT_HAVE_DOS$_wunlink) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16unlink,(char16_t const *__file),_wunlink,(__file))
#elif defined(__CRT_HAVE_DOS$DOS$_wunlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16unlink,(char16_t const *__file),DOS$_wunlink,(__file))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.unistd/wunlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16unlink)(char16_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wunlink))((__WCHAR_TYPE__ const *)__file); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/parts.wchar.unistd/c16unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16unlink, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16unlink)(char16_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16unlink))(__file); })
#endif /* ... */
#if defined(__CRT_HAVE_wunlink) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBKCALL,c32unlink,(char32_t const *__file),wunlink,(__file))
#elif defined(__CRT_HAVE_DOS$wunlink) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32unlink,(char32_t const *__file),wunlink,(__file))
#elif defined(__CRT_HAVE_DOS$KOS$wunlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32unlink,(char32_t const *__file),KOS$wunlink,(__file))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.unistd/wunlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32unlink)(char32_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wunlink))((__WCHAR_TYPE__ const *)__file); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/parts.wchar.unistd/c32unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32unlink, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32unlink)(char32_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32unlink))(__file); })
#endif /* ... */
#if defined(__CRT_HAVE_wrmdir) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBDCALL,c16rmdir,(char16_t const *__path),wrmdir,(__path))
#elif defined(__CRT_HAVE_DOS$_wrmdir) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16rmdir,(char16_t const *__path),_wrmdir,(__path))
#elif defined(__CRT_HAVE_DOS$DOS$_wrmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16rmdir,(char16_t const *__path),DOS$_wrmdir,(__path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.unistd/wrmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16rmdir)(char16_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrmdir))((__WCHAR_TYPE__ const *)__path); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/parts.wchar.unistd/c16rmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rmdir, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16rmdir)(char16_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rmdir))(__path); })
#endif /* ... */
#if defined(__CRT_HAVE_wrmdir) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBKCALL,c32rmdir,(char32_t const *__path),wrmdir,(__path))
#elif defined(__CRT_HAVE_DOS$wrmdir) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32rmdir,(char32_t const *__path),wrmdir,(__path))
#elif defined(__CRT_HAVE_DOS$KOS$wrmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32rmdir,(char32_t const *__path),KOS$wrmdir,(__path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.unistd/wrmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32rmdir)(char32_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrmdir))((__WCHAR_TYPE__ const *)__path); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/parts.wchar.unistd/c32rmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rmdir, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32rmdir)(char32_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rmdir))(__path); })
#endif /* ... */
#ifdef __USE_GNU
#if defined(__CRT_HAVE_weuidaccess) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBDCALL,c16euidaccess,(char16_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$weuidaccess) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16euidaccess,(char16_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$DOS$weuidaccess)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16euidaccess,(char16_t const *__file, __STDC_INT_AS_UINT_T __type),DOS$weuidaccess,(__file,__type))
#else /* ... */
#include <asm/fcntl.h>
#if defined(__CRT_AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.unistd/weuidaccess.h>
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16euidaccess)(char16_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))((__WCHAR_TYPE__ const *)__file, __type); }
#else /* __CRT_AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat && (__SIZEOF_WCHAR_T__ == 2) */
#include <asm/fcntl.h>
#if defined(__CRT_AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat)
#include <local/parts.wchar.unistd/c16euidaccess.h>
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16euidaccess, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16euidaccess)(char16_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16euidaccess))(__file, __type); })
#endif /* __CRT_AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat */
#endif /* !__CRT_AT_FDCWD || !__AT_EACCESS || !__CRT_HAVE_faccessat || !(__SIZEOF_WCHAR_T__ == 2) */
#endif /* !... */
#if defined(__CRT_HAVE_weuidaccess) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBKCALL,c32euidaccess,(char32_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$weuidaccess) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32euidaccess,(char32_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$KOS$weuidaccess)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32euidaccess,(char32_t const *__file, __STDC_INT_AS_UINT_T __type),KOS$weuidaccess,(__file,__type))
#else /* ... */
#include <asm/fcntl.h>
#if defined(__CRT_AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.unistd/weuidaccess.h>
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32euidaccess)(char32_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))((__WCHAR_TYPE__ const *)__file, __type); }
#else /* __CRT_AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat && (__SIZEOF_WCHAR_T__ == 4) */
#include <asm/fcntl.h>
#if defined(__CRT_AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat)
#include <local/parts.wchar.unistd/c32euidaccess.h>
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32euidaccess, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32euidaccess)(char32_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32euidaccess))(__file, __type); })
#endif /* __CRT_AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat */
#endif /* !__CRT_AT_FDCWD || !__AT_EACCESS || !__CRT_HAVE_faccessat || !(__SIZEOF_WCHAR_T__ == 4) */
#endif /* !... */
#if defined(__CRT_HAVE_weuidaccess) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBDCALL,c16eaccess,(char16_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$weuidaccess) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16eaccess,(char16_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$DOS$weuidaccess)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16eaccess,(char16_t const *__file, __STDC_INT_AS_UINT_T __type),DOS$weuidaccess,(__file,__type))
#else /* ... */
#include <asm/fcntl.h>
#if defined(__CRT_AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.unistd/weuidaccess.h>
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16eaccess)(char16_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))((__WCHAR_TYPE__ const *)__file, __type); }
#else /* __CRT_AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat && (__SIZEOF_WCHAR_T__ == 2) */
#include <asm/fcntl.h>
#if defined(__CRT_AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat)
#include <local/parts.wchar.unistd/c16euidaccess.h>
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16eaccess)(char16_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16euidaccess))(__file, __type); }
#endif /* __CRT_AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat */
#endif /* !__CRT_AT_FDCWD || !__AT_EACCESS || !__CRT_HAVE_faccessat || !(__SIZEOF_WCHAR_T__ == 2) */
#endif /* !... */
#if defined(__CRT_HAVE_weuidaccess) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__COMPILER_REDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBKCALL,c32eaccess,(char32_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$weuidaccess) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32eaccess,(char32_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$KOS$weuidaccess)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32eaccess,(char32_t const *__file, __STDC_INT_AS_UINT_T __type),KOS$weuidaccess,(__file,__type))
#else /* ... */
#include <asm/fcntl.h>
#if defined(__CRT_AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.unistd/weuidaccess.h>
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32eaccess)(char32_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))((__WCHAR_TYPE__ const *)__file, __type); }
#else /* __CRT_AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat && (__SIZEOF_WCHAR_T__ == 4) */
#include <asm/fcntl.h>
#if defined(__CRT_AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat)
#include <local/parts.wchar.unistd/c32euidaccess.h>
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32eaccess)(char32_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32euidaccess))(__file, __type); }
#endif /* __CRT_AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat */
#endif /* !__CRT_AT_FDCWD || !__AT_EACCESS || !__CRT_HAVE_faccessat || !(__SIZEOF_WCHAR_T__ == 4) */
#endif /* !... */
#if defined(__CRT_HAVE_wget_current_dir_name) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_MALLOC __ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,__LIBDCALL,c16get_current_dir_name,(void),wget_current_dir_name,())
#elif defined(__CRT_HAVE_DOS$wget_current_dir_name) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,c16get_current_dir_name,(void),wget_current_dir_name,())
#elif defined(__CRT_HAVE_DOS$DOS$wget_current_dir_name)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,c16get_current_dir_name,(void),DOS$wget_current_dir_name,())
#elif (defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.unistd/wget_current_dir_name.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED char16_t *__NOTHROW_RPC(__LIBDCALL c16get_current_dir_name)(void) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wget_current_dir_name))(); }
#elif defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
#include <local/parts.wchar.unistd/c16get_current_dir_name.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16get_current_dir_name, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED char16_t *__NOTHROW_RPC(__LIBDCALL c16get_current_dir_name)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16get_current_dir_name))(); })
#endif /* ... */
#if defined(__CRT_HAVE_wget_current_dir_name) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_MALLOC __ATTR_WUNUSED,char32_t *,__NOTHROW_RPC,__LIBKCALL,c32get_current_dir_name,(void),wget_current_dir_name,())
#elif defined(__CRT_HAVE_DOS$wget_current_dir_name) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED,char32_t *,__NOTHROW_RPC,c32get_current_dir_name,(void),wget_current_dir_name,())
#elif defined(__CRT_HAVE_DOS$KOS$wget_current_dir_name)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED,char32_t *,__NOTHROW_RPC,c32get_current_dir_name,(void),KOS$wget_current_dir_name,())
#elif (defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.unistd/wget_current_dir_name.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED char32_t *__NOTHROW_RPC(__LIBKCALL c32get_current_dir_name)(void) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wget_current_dir_name))(); }
#elif defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
#include <local/parts.wchar.unistd/c32get_current_dir_name.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32get_current_dir_name, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED char32_t *__NOTHROW_RPC(__LIBKCALL c32get_current_dir_name)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32get_current_dir_name))(); })
#endif /* ... */
#endif /* __USE_GNU */
#ifdef __USE_ATFILE
#if defined(__CRT_HAVE_wfaccessat) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBDCALL,c16faccessat,(__fd_t __dfd, char16_t const *__file, int __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#elif defined(__CRT_HAVE_DOS$wfaccessat) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16faccessat,(__fd_t __dfd, char16_t const *__file, int __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#elif defined(__CRT_HAVE_DOS$DOS$wfaccessat)
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16faccessat,(__fd_t __dfd, char16_t const *__file, int __type, __atflag_t __flags),DOS$wfaccessat,(__dfd,__file,__type,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wfaccessat) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBKCALL,c32faccessat,(__fd_t __dfd, char32_t const *__file, int __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#elif defined(__CRT_HAVE_DOS$wfaccessat) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32faccessat,(__fd_t __dfd, char32_t const *__file, int __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#elif defined(__CRT_HAVE_DOS$KOS$wfaccessat)
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32faccessat,(__fd_t __dfd, char32_t const *__file, int __type, __atflag_t __flags),KOS$wfaccessat,(__dfd,__file,__type,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wfchownat) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBDCALL,c16fchownat,(__fd_t __dfd, char16_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_DOS$wfchownat) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16fchownat,(__fd_t __dfd, char16_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_DOS$DOS$wfchownat)
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16fchownat,(__fd_t __dfd, char16_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),DOS$wfchownat,(__dfd,__file,__owner,__group,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wfchownat) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBKCALL,c32fchownat,(__fd_t __dfd, char32_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_DOS$wfchownat) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32fchownat,(__fd_t __dfd, char32_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_DOS$KOS$wfchownat)
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32fchownat,(__fd_t __dfd, char32_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),KOS$wfchownat,(__dfd,__file,__owner,__group,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wlinkat) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,__LIBDCALL,c16linkat,(__fd_t __fromfd, char16_t const *__from, __fd_t __tofd, char16_t const *__to, __atflag_t __flags),wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#elif defined(__CRT_HAVE_DOS$wlinkat) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,c16linkat,(__fd_t __fromfd, char16_t const *__from, __fd_t __tofd, char16_t const *__to, __atflag_t __flags),wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#elif defined(__CRT_HAVE_DOS$DOS$wlinkat)
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,c16linkat,(__fd_t __fromfd, char16_t const *__from, __fd_t __tofd, char16_t const *__to, __atflag_t __flags),DOS$wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wlinkat) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,__LIBKCALL,c32linkat,(__fd_t __fromfd, char32_t const *__from, __fd_t __tofd, char32_t const *__to, __atflag_t __flags),wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#elif defined(__CRT_HAVE_DOS$wlinkat) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__CREDIRECT_KOS(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,c32linkat,(__fd_t __fromfd, char32_t const *__from, __fd_t __tofd, char32_t const *__to, __atflag_t __flags),wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#elif defined(__CRT_HAVE_DOS$KOS$wlinkat)
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__CREDIRECT_KOS(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,c32linkat,(__fd_t __fromfd, char32_t const *__from, __fd_t __tofd, char32_t const *__to, __atflag_t __flags),KOS$wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wsymlinkat) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__LIBDCALL,c16symlinkat,(char16_t const *__link_text, __fd_t __tofd, char16_t const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_DOS$wsymlinkat) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,c16symlinkat,(char16_t const *__link_text, __fd_t __tofd, char16_t const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_DOS$DOS$wsymlinkat)
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,c16symlinkat,(char16_t const *__link_text, __fd_t __tofd, char16_t const *__target_path),DOS$wsymlinkat,(__link_text,__tofd,__target_path))
#endif /* ... */
#if defined(__CRT_HAVE_wsymlinkat) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__LIBKCALL,c32symlinkat,(char32_t const *__link_text, __fd_t __tofd, char32_t const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_DOS$wsymlinkat) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,c32symlinkat,(char32_t const *__link_text, __fd_t __tofd, char32_t const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_DOS$KOS$wsymlinkat)
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,c32symlinkat,(char32_t const *__link_text, __fd_t __tofd, char32_t const *__target_path),KOS$wsymlinkat,(__link_text,__tofd,__target_path))
#endif /* ... */
#if defined(__CRT_HAVE_wreadlinkat) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,__LIBDCALL,c16readlinkat,(__fd_t __dfd, char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlinkat) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c16readlinkat,(__fd_t __dfd, char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$DOS$wreadlinkat)
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c16readlinkat,(__fd_t __dfd, char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen),DOS$wreadlinkat,(__dfd,__path,__buf,__buflen))
#endif /* ... */
#if defined(__CRT_HAVE_wreadlinkat) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,__LIBKCALL,c32readlinkat,(__fd_t __dfd, char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlinkat) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c32readlinkat,(__fd_t __dfd, char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$KOS$wreadlinkat)
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c32readlinkat,(__fd_t __dfd, char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen),KOS$wreadlinkat,(__dfd,__path,__buf,__buflen))
#endif /* ... */
#ifdef __USE_KOS
#if defined(__CRT_HAVE_wfreadlinkat) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,__LIBDCALL,c16freadlinkat,(__fd_t __dfd, char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#elif defined(__CRT_HAVE_DOS$wfreadlinkat) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c16freadlinkat,(__fd_t __dfd, char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#elif defined(__CRT_HAVE_DOS$DOS$wfreadlinkat)
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c16freadlinkat,(__fd_t __dfd, char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen, __atflag_t __flags),DOS$wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wfreadlinkat) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,__LIBKCALL,c32freadlinkat,(__fd_t __dfd, char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#elif defined(__CRT_HAVE_DOS$wfreadlinkat) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c32freadlinkat,(__fd_t __dfd, char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#elif defined(__CRT_HAVE_DOS$KOS$wfreadlinkat)
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c32freadlinkat,(__fd_t __dfd, char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen, __atflag_t __flags),KOS$wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#endif /* ... */
#endif /* __USE_KOS */
#if defined(__CRT_HAVE_wunlinkat) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBDCALL,c16unlinkat,(__fd_t __dfd, char16_t const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#elif defined(__CRT_HAVE_DOS$wunlinkat) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16unlinkat,(__fd_t __dfd, char16_t const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#elif defined(__CRT_HAVE_DOS$DOS$wunlinkat)
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16unlinkat,(__fd_t __dfd, char16_t const *__name, __atflag_t __flags),DOS$wunlinkat,(__dfd,__name,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wunlinkat) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBKCALL,c32unlinkat,(__fd_t __dfd, char32_t const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#elif defined(__CRT_HAVE_DOS$wunlinkat) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32unlinkat,(__fd_t __dfd, char32_t const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#elif defined(__CRT_HAVE_DOS$KOS$wunlinkat)
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32unlinkat,(__fd_t __dfd, char32_t const *__name, __atflag_t __flags),KOS$wunlinkat,(__dfd,__name,__flags))
#endif /* ... */
#endif /* __USE_ATFILE */
#if defined(__CRT_HAVE_wlchown) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBDCALL,c16lchown,(char16_t const *__file, __uid_t __owner, __gid_t __group),wlchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$wlchown) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16lchown,(char16_t const *__file, __uid_t __owner, __gid_t __group),wlchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$DOS$wlchown)
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16lchown,(char16_t const *__file, __uid_t __owner, __gid_t __group),DOS$wlchown,(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_fchownat) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.unistd/wlchown.h>
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16lchown)(char16_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlchown))((__WCHAR_TYPE__ const *)__file, __owner, __group); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_fchownat)
#include <local/parts.wchar.unistd/c16lchown.h>
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16lchown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16lchown)(char16_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16lchown))(__file, __owner, __group); })
#endif /* ... */
#if defined(__CRT_HAVE_wlchown) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBKCALL,c32lchown,(char32_t const *__file, __uid_t __owner, __gid_t __group),wlchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$wlchown) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32lchown,(char32_t const *__file, __uid_t __owner, __gid_t __group),wlchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$KOS$wlchown)
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32lchown,(char32_t const *__file, __uid_t __owner, __gid_t __group),KOS$wlchown,(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_fchownat) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.unistd/wlchown.h>
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32lchown)(char32_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlchown))((__WCHAR_TYPE__ const *)__file, __owner, __group); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_fchownat)
#include <local/parts.wchar.unistd/c32lchown.h>
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32lchown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32lchown)(char32_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32lchown))(__file, __owner, __group); })
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
#if defined(__CRT_HAVE_wtruncate64) && defined(__USE_FILE_OFFSET64) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBDCALL,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate64) && defined(__USE_FILE_OFFSET64) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$DOS$wtruncate64) && defined(__USE_FILE_OFFSET64)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),DOS$wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) && !defined(__USE_FILE_OFFSET64) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBDCALL,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate) && !defined(__USE_FILE_OFFSET64) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$DOS$wtruncate) && !defined(__USE_FILE_OFFSET64)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),DOS$wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_truncate64) || defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate))) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && ((defined(__CRT_HAVE__chsize) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_chsize) && !defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s)) && (__SIZEOF_WCHAR_T__ == 2))
#include <local/parts.wchar.unistd/wtruncate.h>
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBDCALL c16truncate)(char16_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate))((__WCHAR_TYPE__ const *)__file, __length); }
#elif defined(__CRT_HAVE_truncate64) || defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate))) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && ((defined(__CRT_HAVE__chsize) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_chsize) && !defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s)))
#include <local/parts.wchar.unistd/c16truncate.h>
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16truncate, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBDCALL c16truncate)(char16_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16truncate))(__file, __length); })
#endif /* ... */
#if defined(__CRT_HAVE_wtruncate64) && defined(__USE_FILE_OFFSET64) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBKCALL,c32truncate,(char32_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate64) && defined(__USE_FILE_OFFSET64) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate,(char32_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$KOS$wtruncate64) && defined(__USE_FILE_OFFSET64)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate,(char32_t const *__file, __PIO_OFFSET __length),KOS$wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) && !defined(__USE_FILE_OFFSET64) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBKCALL,c32truncate,(char32_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate) && !defined(__USE_FILE_OFFSET64) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate,(char32_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$KOS$wtruncate) && !defined(__USE_FILE_OFFSET64)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate,(char32_t const *__file, __PIO_OFFSET __length),KOS$wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_truncate64) || defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate))) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && ((defined(__CRT_HAVE__chsize) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_chsize) && !defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s)) && (__SIZEOF_WCHAR_T__ == 4))
#include <local/parts.wchar.unistd/wtruncate.h>
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBKCALL c32truncate)(char32_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate))((__WCHAR_TYPE__ const *)__file, __length); }
#elif defined(__CRT_HAVE_truncate64) || defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate))) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && ((defined(__CRT_HAVE__chsize) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_chsize) && !defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s)))
#include <local/parts.wchar.unistd/c32truncate.h>
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32truncate, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBKCALL c32truncate)(char32_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32truncate))(__file, __length); })
#endif /* ... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_wtruncate64) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBDCALL,c16truncate64,(char16_t const *__file, __PIO_OFFSET64 __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate64) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate64,(char16_t const *__file, __PIO_OFFSET64 __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$DOS$wtruncate64)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate64,(char16_t const *__file, __PIO_OFFSET64 __length),DOS$wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBDCALL,c16truncate64,(char16_t const *__file, __PIO_OFFSET64 __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate64,(char16_t const *__file, __PIO_OFFSET64 __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$DOS$wtruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate64,(char16_t const *__file, __PIO_OFFSET64 __length),DOS$wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate)) && (__SIZEOF_WCHAR_T__ == 2))
#include <local/parts.wchar.unistd/wtruncate64.h>
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBDCALL c16truncate64)(char16_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate64))((__WCHAR_TYPE__ const *)__file, __length); }
#elif defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate)))
#include <local/parts.wchar.unistd/c16truncate64.h>
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16truncate64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBDCALL c16truncate64)(char16_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16truncate64))(__file, __length); })
#endif /* ... */
#if defined(__CRT_HAVE_wtruncate64) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBKCALL,c32truncate64,(char32_t const *__file, __PIO_OFFSET64 __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate64) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate64,(char32_t const *__file, __PIO_OFFSET64 __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$KOS$wtruncate64)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate64,(char32_t const *__file, __PIO_OFFSET64 __length),KOS$wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBKCALL,c32truncate64,(char32_t const *__file, __PIO_OFFSET64 __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate64,(char32_t const *__file, __PIO_OFFSET64 __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$KOS$wtruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate64,(char32_t const *__file, __PIO_OFFSET64 __length),KOS$wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate)) && (__SIZEOF_WCHAR_T__ == 4))
#include <local/parts.wchar.unistd/wtruncate64.h>
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBKCALL c32truncate64)(char32_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate64))((__WCHAR_TYPE__ const *)__file, __length); }
#elif defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate)))
#include <local/parts.wchar.unistd/c32truncate64.h>
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32truncate64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBKCALL c32truncate64)(char32_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32truncate64))(__file, __length); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_wsymlink) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__LIBDCALL,c16symlink,(char16_t const *__link_text, char16_t const *__target_path),wsymlink,(__link_text,__target_path))
#elif defined(__CRT_HAVE_DOS$wsymlink) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16symlink,(char16_t const *__link_text, char16_t const *__target_path),wsymlink,(__link_text,__target_path))
#elif defined(__CRT_HAVE_DOS$DOS$wsymlink)
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16symlink,(char16_t const *__link_text, char16_t const *__target_path),DOS$wsymlink,(__link_text,__target_path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_symlinkat) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.unistd/wsymlink.h>
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBDCALL c16symlink)(char16_t const *__link_text, char16_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsymlink))((__WCHAR_TYPE__ const *)__link_text, (__WCHAR_TYPE__ const *)__target_path); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_symlinkat)
#include <local/parts.wchar.unistd/c16symlink.h>
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16symlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBDCALL c16symlink)(char16_t const *__link_text, char16_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16symlink))(__link_text, __target_path); })
#endif /* ... */
#if defined(__CRT_HAVE_wsymlink) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__LIBKCALL,c32symlink,(char32_t const *__link_text, char32_t const *__target_path),wsymlink,(__link_text,__target_path))
#elif defined(__CRT_HAVE_DOS$wsymlink) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32symlink,(char32_t const *__link_text, char32_t const *__target_path),wsymlink,(__link_text,__target_path))
#elif defined(__CRT_HAVE_DOS$KOS$wsymlink)
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32symlink,(char32_t const *__link_text, char32_t const *__target_path),KOS$wsymlink,(__link_text,__target_path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_symlinkat) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.unistd/wsymlink.h>
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBKCALL c32symlink)(char32_t const *__link_text, char32_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsymlink))((__WCHAR_TYPE__ const *)__link_text, (__WCHAR_TYPE__ const *)__target_path); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_symlinkat)
#include <local/parts.wchar.unistd/c32symlink.h>
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32symlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBKCALL c32symlink)(char32_t const *__link_text, char32_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32symlink))(__link_text, __target_path); })
#endif /* ... */
#if defined(__CRT_HAVE_wreadlink) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,__LIBDCALL,c16readlink,(char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen),wreadlink,(__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlink) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,c16readlink,(char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen),wreadlink,(__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$DOS$wreadlink)
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,c16readlink,(char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen),DOS$wreadlink,(__path,__buf,__buflen))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_readlinkat) && (__SIZEOF_WCHAR_T__ == 2)
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
__FORCELOCAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBDCALL c16readlink)(char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wreadlink))((__WCHAR_TYPE__ const *)__path, (__WCHAR_TYPE__ *)__buf, __buflen); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_readlinkat)
#include <local/parts.wchar.unistd/c16readlink.h>
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16readlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBDCALL c16readlink)(char16_t const *__restrict __path, char16_t *__restrict __buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16readlink))(__path, __buf, __buflen); })
#endif /* ... */
#if defined(__CRT_HAVE_wreadlink) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,__LIBKCALL,c32readlink,(char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen),wreadlink,(__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlink) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,c32readlink,(char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen),wreadlink,(__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$KOS$wreadlink)
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,c32readlink,(char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen),KOS$wreadlink,(__path,__buf,__buflen))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_readlinkat) && (__SIZEOF_WCHAR_T__ == 4)
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
__FORCELOCAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBKCALL c32readlink)(char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wreadlink))((__WCHAR_TYPE__ const *)__path, (__WCHAR_TYPE__ *)__buf, __buflen); }
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_readlinkat)
#include <local/parts.wchar.unistd/c32readlink.h>
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32readlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBKCALL c32readlink)(char32_t const *__restrict __path, char32_t *__restrict __buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32readlink))(__path, __buf, __buflen); })
#endif /* ... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */
#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
#if defined(__CRT_HAVE_wgetlogin_r) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBDCALL,c16getlogin_r,(char16_t *__name, size_t __name_len),wgetlogin_r,(__name,__name_len))
#elif defined(__CRT_HAVE_DOS$wgetlogin_r) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16getlogin_r,(char16_t *__name, size_t __name_len),wgetlogin_r,(__name,__name_len))
#elif defined(__CRT_HAVE_DOS$DOS$wgetlogin_r)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16getlogin_r,(char16_t *__name, size_t __name_len),DOS$wgetlogin_r,(__name,__name_len))
#endif /* ... */
#if defined(__CRT_HAVE_wgetlogin_r) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBKCALL,c32getlogin_r,(char32_t *__name, size_t __name_len),wgetlogin_r,(__name,__name_len))
#elif defined(__CRT_HAVE_DOS$wgetlogin_r) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32getlogin_r,(char32_t *__name, size_t __name_len),wgetlogin_r,(__name,__name_len))
#elif defined(__CRT_HAVE_DOS$KOS$wgetlogin_r)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32getlogin_r,(char32_t *__name, size_t __name_len),KOS$wgetlogin_r,(__name,__name_len))
#endif /* ... */
#endif /* __USE_REENTRANT || __USE_POSIX199506 */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_wgethostname) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBDCALL,c16gethostname,(char16_t *__name, size_t __buflen),wgethostname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$wgethostname) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16gethostname,(char16_t *__name, size_t __buflen),wgethostname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$DOS$wgethostname)
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16gethostname,(char16_t *__name, size_t __buflen),DOS$wgethostname,(__name,__buflen))
#endif /* ... */
#if defined(__CRT_HAVE_wgethostname) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBKCALL,c32gethostname,(char32_t *__name, size_t __buflen),wgethostname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$wgethostname) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32gethostname,(char32_t *__name, size_t __buflen),wgethostname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$KOS$wgethostname)
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32gethostname,(char32_t *__name, size_t __buflen),KOS$wgethostname,(__name,__buflen))
#endif /* ... */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */
#ifdef __USE_MISC
#if defined(__CRT_HAVE_wsetlogin) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBDCALL,c16setlogin,(char16_t const *__name),wsetlogin,(__name))
#elif defined(__CRT_HAVE_DOS$wsetlogin) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16setlogin,(char16_t const *__name),wsetlogin,(__name))
#elif defined(__CRT_HAVE_DOS$DOS$wsetlogin)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16setlogin,(char16_t const *__name),DOS$wsetlogin,(__name))
#endif /* ... */
#if defined(__CRT_HAVE_wsetlogin) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBKCALL,c32setlogin,(char32_t const *__name),wsetlogin,(__name))
#elif defined(__CRT_HAVE_DOS$wsetlogin) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32setlogin,(char32_t const *__name),wsetlogin,(__name))
#elif defined(__CRT_HAVE_DOS$KOS$wsetlogin)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32setlogin,(char32_t const *__name),KOS$wsetlogin,(__name))
#endif /* ... */
#if defined(__CRT_HAVE_wsethostname) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> sethostname(2)
 * Set the name of the hosting machine */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBDCALL,c16sethostname,(char16_t const *__name, size_t __len),wsethostname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$wsethostname) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16sethostname,(char16_t const *__name, size_t __len),wsethostname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$DOS$wsethostname)
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16sethostname,(char16_t const *__name, size_t __len),DOS$wsethostname,(__name,__len))
#endif /* ... */
#if defined(__CRT_HAVE_wsethostname) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> sethostname(2)
 * Set the name of the hosting machine */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBKCALL,c32sethostname,(char32_t const *__name, size_t __len),wsethostname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$wsethostname) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32sethostname,(char32_t const *__name, size_t __len),wsethostname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$KOS$wsethostname)
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32sethostname,(char32_t const *__name, size_t __len),KOS$wsethostname,(__name,__len))
#endif /* ... */
#if defined(__CRT_HAVE_wgetdomainname) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBDCALL,c16getdomainname,(char16_t *__name, size_t __buflen),wgetdomainname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$wgetdomainname) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16getdomainname,(char16_t *__name, size_t __buflen),wgetdomainname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$DOS$wgetdomainname)
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16getdomainname,(char16_t *__name, size_t __buflen),DOS$wgetdomainname,(__name,__buflen))
#endif /* ... */
#if defined(__CRT_HAVE_wgetdomainname) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBKCALL,c32getdomainname,(char32_t *__name, size_t __buflen),wgetdomainname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$wgetdomainname) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32getdomainname,(char32_t *__name, size_t __buflen),wgetdomainname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$KOS$wgetdomainname)
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32getdomainname,(char32_t *__name, size_t __buflen),KOS$wgetdomainname,(__name,__buflen))
#endif /* ... */
#if defined(__CRT_HAVE_wsetdomainname) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBDCALL,c16setdomainname,(char16_t const *__name, size_t __len),wsetdomainname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$wsetdomainname) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16setdomainname,(char16_t const *__name, size_t __len),wsetdomainname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$DOS$wsetdomainname)
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16setdomainname,(char16_t const *__name, size_t __len),DOS$wsetdomainname,(__name,__len))
#endif /* ... */
#if defined(__CRT_HAVE_wsetdomainname) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__LIBKCALL,c32setdomainname,(char32_t const *__name, size_t __len),wsetdomainname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$wsetdomainname) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32setdomainname,(char32_t const *__name, size_t __len),wsetdomainname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$KOS$wsetdomainname)
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32setdomainname,(char32_t const *__name, size_t __len),KOS$wsetdomainname,(__name,__len))
#endif /* ... */
#endif /* __USE_MISC */
#if defined(__USE_MISC) || \
   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#if defined(__CRT_HAVE_wchroot) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBDCALL,c16chroot,(char16_t const *__restrict __path),wchroot,(__path))
#elif defined(__CRT_HAVE_DOS$wchroot) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chroot,(char16_t const *__restrict __path),wchroot,(__path))
#elif defined(__CRT_HAVE_DOS$DOS$wchroot)
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chroot,(char16_t const *__restrict __path),DOS$wchroot,(__path))
#endif /* ... */
#if defined(__CRT_HAVE_wchroot) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBKCALL,c32chroot,(char32_t const *__restrict __path),wchroot,(__path))
#elif defined(__CRT_HAVE_DOS$wchroot) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chroot,(char32_t const *__restrict __path),wchroot,(__path))
#elif defined(__CRT_HAVE_DOS$KOS$wchroot)
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chroot,(char32_t const *__restrict __path),KOS$wchroot,(__path))
#endif /* ... */
#endif /* ... */

#if (defined(_EVERY_SOURCE) || \
     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
#if defined(__CRT_HAVE_wctermid) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,,char16_t *,__NOTHROW_NCX,__LIBDCALL,c16ctermid,(char16_t *__s),wctermid,(__s))
#elif defined(__CRT_HAVE_DOS$wctermid) && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT_DOS(,char16_t *,__NOTHROW_NCX,c16ctermid,(char16_t *__s),wctermid,(__s))
#elif defined(__CRT_HAVE_DOS$DOS$wctermid)
__CREDIRECT_DOS(,char16_t *,__NOTHROW_NCX,c16ctermid,(char16_t *__s),DOS$wctermid,(__s))
#endif /* ... */
#if defined(__CRT_HAVE_wctermid) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,,char32_t *,__NOTHROW_NCX,__LIBKCALL,c32ctermid,(char32_t *__s),wctermid,(__s))
#elif defined(__CRT_HAVE_DOS$wctermid) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT_KOS(,char32_t *,__NOTHROW_NCX,c32ctermid,(char32_t *__s),wctermid,(__s))
#elif defined(__CRT_HAVE_DOS$KOS$wctermid)
__CREDIRECT_KOS(,char32_t *,__NOTHROW_NCX,c32ctermid,(char32_t *__s),KOS$wctermid,(__s))
#endif /* ... */
#endif /* _EVERY_SOURCE || (__USE_XOPEN && !__USE_XOPEN2K) */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_UCHAR_UNISTD_H */
