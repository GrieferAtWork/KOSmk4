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
#ifndef GUARD_LIBICONV_CP_H
#define GUARD_LIBICONV_CP_H 1

#include "api.h"
/**/

#include <kos/types.h>

#include "codecs.h"

#if CODEC_CP_COUNT != 0
DECL_BEGIN

struct iconv_codepage_encode_entry {
	char16_t icee_uni;  /* Unicode character */
	uint8_t  icee_cp;   /* Codepage equivalent character */
	uint8_t _icee_pad;  /* Pad */
};

struct iconv_codepage {
	/* Lookup table specifying how to decode a character. */
	char16_t icp_decode[256];

	/* Sorted by `icee_uni': table for how to encode UNI into the cp. */
	COMPILER_FLEXIBLE_ARRAY(struct iconv_codepage_encode_entry, icp_encode);

#define icp_encode_max  icp_encode[0]._icee_pad /* # of encode entries minus 1. */
#define icp_replacement icp_encode[1]._icee_pad /* Replacement character (for `ICONV_ERR_REPLACE') */
};

struct iconv_cp_database;
typedef uint32_t libiconv_cp_offset_t;

INTDEF struct iconv_cp_database const libiconv_cp_db;
INTDEF libiconv_cp_offset_t const libiconv_cp_offsets[];


/* Return the 8-bit code page associated with `codec'.
 * The caller must ensure that `codec >= CODEC_CP_MIN && codec <= CODEC_CP_MAX' */
#define libiconv_cp_page(codec)                                       \
	(struct iconv_codepage const *)((byte_t const *)&libiconv_cp_db + \
	                                libiconv_cp_offsets[(codec)-CODEC_CP_MIN])


DECL_END
#endif /* CODEC_CP_COUNT != 0 */

#endif /* !GUARD_LIBICONV_CP_H */
