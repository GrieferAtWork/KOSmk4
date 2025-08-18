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
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#include <libvideo/color.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/blendcolors.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/surface.h>
#include <libvideo/types.h>

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
libvideo_swgfx_generic__getcolor(struct video_gfx const *__restrict self,
                                 video_coord_t x, video_coord_t y) {
	video_pixel_t pixel = LL_getpixel(self, x, y);
	struct video_surface const *surface = video_gfx_assurface(self);
	return video_surface_pixel2color(surface, pixel);
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__putcolor(struct video_gfx const *__restrict self,
                                 video_coord_t x, video_coord_t y,
                                 video_color_t color) {
	struct video_surface const *surface = video_gfx_assurface(self);
	video_pixel_t op = LL_getpixel(self, x, y);
	video_color_t oc = video_surface_pixel2color(surface, op);
	video_color_t nc = gfx_blendcolors(oc, color, self->vg_blend);
	video_pixel_t np = video_surface_color2pixel(surface, nc);
	LL_setpixel(self, x, y, np);
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__putcolor_noblend(struct video_gfx const *__restrict self,
                                         video_coord_t x, video_coord_t y,
                                         video_color_t color) {
	struct video_surface const *surface = video_gfx_assurface(self);
	video_pixel_t np = video_surface_color2pixel(surface, color);
	LL_setpixel(self, x, y, np);
}

#define DEFINE_libvideo_swgfx_generic__putcolor_FOO(name, mode)                      \
	INTERN ATTR_IN(1) void CC                                                        \
	libvideo_swgfx_generic__putcolor_##name(struct video_gfx const *__restrict self, \
	                                        video_coord_t x, video_coord_t y,        \
	                                        video_color_t color) {                   \
		struct video_surface const *surface = video_gfx_assurface(self);            \
		video_pixel_t op = LL_getpixel(self, x, y);                                  \
		video_color_t oc = video_surface_pixel2color(surface, op);                   \
		video_color_t nc = gfx_blendcolors(oc, color, mode);                         \
		video_pixel_t np = video_surface_color2pixel(surface, nc);                   \
		LL_setpixel(self, x, y, np);                                                 \
	}
GFX_FOREACH_DEDICATED_BLENDMODE(DEFINE_libvideo_swgfx_generic__putcolor_FOO)
#undef DEFINE_libvideo_swgfx_generic__putcolor_FOO


#define DEFINE_libvideo_swgfx_generic__putcolor_FOO(name, mode)                      \
	INTERN ATTR_IN(1) void CC                                                        \
	libvideo_swgfx_generic__putcolor_##name(struct video_gfx const *__restrict self, \
	                                        video_coord_t x, video_coord_t y,        \
	                                        video_color_t color) {                   \
		struct video_surface const *surface = video_gfx_assurface(self);            \
		video_pixel_t op = LL_getpixel(self, x, y);                                  \
		video_color_t oc = video_surface_pixel2color(surface, op);                   \
		video_color_t cc = GFX_BLENDMODE_GET_COLOR(self->vg_blend);                  \
		video_color_t nc = gfx_blendcolors_constant(oc, color, mode, cc);            \
		video_pixel_t np = video_surface_color2pixel(surface, nc);                   \
		LL_setpixel(self, x, y, np);                                                 \
	}
GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(DEFINE_libvideo_swgfx_generic__putcolor_FOO)
#undef DEFINE_libvideo_swgfx_generic__putcolor_FOO





/* Generic, always-valid GFX functions (using only `vx_pxops') */
INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__line_llhh(struct video_gfx const *__restrict self,
                                  video_coord_t dst_x, video_coord_t dst_y,
                                  video_dim_t size_x, video_dim_t size_y,
                                  video_color_t color) {
	video_dim_t step;
	TRACE_START("swgfx_generic__line_llhh("
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
			libvideo_swgfx_generic__line_h(self, dst_x + line_lox, dst_y + step, line_hix - line_lox, color);
			line_lox = line_hix;
		} while (++step < size_y);
	} else if (size_x < size_y) {
		video_coord_t line_loy = 0;
		do {
			video_coord_t line_hiy = (video_dim_t)(((uint64_t)size_y * (step + 1)) / size_x);
			libvideo_swgfx_generic__line_v(self, dst_x + step, dst_y + line_loy, line_hiy - line_loy, color);
			line_loy = line_hiy;
		} while (++step < size_x);
	} else {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y + step;
			LL_putcolor_p(self, line_x, line_y, color);
		} while (++step < size_x);
	}
	TRACE_END("swgfx_generic__line_llhh()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__line_lhhl(struct video_gfx const *__restrict self,
                                  video_coord_t dst_x, video_coord_t dst_y,
                                  video_dim_t size_x, video_dim_t size_y,
                                  video_color_t color) {
	video_dim_t step;
	TRACE_START("swgfx_generic__line_lhhl("
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
			libvideo_swgfx_generic__line_h(self, dst_x + line_lox, dst_y - step, line_hix - line_lox, color);
			line_lox = line_hix;
		} while (++step < size_y);
	} else if (size_x < size_y) {
		video_coord_t line_loy = 0;
		do {
			video_coord_t line_hiy = (video_dim_t)(((uint64_t)size_y * (step + 1)) / size_x);
			libvideo_swgfx_generic__line_v(self, dst_x + step, dst_y - line_hiy + 1, line_hiy - line_loy, color);
			line_loy = line_hiy;
		} while (++step < size_x);
	} else {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y - step;
			LL_putcolor_p(self, line_x, line_y, color);
		} while (++step < size_x);
	}
	TRACE_END("swgfx_generic__line_lhhl()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__line_llhh_l(struct video_gfx const *__restrict self,
                                    video_coord_t dst_x, video_coord_t dst_y,
                                    video_dim_t size_x, video_dim_t size_y,
                                    video_color_t color) {
	TRACE_START("swgfx_generic__line_llhh_l("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ")\n",
	            dst_x, dst_y, size_x, size_y, color);
	if (size_x > size_y) {
		video_foffset_t fp_start;
		video_fcoord_t fp_step;
		video_dim_t pad_min;
		video_dim_t pad_max;
		calc_linear_stretch_dim(size_y, size_x, &fp_start,
		                        &fp_step, &pad_min, &pad_max);
		if (pad_min) {
			libvideo_swgfx_generic__line_h(self, dst_x, dst_y, pad_min, color);
			dst_x += pad_min;
			fp_start += pad_min * fp_step;
			size_x -= pad_min;
		}
		for (size_x -= pad_max; size_x; --size_x, ++dst_x, fp_start += fp_step) {
			linear_fp_blend_t frac_y0 = STRETCH_FP_BLEND_FRAC(fp_start);
			linear_fp_blend_t frac_y1 = LINEAR_FP_BLEND(1) - frac_y0;
			video_coord_t dst_y0 = dst_y + VIDEO_FCOORD_WHOLE(fp_start);
			video_coord_t dst_y1 = dst_y0 + 1;
			video_color_t cy0 = LL_getcolor(self, dst_x, dst_y0);
			video_color_t cy1 = LL_getcolor(self, dst_x, dst_y1);
			cy0 = interpolate_1d(color, cy0, frac_y0, frac_y1);
			cy1 = interpolate_1d(cy1, color, frac_y0, frac_y1);
			LL_putcolor_p(self, dst_x, dst_y0, cy0);
			LL_putcolor_p(self, dst_x, dst_y1, cy1);
		}
		if (pad_max)
			libvideo_swgfx_generic__line_h(self, dst_x, dst_y + (size_y - 1), pad_max, color);
	} else if (size_x < size_y) {
		video_foffset_t fp_start;
		video_fcoord_t fp_step;
		video_dim_t pad_min;
		video_dim_t pad_max;
		calc_linear_stretch_dim(size_x, size_y, &fp_start,
		                        &fp_step, &pad_min, &pad_max);
		if (pad_min) {
			libvideo_swgfx_generic__line_v(self, dst_x, dst_y, pad_min, color);
			dst_y += pad_min;
			fp_start += pad_min * fp_step;
			size_y -= pad_min;
		}
		for (size_y -= pad_max; size_y; --size_y, ++dst_y, fp_start += fp_step) {
			linear_fp_blend_t frac_x0 = STRETCH_FP_BLEND_FRAC(fp_start);
			linear_fp_blend_t frac_x1 = LINEAR_FP_BLEND(1) - frac_x0;
			video_coord_t dst_x0 = dst_x + VIDEO_FCOORD_WHOLE(fp_start);
			video_coord_t dst_x1 = dst_x0 + 1;
			video_color_t cx0 = LL_getcolor(self, dst_x0, dst_y);
			video_color_t cx1 = LL_getcolor(self, dst_x1, dst_y);
			cx0 = interpolate_1d(color, cx0, frac_x0, frac_x1);
			cx1 = interpolate_1d(cx1, color, frac_x0, frac_x1);
			LL_putcolor_p(self, dst_x0, dst_y, cx0);
			LL_putcolor_p(self, dst_x1, dst_y, cx1);
		}
		if (pad_max)
			libvideo_swgfx_generic__line_v(self, dst_x + (size_x - 1), dst_y, pad_max, color);
	} else {
		do {
			LL_putcolor_p(self, dst_x, dst_y, color);
			++dst_x;
			++dst_y;
		} while (--size_x);
	}
	TRACE_END("swgfx_generic__line_llhh_l()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__line_lhhl_l(struct video_gfx const *__restrict self,
                                    video_coord_t dst_x, video_coord_t dst_y,
                                    video_dim_t size_x, video_dim_t size_y,
                                    video_color_t color) {
	TRACE_START("swgfx_generic__line_lhhl_l("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ")\n",
	            dst_x, dst_y, size_x, size_y, color);
	if (size_x > size_y) {
		video_foffset_t fp_start;
		video_fcoord_t fp_step;
		video_dim_t pad_min;
		video_dim_t pad_max;
		calc_linear_stretch_dim(size_y, size_x, &fp_start,
		                        &fp_step, &pad_min, &pad_max);
		if (pad_min) {
			libvideo_swgfx_generic__line_h(self, dst_x, dst_y, pad_min, color);
			dst_x += pad_min;
			fp_start += pad_min * fp_step;
			size_x -= pad_min;
		}
		for (size_x -= pad_max; size_x; --size_x, ++dst_x, fp_start += fp_step) {
			linear_fp_blend_t frac_y0 = STRETCH_FP_BLEND_FRAC(fp_start);
			linear_fp_blend_t frac_y1 = LINEAR_FP_BLEND(1) - frac_y0;
			video_coord_t dst_y0 = dst_y - VIDEO_FCOORD_WHOLE(fp_start);
			video_coord_t dst_y1 = dst_y0 - 1;
			video_color_t cy0 = LL_getcolor(self, dst_x, dst_y0);
			video_color_t cy1 = LL_getcolor(self, dst_x, dst_y1);
			cy0 = interpolate_1d(color, cy0, frac_y0, frac_y1);
			cy1 = interpolate_1d(cy1, color, frac_y0, frac_y1);
			LL_putcolor_p(self, dst_x, dst_y0, cy0);
			LL_putcolor_p(self, dst_x, dst_y1, cy1);
		}
		if (pad_max)
			libvideo_swgfx_generic__line_h(self, dst_x, dst_y - (size_y - 1), pad_max, color);
	} else if (size_x < size_y) {
		video_foffset_t fp_start;
		video_fcoord_t fp_step;
		video_dim_t pad_min;
		video_dim_t pad_max;
		calc_linear_stretch_dim(size_x, size_y, &fp_start,
		                        &fp_step, &pad_min, &pad_max);
		if (pad_min) {
			dst_y -= pad_min;
			libvideo_swgfx_generic__line_v(self, dst_x, dst_y + 1, pad_min, color);
			fp_start += pad_min * fp_step;
			size_y -= pad_min;
		}
		for (size_y -= pad_max; size_y; --size_y, --dst_y, fp_start += fp_step) {
			linear_fp_blend_t frac_x0 = STRETCH_FP_BLEND_FRAC(fp_start);
			linear_fp_blend_t frac_x1 = LINEAR_FP_BLEND(1) - frac_x0;
			video_coord_t dst_x0 = dst_x + VIDEO_FCOORD_WHOLE(fp_start);
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
			libvideo_swgfx_generic__line_v(self, dst_x + (size_x - 1), dst_y, pad_max, color);
		}
	} else {
		do {
			LL_putcolor_p(self, dst_x, dst_y, color);
			++dst_x;
			--dst_y;
		} while (--size_x);
	}
	TRACE_END("swgfx_generic__line_lhhl_l()\n");
}



INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__line_h(struct video_gfx const *__restrict self,
                               video_coord_t dst_x, video_coord_t dst_y,
                               video_dim_t length, video_color_t color) {
	do {
		LL_putcolor_p(self, dst_x, dst_y, color);
		++dst_x;
	} while (--length);
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__line_v(struct video_gfx const *__restrict self,
                               video_coord_t dst_x, video_coord_t dst_y,
                               video_dim_t length, video_color_t color) {
	do {
		LL_putcolor_p(self, dst_x, dst_y, color);
		++dst_y;
	} while (--length);
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__fill(struct video_gfx const *__restrict self,
                             video_coord_t dst_x, video_coord_t dst_y,
                             video_dim_t size_x, video_dim_t size_y,
                             video_color_t color) {
	do {
		LL_line_h(self, dst_x, dst_y, size_x, color);
		++dst_y;
	} while (--size_y);
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
libvideo_swgfx_generic__gradient(struct video_gfx const *__restrict self,
                                 video_coord_t dst_x_, video_coord_t dst_y_,
                                 video_dim_t size_x_, video_dim_t size_y_,
                                 video_color_t const colors[2][2]) {
	/* Check for special case: not actually a 4-color gradient */
	if (colors[0][0] == colors[0][1] && colors[1][0] == colors[1][1]) {
		libvideo_swgfx_generic__gradient_v(self, dst_x_, dst_y_, size_x_, size_y_,
		                                      colors[0][0], colors[1][0]);
		return;
	} else if (colors[0][0] == colors[1][0] && colors[0][1] == colors[1][1]) {
		libvideo_swgfx_generic__gradient_h(self, dst_x_, dst_y_, size_x_, size_y_,
		                                      colors[0][0], colors[0][1]);
		return;
	}

#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)      \
	{                                                                                  \
		video_color_t out = colors[src_y][src_x];                                      \
		libvideo_swgfx_generic__fill(self, dst_x, dst_y, dst_size_x, dst_size_y, out); \
	}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                       \
		video_color_t src_y0_x0 = colors[src_y][src_x0];                                    \
		video_color_t src_y0_x1 = colors[src_y][src_x1];                                    \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);   \
		libvideo_swgfx_generic__line_v(self, dst_x, dst_y, dst_size_y, out);                \
	}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                       \
		video_color_t src_y0_x0 = colors[src_y0][src_x];                                    \
		video_color_t src_y1_x0 = colors[src_y1][src_x];                                    \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);   \
		libvideo_swgfx_generic__line_h(self, dst_x, dst_y, dst_size_x, out);                \
	}

#define pixel_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                 \
		video_color_t src_y0_x0 = colors[src_y0][src_x0];                                             \
		video_color_t src_y0_x1 = colors[src_y0][src_x1];                                             \
		video_color_t src_y1_x0 = colors[src_y1][src_x0];                                             \
		video_color_t src_y1_x1 = colors[src_y1][src_x1];                                             \
		video_color_t out       = interpolate_2d(src_y0_x0, src_y0_x1,                                \
		                                         src_y1_x0, src_y1_x1,                                \
		                                         frac_x0, frac_x1,                                    \
		                                         frac_y0, frac_y1);                                   \
		LL_putcolor_p(self, dst_x, dst_y, out);                                                       \
	}

	TRACE_START("swgfx_generic__gradient("
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
	TRACE_END("swgfx_generic__gradient()\n");
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
libvideo_swgfx_generic__gradient_h(struct video_gfx const *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_dim_t size_x, video_dim_t size_y,
                                   video_color_t locolor, video_color_t hicolor) {
	video_dim_t pad_xmin, pad_xmax;
	video_foffset_t fp_src_x;
	video_fcoord_t fp_step_x;

	/* Check for special case: not actually a gradient */
	if (locolor == hicolor) {
		libvideo_swgfx_generic__fill(self, dst_x, dst_y, size_x, size_y, locolor);
		return;
	}

	TRACE_START("swgfx_generic__gradient_h("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {%#" PRIxCOL ", %#" PRIxCOL "})\n",
	            dst_x, dst_y, size_x, size_y,
	            locolor, hicolor);
	calc_linear_stretch_dim(2, size_x, &fp_src_x, &fp_step_x, &pad_xmin, &pad_xmax);
	if (pad_xmin) {
		libvideo_swgfx_generic__fill(self, dst_x, dst_y, pad_xmin, size_y, locolor);
		dst_x += pad_xmin;
		size_x -= pad_xmin;
		fp_src_x += pad_xmin * fp_step_x;
	}
	if (pad_xmax) {
		size_x -= pad_xmax;
		libvideo_swgfx_generic__fill(self, dst_x + size_x, dst_y, pad_xmax, size_y, hicolor);
	}
	for (; size_x; --size_x, ++dst_x, fp_src_x += fp_step_x) {
		linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_x);
		linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
		video_color_t color = interpolate_1d(locolor, hicolor, frac0, frac1);
		libvideo_swgfx_generic__line_v(self, dst_x, dst_y, size_y, color);
	}
	TRACE_END("swgfx_generic__gradient_h()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swgfx_generic__gradient_v(struct video_gfx const *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_dim_t size_x, video_dim_t size_y,
                                   video_color_t locolor, video_color_t hicolor) {
	video_dim_t pad_ymin, pad_ymax;
	video_foffset_t fp_src_y;
	video_fcoord_t fp_step_y;

	/* Check for special case: not actually a gradient */
	if (locolor == hicolor) {
		libvideo_swgfx_generic__fill(self, dst_x, dst_y, size_x, size_y, locolor);
		return;
	}

	TRACE_START("swgfx_generic__gradient_v("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {%#" PRIxCOL ", %#" PRIxCOL "})\n",
	            dst_x, dst_y, size_x, size_y,
	            locolor, hicolor);
	calc_linear_stretch_dim(2, size_y, &fp_src_y, &fp_step_y, &pad_ymin, &pad_ymax);
	if (pad_ymin) {
		libvideo_swgfx_generic__fill(self, dst_x, dst_y, size_x, pad_ymin, locolor);
		dst_y += pad_ymin;
		size_y -= pad_ymin;
		fp_src_y += pad_ymin * fp_step_y;
	}
	if (pad_ymax) {
		size_y -= pad_ymax;
		libvideo_swgfx_generic__fill(self, dst_x, dst_y + size_y, size_x, pad_ymax, hicolor);
	}
	for (; size_y; --size_y, ++dst_y, fp_src_y += fp_step_y) {
		linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_y);
		linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
		video_color_t color = interpolate_1d(locolor, hicolor, frac0, frac1);
		libvideo_swgfx_generic__line_h(self, dst_x, dst_y, size_x, color);
	}
	TRACE_END("swgfx_generic__gradient_v()\n");
}



/* Custom pre-blending GFX functions */
#define DEFINE_libvideo_swgfx_generic__render_preblend_FOO(name, mode, preblend_name, preblend)   \
	INTERN ATTR_IN(1) void CC                                                                     \
	libvideo_swgfx_preblend__line_llhh__##name(struct video_gfx const *__restrict self,           \
	                                           video_coord_t dst_x, video_coord_t dst_y,          \
	                                           video_dim_t size_x, video_dim_t size_y,            \
	                                           video_color_t color) {                             \
		color = preblend(self->vg_blend, color);                                                  \
		if (preblend##_mayignore(self->vg_blend, color))                                          \
			return;                                                                               \
		if (preblend##_maynblend(self->vg_blend, color)) {                                        \
			libvideo_swgfx_noblend__line_llhh(self, dst_x, dst_y, size_x, size_y, color);         \
		} else {                                                                                  \
			libvideo_swgfx_generic__line_llhh(self, dst_x, dst_y, size_x, size_y, color);         \
		}                                                                                         \
	}                                                                                             \
	INTERN ATTR_IN(1) void CC                                                                     \
	libvideo_swgfx_preblend__line_lhhl__##name(struct video_gfx const *__restrict self,           \
	                                           video_coord_t dst_x, video_coord_t dst_y,          \
	                                           video_dim_t size_x, video_dim_t size_y,            \
	                                           video_color_t color) {                             \
		color = preblend(self->vg_blend, color);                                                  \
		if (preblend##_mayignore(self->vg_blend, color))                                          \
			return;                                                                               \
		if (preblend##_maynblend(self->vg_blend, color)) {                                        \
			libvideo_swgfx_noblend__line_lhhl(self, dst_x, dst_y, size_x, size_y, color);         \
		} else {                                                                                  \
			libvideo_swgfx_generic__line_lhhl(self, dst_x, dst_y, size_x, size_y, color);         \
		}                                                                                         \
	}                                                                                             \
	INTERN ATTR_IN(1) void CC                                                                     \
	libvideo_swgfx_preblend__line_llhh_l__##name(struct video_gfx const *__restrict self,         \
	                                             video_coord_t dst_x, video_coord_t dst_y,        \
	                                             video_dim_t size_x, video_dim_t size_y,          \
	                                             video_color_t color) {                           \
		color = preblend(self->vg_blend, color);                                                  \
		if (preblend##_mayignore(self->vg_blend, color))                                          \
			return;                                                                               \
		libvideo_swgfx_generic__line_llhh_l(self, dst_x, dst_y, size_x, size_y, color);           \
	}                                                                                             \
	INTERN ATTR_IN(1) void CC                                                                     \
	libvideo_swgfx_preblend__line_lhhl_l__##name(struct video_gfx const *__restrict self,         \
	                                             video_coord_t dst_x, video_coord_t dst_y,        \
	                                             video_dim_t size_x, video_dim_t size_y,          \
	                                             video_color_t color) {                           \
		color = preblend(self->vg_blend, color);                                                  \
		if (preblend##_mayignore(self->vg_blend, color))                                          \
			return;                                                                               \
		libvideo_swgfx_generic__line_lhhl_l(self, dst_x, dst_y, size_x, size_y, color);           \
	}                                                                                             \
	INTERN ATTR_IN(1) void CC                                                                     \
	libvideo_swgfx_preblend__line_h__##name(struct video_gfx const *__restrict self,              \
	                                        video_coord_t dst_x, video_coord_t dst_y,             \
	                                        video_dim_t length, video_color_t color) {            \
		color = preblend(self->vg_blend, color);                                                  \
		if (preblend##_mayignore(self->vg_blend, color))                                          \
			return;                                                                               \
		if (preblend##_maynblend(self->vg_blend, color)) {                                        \
			libvideo_swgfx_noblend__line_h(self, dst_x, dst_y, length, color);                    \
		} else {                                                                                  \
			libvideo_swgfx_generic__line_h(self, dst_x, dst_y, length, color);                    \
		}                                                                                         \
	}                                                                                             \
	INTERN ATTR_IN(1) void CC                                                                     \
	libvideo_swgfx_preblend__line_v__##name(struct video_gfx const *__restrict self,              \
	                                        video_coord_t dst_x, video_coord_t dst_y,             \
	                                        video_dim_t length, video_color_t color) {            \
		color = preblend(self->vg_blend, color);                                                  \
		if (preblend##_mayignore(self->vg_blend, color))                                          \
			return;                                                                               \
		if (preblend##_maynblend(self->vg_blend, color)) {                                        \
			libvideo_swgfx_noblend__line_v(self, dst_x, dst_y, length, color);                    \
		} else {                                                                                  \
			libvideo_swgfx_generic__line_v(self, dst_x, dst_y, length, color);                    \
		}                                                                                         \
	}                                                                                             \
	INTERN ATTR_IN(1) void CC                                                                     \
	libvideo_swgfx_preblend__fill__##name(struct video_gfx const *__restrict self,                \
	                                      video_coord_t dst_x, video_coord_t dst_y,               \
	                                      video_dim_t size_x, video_dim_t size_y,                 \
	                                      video_color_t color) {                                  \
		color = preblend(self->vg_blend, color);                                                  \
		if (preblend##_mayignore(self->vg_blend, color))                                          \
			return;                                                                               \
		if (preblend##_maynblend(self->vg_blend, color)) {                                        \
			libvideo_swgfx_noblend__fill(self, dst_x, dst_y, size_x, size_y, color);              \
		} else {                                                                                  \
			libvideo_swgfx_generic__fill(self, dst_x, dst_y, size_x, size_y, color);              \
		}                                                                                         \
	}                                                                                             \
	INTERN ATTR_IN(1) ATTR_IN(6) void CC                                                          \
	libvideo_swgfx_preblend__gradient__##name(struct video_gfx const *__restrict self,            \
	                                          video_coord_t dst_x, video_coord_t dst_y,           \
	                                          video_dim_t size_x, video_dim_t size_y,             \
	                                          video_color_t const colors[2][2]) {                 \
		video_color_t preblend_colors[2][2];                                                      \
		preblend_colors[0][0] = preblend(self->vg_blend, colors[0][0]);                           \
		preblend_colors[0][1] = preblend(self->vg_blend, colors[0][1]);                           \
		preblend_colors[1][0] = preblend(self->vg_blend, colors[1][0]);                           \
		preblend_colors[1][1] = preblend(self->vg_blend, colors[1][1]);                           \
		if (preblend##_mayignore(self->vg_blend, preblend_colors[0][0]) &&                        \
		    preblend##_mayignore(self->vg_blend, preblend_colors[0][1]) &&                        \
		    preblend##_mayignore(self->vg_blend, preblend_colors[1][0]) &&                        \
		    preblend##_mayignore(self->vg_blend, preblend_colors[1][1]))                          \
			return;                                                                               \
		if ((video_gfx_getcodec(self)->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) &&       \
		    preblend##_maynblend(self->vg_blend, preblend_colors[0][0]) &&                        \
		    preblend##_maynblend(self->vg_blend, preblend_colors[0][1]) &&                        \
		    preblend##_maynblend(self->vg_blend, preblend_colors[1][0]) &&                        \
		    preblend##_maynblend(self->vg_blend, preblend_colors[1][1])) {                        \
			libvideo_swgfx_noblend_interp8888__gradient(self, dst_x, dst_y,                       \
			                                            size_x, size_y, preblend_colors);         \
			return;                                                                               \
		}                                                                                         \
		libvideo_swgfx_generic__gradient(self, dst_x, dst_y, size_x, size_y, preblend_colors);    \
	}                                                                                             \
	INTERN ATTR_IN(1) void CC                                                                     \
	libvideo_swgfx_preblend__gradient_h__##name(struct video_gfx const *__restrict self,          \
	                                            video_coord_t dst_x, video_coord_t dst_y,         \
	                                            video_dim_t size_x, video_dim_t size_y,           \
	                                            video_color_t locolor, video_color_t hicolor) {   \
		locolor = preblend(self->vg_blend, locolor);                                              \
		hicolor = preblend(self->vg_blend, hicolor);                                              \
		if (preblend##_mayignore(self->vg_blend, locolor) &&                                      \
		    preblend##_mayignore(self->vg_blend, hicolor))                                        \
			return;                                                                               \
		if ((video_gfx_getcodec(self)->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) &&       \
		    preblend##_maynblend(self->vg_blend, locolor) &&                                      \
		    preblend##_maynblend(self->vg_blend, hicolor)) {                                      \
			libvideo_swgfx_noblend_interp8888__gradient_h(self, dst_x, dst_y, size_x, size_y,     \
			                                              locolor, hicolor);                      \
			return;                                                                               \
		}                                                                                         \
		libvideo_swgfx_generic__gradient_h(self, dst_x, dst_y, size_x, size_y, locolor, hicolor); \
	}                                                                                             \
	INTERN ATTR_IN(1) void CC                                                                     \
	libvideo_swgfx_preblend__gradient_v__##name(struct video_gfx const *__restrict self,          \
	                                            video_coord_t dst_x, video_coord_t dst_y,         \
	                                            video_dim_t size_x, video_dim_t size_y,           \
	                                            video_color_t locolor, video_color_t hicolor) {   \
		locolor = preblend(self->vg_blend, locolor);                                              \
		hicolor = preblend(self->vg_blend, hicolor);                                              \
		if (preblend##_mayignore(self->vg_blend, locolor) &&                                      \
		    preblend##_mayignore(self->vg_blend, hicolor))                                        \
			return;                                                                               \
		if ((video_gfx_getcodec(self)->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) &&       \
		    preblend##_maynblend(self->vg_blend, locolor) &&                                      \
		    preblend##_maynblend(self->vg_blend, hicolor)) {                                      \
			libvideo_swgfx_noblend_interp8888__gradient_v(self, dst_x, dst_y, size_x, size_y,     \
			                                              locolor, hicolor);                      \
			return;                                                                               \
		}                                                                                         \
		libvideo_swgfx_generic__gradient_v(self, dst_x, dst_y, size_x, size_y, locolor, hicolor); \
	}
#ifndef __INTELLISENSE__
GFX_FOREACH_DEDICATED_PREBLENDMODE(DEFINE_libvideo_swgfx_generic__render_preblend_FOO)
#endif /* !__INTELLISENSE__ */
#undef DEFINE_libvideo_swgfx_generic__render_preblend_FOO

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_LL_GENERIC_C_INL */
