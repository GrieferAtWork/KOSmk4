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
#ifndef GUARD_LIBC_USER_ERR_C
#define GUARD_LIBC_USER_ERR_C 1

#include "../api.h"
/**/

#include "err.h"
#include "stdio-api.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

DECL_BEGIN

/* Use the KOS-function `libc_strerror_s()' */
#undef libc_strerror
#define libc_strerror libc_strerror_s


/* Define globals and meta-data for accessing those globals without any relocations. */
#undef program_invocation_short_name
#undef __LOCAL_program_invocation_short_name
DECLARE_NOREL_GLOBAL_META(char *, program_invocation_short_name); /* Defined in "errno.c" */
#define program_invocation_short_name  GET_NOREL_GLOBAL(program_invocation_short_name)
#define __LOCAL_program_invocation_short_name program_invocation_short_name


/*[[[start:implementation]]]*/

/*[[[head:warn,hash:CRC-32=0x4745594d]]]*/
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTERN ATTR_LIBC_PRINTF(1, 2)
ATTR_WEAK ATTR_SECTION(".text.crt.error.warn") void
(VLIBCCALL libc_warn)(char const *format,
                      ...)
		__THROWS(...)
/*[[[body:warn]]]*/
/*AUTO*/{
	va_list args;
	va_start(args, format);
	libc_vwarn(format, args);
	va_end(args);
}
/*[[[end:warn]]]*/

/*[[[head:vwarn,hash:CRC-32=0x9bb6deb5]]]*/
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTERN ATTR_LIBC_PRINTF(1, 0)
ATTR_WEAK ATTR_SECTION(".text.crt.error.vwarn") void
(LIBCCALL libc_vwarn)(char const *format,
                      va_list args)
		__THROWS(...)
/*[[[body:vwarn]]]*/
/*AUTO*/{
	int errval = __libc_geterrno_or(0);
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	libc_flockfile(__LOCAL_stderr);
#endif
	libc_fprintf(__LOCAL_stderr, "%s: ", __LOCAL_program_invocation_short_name);
	if (format) {
		libc_vfprintf(__LOCAL_stderr, format, args);
		libc_fprintf(__LOCAL_stderr, ": %s\n", libc_strerror(errval));
	} else {
		libc_fprintf(__LOCAL_stderr, "%s\n", libc_strerror(errval));
	}
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	libc_funlockfile(__LOCAL_stderr);
#endif
}
/*[[[end:vwarn]]]*/

/*[[[head:warnx,hash:CRC-32=0x21d3347f]]]*/
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTERN ATTR_LIBC_PRINTF(1, 2)
ATTR_WEAK ATTR_SECTION(".text.crt.error.warnx") void
(VLIBCCALL libc_warnx)(char const *format,
                       ...)
		__THROWS(...)
/*[[[body:warnx]]]*/
/*AUTO*/{
	va_list args;
	va_start(args, format);
	libc_vwarnx(format, args);
	va_end(args);
}
/*[[[end:warnx]]]*/

/*[[[head:vwarnx,hash:CRC-32=0x1d88396f]]]*/
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTERN ATTR_LIBC_PRINTF(1, 0)
ATTR_WEAK ATTR_SECTION(".text.crt.error.vwarnx") void
(LIBCCALL libc_vwarnx)(char const *format,
                       va_list args)
		__THROWS(...)
/*[[[body:vwarnx]]]*/
/*AUTO*/{
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	libc_flockfile(__LOCAL_stderr);
#endif
	libc_fprintf(__LOCAL_stderr, "%s: ", __LOCAL_program_invocation_short_name);
	if (format)
		libc_vfprintf(__LOCAL_stderr, format, args);
	libc_fputc('\n', __LOCAL_stderr);
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	libc_funlockfile(__LOCAL_stderr);
#endif
}
/*[[[end:vwarnx]]]*/

/*[[[head:err,hash:CRC-32=0xe4983f0a]]]*/
/* Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_NORETURN ATTR_LIBC_PRINTF(2, 3)
ATTR_WEAK ATTR_SECTION(".text.crt.error.err") void
(VLIBCCALL libc_err)(int status,
                     char const *format,
                     ...)
		__THROWS(...)
/*[[[body:err]]]*/
/*AUTO*/{
	va_list args;
	va_start(args, format);
	libc_verr(status, format, args);
}
/*[[[end:err]]]*/

/*[[[head:verr,hash:CRC-32=0x2de22511]]]*/
/* Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_NORETURN ATTR_LIBC_PRINTF(2, 0)
ATTR_WEAK ATTR_SECTION(".text.crt.error.verr") void
(LIBCCALL libc_verr)(int status,
                     char const *format,
                     va_list args)
		__THROWS(...)
/*[[[body:verr]]]*/
/*AUTO*/{
	libc_vwarn(format, args);
	libc_exit(status);
}
/*[[[end:verr]]]*/

/*[[[head:errx,hash:CRC-32=0x69eca025]]]*/
/* Same as `warnx()', but follow up by calling `exit(status)' */
INTERN ATTR_NORETURN ATTR_LIBC_PRINTF(2, 3)
ATTR_WEAK ATTR_SECTION(".text.crt.error.errx") void
(VLIBCCALL libc_errx)(int status,
                      char const *format,
                      ...)
		__THROWS(...)
/*[[[body:errx]]]*/
/*AUTO*/{
	va_list args;
	va_start(args, format);
	libc_verrx(status, format, args);
}
/*[[[end:errx]]]*/

/*[[[head:verrx,hash:CRC-32=0x9d1fc2a6]]]*/
/* Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_NORETURN ATTR_LIBC_PRINTF(2, 0)
ATTR_WEAK ATTR_SECTION(".text.crt.error.verrx") void
(LIBCCALL libc_verrx)(int status,
                      char const *format,
                      va_list args)
		__THROWS(...)
/*[[[body:verrx]]]*/
/*AUTO*/{
	libc_vwarnx(format, args);
	libc_exit(status);
}
/*[[[end:verrx]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xde815fa9]]]*/
#undef warn
#undef warnx
#undef err
#undef errx
DEFINE_PUBLIC_WEAK_ALIAS(warn, libc_warn);
DEFINE_PUBLIC_WEAK_ALIAS(vwarn, libc_vwarn);
DEFINE_PUBLIC_WEAK_ALIAS(warnx, libc_warnx);
DEFINE_PUBLIC_WEAK_ALIAS(vwarnx, libc_vwarnx);
DEFINE_PUBLIC_WEAK_ALIAS(err, libc_err);
DEFINE_PUBLIC_WEAK_ALIAS(verr, libc_verr);
DEFINE_PUBLIC_WEAK_ALIAS(errx, libc_errx);
DEFINE_PUBLIC_WEAK_ALIAS(verrx, libc_verrx);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ERR_C */
