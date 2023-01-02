/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBVIDEO_CODEC_FORMAT_H
#define _LIBVIDEO_CODEC_FORMAT_H 1

#include <__stdinc.h>

#include <hybrid/__assert.h>

#include <bits/types.h>

#include "api.h"
#include "pixel.h"

#ifdef __cplusplus
#include <__stdcxx.h>

#include "codecs.h"
#endif /* __cplusplus */

__DECL_BEGIN

#ifdef __CC__
struct video_codec;
struct video_palette;

/* Helper macros for doing low-level video data manipulations. */
#define video_format_getpixel(self, line, x)        (*(self)->vf_codec->vc_getpixel)(line, x)
#define video_format_setpixel(self, line, x, pixel) (*(self)->vf_codec->vc_setpixel)(line, x, pixel);
#define video_format_pixel2color(self, pixel)       (*(self)->vf_codec->vc_pixel2color)(self, pixel)
#define video_format_color2pixel(self, color)       (*(self)->vf_codec->vc_color2pixel)(self, color)
#define video_format_getcolor(self, line, x)        video_format_pixel2color(self, video_format_getpixel(self, line, x))
#define video_format_setcolor(self, line, x, color) video_format_setpixel(self, line, x, video_format_color2pixel(self, color))
#define video_format_linecopy(self, dst_line, dst_x, src_line, src_x, num_pixels) \
	(*(self)->vf_codec->vc_linecopy)(dst_line, dst_x, src_line, src_x, num_pixels)
#define video_format_linefill(self, dst_line, dst_x, pixel, num_pixels) \
	(*(self)->vf_codec->vc_linefill)(dst_line, dst_x, pixel, num_pixels)

struct video_format {
	struct video_codec const     *vf_codec;  /* [1..1] Video codec. */
	/*REF*/ struct video_palette *vf_pal;    /* [0..1] Color palette (if applicable) */
#ifdef __cplusplus
public: /* Low-level, memory-based pixel accessor functions. */

	/* Get a pixel (The caller must ensure that the given x/y are in-bounds) */
	__CXX_CLASSMEMBER video_pixel_t LIBVIDEO_CODEC_CC getpixel(__byte_t const *__restrict line, __uintptr_t x) const { return video_format_getpixel(this, line, x); }
	__CXX_CLASSMEMBER video_color_t LIBVIDEO_CODEC_CC getcolor(__byte_t const *__restrict line, __uintptr_t x) const { return video_format_getcolor(this, line, x); }

	/* Set a pixel (The caller must ensure that the given x/y are in-bounds) */
	__CXX_CLASSMEMBER void LIBVIDEO_CODEC_CC setpixel(__byte_t *__restrict line, __uintptr_t x, video_pixel_t pixel) const { video_format_setpixel(this, line, x, pixel); }
	__CXX_CLASSMEMBER void LIBVIDEO_CODEC_CC setcolor(__byte_t *__restrict line, __uintptr_t x, video_color_t color) const { video_format_setcolor(this, line, x, color); }

	/* Convert between color and pixel values. */
	__CXX_CLASSMEMBER video_color_t LIBVIDEO_CODEC_CC pixel2color(video_pixel_t pixel) const { return video_format_pixel2color(this, pixel); }
	__CXX_CLASSMEMBER video_pixel_t LIBVIDEO_CODEC_CC color2pixel(video_color_t color) const { return video_format_color2pixel(this, color); }

	/* Copy `num_pixels' neighboring (the caller must ensure that all coords are in-bounds) */
	__CXX_CLASSMEMBER void LIBVIDEO_CODEC_CC linecopy(__byte_t *__restrict dst_line, __uintptr_t dst_x,
	                                                  __byte_t const *__restrict src_line, __uintptr_t src_x,
	                                                  __size_t num_pixels) const {
		video_format_linecopy(this, dst_line, dst_x, src_line, src_x, num_pixels);
	}

	/* Fill `num_pixels' neighboring (the caller must ensure that all coords are in-bounds) */
	__CXX_CLASSMEMBER void LIBVIDEO_CODEC_CC linefill(__byte_t *__restrict line, __uintptr_t dst_x,
	                                                  video_pixel_t pixel, __size_t num_pixels) const {
		video_format_linefill(this, line, dst_x, pixel, num_pixels);
	}

#endif /* __cplusplus */
};

#endif /* __CC__ */


__DECL_END

#endif /* !_LIBVIDEO_CODEC_FORMAT_H */
