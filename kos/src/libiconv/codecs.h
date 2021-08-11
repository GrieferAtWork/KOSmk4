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
#ifndef GUARD_LIBICONV_CODECS_H
#define GUARD_LIBICONV_CODECS_H 1

#include "api.h"
/**/

#include <hybrid/byteorder.h>

#include <kos/types.h>

#include <libiconv/iconv.h>

DECL_BEGIN

/* Codec IDs. */
enum {
	CODEC_UNKNOWN, /* Invalid codec */
/*[[[begin:codecs]]]*/
	CODEC_ASCII,   /* "ISO-IR-006", "ANSI_X3.4-1968", "ANSI_X3.4-1986", "ISO_646.irv:1991", "ISO646-US", "us", "IBM367", "cp367", "us-ascii" */
	CODEC_UTF8,    /* "UTF8", "UTF-8" */
	CODEC_UTF16LE, /* "UTF16LE", "UTF-16LE" */
	CODEC_UTF16BE, /* "UTF16BE", "UTF-16BE" */
	CODEC_UTF32LE, /* "UTF32LE", "UTF-32LE" */
	CODEC_UTF32BE, /* "UTF32BE", "UTF-32BE" */
	CODEC_CP437,   /* "IBM437", "cp437", "437", "csPC8CodePage437", "OEM-US", "OSF100201B5" */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	CODEC_UTF16 = CODEC_UTF16LE, /* "UTF16", "UTF-16" */
	CODEC_UTF32 = CODEC_UTF32LE, /* "UTF32", "UTF-32" */
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
/*[[[end:codecs]]]*/

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
	CODEC_UTF16 = CODEC_UTF16BE,
	CODEC_UTF32 = CODEC_UTF32BE,
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
};

/* Return the ID of the codec associated with `name'
 * Casing is ignored and codec aliases are respected. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(FCALL libiconv_codecbyname)(char const *__restrict name);

/* Return the nth (0-based) alphabetically sorted name for the codec `id'
 * When `id' is invalid or doesn't have an `nth' name, return `NULL' */
INTDEF ATTR_CONST WUNUSED char const *
NOTHROW_NCX(FCALL libiconv_getcodecname)(unsigned int id, unsigned int nth);



DECL_END

#endif /* !GUARD_LIBICONV_CODECS_H */
