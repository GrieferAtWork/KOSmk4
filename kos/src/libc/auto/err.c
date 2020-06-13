/* HASH CRC-32:0x23a15f1e */
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
#ifndef GUARD_LIBC_AUTO_ERR_C
#define GUARD_LIBC_AUTO_ERR_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "err.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "../user/string.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_LIBC_PRINTF(1, 2) void
(VLIBCCALL libc_warn)(char const *format,
                      ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_vwarn(format, args);
	va_end(args);
}
#include <local/stdstreams.h>
#include <parts/errno.h>
#include <local/program_invocation_name.h>
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_LIBC_PRINTF(1, 0) void
(LIBCCALL libc_vwarn)(char const *format,
                      va_list args) THROWS(...) {
	int errval = __libc_geterrno_or(0);
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	libc_flockfile(stderr);
#endif /* (__CRT_HAVE_flockfile || __CRT_HAVE__lock_file || __CRT_HAVE__IO_flockfile) && (__CRT_HAVE_funlockfile || __CRT_HAVE__unlock_file || __CRT_HAVE__IO_funlockfile) */
	libc_fprintf(stderr, "%s: ", __LOCAL_program_invocation_short_name);
	if (format) {
		libc_vfprintf(stderr, format, args);
		libc_fprintf(stderr, ": %s\n", libc_strerror(errval));
	} else {
		libc_fprintf(stderr, "%s\n", libc_strerror(errval));
	}
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	libc_funlockfile(stderr);
#endif /* (__CRT_HAVE_flockfile || __CRT_HAVE__lock_file || __CRT_HAVE__IO_flockfile) && (__CRT_HAVE_funlockfile || __CRT_HAVE__unlock_file || __CRT_HAVE__IO_funlockfile) */
}
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_LIBC_PRINTF(1, 2) void
(VLIBCCALL libc_warnx)(char const *format,
                       ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_vwarnx(format, args);
	va_end(args);
}
#include <local/stdstreams.h>
#include <local/program_invocation_name.h>
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_LIBC_PRINTF(1, 0) void
(LIBCCALL libc_vwarnx)(char const *format,
                       va_list args) THROWS(...) {
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	libc_flockfile(stderr);
#endif /* (__CRT_HAVE_flockfile || __CRT_HAVE__lock_file || __CRT_HAVE__IO_flockfile) && (__CRT_HAVE_funlockfile || __CRT_HAVE__unlock_file || __CRT_HAVE__IO_funlockfile) */
	libc_fprintf(stderr, "%s: ", __LOCAL_program_invocation_short_name);
	if (format)
		libc_vfprintf(stderr, format, args);
	libc_fputc('\n', stderr);
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	libc_funlockfile(stderr);
#endif /* (__CRT_HAVE_flockfile || __CRT_HAVE__lock_file || __CRT_HAVE__IO_flockfile) && (__CRT_HAVE_funlockfile || __CRT_HAVE__unlock_file || __CRT_HAVE__IO_funlockfile) */
}
/* Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_LIBC_PRINTF(2, 3) void
(VLIBCCALL libc_err)(int status,
                     char const *format,
                     ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_verr(status, format, args);
}
/* Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_LIBC_PRINTF(2, 0) void
(LIBCCALL libc_verr)(int status,
                     char const *format,
                     va_list args) THROWS(...) {
	libc_vwarn(format, args);
	libc_exit(status);
}
/* Same as `warnx()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_LIBC_PRINTF(2, 3) void
(VLIBCCALL libc_errx)(int status,
                      char const *format,
                      ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_verrx(status, format, args);
}
/* Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_LIBC_PRINTF(2, 0) void
(LIBCCALL libc_verrx)(int status,
                      char const *format,
                      va_list args) THROWS(...) {
	libc_vwarnx(format, args);
	libc_exit(status);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(warn, libc_warn);
DEFINE_PUBLIC_ALIAS(vwarn, libc_vwarn);
DEFINE_PUBLIC_ALIAS(warnx, libc_warnx);
DEFINE_PUBLIC_ALIAS(vwarnx, libc_vwarnx);
DEFINE_PUBLIC_ALIAS(err, libc_err);
DEFINE_PUBLIC_ALIAS(verr, libc_verr);
DEFINE_PUBLIC_ALIAS(errx, libc_errx);
DEFINE_PUBLIC_ALIAS(verrx, libc_verrx);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_ERR_C */
