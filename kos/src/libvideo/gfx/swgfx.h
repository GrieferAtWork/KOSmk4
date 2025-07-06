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
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

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
	__ATTR_IN_T(1) video_color_t
	(LIBVIDEO_GFX_CC *xsw_getcolor)(struct video_gfx const *__restrict __self,
	                                video_coord_t __abs_x, video_coord_t __abs_y);

	/* Place a colored pixel ontop of the graphic (whilst also performing blending) */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsw_putcolor)(struct video_gfx const *__restrict __self,
	                                video_coord_t __abs_x, video_coord_t __abs_y,
	                                video_color_t __color);

	/* Get the raw data of a pixel (no blending is done) */
	__ATTR_IN_T(1) video_pixel_t
	(LIBVIDEO_GFX_CC *xsw_getpixel)(struct video_gfx const *__restrict __self,
	                                video_coord_t __abs_x, video_coord_t __abs_y);

	/* Set the raw data of a pixel (no blending is done) */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsw_setpixel)(struct video_gfx const *__restrict __self,
	                                video_coord_t __abs_x, video_coord_t __abs_y,
	                                video_pixel_t __pixel);

	/* Diagonal line from top-left -> bottom-right
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) void /* TODO: Some way to specify the line width */
	(LIBVIDEO_GFX_CC *xsw_absline_llhh)(struct video_gfx const *__restrict __self,
	                                    video_coord_t __x, video_coord_t y,
	                                    video_dim_t __size_x, video_dim_t __size_y,
	                                    video_color_t __color);

	/* Diagonal line from bottom-left -> top-right
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) void /* TODO: Some way to specify the line width */
	(LIBVIDEO_GFX_CC *xsw_absline_lhhl)(struct video_gfx const *__restrict __self,
	                                    video_coord_t __x, video_coord_t __y,
	                                    video_dim_t __size_x, video_dim_t __size_y,
	                                    video_color_t __color);

	/* Horizontal line
	 * @assume(__length > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsw_absline_h)(struct video_gfx const *__restrict __self,
	                                 video_coord_t __x, video_coord_t __y,
		                             video_dim_t __length, video_color_t __color);

	/* Vertical line
	 * @assume(__length > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsw_absline_v)(struct video_gfx const *__restrict __self,
		                             video_coord_t __x, video_coord_t __y,
		                             video_dim_t __length, video_color_t __color);

	/* TODO: Curve drawing (Bézier curve) */

	/* Rect fill
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsw_absfill)(struct video_gfx const *__restrict __self,
	                               video_coord_t __x, video_coord_t __y,
	                               video_dim_t __size_x, video_dim_t __size_y,
	                               video_color_t __color);

	/* Paint masked pixels
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) __ATTR_IN_T(6) __ATTR_IN_T(7) void
	(LIBVIDEO_GFX_CC *xsw_absfillmask)(struct video_gfx const *__restrict __self,
	                                   video_coord_t __dst_x, video_coord_t __dst_y,
	                                   video_dim_t __size_x, video_dim_t __size_y,
	                                   video_color_t const __bg_fg_colors[2],
	                                   struct video_bitmask const *__restrict __bm);

	/* Stretch and paint masked pixels
	 * @assume(__dst_size_x > 0);
	 * @assume(__dst_size_y > 0);
	 * @assume(__src_size_x > 0);
	 * @assume(__src_size_y > 0);
	 * @assume(__dst_size_x != __src_size_x);
	 * @assume(__dst_size_y != __src_size_y); */
	__ATTR_IN_T(1) __ATTR_IN_T(6) __ATTR_IN_T(9) void
	(LIBVIDEO_GFX_CC *xsw_absfillstretchmask)(struct video_gfx const *__restrict __self,
	                                          video_coord_t __dst_x, video_coord_t __dst_y,
	                                          video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                          video_color_t const __bg_fg_colors[2],
	                                          video_dim_t __src_size_x, video_dim_t __src_size_y,
	                                          struct video_bitmask const *__restrict __bm);

	/* Same as `xsw_absfill', but do so via gradient with colors[y][x] being used
	 * to essentially  do a  VIDEO_GFX_F_LINEAR stretch-blit  into the  specified
	 * destination rect.
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) __ATTR_IN_T(6) void
	(LIBVIDEO_GFX_CC *xsw_absgradient)(struct video_gfx const *__restrict __self,
	                                   video_coord_t __x, video_coord_t __y,
	                                   video_dim_t __size_x, video_dim_t __size_y,
	                                   video_color_t const __colors[2][2]);
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsw_absgradient_h)(struct video_gfx const *__restrict __self,
	                                     video_coord_t __x, video_coord_t __y,
	                                     video_dim_t __size_x, video_dim_t __size_y,
	                                     video_color_t __locolor, video_color_t __hicolor);
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsw_absgradient_v)(struct video_gfx const *__restrict __self,
	                                     video_coord_t __x, video_coord_t __y,
	                                     video_dim_t __size_x, video_dim_t __size_y,
	                                     video_color_t __locolor, video_color_t __hicolor);
};

#define video_swgfx_getdrv(self) \
	((struct gfx_swdrv *)(self)->_vx_driver)

/* Video GFX internal API wrappers */
#define _video_swgfx_x_getcolor(self, x, y) \
	(*video_swgfx_getdrv(self)->xsw_getcolor)(self, x, y)
#define _video_swgfx_x_putcolor(self, x, y, color) \
	(*video_swgfx_getdrv(self)->xsw_putcolor)(self, x, y, color)
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



struct blt_swdrv {
	/* All of the following callbacks are [1..1][const]
	 * NOTES:
	 * - Don't use these operators; only use `struct video_gfx_ops'
	 * - All these operators take pre-clamped/rotated/mirrored/etc. coords */

	/* Blit the contents of another video buffer into this one.
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *bsw_blit)(struct video_blitter const *__restrict __self,
	                            video_coord_t __dst_x, video_coord_t __dst_y,
	                            video_coord_t __src_x, video_coord_t __src_y,
	                            video_dim_t __size_x, video_dim_t __size_y);

	/* Same as `bsw_blit', but stretch the contents
	 * @assume(__dst_size_x > 0);
	 * @assume(__dst_size_y > 0);
	 * @assume(__src_size_x > 0);
	 * @assume(__src_size_y > 0);
	 * @assume(__dst_size_x != __src_size_x);
	 * @assume(__dst_size_y != __src_size_y); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *bsw_stretch)(struct video_blitter const *__restrict __self,
	                               video_coord_t __dst_x, video_coord_t __dst_y,
	                               video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                               video_coord_t __src_x, video_coord_t __src_y,
	                               video_dim_t __src_size_x, video_dim_t __src_size_y);

	/* Same as "bsw_blit", but uses a matrix to calculate source pixel locations:
	 * >> for (video_coord_t y = 0; y < __size_y; ++y) {
	 * >>     for (video_coord_t x = 0; x < __size_x; ++x) {
	 * >>         video_coord_t used_src_x = __src_x + __src_matrix[0][0] * x + __src_matrix[0][1] * y;
	 * >>         video_coord_t used_src_y = __src_y + __src_matrix[1][0] * x + __src_matrix[1][1] * y;
	 * >>         video_coord_t used_dst_x = __dst_x + x;
	 * >>         video_coord_t used_dst_y = __dst_y + y;
	 * >>         video_color_t color = (*__self->vbt_src->_vx_xops.xsw_getcolor)(__self->vbt_src, used_src_x, used_src_y);
	 * >>         (*__self->vbt_dst->_vx_xops.xsw_putcolor)(__self->vbt_dst, used_dst_x, used_dst_y, color);
	 * >>     }
	 * >> }
	 *
	 * The given "__src_matrix" is assumed to only contain values -1, 0 or 1,
	 * meaning  it can only be used to do 90° rotation, as well as mirroring.
	 *
	 * When values outside this range are used, results are undefined. */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *bsw_blit_imatrix)(struct video_blitter const *__restrict __self,
	                                    video_coord_t __dst_x, video_coord_t __dst_y,
	                                    video_coord_t __src_x, video_coord_t __src_y,
	                                    video_dim_t __size_x, video_dim_t __size_y,
	                                    video_imatrix2d_t __src_matrix);

	/* Same as "bsw_stretch", but uses a matrix to calculate source pixel locations. */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *bsw_stretch_imatrix)(struct video_blitter const *__restrict __self,
	                                       video_coord_t __dst_x, video_coord_t __dst_y,
	                                       video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                       video_coord_t __src_x, video_coord_t __src_y,
	                                       video_dim_t __src_size_x, video_dim_t __src_size_y,
	                                       video_imatrix2d_t __src_matrix);

	/* Video format converter (used for quickly converting pixel formats under noblend)
	 * [valid_if(bsw_blit            == &libvideo_swblitter_noblend_difffmt__blit ||
	 *           bsw_stretch         == &libvideo_swblitter_noblend_difffmt__stretch_l ||
	 *           bsw_stretch         == &libvideo_swblitter_noblend_difffmt__stretch_n ||
	 *           bsw_blit_imatrix    == &libvideo_swblitter_noblend_difffmt__blit_imatrix ||
	 *           bsw_stretch_imatrix == &libvideo_swblitter_noblend_difffmt__stretch_imatrix_l ||
	 *           bsw_stretch_imatrix == &libvideo_swblitter_noblend_difffmt__stretch_imatrix_n)] */
	struct video_converter bsw_conv;
};

#define video_swblitter_getdrv(self) \
	((struct blt_swdrv *)(self)->_vbt_driver)
#define libvideo_swblitter_generic__conv(self) \
	(&video_swblitter_getdrv(self)->bsw_conv)



/* Video BLIT internal API wrappers */
#define _video_swblitter_x_blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y) \
	(*video_swblitter_getdrv(self)->bsw_blit)(self, dst_x, dst_y, src_x, src_y, size_x, size_y)
#define _video_swblitter_x_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y) \
	(*video_swblitter_getdrv(self)->bsw_stretch)(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y)
#define _video_swblitter_x_blit_imatrix(self, dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix) \
	(*video_swblitter_getdrv(self)->bsw_blit_imatrix)(self, dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix)
#define _video_swblitter_x_stretch_imatrix(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, src_matrix) \
	(*video_swblitter_getdrv(self)->bsw_stretch_imatrix)(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, src_matrix)

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




/************************************************************************/
/************************************************************************/
/************************************************************************/
/* GENERIC, LOW-LEVEL                                                   */
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
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samebuf__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
#define libvideo_swblitter_noblend_samefmt__stretch_l         libvideo_swblitter_generic__stretch_l
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samebuf__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_samefmt__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
#define libvideo_swblitter_noblend_samefmt__stretch_imatrix_n libvideo_swblitter_generic__stretch_imatrix_n
#define libvideo_swblitter_noblend_samefmt__stretch_imatrix_l libvideo_swblitter_generic__stretch_imatrix_l

/* The *_difffmt_* operators here "libvideo_swblitter_generic__conv" to be initialized */
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_swblitter_noblend_difffmt__stretch_imatrix_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t src_matrix);
#define libvideo_swblitter_noblend_difffmt__stretch_l         libvideo_swblitter_generic__stretch_l
#define libvideo_swblitter_noblend_difffmt__stretch_imatrix_l libvideo_swblitter_generic__stretch_imatrix_l







/************************************************************************/
/************************************************************************/
/************************************************************************/
/* GENERIC, HIGH-LEVEL                                                  */
/************************************************************************/
/************************************************************************/
/************************************************************************/

/* Generic GFX operators */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC libvideo_swgfx_blitfrom(struct video_blitter *__restrict ctx);
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
INTDEF ATTR_IN(1) ATTR_IN(4) void CC libvideo_swgfx_bitblit(struct video_gfx const *__restrict dst, video_offset_t dst_x, video_offset_t dst_y, struct video_gfx const *__restrict src, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_swgfx_stretch(struct video_gfx const *__restrict dst, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, struct video_gfx const *__restrict src, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
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






/* Apply a clipping  rect to "self",  shrinking the  pixel
 * area relative to offsets specified by the given coords.
 *
 * Note that the clip area can  only ever be shrunk. To  go
 * back to the initial clip area, either keep a copy of the
 * original GFX  context, or  create a  new context  (which
 * always starts  out with  its clipping  area set  to  the
 * associated buffer's entire surface)
 *
 * @param: clip_x: Delta to add to the Clip Rect starting X coord.
 *                 When negative, extend clip rect with void-pixels to the left
 * @param: clip_y: Delta to add to the Clip Rect starting Y coord.
 *                 When negative, extend clip rect with void-pixels to the top
 * @param: size_x: New width of the clip rect. When greater than the old  clip
 *                 rect width, extend clip rect with void-pixels to the right.
 * @param: size_y: New height of the clip rect.  When greater than the old  clip
 *                 rect height, extend clip rect with void-pixels to the bottom.
 * @return: * : Always re-returns `self' */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *CC
libvideo_gfx_clip(struct video_gfx *__restrict self,
                  video_offset_t clip_x, video_offset_t clip_y,
                  video_dim_t size_x, video_dim_t size_y);

/* Called after the Clip- or I/O-Rect of `self' was updated
 * (caller must ensure  that I/O rect  is still  non-empty) */
#define _libvideo_gfx_clip_updated(self) (void)0

/* Translate virtual (offset) pixel coords to physical (coord) coords.
 * @param: x:      Virtual pixel X offset
 * @param: y:      Virtual pixel Y offset
 * @param: coords: The absolute (physical) coords of the pixel are stored here
 * @return: true:  Translation was successful
 * @return: false: The given x/y lie outside the I/O Rect of `self' */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC
libvideo_gfx_offset2coord(struct video_gfx const *__restrict self,
                          video_offset_t x, video_offset_t y,
                          video_coord_t coords[2]);

/* Translate physical (coord) pixel coords to virtual (offset) coords.
 * @param: x:       Physical pixel X coord
 * @param: y:       Physical pixel Y coord
 * @param: offsets: The offset (virtual) coords of the pixel are stored here
 * @return: true:  Translation was successful
 * @return: false: The given x/y lie outside the I/O Rect of `self' */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC
libvideo_gfx_coord2offset(struct video_gfx const *__restrict self,
                          video_coord_t x, video_coord_t y,
                          video_offset_t offsets[2]);


/* Perform geometric transformations on the contents of the current  clip
 * rect of `self'. Note that none of these functions alter pixel data  of
 * the underlying buffer; they only affect how the given `self' interacts
 * with pixel data of the underlying buffer.
 *
 * - video_gfx_xyswap:  Swap x/y coords (mirror pixel data along a diagonal starting in the top-left)
 * - video_gfx_hmirror: Mirror pixel data horizontally
 * - video_gfx_vmirror: Mirror pixel data vertically
 * - video_gfx_lrot90:  Rotate pixel data left 90°
 * - video_gfx_rrot90:  Rotate pixel data right 90°
 * - video_gfx_rot180:  Rotate pixel data 180°
 * - video_gfx_nrot90n: Rotate pixel data by left by 90*n°
 * - video_gfx_rrot90n: Rotate pixel data by right by 90*n° */
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_xyswap(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_hmirror(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_vmirror(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_lrot90(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_rrot90(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_rot180(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_lrot90n(struct video_gfx *__restrict self, int n);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_rrot90n(struct video_gfx *__restrict self, int n);



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

#define LINK_libvideo_swgfx_generic__putcolor_FOO(name, mode)                        \
		case mode:                                                                 \
			drv->xsw_putcolor = &libvideo_swgfx_generic__putcolor_##name; \
			break;
		GFX_FOREACH_DEDICATED_BLENDMODE(LINK_libvideo_swgfx_generic__putcolor_FOO)
		GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(LINK_libvideo_swgfx_generic__putcolor_FOO)
#undef LINK_libvideo_swgfx_generic__putcolor_FOO
		}
		/* Generic GFX operators that **do** have support for blending */
		drv->xsw_absline_h     = &libvideo_swgfx_generic__absline_h;
		drv->xsw_absline_v     = &libvideo_swgfx_generic__absline_v;
		drv->xsw_absfill       = &libvideo_swgfx_generic__absfill;
		drv->xsw_absfillmask   = &libvideo_swgfx_generic__fillmask;
		drv->xsw_absgradient   = &libvideo_swgfx_generic__absgradient;
		drv->xsw_absgradient_h = &libvideo_swgfx_generic__absgradient_h;
		drv->xsw_absgradient_v = &libvideo_swgfx_generic__absgradient_v;
after_blend:;
	}

	/* Update:
	 * - drv->xsw_absfillstretchmask
	 * - drv->xsw_absline_llhh
	 * - drv->xsw_absline_lhhl */
	if (what & (VIDEO_GFX_UPDATE_FLAGS | VIDEO_GFX_UPDATE_BLEND)) {
		/* Select based on linear vs. Nearest interpolation, and blending */
		if (GFX_BLENDMODE_GET_MODE(self->vx_blend) == GFX_BLENDMODE_OVERRIDE) {
			if (!(self->vx_flags & VIDEO_GFX_F_LINEAR)) {
				drv->xsw_absfillstretchmask = &libvideo_swgfx_noblend__fillstretchmask_n;
				drv->xsw_absline_llhh       = &libvideo_swgfx_generic__absline_llhh_l;
				drv->xsw_absline_lhhl       = &libvideo_swgfx_generic__absline_lhhl_l;
			} else {
				drv->xsw_absfillstretchmask = &libvideo_swgfx_generic__fillstretchmask_l;
				drv->xsw_absline_llhh       = &libvideo_swgfx_noblend__absline_llhh;
				drv->xsw_absline_lhhl       = &libvideo_swgfx_noblend__absline_lhhl;
			}
		} else {
			if (self->vx_flags & VIDEO_GFX_F_LINEAR) {
				drv->xsw_absfillstretchmask = &libvideo_swgfx_generic__fillstretchmask_l;
				drv->xsw_absline_llhh       = &libvideo_swgfx_generic__absline_llhh_l;
				drv->xsw_absline_lhhl       = &libvideo_swgfx_generic__absline_lhhl_l;
			} else {
				drv->xsw_absfillstretchmask = &libvideo_swgfx_generic__fillstretchmask_n;
				drv->xsw_absline_llhh       = &libvideo_swgfx_generic__absline_llhh;
				drv->xsw_absline_lhhl       = &libvideo_swgfx_generic__absline_lhhl;
			}
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
	/* Line/fill operators... */
	libvideo_swgfx_update(self, VIDEO_GFX_UPDATE_ALL);
}

/* Same as `libvideo_swgfx_populate()', but load non-blending defaults */
LOCAL ATTR_INOUT(1) void CC
libvideo_swgfx_populate_noblend(struct video_gfx *__restrict self) {
	struct gfx_swdrv *drv = video_swgfx_getdrv(self);
	if (drv->xsw_getcolor != drv->xsw_getpixel)
		drv->xsw_getcolor = &libvideo_swgfx_generic__getcolor_noblend;
	if (drv->xsw_putcolor != drv->xsw_setpixel)
		drv->xsw_putcolor = &libvideo_swgfx_generic__putcolor_noblend;
	drv->xsw_absline_h   = &libvideo_swgfx_noblend__absline_h;
	drv->xsw_absline_v   = &libvideo_swgfx_noblend__absline_v;
	drv->xsw_absfill     = &libvideo_swgfx_noblend__absfill;
	drv->xsw_absfillmask = &libvideo_swgfx_noblend__fillmask;
	if (self->vx_buffer->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) {
		drv->xsw_absgradient   = &libvideo_swgfx_noblend_interp8888__absgradient;
		drv->xsw_absgradient_h = &libvideo_swgfx_noblend_interp8888__absgradient_h;
		drv->xsw_absgradient_v = &libvideo_swgfx_noblend_interp8888__absgradient_v;
	}
	if (!(self->vx_flags & VIDEO_GFX_F_LINEAR)) {
		drv->xsw_absline_llhh       = &libvideo_swgfx_noblend__absline_llhh;
		drv->xsw_absline_lhhl       = &libvideo_swgfx_noblend__absline_lhhl;
		drv->xsw_absfillstretchmask = &libvideo_swgfx_noblend__fillstretchmask_n;
	}
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

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_H */
