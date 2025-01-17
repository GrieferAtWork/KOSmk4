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
#ifndef _LIBVIDEO_CODEC_CODECS_H
#define _LIBVIDEO_CODEC_CODECS_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "pixel.h"

__DECL_BEGIN

#define VIDEO_CODEC_NONE       0x0000 /* Invalid codec. */

/* Gray-scale */
#define VIDEO_CODEC_GRAY2_LSB  0x1001 /* 1-bit-per-pixel, least-significant-bit-first, black/white */
#define VIDEO_CODEC_GRAY2_MSB  0x1002 /* 1-bit-per-pixel, most-significant-bit-first, black/white */
#define VIDEO_CODEC_GRAY4_LSB  0x1003 /* 2-bit-per-pixel, least-significant-bit-first, 4-color grayscale (0=black; 3=white) */
#define VIDEO_CODEC_GRAY4_MSB  0x1004 /* 2-bit-per-pixel, most-significant-bit-first, 4-color grayscale (0=black; 3=white) */
#define VIDEO_CODEC_GRAY16_LSB 0x1005 /* 4-bit-per-pixel, least-significant-bit-first, 16-color grayscale (0=black; 15=white) */
#define VIDEO_CODEC_GRAY16_MSB 0x1006 /* 4-bit-per-pixel, most-significant-bit-first, 16-color grayscale (0=black; 15=white) */
#define VIDEO_CODEC_GRAY256    0x1007 /* 8-bit-per-pixel, 256-color grayscale (0=black; 255=white) */

/* Full-color */
#define VIDEO_CODEC_RGBA8888   0x2001
#define VIDEO_CODEC_RGBX8888   0x2002
#define VIDEO_CODEC_ARGB8888   0x2003
#define VIDEO_CODEC_XRGB8888   0x2004
#define VIDEO_CODEC_ABGR8888   0x2005
#define VIDEO_CODEC_XBGR8888   0x2006
#define VIDEO_CODEC_BGRA8888   0x2007
#define VIDEO_CODEC_BGRX8888   0x2008
#define VIDEO_CODEC_RGB888     0x2009
#define VIDEO_CODEC_BGR888     0x200a
#define VIDEO_CODEC_RGBA4444   0x2011
#define VIDEO_CODEC_RGBX4444   0x2012
#define VIDEO_CODEC_ARGB4444   0x2013
#define VIDEO_CODEC_XRGB4444   0x2014
#define VIDEO_CODEC_ABGR4444   0x2015
#define VIDEO_CODEC_XBGR4444   0x2016
#define VIDEO_CODEC_BGRA4444   0x2017
#define VIDEO_CODEC_BGRX4444   0x2018
#define VIDEO_CODEC_RGB565     0x2019
#define VIDEO_CODEC_BGR565     0x201a
#define VIDEO_CODEC_RGBA5551   0x2021
#define VIDEO_CODEC_RGBX5551   0x2022
#define VIDEO_CODEC_ARGB1555   0x2023
#define VIDEO_CODEC_XRGB1555   0x2024
#define VIDEO_CODEC_ABGR1555   0x2025
#define VIDEO_CODEC_XBGR1555   0x2026
#define VIDEO_CODEC_BGRA5551   0x2027
#define VIDEO_CODEC_BGRX5551   0x2028

/* Palette-driven */
#define VIDEO_CODEC_PAL2_LSB   0xf001 /* 2-color palette, least-significant-bit-first, (1-bit pixels) */
#define VIDEO_CODEC_PAL2_MSB   0xf011 /* 2-color palette, most-significant-bit-first, (1-bit pixels) */
#define VIDEO_CODEC_PAL4_LSB   0xf002 /* 4-color palette, least-significant-bit-first, (2-bit pixels) */
#define VIDEO_CODEC_PAL4_MSB   0xf012 /* 4-color palette, most-significant-bit-first, (2-bit pixels) */
#define VIDEO_CODEC_PAL16_LSB  0xf004 /* 16-color palette, least-significant-bit-first, (4-bit pixels) */
#define VIDEO_CODEC_PAL16_MSB  0xf014 /* 16-color palette, most-significant-bit-first, (4-bit pixels) */
#define VIDEO_CODEC_PAL256     0xf008 /* 256-color palette (8-bit pixels) */

/* Check if a given video codec uses a palette */
#define VIDEO_CODEC_HASPAL(x) (((x) & 0xf000) == 0xf000)
/* Returns the number of colors used by a palette-driven video codec. */
#define VIDEO_CODEC_PALSIZ(x) (__CCAST(__size_t)1 << ((x) & 0xf))


/* Normal codec flags. */
#define VIDEO_CODEC_FLAG_NORMAL 0x0000

#ifdef __CC__
typedef __uint16_t video_codec_t; /* One of `VIDEO_CODEC_*' */

struct video_rambuffer_requirements {
	__size_t vbs_bufsize; /* Minimal buffer size (in bytes) */
	__size_t vbs_stride;  /* Required scanline stride (in bytes) */
};

struct video_format;
struct video_codec {
	/* Video format operations. */
	video_codec_t vc_codec; /* [const] Video format codec (One of `VIDEO_FORMAT_*') */
	__uint16_t   _vc_flags; /* [const] Video format flags (Set of `VIDEO_CODEC_FLAG_*') */
	__uint32_t    vc_align; /* [!0][const] Byte alignment requirements for base_addr/stride of buffers using this codec. */
	/* NOTE: _ALL_ Callbacks are always [1..1] */

	/* Calculate minimal ram-buffer requirements for a graphic with the given dimensions.
	 * Note that in addition, a ram-buffer needs a minimal alignment of `vc_align' bytes. */
	__ATTR_NONNULL_T((3)) void
	(LIBVIDEO_CODEC_CC *vc_rambuffer_requirements)(__size_t size_x, __size_t size_y,
	                                               struct video_rambuffer_requirements *__restrict result);

	/* Get a pixel (The caller must ensure that the given x is in-bounds) */
	__ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_pixel_t
	(LIBVIDEO_CODEC_CC *vc_getpixel)(__byte_t const *__restrict line, __uintptr_t x);

	/* Set a pixel (The caller must ensure that the given x is in-bounds) */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_CODEC_CC *vc_setpixel)(__byte_t *__restrict line,
	                                 __uintptr_t x, video_pixel_t pixel);

	/* Copy `num_pixels' neighboring (the caller must ensure that all coords are in-bounds) */
	__ATTR_NONNULL_T((1, 3)) void
	(LIBVIDEO_CODEC_CC *vc_linecopy)(__byte_t *__restrict dst_line, __uintptr_t dst_x,
	                                 __byte_t const *__restrict src_line, __uintptr_t src_x,
	                                 __size_t num_pixels);

	/* Fill `num_pixels' neighboring (the caller must ensure that all coords are in-bounds) */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_CODEC_CC *vc_linefill)(__byte_t *__restrict line, __uintptr_t dst_x,
	                                 video_pixel_t pixel, __size_t num_pixels);

	/* Convert between color and pixel values. */
	__ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_color_t
	(LIBVIDEO_CODEC_CC *vc_pixel2color)(struct video_format const *__restrict self,
	                                    video_pixel_t pixel);
	__ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) video_pixel_t
	(LIBVIDEO_CODEC_CC *vc_color2pixel)(struct video_format const *__restrict self,
	                                    video_color_t color);
};


/* Lookup the interface for a given codec, or return NULL if the codec isn't supported. */
typedef __ATTR_CONST_T __ATTR_WUNUSED_T struct video_codec const *
(LIBVIDEO_CODEC_CC *PVIDEO_CODEC_LOOKUP)(video_codec_t codec);
#ifdef LIBVIDEO_CODEC_WANT_PROTOTYPES
LIBVIDEO_CODEC_DECL __ATTR_WUNUSED __ATTR_CONST struct video_codec const *
(LIBVIDEO_CODEC_CC video_codec_lookup)(video_codec_t codec);
#endif /* LIBVIDEO_CODEC_WANT_PROTOTYPES */

#endif /* __CC__ */


__DECL_END

#endif /* !_LIBVIDEO_CODEC_CODECS_H */
