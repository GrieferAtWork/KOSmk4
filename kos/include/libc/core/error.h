/* HASH CRC-32:0xb1cc4e76 */
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
#ifndef _LIBC_CORE_ERROR_H
#define _LIBC_CORE_ERROR_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifndef ____libc_core_error_defined
#define ____libc_core_error_defined
#ifdef __CRT_HAVE_error
#include <kos/anno.h>
#include <bits/types.h>
#include <__crt.h>
/* >> error(3)
 * Helper  function  for printing  an error  message to  `stderr' and  possibly exiting  the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `STATUS' is non-zero, follow up with a call to `exit(status)' */
__LIBC __ATTR_LIBC_PRINTF(3, 4) void (__VLIBCCALL __libc_core_error)(int __status, __errno_t __errnum, const char *__format, ...) __THROWS(...) __CASMNAME("error");
#else /* __CRT_HAVE_error */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#include <features.h>
#if defined(__LOCAL_stdout) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && defined(__LOCAL_program_invocation_short_name)
#include <libc/local/error/error.h>
/* >> error(3)
 * Helper  function  for printing  an error  message to  `stderr' and  possibly exiting  the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `STATUS' is non-zero, follow up with a call to `exit(status)' */
#define __libc_core_error __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error)
#else /* __LOCAL_stdout && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit) && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && __LOCAL_program_invocation_short_name */
#undef ____libc_core_error_defined
#endif /* !__LOCAL_stdout || (!__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit) || (!__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) || !__LOCAL_program_invocation_short_name */
#endif /* !__CRT_HAVE_error */
#endif /* !____libc_core_error_defined */
#ifndef ____libc_core_error_at_line_defined
#define ____libc_core_error_at_line_defined
#ifdef __CRT_HAVE_error_at_line
#include <kos/anno.h>
#include <bits/types.h>
#include <__crt.h>
/* >> error_at_line(3)
 * Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally,    when   `error_one_per_line'   is    non-zero,   consecutive   calls    to   this   function   that
 * pass the same values for `filename' and `line' will not produce the error message. */
__LIBC __ATTR_LIBC_PRINTF(5, 6) void (__VLIBCCALL __libc_core_error_at_line)(int __status, __errno_t __errnum, char const *__filename, unsigned int __line, char const *__format, ...) __THROWS(...) __CASMNAME("error_at_line");
#else /* __CRT_HAVE_error_at_line */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#include <features.h>
#if defined(__LOCAL_stderr) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && defined(__LOCAL_program_invocation_short_name)
#include <libc/local/error/error_at_line.h>
/* >> error_at_line(3)
 * Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally,    when   `error_one_per_line'   is    non-zero,   consecutive   calls    to   this   function   that
 * pass the same values for `filename' and `line' will not produce the error message. */
#define __libc_core_error_at_line __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(error_at_line)
#else /* __LOCAL_stderr && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit) && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && __LOCAL_program_invocation_short_name */
#undef ____libc_core_error_at_line_defined
#endif /* !__LOCAL_stderr || (!__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit) || (!__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) || !__LOCAL_program_invocation_short_name */
#endif /* !__CRT_HAVE_error_at_line */
#endif /* !____libc_core_error_at_line_defined */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_ERROR_H */
