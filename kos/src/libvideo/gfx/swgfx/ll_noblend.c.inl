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
#ifndef GUARD_LIBVIDEO_GFX_SWGFX_LL_NOBLEND_C_INL
#define GUARD_LIBVIDEO_GFX_SWGFX_LL_NOBLEND_C_INL 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <inttypes.h>
#include <stdint.h>

#include <libvideo/color.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/surface.h>
#include <libvideo/types.h>

#include "../gfx-debug.h"
#include "../gfx-utils.h"
#include "ll.h"

DECL_BEGIN

/************************************************************************/
/* INTERNAL API                                                         */
/************************************************************************/

/* Low-level, optimized GFX functions using `struct video_lock' (if available):
 * - *noblend*: Usable only when the relevant GFX's blend-mode is `GFX_BLENDMODE_OVERRIDE' */

PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend__line_llhh__bypixel(struct video_gfx const *__restrict self,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_dim_t size_x, video_dim_t size_y,
                                           video_pixel_t pixel) {
	video_dim_t step;
	step = 0;
	if (size_x > size_y) {
		video_coord_t line_lox = 0;
		do {
			video_coord_t line_hix = (video_dim_t)(((uint64_t)size_x * (step + 1)) / size_y);
			video_coord_t line_x = dst_x + line_lox;
			video_coord_t line_y = dst_y + step;
			video_dim_t length = line_hix - line_lox;
			do {
				LL_setpixel(self, line_x, line_y, pixel);
				++line_x;
			} while (--length);
			line_lox = line_hix;
		} while (++step < size_y);
	} else if (size_x < size_y) {
		video_coord_t line_loy = 0;
		do {
			video_coord_t line_hiy = (video_dim_t)(((uint64_t)size_y * (step + 1)) / size_x);
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y + line_loy;
			video_dim_t length = line_hiy - line_loy;
			do {
				LL_setpixel(self, line_x, line_y, pixel);
				++line_y;
			} while (--length);
			line_loy = line_hiy;
		} while (++step < size_x);
	} else {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y + step;
			LL_setpixel(self, line_x, line_y, pixel);
		} while (++step < size_x);
	}
}


INTERN ATTR_IN(1) void CC
libvideo_swgfx_noblend__line_llhh(struct video_gfx const *__restrict self,
                                  video_coord_t dst_x, video_coord_t dst_y,
                                  video_dim_t size_x, video_dim_t size_y,
                                  video_color_t color) {
	struct video_regionlock lock;
	struct video_surface const *surface = video_gfx_assurface(self);
	struct video_buffer *buffer = video_surface_getbuffer(surface);
	video_pixel_t pixel = video_surface_color2pixel(surface, color);
	gfx_assert(size_x > 0);
	gfx_assert(size_y > 0);
	if likely(LL_wlockregion(buffer, &lock, dst_x, dst_y, size_x, size_y)) {
		video_dim_t step;
		byte_t *line = video_regionlock_getdata(&lock);
		step = 0;
		if (size_x > size_y) {
			video_coord_t line_lox = 0;
			video_codec_linefill_t vc_linefill = video_buffer_getcodec(buffer)->vc_linefill;
			do {
				video_coord_t line_hix = (video_dim_t)(((uint64_t)size_x * (step + 1)) / size_y);
				(*vc_linefill)(line, video_regionlock_getxbase(&lock) + line_lox, pixel, line_hix - line_lox);
				line_lox = line_hix;
				line += video_regionlock_getstride(&lock);
			} while (++step < size_y);
		} else if (size_x < size_y) {
			video_coord_t line_loy = 0;
			video_codec_vertfill_t vc_vertfill = video_buffer_getcodec(buffer)->vc_vertfill;
			do {
				video_coord_t line_hiy = (video_dim_t)(((uint64_t)size_y * (step + 1)) / size_x);
				video_dim_t length = line_hiy - line_loy;
				(*vc_vertfill)(line,
				               video_regionlock_getxbase(&lock) + step,
				               video_regionlock_getstride(&lock),
				               pixel, length);
				line_loy = line_hiy;
				line += length * video_regionlock_getstride(&lock);
			} while (++step < size_x);
		} else {
			video_codec_setpixel_t vc_setpixel;
			vc_setpixel = video_buffer_getcodec(buffer)->vc_setpixel;
			do {
				(*vc_setpixel)(line, video_regionlock_getxbase(&lock) + step, pixel);
				line += video_regionlock_getstride(&lock);
			} while (++step != size_y);
		}
		LL_unlockregion(buffer, &lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_swgfx_noblend__line_llhh__bypixel(self, dst_x, dst_y, size_x, size_y, pixel);
	}
}

PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend__line_lhhl__bypixel(struct video_gfx const *__restrict self,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_dim_t size_x, video_dim_t size_y,
                                           video_pixel_t pixel) {
	video_dim_t step;
	step = 0;
	if (size_x > size_y) {
		video_coord_t line_lox = 0;
		do {
			video_coord_t line_hix = (video_dim_t)(((uint64_t)size_x * (step + 1)) / size_y);
			video_coord_t line_x = dst_x + line_lox;
			video_coord_t line_y = dst_y - step;
			video_dim_t length = line_hix - line_lox;
			do {
				LL_setpixel(self, line_x, line_y, pixel);
				++line_x;
			} while (--length);
			line_lox = line_hix;
		} while (++step < size_y);
	} else if (size_x < size_y) {
		video_coord_t line_loy = 0;
		do {
			video_coord_t line_hiy = (video_dim_t)(((uint64_t)size_y * (step + 1)) / size_x);
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y - line_hiy + 1;
			video_dim_t length = line_hiy - line_loy;
			do {
				LL_setpixel(self, line_x, line_y, pixel);
				++line_y;
			} while (--length);
			line_loy = line_hiy;
		} while (++step < size_x);
	} else {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y - step;
			LL_setpixel(self, line_x, line_y, pixel);
		} while (++step != size_x);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_noblend__line_lhhl(struct video_gfx const *__restrict self,
                                  video_coord_t dst_x, video_coord_t dst_y,
                                  video_dim_t size_x, video_dim_t size_y,
                                  video_color_t color) {
	struct video_regionlock lock;
	struct video_surface const *surface = video_gfx_assurface(self);
	struct video_buffer *buffer = video_surface_getbuffer(surface);
	video_pixel_t pixel = video_surface_color2pixel(surface, color);
	gfx_assert(size_x > 0);
	gfx_assert(size_y > 0);
	if likely(LL_wlockregion(buffer, &lock, dst_x, dst_y - (size_y - 1), size_x, size_y)) {
		video_dim_t step;
		byte_t *line = video_regionlock_getline(&lock, size_y - 1);
		step = 0;
		if (size_x > size_y) {
			video_coord_t line_lox = 0;
			video_codec_linefill_t vc_linefill = video_buffer_getcodec(buffer)->vc_linefill;
			do {
				video_coord_t line_hix = (video_dim_t)(((uint64_t)size_x * (step + 1)) / size_y);
				(*vc_linefill)(line, video_regionlock_getxbase(&lock) + line_lox,
				               pixel, line_hix - line_lox);
				line_lox = line_hix;
				line -= video_regionlock_getstride(&lock);
			} while (++step < size_y);
		} else if (size_x < size_y) {
			video_coord_t line_loy = 0;
			video_codec_vertfill_t vc_vertfill = video_buffer_getcodec(buffer)->vc_vertfill;
			line += video_regionlock_getstride(&lock);
			do {
				video_coord_t line_hiy = (video_dim_t)(((uint64_t)size_y * (step + 1)) / size_x);
				video_dim_t length = line_hiy - line_loy;
				line -= length * video_regionlock_getstride(&lock);
				(*vc_vertfill)(line,
				               video_regionlock_getxbase(&lock) + step,
				               video_regionlock_getstride(&lock),
				               pixel, length);
				line_loy = line_hiy;
			} while (++step < size_x);
		} else {
			video_codec_setpixel_t vc_setpixel;
			vc_setpixel = video_buffer_getcodec(buffer)->vc_setpixel;
			do {
				(*vc_setpixel)(line, video_regionlock_getxbase(&lock) + step, pixel);
				line -= video_regionlock_getstride(&lock);
			} while (++step != size_y);
		}
		LL_unlockregion(buffer, &lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_swgfx_noblend__line_lhhl__bypixel(self, dst_x, dst_y, size_x, size_y, pixel);
	}
}


PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend__line_h__bypixel(struct video_gfx const *__restrict self,
                                        video_coord_t dst_x, video_coord_t dst_y,
                                        video_dim_t length, video_pixel_t pixel) {
	do {
		LL_setpixel(self, dst_x, dst_y, pixel);
		++dst_x;
	} while (--length);
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_noblend__line_h(struct video_gfx const *__restrict self,
                               video_coord_t dst_x, video_coord_t dst_y,
                               video_dim_t length, video_color_t color) {
	struct video_regionlock lock;
	struct video_surface const *surface = video_gfx_assurface(self);
	struct video_buffer *buffer = video_surface_getbuffer(surface);
	video_pixel_t pixel = video_surface_color2pixel(surface, color);
	gfx_assert(length > 0);
	if likely(LL_wlockregion(buffer, &lock, dst_x, dst_y, length, 1)) {
		video_codec_linefill_t vc_linefill = video_buffer_getcodec(buffer)->vc_linefill;
		(*vc_linefill)(video_regionlock_getdata(&lock),
		               video_regionlock_getxbase(&lock),
		               pixel, length);
		LL_unlockregion(buffer, &lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_swgfx_noblend__line_h__bypixel(self, dst_x, dst_y, length, pixel);
	}
}

PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend__line_v__bypixel(struct video_gfx const *__restrict self,
                                        video_coord_t dst_x, video_coord_t dst_y,
                                        video_dim_t length, video_pixel_t pixel) {
	do {
		LL_setpixel(self, dst_x, dst_y, pixel);
		++dst_y;
	} while (--length);
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_noblend__line_v(struct video_gfx const *__restrict self,
                               video_coord_t dst_x, video_coord_t dst_y,
                               video_dim_t length, video_color_t color) {
	struct video_regionlock lock;
	struct video_surface const *surface = video_gfx_assurface(self);
	struct video_buffer *buffer = video_surface_getbuffer(surface);
	video_pixel_t pixel = video_surface_color2pixel(surface, color);
	if likely(LL_wlockregion(buffer, &lock, dst_x, dst_y, 1, length)) {
		video_codec_vertfill_t vc_vertfill = video_buffer_getcodec(buffer)->vc_vertfill;
		(*vc_vertfill)(video_regionlock_getdata(&lock),
		               video_regionlock_getxbase(&lock),
		               video_regionlock_getstride(&lock),
		               pixel, length);
		LL_unlockregion(buffer, &lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_swgfx_noblend__line_v__bypixel(self, dst_x, dst_y, length, pixel);
	}
}

PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend__fill__bypixel(struct video_gfx const *__restrict self,
                                      video_coord_t dst_x, video_coord_t dst_y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      video_pixel_t pixel) {
	do {
		video_coord_t x = 0;
		do {
			LL_setpixel(self, dst_x + x, dst_y, pixel);
		} while (++x < size_x);
		++dst_y;
	} while (--size_y);
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_noblend__fill(struct video_gfx const *__restrict self,
                             video_coord_t dst_x, video_coord_t dst_y,
                             video_dim_t size_x, video_dim_t size_y,
                             video_color_t color) {
	struct video_regionlock lock;
	struct video_surface const *surface = video_gfx_assurface(self);
	struct video_buffer *buffer = video_surface_getbuffer(surface);
	video_pixel_t pixel = video_surface_color2pixel(surface, color);
	gfx_assert(size_x > 0);
	gfx_assert(size_y > 0);
	TRACE_START("swgfx_noblend__fill("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, color: %#" PRIxCOL ")\n",
	            dst_x, dst_y, size_x, size_y, color);
	if likely(LL_wlockregion(buffer, &lock, dst_x, dst_y, size_x, size_y)) {
		/* Use the low-level linefill operator from the video codec */
		video_codec_rectfill_t vc_rectfill = video_buffer_getcodec(buffer)->vc_rectfill;
		(*vc_rectfill)(video_regionlock_getdata(&lock),
		               video_regionlock_getxbase(&lock),
		               video_regionlock_getstride(&lock),
		               pixel, size_x, size_y);
		LL_unlockregion(buffer, &lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_swgfx_noblend__fill__bypixel(self, dst_x, dst_y, size_x, size_y, pixel);
	}
	TRACE_END("swgfx_noblend__fill()");
}

PRIVATE ATTR_IN(1) ATTR_IN(6) void CC
libvideo_swgfx_noblend_interp8888__gradient__bypixel(struct video_gfx const *__restrict self,
                                                     video_coord_t dst_x_, video_coord_t dst_y_,
                                                     video_dim_t size_x_, video_dim_t size_y_,
                                                     video_pixel_t pixels[2][2]) {
#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y) \
	{                                                                             \
		video_pixel_t out = pixels[src_y][src_x];                                 \
		LL_fill(self, dst_x, dst_y, dst_size_x, dst_size_y, out);                 \
	}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                       \
		video_pixel_t src_y0_x0 = pixels[src_y][src_x0];                                    \
		video_pixel_t src_y0_x1 = pixels[src_y][src_x1];                                    \
		video_pixel_t out       = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);   \
		LL_line_v(self, dst_x, dst_y, dst_size_y, out);                                     \
	}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                       \
		video_pixel_t src_y0_x0 = pixels[src_y0][src_x];                                    \
		video_pixel_t src_y1_x0 = pixels[src_y1][src_x];                                    \
		video_pixel_t out       = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);   \
		LL_line_h(self, dst_x, dst_y, dst_size_x, out);                                     \
	}

#define pixel_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                 \
		video_pixel_t src_y0_x0 = pixels[src_y0][src_x0];                                             \
		video_pixel_t src_y0_x1 = pixels[src_y0][src_x1];                                             \
		video_pixel_t src_y1_x0 = pixels[src_y1][src_x0];                                             \
		video_pixel_t src_y1_x1 = pixels[src_y1][src_x1];                                             \
		video_pixel_t out       = interpolate_2d(src_y0_x0, src_y0_x1,                                \
		                                         src_y1_x0, src_y1_x1,                                \
		                                         frac_x0, frac_x1,                                    \
		                                         frac_y0, frac_y1);                                   \
		LL_setpixel(self, dst_x, dst_y, out);                                                         \
	}
	GFX_LINEAR_STRETCH(dst_x_, dst_y_, size_x_, size_y_,
	                   0, 0, 2, 2,
	                   pixel_blend_xmin_ymin,
	                   pixel_blend_ymin,
	                   pixel_blend_xmax_ymin,
	                   pixel_blend_xmin,
	                   pixel_blend,
	                   pixel_blend_xmax,
	                   pixel_blend_xmin_ymax,
	                   pixel_blend_ymax,
	                   pixel_blend_xmax_ymax);
#undef pixel_blend_xmin_ymin
#undef pixel_blend_ymin
#undef pixel_blend_xmax_ymin
#undef pixel_blend_xmin
#undef pixel_blend
#undef pixel_blend_xmax
#undef pixel_blend_xmin_ymax
#undef pixel_blend_ymax
#undef pixel_blend_xmax_ymax
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
libvideo_swgfx_noblend_interp8888__gradient(struct video_gfx const *__restrict self,
                                            video_coord_t dst_x_, video_coord_t dst_y_,
                                            video_dim_t size_x_, video_dim_t size_y_,
                                            video_color_t const colors[2][2]) {
	struct video_regionlock lock;
	struct video_surface const *surface;
	struct video_buffer *buffer;
	video_color_t pixels[2][2];

	/* Check for special case: not actually a 4-color gradient */
	if (colors[0][0] == colors[0][1] && colors[1][0] == colors[1][1]) {
		libvideo_swgfx_noblend_interp8888__gradient_v(self, dst_x_, dst_y_, size_x_, size_y_,
		                                                 colors[0][0], colors[1][0]);
		return;
	} else if (colors[0][0] == colors[1][0] && colors[0][1] == colors[1][1]) {
		libvideo_swgfx_noblend_interp8888__gradient_h(self, dst_x_, dst_y_, size_x_, size_y_,
		                                                 colors[0][0], colors[0][1]);
		return;
	}

	/* Convert colors to pixels */
	surface = video_gfx_assurface(self);
	buffer = video_surface_getbuffer(surface);
	pixels[0][0] = video_surface_color2pixel(surface, colors[0][0]);
	pixels[0][1] = video_surface_color2pixel(surface, colors[0][1]);
	pixels[1][0] = video_surface_color2pixel(surface, colors[1][0]);
	pixels[1][1] = video_surface_color2pixel(surface, colors[1][1]);

	TRACE_START("swgfx_noblend_interp8888__gradient("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {{%#" PRIxCOL ", %#" PRIxCOL "}, {%#" PRIxCOL ", %#" PRIxCOL "}})\n",
	            dst_x_, dst_y_, size_x_, size_y_,
	            colors[0][0], colors[0][1], colors[1][0], colors[1][1]);
	if likely(LL_wlockregion(buffer, &lock, dst_x_, dst_y_, size_x_, size_y_)) {
		video_codec_setpixel_t vc_setpixel = video_buffer_getcodec(buffer)->vc_setpixel;
		video_codec_linefill_t vc_linefill = video_buffer_getcodec(buffer)->vc_linefill;
		video_codec_vertfill_t vc_vertfill = video_buffer_getcodec(buffer)->vc_vertfill;
		video_codec_rectfill_t vc_rectfill = video_buffer_getcodec(buffer)->vc_rectfill;
#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y) \
		{                                                                         \
			video_pixel_t out = pixels[src_y][src_x];                             \
			byte_t *line = video_regionlock_getline(&lock, dst_y);                \
			(*vc_rectfill)(line, dst_x, video_regionlock_getstride(&lock),        \
			               out, dst_size_x, dst_size_y);                          \
		}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
		{                                                                                   \
			video_pixel_t src_y0_x0 = pixels[src_y][src_x0];                                \
			video_pixel_t src_y0_x1 = pixels[src_y][src_x1];                                \
			video_pixel_t out = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);     \
			byte_t *line = video_regionlock_getline(&lock, dst_y);                          \
			(*vc_vertfill)(line, dst_x, video_regionlock_getstride(&lock),                  \
			               out, dst_size_y);                                                \
		}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
		{                                                                                   \
			video_pixel_t src_y0_x0 = pixels[src_y0][src_x];                                \
			video_pixel_t src_y1_x0 = pixels[src_y1][src_x];                                \
			video_pixel_t out = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);     \
			byte_t *line = video_regionlock_getline(&lock, dst_y);                          \
			(*vc_linefill)(line, dst_x, out, dst_size_x);                                   \
		}

#define pixel_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
		{                                                                                             \
			video_pixel_t src_y0_x0 = pixels[src_y0][src_x0];                                         \
			video_pixel_t src_y0_x1 = pixels[src_y0][src_x1];                                         \
			video_pixel_t src_y1_x0 = pixels[src_y1][src_x0];                                         \
			video_pixel_t src_y1_x1 = pixels[src_y1][src_x1];                                         \
			video_pixel_t out = interpolate_2d(src_y0_x0, src_y0_x1,                                  \
			                                   src_y1_x0, src_y1_x1,                                  \
			                                   frac_x0, frac_x1,                                      \
			                                   frac_y0, frac_y1);                                     \
			byte_t *line = video_regionlock_getline(&lock, dst_y);                                    \
			(*vc_setpixel)(line, dst_x, out);                                                         \
		}
		GFX_LINEAR_STRETCH(video_regionlock_getxbase(&lock), 0, size_x_, size_y_,
		                   0, 0, 2, 2,
		                   pixel_blend_xmin_ymin,
		                   pixel_blend_ymin,
		                   pixel_blend_xmax_ymin,
		                   pixel_blend_xmin,
		                   pixel_blend,
		                   pixel_blend_xmax,
		                   pixel_blend_xmin_ymax,
		                   pixel_blend_ymax,
		                   pixel_blend_xmax_ymax);
#undef pixel_blend_xmin_ymin
#undef pixel_blend_ymin
#undef pixel_blend_xmax_ymin
#undef pixel_blend_xmin
#undef pixel_blend
#undef pixel_blend_xmax
#undef pixel_blend_xmin_ymax
#undef pixel_blend_ymax
#undef pixel_blend_xmax_ymax
		LL_unlockregion(buffer, &lock);
	} else {
		libvideo_swgfx_noblend_interp8888__gradient__bypixel(self, dst_x_, dst_y_, size_x_, size_y_, pixels);
	}
	TRACE_END("swgfx_noblend_interp8888__gradient()\n");
}

PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend_interp8888__gradient_h__bypixel(struct video_gfx const *__restrict self,
                                                       video_coord_t dst_x, video_coord_t dst_y,
                                                       video_dim_t size_x, video_dim_t size_y,
                                                       video_pixel_t lopixel, video_pixel_t hipixel,
                                                       video_dim_t pad_xmin, video_dim_t pad_xmax,
                                                       video_foffset_t fp_src_x, video_fcoord_t fp_step_x) {
	if (pad_xmin) {
		libvideo_swgfx_noblend__fill__bypixel(self, dst_x, dst_y, pad_xmin, size_y, lopixel);
		dst_x += pad_xmin;
		size_x -= pad_xmin;
		fp_src_x += pad_xmin * fp_step_x;
	}
	if (pad_xmax) {
		size_x -= pad_xmax;
		libvideo_swgfx_noblend__fill__bypixel(self, dst_x + size_x, dst_y, pad_xmax, size_y, hipixel);
	}
	for (; size_x; --size_x, ++dst_x, fp_src_x += fp_step_x) {
		linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_x);
		linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
		video_pixel_t pixel = interpolate_1d(lopixel, hipixel, frac0, frac1);
		libvideo_swgfx_noblend__line_v__bypixel(self, dst_x, dst_y, size_y, pixel);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_noblend_interp8888__gradient_h(struct video_gfx const *__restrict self,
                                              video_coord_t dst_x, video_coord_t dst_y,
                                              video_dim_t size_x, video_dim_t size_y,
                                              video_color_t locolor, video_color_t hicolor) {
	struct video_regionlock lock;
	video_dim_t pad_xmin, pad_xmax;
	video_foffset_t fp_src_x;
	video_fcoord_t fp_step_x;
	struct video_surface const *surface;
	struct video_buffer *buffer;
	video_pixel_t lopixel;
	video_pixel_t hipixel;

	/* Check for special case: not actually a gradient */
	if (locolor == hicolor) {
		libvideo_swgfx_noblend__fill(self, dst_x, dst_y, size_x, size_y, locolor);
		return;
	}

	TRACE_START("swgfx_noblend_interp8888__gradient_h("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {%#" PRIxCOL ", %#" PRIxCOL "})\n",
	            dst_x, dst_y, size_x, size_y,
	            locolor, hicolor);
	calc_linear_stretch_dim(2, size_x, &fp_src_x, &fp_step_x, &pad_xmin, &pad_xmax);
	surface = video_gfx_assurface(self);
	buffer  = video_surface_getbuffer(surface);
	lopixel = video_surface_color2pixel(surface, locolor);
	hipixel = video_surface_color2pixel(surface, hicolor);
	if likely(LL_wlockregion(buffer, &lock, dst_x, dst_y, size_x, size_y)) {
		video_coord_t used_dst_x = video_regionlock_getxbase(&lock);
		video_codec_vertfill_t vc_vertfill = video_buffer_getcodec(buffer)->vc_vertfill;
		video_codec_rectfill_t vc_rectfill = video_buffer_getcodec(buffer)->vc_rectfill;
		if (pad_xmin) {
			(*vc_rectfill)(video_regionlock_getdata(&lock), used_dst_x,
			               video_regionlock_getstride(&lock),
			               lopixel, pad_xmin, size_y);
			used_dst_x += pad_xmin;
			size_x -= pad_xmin;
			fp_src_x += pad_xmin * fp_step_x;
		}
		if (pad_xmax) {
			size_x -= pad_xmax;
			(*vc_rectfill)(video_regionlock_getdata(&lock), used_dst_x + size_x,
			               video_regionlock_getstride(&lock),
			               hipixel, pad_xmax, size_y);
		}
		for (; size_x; --size_x, ++used_dst_x, fp_src_x += fp_step_x) {
			linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_x);
			linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
			video_pixel_t pixel = interpolate_1d(lopixel, hipixel, frac0, frac1);
			(*vc_vertfill)(video_regionlock_getdata(&lock), used_dst_x,
			               video_regionlock_getstride(&lock), pixel, size_y);
		}
		LL_unlockregion(buffer, &lock);
	} else {
		libvideo_swgfx_noblend_interp8888__gradient_h__bypixel(self, dst_x, dst_y, size_x, size_y,
		                                                       lopixel, hipixel, pad_xmin, pad_xmax,
		                                                       fp_src_x, fp_step_x);
	}
	TRACE_END("swgfx_noblend_interp8888__gradient_h()\n");
}

PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend_interp8888__gradient_v__bypixel(struct video_gfx const *__restrict self,
                                                       video_coord_t dst_x, video_coord_t dst_y,
                                                       video_dim_t size_x, video_dim_t size_y,
                                                       video_pixel_t lopixel, video_pixel_t hipixel,
                                                       video_dim_t pad_ymin, video_dim_t pad_ymax,
                                                       video_foffset_t fp_src_y, video_fcoord_t fp_step_y) {
	if (pad_ymin) {
		libvideo_swgfx_noblend__fill__bypixel(self, dst_x, dst_y, size_x, pad_ymin, lopixel);
		dst_y += pad_ymin;
		size_y -= pad_ymin;
		fp_src_y += pad_ymin * fp_step_y;
	}
	if (pad_ymax) {
		size_y -= pad_ymax;
		libvideo_swgfx_noblend__fill__bypixel(self, dst_x, dst_y + size_y, size_x, pad_ymax, hipixel);
	}
	for (; size_y; --size_y, ++dst_y, fp_src_y += fp_step_y) {
		linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_y);
		linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
		video_pixel_t pixel = interpolate_1d(lopixel, hipixel, frac0, frac1);
		libvideo_swgfx_noblend__line_v__bypixel(self, dst_x, dst_y, size_x, pixel);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_noblend_interp8888__gradient_v(struct video_gfx const *__restrict self,
                                              video_coord_t dst_x, video_coord_t dst_y,
                                              video_dim_t size_x, video_dim_t size_y,
                                              video_color_t locolor, video_color_t hicolor) {
	struct video_regionlock lock;
	video_dim_t pad_ymin, pad_ymax;
	video_foffset_t fp_src_y;
	video_fcoord_t fp_step_y;
	struct video_surface const *surface;
	struct video_buffer *buffer;
	video_pixel_t lopixel;
	video_pixel_t hipixel;

	/* Check for special case: not actually a gradient */
	if (locolor == hicolor) {
		libvideo_swgfx_noblend__fill(self, dst_x, dst_y, size_x, size_y, locolor);
		return;
	}

	TRACE_START("swgfx_noblend_interp8888__gradient_v("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {%#" PRIxCOL ", %#" PRIxCOL "})\n",
	            dst_x, dst_y, size_x, size_y,
	            locolor, hicolor);
	calc_linear_stretch_dim(2, size_y, &fp_src_y, &fp_step_y, &pad_ymin, &pad_ymax);
	surface = video_gfx_assurface(self);
	buffer  = video_surface_getbuffer(surface);
	lopixel = video_surface_color2pixel(surface, locolor);
	hipixel = video_surface_color2pixel(surface, hicolor);
	if likely(LL_wlockregion(buffer, &lock, dst_x, dst_y, size_x, size_y)) {
		byte_t *line = video_regionlock_getdata(&lock);
		video_codec_linefill_t vc_linefill = video_buffer_getcodec(buffer)->vc_linefill;
		video_codec_rectfill_t vc_rectfill = video_buffer_getcodec(buffer)->vc_rectfill;
		if (pad_ymin) {
			size_y -= pad_ymin;
			fp_src_y += pad_ymin * fp_step_y;
			(*vc_rectfill)(line,
			               video_regionlock_getxbase(&lock),
			               video_regionlock_getstride(&lock),
			               lopixel, size_x, pad_ymin);
			line += pad_ymin * video_regionlock_getstride(&lock);
		}
		if (pad_ymax) {
			byte_t *tail;
			size_y -= pad_ymax;
			tail = line + size_y * video_regionlock_getstride(&lock);
			(*vc_rectfill)(tail,
			               video_regionlock_getxbase(&lock),
			               video_regionlock_getstride(&lock),
			               hipixel, size_x, pad_ymax);
		}
		for (; size_y; --size_y, fp_src_y += fp_step_y) {
			linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_y);
			linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
			video_pixel_t pixel = interpolate_1d(lopixel, hipixel, frac0, frac1);
			(*vc_linefill)(line, video_regionlock_getxbase(&lock), pixel, size_x);
			line += video_regionlock_getstride(&lock);
		}
		LL_unlockregion(buffer, &lock);
	} else {
		libvideo_swgfx_noblend_interp8888__gradient_v__bypixel(self, dst_x, dst_y, size_x, size_y,
		                                                       lopixel, hipixel, pad_ymin, pad_ymax,
		                                                       fp_src_y, fp_step_y);
	}
	TRACE_END("swgfx_noblend_interp8888__gradient_v()\n");
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_LL_NOBLEND_C_INL */
