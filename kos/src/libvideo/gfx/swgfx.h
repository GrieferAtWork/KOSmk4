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
#ifndef GUARD_LIBVIDEO_GFX_SWGFX_H
#define GUARD_LIBVIDEO_GFX_SWGFX_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <stdbool.h>

#include <libvideo/color.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/gfx/swgfx.h>
#include <libvideo/types.h>

#include "gfx-debug.h"
#include "gfx-utils.h"

DECL_BEGIN

/* Video GFX internal API wrappers (w/ assertions) */
#define video_swgfx_x_getcolor(self, x, y) \
	(gfx_assert_absbounds_xy(self, x, y), _video_swgfx_x_getcolor(self, x, y))
#define video_swgfx_x_putcolor(self, x, y, color) \
	(gfx_assert_absbounds_xy(self, x, y), _video_swgfx_x_putcolor(self, x, y, color))
#define video_swgfx_x_putcolor_p(self, x, y, color) \
	(gfx_assert_absbounds_xy(self, x, y), _video_swgfx_x_putcolor_p(self, x, y, color))
#define video_swgfx_x_getpixel(self, x, y) \
	(gfx_assert_absbounds_xy(self, x, y), _video_swgfx_x_getpixel(self, x, y))
#define video_swgfx_x_setpixel(self, x, y, pixel) \
	(gfx_assert_absbounds_xy(self, x, y), _video_swgfx_x_setpixel(self, x, y, pixel))
#define video_swgfx_x_line_llhh(self, x, y, size_x, size_y, color) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),            \
	 _video_swgfx_x_line_llhh(self, x, y, size_x, size_y, color))
#define video_swgfx_x_line_lhhl(self, x, y, size_x, size_y, color)                        \
	(gfx_assert_absbounds_sx(self, x, size_x),                                            \
	 gfx_assert_absbounds_ymin(self, y),                                                  \
	 gfx_assert(size_y),                                                                  \
	 gfx_assertf(((y) - (self)->vg_clip.vgc_bymin) >= (size_y) - 1,                       \
	             "Line escapes to the top (start-y: %" PRIuCRD ", size-y: %" PRIuDIM ", " \
	             "min-y: %" PRIuCRD ")",                                                  \
	             (y), size_y, (self)->vg_clip.vgc_bymin),                                 \
	 _video_swgfx_x_line_lhhl(self, x, y, size_x, size_y, color))
#define video_swgfx_x_line_h(self, x, y, length, color)                         \
	(gfx_assert_absbounds_y(self, y), gfx_assert_absbounds_sx(self, x, length), \
	 _video_swgfx_x_line_h(self, x, y, length, color))
#define video_swgfx_x_line_v(self, x, y, length, color)                         \
	(gfx_assert_absbounds_x(self, x), gfx_assert_absbounds_sy(self, y, length), \
	 _video_swgfx_x_line_v(self, x, y, length, color))
#define video_swgfx_x_fill(self, x, y, size_x, size_y, color) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),    \
	 _video_swgfx_x_fill(self, x, y, size_x, size_y, color))
#define video_swgfx_x_fillpoly(self, xoff, yoff, poly, color, matrix, method) \
	_video_swgfx_x_fillpoly(self, xoff, yoff, poly, color, matrix, method)
#define video_swgfx_x_gradient(self, x, y, size_x, size_y, colors) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),         \
	 _video_swgfx_x_gradient(self, x, y, size_x, size_y, colors))
#define video_swgfx_x_gradient_h(self, x, y, size_x, size_y, locolor, hicolor) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                     \
	 _video_swgfx_x_gradient_h(self, x, y, size_x, size_y, locolor, hicolor))
#define video_swgfx_x_gradient_v(self, x, y, size_x, size_y, locolor, hicolor) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                     \
	 _video_swgfx_x_gradient_v(self, x, y, size_x, size_y, locolor, hicolor))

#define video_swgfx_x_getcolor_xyswap(self, x, y) \
	(gfx_assert_absbounds_xy(self, x, y), _video_swgfx_x_getcolor_xyswap(self, x, y))
#define video_swgfx_x_putcolor_xyswap(self, x, y, color) \
	(gfx_assert_absbounds_xy(self, x, y), _video_swgfx_x_putcolor_xyswap(self, x, y, color))
#define video_swgfx_x_putcolor_p_xyswap(self, x, y, color) \
	(gfx_assert_absbounds_xy(self, x, y), _video_swgfx_x_putcolor_p_xyswap(self, x, y, color))
#define video_swgfx_x_getpixel_xyswap(self, x, y) \
	(gfx_assert_absbounds_xy(self, x, y), _video_swgfx_x_getpixel_xyswap(self, x, y))
#define video_swgfx_x_setpixel_xyswap(self, x, y, pixel) \
	(gfx_assert_absbounds_xy(self, x, y), _video_swgfx_x_setpixel_xyswap(self, x, y, pixel))
#define video_swgfx_x_line_llhh_xyswap(self, x, y, size_x, size_y, color) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                \
	 _video_swgfx_x_line_llhh_xyswap(self, x, y, size_x, size_y, color))
#define video_swgfx_x_line_lhhl_xyswap(self, x, y, size_x, size_y, color)                 \
	(gfx_assert_absbounds_sx(self, x, size_x),                                            \
	 gfx_assert_absbounds_ymin(self, y),                                                  \
	 gfx_assert(size_y),                                                                  \
	 gfx_assertf(((y) - (self)->vg_clip.vgc_bymin) >= (size_y) - 1,                       \
	             "Line escapes to the top (start-y: %" PRIuCRD ", size-y: %" PRIuDIM ", " \
	             "min-y: %" PRIuCRD ")",                                                  \
	             (y), size_y, (self)->vg_clip.vgc_bymin),                                 \
	 _video_swgfx_x_line_lhhl_xyswap(self, x, y, size_x, size_y, color))
#define video_swgfx_x_line_h_xyswap(self, x, y, length, color)                  \
	(gfx_assert_absbounds_y(self, y), gfx_assert_absbounds_sx(self, x, length), \
	 _video_swgfx_x_line_h_xyswap(self, x, y, length, color))
#define video_swgfx_x_line_v_xyswap(self, x, y, length, color)                  \
	(gfx_assert_absbounds_x(self, x), gfx_assert_absbounds_sy(self, y, length), \
	 _video_swgfx_x_line_v_xyswap(self, x, y, length, color))
#define video_swgfx_x_fill_xyswap(self, x, y, size_x, size_y, color) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),           \
	 _video_swgfx_x_fill_xyswap(self, x, y, size_x, size_y, color))
#define video_swgfx_x_fillpoly_xyswap(self, xoff, yoff, poly, color, matrix, method) \
	_video_swgfx_x_fillpoly_xyswap(self, xoff, yoff, poly, color, matrix, method)
#define video_swgfx_x_gradient_xyswap(self, x, y, size_x, size_y, colors) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                \
	 _video_swgfx_x_gradient_xyswap(self, x, y, size_x, size_y, colors))
#define video_swgfx_x_gradient_h_xyswap(self, x, y, size_x, size_y, locolor, hicolor) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                            \
	 _video_swgfx_x_gradient_h_xyswap(self, x, y, size_x, size_y, locolor, hicolor))
#define video_swgfx_x_gradient_v_xyswap(self, x, y, size_x, size_y, locolor, hicolor) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                            \
	 _video_swgfx_x_gradient_v_xyswap(self, x, y, size_x, size_y, locolor, hicolor))

/* Video BLIT internal API wrappers (w/ assertions) */
#define video_swblitter_x_blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y) \
	(gfx_assert_absbounds_sxy((self)->vbt_dst, dst_x, dst_y, size_x, size_y),    \
	 gfx_assert_absbounds_sxy((self)->vbt_src, src_x, src_y, size_x, size_y),    \
	 _video_swblitter_x_blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y))
#define video_swblitter_x_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y) \
	(gfx_assert_absbounds_sxy((self)->vbt_dst, dst_x, dst_y, dst_size_x, dst_size_y),                               \
	 gfx_assert_absbounds_sxy((self)->vbt_src, src_x, src_y, src_size_x, src_size_y),                               \
	 _video_swblitter_x_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y))
/* TODO: Re-enable these assertions, accounting for "src_matrix" */
#define video_swblitter_x_blit_imatrix(self, dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix) \
	(/*gfx_assert_absbounds_sxy((self)->vbt_dst, dst_x, dst_y, size_x, size_y),*/                    \
	 /*gfx_assert_absbounds_sxy((self)->vbt_src, src_x, src_y, size_x, size_y),*/                    \
	 _video_swblitter_x_blit_imatrix(self, dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix))
#define video_swblitter_x_stretch_imatrix(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, src_matrix) \
	(/*gfx_assert_absbounds_sxy((self)->vbt_dst, dst_x, dst_y, dst_size_x, dst_size_y),*/                                             \
	 /*gfx_assert_absbounds_sxy((self)->vbt_src, src_x, src_y, src_size_x, src_size_y),*/                                             \
	 _video_swblitter_x_stretch_imatrix(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, src_matrix))



/* Video BLIT internal API wrappers (w/ assertions) */
#define video_swblitter3_x_blit(self, out_x, out_y, dst_x, dst_y, src_x, src_y, size_x, size_y) \
	(gfx_assert_absbounds_sxy((self)->vbt3_wrdst, out_x, out_y, size_x, size_y),                \
	 gfx_assert_absbounds_sxy((self)->vbt3_rddst, dst_x, dst_y, size_x, size_y),                \
	 gfx_assert_absbounds_sxy((self)->vbt3_src, src_x, src_y, size_x, size_y),                  \
	 _video_swblitter3_x_blit(self, out_x, out_y, dst_x, dst_y, src_x, src_y, size_x, size_y))
#define video_swblitter3_x_stretch(self, out_x, out_y, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y) \
	(gfx_assert_absbounds_sxy((self)->vbt3_wrdst, out_x, out_y, dst_size_x, dst_size_y),                                           \
	 gfx_assert_absbounds_sxy((self)->vbt3_rddst, dst_x, dst_y, dst_size_x, dst_size_y),                                           \
	 gfx_assert_absbounds_sxy((self)->vbt3_src, src_x, src_y, src_size_x, src_size_y),                                             \
	 _video_swblitter3_x_stretch(self, out_x, out_y, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y))
/* TODO: Re-enable these assertions, accounting for "src_matrix" */
#define video_swblitter3_x_blit_imatrix(self, out_x, out_y, dst_x, dst_y, dst_matrix, src_x, src_y, size_x, size_y, src_matrix) \
	(/*gfx_assert_absbounds_sxy((self)->vbt3_wrdst, out_x, out_y, size_x, size_y),*/                                            \
	 /*gfx_assert_absbounds_sxy((self)->vbt3_rddst, dst_x, dst_y, size_x, size_y),*/                                            \
	 /*gfx_assert_absbounds_sxy((self)->vbt3_src, src_x, src_y, size_x, size_y),*/                                              \
	 _video_swblitter3_x_blit_imatrix(self, out_x, out_y, dst_x, dst_y, dst_matrix, src_x, src_y, size_x, size_y, src_matrix))
#define video_swblitter3_x_stretch_imatrix(self, out_x, out_y, dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix, src_x, src_y, src_size_x, src_size_y, src_matrix) \
	(/*gfx_assert_absbounds_sxy((self)->vbt3_wrdst, out_x, out_y, dst_size_x, dst_size_y),*/                                                                       \
	 /*gfx_assert_absbounds_sxy((self)->vbt3_rddst, dst_x, dst_y, dst_size_x, dst_size_y),*/                                                                       \
	 /*gfx_assert_absbounds_sxy((self)->vbt3_src, src_x, src_y, src_size_x, src_size_y),*/                                                                         \
	 _video_swblitter3_x_stretch_imatrix(self, out_x, out_y, dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix, src_x, src_y, src_size_x, src_size_y, src_matrix))




/************************************************************************/
/************************************************************************/
/************************************************************************/
/* GENERIC, LOW-LEVEL SW-IMPL                                           */
/************************************************************************/
/************************************************************************/
/************************************************************************/

/* Low-level, Generic, always-valid GFX color functions (using only `xsw_getpixel' + `xsw_setpixel') */
INTDEF ATTR_IN(1) video_color_t CC libvideo_swgfx_generic__getcolor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__putcolor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__putcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__putcolor_alpha_factor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
#define DECLARE_libvideo_swgfx_generic__putcolor_FOO(name, mode) \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__putcolor_##name(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
GFX_FOREACH_DEDICATED_BLENDMODE(DECLARE_libvideo_swgfx_generic__putcolor_FOO)
GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(DECLARE_libvideo_swgfx_generic__putcolor_FOO)
#undef DECLARE_libvideo_swgfx_generic__putcolor_FOO

/* Low-level, Generic, always-valid GFX functions (using only `vgfo_getcolor' + `vgfo_putcolor') */
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__line_llhh(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__line_lhhl(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__line_llhh_l(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__line_lhhl_l(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__line_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__line_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__fill(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) NONNULL((4)) void CC libvideo_swgfx_generic__fillpoly(struct video_gfx const *__restrict self, video_offset_t xoff, video_offset_t yoff, struct video_polygon_data const *__restrict poly, video_color_t color, video_imatrix2d_t matrix, unsigned int method);
INTDEF ATTR_IN(1) NONNULL((4)) void CC libvideo_swgfx_generic__fillpoly_l(struct video_gfx const *__restrict self, video_offset_t xoff, video_offset_t yoff, struct video_polygon_data const *__restrict poly, video_color_t color, video_imatrix2d_t matrix, unsigned int method);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_swgfx_generic__gradient(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__gradient_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__gradient_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);

/* For when no blending is being done (meaning that pixels can be written without prior read+blend) */
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend__line_llhh(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend__line_lhhl(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
#define libvideo_swgfx_noblend__line_llhh_l libvideo_swgfx_generic__line_llhh_l
#define libvideo_swgfx_noblend__line_lhhl_l libvideo_swgfx_generic__line_lhhl_l
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend__line_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend__line_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend__fill(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
#define libvideo_swgfx_noblend__fillpoly libvideo_swgfx_generic__fillpoly /* TODO */
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_swgfx_noblend_interp8888__gradient(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend_interp8888__gradient_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend_interp8888__gradient_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);

/* Custom pre-blending GFX functions */
#define DECLARE_libvideo_swgfx_generic__render_preblend_FOO(name, mode, preblend_name, preblend)                                                                                                                                                    \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__line_llhh__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);                           \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__line_lhhl__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);                           \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__line_llhh_l__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);                         \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__line_lhhl_l__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);                         \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__line_h__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);                                                  \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__line_v__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);                                                  \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__fill__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);                                \
	INTDEF ATTR_IN(1) NONNULL((4)) void CC libvideo_swgfx_preblend__fillpoly__##name(struct video_gfx const *__restrict self, video_offset_t xoff, video_offset_t yoff, struct video_polygon_data const *__restrict poly, video_color_t color, video_imatrix2d_t matrix, unsigned int method); \
	INTDEF ATTR_IN(1) NONNULL((4)) void CC libvideo_swgfx_preblend__fillpoly_l__##name(struct video_gfx const *__restrict self, video_offset_t xoff, video_offset_t yoff, struct video_polygon_data const *__restrict poly, video_color_t color, video_imatrix2d_t matrix, unsigned int method); \
	INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_swgfx_preblend__gradient__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);    \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__gradient_h__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor); \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__gradient_v__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
GFX_FOREACH_DEDICATED_PREBLENDMODE(DECLARE_libvideo_swgfx_generic__render_preblend_FOO)
#undef DECLARE_libvideo_swgfx_generic__render_preblend_FOO

/* Shape rendering operator groups */
INTDEF ATTR_RETNONNULL WUNUSED struct gfx_swdrv_shapeops const *CC _libvideo_swgfx_shapeops__noblend(void);
INTDEF ATTR_RETNONNULL WUNUSED struct gfx_swdrv_shapeops const *CC _libvideo_swgfx_shapeops__noblend_interp8888(void);
INTDEF ATTR_RETNONNULL WUNUSED struct gfx_swdrv_shapeops const *CC _libvideo_swgfx_shapeops__noblend_l(void);
INTDEF ATTR_RETNONNULL WUNUSED struct gfx_swdrv_shapeops const *CC _libvideo_swgfx_shapeops__noblend_interp8888_l(void);
#define LINK_libvideo_swgfx_shapeops__preblend_FOO(name, mode, preblend_name, preblend)                                 \
	INTDEF ATTR_RETNONNULL WUNUSED struct gfx_swdrv_shapeops const *CC _libvideo_swgfx_shapeops__preblend_##name(void); \
	INTDEF ATTR_RETNONNULL WUNUSED struct gfx_swdrv_shapeops const *CC _libvideo_swgfx_shapeops__preblend_##name##_l(void);
GFX_FOREACH_DEDICATED_PREBLENDMODE(LINK_libvideo_swgfx_shapeops__preblend_FOO)
#undef LINK_libvideo_swgfx_shapeops__preblend_FOO
INTDEF ATTR_RETNONNULL WUNUSED struct gfx_swdrv_shapeops const *CC _libvideo_swgfx_shapeops__generic(void);
INTDEF ATTR_RETNONNULL WUNUSED struct gfx_swdrv_shapeops const *CC _libvideo_swgfx_shapeops__generic_l(void);



/* Low-level, Generic, always-valid Blit functions (using only `vgfo_getcolor' + `vgfo_putcolor') */
INTDEF ATTR_IN(1) void CC libvideo_swblitter_generic__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_generic__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_generic__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_generic__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_generic__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_generic__stretch_imatrix_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_samebuf__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_samebuf__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_samebuf__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_samebuf__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_samebuf__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_samebuf__stretch_imatrix_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_ckey__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_ckey__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_ckey__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_ckey__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_ckey__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_ckey__stretch_imatrix_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);

INTDEF ATTR_IN(1) void CC libvideo_swblitter_samebuf_ckey__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_samebuf_ckey__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_samebuf_ckey__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_samebuf_ckey__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_samebuf_ckey__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_samebuf_ckey__stretch_imatrix_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);


/* Low-level, Generic, always-valid Blit functions (using only `vgfo_getcolor' + `vgfo_putcolor') */
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_generic__blit(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_generic__stretch_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_generic__stretch_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_generic__blit_imatrix(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_generic__stretch_imatrix_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_imatrix2d_t dst_matrix, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_generic__stretch_imatrix_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_imatrix2d_t dst_matrix, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_samebuf__blit(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_samebuf__stretch_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_samebuf__stretch_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_samebuf__blit_imatrix(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_samebuf__stretch_imatrix_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_samebuf__stretch_imatrix_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);


INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt__stretch_imatrix_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt_interp8888__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt_interp8888__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samebuf__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samebuf__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);

INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt_ckey__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y); /* TODO */
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt_ckey__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y); /* TODO */
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt_ckey__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y); /* TODO */
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt_ckey__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix); /* TODO */
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt_ckey__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix); /* TODO */
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt_ckey__stretch_imatrix_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix); /* TODO */
#define libvideo_swblitter_noblend_samefmt_ckey_interp8888__stretch_l         libvideo_swblitter_noblend_samefmt_ckey__stretch_l
#define libvideo_swblitter_noblend_samefmt_ckey_interp8888__stretch_imatrix_l libvideo_swblitter_noblend_samefmt_ckey__stretch_imatrix_l
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samebuf_ckey__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y); /* TODO */
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samebuf_ckey__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix); /* TODO */

/* The *_difffmt_* operators here "libvideo_swblitter_generic__conv" to be initialized */
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__stretch_imatrix_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt_interp8888__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt_interp8888__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);

INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt_ckey__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt_ckey__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt_ckey__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt_ckey__stretch_imatrix_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt_ckey__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt_ckey__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
#define libvideo_swblitter_noblend_difffmt_ckey_interp8888__stretch_l         libvideo_swblitter_noblend_difffmt_ckey__stretch_l
#define libvideo_swblitter_noblend_difffmt_ckey_interp8888__stretch_imatrix_l libvideo_swblitter_noblend_difffmt_ckey__stretch_imatrix_l






/************************************************************************/
/************************************************************************/
/************************************************************************/
/* GENERIC, HIGH-LEVEL                                                  */
/************************************************************************/
/************************************************************************/
/************************************************************************/

/* Generic GFX operators */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC libvideo_swgfx_blitfrom(struct video_blitter *__restrict ctx);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter3 *FCC libvideo_swgfx_blitfrom3(struct video_blitter3 *__restrict ctx);
INTDEF ATTR_RETNONNULL ATTR_IN(1) struct video_gfx const *CC libvideo_swgfx_noblend(struct video_gfx const *__restrict self);
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC libvideo_swgfx_getcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC libvideo_swgfx_getcolor_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC libvideo_swgfx_getcolor_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC libvideo_swgfx_getcolor_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC libvideo_swgfx_getcolor_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC libvideo_swgfx_getcolor_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_putcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_putcolor_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_putcolor_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_putcolor_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_putcolor_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_putcolor_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_line(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_line_xyswap(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_line_wrap(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_line_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_line_mirror(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_line_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_hline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_hline_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_hline_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_hline_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_hline_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_hline_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_vline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_vline_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_vline_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_vline_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_vline_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_vline_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_fill(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_fill_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_fill_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_fill_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_fill_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_fill_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) NONNULL((4)) void CC libvideo_swgfx_fillpoly(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, struct video_polygon *__restrict poly, video_color_t color, unsigned int method);
INTDEF ATTR_IN(1) NONNULL((4)) void CC libvideo_swgfx_fillpoly_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, struct video_polygon *__restrict poly, video_color_t color, unsigned int method);
INTDEF ATTR_IN(1) NONNULL((4)) void CC libvideo_swgfx_fillpoly_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, struct video_polygon *__restrict poly, video_color_t color, unsigned int method);
INTDEF ATTR_IN(1) NONNULL((4)) void CC libvideo_swgfx_fillpoly_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, struct video_polygon *__restrict poly, video_color_t color, unsigned int method);
INTDEF ATTR_IN(1) NONNULL((4)) void CC libvideo_swgfx_fillpoly_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, struct video_polygon *__restrict poly, video_color_t color, unsigned int method);
INTDEF ATTR_IN(1) NONNULL((4)) void CC libvideo_swgfx_fillpoly_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, struct video_polygon *__restrict poly, video_color_t color, unsigned int method);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_rect(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_rect_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_rect_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_rect_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_rect_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_rect_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_swgfx_gradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_swgfx_gradient_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_swgfx_gradient_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_swgfx_gradient_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_swgfx_gradient_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_swgfx_gradient_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_hgradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_hgradient_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_hgradient_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_hgradient_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_hgradient_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_hgradient_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_vgradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_vgradient_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_vgradient_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_vgradient_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_vgradient_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_vgradient_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_swgfx_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_swgfx_ops_xyswap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_swgfx_ops_wrap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_swgfx_ops_wrap_xyswap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_swgfx_ops_mirror(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_swgfx_ops_mirror_xyswap(void);
#define libvideo_swgfx_ops                 (*_libvideo_swgfx_ops())
#define libvideo_swgfx_ops_xyswap          (*_libvideo_swgfx_ops_xyswap())
#define libvideo_swgfx_ops_wrap            (*_libvideo_swgfx_ops_wrap())
#define libvideo_swgfx_ops_wrap_xyswap     (*_libvideo_swgfx_ops_wrap_xyswap())
#define libvideo_swgfx_ops_mirror          (*_libvideo_swgfx_ops_mirror())
#define libvideo_swgfx_ops_mirror_xyswap   (*_libvideo_swgfx_ops_mirror_xyswap())

/* Generic blit operators */
INTDEF ATTR_IN(1) void CC libvideo_swblitter_blit(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_blit_imatrix(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_blit_rdwrap(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_blit_rdwrap_imatrix(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_blit_wrap(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_blit_wrap_imatrix(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_stretch(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_stretch_imatrix(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_stretch_rdwrap(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_stretch_rdwrap_imatrix(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_stretch_wrap(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_stretch_wrap_imatrix(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_swblitter_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_swblitter_ops_imatrix(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_swblitter_ops_rdwrap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_swblitter_ops_rdwrap_imatrix(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_swblitter_ops_wrap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_swblitter_ops_wrap_imatrix(void);
#define libvideo_swblitter_ops                (*_libvideo_swblitter_ops())                /* Support: - */
#define libvideo_swblitter_ops_imatrix        (*_libvideo_swblitter_ops_imatrix())        /* Support: src+dst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_swblitter_ops_rdwrap         (*_libvideo_swblitter_ops_rdwrap())         /* Support: src:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_swblitter_ops_rdwrap_imatrix (*_libvideo_swblitter_ops_rdwrap_imatrix()) /* Support: src:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+dst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_swblitter_ops_wrap           (*_libvideo_swblitter_ops_wrap())           /* Support: src+dst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_swblitter_ops_wrap_imatrix   (*_libvideo_swblitter_ops_wrap_imatrix())   /* Support: src+dst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+dst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */


/* Generic blit3 operators (ll) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) video_color_t BLITTER3_SWDRV_BLEND_CC libvideo_swblitter3__blend(struct video_blitter3 const *__restrict self, video_color_t dst, video_color_t src);
#define DECLARE_libvideo_swblitter3__blend_FOO(name, mode) \
	INTDEF ATTR_CONST WUNUSED ATTR_IN(1) video_color_t BLITTER3_SWDRV_BLEND_CC libvideo_swblitter3__blend_##name(struct video_blitter3 const *__restrict self, video_color_t dst, video_color_t src);
GFX_FOREACH_DEDICATED_BLENDMODE(DECLARE_libvideo_swblitter3__blend_FOO)
#undef DECLARE_libvideo_swblitter3__blend_FOO
#define DECLARE_libvideo_swblitter3__blend_FOO(name, mode) \
	INTDEF ATTR_PURE WUNUSED ATTR_IN(1) video_color_t BLITTER3_SWDRV_BLEND_CC libvideo_swblitter3__blend_##name(struct video_blitter3 const *__restrict self, video_color_t dst, video_color_t src);
GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(DECLARE_libvideo_swblitter3__blend_FOO)
#undef DECLARE_libvideo_swblitter3__blend_FOO
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__blit__generic(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch__generic_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch__generic_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__blit_imatrix__generic(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch_imatrix__generic_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch_imatrix__generic_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
/* Same as versions above, but `vbt3_wrdst' doesn't do any extra blending */
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__blit__blend1(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch__blend1_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch__blend1_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__blit_imatrix__blend1(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch_imatrix__blend1_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch_imatrix__blend1_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
/* Same as versions above,  but `vbt3_rddst' is a  1bpp-msb
 * bitmask specifying which pixels to write in `vbt3_wrdst'
 * - The *_blend1* version then specifies that no further blending is done by `vbt3_wrdst'
 * - The *_samefmt* version then specifies that `vbt3_wrdst' and `vbt3_src' use the same codec */
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__blit__mask1msb(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch__mask1msb_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch__mask1msb_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__blit_imatrix__mask1msb(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch_imatrix__mask1msb_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch_imatrix__mask1msb_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__blit__mask1msb_blend1_samefmt(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch__mask1msb_blend1_samefmt_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch__mask1msb_blend1_samefmt_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__blit_imatrix__mask1msb_blend1_samefmt(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch_imatrix__mask1msb_blend1_samefmt_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch_imatrix__mask1msb_blend1_samefmt_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__blit__mask1msb_blend1_difffmt(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch__mask1msb_blend1_difffmt_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch__mask1msb_blend1_difffmt_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__blit_imatrix__mask1msb_blend1_difffmt(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch_imatrix__mask1msb_blend1_difffmt_l(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3__stretch_imatrix__mask1msb_blend1_difffmt_n(struct video_blitter3 const *__restrict self, video_coord_t out_x, video_coord_t out_y, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_imatrix2d_t dst_matrix, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);

/* Generic blit3 operators (hl) */
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_blit(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_blit_imatrix(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_blit_rdwrap(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_blit_rdwrap_imatrix(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_blit_wrap(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_blit_wrap_imatrix(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_blit_rdwrap1(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_blit_rdwrap1_imatrix(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_blit_wrap1(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_blit_wrap1_imatrix(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_stretch(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_stretch_imatrix(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_stretch_rdwrap(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_stretch_rdwrap_imatrix(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_stretch_wrap(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_stretch_wrap_imatrix(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_stretch_rdwrap1(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_stretch_rdwrap1_imatrix(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_stretch_wrap1(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter3_stretch_wrap1_imatrix(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter3_ops const *CC _libvideo_swblitter3_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter3_ops const *CC _libvideo_swblitter3_ops_imatrix(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter3_ops const *CC _libvideo_swblitter3_ops_rdwrap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter3_ops const *CC _libvideo_swblitter3_ops_rdwrap_imatrix(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter3_ops const *CC _libvideo_swblitter3_ops_wrap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter3_ops const *CC _libvideo_swblitter3_ops_wrap_imatrix(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter3_ops const *CC _libvideo_swblitter3_ops_rdwrap1(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter3_ops const *CC _libvideo_swblitter3_ops_rdwrap1_imatrix(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter3_ops const *CC _libvideo_swblitter3_ops_wrap1(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter3_ops const *CC _libvideo_swblitter3_ops_wrap1_imatrix(void);
#define libvideo_swblitter3_ops                 (*_libvideo_swblitter3_ops())                 /* Support: - */
#define libvideo_swblitter3_ops_imatrix         (*_libvideo_swblitter3_ops_imatrix())         /* Support: src+wrdst+rddst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_swblitter3_ops_rdwrap          (*_libvideo_swblitter3_ops_rdwrap())          /* Support: src:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_swblitter3_ops_rdwrap_imatrix  (*_libvideo_swblitter3_ops_rdwrap_imatrix())  /* Support: src:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+wrdst+rddst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_swblitter3_ops_wrap            (*_libvideo_swblitter3_ops_wrap())            /* Support: src+wrdst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_swblitter3_ops_wrap_imatrix    (*_libvideo_swblitter3_ops_wrap_imatrix())    /* Support: src+wrdst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+wrdst+rddst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_swblitter3_ops_rdwrap1         (*_libvideo_swblitter3_ops_rdwrap1())         /* Support: src+rddst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_swblitter3_ops_rdwrap1_imatrix (*_libvideo_swblitter3_ops_rdwrap1_imatrix()) /* Support: src+rddst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+wrdst+rddst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_swblitter3_ops_wrap1           (*_libvideo_swblitter3_ops_wrap1())           /* Support: src+wrdst+rddst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_swblitter3_ops_wrap1_imatrix   (*_libvideo_swblitter3_ops_wrap1_imatrix())   /* Support: src+wrdst+rddst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+wrdst+rddst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */


LOCAL ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC
libvideo_swgfx_ops_of(video_gfx_flag_t flags) {
	if (flags & VIDEO_GFX_F_XYSWAP) {
		if (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR))
			return &libvideo_swgfx_ops_mirror_xyswap;
		if (flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP))
			return &libvideo_swgfx_ops_wrap_xyswap;
		return &libvideo_swgfx_ops_xyswap;
	}
	if (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR))
		return &libvideo_swgfx_ops_mirror;
	if (flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP))
		return &libvideo_swgfx_ops_wrap;
	return &libvideo_swgfx_ops;
}

LOCAL ATTR_CONST WUNUSED bool CC
_blendinfo__is_add_or_subtract_or_max(unsigned int func) {
	return func == GFX_BLENDFUNC_ADD ||
	       func == GFX_BLENDFUNC_SUBTRACT ||
	       func == GFX_BLENDFUNC_MAX;
}

/* Update operator callbacks after the caller changed `what' */
LOCAL ATTR_INOUT(1) void CC
libvideo_swgfx_update(struct video_gfx *__restrict self, unsigned int what) {
	struct gfx_swdrv *drv = video_swgfx_getdrv(self);

	/* Update:
	 * - vg_clip.vgc_ops */
	if (what & VIDEO_GFX_UPDATE_FLAGS) {
		/* Select generic operators based on wrapping rules */
		self->vg_clip.vgc_ops = libvideo_swgfx_ops_of(video_gfx_getflags(self));
	}

	/* Update:
	 * - drv->xsw_getcolor */
	if (what & (VIDEO_GFX_UPDATE_FLAGS | VIDEO_GFX_UPDATE_COLORKEY)) {
		/* Select how colors should be read. */
		if (video_gfx_getcodec(self)->vc_codec == VIDEO_CODEC_RGBA8888) {
			/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
			drv->xsw_getcolor = drv->xsw_getpixel;
		} else {
			drv->xsw_getcolor = &libvideo_swgfx_generic__getcolor;
		}
	}

	/* Update:
	 * - vg_clip.vxh_blitfrom
	 * - drv->xsw_putcolor
	 * - drv->xsw_putcolor_p
	 * - drv->xsw_shape */
	if (what & (VIDEO_GFX_UPDATE_FLAGS | VIDEO_GFX_UPDATE_BLEND)) {
		(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vg_blend), GFX_BLENDMODE_OVERRIDE);
		(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vg_blend), GFX_BLENDMODE_ALPHA);

		/* Detect special blend modes. */
		switch (GFX_BLENDMODE_GET_MODE(self->vg_blend)) {
		default:
			if (!(GFX_BLENDMODE_GET_SRCRGB(self->vg_blend) == GFX_BLENDDATA_ONE &&
			      GFX_BLENDMODE_GET_SRCA(self->vg_blend) == GFX_BLENDDATA_ONE &&
			      GFX_BLENDMODE_GET_DSTRGB(self->vg_blend) == GFX_BLENDDATA_ZERO &&
			      GFX_BLENDMODE_GET_DSTA(self->vg_blend) == GFX_BLENDDATA_ZERO &&
			      _blendinfo__is_add_or_subtract_or_max(GFX_BLENDMODE_GET_FUNRGB(self->vg_blend)) &&
			      _blendinfo__is_add_or_subtract_or_max(GFX_BLENDMODE_GET_FUNA(self->vg_blend)))) {
				/* Actual, custom blending */
				drv->xsw_putcolor = &libvideo_swgfx_generic__putcolor;
				break;
			}
			self->vg_blend = GFX_BLENDMODE_OVERRIDE; /* It essentially behaves the same, so... */
			ATTR_FALLTHROUGH
		case GFX_BLENDMODE_OVERRIDE:
			/* No blending is being done -> link operators that try to make use of direct memory access. */

			/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
			if (video_gfx_getcodec(self)->vc_codec == VIDEO_CODEC_RGBA8888) {
				drv->xsw_putcolor = drv->xsw_setpixel;
			} else {
				drv->xsw_putcolor = &libvideo_swgfx_generic__putcolor_noblend;
			}
			drv->xsw_putcolor_p = drv->xsw_putcolor;
			if (video_gfx_getcodec(self)->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) {
				if (video_gfx_getflags(self) & VIDEO_GFX_F_LINEAR) {
					drv->xsw_shape = _libvideo_swgfx_shapeops__noblend_interp8888_l();
				} else {
					drv->xsw_shape = _libvideo_swgfx_shapeops__noblend_interp8888();
				}
			} else if (video_gfx_getflags(self) & VIDEO_GFX_F_LINEAR) {
				drv->xsw_shape = _libvideo_swgfx_shapeops__noblend_l();
			} else {
				drv->xsw_shape = _libvideo_swgfx_shapeops__noblend();
			}
			goto after_blend;

#define LINK_libvideo_swgfx_generic__putcolor_FOO(name, mode)             \
		case mode:                                                        \
			drv->xsw_putcolor = &libvideo_swgfx_generic__putcolor_##name; \
			break;
		GFX_FOREACH_DEDICATED_BLENDMODE(LINK_libvideo_swgfx_generic__putcolor_FOO)
		GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(LINK_libvideo_swgfx_generic__putcolor_FOO)
#undef LINK_libvideo_swgfx_generic__putcolor_FOO
		}

		/* Generic GFX operators that **do** have support for blending */
		switch (GFX_BLENDMODE_GET_MODE(self->vg_blend)) {
#define LINK_libvideo_swgfx_generic__render_preblend_FOO(name, mode, preblend_name, preblend) \
		case mode:                                                                            \
			drv->xsw_putcolor_p = &libvideo_swgfx_generic__putcolor_##preblend_name;          \
			if (video_gfx_getflags(self) & VIDEO_GFX_F_LINEAR) {                              \
				drv->xsw_shape = _libvideo_swgfx_shapeops__preblend_##name##_l();             \
			} else {                                                                          \
				drv->xsw_shape = _libvideo_swgfx_shapeops__preblend_##name();                 \
			}                                                                                 \
			break;
GFX_FOREACH_DEDICATED_PREBLENDMODE(LINK_libvideo_swgfx_generic__render_preblend_FOO)
#undef LINK_libvideo_swgfx_generic__render_preblend_FOO
		default:
			drv->xsw_putcolor_p = drv->xsw_putcolor;
			if (video_gfx_getflags(self) & VIDEO_GFX_F_LINEAR) {
				drv->xsw_shape = _libvideo_swgfx_shapeops__generic_l();
			} else {
				drv->xsw_shape = _libvideo_swgfx_shapeops__generic();
			}
			break;
		}
after_blend:;
	}
}

/* libvideo_swgfx_populate: fill   in    all
 * operators (except the get/set pixel) ones
 * with generic impls.
 *
 * The caller must have already initialized:
 * - video_swgfx_getdrv(self)->xsw_getpixel
 * - video_swgfx_getdrv(self)->xsw_setpixel
 * - self->vg_surf     (if in "vi_initgfx", already done by *your* caller)
 * - self->vg_blend    (if in "vi_initgfx", already done by *your* caller) */
LOCAL ATTR_INOUT(1) void CC
libvideo_swgfx_populate(struct video_gfx *__restrict self) {
	libvideo_swgfx_update(self, VIDEO_GFX_UPDATE_ALL);
}


/* Select appropriate operators for a video blit operations */
LOCAL ATTR_INOUT(1) void CC
video_swblitter_setops(struct video_blitter *__restrict ctx) {
	/* Select operators based on wrapping flags of src/dst */
	video_gfx_flag_t flags = ctx->vbt_dst->vg_surf.vs_flags | ctx->vbt_src->vg_surf.vs_flags;
	if (ctx->vbt_dst->vg_surf.vs_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
		ctx->vbt_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
		               ? &libvideo_swblitter_ops_wrap_imatrix
		               : &libvideo_swblitter_ops_wrap;
	} else if (ctx->vbt_src->vg_surf.vs_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
		ctx->vbt_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
		               ? &libvideo_swblitter_ops_rdwrap_imatrix
		               : &libvideo_swblitter_ops_rdwrap;
	} else {
		ctx->vbt_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
		               ? &libvideo_swblitter_ops_imatrix
		               : &libvideo_swblitter_ops;
	}
}

LOCAL ATTR_INOUT(1) void CC
video_swblitter3_setops(struct video_blitter3 *__restrict ctx) {
	/* Select operators based on wrapping flags of src/dst */
	video_gfx_flag_t flags = ctx->vbt3_rddst->vg_surf.vs_flags |
	                         ctx->vbt3_wrdst->vg_surf.vs_flags |
	                         ctx->vbt3_src->vg_surf.vs_flags;
	if (ctx->vbt3_rddst->vg_surf.vs_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
		if (ctx->vbt3_wrdst->vg_surf.vs_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
			ctx->vbt3_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
			                ? &libvideo_swblitter3_ops_wrap1_imatrix
			                : &libvideo_swblitter3_ops_wrap1;
		} else {
			ctx->vbt3_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
			                ? &libvideo_swblitter3_ops_rdwrap1_imatrix
			                : &libvideo_swblitter3_ops_rdwrap1;
		}
	} else if (ctx->vbt3_wrdst->vg_surf.vs_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
		ctx->vbt3_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
		                ? &libvideo_swblitter3_ops_wrap_imatrix
		                : &libvideo_swblitter3_ops_wrap;
	} else if (ctx->vbt3_src->vg_surf.vs_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
		ctx->vbt3_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
		                ? &libvideo_swblitter3_ops_rdwrap_imatrix
		                : &libvideo_swblitter3_ops_rdwrap;
	} else {
		ctx->vbt3_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
		                ? &libvideo_swblitter3_ops_imatrix
		                : &libvideo_swblitter3_ops;
	}
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_H */
