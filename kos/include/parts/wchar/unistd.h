/* HASH CRC-32:0xc375fd79 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
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

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_wttyname
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CDECLARE(__ATTR_WUNUSED,wchar_t *,__NOTHROW_RPC,wttyname,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_wttyname */
#include <paths.h>
#include <asm/os/fcntl.h>
#include <bits/os/dirent.h>
#include <asm/os/oflags.h>
#include <bits/os/stat.h>
#if defined(__CRT_HAVE_wttyname_r) || defined(__CRT_HAVE_ttyname_r) || defined(__CRT_HAVE_frealpath4) || ((defined(__CRT_HAVE_opendir) || defined(__CRT_HAVE___libc_opendir) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_opendirat) || defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || defined(__USE_DOS_DIRENT)) && ((defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS)) || (defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS)) || (defined(__USE_DOS_DIRENT) && defined(_DIRENT_MATCHES_DIRENT64))) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_fstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_fstat64)) && ((defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_lstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_lstat64)) && defined(_PATH_DEV))
#include <libc/local/parts.wchar.unistd/wttyname.h>
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__NAMESPACE_LOCAL_USING_OR_IMPL(wttyname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED wchar_t *__NOTHROW_RPC(__LIBCCALL wttyname)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wttyname))(__fd); })
#endif /* __CRT_HAVE_wttyname_r || __CRT_HAVE_ttyname_r || __CRT_HAVE_frealpath4 || ((__CRT_HAVE_opendir || __CRT_HAVE___libc_opendir || (__AT_FDCWD && (__CRT_HAVE_opendirat || __CRT_HAVE_fopendirat || (__CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || (__CRT_HAVE_fdopendir && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || __USE_DOS_DIRENT) && ((__CRT_HAVE_readdirk && __CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdirk64 && __CRT_KOS) || (__CRT_HAVE_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE___libc_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdir64 && !__CRT_KOS) || (__USE_DOS_DIRENT && _DIRENT_MATCHES_DIRENT64)) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__fstat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__fstat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_fstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_fstat64) && ((__CRT_HAVE_klstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_klstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_lstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_lstat64) && _PATH_DEV) */
#endif /* !__CRT_HAVE_wttyname */
#ifdef __CRT_HAVE_wttyname_r
/* >> wttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CDECLARE(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_RPC,wttyname_r,(__fd_t __fd, wchar_t *__buf, size_t __buflen),(__fd,__buf,__buflen))
#else /* __CRT_HAVE_wttyname_r */
#include <paths.h>
#include <asm/os/fcntl.h>
#include <bits/os/dirent.h>
#include <asm/os/oflags.h>
#include <bits/os/stat.h>
#if defined(__CRT_HAVE_ttyname_r) || defined(__CRT_HAVE_frealpath4) || ((defined(__CRT_HAVE_opendir) || defined(__CRT_HAVE___libc_opendir) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_opendirat) || defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || defined(__USE_DOS_DIRENT)) && ((defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS)) || (defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS)) || (defined(__USE_DOS_DIRENT) && defined(_DIRENT_MATCHES_DIRENT64))) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_fstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_fstat64)) && ((defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_lstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_lstat64)) && defined(_PATH_DEV))
#include <libc/local/parts.wchar.unistd/wttyname_r.h>
/* >> wttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__NAMESPACE_LOCAL_USING_OR_IMPL(wttyname_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) __errno_t __NOTHROW_RPC(__LIBCCALL wttyname_r)(__fd_t __fd, wchar_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wttyname_r))(__fd, __buf, __buflen); })
#endif /* __CRT_HAVE_ttyname_r || __CRT_HAVE_frealpath4 || ((__CRT_HAVE_opendir || __CRT_HAVE___libc_opendir || (__AT_FDCWD && (__CRT_HAVE_opendirat || __CRT_HAVE_fopendirat || (__CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || (__CRT_HAVE_fdopendir && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || __USE_DOS_DIRENT) && ((__CRT_HAVE_readdirk && __CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdirk64 && __CRT_KOS) || (__CRT_HAVE_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE___libc_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdir64 && !__CRT_KOS) || (__USE_DOS_DIRENT && _DIRENT_MATCHES_DIRENT64)) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__fstat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__fstat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_fstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_fstat64) && ((__CRT_HAVE_klstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_klstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_lstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_lstat64) && _PATH_DEV) */
#endif /* !__CRT_HAVE_wttyname_r */
#ifdef __CRT_HAVE_wchown
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,wchown,(wchar_t const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#else /* __CRT_HAVE_wchown */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wfchownat) || (defined(__CRT_HAVE_fchownat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_chown) || defined(__CRT_HAVE___chown) || defined(__CRT_HAVE___libc_chown) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_fchownat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/wchown.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wchown, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL wchown)(wchar_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchown))(__file, __owner, __group); })
#endif /* (__AT_FDCWD && (__CRT_HAVE_wfchownat || (__CRT_HAVE_fchownat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_chown || __CRT_HAVE___chown || __CRT_HAVE___libc_chown || (__AT_FDCWD && __CRT_HAVE_fchownat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE_wchown */
#ifdef __CRT_HAVE_wpathconf
__CDECLARE(__ATTR_IN(1),__LONGPTR_TYPE__,__NOTHROW_RPC,wpathconf,(wchar_t const *__path, __STDC_INT_AS_UINT_T __name),(__path,__name))
#else /* __CRT_HAVE_wpathconf */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_pathconf) || defined(__CRT_HAVE___pathconf) || ((defined(__CRT_HAVE_fpathconf) || defined(__CRT_HAVE___fpathconf)) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && defined(__O_RDONLY))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.unistd/wpathconf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wpathconf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __LONGPTR_TYPE__ __NOTHROW_RPC(__LIBCCALL wpathconf)(wchar_t const *__path, __STDC_INT_AS_UINT_T __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wpathconf))(__path, __name); })
#endif /* (__CRT_HAVE_pathconf || __CRT_HAVE___pathconf || ((__CRT_HAVE_fpathconf || __CRT_HAVE___fpathconf) && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && __O_RDONLY)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#endif /* !__CRT_HAVE_wpathconf */
#ifdef __CRT_HAVE_wlink
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,wlink,(wchar_t const *__from, wchar_t const *__to),(__from,__to))
#else /* __CRT_HAVE_wlink */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wlinkat) || ((defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_linkat)))) || ((defined(__CRT_HAVE_link) || defined(__CRT_HAVE___link) || defined(__CRT_HAVE___libc_link) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_linkat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/wlink.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_RPC(__LIBCCALL wlink)(wchar_t const *__from, wchar_t const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlink))(__from, __to); })
#endif /* (__AT_FDCWD && (__CRT_HAVE_wlinkat || ((__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __CRT_HAVE_linkat))) || ((__CRT_HAVE_link || __CRT_HAVE___link || __CRT_HAVE___libc_link || (__AT_FDCWD && __CRT_HAVE_linkat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE_wlink */
#ifdef __CRT_HAVE_waccess
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,waccess,(wchar_t const *__file, __STDC_INT_AS_UINT_T __type),(__file,__type))
#elif defined(__CRT_HAVE__waccess)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,waccess,(wchar_t const *__file, __STDC_INT_AS_UINT_T __type),_waccess,(__file,__type))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wfaccessat) || (defined(__CRT_HAVE_faccessat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_access) || defined(__CRT_HAVE__access) || defined(__CRT_HAVE___access) || defined(__CRT_HAVE___libc_access) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/waccess.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(waccess, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL waccess)(wchar_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(waccess))(__file, __type); })
#endif /* (__AT_FDCWD && (__CRT_HAVE_wfaccessat || (__CRT_HAVE_faccessat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_access || __CRT_HAVE__access || __CRT_HAVE___access || __CRT_HAVE___libc_access || (__AT_FDCWD && __CRT_HAVE_faccessat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !... */
#ifdef __CRT_HAVE_wchdir
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,wchdir,(wchar_t const *__path),(__path))
#elif defined(__CRT_HAVE__wchdir)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,wchdir,(wchar_t const *__path),_wchdir,(__path))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_chdir) || defined(__CRT_HAVE__chdir) || defined(__CRT_HAVE___chdir) || defined(__CRT_HAVE___libc_chdir) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_fchdirat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.unistd/wchdir.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wchdir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL wchdir)(wchar_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchdir))(__path); })
#endif /* (__CRT_HAVE_chdir || __CRT_HAVE__chdir || __CRT_HAVE___chdir || __CRT_HAVE___libc_chdir || (__AT_FDCWD && __CRT_HAVE_fchdirat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#endif /* !... */
#ifndef __wgetcwd_defined
#define __wgetcwd_defined
#ifdef __CRT_HAVE_wgetcwd
__CDECLARE(__ATTR_OUTS(1, 2),wchar_t *,__NOTHROW_RPC,wgetcwd,(wchar_t *__buf, size_t __bufsize),(__buf,__bufsize))
#elif defined(__CRT_HAVE__wgetcwd)
__CREDIRECT(__ATTR_OUTS(1, 2),wchar_t *,__NOTHROW_RPC,wgetcwd,(wchar_t *__buf, size_t __bufsize),_wgetcwd,(__buf,__bufsize))
#elif (defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/parts.wchar.unistd/wgetcwd.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wgetcwd, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) wchar_t *__NOTHROW_RPC(__LIBCCALL wgetcwd)(wchar_t *__buf, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wgetcwd))(__buf, __bufsize); })
#else /* ... */
#undef __wgetcwd_defined
#endif /* !... */
#endif /* !__wgetcwd_defined */
#ifdef __CRT_HAVE_wunlink
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,wunlink,(wchar_t const *__file),(__file))
#elif defined(__CRT_HAVE__wunlink)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,wunlink,(wchar_t const *__file),_wunlink,(__file))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wunlinkat) || (defined(__CRT_HAVE_unlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/wunlink.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wunlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL wunlink)(wchar_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wunlink))(__file); })
#endif /* (__AT_FDCWD && (__CRT_HAVE_wunlinkat || (__CRT_HAVE_unlinkat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_unlink || __CRT_HAVE__unlink || __CRT_HAVE___unlink || __CRT_HAVE___libc_unlink || (__AT_FDCWD && __CRT_HAVE_unlinkat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !... */
#ifdef __CRT_HAVE_wrmdir
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,wrmdir,(wchar_t const *__path),(__path))
#elif defined(__CRT_HAVE__wrmdir)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,wrmdir,(wchar_t const *__path),_wrmdir,(__path))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && (defined(__CRT_HAVE_wunlinkat) || (defined(__CRT_HAVE_unlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_rmdir) || defined(__CRT_HAVE__rmdir) || defined(__CRT_HAVE___rmdir) || defined(__CRT_HAVE___libc_rmdir) || (defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/wrmdir.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wrmdir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL wrmdir)(wchar_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrmdir))(__path); })
#endif /* (__AT_FDCWD && __AT_REMOVEDIR && (__CRT_HAVE_wunlinkat || (__CRT_HAVE_unlinkat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_rmdir || __CRT_HAVE__rmdir || __CRT_HAVE___rmdir || __CRT_HAVE___libc_rmdir || (__AT_FDCWD && __AT_REMOVEDIR && __CRT_HAVE_unlinkat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !... */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_weuidaccess
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,weuidaccess,(wchar_t const *__file, __STDC_INT_AS_UINT_T __type),(__file,__type))
#else /* __CRT_HAVE_weuidaccess */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && defined(__AT_EACCESS) && (defined(__CRT_HAVE_wfaccessat) || (defined(__CRT_HAVE_faccessat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_euidaccess) || defined(__CRT_HAVE_eaccess) || (defined(__CRT_HAVE__access) && defined(__CRT_DOS)) || (defined(__AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/weuidaccess.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(weuidaccess, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL weuidaccess)(wchar_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))(__file, __type); })
#endif /* (__AT_FDCWD && __AT_EACCESS && (__CRT_HAVE_wfaccessat || (__CRT_HAVE_faccessat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_euidaccess || __CRT_HAVE_eaccess || (__CRT_HAVE__access && __CRT_DOS) || (__AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE_weuidaccess */
#ifdef __CRT_HAVE_weuidaccess
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,weaccess,(wchar_t const *__file, __STDC_INT_AS_UINT_T __type),weuidaccess,(__file,__type))
#else /* __CRT_HAVE_weuidaccess */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && defined(__AT_EACCESS) && (defined(__CRT_HAVE_wfaccessat) || (defined(__CRT_HAVE_faccessat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_euidaccess) || defined(__CRT_HAVE_eaccess) || (defined(__CRT_HAVE__access) && defined(__CRT_DOS)) || (defined(__AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/weuidaccess.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL weaccess)(wchar_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(weuidaccess))(__file, __type); }
#endif /* (__AT_FDCWD && __AT_EACCESS && (__CRT_HAVE_wfaccessat || (__CRT_HAVE_faccessat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_euidaccess || __CRT_HAVE_eaccess || (__CRT_HAVE__access && __CRT_DOS) || (__AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE_weuidaccess */
#ifdef __CRT_HAVE_wget_current_dir_name
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,wchar_t *,__NOTHROW_RPC,wget_current_dir_name,(void),())
#elif (defined(__CRT_HAVE_get_current_dir_name) || defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/parts.wchar.unistd/wget_current_dir_name.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wget_current_dir_name, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED wchar_t *__NOTHROW_RPC(__LIBCCALL wget_current_dir_name)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wget_current_dir_name))(); })
#endif /* ... */
#endif /* __USE_GNU */
#ifdef __USE_ATFILE
#ifdef __CRT_HAVE_wfaccessat
__CDECLARE(__ATTR_IN(2),int,__NOTHROW_RPC,wfaccessat,(__fd_t __dfd, wchar_t const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),(__dfd,__file,__type,__flags))
#elif defined(__CRT_HAVE_faccessat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.unistd/wfaccessat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wfaccessat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) int __NOTHROW_RPC(__LIBCCALL wfaccessat)(__fd_t __dfd, wchar_t const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfaccessat))(__dfd, __file, __type, __flags); })
#endif /* ... */
#ifdef __CRT_HAVE_wfchownat
__CDECLARE(__ATTR_IN(2),int,__NOTHROW_RPC,wfchownat,(__fd_t __dfd, wchar_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),(__dfd,__file,__owner,__group,__flags))
#elif defined(__CRT_HAVE_fchownat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.unistd/wfchownat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wfchownat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) int __NOTHROW_RPC(__LIBCCALL wfchownat)(__fd_t __dfd, wchar_t const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfchownat))(__dfd, __file, __owner, __group, __flags); })
#endif /* ... */
#ifdef __CRT_HAVE_wlinkat
__CDECLARE(__ATTR_IN(2) __ATTR_IN(4),int,__NOTHROW_RPC,wlinkat,(__fd_t __fromfd, wchar_t const *__from, __fd_t __tofd, wchar_t const *__to, __atflag_t __flags),(__fromfd,__from,__tofd,__to,__flags))
#elif (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_linkat)
#include <libc/local/parts.wchar.unistd/wlinkat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wlinkat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN(4) int __NOTHROW_RPC(__LIBCCALL wlinkat)(__fd_t __fromfd, wchar_t const *__from, __fd_t __tofd, wchar_t const *__to, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlinkat))(__fromfd, __from, __tofd, __to, __flags); })
#endif /* ... */
#ifdef __CRT_HAVE_wsymlinkat
__CDECLARE(__ATTR_IN(1) __ATTR_IN(3),int,__NOTHROW_RPC,wsymlinkat,(wchar_t const *__link_text, __fd_t __tofd, wchar_t const *__target_path),(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_wfsymlinkat) || (defined(__CRT_HAVE_fsymlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_symlinkat) || defined(__CRT_HAVE_fsymlinkat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/wsymlinkat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wsymlinkat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(3) int __NOTHROW_RPC(__LIBCCALL wsymlinkat)(wchar_t const *__link_text, __fd_t __tofd, wchar_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsymlinkat))(__link_text, __tofd, __target_path); })
#endif /* ... */
#ifdef __CRT_HAVE_wreadlinkat
__CDECLARE(__ATTR_IN(2) __ATTR_OUTS(3, 4),ssize_t,__NOTHROW_RPC,wreadlinkat,(__fd_t __dfd, wchar_t const *__path, wchar_t *__buf, size_t __buflen),(__dfd,__path,__buf,__buflen))
#else /* __CRT_HAVE_wreadlinkat */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_wfreadlinkat) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_freadlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_readlinkat) || defined(__CRT_HAVE_freadlinkat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/wreadlinkat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wreadlinkat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(3, 4) ssize_t __NOTHROW_RPC(__LIBCCALL wreadlinkat)(__fd_t __dfd, wchar_t const *__path, wchar_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wreadlinkat))(__dfd, __path, __buf, __buflen); })
#endif /* __CRT_HAVE_wfreadlinkat || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_freadlinkat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_readlinkat || __CRT_HAVE_freadlinkat) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE_wreadlinkat */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_wfsymlinkat
__CDECLARE(__ATTR_IN(1) __ATTR_IN(3),int,__NOTHROW_RPC,wfsymlinkat,(wchar_t const *__link_text, __fd_t __tofd, wchar_t const *__target_path, __atflag_t __flags),(__link_text,__tofd,__target_path,__flags))
#elif defined(__CRT_HAVE_fsymlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.unistd/wfsymlinkat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wfsymlinkat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(3) int __NOTHROW_RPC(__LIBCCALL wfsymlinkat)(wchar_t const *__link_text, __fd_t __tofd, wchar_t const *__target_path, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfsymlinkat))(__link_text, __tofd, __target_path, __flags); })
#endif /* ... */
#ifdef __CRT_HAVE_wfreadlinkat
__CDECLARE(__ATTR_IN(2) __ATTR_OUTS(3, 4),ssize_t,__NOTHROW_RPC,wfreadlinkat,(__fd_t __dfd, wchar_t const *__path, wchar_t *__buf, size_t __buflen, __atflag_t __flags),(__dfd,__path,__buf,__buflen,__flags))
#else /* __CRT_HAVE_wfreadlinkat */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_freadlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.unistd/wfreadlinkat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wfreadlinkat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(3, 4) ssize_t __NOTHROW_RPC(__LIBCCALL wfreadlinkat)(__fd_t __dfd, wchar_t const *__path, wchar_t *__buf, size_t __buflen, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfreadlinkat))(__dfd, __path, __buf, __buflen, __flags); })
#endif /* (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_freadlinkat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#endif /* !__CRT_HAVE_wfreadlinkat */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_wunlinkat
__CDECLARE(__ATTR_IN(2),int,__NOTHROW_RPC,wunlinkat,(__fd_t __dfd, wchar_t const *__file, __atflag_t __flags),(__dfd,__file,__flags))
#elif defined(__CRT_HAVE_unlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.unistd/wunlinkat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wunlinkat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) int __NOTHROW_RPC(__LIBCCALL wunlinkat)(__fd_t __dfd, wchar_t const *__file, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wunlinkat))(__dfd, __file, __flags); })
#endif /* ... */
#endif /* __USE_ATFILE */
#ifdef __CRT_HAVE_wlchown
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,wlchown,(wchar_t const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#else /* __CRT_HAVE_wlchown */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && (defined(__CRT_HAVE_wfchownat) || (defined(__CRT_HAVE_fchownat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_lchown) || (defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && defined(__CRT_HAVE_fchownat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/wlchown.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wlchown, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL wlchown)(wchar_t const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wlchown))(__file, __owner, __group); })
#endif /* (__AT_FDCWD && __AT_SYMLINK_NOFOLLOW && (__CRT_HAVE_wfchownat || (__CRT_HAVE_fchownat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_lchown || (__AT_FDCWD && __AT_SYMLINK_NOFOLLOW && __CRT_HAVE_fchownat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE_wlchown */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
#include <bits/types.h>
#if defined(__CRT_HAVE_wtruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,wtruncate,(wchar_t const *__file, __PIO_OFFSET __length),(__file,__length))
#elif defined(__CRT_HAVE_wtruncate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,wtruncate,(wchar_t const *__file, __PIO_OFFSET __length),wtruncate64,(__file,__length))
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_wtruncate64) || defined(__CRT_HAVE_wtruncate) || ((defined(__CRT_HAVE_truncate64) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize))) || defined(__CRT_HAVE_truncate) || defined(__CRT_HAVE___truncate) || defined(__CRT_HAVE___libc_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)) && defined(__O_WRONLY))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/wtruncate.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wtruncate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL wtruncate)(wchar_t const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate))(__file, __length); })
#endif /* __CRT_HAVE_wtruncate64 || __CRT_HAVE_wtruncate || ((__CRT_HAVE_truncate64 || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open) && (__CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize)) || __CRT_HAVE_truncate || __CRT_HAVE___truncate || __CRT_HAVE___libc_truncate || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize) && __O_WRONLY)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_wtruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,wtruncate64,(wchar_t const *__file, __PIO_OFFSET64 __length),wtruncate,(__file,__length))
#elif defined(__CRT_HAVE_wtruncate64)
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,wtruncate64,(wchar_t const *__file, __PIO_OFFSET64 __length),(__file,__length))
#else /* ... */
#include <asm/os/oflags.h>
#if ((defined(__CRT_HAVE_truncate64) || defined(__CRT_HAVE_truncate) || defined(__CRT_HAVE___truncate) || defined(__CRT_HAVE___libc_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || defined(__CRT_HAVE_wtruncate)
#include <libc/local/parts.wchar.unistd/wtruncate64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wtruncate64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL wtruncate64)(wchar_t const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtruncate64))(__file, __length); })
#endif /* ((__CRT_HAVE_truncate64 || __CRT_HAVE_truncate || __CRT_HAVE___truncate || __CRT_HAVE___libc_truncate || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open) && (__CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize))) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || __CRT_HAVE_wtruncate */
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_wsymlink
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,wsymlink,(wchar_t const *__link_text, wchar_t const *__target_path),(__link_text,__target_path))
#else /* __CRT_HAVE_wsymlink */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wsymlinkat) || defined(__CRT_HAVE_wfsymlinkat) || (defined(__CRT_HAVE_fsymlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_symlinkat) || defined(__CRT_HAVE_fsymlinkat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_symlink) || defined(__CRT_HAVE___symlink) || defined(__CRT_HAVE___libc_symlink) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_symlinkat) || defined(__CRT_HAVE_fsymlinkat)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/wsymlink.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wsymlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_RPC(__LIBCCALL wsymlink)(wchar_t const *__link_text, wchar_t const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsymlink))(__link_text, __target_path); })
#endif /* (__AT_FDCWD && (__CRT_HAVE_wsymlinkat || __CRT_HAVE_wfsymlinkat || (__CRT_HAVE_fsymlinkat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_symlinkat || __CRT_HAVE_fsymlinkat) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_symlink || __CRT_HAVE___symlink || __CRT_HAVE___libc_symlink || (__AT_FDCWD && (__CRT_HAVE_symlinkat || __CRT_HAVE_fsymlinkat))) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE_wsymlink */
#ifdef __CRT_HAVE_wreadlink
__CDECLARE(__ATTR_IN(1) __ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,wreadlink,(wchar_t const *__path, wchar_t *__buf, size_t __buflen),(__path,__buf,__buflen))
#else /* __CRT_HAVE_wreadlink */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wreadlinkat) || defined(__CRT_HAVE_wfreadlinkat) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_freadlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_readlinkat) || defined(__CRT_HAVE_freadlinkat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_readlink) || defined(__CRT_HAVE___readlink) || defined(__CRT_HAVE___libc_readlink) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_readlinkat) || defined(__CRT_HAVE_freadlinkat)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/wreadlink.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wreadlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUTS(2, 3) ssize_t __NOTHROW_RPC(__LIBCCALL wreadlink)(wchar_t const *__path, wchar_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wreadlink))(__path, __buf, __buflen); })
#endif /* (__AT_FDCWD && (__CRT_HAVE_wreadlinkat || __CRT_HAVE_wfreadlinkat || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_freadlinkat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_readlinkat || __CRT_HAVE_freadlinkat) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_readlink || __CRT_HAVE___readlink || __CRT_HAVE___libc_readlink || (__AT_FDCWD && (__CRT_HAVE_readlinkat || __CRT_HAVE_freadlinkat))) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE_wreadlink */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_wgethostname
__CDECLARE(__ATTR_OUTS(1, 2),int,__NOTHROW_NCX,wgethostname,(wchar_t *__name, size_t __buflen),(__name,__buflen))
#elif defined(__CRT_HAVE_uname) || defined(__CRT_HAVE___uname) || defined(__CRT_HAVE___libc_uname)
#include <libc/local/parts.wchar.unistd/wgethostname.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wgethostname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) int __NOTHROW_NCX(__LIBCCALL wgethostname)(wchar_t *__name, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wgethostname))(__name, __buflen); })
#endif /* ... */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_wsetlogin
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,wsetlogin,(wchar_t const *__name),(__name))
#elif defined(__CRT_HAVE_setlogin) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.unistd/wsetlogin.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wsetlogin, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL wsetlogin)(wchar_t const *__name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsetlogin))(__name); })
#endif /* ... */
#ifdef __CRT_HAVE_wsethostname
__CDECLARE(__ATTR_INS(1, 2),int,__NOTHROW_NCX,wsethostname,(wchar_t const *__name, size_t __len),(__name,__len))
#elif (defined(__CRT_HAVE_sethostname) || defined(__CRT_HAVE___sethostname) || defined(__CRT_HAVE___libc_sethostname)) && (defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.unistd/wsethostname.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wsethostname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(1, 2) int __NOTHROW_NCX(__LIBCCALL wsethostname)(wchar_t const *__name, size_t __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsethostname))(__name, __len); })
#endif /* ... */
#ifdef __CRT_HAVE_wgetdomainname
__CDECLARE(__ATTR_OUTS(1, 2),int,__NOTHROW_NCX,wgetdomainname,(wchar_t *__name, size_t __buflen),(__name,__buflen))
#elif defined(__CRT_HAVE_uname) || defined(__CRT_HAVE___uname) || defined(__CRT_HAVE___libc_uname)
#include <libc/local/parts.wchar.unistd/wgetdomainname.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wgetdomainname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) int __NOTHROW_NCX(__LIBCCALL wgetdomainname)(wchar_t *__name, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wgetdomainname))(__name, __buflen); })
#endif /* ... */
#ifdef __CRT_HAVE_wsetdomainname
__CDECLARE(__ATTR_INS(1, 2),int,__NOTHROW_NCX,wsetdomainname,(wchar_t const *__name, size_t __len),(__name,__len))
#elif (defined(__CRT_HAVE_setdomainname) || defined(__CRT_HAVE___setdomainname) || defined(__CRT_HAVE___libc_setdomainname)) && (defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.unistd/wsetdomainname.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wsetdomainname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(1, 2) int __NOTHROW_NCX(__LIBCCALL wsetdomainname)(wchar_t const *__name, size_t __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsetdomainname))(__name, __len); })
#endif /* ... */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#ifdef __CRT_HAVE_wchroot
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,wchroot,(wchar_t const *__path),(__path))
#elif (defined(__CRT_HAVE_chroot) || defined(__CRT_HAVE___chroot) || defined(__CRT_HAVE___libc_chroot)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.unistd/wchroot.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wchroot, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL wchroot)(wchar_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchroot))(__path); })
#endif /* ... */
#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_WCHAR_UNISTD_H */
