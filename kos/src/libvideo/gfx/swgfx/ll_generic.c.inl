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

#include <alloca.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

#include <libvideo/color.h>
#include <libvideo/float.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/blendcolors.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/gfx/swgfx.h>
#include <libvideo/gfx/polygon.h>
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
		struct video_surface const *surface = video_gfx_assurface(self);             \
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
		struct video_surface const *surface = video_gfx_assurface(self);             \
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


INTERN ATTR_IN(1) NONNULL((4)) void CC
libvideo_swgfx_generic__fillpoly(struct video_gfx const *__restrict self,
                                 video_offset_t xoff, video_offset_t yoff,
                                 struct video_polygon_data const *__restrict poly,
                                 video_color_t color, video_imatrix2d_t matrix,
                                 unsigned int method) {
	size_t active_c, active_i;
	struct video_polygon_edgeref *active_v;
	video_offset_t scanline_y, scanline_yend;
	size_t next_edge_to_activate;
	void (LIBVIDEO_GFX_CC *xsws_line)(struct video_gfx const *__restrict self,
	                                  video_coord_t x, video_coord_t y,
	                                  video_dim_t length, video_color_t color);
	TRACE_START("swgfx_generic__fillpoly("
	            "off: {%" PRIdOFF "x%" PRIdOFF "}, "
	            "poly: {%" PRIdOFF "x%" PRIdOFF ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", "
	            "matrix: {{%d,%d},{%d,%d}})\n",
	            xoff, yoff,
	            poly->vpd_xmin, poly->vpd_ymin,
	            poly->vpd_xdim, poly->vpd_ydim,
	            color,
	            (int)video_imatrix2d_get(&matrix, 0, 0), (int)video_imatrix2d_get(&matrix, 0, 1),
	            (int)video_imatrix2d_get(&matrix, 1, 0), (int)video_imatrix2d_get(&matrix, 1, 1));

	/* Our polygon render algorithm here is based on "Efficient Polygon Fill Algorithm"
	 * >> https://alienryderflex.com/polygon_fill/
	 *
	 * Have an list describing which edges are considered "active". An
	 * active edge is one whose ending Y coord has yet to be  reached.
	 *
	 * At the start of each scanline Y, add all edges that have became newly active. Since
	 * edges are sorted by their starting Y position, simply retain a pointer to the start
	 * of  all edges that have yet to become  active, and keep adding while the first edge
	 * that  has yet to become active has a starting Y positions <= the current scanline's
	 * SCANLINE_Y. Similarly, at the end  of each scanline, remove  all edges whose max  Y
	 * coord is <= the current scanline's SCANLINE_Y.
	 *
	 * A scanline is rendered by:
	 * - Calculate the ACTIVE_EDGE_X coord for all active edges using `video_line_getxat()'
	 * - Sort the linked list of active edges according to their ACTIVE_EDGE_X
	 *   Since this ordering only rarely changes, this sorting step is usually
	 *   O(n) (where n = # of active edges)
	 * - if method == VIDEO_GFX_FILLPOLY_METHOD_EVEN_ODD:
	 *   - Iterate over the array of sorted edges.
	 *     - Using the CURRENT and NEXT active edges:
	 *     - LL_line_h(self, CURRENT.ACTIVE_EDGE_X, SCANLINE_Y,
	 *                 NEXT.ACTIVE_EDGE_X - CURRENT.ACTIVE_EDGE_X,
	 *                 color);
	 * - if method == VIDEO_GFX_FILLPOLY_METHOD_NON_ZERO:
	 *   - Have a counter "int in_shape = 0"
	 *   - Iterate over the array of sorted edges.
	 *     - Using the CURRENT and NEXT active edges:
	 *     - Update "in_shape += CURRENT.vpe_dir"
	 *     - When "in_shape > 0":
	 *       - LL_line_h(self, CURRENT.ACTIVE_EDGE_X, SCANLINE_Y,
	 *                   NEXT.ACTIVE_EDGE_X - CURRENT.ACTIVE_EDGE_X,
	 *                   color);
	 *       - This hline render can also be merged between adjacent edges
	 *         when "in_shape" remains positive.
	 *
	 * NOTE: matrix transformations and addition of xoff/yoff would only
	 *       happen in the above overview during the "LL_line_h()" call.
	 */

	/* Select appropriate line drawing method:
	 * - When X/Y swapping is enabled, must draw vertical lines instead of horizontal ones */
	xsws_line = &libvideo_swgfx_generic__line_h;
	if (video_imatrix2d_get(&matrix, 1, 0) != 0)
		xsws_line = &libvideo_swgfx_generic__line_v;

	/* Initialize variables and allocate list of "active" edges */
	active_c = 0; /* TODO: Don't unconditionally use alloca() --  use malloca, and if  that
	               * fails, the polygon should have a fallback buffer that we can also use! */
	active_v = (struct video_polygon_edgeref *)alloca(poly->vpd_nactive * sizeof(struct video_polygon_edgeref));
	scanline_y = poly->vpd_ymin;
	scanline_yend = scanline_y + poly->vpd_ydim;
	next_edge_to_activate = 0;

	/* Main scanline iteration loop */
	for (;;) {
		/* Add edges starting at "next_edge_to_activate" with Y coords equal to "scanline_y" */
		while (next_edge_to_activate < poly->vpd_nedges) {
			struct video_polygon_edge const *next_edge;
			next_edge = &poly->vpd_edges[next_edge_to_activate];
			if (video_line_getp0y(&next_edge->vpe_edge) /*>*/ != scanline_y)
				break;
			gfx_assert(active_c < poly->vpd_nactive);
			video_polygon_edgeref_setedge(&active_v[active_c], poly, next_edge);
			active_v[active_c].vper_x = video_line_getxat_fast(&next_edge->vpe_edge, scanline_y);
			++active_c;
			++next_edge_to_activate;
		}
		gfx_assert(active_c >= 2);

		/* Re-sort active edges via their current-scanline-X-coord */
		{
			bool changed;
			do {
				changed = false;
				active_i = 0;
				do {
					video_offset_t this_x = active_v[active_i + 0].vper_x;
					video_offset_t next_x = active_v[active_i + 1].vper_x;
					if (next_x < this_x) {
						struct video_polygon_edgeref temp;
						temp = active_v[active_i + 0];
						active_v[active_i + 0] = active_v[active_i + 1];
						active_v[active_i + 1] = temp;
						changed = true;
					}
				} while (++active_i < (active_c - 1));
			} while (changed);
			gfx_assert(active_c >= 2);
		}

		/* Render the current scanline */
		switch (method) {

		case VIDEO_GFX_FILLPOLY_METHOD_EVEN_ODD:
			active_i = 0;
			do {
				video_offset_t start_x = active_v[active_i + 0].vper_x;
				video_offset_t end_x   = active_v[active_i + 1].vper_x;
				video_dim_t length = (video_dim_t)(end_x - start_x);
				if likely(length) {
					video_coord_t render_x = (video_coord_t)(xoff + video_imatrix2d_mapx(&matrix, start_x, scanline_y));
					video_coord_t render_y = (video_coord_t)(yoff + video_imatrix2d_mapy(&matrix, start_x, scanline_y));
					if (video_imatrix2d_get(&matrix, 0, 0) < 0 || video_imatrix2d_get(&matrix, 0, 1) < 0)
						render_x -= (length - 1);
					if (video_imatrix2d_get(&matrix, 1, 0) < 0 || video_imatrix2d_get(&matrix, 1, 1) < 0)
						render_y -= (length - 1);
					(*xsws_line)(self, render_x, render_y, length, color);
				}
			} while ((active_i += 2) < active_c);
			break;

		case VIDEO_GFX_FILLPOLY_METHOD_NON_ZERO:
			active_i = 0;
			do {
				struct video_polygon_edge const *edge;
				video_offset_t start_x;
				video_dim_t length;
				video_offset_t in_shape;
				gfx_assert(active_i < active_c);
				start_x = active_v[active_i].vper_x;
				edge = video_polygon_edgeref_getedge(&active_v[active_i], poly);
				in_shape = edge->vpe_dir;
				for (;;) {
					++active_i;
					gfx_assert(active_i < active_c);
					edge = video_polygon_edgeref_getedge(&active_v[active_i], poly);
					in_shape += edge->vpe_dir;
					if (in_shape == 0)
						break;
					++active_i;
					gfx_assert(active_i < active_c);
					edge = video_polygon_edgeref_getedge(&active_v[active_i], poly);
					in_shape += edge->vpe_dir;
				}
				length = (video_dim_t)(active_v[active_i].vper_x - start_x);
				if likely(length) {
					video_coord_t render_x = (video_coord_t)(xoff + video_imatrix2d_mapx(&matrix, start_x, scanline_y));
					video_coord_t render_y = (video_coord_t)(yoff + video_imatrix2d_mapy(&matrix, start_x, scanline_y));
					if (video_imatrix2d_get(&matrix, 0, 0) < 0 || video_imatrix2d_get(&matrix, 0, 1) < 0)
						render_x -= (length - 1);
					if (video_imatrix2d_get(&matrix, 1, 0) < 0 || video_imatrix2d_get(&matrix, 1, 1) < 0)
						render_y -= (length - 1);
					(*xsws_line)(self, render_x, render_y, length, color);
				}
			} while ((++active_i) < active_c);
			break;

		default: __builtin_unreachable();
		}

		/* Move on to the next scanline */
		++scanline_y;
		if (scanline_y >= scanline_yend)
			break;

		/* Do 2 things at once:
		 * - Remove active edges with end Y coords equal to "scanline_y"
		 * - Calculate (update) X coords for every (still) active edge */
		active_i = 0;
		gfx_assert(active_c >= 2);
		do {
			struct video_polygon_edge const *edge;
			edge = video_polygon_edgeref_getedge(&active_v[active_i], poly);
			if (video_line_getp1y(&edge->vpe_edge) == /*<=*/ scanline_y) {
				--active_c;
				memmovedownc(&active_v[active_i],
				             &active_v[active_i + 1],
				             active_c - active_i,
				             sizeof(*active_v));
			} else {
				active_v[active_i].vper_x = video_line_getxat_fast(&edge->vpe_edge, scanline_y);
				++active_i;
			}
		} while (active_i < active_c);
	}
	TRACE_END("swgfx_generic__fillpoly()\n");
}

INTERN ATTR_IN(1) NONNULL((4)) void CC
libvideo_swgfx_generic__fillpoly_l(struct video_gfx const *__restrict self,
                                   video_offset_t xoff, video_offset_t yoff,
                                   struct video_polygon_data const *__restrict poly,
                                   video_color_t color, video_imatrix2d_t matrix,
                                   unsigned int method) {
	/* TODO */
	libvideo_swgfx_generic__fillpoly(self, xoff, yoff, poly, color, matrix, method);
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
	INTERN ATTR_IN(1) void CC                                                                     \
	libvideo_swgfx_preblend__fillpoly__##name(struct video_gfx const *__restrict self,            \
	                                          video_offset_t xoff, video_offset_t yoff,           \
	                                          struct video_polygon_data const *__restrict poly,   \
	                                          video_color_t color, video_imatrix2d_t matrix,      \
	                                          unsigned int method) {                              \
		color = preblend(self->vg_blend, color);                                                  \
		if (preblend##_mayignore(self->vg_blend, color))                                          \
			return;                                                                               \
		if (preblend##_maynblend(self->vg_blend, color)) {                                        \
			libvideo_swgfx_noblend__fillpoly(self, xoff, yoff, poly, color, matrix, method);      \
		} else {                                                                                  \
			libvideo_swgfx_generic__fillpoly(self, xoff, yoff, poly, color, matrix, method);      \
		}                                                                                         \
	}                                                                                             \
	INTERN ATTR_IN(1) void CC                                                                     \
	libvideo_swgfx_preblend__fillpoly_l__##name(struct video_gfx const *__restrict self,          \
	                                            video_offset_t xoff, video_offset_t yoff,         \
	                                            struct video_polygon_data const *__restrict poly, \
	                                            video_color_t color, video_imatrix2d_t matrix,    \
	                                            unsigned int method) {                            \
		color = preblend(self->vg_blend, color);                                                  \
		if (preblend##_mayignore(self->vg_blend, color))                                          \
			return;                                                                               \
		libvideo_swgfx_generic__fillpoly_l(self, xoff, yoff, poly, color, matrix, method);        \
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
