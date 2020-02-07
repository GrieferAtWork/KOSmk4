/* HASH CRC-32:0x1d2f7223 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_format_c16escape_defined
#define __local_format_c16escape_defined 1

#include <bits/wformat-printer.h>
#include <bits/uformat-printer.h>



/* Dependency: "unicode_readutf16_n" from "unicode" */
#ifndef ____localdep_unicode_readutf16_n_defined
#define ____localdep_unicode_readutf16_n_defined 1
#ifdef __CRT_HAVE_unicode_readutf16_n
/* Same as `unicode_readutf16()', but don't read past `text_end' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf16_n,(/*utf-16*/ __CHAR16_TYPE__ const **__restrict __ptext, __CHAR16_TYPE__ const *__text_end),unicode_readutf16_n,(__ptext,__text_end))
#else /* LIBC: unicode_readutf16_n */
#include <local/unicode/unicode_readutf16_n.h>
/* Same as `unicode_readutf16()', but don't read past `text_end' */
#define __localdep_unicode_readutf16_n (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf16_n))
#endif /* unicode_readutf16_n... */
#endif /* !____localdep_unicode_readutf16_n_defined */

__NAMESPACE_LOCAL_BEGIN
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
__LOCAL_LIBC(format_c16escape) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(format_c16escape))(__pc16formatprinter __printer,
                                                              void *__arg,
                                                              /*utf-8*/ __CHAR16_TYPE__ const *__restrict __text,
                                                              __SIZE_TYPE__ __textlen,
                                                              unsigned int __flags) {
#line 209 "kos/src/libc/magic/format-printer.c"
#ifndef __FORMAT_ESCAPE_FNORMAL
#define __FORMAT_ESCAPE_FNORMAL   0x0000 /* Normal quote flags. */
#define __FORMAT_ESCAPE_FPRINTRAW 0x0001 /* Don't surround the quoted text with "..."; */
#define __FORMAT_ESCAPE_FFORCEHEX 0x0002 /* Force hex encoding of all control characters without special strings (`"\n"', etc.). */
#define __FORMAT_ESCAPE_FFORCEOCT 0x0004 /* Force octal encoding of all non-ascii characters. */
#define __FORMAT_ESCAPE_FNOCTRL   0x0008 /* Disable special encoding strings such as `"\r"', `"\n"' or `"\e"' */
#define __FORMAT_ESCAPE_FNOASCII  0x0010 /* Disable regular ascii-characters and print everything using special encodings. */
#define __FORMAT_ESCAPE_FUPPERHEX 0x0020 /* Use uppercase characters for hex (e.g.: `"\xAB"'). */
#endif /* !FORMAT_ESCAPE_FNORMAL */
#define __escape_tooct(__c) ('0'+(__CHAR16_TYPE__)(__CHAR16_TYPE__)(__c))
#ifndef __DECIMALS_SELECTOR
#define __LOCAL_DECIMALS_SELECTOR_DEFINED 1
#define __DECIMALS_SELECTOR  __decimals
	__PRIVATE char const __decimals[2][16] = {
		{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' },
		{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' },
	};
#endif
	__PRIVATE __CHAR16_TYPE__ const __quote[1] = { '\"' };
	__CHAR16_TYPE__ __encoded_text[12]; __SIZE_TYPE__ __encoded_text_size;
	__SSIZE_TYPE__ __result = 0, __temp; char const *__c_hex;
	__CHAR16_TYPE__ const *__textend = __text + __textlen;
	__CHAR16_TYPE__ const *__flush_start = __text;
	__c_hex = __DECIMALS_SELECTOR[!(__flags & __FORMAT_ESCAPE_FUPPERHEX)];
	__encoded_text[0] = '\\';
	if __likely(!(__flags & __FORMAT_ESCAPE_FPRINTRAW)) {
		__temp = (*__printer)(__arg, __quote, 1);
		if __unlikely(__temp < 0)
		goto __err;
		__result += __temp;
	}
	while (__text < __textend) {
		__CHAR16_TYPE__ const *__old_text = __text;

#if 2 == 2
		__UINT32_TYPE__ __ch = __localdep_unicode_readutf16_n((__CHAR16_TYPE__ const **)&__text, __textend);
#else
		__UINT32_TYPE__ __ch = (__UINT32_TYPE__)*__text++;
#endif



		if __unlikely(__ch < 32 || __ch >= 127  || __ch == '\'' ||
		              __ch == '\"' || __ch == '\\' ||
		             (__flags & __FORMAT_ESCAPE_FNOASCII)) {
			/* Flush unwritten direct-copy text. */
			if (__flush_start < __old_text) {
				__temp = (*__printer)(__arg, __flush_start, (__SIZE_TYPE__)(__old_text - __flush_start));
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
			}
			/* Character requires special encoding. */
			if (__ch < 32) {
				/* Control character. */
				if (__flags & __FORMAT_ESCAPE_FNOCTRL) {
__default_ctrl:
					if (__flags & __FORMAT_ESCAPE_FFORCEHEX)
						goto __encode_hex;
__encode_oct:
					if (__text < __textend) {
						__CHAR16_TYPE__ const *__new_text = __text;

#if 2 == 2
						__UINT32_TYPE__ __next_ch = __localdep_unicode_readutf16_n((__CHAR16_TYPE__ const **)&__new_text, __textend);
#else
						__UINT32_TYPE__ __next_ch = (__UINT32_TYPE__)*__new_text++;
#endif



						if (__next_ch >= '0' && __next_ch <= '7')
							goto __encode_hex;
					}
					if (__ch <= 0x07) {
						__encoded_text[1] = __escape_tooct((__ch & 0x00000007));
						__encoded_text_size = 2;
					} else if (__ch <= 0x3f) {
						__encoded_text[1] = __escape_tooct((__ch & 0x00000038) >> 3);
						__encoded_text[2] = __escape_tooct((__ch & 0x00000007));
						__encoded_text_size = 3;
					} else if (__ch <= 0x1ff) {
						__encoded_text[1] = __escape_tooct((__ch & 0x000000c0) >> 6);
						__encoded_text[2] = __escape_tooct((__ch & 0x00000038) >> 3);
						__encoded_text[3] = __escape_tooct((__ch & 0x00000007));
						__encoded_text_size = 4;
					} else if (__ch <= 0xfff) {
						__encoded_text[1] = __escape_tooct((__ch & 0x00000e00) >> 9);
						__encoded_text[2] = __escape_tooct((__ch & 0x000000c0) >> 6);
						__encoded_text[3] = __escape_tooct((__ch & 0x00000038) >> 3);
						__encoded_text[4] = __escape_tooct((__ch & 0x00000007));
						__encoded_text_size = 5;
					} else if (__ch <= 0x7fff) {
						__encoded_text[1] = __escape_tooct((__ch & 0x00007000) >> 12);
						__encoded_text[2] = __escape_tooct((__ch & 0x00000e00) >> 9);
						__encoded_text[3] = __escape_tooct((__ch & 0x000000c0) >> 6);
						__encoded_text[4] = __escape_tooct((__ch & 0x00000038) >> 3);
						__encoded_text[5] = __escape_tooct((__ch & 0x00000007));
						__encoded_text_size = 6;
					} else if (__ch <= 0x3ffff) {
						__encoded_text[1] = __escape_tooct((__ch & 0x00038000) >> 15);
						__encoded_text[2] = __escape_tooct((__ch & 0x00007000) >> 12);
						__encoded_text[3] = __escape_tooct((__ch & 0x00000e00) >> 9);
						__encoded_text[4] = __escape_tooct((__ch & 0x000000c0) >> 6);
						__encoded_text[5] = __escape_tooct((__ch & 0x00000038) >> 3);
						__encoded_text[6] = __escape_tooct((__ch & 0x00000007));
						__encoded_text_size = 7;
					} else if (__ch <= 0x1fffff) {
						__encoded_text[1] = __escape_tooct((__ch & 0x001c0000) >> 18);
						__encoded_text[2] = __escape_tooct((__ch & 0x00038000) >> 15);
						__encoded_text[3] = __escape_tooct((__ch & 0x00007000) >> 12);
						__encoded_text[4] = __escape_tooct((__ch & 0x00000e00) >> 9);
						__encoded_text[5] = __escape_tooct((__ch & 0x000000c0) >> 6);
						__encoded_text[6] = __escape_tooct((__ch & 0x00000038) >> 3);
						__encoded_text[7] = __escape_tooct((__ch & 0x00000007));
						__encoded_text_size = 8;
					} else if (__ch <= 0xffffff) {
						__encoded_text[1] = __escape_tooct((__ch & 0x00e00000) >> 21);
						__encoded_text[2] = __escape_tooct((__ch & 0x001c0000) >> 18);
						__encoded_text[3] = __escape_tooct((__ch & 0x00038000) >> 15);
						__encoded_text[4] = __escape_tooct((__ch & 0x00007000) >> 12);
						__encoded_text[5] = __escape_tooct((__ch & 0x00000e00) >> 9);
						__encoded_text[6] = __escape_tooct((__ch & 0x000000c0) >> 6);
						__encoded_text[7] = __escape_tooct((__ch & 0x00000038) >> 3);
						__encoded_text[8] = __escape_tooct((__ch & 0x00000007));
						__encoded_text_size = 9;
					} else if (__ch <= 0x7ffffff) {
						__encoded_text[1] = __escape_tooct((__ch & 0x07000000) >> 24);
						__encoded_text[2] = __escape_tooct((__ch & 0x00e00000) >> 21);
						__encoded_text[3] = __escape_tooct((__ch & 0x001c0000) >> 18);
						__encoded_text[4] = __escape_tooct((__ch & 0x00038000) >> 15);
						__encoded_text[5] = __escape_tooct((__ch & 0x00007000) >> 12);
						__encoded_text[6] = __escape_tooct((__ch & 0x00000e00) >> 9);
						__encoded_text[7] = __escape_tooct((__ch & 0x000000c0) >> 6);
						__encoded_text[8] = __escape_tooct((__ch & 0x00000038) >> 3);
						__encoded_text[9] = __escape_tooct((__ch & 0x00000007));
						__encoded_text_size = 10;
					} else if (__ch <= 0x3fffffff) {
						__encoded_text[1] = __escape_tooct((__ch & 0x38000000) >> 27);
						__encoded_text[2] = __escape_tooct((__ch & 0x07000000) >> 24);
						__encoded_text[3] = __escape_tooct((__ch & 0x00e00000) >> 21);
						__encoded_text[4] = __escape_tooct((__ch & 0x001c0000) >> 18);
						__encoded_text[5] = __escape_tooct((__ch & 0x00038000) >> 15);
						__encoded_text[6] = __escape_tooct((__ch & 0x00007000) >> 12);
						__encoded_text[7] = __escape_tooct((__ch & 0x00000e00) >> 9);
						__encoded_text[8] = __escape_tooct((__ch & 0x000000c0) >> 6);
						__encoded_text[9] = __escape_tooct((__ch & 0x00000038) >> 3);
						__encoded_text[10] = __escape_tooct((__ch & 0x00000007));
						__encoded_text_size = 11;
					} else {
						__encoded_text[1] = __escape_tooct((__ch & 0xc0000000) >> 30);
						__encoded_text[2] = __escape_tooct((__ch & 0x38000000) >> 27);
						__encoded_text[3] = __escape_tooct((__ch & 0x07000000) >> 24);
						__encoded_text[4] = __escape_tooct((__ch & 0x00e00000) >> 21);
						__encoded_text[5] = __escape_tooct((__ch & 0x001c0000) >> 18);
						__encoded_text[6] = __escape_tooct((__ch & 0x00038000) >> 15);
						__encoded_text[7] = __escape_tooct((__ch & 0x00007000) >> 12);
						__encoded_text[8] = __escape_tooct((__ch & 0x00000e00) >> 9);
						__encoded_text[9] = __escape_tooct((__ch & 0x000000c0) >> 6);
						__encoded_text[10] = __escape_tooct((__ch & 0x00000038) >> 3);
						__encoded_text[11] = __escape_tooct((__ch & 0x00000007));
						__encoded_text_size = 12;
					}
					goto __print_encoded;
				}
__special_control:
				switch (__ch) {
				case '\a':
					__ch = 'a';
					break;
				case '\b':
					__ch = 'b';
					break;
				case '\f':
					__ch = 'f';
					break;
				case '\n':
					__ch = 'n';
					break;
				case '\r':
					__ch = 'r';
					break;
				case '\t':
					__ch = 't';
					break;
				case '\v':
					__ch = 'v';
					break;
				case '\033':
					__ch = 'e';
					break;
				case '\\':
				case '\'':
				case '\"':
					break;
				default:
					goto __default_ctrl;
				}
				__encoded_text[1] = (__CHAR16_TYPE__)__ch;
				__encoded_text_size = 2;
				goto __print_encoded;
			} else if ((__ch == '\\' || __ch == '\'' || __ch == '\"') &&
			          !(__flags & __FORMAT_ESCAPE_FNOCTRL)) {
				goto __special_control;
			} else {
				/* Non-ascii character. */
/*default_nonascii:*/
				if (__flags & __FORMAT_ESCAPE_FFORCEOCT)
					goto __encode_oct;
__encode_hex:
				if (__text < __textend) {
					__CHAR16_TYPE__ const *__new_text = __text;

#if 2 == 2
					__UINT32_TYPE__ __next_ch = __localdep_unicode_readutf16_n((__CHAR16_TYPE__ const **)&__new_text, __textend);
#else
					__UINT32_TYPE__ __next_ch = (__UINT32_TYPE__)*__new_text++;
#endif



					if ((__next_ch >= 'a' && __next_ch <= 'f') ||
					    (__next_ch >= 'A' && __next_ch <= 'F') ||
					    (__next_ch >= '0' && __next_ch <= '9'))
						goto __encode_uni;
				}
				if (__ch <= 0xf) {
					__encoded_text[1] = 'x';
					__encoded_text[2] = __c_hex[__ch];
					__encoded_text_size = 3;
				} else if (__ch <= 0xff) {
					__encoded_text[1] = 'x';
					__encoded_text[2] = __c_hex[(__ch & 0x000000f0) >> 4];
					__encoded_text[3] = __c_hex[__ch & 0x0000000f];
					__encoded_text_size = 4;
				} else {
__encode_uni:
					if (__ch <= 0xffff) {
						__encoded_text[1] = 'u';
						__encoded_text[2] = __c_hex[(__ch & 0x0000f000) >> 12];
						__encoded_text[3] = __c_hex[(__ch & 0x00000f00) >> 8];
						__encoded_text[4] = __c_hex[(__ch & 0x000000f0) >> 4];
						__encoded_text[5] = __c_hex[__ch & 0x0000000f];
						__encoded_text_size = 6;
					} else {
						__encoded_text[1] = 'U';
						__encoded_text[2] = __c_hex[(__ch & 0xf0000000) >> 28];
						__encoded_text[3] = __c_hex[(__ch & 0x0f000000) >> 24];
						__encoded_text[4] = __c_hex[(__ch & 0x00f00000) >> 20];
						__encoded_text[5] = __c_hex[(__ch & 0x000f0000) >> 16];
						__encoded_text[6] = __c_hex[(__ch & 0x0000f000) >> 12];
						__encoded_text[7] = __c_hex[(__ch & 0x00000f00) >> 8];
						__encoded_text[8] = __c_hex[(__ch & 0x000000f0) >> 4];
						__encoded_text[9] = __c_hex[__ch & 0x0000000f];
						__encoded_text_size = 10;
					}
				}
__print_encoded:
				__temp = (*__printer)(__arg, __encoded_text, __encoded_text_size);
				if __unlikely(__temp < 0)
				goto __err;
				__result += __temp;
			}
			__flush_start = __text;
		}
	}
/*done:*/
	if (__flush_start < __text) {
		__temp = (*__printer)(__arg, __flush_start, (__SIZE_TYPE__)(__text - __flush_start));
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;
	}
	if __likely(!(__flags & __FORMAT_ESCAPE_FPRINTRAW)) {
		__temp = (*__printer)(__arg, __quote, 1);
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;
	}
	return __result;
__err:
	return __temp;
#ifdef __LOCAL_DECIMALS_SELECTOR_DEFINED
#undef __LOCAL_DECIMALS_SELECTOR_DEFINED
#undef __DECIMALS_SELECTOR
#endif /* LOCAL_DECIMALS_SELECTOR_DEFINED */
#undef __escape_tooct
}
__NAMESPACE_LOCAL_END
#endif /* !__local_format_c16escape_defined */
