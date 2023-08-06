/* HASH CRC-32:0xaf951850 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/err.h) */
/* (#) Portability: DragonFly BSD (/include/err.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/err.h) */
/* (#) Portability: FreeBSD       (/include/err.h) */
/* (#) Portability: GNU C Library (/misc/err.h) */
/* (#) Portability: GNU Hurd      (/usr/include/err.h) */
/* (#) Portability: NetBSD        (/include/err.h) */
/* (#) Portability: OpenBSD       (/include/err.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/err.h) */
/* (#) Portability: diet libc     (/include/err.h) */
/* (#) Portability: libbsd        (/include/bsd/err.h) */
/* (#) Portability: libc6         (/include/err.h) */
/* (#) Portability: mintlib       (/include/err.h) */
/* (#) Portability: musl libc     (/include/err.h) */
/* (#) Portability: uClibc        (/include/err.h) */
#ifndef _ERR_H
#define _ERR_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <kos/anno.h>
#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_warn
/* >> warn(3), vwarn(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
__LIBC __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(1, 2) void __NOTHROW_CB(__VLIBCCALL warn)(char const *__format, ...) __CASMNAME_SAME("warn");
#else /* __CRT_HAVE_warn */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#if defined(__CRT_HAVE_vwarn) || defined(__CRT_HAVE_vwarnc) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/err/warn.h>
/* >> warn(3), vwarn(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(warn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(1, 2) void __NOTHROW_CB(__VLIBCCALL warn)(char const *__format, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(warn))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define warn(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(warn))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __CRT_HAVE_vwarn || __CRT_HAVE_vwarnc || (__LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#endif /* !__CRT_HAVE_warn */
#ifdef __CRT_HAVE_vwarn
/* >> warn(3), vwarn(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
__CDECLARE_VOID(__ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(1, 0),__NOTHROW_CB,vwarn,(char const *__format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE_vwarn */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#if defined(__CRT_HAVE_vwarnc) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/err/vwarn.h>
/* >> warn(3), vwarn(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
__NAMESPACE_LOCAL_USING_OR_IMPL(vwarn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(1, 0) void __NOTHROW_CB(__LIBCCALL vwarn)(char const *__format, __builtin_va_list __args) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwarn))(__format, __args); })
#endif /* __CRT_HAVE_vwarnc || (__LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#endif /* !__CRT_HAVE_vwarn */

#ifdef __USE_BSD
#ifndef __warnc_defined
#define __warnc_defined
#ifdef __CRT_HAVE_warnc
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
__LIBC __ATTR_IN_OPT(2) __ATTR_LIBC_PRINTF(2, 3) void __NOTHROW_CB(__VLIBCCALL warnc)(__errno_t __used_errno, char const *__format, ...) __CASMNAME_SAME("warnc");
#else /* __CRT_HAVE_warnc */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#if defined(__CRT_HAVE_vwarnc) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/err/warnc.h>
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(warnc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(2) __ATTR_LIBC_PRINTF(2, 3) void __NOTHROW_CB(__VLIBCCALL warnc)(__errno_t __used_errno, char const *__format, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(warnc))(__used_errno, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define warnc(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(warnc))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* __CRT_HAVE_vwarnc || (__LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#undef __warnc_defined
#endif /* !__CRT_HAVE_vwarnc && (!__LOCAL_stderr || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_vfprintf && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock)) */
#endif /* !__CRT_HAVE_warnc */
#endif /* !__warnc_defined */
#ifndef __vwarnc_defined
#define __vwarnc_defined
#ifdef __CRT_HAVE_vwarnc
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
__CDECLARE_VOID(__ATTR_IN_OPT(2) __ATTR_LIBC_PRINTF(2, 0),__NOTHROW_CB,vwarnc,(__errno_t __used_errno, char const *__format, __builtin_va_list __args),(__used_errno,__format,__args))
#else /* __CRT_HAVE_vwarnc */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#if defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/err/vwarnc.h>
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
__NAMESPACE_LOCAL_USING_OR_IMPL(vwarnc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(2) __ATTR_LIBC_PRINTF(2, 0) void __NOTHROW_CB(__LIBCCALL vwarnc)(__errno_t __used_errno, char const *__format, __builtin_va_list __args) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwarnc))(__used_errno, __format, __args); })
#else /* __LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef __vwarnc_defined
#endif /* !__LOCAL_stderr || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_vfprintf && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__CRT_HAVE_vwarnc */
#endif /* !__vwarnc_defined */
#endif /* __USE_BSD */

#ifdef __CRT_HAVE_warnx
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
__LIBC __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(1, 2) void __NOTHROW_CB(__VLIBCCALL warnx)(char const *__format, ...) __CASMNAME_SAME("warnx");
#else /* __CRT_HAVE_warnx */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#if defined(__CRT_HAVE_vwarnx) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/err/warnx.h>
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(warnx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(1, 2) void __NOTHROW_CB(__VLIBCCALL warnx)(char const *__format, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(warnx))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define warnx(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(warnx))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __CRT_HAVE_vwarnx || (__LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#endif /* !__CRT_HAVE_warnx */
#ifdef __CRT_HAVE_vwarnx
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
__CDECLARE_VOID(__ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(1, 0),__NOTHROW_CB,vwarnx,(char const *__format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE_vwarnx */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#if defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/err/vwarnx.h>
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
__NAMESPACE_LOCAL_USING_OR_IMPL(vwarnx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(1) __ATTR_LIBC_PRINTF(1, 0) void __NOTHROW_CB(__LIBCCALL vwarnx)(char const *__format, __builtin_va_list __args) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwarnx))(__format, __args); })
#endif /* __LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#endif /* !__CRT_HAVE_vwarnx */
#ifdef __CRT_HAVE_err
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
__LIBC __ATTR_NORETURN __ATTR_IN_OPT(2) __ATTR_LIBC_PRINTF(2, 3) void (__VLIBCCALL err)(int __status, char const *__format, ...) __THROWS(...) __CASMNAME_SAME("err");
#else /* __CRT_HAVE_err */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#if defined(__CRT_HAVE_verr) || defined(__CRT_HAVE_verrc) || ((defined(__CRT_HAVE_vwarnc) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit)))
#include <libc/local/err/err.h>
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(err, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN __ATTR_IN_OPT(2) __ATTR_LIBC_PRINTF(2, 3) void (__VLIBCCALL err)(int __status, char const *__format, ...) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(err))(__status, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define err(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(err))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __CRT_HAVE_verr || __CRT_HAVE_verrc || ((__CRT_HAVE_vwarnc || (__LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock))) && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit || __CRT_HAVE_xexit)) */
#endif /* !__CRT_HAVE_err */
#ifdef __CRT_HAVE_verr
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_IN_OPT(2) __ATTR_LIBC_PRINTF(2, 0),__THROWING(...),verr,(int __status, char const *__format, __builtin_va_list __args),(__status,__format,__args))
#else /* __CRT_HAVE_verr */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#if defined(__CRT_HAVE_verrc) || ((defined(__CRT_HAVE_vwarnc) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit)))
#include <libc/local/err/verr.h>
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(verr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN __ATTR_IN_OPT(2) __ATTR_LIBC_PRINTF(2, 0) void (__LIBCCALL verr)(int __status, char const *__format, __builtin_va_list __args) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(verr))(__status, __format, __args); })
#endif /* __CRT_HAVE_verrc || ((__CRT_HAVE_vwarnc || (__LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock))) && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit || __CRT_HAVE_xexit)) */
#endif /* !__CRT_HAVE_verr */

#ifdef __USE_BSD
#ifndef __errc_defined
#define __errc_defined
#ifdef __CRT_HAVE_errc
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
__LIBC __ATTR_NORETURN __ATTR_IN_OPT(3) __ATTR_LIBC_PRINTF(3, 4) void (__VLIBCCALL errc)(int __status, __errno_t __used_errno, char const *__format, ...) __THROWS(...) __CASMNAME_SAME("errc");
#else /* __CRT_HAVE_errc */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#if defined(__CRT_HAVE_verrc) || ((defined(__CRT_HAVE_vwarnc) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit)))
#include <libc/local/err/errc.h>
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(errc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN __ATTR_IN_OPT(3) __ATTR_LIBC_PRINTF(3, 4) void (__VLIBCCALL errc)(int __status, __errno_t __used_errno, char const *__format, ...) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(errc))(__status, __used_errno, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define errc(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(errc))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* __CRT_HAVE_verrc || ((__CRT_HAVE_vwarnc || (__LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock))) && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit || __CRT_HAVE_xexit)) */
#undef __errc_defined
#endif /* !__CRT_HAVE_verrc && ((!__CRT_HAVE_vwarnc && (!__LOCAL_stderr || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_vfprintf && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock))) || (!__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit && !__CRT_HAVE_xexit)) */
#endif /* !__CRT_HAVE_errc */
#endif /* !__errc_defined */
#ifndef __verrc_defined
#define __verrc_defined
#ifdef __CRT_HAVE_verrc
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_IN_OPT(3) __ATTR_LIBC_PRINTF(3, 0),__THROWING(...),verrc,(int __status, __errno_t __used_errno, char const *__format, __builtin_va_list __args),(__status,__used_errno,__format,__args))
#else /* __CRT_HAVE_verrc */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#if (defined(__CRT_HAVE_vwarnc) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit))
#include <libc/local/err/verrc.h>
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(verrc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN __ATTR_IN_OPT(3) __ATTR_LIBC_PRINTF(3, 0) void (__LIBCCALL verrc)(int __status, __errno_t __used_errno, char const *__format, __builtin_va_list __args) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(verrc))(__status, __used_errno, __format, __args); })
#else /* (__CRT_HAVE_vwarnc || (__LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock))) && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit || __CRT_HAVE_xexit) */
#undef __verrc_defined
#endif /* (!__CRT_HAVE_vwarnc && (!__LOCAL_stderr || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_vfprintf && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock))) || (!__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit && !__CRT_HAVE_xexit) */
#endif /* !__CRT_HAVE_verrc */
#endif /* !__verrc_defined */
#endif /* __USE_BSD */

#ifdef __CRT_HAVE_errx
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
__LIBC __ATTR_NORETURN __ATTR_IN_OPT(2) __ATTR_LIBC_PRINTF(2, 3) void (__VLIBCCALL errx)(int __status, char const *__format, ...) __THROWS(...) __CASMNAME_SAME("errx");
#else /* __CRT_HAVE_errx */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#if defined(__CRT_HAVE_verrx) || ((defined(__CRT_HAVE_vwarnx) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit)))
#include <libc/local/err/errx.h>
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(errx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN __ATTR_IN_OPT(2) __ATTR_LIBC_PRINTF(2, 3) void (__VLIBCCALL errx)(int __status, char const *__format, ...) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(errx))(__status, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define errx(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(errx))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __CRT_HAVE_verrx || ((__CRT_HAVE_vwarnx || (__LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock))) && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit || __CRT_HAVE_xexit)) */
#endif /* !__CRT_HAVE_errx */
#ifdef __CRT_HAVE_verrx
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_IN_OPT(2) __ATTR_LIBC_PRINTF(2, 0),__THROWING(...),verrx,(int __status, char const *__format, __builtin_va_list __args),(__status,__format,__args))
#else /* __CRT_HAVE_verrx */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#if (defined(__CRT_HAVE_vwarnx) || (defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit))
#include <libc/local/err/verrx.h>
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(verrx, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN __ATTR_IN_OPT(2) __ATTR_LIBC_PRINTF(2, 0) void (__LIBCCALL verrx)(int __status, char const *__format, __builtin_va_list __args) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(verrx))(__status, __format, __args); })
#endif /* (__CRT_HAVE_vwarnx || (__LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock))) && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit || __CRT_HAVE_xexit) */
#endif /* !__CRT_HAVE_verrx */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ERR_H */
