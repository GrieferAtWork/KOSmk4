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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[define_replacement(COMPILER_ENDOF = __COMPILER_ENDOF)]
%[default:section(".text.crt.unicode.UTF")]
%[define_wchar_replacement(__SIZEOF_WCHAR_T__ = "2", "4")]

%[declare_user_export("__unicode_asciiflags")]
%[declare_user_export("__unicode_descriptor")]
%[declare_user_export("unicode_fold")]

%{
#include <features.h>

#include <hybrid/__byteorder.h>
#include <hybrid/__byteswap.h>

#include <bits/format-printer.h>
#include <bits/mbstate.h>
#include <bits/types.h>
#include <bits/uformat-printer.h>
#include <bits/wformat-printer.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_unicode_utf8seqlen
__LIBC __uint8_t const unicode_utf8seqlen[256] __CASMNAME_SAME("unicode_utf8seqlen");
#elif defined(__local_utf8_seqlen_defined)
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(unicode_utf8seqlen)
#else /* __cplusplus */
#define unicode_utf8seqlen    (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_utf8seqlen))
#endif /* !__cplusplus */
#else /* ... */
__LOCAL_LIBC_CONST_DATA(unicode_utf8seqlen) __UINT8_TYPE__ const unicode_utf8seqlen[256] =
#include "local/utf8-seqlen.h"
;
#endif /* !... */
#define __utf8_seqlen_defined 1

/* The max length of any UTF-8 byte sequence describing a single unicode character. */
#define UNICODE_UTF8_MAXLEN   8   /* == unicode_utf8seqlen[0xff] */

/* The current length of any UTF-8 byte sequence produced by any 32-bit unicode character.
 * While `UNICODE_UTF8_MAXLEN' is the theoretical limit, it allows for up to 42 bits
 * of character digits, while `7' allows for up to `36' bits (`6' would allow `30').
 * As a consequence, the max number of bytes which may be written by `unicode_writeutf8()'
 * is `UNICODE_UTF8_CURLEN', as it takes a 32-bit unicode character.
 * >> char buf[UNICODE_UTF8_CURLEN];
 * >> size_t buflen = (size_t)(unicode_writeutf8(buf,ch) - buf); */
#define UNICODE_UTF8_CURLEN   7

/* The max length of any UTF-16 word sequence describing a single unicode character. */
#define UNICODE_UTF16_MAXLEN  2
#define UNICODE_UTF16_CURLEN  2

/* The max length of any UTF-32 word sequence describing a single unicode character. */
#define UNICODE_UTF32_MAXLEN  1
#define UNICODE_UTF32_CURLEN  1

/* UTF-16 surrogate ranges. */
#define UTF16_HIGH_SURROGATE_MIN 0xd800  /* High surrogate (aka. first byte) */
#define UTF16_HIGH_SURROGATE_MAX 0xdbff
#define UTF16_LOW_SURROGATE_MIN  0xdc00  /* Low surrogate (aka. second byte) */
#define UTF16_LOW_SURROGATE_MAX  0xdfff
#define UTF16_SURROGATE_SHIFT    0x10000 /* Addend when a surrogate is encountered */

/* Check if the given unicode character `ch' can be encoded in UTF-16,
 * returning non-zero if it can, and zero if not.
 * The below function `unicode_writeutf16()' will cause weak undefined
 * behavior if the passed character does not fulfill this requirement. */
#define UNICODE_ISVALIDUTF16(ch)                  \
	(sizeof(ch) == 1                              \
	 ? 1                                          \
	 : ((sizeof(ch) == 2 || (ch) <= 0x10ffff)) && \
	   ((ch) < 0xd800 || (ch) > 0xdfff))

/* The (currently) greatest unicode character */
#define UNICODE_MAXCHAR  0x10ffff

/* Evaluate to the worst-case max required buffer sizes
 * required by different format conversion functions of
 * the same name. */
#define UNICODE_8TO16_MAXBUF(num_chars)   (num_chars)
#define UNICODE_8TO32_MAXBUF(num_chars)   (num_chars)
#define UNICODE_16TO8_MAXBUF(num_chars)  ((num_chars) * 3)
#define UNICODE_16TO32_MAXBUF(num_chars)  (num_chars)
#define UNICODE_32TO8_MAXBUF(num_chars)  ((num_chars) * 7)
#define UNICODE_32TO16_MAXBUF(num_chars) ((num_chars) * 2)
}


%[define(UNICODE_UTF8_MAXLEN      = 8)]
%[define(UNICODE_UTF8_CURLEN      = 7)]
%[define(UNICODE_UTF16_MAXLEN     = 2)]
%[define(UNICODE_UTF16_CURLEN     = 2)]
%[define(UNICODE_UTF32_MAXLEN     = 1)]
%[define(UNICODE_UTF32_CURLEN     = 1)]
%[define(UTF16_HIGH_SURROGATE_MIN = 0xd800)]
%[define(UTF16_HIGH_SURROGATE_MAX = 0xdbff)]
%[define(UTF16_LOW_SURROGATE_MIN  = 0xdc00)]
%[define(UTF16_LOW_SURROGATE_MAX  = 0xdfff)]
%[define(UTF16_SURROGATE_SHIFT    = 0x10000)]
%[define(UNICODE_MAXCHAR          = 0x10ffff)]



%
@@Read a single Unicode character from a given UTF-8 string
[[libc, kernel, impl_include("<local/unicode_utf8seqlen.h>")]]
$char32_t unicode_readutf8([[nonnull]] /*utf-8*/ char const **__restrict ptext)
	[([[nonnull]] /*utf-8*/ char const **__restrict ptext): $char32_t]
	[([[nonnull]] /*utf-8*/ char **__restrict ptext): $char32_t]
{
	char32_t result;
	char const *iter = *ptext;
	result = (char32_t)(u8)*iter++;
	if (result >= 0xc0) {
		switch (__LIBC_LOCAL_NAME(@unicode_utf8seqlen@)[result]) {

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

%
@@Same as `unicode_readutf8', but read backwards, with `*ptext'
@@starting out as a pointer after the character to be read, before
@@being updated to point to the start of the character that was read
[[libc, kernel]]
$char32_t unicode_readutf8_rev([[nonnull]] /*utf-8*/ char const **__restrict ptext)
	[([[nonnull]] /*utf-8*/ char const **__restrict ptext): $char32_t]
	[([[nonnull]] /*utf-8*/ char **__restrict ptext): $char32_t]
{
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

%
@@Same as `unicode_readutf8()', but don't read past `text_end'
[[libc, kernel, impl_include("<local/unicode_utf8seqlen.h>")]]
$char32_t unicode_readutf8_n([[nonnull]] /*utf-8*/ char const **__restrict ptext, [[nonnull]] char const *text_end)
	[([[nonnull]] /*utf-8*/ char const **__restrict ptext, [[nonnull]] char const *text_end): $char32_t]
	[([[nonnull]] /*utf-8*/ char **__restrict ptext, [[nonnull]] char const *text_end): $char32_t]
{
	char32_t result;
	char const *iter = *ptext;
	if __unlikely(iter >= text_end)
		return 0;
	result = (char32_t)(u8)*iter++;
	if (result >= 0xc0) {
		u8 len;
		len = __LIBC_LOCAL_NAME(@unicode_utf8seqlen@)[result];
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

%
@@Same as `unicode_readutf8_rev()', but don't read ahead of `text_start'
[[libc, kernel]]
$char32_t unicode_readutf8_rev_n([[nonnull]] /*utf-8*/ char const **__restrict ptext, [[nonnull]] char const *text_start)
	[([[nonnull]] /*utf-8*/ char const **__restrict ptext, [[nonnull]] char const *text_start): $char32_t]
	[([[nonnull]] /*utf-8*/ char **__restrict ptext, [[nonnull]] char const *text_start): $char32_t]
{
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

%
@@Read a single Unicode character from a given UTF-16 string
[[kernel]]
$char32_t unicode_readutf16([[nonnull]] /*utf-16*/ $char16_t const **__restrict ptext)
	[([[nonnull]] /*utf-16*/ $char16_t const **__restrict ptext): $char32_t]
	[([[nonnull]] /*utf-16*/ $char16_t **__restrict ptext): $char32_t]
{
	char32_t result;
	char16_t const *text = *ptext;
	result = (char32_t)(u16)*text++;
	if (result >= UTF16_HIGH_SURROGATE_MIN &&
	    result <= UTF16_HIGH_SURROGATE_MAX) {
		result -= UTF16_HIGH_SURROGATE_MIN;
		result <<= 10;
		result += UTF16_SURROGATE_SHIFT - UTF16_LOW_SURROGATE_MIN;
		result += *text++; /* low surrogate */
	}
	*ptext = text;
	return result;
}

%
@@Same as `unicode_readutf16()', but don't read past `text_end'
[[kernel]]
$char32_t unicode_readutf16_n([[nonnull]] /*utf-16*/ $char16_t const **__restrict ptext, [[nonnull]] $char16_t const *text_end)
	[([[nonnull]] /*utf-16*/ $char16_t const **__restrict ptext, [[nonnull]] $char16_t const *text_end): $char32_t]
	[([[nonnull]] /*utf-16*/ $char16_t **__restrict ptext, [[nonnull]] $char16_t const *text_end): $char32_t]
{
	char32_t result;
	char16_t const *text = *ptext;
	if (text >= text_end)
		return 0;
	result = (char32_t)(u16)*text++;
	if (result >= UTF16_HIGH_SURROGATE_MIN &&
	    result <= UTF16_HIGH_SURROGATE_MAX &&
	    text < text_end) {
		result -= UTF16_HIGH_SURROGATE_MIN;
		result <<= 10;
		result += UTF16_SURROGATE_SHIFT - UTF16_LOW_SURROGATE_MIN;
		result += *text++; /* low surrogate */
	}
	*ptext = text;
	return result;
}


%
@@Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU
[[kernel, impl_include("<hybrid/__byteswap.h>")]]
$char32_t unicode_readutf16_swap([[nonnull]] /*utf-16-swap*/ $char16_t const **__restrict ptext)
	[([[nonnull]] /*utf-16-swap*/ $char16_t const **__restrict ptext): $char32_t]
	[([[nonnull]] /*utf-16-swap*/ $char16_t **__restrict ptext): $char32_t]
{
	char32_t result;
	char16_t const *text = *ptext;
	result = (char32_t)__hybrid_bswap16((u16)*text);
	++text;
	if (result >= UTF16_HIGH_SURROGATE_MIN &&
	    result <= UTF16_HIGH_SURROGATE_MAX) {
		result -= UTF16_HIGH_SURROGATE_MIN;
		result <<= 10;
		result += UTF16_SURROGATE_SHIFT - UTF16_LOW_SURROGATE_MIN;
		result += __hybrid_bswap16(*text); /* low surrogate */
		++text;
	}
	*ptext = text;
	return result;
}

%
@@Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU
[[kernel, impl_include("<hybrid/__byteswap.h>")]]
$char32_t unicode_readutf16_swap_n([[nonnull]] /*utf-16-swap*/ $char16_t const **__restrict ptext, [[nonnull]] $char16_t const *text_end)
	[([[nonnull]] /*utf-16-swap*/ $char16_t const **__restrict ptext, [[nonnull]] $char16_t const *text_end): $char32_t]
	[([[nonnull]] /*utf-16-swap*/ $char16_t **__restrict ptext, [[nonnull]] $char16_t const *text_end): $char32_t]
{
	char32_t result;
	char16_t const *text = *ptext;
	if (text >= text_end)
		return 0;
	result = (char32_t)__hybrid_bswap16((u16)*text);
	++text;
	if (result >= UTF16_HIGH_SURROGATE_MIN &&
	    result <= UTF16_HIGH_SURROGATE_MAX &&
	    text < text_end) {
		result -= UTF16_HIGH_SURROGATE_MIN;
		result <<= 10;
		result += UTF16_SURROGATE_SHIFT - UTF16_LOW_SURROGATE_MIN;
		result += __hybrid_bswap16(*text); /* low surrogate */
		++text;
	}
	*ptext = text;
	return result;
}

%
@@Same as `unicode_readutf16', but read backwards, with `*ptext'
@@starting out as a pointer after the character to be read, before
@@being updated to point to the start of the character that was read
[[kernel]]
$char32_t unicode_readutf16_rev([[nonnull]] /*utf-16*/ $char16_t const **__restrict ptext)
	[([[nonnull]] /*utf-16*/ $char16_t const **__restrict ptext): $char32_t]
	[([[nonnull]] /*utf-16*/ $char16_t **__restrict ptext): $char32_t]
{
	char32_t result;
	char16_t const *text = *ptext;
	result = (char32_t)(u16)*--text;
	if (result >= UTF16_LOW_SURROGATE_MIN &&
	    result <= UTF16_LOW_SURROGATE_MAX) {
		char32_t high = *--text;
		high   -= UTF16_HIGH_SURROGATE_MIN;
		high   <<= 10;
		high   += UTF16_SURROGATE_SHIFT - UTF16_LOW_SURROGATE_MIN;
		result += high;
	}
	*ptext = text;
	return result;
}

%
@@Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU
[[kernel]]
$char32_t unicode_readutf16_swap_rev([[nonnull]] /*utf-16*/ $char16_t const **__restrict ptext)
	[([[nonnull]] /*utf-16*/ $char16_t const **__restrict ptext): $char32_t]
	[([[nonnull]] /*utf-16*/ $char16_t **__restrict ptext): $char32_t]
{
	char32_t result;
	char16_t const *text = *ptext;
	--text;
	result = (char32_t)__hybrid_bswap16((u16)*text);
	if (result >= UTF16_LOW_SURROGATE_MIN &&
	    result <= UTF16_LOW_SURROGATE_MAX) {
		char32_t high = (--text,__hybrid_bswap16(*text));
		high   -= UTF16_HIGH_SURROGATE_MIN;
		high   <<= 10;
		high   += UTF16_SURROGATE_SHIFT - UTF16_LOW_SURROGATE_MIN;
		result += high;
	}
	*ptext = text;
	return result;
}

@@Same as `unicode_readutf8_rev()', but don't read ahead of `text_start'
[[kernel]]
$char32_t unicode_readutf16_rev_n([[nonnull]] /*utf-16*/ $char16_t const **__restrict ptext, [[nonnull]] $char16_t const *text_start)
	[([[nonnull]] /*utf-16*/ $char16_t const **__restrict ptext, [[nonnull]] $char16_t const *text_start): $char32_t]
	[([[nonnull]] /*utf-16*/ $char16_t **__restrict ptext, [[nonnull]] $char16_t const *text_start): $char32_t]
{
	char32_t result;
	char16_t const *text = *ptext;
	if (text <= text_start)
		return 0;
	result = (char32_t)(u16)*--text;
	if (result >= UTF16_LOW_SURROGATE_MIN &&
	    result <= UTF16_LOW_SURROGATE_MAX && likely(text > text_start)) {
		char32_t high = *--text;
		high   -= UTF16_HIGH_SURROGATE_MIN;
		high   <<= 10;
		high   += UTF16_SURROGATE_SHIFT - UTF16_LOW_SURROGATE_MIN;
		result += high;
	}
	*ptext = text;
	return result;
}

@@Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU
[[kernel]]
$char32_t unicode_readutf16_swap_rev_n([[nonnull]] /*utf-16*/ $char16_t const **__restrict ptext, [[nonnull]] $char16_t const *text_start)
	[([[nonnull]] /*utf-16*/ $char16_t const **__restrict ptext, [[nonnull]] $char16_t const *text_start): $char32_t]
	[([[nonnull]] /*utf-16*/ $char16_t **__restrict ptext, [[nonnull]] $char16_t const *text_start): $char32_t]
{
	char32_t result;
	char16_t const *text = *ptext;
	if (text <= text_start)
		return 0;
	--text;
	result = (char32_t)__hybrid_bswap16((u16)*text);
	if (result >= UTF16_LOW_SURROGATE_MIN &&
	    result <= UTF16_LOW_SURROGATE_MAX && likely(text > text_start)) {
		char32_t high = (--text,__hybrid_bswap16(*text));
		high   -= UTF16_HIGH_SURROGATE_MIN;
		high   <<= 10;
		high   += UTF16_SURROGATE_SHIFT - UTF16_LOW_SURROGATE_MIN;
		result += high;
	}
	*ptext = text;
	return result;
}




%[define(UTF8_1BYTE_MAX = ((uint32_t)1 << 7)-1)]
%[define(UTF8_2BYTE_MAX = ((uint32_t)1 << 11)-1)]
%[define(UTF8_3BYTE_MAX = ((uint32_t)1 << 16)-1)]
%[define(UTF8_4BYTE_MAX = ((uint32_t)1 << 21)-1)]
%[define(UTF8_5BYTE_MAX = ((uint32_t)1 << 26)-1)]
%[define(UTF8_6BYTE_MAX = ((uint32_t)1 << 31)-1)]

%
@@Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
@@This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst'
[[kernel, libc, nonnull]]
char *unicode_writeutf8([[nonnull]] /*utf-8*/ char *__restrict dst, $char32_t ch) {
	if likely(ch <= UTF8_1BYTE_MAX) {
		*dst++ = (char)(u8)ch;
	} else if (ch <= UTF8_2BYTE_MAX) {
		*dst++ = (char)(0xc0 | (u8)((ch >> 6)/* & 0x1f*/));
		*dst++ = (char)(0x80 | (u8)((ch) & 0x3f));
	} else if (ch <= UTF8_3BYTE_MAX) {
		*dst++ = (char)(0xe0 | (u8)((ch >> 12)/* & 0x0f*/));
		*dst++ = (char)(0x80 | (u8)((ch >> 6) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch) & 0x3f));
	} else if (ch <= UTF8_4BYTE_MAX) {
		*dst++ = (char)(0xf0 | (u8)((ch >> 18)/* & 0x07*/));
		*dst++ = (char)(0x80 | (u8)((ch >> 12) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch >> 6) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch) & 0x3f));
	} else if (ch <= UTF8_5BYTE_MAX) {
		*dst++ = (char)(0xf8 | (u8)((ch >> 24)/* & 0x03*/));
		*dst++ = (char)(0x80 | (u8)((ch >> 18) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch >> 12) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch >> 6) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch) & 0x3f));
	} else if (ch <= UTF8_6BYTE_MAX) {
		*dst++ = (char)(0xfc | (u8)((ch >> 30)/* & 0x01*/));
		*dst++ = (char)(0x80 | (u8)((ch >> 24) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch >> 18) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch >> 12) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch >> 6) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch) & 0x3f));
	} else {
		*dst++ = (char)(0xfe);
		*dst++ = (char)(0x80 | (u8)((ch >> 30) & 0x03/* & 0x3f*/));
		*dst++ = (char)(0x80 | (u8)((ch >> 24) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch >> 18) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch >> 12) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch >> 6) & 0x3f));
		*dst++ = (char)(0x80 | (u8)((ch) & 0x3f));
	}
	return dst;
}

%
@@Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
@@This function will write at most `UNICODE_UTF16_CURLEN' bytes to `dst'
[[kernel, libc, nonnull]]
$char16_t *unicode_writeutf16([[nonnull]] /*utf-16*/ $char16_t *__restrict dst, $char32_t ch) {
	if likely(ch <= 0xffff && (ch < 0xd800 || ch > 0xdfff)) {
		*dst++ = (char16_t)ch;
	} else {
		ch -= UTF16_SURROGATE_SHIFT;
		*dst++ = UTF16_HIGH_SURROGATE_MIN + (char16_t)(ch >> 10);
		*dst++ = UTF16_LOW_SURROGATE_MIN + (char16_t)(ch & 0x3ff);
	}
	return dst;
}

%
@@Same as `unicode_writeutf16()', but return `NULL' when `UNICODE_ISVALIDUTF16(ch)' is false
[[kernel, wunused]]
$char16_t *unicode_writeutf16_chk([[nonnull]] /*utf-16*/ $char16_t *__restrict dst, $char32_t ch) {
	if unlikely(ch > UNICODE_MAXCHAR)
		return NULL;
	if likely(ch <= 0xffff && (ch < 0xd800 || ch > 0xdfff)) {
		*dst++ = (char16_t)ch;
	} else {
		ch -= UTF16_SURROGATE_SHIFT;
		*dst++ = UTF16_HIGH_SURROGATE_MIN + (char16_t)(ch >> 10);
		*dst++ = UTF16_LOW_SURROGATE_MIN + (char16_t)(ch & 0x3ff);
	}
	return dst;
}

%{

#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_UNICODE_H_PROTO)
extern "C++" {
/* Read a single Unicode character from a given UTF-32 string. */
__FORCELOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) { return *(*__ptext)++; }
/* Read a single Unicode character from a given UTF-32 string. */
__FORCELOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext) { return *(*__ptext)++; }
/* Same as `unicode_readutf32()', but read in reverse endian as that of the host CPU. */
__FORCELOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32_swap)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) { __CHAR32_TYPE__ __res = *(*__ptext++); return __hybrid_bswap32(__res); }
/* Same as `unicode_readutf32()', but read in reverse endian as that of the host CPU. */
__FORCELOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32_swap)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext) { __CHAR32_TYPE__ __res = *(*__ptext++); return __hybrid_bswap32(__res); }
/* Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__FORCELOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32_rev)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) { return *(--*__ptext); }
/* Same as `unicode_readutf16', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__FORCELOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32_rev)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext) { return *(--*__ptext); }
/* Same as `unicode_readutf32_rev()', but read in reverse endian as that of the host CPU. */
__FORCELOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32_swap_rev)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) { __CHAR32_TYPE__ __res = *(--*__ptext); return __hybrid_bswap32(__res); }
/* Same as `unicode_readutf32_rev()', but read in reverse endian as that of the host CPU. */
__FORCELOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__ (__LIBCCALL unicode_readutf32_swap_rev)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext) { __CHAR32_TYPE__ __res = *(--*__ptext); return __hybrid_bswap32(__res); }
/* Same as `unicode_readutf32()', but don't read past `text_end'. */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_end) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __result;
}
/* Same as `unicode_readutf32()', but don't read past `text_end'. */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_n)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext, __CHAR32_TYPE__ const *__text_end) {
	return unicode_readutf32_n((__CHAR32_TYPE__ const **)__ptext,__text_end);
}
/* Same as `unicode_readutf32()', but don't read before `text_start'. */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_rev_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_start) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __result;
}
/* Same as `unicode_readutf32()', but don't read before `text_start'. */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_rev_n)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext, __CHAR32_TYPE__ const *__text_start) {
	return unicode_readutf32_rev_n((__CHAR32_TYPE__ const **)__ptext,__text_start);
}
/* Same as `unicode_readutf32_n()', but read in reverse endian as that of the host CPU. */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_end) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
/* Same as `unicode_readutf32_n()', but read in reverse endian as that of the host CPU. */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_n)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext, __CHAR32_TYPE__ const *__text_end) {
	return unicode_readutf32_swap_n((__CHAR32_TYPE__ const **)__ptext,__text_end);
}
/* Same as `unicode_readutf32_rev_n()', but read in reverse endian as that of the host CPU. */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_rev_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_start) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
/* Same as `unicode_readutf32_rev_n()', but read in reverse endian as that of the host CPU. */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_rev_n)(/*utf-32*/ __CHAR32_TYPE__ **__restrict __ptext, __CHAR32_TYPE__ const *__text_start) {
	return unicode_readutf32_swap_rev_n((__CHAR32_TYPE__ const **)__ptext,__text_start);
}
}
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* Read a single Unicode character from a given UTF-32 string. */
__FORCELOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) {
	return *(*__ptext)++;
}
/* Same as `unicode_readutf32()', but read in reverse endian as that of the host CPU. */
__FORCELOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) {
	__CHAR32_TYPE__ __res = *(*__ptext++);
	return __hybrid_bswap32(__res);
}
/* Same as `unicode_readutf32', but read backwards, with `*ptext'
 * starting out as a pointer after the character to be read, before
 * being updated to point to the start of the character that was read */
__FORCELOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_rev)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) {
	return *(--*__ptext);
}
/* Same as `unicode_readutf32_rev()', but read in reverse endian as that of the host CPU. */
__FORCELOCAL __ATTR_NONNULL((1)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_rev)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext) {
	__CHAR32_TYPE__ __res = *(--*__ptext);
	return __hybrid_bswap32(__res);
}
/* Same as `unicode_readutf32()', but don't read past `text_end'. */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_end) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __result;
}
/* Same as `unicode_readutf32()', but don't read before `text_start'. */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_rev_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_start) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __result;
}
/* Same as `unicode_readutf32_n()', but read in reverse endian as that of the host CPU. */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_end) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
/* Same as `unicode_readutf32_rev_n()', but read in reverse endian as that of the host CPU. */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__
(__LIBCCALL unicode_readutf32_swap_rev_n)(/*utf-32*/ __CHAR32_TYPE__ const **__restrict __ptext, __CHAR32_TYPE__ const *__text_start) {
	__CHAR32_TYPE__ __result;
	__CHAR32_TYPE__ const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_UNICODE_H_PROTO */

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define unicode_readutf16le        unicode_readutf16
#define unicode_readutf32le        unicode_readutf32
#define unicode_readutf16be        unicode_readutf16_swap
#define unicode_readutf32be        unicode_readutf32_swap
#define unicode_readutf16le_n      unicode_readutf16_n
#define unicode_readutf32le_n      unicode_readutf32_n
#define unicode_readutf16be_n      unicode_readutf16_swap_n
#define unicode_readutf32be_n      unicode_readutf32_swap_n
#define unicode_readutf16le_rev    unicode_readutf16_rev
#define unicode_readutf32le_rev    unicode_readutf32_rev
#define unicode_readutf16be_rev    unicode_readutf16_swap_rev
#define unicode_readutf32be_rev    unicode_readutf32_swap_rev
#define unicode_readutf16le_rev_n  unicode_readutf16_rev_n
#define unicode_readutf32le_rev_n  unicode_readutf32_rev_n
#define unicode_readutf16be_rev_n  unicode_readutf16_swap_rev_n
#define unicode_readutf32be_rev_n  unicode_readutf32_swap_rev_n
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define unicode_readutf16be        unicode_readutf16
#define unicode_readutf32be        unicode_readutf32
#define unicode_readutf16le        unicode_readutf16_swap
#define unicode_readutf32le        unicode_readutf32_swap
#define unicode_readutf16be_n      unicode_readutf16_n
#define unicode_readutf32be_n      unicode_readutf32_n
#define unicode_readutf16le_n      unicode_readutf16_swap_n
#define unicode_readutf32le_n      unicode_readutf32_swap_n
#define unicode_readutf16be_rev    unicode_readutf16_rev
#define unicode_readutf32be_rev    unicode_readutf32_rev
#define unicode_readutf16le_rev    unicode_readutf16_swap_rev
#define unicode_readutf32le_rev    unicode_readutf32_swap_rev
#define unicode_readutf16be_rev_n  unicode_readutf16_rev_n
#define unicode_readutf32be_rev_n  unicode_readutf32_rev_n
#define unicode_readutf16le_rev_n  unicode_readutf16_swap_rev_n
#define unicode_readutf32le_rev_n  unicode_readutf32_swap_rev_n
#endif

/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF32_CURLEN' bytes to `dst' */
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR32_TYPE__ *
(__LIBCCALL unicode_writeutf32)(/*utf-32*/ __CHAR32_TYPE__ *__restrict __dst, __CHAR32_TYPE__ __ch) {
	*__dst++ = __ch;
	return __dst;
}
}

%
@@Convert a given utf-8 string to utf-16.
@@@param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
@@@param: utf8_text: The input UTF-8 string to convert
@@@param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
@@@return: * : A pointer after the last written UTF-16 character
[[kernel, nonnull]]
$char16_t *unicode_8to16([[nonnull]] /*utf-16*/ $char16_t *__restrict utf16_dst,
                         [[inp(utf8_characters)]] /*utf-8*/ char const *__restrict utf8_text,
                         $size_t utf8_characters) {
	char const *utf8_end = utf8_text + utf8_characters;
	while (utf8_text < utf8_end) {
		char32_t ch;
		ch = unicode_readutf8_n((char const **)&utf8_text,utf8_end);
		utf16_dst = unicode_writeutf16(utf16_dst,ch);
	}
	return utf16_dst;
}


%
@@Same as `unicode_8to16()', but return `NULL' if an attempt was made to write an invalid character.
@@@param: utf16_dst: A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_characters)' words, or `*2' bytes
@@@param: utf8_text: The input UTF-8 string to convert
@@@param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
@@@return: * : A pointer after the last written UTF-16 character.
@@@return: NULL: Attempted to write an invalid character
[[wunused]]
$char16_t *unicode_8to16_chk([[nonnull]] /*utf-16*/ $char16_t *__restrict utf16_dst,
                             [[inp(utf8_characters)]] /*utf-8*/ char const *__restrict utf8_text,
                             $size_t utf8_characters) {
	char const *utf8_end = utf8_text + utf8_characters;
	while (utf8_text < utf8_end) {
		char32_t ch;
		ch = unicode_readutf8_n((char const **)&utf8_text,utf8_end);
		if (ch > UNICODE_MAXCHAR || (ch >= 0xd800 && ch <= 0xdfff))
			return NULL;
		utf16_dst = unicode_writeutf16(utf16_dst,ch);
	}
	return utf16_dst;
}

%
@@Convert a given utf-8 string to utf-32.
@@@param: utf32_dst: A buffer of at least `UNICODE_8TO32_MAXBUF(utf8_characters)' dwords, or `*4' bytes
@@@param: utf8_text: The input UTF-8 string to convert
@@@param: utf8_characters: The amount of UTF-8 characters found in `utf8_text'
@@@return: * : A pointer after the last written UTF-32 character.
[[kernel, nonnull]]
$char32_t *unicode_8to32([[nonnull]] /*utf-32*/ $char32_t *__restrict utf32_dst,
                         [[inp(utf8_characters)]] /*utf-8*/ char const *__restrict utf8_text,
                         $size_t utf8_characters) {
	char const *utf8_end = utf8_text + utf8_characters;
	while (utf8_text < utf8_end)
		*utf32_dst++ = unicode_readutf8_n((char const **)&utf8_text,utf8_end);
	return utf32_dst;
}


%
@@Convert a given utf-16 string to utf-8.
@@@param: utf8_dst: A buffer of at least `UNICODE_16TO8_MAXBUF(utf16_characters)' bytes
@@@param: utf16_text: The input UTF-16 string to convert
@@@param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
@@@return: * : A pointer after the last written UTF-8 character
[[kernel, nonnull]]
char *unicode_16to8([[nonnull]] /*utf-8*/ char *__restrict utf8_dst,
                    [[inp(utf16_characters)]] /*utf-16*/ $char16_t const *__restrict utf16_text,
                    $size_t utf16_characters) {
	char16_t const *utf16_end = utf16_text + utf16_characters;
	while (utf16_text < utf16_end) {
		char32_t ch;
		ch = unicode_readutf16_n((char16_t const **)&utf16_text,utf16_end);
		if (ch <= UTF8_1BYTE_MAX) {
			*utf8_dst++ = (char)(u8)ch;
		} else if (ch <= UTF8_2BYTE_MAX) {
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

%
@@Convert a given utf-16 string to utf-32.
@@@param: utf32_dst: A buffer of at least `UNICODE_16TO32_MAXBUF(utf16_characters)' dwords, or *4 bytes
@@@param: utf16_text: The input UTF-16 string to convert
@@@param: utf16_characters: The amount of UTF-16 characters found in `utf16_text'
@@@return: * : A pointer after the last written UTF-32 character
[[kernel, nonnull]]
$char32_t *unicode_16to32([[nonnull]] /*utf-32*/ $char32_t *__restrict utf32_dst,
                          [[inp(utf16_characters)]] /*utf-16*/ $char16_t const *__restrict utf16_text,
                          $size_t utf16_characters) {
	char16_t const *utf16_end = utf16_text + utf16_characters;
	while (utf16_text < utf16_end)
		*utf32_dst++ = unicode_readutf16_n((char16_t const **)&utf16_text,utf16_end);
	return utf32_dst;
}

%
@@Convert a given utf-32 string to utf-8.
@@@param: utf8_dst: A buffer of at least `UNICODE_32TO8_MAXBUF(utf16_characters)' bytes
@@@param: utf32_text: The input UTF-32 string to convert
@@@param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
@@@return: * : A pointer after the last written UTF-8 character
[[kernel, nonnull]]
char *unicode_32to8([[nonnull]] /*utf-8*/ char *__restrict utf8_dst,
                    [[inp(utf32_characters)]] /*utf-32*/ $char32_t const *__restrict utf32_text,
                    $size_t utf32_characters) {
	while (utf32_characters--)
		utf8_dst = unicode_writeutf8(utf8_dst, *utf32_text++);
	return utf8_dst;
}


%
@@Convert a given utf-32 string to utf-16.
@@@param: utf16_dst: A buffer of at least `UNICODE_32TO16_MAXBUF(utf16_characters)' words, or *2 bytes
@@@param: utf32_text: The input UTF-32 string to convert
@@@param: utf32_characters: The amount of UTF-32 characters found in `utf32_text'
@@@return: * : A pointer after the last written UTF-16 character
[[kernel, nonnull]]
$char16_t *unicode_32to16([[nonnull]] /*utf-16*/ $char16_t *__restrict utf16_dst,
                          [[inp(utf32_characters)]] /*utf-32*/ $char32_t const *__restrict utf32_text,
                          $size_t utf32_characters) {
	while (utf32_characters--)
		utf16_dst = unicode_writeutf16(utf16_dst, *utf32_text++);
	return utf16_dst;
}




@@@return: *:          Success (*pc16 was filled; the return value is the number of bytes taken from `s')
@@@return: 0:          Success (*pc16 was filled; `mbs' was modified, but nothing was read from `s'; in this case, a surrogate was written)
@@@return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
@@@return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated)
[[decl_include("<bits/mbstate.h>")]]
$size_t unicode_c8toc16([[nonnull]] $char16_t *__restrict pc16,
                        [[nonnull]] /*utf-8*/ char const *__restrict s, $size_t n,
                        [[nonnull]] __mbstate_t *__restrict mbs) {
	char32_t resch;
	size_t i;
	if ((mbs->__word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_WR_UTF16_LO) {
		*pc16 = 0xdc00 + (mbs->__word & 0x3ff);
		mbs->__word = __MBSTATE_TYPE_EMPTY;
		return 0;
	}
	for (i = 0; i < n; ++i) {
		uint32_t state;
		uint8_t ch;
		state = mbs->__word & __MBSTATE_TYPE_MASK;
		ch = (uint8_t)s[i];
		if (state == __MBSTATE_TYPE_EMPTY) {
			if (ch <= 0x7f) {
				*pc16 = ch;
				goto done;
			} else if (ch <= 0xbf) {
				goto error_ilseq;
			} else if (ch <= 0xdf) {
				mbs->__word = __MBSTATE_TYPE_UTF8_2_2 | (ch & 0x1f);
				continue;
			} else if (ch <= 0xef) {
				mbs->__word = __MBSTATE_TYPE_UTF8_3_2 | ((ch & 0xf) << 6);
				continue;
			} else if (ch <= 0xf7) {
				mbs->__word = __MBSTATE_TYPE_UTF8_4_2 | ((ch & 0x7) << 12);
				continue;
			} else if (ch <= 0xfb) {
				mbs->__word = __MBSTATE_TYPE_UTF8_5_2 | ((ch & 0x3) << 18);
				continue;
			} else if (ch <= 0xfd) {
				mbs->__word = __MBSTATE_TYPE_UTF8_6_2 | ((ch & 0x1) << 24);
				continue;
			} else {
				goto error_ilseq;
			}
		}
		if ((ch & 0xc0) != 0x80)
			goto error_ilseq; /* Must be a follow-up byte */
		ch &= 0x3f;
		switch (mbs->__word & __MBSTATE_TYPE_MASK) {

		case __MBSTATE_TYPE_UTF8_2_2: /* expect 2nd character of a 2-byte utf-8 sequence. { WORD & 0x0000001f } */
			*pc16 = ((mbs->__word & 0x1f) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_3_2: /* expect 2nd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_3_3 | (mbs->__word & 0x3c0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_3_3: /* expect 3rd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0, WORD & 0x0000003f } */
			resch = ((mbs->__word & 0x3ff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty_chk_surrogate;

		case __MBSTATE_TYPE_UTF8_4_2: /* expect 2nd character of a 4-byte utf-8 sequence. { WORD & 0x00007000 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_4_3 | (mbs->__word & 0x7000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_4_3: /* expect 3rd character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_4_4 | (mbs->__word & 0x7fc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_4_4: /* expect 4th character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			resch = ((mbs->__word & 0x7fff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty_chk_surrogate;

		case __MBSTATE_TYPE_UTF8_5_2: /* expect 2nd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_5_3 | (mbs->__word & 0xc0000) | ((uint32_t)ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_5_3: /* expect 3rd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_5_4 | (mbs->__word & 0xff000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_5_4: /* expect 4th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_5_5 | (mbs->__word & 0xfffc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_5_5: /* expect 5th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			resch = ((mbs->__word & 0x000cffff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty_chk_surrogate;

		case __MBSTATE_TYPE_UTF8_6_2: /* expect 2nd character of a 6-byte utf-8 sequence. { WORD & 0x01000000 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_6_3 | (mbs->__word & 0x1000000) | ((uint32_t)ch << (3 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_3: /* expect 3rd character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_6_4 | (mbs->__word & 0x1fc0000) | ((uint32_t)ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_4: /* expect 4th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_6_5 | (mbs->__word & 0x1fff000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_6_5: /* expect 5th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_6_6 | (mbs->__word & 0x1ffffc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_6_6: /* expect 6th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			resch = ((mbs->__word & 0x1ffffff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
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
		if unlikely(resch > UNICODE_MAXCHAR)
			goto error_ilseq; /* Cannot be represented as UTF-16 */
		/* Need a utf-16 surrogate pair. */
		resch -= 0x10000;
		*pc16 = 0xd800 + (__CHAR16_TYPE__)(resch >> 10);
		mbs->__word = __MBSTATE_TYPE_WR_UTF16_LO | (__CHAR16_TYPE__)(resch & 0x3ff);
	} else {
		*pc16 = (char16_t)resch;
	}
done_empty:
	mbs->__word = __MBSTATE_TYPE_EMPTY;
done:
	return i + 1;
}


@@@return: *:          Success (*pc32 was filled; the return value is the number of bytes taken from `s')
@@@return: (size_t)-1: Unicode error (the given input string isn't a valid unicode sequence)
@@@return: (size_t)-2: Success, but no character was generated (s...+=n, together with `mbs' doesn't for a full character, but `mbs' was updated)
[[decl_include("<bits/mbstate.h>")]]
$size_t unicode_c8toc32([[nonnull]] $char32_t *__restrict pc32,
                        [[nonnull]] /*utf-8*/ char const *__restrict s, $size_t n,
                        [[nonnull]] __mbstate_t *__restrict mbs) {
	size_t i;
	for (i = 0; i < n; ++i) {
		uint32_t state;
		uint8_t ch;
		state = mbs->__word & __MBSTATE_TYPE_MASK;
		ch = (uint8_t)s[i];
		if (state == __MBSTATE_TYPE_EMPTY) {
			if (ch <= 0x7f) {
				*pc32 = ch;
				goto done;
			} else if (ch <= 0xbf) {
				goto error_ilseq;
			} else if (ch <= 0xdf) {
				mbs->__word = __MBSTATE_TYPE_UTF8_2_2 | (ch & 0x1f);
				continue;
			} else if (ch <= 0xef) {
				mbs->__word = __MBSTATE_TYPE_UTF8_3_2 | ((ch & 0xf) << 6);
				continue;
			} else if (ch <= 0xf7) {
				mbs->__word = __MBSTATE_TYPE_UTF8_4_2 | ((ch & 0x7) << 12);
				continue;
			} else if (ch <= 0xfb) {
				mbs->__word = __MBSTATE_TYPE_UTF8_5_2 | ((ch & 0x3) << 18);
				continue;
			} else if (ch <= 0xfd) {
				mbs->__word = __MBSTATE_TYPE_UTF8_6_2 | ((ch & 0x1) << 24);
				continue;
			} else {
				goto error_ilseq;
			}
		}
		if ((ch & 0xc0) != 0x80)
			goto error_ilseq; /* Must be a follow-up byte */
		ch &= 0x3f;
		switch (mbs->__word & __MBSTATE_TYPE_MASK) {

		case __MBSTATE_TYPE_UTF8_2_2: /* expect 2nd character of a 2-byte utf-8 sequence. { WORD & 0x0000001f } */
			*pc32 = ((mbs->__word & 0x1f) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_3_2: /* expect 2nd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_3_3 | (mbs->__word & 0x3c0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_3_3: /* expect 3rd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0, WORD & 0x0000003f } */
			*pc32 = ((mbs->__word & 0x3ff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_4_2: /* expect 2nd character of a 4-byte utf-8 sequence. { WORD & 0x00007000 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_4_3 | (mbs->__word & 0x7000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_4_3: /* expect 3rd character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_4_4 | (mbs->__word & 0x7fc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_4_4: /* expect 4th character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			*pc32 = ((mbs->__word & 0x7fff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_5_2: /* expect 2nd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_5_3 | (mbs->__word & 0xc0000) | ((uint32_t)ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_5_3: /* expect 3rd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_5_4 | (mbs->__word & 0xff000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_5_4: /* expect 4th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_5_5 | (mbs->__word & 0xfffc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_5_5: /* expect 5th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			*pc32 = ((mbs->__word & 0x000cffff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_6_2: /* expect 2nd character of a 6-byte utf-8 sequence. { WORD & 0x01000000 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_6_3 | (mbs->__word & 0x1000000) | ((uint32_t)ch << (3 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_3: /* expect 3rd character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_6_4 | (mbs->__word & 0x1fc0000) | ((uint32_t)ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_4: /* expect 4th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_6_5 | (mbs->__word & 0x1fff000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_6_5: /* expect 5th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			mbs->__word = __MBSTATE_TYPE_UTF8_6_6 | (mbs->__word & 0x1ffffc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_6_6: /* expect 6th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			*pc32 = ((mbs->__word & 0x1ffffff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		default:
error_ilseq:
			return (size_t)-1;
		}
	}
	/* Incomplete sequence (but `mbs' may have been updated) */
	return (size_t)-2;
done_empty:
	mbs->__word = __MBSTATE_TYPE_EMPTY;
done:
	return i + 1;
}



%[define(__UNICODE_FORMAT_XTOY_BUFSIZE = 64)]



%{

struct format_8to16_data {
	__pc16formatprinter fd_printer;    /* [1..1] Inner printer */
	void               *fd_arg;        /* Argument for `fd_printer' */
	__UINT32_TYPE__     fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
};
}

@@Format printer (compatible with `__pformatprinter') for
@@converting UTF-8 unicode input data into a UTF-16 output
[[impl_include("<bits/mbstate.h>", "<bits/format-printer.h>", "<bits/uformat-printer.h>")]]
$ssize_t format_8to16(/*struct format_8to16_data **/ void *arg,
                      /*utf-8*/ char const *data, $size_t datalen) {
	struct __local_format_8to16_data {
		__pc16formatprinter fd_printer;    /* [1..1] Inner printer */
		void               *fd_arg;        /* Argument for `fd_printer' */
		__mbstate_t         fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	char16_t buf[__UNICODE_FORMAT_XTOY_BUFSIZE], *dst = buf;
	struct __local_format_8to16_data *closure;
	ssize_t temp, result = 0;
	closure = (struct __local_format_8to16_data *)arg;
	while (datalen) {
		do {
			size_t error = unicode_c8toc16(dst, data, datalen, &closure->fd_incomplete);
			if unlikely(error == (size_t)-1) {
				closure->fd_incomplete.__word = __MBSTATE_TYPE_EMPTY;
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


%{

struct format_8to32_data {
	__pc32formatprinter fd_printer;    /* [1..1] Inner printer */
	void               *fd_arg;        /* Argument for `fd_printer' */
	__UINT32_TYPE__     fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
};
}

@@Format printer (compatible with `__pformatprinter') for
@@converting UTF-8 unicode input data into a UTF-32 output
[[impl_include("<bits/mbstate.h>", "<bits/format-printer.h>", "<bits/uformat-printer.h>")]]
$ssize_t format_8to32(/*struct format_8to32_data **/ void *arg,
                      /*utf-8*/ char const *data, $size_t datalen) {
	struct __local_format_8to32_data {
		__pc32formatprinter fd_printer;    /* [1..1] Inner printer */
		void               *fd_arg;        /* Argument for `fd_printer' */
		__mbstate_t         fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	char32_t buf[__UNICODE_FORMAT_XTOY_BUFSIZE], *dst = buf;
	struct __local_format_8to32_data *closure;
	ssize_t temp, result = 0;
	closure = (struct __local_format_8to32_data *)arg;
	while (datalen) {
		do {
			size_t error = unicode_c8toc32(dst, data, datalen, &closure->fd_incomplete);
			if unlikely(error == (size_t)-1) {
				closure->fd_incomplete.__word = __MBSTATE_TYPE_EMPTY;
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


//struct format_wto8_data {
//	__pformatprinter fd_printer;   /* [1..1] Inner printer */
//	void            *fd_arg;       /* Argument for `fd_printer' */
//#if __SIZEOF_WCHAR_T__ == 2
//	__CHAR16_TYPE__  fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
//#endif /* __SIZEOF_WCHAR_T__ == 2 */
//};

@@Format printer (compatible with `__pc16formatprinter') for
@@converting wide-character unicode input data into a UTF-8 output
[[hidden, impl_include("<bits/format-printer.h>"), wchar]]
$ssize_t format_wto8(/*struct format_wto8_data **/ void *arg,
                     $wchar_t const *data, $size_t datalen) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	struct __local_format_16to8_data {
		__pformatprinter fd_printer;   /* [1..1] Inner printer */
		void            *fd_arg;       /* Argument for `fd_printer' */
		__CHAR16_TYPE__  fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
	};
	char buf[__UNICODE_FORMAT_XTOY_BUFSIZE], *dst = buf;
	struct __local_format_16to8_data *closure;
	ssize_t temp, result = 0;
	size_t i = 0;
	char32_t ch;
	closure = (struct __local_format_16to8_data *)arg;
	if (closure->fd_surrogate && datalen) {
		ch  = closure->fd_surrogate - UTF16_HIGH_SURROGATE_MIN;
		closure->fd_surrogate = 0;
		ch += UTF16_SURROGATE_SHIFT;
		ch += ((char16_t const *)data)[0] - UTF16_LOW_SURROGATE_MIN;
		dst = unicode_writeutf8(dst, ch);
		i = 1;
		goto after_dst_write;
	}
	while (i < datalen) {
		do {
			char16_t ch16;
			ch16 = ((char16_t const *)data)[i++];
			if (ch16 >= UTF16_HIGH_SURROGATE_MIN &&
			    ch16 <= UTF16_HIGH_SURROGATE_MAX) {
				if (i >= datalen) {
					closure->fd_surrogate = ch16;
					break;
				}
				ch  = ch16 - UTF16_HIGH_SURROGATE_MIN;
				ch += UTF16_SURROGATE_SHIFT;
				ch += data[i++] - UTF16_LOW_SURROGATE_MIN;
			} else {
				ch = ch16;
			}
			dst = unicode_writeutf8(dst, ch);
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
@@pp_else@@
	struct __local_format_32to8_data {
		__pformatprinter fd_printer; /* [1..1] Inner printer */
		void            *fd_arg;     /* Argument for `fd_printer' */
	};
	char buf[__UNICODE_FORMAT_XTOY_BUFSIZE];
	struct __local_format_32to8_data *closure;
	ssize_t temp, result = 0;
	size_t i = 0;
	closure = (struct __local_format_32to8_data *)arg;
	while (i < datalen) {
		char *dst = buf;
		do {
			dst = unicode_writeutf8(dst, ((char32_t const *)data)[i++]);
		} while ((dst + 7) < COMPILER_ENDOF(buf) && i < datalen);
		temp = (*closure->fd_printer)(closure->fd_arg, buf, (size_t)(dst - buf));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
@@pp_endif@@
}


%{

struct format_16to8_data {
	__pformatprinter fd_printer;   /* [1..1] Inner printer */
	void            *fd_arg;       /* Argument for `fd_printer' */
	__CHAR16_TYPE__  fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
};
}

@@Format printer (compatible with `__pc16formatprinter') for
@@converting UTF-16 unicode input data into a UTF-8 output
$ssize_t format_16to8(/*struct format_16to8_data **/ void *arg,
                      $char16_t const *data, $size_t datalen)
	%{uchar16("format_wto8")}


%{

struct format_32to8_data {
	__pformatprinter fd_printer; /* [1..1] Inner printer */
	void            *fd_arg;     /* Argument for `fd_printer' */
};
}

@@Format printer (compatible with `__pc32formatprinter') for
@@converting UTF-32 unicode input data into a UTF-8 output
$ssize_t format_32to8(/*struct format_32to8_data **/ void *arg,
                      $char32_t const *data, $size_t datalen)
	%{uchar32("format_wto8")}



//struct format_wto32_data {
//	__pc32formatprinter fd_printer;   /* [1..1] Inner printer */
//	void               *fd_arg;       /* Argument for `fd_printer' */
//#if __SIZEOF_WCHAR_T__ == 2
//	__CHAR16_TYPE__     fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
//#endif /* __SIZEOF_WCHAR_T__ == 2 */
//};

@@Format printer (compatible with `__pc16formatprinter') for
@@converting wide-character unicode input data into a UTF-32 output
[[hidden, impl_include("<bits/uformat-printer.h>"), wchar]]
$ssize_t format_wto32(/*struct format_wto32_data **/ void *arg,
                      $wchar_t const *data, $size_t datalen) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	struct __local_format_16to32_data {
		__pc32formatprinter fd_printer;   /* [1..1] Inner printer */
		void               *fd_arg;       /* Argument for `fd_printer' */
		__CHAR16_TYPE__     fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
	};
	char32_t buf[__UNICODE_FORMAT_XTOY_BUFSIZE], *dst = buf;
	struct __local_format_16to32_data *closure;
	ssize_t temp, result = 0;
	size_t i = 0;
	char32_t ch;
	closure = (struct __local_format_16to32_data *)arg;
	if (closure->fd_surrogate && datalen) {
		ch  = closure->fd_surrogate - UTF16_HIGH_SURROGATE_MIN;
		closure->fd_surrogate = 0;
		ch += UTF16_SURROGATE_SHIFT;
		ch += data[0] - UTF16_LOW_SURROGATE_MIN;
		*dst++ = ch;
		i = 1;
		goto after_dst_write;
	}
	while (i < datalen) {
		do {
			char16_t ch16;
			ch16 = data[i++];
			if (ch16 >= UTF16_HIGH_SURROGATE_MIN &&
			    ch16 <= UTF16_HIGH_SURROGATE_MAX) {
				if (i >= datalen) {
					closure->fd_surrogate = ch16;
					break;
				}
				ch  = ch16 - UTF16_HIGH_SURROGATE_MIN;
				ch += UTF16_SURROGATE_SHIFT;
				ch += data[i++] - UTF16_LOW_SURROGATE_MIN;
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
@@pp_else@@
	struct __local_format_32to32_data {
		__pc32formatprinter fd_printer;   /* [1..1] Inner printer */
		void               *fd_arg;       /* Argument for `fd_printer' */
	};
	struct __local_format_32to32_data *closure;
	closure = (struct __local_format_32to32_data *)arg;
	return (*closure->fd_printer)(closure->fd_arg, (char32_t const *)data, datalen);
@@pp_endif@@
}


%{

struct format_16to32_data {
	__pc32formatprinter fd_printer;   /* [1..1] Inner printer */
	void               *fd_arg;       /* Argument for `fd_printer' */
	__CHAR16_TYPE__     fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
};
}

@@Format printer (compatible with `pc16formatprinter') for
@@converting UTF-16 unicode input data into a UTF-32 output
$ssize_t format_16to32(/*struct format_16to32_data **/ void *arg,
                       $char16_t const *data, $size_t datalen)
	%{uchar16("format_wto32")}


//struct format_wto16_data {
//	__pc16formatprinter fd_printer; /* [1..1] Inner printer */
//	void               *fd_arg;     /* Argument for `fd_printer' */
//};

@@Format printer (compatible with `pwformatprinter') for
@@converting wide-character unicode input data into a UTF-16 output
[[hidden, wchar, impl_include("<bits/format-printer.h>", "<bits/uformat-printer.h>")]]
$ssize_t format_wto16(/*struct format_wto16_data **/ void *arg,
                      $wchar_t const *data, $size_t datalen) {
@@pp_if __SIZEOF_WCHAR_T__ == 4@@
	struct __local_format_32to16_data {
		__pc16formatprinter fd_printer; /* [1..1] Inner printer */
		void               *fd_arg;     /* Argument for `fd_printer' */
	};
	char16_t buf[__UNICODE_FORMAT_XTOY_BUFSIZE];
	struct __local_format_32to16_data *closure;
	ssize_t temp, result = 0;
	size_t i = 0;
	closure = (struct __local_format_32to16_data *)arg;
	while (i < datalen) {
		char16_t *dst = buf;
		do {
			dst = unicode_writeutf16(dst, data[i++]);
		} while ((dst + 2) < COMPILER_ENDOF(buf) && i < datalen);
		temp = (*closure->fd_printer)(closure->fd_arg, buf, (size_t)(dst - buf));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
@@pp_else@@
	struct __local_format_16to16_data {
		__pc16formatprinter fd_printer;   /* [1..1] Inner printer */
		void               *fd_arg;       /* Argument for `fd_printer' */
	};
	struct __local_format_16to16_data *closure;
	closure = (struct __local_format_16to16_data *)arg;
	return (*closure->fd_printer)(closure->fd_arg, (char16_t const *)data, datalen);
@@pp_endif@@
}


%{

struct format_32to16_data {
	__pc16formatprinter fd_printer; /* [1..1] Inner printer */
	void               *fd_arg;     /* Argument for `fd_printer' */
};
}

@@Format printer (compatible with `__pc32formatprinter') for
@@converting UTF-32 unicode input data into a UTF-16 output
$ssize_t format_32to16(/*struct format_32to16_data **/ void *arg,
                       $char32_t const *data, $size_t datalen)
	%{uchar32("format_wto16")}




%{



/* Unicode character traits database */
#ifdef __CRT_HAVE___unicode_descriptor
#ifndef __UNICODE_FPRINT
#define __UNICODE_FPRINT   0x0001 /* The character is printable, or SPC (` '). */
#define __UNICODE_FALPHA   0x0002 /* The character is alphabetic. */
#define __UNICODE_FSPACE   0x0004 /* The character is a space-character. */
#define __UNICODE_FLF      0x0008 /* Line-feed/line-break character. */
#define __UNICODE_FLOWER   0x0010 /* Lower-case. */
#define __UNICODE_FUPPER   0x0020 /* Upper-case. */
#define __UNICODE_FTITLE   0x0040 /* Title-case. */
#define __UNICODE_FCNTRL   0x0080 /* Control character. */
#define __UNICODE_FDIGIT   0x0100 /* The character is a digit. e.g.: `²' (sqare; `ut_digit' is `2') */
#define __UNICODE_FDECIMAL 0x0200 /* The character is a decimal. e.g: `5' (ascii; `ut_digit' is `5') */
#define __UNICODE_FSYMSTRT 0x0400 /* The character can be used as the start of an identifier. */
#define __UNICODE_FSYMCONT 0x0800 /* The character can be used to continue an identifier. */
/*      __UNICODE_F        0x1000 */
/*      __UNICODE_F        0x2000 */
/*      __UNICODE_F        0x4000 */
/*      __UNICODE_F        0x8000 */
struct __unitraits {
	__UINT16_TYPE__ const __ut_flags; /* Character flags (Set of `__UNICODE_F*') */
	__UINT8_TYPE__  const __ut_digit; /* Digit/decimal value (`unicode_isnumeric'), or 0. */
	__UINT8_TYPE__  const __ut_fold;  /* Unicode fold extension index, or `0xff'. */
	__INT32_TYPE__  const __ut_lower; /* Delta added to the character to convert it to lowercase, or 0. */
	__INT32_TYPE__  const __ut_upper; /* Delta added to the character to convert it to uppercase, or 0. */
	__INT32_TYPE__  const __ut_title; /* Delta added to the character to convert it to titlecase, or 0. */
};
#ifndef ____unicode_descriptor_defined
#define ____unicode_descriptor_defined 1
__CDECLARE(__ATTR_RETNONNULL __ATTR_CONST,struct __unitraits *,__NOTHROW,__unicode_descriptor,(__CHAR32_TYPE__ __ch),(__ch))
#endif /* !____unicode_descriptor_defined */
#endif /* !__UNICODE_FPRINT */

#ifdef __CRT_HAVE_unicode_fold
/* The max number of characters ever written by `unicode_fold' */
#define UNICODE_FOLDED_MAX 3

/* Fold the given unicode character CH */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,unicode_fold,(__CHAR32_TYPE__ __ch, __CHAR32_TYPE__ __buf[UNICODE_FOLDED_MAX]),(__ch,__buf))
#else /* __CRT_HAVE_unicode_fold */
/* The max number of characters ever written by `unicode_fold' */
#define UNICODE_FOLDED_MAX 1

/* Fold the given unicode character CH */
__LOCAL __ATTR_RETNONNULL __ATTR_NONNULL((2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL unicode_fold)(__CHAR32_TYPE__ __ch, __CHAR32_TYPE__ __buf[UNICODE_FOLDED_MAX]) {
	__buf[0] = __ch;
	return __buf + 1;
}
#endif /* !__CRT_HAVE_unicode_fold */

/* Unicode character conversion. */
#ifdef __CRT_HAVE___unicode_asciiflags
#ifndef ____unicode_asciiflags_defined
#define ____unicode_asciiflags_defined 1
__LIBC __UINT16_TYPE__ const __unicode_asciiflags[256];
#endif /* !____unicode_asciiflags_defined */
#define __unicode_flags(ch)        (sizeof(ch) == 1 ? __unicode_asciiflags[(__uint8_t)(ch)] : __unicode_descriptor(ch)->__ut_flags)
#define __unicode_asciiisupper(ch) (__unicode_asciiflags[(__UINT8_TYPE__)(ch)] & __UNICODE_FUPPER)
#define __unicode_asciiislower(ch) (__unicode_asciiflags[(__UINT8_TYPE__)(ch)] & __UNICODE_FLOWER)
#define __unicode_asciitolower(ch) (__unicode_asciiisupper(ch) ? (__UINT8_TYPE__)(ch) + 0x20 : (__UINT8_TYPE__)(ch))
#define __unicode_asciitoupper(ch) (__unicode_asciiislower(ch) ? (__UINT8_TYPE__)(ch) - 0x20 : (__UINT8_TYPE__)(ch))
#define __unicode_asciitotitle(ch) (__unicode_asciiislower(ch) ? (__UINT8_TYPE__)(ch) - 0x20 : (__UINT8_TYPE__)(ch))
#define __unicode_asciiasdigit(ch) ((__UINT8_TYPE__)(ch) - 0x30)
#define unicode_tolower(ch)        (sizeof(ch) == 1 ? (__CHAR32_TYPE__)__unicode_asciitolower(ch) : (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_lower))
#define unicode_toupper(ch)        (sizeof(ch) == 1 ? (__CHAR32_TYPE__)__unicode_asciitoupper(ch) : (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_upper))
#define unicode_totitle(ch)        (sizeof(ch) == 1 ? (__CHAR32_TYPE__)__unicode_asciitoupper(ch) : (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_title))
#define unicode_asdigit(ch)        (sizeof(ch) == 1 ? __unicode_asciiasdigit(ch) : __unicode_descriptor(ch)->__ut_digit)
#else /* __CRT_HAVE___unicode_asciiflags */
#define __unicode_flags(ch)        (__unicode_descriptor(ch)->__ut_flags)
#define unicode_tolower(ch)        (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_lower)
#define unicode_toupper(ch)        (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_upper)
#define unicode_totitle(ch)        (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_title)
#define unicode_asdigit(ch)        (__unicode_descriptor(ch)->__ut_digit)
#endif /* !__CRT_HAVE___unicode_asciiflags */

/* Unicode character traits */
#define unicode_isalpha(ch)        (__unicode_flags(ch) & __UNICODE_FALPHA)
#define unicode_islower(ch)        (__unicode_flags(ch) & __UNICODE_FLOWER)
#define unicode_isupper(ch)        (__unicode_flags(ch) & __UNICODE_FUPPER)
#define unicode_isalnum(ch)        (__unicode_flags(ch) & (__UNICODE_FALPHA | __UNICODE_FDECIMAL))
#define unicode_isspace(ch)        (__unicode_flags(ch) & __UNICODE_FSPACE)
#define unicode_istab(ch)          ((ch) == 9)
#define unicode_islf(ch)           (__unicode_flags(ch) & __UNICODE_FLF)
#define unicode_isprint(ch)        (__unicode_flags(ch) & __UNICODE_FPRINT)
#define unicode_isdigit(ch)        (__unicode_flags(ch) & __UNICODE_FDIGIT)
#define unicode_isdecimal(ch)      (__unicode_flags(ch) & __UNICODE_FDECIMAL)
#define unicode_isnumeric(ch)      (__unicode_flags(ch) & (__UNICODE_FDIGIT | __UNICODE_FDECIMAL))
#define unicode_istitle(ch)        (__unicode_flags(ch) & (__UNICODE_FTITLE | __UNICODE_FUPPER))
#define unicode_issymstrt(ch)      (__unicode_flags(ch) & __UNICODE_FSYMSTRT)
#define unicode_issymcont(ch)      (__unicode_flags(ch) & __UNICODE_FSYMCONT)
#define unicode_iscntrl(ch)        (__unicode_flags(ch) & __UNICODE_FCNTRL)

#else /* __CRT_HAVE___unicode_descriptor */
#include <libc/ctype.h>

#define UNICODE_FOLDED_MAX 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL unicode_fold)(__CHAR32_TYPE__ __ch, __CHAR32_TYPE__ __buf[UNICODE_FOLDED_MAX]) {
	__buf[0] = __ch;
	return __buf + 1;
}

#define unicode_tolower(ch)   (unicode_isupper(ch) ? (__CHAR32_TYPE__)(ch) + 0x20 : (__CHAR32_TYPE__)(ch))
#define unicode_toupper(ch)   (unicode_islower(ch) ? (__CHAR32_TYPE__)(ch) - 0x20 : (__CHAR32_TYPE__)(ch))
#define unicode_totitle(ch)   (unicode_islower(ch) ? (__CHAR32_TYPE__)(ch) - 0x20 : (__CHAR32_TYPE__)(ch))
#define unicode_asdigit(ch)   ((__UINT8_TYPE__)(ch) - 0x30)
#define unicode_isalpha(ch)   __libc_isalpha(ch)
#define unicode_islower(ch)   __libc_islower(ch)
#define unicode_isupper(ch)   __libc_isupper(ch)
#define unicode_isalnum(ch)   __libc_isalnum(ch)
#define unicode_isspace(ch)   __libc_isspace(ch)
#define unicode_istab(ch)     ((ch) == 9)
#define unicode_islf(ch)      ((ch) == 13 || (ch) == 10)
#define unicode_isprint(ch)   __libc_isprint(ch)
#define unicode_isdigit(ch)   __libc_isdigit(ch)
#define unicode_isdecimal(ch) unicode_isdigit(ch)
#define unicode_isnumeric(ch) unicode_isdigit(ch)
#define unicode_istitle(ch)   unicode_isupper(ch)
#define unicode_issymstrt(ch) __libc_isalpha(ch)
#define unicode_issymcont(ch) __libc_isalnum(ch)
#define unicode_iscntrl(ch)   __libc_iscntrl(ch)
#endif /* !__CRT_HAVE___unicode_descriptor */

__SYSDECL_END
#endif /* __CC__ */

}


%(libc_fast){
#define __LIBC_UNICODE_UTF8_MAXLEN              8
#define __LIBC_UNICODE_UTF8_CURLEN              7
#define __LIBC_UNICODE_UTF16_MAXLEN             2
#define __LIBC_UNICODE_UTF16_CURLEN             2
#define __LIBC_UNICODE_UTF32_MAXLEN             1
#define __LIBC_UNICODE_UTF32_CURLEN             1
#define __LIBC_UNICODE_ISVALIDUTF16(ch)         (sizeof(ch) == 1 ? 1 : ((sizeof(ch) == 2 || (ch) <= 0x10ffff)) && ((ch) < 0xd800 || (ch) > 0xdfff))
#define __LIBC_UNICODE_MAXCHAR                  0x10ffff
#define __LIBC_UNICODE_8TO16_MAXBUF(num_chars)  (num_chars)
#define __LIBC_UNICODE_8TO32_MAXBUF(num_chars)  (num_chars)
#define __LIBC_UNICODE_16TO8_MAXBUF(num_chars)  ((num_chars) * 3)
#define __LIBC_UNICODE_16TO32_MAXBUF(num_chars) (num_chars)
#define __LIBC_UNICODE_32TO8_MAXBUF(num_chars)  ((num_chars) * 7)
#define __LIBC_UNICODE_32TO16_MAXBUF(num_chars) ((num_chars) * 2)
}

%(libc_fast){

__DECL_BEGIN

#ifdef __CRT_HAVE___unicode_descriptor
#ifndef __UNICODE_FPRINT
#define __UNICODE_FPRINT   0x0001 /* The character is printable, or SPC (` '). */
#define __UNICODE_FALPHA   0x0002 /* The character is alphabetic. */
#define __UNICODE_FSPACE   0x0004 /* The character is a space-character. */
#define __UNICODE_FLF      0x0008 /* Line-feed/line-break character. */
#define __UNICODE_FLOWER   0x0010 /* Lower-case. */
#define __UNICODE_FUPPER   0x0020 /* Upper-case. */
#define __UNICODE_FTITLE   0x0040 /* Title-case. */
#define __UNICODE_FCNTRL   0x0080 /* Control character. */
#define __UNICODE_FDIGIT   0x0100 /* The character is a digit. e.g.: `²' (sqare; `ut_digit' is `2') */
#define __UNICODE_FDECIMAL 0x0200 /* The character is a decimal. e.g: `5' (ascii; `ut_digit' is `5') */
#define __UNICODE_FSYMSTRT 0x0400 /* The character can be used as the start of an identifier. */
#define __UNICODE_FSYMCONT 0x0800 /* The character can be used to continue an identifier. */
/*      __UNICODE_F        0x1000 */
/*      __UNICODE_F        0x2000 */
/*      __UNICODE_F        0x4000 */
/*      __UNICODE_F        0x8000 */
struct __unitraits {
	__UINT16_TYPE__ const __ut_flags; /* Character flags (Set of `__UNICODE_F*') */
	__UINT8_TYPE__  const __ut_digit; /* Digit/decimal value (`unicode_isnumeric'), or 0. */
	__UINT8_TYPE__  const __ut_fold;  /* Unicode fold extension index, or `0xff'. */
	__INT32_TYPE__  const __ut_lower; /* Delta added to the character to convert it to lowercase, or 0. */
	__INT32_TYPE__  const __ut_upper; /* Delta added to the character to convert it to uppercase, or 0. */
	__INT32_TYPE__  const __ut_title; /* Delta added to the character to convert it to titlecase, or 0. */
};
#ifndef ____unicode_descriptor_defined
#define ____unicode_descriptor_defined 1
__CDECLARE(__ATTR_RETNONNULL __ATTR_CONST,struct __unitraits *,__NOTHROW,__unicode_descriptor,(__CHAR32_TYPE__ __ch),(__ch))
#endif /* !____unicode_descriptor_defined */
#endif /* !__UNICODE_FPRINT */
#ifdef __CRT_HAVE_unicode_fold
#define __LIBC_UNICODE_FOLDED_MAX 3
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__libc_unicode_fold,(__CHAR32_TYPE__ __ch, __CHAR32_TYPE__ __buf[__LIBC_UNICODE_FOLDED_MAX]),unicode_fold,(__ch,__buf))
#else /* __CRT_HAVE_unicode_fold */
#define __LIBC_UNICODE_FOLDED_MAX 1
__LOCAL __ATTR_RETNONNULL __ATTR_NONNULL((2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __libc_unicode_fold)(__CHAR32_TYPE__ __ch, __CHAR32_TYPE__ __buf[__LIBC_UNICODE_FOLDED_MAX]) {
	__buf[0] = __ch;
	return __buf + 1;
}
#endif /* !__CRT_HAVE_unicode_fold */
#ifdef __CRT_HAVE___unicode_asciiflags
#ifndef ____unicode_asciiflags_defined
#define ____unicode_asciiflags_defined 1
__LIBC __UINT16_TYPE__ const __unicode_asciiflags[256];
#endif /* !____unicode_asciiflags_defined */
#define __libc_unicode_flags(ch)        (sizeof(ch) == 1 ? __unicode_asciiflags[(__uint8_t)(ch)] : __unicode_descriptor(ch)->__ut_flags)
#define __libc_unicode_asciiisupper(ch) (__unicode_asciiflags[(__UINT8_TYPE__)(ch)] & __UNICODE_FUPPER)
#define __libc_unicode_asciiislower(ch) (__unicode_asciiflags[(__UINT8_TYPE__)(ch)] & __UNICODE_FLOWER)
#define __libc_unicode_asciitolower(ch) (__libc_unicode_asciiisupper(ch) ? (__UINT8_TYPE__)(ch) + 0x20 : (__UINT8_TYPE__)(ch))
#define __libc_unicode_asciitoupper(ch) (__libc_unicode_asciiislower(ch) ? (__UINT8_TYPE__)(ch) - 0x20 : (__UINT8_TYPE__)(ch))
#define __libc_unicode_asciitotitle(ch) (__libc_unicode_asciiislower(ch) ? (__UINT8_TYPE__)(ch) - 0x20 : (__UINT8_TYPE__)(ch))
#define __libc_unicode_asciiasdigit(ch) ((__UINT8_TYPE__)(ch) - 0x30)
#define __libc_unicode_tolower(ch)      (sizeof(ch) == 1 ? (__CHAR32_TYPE__)__libc_unicode_asciitolower(ch) : (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_lower))
#define __libc_unicode_toupper(ch)      (sizeof(ch) == 1 ? (__CHAR32_TYPE__)__libc_unicode_asciitoupper(ch) : (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_upper))
#define __libc_unicode_totitle(ch)      (sizeof(ch) == 1 ? (__CHAR32_TYPE__)__libc_unicode_asciitoupper(ch) : (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_title))
#define __libc_unicode_asdigit(ch)      (sizeof(ch) == 1 ? __libc_unicode_asciiasdigit(ch) : __unicode_descriptor(ch)->__ut_digit)
#else /* __CRT_HAVE___unicode_asciiflags */
#define __libc_unicode_flags(ch)        (__unicode_descriptor(ch)->__ut_flags)
#define __libc_unicode_tolower(ch)      (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_lower)
#define __libc_unicode_toupper(ch)      (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_upper)
#define __libc_unicode_totitle(ch)      (__CHAR32_TYPE__)((ch) + __unicode_descriptor(ch)->__ut_title)
#define __libc_unicode_asdigit(ch)      (__unicode_descriptor(ch)->__ut_digit)
#endif /* !__CRT_HAVE___unicode_asciiflags */
#define __libc_unicode_isalpha(ch)      (__libc_unicode_flags(ch) & __UNICODE_FALPHA)
#define __libc_unicode_islower(ch)      (__libc_unicode_flags(ch) & __UNICODE_FLOWER)
#define __libc_unicode_isupper(ch)      (__libc_unicode_flags(ch) & __UNICODE_FUPPER)
#define __libc_unicode_isalnum(ch)      (__libc_unicode_flags(ch) & (__UNICODE_FALPHA | __UNICODE_FDECIMAL))
#define __libc_unicode_isspace(ch)      (__libc_unicode_flags(ch) & __UNICODE_FSPACE)
#define __libc_unicode_istab(ch)        ((ch) == 9)
#define __libc_unicode_islf(ch)         (__libc_unicode_flags(ch) & __UNICODE_FLF)
#define __libc_unicode_isprint(ch)      (__libc_unicode_flags(ch) & __UNICODE_FPRINT)
#define __libc_unicode_isdigit(ch)      (__libc_unicode_flags(ch) & __UNICODE_FDIGIT)
#define __libc_unicode_isdecimal(ch)    (__libc_unicode_flags(ch) & __UNICODE_FDECIMAL)
#define __libc_unicode_isnumeric(ch)    (__libc_unicode_flags(ch) & (__UNICODE_FDIGIT | __UNICODE_FDECIMAL))
#define __libc_unicode_istitle(ch)      (__libc_unicode_flags(ch) & (__UNICODE_FTITLE | __UNICODE_FUPPER))
#define __libc_unicode_issymstrt(ch)    (__libc_unicode_flags(ch) & __UNICODE_FSYMSTRT)
#define __libc_unicode_issymcont(ch)    (__libc_unicode_flags(ch) & __UNICODE_FSYMCONT)
#define __libc_unicode_iscntrl(ch)      (__libc_unicode_flags(ch) & __UNICODE_FCNTRL)
#else /* __CRT_HAVE___unicode_descriptor */
#include <libc/ctype.h>

#define __LIBC_UNICODE_FOLDED_MAX 1
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __libc_unicode_fold)(__CHAR32_TYPE__ __ch, __CHAR32_TYPE__ __buf[__LIBC_UNICODE_FOLDED_MAX]) {
	__buf[0] = __ch;
	return __buf + 1;
}

#define __libc_unicode_tolower(ch)   (__libc_unicode_isupper(ch) ? (__CHAR32_TYPE__)(ch) + 0x20 : (__CHAR32_TYPE__)(ch))
#define __libc_unicode_toupper(ch)   (__libc_unicode_islower(ch) ? (__CHAR32_TYPE__)(ch) - 0x20 : (__CHAR32_TYPE__)(ch))
#define __libc_unicode_totitle(ch)   (__libc_unicode_islower(ch) ? (__CHAR32_TYPE__)(ch) - 0x20 : (__CHAR32_TYPE__)(ch))
#define __libc_unicode_asdigit(ch)   ((__UINT8_TYPE__)(ch) - 0x30)
#define __libc_unicode_isalpha(ch)   __libc_isalpha(ch)
#define __libc_unicode_islower(ch)   __libc_islower(ch)
#define __libc_unicode_isupper(ch)   __libc_isupper(ch)
#define __libc_unicode_isalnum(ch)   __libc_isalnum(ch)
#define __libc_unicode_isspace(ch)   __libc_isspace(ch)
#define __libc_unicode_istab(ch)     ((ch) == 9)
#define __libc_unicode_islf(ch)      ((ch) == 13 || (ch) == 10)
#define __libc_unicode_isprint(ch)   __libc_isprint(ch)
#define __libc_unicode_isdigit(ch)   __libc_isdigit(ch)
#define __libc_unicode_isdecimal(ch) __libc_unicode_isdigit(ch)
#define __libc_unicode_isnumeric(ch) __libc_unicode_isdigit(ch)
#define __libc_unicode_istitle(ch)   __libc_unicode_isupper(ch)
#define __libc_unicode_issymstrt(ch) __libc_isalpha(ch)
#define __libc_unicode_issymcont(ch) __libc_isalnum(ch)
#define __libc_unicode_iscntrl(ch)   __libc_iscntrl(ch)
#endif /* !__CRT_HAVE___unicode_descriptor */

__DECL_END
}














