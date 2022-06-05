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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[define_replacement(COMPILER_ENDOF = __COMPILER_ENDOF)]
%[define_replacement(unicode_utf8seqlen = __LOCAL_unicode_utf8seqlen)]
%[define_replacement(mbstate_t = "struct __mbstate")]
%[define_replacement(pc16formatprinter = __pc16formatprinter)]
%[define_replacement(pc32formatprinter = __pc32formatprinter)]
%[define_replacement(pformatprinter = __pformatprinter)]
%[default:section(".text.crt{|.dos}.unicode.UTF")]
%[define_wchar_replacement(__SIZEOF_WCHAR_T__ = "2", "4")]

%[define_decl_include("<bits/crt/mbstate.h>": ["struct __mbstate"])]

/* /kos/src/libc/hybrid/unicode.c */
%[declare_kernel_export("unicode_utf8seqlen")]

%(auto_header){
#ifndef __pformatprinter_defined
#define __pformatprinter_defined
typedef __pformatprinter pformatprinter;
#endif /* !__pformatprinter_defined */
#ifndef __pc16formatprinter_defined
#define __pc16formatprinter_defined
typedef __pc16formatprinter pc16formatprinter;
typedef __pc32formatprinter pc32formatprinter;
#endif /* !__pc16formatprinter_defined */
}


%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/byteorder.h>
)]%[insert:prefix(
#include <hybrid/__byteswap.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

}%[insert:prefix(
#include <bits/crt/format-printer.h>
)]%[insert:prefix(
#include <bits/crt/mbstate.h>
)]%[insert:prefix(
#include <bits/crt/uformat-printer.h>
)]%[insert:prefix(
#include <bits/crt/wformat-printer.h>
)]%[insert:prefix(
#include <bits/crt/unicode.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{



/* Other headers only define these under _KOS_SOURCE, but since <unicode.h> is
 * a kos-specific header, we can define these unconditionally (if  available)! */

/* Static initializer for `mbstate_t':
 * >> mbstate_t mbs = MBSTATE_INIT; */
#if !defined(MBSTATE_INIT) && defined(__MBSTATE_INIT)
#define MBSTATE_INIT __MBSTATE_INIT
#endif /* !MBSTATE_INIT && __MBSTATE_INIT */

/* Dynamic initializer for `mbstate_t':
 * >> mbstate_t mbs;
 * >> mbstate_init(&mbs); */
#if !defined(mbstate_init) && defined(__mbstate_init)
#define mbstate_init __mbstate_init
#endif /* !mbstate_init && __mbstate_init */

/* Check if the given mbstate_t is in its zero-shift state:
 * >> if (mbstate_isempty(&mbs)) { ... } */
#if !defined(mbstate_isempty) && defined(__mbstate_isempty)
#define mbstate_isempty __mbstate_isempty
#endif /* !mbstate_isempty && __mbstate_isempty */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __unicode_utf8seqlen_defined
#define __unicode_utf8seqlen_defined
#ifdef __CRT_HAVE_unicode_utf8seqlen
__CSDECLARE2(,__UINT8_TYPE__ const unicode_utf8seqlen[256],unicode_utf8seqlen)
#else /* __CRT_HAVE_unicode_utf8seqlen */
#include <libc/template/unicode_utf8seqlen.h>
#define unicode_utf8seqlen __LOCAL_unicode_utf8seqlen
#endif /* !__CRT_HAVE_unicode_utf8seqlen */
#endif /* !__unicode_utf8seqlen_defined */

/* The max length of any UTF-8 byte sequence describing a single unicode character. */
#define UNICODE_UTF8_MAXLEN  8 /* == unicode_utf8seqlen[0xff] */

/* The current length of any UTF-8 byte sequence produced by any 32-bit unicode character.
 * While `UNICODE_UTF8_MAXLEN'  is the  theoretical limit,  it allows  for up  to 42  bits
 * of  character digits, while `7' allows for up to `36' bits (`6' would only allow `30').
 * As a consequence, the max number of bytes which may be written by `unicode_writeutf8()'
 * is `UNICODE_UTF8_CURLEN', as it takes a 32-bit unicode character.
 * >> char buf[UNICODE_UTF8_CURLEN];
 * >> size_t buflen = (size_t)(unicode_writeutf8(buf, ch) - buf); */
#define UNICODE_UTF8_CURLEN  7

/* The max length of any UTF-16 word sequence describing a single unicode character. */
#define UNICODE_UTF16_MAXLEN 2
#define UNICODE_UTF16_CURLEN 2

/* The max length of any UTF-32 word sequence describing a single unicode character. */
#define UNICODE_UTF32_MAXLEN 1
#define UNICODE_UTF32_CURLEN 1

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

#ifndef __mbstate_t_defined
#define __mbstate_t_defined
typedef struct __mbstate mbstate_t;
#endif /* !__mbstate_t_defined */

#ifndef __char16_t_defined
#define __char16_t_defined
typedef __CHAR16_TYPE__ char16_t;
typedef __CHAR32_TYPE__ char32_t;
#endif /* !__char16_t_defined */

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



@@>> unicode_readutf8(3)
@@Read a single Unicode character from a given UTF-8 string
[[libc, kernel, impl_include("<libc/template/unicode_utf8seqlen.h>")]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char32_t unicode_readutf8([[inout]] /*utf-8*/ char const **__restrict ptext)
	[([[inout]] /*utf-8*/ char const **__restrict ptext): char32_t]
	[([[inout]] /*utf-8*/ char **__restrict ptext): char32_t]
{
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

@@>> unicode_readutf8_rev(3)
@@Same  as  `unicode_readutf8',  but read  backwards,  with `*ptext'
@@starting out as a pointer after  the character to be read,  before
@@being updated to point to the start of the character that was read
[[kernel, libc, decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char32_t unicode_readutf8_rev([[inout]] /*utf-8*/ char const **__restrict ptext)
	[([[inout]] /*utf-8*/ char const **__restrict ptext): char32_t]
	[([[inout]] /*utf-8*/ char **__restrict ptext): char32_t]
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

@@>> unicode_readutf8_n(3)
@@Same as `unicode_readutf8()', but don't read past `text_end'
[[kernel, libc, impl_include("<libc/template/unicode_utf8seqlen.h>")]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char32_t unicode_readutf8_n([[inout]] /*utf-8*/ char const **__restrict ptext, [[nonnull]] char const *text_end)
	[([[inout]] /*utf-8*/ char const **__restrict ptext, [[nonnull]] char const *text_end): char32_t]
	[([[inout]] /*utf-8*/ char **__restrict ptext, [[nonnull]] char const *text_end): char32_t]
{
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

@@>> unicode_readutf8_rev_n(3)
@@Same as `unicode_readutf8_rev()', but don't read ahead of `text_start'
[[kernel, libc, decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char32_t unicode_readutf8_rev_n([[inout]] /*utf-8*/ char const **__restrict ptext, [[in]] char const *text_start)
	[([[inout]] /*utf-8*/ char const **__restrict ptext, [[in]] char const *text_start): char32_t]
	[([[inout]] /*utf-8*/ char **__restrict ptext, [[in]] char const *text_start): char32_t]
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

@@>> unicode_readutf16(3)
@@Read a single Unicode character from a given UTF-16 string
[[kernel, libc, decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char32_t unicode_readutf16([[inout]] /*utf-16*/ char16_t const **__restrict ptext)
	[([[inout]] /*utf-16*/ char16_t const **__restrict ptext): char32_t]
	[([[inout]] /*utf-16*/ char16_t **__restrict ptext): char32_t]
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

@@>> unicode_readutf16_n(3)
@@Same as `unicode_readutf16()', but don't read past `text_end'
[[kernel, libc, decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char32_t unicode_readutf16_n([[inout]] /*utf-16*/ char16_t const **__restrict ptext, [[nonnull]] char16_t const *text_end)
	[([[inout]] /*utf-16*/ char16_t const **__restrict ptext, [[nonnull]] char16_t const *text_end): char32_t]
	[([[inout]] /*utf-16*/ char16_t **__restrict ptext, [[nonnull]] char16_t const *text_end): char32_t]
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


@@>> unicode_readutf16_swap(3)
@@Same as `unicode_readutf16()', but read in reverse endian as that of the host CPU
[[kernel, impl_include("<hybrid/__byteswap.h>")]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char32_t unicode_readutf16_swap([[inout]] /*utf-16-swap*/ char16_t const **__restrict ptext)
	[([[inout]] /*utf-16-swap*/ char16_t const **__restrict ptext): char32_t]
	[([[inout]] /*utf-16-swap*/ char16_t **__restrict ptext): char32_t]
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

@@>> unicode_readutf16_swap_n(3)
@@Same as `unicode_readutf16_n()', but read in reverse endian as that of the host CPU
[[kernel, impl_include("<hybrid/__byteswap.h>")]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char32_t unicode_readutf16_swap_n([[inout]] /*utf-16-swap*/ char16_t const **__restrict ptext, [[nonnull]] char16_t const *text_end)
	[([[inout]] /*utf-16-swap*/ char16_t const **__restrict ptext, [[nonnull]] char16_t const *text_end): char32_t]
	[([[inout]] /*utf-16-swap*/ char16_t **__restrict ptext, [[nonnull]] char16_t const *text_end): char32_t]
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

@@>> unicode_readutf16_rev(3)
@@Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
@@starting out as a pointer after  the character to be read,  before
@@being updated to point to the start of the character that was read
[[kernel, libc, decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char32_t unicode_readutf16_rev([[inout]] /*utf-16*/ char16_t const **__restrict ptext)
	[([[inout]] /*utf-16*/ char16_t const **__restrict ptext): char32_t]
	[([[inout]] /*utf-16*/ char16_t **__restrict ptext): char32_t]
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

@@>> unicode_readutf16_swap_rev(3)
@@Same as `unicode_readutf16_rev()', but read in reverse endian as that of the host CPU
[[kernel, impl_include("<hybrid/__byteswap.h>")]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char32_t unicode_readutf16_swap_rev([[inout]] /*utf-16*/ char16_t const **__restrict ptext)
	[([[inout]] /*utf-16*/ char16_t const **__restrict ptext): char32_t]
	[([[inout]] /*utf-16*/ char16_t **__restrict ptext): char32_t]
{
	char32_t result;
	char16_t const *text = *ptext;
	--text;
	result = (char32_t)__hybrid_bswap16((u16)*text);
	if (result >= UTF16_LOW_SURROGATE_MIN &&
	    result <= UTF16_LOW_SURROGATE_MAX) {
		char32_t high = (--text, __hybrid_bswap16(*text));
		high   -= UTF16_HIGH_SURROGATE_MIN;
		high   <<= 10;
		high   += UTF16_SURROGATE_SHIFT - UTF16_LOW_SURROGATE_MIN;
		result += high;
	}
	*ptext = text;
	return result;
}

@@>> unicode_readutf16_rev_n(3)
@@Same as `unicode_readutf16_rev()', but don't read ahead of `text_start'
[[kernel, libc, decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char32_t unicode_readutf16_rev_n([[inout]] /*utf-16*/ char16_t const **__restrict ptext, [[nonnull]] char16_t const *text_start)
	[([[inout]] /*utf-16*/ char16_t const **__restrict ptext, [[nonnull]] char16_t const *text_start): char32_t]
	[([[inout]] /*utf-16*/ char16_t **__restrict ptext, [[nonnull]] char16_t const *text_start): char32_t]
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

@@>> unicode_readutf16_swap_rev_n(3)
@@Same as `unicode_readutf16_rev_n()', but read in reverse endian as that of the host CPU
[[kernel, impl_include("<hybrid/__byteswap.h>")]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char32_t unicode_readutf16_swap_rev_n([[inout]] /*utf-16*/ char16_t const **__restrict ptext, [[in]] char16_t const *text_start)
	[([[inout]] /*utf-16*/ char16_t const **__restrict ptext, [[in]] char16_t const *text_start): char32_t]
	[([[inout]] /*utf-16*/ char16_t **__restrict ptext, [[in]] char16_t const *text_start): char32_t]
{
	char32_t result;
	char16_t const *text = *ptext;
	if (text <= text_start)
		return 0;
	--text;
	result = (char32_t)__hybrid_bswap16((u16)*text);
	if (result >= UTF16_LOW_SURROGATE_MIN &&
	    result <= UTF16_LOW_SURROGATE_MAX && likely(text > text_start)) {
		char32_t high = (--text, __hybrid_bswap16(*text));
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

@@>> unicode_writeutf8(3)
@@Write  a given Unicode character `ch' to `dst'  and return a pointer to its end
@@location. This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst'
[[kernel, libc, nonnull]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char *unicode_writeutf8([[out]] /*utf-8*/ char *__restrict dst, char32_t ch) {
	if likely(ch <= UTF8_1BYTE_MAX) {
		*dst++ = (char)(unsigned char)ch;
	} else if (ch <= UTF8_2BYTE_MAX) {
		*dst++ = (char)(unsigned char)(0xc0 | (u8)((ch >> 6)/* & 0x1f*/));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch) & 0x3f));
	} else if (ch <= UTF8_3BYTE_MAX) {
		*dst++ = (char)(unsigned char)(0xe0 | (u8)((ch >> 12)/* & 0x0f*/));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 6) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch) & 0x3f));
	} else if (ch <= UTF8_4BYTE_MAX) {
		*dst++ = (char)(unsigned char)(0xf0 | (u8)((ch >> 18)/* & 0x07*/));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 12) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 6) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch) & 0x3f));
	} else if (ch <= UTF8_5BYTE_MAX) {
		*dst++ = (char)(unsigned char)(0xf8 | (u8)((ch >> 24)/* & 0x03*/));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 18) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 12) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 6) & 0x3f));
		*dst++ = (char)(unsigned char)(0x80 | (u8)((ch) & 0x3f));
	} else if (ch <= UTF8_6BYTE_MAX) {
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

@@>> unicode_writeutf8_n(3)
@@Same as `unicode_writeutf8(3)', but don't writ emore than `dst_maxbytes' bytes.
[[nonnull, decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char *unicode_writeutf8_n([[out(? <= dst_maxbytes)]] /*utf-8*/ char *__restrict dst,
                          char32_t ch, $size_t dst_maxbytes) {
	if likely(dst_maxbytes != 0) {
		if likely(ch <= UTF8_1BYTE_MAX) {
			*dst++ = (char)(unsigned char)ch;
		} else {
			char tempbuf[7], *tempdst = tempbuf;
			size_t templen;
			if (ch <= UTF8_2BYTE_MAX) {
				*tempdst++ = (char)(unsigned char)(0xc0 | (u8)((ch >> 6)/* & 0x1f*/));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch)&0x3f));
			} else if (ch <= UTF8_3BYTE_MAX) {
				*tempdst++ = (char)(unsigned char)(0xe0 | (u8)((ch >> 12)/* & 0x0f*/));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 6) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch)&0x3f));
			} else if (ch <= UTF8_4BYTE_MAX) {
				*tempdst++ = (char)(unsigned char)(0xf0 | (u8)((ch >> 18)/* & 0x07*/));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 12) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 6) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch)&0x3f));
			} else if (ch <= UTF8_5BYTE_MAX) {
				*tempdst++ = (char)(unsigned char)(0xf8 | (u8)((ch >> 24)/* & 0x03*/));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 18) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 12) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 6) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch)&0x3f));
			} else if (ch <= UTF8_6BYTE_MAX) {
				*tempdst++ = (char)(unsigned char)(0xfc | (u8)((ch >> 30)/* & 0x01*/));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 24) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 18) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 12) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 6) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch)&0x3f));
			} else {
				*tempdst++ = (char)(unsigned char)(0xfe);
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 30) & 0x03/* & 0x3f*/));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 24) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 18) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 12) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch >> 6) & 0x3f));
				*tempdst++ = (char)(unsigned char)(0x80 | (u8)((ch)&0x3f));
			}
			templen = (size_t)(tempdst - tempbuf) * sizeof(char);
			if (templen > dst_maxbytes)
				templen = dst_maxbytes;
			dst = (char *)mempcpy(dst, tempbuf, templen);
		}
	}
	return dst;
}

@@>> unicode_writeutf16(3)
@@Write a given Unicode character  `ch' to `dst' and return  a pointer to its  end
@@location. This function will write at most `UNICODE_UTF16_CURLEN' words to `dst'
[[kernel, libc, nonnull]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char16_t *unicode_writeutf16([[out]] /*utf-16*/ char16_t *__restrict dst, char32_t ch) {
	if likely(ch <= 0xffff && (ch < 0xd800 || ch > 0xdfff)) {
		*dst++ = (char16_t)ch;
	} else {
		ch -= UTF16_SURROGATE_SHIFT;
		*dst++ = UTF16_HIGH_SURROGATE_MIN + (char16_t)(ch >> 10);
		*dst++ = UTF16_LOW_SURROGATE_MIN + (char16_t)(ch & 0x3ff);
	}
	return dst;
}

@@>> unicode_writeutf16_chk(3)
@@Same as `unicode_writeutf16()', but return `NULL' when `UNICODE_ISVALIDUTF16(ch)' is false
[[kernel, wunused]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char16_t *unicode_writeutf16_chk([[out]] /*utf-16*/ char16_t *__restrict dst, char32_t ch) {
	if unlikely(ch > UNICODE_MAXCHAR)
		return NULL;
	if likely(ch <= 0xffff) {
		if unlikely(ch >= 0xd800 && ch <= 0xdfff)
			return NULL;
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
/* >> unicode_readutf32(3)
 * Read a single Unicode character from a given UTF-32 string. */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32)(/*utf-32*/ char32_t const **__restrict __ptext) { return *(*__ptext)++; }
/* >> unicode_readutf32(3)
 * Read a single Unicode character from a given UTF-32 string. */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32)(/*utf-32*/ char32_t **__restrict __ptext) { return *(*__ptext)++; }
/* >> unicode_readutf32_swap(3)
 * Same as `unicode_readutf32()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32_swap)(/*utf-32*/ char32_t const **__restrict __ptext) { char32_t __res = *(*__ptext++); return __hybrid_bswap32(__res); }
/* >> unicode_readutf32_swap(3)
 * Same as `unicode_readutf32()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32_swap)(/*utf-32*/ char32_t **__restrict __ptext) { char32_t __res = *(*__ptext++); return __hybrid_bswap32(__res); }
/* >> unicode_readutf32_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32_rev)(/*utf-32*/ char32_t const **__restrict __ptext) { return *(--*__ptext); }
/* >> unicode_readutf32_rev(3)
 * Same  as  `unicode_readutf16', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32_rev)(/*utf-32*/ char32_t **__restrict __ptext) { return *(--*__ptext); }
/* >> unicode_readutf32_swap_rev(3)
 * Same as `unicode_readutf32_rev()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32_swap_rev)(/*utf-32*/ char32_t const **__restrict __ptext) { char32_t __res = *(--*__ptext); return __hybrid_bswap32(__res); }
/* >> unicode_readutf32_swap_rev(3)
 * Same as `unicode_readutf32_rev()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) char32_t (__LIBCCALL unicode_readutf32_swap_rev)(/*utf-32*/ char32_t **__restrict __ptext) { char32_t __res = *(--*__ptext); return __hybrid_bswap32(__res); }
/* >> unicode_readutf32_n(3)
 * Same as `unicode_readutf32()', but don't read past `text_end'. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_end) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __result;
}
/* >> unicode_readutf32_n(3)
 * Same as `unicode_readutf32()', but don't read past `text_end'. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_n)(/*utf-32*/ char32_t **__restrict __ptext, char32_t const *__text_end) {
	return unicode_readutf32_n((char32_t const **)__ptext, __text_end);
}
/* >> unicode_readutf32_rev_n(3)
 * Same as `unicode_readutf32()', but don't read before `text_start'. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_rev_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_start) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __result;
}
/* >> unicode_readutf32_rev_n(3)
 * Same as `unicode_readutf32()', but don't read before `text_start'. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_rev_n)(/*utf-32*/ char32_t **__restrict __ptext, char32_t const *__text_start) {
	return unicode_readutf32_rev_n((char32_t const **)__ptext, __text_start);
}
/* >> unicode_readutf32_swap_n(3)
 * Same as `unicode_readutf32_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_swap_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_end) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
/* >> unicode_readutf32_swap_n(3)
 * Same as `unicode_readutf32_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_swap_n)(/*utf-32*/ char32_t **__restrict __ptext, char32_t const *__text_end) {
	return unicode_readutf32_swap_n((char32_t const **)__ptext, __text_end);
}
/* >> unicode_readutf32_swap_rev_n(3)
 * Same as `unicode_readutf32_rev_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_swap_rev_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_start) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
/* >> unicode_readutf32_swap_rev_n(3)
 * Same as `unicode_readutf32_rev_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_swap_rev_n)(/*utf-32*/ char32_t **__restrict __ptext, char32_t const *__text_start) {
	return unicode_readutf32_swap_rev_n((char32_t const **)__ptext, __text_start);
}
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_UNICODE_H_PROTO */
/* >> unicode_readutf32(3)
 * Read a single Unicode character from a given UTF-32 string. */
__LOCAL __ATTR_INOUT(1) char32_t
(__LIBCCALL unicode_readutf32)(/*utf-32*/ char32_t const **__restrict __ptext) {
	return *(*__ptext)++;
}
/* >> unicode_readutf32_swap(3)
 * Same as `unicode_readutf32()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) char32_t
(__LIBCCALL unicode_readutf32_swap)(/*utf-32*/ char32_t const **__restrict __ptext) {
	char32_t __res = *(*__ptext++);
	return __hybrid_bswap32(__res);
}
/* >> unicode_readutf32_rev(3)
 * Same  as  `unicode_readutf32', but  read backwards,  with `*ptext'
 * starting out as a pointer after  the character to be read,  before
 * being updated to point to the start of the character that was read */
__LOCAL __ATTR_INOUT(1) char32_t
(__LIBCCALL unicode_readutf32_rev)(/*utf-32*/ char32_t const **__restrict __ptext) {
	return *(--*__ptext);
}
/* >> unicode_readutf32_swap_rev(3)
 * Same as `unicode_readutf32_rev()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) char32_t
(__LIBCCALL unicode_readutf32_swap_rev)(/*utf-32*/ char32_t const **__restrict __ptext) {
	char32_t __res = *(--*__ptext);
	return __hybrid_bswap32(__res);
}
/* >> unicode_readutf32_n(3)
 * Same as `unicode_readutf32()', but don't read past `text_end'. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_end) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __result;
}
/* >> unicode_readutf32_rev_n(3)
 * Same as `unicode_readutf32()', but don't read before `text_start'. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_rev_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_start) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text <= __text_start)
		return 0;
	__result = *--__text;
	*__ptext = __text;
	return __result;
}
/* >> unicode_readutf32_swap_n(3)
 * Same as `unicode_readutf32_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_swap_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_end) {
	char32_t __result;
	char32_t const *__text = *__ptext;
	if (__text >= __text_end)
		return 0;
	__result = *__text++;
	*__ptext = __text;
	return __hybrid_bswap32(__result);
}
/* >> unicode_readutf32_swap_rev_n(3)
 * Same as `unicode_readutf32_rev_n()', but read in reverse endian as that of the host CPU. */
__LOCAL __ATTR_INOUT(1) __ATTR_NONNULL((2)) char32_t
(__LIBCCALL unicode_readutf32_swap_rev_n)(/*utf-32*/ char32_t const **__restrict __ptext, char32_t const *__text_start) {
	char32_t __result;
	char32_t const *__text = *__ptext;
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
#endif /* __BYTE_ORDER__ == ... */

/* >> unicode_writeutf32(3)
 * Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This  function   will   write   at  most   `UNICODE_UTF32_CURLEN'   dwords   to   `dst' */
__LOCAL __ATTR_RETNONNULL __ATTR_OUT(1) char32_t *
(__LIBCCALL unicode_writeutf32)(/*utf-32*/ char32_t *__restrict __dst, char32_t __ch) {
	*__dst++ = __ch;
	return __dst;
}

}


@@>> unicode_len8to16(3)
@@Return the number of utf-16 words needed to encode a given utf-8 string
@@HINT: This is the exact number of words written by `unicode_8to16(3)'
[[wunused, decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
size_t unicode_len8to16([[in(utf8_bytes)]] /*utf-8*/ char const *__restrict utf8_text,
                        $size_t utf8_bytes) {
	size_t result = 0;
	char const *utf8_end = utf8_text + utf8_bytes;
	while (utf8_text < utf8_end) {
		char32_t ch;
		ch = unicode_readutf8_n((char const **)&utf8_text, utf8_end);
		++result;
		if likely(ch <= 0xffff && (ch < 0xd800 || ch > 0xdfff)) {
			/* Normal single-word utf-16 character */
		} else {
			/* Double-word utf-16 character */
			++result;
		}
	}
	return result;
}

@@>> unicode_len8to32(3)
@@Return the number of utf-32 character needed to encode a given utf-8 string
@@HINT: This is the exact number of words written by `unicode_8to32(3)'
[[wunused, decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
size_t unicode_len8to32([[in(utf8_bytes)]] /*utf-8*/ char const *__restrict utf8_text,
                        $size_t utf8_bytes) {
	size_t result = 0;
	char const *utf8_end = utf8_text + utf8_bytes;
	while (utf8_text < utf8_end) {
		unicode_readutf8_n((char const **)&utf8_text, utf8_end);
		++result;
	}
	return result;
}



@@>> unicode_8to16(3)
@@Convert a given utf-8 string to utf-16.
@@@param: utf16_dst:  A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_bytes)' words, or `*2' bytes
@@@param: utf8_text:  The input UTF-8 string to convert
@@@param: utf8_bytes: The amount of UTF-8 bytes found in `utf8_text'
@@@return: * : A pointer after the last written UTF-16 character
[[kernel, nonnull, decl_include("<hybrid/typecore.h>")]]
char16_t *unicode_8to16([[out]] /*utf-16*/ char16_t *__restrict utf16_dst,
                        [[in(utf8_bytes)]] /*utf-8*/ char const *__restrict utf8_text,
                        $size_t utf8_bytes) {
	char const *utf8_end = utf8_text + utf8_bytes;
	while (utf8_text < utf8_end) {
		char32_t ch;
		ch = unicode_readutf8_n((char const **)&utf8_text, utf8_end);
		utf16_dst = unicode_writeutf16(utf16_dst, ch);
	}
	return utf16_dst;
}

@@>> unicode_8to16_n(3)
@@Same as `unicode_8to16(3)', but don't write more than `utf16_maxwords' words to `utf16_dst'
@@@param: utf16_dst:      A buffer of at least `utf16_dst' words.
@@@param: utf16_maxwords: Max # of words to write to `utf16_dst'
@@@param: utf8_text:      The input UTF-8 string to convert
@@@param: utf8_bytes:     The amount of UTF-8 bytes found in `utf8_text'
@@@return: * : A pointer after the last written UTF-16 character
[[nonnull, decl_include("<hybrid/typecore.h>")]]
char16_t *unicode_8to16_n([[out(? <= utf16_maxwords)]] /*utf-16*/ char16_t *__restrict utf16_dst, $size_t utf16_maxwords,
                          [[in(? <= utf8_bytes)]] /*utf-8*/ char const *__restrict utf8_text, $size_t utf8_bytes) {
	char const *utf8_end = utf8_text + utf8_bytes;
	while (utf8_text < utf8_end && utf16_maxwords) {
		char32_t ch;
		ch = unicode_readutf8_n((char const **)&utf8_text, utf8_end);
		if likely(ch <= 0xffff && (ch < 0xd800 || ch > 0xdfff)) {
			*utf16_dst++ = (char16_t)ch;
			--utf16_maxwords;
		} else {
			ch -= UTF16_SURROGATE_SHIFT;
			*utf16_dst++ = UTF16_HIGH_SURROGATE_MIN + (char16_t)(ch >> 10);
			--utf16_maxwords;
			if unlikely(!utf16_maxwords)
				break;
			*utf16_dst++ = UTF16_LOW_SURROGATE_MIN + (char16_t)(ch & 0x3ff);
			--utf16_maxwords;
		}
	}
	return utf16_dst;
}


@@>> unicode_8to16_chk(3)
@@Same as `unicode_8to16()', but return `NULL' if an attempt was made to write an invalid character.
@@@param: utf16_dst:  A buffer of at least `UNICODE_8TO16_MAXBUF(utf8_bytes)' words, or `*2' bytes
@@@param: utf8_text:  The input UTF-8 string to convert
@@@param: utf8_bytes: The amount of UTF-8 bytes found in `utf8_text'
@@@return: * : A pointer after the last written UTF-16 character.
@@@return: NULL: Attempted to write an invalid character
[[wunused, decl_include("<hybrid/typecore.h>")]]
char16_t *unicode_8to16_chk([[out]] /*utf-16*/ char16_t *__restrict utf16_dst,
                            [[in(utf8_bytes)]] /*utf-8*/ char const *__restrict utf8_text,
                            $size_t utf8_bytes) {
	char const *utf8_end = utf8_text + utf8_bytes;
	while (utf8_text < utf8_end) {
		char32_t ch;
		ch = unicode_readutf8_n((char const **)&utf8_text, utf8_end);
		if (ch > UNICODE_MAXCHAR || (ch >= 0xd800 && ch <= 0xdfff))
			return NULL;
		utf16_dst = unicode_writeutf16(utf16_dst, ch);
	}
	return utf16_dst;
}

@@>> unicode_8to16_chk_n(3)
@@Same as `unicode_8to16_chk(3)', but don't write more than `utf16_maxwords' words to `utf16_dst'
@@@param: utf16_dst:      A buffer of at least `utf16_dst' words.
@@@param: utf16_maxwords: Max # of words to write to `utf16_dst'
@@@param: utf8_text:      The input UTF-8 string to convert
@@@param: utf8_bytes:     The amount of UTF-8 bytes found in `utf8_text'
@@@return: * :   A pointer after the last written UTF-16 character
@@@return: NULL: Attempted to write an invalid character
[[wunused, decl_include("<hybrid/typecore.h>")]]
char16_t *unicode_8to16_chk_n([[out(? <= utf16_maxwords)]] /*utf-16*/ char16_t *__restrict utf16_dst, $size_t utf16_maxwords,
                              [[in(? <= utf8_bytes)]] /*utf-8*/ char const *__restrict utf8_text, $size_t utf8_bytes) {
	char const *utf8_end = utf8_text + utf8_bytes;
	while (utf8_text < utf8_end && utf16_maxwords) {
		char32_t ch;
		ch = unicode_readutf8_n((char const **)&utf8_text, utf8_end);
		if (ch > UNICODE_MAXCHAR || (ch >= 0xd800 && ch <= 0xdfff))
			return NULL;
		if likely(ch <= 0xffff/* && (ch < 0xd800 || ch > 0xdfff)*/) {
			*utf16_dst++ = (char16_t)ch;
			--utf16_maxwords;
		} else {
			ch -= UTF16_SURROGATE_SHIFT;
			*utf16_dst++ = UTF16_HIGH_SURROGATE_MIN + (char16_t)(ch >> 10);
			--utf16_maxwords;
			if unlikely(!utf16_maxwords)
				break;
			*utf16_dst++ = UTF16_LOW_SURROGATE_MIN + (char16_t)(ch & 0x3ff);
			--utf16_maxwords;
		}
	}
	return utf16_dst;
}


@@>> unicode_8to32(3)
@@Convert a given utf-8 string to utf-32.
@@@param: utf32_dst:  A buffer of at least `UNICODE_8TO32_MAXBUF(utf8_bytes)' dwords, or `*4' bytes
@@@param: utf8_text:  The input UTF-8 string to convert
@@@param: utf8_bytes: The amount of UTF-8 bytes found in `utf8_text'
@@@return: * : A pointer after the last written UTF-32 character.
[[kernel, nonnull, decl_include("<hybrid/typecore.h>")]]
char32_t *unicode_8to32([[out]] /*utf-32*/ char32_t *__restrict utf32_dst,
                        [[in(utf8_bytes)]] /*utf-8*/ char const *__restrict utf8_text,
                        $size_t utf8_bytes) {
	char const *utf8_end = utf8_text + utf8_bytes;
	while (utf8_text < utf8_end)
		*utf32_dst++ = unicode_readutf8_n((char const **)&utf8_text, utf8_end);
	return utf32_dst;
}


@@>> unicode_8to32_n(3)
@@Same as `unicode_8to32(3)', but don't write more than `utf32_maxwords' words to `utf32_dst'
@@@param: utf32_dst:      A buffer of at least `utf32_maxwords' dwords
@@@param: utf32_maxwords: Max # of words to write to `utf16_dst'
@@@param: utf8_text:      The input UTF-8 string to convert
@@@param: utf8_bytes:     The amount of UTF-8 bytes found in `utf8_text'
@@@return: * : A pointer after the last written UTF-32 character.
[[nonnull, decl_include("<hybrid/typecore.h>")]]
char32_t *unicode_8to32_n([[out(? <= utf32_maxwords)]] /*utf-32*/ char32_t *__restrict utf32_dst, $size_t utf32_maxwords,
                          [[in(? <= utf8_bytes)]] /*utf-8*/ char const *__restrict utf8_text, $size_t utf8_bytes) {
	char const *utf8_end = utf8_text + utf8_bytes;
	while (utf8_text < utf8_end && utf32_maxwords) {
		*utf32_dst++ = unicode_readutf8_n((char const **)&utf8_text, utf8_end);
		--utf32_maxwords;
	}
	return utf32_dst;
}


@@>> unicode_16to8(3)
@@Convert a given utf-16 string to utf-8.
@@@param: utf8_dst:    A buffer of at least `UNICODE_16TO8_MAXBUF(utf16_words)' bytes
@@@param: utf16_text:  The input UTF-16 string to convert
@@@param: utf16_words: The amount of UTF-16 words found in `utf16_text'
@@@return: * : A pointer after the last written UTF-8 character
[[kernel, nonnull, decl_include("<hybrid/typecore.h>")]]
char *unicode_16to8([[out]] /*utf-8*/ char *__restrict utf8_dst,
                    [[in(utf16_words)]] /*utf-16*/ char16_t const *__restrict utf16_text,
                    $size_t utf16_words) {
	char16_t const *utf16_end = utf16_text + utf16_words;
	while (utf16_text < utf16_end) {
		char32_t ch;
		ch = unicode_readutf16_n((char16_t const **)&utf16_text, utf16_end);
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


@@>> unicode_16to8_n(3)
@@Same as `unicode_16to8(3)', but don't write more than `utf8_maxbytes' bytes to `utf8_dst'
@@@param: utf8_dst:      A buffer of at least `utf8_maxbytes' bytes
@@@param: utf8_maxbytes: Max # of bytes to write to `utf8_dst'
@@@param: utf16_text:    The input UTF-16 string to convert
@@@param: utf16_words:   The amount of UTF-16 words found in `utf16_text'
@@@return: * : A pointer after the last written UTF-8 character
[[nonnull, decl_include("<hybrid/typecore.h>")]]
char *unicode_16to8_n([[out(? <= utf8_maxbytes)]] /*utf-8*/ char *__restrict utf8_dst, $size_t utf8_maxbytes,
                      [[in(? <= utf16_words)]] /*utf-16*/ char16_t const *__restrict utf16_text, $size_t utf16_words) {
	char16_t const *utf16_end = utf16_text + utf16_words;
	while (utf16_text < utf16_end && utf8_maxbytes) {
		char32_t ch;
		ch = unicode_readutf16_n((char16_t const **)&utf16_text, utf16_end);
		if (ch <= UTF8_1BYTE_MAX) {
			*utf8_dst++ = (char)(u8)ch;
			--utf8_maxbytes;
		} else if (ch <= UTF8_2BYTE_MAX) {
			*utf8_dst++ = (char)(0xc0 | (u8)((ch >> 6)/* & 0x1f*/));
			--utf8_maxbytes;
			if unlikely(!utf8_maxbytes)
				break;
			*utf8_dst++ = (char)(0x80 | (u8)((ch) & 0x3f));
			--utf8_maxbytes;
		} else {
			*utf8_dst++ = (char)(0xe0 | (u8)((ch >> 12)/* & 0x0f*/));
			--utf8_maxbytes;
			if unlikely(!utf8_maxbytes)
				break;
			*utf8_dst++ = (char)(0x80 | (u8)((ch >> 6) & 0x3f));
			--utf8_maxbytes;
			if unlikely(!utf8_maxbytes)
				break;
			*utf8_dst++ = (char)(0x80 | (u8)((ch) & 0x3f));
			--utf8_maxbytes;
		}
	}
	return utf8_dst;
}


@@>> unicode_16to32(3)
@@Convert a given utf-16 string to utf-32.
@@@param: utf32_dst:   A buffer of at least `UNICODE_16TO32_MAXBUF(utf16_words)' dwords, or *4 bytes
@@@param: utf16_text:  The input UTF-16 string to convert
@@@param: utf16_words: The amount of UTF-16 words found in `utf16_text'
@@@return: * : A pointer after the last written UTF-32 character
[[kernel, nonnull, decl_include("<hybrid/typecore.h>")]]
char32_t *unicode_16to32([[out]] /*utf-32*/ char32_t *__restrict utf32_dst,
                         [[in(utf16_words)]] /*utf-16*/ char16_t const *__restrict utf16_text,
                         $size_t utf16_words) {
	char16_t const *utf16_end = utf16_text + utf16_words;
	while (utf16_text < utf16_end)
		*utf32_dst++ = unicode_readutf16_n((char16_t const **)&utf16_text, utf16_end);
	return utf32_dst;
}


@@>> unicode_16to32_n(3)
@@Same as `unicode_16to32(3)', but don't write more than `utf32_maxwords' words to `utf32_dst'
@@@param: utf32_dst:      A buffer of at least `utf32_maxwords' dwords
@@@param: utf32_maxwords: Max # of words to write to `utf16_dst'
@@@param: utf16_text:     The input UTF-16 string to convert
@@@param: utf16_words:    The amount of UTF-16 words found in `utf16_text'
@@@return: * : A pointer after the last written UTF-32 character
[[nonnull, decl_include("<hybrid/typecore.h>")]]
char32_t *unicode_16to32_n([[out(? <= utf32_maxwords)]] /*utf-32*/ char32_t *__restrict utf32_dst, $size_t utf32_maxwords,
                           [[in(? <= utf16_words)]] /*utf-16*/ char16_t const *__restrict utf16_text, $size_t utf16_words) {
	char16_t const *utf16_end = utf16_text + utf16_words;
	while (utf16_text < utf16_end && utf32_maxwords) {
		*utf32_dst++ = unicode_readutf16_n((char16_t const **)&utf16_text, utf16_end);
		--utf32_maxwords;
	}
	return utf32_dst;
}


@@>> unicode_32to8(3)
@@Convert a given utf-32 string to utf-8.
@@@param: utf8_dst:     A buffer of at least `UNICODE_32TO8_MAXBUF(utf32_dwords)' bytes
@@@param: utf32_text:   The input UTF-32 string to convert
@@@param: utf32_dwords: The amount of UTF-32 dwords found in `utf32_text'
@@@return: * : A pointer after the last written UTF-8 character
[[kernel, nonnull, decl_include("<hybrid/typecore.h>")]]
char *unicode_32to8([[out]] /*utf-8*/ char *__restrict utf8_dst,
                    [[in(utf32_dwords)]] /*utf-32*/ char32_t const *__restrict utf32_text,
                    $size_t utf32_dwords) {
	while (utf32_dwords--)
		utf8_dst = unicode_writeutf8(utf8_dst, *utf32_text++);
	return utf8_dst;
}

@@>> unicode_32to8_n(3)
@@Same as `unicode_32to8(3)', but don't write more than `utf8_maxbytes' bytes to `utf8_dst'
@@@param: utf8_dst:      A buffer of at least `utf8_maxbytes' bytes
@@@param: utf8_maxbytes: Max # of words to write to `utf8_dst'
@@@param: utf32_text:    The input UTF-32 string to convert
@@@param: utf32_dwords:  The amount of UTF-32 dwords found in `utf32_text'
@@@return: * : A pointer after the last written UTF-8 character
[[nonnull, decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
char *unicode_32to8_n([[out(? <= utf8_maxbytes)]] /*utf-8*/ char *__restrict utf8_dst, $size_t utf8_maxbytes,
                      [[in(? <= utf32_dwords)]] /*utf-32*/ char32_t const *__restrict utf32_text, $size_t utf32_dwords) {
	char *utf8_bufend = utf8_dst + utf8_maxbytes;
	while (utf32_dwords-- && utf8_dst < utf8_bufend) {
		utf8_dst = unicode_writeutf8_n(utf8_dst, *utf32_text++,
		                               (size_t)(utf8_bufend - utf8_dst));
	}
	return utf8_dst;
}


@@>> unicode_32to16(3)
@@Convert a given utf-32 string to utf-16.
@@@param: utf16_dst:    A buffer of at least `UNICODE_32TO16_MAXBUF(utf32_dwords)' words, or *2 bytes
@@@param: utf32_text:   The input UTF-32 string to convert
@@@param: utf32_dwords: The amount of UTF-32 dwords found in `utf32_text'
@@@return: * : A pointer after the last written UTF-16 character
[[kernel, nonnull, decl_include("<hybrid/typecore.h>")]]
char16_t *unicode_32to16([[out]] /*utf-16*/ char16_t *__restrict utf16_dst,
                         [[in(utf32_dwords)]] /*utf-32*/ char32_t const *__restrict utf32_text,
                         $size_t utf32_dwords) {
	while (utf32_dwords--)
		utf16_dst = unicode_writeutf16(utf16_dst, *utf32_text++);
	return utf16_dst;
}


@@>> unicode_32to16_n(3)
@@Same as `unicode_32to16(3)', but don't write more than `utf16_maxwords' words to `utf16_dst'
@@@param: utf16_dst:      A buffer of at least `utf16_dst' words.
@@@param: utf16_maxwords: Max # of words to write to `utf16_dst'
@@@param: utf32_text:     The input UTF-32 string to convert
@@@param: utf32_dwords:   The amount of UTF-32 dwords found in `utf32_text'
@@@return: * : A pointer after the last written UTF-16 character
[[nonnull, decl_include("<hybrid/typecore.h>")]]
char16_t *unicode_32to16_n([[out(? <= utf16_maxwords)]] /*utf-16*/ char16_t *__restrict utf16_dst, $size_t utf16_maxwords,
                           [[in(? <= utf32_dwords)]] /*utf-32*/ char32_t const *__restrict utf32_text, $size_t utf32_dwords) {
	while (utf32_dwords-- && utf16_maxwords) {
		char32_t ch = *utf32_text++;
		if likely(ch <= 0xffff && (ch < 0xd800 || ch > 0xdfff)) {
			*utf16_dst++ = (char16_t)ch;
			--utf16_maxwords;
		} else {
			ch -= UTF16_SURROGATE_SHIFT;
			*utf16_dst++ = UTF16_HIGH_SURROGATE_MIN + (char16_t)(ch >> 10);
			--utf16_maxwords;
			if unlikely(!utf16_maxwords)
				break;
			*utf16_dst++ = UTF16_LOW_SURROGATE_MIN + (char16_t)(ch & 0x3ff);
			--utf16_maxwords;
		}
	}
	return utf16_dst;
}






@@>> unicode_c8toc16(3)
@@@return: *:          Success (*pc16 was filled; the return value
@@                     is  the  number  of bytes  taken  from `s')
@@@return: 0:          Success (*pc16 was filled; `mbs' was modified,
@@                     but nothing was read  from `s'; in this  case,
@@                     a surrogate was written)
@@@return: (size_t)-1: Unicode error (the given input string isn't
@@                     a valid unicode sequence)
@@@return: (size_t)-2: Success, but  no  character  was  generated
@@                     (`s...+=n', together with `mbs' doesn't for
@@                     a full  character, but  `mbs' was  updated)
[[decl_include("<bits/crt/mbstate.h>")]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
$size_t unicode_c8toc16([[out]] char16_t *__restrict pc16,
                        [[in(return <= n)]] /*utf-8*/ char const *__restrict s, $size_t n,
                        [[inout]] mbstate_t *__restrict mbs) {
	char32_t resch;
	size_t i;
	if ((mbs->@__mb_word@ & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_WR_UTF16_LO) {
		*pc16 = 0xdc00 + (mbs->@__mb_word@ & 0x3ff);
		mbs->@__mb_word@ = __MBSTATE_TYPE_EMPTY;
		return 0;
	}
	for (i = 0; i < n; ++i) {
		uint32_t state;
		uint8_t ch;
		state = mbs->@__mb_word@ & __MBSTATE_TYPE_MASK;
		ch = (uint8_t)s[i];
		if (state == __MBSTATE_TYPE_EMPTY) {
			if (ch <= 0x7f) {
				*pc16 = ch;
				goto done;
			} else if (ch <= 0xbf) { /* NOLINT */
				goto error_ilseq;
			} else if (ch <= 0xdf) {
				mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_2_2 | (ch & 0x1f);
				continue;
			} else if (ch <= 0xef) {
				mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_3_2 | ((ch & 0xf) << 6);
				continue;
			} else if (ch <= 0xf7) {
				mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_4_2 | ((ch & 0x7) << 12);
				continue;
			} else if (ch <= 0xfb) {
				mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_5_2 | ((ch & 0x3) << 18);
				continue;
			} else if (ch <= 0xfd) {
				mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_6_2 | ((ch & 0x1) << 24);
				continue;
			} else {
				goto error_ilseq;
			}
		}
		if ((ch & 0xc0) != 0x80)
			goto error_ilseq; /* Must be a follow-up byte */
		ch &= 0x3f;
		switch (mbs->@__mb_word@ & __MBSTATE_TYPE_MASK) {

		case __MBSTATE_TYPE_UTF8_2_2: /* expect 2nd character of a 2-byte utf-8 sequence. { WORD & 0x0000001f } */
			*pc16 = ((mbs->@__mb_word@ & 0x1f) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_3_2: /* expect 2nd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_3_3 | (mbs->@__mb_word@ & 0x3c0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_3_3: /* expect 3rd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0, WORD & 0x0000003f } */
			resch = ((mbs->@__mb_word@ & 0x3ff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty_chk_surrogate;

		case __MBSTATE_TYPE_UTF8_4_2: /* expect 2nd character of a 4-byte utf-8 sequence. { WORD & 0x00007000 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_4_3 | (mbs->@__mb_word@ & 0x7000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_4_3: /* expect 3rd character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_4_4 | (mbs->@__mb_word@ & 0x7fc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_4_4: /* expect 4th character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			resch = ((mbs->@__mb_word@ & 0x7fff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty_chk_surrogate;

		case __MBSTATE_TYPE_UTF8_5_2: /* expect 2nd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_5_3 | (mbs->@__mb_word@ & 0xc0000) | ((uint32_t)ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_5_3: /* expect 3rd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_5_4 | (mbs->@__mb_word@ & 0xff000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_5_4: /* expect 4th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_5_5 | (mbs->@__mb_word@ & 0xfffc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_5_5: /* expect 5th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			resch = ((mbs->@__mb_word@ & 0x000cffff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty_chk_surrogate;

		case __MBSTATE_TYPE_UTF8_6_2: /* expect 2nd character of a 6-byte utf-8 sequence. { WORD & 0x01000000 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_6_3 | (mbs->@__mb_word@ & 0x1000000) | ((uint32_t)ch << (3 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_3: /* expect 3rd character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_6_4 | (mbs->@__mb_word@ & 0x1fc0000) | ((uint32_t)ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_4: /* expect 4th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_6_5 | (mbs->@__mb_word@ & 0x1fff000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_6_5: /* expect 5th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_6_6 | (mbs->@__mb_word@ & 0x1ffffc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_6_6: /* expect 6th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			resch = ((mbs->@__mb_word@ & 0x1ffffff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
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
		*pc16 = 0xd800 + (char16_t)(resch >> 10);
		mbs->@__mb_word@ = __MBSTATE_TYPE_WR_UTF16_LO | (u16)(resch & 0x3ff);
	} else {
		*pc16 = (char16_t)resch;
	}
done_empty:
	mbs->@__mb_word@ = __MBSTATE_TYPE_EMPTY;
done:
	return i + 1;
}


@@>> unicode_c8toc32(3)
@@@return: *:          Success (*pc32 was filled; the return value
@@                     is  the  number  of bytes  taken  from `s')
@@@return: (size_t)-1: Unicode error (the given input string isn't
@@                     a valid unicode sequence)
@@@return: (size_t)-2: Success, but  no  character  was  generated
@@                     (`s...+=n', together with `mbs' doesn't for
@@                     a full  character, but  `mbs' was  updated)
[[decl_include("<bits/crt/mbstate.h>")]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
$size_t unicode_c8toc32([[out]] char32_t *__restrict pc32,
                        [[in(return <= n)]] /*utf-8*/ char const *__restrict s, $size_t n,
                        [[inout]] mbstate_t *__restrict mbs) {
	size_t i;
	for (i = 0; i < n; ++i) {
		uint32_t state;
		uint8_t ch;
		state = mbs->@__mb_word@ & __MBSTATE_TYPE_MASK;
		ch = (uint8_t)s[i];
		if (state == __MBSTATE_TYPE_EMPTY) {
			if (ch <= 0x7f) {
				*pc32 = ch;
				goto done;
			} else if (ch <= 0xbf) { /* NOLINT */
				goto error_ilseq;
			} else if (ch <= 0xdf) {
				mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_2_2 | (ch & 0x1f);
				continue;
			} else if (ch <= 0xef) {
				mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_3_2 | ((ch & 0xf) << 6);
				continue;
			} else if (ch <= 0xf7) {
				mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_4_2 | ((ch & 0x7) << 12);
				continue;
			} else if (ch <= 0xfb) {
				mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_5_2 | ((ch & 0x3) << 18);
				continue;
			} else if (ch <= 0xfd) {
				mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_6_2 | ((ch & 0x1) << 24);
				continue;
			} else {
				goto error_ilseq;
			}
		}
		if ((ch & 0xc0) != 0x80)
			goto error_ilseq; /* Must be a follow-up byte */
		ch &= 0x3f;
		switch (mbs->@__mb_word@ & __MBSTATE_TYPE_MASK) {

		case __MBSTATE_TYPE_UTF8_2_2: /* expect 2nd character of a 2-byte utf-8 sequence. { WORD & 0x0000001f } */
			*pc32 = ((mbs->@__mb_word@ & 0x1f) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_3_2: /* expect 2nd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_3_3 | (mbs->@__mb_word@ & 0x3c0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_3_3: /* expect 3rd character of a 3-byte utf-8 sequence. { WORD & 0x000003c0, WORD & 0x0000003f } */
			*pc32 = ((mbs->@__mb_word@ & 0x3ff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_4_2: /* expect 2nd character of a 4-byte utf-8 sequence. { WORD & 0x00007000 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_4_3 | (mbs->@__mb_word@ & 0x7000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_4_3: /* expect 3rd character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_4_4 | (mbs->@__mb_word@ & 0x7fc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_4_4: /* expect 4th character of a 4-byte utf-8 sequence. { WORD & 0x00007000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			*pc32 = ((mbs->@__mb_word@ & 0x7fff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_5_2: /* expect 2nd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_5_3 | (mbs->@__mb_word@ & 0xc0000) | ((uint32_t)ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_5_3: /* expect 3rd character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_5_4 | (mbs->@__mb_word@ & 0xff000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_5_4: /* expect 4th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_5_5 | (mbs->@__mb_word@ & 0xfffc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_5_5: /* expect 5th character of a 5-byte utf-8 sequence. { WORD & 0x000c0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			*pc32 = ((mbs->@__mb_word@ & 0x000cffff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		case __MBSTATE_TYPE_UTF8_6_2: /* expect 2nd character of a 6-byte utf-8 sequence. { WORD & 0x01000000 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_6_3 | (mbs->@__mb_word@ & 0x1000000) | ((uint32_t)ch << (3 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_3: /* expect 3rd character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_6_4 | (mbs->@__mb_word@ & 0x1fc0000) | ((uint32_t)ch << (2 * __MBSTATE_TYPE_UTF8_SHIFT));
			break;

		case __MBSTATE_TYPE_UTF8_6_4: /* expect 4th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_6_5 | (mbs->@__mb_word@ & 0x1fff000) | ((uint32_t)ch << __MBSTATE_TYPE_UTF8_SHIFT);
			break;

		case __MBSTATE_TYPE_UTF8_6_5: /* expect 5th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0 } */
			mbs->@__mb_word@ = __MBSTATE_TYPE_UTF8_6_6 | (mbs->@__mb_word@ & 0x1ffffc0) | ch;
			break;

		case __MBSTATE_TYPE_UTF8_6_6: /* expect 6th character of a 6-byte utf-8 sequence. { WORD & 0x01000000, WORD & 0x00fc0000, WORD & 0x0003f000, WORD & 0x00000fc0, WORD & 0x0000003f } */
			*pc32 = ((mbs->@__mb_word@ & 0x1ffffff) << __MBSTATE_TYPE_UTF8_SHIFT) | ch;
			goto done_empty;

		default:
error_ilseq:
			return (size_t)-1;
		}
	}
	/* Incomplete sequence (but `mbs' may have been updated) */
	return (size_t)-2;
done_empty:
	mbs->@__mb_word@ = __MBSTATE_TYPE_EMPTY;
done:
	return i + 1;
}


@@>> unicode_c16toc8(3)
@@@return: 0 :         Success, but no characters were generated
@@@return: * :         Success  (this many bytes were written to
@@                     `*pc8'; max is `UNICODE_16TO8_MAXBUF(1)')
@@@return: (size_t)-1: Unicode error (the given input string
@@                     isn't  a   valid  unicode   sequence)
[[decl_include("<bits/crt/mbstate.h>")]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
$size_t unicode_c16toc8([[out/*(return <= 3)*/]] char pc8[3], char16_t c16,
                        [[inout]] mbstate_t *__restrict mbs) {
	char32_t ch32;
	if ((mbs->@__mb_word@ & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_UTF16_LO) {
		if unlikely(!(c16 >= UTF16_LOW_SURROGATE_MIN &&
		              c16 <= UTF16_LOW_SURROGATE_MAX))
			return (size_t)-1;
		ch32 = ((mbs->@__mb_word@ & 0x000003ff) << 10) + 0x10000 + ((u16)c16 - 0xdc00);
		mbs->@__mb_word@ = __MBSTATE_TYPE_EMPTY;
	} else if (c16 >= UTF16_HIGH_SURROGATE_MIN && c16 <= UTF16_HIGH_SURROGATE_MAX) {
		mbs->@__mb_word@ = __MBSTATE_TYPE_UTF16_LO | ((u16)c16 - UTF16_HIGH_SURROGATE_MIN);
		return 0;
	} else {
		ch32 = (char32_t)c16;
	}
	if likely(ch32 <= UTF8_1BYTE_MAX) {
		pc8[0] = (char)(u8)ch32;
		return 1;
	}
	if (ch32 <= UTF8_2BYTE_MAX) {
		pc8[0] = (char)(0xc0 | (u8)((ch32 >> 6)/* & 0x1f*/));
		pc8[1] = (char)(0x80 | (u8)((ch32) & 0x3f));
		return 2;
	}
	pc8[0] = (char)(0xe0 | (u8)((ch32 >> 12)/* & 0x0f*/));
	pc8[1] = (char)(0x80 | (u8)((ch32 >> 6) & 0x3f));
	pc8[2] = (char)(0x80 | (u8)((ch32) & 0x3f));
	return 3;
}



%[define(__UNICODE_FORMAT_XTOY_BUFSIZE = 64)]



//struct format_8tow_data {
//	__pc16formatprinter fd_printer;    /* [1..1] Inner printer */
//	void               *fd_arg;        /* Argument for `fd_printer' */
//	mbstate_t           fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
//};

@@>> format_8tow(3)
@@Format printer  (compatible  with  `__pformatprinter')  for
@@converting UTF-8 unicode input data into a UTF-16/32 output
[[wchar, hidden, decl_include("<bits/crt/format-printer.h>"), cc(__FORMATPRINTER_CC)]]
[[impl_include("<bits/crt/mbstate.h>", "<bits/crt/wformat-printer.h>")]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
$ssize_t format_8tow([[nonnull]] /*struct format_8tow_data **/ void *arg,
                     [[in(datalen)]] /*utf-8*/ char const *data, $size_t datalen) {
	struct __local_format_8tow_data {
		$pwformatprinter fd_printer;    /* [1..1] Inner printer */
		void            *fd_arg;        /* Argument for `fd_printer' */
		$mbstate_t       fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	wchar_t buf[__UNICODE_FORMAT_XTOY_BUFSIZE], *dst = buf;
	struct __local_format_8tow_data *closure;
	ssize_t temp, result = 0;
	closure = (struct __local_format_8tow_data *)arg;
	while (datalen) {
		do {
			size_t error;
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
			error = unicode_c8toc16((char16_t *)dst, data, datalen, &closure->fd_incomplete);
@@pp_else@@
			error = unicode_c8toc32((char32_t *)dst, data, datalen, &closure->fd_incomplete);
@@pp_endif@@
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




%{

struct format_8to16_data {
	__pc16formatprinter fd_printer;    /* [1..1] Inner printer */
	void               *fd_arg;        /* Argument for `fd_printer' */
	mbstate_t           fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
};
}

@@>> format_8to16(3)
@@Format printer (compatible with `__pformatprinter')  for
@@converting UTF-8 unicode input data into a UTF-16 output
[[decl_include("<bits/crt/format-printer.h>"), cc(__FORMATPRINTER_CC)]]
[[decl_include("<hybrid/typecore.h>")]]
$ssize_t format_8to16([[nonnull]] /*struct format_8to16_data **/ void *arg,
                      [[in(datalen)]] /*utf-8*/ char const *data, $size_t datalen)
	%{uchar16("format_8tow")}

%{

struct format_8to32_data {
	__pc32formatprinter fd_printer;    /* [1..1] Inner printer */
	void               *fd_arg;        /* Argument for `fd_printer' */
	mbstate_t           fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
};
}

@@>> format_8to32(3)
@@Format printer (compatible with `__pformatprinter')  for
@@converting UTF-8 unicode input data into a UTF-32 output
[[decl_include("<bits/crt/format-printer.h>"), cc(__FORMATPRINTER_CC)]]
[[decl_include("<hybrid/typecore.h>")]]
$ssize_t format_8to32([[nonnull]] /*struct format_8to32_data **/ void *arg,
                      [[in(datalen)]] /*utf-8*/ char const *data, $size_t datalen)
	%{uchar32("format_8tow")}


//struct format_wto8_data {
//	__pformatprinter fd_printer;   /* [1..1] Inner printer */
//	void            *fd_arg;       /* Argument for `fd_printer' */
//#if __SIZEOF_WCHAR_T__ == 2
//	char16_t         fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
//#endif /* __SIZEOF_WCHAR_T__ == 2 */
//};

@@>> format_wto8(3)
@@Format   printer   (compatible  with   `pc16formatprinter')  for
@@converting wide-character unicode input data into a UTF-8 output
[[wchar, hidden, decl_include("<bits/crt/wformat-printer.h>"), cc(__WFORMATPRINTER_CC)]]
[[impl_include("<bits/crt/format-printer.h>")]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
$ssize_t format_wto8([[nonnull]] /*struct format_wto8_data **/ void *arg,
                     [[in(datalen)]] $wchar_t const *data, $size_t datalen) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	struct __local_format_16to8_data {
		$pformatprinter fd_printer;   /* [1..1] Inner printer */
		void           *fd_arg;       /* Argument for `fd_printer' */
		char16_t        fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
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
	char16_t         fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
};
}

@@>> format_16to8(3)
@@Format printer (compatible with `pc16formatprinter') for
@@converting UTF-16 unicode input data into a UTF-8 output
[[decl_include("<bits/crt/uformat-printer.h>"), cc(__C16FORMATPRINTER_CC)]]
[[decl_include("<hybrid/typecore.h>")]]
$ssize_t format_16to8([[nonnull]] /*struct format_16to8_data **/ void *arg,
                      [[in(datalen)]] char16_t const *data, $size_t datalen)
	%{uchar16("format_wto8")}


%{

struct format_32to8_data {
	__pformatprinter fd_printer; /* [1..1] Inner printer */
	void            *fd_arg;     /* Argument for `fd_printer' */
};
}

@@>> format_32to8(3)
@@Format printer (compatible with `pc32formatprinter') for
@@converting UTF-32 unicode input data into a UTF-8 output
[[decl_include("<bits/crt/uformat-printer.h>"), cc(__C32FORMATPRINTER_CC)]]
[[decl_include("<hybrid/typecore.h>")]]
$ssize_t format_32to8([[nonnull]] /*struct format_32to8_data **/ void *arg,
                      [[in(datalen)]] char32_t const *data, $size_t datalen)
	%{uchar32("format_wto8")}



//struct format_wto32_data {
//	__pc32formatprinter fd_printer;   /* [1..1] Inner printer */
//	void               *fd_arg;       /* Argument for `fd_printer' */
//#if __SIZEOF_WCHAR_T__ == 2
//	char16_t            fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
//#endif /* __SIZEOF_WCHAR_T__ == 2 */
//};

@@>> format_wto32(3)
@@Format  printer   (compatible   with   `pc16formatprinter')   for
@@converting wide-character unicode input data into a UTF-32 output
[[hidden, impl_include("<bits/crt/uformat-printer.h>"), wchar]]
[[decl_include("<bits/crt/wformat-printer.h>"), cc(__WFORMATPRINTER_CC)]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
$ssize_t format_wto32([[nonnull]] /*struct format_wto32_data **/ void *arg,
                      [[in(datalen)]] $wchar_t const *data, $size_t datalen) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	struct __local_format_16to32_data {
		$pc32formatprinter fd_printer;   /* [1..1] Inner printer */
		void              *fd_arg;       /* Argument for `fd_printer' */
		char16_t           fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
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
		$pc32formatprinter fd_printer;   /* [1..1] Inner printer */
		void              *fd_arg;       /* Argument for `fd_printer' */
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
	char16_t            fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
};
}

@@>> format_16to32(3)
@@Format printer (compatible with `pc16formatprinter')  for
@@converting UTF-16 unicode input data into a UTF-32 output
[[decl_include("<bits/crt/uformat-printer.h>"), cc(__C16FORMATPRINTER_CC)]]
[[decl_include("<hybrid/typecore.h>")]]
$ssize_t format_16to32([[nonnull]] /*struct format_16to32_data **/ void *arg,
                       [[in(datalen)]] char16_t const *data, $size_t datalen)
	%{uchar16("format_wto32")}


//struct format_wto16_data {
//	__pc16formatprinter fd_printer; /* [1..1] Inner printer */
//	void               *fd_arg;     /* Argument for `fd_printer' */
//};

@@>> format_wto16(3)
@@Format   printer   (compatible   with   `pwformatprinter')    for
@@converting wide-character unicode input data into a UTF-16 output
[[hidden, wchar, decl_include("<bits/crt/wformat-printer.h>"), cc(__WFORMATPRINTER_CC)]]
[[impl_include("<bits/crt/format-printer.h>", "<bits/crt/uformat-printer.h>")]]
[[decl_include("<hybrid/typecore.h>"), impl_include("<hybrid/typecore.h>")]]
$ssize_t format_wto16([[nonnull]] /*struct format_wto16_data **/ void *arg,
                      [[in(datalen)]] $wchar_t const *data, $size_t datalen) {
@@pp_if __SIZEOF_WCHAR_T__ == 4@@
	struct __local_format_32to16_data {
		$pc16formatprinter fd_printer; /* [1..1] Inner printer */
		void              *fd_arg;     /* Argument for `fd_printer' */
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
		$pc16formatprinter fd_printer;   /* [1..1] Inner printer */
		void              *fd_arg;       /* Argument for `fd_printer' */
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

@@>> format_32to16(3)
@@Format printer (compatible with `__pc32formatprinter') for
@@converting UTF-32 unicode input data into a UTF-16  output
[[decl_include("<bits/crt/uformat-printer.h>"), cc(__C32FORMATPRINTER_CC)]]
[[decl_include("<hybrid/typecore.h>")]]
$ssize_t format_32to16([[nonnull]] /*struct format_32to16_data **/ void *arg,
                       [[in(datalen)]] char32_t const *data, $size_t datalen)
	%{uchar32("format_wto16")}




@@>> __unicode_descriptor(3)
@@Return the internal descriptor for the given `ch'
@@This is the main accessor function for the unicode database, but
@@should not be called directly (unless you know what you're doing
@@and are aware that your code might break should this API ever be
@@changed)
@@Also note that this function never returns `NULL'!
[[guard, libc, const, nonnull, nothrow]]
[[decl_include("<bits/crt/unicode.h>", "<hybrid/typecore.h>")]]
struct __unitraits const *__unicode_descriptor(char32_t ch);

@@>> __unicode_descriptor_digit(3), __unicode_descriptor_digit64(3)
@@Return the integer constant associated  with a given digit  index
@@Returns `0' if the given index is invalid
@@@param: digit_idx: As read from `__unitraits::__ut_digit_idx'
[[guard, libc, const, wunused, nothrow]]
[[decl_include("<hybrid/typecore.h>")]]
$uint8_t __unicode_descriptor_digit($uint8_t digit_idx);

%#ifdef __UINT64_TYPE__
[[guard, libc, const, wunused, nothrow]]
[[doc_alias("__unicode_descriptor_digit")]]
[[decl_include("<hybrid/typecore.h>")]]
$uint64_t __unicode_descriptor_digit64($uint8_t digit_idx);
%#endif /* __UINT64_TYPE__ */

%#ifndef __NO_FPU
@@>> __unicode_descriptor_digitd(3), __unicode_descriptor_digitld(3)
@@Return the floating-point constant associated with a given digit index
@@Returns `0.0' if the given index is invalid
@@@param: digit_idx: As read from `__unitraits::__ut_digit_idx'
[[guard, libc, const, wunused, nothrow]]
[[decl_include("<hybrid/typecore.h>")]]
double __unicode_descriptor_digitd($uint8_t digit_idx);

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[guard, libc, const, wunused, nothrow]]
[[doc_alias("__unicode_descriptor_digitd")]]
[[decl_include("<hybrid/typecore.h>")]]
__LONGDOUBLE __unicode_descriptor_digitld($uint8_t digit_idx);
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */


%{

/* The max number of characters ever written by `unicode_fold' */
#define UNICODE_FOLDED_MAX 3

}

@@>> unicode_fold(3)
@@Fold the given unicode character `ch'
[[libc, inline, no_extern_inline, nonnull, userimpl]]
[[decl_include("<hybrid/typecore.h>")]]
char32_t *unicode_fold(char32_t ch, [[out]] char32_t buf[3]) {
	buf[0] = ch;
	return buf + 1;
}



%{

/* Unicode character traits test functions */
#ifdef ____unicode_descriptor_defined
#define unicode_iscntrl(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISCNTRL) != 0)   /* Control characters */
#define unicode_istab(ch)     ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISTAB) != 0)     /* 09, 0B-0C */
#define unicode_iswhite(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISWHITE) != 0)   /* Pure whitespace characters (excluding tabs and line-feeds) */
#define unicode_isempty(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISEMPTY) != 0)   /* unicode_istab || unicode_iswhite */
#define unicode_islf(ch)      ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISLF) != 0)      /* Line-feed characters */
#define unicode_isspace(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISSPACE) != 0)   /* unicode_isempty | unicode_islf */
#define unicode_islower(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISLOWER) != 0)   /* Lowercase characters */
#define unicode_isupper(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISUPPER) != 0)   /* Uppercase characters */
#define unicode_isalpha(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISALPHA) != 0)   /* Alphabetical characters */
#define unicode_isdigit(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISDIGIT) != 0)   /* Only includes stuff like "2" */
#define unicode_ishex(ch)     ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISHEX) != 0)     /* 'a'-'f', 'A'-'F' */
#define unicode_isxdigit(ch)  ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISXDIGIT) != 0)  /* unicode_isdigit || unicode_ishex */
#define unicode_isalnum(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISALNUM) != 0)   /* unicode_isdigit || unicode_isalpha */
#define unicode_ispunct(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISPUNCT) != 0)   /* Punctuation (such as '.') */
#define unicode_isgraph(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISGRAPH) != 0)   /* Graphical characters (everything printable, excluding spaces) */
#define unicode_isprint(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISPRINT) != 0)   /* unicode_isgraph || unicode_iswhite */
#define unicode_isblank(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISBLANK) != 0)   /* unicode_iswhite || (ch == '\t') */
#define unicode_istitle(ch)   ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISTITLE) != 0)   /* title-case */
#define unicode_isnumeric(ch) ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISNUMERIC) != 0) /* Includes stuff like "²" */
#define unicode_issymstrt(ch) ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISSYMSTRT) != 0) /* Character may appear at the start of a symbol name */
#define unicode_issymcont(ch) ((__unicode_descriptor(ch)->__ut_flags & __UNICODE_ISSYMCONT) != 0) /* Character may appear in the middle of a symbol name */

#define unicode_tolower(ch) ((ch) + __unicode_descriptor(ch)->__ut_lower)
#define unicode_toupper(ch) ((ch) + __unicode_descriptor(ch)->__ut_upper)
#define unicode_totitle(ch) ((ch) + __unicode_descriptor(ch)->__ut_title)

/* >> unicode_asdigit(3)
 * Check if `ch' is a digit- or hex-character (s.a. `unicode_isxdigit()'),
 * and if so, store  its digit value in  `*presult' and return `true'  iff
 * its  digit value is  less than `radix'.  Otherwise, leave `*presult' as
 * undefined and return `false'.
 * Note that `radix' values >= 16 are supported, but the cut-off  value
 * until which they are is  implementation-defined (but always >=  16).
 * If digit characters which equate to values greater than 16 should be
 * supported, then `unicode_getnumeric(64|dbl|ldbl)' should be used! */
#ifdef __INTELLISENSE__
__ATTR_WUNUSED __ATTR_OUT(3) __BOOL
__NOTHROW_NCX(unicode_asdigit)(char32_t ch, __UINT8_TYPE__ radix,
                               __UINT8_TYPE__ * __restrict presult);
#else /* __INTELLISENSE__ */
#define unicode_asdigit(ch, radix, presult) \
	((*(presult) = __unicode_asdigit(ch)) <= (radix))
#endif /* !__INTELLISENSE__ */

#ifndef ____unicode_asdigit_defined
#define ____unicode_asdigit_defined
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT8_TYPE__
__NOTHROW(__LIBCCALL __unicode_asdigit)(char32_t __ch) {
	struct __unitraits const *__traits = __unicode_descriptor(__ch);
	if (!(__traits->__ut_flags & __UNICODE_ISXDIGIT))
		return 0xff;
	return __traits->__ut_digit_idx;
}
#endif /* !____unicode_asdigit_defined */

/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT8_TYPE__
__NOTHROW(__LIBCCALL unicode_getnumeric)(char32_t __ch) {
	struct __unitraits const *__traits = __unicode_descriptor(__ch);
	if __likely(__traits->__ut_digit_idx <= __UNICODE_DIGIT_IDENTITY_MAX)
		return __traits->__ut_digit_idx;
#ifdef ____unicode_descriptor_digit_defined
	return __unicode_descriptor_digit(__traits->__ut_digit_idx);
#elif defined(____unicode_descriptor_digit64_defined)
	return (__UINT8_TYPE__)__unicode_descriptor_digit64(__traits->__ut_digit_idx);
#else /* ____unicode_descriptor_digit64_defined */
	return 0;
#endif /* !____unicode_descriptor_digit64_defined */
}

#ifdef __UINT64_TYPE__
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT64_TYPE__
__NOTHROW(__LIBCCALL unicode_getnumeric64)(char32_t __ch) {
	struct __unitraits const *__traits = __unicode_descriptor(__ch);
	if __likely(__traits->__ut_digit_idx <= __UNICODE_DIGIT_IDENTITY_MAX)
		return __traits->__ut_digit_idx;
#ifdef ____unicode_descriptor_digit64_defined
	return __unicode_descriptor_digit64(__traits->__ut_digit_idx);
#elif defined(____unicode_descriptor_digit_defined)
	return __unicode_descriptor_digit(__traits->__ut_digit_idx);
#else /* ... */
	return 0;
#endif /* !... */
}
#endif /* __UINT64_TYPE__ */

#ifndef __NO_FPU
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL unicode_getnumericdbl)(char32_t __ch) {
	struct __unitraits const *__traits = __unicode_descriptor(__ch);
	if __likely(__traits->__ut_digit_idx <= __UNICODE_DIGIT_IDENTITY_MAX)
		return (double)__traits->__ut_digit_idx;
#ifdef ____unicode_descriptor_digitd_defined
	return __unicode_descriptor_digitd(__traits->__ut_digit_idx);
#else /* ____unicode_descriptor_digitd_defined */
	return 0.0;
#endif /* !____unicode_descriptor_digitd_defined */
}

#ifdef __COMPILER_HAVE_LONGDOUBLE
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL unicode_getnumericldbl)(char32_t __ch) {
	struct __unitraits const *__traits = __unicode_descriptor(__ch);
	if __likely(__traits->__ut_digit_idx <= __UNICODE_DIGIT_IDENTITY_MAX)
		return (__LONGDOUBLE)__traits->__ut_digit_idx;
#ifdef ____unicode_descriptor_digitld_defined
	return __unicode_descriptor_digitld(__traits->__ut_digit_idx);
#elif defined(____unicode_descriptor_digitd_defined)
	return __unicode_descriptor_digitd(__traits->__ut_digit_idx);
#else /* ... */
	return 0.0L;
#endif /* !... */
}
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */

#else /* ____unicode_descriptor_defined */

#include <libc/ctype.h>
#define unicode_iscntrl(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_iscntrl(ch))              /* Control characters */
#define unicode_istab(ch)     ((ch) == 9 || (ch) == 0xb || (ch) == 0xc)                          /* 09, 0B-0C */
#define unicode_iswhite(ch)   ((ch) == 0x20)                                                     /* Pure whitespace characters (excluding tabs and line-feeds) */
#define unicode_isempty(ch)   (unicode_istab(ch) || unicode_iswhite(ch))                         /* unicode_istab || unicode_iswhite */
#define unicode_islf(ch)      ((ch) == 0xa || (ch) == 0xd)                                       /* Line-feed characters */
#define unicode_isspace(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isspace(ch))              /* unicode_isempty | unicode_islf */
#define unicode_islower(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_islower(ch))              /* Lowercase characters */
#define unicode_isupper(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isupper(ch))              /* Uppercase characters */
#define unicode_isalpha(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isalpha(ch))              /* Alphabetical characters */
#define unicode_isdigit(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isdigit(ch))              /* Only includes stuff like "2" */
#define unicode_ishex(ch)     ((ch) >= (0x41 && (ch) <= 0x46) || ((ch) >= 0x61 && (ch) <= 0x66)) /* 'a'-'f', 'A'-'F' */
#define unicode_isxdigit(ch)  ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isxdigit(ch))             /* unicode_isdigit || unicode_ishex */
#define unicode_isalnum(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isalnum(ch))              /* unicode_isdigit || unicode_isalpha */
#define unicode_ispunct(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_ispunct(ch))              /* Punctuation (such as '.') */
#define unicode_isgraph(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isgraph(ch))              /* Graphical characters (everything printable, excluding spaces) */
#define unicode_isprint(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isprint(ch))              /* unicode_isgraph || unicode_iswhite */
#define unicode_isblank(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isblank(ch))              /* unicode_iswhite || (ch == '\t') */
#define unicode_istitle(ch)   unicode_isupper(ch)                                                /* title-case */
#define unicode_isnumeric(ch) unicode_isdigit(ch)                                                /* Includes stuff like "²" */
#define unicode_issymstrt(ch) (unicode_isalpha(ch) || (ch) == 0x5f || (ch) == 0x24)              /* Character may appear at the start of a symbol name */
#define unicode_issymcont(ch) (unicode_isalnum(ch) || (ch) == 0x5f || (ch) == 0x24)              /* Character may appear in the middle of a symbol name */

#define unicode_tolower(ch) ((__UINT32_TYPE__)(ch) <= 0x7f ? __libc_tolower(ch) : (ch))
#define unicode_toupper(ch) ((__UINT32_TYPE__)(ch) <= 0x7f ? __libc_toupper(ch) : (ch))
#define unicode_totitle(ch) unicode_toupper(ch)

/* >> unicode_asdigit(3)
 * Check if `ch' is a digit- or hex-character (s.a. `unicode_isxdigit()'),
 * and if so, store  its digit value in  `*presult' and return `true'  iff
 * its  digit value is  less than `radix'.  Otherwise, leave `*presult' as
 * undefined and return `false'.
 * Note that `radix' values >= 16 are supported, but the cut-off  value
 * until which they are is  implementation-defined (but always >=  16).
 * If digit characters which equate to values greater than 16 should be
 * supported, then `unicode_getnumeric(64|dbl|ldbl)' should be used! */
#ifdef __INTELLISENSE__
__ATTR_WUNUSED __ATTR_NONNULL((3)) __BOOL
__NOTHROW_NCX(unicode_asdigit)(char32_t ch, __UINT8_TYPE__ radix,
                               __UINT8_TYPE__ * __restrict presult);
#else /* __INTELLISENSE__ */
#define unicode_asdigit(ch, radix, presult)                                                \
	(((ch) >= 0x30 && (ch) <= 0x39)                                                        \
	 ? ((*(presult) = (__UINT8_TYPE__)((ch)-0x30)) <= radix)                               \
	 : ((ch) >= 0x41 && (ch) <= 0x46 && (!__builtin_constant_p(radix) || (radix) >= 10))   \
	   ? ((*(presult) = (__UINT8_TYPE__)((ch)-0x37)) <= radix)                             \
	   : ((ch) >= 0x61 && (ch) <= 0x66 && (!__builtin_constant_p(radix) || (radix) >= 10)) \
	     ? ((*(presult) = (__UINT8_TYPE__)((ch)-0x57)) <= radix)                           \
	     : 0)
#endif /* !__INTELLISENSE__ */

#define __unicode_getnumeric(ch)       \
	((ch) >= 0x30 && (ch) <= 0x39     \
	 ? (ch)-0x30                      \
	 : (ch) >= 0x41 && (ch) <= 0x46   \
	   ? (ch)-0x37                    \
	   : (ch) >= 0x61 && (ch) <= 0x66 \
	     ? (ch)-0x57                  \
	     : 0)

/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define unicode_getnumeric(ch) ((__UINT8_TYPE__)__unicode_getnumeric(ch))

#ifdef __UINT64_TYPE__
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define unicode_getnumeric64(ch) ((__UINT64_TYPE__)__unicode_getnumeric(ch))
#endif /* __UINT64_TYPE__ */

#ifndef __NO_FPU
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define unicode_getnumericdbl(ch) ((double)__unicode_getnumeric(ch))

#ifdef __COMPILER_HAVE_LONGDOUBLE
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define unicode_getnumericldbl(ch) ((__LONGDOUBLE)__unicode_getnumeric(ch))
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#endif /* !____unicode_descriptor_defined */

/* Wide-character integration */
#if __SIZEOF_WCHAR_T__ == 4
#define UNICODE_8TOW_MAXBUF UNICODE_8TO32_MAXBUF
#define UNICODE_WTO8_MAXBUF UNICODE_32TO8_MAXBUF
#define unicode_len8tow     unicode_len8to32
#define unicode_wto8(utf8_dst, wchar_text, wchar_words) \
	unicode_32to8(utf8_dst, (char32_t const *)(wchar_text), wchar_words)
#define unicode_wto8_n(utf8_dst, utf8_maxbytes, wchar_text, wchar_words) \
	unicode_32to8_n(utf8_dst, utf8_maxbytes, (char32_t const *)(wchar_text), wchar_words)
#define unicode_8tow(wide_dst, utf8_text, utf8_bytes) \
	(wchar_t *)unicode_8to32((char32_t *)(wide_dst), utf8_text, utf8_bytes)
#define unicode_8tow_n(wide_dst, wide_maxwords, utf8_text, utf8_bytes) \
	(wchar_t *)unicode_8to32_n((char32_t *)(wide_dst), wide_maxwords, utf8_text, utf8_bytes)
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define UNICODE_8TOW_MAXBUF UNICODE_8TO16_MAXBUF
#define UNICODE_WTO8_MAXBUF UNICODE_16TO8_MAXBUF
#define unicode_len8tow     unicode_len8to16
#define unicode_wto8(utf8_dst, wchar_text, wchar_words) \
	unicode_16to8(utf8_dst, (char16_t const *)(wchar_text), wchar_words)
#define unicode_wto8_n(utf8_dst, utf8_maxbytes, wchar_text, wchar_words) \
	unicode_16to8_n(utf8_dst, utf8_maxbytes, (char16_t const *)(wchar_text), wchar_words)
#define unicode_8tow(wide_dst, utf8_text, utf8_bytes) \
	(wchar_t *)unicode_8to16((char16_t *)(wide_dst), utf8_text, utf8_bytes)
#define unicode_8tow_n(wide_dst, wide_maxwords, utf8_text, utf8_bytes) \
	(wchar_t *)unicode_8to16_n((char16_t *)(wide_dst), wide_maxwords, utf8_text, utf8_bytes)
#endif /* __SIZEOF_WCHAR_T__ != 4 */

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
#include <hybrid/typecore.h>
#include <bits/crt/unicode.h>

/* Unicode character traits test functions */
#ifdef ____libc___unicode_descriptor_defined
#define __libc_unicode_iscntrl(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISCNTRL) != 0)   /* Control characters */
#define __libc_unicode_istab(ch)     ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISTAB) != 0)     /* 09, 0B-0C */
#define __libc_unicode_iswhite(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISWHITE) != 0)   /* Pure whitespace characters (excluding tabs and line-feeds) */
#define __libc_unicode_isempty(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISEMPTY) != 0)   /* unicode_istab || unicode_iswhite */
#define __libc_unicode_islf(ch)      ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISLF) != 0)      /* Line-feed characters */
#define __libc_unicode_isspace(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISSPACE) != 0)   /* unicode_isempty | unicode_islf */
#define __libc_unicode_islower(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISLOWER) != 0)   /* Lowercase characters */
#define __libc_unicode_isupper(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISUPPER) != 0)   /* Uppercase characters */
#define __libc_unicode_isalpha(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISALPHA) != 0)   /* Alphabetical characters */
#define __libc_unicode_isdigit(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISDIGIT) != 0)   /* Only includes stuff like "2" */
#define __libc_unicode_ishex(ch)     ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISHEX) != 0)     /* 'a'-'f', 'A'-'F' */
#define __libc_unicode_isxdigit(ch)  ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISXDIGIT) != 0)  /* unicode_isdigit || unicode_ishex */
#define __libc_unicode_isalnum(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISALNUM) != 0)   /* unicode_isdigit || unicode_isalpha */
#define __libc_unicode_ispunct(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISPUNCT) != 0)   /* Punctuation (such as '.') */
#define __libc_unicode_isgraph(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISGRAPH) != 0)   /* Graphical characters (everything printable, excluding spaces) */
#define __libc_unicode_isprint(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISPRINT) != 0)   /* unicode_isgraph || unicode_iswhite */
#define __libc_unicode_isblank(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISBLANK) != 0)   /* unicode_iswhite || (ch == '\t') */
#define __libc_unicode_istitle(ch)   ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISTITLE) != 0)   /* title-case */
#define __libc_unicode_isnumeric(ch) ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISNUMERIC) != 0) /* Includes stuff like "²" */
#define __libc_unicode_issymstrt(ch) ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISSYMSTRT) != 0) /* Character may appear at the start of a symbol name */
#define __libc_unicode_issymcont(ch) ((__libc___unicode_descriptor(ch)->__ut_flags & __UNICODE_ISSYMCONT) != 0) /* Character may appear in the middle of a symbol name */

#define __libc_unicode_tolower(ch) ((ch) + __libc___unicode_descriptor(ch)->__ut_lower)
#define __libc_unicode_toupper(ch) ((ch) + __libc___unicode_descriptor(ch)->__ut_upper)
#define __libc_unicode_totitle(ch) ((ch) + __libc___unicode_descriptor(ch)->__ut_title)

__DECL_BEGIN

/* >> unicode_asdigit(3)
 * Check if `ch' is a digit- or hex-character (s.a. `unicode_isxdigit()'),
 * and if so, store  its digit value in  `*presult' and return `true'  iff
 * its  digit value is  less than `radix'.  Otherwise, leave `*presult' as
 * undefined and return `false'.
 * Note that `radix' values >= 16 are supported, but the cut-off  value
 * until which they are is  implementation-defined (but always >=  16).
 * If digit characters which equate to values greater than 16 should be
 * supported, then `unicode_getnumeric(64|dbl|ldbl)' should be used! */
#ifdef __INTELLISENSE__
__ATTR_WUNUSED __ATTR_OUT(3) __BOOL
__NOTHROW_NCX(__libc_unicode_asdigit)(__CHAR32_TYPE__ ch, __UINT8_TYPE__ radix,
                                      __UINT8_TYPE__ * __restrict presult);
#else /* __INTELLISENSE__ */
#define __libc_unicode_asdigit(ch, radix, presult) \
	((*(presult) = __unicode_asdigit(ch)) <= (radix))
#endif /* !__INTELLISENSE__ */

#ifndef ____unicode_asdigit_defined
#define ____unicode_asdigit_defined
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT8_TYPE__
__NOTHROW(__LIBCCALL __unicode_asdigit)(__CHAR32_TYPE__ __ch) {
	struct __unitraits const *__traits = __libc___unicode_descriptor(__ch);
	if (!(__traits->__ut_flags & __UNICODE_ISXDIGIT))
		return 0xff;
	return __traits->__ut_digit_idx;
}
#endif /* !____unicode_asdigit_defined */

/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT8_TYPE__
__NOTHROW(__LIBCCALL __libc_unicode_getnumeric)(__CHAR32_TYPE__ __ch) {
	struct __unitraits const *__traits = __libc___unicode_descriptor(__ch);
	if __likely(__traits->__ut_digit_idx <= __UNICODE_DIGIT_IDENTITY_MAX)
		return __traits->__ut_digit_idx;
#ifdef ____libc___unicode_descriptor_digit_defined
	return __libc___unicode_descriptor_digit(__traits->__ut_digit_idx);
#elif defined(____libc___unicode_descriptor_digit64_defined)
	return (__UINT8_TYPE__)__libc___unicode_descriptor_digit64(__traits->__ut_digit_idx);
#else /* ... */
	return 0;
#endif /* !... */
}

#ifdef __UINT64_TYPE__
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT64_TYPE__
__NOTHROW(__LIBCCALL __libc_unicode_getnumeric64)(__CHAR32_TYPE__ __ch) {
	struct __unitraits const *__traits = __libc___unicode_descriptor(__ch);
	if __likely(__traits->__ut_digit_idx <= __UNICODE_DIGIT_IDENTITY_MAX)
		return __traits->__ut_digit_idx;
#ifdef ____libc___unicode_descriptor_digit64_defined
	return __libc___unicode_descriptor_digit64(__traits->__ut_digit_idx);
#elif defined(____libc___unicode_descriptor_digit_defined)
	return __libc___unicode_descriptor_digit(__traits->__ut_digit_idx);
#else /* ... */
	return 0;
#endif /* !... */
}
#endif /* __UINT64_TYPE__ */

#ifndef __NO_FPU
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __libc_unicode_getnumericdbl)(__CHAR32_TYPE__ __ch) {
	struct __unitraits const *__traits = __libc___unicode_descriptor(__ch);
	if __likely(__traits->__ut_digit_idx <= __UNICODE_DIGIT_IDENTITY_MAX)
		return (double)__traits->__ut_digit_idx;
#ifdef ____libc___unicode_descriptor_digitd_defined
	return __libc___unicode_descriptor_digitd(__traits->__ut_digit_idx);
#else /* ____libc___unicode_descriptor_digitd_defined */
	return 0.0;
#endif /* !____libc___unicode_descriptor_digitd_defined */
}

#ifdef __COMPILER_HAVE_LONGDOUBLE
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __libc_unicode_getnumericldbl)(__CHAR32_TYPE__ __ch) {
	struct __unitraits const *__traits = __libc___unicode_descriptor(__ch);
	if __likely(__traits->__ut_digit_idx <= __UNICODE_DIGIT_IDENTITY_MAX)
		return (__LONGDOUBLE)__traits->__ut_digit_idx;
#ifdef ____libc___unicode_descriptor_digitld_defined
	return __libc___unicode_descriptor_digitld(__traits->__ut_digit_idx);
#elif defined(____libc___unicode_descriptor_digitd_defined)
	return __libc___unicode_descriptor_digitd(__traits->__ut_digit_idx);
#else /* ... */
	return 0.0L;
#endif /* !... */
}
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
__DECL_END

#else /* ____libc___unicode_descriptor_defined */

#include <libc/ctype.h>
#define __libc_unicode_iscntrl(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_iscntrl(ch))              /* Control characters */
#define __libc_unicode_istab(ch)     ((ch) == 9 || (ch) == 0xb || (ch) == 0xc)                          /* 09, 0B-0C */
#define __libc_unicode_iswhite(ch)   ((ch) == 0x20)                                                     /* Pure whitespace characters (excluding tabs and line-feeds) */
#define __libc_unicode_isempty(ch)   (__libc_unicode_istab(ch) || __libc_unicode_iswhite(ch))           /* unicode_istab || unicode_iswhite */
#define __libc_unicode_islf(ch)      ((ch) == 0xa || (ch) == 0xd)                                       /* Line-feed characters */
#define __libc_unicode_isspace(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isspace(ch))              /* unicode_isempty | unicode_islf */
#define __libc_unicode_islower(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_islower(ch))              /* Lowercase characters */
#define __libc_unicode_isupper(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isupper(ch))              /* Uppercase characters */
#define __libc_unicode_isalpha(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isalpha(ch))              /* Alphabetical characters */
#define __libc_unicode_isdigit(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isdigit(ch))              /* Only includes stuff like "2" */
#define __libc_unicode_ishex(ch)     ((ch) >= (0x41 && (ch) <= 0x46) || ((ch) >= 0x61 && (ch) <= 0x66)) /* 'a'-'f', 'A'-'F' */
#define __libc_unicode_isxdigit(ch)  ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isxdigit(ch))             /* unicode_isdigit || unicode_ishex */
#define __libc_unicode_isalnum(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isalnum(ch))              /* unicode_isdigit || unicode_isalpha */
#define __libc_unicode_ispunct(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_ispunct(ch))              /* Punctuation (such as '.') */
#define __libc_unicode_isgraph(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isgraph(ch))              /* Graphical characters (everything printable, excluding spaces) */
#define __libc_unicode_isprint(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isprint(ch))              /* unicode_isgraph || unicode_iswhite */
#define __libc_unicode_isblank(ch)   ((__UINT32_TYPE__)(ch) <= 0x7f && __libc_isblank(ch))              /* unicode_iswhite || (ch == '\t') */
#define __libc_unicode_istitle(ch)   __libc_unicode_isupper(ch)                                         /* title-case */
#define __libc_unicode_isnumeric(ch) __libc_unicode_isdigit(ch)                                         /* Includes stuff like "²" */
#define __libc_unicode_issymstrt(ch) (__libc_unicode_isalpha(ch) || (ch) == 0x5f || (ch) == 0x24)       /* Character may appear at the start of a symbol name */
#define __libc_unicode_issymcont(ch) (__libc_unicode_isalnum(ch) || (ch) == 0x5f || (ch) == 0x24)       /* Character may appear in the middle of a symbol name */

#define __libc_unicode_tolower(ch) ((__UINT32_TYPE__)(ch) <= 0x7f ? __libc_tolower(ch) : (ch))
#define __libc_unicode_toupper(ch) ((__UINT32_TYPE__)(ch) <= 0x7f ? __libc_toupper(ch) : (ch))
#define __libc_unicode_totitle(ch) __libc_unicode_toupper(ch)

/* >> unicode_asdigit(3)
 * Check if `ch' is a digit- or hex-character (s.a. `unicode_isxdigit()'),
 * and if so, store  its digit value in  `*presult' and return `true'  iff
 * its  digit value is  less than `radix'.  Otherwise, leave `*presult' as
 * undefined and return `false'.
 * Note that `radix' values >= 16 are supported, but the cut-off  value
 * until which they are is  implementation-defined (but always >=  16).
 * If digit characters which equate to values greater than 16 should be
 * supported, then `unicode_getnumeric(64|dbl|ldbl)' should be used! */
#ifdef __INTELLISENSE__
__ATTR_WUNUSED __ATTR_OUT(3) __BOOL
__NOTHROW_NCX(__libc_unicode_asdigit)(__CHAR32_TYPE__ ch, __UINT8_TYPE__ radix,
                                      __UINT8_TYPE__ *__restrict presult);
#else /* __INTELLISENSE__ */
#define __libc_unicode_asdigit(ch, radix, presult)                                         \
	(((ch) >= 0x30 && (ch) <= 0x39)                                                        \
	 ? ((*(presult) = (__UINT8_TYPE__)((ch)-0x30)) <= radix)                               \
	 : ((ch) >= 0x41 && (ch) <= 0x46 && (!__builtin_constant_p(radix) || (radix) >= 10))   \
	   ? ((*(presult) = (__UINT8_TYPE__)((ch)-0x37)) <= radix)                             \
	   : ((ch) >= 0x61 && (ch) <= 0x66 && (!__builtin_constant_p(radix) || (radix) >= 10)) \
	     ? ((*(presult) = (__UINT8_TYPE__)((ch)-0x57)) <= radix)                           \
	     : 0)
#endif /* !__INTELLISENSE__ */

#define ____libc_unicode_getnumeric(ch) \
	((ch) >= 0x30 && (ch) <= 0x39       \
	 ? (ch)-0x30                        \
	 : (ch) >= 0x41 && (ch) <= 0x46     \
	   ? (ch)-0x37                      \
	   : (ch) >= 0x61 && (ch) <= 0x66   \
	     ? (ch)-0x57                    \
	     : 0)

/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define __libc_unicode_getnumeric(ch) ((__UINT8_TYPE__)____libc_unicode_getnumeric(ch))

#ifdef __UINT64_TYPE__
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define __libc_unicode_getnumeric64(ch) ((__UINT64_TYPE__)____libc_unicode_getnumeric(ch))
#endif /* __UINT64_TYPE__ */

#ifndef __NO_FPU
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define __libc_unicode_getnumericdbl(ch) ((double)____libc_unicode_getnumeric(ch))

#ifdef __COMPILER_HAVE_LONGDOUBLE
/* >> unicode_getnumeric(3), unicode_getnumeric64(3), unicode_getnumericdbl(3), unicode_getnumericldbl(3)
 * Return  the numerical  variable for which  `ch' is representative  (s.a. `unicode_isnumeric(3)'). When
 * `ch' doesn't represent  a numerical character,  return `0'.  Note that this  function also  recognizes
 * 'a'-'f' and 'A'-'F' as numeric characters (representing their hex values) */
#define __libc_unicode_getnumericldbl(ch) ((__LONGDOUBLE)____libc_unicode_getnumeric(ch))
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#endif /* !____libc___unicode_descriptor_defined */

}
