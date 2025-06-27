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
#ifdef __INTELLISENSE__
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1
#include "../gfx.c"

//#define DEFINE_libvideo_gfx_generic_XXX
#define DEFINE_libvideo_gfx_generic_XXX_xyswap
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
#include "../gfx.h"

#if (defined(DEFINE_libvideo_gfx_generic_XXX_xyswap) + \
     defined(DEFINE_libvideo_gfx_generic_XXX)) != 1
#error "Must #define exactly one of these"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_libvideo_gfx_generic_XXX_xyswap
#define LOCAL_FUNC(x) x##_xyswap
#else /* DEFINE_libvideo_gfx_generic_XXX_xyswap */
#define LOCAL_FUNC(x) x
#endif /* !DEFINE_libvideo_gfx_generic_XXX_xyswap */


/************************************************************************/
/* GETCOLOR()                                                           */
/************************************************************************/
INTERN ATTR_IN(1) video_color_t CC
LOCAL_FUNC(libvideo_gfx_generic_getcolor)(struct video_gfx const *__restrict self,
                                          video_offset_t x, video_offset_t y) {
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if likely((video_coord_t)x >= GFX_BXMIN && (video_coord_t)x < GFX_BXEND &&
	          (video_coord_t)y >= GFX_BYMIN && (video_coord_t)y < GFX_BYEND) {
		return LOCAL_FUNC(_video_gfx_x_getcolor)(self, (video_coord_t)x, (video_coord_t)y);
	}
	return 0;
}

INTERN ATTR_IN(1) video_color_t CC
LOCAL_FUNC(libvideo_gfx_generic_getcolor_wrap)(struct video_gfx const *__restrict self,
                                               video_offset_t x, video_offset_t y) {
	if (self->vx_flags & VIDEO_GFX_F_XWRAP)
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
	if (self->vx_flags & VIDEO_GFX_F_YWRAP)
		y = wrap(y, self->vx_hdr.vxh_cysiz);
	return libvideo_gfx_generic_getcolor(self, x, y);
}

INTERN ATTR_IN(1) video_color_t CC
LOCAL_FUNC(libvideo_gfx_generic_getcolor_mirror)(struct video_gfx const *__restrict self,
                                                 video_offset_t x, video_offset_t y) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR)
		x = (self->vx_hdr.vxh_cxsiz - 1) - x;
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR)
		y = (self->vx_hdr.vxh_cysiz - 1) - y;
	return libvideo_gfx_generic_getcolor_wrap(self, x, y);
}



/************************************************************************/
/* PUTCOLOR()                                                           */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_putcolor)(struct video_gfx const *__restrict self,
                                          video_offset_t x, video_offset_t y,
                                          video_color_t color) {
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if likely((video_coord_t)x >= GFX_BXMIN && (video_coord_t)x < GFX_BXEND &&
	          (video_coord_t)y >= GFX_BYMIN && (video_coord_t)y < GFX_BYEND)
		LOCAL_FUNC(_video_gfx_x_putcolor)(self, (video_coord_t)x, (video_coord_t)y, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_putcolor_wrap)(struct video_gfx const *__restrict self,
                                               video_offset_t x, video_offset_t y,
                                               video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XWRAP)
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
	if (self->vx_flags & VIDEO_GFX_F_YWRAP)
		y = wrap(y, self->vx_hdr.vxh_cysiz);
	LOCAL_FUNC(libvideo_gfx_generic_putcolor)(self, x, y, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_putcolor_mirror)(struct video_gfx const *__restrict self,
                                                 video_offset_t x, video_offset_t y,
                                                 video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR)
		x = (self->vx_hdr.vxh_cxsiz - 1) - x;
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR)
		y = (self->vx_hdr.vxh_cysiz - 1) - y;
	LOCAL_FUNC(libvideo_gfx_generic_putcolor_wrap)(self, x, y, color);
}





/************************************************************************/
/* LINE()                                                               */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_line)(struct video_gfx const *__restrict self,
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
			LOCAL_FUNC(video_gfx_x_putcolor)(self, (video_coord_t)x1, (video_coord_t)y1, color);
			return;
		}
		LOCAL_FUNC(video_gfx_x_absline_v)(self, (video_coord_t)x1, (video_coord_t)y1,
		                                  (video_dim_t)((video_coord_t)y2 - (video_coord_t)y1) + 1,
		                                  color);
		return;
	}
	gfx_assert(x2 > x1);
	if (y2 > y1) {
		video_dim_t sx = (video_dim_t)((video_coord_t)x2 - (video_coord_t)x1) + 1;
		video_dim_t sy = (video_dim_t)((video_coord_t)y2 - (video_coord_t)y1) + 1;
		LOCAL_FUNC(video_gfx_x_absline_llhh)(self, (video_coord_t)x1, (video_coord_t)y1, sx, sy, color);
	} else if (y2 < y1) {
		video_dim_t sx = (video_dim_t)((video_coord_t)x2 - (video_coord_t)x1) + 1;
		video_dim_t sy = (video_dim_t)((video_coord_t)y1 - (video_coord_t)y2) + 1;
		LOCAL_FUNC(video_gfx_x_absline_lhhl)(self, (video_coord_t)x1, (video_coord_t)y1, sx, sy, color);
	} else {
		video_dim_t length = (video_dim_t)((video_coord_t)x2 - (video_coord_t)x1) + 1;
		LOCAL_FUNC(video_gfx_x_absline_h)(self, (video_coord_t)x1, (video_coord_t)y1, length, color);
	}
#undef COHSUTH_COMPUTEOUTCODE
#undef COHSUTH_INSIDE
#undef COHSUTH_XMIN
#undef COHSUTH_XMAX
#undef COHSUTH_YMIN
#undef COHSUTH_YMAX
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_line_wrap)(struct video_gfx const *__restrict self,
                                           video_offset_t x1, video_offset_t y1,
                                           video_offset_t x2, video_offset_t y2,
                                           video_color_t color) {
	/* TODO */
	LOCAL_FUNC(libvideo_gfx_generic_line)(self, x1, y1, x2, y2, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_line_mirror)(struct video_gfx const *__restrict self,
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
	LOCAL_FUNC(libvideo_gfx_generic_line_wrap)(self, x1, y1, x2, y2, color);
}






/************************************************************************/
/* HLINE()                                                              */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_hline)(struct video_gfx const *__restrict self,
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

	LOCAL_FUNC(video_gfx_x_absline_h)(self, (video_coord_t)x, (video_coord_t)y, length, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_hline_wrap)(struct video_gfx const *__restrict self,
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
			LOCAL_FUNC(libvideo_gfx_generic_hline)(self, 0, y, cxend - self->vx_hdr.vxh_cxsiz, color);
		}
	}
	LOCAL_FUNC(libvideo_gfx_generic_hline)(self, x, y, length, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_hline_mirror)(struct video_gfx const *__restrict self,
                                              video_offset_t x, video_offset_t y,
                                              video_dim_t length, video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR) {
		x = (self->vx_hdr.vxh_cxsiz - 1) - x;
		x -= length;
	}
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR)
		y = (self->vx_hdr.vxh_cysiz - 1) - y;
	LOCAL_FUNC(libvideo_gfx_generic_hline_wrap)(self, x, y, length, color);
}



/************************************************************************/
/* VLINE()                                                              */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_vline)(struct video_gfx const *__restrict self,
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
	LOCAL_FUNC(video_gfx_x_absline_v)(self, (video_coord_t)x, (video_coord_t)y, length, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_vline_wrap)(struct video_gfx const *__restrict self,
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
			LOCAL_FUNC(libvideo_gfx_generic_vline)(self, x, 0, cyend - self->vx_hdr.vxh_cysiz, color);
		}
	}
	LOCAL_FUNC(libvideo_gfx_generic_vline)(self, x, y, length, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_vline_mirror)(struct video_gfx const *__restrict self,
                                              video_offset_t x, video_offset_t y,
                                              video_dim_t length, video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR)
		x = (self->vx_hdr.vxh_cxsiz - 1) - x;
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR) {
		y = (self->vx_hdr.vxh_cysiz - 1) - y;
		y -= length;
	}
	LOCAL_FUNC(libvideo_gfx_generic_vline_wrap)(self, x, y, length, color);
}



/************************************************************************/
/* FILL()                                                               */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_fill)(struct video_gfx const *__restrict self,
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
	LOCAL_FUNC(video_gfx_x_absfill)(self, (video_coord_t)x, (video_coord_t)y,
	                                size_x, size_y, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_fill_wrap)(struct video_gfx const *__restrict self,
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
		LOCAL_FUNC(libvideo_gfx_generic_fill)(self, 0, 0, xwrap, ywrap, color);
	if (xwrap) /* Must do a partial fill at the left */
		LOCAL_FUNC(libvideo_gfx_generic_fill)(self, 0, y, xwrap, size_y, color);
	if (ywrap) /* Must do a partial fill at the top */
		LOCAL_FUNC(libvideo_gfx_generic_fill)(self, x, 0, size_x, ywrap, color);
	LOCAL_FUNC(libvideo_gfx_generic_fill)(self, x, y, size_x, size_y, color);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_fill_mirror)(struct video_gfx const *__restrict self,
                                             video_offset_t x, video_offset_t y,
                                             video_dim_t size_x, video_dim_t size_y,
                                             video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR) {
		x = (self->vx_hdr.vxh_cxsiz - 1) - x;
		x -= size_x;
	}
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR) {
		y = (self->vx_hdr.vxh_cysiz - 1) - y;
		y -= size_y;
	}
	LOCAL_FUNC(libvideo_gfx_generic_fill_wrap)(self, x, y, size_x, size_y, color);
}



/************************************************************************/
/* RECT()                                                               */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_rect)(struct video_gfx const *__restrict self,
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
#define HLINE(x, y, length) LOCAL_FUNC(video_gfx_x_absline_h)(self, x, y, length, color)
#define VLINE(x, y, length) LOCAL_FUNC(video_gfx_x_absline_v)(self, x, y, length, color)
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
LOCAL_FUNC(libvideo_gfx_generic_rect_wrap)(struct video_gfx const *__restrict self,
                                           video_offset_t x, video_offset_t y,
                                           video_dim_t size_x, video_dim_t size_y,
                                           video_color_t color) {
	if (size_x <= 1) {
		if unlikely(!size_x)
			return;
		LOCAL_FUNC(libvideo_gfx_generic_vline_wrap)(self, x, y, size_y, color);
	} else if (size_y <= 1) {
		if unlikely(!size_y)
			return;
		LOCAL_FUNC(libvideo_gfx_generic_hline_wrap)(self, x, y, size_x, color);
	} else {
		video_offset_t ymax = y + size_y - 1;
		LOCAL_FUNC(libvideo_gfx_generic_hline_wrap)(self, x, y, size_x, color);
		LOCAL_FUNC(libvideo_gfx_generic_hline_wrap)(self, x, ymax, size_x, color);
		if (size_y > 2) {
			video_offset_t xmax = x + size_x - 1;
			LOCAL_FUNC(libvideo_gfx_generic_vline_wrap)(self, x, y + 1, size_y - 2, color);
			LOCAL_FUNC(libvideo_gfx_generic_vline_wrap)(self, xmax, y + 1, size_y - 2, color);
		}
	}
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_rect_mirror)(struct video_gfx const *__restrict self,
                                             video_offset_t x, video_offset_t y,
                                             video_dim_t size_x, video_dim_t size_y,
                                             video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR) {
		x = (self->vx_hdr.vxh_cxsiz - 1) - x;
		x -= size_x;
	}
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR) {
		y = (self->vx_hdr.vxh_cysiz - 1) - y;
		y -= size_y;
	}
	LOCAL_FUNC(libvideo_gfx_generic_rect_wrap)(self, x, y, size_x, size_y, color);
}




/************************************************************************/
/* GRADIENT()                                                           */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_gradient)(struct video_gfx const *__restrict self,
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
	LOCAL_FUNC(video_gfx_x_absgradient)(self, (video_coord_t)x, (video_coord_t)y,
	                                    size_x, size_y, colors);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_gradient_wrap)(struct video_gfx const *__restrict self,
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
		LOCAL_FUNC(libvideo_gfx_generic_gradient)(self, 0, 0, xwrap, ywrap, fixed_colors);
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
		LOCAL_FUNC(libvideo_gfx_generic_gradient)(self, 0, y, xwrap, size_y, fixed_colors);
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
		LOCAL_FUNC(libvideo_gfx_generic_gradient)(self, x, 0, size_x, ywrap, fixed_colors);
	}
	LOCAL_FUNC(libvideo_gfx_generic_gradient)(self, x, y, size_x, size_y, colors);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_gradient_mirror)(struct video_gfx const *__restrict self,
                                                 video_offset_t x, video_offset_t y,
                                                 video_dim_t size_x, video_dim_t size_y,
                                                 video_color_t const colors[2][2]) {
	video_color_t fixed_colors[2][2];
	switch (self->vx_flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR)) {
#define Tswap(T, a, b) { T __temp = a; a = b; b = __temp; }
	case 0:
		break;
	case VIDEO_GFX_F_XMIRROR:
		x = (self->vx_hdr.vxh_cxsiz - 1) - x;
		x -= size_x;
		colors = (video_color_t const (*)[2])memcpy(fixed_colors, colors, 4, sizeof(video_color_t));
		Tswap(video_color_t, fixed_colors[0][0], fixed_colors[0][1]);
		Tswap(video_color_t, fixed_colors[1][0], fixed_colors[1][1]);
		break;
	case VIDEO_GFX_F_YMIRROR:
		y = (self->vx_hdr.vxh_cysiz - 1) - y;
		y -= size_y;
		colors = (video_color_t const (*)[2])memcpy(fixed_colors, colors, 4, sizeof(video_color_t));
		Tswap(video_color_t, fixed_colors[0][0], fixed_colors[1][0]);
		Tswap(video_color_t, fixed_colors[0][1], fixed_colors[1][1]);
		break;
	case VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR:
		x = (self->vx_hdr.vxh_cxsiz - 1) - x;
		x -= size_x;
		y = (self->vx_hdr.vxh_cysiz - 1) - y;
		y -= size_y;
		colors = (video_color_t const (*)[2])memcpy(fixed_colors, colors, 4, sizeof(video_color_t));
		Tswap(video_color_t, fixed_colors[0][0], fixed_colors[1][1]);
		Tswap(video_color_t, fixed_colors[0][1], fixed_colors[1][0]);
		break;
	default: __builtin_unreachable();
#undef Tswap
	}
	LOCAL_FUNC(libvideo_gfx_generic_gradient_wrap)(self, x, y, size_x, size_y, colors);
}




/************************************************************************/
/* H-GRADIENT()                                                         */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_hgradient)(struct video_gfx const *__restrict self,
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
	LOCAL_FUNC(video_gfx_x_absgradient_h)(self, (video_coord_t)x, (video_coord_t)y,
	                                      size_x, size_y, locolor, hicolor);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_hgradient_wrap)(struct video_gfx const *__restrict self,
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
		LOCAL_FUNC(libvideo_gfx_generic_hgradient)(self, 0, 0, xwrap, ywrap, fixed_locolor, hicolor);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		linear_fp_blend_t xfrac0, xfrac1;
		video_color_t fixed_locolor;
		xfrac0 = (xwrap * LINEAR_FP_BLEND(1)) / size_x;
		xfrac1 = LINEAR_FP_BLEND(1) - xfrac0;
		fixed_locolor = interpolate_1d(locolor, hicolor, xfrac1, xfrac0);
		LOCAL_FUNC(libvideo_gfx_generic_hgradient)(self, 0, y, xwrap, size_y, fixed_locolor, hicolor);
	}
	if (ywrap) /* Must do a partial fill at the top */
		LOCAL_FUNC(libvideo_gfx_generic_hgradient)(self, x, 0, size_x, ywrap, locolor, hicolor);
	LOCAL_FUNC(libvideo_gfx_generic_hgradient)(self, x, y, size_x, size_y, locolor, hicolor);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_hgradient_mirror)(struct video_gfx const *__restrict self,
                                                  video_offset_t x, video_offset_t y,
                                                  video_dim_t size_x, video_dim_t size_y,
                                                  video_color_t locolor, video_color_t hicolor) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR) {
		video_color_t temp;
		x = (self->vx_hdr.vxh_cxsiz - 1) - x;
		x -= size_x;
		temp = locolor;
		locolor = hicolor;
		hicolor = temp;
	}
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR) {
		y = (self->vx_hdr.vxh_cysiz - 1) - y;
		y -= size_y;
	}
	LOCAL_FUNC(libvideo_gfx_generic_hgradient_wrap)(self, x, y, size_x, size_y, locolor, hicolor);
}




/************************************************************************/
/* V-GRADIENT()                                                         */
/************************************************************************/
INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_vgradient)(struct video_gfx const *__restrict self,
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
	LOCAL_FUNC(video_gfx_x_absgradient_v)(self, (video_coord_t)x, (video_coord_t)y,
	                                      size_x, size_y, locolor, hicolor);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_vgradient_wrap)(struct video_gfx const *__restrict self,
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
		LOCAL_FUNC(libvideo_gfx_generic_vgradient)(self, 0, 0, xwrap, ywrap, fixed_locolor, hicolor);
	}
	if (xwrap) /* Must do a partial fill at the left */
		LOCAL_FUNC(libvideo_gfx_generic_vgradient)(self, 0, y, xwrap, size_y, locolor, hicolor);
	if (ywrap) { /* Must do a partial fill at the top */
		linear_fp_blend_t yfrac0, yfrac1;
		video_color_t fixed_locolor;
		yfrac0 = (ywrap * LINEAR_FP_BLEND(1)) / size_y;
		yfrac1 = LINEAR_FP_BLEND(1) - yfrac0;
		fixed_locolor = interpolate_1d(locolor, hicolor, yfrac1, yfrac0);
		LOCAL_FUNC(libvideo_gfx_generic_vgradient)(self, x, 0, size_x, ywrap, fixed_locolor, hicolor);
	}
	LOCAL_FUNC(libvideo_gfx_generic_vgradient)(self, x, y, size_x, size_y, locolor, hicolor);
}

INTERN ATTR_IN(1) void CC
LOCAL_FUNC(libvideo_gfx_generic_vgradient_mirror)(struct video_gfx const *__restrict self,
                                                  video_offset_t x, video_offset_t y,
                                                  video_dim_t size_x, video_dim_t size_y,
                                                  video_color_t locolor, video_color_t hicolor) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR) {
		x = (self->vx_hdr.vxh_cxsiz - 1) - x;
		x -= size_x;
	}
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR) {
		video_color_t temp;
		y = (self->vx_hdr.vxh_cysiz - 1) - y;
		y -= size_y;
		temp = locolor;
		locolor = hicolor;
		hicolor = temp;
	}
	LOCAL_FUNC(libvideo_gfx_generic_vgradient_wrap)(self, x, y, size_x, size_y, locolor, hicolor);
}





/************************************************************************/
/* BIT-MASKED FILL                                                      */
/************************************************************************/
INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC
LOCAL_FUNC(libvideo_gfx_generic_fillmask)(struct video_gfx const *__restrict self,
                                          video_offset_t dst_x, video_offset_t dst_y,
                                          video_dim_t size_x, video_dim_t size_y,
                                          video_color_t const bg_fg_colors[2],
                                          struct video_bitmask const *__restrict bm) {
	struct video_bitmask fixed_bm;
	video_coord_t temp;
	if (!size_x || !size_y)
		return;
	dst_x += self->vx_hdr.vxh_cxoff;
	dst_y += self->vx_hdr.vxh_cyoff;
	if unlikely(dst_x < (video_offset_t)GFX_BXMIN) {
		dst_x = (video_offset_t)(GFX_BXMIN - (video_coord_t)dst_x);
		if unlikely((video_coord_t)dst_x >= size_x)
			return;
		fixed_bm = *bm;
		bm = &fixed_bm;
		fixed_bm.vbm_skip += (video_coord_t)dst_x;
		size_x -= (video_coord_t)dst_x;
		dst_x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(dst_y < (video_offset_t)GFX_BYMIN) {
		dst_y = (video_offset_t)(GFX_BYMIN - (video_coord_t)dst_y);
		if unlikely((video_coord_t)dst_y >= size_y)
			return;
		fixed_bm = *bm;
		bm = &fixed_bm;
		fixed_bm.vbm_skip += ((video_coord_t)dst_y) * fixed_bm.vbm_scan;
		size_y -= (video_coord_t)dst_y;
		dst_y = (video_offset_t)GFX_BYMIN;
	}

	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, size_x, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)dst_x >= GFX_BXEND)
			return;
		size_x = GFX_BXEND - (video_coord_t)dst_x;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, size_y, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)dst_y >= GFX_BYEND)
			return;
		size_y = GFX_BYEND - (video_coord_t)dst_y;
	}
	LOCAL_FUNC(video_gfx_x_absfillmask)(self,
	                                    (video_coord_t)dst_x,
	                                    (video_coord_t)dst_y,
	                                    size_x, size_y,
	                                    bg_fg_colors, bm);
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC
LOCAL_FUNC(libvideo_gfx_generic_fillmask_wrap)(struct video_gfx const *__restrict self,
                                               video_offset_t dst_x, video_offset_t dst_y,
                                               video_dim_t size_x, video_dim_t size_y,
                                               video_color_t const bg_fg_colors[2],
                                               struct video_bitmask const *__restrict bm) {
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = size_x;
	video_dim_t yinb = size_y;
	if (self->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_coord_t cxend;
		dst_x = wrap(dst_x, self->vx_hdr.vxh_cxsiz);
		if (size_x > self->vx_hdr.vxh_cxsiz)
			size_x = self->vx_hdr.vxh_cxsiz;
		cxend = (video_coord_t)dst_x + size_x;
		if (OVERFLOW_USUB(cxend, self->vx_hdr.vxh_cxsiz, &xwrap)) {
			xwrap = 0;
		} else {
			xinb = self->vx_hdr.vxh_cxsiz - (video_coord_t)dst_x;
		}
	}
	if (self->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_coord_t cyend;
		dst_y = wrap(dst_y, self->vx_hdr.vxh_cysiz);
		if (size_y > self->vx_hdr.vxh_cysiz)
			size_y = self->vx_hdr.vxh_cysiz;
		cyend = (video_coord_t)dst_y + size_y;
		if (OVERFLOW_USUB(cyend, self->vx_hdr.vxh_cysiz, &ywrap)) {
			ywrap = 0;
		} else {
			yinb = self->vx_hdr.vxh_cysiz - (video_coord_t)dst_y;
		}
	}
	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		struct video_bitmask chunk_bm = *bm;
		chunk_bm.vbm_skip += xinb + (yinb * chunk_bm.vbm_scan);
		LOCAL_FUNC(libvideo_gfx_generic_fillmask)(self, 0, 0, xwrap, ywrap, bg_fg_colors, &chunk_bm);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		struct video_bitmask chunk_bm = *bm;
		chunk_bm.vbm_skip += xinb;
		LOCAL_FUNC(libvideo_gfx_generic_fillmask)(self, 0, dst_y, xwrap, size_y, bg_fg_colors, &chunk_bm);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		struct video_bitmask chunk_bm = *bm;
		chunk_bm.vbm_skip += yinb * chunk_bm.vbm_scan;
		LOCAL_FUNC(libvideo_gfx_generic_fillmask)(self, dst_x, 0, size_x, ywrap, bg_fg_colors, &chunk_bm);
	}
	LOCAL_FUNC(libvideo_gfx_generic_fillmask)(self, dst_x, dst_y, xinb, yinb, bg_fg_colors, bm);
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC
LOCAL_FUNC(libvideo_gfx_generic_fillmask_mirror)(struct video_gfx const *__restrict self,
                                                 video_offset_t dst_x, video_offset_t dst_y,
                                                 video_dim_t size_x, video_dim_t size_y,
                                                 video_color_t const bg_fg_colors[2],
                                                 struct video_bitmask const *__restrict bm) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR) {
		dst_x = (self->vx_hdr.vxh_cxsiz - 1) - dst_x;
		dst_x -= size_x;
		/* TODO: Mirror "bm"? */
	}
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR) {
		dst_y = (self->vx_hdr.vxh_cysiz - 1) - dst_y;
		dst_y -= size_y;
		/* TODO: Mirror "bm"? */
	}
	LOCAL_FUNC(libvideo_gfx_generic_fillmask_wrap)(self, dst_x, dst_y, size_x, size_y, bg_fg_colors, bm);
}





/************************************************************************/
/* BIT-MASKED STRETCH FILL                                              */
/************************************************************************/
INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
LOCAL_FUNC(libvideo_gfx_generic_fillstretchmask)(struct video_gfx const *__restrict self,
                                                 video_offset_t dst_x, video_offset_t dst_y,
                                                 video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                 video_color_t const bg_fg_colors[2],
                                                 video_dim_t src_size_x, video_dim_t src_size_y,
                                                 struct video_bitmask const *__restrict bm) {
	struct video_bitmask fixed_bm;
	video_coord_t temp;
	if unlikely(!dst_size_x || !dst_size_y || !src_size_x || !src_size_y)
		return;
	dst_x += self->vx_hdr.vxh_cxoff;
	dst_y += self->vx_hdr.vxh_cyoff;
	if unlikely(dst_x < (video_offset_t)GFX_BXMIN) {
		video_dim_t srcpart;
		dst_x = (video_offset_t)(GFX_BXMIN - (video_coord_t)dst_x);
		if unlikely((video_coord_t)dst_x >= dst_size_x)
			return;
		srcpart = ((video_coord_t)dst_x * src_size_x) / dst_size_x;
		if unlikely(srcpart >= src_size_x)
			return;
		src_size_x -= srcpart;
		dst_size_x -= (video_coord_t)dst_x;
		fixed_bm = *bm;
		bm = &fixed_bm;
		fixed_bm.vbm_skip += srcpart;
		dst_x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(dst_y < (video_offset_t)GFX_BYMIN) {
		video_dim_t srcpart;
		dst_y = (video_offset_t)(GFX_BYMIN - (video_coord_t)dst_y);
		if unlikely((video_coord_t)dst_y >= dst_size_y)
			return;
		srcpart = ((video_coord_t)dst_y * src_size_y) / dst_size_y;
		if unlikely(srcpart >= src_size_y)
			return;
		src_size_y -= srcpart;
		dst_size_y -= (video_coord_t)dst_y;
		fixed_bm = *bm;
		bm = &fixed_bm;
		fixed_bm.vbm_skip += srcpart * fixed_bm.vbm_scan;
		dst_y = (video_offset_t)GFX_BYMIN;
	}

	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, dst_size_x, &temp) || temp > GFX_BXEND) {
		video_dim_t newdstsize, overflow;
		if unlikely((video_coord_t)dst_x >= GFX_BXEND)
			return;
		newdstsize = GFX_BXEND - (video_coord_t)dst_x;
		overflow   = dst_size_x - newdstsize;
		overflow   = (overflow * src_size_x) / dst_size_x;
		dst_size_x = newdstsize;
		if unlikely(overflow >= src_size_x)
			return;
		src_size_x -= overflow;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, dst_size_y, &temp) || temp > GFX_BYEND) {
		video_dim_t newdstsize, overflow;
		if unlikely((video_coord_t)dst_y >= GFX_BYEND)
			return;
		newdstsize = GFX_BYEND - (video_coord_t)dst_y;
		overflow   = dst_size_y - newdstsize;
		overflow   = (overflow * src_size_y) / dst_size_y;
		dst_size_y = newdstsize;
		if unlikely(overflow >= src_size_y)
			return;
		src_size_y -= overflow;
	}
	if (dst_size_x == src_size_x && dst_size_y == src_size_y) {
		/* Can use copy-blit */
		LOCAL_FUNC(video_gfx_x_absfillmask)(self, (video_coord_t)dst_x, (video_coord_t)dst_y,
		                                    dst_size_x, dst_size_y, bg_fg_colors, bm);
	} else {
		/* Must use stretch-blit */
		LOCAL_FUNC(video_gfx_x_absfillstretchmask)(self, (video_coord_t)dst_x, (video_coord_t)dst_y,
		                                           dst_size_x, dst_size_y, bg_fg_colors,
		                                           src_size_x, src_size_y, bm);
	}
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
LOCAL_FUNC(libvideo_gfx_generic_fillstretchmask_wrap)(struct video_gfx const *__restrict self,
                                                      video_offset_t dst_x, video_offset_t dst_y,
                                                      video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                      video_color_t const bg_fg_colors[2],
                                                      video_dim_t src_size_x, video_dim_t src_size_y,
                                                      struct video_bitmask const *__restrict bm) {
#define xdst2src(x) ((video_coord_t)(((uint64_t)(x) * src_size_x) / dst_size_x))
#define ydst2src(y) ((video_coord_t)(((uint64_t)(y) * src_size_y) / dst_size_y))
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = dst_size_x;
	video_dim_t yinb = dst_size_y;
	if (self->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_coord_t cxend;
		dst_x = wrap(dst_x, self->vx_hdr.vxh_cxsiz);
		if (dst_size_x > self->vx_hdr.vxh_cxsiz) {
			src_size_x = xdst2src(self->vx_hdr.vxh_cxsiz);
			dst_size_x = self->vx_hdr.vxh_cxsiz;
		}
		cxend = (video_coord_t)dst_x + dst_size_x;
		if (OVERFLOW_USUB(cxend, self->vx_hdr.vxh_cxsiz, &xwrap)) {
			xwrap = 0;
		} else {
			xinb = self->vx_hdr.vxh_cxsiz - (video_coord_t)dst_x;
		}
	}
	if (self->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_coord_t cyend;
		dst_y = wrap(dst_y, self->vx_hdr.vxh_cysiz);
		if (dst_size_y > self->vx_hdr.vxh_cysiz) {
			src_size_y = ydst2src(self->vx_hdr.vxh_cysiz);
			dst_size_y = self->vx_hdr.vxh_cysiz;
		}
		cyend = (video_coord_t)dst_y + dst_size_y;
		if (OVERFLOW_USUB(cyend, self->vx_hdr.vxh_cysiz, &ywrap)) {
			ywrap = 0;
		} else {
			yinb = self->vx_hdr.vxh_cysiz - (video_coord_t)dst_y;
		}
	}

	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		struct video_bitmask chunk_bm = *bm;
		size_t chunk_src_x = xdst2src(xinb);
		size_t chunk_src_y = ydst2src(yinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		size_t chunk_src_size_y = ydst2src(ywrap);
		chunk_bm.vbm_skip += chunk_src_x + (chunk_src_y * chunk_bm.vbm_scan);
		(LOCAL_FUNC(libvideo_gfx_generic_fillstretchmask)(self, 0, 0, xwrap, ywrap, bg_fg_colors,
		                                                  chunk_src_size_x, chunk_src_size_y, &chunk_bm));
	}
	if (xwrap) { /* Must do a partial fill at the left */
		struct video_bitmask chunk_bm = *bm;
		size_t chunk_src_x = xdst2src(xinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		chunk_bm.vbm_skip += chunk_src_x;
		(LOCAL_FUNC(libvideo_gfx_generic_fillstretchmask)(self, 0, dst_y, xwrap, dst_size_y, bg_fg_colors,
		                                                  chunk_src_size_x, src_size_y, &chunk_bm));
	}
	if (ywrap) { /* Must do a partial fill at the top */
		struct video_bitmask chunk_bm = *bm;
		size_t chunk_src_y = ydst2src(yinb);
		size_t chunk_src_size_y = ydst2src(ywrap);
		chunk_bm.vbm_skip += chunk_src_y * chunk_bm.vbm_scan;
		(LOCAL_FUNC(libvideo_gfx_generic_fillstretchmask)(self, dst_x, 0, dst_size_x, ywrap, bg_fg_colors,
		                                                  src_size_x, chunk_src_size_y, &chunk_bm));
	}
	(LOCAL_FUNC(libvideo_gfx_generic_fillstretchmask)(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                                  bg_fg_colors, src_size_x, src_size_y, bm));
#undef xdst2src
#undef ydst2src
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
LOCAL_FUNC(libvideo_gfx_generic_fillstretchmask_mirror)(struct video_gfx const *__restrict self,
                                                        video_offset_t dst_x, video_offset_t dst_y,
                                                        video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                        video_color_t const bg_fg_colors[2],
                                                        video_dim_t src_size_x, video_dim_t src_size_y,
                                                        struct video_bitmask const *__restrict bm) {
	if (self->vx_flags & VIDEO_GFX_F_XMIRROR) {
		dst_x = (self->vx_hdr.vxh_cxsiz - 1) - dst_x;
		dst_x -= dst_size_x;
		/* TODO: Mirror "bm"? */
	}
	if (self->vx_flags & VIDEO_GFX_F_YMIRROR) {
		dst_y = (self->vx_hdr.vxh_cysiz - 1) - dst_y;
		dst_y -= dst_size_y;
		/* TODO: Mirror "bm"? */
	}
	(LOCAL_FUNC(libvideo_gfx_generic_fillstretchmask_wrap)(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                                       bg_fg_colors, src_size_x, src_size_y, bm));
}


#undef libvideo_gfx_generic_ops
#undef libvideo_gfx_generic_ops_xyswap
#undef libvideo_gfx_generic_ops_wrap
#undef libvideo_gfx_generic_ops_wrap_xyswap
#undef libvideo_gfx_generic_ops_mirror
#undef libvideo_gfx_generic_ops_mirror_xyswap
PRIVATE struct video_gfx_ops LOCAL_FUNC(libvideo_gfx_generic_ops) = {};
PRIVATE struct video_gfx_ops LOCAL_FUNC(libvideo_gfx_generic_ops_wrap) = {};
PRIVATE struct video_gfx_ops LOCAL_FUNC(libvideo_gfx_generic_ops_mirror) = {};

INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC
LOCAL_FUNC(_libvideo_gfx_generic_ops)(void) {
	if unlikely(!LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_getcolor) {
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_bitblit         = &libvideo_gfx_generic_bitblit;
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_stretch         = &libvideo_gfx_generic_stretch;
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_vgradient       = &LOCAL_FUNC(libvideo_gfx_generic_vgradient);
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_hgradient       = &LOCAL_FUNC(libvideo_gfx_generic_hgradient);
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_gradient        = &LOCAL_FUNC(libvideo_gfx_generic_gradient);
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_fillstretchmask = &LOCAL_FUNC(libvideo_gfx_generic_fillstretchmask);
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_fillmask        = &LOCAL_FUNC(libvideo_gfx_generic_fillmask);
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_rect            = &LOCAL_FUNC(libvideo_gfx_generic_rect);
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_fill            = &LOCAL_FUNC(libvideo_gfx_generic_fill);
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_vline           = &LOCAL_FUNC(libvideo_gfx_generic_vline);
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_hline           = &LOCAL_FUNC(libvideo_gfx_generic_hline);
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_line            = &LOCAL_FUNC(libvideo_gfx_generic_line);
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_putcolor        = &LOCAL_FUNC(libvideo_gfx_generic_putcolor);
		COMPILER_WRITE_BARRIER();
		LOCAL_FUNC(libvideo_gfx_generic_ops).vgfo_getcolor = &LOCAL_FUNC(libvideo_gfx_generic_getcolor);
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_FUNC(libvideo_gfx_generic_ops);
}

INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC
LOCAL_FUNC(_libvideo_gfx_generic_ops_wrap)(void) {
	if unlikely(!LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_getcolor) {
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_bitblit         = &libvideo_gfx_generic_bitblit;
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_stretch         = &libvideo_gfx_generic_stretch;
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_vgradient       = &LOCAL_FUNC(libvideo_gfx_generic_vgradient_wrap);
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_hgradient       = &LOCAL_FUNC(libvideo_gfx_generic_hgradient_wrap);
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_gradient        = &LOCAL_FUNC(libvideo_gfx_generic_gradient_wrap);
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_fillstretchmask = &LOCAL_FUNC(libvideo_gfx_generic_fillstretchmask_wrap);
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_fillmask        = &LOCAL_FUNC(libvideo_gfx_generic_fillmask_wrap);
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_rect            = &LOCAL_FUNC(libvideo_gfx_generic_rect_wrap);
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_fill            = &LOCAL_FUNC(libvideo_gfx_generic_fill_wrap);
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_vline           = &LOCAL_FUNC(libvideo_gfx_generic_vline_wrap);
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_hline           = &LOCAL_FUNC(libvideo_gfx_generic_hline_wrap);
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_line            = &LOCAL_FUNC(libvideo_gfx_generic_line_wrap);
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_putcolor        = &LOCAL_FUNC(libvideo_gfx_generic_putcolor_wrap);
		COMPILER_WRITE_BARRIER();
		LOCAL_FUNC(libvideo_gfx_generic_ops_wrap).vgfo_getcolor = &LOCAL_FUNC(libvideo_gfx_generic_getcolor_wrap);
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_FUNC(libvideo_gfx_generic_ops_wrap);
}

INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC
LOCAL_FUNC(_libvideo_gfx_generic_ops_mirror)(void) {
	if unlikely(!LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_getcolor) {
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_bitblit         = &libvideo_gfx_generic_bitblit;
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_stretch         = &libvideo_gfx_generic_stretch;
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_vgradient       = &LOCAL_FUNC(libvideo_gfx_generic_vgradient_mirror);
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_hgradient       = &LOCAL_FUNC(libvideo_gfx_generic_hgradient_mirror);
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_gradient        = &LOCAL_FUNC(libvideo_gfx_generic_gradient_mirror);
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_fillstretchmask = &LOCAL_FUNC(libvideo_gfx_generic_fillstretchmask_mirror);
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_fillmask        = &LOCAL_FUNC(libvideo_gfx_generic_fillmask_mirror);
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_rect            = &LOCAL_FUNC(libvideo_gfx_generic_rect_mirror);
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_fill            = &LOCAL_FUNC(libvideo_gfx_generic_fill_mirror);
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_vline           = &LOCAL_FUNC(libvideo_gfx_generic_vline_mirror);
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_hline           = &LOCAL_FUNC(libvideo_gfx_generic_hline_mirror);
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_line            = &LOCAL_FUNC(libvideo_gfx_generic_line_mirror);
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_putcolor        = &LOCAL_FUNC(libvideo_gfx_generic_putcolor_mirror);
		COMPILER_WRITE_BARRIER();
		LOCAL_FUNC(libvideo_gfx_generic_ops_mirror).vgfo_getcolor = &LOCAL_FUNC(libvideo_gfx_generic_getcolor_mirror);
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_FUNC(libvideo_gfx_generic_ops_mirror);
}

#define libvideo_gfx_generic_ops                 (*_libvideo_gfx_generic_ops())
#define libvideo_gfx_generic_ops_xyswap          (*_libvideo_gfx_generic_ops_xyswap())
#define libvideo_gfx_generic_ops_wrap            (*_libvideo_gfx_generic_ops_wrap())
#define libvideo_gfx_generic_ops_wrap_xyswap     (*_libvideo_gfx_generic_ops_wrap_xyswap())
#define libvideo_gfx_generic_ops_mirror          (*_libvideo_gfx_generic_ops_mirror())
#define libvideo_gfx_generic_ops_mirror_xyswap   (*_libvideo_gfx_generic_ops_mirror_xyswap())

#undef LOCAL_FUNC

DECL_END

#undef DEFINE_libvideo_gfx_generic_XXX_xyswap
#undef DEFINE_libvideo_gfx_generic_XXX
