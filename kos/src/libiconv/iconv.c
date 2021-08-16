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
		__mbstate_init(&self->icd_data.idd_utf.u_16);
		break;

	case CODEC_UTF16BE:
		input->ii_printer = (pformatprinter)&libiconv_utf16be_decode;
		self->icd_data.idd_utf.u_pbc = 0;
		__mbstate_init(&self->icd_data.idd_utf.u_16);
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

	case CODEC_CP_MIN ... CODEC_CP_MAX:
		/* 8-bit codepage */
		self->icd_data.idd_cp = libiconv_cp_page(self->icd_codec);
		input->ii_printer     = (pformatprinter)&libiconv_cp_decode;
		break;

	case CODEC_CP7H_MIN ... CODEC_CP7H_MAX:
		/* 7h codepage */
		self->icd_data.idd_cp7h = libiconv_cp7h_page(self->icd_codec);
		input->ii_printer       = (pformatprinter)&libiconv_cp7h_decode;
		break;

	case CODEC_CP7L_MIN ... CODEC_CP7L_MAX:
		/* 7l codepage */
		self->icd_data.idd_cp7l = libiconv_cp7l_page(self->icd_codec);
		input->ii_printer       = (pformatprinter)&libiconv_cp7l_decode;
		break;

	case CODEC_ISO646_MIN ... CODEC_ISO646_MAX:
		/* iso646 codepage. */
		self->icd_data.idd_cp646 = libiconv_iso646_page(self->icd_codec);
		input->ii_printer        = (pformatprinter)&libiconv_cp646_decode;
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
		       __MBSTATE_ISINIT(&self->icd_data.idd_utf.u_16);

	case CODEC_UTF32LE:
	case CODEC_UTF32BE:
		return self->icd_data.idd_utf.u_pbc == 0;

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
	__mbstate_init(&self->ice_data.ied_utf8);
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

	case CODEC_CP_MIN ... CODEC_CP_MAX:
		/* 8-bit codepage */
		self->ice_data.ied_cp = libiconv_cp_page(self->ice_codec);
		input->ii_printer     = (pformatprinter)&libiconv_cp_encode;
		break;

	case CODEC_CP7H_MIN ... CODEC_CP7H_MAX:
		/* 7h codepage */
		self->ice_data.ied_cp7h = libiconv_cp7h_page(self->ice_codec);
		input->ii_printer       = (pformatprinter)&libiconv_cp7h_encode;
		break;

	case CODEC_CP7L_MIN ... CODEC_CP7L_MAX:
		/* 7l codepage */
		self->ice_data.ied_cp7l = libiconv_cp7l_page(self->ice_codec);
		input->ii_printer       = (pformatprinter)&libiconv_cp7l_encode;
		break;

	case CODEC_ISO646_MIN ... CODEC_ISO646_MAX:
		/* iso646 codepage. */
		self->ice_data.ied_cp646 = libiconv_iso646_page(self->ice_codec);
		input->ii_printer        = (pformatprinter)&libiconv_cp646_encode;
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

		/* No supported codec currently requires any additional work!
		 * TODO: This will change once support for more complicated
		 *       codecs gets added. */

	default:
		break;
	}
	/* All encode codecs need a UTF-8 multi-byte state descriptor  so
	 * that they're able to decode the in-coming UTF-8 data. Here, we
	 * have to reset that state! */
	__mbstate_init(&self->ice_data.ied_utf8);
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
