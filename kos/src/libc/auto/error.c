/* HASH CRC-32:0xd75c6d62 */
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
#ifndef GUARD_LIBC_AUTO_ERROR_C
#define GUARD_LIBC_AUTO_ERROR_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "error.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

/* Use the KOS-special `libc_strerrordesc_np()' functions, rather than strerror()
 * below (thus making  these functions  a bit  more light-weight  by having  just
 * a bit less dependencies) */
#define strerror      libc_strerrordesc_np
#define libc_strerror libc_strerrordesc_np
#include "../libc/globals.h" /* For norel access to global variables */
#ifndef __KERNEL__
#ifndef __LOCAL_error_print_progname
#ifdef error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#elif defined(__CRT_HAVE_error_print_progname)
#ifdef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(,void (__LIBKCALL *__LOCAL_error_print_progname)(void),__LOCAL_error_print_progname,error_print_progname)
#else /* __NO_COMPILER_SREDIRECT */
__CSDECLARE2(,void (__LIBKCALL *error_print_progname)(void),error_print_progname)
#define error_print_progname       error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_error_print_progname */
#ifndef __LOCAL_error_message_count
#ifdef error_message_count
#define __LOCAL_error_message_count error_message_count
#elif defined(__CRT_HAVE_error_message_count)
#ifdef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,unsigned int,__LOCAL_error_message_count,error_message_count)
#else /* __NO_COMPILER_SREDIRECT */
__CSDECLARE(,unsigned int,error_message_count)
#define error_message_count       error_message_count
#define __LOCAL_error_message_count error_message_count
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_error_message_count */
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
INTERN ATTR_SECTION(".text.crt.error") ATTR_LIBC_PRINTF(3, 0) void
NOTHROW_CB_NCX(LIBCCALL libc_verror)(int status,
                                     errno_t errnum,
                                     const char *format,
                                     va_list args) {

	if (__LOCAL_error_print_progname) {
		(*__LOCAL_error_print_progname)();
	} else

	{

		libc_fflush(stdout);

		libc_fprintf(stderr, "%s: ", program_invocation_short_name);
	}
	if (format)
		libc_vfprintf(stderr, format, args);

	++__LOCAL_error_message_count;

	if (errnum != 0)
		libc_fprintf(stderr, ": %s", libc_strerror(errnum));
	libc_fputc('\n', stderr);
	if (status != 0)
		libc_exit(status);
}
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#ifndef __LOCAL_error_print_progname
#ifdef error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#elif defined(__CRT_HAVE_error_print_progname)
#ifdef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(,void (__LIBKCALL *__LOCAL_error_print_progname)(void),__LOCAL_error_print_progname,error_print_progname)
#else /* __NO_COMPILER_SREDIRECT */
__CSDECLARE2(,void (__LIBKCALL *error_print_progname)(void),error_print_progname)
#define error_print_progname       error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_error_print_progname */
#ifndef __LOCAL_error_one_per_line
#ifdef error_one_per_line
#define __LOCAL_error_one_per_line error_one_per_line
#elif defined(__CRT_HAVE_error_one_per_line)
#ifdef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,int,__LOCAL_error_one_per_line,error_one_per_line)
#else /* __NO_COMPILER_SREDIRECT */
__CSDECLARE(,int,error_one_per_line)
#define error_one_per_line       error_one_per_line
#define __LOCAL_error_one_per_line error_one_per_line
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_error_one_per_line */
#ifndef __LOCAL_error_message_count
#ifdef error_message_count
#define __LOCAL_error_message_count error_message_count
#elif defined(__CRT_HAVE_error_message_count)
#ifdef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,unsigned int,__LOCAL_error_message_count,error_message_count)
#else /* __NO_COMPILER_SREDIRECT */
__CSDECLARE(,unsigned int,error_message_count)
#define error_message_count       error_message_count
#define __LOCAL_error_message_count error_message_count
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_error_message_count */
INTERN ATTR_SECTION(".text.crt.error") ATTR_LIBC_PRINTF(5, 0) void
NOTHROW_CB_NCX(LIBCCALL libc_verror_at_line)(int status,
                                             errno_t errnum,
                                             char const *filename,
                                             unsigned int line,
                                             char const *format,
                                             va_list args) {

	static char const *last_filename = NULL;
	static unsigned int last_line = 0;
	if (__LOCAL_error_one_per_line != 0 &&
	    line == last_line && filename && last_filename &&
	    (filename == last_filename || libc_strcmp(filename, last_filename) == 0)) {
		/* Don't print the same error more than once */
	} else

	{

		filename = last_filename;
		line     = last_line;


		if (__LOCAL_error_print_progname) {
			(*__LOCAL_error_print_progname)();
		} else

		{

			libc_fflush(stdout);

			libc_fprintf(stderr, "%s:", program_invocation_short_name);
		}
		libc_fprintf(stderr, "%s:%u: ", filename, line);
		if (format)
			libc_vfprintf(stderr, format, args);

		++__LOCAL_error_message_count;

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
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> error(3)
 * Helper  function  for printing  an error  message to  `stderr' and  possibly exiting  the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `status' is non-zero, follow up with a call to `exit(status)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_LIBC_PRINTF(3, 4) void
NOTHROW_CB_NCX(VLIBDCALL libd_error)(int status,
                                     errno_t errnum,
                                     const char *format,
                                     ...) {
	va_list args;
	va_start(args, format);
	libc_verror(status, errnum, format, args);
	va_end(args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> error(3)
 * Helper  function  for printing  an error  message to  `stderr' and  possibly exiting  the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `status' is non-zero, follow up with a call to `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_LIBC_PRINTF(3, 4) void
NOTHROW_CB_NCX(VLIBCCALL libc_error)(int status,
                                     errno_t errnum,
                                     const char *format,
                                     ...) {
	va_list args;
	va_start(args, format);
	libc_verror(status, errnum, format, args);
	va_end(args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> error_at_line(3)
 * Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally,  when `error_one_per_line' is non-zero, consecutive calls to  this function that pass the same values
 * for `filename' and `line' will not produce the error message. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_LIBC_PRINTF(5, 6) void
NOTHROW_CB_NCX(VLIBDCALL libd_error_at_line)(int status,
                                             errno_t errnum,
                                             char const *filename,
                                             unsigned int line,
                                             char const *format,
                                             ...) {
	va_list args;
	va_start(args, format);
	libc_verror_at_line(status, errnum, filename, line, format, args);
	va_end(args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> error_at_line(3)
 * Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally,  when `error_one_per_line' is non-zero, consecutive calls to  this function that pass the same values
 * for `filename' and `line' will not produce the error message. */
INTERN ATTR_SECTION(".text.crt.error") ATTR_LIBC_PRINTF(5, 6) void
NOTHROW_CB_NCX(VLIBCCALL libc_error_at_line)(int status,
                                             errno_t errnum,
                                             char const *filename,
                                             unsigned int line,
                                             char const *format,
                                             ...) {
	va_list args;
	va_start(args, format);
	libc_verror_at_line(status, errnum, filename, line, format, args);
	va_end(args);
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
