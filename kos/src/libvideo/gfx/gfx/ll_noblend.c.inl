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
#ifndef GUARD_LIBVIDEO_GFX_GFX_LL_NOBLEND_C_INL
#define GUARD_LIBVIDEO_GFX_GFX_LL_NOBLEND_C_INL 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/bit.h>
#include <hybrid/unaligned.h>

#include <kos/types.h>
#include <sys/param.h>

#include <stdint.h>

#include <libvideo/codec/api.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "../gfx.h"
#include "../gfx-utils.h"

DECL_BEGIN

/* Low-level, optimized GFX functions using `struct video_lock' (if available):
 * - *noblend*: Usable only when the relevant GFX's blend-mode is `GFX_BLENDMODE_OVERRIDE' */

PRIVATE ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_llhh__bypixel(struct video_gfx const *__restrict self,
                                            video_coord_t dst_x, video_coord_t dst_y,
                                            video_dim_t size_x, video_dim_t size_y,
                                            video_pixel_t pixel) {
	video_dim_t step;
	step = 0;
	if (size_x > size_y) {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y + (video_dim_t)(((uint64_t)size_y * step) / size_x);
			video_gfx_x_setpixel(self, line_x, line_y, pixel);
		} while (++step != size_x);
	} else if (size_x < size_y) {
		do {
			video_coord_t line_x = dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y);
			video_coord_t line_y = dst_y + step;
			video_gfx_x_setpixel(self, line_x, line_y, pixel);
		} while (++step != size_y);
	} else {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y + step;
			video_gfx_x_setpixel(self, line_x, line_y, pixel);
		} while (++step != size_x);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_llhh(struct video_gfx const *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_dim_t size_x, video_dim_t size_y,
                                   video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_pixel_t pixel = buffer->vb_format.color2pixel(color);
	gfx_assert(size_x > 0);
	gfx_assert(size_y > 0);
	if likely(buffer->wlock(lock) == 0) {
		video_dim_t step;
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		step = 0;
		if (size_x > size_y) {
			void (LIBVIDEO_CODEC_CC *vc_linefill)(byte_t *__restrict line, video_coord_t dst_x,
			                                      video_pixel_t pixel, video_dim_t num_pixels);
			vc_linefill = buffer->vb_format.vf_codec->vc_linefill;
			do {
				video_dim_t row = (video_dim_t)(((uint64_t)size_y * step) / size_x);
				video_dim_t row_end_step, row_length;
				row_end_step = step + 1;
				while (row == (video_dim_t)(((uint64_t)size_y * row_end_step) / size_x) &&
				       row_end_step != size_x)
					++row_end_step;
				row_length = row_end_step - row;
				(*vc_linefill)(line, dst_x + step, pixel, row_length);
				step = row_end_step;
				line += lock.vl_stride;
			} while (step != size_x);
		} else {
			void (LIBVIDEO_CODEC_CC *vc_setpixel)(byte_t *__restrict line, video_coord_t dst_x, video_pixel_t pixel);
			vc_setpixel = buffer->vb_format.vf_codec->vc_setpixel;
			if (size_x < size_y) {
				do {
					(*vc_setpixel)(line, dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y), pixel);
					line += lock.vl_stride;
				} while (++step != size_y);
			} else {
				do {
					(*vc_setpixel)(line, dst_x + step, pixel);
					line += lock.vl_stride;
				} while (++step != size_y);
			}
		}
		buffer->unlock(lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_gfx_noblend__absline_llhh__bypixel(self, dst_x, dst_y, size_x, size_y, pixel);
	}
}

PRIVATE ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_lhhl__bypixel(struct video_gfx const *__restrict self,
                                            video_coord_t dst_x, video_coord_t dst_y,
                                            video_dim_t size_x, video_dim_t size_y,
                                            video_pixel_t pixel) {
	video_dim_t step;
	step = 0;
	if (size_x > size_y) {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y - (video_dim_t)(((uint64_t)size_y * step) / size_x);
			video_gfx_x_setpixel(self, line_x, line_y, pixel);
		} while (++step != size_x);
	} else if (size_x < size_y) {
		do {
			video_coord_t line_x = dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y);
			video_coord_t line_y = dst_y - step;
			video_gfx_x_setpixel(self, line_x, line_y, pixel);
		} while (++step != size_y);
	} else {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y - step;
			video_gfx_x_setpixel(self, line_x, line_y, pixel);
		} while (++step != size_x);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_lhhl(struct video_gfx const *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_dim_t size_x, video_dim_t size_y,
                                   video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_pixel_t pixel = buffer->vb_format.color2pixel(color);
	gfx_assert(size_x > 0);
	gfx_assert(size_y > 0);
	if likely(buffer->wlock(lock) == 0) {
		video_dim_t step;
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		step = 0;
		if (size_x > size_y) {
			void (LIBVIDEO_CODEC_CC *vc_linefill)(byte_t *__restrict line, video_coord_t dst_x,
			                                      video_pixel_t pixel, video_dim_t num_pixels);
			vc_linefill = buffer->vb_format.vf_codec->vc_linefill;
			do {
				video_dim_t row = (video_dim_t)(((uint64_t)size_y * step) / size_x);
				video_dim_t row_end_step, row_length;
				row_end_step = step + 1;
				while (row == (video_dim_t)(((uint64_t)size_y * row_end_step) / size_x) &&
				       row_end_step != size_x)
					++row_end_step;
				row_length = row_end_step - row;
				(*vc_linefill)(line, dst_x + step, pixel, row_length);
				step = row_end_step;
				line -= lock.vl_stride;
			} while (step != size_x);
		} else {
			void (LIBVIDEO_CODEC_CC *vc_setpixel)(byte_t *__restrict line, video_coord_t dst_x, video_pixel_t pixel);
			vc_setpixel = buffer->vb_format.vf_codec->vc_setpixel;
			if (size_x < size_y) {
				do {
					(*vc_setpixel)(line, dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y), pixel);
					line -= lock.vl_stride;
				} while (++step != size_y);
			} else {
				do {
					(*vc_setpixel)(line, dst_x + step, pixel);
					line -= lock.vl_stride;
				} while (++step != size_y);
			}
		}
		buffer->unlock(lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_gfx_noblend__absline_lhhl__bypixel(self, dst_x, dst_y, size_x, size_y, pixel);
	}
}


PRIVATE ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_h__bypixel(struct video_gfx const *__restrict self,
                                         video_coord_t dst_x, video_coord_t dst_y,
                                         video_dim_t length, video_pixel_t pixel) {
	do {
		video_gfx_x_setpixel(self, dst_x, dst_y, pixel);
		++dst_x;
	} while (--length);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_h(struct video_gfx const *__restrict self,
                                video_coord_t dst_x, video_coord_t dst_y,
                                video_dim_t length, video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_pixel_t pixel = buffer->vb_format.color2pixel(color);
	if likely(buffer->wlock(lock) == 0) {
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		buffer->vb_format.linefill(line, dst_x, pixel, length);
		buffer->unlock(lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_gfx_noblend__absline_h__bypixel(self, dst_x, dst_y, length, pixel);
	}
}

PRIVATE ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_v__bypixel(struct video_gfx const *__restrict self,
                                         video_coord_t dst_x, video_coord_t dst_y,
                                         video_dim_t length, video_pixel_t pixel) {
	do {
		video_gfx_x_setpixel(self, dst_x, dst_y, pixel);
		++dst_y;
	} while (--length);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend__absline_v(struct video_gfx const *__restrict self,
                                video_coord_t dst_x, video_coord_t dst_y,
                                video_dim_t length, video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_pixel_t pixel = buffer->vb_format.color2pixel(color);
	if likely(buffer->wlock(lock) == 0) {
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		void (LIBVIDEO_CODEC_CC *vc_vertfill)(byte_t *__restrict line, video_coord_t x, size_t stride,
		                                      video_pixel_t pixel, video_dim_t num_pixels);
		vc_vertfill = buffer->vb_format.vf_codec->vc_vertfill;
		(*vc_vertfill)(line, dst_x, lock.vl_stride, pixel, length);
		buffer->unlock(lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_gfx_noblend__absline_v__bypixel(self, dst_x, dst_y, length, pixel);
	}
}

PRIVATE ATTR_IN(1) void CC
libvideo_gfx_noblend__absfill__bypixel(struct video_gfx const *__restrict self,
                                       video_coord_t dst_x, video_coord_t dst_y,
                                       video_dim_t size_x, video_dim_t size_y,
                                       video_pixel_t pixel) {
	do {
		video_coord_t x = 0;
		do {
			video_gfx_x_setpixel(self, dst_x + x, dst_y, pixel);
		} while (++x < size_x);
		++dst_y;
	} while (--size_y);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend__absfill(struct video_gfx const *__restrict self,
                              video_coord_t dst_x, video_coord_t dst_y,
                              video_dim_t size_x, video_dim_t size_y,
                              video_color_t color) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_pixel_t pixel = buffer->vb_format.color2pixel(color);
	if likely(buffer->wlock(lock) == 0) {
		/* Use the low-level linefill operator from the video codec */
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		void (LIBVIDEO_CODEC_CC *vc_rectfill)(byte_t *__restrict line, video_coord_t x, size_t stride,
		                                      video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
		vc_rectfill = buffer->vb_format.vf_codec->vc_rectfill;
		gfx_assert(size_x > 0);
		gfx_assert(size_y > 0);
		(*vc_rectfill)(line, dst_x, lock.vl_stride, pixel, size_x, size_y);
		buffer->unlock(lock);
	} else {
		/* Use pixel-based rendering */
		libvideo_gfx_noblend__absfill__bypixel(self, dst_x, dst_y, size_x, size_y, pixel);
	}
}

PRIVATE ATTR_IN(1) ATTR_IN(6) void CC
libvideo_gfx_noblend_interp8888__absgradient__bypixel(struct video_gfx const *__restrict self,
                                                      video_coord_t dst_x_, video_coord_t dst_y_,
                                                      video_dim_t size_x_, video_dim_t size_y_,
                                                      video_pixel_t pixels[2][2]) {
#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y) \
	{                                                                             \
		video_pixel_t out = pixels[src_y][src_x];                                 \
		video_gfx_x_absfill(self, dst_x, dst_y, dst_size_x, dst_size_y, out);     \
	}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                       \
		video_pixel_t src_y0_x0 = pixels[src_y][src_x0];                                    \
		video_pixel_t src_y0_x1 = pixels[src_y][src_x1];                                    \
		video_pixel_t out       = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);   \
		video_gfx_x_absline_v(self, dst_x, dst_y, dst_size_y, out);                         \
	}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                       \
		video_pixel_t src_y0_x0 = pixels[src_y0][src_x];                                    \
		video_pixel_t src_y1_x0 = pixels[src_y1][src_x];                                    \
		video_pixel_t out       = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);   \
		video_gfx_x_absline_h(self, dst_x, dst_y, dst_size_x, out);                         \
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
		video_gfx_x_setpixel(self, dst_x, dst_y, out);                                                \
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
libvideo_gfx_noblend_interp8888__absgradient(struct video_gfx const *__restrict self,
                                             video_coord_t dst_x_, video_coord_t dst_y_,
                                             video_dim_t size_x_, video_dim_t size_y_,
                                             video_color_t const colors[2][2]) {
	struct video_lock lock;
	struct video_buffer *buffer;
	video_color_t pixels[2][2];

	/* Check for special case: not actually a 4-color gradient */
	if (colors[0][0] == colors[0][1] && colors[1][0] == colors[1][1]) {
		libvideo_gfx_noblend_interp8888__absgradient_v(self, dst_x_, dst_y_, size_x_, size_y_,
		                                               colors[0][0], colors[1][0]);
		return;
	} else if (colors[0][0] == colors[1][0] && colors[0][1] == colors[1][1]) {
		libvideo_gfx_noblend_interp8888__absgradient_h(self, dst_x_, dst_y_, size_x_, size_y_,
		                                               colors[0][0], colors[0][1]);
		return;
	}

	/* Convert colors to pixels */
	buffer = self->vx_buffer;
	pixels[0][0] = buffer->vb_format.color2pixel(colors[0][0]);
	pixels[0][1] = buffer->vb_format.color2pixel(colors[0][1]);
	pixels[1][0] = buffer->vb_format.color2pixel(colors[1][0]);
	pixels[1][1] = buffer->vb_format.color2pixel(colors[1][1]);

	TRACE_START("noblend_interp8888__absgradient("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {{%#" PRIxCOL ", %#" PRIxCOL "}, {%#" PRIxCOL ", %#" PRIxCOL "}})\n",
	            dst_x_, dst_y_, size_x_, size_y_,
	            colors[0][0], colors[0][1], colors[1][0], colors[1][1]);
	if likely(buffer->wlock(lock) == 0) {
		byte_t *base = lock.vl_data + dst_y_ * lock.vl_stride;
		void (LIBVIDEO_CODEC_CC *vc_setpixel)(byte_t *__restrict line, video_coord_t dst_x,
		                                      video_pixel_t pixel);
		void (LIBVIDEO_CODEC_CC *vc_linefill)(byte_t *__restrict line, video_coord_t dst_x,
		                                      video_pixel_t pixel, video_dim_t num_pixels);
		void (LIBVIDEO_CODEC_CC *vc_vertfill)(byte_t *__restrict line, video_coord_t x, size_t stride,
		                                      video_pixel_t pixel, video_dim_t num_pixels);
		void (LIBVIDEO_CODEC_CC *vc_rectfill)(byte_t *__restrict line, video_coord_t x, size_t stride,
		                                      video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
		vc_setpixel = buffer->vb_format.vf_codec->vc_setpixel;
		vc_linefill = buffer->vb_format.vf_codec->vc_linefill;
		vc_vertfill = buffer->vb_format.vf_codec->vc_vertfill;
		vc_rectfill = buffer->vb_format.vf_codec->vc_rectfill;
#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)     \
		{                                                                             \
			video_pixel_t out = pixels[src_y][src_x];                                 \
			byte_t *line = base + dst_y * lock.vl_stride;                             \
			(*vc_rectfill)(line, dst_x, lock.vl_stride, out, dst_size_x, dst_size_y); \
		}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
		{                                                                                   \
			video_pixel_t src_y0_x0 = pixels[src_y][src_x0];                                \
			video_pixel_t src_y0_x1 = pixels[src_y][src_x1];                                \
			video_pixel_t out = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);     \
			byte_t *line = base + dst_y * lock.vl_stride;                                   \
			(*vc_vertfill)(line, dst_x, lock.vl_stride, out, dst_size_y);                   \
		}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1)   \
		{                                                                                     \
			video_pixel_t src_y0_x0 = pixels[src_y0][src_x];                                  \
			video_pixel_t src_y1_x0 = pixels[src_y1][src_x];                                  \
			video_pixel_t out       = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1); \
			byte_t *line = base + dst_y * lock.vl_stride;                                     \
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
			byte_t *line = base + dst_y * lock.vl_stride;                                             \
			(*vc_setpixel)(line, dst_x, out);                                                         \
		}
		GFX_LINEAR_STRETCH(dst_x_, 0, size_x_, size_y_,
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
	} else {
		libvideo_gfx_noblend_interp8888__absgradient__bypixel(self, dst_x_, dst_y_, size_x_, size_y_, pixels);
	}
	TRACE_END("noblend_interp8888__absgradient()\n");
}

PRIVATE ATTR_IN(1) void CC
libvideo_gfx_noblend_interp8888__absgradient_h__bypixel(struct video_gfx const *__restrict self,
                                                        video_coord_t dst_x, video_coord_t dst_y,
                                                        video_dim_t size_x, video_dim_t size_y,
                                                        video_pixel_t lopixel, video_pixel_t hipixel,
                                                        video_dim_t pad_xmin, video_dim_t pad_xmax,
                                                        sstretch_fp_t fp_src_x, stretch_fp_t fp_step_x) {
	if (pad_xmin) {
		libvideo_gfx_noblend__absfill__bypixel(self, dst_x, dst_y, pad_xmin, size_y, lopixel);
		dst_x += pad_xmin;
		size_x -= pad_xmin;
		fp_src_x += pad_xmin * fp_step_x;
	}
	if (pad_xmax) {
		size_x -= pad_xmax;
		libvideo_gfx_noblend__absfill__bypixel(self, dst_x + size_x, dst_y, pad_xmax, size_y, hipixel);
	}
	for (; size_x; --size_x, ++dst_x, fp_src_x += fp_step_x) {
		linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_x);
		linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
		video_pixel_t pixel = interpolate_1d(lopixel, hipixel, frac0, frac1);
		libvideo_gfx_noblend__absline_v__bypixel(self, dst_x, dst_y, size_y, pixel);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend_interp8888__absgradient_h(struct video_gfx const *__restrict self,
                                               video_coord_t dst_x, video_coord_t dst_y,
                                               video_dim_t size_x, video_dim_t size_y,
                                               video_color_t locolor, video_color_t hicolor) {
	struct video_lock lock;
	video_dim_t pad_xmin, pad_xmax;
	sstretch_fp_t fp_src_x;
	stretch_fp_t fp_step_x;
	struct video_buffer *buffer;
	video_pixel_t lopixel;
	video_pixel_t hipixel;

	/* Check for special case: not actually a gradient */
	if (locolor == hicolor) {
		libvideo_gfx_noblend__absfill(self, dst_x, dst_y, size_x, size_y, locolor);
		return;
	}

	TRACE_START("noblend_interp8888__absgradient_h("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {%#" PRIxCOL ", %#" PRIxCOL "})\n",
	            dst_x, dst_y, size_x, size_y,
	            locolor, hicolor);
	calc_linear_stretch_dim(2, size_x, &fp_src_x, &fp_step_x, &pad_xmin, &pad_xmax);
	buffer = self->vx_buffer;
	lopixel = buffer->vb_format.color2pixel(locolor);
	hipixel = buffer->vb_format.color2pixel(hicolor);
	if likely(buffer->wlock(lock) == 0) {
		byte_t *base = lock.vl_data + dst_y * lock.vl_stride;
		void (LIBVIDEO_CODEC_CC *vc_vertfill)(byte_t *__restrict line, video_coord_t x, size_t stride,
		                                      video_pixel_t pixel, video_dim_t num_pixels);
		void (LIBVIDEO_CODEC_CC *vc_rectfill)(byte_t *__restrict line, video_coord_t x, size_t stride,
		                                      video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
		vc_vertfill = buffer->vb_format.vf_codec->vc_vertfill;
		vc_rectfill = buffer->vb_format.vf_codec->vc_rectfill;
		if (pad_xmin) {
			(*vc_rectfill)(base, dst_x, lock.vl_stride, lopixel, pad_xmin, size_y);
			dst_x += pad_xmin;
			size_x -= pad_xmin;
			fp_src_x += pad_xmin * fp_step_x;
		}
		if (pad_xmax) {
			size_x -= pad_xmax;
			(*vc_rectfill)(base, dst_x + size_x, lock.vl_stride, hipixel, pad_xmax, size_y);
		}
		for (; size_x; --size_x, ++dst_x, fp_src_x += fp_step_x) {
			linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_x);
			linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
			video_pixel_t pixel = interpolate_1d(lopixel, hipixel, frac0, frac1);
			(*vc_vertfill)(base, dst_x, lock.vl_stride, pixel, size_y);
		}
	} else {
		libvideo_gfx_noblend_interp8888__absgradient_h__bypixel(self, dst_x, dst_y, size_x, size_y,
		                                                        lopixel, hipixel, pad_xmin, pad_xmax,
		                                                        fp_src_x, fp_step_x);
	}
	TRACE_END("noblend_interp8888__absgradient_h()\n");
}

PRIVATE ATTR_IN(1) void CC
libvideo_gfx_noblend_interp8888__absgradient_v__bypixel(struct video_gfx const *__restrict self,
                                                        video_coord_t dst_x, video_coord_t dst_y,
                                                        video_dim_t size_x, video_dim_t size_y,
                                                        video_pixel_t lopixel, video_pixel_t hipixel,
                                                        video_dim_t pad_ymin, video_dim_t pad_ymax,
                                                        sstretch_fp_t fp_src_y, stretch_fp_t fp_step_y) {
	if (pad_ymin) {
		libvideo_gfx_noblend__absfill__bypixel(self, dst_x, dst_y, size_x, pad_ymin, lopixel);
		dst_y += pad_ymin;
		size_y -= pad_ymin;
		fp_src_y += pad_ymin * fp_step_y;
	}
	if (pad_ymax) {
		size_y -= pad_ymax;
		libvideo_gfx_noblend__absfill__bypixel(self, dst_x, dst_y + size_y, size_x, pad_ymax, hipixel);
	}
	for (; size_y; --size_y, ++dst_y, fp_src_y += fp_step_y) {
		linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_y);
		linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
		video_pixel_t pixel = interpolate_1d(lopixel, hipixel, frac0, frac1);
		libvideo_gfx_noblend__absline_v__bypixel(self, dst_x, dst_y, size_x, pixel);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_noblend_interp8888__absgradient_v(struct video_gfx const *__restrict self,
                                               video_coord_t dst_x, video_coord_t dst_y,
                                               video_dim_t size_x, video_dim_t size_y,
                                               video_color_t locolor, video_color_t hicolor) {
	struct video_lock lock;
	video_dim_t pad_ymin, pad_ymax;
	sstretch_fp_t fp_src_y;
	stretch_fp_t fp_step_y;
	struct video_buffer *buffer;
	video_pixel_t lopixel;
	video_pixel_t hipixel;

	/* Check for special case: not actually a gradient */
	if (locolor == hicolor) {
		libvideo_gfx_noblend__absfill(self, dst_x, dst_y, size_x, size_y, locolor);
		return;
	}

	TRACE_START("noblend_interp8888__absgradient_v("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {%#" PRIxCOL ", %#" PRIxCOL "})\n",
	            dst_x, dst_y, size_x, size_y,
	            locolor, hicolor);
	calc_linear_stretch_dim(2, size_y, &fp_src_y, &fp_step_y, &pad_ymin, &pad_ymax);
	buffer = self->vx_buffer;
	lopixel = buffer->vb_format.color2pixel(locolor);
	hipixel = buffer->vb_format.color2pixel(hicolor);
	if likely(buffer->wlock(lock) == 0) {
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		void (LIBVIDEO_CODEC_CC *vc_linefill)(byte_t *__restrict line, video_coord_t dst_x,
		                                      video_pixel_t pixel, video_dim_t num_pixels);
		void (LIBVIDEO_CODEC_CC *vc_rectfill)(byte_t *__restrict line, video_coord_t x, size_t stride,
		                                      video_pixel_t pixel, video_dim_t size_x, video_dim_t size_y);
		vc_linefill = buffer->vb_format.vf_codec->vc_linefill;
		vc_rectfill = buffer->vb_format.vf_codec->vc_rectfill;
		if (pad_ymin) {
			size_y -= pad_ymin;
			fp_src_y += pad_ymin * fp_step_y;
			(*vc_rectfill)(line, dst_x, lock.vl_stride, lopixel, size_x, pad_ymin);
			line += pad_ymin * lock.vl_stride;
		}
		if (pad_ymax) {
			byte_t *tail;
			size_y -= pad_ymax;
			tail = line + size_y * lock.vl_stride;
			(*vc_rectfill)(tail, dst_x, lock.vl_stride, hipixel, size_x, pad_ymax);
		}
		for (; size_y; --size_y, fp_src_y += fp_step_y) {
			linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_y);
			linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
			video_pixel_t pixel = interpolate_1d(lopixel, hipixel, frac0, frac1);
			(*vc_linefill)(line, dst_x, pixel, size_x);
			line += lock.vl_stride;
		}
	} else {
		libvideo_gfx_noblend_interp8888__absgradient_v__bypixel(self, dst_x, dst_y, size_x, size_y,
		                                                        lopixel, hipixel, pad_ymin, pad_ymax,
		                                                        fp_src_y, fp_step_y);
	}
	TRACE_END("noblend_interp8888__absgradient_v()\n");
}


PRIVATE ATTR_IN(1) ATTR_IN(7) void CC
libvideo_gfx_noblend__fillmask__bypixel(struct video_gfx const *__restrict self,
                                        video_coord_t dst_x, video_coord_t dst_y,
                                        video_dim_t size_x, video_dim_t size_y,
                                        video_pixel_t pixel,
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
			if (byte & ((byte_t)1 << bits))
				video_gfx_x_setpixel(self, dst_x + x, dst_y, pixel);
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

INTERN ATTR_IN(1) ATTR_IN(7) void CC
libvideo_gfx_noblend__fillmask(struct video_gfx const *__restrict self,
                               video_coord_t dst_x, video_coord_t dst_y,
                               video_dim_t size_x, video_dim_t size_y,
                               video_color_t color,
                               struct video_bitmask const *__restrict bm) {
	struct video_lock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_pixel_t pixel = buffer->vb_format.color2pixel(color);
	TRACE_START("noblend__fillmask("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", bm: %p+%" PRIuPTR "\n",
	            dst_x, dst_y, size_x, size_y, color,
	            bm->vbm_mask, bm->vbm_skip);
	if likely(buffer->wlock(lock) == 0) {
		byte_t *line = lock.vl_data + dst_y * lock.vl_stride;
		void (LIBVIDEO_CODEC_CC *vc_linefill)(byte_t *__restrict line, video_coord_t dst_x,
		                                      video_pixel_t pixel, video_dim_t num_pixels);
		uintptr_t bitskip = bm->vbm_skip;
		byte_t const *bitmask = (byte_t const *)bm->vbm_mask;
		bitmask += bitskip / NBBY;
		bitskip = bitskip % NBBY;
		vc_linefill = buffer->vb_format.vf_codec->vc_linefill;
		gfx_assert(size_x > 0);
		gfx_assert(size_y > 0);
#ifndef __OPTIMIZE_SIZE__
		if likely(bitskip == 0 && !(bm->vbm_scan & 7)) {
			size_t bm_scanline = bm->vbm_scan >> 3;
			switch (size_x) {
#define DO_FIXED_WORD_RENDER(N)                                   \
				do {                                              \
					video_dim_t x = dst_x;                        \
					uint##N##_t word = UNALIGNED_GET##N(bitmask); \
					while (word) {                                \
						shift_t bits;                             \
						bits = CLZ((uint##N##_t)word);            \
						x += bits;                                \
						word <<= bits;                            \
						bits = CLZ((uint##N##_t)~word);           \
						gfx_assert(bits > 0);                     \
						(*vc_linefill)(line, x, pixel, bits);     \
						x += bits;                                \
						word <<= bits;                            \
					}                                             \
					line += lock.vl_stride;                       \
					bitmask += bm_scanline;                       \
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
						byte = *++row;
						row_bitskip = 0;
						bits = NBBY;
					}
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
				(*vc_linefill)(line, dst_x + x, pixel, count);
				x += count;
			} while (x < size_x);
next_row:
			bitskip += bm->vbm_scan;
			line += lock.vl_stride;
			bitmask += bitskip / NBBY;
			bitskip = bitskip % NBBY;
		} while (--size_y);
		buffer->unlock(lock);
		goto done;
	}
	/* Use pixel-based rendering */
	libvideo_gfx_noblend__fillmask__bypixel(self, dst_x, dst_y, size_x, size_y, pixel, bm);
done:
	TRACE_END("noblend__fillmask()\n");
}

PRIVATE ATTR_IN(1) void CC
libvideo_blitter_noblend_samefmt__blit__bypixel(struct video_blitter const *__restrict self,
                                                video_coord_t dst_x, video_coord_t dst_y,
                                                video_coord_t src_x, video_coord_t src_y,
                                                video_dim_t size_x, video_dim_t size_y) {
	video_dim_t x, y;
	struct video_gfx const *src = self->vbt_src;
	struct video_gfx const *dst = self->vbt_dst;
	for (y = 0; y < size_y; ++y) {
		for (x = 0; x < size_x; ++x) {
			video_pixel_t pixel;
			pixel = video_gfx_x_getpixel(src, src_x + x, src_y + y);
			video_gfx_x_setpixel(dst, dst_x + x, dst_y + y, pixel);
		}
	}
}

INTERN ATTR_IN(1) void CC
libvideo_blitter_noblend_samefmt__blit(struct video_blitter const *__restrict self,
                                       video_coord_t dst_x, video_coord_t dst_y,
                                       video_coord_t src_x, video_coord_t src_y,
                                       video_dim_t size_x, video_dim_t size_y) {
	struct video_lock dst_lock;
	struct video_buffer *dst_buffer = self->vbt_dst->vx_buffer;
	TRACE_START("noblend_samefmt__blit("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x, dst_y, src_x, src_y, size_x, size_y);
	if likely(dst_buffer->wlock(dst_lock) == 0) {
		struct video_lock src_lock;
		struct video_buffer *src_buffer = self->vbt_src->vx_buffer;
		if likely(src_buffer->rlock(src_lock) == 0) {
			byte_t *dst_line = dst_lock.vl_data + dst_y * dst_lock.vl_stride;
			byte_t const *src_line = src_lock.vl_data + src_y * src_lock.vl_stride;
			void (LIBVIDEO_CODEC_CC *vc_rectcopy)(byte_t *__restrict dst_line, video_coord_t dst_x, size_t dst_stride,
			                                      byte_t const *__restrict src_line, video_coord_t src_x, size_t src_stride,
			                                      video_dim_t size_x, video_dim_t size_y);
			vc_rectcopy = dst_buffer->vb_format.vf_codec->vc_rectcopy;
			(*vc_rectcopy)(dst_line, dst_x, dst_lock.vl_stride,
			               src_line, src_x, src_lock.vl_stride,
			               size_x, size_y);
			src_buffer->unlock(src_lock);
			dst_buffer->unlock(dst_lock);
			goto done;
		}
		dst_buffer->unlock(dst_lock);
	}
	/* Use pixel-based rendering */
	libvideo_blitter_noblend_samefmt__blit__bypixel(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
done:
	TRACE_END("noblend_samefmt__blit()\n");
}

static_assert(sizeof(struct video_converter) <= sizeof(((struct video_blitter *)0)->_vbt_driver),
              "This relation is required because `libvideo_gfx_generic__*' require driver-"
              "specific data to be set-up as a pixel format converter");

INTERN ATTR_IN(1) void CC
libvideo_blitter_noblend_difffmt__blit(struct video_blitter const *__restrict self,
                                       video_coord_t dst_x, video_coord_t dst_y,
                                       video_coord_t src_x, video_coord_t src_y,
                                       video_dim_t size_x, video_dim_t size_y) {
	video_dim_t x, y;
	struct video_gfx const *src = self->vbt_src;
	struct video_gfx const *dst = self->vbt_dst;
	struct video_converter *conv = libvideo_blitter_generic__conv(self);
	TRACE_START("noblend_difffmt__blit("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "}) "
	            "[method: %[vinfo:%n]]\n",
	            dst_x, dst_y, src_x, src_y, size_x, size_y, conv->vcv_mappixel);
	/* Blit per-pixel, with pixel format converter */
	for (y = 0; y < size_y; ++y) {
		for (x = 0; x < size_x; ++x) {
			video_pixel_t pixel;
			pixel = video_gfx_x_getpixel(src, src_x + x, src_y + y);
			pixel = video_converter_mappixel(conv, pixel);
			video_gfx_x_setpixel(dst, dst_x + x, dst_y + y, pixel);
		}
	}
	TRACE_END("noblend_difffmt__blit()\n");
}



INTERN ATTR_IN(1) ATTR_IN(9) void CC
libvideo_gfx_noblend__fillstretchmask_n(struct video_gfx const *__restrict self,
                                        video_coord_t dst_x, video_coord_t dst_y,
                                        video_dim_t dst_size_x, video_dim_t dst_size_y,
                                        video_color_t color,
                                        video_dim_t src_size_x, video_dim_t src_size_y,
                                        struct video_bitmask const *__restrict bm) {
	/* TODO */
	libvideo_gfx_generic__fillstretchmask_n(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                        color, src_size_x, src_size_y, bm);
}

INTERN ATTR_IN(1) void CC
libvideo_blitter_noblend_samefmt__stretch_n(struct video_blitter const *__restrict self,
                                            video_coord_t dst_x, video_coord_t dst_y,
                                            video_dim_t dst_size_x, video_dim_t dst_size_y,
                                            video_coord_t src_x, video_coord_t src_y,
                                            video_dim_t src_size_x, video_dim_t src_size_y) {
	/* TODO */
	libvideo_blitter_generic__stretch_n(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                    src_x, src_y, src_size_x, src_size_y);
}

INTERN ATTR_IN(1) void CC
libvideo_blitter_noblend_difffmt__stretch_n(struct video_blitter const *__restrict self,
                                            video_coord_t dst_x, video_coord_t dst_y,
                                            video_dim_t dst_size_x, video_dim_t dst_size_y,
                                            video_coord_t src_x, video_coord_t src_y,
                                            video_dim_t src_size_x, video_dim_t src_size_y) {
	/* TODO */
	libvideo_blitter_generic__stretch_n(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                    src_x, src_y, src_size_x, src_size_y);
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_LL_NOBLEND_C_INL */
