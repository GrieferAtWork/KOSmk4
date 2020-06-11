/* HASH CRC-32:0xc5018340 */
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
#ifndef GUARD_LIBC_AUTO_ERR_H
#define GUARD_LIBC_AUTO_ERR_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <err.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTDEF ATTR_LIBC_PRINTF(1, 2) void (VLIBCCALL libc_warn)(char const *format, ...) THROWS(...);
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTDEF ATTR_LIBC_PRINTF(1, 0) void (LIBCCALL libc_vwarn)(char const *format, va_list args) THROWS(...);
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTDEF ATTR_LIBC_PRINTF(1, 2) void (VLIBCCALL libc_warnx)(char const *format, ...) THROWS(...);
/* Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTDEF ATTR_LIBC_PRINTF(1, 0) void (LIBCCALL libc_vwarnx)(char const *format, va_list args) THROWS(...);
/* Same as `warn()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_LIBC_PRINTF(2, 3) void (VLIBCCALL libc_err)(int status, char const *format, ...) THROWS(...);
/* Same as `warn()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_LIBC_PRINTF(2, 0) void (LIBCCALL libc_verr)(int status, char const *format, va_list args) THROWS(...);
/* Same as `warnx()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_LIBC_PRINTF(2, 3) void (VLIBCCALL libc_errx)(int status, char const *format, ...) THROWS(...);
/* Same as `warn()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_LIBC_PRINTF(2, 0) void (LIBCCALL libc_verrx)(int status, char const *format, va_list args) THROWS(...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ERR_H */
