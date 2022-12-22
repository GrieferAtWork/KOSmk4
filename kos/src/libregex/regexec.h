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

/* Execute a regular expression.
 * @return: >= 0:        The # of bytes starting at `exec->rx_startoff' that got matched.
 * @return: -RE_NOMATCH: Nothing was matched
 * @return: -RE_ESPACE:  Out of memory
 * @return: -RE_ESIZE:   On-failure stack before too large. */
INTDEF WUNUSED NONNULL((1)) ssize_t
NOTHROW_NCX(CC libre_exec_match)(struct re_exec const *__restrict exec);

/* Similar to `re_exec_match', try to match a pattern against the given input buffer. Do this
 * with increasing offsets for the first `search_range' bytes, meaning at most `search_range'
 * regex matches will be performed.
 * @param: search_range: One plus the max starting  byte offset (from `exec->rx_startoff')  to
 *                       check. Too great values for `search_range' are automatically clamped.
 * @param: p_match_size: When non-NULL, set to the # of bytes that were actually matched.
 *                       This would have  been the return  value of  `re_exec_match(3R)'.
 * @return: >= 0:        The offset where the matched area starts (in `[exec->rx_startoff, exec->rx_startoff + search_range)').
 * @return: -RE_NOMATCH: Nothing was matched
 * @return: -RE_ESPACE:  Out of memory
 * @return: -RE_ESIZE:   On-failure stack before too large. */
INTDEF WUNUSED NONNULL((1)) ssize_t
NOTHROW_NCX(CC libre_exec_search)(struct re_exec const *__restrict exec,
                                  size_t search_range, size_t *p_match_size);

/* Same as `re_exec_search(3R)', but perform searching with starting
 * offsets  in   `[exec->rx_endoff - search_range, exec->rx_endoff)'
 * Too great values  for `search_range'  are automatically  clamped.
 * The return value will thus also be within that same range. */
INTDEF WUNUSED NONNULL((1)) ssize_t
NOTHROW_NCX(CC libre_exec_rsearch)(struct re_exec const *__restrict exec,
                                   size_t search_range, size_t *p_match_size);

DECL_END

#endif /* !GUARD_LIBREGEX_REGEXEC_H */
