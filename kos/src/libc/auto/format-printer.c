/* HASH CRC-32:0xbd6c092f */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_FORMAT_PRINTER_C
#define GUARD_LIBC_AUTO_FORMAT_PRINTER_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "format-printer.h"
#include "../user/ctype.h"
#include "parts.wchar.format-printer.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/unicode.h"

DECL_BEGIN

#include "../libc/dl.h"      /* Use libc's relocation-optimized dl* functions. */
#include "../auto/string.h"  /* Dependency of `#include <libc/template/format-printf.h>' */
#include "../user/unicode.h" /* Dependency of `#include <libc/template/format-scanf.h>' */
/**/
#include <hybrid/__assert.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <hybrid/__alloca.h> /* Dependency of `#include <libc/template/format-printf.h>' */

#include <bits/math-constants.h>
#include <bits/types.h> /* Dependency of `#include <libc/template/format-printf.h>' */

#include <libc/template/itoa_digits.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <libdisasm/disassembler.h>    /* Dependency of `#include <libc/template/format-printf.h>' */
#ifdef __KERNEL__
#include <kernel/addr2line.h>
#else /* __KERNEL__ */
#include <libdebuginfo/addr2line.h>
#endif /* !__KERNEL__ */
#include <hybrid/__alloca.h>
#include <libc/string.h>
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
INTERN ATTR_SECTION(".text.crt.string.format") NONNULL((1)) ssize_t
NOTHROW_CB(LIBCCALL libc_format_repeat)(pformatprinter printer,
                                        void *arg,
                                        char ch,
                                        size_t num_repetitions) {
	ssize_t result, temp;
#ifdef __hybrid_alloca
	char *buffer;
	if likely(num_repetitions <= 64) {
		buffer = (char *)__hybrid_alloca(num_repetitions * sizeof(char));
		__libc_memsetc(buffer, ch, num_repetitions, __SIZEOF_CHAR__);
		return (*printer)(arg, buffer, num_repetitions);
	}
	buffer = (char *)__hybrid_alloca(64 * sizeof(char));
	__libc_memsetc(buffer, ch, 64, __SIZEOF_CHAR__);
#else /* __hybrid_alloca */
	char buffer[64];
	if likely(num_repetitions <= 64) {
		__libc_memsetc(buffer, ch, num_repetitions, __SIZEOF_CHAR__);
		return (*printer)(arg, buffer, num_repetitions);
	}
	__libc_memsetc(buffer, ch, 64, __SIZEOF_CHAR__);
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
#include <libc/template/hex.h>
/* >> format_escape(3)
 * Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: "\"Hello \"World\" W\nhat a great day.\""
 * Output #2:   "Hello \"World\" W\nhat a great day"
 * NOTE: Output  #2 is generated if `FORMAT_ESCAPE_FPRINTRAW' is set
 * This  function  escapes  all  control  and  non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a  behavior that may be  modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: printer: A function called for all quoted portions of the text
 * @param: textlen: The total number of bytes to escape, starting at `text' */
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_INS(3, 4) NONNULL((1)) ssize_t
NOTHROW_CB(LIBCCALL libc_format_escape)(pformatprinter printer,
                                        void *arg,
                                        char const *__restrict text,
                                        size_t textlen,
                                        unsigned int flags) {
	__PRIVATE char const quote[1] = { '\"' };
	char encoded_text[12]; size_t encoded_text_size;
	ssize_t result = 0, temp;
	char const *textend = text + textlen;
	char const *flush_start = text;
	encoded_text[0] = '\\';
	if likely(!(flags & 0x0001)) {
		temp = (*printer)(arg, quote, 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	while (text < textend) {
		char const *old_text = text;
		uint32_t ch;

		ch = libc_unicode_readutf8_n((char const **)&text, textend);






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
						char const *new_text = text;
						uint32_t next_ch;

						next_ch = libc_unicode_readutf8_n((char const **)&new_text, textend);






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
				encoded_text[1] = (char)ch;
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
					char const *new_text = text;
					char32_t next_ch;

					next_ch = libc_unicode_readutf8_n((char const **)&new_text, textend);






					if (__libc_ishex(next_ch))
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
#include <hybrid/__unaligned.h>
#include <hybrid/byteorder.h>
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
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_INS(3, 4) NONNULL((1)) ssize_t
NOTHROW_CB(LIBCCALL libc_format_hexdump)(pformatprinter printer,
                                         void *arg,
                                         void const *__restrict data,
                                         size_t size,
                                         size_t linesize,
                                         unsigned int flags) {
	__PRIVATE char const lf[1] = { '\n' };
	byte_t const *line_data;
	char buffer[
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
					u16 w = __hybrid_unaligned_get16(line_data + i);
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
					u32 l = __hybrid_unaligned_get32(line_data + i);
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
					u64 q = __hybrid_unaligned_get64(line_data + i);
					dst = buffer + 16;
					while (dst > buffer) {
						*--dst = itoa_digit(!(flags & 0x0001), q & 0xf);
						q >>= 4;
					}
#else /* __SIZEOF_POINTER__ >= 8 */
					u32 a, b;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
					a = __hybrid_unaligned_get32(line_data + i + 4);
					b = __hybrid_unaligned_get32(line_data + i);
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
					a = __hybrid_unaligned_get32(line_data + i);
					b = __hybrid_unaligned_get32(line_data + i + 4);
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
				temp = libc_format_repeat(printer, arg, ' ', tailspace_count);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
		if (!(flags & 0x0010)) {
			for (i = 0; i < line_len; ++i) {
				char b = (char)(unsigned char)line_data[i];
				if (!libc_isprint((unsigned char)b))
					b = '.';
				temp = (*printer)(arg, &b, 1);
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
#include <libc/parts.uchar.string.h>
#include <libc/errno.h>
#include <hybrid/__assert.h>
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
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) NONNULL((1)) ssize_t
NOTHROW_CB(LIBCCALL libc_format_vprintf)(pformatprinter printer,
                                         void *arg,
                                         char const *__restrict format,
                                         va_list args) {
#ifndef __INTELLISENSE__
#define __FORMAT_PRINTER           printer
#define __FORMAT_ARG               arg
#define __FORMAT_FORMAT            format
#define __FORMAT_ARGS              args
#define __CHAR_TYPE                char
#define __CHAR_SIZE                __SIZEOF_CHAR__
#define __FORMAT_STRERROR          libc_strerror
#define __FORMAT_REPEAT            libc_format_repeat
#define __FORMAT_HEXDUMP           libc_format_hexdump
#define __FORMAT_WIDTH             libc_format_width
#define __FORMAT_ESCAPE            libc_format_escape
#define __FORMAT_WIDTH16           libd_format_wwidth
#define __FORMAT_WIDTH32           libc_format_wwidth
#define __FORMAT_ESCAPE16          libd_format_wescape
#define __FORMAT_ESCAPE32          libc_format_wescape
#define __FORMAT_UNICODE_WRITECHAR libc_unicode_writeutf8
#define __FORMAT_UNICODE_FORMAT16  libd_format_wto8
#define __FORMAT_UNICODE_FORMAT32  libc_format_wto8
#include <libc/template/format-printf.h>
#endif /* !__INTELLISENSE__ */
}
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.string.format") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) NONNULL((1)) ssize_t
NOTHROW_CB(VLIBDCALL libd_format_printf)(pformatprinter printer,
                                         void *arg,
                                         char const *__restrict format,
                                         ...) {
	ssize_t result;
	va_list args;
	va_start(args, format);
	result = libc_format_vprintf(printer, arg, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) NONNULL((1)) ssize_t
NOTHROW_CB(VLIBCCALL libc_format_printf)(pformatprinter printer,
                                         void *arg,
                                         char const *__restrict format,
                                         ...) {
	ssize_t result;
	va_list args;
	va_start(args, format);
	result = libc_format_vprintf(printer, arg, format, args);
	va_end(args);
	return result;
}
#include <libc/unicode.h>
#include <bits/math-constants.h>
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_IN(4) ATTR_LIBC_SCANF(4, 0) NONNULL((1, 2)) ssize_t
NOTHROW_CB(LIBCCALL libc_format_vscanf)(pformatgetc pgetc,
                                        pformatungetc pungetc,
                                        void *arg,
                                        char const *__restrict format,
                                        va_list args) {
#ifndef __INTELLISENSE__
#define __CHAR_TYPE      char
#define __CHAR_SIZE      __SIZEOF_CHAR__
#define __FORMAT_PGETC   pgetc
#define __FORMAT_PUNGETC pungetc
#define __FORMAT_ARG     arg
#define __FORMAT_FORMAT  format
#define __FORMAT_ARGS    args
#include <libc/template/format-scanf.h>
#endif /* !__INTELLISENSE__ */
}
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.string.format") ATTR_IN(4) ATTR_LIBC_SCANF(4, 5) NONNULL((1, 2)) ssize_t
NOTHROW_CB(VLIBDCALL libd_format_scanf)(pformatgetc pgetc,
                                        pformatungetc pungetc,
                                        void *arg,
                                        char const *__restrict format,
                                        ...) {
	ssize_t result;
	va_list args;
	va_start(args, format);
	result = libc_format_vscanf(pgetc, pungetc, arg, format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_IN(4) ATTR_LIBC_SCANF(4, 5) NONNULL((1, 2)) ssize_t
NOTHROW_CB(VLIBCCALL libc_format_scanf)(pformatgetc pgetc,
                                        pformatungetc pungetc,
                                        void *arg,
                                        char const *__restrict format,
                                        ...) {
	ssize_t result;
	va_list args;
	va_start(args, format);
	result = libc_format_vscanf(pgetc, pungetc, arg, format, args);
	va_end(args);
	return result;
}
/* >> format_sprintf_printer(3)
 * Format-printer implementation for printing to a string buffer like `sprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_INS(2, 3) NONNULL((1)) ssize_t
NOTHROW_NCX(__FORMATPRINTER_CC libc_format_sprintf_printer)(void *arg,
                                                            char const *__restrict data,
                                                            size_t datalen) {
	*(char **)arg = (char *)libc_mempcpyc(*(char **)arg, data, datalen, sizeof(char));
	return (ssize_t)datalen;
}
/* >> format_snprintf_printer(3)
 * Format-printer implementation for printing to a string buffer like `snprintf(3)' would
 * NOTES:
 *  - No trailing NUL-character is implicitly appended !!!
 *  - The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 *  - The number  of required  characters is  `arg->sd_buffer - <orig_buf>', and  is
 *    equal to the sum of return values of all calls to `format_snprintf_printer(3)'
 *  - There is no error-case, so this function never returns a negative result */
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_INS(2, 3) NONNULL((1)) ssize_t
NOTHROW_NCX(__FORMATPRINTER_CC libc_format_snprintf_printer)(void *arg,
                                                             char const *__restrict data,
                                                             size_t datalen) {
	struct __local_format_snprintf_data {
		char  *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		size_t sd_bufsiz; /* Remaining buffer size. */
	};
	struct __local_format_snprintf_data *ctrl;
	size_t result = datalen;
	ctrl = (struct __local_format_snprintf_data *)arg;
	if (result > ctrl->sd_bufsiz)
		result = ctrl->sd_bufsiz;
	libc_memcpyc(ctrl->sd_buffer, data, result, sizeof(char));
	ctrl->sd_buffer += datalen;
	ctrl->sd_bufsiz -= result;
	return (ssize_t)datalen;
}
#include <libc/template/unicode_utf8seqlen.h>
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_PURE ATTR_INS(2, 3) NONNULL((2)) ssize_t
NOTHROW_NCX(__FORMATPRINTER_CC libc_format_width)(void *arg,
                                                  char const *__restrict data,
                                                  size_t datalen) {
	size_t result = 0;
	char const *iter, *end;
	(void)arg;
	end = (iter = data) + datalen;
	while (iter < end) {
		u8 len;
		len = unicode_utf8seqlen[(u8)*iter];
		if unlikely(!len)
			len = 1;
		iter += len;
		++result;
	}
	return (ssize_t)result;
}
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_CONST ATTR_INS(2, 3) NONNULL((2)) ssize_t
NOTHROW(__FORMATPRINTER_CC libc_format_length)(void *arg,
                                               char const *__restrict data,
                                               size_t datalen) {
	(void)arg;
	(void)data;
	return (ssize_t)datalen;
}
#ifndef __KERNEL__
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size (including space for trailing NUL) */
	__SIZE_TYPE__ ap_used;  /* Used buffer size (excluding trailing NUL, which only gets added during pack) */
};
#endif /* !__format_aprintf_data_defined */
/* >> format_aprintf_pack(3)
 * Pack  and  finalize  a  given  aprintf  format printer
 * Together with `format_aprintf_printer(3)', the aprintf
 * format  printer sub-system should  be used as follows:
 * >> char *result;
 * >> ssize_t error;
 * >> struct format_aprintf_data p = FORMAT_APRINTF_DATA_INIT;
 * >> error = format_printf(&format_aprintf_printer, &p, "%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_aprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_aprintf_pack(&p, NULL);
 * >> // `return' is an malloc()'d string "Hello World"
 * >> return result;
 * WARNING: Note that `format_aprintf_pack(3)' is able to return `NULL' as well,
 *          but  will  finalize  the  given   aprintf  printer  an  all   cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free(3)'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `strlen(return)' when NUL characters  were
 *                  printed to the aprintf-printer at one point.
 *                  (e.g. `format_aprintf_printer(&my_printer, "\0", 1)') */
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_INOUT(1) ATTR_OUT_OPT(2) char *
NOTHROW_NCX(LIBCCALL libc_format_aprintf_pack)(struct format_aprintf_data *__restrict self,
                                               size_t *pstrlen) {
	/* Free unused buffer memory. */
	char *result;
	if (self->ap_avail != 1) {

		char *newbuf;
		newbuf = (char *)libc_realloc(self->ap_base,
		                         (self->ap_used + 1) *
		                         sizeof(char));
		if likely(newbuf)
			self->ap_base = newbuf;

	} else {
		if unlikely(!self->ap_used) {
			/* Special case: Nothing was printed. */
			__hybrid_assert(!self->ap_base);

			self->ap_base = (char *)libc_malloc(1 * sizeof(char));
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
	self->ap_base  = (char *)__UINT32_C(0xcccccccc);
	self->ap_avail = __UINT32_C(0xcccccccc);
	self->ap_used  = __UINT32_C(0xcccccccc);
#elif __SIZEOF_POINTER__ == 8
	self->ap_base  = (char *)__UINT64_C(0xcccccccccccccccc);
	self->ap_avail = __UINT64_C(0xcccccccccccccccc);
	self->ap_used  = __UINT64_C(0xcccccccccccccccc);
#endif /* ... */
#endif /* !NDEBUG && !NDEBUG_FINI */
	return result;
}
#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size (including space for trailing NUL) */
	__SIZE_TYPE__ ap_used;  /* Used buffer size (excluding trailing NUL, which only gets added during pack) */
};
#endif /* !__format_aprintf_data_defined */
/* >> format_aprintf_alloc(3)
 * Allocate  a   buffer  of   `num_chars'  characters   at  the   end  of   `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
INTERN ATTR_SECTION(".text.crt.string.format") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_format_aprintf_alloc)(struct format_aprintf_data *__restrict self,
                                                size_t num_chars) {
	char *result;
	if (num_chars >= self->ap_avail) {
		char *newbuf;
		size_t min_alloc = self->ap_used + num_chars + 1;
		size_t new_alloc = self->ap_used + self->ap_avail;
		if (!new_alloc)
			new_alloc = 4;
		do {
			new_alloc *= 2;
		} while (new_alloc < min_alloc);
		newbuf = (char *)libc_realloc(self->ap_base, new_alloc * sizeof(char));
		if unlikely(!newbuf) {
			new_alloc = min_alloc;
			newbuf    = (char *)libc_realloc(self->ap_base, new_alloc * sizeof(char));
			if unlikely(!newbuf)
				goto err;
		}
		__hybrid_assert(new_alloc > self->ap_used + num_chars);
		self->ap_base  = newbuf;
		self->ap_avail = new_alloc - self->ap_used;
	}
	result = self->ap_base + self->ap_used;
	self->ap_avail -= num_chars;
	self->ap_used  += num_chars;
	return result;
err:
	return NULL;
}
/* >> format_aprintf_printer(3)
 * Print data to  a dynamically  allocated heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
INTERN ATTR_SECTION(".text.crt.string.format") WUNUSED ATTR_INS(2, 3) NONNULL((1)) ssize_t
NOTHROW_NCX(__FORMATPRINTER_CC libc_format_aprintf_printer)(void *arg,
                                                            char const *__restrict data,
                                                            size_t datalen) {
	char *buf;
	buf = libc_format_aprintf_alloc((struct format_aprintf_data *)arg,
	                           datalen);
	if unlikely(!buf)
		goto err;
	libc_memcpyc(buf, data, datalen, sizeof(char));
	return (ssize_t)datalen;
err:
	return -1;
}
#endif /* !__KERNEL__ */

DECL_END

DEFINE_PUBLIC_ALIAS_P(format_repeat,libc_format_repeat,NONNULL((1)),ssize_t,NOTHROW_CB,LIBCCALL,(pformatprinter printer, void *arg, char ch, size_t num_repetitions),(printer,arg,ch,num_repetitions));
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(format_quote,libc_format_escape,ATTR_INS(3, 4) NONNULL((1)),ssize_t,NOTHROW_CB,LIBCCALL,(pformatprinter printer, void *arg, char const *__restrict text, size_t textlen, unsigned int flags),(printer,arg,text,textlen,flags));
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P(format_escape,libc_format_escape,ATTR_INS(3, 4) NONNULL((1)),ssize_t,NOTHROW_CB,LIBCCALL,(pformatprinter printer, void *arg, char const *__restrict text, size_t textlen, unsigned int flags),(printer,arg,text,textlen,flags));
DEFINE_PUBLIC_ALIAS_P(format_hexdump,libc_format_hexdump,ATTR_INS(3, 4) NONNULL((1)),ssize_t,NOTHROW_CB,LIBCCALL,(pformatprinter printer, void *arg, void const *__restrict data, size_t size, size_t linesize, unsigned int flags),(printer,arg,data,size,linesize,flags));
DEFINE_PUBLIC_ALIAS_P(format_vprintf,libc_format_vprintf,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) NONNULL((1)),ssize_t,NOTHROW_CB,LIBCCALL,(pformatprinter printer, void *arg, char const *__restrict format, va_list args),(printer,arg,format,args));
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$format_printf,libd_format_printf,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) NONNULL((1)),ssize_t,NOTHROW_CB,VLIBDCALL,(pformatprinter printer, void *arg, char const *__restrict format, ...),(printer,arg,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P(format_printf,libc_format_printf,ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) NONNULL((1)),ssize_t,NOTHROW_CB,VLIBCCALL,(pformatprinter printer, void *arg, char const *__restrict format, ...),(printer,arg,format,));
DEFINE_PUBLIC_ALIAS_P(format_vscanf,libc_format_vscanf,ATTR_IN(4) ATTR_LIBC_SCANF(4, 0) NONNULL((1, 2)),ssize_t,NOTHROW_CB,LIBCCALL,(pformatgetc pgetc, pformatungetc pungetc, void *arg, char const *__restrict format, va_list args),(pgetc,pungetc,arg,format,args));
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS_P(DOS$format_scanf,libd_format_scanf,ATTR_IN(4) ATTR_LIBC_SCANF(4, 5) NONNULL((1, 2)),ssize_t,NOTHROW_CB,VLIBDCALL,(pformatgetc pgetc, pformatungetc pungetc, void *arg, char const *__restrict format, ...),(pgetc,pungetc,arg,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P(format_scanf,libc_format_scanf,ATTR_IN(4) ATTR_LIBC_SCANF(4, 5) NONNULL((1, 2)),ssize_t,NOTHROW_CB,VLIBCCALL,(pformatgetc pgetc, pformatungetc pungetc, void *arg, char const *__restrict format, ...),(pgetc,pungetc,arg,format,));
DEFINE_PUBLIC_ALIAS_P(format_sprintf_printer,libc_format_sprintf_printer,ATTR_INS(2, 3) NONNULL((1)),ssize_t,NOTHROW_NCX,__FORMATPRINTER_CC,(void *arg, char const *__restrict data, size_t datalen),(arg,data,datalen));
DEFINE_PUBLIC_ALIAS_P(format_snprintf_printer,libc_format_snprintf_printer,ATTR_INS(2, 3) NONNULL((1)),ssize_t,NOTHROW_NCX,__FORMATPRINTER_CC,(void *arg, char const *__restrict data, size_t datalen),(arg,data,datalen));
DEFINE_PUBLIC_ALIAS_P(format_width,libc_format_width,ATTR_PURE ATTR_INS(2, 3) NONNULL((2)),ssize_t,NOTHROW_NCX,__FORMATPRINTER_CC,(void *arg, char const *__restrict data, size_t datalen),(arg,data,datalen));
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(format_wwidth,libc_format_length,ATTR_CONST ATTR_INS(2, 3) NONNULL((2)),ssize_t,NOTHROW,__FORMATPRINTER_CC,(void *arg, char const *__restrict data, size_t datalen),(arg,data,datalen));
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS_P(format_length,libc_format_length,ATTR_CONST ATTR_INS(2, 3) NONNULL((2)),ssize_t,NOTHROW,__FORMATPRINTER_CC,(void *arg, char const *__restrict data, size_t datalen),(arg,data,datalen));
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(format_aprintf_pack,libc_format_aprintf_pack,ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_INOUT(1) ATTR_OUT_OPT(2),char *,NOTHROW_NCX,LIBCCALL,(struct format_aprintf_data *__restrict self, size_t *pstrlen),(self,pstrlen));
DEFINE_PUBLIC_ALIAS_P(format_aprintf_alloc,libc_format_aprintf_alloc,ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INOUT(1),char *,NOTHROW_NCX,LIBCCALL,(struct format_aprintf_data *__restrict self, size_t num_chars),(self,num_chars));
DEFINE_PUBLIC_ALIAS_P(format_aprintf_printer,libc_format_aprintf_printer,WUNUSED ATTR_INS(2, 3) NONNULL((1)),ssize_t,NOTHROW_NCX,__FORMATPRINTER_CC,(void *arg, char const *__restrict data, size_t datalen),(arg,data,datalen));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_FORMAT_PRINTER_C */
