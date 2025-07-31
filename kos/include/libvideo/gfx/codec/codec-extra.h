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
#ifndef _LIBVIDEO_GFX_CODEC_CODEC_EXTRA_H
#define _LIBVIDEO_GFX_CODEC_CODEC_EXTRA_H 1

#include "../api.h"
/**/

/************************************************************************/
/* "Extra" video codecs                                                 */
/************************************************************************/


/* Video mode used by 16-bit  VBE video modes. You'd  think they'd have just  used
 * `VIDEO_CODEC_P4_MSB' for this one, but ///nOoOoOoO/// it had to be more similar
 * to what happens in 16-color  planar mode (which is actually  VIDEO_CODEC_P1_MSB
 * repeated 4 times across different "planes").
 *
 * 4-bit-per-pixel, 8-pixels-per-byte, 4-byte-repeating:
 * >> Byte:      B0......B1......B2......B3...... B4......B5......B6......B7......
 * >> Pixel:     ABCDEFGHABCDEFGHABCDEFGHABCDEFGH IJKLMNOPIJKLMNOPIJKLMNOPIJKLMNOP
 * >> Pixel-Bit: 00000000111111112222222233333333 00000000111111112222222233333333
 *
 * iow: to set pixel "C" as "v" (where "v in [0,15]"), you have to do:
 * >> B0 = (B0 & 0xdf) | (((v >> 0) & 1) << 5); // Bit#0
 * >> B1 = (B1 & 0xdf) | (((v >> 1) & 1) << 5); // Bit#1
 * >> B2 = (B2 & 0xdf) | (((v >> 2) & 1) << 5); // Bit#2
 * >> B3 = (B3 & 0xdf) | (((v >> 3) & 1) << 5); // Bit#3 */
#define VIDEO_CODEC_X_VBE16  0x3001

/* Tile-based video codec, where each "pixel" is actually a descriptor for a tile:
 * >> TTTTTTTTBBBBFFFF
 * T: Tile index        (== R)
 * B: Background color  (== G)
 * F: Foreground color  (== B)
 *
 * When it comes to pixel<=>color conversion, we encode TBG as RGB
 *
 * As such, this format could also be called "RGB844" */
#define VIDEO_CODEC_X_TILE16 0x3002

/* TODO: 4-bit-per-pixel, 8-pixels-per-byte, planar */


#endif /* !_LIBVIDEO_GFX_CODEC_CODEC_EXTRA_H */
