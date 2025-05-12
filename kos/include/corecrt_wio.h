/* HASH CRC-32:0xc667a63d */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Windows Kits (/ucrt/corecrt_wio.h) */
/*!always_includes <crtdefs.h>*/
#ifndef _CORECRT_WIO_H
#define _CORECRT_WIO_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/types.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <crtdefs.h>

#ifdef __INTELLISENSE__
#include <bits/types/size_t.h>
#include <bits/types/errno_t.h>
#include <bits/types/intptr_t.h>
#endif /* __INTELLISENSE__ */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */

#ifndef _FSIZE_T_DEFINED
#define _FSIZE_T_DEFINED
typedef __UINT32_TYPE__ _fsize_t;
#endif /* _FSIZE_T_DEFINED */

struct _wfinddata32_t;
struct _wfinddata64_t;
struct _wfinddata32i64_t;
struct _wfinddata64i32_t;

#ifdef __CRT_HAVE_waccess
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,_waccess,(wchar_t const *__file, __STDC_INT_AS_UINT_T __type),waccess,(__file,__type))
#elif defined(__CRT_HAVE__waccess)
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,_waccess,(wchar_t const *__file, __STDC_INT_AS_UINT_T __type),(__file,__type))
#elif (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wfaccessat) || (defined(__CRT_HAVE_faccessat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_access) || defined(__CRT_HAVE__access) || defined(__CRT_HAVE___access) || defined(__CRT_HAVE___libc_access) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/waccess.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL _waccess)(wchar_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(waccess))(__file, __type); }
#endif /* ... */
#ifdef __CRT_HAVE__waccess_s
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),errno_t,__NOTHROW_RPC,_waccess_s,(wchar_t const *__file, __STDC_INT_AS_UINT_T __type),(__file,__type))
#elif defined(__CRT_HAVE_waccess) || defined(__CRT_HAVE__waccess) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wfaccessat) || (defined(__CRT_HAVE_faccessat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_access) || defined(__CRT_HAVE__access) || defined(__CRT_HAVE___access) || defined(__CRT_HAVE___libc_access) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/corecrt_wio/_waccess_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_waccess_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) errno_t __NOTHROW_RPC(__LIBCCALL _waccess_s)(wchar_t const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_waccess_s))(__file, __type); })
#endif /* ... */
#ifdef __CRT_HAVE_wchmod
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,_wchmod,(wchar_t const *__filename, __mode_t __mode),wchmod,(__filename,__mode))
#elif defined(__CRT_HAVE__wchmod)
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,_wchmod,(wchar_t const *__filename, __mode_t __mode),(__filename,__mode))
#elif (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wfchmodat) || (defined(__CRT_HAVE_fchmodat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_chmod) || defined(__CRT_HAVE__chmod) || defined(__CRT_HAVE___chmod) || defined(__CRT_HAVE___libc_chmod) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_fchmodat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.sys.stat/wchmod.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL _wchmod)(wchar_t const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchmod))(__filename, __mode); }
#endif /* ... */
#if defined(__CRT_HAVE_wcreat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,_wcreat,(wchar_t const *__filename, __mode_t __mode),wcreat,(__filename,__mode))
#elif defined(__CRT_HAVE__wcreat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,_wcreat,(wchar_t const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE_wcreat64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,_wcreat,(wchar_t const *__filename, __mode_t __mode),wcreat64,(__filename,__mode))
#elif (defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && (defined(__CRT_HAVE_wopen64) || defined(__CRT_HAVE_wopen) || defined(__CRT_HAVE__wopen) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wopenat64) || defined(__CRT_HAVE_wopenat) || ((defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || (((defined(__CRT_HAVE_creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE__creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE___creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE___libc_creat) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_creat64) || (defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.fcntl/wcreat.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __fd_t __NOTHROW_RPC(__LIBCCALL _wcreat)(wchar_t const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcreat))(__filename, __mode); }
#endif /* ... */
#ifdef __CRT_HAVE_wunlink
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,_wunlink,(wchar_t const *__file),wunlink,(__file))
#elif defined(__CRT_HAVE__wunlink)
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,_wunlink,(wchar_t const *__file),(__file))
#elif (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wunlinkat) || (defined(__CRT_HAVE_unlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/wunlink.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL _wunlink)(wchar_t const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wunlink))(__file); }
#endif /* ... */
#ifdef __CRT_HAVE_wrename
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,_wrename,(wchar_t const *__oldname, wchar_t const *__newname_or_path),wrename,(__oldname,__newname_or_path))
#elif defined(__CRT_HAVE__wrename)
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,_wrename,(wchar_t const *__oldname, wchar_t const *__newname_or_path),(__oldname,__newname_or_path))
#elif (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wrenameat) || defined(__CRT_HAVE_wrenameat2) || (defined(__CRT_HAVE_renameat2) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_renameat2)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.stdio/wrename.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_RPC(__LIBCCALL _wrename)(wchar_t const *__oldname, wchar_t const *__newname_or_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrename))(__oldname, __newname_or_path); }
#endif /* ... */
#ifdef __CRT_HAVE__wmktemp_s
__CDECLARE(__ATTR_INOUTS(1, 2),errno_t,__NOTHROW_NCX,_wmktemp_s,(wchar_t *__template_, size_t __bufsize),(__template_,__bufsize))
#else /* __CRT_HAVE__wmktemp_s */
#include <bits/os/stat.h>
#if defined(__CRT_HAVE__wmktemp) || ((defined(__CRT_HAVE_mktemp) || defined(__CRT_HAVE__mktemp) || defined(__CRT_HAVE___mktemp) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))) || (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_stat) || defined(__CRT_HAVE_stat64) || defined(__CRT_HAVE___stat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/corecrt_wio/_wmktemp_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wmktemp_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUTS(1, 2) errno_t __NOTHROW_NCX(__LIBCCALL _wmktemp_s)(wchar_t *__template_, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wmktemp_s))(__template_, __bufsize); })
#endif /* __CRT_HAVE__wmktemp || ((__CRT_HAVE_mktemp || __CRT_HAVE__mktemp || __CRT_HAVE___mktemp || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) || (__AT_FDCWD && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_stat || __CRT_HAVE_stat64 || __CRT_HAVE___stat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#endif /* !__CRT_HAVE__wmktemp_s */
#ifdef __CRT_HAVE__wmktemp
__CDECLARE(__ATTR_RETNONNULL __ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,_wmktemp,(wchar_t *__template_),(__template_))
#else /* __CRT_HAVE__wmktemp */
#include <bits/os/stat.h>
#if (defined(__CRT_HAVE_mktemp) || defined(__CRT_HAVE__mktemp) || defined(__CRT_HAVE___mktemp) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))) || (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_stat) || defined(__CRT_HAVE_stat64) || defined(__CRT_HAVE___stat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/corecrt_wio/_wmktemp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wmktemp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL _wmktemp)(wchar_t *__template_) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wmktemp))(__template_); })
#endif /* (__CRT_HAVE_mktemp || __CRT_HAVE__mktemp || __CRT_HAVE___mktemp || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) || (__AT_FDCWD && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_stat || __CRT_HAVE_stat64 || __CRT_HAVE___stat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#endif /* !__CRT_HAVE__wmktemp */

#ifdef __CRT_HAVE__wsopen_s
__CDECLARE(__ATTR_IN(2) __ATTR_OUT(1),errno_t,__NOTHROW_RPC,_wsopen_s,(__fd_t *__fd, wchar_t const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode),(__fd,__filename,__oflags,__sflags,__mode))
#elif defined(__CRT_HAVE__wsopen) || defined(__CRT_HAVE_wopen64) || defined(__CRT_HAVE_wopen) || defined(__CRT_HAVE__wopen) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wopenat64) || defined(__CRT_HAVE_wopenat) || ((defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/corecrt_wio/_wsopen_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wsopen_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUT(1) errno_t __NOTHROW_RPC(__LIBCCALL _wsopen_s)(__fd_t *__fd, wchar_t const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wsopen_s))(__fd, __filename, __oflags, __sflags, __mode); })
#endif /* ... */
#ifdef __CRT_HAVE__wsopen_dispatch
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(5),errno_t,__NOTHROW_RPC,_wsopen_dispatch,(wchar_t const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode, __fd_t *__fd, int __bsecure),(__filename,__oflags,__sflags,__mode,__fd,__bsecure))
#elif defined(__CRT_HAVE__wsopen_s) || defined(__CRT_HAVE__wsopen) || defined(__CRT_HAVE_wopen64) || defined(__CRT_HAVE_wopen) || defined(__CRT_HAVE__wopen) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wopenat64) || defined(__CRT_HAVE_wopenat) || ((defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/corecrt_wio/_wsopen_dispatch.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wsopen_dispatch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(5) errno_t __NOTHROW_RPC(__LIBCCALL _wsopen_dispatch)(wchar_t const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode, __fd_t *__fd, int __bsecure) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wsopen_dispatch))(__filename, __oflags, __sflags, __mode, __fd, __bsecure); })
#endif /* ... */
#if defined(__CRT_HAVE_wopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,_wopen,(wchar_t const *__filename, __oflag_t __oflags),wopen,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__wopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__LIBC __ATTR_WUNUSED __ATTR_IN(1) __fd_t __NOTHROW_RPC(__VLIBCCALL _wopen)(wchar_t const *__filename, __oflag_t __oflags, ...) __CASMNAME_SAME("_wopen");
#elif defined(__CRT_HAVE_wopen64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,_wopen,(wchar_t const *__filename, __oflag_t __oflags),wopen64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_wopen) || defined(__CRT_HAVE__wopen) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wopenat64) || defined(__CRT_HAVE_wopenat) || ((defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.fcntl/wopen.h>
#define _wopen(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wopen))(__VA_ARGS__)
#endif /* ... */
#ifdef __CRT_HAVE__wsopen
__LIBC __ATTR_WUNUSED __ATTR_IN(1) __fd_t __NOTHROW_RPC(__VLIBCCALL _wsopen)(wchar_t const *__filename, __oflag_t __oflags, int __sflags, ...) __CASMNAME_SAME("_wsopen");
#elif defined(__CRT_HAVE_wopen64) || defined(__CRT_HAVE_wopen) || defined(__CRT_HAVE__wopen) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wopenat64) || defined(__CRT_HAVE_wopenat) || ((defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/corecrt_wio/_wsopen.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_wsopen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __fd_t __NOTHROW_RPC(__VLIBCCALL _wsopen)(wchar_t const *__filename, __oflag_t __oflags, int __sflags, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wsopen))(__filename, __oflags, __sflags, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _wsopen(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wsopen))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__wfindfirst32
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),intptr_t,__NOTHROW_RPC,_wfindfirst32,(wchar_t const *__restrict __filename, struct _wfinddata32_t *__restrict __finddata),(__filename,__finddata))
#elif defined(__CRT_HAVE__wfindfirst)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),intptr_t,__NOTHROW_RPC,_wfindfirst32,(wchar_t const *__restrict __filename, struct _wfinddata32_t *__restrict __finddata),_wfindfirst,(__filename,__finddata))
#endif /* ... */
#ifdef __CRT_HAVE__wfindfirst32i64
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),intptr_t,__NOTHROW_RPC,_wfindfirst32i64,(wchar_t const *__restrict __filename, struct _wfinddata32i64_t *__restrict __finddata),(__filename,__finddata))
#elif defined(__CRT_HAVE__wfindfirsti64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),intptr_t,__NOTHROW_RPC,_wfindfirst32i64,(wchar_t const *__restrict __filename, struct _wfinddata32i64_t *__restrict __finddata),_wfindfirsti64,(__filename,__finddata))
#endif /* ... */
#ifdef __CRT_HAVE__wfindfirst64
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),intptr_t,__NOTHROW_RPC,_wfindfirst64,(wchar_t const *__restrict __filename, struct _wfinddata64_t *__restrict __finddata),(__filename,__finddata))
#elif defined(__CRT_HAVE__wfindfirst64i32)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),intptr_t,__NOTHROW_RPC,_wfindfirst64,(wchar_t const *__restrict __filename, struct _wfinddata64_t *__restrict __finddata),_wfindfirst64i32,(__filename,__finddata))
#endif /* ... */
#ifdef __CRT_HAVE__wfindfirst64
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),intptr_t,__NOTHROW_RPC,_wfindfirst64i32,(wchar_t const *__restrict __filename, struct _wfinddata64i32_t *__restrict __finddata),_wfindfirst64,(__filename,__finddata))
#elif defined(__CRT_HAVE__wfindfirst64i32)
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),intptr_t,__NOTHROW_RPC,_wfindfirst64i32,(wchar_t const *__restrict __filename, struct _wfinddata64i32_t *__restrict __finddata),(__filename,__finddata))
#endif /* ... */
#ifdef __CRT_HAVE__wfindnext32
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_RPC,_wfindnext32,(intptr_t __findfd, struct _wfinddata32_t *__restrict __finddata),(__findfd,__finddata))
#elif defined(__CRT_HAVE__wfindnext)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_RPC,_wfindnext32,(intptr_t __findfd, struct _wfinddata32_t *__restrict __finddata),_wfindnext,(__findfd,__finddata))
#endif /* ... */
#ifdef __CRT_HAVE__wfindnext32i64
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_RPC,_wfindnext32i64,(intptr_t __findfd, struct _wfinddata32i64_t *__restrict __finddata),(__findfd,__finddata))
#elif defined(__CRT_HAVE__wfindnexti64)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_RPC,_wfindnext32i64,(intptr_t __findfd, struct _wfinddata32i64_t *__restrict __finddata),_wfindnexti64,(__findfd,__finddata))
#endif /* ... */
#ifdef __CRT_HAVE__wfindnext64
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_RPC,_wfindnext64,(intptr_t __findfd, struct _wfinddata64_t *__restrict __finddata),(__findfd,__finddata))
#elif defined(__CRT_HAVE__wfindnext64i32)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_RPC,_wfindnext64,(intptr_t __findfd, struct _wfinddata64_t *__restrict __finddata),_wfindnext64i32,(__findfd,__finddata))
#endif /* ... */
#ifdef __CRT_HAVE__wfindnext64
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_RPC,_wfindnext64i32,(intptr_t __findfd, struct _wfinddata64i32_t *__restrict __finddata),_wfindnext64,(__findfd,__finddata))
#elif defined(__CRT_HAVE__wfindnext64i32)
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_RPC,_wfindnext64i32,(intptr_t __findfd, struct _wfinddata64i32_t *__restrict __finddata),(__findfd,__finddata))
#endif /* ... */

#ifndef _WFINDDATA_T_DEFINED
#define _WFINDDATA_T_DEFINED 1
/* Safely first! */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("attrib")
#pragma push_macro("time_create")
#pragma push_macro("time_access")
#pragma push_macro("time_write")
#pragma push_macro("size")
#pragma push_macro("name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef attrib
#undef time_create
#undef time_access
#undef time_write
#undef size
#undef name
struct _wfinddata32_t {
	__UINT32_TYPE__      attrib;
	__INT32_TYPE__       time_create;
	__INT32_TYPE__       time_access;
	__INT32_TYPE__       time_write;
	_fsize_t             size;
	wchar_t              name[260];
};
struct _wfinddata32i64_t {
	__UINT32_TYPE__      attrib;
	__INT32_TYPE__       time_create;
	__INT32_TYPE__       time_access;
	__INT32_TYPE__       time_write;
	__INT64_TYPE__       size;
	wchar_t              name[260];
};
struct _wfinddata64i32_t {
	__UINT32_TYPE__      attrib;
	__UINT32_TYPE__     _wfd64i32_pad; /* Padding made visible */
	__INT64_TYPE__       time_create;
	__INT64_TYPE__       time_access;
	__INT64_TYPE__       time_write;
	union {
		_fsize_t         size;
		__INT64_TYPE__ __pad; /* I think this is correct? */
	};
	wchar_t              name[260];
};
struct _wfinddata64_t {
	__UINT32_TYPE__      attrib;
	__UINT32_TYPE__     _wfd64_pad; /* Padding made visible */
	__INT64_TYPE__       time_create;
	__INT64_TYPE__       time_access;
	__INT64_TYPE__       time_write;
	__INT64_TYPE__       size;
	wchar_t              name[260];
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("name")
#pragma pop_macro("size")
#pragma pop_macro("time_write")
#pragma pop_macro("time_access")
#pragma pop_macro("time_create")
#pragma pop_macro("attrib")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifdef __USE_TIME_BITS64
#define _wfinddata_t                       _wfinddata64i32_t
#define _wfinddatai64_t                    _wfinddata64_t
#define _wfindfirst(filename, finddata)    _wfindfirst64i32(filename, finddata)
#define _wfindnext(findfd, finddata)       _wfindnext64i32(findfd, finddata)
#define _wfindfirsti64(filename, finddata) _wfindfirst64(filename, finddata)
#define _wfindnexti64(findfd, finddata)    _wfindnext64(findfd, finddata)
#else /* __USE_TIME_BITS64 */
#define _wfinddata_t                       _wfinddata32_t
#define _wfinddatai64_t                    _wfinddata32i64_t
#define _wfindfirst(filename, finddata)    _wfindfirst32(filename, finddata)
#define _wfindnext(findfd, finddata)       _wfindnext32(findfd, finddata)
#define _wfindfirsti64(filename, finddata) _wfindfirst32i64(filename, finddata)
#define _wfindnexti64(findfd, finddata)    _wfindnext32i64(findfd, finddata)
#endif /* !__USE_TIME_BITS64 */
#endif /* !_WFINDDATA_T_DEFINED */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_IO_H)
#include <parts/uchar/io.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_IO_H */
#endif /* __USE_UTF */

#endif /* !_CORECRT_WIO_H */
