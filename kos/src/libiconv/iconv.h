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
#ifndef GUARD_LIBICONV_ICONV_H
#define GUARD_LIBICONV_ICONV_H 1

#include "api.h"
/**/

#include <kos/types.h>

#include <format-printer.h>

#include <libiconv/iconv.h>

DECL_BEGIN

/* Initialize the given iconv decoder for the purpose of
 * converting  data from an  arbitrary codec into UTF-8.
 * @param: self:             [in|out] iconv decode controller.
 * @param: input_codec_name: [in]  The name of the codec in which input data will be presented.
 * @param: input:            [out] Location where to write callback+cookie for data input.
 *                                 The written function+cookie may only be used for as long
 *                                 as `self' remains valid.
 * @return: 0 : Success (you may now use `input->ii_printer' and `input->ii_arg' to feed data)
 * @return: -1: [errno=EINVAL] Unsupported/unknown codec `input_codec_name' */
INTDEF NONNULL((1, 2, 3)) int
NOTHROW_NCX(CC _libiconv_decode_init)(/*in|out*/ struct iconv_decode *__restrict self,
                                      /*out*/ struct iconv_printer *__restrict input, /* Accepts `input_codec_name' */
                                      /*in*/ char const *__restrict input_codec_name);



/* Initialize the given iconv encoder for the purpose of
 * converting  data from an  arbitrary codec into UTF-8.
 * @param: self:              [in|out] iconv encode controller.
 * @param: output_codec_name: [in]  The name of the codec in which output data will be printed.
 * @param: input:             [out] Location where to write callback+cookie for data input.
 *                                  The written function+cookie may only be used for as long
 *                                  as `self' remains valid.
 * @return: 0 : Success (you may now use `input->ii_printer' and `input->ii_arg' to feed data)
 * @return: -1: [errno=EINVAL] Unsupported/unknown codec `output_codec_name' */
INTDEF NONNULL((1, 2, 3)) int
NOTHROW_NCX(CC _libiconv_encode_init)(/*in|out*/ struct iconv_encode *__restrict self,
                                      /*out*/ struct iconv_printer *__restrict input, /* Accepts `UTF-8' */
                                      /*in*/ char const *__restrict output_codec_name);



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
 * @return: -1: [errno=EINVAL] Unsupported/unknown codec `input_codec_name' or `output_codec_name' */
INTDEF NONNULL((1, 2, 3, 4)) int
NOTHROW_NCX(CC _libiconv_transcode_init)(/*in|out*/ struct iconv_transcode *__restrict self,
                                         /*out*/ struct iconv_printer *__restrict input,   /* Accepts `input_codec_name' */
                                         /*in*/ char const *__restrict input_codec_name,   /* For decode */
                                         /*in*/ char const *__restrict output_codec_name); /* For encode */


INTDEF NONNULL((1, 2)) int
NOTHROW_NCX(CC libiconv_decode_init)(/*in|out*/ struct iconv_decode *__restrict self,
                                     /*out*/ struct iconv_printer *__restrict input, /* Accepts `input_codec_name' */
                                     /*in*/ unsigned int input_codec);
INTDEF NONNULL((1, 2)) int
NOTHROW_NCX(CC libiconv_encode_init)(/*in|out*/ struct iconv_encode *__restrict self,
                                     /*out*/ struct iconv_printer *__restrict input, /* Accepts `UTF-8' */
                                     /*in*/ unsigned int output_codec);

DECL_END

#endif /* !GUARD_LIBICONV_ICONV_H */
