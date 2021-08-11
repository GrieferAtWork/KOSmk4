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

DECL_BEGIN

struct iconv_codepage_encode_entry {
	char16_t icee_uni;  /* Unicode character */
	uint8_t  icee_cp;   /* Codepage equivalent character */
	uint8_t _icee_pad;  /* Pad */
};

struct iconv_codepage {
	char16_t                                                    icp_decode[256]; /* Lookup table specifying how to decode a character. */
	COMPILER_FLEXIBLE_ARRAY(struct iconv_codepage_encode_entry, icp_encode); /* Sorted (by `icee_uni') table for how to encode UNI into the cp. */
#define icp_replacement icp_encode[0]._icee_pad /* Replacement character (for `ICONV_ERR_REPLACE') */
#define icp_encode_max  icp_encode[1]._icee_pad /* # of encode entries minus 1. */
};


/* If so, return the codepage associated with `codec' */
INTDEF ATTR_CONST WUNUSED struct iconv_codepage const *
NOTHROW(CC libiconv_get_codepage)(unsigned int codec);



DECL_END

#endif /* !GUARD_LIBICONV_CP_H */
