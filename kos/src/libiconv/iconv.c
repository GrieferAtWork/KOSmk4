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
#define _KOS_SOURCE 1

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
#include "cp.h"
#include "iconv.h"

DECL_BEGIN

STATIC_ASSERT(offsetof(struct iconv_encode, ice_output) == offsetof(struct iconv_decode, icd_output));
STATIC_ASSERT(offsetof(struct iconv_encode, ice_flags) == offsetof(struct iconv_decode, icd_flags));
STATIC_ASSERT(sizeof(union iconv_decode_data) == (_ICONV_DECODE_OPAQUE_POINTERS * sizeof(void *)));
STATIC_ASSERT(sizeof(union iconv_encode_data) == (_ICONV_ENCODE_OPAQUE_POINTERS * sizeof(void *)));

PRIVATE NONNULL((1, 2)) int
NOTHROW_NCX(CC libiconv_decode_init)(/*in|out*/ struct iconv_decode *__restrict self,
                                     /*out*/ struct iconv_printer *__restrict input, /* Accepts `input_codec_name' */
                                     /*in*/ unsigned int input_codec) {
	/* By default, the iconv decoder is used as input cookie. */
	input->ii_arg = self;
	switch (input_codec) {

	case CODEC_ASCII:
		if ((self->icd_flags & ICONV_ERRMASK) == ICONV_ERR_IGNORE) {
			/* When  errors can be  ignored, the 7-bit ascii
			 * character set is source-compatible with UTF-8 */
			*input = self->icd_output;
		} else {
			input->ii_printer = (pformatprinter)&libiconv_ascii_decode_errchk;
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

	default: {
		struct iconv_codepage const *cp;
		/* Check for a generic code page */
		cp = libiconv_get_codepage(input_codec);
		if (cp) {
			self->icd_data.idd_cp = cp;
			input->ii_printer     = (pformatprinter)&libiconv_cp_decode;
			break;
		}
		errno = ENOENT;
		return -1;
	}	break;
	}
	return 0;
}


PRIVATE NONNULL((1, 2)) int
NOTHROW_NCX(CC libiconv_encode_init)(/*in|out*/ struct iconv_encode *__restrict self,
                                     /*out*/ struct iconv_printer *__restrict input, /* Accepts `UTF-8' */
                                     /*in*/ unsigned int output_codec) {
	/* By default, the iconv encoder is used as input cookie. */
	input->ii_arg = self;
	/* Almost all codecs use the utf-8 parser mbstate. */
	__mbstate_init(&self->ice_data.ied_utf8);
	switch (output_codec) {

	case CODEC_ASCII:
		if (self->ice_flags & ICONV_ERR_TRANSLIT) {
			/* When transliteration is enabled, we have to properly decode unicode
			 * characters, since we may need to replace them with longer variants.
			 * As such, use a different parser for this case! */
			input->ii_printer = (pformatprinter)&libiconv_ascii_encode_trans;
		} else if ((self->ice_flags & ICONV_ERRMASK) != ICONV_ERR_IGNORE) {
			/* Encoding ASCII is the same as decoding it. We simply
			 * have  to  handle  any  character  that  is `>= 0x80' */
			input->ii_printer = (pformatprinter)&libiconv_ascii_decode_errchk;
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

	default: {
		struct iconv_codepage const *cp;
		/* Check for a generic code page */
		cp = libiconv_get_codepage(output_codec);
		if (cp) {
			self->ice_data.ied_cp.ic_cp = cp;
			input->ii_printer = (pformatprinter)&libiconv_cp_encode;
			break;
		}
		errno = ENOENT;
		return -1;
	}	break;
	}
	return 0;
}



/* Initialize the given iconv decoder for the purpose of
 * converting  data from an  arbitrary codec into UTF-8.
 * @param: self:             [in|out] iconv decode controller.
 * @param: input_codec_name: [in]  The name of the codec in which input data will be presented.
 * @param: input:            [out] Location  where to write callback+cookie for data input.
 *                                 The written function+cookie may only be used for as long
 *                                 as `self' remains valid.
 * @return: 0 : Success (you may now use `input->ii_printer' and `input->ii_arg' to feed data)
 * @return: -1: [errno=ENOENT] Unsupported/unknown codec `input_codec_name' */
INTERN NONNULL((1, 2, 3)) int
NOTHROW_NCX(CC _libiconv_decode_init)(/*in|out*/ struct iconv_decode *__restrict self,
                                      /*out*/ struct iconv_printer *__restrict input, /* Accepts `input_codec_name' */
                                      /*in*/ char const *__restrict input_codec_name) {
	unsigned int codec;
	codec = libiconv_codecbyname(input_codec_name);
	return libiconv_decode_init(self, input, codec);
}



/* Initialize the given iconv encoder for the purpose of
 * converting  data from an  arbitrary codec into UTF-8.
 * @param: self:              [in|out] iconv encode controller.
 * @param: output_codec_name: [in]  The name of the codec in which output data will be printed.
 * @param: input:             [out] Location  where to write callback+cookie for data input.
 *                                  The written function+cookie may only be used for as long
 *                                  as `self' remains valid.
 * @return: 0 : Success (you may now use `input->ii_printer' and `input->ii_arg' to feed data)
 * @return: -1: [errno=ENOENT] Unsupported/unknown codec `output_codec_name' */
INTERN NONNULL((1, 2, 3)) int
NOTHROW_NCX(CC _libiconv_encode_init)(/*in|out*/ struct iconv_encode *__restrict self,
                                      /*out*/ struct iconv_printer *__restrict input, /* Accepts `UTF-8' */
                                      /*in*/ char const *__restrict output_codec_name) {
	unsigned int codec;
	codec = libiconv_codecbyname(output_codec_name);
	return libiconv_encode_init(self, input, codec);
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
 * @return: -1: [errno=ENOENT] Unsupported/unknown codec `input_codec_name' or `output_codec_name' */
INTERN NONNULL((1, 2, 3, 4)) int
NOTHROW_NCX(CC _libiconv_transcode_init)(/*in|out*/ struct iconv_transcode *__restrict self,
                                         /*out*/ struct iconv_printer *__restrict input, /* Accepts `input_codec_name' */
                                         /*in*/ char const *__restrict input_codec_name,
                                         /*in*/ char const *__restrict output_codec_name) {
	int result;
	unsigned int input_codec;
	unsigned int output_codec;

	input_codec  = libiconv_codecbyname(input_codec_name);
	output_codec = libiconv_codecbyname(output_codec_name);

	/* Check for special case: when input and output  codecs are the same,  then
	 *                         it really shouldn't matter if we don't know them! */
	if (input_codec == output_codec &&
	    (input_codec != 0 || strcasecmp(input_codec_name, output_codec_name) == 0)) {
		*input = self->it_encode.ice_output;
		return 0;
	}

	/* Initialize the encoder and set-up its input pipe for use as output by the decoder. */
	self->it_decode.icd_flags = self->it_encode.ice_flags;
	result = libiconv_encode_init(&self->it_encode,
	                              &self->it_decode.icd_output,
	                              output_codec);
	if unlikely(result != 0)
		goto done;

	/* Initialize the decoder (note that it's output printer was already set-up
	 * as the input descriptor for the  encode function in the previous  step!) */
	result = libiconv_decode_init(&self->it_decode,
	                              input,
	                              input_codec);

	/* And that's already it! */

done:
	return result;
}





/* Exports... */
DEFINE_PUBLIC_ALIAS(_iconv_decode_init, _libiconv_decode_init);
DEFINE_PUBLIC_ALIAS(_iconv_decode_init, _libiconv_decode_init);
DEFINE_PUBLIC_ALIAS(_iconv_transcode_init, _libiconv_transcode_init);

DECL_END

#endif /* !GUARD_LIBICONV_ICONV_C */
