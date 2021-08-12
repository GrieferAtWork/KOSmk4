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
#ifndef _LIBICONV_WRITER_H
#define _LIBICONV_WRITER_H 1

#include "api.h"
/**/

#include <__stdinc.h>

#include <bits/crt/format-printer.h>
#include <bits/types.h>

#ifdef GUARD_LIBICONV_API_H
#define LIBICONV_EXPOSE_INTERNAL
#endif /* GUARD_LIBICONV_API_H */


#ifdef LIBICONV_EXPOSE_INTERNAL
#include <bits/crt/mbstate.h>
#endif /* LIBICONV_EXPOSE_INTERNAL */

__DECL_BEGIN

#define _ICONV_DECODE_OPAQUE_POINTERS 5
#define _ICONV_ENCODE_OPAQUE_POINTERS 5


#ifdef LIBICONV_EXPOSE_INTERNAL
struct iconv_codepage;
union iconv_decode_data {
	struct {
		byte_t           u_pbc;   /* # of pending bytes in `u_pb' */
		byte_t           u_pb[3]; /* Pending byte(s). */
		struct __mbstate u_16;    /* Surrogate storage for utf-16 input. */
	} idd_utf; /* For UTF-16 and UTF-32 input data. */

	struct iconv_codepage const *idd_cp; /* [1..1][const] Code page */
	void *__idd_pad[_ICONV_DECODE_OPAQUE_POINTERS];
};

union iconv_encode_data {
	struct __mbstate ied_utf8; /* UTF-8 input data buffer. */
	struct {
		struct __mbstate             ic_utf8; /* UTF-8 input data buffer. */
		struct iconv_codepage const *ic_cp;   /* [1..1][const] Code page */
	} ied_cp;
	void *__ied_pad[_ICONV_ENCODE_OPAQUE_POINTERS];
};
#endif /* LIBICONV_EXPOSE_INTERNAL */


/*
 * ICONV: Using this API, you can make use of KOS's pformatprinter APIs to
 *        construct  transparent descriptors for  converting text from one
 *        codec to another.
 *        For this purpose, all functions either convert to, or from UTF-8,
 *        since that's the default encoding used by the KOS kernel, and all
 *        KOS system interfaces in general.
 *        However, you can easily connect an iconv_decode to  iconv_encode
 *        in order to convert from any codec to UTF-8, and directly follow
 *        up by converting to some other codec.
 *
 * Usage (decode; aka CODEC -> UTF-8):
 * >> struct iconv_decode decode;
 * >> struct iconv_printer input;
 * >> iconv_decode_init(&decode, &input, "cp437", &file_printer, stdout);
 * >> format_printf(input.ii_printer, input.ii_arg,
 * >>               "\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n"
 * >>               "\xBA This is cp437 text \xBA\n"
 * >>               "\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n"
 * >>               );
 *
 *
 * Usage (encode; aka UTF-8 -> CODEC):
 * >> char buf[512];
 * >> struct format_snprintf_data cp437_printer;
 * >> format_snprintf_init(&cp437_printer, buf, sizeof(buf));
 * >>
 * >> struct iconv_printer input;
 * >> struct iconv_encode encode;
 * >> iconv_encode_init(&encode, &input, "cp437", &format_snprintf_printer, &cp437_printer);
 * >> format_printf(input.ii_printer, input.ii_arg,
 * >>               "\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n"
 * >>               "\u2551 This is Unicode text \u2551\n"
 * >>               "\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n"
 * >>               );
 * >>
 * >> size_t len = (size_t)(cp437_printer.sd_buffer - buf);
 * >> printf("Encoded into %" PRIuSIZ " bytes\n", len);
 * >> printf("%$[hex]\n", len, buf);
 */



/* ICONV decode/encode flags. */
#define ICONV_ERRMASK       0x0000000f /* Mask for error code. */
#define ICONV_ERR_ERRNO              0 /* Set `errno=EILSEQ'  and have  the pformatprinter-compatible  function
                                        * return  `-1', thus signaling that an error happened. This will happen
                                        * forever until the iconv_encode/iconv_decode object is re-initialized. */
#define ICONV_ERR_REPLACE            1 /* Replace characters that cannot be encoded/decoded with ascii  '?'
                                        * If that character also doesn't exist in the target codec (this is
                                        * only  the case  for `iconv_encode'),  then use  some other codec-
                                        * specific replacement character. */
#define ICONV_ERR_IGNORE             2 /* Forward data that cannot be encoded/decoded as-is, but note that
                                        * doing this will most definitely result in data corruption as the
                                        * result will be encoded data mixed with data that's not encoded. */
#define ICONV_ERR_DISCARD            3 /* Data that cannot be encoded/decoded is silently discarded. */
#define ICONV_ERR_TRANSLIT  0x00000010 /* FLAG: Try to perform transliteration (s.a. `unicode_fold(3)') when
                                        *       a unicode character cannot be encoded in the target codec.
                                        *       If successful, characters will be replaced by one or more
                                        *       similar-looking characters that can (hopefully) be encoded. */
#define ICONV_HASERR        0x00000020 /* Used for `ICONV_ERR_ERRNO': keep setting EILSEQ and returning -1. */
/* NOTE: Other flags may have arbitrary meaning depending on the codec used. */


struct iconv_printer {
	__pformatprinter ii_printer; /* [1..1] Printer. */
	void            *ii_arg;     /* [?..1] Printer cookie. */
};

/************************************************************************/
/* ICONV Decode  (aka. <Some-Codec> --> UTF-8)                          */
/************************************************************************/
struct iconv_decode {
	/* Convert from an arbitrary codec to UTF-8 */
	struct iconv_printer    icd_output; /* [1..1][in][const] Output printer. */
	__uintptr_t             icd_flags;  /* [const] Error mode and flags. */
#ifdef LIBICONV_EXPOSE_INTERNAL
	union iconv_decode_data icd_data;   /* Internal data. */
#else /* LIBICONV_EXPOSE_INTERNAL */
	void                 *__icd_opaque[_ICONV_DECODE_OPAQUE_POINTERS]; /* [?..?] Codec-specific data fields. */
#endif /* !LIBICONV_EXPOSE_INTERNAL */
};


/* Initialize the given iconv decoder for the purpose of
 * converting  data from an  arbitrary codec into UTF-8.
 * @param: self:             [in|out] iconv decode controller.
 * @param: input_codec_name: [in]  The name of the codec in which input data will be presented.
 * @param: input:            [out] Location where to write callback+cookie for data input.
 *                                 The written function+cookie may only be used for as long
 *                                 as `self' remains valid.
 * @return: 0 : Success (you may now use `input->ii_printer' and `input->ii_arg' to feed data)
 * @return: -1: [errno=ENOENT] Unsupported/unknown codec `input_codec_name' */
typedef __ATTR_NONNULL((1, 2, 3)) int
/*__NOTHROW_NCX*/ (LIBICONV_CC *_LPICONV_DECODE_INIT)(/*in|out*/ struct iconv_decode *__restrict self,
                                                      /*out*/ struct iconv_printer *__restrict input, /* Accepts `input_codec_name' */
                                                      /*in*/ char const *__restrict input_codec_name);
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(LIBICONV_CC _iconv_decode_init)(/*in|out*/ struct iconv_decode *__restrict self,
                                              /*out*/ struct iconv_printer *__restrict input, /* Accepts `input_codec_name' */
                                              /*in*/ char const *__restrict input_codec_name);
__FORCELOCAL __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(iconv_decode_init)(/*in|out*/ struct iconv_decode *__restrict self,
                                 /*out*/ struct iconv_printer *__restrict input, /* Accepts `input_codec_name' */
                                 /*in*/ char const *__restrict input_codec_name,
                                 __pformatprinter output_printer, /* Accepting `UTF-8' */
                                 void *output_printer_arg,
                                 int error_mode __DFL(ICONV_ERR_ERRNO)) {
	self->icd_output.ii_printer = output_printer;
	self->icd_output.ii_arg     = output_printer_arg;
	self->icd_flags             = (__uintptr_t)(unsigned int)error_mode;
	return _iconv_decode_init(self, input, input_codec_name);
}
#endif /* LIBICONV_WANT_PROTOTYPES */
/************************************************************************/







/************************************************************************/
/* ICONV Encode  (aka. UTF-8 --> <Some-Codec>)                          */
/************************************************************************/
struct iconv_encode {
	/* Convert from UTF-8 to an arbitrary codec */
	struct iconv_printer    ice_output; /* [1..1][in][const] Output printer. */
	__uintptr_t             ice_flags;  /* [const] Error mode and flags. */
#ifdef LIBICONV_EXPOSE_INTERNAL
	union iconv_encode_data ice_data;   /* Internal data. */
#else /* LIBICONV_EXPOSE_INTERNAL */
	void                 *__ice_opaque[_ICONV_ENCODE_OPAQUE_POINTERS]; /* [?..?] Codec-specific data fields. */
#endif /* !LIBICONV_EXPOSE_INTERNAL */
};


/* Initialize the given iconv encoder for the purpose of
 * converting  data from an  arbitrary codec into UTF-8.
 * @param: self:              [in|out] iconv encode controller.
 * @param: output_codec_name: [in]  The name of the codec in which output data will be printed.
 * @param: input:             [out] Location where to write callback+cookie for data input.
 *                                  The written function+cookie may only be used for as long
 *                                  as `self' remains valid.
 * @return: 0 : Success (you may now use `input->ii_printer' and `input->ii_arg' to feed data)
 * @return: -1: [errno=ENOENT] Unsupported/unknown codec `output_codec_name' */
typedef __ATTR_NONNULL((1, 2, 3)) int
/*__NOTHROW_NCX*/ (LIBICONV_CC *_LPICONV_ENCODE_INIT)(/*in|out*/ struct iconv_encode *__restrict self,
                                                      /*out*/ struct iconv_printer *__restrict input, /* Accepts `UTF-8' */
                                                      /*in*/ char const *__restrict output_codec_name);
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(LIBICONV_CC _iconv_encode_init)(/*in|out*/ struct iconv_encode *__restrict self,
                                              /*out*/ struct iconv_printer *__restrict input, /* Accepts `UTF-8' */
                                              /*in*/ char const *__restrict output_codec_name);
__FORCELOCAL __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(iconv_encode_init)(/*in|out*/ struct iconv_encode *__restrict self,
                                 /*out*/ struct iconv_printer *__restrict input, /* Accepts `UTF-8' */
                                 /*in*/ char const *__restrict output_codec_name,
                                 __pformatprinter output_printer, /* Accepting `output_codec_name' */
                                 void *output_printer_arg,
                                 int error_mode __DFL(ICONV_ERR_ERRNO)) {
	self->ice_output.ii_printer = output_printer;
	self->ice_output.ii_arg     = output_printer_arg;
	self->ice_flags             = (__uintptr_t)(unsigned int)error_mode;
	return _iconv_encode_init(self, input, output_codec_name);
}
#endif /* LIBICONV_WANT_PROTOTYPES */
/************************************************************************/







/************************************************************************/
/* ICONV Transcode  (aka. <Some-Codec> --> <Some-Codec>)                */
/************************************************************************/
struct iconv_transcode {
	struct iconv_decode it_decode; /* Decoder */
	struct iconv_encode it_encode; /* Encoder */
};

/* The combination of the encode+decode functions into a single one which
 * allows for conversion from an arbitrary codec into another arbitrary codec.
 * This is pretty much just a convenience wrapper around the other 2 functions,
 * and you can easily tell as much if you were to look at this one's impl.
 * @param: self:              [in|out] iconv encode/decode controller.
 * @param: input_codec_name:  [in]  The name of the codec in which input data will be presented.
 * @param: output_codec_name: [in]  The name of the codec in which output data will be printed.
 * @param: input:             [out] Location where to write callback+cookie for data input.
 *                                  The written function+cookie may only be used for as long
 *                                  as `self' remains valid.
 * @return: 0 : Success (you may now use `input->ii_printer' and `input->ii_arg' to feed data)
 * @return: -1: [errno=ENOENT] Unsupported/unknown codec `input_codec_name' or `output_codec_name' */
typedef __ATTR_NONNULL((1, 2, 3, 4)) int
/*__NOTHROW_NCX*/ (LIBICONV_CC *_LPICONV_TRANSCODE_INIT)(/*in|out*/ struct iconv_transcode *__restrict self,
                                                         /*out*/ struct iconv_printer *__restrict input,   /* Accepts `input_codec_name' */
                                                         /*in*/ char const *__restrict input_codec_name,   /* For decode */
                                                         /*in*/ char const *__restrict output_codec_name); /* For encode */
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_NONNULL((1, 2, 3, 4)) int
__NOTHROW_NCX(LIBICONV_CC _iconv_transcode_init)(/*in|out*/ struct iconv_transcode *__restrict self,
                                                 /*out*/ struct iconv_printer *__restrict input,   /* Accepts `input_codec_name' */
                                                 /*in*/ char const *__restrict input_codec_name,   /* For decode */
                                                 /*in*/ char const *__restrict output_codec_name); /* For encode */
__FORCELOCAL __ATTR_NONNULL((1, 2, 3, 4)) int
__NOTHROW_NCX(iconv_transcode_init)(/*in|out*/ struct iconv_transcode *__restrict self,
                                    /*out*/ struct iconv_printer *__restrict input,  /* Accepts `input_codec_name' */
                                    /*in*/ char const *__restrict input_codec_name,  /* For decode */
                                    /*in*/ char const *__restrict output_codec_name, /* For encode */
                                    __pformatprinter output_printer,                 /* Accepting `output_codec_name' */
                                    void *output_printer_arg,
                                    int error_mode __DFL(ICONV_ERR_ERRNO)) {
	self->it_encode.ice_output.ii_printer = output_printer;
	self->it_encode.ice_output.ii_arg     = output_printer_arg;
	self->it_encode.ice_flags             = (__uintptr_t)(unsigned int)error_mode;
	return _iconv_transcode_init(self, input, input_codec_name, output_codec_name);
}
#endif /* LIBICONV_WANT_PROTOTYPES */
/************************************************************************/






__DECL_END

#endif /* !_LIBICONV_WRITER_H */
