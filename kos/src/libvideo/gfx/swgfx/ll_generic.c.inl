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
#ifndef GUARD_LIBVIDEO_GFX_SWGFX_LL_GENERIC_C_INL
#define GUARD_LIBVIDEO_GFX_SWGFX_LL_GENERIC_C_INL 1
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

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/blendcolors.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "../gfx-debug.h"
#include "../gfx-utils.h"
#include "../swgfx.h"
#include "ll.h"

DECL_BEGIN

/************************************************************************/
/* INTERNAL API                                                         */
/************************************************************************/


/* Low-level, Generic, always-valid GFX color functions (using only `xsw_getpixel' + `xsw_setpixel') */
INTERN ATTR_IN(1) video_color_t CC
libvideo_swgfx_generic__getcolor_noblend(struct video_gfx const *__restrict self,
                                         video_coord_t x, video_coord_t y) {
	video_pixel_t pixel = LL_getpixel(self, x, y);
	return video_format_pixel2color(&self->vx_buffer->vb_format, pixel);
}

INTERN ATTR_IN(1) video_color_t CC
libvideo_swgfx_generic__getcolor_blur(struct video_gfx const *__restrict self,
                                      video_coord_t x, video_coord_t y) {
	video_color_t result;
	video_color_t colors[8];
	video_twochannels_t r, g, b, a;
	uint_fast8_t i, color_count;
#define MODE_XMIN 0x1
#define MODE_XMAX 0x2
#define MODE_YMIN 0x4
#define MODE_YMAX 0x8
	uint_fast8_t mode = 0x0;
	/* Figure out how we're situated in relation to bounds. */
	if unlikely(x == self->vx_hdr.vxh_bxmin)
		mode |= MODE_XMIN;
	if unlikely(y == self->vx_hdr.vxh_bymin)
		mode |= MODE_YMIN;
	if unlikely(x == self->vx_hdr.vxh_bxend - 1)
		mode |= MODE_XMAX;
	if unlikely(y == self->vx_hdr.vxh_byend - 1)
		mode |= MODE_YMAX;
	/* Load colors as needed. */
	switch (__builtin_expect(mode, 0x0)) {
#define GETCOLOR(xoff, yoff) \
		libvideo_swgfx_generic__getcolor_noblend(self, x + (xoff), y + (yoff))

	case 0x0:
		/* +++ */
		/* +.+ */
		/* +++ */
		color_count = 8;
		colors[0] = GETCOLOR(-1, -1);
		colors[1] = GETCOLOR(0, -1);
		colors[2] = GETCOLOR(1, -1);

		colors[3] = GETCOLOR(-1, 0);
		colors[4] = GETCOLOR(1, 0);

		colors[5] = GETCOLOR(-1, 1);
		colors[6] = GETCOLOR(0, 1);
		colors[7] = GETCOLOR(1, 1);
		break;

	case MODE_XMIN:
		/* -++ */
		/* -.+ */
		/* -++ */
		color_count = 5;
		colors[0] = GETCOLOR(0, -1);
		colors[1] = GETCOLOR(1, -1);

		colors[2] = GETCOLOR(1, 0);

		colors[3] = GETCOLOR(0, 1);
		colors[4] = GETCOLOR(1, 1);
		break;

	case MODE_XMAX:
		/* ++- */
		/* +.- */
		/* ++- */
		color_count = 5;
		colors[0] = GETCOLOR(-1, -1);
		colors[1] = GETCOLOR(0, -1);

		colors[2] = GETCOLOR(-1, 0);

		colors[3] = GETCOLOR(-1, 1);
		colors[4] = GETCOLOR(0, 1);
		break;

	case MODE_YMIN:
		/* --- */
		/* +.+ */
		/* +++ */
		color_count = 5;
		colors[0] = GETCOLOR(-1, 0);
		colors[1] = GETCOLOR(1, 0);
		colors[2] = GETCOLOR(-1, 1);
		colors[3] = GETCOLOR(0, 1);
		colors[4] = GETCOLOR(1, 1);
		break;

	case MODE_YMAX:
		/* +++ */
		/* +.+ */
		/* --- */
		color_count = 5;
		colors[0] = GETCOLOR(-1, -1);
		colors[1] = GETCOLOR(0, -1);
		colors[2] = GETCOLOR(1, -1);
		colors[3] = GETCOLOR(-1, 0);
		colors[4] = GETCOLOR(1, 0);
		break;

	case MODE_YMIN | MODE_YMAX:
		/* --- */
		/* +.+ */
		/* --- */
		color_count = 2;
		colors[0] = GETCOLOR(-1, 0);
		colors[1] = GETCOLOR(1, 0);
		break;

	case MODE_XMIN | MODE_XMAX:
		/* -+- */
		/* -.- */
		/* -+- */
		color_count = 2;
		colors[0] = GETCOLOR(0, -1);
		colors[1] = GETCOLOR(0, 1);
		break;

	case MODE_YMIN | MODE_XMIN:
		/* --- */
		/* -.+ */
		/* -++ */
		color_count = 3;
		colors[0] = GETCOLOR(1, 0);
		colors[1] = GETCOLOR(0, 1);
		colors[2] = GETCOLOR(1, 1);
		break;

	case MODE_YMIN | MODE_XMAX:
		/* --- */
		/* +.- */
		/* ++- */
		color_count = 3;
		colors[0] = GETCOLOR(-1, 0);
		colors[1] = GETCOLOR(-1, 1);
		colors[2] = GETCOLOR(0, 1);
		break;

	case MODE_YMAX | MODE_XMIN:
		/* -++ */
		/* -.+ */
		/* --- */
		color_count = 3;
		colors[0] = GETCOLOR(0, -1);
		colors[1] = GETCOLOR(1, -1);
		colors[2] = GETCOLOR(1, 0);
		break;

	case MODE_YMAX | MODE_XMAX:
		/* ++- */
		/* +.- */
		/* --- */
		color_count = 3;
		colors[0] = GETCOLOR(-1, -1);
		colors[1] = GETCOLOR(0, -1);
		colors[2] = GETCOLOR(-1, 0);
		break;

	case MODE_XMIN | MODE_XMAX | MODE_YMIN:
		/* --- */
		/* -.- */
		/* -+- */
		color_count = 1;
		colors[0] = GETCOLOR(0, 1);
		break;

	case MODE_XMIN | MODE_XMAX | MODE_YMAX:
		/* -+- */
		/* -.- */
		/* --- */
		color_count = 1;
		colors[0] = GETCOLOR(0, -1);
		break;

	case MODE_YMIN | MODE_YMAX | MODE_XMIN:
		/* --- */
		/* -.+ */
		/* --- */
		color_count = 1;
		colors[0] = GETCOLOR(1, 0);
		break;

	case MODE_YMIN | MODE_YMAX | MODE_XMAX:
		/* --- */
		/* +.- */
		/* --- */
		color_count = 1;
		colors[0] = GETCOLOR(-1, 0);
		break;

	case MODE_XMIN | MODE_YMIN | MODE_XMAX | MODE_YMAX:
		/* --- */
		/* -.- */
		/* --- */
		color_count = 0;
		break;

#undef GETCOLOR
	default: __builtin_unreachable();
	}
#undef MODE_XMIN
#undef MODE_XMAX
#undef MODE_YMIN
#undef MODE_YMAX
	result = libvideo_swgfx_generic__getcolor_noblend(self, x, y);
	r = VIDEO_COLOR_GET_RED(result);
	g = VIDEO_COLOR_GET_GREEN(result);
	b = VIDEO_COLOR_GET_BLUE(result);
	a = VIDEO_COLOR_GET_ALPHA(result);
	for (i = 0; i < color_count; ++i) {
		r += VIDEO_COLOR_GET_RED(colors[i]);
		g += VIDEO_COLOR_GET_GREEN(colors[i]);
		b += VIDEO_COLOR_GET_BLUE(colors[i]);
		a += VIDEO_COLOR_GET_ALPHA(colors[i]);
	}
	++color_count;
	r /= color_count;
	g /= color_count;
	b /= color_count;
	a /= color_count;
	result = VIDEO_COLOR_RGBA((video_channel_t)r,
	                          (video_channel_t)g,
	                          (video_channel_t)b,
	                          (video_channel_t)a);
	return result;
}

INTERN ATTR_IN(1) video_color_t CC
libvideo_swgfx_generic__getcolor_with_key(struct video_gfx const *__restrict self,
                                          video_coord_t x, video_coord_t y) {
	video_pixel_t pixel  = LL_getpixel(self, x, y);
	video_color_t result = video_format_pixel2color(&self->vx_buffer->vb_format, pixel);
	if (result == self->vx_colorkey)
		result = 0;
	return result;
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__putcolor(struct video_gfx const *__restrict self,
                                 video_coord_t x, video_coord_t y,
                                 video_color_t color) {
	video_pixel_t op = LL_getpixel(self, x, y);
	video_color_t oc = video_format_pixel2color(&self->vx_buffer->vb_format, op);
	video_color_t nc = gfx_blendcolors(oc, color, self->vx_blend);
	video_pixel_t np = video_format_color2pixel(&self->vx_buffer->vb_format, nc);
	LL_setpixel(self, x, y, np);
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__putcolor_noblend(struct video_gfx const *__restrict self,
                                         video_coord_t x, video_coord_t y,
                                         video_color_t color) {
	video_pixel_t np = video_format_color2pixel(&self->vx_buffer->vb_format, color);
	LL_setpixel(self, x, y, np);
}

#define DEFINE_libvideo_swgfx_generic__putcolor_FOO(name, mode)                       \
	INTERN ATTR_IN(1) void CC                                                         \
	libvideo_swgfx_generic__putcolor_##name(struct video_gfx const *__restrict self,  \
	                                        video_coord_t x, video_coord_t y,         \
	                                        video_color_t color) {                    \
		video_pixel_t op = LL_getpixel(self, x, y);                                   \
		video_color_t oc = video_format_pixel2color(&self->vx_buffer->vb_format, op); \
		video_color_t nc = gfx_blendcolors(oc, color, mode);                          \
		video_pixel_t np = video_format_color2pixel(&self->vx_buffer->vb_format, nc); \
		LL_setpixel(self, x, y, np);                                                  \
	}
GFX_FOREACH_DEDICATED_BLENDMODE(DEFINE_libvideo_swgfx_generic__putcolor_FOO)
#undef DEFINE_libvideo_swgfx_generic__putcolor_FOO


#define DEFINE_libvideo_swgfx_generic__putcolor_FOO(name, mode)                       \
	INTERN ATTR_IN(1) void CC                                                         \
	libvideo_swgfx_generic__putcolor_##name(struct video_gfx const *__restrict self,  \
	                                        video_coord_t x, video_coord_t y,         \
	                                        video_color_t color) {                    \
		video_pixel_t op = LL_getpixel(self, x, y);                                   \
		video_color_t oc = video_format_pixel2color(&self->vx_buffer->vb_format, op); \
		video_color_t cc = GFX_BLENDMODE_GET_COLOR(self->vx_blend);                   \
		video_color_t nc = gfx_blendcolors_constant(oc, color, mode, cc);             \
		video_pixel_t np = video_format_color2pixel(&self->vx_buffer->vb_format, nc); \
		LL_setpixel(self, x, y, np);                                                  \
	}
GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(DEFINE_libvideo_swgfx_generic__putcolor_FOO)
#undef DEFINE_libvideo_swgfx_generic__putcolor_FOO





/* Generic, always-valid GFX functions (using only `vx_pxops') */
INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__absline_llhh(struct video_gfx const *__restrict self,
                                     video_coord_t dst_x, video_coord_t dst_y,
                                     video_dim_t size_x, video_dim_t size_y,
                                     video_color_t color) {
	video_dim_t step;
	TRACE_START("swgfx_generic__absline_llhh("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ")\n",
	            dst_x, dst_y, size_x, size_y, color);
	gfx_assert(size_x > 0);
	gfx_assert(size_y > 0);
	step = 0;
	if (size_x > size_y) {
		video_coord_t line_lox = 0;
		do {
			video_coord_t line_hix = (video_dim_t)(((uint64_t)size_x * (step + 1)) / size_y);
			libvideo_swgfx_generic__absline_h(self, dst_x + line_lox, dst_y + step, line_hix - line_lox, color);
			line_lox = line_hix;
		} while (++step < size_y);
	} else if (size_x < size_y) {
		video_coord_t line_loy = 0;
		do {
			video_coord_t line_hiy = (video_dim_t)(((uint64_t)size_y * (step + 1)) / size_x);
			libvideo_swgfx_generic__absline_v(self, dst_x + step, dst_y + line_loy, line_hiy - line_loy, color);
			line_loy = line_hiy;
		} while (++step < size_x);
	} else {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y + step;
			LL_putcolor_p(self, line_x, line_y, color);
		} while (++step < size_x);
	}
	TRACE_END("swgfx_generic__absline_llhh()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__absline_lhhl(struct video_gfx const *__restrict self,
                                     video_coord_t dst_x, video_coord_t dst_y,
                                     video_dim_t size_x, video_dim_t size_y,
                                     video_color_t color) {
	video_dim_t step;
	TRACE_START("swgfx_generic__absline_lhhl("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ")\n",
	            dst_x, dst_y, size_x, size_y, color);
	gfx_assert(size_x > 0);
	gfx_assert(size_y > 0);
	step = 0;
	if (size_x > size_y) {
		video_coord_t line_lox = 0;
		do {
			video_coord_t line_hix = (video_dim_t)(((uint64_t)size_x * (step + 1)) / size_y);
			libvideo_swgfx_generic__absline_h(self, dst_x + line_lox, dst_y - step, line_hix - line_lox, color);
			line_lox = line_hix;
		} while (++step < size_y);
	} else if (size_x < size_y) {
		video_coord_t line_loy = 0;
		do {
			video_coord_t line_hiy = (video_dim_t)(((uint64_t)size_y * (step + 1)) / size_x);
			libvideo_swgfx_generic__absline_v(self, dst_x + step, dst_y - line_hiy + 1, line_hiy - line_loy, color);
			line_loy = line_hiy;
		} while (++step < size_x);
	} else {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y - step;
			LL_putcolor_p(self, line_x, line_y, color);
		} while (++step < size_x);
	}
	TRACE_END("swgfx_generic__absline_lhhl()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__absline_llhh_l(struct video_gfx const *__restrict self,
                                       video_coord_t dst_x, video_coord_t dst_y,
                                       video_dim_t size_x, video_dim_t size_y,
                                       video_color_t color) {
	TRACE_START("swgfx_generic__absline_llhh_l("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ")\n",
	            dst_x, dst_y, size_x, size_y, color);
	if (size_x > size_y) {
		sstretch_fp_t fp_start;
		stretch_fp_t fp_step;
		video_dim_t pad_min;
		video_dim_t pad_max;
		calc_linear_stretch_dim(size_y, size_x, &fp_start,
		                        &fp_step, &pad_min, &pad_max);
		if (pad_min) {
			libvideo_swgfx_generic__absline_h(self, dst_x, dst_y, pad_min, color);
			dst_x += pad_min;
			fp_start += pad_min * fp_step;
			size_x -= pad_min;
		}
		for (size_x -= pad_max; size_x; --size_x, ++dst_x, fp_start += fp_step) {
			linear_fp_blend_t frac_y0 = STRETCH_FP_BLEND_FRAC(fp_start);
			linear_fp_blend_t frac_y1 = LINEAR_FP_BLEND(1) - frac_y0;
			video_coord_t dst_y0 = dst_y + STRETCH_FP_WHOLE(fp_start);
			video_coord_t dst_y1 = dst_y0 + 1;
			video_color_t cy0 = LL_getcolor(self, dst_x, dst_y0);
			video_color_t cy1 = LL_getcolor(self, dst_x, dst_y1);
			cy0 = interpolate_1d(color, cy0, frac_y0, frac_y1);
			cy1 = interpolate_1d(cy1, color, frac_y0, frac_y1);
			LL_putcolor_p(self, dst_x, dst_y0, cy0);
			LL_putcolor_p(self, dst_x, dst_y1, cy1);
		}
		if (pad_max)
			libvideo_swgfx_generic__absline_h(self, dst_x, dst_y + (size_y - 1), pad_max, color);
	} else if (size_x < size_y) {
		sstretch_fp_t fp_start;
		stretch_fp_t fp_step;
		video_dim_t pad_min;
		video_dim_t pad_max;
		calc_linear_stretch_dim(size_x, size_y, &fp_start,
		                        &fp_step, &pad_min, &pad_max);
		if (pad_min) {
			libvideo_swgfx_generic__absline_v(self, dst_x, dst_y, pad_min, color);
			dst_y += pad_min;
			fp_start += pad_min * fp_step;
			size_y -= pad_min;
		}
		for (size_y -= pad_max; size_y; --size_y, ++dst_y, fp_start += fp_step) {
			linear_fp_blend_t frac_x0 = STRETCH_FP_BLEND_FRAC(fp_start);
			linear_fp_blend_t frac_x1 = LINEAR_FP_BLEND(1) - frac_x0;
			video_coord_t dst_x0 = dst_x + STRETCH_FP_WHOLE(fp_start);
			video_coord_t dst_x1 = dst_x0 + 1;
			video_color_t cx0 = LL_getcolor(self, dst_x0, dst_y);
			video_color_t cx1 = LL_getcolor(self, dst_x1, dst_y);
			cx0 = interpolate_1d(color, cx0, frac_x0, frac_x1);
			cx1 = interpolate_1d(cx1, color, frac_x0, frac_x1);
			LL_putcolor_p(self, dst_x0, dst_y, cx0);
			LL_putcolor_p(self, dst_x1, dst_y, cx1);
		}
		if (pad_max)
			libvideo_swgfx_generic__absline_v(self, dst_x + (size_x - 1), dst_y, pad_max, color);
	} else {
		do {
			LL_putcolor_p(self, dst_x, dst_y, color);
			++dst_x;
			++dst_y;
		} while (--size_x);
	}
	TRACE_END("swgfx_generic__absline_llhh_l()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__absline_lhhl_l(struct video_gfx const *__restrict self,
                                       video_coord_t dst_x, video_coord_t dst_y,
                                       video_dim_t size_x, video_dim_t size_y,
                                       video_color_t color) {
	TRACE_START("swgfx_generic__absline_lhhl_l("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ")\n",
	            dst_x, dst_y, size_x, size_y, color);
	if (size_x > size_y) {
		sstretch_fp_t fp_start;
		stretch_fp_t fp_step;
		video_dim_t pad_min;
		video_dim_t pad_max;
		calc_linear_stretch_dim(size_y, size_x, &fp_start,
		                        &fp_step, &pad_min, &pad_max);
		if (pad_min) {
			libvideo_swgfx_generic__absline_h(self, dst_x, dst_y, pad_min, color);
			dst_x += pad_min;
			fp_start += pad_min * fp_step;
			size_x -= pad_min;
		}
		for (size_x -= pad_max; size_x; --size_x, ++dst_x, fp_start += fp_step) {
			linear_fp_blend_t frac_y0 = STRETCH_FP_BLEND_FRAC(fp_start);
			linear_fp_blend_t frac_y1 = LINEAR_FP_BLEND(1) - frac_y0;
			video_coord_t dst_y0 = dst_y - STRETCH_FP_WHOLE(fp_start);
			video_coord_t dst_y1 = dst_y0 - 1;
			video_color_t cy0 = LL_getcolor(self, dst_x, dst_y0);
			video_color_t cy1 = LL_getcolor(self, dst_x, dst_y1);
			cy0 = interpolate_1d(color, cy0, frac_y0, frac_y1);
			cy1 = interpolate_1d(cy1, color, frac_y0, frac_y1);
			LL_putcolor_p(self, dst_x, dst_y0, cy0);
			LL_putcolor_p(self, dst_x, dst_y1, cy1);
		}
		if (pad_max)
			libvideo_swgfx_generic__absline_h(self, dst_x, dst_y - (size_y - 1), pad_max, color);
	} else if (size_x < size_y) {
		sstretch_fp_t fp_start;
		stretch_fp_t fp_step;
		video_dim_t pad_min;
		video_dim_t pad_max;
		calc_linear_stretch_dim(size_x, size_y, &fp_start,
		                        &fp_step, &pad_min, &pad_max);
		if (pad_min) {
			dst_y -= pad_min;
			libvideo_swgfx_generic__absline_v(self, dst_x, dst_y + 1, pad_min, color);
			fp_start += pad_min * fp_step;
			size_y -= pad_min;
		}
		for (size_y -= pad_max; size_y; --size_y, --dst_y, fp_start += fp_step) {
			linear_fp_blend_t frac_x0 = STRETCH_FP_BLEND_FRAC(fp_start);
			linear_fp_blend_t frac_x1 = LINEAR_FP_BLEND(1) - frac_x0;
			video_coord_t dst_x0 = dst_x + STRETCH_FP_WHOLE(fp_start);
			video_coord_t dst_x1 = dst_x0 + 1;
			video_color_t cx0 = LL_getcolor(self, dst_x0, dst_y);
			video_color_t cx1 = LL_getcolor(self, dst_x1, dst_y);
			cx0 = interpolate_1d(color, cx0, frac_x0, frac_x1);
			cx1 = interpolate_1d(cx1, color, frac_x0, frac_x1);
			LL_putcolor_p(self, dst_x0, dst_y, cx0);
			LL_putcolor_p(self, dst_x1, dst_y, cx1);
		}
		if (pad_max) {
			dst_y -= (pad_max - 1);
			libvideo_swgfx_generic__absline_v(self, dst_x + (size_x - 1), dst_y, pad_max, color);
		}
	} else {
		do {
			LL_putcolor_p(self, dst_x, dst_y, color);
			++dst_x;
			--dst_y;
		} while (--size_x);
	}
	TRACE_END("swgfx_generic__absline_lhhl_l()\n");
}



INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__absline_h(struct video_gfx const *__restrict self,
                                  video_coord_t dst_x, video_coord_t dst_y,
                                  video_dim_t length, video_color_t color) {
	do {
		LL_putcolor_p(self, dst_x, dst_y, color);
		++dst_x;
	} while (--length);
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__absline_v(struct video_gfx const *__restrict self,
                                  video_coord_t dst_x, video_coord_t dst_y,
                                  video_dim_t length, video_color_t color) {
	do {
		LL_putcolor_p(self, dst_x, dst_y, color);
		++dst_y;
	} while (--length);
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__absfill(struct video_gfx const *__restrict self,
                                video_coord_t dst_x, video_coord_t dst_y,
                                video_dim_t size_x, video_dim_t size_y,
                                video_color_t color) {
	do {
		LL_absline_h(self, dst_x, dst_y, size_x, color);
		++dst_y;
	} while (--size_y);
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
libvideo_swgfx_generic__absgradient(struct video_gfx const *__restrict self,
                                    video_coord_t dst_x_, video_coord_t dst_y_,
                                    video_dim_t size_x_, video_dim_t size_y_,
                                    video_color_t const colors[2][2]) {
	/* Check for special case: not actually a 4-color gradient */
	if (colors[0][0] == colors[0][1] && colors[1][0] == colors[1][1]) {
		libvideo_swgfx_generic__absgradient_v(self, dst_x_, dst_y_, size_x_, size_y_,
		                                      colors[0][0], colors[1][0]);
		return;
	} else if (colors[0][0] == colors[1][0] && colors[0][1] == colors[1][1]) {
		libvideo_swgfx_generic__absgradient_h(self, dst_x_, dst_y_, size_x_, size_y_,
		                                      colors[0][0], colors[0][1]);
		return;
	}

#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)         \
	{                                                                                     \
		video_color_t out = colors[src_y][src_x];                                         \
		libvideo_swgfx_generic__absfill(self, dst_x, dst_y, dst_size_x, dst_size_y, out); \
	}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                       \
		video_color_t src_y0_x0 = colors[src_y][src_x0];                                    \
		video_color_t src_y0_x1 = colors[src_y][src_x1];                                    \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);   \
		libvideo_swgfx_generic__absline_v(self, dst_x, dst_y, dst_size_y, out);             \
	}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                       \
		video_color_t src_y0_x0 = colors[src_y0][src_x];                                    \
		video_color_t src_y1_x0 = colors[src_y1][src_x];                                    \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);   \
		libvideo_swgfx_generic__absline_h(self, dst_x, dst_y, dst_size_x, out);             \
	}

#define pixel_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                 \
		video_color_t src_y0_x0 = colors[src_y0][src_x0];                                             \
		video_color_t src_y0_x1 = colors[src_y0][src_x1];                                             \
		video_color_t src_y1_x0 = colors[src_y1][src_x0];                                             \
		video_color_t src_y1_x1 = colors[src_y1][src_x1];                                             \
		video_color_t out = interpolate_2d(src_y0_x0, src_y0_x1,                                      \
		                                   src_y1_x0, src_y1_x1,                                      \
		                                   frac_x0, frac_x1,                                          \
		                                   frac_y0, frac_y1);                                         \
		LL_putcolor_p(self, dst_x, dst_y, out);                                                       \
	}

	TRACE_START("swgfx_generic__absgradient("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {{%#" PRIxCOL ", %#" PRIxCOL "}, {%#" PRIxCOL ", %#" PRIxCOL "}})\n",
	            dst_x_, dst_y_, size_x_, size_y_,
	            colors[0][0], colors[0][1], colors[1][0], colors[1][1]);
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
	TRACE_END("swgfx_generic__absgradient()\n");
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

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__absgradient_h(struct video_gfx const *__restrict self,
                                      video_coord_t dst_x, video_coord_t dst_y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      video_color_t locolor, video_color_t hicolor) {
	video_dim_t pad_xmin, pad_xmax;
	sstretch_fp_t fp_src_x;
	stretch_fp_t fp_step_x;

	/* Check for special case: not actually a gradient */
	if (locolor == hicolor) {
		libvideo_swgfx_generic__absfill(self, dst_x, dst_y, size_x, size_y, locolor);
		return;
	}

	TRACE_START("swgfx_generic__absgradient_h("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {%#" PRIxCOL ", %#" PRIxCOL "})\n",
	            dst_x, dst_y, size_x, size_y,
	            locolor, hicolor);
	calc_linear_stretch_dim(2, size_x, &fp_src_x, &fp_step_x, &pad_xmin, &pad_xmax);
	if (pad_xmin) {
		libvideo_swgfx_generic__absfill(self, dst_x, dst_y, pad_xmin, size_y, locolor);
		dst_x += pad_xmin;
		size_x -= pad_xmin;
		fp_src_x += pad_xmin * fp_step_x;
	}
	if (pad_xmax) {
		size_x -= pad_xmax;
		libvideo_swgfx_generic__absfill(self, dst_x + size_x, dst_y, pad_xmax, size_y, hicolor);
	}
	for (; size_x; --size_x, ++dst_x, fp_src_x += fp_step_x) {
		linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_x);
		linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
		video_color_t color = interpolate_1d(locolor, hicolor, frac0, frac1);
		libvideo_swgfx_generic__absline_v(self, dst_x, dst_y, size_y, color);
	}
	TRACE_END("swgfx_generic__absgradient_h()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__absgradient_v(struct video_gfx const *__restrict self,
                                      video_coord_t dst_x, video_coord_t dst_y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      video_color_t locolor, video_color_t hicolor) {
	video_dim_t pad_ymin, pad_ymax;
	sstretch_fp_t fp_src_y;
	stretch_fp_t fp_step_y;

	/* Check for special case: not actually a gradient */
	if (locolor == hicolor) {
		libvideo_swgfx_generic__absfill(self, dst_x, dst_y, size_x, size_y, locolor);
		return;
	}

	TRACE_START("swgfx_generic__absgradient_v("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {%#" PRIxCOL ", %#" PRIxCOL "})\n",
	            dst_x, dst_y, size_x, size_y,
	            locolor, hicolor);
	calc_linear_stretch_dim(2, size_y, &fp_src_y, &fp_step_y, &pad_ymin, &pad_ymax);
	if (pad_ymin) {
		libvideo_swgfx_generic__absfill(self, dst_x, dst_y, size_x, pad_ymin, locolor);
		dst_y += pad_ymin;
		size_y -= pad_ymin;
		fp_src_y += pad_ymin * fp_step_y;
	}
	if (pad_ymax) {
		size_y -= pad_ymax;
		libvideo_swgfx_generic__absfill(self, dst_x, dst_y + size_y, size_x, pad_ymax, hicolor);
	}
	for (; size_y; --size_y, ++dst_y, fp_src_y += fp_step_y) {
		linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_y);
		linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
		video_color_t color = interpolate_1d(locolor, hicolor, frac0, frac1);
		libvideo_swgfx_generic__absline_h(self, dst_x, dst_y, size_x, color);
	}
	TRACE_END("swgfx_generic__absgradient_v()\n");
}




/************************************************************************/
/* BIT-MASKED FILL                                                      */
/************************************************************************/

PRIVATE ATTR_NOINLINE ATTR_IN(1) ATTR_IN(7) void CC
libvideo_swgfx_generic__fillmask1(struct video_gfx const *__restrict self,
                                  video_coord_t dst_x, video_coord_t dst_y,
                                  video_dim_t size_x, video_dim_t size_y,
                                  video_color_t color,
                                  struct video_bitmask const *__restrict bm,
                                  __REGISTER_TYPE__ bm_xor) {
	byte_t const *bitmask;
	uintptr_t bitskip;
	TRACE_START("swgfx_generic__fillmask1("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", bm: %p+%" PRIuPTR ", "
	            "bm_xor: %#" PRIxN(__SIZEOF_REGISTER__) ")\n",
	            dst_x, dst_y, size_x, size_y, color, bm->vbm_mask, bm->vbm_skip, bm_xor);
	bitmask = (byte_t const *)bm->vbm_mask;
	bitskip = bm->vbm_skip;
	bitmask += bitskip / NBBY;
	bitskip = bitskip % NBBY;
#ifndef __OPTIMIZE_SIZE__
	if likely(bitskip == 0 && !(bm->vbm_scan & 7)) {
		size_t bm_scanline = bm->vbm_scan >> 3;
		switch (size_x) {
#define DO_FIXED_WORD_RENDER(N)                                                     \
			do {                                                                    \
				video_dim_t x = dst_x;                                              \
				uint##N##_t word = UNALIGNED_GET##N(bitmask) ^                      \
				                   (uint##N##_t)bm_xor;                             \
				while (word) {                                                      \
					shift_t bits;                                                   \
					bits = CLZ((uint##N##_t)word);                                  \
					x += bits;                                                      \
					word <<= bits;                                                  \
					bits = CLZ((uint##N##_t) ~word);                                \
					gfx_assert(bits > 0);                                           \
					libvideo_swgfx_generic__absline_h(self, x, dst_y, bits, color); \
					x += bits;                                                      \
					word <<= bits;                                                  \
				}                                                                   \
				++dst_y;                                                            \
				bitmask += bm_scanline;                                             \
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
			libvideo_swgfx_generic__absline_h(self, dst_x + x, dst_y, count, color);
			x += count;
		} while (x < size_x);
next_row:
		bitskip += bm->vbm_scan;
		bitmask += bitskip / NBBY;
		bitskip = bitskip % NBBY;
		++dst_y;
	} while (--size_y);
#ifndef __OPTIMIZE_SIZE__
done:
#endif /* !__OPTIMIZE_SIZE__ */
	TRACE_END("swgfx_generic__fillmask1()\n");
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC
libvideo_swgfx_generic__fillmask(struct video_gfx const *__restrict self,
                                 video_coord_t dst_x, video_coord_t dst_y,
                                 video_dim_t size_x, video_dim_t size_y,
                                 video_color_t const bg_fg_colors[2],
                                 struct video_bitmask const *__restrict bm) {
	byte_t const *bitmask;
	uintptr_t bitskip;
	TRACE_START("swgfx_generic__fillmask("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "bg_fg_colors: {%#" PRIxCOL ", %#" PRIxCOL "}, bm: %p+%" PRIuPTR ")\n",
	            dst_x, dst_y, size_x, size_y, bg_fg_colors[0], bg_fg_colors[1],
	            bm->vbm_mask, bm->vbm_skip);
	bitmask = (byte_t const *)bm->vbm_mask;
	bitskip = bm->vbm_skip;
	bitmask += bitskip / NBBY;
	bitskip = bitskip % NBBY;
#ifndef __OPTIMIZE_SIZE__
	if likely(bitskip == 0 && !(bm->vbm_scan & 7)) {
		size_t bm_scanline = bm->vbm_scan >> 3;
		switch (size_x) {
#define DO_FIXED_WORD_RENDER(N)                                                                   \
			do {                                                                                  \
				video_dim_t x = dst_x;                                                            \
				uint##N##_t word = UNALIGNED_GET##N(bitmask);                                     \
				while (word) {                                                                    \
					shift_t bits;                                                                 \
					bits = CLZ((uint##N##_t)word);                                                \
					if (bits) {                                                                   \
						libvideo_swgfx_generic__absline_h(self, x, dst_y, bits, bg_fg_colors[0]); \
						x += bits;                                                                \
					}                                                                             \
					word <<= bits;                                                                \
					bits = CLZ((uint##N##_t) ~word);                                              \
					gfx_assert(bits > 0);                                                         \
					libvideo_swgfx_generic__absline_h(self, x, dst_y, bits, bg_fg_colors[1]);     \
					x += bits;                                                                    \
					word <<= bits;                                                                \
				}                                                                                 \
				++dst_y;                                                                          \
				bitmask += bm_scanline;                                                           \
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
				libvideo_swgfx_generic__absline_h(self, dst_x + x, dst_y, count, bg_fg_colors[0]);
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
			libvideo_swgfx_generic__absline_h(self, dst_x + x, dst_y, count, bg_fg_colors[1]);
			x += count;
		} while (x < size_x);
/*next_row:*/
		bitskip += bm->vbm_scan;
		bitmask += bitskip / NBBY;
		bitskip = bitskip % NBBY;
		++dst_y;
	} while (--size_y);
#ifndef __OPTIMIZE_SIZE__
done:
#endif /* !__OPTIMIZE_SIZE__ */
	TRACE_END("swgfx_generic__fillmask()\n");
}

PRIVATE ATTR_NOINLINE ATTR_IN(1) ATTR_IN(9) void CC
libvideo_swgfx_generic__fillstretchmask_l__alpha_only(struct video_gfx const *__restrict self,
                                                      video_coord_t dst_x_, video_coord_t dst_y_,
                                                      video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                                      video_color_t color,
                                                      video_dim_t src_size_x_, video_dim_t src_size_y_,
                                                      struct video_bitmask const *__restrict bm,
                                                      __REGISTER_TYPE__ bm_xor) {
	uintptr_t bitskip_;
	byte_t const *bitmask;
	video_color_t raw_color;
	channel_t raw_alpha;
	if (libvideo_gfx_allow_ignore(self, color))
		return;
	bitskip_  = bm->vbm_skip;
	bitmask   = (byte_t const *)bm->vbm_mask;
	raw_color = color & ~VIDEO_COLOR_ALPHA_MASK;
	raw_alpha = VIDEO_COLOR_GET_ALPHA(color);
#define makealpha(alpha_chan) (channel_t)(((twochannels_t)raw_alpha * (alpha_chan)) / CHANNEL_MAX)
#define makecolor(alpha_chan) (raw_color | ((video_color_t)makealpha(alpha_chan) << VIDEO_COLOR_ALPHA_SHIFT))
	bitmask += bitskip_ / NBBY;
	bitskip_ = bitskip_ % NBBY;
#define getbit(src_x, src_y) (bitmask2d_getbit_channel(bitmask, bm->vbm_scan, src_x, src_y) ^ (byte_t)bm_xor)

#define bitmask_blend_xmax_ymin bitmask_blend_xmin_ymin
#define bitmask_blend_xmin_ymax bitmask_blend_xmin_ymin
#define bitmask_blend_xmax_ymax bitmask_blend_xmin_ymin
#define bitmask_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)             \
	{                                                                                           \
		if (getbit(src_x, src_y))                                                               \
			libvideo_swgfx_generic__absfill(self, dst_x, dst_y, dst_size_x, dst_size_y, color); \
	}

#define bitmask_blend_ymax bitmask_blend_ymin
#define bitmask_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                         \
		channel_t src_y0_x0 = getbit(src_x0, src_y);                                          \
		channel_t src_y0_x1 = getbit(src_x1, src_y);                                          \
		channel_t chan = interpolate_channel_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);      \
		if (chan) {                                                                           \
			video_color_t out = makecolor(chan);                                              \
			libvideo_swgfx_generic__absline_v(self, dst_x, dst_y, dst_size_y, out);           \
		}                                                                                     \
	}

#define bitmask_blend_xmax bitmask_blend_xmin
#define bitmask_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                         \
		channel_t src_y0_x0 = getbit(src_x, src_y0);                                          \
		channel_t src_y1_x0 = getbit(src_x, src_y1);                                          \
		channel_t chan = interpolate_channel_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);      \
		if (chan) {                                                                           \
			video_color_t out = makecolor(chan);                                              \
			libvideo_swgfx_generic__absline_h(self, dst_x, dst_y, dst_size_x, out);           \
		}                                                                                     \
	}

#define bitmask_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                   \
		channel_t src_y0_x0 = getbit(src_x0, src_y0);                                                   \
		channel_t src_y0_x1 = getbit(src_x1, src_y0);                                                   \
		channel_t src_y1_x0 = getbit(src_x0, src_y1);                                                   \
		channel_t src_y1_x1 = getbit(src_x1, src_y1);                                                   \
		channel_t chan = interpolate_channel_2d(src_y0_x0, src_y0_x1,                                   \
		                                        src_y1_x0, src_y1_x1,                                   \
		                                        frac_x0, frac_x1,                                       \
		                                        frac_y0, frac_y1);                                      \
		if (chan) {                                                                                     \
			video_color_t out = makecolor(chan);                                                        \
			LL_putcolor_p(self, dst_x, dst_y, out);                                                     \
		}                                                                                               \
	}

	TRACE_START("swgfx_generic__fillstretchmask_l__alpha_only("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", "
	            "src: {%" PRIuDIM "x%" PRIuDIM "}, bm: %p+%" PRIuPTR ")\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            color, src_size_x_, src_size_y_, bm->vbm_mask, bm->vbm_skip);
	GFX_LINEAR_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                   bitskip_, 0, src_size_x_, src_size_y_,
	                   bitmask_blend_xmin_ymin,
	                   bitmask_blend_ymin,
	                   bitmask_blend_xmax_ymin,
	                   bitmask_blend_xmin,
	                   bitmask_blend,
	                   bitmask_blend_xmax,
	                   bitmask_blend_xmin_ymax,
	                   bitmask_blend_ymax,
	                   bitmask_blend_xmax_ymax);
	TRACE_END("swgfx_generic__fillstretchmask_l__alpha_only()\n");
#undef bitmask_blend_xmin_ymin
#undef bitmask_blend_ymin
#undef bitmask_blend_xmax_ymin
#undef bitmask_blend_xmin
#undef bitmask_blend
#undef bitmask_blend_xmax
#undef bitmask_blend_xmin_ymax
#undef bitmask_blend_ymax
#undef bitmask_blend_xmax_ymax

#undef getbit
#undef makealpha
#undef makecolor
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
libvideo_swgfx_generic__fillstretchmask_l(struct video_gfx const *__restrict self,
                                          video_coord_t dst_x_, video_coord_t dst_y_,
                                          video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                          video_color_t const bg_fg_colors[2],
                                          video_dim_t src_size_x_, video_dim_t src_size_y_,
                                          struct video_bitmask const *__restrict bm) {
	uintptr_t bitskip_;
	byte_t const *bitmask;

	/* Need to do full blending of colors */
	bitskip_ = bm->vbm_skip;
	bitmask = (byte_t const *)bm->vbm_mask;
	bitmask += bitskip_ / NBBY;
	bitskip_ = bitskip_ % NBBY;
#define bm_getcolor(x, y) bg_fg_colors[bitmask2d_getbit(bitmask, bm->vbm_scan, x, y)]

#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)         \
	{                                                                                     \
		video_color_t out = bm_getcolor(src_x, src_y);                                    \
		libvideo_swgfx_generic__absfill(self, dst_x, dst_y, dst_size_x, dst_size_y, out); \
	}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                       \
		video_color_t src_y0_x0 = bm_getcolor(src_x0, src_y);                               \
		video_color_t src_y0_x1 = bm_getcolor(src_x1, src_y);                               \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);   \
		libvideo_swgfx_generic__absline_v(self, dst_x, dst_y, dst_size_y, out);             \
	}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                       \
		video_color_t src_y0_x0 = bm_getcolor(src_x, src_y0);                               \
		video_color_t src_y1_x0 = bm_getcolor(src_x, src_y1);                               \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);   \
		libvideo_swgfx_generic__absline_h(self, dst_x, dst_y, dst_size_x, out);             \
	}

#define pixel_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                 \
		video_color_t src_y0_x0 = bm_getcolor(src_x0, src_y0);                                        \
		video_color_t src_y0_x1 = bm_getcolor(src_x1, src_y0);                                        \
		video_color_t src_y1_x0 = bm_getcolor(src_x0, src_y1);                                        \
		video_color_t src_y1_x1 = bm_getcolor(src_x1, src_y1);                                        \
		video_color_t out = interpolate_2d(src_y0_x0, src_y0_x1,                                      \
		                                   src_y1_x0, src_y1_x1,                                      \
		                                   frac_x0, frac_x1,                                          \
		                                   frac_y0, frac_y1);                                         \
		LL_putcolor_p(self, dst_x, dst_y, out);                                                       \
	}

	TRACE_START("swgfx_generic__fillstretchmask_l("
	            "self: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "bg_fg_colors: {%#" PRIxCOL ", %#" PRIxCOL "}, "
	            "src: {%" PRIuDIM "x%" PRIuDIM "}, bm: %p+%" PRIuPTR ")\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            bg_fg_colors[0], bg_fg_colors[0],
	            src_size_x_, src_size_y_, bm->vbm_mask, bm->vbm_skip);
	GFX_LINEAR_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                   bitskip_, 0, src_size_x_, src_size_y_,
	                   pixel_blend_xmin_ymin,
	                   pixel_blend_ymin,
	                   pixel_blend_xmax_ymin,
	                   pixel_blend_xmin,
	                   pixel_blend,
	                   pixel_blend_xmax,
	                   pixel_blend_xmin_ymax,
	                   pixel_blend_ymax,
	                   pixel_blend_xmax_ymax);
	TRACE_END("swgfx_generic__fillstretchmask_l()\n");
#undef pixel_blend_xmin_ymin
#undef pixel_blend_ymin
#undef pixel_blend_xmax_ymin
#undef pixel_blend_xmin
#undef pixel_blend
#undef pixel_blend_xmax
#undef pixel_blend_xmin_ymax
#undef pixel_blend_ymax
#undef pixel_blend_xmax_ymax
#undef bm_getcolor
}

PRIVATE ATTR_IN(1) ATTR_IN(9) void CC
libvideo_swgfx_generic__fillstretchmask1_n(struct video_gfx const *__restrict self,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_dim_t dst_size_x, video_dim_t dst_size_y,
                                           video_color_t color,
                                           video_dim_t src_size_x, video_dim_t src_size_y,
                                           struct video_bitmask const *__restrict bm,
                                           __REGISTER_TYPE__ bm_xor) {
	video_dim_t y;
	stretch_fp_t step_x, step_y, src_pos_y;
	if ((src_size_x < (dst_size_x >> 1)) &&
	    (src_size_y < (dst_size_y >> 1))) {
		/* XXX: Iterate across "src" and use "libvideo_swgfx_generic__absfill"
		 *      to  fill  rects   associated  with   visible  source   pixels. */
	}
	TRACE_START("swgfx_generic__fillstretchmask1_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", "
	            "src: {%" PRIuDIM "x%" PRIuDIM "}, bm: %p+%" PRIuPTR ")\n",
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            color, src_size_x, src_size_y, bm->vbm_mask, bm->vbm_skip);
	step_x = STRETCH_FP(src_size_x) / dst_size_x;
	step_y = STRETCH_FP(src_size_y) / dst_size_y;
	src_pos_y = step_y >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
	y = 0;
	do {
		video_coord_t row_dst_y = dst_y + y;
		video_coord_t row_src_y = STRETCH_FP_WHOLE(src_pos_y);
		stretch_fp_t src_pos_x = step_x >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
		video_dim_t x = 0;
		uintptr_t row_bitno = bm->vbm_skip + row_src_y * bm->vbm_scan;
		do {
			video_coord_t row_src_x = STRETCH_FP_WHOLE(src_pos_x);
			uintptr_t bitno = row_bitno + row_src_x;
			if ((((byte_t const *)bm->vbm_mask)[bitno / NBBY] ^ bm_xor) &
			    ((byte_t)1 << ((NBBY - 1) - (bitno % NBBY))))
				LL_putcolor_p(self, dst_x + x, row_dst_y, color);
			src_pos_x += step_x;
			++x;
		} while (x < dst_size_x);
		++y;
		src_pos_y += step_y;
	} while (y < dst_size_y);
	TRACE_END("swgfx_generic__fillstretchmask1_n()\n");
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
libvideo_swgfx_generic__fillstretchmask_n(struct video_gfx const *__restrict self,
                                          video_coord_t dst_x, video_coord_t dst_y,
                                          video_dim_t dst_size_x, video_dim_t dst_size_y,
                                          video_color_t const bg_fg_colors[2],
                                          video_dim_t src_size_x, video_dim_t src_size_y,
                                          struct video_bitmask const *__restrict bm) {
	video_dim_t y;
	stretch_fp_t step_x, step_y, src_pos_y;
	if ((src_size_x < (dst_size_x >> 1)) &&
	    (src_size_y < (dst_size_y >> 1))) {
		/* XXX: Iterate across "src" and use "libvideo_swgfx_generic__absfill"
		 *      to  fill  rects   associated  with   visible  source   pixels. */
	}
	TRACE_START("swgfx_generic__fillstretchmask_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "bg_fg_colors: {%#" PRIxCOL ", %#" PRIxCOL "}, "
	            "src: {%" PRIuDIM "x%" PRIuDIM "}, bm: %p+%" PRIuPTR ")\n",
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            bg_fg_colors[0], bg_fg_colors[1],
	            src_size_x, src_size_y, bm->vbm_mask, bm->vbm_skip);
	step_x = STRETCH_FP(src_size_x) / dst_size_x;
	step_y = STRETCH_FP(src_size_y) / dst_size_y;
	src_pos_y = step_y >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
	y = 0;
	do {
		video_coord_t row_dst_y = dst_y + y;
		video_coord_t row_src_y = STRETCH_FP_WHOLE(src_pos_y);
		stretch_fp_t src_pos_x = step_x >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
		video_dim_t x = 0;
		uintptr_t row_bitno = bm->vbm_skip + row_src_y * bm->vbm_scan;
		do {
			video_coord_t row_src_x = STRETCH_FP_WHOLE(src_pos_x);
			uintptr_t bitno = row_bitno + row_src_x;
			byte_t byte = ((byte_t const *)bm->vbm_mask)[bitno / NBBY];
			byte_t bit  = (byte >> ((NBBY - 1) - (bitno % NBBY))) & 1;
			LL_putcolor_p(self, dst_x + x, row_dst_y, bg_fg_colors[bit]);
			src_pos_x += step_x;
			++x;
		} while (x < dst_size_x);
		++y;
		src_pos_y += step_y;
	} while (y < dst_size_y);
	TRACE_END("swgfx_generic__fillstretchmask_n()\n");
}



/* Custom pre-blending GFX functions */
#define DEFINE_libvideo_swgfx_generic__render_preblend_FOO(name, mode, preblend_name, preblend)          \
	INTERN ATTR_IN(1) void CC                                                                            \
	libvideo_swgfx_preblend__absline_llhh__##name(struct video_gfx const *__restrict self,               \
	                                              video_coord_t dst_x, video_coord_t dst_y,              \
	                                              video_dim_t size_x, video_dim_t size_y,                \
	                                              video_color_t color) {                                 \
		color = preblend(self->vx_blend, color);                                                         \
		if (preblend##_mayignore(self->vx_blend, color))                                                 \
			return;                                                                                      \
		if (preblend##_maynblend(self->vx_blend, color)) {                                               \
			libvideo_swgfx_noblend__absline_llhh(self, dst_x, dst_y, size_x, size_y, color);             \
		} else {                                                                                         \
			libvideo_swgfx_generic__absline_llhh(self, dst_x, dst_y, size_x, size_y, color);             \
		}                                                                                                \
	}                                                                                                    \
	INTERN ATTR_IN(1) void CC                                                                            \
	libvideo_swgfx_preblend__absline_lhhl__##name(struct video_gfx const *__restrict self,               \
	                                              video_coord_t dst_x, video_coord_t dst_y,              \
	                                              video_dim_t size_x, video_dim_t size_y,                \
	                                              video_color_t color) {                                 \
		color = preblend(self->vx_blend, color);                                                         \
		if (preblend##_mayignore(self->vx_blend, color))                                                 \
			return;                                                                                      \
		if (preblend##_maynblend(self->vx_blend, color)) {                                               \
			libvideo_swgfx_noblend__absline_lhhl(self, dst_x, dst_y, size_x, size_y, color);             \
		} else {                                                                                         \
			libvideo_swgfx_generic__absline_lhhl(self, dst_x, dst_y, size_x, size_y, color);             \
		}                                                                                                \
	}                                                                                                    \
	INTERN ATTR_IN(1) void CC                                                                            \
	libvideo_swgfx_preblend__absline_llhh_l__##name(struct video_gfx const *__restrict self,             \
	                                                video_coord_t dst_x, video_coord_t dst_y,            \
	                                                video_dim_t size_x, video_dim_t size_y,              \
	                                                video_color_t color) {                               \
		color = preblend(self->vx_blend, color);                                                         \
		if (preblend##_mayignore(self->vx_blend, color))                                                 \
			return;                                                                                      \
		libvideo_swgfx_generic__absline_llhh_l(self, dst_x, dst_y, size_x, size_y, color);               \
	}                                                                                                    \
	INTERN ATTR_IN(1) void CC                                                                            \
	libvideo_swgfx_preblend__absline_lhhl_l__##name(struct video_gfx const *__restrict self,             \
	                                                video_coord_t dst_x, video_coord_t dst_y,            \
	                                                video_dim_t size_x, video_dim_t size_y,              \
	                                                video_color_t color) {                               \
		color = preblend(self->vx_blend, color);                                                         \
		if (preblend##_mayignore(self->vx_blend, color))                                                 \
			return;                                                                                      \
		libvideo_swgfx_generic__absline_lhhl_l(self, dst_x, dst_y, size_x, size_y, color);               \
	}                                                                                                    \
	INTERN ATTR_IN(1) void CC                                                                            \
	libvideo_swgfx_preblend__absline_h__##name(struct video_gfx const *__restrict self,                  \
	                                           video_coord_t dst_x, video_coord_t dst_y,                 \
	                                           video_dim_t length, video_color_t color) {                \
		color = preblend(self->vx_blend, color);                                                         \
		if (preblend##_mayignore(self->vx_blend, color))                                                 \
			return;                                                                                      \
		if (preblend##_maynblend(self->vx_blend, color)) {                                               \
			libvideo_swgfx_noblend__absline_h(self, dst_x, dst_y, length, color);                        \
		} else {                                                                                         \
			libvideo_swgfx_generic__absline_h(self, dst_x, dst_y, length, color);                        \
		}                                                                                                \
	}                                                                                                    \
	INTERN ATTR_IN(1) void CC                                                                            \
	libvideo_swgfx_preblend__absline_v__##name(struct video_gfx const *__restrict self,                  \
	                                           video_coord_t dst_x, video_coord_t dst_y,                 \
	                                           video_dim_t length, video_color_t color) {                \
		color = preblend(self->vx_blend, color);                                                         \
		if (preblend##_mayignore(self->vx_blend, color))                                                 \
			return;                                                                                      \
		if (preblend##_maynblend(self->vx_blend, color)) {                                               \
			libvideo_swgfx_noblend__absline_v(self, dst_x, dst_y, length, color);                        \
		} else {                                                                                         \
			libvideo_swgfx_generic__absline_v(self, dst_x, dst_y, length, color);                        \
		}                                                                                                \
	}                                                                                                    \
	INTERN ATTR_IN(1) void CC                                                                            \
	libvideo_swgfx_preblend__absfill__##name(struct video_gfx const *__restrict self,                    \
	                                         video_coord_t dst_x, video_coord_t dst_y,                   \
	                                         video_dim_t size_x, video_dim_t size_y,                     \
	                                         video_color_t color) {                                      \
		color = preblend(self->vx_blend, color);                                                         \
		if (preblend##_mayignore(self->vx_blend, color))                                                 \
			return;                                                                                      \
		if (preblend##_maynblend(self->vx_blend, color)) {                                               \
			libvideo_swgfx_noblend__absfill(self, dst_x, dst_y, size_x, size_y, color);                  \
		} else {                                                                                         \
			libvideo_swgfx_generic__absfill(self, dst_x, dst_y, size_x, size_y, color);                  \
		}                                                                                                \
	}                                                                                                    \
	INTERN ATTR_IN(1) ATTR_IN(6) void CC                                                                 \
	libvideo_swgfx_preblend__absgradient__##name(struct video_gfx const *__restrict self,                \
	                                             video_coord_t dst_x, video_coord_t dst_y,               \
	                                             video_dim_t size_x, video_dim_t size_y,                 \
	                                             video_color_t const colors[2][2]) {                     \
		video_color_t preblend_colors[2][2];                                                             \
		preblend_colors[0][0] = preblend(self->vx_blend, colors[0][0]);                                  \
		preblend_colors[0][1] = preblend(self->vx_blend, colors[0][1]);                                  \
		preblend_colors[1][0] = preblend(self->vx_blend, colors[1][0]);                                  \
		preblend_colors[1][1] = preblend(self->vx_blend, colors[1][1]);                                  \
		if (preblend##_mayignore(self->vx_blend, preblend_colors[0][0]) &&                               \
		    preblend##_mayignore(self->vx_blend, preblend_colors[0][1]) &&                               \
		    preblend##_mayignore(self->vx_blend, preblend_colors[1][0]) &&                               \
		    preblend##_mayignore(self->vx_blend, preblend_colors[1][1]))                                 \
			return;                                                                                      \
		if ((self->vx_buffer->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) &&   \
		    preblend##_maynblend(self->vx_blend, preblend_colors[0][0]) &&                               \
		    preblend##_maynblend(self->vx_blend, preblend_colors[0][1]) &&                               \
		    preblend##_maynblend(self->vx_blend, preblend_colors[1][0]) &&                               \
		    preblend##_maynblend(self->vx_blend, preblend_colors[1][1])) {                               \
			libvideo_swgfx_noblend_interp8888__absgradient(self, dst_x, dst_y,                           \
			                                               size_x, size_y, preblend_colors);             \
			return;                                                                                      \
		}                                                                                                \
		libvideo_swgfx_generic__absgradient(self, dst_x, dst_y, size_x, size_y, preblend_colors);        \
	}                                                                                                    \
	INTERN ATTR_IN(1) void CC                                                                            \
	libvideo_swgfx_preblend__absgradient_h__##name(struct video_gfx const *__restrict self,              \
	                                               video_coord_t dst_x, video_coord_t dst_y,             \
	                                               video_dim_t size_x, video_dim_t size_y,               \
	                                               video_color_t locolor, video_color_t hicolor) {       \
		locolor = preblend(self->vx_blend, locolor);                                                     \
		hicolor = preblend(self->vx_blend, hicolor);                                                     \
		if (preblend##_mayignore(self->vx_blend, locolor) &&                                             \
		    preblend##_mayignore(self->vx_blend, hicolor))                                               \
			return;                                                                                      \
		if ((self->vx_buffer->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) &&   \
		    preblend##_maynblend(self->vx_blend, locolor) &&                                             \
		    preblend##_maynblend(self->vx_blend, hicolor)) {                                             \
			libvideo_swgfx_noblend_interp8888__absgradient_h(self, dst_x, dst_y, size_x, size_y,         \
			                                                 locolor, hicolor);                          \
			return;                                                                                      \
		}                                                                                                \
		libvideo_swgfx_generic__absgradient_h(self, dst_x, dst_y, size_x, size_y, locolor, hicolor);     \
	}                                                                                                    \
	INTERN ATTR_IN(1) void CC                                                                            \
	libvideo_swgfx_preblend__absgradient_v__##name(struct video_gfx const *__restrict self,              \
	                                               video_coord_t dst_x, video_coord_t dst_y,             \
	                                               video_dim_t size_x, video_dim_t size_y,               \
	                                               video_color_t locolor, video_color_t hicolor) {       \
		locolor = preblend(self->vx_blend, locolor);                                                     \
		hicolor = preblend(self->vx_blend, hicolor);                                                     \
		if (preblend##_mayignore(self->vx_blend, locolor) &&                                             \
		    preblend##_mayignore(self->vx_blend, hicolor))                                               \
			return;                                                                                      \
		if ((self->vx_buffer->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) &&   \
		    preblend##_maynblend(self->vx_blend, locolor) &&                                             \
		    preblend##_maynblend(self->vx_blend, hicolor)) {                                             \
			libvideo_swgfx_noblend_interp8888__absgradient_v(self, dst_x, dst_y, size_x, size_y,         \
			                                                 locolor, hicolor);                          \
			return;                                                                                      \
		}                                                                                                \
		libvideo_swgfx_generic__absgradient_v(self, dst_x, dst_y, size_x, size_y, locolor, hicolor);     \
	}                                                                                                    \
	INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC                                                      \
	libvideo_swgfx_preblend__fillmask__##name(struct video_gfx const *__restrict self,                   \
	                                          video_coord_t dst_x, video_coord_t dst_y,                  \
	                                          video_dim_t size_x, video_dim_t size_y,                    \
	                                          video_color_t const bg_fg_colors[2],                       \
	                                          struct video_bitmask const *__restrict bm) {               \
		video_color_t preblend_bg_fg_colors[2];                                                          \
		preblend_bg_fg_colors[0] = preblend(self->vx_blend, bg_fg_colors[0]);                            \
		preblend_bg_fg_colors[1] = preblend(self->vx_blend, bg_fg_colors[1]);                            \
		/* Optimization when only one (FG or  BG) can be rendered w/o  blending,                         \
		 * and  the other would be a no-op during blending. In this case, we can                         \
		 * skip painting the FG/BG pixels entirely, and only paint the other one                         \
		 * respectively.                                                                                 \
		 *                                                                                               \
		 * This is probably actually the most likely case, since this is what                            \
		 * happens when the  user does alpha-blending,  and sets ALPHA=0  for                            \
		 * background, and ALPHA=255 for foreground. */                                                  \
		if (preblend##_maynblend(self->vx_blend, preblend_bg_fg_colors[0])) {                            \
			if (preblend##_maynblend(self->vx_blend, preblend_bg_fg_colors[1])) {                        \
				libvideo_swgfx_noblend__fillmask(self, dst_x, dst_y, size_x, size_y,                     \
				                                 preblend_bg_fg_colors, bm);                             \
				return;                                                                                  \
			}                                                                                            \
			if (preblend##_mayignore(self->vx_blend, preblend_bg_fg_colors[1])) {                        \
				libvideo_swgfx_noblend__fillmask1(self, dst_x, dst_y, size_x, size_y,                    \
				                                  preblend_bg_fg_colors[0], bm,                          \
				                                  (__REGISTER_TYPE__)(-1));                              \
				return;                                                                                  \
			}                                                                                            \
		} else if (preblend##_maynblend(self->vx_blend, preblend_bg_fg_colors[1])) {                     \
			if (preblend##_mayignore(self->vx_blend, preblend_bg_fg_colors[0])) {                        \
				libvideo_swgfx_noblend__fillmask1(self, dst_x, dst_y, size_x, size_y,                    \
				                                  preblend_bg_fg_colors[1], bm, 0);                      \
				return;                                                                                  \
			}                                                                                            \
		} else if (preblend##_mayignore(self->vx_blend, preblend_bg_fg_colors[0])) {                     \
			libvideo_swgfx_generic__fillmask1(self, dst_x, dst_y, size_x, size_y,                        \
			                                  preblend_bg_fg_colors[0], bm, 0);                          \
			return;                                                                                      \
		} else if (preblend##_mayignore(self->vx_blend, preblend_bg_fg_colors[1])) {                     \
			libvideo_swgfx_generic__fillmask1(self, dst_x, dst_y, size_x, size_y,                        \
			                                  preblend_bg_fg_colors[1], bm, (__REGISTER_TYPE__)(-1));    \
			return;                                                                                      \
		}                                                                                                \
		libvideo_swgfx_generic__fillmask(self, dst_x, dst_y, size_x, size_y, preblend_bg_fg_colors, bm); \
	}                                                                                                    \
	INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC                                                      \
	libvideo_swgfx_preblend__fillstretchmask_l__##name(struct video_gfx const *__restrict self,          \
	                                                   video_coord_t dst_x, video_coord_t dst_y,         \
	                                                   video_dim_t dst_size_x, video_dim_t dst_size_y,   \
	                                                   video_color_t const bg_fg_colors[2],              \
	                                                   video_dim_t src_size_x, video_dim_t src_size_y,   \
	                                                   struct video_bitmask const *__restrict bm) {      \
		video_color_t preblend_bg_fg_colors[2];                                                          \
		preblend_bg_fg_colors[0] = preblend(self->vx_blend, bg_fg_colors[0]);                            \
		preblend_bg_fg_colors[1] = preblend(self->vx_blend, bg_fg_colors[1]);                            \
		/* Optimization for  likely case:  one color  is the  alpha-less                                 \
		 * equivalent of the other, and can be ignored under the current                                 \
		 * blend mode.                                                                                   \
		 *                                                                                               \
		 * iow: you're doing alpha-blending, and use "transparent" as BG */                              \
		if (preblend##_mayignore(self->vx_blend, preblend_bg_fg_colors[0])) {                            \
			if (preblend##_mayignore(self->vx_blend, preblend_bg_fg_colors[1]))                          \
				return;                                                                                  \
			if (preblend_bg_fg_colors[0] == (preblend_bg_fg_colors[1] & ~VIDEO_COLOR_ALPHA_MASK)) {      \
				libvideo_swgfx_generic__fillstretchmask_l__alpha_only(self, dst_x, dst_y, dst_size_x,    \
				                                                      dst_size_y,                        \
				                                                      preblend_bg_fg_colors[1],          \
				                                                      src_size_x, src_size_y,            \
				                                                      bm, 0);                            \
				return;                                                                                  \
			}                                                                                            \
		} else if (preblend##_mayignore(self->vx_blend, preblend_bg_fg_colors[1])) {                     \
			if (preblend_bg_fg_colors[1] == (preblend_bg_fg_colors[0] & ~VIDEO_COLOR_ALPHA_MASK)) {      \
				libvideo_swgfx_generic__fillstretchmask_l__alpha_only(self, dst_x, dst_y, dst_size_x,    \
				                                                      dst_size_y,                        \
				                                                      preblend_bg_fg_colors[0],          \
				                                                      src_size_x, src_size_y,            \
				                                                      bm, (__REGISTER_TYPE__)(-1));      \
				return;                                                                                  \
			}                                                                                            \
		}                                                                                                \
		libvideo_swgfx_generic__fillstretchmask_l(self, dst_x, dst_y, dst_size_x, dst_size_y,            \
		                                          preblend_bg_fg_colors, src_size_x, src_size_y, bm);    \
	}                                                                                                    \
	INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC                                                      \
	libvideo_swgfx_preblend__fillstretchmask_n__##name(struct video_gfx const *__restrict self,          \
	                                                   video_coord_t dst_x, video_coord_t dst_y,         \
	                                                   video_dim_t dst_size_x, video_dim_t dst_size_y,   \
	                                                   video_color_t const bg_fg_colors[2],              \
	                                                   video_dim_t src_size_x, video_dim_t src_size_y,   \
	                                                   struct video_bitmask const *__restrict bm) {      \
		video_color_t preblend_bg_fg_colors[2];                                                          \
		preblend_bg_fg_colors[0] = preblend(self->vx_blend, bg_fg_colors[0]);                            \
		preblend_bg_fg_colors[1] = preblend(self->vx_blend, bg_fg_colors[1]);                            \
		if (preblend##_mayignore(self->vx_blend, preblend_bg_fg_colors[0])) {                            \
			if (preblend##_mayignore(self->vx_blend, preblend_bg_fg_colors[1]))                          \
				return;                                                                                  \
			if (preblend##_maynblend(self->vx_blend, preblend_bg_fg_colors[1])) {                        \
				libvideo_swgfx_noblend__fillstretchmask1_n(self, dst_x, dst_y, dst_size_x, dst_size_y,   \
				                                           preblend_bg_fg_colors[1], src_size_x,         \
				                                           src_size_y, bm, 0);                           \
			} else {                                                                                     \
				libvideo_swgfx_generic__fillstretchmask1_n(self, dst_x, dst_y, dst_size_x, dst_size_y,   \
				                                           preblend_bg_fg_colors[1], src_size_x,         \
				                                           src_size_y, bm, 0);                           \
			}                                                                                            \
		} else if (preblend##_mayignore(self->vx_blend, preblend_bg_fg_colors[1])) {                     \
			if (preblend##_maynblend(self->vx_blend, preblend_bg_fg_colors[0])) {                        \
				libvideo_swgfx_noblend__fillstretchmask1_n(self, dst_x, dst_y, dst_size_x, dst_size_y,   \
				                                           preblend_bg_fg_colors[0], src_size_x,         \
				                                           src_size_y, bm, (__REGISTER_TYPE__)(-1));     \
			} else {                                                                                     \
				libvideo_swgfx_generic__fillstretchmask1_n(self, dst_x, dst_y, dst_size_x, dst_size_y,   \
				                                           preblend_bg_fg_colors[0], src_size_x,         \
				                                           src_size_y, bm, (__REGISTER_TYPE__)(-1));     \
			}                                                                                            \
		} else if (preblend##_maynblend(self->vx_blend, preblend_bg_fg_colors[0]) &&                     \
		           preblend##_maynblend(self->vx_blend, preblend_bg_fg_colors[1])) {                     \
			libvideo_swgfx_noblend__fillstretchmask_n(self, dst_x, dst_y, dst_size_x, dst_size_y,        \
			                                          preblend_bg_fg_colors, src_size_x, src_size_y,     \
			                                          bm);                                               \
		} else {                                                                                         \
			libvideo_swgfx_generic__fillstretchmask_n(self, dst_x, dst_y, dst_size_x, dst_size_y,        \
			                                          preblend_bg_fg_colors, src_size_x, src_size_y,     \
			                                          bm);                                               \
		}                                                                                                \
	}
#ifndef __INTELLISENSE__
GFX_FOREACH_DEDICATED_PREBLENDMODE(DEFINE_libvideo_swgfx_generic__render_preblend_FOO)
#endif /* !__INTELLISENSE__ */
#undef DEFINE_libvideo_swgfx_generic__render_preblend_FOO

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_LL_GENERIC_C_INL */
