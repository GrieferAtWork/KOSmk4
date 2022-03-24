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
%(c_prefix){
/* (#) Portability: Cygwin        (/winsup/cygwin/include/error.h) */
/* (#) Portability: GNU C Library (/misc/error.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/include/error.h) */
/* (#) Portability: libc6         (/include/error.h) */
/* (#) Portability: uClibc        (/include/error.h) */
}

%[define_replacement(errno_t = __errno_t)]
%[default:section(".text.crt{|.dos}.error")]

%(auto_source){
/* Use the KOS-special `libc_strerrordesc_np()' functions, rather than strerror()
 * below (thus making  these functions  a bit  more light-weight  by having  just
 * a bit less dependencies) */
#define strerror        libc_strerrordesc_np
#define libc_strerror   libc_strerrordesc_np
#include "../libc/globals.h" /* For norel access to global variables */
}

/* All of these get defined in "libc/globals.h" */
%[assume_defined_in_kos_userspace(__LOCAL_error_print_progname)]
%[assume_defined_in_kos_userspace(__LOCAL_error_message_count)]
%[assume_defined_in_kos_userspace(__LOCAL_error_one_per_line)]
%[assume_defined_in_kos_userspace(error_print_progname)]
%[assume_defined_in_kos_userspace(error_message_count)]
%[assume_defined_in_kos_userspace(error_one_per_line)]

%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/error.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */

#ifdef __CC__
__SYSDECL_BEGIN

}

%[define(DEFINE_LOCAL_error_print_progname =
@@pp_ifndef __LOCAL_error_print_progname@@
@@pp_ifdef          error_print_progname@@
#define __LOCAL_error_print_progname error_print_progname
@@pp_elif defined(__CRT_HAVE_error_print_progname)@@
@@pp_ifdef __NO_ASMNAME@@
__LIBC void (__LIBKCALL *__LOCAL_error_print_progname)(void) __ASMNAME("error_print_progname");
@@pp_else@@
__LIBC void (__LIBKCALL *error_print_progname)(void);
#define error_print_progname         error_print_progname
#define __LOCAL_error_print_progname error_print_progname
@@pp_endif@@
@@pp_endif@@
@@pp_endif@@
)]

%[define(DEFINE_LOCAL_error_message_count =
@@pp_ifndef __LOCAL_error_message_count@@
@@pp_ifdef          error_message_count@@
#define __LOCAL_error_message_count error_message_count
@@pp_elif defined(__CRT_HAVE_error_message_count)@@
@@pp_ifdef __NO_ASMNAME@@
__LIBC unsigned int __LOCAL_error_message_count __ASMNAME("error_message_count");
@@pp_else@@
__LIBC unsigned int error_message_count;
#define error_message_count         error_message_count
#define __LOCAL_error_message_count error_message_count
@@pp_endif@@
@@pp_endif@@
@@pp_endif@@
)]

%[define(DEFINE_LOCAL_error_one_per_line =
@@pp_ifndef __LOCAL_error_one_per_line@@
@@pp_ifdef          error_one_per_line@@
#define __LOCAL_error_one_per_line error_one_per_line
@@pp_elif defined(__CRT_HAVE_error_one_per_line)@@
@@pp_ifdef __NO_ASMNAME@@
__LIBC int __LOCAL_error_one_per_line __ASMNAME("error_one_per_line");
@@pp_else@@
__LIBC int error_one_per_line;
#define error_one_per_line         error_one_per_line
#define __LOCAL_error_one_per_line error_one_per_line
@@pp_endif@@
@@pp_endif@@
@@pp_endif@@
)]

/* These are defined in <libc/template/program_invocation_name.h> */
%[define_replacement(program_invocation_name       = __LOCAL_program_invocation_name)]
%[define_replacement(program_invocation_short_name = __LOCAL_program_invocation_short_name)]


@@>> error(3)
@@Helper  function  for printing  an error  message to  `stderr' and  possibly exiting  the program
@@The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
@@Also note that `stdout' is flushed before the message is printed.
@@If `STATUS' is non-zero, follow up with a call to `exit(status)'
[[fast, libc, throws]]
[[decl_include("<bits/types.h>")]]
[[impl_prefix(DEFINE_LOCAL_error_print_progname)]]
[[impl_prefix(DEFINE_LOCAL_error_message_count)]]
[[impl_include("<libc/template/stdstreams.h>")]]
[[impl_include("<libc/template/program_invocation_name.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(exit) &&
           $has_function(fprintf) && $has_function(vfprintf) && $has_function(fputc) &&
           defined(__LOCAL_program_invocation_short_name) &&
           $has_function(strerror))]]
void error(int status, $errno_t errnum, [[nullable, format("printf")]] const char *format, ...) {
@@pp_ifdef __LOCAL_error_print_progname@@
	if (__LOCAL_error_print_progname) {
		(*__LOCAL_error_print_progname)();
	} else
@@pp_endif@@
	{
@@pp_ifdef stdout@@
		fflush(stdout);
@@pp_endif@@
		fprintf(stderr, "%s: ", program_invocation_short_name);
	}
	if (format) {
		va_list args;
		va_start(args, format);
		vfprintf(stderr, format, args);
		va_end(args);
	}
@@pp_ifdef __LOCAL_error_message_count@@
	++__LOCAL_error_message_count;
@@pp_endif@@
	if (errnum != 0)
		fprintf(stderr, ": %s", strerror(errnum));
	fputc('\n', stderr);
	if (status != 0)
		exit(status);
}


@@>> error_at_line(3)
@@Same as `error()', but also include the given filename in the error message.
@@The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
@@Additionally,    when   `error_one_per_line'   is    non-zero,   consecutive   calls    to   this   function   that
@@pass the same values for `filename' and `line' will not produce the error message.
[[fast, libc, throws]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/template/stdstreams.h>")]]
[[impl_include("<libc/template/program_invocation_name.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/program_invocation_name.h>")]]
[[requires(defined(__LOCAL_stderr) && $has_function(exit) &&
           $has_function(fprintf) && $has_function(vfprintf) &&
           $has_function(fputc) && defined(__LOCAL_program_invocation_short_name) &&
           $has_function(strerror))]]
[[impl_prefix(DEFINE_LOCAL_error_print_progname)]]
[[impl_prefix(DEFINE_LOCAL_error_one_per_line)]]
[[impl_prefix(DEFINE_LOCAL_error_message_count)]]
void error_at_line(int status, $errno_t errnum, char const *filename,
                   unsigned int line, [[nullable, format("printf")]] char const *format, ...) {
@@pp_ifdef __LOCAL_error_one_per_line@@
	static char const *last_filename = NULL;
	static unsigned int last_line = 0;
	if (__LOCAL_error_one_per_line != 0 &&
	    line == last_line && filename && last_filename &&
	    (filename == last_filename || strcmp(filename, last_filename) == 0)) {
		/* Don't print the same error more than once */
	} else
@@pp_endif@@
	{
@@pp_ifdef __LOCAL_error_one_per_line@@
		filename = last_filename;
		line     = last_line;
@@pp_endif@@
@@pp_ifdef __LOCAL_error_print_progname@@
		if (__LOCAL_error_print_progname) {
			(*__LOCAL_error_print_progname)();
		} else
@@pp_endif@@
		{
@@pp_ifdef stdout@@
			fflush(stdout);
@@pp_endif@@
			fprintf(stderr, "%s:", program_invocation_short_name);
		}
		fprintf(stderr, "%s:%u: ", filename, line);
		if (format) {
			va_list args;
			va_start(args, format);
			vfprintf(stderr, format, args);
			va_end(args);
		}
@@pp_ifdef __LOCAL_error_message_count@@
		++__LOCAL_error_message_count;
@@pp_endif@@
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
 * When non-NULL,  this  function  should:
 *  - fflush(stdout);
 *  - fprintf(stderr, "%s:", basename(argv[0])); */
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
 * values for `filename'  and `line'  will not produce  the error  message.
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
