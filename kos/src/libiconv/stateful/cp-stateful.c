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
#ifndef GUARD_LIBICONV_STATEFUL_CP_STATEFUL_C
#define GUARD_LIBICONV_STATEFUL_CP_STATEFUL_C 1

#include "../api.h"
/**/

#include <hybrid/byteorder.h>
#include <hybrid/minmax.h>

#include <kos/types.h>

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <unicode.h>

#include <libiconv/iconv.h>

#include "../codecs.h"
#include "cp-stateful.h"

#if CODEC_STATEFUL_COUNT != 0
DECL_BEGIN

/*
 * Codec: IBM930
 * Codec: IBM933
 * Codec: IBM935
 * Codec: IBM937
 * Codec: IBM939
 * Codec: IBM1364
 * Codec: IBM1371
 * Codec: IBM1388
 * Codec: IBM1390  [*]
 * Codec: IBM1399  [*]
 *
 * [*] The DOUBLE_BYTE_LOOKUP_TABLE contains entires that decode to 2 unicode characters
 *
 * NOTE: Each codec has a different <SINGLE_BYTE_LOOKUP_TABLE> / <DOUBLE_BYTE_LOOKUP_TABLE>
 *
 * VAR STATE: enum { SINGLE_BYTE, DOUBLE_BYTE_1, DOUBLE_BYTE_2 } = SINGLE_BYTE
 * VAR SAVED_BYTE: unsigned char                                 = <undefined>
 *
 * decode(unsigned char ch) {
 *    if (ch == 0x0E)             // 0x0E = ascii.SO
 *        STATE = DOUBLE_BYTE_1;
 *    else if (ch == 0x0F)        // 0x0F = ascii.SI
 *        STATE = SINGLE_BYTE;
 *    else {
 *        if (STATE == SINGLE_BYTE) {
 *            return <SINGLE_BYTE_LOOKUP_TABLE>[ch];
 *        }
 *        if (STATE == DOUBLE_BYTE_1) {
 *            STATE = DOUBLE_BYTE_2;
 *            SAVED_BYTE = ch;
 *            return;
 *        }
 *        assert(STATE == DOUBLE_BYTE_2);
 *        uint16_t ch16 = (SAVED_BYTE << 8) | ch;
 *        return  <DOUBLE_BYTE_LOOKUP_TABLE>[ch];
 *    }
 * }
 *
 */

/*[[[deemon
import File from deemon;
import fs;
// Put in a separate file so this one doesn't bloat too much
local dataFilename = "cp-stateful-data.c.inl";
local savedStdout = File.stdout;
File.stdout = File.open(dataFilename, "w");
File.stdout.write(File.open("cp-stateful.c").read().decode("utf-8").partition("#ifndef")[0].unifylines());
(printCpStatefulDatabase from ..iconvdata.iconvdata)();
File.stdout.close();
File.stdout = savedStdout;
print "#include", repr dataFilename;
]]]*/
#include "cp-stateful-data.c.inl"
/*[[[end]]]*/


#define IS_ICONV_ERR_ERRNO(flags)                     (((flags) & ICONV_ERRMASK) == ICONV_ERR_ERRNO)
#define IS_ICONV_ERR_ERROR_OR_ERRNO(flags)            (((flags) & ICONV_ERRMASK) <= ICONV_ERR_ERROR)
#define IS_ICONV_ERR_ERROR_OR_ERRNO_OR_DISCARD(flags) (((flags) & ICONV_ERRMASK) <= ICONV_ERR_DISCARD)
#define IS_ICONV_ERR_DISCARD(flags)                   (((flags) & ICONV_ERRMASK) == ICONV_ERR_DISCARD)
#define IS_ICONV_ERR_REPLACE(flags)                   (((flags) & ICONV_ERRMASK) == ICONV_ERR_REPLACE)
#define IS_ICONV_ERR_IGNORE(flags)                    (((flags) & ICONV_ERRMASK) == ICONV_ERR_IGNORE)

#define decode_output_printer self->icd_output.ii_printer
#define decode_output_arg     self->icd_output.ii_arg
#define decode_output(p, s)   (*decode_output_printer)(decode_output_arg, p, s)
#define encode_output_printer self->ice_output.ii_printer
#define encode_output_arg     self->ice_output.ii_arg
#define encode_output(p, s)   (*encode_output_printer)(encode_output_arg, p, s)
#define DO(expr)                         \
	do {                                 \
		if unlikely((temp = (expr)) < 0) \
			goto err;                    \
		result += temp;                  \
	}	__WHILE0
#define DO_encode_output(p, s) DO(encode_output(p, s))
#define DO_decode_output(p, s) DO(decode_output(p, s))

/* Helper macro for encode functions that enumerates input
 * UTF-8  data  by  the embedded  UTF-32  character codes:
 * >> char32_t c32;
 * >> FOREACH_UTF8(c32, self, data, size) {
 * >>     output(ENCODE(c32));
 * >> }
 */
#define FOREACH_UTF8(c32, self, data, size)                                            \
	for (size_t _uni_status;;)                                                         \
		if ((_uni_status = unicode_c8toc32(&(c32), data, size,                         \
		                                   &(self)->ice_data.ied_utf8),                \
		     0))                                                                       \
			;                                                                          \
		else if unlikely((ssize_t)_uni_status < 0 &&                                   \
		                 (_uni_status == (size_t)-1                                    \
		                  ? (IS_ICONV_ERR_ERROR_OR_ERRNO_OR_DISCARD((self)->ice_flags) \
		                     ? 1                                                       \
		                     : ((c32) = '?', _uni_status = 1, 0))                      \
		                  : _uni_status == (size_t)-2)) {                              \
			/* Error or all data parsed. */                                            \
			if unlikely(_uni_status == (size_t)-1) {                                   \
				if (IS_ICONV_ERR_DISCARD((self)->ice_flags)) {                         \
					(data) += 1;                                                       \
					(size) -= 1;                                                       \
					continue;                                                          \
				}                                                                      \
				goto err_ilseq; /* Error! */                                           \
			}                                                                          \
			break; /* Done! */                                                         \
		} else if (((data) += _uni_status,                                             \
		            (size) -= _uni_status, 0))                                         \
			;                                                                          \
		else



#define SO 0x0e /* ShiftOut (ASCII) */
#define SI 0x0f /* ShiftIn (ASCII) */

PRIVATE char const ascii_so[] = { SO };
PRIVATE char const ascii_si[] = { SI };


/************************************************************************/
/* Stateful code page encode/decode functions.                          */
/************************************************************************/
INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_stateful_decode(struct iconv_decode *__restrict self,
                         /*cp???*/ char const *__restrict data, size_t size) {
	size_t utf8_len;
	char utf8_buf[UNICODE_UTF8_CURLEN];
	struct iconv_stateful_codepage const *cp;
	ssize_t temp, result = 0;
	if unlikely(self->icd_flags & ICONV_HASERR)
		goto err_ilseq;
	cp = self->icd_data.idd_stateful.sf_cp;
	for (; size; --size, ++data) {
		unsigned char ch;
		ch = (unsigned char)*data;
		/* Handle SI and SO */
		if unlikely(ch <= MAX_C(SI, SO)) {
			if (ch == SI) {
				self->icd_data.idd_stateful.sf_state = _ICONV_DECODE_STATEFUL_SB;
				continue;
			} else if (ch == SO) {
				self->icd_data.idd_stateful.sf_state = _ICONV_DECODE_STATEFUL_DB0;
				continue;
			}
		}
		/* Switch on current state. */
		switch (self->icd_data.idd_stateful.sf_state) {

		case _ICONV_DECODE_STATEFUL_SB: {
			char16_t outch;
			outch = cp->isc_sb[ch];
			if unlikely(outch == 0 && ch != 0) {
				/* Invalid input character. */
				if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->icd_flags))
					goto err_ilseq;
				if (IS_ICONV_ERR_DISCARD(self->icd_flags))
					continue;
				outch = '?';
				if (!IS_ICONV_ERR_REPLACE(self->icd_flags))
					outch = (char16_t)ch;
			}
			utf8_len = (size_t)(unicode_writeutf8(utf8_buf, outch) - utf8_buf);
			DO_decode_output(utf8_buf, utf8_len);
		}	break;

		case _ICONV_DECODE_STATEFUL_DB0: {
			/* Collect first byte for double-byte character. */
			self->icd_data.idd_stateful.sf_b0    = ch;
			self->icd_data.idd_stateful.sf_state = _ICONV_DECODE_STATEFUL_DB1;
		}	break;

		case _ICONV_DECODE_STATEFUL_DB1: {
			struct iconv_stateful_range const *ent;
			uint16_t lo, hi;
			uint16_t ch16 = ((uint16_t)self->icd_data.idd_stateful.sf_b0 << 8) | (uint16_t)ch;
			char32_t uni;
			/* Now to decode `ch16' (which is kind-of complicated) */
			lo = 0;
			hi = cp->isc_db_count;
			for (;;) {
				uint16_t i;
				assert(lo <= hi);
				i   = (lo + hi) / 2;
				ent = &cp->isc_db_ranges[i];
				if (ch16 < iconv_stateful_range_start(ent)) {
					hi = i + 1;
				} else if (ch16 >= iconv_stateful_range_end(ent)) {
					if unlikely(ch16 == 0xffff) /* Special case not covered by the table. */
						goto decode_unknown_c16;
					lo = i;
				} else {
					/* Found it! */
					break;
				}
			}

			/* Figure out what kind of entry this is. */
			if (ent->isr_uni_off >= cp->isc_rab_minoff &&
			    ent->isr_uni_off <= cp->isc_rab_maxoff) {

				/* Random access character */
				uint16_t uni_offset, rab_index;
				rab_index  = ent->isr_uni_off - cp->isc_rab_minoff;
				uni_offset = self->icd_data.idd_stateful.sf_rab[rab_index];
				uni_offset += ch - ent->isr_cp_ord;
				if (uni_offset >= cp->isc_u16_count) {
					/* 32-bit entry */
					uint32_t u32_value;
					u32_value = self->icd_data.idd_stateful.sf_u32[uni_offset - cp->isc_u16_count];
					if (u32_value & UINT32_C(0x80000000)) {
						/* 1-character sequence */
						uni = u32_value & UINT32_C(0x7fffffff);
					} else {
						/* 2-character sequence */
						char16_t c1, c2;
						c1 = (char16_t)((u32_value & UINT32_C(0xffff0000)) >> 16);
						c2 = (char16_t)((u32_value & UINT32_C(0x0000ffff)));

						/* Output the first character. */
						utf8_len = (size_t)(unicode_writeutf8(utf8_buf, c1) - utf8_buf);
						DO_decode_output(utf8_buf, utf8_len);

						/* Output the second character. */
						uni = c2;
					}
				} else {
					/* 16-bit entry */
					uni = self->icd_data.idd_stateful.sf_u16[uni_offset];
					if unlikely(uni == 0)
						goto decode_unknown_c16;
				}
			} else {
				/* Identity character or unmapped */
				if unlikely(ent->isr_uni_off == 0 && ch16 != 0)
					goto decode_unknown_c16;
				uni = (char32_t)(char16_t)(uint16_t)(ch16 + ent->isr_uni_off);
			}

do_double_uni_and_set_db0:
			/* Encode unicode as UTF-8 */
			utf8_len = (size_t)(unicode_writeutf8(utf8_buf, uni) - utf8_buf);
			DO_decode_output(utf8_buf, utf8_len);

			/* Switch back to DB0 */
			self->icd_data.idd_stateful.sf_state = _ICONV_DECODE_STATEFUL_DB0;
			break;

			/* Invalid input character. */
decode_unknown_c16:
			if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->icd_flags))
				goto err_ilseq;
			if (IS_ICONV_ERR_DISCARD(self->icd_flags)) {
				self->icd_data.idd_stateful.sf_state = _ICONV_DECODE_STATEFUL_DB0;
				continue;
			}
			uni = '?';
			if (!IS_ICONV_ERR_REPLACE(self->icd_flags))
				uni = (char32_t)(char16_t)ch;
			goto do_double_uni_and_set_db0;
		}	break;

		default:
			__builtin_unreachable();
		}
	}
	return result;
err:
	return temp;
err_ilseq:
	self->icd_flags |= ICONV_HASERR;
	if (IS_ICONV_ERR_ERRNO(self->icd_flags))
		errno = EILSEQ;
	return -(ssize_t)size;
}


INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_stateful_encode(struct iconv_encode *__restrict self,
                         /*utf-8*/ char const *__restrict data, size_t size) {
	char32_t ch;
	unsigned char outbuf[2];
	ssize_t temp, result = 0;
	struct iconv_stateful_codepage const *cp;
	struct iconv_stateful_encode_range const *isc_encode_ranges;
	if unlikely(self->ice_flags & ICONV_HASERR)
		goto err_ilseq;

	/* Enumerate unicode characters from the input stream */
	cp                = self->ice_data.ied_stateful.sf_cp;
	isc_encode_ranges = self->ice_data.ied_stateful.sf_encode_ranges;
	FOREACH_UTF8(ch, self, data, size) {
		uint16_t cp_ch;
		if unlikely(self->ice_data.ied_stateful.sf_state == _ICONV_ENCODE_STATEFUL_DB_2CH) {
			struct iconv_stateful_2char_encode const *twochar_ent;
			/* Check if there is a special encoding for `ch' in a 2-character sequence. */
			twochar_ent = self->ice_data.ied_stateful.sf_2char;
			while (twochar_ent->is2ce_uni2 != 0 && twochar_ent->is2ce_uni2 != ch)
				++twochar_ent;
			/* Output the character. */
			outbuf[0] = (unsigned char)((twochar_ent->is2ce_cp & 0xff00) >> 8);
			outbuf[1] = (unsigned char)((twochar_ent->is2ce_cp & 0x00ff));
			DO_encode_output((char const *)outbuf, 2);
			self->ice_data.ied_stateful.sf_state = _ICONV_ENCODE_STATEFUL_DB;
			if (twochar_ent->is2ce_uni2 != 0)
				continue; /* Consume the second unicode character. */
			/* Fallthru: no special sequence encoded; parse the second character like normal. */
		}
		if likely(ch < 0xffff) {
			struct iconv_stateful_encode_range const *ent;
			uint16_t lo, hi;
			lo = 0;
			hi = cp->isc_encode_count;
			for (;;) {
				uint16_t i;
				assert(lo <= hi);
				i   = (lo + hi) / 2;
				ent = &isc_encode_ranges[i];
				if (ch < iconv_stateful_encode_range_start(ent)) {
					hi = i + 1;
				} else if (ch >= iconv_stateful_encode_range_end(ent)) {
					lo = i;
				} else {
					/* Found it! */
					break;
				}
			}
			if (ent->iser_cp_off >= cp->isc_encode_rab_minoff &&
			    ent->iser_cp_off <= cp->isc_encode_rab_maxoff) {
				/* Random access character */
				uint16_t cp_offset, rab_index, result;
				uint16_t const *isc_encode_rab, *isc_encode_tab;
				isc_encode_rab = iconv_stateful_codepage__isc_encode_rab__from__isc_encode_ranges(cp, isc_encode_ranges);
				isc_encode_tab = iconv_stateful_codepage__isc_encode_tab__from__isc_encode_rab(cp, isc_encode_rab);
				rab_index      = ent->iser_cp_off - cp->isc_encode_rab_minoff;
				cp_offset      = isc_encode_rab[rab_index];
				cp_offset += ch - ent->iser_uni_ord;
				if (cp_offset >= cp->isc_encode_tab_count) {
					/* 2-char unicode sequence */
					struct iconv_stateful_2char_encode const *entry, *isc_encode_2ch;
					isc_encode_2ch = iconv_stateful_codepage__isc_encode_2ch__from__isc_encode_tab(cp, isc_encode_tab);
					entry          = &isc_encode_2ch[cp_offset - cp->isc_encode_tab_count];
					if (self->ice_data.ied_stateful.sf_state == _ICONV_ENCODE_STATEFUL_SB)
						DO_encode_output(ascii_so, sizeof(ascii_so)); /* Switch to double-byte mode. */
					self->ice_data.ied_stateful.sf_state = _ICONV_ENCODE_STATEFUL_DB_2CH;
					self->ice_data.ied_stateful.sf_2char = entry;
					continue; /* Load the next input character. */
				}
				/* Single-character encoding. */
				cp_ch = isc_encode_tab[cp_offset];
				if unlikely(result == 0) {
cannot_encode_ch:
					if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->ice_flags)) {
						data -= _uni_status;
						size += _uni_status;
						goto err_ilseq;
					}
					if (IS_ICONV_ERR_DISCARD(self->ice_flags))
						continue; /* Just ignore */
					cp_ch = cp->isc_encode_repl;
					if (!IS_ICONV_ERR_REPLACE(self->ice_flags))
						cp_ch = (uint16_t)ch & 0xffff;
				}
			} else {
				/* Identity character */
				if unlikely(ent->iser_cp_off == 0)
					goto cannot_encode_ch; /* Unmapped range */
				cp_ch = (uint16_t)((uint16_t)ch + ent->iser_cp_off);
			}
		} else {
			uint16_t lo, hi;
			struct iconv_stateful_c32_encode const *ent;
			struct iconv_stateful_c32_encode const *isc_encode_c32;
			/* Encode a 32-bit unicode character. */
			isc_encode_c32 = iconv_stateful_codepage__isc_encode_c32__from__isc_encode_ranges(cp, isc_encode_ranges);
			lo             = 0;
			hi             = cp->isc_encode_c32_count;
			for (;;) {
				uint16_t i;
				if (!(lo < hi))
					goto cannot_encode_ch;
				i   = (lo + hi) / 2;
				ent = &isc_encode_c32[i];
				if (ch < ent->isc32e_uni) {
					hi = i + 1;
				} else if (ch > ent->isc32e_uni) {
					lo = i;
				} else {
					/* Found it! */
					break;
				}
			}
			/* Encode `ent->isc32e_cp', which is guarantied to be double-byte */
			assert((ent->isc32e_cp & 0xff00) != 0);
			cp_ch = ent->isc32e_cp;
			goto do_encode_db;
		}

		/* Output a 1- or 2-byte character. */
		if ((cp_ch & 0xff00) == 0) {
			if (self->ice_data.ied_stateful.sf_state == _ICONV_ENCODE_STATEFUL_DB) {
				DO_encode_output(ascii_si, sizeof(ascii_si));
				self->ice_data.ied_stateful.sf_state = _ICONV_ENCODE_STATEFUL_SB;
			}
			outbuf[0] = (unsigned char)cp_ch;
			DO_encode_output((char const *)outbuf, 1);
		} else {
do_encode_db:
			if (self->ice_data.ied_stateful.sf_state == _ICONV_ENCODE_STATEFUL_SB) {
				DO_encode_output(ascii_so, sizeof(ascii_so));
				self->ice_data.ied_stateful.sf_state = _ICONV_ENCODE_STATEFUL_DB;
			}
			outbuf[0] = (unsigned char)((cp_ch & 0xff00) >> 8);
			outbuf[1] = (unsigned char)((cp_ch & 0x00ff));
			DO_encode_output((char const *)outbuf, 2);
		}
	} /* FOREACH_UTF8 */
	return result;
err:
	return temp;
err_ilseq:
	self->ice_flags |= ICONV_HASERR;
	if (IS_ICONV_ERR_ERRNO(self->ice_flags))
		errno = EILSEQ;
	return -(ssize_t)size;
}



/* TODO: ibm1390 and ibm1399 have the same double-byte tables and
 *       only differ in how they encode their single-byte  parts.
 *       As such, we can get rid of one of them and implement the
 *       other by use  of a custom  encode/decode function  using
 *       the data of the other, saving  a bunch of memory in  the
 *       process! */

/* TODO: Support for transliteration. Also: export the transliterate
 *       function from the main libiconv.so, so this library is able
 *       to import it!
 *       For this purpose, use `dlgetmodule(3)' w/o the INCREF flag.
 *       If that function fails, we  can just abort(3) since if  you
 *       load this library  without first  loading libiconv,  you're
 *       already doing something wrong! */



/* Initialize a stateful encoder/decoder. */
INTERN NONNULL((1, 2)) void CC
libiconv_stateful_decode_init(struct iconv_decode *__restrict self,
                              /*out*/ struct iconv_printer *__restrict input) {
	struct iconv_stateful_codepage const *cp;
	assert(self->icd_codec >= CODEC_STATEFUL_MIN &&
	       self->icd_codec <= CODEC_STATEFUL_MAX);
	cp = libiconv_stateful_page(self->icd_codec);
	/* Initialize the decoder. */
	self->icd_data.idd_stateful.sf_state = _ICONV_DECODE_STATEFUL_SB;
	self->icd_data.idd_stateful.sf_cp    = cp;
	self->icd_data.idd_stateful.sf_rab   = iconv_stateful_codepage__isc_rab(cp);
	self->icd_data.idd_stateful.sf_u16   = iconv_stateful_codepage__isc_u16__from__isc_rab(cp, self->icd_data.idd_stateful.sf_rab);
	self->icd_data.idd_stateful.sf_u32   = iconv_stateful_codepage__isc_u32__from__isc_u16(cp, self->icd_data.idd_stateful.sf_u16);
	/* Initialize the input pipe. */
	input->ii_arg     = self;
	input->ii_printer = (pformatprinter)&libiconv_stateful_decode;
}

INTERN NONNULL((1, 2)) void CC
libiconv_stateful_encode_init(struct iconv_encode *__restrict self,
                              /*out*/ struct iconv_printer *__restrict input) {
	struct iconv_stateful_codepage const *cp;
	assert(self->ice_codec >= CODEC_STATEFUL_MIN &&
	       self->ice_codec <= CODEC_STATEFUL_MAX);
	cp = libiconv_stateful_page(self->ice_codec);
	/* Initialize the encoder. */
	mbstate_init(&self->ice_data.ied_utf8);
	self->ice_data.ied_stateful.sf_state         = _ICONV_ENCODE_STATEFUL_SB;
	self->ice_data.ied_stateful.sf_cp            = cp;
	self->ice_data.ied_stateful.sf_encode_ranges = iconv_stateful_codepage__isc_encode_ranges(cp);
	/* Initialize the input pipe. */
	input->ii_arg     = self;
	input->ii_printer = (pformatprinter)&libiconv_stateful_encode;
}

/* These two functions are lazily loaded in `/libiconv/iconv.c' */
DEFINE_PUBLIC_ALIAS(iconv_stateful_decode_init, libiconv_stateful_decode_init);
DEFINE_PUBLIC_ALIAS(iconv_stateful_encode_init, libiconv_stateful_encode_init);

DECL_END
#endif /* CODEC_STATEFUL_COUNT != 0 */

#endif /* !GUARD_LIBICONV_STATEFUL_CP_STATEFUL_C */
