/* HASH CRC-32:0x44c79b70 */
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
#ifndef GUARD_LIBC_AUTO_ERROR_H
#define GUARD_LIBC_AUTO_ERROR_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <error.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> error(3)
 * Helper  function  for printing  an error  message to  `stderr' and  possibly exiting  the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `STATUS' is non-zero, follow up with a call to `exit(status)' */
INTDEF ATTR_LIBC_PRINTF(3, 4) void (VLIBDCALL libd_error)(int status, errno_t errnum, const char *format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> error(3)
 * Helper  function  for printing  an error  message to  `stderr' and  possibly exiting  the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `STATUS' is non-zero, follow up with a call to `exit(status)' */
INTDEF ATTR_LIBC_PRINTF(3, 4) void (VLIBCCALL libc_error)(int status, errno_t errnum, const char *format, ...) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> error_at_line(3)
 * Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally,    when   `error_one_per_line'   is    non-zero,   consecutive   calls    to   this   function   that
 * pass the same values for `filename' and `line' will not produce the error message. */
INTDEF ATTR_LIBC_PRINTF(5, 6) void (VLIBDCALL libd_error_at_line)(int status, errno_t errnum, char const *filename, unsigned int line, char const *format, ...) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> error_at_line(3)
 * Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally,    when   `error_one_per_line'   is    non-zero,   consecutive   calls    to   this   function   that
 * pass the same values for `filename' and `line' will not produce the error message. */
INTDEF ATTR_LIBC_PRINTF(5, 6) void (VLIBCCALL libc_error_at_line)(int status, errno_t errnum, char const *filename, unsigned int line, char const *format, ...) THROWS(...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ERROR_H */
