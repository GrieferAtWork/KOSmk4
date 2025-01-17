/* HASH CRC-32:0xd3d6c07c */
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
#ifndef _PARTS_UCHAR_STDLIB_H
#define _PARTS_UCHAR_STDLIB_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* !_STDLIB_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

/************************************************************************/
/* WARNING: UTF-16 functions use DOS paths under `DOSFS_ENABLED'        */
/*          s.a. `dosfs_setenabled(3)'                                  */
/************************************************************************/

#if defined(__CRT_HAVE_mbtowc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),int,__NOTHROW_NCX,mbtoc16,(char16_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen),mbtowc,(__pwc,__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$mbtowc)
__CREDIRECT_DOS(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),int,__NOTHROW_NCX,mbtoc16,(char16_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen),mbtowc,(__pwc,__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/stdlib/mbtowc.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1) int __NOTHROW_NCX(__LIBDCALL mbtoc16)(char16_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbtowc))((__WCHAR_TYPE__ *)__pwc, __str, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/mbtoc16.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mbtoc16, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1) int __NOTHROW_NCX(__LIBDCALL mbtoc16)(char16_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbtoc16))(__pwc, __str, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_mbtowc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),int,__NOTHROW_NCX,mbtoc32,(char32_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen),mbtowc,(__pwc,__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$mbtowc)
__CREDIRECT_KOS(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),int,__NOTHROW_NCX,mbtoc32,(char32_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen),mbtowc,(__pwc,__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/stdlib/mbtowc.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1) int __NOTHROW_NCX(__LIBKCALL mbtoc32)(char32_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbtowc))((__WCHAR_TYPE__ *)__pwc, __str, __maxlen); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/mbtoc32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mbtoc32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1) int __NOTHROW_NCX(__LIBKCALL mbtoc32)(char32_t *__restrict __pwc, char const *__restrict __str, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbtoc32))(__pwc, __str, __maxlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wctomb) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_OUT_OPT(1),int,__NOTHROW_NCX,c16tomb,(char *__str, char16_t __wc),wctomb,(__str,__wc))
#elif defined(__CRT_HAVE_DOS$wctomb)
__CREDIRECT_DOS(__ATTR_OUT_OPT(1),int,__NOTHROW_NCX,c16tomb,(char *__str, char16_t __wc),wctomb,(__str,__wc))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/stdlib/wctomb.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(1) int __NOTHROW_NCX(__LIBDCALL c16tomb)(char *__str, char16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctomb))(__str, (__WCHAR_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16tomb.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16tomb, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(1) int __NOTHROW_NCX(__LIBDCALL c16tomb)(char *__str, char16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16tomb))(__str, __wc); })
#endif /* !... */
#if defined(__CRT_HAVE_wctomb) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_OUT_OPT(1),int,__NOTHROW_NCX,c32tomb,(char *__str, char32_t __wc),wctomb,(__str,__wc))
#elif defined(__CRT_HAVE_KOS$wctomb)
__CREDIRECT_KOS(__ATTR_OUT_OPT(1),int,__NOTHROW_NCX,c32tomb,(char *__str, char32_t __wc),wctomb,(__str,__wc))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/stdlib/wctomb.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(1) int __NOTHROW_NCX(__LIBKCALL c32tomb)(char *__str, char32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctomb))(__str, (__WCHAR_TYPE__)__wc); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32tomb.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32tomb, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(1) int __NOTHROW_NCX(__LIBKCALL c32tomb)(char *__str, char32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32tomb))(__str, __wc); })
#endif /* !... */
#if defined(__CRT_HAVE_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,mbstoc16s,(char16_t *__restrict __dst, char const *__restrict __src, size_t __dstlen),mbstowcs,(__dst,__src,__dstlen))
#elif defined(__CRT_HAVE_DOS$mbstowcs)
__CREDIRECT_DOS(__ATTR_IN(2) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,mbstoc16s,(char16_t *__restrict __dst, char const *__restrict __src, size_t __dstlen),mbstowcs,(__dst,__src,__dstlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/stdlib/mbstowcs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBDCALL mbstoc16s)(char16_t *__restrict __dst, char const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstowcs))((__WCHAR_TYPE__ *)__dst, __src, __dstlen); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/mbstoc16s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mbstoc16s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBDCALL mbstoc16s)(char16_t *__restrict __dst, char const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstoc16s))(__dst, __src, __dstlen); })
#endif /* !... */
#if defined(__CRT_HAVE_mbstowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,mbstoc32s,(char32_t *__restrict __dst, char const *__restrict __src, size_t __dstlen),mbstowcs,(__dst,__src,__dstlen))
#elif defined(__CRT_HAVE_KOS$mbstowcs)
__CREDIRECT_KOS(__ATTR_IN(2) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,mbstoc32s,(char32_t *__restrict __dst, char const *__restrict __src, size_t __dstlen),mbstowcs,(__dst,__src,__dstlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/stdlib/mbstowcs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBKCALL mbstoc32s)(char32_t *__restrict __dst, char const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstowcs))((__WCHAR_TYPE__ *)__dst, __src, __dstlen); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/mbstoc32s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mbstoc32s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBKCALL mbstoc32s)(char32_t *__restrict __dst, char const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstoc32s))(__dst, __src, __dstlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,c16stombs,(char *__restrict __dst, char16_t const *__restrict __src, size_t __dstlen),wcstombs,(__dst,__src,__dstlen))
#elif defined(__CRT_HAVE_DOS$wcstombs)
__CREDIRECT_DOS(__ATTR_IN(2) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,c16stombs,(char *__restrict __dst, char16_t const *__restrict __src, size_t __dstlen),wcstombs,(__dst,__src,__dstlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/stdlib/wcstombs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBDCALL c16stombs)(char *__restrict __dst, char16_t const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstombs))(__dst, (__WCHAR_TYPE__ const *)__src, __dstlen); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16stombs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBDCALL c16stombs)(char *__restrict __dst, char16_t const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stombs))(__dst, __src, __dstlen); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,c32stombs,(char *__restrict __dst, char32_t const *__restrict __src, size_t __dstlen),wcstombs,(__dst,__src,__dstlen))
#elif defined(__CRT_HAVE_KOS$wcstombs)
__CREDIRECT_KOS(__ATTR_IN(2) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,c32stombs,(char *__restrict __dst, char32_t const *__restrict __src, size_t __dstlen),wcstombs,(__dst,__src,__dstlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/stdlib/wcstombs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBKCALL c32stombs)(char *__restrict __dst, char32_t const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstombs))(__dst, (__WCHAR_TYPE__ const *)__src, __dstlen); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32stombs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBKCALL c32stombs)(char *__restrict __dst, char32_t const *__restrict __src, size_t __dstlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stombs))(__dst, __src, __dstlen); })
#endif /* !... */
#ifndef __c16system_defined
#define __c16system_defined
#if defined(__CRT_HAVE_wsystem) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(,int,__NOTHROW_RPC,c16system,(char16_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE_DOS$wsystem)
__CREDIRECT_DOS(,int,__NOTHROW_RPC,c16system,(char16_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE__wsystem) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(,int,__NOTHROW_RPC,c16system,(char16_t const *__cmd),_wsystem,(__cmd))
#elif defined(__CRT_HAVE_DOS$_wsystem)
__CREDIRECT_DOS(,int,__NOTHROW_RPC,c16system,(char16_t const *__cmd),_wsystem,(__cmd))
#else /* ... */
#include <libc/template/environ.h>
#if (defined(__CRT_HAVE_system) || defined(__CRT_HAVE___libc_system) || ((defined(__CRT_HAVE_shexec) || defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork) || defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.stdlib/wsystem.h>
__FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBDCALL c16system)(char16_t const *__cmd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsystem))((__WCHAR_TYPE__ const *)__cmd); }
#elif (defined(__CRT_HAVE_system) || defined(__CRT_HAVE___libc_system) || ((defined(__CRT_HAVE_shexec) || defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork) || defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)))) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.uchar.stdlib/c16system.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16system, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBDCALL c16system)(char16_t const *__cmd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16system))(__cmd); })
#else /* ... */
#undef __c16system_defined
#endif /* !... */
#endif /* !... */
#endif /* !__c16system_defined */
#ifndef __c32system_defined
#define __c32system_defined
#if defined(__CRT_HAVE_wsystem) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(,int,__NOTHROW_RPC,c32system,(char32_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE_KOS$wsystem)
__CREDIRECT_KOS(,int,__NOTHROW_RPC,c32system,(char32_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE__wsystem) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(,int,__NOTHROW_RPC,c32system,(char32_t const *__cmd),_wsystem,(__cmd))
#elif defined(__CRT_HAVE_KOS$_wsystem)
__CREDIRECT_KOS(,int,__NOTHROW_RPC,c32system,(char32_t const *__cmd),_wsystem,(__cmd))
#else /* ... */
#include <libc/template/environ.h>
#if (defined(__CRT_HAVE_system) || defined(__CRT_HAVE___libc_system) || ((defined(__CRT_HAVE_shexec) || defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork) || defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.stdlib/wsystem.h>
__FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBKCALL c32system)(char32_t const *__cmd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsystem))((__WCHAR_TYPE__ const *)__cmd); }
#elif (defined(__CRT_HAVE_system) || defined(__CRT_HAVE___libc_system) || ((defined(__CRT_HAVE_shexec) || defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork) || defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)))) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.uchar.stdlib/c32system.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32system, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBKCALL c32system)(char32_t const *__cmd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32system))(__cmd); })
#else /* ... */
#undef __c32system_defined
#endif /* !... */
#endif /* !... */
#endif /* !__c32system_defined */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#if defined(__CRT_HAVE_wrealpath) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT_OPT(2),char16_t *,__NOTHROW_RPC,c16realpath,(char16_t const *__filename, char16_t *__resolved),wrealpath,(__filename,__resolved))
#elif defined(__CRT_HAVE_DOS$wrealpath)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT_OPT(2),char16_t *,__NOTHROW_RPC,c16realpath,(char16_t const *__filename, char16_t *__resolved),wrealpath,(__filename,__resolved))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wfrealpathat) || (defined(__CRT_HAVE_frealpathat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))))) || ((defined(__CRT_HAVE_realpath) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_frealpathat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2)
#include <libc/local/parts.wchar.stdlib/wrealpath.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT_OPT(2) char16_t *__NOTHROW_RPC(__LIBDCALL c16realpath)(char16_t const *__filename, char16_t *__resolved) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrealpath))((__WCHAR_TYPE__ const *)__filename, (__WCHAR_TYPE__ *)__resolved); }
#elif (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wfrealpathat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wfrealpathat) || (defined(__CRT_HAVE_frealpathat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_frealpathat) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))))) || ((defined(__CRT_HAVE_realpath) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_frealpathat))) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
#include <libc/local/parts.uchar.stdlib/c16realpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16realpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT_OPT(2) char16_t *__NOTHROW_RPC(__LIBDCALL c16realpath)(char16_t const *__filename, char16_t *__resolved) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16realpath))(__filename, __resolved); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_wrealpath) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT_OPT(2),char32_t *,__NOTHROW_RPC,c32realpath,(char32_t const *__filename, char32_t *__resolved),wrealpath,(__filename,__resolved))
#elif defined(__CRT_HAVE_KOS$wrealpath)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT_OPT(2),char32_t *,__NOTHROW_RPC,c32realpath,(char32_t const *__filename, char32_t *__resolved),wrealpath,(__filename,__resolved))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_wfrealpathat) || (defined(__CRT_HAVE_frealpathat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))))) || ((defined(__CRT_HAVE_realpath) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_frealpathat))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4)
#include <libc/local/parts.wchar.stdlib/wrealpath.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT_OPT(2) char32_t *__NOTHROW_RPC(__LIBKCALL c32realpath)(char32_t const *__filename, char32_t *__resolved) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wrealpath))((__WCHAR_TYPE__ const *)__filename, (__WCHAR_TYPE__ *)__resolved); }
#elif (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wfrealpathat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wfrealpathat) || (defined(__CRT_HAVE_frealpathat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_frealpathat) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_KOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))))) || ((defined(__CRT_HAVE_realpath) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_frealpathat))) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_KOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
#include <libc/local/parts.uchar.stdlib/c32realpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32realpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT_OPT(2) char32_t *__NOTHROW_RPC(__LIBKCALL c32realpath)(char32_t const *__filename, char32_t *__resolved) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32realpath))(__filename, __resolved); })
#endif /* ... */
#endif /* !... */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS)
#if defined(__CRT_HAVE_wfrealpath) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3),char16_t *,__NOTHROW_RPC,c16frealpath,(__fd_t __fd, char16_t *__resolved, __SIZE_TYPE__ __buflen),wfrealpath,(__fd,__resolved,__buflen))
#elif defined(__CRT_HAVE_DOS$wfrealpath)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3),char16_t *,__NOTHROW_RPC,c16frealpath,(__fd_t __fd, char16_t *__resolved, __SIZE_TYPE__ __buflen),wfrealpath,(__fd,__resolved,__buflen))
#elif defined(__CRT_HAVE_wfrealpath4) || (defined(__CRT_HAVE_frealpath4) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_frealpath) || defined(__CRT_HAVE_frealpath4)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2)
#include <libc/local/parts.wchar.stdlib/wfrealpath.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3) char16_t *__NOTHROW_RPC(__LIBDCALL c16frealpath)(__fd_t __fd, char16_t *__resolved, __SIZE_TYPE__ __buflen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfrealpath))(__fd, (__WCHAR_TYPE__ *)__resolved, __buflen); }
#elif defined(__CRT_HAVE_DOS$wfrealpath4) || (defined(__CRT_HAVE_frealpath4) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_frealpath) || defined(__CRT_HAVE_frealpath4)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
#include <libc/local/parts.uchar.stdlib/c16frealpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16frealpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3) char16_t *__NOTHROW_RPC(__LIBDCALL c16frealpath)(__fd_t __fd, char16_t *__resolved, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16frealpath))(__fd, __resolved, __buflen); })
#endif /* ... */
#if defined(__CRT_HAVE_wfrealpath) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3),char32_t *,__NOTHROW_RPC,c32frealpath,(__fd_t __fd, char32_t *__resolved, __SIZE_TYPE__ __buflen),wfrealpath,(__fd,__resolved,__buflen))
#elif defined(__CRT_HAVE_KOS$wfrealpath)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3),char32_t *,__NOTHROW_RPC,c32frealpath,(__fd_t __fd, char32_t *__resolved, __SIZE_TYPE__ __buflen),wfrealpath,(__fd,__resolved,__buflen))
#elif defined(__CRT_HAVE_wfrealpath4) || (defined(__CRT_HAVE_frealpath4) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_frealpath) || defined(__CRT_HAVE_frealpath4)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4)
#include <libc/local/parts.wchar.stdlib/wfrealpath.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3) char32_t *__NOTHROW_RPC(__LIBKCALL c32frealpath)(__fd_t __fd, char32_t *__resolved, __SIZE_TYPE__ __buflen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfrealpath))(__fd, (__WCHAR_TYPE__ *)__resolved, __buflen); }
#elif defined(__CRT_HAVE_KOS$wfrealpath4) || (defined(__CRT_HAVE_frealpath4) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_KOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))) || ((defined(__CRT_HAVE_frealpath) || defined(__CRT_HAVE_frealpath4)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_KOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
#include <libc/local/parts.uchar.stdlib/c32frealpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32frealpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3) char32_t *__NOTHROW_RPC(__LIBKCALL c32frealpath)(__fd_t __fd, char32_t *__resolved, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32frealpath))(__fd, __resolved, __buflen); })
#endif /* ... */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED || __USE_KOS */

#ifdef __USE_KOS
#if defined(__CRT_HAVE_wfrealpath4) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3),char16_t *,__NOTHROW_RPC,c16frealpath4,(__fd_t __fd, char16_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfrealpath4,(__fd,__resolved,__buflen,__flags))
#elif defined(__CRT_HAVE_DOS$wfrealpath4)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3),char16_t *,__NOTHROW_RPC,c16frealpath4,(__fd_t __fd, char16_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfrealpath4,(__fd,__resolved,__buflen,__flags))
#elif defined(__CRT_HAVE_frealpath4) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.stdlib/wfrealpath4.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3) char16_t *__NOTHROW_RPC(__LIBDCALL c16frealpath4)(__fd_t __fd, char16_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfrealpath4))(__fd, (__WCHAR_TYPE__ *)__resolved, __buflen, __flags); }
#elif defined(__CRT_HAVE_frealpath4) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/parts.uchar.stdlib/c16frealpath4.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16frealpath4, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3) char16_t *__NOTHROW_RPC(__LIBDCALL c16frealpath4)(__fd_t __fd, char16_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16frealpath4))(__fd, __resolved, __buflen, __flags); })
#endif /* ... */
#if defined(__CRT_HAVE_wfrealpath4) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3),char32_t *,__NOTHROW_RPC,c32frealpath4,(__fd_t __fd, char32_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfrealpath4,(__fd,__resolved,__buflen,__flags))
#elif defined(__CRT_HAVE_KOS$wfrealpath4)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3),char32_t *,__NOTHROW_RPC,c32frealpath4,(__fd_t __fd, char32_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfrealpath4,(__fd,__resolved,__buflen,__flags))
#elif defined(__CRT_HAVE_frealpath4) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.stdlib/wfrealpath4.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3) char32_t *__NOTHROW_RPC(__LIBKCALL c32frealpath4)(__fd_t __fd, char32_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfrealpath4))(__fd, (__WCHAR_TYPE__ *)__resolved, __buflen, __flags); }
#elif defined(__CRT_HAVE_frealpath4) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_KOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/parts.uchar.stdlib/c32frealpath4.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32frealpath4, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_OUTS(2, 3) char32_t *__NOTHROW_RPC(__LIBKCALL c32frealpath4)(__fd_t __fd, char32_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32frealpath4))(__fd, __resolved, __buflen, __flags); })
#endif /* ... */
#if defined(__CRT_HAVE_wfrealpathat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUTS(3, 4),char16_t *,__NOTHROW_RPC,c16frealpathat,(__fd_t __dirfd, char16_t const *__filename, char16_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfrealpathat,(__dirfd,__filename,__resolved,__buflen,__flags))
#elif defined(__CRT_HAVE_DOS$wfrealpathat)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUTS(3, 4),char16_t *,__NOTHROW_RPC,c16frealpathat,(__fd_t __dirfd, char16_t const *__filename, char16_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfrealpathat,(__dirfd,__filename,__resolved,__buflen,__flags))
#elif defined(__CRT_HAVE_frealpathat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.stdlib/wfrealpathat.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUTS(3, 4) char16_t *__NOTHROW_RPC(__LIBDCALL c16frealpathat)(__fd_t __dirfd, char16_t const *__filename, char16_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfrealpathat))(__dirfd, (__WCHAR_TYPE__ const *)__filename, (__WCHAR_TYPE__ *)__resolved, __buflen, __flags); }
#elif defined(__CRT_HAVE_frealpathat) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_DOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/parts.uchar.stdlib/c16frealpathat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16frealpathat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUTS(3, 4) char16_t *__NOTHROW_RPC(__LIBDCALL c16frealpathat)(__fd_t __dirfd, char16_t const *__filename, char16_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16frealpathat))(__dirfd, __filename, __resolved, __buflen, __flags); })
#endif /* ... */
#if defined(__CRT_HAVE_wfrealpathat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUTS(3, 4),char32_t *,__NOTHROW_RPC,c32frealpathat,(__fd_t __dirfd, char32_t const *__filename, char32_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfrealpathat,(__dirfd,__filename,__resolved,__buflen,__flags))
#elif defined(__CRT_HAVE_KOS$wfrealpathat)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUTS(3, 4),char32_t *,__NOTHROW_RPC,c32frealpathat,(__fd_t __dirfd, char32_t const *__filename, char32_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfrealpathat,(__dirfd,__filename,__resolved,__buflen,__flags))
#elif defined(__CRT_HAVE_frealpathat) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.stdlib/wfrealpathat.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUTS(3, 4) char32_t *__NOTHROW_RPC(__LIBKCALL c32frealpathat)(__fd_t __dirfd, char32_t const *__filename, char32_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wfrealpathat))(__dirfd, (__WCHAR_TYPE__ const *)__filename, (__WCHAR_TYPE__ *)__resolved, __buflen, __flags); }
#elif defined(__CRT_HAVE_frealpathat) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_convert_mbstowcs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcs) || ((defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_convert_mbstowcsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)) || defined(__CRT_HAVE_KOS$format_waprintf_printer) || (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && ((defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/parts.uchar.stdlib/c32frealpathat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32frealpathat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUTS(3, 4) char32_t *__NOTHROW_RPC(__LIBKCALL c32frealpathat)(__fd_t __dirfd, char32_t const *__filename, char32_t *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32frealpathat))(__dirfd, __filename, __resolved, __buflen, __flags); })
#endif /* ... */
#endif /* __USE_KOS */

#ifdef __USE_KOS
#if defined(__CRT_HAVE_wcsto32_r) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcsto32_r)
/* >> wcsto32_r(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto32_r.h>
/* >> wcsto32_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __INT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto32_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16sto32_r.h>
/* >> wcsto32_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sto32_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __INT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto32_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sto32_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsto32_r) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_KOS$wcsto32_r)
/* >> wcsto32_r(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto32_r.h>
/* >> wcsto32_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __INT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto32_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32sto32_r.h>
/* >> wcsto32_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sto32_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __INT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto32_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sto32_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou32_r) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcstou32_r)
/* >> wcstou32_r(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou32_r.h>
/* >> wcstou32_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __UINT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou32_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16stou32_r.h>
/* >> wcstou32_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stou32_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __UINT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou32_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stou32_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou32_r) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_KOS$wcstou32_r)
/* >> wcstou32_r(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou32_r.h>
/* >> wcstou32_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __UINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou32_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32stou32_r.h>
/* >> wcstou32_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stou32_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __UINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou32_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stou32_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol) && __SIZEOF_LONG__ == 4
/* >> wcsto32(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto32)
/* >> wcsto32(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax) && __SIZEOF_INTMAX_T__ == 4
/* >> wcsto32(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto32.h>
/* >> wcsto32(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto32)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16sto32.h>
/* >> wcsto32(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sto32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto32)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sto32))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstol) && __SIZEOF_LONG__ == 4
/* >> wcsto32(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoll) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoq) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto32)
/* >> wcsto32(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoimax) && __SIZEOF_INTMAX_T__ == 4
/* >> wcsto32(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto32.h>
/* >> wcsto32(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto32)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32sto32.h>
/* >> wcsto32(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sto32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto32)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sto32))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul) && __SIZEOF_LONG__ == 4
/* >> wcstou32(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou32)
/* >> wcstou32(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax) && __SIZEOF_INTMAX_T__ == 4
/* >> wcstou32(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou32.h>
/* >> wcstou32(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou32)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16stou32.h>
/* >> wcstou32(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stou32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou32)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stou32))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoul) && __SIZEOF_LONG__ == 4
/* >> wcstou32(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoull) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstouq) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou32)
/* >> wcstou32(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoumax) && __SIZEOF_INTMAX_T__ == 4
/* >> wcstou32(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou32.h>
/* >> wcstou32(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou32)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32stou32.h>
/* >> wcstou32(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stou32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou32)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stou32))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __UINT64_TYPE__
#if defined(__CRT_HAVE_wcsto64_r) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcsto64_r)
/* >> wcsto64_r(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto64_r.h>
/* >> wcsto64_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __INT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto64_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16sto64_r.h>
/* >> wcsto64_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sto64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __INT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto64_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sto64_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsto64_r) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_KOS$wcsto64_r)
/* >> wcsto64_r(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto64_r.h>
/* >> wcsto64_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __INT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto64_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32sto64_r.h>
/* >> wcsto64_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sto64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __INT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto64_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sto64_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou64_r) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcstou64_r)
/* >> wcstou64_r(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou64_r.h>
/* >> wcstou64_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __UINT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou64_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16stou64_r.h>
/* >> wcstou64_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stou64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __UINT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou64_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stou64_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou64_r) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_KOS$wcstou64_r)
/* >> wcstou64_r(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou64_r.h>
/* >> wcstou64_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __UINT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou64_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32stou64_r.h>
/* >> wcstou64_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stou64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __UINT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou64_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stou64_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol) && __SIZEOF_LONG__ == 8
/* >> wcsto64(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto64)
/* >> wcsto64(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoi64)
/* >> wcsto64(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax) && __SIZEOF_INTMAX_T__ == 8
/* >> wcsto64(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto64.h>
/* >> wcsto64(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto64)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16sto64.h>
/* >> wcsto64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sto64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto64)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sto64))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstol) && __SIZEOF_LONG__ == 8
/* >> wcsto64(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoll) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoq) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcsto64)
/* >> wcsto64(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoi64)
/* >> wcsto64(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoimax) && __SIZEOF_INTMAX_T__ == 8
/* >> wcsto64(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto64.h>
/* >> wcsto64(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto64)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32sto64.h>
/* >> wcsto64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sto64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto64)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sto64))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoul) && __SIZEOF_LONG__ == 8
/* >> wcstou64(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoull) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstouq) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstou64)
/* >> wcstou64(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoui64)
/* >> wcstou64(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoumax) && __SIZEOF_INTMAX_T__ == 8
/* >> wcstou64(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou64.h>
/* >> wcstou64(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou64)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16stou64.h>
/* >> wcstou64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stou64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou64)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stou64))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoul) && __SIZEOF_LONG__ == 8
/* >> wcstou64(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoull) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstouq) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou64)
/* >> wcstou64(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoui64)
/* >> wcstou64(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoumax) && __SIZEOF_INTMAX_T__ == 8
/* >> wcstou64(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou64.h>
/* >> wcstou64(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou64)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32stou64.h>
/* >> wcstou64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stou64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou64)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stou64))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#if defined(__CRT_HAVE_wcsto32_r) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstol_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),long,__NOTHROW_NCX,c16stol_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcsto32_r) && __SIZEOF_LONG__ == 4
/* >> wcstol_r(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),long,__NOTHROW_NCX,c16stol_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcsto64_r) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstol_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),long,__NOTHROW_NCX,c16stol_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcsto64_r) && __SIZEOF_LONG__ == 8
/* >> wcstol_r(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),long,__NOTHROW_NCX,c16stol_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto32_r.h>
/* >> wcstol_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) long __NOTHROW_NCX(__LIBDCALL c16stol_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto64_r.h>
/* >> wcstol_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) long __NOTHROW_NCX(__LIBDCALL c16stol_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstol_r.h>
/* >> wcstol_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) long __NOTHROW_NCX(__LIBDCALL c16stol_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16stol_r.h>
/* >> wcstol_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stol_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) long __NOTHROW_NCX(__LIBDCALL c16stol_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stol_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsto32_r) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstol_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),long,__NOTHROW_NCX,c32stol_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_KOS$wcsto32_r) && __SIZEOF_LONG__ == 4
/* >> wcstol_r(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),long,__NOTHROW_NCX,c32stol_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcsto64_r) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstol_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),long,__NOTHROW_NCX,c32stol_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_KOS$wcsto64_r) && __SIZEOF_LONG__ == 8
/* >> wcstol_r(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),long,__NOTHROW_NCX,c32stol_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto32_r.h>
/* >> wcstol_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) long __NOTHROW_NCX(__LIBKCALL c32stol_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto64_r.h>
/* >> wcstol_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) long __NOTHROW_NCX(__LIBKCALL c32stol_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstol_r.h>
/* >> wcstol_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) long __NOTHROW_NCX(__LIBKCALL c32stol_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32stol_r.h>
/* >> wcstol_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stol_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) long __NOTHROW_NCX(__LIBKCALL c32stol_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stol_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou32_r) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoul_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),unsigned long,__NOTHROW_NCX,c16stoul_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcstou32_r) && __SIZEOF_LONG__ == 4
/* >> wcstoul_r(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),unsigned long,__NOTHROW_NCX,c16stoul_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcstou64_r) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoul_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),unsigned long,__NOTHROW_NCX,c16stoul_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcstou64_r) && __SIZEOF_LONG__ == 8
/* >> wcstoul_r(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),unsigned long,__NOTHROW_NCX,c16stoul_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou32_r.h>
/* >> wcstoul_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) unsigned long __NOTHROW_NCX(__LIBDCALL c16stoul_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou64_r.h>
/* >> wcstoul_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) unsigned long __NOTHROW_NCX(__LIBDCALL c16stoul_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoul_r.h>
/* >> wcstoul_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) unsigned long __NOTHROW_NCX(__LIBDCALL c16stoul_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16stoul_r.h>
/* >> wcstoul_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoul_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) unsigned long __NOTHROW_NCX(__LIBDCALL c16stoul_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoul_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou32_r) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoul_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),unsigned long,__NOTHROW_NCX,c32stoul_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_KOS$wcstou32_r) && __SIZEOF_LONG__ == 4
/* >> wcstoul_r(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),unsigned long,__NOTHROW_NCX,c32stoul_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcstou64_r) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoul_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),unsigned long,__NOTHROW_NCX,c32stoul_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_KOS$wcstou64_r) && __SIZEOF_LONG__ == 8
/* >> wcstoul_r(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),unsigned long,__NOTHROW_NCX,c32stoul_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou32_r.h>
/* >> wcstoul_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) unsigned long __NOTHROW_NCX(__LIBKCALL c32stoul_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou64_r.h>
/* >> wcstoul_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) unsigned long __NOTHROW_NCX(__LIBKCALL c32stoul_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoul_r.h>
/* >> wcstoul_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) unsigned long __NOTHROW_NCX(__LIBKCALL c32stoul_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32stoul_r.h>
/* >> wcstoul_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoul_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) unsigned long __NOTHROW_NCX(__LIBKCALL c32stoul_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoul_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#ifdef __LONGLONG
#if defined(__CRT_HAVE_wcsto64_r) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__LONGLONG,__NOTHROW_NCX,c16stoll_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcsto64_r) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll_r(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__LONGLONG,__NOTHROW_NCX,c16stoll_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcsto32_r) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoll_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__LONGLONG,__NOTHROW_NCX,c16stoll_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcsto32_r) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoll_r(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__LONGLONG,__NOTHROW_NCX,c16stoll_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto64_r.h>
/* >> wcstoll_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoll_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto32_r.h>
/* >> wcstoll_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoll_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoll_r.h>
/* >> wcstoll_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoll_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16stoll_r.h>
/* >> wcstoll_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoll_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16stoll_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoll_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsto64_r) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__LONGLONG,__NOTHROW_NCX,c32stoll_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_KOS$wcsto64_r) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll_r(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__LONGLONG,__NOTHROW_NCX,c32stoll_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcsto32_r) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoll_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__LONGLONG,__NOTHROW_NCX,c32stoll_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_KOS$wcsto32_r) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoll_r(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__LONGLONG,__NOTHROW_NCX,c32stoll_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto64_r.h>
/* >> wcstoll_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoll_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto32_r.h>
/* >> wcstoll_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoll_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoll_r.h>
/* >> wcstoll_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoll_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32stoll_r.h>
/* >> wcstoll_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoll_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32stoll_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoll_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou64_r) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__ULONGLONG,__NOTHROW_NCX,c16stoull_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcstou64_r) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull_r(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__ULONGLONG,__NOTHROW_NCX,c16stoull_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcstou32_r) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstoull_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__ULONGLONG,__NOTHROW_NCX,c16stoull_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcstou32_r) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoull_r(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__ULONGLONG,__NOTHROW_NCX,c16stoull_r,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou64_r.h>
/* >> wcstoull_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stoull_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou32_r.h>
/* >> wcstoull_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stoull_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstoull_r.h>
/* >> wcstoull_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stoull_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16stoull_r.h>
/* >> wcstoull_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stoull_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __ULONGLONG __NOTHROW_NCX(__LIBDCALL c16stoull_r)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stoull_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou64_r) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__ULONGLONG,__NOTHROW_NCX,c32stoull_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_KOS$wcstou64_r) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull_r(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__ULONGLONG,__NOTHROW_NCX,c32stoull_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcstou32_r) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstoull_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__ULONGLONG,__NOTHROW_NCX,c32stoull_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_KOS$wcstou32_r) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoull_r(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__ULONGLONG,__NOTHROW_NCX,c32stoull_r,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou64_r.h>
/* >> wcstoull_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stoull_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou32_r.h>
/* >> wcstoull_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stoull_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstoull_r.h>
/* >> wcstoull_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stoull_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_r))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __error); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32stoull_r.h>
/* >> wcstoull_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stoull_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __ULONGLONG __NOTHROW_NCX(__LIBKCALL c32stoull_r)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stoull_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#endif /* __LONGLONG */

#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstol_l) && __SIZEOF_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstol_l) && __SIZEOF_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstol_l) && __SIZEOF_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto32_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcsto32_l)
/* >> wcsto32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c16sto32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto32_l.h>
/* >> wcsto32_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto32_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16sto32_l.h>
/* >> wcsto32_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sto32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto32_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sto32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstol_l) && __SIZEOF_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstol_l) && __SIZEOF_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstol_l) && __SIZEOF_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto32_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcsto32_l)
/* >> wcsto32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,c32sto32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto32_l.h>
/* >> wcsto32_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto32_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32sto32_l.h>
/* >> wcsto32_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sto32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto32_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sto32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoul_l) && __SIZEOF_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoul_l) && __SIZEOF_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoul_l) && __SIZEOF_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou32_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstou32_l)
/* >> wcstou32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c16stou32_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou32_l.h>
/* >> wcstou32_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou32_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16stou32_l.h>
/* >> wcstou32_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stou32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT32_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou32_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stou32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoul_l) && __SIZEOF_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoul_l) && __SIZEOF_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoul_l) && __SIZEOF_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou32_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstou32_l)
/* >> wcstou32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,c32stou32_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou32_l.h>
/* >> wcstou32_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou32_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32stou32_l.h>
/* >> wcstou32_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stou32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou32_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stou32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */

#ifdef __UINT64_TYPE__
#if defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstol_l) && __SIZEOF_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstol_l) && __SIZEOF_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstol_l) && __SIZEOF_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcsto64_l)
/* >> wcsto64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoi64_l)
/* >> wcsto64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c16sto64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsto64_l.h>
/* >> wcsto64_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto64_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16sto64_l.h>
/* >> wcsto64_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16sto64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16sto64_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16sto64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstol_l) && __SIZEOF_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstol_l) && __SIZEOF_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstol_l) && __SIZEOF_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcsto64_l)
/* >> wcsto64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoi64_l)
/* >> wcsto64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,c32sto64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsto64_l.h>
/* >> wcsto64_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto64_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32sto64_l.h>
/* >> wcsto64_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32sto64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32sto64_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32sto64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoul_l) && __SIZEOF_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoul_l) && __SIZEOF_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoul_l) && __SIZEOF_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstou64_l)
/* >> wcstou64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoui64_l)
/* >> wcstou64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_DOS$_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c16stou64_l,(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcstou64_l.h>
/* >> wcstou64_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou64_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16stou64_l.h>
/* >> wcstou64_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16stou64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT64_TYPE__ __NOTHROW_NCX(__LIBDCALL c16stou64_l)(char16_t const *__restrict __nptr, char16_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stou64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoul_l) && __SIZEOF_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoul_l) && __SIZEOF_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoul_l) && __SIZEOF_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstou64_l)
/* >> wcstou64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoui64_l)
/* >> wcstou64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,c32stou64_l,(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcstou64_l.h>
/* >> wcstou64_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou64_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_l))((__WCHAR_TYPE__ const *)__nptr, (__WCHAR_TYPE__ **)__endptr, __base, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32stou64_l.h>
/* >> wcstou64_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32stou64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT64_TYPE__ __NOTHROW_NCX(__LIBKCALL c32stou64_l)(char32_t const *__restrict __nptr, char32_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32stou64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_XOPEN2K8 */
#if defined(__CRT_HAVE_wtoi) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtoi)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoi)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_INT__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtoi64,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoi64) && __SIZEOF_INT__ == 8
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c16toi,(char16_t const *__nptr),_wtoi64,(__nptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.stdlib/wtoi.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_NCX(__LIBDCALL c16toi)(char16_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoi))((__WCHAR_TYPE__ const *)__nptr); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16toi.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16toi, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_NCX(__LIBDCALL c16toi)(char16_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16toi))(__nptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wtoi) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtoi)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoi)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_INT__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtoi64,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoi64) && __SIZEOF_INT__ == 8
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,c32toi,(char32_t const *__nptr),_wtoi64,(__nptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.stdlib/wtoi.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_NCX(__LIBKCALL c32toi)(char32_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoi))((__WCHAR_TYPE__ const *)__nptr); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32toi.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32toi, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_NCX(__LIBKCALL c32toi)(char32_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32toi))(__nptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wtol) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtol)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtol)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtoi64,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c16tol,(char16_t const *__nptr),_wtoi64,(__nptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.stdlib/wtol.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) long __NOTHROW_NCX(__LIBDCALL c16tol)(char16_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtol))((__WCHAR_TYPE__ const *)__nptr); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16tol.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16tol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) long __NOTHROW_NCX(__LIBDCALL c16tol)(char16_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16tol))(__nptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wtol) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtol)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtol)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtoi64,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,c32tol,(char32_t const *__nptr),_wtoi64,(__nptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.stdlib/wtol.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) long __NOTHROW_NCX(__LIBKCALL c32tol)(char32_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtol))((__WCHAR_TYPE__ const *)__nptr); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32tol.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32tol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) long __NOTHROW_NCX(__LIBKCALL c32tol)(char32_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32tol))(__nptr); })
#endif /* !... */
#ifdef __LONGLONG
#if defined(__CRT_HAVE_wtoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE_DOS$wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtoi64,(__nptr))
#elif defined(__CRT_HAVE_DOS$_wtoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c16toll,(char16_t const *__nptr),_wtoi64,(__nptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.stdlib/wtoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16toll)(char16_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoll))((__WCHAR_TYPE__ const *)__nptr); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c16toll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16toll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __LONGLONG __NOTHROW_NCX(__LIBDCALL c16toll)(char16_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16toll))(__nptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wtoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE_KOS$wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtoi64,(__nptr))
#elif defined(__CRT_HAVE_KOS$_wtoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,c32toll,(char32_t const *__nptr),_wtoi64,(__nptr))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.stdlib/wtoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32toll)(char32_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoll))((__WCHAR_TYPE__ const *)__nptr); }
#else /* ... */
#include <libc/local/parts.uchar.stdlib/c32toll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32toll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __LONGLONG __NOTHROW_NCX(__LIBKCALL c32toll)(char32_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32toll))(__nptr); })
#endif /* !... */
#endif /* __LONGLONG */
#endif /* __USE_KOS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_UCHAR_STDLIB_H */
