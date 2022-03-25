/* HASH CRC-32:0x2b29e7d9 */
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
#ifndef GUARD_LIBC_AUTO_UNICODE_C
#define GUARD_LIBC_AUTO_UNICODE_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/unicode.h"

DECL_BEGIN

#include <libc/template/unicode_utf8seqlen.h>
/* >> unicode_readutf8(3)
 * Read a single Unicode character from a given UTF-8 string */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1)) char32_t
NOTHROW_NCX(LIBCCALL libc_unicode_readutf8)(char const **__restrict ptext) {
	char32_t result;
	char const *iter = *ptext;
	result = (char32_t)(u8)*iter++;
	if (result >= 0xc0) {
		switch (unicode_utf8seqlen[result]) {

		case 0:
		case 1:
			break;

		case 2:
			result  = (result & 0x1f) << 6;
			result |= (iter[0] & 0x3f);
			iter += 1;
			break;

		case 3:
			result  = (result & 0x0f) << 12;
			result |= (iter[0] & 0x3f) << 6;
			result |= (iter[1] & 0x3f);
			iter += 2;
			break;

		case 4:
			result  = (result & 0x07) << 18;
			result |= (iter[0] & 0x3f) << 12;
			result |= (iter[1] & 0x3f) << 6;
			result |= (iter[2] & 0x3f);
			iter += 3;
			break;

		case 5:
			result  = (result & 0x03) << 24;
			result |= (iter[0] & 0x3f) << 18;
			result |= (iter[1] & 0x3f) << 12;
			result |= (iter[2] & 0x3f) << 6;
			result |= (iter[3] & 0x3f);
			iter += 4;
			break;

		case 6:
			result  = (result & 0x01) << 30;
			result |= (iter[0] & 0x3f) << 24;
			result |= (iter[1] & 0x3f) << 18;
			result |= (iter[2] & 0x3f) << 12;
			result |= (iter[3] & 0x3f) << 6;
			result |= (iter[4] & 0x3f);
			iter += 5;
			break;

		case 7:
			result  = (iter[0] & 0x03/*0x3f*/) << 30;
			result |= (iter[1] & 0x3f) << 24;
			result |= (iter[2] & 0x3f) << 18;
			result |= (iter[3] & 0x3f) << 12;
			result |= (iter[4] & 0x3f) << 6;
			result |= (iter[5] & 0x3f);
			iter += 6;
			break;

		case 8:
			/*result = (iter[0] & 0x3f) << 36;*/
			result  = (iter[1] & 0x03/*0x3f*/) << 30;
			result |= (iter[2] & 0x3f) << 24;
			result |= (iter[3] & 0x3f) << 18;
			result |= (iter[4] & 0x3f) << 12;
			result |= (iter[5] & 0x3f) << 6;
			result |= (iter[6] & 0x3f);
			iter += 7;
			break;

		default:
			__builtin_unreachable();
		}
	}
	*ptext = iter;
	return result;
}
/* >> unicode_readutf8_rev(3)
 * Same  as  `unicode_readutf8',  but read  backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1)) char32_t
NOTHROW_NCX(LIBCCALL libc_unicode_readutf8_rev)(char const **__restrict ptext) {
	char32_t result;
	char const *iter = *ptext;
	uint8_t seqlen = 1;
	for (;;) {
		result = (unsigned char)*--iter;
		if ((result & 0xc0) != 0x80)
			break;
		if (seqlen >= 8)
			break;
		++seqlen;
	}
	if (result >= 0xc0) {
		switch (seqlen) {

		case 0:
		case 1:
			break;

		case 2:
			result  = (result & 0x1f) << 6;
			result |= (iter[0] & 0x3f);
			break;

		case 3:
			result  = (result & 0x0f) << 12;
			result |= (iter[0] & 0x3f) << 6;
			result |= (iter[1] & 0x3f);
			break;

		case 4:
			result  = (result & 0x07) << 18;
			result |= (iter[0] & 0x3f) << 12;
			result |= (iter[1] & 0x3f) << 6;
			result |= (iter[2] & 0x3f);
			break;

		case 5:
			result  = (result & 0x03) << 24;
			result |= (iter[0] & 0x3f) << 18;
			result |= (iter[1] & 0x3f) << 12;
			result |= (iter[2] & 0x3f) << 6;
			result |= (iter[3] & 0x3f);
			break;

		case 6:
			result  = (result & 0x01) << 30;
			result |= (iter[0] & 0x3f) << 24;
			result |= (iter[1] & 0x3f) << 18;
			result |= (iter[2] & 0x3f) << 12;
			result |= (iter[3] & 0x3f) << 6;
			result |= (iter[4] & 0x3f);
			break;

		case 7:
			result  = (iter[0] & 0x03/*0x3f*/) << 30;
			result |= (iter[1] & 0x3f) << 24;
			result |= (iter[2] & 0x3f) << 18;
			result |= (iter[3] & 0x3f) << 12;
			result |= (iter[4] & 0x3f) << 6;
			result |= (iter[5] & 0x3f);
			break;

		case 8:
			/*result = (iter[0] & 0x3f) << 36;*/
			result  = (iter[1] & 0x03/*0x3f*/) << 30;
			result |= (iter[2] & 0x3f) << 24;
			result |= (iter[3] & 0x3f) << 18;
			result |= (iter[4] & 0x3f) << 12;
			result |= (iter[5] & 0x3f) << 6;
			result |= (iter[6] & 0x3f);
			break;

		default:
			__builtin_unreachable();
		}
	}
	*ptext = iter;
	return result;
}
/* >> unicode_readutf8_n(3)
 * Same as `unicode_readutf8()', but don't read past `text_end' */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1, 2)) char32_t
NOTHROW_NCX(LIBCCALL libc_unicode_readutf8_n)(char const **__restrict ptext,
                                              char const *text_end) {
	char32_t result;
	char const *iter = *ptext;
	if __unlikely(iter >= text_end)
		return 0;
	result = (char32_t)(u8)*iter++;
	if (result >= 0xc0) {
		u8 len;
		len = unicode_utf8seqlen[result];
		if (iter + len-1 >= text_end)
			len = (u8)(text_end - iter)+1;
		switch (len) {

		case 0:
		case 1:
			break;

		case 2:
			result  = (result & 0x1f) << 6;
			result |= (iter[0] & 0x3f);
			iter += 1;
			break;

		case 3:
			result  = (result & 0x0f) << 12;
			result |= (iter[0] & 0x3f) << 6;
			result |= (iter[1] & 0x3f);
			iter += 2;
			break;

		case 4:
			result  = (result & 0x07) << 18;
			result |= (iter[0] & 0x3f) << 12;
			result |= (iter[1] & 0x3f) << 6;
			result |= (iter[2] & 0x3f);
			iter += 3;
			break;

		case 5:
			result  = (result & 0x03) << 24;
			result |= (iter[0] & 0x3f) << 18;
			result |= (iter[1] & 0x3f) << 12;
			result |= (iter[2] & 0x3f) << 6;
			result |= (iter[3] & 0x3f);
			iter += 4;
			break;

		case 6:
			result  = (result & 0x01) << 30;
			result |= (iter[0] & 0x3f) << 24;
			result |= (iter[1] & 0x3f) << 18;
			result |= (iter[2] & 0x3f) << 12;
			result |= (iter[3] & 0x3f) << 6;
			result |= (iter[4] & 0x3f);
			iter += 5;
			break;

		case 7:
			result  = (iter[0] & 0x03/*0x3f*/) << 30;
			result |= (iter[1] & 0x3f) << 24;
			result |= (iter[2] & 0x3f) << 18;
			result |= (iter[3] & 0x3f) << 12;
			result |= (iter[4] & 0x3f) << 6;
			result |= (iter[5] & 0x3f);
			iter += 6;
			break;

		case 8:
			/*result = (iter[0] & 0x3f) << 36;*/
			result  = (iter[1] & 0x03/*0x3f*/) << 30;
			result |= (iter[2] & 0x3f) << 24;
			result |= (iter[3] & 0x3f) << 18;
			result |= (iter[4] & 0x3f) << 12;
			result |= (iter[5] & 0x3f) << 6;
			result |= (iter[6] & 0x3f);
			iter += 7;
			break;

		default:
			__builtin_unreachable();
		}
	}
	*ptext = iter;
	return result;
}
/* >> unicode_readutf8_rev_n(3)
 * Same as `unicode_readutf8_rev()', but don't read ahead of `text_start' */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1, 2)) char32_t
NOTHROW_NCX(LIBCCALL libc_unicode_readutf8_rev_n)(char const **__restrict ptext,
                                                  char const *text_start) {
	char32_t result;
	char const *iter = *ptext;
	uint8_t seqlen = 1;
	if __unlikely(iter <= text_start)
		return 0;
	for (;;) {
		result = (unsigned char)*--iter;
		if ((result & 0xc0) != 0x80)
			break;
		if (seqlen >= 8)
			break;
		++seqlen;
		if (iter <= text_start)
			break;
	}
	if (result >= 0xc0) {
		switch (seqlen) {

		case 0:
		case 1:
			break;

		case 2:
			result  = (result & 0x1f) << 6;
			result |= (iter[0] & 0x3f);
			break;

		case 3:
			result  = (result & 0x0f) << 12;
			result |= (iter[0] & 0x3f) << 6;
			result |= (iter[1] & 0x3f);
			break;

		case 4:
			result  = (result & 0x07) << 18;
			result |= (iter[0] & 0x3f) << 12;
			result |= (iter[1] & 0x3f) << 6;
			result |= (iter[2] & 0x3f);
			break;

		case 5:
			result  = (result & 0x03) << 24;
			result |= (iter[0] & 0x3f) << 18;
			result |= (iter[1] & 0x3f) << 12;
			result |= (iter[2] & 0x3f) << 6;
			result |= (iter[3] & 0x3f);
			break;

		case 6:
			result  = (result & 0x01) << 30;
			result |= (iter[0] & 0x3f) << 24;
			result |= (iter[1] & 0x3f) << 18;
			result |= (iter[2] & 0x3f) << 12;
			result |= (iter[3] & 0x3f) << 6;
			result |= (iter[4] & 0x3f);
			break;

		case 7:
			result  = (iter[0] & 0x03/*0x3f*/) << 30;
			result |= (iter[1] & 0x3f) << 24;
			result |= (iter[2] & 0x3f) << 18;
			result |= (iter[3] & 0x3f) << 12;
			result |= (iter[4] & 0x3f) << 6;
			result |= (iter[5] & 0x3f);
			break;

		case 8:
			/*result = (iter[0] & 0x3f) << 36;*/
			result  = (iter[1] & 0x03/*0x3f*/) << 30;
			result |= (iter[2] & 0x3f) << 24;
			result |= (iter[3] & 0x3f) << 18;
			result |= (iter[4] & 0x3f) << 12;
			result |= (iter[5] & 0x3f) << 6;
			result |= (iter[6] & 0x3f);
			break;

		default:
			__builtin_unreachable();
		}
	}
	*ptext = iter;
	return result;
}
/* >> unicode_readutf16(3)
 * Read a single Unicode character from a given UTF-16 string */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1)) char32_t
NOTHROW_NCX(LIBCCALL libc_unicode_readutf16)(char16_t const **__restrict ptext) {
	char32_t result;
	char16_t const *text = *ptext;
	result = (char32_t)(u16)*text++;
	if (result >= 0xd800 &&
	    result <= 0xdbff) {
		result -= 0xd800;
		result <<= 10;
		result += 0x10000 - 0xdc00;
		result += *text++; /* low surrogate */
	}
	*ptext = text;
	return result;
}
/* >> unicode_readutf16_n(3)
 * Same as `unicode_readutf16()', but don't read past `text_end' */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1, 2)) char32_t
NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_n)(char16_t const **__restrict ptext,
                                               char16_t const *text_end) {
	char32_t result;
	char16_t const *text = *ptext;
	if (text >= text_end)
		return 0;
	result = (char32_t)(u16)*text++;
	if (result >= 0xd800 &&
	    result <= 0xdbff &&
	    text < text_end) {
		result -= 0xd800;
		result <<= 10;
		result += 0x10000 - 0xdc00;
		result += *text++; /* low surrogate */
	}
	*ptext = text;
	return result;
}
#include <hybrid/__byteswap.h>
/* >> unicode_readutf16_swap(3)
 * Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1)) char32_t
NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_swap)(char16_t const **__restrict ptext) {
	char32_t result;
	char16_t const *text = *ptext;
	result = (char32_t)__hybrid_bswap16((u16)*text);
	++text;
	if (result >= 0xd800 &&
	    result <= 0xdbff) {
		result -= 0xd800;
		result <<= 10;
		result += 0x10000 - 0xdc00;
		result += __hybrid_bswap16(*text); /* low surrogate */
		++text;
	}
	*ptext = text;
	return result;
}
/* >> unicode_readutf16_swap_n(3)
 * Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1, 2)) char32_t
NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_swap_n)(char16_t const **__restrict ptext,
                                                    char16_t const *text_end) {
	char32_t result;
	char16_t const *text = *ptext;
	if (text >= text_end)
		return 0;
	result = (char32_t)__hybrid_bswap16((u16)*text);
	++text;
	if (result >= 0xd800 &&
	    result <= 0xdbff &&
	    text < text_end) {
		result -= 0xd800;
		result <<= 10;
		result += 0x10000 - 0xdc00;
		result += __hybrid_bswap16(*text); /* low surrogate */
		++text;
	}
	*ptext = text;
	return result;
}
/* >> unicode_readutf16_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1)) char32_t
NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_rev)(char16_t const **__restrict ptext) {
	char32_t result;
	char16_t const *text = *ptext;
	result = (char32_t)(u16)*--text;
	if (result >= 0xdc00 &&
	    result <= 0xdfff) {
		char32_t high = *--text;
		high   -= 0xd800;
		high   <<= 10;
		high   += 0x10000 - 0xdc00;
		result += high;
	}
	*ptext = text;
	return result;
}
/* >> unicode_readutf16_swap_rev(3)
 * Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1)) char32_t
NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_swap_rev)(char16_t const **__restrict ptext) {
	char32_t result;
	char16_t const *text = *ptext;
	--text;
	result = (char32_t)__hybrid_bswap16((u16)*text);
	if (result >= 0xdc00 &&
	    result <= 0xdfff) {
		char32_t high = (--text, __hybrid_bswap16(*text));
		high   -= 0xd800;
		high   <<= 10;
		high   += 0x10000 - 0xdc00;
		result += high;
	}
	*ptext = text;
	return result;
}
/* >> unicode_readutf16_rev_n(3)
 * Same as `unicode_readutf16_rev()', but don't read ahead of `text_start' */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1, 2)) char32_t
NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_rev_n)(char16_t const **__restrict ptext,
                                                   char16_t const *text_start) {
	char32_t result;
	char16_t const *text = *ptext;
	if (text <= text_start)
		return 0;
	result = (char32_t)(u16)*--text;
	if (result >= 0xdc00 &&
	    result <= 0xdfff && likely(text > text_start)) {
		char32_t high = *--text;
		high   -= 0xd800;
		high   <<= 10;
		high   += 0x10000 - 0xdc00;
		result += high;
	}
	*ptext = text;
	return result;
}
/* >> unicode_readutf16_swap_rev_n(3)
 * Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1, 2)) char32_t
NOTHROW_NCX(LIBCCALL libc_unicode_readutf16_swap_rev_n)(char16_t const **__restrict ptext,
                                                        char16_t const *text_start) {
	char32_t result;
	char16_t const *text = *ptext;
	if (text <= text_start)
		return 0;
	--text;
	result = (char32_t)__hybrid_bswap16((u16)*text);
	if (result >= 0xdc00 &&
	    result <= 0xdfff && likely(text > text_start)) {
		char32_t high = (--text, __hybrid_bswap16(*text));
		high   -= 0xd800;
		high   <<= 10;
		high   += 0x10000 - 0xdc00;
		result += high;
	}
	*ptext = text;
	return result;
}
/* >> unicode_writeutf8(3)
 * Write  a given Unicode character `ch' to `dst'  and return a pointer to its end
 * location. This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_unicode_writeutf8)(char *__restrict dst,
                                             char32_t ch) {
	if likely(ch <= ((uint32_t)1 << 7)-1) {
		*dst++ = (char)(unsigned char)ch;
	} else if (ch <= ((uint32_t)1 << 11)-1) {
		*dst++ = (char)(unsigned char)(0xc0 | (u8)((ch >> 6)/* & 0x1f*/));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch) & 0x3f));
	} else if (ch <= ((uint32_t)1 << 16)-1) {
		*dst++ = (char)(unsigned char)(0xe0 | (u8)((ch >> 12)/* & 0x0f*/));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 6) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch) & 0x3f));
	} else if (ch <= ((uint32_t)1 << 21)-1) {
		*dst++ = (char)(unsigned char)(0xf0 | (u8)((ch >> 18)/* & 0x07*/));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 12) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 6) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch) & 0x3f));
	} else if (ch <= ((uint32_t)1 << 26)-1) {
		*dst++ = (char)(unsigned char)(0xf8 | (u8)((ch >> 24)/* & 0x03*/));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 18) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 12) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 6) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch) & 0x3f));
	} else if (ch <= ((uint32_t)1 << 31)-1) {
		*dst++ = (char)(unsigned char)(0xfc | (u8)((ch >> 30)/* & 0x01*/));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 24) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 18) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 12) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 6) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch) & 0x3f));
	} else {
		*dst++ = (char)(unsigned char)(0xfe);
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 30) & 0x03/* & 0x3f*/));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 24) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 18) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 12) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 6) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch) & 0x3f));
	}
	return dst;
}
/* >> unicode_writeutf16(3)
 * Write a given Unicode character  `ch' to `dst' and return  a pointer to its  end
 * location. This function will write at most `UNICODE_UTF16_CURLEN' words to `dst' */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBCCALL libc_unicode_writeutf16)(char16_t *__restrict dst,
                                              char32_t ch) {
	if likely(ch <= 0xffff && (ch < 0xd800 || ch > 0xdfff)) {
		*dst++ = (char16_t)ch;
	} else {
		ch -= 0x10000;
		*dst++ = 0xd800 + (char16_t)(ch >> 10);
		*dst++ = 0xdc00 + (char16_t)(ch & 0x3ff);
	}
	return dst;
}
/* >> unicode_writeutf16_chk(3)
 * Same as `unicode_writeutf16()', but return `NULL' when `UNICODE_ISVALIDUTF16(ch)' is false */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBCCALL libc_unicode_writeutf16_chk)(char16_t *__restrict dst,
                                                  char32_t ch) {
	if unlikely(ch > 0x10ffff)
		return NULL;
	if likely(ch <= 0xffff) {
		if unlikely(ch >= 0xd800 && ch <= 0xdfff)
			return NULL;
		*dst++ = (char16_t)ch;
	} else {
		ch -= 0x10000;
		*dst++ = 0xd800 + (char16_t)(ch >> 10);
		*dst++ = 0xdc00 + (char16_t)(ch & 0x3ff);
	}
	return dst;
}
/* >> unicode_8to16(3)
 * Convert a given utf-8 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBCCALL libc_unicode_8to16)(char16_t *__restrict utf16_dst,
                                         char const *__restrict utf8_text,
                                         size_t utf8_characters) {
	char const *utf8_end = utf8_text + utf8_characters;
	while (utf8_text < utf8_end) {
		char32_t ch;
		ch = libc_unicode_readutf8_n((char const **)&utf8_text, utf8_end);
		utf16_dst = libc_unicode_writeutf16(utf16_dst, ch);
	}
	return utf16_dst;
}
#ifndef __KERNEL__
/* >> unicode_8to16_chk(3)
 * Same as `unicode_8to16()', but return `NULL' if an attempt was made to write an invalid character.
 * @param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-16 character.
 * @return: NULL: Attempted to write an invalid character */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") WUNUSED NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBCCALL libc_unicode_8to16_chk)(char16_t *__restrict utf16_dst,
                                             char const *__restrict utf8_text,
                                             size_t utf8_characters) {
	char const *utf8_end = utf8_text + utf8_characters;
	while (utf8_text < utf8_end) {
		char32_t ch;
		ch = libc_unicode_readutf8_n((char const **)&utf8_text, utf8_end);
		if (ch > 0x10ffff || (ch >= 0xd800 && ch <= 0xdfff))
			return NULL;
		utf16_dst = libc_unicode_writeutf16(utf16_dst, ch);
	}
	return utf16_dst;
}
#endif /* !__KERNEL__ */
/* >> unicode_8to32(3)
 * Convert a given utf-8 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_8TO32_MAXBUF(utf8_characters)' dwords, or `*4' bytes
 * @param: utf8_text: The input UTF-8 string to convert
 * @param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
 * @return: * : A pointer after the last written UTF-32 character. */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBCCALL libc_unicode_8to32)(char32_t *__restrict utf32_dst,
                                         char const *__restrict utf8_text,
                                         size_t utf8_characters) {
	char const *utf8_end = utf8_text + utf8_characters;
	while (utf8_text < utf8_end)
		*utf32_dst++ = libc_unicode_readutf8_n((char const **)&utf8_text, utf8_end);
	return utf32_dst;
}
/* >> unicode_16to8(3)
 * Convert a given utf-16 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_16TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-8 character */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_unicode_16to8)(char *__restrict utf8_dst,
                                         char16_t const *__restrict utf16_text,
                                         size_t utf16_characters) {
	char16_t const *utf16_end = utf16_text + utf16_characters;
	while (utf16_text < utf16_end) {
		char32_t ch;
		ch = libc_unicode_readutf16_n((char16_t const **)&utf16_text, utf16_end);
		if (ch <= ((uint32_t)1 << 7)-1) {
			*utf8_dst++ = (char)(u8)ch;
		} else if (ch <= ((uint32_t)1 << 11)-1) {
			*utf8_dst++ = (char)(0xc0 | (u8)((ch >> 6)/* & 0x1f*/));
			*utf8_dst++ = (char)(0x80 | (u8)((ch) & 0x3f));
		} else {
			*utf8_dst++ = (char)(0xe0 | (u8)((ch >> 12)/* & 0x0f*/));
			*utf8_dst++ = (char)(0x80 | (u8)((ch >> 6) & 0x3f));
			*utf8_dst++ = (char)(0x80 | (u8)((ch) & 0x3f));
		}
	}
	return utf8_dst;
}
/* >> unicode_16to32(3)
 * Convert a given utf-16 string to utf-32.
 * @param: utf32_dst: A buffer of at least `UNICODE_16TO32_MAXBUF(utf16_characters)' dwords, or *4 bytes
 * @param: utf16_text: The input UTF-16 string to convert
 * @param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
 * @return: * : A pointer after the last written UTF-32 character */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBCCALL libc_unicode_16to32)(char32_t *__restrict utf32_dst,
                                          char16_t const *__restrict utf16_text,
                                          size_t utf16_characters) {
	char16_t const *utf16_end = utf16_text + utf16_characters;
	while (utf16_text < utf16_end)
		*utf32_dst++ = libc_unicode_readutf16_n((char16_t const **)&utf16_text, utf16_end);
	return utf32_dst;
}
/* >> unicode_32to8(3)
 * Convert a given utf-32 string to utf-8.
 * @param: utf8_dst: A buffer of at least `UNICODE_32TO8_MAXBUF(utf16_characters)' bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-8 character */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_unicode_32to8)(char *__restrict utf8_dst,
                                         char32_t const *__restrict utf32_text,
                                         size_t utf32_characters) {
	while (utf32_characters--)
		utf8_dst = libc_unicode_writeutf8(utf8_dst, *utf32_text++);
	return utf8_dst;
}
/* >> unicode_32to16(3)
 * Convert a given utf-32 string to utf-16.
 * @param: utf16_dst: A buffer of at least `UNICODE_32TO16_MAXBUF(utf16_characters)' words, or *2 bytes
 * @param: utf32_text: The input UTF-32 string to convert
 * @param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
 * @return: * : A pointer after the last written UTF-16 character */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBCCALL libc_unicode_32to16)(char16_t *__restrict utf16_dst,
                                          char32_t const *__restrict utf32_text,
                                          size_t utf32_characters) {
	while (utf32_characters--)
		utf16_dst = libc_unicode_writeutf16(utf16_dst, *utf32_text++);
	return utf16_dst;
}
#ifndef __KERNEL__
/* >> unicode_c8toc16(3)
 * @return: *:          Success (*pc16 was filled; the return value
 *                      is  the  number  of bytes  taken  from `s')
 * @return: 0:          Success (*pc16 was filled; `mbs' was modified,
 *                      but nothing was read  from `s'; in this  case,
 *                      a surrogate was written)
 * @return: (size_t)-1: Unicode error (the given input string isn't
 *                      a valid unicode sequence)
 * @return: (size_t)-2: Success, but  no  character  was  generated
 *                      (`s...+=n', together with `mbs' doesn't for
 *                      a full  character, but  `mbs' was  updated) */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1, 2, 4)) size_t
NOTHROW_NCX(LIBCCALL libc_unicode_c8toc16)(char16_t *__restrict pc16,
                                           char const *__restrict s,
                                           size_t n,
                                           mbstate_t *__restrict mbs) {
	char32_t resch;
	size_t i;
	if ((mbs->__mb_word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_WR_UTF16_LO) {
		*pc16 = 0xdc00 + (mbs->__mb_word & 0x3ff);
		mbs->__mb_word = __MBSTATE_TYPE_EMPTY;
		return 0;
	}
	for (i = 0; i < n; ++i) {
		uint32_t state;
		uint8_t ch;
		state = mbs->__mb_word & __MBSTATE_TYPE_MASK;
		ch = (uint8_t)s[i];
		if (state == __MBSTATE_TYPE_EMPTY) {
			if (ch <= 0x7f) {
				*pc16 = ch;
				goto done;
			} else if (ch <= 0xbf) {
				goto error_ilseq;
			} else if (ch <= 0xdf) {
				mbs->__mb_word = __MBSTATE_TYPE_UTF8_2_2 | (ch & 0x1f);
				continue;
			} else if (ch <= 0xef) {
				mbs->__mb_word = __MBSTATE_TYPE_UTF8_3_2 | ((ch & 0xf) << 6);
				continue;
			} else if (ch <= 0xf7) {
				mbs->__mb_word = __MBSTATE_TYPE_UTF8_4_2 | ((ch & 0x7) << 12);
				continue;
			} else if (ch <= 0xfb) {
				mbs->__mb_word = __MBSTATE_TYPE_UTF8_5_2 | ((ch & 0x3) << 18);
				continue;
			} else if (ch <= 0xfd) {
				mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_2 | ((ch & 0x1) << 24);
				continue;
			} else {
				goto error_ilseq;
			}
		}
		if ((ch & 0xc0) != 0x80)
			goto error_ilseq; /* Must be a follow-up byte */
		ch &= 0x3f;
		switch (mbs->__mb_word & __MBSTATE_TYPE_MASK) {

		case __MBSTATE_TYPE_UTF8_2_2: /* expect 2nd character of a 2-byte utf-8 sequence. { WORD & 0x0000001f } */
			*pc16 = ((mbs->__mb_word & 0x1f) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_3_2: /* expect 2nd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_3_3 | (mbs->__mb_word & 0x3c0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_3_3: /* expect 3rd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0, WORD & 0x0000003f } */
			resch = ((mbs->__mb_word & 0x3ff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty_chk_surrogate;

		case __MBSTATE_TYPE_UTF8_4_2: /* expect 2nd character of a 4-byte utf-8 sequence. { WORD & 0x00007000 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_4_3 | (mbs->__mb_word & 0x7000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_4_3: /* expect 3rd character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_4_4 | (mbs->__mb_word & 0x7fc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_4_4: /* expect 4th character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			resch = ((mbs->__mb_word & 0x7fff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty_chk_surrogate;

		case __MBSTATE_TYPE_UTF8_5_2: /* expect 2nd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_5_3 | (mbs->__mb_word & 0xc0000) | ((uint32_t)ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_5_3: /* expect 3rd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_5_4 | (mbs->__mb_word & 0xff000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_5_4: /* expect 4th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_5_5 | (mbs->__mb_word & 0xfffc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_5_5: /* expect 5th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			resch = ((mbs->__mb_word & 0x000cffff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty_chk_surrogate;

		case __MBSTATE_TYPE_UTF8_6_2: /* expect 2nd character of a 6-byte utf-8 sequence. { WORD & 0x01000000 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_3 | (mbs->__mb_word & 0x1000000) | ((uint32_t)ch << (3 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_3: /* expect 3rd character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_4 | (mbs->__mb_word & 0x1fc0000) | ((uint32_t)ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_4: /* expect 4th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_5 | (mbs->__mb_word & 0x1fff000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_6_5: /* expect 5th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_6 | (mbs->__mb_word & 0x1ffffc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_6_6: /* expect 6th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			resch = ((mbs->__mb_word & 0x1ffffff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty_chk_surrogate;

		default:
error_ilseq:
			return (size_t)-1;
		}
	}
	/* Incomplete sequence (but `mbs' may have been updated) */
	return (size_t)-2;
done_empty_chk_surrogate:
	if ((resch >= 0xd800 && resch <= 0xdfff) || (resch >= 0x10000)) {
		if unlikely(resch > 0x10ffff)
			goto error_ilseq; /* Cannot be represented as UTF-16 */
		/* Need a utf-16 surrogate pair. */
		resch -= 0x10000;
		*pc16 = 0xd800 + (char16_t)(resch >> 10);
		mbs->__mb_word = __MBSTATE_TYPE_WR_UTF16_LO | (u16)(resch & 0x3ff);
	} else {
		*pc16 = (char16_t)resch;
	}
done_empty:
	mbs->__mb_word = __MBSTATE_TYPE_EMPTY;
done:
	return i + 1;
}
/* >> unicode_c8toc32(3)
 * @return: *:          Success (*pc32 was filled; the return value
 *                      is  the  number  of bytes  taken  from `s')
 * @return: (size_t)-1: Unicode error (the given input string isn't
 *                      a valid unicode sequence)
 * @return: (size_t)-2: Success, but  no  character  was  generated
 *                      (`s...+=n', together with `mbs' doesn't for
 *                      a full  character, but  `mbs' was  updated) */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1, 2, 4)) size_t
NOTHROW_NCX(LIBCCALL libc_unicode_c8toc32)(char32_t *__restrict pc32,
                                           char const *__restrict s,
                                           size_t n,
                                           mbstate_t *__restrict mbs) {
	size_t i;
	for (i = 0; i < n; ++i) {
		uint32_t state;
		uint8_t ch;
		state = mbs->__mb_word & __MBSTATE_TYPE_MASK;
		ch = (uint8_t)s[i];
		if (state == __MBSTATE_TYPE_EMPTY) {
			if (ch <= 0x7f) {
				*pc32 = ch;
				goto done;
			} else if (ch <= 0xbf) {
				goto error_ilseq;
			} else if (ch <= 0xdf) {
				mbs->__mb_word = __MBSTATE_TYPE_UTF8_2_2 | (ch & 0x1f);
				continue;
			} else if (ch <= 0xef) {
				mbs->__mb_word = __MBSTATE_TYPE_UTF8_3_2 | ((ch & 0xf) << 6);
				continue;
			} else if (ch <= 0xf7) {
				mbs->__mb_word = __MBSTATE_TYPE_UTF8_4_2 | ((ch & 0x7) << 12);
				continue;
			} else if (ch <= 0xfb) {
				mbs->__mb_word = __MBSTATE_TYPE_UTF8_5_2 | ((ch & 0x3) << 18);
				continue;
			} else if (ch <= 0xfd) {
				mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_2 | ((ch & 0x1) << 24);
				continue;
			} else {
				goto error_ilseq;
			}
		}
		if ((ch & 0xc0) != 0x80)
			goto error_ilseq; /* Must be a follow-up byte */
		ch &= 0x3f;
		switch (mbs->__mb_word & __MBSTATE_TYPE_MASK) {

		case __MBSTATE_TYPE_UTF8_2_2: /* expect 2nd character of a 2-byte utf-8 sequence. { WORD & 0x0000001f } */
			*pc32 = ((mbs->__mb_word & 0x1f) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_3_2: /* expect 2nd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_3_3 | (mbs->__mb_word & 0x3c0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_3_3: /* expect 3rd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0, WORD & 0x0000003f } */
			*pc32 = ((mbs->__mb_word & 0x3ff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_4_2: /* expect 2nd character of a 4-byte utf-8 sequence. { WORD & 0x00007000 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_4_3 | (mbs->__mb_word & 0x7000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_4_3: /* expect 3rd character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_4_4 | (mbs->__mb_word & 0x7fc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_4_4: /* expect 4th character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			*pc32 = ((mbs->__mb_word & 0x7fff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_5_2: /* expect 2nd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_5_3 | (mbs->__mb_word & 0xc0000) | ((uint32_t)ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_5_3: /* expect 3rd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_5_4 | (mbs->__mb_word & 0xff000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_5_4: /* expect 4th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_5_5 | (mbs->__mb_word & 0xfffc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_5_5: /* expect 5th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			*pc32 = ((mbs->__mb_word & 0x000cffff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_6_2: /* expect 2nd character of a 6-byte utf-8 sequence. { WORD & 0x01000000 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_3 | (mbs->__mb_word & 0x1000000) | ((uint32_t)ch << (3 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_3: /* expect 3rd character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_4 | (mbs->__mb_word & 0x1fc0000) | ((uint32_t)ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_4: /* expect 4th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_5 | (mbs->__mb_word & 0x1fff000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_6_5: /* expect 5th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			mbs->__mb_word = __MBSTATE_TYPE_UTF8_6_6 | (mbs->__mb_word & 0x1ffffc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_6_6: /* expect 6th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			*pc32 = ((mbs->__mb_word & 0x1ffffff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		default:
error_ilseq:
			return (size_t)-1;
		}
	}
	/* Incomplete sequence (but `mbs' may have been updated) */
	return (size_t)-2;
done_empty:
	mbs->__mb_word = __MBSTATE_TYPE_EMPTY;
done:
	return i + 1;
}
/* >> unicode_c16toc8(3)
 * @return: 0 :         Success, but no characters were generated
 * @return: * :         Success  (this many bytes were written to
 *                      `*pc8'; max is `UNICODE_16TO8_MAXBUF(1)')
 * @return: (size_t)-1: Unicode error (the given input string
 *                      isn't  a   valid  unicode   sequence) */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBCCALL libc_unicode_c16toc8)(char pc8[3],
                                           char16_t c16,
                                           mbstate_t *__restrict mbs) {
	char32_t ch32;
	if ((mbs->__mb_word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_UTF16_LO) {
		if unlikely(!(c16 >= 0xdc00 &&
		              c16 <= 0xdfff))
			return (size_t)-1;
		ch32 = ((mbs->__mb_word & 0x000003ff) << 10) + 0x10000 + ((u16)c16 - 0xdc00);
		mbs->__mb_word = __MBSTATE_TYPE_EMPTY;
	} else if (c16 >= 0xd800 && c16 <= 0xdbff) {
		mbs->__mb_word = __MBSTATE_TYPE_UTF16_LO | ((u16)c16 - 0xd800);
		return 0;
	} else {
		ch32 = (char32_t)c16;
	}
	if likely(ch32 <= ((uint32_t)1 << 7)-1) {
		pc8[0] = (char)(u8)ch32;
		return 1;
	}
	if (ch32 <= ((uint32_t)1 << 11)-1) {
		pc8[0] = (char)(0xc0 | (u8)((ch32 >> 6)/* & 0x1f*/));
		pc8[1] = (char)(0x80 | (u8)((ch32) & 0x3f));
		return 2;
	}
	pc8[0] = (char)(0xe0 | (u8)((ch32 >> 12)/* & 0x0f*/));
	pc8[1] = (char)(0x80 | (u8)((ch32 >> 6) & 0x3f));
	pc8[2] = (char)(0x80 | (u8)((ch32) & 0x3f));
	return 3;
}
#include <bits/crt/mbstate.h>
#include <bits/crt/uformat-printer.h>
/* >> format_8tow(3)
 * Format printer  (compatible  with  `__pformatprinter')  for
 * converting UTF-8 unicode input data into a UTF-16/32 output */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.UTF") ssize_t
NOTHROW_NCX(__FORMATPRINTER_CC libd_format_8tow)(void *arg,
                                                 char const *data,
                                                 size_t datalen) {
	struct __local_format_8tow_data {
		pc16formatprinter fd_printer;    /* [1..1] Inner printer */
		void            *fd_arg;        /* Argument for `fd_printer' */
		mbstate_t       fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	char16_t buf[64], *dst = buf;
	struct __local_format_8tow_data *closure;
	ssize_t temp, result = 0;
	closure = (struct __local_format_8tow_data *)arg;
	while (datalen) {
		do {
			size_t error;

			error = libc_unicode_c8toc16((char16_t *)dst, data, datalen, &closure->fd_incomplete);



			if unlikely(error == (size_t)-1) {
				mbstate_init(&closure->fd_incomplete);
				*dst = data[0];
				error = 1;
			} else if (error == (size_t)-2) {
				datalen = 0;
				break;
			}
			data += error;
			datalen -= error;
			++dst;
		} while (dst < COMPILER_ENDOF(buf) && datalen);
		temp = (*closure->fd_printer)(closure->fd_arg, buf, (size_t)(dst - buf));
		if unlikely(temp < 0)
			goto err;
		result += temp;
		dst = buf;
	}
	return result;
err:
	return temp;
}
#include <bits/crt/mbstate.h>
#include <bits/crt/uformat-printer.h>
/* >> format_8tow(3)
 * Format printer  (compatible  with  `__pformatprinter')  for
 * converting UTF-8 unicode input data into a UTF-16/32 output */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ssize_t
NOTHROW_NCX(__FORMATPRINTER_CC libc_format_8tow)(void *arg,
                                                 char const *data,
                                                 size_t datalen) {
	struct __local_format_8tow_data {
		pc32formatprinter fd_printer;    /* [1..1] Inner printer */
		void            *fd_arg;        /* Argument for `fd_printer' */
		mbstate_t       fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	char32_t buf[64], *dst = buf;
	struct __local_format_8tow_data *closure;
	ssize_t temp, result = 0;
	closure = (struct __local_format_8tow_data *)arg;
	while (datalen) {
		do {
			size_t error;



			error = libc_unicode_c8toc32((char32_t *)dst, data, datalen, &closure->fd_incomplete);

			if unlikely(error == (size_t)-1) {
				mbstate_init(&closure->fd_incomplete);
				*dst = data[0];
				error = 1;
			} else if (error == (size_t)-2) {
				datalen = 0;
				break;
			}
			data += error;
			datalen -= error;
			++dst;
		} while (dst < COMPILER_ENDOF(buf) && datalen);
		temp = (*closure->fd_printer)(closure->fd_arg, buf, (size_t)(dst - buf));
		if unlikely(temp < 0)
			goto err;
		result += temp;
		dst = buf;
	}
	return result;
err:
	return temp;
}
#include <bits/crt/format-printer.h>
/* >> format_wto8(3)
 * Format   printer   (compatible  with   `pc16formatprinter')  for
 * converting wide-character unicode input data into a UTF-8 output */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.UTF") ssize_t
NOTHROW_NCX(__C16FORMATPRINTER_CC libd_format_wto8)(void *arg,
                                                    char16_t const *data,
                                                    size_t datalen) {

	struct __local_format_16to8_data {
		pformatprinter fd_printer;   /* [1..1] Inner printer */
		void           *fd_arg;       /* Argument for `fd_printer' */
		char16_t        fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
	};
	char buf[64], *dst = buf;
	struct __local_format_16to8_data *closure;
	ssize_t temp, result = 0;
	size_t i = 0;
	char32_t ch;
	closure = (struct __local_format_16to8_data *)arg;
	if (closure->fd_surrogate && datalen) {
		ch  = closure->fd_surrogate - 0xd800;
		closure->fd_surrogate = 0;
		ch += 0x10000;
		ch += ((char16_t const *)data)[0] - 0xdc00;
		dst = libc_unicode_writeutf8(dst, ch);
		i = 1;
		goto after_dst_write;
	}
	while (i < datalen) {
		do {
			char16_t ch16;
			ch16 = ((char16_t const *)data)[i++];
			if (ch16 >= 0xd800 &&
			    ch16 <= 0xdbff) {
				if (i >= datalen) {
					closure->fd_surrogate = ch16;
					break;
				}
				ch  = ch16 - 0xd800;
				ch += 0x10000;
				ch += data[i++] - 0xdc00;
			} else {
				ch = ch16;
			}
			dst = libc_unicode_writeutf8(dst, ch);
after_dst_write:
			;
		} while ((dst + 4) < COMPILER_ENDOF(buf) && i < datalen);
		temp = (*closure->fd_printer)(closure->fd_arg, buf, (size_t)(dst - buf));
		if unlikely(temp < 0)
			goto err;
		result += temp;
		dst = buf;
	}
	return result;
err:
	return temp;
























}
#include <bits/crt/format-printer.h>
/* >> format_wto8(3)
 * Format   printer   (compatible  with   `pc16formatprinter')  for
 * converting wide-character unicode input data into a UTF-8 output */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ssize_t
NOTHROW_NCX(__C32FORMATPRINTER_CC libc_format_wto8)(void *arg,
                                                    char32_t const *data,
                                                    size_t datalen) {



















































	struct __local_format_32to8_data {
		__pformatprinter fd_printer; /* [1..1] Inner printer */
		void            *fd_arg;     /* Argument for `fd_printer' */
	};
	char buf[64];
	struct __local_format_32to8_data *closure;
	ssize_t temp, result = 0;
	size_t i = 0;
	closure = (struct __local_format_32to8_data *)arg;
	while (i < datalen) {
		char *dst = buf;
		do {
			dst = libc_unicode_writeutf8(dst, ((char32_t const *)data)[i++]);
		} while ((dst + 7) < COMPILER_ENDOF(buf) && i < datalen);
		temp = (*closure->fd_printer)(closure->fd_arg, buf, (size_t)(dst - buf));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;

}
#include <bits/crt/uformat-printer.h>
/* >> format_wto32(3)
 * Format  printer   (compatible   with   `pc16formatprinter')   for
 * converting wide-character unicode input data into a UTF-32 output */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.UTF") ssize_t
NOTHROW_NCX(__C16FORMATPRINTER_CC libd_format_wto32)(void *arg,
                                                     char16_t const *data,
                                                     size_t datalen) {

	struct __local_format_16to32_data {
		pc32formatprinter fd_printer;   /* [1..1] Inner printer */
		void              *fd_arg;       /* Argument for `fd_printer' */
		char16_t           fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
	};
	char32_t buf[64], *dst = buf;
	struct __local_format_16to32_data *closure;
	ssize_t temp, result = 0;
	size_t i = 0;
	char32_t ch;
	closure = (struct __local_format_16to32_data *)arg;
	if (closure->fd_surrogate && datalen) {
		ch  = closure->fd_surrogate - 0xd800;
		closure->fd_surrogate = 0;
		ch += 0x10000;
		ch += data[0] - 0xdc00;
		*dst++ = ch;
		i = 1;
		goto after_dst_write;
	}
	while (i < datalen) {
		do {
			char16_t ch16;
			ch16 = data[i++];
			if (ch16 >= 0xd800 &&
			    ch16 <= 0xdbff) {
				if (i >= datalen) {
					closure->fd_surrogate = ch16;
					break;
				}
				ch  = ch16 - 0xd800;
				ch += 0x10000;
				ch += data[i++] - 0xdc00;
			} else {
				ch = ch16;
			}
			*dst++ = ch;
after_dst_write:
			;
		} while (dst < COMPILER_ENDOF(buf) && i < datalen);
		temp = (*closure->fd_printer)(closure->fd_arg, buf, (size_t)(dst - buf));
		if unlikely(temp < 0)
			goto err;
		result += temp;
		dst = buf;
	}
	return result;
err:
	return temp;









}
#include <bits/crt/uformat-printer.h>
/* >> format_wto32(3)
 * Format  printer   (compatible   with   `pc16formatprinter')   for
 * converting wide-character unicode input data into a UTF-32 output */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ssize_t
NOTHROW_NCX(__C32FORMATPRINTER_CC libc_format_wto32)(void *arg,
                                                     char32_t const *data,
                                                     size_t datalen) {



















































	struct __local_format_32to32_data {
		pc32formatprinter fd_printer;   /* [1..1] Inner printer */
		void              *fd_arg;       /* Argument for `fd_printer' */
	};
	struct __local_format_32to32_data *closure;
	closure = (struct __local_format_32to32_data *)arg;
	return (*closure->fd_printer)(closure->fd_arg, (char32_t const *)data, datalen);

}
#include <bits/crt/format-printer.h>
#include <bits/crt/uformat-printer.h>
/* >> format_wto16(3)
 * Format   printer   (compatible   with   `pwformatprinter')    for
 * converting wide-character unicode input data into a UTF-16 output */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unicode.UTF") ssize_t
NOTHROW_NCX(__C16FORMATPRINTER_CC libd_format_wto16)(void *arg,
                                                     char16_t const *data,
                                                     size_t datalen) {
























	struct __local_format_16to16_data {
		pc16formatprinter fd_printer;   /* [1..1] Inner printer */
		void              *fd_arg;       /* Argument for `fd_printer' */
	};
	struct __local_format_16to16_data *closure;
	closure = (struct __local_format_16to16_data *)arg;
	return (*closure->fd_printer)(closure->fd_arg, (char16_t const *)data, datalen);

}
#include <bits/crt/format-printer.h>
#include <bits/crt/uformat-printer.h>
/* >> format_wto16(3)
 * Format   printer   (compatible   with   `pwformatprinter')    for
 * converting wide-character unicode input data into a UTF-16 output */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ssize_t
NOTHROW_NCX(__C32FORMATPRINTER_CC libc_format_wto16)(void *arg,
                                                     char32_t const *data,
                                                     size_t datalen) {

	struct __local_format_32to16_data {
		pc16formatprinter fd_printer; /* [1..1] Inner printer */
		void              *fd_arg;     /* Argument for `fd_printer' */
	};
	char16_t buf[64];
	struct __local_format_32to16_data *closure;
	ssize_t temp, result = 0;
	size_t i = 0;
	closure = (struct __local_format_32to16_data *)arg;
	while (i < datalen) {
		char16_t *dst = buf;
		do {
			dst = libc_unicode_writeutf16(dst, data[i++]);
		} while ((dst + 2) < COMPILER_ENDOF(buf) && i < datalen);
		temp = (*closure->fd_printer)(closure->fd_arg, buf, (size_t)(dst - buf));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;









}
#endif /* !__KERNEL__ */

DECL_END

DEFINE_PUBLIC_ALIAS(unicode_readutf8, libc_unicode_readutf8);
DEFINE_PUBLIC_ALIAS(unicode_readutf8_rev, libc_unicode_readutf8_rev);
DEFINE_PUBLIC_ALIAS(unicode_readutf8_n, libc_unicode_readutf8_n);
DEFINE_PUBLIC_ALIAS(unicode_readutf8_rev_n, libc_unicode_readutf8_rev_n);
DEFINE_PUBLIC_ALIAS(unicode_readutf16, libc_unicode_readutf16);
DEFINE_PUBLIC_ALIAS(unicode_readutf16_n, libc_unicode_readutf16_n);
DEFINE_PUBLIC_ALIAS(unicode_readutf16_swap, libc_unicode_readutf16_swap);
DEFINE_PUBLIC_ALIAS(unicode_readutf16_swap_n, libc_unicode_readutf16_swap_n);
DEFINE_PUBLIC_ALIAS(unicode_readutf16_rev, libc_unicode_readutf16_rev);
DEFINE_PUBLIC_ALIAS(unicode_readutf16_swap_rev, libc_unicode_readutf16_swap_rev);
DEFINE_PUBLIC_ALIAS(unicode_readutf16_rev_n, libc_unicode_readutf16_rev_n);
DEFINE_PUBLIC_ALIAS(unicode_readutf16_swap_rev_n, libc_unicode_readutf16_swap_rev_n);
DEFINE_PUBLIC_ALIAS(unicode_writeutf8, libc_unicode_writeutf8);
DEFINE_PUBLIC_ALIAS(unicode_writeutf16, libc_unicode_writeutf16);
DEFINE_PUBLIC_ALIAS(unicode_writeutf16_chk, libc_unicode_writeutf16_chk);
DEFINE_PUBLIC_ALIAS(unicode_8to16, libc_unicode_8to16);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(unicode_8to16_chk, libc_unicode_8to16_chk);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(unicode_8to32, libc_unicode_8to32);
DEFINE_PUBLIC_ALIAS(unicode_16to8, libc_unicode_16to8);
DEFINE_PUBLIC_ALIAS(unicode_16to32, libc_unicode_16to32);
DEFINE_PUBLIC_ALIAS(unicode_32to8, libc_unicode_32to8);
DEFINE_PUBLIC_ALIAS(unicode_32to16, libc_unicode_32to16);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(unicode_c8toc16, libc_unicode_c8toc16);
DEFINE_PUBLIC_ALIAS(unicode_c8toc32, libc_unicode_c8toc32);
DEFINE_PUBLIC_ALIAS(unicode_c16toc8, libc_unicode_c16toc8);
DEFINE_PUBLIC_ALIAS(DOS$format_8tow, libd_format_8tow);
DEFINE_PUBLIC_ALIAS(format_8tow, libc_format_8tow);
DEFINE_PUBLIC_ALIAS(DOS$format_wto8, libd_format_wto8);
DEFINE_PUBLIC_ALIAS(format_wto8, libc_format_wto8);
DEFINE_PUBLIC_ALIAS(DOS$format_wto32, libd_format_wto32);
DEFINE_PUBLIC_ALIAS(format_wto32, libc_format_wto32);
DEFINE_PUBLIC_ALIAS(DOS$format_wto16, libd_format_wto16);
DEFINE_PUBLIC_ALIAS(format_wto16, libc_format_wto16);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_UNICODE_C */
