/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_MBCTYPE_C
#define GUARD_LIBC_USER_MBCTYPE_C 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <format-printer.h>
#include <stddef.h>
#include <stdio.h>
#include <unicode.h>

#include <libiconv/iconv.h>

#include "../libc/globals.h"
#include "mbctype.h"

#ifndef FCALL
#define FCALL __FCALL
#endif /* !FCALL */

DECL_BEGIN

INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) void *FCALL
libc_get_libiconv_symbol(char const *__restrict name);
#define DEFINE_LIBICONV_SYMBOL_BINDING(T, name)                                        \
	PRIVATE ATTR_SECTION(".bss.crt.dos.mbstring") T pdyn_##name               = NULL;  \
	PRIVATE ATTR_SECTION(".rodata.crt.dos.mbstring") char const name_##name[] = #name; \
	PRIVATE ATTR_SECTION(".text.crt.dos.mbstring")                                     \
	T FCALL libc_resolve_##name(void) {                                                \
		if (pdyn_##name == NULL)                                                       \
			*(void **)&pdyn_##name = libc_get_libiconv_symbol(name_##name);            \
		return pdyn_##name;                                                            \
	}
DEFINE_LIBICONV_SYMBOL_BINDING(_PICONV_DECODE_INIT, _iconv_decode_init)
DEFINE_LIBICONV_SYMBOL_BINDING(PICONV_DECODE_ISSHIFTZERO, iconv_decode_isshiftzero)
DEFINE_LIBICONV_SYMBOL_BINDING(_PICONV_ENCODE_INIT, _iconv_encode_init)
DEFINE_LIBICONV_SYMBOL_BINDING(PICONV_ENCODE_FLUSH, iconv_encode_flush)
#define _iconv_decode_init       (*libc_resolve__iconv_decode_init())
#define iconv_decode_isshiftzero (*libc_resolve_iconv_decode_isshiftzero())
#define _iconv_encode_init       (*libc_resolve__iconv_encode_init())
#define iconv_encode_flush       (*libc_resolve_iconv_encode_flush())
#undef DEFINE_LIBICONV_SYMBOL_BINDING

/*[[[deemon
import * from deemon;
#define __ascii_ispunct(ch)  (((ch) >= 0x21 && (ch) <= 0x2f) || ((ch) >= 0x3a && (ch) <= 0x40) || ((ch) >= 0x5b && (ch) <= 0x60) || ((ch) >= 0x7b && (ch) <= 0x7e))
#define _MS    0x01 // _ismbbkalnum: ...
#define _MP    0x02 // _ismbbkpunct: ...
#define _M1    0x04 // _ismbblead: First byte
#define _M2    0x08 // _ismbbtrail: Second byte
#define _SBUP  0x10 // _ismbcupper (for characters <= 0xff)
#define _SBLOW 0x20 // _ismbclower (for characters <= 0xff)
function get_mbctype(ord: int): int {
	local result = 0;
	local s = string.chr(ord);
	if (s.isalnum())
		result |= _MS;
	if (__ascii_ispunct(ord))
		result |= _MP;
	if (s.isupper())
		result |= _SBUP;
	if (s.islower())
		result |= _SBLOW;
	return result;
}
print("INTERN ATTR_SECTION(\".data.crt.dos.mbstring\")");
print("unsigned char libc__mbctype[257] = {0,");
for (local line: [:256].segments(16)) {
	print("\t", ",".join(for (local ord: line) get_mbctype(ord)), ",");
}
print("};");
print("INTERN ATTR_SECTION(\".data.crt.dos.mbstring\")");
print("unsigned char libc__mbcasemap[256] = {");
for (local line: [:256].segments(16)) {
	print("\t", ",".join(for (local ord: line)
		string.chr(ord).islower() ? string.chr(ord).upper().ord() :
		string.chr(ord).isupper() ? string.chr(ord).lower().ord() :
		ord), ",");
}
print("};");
]]]*/
INTERN ATTR_SECTION(".data.crt.dos.mbstring")
unsigned char libc__mbctype[257] = {0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,
	2,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
	17,17,17,17,17,17,17,17,17,17,17,2,2,2,2,2,
	2,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,
	33,33,33,33,33,33,33,33,33,33,33,2,2,2,2,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
INTERN ATTR_SECTION(".data.crt.dos.mbstring")
unsigned char libc__mbcasemap[256] = {
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
	16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
	32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
	48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,
	64,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,
	112,113,114,115,116,117,118,119,120,121,122,91,92,93,94,95,
	96,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
	80,81,82,83,84,85,86,87,88,89,90,123,124,125,126,127,
	128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
	144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
	160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
	176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
	192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
	208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
	224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
	240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,
};
/*[[[end]]]*/

#undef _mbctype
#undef _mbcasemap
DEFINE_PUBLIC_ALIAS(_mbctype, libc__mbctype);
DEFINE_PUBLIC_ALIAS(_mbcasemap, libc__mbcasemap);
#define _mbctype   (&GET_NOREL_GLOBAL(_mbctype))
#define _mbcasemap (&GET_NOREL_GLOBAL(_mbcasemap))

/*[[[head:libc___p__mbctype,hash:CRC-32=0xcd3197a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_CONST ATTR_RETNONNULL WUNUSED unsigned char *
NOTHROW(LIBCCALL libc___p__mbctype)(void)
/*[[[body:libc___p__mbctype]]]*/
{
	return _mbctype;
}
/*[[[end:libc___p__mbctype]]]*/

/*[[[head:libc___p__mbcasemap,hash:CRC-32=0xb7872f04]]]*/
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_CONST ATTR_RETNONNULL WUNUSED unsigned char *
NOTHROW(LIBCCALL libc___p__mbcasemap)(void)
/*[[[body:libc___p__mbcasemap]]]*/
{
	return _mbcasemap;
}
/*[[[end:libc___p__mbcasemap]]]*/

/* The currently loaded MBC codepage. */
PRIVATE ATTR_SECTION(".data.crt.dos.mbstring") int libd_mbcp = _MB_CP_UTF8;

/*[[[head:libc__setmbcp,hash:CRC-32=0x744d8eaa]]]*/
INTERN ATTR_SECTION(".text.crt.dos.mbstring") int
NOTHROW_NCX(LIBCCALL libc__setmbcp)(int cp)
/*[[[body:libc__setmbcp]]]*/
{
	int result;
	result    = libd_mbcp;
	libd_mbcp = cp;
	if (result != cp) {
		unsigned int ch;
		unsigned char *mbctype   = _mbctype + 1;
		unsigned char *mbcasemap = _mbcasemap;
		char cpname[lengthof("cp" PRIMAXu)];
		struct iconv_decode decoder;
		struct iconv_printer decode_input;
		struct format_snprintf_data printer;
		int decoder_error;
		if (cp == _MB_CP_UTF8) {
			/* mbstring is officially documented as not working with  UTF-8.
			 * Without  this check right  here, we would  (try to) get UTF-8
			 * working here, even though that would lead to problems further
			 * down the line, related to  the fact that mbstring only  works
			 * with 1- or 2-byte characters. */
			decoder_error = -1;
		} else {
			sprintf(cpname, "cp%u", cp);
			decoder.icd_output.ii_printer = &format_snprintf_printer;
			decoder.icd_output.ii_arg     = &printer;
			decoder.icd_flags             = ICONV_ERR_ERRNO;
			/* Use a decoder to detect lead bytes */
			decoder_error = _iconv_decode_init(&decoder, &decode_input, cpname);
		}
		for (ch = 128; ch < 256; ++ch) {
			unsigned char flags = 0;
			unsigned char casem = ch;
			struct __unitraits const *traits;
			traits = __unicode_descriptor(libc__mbctouni_l(ch, NULL));
			if (traits->__ut_flags & __UNICODE_ISALNUM)
				flags |= _MS;
			if (traits->__ut_flags & __UNICODE_ISPUNCT)
				flags |= _MP;
			if (traits->__ut_flags & __UNICODE_ISUPPER)
				flags |= _SBUP;
			if (traits->__ut_flags & __UNICODE_ISLOWER)
				flags |= _SBLOW;
			if (flags & (_SBUP | _SBLOW))
				casem = (unsigned char)(ch + traits->__ut_lower + traits->__ut_upper);
			if (decoder_error == 0) {
				unsigned char input[1];
				char utf8_buf[UNICODE_UTF8_MAXLEN + 1];
				format_snprintf_init(&printer, utf8_buf, sizeof(utf8_buf));
				input[0] = (unsigned char)ch;
				if ((*decode_input.ii_printer)(decode_input.ii_arg, (char const *)input, 1) < 0) {
					/* Encoding error --> invalid character --> assume it's a trail byte.
					 * XXX: This isn't necessarily correct, but libiconv doesn't offer any
					 *      way to properly determine this... */
					flags |= _M2;
				} else {
					if (!iconv_decode_isshiftzero(&decoder)) {
						/* Non-zero shift state --> This must have been a lead byte. */
						flags |= _M1;
						decoder_error = _iconv_decode_init(&decoder, &decode_input, cpname);
					} else {
						/* Single-byte character. */
					}
				}
			}
			mbctype[ch]   = flags;
			mbcasemap[ch] = casem;
		}
	}
	return result;
}
/*[[[end:libc__setmbcp]]]*/

/*[[[head:libc__getmbcp,hash:CRC-32=0xada42678]]]*/
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__getmbcp)(void)
/*[[[body:libc__getmbcp]]]*/
{
	return libd_mbcp;
}
/*[[[end:libc__getmbcp]]]*/


/*[[[head:libc__mbctouni_l,hash:CRC-32=0x8b190593]]]*/
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED char32_t
NOTHROW_NCX(LIBCCALL libc__mbctouni_l)(unsigned int ch,
                                       locale_t locale)
/*[[[body:libc__mbctouni_l]]]*/
{
	char cpname[lengthof("cp" PRIMAXu)];
	struct iconv_decode decoder;
	struct iconv_printer decode_input;
	struct format_snprintf_data printer;
	char utf8_buf[UNICODE_UTF8_MAXLEN + 1], *utf8_reader;
	unsigned char input[2];
	char32_t utf32;

	/* Simple case: ASCII is always mapped 1-on-1 */
	if (ch < 0x80)
		return ch;

	/* Use libiconv to convert characters from the current MBCS codepage to UTF-8 */
	sprintf(cpname, "cp%u", libc__getmbcp_l(locale));
	format_snprintf_init(&printer, utf8_buf, sizeof(utf8_buf));
	decoder.icd_output.ii_printer = &format_snprintf_printer;
	decoder.icd_output.ii_arg     = &printer;
	decoder.icd_flags             = ICONV_ERR_ERRNO;
	if (_iconv_decode_init(&decoder, &decode_input, cpname) != 0)
		goto err;

	/* Feed input data. */
	input[0] = (unsigned char)(ch >> 8);
	input[1] = (unsigned char)(ch & 0xff);
	if ((*decode_input.ii_printer)(decode_input.ii_arg, (char const *)input, 2) < 0)
		goto err; /* ERROR: Invalid input character */

	/* Ensure that we're in a zero-shift state. */
	if (!iconv_decode_isshiftzero(&decoder)) {
		/* ERROR: Incomplete input character */
		errno = EILSEQ;
		goto err;
	}

	/* Ensure that the UTF-8 buffer didn't completely fill up */
	if (printer.sd_bufsiz == 0) {
		/* ERROR: More than 1 UTF-8 character produced */
		errno = EILSEQ;
		goto err;
	}

	/* Decode produced UTF-8 into UTF-32. */
	utf8_reader = utf8_buf;
	utf32       = unicode_readutf8_n(&utf8_reader, printer.sd_buffer);
	if (utf8_reader != printer.sd_buffer) {
		/* ERROR: More than 1 UTF-8 character produced */
		errno = EILSEQ;
		goto err;
	}
	return utf32;
err:
	return 0;
}
/*[[[end:libc__mbctouni_l]]]*/

/*[[[head:libc__unitombc_l,hash:CRC-32=0xfeb1b14b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__unitombc_l)(char32_t ch,
                                       locale_t locale)
/*[[[body:libc__unitombc_l]]]*/
{
	char cpname[lengthof("cp" PRIMAXu)];
	struct iconv_encode encoder;
	struct iconv_printer encode_input;
	struct format_snprintf_data printer;
	char input[UNICODE_UTF8_MAXLEN];
	size_t input_len;
	unsigned char output[3];
	size_t output_len;
	uint16_t mbc;

	/* Simple case: ASCII is always mapped 1-on-1 */
	if (ch < 0x80)
		return ch;

	/* Use libiconv to convert characters from the current MBCS codepage to UTF-8 */
	sprintf(cpname, "cp%u", libc__getmbcp_l(locale));
	format_snprintf_init(&printer, (char *)output, sizeof(output));
	encoder.ice_output.ii_printer = &format_snprintf_printer;
	encoder.ice_output.ii_arg     = &printer;
	encoder.ice_flags             = ICONV_ERR_ERRNO;
	if (_iconv_encode_init(&encoder, &encode_input, cpname) != 0)
		goto err;

	/* Feed input data. */
	input_len = (size_t)(unicode_writeutf8(input, ch) - input);
	if ((*encode_input.ii_printer)(encode_input.ii_arg, input, input_len) < 0)
		goto err; /* ERROR: Cannot encode `ch' */
	if (iconv_encode_flush(&encoder) < 0)
		goto err; /* ERROR: Cannot encode `ch' */

	/* Ensure that the output buffer didn't fill up completely */
	output_len = sizeof(output) - printer.sd_bufsiz;
	if ((output_len != 1) && (output_len != 2)) {
		/* ERROR: None, or more than 1 MBC character produced */
		errno = EILSEQ;
		goto err;
	}

	/* Assemble the MBC character. */
	mbc = output[0];
	if (output_len == 2)
		mbc = (mbc << 1) | output[1];
	return mbc;
err:
	return 0;
}
/*[[[end:libc__unitombc_l]]]*/

/*[[[start:exports,hash:CRC-32=0x684938f5]]]*/
DEFINE_PUBLIC_ALIAS(__p__mbctype, libc___p__mbctype);
DEFINE_PUBLIC_ALIAS(__p__mbcasemap, libc___p__mbcasemap);
DEFINE_PUBLIC_ALIAS(_setmbcp, libc__setmbcp);
DEFINE_PUBLIC_ALIAS(_getmbcp, libc__getmbcp);
DEFINE_PUBLIC_ALIAS(_mbctouni_l, libc__mbctouni_l);
DEFINE_PUBLIC_ALIAS(_unitombc_l, libc__unitombc_l);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MBCTYPE_C */
