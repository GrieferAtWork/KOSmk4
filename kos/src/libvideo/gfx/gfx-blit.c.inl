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
#include "gfx-impl.c.inl"
#define DEFINE_BLIT_FIRSTPASS 1
#define DEFINE_BLIT 1
//#define DEFINE_BITBLIT 1
//#define DEFINE_BITFILL 1
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_BLIT) + defined(DEFINE_BITBLIT) + defined(DEFINE_BITFILL)) != 1
#error "Must #define exactly one of `DEFINE_BLIT' or `DEFINE_BITBLIT' or `DEFINE_BITFILL'"
#endif

DECL_BEGIN

#ifdef DEFINE_BITFILL
#define IF_BITFILL(...)  __VA_ARGS__
#define NIF_BITFILL(...) /* nothing */
#else /* DEFINE_BITFILL */
#define IF_BITFILL(...)  /* nothing */
#define NIF_BITFILL(...) __VA_ARGS__
#endif /* !DEFINE_BITFILL */

#ifdef DEFINE_BLIT
#define BLIT_FUNC(x)     GFX_FUNC(x##_blit)
#define BLIT_FUNC2(x)    x##_blit
#define STRETCH_FUNC(x)  GFX_FUNC(x##_stretch)
#define STRETCH_FUNC2(x) x##_stretch
#define IF_BITBLIT(...)  /* nothing */
#elif defined(DEFINE_BITBLIT)
#define BLIT_FUNC(x)     GFX_FUNC(x##_bitblit)
#define BLIT_FUNC2(x)    x##_bitblit
#define STRETCH_FUNC(x)  GFX_FUNC(x##_bitstretchblit)
#define STRETCH_FUNC2(x) x##_bitstretchblit
#define IF_BITBLIT(...)  __VA_ARGS__
#elif defined(DEFINE_BITFILL)
#define BLIT_FUNC(x)     GFX_FUNC(x##_bitfill)
#define BLIT_FUNC2(x)    x##_bitfill
#define STRETCH_FUNC(x)  GFX_FUNC(x##_bitstretchfill)
#define STRETCH_FUNC2(x) x##_bitstretchfill
#define IF_BITBLIT(...)  __VA_ARGS__
#endif /* !DEFINE_BLIT */



#ifdef DEFINE_BLIT_FIRSTPASS
LOCAL void CC
BLIT_FUNC2(copy_perpixel_fixed)(struct video_gfx *IF_BITFILL(__restrict) self,
                                uintptr_t dst_x, uintptr_t dst_y,
                                IF_BITFILL(video_color_t color,)
                                NIF_BITFILL(struct video_gfx const *src,)
                                NIF_BITFILL(uintptr_t src_x, uintptr_t src_y,)
                                size_t size_x, size_t size_y
                                IF_BITBLIT(, void const *__restrict bitmask)
                                IF_BITBLIT(, uintptr_t bitskip)
                                IF_BITBLIT(, size_t bitscan)) {
	size_t x, y;
#ifndef DEFINE_BLIT
	if (bitscan == size_x) {
		uint8_t byte, bits = 0;
		if (bitskip) {
			bitmask = (uint8_t *)bitmask + (bitskip / 8);
			bitskip &= 7;
			byte    = *(uint8_t const *)bitmask << bitskip;
			bitmask = (uint8_t *)bitmask + 1;
			bits    = 8 - bitskip;
		}
		for (y = 0; y < size_y; ++y) {
			for (x = 0; x < size_x; ++x) {
				uint8_t bit;
				NIF_BITFILL(video_color_t color;)
				if (!bits) {
					byte    = *(uint8_t const *)bitmask;
					bitmask = (uint8_t *)bitmask + 1;
					bits    = 8;
				}
				--bits;
				bit = byte & 0x80;
				byte <<= 1;
				if (!bit)
					continue;
				NIF_BITFILL(color = video_gfx_getabscolor(src,
				                                          src_x + x,
				                                          src_y + y));
				video_gfx_putabscolor(self,
				                      dst_x + x,
				                      dst_y + y,
				                      color);
			}
		}
	} else
#endif /* !DEFINE_BLIT */
	{
		for (y = 0; y < size_y; ++y) {
			for (x = 0; x < size_x; ++x) {
				NIF_BITFILL(video_color_t color;)
#ifndef DEFINE_BLIT
				size_t bitno;
				uint8_t byte;
				bitno = bitskip + x + y * bitscan;
				byte = ((uint8_t *)bitmask)[bitno / 8];
				if (!(byte & ((uint8_t)1 << (7 - (bitno % 8)))))
					continue;
#endif /* !DEFINE_BLIT */
				NIF_BITFILL(color = video_gfx_getabscolor(src,
				                                          src_x + x,
				                                          src_y + y));
				video_gfx_putabscolor(self,
				                      dst_x + x,
				                      dst_y + y,
				                      color);
			}
		}
	}
}
#endif /* DEFINE_BLIT_FIRSTPASS */


/************************************************************************/
/* BLIT(), BITBLIT(), BITFILL()                                         */
/************************************************************************/
INTERN void CC
BLIT_FUNC(libvideo_gfx_defaultgfx)(struct video_gfx *IF_BITFILL(__restrict) self,
                                   intptr_t dst_x, intptr_t dst_y,
                                   IF_BITFILL(video_color_t color,)
                                   NIF_BITFILL(struct video_gfx const *src,)
                                   NIF_BITFILL(intptr_t src_x, intptr_t src_y,)
                                   size_t size_x, size_t size_y
                                   IF_BITBLIT(, void const *__restrict bitmask)
                                   IF_BITBLIT(, uintptr_t bitskip)
                                   IF_BITBLIT(, size_t bitscan)) {
	uintptr_t temp;
	if (!size_x || !size_y)
		return;
	IF_OFFSET(dst_x += self->vx_offt_x);
	IF_OFFSET(dst_y += self->vx_offt_y);
	NIF_BITFILL(src_x += src->vx_offt_x);
	NIF_BITFILL(src_y += src->vx_offt_y);
	if unlikely(dst_x < (intptr_t)GFX_XMIN) {
		dst_x = (intptr_t)(GFX_XMIN - (uintptr_t)dst_x);
		if unlikely((uintptr_t)dst_x >= size_x)
			return;
		IF_BITBLIT(bitskip += (uintptr_t)dst_x);
		NIF_BITFILL(src_x += (uintptr_t)dst_x);
		size_x -= (uintptr_t)dst_x;
		dst_x = (intptr_t)GFX_XMIN;
	}
	if unlikely(dst_y < (intptr_t)GFX_YMIN) {
		dst_y = (intptr_t)(GFX_YMIN - (uintptr_t)dst_y);
		if unlikely((uintptr_t)dst_y >= size_y)
			return;
		IF_BITBLIT(bitskip += ((uintptr_t)dst_y) * bitscan);
		NIF_BITFILL(src_y += (uintptr_t)dst_y);
		size_y -= (uintptr_t)dst_y;
		dst_y = (intptr_t)GFX_YMIN;
	}
#ifndef DEFINE_BITFILL
	if unlikely(src_x < (intptr_t)src->vx_xmin) {
		src_x = (intptr_t)(src->vx_xmin - (uintptr_t)src_x);
		if unlikely((uintptr_t)src_x >= size_x)
			return;
		IF_BITBLIT(bitskip += (uintptr_t)src_x);
		dst_x += (uintptr_t)src_x;
		size_x -= (uintptr_t)src_x;
		src_x = (intptr_t)src->vx_xmin;
	}
	if unlikely(src_y < (intptr_t)src->vx_ymin) {
		src_y = (intptr_t)(src->vx_ymin - (uintptr_t)src_y);
		if unlikely((uintptr_t)src_y >= size_y)
			return;
		IF_BITBLIT(bitskip += ((uintptr_t)src_y) * bitscan);
		dst_y += (uintptr_t)src_y;
		size_y -= (uintptr_t)src_y;
		src_y = (intptr_t)src->vx_ymin;
	}
#endif /* !DEFINE_BITFILL */
	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_x, size_x, &temp) || temp > GFX_XEND) {
		if unlikely((uintptr_t)dst_x >= GFX_XEND)
			return;
		size_x = GFX_XEND - (uintptr_t)dst_x;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_y, size_y, &temp) || temp > GFX_YEND) {
		if unlikely((uintptr_t)dst_y >= GFX_YEND)
			return;
		size_y = GFX_YEND - (uintptr_t)dst_y;
	}
#ifndef DEFINE_BITFILL
	if unlikely(OVERFLOW_UADD((uintptr_t)src_x, size_x, &temp) || temp > src->vx_xend) {
		if unlikely((uintptr_t)src_x >= src->vx_xend)
			return;
		size_x = src->vx_xend - (uintptr_t)src_x;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)src_y, size_y, &temp) || temp > src->vx_yend) {
		if unlikely((uintptr_t)src_y >= src->vx_yend)
			return;
		size_y = src->vx_yend - (uintptr_t)src_y;
	}
#endif /* !DEFINE_BITFILL */
	BLIT_FUNC2(copy_perpixel_fixed)(self,
	                                (uintptr_t)dst_x,
	                                (uintptr_t)dst_y
	                                IF_BITFILL(, color)
	                                NIF_BITFILL(, src)
	                                NIF_BITFILL(, (uintptr_t)src_x)
	                                NIF_BITFILL(, (uintptr_t)src_y)
	                                , size_x
	                                , size_y
	                                IF_BITBLIT(, bitmask)
	                                IF_BITBLIT(, bitskip)
	                                IF_BITBLIT(, bitscan));
}


















#ifdef DEFINE_BLIT_FIRSTPASS
#ifndef DEFINE_BITFILL
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
	r = (uint8_t)((double)r * part);
	g = (uint8_t)((double)g * part);
	b = (uint8_t)((double)b * part);
	a = (uint8_t)((double)a * part);
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
	intptr_t base_x, base_y;
	double base_xf, base_yf;
	double rel_x, rel_y;
	x -= 0.5;
	y -= 0.5;
	base_xf = floor(x);
	base_yf = floor(y);
	base_x = (intptr_t)base_xf;
	base_y = (intptr_t)base_yf;
	if unlikely(base_x < (intptr_t)self->vx_xmin) {
		if unlikely(base_x <= (intptr_t)self->vx_xmin - 2)
			return 0; /* This can happen because of rounding */
		c[0][0] = 0;
		c[0][1] = 0;
		if unlikely(base_y < (intptr_t)self->vx_ymin) {
			if unlikely(base_y <= (intptr_t)self->vx_ymin - 2)
				return 0; /* This can happen because of rounding */
			c[1][0] = 0;
			c[1][1] = video_gfx_getabscolor(self, self->vx_xmin, self->vx_ymin);
		} else {
			if unlikely((uintptr_t)base_y >= self->vx_yend)
				return 0; /* This can happen because of rounding */
			c[1][0] = video_gfx_getabscolor(self, self->vx_xmin, (uintptr_t)base_y);
			if unlikely((uintptr_t)base_y == self->vx_yend - 1) {
				c[1][1] = 0;
			} else {
				c[1][1] = video_gfx_getabscolor(self, self->vx_xmin, (uintptr_t)base_y + 1);
			}
		}
	} else {
		if unlikely((uintptr_t)base_x >= self->vx_xend)
			return 0; /* This can happen because of rounding */
		if unlikely(base_y < (intptr_t)self->vx_ymin) {
			if unlikely(base_y <= (intptr_t)self->vx_ymin - 2)
				return 0; /* This can happen because of rounding */
			c[0][0] = 0;
			c[1][0] = 0;
			c[0][1] = video_gfx_getabscolor(self, (uintptr_t)base_x, self->vx_ymin);
			if unlikely((uintptr_t)base_x == self->vx_xend - 1) {
				c[1][1] = 0;
			} else {
				c[1][1] = video_gfx_getabscolor(self, (uintptr_t)base_x + 1, self->vx_ymin);
			}
		} else {
			if unlikely((uintptr_t)base_y >= self->vx_yend)
				return 0; /* This can happen because of rounding */
			/* Load source colors. */
			c[0][0] = video_gfx_getabscolor(self,
			                                (uintptr_t)base_x,
			                                (uintptr_t)base_y);
			if unlikely((uintptr_t)base_x == self->vx_xend - 1) {
				/* This can happen because of rounding */
				c[1][0] = 0;
				c[1][1] = 0;
				if unlikely((uintptr_t)base_y == self->vx_yend - 1) {
					c[0][1] = false; /* This can happen because of rounding */
				} else {
					c[0][1] = video_gfx_getabscolor(self,
					                                (uintptr_t)base_x,
					                                (uintptr_t)base_y + 1);
				}
			} else {
				c[1][0] = video_gfx_getabscolor(self,
				                                (uintptr_t)base_x + 1,
				                                (uintptr_t)base_y);
				if unlikely((uintptr_t)base_y == self->vx_yend - 1) {
					c[0][1] = 0; /* This can happen because of rounding */
					c[1][1] = 0;
				} else {
					c[0][1] = video_gfx_getabscolor(self, (uintptr_t)base_x, (uintptr_t)base_y + 1);
					c[1][1] = video_gfx_getabscolor(self, (uintptr_t)base_x + 1, (uintptr_t)base_y + 1);
				}
			}
		}
	}

	/* Figure out the sub-pixel relation. */
	rel_x = x - base_xf;
	rel_y = y - base_yf;
	/* Calculate color affinity */
	result  = colorfactor(c[0][0], ((1.0 - rel_x) + (1.0 - rel_y)) / 4.0);
	result += colorfactor(c[0][1], ((1.0 - rel_x) + rel_y) / 4.0);
	result += colorfactor(c[1][0], (rel_x + (1.0 - rel_y)) / 4.0);
	result += colorfactor(c[1][1], (rel_x + rel_y) / 4.0);
	return result;
}
#endif /* !GETLINEARCOLOR_DEFINED */
#endif /* !DEFINE_BITFILL */

#ifndef DEFINE_BLIT
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
             uintptr_t bitskip,
             size_t bitmask_size_x,
             size_t bitmask_size_y,
             double x, double y) {
	uint8_t result;
	bool c[2][2];
	intptr_t base_x, base_y;
	double base_xf, base_yf;
	double rel_x, rel_y;
	size_t bitno;
	x -= 0.5;
	y -= 0.5;
	base_xf = floor(x);
	base_yf = floor(y);
	base_x = (intptr_t)base_xf;
	base_y = (intptr_t)base_yf;
	if unlikely(base_x < 0) {
		if unlikely(base_x <= -2)
			return 0; /* This can happen because of rounding */
		c[0][0] = false;
		c[0][1] = false;
		if unlikely(base_y < 0) {
			if unlikely(base_y <= -2)
				return 0; /* This can happen because of rounding */
			c[1][0] = false;
			c[1][1] = (((uint8_t *)bitmask)[0] & 0x80) != 0;
		} else {
			if unlikely((uintptr_t)base_y >= bitmask_size_y)
				return 0; /* This can happen because of rounding */
			bitno = bitskip + (uintptr_t)base_y * bitmask_size_x;
			c[1][0] = (((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))) != 0;
			if unlikely((uintptr_t)base_y == bitmask_size_y - 1) {
				c[1][1] = false;
			} else {
				bitno += bitmask_size_x;
				c[1][1] = (((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))) != 0;
			}
		}
	} else {
		if unlikely((uintptr_t)base_x >= bitmask_size_x)
			return 0; /* This can happen because of rounding */
		if (base_y < 0) {
			if (base_y <= -2)
				return 0; /* This can happen because of rounding */
			c[0][0] = false;
			c[1][0] = false;
			bitno = bitskip + (uintptr_t)base_x;
			c[0][1] = (((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))) != 0;
			if unlikely((uintptr_t)base_x == bitmask_size_x - 1) {
				c[1][1] = false;
			} else {
				++bitno;
				c[1][1] = (((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))) != 0;
			}
		} else {
			if unlikely((uintptr_t)base_y >= bitmask_size_y)
				return 0; /* This can happen because of rounding */
			/* Load source colors. */
			bitno = bitskip + (uintptr_t)base_x + (uintptr_t)base_y * bitmask_size_x;
			c[0][0] = (((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))) != 0;
			if unlikely((uintptr_t)base_x == bitmask_size_x - 1) {
				/* This can happen because of rounding */
				c[1][0] = false;
				c[1][1] = false;
				if unlikely((uintptr_t)base_y == bitmask_size_y - 1) {
					c[0][1] = false; /* This can happen because of rounding */
				} else {
					bitno += bitmask_size_x;
					c[0][1] = (((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))) != 0;
				}
			} else {
				++bitno;
				c[1][0] = (((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))) != 0;
				if unlikely((uintptr_t)base_y == bitmask_size_y - 1) {
					c[1][1] = false; /* This can happen because of rounding */
					c[0][1] = false;
				} else {
					bitno += bitmask_size_x;
					c[1][1] = (((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))) != 0;
					--bitno;
					c[0][1] = (((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))) != 0;
				}
			}
		}
	}

	/* Figure out the sub-pixel relation. */
	rel_x = x - base_xf;
	rel_y = y - base_yf;
	/* Calculate color affinity */
	result  = bitfactor(c[0][0], ((1.0 - rel_x) + (1.0 - rel_y)) / 4.0);
	result += bitfactor(c[0][1], ((1.0 - rel_x) + rel_y) / 4.0);
	result += bitfactor(c[1][0], (rel_x + (1.0 - rel_y)) / 4.0);
	result += bitfactor(c[1][1], (rel_x + rel_y) / 4.0);
	return result;
}
#endif /* !GETLINEARBIT_DEFINED */
#endif /* !DEFINE_BLIT */


LOCAL void CC
STRETCH_FUNC2(stretch_perpixel_fixed)(struct video_gfx *IF_BITFILL(__restrict) self,
                                      uintptr_t dst_x, uintptr_t dst_y,
                                      size_t dst_size_x, size_t dst_size_y,
                                      IF_BITFILL(video_color_t color,)
                                      NIF_BITFILL(struct video_gfx const *src,)
                                      NIF_BITFILL(uintptr_t src_x, uintptr_t src_y,)
                                      size_t src_size_x, size_t src_size_y
                                      IF_BITBLIT(, void const *__restrict bitmask)
                                      IF_BITBLIT(, uintptr_t bitskip)
                                      IF_BITBLIT(, size_t bitmask_size_x)
                                      IF_BITBLIT(, size_t bitmask_size_y)) {
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
				double rel_x, rel_y;
#ifndef DEFINE_BLIT
				uint8_t opacity;
#endif /* !DEFINE_BLIT */
				rel_x = (double)x * x_scale;
				rel_y = (double)y * y_scale;
#ifndef DEFINE_BLIT
				opacity = getlinearbit(bitmask,
				                       bitskip,
				                       bitmask_size_x,
				                       bitmask_size_y,
				                       rel_x,
				                       rel_y);
				if (!opacity)
					continue;
#endif /* !DEFINE_BLIT */
#ifndef DEFINE_BITFILL
				rel_x += (double)src_x;
				rel_y += (double)src_y;
				used_color = getlinearcolor(src, rel_x, rel_y);
#else /* !DEFINE_BITFILL */
				used_color = color;
#endif /* DEFINE_BITFILL */
#ifndef DEFINE_BLIT
				opacity = (((uint32_t)VIDEO_COLOR_GET_ALPHA(used_color) * opacity) / 255);
				used_color &= ~VIDEO_COLOR_ALPHA_MASK;
				used_color |= (video_color_t)opacity << VIDEO_COLOR_ALPHA_SHIFT;
#endif /* !DEFINE_BLIT */
				video_gfx_putabscolor(self,
				                      dst_x + x,
				                      dst_y + y,
				                      used_color);
			}
		}
	} else {
		for (y = 0; y < dst_size_y; ++y) {
			for (x = 0; x < dst_size_x; ++x) {
				NIF_BITFILL(video_color_t color;)
				uintptr_t rel_x, rel_y;
#ifndef DEFINE_BLIT
				size_t bitno;
#endif /* !DEFINE_BLIT */
				rel_x = (uintptr_t)round((double)x * x_scale);
				rel_y = (uintptr_t)round((double)y * y_scale);
#ifndef DEFINE_BLIT
				if unlikely(rel_x >= bitmask_size_x)
					continue; /* This can happen because of rounding */
				if unlikely(rel_y >= bitmask_size_y)
					continue; /* This can happen because of rounding */
				bitno = bitskip + rel_x + rel_y * bitmask_size_x;
				if (!(((uint8_t *)bitmask)[bitno / 8] & ((uint8_t)1 << (7 - (bitno % 8)))))
					continue;
#endif /* !DEFINE_BLIT */
#ifndef DEFINE_BITFILL
				rel_x += src_x;
				rel_y += src_y;
				if unlikely(rel_x >= src->vx_xend ||
				            rel_y >= src->vx_yend) {
					color = 0; /* This can happen because of rounding */
				} else {
					color = video_gfx_getabscolor(src,
					                              rel_x,
					                              rel_y);
				}
#endif /* DEFINE_BITFILL */
				video_gfx_putabscolor(self,
				                      dst_x + x,
				                      dst_y + y,
				                      color);
			}
		}
	}
}
#endif /* DEFINE_BLIT_FIRSTPASS */




/************************************************************************/
/* STRETCH(), BITSTRETCHBLIT(), BITSTRETCHFILL()                        */
/************************************************************************/
INTERN void CC
STRETCH_FUNC(libvideo_gfx_defaultgfx)(struct video_gfx *IF_BITFILL(__restrict) self,
                                      intptr_t dst_x, intptr_t dst_y,
                                      size_t dst_size_x, size_t dst_size_y,
                                      IF_BITFILL(video_color_t color,)
                                      NIF_BITFILL(struct video_gfx const *src,)
                                      NIF_BITFILL(intptr_t src_x, intptr_t src_y,)
                                      size_t src_size_x, size_t src_size_y
                                      IF_BITBLIT(, void const *__restrict bitmask)
                                      IF_BITBLIT(, uintptr_t bitskip)
                                      IF_BITBLIT(, size_t bitscan)) {
	uintptr_t temp;
	IF_BITBLIT(size_t bitmask_size_y);
	if unlikely(!dst_size_x || !dst_size_y || !src_size_x || !src_size_y)
		return;
	IF_OFFSET(dst_x += self->vx_offt_x);
	IF_OFFSET(dst_y += self->vx_offt_y);
	IF_BITBLIT(bitmask_size_y = src_size_y);
	NIF_BITFILL(src_x += src->vx_offt_x);
	NIF_BITFILL(src_y += src->vx_offt_y);
	if unlikely(dst_x < (intptr_t)GFX_XMIN) {
		size_t srcpart;
		dst_x = (intptr_t)(GFX_XMIN - (uintptr_t)dst_x);
		if unlikely((uintptr_t)dst_x >= dst_size_x)
			return;
		srcpart = ((uintptr_t)dst_x * src_size_x) / dst_size_x;
		if unlikely(srcpart >= src_size_x)
			return;
		src_size_x -= srcpart;
		dst_size_x -= (uintptr_t)dst_x;
		IF_BITBLIT(bitskip += srcpart);
		NIF_BITFILL(src_x += srcpart);
		dst_x = (intptr_t)GFX_XMIN;
	}
	if unlikely(dst_y < (intptr_t)GFX_YMIN) {
		size_t srcpart;
		dst_y = (intptr_t)(GFX_YMIN - (uintptr_t)dst_y);
		if unlikely((uintptr_t)dst_y >= dst_size_y)
			return;
		srcpart = ((uintptr_t)dst_y * src_size_y) / dst_size_y;
		if unlikely(srcpart >= src_size_y)
			return;
		src_size_y -= srcpart;
		dst_size_y -= (uintptr_t)dst_y;
		IF_BITBLIT(bitskip += srcpart * bitscan);
		NIF_BITFILL(src_y += srcpart);
		dst_y = (intptr_t)GFX_YMIN;
	}
#ifndef DEFINE_BITFILL
	if unlikely(src_x < (intptr_t)src->vx_xmin) {
		size_t dstpart;
		src_x = (intptr_t)(src->vx_xmin - (uintptr_t)src_x);
		if unlikely((uintptr_t)src_x >= src_size_x)
			return;
		dstpart = ((uintptr_t)src_x * dst_size_x) / src_size_x;
		if unlikely(dstpart >= dst_size_x)
			return;
		dst_size_x -= dstpart;
		dst_x += dstpart;
		IF_BITBLIT(bitskip += (uintptr_t)src_x);
		src_size_x -= (uintptr_t)src_x;
		src_x = (intptr_t)src->vx_xmin;
	}
	if unlikely(src_y < (intptr_t)src->vx_ymin) {
		size_t dstpart;
		src_y = (intptr_t)(src->vx_ymin - (uintptr_t)src_y);
		src_y = -src_y;
		if unlikely((uintptr_t)src_y >= src_size_y)
			return;
		dstpart = ((uintptr_t)src_y * dst_size_y) / src_size_y;
		if unlikely(dstpart >= dst_size_y)
			return;
		dst_size_y -= dstpart;
		dst_y += dstpart;
		IF_BITBLIT(bitskip += ((uintptr_t)-src_y) * bitscan);
		src_size_y -= (uintptr_t)src_y;
		src_y = (intptr_t)src->vx_ymin;
	}
#endif /* !DEFINE_BITFILL */
	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_x, dst_size_x, &temp) || temp > GFX_XEND) {
		size_t newdstsize, overflow;
		if unlikely((uintptr_t)dst_x >= GFX_XEND)
			return;
		newdstsize = GFX_XEND - (uintptr_t)dst_x;
		overflow   = dst_size_x - newdstsize;
		overflow   = (overflow * src_size_x) / dst_size_x;
		dst_size_x = newdstsize;
		if unlikely(overflow >= src_size_x)
			return;
		src_size_x -= overflow;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)dst_y, dst_size_y, &temp) || temp > GFX_YEND) {
		size_t newdstsize, overflow;
		if unlikely((uintptr_t)dst_y >= GFX_YEND)
			return;
		newdstsize = GFX_YEND - (uintptr_t)dst_y;
		overflow   = dst_size_y - newdstsize;
		overflow   = (overflow * src_size_y) / dst_size_y;
		dst_size_y = newdstsize;
		if unlikely(overflow >= src_size_y)
			return;
		src_size_y -= overflow;
	}
#ifndef DEFINE_BITFILL
	if unlikely(OVERFLOW_UADD((uintptr_t)src_x, src_size_x, &temp) || temp > src->vx_xend) {
		size_t newsrcsize, overflow;
		if unlikely((uintptr_t)src_x >= src->vx_xend)
			return;
		newsrcsize = src->vx_xend - (uintptr_t)src_x;
		overflow   = src_size_x - newsrcsize;
		overflow   = (overflow * dst_size_x) / src_size_x;
		src_size_x = newsrcsize;
		if unlikely(overflow >= dst_size_x)
			return;
		dst_size_x -= overflow;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)src_y, src_size_y, &temp) || temp > src->vx_yend) {
		size_t newsrcsize, overflow;
		if unlikely((uintptr_t)src_y >= src->vx_yend)
			return;
		newsrcsize = src->vx_yend - (uintptr_t)src_y;
		overflow   = src_size_y - newsrcsize;
		overflow   = (overflow * dst_size_y) / src_size_y;
		src_size_y = newsrcsize;
		if unlikely(overflow >= dst_size_y)
			return;
		dst_size_y -= overflow;
	}
#endif /* !DEFINE_BITFILL */
	if (dst_size_x == src_size_x && dst_size_y == src_size_y) {
		/* Can use copy-blit */
		BLIT_FUNC2(copy_perpixel_fixed)(self,
		                                (uintptr_t)dst_x,
		                                (uintptr_t)dst_y
		                                IF_BITFILL(, color)
		                                NIF_BITFILL(, src)
		                                NIF_BITFILL(, (uintptr_t)src_x)
		                                NIF_BITFILL(, (uintptr_t)src_y)
		                                , dst_size_x
		                                , dst_size_y
		                                IF_BITBLIT(, bitmask)
		                                IF_BITBLIT(, bitskip)
		                                IF_BITBLIT(, bitscan));
	} else {
		/* Must use stretch-blit */
		STRETCH_FUNC2(stretch_perpixel_fixed)(self,
		                                      (uintptr_t)dst_x,
		                                      (uintptr_t)dst_y,
		                                      dst_size_x,
		                                      dst_size_y
		                                      IF_BITFILL(, color)
		                                      NIF_BITFILL(, src)
		                                      NIF_BITFILL(, src_x)
		                                      NIF_BITFILL(, src_y)
		                                      , src_size_x
		                                      , src_size_y
		                                      IF_BITBLIT(, bitmask)
		                                      IF_BITBLIT(, bitskip)
		                                      IF_BITBLIT(, bitscan)
		                                      IF_BITBLIT(, bitmask_size_y));
	}
}




DECL_END

#undef IF_BITFILL
#undef NIF_BITFILL
#undef IF_BITBLIT
#undef STRETCH_FUNC2
#undef STRETCH_FUNC
#undef BLIT_FUNC
#undef BLIT_FUNC2
#undef DEFINE_BLIT
#undef DEFINE_BITBLIT
#undef DEFINE_BITFILL
