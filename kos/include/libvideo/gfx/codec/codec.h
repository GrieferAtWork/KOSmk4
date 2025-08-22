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
#ifndef _LIBVIDEO_GFX_CODEC_CODEC_H
#define _LIBVIDEO_GFX_CODEC_CODEC_H 1

#include "../api.h"
/**/

#include <__stdinc.h>

#include <hybrid/__atomic.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>
#include <hybrid/byteorder.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/refcnt.h>

#include "../../color.h"
#include "../../types.h"

#define VIDEO_CODEC_NONE   0x0000 /* Invalid codec. */
#define VIDEO_CODEC_USER   0xfffe /* User-defined codec (use this when defining+implementing your own `struct video_codec') */
#define VIDEO_CODEC_CUSTOM 0xffff /* Custom codec (not one of the built-in ones) */

/* Notation:
 * >> VIDEO_CODEC_{CHANNELS}{CHANNEL_BITS}{SUFFIX}
 *
 * CHANNELS:
 * - Color/data channels used by the codec, written in order:
 *   >> byte ASC, bit DESC
 *   iow: channels that appear in bytes at lower memory addresses
 *        are listed first, and channels that appear in the  same
 *        byte  are  listed from  most-to-least  significant bit.
 *        e.g. `VIDEO_CODEC_RGB332' uses: r:0xe0, g:0x1c,  b:0x03
 * - P: Palette index
 * - L: Luminance / brightness (0: black; 1: white)
 * - R: Red color component/intensity   (direct color codecs only)
 * - G: Green color component/intensity (direct color codecs only)
 * - B: Blue color component/intensity  (direct color codecs only)
 * - A: Alpha component/intensity
 * - X: Ignored/unused
 *
 * CHANNEL_BITS:
 * - # of bits used by this channel. The starting bit of any
 *   channel is the # of  bits from all preceding  channels.
 * - The sum of these values always adds up to a multiple of 8,
 *   or  will be equal to 1, 2 or 4 (in these last 3 cases, the
 *   codec stores multiple pixels per byte)
 *
 * SUFFIX:
 * - Only relevant when a single byte can hold more than 1 pixel,
 *   in which case "_MSB" means that the first pixel is stored at
 *   greater bits than pixels that follow thereafter.
 * - "_LSB" means the opposite, meaning the bit=0 belongs to the
 *   first pixel (as opposed to the last)
 */

/* Full-color */
#define VIDEO_CODEC_RGBA8888 0x0001 /* { 0xRR, 0xGG, 0xBB, 0xAA } (Hint: in this codec, "video_pixel_t" and "video_color_t" are identical) */
#define VIDEO_CODEC_RGBX8888 0x0002 /* { 0xRR, 0xGG, 0xBB, 0x__ } */
#define VIDEO_CODEC_ARGB8888 0x0003 /* { 0xAA, 0xRR, 0xGG, 0xBB } */
#define VIDEO_CODEC_XRGB8888 0x0004 /* { 0x__, 0xRR, 0xGG, 0xBB } */
#define VIDEO_CODEC_ABGR8888 0x0005 /* { 0xAA, 0xBB, 0xGG, 0xRR } */
#define VIDEO_CODEC_XBGR8888 0x0006 /* { 0x__, 0xBB, 0xGG, 0xRR } */
#define VIDEO_CODEC_BGRA8888 0x0007 /* { 0xBB, 0xGG, 0xRR, 0xAA } */
#define VIDEO_CODEC_BGRX8888 0x0008 /* { 0xBB, 0xGG, 0xRR, 0x__ } */
#define VIDEO_CODEC_RGB888   0x0009 /* { 0xRR, 0xGG, 0xBB } */
#define VIDEO_CODEC_BGR888   0x000a /* { 0xBB, 0xGG, 0xRR } */
#define VIDEO_CODEC_RGBA4444 0x0011 /* { 0bRRRRGGGG, 0bBBBBAAAA } */
#define VIDEO_CODEC_RGBX4444 0x0012 /* { 0bRRRRGGGG, 0bBBBB____ } */
#define VIDEO_CODEC_ARGB4444 0x0013 /* { 0bAAAARRRR, 0bGGGGBBBB } */
#define VIDEO_CODEC_XRGB4444 0x0014 /* { 0b____RRRR, 0bGGGGBBBB } */
#define VIDEO_CODEC_ABGR4444 0x0015 /* { 0bAAAABBBB, 0bGGGGRRRR } */
#define VIDEO_CODEC_XBGR4444 0x0016 /* { 0b____BBBB, 0bGGGGRRRR } */
#define VIDEO_CODEC_BGRA4444 0x0017 /* { 0bBBBBGGGG, 0bRRRRAAAA } */
#define VIDEO_CODEC_BGRX4444 0x0018 /* { 0bBBBBGGGG, 0bRRRR____ } */
#define VIDEO_CODEC_RGB565   0x0019 /* { 0bRRRRRGGG, 0bGGGBBBBB } */
#define VIDEO_CODEC_BGR565   0x001a /* { 0bBBBBBGGG, 0bGGGRRRRR } */
#define VIDEO_CODEC_RGBA5551 0x0021 /* { 0bRRRRRGGG, 0bGGBBBBBA } */
#define VIDEO_CODEC_RGBX5551 0x0022 /* { 0bRRRRRGGG, 0bGGBBBBB_ } */
#define VIDEO_CODEC_ARGB1555 0x0023 /* { 0bARRRRRGG, 0bGGGBBBBB } */
#define VIDEO_CODEC_XRGB1555 0x0024 /* { 0b_RRRRRGG, 0bGGGBBBBB } */
#define VIDEO_CODEC_ABGR1555 0x0025 /* { 0bABBBBBGG, 0bGGGRRRRR } */
#define VIDEO_CODEC_XBGR1555 0x0026 /* { 0b_BBBBBGG, 0bGGGRRRRR } */
#define VIDEO_CODEC_BGRA5551 0x0027 /* { 0bBBBBBGGG, 0bGGRRRRRA } */
#define VIDEO_CODEC_BGRX5551 0x0028 /* { 0bBBBBBGGG, 0bGGRRRRR_ } */
#define VIDEO_CODEC_RGB332   0x0029 /* 0bRRRGGGBB  [r: 0xe0, g: 0x1c, b: 0x03] */
#define VIDEO_CODEC_RGB323   0x002a /* 0bRRRGGBBB  [r: 0xe0, g: 0x18, b: 0x07] */
#define VIDEO_CODEC_RGB233   0x002b /* 0bRRGGGBBB  [r: 0xc0, g: 0x38, b: 0x07] */
#define VIDEO_CODEC_BGR332   0x002c /* 0bBBBGGGRR  [r: 0x03, g: 0x1c, b: 0xe0] */
#define VIDEO_CODEC_BGR323   0x002d /* 0bBBBGGRRR  [r: 0x07, g: 0x18, b: 0xe0] */
#define VIDEO_CODEC_BGR233   0x002e /* 0bBBGGGRRR  [r: 0x07, g: 0x38, b: 0xc0] */
#define VIDEO_CODEC_RGBA2222 0x0030 /* 0bRRGGBBAA  [r: 0xc0, g: 0x30, b: 0x0c, a: 0x03] */
#define VIDEO_CODEC_RGBX2222 0x0031 /* 0bRRGGBB__  [r: 0xc0, g: 0x30, b: 0x0c] */
#define VIDEO_CODEC_ARGB2222 0x0032 /* 0bAARRGGBB  [r: 0x30, g: 0x0c, b: 0x03, a: 0xc0] */
#define VIDEO_CODEC_XRGB2222 0x0033 /* 0b__RRGGBB  [r: 0x30, g: 0x0c, b: 0x03] */
#define VIDEO_CODEC_BGRA2222 0x0034 /* 0bBBGGRRAA  [r: 0x0c, g: 0x30, b: 0xc0, a: 0x03] */
#define VIDEO_CODEC_BGRX2222 0x0035 /* 0bBBGGRR__  [r: 0x0c, g: 0x30, b: 0xc0] */
#define VIDEO_CODEC_ABGR2222 0x0036 /* 0bAABBGGRR  [r: 0x03, g: 0x0c, b: 0x30, a: 0xc0] */
#define VIDEO_CODEC_XBGR2222 0x0037 /* 0b__BBGGRR  [r: 0x03, g: 0x0c, b: 0x30] */

/* 32bpp HDR codecs */
#define VIDEO_CODEC_RGBA1010102 0x0038 /* { 0bRRRRRRRR, 0bRRGGGGGG, 0bGGGGBBBB, 0bBBBBBBAA } */
#define VIDEO_CODEC_RGBX1010102 0x0039 /* { 0bRRRRRRRR, 0bRRGGGGGG, 0bGGGGBBBB, 0bBBBBBB__ } */
#define VIDEO_CODEC_ARGB2101010 0x003a /* { 0bAARRRRRR, 0bRRRRGGGG, 0bGGGGGGBB, 0bBBBBBBBB } */
#define VIDEO_CODEC_XRGB2101010 0x003b /* { 0b__RRRRRR, 0bRRRRGGGG, 0bGGGGGGBB, 0bBBBBBBBB } */
#define VIDEO_CODEC_BGRA1010102 0x003c /* { 0bBBBBBBBB, 0bBBGGGGGG, 0bGGGGRRRR, 0bRRRRRRAA } */
#define VIDEO_CODEC_BGRX1010102 0x003d /* { 0bBBBBBBBB, 0bBBGGGGGG, 0bGGGGRRRR, 0bRRRRRR__ } */
#define VIDEO_CODEC_ABGR2101010 0x003e /* { 0bAABBBBBB, 0bBBBBGGGG, 0bGGGGGGRR, 0bRRRRRRRR } */
#define VIDEO_CODEC_XBGR2101010 0x003f /* { 0b__BBBBBB, 0bBBBBGGGG, 0bGGGGGGRR, 0bRRRRRRRR } */
#define VIDEO_CODEC_RGB111110   0x0040 /* { 0bRRRRRRRR, 0bRRRGGGGG, 0bGGGGGGBB, 0bBBBBBBBB } */
#define VIDEO_CODEC_RGB111011   0x0041 /* { 0bRRRRRRRR, 0bRRRGGGGG, 0bGGGGGBBB, 0bBBBBBBBB } */
#define VIDEO_CODEC_RGB101111   0x0042 /* { 0bRRRRRRRR, 0bRRGGGGGG, 0bGGGGGBBB, 0bBBBBBBBB } */
#define VIDEO_CODEC_BGR111110   0x0043 /* { 0bBBBBBBBB, 0bBBBGGGGG, 0bGGGGGGRR, 0bRRRRRRRR } */
#define VIDEO_CODEC_BGR111011   0x0044 /* { 0bBBBBBBBB, 0bBBBGGGGG, 0bGGGGGRRR, 0bRRRRRRRR } */
#define VIDEO_CODEC_BGR101111   0x0045 /* { 0bBBBBBBBB, 0bBBGGGGGG, 0bGGGGGRRR, 0bRRRRRRRR } */

/* 64bpp direct color */
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
#define VIDEO_CODEC_RGBA16161616_LE 0x0046 /* { 0bRRRRRRRR, 0bRRRRRRRR, 0bGGGGGGGG, 0bGGGGGGGG, 0bBBBBBBBB, 0bBBBBBBBB, 0bAAAAAAAA, 0bAAAAAAAA } */
#define VIDEO_CODEC_RGBA16161616_BE 0x0047 /* { 0bRRRRRRRR, 0bRRRRRRRR, 0bGGGGGGGG, 0bGGGGGGGG, 0bBBBBBBBB, 0bBBBBBBBB, 0bAAAAAAAA, 0bAAAAAAAA } */
#define VIDEO_CODEC_RGBX16161616_LE 0x0048 /* { 0bRRRRRRRR, 0bRRRRRRRR, 0bGGGGGGGG, 0bGGGGGGGG, 0bBBBBBBBB, 0bBBBBBBBB, 0b________, 0b________ } */
#define VIDEO_CODEC_RGBX16161616_BE 0x0049 /* { 0bRRRRRRRR, 0bRRRRRRRR, 0bGGGGGGGG, 0bGGGGGGGG, 0bBBBBBBBB, 0bBBBBBBBB, 0b________, 0b________ } */
#define VIDEO_CODEC_ARGB16161616_LE 0x004a /* { 0bAAAAAAAA, 0bAAAAAAAA, 0bRRRRRRRR, 0bRRRRRRRR, 0bGGGGGGGG, 0bGGGGGGGG, 0bBBBBBBBB, 0bBBBBBBBB } */
#define VIDEO_CODEC_ARGB16161616_BE 0x004b /* { 0bAAAAAAAA, 0bAAAAAAAA, 0bRRRRRRRR, 0bRRRRRRRR, 0bGGGGGGGG, 0bGGGGGGGG, 0bBBBBBBBB, 0bBBBBBBBB } */
#define VIDEO_CODEC_XRGB16161616_LE 0x004c /* { 0b________, 0b________, 0bRRRRRRRR, 0bRRRRRRRR, 0bGGGGGGGG, 0bGGGGGGGG, 0bBBBBBBBB, 0bBBBBBBBB } */
#define VIDEO_CODEC_XRGB16161616_BE 0x004d /* { 0b________, 0b________, 0bRRRRRRRR, 0bRRRRRRRR, 0bGGGGGGGG, 0bGGGGGGGG, 0bBBBBBBBB, 0bBBBBBBBB } */
#define VIDEO_CODEC_BGRA16161616_LE 0x004e /* { 0bBBBBBBBB, 0bBBBBBBBB, 0bGGGGGGGG, 0bGGGGGGGG, 0bRRRRRRRR, 0bRRRRRRRR, 0bAAAAAAAA, 0bAAAAAAAA } */
#define VIDEO_CODEC_BGRA16161616_BE 0x004f /* { 0bBBBBBBBB, 0bBBBBBBBB, 0bGGGGGGGG, 0bGGGGGGGG, 0bRRRRRRRR, 0bRRRRRRRR, 0bAAAAAAAA, 0bAAAAAAAA } */
#define VIDEO_CODEC_BGRX16161616_LE 0x0050 /* { 0bBBBBBBBB, 0bBBBBBBBB, 0bGGGGGGGG, 0bGGGGGGGG, 0bRRRRRRRR, 0bRRRRRRRR, 0b________, 0b________ } */
#define VIDEO_CODEC_BGRX16161616_BE 0x0051 /* { 0bBBBBBBBB, 0bBBBBBBBB, 0bGGGGGGGG, 0bGGGGGGGG, 0bRRRRRRRR, 0bRRRRRRRR, 0b________, 0b________ } */
#define VIDEO_CODEC_ABGR16161616_LE 0x0052 /* { 0bAAAAAAAA, 0bAAAAAAAA, 0bBBBBBBBB, 0bBBBBBBBB, 0bGGGGGGGG, 0bGGGGGGGG, 0bRRRRRRRR, 0bRRRRRRRR } */
#define VIDEO_CODEC_ABGR16161616_BE 0x0053 /* { 0bAAAAAAAA, 0bAAAAAAAA, 0bBBBBBBBB, 0bBBBBBBBB, 0bGGGGGGGG, 0bGGGGGGGG, 0bRRRRRRRR, 0bRRRRRRRR } */
#define VIDEO_CODEC_XBGR16161616_LE 0x0054 /* { 0b________, 0b________, 0bBBBBBBBB, 0bBBBBBBBB, 0bGGGGGGGG, 0bGGGGGGGG, 0bRRRRRRRR, 0bRRRRRRRR } */
#define VIDEO_CODEC_XBGR16161616_BE 0x0055 /* { 0b________, 0b________, 0bBBBBBBBB, 0bBBBBBBBB, 0bGGGGGGGG, 0bGGGGGGGG, 0bRRRRRRRR, 0bRRRRRRRR } */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define VIDEO_CODEC_RGBA16161616       VIDEO_CODEC_RGBA16161616_BE
#define VIDEO_CODEC_RGBX16161616       VIDEO_CODEC_RGBX16161616_BE
#define VIDEO_CODEC_ARGB16161616       VIDEO_CODEC_ARGB16161616_BE
#define VIDEO_CODEC_XRGB16161616       VIDEO_CODEC_XRGB16161616_BE
#define VIDEO_CODEC_BGRA16161616       VIDEO_CODEC_BGRA16161616_BE
#define VIDEO_CODEC_BGRX16161616       VIDEO_CODEC_BGRX16161616_BE
#define VIDEO_CODEC_ABGR16161616       VIDEO_CODEC_ABGR16161616_BE
#define VIDEO_CODEC_XBGR16161616       VIDEO_CODEC_XBGR16161616_BE
#define VIDEO_CODEC_RGBA16161616_BSWAP VIDEO_CODEC_RGBA16161616_LE
#define VIDEO_CODEC_RGBX16161616_BSWAP VIDEO_CODEC_RGBX16161616_LE
#define VIDEO_CODEC_ARGB16161616_BSWAP VIDEO_CODEC_ARGB16161616_LE
#define VIDEO_CODEC_XRGB16161616_BSWAP VIDEO_CODEC_XRGB16161616_LE
#define VIDEO_CODEC_BGRA16161616_BSWAP VIDEO_CODEC_BGRA16161616_LE
#define VIDEO_CODEC_BGRX16161616_BSWAP VIDEO_CODEC_BGRX16161616_LE
#define VIDEO_CODEC_ABGR16161616_BSWAP VIDEO_CODEC_ABGR16161616_LE
#define VIDEO_CODEC_XBGR16161616_BSWAP VIDEO_CODEC_XBGR16161616_LE
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define VIDEO_CODEC_RGBA16161616       VIDEO_CODEC_RGBA16161616_LE
#define VIDEO_CODEC_RGBX16161616       VIDEO_CODEC_RGBX16161616_LE
#define VIDEO_CODEC_ARGB16161616       VIDEO_CODEC_ARGB16161616_LE
#define VIDEO_CODEC_XRGB16161616       VIDEO_CODEC_XRGB16161616_LE
#define VIDEO_CODEC_BGRA16161616       VIDEO_CODEC_BGRA16161616_LE
#define VIDEO_CODEC_BGRX16161616       VIDEO_CODEC_BGRX16161616_LE
#define VIDEO_CODEC_ABGR16161616       VIDEO_CODEC_ABGR16161616_LE
#define VIDEO_CODEC_XBGR16161616       VIDEO_CODEC_XBGR16161616_LE
#define VIDEO_CODEC_RGBA16161616_BSWAP VIDEO_CODEC_RGBA16161616_BE
#define VIDEO_CODEC_RGBX16161616_BSWAP VIDEO_CODEC_RGBX16161616_BE
#define VIDEO_CODEC_ARGB16161616_BSWAP VIDEO_CODEC_ARGB16161616_BE
#define VIDEO_CODEC_XRGB16161616_BSWAP VIDEO_CODEC_XRGB16161616_BE
#define VIDEO_CODEC_BGRA16161616_BSWAP VIDEO_CODEC_BGRA16161616_BE
#define VIDEO_CODEC_BGRX16161616_BSWAP VIDEO_CODEC_BGRX16161616_BE
#define VIDEO_CODEC_ABGR16161616_BSWAP VIDEO_CODEC_ABGR16161616_BE
#define VIDEO_CODEC_XBGR16161616_BSWAP VIDEO_CODEC_XBGR16161616_BE
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */


/* Gray-scale (Luminance) */
#define VIDEO_CODEC_L1_MSB    0x1001 /* { 0b[L0][L1][L2][L3][L4][L5][L6][L7] } 1-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b01234567" (e.g. x=1 is defined by "byte & 0x40") */
#define VIDEO_CODEC_L1_LSB    0x1002 /* { 0b[L7][L6][L5][L4][L3][L2][L1][L0] } 1-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b76543210" (e.g. x=1 is defined by "byte & 0x02") */
#define VIDEO_CODEC_L2_MSB    0x1003 /* { 0b[LL0][LL1][LL2][LL3] } 2-bit-per-pixel, 4-level grayscale (0=black; 3=white), left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_L2_LSB    0x1004 /* { 0b[LL3][LL2][LL1][LL0] } 2-bit-per-pixel, 4-level grayscale (0=black; 3=white), left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_L4_MSB    0x1005 /* { 0b[LLLL0][LLLL1] } 4-bit-per-pixel, 16-level grayscale (0=black; 15=white), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_L4_LSB    0x1006 /* { 0b[LLLL1][LLLL0] } 4-bit-per-pixel, 16-level grayscale (0=black; 15=white), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_L8        0x1007 /* { 0bLLLLLLLL } 1-byte-per-pixel, 256-level grayscale (0=black; 255=white) */
#define VIDEO_CODEC_LA11_MSB  0x1008 /* { 0b[LA0][LA1][LA2][LA3] } 2-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_LA11_LSB  0x1009 /* { 0b[LA3][LA2][LA1][LA0] } 2-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_AL11_MSB  0x100a /* { 0b[AL0][AL1][AL2][AL3] } 2-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_AL11_LSB  0x100b /* { 0b[AL3][AL2][AL1][AL0] } 2-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_LA22_MSB  0x100c /* { 0b[LLAA0][LLAA1] } 4-bit-per-pixel, 4-level grayscale+alpha (0=black; 3=white), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_LA22_LSB  0x100d /* { 0b[LLAA1][LLAA0] } 4-bit-per-pixel, 4-level grayscale+alpha (0=black; 3=white), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_AL22_MSB  0x100e /* { 0b[AALL0][AALL1] } 4-bit-per-pixel, 4-level grayscale+alpha (0=black; 3=white), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_AL22_LSB  0x100f /* { 0b[AALL1][AALL0] } 4-bit-per-pixel, 4-level grayscale+alpha (0=black; 3=white), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_LA31_MSB  0x1010 /* { 0b[LLLA0][LLLA1] } 4-bit-per-pixel, 8-level grayscale+alpha (0=black; 7=white), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_LA31_LSB  0x1011 /* { 0b[LLLA1][LLLA0] } 4-bit-per-pixel, 8-level grayscale+alpha (0=black; 7=white), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_AL13_MSB  0x1012 /* { 0b[ALLL0][ALLL1] } 4-bit-per-pixel, 8-level grayscale+alpha (0=black; 7=white), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_AL13_LSB  0x1013 /* { 0b[ALLL1][ALLL0] } 4-bit-per-pixel, 8-level grayscale+alpha (0=black; 7=white), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_LA44      0x1014 /* { 0bLLLLAAAA } 1-byte-per-pixel, 16-level grayscale+alpha (0=black; 15=white) */
#define VIDEO_CODEC_AL44      0x1015 /* { 0bAAAALLLL } 1-byte-per-pixel, 16-level grayscale+alpha (0=black; 15=white) */
#define VIDEO_CODEC_LA71      0x1016 /* { 0bLLLLLLLA } 1-byte-per-pixel, 128-level grayscale+alpha (0=black; 15=white) */
#define VIDEO_CODEC_AL17      0x1017 /* { 0bALLLLLLL } 1-byte-per-pixel, 128-level grayscale+alpha (0=black; 15=white) */
#define VIDEO_CODEC_LA88      0x1018 /* { 0bLLLLLLLL, 0bAAAAAAAA } 2-byte-per-pixel, 256-level grayscale+alpha (0=black; 255=white) */
#define VIDEO_CODEC_AL88      0x1019 /* { 0bAAAAAAAA, 0bLLLLLLLL } 2-byte-per-pixel, 256-level grayscale+alpha (0=black; 255=white) */
#define VIDEO_CODEC_L16_LE    0x101a /* { 0bLLLLLLLL, 0bLLLLLLLL } 2-byte-per-pixel, 65536-level grayscale (0=black; 65535=white) */
#define VIDEO_CODEC_L16_BE    0x101b /* { 0bLLLLLLLL, 0bLLLLLLLL } 2-byte-per-pixel, 65536-level grayscale (0=black; 65535=white) */
#define VIDEO_CODEC_LA1616_LE 0x101c /* { 0bLLLLLLLL, 0bLLLLLLLL, 0bAAAAAAAA, 0bAAAAAAAA } 4-byte-per-pixel, 65536-level grayscale+alpha (0=black; 65535=white) */
#define VIDEO_CODEC_LA1616_BE 0x101d /* { 0bLLLLLLLL, 0bLLLLLLLL, 0bAAAAAAAA, 0bAAAAAAAA } 4-byte-per-pixel, 65536-level grayscale+alpha (0=black; 65535=white) */
#define VIDEO_CODEC_AL1616_LE 0x101e /* { 0bAAAAAAAA, 0bAAAAAAAA, 0bLLLLLLLL, 0bLLLLLLLL } 4-byte-per-pixel, 65536-level grayscale+alpha (0=black; 65535=white) */
#define VIDEO_CODEC_AL1616_BE 0x101f /* { 0bAAAAAAAA, 0bAAAAAAAA, 0bLLLLLLLL, 0bLLLLLLLL } 4-byte-per-pixel, 65536-level grayscale+alpha (0=black; 65535=white) */
#define VIDEO_CODEC_A1_MSB    0x1020 /* { 0b[A0][A1][A2][A3][A4][A5][A6][A7] } 1-bit-per-pixel, alpha-mask (rgb=0), left->right pixels are encoded in a byte as "0b01234567" (e.g. x=1 is defined by "byte & 0x40") */
#define VIDEO_CODEC_A1_LSB    0x1021 /* { 0b[A7][A6][A5][A4][A3][A2][A1][A0] } 1-bit-per-pixel, alpha-mask (rgb=0), left->right pixels are encoded in a byte as "0b76543210" (e.g. x=1 is defined by "byte & 0x02") */
#define VIDEO_CODEC_A2_MSB    0x1022 /* { 0b[AA0][AA1][AA2][AA3] } 2-bit-per-pixel, 4-level alpha-mask (0=transparent; 3=opaque; rgb=0), left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_A2_LSB    0x1023 /* { 0b[AA3][AA2][AA1][AA0] } 2-bit-per-pixel, 4-level alpha-mask (0=transparent; 3=opaque; rgb=0), left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_A4_MSB    0x1024 /* { 0b[AAAA0][AAAA1] } 4-bit-per-pixel, 16-level alpha-mask (0=transparent; 15=opaque; rgb=0), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_A4_LSB    0x1025 /* { 0b[AAAA1][AAAA0] } 4-bit-per-pixel, 16-level alpha-mask (0=transparent; 15=opaque; rgb=0), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_A8        0x1026 /* { 0bAAAAAAAA } 1-byte-per-pixel, 256-level alpha-mask (0=transparent; 255=opaque; rgb=0) */
#define VIDEO_CODEC_A16_LE    0x1027 /* { 0bAAAAAAAA, 0bAAAAAAAA } 2-byte-per-pixel, 65536-level alpha-mask (0=transparent; 65535=opaque; rgb=0) */
#define VIDEO_CODEC_A16_BE    0x1028 /* { 0bAAAAAAAA, 0bAAAAAAAA } 2-byte-per-pixel, 65536-level alpha-mask (0=transparent; 65535=opaque; rgb=0) */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define VIDEO_CODEC_L16          VIDEO_CODEC_L16_BE
#define VIDEO_CODEC_LA1616       VIDEO_CODEC_LA1616_BE
#define VIDEO_CODEC_AL1616       VIDEO_CODEC_AL1616_BE
#define VIDEO_CODEC_A16          VIDEO_CODEC_A16_BE
#define VIDEO_CODEC_L16_BSWAP    VIDEO_CODEC_L16_LE
#define VIDEO_CODEC_LA1616_BSWAP VIDEO_CODEC_LA1616_LE
#define VIDEO_CODEC_AL1616_BSWAP VIDEO_CODEC_AL1616_LE
#define VIDEO_CODEC_A16_BSWAP    VIDEO_CODEC_A16_LE
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define VIDEO_CODEC_L16          VIDEO_CODEC_L16_LE
#define VIDEO_CODEC_LA1616       VIDEO_CODEC_LA1616_LE
#define VIDEO_CODEC_AL1616       VIDEO_CODEC_AL1616_LE
#define VIDEO_CODEC_A16          VIDEO_CODEC_A16_LE
#define VIDEO_CODEC_L16_BSWAP    VIDEO_CODEC_L16_BE
#define VIDEO_CODEC_LA1616_BSWAP VIDEO_CODEC_LA1616_BE
#define VIDEO_CODEC_AL1616_BSWAP VIDEO_CODEC_AL1616_BE
#define VIDEO_CODEC_A16_BSWAP    VIDEO_CODEC_A16_BE
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */

/* Palette-driven:
 * - In those cases where only a palette is used (without a dedicated
 *   alpha channel), the alpha value of pixel colors is read from the
 *   palette.
 * - When there is a dedicated alpha channel within pixel data, alpha
 *   values from the  palette are ignored,  and **ONLY** values  from
 *   pixel data are used. */
#define VIDEO_CODEC_P1_MSB    0x2001 /* { 0b[P0][P1][P2][P3][P4][P5][P6][P7] } 2-color palette, (1-bit pixels), left->right pixels are encoded in a byte as "0b01234567" (e.g. x=1 is defined by "byte & 0x40") */
#define VIDEO_CODEC_P1_LSB    0x2002 /* { 0b[P7][P6][P5][P4][P3][P2][P1][P0] } 2-color palette, (1-bit pixels), left->right pixels are encoded in a byte as "0b76543210" (e.g. x=1 is defined by "byte & 0x02") */
#define VIDEO_CODEC_P2_MSB    0x2003 /* { 0b[PP0][PP1][PP2][PP3] } 4-color palette, (2-bit pixels), left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_P2_LSB    0x2004 /* { 0b[PP3][PP2][PP1][PP0] } 4-color palette, (2-bit pixels), left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_P4_MSB    0x2005 /* { 0b[PPPP0][PPPP1] } 16-color palette, (4-bit pixels), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_P4_LSB    0x2006 /* { 0b[PPPP1][PPPP0] } 16-color palette, (4-bit pixels), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_P8        0x2007 /* { 0bPPPPPPPP } 256-color palette (8-bit pixels) */
#define VIDEO_CODEC_PA11_MSB  0x2008 /* { 0b[PA0][PA1][PA2][PA3] } 2-bit-per-pixel, 2-color palette, left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_PA11_LSB  0x2009 /* { 0b[PA3][PA2][PA1][PA0] } 2-bit-per-pixel, 2-color palette, left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_AP11_MSB  0x200a /* { 0b[AP0][AP1][AP2][AP3] } 2-bit-per-pixel, 2-color palette, left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_AP11_LSB  0x200b /* { 0b[AP3][AP2][AP1][AP0] } 2-bit-per-pixel, 2-color palette, left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_PA22_MSB  0x200c /* { 0b[PPAA0][PPAA1] } 4-bit-per-pixel, 4-color palette+alpha, left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_PA22_LSB  0x200d /* { 0b[PPAA1][PPAA0] } 4-bit-per-pixel, 4-color palette+alpha, left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_AP22_MSB  0x200e /* { 0b[AAPP0][AAPP1] } 4-bit-per-pixel, 4-color palette+alpha, left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_AP22_LSB  0x200f /* { 0b[AAPP1][AAPP0] } 4-bit-per-pixel, 4-color palette+alpha, left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_PA31_MSB  0x2010 /* { 0b[PPPA0][PPPA1] } 4-bit-per-pixel, 8-color palette+alpha, left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_PA31_LSB  0x2011 /* { 0b[PPPA1][PPPA0] } 4-bit-per-pixel, 8-color palette+alpha, left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_AP13_MSB  0x2012 /* { 0b[APPP0][APPP1] } 4-bit-per-pixel, 8-color palette+alpha, left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_AP13_LSB  0x2013 /* { 0b[APPP1][APPP0] } 4-bit-per-pixel, 8-color palette+alpha, left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_PA44      0x2014 /* { 0bPPPPAAAA } 1-byte-per-pixel, 16-color palette+alpha */
#define VIDEO_CODEC_AP44      0x2015 /* { 0bAAAAPPPP } 1-byte-per-pixel, 16-color palette+alpha */
#define VIDEO_CODEC_PA71      0x2016 /* { 0bPPPPPPPA } 1-byte-per-pixel, 128-color palette+alpha */
#define VIDEO_CODEC_AP17      0x2017 /* { 0bAPPPPPPP } 1-byte-per-pixel, 128-color palette+alpha */
#define VIDEO_CODEC_PA88      0x2018 /* { 0bPPPPPPPP, 0bAAAAAAAA } 2-byte-per-pixel, 256-color palette+alpha */
#define VIDEO_CODEC_AP88      0x2019 /* { 0bAAAAAAAA, 0bPPPPPPPP } 2-byte-per-pixel, 256-color palette+alpha */
#define VIDEO_CODEC_P16_LE    0x201a /* { 0bPPPPPPPP, 0bPPPPPPPP } 2-byte-per-pixel, 65536-level palette */
#define VIDEO_CODEC_P16_BE    0x201b /* { 0bPPPPPPPP, 0bPPPPPPPP } 2-byte-per-pixel, 65536-level palette */
#define VIDEO_CODEC_PA1616_LE 0x201c /* { 0bPPPPPPPP, 0bPPPPPPPP, 0bAAAAAAAA, 0bAAAAAAAA } 4-byte-per-pixel, 65536-level palette+alpha */
#define VIDEO_CODEC_PA1616_BE 0x201d /* { 0bPPPPPPPP, 0bPPPPPPPP, 0bAAAAAAAA, 0bAAAAAAAA } 4-byte-per-pixel, 65536-level palette+alpha */
#define VIDEO_CODEC_AP1616_LE 0x201e /* { 0bAAAAAAAA, 0bAAAAAAAA, 0bPPPPPPPP, 0bPPPPPPPP } 4-byte-per-pixel, 65536-level palette+alpha */
#define VIDEO_CODEC_AP1616_BE 0x201f /* { 0bAAAAAAAA, 0bAAAAAAAA, 0bPPPPPPPP, 0bPPPPPPPP } 4-byte-per-pixel, 65536-level palette+alpha */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define VIDEO_CODEC_P16          VIDEO_CODEC_P16_BE
#define VIDEO_CODEC_PA1616       VIDEO_CODEC_PA1616_BE
#define VIDEO_CODEC_AP1616       VIDEO_CODEC_AP1616_BE
#define VIDEO_CODEC_P16_BSWAP    VIDEO_CODEC_P16_LE
#define VIDEO_CODEC_PA1616_BSWAP VIDEO_CODEC_PA1616_LE
#define VIDEO_CODEC_AP1616_BSWAP VIDEO_CODEC_AP1616_LE
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define VIDEO_CODEC_P16          VIDEO_CODEC_P16_LE
#define VIDEO_CODEC_PA1616       VIDEO_CODEC_PA1616_LE
#define VIDEO_CODEC_AP1616       VIDEO_CODEC_AP1616_LE
#define VIDEO_CODEC_P16_BSWAP    VIDEO_CODEC_P16_BE
#define VIDEO_CODEC_PA1616_BSWAP VIDEO_CODEC_PA1616_BE
#define VIDEO_CODEC_AP1616_BSWAP VIDEO_CODEC_AP1616_BE
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */




/* Video codec flags (bits for `struct video_codec_specs::vcs_flags') */
#define VIDEO_CODEC_FLAG_NORMAL     0x00 /* Normal flags */
#define VIDEO_CODEC_FLAG_PAL        0x01 /* Does this codec use a palette? (do not combine with `VIDEO_CODEC_FLAG_LUM') */
#define VIDEO_CODEC_FLAG_LUM        0x02 /* Is this a grayscale-only (luminance) or alpha-only codec? (do not combine with `VIDEO_CODEC_FLAG_PAL') */
#define VIDEO_CODEC_FLAG_MSB        0x00 /* When multiple pixels fit into a single byte, they are ordered as "0b01234567" (e.g. pixel at x=1 is defined by "byte & 0x40") */
#define VIDEO_CODEC_FLAG_LSB        0x04 /* When multiple pixels fit into a single byte, they are ordered as "0b76543210" (e.g. pixel at x=1 is defined by "byte & 0x02") */
#define VIDEO_CODEC_FLAG_INTERP8888 0x08 /* When interpreted as uint8_t[4], pixel values can be interpolated directly (as opposed to converting to colors, interpolating,
                                          * then converting back)  This applies  to all  codecs supporting linear  blending, that  also make  use of  8-bits-per-channel.
                                          * The caller need not pre-calculate this flag for `video_codec_fromspecs' */
#define VIDEO_CODEC_FLAG_LITTLE_ENDIAN 0x00 /* Multi- (and whole-)byte channels are encoded in little-endian (default) */
#define VIDEO_CODEC_FLAG_BIG_ENDIAN    0x10 /* Multi- (and whole-)byte channels are encoded in big-endian (else: little-endian) */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define VIDEO_CODEC_FLAG_NATIVE_ENDIAN VIDEO_CODEC_FLAG_BIG_ENDIAN
#define VIDEO_CODEC_FLAG_BSWAP_ENDIAN  VIDEO_CODEC_FLAG_LITTLE_ENDIAN
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
#define VIDEO_CODEC_FLAG_NATIVE_ENDIAN VIDEO_CODEC_FLAG_LITTLE_ENDIAN
#define VIDEO_CODEC_FLAG_BSWAP_ENDIAN  VIDEO_CODEC_FLAG_BIG_ENDIAN
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */

#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
/* VIDEO_CODEC_FLAG_COLOR64:
 *  - video_color64_t must be used for loss-less pixel<=>color conversion
 *  - Example: VIDEO_CODEC_RGBA1010102
 *    because color channels are >8bit
 * VIDEO_CODEC_FLAG_PIXEL64:
 *  - video_pixel64_t must be used for loss-less reads/writes
 *  - Example: VIDEO_CODEC_RGBA16161616
 *    because "video_pixel_t" is too small to hold the full pixel */
#define VIDEO_CODEC_FLAG_COLOR64    0x20 /* This codec uses color channels >8bit, meaning `vc_pixel2color' produces truncated results and `vc_pixel2color64' should be used */
#define VIDEO_CODEC_FLAG_PIXEL64    0x40 /* This codec's bpp is >32, meaning `vc_color2pixel' produces truncated results and `vc_color2pixel64' should be used. This flag implies `VIDEO_CODEC_FLAG_COLOR64' */
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
#define VIDEO_CODEC_FLAG_SPECIAL    0x80 /* Special video codec that cannot be represented using `vcs_*mask' */
#define VIDEO_CODEC_FLAG_ISLSB(x) ((x) & VIDEO_CODEC_FLAG_LSB)
#define VIDEO_CODEC_FLAG_ISMSB(x) (!((x) & VIDEO_CODEC_FLAG_LSB))

#ifdef __CC__
__DECL_BEGIN

typedef __uint16_t video_codec_t; /* One of `VIDEO_CODEC_*' */

struct video_converter;
struct video_surface;

struct video_rambuffer_requirements {
	__size_t vbs_bufsize; /* Minimal buffer size (in bytes) */
	__size_t vbs_stride;  /* Minimal scanline stride (in bytes) */
};

struct video_codec_specs {
	__uint8_t        vcs_flags; /* Set of `VIDEO_CODEC_FLAG_*' */
	__uint8_t        vcs_pxsz;  /* [== CEILDIV(vcs_bpp, NBBY)] # of bytes per pixel (rounded up) */
	__SHIFT_TYPE__   vcs_bpp;   /* # of bits per pixel (when not divisible by "8", pixels aren't aligned by byte-boundaries) */
	__SHIFT_TYPE__   vcs_cbits; /* [<= vcs_bpp] # of color  bits per pixel.  Usually same as  "vcs_bpp", except when  some bits  go
	                             * unused. In the  case of a  palette-driven codec, `1 << vcs_cbits'  is the size  of the  palette.
	                             * For normal codecs, this is always equal to `SUM(POPCOUNT(vcs_*mask))' (and includes "vcs_amask",
	                             * which it doesn't for palette/gray-scale codecs) */
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
	__UINT32_TYPE__ _vcs_pad;   /* ... */
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

	/* Color masks. For grayscale / palette-driven codecs, these are all identical and
	 * specify the mask of bits within a single pixel whose "PEXT" result is then used
	 * as palette index / grayscale-strength.
	 *
	 * For whole/multi-byte codecs, these masks assume that you read a pixel as:
	 * >> video_pixel64_t pixel = UNALIGNED_GET((uintN_t *)pixel_addr);
	 * iow: these masks are always in host-endian */
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
	video_pixel64_t  vcs_rmask; /* Mask of bits in a pixel that make up red */
	video_pixel64_t  vcs_gmask; /* Mask of bits in a pixel that make up green */
	video_pixel64_t  vcs_bmask; /* Mask of bits in a pixel that make up blue */
	/* The alpha-mask does not participate in palette/grayscale lookup; it always functions as its own thing */
	video_pixel64_t  vcs_amask; /* Mask of bits in a pixel that make up alpha */
#else /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */
	video_pixel_t    vcs_rmask; /* Mask of bits in a pixel that make up red */
	video_pixel_t    vcs_gmask; /* Mask of bits in a pixel that make up green */
	video_pixel_t    vcs_bmask; /* Mask of bits in a pixel that make up blue */
	/* The alpha-mask does not participate in palette/grayscale lookup; it always functions as its own thing */
	video_pixel_t    vcs_amask; /* Mask of bits in a pixel that make up alpha */
#endif /* !CONFIG_LIBVIDEO_HAVE_PIXEL64 */
};



/* Convert between color and pixel values. */
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_color_t
(LIBVIDEO_GFX_FCC *video_codec_pixel2color_t)(struct video_surface const *__restrict __self,
                                              video_pixel_t __pixel);
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_pixel_t
(LIBVIDEO_GFX_FCC *video_codec_color2pixel_t)(struct video_surface const *__restrict __self,
                                              video_color_t __color);

/* Initialize a pixel format converter `__self' by:
 * - Filling in `__self->vcv_mappixel'
 * - Optionally filling in `__self->_vcv_driver'
 *
 * The caller must have already filled in:
 * - `__self->vcv_from'
 * - `__self->vcv_to'
 *
 * This operator must be called as `(*__self->vcv_from.vbf_codec->vc_initconverter)(__self)'
 * @return: * : Always re-returns `__self' */
typedef __ATTR_RETNONNULL_T __ATTR_INOUT_T(1) struct video_converter *
(LIBVIDEO_GFX_FCC *video_codec_initconverter_t)(struct video_converter *__restrict __self);

/* Get a pixel (The caller must ensure that the given x is in-bounds) */
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_pixel_t
(LIBVIDEO_GFX_FCC *video_codec_getpixel_t)(__byte_t const *__restrict __line, video_coord_t __x);

/* Set a pixel (The caller must ensure that the given x is in-bounds) */
typedef __ATTR_NONNULL_T((1)) void
(LIBVIDEO_GFX_FCC *video_codec_setpixel_t)(__byte_t *__restrict __line,
                                           video_coord_t __x, video_pixel_t __pixel);

#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
#if __has_attribute(__regparm__)
#define VIDEO_CODEC_SETPIXEL3_CC __attribute__((__regparm__(3)))
/* Same as `vc_setpixel', but uses a different calling
 * convention  to pass all arguments through registers */
typedef __ATTR_NONNULL_T((1)) void
(VIDEO_CODEC_SETPIXEL3_CC *_video_codec_setpixel3_t)(__byte_t *__restrict __line,
	                                                 video_coord_t __x, video_pixel_t __pixel);
#else /* __has_attribute(__regparm__) */
typedef void (*_video_codec_setpixel3_t)(void);
#define VIDEO_CODEC_HAVE__VC_SETPIXEL3_DUMMY
#endif /* !__has_attribute(__regparm__) */
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */

/* Fill `__num_pixels' neighboring pixels  horizontally.
 * The caller must ensure that all coords are in-bounds.
 * @assume(IS_ALIGNED(__line, vc_align));
 * @assume(__num_pixels > 0); */
typedef __ATTR_NONNULL_T((1)) void
(LIBVIDEO_GFX_FCC *video_codec_linefill_t)(__byte_t *__restrict __line, video_coord_t __x,
                                           video_pixel_t __pixel, video_dim_t __num_pixels);

/* Fill a vertical line of pixels. Same as:
 * >> do {
 * >>     (*vc_setpixel)(__line, __x, __pixel);
 * >>     __line += __stride;
 * >> } while (--__num_pixels);
 * @assume(IS_ALIGNED(__line, vc_align));
 * @assume(IS_ALIGNED(__stride, vc_align));
 * @assume(__num_pixels > 0); */
typedef __ATTR_NONNULL_T((1)) void
(LIBVIDEO_GFX_FCC *video_codec_vertfill_t)(__byte_t *__restrict __line, video_coord_t __x, __size_t __stride,
                                           video_pixel_t __pixel, video_dim_t __num_pixels);

/* Fill a rect of pixels. Same as:
 * >> do {
 * >>     (*vc_linefill)(__line, __x, __pixel, __size_x);
 * >>     __line += __stride;
 * >> } while (--__size_y);
 * @assume(__size_x > 0);
 * @assume(__size_y > 0);
 * @assume(IS_ALIGNED(__line, vc_align));
 * @assume(IS_ALIGNED(__stride, vc_align)); */
typedef __ATTR_NONNULL_T((1)) void
(LIBVIDEO_GFX_FCC *video_codec_rectfill_t)(__byte_t *__restrict __line, video_coord_t __x, __size_t __stride,
                                           video_pixel_t __pixel, video_dim_t __size_x, video_dim_t __size_y);

/* Copy a rect of pixels. When src/dst overlap, results are weak-undefined.
 * @assume(IS_ALIGNED(__dst_line, vc_align));
 * @assume(IS_ALIGNED(__src_line, vc_align));
 * @assume(IS_ALIGNED(__dst_stride, vc_align));
 * @assume(IS_ALIGNED(__src_stride, vc_align));
 * @assume(__size_x > 0);
 * @assume(__size_y > 0); */
typedef __ATTR_NONNULL_T((1, 4)) void
(LIBVIDEO_GFX_FCC *video_codec_rectcopy_t)(__byte_t *__restrict __dst_line, video_coord_t __dst_x, __size_t __dst_stride,
                                           __byte_t const *__restrict __src_line, video_coord_t __src_x, __size_t __src_stride,
                                           video_dim_t __size_x, video_dim_t __size_y);

/* Same as `vc_rectcopy', but able to deal with the actual memory of __dst_line/__src_line
 * overlapping, whilst properly dealing with that being the case without producing corrupt
 * results (iow: this is "memmove", and `vc_rectcopy' is "memcpy") */
typedef __ATTR_NONNULL_T((1, 3)) void
(LIBVIDEO_GFX_FCC *video_codec_rectmove_t)(__byte_t *__dst_line, video_coord_t __dst_x,
                                           __byte_t const *__src_line, video_coord_t __src_x,
                                           __size_t __stride, video_dim_t __size_x, video_dim_t __size_y);

/* Copy a line of pixels. When src/dst overlap, results are weak-undefined.
 * @assume(IS_ALIGNED(__dst_line, vc_align));
 * @assume(IS_ALIGNED(__src_line, vc_align));
 * @assume(__size_x > 0); */
typedef __ATTR_NONNULL_T((1, 3)) void
(LIBVIDEO_GFX_FCC *video_codec_linecopy_t)(__byte_t *__restrict __dst_line, video_coord_t __dst_x,
                                           __byte_t const *__restrict __src_line, video_coord_t __src_x,
                                           video_dim_t __size_x);

/* 64-bit color/pixel functions */
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_color64_t
(LIBVIDEO_GFX_FCC *video_codec_pixel2color64_t)(struct video_surface const *__restrict __self,
                                                video_pixel64_t __pixel);
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_pixel64_t
(LIBVIDEO_GFX_FCC *video_codec_color2pixel64_t)(struct video_surface const *__restrict __self,
                                                video_color64_t __color);
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_pixel64_t
(LIBVIDEO_GFX_FCC *video_codec_getpixel64_t)(__byte_t const *__restrict __line, video_coord_t __x);
typedef __ATTR_NONNULL_T((1)) void
(LIBVIDEO_GFX_FCC *video_codec_setpixel64_t)(__byte_t *__restrict __line,
                                             video_coord_t __x, video_pixel64_t __pixel);
typedef __ATTR_NONNULL_T((1)) void
(LIBVIDEO_GFX_FCC *video_codec_linefill64_t)(__byte_t *__restrict __line, video_coord_t __x,
                                             video_pixel64_t __pixel, video_dim_t __num_pixels);
typedef __ATTR_NONNULL_T((1)) void
(LIBVIDEO_GFX_FCC *video_codec_vertfill64_t)(__byte_t *__restrict __line, video_coord_t __x, __size_t __stride,
                                             video_pixel64_t __pixel, video_dim_t __num_pixels);
typedef __ATTR_NONNULL_T((1)) void
(LIBVIDEO_GFX_FCC *video_codec_rectfill64_t)(__byte_t *__restrict __line, video_coord_t __x, __size_t __stride,
                                             video_pixel64_t __pixel, video_dim_t __size_x, video_dim_t __size_y);
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */



#ifndef __VIDEO_CODEC_const
#define __VIDEO_CODEC_const const
#endif /* !__VIDEO_CODEC_const */

struct video_codec {
	__uintptr_t        vc_refcnt; /* Reference counter. */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_FCC *__VIDEO_CODEC_const vc_destroy)(struct video_codec *__restrict __self);

	/* Video format operations. */
	video_codec_t             __VIDEO_CODEC_const vc_codec; /* [const] Video codec ID (One of `VIDEO_FORMAT_*') */
	struct video_codec_specs  __VIDEO_CODEC_const vc_specs; /* [const] Video format flags (Set of `VIDEO_CODEC_FLAG_*') */
	__uint32_t                __VIDEO_CODEC_const vc_align; /* [!0][const] Byte alignment requirements for base_addr/stride of buffers using this codec. */
	__REF struct video_codec *__VIDEO_CODEC_const vc_nalgn; /* [1..1][const] Codec identical to this one, except with `vc_align == 1' */
	/* NOTE: _ALL_ Callbacks are always [1..1][const] */

	/* Calculate minimal ram-buffer requirements for a graphic with the given dimensions.
	 * Note that in addition, a ram-buffer needs a minimal alignment of `vc_align' bytes,
	 * though this restriction may be omitted by simply using `vc_nalgn' instead. */
	__ATTR_OUT_T(3) void
	__NOTHROW_T(LIBVIDEO_GFX_FCC *__VIDEO_CODEC_const vc_rambuffer_requirements)(video_dim_t __size_x, video_dim_t __size_y,
	                                                                             struct video_rambuffer_requirements *__restrict __result);

	/* Modulate `*__p_coord' into the relevant sub-byte pixel offset,
	 * and return the byte-offset that must be added to the start  of
	 * some  pixel-line  to   account  for   the  pixel   adjustment:
	 * >> pixel = (*vc_getpixel)(LINE, X);
	 * Same as:
	 * >> LINE += (*vc_coord2bytes)(&X);
	 * >> pixel = (*vc_getpixel)(LINE, X); */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __size_t
	__NOTHROW_T(LIBVIDEO_GFX_FCC *__VIDEO_CODEC_const vc_coord2bytes)(video_coord_t *__restrict __p_coord);

	video_codec_pixel2color_t   __VIDEO_CODEC_const vc_pixel2color;   /* Convert between color and pixel values. */
	video_codec_color2pixel_t   __VIDEO_CODEC_const vc_color2pixel;   /* ... */
	video_codec_initconverter_t __VIDEO_CODEC_const vc_initconverter; /* Initialize a pixel format converter */
	video_codec_getpixel_t      __VIDEO_CODEC_const vc_getpixel;      /* Get a pixel */
	video_codec_setpixel_t      __VIDEO_CODEC_const vc_setpixel;      /* Set a pixel */
#ifdef CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3
	_video_codec_setpixel3_t   __VIDEO_CODEC_const _vc_setpixel3;     /* ... */
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */
	video_codec_linefill_t      __VIDEO_CODEC_const vc_linefill;      /* Fill neighboring pixels horizontally. .*/
	video_codec_vertfill_t      __VIDEO_CODEC_const vc_vertfill;      /* Fill a vertical line of pixels.*/
	video_codec_rectfill_t      __VIDEO_CODEC_const vc_rectfill;      /* Fill a rect of pixels. */
	video_codec_rectcopy_t      __VIDEO_CODEC_const vc_rectcopy;      /* Copy a rect of pixels. When src/dst overlap, results are weak-undefined. */
	video_codec_rectmove_t      __VIDEO_CODEC_const vc_rectmove;      /* Same as `vc_rectcopy', but properly deal with overlapping video buffers */
	video_codec_linecopy_t      __VIDEO_CODEC_const vc_linecopy;      /* Copy a line of pixels */

	/* TODO: More operators for fast rectcopy w/ rotation/mirroring */

	/* HDR video codec operators */
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
	video_codec_pixel2color64_t __VIDEO_CODEC_const vc_pixel2color64; /* Convert between color and pixel values. */
	video_codec_color2pixel64_t __VIDEO_CODEC_const vc_color2pixel64; /* ... */
	video_codec_getpixel64_t    __VIDEO_CODEC_const vc_getpixel64;    /* Get a pixel */
	video_codec_setpixel64_t    __VIDEO_CODEC_const vc_setpixel64;    /* Set a pixel */
	video_codec_linefill64_t    __VIDEO_CODEC_const vc_linefill64;    /* Fill neighboring pixels horizontally. .*/
	video_codec_vertfill64_t    __VIDEO_CODEC_const vc_vertfill64;    /* Fill a vertical line of pixels.*/
	video_codec_rectfill64_t    __VIDEO_CODEC_const vc_rectfill64;    /* Fill a rect of pixels. */
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

	/* Extra implementation-specific operators/fields go here... */
};


#ifdef __INTELLISENSE__
/* Return the # of colors needed by palettes used with this codec. If the
 * codec doesn't make use of  palettes, this returns an undefined  value. */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_pixel_t
video_codec_getpalcolors(struct video_codec const *__restrict self);
#else /* __INTELLISENSE__ */
#define video_codec_getpalcolors(self) ((video_pixel_t)1 << (self)->vc_specs.vcs_cbits)
#endif /* !__INTELLISENSE__ */


/* Reference counter controls for `struct video_codec' */
#define video_codec_destroy(self) (*(self)->vc_destroy)(self)
#define video_codec_incref(self) \
	__hybrid_atomic_inc(&(self)->vc_refcnt, __ATOMIC_SEQ_CST)
#define video_codec_decref(self)                                       \
	(void)(__hybrid_atomic_decfetch(&(self)->vc_refcnt, __ATOMIC_SEQ_CST) || \
	       (video_codec_destroy(self), 0))
#define video_codec_xincref(self) (void)(!(self) || (video_codec_incref(self), 0))
#define video_codec_xdecref(self) (void)(!(self) || (video_codec_decref(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_codec, vc_refcnt, video_codec_destroy)



/* If available for host+compiler, use "_vc_setpixel3" when possible */
#if (defined(CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3) && \
     !defined(VIDEO_CODEC_HAVE__VC_SETPIXEL3_DUMMY))
#define video_codec_setpixel_t _video_codec_setpixel3_t
#define vc_setpixel            _vc_setpixel3
#endif /* CONFIG_VIDEO_CODEC_HAVE__VC_SETPIXEL3 */



/* Lookup the interface for a given codec, or return NULL if the codec isn't supported. */
typedef __ATTR_CONST_T __ATTR_WUNUSED_T struct video_codec *
(LIBVIDEO_GFX_FCC *PVIDEO_CODEC_LOOKUP)(video_codec_t __codec);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_CONST __ATTR_WUNUSED struct video_codec *
(LIBVIDEO_GFX_FCC video_codec_lookup)(video_codec_t __codec);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

/* Same as `video_codec_lookup()', and also only returns built-in codecs, but lookup
 * is  done via `specs', as opposed to the  caller having to provide the codec's ID.
 *
 * NOTE: This function doesn't need `vcs_pxsz' or `vcs_cbits' to be initialized. */
typedef __ATTR_CONST_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) struct video_codec *
(LIBVIDEO_GFX_FCC *PVIDEO_CODEC_LOOKUP_SPECS)(struct video_codec_specs const *__restrict __specs);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) struct video_codec *
(LIBVIDEO_GFX_FCC video_codec_lookup_specs)(struct video_codec_specs const *__restrict __specs);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */



/* Same as `video_codec_lookup_specs()', but can also be used to construct
 * new codecs on-the-fly. Because this function is able/allowed to  create
 * new codecs on-the-fly, the caller must take ownership of a reference to
 * `*p_handle'  on success, and  keep that reference alive  for as long as
 * the returned codec is in-use.
 *
 * When the described codec is actually a built-in one, this function always
 * succeeds,  and a  reference to a  dummy object is  stored in `*p_handle'.
 *
 * NOTE: This function doesn't need `vcs_pxsz' or `vcs_cbits' to be initialized.
 *
 * @return: * :   The codec in question (`*p_handle' must be inherited in this case)
 * @return: NULL: [EINVAL] Impossible codec
 * @return: NULL: [ENOMEM] Out-of-memory
 * @return: NULL: [*] Error */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __REF struct video_codec *
(LIBVIDEO_GFX_FCC *PVIDEO_CODEC_FROMSPECS)(struct video_codec_specs const *__restrict __specs);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __REF struct video_codec *
(LIBVIDEO_GFX_FCC video_codec_fromspecs)(struct video_codec_specs const *__restrict __specs);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_CODEC_CODEC_H */
