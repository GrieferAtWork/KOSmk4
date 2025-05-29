/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVIDEO_CODEC_CODECS_H
#define GUARD_LIBVIDEO_CODEC_CODECS_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/__byteswap.h>
#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#include <kos/types.h>

#include <libvideo/codec/codecs.h>

DECL_BEGIN

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define MASK4(x) __UINT32_C(x)
#define MASK3(x) __UINT32_C(x)
#define MASK2(x) __UINT16_C(x)
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define MASK4(x) __hybrid_bswap32_c(__UINT32_C(x))
#define MASK3(x) (__hybrid_bswap32_c(__UINT32_C(x)) >> 8)
#define MASK2(x) __hybrid_bswap16_c(__UINT16_C(x))
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */


/* Lookup the interface for a given codec, or return NULL if the codec isn't supported. */
INTDEF ATTR_CONST WUNUSED struct video_codec const *CC
libvideo_codec_lookup(video_codec_t codec);

DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_CODECS_H */
