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

#include <hybrid/bit.h>
#include <hybrid/typecore.h>
#include <hybrid/unaligned.h>

#include <kos/types.h>
#include <sys/param.h>

#include <inttypes.h>
#include <stddef.h>
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
libvideo_swgfx_noblend__absline_llhh__bypixel(struct video_gfx const *__restrict self,
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
libvideo_swgfx_noblend__absline_llhh(struct video_gfx const *__restrict self,
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
		byte_t *line = lock.vrl_lock.vl_data;
		step = 0;
		if (size_x > size_y) {
			video_coord_t line_lox = 0;
			video_codec_linefill_t vc_linefill = video_buffer_getcodec(buffer)->vc_linefill;
			do {
				video_coord_t line_hix = (video_dim_t)(((uint64_t)size_x * (step + 1)) / size_y);
				(*vc_linefill)(line, lock.vrl_xbas + line_lox, pixel, line_hix - line_lox);
				line_lox = line_hix;
				line += lock.vrl_lock.vl_stride;
			} while (++step < size_y);
		} else if (size_x < size_y) {
			video_coord_t line_loy = 0;
			video_codec_vertfill_t vc_vertfill = video_buffer_getcodec(buffer)->vc_vertfill;
			do {
				video_coord_t line_hiy = (video_dim_t)(((uint64_t)size_y * (step + 1)) / size_x);
				video_dim_t length = line_hiy - line_loy;
				(*vc_vertfill)(line, lock.vrl_xbas + step, lock.vrl_lock.vl_stride, pixel, length);
				line_loy = line_hiy;
				line += length * lock.vrl_lock.vl_stride;
			} while (++step < size_x);
		} else {
			video_codec_setpixel_t vc_setpixel;
			vc_setpixel = video_buffer_getcodec(buffer)->vc_setpixel;
			do {
				(*vc_setpixel)(line, lock.vrl_xbas + step, pixel);
				line += lock.vrl_lock.vl_stride;
			} while (++step != size_y);
		}
		LL_unlockregion(buffer, &lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_swgfx_noblend__absline_llhh__bypixel(self, dst_x, dst_y, size_x, size_y, pixel);
	}
}

PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend__absline_lhhl__bypixel(struct video_gfx const *__restrict self,
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
libvideo_swgfx_noblend__absline_lhhl(struct video_gfx const *__restrict self,
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
		byte_t *line = lock.vrl_lock.vl_data + (size_y - 1) * lock.vrl_lock.vl_stride;
		step = 0;
		if (size_x > size_y) {
			video_coord_t line_lox = 0;
			video_codec_linefill_t vc_linefill = video_buffer_getcodec(buffer)->vc_linefill;
			do {
				video_coord_t line_hix = (video_dim_t)(((uint64_t)size_x * (step + 1)) / size_y);
				(*vc_linefill)(line, lock.vrl_xbas + line_lox, pixel, line_hix - line_lox);
				line_lox = line_hix;
				line -= lock.vrl_lock.vl_stride;
			} while (++step < size_y);
		} else if (size_x < size_y) {
			video_coord_t line_loy = 0;
			video_codec_vertfill_t vc_vertfill = video_buffer_getcodec(buffer)->vc_vertfill;
			line += lock.vrl_lock.vl_stride;
			do {
				video_coord_t line_hiy = (video_dim_t)(((uint64_t)size_y * (step + 1)) / size_x);
				video_dim_t length = line_hiy - line_loy;
				line -= length * lock.vrl_lock.vl_stride;
				(*vc_vertfill)(line, lock.vrl_xbas + step, lock.vrl_lock.vl_stride, pixel, length);
				line_loy = line_hiy;
			} while (++step < size_x);
		} else {
			video_codec_setpixel_t vc_setpixel;
			vc_setpixel = video_buffer_getcodec(buffer)->vc_setpixel;
			do {
				(*vc_setpixel)(line, lock.vrl_xbas + step, pixel);
				line -= lock.vrl_lock.vl_stride;
			} while (++step != size_y);
		}
		LL_unlockregion(buffer, &lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_swgfx_noblend__absline_lhhl__bypixel(self, dst_x, dst_y, size_x, size_y, pixel);
	}
}


PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend__absline_h__bypixel(struct video_gfx const *__restrict self,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_dim_t length, video_pixel_t pixel) {
	do {
		LL_setpixel(self, dst_x, dst_y, pixel);
		++dst_x;
	} while (--length);
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_noblend__absline_h(struct video_gfx const *__restrict self,
                                  video_coord_t dst_x, video_coord_t dst_y,
                                  video_dim_t length, video_color_t color) {
	struct video_regionlock lock;
	struct video_surface const *surface = video_gfx_assurface(self);
	struct video_buffer *buffer = video_surface_getbuffer(surface);
	video_pixel_t pixel = video_surface_color2pixel(surface, color);
	gfx_assert(length > 0);
	if likely(LL_wlockregion(buffer, &lock, dst_x, dst_y, length, 1)) {
		video_codec_linefill_t vc_linefill = video_buffer_getcodec(buffer)->vc_linefill;
		(*vc_linefill)(lock.vrl_lock.vl_data, lock.vrl_xbas, pixel, length);
		LL_unlockregion(buffer, &lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_swgfx_noblend__absline_h__bypixel(self, dst_x, dst_y, length, pixel);
	}
}

PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend__absline_v__bypixel(struct video_gfx const *__restrict self,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_dim_t length, video_pixel_t pixel) {
	do {
		LL_setpixel(self, dst_x, dst_y, pixel);
		++dst_y;
	} while (--length);
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_noblend__absline_v(struct video_gfx const *__restrict self,
                                  video_coord_t dst_x, video_coord_t dst_y,
                                  video_dim_t length, video_color_t color) {
	struct video_regionlock lock;
	struct video_surface const *surface = video_gfx_assurface(self);
	struct video_buffer *buffer = video_surface_getbuffer(surface);
	video_pixel_t pixel = video_surface_color2pixel(surface, color);
	if likely(LL_wlockregion(buffer, &lock, dst_x, dst_y, 1, length)) {
		video_codec_vertfill_t vc_vertfill = video_buffer_getcodec(buffer)->vc_vertfill;
		(*vc_vertfill)(lock.vrl_lock.vl_data, lock.vrl_xbas, lock.vrl_lock.vl_stride, pixel, length);
		LL_unlockregion(buffer, &lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_swgfx_noblend__absline_v__bypixel(self, dst_x, dst_y, length, pixel);
	}
}

PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend__absfill__bypixel(struct video_gfx const *__restrict self,
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
libvideo_swgfx_noblend__absfill(struct video_gfx const *__restrict self,
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
		/* Use the low-level linefill operator from the video codec */
		video_codec_rectfill_t vc_rectfill = video_buffer_getcodec(buffer)->vc_rectfill;
		(*vc_rectfill)(lock.vrl_lock.vl_data, lock.vrl_xbas,
		               lock.vrl_lock.vl_stride, pixel, size_x, size_y);
		LL_unlockregion(buffer, &lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_swgfx_noblend__absfill__bypixel(self, dst_x, dst_y, size_x, size_y, pixel);
	}
}

PRIVATE ATTR_IN(1) ATTR_IN(6) void CC
libvideo_swgfx_noblend_interp8888__absgradient__bypixel(struct video_gfx const *__restrict self,
                                                        video_coord_t dst_x_, video_coord_t dst_y_,
                                                        video_dim_t size_x_, video_dim_t size_y_,
                                                        video_pixel_t pixels[2][2]) {
#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y) \
	{                                                                             \
		video_pixel_t out = pixels[src_y][src_x];                                 \
		LL_absfill(self, dst_x, dst_y, dst_size_x, dst_size_y, out);              \
	}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                       \
		video_pixel_t src_y0_x0 = pixels[src_y][src_x0];                                    \
		video_pixel_t src_y0_x1 = pixels[src_y][src_x1];                                    \
		video_pixel_t out       = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);   \
		LL_absline_v(self, dst_x, dst_y, dst_size_y, out);                                  \
	}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                       \
		video_pixel_t src_y0_x0 = pixels[src_y0][src_x];                                    \
		video_pixel_t src_y1_x0 = pixels[src_y1][src_x];                                    \
		video_pixel_t out       = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);   \
		LL_absline_h(self, dst_x, dst_y, dst_size_x, out);                                  \
	}

#define pixel_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                 \
		video_pixel_t src_y0_x0 = pixels[src_y0][src_x0];                                             \
		video_pixel_t src_y0_x1 = pixels[src_y0][src_x1];                                             \
		video_pixel_t src_y1_x0 = pixels[src_y1][src_x0];                                             \
		video_pixel_t src_y1_x1 = pixels[src_y1][src_x1];                                             \
		video_pixel_t out = interpolate_2d(src_y0_x0, src_y0_x1,                                      \
		                                   src_y1_x0, src_y1_x1,                                      \
		                                   frac_x0, frac_x1,                                          \
		                                   frac_y0, frac_y1);                                         \
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
libvideo_swgfx_noblend_interp8888__absgradient(struct video_gfx const *__restrict self,
                                               video_coord_t dst_x_, video_coord_t dst_y_,
                                               video_dim_t size_x_, video_dim_t size_y_,
                                               video_color_t const colors[2][2]) {
	struct video_regionlock lock;
	struct video_surface const *surface;
	struct video_buffer *buffer;
	video_color_t pixels[2][2];

	/* Check for special case: not actually a 4-color gradient */
	if (colors[0][0] == colors[0][1] && colors[1][0] == colors[1][1]) {
		libvideo_swgfx_noblend_interp8888__absgradient_v(self, dst_x_, dst_y_, size_x_, size_y_,
		                                                 colors[0][0], colors[1][0]);
		return;
	} else if (colors[0][0] == colors[1][0] && colors[0][1] == colors[1][1]) {
		libvideo_swgfx_noblend_interp8888__absgradient_h(self, dst_x_, dst_y_, size_x_, size_y_,
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

	TRACE_START("noblend_interp8888__absgradient("
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
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)              \
		{                                                                                      \
			video_pixel_t out = pixels[src_y][src_x];                                          \
			byte_t *line      = lock.vrl_lock.vl_data + dst_y * lock.vrl_lock.vl_stride;       \
			(*vc_rectfill)(line, dst_x, lock.vrl_lock.vl_stride, out, dst_size_x, dst_size_y); \
		}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
		{                                                                                   \
			video_pixel_t src_y0_x0 = pixels[src_y][src_x0];                                \
			video_pixel_t src_y0_x1 = pixels[src_y][src_x1];                                \
			video_pixel_t out = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);     \
			byte_t *line = lock.vrl_lock.vl_data + dst_y * lock.vrl_lock.vl_stride;         \
			(*vc_vertfill)(line, dst_x, lock.vrl_lock.vl_stride, out, dst_size_y);          \
		}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1)   \
		{                                                                                     \
			video_pixel_t src_y0_x0 = pixels[src_y0][src_x];                                  \
			video_pixel_t src_y1_x0 = pixels[src_y1][src_x];                                  \
			video_pixel_t out       = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1); \
			byte_t *line = lock.vrl_lock.vl_data + dst_y * lock.vrl_lock.vl_stride;           \
			(*vc_linefill)(line, dst_x, out, dst_size_x);                                     \
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
			byte_t *line = lock.vrl_lock.vl_data + dst_y * lock.vrl_lock.vl_stride;                   \
			(*vc_setpixel)(line, dst_x, out);                                                         \
		}
		GFX_LINEAR_STRETCH(lock.vrl_xbas, 0, size_x_, size_y_,
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
		libvideo_swgfx_noblend_interp8888__absgradient__bypixel(self, dst_x_, dst_y_, size_x_, size_y_, pixels);
	}
	TRACE_END("noblend_interp8888__absgradient()\n");
}

PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend_interp8888__absgradient_h__bypixel(struct video_gfx const *__restrict self,
                                                          video_coord_t dst_x, video_coord_t dst_y,
                                                          video_dim_t size_x, video_dim_t size_y,
                                                          video_pixel_t lopixel, video_pixel_t hipixel,
                                                          video_dim_t pad_xmin, video_dim_t pad_xmax,
                                                          sstretch_fp_t fp_src_x, stretch_fp_t fp_step_x) {
	if (pad_xmin) {
		libvideo_swgfx_noblend__absfill__bypixel(self, dst_x, dst_y, pad_xmin, size_y, lopixel);
		dst_x += pad_xmin;
		size_x -= pad_xmin;
		fp_src_x += pad_xmin * fp_step_x;
	}
	if (pad_xmax) {
		size_x -= pad_xmax;
		libvideo_swgfx_noblend__absfill__bypixel(self, dst_x + size_x, dst_y, pad_xmax, size_y, hipixel);
	}
	for (; size_x; --size_x, ++dst_x, fp_src_x += fp_step_x) {
		linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_x);
		linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
		video_pixel_t pixel = interpolate_1d(lopixel, hipixel, frac0, frac1);
		libvideo_swgfx_noblend__absline_v__bypixel(self, dst_x, dst_y, size_y, pixel);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_noblend_interp8888__absgradient_h(struct video_gfx const *__restrict self,
                                                 video_coord_t dst_x, video_coord_t dst_y,
                                                 video_dim_t size_x, video_dim_t size_y,
                                                 video_color_t locolor, video_color_t hicolor) {
	struct video_regionlock lock;
	video_dim_t pad_xmin, pad_xmax;
	sstretch_fp_t fp_src_x;
	stretch_fp_t fp_step_x;
	struct video_surface const *surface;
	struct video_buffer *buffer;
	video_pixel_t lopixel;
	video_pixel_t hipixel;

	/* Check for special case: not actually a gradient */
	if (locolor == hicolor) {
		libvideo_swgfx_noblend__absfill(self, dst_x, dst_y, size_x, size_y, locolor);
		return;
	}

	TRACE_START("noblend_interp8888__absgradient_h("
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
		video_coord_t used_dst_x = lock.vrl_xbas;
		video_codec_vertfill_t vc_vertfill = video_buffer_getcodec(buffer)->vc_vertfill;
		video_codec_rectfill_t vc_rectfill = video_buffer_getcodec(buffer)->vc_rectfill;
		if (pad_xmin) {
			(*vc_rectfill)(lock.vrl_lock.vl_data, used_dst_x,
			               lock.vrl_lock.vl_stride, lopixel, pad_xmin, size_y);
			used_dst_x += pad_xmin;
			size_x -= pad_xmin;
			fp_src_x += pad_xmin * fp_step_x;
		}
		if (pad_xmax) {
			size_x -= pad_xmax;
			(*vc_rectfill)(lock.vrl_lock.vl_data, used_dst_x + size_x,
			               lock.vrl_lock.vl_stride, hipixel, pad_xmax, size_y);
		}
		for (; size_x; --size_x, ++used_dst_x, fp_src_x += fp_step_x) {
			linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_x);
			linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
			video_pixel_t pixel = interpolate_1d(lopixel, hipixel, frac0, frac1);
			(*vc_vertfill)(lock.vrl_lock.vl_data, used_dst_x, lock.vrl_lock.vl_stride, pixel, size_y);
		}
		LL_unlockregion(buffer, &lock);
	} else {
		libvideo_swgfx_noblend_interp8888__absgradient_h__bypixel(self, dst_x, dst_y, size_x, size_y,
		                                                          lopixel, hipixel, pad_xmin, pad_xmax,
		                                                          fp_src_x, fp_step_x);
	}
	TRACE_END("noblend_interp8888__absgradient_h()\n");
}

PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend_interp8888__absgradient_v__bypixel(struct video_gfx const *__restrict self,
                                                          video_coord_t dst_x, video_coord_t dst_y,
                                                          video_dim_t size_x, video_dim_t size_y,
                                                          video_pixel_t lopixel, video_pixel_t hipixel,
                                                          video_dim_t pad_ymin, video_dim_t pad_ymax,
                                                          sstretch_fp_t fp_src_y, stretch_fp_t fp_step_y) {
	if (pad_ymin) {
		libvideo_swgfx_noblend__absfill__bypixel(self, dst_x, dst_y, size_x, pad_ymin, lopixel);
		dst_y += pad_ymin;
		size_y -= pad_ymin;
		fp_src_y += pad_ymin * fp_step_y;
	}
	if (pad_ymax) {
		size_y -= pad_ymax;
		libvideo_swgfx_noblend__absfill__bypixel(self, dst_x, dst_y + size_y, size_x, pad_ymax, hipixel);
	}
	for (; size_y; --size_y, ++dst_y, fp_src_y += fp_step_y) {
		linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_y);
		linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
		video_pixel_t pixel = interpolate_1d(lopixel, hipixel, frac0, frac1);
		libvideo_swgfx_noblend__absline_v__bypixel(self, dst_x, dst_y, size_x, pixel);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_noblend_interp8888__absgradient_v(struct video_gfx const *__restrict self,
                                                 video_coord_t dst_x, video_coord_t dst_y,
                                                 video_dim_t size_x, video_dim_t size_y,
                                                 video_color_t locolor, video_color_t hicolor) {
	struct video_regionlock lock;
	video_dim_t pad_ymin, pad_ymax;
	sstretch_fp_t fp_src_y;
	stretch_fp_t fp_step_y;
	struct video_surface const *surface;
	struct video_buffer *buffer;
	video_pixel_t lopixel;
	video_pixel_t hipixel;

	/* Check for special case: not actually a gradient */
	if (locolor == hicolor) {
		libvideo_swgfx_noblend__absfill(self, dst_x, dst_y, size_x, size_y, locolor);
		return;
	}

	TRACE_START("noblend_interp8888__absgradient_v("
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
		byte_t *line = lock.vrl_lock.vl_data;
		video_codec_linefill_t vc_linefill = video_buffer_getcodec(buffer)->vc_linefill;
		video_codec_rectfill_t vc_rectfill = video_buffer_getcodec(buffer)->vc_rectfill;
		if (pad_ymin) {
			size_y -= pad_ymin;
			fp_src_y += pad_ymin * fp_step_y;
			(*vc_rectfill)(line, lock.vrl_xbas, lock.vrl_lock.vl_stride, lopixel, size_x, pad_ymin);
			line += pad_ymin * lock.vrl_lock.vl_stride;
		}
		if (pad_ymax) {
			byte_t *tail;
			size_y -= pad_ymax;
			tail = line + size_y * lock.vrl_lock.vl_stride;
			(*vc_rectfill)(tail, lock.vrl_xbas, lock.vrl_lock.vl_stride, hipixel, size_x, pad_ymax);
		}
		for (; size_y; --size_y, fp_src_y += fp_step_y) {
			linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_y);
			linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
			video_pixel_t pixel = interpolate_1d(lopixel, hipixel, frac0, frac1);
			(*vc_linefill)(line, lock.vrl_xbas, pixel, size_x);
			line += lock.vrl_lock.vl_stride;
		}
	} else {
		libvideo_swgfx_noblend_interp8888__absgradient_v__bypixel(self, dst_x, dst_y, size_x, size_y,
		                                                          lopixel, hipixel, pad_ymin, pad_ymax,
		                                                          fp_src_y, fp_step_y);
	}
	TRACE_END("noblend_interp8888__absgradient_v()\n");
}


PRIVATE ATTR_IN(1) ATTR_IN(7) void CC
libvideo_swgfx_noblend__fillmask1__bypixel(struct video_gfx const *__restrict self,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_dim_t size_x, video_dim_t size_y,
                                           video_pixel_t pixel,
                                           struct video_bitmask const *__restrict bm,
                                           __REGISTER_TYPE__ bm_xor) {
	uintptr_t bitskip = bm->vbm_skip;
	byte_t const *bitmask = (byte_t const *)bm->vbm_mask;
	bitmask += bitskip / NBBY;
	bitskip = bitskip % NBBY;
	do {
		video_dim_t x;
		uintptr_t row_bitskip;
		byte_t const *row;
		byte_t byte;
		shift_t bits;
		row_bitskip = bitskip;
		row = bitmask;
		byte = (*row) ^ (byte_t)bm_xor;
		bits = NBBY - row_bitskip;
		for (x = 0;;) {
			--bits;
			++row_bitskip;
			if ((byte >> bits) & 1)
				LL_setpixel(self, dst_x + x, dst_y, pixel);
			++x;
			if (x >= size_x)
				break;
			if (!bits) {
				byte = (*++row) ^ (byte_t)bm_xor;
				row_bitskip = 0;
				bits = NBBY;
			}
		}
		bitskip += bm->vbm_scan;
		bitmask += bitskip / NBBY;
		bitskip = bitskip % NBBY;
		++dst_y;
	} while (--size_y);
}

INTERN ATTR_NOINLINE ATTR_IN(1) ATTR_IN(7) void CC
libvideo_swgfx_noblend__fillmask1(struct video_gfx const *__restrict self,
                                  video_coord_t dst_x, video_coord_t dst_y,
                                  video_dim_t size_x, video_dim_t size_y,
                                  video_color_t color,
                                  struct video_bitmask const *__restrict bm,
                                  __REGISTER_TYPE__ bm_xor) {
	struct video_regionlock lock;
	struct video_surface const *surface = video_gfx_assurface(self);
	struct video_buffer *buffer = video_surface_getbuffer(surface);
	video_pixel_t pixel = video_surface_color2pixel(surface, color);
	TRACE_START("noblend__fillmask1("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", bm: %p+%" PRIuPTR ", "
	            "bm_xor: %#" PRIxN(__SIZEOF_REGISTER__) ")\n",
	            dst_x, dst_y, size_x, size_y, color,
	            bm->vbm_mask, bm->vbm_skip, bm_xor);
	if likely(LL_wlockregion(buffer, &lock, dst_x, dst_y, size_x, size_y)) {
		byte_t *line = lock.vrl_lock.vl_data;
		video_codec_linefill_t vc_linefill = video_buffer_getcodec(buffer)->vc_linefill;
		uintptr_t bitskip = bm->vbm_skip;
		byte_t const *bitmask = (byte_t const *)bm->vbm_mask;
		bitmask += bitskip / NBBY;
		bitskip = bitskip % NBBY;
		gfx_assert(size_x > 0);
		gfx_assert(size_y > 0);
#ifndef __OPTIMIZE_SIZE__
		if likely(bitskip == 0 && !(bm->vbm_scan & 7)) {
			size_t bm_scanline = bm->vbm_scan >> 3;
			switch (size_x) {
#define DO_FIXED_WORD_RENDER(N)                                    \
				do {                                               \
					video_dim_t x = lock.vrl_xbas;                 \
					uint##N##_t word = UNALIGNED_GET##N(bitmask) ^ \
					                   (uint##N##_t)bm_xor;        \
					while (word) {                                 \
						shift_t bits;                              \
						bits = CLZ((uint##N##_t)word);             \
						x += bits;                                 \
						word <<= bits;                             \
						bits = CLZ((uint##N##_t)~word);            \
						gfx_assert(bits > 0);                      \
						(*vc_linefill)(line, x, pixel, bits);      \
						x += bits;                                 \
						word <<= bits;                             \
					}                                              \
					line += lock.vrl_lock.vl_stride;               \
					bitmask += bm_scanline;                        \
				} while (--size_y)
			case 0 ... 8:
				DO_FIXED_WORD_RENDER(8);
				goto done;
			case 9 ... 16:
				DO_FIXED_WORD_RENDER(16);
				goto done;
			case 17 ... 32:
				DO_FIXED_WORD_RENDER(32);
				goto done;
#if __SIZEOF_REGISTER__ >= 8
			case 33 ... 64:
				DO_FIXED_WORD_RENDER(64);
				goto done;
#endif /* __SIZEOF_REGISTER__ >= 8 */
			default: break;
#undef DO_FIXED_WORD_RENDER
			}
		}
#endif /* !__OPTIMIZE_SIZE__ */
		do {
			video_dim_t x;
			uintptr_t row_bitskip;
			byte_t const *row;
			x = 0;
			row_bitskip = bitskip;
			row = bitmask;
			do {
				video_dim_t count;
				byte_t byte = (*row) ^ (byte_t)bm_xor;
				shift_t bits = NBBY - row_bitskip;

				/* Skip over 0-bits */
				for (;;) {
					--bits;
					++row_bitskip;
					if (byte & ((byte_t)1 << bits))
						break;
					++x;
					if (x >= size_x)
						goto next_row;
					if (!bits) {
						byte = (*++row) ^ (byte_t)bm_xor;
						row_bitskip = 0;
						bits = NBBY;
					}
				}

				/* Count consecutive 1-bits */
				count = 1;
				while ((x + count) < size_x) {
					if (!bits) {
						byte = (*++row) ^ (byte_t)bm_xor;
						row_bitskip = 0;
						bits = NBBY;
					}
					--bits;
					if (!(byte & ((byte_t)1 << bits)))
						break;
					++row_bitskip;
					++count;
				}
				(*vc_linefill)(line, lock.vrl_xbas + x, pixel, count);
				x += count;
			} while (x < size_x);
next_row:
			bitskip += bm->vbm_scan;
			line += lock.vrl_lock.vl_stride;
			bitmask += bitskip / NBBY;
			bitskip = bitskip % NBBY;
		} while (--size_y);
		LL_unlockregion(buffer, &lock);
		goto done;
	}
	/* Use pixel-based rendering */
	libvideo_swgfx_noblend__fillmask1__bypixel(self, dst_x, dst_y,
	                                           size_x, size_y,
	                                           pixel, bm, bm_xor);
done:
	TRACE_END("noblend__fillmask1()\n");
}

PRIVATE ATTR_IN(1) ATTR_IN(7) void CC
libvideo_swgfx_noblend__fillmask__bypixel(struct video_gfx const *__restrict self,
                                          video_coord_t dst_x, video_coord_t dst_y,
                                          video_dim_t size_x, video_dim_t size_y,
                                          video_pixel_t const bg_fg_pixels[2],
                                          struct video_bitmask const *__restrict bm) {
	uintptr_t bitskip = bm->vbm_skip;
	byte_t const *bitmask = (byte_t const *)bm->vbm_mask;
	bitmask += bitskip / NBBY;
	bitskip = bitskip % NBBY;
	do {
		video_dim_t x;
		uintptr_t row_bitskip;
		byte_t const *row;
		byte_t byte;
		shift_t bits;
		row_bitskip = bitskip;
		row = bitmask;
		byte = *row;
		bits = NBBY - row_bitskip;
		for (x = 0;;) {
			--bits;
			++row_bitskip;
			LL_setpixel(self, dst_x + x, dst_y, bg_fg_pixels[(byte >> bits) & 1]);
			++x;
			if (x >= size_x)
				break;
			if (!bits) {
				byte = *++row;
				row_bitskip = 0;
				bits = NBBY;
			}
		}
		bitskip += bm->vbm_scan;
		bitmask += bitskip / NBBY;
		bitskip = bitskip % NBBY;
		++dst_y;
	} while (--size_y);
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC
libvideo_swgfx_noblend__fillmask(struct video_gfx const *__restrict self,
                                 video_coord_t dst_x, video_coord_t dst_y,
                                 video_dim_t size_x, video_dim_t size_y,
                                 video_color_t const bg_fg_colors[2],
                                 struct video_bitmask const *__restrict bm) {
	struct video_regionlock lock;
	struct video_surface const *surface = video_gfx_assurface(self);
	struct video_buffer *buffer = video_surface_getbuffer(surface);
	video_pixel_t bg_fg_pixel[2];
	bg_fg_pixel[0] = video_surface_color2pixel(surface, bg_fg_colors[0]);
	bg_fg_pixel[1] = video_surface_color2pixel(surface, bg_fg_colors[1]);
	TRACE_START("noblend__fillmask("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "bg_fg_colors: {%#" PRIxCOL ", %#" PRIxCOL "}, bm: %p+%" PRIuPTR ")\n",
	            dst_x, dst_y, size_x, size_y, bg_fg_colors[0], bg_fg_colors[1],
	            bm->vbm_mask, bm->vbm_skip);
	if likely(LL_wlockregion(buffer, &lock, dst_x, dst_y, size_x, size_y)) {
		byte_t *line = lock.vrl_lock.vl_data;
		video_codec_linefill_t vc_linefill = video_buffer_getcodec(buffer)->vc_linefill;
		uintptr_t bitskip = bm->vbm_skip;
		byte_t const *bitmask = (byte_t const *)bm->vbm_mask;
		bitmask += bitskip / NBBY;
		bitskip = bitskip % NBBY;
		gfx_assert(size_x > 0);
		gfx_assert(size_y > 0);
#ifndef __OPTIMIZE_SIZE__
		if likely(bitskip == 0 && !(bm->vbm_scan & 7)) {
			size_t bm_scanline = bm->vbm_scan >> 3;
			video_coord_t dst_endx = lock.vrl_xbas + size_x;
			switch (size_x) {
				/* XXX: I feel like this can be done with less if-statements. */
#define DO_FIXED_WORD_RENDER(N)                                                \
				do {                                                           \
					video_dim_t x = lock.vrl_xbas;                             \
					uint##N##_t word = UNALIGNED_GET##N(bitmask);              \
					while (word) {                                             \
						shift_t bits;                                          \
						bits = CLZ((uint##N##_t)word);                         \
						if (bits) {                                            \
							(*vc_linefill)(line, x, bg_fg_pixel[0], bits);     \
							x += bits;                                         \
						}                                                      \
						word <<= bits;                                         \
						bits = CLZ((uint##N##_t)~word);                        \
						gfx_assert(bits > 0);                                  \
						(*vc_linefill)(line, x, bg_fg_pixel[1], bits);         \
						x += bits;                                             \
						word <<= bits;                                         \
					}                                                          \
					if (x < dst_endx)                                          \
						(*vc_linefill)(line, x, bg_fg_pixel[0], dst_endx - x); \
					line += lock.vrl_lock.vl_stride;                           \
					bitmask += bm_scanline;                                    \
				} while (--size_y)
			case 0 ... 8:
				DO_FIXED_WORD_RENDER(8);
				goto done;
			case 9 ... 16:
				DO_FIXED_WORD_RENDER(16);
				goto done;
			case 17 ... 32:
				DO_FIXED_WORD_RENDER(32);
				goto done;
#if __SIZEOF_REGISTER__ >= 8
			case 33 ... 64:
				DO_FIXED_WORD_RENDER(64);
				goto done;
#endif /* __SIZEOF_REGISTER__ >= 8 */
			default: break;
#undef DO_FIXED_WORD_RENDER
			}
		}
#endif /* !__OPTIMIZE_SIZE__ */
		do {
			video_dim_t x;
			uintptr_t row_bitskip;
			byte_t const *row;
			x = 0;
			row_bitskip = bitskip;
			row = bitmask;
			do {
				video_dim_t count;
				byte_t byte = *row;
				shift_t bits = NBBY - row_bitskip;

				/* Count 0-bits */
				count = 0;
				for (;;) {
					--bits;
					++row_bitskip;
					if (byte & ((byte_t)1 << bits))
						break;
					++count;
					if ((x + count) >= size_x)
						break;
					if (!bits) {
						byte = *++row;
						row_bitskip = 0;
						bits = NBBY;
					}
				}
				if (count) {
					(*vc_linefill)(line, lock.vrl_xbas + x, bg_fg_pixel[0], count);
					x += count;
					if (x >= size_x)
						break;
				}

				/* Count consecutive 1-bits */
				count = 1;
				while ((x + count) < size_x) {
					if (!bits) {
						byte = *++row;
						row_bitskip = 0;
						bits = NBBY;
					}
					--bits;
					if (!(byte & ((byte_t)1 << bits)))
						break;
					++row_bitskip;
					++count;
				}
				(*vc_linefill)(line, lock.vrl_xbas + x, bg_fg_pixel[1], count);
				x += count;
			} while (x < size_x);
/*next_row:*/
			bitskip += bm->vbm_scan;
			line += lock.vrl_lock.vl_stride;
			bitmask += bitskip / NBBY;
			bitskip = bitskip % NBBY;
		} while (--size_y);
		LL_unlockregion(buffer, &lock);
		goto done;
	}
	/* Use pixel-based rendering */
	libvideo_swgfx_noblend__fillmask__bypixel(self, dst_x, dst_y, size_x, size_y, bg_fg_pixel, bm);
done:
	TRACE_END("noblend__fillmask()\n");
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_LL_NOBLEND_C_INL */
