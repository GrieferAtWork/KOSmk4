/* HASH CRC-32:0x279d1e52 */
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 2) void
NOTHROW_CB_NCX(VLIBDCALL libd_warn)(char const *format,
                                    ...) {
	va_list args;
	va_start(args, format);
	libc_vwarn(format, args);
	va_end(args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> warn(3), vwarn(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 2) void
NOTHROW_CB_NCX(VLIBCCALL libc_warn)(char const *format,
                                    ...) {
	va_list args;
	va_start(args, format);
	libc_vwarn(format, args);
	va_end(args);
}
#include <libc/errno.h>
/* >> warn(3), vwarn(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 0) void
NOTHROW_CB_NCX(LIBCCALL libc_vwarn)(char const *format,
                                    va_list args) {
	libc_vwarnc(__libc_geterrno_or(0), format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3) void
NOTHROW_CB_NCX(VLIBDCALL libd_warnc)(errno_t used_errno,
                                     char const *format,
                                     ...) {
	va_list args;
	va_start(args, format);
	libc_vwarnc(used_errno, format, args);
	va_end(args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3) void
NOTHROW_CB_NCX(VLIBCCALL libc_warnc)(errno_t used_errno,
                                     char const *format,
                                     ...) {
	va_list args;
	va_start(args, format);
	libc_vwarnc(used_errno, format, args);
	va_end(args);
}
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
/* >> warnc(3), vwarnc(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>: strerror(used_errno)\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 0) void
NOTHROW_CB_NCX(LIBCCALL libc_vwarnc)(errno_t used_errno,
                                     char const *format,
                                     va_list args) {

	libc_flockfile(stderr);

	libc_fprintf_unlocked(stderr, "%s: ", program_invocation_short_name);
	if (format) {
		libc_vfprintf_unlocked(stderr, format, args);
		libc_fprintf_unlocked(stderr, ": %s\n", libc_strerror(used_errno));
	} else {
		libc_fprintf_unlocked(stderr, "%s\n", libc_strerror(used_errno));
	}

	libc_funlockfile(stderr);

}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 2) void
NOTHROW_CB_NCX(VLIBDCALL libd_warnx)(char const *format,
                                     ...) {
	va_list args;
	va_start(args, format);
	libc_vwarnx(format, args);
	va_end(args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 2) void
NOTHROW_CB_NCX(VLIBCCALL libc_warnx)(char const *format,
                                     ...) {
	va_list args;
	va_start(args, format);
	libc_vwarnx(format, args);
	va_end(args);
}
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
/* >> warnx(3), vwarnx(3)
 * Print to stderr: `<program_invocation_short_name>: <format...>\n' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 0) void
NOTHROW_CB_NCX(LIBCCALL libc_vwarnx)(char const *format,
                                     va_list args) {

	libc_flockfile(stderr);

	libc_fprintf_unlocked(stderr, "%s: ", program_invocation_short_name);
	if (format)
		libc_vfprintf_unlocked(stderr, format, args);
	libc_fputc_unlocked('\n', stderr);

	libc_funlockfile(stderr);

}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3) void
NOTHROW_CB_NCX(VLIBDCALL libd_err)(int status,
                                   char const *format,
                                   ...) {
	va_list args;
	va_start(args, format);
	libc_verr(status, format, args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3) void
NOTHROW_CB_NCX(VLIBCCALL libc_err)(int status,
                                   char const *format,
                                   ...) {
	va_list args;
	va_start(args, format);
	libc_verr(status, format, args);
}
#include <libc/errno.h>
/* >> err(3), verr(3)
 * Same as `warn()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 0) void
NOTHROW_CB_NCX(LIBCCALL libc_verr)(int status,
                                   char const *format,
                                   va_list args) {
	libc_verrc(status, __libc_geterrno_or(0), format, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_NORETURN ATTR_IN_OPT(3) ATTR_LIBC_PRINTF(3, 4) void
NOTHROW_CB_NCX(VLIBDCALL libd_errc)(int status,
                                    errno_t used_errno,
                                    char const *format,
                                    ...) {
	va_list args;
	va_start(args, format);
	libc_verrc(status, used_errno, format, args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_IN_OPT(3) ATTR_LIBC_PRINTF(3, 4) void
NOTHROW_CB_NCX(VLIBCCALL libc_errc)(int status,
                                    errno_t used_errno,
                                    char const *format,
                                    ...) {
	va_list args;
	va_start(args, format);
	libc_verrc(status, used_errno, format, args);
}
/* >> errc(3), verrc(3)
 * Same as `warnc()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_IN_OPT(3) ATTR_LIBC_PRINTF(3, 0) void
NOTHROW_CB_NCX(LIBCCALL libc_verrc)(int status,
                                    errno_t used_errno,
                                    char const *format,
                                    va_list args) {
	libc_vwarnc(used_errno, format, args);
	libc_exit(status);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.error") ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3) void
NOTHROW_CB_NCX(VLIBDCALL libd_errx)(int status,
                                    char const *format,
                                    ...) {
	va_list args;
	va_start(args, format);
	libc_verrx(status, format, args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3) void
NOTHROW_CB_NCX(VLIBCCALL libc_errx)(int status,
                                    char const *format,
                                    ...) {
	va_list args;
	va_start(args, format);
	libc_verrx(status, format, args);
}
/* >> errx(3), verrx(3)
 * Same as `warnx()', but follow up by calling `exit(status)' */
INTERN ATTR_SECTION(".text.crt.error") ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 0) void
NOTHROW_CB_NCX(LIBCCALL libc_verrx)(int status,
                                    char const *format,
                                    va_list args) {
	libc_vwarnx(format, args);
	libc_exit(status);
}
#endif /* !__KERNEL__ */

DECL_END

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$warn,libd_warn,ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 2),NOTHROW_CB_NCX,VLIBDCALL,(char const *format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(warn,libc_warn,ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 2),NOTHROW_CB_NCX,VLIBCCALL,(char const *format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P_VOID(vwarn,libc_vwarn,ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 0),NOTHROW_CB_NCX,LIBCCALL,(char const *format, va_list args),(format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$warnc,libd_warnc,ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3),NOTHROW_CB_NCX,VLIBDCALL,(errno_t used_errno, char const *format, ...),(used_errno,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(warnc,libc_warnc,ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3),NOTHROW_CB_NCX,VLIBCCALL,(errno_t used_errno, char const *format, ...),(used_errno,format,));
DEFINE_PUBLIC_ALIAS_P_VOID(vwarnc,libc_vwarnc,ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 0),NOTHROW_CB_NCX,LIBCCALL,(errno_t used_errno, char const *format, va_list args),(used_errno,format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$warnx,libd_warnx,ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 2),NOTHROW_CB_NCX,VLIBDCALL,(char const *format, ...),(format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(warnx,libc_warnx,ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 2),NOTHROW_CB_NCX,VLIBCCALL,(char const *format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P_VOID(vwarnx,libc_vwarnx,ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(1, 0),NOTHROW_CB_NCX,LIBCCALL,(char const *format, va_list args),(format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$err,libd_err,ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3),NOTHROW_CB_NCX,VLIBDCALL,(int status, char const *format, ...),(status,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(err,libc_err,ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3),NOTHROW_CB_NCX,VLIBCCALL,(int status, char const *format, ...),(status,format,));
DEFINE_PUBLIC_ALIAS_P_VOID(verr,libc_verr,ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 0),NOTHROW_CB_NCX,LIBCCALL,(int status, char const *format, va_list args),(status,format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$errc,libd_errc,ATTR_NORETURN ATTR_IN_OPT(3) ATTR_LIBC_PRINTF(3, 4),NOTHROW_CB_NCX,VLIBDCALL,(int status, errno_t used_errno, char const *format, ...),(status,used_errno,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(errc,libc_errc,ATTR_NORETURN ATTR_IN_OPT(3) ATTR_LIBC_PRINTF(3, 4),NOTHROW_CB_NCX,VLIBCCALL,(int status, errno_t used_errno, char const *format, ...),(status,used_errno,format,));
DEFINE_PUBLIC_ALIAS_P_VOID(verrc,libc_verrc,ATTR_NORETURN ATTR_IN_OPT(3) ATTR_LIBC_PRINTF(3, 0),NOTHROW_CB_NCX,LIBCCALL,(int status, errno_t used_errno, char const *format, va_list args),(status,used_errno,format,args));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$errx,libd_errx,ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3),NOTHROW_CB_NCX,VLIBDCALL,(int status, char const *format, ...),(status,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(errx,libc_errx,ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 3),NOTHROW_CB_NCX,VLIBCCALL,(int status, char const *format, ...),(status,format,));
DEFINE_PUBLIC_ALIAS_P_VOID(verrx,libc_verrx,ATTR_NORETURN ATTR_IN_OPT(2) ATTR_LIBC_PRINTF(2, 0),NOTHROW_CB_NCX,LIBCCALL,(int status, char const *format, va_list args),(status,format,args));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_ERR_C */
