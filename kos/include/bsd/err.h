/* HASH CRC-32:0x4d122621 */
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
/* (#) Portability: libbsd (/include/bsd/err.h) */
#ifndef _BSD_ERR_H
#define _BSD_ERR_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <err.h>
#include <kos/anno.h>
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __warnc_defined
#define __warnc_defined 1
#ifdef __CRT_HAVE_warnc
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
__LIBC __ATTR_LIBC_PRINTF(1, 2) void (__VLIBCCALL warnc)(__errno_t __used_errno, char const *__format, ...) __THROWS(...) __CASMNAME_SAME("warnc");
#else /* __CRT_HAVE_warnc */
#include <__crt.h>
#include <libc/local/program_invocation_name.h>
#include <features.h>
#if defined(__CRT_HAVE_vwarnc) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/err/warnc.h>
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(warnc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 2) void (__VLIBCCALL warnc)(__errno_t __used_errno, char const *__format, ...) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(warnc))(__used_errno, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define warnc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(warnc))
#endif /* !__cplusplus */
#else /* __CRT_HAVE_vwarnc || (!__NO_STDSTREAMS && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#undef __warnc_defined
#endif /* !__CRT_HAVE_vwarnc && (__NO_STDSTREAMS || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock)) */
#endif /* !__CRT_HAVE_warnc */
#endif /* !__warnc_defined */
#ifndef __vwarnc_defined
#define __vwarnc_defined 1
#ifdef __CRT_HAVE_vwarnc
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
__CDECLARE_VOID(__ATTR_LIBC_PRINTF(1, 0),__THROWING,vwarnc,(__errno_t __used_errno, char const *__format, __builtin_va_list __args),(__used_errno,__format,__args))
#else /* __CRT_HAVE_vwarnc */
#include <__crt.h>
#include <libc/local/program_invocation_name.h>
#include <features.h>
#if !defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/err/vwarnc.h>
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
__NAMESPACE_LOCAL_USING_OR_IMPL(vwarnc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) void (__LIBCCALL vwarnc)(__errno_t __used_errno, char const *__format, __builtin_va_list __args) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwarnc))(__used_errno, __format, __args); })
#else /* !__NO_STDSTREAMS && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef __vwarnc_defined
#endif /* __NO_STDSTREAMS || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__CRT_HAVE_vwarnc */
#endif /* !__vwarnc_defined */
#ifndef __errc_defined
#define __errc_defined 1
#ifdef __CRT_HAVE_errc
/* Same as `warnc()', but follow up by calling `exit(status)' */
__LIBC __ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 3) void (__VLIBCCALL errc)(int __status, __errno_t __used_errno, char const *__format, ...) __THROWS(...) __CASMNAME_SAME("errc");
#else /* __CRT_HAVE_errc */
#include <__crt.h>
#include <libc/local/program_invocation_name.h>
#include <features.h>
#if defined(__CRT_HAVE_verrc) || ((defined(__CRT_HAVE_vwarnc) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)))
#include <libc/local/err/errc.h>
/* Same as `warnc()', but follow up by calling `exit(status)' */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(errc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 3) void (__VLIBCCALL errc)(int __status, __errno_t __used_errno, char const *__format, ...) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(errc))(__status, __used_errno, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define errc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(errc))
#endif /* !__cplusplus */
#else /* __CRT_HAVE_verrc || ((__CRT_HAVE_vwarnc || (!__NO_STDSTREAMS && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock))) && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit)) */
#undef __errc_defined
#endif /* !__CRT_HAVE_verrc && ((!__CRT_HAVE_vwarnc && (__NO_STDSTREAMS || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock))) || (!__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit)) */
#endif /* !__CRT_HAVE_errc */
#endif /* !__errc_defined */
#ifndef __verrc_defined
#define __verrc_defined 1
#ifdef __CRT_HAVE_verrc
/* Same as `warnc()', but follow up by calling `exit(status)' */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 0),__THROWING,verrc,(int __status, __errno_t __used_errno, char const *__format, __builtin_va_list __args),(__status,__used_errno,__format,__args))
#else /* __CRT_HAVE_verrc */
#include <__crt.h>
#include <libc/local/program_invocation_name.h>
#include <features.h>
#if (defined(__CRT_HAVE_vwarnc) || (!defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit))
#include <libc/local/err/verrc.h>
/* Same as `warnc()', but follow up by calling `exit(status)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(verrc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN __ATTR_LIBC_PRINTF(2, 0) void (__LIBCCALL verrc)(int __status, __errno_t __used_errno, char const *__format, __builtin_va_list __args) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(verrc))(__status, __used_errno, __format, __args); })
#else /* (__CRT_HAVE_vwarnc || (!__NO_STDSTREAMS && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock))) && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit) */
#undef __verrc_defined
#endif /* (!__CRT_HAVE_vwarnc && (__NO_STDSTREAMS || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock))) || (!__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit) */
#endif /* !__CRT_HAVE_verrc */
#endif /* !__verrc_defined */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BSD_ERR_H */
