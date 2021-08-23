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
#ifndef GUARD_LIBICONV_TRANSLITERATE_H
#define GUARD_LIBICONV_TRANSLITERATE_H 1

#include "api.h"
/**/

#include <kos/types.h>

#include <libiconv/transliterate.h>

DECL_BEGIN

/* Generate the `nth' transliteration for `uni_ch' and store the results
 * in `result', returning  the #  of stored characters.  When no  (more)
 * transliterations exist for `uni_ch' (where available ones are indexed
 * via `nth', starting at `0'), return `(size_t)-1'
 * Note that in the case of multi-character transliterations, all possible
 * transliterations for replacement  characters are  already attempted  by
 * this  function itself,  meaning that in  these cases all  those are all
 * tried as well.
 * Note that this function may or may not re-return  `uni_ch && return==1'.
 * When this is the case, simply ignore the call any try again with `nth+1'
 *
 * @param: result: Result buffer for transliterated text.
 * @param: uni_ch: The character that should be transliterated.
 * @param: nth:    Specifies  that the nth transliteration of `uni_ch' be
 *                 generated, starting at `0' and ending as soon as  this
 *                 function returns `(size_t)-1' to indicate that no more
 *                 possible transliterations are available.
 * @return: (size_t)-1: No (more) transliterations available.
 * @return: * : The # of characters written to `result' (may be 0). */
INTDEF WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC libiconv_transliterate)(char32_t result[ICONV_TRANSLITERATE_MAXLEN],
                                       char32_t uni_ch, size_t nth);

DECL_END

#endif /* !GUARD_LIBICONV_TRANSLITERATE_H */
