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
 *   >> byte ASC, bit ASC
 *   iow: channels that appear in bytes at lower memory addresses
 *        are listed first, and channels that appear in the  same
 *        byte are listed from least-to-most significant bit.
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
#define VIDEO_CODEC_RGBA8888 0x0001 /* >> struct { uint8_t r; uint8_t g; uint8_t b; uint8_t a; }
                                     * Hint: in this codec, "video_pixel_t" and "video_color_t" are identical */
#define VIDEO_CODEC_RGBX8888 0x0002 /* >> struct { uint8_t r; uint8_t g; uint8_t b; uint8_t x; } */
#define VIDEO_CODEC_ARGB8888 0x0003 /* >> struct { uint8_t a; uint8_t r; uint8_t g; uint8_t b; } */
#define VIDEO_CODEC_XRGB8888 0x0004 /* >> struct { uint8_t x; uint8_t r; uint8_t g; uint8_t b; } */
#define VIDEO_CODEC_ABGR8888 0x0005 /* >> struct { uint8_t a; uint8_t b; uint8_t g; uint8_t r; } */
#define VIDEO_CODEC_XBGR8888 0x0006 /* >> struct { uint8_t x; uint8_t b; uint8_t g; uint8_t r; } */
#define VIDEO_CODEC_BGRA8888 0x0007 /* >> struct { uint8_t b; uint8_t g; uint8_t r; uint8_t a; } */
#define VIDEO_CODEC_BGRX8888 0x0008 /* >> struct { uint8_t b; uint8_t g; uint8_t r; uint8_t x; } */
#define VIDEO_CODEC_RGB888   0x0009 /* >> struct { uint8_t r; uint8_t g; uint8_t b; } */
#define VIDEO_CODEC_BGR888   0x000a /* >> struct { uint8_t b; uint8_t g; uint8_t r; } */
#define VIDEO_CODEC_RGBA4444 0x0011
#define VIDEO_CODEC_RGBX4444 0x0012
#define VIDEO_CODEC_ARGB4444 0x0013
#define VIDEO_CODEC_XRGB4444 0x0014
#define VIDEO_CODEC_ABGR4444 0x0015
#define VIDEO_CODEC_XBGR4444 0x0016
#define VIDEO_CODEC_BGRA4444 0x0017
#define VIDEO_CODEC_BGRX4444 0x0018
#define VIDEO_CODEC_RGB565   0x0019
#define VIDEO_CODEC_BGR565   0x001a
#define VIDEO_CODEC_RGBA5551 0x0021
#define VIDEO_CODEC_RGBX5551 0x0022
#define VIDEO_CODEC_ARGB1555 0x0023
#define VIDEO_CODEC_XRGB1555 0x0024
#define VIDEO_CODEC_ABGR1555 0x0025
#define VIDEO_CODEC_XBGR1555 0x0026
#define VIDEO_CODEC_BGRA5551 0x0027
#define VIDEO_CODEC_BGRX5551 0x0028
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
/* TODO: RGBA1010102 */
/* TODO: RGBX1010102 */
/* TODO: ARGB2101010 */
/* TODO: XRGB2101010 */
/* TODO: BGRA1010102 */
/* TODO: BGRX1010102 */
/* TODO: ABGR2101010 */
/* TODO: XBGR2101010 */
/* TODO: RGB111110 */
/* TODO: RGB111011 */
/* TODO: RGB101111 */
/* TODO: BGR111110 */
/* TODO: BGR111011 */
/* TODO: BGR101111 */

/* 64bpp direct color */
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
/* TODO: RGBA16161616 */
/* TODO: RGBX16161616 */
/* TODO: ARGB16161616 */
/* TODO: XRGB16161616 */
/* TODO: BGRA16161616 */
/* TODO: BGRX16161616 */
/* TODO: ABGR16161616 */
/* TODO: XBGR16161616 */
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */


/* Gray-scale (Luminance) */
#define VIDEO_CODEC_L1_MSB   0x1001 /* 1-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b01234567" (e.g. x=1 is defined by "byte & 0x40") */
#define VIDEO_CODEC_L1_LSB   0x1002 /* 1-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b76543210" (e.g. x=1 is defined by "byte & 0x02") */
#define VIDEO_CODEC_L2_MSB   0x1003 /* 2-bit-per-pixel, 4-level grayscale (0=black; 3=white), left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_L2_LSB   0x1004 /* 2-bit-per-pixel, 4-level grayscale (0=black; 3=white), left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_L4_MSB   0x1005 /* 4-bit-per-pixel, 16-level grayscale (0=black; 15=white), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_L4_LSB   0x1006 /* 4-bit-per-pixel, 16-level grayscale (0=black; 15=white), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_L8       0x1007 /* 1-byte-per-pixel, 256-level grayscale (0=black; 255=white) */
#define VIDEO_CODEC_LA11_MSB 0x1008 /* 2-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_LA11_LSB 0x1009 /* 2-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_AL11_MSB 0x100a /* 2-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_AL11_LSB 0x100b /* 2-bit-per-pixel, black/white, left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_LA22_MSB 0x100c /* 4-bit-per-pixel, 4-level grayscale+alpha (0=black; 3=white), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_LA22_LSB 0x100d /* 4-bit-per-pixel, 4-level grayscale+alpha (0=black; 3=white), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_AL22_MSB 0x100e /* 4-bit-per-pixel, 4-level grayscale+alpha (0=black; 3=white), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_AL22_LSB 0x100f /* 4-bit-per-pixel, 4-level grayscale+alpha (0=black; 3=white), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_LA31_MSB 0x1010 /* 4-bit-per-pixel, 8-level grayscale+alpha (0=black; 7=white), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_LA31_LSB 0x1011 /* 4-bit-per-pixel, 8-level grayscale+alpha (0=black; 7=white), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_AL13_MSB 0x1012 /* 4-bit-per-pixel, 8-level grayscale+alpha (0=black; 7=white), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_AL13_LSB 0x1013 /* 4-bit-per-pixel, 8-level grayscale+alpha (0=black; 7=white), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_LA44     0x1014 /* 1-byte-per-pixel, 16-level grayscale+alpha (0=black; 15=white) */
#define VIDEO_CODEC_AL44     0x1015 /* 1-byte-per-pixel, 16-level grayscale+alpha (0=black; 15=white) */
#define VIDEO_CODEC_LA71     0x1016 /* 1-byte-per-pixel, 128-level grayscale+alpha (0=black; 15=white) */
#define VIDEO_CODEC_AL17     0x1017 /* 1-byte-per-pixel, 128-level grayscale+alpha (0=black; 15=white) */
#define VIDEO_CODEC_LA88     0x1018 /* 2-byte-per-pixel, 256-level grayscale+alpha (0=black; 255=white) */
#define VIDEO_CODEC_AL88     0x1019 /* 2-byte-per-pixel, 256-level grayscale+alpha (0=black; 255=white) */
#define VIDEO_CODEC_A1_MSB   0x101a /* 1-bit-per-pixel, alpha-mask (rgb=0), left->right pixels are encoded in a byte as "0b01234567" (e.g. x=1 is defined by "byte & 0x40") */
#define VIDEO_CODEC_A1_LSB   0x101b /* 1-bit-per-pixel, alpha-mask (rgb=0), left->right pixels are encoded in a byte as "0b76543210" (e.g. x=1 is defined by "byte & 0x02") */
#define VIDEO_CODEC_A2_MSB   0x101c /* 2-bit-per-pixel, 4-level alpha-mask (0=transparent; 3=opaque; rgb=0), left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_A2_LSB   0x101d /* 2-bit-per-pixel, 4-level alpha-mask (0=transparent; 3=opaque; rgb=0), left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_A4_MSB   0x101e /* 4-bit-per-pixel, 16-level alpha-mask (0=transparent; 15=opaque; rgb=0), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_A4_LSB   0x101f /* 4-bit-per-pixel, 16-level alpha-mask (0=transparent; 15=opaque; rgb=0), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_A8       0x1020 /* 1-byte-per-pixel, 256-level alpha-mask (0=transparent; 255=opaque; rgb=0) */
#ifdef CONFIG_LIBVIDEO_HAVE_PIXEL64
/* TODO: L16 */
/* TODO: LA1616 */
/* TODO: AL1616 */
#endif /* CONFIG_LIBVIDEO_HAVE_PIXEL64 */

/* Palette-driven:
 * - In those cases where only a palette is used (without a dedicated
 *   alpha channel), the alpha value of pixel colors is read from the
 *   palette.
 * - When there is a dedicated alpha channel within pixel data, alpha
 *   values from the  palette are ignored,  and **ONLY** values  from
 *   pixel data are used. */
#define VIDEO_CODEC_P1_MSB   0x2001 /* 2-color palette, (1-bit pixels), left->right pixels are encoded in a byte as "0b01234567" (e.g. x=1 is defined by "byte & 0x40") */
#define VIDEO_CODEC_P1_LSB   0x2002 /* 2-color palette, (1-bit pixels), left->right pixels are encoded in a byte as "0b76543210" (e.g. x=1 is defined by "byte & 0x02") */
#define VIDEO_CODEC_P2_MSB   0x2003 /* 4-color palette, (2-bit pixels), left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_P2_LSB   0x2004 /* 4-color palette, (2-bit pixels), left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_P4_MSB   0x2005 /* 16-color palette, (4-bit pixels), left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_P4_LSB   0x2006 /* 16-color palette, (4-bit pixels), left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_P8       0x2007 /* 256-color palette (8-bit pixels) */
#define VIDEO_CODEC_PA11_MSB 0x2008 /* 2-bit-per-pixel, 2-color palette, left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_PA11_LSB 0x2009 /* 2-bit-per-pixel, 2-color palette, left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_AP11_MSB 0x200a /* 2-bit-per-pixel, 2-color palette, left->right pixels are encoded in a byte as "0b00112233" (e.g. x=1 is defined by "byte & 0x30") */
#define VIDEO_CODEC_AP11_LSB 0x200b /* 2-bit-per-pixel, 2-color palette, left->right pixels are encoded in a byte as "0b33221100" (e.g. x=1 is defined by "byte & 0x0c") */
#define VIDEO_CODEC_PA22_MSB 0x200c /* 4-bit-per-pixel, 4-color palette+alpha, left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_PA22_LSB 0x200d /* 4-bit-per-pixel, 4-color palette+alpha, left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_AP22_MSB 0x200e /* 4-bit-per-pixel, 4-color palette+alpha, left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_AP22_LSB 0x200f /* 4-bit-per-pixel, 4-color palette+alpha, left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_PA31_MSB 0x2010 /* 4-bit-per-pixel, 8-color palette+alpha, left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_PA31_LSB 0x2011 /* 4-bit-per-pixel, 8-color palette+alpha, left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_AP13_MSB 0x2012 /* 4-bit-per-pixel, 8-color palette+alpha, left->right pixels are encoded in a byte as "0b00001111" (e.g. x=1 is defined by "byte & 0x0f") */
#define VIDEO_CODEC_AP13_LSB 0x2013 /* 4-bit-per-pixel, 8-color palette+alpha, left->right pixels are encoded in a byte as "0b11110000" (e.g. x=1 is defined by "byte & 0xf0") */
#define VIDEO_CODEC_PA44     0x2014 /* 1-byte-per-pixel, 16-color palette+alpha */
#define VIDEO_CODEC_AP44     0x2015 /* 1-byte-per-pixel, 16-color palette+alpha */
#define VIDEO_CODEC_PA71     0x2016 /* 1-byte-per-pixel, 128-color palette+alpha */
#define VIDEO_CODEC_AP17     0x2017 /* 1-byte-per-pixel, 128-color palette+alpha */
#define VIDEO_CODEC_PA88     0x2018 /* 2-byte-per-pixel, 256-color palette+alpha */
#define VIDEO_CODEC_AP88     0x2019 /* 2-byte-per-pixel, 256-color palette+alpha */




/* Video codec flags (bits for `struct video_codec_specs::vcs_flags') */
#define VIDEO_CODEC_FLAG_NORMAL     0x00 /* Normal flags */
#define VIDEO_CODEC_FLAG_PAL        0x01 /* Does this codec use a palette? (do not combine with `VIDEO_CODEC_FLAG_LUM') */
#define VIDEO_CODEC_FLAG_LUM        0x02 /* Is this a grayscale-only (luminance) or alpha-only codec? (do not combine with `VIDEO_CODEC_FLAG_PAL') */
#define VIDEO_CODEC_FLAG_MSB        0x00 /* When multiple pixels fit into a single byte, they are ordered as "0b01234567" (e.g. pixel at x=1 is defined by "byte & 0x40") */
#define VIDEO_CODEC_FLAG_LSB        0x04 /* When multiple pixels fit into a single byte, they are ordered as "0b76543210" (e.g. pixel at x=1 is defined by "byte & 0x02") */
#define VIDEO_CODEC_FLAG_INTERP8888 0x08 /* When interpreted as uint8_t[4], pixel values can be interpolated directly (as opposed to converting to colors, interpolating,
                                          * then converting back)  This applies  to all  codecs supporting linear  blending, that  also make  use of  8-bits-per-channel.
                                          * The caller need not pre-calculate this flag for `video_codec_fromspecs' */
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
	__ATTR_NONNULL_T((3)) void
	(LIBVIDEO_GFX_FCC *__VIDEO_CODEC_const vc_rambuffer_requirements)(video_dim_t __size_x, video_dim_t __size_y,
	                                                                  struct video_rambuffer_requirements *__restrict __result);

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
 * the the returned codec is in-use.
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
