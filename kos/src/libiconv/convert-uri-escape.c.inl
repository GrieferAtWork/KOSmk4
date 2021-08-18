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


INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_uri_escape_encode(struct iconv_encode *__restrict self,
                           /*bytes*/ char const *__restrict data,
                           size_t size) {
	ssize_t temp, result = 0;
	char const *end, *flush_start;
	flush_start = data;
	end         = data + size;
	while (data < end) {
		unsigned char ch;
		ch = (unsigned char)*data;
		/* Only the bytes associated with the following
		 * ASCI characters  don't need  to be  escaped:
		 *    A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
		 *    a b c d e f g h i j k l m n o p q r s t u v w x y z
		 *    0 1 2 3 4 5 6 7 8 9 - _ . ~ */
		switch (ch) {

		case 'A' ... 'Z':
		case 'a' ... 'z':
		case '0' ... '9':
		case '-':
		case '_':
		case '.':
		case '~':
			/* Don't need to escape this! */
			break;

		default: {
			char esc[3];
			DO_encode_output(flush_start, (size_t)(data - flush_start));
			esc[0] = '%';
			esc[1] = upper_hex[(ch & 0xf0) >> 4];
			esc[2] = upper_hex[ch & 0xf];
			DO_encode_output(esc, 3);
			flush_start = data + 1;
		}	break;

		}
		++data;
	}
	DO_encode_output(flush_start, (size_t)(end - flush_start));
	return result;
err:
	return temp;
}

INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libiconv_uri_escape_decode(struct iconv_decode *__restrict self,
                           /*ascii*/ char const *__restrict data,
                           size_t size) {
	ssize_t temp, result = 0;
	char const *end, *flush_start;
	flush_start = data;
	end         = data + size;
	if unlikely(self->icd_flags & ICONV_HASERR)
		goto err_ilseq;
	while (data < end) {
		unsigned char ch = (unsigned char)*data;
		if unlikely(self->icd_data.idd_uri.ue_mode != _ICONV_DECODE_URI_TXT) {
			uint8_t nibble;
			if (ch >= '0' && ch <= '9') {
				nibble = ch - '0';
			} else if (ch >= 'A' && ch <= 'F') {
				nibble = 10 + ch - 'A';
			} else if (ch >= 'a' && ch <= 'f') {
				nibble = 10 + ch - 'a';
			} else {
				/* TODO: Custom error handling! */
				goto err_ilseq;
			}
			if (self->icd_data.idd_uri.ue_mode == _ICONV_DECODE_URI_PCT) {
				self->icd_data.idd_uri.ue_chr = nibble << 4;
				self->icd_data.idd_uri.ue_mode = _ICONV_DECODE_URI_PCT_1;
			} else {
				nibble |= self->icd_data.idd_uri.ue_chr;
				/* Output the fully decoded character. */
				DO_decode_output((char const *)&nibble, 1);
				self->icd_data.idd_uri.ue_mode = _ICONV_DECODE_URI_TXT;
				flush_start = data + 1;
			}
		} else {
			/* Only the bytes associated with the following
			 * ASCI characters  don't need  to be  escaped:
			 *    A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
			 *    a b c d e f g h i j k l m n o p q r s t u v w x y z
			 *    0 1 2 3 4 5 6 7 8 9 - _ . ~ */
			switch (ch) {
	
			case 'A' ... 'Z':
			case 'a' ... 'z':
			case '0' ... '9':
			case '-':
			case '_':
			case '.':
			case '~':
				/* Allowed as-is. */
				break;
	
			case '%':
				/* Enter escape mode. */
				DO_decode_output(flush_start, (size_t)(data - flush_start));
				self->icd_data.idd_uri.ue_mode = _ICONV_DECODE_URI_PCT;
				break;
	
			default:
				/* Illegal character! */
				/* TODO: Custom error handling! */
				goto err_ilseq;
			}
		}
		++data;
	}
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
