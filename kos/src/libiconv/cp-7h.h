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
#ifndef GUARD_LIBICONV_CP_7H_H
#define GUARD_LIBICONV_CP_7H_H 1

#include "api.h"
/**/

#include <hybrid/byteorder.h>

#include <kos/types.h>

#include <format-printer.h>

#include <libiconv/iconv.h>

#include "codecs.h"
#include "cp.h"

#if CODEC_CP7H_COUNT != 0
DECL_BEGIN

/* General-purpose codepage for  codecs that are  ASCII-compatible.
 * The name 7h  means that 7-bit  codepoints are  ASCII-compatible,
 * while h means that only the high half of characters are defined. */

struct iconv_7h_codepage {
	/* Lookup table specifying how to decode a character. */
	char16_t i7hcp_decode[128];

	/* Sorted by `icee_uni': table for how to encode UNI into the cp. */
	COMPILER_FLEXIBLE_ARRAY(struct iconv_codepage_encode_entry, i7hcp_encode);
#define i7hcp_encode_count i7hcp_encode[0]._icee_pad /* # of encode entries. */
};

struct iconv_cp7h_database;
typedef uint32_t libiconv_cp7h_offset_t;

INTDEF struct iconv_cp7h_database const libiconv_cp7h_db;
INTDEF libiconv_cp7h_offset_t const libiconv_cp7h_offsets[];


/* Return the 7-bit code page associated with `codec'.
 * The caller must ensure that `codec >= CODEC_CP7H_MIN && codec <= CODEC_CP7H_MAX' */
#define libiconv_cp7h_page(codec)                                          \
	(struct iconv_7h_codepage const *)((byte_t const *)&libiconv_cp7h_db + \
	                                   libiconv_cp7h_offsets[(codec)-CODEC_CP7H_MIN])


DECL_END
#endif /* CODEC_CP7H_COUNT != 0 */

#endif /* !GUARD_LIBICONV_CP_7H_H */
