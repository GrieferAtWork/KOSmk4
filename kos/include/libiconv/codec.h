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
#ifndef _LIBICONV_CODEC_H
#define _LIBICONV_CODEC_H 1

#include "api.h"
/**/

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

typedef __UINTPTR_HALF_TYPE__ iconv_codec_t;
#define ICONV_CODEC_UNKNOWN 0 /* Unknown/unsupported codec. */
#define ICONV_CODEC_FIRST   1 /* First valid codec. Which codec this references is  implementation-defined.
                               * Actual codec IDs are internal and the actual codecs may only be referenced
                               * by (one of) their names.
                               * To learn about supported codecs (and their names),
                               * take a  look at:  `/kos/src/libiconv/iconvdata/db' */


/* Return the internal ID of the codec associated with `name'
 * Casing   is  ignored  and  codec  aliases  are  respected.
 * @return: * :                  Internal codec ID (s.a. `iconv_getcodecname()')
 * @return: ICONV_CODEC_UNKNOWN: Unrecognized codec. */
typedef __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) iconv_codec_t
/*__NOTHROW_NCX*/ (LIBICONV_CC *LPICONV_CODECBYNAME)(char const *__restrict name);
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) iconv_codec_t
__NOTHROW_NCX(LIBICONV_CC iconv_codecbyname)(char const *__restrict name);
#endif /* LIBICONV_WANT_PROTOTYPES */

/* Return the nth (0-based) lexicographically sorted name for the codec `id'
 * When `id'  is  invalid or  doesn't  have  an `nth'  name,  return  `NULL'
 * Note  that all valid codecs have at least 1 (iow: `nth=0') valid name. As
 * such,  supported  codecs as  well as  their names  can be  enumerated as:
 * >> iconv_codec_t id;
 * >> for (id = ICONV_CODEC_FIRST;;) {
 * >>     unsigned int nth = 0;
 * >>     char const *name;
 * >>     for (nth = 0; (name = iconv_getcodecname(id, nth)) != NULL; ++nth) {
 * >>         if (nth != 0)
 * >>             putc('\t');
 * >>         printf("%s", name);
 * >>     }
 * >>     putc('\n');
 * >>     if (nth == 0)
 * >>         break;
 * >> } */
typedef __ATTR_CONST __ATTR_WUNUSED char const *
/*__NOTHROW_NCX*/ (LIBICONV_CC *LPICONV_GETCODECNAME)(iconv_codec_t id, unsigned int nth);
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW_NCX(LIBICONV_CC iconv_getcodecname)(iconv_codec_t id, unsigned int nth);
#endif /* LIBICONV_WANT_PROTOTYPES */


/* Same as `iconv_codecbyname()', but  also parse possible flag-relation  options.
 * The given `*pflags' argument must already  be populated with valid data  before
 * this function is called, and should usually point to `icd_flags' or `ice_flags' */
typedef __ATTR_WUNUSED __ATTR_NONNULL((1)) iconv_codec_t
/*__NOTHROW_NCX*/ (LIBICONV_CC *LPICONV_CODEC_AND_FLAGS_BYNAME)(char const *__restrict name,
                                                                /*[in|out]*/ __UINTPTR_HALF_TYPE__ *__restrict pflags);
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) iconv_codec_t
__NOTHROW_NCX(LIBICONV_CC iconv_codec_and_flags_byname)(char const *__restrict name,
                                                        /*[in|out]*/ __UINTPTR_HALF_TYPE__ *__restrict pflags);
#endif /* LIBICONV_WANT_PROTOTYPES */

/* Check  if  the 2  given strings  reference  the same  codec name.
 * This differs from same codec ID as this function doesn't actually
 * search the codec database but will simply strip potential  flags,
 * normalize the underlying codec names, and check if the  resulting
 * strings strcasecmp(3) to be equal. */
typedef __ATTR_CONST __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) bool
/*__NOTHROW_NCX*/ (LIBICONV_CC *LPICONV_SAME_CODEC_NAME)(char const *__restrict a,
                                                         char const *__restrict b);
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_CONST __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) bool
__NOTHROW_NCX(LIBICONV_CC iconv_same_codec_name)(char const *__restrict a,
                                                 char const *__restrict b);
#endif /* LIBICONV_WANT_PROTOTYPES */



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
typedef __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) iconv_codec_t
/*__NOTHROW_NCX*/ (LIBICONV_CC *LPICONV_DETECT_CODEC)(void const *__restrict data, size_t size);
#ifdef LIBICONV_WANT_PROTOTYPES
LIBICONV_DECL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) iconv_codec_t
__NOTHROW_NCX(LIBICONV_CC iconv_detect_codec)(void const *__restrict data, size_t size);
#endif /* LIBICONV_WANT_PROTOTYPES */



__DECL_END
#endif /* __CC__ */

#endif /* !_LIBICONV_CODEC_H */
