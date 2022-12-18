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
#ifndef _LIBREGEX_REGEXEC_H
#define _LIBREGEX_REGEXEC_H 1

#include "api.h"
/**/

#include <bits/types.h>

__DECL_BEGIN

struct re_code;
struct iovec;

/* Flags for `re_exec_matchv' */
#define RE_EXEC_NOTBOL 0x0001 /* '^' (REOP_AT_SOL) doesn't match at the start of the input buffer (but only at an actual begin-of-line) */
#define RE_EXEC_NOTEOL 0x0002 /* '$' (REOP_AT_EOL) doesn't match at the end of the input buffer (but only before an actual line-feed) */

struct re_exec {
	struct re_code const *rx_code;     /* [1..1] Regex code */
	struct iovec const   *rx_iov;      /* [0..*] I/O vector of input data to scan */
	__size_t              rx_startoff; /* Starting byte offset into `rx_iov' of data to match. */
	__size_t              rx_endoff;   /* Ending byte offset into `rx_iov' of data to match. */
	__size_t              rx_extra;    /* Number of extra bytes that can still be read after `rx_endoff'
	                                    * Usually `0', but when  non-zero, `REOP_AT_*' opcodes will  try
	                                    * to read this extra memory in order to check matches. */
	unsigned int          rx_eflags;   /* Execution flags (set of `RE_EXEC_*') */
};

/* *sigh* this has to be an int for glibc compat (but it should have been a `size_t')
 * NOTE: When nothing got matched for some given group, set to `RE_REGOFF_UNSET'. */
typedef unsigned int re_regoff_t;
#define RE_REGOFF_UNSET ((re_regoff_t)-1)

typedef struct {
	re_regoff_t rm_so;
	re_regoff_t rm_eo;
} re_regmatch_t;

/* Execute a regular expression.
 * @param: nmatch: # of elements to fill in `pmatch'
 * @param: pmatch: Offsets of matched groups (up to the first `nmatch' groups
 *                 are written, but only on success; iow: when `return >= 0')
 *                 Offsets written INCLUDE `exec->rx_startoff'
 * @return: >= 0:        The # of bytes starting at `exec->rx_startoff' that got matched.
 * @return: -RE_NOMATCH: Nothing was matched
 * @return: -RE_ESPACE:  Out of memory
 * @return: -RE_ESIZE:   On-failure stack before too large. */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __ssize_t
__NOTHROW_NCX_T(LIBREGEX_CC *PRE_EXEC_MATCH)(struct re_exec const *__restrict exec,
                                             size_t nmatch, re_regmatch_t *pmatch);
#ifdef LIBREGEX_WANT_PROTOTYPES
LIBREGEX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ssize_t
__NOTHROW_NCX(LIBREGEX_CC re_exec_match)(struct re_exec const *__restrict exec,
                                         size_t nmatch, re_regmatch_t *pmatch);
#endif /* LIBREGEX_WANT_PROTOTYPES */

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
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __ssize_t
__NOTHROW_NCX_T(LIBREGEX_CC *PRE_EXEC_SEARCH)(struct re_exec const *__restrict exec, size_t search_range,
                                              size_t nmatch, re_regmatch_t *pmatch, size_t *p_match_size);
#ifdef LIBREGEX_WANT_PROTOTYPES
LIBREGEX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ssize_t
__NOTHROW_NCX(LIBREGEX_CC re_exec_search)(struct re_exec const *__restrict exec, size_t search_range,
                                          size_t nmatch, re_regmatch_t *pmatch, size_t *p_match_size);
#endif /* LIBREGEX_WANT_PROTOTYPES */

/* Same as `re_exec_search()', but perform searching with starting
 * offsets in  `[exec->rx_endoff - search_range, exec->rx_endoff)'
 * Too  great values for `search_range' are automatically clamped.
 * The return value will thus also be within that same range. */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __ssize_t
__NOTHROW_NCX_T(LIBREGEX_CC *PRE_EXEC_RSEARCH)(struct re_exec const *__restrict exec, size_t search_range,
                                               size_t nmatch, re_regmatch_t *pmatch, size_t *p_match_size);
#ifdef LIBREGEX_WANT_PROTOTYPES
LIBREGEX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ssize_t
__NOTHROW_NCX(LIBREGEX_CC re_exec_rsearch)(struct re_exec const *__restrict exec, size_t search_range,
                                           size_t nmatch, re_regmatch_t *pmatch, size_t *p_match_size);
#endif /* LIBREGEX_WANT_PROTOTYPES */

__DECL_END

#endif /* !_LIBREGEX_REGEXEC_H */
