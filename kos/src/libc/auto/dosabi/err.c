/* HASH CRC-32:0xc13fbf4e */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_ERR_C
#define GUARD_LIBC_AUTO_DOSABI_ERR_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../err.h"

DECL_BEGIN

/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTERN ATTR_SECTION(".text.crt.dos.error") ATTR_LIBC_PRINTF(1, 2) void
(VLIBDCALL libd_warn)(char const *format,
                      ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_vwarn(format, args);
	va_end(args);
}
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTERN ATTR_SECTION(".text.crt.dos.error") ATTR_LIBC_PRINTF(1, 0) void
(LIBDCALL libd_vwarn)(char const *format,
                      va_list args) THROWS(...) {
	libc_vwarn(format, args);
}
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTERN ATTR_SECTION(".text.crt.dos.error") ATTR_LIBC_PRINTF(1, 2) void
(VLIBDCALL libd_warnx)(char const *format,
                       ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_vwarnx(format, args);
	va_end(args);
}
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTERN ATTR_SECTION(".text.crt.dos.error") ATTR_LIBC_PRINTF(1, 0) void
(LIBDCALL libd_vwarnx)(char const *format,
                       va_list args) THROWS(...) {
	libc_vwarnx(format, args);
}
/* Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.dos.error") ATTR_NORETURN ATTR_LIBC_PRINTF(2, 3) void
(VLIBDCALL libd_err)(int status,
                     char const *format,
                     ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_verr(status, format, args);
}
/* Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.dos.error") ATTR_NORETURN ATTR_LIBC_PRINTF(2, 0) void
(LIBDCALL libd_verr)(int status,
                     char const *format,
                     va_list args) THROWS(...) {
	libc_verr(status, format, args);
}
/* Same as `warnx()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.dos.error") ATTR_NORETURN ATTR_LIBC_PRINTF(2, 3) void
(VLIBDCALL libd_errx)(int status,
                      char const *format,
                      ...) THROWS(...) {
	va_list args;
	va_start(args, format);
	libc_verrx(status, format, args);
}
/* Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.dos.error") ATTR_NORETURN ATTR_LIBC_PRINTF(2, 0) void
(LIBDCALL libd_verrx)(int status,
                      char const *format,
                      va_list args) THROWS(...) {
	libc_verrx(status, format, args);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$warn, libd_warn);
DEFINE_PUBLIC_ALIAS(DOS$vwarn, libd_vwarn);
DEFINE_PUBLIC_ALIAS(DOS$warnx, libd_warnx);
DEFINE_PUBLIC_ALIAS(DOS$vwarnx, libd_vwarnx);
DEFINE_PUBLIC_ALIAS(DOS$err, libd_err);
DEFINE_PUBLIC_ALIAS(DOS$verr, libd_verr);
DEFINE_PUBLIC_ALIAS(DOS$errx, libd_errx);
DEFINE_PUBLIC_ALIAS(DOS$verrx, libd_verrx);

#endif /* !GUARD_LIBC_AUTO_DOSABI_ERR_C */
