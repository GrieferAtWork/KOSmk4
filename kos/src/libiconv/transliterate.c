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
#ifndef GUARD_LIBICONV_TRANSLITERATE_C
#define GUARD_LIBICONV_TRANSLITERATE_C 1

#include "api.h"
/**/

#include <kos/types.h>

#include <assert.h>
#include <unicode.h>

#include <libiconv/transliterate.h>

#include "transliterate.h"

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
INTERN WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC libiconv_transliterate)(char32_t result[ICONV_TRANSLITERATE_MAXLEN],
                                       char32_t uni_ch, size_t nth) {
	/* TODO: There are some transliterations that can only be applied to multiple
	 *       input  characters at a time! As such,  this API must be extended and
	 *       there has to be a  limit for how many  such characters must be  kept
	 *       track of. */
	struct __unitraits const *traits;
	traits = __unicode_descriptor(uni_ch);

	/* Try lower/upper/title case deltas. */
	if (traits->__ut_lower != 0) {
		if (nth == 0) {
			result[0] = (char32_t)(uni_ch + traits->__ut_lower);
			return 1;
		}
		--nth;
	}
	if (traits->__ut_upper != 0 &&
	    traits->__ut_upper != traits->__ut_lower) {
		if (nth == 0) {
			result[0] = (char32_t)(uni_ch + traits->__ut_upper);
			return 1;
		}
		--nth;
	}
	if (traits->__ut_title != 0 &&
	    traits->__ut_title != traits->__ut_upper &&
	    traits->__ut_title != traits->__ut_lower) {
		if (nth == 0) {
			result[0] = (char32_t)(uni_ch + traits->__ut_title);
			return 1;
		}
		--nth;
	}

	/* Try to casefold the character and then try all
	 * combinations  of casings on the folded string. */
	if (traits->__ut_fold != 0xff) {
		size_t i, len, total_variations;
		byte_t variations[UNICODE_FOLDED_MAX]; /* # of variations per character */
		STATIC_ASSERT(ICONV_TRANSLITERATE_MAXLEN >= UNICODE_FOLDED_MAX);
		len = (size_t)(unicode_fold(uni_ch, result) - result);
		assert(len != 0);
		if unlikely(len == 1 && result[0] == uni_ch) {
			goto after_fold; /* Shouldn't happen (because __ut_fold != 0xff, len
			                  * should always be  >= 2), but  better be  safe... */
		}
		total_variations = 1;
		for (i = 0; i < len; ++i) {
			byte_t count = 1;
			traits = __unicode_descriptor(result[i]);
			if (traits->__ut_lower != 0)
				++count;
			if (traits->__ut_upper != 0 &&
			    traits->__ut_upper != traits->__ut_lower)
				++count;
			if (traits->__ut_title != 0 &&
			    traits->__ut_title != traits->__ut_upper &&
			    traits->__ut_title != traits->__ut_lower)
				++count;
			variations[i] = count;
			total_variations *= count;
		}
		if (nth >= total_variations) {
			nth -= total_variations;
		} else {
			/* Generate the requested variation. */
			for (i = 0; i < len; ++i) {
				byte_t variation;
				byte_t count = variations[i];
				/* Figure out the variation for this character.
				 * This  is a  variable-meaning command ID  of stuff to  do with this
				 * character, of which there are a total of `count' different things.
				 * We know that there's always  at least 1 thing  to do (which is  to
				 * do nothing), so this can't divide by zero. */
				variation = nth % count;
				nth /= count;
				if (variation == 0)
					continue; /* Leave unchanged. */
				--variation;
				traits = __unicode_descriptor(result[i]);
				if (traits->__ut_lower != 0) {
					if (variation == 0) {
						result[i] += traits->__ut_lower; /* tolower */
						continue;
					}
					--variation;
				}
				if (traits->__ut_upper != 0) {
					if (variation == 0) {
						result[i] += traits->__ut_upper; /* toupper */
						continue;
					}
					--variation;
				}
				assert(variation == 0);
				assert(traits->__ut_title != 0);
				assert(traits->__ut_title != traits->__ut_upper);
				assert(traits->__ut_title != traits->__ut_lower);
				result[i] += traits->__ut_title; /* totitle */
			}
			return len;
		}
	}
after_fold:

	/* TODO: Support for *actual* transliteration, as described by unicode:
	 * http://cldr.unicode.org/index/cldr-spec/transliteration-guidelines
	 */


	/* All possibilities exhausted. */
	return (size_t)-1;
}

DEFINE_PUBLIC_ALIAS(iconv_transliterate, libiconv_transliterate);

DECL_END

#endif /* !GUARD_LIBICONV_TRANSLITERATE_C */
