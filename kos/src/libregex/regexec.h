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
#ifndef GUARD_LIBREGEX_REGEXEC_H
#define GUARD_LIBREGEX_REGEXEC_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libregex/regexec.h>

DECL_BEGIN

/* ASCII character trait flags (s.a. `/kos/kos/include/bits/crt/ctype.h') */
#define CTYPE_C_FLAG_CNTRL  0x01
#define CTYPE_C_FLAG_SPACE  0x02
#define CTYPE_C_FLAG_LOWER  0x04
#define CTYPE_C_FLAG_UPPER  0x08
#define CTYPE_C_FLAG_ALPHA  0x0c
#define CTYPE_C_FLAG_DIGIT  0x10
#define CTYPE_C_FLAG_XDIGIT 0x30
#define CTYPE_C_FLAG_ALNUM  0x1c
#define CTYPE_C_FLAG_PUNCT  0x40
#define CTYPE_C_FLAG_GRAPH  0x5c
#define CTYPE_C_FLAG_PRINT  0xdc


/* Execute a regular expression.
 * @param: nmatch: # of elements to fill in `pmatch'
 * @param: pmatch: Offsets of matched groups (up to the first `nmatch' groups
 *                 are written, but only on success; iow: when `return >= 0')
 *                 Offsets written INCLUDE `exec->rx_startoff'
 * @return: >= 0:        The # of bytes starting at `exec->rx_startoff' that got matched.
 * @return: -RE_NOMATCH: Nothing was matched
 * @return: -RE_ESPACE:  Out of memory
 * @return: -RE_ESIZE:   On-failure stack before too large. */
INTDEF WUNUSED NONNULL((1)) ssize_t
NOTHROW_NCX(CC libre_exec_match)(struct re_exec const *__restrict exec,
                                 size_t nmatch, re_regmatch_t *pmatch);

/* Similar to `re_exec_match', try to match pattern  against the given input buffer. Do  this
 * with increasing offsets for the first `search_range' bytes, meaning at most `search_range'
 * regex matches will be performed.
 * @param: search_range: One plus the max starting  byte offset (from `exec->rx_startoff')  to
 *                       check. Too great values for `search_range' are automatically clamped.
 * @param: nmatch: # of elements to fill in `pmatch'
 * @param: pmatch: Offsets of matched groups (up to the first `nmatch' groups
 *                 are written, but only on success; iow: when `return >= 0')
 *                 Offsets written INCLUDE `exec->rx_startoff'
 * @param: p_match_size: When non-NULL, store the # of bytes that were here on success
 *                       This would have been  the return value of  `re_exec_match()'.
 * @return: >= 0:        The offset where the matched area starts (`< exec->rx_startoff + search_range').
 * @return: -RE_NOMATCH: Nothing was matched
 * @return: -RE_ESPACE:  Out of memory
 * @return: -RE_ESIZE:   On-failure stack before too large. */
INTDEF WUNUSED NONNULL((1)) ssize_t
NOTHROW_NCX(CC libre_exec_search)(struct re_exec const *__restrict exec, size_t search_range,
                                  size_t nmatch, re_regmatch_t *pmatch, size_t *p_match_size);

/* Same as `re_exec_search()', but perform searching with starting
 * offsets in  `[exec->rx_endoff - search_range, exec->rx_endoff)'
 * Too  great values for `search_range' are automatically clamped.
 * The return value will thus also be within that same range. */
INTDEF WUNUSED NONNULL((1)) ssize_t
NOTHROW_NCX(CC libre_exec_rsearch)(struct re_exec const *__restrict exec, size_t search_range,
                                   size_t nmatch, re_regmatch_t *pmatch, size_t *p_match_size);

DECL_END

#endif /* !GUARD_LIBREGEX_REGEXEC_H */
