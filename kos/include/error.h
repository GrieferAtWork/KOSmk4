/* HASH CRC-32:0x7eab9149 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/error.h) */
/* (#) Portability: GNU C Library (/misc/error.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/include/error.h) */
/* (#) Portability: libc6         (/include/error.h) */
/* (#) Portability: uClibc        (/include/error.h) */
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
/* >> error(3)
 * Helper  function  for printing  an error  message to  `stderr' and  possibly exiting  the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `status' is non-zero, follow up with a call to `exit(status)' */
#if __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_FAST_USING_OR_IMPL(error, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) void (__VLIBCCALL error)(int __status, __errno_t __errnum, const char *__format, ...) __THROWS(...) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(error))(__status, __errnum, __format, __builtin_va_arg_pack()); })
#else /* __has_builtin(__builtin_va_arg_pack) */
#define error(...) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(error))(__VA_ARGS__)
#endif /* !__has_builtin(__builtin_va_arg_pack) */
#elif defined(__CRT_HAVE_error)
/* >> error(3)
 * Helper  function  for printing  an error  message to  `stderr' and  possibly exiting  the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `status' is non-zero, follow up with a call to `exit(status)' */
__LIBC __ATTR_LIBC_PRINTF(3, 4) void (__VLIBCCALL error)(int __status, __errno_t __errnum, const char *__format, ...) __THROWS(...) __CASMNAME_SAME("error");
#else /* ... */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#include <features.h>
#if defined(__LOCAL_stdout) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && defined(__LOCAL_program_invocation_short_name)
#include <libc/local/error/error.h>
/* >> error(3)
 * Helper  function  for printing  an error  message to  `stderr' and  possibly exiting  the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `status' is non-zero, follow up with a call to `exit(status)' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(error, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) void (__VLIBCCALL error)(int __status, __errno_t __errnum, const char *__format, ...) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error))(__status, __errnum, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define error(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __LOCAL_stdout && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit) && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && __LOCAL_program_invocation_short_name */
#endif /* !... */
#ifdef __fast_error_at_line_defined
/* >> error_at_line(3)
 * Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally,  when `error_one_per_line' is non-zero, consecutive calls to  this function that pass the same values
 * for `filename' and `line' will not produce the error message. */
#if __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_FAST_USING_OR_IMPL(error_at_line, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(5, 6) void (__VLIBCCALL error_at_line)(int __status, __errno_t __errnum, char const *__filename, unsigned int __line, char const *__format, ...) __THROWS(...) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(error_at_line))(__status, __errnum, __filename, __line, __format, __builtin_va_arg_pack()); })
#else /* __has_builtin(__builtin_va_arg_pack) */
#define error_at_line(...) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(error_at_line))(__VA_ARGS__)
#endif /* !__has_builtin(__builtin_va_arg_pack) */
#elif defined(__CRT_HAVE_error_at_line)
/* >> error_at_line(3)
 * Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally,  when `error_one_per_line' is non-zero, consecutive calls to  this function that pass the same values
 * for `filename' and `line' will not produce the error message. */
__LIBC __ATTR_LIBC_PRINTF(5, 6) void (__VLIBCCALL error_at_line)(int __status, __errno_t __errnum, char const *__filename, unsigned int __line, char const *__format, ...) __THROWS(...) __CASMNAME_SAME("error_at_line");
#else /* ... */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#include <features.h>
#if defined(__LOCAL_stderr) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && defined(__LOCAL_program_invocation_short_name)
#include <libc/local/error/error_at_line.h>
/* >> error_at_line(3)
 * Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally,  when `error_one_per_line' is non-zero, consecutive calls to  this function that pass the same values
 * for `filename' and `line' will not produce the error message. */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(error_at_line, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(5, 6) void (__VLIBCCALL error_at_line)(int __status, __errno_t __errnum, char const *__filename, unsigned int __line, char const *__format, ...) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_at_line))(__status, __errnum, __filename, __line, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define error_at_line(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_at_line))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __LOCAL_stderr && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit) && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && __LOCAL_program_invocation_short_name */
#endif /* !... */

#ifndef error_print_progname
#ifdef __LOCAL_error_print_progname
#define error_print_progname __LOCAL_error_print_progname
#elif defined(__CRT_HAVE_error_print_progname)
/* Override for printing the program name.
 * When non-NULL,  this  function  should:
 *  - fflush(stdout);
 *  - fprintf(stderr, "%s:", basename(argv[0])); */
__LIBC void (__LIBKCALL *error_print_progname)(void);
#define error_print_progname error_print_progname
#endif /* ... */
#endif /* !error_print_progname */

#ifndef error_message_count
#ifdef __LOCAL_error_message_count
#define error_message_count __LOCAL_error_message_count
#elif defined(__CRT_HAVE_error_message_count)
/* Incremented by one each time `error()' or `error_at_line()' is called. */
__LIBC unsigned int error_message_count;
#define error_message_count error_message_count
#endif /* ... */
#endif /* !error_message_count */

#ifndef error_one_per_line
#ifdef __LOCAL_error_one_per_line
#define error_one_per_line __LOCAL_error_one_per_line
#elif defined(__CRT_HAVE_error_one_per_line)
/* Mode configuration for `error_at_line()'.
 * When non-zero, consecutive calls to `error_at_line()' that pass the same
 * values for `filename'  and `line'  will not produce  the error  message.
 * The default value is ZERO(0) */
__LIBC int error_one_per_line;
#define error_one_per_line error_one_per_line
#endif /* ... */
#endif /* !error_one_per_line */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ERROR_H */
