/* HASH CRC-32:0x71b39635 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ERROR_H
#define _ERROR_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <bits/types.h>
#include <kos/anno.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/error.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */

#ifdef __CC__

__SYSDECL_BEGIN

#ifdef __fast_error_defined
/* Helper function for printing an error message to `stderr' and possibly exiting the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `STATUS' is non-zero, follow up with a call to `exit(status)' */
__NAMESPACE_FAST_USING_OR_IMPL(error, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) void (__VLIBCCALL error)(int __status, __errno_t __errnum, const char *__format, ...) __THROWS(...) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(error))(__status, __errnum, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_error)
/* Helper function for printing an error message to `stderr' and possibly exiting the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `STATUS' is non-zero, follow up with a call to `exit(status)' */
__LIBC __ATTR_LIBC_PRINTF(3, 4) void (__VLIBCCALL error)(int __status, __errno_t __errnum, const char *__format, ...) __THROWS(...) __CASMNAME_SAME("error");
#else /* ... */
#include <__crt.h>
#include <local/program_invocation_name.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && defined(__LOCAL_program_invocation_short_name)
#include <local/error/error.h>
/* Helper function for printing an error message to `stderr' and possibly exiting the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `STATUS' is non-zero, follow up with a call to `exit(status)' */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(error, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) void (__VLIBCCALL error)(int __status, __errno_t __errnum, const char *__format, ...) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error))(__status, __errnum, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define error (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error))
#endif /* !__cplusplus */
#endif /* !__NO_STDSTREAMS && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit) && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) && (__CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) && __LOCAL_program_invocation_short_name */
#endif /* !... */
#ifdef __fast_error_at_line_defined
/* Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally, when `error_one_per_line' is non-zero, consecutive calls to this function that
 * pass the same values for `filename' and `line' will not produce the error message. */
__NAMESPACE_FAST_USING_OR_IMPL(error_at_line, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(5, 6) void (__VLIBCCALL error_at_line)(int __status, __errno_t __errnum, char const *__filename, unsigned int __line, char const *__format, ...) __THROWS(...) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(error_at_line))(__status, __errnum, __filename, __line, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_error_at_line)
/* Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally, when `error_one_per_line' is non-zero, consecutive calls to this function that
 * pass the same values for `filename' and `line' will not produce the error message. */
__LIBC __ATTR_LIBC_PRINTF(5, 6) void (__VLIBCCALL error_at_line)(int __status, __errno_t __errnum, char const *__filename, unsigned int __line, char const *__format, ...) __THROWS(...) __CASMNAME_SAME("error_at_line");
#else /* ... */
#include <__crt.h>
#include <local/program_invocation_name.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && (defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)) && defined(__LOCAL_program_invocation_short_name)
#include <local/error/error_at_line.h>
/* Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally, when `error_one_per_line' is non-zero, consecutive calls to this function that
 * pass the same values for `filename' and `line' will not produce the error message. */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(error_at_line, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(5, 6) void (__VLIBCCALL error_at_line)(int __status, __errno_t __errnum, char const *__filename, unsigned int __line, char const *__format, ...) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_at_line))(__status, __errnum, __filename, __line, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define error_at_line (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_at_line))
#endif /* !__cplusplus */
#endif /* !__NO_STDSTREAMS && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit) && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) && (__CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite) && __LOCAL_program_invocation_short_name */
#endif /* !... */

#ifndef error_print_progname
#ifdef __CRT_HAVE_error_print_progname
/* Override for printing the program name.
 * When non-NULL, this function should:
 *  - fflush(stdout);
 *  - fprintf(stderr, "%s: ", basename(argv[0])); */
__LIBC void (__LIBKCALL *error_print_progname)(void);
#define error_print_progname error_print_progname
#endif /* __CRT_HAVE_error_print_progname */
#endif /* !error_print_progname */

#ifndef error_message_count
#ifdef __CRT_HAVE_error_print_progname
/* Incremented by one each time `error()' or `error_at_line()' is called. */
__LIBC unsigned int error_message_count;
#define error_message_count error_message_count
#endif /* __CRT_HAVE_error_print_progname */
#endif /* !error_message_count */

#ifndef error_one_per_line
#ifdef __CRT_HAVE_error_one_per_line
/* Mode configuration for `error_at_line()'.
 * When non-zero, consecutive calls to `error_at_line()' that pass the same
 * values for `filename' and `line' will not produce the error message.
 * The default value is ZERO(0) */
__LIBC int error_one_per_line;
#define error_one_per_line error_one_per_line
#endif /* __CRT_HAVE_error_one_per_line */
#endif /* !error_one_per_line */


__SYSDECL_END

#endif /* __CC__ */

#endif /* !_ERROR_H */
