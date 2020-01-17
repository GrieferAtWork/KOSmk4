/*[[[magic
// Turn on full optimizations for this file!
local opt = options.setdefault("GCC.options",[]);
opt.removeif([](e) -> e.startswith("-O"));
opt.append("-O3");
]]]*/
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVIDEO_GFX_GFX_C
#define GUARD_LIBVIDEO_GFX_GFX_C 1

#include "gfx.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <kos/types.h>

#include <assert.h>
#include <math.h>

#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "buffer.h"
#include "ram-buffer.h"

DECL_BEGIN

#define video_gfx_getabscolor(self, abs_x, abs_y) \
	(*(self)->vx_pxops.fxo_getcolor)(self, abs_x, abs_y)
#define video_gfx_putabscolor(self, abs_x, abs_y, color) \
	(*(self)->vx_pxops.fxo_putcolor)(self, abs_x, abs_y, color)


LOCAL void CC
line_llhh(struct video_gfx *__restrict self,
          uintptr_t x, uintptr_t y,
          size_t sizex, size_t sizey,
          video_color_t color) {
	double relation;
	size_t step;
	assert(sizex != 0);
	assert(sizey != 0);
	step = 0;
	if (sizex > sizey) {
		do {
			video_gfx_putabscolor(self,
			                      x + step,
			                      y + (size_t)(((uint64_t)sizey * step) / sizex),
			                      color);
		} while (++step != sizex);
	} else if (sizex < sizey) {
		do {
			video_gfx_putabscolor(self,
			                      x + (size_t)(((uint64_t)sizex * step) / sizey),
			                      y + step,
			                      color);
		} while (++step != sizey);
	} else {
		do {
			video_gfx_putabscolor(self,
			                      x + step,
			                      y + step,
			                      color);
		} while (++step != sizex);
	}
}

LOCAL void CC
line_lhhl(struct video_gfx *__restrict self,
          uintptr_t x, uintptr_t y,
          size_t sizex, size_t sizey,
          video_color_t color) {
	size_t step;
	assert(sizex != 0);
	assert(sizey != 0);
	step = 0;
	if (sizex > sizey) {
		do {
			video_gfx_putabscolor(self,
			                      x + step,
			                      (size_t)(((uint64_t)sizey * step) / sizex),
			                      color);
		} while (++step != sizex);
	} else if (sizex < sizey) {
		do {
			video_gfx_putabscolor(self,
			                      x + (size_t)(((uint64_t)sizex * step) / sizey),
			                      y - step,
			                      color);
		} while (++step != sizey);
	} else {
		do {
			video_gfx_putabscolor(self,
			                      x + step,
			                      y - step,
			                      color);
		} while (++step != sizex);
	}
}


/* Default GFX functions (using get/put pixel) */
INTERN void CC
libvideo_gfx_defaultgfx_line(struct video_gfx *__restrict self,
                             intptr_t x1, intptr_t y1,
                             intptr_t x2, intptr_t y2,
                             video_color_t color) {
	/* >> Cohen-Sutherland algorithm
	 * https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm */
	intptr_t xmax, ymax, temp, x, y;
	int outcode0, outcode1, outcodeOut;
#define COHSUTH_INSIDE 0 /* 0000 */
#define COHSUTH_XMIN   1 /* 0001 */
#define COHSUTH_XMAX   2 /* 0010 */
#define COHSUTH_YMIN   4 /* 0100 */
#define COHSUTH_YMAX   8 /* 1000 */
	xmax = (intptr_t)(self->vx_size_x - 1);
	ymax = (intptr_t)(self->vx_size_y - 1);
#define COHSUTH_COMPUTEOUTCODE(x, y, result) \
	do {                                     \
		(result) = COHSUTH_INSIDE;           \
		if ((x) < 0)                         \
			(result) |= COHSUTH_XMIN;        \
		else if ((x) > xmax)                 \
			(result) |= COHSUTH_XMAX;        \
		if ((y) < 0)                         \
			(result) |= COHSUTH_YMIN;        \
		else if ((y) > ymax)                 \
			(result) |= COHSUTH_YMAX;        \
	} __WHILE0
	COHSUTH_COMPUTEOUTCODE(x1, y1, outcode0);
	COHSUTH_COMPUTEOUTCODE(x2, y2, outcode1);
	while ((outcode0 | outcode1) != 0) {
		if ((outcode0 & outcode1) != 0)
			return;
		outcodeOut = outcode0 ? outcode0 : outcode1;
		if ((outcodeOut & COHSUTH_YMAX) != 0)
			x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1), y = ymax;
		else if ((outcodeOut & COHSUTH_YMIN) != 0)
			x = x1 + (x2 - x1) * (0 - y1) / (y2 - y1), y = 0;
		else if ((outcodeOut & COHSUTH_XMAX) != 0)
			y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1), x = xmax;
		else /*if ((outcodeOut & COHSUTH_XMIN) != 0)*/
			y = y1 + (y2 - y1) * (0 - x1) / (x2 - x1), x = 0;
		if (outcodeOut == outcode0) {
			x1 = x, y1 = y;
			COHSUTH_COMPUTEOUTCODE(x1, y1, outcode0);
		} else {
			x2 = x, y2 = y;
			COHSUTH_COMPUTEOUTCODE(x2, y2, outcode1);
		}
	}
	/* Coords are clamped! --> Now select the proper line algorithm */
	if (x1 > x2) {
		temp = x2, x2 = x1, x1 = temp;
		temp = y2, y2 = y1, y1 = temp;
	} else if (x2 == x1) {
		if (y1 > y2)
			temp = y2, y2 = y1, y1 = temp;
		else if (y2 == y1)
			return;
		self->vline(x1, y1, y2, color);
		return;
	}
	if (y2 > y1) {
		line_llhh(self, (size_t)x1, (size_t)y1,
		          (size_t)(x2 - x1) + 1,
		          (size_t)(y2 - y1) + 1, color);
	} else if (y2 < y1) {
		line_lhhl(self, (size_t)x1, (size_t)y1,
		          (size_t)(x2 - x1) + 1,
		          (size_t)(y1 - y2) + 1, color);
	} else if (x1 != x2) {
		self->hline(y1, x1, x2, color);
	}
#undef COHSUTH_COMPUTEOUTCODE
#undef COHSUTH_INSIDE
#undef COHSUTH_XMIN
#undef COHSUTH_XMAX
#undef COHSUTH_YMIN
#undef COHSUTH_YMAX
}


INTERN void CC
libvideo_gfx_defaultgfx_vline(struct video_gfx *__restrict self,
                              uintptr_t x, uintptr_t from_y, uintptr_t to_y,
                              video_color_t color) {
	uintptr_t y;
	if (x >= self->vx_size_x)
		return;
	if (from_y > to_y) {
		uintptr_t temp;
		temp = from_y;
		from_y = to_y;
		to_y = temp;
	}
	if (from_y >= self->vx_size_y)
		return;
	if (to_y > self->vx_size_y)
		to_y = self->vx_size_y;
	for (y = from_y; y < to_y; ++y) {
		video_gfx_putabscolor(self,
		                      x,
		                      y,
		                      color);
	}
}

INTERN void CC
libvideo_gfx_defaultgfx_hline(struct video_gfx *__restrict self,
                              uintptr_t y, uintptr_t from_x, uintptr_t to_x,
                              video_color_t color) {
	uintptr_t x;
	if (y >= self->vx_size_y)
		return;
	if (from_x > to_x) {
		uintptr_t temp;
		temp = from_x;
		from_x = to_x;
		to_x = temp;
	}
	if (from_x >= self->vx_size_x)
		return;
	if (to_x > self->vx_size_x)
		to_x = self->vx_size_x;
	for (x = from_x; x < to_x; ++x) {
		video_gfx_putabscolor(self,
		                      x,
		                      y,
		                      color);
	}
}

INTERN void CC
libvideo_gfx_defaultgfx_fill(struct video_gfx *__restrict self,
                             uintptr_t x, uintptr_t y,
                             size_t size_x, size_t size_y,
                             video_color_t color) {
	uintptr_t end_x, end_y;
	uintptr_t yi;
	if unlikely(!size_x || !size_y)
		return;
	if unlikely(x >= self->vx_size_x)
		return;
	if unlikely(y >= self->vx_size_y)
		return;
	if (OVERFLOW_UADD(x, size_x, &end_x) || end_x >= self->vx_size_x)
		size_x = self->vx_size_x - x;
	if (OVERFLOW_UADD(y, size_y, &end_y) || end_y >= self->vx_size_y)
		end_y = self->vx_size_y;
	for (yi = y; yi < end_y; ++yi) {
		self->hline(yi, x, end_x, color);
	}
}

INTERN void CC
libvideo_gfx_defaultgfx_rect(struct video_gfx *__restrict self,
                             uintptr_t x, uintptr_t y,
                             size_t size_x, size_t size_y,
                             video_color_t color) {
	self->hline(y, x, (uintptr_t)(x + size_x), color);
	self->hline((uintptr_t)(y + size_y), x, (uintptr_t)(x + size_x), color);
	if (size_y > 2) {
		self->vline(x, y + 1, (uintptr_t)(y + size_y) - 1, color);
		self->vline((uintptr_t)(x + size_x), y + 1, (uintptr_t)(y + size_y) - 1, color);
	}
}

LOCAL void CC
copyblit_perpixel_fixed(struct video_gfx *self,
                        uintptr_t dst_x, uintptr_t dst_y,
                        struct video_gfx const *src,
                        uintptr_t src_x, uintptr_t src_y,
                        size_t size_x, size_t size_y) {
	size_t x, y;
	src_x += src->vx_offt_x;
	src_y += src->vx_offt_y;
	for (y = 0; y < size_y; ++y) {
		for (x = 0; x < size_x; ++x) {
			video_color_t color;
			color = video_gfx_getabscolor(src,
			                              src_x + x,
			                              src_y + y);
			video_gfx_putabscolor(self,
			                      dst_x + x,
			                      dst_y + y,
			                      color);
		}
	}
}

LOCAL ATTR_CONST video_color_t CC
colorfactor(video_color_t color, double part) {
	uint8_t r, g, b, a;
	/* Load color channels. */
	r = VIDEO_COLOR_GET_RED(color);
	g = VIDEO_COLOR_GET_GREEN(color);
	b = VIDEO_COLOR_GET_BLUE(color);
	a = VIDEO_COLOR_GET_ALPHA(color);
	/* Apply color parts */
	r = (uint8_t)(part * r);
	g = (uint8_t)(part * g);
	b = (uint8_t)(part * b);
	a = (uint8_t)(part * a);
	/* Pack the color back together. */
	return VIDEO_COLOR_RGBA(r, g, b, a);
}

LOCAL video_color_t CC
getlinearcolor(struct video_gfx const *__restrict self,
               double x, double y) {
	video_color_t result;
	video_color_t c[2][2];
	uintptr_t base_x, base_y;
	double rel_x, rel_y;
	base_x = (uintptr_t)x;
	base_y = (uintptr_t)y;
	/* Load source colors. */
	c[0][0] = self->getcolor(base_x + 0, base_y + 0);
	c[0][1] = self->getcolor(base_x + 0, base_y + 1);
	c[1][0] = self->getcolor(base_x + 1, base_y + 0);
	c[1][1] = self->getcolor(base_x + 1, base_y + 1);
	/* Figure out the sub-pixel relation. */
	rel_x = x - (double)base_x;
	rel_y = y - (double)base_y;
	/* Calculate color affinity */
	result  = colorfactor(c[0][0], (rel_x + rel_y) / 2.0);
	result += colorfactor(c[0][1], (rel_x + (1.0 - rel_y)) / 2.0);
	result += colorfactor(c[1][0], ((1.0 - rel_x) + rel_y) / 2.0);
	result += colorfactor(c[1][1], ((1.0 - rel_x) + (1.0 - rel_y)) / 2.0);
	return result;
}



LOCAL void CC
stretchblit_perpixel_fixed(struct video_gfx *self,
                           uintptr_t dst_x, uintptr_t dst_y,
                           size_t dst_size_x, size_t dst_size_y,
                           struct video_gfx const *src,
                           uintptr_t src_x, uintptr_t src_y,
                           size_t src_size_x, size_t src_size_y) {
	size_t x, y;
	double x_scale, y_scale;
	assert(dst_size_x != 0);
	assert(dst_size_y != 0);
	assert(src_size_x != 0);
	assert(src_size_y != 0);
	x_scale = (double)src_size_x / (double)dst_size_x;
	y_scale = (double)src_size_y / (double)dst_size_y;
	if (self->vx_flags & VIDEO_GFX_FLINEARBLIT) {
		for (y = 0; y < dst_size_y; ++y) {
			for (x = 0; x < dst_size_x; ++x) {
				video_color_t color;
				double src_xr, src_yr;
				src_xr = round((double)x * x_scale) + src_x;
				src_yr = round((double)y * y_scale) + src_y;
				color = getlinearcolor(src, src_xr, src_yr);
				video_gfx_putabscolor(self,
				                      dst_x + x,
				                      dst_y + y,
				                      color);
			}
		}
	} else {
		src_x += src->vx_offt_x;
		src_y += src->vx_offt_y;
		for (y = 0; y < dst_size_y; ++y) {
			for (x = 0; x < dst_size_x; ++x) {
				video_color_t color;
				uintptr_t src_xr, src_yr;
				src_xr = src_x + (uintptr_t)round((double)x * x_scale);
				src_yr = src_y + (uintptr_t)round((double)y * y_scale);
				color = video_gfx_getabscolor(src,
				                              src_xr,
				                              src_yr);
				video_gfx_putabscolor(self, dst_x + x,
				                      dst_y + y,
				                      color);
			}
		}
	}
}

INTERN void CC
libvideo_gfx_defaultgfx_blit(struct video_gfx *self,
                             intptr_t dst_x, intptr_t dst_y,
                             struct video_gfx const *src,
                             intptr_t src_x, intptr_t src_y,
                             size_t size_x, size_t size_y) {
	size_t dst_sx, dst_sy;
	size_t src_sx, src_sy;
	uintptr_t temp;
	if (!size_x || !size_y)
		return;
	if (dst_x < 0) {
		if unlikely((uintptr_t)(-dst_x) >= size_x)
			return;
		src_x += (uintptr_t)-dst_x;
		size_x -= (uintptr_t)-dst_x;
		dst_x = 0;
	}
	if (dst_y < 0) {
		if unlikely((uintptr_t)(-dst_y) >= size_y)
			return;
		src_y += (uintptr_t)-dst_x;
		size_y -= (uintptr_t)-dst_y;
		dst_y = 0;
	}
	if (src_x < 0) {
		if unlikely((uintptr_t)(-src_x) >= size_x)
			return;
		dst_x += (uintptr_t)-src_x;
		size_x -= (uintptr_t)-src_x;
		src_x = 0;
	}
	if (src_y < 0) {
		if unlikely((uintptr_t)(-src_y) >= size_y)
			return;
		dst_y += (uintptr_t)-src_y;
		size_y -= (uintptr_t)-src_y;
		src_y = 0;
	}
	dst_sx = self->vx_size_x;
	dst_sy = self->vx_size_y;
	src_sx = src->vx_size_x;
	src_sy = src->vx_size_y;
	/* Check for out-of-bounds rendering */
	if unlikely((uintptr_t)dst_x >= dst_sx)
		return;
	if unlikely((uintptr_t)dst_y >= dst_sy)
		return;
	if unlikely((uintptr_t)src_x >= src_sx)
		return;
	if unlikely((uintptr_t)src_y >= src_sy)
		return;
	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_x, size_x, &temp) || temp > dst_sx)
		size_x = dst_sx - (uintptr_t)dst_x;
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_y, size_y, &temp) || temp > dst_sy)
		size_y = dst_sy - (uintptr_t)dst_y;
	if unlikely(OVERFLOW_UADD((uintptr_t)src_x, size_x, &temp) || temp > src_sx)
		size_x = src_sx - (uintptr_t)src_x;
	if unlikely(OVERFLOW_UADD((uintptr_t)src_y, size_y, &temp) || temp > src_sy)
		size_y = src_sy - (uintptr_t)src_y;
	copyblit_perpixel_fixed(self, (uintptr_t)dst_x, (uintptr_t)dst_y,
	                        src, (uintptr_t)src_x, (uintptr_t)src_y,
	                        size_x, size_y);
}



INTERN void CC
libvideo_gfx_defaultgfx_stretch(struct video_gfx *self,
                                intptr_t dst_x, intptr_t dst_y,
                                size_t dst_size_x, size_t dst_size_y,
                                struct video_gfx const *src,
                                intptr_t src_x, intptr_t src_y,
                                size_t src_size_x, size_t src_size_y) {
	size_t dst_sx, dst_sy;
	size_t src_sx, src_sy;
	uintptr_t temp;
	if (!dst_size_x || !dst_size_y || !src_size_x || !src_size_y)
		return;
	if (dst_x < 0) {
		double portion;
		size_t srcpart;
		dst_x = -dst_x;
		if unlikely((uintptr_t)dst_x >= dst_size_x)
			return;
		portion = (double)(uintptr_t)dst_x / (double)dst_size_x;
		srcpart = (size_t)(portion * (double)src_size_x);
		src_x += srcpart;
		src_size_x -= srcpart;
		if unlikely(!src_size_x)
			return;
		dst_size_x -= (uintptr_t)dst_x;
		dst_x = 0;
	}
	if (dst_y < 0) {
		double portion;
		size_t srcpart;
		dst_y = -dst_y;
		if unlikely((uintptr_t)dst_y >= dst_size_y)
			return;
		portion = (double)(uintptr_t)dst_y / (double)dst_size_y;
		srcpart = (size_t)(portion * (double)src_size_y);
		src_y += srcpart;
		src_size_y -= srcpart;
		if unlikely(!src_size_y)
			return;
		dst_size_y -= (uintptr_t)dst_y;
		dst_y = 0;
	}
	if (src_x < 0) {
		double portion;
		size_t dstpart;
		src_x = -src_x;
		if unlikely((uintptr_t)src_x >= src_size_x)
			return;
		portion = (double)(uintptr_t)src_x / (double)src_size_x;
		dstpart = (size_t)(portion * (double)dst_size_x);
		dst_x += dstpart;
		dst_size_x -= dstpart;
		if unlikely(!dst_size_x)
			return;
		src_size_x -= (uintptr_t)src_x;
		src_x = 0;
	}
	if (src_y < 0) {
		double portion;
		size_t dstpart;
		src_y = -src_y;
		if unlikely((uintptr_t)src_y >= src_size_y)
			return;
		portion = (double)(uintptr_t)src_y / (double)src_size_y;
		dstpart = (size_t)(portion * (double)dst_size_y);
		dst_y += dstpart;
		dst_size_y -= dstpart;
		if unlikely(!dst_size_y)
			return;
		src_size_y -= (uintptr_t)src_y;
		src_y = 0;
	}
	dst_sx = self->vx_size_x;
	dst_sy = self->vx_size_y;
	src_sx = src->vx_size_x;
	src_sy = src->vx_size_y;
	/* Check for out-of-bounds rendering */
	if unlikely((uintptr_t)dst_x >= dst_sx)
		return;
	if unlikely((uintptr_t)dst_y >= dst_sy)
		return;
	if unlikely((uintptr_t)src_x >= src_sx)
		return;
	if unlikely((uintptr_t)src_y >= src_sy)
		return;
	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_x, dst_size_x, &temp) || temp > dst_sx) {
		size_t overflow = (size_t)(temp - dst_sx);
		assert(overflow < dst_size_x);
		double portion = (double)overflow / (double)dst_size_x;
		src_size_x -= (size_t)(portion * (double)src_size_x);
		if unlikely(!src_size_x)
			return;
		dst_size_x = dst_sx - (uintptr_t)dst_x;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_y, dst_size_y, &temp) || temp > dst_sy) {
		size_t overflow = (size_t)(temp - dst_sy);
		assert(overflow < dst_size_y);
		double portion = (double)overflow / (double)dst_size_y;
		src_size_y -= (size_t)(portion * (double)src_size_y);
		if unlikely(!src_size_y)
			return;
		dst_size_y = dst_sy - (uintptr_t)dst_y;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)src_x, src_size_x, &temp) || temp > src_sx) {
		size_t overflow = (size_t)(temp - src_sx);
		assert(overflow < src_size_x);
		double portion = (double)overflow / (double)src_size_x;
		dst_size_x -= (size_t)(portion * (double)dst_size_x);
		if unlikely(!dst_size_x)
			return;
		src_size_x = src_sx - (uintptr_t)src_x;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)src_y, src_size_y, &temp) || temp > src_sy) {
		size_t overflow = (size_t)(temp - src_sy);
		assert(overflow < src_size_y);
		double portion = (double)overflow / (double)src_size_y;
		dst_size_y -= (size_t)(portion * (double)dst_size_y);
		if unlikely(!dst_size_y)
			return;
		src_size_y = src_sy - (uintptr_t)src_y;
	}
	if (dst_size_x == src_size_x &&
	    dst_size_y == src_size_y) {
		/* Can use copy-blit */
		copyblit_perpixel_fixed(self,
		                        (uintptr_t)dst_x,
		                        (uintptr_t)dst_y,
		                        src,
		                        (uintptr_t)src_x,
		                        (uintptr_t)src_y,
		                        dst_size_x,
		                        dst_size_y);
	} else {
		/* Must use stretch-blit */
		stretchblit_perpixel_fixed(self,
		                           (uintptr_t)dst_x,
		                           (uintptr_t)dst_y,
		                           dst_size_x,
		                           dst_size_y,
		                           src,
		                           (uintptr_t)src_x,
		                           (uintptr_t)src_y,
		                           src_size_x,
		                           src_size_y);
	}
}

LOCAL void CC
fillbitblit_perpixel(struct video_gfx *self,
                     uintptr_t dst_x, uintptr_t dst_y,
                     size_t size_x, size_t size_y,
                     video_color_t color,
                     void const *__restrict bitmask,
                     size_t bitmask_base_offset,
                     size_t bitmask_size_x) {
	size_t x, y;
	if (bitmask_base_offset == 0 && bitmask_size_x == size_x) {
		uint8_t byte, bits = 0;
		for (y = 0; y < size_y; ++y) {
			for (x = 0; x < size_x; ++x) {
				uint8_t bit;
				if (!bits) {
					byte    = *(uint8_t *)bitmask;
					bitmask = (uint8_t *)bitmask + 1;
					bits    = 8;
				}
				--bits;
				bit = byte & 1;
				byte >>= 1;
				if (!bit)
					continue;
				video_gfx_putabscolor(self,
				                      dst_x + x,
				                      dst_y + y,
				                      color);
			}
		}
	} else {
		for (y = 0; y < size_y; ++y) {
			for (x = 0; x < size_x; ++x) {
				size_t bitno;
				uint8_t byte;
				bitno = bitmask_base_offset + y * bitmask_size_x + x;
				byte = ((uint8_t *)bitmask)[bitno / 8];
				if (!(byte & (bitno % 8)))
					continue;
				video_gfx_putabscolor(self,
				                      dst_x + x,
				                      dst_y + y,
				                      color);
			}
		}
	}
}

INTERN void CC
libvideo_gfx_defaultgfx_bitfill(struct video_gfx *__restrict self,
                                intptr_t dst_x, intptr_t dst_y,
                                size_t dst_size_x, size_t dst_size_y,
                                video_color_t color,
                                void const *__restrict bitmask) {
	size_t dst_sx, dst_sy;
	uintptr_t temp;
	size_t bitmask_base_offset;
	size_t bitmask_size_x;
	if (!dst_size_x || !dst_size_y)
		return;
	bitmask_base_offset = 0;
	bitmask_size_x = dst_size_x;
	if (dst_x < 0) {
		if unlikely((uintptr_t)(-dst_x) >= dst_size_x)
			return;
		bitmask_base_offset = (uintptr_t)-dst_x;
		dst_size_x -= (uintptr_t)-dst_x;
		dst_x = 0;
	}
	if (dst_y < 0) {
		if unlikely((uintptr_t)(-dst_y) >= dst_size_y)
			return;
		bitmask_base_offset += ((uintptr_t)-dst_y) * bitmask_size_x;
		dst_size_y -= (uintptr_t)-dst_y;
		dst_y = 0;
	}
	dst_sx = self->vx_size_x;
	dst_sy = self->vx_size_y;
	/* Check for out-of-bounds rendering */
	if unlikely((uintptr_t)dst_x >= dst_sx)
		return;
	if unlikely((uintptr_t)dst_y >= dst_sy)
		return;
	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_x, dst_size_x, &temp) || temp > dst_sx)
		dst_size_x = dst_sx - (uintptr_t)dst_x;
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_y, dst_size_y, &temp) || temp > dst_sy)
		dst_size_y = dst_sy - (uintptr_t)dst_y;
	fillbitblit_perpixel(self, (uintptr_t)dst_x, (uintptr_t)dst_y,
	                     dst_size_x, dst_size_y,
	                     color, bitmask,
	                     bitmask_base_offset,
	                     bitmask_size_x);
}

LOCAL void CC
copybitblit_perpixel_fixed(struct video_gfx *self,
                           uintptr_t dst_x, uintptr_t dst_y,
                           struct video_gfx const *src,
                           uintptr_t src_x, uintptr_t src_y,
                           size_t size_x, size_t size_y,
                           void const *__restrict bitmask,
                           size_t bitmask_base_offset,
                           size_t bitmask_size_x) {
	size_t x, y;
	src_x += src->vx_offt_x;
	src_y += src->vx_offt_y;
	if (bitmask_base_offset == 0 && bitmask_size_x == size_x) {
		uint8_t byte, bits = 0;
		for (y = 0; y < size_y; ++y) {
			for (x = 0; x < size_x; ++x) {
				video_color_t color;
				uint8_t bit;
				if (!bits) {
					byte    = *(uint8_t *)bitmask;
					bitmask = (uint8_t *)bitmask + 1;
					bits    = 8;
				}
				--bits;
				bit = byte & 1;
				byte >>= 1;
				if (!bit)
					continue;
				color = video_gfx_getabscolor(src,
				                              src_x + x,
				                              src_y + y);
				video_gfx_putabscolor(self,
				                      dst_x + x,
				                      dst_y + y,
				                      color);
			}
		}
	} else {
		for (y = 0; y < size_y; ++y) {
			for (x = 0; x < size_x; ++x) {
				video_color_t color;
				size_t bitno;
				uint8_t byte;
				bitno = bitmask_base_offset + y * bitmask_size_x + x;
				byte = ((uint8_t *)bitmask)[bitno / 8];
				if (!(byte & (bitno % 8)))
					continue;
				color = video_gfx_getabscolor(src,
				                              src_x + x,
				                              src_y + y);
				video_gfx_putabscolor(self,
				                      dst_x + x,
				                      dst_y + y,
				                      color);
			}
		}
	}
}

INTERN void CC
libvideo_gfx_defaultgfx_bitblit(struct video_gfx *self,
                                intptr_t dst_x, intptr_t dst_y,
                                struct video_gfx const *src,
                                intptr_t src_x, intptr_t src_y,
                                size_t size_x, size_t size_y,
                                void const *__restrict bitmask) {
	size_t dst_sx, dst_sy;
	size_t src_sx, src_sy;
	uintptr_t temp;
	size_t bitmask_base_offset;
	size_t bitmask_size_x;
	if (!size_x || !size_y)
		return;
	bitmask_base_offset = 0;
	bitmask_size_x = size_x;
	if (dst_x < 0) {
		if unlikely((uintptr_t)(-dst_x) >= size_x)
			return;
		bitmask_base_offset = (uintptr_t)-dst_x;
		src_x += (uintptr_t)-dst_x;
		size_x -= (uintptr_t)-dst_x;
		dst_x = 0;
	}
	if (dst_y < 0) {
		if unlikely((uintptr_t)(-dst_y) >= size_y)
			return;
		bitmask_base_offset += ((uintptr_t)-dst_y) * bitmask_size_x;
		src_y += (uintptr_t)-dst_y;
		size_y -= (uintptr_t)-dst_y;
		dst_y = 0;
	}
	if (src_x < 0) {
		if unlikely((uintptr_t)(-src_x) >= size_x)
			return;
		bitmask_base_offset += (uintptr_t)-src_x;
		dst_x += (uintptr_t)-src_x;
		size_x -= (uintptr_t)-src_x;
		src_x = 0;
	}
	if (src_y < 0) {
		if unlikely((uintptr_t)(-src_y) >= size_y)
			return;
		bitmask_base_offset += ((uintptr_t)-src_y) * bitmask_size_x;
		dst_y += (uintptr_t)-src_y;
		size_y -= (uintptr_t)-src_y;
		src_y = 0;
	}
	dst_sx = self->vx_size_x;
	dst_sy = self->vx_size_y;
	src_sx = src->vx_size_x;
	src_sy = src->vx_size_y;
	/* Check for out-of-bounds rendering */
	if unlikely((uintptr_t)dst_x >= dst_sx)
		return;
	if unlikely((uintptr_t)dst_y >= dst_sy)
		return;
	if unlikely((uintptr_t)src_x >= src_sx)
		return;
	if unlikely((uintptr_t)src_y >= src_sy)
		return;
	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_x, size_x, &temp) || temp > dst_sx)
		size_x = dst_sx - (uintptr_t)dst_x;
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_y, size_y, &temp) || temp > dst_sy)
		size_y = dst_sy - (uintptr_t)dst_y;
	if unlikely(OVERFLOW_UADD((uintptr_t)src_x, size_x, &temp) || temp > src_sx)
		size_x = src_sx - (uintptr_t)src_x;
	if unlikely(OVERFLOW_UADD((uintptr_t)src_y, size_y, &temp) || temp > src_sy)
		size_y = src_sy - (uintptr_t)src_y;
	copybitblit_perpixel_fixed(self, (uintptr_t)dst_x, (uintptr_t)dst_y,
	                           src, (uintptr_t)src_x, (uintptr_t)src_y,
	                           size_x, size_y, bitmask,
	                           bitmask_base_offset,
	                           bitmask_size_x);
}


/* Same as the functions above, but these take `vx_offt_(x|y)' into account. */
INTERN void CC
libvideo_gfx_defaultgfx_line_o(struct video_gfx *__restrict self,
                               intptr_t x1, intptr_t y1,
                               intptr_t x2, intptr_t y2,
                               video_color_t color) {
	libvideo_gfx_defaultgfx_line(self,
	                             x1 + self->vx_offt_x,
	                             y1 + self->vx_offt_y,
	                             x2 + self->vx_offt_x,
	                             y2 + self->vx_offt_y,
	                             color);
}

INTERN void CC
libvideo_gfx_defaultgfx_vline_o(struct video_gfx *__restrict self,
                                uintptr_t x, uintptr_t y1, uintptr_t y2,
                                video_color_t color) {
	libvideo_gfx_defaultgfx_vline(self,
	                              x + self->vx_offt_x,
	                              y1 + self->vx_offt_y,
	                              y2 + self->vx_offt_y,
	                              color);
}

INTERN void CC
libvideo_gfx_defaultgfx_hline_o(struct video_gfx *__restrict self,
                                uintptr_t y, uintptr_t x1, uintptr_t x2,
                                video_color_t color) {
	libvideo_gfx_defaultgfx_hline(self,
	                              y + self->vx_offt_y,
	                              x1 + self->vx_offt_x,
	                              x2 + self->vx_offt_x,
	                              color);
}

INTERN void CC
libvideo_gfx_defaultgfx_fill_o(struct video_gfx *__restrict self,
                               uintptr_t x, uintptr_t y,
                               size_t size_x, size_t size_y,
                               video_color_t color) {
	libvideo_gfx_defaultgfx_fill(self,
	                             x + self->vx_offt_x,
	                             y + self->vx_offt_y,
	                             size_x,
	                             size_y,
	                             color);
}

INTERN void CC
libvideo_gfx_defaultgfx_rect_o(struct video_gfx *__restrict self,
                               uintptr_t x, uintptr_t y,
                               size_t size_x, size_t size_y,
                               video_color_t color) {
	libvideo_gfx_defaultgfx_fill(self,
	                             x + self->vx_offt_x,
	                             y + self->vx_offt_y,
	                             size_x,
	                             size_y,
	                             color);
}

INTERN void CC
libvideo_gfx_defaultgfx_blit_o(struct video_gfx *self,
                               intptr_t dst_x, intptr_t dst_y,
                               struct video_gfx const *src,
                               intptr_t src_x, intptr_t src_y,
                               size_t size_x, size_t size_y) {
	libvideo_gfx_defaultgfx_blit(self,
	                             dst_x + self->vx_offt_x,
	                             dst_y + self->vx_offt_y,
	                             src,
	                             src_x,
	                             src_y,
	                             size_x,
	                             size_y);
}

INTERN void CC
libvideo_gfx_defaultgfx_stretch_o(struct video_gfx *self,
                                  intptr_t dst_x, intptr_t dst_y,
                                  size_t dst_size_x, size_t dst_size_y,
                                  struct video_gfx const *src,
                                  intptr_t src_x, intptr_t src_y,
                                  size_t src_size_x, size_t src_size_y) {
	libvideo_gfx_defaultgfx_stretch(self,
	                                dst_x + self->vx_offt_x,
	                                dst_y + self->vx_offt_y,
	                                dst_size_x,
	                                dst_size_y,
	                                src,
	                                src_x,
	                                src_y,
	                                src_size_x,
	                                src_size_y);
}

INTERN void CC
libvideo_gfx_defaultgfx_bitfill_o(struct video_gfx *__restrict self,
                                  intptr_t x, intptr_t y,
                                  size_t size_x, size_t size_y,
                                  video_color_t color,
                                  void const *__restrict bitmask) {
	libvideo_gfx_defaultgfx_bitfill(self,
	                                x + self->vx_offt_x,
	                                y + self->vx_offt_y,
	                                size_x,
	                                size_y,
	                                color,
	                                bitmask);
}

INTERN void CC
libvideo_gfx_defaultgfx_bitblit_o(struct video_gfx *self,
                                  intptr_t dst_x, intptr_t dst_y,
                                  struct video_gfx const *src,
                                  intptr_t src_x, intptr_t src_y,
                                  size_t size_x, size_t size_y,
                                  void const *__restrict bitmask) {
	libvideo_gfx_defaultgfx_bitblit(self,
	                                dst_x + self->vx_offt_x,
	                                dst_y + self->vx_offt_y,
	                                src,
	                                src_x,
	                                src_y,
	                                size_x,
	                                size_y,
	                                bitmask);
}


PRIVATE struct video_gfx_ops libvideo_gfx_defaultgfx_ops = {};
INTERN ATTR_PURE ATTR_RETNONNULL WUNUSED
struct video_gfx_ops *CC libvideo_gfx_defaultgfx_getops(void) {
	if (!libvideo_gfx_defaultgfx_ops.fxo_line) {
		libvideo_gfx_defaultgfx_ops.fxo_vline   = &libvideo_gfx_defaultgfx_vline;
		libvideo_gfx_defaultgfx_ops.fxo_hline   = &libvideo_gfx_defaultgfx_hline;
		libvideo_gfx_defaultgfx_ops.fxo_fill    = &libvideo_gfx_defaultgfx_fill;
		libvideo_gfx_defaultgfx_ops.fxo_rect    = &libvideo_gfx_defaultgfx_rect;
		libvideo_gfx_defaultgfx_ops.fxo_blit    = &libvideo_gfx_defaultgfx_blit;
		libvideo_gfx_defaultgfx_ops.fxo_stretch = &libvideo_gfx_defaultgfx_stretch;
		libvideo_gfx_defaultgfx_ops.fxo_bitfill = &libvideo_gfx_defaultgfx_bitfill;
		libvideo_gfx_defaultgfx_ops.fxo_bitblit = &libvideo_gfx_defaultgfx_bitblit;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_defaultgfx_ops.fxo_line = &libvideo_gfx_defaultgfx_line;
	}
	return &libvideo_gfx_defaultgfx_ops;
}

PRIVATE struct video_gfx_ops libvideo_gfx_defaultgfx_ops_o = {};
INTERN ATTR_PURE ATTR_RETNONNULL WUNUSED
struct video_gfx_ops *CC libvideo_gfx_defaultgfx_getops_o(void) {
	if (!libvideo_gfx_defaultgfx_ops_o.fxo_line) {
		libvideo_gfx_defaultgfx_ops_o.fxo_vline   = &libvideo_gfx_defaultgfx_vline_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_hline   = &libvideo_gfx_defaultgfx_hline_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_fill    = &libvideo_gfx_defaultgfx_fill_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_rect    = &libvideo_gfx_defaultgfx_rect_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_blit    = &libvideo_gfx_defaultgfx_blit_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_stretch = &libvideo_gfx_defaultgfx_stretch_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_bitfill = &libvideo_gfx_defaultgfx_bitfill_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_bitblit = &libvideo_gfx_defaultgfx_bitblit_o;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_defaultgfx_ops_o.fxo_line = &libvideo_gfx_defaultgfx_line_o;
	}
	return &libvideo_gfx_defaultgfx_ops_o;
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_C */
