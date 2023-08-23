/* HASH CRC-32:0xeb4cf3a7 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_ARGP_H
#define GUARD_LIBC_USER_ARGP_H 1

#include "../api.h"
#include "../auto/argp.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <argp.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> argp_parse(3)
 * @param: flags: Set  of  `ARGP_PARSE_ARGV0  | ARGP_NO_ERRS  |  ARGP_NO_ARGS |
 *                ARGP_IN_ORDER | ARGP_NO_HELP | ARGP_NO_EXIT | ARGP_LONG_ONLY' */
INTDEF ATTR_IN(1) ATTR_INS(3, 2) ATTR_OUT(5) error_t NOTHROW_NCX(LIBCCALL libc_argp_parse)(struct argp const *__restrict ap, int argc, char **__restrict argv, unsigned int flags, int *__restrict arg_index, void *input);
/* >> argp_parse(3)
 * @param: flags: Set of `ARGP_HELP_*' */
INTDEF ATTR_IN(1) ATTR_IN(4) ATTR_INOUT(2) void NOTHROW_NCX(LIBCCALL libc_argp_help)(struct argp const *__restrict ap, FILE *__restrict stream, unsigned int flags, char __KOS_FIXED_CONST *__restrict name);
/* >> argp_state_help(3)
 * @param: flags: Set of `ARGP_HELP_*' */
INTDEF ATTR_INOUT_OPT(2) ATTR_IN_OPT(1) void NOTHROW_NCX(LIBCCALL libc_argp_state_help)(struct argp_state const *__restrict state, FILE *__restrict stream, unsigned int flags);
INTDEF ATTR_IN_OPT(1) ATTR_IN_OPT(2) void *NOTHROW_NCX(LIBCCALL libc__argp_input)(struct argp const *__restrict ap, struct argp_state const *__restrict state);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_ARGP_H */
