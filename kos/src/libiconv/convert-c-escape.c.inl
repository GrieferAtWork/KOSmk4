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
#ifdef __INTELLISENSE__
#include "convert.c"
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#ifndef UPPER_HEX_DEFINED
#define UPPER_HEX_DEFINED
PRIVATE char const upper_hex[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};
#endif /* !UPPER_HEX_DEFINED */

INTERN NONNULL((1, 2)) size_t
NOTHROW(CC libiconv_c_escape_byte)(struct iconv_encode *__restrict self,
                                   char buf[4], unsigned char b) {
	size_t result;
	buf[0] = '\\';
	result = 2;
	switch (b) {

	case 0x07: buf[1] = 'a'; break;
	case 0x08: buf[1] = 'b'; break;
	case 0x09: buf[1] = 't'; break;
	case 0x0a: buf[1] = 'n'; break;
	case 0x0b: buf[1] = 'v'; break;
	case 0x0c: buf[1] = 'f'; break;
	case 0x0d: buf[1] = 'r'; break;
	case 0x1b: buf[1] = 'e'; break;

	case '\\':
	case '\'':
	case '\"':
		/* Escape with itself. */
		buf[1] = (char)b;
		break;

	case 0 ... 6:
		buf[1] = '0' + b;
		self->ice_flags |= _ICONV_CENCODE_POSTOCT;
		break;

	case 0x0e ... 0x1a:
	case 0x1c ... 0x1f:
		/* Encode as a 3-character octal */
		buf[1] = '0';
		buf[2] = '0' + ((b >> 3) & 7);
		buf[3] = '0' + (b & 7);
		result = 4;
		break;

	default:
		/* Fallback escape as a 2-character hex */
		buf[1] = 'x';
		buf[2] = upper_hex[(b >> 4) & 0xf];
		buf[3] = upper_hex[b & 0xf];
		result = 4;
		self->ice_flags |= _ICONV_CENCODE_POSTHEX;
		break;
	}
	return result;
}


INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_c_escape_encode(struct iconv_encode *__restrict self,
                         /*utf-8*/ char const *__restrict data, size_t size) {
	ssize_t temp, result = 0;
	char const *end, *flush_start;
	if ((self->ice_flags & (_ICONV_CENCODE_NOQUOTE | _ICONV_CENCODE_INQUOTE)) == 0) {
		char quote[1] = { '\"' };
		/* Always emit quotes if printers were invoked at least once. */
		if (self->ice_flags & _ICONV_CENCODE_USECHAR)
			quote[0] = '\'';
		DO_encode_output(quote, 1);
		self->ice_flags |= _ICONV_CENCODE_INQUOTE;
	}
	flush_start = data;
	end         = data + size;
	if unlikely(self->ice_flags & ICONV_HASERR)
		goto err_ilseq;
	if (!mbstate_isempty(&self->ice_data.ied_utf8))
		goto parse_unicode;
	while (data < end) {
		unsigned char ch;
		ch = (unsigned char)*data;
		if (ch >= 0x80 && !(self->ice_flags & _ICONV_CENCODE_NOUNICD)) {
			char unibuf[MAX_C(UNICODE_UTF8_CURLEN, 10)];
			char32_t ch32;
			size_t status;
			DO_encode_output(flush_start, (size_t)(data - flush_start));
parse_unicode:
			status = unicode_c8toc32(&ch32, data, (size_t)(end - data),
			                         &self->ice_data.ied_utf8);
			if ((ssize_t)status < 0) {
				if (status == (size_t)-1) {
					ch = (unsigned char)*data;
					if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->ice_flags))
						goto err_ilseq;
					if (IS_ICONV_ERR_DISCARD(self->ice_flags)) {
						mbstate_init(&self->ice_data.ied_utf8);
						flush_start = data + 1;
						goto next_data;
					}
					/* Special case: we can actually ignore utf-8 errors  by
					 * encoding bad bytes output of unicode escape sequences
					 * when simply using \xAB encoding! */
					if (IS_ICONV_ERR_IGNORE(self->ice_flags))
						goto escape_bytes;
					ch32   = '?';
					status = 1;
				} else if (status == (size_t)-2) {
					return result; /* Everything parsed! */
				}
			}
			data += status;
			flush_start = data;

			/* Printable characters are emit as-is. */
			if (unicode_isprint(ch32)) {
				/* A couple of characters require special treatment! */
				switch (ch32) {

				case '\\':
					goto force_escape_ch32;

				case '\"':
					/* The " character doesn't need to be escaped when using c-escape-chr */
					if ((self->ice_flags & (_ICONV_CENCODE_NOQUOTE | _ICONV_CENCODE_USECHAR)) != _ICONV_CENCODE_USECHAR)
						goto force_escape_ch32;
					break;

				case '\'':
					/* The ' character doesn't need to be escaped when using c-escape-str */
					if ((self->ice_flags & (_ICONV_CENCODE_NOQUOTE | _ICONV_CENCODE_USECHAR)) != 0)
						goto force_escape_ch32;
					break;

				case '0' ... '7':
					if (self->ice_flags & (_ICONV_CENCODE_POSTHEX | _ICONV_CENCODE_POSTOCT)) {
						char seq[3];
uni_handle_illegal_after_escape:
						/* If we're not allowed to begin a new string, we
						 * must escape this normally printable character. */
						if (self->ice_flags & _ICONV_CENCODE_NOQUOTE)
							goto force_escape_ch32;
						seq[0] = '\"';
						if (self->ice_flags & _ICONV_CENCODE_USECHAR)
							seq[0] = '\'';
						seq[1] = ' ';
						seq[2] = seq[0];
						DO_encode_output(seq, 3);
					}
					break;

				case '8' ... '9':
				case 'a' ... 'f':
				case 'A' ... 'F':
					if (self->ice_flags & _ICONV_CENCODE_POSTHEX)
						goto uni_handle_illegal_after_escape;
					break;

				default:
					break;
				}
				self->ice_flags &= ~(_ICONV_CENCODE_POSTHEX | _ICONV_CENCODE_POSTOCT);
				status = (size_t)(unicode_writeutf8(unibuf, ch32) - unibuf);
			} else {
force_escape_ch32:
				self->ice_flags &= ~(_ICONV_CENCODE_POSTHEX | _ICONV_CENCODE_POSTOCT);
				if unlikely(ch32 <= 0x7f) {
					/* This can happen, but shouldn't in theory! */
					status = libiconv_c_escape_byte(self, unibuf, (unsigned char)ch32);
				} else {
					unibuf[0] = '\\';
					if (ch32 <= 0xffff) {
						/* Output as \uXXXX */
						unibuf[1] = 'u';
						unibuf[2] = upper_hex[(ch32 & UINT16_C(0xf000)) >> 12];
						unibuf[3] = upper_hex[(ch32 & UINT16_C(0x0f00)) >> 8];
						unibuf[4] = upper_hex[(ch32 & UINT16_C(0x00f0)) >> 4];
						unibuf[5] = upper_hex[(ch32 & UINT16_C(0x000f)) >> 0];
						status    = 6;
					} else {
						/* Output as \UXXXXXXXX */
						unibuf[1] = 'U';
						unibuf[2] = upper_hex[(ch32 & UINT32_C(0xf000)) >> 12];
						unibuf[3] = upper_hex[(ch32 & UINT32_C(0x0f00)) >> 8];
						unibuf[4] = upper_hex[(ch32 & UINT32_C(0x00f0)) >> 4];
						unibuf[5] = upper_hex[(ch32 & UINT32_C(0x000f)) >> 0];
						unibuf[6] = upper_hex[(ch32 & UINT32_C(0x000f)) >> 0];
						unibuf[7] = upper_hex[(ch32 & UINT32_C(0x000f)) >> 0];
						unibuf[8] = upper_hex[(ch32 & UINT32_C(0x000f)) >> 0];
						unibuf[9] = upper_hex[(ch32 & UINT32_C(0x000f)) >> 0];
						status    = 10;
					}
				}
			}

			/* Output `ch32' in its escaped form. */
			DO_encode_output(unibuf, status);
		} else {
			/* Output `ch' and escape it if necessary */
escape_bytes:
			if (ch >= 0x20 && ch <= 0x7e) {
				/* Simple case: printable (iow: unescaped) ASCII sub-set.
				 * But note that we have to do special handling for 0-9, A-F, a-f in certain cases! */
				switch (ch) {

					/* A couple of characters require special treatment! */
				case '\\':
					goto force_escape_ch;

				case '\"':
					/* The " character doesn't need to be escaped when using c-escape-chr */
					if ((self->ice_flags & (_ICONV_CENCODE_NOQUOTE | _ICONV_CENCODE_USECHAR)) != _ICONV_CENCODE_USECHAR)
						goto force_escape_ch;
					break;

				case '\'':
					/* The ' character doesn't need to be escaped when using c-escape-str */
					if ((self->ice_flags & (_ICONV_CENCODE_NOQUOTE | _ICONV_CENCODE_USECHAR)) != 0)
						goto force_escape_ch;
					break;

				case '0' ... '7':
					if (self->ice_flags & (_ICONV_CENCODE_POSTHEX | _ICONV_CENCODE_POSTOCT)) {
						char seq[3];
handle_illegal_after_escape:
						/* If we're not allowed to begin a new string, we
						 * must escape this normally printable character. */
						if (self->ice_flags & _ICONV_CENCODE_NOQUOTE)
							goto force_escape_ch;
						seq[0] = '\"';
						if (self->ice_flags & _ICONV_CENCODE_USECHAR)
							seq[0] = '\'';
						seq[1] = ' ';
						seq[2] = seq[0];
						DO_encode_output(flush_start, (size_t)(data - flush_start));
						DO_encode_output(seq, 3);
						flush_start = data;
					}
					break;

				case '8' ... '9':
				case 'a' ... 'f':
				case 'A' ... 'F':
					if (self->ice_flags & _ICONV_CENCODE_POSTHEX)
						goto handle_illegal_after_escape;
					break;

				default:
					break;
				}
				/* Clear flags for special character positions (since we're no longer in such a position) */
				self->ice_flags &= ~(_ICONV_CENCODE_POSTHEX | _ICONV_CENCODE_POSTOCT);
			} else {
				char buf[4];
				size_t len;
force_escape_ch:
				/* Emit an escape sequence. */
				len = libiconv_c_escape_byte(self, buf, ch);
				DO_encode_output(flush_start, (size_t)(data - flush_start));
				DO_encode_output(buf, len);
				flush_start = data + 1;
			}
next_data:
			++data;
		}
	}
	DO_encode_output(flush_start, (size_t)(end - flush_start));
	return result;
err:
	return temp;
err_ilseq:
	self->ice_flags |= ICONV_HASERR;
	if (IS_ICONV_ERR_ERRNO(self->ice_flags))
		errno = EILSEQ;
	return -(ssize_t)(size_t)(end - data);
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_c_escape_decode(struct iconv_decode *__restrict self,
                         /*utf-8*/ char const *__restrict data, size_t size) {
#define SHOULD_FLUSH() _ICONV_CDECODE_SHOULD_FLUSH(self->icd_flags & _ICONV_CDECODE_STMASK)
	ssize_t temp, result = 0;
	char const *ch_start;
	char const *end, *flush_start;
	flush_start = data;
	end         = data + size;
	if unlikely(self->icd_flags & ICONV_HASERR)
		goto err_ilseq;
	if (!mbstate_isempty(&self->icd_data.idd_cesc.ce_utf8)) {
		ch_start = data;
		goto parse_unicode;
	}
	while (data < end) {
		char32_t ch;
		ch_start = data;
		ch       = (char32_t)(unsigned char)*data;
		if (ch >= 0x80) {
			size_t status;
parse_unicode:
			status = unicode_c8toc32(&ch, data, (size_t)(end - data),
			                         &self->icd_data.idd_cesc.ce_utf8);
			if ((ssize_t)status < 0) {
				if (status == (size_t)-1) {
					if (IS_ICONV_ERR_ERROR_OR_ERRNO(self->icd_flags))
						goto err_ilseq;
					if (IS_ICONV_ERR_DISCARD(self->icd_flags)) {
						mbstate_init(&self->icd_data.idd_cesc.ce_utf8);
						if (SHOULD_FLUSH()) {
							DO_decode_output(flush_start, (size_t)(end - flush_start));
							flush_start = data + 1;
						}
						++data;
						continue;
					}
					if (!IS_ICONV_ERR_IGNORE(self->icd_flags))
						ch = '?';
					status = 1;
				} else if (status == (size_t)-2) {
					goto done; /* Everything parsed! */
				}
			}
			data += status;
		} else {
			++data;
		}

		/* Process `ch' */
switch_on_state:
		switch (self->icd_flags & _ICONV_CDECODE_STMASK) {

		case _ICONV_CDECODE_ST_RAW:
		case _ICONV_CDECODE_ST_STRIN:
		case _ICONV_CDECODE_ST_CHRIN:
		case _ICONV_CDECODE_ST_ALLIN:
			/* Process inside of a string. */
			if (ch == '\\') {
				/* Begin an escape sequence. */
				self->icd_flags |= _ICONV_CDECODE_F_ESCAPE;
				self->icd_data.idd_cesc.ce_esc = _ICONV_DECODE_CESCAPE_ESC_MODE_INIT;
flush_until_special_character:
				DO_decode_output(flush_start, (size_t)(ch_start - flush_start));
			} else if (ch == '\"') {
				if ((self->icd_flags & _ICONV_CDECODE_STMASK) == _ICONV_CDECODE_ST_STRIN) {
					if (self->icd_flags & _ICONV_CDECODE_F_ONESTR)
						goto err_ilseq_ch_start; /* Stop once the current string has ended */
					self->icd_flags &= ~_ICONV_CDECODE_STMASK;
					self->icd_flags |= _ICONV_CDECODE_ST_STR;
					goto flush_until_special_character;
				} else if ((self->icd_flags & _ICONV_CDECODE_STMASK) == _ICONV_CDECODE_ST_RAW) {
					goto err_ilseq_ch_start; /* Not allowed in raw strings! */
				}
				/* " can appear unescaped in _ICONV_CDECODE_ST_CHRIN and _ICONV_CDECODE_ST_ALLIN */
			} else if (ch == '\'') {
				if ((self->icd_flags & _ICONV_CDECODE_STMASK) == _ICONV_CDECODE_ST_CHRIN) {
					if (self->icd_flags & _ICONV_CDECODE_F_ONESTR)
						goto err_ilseq_ch_start; /* Stop once the current string has ended */
					/* Exit the string literal */
					self->icd_flags &= ~_ICONV_CDECODE_STMASK;
					self->icd_flags |= _ICONV_CDECODE_ST_CHR;
					goto flush_until_special_character;
				} else if ((self->icd_flags & _ICONV_CDECODE_STMASK) == _ICONV_CDECODE_ST_RAW) {
					goto err_ilseq_ch_start; /* Not allowed in raw strings! */
				}
				/* ' can appear unescaped in _ICONV_CDECODE_ST_STRIN and _ICONV_CDECODE_ST_ALLIN */
			} else if (unicode_islf(ch)) {
				/* Unescaped linefeeds aren't allowed inside of strings! */
				goto err_ilseq_ch_start;
			}
			break;

		case _ICONV_CDECODE_ST_RAW | _ICONV_CDECODE_F_ESCAPE:
		case _ICONV_CDECODE_ST_STRIN | _ICONV_CDECODE_F_ESCAPE:
		case _ICONV_CDECODE_ST_CHRIN | _ICONV_CDECODE_F_ESCAPE:
		case _ICONV_CDECODE_ST_ALLIN | _ICONV_CDECODE_F_ESCAPE: {
			/* Parse an escape sequence. */
			switch (self->icd_data.idd_cesc.ce_esc) {

			case _ICONV_DECODE_CESCAPE_ESC_MODE_SLF:
				/* Special handling so we can ignore `ch' iff it's \n */
				if (ch == '\n')
					goto exit_escape_at_data; /* Don't include the line-feed */

				/* Do include whatever character this is! */
exit_escape_at_ch_start:
				self->icd_flags &= ~_ICONV_CDECODE_F_ESCAPE; /* Exit escape mode */
				flush_start = ch_start;
				goto switch_on_state;

			case _ICONV_DECODE_CESCAPE_ESC_MODE_HEX:
				if (ch >= '0' && ch <= '9') {
					self->icd_data.idd_cesc.ce_esc_value = (uint8_t)(ch - '0');
				} else if (ch >= 'a' && ch <= 'f') {
					self->icd_data.idd_cesc.ce_esc_value = (uint8_t)(10 + ch - 'a');
				} else if (ch >= 'A' && ch <= 'F') {
					self->icd_data.idd_cesc.ce_esc_value = (uint8_t)(10 + ch - 'A');
				} else {
					goto err_ilseq_ch_start;
				}
				self->icd_data.idd_cesc.ce_esc_value <<= 4;
				self->icd_data.idd_cesc.ce_esc = _ICONV_DECODE_CESCAPE_ESC_MODE_HEX_1;
				break;

			case _ICONV_DECODE_CESCAPE_ESC_MODE_HEX_1:
				if (ch >= '0' && ch <= '9') {
					self->icd_data.idd_cesc.ce_esc_value |= (uint8_t)(ch - '0');
				} else if (ch >= 'a' && ch <= 'f') {
					self->icd_data.idd_cesc.ce_esc_value |= (uint8_t)(10 + ch - 'a');
				} else if (ch >= 'A' && ch <= 'F') {
					self->icd_data.idd_cesc.ce_esc_value |= (uint8_t)(10 + ch - 'A');
				} else {
					goto err_ilseq_ch_start;
				}
				self->icd_data.idd_cesc.ce_esc = _ICONV_DECODE_CESCAPE_ESC_MODE_HEX_2;
				break;

			case _ICONV_DECODE_CESCAPE_ESC_MODE_HEX_2:
				if unlikely((ch >= '0' && ch <= '9') ||
				            (ch >= 'a' && ch <= 'f') ||
				            (ch >= 'A' && ch <= 'F'))
					goto err_ilseq_ch_start;
				/* Output the custom byte and exit escape mode. */
output_esc_value:
				DO_decode_output((char const *)&self->icd_data.idd_cesc.ce_esc_value, 1);
				/* Include the current character in the next flush! */
				goto exit_escape_at_ch_start;

			case _ICONV_DECODE_CESCAPE_ESC_MODE_OCT_1:
				if (!(ch >= '0' && ch <= '7'))
					goto output_esc_value; /* Input was \1 ... \7 */
				self->icd_data.idd_cesc.ce_esc_value <<= 3;
				self->icd_data.idd_cesc.ce_esc_value |= (uint8_t)(ch - '0');
				self->icd_data.idd_cesc.ce_esc = _ICONV_DECODE_CESCAPE_ESC_MODE_OCT_2;
				break;

			case _ICONV_DECODE_CESCAPE_ESC_MODE_OCT_2:
				if (!(ch >= '0' && ch <= '7'))
					goto output_esc_value; /* Input was \00 ... \77 */
				self->icd_data.idd_cesc.ce_esc_value <<= 3;
				self->icd_data.idd_cesc.ce_esc_value |= (uint8_t)(ch - '0');
				DO_decode_output((char const *)&self->icd_data.idd_cesc.ce_esc_value, 1);
				self->icd_flags &= ~_ICONV_CDECODE_F_ESCAPE;
				break; /* Don't re-switch on `ch'! */

			case _ICONV_DECODE_CESCAPE_ESC_MODE_U16:
			case _ICONV_DECODE_CESCAPE_ESC_MODE_U16_1:
			case _ICONV_DECODE_CESCAPE_ESC_MODE_U16_2:
			case _ICONV_DECODE_CESCAPE_ESC_MODE_U16_3: {
				uint8_t digit;
				unsigned int position;
				STATIC_ASSERT(_ICONV_DECODE_CESCAPE_ESC_MODE_U16 + 1 == _ICONV_DECODE_CESCAPE_ESC_MODE_U16_1);
				STATIC_ASSERT(_ICONV_DECODE_CESCAPE_ESC_MODE_U16 + 2 == _ICONV_DECODE_CESCAPE_ESC_MODE_U16_2);
				STATIC_ASSERT(_ICONV_DECODE_CESCAPE_ESC_MODE_U16 + 3 == _ICONV_DECODE_CESCAPE_ESC_MODE_U16_3);
				if (ch >= '0' && ch <= '9') {
					digit = (uint8_t)(ch - '0');
				} else if (ch >= 'a' && ch <= 'f') {
					digit = (uint8_t)(10 + ch - 'a');
				} else if (ch >= 'A' && ch <= 'F') {
					digit = (uint8_t)(10 + ch - 'A');
				} else {
					goto err_ilseq_ch_start;
				}
				position = self->icd_data.idd_cesc.ce_esc -
				           _ICONV_DECODE_CESCAPE_ESC_MODE_U16; /* Positions are: \u<0><1><2><3> */
				position = 3 - position;                       /* Positions are: \u<3><2><1><0> */
				position <<= 2;                                /* Positions are: \u<12><8><4><0> */
				/* Add to the escape buffer. */
				self->icd_data.idd_cesc.ce_esc_u16 |= (char16_t)((uint16_t)digit << position);
				if (self->icd_data.idd_cesc.ce_esc == _ICONV_DECODE_CESCAPE_ESC_MODE_U16_3) {
					/* Last digit was decoded. -> Output the character. */
					self->icd_data.idd_cesc.ce_esc_u32 = self->icd_data.idd_cesc.ce_esc_u16;
					goto output_esc_value_u32;
				} else {
					++self->icd_data.idd_cesc.ce_esc;
				}
			}	break;

			case _ICONV_DECODE_CESCAPE_ESC_MODE_U32:
			case _ICONV_DECODE_CESCAPE_ESC_MODE_U32_1:
			case _ICONV_DECODE_CESCAPE_ESC_MODE_U32_2:
			case _ICONV_DECODE_CESCAPE_ESC_MODE_U32_3:
			case _ICONV_DECODE_CESCAPE_ESC_MODE_U32_4:
			case _ICONV_DECODE_CESCAPE_ESC_MODE_U32_5:
			case _ICONV_DECODE_CESCAPE_ESC_MODE_U32_6:
			case _ICONV_DECODE_CESCAPE_ESC_MODE_U32_7: {
				uint8_t digit;
				unsigned int position;
				STATIC_ASSERT(_ICONV_DECODE_CESCAPE_ESC_MODE_U32 + 1 == _ICONV_DECODE_CESCAPE_ESC_MODE_U32_1);
				STATIC_ASSERT(_ICONV_DECODE_CESCAPE_ESC_MODE_U32 + 2 == _ICONV_DECODE_CESCAPE_ESC_MODE_U32_2);
				STATIC_ASSERT(_ICONV_DECODE_CESCAPE_ESC_MODE_U32 + 3 == _ICONV_DECODE_CESCAPE_ESC_MODE_U32_3);
				STATIC_ASSERT(_ICONV_DECODE_CESCAPE_ESC_MODE_U32 + 4 == _ICONV_DECODE_CESCAPE_ESC_MODE_U32_4);
				STATIC_ASSERT(_ICONV_DECODE_CESCAPE_ESC_MODE_U32 + 5 == _ICONV_DECODE_CESCAPE_ESC_MODE_U32_5);
				STATIC_ASSERT(_ICONV_DECODE_CESCAPE_ESC_MODE_U32 + 6 == _ICONV_DECODE_CESCAPE_ESC_MODE_U32_6);
				STATIC_ASSERT(_ICONV_DECODE_CESCAPE_ESC_MODE_U32 + 7 == _ICONV_DECODE_CESCAPE_ESC_MODE_U32_7);
				if (ch >= '0' && ch <= '9') {
					digit = (uint8_t)(ch - '0');
				} else if (ch >= 'a' && ch <= 'f') {
					digit = (uint8_t)(10 + ch - 'a');
				} else if (ch >= 'A' && ch <= 'F') {
					digit = (uint8_t)(10 + ch - 'A');
				} else {
					goto err_ilseq_ch_start;
				}
				position = self->icd_data.idd_cesc.ce_esc -
				           _ICONV_DECODE_CESCAPE_ESC_MODE_U32; /* Positions are: \U<0><1><2><3><4><5><6><7> */
				position = 7 - position;                       /* Positions are: \U<7><6><5><4><3><2><1><0> */
				position <<= 2;                                /* Positions are: \U<28><24><20><16><12><8><4><0> */
				/* Add to the escape buffer. */
				self->icd_data.idd_cesc.ce_esc_u32 |= (char32_t)((uint32_t)digit << position);
				if (self->icd_data.idd_cesc.ce_esc == _ICONV_DECODE_CESCAPE_ESC_MODE_U16_3) {
					size_t len;
					char buf[UNICODE_UTF8_CURLEN];
					/* Last digit was decoded. -> Output the character. */
output_esc_value_u32:
					/* Encode the escaped character as utf-8 */
					len = (size_t)(unicode_writeutf8(buf, self->icd_data.idd_cesc.ce_esc_u32) - buf);
					DO_decode_output(buf, len);
					/* Exit escape mode, but don't include the current character in the next flush. */
					goto exit_escape_at_data;
				} else {
					++self->icd_data.idd_cesc.ce_esc;
				}
			}	break;

			/*case _ICONV_DECODE_CESCAPE_ESC_MODE_INIT:*/
			default: {
				char out[1];

				/* Start of sequence. */
				switch (ch) {

				case '\\':
				case '\"':
				case '\'':
					/* Self-escape */
					out[0] = (char)(unsigned char)(uint32_t)ch;
					goto do_output_special;

				case 'a':
					out[0] = 0x07;
					goto do_output_special;

				case 'b':
					out[0] = 0x08;
					goto do_output_special;

				case 't':
					out[0] = 0x09;
					goto do_output_special;

				case 'n':
					out[0] = 0x0a;
					goto do_output_special;

				case 'v':
					out[0] = 0x0b;
					goto do_output_special;

				case 'f':
					out[0] = 0x0c;
					goto do_output_special;

				case 'r':
					out[0] = 0x0d;
					goto do_output_special;

				case 'e':
					out[0] = 0x1b;
do_output_special:
					/* Output the unescaped character */
					DO_decode_output(out, 1);
					/* Exit escape mode */
exit_escape_at_data:
					self->icd_flags &= ~_ICONV_CDECODE_F_ESCAPE;
					flush_start = data;
					break;

				case 'x':
				case 'X':
					self->icd_data.idd_cesc.ce_esc = _ICONV_DECODE_CESCAPE_ESC_MODE_HEX;
					break;

				case '0' ... '7':
					self->icd_data.idd_cesc.ce_esc = _ICONV_DECODE_CESCAPE_ESC_MODE_OCT_1;
					self->icd_data.idd_cesc.ce_esc_value = (uint8_t)(ch - '0');
					break;

				case 'u':
					self->icd_data.idd_cesc.ce_esc = _ICONV_DECODE_CESCAPE_ESC_MODE_U16;
					self->icd_data.idd_cesc.ce_esc_value = 0;
					break;

				case 'U':
					self->icd_data.idd_cesc.ce_esc = _ICONV_DECODE_CESCAPE_ESC_MODE_U32;
					self->icd_data.idd_cesc.ce_esc_value = 0;
					break;

				case '\r':
					/* Special case: If the next character is \n, then it must also be ignored.
					 * We do this by setting the first byte of the saved escape sequence as \r */
					self->icd_data.idd_cesc.ce_esc = _ICONV_DECODE_CESCAPE_ESC_MODE_SLF;
					break;

				default:
					if (unicode_islf(ch))
						goto exit_escape_at_data; /* Escaped linefeed. (just ignore) */

					/* Unrecognized start of escape sequence. */
					goto err_ilseq_ch_start;
				}
			}	break;

			}
		}	break;

		case _ICONV_CDECODE_ST_STR:
		case _ICONV_CDECODE_ST_CHR:
			/* Skip space characters outside of strings */
			if (unicode_isspace(ch))
				break;

			/* Check if another string starts here! */
			if (ch == ((self->icd_flags & _ICONV_CDECODE_STMASK) == _ICONV_CDECODE_ST_STR ? '\"' : '\'')) {
				/* Switch back to inside-of-string mode. */
				self->icd_flags = (self->icd_flags & ~_ICONV_CDECODE_STMASK) |
				                  ((self->icd_flags & _ICONV_CDECODE_STMASK) == _ICONV_CDECODE_ST_STR
				                   ? _ICONV_CDECODE_ST_STRIN
				                   : _ICONV_CDECODE_ST_CHRIN);
				flush_start = data;
				break;
			}

			/* Anything else isn't allowed outside of strings. */
err_ilseq_ch_start:
			data = ch_start;
			goto err_ilseq;

		case _ICONV_CDECODE_ST_UNDEF:
			/* Determine string-mode via the first character encountered. */
			self->icd_flags &= ~_ICONV_CDECODE_STMASK;
			flush_start = data;
			if (ch == '\"') {
				self->icd_flags |= _ICONV_CDECODE_ST_STRIN;
			} else if (ch == '\'') {
				self->icd_flags |= _ICONV_CDECODE_ST_CHRIN;
			} else {
				/* Everything else counts as a raw string, in which case we
				 * need to process the current character as the first apart
				 * of the string. */
				self->icd_flags |= _ICONV_CDECODE_ST_RAW;
				flush_start = ch_start;
				goto switch_on_state;
			}
			break;

		default:
			/* Normal character inside of string; -> nothing to do! */
			break;
		}
	}
done:
	if (SHOULD_FLUSH())
		DO_decode_output(flush_start, (size_t)(end - flush_start));
	return result;
err:
	return temp;
err_ilseq:
	self->icd_flags |= ICONV_HASERR;
	if (IS_ICONV_ERR_ERRNO(self->icd_flags))
		errno = EILSEQ;
	return -(ssize_t)(size_t)(end - data);
}

DECL_END
