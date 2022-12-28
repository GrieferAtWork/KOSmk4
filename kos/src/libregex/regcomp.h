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
#ifndef GUARD_LIBREGEX_REGCOMP_H
#define GUARD_LIBREGEX_REGCOMP_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libregex/regcomp.h>

#ifndef NDEBUG
#include <format-printer.h>
#endif /* !NDEBUG */

DECL_BEGIN

/* Parse and yield the next regex-token pointed-to by `self->rep_pos'
 * @return: * : A unicode character, or one of `RE_TOKEN_*' */
INTDEF WUNUSED NONNULL((1)) re_token_t
NOTHROW_NCX(CC libre_parser_yield)(struct re_parser *__restrict self);

/* Parse  and compile the pattern given to `self' to generate code.
 * Even  upon error, `self'  remains in a  valid state (except that
 * you're  not allowed to call `re_compiler_compile(3R)' again), so
 * that the caller has to invoke `re_compiler_fini(3R)' in order to
 * perform cleanup.
 * Upon success, members of `self' are initialized as:
 * - *rec_parser.rep_pos    == '\0'
 * - rec_parser.rep_pos     == rec_parser.rep_end
 * - rec_parser.rep_syntax  == <unchanged>
 * - rec_parser.rec_cbase   == <pointer-to-struct re_code>
 * - rec_parser.rec_estart  == <undefined>
 * - rec_parser.rec_cpos    == <undefined>
 * - rec_parser.rec_cend    == <code-end-pointer (1 past the `REOP_MATCHED[_PERFECT]' opcode)>
 * - rec_parser.rec_ngrp    == <greaters-referenced-group + 1>
 * - rec_parser.rec_nvar    == <greaters-referenced-var + 1>
 * - rec_parser.rec_grpinfo == <undefined>
 * @return: RE_NOERROR: Success
 * @return: RE_BADPAT:  General pattern syntax error.
 * @return: RE_ECTYPE:  Invalid/unknown character class name.
 * @return: RE_EESCAPE: Trailing backslash.
 * @return: RE_ESUBREG: Invalid back reference.
 * @return: RE_EBRACK:  Unmatched '['.
 * @return: RE_EPAREN:  Unmatched '('.
 * @return: RE_EBRACE:  Unmatched '{'.
 * @return: RE_BADBR:   Invalid contents of '{...}'.
 * @return: RE_ERANGE:  Invalid range end (e.g. '[z-a]').
 * @return: RE_ESPACE:  Out of memory.
 * @return: RE_BADRPT:  Nothing is preceding '+', '*', '?' or '{'.
 * @return: RE_EEND:    Unexpected end of pattern.
 * @return: RE_ESIZE:   Compiled pattern bigger than 2^16 bytes.
 * @return: RE_ERPAREN: Unmatched ')' (only when `RE_SYNTAX_UNMATCHED_RIGHT_PAREN_ORD' was set)
 * @return: RE_EILLSEQ: Illegal unicode character (when `RE_NO_UTF8' wasn't set)
 * @return: RE_EILLSET: Tried to combine raw bytes with unicode characters in charsets (e.g. "[Ä\xC3]") */
INTDEF WUNUSED NONNULL((1)) re_errno_t
NOTHROW_NCX(CC libre_compiler_compile)(struct re_compiler *__restrict self);

#ifndef NDEBUG
/* Print a disassembly of `self' (for debugging) */
INTDEF NONNULL((1)) ssize_t
NOTHROW_NCX(CC libre_code_disasm)(struct re_code const *__restrict self,
                                  pformatprinter printer, void *arg);
#endif /* !NDEBUG */

DECL_END

#endif /* !GUARD_LIBREGEX_REGCOMP_H */
