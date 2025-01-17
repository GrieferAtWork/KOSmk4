/* HASH CRC-32:0x71d6d463 */
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
#ifndef GUARD_LIBC_AUTO_ARGP_H
#define GUARD_LIBC_AUTO_ARGP_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <argp.h>

DECL_BEGIN

#include <stdio.h> /* FILE */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> argp_parse(3)
 * @param: flags: Set  of  `ARGP_PARSE_ARGV0  | ARGP_NO_ERRS  |  ARGP_NO_ARGS |
 *                ARGP_IN_ORDER | ARGP_NO_HELP | ARGP_NO_EXIT | ARGP_LONG_ONLY' */
INTDEF ATTR_IN(1) ATTR_INS(3, 2) ATTR_OUT(5) error_t NOTHROW_NCX(LIBDCALL libd_argp_parse)(struct argp const *__restrict ap, int argc, char **__restrict argv, unsigned int flags, int *__restrict arg_index, void *input);
/* >> argp_parse(3)
 * @param: flags: Set of `ARGP_HELP_*' */
INTDEF ATTR_IN(1) ATTR_IN(4) ATTR_INOUT(2) void NOTHROW_NCX(LIBDCALL libd_argp_help)(struct argp const *__restrict ap, FILE *__restrict stream, unsigned int flags, char __KOS_FIXED_CONST *__restrict name);
/* >> argp_state_help(3)
 * @param: flags: Set of `ARGP_HELP_*' */
INTDEF ATTR_INOUT_OPT(2) ATTR_IN_OPT(1) void NOTHROW_NCX(LIBDCALL libd_argp_state_help)(struct argp_state const *__restrict state, FILE *__restrict stream, unsigned int flags);
INTDEF ATTR_IN(1) void NOTHROW_NCX(LIBDCALL libd_argp_usage)(struct argp_state const *state);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) void NOTHROW_NCX(LIBCCALL libc_argp_usage)(struct argp_state const *state);
INTDEF ATTR_IN(2) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(2, 0) void NOTHROW_NCX(LIBCCALL libc_argp_verror)(struct argp_state const *__restrict state, char const *__restrict format, va_list args);
INTDEF ATTR_IN_OPT(1) ATTR_IN_OPT(4) ATTR_LIBC_PRINTF(4, 0) void NOTHROW_NCX(LIBCCALL libc_argp_vfailure)(struct argp_state const *__restrict state, int exit_status, errno_t errnum, char const *__restrict format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(2, 3) void NOTHROW_NCX(VLIBDCALL libd_argp_error)(struct argp_state const *__restrict state, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(2, 3) void NOTHROW_NCX(VLIBCCALL libc_argp_error)(struct argp_state const *__restrict state, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(4) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(4, 5) void NOTHROW_NCX(VLIBDCALL libd_argp_failure)(struct argp_state const *__restrict state, int status, errno_t errnum, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(4) ATTR_IN_OPT(1) ATTR_LIBC_PRINTF(4, 5) void NOTHROW_NCX(VLIBCCALL libc_argp_failure)(struct argp_state const *__restrict state, int status, errno_t errnum, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd__option_is_short)(struct argp_option const *opt);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc__option_is_short)(struct argp_option const *opt);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> _option_is_end(3)
 * Check if `opt' represents the end of an option-chain */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd__option_is_end)(struct argp_option const *opt);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> _option_is_end(3)
 * Check if `opt' represents the end of an option-chain */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc__option_is_end)(struct argp_option const *opt);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN_OPT(1) ATTR_IN_OPT(2) void *NOTHROW_NCX(LIBDCALL libd__argp_input)(struct argp const *__restrict ap, struct argp_state const *__restrict state);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ARGP_H */
