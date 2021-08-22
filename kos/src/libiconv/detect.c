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
#ifndef GUARD_LIBICONV_DETECT_C
#define GUARD_LIBICONV_DETECT_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <kos/types.h>
#include <sys/param.h>

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <syslog.h>
#include <unicode.h>

#include <libiconv/codec.h>
#include <libiconv/iconv.h>

#include "codecs.h"
#include "cp-7h.h"
#include "cp-7l.h"
#include "cp-iso646.h"
#include "cp.h"
#include "detect.h"
#include "iconv.h"

DECL_BEGIN

/* Max # of characters to check before believing that a "hunch" is correct. */
#ifndef HUNCH_CHECK_MAXCHARS
#define HUNCH_CHECK_MAXCHARS 16384
#endif /* !HUNCH_CHECK_MAXCHARS */

/* Only search the first MARKER_CHECK_MAXCHARS bytes for human-readable codec markers. */
#ifndef MARKER_CHECK_MAXCHARS
#define MARKER_CHECK_MAXCHARS 2048
#endif /* !MARKER_CHECK_MAXCHARS */


/* Check if `ch' is allowed to appear within "text" */
PRIVATE ATTR_CONST WUNUSED bool
NOTHROW(CC istxtchar)(char32_t ch) {
	uint16_t flags = __unicode_flags(ch);
	if (flags & (__UNICODE_FPRINT | __UNICODE_FALPHA | __UNICODE_FSPACE |
	             __UNICODE_FLF | __UNICODE_FLOWER | __UNICODE_FUPPER |
	             __UNICODE_FTITLE | __UNICODE_FDIGIT | __UNICODE_FDECIMAL |
	             __UNICODE_FSYMSTRT | __UNICODE_FSYMCONT)) {
		assert(ch != 0); /* Just for safety... */
		return true;
	}
	if (ch < 0x20) {
		/* Whitelist of text characters within the C1 area */
		static char const c1_printable[] = {
			0x09, /* TAB */
			0x0a, /* LF */
			0x0c, /* FF */
			0x0d, /* CR */
			0x1b, /* ESC (for the purpose of console escape codes) */
		};
		return memchr(c1_printable, (uint8_t)ch, sizeof(c1_printable)) != NULL;
	}
	/* Generic case: not a text character! */
	return false;
}


PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC hunch_check_utf32)(void const *__restrict data, size_t size, bool be) {
	if ((size & 3) != 0)
		goto nope; /* UTF-32 requires that the file size be a multiple of 4 */
	if (size > HUNCH_CHECK_MAXCHARS * 4)
		size = HUNCH_CHECK_MAXCHARS * 4;
	while (size) {
		char32_t ch;
		ch = be ? (char32_t)UNALIGNED_GETBE32((uint32_t const *)data)
		        : (char32_t)UNALIGNED_GETLE32((uint32_t const *)data);
		if (!istxtchar(ch))
			goto nope;
		data = (byte_t const *)data + 4;
		size -= 4;
	}
	return true;
nope:
	return false;
}


PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC hunch_check_utf16)(void const *__restrict data, size_t size, bool be) {
	size_t num_chars;
	if ((size & 1) != 0)
		goto nope; /* UTF-16 requires that the file size be a multiple of 2 */
	num_chars = HUNCH_CHECK_MAXCHARS;
	while (size && num_chars) {
		char16_t ch16;
		ch16 = be ? (char16_t)UNALIGNED_GETBE16((uint16_t const *)data)
		          : (char16_t)UNALIGNED_GETLE16((uint16_t const *)data);
		if (ch16 >= UTF16_LOW_SURROGATE_MIN && ch16 <= UTF16_LOW_SURROGATE_MAX)
			goto nope; /* Unmatched low surrogate (wrong!) */
		if (ch16 >= UTF16_HIGH_SURROGATE_MIN && ch16 <= UTF16_HIGH_SURROGATE_MAX) {
			char32_t ch32;
			char16_t ch16_2;
			/* Surrogate pair! */
			data = (byte_t const *)data + 2;
			size -= 2;
			if (!size)
				goto nope;
			ch16_2 = be ? (char16_t)UNALIGNED_GETBE16((uint16_t const *)data)
			            : (char16_t)UNALIGNED_GETLE16((uint16_t const *)data);
			if (!(ch16_2 >= UTF16_LOW_SURROGATE_MIN && ch16_2 <= UTF16_LOW_SURROGATE_MAX))
				goto nope;
			ch32 = ch16 - UTF16_HIGH_SURROGATE_MIN;
			ch32 <<= 10;
			ch32 += UTF16_SURROGATE_SHIFT - UTF16_LOW_SURROGATE_MIN;
			ch32 += ch16_2;
			if (!istxtchar(ch32))
				goto nope;
		} else {
			if (!istxtchar(ch16))
				goto nope;
		}
		--num_chars;
		data = (byte_t const *)data + 2;
		size -= 2;
	}
	return true;
nope:
	return false;
}





/* This heuristic was generated by counting byte occurrences within text files
 * found throughout the  KOS source tree,  as well as  inside of some  english
 * literature I've had laying around. It should be a fairly good approximation
 * of what should be "normal" english text.
 * Of course, trying to automatically detect the codec of non-english text that
 * has been encoded in an ascii-incompatible character set will still fail  and
 * may  not actually figure out what's going on, but this should be pretty much
 * perfect for any english codec applied to english text! */
#define ASCII_HEURISTIC_TOTAL 0x52ab284 /* Sum of all values from `ascii_heuristic' */
PRIVATE uint32_t const ascii_heuristic[128] = {
	0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
	0x000000, 0x0df50b, 0x1bf22c, 0x000000, 0x000018, 0x000533, 0x000000, 0x000000,
	0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
	0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
	0xfb5183, 0x016a96, 0x0232c1, 0x06fc56, 0x00703a, 0x007941, 0x026407, 0x02aed0,
	0x0e594c, 0x0e5b97, 0x163dbc, 0x00b20f, 0x0f6551, 0x0377f5, 0x070ad2, 0x0a73dd,
	0x09f063, 0x053a03, 0x04f8a6, 0x033662, 0x02e782, 0x012b88, 0x038278, 0x00cc59,
	0x0223b1, 0x00e81f, 0x033f3b, 0x05c010, 0x0195e5, 0x037987, 0x030e57, 0x0051d6,
	0x017ac5, 0x0e1341, 0x03a89e, 0x0d3ab1, 0x06aa71, 0x131c27, 0x05493a, 0x038f9c,
	0x04b344, 0x0c39eb, 0x001d47, 0x01dcdf, 0x0c00f3, 0x05206c, 0x0cd5ac, 0x0af5e3,
	0x06d758, 0x003639, 0x0dd496, 0x0a9eb8, 0x1121b5, 0x05ab3a, 0x0312b2, 0x02c7c5,
	0x02d527, 0x023a1a, 0x00ce85, 0x019f7f, 0x00c413, 0x019be5, 0x0003c5, 0x5063c8,
	0x01c6de, 0x22d257, 0x0980c8, 0x196e22, 0x1e1a5c, 0x4b4a66, 0x17ef4b, 0x09bbe6,
	0x0ebe51, 0x2b98c2, 0x007fb1, 0x04975d, 0x1ad066, 0x0e87a4, 0x298364, 0x22910e,
	0x1058e9, 0x00fe4a, 0x2864a1, 0x24e573, 0x36658e, 0x12a203, 0x05b098, 0x06b235,
	0x08185e, 0x081274, 0x018ee6, 0x023433, 0x01a487, 0x023428, 0x0010dd, 0x000000,
};

/* Check if the given heuristic is ASCII-compatible. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(CC is_ascii_heuristic)(uint16_t const heuristic[128]) {
	unsigned int i;
	/* ASCII character indices that cannot appear in text. */
	static uint8_t const nontext_ascii[] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
		0x07, 0x08, 0x0b, 0x0e, 0x0f, 0x7f
	};
	for (i = 0; i < COMPILER_LENOF(nontext_ascii); ++i) {
		if (heuristic[nontext_ascii[i]] != 0) {
			/* If the heuristic were ASCII, it'd contain
			 * characters that  can't  appear  in  text! */
			return false;
		}
	}
	return true;
}



/* Calculate the "fuzzyness" of how close the given heuristic (if decoded using `decode')
 * would  be to the  known `ascii_heuristic' for "normal text".  When it's clear that the
 * given `cp' can't be used at all, return `(size_t)-1'.
 * When `cp' is `NULL', don't decode and check for the ASCII codepage. */
PRIVATE ATTR_PURE NONNULL((2)) size_t
NOTHROW_NCX(CC calculate_ascii_fuzzyness)(char16_t const decode[/*decode_count*/],
                                          uint16_t const byte_heuristic[128],
                                          uint32_t byte_heuristic_sum,
                                          size_t decode_count, bool is_iso646) {
	uint32_t cp_heuristic_sum;
	uint32_t cp_heuristic[128];
	size_t i;
	/* Step #1: Check  that  all  bytes  that  _did_  appear can
	 *          actually appear in text when encoded using `cp'. */
	memset(cp_heuristic, 0, sizeof(cp_heuristic));
	cp_heuristic_sum = 0;
	for (i = 0; i < decode_count; ++i) {
		char16_t encoded;
		if (byte_heuristic[i] == 0)
			continue; /* Byte never appeared! */
		if (decode == NULL) {
			encoded = (char16_t)i;
		} else if (is_iso646) {
			uint8_t index = libiconv_iso646_override[i];
			encoded = (char16_t)i;
			if (index < ISO646_OVERRIDE_COUNT)
				encoded = decode[index];
		} else {
			encoded = decode[i];
		}
		if (!istxtchar(encoded))
			goto nope; /* There are bytes that (when decoded) cannot appear in text. */
		/* If it fits, copy over heuristic bytes. */
		if (encoded <= 0x7f) {
			cp_heuristic[(uint8_t)encoded] = byte_heuristic[i];
			cp_heuristic_sum += byte_heuristic[i];
		}
	}
	if ((cp_heuristic_sum * 4) <= (byte_heuristic_sum * 3)) {
		goto nope; /* Too many characters (once decoded) fall out-of-line.
		            * Iow: this probably isn't the right codec! */
	}
	assertf(cp_heuristic_sum != 0, "Guarantied by the <= in the previous compare!");

	/* Up-scale (presumably ascii-like) heuristic values to match those from the baseline. */
	for (i = 0; i < 128; ++i) {
		uint64_t temp;
		STATIC_ASSERT(((uint64_t)0xffff * (uint64_t)ASCII_HEURISTIC_TOTAL) > (uint64_t)0xffff);
		STATIC_ASSERT(((uint64_t)0xffff * (uint64_t)ASCII_HEURISTIC_TOTAL) > (uint64_t)ASCII_HEURISTIC_TOTAL);
		/* This multiply can't possibly overflow, which is guarantied by the STATIC_ASSERT
		 * which  ensures that the max possible input values that can appear at this point
		 * don't overflow when multiplied with each other. */
		temp = (uint64_t)cp_heuristic[i] * (uint64_t)ASCII_HEURISTIC_TOTAL;
		temp /= cp_heuristic_sum;
		cp_heuristic[i] = temp;
	}

	/* Fuzzy compare the codepage-based heuristic with the baseline.  */
	return fuzzy_memcmpl(cp_heuristic, 128, ascii_heuristic, 128);
nope:
	return (size_t)-1;
}


PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC hunch_check_utf8)(void const *__restrict data, size_t size) {
	size_t num_chars;
	num_chars = HUNCH_CHECK_MAXCHARS;
	while (size && num_chars) {
		uint8_t ch, seqlen;
		ch     = *(uint8_t const *)data;
		seqlen = unicode_utf8seqlen[ch];
		if (seqlen != 1) {
			uint8_t i, seq[8];
			char *ptr;
			char32_t ch32;
			if (seqlen == 0)
				goto nope; /* Illegal start to UTF-8 sequence. */
			if (seqlen > size)
				goto nope; /* This would result in an incomplete sequence. */
			/* Load the sequence. */
			seq[0] = ch;
			memcpy(seq + 1, (uint8_t const *)data + 1, seqlen - 1);
			for (i = 1; i < seqlen; ++i) {
				if ((seq[i] & 0xc0) != 0x80)
					goto nope; /* Invalid utf-8 multi-byte sequence follow-up byte! */
			}
			ptr  = (char *)seq;
			ch32 = unicode_readutf8(&ptr);
			assert(ptr == (char *)seq + seqlen);

			/* Check if the decoded character can appear in text. */
			if (!istxtchar(ch32))
				goto nope;

			/* Advance to skip this character. */
			data = (uint8_t const *)data + seqlen;
			size -= seqlen;
			--num_chars;
		} else {
			/* Make sure it's a valid text character. */
			if (!istxtchar(ch))
				goto nope;
			data = (uint8_t const *)data + 1;
			--size;
			--num_chars;
		}
	}
	return true;
nope:
	return false;
}



/* Helpers for working with a bitset of cp7h codecs. */
typedef uintptr_t cp7h_bitset_t[CEILDIV(CODEC_CP7H_COUNT, sizeof(uintptr_t) * NBBY)];
#define _cp7h_bitset_index(codec) (((codec) - CODEC_CP7H_MIN) / (sizeof(uintptr_t) * NBBY))
#define _cp7h_bitset_shift(codec) (((codec) - CODEC_CP7H_MIN) % (sizeof(uintptr_t) * NBBY))
#define _cp7h_bitset_mask(codec)  ((uintptr_t)1 << _cp7h_bitset_index(codec))
#define cp7h_bitset_insert(self, codec)   ((self)[_cp7h_bitset_index(codec)] |= _cp7h_bitset_mask(codec))
#define cp7h_bitset_contains(self, codec) ((self)[_cp7h_bitset_index(codec)] & _cp7h_bitset_mask(codec))
#define cp7h_bitset_clear(self)           memset(self, 0, sizeof(cp7h_bitset_t))



typedef uintptr_t cp8_bitset_t[CEILDIV(CODEC_CP_COUNT, sizeof(uintptr_t) * NBBY)];
#define _cp8_bitset_index(codec) (((codec) - CODEC_CP_MIN) / (sizeof(uintptr_t) * NBBY))
#define _cp8_bitset_shift(codec) (((codec) - CODEC_CP_MIN) % (sizeof(uintptr_t) * NBBY))
#define _cp8_bitset_mask(codec)  ((uintptr_t)1 << _cp8_bitset_index(codec))
#define cp8_bitset_insert(self, codec)   ((self)[_cp8_bitset_index(codec)] |= _cp8_bitset_mask(codec))
#define cp8_bitset_contains(self, codec) ((self)[_cp8_bitset_index(codec)] & _cp8_bitset_mask(codec))
#define cp8_bitset_clear(self)           memset(self, 0, sizeof(cp8_bitset_t))



/* Scan `data' for something  resembling an explicit codec  marker,
 * but stop after a while or when hitting a non-ascii (or non-text)
 * character.
 *
 * Detected patterns (documented here using regex):
 *    - Comments:
 *         / *[ \t*#@+!$/]*(charset|coding|codec)[\t =:]+CODEC[ \t*#@+!$/]** /
 *         ( *[ \t*#@+!$/]*(charset|coding|codec)[\t =:]+CODEC[ \t*#@+!$/]** )
 *         [#@+!$][ \t*#@+!$/]*(charset|coding|codec)[\t =:]+CODEC\n
 *
 *    - Free-standing:
 *         (charset|coding|codec)[\t =:]*("CODEC"|'CODEC')
 *
 * @return: * :                The determined codec.
 * @return: CODEC_UNKNOWN:     Marker references an unknown codec.
 * @return: (iconv_codec_t)-1: No marker found. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) iconv_codec_t
NOTHROW(CC search_for_ascii_codec_marker)(unsigned char const *__restrict data, size_t size) {
	unsigned char const *codec_start;
	unsigned char const *codec_end;
	unsigned char const *end;
	if (size > MARKER_CHECK_MAXCHARS)
		size = MARKER_CHECK_MAXCHARS;
	end = data + size;
	for (;;) {
		unsigned char ch;
#define nextch()                                        \
		do {                                            \
			if (data >= end)                            \
				goto stop; /* Can't read any more */    \
			ch = *data++;                               \
			if (ch >= 0x80 || ascii_heuristic[ch] == 0) \
				goto stop; /* Not allowed! */           \
		}	__WHILE0

		nextch();
main_switch:
		switch (ch) {

		case 'c':
			if ((size_t)(end - data) >= 7) {
				if (memcasecmp(data, "harset", 6 * sizeof(char)) == 0) {
					data += 6;
check_free_standing_charset:
					do {
						nextch();
					} while (ch == ' ' || ch == '\t' ||
					         ch == ':' || ch == '=');
					if (ch == '\"' || ch == '\'') {
						/* Search until the matching quote. */
						unsigned char endquote = ch;
						codec_start = data;
						do {
							nextch();
							if (ch == '\n' || ch == '\r')
								goto main_switch;
						} while (ch != endquote);
						codec_end = data - 1;
						goto search_for_codec;
					}
				} else if (memcasecmp(data, "oding", 5 * sizeof(char)) == 0) {
					data += 5;
					goto check_free_standing_charset;
				} else if (memcasecmp(data, "odec", 4 * sizeof(char)) == 0) {
					data += 4;
					goto check_free_standing_charset;
				}
			}
			break;


		case '/': {
			unsigned int comment_style;
#define COMMENT_STYLE_LINE   0
#define COMMENT_STYLE_C      1
#define COMMENT_STYLE_PASCAL 2
			nextch();
			if (ch == '*') {
				comment_style = COMMENT_STYLE_C;
				goto comment_check;
			}
			comment_style = COMMENT_STYLE_LINE;
			goto comment_check_with_first_ch;

		case '(':
			nextch();
			if (ch == '*') {
				comment_style = COMMENT_STYLE_PASCAL;
				goto comment_check;
			}
			break;

		case '#':
		case '@':
		case '+':
		case '!':
		case '$':
			comment_style = COMMENT_STYLE_LINE;
comment_check:
#define is_comment_space_char(ch)                  \
	((ch) == ' ' || (ch) == '\t' || (ch) == '*' || \
	 (ch) == '#' || (ch) == '@' || (ch) == '+' ||  \
	 (ch) == '!' || (ch) == '$' || (ch) == '/')
			do {
				nextch();
comment_check_with_first_ch:
				;
				/* Skip characters which may indicate comments, as well
				 * as  whitespace  that  isn't  related  to  new-lines. */
			} while (is_comment_space_char(ch));

			if ((ch == 'c' || ch == 'C') && (size_t)(end - data) >= 7) {
				if (memcasecmp(data, "odec", 4 * sizeof(char)) == 0) {
					data += 4;
comment_after_coding_prefix:
					nextch();
					if (!(ch == ' ' || ch == '\t' ||
					      ch == ':' || ch == '='))
						goto main_switch;
					do {
						nextch();
					} while (ch == ' ' || ch == '\t' ||
					         ch == ':' || ch == '='); /* Allow a ':' or '=' after the coding */

					codec_start = data - 1;
					/* Load the rest of the line. */
					switch (comment_style) {

					case COMMENT_STYLE_C:
						for (;;) {
							nextch();
							if (ch != '*')
								continue;
							nextch();
							if (ch != '/')
								continue;
							break;
						}
						codec_end = data - 2;
trim_trailing_comment_space:
						/* Trim trailing comment space characters. */
						while (codec_end > codec_start) {
							ch = codec_end[-1];
							if (!is_comment_space_char(ch))
								break;
							--codec_end;
						}
						break;

					case COMMENT_STYLE_PASCAL:
						for (;;) {
							nextch();
							if (ch != '*')
								continue;
							nextch();
							if (ch != ')')
								continue;
							break;
						}
						codec_end = data - 2;
						goto trim_trailing_comment_space;

					default:
						do {
							nextch();
						} while (ch != '\r' && ch != '\n');
						codec_end = data - 1;
						break;
					}
					goto search_for_codec;
				} else if (memcasecmp(data, "oding", 5 * sizeof(char)) == 0) {
					data += 5;
					goto comment_after_coding_prefix;
				} else if (memcasecmp(data, "harset", 6 * sizeof(char)) == 0) {
					data += 6;
					goto comment_after_coding_prefix;
				}
			}
		}	break;

		default:
			break;
		}
#undef nextch
	}
stop:
	return (iconv_codec_t)-1;
search_for_codec:
	return libiconv_codecbynamez((char const *)codec_start,
	                             (size_t)(codec_end - codec_start));
}





/* Try to automatically detect the codec of the given data-blob, which  should
 * represent the memory-mapping of a text-file. This function will then try to
 * inspect its beginning for comment-style indicators which might inform about
 * which  codec the file uses (e.g. xml, python, etc.), as well as analysis of
 * NUL-bytes for multi-byte codecs.
 *
 * In case of a single-byte codec, go through all bytes that appear in the file
 * and count which of them occur how often before narrowing down candidates  by
 * excluding any where decoding would result in non-printable characters  other
 * than those needed for text (e.g. line-feeds, spaces, and unicode prefixes).
 *
 * Once the set of codecs capable of decoding the file into something that looks
 * like text is determined, use each of them to try and decode the text to UTF-8
 * and count how often each bytes occurs within the UTF-8 stream. The results of
 * this are then fuzzy-compared against a known-good heuristic of byte usage  in
 * normal text, and the codec which is closest to this heuristic is used.
 *
 * If the function is unable to determine the codec to-be used, it will return
 * with `ICONV_CODEC_UNKNOWN'. */
INTERN ATTR_PURE WUNUSED NONNULL((1)) iconv_codec_t
NOTHROW_NCX(CC libiconv_detect_codec)(void const *__restrict data, size_t size) {
#if !defined(NDEBUG) && 0
#define HAVE_LOGGING
#define goto_unknown                                                        \
	do {                                                                    \
		syslog(LOG_DEBUG, "%s(%d) : 'goto unknown'\n", __FILE__, __LINE__); \
		goto unknown;                                                       \
	}	__WHILE0
#else /* ... */
#define goto_unknown goto unknown
#endif /* !... */

	/* Special case: when there is no input data, we can't possible know what's going on! */
	if unlikely(!size)
		goto_unknown;

	/* Check for multi-byte codecs. */
	if (size >= 4) {
		union {
			uint8_t bytes[4];
			uint32_t word;
		} hdr;
		hdr.word = UNALIGNED_GET32((uint32_t const *)data);
		/* Check for supported multi-byte encodings. */
		if (hdr.bytes[0] == 0) {
			if (hdr.bytes[1] == 0) {
				if (hunch_check_utf32(data, size, true))
					return CODEC_UTF32BE;
			} else {
				if (hunch_check_utf16(data, size, true))
					return CODEC_UTF16BE;
			}
		}
		if (hdr.bytes[1] == 0) {
			if (hdr.bytes[2] == 0) {
				if (hunch_check_utf32(data, size, false))
					return CODEC_UTF32LE;
			} else {
				if (hunch_check_utf16(data, size, false))
					return CODEC_UTF16LE;
			}
		}
		if (hdr.bytes[0] == 0xef && hdr.bytes[1] == 0xbb && hdr.bytes[2] == 0xbf)
			return CODEC_UTF8_BOM; /* Special UTF-8 BOM marker. */
		if (hdr.bytes[0] == 0 || hdr.bytes[1] == 0 ||
		    hdr.bytes[2] == 0 || hdr.bytes[3] == 0) {
			/* There's a NUL in the header, but we still haven't figured out what
			 * kind of multi-byte codec is being used. As such, try all which  we
			 * know of again and if we still  fail, there's nothing we can do  to
			 * figure out the answer. */
			if (hunch_check_utf32(data, size, true))
				return CODEC_UTF32BE;
			if (hunch_check_utf32(data, size, false))
				return CODEC_UTF32LE;
			if (hunch_check_utf16(data, size, true))
				return CODEC_UTF16BE;
			if (hunch_check_utf16(data, size, false))
				return CODEC_UTF16LE;
			goto_unknown;
		}
	}
	/* With that,  all multi-byte  encodings are  out of  the  way.
	 * Time to get to the meat and scan the actual file's contents. */

	/* Check for user-defined codec markers. Only search for these within
	 * the  first `HUNCH_CHECK_MAXCHARS'  bytes of  the file,  but stop a
	 * character is found that may not appear in ASCII text. */
	{
		iconv_codec_t result;
		result = search_for_ascii_codec_marker((unsigned char const *)data, size);
		if (result != (iconv_codec_t)-1)
			return result;
	}


	/* Do heuristic-based codec detection. */
	{
		uint16_t heuristic[256];
		uint32_t heuristic_sum;

		/* Generate the heuristic. */
		{
			size_t i, h_size = size;
			if (h_size > HUNCH_CHECK_MAXCHARS)
				h_size = HUNCH_CHECK_MAXCHARS;
			memset(heuristic, 0, sizeof(heuristic));
			for (i = 0; i < h_size; ++i) {
				byte_t b = ((byte_t const *)data)[i];
				++heuristic[b];
			}
		}

		/* Check if input data contained only 7-bit characters. If so,
		 * we need  to check  against cp7l  codecs (including  ASCII). */
		{
			size_t i;
			for (i = 128; i < 256; ++i) {
				if (heuristic[i] != 0)
					goto is_8bit_codec;
			}
		}

		/* Sum up heuristic values in the low 128 bits. */
		{
			size_t i;
			for (heuristic_sum = 0, i = 0; i < 128; ++i)
				heuristic_sum += heuristic[i];
		}

		/* Go through all 7l codecs and check with one has the best "fuzzyness" */
		{
			iconv_codec_t codec;
			iconv_codec_t best_codec = CODEC_UNKNOWN;
			size_t fuzzy, best_fuzzyness = (size_t)-1;

			/* Check cp7l pages. */
			for (codec = CODEC_CP7L_MIN; codec <= CODEC_CP7L_MAX; ++codec) {
				struct iconv_7l_codepage const *cp;
				cp    = libiconv_cp7l_page(codec);
				fuzzy = calculate_ascii_fuzzyness(cp->i7lcp_decode, heuristic,
				                                  heuristic_sum, 128, false);
				if (best_fuzzyness > fuzzy) {
					best_fuzzyness = fuzzy;
					best_codec = codec;
				}
			}

			/* Check iso646 code pages! (because they're a sub-set of cp7l pages) */
			for (codec = CODEC_ISO646_MIN; codec <= CODEC_ISO646_MAX; ++codec) {
				struct iconv_iso646_codepage const *cp;
				cp    = libiconv_iso646_page(codec);
				fuzzy = calculate_ascii_fuzzyness(cp->iic_override, heuristic,
				                                  heuristic_sum, 128, true);
				if (best_fuzzyness > fuzzy) {
					best_fuzzyness = fuzzy;
					best_codec = codec;
				}
			}

			/* Also check how  "fuzzy" pure ASCII  is, but if  it's the best,  then
			 * actually tell the caller that input is UTF-8 for 3 reasons. Firstly,
			 * the part of the file which we tested might just have happened to not
			 * contain any UTF-8  characters, and  there might be  more later,  and
			 * secondly, UTF-8 is compatible with  ASCII, and thirdly, KOS is  much
			 * faster in processing UTF-8 because that's the OS's native codec! */
			fuzzy = calculate_ascii_fuzzyness(NULL, heuristic, heuristic_sum, 128, false);
			if (best_fuzzyness >= fuzzy && fuzzy != (size_t)-1) { /* >= because we really like ASCII/UTF-8 :) */
				best_fuzzyness = fuzzy;
				best_codec = CODEC_UTF8;
			}

			/* If we figured out a good cp7l codec,  then
			 * go ahead and tell our caller all about it! */
			if (best_codec != CODEC_UNKNOWN)
				return best_codec;
		}

		/* Unknown 7-bit codec. */
		goto_unknown;
is_8bit_codec:

		/* This is where it gets a bit more complicated. Firstly, we want to figure
		 * out  if this might actually be UTF-8. If it is, then we can already tell
		 * by which bytes never appear in the heuristic:
		 *  - Within 00h-7Fh: The same bytes which are also 0 in `ascii_heuristic'
		 * If  this is the case, then try to go through input data a second time and
		 * see if we're able to decode the part we're interested in as UTF-8. If so,
		 * then we're (probably) correct in assuming that it's all UTF-8! */
		if (is_ascii_heuristic(heuristic)) {

			/* Check for utf-8 */
			if (hunch_check_utf8(data, size))
				return CODEC_UTF8;

			/* Because the low 128 entries in the heuristic seem to be ASCII-compatible,
			 * we  can now check if one of our known cp7h codecs might be used to decode
			 * input data (since all of those codecs use ASCII as a basis)
			 *
			 * As such, piece together the set of  codecs that (if used) will decode  the
			 * entire heuristic to text characters. If this set consists of only 1 codec,
			 * then  that's the one we return. If there  is more than one codec, check if
			 * the available codecs would all produce the same results if applied to  the
			 * heuristic (i.e. do they differ for any of the non-empty bytes). If they're
			 * all the same, then pick and return one at random.
			 *
			 * If all of this fails, indicate to the caller that the codec is unknown. */
			{
				iconv_codec_t cd;
				cp7h_bitset_t codecs;
				size_t candidates = 0;
				bool is_latin1_candidate = false;
				cp7h_bitset_clear(codecs);

				/* Check latin1 (special case because that codec doesn't have a code page object) */
				{
					size_t i;
					for (i = 128; i < 256; ++i) {
						if (heuristic[i] != 0 && !istxtchar(i))
							goto latin1_doesnt_work; /* latin1 would decode to non-text characters. */
					}
					is_latin1_candidate = true;
					++candidates;
				}
latin1_doesnt_work:
				for (cd = CODEC_CP7H_MIN; cd <= CODEC_CP7H_MAX; ++cd) {
					size_t i;
					struct iconv_7h_codepage const *cp;
					cp = libiconv_cp7h_page(cd);
					for (i = 128; i < 256; ++i) {
						char16_t cp_ch;
						if (heuristic[i] == 0)
							continue;
						cp_ch = cp->i7hcp_decode[i - 128];
						if (!istxtchar(cp_ch))
							goto next_cp7h_codec; /* This codepage would decode to non-text characters. */
					}
					cp7h_bitset_insert(codecs, cd);
					++candidates;
next_cp7h_codec:
					;
				}

				/* Check if we've had at least 1 candidate. */
				if (candidates > 0) {
					struct iconv_7h_codepage const *frst_cp = NULL;
					iconv_codec_t frst_codec = CODEC_UNKNOWN;
					for (cd = CODEC_CP7H_MIN;; ++cd) {
						size_t i;
						struct iconv_7h_codepage const *this_cp;
						assert(cd <= CODEC_CP7H_MAX);
						if (!cp7h_bitset_contains(codecs, cd))
							continue;
						this_cp = libiconv_cp7h_page(cd);
						if (!frst_cp) {
							if (candidates == 1)
								return cd;
							frst_cp = this_cp;
							frst_codec = cd;
							continue;
						}
						/* Check if `first_cp' and `this_cp' decode to all the
						 * same characters for  all non-zero heuristic  bytes. */
						for (i = 128; i < 256; ++i) {
							char16_t frst_c16;
							char16_t this_c16;
							if (heuristic[i] == 0)
								continue; /* Ignore this byte. */
							frst_c16 = frst_cp->i7hcp_decode[i - 128];
							this_c16 = this_cp->i7hcp_decode[i - 128];
							/* If the 2 pages encode different characters, then we have
							 * no way  of telling  which codec  isn't supposed  to  be. */
							if (frst_c16 != this_c16)
								goto_unknown;
						}
					}
					if (is_latin1_candidate) {
						if (frst_cp) {
							size_t i;
							/* Check if `first_cp' is latin1 compatible. */
							for (i = 128; i < 256; ++i) {
								if (heuristic[i] != 0 && frst_cp->i7hcp_decode[i - 128] != (char16_t)i)
									goto_unknown;
							}
						}
						return CODEC_ISO_8859_1;
					}
					return frst_codec;
				} /* if (candidates > 0) */
			}     /* Scope... */
		}         /* if (is_ascii_heuristic(heuristic)) */

		/* Go over all 8-bit code pages and compare generated ASCII heuristics
		 * against  the base-line heuristic. All code pages that have the same
		 * fuzzyness are put in a set and  one is selected via the same  rules
		 * as also used for selecting cp7h pages. */
		{
			iconv_codec_t cd;
			cp8_bitset_t best_codecs;
			size_t best_codecs_count = 0;
			size_t fuzzy, best_fuzzyness = (size_t)-1;
			cp8_bitset_clear(best_codecs);

			/* Calculate the sum of the entire heuristic. */
			{
				size_t i;
				for (heuristic_sum = 0, i = 0; i < 256; ++i)
					heuristic_sum += heuristic[i];
			}

			/* Go over all codecs. */
			for (cd = CODEC_CP_MIN; cd <= CODEC_CP_MAX; ++cd) {
				size_t i;
				struct iconv_codepage const *cp;
				cp = libiconv_cp_page(cd);

				/* Check that all non-ascii bytes (that appear) decode to text characters. */
				for (i = 128; i < 256; ++i) {
					char16_t cp_ch;
					if (heuristic[i] == 0)
						continue; /* Doesn't appear; doesn't matter. */
					cp_ch = cp->icp_decode[i];
					if (!istxtchar(cp_ch))
						goto next_cp8_codec;
				}

				/* Check how fuzzy the decode-to-ascii part is */
				fuzzy = calculate_ascii_fuzzyness(cp->icp_decode, heuristic,
				                                  heuristic_sum, 256, false);
				if (fuzzy <= best_fuzzyness && fuzzy != (size_t)-1) {
					/* Better, or as good as the current best candidate(s). */
					if (fuzzy < best_fuzzyness) {
						/* New best (clear all previous candidates) */
						best_codecs_count = 0;
						best_fuzzyness = fuzzy;
						cp8_bitset_clear(best_codecs);
					} else {
						/* As good as the other candidates. - Just add to the set. */
					}
					cp8_bitset_insert(best_codecs, cd);
					++best_codecs_count;
				}
next_cp8_codec:
				;
			}

			/* Check if we've found some candidates. */
			if (best_codecs_count > 0) {
				struct iconv_codepage const *frst_cp = NULL;
				iconv_codec_t frst_codec = CODEC_UNKNOWN;
				for (cd = CODEC_CP_MIN;; ++cd) {
					size_t i;
					struct iconv_codepage const *this_cp;
					assert(cd <= CODEC_CP7H_MAX);
					if (!cp8_bitset_contains(best_codecs, cd))
						continue;
					this_cp = libiconv_cp_page(cd);
					if (!frst_cp) {
						if (best_codecs_count == 1)
							return cd;
						frst_cp = this_cp;
						frst_codec = cd;
						continue;
					}
					/* Check if `first_cp' and `this_cp' decode to all the
					 * same characters for  all non-zero heuristic  bytes. */
					for (i = 0; i < 256; ++i) {
						char16_t frst_c16;
						char16_t this_c16;
						if (heuristic[i] == 0)
							continue; /* Ignore this byte. */
						frst_c16 = frst_cp->icp_decode[i];
						this_c16 = this_cp->icp_decode[i];
						/* If the 2 pages encode different characters, then we have
						 * no way  of telling  which codec  isn't supposed  to  be. */
						if (frst_c16 != this_c16)
							goto_unknown;
					}
				}
				return frst_codec;
			} /* if (best_codecs_count > 0) */
		}     /* Scope... */
	}         /* Scope... */
#ifdef HAVE_LOGGING
	goto_unknown;
#endif /* HAVE_LOGGING */
#undef goto_unknown
unknown:
	return CODEC_UNKNOWN;
}



DEFINE_PUBLIC_ALIAS(iconv_detect_codec, libiconv_detect_codec);

DECL_END

#endif /* !GUARD_LIBICONV_DETECT_C */
