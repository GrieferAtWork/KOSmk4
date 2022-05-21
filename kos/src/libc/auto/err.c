/* HASH CRC-32:0x60ab84cf */
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
#ifndef GUARD_LIBC_AUTO_ERR_C
#define GUARD_LIBC_AUTO_ERR_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "err.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#include "../libc/globals.h"
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> warn(3), vwarn(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_ACCESS_RO_OPT(1) ATTR_LIBC_PRINTF(1, 2) void
(VLIBDCALL libd_warn)(char const *format,
                      ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_vwarn(format, args);
	va_end(args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> warn(3), vwarn(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_ACCESS_RO_OPT(1) ATTR_LIBC_PRINTF(1, 2) void
(VLIBCCALL libc_warn)(char const *format,
                      ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_vwarn(format, args);
	va_end(args);
}
#include <libc/errno.h>
/* >> warn(3), vwarn(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_ACCESS_RO_OPT(1) ATTR_LIBC_PRINTF(1, 0) void
(LIBCCALL libc_vwarn)(char const *format,
                      va_list args) THROWS(...) {
	libc_vwarnc(__libc_geterrno_or(0), format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_ACCESS_RO_OPT(2) ATTR_LIBC_PRINTF(2, 3) void
(VLIBDCALL libd_warnc)(errno_t used_errno,
                       char const *format,
                       ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_vwarnc(used_errno, format, args);
	va_end(args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_ACCESS_RO_OPT(2) ATTR_LIBC_PRINTF(2, 3) void
(VLIBCCALL libc_warnc)(errno_t used_errno,
                       char const *format,
                       ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_vwarnc(used_errno, format, args);
	va_end(args);
}
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_ACCESS_RO_OPT(2) ATTR_LIBC_PRINTF(2, 0) void
(LIBCCALL libc_vwarnc)(errno_t used_errno,
                       char const *format,
                       va_list args) THROWS(...) {

	libc_flockfile(stderr);

	libc_fprintf(stderr, "%s: ", program_invocation_short_name);
	if (format) {
		libc_vfprintf(stderr, format, args);
		libc_fprintf(stderr, ": %s\n", libc_strerror(used_errno));
	} else {
		libc_fprintf(stderr, "%s\n", libc_strerror(used_errno));
	}

	libc_funlockfile(stderr);

}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_ACCESS_RO_OPT(1) ATTR_LIBC_PRINTF(1, 2) void
(VLIBDCALL libd_warnx)(char const *format,
                       ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_vwarnx(format, args);
	va_end(args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_ACCESS_RO_OPT(1) ATTR_LIBC_PRINTF(1, 2) void
(VLIBCCALL libc_warnx)(char const *format,
                       ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_vwarnx(format, args);
	va_end(args);
}
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_ACCESS_RO_OPT(1) ATTR_LIBC_PRINTF(1, 0) void
(LIBCCALL libc_vwarnx)(char const *format,
                       va_list args) THROWS(...) {

	libc_flockfile(stderr);

	libc_fprintf(stderr, "%s: ", program_invocation_short_name);
	if (format)
		libc_vfprintf(stderr, format, args);
	libc_fputc('\n', stderr);

	libc_funlockfile(stderr);

}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_NORETURN ATTR_ACCESS_RO_OPT(2) ATTR_LIBC_PRINTF(2, 3) void
(VLIBDCALL libd_err)(int status,
                     char const *format,
                     ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_verr(status, format, args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_ACCESS_RO_OPT(2) ATTR_LIBC_PRINTF(2, 3) void
(VLIBCCALL libc_err)(int status,
                     char const *format,
                     ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_verr(status, format, args);
}
#include <libc/errno.h>
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_ACCESS_RO_OPT(2) ATTR_LIBC_PRINTF(2, 0) void
(LIBCCALL libc_verr)(int status,
                     char const *format,
                     va_list args) THROWS(...) {
	libc_verrc(status, __libc_geterrno_or(0), format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_NORETURN ATTR_ACCESS_RO_OPT(3) ATTR_LIBC_PRINTF(3, 4) void
(VLIBDCALL libd_errc)(int status,
                      errno_t used_errno,
                      char const *format,
                      ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_verrc(status, used_errno, format, args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_ACCESS_RO_OPT(3) ATTR_LIBC_PRINTF(3, 4) void
(VLIBCCALL libc_errc)(int status,
                      errno_t used_errno,
                      char const *format,
                      ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_verrc(status, used_errno, format, args);
}
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_ACCESS_RO_OPT(3) ATTR_LIBC_PRINTF(3, 0) void
(LIBCCALL libc_verrc)(int status,
                      errno_t used_errno,
                      char const *format,
                      va_list args) THROWS(...) {
	libc_vwarnc(used_errno, format, args);
	libc_exit(status);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_NORETURN ATTR_ACCESS_RO_OPT(2) ATTR_LIBC_PRINTF(2, 3) void
(VLIBDCALL libd_errx)(int status,
                      char const *format,
                      ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_verrx(status, format, args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_ACCESS_RO_OPT(2) ATTR_LIBC_PRINTF(2, 3) void
(VLIBCCALL libc_errx)(int status,
                      char const *format,
                      ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_verrx(status, format, args);
}
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_ACCESS_RO_OPT(2) ATTR_LIBC_PRINTF(2, 0) void
(LIBCCALL libc_verrx)(int status,
                      char const *format,
                      va_list args) THROWS(...) {
	libc_vwarnx(format, args);
	libc_exit(status);
}
#endif /* !__KERNEL__ */

DECL_END

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$warn, libd_warn);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(warn, libc_warn);
DEFINE_PUBLIC_ALIAS(vwarn, libc_vwarn);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$warnc, libd_warnc);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(warnc, libc_warnc);
DEFINE_PUBLIC_ALIAS(vwarnc, libc_vwarnc);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$warnx, libd_warnx);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(warnx, libc_warnx);
DEFINE_PUBLIC_ALIAS(vwarnx, libc_vwarnx);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$err, libd_err);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(err, libc_err);
DEFINE_PUBLIC_ALIAS(verr, libc_verr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$errc, libd_errc);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(errc, libc_errc);
DEFINE_PUBLIC_ALIAS(verrc, libc_verrc);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$errx, libd_errx);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(errx, libc_errx);
DEFINE_PUBLIC_ALIAS(verrx, libc_verrx);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_ERR_C */
