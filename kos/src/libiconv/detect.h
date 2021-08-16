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
#ifndef GUARD_LIBICONV_DETECT_H
#define GUARD_LIBICONV_DETECT_H 1

#include "api.h"
/**/

#include <kos/types.h>

#include <stdbool.h>

#include <libiconv/codec.h>
#include <libiconv/iconv.h>

DECL_BEGIN

/* Try to automatically detect the codec of the given data-blob, which should
 * represent the memory-mapping of a text-file. This function will then try to
 * inspect its beginning for comment-style indicators which might inform about
 * which codec the file uses (e.g. xml, python, etc.), as well as analysis of
 * NUL-bytes for multi-byte codecs.
 *
 * In case of a single-byte codec, go through all bytes that appear in the file
 * and count which of them occur how often before narrowing down candidates by
 * excluding any where decoding would result in non-printable characters other
 * than those needed for text (e.g. line-feeds, spaces, and unicode prefixes).
 *
 * Once the set of codecs capable of decoding the file into something that looks
 * like text is determined, use each of them to try and decode the text to UTF-8
 * and count how often each bytes occurs within the UTF-8 stream. The results of
 * this are then fuzzy-compared against a known-good heuristic of byte usage in
 * normal text, and the codec which is closest to this heuristic is used.
 *
 * If the function is unable to determine the codec to-be used, it will return
 * with `ICONV_CODEC_UNKNOWN'. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) iconv_codec_t
NOTHROW_NCX(CC libiconv_detect_codec)(void const *__restrict data, size_t size);


DECL_END

#endif /* !GUARD_LIBICONV_DETECT_H */
