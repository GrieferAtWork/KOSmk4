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
#ifdef __INTELLISENSE__
#include "gfx.c"
//#define DEFINE_STRETCH 1
#define DEFINE_BITSTRETCHBLIT 1
//#define DEFINE_BITSTRETCHFILL 1
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_STRETCH) + defined(DEFINE_BITSTRETCHBLIT) + defined(DEFINE_BITSTRETCHFILL)) != 1
#error "Must #define exactly one of `DEFINE_STRETCH' or `DEFINE_BITSTRETCHBLIT' or `DEFINE_BITSTRETCHFILL'"
#endif

DECL_BEGIN

#ifdef DEFINE_STRETCH
#define FUNC(x)         x##_stretch
#define IF_BLIT(...)    __VA_ARGS__
#define IF_BITBLIT(...) /* nothing */
#elif defined(DEFINE_BITSTRETCHBLIT)
#define FUNC(x)         x##_bitstretchblit
#define IF_BLIT(...)    /* nothing */
#define IF_BITBLIT(...) __VA_ARGS__
#else /* DEFINE_STRETCH */
#define FUNC(x)         x##_bitstretchfill
#define IF_BLIT(...)    /* nothing */
#define IF_BITBLIT(...) __VA_ARGS__
#endif /* !DEFINE_STRETCH */


#ifndef DEFINE_BITSTRETCHFILL
#ifndef COLORFACTOR_DEFINED
#define COLORFACTOR_DEFINED 1
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
#endif /* !COLORFACTOR_DEFINED */

#ifndef GETLINEARCOLOR_DEFINED
#define GETLINEARCOLOR_DEFINED 1
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
#endif /* !GETLINEARCOLOR_DEFINED */
#endif /* !DEFINE_BITSTRETCHFILL */

#ifndef DEFINE_STRETCH
#ifndef BITFACTOR_DEFINED
#define BITFACTOR_DEFINED 1
LOCAL ATTR_CONST uint8_t CC
bitfactor(bool bit, double part) {
	return (uint8_t)((double)(bit ? 0xff : 0x00) * part);

}
#endif /* !BITFACTOR_DEFINED */

#ifndef GETLINEARBIT_DEFINED
#define GETLINEARBIT_DEFINED 1
LOCAL ATTR_PURE uint8_t CC
getlinearbit(void const *__restrict bitmask,
             size_t bitmask_base_offset,
             size_t bitmask_size_x,
             double x, double y) {
	video_color_t result;
	bool c[2][2];
	uintptr_t base_x, base_y;
	double rel_x, rel_y;
	size_t bitno;
	base_x = (uintptr_t)x;
	base_y = (uintptr_t)y;
	/* Load source colors. */
	bitno = bitmask_base_offset + base_x + base_y * bitmask_size_x;
	c[0][0] = (((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))) != 0;
	++bitno;
	c[1][0] = (((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))) != 0;
	bitno += bitmask_size_x;
	c[1][1] = (((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))) != 0;
	--bitno;
	c[0][1] = (((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))) != 0;

	/* Figure out the sub-pixel relation. */
	rel_x = x - (double)base_x;
	rel_y = y - (double)base_y;
	/* Calculate color affinity */
	result  = bitfactor(c[0][0], (rel_x + rel_y) / 2.0);
	result += bitfactor(c[0][1], (rel_x + (1.0 - rel_y)) / 2.0);
	result += bitfactor(c[1][0], ((1.0 - rel_x) + rel_y) / 2.0);
	result += bitfactor(c[1][1], ((1.0 - rel_x) + (1.0 - rel_y)) / 2.0);
	return result;
}
#endif /* !GETLINEARBIT_DEFINED */
#endif /* !DEFINE_STRETCH */


LOCAL void CC
FUNC(stretch_perpixel_fixed)(struct video_gfx *self,
                             uintptr_t dst_x, uintptr_t dst_y,
                             size_t dst_size_x, size_t dst_size_y,
#ifdef DEFINE_BITSTRETCHFILL
                             video_color_t color,
#else /* DEFINE_BITSTRETCHFILL */
                             struct video_gfx const *src,
                             uintptr_t src_x, uintptr_t src_y,
#endif /* !DEFINE_BITSTRETCHFILL */
                             size_t src_size_x, size_t src_size_y
#ifndef DEFINE_STRETCH
                             ,
                             void const *__restrict bitmask,
                             size_t bitmask_base_offset,
                             size_t bitmask_size_x
#endif /* !DEFINE_STRETCH */
                             ) {
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
				video_color_t used_color;
#ifndef DEFINE_BITSTRETCHFILL
				double src_xr, src_yr;
#endif /* !DEFINE_BITSTRETCHFILL */
#ifndef DEFINE_STRETCH
				uint8_t bit;
				double bit_xr, bit_yr;
				bit_xr = round((double)x * x_scale);
				bit_yr = round((double)y * y_scale);
				bit = getlinearbit(bitmask,
				                   bitmask_base_offset,
				                   bitmask_size_x,
				                   bit_xr, bit_yr);
				if (!bit)
					continue;
#endif /* !DEFINE_STRETCH */
#ifndef DEFINE_BITSTRETCHFILL
				src_xr = (double)x * x_scale + (double)src_x;
				src_yr = (double)y * y_scale + (double)src_y;
				used_color = getlinearcolor(src, src_xr, src_yr);
#else /* !DEFINE_BITSTRETCHFILL */
				used_color = color;
#endif /* DEFINE_BITSTRETCHFILL */
#ifndef DEFINE_STRETCH
				bit = (((uint32_t)VIDEO_COLOR_GET_ALPHA(used_color) * bit) / 255);
				used_color &= ~VIDEO_COLOR_ALPHA_MASK;
				used_color |= (video_color_t)bit << VIDEO_COLOR_ALPHA_SHIFT;
#endif /* !DEFINE_STRETCH */
				video_gfx_putabscolor(self,
				                      dst_x + x,
				                      dst_y + y,
				                      used_color);
			}
		}
	} else {
#ifndef DEFINE_BITSTRETCHFILL
		src_x += src->vx_offt_x;
		src_y += src->vx_offt_y;
#endif /* !DEFINE_BITSTRETCHFILL */
		for (y = 0; y < dst_size_y; ++y) {
			for (x = 0; x < dst_size_x; ++x) {
#ifndef DEFINE_BITSTRETCHFILL
				video_color_t color;
#endif /* DEFINE_BITSTRETCHFILL */
				uintptr_t rel_x, rel_y;
				rel_x = (uintptr_t)round((double)x * x_scale);
				rel_y = (uintptr_t)round((double)y * y_scale);
#ifndef DEFINE_STRETCH
				size_t bitno;
				bitno = bitmask_base_offset + rel_x + rel_y * bitmask_size_x;
				if (!(((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))))
					continue;
#endif /* !DEFINE_STRETCH */
#ifndef DEFINE_BITSTRETCHFILL
				rel_x += src_x;
				rel_y += src_y;
				if unlikely(rel_x >= src->vx_size_x) /* This can happen because of rounding */
					rel_x = src->vx_size_x - 1;
				if unlikely(rel_y >= src->vx_size_y) /* This can happen because of rounding */
					rel_y = src->vx_size_y - 1;
				color = video_gfx_getabscolor(src, rel_x, rel_y);
#endif /* DEFINE_BITSTRETCHFILL */
				video_gfx_putabscolor(self,
				                      dst_x + x,
				                      dst_y + y,
				                      color);
			}
		}
	}
}





INTERN void CC
FUNC(libvideo_gfx_defaultgfx)(struct video_gfx *self,
                              intptr_t dst_x, intptr_t dst_y,
                              size_t dst_size_x, size_t dst_size_y,
#ifdef DEFINE_BITSTRETCHFILL
                              video_color_t color,
#else /* DEFINE_BITSTRETCHFILL */
                              struct video_gfx const *src,
                              intptr_t src_x, intptr_t src_y,
#endif /* !DEFINE_BITSTRETCHFILL */
                              size_t src_size_x, size_t src_size_y
                              IF_BITBLIT(, void const *__restrict bitmask)) {
	size_t dst_sx, dst_sy;
#ifndef DEFINE_BITSTRETCHFILL
	size_t src_sx, src_sy;
#endif /* !DEFINE_BITSTRETCHFILL */
	uintptr_t temp;
	IF_BITBLIT(size_t bitmask_base_offset);
	IF_BITBLIT(size_t bitmask_size_x);
	if (!dst_size_x || !dst_size_y || !src_size_x || !src_size_y)
		return;
	IF_BITBLIT(bitmask_base_offset = 0);
	IF_BITBLIT(bitmask_size_x = src_size_x);
	if (dst_x < 0) {
		double portion;
		size_t srcpart;
		dst_x = -dst_x;
		if unlikely((uintptr_t)dst_x >= dst_size_x)
			return;
		portion = (double)(uintptr_t)dst_x / (double)dst_size_x;
		srcpart = (size_t)(portion * (double)src_size_x);
		IF_BITBLIT(bitmask_base_offset = srcpart);
#ifndef DEFINE_BITSTRETCHFILL
		src_x += srcpart;
#endif /* !DEFINE_BITSTRETCHFILL */
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
		IF_BITBLIT(bitmask_base_offset += srcpart * bitmask_size_x);
#ifndef DEFINE_BITSTRETCHFILL
		src_y += srcpart;
#endif /* !DEFINE_BITSTRETCHFILL */
		src_size_y -= srcpart;
		if unlikely(!src_size_y)
			return;
		dst_size_y -= (uintptr_t)dst_y;
		dst_y = 0;
	}
#ifndef DEFINE_BITSTRETCHFILL
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
		IF_BITBLIT(bitmask_base_offset += (uintptr_t)src_x);
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
		IF_BITBLIT(bitmask_base_offset += ((uintptr_t)-src_y) * bitmask_size_x);
		src_size_y -= (uintptr_t)src_y;
		src_y = 0;
	}
#endif /* !DEFINE_BITSTRETCHFILL */
	dst_sx = self->vx_size_x;
	dst_sy = self->vx_size_y;
#ifndef DEFINE_BITSTRETCHFILL
	src_sx = src->vx_size_x;
	src_sy = src->vx_size_y;
#endif /* !DEFINE_BITSTRETCHFILL */
	/* Check for out-of-bounds rendering */
	if unlikely((uintptr_t)dst_x >= dst_sx)
		return;
	if unlikely((uintptr_t)dst_y >= dst_sy)
		return;
#ifndef DEFINE_BITSTRETCHFILL
	if unlikely((uintptr_t)src_x >= src_sx)
		return;
	if unlikely((uintptr_t)src_y >= src_sy)
		return;
#endif /* !DEFINE_BITSTRETCHFILL */
	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_x, dst_size_x, &temp) || temp > dst_sx) {
		size_t overflow;
		double portion;
		overflow = (size_t)(temp - dst_sx);
		assert(overflow < dst_size_x);
		portion = (double)overflow / (double)dst_size_x;
		overflow = (size_t)(portion * (double)src_size_x);
		if unlikely(overflow >= src_size_x)
			return;
		src_size_x -= overflow;
		IF_BITBLIT(bitmask_base_offset += overflow);
		dst_size_x = dst_sx - (uintptr_t)dst_x;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_y, dst_size_y, &temp) || temp > dst_sy) {
		size_t overflow;
		double portion;
		overflow = (size_t)(temp - dst_sy);
		assert(overflow < dst_size_y);
		portion = (double)overflow / (double)dst_size_y;
		overflow = (size_t)(portion * (double)src_size_y);
		if unlikely(overflow >= src_size_y)
			return;
		src_size_y -= overflow;
		IF_BITBLIT(bitmask_base_offset += overflow * bitmask_size_x);
		dst_size_y = dst_sy - (uintptr_t)dst_y;
	}
#ifndef DEFINE_BITSTRETCHFILL
	if unlikely(OVERFLOW_UADD((uintptr_t)src_x, src_size_x, &temp) || temp > src_sx) {
		size_t overflow;
		double portion;
		overflow = (size_t)(temp - src_sx);
		assert(overflow < src_size_x);
		portion = (double)overflow / (double)src_size_x;
		overflow = (size_t)(portion * (double)dst_size_x);
		if unlikely(overflow >= dst_size_x)
			return;
		dst_size_x -= overflow;
		overflow = src_sx - (uintptr_t)src_x;
		IF_BITBLIT(bitmask_base_offset += src_size_x - overflow);
		src_size_x = overflow;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)src_y, src_size_y, &temp) || temp > src_sy) {
		size_t overflow;
		double portion;
		overflow = (size_t)(temp - src_sy);
		assert(overflow < src_size_y);
		portion = (double)overflow / (double)src_size_y;
		overflow = (size_t)(portion * (double)dst_size_y);
		if unlikely(overflow >= dst_size_y)
			return;
		dst_size_y -= overflow;
		IF_BITBLIT(bitmask_base_offset += (src_size_y - (src_sy - (uintptr_t)src_y)) * bitmask_size_x);
		src_size_y = src_sy - (uintptr_t)src_y;
	}
#endif /* !DEFINE_BITSTRETCHFILL */
	if (dst_size_x == src_size_x &&
	    dst_size_y == src_size_y) {
		/* Can use copy-blit */
#ifdef DEFINE_STRETCH
		copy_perpixel_fixed_blit(self,
		                         (uintptr_t)dst_x,
		                         (uintptr_t)dst_y,
		                         src,
		                         (uintptr_t)src_x,
		                         (uintptr_t)src_y,
		                         dst_size_x,
		                         dst_size_y);
#elif defined(DEFINE_BITSTRETCHFILL)
		fillbitblit_perpixel(self,
		                     (uintptr_t)dst_x,
		                     (uintptr_t)dst_y,
		                     (uintptr_t)dst_size_x,
		                     (uintptr_t)dst_size_y,
		                     color,
		                     bitmask,
		                     bitmask_base_offset,
		                     bitmask_size_x);
#else
		copy_perpixel_fixed_bitblit(self,
		                            (uintptr_t)dst_x,
		                            (uintptr_t)dst_y,
		                            src,
		                            (uintptr_t)src_x,
		                            (uintptr_t)src_y,
		                            dst_size_x,
		                            dst_size_y,
		                            bitmask,
		                            bitmask_base_offset,
		                            bitmask_size_x);
#endif
	} else {
		/* Must use stretch-blit */
		FUNC(stretch_perpixel_fixed)(self,
		                             (uintptr_t)dst_x,
		                             (uintptr_t)dst_y,
		                             dst_size_x,
		                             dst_size_y,
#ifdef DEFINE_BITSTRETCHFILL
		                             color,
#else /* DEFINE_BITSTRETCHFILL */
		                             src,
		                             src_x,
		                             src_y,
#endif /* !DEFINE_BITSTRETCHFILL */
		                             src_size_x,
		                             src_size_y
#ifndef DEFINE_STRETCH
		                             ,
		                             bitmask,
		                             bitmask_base_offset,
		                             bitmask_size_x
#endif /* !DEFINE_STRETCH */
		                             );
	}
}





DECL_END

#undef IF_BLIT
#undef IF_BITBLIT
#undef FUNC
#undef DEFINE_STRETCH
#undef DEFINE_BITSTRETCHBLIT
#undef DEFINE_BITSTRETCHFILL
