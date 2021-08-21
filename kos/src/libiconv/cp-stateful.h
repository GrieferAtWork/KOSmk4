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
#ifndef GUARD_LIBICONV_CP_STATEFUL_H
#define GUARD_LIBICONV_CP_STATEFUL_H 1

#include "api.h"
/**/

#include <hybrid/byteorder.h>

#include <kos/types.h>

#include <format-printer.h>

#include <libiconv/iconv.h>

#include "codecs.h"

#if CODEC_STATEFUL_COUNT != 0
DECL_BEGIN

/* Requires for use of `iconv_stateful_codepage':
 *   - The double-byte sequence 0xFF,0xFF must not be a valid code-point
 *   - All codepage code points must decode to max 2 unicode character
 *   - All unicode code points must fit into 16 bits, unless only a single
 *     unicode character is being encoded, in which case that character is
 *     allowed to take up 32 bits. */



/* NOTE: Codepage ordinals are always encoded in big endian (iow: b[0] << 8 | b[1])  */


struct iconv_stateful_range {
	uint16_t isr_cp_ord;  /* Codepage ordinal */
	uint16_t isr_uni_off; /* Unicode ordinal offset or index into random-access-block table. */
};
#define iconv_stateful_range_start(self) ((self)->isr_cp_ord)   /* First code-page character apart of this range */
#define iconv_stateful_range_end(self)   ((self)[1].isr_cp_ord) /* First code-page character no longer apart of this range */

struct iconv_stateful_codepage {
	char16_t isc_sb[256];    /* Single-byte decode table. (0-entires require special treatment;
	                          * specifically  `0E' and `0F'  which are guarantied  to map to 0) */
	/*
	 * In order to maximize compression, double-byte character decoding is a bit complicated:
	 * >> decode16(uint16_t ch) {
	 * >>     struct iconv_stateful_range *range;
	 * >>     range = FIND_RANGE_CONTAINING(self, ch); // Guarantied to exist; use bsearch for O(log2(n))
	 * >>     if (range->isr_uni_off >= self->isc_rab_minoff &&
	 * >>         range->isr_uni_off <= self->isc_rab_maxoff) {
	 * >>         // Random access character
	 * >>         uint16_t uni_offset, rab_index;
	 * >>         rab_index  = range->isr_uni_off - self->isc_rab_minoff;
	 * >>         uni_offset = self->isc_rab[rab_index];
	 * >>         uni_offset += ch - range->isr_cp_ord;
	 * >>         if (uni_offset >= self->isc_u16_count) {
	 * >>             // 32-bit entry
	 * >>             uint32_t ent = self->isc_u32[uni_offset - self->isc_u16_count];
	 * >>             if (ent & 0x80000000) // 1-character sequence
	 * >>                 return ent & 0x7fffffff;
	 * >>             return { // 2-character sequence
	 * >>                 (char16_t)((ent & 0xffff0000) >> 16),
	 * >>                 (char16_t)(ent & 0xffff)
	 * >>             };
	 * >>         } else {
	 * >>             // 16-bit entry
	 * >>             char16_t result = self->isc_u16[uni_offset];
	 * >>             if (result == 0)
	 * >>                 return ILLEGAL_CHARACTER;
	 * >>             return result;
	 * >>         }
	 * >>     } else {
	 * >>         // Identity character
	 * >>         if (!range->isr_uni_off)
	 * >>             return ILLEGAL_CHARACTER;
	 * >>         return (char32_t)(uint16_t)(ch + range->isr_uni_off);
	 * >>     }
	 * >> }
	 */
	uint16_t isc_db_count;   /* # of code page ranges. */
	uint16_t isc_u16_count;  /* # of entires in the 16-bit unicode table. */
	uint16_t isc_rab_minoff; /* Random access block min offset */
	uint16_t isc_rab_maxoff; /* Random access block max offset */
	COMPILER_FLEXIBLE_ARRAY(struct iconv_stateful_range, isc_db_ranges); /* [isc_db_count] */
/*	uint16_t                    isc_db_ranges_end; // [== 0xffff] */
/*	uint16_t                    isc_rab[(isc_rab_maxoff - isc_rab_minoff) + 1]; // Random access offset table */
/*	char16_t                    isc_u16[isc_u16_count]; */
/*	uint32_t                    isc_u32[]; // 32-bit unicode table (when indices are `>= isc_u16_count')
 *	                                       // Entries are 32-bit  unicode when 0x80000000  is set;  else
 *	                                       // entires are 2x 16-bit  unicode (0xffff0000 is first  char) */
	/* TODO: Cache data for encoding from unicode! (all of the above is only used for decoding) */
};
/* Helpers for accessing the hidden fields of the above structure. */
#define iconv_stateful_codepage__isc_rab(self) \
	((uint16_t const *)((self)->isc_db_ranges + (self)->isc_db_count) + 1)
#define iconv_stateful_codepage__isc_u16(self)                   \
	((char16_t const *)(iconv_stateful_codepage__isc_rab(self) + \
	                    ((self)->isc_rab_maxoff - (self)->isc_rab_minoff) + 1))
#define iconv_stateful_codepage__isc_u32(self) \
	((uint32_t const *)(iconv_stateful_codepage__isc_u16(self) + (self)->isc_u16_count)





typedef uint32_t libiconv_stateful_offset_t;
struct iconv_stateful_database;
INTDEF struct iconv_stateful_database const libiconv_stateful_db;
INTDEF libiconv_stateful_offset_t const libiconv_stateful_offsets[];

/* Return the 7-bit code page associated with `codec'.
 * The caller must ensure that `codec >= CODEC_CP7L_MIN && codec <= CODEC_CP7L_MAX' */
#define libiconv_stateful_page(codec)                                                \
	(struct iconv_stateful_codepage const *)((byte_t const *)&libiconv_stateful_db + \
	                                         libiconv_stateful_offsets[(codec)-CODEC_STATEFUL_MIN])


/************************************************************************/
/* Stateful code page encode/decode functions.                          */
/************************************************************************/
INTDEF NONNULL((1, 2)) ssize_t FORMATPRINTER_CC libiconv_stateful_encode(struct iconv_encode *__restrict self, /*utf-8*/ char const *__restrict data, size_t size);
INTDEF NONNULL((1, 2)) ssize_t FORMATPRINTER_CC libiconv_stateful_decode(struct iconv_decode *__restrict self, /*cp???*/ char const *__restrict data, size_t size);


DECL_END
#endif /* CODEC_STATEFUL_COUNT != 0 */

#endif /* !GUARD_LIBICONV_CP_STATEFUL_H */
