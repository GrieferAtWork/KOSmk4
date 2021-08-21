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
#ifndef GUARD_LIBICONV_STATEFUL_CP_STATEFUL_H
#define GUARD_LIBICONV_STATEFUL_CP_STATEFUL_H 1

#include "../api.h"
/**/

#include <hybrid/byteorder.h>

#include <kos/types.h>

#include <format-printer.h>

#include <libiconv/iconv.h>

#include "../codecs.h"

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

struct iconv_stateful_encode_range {
	uint16_t iser_uni_ord; /* Unicode ordinal */
	uint16_t iser_cp_off;  /* Code page ordinal offset or index into random-access-block table. */
};
#define iconv_stateful_encode_range_start(self) ((self)->iser_uni_ord)   /* First unicode character apart of this range */
#define iconv_stateful_encode_range_end(self)   ((self)[1].iser_uni_ord) /* First unicode character no longer apart of this range */

struct iconv_stateful_2char_encode {
	char16_t is2ce_uni2;   /* Second unicode character (or `0' for all others / fallback) */
	uint16_t is2ce_cp;     /* Resulting code page character (double-byte) */
};

struct iconv_stateful_c32_encode {
	char32_t  isc32e_uni;  /* 32-bit unicode character */
	uint16_t  isc32e_cp;   /* Resulting code page character (double-byte) */
	uint16_t _isc32e_pad;  /* ... */
};

struct iconv_stateful_codepage {
	char16_t isc_sb[256];    /* Single-byte decode table. (0-entires require special treatment;
	                          * specifically  `0E' and `0F'  which are guarantied  to map to 0) */
	/*
	 * In order to maximize compression, double-byte character decoding is a bit complicated:
	 * >> decode16(uint16_t ch) {
	 * >>     struct iconv_stateful_range *range;
	 * >>     range = FIND_RANGE_CONTAINING(self, ch);
	 * >>     if (!range)
	 * >>         return ILLEGAL_CHARACTER;
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
	 * >>         if (range->isr_uni_off == 0 && ch != 0)
	 * >>             return ILLEGAL_CHARACTER;
	 * >>         return (char32_t)(uint16_t)(ch + range->isr_uni_off);
	 * >>     }
	 * >> }
	 *
	 * >> encode(char32_t ch) {
	 * >>     if (ch < 0xffff) {
	 * >>         struct iconv_stateful_encode_range *range;
	 * >>         range = FIND_ENCODE_RANGE_CONTAINING(self, ch);
	 * >>         assert(range); // Always defined for `ch < 0xffff'; yes: 0xffff doesn't have an entry!
	 * >>         if (range->iser_cp_off >= self->isc_encode_rab_minoff &&
	 * >>             range->iser_cp_off <= self->isc_encode_rab_maxoff) {
	 * >>             // Random access character
	 * >>             uint16_t cp_offset, rab_index, result;
	 * >>             rab_index = range->iser_cp_off - self->isc_encode_rab_minoff;
	 * >>             cp_offset = self->isc_encode_rab[rab_index];
	 * >>             cp_offset += ch - range->iser_uni_ord;
	 * >>             if (cp_offset >= isc_encode_tab_count) {
	 * >>                 // 2-char unicode sequence
	 * >>                 struct iconv_stateful_2char_encode *entry;
	 * >>                 entry = &isc_encode_2ch[cp_offset - isc_encode_tab_count];
	 * >>                 ON_FLUSH({
	 * >>                     while (entry->is2ce_uni2)
	 * >>                         +++entry;
	 * >>                     OUTPUT16(entry->is2ce_cp); // Guarantied to never be 0 (for now)
	 * >>                 });
	 * >>                 ON_NEXT_UNI([](char32_t ch) {
	 * >>                     UNSET_ON_FLUSH();
	 * >>                     while (entry->is2ce_uni2 && entry->is2ce_uni2 != ch)
	 * >>                         +++entry;
	 * >>                     OUTPUT16(entry->is2ce_cp); // Guarantied to never be 0 (for now)
	 * >>                     if (entry->is2ce_uni2 == ch)
	 * >>                         return DONE;   // 2-unicode-character sequence encoded
	 * >>                     return encode(ch); // Encode the second character like normal
	 * >>                 })
	 * >>                 return;
	 * >>             }
	 * >>             result = self->isc_encode_tab[cp_offset];
	 * >>             if (result == 0)
	 * >>                 return ILLEGAL_CHARACTER;
	 * >>             return result;
	 * >>         } else {
	 * >>             // Identity character
	 * >>             if (range->iser_cp_off == 0)
	 * >>                 return ILLEGAL_CHARACTER;
	 * >>             return (uint16_t)ch + range->iser_cp_off;
	 * >>         }
	 * >>     }
	 * >>     // Only necessary if ch > 0xffff:
	 * >>     struct iconv_stateful_c32_encode *c32;
	 * >>     c32 = BSEARCH_IN_TABLE(isc_encode_c32, isc_encode_c32_count, ch);
	 * >>     if (c32 == NULL)
	 * >>         return ILLEGAL_CHARACTER;
	 * >>     return c32->isc32e_cp;
	 * >> }
	 */
	uint16_t isc_db_count;          /* # of code page ranges. */
	uint16_t isc_u16_count;         /* # of entires in the 16-bit unicode table. */
	uint16_t isc_u32_count;         /* # of entires in the 32-bit unicode table. */
	uint16_t isc_rab_minoff;        /* Random access block min offset */
	uint16_t isc_rab_maxoff;        /* Random access block max offset */
	uint16_t isc_encode_count;      /* # of encode ranges. */
	uint16_t isc_encode_tab_count;  /* # of encode uint16_t entries. */
	uint16_t isc_encode_rab_minoff; /* Encode random access block max offset */
	uint16_t isc_encode_rab_maxoff; /* Encode random access block max offset */
	uint8_t  isc_encode_repl;       /* Encode replacement character. */
	uint8_t  isc_encode_2ch_count;  /* # of 2-character encode entires. */
	uint16_t isc_encode_c32_count;  /* # of 32-bit unicode encode entries. */
	COMPILER_FLEXIBLE_ARRAY(struct iconv_stateful_range, isc_db_ranges); /* [isc_db_count] */
/*	uint16_t                    isc_db_ranges_end; // [== 0xffff] */
/*	uint16_t                    isc_rab[(isc_rab_maxoff - isc_rab_minoff) + 1]; // Random access offset table */
/*	char16_t                    isc_u16[isc_u16_count]; */
	/* NOTE: `isc_u32' is guarantied to exist at an offset divisible by 4. */
/*	uint32_t                    isc_u32[isc_u32_count]; // 32-bit unicode table (when indices are `>= isc_u16_count')
 *	                                                    // Entries are 32-bit  unicode when 0x80000000  is set;  else
 *	                                                    // entires are 2x 16-bit  unicode (0xffff0000 is first  char) */
/*	struct iconv_stateful_encode_range isc_encode_ranges[isc_encode_count]; */
/*	uint16_t                           isc_encode_ranges_end;  // [== 0xffff] */
/*	uint16_t                           isc_encode_rab[(isc_encode_rab_maxoff - isc_encode_rab_minoff) + 1]; // Random access offset table */
/*	uint16_t                           isc_encode_tab[isc_encode_tab_count]; // Encode 2-byte values. */
/*	struct iconv_stateful_2char_encode isc_encode_2ch[isc_encode_2ch_count]; // Encode 2 unicode character into 1 codepage entry */
/*	struct iconv_stateful_c32_encode   isc_encode_c32[isc_encode_c32_count]; // Encode a 32-bit unicode character */
};

/* Helpers for accessing the hidden fields of the above structure.
 * NOTE: It is recommended to cache these values as they are needed! */
#define iconv_stateful_codepage__isc_u16__from__isc_rab(self, isc_rab)                               ((char16_t const *)((isc_rab) + ((self)->isc_rab_maxoff - (self)->isc_rab_minoff) + 1))
#define iconv_stateful_codepage__isc_u32__from__isc_u16(self, isc_u16)                               ((uint32_t const *)((isc_u16) + (self)->isc_u16_count))
#define iconv_stateful_codepage__isc_encode_ranges__from__isc_u32(self, isc_u32)                     ((struct iconv_stateful_encode_range const *)((isc_u32) + (self)->isc_u32_count))
#define iconv_stateful_codepage__isc_encode_rab__from__isc_encode_ranges(self, isc_encode_ranges)    ((uint16_t const *)((isc_encode_ranges) + (self)->isc_encode_count) + 1)
#define iconv_stateful_codepage__isc_encode_tab__from__isc_encode_rab(self, isc_encode_rab)          ((isc_encode_rab) + ((self)->isc_encode_rab_maxoff - (self)->isc_encode_rab_minoff) + 1)
#define iconv_stateful_codepage__isc_encode_tab__from__isc_encode_ranges(self, isc_encode_ranges)    iconv_stateful_codepage__isc_encode_tab__from__isc_encode_rab(self, iconv_stateful_codepage__isc_encode_rab__from__isc_encode_ranges(self, isc_encode_ranges))
#define iconv_stateful_codepage__isc_encode_2ch__from__isc_encode_tab(self, isc_encode_tab)          ((struct iconv_stateful_2char_encode const *)((isc_encode_tab) + (self)->isc_encode_tab_count))
#define iconv_stateful_codepage__isc_encode_2ch__from__isc_encode_rab(self, isc_encode_rab)          iconv_stateful_codepage__isc_encode_2ch__from__isc_encode_tab(self, iconv_stateful_codepage__isc_encode_tab__from__isc_encode_rab(self, isc_encode_rab))
#define iconv_stateful_codepage__isc_encode_2ch__from__isc_encode_ranges(self, isc_encode_ranges)    iconv_stateful_codepage__isc_encode_2ch__from__isc_encode_tab(self, iconv_stateful_codepage__isc_encode_tab__from__isc_encode_ranges(self, isc_encode_ranges))
#define iconv_stateful_codepage__isc_encode_c32__from__isc_encode_2ch(self, isc_encode_2ch)          ((struct iconv_stateful_c32_encode const *)((isc_encode_2ch) + (self)->isc_encode_2ch_count))
#define iconv_stateful_codepage__isc_encode_c32__from__isc_encode_tab(self, isc_encode_tab)          iconv_stateful_codepage__isc_encode_c32__from__isc_encode_2ch(self, iconv_stateful_codepage__isc_encode_2ch__from__isc_encode_tab(self, isc_encode_tab))
#define iconv_stateful_codepage__isc_encode_c32__from__isc_encode_rab(self, isc_encode_rab)          iconv_stateful_codepage__isc_encode_c32__from__isc_encode_2ch(self, iconv_stateful_codepage__isc_encode_2ch__from__isc_encode_rab(self, isc_encode_rab))
#define iconv_stateful_codepage__isc_encode_c32__from__isc_encode_ranges(self, isc_encode_ranges)    iconv_stateful_codepage__isc_encode_c32__from__isc_encode_2ch(self, iconv_stateful_codepage__isc_encode_2ch__from__isc_encode_ranges(self, isc_encode_ranges))

#define iconv_stateful_codepage__isc_rab(self)           ((uint16_t const *)((self)->isc_db_ranges + (self)->isc_db_count) + 1)
#define iconv_stateful_codepage__isc_u16(self)           iconv_stateful_codepage__isc_u16__from__isc_rab(self, iconv_stateful_codepage__isc_rab(self))
#define iconv_stateful_codepage__isc_u32(self)           iconv_stateful_codepage__isc_u32__from__isc_u16(self, iconv_stateful_codepage__isc_u16(self))
#define iconv_stateful_codepage__isc_encode_ranges(self) iconv_stateful_codepage__isc_encode_ranges__from__isc_u32(self, iconv_stateful_codepage__isc_u32(self))
#define iconv_stateful_codepage__isc_encode_rab(self)    iconv_stateful_codepage__isc_encode_rab__from__isc_encode_ranges(self, iconv_stateful_codepage__isc_encode_ranges(self))
#define iconv_stateful_codepage__isc_encode_tab(self)    iconv_stateful_codepage__isc_encode_tab__from__isc_encode_rab(self, iconv_stateful_codepage__isc_encode_rab(self))
#define iconv_stateful_codepage__isc_encode_2ch(self)    iconv_stateful_codepage__isc_encode_2ch__from__isc_encode_tab(self, iconv_stateful_codepage__isc_encode_tab(self))
#define iconv_stateful_codepage__isc_encode_c32(self)    iconv_stateful_codepage__isc_encode_c32__from__isc_encode_2ch(self, iconv_stateful_codepage__isc_encode_2ch(self))




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
INTDEF NONNULL((1, 2)) ssize_t FORMATPRINTER_CC libiconv_stateful_decode(struct iconv_decode *__restrict self, /*cp???*/ char const *__restrict data, size_t size);
INTDEF NONNULL((1, 2)) ssize_t FORMATPRINTER_CC libiconv_stateful_encode(struct iconv_encode *__restrict self, /*utf-8*/ char const *__restrict data, size_t size);


/* Initialize a stateful encoder/decoder. */
INTDEF NONNULL((1, 2)) void CC libiconv_stateful_decode_init(struct iconv_decode *__restrict self, /*out*/ struct iconv_printer *__restrict input);
INTDEF NONNULL((1, 2)) void CC libiconv_stateful_encode_init(struct iconv_encode *__restrict self, /*out*/ struct iconv_printer *__restrict input);


DECL_END
#endif /* CODEC_STATEFUL_COUNT != 0 */

#endif /* !GUARD_LIBICONV_STATEFUL_CP_STATEFUL_H */
