/* HASH CRC-32:0x98d3d571 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_ARGP_C
#define GUARD_LIBC_AUTO_ARGP_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/argp.h"
#include "../user/ctype.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#include "../libc/globals.h"
#include <sysexits.h> /* for `EX_USAGE' */
#ifndef __KERNEL__
#undef argp_program_version
#undef argp_program_version_hook
#undef argp_program_bug_address
#undef argp_err_exit_status
INTERN ATTR_SECTION(".bss.crt.compat.glibc.string.argp") char const *libc_argp_program_version = NULL;
INTERN ATTR_SECTION(".bss.crt.compat.glibc.string.argp") __argp_program_version_hook_t libc_argp_program_version_hook = NULL;
INTERN ATTR_SECTION(".bss.crt.compat.glibc.string.argp") char const *libc_argp_program_bug_address = NULL;
INTERN ATTR_SECTION(".data.crt.compat.glibc.string.argp") int libc_argp_err_exit_status = EX_USAGE;
DEFINE_PUBLIC_ALIAS(argp_program_version, libc_argp_program_version);
DEFINE_PUBLIC_ALIAS(argp_program_version_hook, libc_argp_program_version_hook);
DEFINE_PUBLIC_ALIAS(argp_program_bug_address, libc_argp_program_bug_address);
DEFINE_PUBLIC_ALIAS(argp_err_exit_status, libc_argp_err_exit_status);
#define argp_program_version      GET_NOREL_GLOBAL(argp_program_version)
#define argp_program_version_hook GET_NOREL_GLOBAL(argp_program_version_hook)
#define argp_program_bug_address  GET_NOREL_GLOBAL(argp_program_bug_address)
#define argp_err_exit_status      GET_NOREL_GLOBAL(argp_err_exit_status)
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN(1) void
NOTHROW_NCX(LIBCCALL libc_argp_usage)(struct argp_state const *state) {
	libc_argp_state_help(state, stderr, ARGP_HELP_STD_USAGE);
}
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN(2) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(2, 0) void
NOTHROW_NCX(LIBCCALL libc_argp_verror)(struct argp_state const *__restrict state,
                                       char const *__restrict format,
                                       va_list args) {
	FILE *out;
	char const *appname;
	if unlikely(state && (state->flags & ARGP_NO_ERRS))
		return;
	out = NULL;
	if likely(state)
		out = state->err_stream;

	if unlikely(!out)
		out = stderr;

	if unlikely(!out)
		return;
	appname = NULL;
	if likely(state)
		appname = state->name;
#ifdef program_invocation_name
	if unlikely(!appname)
		appname = program_invocation_name;
#endif /* program_invocation_name */
	if unlikely(!appname)
		appname = "?";

	/* Print the message. */

	(void)libc_flockfile(out);

	(void)libc_fprintf_unlocked(out, "%s: ", appname);
	(void)libc_vfprintf_unlocked(out, format, args);

	(void)libc_fputc_unlocked('\n', out);



	(void)libc_argp_state_help(state, out, ARGP_HELP_STD_ERR);

	(void)libc_funlockfile(out);

}
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN_OPT(1) ATTR_IN_OPT(4) ATTR_LIBC_PRINTF(4, 0) void
NOTHROW_NCX(LIBCCALL libc_argp_vfailure)(struct argp_state const *__restrict state,
                                         int exit_status,
                                         errno_t errnum,
                                         char const *__restrict format,
                                         va_list args) {
	FILE *out;
	char const *appname;
	if unlikely(state && (state->flags & ARGP_NO_ERRS))
		return;
	out = NULL;
	if likely(state)
		out = state->err_stream;

	if unlikely(!out)
		out = stderr;

	if unlikely(!out)
		return;
	appname = NULL;
	if likely(state)
		appname = state->name;
#ifdef program_invocation_name
	if unlikely(!appname)
		appname = program_invocation_name;
#endif /* program_invocation_name */
	if unlikely(!appname)
		appname = "?";

	/* Print the message. */

	(void)libc_flockfile(out);


	(void)libc_fputs_unlocked(appname, out);



	if (format) {

		(void)libc_fputs_unlocked(": ", out);



		(void)libc_vfprintf_unlocked(out, format, args);
	}
	if (errnum) {

		(void)libc_fputs_unlocked(": ", out);
		(void)libc_fputs_unlocked(libc_strerror(errnum), out);



	}

	(void)libc_fputc_unlocked('\n', out);



	(void)libc_argp_state_help(state, out, ARGP_HELP_STD_ERR);

	(void)libc_funlockfile(out);


	/* Exit the program (if need be) */
	if (exit_status && (!state || !(state->flags & ARGP_NO_EXIT)))
		libc_exit(exit_status);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.compat.glibc.string.argp") ATTR_IN(2) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(2, 3) void
NOTHROW_NCX(VLIBDCALL libd_argp_error)(struct argp_state const *__restrict state,
                                       char const *__restrict format,
                                       ...) {
	va_list args;
	va_start(args, format);
	libc_argp_verror(state, format, args);
	va_end(args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN(2) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(2, 3) void
NOTHROW_NCX(VLIBCCALL libc_argp_error)(struct argp_state const *__restrict state,
                                       char const *__restrict format,
                                       ...) {
	va_list args;
	va_start(args, format);
	libc_argp_verror(state, format, args);
	va_end(args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.compat.glibc.string.argp") ATTR_IN(4) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(4, 5) void
NOTHROW_NCX(VLIBDCALL libd_argp_failure)(struct argp_state const *__restrict state,
                                         int status,
                                         errno_t errnum,
                                         char const *__restrict format,
                                         ...) {
	va_list args;
	va_start(args, format);
	libc_argp_vfailure(state, status, errnum, format, args);
	va_end(args);
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN(4) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(4, 5) void
NOTHROW_NCX(VLIBCCALL libc_argp_failure)(struct argp_state const *__restrict state,
                                         int status,
                                         errno_t errnum,
                                         char const *__restrict format,
                                         ...) {
	va_list args;
	va_start(args, format);
	libc_argp_vfailure(state, status, errnum, format, args);
	va_end(args);
}
#include <bits/crt/argp.h>
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc__option_is_short)(struct argp_option const *opt) {
	int opt_key;
	if (opt->flags & __OPTION_DOC)
		return 0;
	opt_key = opt->key;
	return opt_key > 0 && opt_key <= 0xff && libc_isprint(opt_key);
}
#include <bits/crt/argp.h>
/* >> _option_is_end(3)
 * Check if `opt' represents the end of an option-chain */
INTERN ATTR_SECTION(".text.crt.compat.glibc.string.argp") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc__option_is_end)(struct argp_option const *opt) {
	return !opt->name && !opt->key && !opt->doc && !opt->group;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(__argp_usage,libc_argp_usage,ATTR_IN(1),NOTHROW_NCX,LIBCCALL,(struct argp_state const *state),(state));
DEFINE_PUBLIC_ALIAS_P_VOID(argp_usage,libc_argp_usage,ATTR_IN(1),NOTHROW_NCX,LIBCCALL,(struct argp_state const *state),(state));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$__argp_error,libd_argp_error,ATTR_IN(2) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(2, 3),NOTHROW_NCX,VLIBDCALL,(struct argp_state const *__restrict state, char const *__restrict format, ...),(state,format,));
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$argp_error,libd_argp_error,ATTR_IN(2) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(2, 3),NOTHROW_NCX,VLIBDCALL,(struct argp_state const *__restrict state, char const *__restrict format, ...),(state,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(__argp_error,libc_argp_error,ATTR_IN(2) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(2, 3),NOTHROW_NCX,VLIBCCALL,(struct argp_state const *__restrict state, char const *__restrict format, ...),(state,format,));
DEFINE_PUBLIC_ALIAS_P_VOID(argp_error,libc_argp_error,ATTR_IN(2) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(2, 3),NOTHROW_NCX,VLIBCCALL,(struct argp_state const *__restrict state, char const *__restrict format, ...),(state,format,));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$__argp_failure,libd_argp_failure,ATTR_IN(4) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(4, 5),NOTHROW_NCX,VLIBDCALL,(struct argp_state const *__restrict state, int status, errno_t errnum, char const *__restrict format, ...),(state,status,errnum,format,));
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$argp_failure,libd_argp_failure,ATTR_IN(4) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(4, 5),NOTHROW_NCX,VLIBDCALL,(struct argp_state const *__restrict state, int status, errno_t errnum, char const *__restrict format, ...),(state,status,errnum,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(__argp_failure,libc_argp_failure,ATTR_IN(4) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(4, 5),NOTHROW_NCX,VLIBCCALL,(struct argp_state const *__restrict state, int status, errno_t errnum, char const *__restrict format, ...),(state,status,errnum,format,));
DEFINE_PUBLIC_ALIAS_P_VOID(argp_failure,libc_argp_failure,ATTR_IN(4) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(4, 5),NOTHROW_NCX,VLIBCCALL,(struct argp_state const *__restrict state, int status, errno_t errnum, char const *__restrict format, ...),(state,status,errnum,format,));
DEFINE_PUBLIC_ALIAS_P(__option_is_short,libc__option_is_short,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(struct argp_option const *opt),(opt));
DEFINE_PUBLIC_ALIAS_P(_option_is_short,libc__option_is_short,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(struct argp_option const *opt),(opt));
DEFINE_PUBLIC_ALIAS_P(__option_is_end,libc__option_is_end,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(struct argp_option const *opt),(opt));
DEFINE_PUBLIC_ALIAS_P(_option_is_end,libc__option_is_end,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(struct argp_option const *opt),(opt));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_ARGP_C */
