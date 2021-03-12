/* HASH CRC-32:0x8489146a */
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
#ifndef GUARD_LIBC_AUTO_REGEX_H
#define GUARD_LIBC_AUTO_REGEX_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <regex.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Sets the current default syntax to `syntax', and return the old syntax.
 * You can also simply assign to the `re_syntax_options' variable */
INTDEF reg_syntax_t NOTHROW_NCX(LIBDCALL libd_re_set_syntax)(reg_syntax_t syntax);
/* Compile the regular expression `pattern', with length `length'
 * and syntax given by the global `re_syntax_options', into the buffer
 * `buffer'. Return NULL if successful, and an error string if not.
 * To free the allocated storage, you must call `regfree' on `buffer'.
 * Note that the translate table must either have been initialized by
 * `regcomp', with a malloc'd value, or set to NULL before calling `regfree' */
INTDEF char const *NOTHROW_NCX(LIBDCALL libd_re_compile_pattern)(char const *pattern, size_t length, struct re_pattern_buffer *buffer);
/* Compile a fastmap for the compiled pattern in `buffer'; used to
 * accelerate searches. Return 0 if successful and `-2' if was an internal error */
INTDEF int NOTHROW_NCX(LIBDCALL libd_re_compile_fastmap)(struct re_pattern_buffer *buffer);
/* Search in the string `string' (with length `length') for the pattern
 * compiled into `buffer'. Start searching at position `start', for `range'
 * characters. Return the starting position of the match, `-1' for no
 * match, or `-2' for an internal error. Also return register
 * information in `regs' (if `regs' and `buffer'->no_sub are nonzero) */
INTDEF int NOTHROW_NCX(LIBDCALL libd_re_search)(struct re_pattern_buffer *buffer, char const *string, int length, int start, int range, struct re_registers *regs);
/* Like `re_search', but search in the concatenation of `string1'
 * and `string2'. Also, stop searching at index `start + stop' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_re_search_2)(struct re_pattern_buffer *buffer, char const *string1, int length1, char const *string2, int length2, int start, int range, struct re_registers *regs, int stop);
/* Like `re_search', but return how many characters in `string'
 * the regexp in `buffer' matched, starting at position `start' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_re_match)(struct re_pattern_buffer *buffer, char const *string, int length, int start, struct re_registers *regs);
/* Relates to `re_match' as `re_search_2' relates to `re_search' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_re_match_2)(struct re_pattern_buffer *buffer, char const *string1, int length1, char const *string2, int length2, int start, struct re_registers *regs, int stop);
/* Set `regs' to hold `num_regs' registers, storing them in `starts' and
 * `ends'. Subsequent matches using `buffer' and `regs' will use this memory
 * for recording register information. `starts' and `ends' must be allocated
 * with malloc, and must each be at least ``num_regs' * sizeof(regoff_t)' bytes long.
 * If `num_regs == 0', then subsequent matches should allocate their own register data.
 * Unless this function is called, the first search or match using
 * PATTERN_BUFFER will allocate its own register data, without freeing the old data */
INTDEF void NOTHROW_NCX(LIBDCALL libd_re_set_registers)(struct re_pattern_buffer *buffer, struct re_registers *regs, unsigned int num_regs, regoff_t *starts, regoff_t *ends);
INTDEF int NOTHROW_NCX(LIBDCALL libd_regcomp)(regex_t *__restrict preg, char const *__restrict pattern, int cflags);
INTDEF int NOTHROW_NCX(LIBDCALL libd_regexec)(regex_t const *__restrict preg, char const *__restrict string, size_t nmatch, regmatch_t pmatch[__restrict_arr], int eflags);
INTDEF size_t NOTHROW_NCX(LIBDCALL libd_regerror)(int errcode, regex_t const *__restrict preg, char *__restrict errbuf, size_t errbuf_size);
INTDEF void NOTHROW_NCX(LIBDCALL libd_regfree)(regex_t *preg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_REGEX_H */
