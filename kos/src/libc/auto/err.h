/* HASH CRC-32:0xd6cfb114 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> warn(3), vwarn(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTDEF ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 2) void NOTHROW_CB_NCX(VLIBDCALL libd_warn)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> warn(3), vwarn(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTDEF ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 2) void NOTHROW_CB_NCX(VLIBCCALL libc_warn)(char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> warn(3), vwarn(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTDEF ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 0) void NOTHROW_CB_NCX(LIBDCALL libd_vwarn)(char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> warn(3), vwarn(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTDEF ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 0) void NOTHROW_CB_NCX(LIBCCALL libc_vwarn)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
INTDEF ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3) void NOTHROW_CB_NCX(VLIBDCALL libd_warnc)(errno_t used_errno, char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
INTDEF ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3) void NOTHROW_CB_NCX(VLIBCCALL libc_warnc)(errno_t used_errno, char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
INTDEF ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 0) void NOTHROW_CB_NCX(LIBDCALL libd_vwarnc)(errno_t used_errno, char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
INTDEF ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 0) void NOTHROW_CB_NCX(LIBCCALL libc_vwarnc)(errno_t used_errno, char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTDEF ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 2) void NOTHROW_CB_NCX(VLIBDCALL libd_warnx)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTDEF ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 2) void NOTHROW_CB_NCX(VLIBCCALL libc_warnx)(char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTDEF ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 0) void NOTHROW_CB_NCX(LIBDCALL libd_vwarnx)(char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTDEF ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 0) void NOTHROW_CB_NCX(LIBCCALL libc_vwarnx)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3) void NOTHROW_CB_NCX(VLIBDCALL libd_err)(int status, char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3) void NOTHROW_CB_NCX(VLIBCCALL libc_err)(int status, char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 0) void NOTHROW_CB_NCX(LIBDCALL libd_verr)(int status, char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 0) void NOTHROW_CB_NCX(LIBCCALL libc_verr)(int status, char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_IN_OPT(3) ATTR_LIBC_PRINTF(3, 4) void NOTHROW_CB_NCX(VLIBDCALL libd_errc)(int status, errno_t used_errno, char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_IN_OPT(3) ATTR_LIBC_PRINTF(3, 4) void NOTHROW_CB_NCX(VLIBCCALL libc_errc)(int status, errno_t used_errno, char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_IN_OPT(3) ATTR_LIBC_PRINTF(3, 0) void NOTHROW_CB_NCX(LIBDCALL libd_verrc)(int status, errno_t used_errno, char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_IN_OPT(3) ATTR_LIBC_PRINTF(3, 0) void NOTHROW_CB_NCX(LIBCCALL libc_verrc)(int status, errno_t used_errno, char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3) void NOTHROW_CB_NCX(VLIBDCALL libd_errx)(int status, char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3) void NOTHROW_CB_NCX(VLIBCCALL libc_errx)(int status, char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 0) void NOTHROW_CB_NCX(LIBDCALL libd_verrx)(int status, char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
INTDEF ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 0) void NOTHROW_CB_NCX(LIBCCALL libc_verrx)(int status, char const *format, va_list args);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ERR_H */
