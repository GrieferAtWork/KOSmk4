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

%[define_replacement(errno_t = __errno_t)]
%[default_impl_section(.text.crt.error)]

%{
#include <bits/types.h>

#ifdef __CC__

__SYSDECL_BEGIN

}

%[define(DEFINE_LOCAL_error_print_progname =
#ifndef __LOCAL_error_print_progname
#ifdef error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#elif defined(__CRT_HAVE_error_print_progname)
#ifdef __NO_ASMNAME
__LIBC void (__LIBCCALL *__LOCAL_error_print_progname)(void) __ASMNAME("error_print_progname");
#else /* __NO_ASMNAME */
__LIBC void (__LIBCCALL *error_print_progname)(void);
#ifndef __cplusplus
#define error_print_progname         error_print_progname
#endif /* !__cplusplus */
#define __LOCAL_error_print_progname error_print_progname
#endif /* !__NO_ASMNAME */
#endif /* __CRT_HAVE_error_print_progname */
#endif /* !__LOCAL_error_print_progname */
)]

%[define(DEFINE_LOCAL_error_message_count =
#ifndef __LOCAL_error_message_count
#ifdef error_message_count
#define __LOCAL_error_message_count error_message_count
#elif defined(__CRT_HAVE_error_message_count)
#ifdef __NO_ASMNAME
__LIBC unsigned int __LOCAL_error_message_count __ASMNAME("error_message_count");
#else /* __NO_ASMNAME */
__LIBC unsigned int error_message_count;
#ifndef __cplusplus
#define error_message_count         error_message_count
#endif /* !__cplusplus */
#define __LOCAL_error_message_count error_message_count
#endif /* !__NO_ASMNAME */
#endif /* __CRT_HAVE_error_message_count */
#endif /* !__LOCAL_error_message_count */
)]

%[define(DEFINE_LOCAL_error_one_per_line =
#ifndef __LOCAL_error_one_per_line
#ifdef error_one_per_line
#define __LOCAL_error_one_per_line error_one_per_line
#elif defined(__CRT_HAVE_error_one_per_line)
#ifdef __NO_ASMNAME
__LIBC int __LOCAL_error_one_per_line __ASMNAME("error_one_per_line");
#else /* __NO_ASMNAME */
__LIBC int error_one_per_line;
#ifndef __cplusplus
#define error_one_per_line         error_one_per_line
#endif /* !__cplusplus */
#define __LOCAL_error_one_per_line error_one_per_line
#endif /* !__NO_ASMNAME */
#endif /* __CRT_HAVE_error_one_per_line */
#endif /* !__LOCAL_error_one_per_line */
)]


@@Helper function for printing an error message to `stderr' and possibly exiting the program
@@The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
@@Also note that `stdout' is flushed before the message is printed.
@@If `STATUS' is non-zero, follow up with a call to `exit(status)'
[[ATTR_LIBC_PRINTF(3, 4), fast, libc, userimpl, throws]]
[decl_include("<bits/types.h>")]
[impl_include("<local/stdstreams.h>")]
[[requires_include("<__crt.h>")]]
[requires_include(<local/program_invocation_name.h>)]
[requires(!defined(__NO_STDSTREAMS) && $has_function(exit) &&
          $has_function(fprintf) && $has_function(vfprintf) && $has_function(fputc) &&
          defined(__LOCAL_program_invocation_short_name) &&
          $has_function(strerror))]
[impl_prefix(DEFINE_LOCAL_error_print_progname)]
[impl_prefix(DEFINE_LOCAL_error_message_count)]
error:(int status, $errno_t errnum, const char *format, ...) {
#ifdef @__LOCAL_error_print_progname@
	if (__LOCAL_error_print_progname) {
		(*__LOCAL_error_print_progname)();
	} else
#endif /* __LOCAL_error_print_progname */
	{
		fflush(stdout);
		fprintf(stderr, "%s: ", @__LOCAL_program_invocation_short_name@);
	}
	if (format) {
		va_list args;
		va_start(args, format);
		vfprintf(stderr, format, args);
		va_end(args);
	}
#ifdef @__LOCAL_error_message_count@
	++@__LOCAL_error_message_count@;
#endif /* __LOCAL_error_message_count */
	if (errnum != 0)
		fprintf(stderr, ": %s", strerror(errnum));
	fputc('\n', stderr);
	if (status != 0)
		exit(status);
}


@@Same as `error()', but also include the given filename in the error message.
@@The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
@@Additionally, when `error_one_per_line' is non-zero, consecutive calls to this function that
@@pass the same values for `filename' and `line' will not produce the error message.
[ATTR_LIBC_PRINTF(5, 6)][[fast, libc, userimpl]][throws]
[decl_include("<bits/types.h>")]
[impl_include("<local/stdstreams.h>")]
[[requires_include("<__crt.h>")]]
[requires_include(<local/program_invocation_name.h>)]
[requires(!defined(__NO_STDSTREAMS) && $has_function(exit) &&
          $has_function(fprintf) && $has_function(vfprintf) && $has_function(fputc) &&
          defined(__LOCAL_program_invocation_short_name) &&
          $has_function(strerror))]
[impl_prefix(DEFINE_LOCAL_error_print_progname)]
[impl_prefix(DEFINE_LOCAL_error_one_per_line)]
[impl_prefix(DEFINE_LOCAL_error_message_count)]
error_at_line:(int status, $errno_t errnum, char const *filename,
               unsigned int line, char const *format, ...) {
#ifdef @__LOCAL_error_one_per_line@
	static char const *last_filename = NULL;
	static unsigned int last_line = 0;
	if (@__LOCAL_error_one_per_line@ != 0 &&
	    line == last_line &&
	    (filename == last_filename ||
	     strcmp(filename, last_filename) == 0)) {
		/* Don't print the same error more than once */
	} else
#endif /* __LOCAL_error_one_per_line */
	{
#ifdef @__LOCAL_error_one_per_line@
		filename = last_filename;
		line     = last_line;
#endif /* __LOCAL_error_one_per_line */
#ifdef @__LOCAL_error_print_progname@
		if (__LOCAL_error_print_progname) {
			(*__LOCAL_error_print_progname)();
		} else
#endif /* __LOCAL_error_print_progname */
		{
			fflush(stdout);
			fprintf(stderr, "%s:", @__LOCAL_program_invocation_short_name@);
		}
		fprintf(stderr, "%s:%u: ", filename, line);
		if (format) {
			va_list args;
			va_start(args, format);
			vfprintf(stderr, format, args);
			va_end(args);
		}
#ifdef @__LOCAL_error_message_count@
		++@__LOCAL_error_message_count@;
#endif /* __LOCAL_error_message_count */
		if (errnum != 0)
			fprintf(stderr, ": %s", strerror(errnum));
		fputc('\n', stderr);
		if (status != 0)
			exit(status);
	}
	if (status != 0)
		exit(status);
}


%{

#ifndef error_print_progname
#ifdef __CRT_HAVE_error_print_progname
/* Override for printing the program name.
 * When non-NULL, this function should:
 *  - fflush(stdout);
 *  - fprintf(stderr, "%s: ", basename(argv[0])); */
__LIBC void (__LIBCCALL *error_print_progname)(void);
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

}

%{

__SYSDECL_END

#endif /* __CC__ */

}

