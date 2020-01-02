/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBREGEX_REGEX_H
#define GUARD_LIBREGEX_REGEX_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libregex/regex.h>

DECL_BEGIN

/* Given a regular expression `pattern', check if it
 * matches the string found in `data', returning the
 * number of bytes in `data' that are being matched,
 * or `0' if the pattern doesn't match.
 * @param: datalen:           Number of bytes (not characters) in data.
 * @param: patternlen:        Number of bytes (not characters) in pattern.
 * @return: * :               Number of characters (not bytes) matched in `data'.
 * @return: 0 :               Pattern not found.
 * @return: REGEX_ISERROR(*): Error. */
INTDEF NONNULL((1, 3)) size_t CC
libregex_matches(/*utf-8*/ char const *__restrict data, size_t datalen,
                 /*utf-8*/ char const *__restrict pattern, size_t patternlen,
                 uintptr_t flags);

/* Same as `regex_matches()', but also store a pointer to the end of
 * consumed data in `pdataend'. Because input data is formatted in UTF-8,
 * this position would only be equal to `data + return' if all input data
 * was ASCII only, meaning that in the universal case, this function
 * becomes useful when dealing with unicode data.
 * @param: pdataend:          Upon success (return != 0 && return != (size_t)-1),
 *                            save a pointer to the end of consumed data here.
 * @param: datalen:           Number of bytes (not characters) in data.
 * @param: patternlen:        Number of bytes (not characters) in pattern.
 * @return: * :               Number of characters (not bytes) matched in `data'.
 * @return: 0 :               Pattern not found.
 * @return: REGEX_ISERROR(*): Error. */
INTDEF NONNULL((1, 3, 5)) size_t CC
libregex_matchesptr(/*utf-8*/ char const *__restrict data, size_t datalen,
                    /*utf-8*/ char const *__restrict pattern, size_t patternlen,
                    /*utf-8*/ char const **__restrict pdataend,
                    uintptr_t flags);


/* Find the first instance matching `pattern' and store the
 * character indices (not byte offsets) in `*pstart' and `*pend'
 * @return: 1:                Pattern was found.
 * @return: 0:                Pattern not found.
 * @return: REGEX_ISERROR(*): Error. */
INTDEF NONNULL((1, 3, 5)) int CC
libregex_find(/*utf-8*/ char const *__restrict data, size_t datalen,
              /*utf-8*/ char const *__restrict pattern, size_t patternlen,
              struct regex_range *__restrict presult, uintptr_t flags);
INTDEF NONNULL((1, 3, 5)) int CC
libregex_rfind(/*utf-8*/ char const *__restrict data, size_t datalen,
               /*utf-8*/ char const *__restrict pattern, size_t patternlen,
               struct regex_range *__restrict presult, uintptr_t flags);

/* Same as the functions above, but return character pointers, rather than indices. */
INTDEF NONNULL((1, 3, 5)) int CC
libregex_findptr(/*utf-8*/ char const *__restrict data, size_t datalen,
                 /*utf-8*/ char const *__restrict pattern, size_t patternlen,
                 struct regex_range_ptr *__restrict presult, uintptr_t flags);
INTDEF NONNULL((1, 3, 5)) int CC
libregex_rfindptr(/*utf-8*/ char const *__restrict data, size_t datalen,
                  /*utf-8*/ char const *__restrict pattern, size_t patternlen,
                  struct regex_range_ptr *__restrict presult, uintptr_t flags);

/* Same as the functions above, but return both character indices _and_ pointers. */
INTDEF NONNULL((1, 3, 5)) int CC
libregex_findex(/*utf-8*/ char const *__restrict data, size_t datalen,
                /*utf-8*/ char const *__restrict pattern, size_t patternlen,
                struct regex_range_ex *__restrict presult, uintptr_t flags);
INTDEF NONNULL((1, 3, 5)) int CC
libregex_rfindex(/*utf-8*/ char const *__restrict data, size_t datalen,
                 /*utf-8*/ char const *__restrict pattern, size_t patternlen,
                 struct regex_range_ex *__restrict presult, uintptr_t flags);


DECL_END

#endif /* !GUARD_LIBREGEX_REGEX_H */
