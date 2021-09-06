/* HASH CRC-32:0xe87b0a8 */
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
#ifndef GUARD_LIBC_AUTO_ERROR_C
#define GUARD_LIBC_AUTO_ERROR_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "error.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "../user/string.h"

DECL_BEGIN

/* Use the KOS-special `libc_strerrordesc_np()' functions, rather than strerror()
 * below (thus making  these functions  a bit  more light-weight  by having  just
 * a bit less dependencies) */
#define strerror        libc_strerrordesc_np
#define libc_strerror   libc_strerrordesc_np
#include "../libc/globals.h" /* For norel access to global variables */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <libc/local/stdstreams.h>
#ifndef __LOCAL_error_print_progname
#ifdef error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#elif defined(__CRT_HAVE_error_print_progname)
#ifdef __NO_ASMNAME
__LIBC void (__LIBKCALL *__LOCAL_error_print_progname)(void) __ASMNAME("error_print_progname");
#else /* __NO_ASMNAME */
__LIBC void (__LIBKCALL *error_print_progname)(void);
#define error_print_progname         error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#endif /* !__NO_ASMNAME */
#endif /* ... */
#endif /* !__LOCAL_error_print_progname */
#ifndef __LOCAL_error_message_count
#ifdef error_message_count
#define __LOCAL_error_message_count error_message_count
#elif defined(__CRT_HAVE_error_message_count)
#ifdef __NO_ASMNAME
__LIBC unsigned int __LOCAL_error_message_count __ASMNAME("error_message_count");
#else /* __NO_ASMNAME */
__LIBC unsigned int error_message_count;
#define error_message_count         error_message_count
#define __LOCAL_error_message_count error_message_count
#endif /* !__NO_ASMNAME */
#endif /* ... */
#endif /* !__LOCAL_error_message_count */
#include <libc/local/program_invocation_name.h>
/* Helper  function  for printing  an error  message to  `stderr' and  possibly exiting  the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `STATUS' is non-zero, follow up with a call to `exit(status)' */
INTERN ATTR_SECTION(".text.crt.dos.error") ATTR_LIBC_PRINTF(3, 4) void
(VLIBDCALL libd_error)(int status,
                       errno_t errnum,
                       const char *format,
                       ...) THROWS(...) {
#ifdef __LOCAL_error_print_progname
	if (__LOCAL_error_print_progname) {
		(*__LOCAL_error_print_progname)();
	} else
#endif /* __LOCAL_error_print_progname */
	{
		libc_fflush(stdout);
		libc_fprintf(stderr, "%s: ", __LOCAL_program_invocation_short_name);
	}
	if (format) {
		va_list args;
		va_start(args, format);
		libc_vfprintf(stderr, format, args);
		va_end(args);
	}
#ifdef __LOCAL_error_message_count
	++__LOCAL_error_message_count;
#endif /* __LOCAL_error_message_count */
	if (errnum != 0)
		libc_fprintf(stderr, ": %s", libc_strerror(errnum));
	libc_fputc('\n', stderr);
	if (status != 0)
		libc_exit(status);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <libc/local/stdstreams.h>
#ifndef __LOCAL_error_print_progname
#ifdef error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#elif defined(__CRT_HAVE_error_print_progname)
#ifdef __NO_ASMNAME
__LIBC void (__LIBKCALL *__LOCAL_error_print_progname)(void) __ASMNAME("error_print_progname");
#else /* __NO_ASMNAME */
__LIBC void (__LIBKCALL *error_print_progname)(void);
#define error_print_progname         error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#endif /* !__NO_ASMNAME */
#endif /* ... */
#endif /* !__LOCAL_error_print_progname */
#ifndef __LOCAL_error_message_count
#ifdef error_message_count
#define __LOCAL_error_message_count error_message_count
#elif defined(__CRT_HAVE_error_message_count)
#ifdef __NO_ASMNAME
__LIBC unsigned int __LOCAL_error_message_count __ASMNAME("error_message_count");
#else /* __NO_ASMNAME */
__LIBC unsigned int error_message_count;
#define error_message_count         error_message_count
#define __LOCAL_error_message_count error_message_count
#endif /* !__NO_ASMNAME */
#endif /* ... */
#endif /* !__LOCAL_error_message_count */
#include <libc/local/program_invocation_name.h>
/* Helper  function  for printing  an error  message to  `stderr' and  possibly exiting  the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `STATUS' is non-zero, follow up with a call to `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_LIBC_PRINTF(3, 4) void
(VLIBCCALL libc_error)(int status,
                       errno_t errnum,
                       const char *format,
                       ...) THROWS(...) {
#ifdef __LOCAL_error_print_progname
	if (__LOCAL_error_print_progname) {
		(*__LOCAL_error_print_progname)();
	} else
#endif /* __LOCAL_error_print_progname */
	{
		libc_fflush(stdout);
		libc_fprintf(stderr, "%s: ", __LOCAL_program_invocation_short_name);
	}
	if (format) {
		va_list args;
		va_start(args, format);
		libc_vfprintf(stderr, format, args);
		va_end(args);
	}
#ifdef __LOCAL_error_message_count
	++__LOCAL_error_message_count;
#endif /* __LOCAL_error_message_count */
	if (errnum != 0)
		libc_fprintf(stderr, ": %s", libc_strerror(errnum));
	libc_fputc('\n', stderr);
	if (status != 0)
		libc_exit(status);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <libc/local/stdstreams.h>
#include <libc/local/program_invocation_name.h>
#ifndef __LOCAL_error_print_progname
#ifdef error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#elif defined(__CRT_HAVE_error_print_progname)
#ifdef __NO_ASMNAME
__LIBC void (__LIBKCALL *__LOCAL_error_print_progname)(void) __ASMNAME("error_print_progname");
#else /* __NO_ASMNAME */
__LIBC void (__LIBKCALL *error_print_progname)(void);
#define error_print_progname         error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#endif /* !__NO_ASMNAME */
#endif /* ... */
#endif /* !__LOCAL_error_print_progname */
#ifndef __LOCAL_error_one_per_line
#ifdef error_one_per_line
#define __LOCAL_error_one_per_line error_one_per_line
#elif defined(__CRT_HAVE_error_one_per_line)
#ifdef __NO_ASMNAME
__LIBC int __LOCAL_error_one_per_line __ASMNAME("error_one_per_line");
#else /* __NO_ASMNAME */
__LIBC int error_one_per_line;
#define error_one_per_line         error_one_per_line
#define __LOCAL_error_one_per_line error_one_per_line
#endif /* !__NO_ASMNAME */
#endif /* ... */
#endif /* !__LOCAL_error_one_per_line */
#ifndef __LOCAL_error_message_count
#ifdef error_message_count
#define __LOCAL_error_message_count error_message_count
#elif defined(__CRT_HAVE_error_message_count)
#ifdef __NO_ASMNAME
__LIBC unsigned int __LOCAL_error_message_count __ASMNAME("error_message_count");
#else /* __NO_ASMNAME */
__LIBC unsigned int error_message_count;
#define error_message_count         error_message_count
#define __LOCAL_error_message_count error_message_count
#endif /* !__NO_ASMNAME */
#endif /* ... */
#endif /* !__LOCAL_error_message_count */
/* Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally,    when   `error_one_per_line'   is    non-zero,   consecutive   calls    to   this   function   that
 * pass the same values for `filename' and `line' will not produce the error message. */
INTERN ATTR_SECTION(".text.crt.dos.error") ATTR_LIBC_PRINTF(5, 6) void
(VLIBDCALL libd_error_at_line)(int status,
                               errno_t errnum,
                               char const *filename,
                               unsigned int line,
                               char const *format,
                               ...) THROWS(...) {
#ifdef __LOCAL_error_one_per_line
	static char const *last_filename = NULL;
	static unsigned int last_line = 0;
	if (__LOCAL_error_one_per_line != 0 &&
	    line == last_line && filename && last_filename &&
	    (filename == last_filename || libc_strcmp(filename, last_filename) == 0)) {
		/* Don't print the same error more than once */
	} else
#endif /* __LOCAL_error_one_per_line */
	{
#ifdef __LOCAL_error_one_per_line
		filename = last_filename;
		line     = last_line;
#endif /* __LOCAL_error_one_per_line */
#ifdef __LOCAL_error_print_progname
		if (__LOCAL_error_print_progname) {
			(*__LOCAL_error_print_progname)();
		} else
#endif /* __LOCAL_error_print_progname */
		{
			libc_fflush(stdout);
			libc_fprintf(stderr, "%s:", __LOCAL_program_invocation_short_name);
		}
		libc_fprintf(stderr, "%s:%u: ", filename, line);
		if (format) {
			va_list args;
			va_start(args, format);
			libc_vfprintf(stderr, format, args);
			va_end(args);
		}
#ifdef __LOCAL_error_message_count
		++__LOCAL_error_message_count;
#endif /* __LOCAL_error_message_count */
		if (errnum != 0)
			libc_fprintf(stderr, ": %s", libc_strerror(errnum));
		libc_fputc('\n', stderr);
		if (status != 0)
			libc_exit(status);
	}
	if (status != 0)
		libc_exit(status);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <libc/local/stdstreams.h>
#include <libc/local/program_invocation_name.h>
#ifndef __LOCAL_error_print_progname
#ifdef error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#elif defined(__CRT_HAVE_error_print_progname)
#ifdef __NO_ASMNAME
__LIBC void (__LIBKCALL *__LOCAL_error_print_progname)(void) __ASMNAME("error_print_progname");
#else /* __NO_ASMNAME */
__LIBC void (__LIBKCALL *error_print_progname)(void);
#define error_print_progname         error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#endif /* !__NO_ASMNAME */
#endif /* ... */
#endif /* !__LOCAL_error_print_progname */
#ifndef __LOCAL_error_one_per_line
#ifdef error_one_per_line
#define __LOCAL_error_one_per_line error_one_per_line
#elif defined(__CRT_HAVE_error_one_per_line)
#ifdef __NO_ASMNAME
__LIBC int __LOCAL_error_one_per_line __ASMNAME("error_one_per_line");
#else /* __NO_ASMNAME */
__LIBC int error_one_per_line;
#define error_one_per_line         error_one_per_line
#define __LOCAL_error_one_per_line error_one_per_line
#endif /* !__NO_ASMNAME */
#endif /* ... */
#endif /* !__LOCAL_error_one_per_line */
#ifndef __LOCAL_error_message_count
#ifdef error_message_count
#define __LOCAL_error_message_count error_message_count
#elif defined(__CRT_HAVE_error_message_count)
#ifdef __NO_ASMNAME
__LIBC unsigned int __LOCAL_error_message_count __ASMNAME("error_message_count");
#else /* __NO_ASMNAME */
__LIBC unsigned int error_message_count;
#define error_message_count         error_message_count
#define __LOCAL_error_message_count error_message_count
#endif /* !__NO_ASMNAME */
#endif /* ... */
#endif /* !__LOCAL_error_message_count */
/* Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally,    when   `error_one_per_line'   is    non-zero,   consecutive   calls    to   this   function   that
 * pass the same values for `filename' and `line' will not produce the error message. */
INTERN ATTR_SECTION(".text.crt.error") ATTR_LIBC_PRINTF(5, 6) void
(VLIBCCALL libc_error_at_line)(int status,
                               errno_t errnum,
                               char const *filename,
                               unsigned int line,
                               char const *format,
                               ...) THROWS(...) {
#ifdef __LOCAL_error_one_per_line
	static char const *last_filename = NULL;
	static unsigned int last_line = 0;
	if (__LOCAL_error_one_per_line != 0 &&
	    line == last_line && filename && last_filename &&
	    (filename == last_filename || libc_strcmp(filename, last_filename) == 0)) {
		/* Don't print the same error more than once */
	} else
#endif /* __LOCAL_error_one_per_line */
	{
#ifdef __LOCAL_error_one_per_line
		filename = last_filename;
		line     = last_line;
#endif /* __LOCAL_error_one_per_line */
#ifdef __LOCAL_error_print_progname
		if (__LOCAL_error_print_progname) {
			(*__LOCAL_error_print_progname)();
		} else
#endif /* __LOCAL_error_print_progname */
		{
			libc_fflush(stdout);
			libc_fprintf(stderr, "%s:", __LOCAL_program_invocation_short_name);
		}
		libc_fprintf(stderr, "%s:%u: ", filename, line);
		if (format) {
			va_list args;
			va_start(args, format);
			libc_vfprintf(stderr, format, args);
			va_end(args);
		}
#ifdef __LOCAL_error_message_count
		++__LOCAL_error_message_count;
#endif /* __LOCAL_error_message_count */
		if (errnum != 0)
			libc_fprintf(stderr, ": %s", libc_strerror(errnum));
		libc_fputc('\n', stderr);
		if (status != 0)
			libc_exit(status);
	}
	if (status != 0)
		libc_exit(status);
}
#endif /* !__KERNEL__ */

DECL_END

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$error, libd_error);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(error, libc_error);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$error_at_line, libd_error_at_line);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(error_at_line, libc_error_at_line);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_ERROR_C */
