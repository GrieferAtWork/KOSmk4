/* HASH CRC-32:0xc9637580 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Windows Kits (/ucrt/corecrt_wdirect.h) */
#ifndef _CORECRT_WDIRECT_H
#define _CORECRT_WDIRECT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __ernno_t_defined
#define __ernno_t_defined
typedef __errno_t errno_t;
#endif /* !__ernno_t_defined */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifdef __CRT_HAVE_wgetcwd
__CREDIRECT(__ATTR_OUTS(1, 2),wchar_t *,__NOTHROW_RPC,_wgetcwd,(wchar_t *__buf, size_t __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__wgetcwd)
__CDECLARE(__ATTR_OUTS(1, 2),wchar_t *,__NOTHROW_RPC,_wgetcwd,(wchar_t *__buf, size_t __bufsize),(__buf,__bufsize))
#elif (defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/parts.wchar.unistd/wgetcwd.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) wchar_t *__NOTHROW_RPC(__LIBCCALL _wgetcwd)(wchar_t *__buf, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wgetcwd))(__buf, __bufsize); }
#endif /* ... */
#ifdef __CRT_HAVE__wgetdcwd
__CDECLARE(__ATTR_OUTS(2, 3),wchar_t *,__NOTHROW_RPC,_wgetdcwd,(int __drive, wchar_t *__buf, size_t __size),(__drive,__buf,__size))
#elif defined(__CRT_HAVE__wgetdcwd_nolock)
__CREDIRECT(__ATTR_OUTS(2, 3),wchar_t *,__NOTHROW_RPC,_wgetdcwd,(int __drive, wchar_t *__buf, size_t __size),_wgetdcwd_nolock,(__drive,__buf,__size))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_wfrealpath4) || (defined(__CRT_HAVE_frealpath4) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))) && defined(__AT_FDDRIVE_CWD)
#include <libc/local/corecrt_wdirect/_wgetdcwd.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wgetdcwd, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) wchar_t *__NOTHROW_RPC(__LIBCCALL _wgetdcwd)(int __drive, wchar_t *__buf, size_t __size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wgetdcwd))(__drive, __buf, __size); })
#endif /* (__CRT_HAVE_wfrealpath4 || (__CRT_HAVE_frealpath4 && (__CRT_HAVE_convert_mbstowcs || __CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))))) && __AT_FDDRIVE_CWD */
#endif /* !... */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE__wgetdcwd) || defined(__CRT_HAVE__wgetdcwd_nolock) || ((defined(__CRT_HAVE_wfrealpath4) || (defined(__CRT_HAVE_frealpath4) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))) && defined(__AT_FDDRIVE_CWD))
#define _wgetdcwd_nolock(drive, buf, size) _wgetdcwd(drive, buf, size)
#endif /* __CRT_HAVE__wgetdcwd || __CRT_HAVE__wgetdcwd_nolock || ((__CRT_HAVE_wfrealpath4 || (__CRT_HAVE_frealpath4 && (__CRT_HAVE_convert_mbstowcs || __CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))))) && __AT_FDDRIVE_CWD) */
#ifdef __CRT_HAVE_wchdir
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,_wchdir,(wchar_t const *__path),wchdir,(__path))
#elif defined(__CRT_HAVE__wchdir)
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,_wchdir,(wchar_t const *__path),(__path))
#elif (defined(__CRT_HAVE_chdir) || defined(__CRT_HAVE__chdir) || defined(__CRT_HAVE___chdir) || defined(__CRT_HAVE___libc_chdir) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_fchdirat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.unistd/wchdir.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL _wchdir)(wchar_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wchdir))(__path); }
#endif /* ... */
#ifdef __CRT_HAVE_wrmdir
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,_wrmdir,(wchar_t const *__path),wrmdir,(__path))
#elif defined(__CRT_HAVE__wrmdir)
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,_wrmdir,(wchar_t const *__path),(__path))
#elif (defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && (defined(__CRT_HAVE_wunlinkat) || (defined(__CRT_HAVE_unlinkat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_rmdir) || defined(__CRT_HAVE__rmdir) || defined(__CRT_HAVE___rmdir) || defined(__CRT_HAVE___libc_rmdir) || (defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.unistd/wrmdir.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL _wrmdir)(wchar_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrmdir))(__path); }
#endif /* ... */
#ifdef __CRT_HAVE__wmkdir
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,_wmkdir,(wchar_t const *__path),(__path))
#elif defined(__CRT_HAVE_wmkdir) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wmkdirat) || defined(__CRT_HAVE_wfmkdirat) || (defined(__CRT_HAVE_fmkdirat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_mkdir) || defined(__CRT_HAVE___mkdir) || defined(__CRT_HAVE___libc_mkdir) || (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/corecrt_wdirect/_wmkdir.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wmkdir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL _wmkdir)(wchar_t const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wmkdir))(__path); })
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_CORECRT_WDIRECT_H */
