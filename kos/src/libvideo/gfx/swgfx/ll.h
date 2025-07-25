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
#ifndef GUARD_LIBVIDEO_GFX_SWGFX_LL_H
#define GUARD_LIBVIDEO_GFX_SWGFX_LL_H 1

#include "../swgfx.h"

/* When  low-level  GFX  functions want  to  call other
 * low-level GFX functions, these macros should be used */
#define _LL_getcolor      _video_swgfx_x_getcolor
#define _LL_putcolor      _video_swgfx_x_putcolor
#define _LL_putcolor_p    _video_swgfx_x_putcolor_p
#define _LL_getpixel      _video_swgfx_x_getpixel
#define _LL_setpixel      _video_swgfx_x_setpixel
#define _LL_absline_llhh  _video_swgfx_x_absline_llhh
#define _LL_absline_lhhl  _video_swgfx_x_absline_lhhl
#define _LL_absline_h     _video_swgfx_x_absline_h
#define _LL_absline_v     _video_swgfx_x_absline_v
#define _LL_absfill       _video_swgfx_x_absfill
#define _LL_absgradient   _video_swgfx_x_absgradient
#define _LL_absgradient_h _video_swgfx_x_absgradient_h
#define _LL_absgradient_v _video_swgfx_x_absgradient_v

#define LL_assert_x(self, x) \
	gfx_assertf((x) < (self)->vx_surf.vs_buffer->vb_xdim, "X coord too large (%" PRIuCRD " >= %" PRIuCRD ")", (x), (self)->vx_surf.vs_buffer->vb_xdim)
#define LL_assert_y(self, y) \
	gfx_assertf((y) < (self)->vx_surf.vs_buffer->vb_ydim, "Y coord too large (%" PRIuCRD " >= %" PRIuCRD ")", (y), (self)->vx_surf.vs_buffer->vb_ydim)
#define LL_assert_sx(self, x, sx)                                                        \
	(gfx_assert(sx),                                                                     \
	 gfx_assertf((x) + (sx) > (x), "X+SX overflows (%" PRIuCRD "+%" PRIuDIM ")", x, sx), \
	 gfx_assertf((x) + (sx) <= (self)->vx_surf.vs_buffer->vb_xdim, "X+SX coord too large (%" PRIuCRD "+%" PRIuCRD "{%" PRIuCRD "} >= %" PRIuCRD ")", x, sx, (x) + (sx), (self)->vx_surf.vs_buffer->vb_xdim))
#define LL_assert_sy(self, y, sy)                                                        \
	(gfx_assert(sy),                                                                     \
	 gfx_assertf((y) + (sy) > (y), "Y+SY overflows (%" PRIuCRD "+%" PRIuDIM ")", y, sy), \
	 gfx_assertf((y) + (sy) <= (self)->vx_surf.vs_buffer->vb_ydim, "Y+SY coord too large (%" PRIuCRD "+%" PRIuCRD "{%" PRIuCRD "} >= %" PRIuCRD ")", y, sy, (y) + (sy), (self)->vx_surf.vs_buffer->vb_ydim))
#define LL_assert_xy(self, x, y)          (LL_assert_x(self, x), LL_assert_y(self, y))
#define LL_assert_sxy(self, x, y, sx, sy) (LL_assert_sx(self, x, sx), LL_assert_sy(self, y, sy))

#define LL_getcolor(self, x, y) \
	(LL_assert_xy(self, x, y), _LL_getcolor(self, x, y))
#define LL_putcolor(self, x, y, color) \
	(LL_assert_xy(self, x, y), _LL_putcolor(self, x, y, color))
#define LL_putcolor_p(self, x, y, color) \
	(LL_assert_xy(self, x, y), _LL_putcolor_p(self, x, y, color))
#define LL_getpixel(self, x, y) \
	(LL_assert_xy(self, x, y), _LL_getpixel(self, x, y))
#define LL_setpixel(self, x, y, pixel) \
	(LL_assert_xy(self, x, y), _LL_setpixel(self, x, y, pixel))
#define LL_absline_llhh(self, x, y, size_x, size_y, color) \
	(LL_assert_sxy(self, x, y, size_x, size_y), _LL_absline_llhh(self, x, y, size_x, size_y, color))
#define LL_absline_lhhl(self, x, y, size_x, size_y, color)                                \
	(LL_assert_sx(self, x, size_x), gfx_assert(size_y), LL_assert_y(self, y),             \
	 gfx_assertf((y) >= (size_y) - 1,                                                     \
	             "Line escapes to the top (start-y: %" PRIuCRD ", size-y: %" PRIuDIM ")", \
	             (y), size_y),                                                            \
	 _LL_absline_lhhl(self, x, y, size_x, size_y, color))
#define LL_absline_h(self, x, y, length, color) \
	(LL_assert_sx(self, x, length), LL_assert_y(self, y), _LL_absline_h(self, x, y, length, color))
#define LL_absline_v(self, x, y, length, color) \
	(LL_assert_x(self, x), LL_assert_sy(self, y, length), _LL_absline_v(self, x, y, length, color))
#define LL_absfill(self, x, y, size_x, size_y, color) \
	(LL_assert_sxy(self, x, y, size_x, size_y), _LL_absfill(self, x, y, size_x, size_y, color))
#define LL_absgradient(self, x, y, size_x, size_y, colors) \
	(LL_assert_sxy(self, x, y, size_x, size_y), _LL_absgradient(self, x, y, size_x, size_y, colors))
#define LL_absgradient_h(self, x, y, size_x, size_y, locolor, hicolor) \
	(LL_assert_sxy(self, x, y, size_x, size_y), _LL_absgradient_h(self, x, y, size_x, size_y, locolor, hicolor))
#define LL_absgradient_v(self, x, y, size_x, size_y, locolor, hicolor) \
	(LL_assert_sxy(self, x, y, size_x, size_y), _LL_absgradient_v(self, x, y, size_x, size_y, locolor, hicolor))


/* Helpers for acquiring video region locks */
#define assert_video_regionlock_retains_region(lock, xmin, ymin, xdim, ydim) \
	(/*gfx_assert((lock)->_vrl_rect.vcr_xmin == (xmin)), -- might get        \
	 gfx_assert((lock)->_vrl_rect.vcr_ymin == (ymin)),   -- changed */       \
	 gfx_assert((lock)->_vrl_rect.vcr_xdim == (xdim)),                       \
	 gfx_assert((lock)->_vrl_rect.vcr_ydim == (ydim)))
#define LL_wlockregion(buffer, lock, xmin, ymin, xdim, ydim)                \
	(video_buffer_wlockregion(buffer, lock, xmin, ymin, xdim, ydim) == 0 && \
	 (assert_video_regionlock_retains_region(lock, xmin, ymin, xdim, ydim), 1))
#define LL_rlockregion(buffer, lock, xmin, ymin, xdim, ydim)                \
	(video_buffer_rlockregion(buffer, lock, xmin, ymin, xdim, ydim) == 0 && \
	 (assert_video_regionlock_retains_region(lock, xmin, ymin, xdim, ydim), 1))
#define LL_unlockregion(buffer, lock) \
	video_buffer_unlockregion(buffer, lock)

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_LL_H */
