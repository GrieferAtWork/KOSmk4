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
#ifndef _LIBVIDEO_GFX_GFX_SWGFX_H
#define _LIBVIDEO_GFX_GFX_SWGFX_H 1

#include "../api.h"
/**/

#ifdef LIBVIDEO_GFX_EXPOSE_INTERNALS
#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <libvideo/gfx/codec/converter.h>

#include "../../color.h"
#include "../../types.h"
#include "../blend.h"

#ifdef __CC__
__DECL_BEGIN

struct video_gfx;
struct video_blitter;
struct video_blitter3;

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

#define gfx_region_imatrix_getxmin(src_x, src_y, size_x, size_y, src_matrix) \
	_gfx_region_imatrix_getxmin(src_x, size_x, size_y, src_matrix)
__LOCAL __ATTR_CONST video_coord_t
_gfx_region_imatrix_getxmin(video_coord_t __src_x,
                            video_dim_t __size_x, video_dim_t __size_y,
                            video_imatrix2d_t __src_matrix) {
	video_coord_t __result = __src_x;
	if (video_imatrix2d_get(&__src_matrix, 0, 1) < 0)
		__result -= (__size_y - 1);
	if (video_imatrix2d_get(&__src_matrix, 0, 0) < 0)
		__result -= (__size_x - 1);
	return __result;
}

#define gfx_region_imatrix_getymin(src_x, src_y, size_x, size_y, src_matrix) \
	_gfx_region_imatrix_getymin(src_y, size_x, size_y, src_matrix)
__LOCAL __ATTR_CONST video_coord_t
_gfx_region_imatrix_getymin(video_coord_t __src_y,
                            video_dim_t __size_x, video_dim_t __size_y,
                            video_imatrix2d_t __src_matrix) {
	video_coord_t __result = __src_y;
	if (video_imatrix2d_get(&__src_matrix, 1, 1) < 0)
		__result -= (__size_y - 1);
	if (video_imatrix2d_get(&__src_matrix, 1, 0) < 0)
		__result -= (__size_x - 1);
	return __result;
}

__LOCAL __ATTR_CONST video_dim_t
gfx_region_imatrix_getxdim(video_dim_t __size_x, video_dim_t __size_y,
                           video_imatrix2d_t __src_matrix) {
	video_coord_t __result = 0;
	if (video_imatrix2d_get(&__src_matrix, 0, 0) != 0)
		__result += __size_x;
	if (video_imatrix2d_get(&__src_matrix, 0, 1) != 0)
		__result += __size_y;
	return __result;
}

__LOCAL __ATTR_CONST video_dim_t
gfx_region_imatrix_getydim(video_dim_t __size_x, video_dim_t __size_y,
                           video_imatrix2d_t __src_matrix) {
	video_coord_t __result = 0;
	if (video_imatrix2d_get(&__src_matrix, 1, 0) != 0)
		__result += __size_x;
	if (video_imatrix2d_get(&__src_matrix, 1, 1) != 0)
		__result += __size_y;
	return __result;
}







/************************************************************************/
/* SW-BLITTER                                                           */
/************************************************************************/

/* Structure stored in "struct video_blitter::_vbt_driver" */
struct blitter_swdrv {
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
	 * [valid_if(bsw_blit            == &libvideo_swblitter_noblend_difffmtblit ||
	 *           bsw_stretch         == &libvideo_swblitter_noblend_difffmtstretch_l ||
	 *           bsw_stretch         == &libvideo_swblitter_noblend_difffmtstretch_n ||
	 *           bsw_blit_imatrix    == &libvideo_swblitter_noblend_difffmtblit_imatrix ||
	 *           bsw_stretch_imatrix == &libvideo_swblitter_noblend_difffmtstretch_imatrix_l ||
	 *           bsw_stretch_imatrix == &libvideo_swblitter_noblend_difffmtstretch_imatrix_n)] */
	struct video_converter bsw_conv;
};

#define video_swblitter_getdrv(self) \
	((struct blitter_swdrv *)(self)->_vbt_driver)
#define video_swblitter_getcdrv(self) \
	((struct blitter_swdrv const *)(self)->_vbt_driver)
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







/************************************************************************/
/* SW-BLITTER3                                                          */
/************************************************************************/

#if defined(__i386__) && !defined(__x86_64__) && __has_attribute(__regparm__)
#define BLITTER3_SWDRV_BLEND_CC __attribute__((__regparm__(3)))
#else /* __has_attribute(__regparm__) */
#define BLITTER3_SWDRV_BLEND_CC LIBVIDEO_GFX_FCC
#endif /* !__has_attribute(__regparm__) */
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_IN_T(1) video_color_t
(BLITTER3_SWDRV_BLEND_CC *blitter3_blend_t)(struct video_blitter3 const *__restrict __self,
                                            video_color_t __dst, video_color_t __src);

/* Structure stored in "struct video_blitter3::_vbt3_driver" */
struct blitter3_swdrv {
	/* All of the following callbacks are [1..1][const]
	 * NOTES:
	 * - Don't use these operators; only use `struct video_gfx_ops'
	 * - All these operators take pre-clamped/rotated/mirrored/etc. coords */

	/* [== :vbt3_rddst->vg_blend] */
	gfx_blendmode_t bsw3_blendmode;

	/* Blend "__dst" and "__src" colors together and return the result.
	 * @param: __dst: color, as read from `__self->vbt3_dsc'
	 * @param: __src: color, as read from `__self->vbt3_src'
	 * @return: * : Fully-blended color */
	blitter3_blend_t bsw3_blend;

	/* Blit the contents of another video buffer into this one.
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *bsw3_blit)(struct video_blitter3 const *__restrict __self,
	                             video_coord_t __out_x, video_coord_t __out_y,
	                             video_coord_t __dst_x, video_coord_t __dst_y,
	                             video_coord_t __src_x, video_coord_t __src_y,
	                             video_dim_t __size_x, video_dim_t __size_y);

	/* Same as `bsw3_blit', but stretch the contents
	 * @assume(__dst_size_x > 0);
	 * @assume(__dst_size_y > 0);
	 * @assume(__src_size_x > 0);
	 * @assume(__src_size_y > 0);
	 * @assume(__dst_size_x != __src_size_x);
	 * @assume(__dst_size_y != __src_size_y); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *bsw3_stretch)(struct video_blitter3 const *__restrict __self,
	                                video_coord_t __out_x, video_coord_t __out_y,
	                                video_coord_t __dst_x, video_coord_t __dst_y,
	                                video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                video_coord_t __src_x, video_coord_t __src_y,
	                                video_dim_t __src_size_x, video_dim_t __src_size_y);

	/* s.a. `blitter_swdrv::bsw_blit_imatrix' */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *bsw3_blit_imatrix)(struct video_blitter3 const *__restrict __self,
	                                     video_coord_t __out_x, video_coord_t __out_y,
	                                     video_coord_t __dst_x, video_coord_t __dst_y,
	                                     video_imatrix2d_t __dst_matrix,
	                                     video_coord_t __src_x, video_coord_t __src_y,
	                                     video_dim_t __size_x, video_dim_t __size_y,
	                                     video_imatrix2d_t __src_matrix);

	/* s.a. `blitter_swdrv::bsw_stretch_imatrix' */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *bsw3_stretch_imatrix)(struct video_blitter3 const *__restrict __self,
	                                        video_coord_t __out_x, video_coord_t __out_y,
	                                        video_coord_t __dst_x, video_coord_t __dst_y,
	                                        video_dim_t __dst_size_x, video_dim_t __dst_size_y,
	                                        video_imatrix2d_t __dst_matrix,
	                                        video_coord_t __src_x, video_coord_t __src_y,
	                                        video_dim_t __src_size_x, video_dim_t __src_size_y,
	                                        video_imatrix2d_t __src_matrix);

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
	((struct blitter3_swdrv *)(self)->_vbt3_driver)
#define video_swblitter3_getcdrv(self) \
	((struct blitter3_swdrv const *)(self)->_vbt3_driver)
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







/************************************************************************/
/* SW-GFX                                                               */
/************************************************************************/

struct gfx_swdrv_shapeops {
	/* Diagonal line from top-left -> bottom-right
	 * LLHH -> Low Low High High
	 * XYXY    X   Y   X    Y
	 *         Start   End
	 * @param: __x/__y: Staring coord of the top-left pixel
	 * @param: __size_x/__size_y: The # of pixels to render diagonally
	           (the furthest pixel is at {__x+__size_x-1,__y+__size_y-1})
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) void /* TODO: Some way to specify the line width */
	(LIBVIDEO_GFX_CC *xsws_line_llhh)(struct video_gfx const *__restrict __self,
	                                  video_coord_t __x, video_coord_t __y,
	                                  video_dim_t __size_x, video_dim_t __size_y,
	                                  video_color_t __color);

	/* Diagonal line from bottom-left -> top-right
	 * LHLH -> Low High Low High
	 * XYXY    X   Y    X    Y
	 *         Start    End
	 * @param: __x/__y: Staring coord of the bottom-left pixel (relative to top-left)
	 * @param: __size_x/__size_y: The #  of pixels  to render  diagonally
	 *         (the furthest pixel is at {__x+__size_x-1,__y-__size_y+1})
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) void /* TODO: Some way to specify the line width */
	(LIBVIDEO_GFX_CC *xsws_line_lhhl)(struct video_gfx const *__restrict __self,
	                                  video_coord_t __x, video_coord_t __y,
	                                  video_dim_t __size_x, video_dim_t __size_y,
	                                  video_color_t __color);

	/* Horizontal line
	 * @assume(__length > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsws_line_h)(struct video_gfx const *__restrict __self,
	                               video_coord_t __x, video_coord_t __y,
	                               video_dim_t __length, video_color_t __color);

	/* Vertical line
	 * @assume(__length > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsws_line_v)(struct video_gfx const *__restrict __self,
	                               video_coord_t __x, video_coord_t __y,
	                               video_dim_t __length, video_color_t __color);

	/* TODO: Curve drawing (Bézier curve) */

	/* Rect fill
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsws_fill)(struct video_gfx const *__restrict __self,
	                             video_coord_t __x, video_coord_t __y,
	                             video_dim_t __size_x, video_dim_t __size_y,
	                             video_color_t __color);

	/* Same as `xsws_fill', but do  so via gradient with __colors[__y][__x]  being
	 * used to essentially do a VIDEO_GFX_F_LINEAR stretch-blit into the specified
	 * destination rect.
	 * @assume(__size_x > 0);
	 * @assume(__size_y > 0); */
	__ATTR_IN_T(1) __ATTR_IN_T(6) void
	(LIBVIDEO_GFX_CC *xsws_gradient)(struct video_gfx const *__restrict __self,
	                                 video_coord_t __x, video_coord_t __y,
	                                 video_dim_t __size_x, video_dim_t __size_y,
	                                 video_color_t const __colors[2][2]);
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsws_gradient_h)(struct video_gfx const *__restrict __self,
	                                   video_coord_t __x, video_coord_t __y,
	                                   video_dim_t __size_x, video_dim_t __size_y,
	                                   video_color_t __locolor, video_color_t __hicolor);
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsws_gradient_v)(struct video_gfx const *__restrict __self,
	                                   video_coord_t __x, video_coord_t __y,
	                                   video_dim_t __size_x, video_dim_t __size_y,
	                                   video_color_t __locolor, video_color_t __hicolor);
};

/* Structure stored in "struct video_gfx::_vg_driver" */
struct gfx_swdrv {
	/* All of the following callbacks are [1..1][const] */

	/* Get the color of a pixel */
	__ATTR_IN_T(1) video_color_t
	(LIBVIDEO_GFX_CC *xsw_getcolor)(struct video_gfx const *__restrict __self,
	                                video_coord_t __x, video_coord_t __y);

	/* Place a colored pixel ontop of the graphic (whilst also performing blending) */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsw_putcolor)(struct video_gfx const *__restrict __self,
	                                video_coord_t __x, video_coord_t __y,
	                                video_color_t __color);

	/* Same as `xsw_putcolor', but given color has been pre-blended for certain blend modes:
	 * - GFX_BLENDMODE_ALPHA:             as per `GFX_BLENDMODE_ALPHA_PREMULTIPLIED'
	 * - GFX_BLENDMODE_ALPHA_FACTOR(*):   as per `GFX_BLENDMODE_ALPHA_PREMULTIPLIED'
	 * - GFX_BLENDMODE_ALPHA_OVERRIDE(*): as per `GFX_BLENDMODE_ALPHA_PREMULTIPLIED'
	 * - GFX_BLENDMODE_ADD:               as per `GFX_BLENDMODE_ADD_PREMULTIPLIED'
	 * otherwise, identical to `xsw_putcolor' */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsw_putcolor_p)(struct video_gfx const *__restrict __self,
	                                  video_coord_t __x, video_coord_t __y,
	                                  video_color_t __preblended_color);

	/* Get the raw data of a pixel (no blending is done) */
	__ATTR_IN_T(1) video_pixel_t
	(LIBVIDEO_GFX_CC *xsw_getpixel)(struct video_gfx const *__restrict __self,
	                                video_coord_t __x, video_coord_t __y);

	/* Set the raw data of a pixel (no blending is done) */
	__ATTR_IN_T(1) void
	(LIBVIDEO_GFX_CC *xsw_setpixel)(struct video_gfx const *__restrict __self,
	                                video_coord_t __x, video_coord_t __y,
	                                video_pixel_t __pixel);

	/* [1..1] Shape rendering operators */
	struct gfx_swdrv_shapeops const *xsw_shape;
};

#define video_swgfx_getdrv(self)       ((struct gfx_swdrv *)(self)->_vg_driver)
#define video_swgfx_getcdrv(self)      ((struct gfx_swdrv const *)(self)->_vg_driver)
#define video_swgfx_getcdrvshape(self) video_swgfx_getcdrv(self)->xsw_shape

/* Video GFX internal API wrappers */
#define _video_swgfx_x_getcolor(self, x, y)                                     (*video_swgfx_getcdrv(self)->xsw_getcolor)(self, x, y)
#define _video_swgfx_x_putcolor(self, x, y, color)                              (*video_swgfx_getcdrv(self)->xsw_putcolor)(self, x, y, color)
#define _video_swgfx_x_putcolor_p(self, x, y, color)                            (*video_swgfx_getcdrv(self)->xsw_putcolor_p)(self, x, y, color)
#define _video_swgfx_x_getpixel(self, x, y)                                     (*video_swgfx_getcdrv(self)->xsw_getpixel)(self, x, y)
#define _video_swgfx_x_setpixel(self, x, y, pixel)                              (*video_swgfx_getcdrv(self)->xsw_setpixel)(self, x, y, pixel)
#define _video_swgfx_x_line_llhh(self, x, y, size_x, size_y, color)             (*video_swgfx_getcdrvshape(self)->xsws_line_llhh)(self, x, y, size_x, size_y, color)
#define _video_swgfx_x_line_lhhl(self, x, y, size_x, size_y, color)             (*video_swgfx_getcdrvshape(self)->xsws_line_lhhl)(self, x, y, size_x, size_y, color)
#define _video_swgfx_x_line_h(self, x, y, length, color)                        (*video_swgfx_getcdrvshape(self)->xsws_line_h)(self, x, y, length, color)
#define _video_swgfx_x_line_v(self, x, y, length, color)                        (*video_swgfx_getcdrvshape(self)->xsws_line_v)(self, x, y, length, color)
#define _video_swgfx_x_fill(self, x, y, size_x, size_y, color)                  (*video_swgfx_getcdrvshape(self)->xsws_fill)(self, x, y, size_x, size_y, color)
#define _video_swgfx_x_gradient(self, x, y, size_x, size_y, colors)             (*video_swgfx_getcdrvshape(self)->xsws_gradient)(self, x, y, size_x, size_y, colors)
#define _video_swgfx_x_gradient_h(self, x, y, size_x, size_y, locolor, hicolor) (*video_swgfx_getcdrvshape(self)->xsws_gradient_h)(self, x, y, size_x, size_y, locolor, hicolor)
#define _video_swgfx_x_gradient_v(self, x, y, size_x, size_y, locolor, hicolor) (*video_swgfx_getcdrvshape(self)->xsws_gradient_v)(self, x, y, size_x, size_y, locolor, hicolor)

#define _video_swgfx_x_getcolor_xyswap(self, x, y)                                     _video_swgfx_x_getcolor(self, y, x)
#define _video_swgfx_x_putcolor_xyswap(self, x, y, color)                              _video_swgfx_x_putcolor(self, y, x, color)
#define _video_swgfx_x_putcolor_p_xyswap(self, x, y, color)                            _video_swgfx_x_putcolor_p(self, y, x, color)
#define _video_swgfx_x_getpixel_xyswap(self, x, y)                                     _video_swgfx_x_getpixel(self, y, x)
#define _video_swgfx_x_setpixel_xyswap(self, x, y, pixel)                              _video_swgfx_x_setpixel(self, y, x, pixel)
#define _video_swgfx_x_line_llhh_xyswap(self, x, y, size_x, size_y, color)             _video_swgfx_x_line_llhh(self, y, x, size_y, size_x, color)
#define _video_swgfx_x_line_lhhl_xyswap(self, x, y, size_x, size_y, color)             _video_swgfx_x_line_lhhl(self, (y) - (size_y) + 1, (x) + (size_x) - 1, size_y, size_x, color)
#define _video_swgfx_x_line_h_xyswap(self, x, y, length, color)                        _video_swgfx_x_line_h(self, y, x, length, color)
#define _video_swgfx_x_line_v_xyswap(self, x, y, length, color)                        _video_swgfx_x_line_v(self, y, x, length, color)
#define _video_swgfx_x_fill_xyswap(self, x, y, size_x, size_y, color)                  _video_swgfx_x_fill(self, y, x, size_y, size_x, color)
#define _video_swgfx_x_gradient_xyswap(self, x, y, size_x, size_y, colors)             _video_swgfx_x_gradient(self, y, x, size_y, size_x, colors)
#define _video_swgfx_x_gradient_h_xyswap(self, x, y, size_x, size_y, locolor, hicolor) _video_swgfx_x_gradient_h(self, y, x, size_y, size_x, locolor, hicolor)
#define _video_swgfx_x_gradient_v_xyswap(self, x, y, size_x, size_y, locolor, hicolor) _video_swgfx_x_gradient_v(self, y, x, size_y, size_x, locolor, hicolor)


/* Populate/update generic SW-GFX operators of `__self'.
 * - `video_swgfx_populate(self)' is identical to `video_swgfx_update(__self, VIDEO_GFX_UPDATE_ALL)'
 * - Use `video_swgfx_populate()' to initialize SW-GFX operators from `vi_initgfx'
 * - `video_swgfx_populate()' will initialize *ALL* fields of `video_swgfx_getdrv(__self)',
 *   except   for   the  following,   which  have   to  be   initialized  by   the  caller:
 *   - video_swgfx_getdrv(self)->xsw_getpixel
 *   - video_swgfx_getdrv(self)->xsw_setpixel
 * - Additionally,  `self->vg_surf' and `self->vg_blend' need to be initialized
 *   already, though this should already be the case if used from `vi_initgfx'.
 * - `video_swgfx_update()' should be called from `vi_updategfx'
 * @param: __self: The GFX context to initialize/update for use with SW-GFX operators
 * @param: __what: What it is about the GFX context that changed
 * @return: * : Always re-returns `__self' */
typedef __ATTR_RETNONNULL_T __ATTR_INOUT_T(1) struct video_gfx *
(LIBVIDEO_GFX_FCC *PVIDEO_SWGFX_POPULATE)(struct video_gfx *__restrict __self);
typedef __ATTR_RETNONNULL_T __ATTR_INOUT_T(1) struct video_gfx *
(LIBVIDEO_GFX_FCC *PVIDEO_SWGFX_UPDATE)(struct video_gfx *__restrict __self, unsigned int __what);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *LIBVIDEO_GFX_FCC
video_swgfx_populate(struct video_gfx *__restrict __self);
LIBVIDEO_GFX_DECL __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_gfx *LIBVIDEO_GFX_FCC
video_swgfx_update(struct video_gfx *__restrict __self, unsigned int __what);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */
#endif /* LIBVIDEO_GFX_EXPOSE_INTERNALS */

#endif /* !_LIBVIDEO_GFX_GFX_SWGFX_H */
