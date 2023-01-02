/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif([](x) -> x.startswith("-O"));
gcc_opt.append("-O3"); // Force _all_ optimizations because stuff in here is performance-critical
]]]*/
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
#ifndef GUARD_LIBVIDEO_GFX_GFX_C
#define GUARD_LIBVIDEO_GFX_GFX_C 1
#define _KOS_SOURCE 1

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

#undef ASSERT_ABS_COORDS_IS_NOOP
#if !defined(NDEBUG) && 0
#define ASSERT_ABS_COORDS(self, x, y)                   \
	(assertf((x) >= (self)->vx_xmin &&                  \
	         (x) < (self)->vx_xend,                     \
	         "x       = %" PRIuPTR " (%#" PRIxPTR ")\n" \
	         "vx_xmin = %" PRIuPTR " (%#" PRIxPTR ")\n" \
	         "vx_xend = %" PRIuPTR " (%#" PRIxPTR ")",  \
	         (x), (x),                                  \
	         (self)->vx_xmin, (self)->vx_xmin,          \
	         (self)->vx_xend, (self)->vx_xend),         \
	 assertf((y) >= (self)->vx_ymin &&                  \
	         (y) < (self)->vx_yend,                     \
	         "y       = %" PRIuPTR " (%#" PRIxPTR ")\n" \
	         "vx_ymin = %" PRIuPTR " (%#" PRIxPTR ")\n" \
	         "vx_yend = %" PRIuPTR " (%#" PRIxPTR ")",  \
	         (y), (y),                                  \
	         (self)->vx_ymin, (self)->vx_ymin,          \
	         (self)->vx_yend, (self)->vx_yend))
#else /* !NDEBUG */
#define ASSERT_ABS_COORDS(self, x, y) (void)0
#define ASSERT_ABS_COORDS_IS_NOOP 1
#endif /* NDEBUG */


#define video_gfx_getabscolor(self, abs_x, abs_y) \
	(ASSERT_ABS_COORDS(self, abs_x, abs_y), (*(self)->vx_pxops.fxo_getcolor)(self, abs_x, abs_y))
#define video_gfx_putabscolor(self, abs_x, abs_y, color) \
	(ASSERT_ABS_COORDS(self, abs_x, abs_y), (*(self)->vx_pxops.fxo_putcolor)(self, abs_x, abs_y, color))

#ifdef ASSERT_ABS_COORDS_IS_NOOP
#undef video_gfx_getabscolor
#undef video_gfx_putabscolor
#define video_gfx_getabscolor(self, abs_x, abs_y) \
	(*(self)->vx_pxops.fxo_getcolor)(self, abs_x, abs_y)
#define video_gfx_putabscolor(self, abs_x, abs_y, color) \
	(*(self)->vx_pxops.fxo_putcolor)(self, abs_x, abs_y, color)
#endif /* ASSERT_ABS_COORDS_IS_NOOP */


LOCAL NONNULL((1)) void CC
line_llhh(struct video_gfx *__restrict self,
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

LOCAL NONNULL((1)) void CC
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
			                      y - (size_t)(((uint64_t)sizey * step) / sizex),
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

#if 0
#define line_hori(self, x, y, length, color) \
	do {                                     \
		uintptr_t _x = (x);                  \
		uintptr_t _y = (y);                  \
		size_t _len  = (length);             \
		uintptr_t _i;                        \
		for (_i = 0; _i < _len; ++_i) {      \
			video_gfx_putabscolor(self,      \
			                      _x + _i,   \
			                      _y,        \
			                      color);    \
		}                                    \
	}	__WHILE0
#define line_vert(self, x, y, length, color) \
	do {                                     \
		uintptr_t _x = (x);                  \
		uintptr_t _y = (y);                  \
		size_t _len  = (length);             \
		uintptr_t _i;                        \
		for (_i = 0; _i < _len; ++_i) {      \
			video_gfx_putabscolor(self,      \
			                      _x,        \
			                      _y + _i,   \
			                      color);    \
		}                                    \
	}	__WHILE0
#else
LOCAL NONNULL((1)) void CC
line_hori(struct video_gfx *__restrict self,
          uintptr_t x, uintptr_t y, size_t length,
          video_color_t color) {
	uintptr_t i;
	for (i = 0; i < length; ++i) {
		video_gfx_putabscolor(self,
		                      x + i,
		                      y,
		                      color);
	}
}

LOCAL NONNULL((1)) void CC
line_vert(struct video_gfx *__restrict self,
          uintptr_t x, uintptr_t y, size_t length,
          video_color_t color) {
	uintptr_t i;
	for (i = 0; i < length; ++i) {
		video_gfx_putabscolor(self,
		                      x,
		                      y + i,
		                      color);
	}
}
#endif

LOCAL NONNULL((1)) void CC
line_fill(struct video_gfx *__restrict self,
          uintptr_t x, uintptr_t y,
          size_t size_x, size_t size_y,
          video_color_t color) {
	uintptr_t iy;
	for (iy = 0; iy < size_y; ++iy) {
		line_hori(self, x, y + iy, size_x, color);
	}
}


#ifndef __INTELLISENSE__
DECL_END

#define DEFINE_GFX_NORMAL 1
#include "gfx-impl.c.inl"
#define DEFINE_GFX_OFFSET 1
#include "gfx-impl.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */


PRIVATE struct video_gfx_ops libvideo_gfx_defaultgfx_ops = {};
INTERN ATTR_RETNONNULL WUNUSED
struct video_gfx_ops *CC libvideo_gfx_defaultgfx_getops(void) {
	if (!libvideo_gfx_defaultgfx_ops.fxo_line) {
		libvideo_gfx_defaultgfx_ops.fxo_vline          = &libvideo_gfx_defaultgfx_vline;
		libvideo_gfx_defaultgfx_ops.fxo_hline          = &libvideo_gfx_defaultgfx_hline;
		libvideo_gfx_defaultgfx_ops.fxo_fill           = &libvideo_gfx_defaultgfx_fill;
		libvideo_gfx_defaultgfx_ops.fxo_rect           = &libvideo_gfx_defaultgfx_rect;
		libvideo_gfx_defaultgfx_ops.fxo_blit           = &libvideo_gfx_defaultgfx_blit;
		libvideo_gfx_defaultgfx_ops.fxo_stretch        = &libvideo_gfx_defaultgfx_stretch;
		libvideo_gfx_defaultgfx_ops.fxo_bitfill        = &libvideo_gfx_defaultgfx_bitfill;
		libvideo_gfx_defaultgfx_ops.fxo_bitblit        = &libvideo_gfx_defaultgfx_bitblit;
		libvideo_gfx_defaultgfx_ops.fxo_bitstretchfill = &libvideo_gfx_defaultgfx_bitstretchfill;
		libvideo_gfx_defaultgfx_ops.fxo_bitstretchblit = &libvideo_gfx_defaultgfx_bitstretchblit;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_defaultgfx_ops.fxo_line = &libvideo_gfx_defaultgfx_line;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_gfx_defaultgfx_ops;
}

PRIVATE struct video_gfx_ops libvideo_gfx_defaultgfx_ops_o = {};
INTERN ATTR_RETNONNULL WUNUSED
struct video_gfx_ops *CC libvideo_gfx_defaultgfx_getops_o(void) {
	if (!libvideo_gfx_defaultgfx_ops_o.fxo_line) {
		libvideo_gfx_defaultgfx_ops_o.fxo_vline          = &libvideo_gfx_defaultgfx_vline_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_hline          = &libvideo_gfx_defaultgfx_hline_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_fill           = &libvideo_gfx_defaultgfx_fill_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_rect           = &libvideo_gfx_defaultgfx_rect_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_blit           = &libvideo_gfx_defaultgfx_blit_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_stretch        = &libvideo_gfx_defaultgfx_stretch_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_bitfill        = &libvideo_gfx_defaultgfx_bitfill_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_bitblit        = &libvideo_gfx_defaultgfx_bitblit_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_bitstretchfill = &libvideo_gfx_defaultgfx_bitstretchfill_o;
		libvideo_gfx_defaultgfx_ops_o.fxo_bitstretchblit = &libvideo_gfx_defaultgfx_bitstretchblit_o;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_defaultgfx_ops_o.fxo_line = &libvideo_gfx_defaultgfx_line_o;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_gfx_defaultgfx_ops_o;
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_C */
