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
#ifndef GUARD_LIBICONV_ICONV_C
#define GUARD_LIBICONV_ICONV_C 1

#include "api.h"
/**/

#include <hybrid/byteorder.h>

#include <kos/types.h>

#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <unicode.h>

#include "codecs.h"
#include "convert.h"
#include "cp-7h.h"
#include "cp-7l.h"
#include "cp-iso646.h"
#include "cp.h"
#include "iconv.h"

DECL_BEGIN

STATIC_ASSERT(sizeof(union iconv_decode_data) == (_ICONV_DECODE_OPAQUE_POINTERS * sizeof(void *)));
STATIC_ASSERT(sizeof(union iconv_encode_data) == (_ICONV_ENCODE_OPAQUE_POINTERS * sizeof(void *)));

INTERN NONNULL((1, 2)) int
NOTHROW_NCX(CC libiconv_decode_init)(/*in|out*/ struct iconv_decode *__restrict self,
                                     /*out*/ struct iconv_printer *__restrict input) {
	/* By default, the iconv decoder is used as input cookie. */
	input->ii_arg = self;
	switch (self->icd_codec) {

	case CODEC_ASCII:
		if ((self->icd_flags & ICONV_ERRMASK) == ICONV_ERR_IGNORE) {
			/* When  errors can be  ignored, the 7-bit ascii
			 * character set is source-compatible with UTF-8 */
			*input = self->icd_output;
		} else {
			input->ii_printer = (pformatprinter)&libiconv_ascii_decode;
		}
		break;

	case CODEC_UTF8:
		/* Simple no-op (because output is also UTF-8) */
		*input = self->icd_output;
		break;

	case CODEC_UTF16LE:
		input->ii_printer = (pformatprinter)&libiconv_utf16le_decode;
		self->icd_data.idd_utf.u_pbc = 0;
		mbstate_init(&self->icd_data.idd_utf.u_16);
		break;

	case CODEC_UTF16BE:
		input->ii_printer = (pformatprinter)&libiconv_utf16be_decode;
		self->icd_data.idd_utf.u_pbc = 0;
		mbstate_init(&self->icd_data.idd_utf.u_16);
		break;

	case CODEC_UTF32LE:
		input->ii_printer = (pformatprinter)&libiconv_utf32le_decode;
		self->icd_data.idd_utf.u_pbc = 0;
		break;

	case CODEC_UTF32BE:
		input->ii_printer = (pformatprinter)&libiconv_utf32be_decode;
		self->icd_data.idd_utf.u_pbc = 0;
		break;

	case CODEC_ISO_8859_1:
		input->ii_printer = (pformatprinter)&libiconv_latin1_decode;
		break;

#if CODEC_CP_COUNT != 0
	case CODEC_CP_MIN ... CODEC_CP_MAX:
		/* 8-bit codepage */
		self->icd_data.idd_cp = libiconv_cp_page(self->icd_codec);
		input->ii_printer     = (pformatprinter)&libiconv_cp_decode;
		break;
#endif /* CODEC_CP_COUNT != 0 */

#if CODEC_CP7H_COUNT != 0
	case CODEC_CP7H_MIN ... CODEC_CP7H_MAX:
		/* 7h codepage */
		self->icd_data.idd_cp7h = libiconv_cp7h_page(self->icd_codec);
		input->ii_printer       = (pformatprinter)&libiconv_cp7h_decode;
		break;
#endif /* CODEC_CP7H_COUNT != 0 */

#if CODEC_CP7L_COUNT != 0
	case CODEC_CP7L_MIN ... CODEC_CP7L_MAX:
		/* 7l codepage */
		self->icd_data.idd_cp7l = libiconv_cp7l_page(self->icd_codec);
		input->ii_printer       = (pformatprinter)&libiconv_cp7l_decode;
		break;
#endif /* CODEC_CP7L_COUNT != 0 */

#if CODEC_ISO646_COUNT != 0
	case CODEC_ISO646_MIN ... CODEC_ISO646_MAX:
		/* iso646 codepage. */
		self->icd_data.idd_cp646 = libiconv_iso646_page(self->icd_codec);
		input->ii_printer        = (pformatprinter)&libiconv_cp646_decode;
		break;
#endif /* CODEC_ISO646_COUNT != 0 */

		/* C-escape */
	case CODEC_C_ESCAPE:
	case CODEC_C_ESCAPE_RAW:
	case CODEC_C_ESCAPE_ALL:
	case CODEC_C_ESCAPE_CHR:
	case CODEC_C_ESCAPE_STR:
	case CODEC_C_ESCAPE_INCHR:
	case CODEC_C_ESCAPE_INSTR:
	case CODEC_C_ESCAPE_BYTES:
	case CODEC_C_ESCAPE_BYTES_RAW:
	case CODEC_C_ESCAPE_BYTES_ALL:
	case CODEC_C_ESCAPE_BYTES_CHR:
	case CODEC_C_ESCAPE_BYTES_STR:
	case CODEC_C_ESCAPE_BYTES_INCHR:
	case CODEC_C_ESCAPE_BYTES_INSTR:
		input->ii_printer = (pformatprinter)&libiconv_c_escape_decode;
		/* Set-up the initial state for the parser. */
		mbstate_init(&self->icd_data.idd_cesc.ce_utf8);
		if (self->icd_codec == CODEC_C_ESCAPE_STR || self->icd_codec == CODEC_C_ESCAPE_BYTES_STR) {
			self->icd_flags |= _ICONV_CDECODE_ST_STR;
		} else if (self->icd_codec == CODEC_C_ESCAPE_CHR || self->icd_codec == CODEC_C_ESCAPE_BYTES_CHR) {
			self->icd_flags |= _ICONV_CDECODE_ST_CHR;
		} else if (self->icd_codec == CODEC_C_ESCAPE_INSTR || self->icd_codec == CODEC_C_ESCAPE_BYTES_INSTR) {
			/* Start out inside of a string, but stop once we go outside */
			self->icd_flags |= (_ICONV_CDECODE_ST_STRIN | _ICONV_CDECODE_F_ONESTR);
		} else if (self->icd_codec == CODEC_C_ESCAPE_INCHR || self->icd_codec == CODEC_C_ESCAPE_BYTES_INCHR) {
			/* Start out inside of a character, but stop once we go outside */
			self->icd_flags |= (_ICONV_CDECODE_ST_CHRIN | _ICONV_CDECODE_F_ONESTR);
		} else if (self->icd_codec == CODEC_C_ESCAPE_ALL || self->icd_codec == CODEC_C_ESCAPE_BYTES_ALL) {
			self->icd_flags |= _ICONV_CDECODE_ST_ALLIN;
		} else if (self->icd_codec == CODEC_C_ESCAPE_RAW || self->icd_codec == CODEC_C_ESCAPE_BYTES_RAW) {
			self->icd_flags |= _ICONV_CDECODE_ST_RAW; /* Immediately start off in raw-mode. */
		} else {
			/* Undefined; to-be determined by the first parsed byte. */
			self->icd_flags |= _ICONV_CDECODE_ST_UNDEF;
		}
		break;

	case CODEC_XML_ESCAPE:
		input->ii_printer = (pformatprinter)&libiconv_xml_escape_decode;
		mbstate_init(&self->icd_data.idd_xml.xe_utf8);
		self->icd_data.idd_xml.xe_mode = _ICONV_DECODE_XML_TXT;
		break;

	case CODEC_URI_ESCAPE:
		input->ii_printer = (pformatprinter)&libiconv_uri_escape_decode;
		self->icd_data.idd_uri.ue_mode = _ICONV_DECODE_URI_TXT;
		break;

	case CODEC_HEX_LOWER:
	case CODEC_HEX_UPPER:
		input->ii_printer = (pformatprinter)&libiconv_hex_decode;
		self->icd_data.idd_hex = 0x01;
		break;

	default:
		errno = EINVAL;
		return -1;
	}
	return 0;
}

/* Check  if the given encoder is in its default (zero) shift state. If it isn't,
 * then that must mean that it's still waiting for more input data to arrive, and
 * that  you should either feed it said data,  or deal with the fact that there's
 * something missing in your input.
 * WARNING: This  function DOESN'T work  when the given decoder  is used to parse
 *          UTF-8 input! This is because special optimizations are performed when
 *          decoding  UTF-8 (since  decoders also  always output  UTF-8). In this
 *          case this function will always return `true'
 * Hint: the optimization is that  `iconv_decode_init:input == self->icd_output',
 *       so if you want to programmatically handle this case you can check for it
 *       by doing `self->icd_output.ii_printer == :input->ii_printer', where  the
 *       given `:input' is the one filled in by `iconv_decode_init(3)' */
INTERN ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC libiconv_decode_isshiftzero)(struct iconv_decode const *__restrict self) {
	switch (self->icd_codec) {

	case CODEC_UTF16LE:
	case CODEC_UTF16BE:
		return self->icd_data.idd_utf.u_pbc == 0 &&
		       mbstate_isempty(&self->icd_data.idd_utf.u_16);

	case CODEC_UTF32LE:
	case CODEC_UTF32BE:
		return self->icd_data.idd_utf.u_pbc == 0;

		/* C-escape */
	case CODEC_C_ESCAPE:
	case CODEC_C_ESCAPE_RAW:
	case CODEC_C_ESCAPE_CHR:
	case CODEC_C_ESCAPE_STR:
	case CODEC_C_ESCAPE_BYTES:
	case CODEC_C_ESCAPE_BYTES_RAW:
	case CODEC_C_ESCAPE_BYTES_CHR:
	case CODEC_C_ESCAPE_BYTES_STR:
		return mbstate_isempty(&self->icd_data.idd_cesc.ce_utf8) &&
		       /* Make sure that the parser state indicate that we're outside of a string. */
		       (/* String type never determined */
		        (self->icd_flags & _ICONV_CDECODE_STMASK) == _ICONV_CDECODE_ST_UNDEF ||
		        /* "-string, but outside "-pairs */
		        (self->icd_flags & _ICONV_CDECODE_STMASK) == _ICONV_CDECODE_ST_STR ||
		        /* '-string, but outside '-pairs */
		        (self->icd_flags & _ICONV_CDECODE_STMASK) == _ICONV_CDECODE_ST_CHR ||
		        /* Raw strings don't have a notion of inside or outside, so shift is always 0 */
		        (self->icd_flags & _ICONV_CDECODE_STMASK) == _ICONV_CDECODE_ST_RAW);

	case CODEC_C_ESCAPE_INSTR:
	case CODEC_C_ESCAPE_INCHR:
	case CODEC_C_ESCAPE_ALL:
	case CODEC_C_ESCAPE_BYTES_INCHR:
	case CODEC_C_ESCAPE_BYTES_INSTR:
	case CODEC_C_ESCAPE_BYTES_ALL:
		/* These codecs are a little more special since the base-line requires that we're
		 * inside  of a character or string constant.  As such, the zero-shift state must
		 * reflect this and only apply while we're still inside! */
		return mbstate_isempty(&self->icd_data.idd_cesc.ce_utf8) &&
		       ((self->icd_flags & _ICONV_CDECODE_STMASK) == _ICONV_CDECODE_ST_STRIN ||
		        (self->icd_flags & _ICONV_CDECODE_STMASK) == _ICONV_CDECODE_ST_CHRIN ||
		        (self->icd_flags & _ICONV_CDECODE_STMASK) == _ICONV_CDECODE_ST_ALLIN);

	case CODEC_XML_ESCAPE:
		/* Make sure that we're not inside of an XML escape sequence. */
		return mbstate_isempty(&self->icd_data.idd_xml.xe_utf8) &&
		       (self->icd_data.idd_xml.xe_mode == _ICONV_DECODE_XML_TXT ||
		        /* OptionalSeMicollon also counts as a 0-shift state! */
		        self->icd_data.idd_xml.xe_mode == _ICONV_DECODE_XML_OSM);

	case CODEC_URI_ESCAPE:
		/* Make sure that we're not inside of a %XX sequence. */
		return self->icd_data.idd_uri.ue_mode == _ICONV_DECODE_URI_TXT;

	case CODEC_HEX_LOWER:
	case CODEC_HEX_UPPER:
		/* Make sure that we've parsed an even number of nibbles */
		return self->icd_data.idd_hex == 0x01;

	default:
		break;
	}
	return true;
}





INTERN NONNULL((1, 2)) int
NOTHROW_NCX(CC libiconv_encode_init)(/*in|out*/ struct iconv_encode *__restrict self,
                                     /*out*/ struct iconv_printer *__restrict input) {
	/* By default, the iconv encoder is used as input cookie. */
	input->ii_arg = self;
	/* Almost all codecs use the utf-8 parser mbstate. */
	mbstate_init(&self->ice_data.ied_utf8);
	switch (self->ice_codec) {

	case CODEC_ASCII:
		if ((self->ice_flags & ICONV_ERRMASK) != ICONV_ERR_IGNORE ||
		    (self->ice_flags & ICONV_ERR_TRANSLIT)) {
			/* Encoding ASCII is the same as decoding it. We simply
			 * have  to  handle  any  character  that  is `>= 0x80' */
			input->ii_printer = (pformatprinter)&libiconv_ascii_encode;
		} else {
			/* When  errors can be  ignored, the 7-bit ascii
			 * character set is source-compatible with UTF-8 */
			*input = self->ice_output;
		}
		break;

	case CODEC_UTF8:
		/* Simple no-op (because output is also UTF-8) */
		*input = self->ice_output;
		break;

	case CODEC_UTF16LE:
		input->ii_printer = (pformatprinter)&libiconv_utf16le_encode;
		break;

	case CODEC_UTF16BE:
		input->ii_printer = (pformatprinter)&libiconv_utf16be_encode;
		break;

	case CODEC_UTF32LE:
		input->ii_printer = (pformatprinter)&libiconv_utf32le_encode;
		break;

	case CODEC_UTF32BE:
		input->ii_printer = (pformatprinter)&libiconv_utf32be_encode;
		break;

	case CODEC_ISO_8859_1:
		input->ii_printer = (pformatprinter)&libiconv_latin1_encode;
		break;

#if CODEC_CP_COUNT != 0
	case CODEC_CP_MIN ... CODEC_CP_MAX:
		/* 8-bit codepage */
		self->ice_data.ied_cp = libiconv_cp_page(self->ice_codec);
		input->ii_printer     = (pformatprinter)&libiconv_cp_encode;
		break;
#endif /* CODEC_CP_COUNT != 0 */

#if CODEC_CP7H_COUNT != 0
	case CODEC_CP7H_MIN ... CODEC_CP7H_MAX:
		/* 7h codepage */
		self->ice_data.ied_cp7h = libiconv_cp7h_page(self->ice_codec);
		input->ii_printer       = (pformatprinter)&libiconv_cp7h_encode;
		break;
#endif /* CODEC_CP7H_COUNT != 0 */

#if CODEC_CP7L_COUNT != 0
	case CODEC_CP7L_MIN ... CODEC_CP7L_MAX:
		/* 7l codepage */
		self->ice_data.ied_cp7l = libiconv_cp7l_page(self->ice_codec);
		input->ii_printer       = (pformatprinter)&libiconv_cp7l_encode;
		break;
#endif /* CODEC_CP7L_COUNT != 0 */

#if CODEC_ISO646_COUNT != 0
	case CODEC_ISO646_MIN ... CODEC_ISO646_MAX:
		/* iso646 codepage. */
		self->ice_data.ied_cp646 = libiconv_iso646_page(self->ice_codec);
		input->ii_printer        = (pformatprinter)&libiconv_cp646_encode;
		break;
#endif /* CODEC_ISO646_COUNT != 0 */

		/* C-escape */
	case CODEC_C_ESCAPE:
	case CODEC_C_ESCAPE_RAW:
	case CODEC_C_ESCAPE_ALL:
	case CODEC_C_ESCAPE_CHR:
	case CODEC_C_ESCAPE_STR:
	case CODEC_C_ESCAPE_INCHR:
	case CODEC_C_ESCAPE_INSTR:
	case CODEC_C_ESCAPE_BYTES:
	case CODEC_C_ESCAPE_BYTES_RAW:
	case CODEC_C_ESCAPE_BYTES_ALL:
	case CODEC_C_ESCAPE_BYTES_CHR:
	case CODEC_C_ESCAPE_BYTES_STR:
	case CODEC_C_ESCAPE_BYTES_INCHR:
	case CODEC_C_ESCAPE_BYTES_INSTR:
		/* All c-escape variants use the same function for encoding. */
		input->ii_printer = (pformatprinter)&libiconv_c_escape_encode;

		/* Set-up  flags depending  on which  codec is  being used exactly.
		 * Note that when it comes to encoding, some of the c-escape codecs
		 * behave  exactly the same,  but don't when  it comes to decoding.
		 * See the documentation in `iconvdata/db'! */

		/* >> if ("_CHR" !in str(self->ice_codec) && "_STR" !in str(self->ice_codec)) */
		if (self->ice_codec == CODEC_C_ESCAPE || self->ice_codec == CODEC_C_ESCAPE_BYTES ||
		    self->ice_codec == CODEC_C_ESCAPE_RAW || self->ice_codec == CODEC_C_ESCAPE_BYTES_RAW ||
		    self->ice_codec == CODEC_C_ESCAPE_ALL || self->ice_codec == CODEC_C_ESCAPE_BYTES_ALL)
			self->ice_flags |= _ICONV_CENCODE_NOQUOTE; /* Don't emit quotes */

		/* >> if ("_CHR" in str(self->ice_codec)) */
		if (self->ice_codec == CODEC_C_ESCAPE_CHR || self->ice_codec == CODEC_C_ESCAPE_INCHR ||
		    self->ice_codec == CODEC_C_ESCAPE_BYTES_CHR || self->ice_codec == CODEC_C_ESCAPE_BYTES_INCHR)
			self->ice_flags |= _ICONV_CENCODE_USECHAR; /* Emit ' instead of " when printing quotes */

		/* >> if ("_BYTES" in str(self->ice_codec)) */
		if (self->ice_codec == CODEC_C_ESCAPE_BYTES || self->ice_codec == CODEC_C_ESCAPE_BYTES_RAW ||
		    self->ice_codec == CODEC_C_ESCAPE_BYTES_CHR || self->ice_codec == CODEC_C_ESCAPE_BYTES_INCHR ||
		    self->ice_codec == CODEC_C_ESCAPE_BYTES_STR || self->ice_codec == CODEC_C_ESCAPE_BYTES_INSTR)
			self->ice_flags |= _ICONV_CENCODE_NOUNICD; /* Don't emit \u or \U and encode everything as \x */
		break;

	case CODEC_XML_ESCAPE:
		input->ii_printer = (pformatprinter)&libiconv_xml_escape_encode;
		break;

	case CODEC_URI_ESCAPE:
		input->ii_printer = (pformatprinter)&libiconv_uri_escape_encode;
		break;

	case CODEC_HEX_LOWER:
		input->ii_printer = (pformatprinter)&libiconv_hex_lower_encode;
		break;

	case CODEC_HEX_UPPER:
		input->ii_printer = (pformatprinter)&libiconv_hex_upper_encode;
		break;

	default:
		errno = EINVAL;
		return -1;
	}
	return 0;
}

/* Reset the internal shift state to its  default and print the associated byte  sequence
 * to the output printer of the encode descriptor, returning the sum of its return values
 * or the first negative return value.
 * This  function should be  called once all input  data has been  printed and will ensure
 * that input didn't end with an incomplete byte sequence, and that output doesn't contain
 * any unmatched shift-state changes.
 * Simply  call this once you're out of input  and treat its return value like you're
 * treating the return values of the input printer returned by `iconv_encode_init(3)' */
INTERN NONNULL((1)) ssize_t
NOTHROW_NCX(CC libiconv_encode_flush)(struct iconv_encode *__restrict self) {
	ssize_t result = 0;
	switch (self->ice_codec) {

	case CODEC_C_ESCAPE_CHR:
	case CODEC_C_ESCAPE_STR:
	case CODEC_C_ESCAPE_INCHR:
	case CODEC_C_ESCAPE_INSTR:
	case CODEC_C_ESCAPE_BYTES_CHR:
	case CODEC_C_ESCAPE_BYTES_STR:
	case CODEC_C_ESCAPE_BYTES_INCHR:
	case CODEC_C_ESCAPE_BYTES_INSTR:
		if (self->ice_flags & _ICONV_CENCODE_INQUOTE) {
			char out[1] = { '\"' };
			if (self->ice_flags & _ICONV_CENCODE_USECHAR)
				out[0] = '\'';
			result = (*self->ice_output.ii_printer)(self->ice_output.ii_arg, out, 1);
			if likely(result >= 0)
				self->ice_flags &= ~_ICONV_CENCODE_INQUOTE;
		}
		break;

	default:
		break;
	}
	/* (Almost) all encode codecs need a UTF-8 multi-byte state descriptor
	 * so that they're able to decode  the in-coming UTF-8 data. Here,  we
	 * have to reset that state! */
	mbstate_init(&self->ice_data.ied_utf8);
	return result;
}






/* Initialize the given iconv decoder for the purpose of
 * converting  data from an  arbitrary codec into UTF-8.
 * @param: self:             [in|out] iconv decode controller.
 * @param: input_codec_name: [in]  The name of the codec in which input data will be presented.
 * @param: input:            [out] Location  where to write callback+cookie for data input.
 *                                 The written function+cookie may only be used for as long
 *                                 as `self' remains valid.
 * @return: 0 : Success (you may now use `input->ii_printer' and `input->ii_arg' to feed data)
 * @return: -1: [errno=EINVAL] Unsupported/unknown codec `input_codec_name' */
INTERN NONNULL((1, 2, 3)) int
NOTHROW_NCX(CC _libiconv_decode_init)(/*in|out*/ struct iconv_decode *__restrict self,
                                      /*out*/ struct iconv_printer *__restrict input, /* Accepts `input_codec_name' */
                                      /*in*/ char const *__restrict input_codec_name) {
	self->icd_codec = libiconv_codec_and_flags_byname(input_codec_name, &self->icd_flags);
	return libiconv_decode_init(self, input);
}





/* Initialize the given iconv encoder for the purpose of
 * converting  data from an  arbitrary codec into UTF-8.
 * @param: self:              [in|out] iconv encode controller.
 * @param: output_codec_name: [in]  The name of the codec in which output data will be printed.
 * @param: input:             [out] Location  where to write callback+cookie for data input.
 *                                  The written function+cookie may only be used for as long
 *                                  as `self' remains valid.
 * @return: 0 : Success (you may now use `input->ii_printer' and `input->ii_arg' to feed data)
 * @return: -1: [errno=EINVAL] Unsupported/unknown codec `output_codec_name' */
INTERN NONNULL((1, 2, 3)) int
NOTHROW_NCX(CC _libiconv_encode_init)(/*in|out*/ struct iconv_encode *__restrict self,
                                      /*out*/ struct iconv_printer *__restrict input, /* Accepts `UTF-8' */
                                      /*in*/ char const *__restrict output_codec_name) {
	self->ice_codec = libiconv_codec_and_flags_byname(output_codec_name, &self->ice_flags);
	return libiconv_encode_init(self, input);
}




/* The  combination  of the  encode+decode functions  into  a single  one which
 * allows  for conversion from an arbitrary codec into another arbitrary codec.
 * This is pretty much just a convenience wrapper around the other 2 functions,
 * and you can  easily tell as  much if you  were to look  at this one's  impl.
 * @param: self:              [in|out] iconv encode/decode controller.
 * @param: input_codec_name:  [in]  The name of the codec in which input data will be presented.
 * @param: output_codec_name: [in]  The name of the codec in which output data will be printed.
 * @param: input:             [out] Location  where to write callback+cookie for data input.
 *                                  The written function+cookie may only be used for as long
 *                                  as `self' remains valid.
 * @return: 0 : Success (you may now use `input->ii_printer' and `input->ii_arg' to feed data)
 * @return: -1: [errno=EINVAL] Unsupported/unknown codec `input_codec_name' or `output_codec_name' */
INTERN NONNULL((1, 2, 3, 4)) int
NOTHROW_NCX(CC _libiconv_transcode_init)(/*in|out*/ struct iconv_transcode *__restrict self,
                                         /*out*/ struct iconv_printer *__restrict input, /* Accepts `input_codec_name' */
                                         /*in*/ char const *__restrict input_codec_name,
                                         /*in*/ char const *__restrict output_codec_name) {
	int result;

	/* The caller only fills in flags for the encoder. */
	self->it_decode.icd_flags = self->it_encode.ice_flags;

	/* Load codec names and parse additional flags. */
	self->it_decode.icd_codec = libiconv_codec_and_flags_byname(input_codec_name, &self->it_decode.icd_flags);
	self->it_encode.ice_codec = libiconv_codec_and_flags_byname(output_codec_name, &self->it_encode.ice_flags);

	/* Check for special case: when input and output  codecs are the same,  then
	 *                         it really shouldn't matter if we don't know them! */
	if (self->it_decode.icd_codec == self->it_encode.ice_codec &&
	    (self->it_decode.icd_codec != CODEC_UNKNOWN ||
	     libiconv_same_codec_name(input_codec_name, output_codec_name))) {
		*input = self->it_encode.ice_output;
		return 0;
	}

	/* Initialize the encoder and set-up its input pipe for use as output by the decoder. */
	result = libiconv_encode_init(&self->it_encode, &self->it_decode.icd_output);
	if unlikely(result != 0)
		goto done;

	/* Initialize the decoder (note that it's output printer was already set-up
	 * as the input descriptor for the  encode function in the previous  step!) */
	result = libiconv_decode_init(&self->it_decode, input);

	/* And that's already it! */

done:
	return result;
}



/* Exports... */
DEFINE_PUBLIC_ALIAS(_iconv_decode_init, _libiconv_decode_init);
DEFINE_PUBLIC_ALIAS(iconv_decode_isshiftzero, libiconv_decode_isshiftzero);
DEFINE_PUBLIC_ALIAS(_iconv_encode_init, _libiconv_encode_init);
DEFINE_PUBLIC_ALIAS(iconv_encode_flush, libiconv_encode_flush);
DEFINE_PUBLIC_ALIAS(_iconv_transcode_init, _libiconv_transcode_init);

DECL_END

#endif /* !GUARD_LIBICONV_ICONV_C */
