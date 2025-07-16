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

#include <hybrid/typecore.h>

#include <stdbool.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/color.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "gfx-debug.h"
#include "gfx-utils.h"

DECL_BEGIN

/* This is the layout of `video_gfx::_vx_driver' expected by generic SW-based GFX */
struct gfx_swdrv {
	/* All of the following callbacks are [1..1][const]
	 * NOTES:
	 * - Don't use these operators; only use `struct video_gfx_ops'
	 * - All these operators take pre-clamped/rotated/mirrored/etc. coords */

	/* TODO: Group operators that are always set all at once into sub-structs */

	/* Get the color of a pixel */
	ATTR_IN_T(1) video_color_t
	(CC *xsw_getcolor)(struct video_gfx const *__restrict self,
	                   video_coord_t abs_x, video_coord_t abs_y);

	/* Place a colored pixel ontop of the graphic (whilst also performing blending) */
	ATTR_IN_T(1) void
	(CC *xsw_putcolor)(struct video_gfx const *__restrict self,
	                   video_coord_t abs_x, video_coord_t abs_y,
	                   video_color_t color);

	/* Same as `xsw_putcolor', but given color has been pre-blended for certain blend modes:
	 * - GFX_BLENDMODE_ALPHA:             as per `GFX_BLENDMODE_ALPHA_PREMULTIPLIED'
	 * - GFX_BLENDMODE_ALPHA_FACTOR(*):   as per `GFX_BLENDMODE_ALPHA_PREMULTIPLIED'
	 * - GFX_BLENDMODE_ALPHA_OVERRIDE(*): as per `GFX_BLENDMODE_ALPHA_PREMULTIPLIED'
	 * - GFX_BLENDMODE_ADD:               as per `GFX_BLENDMODE_ADD_PREMULTIPLIED'
	 * otherwise, identical to `xsw_putcolor' */
	ATTR_IN_T(1) void
	(CC *xsw_putcolor_p)(struct video_gfx const *__restrict self,
	                     video_coord_t abs_x, video_coord_t abs_y,
	                     video_color_t preblended_color);

	/* Get the raw data of a pixel (no blending is done) */
	ATTR_IN_T(1) video_pixel_t
	(CC *xsw_getpixel)(struct video_gfx const *__restrict self,
	                   video_coord_t abs_x, video_coord_t abs_y);

	/* Set the raw data of a pixel (no blending is done) */
	ATTR_IN_T(1) void
	(CC *xsw_setpixel)(struct video_gfx const *__restrict self,
	                   video_coord_t abs_x, video_coord_t abs_y,
	                   video_pixel_t pixel);

	/* Diagonal line from top-left -> bottom-right
	 * @assume(size_x > 0);
	 * @assume(size_y > 0); */
	ATTR_IN_T(1) void /* TODO: Some way to specify the line width */
	(CC *xsw_absline_llhh)(struct video_gfx const *__restrict self,
	                       video_coord_t x, video_coord_t y,
	                       video_dim_t size_x, video_dim_t size_y,
	                       video_color_t color);

	/* Diagonal line from bottom-left -> top-right
	 * @assume(size_x > 0);
	 * @assume(size_y > 0); */
	ATTR_IN_T(1) void /* TODO: Some way to specify the line width */
	(CC *xsw_absline_lhhl)(struct video_gfx const *__restrict self,
	                       video_coord_t x, video_coord_t y,
	                       video_dim_t size_x, video_dim_t size_y,
	                       video_color_t color);

	/* Horizontal line
	 * @assume(length > 0); */
	ATTR_IN_T(1) void
	(CC *xsw_absline_h)(struct video_gfx const *__restrict self,
	                    video_coord_t x, video_coord_t y,
	                    video_dim_t length, video_color_t color);

	/* Vertical line
	 * @assume(length > 0); */
	ATTR_IN_T(1) void
	(CC *xsw_absline_v)(struct video_gfx const *__restrict self,
	                    video_coord_t x, video_coord_t y,
	                    video_dim_t length, video_color_t color);

	/* TODO: Curve drawing (Bézier curve) */

	/* Rect fill
	 * @assume(size_x > 0);
	 * @assume(size_y > 0); */
	ATTR_IN_T(1) void
	(CC *xsw_absfill)(struct video_gfx const *__restrict self,
	                  video_coord_t x, video_coord_t y,
	                  video_dim_t size_x, video_dim_t size_y,
	                  video_color_t color);

	/* Paint masked pixels
	 * @assume(size_x > 0);
	 * @assume(size_y > 0); */
	ATTR_IN_T(1) ATTR_IN_T(6) ATTR_IN_T(7) void
	(CC *xsw_absfillmask)(struct video_gfx const *__restrict self,
	                      video_coord_t dst_x, video_coord_t dst_y,
	                      video_dim_t size_x, video_dim_t size_y,
	                      video_color_t const bg_fg_colors[2],
	                      struct video_bitmask const *__restrict bm);

	/* Stretch and paint masked pixels
	 * @assume(dst_size_x > 0);
	 * @assume(dst_size_y > 0);
	 * @assume(src_size_x > 0);
	 * @assume(src_size_y > 0);
	 * @assume(dst_size_x != src_size_x);
	 * @assume(dst_size_y != src_size_y); */
	ATTR_IN_T(1) ATTR_IN_T(6) ATTR_IN_T(9) void
	(CC *xsw_absfillstretchmask)(struct video_gfx const *__restrict self,
	                             video_coord_t dst_x, video_coord_t dst_y,
	                             video_dim_t dst_size_x, video_dim_t dst_size_y,
	                             video_color_t const bg_fg_colors[2],
	                             video_dim_t src_size_x, video_dim_t src_size_y,
	                             struct video_bitmask const *__restrict bm);

	/* Same as `xsw_absfill', but do so via gradient with colors[y][x] being used
	 * to essentially  do a  VIDEO_GFX_F_LINEAR stretch-blit  into the  specified
	 * destination rect.
	 * @assume(size_x > 0);
	 * @assume(size_y > 0); */
	ATTR_IN_T(1) ATTR_IN_T(6) void
	(CC *xsw_absgradient)(struct video_gfx const *__restrict self,
	                      video_coord_t x, video_coord_t y,
	                      video_dim_t size_x, video_dim_t size_y,
	                      video_color_t const colors[2][2]);
	ATTR_IN_T(1) void
	(CC *xsw_absgradient_h)(struct video_gfx const *__restrict self,
	                        video_coord_t x, video_coord_t y,
	                        video_dim_t size_x, video_dim_t size_y,
	                        video_color_t locolor, video_color_t hicolor);
	ATTR_IN_T(1) void
	(CC *xsw_absgradient_v)(struct video_gfx const *__restrict self,
	                        video_coord_t x, video_coord_t y,
	                        video_dim_t size_x, video_dim_t size_y,
	                        video_color_t locolor, video_color_t hicolor);
};

#define video_swgfx_getdrv(self) \
	((struct gfx_swdrv *)(self)->_vx_driver)

/* Video GFX internal API wrappers */
#define _video_swgfx_x_getcolor(self, x, y) \
	(*video_swgfx_getdrv(self)->xsw_getcolor)(self, x, y)
#define _video_swgfx_x_putcolor(self, x, y, color) \
	(*video_swgfx_getdrv(self)->xsw_putcolor)(self, x, y, color)
#define _video_swgfx_x_putcolor_p(self, x, y, color) \
	(*video_swgfx_getdrv(self)->xsw_putcolor_p)(self, x, y, color)
#define _video_swgfx_x_getpixel(self, x, y) \
	(*video_swgfx_getdrv(self)->xsw_getpixel)(self, x, y)
#define _video_swgfx_x_setpixel(self, x, y, pixel) \
	(*video_swgfx_getdrv(self)->xsw_setpixel)(self, x, y, pixel)
#define _video_swgfx_x_absline_llhh(self, x, y, size_x, size_y, color) \
	(*video_swgfx_getdrv(self)->xsw_absline_llhh)(self, x, y, size_x, size_y, color)
#define _video_swgfx_x_absline_lhhl(self, x, y, size_x, size_y, color) \
	(*video_swgfx_getdrv(self)->xsw_absline_lhhl)(self, x, y, size_x, size_y, color)
#define _video_swgfx_x_absline_h(self, x, y, length, color) \
	(*video_swgfx_getdrv(self)->xsw_absline_h)(self, x, y, length, color)
#define _video_swgfx_x_absline_v(self, x, y, length, color) \
	(*video_swgfx_getdrv(self)->xsw_absline_v)(self, x, y, length, color)
#define _video_swgfx_x_absfill(self, x, y, size_x, size_y, color) \
	(*video_swgfx_getdrv(self)->xsw_absfill)(self, x, y, size_x, size_y, color)
#define _video_swgfx_x_absfillmask(self, dst_x, dst_y, size_x, size_y, bg_fg_colors, bm) \
	(*video_swgfx_getdrv(self)->xsw_absfillmask)(self, dst_x, dst_y, size_x, size_y, bg_fg_colors, bm)
#define _video_swgfx_x_absfillstretchmask(self, dst_x, dst_y, dst_size_x, dst_size_y, bg_fg_colors, src_size_x, src_size_y, bm) \
	(*video_swgfx_getdrv(self)->xsw_absfillstretchmask)(self, dst_x, dst_y, dst_size_x, dst_size_y, bg_fg_colors, src_size_x, src_size_y, bm)
#define _video_swgfx_x_absgradient(self, x, y, size_x, size_y, colors) \
	(*video_swgfx_getdrv(self)->xsw_absgradient)(self, x, y, size_x, size_y, colors)
#define _video_swgfx_x_absgradient_h(self, x, y, size_x, size_y, locolor, hicolor) \
	(*video_swgfx_getdrv(self)->xsw_absgradient_h)(self, x, y, size_x, size_y, locolor, hicolor)
#define _video_swgfx_x_absgradient_v(self, x, y, size_x, size_y, locolor, hicolor) \
	(*video_swgfx_getdrv(self)->xsw_absgradient_v)(self, x, y, size_x, size_y, locolor, hicolor)

#define _video_swgfx_x_getcolor_xyswap(self, x, y) \
	(*video_swgfx_getdrv(self)->xsw_getcolor)(self, y, x)
#define _video_swgfx_x_putcolor_xyswap(self, x, y, color) \
	(*video_swgfx_getdrv(self)->xsw_putcolor)(self, y, x, color)
#define _video_swgfx_x_putcolor_p_xyswap(self, x, y, color) \
	(*video_swgfx_getdrv(self)->xsw_putcolor_p)(self, y, x, color)
#define _video_swgfx_x_getpixel_xyswap(self, x, y) \
	(*video_swgfx_getdrv(self)->xsw_getpixel)(self, y, x)
#define _video_swgfx_x_setpixel_xyswap(self, x, y, pixel) \
	(*video_swgfx_getdrv(self)->xsw_setpixel)(self, y, x, pixel)
#define _video_swgfx_x_absline_llhh_xyswap(self, x, y, size_x, size_y, color) \
	(*video_swgfx_getdrv(self)->xsw_absline_llhh)(self, y, x, size_x, size_y, color)
#define _video_swgfx_x_absline_lhhl_xyswap(self, x, y, size_x, size_y, color) \
	(*video_swgfx_getdrv(self)->xsw_absline_lhhl)(self, y, x, size_x, size_y, color)
#define _video_swgfx_x_absline_h_xyswap(self, x, y, length, color) \
	(*video_swgfx_getdrv(self)->xsw_absline_v)(self, y, x, length, color)
#define _video_swgfx_x_absline_v_xyswap(self, x, y, length, color) \
	(*video_swgfx_getdrv(self)->xsw_absline_h)(self, y, x, length, color)
#define _video_swgfx_x_absfill_xyswap(self, x, y, size_x, size_y, color) \
	(*video_swgfx_getdrv(self)->xsw_absfill)(self, y, x, size_y, size_x, color)
#define _video_swgfx_x_absgradient_xyswap(self, x, y, size_x, size_y, colors) \
	(*video_swgfx_getdrv(self)->xsw_absgradient)(self, y, x, size_y, size_x, colors)
#define _video_swgfx_x_absgradient_h_xyswap(self, x, y, size_x, size_y, locolor, hicolor) \
	(*video_swgfx_getdrv(self)->xsw_absgradient_v)(self, y, x, size_y, size_x, locolor, hicolor)
#define _video_swgfx_x_absgradient_v_xyswap(self, x, y, size_x, size_y, locolor, hicolor) \
	(*video_swgfx_getdrv(self)->xsw_absgradient_h)(self, y, x, size_y, size_x, locolor, hicolor)


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
#define video_swgfx_x_absline_llhh(self, x, y, size_x, size_y, color) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),            \
	 _video_swgfx_x_absline_llhh(self, x, y, size_x, size_y, color))
#define video_swgfx_x_absline_lhhl(self, x, y, size_x, size_y, color)                     \
	(gfx_assert_absbounds_sx(self, x, size_x),                                            \
	 gfx_assert_absbounds_ymin(self, y),                                                  \
	 gfx_assert(size_y),                                                                  \
	 gfx_assertf(((y) - (self)->vx_hdr.vxh_bymin) >= (size_y) - 1,                        \
	             "Line escapes to the top (start-y: %" PRIuCRD ", size-y: %" PRIuDIM ", " \
	             "min-y: %" PRIuCRD ")",                                                  \
	             (y), size_y, (self)->vx_hdr.vxh_bymin),                                  \
	 _video_swgfx_x_absline_lhhl(self, x, y, size_x, size_y, color))
#define video_swgfx_x_absline_h(self, x, y, length, color)                      \
	(gfx_assert_absbounds_y(self, y), gfx_assert_absbounds_sx(self, x, length), \
	 _video_swgfx_x_absline_h(self, x, y, length, color))
#define video_swgfx_x_absline_v(self, x, y, length, color)                      \
	(gfx_assert_absbounds_x(self, x), gfx_assert_absbounds_sy(self, y, length), \
	 _video_swgfx_x_absline_v(self, x, y, length, color))
#define video_swgfx_x_absfill(self, x, y, size_x, size_y, color) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),       \
	 _video_swgfx_x_absfill(self, x, y, size_x, size_y, color))
#define video_swgfx_x_absfillmask(self, dst_x, dst_y, size_x, size_y, bg_fg_colors, bm) \
	(gfx_assert_absbounds_sxy(self, dst_x, dst_y, size_x, size_y),                      \
	 _video_swgfx_x_absfillmask(self, dst_x, dst_y, size_x, size_y, bg_fg_colors, bm))
#define video_swgfx_x_absfillstretchmask(self, dst_x, dst_y, dst_size_x, dst_size_y, bg_fg_colors, src_size_x, src_size_y, bm) \
	(gfx_assert_absbounds_sxy(self, dst_x, dst_y, dst_size_x, dst_size_y),                                                     \
	 gfx_assert(src_size_x), gfx_assert(src_size_y),                                                                           \
	 gfx_assertf((dst_size_x) != (src_size_x) || (dst_size_y) != (src_size_y),                                                 \
	             "dst/src size identical: {%" PRIuDIM "x%" PRIuDIM "}", dst_size_x, dst_size_y),                               \
	 _video_swgfx_x_absfillstretchmask(self, dst_x, dst_y, dst_size_x, dst_size_y, bg_fg_colors, src_size_x, src_size_y, bm))
#define video_swgfx_x_absgradient(self, x, y, size_x, size_y, colors) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),            \
	 _video_swgfx_x_absgradient(self, x, y, size_x, size_y, colors))
#define video_swgfx_x_absgradient_h(self, x, y, size_x, size_y, locolor, hicolor) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                        \
	 _video_swgfx_x_absgradient_h(self, x, y, size_x, size_y, locolor, hicolor))
#define video_swgfx_x_absgradient_v(self, x, y, size_x, size_y, locolor, hicolor) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                        \
	 _video_swgfx_x_absgradient_v(self, x, y, size_x, size_y, locolor, hicolor))

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
#define video_swgfx_x_absline_llhh_xyswap(self, x, y, size_x, size_y, color) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                   \
	 _video_swgfx_x_absline_llhh_xyswap(self, x, y, size_x, size_y, color))
#define video_swgfx_x_absline_lhhl_xyswap(self, x, y, size_x, size_y, color)              \
	(gfx_assert_absbounds_sx(self, x, size_x),                                            \
	 gfx_assert_absbounds_ymin(self, y),                                                  \
	 gfx_assert(size_y),                                                                  \
	 gfx_assertf(((y) - (self)->vx_hdr.vxh_bymin) >= (size_y) - 1,                        \
	             "Line escapes to the top (start-y: %" PRIuCRD ", size-y: %" PRIuDIM ", " \
	             "min-y: %" PRIuCRD ")",                                                  \
	             (y), size_y, (self)->vx_hdr.vxh_bymin),                                  \
	 _video_swgfx_x_absline_lhhl_xyswap(self, x, y, size_x, size_y, color))
#define video_swgfx_x_absline_h_xyswap(self, x, y, length, color)               \
	(gfx_assert_absbounds_y(self, y), gfx_assert_absbounds_sx(self, x, length), \
	 _video_swgfx_x_absline_h_xyswap(self, x, y, length, color))
#define video_swgfx_x_absline_v_xyswap(self, x, y, length, color)               \
	(gfx_assert_absbounds_x(self, x), gfx_assert_absbounds_sy(self, y, length), \
	 _video_swgfx_x_absline_v_xyswap(self, x, y, length, color))
#define video_swgfx_x_absfill_xyswap(self, x, y, size_x, size_y, color) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),              \
	 _video_swgfx_x_absfill_xyswap(self, x, y, size_x, size_y, color))
#define video_swgfx_x_absgradient_xyswap(self, x, y, size_x, size_y, colors) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                   \
	 _video_swgfx_x_absgradient_xyswap(self, x, y, size_x, size_y, colors))
#define video_swgfx_x_absgradient_h_xyswap(self, x, y, size_x, size_y, locolor, hicolor) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                               \
	 _video_swgfx_x_absgradient_h_xyswap(self, x, y, size_x, size_y, locolor, hicolor))
#define video_swgfx_x_absgradient_v_xyswap(self, x, y, size_x, size_y, locolor, hicolor) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                               \
	 _video_swgfx_x_absgradient_v_xyswap(self, x, y, size_x, size_y, locolor, hicolor))

/* 2d integer matrix video_imatrix2d_t[y][x].
 * Only allowed to  hold values -1,  0, or  1
 *
 * Vector is only applied to relative coords (never absolute ones).
 * >> used_x = base_x + video_imatrix2d_get(matrix, 0, 0) * rel_x + video_imatrix2d_get(matrix, 0, 1) * rel_y;
 * >> used_y = base_y + video_imatrix2d_get(matrix, 1, 0) * rel_x + video_imatrix2d_get(matrix, 1, 1) * rel_y; */
typedef __INT_FAST32_TYPE__ video_imatrix2d_t;
#define __video_imatrix2d_shift(y, x)      ((y) * 16 + (x) * 8)
#define __video_imatrix2d_mask(y, x)       ((video_imatrix2d_t)0xff << __video_imatrix2d_shift(y, x))
#define video_imatrix2d_get(self, y, x)    ((__INT8_TYPE__)(*(self) >> __video_imatrix2d_shift(y, x)))
#define video_imatrix2d_set(self, y, x, v) (void)(*(self) = (*(self) & ~__video_imatrix2d_mask(y, x)) | ((video_imatrix2d_t)(__UINT8_TYPE__)(v) << __video_imatrix2d_shift(y, x)))
#define VIDEO_IMATRIX2D_INIT(_00, _01, _10, _11)                                                    \
	(((video_imatrix2d_t)(__UINT8_TYPE__)(_00)) | ((video_imatrix2d_t)(__UINT8_TYPE__)(_01) << 8) | \
	 ((video_imatrix2d_t)(__UINT8_TYPE__)(_10) << 16) | ((video_imatrix2d_t)(__UINT8_TYPE__)(_11) << 24))
#define video_imatrix2d_swap(self, y1, x1, y2, x2)                            \
	do {                                                                      \
		__INT_FAST8_TYPE__ _temp = video_imatrix2d_get(self, y1, x1);         \
		video_imatrix2d_set(self, y1, x1, video_imatrix2d_get(self, y2, x2)); \
		video_imatrix2d_set(self, y2, x2, _temp);                             \
	}	__WHILE0





struct blt_swdrv {
	/* All of the following callbacks are [1..1][const]
	 * NOTES:
	 * - Don't use these operators; only use `struct video_gfx_ops'
	 * - All these operators take pre-clamped/rotated/mirrored/etc. coords */

	/* Blit the contents of another video buffer into this one.
	 * @assume(size_x > 0);
	 * @assume(size_y > 0); */
	ATTR_IN_T(1) void
	(CC *bsw_blit)(struct video_blitter const *__restrict self,
	               video_coord_t dst_x, video_coord_t dst_y,
	               video_coord_t src_x, video_coord_t src_y,
	               video_dim_t size_x, video_dim_t size_y);

	/* Same as `bsw_blit', but stretch the contents
	 * @assume(dst_size_x > 0);
	 * @assume(dst_size_y > 0);
	 * @assume(src_size_x > 0);
	 * @assume(src_size_y > 0);
	 * @assume(dst_size_x != src_size_x);
	 * @assume(dst_size_y != src_size_y); */
	ATTR_IN_T(1) void
	(CC *bsw_stretch)(struct video_blitter const *__restrict self,
	                  video_coord_t dst_x, video_coord_t dst_y,
	                  video_dim_t dst_size_x, video_dim_t dst_size_y,
	                  video_coord_t src_x, video_coord_t src_y,
	                  video_dim_t src_size_x, video_dim_t src_size_y);

	/* Same as "bsw_blit", but uses a matrix to calculate source pixel locations:
	 * >> for (video_coord_t y = 0; y < size_y; ++y) {
	 * >>     for (video_coord_t x = 0; x < size_x; ++x) {
	 * >>         video_coord_t used_src_x = src_x + src_matrix[0][0] * x + src_matrix[0][1] * y;
	 * >>         video_coord_t used_src_y = src_y + src_matrix[1][0] * x + src_matrix[1][1] * y;
	 * >>         video_coord_t used_dst_x = dst_x + x;
	 * >>         video_coord_t used_dst_y = dst_y + y;
	 * >>         video_color_t color = (*self->vbt_src->_vx_xops.xsw_getcolor)(self->vbt_src, used_src_x, used_src_y);
	 * >>         (*self->vbt_dst->_vx_xops.xsw_putcolor)(self->vbt_dst, used_dst_x, used_dst_y, color);
	 * >>     }
	 * >> }
	 *
	 * The given "src_matrix" is assumed to only contain values -1, 0 or  1,
	 * meaning it can only be used to do 90° rotation, as well as mirroring.
	 *
	 * When values outside this range are used, results are undefined. */
	ATTR_IN_T(1) void
	(CC *bsw_blit_imatrix)(struct video_blitter const *__restrict self,
	                       video_coord_t dst_x, video_coord_t dst_y,
	                       video_coord_t src_x, video_coord_t src_y,
	                       video_dim_t size_x, video_dim_t size_y,
	                       video_imatrix2d_t src_matrix);

	/* Same as "bsw_stretch", but uses a matrix to calculate source pixel locations. */
	ATTR_IN_T(1) void
	(CC *bsw_stretch_imatrix)(struct video_blitter const *__restrict self,
	                          video_coord_t dst_x, video_coord_t dst_y,
	                          video_dim_t dst_size_x, video_dim_t dst_size_y,
	                          video_coord_t src_x, video_coord_t src_y,
	                          video_dim_t src_size_x, video_dim_t src_size_y,
	                          video_imatrix2d_t src_matrix);

	/* Video format converter (used for quickly converting pixel formats under noblend)
	 * [valid_if(bsw_blit            == &libvideo_swblitter_noblend_difffmtblit ||
	 *           bsw_stretch         == &libvideo_swblitter_noblend_difffmtstretch_l ||
	 *           bsw_stretch         == &libvideo_swblitter_noblend_difffmtstretch_n ||
	 *           bsw_blit_imatrix    == &libvideo_swblitter_noblend_difffmtblit_imatrix ||
	 *           bsw_stretch_imatrix == &libvideo_swblitter_noblend_difffmtstretch_imatrix_l ||
	 *           bsw_stretch_imatrix == &libvideo_swblitter_noblend_difffmtstretch_imatrix_n)] */
	struct video_converter bsw_conv;
};

#define video_swblitter_getdrv(self) \
	((struct blt_swdrv *)(self)->_vbt_driver)
#define video_swblitter_getcdrv(self) \
	((struct blt_swdrv const *)(self)->_vbt_driver)
#define libvideo_swblitter_generic__conv(self) \
	(&video_swblitter_getdrv(self)->bsw_conv)
#define libvideo_swblitter_generic__cconv(self) \
	(&video_swblitter_getcdrv(self)->bsw_conv)

/* Video BLIT internal API wrappers */
#define _video_swblitter_x_blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y) \
	(*video_swblitter_getcdrv(self)->bsw_blit)(self, dst_x, dst_y, src_x, src_y, size_x, size_y)
#define _video_swblitter_x_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y) \
	(*video_swblitter_getcdrv(self)->bsw_stretch)(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y)
#define _video_swblitter_x_blit_imatrix(self, dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix) \
	(*video_swblitter_getcdrv(self)->bsw_blit_imatrix)(self, dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix)
#define _video_swblitter_x_stretch_imatrix(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, src_matrix) \
	(*video_swblitter_getcdrv(self)->bsw_stretch_imatrix)(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, src_matrix)

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






#if defined(__i386__) && !defined(__x86_64__) && __has_attribute(__regparm__)
#define BLT3_SWDRV_BLEND_CC __attribute__((__regparm__(3)))
#else /* __has_attribute(__regparm__) */
#define BLT3_SWDRV_BLEND_CC FCC
#endif /* !__has_attribute(__regparm__) */
typedef ATTR_PURE_T WUNUSED_T ATTR_IN_T(1) video_color_t
(BLT3_SWDRV_BLEND_CC *blt3_blend_t)(struct video_blitter3 const *__restrict self,
                                    video_color_t dst, video_color_t src);

struct blt3_swdrv {
	/* All of the following callbacks are [1..1][const]
	 * NOTES:
	 * - Don't use these operators; only use `struct video_gfx_ops'
	 * - All these operators take pre-clamped/rotated/mirrored/etc. coords */

	/* [== :vbt3_rddst->vx_blend] */
	gfx_blendmode_t bsw3_blendmode;

	/* Blend "dst" and "src" colors together and return the result.
	 * @param: dst: color, as read from `self->vbt3_dsc'
	 * @param: dst: color, as read from `self->vbt3_src'
	 * @return: * : Fully-blended color */
	blt3_blend_t bsw3_blend;

	/* Blit the contents of another video buffer into this one.
	 * @assume(size_x > 0);
	 * @assume(size_y > 0); */
	ATTR_IN_T(1) void
	(CC *bsw3_blit)(struct video_blitter3 const *__restrict self,
	                video_coord_t out_x, video_coord_t out_y,
	                video_coord_t dst_x, video_coord_t dst_y,
	                video_coord_t src_x, video_coord_t src_y,
	                video_dim_t size_x, video_dim_t size_y);

	/* Same as `bsw3_blit', but stretch the contents
	 * @assume(dst_size_x > 0);
	 * @assume(dst_size_y > 0);
	 * @assume(src_size_x > 0);
	 * @assume(src_size_y > 0);
	 * @assume(dst_size_x != src_size_x);
	 * @assume(dst_size_y != src_size_y); */
	ATTR_IN_T(1) void
	(CC *bsw3_stretch)(struct video_blitter3 const *__restrict self,
	                   video_coord_t out_x, video_coord_t out_y,
	                   video_coord_t dst_x, video_coord_t dst_y,
	                   video_dim_t dst_size_x, video_dim_t dst_size_y,
	                   video_coord_t src_x, video_coord_t src_y,
	                   video_dim_t src_size_x, video_dim_t src_size_y);

	/* s.a. `blt_swdrv::bsw_blit_imatrix' */
	ATTR_IN_T(1) void
	(CC *bsw3_blit_imatrix)(struct video_blitter3 const *__restrict self,
	                        video_coord_t out_x, video_coord_t out_y,
	                        video_coord_t dst_x, video_coord_t dst_y,
	                        video_imatrix2d_t dst_matrix,
	                        video_coord_t src_x, video_coord_t src_y,
	                        video_dim_t size_x, video_dim_t size_y,
	                        video_imatrix2d_t src_matrix);

	/* s.a. `blt_swdrv::bsw_stretch_imatrix' */
	ATTR_IN_T(1) void
	(CC *bsw3_stretch_imatrix)(struct video_blitter3 const *__restrict self,
	                           video_coord_t out_x, video_coord_t out_y,
	                           video_coord_t dst_x, video_coord_t dst_y,
	                           video_dim_t dst_size_x, video_dim_t dst_size_y,
	                           video_imatrix2d_t dst_matrix,
	                           video_coord_t src_x, video_coord_t src_y,
	                           video_dim_t src_size_x, video_dim_t src_size_y,
	                           video_imatrix2d_t src_matrix);

	/* Video format converter (used for quickly converting pixel formats under noblend)
	 * [valid_if(bsw_blit            == &libvideo_swblitter_noblend_difffmtblit ||
	 *           bsw_stretch         == &libvideo_swblitter_noblend_difffmtstretch_l ||
	 *           bsw_stretch         == &libvideo_swblitter_noblend_difffmtstretch_n ||
	 *           bsw_blit_imatrix    == &libvideo_swblitter_noblend_difffmtblit_imatrix ||
	 *           bsw_stretch_imatrix == &libvideo_swblitter_noblend_difffmtstretch_imatrix_l ||
	 *           bsw_stretch_imatrix == &libvideo_swblitter_noblend_difffmtstretch_imatrix_n)] */
	struct video_converter bsw3_conv;
};

#define video_swblitter3_getdrv(self) \
	((struct blt3_swdrv *)(self)->_vbt3_driver)
#define video_swblitter3_getcdrv(self) \
	((struct blt3_swdrv const *)(self)->_vbt3_driver)
#define libvideo_swblitter3_generic__conv(self) \
	(&video_swblitter3_getdrv(self)->bsw3_conv)
#define libvideo_swblitter3_generic__cconv(self) \
	(&video_swblitter3_getcdrv(self)->bsw3_conv)

/* Video BLIT internal API wrappers */
#define _video_swblitter3_x_blit(self, out_x, out_y, dst_x, dst_y, src_x, src_y, size_x, size_y) \
	(*video_swblitter3_getcdrv(self)->bsw3_blit)(self, out_x, out_y, dst_x, dst_y, src_x, src_y, size_x, size_y)
#define _video_swblitter3_x_stretch(self, out_x, out_y, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y) \
	(*video_swblitter3_getcdrv(self)->bsw3_stretch)(self, out_x, out_y, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y)
#define _video_swblitter3_x_blit_imatrix(self, out_x, out_y, dst_x, dst_y, dst_matrix, src_x, src_y, size_x, size_y, src_matrix) \
	(*video_swblitter3_getcdrv(self)->bsw3_blit_imatrix)(self, out_x, out_y, dst_x, dst_y, dst_matrix, src_x, src_y, size_x, size_y, src_matrix)
#define _video_swblitter3_x_stretch_imatrix(self, out_x, out_y, dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix, src_x, src_y, src_size_x, src_size_y, src_matrix) \
	(*video_swblitter3_getcdrv(self)->bsw3_stretch_imatrix)(self, out_x, out_y, dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix, src_x, src_y, src_size_x, src_size_y, src_matrix)

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
INTDEF ATTR_IN(1) video_color_t CC libvideo_swgfx_generic__getcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_swgfx_generic__getcolor_blur(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_swgfx_generic__getcolor_with_key(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__putcolor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__putcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__putcolor_alpha_factor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
#define DECLARE_libvideo_swgfx_generic__putcolor_FOO(name, mode) \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__putcolor_##name(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
GFX_FOREACH_DEDICATED_BLENDMODE(DECLARE_libvideo_swgfx_generic__putcolor_FOO)
GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(DECLARE_libvideo_swgfx_generic__putcolor_FOO)
#undef DECLARE_libvideo_swgfx_generic__putcolor_FOO

/* Low-level, Generic, always-valid GFX functions (using only `vgfo_getcolor' + `vgfo_putcolor') */
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__absline_llhh(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__absline_lhhl(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__absline_llhh_l(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__absline_lhhl_l(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__absline_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__absline_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__absfill(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_swgfx_generic__absgradient(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__absgradient_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_generic__absgradient_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC libvideo_swgfx_generic__fillmask(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_swgfx_generic__fillstretchmask_l(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_swgfx_generic__fillstretchmask_n(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);

/* Custom pre-blending GFX functions */
#define DECLARE_libvideo_swgfx_generic__render_preblend_FOO(name, mode, preblend_name, preblend)                                                                                                                                                                                                                                                                           \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__absline_llhh__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);                                                                                                                                               \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__absline_lhhl__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);                                                                                                                                               \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__absline_llhh_l__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);                                                                                                                                             \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__absline_lhhl_l__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);                                                                                                                                             \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__absline_h__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);                                                                                                                                                                      \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__absline_v__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);                                                                                                                                                                      \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__absfill__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);                                                                                                                                                    \
	INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_swgfx_preblend__absgradient__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);                                                                                                                        \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__absgradient_h__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);                                                                                                                     \
	INTDEF ATTR_IN(1) void CC libvideo_swgfx_preblend__absgradient_v__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);                                                                                                                     \
	INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC libvideo_swgfx_preblend__fillmask__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);                                                                  \
	INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_swgfx_preblend__fillstretchmask_l__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm); \
	INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_swgfx_preblend__fillstretchmask_n__##name(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
GFX_FOREACH_DEDICATED_PREBLENDMODE(DECLARE_libvideo_swgfx_generic__render_preblend_FOO)
#undef DECLARE_libvideo_swgfx_generic__render_preblend_FOO

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


/* Low-level, optimized GFX functions using `struct video_lock' (if available):
 * - *noblend*: Usable only when the relevant GFX's blend-mode is `GFX_BLENDMODE_OVERRIDE' */
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend__absline_llhh(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend__absline_lhhl(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend__absline_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend__absline_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend__absfill(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_swgfx_noblend_interp8888__absgradient(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend_interp8888__absgradient_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_swgfx_noblend_interp8888__absgradient_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) ATTR_IN(7) void CC libvideo_swgfx_noblend__fillmask1(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color, struct video_bitmask const *__restrict bm, __REGISTER_TYPE__ bm_xor);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC libvideo_swgfx_noblend__fillmask(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_swgfx_noblend__fillstretchmask_n(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(9) void CC libvideo_swgfx_noblend__fillstretchmask1_n(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t color, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm, __REGISTER_TYPE__ bm_xor);

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

/* The *_difffmt_* operators here "libvideo_swblitter_generic__conv" to be initialized */
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__stretch_imatrix_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt_interp8888__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt_interp8888__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);







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
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC libvideo_swgfx_fillmask(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC libvideo_swgfx_fillmask_wrap(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC libvideo_swgfx_fillmask_byblit(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_swgfx_fillstretchmask(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_swgfx_fillstretchmask_wrap(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_swgfx_fillstretchmask_byblit(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
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
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) video_color_t BLT3_SWDRV_BLEND_CC libvideo_swblitter3__blend(struct video_blitter3 const *__restrict self, video_color_t dst, video_color_t src);
#define DECLARE_libvideo_swblitter3__blend_FOO(name, mode) \
	INTDEF ATTR_CONST WUNUSED ATTR_IN(1) video_color_t BLT3_SWDRV_BLEND_CC libvideo_swblitter3__blend_##name(struct video_blitter3 const *__restrict self, video_color_t dst, video_color_t src);
GFX_FOREACH_DEDICATED_BLENDMODE(DECLARE_libvideo_swblitter3__blend_FOO)
#undef DECLARE_libvideo_swblitter3__blend_FOO
#define DECLARE_libvideo_swblitter3__blend_FOO(name, mode) \
	INTDEF ATTR_PURE WUNUSED ATTR_IN(1) video_color_t BLT3_SWDRV_BLEND_CC libvideo_swblitter3__blend_##name(struct video_blitter3 const *__restrict self, video_color_t dst, video_color_t src);
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
libvideo_swgfx_ops_of(gfx_flag_t flags) {
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
	 * - vx_hdr.vxh_ops */
	if (what & VIDEO_GFX_UPDATE_FLAGS) {
		/* Select generic operators based on wrapping rules */
		self->vx_hdr.vxh_ops = libvideo_swgfx_ops_of(self->vx_flags);
	}

	/* Update:
	 * - drv->xsw_getcolor */
	if (what & (VIDEO_GFX_UPDATE_FLAGS | VIDEO_GFX_UPDATE_COLORKEY)) {
		/* Select how colors should be read. */
		if (self->vx_flags & VIDEO_GFX_F_BLUR) {
			drv->xsw_getcolor = &libvideo_swgfx_generic__getcolor_blur;
		} else if (!VIDEO_COLOR_ISTRANSPARENT(self->vx_colorkey)) {
			drv->xsw_getcolor = &libvideo_swgfx_generic__getcolor_with_key;
		} else if (self->vx_buffer->vb_format.vf_codec->vc_codec == VIDEO_CODEC_RGBA8888) {
			/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
			drv->xsw_getcolor = drv->xsw_getpixel;
		} else {
			drv->xsw_getcolor = &libvideo_swgfx_generic__getcolor_noblend;
		}
	}

	/* Update:
	 * - vx_hdr.vxh_blitfrom
	 * - drv->xsw_putcolor
	 * - drv->xsw_absline_h
	 * - drv->xsw_absline_v
	 * - drv->xsw_absfill
	 * - drv->xsw_absfillmask
	 * - drv->xsw_absgradient
	 * - drv->xsw_absgradient_h
	 * - drv->xsw_absgradient_v */
	if (what & VIDEO_GFX_UPDATE_BLEND) {
		(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_OVERRIDE);
		(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_ALPHA);

		/* Detect special blend modes. */
		switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
		default:
			if (!(GFX_BLENDMODE_GET_SRCRGB(self->vx_blend) == GFX_BLENDDATA_ONE &&
			      GFX_BLENDMODE_GET_SRCA(self->vx_blend) == GFX_BLENDDATA_ONE &&
			      GFX_BLENDMODE_GET_DSTRGB(self->vx_blend) == GFX_BLENDDATA_ZERO &&
			      GFX_BLENDMODE_GET_DSTA(self->vx_blend) == GFX_BLENDDATA_ZERO &&
			      _blendinfo__is_add_or_subtract_or_max(GFX_BLENDMODE_GET_FUNRGB(self->vx_blend)) &&
			      _blendinfo__is_add_or_subtract_or_max(GFX_BLENDMODE_GET_FUNA(self->vx_blend)))) {
				/* Actual, custom blending */
				drv->xsw_putcolor = &libvideo_swgfx_generic__putcolor;
				break;
			}
			self->vx_blend = GFX_BLENDMODE_OVERRIDE; /* It essentially behaves the same, so... */
			ATTR_FALLTHROUGH
		case GFX_BLENDMODE_OVERRIDE:
			/* No blending is being done -> link operators that try to make use of direct memory access. */

			/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
			if (self->vx_buffer->vb_format.vf_codec->vc_codec == VIDEO_CODEC_RGBA8888) {
				drv->xsw_putcolor = drv->xsw_setpixel;
			} else {
				drv->xsw_putcolor = &libvideo_swgfx_generic__putcolor_noblend;
			}
			drv->xsw_putcolor_p  = drv->xsw_putcolor;
			drv->xsw_absline_h   = &libvideo_swgfx_noblend__absline_h;
			drv->xsw_absline_v   = &libvideo_swgfx_noblend__absline_v;
			drv->xsw_absfill     = &libvideo_swgfx_noblend__absfill;
			drv->xsw_absfillmask = &libvideo_swgfx_noblend__fillmask;
			if (self->vx_buffer->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) {
				drv->xsw_absgradient   = &libvideo_swgfx_noblend_interp8888__absgradient;
				drv->xsw_absgradient_h = &libvideo_swgfx_noblend_interp8888__absgradient_h;
				drv->xsw_absgradient_v = &libvideo_swgfx_noblend_interp8888__absgradient_v;
			} else {
				drv->xsw_absgradient   = &libvideo_swgfx_generic__absgradient;
				drv->xsw_absgradient_h = &libvideo_swgfx_generic__absgradient_h;
				drv->xsw_absgradient_v = &libvideo_swgfx_generic__absgradient_v;
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
		switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
#define LINK_libvideo_swgfx_generic__render_preblend_FOO(name, mode, preblend_name, preblend) \
		case mode:                                                                            \
			drv->xsw_putcolor_p    = &libvideo_swgfx_generic__putcolor_##preblend_name;       \
			drv->xsw_absline_h     = &libvideo_swgfx_preblend__absline_h__##name;             \
			drv->xsw_absline_v     = &libvideo_swgfx_preblend__absline_v__##name;             \
			drv->xsw_absfill       = &libvideo_swgfx_preblend__absfill__##name;               \
			drv->xsw_absfillmask   = &libvideo_swgfx_preblend__fillmask__##name;              \
			drv->xsw_absgradient   = &libvideo_swgfx_preblend__absgradient__##name;           \
			drv->xsw_absgradient_h = &libvideo_swgfx_preblend__absgradient_h__##name;         \
			drv->xsw_absgradient_v = &libvideo_swgfx_preblend__absgradient_v__##name;         \
			break;
GFX_FOREACH_DEDICATED_PREBLENDMODE(LINK_libvideo_swgfx_generic__render_preblend_FOO)
#undef LINK_libvideo_swgfx_generic__render_preblend_FOO
		default:
			drv->xsw_putcolor_p    = drv->xsw_putcolor;
			drv->xsw_absline_h     = &libvideo_swgfx_generic__absline_h;
			drv->xsw_absline_v     = &libvideo_swgfx_generic__absline_v;
			drv->xsw_absfill       = &libvideo_swgfx_generic__absfill;
			drv->xsw_absfillmask   = &libvideo_swgfx_generic__fillmask;
			drv->xsw_absgradient   = &libvideo_swgfx_generic__absgradient;
			drv->xsw_absgradient_h = &libvideo_swgfx_generic__absgradient_h;
			drv->xsw_absgradient_v = &libvideo_swgfx_generic__absgradient_v;
			break;
		}
after_blend:;
	}

	/* Update:
	 * - drv->xsw_absfillstretchmask
	 * - drv->xsw_absline_llhh
	 * - drv->xsw_absline_lhhl */
	if (what & (VIDEO_GFX_UPDATE_FLAGS | VIDEO_GFX_UPDATE_BLEND)) {
		/* Select based on linear vs. Nearest interpolation, and blending */
		switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
		case GFX_BLENDMODE_OVERRIDE:
			if (self->vx_flags & VIDEO_GFX_F_LINEAR)
				goto set_generic_linear_blend_operators;
			drv->xsw_absfillstretchmask = &libvideo_swgfx_noblend__fillstretchmask_n;
			drv->xsw_absline_llhh       = &libvideo_swgfx_noblend__absline_llhh;
			drv->xsw_absline_lhhl       = &libvideo_swgfx_noblend__absline_lhhl;
			break;
#define LINK_libvideo_swgfx_generic__render_preblend_FOO(name, mode, preblend_name, preblend)  \
		case mode:                                                                             \
			drv->xsw_absfillstretchmask = &libvideo_swgfx_preblend__fillstretchmask_n__##name; \
			drv->xsw_absline_llhh       = &libvideo_swgfx_preblend__absline_llhh__##name;      \
			drv->xsw_absline_lhhl       = &libvideo_swgfx_preblend__absline_lhhl__##name;      \
			break;
GFX_FOREACH_DEDICATED_PREBLENDMODE(LINK_libvideo_swgfx_generic__render_preblend_FOO)
#undef LINK_libvideo_swgfx_generic__render_preblend_FOO
		default:
			if (self->vx_flags & VIDEO_GFX_F_LINEAR) {
set_generic_linear_blend_operators:
				drv->xsw_absfillstretchmask = &libvideo_swgfx_generic__fillstretchmask_l;
				drv->xsw_absline_llhh       = &libvideo_swgfx_generic__absline_llhh_l;
				drv->xsw_absline_lhhl       = &libvideo_swgfx_generic__absline_lhhl_l;
				break;
			}
			drv->xsw_absfillstretchmask = &libvideo_swgfx_generic__fillstretchmask_n;
			drv->xsw_absline_llhh       = &libvideo_swgfx_generic__absline_llhh;
			drv->xsw_absline_lhhl       = &libvideo_swgfx_generic__absline_lhhl;
			break;
		}
	}
}

/* libvideo_swgfx_populate: fill   in    all
 * operators (except the get/set pixel) ones
 * with generic impls.
 *
 * The caller must have already initialized:
 * - video_swgfx_getdrv(self)->xsw_getpixel
 * - video_swgfx_getdrv(self)->xsw_setpixel
 * - self->vx_flags     (if in "vi_initgfx", already done by *your* caller)
 * - self->vx_colorkey  (if in "vi_initgfx", already done by *your* caller)
 * - self->vx_blend     (if in "vi_initgfx", already done by *your* caller)
 * - self->vx_buffer    (if in "vi_initgfx", already done by *your* caller) */
LOCAL ATTR_INOUT(1) void CC
libvideo_swgfx_populate(struct video_gfx *__restrict self) {
	libvideo_swgfx_update(self, VIDEO_GFX_UPDATE_ALL);
}


/* Select appropriate operators for a video blit operations */
LOCAL ATTR_INOUT(1) void CC
video_swblitter_setops(struct video_blitter *__restrict ctx) {
	/* Select operators based on wrapping flags of src/dst */
	gfx_flag_t flags = ctx->vbt_dst->vx_flags | ctx->vbt_src->vx_flags;
	if (ctx->vbt_dst->vx_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
		ctx->vbt_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
		               ? &libvideo_swblitter_ops_wrap_imatrix
		               : &libvideo_swblitter_ops_wrap;
	} else if (ctx->vbt_src->vx_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
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
	gfx_flag_t flags = ctx->vbt3_rddst->vx_flags |
	                   ctx->vbt3_wrdst->vx_flags |
	                   ctx->vbt3_src->vx_flags;
	if (ctx->vbt3_rddst->vx_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
		if (ctx->vbt3_wrdst->vx_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
			ctx->vbt3_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
			                ? &libvideo_swblitter3_ops_wrap1_imatrix
			                : &libvideo_swblitter3_ops_wrap1;
		} else {
			ctx->vbt3_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
			                ? &libvideo_swblitter3_ops_rdwrap1_imatrix
			                : &libvideo_swblitter3_ops_rdwrap1;
		}
	} else if (ctx->vbt3_wrdst->vx_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
		ctx->vbt3_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
		                ? &libvideo_swblitter3_ops_wrap_imatrix
		                : &libvideo_swblitter3_ops_wrap;
	} else if (ctx->vbt3_src->vx_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
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
