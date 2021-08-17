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

PRIVATE char const upper_hex[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

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
	if (self->ice_data.ied_utf8.__word != __MBSTATE_TYPE_EMPTY)
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
						self->ice_data.ied_utf8.__word = __MBSTATE_TYPE_EMPTY;
						flush_start                    = data;
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

//INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
//libiconv_c_escape_decode(struct iconv_decode *__restrict self,
//                         /*ascii*/ char const *__restrict data, size_t size) {
//	/* TODO */
//}

DECL_END
