/* HASH CRC-32:0xd3545f17 */
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

#ifdef __CC__
__SYSDECL_BEGIN

#if defined(__CRT_HAVE_wttyname) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT(__ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,c16ttyname,(__fd_t __fd),wttyname,(__fd))
#elif defined(__CRT_HAVE_DOS$wttyname)
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_DOS(__ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,c16ttyname,(__fd_t __fd),wttyname,(__fd))
#endif /* ... */
#if defined(__CRT_HAVE_wttyname) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT(__ATTR_WUNUSED,char32_t *,__NOTHROW_RPC,c32ttyname,(__fd_t __fd),wttyname,(__fd))
#elif defined(__CRT_HAVE_KOS$wttyname)
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_KOS(__ATTR_WUNUSED,char32_t *,__NOTHROW_RPC,c32ttyname,(__fd_t __fd),wttyname,(__fd))
#endif /* ... */
#if defined(__CRT_HAVE_wttyname_r) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16ttyname_r,(__fd_t __fd, char16_t *__buf, size_t __buflen),wttyname_r,(__fd,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wttyname_r)
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16ttyname_r,(__fd_t __fd, char16_t *__buf, size_t __buflen),wttyname_r,(__fd,__buf,__buflen))
#endif /* ... */
#if defined(__CRT_HAVE_wttyname_r) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32ttyname_r,(__fd_t __fd, char32_t *__buf, size_t __buflen),wttyname_r,(__fd,__buf,__buflen))
#elif defined(__CRT_HAVE_KOS$wttyname_r)
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32ttyname_r,(__fd_t __fd, char32_t *__buf, size_t __buflen),wttyname_r,(__fd,__buf,__buflen))
#endif /* ... */
#if defined(__CRT_HAVE_wchown) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chown,(char16_t const *__file, __uid_t __owner, __gid_t __group),wchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$wchown)
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chown,(char16_t const *__file, __uid_t __owner, __gid_t __group),wchown,(__file,__owner,__group))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wfchownat) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.unistd/wchown.h>
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16chown)(char16_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchown))((__WCHAR_TYPE__ const *)__file, __owner, __group); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wfchownat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wfchownat))
#include <libc/local/parts.uchar.unistd/c16chown.h>
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16chown, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16chown)(char16_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chown))(__file, __owner, __group); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wchown) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chown,(char32_t const *__file, __uid_t __owner, __gid_t __group),wchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_KOS$wchown)
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chown,(char32_t const *__file, __uid_t __owner, __gid_t __group),wchown,(__file,__owner,__group))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wfchownat) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.unistd/wchown.h>
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32chown)(char32_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchown))((__WCHAR_TYPE__ const *)__file, __owner, __group); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wfchownat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wfchownat))
#include <libc/local/parts.uchar.unistd/c32chown.h>
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32chown, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32chown)(char32_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32chown))(__file, __owner, __group); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wpathconf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> pathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CREDIRECT(__ATTR_NONNULL((1)),__LONGPTR_TYPE__,__NOTHROW_RPC,c16pathconf,(char16_t const *__path, __STDC_INT_AS_UINT_T __name),wpathconf,(__path,__name))
#elif defined(__CRT_HAVE_DOS$wpathconf)
/* >> pathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__LONGPTR_TYPE__,__NOTHROW_RPC,c16pathconf,(char16_t const *__path, __STDC_INT_AS_UINT_T __name),wpathconf,(__path,__name))
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_fpathconf) || defined(__CRT_HAVE___fpathconf)) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && defined(__O_RDONLY) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.unistd/wpathconf.h>
/* >> pathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGPTR_TYPE__ __NOTHROW_RPC(__LIBDCALL c16pathconf)(char16_t const *__path, __STDC_INT_AS_UINT_T __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wpathconf))((__WCHAR_TYPE__ const *)__path, __name); }
#elif (defined(__CRT_HAVE_fpathconf) || defined(__CRT_HAVE___fpathconf)) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && defined(__O_RDONLY)
#include <libc/local/parts.uchar.unistd/c16pathconf.h>
/* >> pathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16pathconf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGPTR_TYPE__ __NOTHROW_RPC(__LIBDCALL c16pathconf)(char16_t const *__path, __STDC_INT_AS_UINT_T __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16pathconf))(__path, __name); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wpathconf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> pathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CREDIRECT(__ATTR_NONNULL((1)),__LONGPTR_TYPE__,__NOTHROW_RPC,c32pathconf,(char32_t const *__path, __STDC_INT_AS_UINT_T __name),wpathconf,(__path,__name))
#elif defined(__CRT_HAVE_KOS$wpathconf)
/* >> pathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__LONGPTR_TYPE__,__NOTHROW_RPC,c32pathconf,(char32_t const *__path, __STDC_INT_AS_UINT_T __name),wpathconf,(__path,__name))
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_fpathconf) || defined(__CRT_HAVE___fpathconf)) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && defined(__O_RDONLY) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.unistd/wpathconf.h>
/* >> pathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGPTR_TYPE__ __NOTHROW_RPC(__LIBKCALL c32pathconf)(char32_t const *__path, __STDC_INT_AS_UINT_T __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wpathconf))((__WCHAR_TYPE__ const *)__path, __name); }
#elif (defined(__CRT_HAVE_fpathconf) || defined(__CRT_HAVE___fpathconf)) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && defined(__O_RDONLY)
#include <libc/local/parts.uchar.unistd/c32pathconf.h>
/* >> pathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32pathconf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGPTR_TYPE__ __NOTHROW_RPC(__LIBKCALL c32pathconf)(char32_t const *__path, __STDC_INT_AS_UINT_T __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32pathconf))(__path, __name); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wlink) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16link,(char16_t const *__from, char16_t const *__to),wlink,(__from,__to))
#elif defined(__CRT_HAVE_DOS$wlink)
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16link,(char16_t const *__from, char16_t const *__to),wlink,(__from,__to))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wlinkat) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.unistd/wlink.h>
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBDCALL c16link)(char16_t const *__from, char16_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlink))((__WCHAR_TYPE__ const *)__from, (__WCHAR_TYPE__ const *)__to); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wlinkat))
#include <libc/local/parts.uchar.unistd/c16link.h>
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16link, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBDCALL c16link)(char16_t const *__from, char16_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16link))(__from, __to); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wlink) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32link,(char32_t const *__from, char32_t const *__to),wlink,(__from,__to))
#elif defined(__CRT_HAVE_KOS$wlink)
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32link,(char32_t const *__from, char32_t const *__to),wlink,(__from,__to))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wlinkat) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.unistd/wlink.h>
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBKCALL c32link)(char32_t const *__from, char32_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlink))((__WCHAR_TYPE__ const *)__from, (__WCHAR_TYPE__ const *)__to); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wlinkat))
#include <libc/local/parts.uchar.unistd/c32link.h>
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32link, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBKCALL c32link)(char32_t const *__from, char32_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32link))(__from, __to); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_waccess) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16access,(char16_t const *__file, __STDC_INT_AS_UINT_T __type),waccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$waccess)
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16access,(char16_t const *__file, __STDC_INT_AS_UINT_T __type),waccess,(__file,__type))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.unistd/waccess.h>
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16access)(char16_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(waccess))((__WCHAR_TYPE__ const *)__file, __type); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wfaccessat))
#include <libc/local/parts.uchar.unistd/c16access.h>
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16access, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16access)(char16_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16access))(__file, __type); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_waccess) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32access,(char32_t const *__file, __STDC_INT_AS_UINT_T __type),waccess,(__file,__type))
#elif defined(__CRT_HAVE_KOS$waccess)
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32access,(char32_t const *__file, __STDC_INT_AS_UINT_T __type),waccess,(__file,__type))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.unistd/waccess.h>
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32access)(char32_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(waccess))((__WCHAR_TYPE__ const *)__file, __type); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wfaccessat))
#include <libc/local/parts.uchar.unistd/c32access.h>
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32access, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32access)(char32_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32access))(__file, __type); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wchdir) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> chdir(2)
 * Change the current working directory to `path' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chdir,(char16_t const *__path),wchdir,(__path))
#elif defined(__CRT_HAVE_DOS$wchdir)
/* >> chdir(2)
 * Change the current working directory to `path' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chdir,(char16_t const *__path),wchdir,(__path))
#elif defined(__CRT_HAVE__wchdir) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> chdir(2)
 * Change the current working directory to `path' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chdir,(char16_t const *__path),_wchdir,(__path))
#elif defined(__CRT_HAVE_DOS$_wchdir)
/* >> chdir(2)
 * Change the current working directory to `path' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chdir,(char16_t const *__path),_wchdir,(__path))
#endif /* ... */
#if defined(__CRT_HAVE_wchdir) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> chdir(2)
 * Change the current working directory to `path' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chdir,(char32_t const *__path),wchdir,(__path))
#elif defined(__CRT_HAVE_KOS$wchdir)
/* >> chdir(2)
 * Change the current working directory to `path' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chdir,(char32_t const *__path),wchdir,(__path))
#elif defined(__CRT_HAVE__wchdir) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> chdir(2)
 * Change the current working directory to `path' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chdir,(char32_t const *__path),_wchdir,(__path))
#elif defined(__CRT_HAVE_KOS$_wchdir)
/* >> chdir(2)
 * Change the current working directory to `path' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chdir,(char32_t const *__path),_wchdir,(__path))
#endif /* ... */
#if defined(__CRT_HAVE_wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,char16_t *,__NOTHROW_RPC,c16getcwd,(char16_t *__buf, size_t __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$wgetcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT_DOS(,char16_t *,__NOTHROW_RPC,c16getcwd,(char16_t *__buf, size_t __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,char16_t *,__NOTHROW_RPC,c16getcwd,(char16_t *__buf, size_t __bufsize),_wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$_wgetcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT_DOS(,char16_t *,__NOTHROW_RPC,c16getcwd,(char16_t *__buf, size_t __bufsize),_wgetcwd,(__buf,__bufsize))
#endif /* ... */
#if defined(__CRT_HAVE_wgetcwd) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,char32_t *,__NOTHROW_RPC,c32getcwd,(char32_t *__buf, size_t __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_KOS$wgetcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT_KOS(,char32_t *,__NOTHROW_RPC,c32getcwd,(char32_t *__buf, size_t __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__wgetcwd) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,char32_t *,__NOTHROW_RPC,c32getcwd,(char32_t *__buf, size_t __bufsize),_wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_KOS$_wgetcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT_KOS(,char32_t *,__NOTHROW_RPC,c32getcwd,(char32_t *__buf, size_t __bufsize),_wgetcwd,(__buf,__bufsize))
#endif /* ... */
#if defined(__CRT_HAVE_wunlink) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16unlink,(char16_t const *__file),wunlink,(__file))
#elif defined(__CRT_HAVE_DOS$wunlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16unlink,(char16_t const *__file),wunlink,(__file))
#elif defined(__CRT_HAVE__wunlink) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16unlink,(char16_t const *__file),_wunlink,(__file))
#elif defined(__CRT_HAVE_DOS$_wunlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16unlink,(char16_t const *__file),_wunlink,(__file))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.unistd/wunlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16unlink)(char16_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wunlink))((__WCHAR_TYPE__ const *)__file); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wunlinkat))
#include <libc/local/parts.uchar.unistd/c16unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16unlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16unlink)(char16_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16unlink))(__file); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wunlink) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32unlink,(char32_t const *__file),wunlink,(__file))
#elif defined(__CRT_HAVE_KOS$wunlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32unlink,(char32_t const *__file),wunlink,(__file))
#elif defined(__CRT_HAVE__wunlink) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32unlink,(char32_t const *__file),_wunlink,(__file))
#elif defined(__CRT_HAVE_KOS$_wunlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32unlink,(char32_t const *__file),_wunlink,(__file))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.unistd/wunlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32unlink)(char32_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wunlink))((__WCHAR_TYPE__ const *)__file); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wunlinkat))
#include <libc/local/parts.uchar.unistd/c32unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32unlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32unlink)(char32_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32unlink))(__file); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wrmdir) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16rmdir,(char16_t const *__path),wrmdir,(__path))
#elif defined(__CRT_HAVE_DOS$wrmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16rmdir,(char16_t const *__path),wrmdir,(__path))
#elif defined(__CRT_HAVE__wrmdir) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16rmdir,(char16_t const *__path),_wrmdir,(__path))
#elif defined(__CRT_HAVE_DOS$_wrmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16rmdir,(char16_t const *__path),_wrmdir,(__path))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.unistd/wrmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16rmdir)(char16_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrmdir))((__WCHAR_TYPE__ const *)__path); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wunlinkat))
#include <libc/local/parts.uchar.unistd/c16rmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16rmdir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16rmdir)(char16_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rmdir))(__path); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wrmdir) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32rmdir,(char32_t const *__path),wrmdir,(__path))
#elif defined(__CRT_HAVE_KOS$wrmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32rmdir,(char32_t const *__path),wrmdir,(__path))
#elif defined(__CRT_HAVE__wrmdir) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32rmdir,(char32_t const *__path),_wrmdir,(__path))
#elif defined(__CRT_HAVE_KOS$_wrmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32rmdir,(char32_t const *__path),_wrmdir,(__path))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.unistd/wrmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32rmdir)(char32_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrmdir))((__WCHAR_TYPE__ const *)__path); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wunlinkat))
#include <libc/local/parts.uchar.unistd/c32rmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32rmdir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32rmdir)(char32_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32rmdir))(__path); })
#endif /* ... */
#endif /* !... */
#ifdef __USE_GNU
#if defined(__CRT_HAVE_weuidaccess) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16euidaccess,(char16_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$weuidaccess)
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16euidaccess,(char16_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.unistd/weuidaccess.h>
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16euidaccess)(char16_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))((__WCHAR_TYPE__ const *)__file, __type); }
#elif defined(__AT_FDCWD) && defined(__AT_EACCESS) && ((defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wfaccessat))
#include <libc/local/parts.uchar.unistd/c16euidaccess.h>
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16euidaccess, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16euidaccess)(char16_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16euidaccess))(__file, __type); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_weuidaccess) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32euidaccess,(char32_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_KOS$weuidaccess)
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32euidaccess,(char32_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.unistd/weuidaccess.h>
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32euidaccess)(char32_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))((__WCHAR_TYPE__ const *)__file, __type); }
#elif defined(__AT_FDCWD) && defined(__AT_EACCESS) && ((defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wfaccessat))
#include <libc/local/parts.uchar.unistd/c32euidaccess.h>
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32euidaccess, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32euidaccess)(char32_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32euidaccess))(__file, __type); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_weuidaccess) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16eaccess,(char16_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_DOS$weuidaccess)
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16eaccess,(char16_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.unistd/weuidaccess.h>
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16eaccess)(char16_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))((__WCHAR_TYPE__ const *)__file, __type); }
#elif defined(__AT_FDCWD) && defined(__AT_EACCESS) && ((defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wfaccessat))
#include <libc/local/parts.uchar.unistd/c16euidaccess.h>
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16eaccess)(char16_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16euidaccess))(__file, __type); }
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_weuidaccess) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32eaccess,(char32_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#elif defined(__CRT_HAVE_KOS$weuidaccess)
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32eaccess,(char32_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.unistd/weuidaccess.h>
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32eaccess)(char32_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))((__WCHAR_TYPE__ const *)__file, __type); }
#elif defined(__AT_FDCWD) && defined(__AT_EACCESS) && ((defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wfaccessat))
#include <libc/local/parts.uchar.unistd/c32euidaccess.h>
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32eaccess)(char32_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32euidaccess))(__file, __type); }
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wget_current_dir_name) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,c16get_current_dir_name,(void),wget_current_dir_name,())
#elif defined(__CRT_HAVE_DOS$wget_current_dir_name)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_WUNUSED,char16_t *,__NOTHROW_RPC,c16get_current_dir_name,(void),wget_current_dir_name,())
#elif (defined(__CRT_HAVE_wgetcwd) || defined(__CRT_HAVE__wgetcwd)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.unistd/wget_current_dir_name.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char16_t *__NOTHROW_RPC(__LIBDCALL c16get_current_dir_name)(void) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wget_current_dir_name))(); }
#elif (defined(__CRT_HAVE_wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wgetcwd) || (defined(__CRT_HAVE__wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wgetcwd)
#include <libc/local/parts.uchar.unistd/c16get_current_dir_name.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16get_current_dir_name, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char16_t *__NOTHROW_RPC(__LIBDCALL c16get_current_dir_name)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16get_current_dir_name))(); })
#endif /* ... */
#if defined(__CRT_HAVE_wget_current_dir_name) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char32_t *,__NOTHROW_RPC,c32get_current_dir_name,(void),wget_current_dir_name,())
#elif defined(__CRT_HAVE_KOS$wget_current_dir_name)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED,char32_t *,__NOTHROW_RPC,c32get_current_dir_name,(void),wget_current_dir_name,())
#elif (defined(__CRT_HAVE_wgetcwd) || defined(__CRT_HAVE__wgetcwd)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.unistd/wget_current_dir_name.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char32_t *__NOTHROW_RPC(__LIBKCALL c32get_current_dir_name)(void) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wget_current_dir_name))(); }
#elif (defined(__CRT_HAVE_wgetcwd) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wgetcwd) || (defined(__CRT_HAVE__wgetcwd) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wgetcwd)
#include <libc/local/parts.uchar.unistd/c32get_current_dir_name.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32get_current_dir_name, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char32_t *__NOTHROW_RPC(__LIBKCALL c32get_current_dir_name)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32get_current_dir_name))(); })
#endif /* ... */
#endif /* __USE_GNU */
#ifdef __USE_ATFILE
#if defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> faccessat(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `dfd:file', testing for `type' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16faccessat,(__fd_t __dfd, char16_t const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#elif defined(__CRT_HAVE_DOS$wfaccessat)
/* >> faccessat(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `dfd:file', testing for `type' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16faccessat,(__fd_t __dfd, char16_t const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wfaccessat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> faccessat(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `dfd:file', testing for `type' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32faccessat,(__fd_t __dfd, char32_t const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#elif defined(__CRT_HAVE_KOS$wfaccessat)
/* >> faccessat(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `dfd:file', testing for `type' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32faccessat,(__fd_t __dfd, char32_t const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wfchownat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16fchownat,(__fd_t __dfd, char16_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_DOS$wfchownat)
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16fchownat,(__fd_t __dfd, char16_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wfchownat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32fchownat,(__fd_t __dfd, char32_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_KOS$wfchownat)
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32fchownat,(__fd_t __dfd, char32_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),wfchownat,(__dfd,__file,__owner,__group,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
__CREDIRECT(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,c16linkat,(__fd_t __fromfd, char16_t const *__from, __fd_t __tofd, char16_t const *__to, __atflag_t __flags),wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#elif defined(__CRT_HAVE_DOS$wlinkat)
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,c16linkat,(__fd_t __fromfd, char16_t const *__from, __fd_t __tofd, char16_t const *__to, __atflag_t __flags),wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
__CREDIRECT(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,c32linkat,(__fd_t __fromfd, char32_t const *__from, __fd_t __tofd, char32_t const *__to, __atflag_t __flags),wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#elif defined(__CRT_HAVE_KOS$wlinkat)
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
__CREDIRECT_KOS(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,c32linkat,(__fd_t __fromfd, char32_t const *__from, __fd_t __tofd, char32_t const *__to, __atflag_t __flags),wlinkat,(__fromfd,__from,__tofd,__to,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wsymlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,c16symlinkat,(char16_t const *__link_text, __fd_t __tofd, char16_t const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_DOS$wsymlinkat)
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,c16symlinkat,(char16_t const *__link_text, __fd_t __tofd, char16_t const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#endif /* ... */
#if defined(__CRT_HAVE_wsymlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,c32symlinkat,(char32_t const *__link_text, __fd_t __tofd, char32_t const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_KOS$wsymlinkat)
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,c32symlinkat,(char32_t const *__link_text, __fd_t __tofd, char32_t const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#endif /* ... */
#if defined(__CRT_HAVE_wreadlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c16readlinkat,(__fd_t __dfd, char16_t const *__path, char16_t *__buf, size_t __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlinkat)
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c16readlinkat,(__fd_t __dfd, char16_t const *__path, char16_t *__buf, size_t __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#endif /* ... */
#if defined(__CRT_HAVE_wreadlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c32readlinkat,(__fd_t __dfd, char32_t const *__path, char32_t *__buf, size_t __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_KOS$wreadlinkat)
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c32readlinkat,(__fd_t __dfd, char32_t const *__path, char32_t *__buf, size_t __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#endif /* ... */
#ifdef __USE_KOS
#if defined(__CRT_HAVE_wfreadlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c16freadlinkat,(__fd_t __dfd, char16_t const *__path, char16_t *__buf, size_t __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#elif defined(__CRT_HAVE_DOS$wfreadlinkat)
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c16freadlinkat,(__fd_t __dfd, char16_t const *__path, char16_t *__buf, size_t __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wfreadlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c32freadlinkat,(__fd_t __dfd, char32_t const *__path, char32_t *__buf, size_t __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#elif defined(__CRT_HAVE_KOS$wfreadlinkat)
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,c32freadlinkat,(__fd_t __dfd, char32_t const *__path, char32_t *__buf, size_t __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#endif /* ... */
#endif /* __USE_KOS */
#if defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16unlinkat,(__fd_t __dfd, char16_t const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#elif defined(__CRT_HAVE_DOS$wunlinkat)
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c16unlinkat,(__fd_t __dfd, char16_t const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#endif /* ... */
#if defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32unlinkat,(__fd_t __dfd, char32_t const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#elif defined(__CRT_HAVE_KOS$wunlinkat)
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,c32unlinkat,(__fd_t __dfd, char32_t const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#endif /* ... */
#endif /* __USE_ATFILE */
#if defined(__CRT_HAVE_wlchown) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16lchown,(char16_t const *__file, __uid_t __owner, __gid_t __group),wlchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_DOS$wlchown)
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16lchown,(char16_t const *__file, __uid_t __owner, __gid_t __group),wlchown,(__file,__owner,__group))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && defined(__CRT_HAVE_wfchownat) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.unistd/wlchown.h>
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16lchown)(char16_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlchown))((__WCHAR_TYPE__ const *)__file, __owner, __group); }
#elif defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && ((defined(__CRT_HAVE_wfchownat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wfchownat))
#include <libc/local/parts.uchar.unistd/c16lchown.h>
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16lchown, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16lchown)(char16_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16lchown))(__file, __owner, __group); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wlchown) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32lchown,(char32_t const *__file, __uid_t __owner, __gid_t __group),wlchown,(__file,__owner,__group))
#elif defined(__CRT_HAVE_KOS$wlchown)
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32lchown,(char32_t const *__file, __uid_t __owner, __gid_t __group),wlchown,(__file,__owner,__group))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && defined(__CRT_HAVE_wfchownat) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.unistd/wlchown.h>
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32lchown)(char32_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlchown))((__WCHAR_TYPE__ const *)__file, __owner, __group); }
#elif defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && ((defined(__CRT_HAVE_wfchownat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wfchownat))
#include <libc/local/parts.uchar.unistd/c32lchown.h>
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32lchown, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32lchown)(char32_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32lchown))(__file, __owner, __group); })
#endif /* ... */
#endif /* !... */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
#include <bits/types.h>
#if defined(__CRT_HAVE_wtruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate,(char16_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_wtruncate64) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize))) || defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)) && __SIZEOF_WCHAR_T__ == 2)
#include <libc/local/parts.wchar.unistd/wtruncate.h>
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBDCALL c16truncate)(char16_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate))((__WCHAR_TYPE__ const *)__file, __length); }
#elif defined(__CRT_HAVE_DOS$wtruncate64) || defined(__CRT_HAVE_DOS$wtruncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)))
#include <libc/local/parts.uchar.unistd/c16truncate.h>
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16truncate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBDCALL c16truncate)(char16_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16truncate))(__file, __length); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wtruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate,(char32_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_KOS$wtruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate,(char32_t const *__file, __PIO_OFFSET __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate,(char32_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_KOS$wtruncate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate,(char32_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_wtruncate64) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize))) || defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)) && __SIZEOF_WCHAR_T__ == 4)
#include <libc/local/parts.wchar.unistd/wtruncate.h>
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBKCALL c32truncate)(char32_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate))((__WCHAR_TYPE__ const *)__file, __length); }
#elif defined(__CRT_HAVE_KOS$wtruncate64) || defined(__CRT_HAVE_KOS$wtruncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)))
#include <libc/local/parts.uchar.unistd/c32truncate.h>
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32truncate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBKCALL c32truncate)(char32_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32truncate))(__file, __length); })
#endif /* ... */
#endif /* !... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_wtruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate64,(char16_t const *__file, __PIO_OFFSET64 __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate64,(char16_t const *__file, __PIO_OFFSET64 __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate64,(char16_t const *__file, __PIO_OFFSET64 __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_DOS$wtruncate64)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16truncate64,(char16_t const *__file, __PIO_OFFSET64 __length),wtruncate64,(__file,__length))
#else /* ... */
#include <asm/os/oflags.h>
#if defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)) && __SIZEOF_WCHAR_T__ == 2)
#include <libc/local/parts.wchar.unistd/wtruncate64.h>
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBDCALL c16truncate64)(char16_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate64))((__WCHAR_TYPE__ const *)__file, __length); }
#elif defined(__CRT_HAVE_DOS$wtruncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)))
#include <libc/local/parts.uchar.unistd/c16truncate64.h>
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16truncate64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBDCALL c16truncate64)(char16_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16truncate64))(__file, __length); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wtruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate64,(char32_t const *__file, __PIO_OFFSET64 __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_KOS$wtruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate64,(char32_t const *__file, __PIO_OFFSET64 __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate64,(char32_t const *__file, __PIO_OFFSET64 __length),wtruncate64,(__file,__length))
#elif defined(__CRT_HAVE_KOS$wtruncate64)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32truncate64,(char32_t const *__file, __PIO_OFFSET64 __length),wtruncate64,(__file,__length))
#else /* ... */
#include <asm/os/oflags.h>
#if defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)) && __SIZEOF_WCHAR_T__ == 4)
#include <libc/local/parts.wchar.unistd/wtruncate64.h>
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBKCALL c32truncate64)(char32_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate64))((__WCHAR_TYPE__ const *)__file, __length); }
#elif defined(__CRT_HAVE_KOS$wtruncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)))
#include <libc/local/parts.uchar.unistd/c32truncate64.h>
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32truncate64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBKCALL c32truncate64)(char32_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32truncate64))(__file, __length); })
#endif /* ... */
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_wsymlink) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16symlink,(char16_t const *__link_text, char16_t const *__target_path),wsymlink,(__link_text,__target_path))
#elif defined(__CRT_HAVE_DOS$wsymlink)
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16symlink,(char16_t const *__link_text, char16_t const *__target_path),wsymlink,(__link_text,__target_path))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wsymlinkat) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.unistd/wsymlink.h>
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBDCALL c16symlink)(char16_t const *__link_text, char16_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsymlink))((__WCHAR_TYPE__ const *)__link_text, (__WCHAR_TYPE__ const *)__target_path); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wsymlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wsymlinkat))
#include <libc/local/parts.uchar.unistd/c16symlink.h>
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16symlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBDCALL c16symlink)(char16_t const *__link_text, char16_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16symlink))(__link_text, __target_path); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wsymlink) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32symlink,(char32_t const *__link_text, char32_t const *__target_path),wsymlink,(__link_text,__target_path))
#elif defined(__CRT_HAVE_KOS$wsymlink)
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32symlink,(char32_t const *__link_text, char32_t const *__target_path),wsymlink,(__link_text,__target_path))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wsymlinkat) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.unistd/wsymlink.h>
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBKCALL c32symlink)(char32_t const *__link_text, char32_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsymlink))((__WCHAR_TYPE__ const *)__link_text, (__WCHAR_TYPE__ const *)__target_path); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wsymlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wsymlinkat))
#include <libc/local/parts.uchar.unistd/c32symlink.h>
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32symlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBKCALL c32symlink)(char32_t const *__link_text, char32_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32symlink))(__link_text, __target_path); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wreadlink) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,c16readlink,(char16_t const *__path, char16_t *__buf, size_t __buflen),wreadlink,(__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlink)
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,c16readlink,(char16_t const *__path, char16_t *__buf, size_t __buflen),wreadlink,(__path,__buf,__buflen))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wreadlinkat) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.unistd/wreadlink.h>
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBDCALL c16readlink)(char16_t const *__path, char16_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wreadlink))((__WCHAR_TYPE__ const *)__path, (__WCHAR_TYPE__ *)__buf, __buflen); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wreadlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wreadlinkat))
#include <libc/local/parts.uchar.unistd/c16readlink.h>
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16readlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBDCALL c16readlink)(char16_t const *__path, char16_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16readlink))(__path, __buf, __buflen); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wreadlink) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,c32readlink,(char32_t const *__path, char32_t *__buf, size_t __buflen),wreadlink,(__path,__buf,__buflen))
#elif defined(__CRT_HAVE_KOS$wreadlink)
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,c32readlink,(char32_t const *__path, char32_t *__buf, size_t __buflen),wreadlink,(__path,__buf,__buflen))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wreadlinkat) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.unistd/wreadlink.h>
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBKCALL c32readlink)(char32_t const *__path, char32_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wreadlink))((__WCHAR_TYPE__ const *)__path, (__WCHAR_TYPE__ *)__buf, __buflen); }
#elif defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wreadlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wreadlinkat))
#include <libc/local/parts.uchar.unistd/c32readlink.h>
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32readlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBKCALL c32readlink)(char32_t const *__path, char32_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32readlink))(__path, __buf, __buflen); })
#endif /* ... */
#endif /* !... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_wgethostname) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16gethostname,(char16_t *__name, size_t __buflen),wgethostname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$wgethostname)
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16gethostname,(char16_t *__name, size_t __buflen),wgethostname,(__name,__buflen))
#endif /* ... */
#if defined(__CRT_HAVE_wgethostname) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32gethostname,(char32_t *__name, size_t __buflen),wgethostname,(__name,__buflen))
#elif defined(__CRT_HAVE_KOS$wgethostname)
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32gethostname,(char32_t *__name, size_t __buflen),wgethostname,(__name,__buflen))
#endif /* ... */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */
#ifdef __USE_MISC
#if defined(__CRT_HAVE_wsetlogin) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> setlogin(3) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16setlogin,(char16_t const *__name),wsetlogin,(__name))
#elif defined(__CRT_HAVE_DOS$wsetlogin)
/* >> setlogin(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16setlogin,(char16_t const *__name),wsetlogin,(__name))
#endif /* ... */
#if defined(__CRT_HAVE_wsetlogin) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> setlogin(3) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32setlogin,(char32_t const *__name),wsetlogin,(__name))
#elif defined(__CRT_HAVE_KOS$wsetlogin)
/* >> setlogin(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32setlogin,(char32_t const *__name),wsetlogin,(__name))
#endif /* ... */
#if defined(__CRT_HAVE_wsethostname) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16sethostname,(char16_t const *__name, size_t __len),wsethostname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$wsethostname)
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16sethostname,(char16_t const *__name, size_t __len),wsethostname,(__name,__len))
#endif /* ... */
#if defined(__CRT_HAVE_wsethostname) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32sethostname,(char32_t const *__name, size_t __len),wsethostname,(__name,__len))
#elif defined(__CRT_HAVE_KOS$wsethostname)
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32sethostname,(char32_t const *__name, size_t __len),wsethostname,(__name,__len))
#endif /* ... */
#if defined(__CRT_HAVE_wgetdomainname) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16getdomainname,(char16_t *__name, size_t __buflen),wgetdomainname,(__name,__buflen))
#elif defined(__CRT_HAVE_DOS$wgetdomainname)
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16getdomainname,(char16_t *__name, size_t __buflen),wgetdomainname,(__name,__buflen))
#endif /* ... */
#if defined(__CRT_HAVE_wgetdomainname) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32getdomainname,(char32_t *__name, size_t __buflen),wgetdomainname,(__name,__buflen))
#elif defined(__CRT_HAVE_KOS$wgetdomainname)
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32getdomainname,(char32_t *__name, size_t __buflen),wgetdomainname,(__name,__buflen))
#endif /* ... */
#if defined(__CRT_HAVE_wsetdomainname) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16setdomainname,(char16_t const *__name, size_t __len),wsetdomainname,(__name,__len))
#elif defined(__CRT_HAVE_DOS$wsetdomainname)
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16setdomainname,(char16_t const *__name, size_t __len),wsetdomainname,(__name,__len))
#endif /* ... */
#if defined(__CRT_HAVE_wsetdomainname) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32setdomainname,(char32_t const *__name, size_t __len),wsetdomainname,(__name,__len))
#elif defined(__CRT_HAVE_KOS$wsetdomainname)
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32setdomainname,(char32_t const *__name, size_t __len),wsetdomainname,(__name,__len))
#endif /* ... */
#endif /* __USE_MISC */
#if defined(__USE_MISC) || \
   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#if defined(__CRT_HAVE_wchroot) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chroot,(char16_t const *__restrict __path),wchroot,(__path))
#elif defined(__CRT_HAVE_DOS$wchroot)
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16chroot,(char16_t const *__restrict __path),wchroot,(__path))
#endif /* ... */
#if defined(__CRT_HAVE_wchroot) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chroot,(char32_t const *__restrict __path),wchroot,(__path))
#elif defined(__CRT_HAVE_KOS$wchroot)
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32chroot,(char32_t const *__restrict __path),wchroot,(__path))
#endif /* ... */
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_UCHAR_UNISTD_H */
