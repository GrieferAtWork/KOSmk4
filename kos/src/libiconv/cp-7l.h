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
#ifndef GUARD_LIBICONV_CP_7L_H
#define GUARD_LIBICONV_CP_7L_H 1

#include "api.h"
/**/

#include <hybrid/byteorder.h>

#include <kos/types.h>

#include <format-printer.h>
#include <libiconv/iconv.h>

#include "cp.h"

DECL_BEGIN

/* General-purpose codepage for codecs that only map up to 7 bits per character. */

struct iconv_7l_codepage {
	/* Lookup table specifying how to decode a character. */
	char16_t i7lcp_decode[128];

	/* Sorted by `icee_uni': table for how to encode UNI into the cp. */
	COMPILER_FLEXIBLE_ARRAY(struct iconv_codepage_encode_entry, i7lcp_encode);
#define i7lcp_encode_count i7lcp_encode[0]._icee_pad /* # of encode entries. */
#define i7lcp_replacement  i7lcp_encode[1]._icee_pad /* Replacement character. */
};

struct iconv_cp7l_database;
typedef uint16_t libiconv_cp7l_offset_t;

INTDEF struct iconv_cp7l_database const libiconv_cp7l_db;
INTDEF libiconv_cp7l_offset_t const libiconv_cp7l_offsets[];


/* Return the 7-bit code page associated with `codec'.
 * The caller must ensure that `codec >= CODEC_CP7L_MIN && codec <= CODEC_CP7L_MAX' */
#define libiconv_cp7l_page(codec)                                          \
	(struct iconv_7l_codepage const *)((byte_t const *)&libiconv_cp7l_db + \
	                                   libiconv_cp7l_offsets[(codec)-CODEC_CP7L_MIN])


DECL_END

#endif /* !GUARD_LIBICONV_CP_7L_H */
