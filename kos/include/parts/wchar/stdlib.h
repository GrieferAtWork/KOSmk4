/* HASH CRC-32:0x9f947cb5 */
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
#ifndef _PARTS_WCHAR_STDLIB_H
#define _PARTS_WCHAR_STDLIB_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* !_STDLIB_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __wsystem_defined
#define __wsystem_defined
#ifdef __CRT_HAVE_wsystem
__CDECLARE(,int,__NOTHROW_RPC,wsystem,(wchar_t const *__cmd),(__cmd))
#elif defined(__CRT_HAVE__wsystem)
__CREDIRECT(,int,__NOTHROW_RPC,wsystem,(wchar_t const *__cmd),_wsystem,(__cmd))
#else /* ... */
#include <libc/template/environ.h>
#if (defined(__CRT_HAVE_system) || defined(__CRT_HAVE___libc_system) || ((defined(__CRT_HAVE_shexec) || defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork) || defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.stdlib/wsystem.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wsystem, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL wsystem)(wchar_t const *__cmd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsystem))(__cmd); })
#else /* (__CRT_HAVE_system || __CRT_HAVE___libc_system || ((__CRT_HAVE_shexec || __CRT_HAVE_execl || __CRT_HAVE__execl || __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __LOCAL_environ)) && (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork || __CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork))) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __wsystem_defined
#endif /* (!__CRT_HAVE_system && !__CRT_HAVE___libc_system && ((!__CRT_HAVE_shexec && !__CRT_HAVE_execl && !__CRT_HAVE__execl && !__CRT_HAVE_execv && !__CRT_HAVE__execv && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__LOCAL_environ)) || (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork && !__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork))) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !... */
#endif /* !__wsystem_defined */
#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __CRT_HAVE_wrealpath
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT_OPT(2),wchar_t *,__NOTHROW_RPC,wrealpath,(wchar_t const *__filename, wchar_t *__resolved),(__filename,__resolved))
#else /* __CRT_HAVE_wrealpath */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wfrealpathat) || (defined(__CRT_HAVE_frealpathat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))))) || ((defined(__CRT_HAVE_realpath) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_frealpathat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
#include <libc/local/parts.wchar.stdlib/wrealpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wrealpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT_OPT(2) wchar_t *__NOTHROW_RPC(__LIBCCALL wrealpath)(wchar_t const *__filename, wchar_t *__resolved) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrealpath))(__filename, __resolved); })
#endif /* (__AT_FDCWD && (__CRT_HAVE_wfrealpathat || (__CRT_HAVE_frealpathat && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_convert_mbstowcs || __CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))))) || ((__CRT_HAVE_realpath || (__AT_FDCWD && __CRT_HAVE_frealpathat)) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_convert_mbstowcs || __CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) */
#endif /* !__CRT_HAVE_wrealpath */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS)
#ifdef __CRT_HAVE_wfrealpath
__CDECLARE(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3),wchar_t *,__NOTHROW_RPC,wfrealpath,(__fd_t __fd, wchar_t *__resolved, __SIZE_TYPE__ __buflen),(__fd,__resolved,__buflen))
#elif defined(__CRT_HAVE_wfrealpath4) || (defined(__CRT_HAVE_frealpath4) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_frealpath) || defined(__CRT_HAVE_frealpath4)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
#include <libc/local/parts.wchar.stdlib/wfrealpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wfrealpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3) wchar_t *__NOTHROW_RPC(__LIBCCALL wfrealpath)(__fd_t __fd, wchar_t *__resolved, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfrealpath))(__fd, __resolved, __buflen); })
#endif /* ... */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED || __USE_KOS */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_wfrealpath4
__CDECLARE(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3),wchar_t *,__NOTHROW_RPC,wfrealpath4,(__fd_t __fd, wchar_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),(__fd,__resolved,__buflen,__flags))
#elif defined(__CRT_HAVE_frealpath4) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/parts.wchar.stdlib/wfrealpath4.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wfrealpath4, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3) wchar_t *__NOTHROW_RPC(__LIBCCALL wfrealpath4)(__fd_t __fd, wchar_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfrealpath4))(__fd, __resolved, __buflen, __flags); })
#endif /* ... */
#ifdef __CRT_HAVE_wfrealpathat
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUTS(3, 4),wchar_t *,__NOTHROW_RPC,wfrealpathat,(__fd_t __dirfd, wchar_t const *__filename, wchar_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),(__dirfd,__filename,__resolved,__buflen,__flags))
#elif defined(__CRT_HAVE_frealpathat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/parts.wchar.stdlib/wfrealpathat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wfrealpathat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUTS(3, 4) wchar_t *__NOTHROW_RPC(__LIBCCALL wfrealpathat)(__fd_t __dirfd, wchar_t const *__filename, wchar_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfrealpathat))(__dirfd, __filename, __resolved, __buflen, __flags); })
#endif /* ... */
#ifdef __CRT_HAVE_wtoi
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE__wtoi)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,wtoi,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <libc/local/parts.wchar.stdlib/wtoi.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wtoi, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL wtoi)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoi))(__nptr); })
#endif /* !... */
#ifdef __CRT_HAVE_wtol
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE__wtol)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,wtol,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <libc/local/parts.wchar.stdlib/wtol.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wtol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) long __NOTHROW_NCX(__LIBCCALL wtol)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtol))(__nptr); })
#endif /* !... */
#ifdef __LONGLONG
#ifdef __CRT_HAVE_wtoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE__wtoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,wtoll,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <libc/local/parts.wchar.stdlib/wtoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wtoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __LONGLONG __NOTHROW_NCX(__LIBCCALL wtoll)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoll))(__nptr); })
#endif /* !... */
#endif /* __LONGLONG */
#endif /* __USE_KOS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_WCHAR_STDLIB_H */
