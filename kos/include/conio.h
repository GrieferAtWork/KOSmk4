/* HASH CRC-32:0xce95a843 */
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
/* (#) Portability: DJGPP        (/include/conio.h) */
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/conio.h) */
/* (#) Portability: Windows Kits (/ucrt/conio.h) */
#ifndef _CONIO_H
#define _CONIO_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <hybrid/typecore.h>

#ifdef __USE_DOS
#include <crtdefs.h>
#include <corecrt_wconio.h>
#endif /* __USE_DOS */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t; /* Errno code (one of `E*' from <errno.h>) */
#endif /* !__errno_t_defined */

__CDECLARE_OPT(__ATTR_WUNUSED,int,__NOTHROW_NCX,_kbhit,(void),())
#if defined(__CRT_HAVE__getch_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> _getch(3), _getch_nolock(3)
 * Read a character from the console, without echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,_getch,(void),_getch_nolock,())
#elif defined(__CRT_HAVE__getch)
/* >> _getch(3), _getch_nolock(3)
 * Read a character from the console, without echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,_getch,(void),())
#endif /* ... */
#ifdef __CRT_HAVE__getch_nolock
/* >> _getch(3), _getch_nolock(3)
 * Read a character from the console, without echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,_getch_nolock,(void),())
#elif defined(__CRT_HAVE__getch)
/* >> _getch(3), _getch_nolock(3)
 * Read a character from the console, without echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,_getch_nolock,(void),_getch,())
#endif /* ... */
#if defined(__CRT_HAVE__getche_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> _getche(3), _getche_nolock(3)
 * Read a character from the console, whilst also echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,_getche,(void),_getche_nolock,())
#elif defined(__CRT_HAVE__getche)
/* >> _getche(3), _getche_nolock(3)
 * Read a character from the console, whilst also echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,_getche,(void),())
#endif /* ... */
#ifdef __CRT_HAVE__getche_nolock
/* >> _getche(3), _getche_nolock(3)
 * Read a character from the console, whilst also echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,_getche_nolock,(void),())
#elif defined(__CRT_HAVE__getche)
/* >> _getche(3), _getche_nolock(3)
 * Read a character from the console, whilst also echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,_getche_nolock,(void),_getche,())
#endif /* ... */
#if defined(__CRT_HAVE__putch_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,int,__NOTHROW_NCX,_putch,(int __ch),_putch_nolock,(__ch))
#elif defined(__CRT_HAVE__putch)
__CDECLARE(,int,__NOTHROW_NCX,_putch,(int __ch),(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/conio/_putch.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_putch, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL _putch)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_putch))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE__putch_nolock
__CDECLARE(,int,__NOTHROW_NCX,_putch_nolock,(int __ch),(__ch))
#elif defined(__CRT_HAVE__putch)
__CREDIRECT(,int,__NOTHROW_NCX,_putch_nolock,(int __ch),_putch,(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/conio/_putch_nolock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_putch_nolock, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL _putch_nolock)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_putch_nolock))(__ch); })
#endif /* ... */
#if defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,int,__NOTHROW_NCX,_ungetch,(int __ch),_ungetch_nolock,(__ch))
#elif defined(__CRT_HAVE__ungetch)
__CDECLARE(,int,__NOTHROW_NCX,_ungetch,(int __ch),(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#include <libc/local/conio/_ungetch.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ungetch, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL _ungetch)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ungetch))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE__ungetch_nolock
__CDECLARE(,int,__NOTHROW_NCX,_ungetch_nolock,(int __ch),(__ch))
#elif defined(__CRT_HAVE__ungetch)
__CREDIRECT(,int,__NOTHROW_NCX,_ungetch_nolock,(int __ch),_ungetch,(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#include <libc/local/conio/_ungetch_nolock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ungetch_nolock, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL _ungetch_nolock)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ungetch_nolock))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE__cgets
__CDECLARE(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,_cgets,(char *__restrict __buf),(__buf))
#elif defined(__CRT_HAVE__cgets_s) || (((defined(__CRT_HAVE__getch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getch)) && ((defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <libc/local/conio/_cgets.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_cgets, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL _cgets)(char *__restrict __buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cgets))(__buf); })
#endif /* ... */
#ifdef __CRT_HAVE__cgets_s
__CDECLARE(__ATTR_NONNULL((1, 3)),errno_t,__NOTHROW_NCX,_cgets_s,(char *__buf, size_t __bufsize, size_t *__restrict __p_readsize),(__buf,__bufsize,__p_readsize))
#elif ((defined(__CRT_HAVE__getch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getch)) && ((defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
#include <libc/local/conio/_cgets_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_cgets_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) errno_t __NOTHROW_NCX(__LIBCCALL _cgets_s)(char *__buf, size_t __bufsize, size_t *__restrict __p_readsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cgets_s))(__buf, __bufsize, __p_readsize); })
#endif /* ... */
#ifdef __CRT_HAVE__cputs
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_cputs,(char const *__restrict __str),(__str))
#elif (defined(__CRT_HAVE__putch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__putch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_cputs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_cputs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL _cputs)(char const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cputs))(__str); })
#endif /* ... */
#ifdef __CRT_HAVE___conio_common_vcprintf
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__conio_common_vcprintf,(__UINT64_TYPE__ __options, char const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__format,__locale,__args))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/conio/__conio_common_vcprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__conio_common_vcprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __conio_common_vcprintf)(__UINT64_TYPE__ __options, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__conio_common_vcprintf))(__options, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE___conio_common_vcprintf_s
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__conio_common_vcprintf_s,(__UINT64_TYPE__ __options, char const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__format,__locale,__args))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf_s) || defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/conio/__conio_common_vcprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__conio_common_vcprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __conio_common_vcprintf_s)(__UINT64_TYPE__ __options, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__conio_common_vcprintf_s))(__options, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE___conio_common_vcprintf_p
__CDECLARE(__ATTR_LIBC_PRINTF_P(2, 0) __ATTR_NONNULL((2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__conio_common_vcprintf_p,(__UINT64_TYPE__ __options, char const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__format,__locale,__args))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf_p) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/conio/__conio_common_vcprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__conio_common_vcprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(2, 0) __ATTR_NONNULL((2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __conio_common_vcprintf_p)(__UINT64_TYPE__ __options, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__conio_common_vcprintf_p))(__options, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE___conio_common_vcscanf
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__conio_common_vcscanf,(__UINT64_TYPE__ __options, char const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__format,__locale,__args))
#elif ((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche)) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked))))
#include <libc/local/conio/__conio_common_vcscanf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__conio_common_vcscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __conio_common_vcscanf)(__UINT64_TYPE__ __options, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__conio_common_vcscanf))(__options, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcprintf_l
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcprintf_l,(char const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE___conio_common_vcprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_vcprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcprintf_l)(char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcprintf_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcprintf_s_l
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcprintf_s_l,(char const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE___conio_common_vcprintf_s) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf_s) || defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_vcprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcprintf_s_l)(char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcprintf_s_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcprintf_p_l
__CDECLARE(__ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcprintf_p_l,(char const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE___conio_common_vcprintf_p) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf_p) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_vcprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcprintf_p_l)(char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcprintf_p_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcscanf_l
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcscanf_l,(char const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE___conio_common_vcscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche)) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/conio/_vcscanf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcscanf_l)(char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcscanf_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcscanf_s_l
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcscanf_s_l,(char const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE___conio_common_vcscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche)) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/conio/_vcscanf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcscanf_s_l)(char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcscanf_s_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcprintf
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcprintf,(char const *__format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vcprintf_l) || defined(__CRT_HAVE___conio_common_vcprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_vcprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcprintf)(char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcprintf))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcprintf_s
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcprintf_s,(char const *__format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vcprintf_s_l) || defined(__CRT_HAVE___conio_common_vcprintf_s) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf_s) || defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_vcprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcprintf_s)(char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcprintf_s))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcprintf_p
__CDECLARE(__ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcprintf_p,(char const *__format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vcprintf_p_l) || defined(__CRT_HAVE___conio_common_vcprintf_p) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf_p) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_vcprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcprintf_p)(char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcprintf_p))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcscanf
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcscanf,(char const *__format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vcscanf_l) || defined(__CRT_HAVE___conio_common_vcscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche)) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/conio/_vcscanf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcscanf)(char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcscanf))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcscanf_s
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcscanf_s,(char const *__format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vcscanf_s_l) || defined(__CRT_HAVE___conio_common_vcscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche)) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/conio/_vcscanf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcscanf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcscanf_s)(char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcscanf_s))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__cprintf
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cprintf)(char const *__format, ...) __CASMNAME_SAME("_cprintf");
#elif defined(__CRT_HAVE__vcprintf) || defined(__CRT_HAVE__vcprintf_l) || defined(__CRT_HAVE___conio_common_vcprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_cprintf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_cprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cprintf)(char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cprintf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _cprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cprintf))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__cprintf_l
__LIBC __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cprintf_l)(char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_cprintf_l");
#elif defined(__CRT_HAVE__vcprintf_l) || defined(__CRT_HAVE___conio_common_vcprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_cprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_cprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cprintf_l)(char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cprintf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _cprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cprintf_l))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__cprintf_s
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cprintf_s)(char const *__format, ...) __CASMNAME_SAME("_cprintf_s");
#elif defined(__CRT_HAVE__vcprintf_s) || defined(__CRT_HAVE__vcprintf_s_l) || defined(__CRT_HAVE___conio_common_vcprintf_s) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf_s) || defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_cprintf_s.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_cprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cprintf_s)(char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cprintf_s))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _cprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cprintf_s))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__cprintf_s_l
__LIBC __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cprintf_s_l)(char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_cprintf_s_l");
#elif defined(__CRT_HAVE__vcprintf_s_l) || defined(__CRT_HAVE___conio_common_vcprintf_s) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf_s) || defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_cprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_cprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cprintf_s_l)(char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cprintf_s_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _cprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cprintf_s_l))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__cprintf_p
__LIBC __ATTR_LIBC_PRINTF_P(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cprintf_p)(char const *__format, ...) __CASMNAME_SAME("_cprintf_p");
#elif defined(__CRT_HAVE__vcprintf_p) || defined(__CRT_HAVE__vcprintf_p_l) || defined(__CRT_HAVE___conio_common_vcprintf_p) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf_p) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_cprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_cprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cprintf_p)(char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cprintf_p))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _cprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cprintf_p))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__cprintf_p_l
__LIBC __ATTR_LIBC_PRINTF_P(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cprintf_p_l)(char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_cprintf_p_l");
#elif defined(__CRT_HAVE__vcprintf_p_l) || defined(__CRT_HAVE___conio_common_vcprintf_p) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf_p) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_cprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_cprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cprintf_p_l)(char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cprintf_p_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _cprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cprintf_p_l))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__cscanf
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cscanf)(char const *__format, ...) __CASMNAME_SAME("_cscanf");
#elif defined(__CRT_HAVE__vcscanf) || defined(__CRT_HAVE__vcscanf_l) || defined(__CRT_HAVE___conio_common_vcscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche)) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/conio/_cscanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_cscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cscanf)(char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cscanf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _cscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cscanf))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__cscanf_l
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cscanf_l)(char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_cscanf_l");
#elif defined(__CRT_HAVE__vcscanf_l) || defined(__CRT_HAVE___conio_common_vcscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche)) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/conio/_cscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_cscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cscanf_l)(char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cscanf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _cscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cscanf_l))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__cscanf_s
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cscanf_s)(char const *__format, ...) __CASMNAME_SAME("_cscanf_s");
#elif defined(__CRT_HAVE__vcscanf_s) || defined(__CRT_HAVE__vcscanf_s_l) || defined(__CRT_HAVE___conio_common_vcscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche)) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/conio/_cscanf_s.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_cscanf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cscanf_s)(char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cscanf_s))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _cscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cscanf_s))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__cscanf_s_l
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cscanf_s_l)(char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_cscanf_s_l");
#elif defined(__CRT_HAVE__vcscanf_s_l) || defined(__CRT_HAVE___conio_common_vcscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche)) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/conio/_cscanf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_cscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cscanf_s_l)(char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cscanf_s_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _cscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cscanf_s_l))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE__cgets
__CREDIRECT(__ATTR_NONNULL((1)),char *,__NOTHROW_NCX,cgets,(char *__restrict __buf),_cgets,(__buf))
#elif defined(__CRT_HAVE__cgets_s) || (((defined(__CRT_HAVE__getch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getch)) && ((defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <libc/local/conio/_cgets.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL cgets)(char *__restrict __buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cgets))(__buf); }
#endif /* ... */
#ifdef __CRT_HAVE__cputs
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,cputs,(char const *__restrict __str),_cputs,(__str))
#elif (defined(__CRT_HAVE__putch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__putch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_cputs.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL cputs)(char const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cputs))(__str); }
#endif /* ... */
#if defined(__CRT_HAVE__getch_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> _getch(3), _getch_nolock(3)
 * Read a character from the console, without echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,getch,(void),_getch_nolock,())
#elif defined(__CRT_HAVE__getch)
/* >> _getch(3), _getch_nolock(3)
 * Read a character from the console, without echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,getch,(void),_getch,())
#endif /* ... */
#if defined(__CRT_HAVE__getche_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> _getche(3), _getche_nolock(3)
 * Read a character from the console, whilst also echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,getche,(void),_getche_nolock,())
#elif defined(__CRT_HAVE__getche)
/* >> _getche(3), _getche_nolock(3)
 * Read a character from the console, whilst also echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,getche,(void),_getche,())
#endif /* ... */
#ifdef __CRT_HAVE__kbhit
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,kbhit,(void),_kbhit,())
#endif /* __CRT_HAVE__kbhit */
#if defined(__CRT_HAVE__putch_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,int,__NOTHROW_NCX,putch,(int __ch),_putch_nolock,(__ch))
#elif defined(__CRT_HAVE__putch)
__CREDIRECT(,int,__NOTHROW_NCX,putch,(int __ch),_putch,(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/conio/_putch.h>
__FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL putch)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_putch))(__ch); }
#endif /* ... */
#if defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,int,__NOTHROW_NCX,ungetch,(int __ch),_ungetch_nolock,(__ch))
#elif defined(__CRT_HAVE__ungetch)
__CREDIRECT(,int,__NOTHROW_NCX,ungetch,(int __ch),_ungetch,(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#include <libc/local/conio/_ungetch.h>
__FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL ungetch)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ungetch))(__ch); }
#endif /* ... */
#ifdef __CRT_HAVE__cprintf
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL cprintf)(char const *__format, ...) __CASMNAME("_cprintf");
#elif defined(__CRT_HAVE__vcprintf) || defined(__CRT_HAVE__vcprintf_l) || defined(__CRT_HAVE___conio_common_vcprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/conio/_cprintf.h>
#define cprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cprintf))
#endif /* ... */
#ifdef __CRT_HAVE__cscanf
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL cscanf)(char const *__format, ...) __CASMNAME("_cscanf");
#elif defined(__CRT_HAVE__vcscanf) || defined(__CRT_HAVE__vcscanf_l) || defined(__CRT_HAVE___conio_common_vcscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche)) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/conio/_cscanf.h>
#define cscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cscanf))
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_CONIO_H */
