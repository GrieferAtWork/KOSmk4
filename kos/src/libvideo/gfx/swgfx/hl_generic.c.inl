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
#define _KOS_SOURCE 1

#ifdef __INTELLISENSE__
//#define DEFINE_libvideo_swgfx_XXX
#define DEFINE_libvideo_swgfx_XXX_xyswap
#endif /* __INTELLISENSE__ */

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/gfx.h>

#include "../gfx-utils.h"
#include "../swgfx.h"

#if (defined(DEFINE_libvideo_swgfx_XXX_xyswap) + \
     defined(DEFINE_libvideo_swgfx_XXX)) != 1
#error "Must #define exactly one of these"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_libvideo_swgfx_XXX_xyswap
#define LOCAL_FUNC(x) x##_xyswap
#else /* DEFINE_libvideo_swgfx_XXX_xyswap */
#define LOCAL_FUNC(x) x
#endif /* !DEFINE_libvideo_swgfx_XXX_xyswap */

#define LOCAL_libvideo_swgfx_getcolor               LOCAL_FUNC(libvideo_swgfx_getcolor)
#define LOCAL_libvideo_swgfx_getcolor_wrap          LOCAL_FUNC(libvideo_swgfx_getcolor_wrap)
#define LOCAL_libvideo_swgfx_getcolor_mirror        LOCAL_FUNC(libvideo_swgfx_getcolor_mirror)
#define LOCAL_libvideo_swgfx_putcolor               LOCAL_FUNC(libvideo_swgfx_putcolor)
#define LOCAL_libvideo_swgfx_putcolor_wrap          LOCAL_FUNC(libvideo_swgfx_putcolor_wrap)
#define LOCAL_libvideo_swgfx_putcolor_mirror        LOCAL_FUNC(libvideo_swgfx_putcolor_mirror)
#define LOCAL_libvideo_swgfx_line                   LOCAL_FUNC(libvideo_swgfx_line)
#define LOCAL_libvideo_swgfx_line_wrap              LOCAL_FUNC(libvideo_swgfx_line_wrap)
#define LOCAL_libvideo_swgfx_line_mirror            LOCAL_FUNC(libvideo_swgfx_line_mirror)
#define LOCAL_libvideo_swgfx_hline                  LOCAL_FUNC(libvideo_swgfx_hline)
#define LOCAL_libvideo_swgfx_hline_wrap             LOCAL_FUNC(libvideo_swgfx_hline_wrap)
#define LOCAL_libvideo_swgfx_hline_mirror           LOCAL_FUNC(libvideo_swgfx_hline_mirror)
#define LOCAL_libvideo_swgfx_vline                  LOCAL_FUNC(libvideo_swgfx_vline)
#define LOCAL_libvideo_swgfx_vline_wrap             LOCAL_FUNC(libvideo_swgfx_vline_wrap)
#define LOCAL_libvideo_swgfx_vline_mirror           LOCAL_FUNC(libvideo_swgfx_vline_mirror)
#define LOCAL_libvideo_swgfx_fill                   LOCAL_FUNC(libvideo_swgfx_fill)
#define LOCAL_libvideo_swgfx_fill_wrap              LOCAL_FUNC(libvideo_swgfx_fill_wrap)
#define LOCAL_libvideo_swgfx_fill_mirror            LOCAL_FUNC(libvideo_swgfx_fill_mirror)
#define LOCAL_libvideo_swgfx_rect                   LOCAL_FUNC(libvideo_swgfx_rect)
#define LOCAL_libvideo_swgfx_rect_wrap              LOCAL_FUNC(libvideo_swgfx_rect_wrap)
#define LOCAL_libvideo_swgfx_rect_mirror            LOCAL_FUNC(libvideo_swgfx_rect_mirror)
#define LOCAL_libvideo_swgfx_gradient               LOCAL_FUNC(libvideo_swgfx_gradient)
#define LOCAL_libvideo_swgfx_gradient_wrap          LOCAL_FUNC(libvideo_swgfx_gradient_wrap)
#define LOCAL_libvideo_swgfx_gradient_mirror        LOCAL_FUNC(libvideo_swgfx_gradient_mirror)
#define LOCAL_libvideo_swgfx_hgradient              LOCAL_FUNC(libvideo_swgfx_hgradient)
#define LOCAL_libvideo_swgfx_hgradient_wrap         LOCAL_FUNC(libvideo_swgfx_hgradient_wrap)
#define LOCAL_libvideo_swgfx_hgradient_mirror       LOCAL_FUNC(libvideo_swgfx_hgradient_mirror)
#define LOCAL_libvideo_swgfx_vgradient              LOCAL_FUNC(libvideo_swgfx_vgradient)
#define LOCAL_libvideo_swgfx_vgradient_wrap         LOCAL_FUNC(libvideo_swgfx_vgradient_wrap)
#define LOCAL_libvideo_swgfx_vgradient_mirror       LOCAL_FUNC(libvideo_swgfx_vgradient_mirror)

#ifdef DEFINE_libvideo_swgfx_XXX_xyswap
#define LOCAL_libvideo_swgfx_fillmask             libvideo_swgfx_fillmask_byblit
#define LOCAL_libvideo_swgfx_fillmask_wrap        libvideo_swgfx_fillmask_byblit
#define LOCAL_libvideo_swgfx_fillstretchmask      libvideo_swgfx_fillstretchmask_byblit
#define LOCAL_libvideo_swgfx_fillstretchmask_wrap libvideo_swgfx_fillstretchmask_byblit
#else /* DEFINE_libvideo_swgfx_XXX_xyswap */
#define LOCAL_libvideo_swgfx_fillmask             libvideo_swgfx_fillmask
#define LOCAL_libvideo_swgfx_fillmask_wrap        libvideo_swgfx_fillmask_wrap
#define LOCAL_libvideo_swgfx_fillstretchmask      libvideo_swgfx_fillstretchmask
#define LOCAL_libvideo_swgfx_fillstretchmask_wrap libvideo_swgfx_fillstretchmask_wrap
#endif /* !DEFINE_libvideo_swgfx_XXX_xyswap */

#define LOCAL__video_swgfx_x_getcolor           LOCAL_FUNC(_video_swgfx_x_getcolor)
#define LOCAL__video_swgfx_x_putcolor           LOCAL_FUNC(_video_swgfx_x_putcolor)
#define LOCAL__video_swgfx_x_getpixel           LOCAL_FUNC(_video_swgfx_x_getpixel)
#define LOCAL__video_swgfx_x_setpixel           LOCAL_FUNC(_video_swgfx_x_setpixel)
#define LOCAL__video_swgfx_x_absline_llhh       LOCAL_FUNC(_video_swgfx_x_absline_llhh)
#define LOCAL__video_swgfx_x_absline_lhhl       LOCAL_FUNC(_video_swgfx_x_absline_lhhl)
#define LOCAL__video_swgfx_x_absline_h          LOCAL_FUNC(_video_swgfx_x_absline_h)
#define LOCAL__video_swgfx_x_absline_v          LOCAL_FUNC(_video_swgfx_x_absline_v)
#define LOCAL__video_swgfx_x_absfill            LOCAL_FUNC(_video_swgfx_x_absfill)
#define LOCAL__video_swgfx_x_absfillmask        LOCAL_FUNC(_video_swgfx_x_absfillmask)
#define LOCAL__video_swgfx_x_absfillstretchmask LOCAL_FUNC(_video_swgfx_x_absfillstretchmask)
#define LOCAL__video_swgfx_x_absgradient        LOCAL_FUNC(_video_swgfx_x_absgradient)
#define LOCAL__video_swgfx_x_absgradient_h      LOCAL_FUNC(_video_swgfx_x_absgradient_h)
#define LOCAL__video_swgfx_x_absgradient_v      LOCAL_FUNC(_video_swgfx_x_absgradient_v)

#define LOCAL_video_swgfx_x_getcolor           LOCAL_FUNC(video_swgfx_x_getcolor)
#define LOCAL_video_swgfx_x_putcolor           LOCAL_FUNC(video_swgfx_x_putcolor)
#define LOCAL_video_swgfx_x_getpixel           LOCAL_FUNC(video_swgfx_x_getpixel)
#define LOCAL_video_swgfx_x_setpixel           LOCAL_FUNC(video_swgfx_x_setpixel)
#define LOCAL_video_swgfx_x_absline_llhh       LOCAL_FUNC(video_swgfx_x_absline_llhh)
#define LOCAL_video_swgfx_x_absline_lhhl       LOCAL_FUNC(video_swgfx_x_absline_lhhl)
#define LOCAL_video_swgfx_x_absline_h          LOCAL_FUNC(video_swgfx_x_absline_h)
#define LOCAL_video_swgfx_x_absline_v          LOCAL_FUNC(video_swgfx_x_absline_v)
#define LOCAL_video_swgfx_x_absfill            LOCAL_FUNC(video_swgfx_x_absfill)
#define LOCAL_video_swgfx_x_absfillmask        LOCAL_FUNC(video_swgfx_x_absfillmask)
#define LOCAL_video_swgfx_x_absfillstretchmask LOCAL_FUNC(video_swgfx_x_absfillstretchmask)
#define LOCAL_video_swgfx_x_absgradient        LOCAL_FUNC(video_swgfx_x_absgradient)
#define LOCAL_video_swgfx_x_absgradient_h      LOCAL_FUNC(video_swgfx_x_absgradient_h)
#define LOCAL_video_swgfx_x_absgradient_v      LOCAL_FUNC(video_swgfx_x_absgradient_v)

#define LOCAL_libvideo_swgfx_ops         LOCAL_FUNC(libvideo_swgfx_ops)
#define LOCAL_libvideo_swgfx_ops_wrap    LOCAL_FUNC(libvideo_swgfx_ops_wrap)
#define LOCAL_libvideo_swgfx_ops_mirror  LOCAL_FUNC(libvideo_swgfx_ops_mirror)
#define LOCAL__libvideo_swgfx_ops        LOCAL_FUNC(_libvideo_swgfx_ops)
#define LOCAL__libvideo_swgfx_ops_wrap   LOCAL_FUNC(_libvideo_swgfx_ops_wrap)
#define LOCAL__libvideo_swgfx_ops_mirror LOCAL_FUNC(_libvideo_swgfx_ops_mirror)


/************************************************************************/
/* GETCOLOR()                                                           */
/************************************************************************/
INTERN ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC
LOCAL_libvideo_swgfx_getcolor(struct video_gfx const *__restrict self,
                              video_offset_t x, video_offset_t y) {
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if likely((video_coord_t)x >= GFX_BXMIN && (video_coord_t)x < GFX_BXEND &&
	          (video_coord_t)y >= GFX_BYMIN && (video_coord_t)y < GFX_BYEND) {
		return LOCAL__video_swgfx_x_getcolor(self, (video_coord_t)x, (video_coord_t)y);
	}
	return 0;
}

INTERN ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC
LOCAL_libvideo_swgfx_getcolor_wrap(struct video_gfx const *__restrict self,
                                   video_offset_t x, video_offset_t y) {
	if (self->vx_flags & VIDEO_GFX_F_XWRAP)
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
	if (self->vx_flags & VIDEO_GFX_F_YWRAP)
		y = wrap(y, self->vx_hdr.vxh_cysiz);
	return LOCAL_libvideo_swgfx_getcolor(self, x, y);
}

INTERN ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC
LOCAL_libvideo_swgfx_getcolor_mirror(struct video_gfx const *__restrict self,
                                     video_offset_t x, video_offset_t y) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR)
		x = (self->vx_hdr.vxh_cxsiz - 1) - x;
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR)
		y = (self->vx_hdr.vxh_cysiz - 1) - y;
	return LOCAL_libvideo_swgfx_getcolor_wrap(self, x, y);
}



/************************************************************************/
/* PUTCOLOR()                                                           */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_putcolor(struct video_gfx const *__restrict self,
                              video_offset_t x, video_offset_t y,
                              video_color_t color) {
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if likely((video_coord_t)x >= GFX_BXMIN && (video_coord_t)x < GFX_BXEND &&
	          (video_coord_t)y >= GFX_BYMIN && (video_coord_t)y < GFX_BYEND)
		LOCAL__video_swgfx_x_putcolor(self, (video_coord_t)x, (video_coord_t)y, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_putcolor_wrap(struct video_gfx const *__restrict self,
                                   video_offset_t x, video_offset_t y,
                                   video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XWRAP)
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
	if (self->vx_flags & VIDEO_GFX_F_YWRAP)
		y = wrap(y, self->vx_hdr.vxh_cysiz);
	LOCAL_libvideo_swgfx_putcolor(self, x, y, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_putcolor_mirror(struct video_gfx const *__restrict self,
                                     video_offset_t x, video_offset_t y,
                                     video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR)
		x = (self->vx_hdr.vxh_cxsiz - 1) - x;
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR)
		y = (self->vx_hdr.vxh_cysiz - 1) - y;
	LOCAL_libvideo_swgfx_putcolor_wrap(self, x, y, color);
}





/************************************************************************/
/* LINE()                                                               */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_line(struct video_gfx const *__restrict self,
                          video_offset_t x1, video_offset_t y1,
                          video_offset_t x2, video_offset_t y2,
                          video_color_t color) {
	/* >> Cohen-Sutherland algorithm
	 * https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm */
	int outcode0, outcode1, outcodeOut;
	video_offset_t temp, x, y;
#define COHSUTH_INSIDE 0 /* 0000 */
#define COHSUTH_XMIN   1 /* 0001 */
#define COHSUTH_XMAX   2 /* 0010 */
#define COHSUTH_YMIN   4 /* 0100 */
#define COHSUTH_YMAX   8 /* 1000 */
	x1 += self->vx_hdr.vxh_cxoff;
	y1 += self->vx_hdr.vxh_cyoff;
	x2 += self->vx_hdr.vxh_cxoff;
	y2 += self->vx_hdr.vxh_cyoff;
#define COHSUTH_COMPUTEOUTCODE(x, y, result)           \
	do {                                               \
		(result) = COHSUTH_INSIDE;                     \
		if ((x) < (video_offset_t)GFX_BXMIN) {         \
			(result) |= COHSUTH_XMIN;                  \
		} else if ((x) >= (video_offset_t)GFX_BXEND) { \
			(result) |= COHSUTH_XMAX;                  \
		}                                              \
		if ((y) < (video_offset_t)GFX_BYMIN) {         \
			(result) |= COHSUTH_YMIN;                  \
		} else if ((y) >= (video_offset_t)GFX_BYEND) { \
			(result) |= COHSUTH_YMAX;                  \
		}                                              \
	}	__WHILE0
	COHSUTH_COMPUTEOUTCODE(x1, y1, outcode0);
	COHSUTH_COMPUTEOUTCODE(x2, y2, outcode1);
	while ((outcode0 | outcode1) != 0) {
		if ((outcode0 & outcode1) != 0)
			return;
		outcodeOut = outcode0 ? outcode0 : outcode1;
		if ((outcodeOut & COHSUTH_YMAX) != 0) {
			x = x1 + (x2 - x1) * ((video_offset_t)GFX_BYMAX - y1) / (y2 - y1);
			y = (video_offset_t)GFX_BYMAX;
		} else if ((outcodeOut & COHSUTH_YMIN) != 0) {
			x = x1 + (x2 - x1) * ((video_offset_t)GFX_BYMIN - y1) / (y2 - y1);
			y = (video_offset_t)GFX_BYMIN;
		} else if ((outcodeOut & COHSUTH_XMAX) != 0) {
			y = y1 + (y2 - y1) * ((video_offset_t)GFX_BXMAX - x1) / (x2 - x1);
			x = (video_offset_t)GFX_BXMAX;
		} else /*if ((outcodeOut & COHSUTH_XMIN) != 0)*/ {
			y = y1 + (y2 - y1) * ((video_offset_t)GFX_BXMIN - x1) / (x2 - x1);
			x = (video_offset_t)GFX_BXMIN;
		}
		if (outcodeOut == outcode0) {
			x1 = x;
			y1 = y;
			COHSUTH_COMPUTEOUTCODE(x1, y1, outcode0);
		} else {
			x2 = x;
			y2 = y;
			COHSUTH_COMPUTEOUTCODE(x2, y2, outcode1);
		}
	}
	gfx_assert_absbounds_xy(self, (video_coord_t)x1, (video_coord_t)y1);
	gfx_assert_absbounds_xy(self, (video_coord_t)x2, (video_coord_t)y2);

	/* Coords are clamped! --> Now select the proper line algorithm */
	if (x1 > x2) {
		temp = x2, x2 = x1, x1 = temp;
		temp = y2, y2 = y1, y1 = temp;
	} else if (x1 == x2) {
		if (y1 > y2) {
			temp = y2;
			y2   = y1;
			y1   = temp;
		} else if (y1 == y2) {
			LOCAL_video_swgfx_x_putcolor(self, (video_coord_t)x1, (video_coord_t)y1, color);
			return;
		}
		LOCAL_video_swgfx_x_absline_v(self, (video_coord_t)x1, (video_coord_t)y1,
		                              (video_dim_t)((video_coord_t)y2 - (video_coord_t)y1) + 1,
		                              color);
		return;
	}
	gfx_assert(x2 > x1);
	if (y2 > y1) {
		video_dim_t sx = (video_dim_t)((video_coord_t)x2 - (video_coord_t)x1) + 1;
		video_dim_t sy = (video_dim_t)((video_coord_t)y2 - (video_coord_t)y1) + 1;
		LOCAL_video_swgfx_x_absline_llhh(self, (video_coord_t)x1, (video_coord_t)y1, sx, sy, color);
	} else if (y2 < y1) {
		video_dim_t sx = (video_dim_t)((video_coord_t)x2 - (video_coord_t)x1) + 1;
		video_dim_t sy = (video_dim_t)((video_coord_t)y1 - (video_coord_t)y2) + 1;
		LOCAL_video_swgfx_x_absline_lhhl(self, (video_coord_t)x1, (video_coord_t)y1, sx, sy, color);
	} else {
		video_dim_t length = (video_dim_t)((video_coord_t)x2 - (video_coord_t)x1) + 1;
		LOCAL_video_swgfx_x_absline_h(self, (video_coord_t)x1, (video_coord_t)y1, length, color);
	}
#undef COHSUTH_COMPUTEOUTCODE
#undef COHSUTH_INSIDE
#undef COHSUTH_XMIN
#undef COHSUTH_XMAX
#undef COHSUTH_YMIN
#undef COHSUTH_YMAX
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_line_wrap(struct video_gfx const *__restrict self,
                               video_offset_t x1, video_offset_t y1,
                               video_offset_t x2, video_offset_t y2,
                               video_color_t color) {
	/* TODO */
	LOCAL_libvideo_swgfx_line(self, x1, y1, x2, y2, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_line_mirror(struct video_gfx const *__restrict self,
                                 video_offset_t x1, video_offset_t y1,
                                 video_offset_t x2, video_offset_t y2,
                                 video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR) {
		x1 = (self->vx_hdr.vxh_cxsiz - 1) - x1;
		x2 = (self->vx_hdr.vxh_cxsiz - 1) - x2;
	}
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR) {
		y1 = (self->vx_hdr.vxh_cysiz - 1) - y1;
		y2 = (self->vx_hdr.vxh_cysiz - 1) - y2;
	}
	LOCAL_libvideo_swgfx_line_wrap(self, x1, y1, x2, y2, color);
}






/************************************************************************/
/* HLINE()                                                              */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_hline(struct video_gfx const *__restrict self,
                           video_offset_t x, video_offset_t y,
                           video_dim_t length, video_color_t color) {
	video_coord_t temp;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(y < (video_offset_t)GFX_BYMIN)
		return;
	if unlikely(y >= (video_offset_t)GFX_BYEND)
		return;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(length <= off)
			return;
		length -= off;
		x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, length, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		length = GFX_BXEND - (video_coord_t)x;
	}

	LOCAL_video_swgfx_x_absline_h(self, (video_coord_t)x, (video_coord_t)y, length, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_hline_wrap(struct video_gfx const *__restrict self,
                                video_offset_t x, video_offset_t y,
                                video_dim_t length, video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_YWRAP)
		y = wrap(y, self->vx_hdr.vxh_cysiz);
	if (self->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_coord_t cxend;
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
		if (OVERFLOW_UADD((video_coord_t)x, length, &cxend) || length >= self->vx_hdr.vxh_cxsiz) {
			x = 0;
			length = self->vx_hdr.vxh_cxsiz;
		} else if (cxend > self->vx_hdr.vxh_cxsiz) {
			LOCAL_libvideo_swgfx_hline(self, 0, y, cxend - self->vx_hdr.vxh_cxsiz, color);
		}
	}
	LOCAL_libvideo_swgfx_hline(self, x, y, length, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_hline_mirror(struct video_gfx const *__restrict self,
                                  video_offset_t x, video_offset_t y,
                                  video_dim_t length, video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR)
		x = (self->vx_hdr.vxh_cxsiz - length) - x;
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR)
		y = (self->vx_hdr.vxh_cysiz - 1) - y;
	LOCAL_libvideo_swgfx_hline_wrap(self, x, y, length, color);
}



/************************************************************************/
/* VLINE()                                                              */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_vline(struct video_gfx const *__restrict self,
                           video_offset_t x, video_offset_t y,
                           video_dim_t length, video_color_t color) {
	video_coord_t temp;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN)
		return;
	if unlikely(x >= (video_offset_t)GFX_BXEND)
		return;
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(length <= off)
			return;
		length -= off;
		y = (video_offset_t)GFX_BYMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, length, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		length = GFX_BYEND - (video_coord_t)y;
	}
	LOCAL_video_swgfx_x_absline_v(self, (video_coord_t)x, (video_coord_t)y, length, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_vline_wrap(struct video_gfx const *__restrict self,
                                video_offset_t x, video_offset_t y,
                                video_dim_t length, video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XWRAP)
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
	if (self->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_coord_t cyend;
		y = wrap(y, self->vx_hdr.vxh_cysiz);
		if (OVERFLOW_UADD((video_coord_t)y, length, &cyend) || length >= self->vx_hdr.vxh_cysiz) {
			y = 0;
			length = self->vx_hdr.vxh_cysiz;
		} else if (cyend > self->vx_hdr.vxh_cysiz) {
			LOCAL_libvideo_swgfx_vline(self, x, 0, cyend - self->vx_hdr.vxh_cysiz, color);
		}
	}
	LOCAL_libvideo_swgfx_vline(self, x, y, length, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_vline_mirror(struct video_gfx const *__restrict self,
                                  video_offset_t x, video_offset_t y,
                                  video_dim_t length, video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR)
		x = (self->vx_hdr.vxh_cxsiz - 1) - x;
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR)
		y = (self->vx_hdr.vxh_cysiz - length) - y;
	LOCAL_libvideo_swgfx_vline_wrap(self, x, y, length, color);
}



/************************************************************************/
/* FILL()                                                               */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_fill(struct video_gfx const *__restrict self,
                          video_offset_t x, video_offset_t y,
                          video_dim_t size_x, video_dim_t size_y,
                          video_color_t color) {
	video_coord_t temp;
	if unlikely(!size_x || !size_y)
		return;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(size_x <= off)
			return;
		size_x -= off;
		x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(size_y <= off)
			return;
		size_y -= off;
		y = (video_offset_t)GFX_BYMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, size_x, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		size_x = GFX_BXEND - (video_coord_t)x;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, size_y, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		size_y = GFX_BYEND - (video_coord_t)y;
	}
	LOCAL_video_swgfx_x_absfill(self, (video_coord_t)x, (video_coord_t)y,
	                            size_x, size_y, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_fill_wrap(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y,
                               video_dim_t size_x, video_dim_t size_y,
                               video_color_t color) {
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	if (self->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_coord_t cxend;
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
		if (OVERFLOW_UADD((video_coord_t)x, size_x, &cxend) || size_x >= self->vx_hdr.vxh_cxsiz) {
			x = 0;
			size_x = self->vx_hdr.vxh_cxsiz;
		} else {
			/* # of pixels that go beyond the right clip-edge */
			if (OVERFLOW_USUB(cxend, self->vx_hdr.vxh_cxsiz, &xwrap))
				xwrap = 0;
		}
	}
	if (self->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_coord_t cyend;
		y = wrap(y, self->vx_hdr.vxh_cysiz);
		if (OVERFLOW_UADD((video_coord_t)y, size_y, &cyend) || size_y >= self->vx_hdr.vxh_cysiz) {
			y = 0;
			size_y = self->vx_hdr.vxh_cysiz;
		} else {
			/* # of pixels that go beyond the bottom clip-edge */
			if (OVERFLOW_USUB(cyend, self->vx_hdr.vxh_cysiz, &ywrap))
				ywrap = 0;
		}
	}
	if (xwrap && ywrap) /* Must do a partial fill at the top-left */
		LOCAL_libvideo_swgfx_fill(self, 0, 0, xwrap, ywrap, color);
	if (xwrap) /* Must do a partial fill at the left */
		LOCAL_libvideo_swgfx_fill(self, 0, y, xwrap, size_y, color);
	if (ywrap) /* Must do a partial fill at the top */
		LOCAL_libvideo_swgfx_fill(self, x, 0, size_x, ywrap, color);
	LOCAL_libvideo_swgfx_fill(self, x, y, size_x, size_y, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_fill_mirror(struct video_gfx const *__restrict self,
                                 video_offset_t x, video_offset_t y,
                                 video_dim_t size_x, video_dim_t size_y,
                                 video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR)
		x = (self->vx_hdr.vxh_cxsiz - size_x) - x;
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR)
		y = (self->vx_hdr.vxh_cysiz - size_y) - y;
	LOCAL_libvideo_swgfx_fill_wrap(self, x, y, size_x, size_y, color);
}



/************************************************************************/
/* RECT()                                                               */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_rect(struct video_gfx const *__restrict self,
                          video_offset_t x, video_offset_t y,
                          video_dim_t size_x, video_dim_t size_y,
                          video_color_t color) {
	video_dim_t temp;
#define LINE_XMIN 0x1
#define LINE_YMIN 0x2
#define LINE_XMAX 0x4
#define LINE_YMAX 0x8
	uint8_t draw_lines;
	if unlikely(!size_x || !size_y)
		return;
	draw_lines = 0xf;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(size_x <= off)
			return;
		size_x -= off;
		x = (video_offset_t)GFX_BXMIN;
		draw_lines &= ~LINE_XMIN;
	}
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(size_y <= off)
			return;
		size_y -= off;
		y = (video_offset_t)GFX_BYMIN;
		draw_lines &= ~LINE_YMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, size_x, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		size_x = GFX_BXEND - (video_coord_t)x;
		draw_lines &= ~LINE_XMAX;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, size_y, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		size_y = GFX_BYEND - (video_coord_t)y;
		draw_lines &= ~LINE_YMAX;
	}
#define HLINE(x, y, length) LOCAL_video_swgfx_x_absline_h(self, x, y, length, color)
#define VLINE(x, y, length) LOCAL_video_swgfx_x_absline_v(self, x, y, length, color)
	switch (draw_lines) {

		/* All 4 lines */
	case LINE_XMIN | LINE_YMIN | LINE_XMAX | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
			if (size_y >= 3) {
				VLINE((video_coord_t)x, (video_coord_t)y + 1, size_y - 2); /* XMIN */
				if (size_x >= 2)
					VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y + 1, size_y - 2); /* XMAX */
			}
		}
		break;

		/* 3-line combinations */
	case LINE_YMIN | LINE_YMAX | LINE_XMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
			if (size_y >= 3)
				VLINE((video_coord_t)x, (video_coord_t)y + 1, size_y - 2); /* XMIN */
		}
		break;

	case LINE_YMIN | LINE_YMAX | LINE_XMAX:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
			if (size_y >= 3)
				VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y + 1, size_y - 2); /* XMAX */
		}
		break;

	case LINE_XMIN | LINE_XMAX | LINE_YMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			VLINE((video_coord_t)x, (video_coord_t)y + 1, size_y - 1); /* XMIN */
			if (size_x >= 2)
				VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y + 1, size_y - 1); /* XMAX */
		}
		break;

	case LINE_XMIN | LINE_XMAX | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
		if (size_y >= 2) {
			VLINE((video_coord_t)x, (video_coord_t)y, size_y - 1); /* XMIN */
			if (size_x >= 2)
				VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y, size_y - 1); /* XMAX */
		}
		break;

		/* Adjacent lines */
	case LINE_XMIN | LINE_YMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2)
			VLINE((video_coord_t)x, (video_coord_t)y + 1, size_y - 1); /* XMIN */
		break;

	case LINE_XMAX | LINE_YMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2)
			VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y + 1, size_y - 1); /* XMAX */
		break;

	case LINE_XMIN | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
		if (size_y >= 2)
			VLINE((video_coord_t)x, (video_coord_t)y, size_y - 1); /* XMIN */
		break;

	case LINE_XMAX | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
		if (size_y >= 2)
			VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y, size_y - 1); /* XMAX */
		break;


		/* Opposing lines */
	case LINE_XMIN | LINE_XMAX:
		VLINE((video_coord_t)x, (video_coord_t)y, size_y); /* XMIN */
		if (size_x >= 2)
			VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y, size_y); /* XMAX */
		break;

	case LINE_YMIN | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2)
			HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
		break;

		/* Single lines */
	case LINE_XMAX:
		x += size_x - 1;
		ATTR_FALLTHROUGH
	case LINE_XMIN:
		VLINE((video_coord_t)x, (video_coord_t)y, size_y); /* XMIN / XMAX */
		break;

	case LINE_YMAX:
		y += size_y - 1;
		ATTR_FALLTHROUGH
	case LINE_YMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN / YMAX */
		break;

	case 0: /* Completely out-of-bounds */
		break;

	default:
		__builtin_unreachable();
	}
#undef VLINE
#undef HLINE
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_rect_wrap(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y,
                               video_dim_t size_x, video_dim_t size_y,
                               video_color_t color) {
	if (size_x <= 1) {
		if unlikely(!size_x)
			return;
		LOCAL_libvideo_swgfx_vline_wrap(self, x, y, size_y, color);
	} else if (size_y <= 1) {
		if unlikely(!size_y)
			return;
		LOCAL_libvideo_swgfx_hline_wrap(self, x, y, size_x, color);
	} else {
		video_offset_t ymax = y + size_y - 1;
		LOCAL_libvideo_swgfx_hline_wrap(self, x, y, size_x, color);
		LOCAL_libvideo_swgfx_hline_wrap(self, x, ymax, size_x, color);
		if (size_y > 2) {
			video_offset_t xmax = x + size_x - 1;
			LOCAL_libvideo_swgfx_vline_wrap(self, x, y + 1, size_y - 2, color);
			LOCAL_libvideo_swgfx_vline_wrap(self, xmax, y + 1, size_y - 2, color);
		}
	}
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_rect_mirror(struct video_gfx const *__restrict self,
                                 video_offset_t x, video_offset_t y,
                                 video_dim_t size_x, video_dim_t size_y,
                                 video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR)
		x = (self->vx_hdr.vxh_cxsiz - size_x) - x;
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR)
		y = (self->vx_hdr.vxh_cysiz - size_y) - y;
	LOCAL_libvideo_swgfx_rect_wrap(self, x, y, size_x, size_y, color);
}




/************************************************************************/
/* GRADIENT()                                                           */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_gradient(struct video_gfx const *__restrict self,
                              video_offset_t x, video_offset_t y,
                              video_dim_t size_x, video_dim_t size_y,
                              video_color_t const colors[2][2]) {
	video_coord_t temp;
	video_color_t fixed_colors[2][2];
	if unlikely(!size_x || !size_y)
		return;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(size_x <= off)
			return;
		frac0 = (off * LINEAR_FP_BLEND(1)) / size_x;
		frac1 = LINEAR_FP_BLEND(1) - frac0;
		size_x -= off;
		x = (video_offset_t)GFX_BXMIN;
		colors = (video_color_t (*)[2])memcpy(fixed_colors, colors, sizeof(fixed_colors));
		fixed_colors[0][0] = interpolate_1d(fixed_colors[0][0], fixed_colors[0][1], frac0, frac1);
		fixed_colors[1][0] = interpolate_1d(fixed_colors[1][0], fixed_colors[1][1], frac0, frac1);
	}
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(size_y <= off)
			return;
		frac0 = (off * LINEAR_FP_BLEND(1)) / size_y;
		frac1 = LINEAR_FP_BLEND(1) - frac0;
		size_y -= off;
		y = (video_offset_t)GFX_BYMIN;
		colors = (video_color_t (*)[2])memcpy(fixed_colors, colors, sizeof(fixed_colors));
		fixed_colors[0][0] = interpolate_1d(fixed_colors[0][0], fixed_colors[1][0], frac0, frac1);
		fixed_colors[0][1] = interpolate_1d(fixed_colors[0][1], fixed_colors[1][1], frac0, frac1);
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, size_x, &temp) || temp > GFX_BXEND) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off;
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		off = temp - GFX_BXEND;
		frac1 = (off * LINEAR_FP_BLEND(1)) / size_x;
		frac0 = LINEAR_FP_BLEND(1) - frac1;
		size_x = GFX_BXEND - (video_coord_t)x;
		colors = (video_color_t (*)[2])memcpy(fixed_colors, colors, sizeof(fixed_colors));
		fixed_colors[0][1] = interpolate_1d(fixed_colors[0][0], fixed_colors[0][1], frac1, frac0);
		fixed_colors[1][1] = interpolate_1d(fixed_colors[1][0], fixed_colors[1][1], frac1, frac0);
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, size_y, &temp) || temp > GFX_BYEND) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off;
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		off = temp - GFX_BYEND;
		frac1 = (off * LINEAR_FP_BLEND(1)) / size_y;
		frac0 = LINEAR_FP_BLEND(1) - frac1;
		size_y = GFX_BYEND - (video_coord_t)y;
		colors = (video_color_t (*)[2])memcpy(fixed_colors, colors, sizeof(fixed_colors));
		fixed_colors[1][0] = interpolate_1d(fixed_colors[0][0], fixed_colors[1][0], frac1, frac0);
		fixed_colors[1][1] = interpolate_1d(fixed_colors[0][1], fixed_colors[1][1], frac1, frac0);
	}
	LOCAL_video_swgfx_x_absgradient(self, (video_coord_t)x, (video_coord_t)y,
	                                    size_x, size_y, colors);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_gradient_wrap(struct video_gfx const *__restrict self,
                                   video_offset_t x, video_offset_t y,
                                   video_dim_t size_x, video_dim_t size_y,
                                   video_color_t const colors[2][2]) {
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	if (self->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_coord_t cxend;
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
		if (OVERFLOW_UADD((video_coord_t)x, size_x, &cxend) || size_x >= self->vx_hdr.vxh_cxsiz) {
			x = 0;
			size_x = self->vx_hdr.vxh_cxsiz;
		} else {
			/* # of pixels that go beyond the right clip-edge */
			if (OVERFLOW_USUB(cxend, self->vx_hdr.vxh_cxsiz, &xwrap))
				xwrap = 0;
		}
	}
	if (self->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_coord_t cyend;
		y = wrap(y, self->vx_hdr.vxh_cysiz);
		if (OVERFLOW_UADD((video_coord_t)y, size_y, &cyend) || size_y >= self->vx_hdr.vxh_cysiz) {
			y = 0;
			size_y = self->vx_hdr.vxh_cysiz;
		} else {
			/* # of pixels that go beyond the bottom clip-edge */
			if (OVERFLOW_USUB(cyend, self->vx_hdr.vxh_cysiz, &ywrap))
				ywrap = 0;
		}
	}
	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		linear_fp_blend_t xfrac0, xfrac1;
		linear_fp_blend_t yfrac0, yfrac1;
		video_color_t fixed_colors[2][2];
		xfrac0 = (xwrap * LINEAR_FP_BLEND(1)) / size_x;
		xfrac1 = LINEAR_FP_BLEND(1) - xfrac0;
		yfrac0 = (ywrap * LINEAR_FP_BLEND(1)) / size_y;
		yfrac1 = LINEAR_FP_BLEND(1) - yfrac0;
		fixed_colors[0][0] = interpolate_2d(colors[0][0], colors[0][1], colors[1][0], colors[1][1],
		                                    xfrac1, xfrac0, yfrac1, yfrac0);
		fixed_colors[1][0] = interpolate_1d(colors[1][0], colors[1][1], xfrac1, xfrac0);
		fixed_colors[0][1] = interpolate_1d(colors[0][1], colors[1][1], yfrac1, yfrac0);
		fixed_colors[1][1] = colors[1][1];
		LOCAL_libvideo_swgfx_gradient(self, 0, 0, xwrap, ywrap, fixed_colors);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		linear_fp_blend_t xfrac0, xfrac1;
		video_color_t fixed_colors[2][2];
		xfrac0 = (xwrap * LINEAR_FP_BLEND(1)) / size_x;
		xfrac1 = LINEAR_FP_BLEND(1) - xfrac0;
		fixed_colors[0][0] = interpolate_1d(colors[0][0], colors[0][1], xfrac1, xfrac0);
		fixed_colors[1][0] = interpolate_1d(colors[1][0], colors[1][1], xfrac1, xfrac0);
		fixed_colors[0][1] = colors[0][1];
		fixed_colors[1][1] = colors[1][1];
		LOCAL_libvideo_swgfx_gradient(self, 0, y, xwrap, size_y, fixed_colors);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		linear_fp_blend_t yfrac0, yfrac1;
		video_color_t fixed_colors[2][2];
		yfrac0 = (ywrap * LINEAR_FP_BLEND(1)) / size_y;
		yfrac1 = LINEAR_FP_BLEND(1) - yfrac0;
		fixed_colors[0][0] = interpolate_1d(colors[0][0], colors[1][0], yfrac1, yfrac0);
		fixed_colors[1][0] = colors[1][0];
		fixed_colors[0][1] = interpolate_1d(colors[0][1], colors[1][1], yfrac1, yfrac0);
		fixed_colors[1][1] = colors[1][1];
		LOCAL_libvideo_swgfx_gradient(self, x, 0, size_x, ywrap, fixed_colors);
	}
	LOCAL_libvideo_swgfx_gradient(self, x, y, size_x, size_y, colors);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_gradient_mirror(struct video_gfx const *__restrict self,
                                     video_offset_t x, video_offset_t y,
                                     video_dim_t size_x, video_dim_t size_y,
                                     video_color_t const colors[2][2]) {
	video_color_t fixed_colors[2][2];
	switch (self->vx_flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR)) {
#define Tswap(T, a, b) { T _temp = (a); (a) = (b); (b) = _temp; }
	case 0:
		break;
	case VIDEO_GFX_F_XMIRROR:
		x = (self->vx_hdr.vxh_cxsiz - size_x) - x;
		colors = (video_color_t const (*)[2])memcpy(fixed_colors, colors, 4, sizeof(video_color_t));
		Tswap(video_color_t, fixed_colors[0][0], fixed_colors[0][1]);
		Tswap(video_color_t, fixed_colors[1][0], fixed_colors[1][1]);
		break;
	case VIDEO_GFX_F_YMIRROR:
		y = (self->vx_hdr.vxh_cysiz - size_y) - y;
		colors = (video_color_t const (*)[2])memcpy(fixed_colors, colors, 4, sizeof(video_color_t));
		Tswap(video_color_t, fixed_colors[0][0], fixed_colors[1][0]);
		Tswap(video_color_t, fixed_colors[0][1], fixed_colors[1][1]);
		break;
	case VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR:
		x = (self->vx_hdr.vxh_cxsiz - size_x) - x;
		y = (self->vx_hdr.vxh_cysiz - size_y) - y;
		colors = (video_color_t const (*)[2])memcpy(fixed_colors, colors, 4, sizeof(video_color_t));
		Tswap(video_color_t, fixed_colors[0][0], fixed_colors[1][1]);
		Tswap(video_color_t, fixed_colors[0][1], fixed_colors[1][0]);
		break;
	default: __builtin_unreachable();
#undef Tswap
	}
	LOCAL_libvideo_swgfx_gradient_wrap(self, x, y, size_x, size_y, colors);
}




/************************************************************************/
/* H-GRADIENT()                                                         */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_hgradient(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y,
                               video_dim_t size_x, video_dim_t size_y,
                               video_color_t locolor, video_color_t hicolor) {
	video_coord_t temp;
	if unlikely(!size_x || !size_y)
		return;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(size_x <= off)
			return;
		frac0 = (off * LINEAR_FP_BLEND(1)) / size_x;
		frac1 = LINEAR_FP_BLEND(1) - frac0;
		size_x -= off;
		x = (video_offset_t)GFX_BXMIN;
		locolor = interpolate_1d(locolor, hicolor, frac0, frac1);
	}
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(size_y <= off)
			return;
		size_y -= off;
		y = (video_offset_t)GFX_BYMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, size_x, &temp) || temp > GFX_BXEND) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off;
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		off = temp - GFX_BXEND;
		frac1 = (off * LINEAR_FP_BLEND(1)) / size_x;
		frac0 = LINEAR_FP_BLEND(1) - frac1;
		size_x = GFX_BXEND - (video_coord_t)x;
		hicolor = interpolate_1d(locolor, hicolor, frac1, frac0);
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, size_y, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		size_y = GFX_BYEND - (video_coord_t)y;
	}
	LOCAL_video_swgfx_x_absgradient_h(self, (video_coord_t)x, (video_coord_t)y,
	                                      size_x, size_y, locolor, hicolor);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_hgradient_wrap(struct video_gfx const *__restrict self,
                                    video_offset_t x, video_offset_t y,
                                    video_dim_t size_x, video_dim_t size_y,
                                    video_color_t locolor, video_color_t hicolor) {
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	if (self->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_coord_t cxend;
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
		if (OVERFLOW_UADD((video_coord_t)x, size_x, &cxend) || size_x >= self->vx_hdr.vxh_cxsiz) {
			x = 0;
			size_x = self->vx_hdr.vxh_cxsiz;
		} else {
			/* # of pixels that go beyond the right clip-edge */
			if (OVERFLOW_USUB(cxend, self->vx_hdr.vxh_cxsiz, &xwrap))
				xwrap = 0;
		}
	}
	if (self->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_coord_t cyend;
		y = wrap(y, self->vx_hdr.vxh_cysiz);
		if (OVERFLOW_UADD((video_coord_t)y, size_y, &cyend) || size_y >= self->vx_hdr.vxh_cysiz) {
			y = 0;
			size_y = self->vx_hdr.vxh_cysiz;
		} else {
			/* # of pixels that go beyond the bottom clip-edge */
			if (OVERFLOW_USUB(cyend, self->vx_hdr.vxh_cysiz, &ywrap))
				ywrap = 0;
		}
	}
	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		linear_fp_blend_t xfrac0, xfrac1;
		video_color_t fixed_locolor;
		xfrac0 = (xwrap * LINEAR_FP_BLEND(1)) / size_x;
		xfrac1 = LINEAR_FP_BLEND(1) - xfrac0;
		fixed_locolor = interpolate_1d(locolor, hicolor, xfrac1, xfrac0);
		LOCAL_libvideo_swgfx_hgradient(self, 0, 0, xwrap, ywrap, fixed_locolor, hicolor);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		linear_fp_blend_t xfrac0, xfrac1;
		video_color_t fixed_locolor;
		xfrac0 = (xwrap * LINEAR_FP_BLEND(1)) / size_x;
		xfrac1 = LINEAR_FP_BLEND(1) - xfrac0;
		fixed_locolor = interpolate_1d(locolor, hicolor, xfrac1, xfrac0);
		LOCAL_libvideo_swgfx_hgradient(self, 0, y, xwrap, size_y, fixed_locolor, hicolor);
	}
	if (ywrap) /* Must do a partial fill at the top */
		LOCAL_libvideo_swgfx_hgradient(self, x, 0, size_x, ywrap, locolor, hicolor);
	LOCAL_libvideo_swgfx_hgradient(self, x, y, size_x, size_y, locolor, hicolor);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_hgradient_mirror(struct video_gfx const *__restrict self,
                                      video_offset_t x, video_offset_t y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      video_color_t locolor, video_color_t hicolor) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR) {
		video_color_t temp;
		x = (self->vx_hdr.vxh_cxsiz - size_x) - x;
		temp = locolor;
		locolor = hicolor;
		hicolor = temp;
	}
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR)
		y = (self->vx_hdr.vxh_cysiz - size_y) - y;
	LOCAL_libvideo_swgfx_hgradient_wrap(self, x, y, size_x, size_y, locolor, hicolor);
}




/************************************************************************/
/* V-GRADIENT()                                                         */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_vgradient(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y,
                               video_dim_t size_x, video_dim_t size_y,
                               video_color_t locolor, video_color_t hicolor) {
	video_coord_t temp;
	if unlikely(!size_x || !size_y)
		return;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(size_x <= off)
			return;
		size_x -= off;
		x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(size_y <= off)
			return;
		frac0 = (off * LINEAR_FP_BLEND(1)) / size_y;
		frac1 = LINEAR_FP_BLEND(1) - frac0;
		size_y -= off;
		y = (video_offset_t)GFX_BYMIN;
		locolor = interpolate_1d(locolor, hicolor, frac0, frac1);
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, size_x, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		size_x = GFX_BXEND - (video_coord_t)x;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, size_y, &temp) || temp > GFX_BYEND) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off;
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		off = temp - GFX_BYEND;
		frac1 = (off * LINEAR_FP_BLEND(1)) / size_y;
		frac0 = LINEAR_FP_BLEND(1) - frac1;
		size_y = GFX_BYEND - (video_coord_t)y;
		hicolor = interpolate_1d(locolor, hicolor, frac1, frac0);
	}
	LOCAL_video_swgfx_x_absgradient_v(self, (video_coord_t)x, (video_coord_t)y,
	                                  size_x, size_y, locolor, hicolor);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_vgradient_wrap(struct video_gfx const *__restrict self,
                                    video_offset_t x, video_offset_t y,
                                    video_dim_t size_x, video_dim_t size_y,
                                    video_color_t locolor, video_color_t hicolor) {
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	if (self->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_coord_t cxend;
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
		if (OVERFLOW_UADD((video_coord_t)x, size_x, &cxend) || size_x >= self->vx_hdr.vxh_cxsiz) {
			x = 0;
			size_x = self->vx_hdr.vxh_cxsiz;
		} else {
			/* # of pixels that go beyond the right clip-edge */
			if (OVERFLOW_USUB(cxend, self->vx_hdr.vxh_cxsiz, &xwrap))
				xwrap = 0;
		}
	}
	if (self->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_coord_t cyend;
		y = wrap(y, self->vx_hdr.vxh_cysiz);
		if (OVERFLOW_UADD((video_coord_t)y, size_y, &cyend) || size_y >= self->vx_hdr.vxh_cysiz) {
			y = 0;
			size_y = self->vx_hdr.vxh_cysiz;
		} else {
			/* # of pixels that go beyond the bottom clip-edge */
			if (OVERFLOW_USUB(cyend, self->vx_hdr.vxh_cysiz, &ywrap))
				ywrap = 0;
		}
	}
	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		linear_fp_blend_t yfrac0, yfrac1;
		video_color_t fixed_locolor;
		yfrac0 = (ywrap * LINEAR_FP_BLEND(1)) / size_y;
		yfrac1 = LINEAR_FP_BLEND(1) - yfrac0;
		fixed_locolor = interpolate_1d(locolor, hicolor, yfrac1, yfrac0);
		LOCAL_libvideo_swgfx_vgradient(self, 0, 0, xwrap, ywrap, fixed_locolor, hicolor);
	}
	if (xwrap) /* Must do a partial fill at the left */
		LOCAL_libvideo_swgfx_vgradient(self, 0, y, xwrap, size_y, locolor, hicolor);
	if (ywrap) { /* Must do a partial fill at the top */
		linear_fp_blend_t yfrac0, yfrac1;
		video_color_t fixed_locolor;
		yfrac0 = (ywrap * LINEAR_FP_BLEND(1)) / size_y;
		yfrac1 = LINEAR_FP_BLEND(1) - yfrac0;
		fixed_locolor = interpolate_1d(locolor, hicolor, yfrac1, yfrac0);
		LOCAL_libvideo_swgfx_vgradient(self, x, 0, size_x, ywrap, fixed_locolor, hicolor);
	}
	LOCAL_libvideo_swgfx_vgradient(self, x, y, size_x, size_y, locolor, hicolor);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swgfx_vgradient_mirror(struct video_gfx const *__restrict self,
                                      video_offset_t x, video_offset_t y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      video_color_t locolor, video_color_t hicolor) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR)
		x = (self->vx_hdr.vxh_cxsiz - size_x) - x;
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR) {
		video_color_t temp;
		y = (self->vx_hdr.vxh_cysiz - size_y) - y;
		temp = locolor;
		locolor = hicolor;
		hicolor = temp;
	}
	LOCAL_libvideo_swgfx_vgradient_wrap(self, x, y, size_x, size_y, locolor, hicolor);
}





#undef libvideo_swgfx_ops
#undef libvideo_swgfx_ops_xyswap
#undef libvideo_swgfx_ops_wrap
#undef libvideo_swgfx_ops_wrap_xyswap
#undef libvideo_swgfx_ops_mirror
#undef libvideo_swgfx_ops_mirror_xyswap
PRIVATE struct video_gfx_ops LOCAL_libvideo_swgfx_ops = {};
PRIVATE struct video_gfx_ops LOCAL_libvideo_swgfx_ops_wrap = {};
PRIVATE struct video_gfx_ops LOCAL_libvideo_swgfx_ops_mirror = {};

#ifndef DEFINED_libvideo_gfx_ops_setcommon
#define DEFINED_libvideo_gfx_ops_setcommon
PRIVATE ATTR_INOUT(1) void CC
libvideo_gfx_ops_setcommon(struct video_gfx_ops *__restrict self) {
	self->vgfo_blitfrom     = &libvideo_swgfx_blitfrom;
	self->vgfo_blitfrom3    = &libvideo_swgfx_blitfrom3;
	self->vgfo_clip         = &libvideo_gfx_clip__generic;
	self->vgfo_offset2coord = &libvideo_gfx_offset2coord__generic;
	self->vgfo_coord2offset = &libvideo_gfx_coord2offset__generic;
	self->vgfo_bitblit      = &libvideo_gfx_bitblit__with_blitter;
	self->vgfo_stretch      = &libvideo_gfx_stretch__with_blitter;
	self->vgfo_bitblit3     = &libvideo_gfx_bitblit3__with_blitter3;
	self->vgfo_stretch3     = &libvideo_gfx_stretch3__with_blitter3;
}
#endif /* !DEFINED_libvideo_gfx_ops_setcommon */

INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC
LOCAL__libvideo_swgfx_ops(void) {
	if unlikely(!LOCAL_libvideo_swgfx_ops.vgfo_getcolor) {
		libvideo_gfx_ops_setcommon(&LOCAL_libvideo_swgfx_ops);
		LOCAL_libvideo_swgfx_ops.vgfo_vgradient       = &LOCAL_libvideo_swgfx_vgradient;
		LOCAL_libvideo_swgfx_ops.vgfo_hgradient       = &LOCAL_libvideo_swgfx_hgradient;
		LOCAL_libvideo_swgfx_ops.vgfo_gradient        = &LOCAL_libvideo_swgfx_gradient;
		LOCAL_libvideo_swgfx_ops.vgfo_fillstretchmask = &LOCAL_libvideo_swgfx_fillstretchmask;
		LOCAL_libvideo_swgfx_ops.vgfo_fillmask        = &LOCAL_libvideo_swgfx_fillmask;
		LOCAL_libvideo_swgfx_ops.vgfo_rect            = &LOCAL_libvideo_swgfx_rect;
		LOCAL_libvideo_swgfx_ops.vgfo_fill            = &LOCAL_libvideo_swgfx_fill;
		LOCAL_libvideo_swgfx_ops.vgfo_vline           = &LOCAL_libvideo_swgfx_vline;
		LOCAL_libvideo_swgfx_ops.vgfo_hline           = &LOCAL_libvideo_swgfx_hline;
		LOCAL_libvideo_swgfx_ops.vgfo_line            = &LOCAL_libvideo_swgfx_line;
		LOCAL_libvideo_swgfx_ops.vgfo_putcolor        = &LOCAL_libvideo_swgfx_putcolor;
		COMPILER_WRITE_BARRIER();
		LOCAL_libvideo_swgfx_ops.vgfo_getcolor = &LOCAL_libvideo_swgfx_getcolor;
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_libvideo_swgfx_ops;
}

INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC
LOCAL__libvideo_swgfx_ops_wrap(void) {
	if unlikely(!LOCAL_libvideo_swgfx_ops_wrap.vgfo_getcolor) {
		libvideo_gfx_ops_setcommon(&LOCAL_libvideo_swgfx_ops_wrap);
		LOCAL_libvideo_swgfx_ops_wrap.vgfo_vgradient       = &LOCAL_libvideo_swgfx_vgradient_wrap;
		LOCAL_libvideo_swgfx_ops_wrap.vgfo_hgradient       = &LOCAL_libvideo_swgfx_hgradient_wrap;
		LOCAL_libvideo_swgfx_ops_wrap.vgfo_gradient        = &LOCAL_libvideo_swgfx_gradient_wrap;
		LOCAL_libvideo_swgfx_ops_wrap.vgfo_fillstretchmask = &LOCAL_libvideo_swgfx_fillstretchmask_wrap;
		LOCAL_libvideo_swgfx_ops_wrap.vgfo_fillmask        = &LOCAL_libvideo_swgfx_fillmask_wrap;
		LOCAL_libvideo_swgfx_ops_wrap.vgfo_rect            = &LOCAL_libvideo_swgfx_rect_wrap;
		LOCAL_libvideo_swgfx_ops_wrap.vgfo_fill            = &LOCAL_libvideo_swgfx_fill_wrap;
		LOCAL_libvideo_swgfx_ops_wrap.vgfo_vline           = &LOCAL_libvideo_swgfx_vline_wrap;
		LOCAL_libvideo_swgfx_ops_wrap.vgfo_hline           = &LOCAL_libvideo_swgfx_hline_wrap;
		LOCAL_libvideo_swgfx_ops_wrap.vgfo_line            = &LOCAL_libvideo_swgfx_line_wrap;
		LOCAL_libvideo_swgfx_ops_wrap.vgfo_putcolor        = &LOCAL_libvideo_swgfx_putcolor_wrap;
		COMPILER_WRITE_BARRIER();
		LOCAL_libvideo_swgfx_ops_wrap.vgfo_getcolor = &LOCAL_libvideo_swgfx_getcolor_wrap;
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_libvideo_swgfx_ops_wrap;
}

INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC
LOCAL__libvideo_swgfx_ops_mirror(void) {
	if unlikely(!LOCAL_libvideo_swgfx_ops_mirror.vgfo_getcolor) {
		libvideo_gfx_ops_setcommon(&LOCAL_libvideo_swgfx_ops_mirror);
		LOCAL_libvideo_swgfx_ops_mirror.vgfo_vgradient       = &LOCAL_libvideo_swgfx_vgradient_mirror;
		LOCAL_libvideo_swgfx_ops_mirror.vgfo_hgradient       = &LOCAL_libvideo_swgfx_hgradient_mirror;
		LOCAL_libvideo_swgfx_ops_mirror.vgfo_gradient        = &LOCAL_libvideo_swgfx_gradient_mirror;
		LOCAL_libvideo_swgfx_ops_mirror.vgfo_fillstretchmask = &libvideo_swgfx_fillstretchmask_byblit;
		LOCAL_libvideo_swgfx_ops_mirror.vgfo_fillmask        = &libvideo_swgfx_fillmask_byblit;
		LOCAL_libvideo_swgfx_ops_mirror.vgfo_rect            = &LOCAL_libvideo_swgfx_rect_mirror;
		LOCAL_libvideo_swgfx_ops_mirror.vgfo_fill            = &LOCAL_libvideo_swgfx_fill_mirror;
		LOCAL_libvideo_swgfx_ops_mirror.vgfo_vline           = &LOCAL_libvideo_swgfx_vline_mirror;
		LOCAL_libvideo_swgfx_ops_mirror.vgfo_hline           = &LOCAL_libvideo_swgfx_hline_mirror;
		LOCAL_libvideo_swgfx_ops_mirror.vgfo_line            = &LOCAL_libvideo_swgfx_line_mirror;
		LOCAL_libvideo_swgfx_ops_mirror.vgfo_putcolor        = &LOCAL_libvideo_swgfx_putcolor_mirror;
		COMPILER_WRITE_BARRIER();
		LOCAL_libvideo_swgfx_ops_mirror.vgfo_getcolor = &LOCAL_libvideo_swgfx_getcolor_mirror;
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_libvideo_swgfx_ops_mirror;
}

#define libvideo_swgfx_ops                 (*_libvideo_swgfx_ops())
#define libvideo_swgfx_ops_xyswap          (*_libvideo_swgfx_ops_xyswap())
#define libvideo_swgfx_ops_wrap            (*_libvideo_swgfx_ops_wrap())
#define libvideo_swgfx_ops_wrap_xyswap     (*_libvideo_swgfx_ops_wrap_xyswap())
#define libvideo_swgfx_ops_mirror          (*_libvideo_swgfx_ops_mirror())
#define libvideo_swgfx_ops_mirror_xyswap   (*_libvideo_swgfx_ops_mirror_xyswap())

#undef LOCAL_libvideo_swgfx_getcolor_wrap
#undef LOCAL_libvideo_swgfx_getcolor_mirror
#undef LOCAL_libvideo_swgfx_putcolor
#undef LOCAL_libvideo_swgfx_putcolor_wrap
#undef LOCAL_libvideo_swgfx_putcolor_mirror
#undef LOCAL_libvideo_swgfx_line
#undef LOCAL_libvideo_swgfx_line_wrap
#undef LOCAL_libvideo_swgfx_line_mirror
#undef LOCAL_libvideo_swgfx_hline
#undef LOCAL_libvideo_swgfx_hline_wrap
#undef LOCAL_libvideo_swgfx_hline_mirror
#undef LOCAL_libvideo_swgfx_vline
#undef LOCAL_libvideo_swgfx_vline_wrap
#undef LOCAL_libvideo_swgfx_vline_mirror
#undef LOCAL_libvideo_swgfx_fill
#undef LOCAL_libvideo_swgfx_fill_wrap
#undef LOCAL_libvideo_swgfx_fill_mirror
#undef LOCAL_libvideo_swgfx_rect
#undef LOCAL_libvideo_swgfx_rect_wrap
#undef LOCAL_libvideo_swgfx_rect_mirror
#undef LOCAL_libvideo_swgfx_gradient
#undef LOCAL_libvideo_swgfx_gradient_wrap
#undef LOCAL_libvideo_swgfx_gradient_mirror
#undef LOCAL_libvideo_swgfx_hgradient
#undef LOCAL_libvideo_swgfx_hgradient_wrap
#undef LOCAL_libvideo_swgfx_hgradient_mirror
#undef LOCAL_libvideo_swgfx_vgradient
#undef LOCAL_libvideo_swgfx_vgradient_wrap
#undef LOCAL_libvideo_swgfx_vgradient_mirror
#undef LOCAL_libvideo_swgfx_fillmask
#undef LOCAL_libvideo_swgfx_fillmask_wrap
#undef LOCAL_libvideo_swgfx_fillstretchmask
#undef LOCAL_libvideo_swgfx_fillstretchmask_wrap

#undef LOCAL__video_swgfx_x_getcolor
#undef LOCAL__video_swgfx_x_putcolor
#undef LOCAL__video_swgfx_x_getpixel
#undef LOCAL__video_swgfx_x_setpixel
#undef LOCAL__video_swgfx_x_absline_llhh
#undef LOCAL__video_swgfx_x_absline_lhhl
#undef LOCAL__video_swgfx_x_absline_h
#undef LOCAL__video_swgfx_x_absline_v
#undef LOCAL__video_swgfx_x_absfill
#undef LOCAL__video_swgfx_x_absfillmask
#undef LOCAL__video_swgfx_x_absfillstretchmask
#undef LOCAL__video_swgfx_x_absgradient
#undef LOCAL__video_swgfx_x_absgradient_h
#undef LOCAL__video_swgfx_x_absgradient_v

#undef LOCAL_video_swgfx_x_getcolor
#undef LOCAL_video_swgfx_x_putcolor
#undef LOCAL_video_swgfx_x_getpixel
#undef LOCAL_video_swgfx_x_setpixel
#undef LOCAL_video_swgfx_x_absline_llhh
#undef LOCAL_video_swgfx_x_absline_lhhl
#undef LOCAL_video_swgfx_x_absline_h
#undef LOCAL_video_swgfx_x_absline_v
#undef LOCAL_video_swgfx_x_absfill
#undef LOCAL_video_swgfx_x_absfillmask
#undef LOCAL_video_swgfx_x_absfillstretchmask
#undef LOCAL_video_swgfx_x_absgradient
#undef LOCAL_video_swgfx_x_absgradient_h
#undef LOCAL_video_swgfx_x_absgradient_v

#undef LOCAL_libvideo_swgfx_ops
#undef LOCAL_libvideo_swgfx_ops_wrap
#undef LOCAL_libvideo_swgfx_ops_mirror
#undef LOCAL__libvideo_swgfx_ops
#undef LOCAL__libvideo_swgfx_ops_wrap
#undef LOCAL__libvideo_swgfx_ops_mirror

#undef LOCAL_FUNC

DECL_END

#undef DEFINE_libvideo_swgfx_XXX_xyswap
#undef DEFINE_libvideo_swgfx_XXX
