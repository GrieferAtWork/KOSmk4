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
#ifndef _LIBVIDEO_PIXEL_H
#define _LIBVIDEO_PIXEL_H 1

#include <__stdinc.h>

#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

__DECL_BEGIN

/* Encoding of the general-purpose video_color_t datatype.
 * NOTE: `video_color_t' is always encoded to  match
 *       the memory-layout of `VIDEO_CODEC_RGBA8888' */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define VIDEO_COLOR_RED_MASK    __UINT32_C(0x000000ff)
#define VIDEO_COLOR_RED_SHIFT   0
#define VIDEO_COLOR_GREEN_MASK  __UINT32_C(0x0000ff00)
#define VIDEO_COLOR_GREEN_SHIFT 8
#define VIDEO_COLOR_BLUE_MASK   __UINT32_C(0x00ff0000)
#define VIDEO_COLOR_BLUE_SHIFT  16
#define VIDEO_COLOR_ALPHA_MASK  __UINT32_C(0xff000000)
#define VIDEO_COLOR_ALPHA_SHIFT 24
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define VIDEO_COLOR_RED_MASK    __UINT32_C(0xff000000)
#define VIDEO_COLOR_RED_SHIFT   24
#define VIDEO_COLOR_GREEN_MASK  __UINT32_C(0x00ff0000)
#define VIDEO_COLOR_GREEN_SHIFT 16
#define VIDEO_COLOR_BLUE_MASK   __UINT32_C(0x0000ff00)
#define VIDEO_COLOR_BLUE_SHIFT  8
#define VIDEO_COLOR_ALPHA_MASK  __UINT32_C(0x000000ff)
#define VIDEO_COLOR_ALPHA_SHIFT 0
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */

/* Extract individual channels from a given `color' */
#define VIDEO_COLOR_GET_RED(color)   __CCAST(video_channel_t)(((color) & VIDEO_COLOR_RED_MASK) >> VIDEO_COLOR_RED_SHIFT)
#define VIDEO_COLOR_GET_GREEN(color) __CCAST(video_channel_t)(((color) & VIDEO_COLOR_GREEN_MASK) >> VIDEO_COLOR_GREEN_SHIFT)
#define VIDEO_COLOR_GET_BLUE(color)  __CCAST(video_channel_t)(((color) & VIDEO_COLOR_BLUE_MASK) >> VIDEO_COLOR_BLUE_SHIFT)
#define VIDEO_COLOR_GET_ALPHA(color) __CCAST(video_channel_t)(((color) & VIDEO_COLOR_ALPHA_MASK) >> VIDEO_COLOR_ALPHA_SHIFT)

/* Construct a custom RGBA video color. */
#define VIDEO_COLOR_RGBA(r, g, b, a)                          \
	((__CCAST(video_color_t)(r) << VIDEO_COLOR_RED_SHIFT) |   \
	 (__CCAST(video_color_t)(g) << VIDEO_COLOR_GREEN_SHIFT) | \
	 (__CCAST(video_color_t)(b) << VIDEO_COLOR_BLUE_SHIFT) |  \
	 (__CCAST(video_color_t)(a) << VIDEO_COLOR_ALPHA_SHIFT))

/* Construct a custom RGB video color. */
#define VIDEO_COLOR_RGB(r, g, b)                              \
	((__CCAST(video_color_t)(r) << VIDEO_COLOR_RED_SHIFT) |   \
	 (__CCAST(video_color_t)(g) << VIDEO_COLOR_GREEN_SHIFT) | \
	 (__CCAST(video_color_t)(b) << VIDEO_COLOR_BLUE_SHIFT) |  \
	 VIDEO_COLOR_ALPHA_MASK)

/* Check if the given "color" should be treated as being "transparent" / "opaque" */
#define VIDEO_COLOR_ISTRANSPARENT(color) (((color) & VIDEO_COLOR_ALPHA_MASK) == 0)
#define VIDEO_COLOR_ISOPAQUE(color)      (((color) & VIDEO_COLOR_ALPHA_MASK) == VIDEO_COLOR_ALPHA_MASK)

/* Standard video colors */
#define VIDEO_COLOR_BLACK      VIDEO_COLOR_RGB(0x00, 0x00, 0x00)
#define VIDEO_COLOR_NAVY       VIDEO_COLOR_RGB(0x00, 0x00, 0xa8)
#define VIDEO_COLOR_GREEN      VIDEO_COLOR_RGB(0x00, 0xa8, 0x00)
#define VIDEO_COLOR_TEAL       VIDEO_COLOR_RGB(0x00, 0xa8, 0xa8)
#define VIDEO_COLOR_MAROON     VIDEO_COLOR_RGB(0xa8, 0x00, 0x00)
#define VIDEO_COLOR_PURPLE     VIDEO_COLOR_RGB(0xa8, 0x00, 0xa8)
#define VIDEO_COLOR_OLIVE      VIDEO_COLOR_RGB(0xa8, 0x57, 0x00)
#define VIDEO_COLOR_SILVER     VIDEO_COLOR_RGB(0xa8, 0xa8, 0xa8)
#define VIDEO_COLOR_GREY       VIDEO_COLOR_RGB(0x57, 0x57, 0x57)
#define VIDEO_COLOR_BLUE       VIDEO_COLOR_RGB(0x57, 0x57, 0xff)
#define VIDEO_COLOR_LIME       VIDEO_COLOR_RGB(0x57, 0xff, 0x57)
#define VIDEO_COLOR_AQUA       VIDEO_COLOR_RGB(0x57, 0xff, 0xff)
#define VIDEO_COLOR_RED        VIDEO_COLOR_RGB(0xff, 0x57, 0x57)
#define VIDEO_COLOR_FUCHSIA    VIDEO_COLOR_RGB(0xff, 0x57, 0xff)
#define VIDEO_COLOR_YELLOW     VIDEO_COLOR_RGB(0xff, 0xff, 0x57)
#define VIDEO_COLOR_WHITE      VIDEO_COLOR_RGB(0xff, 0xff, 0xff)
#define VIDEO_COLOR_LIGHT_GRAY VIDEO_COLOR_SILVER
#define VIDEO_COLOR_DARK_GRAY  VIDEO_COLOR_GREY


/* Sizes of unified video pixel/color types */
#define __SIZEOF_VIDEO_COLOR_T__       4
#define __SIZEOF_VIDEO_PIXEL_T__       4
#define __SIZEOF_VIDEO_CHANNEL_T__     1
#define __SIZEOF_VIDEO_TWOCHANNELS_T__ __SIZEOF_INT_FAST16_T__

/* The min/max values for `video_channel_t' */
#define VIDEO_CHANNEL_MIN 0x00
#define VIDEO_CHANNEL_MAX 0xff

#ifdef __CC__
typedef __UINT32_TYPE__ video_color_t;  /* General-purpose */
typedef __UINT32_TYPE__ video_pixel_t;  /* Codec-specific */
typedef __UINT8_TYPE__ video_channel_t; /* Singular color channel of "video_color_t" */
typedef __UINT_FAST16_TYPE__ video_twochannels_t; /* Word with sufficient space for 2 video_channel_t */
typedef __INT_FAST16_TYPE__ video_stwochannels_t; /* Word with sufficient space for 2 video_channel_t */
#endif /* __CC__ */






/* Encoding of the general-purpose video_color_t datatype.
 * NOTE: `video_color_t' is always encoded to  match
 *       the memory-layout of `VIDEO_CODEC_RGBA8888' */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define VIDEO_COLOR64_RED_MASK     __UINT64_C(0x000000000000ffff)
#define VIDEO_COLOR64_RED_SHIFT    0
#define VIDEO_COLOR64_GREEN_MASK   __UINT64_C(0x00000000ffff0000)
#define VIDEO_COLOR64_GREEN_SHIFT  16
#define VIDEO_COLOR64_BLUE_MASK    __UINT64_C(0x0000ffff00000000)
#define VIDEO_COLOR64_BLUE_SHIFT   32
#define VIDEO_COLOR64_ALPHA_MASK   __UINT64_C(0xffff000000000000)
#define VIDEO_COLOR64_ALPHA_SHIFT  48
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define VIDEO_COLOR64_RED_MASK     __UINT64_C(0xffff000000000000)
#define VIDEO_COLOR64_RED_SHIFT    48
#define VIDEO_COLOR64_GREEN_MASK   __UINT64_C(0x0000ffff00000000)
#define VIDEO_COLOR64_GREEN_SHIFT  32
#define VIDEO_COLOR64_BLUE_MASK    __UINT64_C(0x00000000ffff0000)
#define VIDEO_COLOR64_BLUE_SHIFT   16
#define VIDEO_COLOR64_ALPHA_MASK   __UINT64_C(0x000000000000ffff)
#define VIDEO_COLOR64_ALPHA_SHIFT  0
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */

/* Extract individual channels from a given `color' */
#define VIDEO_COLOR64_GET_RED(color)   __CCAST(video_channel16_t)(((color) & VIDEO_COLOR64_RED_MASK) >> VIDEO_COLOR64_RED_SHIFT)
#define VIDEO_COLOR64_GET_GREEN(color) __CCAST(video_channel16_t)(((color) & VIDEO_COLOR64_GREEN_MASK) >> VIDEO_COLOR64_GREEN_SHIFT)
#define VIDEO_COLOR64_GET_BLUE(color)  __CCAST(video_channel16_t)(((color) & VIDEO_COLOR64_BLUE_MASK) >> VIDEO_COLOR64_BLUE_SHIFT)
#define VIDEO_COLOR64_GET_ALPHA(color) __CCAST(video_channel16_t)(((color) & VIDEO_COLOR64_ALPHA_MASK) >> VIDEO_COLOR64_ALPHA_SHIFT)

/* Construct a custom RGBA, 64-bit video color. */
#define VIDEO_COLOR64_RGBA(r, g, b, a)                            \
	((__CCAST(video_color64_t)(r) << VIDEO_COLOR64_RED_SHIFT) |   \
	 (__CCAST(video_color64_t)(g) << VIDEO_COLOR64_GREEN_SHIFT) | \
	 (__CCAST(video_color64_t)(b) << VIDEO_COLOR64_BLUE_SHIFT) |  \
	 (__CCAST(video_color64_t)(a) << VIDEO_COLOR64_ALPHA_SHIFT))

/* Construct a custom RGB, 64-bit video color. */
#define VIDEO_COLOR64_RGB(r, g, b)                                \
	((__CCAST(video_color64_t)(r) << VIDEO_COLOR64_RED_SHIFT) |   \
	 (__CCAST(video_color64_t)(g) << VIDEO_COLOR64_GREEN_SHIFT) | \
	 (__CCAST(video_color64_t)(b) << VIDEO_COLOR64_BLUE_SHIFT) |  \
	 VIDEO_COLOR64_ALPHA_MASK)

/* Check if the given "color" should be treated as being "transparent" / "opaque" */
#define VIDEO_COLOR64_ISTRANSPARENT(color) (((color) & VIDEO_COLOR64_ALPHA_MASK) == 0)
#define VIDEO_COLOR64_ISOPAQUE(color)      (((color) & VIDEO_COLOR64_ALPHA_MASK) == VIDEO_COLOR64_ALPHA_MASK)

/* Convert between regular `video_color_t' and `video_color64_t' */
#define VIDEO_COLOR64_FROM_COLOR(color)                                                                   \
	((__CCAST(video_color64_t)__UINT64_C(0x0000000000000101) * __CCAST(video_channel_t)((color))) |       \
	 (__CCAST(video_color64_t)__UINT64_C(0x0000000001010000) * __CCAST(video_channel_t)((color) >> 8)) |  \
	 (__CCAST(video_color64_t)__UINT64_C(0x0000010100000000) * __CCAST(video_channel_t)((color) >> 16)) | \
	 (__CCAST(video_color64_t)__UINT64_C(0x0101000000000000) * __CCAST(video_channel_t)((color) >> 24)))
#define VIDEO_COLOR_FROM_COLOR64(color)                                      \
	((__CCAST(video_color_t)__CCAST(video_channel_t)((color) >> 56) << 24) | \
	 (__CCAST(video_color_t)__CCAST(video_channel_t)((color) >> 40) << 16) | \
	 (__CCAST(video_color_t)__CCAST(video_channel_t)((color) >> 24) << 8) |  \
	 (__CCAST(video_color_t)__CCAST(video_channel_t)((color) >> 8)))


/* Sizes of unified video pixel/color types */
#define __SIZEOF_VIDEO_COLOR64_T__       8
#define __SIZEOF_VIDEO_PIXEL64_T__       8
#define __SIZEOF_VIDEO_CHANNEL16_T__     2
#define __SIZEOF_VIDEO_TWOCHANNELS16_T__ __SIZEOF_INT_FAST32_T__

/* The min/max values for `video_channel_t' */
#define VIDEO_CHANNEL16_MIN 0x0000
#define VIDEO_CHANNEL16_MAX 0xffff

#ifdef __CC__
typedef __UINT64_TYPE__ video_color64_t;            /* General-purpose */
typedef __UINT64_TYPE__ video_pixel64_t;            /* Codec-specific */
typedef __UINT16_TYPE__ video_channel16_t;          /* Singular color channel of "video_color64_t" */
typedef __UINT_FAST32_TYPE__ video_twochannels16_t; /* Word with sufficient space for 2 video_channel16_t */
typedef __INT_FAST32_TYPE__ video_stwochannels16_t; /* Word with sufficient space for 2 video_channel16_t */
#endif /* __CC__ */

__DECL_END

#endif /* !_LIBVIDEO_PIXEL_H */
