/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "gfx.c"

//#define DEFINE_GFX_NORMAL 1
#define DEFINE_GFX_OFFSET 1
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_GFX_NORMAL) + defined(DEFINE_GFX_OFFSET)) != 1
#error "Must #define exactly one of `DEFINE_GFX_NORMAL', `DEFINE_GFX_OFFSET'"
#endif

#ifdef DEFINE_GFX_NORMAL
#define GFX_FUNC(x) x
#define IFELSE_NoOf(if_normal, if_offset) if_normal
#define IF_NORMAL(...) __VA_ARGS__
#define IF_OFFSET(...) /* nothing */
#else /* DEFINE_GFX_NORMAL */
#define GFX_FUNC(x) x##_o
#define IFELSE_NoOf(if_normal, if_offset) if_offset
#define IF_NORMAL(...) /* nothing */
#define IF_OFFSET(...) __VA_ARGS__
#endif /* !DEFINE_GFX_NORMAL */

DECL_BEGIN


#ifdef DEFINE_GFX_NORMAL
#define GFX_XMIN (uintptr_t)0
#define GFX_YMIN (uintptr_t)0
#else /* DEFINE_GFX_NORMAL */
#define GFX_XMIN self->vx_xmin
#define GFX_YMIN self->vx_ymin
#endif /* !DEFINE_GFX_NORMAL */
#define GFX_XEND self->vx_xend
#define GFX_YEND self->vx_yend
#define GFX_XMAX (self->vx_xend - 1)
#define GFX_YMAX (self->vx_yend - 1)

INTERN NONNULL((1)) void CC
GFX_FUNC(libvideo_gfx_defaultgfx_line)(struct video_gfx *__restrict self,
                                       intptr_t x1, intptr_t y1,
                                       intptr_t x2, intptr_t y2,
                                       video_color_t color) {
	/* >> Cohen-Sutherland algorithm
	 * https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm */
	int outcode0, outcode1, outcodeOut;
	intptr_t temp, x, y;
#define COHSUTH_INSIDE 0 /* 0000 */
#define COHSUTH_XMIN   1 /* 0001 */
#define COHSUTH_XMAX   2 /* 0010 */
#define COHSUTH_YMIN   4 /* 0100 */
#define COHSUTH_YMAX   8 /* 1000 */
	IF_OFFSET(x1 += self->vx_offt_x);
	IF_OFFSET(y1 += self->vx_offt_y);
	IF_OFFSET(x2 += self->vx_offt_x);
	IF_OFFSET(y2 += self->vx_offt_y);
#define COHSUTH_COMPUTEOUTCODE(x, y, result)    \
	do {                                        \
		(result) = COHSUTH_INSIDE;              \
		if ((x) < (intptr_t)GFX_XMIN) {         \
			(result) |= COHSUTH_XMIN;           \
		} else if ((x) >= (intptr_t)GFX_XEND) { \
			(result) |= COHSUTH_XMAX;           \
		}                                       \
		if ((y) < (intptr_t)GFX_YMIN) {         \
			(result) |= COHSUTH_YMIN;           \
		} else if ((y) >= (intptr_t)GFX_YEND) { \
			(result) |= COHSUTH_YMAX;           \
		}                                       \
	}	__WHILE0
	COHSUTH_COMPUTEOUTCODE(x1, y1, outcode0);
	COHSUTH_COMPUTEOUTCODE(x2, y2, outcode1);
	while ((outcode0 | outcode1) != 0) {
		if ((outcode0 & outcode1) != 0)
			return;
		outcodeOut = outcode0 ? outcode0 : outcode1;
		if ((outcodeOut & COHSUTH_YMAX) != 0) {
			x = x1 + (x2 - x1) * ((intptr_t)GFX_YMAX - y1) / (y2 - y1);
			y = (intptr_t)GFX_YMAX;
		} else if ((outcodeOut & COHSUTH_YMIN) != 0) {
			x = x1 + (x2 - x1) * ((intptr_t)GFX_YMIN - y1) / (y2 - y1);
			y = (intptr_t)GFX_YMIN;
		} else if ((outcodeOut & COHSUTH_XMAX) != 0) {
			y = y1 + (y2 - y1) * ((intptr_t)GFX_XMAX - x1) / (x2 - x1);
			x = (intptr_t)GFX_XMAX;
		} else /*if ((outcodeOut & COHSUTH_XMIN) != 0)*/ {
			y = y1 + (y2 - y1) * ((intptr_t)GFX_XMIN - x1) / (x2 - x1);
			x = (intptr_t)GFX_XMIN;
		}
		if (outcodeOut == outcode0) {
			x1 = x, y1 = y;
			COHSUTH_COMPUTEOUTCODE(x1, y1, outcode0);
		} else {
			x2 = x, y2 = y;
			COHSUTH_COMPUTEOUTCODE(x2, y2, outcode1);
		}
	}
	ASSERT_ABS_COORDS(self, (uintptr_t)x1, (uintptr_t)y1);
	ASSERT_ABS_COORDS(self, (uintptr_t)x2, (uintptr_t)y2);

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
			video_gfx_putabscolor(self,
			                      (uintptr_t)x1,
			                      (uintptr_t)y1,
			                      color);
			return;
		}
		line_vert(self,
		          (uintptr_t)x1,
		          (uintptr_t)y1,
		          (size_t)((uintptr_t)y2 - (uintptr_t)y1) + 1,
		          color);
		return;
	}
	assert(x2 > x1);
	if (y2 > y1) {
		line_llhh(self,
		          (uintptr_t)x1,
		          (uintptr_t)y1,
		          (size_t)((uintptr_t)x2 - (uintptr_t)x1) + 1,
		          (size_t)((uintptr_t)y2 - (uintptr_t)y1) + 1,
		          color);
	} else if (y2 < y1) {
		line_lhhl(self,
		          (uintptr_t)x1,
		          (uintptr_t)y1,
		          (size_t)((uintptr_t)x2 - (uintptr_t)x1) + 1,
		          (size_t)((uintptr_t)y1 - (uintptr_t)y2) + 1,
		          color);
	} else {
		line_hori(self,
		          (uintptr_t)x1,
		          (uintptr_t)y1,
		          (size_t)((uintptr_t)x2 - (uintptr_t)x1) + 1,
		          color);
	}
#undef COHSUTH_COMPUTEOUTCODE
#undef COHSUTH_INSIDE
#undef COHSUTH_XMIN
#undef COHSUTH_XMAX
#undef COHSUTH_YMIN
#undef COHSUTH_YMAX
}





/************************************************************************/
/* RECT()                                                               */
/************************************************************************/
INTERN NONNULL((1)) void CC
GFX_FUNC(libvideo_gfx_defaultgfx_rect)(struct video_gfx *__restrict self,
                                       intptr_t x, intptr_t y,
                                       size_t size_x, size_t size_y,
                                       video_color_t color) {
	size_t temp;
#define LINE_XMIN 0x1
#define LINE_YMIN 0x2
#define LINE_XMAX 0x4
#define LINE_YMAX 0x8
	uint8_t draw_lines;
	if unlikely(!size_x || !size_y)
		return;
	draw_lines = 0xf;
	IF_OFFSET(x += self->vx_offt_x);
	IF_OFFSET(y += self->vx_offt_y);
	if unlikely(x < (intptr_t)GFX_XMIN) {
		x = (intptr_t)(GFX_XMIN - (uintptr_t)x);
		if unlikely((uintptr_t)x >= size_x)
			return;
		size_x -= (uintptr_t)x;
		x = (intptr_t)GFX_XMIN;
		draw_lines &= ~LINE_XMIN;
	}
	if unlikely(y < (intptr_t)GFX_YMIN) {
		y = (intptr_t)(GFX_YMIN - (uintptr_t)y);
		if unlikely((uintptr_t)y >= size_y)
			return;
		size_y -= (uintptr_t)y;
		y = (intptr_t)GFX_YMIN;
		draw_lines &= ~LINE_YMIN;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)x, size_x, &temp) || temp > GFX_XEND) {
		if unlikely((uintptr_t)x >= GFX_XEND)
			return;
		size_x = GFX_XEND - (uintptr_t)x;
		draw_lines &= ~LINE_XMAX;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)y, size_y, &temp) || temp > GFX_YEND) {
		if unlikely((uintptr_t)y >= GFX_YEND)
			return;
		size_y = GFX_YEND - (uintptr_t)y;
		draw_lines &= ~LINE_YMAX;
	}
#define HLINE(x, y, length) line_hori(self, x, y, length, color)
#define VLINE(x, y, length) line_vert(self, x, y, length, color)
	switch (draw_lines) {

		/* All 4 lines */
	case LINE_XMIN | LINE_YMIN | LINE_XMAX | LINE_YMAX:
		HLINE((uintptr_t)x, (uintptr_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			HLINE((uintptr_t)x, (uintptr_t)y + size_y - 1, size_x); /* YMAX */
			if (size_y >= 3) {
				VLINE((uintptr_t)x, (uintptr_t)y + 1, size_y - 2); /* XMIN */
				if (size_x >= 2)
					VLINE((uintptr_t)x + size_x - 1, (uintptr_t)y + 1, size_y - 2); /* XMAX */
			}
		}
		break;

		/* 3-line combinations */
	case LINE_YMIN | LINE_YMAX | LINE_XMIN:
		HLINE((uintptr_t)x, (uintptr_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			HLINE((uintptr_t)x, (uintptr_t)y + size_y - 1, size_x); /* YMAX */
			if (size_y >= 3)
				VLINE((uintptr_t)x, (uintptr_t)y + 1, size_y - 2); /* XMIN */
		}
		break;

	case LINE_YMIN | LINE_YMAX | LINE_XMAX:
		HLINE((uintptr_t)x, (uintptr_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			HLINE((uintptr_t)x, (uintptr_t)y + size_y - 1, size_x); /* YMAX */
			if (size_y >= 3)
				VLINE((uintptr_t)x + size_x - 1, (uintptr_t)y + 1, size_y - 2); /* XMAX */
		}
		break;

	case LINE_XMIN | LINE_XMAX | LINE_YMIN:
		HLINE((uintptr_t)x, (uintptr_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			VLINE((uintptr_t)x, (uintptr_t)y + 1, size_y - 1); /* XMIN */
			if (size_x >= 2)
				VLINE((uintptr_t)x + size_x - 1, (uintptr_t)y + 1, size_y - 1); /* XMAX */
		}
		break;

	case LINE_XMIN | LINE_XMAX | LINE_YMAX:
		HLINE((uintptr_t)x, (uintptr_t)y + size_y - 1, size_x); /* YMAX */
		if (size_y >= 2) {
			VLINE((uintptr_t)x, (uintptr_t)y, size_y - 1); /* XMIN */
			if (size_x >= 2)
				VLINE((uintptr_t)x + size_x - 1, (uintptr_t)y, size_y - 1); /* XMAX */
		}
		break;

		/* Adjacent lines */
	case LINE_XMIN | LINE_YMIN:
		HLINE((uintptr_t)x, (uintptr_t)y, size_x); /* YMIN */
		if (size_y >= 2)
			VLINE((uintptr_t)x, (uintptr_t)y + 1, size_y - 1); /* XMIN */
		break;

	case LINE_XMAX | LINE_YMIN:
		HLINE((uintptr_t)x, (uintptr_t)y, size_x); /* YMIN */
		if (size_y >= 2)
			VLINE((uintptr_t)x + size_x - 1, (uintptr_t)y + 1, size_y - 1); /* XMAX */
		break;

	case LINE_XMIN | LINE_YMAX:
		HLINE((uintptr_t)x, (uintptr_t)y + size_y - 1, size_x); /* YMAX */
		if (size_y >= 2)
			VLINE((uintptr_t)x, (uintptr_t)y, size_y - 1); /* XMIN */
		break;

	case LINE_XMAX | LINE_YMAX:
		HLINE((uintptr_t)x, (uintptr_t)y + size_y - 1, size_x); /* YMAX */
		if (size_y >= 2)
			VLINE((uintptr_t)x + size_x - 1, (uintptr_t)y, size_y - 1); /* XMAX */
		break;


		/* Opposing lines */
	case LINE_XMIN | LINE_XMAX:
		VLINE((uintptr_t)x, (uintptr_t)y, size_y); /* XMIN */
		if (size_x >= 2)
			VLINE((uintptr_t)x + size_x - 1, (uintptr_t)y, size_y); /* XMAX */
		break;

	case LINE_YMIN | LINE_YMAX:
		HLINE((uintptr_t)x, (uintptr_t)y, size_x); /* YMIN */
		if (size_y >= 2)
			HLINE((uintptr_t)x, (uintptr_t)y + size_y - 1, size_x); /* YMAX */
		break;

		/* Single lines */
	case LINE_XMAX:
		x += size_x - 1;
		ATTR_FALLTHROUGH
	case LINE_XMIN:
		VLINE((uintptr_t)x, (uintptr_t)y, size_y); /* XMIN / XMAX */
		break;

	case LINE_YMAX:
		y += size_y - 1;
		ATTR_FALLTHROUGH
	case LINE_YMIN:
		HLINE((uintptr_t)x, (uintptr_t)y, size_x); /* YMIN / YMAX */
		break;

	case 0: /* Completely out-of-bounds */
		break;

	default:
		__builtin_unreachable();
	}
#undef VLINE
#undef HLINE
}






/************************************************************************/
/* HLINE()                                                              */
/************************************************************************/
INTERN NONNULL((1)) void CC
GFX_FUNC(libvideo_gfx_defaultgfx_hline)(struct video_gfx *__restrict self,
                                        intptr_t x, intptr_t y, size_t length,
                                        video_color_t color) {
	uintptr_t temp;
	IF_OFFSET(x += self->vx_offt_x);
	IF_OFFSET(y += self->vx_offt_y);
	if unlikely(y < (intptr_t)GFX_YMIN)
		return;
	if unlikely(x < (intptr_t)GFX_XMIN) {
		x = (intptr_t)(GFX_XMIN - (uintptr_t)x);
		if unlikely(length <= (uintptr_t)x)
			return;
		length -= (uintptr_t)x;
		x = (intptr_t)GFX_XMIN;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)x, length, &temp) || temp > GFX_XEND) {
		if unlikely((uintptr_t)x >= GFX_XEND)
			return;
		length = GFX_XEND - (uintptr_t)x;
	}
	line_hori(self, (uintptr_t)x, (uintptr_t)y, length, color);
}






/************************************************************************/
/* VLINE()                                                              */
/************************************************************************/
INTERN NONNULL((1)) void CC
GFX_FUNC(libvideo_gfx_defaultgfx_vline)(struct video_gfx *__restrict self,
                                        intptr_t x, intptr_t y, size_t length,
                                        video_color_t color) {
	uintptr_t temp;
	IF_OFFSET(x += self->vx_offt_x);
	IF_OFFSET(y += self->vx_offt_y);
	if unlikely(x < (intptr_t)GFX_XMIN)
		return;
	if unlikely(y < (intptr_t)GFX_YMIN) {
		y = (intptr_t)(GFX_YMIN - (uintptr_t)y);
		if unlikely(length <= (uintptr_t)y)
			return;
		length -= (uintptr_t)y;
		y = (intptr_t)GFX_YMIN;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)y, length, &temp) || temp > GFX_YEND) {
		if unlikely((uintptr_t)y >= GFX_YEND)
			return;
		length = GFX_YEND - (uintptr_t)y;
	}
	line_vert(self, (uintptr_t)x, (uintptr_t)y, length, color);
}






/************************************************************************/
/* FILL()                                                               */
/************************************************************************/
INTERN NONNULL((1)) void CC
GFX_FUNC(libvideo_gfx_defaultgfx_fill)(struct video_gfx *__restrict self,
                                       intptr_t x, intptr_t y,
                                       size_t size_x, size_t size_y,
                                       video_color_t color) {
	uintptr_t temp;
	if unlikely(!size_x)
		return;
	IF_OFFSET(x += self->vx_offt_x);
	IF_OFFSET(y += self->vx_offt_y);
	if unlikely(x < (intptr_t)GFX_XMIN) {
		x = (intptr_t)(GFX_XMIN - (uintptr_t)x);
		if unlikely(size_x <= (uintptr_t)x)
			return;
		size_x -= (uintptr_t)x;
		x = (intptr_t)GFX_XMIN;
	}
	if unlikely(y < (intptr_t)GFX_YMIN) {
		y = (intptr_t)(GFX_YMIN - (uintptr_t)y);
		if unlikely(size_y <= (uintptr_t)y)
			return;
		size_y -= (uintptr_t)y;
		y = (intptr_t)GFX_YMIN;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)x, size_x, &temp) || temp > GFX_XEND) {
		if unlikely((uintptr_t)x >= GFX_XEND)
			return;
		size_x = GFX_XEND - (uintptr_t)x;
	}
	if unlikely(OVERFLOW_UADD((uintptr_t)y, size_y, &temp) || temp > GFX_YEND) {
		if unlikely((uintptr_t)y >= GFX_YEND)
			return;
		size_y = GFX_YEND - (uintptr_t)y;
	}
	line_fill(self, (uintptr_t)x, (uintptr_t)y, size_x, size_y, color);
}




DECL_END

#ifndef __INTELLISENSE__

#ifndef DID_DEFINE_BLIT_FIRSTPASS
#define DID_DEFINE_BLIT_FIRSTPASS 1
#define DEFINE_BLIT_FIRSTPASS 1
#endif /* !DID_DEFINE_BLIT_FIRSTPASS */

#define DEFINE_BLIT 1
#include "gfx-blit.c.inl"

#define DEFINE_BITBLIT 1
#include "gfx-blit.c.inl"

#define DEFINE_BITFILL 1
#include "gfx-blit.c.inl"

#undef DEFINE_BLIT_FIRSTPASS
#undef GFX_XMIN
#undef GFX_YMIN
#undef GFX_XEND
#undef GFX_YEND
#undef GFX_XMAX
#undef GFX_YMAX

#undef IFELSE_NoOf
#undef IF_NORMAL
#undef IF_OFFSET
#undef GFX_FUNC
#undef DEFINE_GFX_OFFSET
#undef DEFINE_GFX_NORMAL
#endif /* !__INTELLISENSE__ */
