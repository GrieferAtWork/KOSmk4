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
#include <stdbool.h>

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
INTDEF ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW_NCX(CC libiconv_decode_isshiftzero)(struct iconv_decode const *__restrict self);


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

/* Reset the internal shift state to its  default and print the associated byte  sequence
 * to the output printer of the encode descriptor, returning the sum of its return values
 * or the first negative return value.
 * This  function should be  called once all input  data has been  printed and will ensure
 * that input didn't end with an incomplete byte sequence, and that output doesn't contain
 * any unmatched shift-state changes.
 * Simply  call this once you're out of input  and treat its return value like you're
 * treating the return values of the input printer returned by `iconv_encode_init(3)' */
INTDEF NONNULL((1)) ssize_t
NOTHROW_NCX(CC libiconv_encode_flush)(struct iconv_encode *__restrict self);



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



/************************************************************************/
/* Internal functions                                                   */
/************************************************************************/
INTDEF NONNULL((1, 2)) int
NOTHROW_NCX(CC libiconv_decode_init)(/*in|out*/ struct iconv_decode *__restrict self,
                                     /*out*/ struct iconv_printer *__restrict input);
INTDEF NONNULL((1, 2)) int
NOTHROW_NCX(CC libiconv_encode_init)(/*in|out*/ struct iconv_encode *__restrict self,
                                     /*out*/ struct iconv_printer *__restrict input);


DECL_END

#endif /* !GUARD_LIBICONV_ICONV_H */
