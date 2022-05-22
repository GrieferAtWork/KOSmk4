/* HASH CRC-32:0xd4fce8a3 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _PARTS_WCHAR_SYS_STAT_H
#define _PARTS_WCHAR_SYS_STAT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _SYS_STAT_H
#include <sys/stat.h>
#endif /* !_SYS_STAT_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_wmkdir
__CDECLARE(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,wmkdir,(wchar_t const *__pathname, __mode_t __mode),(__pathname,__mode))
#else /* __CRT_HAVE_wmkdir */
#include <asm/os/fcntl.h>
#if (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__wmkdir)) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wmkdirat) || defined(__CRT_HAVE_wfmkdirat) || (defined(__CRT_HAVE_fmkdirat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_mkdir) || defined(__CRT_HAVE___mkdir) || defined(__CRT_HAVE___libc_mkdir) || (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.sys.stat/wmkdir.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmkdir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) int __NOTHROW_RPC(__LIBCCALL wmkdir)(wchar_t const *__pathname, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmkdir))(__pathname, __mode); })
#endif /* (__CRT_DOS_PRIMARY && __CRT_HAVE__wmkdir) || (__AT_FDCWD && (__CRT_HAVE_wmkdirat || __CRT_HAVE_wfmkdirat || (__CRT_HAVE_fmkdirat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_mkdirat || __CRT_HAVE_fmkdirat) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_mkdir || __CRT_HAVE___mkdir || __CRT_HAVE___libc_mkdir || (__CRT_DOS_PRIMARY && __CRT_HAVE__mkdir) || (__AT_FDCWD && (__CRT_HAVE_mkdirat || __CRT_HAVE_fmkdirat))) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE_wmkdir */
#ifdef __CRT_HAVE_wchmod
__CDECLARE(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,wchmod,(wchar_t const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE__wchmod)
__CREDIRECT(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,wchmod,(wchar_t const *__filename, __mode_t __mode),_wchmod,(__filename,__mode))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wfchmodat) || (defined(__CRT_HAVE_fchmodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_chmod) || defined(__CRT_HAVE__chmod) || defined(__CRT_HAVE___chmod) || defined(__CRT_HAVE___libc_chmod) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_fchmodat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.sys.stat/wchmod.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wchmod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) int __NOTHROW_RPC(__LIBCCALL wchmod)(wchar_t const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchmod))(__filename, __mode); })
#endif /* (__AT_FDCWD && (__CRT_HAVE_wfchmodat || (__CRT_HAVE_fchmodat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_chmod || __CRT_HAVE__chmod || __CRT_HAVE___chmod || __CRT_HAVE___libc_chmod || (__AT_FDCWD && __CRT_HAVE_fchmodat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !... */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_wlchmod
__CDECLARE(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,wlchmod,(wchar_t const *__filename, __mode_t __mode),(__filename,__mode))
#else /* __CRT_HAVE_wlchmod */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && (defined(__CRT_HAVE_wfchmodat) || (defined(__CRT_HAVE_fchmodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_lchmod) || (defined(__CRT_HAVE__chmod) && defined(__CRT_DOS_PRIMARY)) || (defined(__CRT_HAVE_chmod) && defined(__CRT_DOS_PRIMARY)) || (defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && defined(__CRT_HAVE_fchmodat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.sys.stat/wlchmod.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wlchmod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) int __NOTHROW_RPC(__LIBCCALL wlchmod)(wchar_t const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlchmod))(__filename, __mode); })
#endif /* (__AT_FDCWD && __AT_SYMLINK_NOFOLLOW && (__CRT_HAVE_wfchmodat || (__CRT_HAVE_fchmodat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_lchmod || (__CRT_HAVE__chmod && __CRT_DOS_PRIMARY) || (__CRT_HAVE_chmod && __CRT_DOS_PRIMARY) || (__AT_FDCWD && __AT_SYMLINK_NOFOLLOW && __CRT_HAVE_fchmodat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE_wlchmod */
#endif /* __USE_MISC */

#if defined(__USE_KOS) && defined(__USE_ATFILE)
#ifdef __CRT_HAVE_wfmkdirat
__CDECLARE(__ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,wfmkdirat,(__fd_t __dirfd, wchar_t const *__pathname, __mode_t __mode, __atflag_t __flags),(__dirfd,__pathname,__mode,__flags))
#elif defined(__CRT_HAVE_fmkdirat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.sys.stat/wfmkdirat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wfmkdirat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) int __NOTHROW_RPC(__LIBCCALL wfmkdirat)(__fd_t __dirfd, wchar_t const *__pathname, __mode_t __mode, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfmkdirat))(__dirfd, __pathname, __mode, __flags); })
#endif /* ... */
#ifdef __CRT_HAVE_wfmknodat
__CDECLARE(__ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,wfmknodat,(__fd_t __dirfd, wchar_t const *__nodename, __mode_t __mode, __dev_t __dev, __atflag_t __flags),(__dirfd,__nodename,__mode,__dev,__flags))
#elif defined(__CRT_HAVE_fmknodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.sys.stat/wfmknodat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wfmknodat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) int __NOTHROW_RPC(__LIBCCALL wfmknodat)(__fd_t __dirfd, wchar_t const *__nodename, __mode_t __mode, __dev_t __dev, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfmknodat))(__dirfd, __nodename, __mode, __dev, __flags); })
#endif /* ... */
#endif /* __USE_KOS && __USE_ATFILE */
#ifdef __CRT_HAVE_wmkfifo
__CDECLARE(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,wmkfifo,(wchar_t const *__fifoname, __mode_t __mode),(__fifoname,__mode))
#else /* __CRT_HAVE_wmkfifo */
#include <asm/os/stat.h>
#include <asm/os/fcntl.h>
#if ((defined(__CRT_HAVE_wmknod) || ((defined(__CRT_HAVE_wmknodat) || defined(__CRT_HAVE_wfmknodat) || (defined(__CRT_HAVE_fmknodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && defined(__AT_FDCWD)) || ((defined(__CRT_HAVE_mknod) || ((defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && defined(__AT_FDCWD))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && defined(__S_IFIFO)) || ((defined(__CRT_HAVE_mkfifo) || ((defined(__CRT_HAVE_mknod) || ((defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && defined(__AT_FDCWD))) && defined(__S_IFIFO))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.sys.stat/wmkfifo.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmkfifo, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) int __NOTHROW_RPC(__LIBCCALL wmkfifo)(wchar_t const *__fifoname, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmkfifo))(__fifoname, __mode); })
#endif /* ((__CRT_HAVE_wmknod || ((__CRT_HAVE_wmknodat || __CRT_HAVE_wfmknodat || (__CRT_HAVE_fmknodat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_mknodat || __CRT_HAVE_fmknodat) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && __AT_FDCWD) || ((__CRT_HAVE_mknod || ((__CRT_HAVE_mknodat || __CRT_HAVE_fmknodat) && __AT_FDCWD)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && __S_IFIFO) || ((__CRT_HAVE_mkfifo || ((__CRT_HAVE_mknod || ((__CRT_HAVE_mknodat || __CRT_HAVE_fmknodat) && __AT_FDCWD)) && __S_IFIFO)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE_wmkfifo */

#ifdef __USE_ATFILE
#ifdef __CRT_HAVE_wfchmodat
__CDECLARE(__ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,wfchmodat,(__fd_t __dirfd, wchar_t const *__filename, __mode_t __mode, __atflag_t __flags),(__dirfd,__filename,__mode,__flags))
#elif defined(__CRT_HAVE_fchmodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.sys.stat/wfchmodat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wfchmodat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) int __NOTHROW_RPC(__LIBCCALL wfchmodat)(__fd_t __dirfd, wchar_t const *__filename, __mode_t __mode, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfchmodat))(__dirfd, __filename, __mode, __flags); })
#endif /* ... */
#ifdef __CRT_HAVE_wmkdirat
__CDECLARE(__ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,wmkdirat,(__fd_t __dirfd, wchar_t const *__pathname, __mode_t __mode),(__dirfd,__pathname,__mode))
#elif defined(__CRT_HAVE_wfmkdirat) || (defined(__CRT_HAVE_fmkdirat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.sys.stat/wmkdirat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmkdirat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) int __NOTHROW_RPC(__LIBCCALL wmkdirat)(__fd_t __dirfd, wchar_t const *__pathname, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmkdirat))(__dirfd, __pathname, __mode); })
#endif /* ... */
#ifdef __CRT_HAVE_wmkfifoat
__CDECLARE(__ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,wmkfifoat,(__fd_t __dirfd, wchar_t const *__fifoname, __mode_t __mode),(__dirfd,__fifoname,__mode))
#else /* __CRT_HAVE_wmkfifoat */
#include <asm/os/stat.h>
#if ((defined(__CRT_HAVE_wmknodat) || defined(__CRT_HAVE_wfmknodat) || (defined(__CRT_HAVE_fmknodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && defined(__S_IFIFO)) || ((defined(__CRT_HAVE_mkfifoat) || ((defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && defined(__S_IFIFO))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.sys.stat/wmkfifoat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmkfifoat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) int __NOTHROW_RPC(__LIBCCALL wmkfifoat)(__fd_t __dirfd, wchar_t const *__fifoname, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmkfifoat))(__dirfd, __fifoname, __mode); })
#endif /* ((__CRT_HAVE_wmknodat || __CRT_HAVE_wfmknodat || (__CRT_HAVE_fmknodat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_mknodat || __CRT_HAVE_fmknodat) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && __S_IFIFO) || ((__CRT_HAVE_mkfifoat || ((__CRT_HAVE_mknodat || __CRT_HAVE_fmknodat) && __S_IFIFO)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE_wmkfifoat */
#endif /* __USE_ATFILE */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __CRT_HAVE_wmknod
__CDECLARE(__ATTR_ACCESS_RO(1),int,__NOTHROW_RPC,wmknod,(wchar_t const *__nodename, __mode_t __mode, __dev_t __dev),(__nodename,__mode,__dev))
#else /* __CRT_HAVE_wmknod */
#include <asm/os/fcntl.h>
#if ((defined(__CRT_HAVE_wmknodat) || defined(__CRT_HAVE_wfmknodat) || (defined(__CRT_HAVE_fmknodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && defined(__AT_FDCWD)) || ((defined(__CRT_HAVE_mknod) || ((defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && defined(__AT_FDCWD))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.sys.stat/wmknod.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmknod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) int __NOTHROW_RPC(__LIBCCALL wmknod)(wchar_t const *__nodename, __mode_t __mode, __dev_t __dev) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmknod))(__nodename, __mode, __dev); })
#endif /* ((__CRT_HAVE_wmknodat || __CRT_HAVE_wfmknodat || (__CRT_HAVE_fmknodat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_mknodat || __CRT_HAVE_fmknodat) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) && __AT_FDCWD) || ((__CRT_HAVE_mknod || ((__CRT_HAVE_mknodat || __CRT_HAVE_fmknodat) && __AT_FDCWD)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE_wmknod */
#ifdef __USE_ATFILE
#ifdef __CRT_HAVE_wmknodat
__CDECLARE(__ATTR_ACCESS_RO(2),int,__NOTHROW_RPC,wmknodat,(__fd_t __dirfd, wchar_t const *__nodename, __mode_t __mode, __dev_t __dev),(__dirfd,__nodename,__mode,__dev))
#elif defined(__CRT_HAVE_wfmknodat) || (defined(__CRT_HAVE_fmknodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.sys.stat/wmknodat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmknodat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) int __NOTHROW_RPC(__LIBCCALL wmknodat)(__fd_t __dirfd, wchar_t const *__nodename, __mode_t __mode, __dev_t __dev) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmknodat))(__dirfd, __nodename, __mode, __dev); })
#endif /* ... */
#endif /* __USE_ATFILE */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_ATFILE
#include <bits/types.h>
#if defined(__CRT_HAVE_wutimensat) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CDECLARE(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3),int,__NOTHROW_RPC,wutimensat,(__fd_t __dirfd, wchar_t const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_wutimensat64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3),int,__NOTHROW_RPC,wutimensat,(__fd_t __dirfd, wchar_t const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags),wutimensat64,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_wutimensat64) || defined(__CRT_HAVE_wutimensat) || ((defined(__CRT_HAVE_utimensat64) || defined(__CRT_HAVE_utimensat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.sys.stat/wutimensat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wutimensat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3) int __NOTHROW_RPC(__LIBCCALL wutimensat)(__fd_t __dirfd, wchar_t const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutimensat))(__dirfd, __filename, __times, __flags); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_wutimensat) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3),int,__NOTHROW_RPC,wutimensat64,(__fd_t __dirfd, wchar_t const *__filename, struct timespec64 const __times[2 /*or:3*/], __atflag_t __flags),wutimensat,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_wutimensat64)
__CDECLARE(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3),int,__NOTHROW_RPC,wutimensat64,(__fd_t __dirfd, wchar_t const *__filename, struct timespec64 const __times[2 /*or:3*/], __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#elif ((defined(__CRT_HAVE_utimensat64) || defined(__CRT_HAVE_utimensat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || defined(__CRT_HAVE_wutimensat)
#include <libc/local/parts.wchar.sys.stat/wutimensat64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wutimensat64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3) int __NOTHROW_RPC(__LIBCCALL wutimensat64)(__fd_t __dirfd, wchar_t const *__filename, struct timespec64 const __times[2 /*or:3*/], __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutimensat64))(__dirfd, __filename, __times, __flags); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_ATFILE */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_WCHAR_SYS_STAT_H */
