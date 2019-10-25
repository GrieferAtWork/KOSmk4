/* HASH CRC-32:0x22ff8daa */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_FORMAT_PRINTER_C
#define GUARD_LIBC_AUTO_PARTS_WCHAR_FORMAT_PRINTER_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "parts.wchar.format-printer.h"
#include "wchar.h"
#include "string.h"
#include "unicode.h"
#include "wctype.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/format-printer.h>
#include <hybrid/__alloca.h>
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.format.format_wrepeat") ssize_t
NOTHROW_NCX(LIBCCALL libc_format_wrepeat)(pc32formatprinter printer,
                                          void *arg,
                                          char32_t ch,
                                          size_t num_repetitions) {
#line 97 "kos/src/libc/magic/format-printer.c"
#ifndef FORMAT_REPEAT_BUFSIZE
#define FORMAT_REPEAT_BUFSIZE 64
#endif /* !FORMAT_REPEAT_BUFSIZE */
	ssize_t result, temp;
#ifdef __hybrid_alloca
	char32_t *buffer;
	if __likely(num_repetitions <= FORMAT_REPEAT_BUFSIZE) {
		buffer = (char32_t *)__hybrid_alloca(num_repetitions);

		libc_wmemset(buffer, ch, num_repetitions);



		return (*printer)(arg, buffer, num_repetitions);
	}
	buffer = (char32_t *)__hybrid_alloca(FORMAT_REPEAT_BUFSIZE);
	memset(buffer, ch, FORMAT_REPEAT_BUFSIZE);
#else /* __hybrid_alloca */
	char32_t buffer[FORMAT_REPEAT_BUFSIZE];
	if __likely(num_repetitions <= FORMAT_REPEAT_BUFSIZE) {

		libc_wmemset(buffer, ch, num_repetitions);



		return (*printer)(arg, buffer, num_repetitions);
	}
	memset(buffer, ch, FORMAT_REPEAT_BUFSIZE);
#endif /* !__hybrid_alloca */
	result = (*printer)(arg, buffer, FORMAT_REPEAT_BUFSIZE);
	if __unlikely(result < 0)
		goto done;
	for (;;) {
		num_repetitions -= FORMAT_REPEAT_BUFSIZE;
		if (num_repetitions < FORMAT_REPEAT_BUFSIZE)
			break;
		temp = (*printer)(arg, buffer, FORMAT_REPEAT_BUFSIZE);
		if __unlikely(temp < 0)
			goto done;
		result += temp;
	}
	if (num_repetitions) {
		temp = (*printer)(arg, buffer, num_repetitions);
		if __unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
}
#include <bits/format-printer.h>
#include <hybrid/__alloca.h>
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.format.format_wrepeat") ssize_t
NOTHROW_NCX(LIBDCALL libd_format_wrepeat)(pc16formatprinter printer,
                                          void *arg,
                                          char16_t ch,
                                          size_t num_repetitions) {
#line 97 "kos/src/libc/magic/format-printer.c"
#ifndef FORMAT_REPEAT_BUFSIZE
#define FORMAT_REPEAT_BUFSIZE 64
#endif /* !FORMAT_REPEAT_BUFSIZE */
	ssize_t result, temp;
#ifdef __hybrid_alloca
	char16_t *buffer;
	if __likely(num_repetitions <= FORMAT_REPEAT_BUFSIZE) {
		buffer = (char16_t *)__hybrid_alloca(num_repetitions);

		libd_wmemset(buffer, ch, num_repetitions);



		return (*printer)(arg, buffer, num_repetitions);
	}
	buffer = (char16_t *)__hybrid_alloca(FORMAT_REPEAT_BUFSIZE);
	libc_memset(buffer, ch, FORMAT_REPEAT_BUFSIZE);
#else /* __hybrid_alloca */
	char16_t buffer[FORMAT_REPEAT_BUFSIZE];
	if __likely(num_repetitions <= FORMAT_REPEAT_BUFSIZE) {

		libd_wmemset(buffer, ch, num_repetitions);



		return (*printer)(arg, buffer, num_repetitions);
	}
	libc_memset(buffer, ch, FORMAT_REPEAT_BUFSIZE);
#endif /* !__hybrid_alloca */
	result = (*printer)(arg, buffer, FORMAT_REPEAT_BUFSIZE);
	if __unlikely(result < 0)
		goto done;
	for (;;) {
		num_repetitions -= FORMAT_REPEAT_BUFSIZE;
		if (num_repetitions < FORMAT_REPEAT_BUFSIZE)
			break;
		temp = (*printer)(arg, buffer, FORMAT_REPEAT_BUFSIZE);
		if __unlikely(temp < 0)
			goto done;
		result += temp;
	}
	if (num_repetitions) {
		temp = (*printer)(arg, buffer, num_repetitions);
		if __unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
}

#include <bits/format-printer.h>
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.format.format_wescape") ssize_t
NOTHROW_NCX(LIBCCALL libc_format_wescape)(pc32formatprinter printer,
                                          void *arg,
                                          /*utf-8*/ char32_t const *__restrict text,
                                          size_t textlen,
                                          unsigned int flags) {
#line 184 "kos/src/libc/magic/format-printer.c"
#ifndef FORMAT_ESCAPE_FNORMAL
#define FORMAT_ESCAPE_FNORMAL   0x0000 /* Normal quote flags. */
#define FORMAT_ESCAPE_FPRINTRAW 0x0001 /* Don't surround the quoted text with "..."; */
#define FORMAT_ESCAPE_FFORCEHEX 0x0002 /* Force hex encoding of all control characters without special strings (`"\n"', etc.). */
#define FORMAT_ESCAPE_FFORCEOCT 0x0004 /* Force octal encoding of all non-ascii characters. */
#define FORMAT_ESCAPE_FNOCTRL   0x0008 /* Disable special encoding strings such as `"\r"', `"\n"' or `"\e"' */
#define FORMAT_ESCAPE_FNOASCII  0x0010 /* Disable regular ascii-characters and print everything using special encodings. */
#define FORMAT_ESCAPE_FUPPERHEX 0x0020 /* Use uppercase characters for hex (e.g.: `"\xAB"'). */
#endif /* !FORMAT_ESCAPE_FNORMAL */
#define escape_tooct(c) ('0'+(char32_t)(char32_t)(c))
#ifndef DECIMALS_SELECTOR
#define LOCAL_DECIMALS_SELECTOR_DEFINED 1
#define DECIMALS_SELECTOR  decimals
	__PRIVATE char const decimals[2][16] = {
		{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' },
		{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' },
	};
#endif
	__PRIVATE char32_t const quote[1] = { '\"' };
	char32_t encoded_text[12]; size_t encoded_text_size;
	ssize_t result = 0, temp; char const *c_hex;
	char32_t const *textend = text + textlen;
	char32_t const *flush_start = text;
	c_hex = DECIMALS_SELECTOR[!(flags & FORMAT_ESCAPE_FUPPERHEX)];
	encoded_text[0] = '\\';
	if __likely(!(flags & FORMAT_ESCAPE_FPRINTRAW)) {
		temp = (*printer)(arg, quote, 1);
		if __unlikely(temp < 0)
		goto err;
		result += temp;
	}
	while (text < textend) {
		char32_t const *old_text = text;

#if 4 == 2
		uint32_t ch = libc_unicode_readutf16_n((char16_t const **)&text, textend);
#else
		uint32_t ch = (uint32_t)*text++;
#endif



		if __unlikely(ch < 32 || ch >= 127  || ch == '\'' ||
		              ch == '\"' || ch == '\\' ||
		             (flags & FORMAT_ESCAPE_FNOASCII)) {
			/* Flush unwritten direct-copy text. */
			if (flush_start < old_text) {
				temp = (*printer)(arg, flush_start, (size_t)(old_text - flush_start));
				if __unlikely(temp < 0)
					goto err;
				result += temp;
			}
			/* Character requires special encoding. */
			if (ch < 32) {
				/* Control character. */
				if (flags & FORMAT_ESCAPE_FNOCTRL) {
default_ctrl:
					if (flags & FORMAT_ESCAPE_FFORCEHEX)
						goto encode_hex;
encode_oct:
					if (text < textend) {
						char32_t const *new_text = text;

#if 4 == 2
						uint32_t next_ch = libc_unicode_readutf16_n((char16_t const **)&new_text, textend);
#else
						uint32_t next_ch = (uint32_t)*new_text++;
#endif



						if (next_ch >= '0' && next_ch <= '7')
							goto encode_hex;
					}
					if (ch <= 0x07) {
						encoded_text[1] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 2;
					} else if (ch <= 0x3f) {
						encoded_text[1] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[2] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 3;
					} else if (ch <= 0x1ff) {
						encoded_text[1] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[2] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[3] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 4;
					} else if (ch <= 0xfff) {
						encoded_text[1] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[2] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[3] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[4] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 5;
					} else if (ch <= 0x7fff) {
						encoded_text[1] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[2] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[3] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[4] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[5] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 6;
					} else if (ch <= 0x3ffff) {
						encoded_text[1] = escape_tooct((ch & 0x00038000) >> 15);
						encoded_text[2] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[3] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[4] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[5] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[6] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 7;
					} else if (ch <= 0x1fffff) {
						encoded_text[1] = escape_tooct((ch & 0x001c0000) >> 18);
						encoded_text[2] = escape_tooct((ch & 0x00038000) >> 15);
						encoded_text[3] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[4] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[5] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[6] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[7] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 8;
					} else if (ch <= 0xffffff) {
						encoded_text[1] = escape_tooct((ch & 0x00e00000) >> 21);
						encoded_text[2] = escape_tooct((ch & 0x001c0000) >> 18);
						encoded_text[3] = escape_tooct((ch & 0x00038000) >> 15);
						encoded_text[4] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[5] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[6] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[7] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[8] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 9;
					} else if (ch <= 0x7ffffff) {
						encoded_text[1] = escape_tooct((ch & 0x07000000) >> 24);
						encoded_text[2] = escape_tooct((ch & 0x00e00000) >> 21);
						encoded_text[3] = escape_tooct((ch & 0x001c0000) >> 18);
						encoded_text[4] = escape_tooct((ch & 0x00038000) >> 15);
						encoded_text[5] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[6] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[7] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[8] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[9] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 10;
					} else if (ch <= 0x3fffffff) {
						encoded_text[1] = escape_tooct((ch & 0x38000000) >> 27);
						encoded_text[2] = escape_tooct((ch & 0x07000000) >> 24);
						encoded_text[3] = escape_tooct((ch & 0x00e00000) >> 21);
						encoded_text[4] = escape_tooct((ch & 0x001c0000) >> 18);
						encoded_text[5] = escape_tooct((ch & 0x00038000) >> 15);
						encoded_text[6] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[7] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[8] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[9] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[10] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 11;
					} else {
						encoded_text[1] = escape_tooct((ch & 0xc0000000) >> 30);
						encoded_text[2] = escape_tooct((ch & 0x38000000) >> 27);
						encoded_text[3] = escape_tooct((ch & 0x07000000) >> 24);
						encoded_text[4] = escape_tooct((ch & 0x00e00000) >> 21);
						encoded_text[5] = escape_tooct((ch & 0x001c0000) >> 18);
						encoded_text[6] = escape_tooct((ch & 0x00038000) >> 15);
						encoded_text[7] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[8] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[9] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[10] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[11] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 12;
					}
					goto print_encoded;
				}
special_control:
				switch (ch) {
				case '\a':
					ch = 'a';
					break;
				case '\b':
					ch = 'b';
					break;
				case '\f':
					ch = 'f';
					break;
				case '\n':
					ch = 'n';
					break;
				case '\r':
					ch = 'r';
					break;
				case '\t':
					ch = 't';
					break;
				case '\v':
					ch = 'v';
					break;
				case '\033':
					ch = 'e';
					break;
				case '\\':
				case '\'':
				case '\"':
					break;
				default:
					goto default_ctrl;
				}
				encoded_text[1] = (char32_t)ch;
				encoded_text_size = 2;
				goto print_encoded;
			} else if ((ch == '\\' || ch == '\'' || ch == '\"') &&
			          !(flags & FORMAT_ESCAPE_FNOCTRL)) {
				goto special_control;
			} else {
				/* Non-ascii character. */
/*default_nonascii:*/
				if (flags & FORMAT_ESCAPE_FFORCEOCT)
					goto encode_oct;
encode_hex:
				if (text < textend) {
					char32_t const *new_text = text;

#if 4 == 2
					uint32_t next_ch = libc_unicode_readutf16_n((char16_t const **)&new_text, textend);
#else
					uint32_t next_ch = (uint32_t)*new_text++;
#endif



					if ((next_ch >= 'a' && next_ch <= 'f') ||
					    (next_ch >= 'A' && next_ch <= 'F') ||
					    (next_ch >= '0' && next_ch <= '9'))
						goto encode_uni;
				}
				if (ch <= 0xf) {
					encoded_text[1] = 'x';
					encoded_text[2] = c_hex[ch];
					encoded_text_size = 3;
				} else if (ch <= 0xff) {
					encoded_text[1] = 'x';
					encoded_text[2] = c_hex[(ch & 0x000000f0) >> 4];
					encoded_text[3] = c_hex[ch & 0x0000000f];
					encoded_text_size = 4;
				} else {
encode_uni:
					if (ch <= 0xffff) {
						encoded_text[1] = 'u';
						encoded_text[2] = c_hex[(ch & 0x0000f000) >> 12];
						encoded_text[3] = c_hex[(ch & 0x00000f00) >> 8];
						encoded_text[4] = c_hex[(ch & 0x000000f0) >> 4];
						encoded_text[5] = c_hex[ch & 0x0000000f];
						encoded_text_size = 6;
					} else {
						encoded_text[1] = 'U';
						encoded_text[2] = c_hex[(ch & 0xf0000000) >> 28];
						encoded_text[3] = c_hex[(ch & 0x0f000000) >> 24];
						encoded_text[4] = c_hex[(ch & 0x00f00000) >> 20];
						encoded_text[5] = c_hex[(ch & 0x000f0000) >> 16];
						encoded_text[6] = c_hex[(ch & 0x0000f000) >> 12];
						encoded_text[7] = c_hex[(ch & 0x00000f00) >> 8];
						encoded_text[8] = c_hex[(ch & 0x000000f0) >> 4];
						encoded_text[9] = c_hex[ch & 0x0000000f];
						encoded_text_size = 10;
					}
				}
print_encoded:
				temp = (*printer)(arg, encoded_text, encoded_text_size);
				if __unlikely(temp < 0)
				goto err;
				result += temp;
			}
			flush_start = text;
		}
	}
/*done:*/
	if (flush_start < text) {
		temp = (*printer)(arg, flush_start, (size_t)(text - flush_start));
		if __unlikely(temp < 0)
			goto err;
		result += temp;
	}
	if __likely(!(flags & FORMAT_ESCAPE_FPRINTRAW)) {
		temp = (*printer)(arg, quote, 1);
		if __unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
#ifdef LOCAL_DECIMALS_SELECTOR_DEFINED
#undef LOCAL_DECIMALS_SELECTOR_DEFINED
#undef DECIMALS_SELECTOR
#endif /* LOCAL_DECIMALS_SELECTOR_DEFINED */
#undef escape_tooct
}
#include <bits/format-printer.h>
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.format.format_wescape") ssize_t
NOTHROW_NCX(LIBDCALL libd_format_wescape)(pc16formatprinter printer,
                                          void *arg,
                                          /*utf-8*/ char16_t const *__restrict text,
                                          size_t textlen,
                                          unsigned int flags) {
#line 184 "kos/src/libc/magic/format-printer.c"
#ifndef FORMAT_ESCAPE_FNORMAL
#define FORMAT_ESCAPE_FNORMAL   0x0000 /* Normal quote flags. */
#define FORMAT_ESCAPE_FPRINTRAW 0x0001 /* Don't surround the quoted text with "..."; */
#define FORMAT_ESCAPE_FFORCEHEX 0x0002 /* Force hex encoding of all control characters without special strings (`"\n"', etc.). */
#define FORMAT_ESCAPE_FFORCEOCT 0x0004 /* Force octal encoding of all non-ascii characters. */
#define FORMAT_ESCAPE_FNOCTRL   0x0008 /* Disable special encoding strings such as `"\r"', `"\n"' or `"\e"' */
#define FORMAT_ESCAPE_FNOASCII  0x0010 /* Disable regular ascii-characters and print everything using special encodings. */
#define FORMAT_ESCAPE_FUPPERHEX 0x0020 /* Use uppercase characters for hex (e.g.: `"\xAB"'). */
#endif /* !FORMAT_ESCAPE_FNORMAL */
#define escape_tooct(c) ('0'+(char16_t)(char16_t)(c))
#ifndef DECIMALS_SELECTOR
#define LOCAL_DECIMALS_SELECTOR_DEFINED 1
#define DECIMALS_SELECTOR  decimals
	__PRIVATE char const decimals[2][16] = {
		{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' },
		{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' },
	};
#endif
	__PRIVATE char16_t const quote[1] = { '\"' };
	char16_t encoded_text[12]; size_t encoded_text_size;
	ssize_t result = 0, temp; char const *c_hex;
	char16_t const *textend = text + textlen;
	char16_t const *flush_start = text;
	c_hex = DECIMALS_SELECTOR[!(flags & FORMAT_ESCAPE_FUPPERHEX)];
	encoded_text[0] = '\\';
	if __likely(!(flags & FORMAT_ESCAPE_FPRINTRAW)) {
		temp = (*printer)(arg, quote, 1);
		if __unlikely(temp < 0)
		goto err;
		result += temp;
	}
	while (text < textend) {
		char16_t const *old_text = text;

#if 2 == 2
		uint32_t ch = libc_unicode_readutf16_n((char16_t const **)&text, textend);
#else
		uint32_t ch = (uint32_t)*text++;
#endif



		if __unlikely(ch < 32 || ch >= 127  || ch == '\'' ||
		              ch == '\"' || ch == '\\' ||
		             (flags & FORMAT_ESCAPE_FNOASCII)) {
			/* Flush unwritten direct-copy text. */
			if (flush_start < old_text) {
				temp = (*printer)(arg, flush_start, (size_t)(old_text - flush_start));
				if __unlikely(temp < 0)
					goto err;
				result += temp;
			}
			/* Character requires special encoding. */
			if (ch < 32) {
				/* Control character. */
				if (flags & FORMAT_ESCAPE_FNOCTRL) {
default_ctrl:
					if (flags & FORMAT_ESCAPE_FFORCEHEX)
						goto encode_hex;
encode_oct:
					if (text < textend) {
						char16_t const *new_text = text;

#if 2 == 2
						uint32_t next_ch = libc_unicode_readutf16_n((char16_t const **)&new_text, textend);
#else
						uint32_t next_ch = (uint32_t)*new_text++;
#endif



						if (next_ch >= '0' && next_ch <= '7')
							goto encode_hex;
					}
					if (ch <= 0x07) {
						encoded_text[1] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 2;
					} else if (ch <= 0x3f) {
						encoded_text[1] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[2] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 3;
					} else if (ch <= 0x1ff) {
						encoded_text[1] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[2] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[3] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 4;
					} else if (ch <= 0xfff) {
						encoded_text[1] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[2] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[3] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[4] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 5;
					} else if (ch <= 0x7fff) {
						encoded_text[1] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[2] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[3] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[4] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[5] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 6;
					} else if (ch <= 0x3ffff) {
						encoded_text[1] = escape_tooct((ch & 0x00038000) >> 15);
						encoded_text[2] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[3] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[4] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[5] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[6] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 7;
					} else if (ch <= 0x1fffff) {
						encoded_text[1] = escape_tooct((ch & 0x001c0000) >> 18);
						encoded_text[2] = escape_tooct((ch & 0x00038000) >> 15);
						encoded_text[3] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[4] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[5] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[6] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[7] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 8;
					} else if (ch <= 0xffffff) {
						encoded_text[1] = escape_tooct((ch & 0x00e00000) >> 21);
						encoded_text[2] = escape_tooct((ch & 0x001c0000) >> 18);
						encoded_text[3] = escape_tooct((ch & 0x00038000) >> 15);
						encoded_text[4] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[5] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[6] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[7] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[8] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 9;
					} else if (ch <= 0x7ffffff) {
						encoded_text[1] = escape_tooct((ch & 0x07000000) >> 24);
						encoded_text[2] = escape_tooct((ch & 0x00e00000) >> 21);
						encoded_text[3] = escape_tooct((ch & 0x001c0000) >> 18);
						encoded_text[4] = escape_tooct((ch & 0x00038000) >> 15);
						encoded_text[5] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[6] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[7] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[8] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[9] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 10;
					} else if (ch <= 0x3fffffff) {
						encoded_text[1] = escape_tooct((ch & 0x38000000) >> 27);
						encoded_text[2] = escape_tooct((ch & 0x07000000) >> 24);
						encoded_text[3] = escape_tooct((ch & 0x00e00000) >> 21);
						encoded_text[4] = escape_tooct((ch & 0x001c0000) >> 18);
						encoded_text[5] = escape_tooct((ch & 0x00038000) >> 15);
						encoded_text[6] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[7] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[8] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[9] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[10] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 11;
					} else {
						encoded_text[1] = escape_tooct((ch & 0xc0000000) >> 30);
						encoded_text[2] = escape_tooct((ch & 0x38000000) >> 27);
						encoded_text[3] = escape_tooct((ch & 0x07000000) >> 24);
						encoded_text[4] = escape_tooct((ch & 0x00e00000) >> 21);
						encoded_text[5] = escape_tooct((ch & 0x001c0000) >> 18);
						encoded_text[6] = escape_tooct((ch & 0x00038000) >> 15);
						encoded_text[7] = escape_tooct((ch & 0x00007000) >> 12);
						encoded_text[8] = escape_tooct((ch & 0x00000e00) >> 9);
						encoded_text[9] = escape_tooct((ch & 0x000000c0) >> 6);
						encoded_text[10] = escape_tooct((ch & 0x00000038) >> 3);
						encoded_text[11] = escape_tooct((ch & 0x00000007));
						encoded_text_size = 12;
					}
					goto print_encoded;
				}
special_control:
				switch (ch) {
				case '\a':
					ch = 'a';
					break;
				case '\b':
					ch = 'b';
					break;
				case '\f':
					ch = 'f';
					break;
				case '\n':
					ch = 'n';
					break;
				case '\r':
					ch = 'r';
					break;
				case '\t':
					ch = 't';
					break;
				case '\v':
					ch = 'v';
					break;
				case '\033':
					ch = 'e';
					break;
				case '\\':
				case '\'':
				case '\"':
					break;
				default:
					goto default_ctrl;
				}
				encoded_text[1] = (char16_t)ch;
				encoded_text_size = 2;
				goto print_encoded;
			} else if ((ch == '\\' || ch == '\'' || ch == '\"') &&
			          !(flags & FORMAT_ESCAPE_FNOCTRL)) {
				goto special_control;
			} else {
				/* Non-ascii character. */
/*default_nonascii:*/
				if (flags & FORMAT_ESCAPE_FFORCEOCT)
					goto encode_oct;
encode_hex:
				if (text < textend) {
					char16_t const *new_text = text;

#if 2 == 2
					uint32_t next_ch = libc_unicode_readutf16_n((char16_t const **)&new_text, textend);
#else
					uint32_t next_ch = (uint32_t)*new_text++;
#endif



					if ((next_ch >= 'a' && next_ch <= 'f') ||
					    (next_ch >= 'A' && next_ch <= 'F') ||
					    (next_ch >= '0' && next_ch <= '9'))
						goto encode_uni;
				}
				if (ch <= 0xf) {
					encoded_text[1] = 'x';
					encoded_text[2] = c_hex[ch];
					encoded_text_size = 3;
				} else if (ch <= 0xff) {
					encoded_text[1] = 'x';
					encoded_text[2] = c_hex[(ch & 0x000000f0) >> 4];
					encoded_text[3] = c_hex[ch & 0x0000000f];
					encoded_text_size = 4;
				} else {
encode_uni:
					if (ch <= 0xffff) {
						encoded_text[1] = 'u';
						encoded_text[2] = c_hex[(ch & 0x0000f000) >> 12];
						encoded_text[3] = c_hex[(ch & 0x00000f00) >> 8];
						encoded_text[4] = c_hex[(ch & 0x000000f0) >> 4];
						encoded_text[5] = c_hex[ch & 0x0000000f];
						encoded_text_size = 6;
					} else {
						encoded_text[1] = 'U';
						encoded_text[2] = c_hex[(ch & 0xf0000000) >> 28];
						encoded_text[3] = c_hex[(ch & 0x0f000000) >> 24];
						encoded_text[4] = c_hex[(ch & 0x00f00000) >> 20];
						encoded_text[5] = c_hex[(ch & 0x000f0000) >> 16];
						encoded_text[6] = c_hex[(ch & 0x0000f000) >> 12];
						encoded_text[7] = c_hex[(ch & 0x00000f00) >> 8];
						encoded_text[8] = c_hex[(ch & 0x000000f0) >> 4];
						encoded_text[9] = c_hex[ch & 0x0000000f];
						encoded_text_size = 10;
					}
				}
print_encoded:
				temp = (*printer)(arg, encoded_text, encoded_text_size);
				if __unlikely(temp < 0)
				goto err;
				result += temp;
			}
			flush_start = text;
		}
	}
/*done:*/
	if (flush_start < text) {
		temp = (*printer)(arg, flush_start, (size_t)(text - flush_start));
		if __unlikely(temp < 0)
			goto err;
		result += temp;
	}
	if __likely(!(flags & FORMAT_ESCAPE_FPRINTRAW)) {
		temp = (*printer)(arg, quote, 1);
		if __unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
#ifdef LOCAL_DECIMALS_SELECTOR_DEFINED
#undef LOCAL_DECIMALS_SELECTOR_DEFINED
#undef DECIMALS_SELECTOR
#endif /* LOCAL_DECIMALS_SELECTOR_DEFINED */
#undef escape_tooct
}

#include <bits/format-printer.h>
#include <hybrid/__alloca.h>

#include <hybrid/__unaligned.h>

#include <hybrid/byteorder.h>
/* Print a hex dump of the given data using the provided format printer
 * @param: PRINTER:  A function called for all quoted portions of the text
 * @param: DATA:     A pointer to the data that should be dumped
 * @param: SIZE:     The amount of bytes read starting at DATA
 * @param: LINESIZE: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: FLAGS:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: 0: The given data was successfully hex-dumped
 * @return: *: The first non-ZERO(0) return value of PRINTER */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.format.format_whexdump") ssize_t
NOTHROW_NCX(LIBCCALL libc_format_whexdump)(pc32formatprinter printer,
                                           void *arg,
                                           void const *__restrict data,
                                           size_t size,
                                           size_t linesize,
                                           unsigned int flags) {
#line 506 "kos/src/libc/magic/format-printer.c"
#ifndef FORMAT_HEXDUMP_FNORMAL
#define FORMAT_HEXDUMP_FNORMAL    0x0000 /* Normal hexdump flags. */
#define FORMAT_HEXDUMP_FHEXLOWER  0x0001 /* Print hex text of the dump in lowercase (does not affect address/offset). */
#define FORMAT_HEXDUMP_FNOADDRESS 0x0002 /* Don't include the absolute address at the start of every line. */
#define FORMAT_HEXDUMP_FOFFSETS   0x0004 /* Include offsets from the base address at the start of every line (after the address when also shown). */
#define FORMAT_HEXDUMP_FNOHEX     0x0008 /* Don't print the actual hex dump (hex data representation). */
#define FORMAT_HEXDUMP_FNOASCII   0x0010 /* Don't print ascii representation of printable characters at the end of lines. */
#define FORMAT_HEXDUMP_BYTES      0x0000 /* Dump data as bytes. */
#define FORMAT_HEXDUMP_WORDS      0x1000 /* Dump data as words (uint16_t). */
#define FORMAT_HEXDUMP_DWORDS     0x2000 /* Dump data as dwords (uint32_t). */
#define FORMAT_HEXDUMP_QWORDS     0x3000 /* Dump data as qwords (uint64_t). */
#define FORMAT_HEXDUMP_SIZEMASK   0x3000 /* Mask for the dump size. */
#endif /* !FORMAT_HEXDUMP_FNORMAL */
#ifndef DECIMALS_SELECTOR
#define LOCAL_DECIMALS_SELECTOR_DEFINED 1
#define DECIMALS_SELECTOR  decimals
	__PRIVATE char const decimals[2][16] = {
		{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' },
		{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' },
	};
#endif
	__PRIVATE char32_t const lf[1] = { '\n' };
	char const *dec;
	byte_t const *line_data;
	char32_t buffer[
		(1 + (sizeof(void *) * 2) + 1) < 17 ? 17 :
		(1 + (sizeof(void *) * 2) + 1)], *dst;
	ssize_t temp, result = 0;
	unsigned int i; uintptr_t value;
	unsigned int offset_digits = 0;
	if (!size) goto done;
	if (!linesize) linesize = 16;
	dec = DECIMALS_SELECTOR[!(flags & FORMAT_HEXDUMP_FHEXLOWER)];
	if (flags & FORMAT_HEXDUMP_FOFFSETS) {
		value = size;
		do ++offset_digits;
		while ((value >>= 4) != 0);
	}
	line_data = (byte_t const *)data;
	for (;;) {
		size_t line_len = linesize;
		if (line_len > size)
			line_len = size;
		if (!(flags & FORMAT_HEXDUMP_FNOADDRESS)) {
			value = (uintptr_t)line_data;
			dst = buffer + sizeof(void *) * 2;
			*dst = ' ';
			while (dst > buffer) {
				*--dst = dec[value & 0xf];
				value >>= 4;
			}
			temp = (*printer)(arg, buffer, (sizeof(void *) * 2) + 1);
			if __unlikely(temp < 0)
				goto err;
			result += temp;
		}
		if (flags & FORMAT_HEXDUMP_FOFFSETS) {
			dst = buffer + 1 + offset_digits;
			*dst = ' ';
			value = (line_data - (byte_t const *)data);
			while (dst > buffer + 1) {
				*--dst = dec[value & 0xf];
				value >>= 4;
			}
			buffer[0] = '+';
			temp = (*printer)(arg, buffer, 2 + offset_digits);
			if __unlikely(temp < 0)
				goto err;
			result += temp;
		}
		if (!(flags & FORMAT_HEXDUMP_FNOHEX)) {
			size_t i = 0;
			size_t tailspace_count;
			switch (flags & FORMAT_HEXDUMP_SIZEMASK) {
			default:
				tailspace_count = linesize * 3;
				break;
			case FORMAT_HEXDUMP_WORDS:
				tailspace_count = (linesize / 2) * 5 + (linesize % 2) * 3;
				buffer[4] = ' ';
				for (; i + 2 <= line_len; i += 2) {
					u16 w = __hybrid_unaligned_get16((u16 *)(line_data + i));
					dst = buffer + 4;
					while (dst > buffer) {
						*--dst = dec[w & 0xf];
						w >>= 4;
					}
					temp = (*printer)(arg, buffer, 5);
					if __unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 5;
				}
				break;
			case FORMAT_HEXDUMP_DWORDS:
				tailspace_count = (linesize / 4) * 9 + (linesize % 4) * 3;
				buffer[8] = ' ';
				for (; i + 4 <= line_len; i += 4) {
					u32 l = __hybrid_unaligned_get32((u32 *)(line_data + i));
					dst = buffer + 8;
					while (dst > buffer) {
						*--dst = dec[l & 0xf];
						l >>= 4;
					}
					temp = (*printer)(arg, buffer, 9);
					if __unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 9;
				}
				break;
			case FORMAT_HEXDUMP_QWORDS:
				tailspace_count = (linesize / 8) * 17 + (linesize % 8) * 3;
				buffer[16] = ' ';
				for (; i + 8 <= line_len; i += 8) {
#if __SIZEOF_POINTER__ >= 8
					u64 q = __hybrid_unaligned_get64((u64 *)(line_data + i));
					dst = buffer + 16;
					while (dst > buffer) {
						*--dst = dec[q & 0xf];
						q >>= 4;
					}
#else
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
					u32 b = __hybrid_unaligned_get32((u32 *)(line_data + i));
					u32 a = __hybrid_unaligned_get32((u32 *)(line_data + i + 4));
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
					u32 a = __hybrid_unaligned_get32((u32 *)(line_data + i));
					u32 b = __hybrid_unaligned_get32((u32 *)(line_data + i + 4));
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
					dst = buffer + 16;
					while (dst > buffer + 8) {
						*--dst = dec[b & 0xf];
						b >>= 4;
					}
					while (dst > buffer) {
						*--dst = dec[a & 0xf];
						a >>= 4;
					}
#endif
					temp = (*printer)(arg, buffer, 17);
					if __unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 17;
				}
				break;
			}
			buffer[2] = ' ';
			for (; i < line_len; ++i) {
				byte_t b = line_data[i];
				buffer[0] = dec[b >> 4];
				buffer[1] = dec[b & 0xf];
				temp = (*printer)(arg, buffer, 3);
				if __unlikely(temp < 0)
					goto err;
				result += temp;
				tailspace_count -= 3;
			}
			if (tailspace_count) {
				temp = libc_format_wrepeat(printer, arg, ' ', tailspace_count);
				if __unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
		if (!(flags & FORMAT_HEXDUMP_FNOASCII)) {
			for (i = 0; i < line_len; ++i) {
				byte_t b = line_data[i];
				if (!libc_iswprint(b))
					b = '.';
				temp = (*printer)(arg, (char32_t const *)&b, 1);
				if __unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
		if (line_len >= size)
			break;
		line_data += line_len;
		size      -= line_len;
		temp = (*printer)(arg, lf, 1);
		if __unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
#ifdef LOCAL_DECIMALS_SELECTOR_DEFINED
#undef LOCAL_DECIMALS_SELECTOR_DEFINED
#undef DECIMALS_SELECTOR
#endif /* LOCAL_DECIMALS_SELECTOR_DEFINED */
}
#include <bits/format-printer.h>
#include <hybrid/__alloca.h>

#include <hybrid/__unaligned.h>

#include <hybrid/byteorder.h>
/* Print a hex dump of the given data using the provided format printer
 * @param: PRINTER:  A function called for all quoted portions of the text
 * @param: DATA:     A pointer to the data that should be dumped
 * @param: SIZE:     The amount of bytes read starting at DATA
 * @param: LINESIZE: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: FLAGS:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: 0: The given data was successfully hex-dumped
 * @return: *: The first non-ZERO(0) return value of PRINTER */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.format.format_whexdump") ssize_t
NOTHROW_NCX(LIBDCALL libd_format_whexdump)(pc16formatprinter printer,
                                           void *arg,
                                           void const *__restrict data,
                                           size_t size,
                                           size_t linesize,
                                           unsigned int flags) {
#line 506 "kos/src/libc/magic/format-printer.c"
#ifndef FORMAT_HEXDUMP_FNORMAL
#define FORMAT_HEXDUMP_FNORMAL    0x0000 /* Normal hexdump flags. */
#define FORMAT_HEXDUMP_FHEXLOWER  0x0001 /* Print hex text of the dump in lowercase (does not affect address/offset). */
#define FORMAT_HEXDUMP_FNOADDRESS 0x0002 /* Don't include the absolute address at the start of every line. */
#define FORMAT_HEXDUMP_FOFFSETS   0x0004 /* Include offsets from the base address at the start of every line (after the address when also shown). */
#define FORMAT_HEXDUMP_FNOHEX     0x0008 /* Don't print the actual hex dump (hex data representation). */
#define FORMAT_HEXDUMP_FNOASCII   0x0010 /* Don't print ascii representation of printable characters at the end of lines. */
#define FORMAT_HEXDUMP_BYTES      0x0000 /* Dump data as bytes. */
#define FORMAT_HEXDUMP_WORDS      0x1000 /* Dump data as words (uint16_t). */
#define FORMAT_HEXDUMP_DWORDS     0x2000 /* Dump data as dwords (uint32_t). */
#define FORMAT_HEXDUMP_QWORDS     0x3000 /* Dump data as qwords (uint64_t). */
#define FORMAT_HEXDUMP_SIZEMASK   0x3000 /* Mask for the dump size. */
#endif /* !FORMAT_HEXDUMP_FNORMAL */
#ifndef DECIMALS_SELECTOR
#define LOCAL_DECIMALS_SELECTOR_DEFINED 1
#define DECIMALS_SELECTOR  decimals
	__PRIVATE char const decimals[2][16] = {
		{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' },
		{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' },
	};
#endif
	__PRIVATE char16_t const lf[1] = { '\n' };
	char const *dec;
	byte_t const *line_data;
	char16_t buffer[
		(1 + (sizeof(void *) * 2) + 1) < 17 ? 17 :
		(1 + (sizeof(void *) * 2) + 1)], *dst;
	ssize_t temp, result = 0;
	unsigned int i; uintptr_t value;
	unsigned int offset_digits = 0;
	if (!size) goto done;
	if (!linesize) linesize = 16;
	dec = DECIMALS_SELECTOR[!(flags & FORMAT_HEXDUMP_FHEXLOWER)];
	if (flags & FORMAT_HEXDUMP_FOFFSETS) {
		value = size;
		do ++offset_digits;
		while ((value >>= 4) != 0);
	}
	line_data = (byte_t const *)data;
	for (;;) {
		size_t line_len = linesize;
		if (line_len > size)
			line_len = size;
		if (!(flags & FORMAT_HEXDUMP_FNOADDRESS)) {
			value = (uintptr_t)line_data;
			dst = buffer + sizeof(void *) * 2;
			*dst = ' ';
			while (dst > buffer) {
				*--dst = dec[value & 0xf];
				value >>= 4;
			}
			temp = (*printer)(arg, buffer, (sizeof(void *) * 2) + 1);
			if __unlikely(temp < 0)
				goto err;
			result += temp;
		}
		if (flags & FORMAT_HEXDUMP_FOFFSETS) {
			dst = buffer + 1 + offset_digits;
			*dst = ' ';
			value = (line_data - (byte_t const *)data);
			while (dst > buffer + 1) {
				*--dst = dec[value & 0xf];
				value >>= 4;
			}
			buffer[0] = '+';
			temp = (*printer)(arg, buffer, 2 + offset_digits);
			if __unlikely(temp < 0)
				goto err;
			result += temp;
		}
		if (!(flags & FORMAT_HEXDUMP_FNOHEX)) {
			size_t i = 0;
			size_t tailspace_count;
			switch (flags & FORMAT_HEXDUMP_SIZEMASK) {
			default:
				tailspace_count = linesize * 3;
				break;
			case FORMAT_HEXDUMP_WORDS:
				tailspace_count = (linesize / 2) * 5 + (linesize % 2) * 3;
				buffer[4] = ' ';
				for (; i + 2 <= line_len; i += 2) {
					u16 w = __hybrid_unaligned_get16((u16 *)(line_data + i));
					dst = buffer + 4;
					while (dst > buffer) {
						*--dst = dec[w & 0xf];
						w >>= 4;
					}
					temp = (*printer)(arg, buffer, 5);
					if __unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 5;
				}
				break;
			case FORMAT_HEXDUMP_DWORDS:
				tailspace_count = (linesize / 4) * 9 + (linesize % 4) * 3;
				buffer[8] = ' ';
				for (; i + 4 <= line_len; i += 4) {
					u32 l = __hybrid_unaligned_get32((u32 *)(line_data + i));
					dst = buffer + 8;
					while (dst > buffer) {
						*--dst = dec[l & 0xf];
						l >>= 4;
					}
					temp = (*printer)(arg, buffer, 9);
					if __unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 9;
				}
				break;
			case FORMAT_HEXDUMP_QWORDS:
				tailspace_count = (linesize / 8) * 17 + (linesize % 8) * 3;
				buffer[16] = ' ';
				for (; i + 8 <= line_len; i += 8) {
#if __SIZEOF_POINTER__ >= 8
					u64 q = __hybrid_unaligned_get64((u64 *)(line_data + i));
					dst = buffer + 16;
					while (dst > buffer) {
						*--dst = dec[q & 0xf];
						q >>= 4;
					}
#else
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
					u32 b = __hybrid_unaligned_get32((u32 *)(line_data + i));
					u32 a = __hybrid_unaligned_get32((u32 *)(line_data + i + 4));
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
					u32 a = __hybrid_unaligned_get32((u32 *)(line_data + i));
					u32 b = __hybrid_unaligned_get32((u32 *)(line_data + i + 4));
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
					dst = buffer + 16;
					while (dst > buffer + 8) {
						*--dst = dec[b & 0xf];
						b >>= 4;
					}
					while (dst > buffer) {
						*--dst = dec[a & 0xf];
						a >>= 4;
					}
#endif
					temp = (*printer)(arg, buffer, 17);
					if __unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 17;
				}
				break;
			}
			buffer[2] = ' ';
			for (; i < line_len; ++i) {
				byte_t b = line_data[i];
				buffer[0] = dec[b >> 4];
				buffer[1] = dec[b & 0xf];
				temp = (*printer)(arg, buffer, 3);
				if __unlikely(temp < 0)
					goto err;
				result += temp;
				tailspace_count -= 3;
			}
			if (tailspace_count) {
				temp = libd_format_wrepeat(printer, arg, ' ', tailspace_count);
				if __unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
		if (!(flags & FORMAT_HEXDUMP_FNOASCII)) {
			for (i = 0; i < line_len; ++i) {
				byte_t b = line_data[i];
				if (!libc_iswprint(b))
					b = '.';
				temp = (*printer)(arg, (char16_t const *)&b, 1);
				if __unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
		if (line_len >= size)
			break;
		line_data += line_len;
		size      -= line_len;
		temp = (*printer)(arg, lf, 1);
		if __unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
#ifdef LOCAL_DECIMALS_SELECTOR_DEFINED
#undef LOCAL_DECIMALS_SELECTOR_DEFINED
#undef DECIMALS_SELECTOR
#endif /* LOCAL_DECIMALS_SELECTOR_DEFINED */
}


#include <bits/wformat-printer.h>
#include <bits/uformat-printer.h>




#include <libc/parts.uchar.string.h>



#include <hybrid/__assert.h>
#if !defined(CONFIG_USE_LIBDISASM) && !defined(CONFIG_NO_USE_LIBDISASM) && \
  ((defined(__KERNEL__) && defined(__KOS__)) || ((defined(CONFIG_HAVE_LIBDISASM_DISASSEMBLER_H) || \
    defined(HAVE_LIBDISASM_DISASSEMBLER_H) || __has_include(<libdisasm/disassembler.h>)) && \
    defined(__CRT_HAVE_dlopen) && defined(__CRT_HAVE_dlsym)))
#define CONFIG_USE_LIBDISASM 1
#endif
#if !defined(CONFIG_USE_LIBDEBUGINFO) && !defined(CONFIG_NO_USE_LIBDEBUGINFO) && \
  ((defined(__KERNEL__) && defined(__KOS__)) || ((defined(CONFIG_HAVE_LIBDEBUGINFO_ADDR2LINE_H) || \
    defined(HAVE_LIBDEBUGINFO_ADDR2LINE_H) || __has_include(<libdebuginfo/addr2line.h>)) && \
    defined(__CRT_HAVE_dlopen) && defined(__CRT_HAVE_dlsym) && defined(__CRT_HAVE_dlgetmodule) && defined(__CRT_HAVE_dlmodulebase)))
#define CONFIG_USE_LIBDEBUGINFO 1
#endif
#ifdef CONFIG_USE_LIBDISASM
#if !defined(__KERNEL__) || !defined(__KOS__)
#include <dlfcn.h>
#endif
#include <libdisasm/disassembler.h>
#endif
#ifdef CONFIG_USE_LIBDEBUGINFO
#if !defined(__KERNEL__) || !defined(__KOS__)
#include <dlfcn.h>
#include <libdebuginfo/addr2line.h>
#else
#include <kernel/addr2line.h>
#endif
#endif
/* Generic printf implementation
 * Taking a regular printf-style format string and arguments, these
 * functions will call the given `PRINTER' callback with various strings
 * that, when put together, result in the desired formated text.
 *  - `PRINTER' obviously is called with the text parts in their correct order
 *  - If `PRINTER' returns '< 0', the function returns immediately,
 *    yielding that same value. Otherwise, format_printf() returns
 *    the sum of all return values from `PRINTER'.
 *  - The strings passed to `PRINTER' may not necessarily be zero-terminated, and
 *    a second argument is passed that indicates the absolute length in characters.
 * Supported extensions:
 *  - `%q'-format mode: Semantics equivalent to `%s', this modifier escapes the string using
 *                        `format_wescape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
 *  - `%.*s'   Instead of reading an `int' and dealing with undefined behavior when negative, an `unsigned int' is read.
 *  - `%.?s'   Similar to `%.*s', but takes a `size_t' from the argument list instead of an `unsigned int', as well as define
 *             a fixed-length buffer size for string/quote formats (thus allowing you to print '\0' characters after quoting)
 *  - `%$s'    Same as `%.?s'
 *  - `%q'     Print an escaped string. (format_printf(..., "a%qb", "foo\nbar")) --> "a\"foo\\nbar\"b"
 *  - `%#q'    Same as %q, without quotes. (format_printf(..., "a%#qb", "foo\nbar")) --> "afoo\\nbarb"
 *  - `%Q'     Print an escaped character. (format_printf(..., "a%Qb", '\n')) --> "a\'\\n\'b"
 *  - `%#Q'    Same as %Q, without quotes. (format_printf(..., "a%#Qb", '\n')) --> "a\\nb"
 *  - `%I'     length modifier: Integral length equivalent to sizeof(size_t)/sizeof(uintptr_t).
 *  - `%I8'    length modifier: Integral length equivalent to sizeof(int8_t).
 *  - `%I16'   length modifier: Integral length equivalent to sizeof(int16_t).
 *  - `%I32'   length modifier: Integral length equivalent to sizeof(int32_t).
 *  - `%I64'   length modifier: Integral length equivalent to sizeof(int64_t).
 *  - `%[...]' Extended formating options, allowing for additional formating options:
 *             - `%$[hex]' / `%$[hex:lLoOpPaAhH]'
 *                 - Invoke `format_whexdump(..., va_arg(args, void *))'
 *                 - Integer-length (`%$I32[hex]') flags affect `FORMAT_HEXDUMP_(BYTES|WORDS|DWORDS|QWORDS)'
 *                 - The argument string affect flags (defaults to `FORMAT_HEXDUMP_FNORMAL')
 *                    - `FORMAT_HEXDUMP_FHEXLOWER':  yes:l, no:L
 *                    - `FORMAT_HEXDUMP_FOFFSETS':   yes:o, no:O
 *                    - `FORMAT_HEXDUMP_FNOADDRESS': yes:P, no:p
 *                    - `FORMAT_HEXDUMP_FNOASCII':   yes:A, no:a
 *                    - `FORMAT_HEXDUMP_FNOHEX':     yes:H, no:h
 *             - `%[gen]'
 *                 - Invoke a custom format printer function pointer passed through args
 *                   >> typedef ssize_t (*PGEN)(pwformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> DO((*g)(printer, arg));
 *             - `%[gen:c]'
 *                 - Same as `%[gen]', but insert an additional argument `T' that depends
 *                   on the integer size prefix (`%I32[gen:c]') and defaults to `void *'
 *                   >> typedef ssize_t (*PGEN)(T a, pwformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> T    a = va_arg(args, T);
 *                   >> DO((*g)(a, printer, arg));
 *             - `%[disasm]' / `%$[disasm]'
 *                 - Print the mnemonic and operands of a single native assembly
 *                   instruction read from `va_arg(args, void *)' (using `libdisasm')
 *                   s.a. `disasm_single()'
 *                 - When the second form (with a fixed buffer size) is used, do a full
 *                   disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *                   s.a. `disasm()'
 *             - `%[vinfo]' / `%[vinfo:<FORMAT=%f(%l,%c) : %n>]'
 *                 - Print addr2line information for a text address read from `va_arg(args, void *)'
 *                 - The given FORMAT string is a special printf-like format declaration
 *                   that accepts the following substitutions:
 *                   - `%%'   Print a single `%'-character (used for escaping `%')
 *                   - `%p'   Output the queried text address the same way `format_wprintf(..., "%q", addr)' would (as `sizeof(void *) * 2' uppercase hex characters)
 *                   - `%n'   Symbol name of the surrounding symbol (managed), or `???'   `di_debug_addr2line_t::al_name'
 *                   - `%N'   Raw name of the surrounding symbol, or `???'                `di_debug_addr2line_t::al_rawname'
 *                   - `%l'   Source line number (1-based; 0 if unknown)                  `di_debug_addr2line_t::al_srcline'
 *                   - `%c'   Source column number (1-based; 0 if unknown)                `di_debug_addr2line_t::al_srccol'
 *                   - `%f'   Source filename (with path prefix)                          `di_debug_addr2line_t::(al_cubase|al_srcpath|al_srcfile)'
 *                   - `%Rf'  Source filename (without path prefix)                       `di_debug_addr2line_t::al_srcfile'
 *                   - `%<'   Absolute starting address of the associated source location `di_debug_addr2line_t::al_linestart'
 *                   - `%>'   Absolute end address of the associated source location      `di_debug_addr2line_t::al_lineend'
 *                   - `%1>'  Absolute end address of the associated source location - 1  `di_debug_addr2line_t::al_lineend'
 *                   - `%S'   Absolute starting address of the surrounding symbol         `di_debug_addr2line_t::al_symstart'
 *                   - `%E'   Absolute end address of the surrounding symbol              `di_debug_addr2line_t::al_symend'
 *                   - `%1E'  Absolute end address of the surrounding symbol - 1          `di_debug_addr2line_t::al_symend'
 *                   - `%Dl'  Declaration line number (1-based; 0 if unknown)             `di_debug_addr2line_t::al_dclline'
 *                   - `%Dc'  Declaration column number (1-based; 0 if unknown)           `di_debug_addr2line_t::al_dclcol'
 *                   - `%Df'  Declaration filename (with path prefix)                     `di_debug_addr2line_t::(al_cubase|al_dclpath|al_dclfile)'
 *                   - `%RDf' Declaration filename (without path prefix)                  `di_debug_addr2line_t::al_dclfile'
 *                   - Any other character[-sequence] is forwarded as-is
 *             - `%[...]' Other sequences are resered for future usage
 * >>> Possible (and actual) uses:
 *  - printf:           Unbuffered output into any kind of stream/file.
 *  - sprintf/snprintf: Unsafe/Counted string formatting into a user-supplied buffer.
 *  - strdupf:          Output into dynamically allocated heap memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more... */
INTERN NONNULL((1, 3)) ATTR_LIBC_PRINTF(3, 0)
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.format.format_vwprintf") ssize_t
NOTHROW_NCX(LIBCCALL libc_format_vwprintf)(pc32formatprinter printer,
                                           void *arg,
                                           char32_t const *__restrict format,
                                           __builtin_va_list args) {
#line 840 "kos/src/libc/magic/format-printer.c"
#define __CHAR_TYPE                 char32_t
#define __CHAR_SIZE                 4
#define __FORMAT_REPEAT             libc_format_wrepeat
#define __FORMAT_ESCAPE             libc_format_wescape
#define __FORMAT_HEXDUMP            libc_format_whexdump

#if 4 == 2
#define __FORMAT_UNICODE_WRITEUTF8  libc_unicode_writeutf16
#else
#define __FORMAT_UNICODE_WRITEUTF8(dst, ch) ((dst)[0] = (ch), (dst) + 1)
#endif
#define __FORMAT_WIDTH              libc_format_wwidth




#define __FORMAT_PRINTER            printer
#define __FORMAT_ARG                arg
#define __FORMAT_FORMAT             format
#define __FORMAT_ARGS               args
#include <local/format-printf.h>
}

#include <bits/wformat-printer.h>
#include <bits/uformat-printer.h>




#include <libc/parts.uchar.string.h>



#include <hybrid/__assert.h>
#if !defined(CONFIG_USE_LIBDISASM) && !defined(CONFIG_NO_USE_LIBDISASM) && \
  ((defined(__KERNEL__) && defined(__KOS__)) || ((defined(CONFIG_HAVE_LIBDISASM_DISASSEMBLER_H) || \
    defined(HAVE_LIBDISASM_DISASSEMBLER_H) || __has_include(<libdisasm/disassembler.h>)) && \
    defined(__CRT_HAVE_dlopen) && defined(__CRT_HAVE_dlsym)))
#define CONFIG_USE_LIBDISASM 1
#endif
#if !defined(CONFIG_USE_LIBDEBUGINFO) && !defined(CONFIG_NO_USE_LIBDEBUGINFO) && \
  ((defined(__KERNEL__) && defined(__KOS__)) || ((defined(CONFIG_HAVE_LIBDEBUGINFO_ADDR2LINE_H) || \
    defined(HAVE_LIBDEBUGINFO_ADDR2LINE_H) || __has_include(<libdebuginfo/addr2line.h>)) && \
    defined(__CRT_HAVE_dlopen) && defined(__CRT_HAVE_dlsym) && defined(__CRT_HAVE_dlgetmodule) && defined(__CRT_HAVE_dlmodulebase)))
#define CONFIG_USE_LIBDEBUGINFO 1
#endif
#ifdef CONFIG_USE_LIBDISASM
#if !defined(__KERNEL__) || !defined(__KOS__)
#include <dlfcn.h>
#endif
#include <libdisasm/disassembler.h>
#endif
#ifdef CONFIG_USE_LIBDEBUGINFO
#if !defined(__KERNEL__) || !defined(__KOS__)
#include <dlfcn.h>
#include <libdebuginfo/addr2line.h>
#else
#include <kernel/addr2line.h>
#endif
#endif
/* Generic printf implementation
 * Taking a regular printf-style format string and arguments, these
 * functions will call the given `PRINTER' callback with various strings
 * that, when put together, result in the desired formated text.
 *  - `PRINTER' obviously is called with the text parts in their correct order
 *  - If `PRINTER' returns '< 0', the function returns immediately,
 *    yielding that same value. Otherwise, format_printf() returns
 *    the sum of all return values from `PRINTER'.
 *  - The strings passed to `PRINTER' may not necessarily be zero-terminated, and
 *    a second argument is passed that indicates the absolute length in characters.
 * Supported extensions:
 *  - `%q'-format mode: Semantics equivalent to `%s', this modifier escapes the string using
 *                        `format_wescape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
 *  - `%.*s'   Instead of reading an `int' and dealing with undefined behavior when negative, an `unsigned int' is read.
 *  - `%.?s'   Similar to `%.*s', but takes a `size_t' from the argument list instead of an `unsigned int', as well as define
 *             a fixed-length buffer size for string/quote formats (thus allowing you to print '\0' characters after quoting)
 *  - `%$s'    Same as `%.?s'
 *  - `%q'     Print an escaped string. (format_printf(..., "a%qb", "foo\nbar")) --> "a\"foo\\nbar\"b"
 *  - `%#q'    Same as %q, without quotes. (format_printf(..., "a%#qb", "foo\nbar")) --> "afoo\\nbarb"
 *  - `%Q'     Print an escaped character. (format_printf(..., "a%Qb", '\n')) --> "a\'\\n\'b"
 *  - `%#Q'    Same as %Q, without quotes. (format_printf(..., "a%#Qb", '\n')) --> "a\\nb"
 *  - `%I'     length modifier: Integral length equivalent to sizeof(size_t)/sizeof(uintptr_t).
 *  - `%I8'    length modifier: Integral length equivalent to sizeof(int8_t).
 *  - `%I16'   length modifier: Integral length equivalent to sizeof(int16_t).
 *  - `%I32'   length modifier: Integral length equivalent to sizeof(int32_t).
 *  - `%I64'   length modifier: Integral length equivalent to sizeof(int64_t).
 *  - `%[...]' Extended formating options, allowing for additional formating options:
 *             - `%$[hex]' / `%$[hex:lLoOpPaAhH]'
 *                 - Invoke `format_whexdump(..., va_arg(args, void *))'
 *                 - Integer-length (`%$I32[hex]') flags affect `FORMAT_HEXDUMP_(BYTES|WORDS|DWORDS|QWORDS)'
 *                 - The argument string affect flags (defaults to `FORMAT_HEXDUMP_FNORMAL')
 *                    - `FORMAT_HEXDUMP_FHEXLOWER':  yes:l, no:L
 *                    - `FORMAT_HEXDUMP_FOFFSETS':   yes:o, no:O
 *                    - `FORMAT_HEXDUMP_FNOADDRESS': yes:P, no:p
 *                    - `FORMAT_HEXDUMP_FNOASCII':   yes:A, no:a
 *                    - `FORMAT_HEXDUMP_FNOHEX':     yes:H, no:h
 *             - `%[gen]'
 *                 - Invoke a custom format printer function pointer passed through args
 *                   >> typedef ssize_t (*PGEN)(pwformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> DO((*g)(printer, arg));
 *             - `%[gen:c]'
 *                 - Same as `%[gen]', but insert an additional argument `T' that depends
 *                   on the integer size prefix (`%I32[gen:c]') and defaults to `void *'
 *                   >> typedef ssize_t (*PGEN)(T a, pwformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> T    a = va_arg(args, T);
 *                   >> DO((*g)(a, printer, arg));
 *             - `%[disasm]' / `%$[disasm]'
 *                 - Print the mnemonic and operands of a single native assembly
 *                   instruction read from `va_arg(args, void *)' (using `libdisasm')
 *                   s.a. `disasm_single()'
 *                 - When the second form (with a fixed buffer size) is used, do a full
 *                   disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *                   s.a. `disasm()'
 *             - `%[vinfo]' / `%[vinfo:<FORMAT=%f(%l,%c) : %n>]'
 *                 - Print addr2line information for a text address read from `va_arg(args, void *)'
 *                 - The given FORMAT string is a special printf-like format declaration
 *                   that accepts the following substitutions:
 *                   - `%%'   Print a single `%'-character (used for escaping `%')
 *                   - `%p'   Output the queried text address the same way `format_wprintf(..., "%q", addr)' would (as `sizeof(void *) * 2' uppercase hex characters)
 *                   - `%n'   Symbol name of the surrounding symbol (managed), or `???'   `di_debug_addr2line_t::al_name'
 *                   - `%N'   Raw name of the surrounding symbol, or `???'                `di_debug_addr2line_t::al_rawname'
 *                   - `%l'   Source line number (1-based; 0 if unknown)                  `di_debug_addr2line_t::al_srcline'
 *                   - `%c'   Source column number (1-based; 0 if unknown)                `di_debug_addr2line_t::al_srccol'
 *                   - `%f'   Source filename (with path prefix)                          `di_debug_addr2line_t::(al_cubase|al_srcpath|al_srcfile)'
 *                   - `%Rf'  Source filename (without path prefix)                       `di_debug_addr2line_t::al_srcfile'
 *                   - `%<'   Absolute starting address of the associated source location `di_debug_addr2line_t::al_linestart'
 *                   - `%>'   Absolute end address of the associated source location      `di_debug_addr2line_t::al_lineend'
 *                   - `%1>'  Absolute end address of the associated source location - 1  `di_debug_addr2line_t::al_lineend'
 *                   - `%S'   Absolute starting address of the surrounding symbol         `di_debug_addr2line_t::al_symstart'
 *                   - `%E'   Absolute end address of the surrounding symbol              `di_debug_addr2line_t::al_symend'
 *                   - `%1E'  Absolute end address of the surrounding symbol - 1          `di_debug_addr2line_t::al_symend'
 *                   - `%Dl'  Declaration line number (1-based; 0 if unknown)             `di_debug_addr2line_t::al_dclline'
 *                   - `%Dc'  Declaration column number (1-based; 0 if unknown)           `di_debug_addr2line_t::al_dclcol'
 *                   - `%Df'  Declaration filename (with path prefix)                     `di_debug_addr2line_t::(al_cubase|al_dclpath|al_dclfile)'
 *                   - `%RDf' Declaration filename (without path prefix)                  `di_debug_addr2line_t::al_dclfile'
 *                   - Any other character[-sequence] is forwarded as-is
 *             - `%[...]' Other sequences are resered for future usage
 * >>> Possible (and actual) uses:
 *  - printf:           Unbuffered output into any kind of stream/file.
 *  - sprintf/snprintf: Unsafe/Counted string formatting into a user-supplied buffer.
 *  - strdupf:          Output into dynamically allocated heap memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more... */
INTERN NONNULL((1, 3)) ATTR_LIBC_PRINTF(3, 0)
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.format.format_vwprintf") ssize_t
NOTHROW_NCX(LIBDCALL libd_format_vwprintf)(pc16formatprinter printer,
                                           void *arg,
                                           char16_t const *__restrict format,
                                           __builtin_va_list args) {
#line 840 "kos/src/libc/magic/format-printer.c"
#define __CHAR_TYPE                 char16_t
#define __CHAR_SIZE                 2
#define __FORMAT_REPEAT             libd_format_wrepeat
#define __FORMAT_ESCAPE             libd_format_wescape
#define __FORMAT_HEXDUMP            libd_format_whexdump

#if 2 == 2
#define __FORMAT_UNICODE_WRITEUTF8  libc_unicode_writeutf16
#else
#define __FORMAT_UNICODE_WRITEUTF8(dst, ch) ((dst)[0] = (ch), (dst) + 1)
#endif
#define __FORMAT_WIDTH              libd_format_wwidth




#define __FORMAT_PRINTER            printer
#define __FORMAT_ARG                arg
#define __FORMAT_FORMAT             format
#define __FORMAT_ARGS               args
#include <local/format-printf.h>
}

#include <bits/format-printer.h>
/* Generic printf implementation
 * Taking a regular printf-style format string and arguments, these
 * functions will call the given `PRINTER' callback with various strings
 * that, when put together, result in the desired formated text.
 *  - `PRINTER' obviously is called with the text parts in their correct order
 *  - If `PRINTER' returns '< 0', the function returns immediately,
 *    yielding that same value. Otherwise, format_printf() returns
 *    the sum of all return values from `PRINTER'.
 *  - The strings passed to `PRINTER' may not necessarily be zero-terminated, and
 *    a second argument is passed that indicates the absolute length in characters.
 * Supported extensions:
 *  - `%q'-format mode: Semantics equivalent to `%s', this modifier escapes the string using
 *                        `format_wescape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
 *  - `%.*s'   Instead of reading an `int' and dealing with undefined behavior when negative, an `unsigned int' is read.
 *  - `%.?s'   Similar to `%.*s', but takes a `size_t' from the argument list instead of an `unsigned int', as well as define
 *             a fixed-length buffer size for string/quote formats (thus allowing you to print '\0' characters after quoting)
 *  - `%$s'    Same as `%.?s'
 *  - `%q'     Print an escaped string. (format_printf(..., "a%qb", "foo\nbar")) --> "a\"foo\\nbar\"b"
 *  - `%#q'    Same as %q, without quotes. (format_printf(..., "a%#qb", "foo\nbar")) --> "afoo\\nbarb"
 *  - `%Q'     Print an escaped character. (format_printf(..., "a%Qb", '\n')) --> "a\'\\n\'b"
 *  - `%#Q'    Same as %Q, without quotes. (format_printf(..., "a%#Qb", '\n')) --> "a\\nb"
 *  - `%I'     length modifier: Integral length equivalent to sizeof(size_t)/sizeof(uintptr_t).
 *  - `%I8'    length modifier: Integral length equivalent to sizeof(int8_t).
 *  - `%I16'   length modifier: Integral length equivalent to sizeof(int16_t).
 *  - `%I32'   length modifier: Integral length equivalent to sizeof(int32_t).
 *  - `%I64'   length modifier: Integral length equivalent to sizeof(int64_t).
 *  - `%[...]' Extended formating options, allowing for additional formating options:
 *             - `%$[hex]' / `%$[hex:lLoOpPaAhH]'
 *                 - Invoke `format_whexdump(..., va_arg(args, void *))'
 *                 - Integer-length (`%$I32[hex]') flags affect `FORMAT_HEXDUMP_(BYTES|WORDS|DWORDS|QWORDS)'
 *                 - The argument string affect flags (defaults to `FORMAT_HEXDUMP_FNORMAL')
 *                    - `FORMAT_HEXDUMP_FHEXLOWER':  yes:l, no:L
 *                    - `FORMAT_HEXDUMP_FOFFSETS':   yes:o, no:O
 *                    - `FORMAT_HEXDUMP_FNOADDRESS': yes:P, no:p
 *                    - `FORMAT_HEXDUMP_FNOASCII':   yes:A, no:a
 *                    - `FORMAT_HEXDUMP_FNOHEX':     yes:H, no:h
 *             - `%[gen]'
 *                 - Invoke a custom format printer function pointer passed through args
 *                   >> typedef ssize_t (*PGEN)(pwformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> DO((*g)(printer, arg));
 *             - `%[gen:c]'
 *                 - Same as `%[gen]', but insert an additional argument `T' that depends
 *                   on the integer size prefix (`%I32[gen:c]') and defaults to `void *'
 *                   >> typedef ssize_t (*PGEN)(T a, pwformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> T    a = va_arg(args, T);
 *                   >> DO((*g)(a, printer, arg));
 *             - `%[disasm]' / `%$[disasm]'
 *                 - Print the mnemonic and operands of a single native assembly
 *                   instruction read from `va_arg(args, void *)' (using `libdisasm')
 *                   s.a. `disasm_single()'
 *                 - When the second form (with a fixed buffer size) is used, do a full
 *                   disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *                   s.a. `disasm()'
 *             - `%[vinfo]' / `%[vinfo:<FORMAT=%f(%l,%c) : %n>]'
 *                 - Print addr2line information for a text address read from `va_arg(args, void *)'
 *                 - The given FORMAT string is a special printf-like format declaration
 *                   that accepts the following substitutions:
 *                   - `%%'   Print a single `%'-character (used for escaping `%')
 *                   - `%p'   Output the queried text address the same way `format_wprintf(..., "%q", addr)' would (as `sizeof(void *) * 2' uppercase hex characters)
 *                   - `%n'   Symbol name of the surrounding symbol (managed), or `???'   `di_debug_addr2line_t::al_name'
 *                   - `%N'   Raw name of the surrounding symbol, or `???'                `di_debug_addr2line_t::al_rawname'
 *                   - `%l'   Source line number (1-based; 0 if unknown)                  `di_debug_addr2line_t::al_srcline'
 *                   - `%c'   Source column number (1-based; 0 if unknown)                `di_debug_addr2line_t::al_srccol'
 *                   - `%f'   Source filename (with path prefix)                          `di_debug_addr2line_t::(al_cubase|al_srcpath|al_srcfile)'
 *                   - `%Rf'  Source filename (without path prefix)                       `di_debug_addr2line_t::al_srcfile'
 *                   - `%<'   Absolute starting address of the associated source location `di_debug_addr2line_t::al_linestart'
 *                   - `%>'   Absolute end address of the associated source location      `di_debug_addr2line_t::al_lineend'
 *                   - `%1>'  Absolute end address of the associated source location - 1  `di_debug_addr2line_t::al_lineend'
 *                   - `%S'   Absolute starting address of the surrounding symbol         `di_debug_addr2line_t::al_symstart'
 *                   - `%E'   Absolute end address of the surrounding symbol              `di_debug_addr2line_t::al_symend'
 *                   - `%1E'  Absolute end address of the surrounding symbol - 1          `di_debug_addr2line_t::al_symend'
 *                   - `%Dl'  Declaration line number (1-based; 0 if unknown)             `di_debug_addr2line_t::al_dclline'
 *                   - `%Dc'  Declaration column number (1-based; 0 if unknown)           `di_debug_addr2line_t::al_dclcol'
 *                   - `%Df'  Declaration filename (with path prefix)                     `di_debug_addr2line_t::(al_cubase|al_dclpath|al_dclfile)'
 *                   - `%RDf' Declaration filename (without path prefix)                  `di_debug_addr2line_t::al_dclfile'
 *                   - Any other character[-sequence] is forwarded as-is
 *             - `%[...]' Other sequences are resered for future usage
 * >>> Possible (and actual) uses:
 *  - printf:           Unbuffered output into any kind of stream/file.
 *  - sprintf/snprintf: Unsafe/Counted string formatting into a user-supplied buffer.
 *  - strdupf:          Output into dynamically allocated heap memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more... */
INTERN NONNULL((1, 3)) ATTR_LIBC_PRINTF(3, 4)
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.format.format_wprintf") ssize_t
NOTHROW_NCX(VLIBCCALL libc_format_wprintf)(pc32formatprinter printer,
                                           void *arg,
                                           char32_t const *__restrict format,
                                           ...) {
#line 867 "kos/src/libc/magic/format-printer.c"
	ssize_t result;
	va_list args;
	va_start(args, format);
	result = libc_format_vwprintf(printer, arg, format, args);
	va_end(args);
	return result;
}
#include <bits/format-printer.h>
/* Generic printf implementation
 * Taking a regular printf-style format string and arguments, these
 * functions will call the given `PRINTER' callback with various strings
 * that, when put together, result in the desired formated text.
 *  - `PRINTER' obviously is called with the text parts in their correct order
 *  - If `PRINTER' returns '< 0', the function returns immediately,
 *    yielding that same value. Otherwise, format_printf() returns
 *    the sum of all return values from `PRINTER'.
 *  - The strings passed to `PRINTER' may not necessarily be zero-terminated, and
 *    a second argument is passed that indicates the absolute length in characters.
 * Supported extensions:
 *  - `%q'-format mode: Semantics equivalent to `%s', this modifier escapes the string using
 *                        `format_wescape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
 *  - `%.*s'   Instead of reading an `int' and dealing with undefined behavior when negative, an `unsigned int' is read.
 *  - `%.?s'   Similar to `%.*s', but takes a `size_t' from the argument list instead of an `unsigned int', as well as define
 *             a fixed-length buffer size for string/quote formats (thus allowing you to print '\0' characters after quoting)
 *  - `%$s'    Same as `%.?s'
 *  - `%q'     Print an escaped string. (format_printf(..., "a%qb", "foo\nbar")) --> "a\"foo\\nbar\"b"
 *  - `%#q'    Same as %q, without quotes. (format_printf(..., "a%#qb", "foo\nbar")) --> "afoo\\nbarb"
 *  - `%Q'     Print an escaped character. (format_printf(..., "a%Qb", '\n')) --> "a\'\\n\'b"
 *  - `%#Q'    Same as %Q, without quotes. (format_printf(..., "a%#Qb", '\n')) --> "a\\nb"
 *  - `%I'     length modifier: Integral length equivalent to sizeof(size_t)/sizeof(uintptr_t).
 *  - `%I8'    length modifier: Integral length equivalent to sizeof(int8_t).
 *  - `%I16'   length modifier: Integral length equivalent to sizeof(int16_t).
 *  - `%I32'   length modifier: Integral length equivalent to sizeof(int32_t).
 *  - `%I64'   length modifier: Integral length equivalent to sizeof(int64_t).
 *  - `%[...]' Extended formating options, allowing for additional formating options:
 *             - `%$[hex]' / `%$[hex:lLoOpPaAhH]'
 *                 - Invoke `format_whexdump(..., va_arg(args, void *))'
 *                 - Integer-length (`%$I32[hex]') flags affect `FORMAT_HEXDUMP_(BYTES|WORDS|DWORDS|QWORDS)'
 *                 - The argument string affect flags (defaults to `FORMAT_HEXDUMP_FNORMAL')
 *                    - `FORMAT_HEXDUMP_FHEXLOWER':  yes:l, no:L
 *                    - `FORMAT_HEXDUMP_FOFFSETS':   yes:o, no:O
 *                    - `FORMAT_HEXDUMP_FNOADDRESS': yes:P, no:p
 *                    - `FORMAT_HEXDUMP_FNOASCII':   yes:A, no:a
 *                    - `FORMAT_HEXDUMP_FNOHEX':     yes:H, no:h
 *             - `%[gen]'
 *                 - Invoke a custom format printer function pointer passed through args
 *                   >> typedef ssize_t (*PGEN)(pwformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> DO((*g)(printer, arg));
 *             - `%[gen:c]'
 *                 - Same as `%[gen]', but insert an additional argument `T' that depends
 *                   on the integer size prefix (`%I32[gen:c]') and defaults to `void *'
 *                   >> typedef ssize_t (*PGEN)(T a, pwformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> T    a = va_arg(args, T);
 *                   >> DO((*g)(a, printer, arg));
 *             - `%[disasm]' / `%$[disasm]'
 *                 - Print the mnemonic and operands of a single native assembly
 *                   instruction read from `va_arg(args, void *)' (using `libdisasm')
 *                   s.a. `disasm_single()'
 *                 - When the second form (with a fixed buffer size) is used, do a full
 *                   disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *                   s.a. `disasm()'
 *             - `%[vinfo]' / `%[vinfo:<FORMAT=%f(%l,%c) : %n>]'
 *                 - Print addr2line information for a text address read from `va_arg(args, void *)'
 *                 - The given FORMAT string is a special printf-like format declaration
 *                   that accepts the following substitutions:
 *                   - `%%'   Print a single `%'-character (used for escaping `%')
 *                   - `%p'   Output the queried text address the same way `format_wprintf(..., "%q", addr)' would (as `sizeof(void *) * 2' uppercase hex characters)
 *                   - `%n'   Symbol name of the surrounding symbol (managed), or `???'   `di_debug_addr2line_t::al_name'
 *                   - `%N'   Raw name of the surrounding symbol, or `???'                `di_debug_addr2line_t::al_rawname'
 *                   - `%l'   Source line number (1-based; 0 if unknown)                  `di_debug_addr2line_t::al_srcline'
 *                   - `%c'   Source column number (1-based; 0 if unknown)                `di_debug_addr2line_t::al_srccol'
 *                   - `%f'   Source filename (with path prefix)                          `di_debug_addr2line_t::(al_cubase|al_srcpath|al_srcfile)'
 *                   - `%Rf'  Source filename (without path prefix)                       `di_debug_addr2line_t::al_srcfile'
 *                   - `%<'   Absolute starting address of the associated source location `di_debug_addr2line_t::al_linestart'
 *                   - `%>'   Absolute end address of the associated source location      `di_debug_addr2line_t::al_lineend'
 *                   - `%1>'  Absolute end address of the associated source location - 1  `di_debug_addr2line_t::al_lineend'
 *                   - `%S'   Absolute starting address of the surrounding symbol         `di_debug_addr2line_t::al_symstart'
 *                   - `%E'   Absolute end address of the surrounding symbol              `di_debug_addr2line_t::al_symend'
 *                   - `%1E'  Absolute end address of the surrounding symbol - 1          `di_debug_addr2line_t::al_symend'
 *                   - `%Dl'  Declaration line number (1-based; 0 if unknown)             `di_debug_addr2line_t::al_dclline'
 *                   - `%Dc'  Declaration column number (1-based; 0 if unknown)           `di_debug_addr2line_t::al_dclcol'
 *                   - `%Df'  Declaration filename (with path prefix)                     `di_debug_addr2line_t::(al_cubase|al_dclpath|al_dclfile)'
 *                   - `%RDf' Declaration filename (without path prefix)                  `di_debug_addr2line_t::al_dclfile'
 *                   - Any other character[-sequence] is forwarded as-is
 *             - `%[...]' Other sequences are resered for future usage
 * >>> Possible (and actual) uses:
 *  - printf:           Unbuffered output into any kind of stream/file.
 *  - sprintf/snprintf: Unsafe/Counted string formatting into a user-supplied buffer.
 *  - strdupf:          Output into dynamically allocated heap memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more... */
INTERN NONNULL((1, 3)) ATTR_LIBC_PRINTF(3, 4)
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.format.format_wprintf") ssize_t
NOTHROW_NCX(VLIBDCALL libd_format_wprintf)(pc16formatprinter printer,
                                           void *arg,
                                           char16_t const *__restrict format,
                                           ...) {
#line 867 "kos/src/libc/magic/format-printer.c"
	ssize_t result;
	va_list args;
	va_start(args, format);
	result = libd_format_vwprintf(printer, arg, format, args);
	va_end(args);
	return result;
}

/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.format.format_wsprintf_printer") ssize_t
NOTHROW_NCX(LIBCCALL libc_format_wsprintf_printer)(/*wchar_t ***/void *arg,
                                                   char32_t const *__restrict data,
                                                   size_t datalen) {
#line 941 "kos/src/libc/magic/format-printer.c"

	*(char32_t **)arg = (char32_t *)libc_wmempcpy(*(char32_t **)arg, data, datalen);



	return (ssize_t)datalen;
}
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.format.format_wsprintf_printer") ssize_t
NOTHROW_NCX(LIBDCALL libd_format_wsprintf_printer)(/*wchar_t ***/void *arg,
                                                   char16_t const *__restrict data,
                                                   size_t datalen) {
#line 941 "kos/src/libc/magic/format-printer.c"

	*(char16_t **)arg = (char16_t *)libd_wmempcpy(*(char16_t **)arg, data, datalen);



	return (ssize_t)datalen;
}

#include <hybrid/typecore.h>
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `ORIG_BUFSIZE - ARG->sd_bufsiz'
 * NOTE: The number of required characters is `ARG->sd_buffer - ORIG_BUF', or alternatively the sum of return values of all calls to `format_snprintf_printer()' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.format.format_wsnprintf_printer") ssize_t
NOTHROW_NCX(LIBCCALL libc_format_wsnprintf_printer)(/*struct format_wsnprintf_data**/void *arg,
                                                    char32_t const *__restrict data,
                                                    size_t datalen) {
#line 973 "kos/src/libc/magic/format-printer.c"
	struct format_snprintf_data_ {
		char32_t         *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
	};
	struct format_snprintf_data_ *ctrl;
	size_t result = datalen;
	ctrl = (struct format_snprintf_data_ *)arg;
	if (result > ctrl->sd_bufsiz)
		result = ctrl->sd_bufsiz;

	libc_wmemcpy(ctrl->sd_buffer, data, result);



	ctrl->sd_buffer += datalen;
	ctrl->sd_bufsiz -= result;
	return (ssize_t)datalen;
}
#include <hybrid/typecore.h>
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `ORIG_BUFSIZE - ARG->sd_bufsiz'
 * NOTE: The number of required characters is `ARG->sd_buffer - ORIG_BUF', or alternatively the sum of return values of all calls to `format_snprintf_printer()' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.format.format_wsnprintf_printer") ssize_t
NOTHROW_NCX(LIBDCALL libd_format_wsnprintf_printer)(/*struct format_wsnprintf_data**/void *arg,
                                                    char16_t const *__restrict data,
                                                    size_t datalen) {
#line 973 "kos/src/libc/magic/format-printer.c"
	struct format_snprintf_data_ {
		char16_t         *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
	};
	struct format_snprintf_data_ *ctrl;
	size_t result = datalen;
	ctrl = (struct format_snprintf_data_ *)arg;
	if (result > ctrl->sd_bufsiz)
		result = ctrl->sd_bufsiz;

	libd_wmemcpy(ctrl->sd_buffer, data, result);



	ctrl->sd_buffer += datalen;
	ctrl->sd_bufsiz -= result;
	return (ssize_t)datalen;
}

/* Returns the width (number of characters; not bytes) of the given unicode string */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.format.format_wwidth") ssize_t
NOTHROW_NCX(LIBCCALL libc_format_wwidth)(void *arg,
                                         char32_t const *__restrict data,
                                         size_t datalen) {
#line 123 "kos/src/libc/magic/parts.wchar.format-printer.c"
#if 4 == 2
	size_t result = 0;
	char32_t const *iter, *end;
	(void)arg;
	end = (iter = data) + datalen;
	while (iter < end) {
		char32_t ch;
		ch = *iter++;
		if (ch >= 0xd800 && ch <= 0xd800 && iter < end) {
			ch = *iter;
			if (ch >= 0xdc00 && ch <= 0xdfff)
				++iter;
		}
		++result;
	}
	return (ssize_t)result;
#else
	(void)arg;
	(void)data;
	return (ssize_t)datalen;
#endif
}
/* Returns the width (number of characters; not bytes) of the given unicode string */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.format.format_wwidth") ssize_t
NOTHROW_NCX(LIBDCALL libd_format_wwidth)(void *arg,
                                         char16_t const *__restrict data,
                                         size_t datalen) {
#line 123 "kos/src/libc/magic/parts.wchar.format-printer.c"
#if 2 == 2
	size_t result = 0;
	char16_t const *iter, *end;
	(void)arg;
	end = (iter = data) + datalen;
	while (iter < end) {
		char16_t ch;
		ch = *iter++;
		if (ch >= 0xd800 && ch <= 0xd800 && iter < end) {
			ch = *iter;
			if (ch >= 0xdc00 && ch <= 0xdfff)
				++iter;
		}
		++result;
	}
	return (ssize_t)result;
#else
	(void)arg;
	(void)data;
	return (ssize_t)datalen;
#endif
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#undef format_wprintf
DEFINE_PUBLIC_WEAK_ALIAS(format_wrepeat, libc_format_wrepeat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$format_wrepeat, libd_format_wrepeat);
DEFINE_PUBLIC_WEAK_ALIAS(format_wescape, libc_format_wescape);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$format_wescape, libd_format_wescape);
DEFINE_PUBLIC_WEAK_ALIAS(format_whexdump, libc_format_whexdump);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$format_whexdump, libd_format_whexdump);
DEFINE_PUBLIC_WEAK_ALIAS(format_vwprintf, libc_format_vwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$format_vwprintf, libd_format_vwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(format_wprintf, libc_format_wprintf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$format_wprintf, libd_format_wprintf);
DEFINE_PUBLIC_WEAK_ALIAS(format_wsprintf_printer, libc_format_wsprintf_printer);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$format_wsprintf_printer, libd_format_wsprintf_printer);
DEFINE_PUBLIC_WEAK_ALIAS(format_wsnprintf_printer, libc_format_wsnprintf_printer);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$format_wsnprintf_printer, libd_format_wsnprintf_printer);
DEFINE_PUBLIC_WEAK_ALIAS(format_wwidth, libc_format_wwidth);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$format_wwidth, libd_format_wwidth);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_FORMAT_PRINTER_C */
