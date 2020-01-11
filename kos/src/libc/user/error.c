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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_ERROR_C
#define GUARD_LIBC_USER_ERROR_C 1

#include "../api.h"
/**/

#include "error.h"
#include "stdio-api.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

DECL_BEGIN

/* Use the KOS-function `libc_strerror_s()' */
#undef libc_strerror
#define libc_strerror libc_strerror_s


typedef void (__LIBCCALL *PERROR_PRINT_PROGNAME)(void);

#define ERROR_BSS(name) ATTR_SECTION(".bss.crt.error." name) 

/* Define globals and meta-data for accessing those globals without any relocations. */
#undef error_message_count
#undef error_print_progname
#undef error_one_per_line
#undef program_invocation_short_name
#undef __LOCAL_error_print_progname
#undef __LOCAL_error_message_count
#undef __LOCAL_error_one_per_line
#undef __LOCAL_program_invocation_short_name
PUBLIC ERROR_BSS("error_print_progname") PERROR_PRINT_PROGNAME error_print_progname = NULL;
PUBLIC ERROR_BSS("error_message_count") unsigned int error_message_count = 0;
PUBLIC ERROR_BSS("error_one_per_line") int error_one_per_line = 0;
DEFINE_NOREL_GLOBAL_META(PERROR_PRINT_PROGNAME, error_print_progname, ".crt.error");
DEFINE_NOREL_GLOBAL_META(unsigned int, error_message_count, ".crt.error");
DEFINE_NOREL_GLOBAL_META(int, error_one_per_line, ".crt.error");
DECLARE_NOREL_GLOBAL_META(char *, program_invocation_short_name); /* Defined in "errno.c" */
#define error_print_progname           GET_NOREL_GLOBAL(error_print_progname)
#define error_message_count            GET_NOREL_GLOBAL(error_message_count)
#define error_one_per_line             GET_NOREL_GLOBAL(error_one_per_line)
#define program_invocation_short_name  GET_NOREL_GLOBAL(program_invocation_short_name)
#define __LOCAL_error_print_progname          error_print_progname
#define __LOCAL_error_message_count           error_message_count
#define __LOCAL_error_one_per_line            error_one_per_line
#define __LOCAL_program_invocation_short_name program_invocation_short_name





/*[[[start:implementation]]]*/

/*[[[head:error,hash:CRC-32=0x42f825dd]]]*/
/* Helper function for printing an error message to `stderr' and possibly exiting the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `STATUS' is non-zero, follow up with a call to `exit(status)' */
INTERN ATTR_LIBC_PRINTF(3, 4)
ATTR_WEAK ATTR_SECTION(".text.crt.error.error") void
(VLIBCCALL libc_error)(int status,
                       errno_t errnum,
                       const char *format,
                       ...)
		__THROWS(...)
/*[[[body:error]]]*/
/*AUTO*/{
#ifdef __LOCAL_error_print_progname
	if (__LOCAL_error_print_progname) {
		(*__LOCAL_error_print_progname)();
	} else
#endif /* __LOCAL_error_print_progname */
	{
		libc_fflush(__LOCAL_stdout);
		libc_fprintf(__LOCAL_stderr, "%s: ", __LOCAL_program_invocation_short_name);
	}
	if (format) {
		va_list args;
		va_start(args, format);
		libc_vfprintf(__LOCAL_stderr, format, args);
		va_end(args);
	}
#ifdef __LOCAL_error_message_count
	++__LOCAL_error_message_count;
#endif /* __LOCAL_error_message_count */
	if (errnum != 0)
		libc_fprintf(__LOCAL_stderr, ": %s", libc_strerror(errnum));
	libc_fputc('\n', __LOCAL_stderr);
	if (status != 0)
		libc_exit(status);
}
/*[[[end:error]]]*/

/*[[[head:error_at_line,hash:CRC-32=0x9ffded27]]]*/
/* Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally, when `error_one_per_line' is non-zero, consecutive calls to this function that
 * pass the same values for `filename' and `line' will not produce the error message. */
INTERN ATTR_LIBC_PRINTF(5, 6)
ATTR_WEAK ATTR_SECTION(".text.crt.error.error_at_line") void
(VLIBCCALL libc_error_at_line)(int status,
                               errno_t errnum,
                               char const *filename,
                               unsigned int line,
                               char const *format,
                               ...)
		__THROWS(...)
/*[[[body:error_at_line]]]*/
/*AUTO*/{
#ifdef __LOCAL_error_one_per_line
	static char const *last_filename = NULL;
	static unsigned int last_line = 0;
	if (__LOCAL_error_one_per_line != 0 &&
	    line == last_line &&
	    (filename == last_filename ||
	     libc_strcmp(filename, last_filename) == 0)) {
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
			libc_fflush(__LOCAL_stdout);
			libc_fprintf(__LOCAL_stderr, "%s:", __LOCAL_program_invocation_short_name);
		}
		libc_fprintf(__LOCAL_stderr, "%s:%u: ", filename, line);
		if (format) {
			va_list args;
			va_start(args, format);
			libc_vfprintf(__LOCAL_stderr, format, args);
			va_end(args);
		}
#ifdef __LOCAL_error_message_count
		++__LOCAL_error_message_count;
#endif /* __LOCAL_error_message_count */
		if (errnum != 0)
			libc_fprintf(__LOCAL_stderr, ": %s", libc_strerror(errnum));
		libc_fputc('\n', __LOCAL_stderr);
		if (status != 0)
			libc_exit(status);
	}
	if (status != 0)
		libc_exit(status);
}
/*[[[end:error_at_line]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x50bd4cea]]]*/
#undef error
#undef error_at_line
DEFINE_PUBLIC_WEAK_ALIAS(error, libc_error);
DEFINE_PUBLIC_WEAK_ALIAS(error_at_line, libc_error_at_line);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ERROR_C */
