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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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


LOCAL void CC
line_llhh(struct video_buffer_gfx *__restrict self,
          uintptr_t x, uintptr_t y,
          size_t sizex, size_t sizey,
          video_color_t color) {
	double relation;
	size_t step;
	assert(sizex != 0);
	assert(sizey != 0);
	step = 0;
	if (sizex > sizey) {
		relation = (double)sizey / (double)sizex;
		do {
			self->putcolor(x + step, y + (size_t)(relation * step), color);
		} while (++step != sizex);
	} else if (sizex < sizey) {
		relation = (double)sizex / (double)sizey;
		do {
			self->putcolor(x + (size_t)(relation * step), y + step, color);
		} while (++step != sizey);
	} else {
		do {
			self->putcolor(x + step, y + step, color);
		} while (++step != sizex);
	}
}

LOCAL void CC
line_lhhl(struct video_buffer_gfx *__restrict self,
          uintptr_t x, uintptr_t y,
          size_t sizex, size_t sizey,
          video_color_t color) {
	double relation;
	size_t step;
	assert(sizex != 0);
	assert(sizey != 0);
	step = 0;
	if (sizex > sizey) {
		relation = (double)sizey / (double)sizex;
		do {
			self->putcolor(x + step, y - (size_t)(relation * step), color);
		} while (++step != sizex);
	} else if (sizex < sizey) {
		relation = (double)sizex / (double)sizey;
		do {
			self->putcolor(x + (size_t)(relation * step), y - step, color);
		} while (++step != sizey);
	} else {
		do {
			self->putcolor(x + step, y - step, color);
		} while (++step != sizex);
	}
}


/* Default GFX functions (using get/put pixel) */
INTERN void CC
libvideo_gfx_defaultgfx_line(struct video_buffer_gfx *__restrict self,
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
	xmax = (intptr_t)(self->bfx_buffer->vb_size_x - 1);
	ymax = (intptr_t)(self->bfx_buffer->vb_size_y - 1);
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
libvideo_gfx_defaultgfx_vline(struct video_buffer_gfx *__restrict self,
                              uintptr_t x, uintptr_t from_y, uintptr_t to_y,
                              video_color_t color) {
	uintptr_t y;
	if (x >= self->bfx_buffer->vb_size_x)
		return;
	if (from_y > to_y) {
		uintptr_t temp;
		temp = from_y;
		from_y = to_y;
		to_y = temp;
	}
	if (from_y >= self->bfx_buffer->vb_size_y)
		return;
	if (to_y > self->bfx_buffer->vb_size_y)
		to_y = self->bfx_buffer->vb_size_y;
	for (y = from_y; y < to_y; ++y)
		self->putcolor(x, y, color);
}

INTERN void CC
libvideo_gfx_defaultgfx_hline(struct video_buffer_gfx *__restrict self,
                              uintptr_t y, uintptr_t from_x, uintptr_t to_x,
                              video_color_t color) {
	uintptr_t x;
	if (y >= self->bfx_buffer->vb_size_y)
		return;
	if (from_x > to_x) {
		uintptr_t temp;
		temp = from_x;
		from_x = to_x;
		to_x = temp;
	}
	if (from_x >= self->bfx_buffer->vb_size_x)
		return;
	if (to_x > self->bfx_buffer->vb_size_x)
		to_x = self->bfx_buffer->vb_size_x;
	for (x = from_x; x < to_x; ++x)
		self->putcolor(x, y, color);
}

INTERN void CC
libvideo_gfx_defaultgfx_fill(struct video_buffer_gfx *__restrict self,
                             uintptr_t x, uintptr_t y,
                             size_t size_x, size_t size_y,
                             video_color_t color) {
	uintptr_t end_x, end_y;
	uintptr_t yi;
	if unlikely(!size_x || !size_y)
		return;
	if unlikely(x >= self->bfx_buffer->vb_size_x)
		return;
	if unlikely(y >= self->bfx_buffer->vb_size_y)
		return;
	if (OVERFLOW_UADD(x, size_x, &end_x) || end_x >= self->bfx_buffer->vb_size_x)
		size_x = self->bfx_buffer->vb_size_x - x;
	if (OVERFLOW_UADD(y, size_y, &end_y) || end_y >= self->bfx_buffer->vb_size_y)
		end_y = self->bfx_buffer->vb_size_y;
	for (yi = y; yi < end_y; ++yi) {
		self->hline(yi, x, end_x, color);
	}
}

INTERN void CC
libvideo_gfx_defaultgfx_rect(struct video_buffer_gfx *__restrict self,
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
copyblit_perpixel_fixed(struct video_buffer_gfx *self,
                        uintptr_t dst_x, uintptr_t dst_y,
                        struct video_buffer_gfx const *src,
                        uintptr_t src_x, uintptr_t src_y,
                        size_t size_x, size_t size_y) {
	size_t x, y;
	for (y = 0; y < size_y; ++y) {
		for (x = 0; x < size_x; ++x) {
			video_color_t color;
			color = src->getcolor(src_x + x,
			                      src_y + y);
			self->putcolor(dst_x + x,
			               dst_y + y,
			               color);
		}
	}
}

LOCAL video_color_t CC
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
getlinearcolor(struct video_buffer_gfx const *__restrict self,
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
stretchblit_perpixel_fixed(struct video_buffer_gfx *self,
                           uintptr_t dst_x, uintptr_t dst_y,
                           size_t dst_size_x, size_t dst_size_y,
                           struct video_buffer_gfx const *src,
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
	if (self->bfx_flags & VIDEO_GFX_FLINEARBLIT) {
		for (y = 0; y < dst_size_y; ++y) {
			for (x = 0; x < dst_size_x; ++x) {
				video_color_t color;
				double src_xr, src_yr;
				src_xr = round((double)x * x_scale) + src_x;
				src_yr = round((double)y * y_scale) + src_y;
				color = getlinearcolor(src, src_xr, src_yr);
				self->putcolor(dst_x + x,
				               dst_y + y,
				               color);
			}
		}
	} else {
		for (y = 0; y < dst_size_y; ++y) {
			for (x = 0; x < dst_size_x; ++x) {
				video_color_t color;
				uintptr_t src_xr, src_yr;
				src_xr = src_x + (uintptr_t)round((double)x * x_scale);
				src_yr = src_y + (uintptr_t)round((double)y * y_scale);
				color = src->getcolor(src_xr, src_yr);
				self->putcolor(dst_x + x,
				               dst_y + y,
				               color);
			}
		}
	}
}

INTERN void CC
libvideo_gfx_defaultgfx_blit(struct video_buffer_gfx *self,
                             intptr_t dst_x, intptr_t dst_y,
                             struct video_buffer_gfx const *src,
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
	dst_sx = self->bfx_buffer->vb_size_x;
	dst_sy = self->bfx_buffer->vb_size_y;
	src_sx = src->bfx_buffer->vb_size_x;
	src_sy = src->bfx_buffer->vb_size_y;
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
libvideo_gfx_defaultgfx_stretch(struct video_buffer_gfx *self,
                                intptr_t dst_x, intptr_t dst_y,
                                size_t dst_size_x, size_t dst_size_y,
                                struct video_buffer_gfx const *src,
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
	dst_sx = self->bfx_buffer->vb_size_x;
	dst_sy = self->bfx_buffer->vb_size_y;
	src_sx = src->bfx_buffer->vb_size_x;
	src_sy = src->bfx_buffer->vb_size_y;
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



DEFINE_INTERN_WEAK_ALIAS(libvideo_gfx_ramgfx_line, libvideo_gfx_defaultgfx_line);
DEFINE_INTERN_WEAK_ALIAS(libvideo_gfx_ramgfx_vline, libvideo_gfx_defaultgfx_vline);
DEFINE_INTERN_WEAK_ALIAS(libvideo_gfx_ramgfx_hline, libvideo_gfx_defaultgfx_hline);
DEFINE_INTERN_WEAK_ALIAS(libvideo_gfx_ramgfx_fill, libvideo_gfx_defaultgfx_fill);
DEFINE_INTERN_WEAK_ALIAS(libvideo_gfx_ramgfx_rect, libvideo_gfx_defaultgfx_rect);
DEFINE_INTERN_WEAK_ALIAS(libvideo_gfx_ramgfx_blit, libvideo_gfx_defaultgfx_blit);
DEFINE_INTERN_WEAK_ALIAS(libvideo_gfx_ramgfx_stretch, libvideo_gfx_defaultgfx_stretch);



DEFINE_PUBLIC_ALIAS(video_gfx_defaultgfx_line, libvideo_gfx_defaultgfx_line);
DEFINE_PUBLIC_ALIAS(video_gfx_defaultgfx_vline, libvideo_gfx_defaultgfx_vline);
DEFINE_PUBLIC_ALIAS(video_gfx_defaultgfx_hline, libvideo_gfx_defaultgfx_hline);
DEFINE_PUBLIC_ALIAS(video_gfx_defaultgfx_fill, libvideo_gfx_defaultgfx_fill);
DEFINE_PUBLIC_ALIAS(video_gfx_defaultgfx_rect, libvideo_gfx_defaultgfx_rect);
DEFINE_PUBLIC_ALIAS(video_gfx_defaultgfx_blit, libvideo_gfx_defaultgfx_blit);
DEFINE_PUBLIC_ALIAS(video_gfx_defaultgfx_stretch, libvideo_gfx_defaultgfx_stretch);


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_C */
