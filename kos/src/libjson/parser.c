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
#ifndef GUARD_LIBJSON_PARSER_C
#define GUARD_LIBJSON_PARSER_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/unaligned.h>

#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <uchar.h>
#include <unicode.h>

#include "parser.h"

DECL_BEGIN

#define isradixch(ch) ((ch) == 'x' || (ch) == 'X' || (ch) == 'b' || (ch) == 'B')


/* RETURN *<ptr>++; */
PRIVATE NONNULL((1)) char32_t
NOTHROW_NCX(CC json_getc)(struct json_parser *__restrict self) {
	char32_t result;
	switch (__builtin_expect(self->jp_encoding, JSON_ENCODING_UTF8)) {

	case JSON_ENCODING_UTF8:
		result = unicode_readutf8_n((char const **)&self->jp_pos,
		                            (char const *)self->jp_end);
		break;

	case JSON_ENCODING_UTF16LE:
		result = unicode_readutf16le_n((char16_t const **)&self->jp_pos,
		                               (char16_t const *)self->jp_end);
		break;

	case JSON_ENCODING_UTF32LE:
		result = unicode_readutf32le_n((char32_t const **)&self->jp_pos,
		                               (char32_t const *)self->jp_end);
		break;

	case JSON_ENCODING_UTF16BE:
		result = unicode_readutf16be_n((char16_t const **)&self->jp_pos,
		                               (char16_t const *)self->jp_end);
		break;

	case JSON_ENCODING_UTF32BE:
		result = unicode_readutf32be_n((char32_t const **)&self->jp_pos,
		                               (char32_t const *)self->jp_end);
		break;

	default: __builtin_unreachable();
	}
	return result;
}


/* RETURN *--<ptr>; */
PRIVATE NONNULL((1)) char32_t
NOTHROW_NCX(CC json_ungetc)(struct json_parser *__restrict self) {
	char32_t result;
	switch (__builtin_expect(self->jp_encoding, JSON_ENCODING_UTF8)) {

	case JSON_ENCODING_UTF8:
		result = unicode_readutf8_rev_n((char const **)&self->jp_pos,
		                                (char const *)self->jp_start);
		break;

	case JSON_ENCODING_UTF16LE:
		result = unicode_readutf16le_rev_n((char16_t const **)&self->jp_pos,
		                                   (char16_t const *)self->jp_start);
		break;

	case JSON_ENCODING_UTF32LE:
		result = unicode_readutf32le_rev_n((char32_t const **)&self->jp_pos,
		                                   (char32_t const *)self->jp_start);
		break;

	case JSON_ENCODING_UTF16BE:
		result = unicode_readutf16be_rev_n((char16_t const **)&self->jp_pos,
		                                   (char16_t const *)self->jp_start);
		break;

	case JSON_ENCODING_UTF32BE:
		result = unicode_readutf32be_rev_n((char32_t const **)&self->jp_pos,
		                                   (char32_t const *)self->jp_start);
		break;

	default: __builtin_unreachable();
	}
	return result;
}

#ifndef CONFIG_NO_JSON_C_COMMENT_SUPPORT
/* Skip a comment after already having parsed `/' and `*', with
 * the parser currently pointing at the first character of  the
 * comment body. */
PRIVATE NONNULL((1)) int
NOTHROW_NCX(CC json_skip_comment)(struct json_parser *__restrict self) {
	char const *cbody_start;
	cbody_start = self->jp_pos;
	switch (__builtin_expect(self->jp_encoding, JSON_ENCODING_UTF8)) {

	case JSON_ENCODING_UTF8:
		for (;;) {
			char const *pos;
			pos = (char const *)memchr(self->jp_pos, '*',
			                           (size_t)(self->jp_end - self->jp_pos));
			if (!pos || pos >= self->jp_end - 1)
				goto comment_syn;
			if (pos[1] == '/') {
				self->jp_pos = pos + 2;
				break;
			}
			self->jp_pos = pos + 1;
		}
		break;

	case JSON_ENCODING_UTF16LE:
	case JSON_ENCODING_UTF16BE: {
		uint16_t star = '*', slash = '/';
#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
		if (self->jp_encoding == JSON_ENCODING_UTF16LE) {
			star  = (uint16_t)HTOLE16('*');
			slash = (uint16_t)HTOLE16('/');
		}
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#if __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__
		if (self->jp_encoding == JSON_ENCODING_UTF16BE) {
			star  = (uint16_t)HTOBE16('*');
			slash = (uint16_t)HTOBE16('/');
		}
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
		for (;;) {
			uint16_t const *pos;
			pos = memchrw(self->jp_pos, star, (size_t)(self->jp_end - self->jp_pos) / 2);
			if (!pos || pos >= (uint16_t const *)(self->jp_end - 2))
				goto comment_syn;
			if (pos[1] == slash) {
				self->jp_pos = (char const *)(pos + 2);
				break;
			}
			self->jp_pos = (char const *)(pos + 1);
		}
	}	break;

	case JSON_ENCODING_UTF32LE:
	case JSON_ENCODING_UTF32BE: {
		uint32_t star = '*', slash = '/';
#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
		if (self->jp_encoding == JSON_ENCODING_UTF16LE) {
			star  = (uint32_t)HTOLE32('*');
			slash = (uint32_t)HTOLE32('/');
		}
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#if __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__
		if (self->jp_encoding == JSON_ENCODING_UTF16BE) {
			star  = (uint32_t)HTOBE32('*');
			slash = (uint32_t)HTOBE32('/');
		}
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
		for (;;) {
			uint32_t const *pos;
			pos = memchrl(self->jp_pos, star, (size_t)(self->jp_end - self->jp_pos) / 4);
			if (!pos || pos >= (uint32_t const *)(self->jp_end - 4))
				goto comment_syn;
			if (pos[1] == slash) {
				self->jp_pos = (char const *)(pos + 2);
				break;
			}
			self->jp_pos = (char const *)(pos + 1);
		}
	}	break;

	default: __builtin_unreachable();
	}
	return JSON_ERROR_OK;
comment_syn:
	self->jp_pos = cbody_start;
	json_ungetc(self); /* '*' */
	json_ungetc(self); /* '/' */
	return JSON_ERROR_SYNTAX;
}

/* Skip a comment after already having parsed `*' and `/', with
 * the parser currently pointing at the `*' character after the
 * comment body. */
PRIVATE NONNULL((1)) int
NOTHROW_NCX(CC json_unskip_comment)(struct json_parser *__restrict self) {
	char const *cbody_end = self->jp_pos;
	switch (__builtin_expect(self->jp_encoding, JSON_ENCODING_UTF8)) {

	case JSON_ENCODING_UTF8:
		for (;;) {
			char const *pos;
			pos = (char const *)memrchr(self->jp_start, '*',
			                            (size_t)(self->jp_pos - self->jp_start));
			if (!pos || pos <= self->jp_start)
				goto comment_syn;
			if (pos[-1] == '/') {
				self->jp_pos = pos - 1;
				break;
			}
			self->jp_pos = pos;
		}
		break;

	case JSON_ENCODING_UTF16LE:
	case JSON_ENCODING_UTF16BE: {
		uint16_t star = '*', slash = '/';
#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
		if (self->jp_encoding == JSON_ENCODING_UTF16LE) {
			star  = (uint16_t)HTOLE16('*');
			slash = (uint16_t)HTOLE16('/');
		}
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#if __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__
		if (self->jp_encoding == JSON_ENCODING_UTF16BE) {
			star  = (uint16_t)HTOBE16('*');
			slash = (uint16_t)HTOBE16('/');
		}
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
		for (;;) {
			uint16_t const *pos;
			pos = memrchrw(self->jp_start, star,
			               (size_t)(self->jp_pos - self->jp_start) / 2);
			if (!pos || pos <= (uint16_t const *)self->jp_start)
				goto comment_syn;
			if (pos[-1] == slash) {
				self->jp_pos = (char const *)(pos - 1);
				break;
			}
			self->jp_pos = (char const *)pos;
		}
	}	break;

	case JSON_ENCODING_UTF32LE:
	case JSON_ENCODING_UTF32BE: {
		uint32_t star = '*', slash = '/';
#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
		if (self->jp_encoding == JSON_ENCODING_UTF16LE) {
			star  = (uint32_t)HTOLE32('*');
			slash = (uint32_t)HTOLE32('/');
		}
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#if __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__
		if (self->jp_encoding == JSON_ENCODING_UTF16BE) {
			star  = (uint32_t)HTOBE32('*');
			slash = (uint32_t)HTOBE32('/');
		}
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
		for (;;) {
			uint32_t const *pos;
			pos = memrchrl(self->jp_start, star,
			               (size_t)(self->jp_pos - self->jp_start) / 4);
			if (!pos || pos <= (uint32_t const *)self->jp_start)
				goto comment_syn;
			if (pos[-1] == slash) {
				self->jp_pos = (char const *)(pos - 1);
				break;
			}
			self->jp_pos = (char const *)pos;
		}
	}	break;

	default: __builtin_unreachable();
	}
	return JSON_ERROR_OK;
comment_syn:
	self->jp_pos = cbody_end;
	json_getc(self); /* '*' */
	json_getc(self); /* '/' */
	return JSON_ERROR_SYNTAX;
}
#endif /* !CONFIG_NO_JSON_C_COMMENT_SUPPORT */


LOCAL NONNULL((1)) void
NOTHROW_NCX(CC json_skip_whitespace)(struct json_parser *__restrict self) {
	char const *prev;
	char32_t ch;
#ifndef CONFIG_NO_JSON_C_COMMENT_SUPPORT
again:
#endif /* !CONFIG_NO_JSON_C_COMMENT_SUPPORT */
	do {
		prev = self->jp_pos;
		ch   = json_getc(self);
	} while (unicode_isspace(ch));
#ifndef CONFIG_NO_JSON_C_COMMENT_SUPPORT
	if (ch == '/') {
		ch = json_getc(self);
		if (ch == '*') {
			if (json_skip_comment(self) == JSON_ERROR_OK)
				goto again;
		}
	}
#endif /* !CONFIG_NO_JSON_C_COMMENT_SUPPORT */
	self->jp_pos = prev;
}

LOCAL NONNULL((1)) void
NOTHROW_NCX(CC json_skip_whitespace_at)(struct json_parser *__restrict self,
                                        char32_t ch, char const *prev) {
	while (unicode_isspace(ch)) {
#ifndef CONFIG_NO_JSON_C_COMMENT_SUPPORT
again:
#endif /* !CONFIG_NO_JSON_C_COMMENT_SUPPORT */
		prev = self->jp_pos;
		ch   = json_getc(self);
	}
#ifndef CONFIG_NO_JSON_C_COMMENT_SUPPORT
	if (ch == '/') {
		ch = json_getc(self);
		if (ch == '*') {
			if (json_skip_comment(self) == JSON_ERROR_OK)
				goto again;
		}
	}
#endif /* !CONFIG_NO_JSON_C_COMMENT_SUPPORT */
	self->jp_pos = prev;
}

/* Initialize a json parser with the given piece of in-memory json.
 * NOTE: This function automatically detects  the encoding (one of  `JSON_ENCODING_*')
 *       of the given input, as  specified by the Json  specs, meaning you don't  have
 *       to concern yourself with the details on how to supply input to this function.
 * @param: start: Pointer to the start of json input data (usually points to a c-string)
 * @param: end:   Pointer to the first byte past the end of json input data (usually equal
 *                to `strend(start)', though note that the input string doesn't need to be
 *                NUL-terminated. - Only bytes `x' with `x >= start && x < end' will  ever
 *                be accessed) */
INTERN NONNULL((1, 2, 3)) void
NOTHROW_NCX(CC libjson_parser_init)(struct json_parser *__restrict self,
                                    void const *start, void const *end) {
	self->jp_start    = (char *)start;
	self->jp_pos      = (char *)start;
	self->jp_end      = (char *)end;
	self->jp_encoding = JSON_ENCODING_UTF8;
	if likely((char *)start + 4 < end) {
		/* Automatically determine input encoding:
		 *      00 00 00 xx   UTF-32BE
		 *      00 xx 00 xx   UTF-16BE
		 *      xx 00 00 00   UTF-32LE
		 *      xx 00 xx 00   UTF-16LE
		 *      xx xx xx xx   UTF-8 */
		union {
			uint32_t word;
			uint8_t bytes[4];
		} first_word;
		first_word.word = UNALIGNED_GET32((uint32_t const *)start);
		if unlikely(first_word.bytes[0] == 0) {
			self->jp_encoding = first_word.bytes[1] == 0
			                    ? JSON_ENCODING_UTF32BE
			                    : JSON_ENCODING_UTF16BE;
		} else if unlikely(first_word.bytes[1] == 0) {
			self->jp_encoding = first_word.bytes[2] == 0
			                    ? JSON_ENCODING_UTF32LE
			                    : JSON_ENCODING_UTF16LE;
		}
	}
	/* Skip leading whitespace. */
	json_skip_whitespace(self);
}

INTERN NONNULL((1, 2)) void
NOTHROW_NCX(CC json_skip_utf8string_trailing_nuls)(struct json_parser *__restrict self,
                                                   char const *__restrict new_pointer) {
	switch (self->jp_encoding) {

	case JSON_ENCODING_UTF8:
		new_pointer = (char const *)memxendb(new_pointer, 0, (size_t)(self->jp_end - new_pointer));
		break;

	case JSON_ENCODING_UTF16LE:
	case JSON_ENCODING_UTF16BE:
		if (((uintptr_t)new_pointer & 1) != ((uintptr_t)self->jp_start & 1))
			++new_pointer; /* Fix alignment */
		while (new_pointer < self->jp_end && UNALIGNED_GET16((uint16_t const *)new_pointer) == 0)
			new_pointer += 2;
		break;

	case JSON_ENCODING_UTF32LE:
	case JSON_ENCODING_UTF32BE:
		while (((uintptr_t)new_pointer & 3) != ((uintptr_t)self->jp_start & 3))
			++new_pointer; /* Fix alignment */
		while (new_pointer < self->jp_end && UNALIGNED_GET32((uint32_t const *)new_pointer) == 0)
			new_pointer += 4;
		break;

	default: __builtin_unreachable();
	}
	self->jp_pos = new_pointer;
}

INTERN NONNULL((1, 2)) void
NOTHROW_NCX(CC json_truncate_pos_for_alignment)(struct json_parser *__restrict self,
                                                char const *__restrict new_pointer) {
	switch (self->jp_encoding) {

	case JSON_ENCODING_UTF8:
		break;

	case JSON_ENCODING_UTF16LE:
	case JSON_ENCODING_UTF16BE:
		if (((uintptr_t)new_pointer & 1) != ((uintptr_t)self->jp_start & 1))
			--new_pointer; /* Fix alignment */
		break;

	case JSON_ENCODING_UTF32LE:
	case JSON_ENCODING_UTF32BE:
		while (((uintptr_t)new_pointer & 3) != ((uintptr_t)self->jp_start & 3))
			--new_pointer; /* Fix alignment */
		break;

	default: __builtin_unreachable();
	}
	self->jp_pos = new_pointer;
}

/* Yield to the current token and advance to the next one (*<ptr>++)
 * @return: JSON_PARSER_*:     The previously selected token (the parser now points at its end)
 * @return: JSON_ERROR_EOF:    The end of the input file has been reached.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_yield)(struct json_parser *__restrict self) {
	char const *prev;
	char32_t ch;
	int result;
again:
	assert(self->jp_pos >= self->jp_start);
	assert(self->jp_pos <= self->jp_end);
	ch = json_getc(self);
	switch (ch) {

	case 0:
		/* Check for end-of-file */
		if (self->jp_pos >= self->jp_end)
			return JSON_ERROR_EOF;
		/* transformed utf-8 string */
		json_skip_utf8string_trailing_nuls(self, strend(self->jp_pos));
		result = JSON_PARSER_STRING;
		break;

	case 1:
		prev = (char const *)memxendb(self->jp_pos, 1, (size_t)(self->jp_end - self->jp_pos));
		json_truncate_pos_for_alignment(self, prev);
		result = JSON_PARSER_STRING;
		break;

#ifndef CONFIG_NO_JSON_C_COMMENT_SUPPORT
	case '/':
		ch = json_getc(self);
		if (ch != '*')
			goto syn2;
		result = json_skip_comment(self);
		if (result == JSON_ERROR_OK)
			goto again;
		goto done;
#endif /* !CONFIG_NO_JSON_C_COMMENT_SUPPORT */

		/* Single-character tokens. */
	case '[': case ']':
	case '{': case '}':
	case ',': case ':':
		result = (int)ch;
		break;

	case '\"': /* String */
		result = JSON_PARSER_STRING;
		for (;;) {
			ch = json_getc(self);
			if (ch == '\"') {
				break;
			} else if (ch == '\\') {
				json_getc(self); /* Skip 1 character. */
			} else if (ch == 0 && self->jp_pos >= self->jp_end) {
				return JSON_ERROR_SYNTAX;
			}
		}
		break;

	case '-':
		ch = json_getc(self);
		if unlikely(!unicode_isdecimal(ch))
			goto syn2;
		if (ch == '0')
			goto do_decimal_0;
		goto do_decimal;

	case 't':
		if ((ch = json_getc(self)) != 'r')
			goto syn2;
		if ((ch = json_getc(self)) != 'u')
			goto syn3;
		if ((ch = json_getc(self)) != 'e')
			goto syn4;
		result = JSON_PARSER_TRUE;
		break;

	case 'f':
		if (json_getc(self) != 'a')
			goto syn2;
		if (json_getc(self) != 'l')
			goto syn3;
		if (json_getc(self) != 's')
			goto syn4;
		if (json_getc(self) != 'e')
			goto syn5;
		result = JSON_PARSER_FALSE;
		break;

	case 'n':
		if (json_getc(self) != 'u')
			goto syn2;
		if (json_getc(self) != 'l')
			goto syn3;
		if (json_getc(self) != 'l')
			goto syn4;
		result = JSON_PARSER_NULL;
		break;

	default:
		if (unicode_isdecimal(ch)) {
		case '0':
do_decimal_0:
			prev = self->jp_pos;
			ch   = json_getc(self);
			if (!isradixch(ch))
				goto do_digit_inner;
			ATTR_FALLTHROUGH
		case '1': case '2': case '3':
		case '4': case '5': case '6':
		case '7': case '8': case '9':
do_decimal:
			do {
				prev = self->jp_pos;
				ch = json_getc(self);
do_digit_inner:
				;
			} while (unicode_isdecimal(ch) ||
			         (ch >= 'a' && ch <= 'f') ||
			         (ch >= 'A' && ch <= 'F'));
			if (ch == '.') {
				/* Fractional part. */
				do {
					prev = self->jp_pos;
					ch = json_getc(self);
				} while (unicode_isdecimal(ch));
			}
			if (ch == 'e' || ch == 'E') {
				/* Exponent. */
				ch = json_getc(self);
				if (ch == '+' || ch == '-')
					ch = json_getc(self);
				do {
					prev = self->jp_pos;
					ch = json_getc(self);
				} while (unicode_isdecimal(ch));
			}
			self->jp_pos = prev;
			result = JSON_PARSER_NUMBER;
			break;
		} else if (unicode_isspace(ch)) {
		case 0x20: /* Space */
		case 0x09: /* Horizontal tab */
		case 0x0a: /* Line feed or New line */
		case 0x0d: /* Carriage return */
			goto again; /* Whitespace */
		}
		/* Anything else isn't allowed and indicates a syntax error. */
		goto syn1;
	}
	/* Skip trailing whitespace. */
	json_skip_whitespace(self);
#ifndef CONFIG_NO_JSON_C_COMMENT_SUPPORT
done:
#endif /* !CONFIG_NO_JSON_C_COMMENT_SUPPORT */
	return result;
syn5:
	json_ungetc(self);
syn4:
	json_ungetc(self);
syn3:
	json_ungetc(self);
syn2:
	json_ungetc(self);
syn1:
	json_ungetc(self);
	return JSON_ERROR_SYNTAX;
}

/* Yield to the previous token and return it (*--<ptr>)
 * @return: JSON_PARSER_*:     The now selected token (The parser is now located at the previous token)
 * @return: JSON_ERROR_EOF:    The start of the input file had already been reached.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_unyield)(struct json_parser *__restrict self) {
	char const *next;
	char32_t ch;
	int result;
again:
	assert(self->jp_pos >= self->jp_start);
	assert(self->jp_pos <= self->jp_end);
	ch = json_ungetc(self);
	switch (ch) {
		/* Single-character tokens. */
	case '[': case ']':
	case '{': case '}':
	case ',': case ':':
		result = (int)ch;
		break;

	case 0:
		/* Check for end-of-file */
		if (self->jp_pos <= self->jp_start)
			return JSON_ERROR_EOF;
		/* transformed utf-8 string */
		{
			uint8_t const *string_end;
			string_end = memrxchrb(self->jp_start, 0, (size_t)(self->jp_pos - self->jp_start));
			if unlikely(!string_end)
				goto syn1;
			string_end = memrchrb(self->jp_start, 0, (size_t)((char *)string_end - self->jp_start));
			if unlikely(!string_end)
				goto syn1;
			json_truncate_pos_for_alignment(self, (char *)string_end);
			result = JSON_PARSER_STRING;
		}
		break;

	case 1: {
		uint8_t const *string_end;
		string_end = memrxchrb(self->jp_start, 1, (size_t)(self->jp_pos - self->jp_start));
		if unlikely(!string_end)
		    goto syn1;
		json_truncate_pos_for_alignment(self, (char *)string_end);
		result = JSON_PARSER_STRING;
	}	break;

#ifndef CONFIG_NO_JSON_C_COMMENT_SUPPORT
	case '/':
		ch = json_ungetc(self);
		if (ch != '*')
			goto syn2;
		result = json_unskip_comment(self);
		if (result == JSON_ERROR_OK)
			goto again;
		goto done;
#endif /* !CONFIG_NO_JSON_C_COMMENT_SUPPORT */

	case '\"': /* String */
		for (;;) {
			ch = json_ungetc(self);
			if (ch == '\"') {
				bool is_escaped_quote = false;
				next = self->jp_pos;
				for (;;) {
					ch = json_ungetc(self);
					if (ch != '\\')
						break;
					is_escaped_quote = !is_escaped_quote;
				}
				if (!is_escaped_quote) {
					self->jp_pos = next;
					break;
				}
			} else if (ch == 0 && self->jp_pos <= self->jp_start) {
				return JSON_ERROR_SYNTAX;
			}
		}
		result = JSON_PARSER_STRING;
		break;

	case 'l':
		if (json_ungetc(self) != 'l')
			goto syn2;
		if (json_ungetc(self) != 'u')
			goto syn3;
		if (json_ungetc(self) != 'n')
			goto syn4;
		result = JSON_PARSER_NULL;
		break;

	case 'e':
		next = self->jp_pos;
		ch = json_ungetc(self);
		if (ch == 'u') {
			if (json_ungetc(self) != 'r')
				goto syn3;
			if (json_ungetc(self) != 't')
				goto syn4;
			result = JSON_PARSER_TRUE;
		} else if (ch == 's') {
			if (json_ungetc(self) != 'l')
				goto syn3;
			if (json_ungetc(self) != 'a')
				goto syn4;
			if (json_ungetc(self) != 'f')
				goto syn5;
			result = JSON_PARSER_FALSE;
		} else {
			/* 'e' can be trailing character in `0xe' */
			goto do_decimal;
		}
		break;

	default:
		if (unicode_isdecimal(ch)) {
		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
		case '8': case '9':
		case 'a': case 'b': case 'c': case 'd': /*case 'e':*/ case 'f':
		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
			do {
				next = self->jp_pos;
				ch = json_ungetc(self);
do_decimal:
				;
			} while (unicode_isdecimal(ch));
			if (ch == '+' || ch == '-') {
				do {
					next = self->jp_pos;
					ch = json_ungetc(self);
				} while (unicode_isdecimal(ch));
			}
			if (ch == 'e' || ch == 'E') {
				do {
					next = self->jp_pos;
					ch = json_ungetc(self);
				} while (unicode_isdecimal(ch));
			}
			if (ch == '.') {
				do {
					next = self->jp_pos;
					ch = json_ungetc(self);
				} while (unicode_isdecimal(ch));
			}
			if (isradixch(ch)) {
				next = self->jp_pos;
				ch = json_ungetc(self);
				if (ch == '0') {
					next = self->jp_pos;
					ch = json_ungetc(self);
				}
			}
			/* If  the number is  positive, move the  pointer to its start.
			 * Else, have the pointer be placed to point at the leading `-' */
			if (ch != '-')
				self->jp_pos = next;
			result = JSON_PARSER_NUMBER;
			break;
		} else if (unicode_isspace(ch)) {
		case 0x20: /* Space */
		case 0x09: /* Horizontal tab */
		case 0x0a: /* Line feed or New line */
		case 0x0d: /* Carriage return */
			goto again; /* Whitespace */
		}
		/* Anything else isn't allowed and indicates a syntax error. */
		goto syn1;
	}
#ifndef CONFIG_NO_JSON_C_COMMENT_SUPPORT
done:
#endif /* !CONFIG_NO_JSON_C_COMMENT_SUPPORT */
	return result;
syn5:
	json_getc(self);
syn4:
	json_getc(self);
syn3:
	json_getc(self);
syn2:
	json_getc(self);
syn1:
	json_getc(self);
	return JSON_ERROR_SYNTAX;
}

/* Rewind to the start of the current object/array
 * @return: JSON_PARSER_ARRAY:  The parser now points at the first token following the initial `['.
 * @return: JSON_PARSER_OBJECT: The parser now points at the first token following the initial `{'.
 * @return: JSON_ERROR_SYNTAX:  Syntax error. */
INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_rewind)(struct json_parser *__restrict self) {
	unsigned int recursion = 0;
	for (;;) {
		char const *temp = self->jp_pos;
		int tok = libjson_parser_unyield(self);
		if unlikely(tok <= 0)
			return JSON_ERROR_SYNTAX;
		if (tok == '{' || tok == '[') {
			if (!recursion) {
				self->jp_pos = temp;
				return tok;
			}
			--recursion;
		} else if (tok == '}' || tok == ']') {
			++recursion;
		}
	}
}


/* Advance the parser to the next object member or array index
 * @return: JSON_ERROR_OK:    The parser now points at the first token after the `,'
 *                            following   previous   object   memory/array    index.
 *                            Should that token be a `}' or `]',  `JSON_ERROR_NOOBJ'
 *                            will be returned instead.
 * @return: JSON_ERROR_NOOBJ: The end of the current object/array was reached.
 *                            The parser now points at the `}' or `]' following the object/array
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_next)(struct json_parser *__restrict self) {
	unsigned int recursion = 0;
	for (;;) {
		char const *temp = self->jp_pos;
		int tok = libjson_parser_yield(self);
		switch (tok) {
		case ',':
			if (recursion == 0) {
				/* Check for a trailing } or ] */
				temp = self->jp_pos;
				tok  = libjson_parser_yield(self);
				if (tok < 0)
					return JSON_ERROR_SYNTAX;
				self->jp_pos = temp;
				if (tok == '}' || tok == ']' || tok == 0)
					return JSON_ERROR_NOOBJ;
				return JSON_ERROR_OK;
			}
			break;
		case '{':
		case '[':
			++recursion;
			break;
		case '}':
		case ']':
			if (!recursion) {
				self->jp_pos = temp;
				return JSON_ERROR_NOOBJ;
			}
			--recursion;
			break;

		default:
			if unlikely(tok <= 0) {
				return JSON_ERROR_SYNTAX;
			}
			break;
		}
	}
}

/* Rewind the parser to the previous object member or array index
 * @return: JSON_ERROR_OK:    The parser now points at the start of the previous object member/array index.
 * @return: JSON_ERROR_NOOBJ: The start of the current object/array was reached.
 *                            In this case, the position of the parser depends on `leave_object':
 *                            leave_object  ==   true:  The   parser   now  points   at   either:
 *                               - The `{' or `[' token if the inner object/array was an array index
 *                               - The start of the member name `"foo":{...}' if the inner
 *                                 object/array was an object member
 *                            leave_object == false: The  parser  still points  at the  start of
 *                                                   the first member of the inner object/array.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_prev)(struct json_parser *__restrict self,
                                    bool leave_object) {
	char const *temp = self->jp_pos;
	int tok = libjson_parser_unyield(self);
	if (tok == ',') {
		/* There is a predecessor within the same object/array. */
		tok = libjson_parser_unyield(self);
		if (tok == '}' || tok == ']') {
			unsigned int recursion = 0;
			/* The previous component is an object/array */
			for (;;) {
				tok = libjson_parser_unyield(self);
				switch (tok) {
				case '{':
				case '[':
					if (!recursion)
						goto check_field_label;
					--recursion;
					break;
				case '}':
				case ']':
					++recursion;
					break;
				default:
					if unlikely(tok <= 0) {
						return JSON_ERROR_SYNTAX;
					}
				}
			}
		}
check_field_label:
		/* Check for object-field label. */
		temp = self->jp_pos;
		tok  = libjson_parser_unyield(self);
		if (tok == ':') {
			tok = libjson_parser_unyield(self);
			if (tok != JSON_PARSER_STRING)
				return JSON_ERROR_SYNTAX;
		} else {
			self->jp_pos = temp;
		}
		return JSON_ERROR_OK;
	} else if (tok == '{' || tok == '[') {
		/* Start of object has been reached. */
		if (!leave_object) {
			self->jp_pos = temp;
		} else {
			temp = self->jp_pos;
			tok  = libjson_parser_unyield(self);
			if (tok == ':') {
				tok = libjson_parser_unyield(self);
				if (tok != JSON_PARSER_STRING)
					return JSON_ERROR_SYNTAX;
			} else {
				self->jp_pos = temp;
			}
		}
		return JSON_ERROR_NOOBJ;
	} else if (!tok && !leave_object) {
		/* Start of input */
		self->jp_pos = self->jp_start;
		return JSON_ERROR_NOOBJ;
	}
	return JSON_ERROR_SYNTAX;
}

/* Advance the parser to the next object sibling
 * @return: JSON_ERROR_OK:    The parser now points at first member/index of the inner object/array.
 * @return: JSON_ERROR_NOOBJ: The parser didn't point at `{' or `[' (its position remains unchanged).
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
PRIVATE NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_enter_something)(struct json_parser *__restrict self,
                                               bool allow_object,
                                               bool allow_array) {
	char const *temp = self->jp_pos;
	int tok = libjson_parser_yield(self);
	if ((tok == '{' && allow_object) ||
	    (tok == '[' && allow_array))
		return JSON_ERROR_OK;
	if (tok < 0)
		return JSON_ERROR_SYNTAX;
	self->jp_pos = temp;
	return JSON_ERROR_NOOBJ;
}

INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_enter)(struct json_parser *__restrict self) {
	return libjson_parser_enter_something(self, true, true);
}

INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_enterobject)(struct json_parser *__restrict self) {
	return libjson_parser_enter_something(self, true, false);
}

INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_enterarray)(struct json_parser *__restrict self) {
	return libjson_parser_enter_something(self, false, true);
}


/* Skip the remainder of the  current object/array and parse  until after the following  `,'
 * If that token doesn't exist, or is followed by another closing token, stop parsing there.
 * @return: JSON_ERROR_OK:  The  parser  now  points at  the  first token  after  the `,'
 *                          following  the previous object. - If that `,' does not exist,
 *                          the parser exists at the `}' or `]' that is taking its place.
 * @return: JSON_ERROR_EOF: The end of the input file has been reached.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
PRIVATE NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_leave_something)(struct json_parser *__restrict self,
                                               bool allow_object,
                                               bool allow_array) {
	unsigned int recursion = 0;
	for (;;) {
		int tok = libjson_parser_yield(self);
		if (tok == '}' || tok == ']') {
			if (!recursion) {
				char const *prev;
				if (!allow_object || !allow_array) {
					if (allow_object) {
						if (tok != '}')
							return JSON_ERROR_SYNTAX;
					} else {
						if (tok != ']')
							return JSON_ERROR_SYNTAX;
					}
				}
				prev = self->jp_pos;
				tok = libjson_parser_yield(self);
				if (tok == ',')
					return JSON_ERROR_OK;
				if (tok == 0)
					return JSON_ERROR_EOF;
				self->jp_pos = prev;
				return JSON_ERROR_OK;
			}
			--recursion;
		} else if (tok == '{' || tok == '[') {
			++recursion;
		}
		if (tok <= 0) {
			if (tok < 0 || recursion != 0)
				return tok;
			return JSON_ERROR_EOF;
		}
	}
}

INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_leave)(struct json_parser *__restrict self) {
	return libjson_parser_leave_something(self, true, true);
}

INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_leaveobject)(struct json_parser *__restrict self) {
	return libjson_parser_leave_something(self, true, false);
}

INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_leavearray)(struct json_parser *__restrict self) {
	return libjson_parser_leave_something(self, false, true);
}


/* Returns the current parser state / token type.
 * @return: JSON_PARSER_*: The current parser state.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_state)(struct json_parser *__restrict self) {
	char const *temp = self->jp_pos;
	int result = libjson_parser_yield(self);
	self->jp_pos = temp;
	return result;
}

/* Search for the given key within the current object.
 * The given key is searched in both forward, and backward direction, starting
 * at the current parser location. - If  the key exists multiple times, it  is
 * undefined which of these locations will be referenced upon return.
 * @return: JSON_ERROR_OK:     The parser now points after the `:' following the matching key's name.
 * @return: JSON_ERROR_NOOBJ:  The given `key' wasn't found (The position of `self' remains unchanged)
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTERN NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_parser_findkey)(struct json_parser *__restrict self,
                                       /*utf-8*/ char const *__restrict key,
                                       size_t keylen) {
	char const *start;
	int result, tok;
again:
	start = self->jp_pos;
	for (;;) {
		/* Check if this is the requested field. */
		result = libjson_parser_eqstring(self, key, keylen);
		if (result == JSON_ERROR_NOOBJ) {
			/* Check if we were pointing at a comma. - If so, continue searching after it. */
			tok = libjson_parser_yield(self);
			if (tok == ',')
				goto again;
			if (tok == '}')
				break; /* End-of-object (fall-through to the rewind below to search everything prior) */
			self->jp_pos = start;
			return JSON_ERROR_SYNTAX;
		}
		if (result == JSON_ERROR_SYNTAX)
			return JSON_ERROR_SYNTAX;
		tok = libjson_parser_yield(self);
		if (tok != ':')
			return JSON_ERROR_SYNTAX;
		if (result == JSON_ERROR_OK)
			return JSON_ERROR_OK; /* Found it! (The parser now points at the field's value) */
		/* Advance to the next field. */
		result = libjson_parser_next(self);
		if (result != JSON_ERROR_OK) {
			if (result == JSON_ERROR_NOOBJ)
				break; /* End of object has been reached. */
			assert(result == JSON_ERROR_SYNTAX);
			return result; /* JSON_ERROR_SYNTAX */
		}
	}
	/* Move back to the start of the object, and search for the key from there. */
	self->jp_pos = start;
	result = libjson_parser_rewind(self);
	if (result != JSON_PARSER_OBJECT)
		return JSON_ERROR_SYNTAX;
	while (self->jp_pos < start) {
		result = libjson_parser_eqstring(self, key, keylen);
		if (result == JSON_ERROR_SYNTAX || result == JSON_ERROR_NOOBJ)
			return JSON_ERROR_SYNTAX;
		tok = libjson_parser_yield(self);
		if (tok != ':')
			return JSON_ERROR_SYNTAX;
		if (result == JSON_ERROR_OK)
			return JSON_ERROR_OK; /* Found it! (The parser now points at the field's value) */
		/* Advance to the next field. */
		result = libjson_parser_next(self);
		if (result != JSON_ERROR_OK) {
			if (result == JSON_ERROR_NOOBJ)
				break; /* End of object has been reached. */
			assert(result == JSON_ERROR_SYNTAX);
			return result; /* JSON_ERROR_SYNTAX */
		}
	}
	/* Failed to find the key... */
	self->jp_pos = start;
	return JSON_ERROR_NOOBJ;
}

/* Goto  the  `index'th'  array element  before  returning `JSON_ERROR_OK'
 * The parser is rewound to the start of the current array before skipping
 * exactly `index' elements, thus causing that element to end up selected.
 * NOTE: If  the intend is  to enumerate array elements,  it is more efficient
 *       to rewind to the start of the array with `json_parser_rewind()', then
 *       proceeding to use `json_parser_next()' to iterate elements.
 * @return: JSON_ERROR_OK:    The parser was now advanced  to the `index'th array  element.
 *                            In this case, the parser points at the start of that element.
 * @return: JSON_ERROR_NOOBJ: The end  of  the array  has  been  reached before,  or  when  `index'
 *                            elements had been skipped. (The position of `self' remains unchanged)
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_findindex)(struct json_parser *__restrict self,
                                         uintptr_t index) {
	char const *start = self->jp_pos;
	int result = libjson_parser_rewind(self);
	if unlikely(result != JSON_PARSER_ARRAY) {
		return JSON_ERROR_SYNTAX;
	}
	/* Advance to the given index. */
	for (; index != 0; --index) {
		result = libjson_parser_next(self);
		if unlikely(result != JSON_ERROR_OK) {
			if (result == JSON_ERROR_NOOBJ)
				self->jp_pos = start;
			return result; /* JSON_ERROR_NOOBJ or JSON_ERROR_SYNTAX */
		}
	}
	return JSON_ERROR_OK;
}


struct format_compare_data {
	/*utf-8*/ char const *str;
	size_t                len;
};

PRIVATE NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
format_compare_string(void *arg,
                      /*utf-8*/ char const *__restrict data,
                      size_t datalen) {
	struct format_compare_data *compare_data;
	compare_data = (struct format_compare_data *)arg;
	if (datalen > compare_data->len)
		return -1; /* Json string is too long */
	if (memcmp(compare_data->str, data, datalen) != 0)
		return -1; /* Json string isn't equal */
	/* Consume data that has already been compared. */
	compare_data->str += datalen;
	compare_data->len -= datalen;
	return 0;
}



/* Check if the current parser token (which should be a string) is equal to `str'
 * @return: JSON_ERROR_OK:     The  previous  token  is  was  a   string  that  was  equal  to   `str'
 *                             In this case the parser now points at the first token after the string.
 * @return: JSON_ERROR_NOTEQ:  The string isn't equal to `str'.
 *                             In this case the parser now points at the first token after the string.
 * @return: JSON_ERROR_NOOBJ:  The parser didn't point at a string. (The position of `self' remains unchanged)
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTERN NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_parser_eqstring)(struct json_parser *__restrict self,
                                        /*utf-8*/ char const *__restrict str,
                                        size_t len) {
	int error;
	ssize_t compare_result;
	struct format_compare_data compare_data;
	compare_data.str = str;
	compare_data.len = len;
	error = libjson_parser_printstring(self,
	                                   &format_compare_string,
	                                   &compare_data,
	                                   &compare_result);
	if ((error == JSON_ERROR_SYSERR) ||
	    (error == JSON_ERROR_OK && compare_data.len != 0))
		return JSON_ERROR_NOTEQ; /* Not equal */
	return error; /* OK, NOOBJ or SYNTAX */
}

/* Parse a Json string and print its contents to `printer'
 * @return: JSON_ERROR_OK:     Success. - The sum  of all calls to  `*printer' is stored in  `*pprinter_result'
 *                             In this case the parser points at the first token after an optional trailing `,'
 *                             NOTE: Should the token following the string be a `:', the parser will point at
 *                                   that location instead.
 * @return: JSON_ERROR_NOOBJ:  The  parser  didn't  point at  a  string token.
 *                             In this case the parser didn't change position.
 * @return: JSON_ERROR_SYSERR: An invocation of `printer' returned a negative value (stored in `*pprinter_result').
 *                             In this case  the position  of the parser  is revered  to the start  of the  string.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTERN NONNULL((1, 2, 4)) int
NOTHROW_NCX(CC libjson_parser_printstring)(struct json_parser *__restrict self,
                                           pformatprinter printer, void *arg,
                                           ssize_t *__restrict pprinter_result) {
	/*utf-8*/ char buf[128], *bufend;
	char const *start = self->jp_pos;
	char32_t ch = json_getc(self);
	ssize_t printer_result, temp;
	if (ch != '\"') {
		if (ch == 0) {
			/* Transformed utf-8 string */
			size_t len = strlen(self->jp_pos);
			printer_result = (*printer)(arg, self->jp_pos, len);
			json_skip_utf8string_trailing_nuls(self, self->jp_pos + len);
			*pprinter_result = printer_result;
			if unlikely(printer_result < 0)
				return JSON_ERROR_SYSERR;
			return JSON_ERROR_OK;
		} else if (ch == 1) {
			/* empty utf-8 string */
			start = (char *)memrxchrb(self->jp_pos, 1, (size_t)(self->jp_end - self->jp_pos));
			json_truncate_pos_for_alignment(self, (char *)start);
			*pprinter_result = 0;
			return JSON_ERROR_OK;
		}
		/* Not a string */
		self->jp_pos = start;
		return JSON_ERROR_NOOBJ;
	}
	bufend = buf;
	printer_result = 0;
	/* Parse the string! */
	for (;;) {
		ch = json_getc(self);
		switch (ch) {
		case '\"':
			goto done; /* String end. */
		case '\\':
			/* Escaped character. */
			ch = json_getc(self);
			switch (ch) {
			case '\\':
			case '\"':
			case '\'': /* NOTE: This is an extension! */
			case '/':
				/* ch = ch; */
				break;
			case 'b': ch = 0x08; break;
			case 'f': ch = 0x0c; break;
			case 'n': ch = 0x0a; break;
			case 'r': ch = 0x0d; break;
			case 't': ch = 0x09; break;
			case 'a': ch = '\a'; break; /* NOTE: This is an extension! */
			case 'e': ch = 0x1b; break; /* NOTE: This is an extension! */
			case 'v': ch = '\v'; break; /* NOTE: This is an extension! */

			case 'u':
			case 'U': /* NOTE: This is an extension! */
			{
				uint32_t c = 0;
				unsigned int i, n = ch == 'u' ? 4 : 8;
				for (i = 0; i < n; ++i) {
					ch = json_getc(self);
					if (ch >= '0' && ch <= '9')
						ch -= '0';
					else if (ch >= 'a' && ch <= 'f')
						ch = 10 + (ch - 'a');
					else if (ch >= 'A' && ch <= 'F')
						ch = 10 + (ch - 'A');
					else if (unicode_isdecimal(ch))
						ch = unicode_asdigit(ch);
					else {
						return JSON_ERROR_SYNTAX;
					}
				}
				ch = (char32_t)c;
			}	break;

			default:
				return JSON_ERROR_SYNTAX; /* Unsupported escape code. */
			}
			break;
		case 0:
			if (self->jp_pos >= self->jp_end)
				return JSON_ERROR_SYNTAX; /* Unexpected end-of-string. */
			break;
		default:
			break;
		}
		if (printer_result >= 0) {
			if unlikely(bufend >= COMPILER_ENDOF(buf) - UNICODE_UTF8_CURLEN) {
				/* Flush the buffer */
				temp = (*printer)(arg, buf, (size_t)(bufend - buf));
				if unlikely(temp < 0) {
					printer_result = temp;
					continue;
				}
				printer_result += temp;
				bufend = buf;
			}
			/* Append the loaded character to the buffer */
			bufend = unicode_writeutf8(bufend, ch);
		}
	}
done:
	/* Skip trailing whitespace. */
	json_skip_whitespace(self);
	/* Flush all unwritten data. */
	if (bufend != buf && likely(printer_result >= 0)) {
		temp = (*printer)(arg, buf, (size_t)(bufend - buf));
		if unlikely(temp < 0) {
			printer_result = temp;
		} else {
			printer_result += temp;
		}
	}
	*pprinter_result = printer_result;
	if unlikely(printer_result < 0)
		return JSON_ERROR_SYSERR;
	return JSON_ERROR_OK;
}



PRIVATE NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
json_inline_convert_string(void *arg,
                           /*utf-8*/ char const *__restrict data,
                           size_t datalen) {
	char *dst = *(char **)arg;
#if 1 /* libjson_parser_printstring() never flushes directly from the input source. */
	dst = (char *)mempcpy(dst, data, datalen);
#else
	dst = (char *)mempmove(dst, data, datalen);
#endif
	*(char **)arg = dst;
	return (ssize_t)datalen;
}


INTERN_CONST char const libjson_empty_string[1] = { 0 };


/* A somewhat hacky variant of `libjson_parser_printstring()', which replaces the source
 * string  in-line (thus  modifying the source  string) with its  utf-8 encoded variant.
 * This is done by re-encoding the string using a special extension syntax token that is
 * specifically designed to be able to hold a NUL-terminated utf-8 string token:
 * BEFORE:  \"foo\\nbar\"
 * AFTER:   \0foo\nbar\0\0
 * NOTE: If the source input uses a multi-byte format, the leading \0's width matches
 *       that format's width, while the remainder of the string always follows  UTF-8
 * NOTE: Another special encoding also exists for an empty string:
 * BEFORE:  \"\"
 * AFTER:   \1\1 -- Additional \1 characters may follow
 * @param: plength: When non-NULL, write the length of the returned string here.
 * @return: * :     A pointer to the start of the inlined utf-8 string
 * @return: NULL:   An error occurred; when `perror` is non-NULL, that error is stored there:
 *                   - JSON_ERROR_NOOBJ:  Parser didn't point at a string object.
 *                   - JSON_ERROR_SYNTAX: Syntax error */
INTERN WUNUSED NONNULL((1)) /*utf-8*/ char *
NOTHROW_NCX(CC libjson_parser_getstring)(struct json_parser *__restrict self,
                                         size_t *plength, int *perror) {
	char *dst, *dst_writer; int error;
	char const *start = self->jp_pos;
	char32_t ch = json_getc(self);
	ssize_t total_length;
	if (ch == 0) {
		size_t len;
		/* Already utf-8 encoded. */
		start = self->jp_pos;
		len = strlen(start);
		/* Advance to the end of the string. */
		json_skip_utf8string_trailing_nuls(self, start + len);
		if (plength)
			*plength = len;
		return (char *)start;
	}
	if (ch == 1) {
		start = (char *)memxendb(self->jp_pos, 1, (size_t)(self->jp_end - self->jp_pos));
		json_truncate_pos_for_alignment(self, (char *)start);
do_return_empty_string:
		return (char *)libjson_empty_string;
	}
	dst = (char *)self->jp_pos;
	self->jp_pos = start;
	/* Parse + inline-convert the string to utf-8 */
	dst_writer = dst;
	error = libjson_parser_printstring(self,
	                                   &json_inline_convert_string,
	                                   &dst_writer,
	                                   &total_length);
	if unlikely(error != JSON_ERROR_OK) {
		assert(error != JSON_ERROR_SYSERR);
		if (plength)
			*plength = 0;
		if (perror)
			*perror = error;
		return NULL;
	}
	/* Filter out nul characters prior to the end of the string. */
	total_length = strnlen(dst, total_length);
	if unlikely(!total_length) {
		/* Special case: empty string. */
		memset((char *)start, 1, (size_t)(self->jp_pos - start), sizeof(char));
		goto do_return_empty_string;
	}
	/* Normal, inlined utf-8 string -> Initialize leading and trailing markers. */
	assert(dst > start);
	assert(self->jp_pos > (dst + total_length));
	memset((char *)start, 0, (size_t)(dst - start), sizeof(char));
	memset((char *)dst + total_length, 0, (size_t)(self->jp_pos - (dst + total_length)), sizeof(char));
	return dst;
}




/* Decode a Json number and store its value in `*presult'
 * @return: JSON_ERROR_OK:     Success. - The number is stored in `*presult'
 *                             In this case the parser points at the first token after the number
 * @return: JSON_ERROR_NOOBJ:  The  parser  didn't  point at  a  number token.
 *                             In this case the parser didn't change position.
 * @return: JSON_ERROR_SYNTAX: Syntax error.
 * @return: JSON_ERROR_RANGE:  The encoded value does not fit into the given type.
 *                             NOTE:  Not  returned  by   `json_parser_getfloat()'!
 *                             In this case `*presult' is filled with the truncated
 *                             integer value, and the parser points at the first token after the number */
INTERN NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_parser_getnumber)(struct json_parser *__restrict self,
                                         intptr_t *__restrict presult) {
	char const *start = self->jp_pos;
	char32_t ch = json_getc(self);
	bool negative = false;
	int error = JSON_ERROR_OK;
	unsigned int radix = 10;
	intptr_t result, new_result;
	if (ch == '-') {
		ch = json_getc(self);
		negative = true;
	}
	if (!unicode_isdecimal(ch)) {
		if (negative)
			return JSON_ERROR_SYNTAX;
bad_integer:
		self->jp_pos = start;
		return JSON_ERROR_NOOBJ; /* Not an integer. */
	}
	result = 0;
	if (ch == '0') {
		char const *pos;
		pos = self->jp_pos;
		ch  = json_getc(self);
		if (ch == 'x' || ch == 'X') {
			radix = 16;
			ch    = json_getc(self);
		} else if (ch == 'b' || ch == 'B') {
			radix = 2;
			ch    = json_getc(self);
		} else {
			radix = 8;
		}
		if (!unicode_isdecimal(ch) &&
		    !(ch >= 'a' && ch <= 'f') &&
		    !(ch >= 'A' && ch <= 'F')) {
			if (radix == 8) {
				/* Special case: '0' */
				start = pos;
				goto done;
			}
			goto bad_integer;
		}
	}
	for (;;) {
		uint8_t digit;
again_parse_ch:
		if (ch >= '0' && ch <= '9') {
			digit = (uint8_t)(ch - '0');
		} else if (ch >= 'a' && ch <= 'f') {
			digit = 10 + (uint8_t)(ch - 'a');
		} else if (ch >= 'A' && ch <= 'F') {
			digit = 10 + (uint8_t)(ch - 'A');
		} else {
			digit = unicode_asdigit(ch);
		}
		if unlikely(digit > radix)
			return JSON_ERROR_SYNTAX;
		new_result = (result * radix) + digit;
		if (new_result < result) {
			result = new_result;
			/* Check  for special case: INTPTR_MIN, as well
			 * as the fact that `INTPTR_MIN == -INTPTR_MIN' */
			if (new_result == INTPTR_MIN && negative) {
				start = self->jp_pos;
				ch = json_getc(self);
				/* If this was the last digit, then the
				 * number  doesn't  actually  overflow! */
				if (!unicode_isdecimal(ch)) {
					if (radix < 16)
						break;
					if (!(ch >= 'a' && ch <= 'f') &&
					    !(ch >= 'A' && ch <= 'F'))
						break;
				}
				error = JSON_ERROR_RANGE;
				goto again_parse_ch;
			}
			error = JSON_ERROR_RANGE;
		}
		result = new_result;
		start  = self->jp_pos;
		ch     = json_getc(self);
		if (unicode_isdecimal(ch))
			continue;
		if (radix >= 16) {
			if (ch >= 'a' && ch <= 'f')
				continue;
			if (ch >= 'A' && ch <= 'F')
				continue;
		}
		break;
	}
	/* Skip trailing whitespace. */
done:
	json_skip_whitespace_at(self, ch, start);
	/* Store the generated integer.
	 * NOTE: The special case where `INTPTR_MIN == -INTPTR_MIN'
	 *       is already handled  above by  the overflow  check! */
	if (negative)
		result = -result;
	*presult = result;
	return error;
}

#if __SIZEOF_POINTER__ >= 8
DEFINE_INTERN_ALIAS(libjson_parser_getint64, libjson_parser_getnumber);
#else /* __SIZEOF_POINTER__ >= 8 */
INTERN NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_parser_getint64)(struct json_parser *__restrict self,
                                        int64_t *__restrict presult) {
	char const *start = self->jp_pos;
	char32_t ch = json_getc(self);
	bool negative = false;
	int error = JSON_ERROR_OK;
	unsigned int radix = 10;
	int64_t result, new_result;
	if (ch == '-') {
		ch = json_getc(self);
		negative = true;
	}
	if (!unicode_isdecimal(ch)) {
		if (negative)
			return JSON_ERROR_SYNTAX;
bad_integer:
		self->jp_pos = start;
		return JSON_ERROR_NOOBJ; /* Not an integer. */
	}
	result = 0;
	if (ch == '0') {
		char const *pos;
		pos = self->jp_pos;
		ch  = json_getc(self);
		if (ch == 'x' || ch == 'X') {
			radix = 16;
			ch    = json_getc(self);
		} else if (ch == 'b' || ch == 'B') {
			radix = 2;
			ch    = json_getc(self);
		} else {
			radix = 8;
		}
		if (!unicode_isdecimal(ch) &&
		    !(ch >= 'a' && ch <= 'f') &&
		    !(ch >= 'A' && ch <= 'F')) {
			if (radix == 8) {
				/* Special case: '0' */
				start = pos;
				goto done;
			}
			goto bad_integer;
		}
	}
	for (;;) {
		uint8_t digit;
again_parse_ch:
		if (ch >= '0' && ch <= '9') {
			digit = (uint8_t)(ch - '0');
		} else if (ch >= 'a' && ch <= 'f') {
			digit = 10 + (uint8_t)(ch - 'a');
		} else if (ch >= 'A' && ch <= 'F') {
			digit = 10 + (uint8_t)(ch - 'A');
		} else {
			digit = unicode_asdigit(ch);
		}
		if unlikely(digit > radix)
			return JSON_ERROR_SYNTAX;
		new_result = (result * radix) + digit;
		if (new_result < result) {
			result = new_result;
			/* Check for special case: INT64_MIN, as well
			 * as the fact that `INT64_MIN == -INT64_MIN' */
			if (new_result == INT64_MIN && negative) {
				start = self->jp_pos;
				ch = json_getc(self);
				/* If this was the last digit, then the
				 * number  doesn't  actually  overflow! */
				if (!unicode_isdecimal(ch)) {
					if (radix < 16)
						break;
					if (!(ch >= 'a' && ch <= 'f') &&
					    !(ch >= 'A' && ch <= 'F'))
						break;
				}
				error = JSON_ERROR_RANGE;
				goto again_parse_ch;
			}
			error = JSON_ERROR_RANGE;
		}
		result = new_result;
		start  = self->jp_pos;
		ch     = json_getc(self);
		if (unicode_isdecimal(ch))
			continue;
		if (radix >= 16) {
			if (ch >= 'a' && ch <= 'f')
				continue;
			if (ch >= 'A' && ch <= 'F')
				continue;
		}
		break;
	}
	/* Skip trailing whitespace. */
done:
	json_skip_whitespace_at(self, ch, start);
	/* Store the generated integer.
	 * NOTE: The special case where `INTPTR_MIN == -INTPTR_MIN'
	 *       is already handled  above by  the overflow  check! */
	if (negative)
		result = -result;
	*presult = result;
	return error;
}
#endif /* __SIZEOF_POINTER__ < 8 */
DEFINE_INTERN_ALIAS(libjson_parser_getuint64, libjson_parser_getint64);

#ifndef __NO_FPU
INTERN NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_parser_getfloat)(struct json_parser *__restrict self,
                                        double *__restrict presult) {
	char const *start = self->jp_pos;
	char32_t ch = json_getc(self);
	bool negative = false;
	intptr_t result_whole;
	double result, result_frac;
	if (ch == '-') {
		ch = json_getc(self);
		negative = true;
	}
	if (!unicode_isdecimal(ch)) {
		if (negative)
			return JSON_ERROR_SYNTAX;
		self->jp_pos = start;
		return JSON_ERROR_NOOBJ; /* Not an integer. */
	}
	result_whole = 0;
	do {
		result_whole *= 10;
		result_whole += unicode_asdigit(ch);
		start = self->jp_pos;
		ch = json_getc(self);
	} while (unicode_isdecimal(ch));
	result_frac = 0.0;
	if (ch == '.') {
		uintptr_t base = 10;
		ch = json_getc(self);
		if (!unicode_isdecimal(ch))
			return JSON_ERROR_SYNTAX;
		do {
			base *= 10;
			result_frac *= 10.0;
			result_frac += unicode_asdigit(ch);
			start = self->jp_pos;
			ch = json_getc(self);
		} while (unicode_isdecimal(ch));
		result_frac /= (double)base;
	}
	result = (double)result_whole + result_frac;
	if (ch == 'e' || ch == 'E') {
		bool exp_negative = false;
		uintptr_t exp = 0;
		ch = json_getc(self);
		if (ch == '+' || ch == '-') {
			exp_negative = ch == '-';
			ch = json_getc(self);
		}
		if (!unicode_isdecimal(ch))
			return JSON_ERROR_SYNTAX;
		do {
			exp *= 10;
			exp += unicode_asdigit(ch);
			start = self->jp_pos;
			ch = json_getc(self);
		} while (unicode_isdecimal(ch));
		/* TODO: Use the same trick for converting string->float
		 *       as is  also  being  used  by  `format_scanf()'!
		 *       It's much more precise, and doesn't require any
		 *       functions from <math.h>! */
#ifdef __USE_GNU
		exp = pow10(exp);
#else /* __USE_GNU */
		exp = pow(10.0, exp);
#endif /* !__USE_GNU */
		if (exp_negative) {
			result /= exp;
		} else {
			result *= exp;
		}
	}
	/* Skip trailing whitespace. */
	json_skip_whitespace_at(self, ch, start);
	/* Store the generated integer. */
	if (negative)
		result = -result;
	*presult = result;
	return JSON_ERROR_OK;
}
#endif /* !__NO_FPU */


/* Decode a Json boolean and store its value in `*presult'
 * @return: JSON_ERROR_OK:     Success. - The value is stored in `*presult'
 *                             In this case the parser points at the first token after an optional trailing `,'
 * @return: JSON_ERROR_NOOBJ:  The  parser didn't point at a true/false token.
 *                             In this case the parser didn't change position.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTERN NONNULL((1, 2)) int
NOTHROW_NCX(CC libjson_parser_getbool)(struct json_parser *__restrict self,
                                       bool *__restrict presult) {
	char const *initial = self->jp_pos;
	int tok = libjson_parser_yield(self);
	if (tok == JSON_PARSER_TRUE)
		*presult = true;
	else if (tok == JSON_PARSER_FALSE)
		*presult = false;
	else {
		if (tok < 0)
			return tok; /* JSON_ERROR_SYNTAX */
		self->jp_pos = initial;
		return JSON_ERROR_NOOBJ;
	}
	return JSON_ERROR_OK;
}

/* Decode a Json null-value
 * @return: JSON_ERROR_OK:     Success.
 *                             In this case the parser points at the first token after an optional trailing `,'
 * @return: JSON_ERROR_NOOBJ:  The  parser  didn't  point at  a  `null' token.
 *                             In this case the parser didn't change position.
 * @return: JSON_ERROR_SYNTAX: Syntax error. */
INTERN NONNULL((1)) int
NOTHROW_NCX(CC libjson_parser_getnull)(struct json_parser *__restrict self) {
	char const *initial = self->jp_pos;
	int tok = libjson_parser_yield(self);
	if (tok == JSON_PARSER_NULL)
		;
	else {
		if (tok < 0)
			return tok; /* JSON_ERROR_SYNTAX */
		self->jp_pos = initial;
		return JSON_ERROR_NOOBJ;
	}
	return JSON_ERROR_OK;
}



DEFINE_PUBLIC_ALIAS(json_parser_init, libjson_parser_init);
DEFINE_PUBLIC_ALIAS(json_parser_yield, libjson_parser_yield);
DEFINE_PUBLIC_ALIAS(json_parser_unyield, libjson_parser_unyield);
DEFINE_PUBLIC_ALIAS(json_parser_rewind, libjson_parser_rewind);
DEFINE_PUBLIC_ALIAS(json_parser_next, libjson_parser_next);
DEFINE_PUBLIC_ALIAS(json_parser_prev, libjson_parser_prev);
DEFINE_PUBLIC_ALIAS(json_parser_enter, libjson_parser_enter);
DEFINE_PUBLIC_ALIAS(json_parser_enterobject, libjson_parser_enterobject);
DEFINE_PUBLIC_ALIAS(json_parser_enterarray, libjson_parser_enterarray);
DEFINE_PUBLIC_ALIAS(json_parser_leave, libjson_parser_leave);
DEFINE_PUBLIC_ALIAS(json_parser_leaveobject, libjson_parser_leaveobject);
DEFINE_PUBLIC_ALIAS(json_parser_leavearray, libjson_parser_leavearray);
DEFINE_PUBLIC_ALIAS(json_parser_state, libjson_parser_state);
DEFINE_PUBLIC_ALIAS(json_parser_findkey, libjson_parser_findkey);
DEFINE_PUBLIC_ALIAS(json_parser_findindex, libjson_parser_findindex);
DEFINE_PUBLIC_ALIAS(json_parser_eqstring, libjson_parser_eqstring);
DEFINE_PUBLIC_ALIAS(json_parser_printstring, libjson_parser_printstring);
DEFINE_PUBLIC_ALIAS(json_parser_getstring, libjson_parser_getstring);
DEFINE_PUBLIC_ALIAS(json_parser_getnumber, libjson_parser_getnumber);
DEFINE_PUBLIC_ALIAS(json_parser_getint64, libjson_parser_getint64);
DEFINE_PUBLIC_ALIAS(json_parser_getuint64, libjson_parser_getuint64);
#ifndef __NO_FPU
DEFINE_PUBLIC_ALIAS(json_parser_getfloat, libjson_parser_getfloat);
#endif /* !__NO_FPU */
DEFINE_PUBLIC_ALIAS(json_parser_getbool, libjson_parser_getbool);
DEFINE_PUBLIC_ALIAS(json_parser_getnull, libjson_parser_getnull);

DECL_END

#endif /* !GUARD_LIBJSON_PARSER_C */
