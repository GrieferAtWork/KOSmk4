/* HASH CRC-32:0x6e4f1760 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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
#include "format-printer.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "../user/string.h"
#include "../user/unicode.h"
#include "wctype.h"

DECL_BEGIN

#include "../libc/dl.h"      /* Use libc's relocation-optimized dl* functions. */
#include "../libc/string.h"  /* Dependency of `#include <libc/template/format-printf.h>' */
#include "../libc/unicode.h" /* Dependency of `#include <libc/template/format-scanf.h>' */
/**/
#include <hybrid/__assert.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <hybrid/__alloca.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <bits/types.h>      /* Dependency of `#include <libc/template/format-printf.h>' */
#include <bits/math-constants.h>

#include <libc/template/itoa_digits.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <libdisasm/disassembler.h>    /* Dependency of `#include <libc/template/format-printf.h>' */
#ifdef __KERNEL__
#include <kernel/addr2line.h>
#else /* __KERNEL__ */
#include <libdebuginfo/addr2line.h>
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#include <hybrid/__alloca.h>
#include <libc/string.h>
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.format") NONNULL((1)) ssize_t
(LIBDCALL libd_format_wrepeat)(pc16formatprinter printer,
                               void *arg,
                               char16_t ch,
                               size_t num_repetitions) THROWS(...) {
	ssize_t result, temp;
#ifdef __hybrid_alloca
	char16_t *buffer;
	if likely(num_repetitions <= 64) {
		buffer = (char16_t *)__hybrid_alloca(num_repetitions);
		__libc_memsetc(buffer, ch, num_repetitions, 2);
		return (*printer)(arg, buffer, num_repetitions);
	}
	buffer = (char16_t *)__hybrid_alloca(64);
	__libc_memsetc(buffer, ch, 64, 2);
#else /* __hybrid_alloca */
	char16_t buffer[64];
	if likely(num_repetitions <= 64) {
		__libc_memsetc(buffer, ch, num_repetitions, 2);
		return (*printer)(arg, buffer, num_repetitions);
	}
	__libc_memsetc(buffer, ch, 64, 2);
#endif /* !__hybrid_alloca */
	result = (*printer)(arg, buffer, 64);
	if unlikely(result < 0)
		goto done;
	for (;;) {
		num_repetitions -= 64;
		if (num_repetitions < 64)
			break;
		temp = (*printer)(arg, buffer, 64);
		if unlikely(temp < 0)
			goto done;
		result += temp;
	}
	if (num_repetitions) {
		temp = (*printer)(arg, buffer, num_repetitions);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
}
#include <hybrid/__alloca.h>
#include <libc/string.h>
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
INTERN ATTR_SECTION(".text.crt.wchar.string.format") NONNULL((1)) ssize_t
(LIBKCALL libc_format_wrepeat)(pc32formatprinter printer,
                               void *arg,
                               char32_t ch,
                               size_t num_repetitions) THROWS(...) {
	ssize_t result, temp;
#ifdef __hybrid_alloca
	char32_t *buffer;
	if likely(num_repetitions <= 64) {
		buffer = (char32_t *)__hybrid_alloca(num_repetitions);
		__libc_memsetc(buffer, ch, num_repetitions, 4);
		return (*printer)(arg, buffer, num_repetitions);
	}
	buffer = (char32_t *)__hybrid_alloca(64);
	__libc_memsetc(buffer, ch, 64, 4);
#else /* __hybrid_alloca */
	char32_t buffer[64];
	if likely(num_repetitions <= 64) {
		__libc_memsetc(buffer, ch, num_repetitions, 4);
		return (*printer)(arg, buffer, num_repetitions);
	}
	__libc_memsetc(buffer, ch, 64, 4);
#endif /* !__hybrid_alloca */
	result = (*printer)(arg, buffer, 64);
	if unlikely(result < 0)
		goto done;
	for (;;) {
		num_repetitions -= 64;
		if (num_repetitions < 64)
			break;
		temp = (*printer)(arg, buffer, 64);
		if unlikely(temp < 0)
			goto done;
		result += temp;
	}
	if (num_repetitions) {
		temp = (*printer)(arg, buffer, num_repetitions);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
}
#include <libc/template/itoa_digits.h>
/* >> format_escape(3)
 * Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2:  >> Hello  \"World\"  W\nhat a  great  day
 * NOTE: Output  #2 is generated if `FORMAT_ESCAPE_FPRINTRAW' is set
 * This  function  escapes  all  control  and  non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a  behavior that may be  modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: printer: A function called for all quoted portions of the text
 * @param: textlen: The total number of bytes to escape, starting at `text' */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.format") NONNULL((1)) ssize_t
(LIBDCALL libd_format_wescape)(pc16formatprinter printer,
                               void *arg,
                               char16_t const *__restrict text,
                               size_t textlen,
                               unsigned int flags) THROWS(...) {
	__PRIVATE char16_t const quote[1] = { '\"' };
	char16_t encoded_text[12]; size_t encoded_text_size;
	ssize_t result = 0, temp;
	char16_t const *textend = text + textlen;
	char16_t const *flush_start = text;
	encoded_text[0] = '\\';
	if likely(!(flags & 0x0001)) {
		temp = (*printer)(arg, quote, 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	while (text < textend) {
		char16_t const *old_text = text;
		uint32_t ch;



		ch = libc_unicode_readutf16_n((char16_t const **)&text,
		                         (char16_t const *)textend);



		if unlikely(ch < 32 || ch >= 127  || ch == '\'' ||
		              ch == '\"' || ch == '\\' ||
		             (flags & 0x0010)) {
			/* Flush unwritten direct-copy text. */
			if (flush_start < old_text) {
				temp = (*printer)(arg, flush_start, (size_t)(old_text - flush_start));
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			/* Character requires special encoding. */
			if (ch < 32) {
				/* Control character. */
				if (flags & 0x0008) {
default_ctrl:
					if (flags & 0x0002)
						goto encode_hex;
encode_oct:
					if (text < textend) {
						char16_t const *new_text = text;
						uint32_t next_ch;



						next_ch = libc_unicode_readutf16_n((char16_t const **)&new_text,
						                              (char16_t const *)textend);



						if (next_ch >= '0' && next_ch <= '7')
							goto encode_hex;
					}
					if (ch <= 0x07) {
						encoded_text[1] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 2;
					} else if (ch <= 0x3f) {
						encoded_text[1] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[2] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 3;
					} else if (ch <= 0x1ff) {
						encoded_text[1] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[2] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[3] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 4;
					} else if (ch <= 0xfff) {
						encoded_text[1] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[2] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[3] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[4] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 5;
					} else if (ch <= 0x7fff) {
						encoded_text[1] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[2] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[3] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[4] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[5] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 6;
					} else if (ch <= 0x3ffff) {
						encoded_text[1] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[2] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[3] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[4] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[5] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[6] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 7;
					} else if (ch <= 0x1fffff) {
						encoded_text[1] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[2] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[3] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[4] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[5] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[6] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[7] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 8;
					} else if (ch <= 0xffffff) {
						encoded_text[1] = itoa_decimal((ch & 0x00e00000) >> 21);
						encoded_text[2] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[3] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[4] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[5] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[6] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[7] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[8] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 9;
					} else if (ch <= 0x7ffffff) {
						encoded_text[1] = itoa_decimal((ch & 0x07000000) >> 24);
						encoded_text[2] = itoa_decimal((ch & 0x00e00000) >> 21);
						encoded_text[3] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[4] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[5] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[6] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[7] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[8] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[9] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 10;
					} else if (ch <= 0x3fffffff) {
						encoded_text[1] = itoa_decimal((ch & 0x38000000) >> 27);
						encoded_text[2] = itoa_decimal((ch & 0x07000000) >> 24);
						encoded_text[3] = itoa_decimal((ch & 0x00e00000) >> 21);
						encoded_text[4] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[5] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[6] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[7] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[8] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[9] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[10] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 11;
					} else {
						encoded_text[1] = itoa_decimal((ch & 0xc0000000) >> 30);
						encoded_text[2] = itoa_decimal((ch & 0x38000000) >> 27);
						encoded_text[3] = itoa_decimal((ch & 0x07000000) >> 24);
						encoded_text[4] = itoa_decimal((ch & 0x00e00000) >> 21);
						encoded_text[5] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[6] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[7] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[8] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[9] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[10] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[11] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 12;
					}
					goto print_encoded;
				}
special_control:
				switch (ch) {

				case 7:  ch = 'a'; break;
				case 8:  ch = 'b'; break;
				case 9:  ch = 't'; break;
				case 10: ch = 'n'; break;
				case 11: ch = 'v'; break;
				case 12: ch = 'f'; break;
				case 13: ch = 'r'; break;
				case 27: ch = 'e'; break;

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
			           !(flags & 0x0008)) {
				goto special_control;
			} else {
				/* Non-ascii character. */
/*default_nonascii:*/
				if (flags & 0x0004)
					goto encode_oct;
encode_hex:
				if (text < textend) {
					char16_t const *new_text = text;
					uint32_t next_ch;



					next_ch = libc_unicode_readutf16_n((char16_t const **)&new_text,
					                              (char16_t const *)textend);



					if ((next_ch >= 'a' && next_ch <= 'f') ||
					    (next_ch >= 'A' && next_ch <= 'F') ||
					    (next_ch >= '0' && next_ch <= '9'))
						goto encode_uni;
				}
				if (ch <= 0xf) {
					encoded_text[1] = 'x';
					encoded_text[2] = itoa_digit(flags & 0x0020, ch);
					encoded_text_size = 3;
				} else if (ch <= 0x7f) {
					encoded_text[1] = 'x';
					encoded_text[2] = itoa_digit(flags & 0x0020, (ch & 0x000000f0) >> 4);
					encoded_text[3] = itoa_digit(flags & 0x0020, ch & 0x0000000f);
					encoded_text_size = 4;
				} else {
encode_uni:
					if (ch <= 0xffff) {
						encoded_text[1] = 'u';
						encoded_text[2] = itoa_digit(flags & 0x0020, (ch & 0x0000f000) >> 12);
						encoded_text[3] = itoa_digit(flags & 0x0020, (ch & 0x00000f00) >> 8);
						encoded_text[4] = itoa_digit(flags & 0x0020, (ch & 0x000000f0) >> 4);
						encoded_text[5] = itoa_digit(flags & 0x0020, ch & 0x0000000f);
						encoded_text_size = 6;
					} else {
						encoded_text[1] = 'U';
						encoded_text[2] = itoa_digit(flags & 0x0020, (ch & 0xf0000000) >> 28);
						encoded_text[3] = itoa_digit(flags & 0x0020, (ch & 0x0f000000) >> 24);
						encoded_text[4] = itoa_digit(flags & 0x0020, (ch & 0x00f00000) >> 20);
						encoded_text[5] = itoa_digit(flags & 0x0020, (ch & 0x000f0000) >> 16);
						encoded_text[6] = itoa_digit(flags & 0x0020, (ch & 0x0000f000) >> 12);
						encoded_text[7] = itoa_digit(flags & 0x0020, (ch & 0x00000f00) >> 8);
						encoded_text[8] = itoa_digit(flags & 0x0020, (ch & 0x000000f0) >> 4);
						encoded_text[9] = itoa_digit(flags & 0x0020, ch & 0x0000000f);
						encoded_text_size = 10;
					}
				}
print_encoded:
				temp = (*printer)(arg, encoded_text, encoded_text_size);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			flush_start = text;
		}
	}
/*done:*/
	if (flush_start < text) {
		temp = (*printer)(arg, flush_start, (size_t)(text - flush_start));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	if likely(!(flags & 0x0001)) {
		temp = (*printer)(arg, quote, 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
}
#include <libc/template/itoa_digits.h>
/* >> format_escape(3)
 * Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2:  >> Hello  \"World\"  W\nhat a  great  day
 * NOTE: Output  #2 is generated if `FORMAT_ESCAPE_FPRINTRAW' is set
 * This  function  escapes  all  control  and  non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a  behavior that may be  modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: printer: A function called for all quoted portions of the text
 * @param: textlen: The total number of bytes to escape, starting at `text' */
INTERN ATTR_SECTION(".text.crt.wchar.string.format") NONNULL((1)) ssize_t
(LIBKCALL libc_format_wescape)(pc32formatprinter printer,
                               void *arg,
                               char32_t const *__restrict text,
                               size_t textlen,
                               unsigned int flags) THROWS(...) {
	__PRIVATE char32_t const quote[1] = { '\"' };
	char32_t encoded_text[12]; size_t encoded_text_size;
	ssize_t result = 0, temp;
	char32_t const *textend = text + textlen;
	char32_t const *flush_start = text;
	encoded_text[0] = '\\';
	if likely(!(flags & 0x0001)) {
		temp = (*printer)(arg, quote, 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	while (text < textend) {
		char32_t const *old_text = text;
		uint32_t ch;






		ch = (uint32_t)*text++;

		if unlikely(ch < 32 || ch >= 127  || ch == '\'' ||
		              ch == '\"' || ch == '\\' ||
		             (flags & 0x0010)) {
			/* Flush unwritten direct-copy text. */
			if (flush_start < old_text) {
				temp = (*printer)(arg, flush_start, (size_t)(old_text - flush_start));
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			/* Character requires special encoding. */
			if (ch < 32) {
				/* Control character. */
				if (flags & 0x0008) {
default_ctrl:
					if (flags & 0x0002)
						goto encode_hex;
encode_oct:
					if (text < textend) {
						char32_t const *new_text = text;
						uint32_t next_ch;






						next_ch = (uint32_t)*new_text++;

						if (next_ch >= '0' && next_ch <= '7')
							goto encode_hex;
					}
					if (ch <= 0x07) {
						encoded_text[1] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 2;
					} else if (ch <= 0x3f) {
						encoded_text[1] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[2] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 3;
					} else if (ch <= 0x1ff) {
						encoded_text[1] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[2] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[3] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 4;
					} else if (ch <= 0xfff) {
						encoded_text[1] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[2] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[3] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[4] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 5;
					} else if (ch <= 0x7fff) {
						encoded_text[1] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[2] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[3] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[4] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[5] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 6;
					} else if (ch <= 0x3ffff) {
						encoded_text[1] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[2] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[3] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[4] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[5] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[6] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 7;
					} else if (ch <= 0x1fffff) {
						encoded_text[1] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[2] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[3] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[4] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[5] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[6] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[7] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 8;
					} else if (ch <= 0xffffff) {
						encoded_text[1] = itoa_decimal((ch & 0x00e00000) >> 21);
						encoded_text[2] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[3] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[4] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[5] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[6] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[7] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[8] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 9;
					} else if (ch <= 0x7ffffff) {
						encoded_text[1] = itoa_decimal((ch & 0x07000000) >> 24);
						encoded_text[2] = itoa_decimal((ch & 0x00e00000) >> 21);
						encoded_text[3] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[4] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[5] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[6] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[7] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[8] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[9] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 10;
					} else if (ch <= 0x3fffffff) {
						encoded_text[1] = itoa_decimal((ch & 0x38000000) >> 27);
						encoded_text[2] = itoa_decimal((ch & 0x07000000) >> 24);
						encoded_text[3] = itoa_decimal((ch & 0x00e00000) >> 21);
						encoded_text[4] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[5] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[6] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[7] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[8] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[9] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[10] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 11;
					} else {
						encoded_text[1] = itoa_decimal((ch & 0xc0000000) >> 30);
						encoded_text[2] = itoa_decimal((ch & 0x38000000) >> 27);
						encoded_text[3] = itoa_decimal((ch & 0x07000000) >> 24);
						encoded_text[4] = itoa_decimal((ch & 0x00e00000) >> 21);
						encoded_text[5] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[6] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[7] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[8] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[9] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[10] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[11] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 12;
					}
					goto print_encoded;
				}
special_control:
				switch (ch) {

				case 7:  ch = 'a'; break;
				case 8:  ch = 'b'; break;
				case 9:  ch = 't'; break;
				case 10: ch = 'n'; break;
				case 11: ch = 'v'; break;
				case 12: ch = 'f'; break;
				case 13: ch = 'r'; break;
				case 27: ch = 'e'; break;

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
			           !(flags & 0x0008)) {
				goto special_control;
			} else {
				/* Non-ascii character. */
/*default_nonascii:*/
				if (flags & 0x0004)
					goto encode_oct;
encode_hex:
				if (text < textend) {
					char32_t const *new_text = text;
					uint32_t next_ch;






					next_ch = (uint32_t)*new_text++;

					if ((next_ch >= 'a' && next_ch <= 'f') ||
					    (next_ch >= 'A' && next_ch <= 'F') ||
					    (next_ch >= '0' && next_ch <= '9'))
						goto encode_uni;
				}
				if (ch <= 0xf) {
					encoded_text[1] = 'x';
					encoded_text[2] = itoa_digit(flags & 0x0020, ch);
					encoded_text_size = 3;
				} else if (ch <= 0x7f) {
					encoded_text[1] = 'x';
					encoded_text[2] = itoa_digit(flags & 0x0020, (ch & 0x000000f0) >> 4);
					encoded_text[3] = itoa_digit(flags & 0x0020, ch & 0x0000000f);
					encoded_text_size = 4;
				} else {
encode_uni:
					if (ch <= 0xffff) {
						encoded_text[1] = 'u';
						encoded_text[2] = itoa_digit(flags & 0x0020, (ch & 0x0000f000) >> 12);
						encoded_text[3] = itoa_digit(flags & 0x0020, (ch & 0x00000f00) >> 8);
						encoded_text[4] = itoa_digit(flags & 0x0020, (ch & 0x000000f0) >> 4);
						encoded_text[5] = itoa_digit(flags & 0x0020, ch & 0x0000000f);
						encoded_text_size = 6;
					} else {
						encoded_text[1] = 'U';
						encoded_text[2] = itoa_digit(flags & 0x0020, (ch & 0xf0000000) >> 28);
						encoded_text[3] = itoa_digit(flags & 0x0020, (ch & 0x0f000000) >> 24);
						encoded_text[4] = itoa_digit(flags & 0x0020, (ch & 0x00f00000) >> 20);
						encoded_text[5] = itoa_digit(flags & 0x0020, (ch & 0x000f0000) >> 16);
						encoded_text[6] = itoa_digit(flags & 0x0020, (ch & 0x0000f000) >> 12);
						encoded_text[7] = itoa_digit(flags & 0x0020, (ch & 0x00000f00) >> 8);
						encoded_text[8] = itoa_digit(flags & 0x0020, (ch & 0x000000f0) >> 4);
						encoded_text[9] = itoa_digit(flags & 0x0020, ch & 0x0000000f);
						encoded_text_size = 10;
					}
				}
print_encoded:
				temp = (*printer)(arg, encoded_text, encoded_text_size);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			flush_start = text;
		}
	}
/*done:*/
	if (flush_start < text) {
		temp = (*printer)(arg, flush_start, (size_t)(text - flush_start));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	if likely(!(flags & 0x0001)) {
		temp = (*printer)(arg, quote, 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
}
#include <hybrid/__alloca.h>
#include <hybrid/__unaligned.h>
#include <hybrid/byteorder.h>
#include <libc/template/itoa_digits.h>
/* >> format_hexdump(3)
 * Print a hex dump of the given data using the provided format printer
 * @param: printer:  The format printer callback
 * @param: data:     A pointer to the data that should be dumped
 * @param: size:     The amount of bytes read starting at data
 * @param: linesize: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: flags:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.format") NONNULL((1)) ssize_t
(LIBDCALL libd_format_whexdump)(pc16formatprinter printer,
                                void *arg,
                                void const *__restrict data,
                                size_t size,
                                size_t linesize,
                                unsigned int flags) THROWS(...) {
	__PRIVATE char16_t const lf[1] = { '\n' };
	byte_t const *line_data;
	char16_t buffer[
		(1 + (sizeof(void *) * 2) + 1) < 17 ? 17 :
		(1 + (sizeof(void *) * 2) + 1)], *dst;
	ssize_t temp, result = 0;
	unsigned int i; uintptr_t value;
	unsigned int offset_digits = 0;
	if (!size) goto done;
	if (!linesize) linesize = 16;
	if (flags & 0x0004) {
		value = size;
		do {
			++offset_digits;
		} while ((value >>= 4) != 0);
	}
	line_data = (byte_t const *)data;
	for (;;) {
		size_t line_len = linesize;
		if (line_len > size)
			line_len = size;
		if (!(flags & 0x0002)) {
			value = (uintptr_t)line_data;
			dst = buffer + sizeof(void *) * 2;
			*dst = ' ';
			while (dst > buffer) {
				*--dst = itoa_digit(!(flags & 0x0001), value & 0xf);
				value >>= 4;
			}
			temp = (*printer)(arg, buffer, (sizeof(void *) * 2) + 1);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		if (flags & 0x0004) {
			dst = buffer + 1 + offset_digits;
			*dst = ' ';
			value = (line_data - (byte_t const *)data);
			while (dst > buffer + 1) {
				*--dst = itoa_digit(!(flags & 0x0001), value & 0xf);
				value >>= 4;
			}
			buffer[0] = '+';
			temp = (*printer)(arg, buffer, (size_t)2 + offset_digits);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		if (!(flags & 0x0008)) {
			size_t i = 0;
			size_t tailspace_count;
			switch (flags & 0x3000) {

			default:
				tailspace_count = linesize * 3;
				break;

			case 0x1000:
				tailspace_count = (linesize / 2) * 5 + (linesize % 2) * 3;
				buffer[4] = ' ';
				for (; i + 2 <= line_len; i += 2) {
					u16 w = __hybrid_unaligned_get16((u16 *)(line_data + i));
					dst = buffer + 4;
					while (dst > buffer) {
						*--dst = itoa_digit(!(flags & 0x0001), w & 0xf);
						w >>= 4;
					}
					temp = (*printer)(arg, buffer, 5);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 5;
				}
				break;

			case 0x2000:
				tailspace_count = (linesize / 4) * 9 + (linesize % 4) * 3;
				buffer[8] = ' ';
				for (; i + 4 <= line_len; i += 4) {
					u32 l = __hybrid_unaligned_get32((u32 *)(line_data + i));
					dst = buffer + 8;
					while (dst > buffer) {
						*--dst = itoa_digit(!(flags & 0x0001), l & 0xf);
						l >>= 4;
					}
					temp = (*printer)(arg, buffer, 9);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 9;
				}
				break;

			case 0x3000:
				tailspace_count = (linesize / 8) * 17 + (linesize % 8) * 3;
				buffer[16] = ' ';
				for (; i + 8 <= line_len; i += 8) {
#if __SIZEOF_POINTER__ >= 8
					u64 q = __hybrid_unaligned_get64((u64 *)(line_data + i));
					dst = buffer + 16;
					while (dst > buffer) {
						*--dst = itoa_digit(!(flags & 0x0001), q & 0xf);
						q >>= 4;
					}
#else /* __SIZEOF_POINTER__ >= 8 */
					u32 a, b;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
					a = __hybrid_unaligned_get32((u32 *)(line_data + i + 4));
					b = __hybrid_unaligned_get32((u32 *)(line_data + i));
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
					a = __hybrid_unaligned_get32((u32 *)(line_data + i));
					b = __hybrid_unaligned_get32((u32 *)(line_data + i + 4));
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
					dst = buffer + 16;
					while (dst > buffer + 8) {
						*--dst = itoa_digit(!(flags & 0x0001), b & 0xf);
						b >>= 4;
					}
					while (dst > buffer) {
						*--dst = itoa_digit(!(flags & 0x0001), a & 0xf);
						a >>= 4;
					}
#endif /* __SIZEOF_POINTER__ < 8 */
					temp = (*printer)(arg, buffer, 17);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 17;
				}
				break;
			}
			buffer[2] = ' ';
			for (; i < line_len; ++i) {
				byte_t b = line_data[i];
				buffer[0] = itoa_digit(!(flags & 0x0001), b >> 4);
				buffer[1] = itoa_digit(!(flags & 0x0001), b & 0xf);
				temp = (*printer)(arg, buffer, 3);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				tailspace_count -= 3;
			}
			if (tailspace_count) {
				temp = libd_format_wrepeat(printer, arg, ' ', tailspace_count);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
		if (!(flags & 0x0010)) {
			for (i = 0; i < line_len; ++i) {
				byte_t b = line_data[i];
				if (!libd_iswprint(b))
					b = '.';
				temp = (*printer)(arg, (char16_t const *)&b, 1);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
		if (line_len >= size)
			break;
		line_data += line_len;
		size      -= line_len;
		temp = (*printer)(arg, lf, 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
}
#include <hybrid/__alloca.h>
#include <hybrid/__unaligned.h>
#include <hybrid/byteorder.h>
#include <libc/template/itoa_digits.h>
/* >> format_hexdump(3)
 * Print a hex dump of the given data using the provided format printer
 * @param: printer:  The format printer callback
 * @param: data:     A pointer to the data that should be dumped
 * @param: size:     The amount of bytes read starting at data
 * @param: linesize: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: flags:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
INTERN ATTR_SECTION(".text.crt.wchar.string.format") NONNULL((1)) ssize_t
(LIBKCALL libc_format_whexdump)(pc32formatprinter printer,
                                void *arg,
                                void const *__restrict data,
                                size_t size,
                                size_t linesize,
                                unsigned int flags) THROWS(...) {
	__PRIVATE char32_t const lf[1] = { '\n' };
	byte_t const *line_data;
	char32_t buffer[
		(1 + (sizeof(void *) * 2) + 1) < 17 ? 17 :
		(1 + (sizeof(void *) * 2) + 1)], *dst;
	ssize_t temp, result = 0;
	unsigned int i; uintptr_t value;
	unsigned int offset_digits = 0;
	if (!size) goto done;
	if (!linesize) linesize = 16;
	if (flags & 0x0004) {
		value = size;
		do {
			++offset_digits;
		} while ((value >>= 4) != 0);
	}
	line_data = (byte_t const *)data;
	for (;;) {
		size_t line_len = linesize;
		if (line_len > size)
			line_len = size;
		if (!(flags & 0x0002)) {
			value = (uintptr_t)line_data;
			dst = buffer + sizeof(void *) * 2;
			*dst = ' ';
			while (dst > buffer) {
				*--dst = itoa_digit(!(flags & 0x0001), value & 0xf);
				value >>= 4;
			}
			temp = (*printer)(arg, buffer, (sizeof(void *) * 2) + 1);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		if (flags & 0x0004) {
			dst = buffer + 1 + offset_digits;
			*dst = ' ';
			value = (line_data - (byte_t const *)data);
			while (dst > buffer + 1) {
				*--dst = itoa_digit(!(flags & 0x0001), value & 0xf);
				value >>= 4;
			}
			buffer[0] = '+';
			temp = (*printer)(arg, buffer, (size_t)2 + offset_digits);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		if (!(flags & 0x0008)) {
			size_t i = 0;
			size_t tailspace_count;
			switch (flags & 0x3000) {

			default:
				tailspace_count = linesize * 3;
				break;

			case 0x1000:
				tailspace_count = (linesize / 2) * 5 + (linesize % 2) * 3;
				buffer[4] = ' ';
				for (; i + 2 <= line_len; i += 2) {
					u16 w = __hybrid_unaligned_get16((u16 *)(line_data + i));
					dst = buffer + 4;
					while (dst > buffer) {
						*--dst = itoa_digit(!(flags & 0x0001), w & 0xf);
						w >>= 4;
					}
					temp = (*printer)(arg, buffer, 5);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 5;
				}
				break;

			case 0x2000:
				tailspace_count = (linesize / 4) * 9 + (linesize % 4) * 3;
				buffer[8] = ' ';
				for (; i + 4 <= line_len; i += 4) {
					u32 l = __hybrid_unaligned_get32((u32 *)(line_data + i));
					dst = buffer + 8;
					while (dst > buffer) {
						*--dst = itoa_digit(!(flags & 0x0001), l & 0xf);
						l >>= 4;
					}
					temp = (*printer)(arg, buffer, 9);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 9;
				}
				break;

			case 0x3000:
				tailspace_count = (linesize / 8) * 17 + (linesize % 8) * 3;
				buffer[16] = ' ';
				for (; i + 8 <= line_len; i += 8) {
#if __SIZEOF_POINTER__ >= 8
					u64 q = __hybrid_unaligned_get64((u64 *)(line_data + i));
					dst = buffer + 16;
					while (dst > buffer) {
						*--dst = itoa_digit(!(flags & 0x0001), q & 0xf);
						q >>= 4;
					}
#else /* __SIZEOF_POINTER__ >= 8 */
					u32 a, b;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
					a = __hybrid_unaligned_get32((u32 *)(line_data + i + 4));
					b = __hybrid_unaligned_get32((u32 *)(line_data + i));
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
					a = __hybrid_unaligned_get32((u32 *)(line_data + i));
					b = __hybrid_unaligned_get32((u32 *)(line_data + i + 4));
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
					dst = buffer + 16;
					while (dst > buffer + 8) {
						*--dst = itoa_digit(!(flags & 0x0001), b & 0xf);
						b >>= 4;
					}
					while (dst > buffer) {
						*--dst = itoa_digit(!(flags & 0x0001), a & 0xf);
						a >>= 4;
					}
#endif /* __SIZEOF_POINTER__ < 8 */
					temp = (*printer)(arg, buffer, 17);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 17;
				}
				break;
			}
			buffer[2] = ' ';
			for (; i < line_len; ++i) {
				byte_t b = line_data[i];
				buffer[0] = itoa_digit(!(flags & 0x0001), b >> 4);
				buffer[1] = itoa_digit(!(flags & 0x0001), b & 0xf);
				temp = (*printer)(arg, buffer, 3);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				tailspace_count -= 3;
			}
			if (tailspace_count) {
				temp = libc_format_wrepeat(printer, arg, ' ', tailspace_count);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
		if (!(flags & 0x0010)) {
			for (i = 0; i < line_len; ++i) {
				byte_t b = line_data[i];
				if (!libc_iswprint(b))
					b = '.';
				temp = (*printer)(arg, (char32_t const *)&b, 1);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
		if (line_len >= size)
			break;
		line_data += line_len;
		size      -= line_len;
		temp = (*printer)(arg, lf, 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
}
#include <parts/printf-config.h>
#include <bits/types.h>
#include <libc/template/itoa_digits.h>
#include <libc/parts.uchar.string.h>
#include <libc/string.h>
#include <libc/errno.h>
#include <hybrid/__assert.h>
#include <hybrid/__alloca.h>
#ifndef __NO_PRINTF_DISASM
#if !defined(__KERNEL__) || !defined(__KOS__)
#include <dlfcn.h>
#endif /* !__KERNEL__ || !__KOS__ */
#include <libdisasm/disassembler.h>
#endif /* !__NO_PRINTF_DISASM */
#ifndef __NO_PRINTF_VINFO
#if !defined(__KERNEL__) || !defined(__KOS__)
#include <dlfcn.h>
#include <libdebuginfo/addr2line.h>
#else /* !__KERNEL__ || !__KOS__ */
#include <kernel/addr2line.h>
#endif /* __KERNEL__ && __KOS__ */
#endif /* !__NO_PRINTF_VINFO */
/* >> format_printf(3), format_vprintf(3)
 * Generic     printf      implementation
 * Taking a  regular printf-style  format  string and  arguments,  these
 * functions will call the given `printer' callback with various strings
 * that, when put together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * Supported extensions:
 *  - `%q'-format mode: Semantics equivalent to `%s', this modifier escapes the string using
 *                        - `format_escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        - `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
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
 *                 - Invoke `format_hexdump(..., va_arg(args, void *))'
 *                 - Integer-length (`%$I32[hex]') flags affect `FORMAT_HEXDUMP_(BYTES|WORDS|DWORDS|QWORDS)'
 *                 - The argument string affect flags (defaults to `FORMAT_HEXDUMP_FNORMAL')
 *                    - `FORMAT_HEXDUMP_FHEXLOWER':  yes:l, no:L
 *                    - `FORMAT_HEXDUMP_FOFFSETS':   yes:o, no:O
 *                    - `FORMAT_HEXDUMP_FNOADDRESS': yes:P, no:p
 *                    - `FORMAT_HEXDUMP_FNOASCII':   yes:A, no:a
 *                    - `FORMAT_HEXDUMP_FNOHEX':     yes:H, no:h
 *             - `%[gen]'
 *                 - Invoke a custom format printer function pointer passed through args
 *                   >> typedef ssize_t (*PGEN)(pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> DO((*g)(printer, arg));
 *             - `%[gen:c]'
 *                 - Same as `%[gen]', but insert an additional argument `T' that depends
 *                   on the integer size prefix (`%I32[gen:c]') and defaults to  `void *'
 *                   >> typedef ssize_t (*PGEN)(T a, pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> T    a = va_arg(args, T);
 *                   >> DO((*g)(a, printer, arg));
 *             - `%[disasm]' / `%$[disasm]'
 *                 - Print the  mnemonic and  operands of  a single  native  assembly
 *                   instruction read from `va_arg(args, void *)' (using `libdisasm')
 *                   s.a. `disasm_single()'
 *                 - When the second form (with  a fixed buffer size)  is used, do a  full
 *                   disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *                   s.a. `disasm()'
 *             - `%[vinfo]' / `%[vinfo:<format=%f(%l,%c) : %n>]'
 *                 - Print addr2line information for a text address read from `va_arg(args, void *)'
 *                 - The given `format' string is a special printf-like format declaration
 *                   that accepts the following substitutions:
 *                   - `%%'   Print a single `%'-character (used for escaping `%')
 *                   - `%p'   Output the queried text address the same way `format_printf(..., "%q", addr)' would (as `sizeof(void *) * 2' uppercase hex characters)
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
 *  - strdupf:          Output  into  dynamically   allocated  heap   memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more...
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.format") ATTR_LIBC_C16PRINTF(3, 0) NONNULL((1, 3)) ssize_t
(LIBDCALL libd_format_vwprintf)(pc16formatprinter printer,
                                void *arg,
                                char16_t const *__restrict format,
                                va_list args) THROWS(...) {
#ifndef __INTELLISENSE__
#define __FORMAT_PRINTER            printer
#define __FORMAT_ARG                arg
#define __FORMAT_FORMAT             format
#define __FORMAT_ARGS               args
#define __CHAR_TYPE                 char16_t
#define __CHAR_SIZE                 2
#define __FORMAT_STRERROR           libd_strerror
#define __FORMAT_REPEAT             libd_format_wrepeat
#define __FORMAT_HEXDUMP            libd_format_whexdump
#define __FORMAT_WIDTH              libd_format_wwidth
#define __FORMAT_ESCAPE             libd_format_wescape
#define __FORMAT_WIDTH8             libc_format_width
#define __FORMAT_ESCAPE8            libc_format_escape
#define __FORMAT_UNICODE_FORMAT8    libd_format_8tow

#define __FORMAT_WIDTH32            libc_format_wwidth
#define __FORMAT_ESCAPE32           libc_format_wescape
#define __FORMAT_UNICODE_WRITECHAR  libc_unicode_writeutf16
#define __FORMAT_UNICODE_FORMAT32   libc_format_wto16






#include <libc/template/format-printf.h>
#endif /* !__INTELLISENSE__ */
}
#include <parts/printf-config.h>
#include <bits/types.h>
#include <libc/template/itoa_digits.h>
#include <libc/parts.uchar.string.h>
#include <libc/string.h>
#include <libc/errno.h>
#include <hybrid/__assert.h>
#include <hybrid/__alloca.h>
#ifndef __NO_PRINTF_DISASM
#if !defined(__KERNEL__) || !defined(__KOS__)
#include <dlfcn.h>
#endif /* !__KERNEL__ || !__KOS__ */
#include <libdisasm/disassembler.h>
#endif /* !__NO_PRINTF_DISASM */
#ifndef __NO_PRINTF_VINFO
#if !defined(__KERNEL__) || !defined(__KOS__)
#include <dlfcn.h>
#include <libdebuginfo/addr2line.h>
#else /* !__KERNEL__ || !__KOS__ */
#include <kernel/addr2line.h>
#endif /* __KERNEL__ && __KOS__ */
#endif /* !__NO_PRINTF_VINFO */
/* >> format_printf(3), format_vprintf(3)
 * Generic     printf      implementation
 * Taking a  regular printf-style  format  string and  arguments,  these
 * functions will call the given `printer' callback with various strings
 * that, when put together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * Supported extensions:
 *  - `%q'-format mode: Semantics equivalent to `%s', this modifier escapes the string using
 *                        - `format_escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        - `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
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
 *                 - Invoke `format_hexdump(..., va_arg(args, void *))'
 *                 - Integer-length (`%$I32[hex]') flags affect `FORMAT_HEXDUMP_(BYTES|WORDS|DWORDS|QWORDS)'
 *                 - The argument string affect flags (defaults to `FORMAT_HEXDUMP_FNORMAL')
 *                    - `FORMAT_HEXDUMP_FHEXLOWER':  yes:l, no:L
 *                    - `FORMAT_HEXDUMP_FOFFSETS':   yes:o, no:O
 *                    - `FORMAT_HEXDUMP_FNOADDRESS': yes:P, no:p
 *                    - `FORMAT_HEXDUMP_FNOASCII':   yes:A, no:a
 *                    - `FORMAT_HEXDUMP_FNOHEX':     yes:H, no:h
 *             - `%[gen]'
 *                 - Invoke a custom format printer function pointer passed through args
 *                   >> typedef ssize_t (*PGEN)(pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> DO((*g)(printer, arg));
 *             - `%[gen:c]'
 *                 - Same as `%[gen]', but insert an additional argument `T' that depends
 *                   on the integer size prefix (`%I32[gen:c]') and defaults to  `void *'
 *                   >> typedef ssize_t (*PGEN)(T a, pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> T    a = va_arg(args, T);
 *                   >> DO((*g)(a, printer, arg));
 *             - `%[disasm]' / `%$[disasm]'
 *                 - Print the  mnemonic and  operands of  a single  native  assembly
 *                   instruction read from `va_arg(args, void *)' (using `libdisasm')
 *                   s.a. `disasm_single()'
 *                 - When the second form (with  a fixed buffer size)  is used, do a  full
 *                   disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *                   s.a. `disasm()'
 *             - `%[vinfo]' / `%[vinfo:<format=%f(%l,%c) : %n>]'
 *                 - Print addr2line information for a text address read from `va_arg(args, void *)'
 *                 - The given `format' string is a special printf-like format declaration
 *                   that accepts the following substitutions:
 *                   - `%%'   Print a single `%'-character (used for escaping `%')
 *                   - `%p'   Output the queried text address the same way `format_printf(..., "%q", addr)' would (as `sizeof(void *) * 2' uppercase hex characters)
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
 *  - strdupf:          Output  into  dynamically   allocated  heap   memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more...
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
INTERN ATTR_SECTION(".text.crt.wchar.string.format") ATTR_LIBC_C32PRINTF(3, 0) NONNULL((1, 3)) ssize_t
(LIBKCALL libc_format_vwprintf)(pc32formatprinter printer,
                                void *arg,
                                char32_t const *__restrict format,
                                va_list args) THROWS(...) {
#ifndef __INTELLISENSE__
#define __FORMAT_PRINTER            printer
#define __FORMAT_ARG                arg
#define __FORMAT_FORMAT             format
#define __FORMAT_ARGS               args
#define __CHAR_TYPE                 char32_t
#define __CHAR_SIZE                 4
#define __FORMAT_STRERROR           libc_strerror
#define __FORMAT_REPEAT             libc_format_wrepeat
#define __FORMAT_HEXDUMP            libc_format_whexdump
#define __FORMAT_WIDTH              libc_format_wwidth
#define __FORMAT_ESCAPE             libc_format_wescape
#define __FORMAT_WIDTH8             libc_format_width
#define __FORMAT_ESCAPE8            libc_format_escape
#define __FORMAT_UNICODE_FORMAT8    libc_format_8tow






#define __FORMAT_WIDTH16            libd_format_wwidth
#define __FORMAT_ESCAPE16           libd_format_wescape
#define __FORMAT_UNICODE_WRITECHAR(dst, ch) ((dst)[0] = (ch), (dst) + 1)
#define __FORMAT_UNICODE_FORMAT16   libd_format_wto32

#include <libc/template/format-printf.h>
#endif /* !__INTELLISENSE__ */
}
/* >> format_printf(3), format_vprintf(3)
 * Generic     printf      implementation
 * Taking a  regular printf-style  format  string and  arguments,  these
 * functions will call the given `printer' callback with various strings
 * that, when put together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * Supported extensions:
 *  - `%q'-format mode: Semantics equivalent to `%s', this modifier escapes the string using
 *                        - `format_escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        - `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
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
 *                 - Invoke `format_hexdump(..., va_arg(args, void *))'
 *                 - Integer-length (`%$I32[hex]') flags affect `FORMAT_HEXDUMP_(BYTES|WORDS|DWORDS|QWORDS)'
 *                 - The argument string affect flags (defaults to `FORMAT_HEXDUMP_FNORMAL')
 *                    - `FORMAT_HEXDUMP_FHEXLOWER':  yes:l, no:L
 *                    - `FORMAT_HEXDUMP_FOFFSETS':   yes:o, no:O
 *                    - `FORMAT_HEXDUMP_FNOADDRESS': yes:P, no:p
 *                    - `FORMAT_HEXDUMP_FNOASCII':   yes:A, no:a
 *                    - `FORMAT_HEXDUMP_FNOHEX':     yes:H, no:h
 *             - `%[gen]'
 *                 - Invoke a custom format printer function pointer passed through args
 *                   >> typedef ssize_t (*PGEN)(pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> DO((*g)(printer, arg));
 *             - `%[gen:c]'
 *                 - Same as `%[gen]', but insert an additional argument `T' that depends
 *                   on the integer size prefix (`%I32[gen:c]') and defaults to  `void *'
 *                   >> typedef ssize_t (*PGEN)(T a, pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> T    a = va_arg(args, T);
 *                   >> DO((*g)(a, printer, arg));
 *             - `%[disasm]' / `%$[disasm]'
 *                 - Print the  mnemonic and  operands of  a single  native  assembly
 *                   instruction read from `va_arg(args, void *)' (using `libdisasm')
 *                   s.a. `disasm_single()'
 *                 - When the second form (with  a fixed buffer size)  is used, do a  full
 *                   disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *                   s.a. `disasm()'
 *             - `%[vinfo]' / `%[vinfo:<format=%f(%l,%c) : %n>]'
 *                 - Print addr2line information for a text address read from `va_arg(args, void *)'
 *                 - The given `format' string is a special printf-like format declaration
 *                   that accepts the following substitutions:
 *                   - `%%'   Print a single `%'-character (used for escaping `%')
 *                   - `%p'   Output the queried text address the same way `format_printf(..., "%q", addr)' would (as `sizeof(void *) * 2' uppercase hex characters)
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
 *  - strdupf:          Output  into  dynamically   allocated  heap   memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more...
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.format") ATTR_LIBC_C16PRINTF(3, 0) NONNULL((1, 3)) ssize_t
(LIBDCALL libd_format_wprintf)(pc16formatprinter printer,
                               void *arg,
                               char16_t const *__restrict format,
                               ...) THROWS(...) {
	ssize_t result;
	va_list args;
	va_start(args, format);
	result = libd_format_vwprintf(printer, arg, format, args);
	va_end(args);
	return result;
}
/* >> format_printf(3), format_vprintf(3)
 * Generic     printf      implementation
 * Taking a  regular printf-style  format  string and  arguments,  these
 * functions will call the given `printer' callback with various strings
 * that, when put together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * Supported extensions:
 *  - `%q'-format mode: Semantics equivalent to `%s', this modifier escapes the string using
 *                        - `format_escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        - `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
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
 *                 - Invoke `format_hexdump(..., va_arg(args, void *))'
 *                 - Integer-length (`%$I32[hex]') flags affect `FORMAT_HEXDUMP_(BYTES|WORDS|DWORDS|QWORDS)'
 *                 - The argument string affect flags (defaults to `FORMAT_HEXDUMP_FNORMAL')
 *                    - `FORMAT_HEXDUMP_FHEXLOWER':  yes:l, no:L
 *                    - `FORMAT_HEXDUMP_FOFFSETS':   yes:o, no:O
 *                    - `FORMAT_HEXDUMP_FNOADDRESS': yes:P, no:p
 *                    - `FORMAT_HEXDUMP_FNOASCII':   yes:A, no:a
 *                    - `FORMAT_HEXDUMP_FNOHEX':     yes:H, no:h
 *             - `%[gen]'
 *                 - Invoke a custom format printer function pointer passed through args
 *                   >> typedef ssize_t (*PGEN)(pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> DO((*g)(printer, arg));
 *             - `%[gen:c]'
 *                 - Same as `%[gen]', but insert an additional argument `T' that depends
 *                   on the integer size prefix (`%I32[gen:c]') and defaults to  `void *'
 *                   >> typedef ssize_t (*PGEN)(T a, pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> T    a = va_arg(args, T);
 *                   >> DO((*g)(a, printer, arg));
 *             - `%[disasm]' / `%$[disasm]'
 *                 - Print the  mnemonic and  operands of  a single  native  assembly
 *                   instruction read from `va_arg(args, void *)' (using `libdisasm')
 *                   s.a. `disasm_single()'
 *                 - When the second form (with  a fixed buffer size)  is used, do a  full
 *                   disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *                   s.a. `disasm()'
 *             - `%[vinfo]' / `%[vinfo:<format=%f(%l,%c) : %n>]'
 *                 - Print addr2line information for a text address read from `va_arg(args, void *)'
 *                 - The given `format' string is a special printf-like format declaration
 *                   that accepts the following substitutions:
 *                   - `%%'   Print a single `%'-character (used for escaping `%')
 *                   - `%p'   Output the queried text address the same way `format_printf(..., "%q", addr)' would (as `sizeof(void *) * 2' uppercase hex characters)
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
 *  - strdupf:          Output  into  dynamically   allocated  heap   memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more...
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
INTERN ATTR_SECTION(".text.crt.wchar.string.format") ATTR_LIBC_C32PRINTF(3, 0) NONNULL((1, 3)) ssize_t
(LIBKCALL libc_format_wprintf)(pc32formatprinter printer,
                               void *arg,
                               char32_t const *__restrict format,
                               ...) THROWS(...) {
	ssize_t result;
	va_list args;
	va_start(args, format);
	result = libc_format_vwprintf(printer, arg, format, args);
	va_end(args);
	return result;
}
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.format") NONNULL((1, 2)) ssize_t
NOTHROW_NCX(__C16FORMATPRINTER_CC libd_format_wsprintf_printer)(void *arg,
                                                                char16_t const *__restrict data,
                                                                size_t datalen) {
	*(char16_t **)arg = (char16_t *)libc_mempcpyc(*(char16_t **)arg, data, datalen, sizeof(char16_t));
	return (ssize_t)datalen;
}
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
INTERN ATTR_SECTION(".text.crt.wchar.string.format") NONNULL((1, 2)) ssize_t
NOTHROW_NCX(__C32FORMATPRINTER_CC libc_format_wsprintf_printer)(void *arg,
                                                                char32_t const *__restrict data,
                                                                size_t datalen) {
	*(char32_t **)arg = (char32_t *)libc_mempcpyc(*(char32_t **)arg, data, datalen, sizeof(char32_t));
	return (ssize_t)datalen;
}
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 * NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',   or
 *       alternatively the sum of return values of all calls to `format_wsnprintf_printer(3)' */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.format") NONNULL((1, 2)) ssize_t
NOTHROW_NCX(__C16FORMATPRINTER_CC libd_format_wsnprintf_printer)(void *arg,
                                                                 char16_t const *__restrict data,
                                                                 size_t datalen) {
	struct __local_format_snprintf_data {
		char16_t  *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		size_t sd_bufsiz; /* Remaining buffer size. */
	};
	struct __local_format_snprintf_data *ctrl;
	size_t result = datalen;
	ctrl = (struct __local_format_snprintf_data *)arg;
	if (result > ctrl->sd_bufsiz)
		result = ctrl->sd_bufsiz;
	libc_memcpyc(ctrl->sd_buffer, data, result, sizeof(char16_t));
	ctrl->sd_buffer += datalen;
	ctrl->sd_bufsiz -= result;
	return (ssize_t)datalen;
}
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 * NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',   or
 *       alternatively the sum of return values of all calls to `format_wsnprintf_printer(3)' */
INTERN ATTR_SECTION(".text.crt.wchar.string.format") NONNULL((1, 2)) ssize_t
NOTHROW_NCX(__C32FORMATPRINTER_CC libc_format_wsnprintf_printer)(void *arg,
                                                                 char32_t const *__restrict data,
                                                                 size_t datalen) {
	struct __local_format_snprintf_data {
		char32_t  *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		size_t sd_bufsiz; /* Remaining buffer size. */
	};
	struct __local_format_snprintf_data *ctrl;
	size_t result = datalen;
	ctrl = (struct __local_format_snprintf_data *)arg;
	if (result > ctrl->sd_bufsiz)
		result = ctrl->sd_bufsiz;
	libc_memcpyc(ctrl->sd_buffer, data, result, sizeof(char32_t));
	ctrl->sd_buffer += datalen;
	ctrl->sd_bufsiz -= result;
	return (ssize_t)datalen;
}
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.format") ATTR_PURE NONNULL((2)) ssize_t
NOTHROW_NCX(__C16FORMATPRINTER_CC libd_format_wwidth)(void *arg,
                                                      char16_t const *__restrict data,
                                                      size_t datalen) {

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











}
#include <hybrid/__assert.h>
/* Pack  and  finalize  a  given  aprintf  format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format  printer sub-system should  be used as follows:
 * >> char *result;
 * >> ssize_t error;
 * >> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but  will  finalize  the  given   aprintf  printer  an  all   cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters  were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.format") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_format_waprintf_pack)(struct format_c16aprintf_data *__restrict self,
                                                size_t *pstrlen) {
	/* Free unused buffer memory. */
	char16_t *result;
	if (self->ap_avail != 0) {
		char16_t *newbuf;
		newbuf = (char16_t *)libc_realloc(self->ap_base,
		                         (self->ap_used + 1) * sizeof(char16_t));
		if likely(newbuf)
			self->ap_base = newbuf;
	} else {
		if unlikely(!self->ap_used) {
			/* Special case: Nothing was printed. */
			__hybrid_assert(!self->ap_base);
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
			self->ap_base = (char16_t *)libc_malloc(1 * sizeof(char16_t));
#else /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
			self->ap_base = (char16_t *)libc_realloc(NULL, 1 * sizeof(char16_t));
#endif /* !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
			if unlikely(!self->ap_base)
				return NULL;
		}
	}
	result = self->ap_base;
	__hybrid_assert(result);
	result[self->ap_used] = '\0'; /* NUL-terminate */
	if (pstrlen)
		*pstrlen = self->ap_used;
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#if __SIZEOF_POINTER__ == 4
	self->ap_base  = (char16_t *)__UINT32_C(0xcccccccc);
	self->ap_avail = __UINT32_C(0xcccccccc);
	self->ap_used  = __UINT32_C(0xcccccccc);
#elif __SIZEOF_POINTER__ == 8
	self->ap_base  = (char16_t *)__UINT64_C(0xcccccccccccccccc);
	self->ap_avail = __UINT64_C(0xcccccccccccccccc);
	self->ap_used  = __UINT64_C(0xcccccccccccccccc);
#endif /* ... */
#endif /* !NDEBUG && !NDEBUG_FINI */
	return result;
}
#include <hybrid/__assert.h>
/* Pack  and  finalize  a  given  aprintf  format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format  printer sub-system should  be used as follows:
 * >> char *result;
 * >> ssize_t error;
 * >> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but  will  finalize  the  given   aprintf  printer  an  all   cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters  were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
INTERN ATTR_SECTION(".text.crt.wchar.string.format") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_format_waprintf_pack)(struct format_c32aprintf_data *__restrict self,
                                                size_t *pstrlen) {
	/* Free unused buffer memory. */
	char32_t *result;
	if (self->ap_avail != 0) {
		char32_t *newbuf;
		newbuf = (char32_t *)libc_realloc(self->ap_base,
		                         (self->ap_used + 1) * sizeof(char32_t));
		if likely(newbuf)
			self->ap_base = newbuf;
	} else {
		if unlikely(!self->ap_used) {
			/* Special case: Nothing was printed. */
			__hybrid_assert(!self->ap_base);
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
			self->ap_base = (char32_t *)libc_malloc(1 * sizeof(char32_t));
#else /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
			self->ap_base = (char32_t *)libc_realloc(NULL, 1 * sizeof(char32_t));
#endif /* !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
			if unlikely(!self->ap_base)
				return NULL;
		}
	}
	result = self->ap_base;
	__hybrid_assert(result);
	result[self->ap_used] = '\0'; /* NUL-terminate */
	if (pstrlen)
		*pstrlen = self->ap_used;
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#if __SIZEOF_POINTER__ == 4
	self->ap_base  = (char32_t *)__UINT32_C(0xcccccccc);
	self->ap_avail = __UINT32_C(0xcccccccc);
	self->ap_used  = __UINT32_C(0xcccccccc);
#elif __SIZEOF_POINTER__ == 8
	self->ap_base  = (char32_t *)__UINT64_C(0xcccccccccccccccc);
	self->ap_avail = __UINT64_C(0xcccccccccccccccc);
	self->ap_used  = __UINT64_C(0xcccccccccccccccc);
#endif /* ... */
#endif /* !NDEBUG && !NDEBUG_FINI */
	return result;
}
#include <hybrid/__assert.h>
/* >> format_waprintf_alloc(3)
 * Allocate  a  buffer  of  `num_wchars'  wide-characters  at  the  end  of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.format") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_format_waprintf_alloc)(struct format_c16aprintf_data *__restrict self,
                                                 size_t num_wchars) {
	char16_t *result;
	if (self->ap_avail < num_wchars) {
		char16_t *newbuf;
		size_t min_alloc = self->ap_used + num_wchars;
		size_t new_alloc = self->ap_used + self->ap_avail;
		if (!new_alloc)
			new_alloc = 8;
		while (new_alloc < min_alloc)
			new_alloc *= 2;
		newbuf = (char16_t *)libc_realloc(self->ap_base, (new_alloc + 1) * sizeof(char16_t));
		if unlikely(!newbuf) {
			new_alloc = min_alloc;
			newbuf    = (char16_t *)libc_realloc(self->ap_base, (new_alloc + 1) * sizeof(char16_t));
			if unlikely(!newbuf)
				goto err;
		}
		__hybrid_assert(new_alloc >= self->ap_used + num_wchars);
		self->ap_base  = newbuf;
		self->ap_avail = new_alloc - self->ap_used;
	}
	result = self->ap_base + self->ap_used;
	self->ap_avail -= num_wchars;
	self->ap_used  += num_wchars;
	return result;
err:
	return NULL;
}
#include <hybrid/__assert.h>
/* >> format_waprintf_alloc(3)
 * Allocate  a  buffer  of  `num_wchars'  wide-characters  at  the  end  of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
INTERN ATTR_SECTION(".text.crt.wchar.string.format") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_format_waprintf_alloc)(struct format_c32aprintf_data *__restrict self,
                                                 size_t num_wchars) {
	char32_t *result;
	if (self->ap_avail < num_wchars) {
		char32_t *newbuf;
		size_t min_alloc = self->ap_used + num_wchars;
		size_t new_alloc = self->ap_used + self->ap_avail;
		if (!new_alloc)
			new_alloc = 8;
		while (new_alloc < min_alloc)
			new_alloc *= 2;
		newbuf = (char32_t *)libc_realloc(self->ap_base, (new_alloc + 1) * sizeof(char32_t));
		if unlikely(!newbuf) {
			new_alloc = min_alloc;
			newbuf    = (char32_t *)libc_realloc(self->ap_base, (new_alloc + 1) * sizeof(char32_t));
			if unlikely(!newbuf)
				goto err;
		}
		__hybrid_assert(new_alloc >= self->ap_used + num_wchars);
		self->ap_base  = newbuf;
		self->ap_avail = new_alloc - self->ap_used;
	}
	result = self->ap_base + self->ap_used;
	self->ap_avail -= num_wchars;
	self->ap_used  += num_wchars;
	return result;
err:
	return NULL;
}
/* >> format_waprintf_printer(3)
 * Print data  to a  dynamically allocated  heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pwformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.format") WUNUSED NONNULL((1, 2)) ssize_t
NOTHROW_NCX(__C16FORMATPRINTER_CC libd_format_waprintf_printer)(void *arg,
                                                                char16_t const *__restrict data,
                                                                size_t datalen) {
	char16_t *buf;
	buf = libd_format_waprintf_alloc((struct format_c16aprintf_data *)arg, datalen);
	if unlikely(!buf)
		goto err;
	(char16_t *)libc_memcpyw(buf, data, datalen);
	return (ssize_t)datalen;
err:
	return -1;
}
/* >> format_waprintf_printer(3)
 * Print data  to a  dynamically allocated  heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pwformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
INTERN ATTR_SECTION(".text.crt.wchar.string.format") WUNUSED NONNULL((1, 2)) ssize_t
NOTHROW_NCX(__C32FORMATPRINTER_CC libc_format_waprintf_printer)(void *arg,
                                                                char32_t const *__restrict data,
                                                                size_t datalen) {
	char32_t *buf;
	buf = libc_format_waprintf_alloc((struct format_c32aprintf_data *)arg, datalen);
	if unlikely(!buf)
		goto err;
	(char32_t *)libc_memcpyl(buf, data, datalen);
	return (ssize_t)datalen;
err:
	return -1;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$format_wrepeat, libd_format_wrepeat);
DEFINE_PUBLIC_ALIAS(format_wrepeat, libc_format_wrepeat);
DEFINE_PUBLIC_ALIAS(DOS$format_wescape, libd_format_wescape);
DEFINE_PUBLIC_ALIAS(format_wescape, libc_format_wescape);
DEFINE_PUBLIC_ALIAS(DOS$format_whexdump, libd_format_whexdump);
DEFINE_PUBLIC_ALIAS(format_whexdump, libc_format_whexdump);
DEFINE_PUBLIC_ALIAS(DOS$format_vwprintf, libd_format_vwprintf);
DEFINE_PUBLIC_ALIAS(format_vwprintf, libc_format_vwprintf);
DEFINE_PUBLIC_ALIAS(DOS$format_wprintf, libd_format_wprintf);
DEFINE_PUBLIC_ALIAS(format_wprintf, libc_format_wprintf);
DEFINE_PUBLIC_ALIAS(DOS$format_wsprintf_printer, libd_format_wsprintf_printer);
DEFINE_PUBLIC_ALIAS(format_wsprintf_printer, libc_format_wsprintf_printer);
DEFINE_PUBLIC_ALIAS(DOS$format_wsnprintf_printer, libd_format_wsnprintf_printer);
DEFINE_PUBLIC_ALIAS(format_wsnprintf_printer, libc_format_wsnprintf_printer);
DEFINE_PUBLIC_ALIAS(DOS$format_wwidth, libd_format_wwidth);
DEFINE_PUBLIC_ALIAS(DOS$format_waprintf_pack, libd_format_waprintf_pack);
DEFINE_PUBLIC_ALIAS(format_waprintf_pack, libc_format_waprintf_pack);
DEFINE_PUBLIC_ALIAS(DOS$format_waprintf_alloc, libd_format_waprintf_alloc);
DEFINE_PUBLIC_ALIAS(format_waprintf_alloc, libc_format_waprintf_alloc);
DEFINE_PUBLIC_ALIAS(DOS$format_waprintf_printer, libd_format_waprintf_printer);
DEFINE_PUBLIC_ALIAS(format_waprintf_printer, libc_format_waprintf_printer);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_FORMAT_PRINTER_C */
