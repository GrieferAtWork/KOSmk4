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
#ifndef GUARD_LIBICONV_CP_ISO646_H
#define GUARD_LIBICONV_CP_ISO646_H 1

#include "api.h"
/**/

#include <hybrid/byteorder.h>

#include <kos/types.h>

#include <format-printer.h>
#include <libiconv/iconv.h>

DECL_BEGIN

/* General-purpose ISO646 code pages only override a limited number
 * of characters. To safe space, we use a special encoding that only
 * provides overrides for these specific characters, while all others
 * will simply be encoded as ASCII.
 * s.a.: https://en.wikipedia.org/wiki/ISO/IEC_646
 */
struct iconv_iso646_codepage {
#define ISO646_OVERRIDE_COUNT 18
	/* Overrides.
	 * ASCII-Defaults: { '!', '"', '#', '$', '&', ':', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~' } */
	char16_t iic_override[ISO646_OVERRIDE_COUNT];
#define iconv_iso646_codepage_qmark(self) ((self)->iic_override[6]) /* The override for `?' is at slot 6 */
};

INTDEF struct iconv_iso646_codepage const libiconv_iso646_pages[];
#define libiconv_iso646_page(codec) (&libiconv_iso646_pages[(codec) - CODEC_ISO646_MIN])


/* Index into `iic_override' for which override to use for which character.
 * When no override should be used, returned index is out-of-bounds. */
INTDEF uint8_t const libiconv_iso646_override[128];

/* Evaluate to the ordinal indices at which each of the overrides applies.
 * Coincidentally, these indices are also equal to the default overrides,
 * though since every iso646 codepage specifies all overrides, that fact
 * doesn't actually matter. */
INTDEF uint8_t const libiconv_iso646_override_chars[ISO646_OVERRIDE_COUNT];

/* Returns `0' when the character cannot be encoded. */
FORCELOCAL ATTR_PURE WUNUSED NONNULL((1)) char
NOTHROW_NCX(iso646_encode)(struct iconv_iso646_codepage const *__restrict cp, char32_t c32) {
	unsigned int i;
	if ((uint32_t)c32 <= 0x7f) {
		uint8_t index = libiconv_iso646_override[(uint32_t)c32];
		if (index >= ISO646_OVERRIDE_COUNT)
			return (char)(unsigned char)(uint8_t)(uint32_t)c32;
	}

	/* Check if one of the overrides encodes the given `c32' */
	for (i = 0; i < ISO646_OVERRIDE_COUNT; ++i) {
		if (cp->iic_override[i] == c32)
			return (char)(unsigned char)libiconv_iso646_override_chars[i];
	}

	/* Cannot encode :( */
	return 0;
}

/* WARNING: The caller must ensure that `c <= 0x7f'
 * Returns `0' if the character isn't assigned, or when `c == 0'. */
FORCELOCAL ATTR_PURE WUNUSED NONNULL((1)) char16_t
NOTHROW_NCX(iso646_decode)(struct iconv_iso646_codepage const *__restrict cp, char c) {
	uint8_t index;
	index = libiconv_iso646_override[(unsigned char)c];
	if (index >= ISO646_OVERRIDE_COUNT)
		return (char16_t)(uint16_t)(unsigned char)c;
	return cp->iic_override[index];
}


DECL_END

#endif /* !GUARD_LIBICONV_CP_ISO646_H */
