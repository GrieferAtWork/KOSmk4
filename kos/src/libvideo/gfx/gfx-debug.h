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
#ifndef GUARD_LIBVIDEO_GFX_GFX_DEBUG_H
#define GUARD_LIBVIDEO_GFX_GFX_DEBUG_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <stdbool.h>

#include <libvideo/color.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

DECL_BEGIN

#undef GFX_DEBUG
#if !defined(NDEBUG) && 1
#define GFX_DEBUG
#endif

#ifndef PRIdOFF
#include <inttypes.h>
#define PRIdOFF __PRIN_PREFIX(__SIZEOF_VIDEO_OFFSET_T__) "d"
#define PRIxOFF __PRIN_PREFIX(__SIZEOF_VIDEO_OFFSET_T__) "x"
#define PRIuCRD __PRIN_PREFIX(__SIZEOF_VIDEO_COORD_T__) "u"
#define PRIxCRD __PRIN_PREFIX(__SIZEOF_VIDEO_COORD_T__) "x"
#define PRIuDIM __PRIN_PREFIX(__SIZEOF_VIDEO_DIM_T__) "u"
#define PRIxDIM __PRIN_PREFIX(__SIZEOF_VIDEO_DIM_T__) "x"
#define PRIxCOL __PRIN_PREFIX(__SIZEOF_VIDEO_COLOR_T__) "x"
#endif /* !PRIdOFF */

#ifdef GFX_DEBUG
#include <sys/syslog.h>
#define TRACE_START(...) syslog(LOG_DEBUG, "[gfx] start: " __VA_ARGS__)
#define TRACE_END(...)   syslog(LOG_DEBUG, "[gfx] end: " __VA_ARGS__)
#else
#define TRACE_START(...) (void)0
#define TRACE_END(...)   (void)0
#endif

#ifndef GFX_DEBUG
#if 1 /* Turn GFX assertions into compile-time assumptions for max speed */
#ifdef __CRT_UBSAN_BUILTIN_UNREACHABLE
#undef __CRT_UBSAN_BUILTIN_UNREACHABLE
#undef __builtin_unreachable /* Disable binding of "__ubsan_handle_builtin_unreachable" */
#endif /* __CRT_UBSAN_BUILTIN_UNREACHABLE */
#define gfx_assert(x)       __builtin_assume(x)
#define gfx_assertf(x, ...) __builtin_assume(x)
#else
#define gfx_assert(x)       (void)0
#define gfx_assertf(x, ...) (void)0
#endif
#else /* GFX_DEBUG */
#include <assert.h>
#define gfx_assert  assert
#define gfx_assertf assertf
#endif /* !GFX_DEBUG */

#define gfx_assert_absbounds_xmin(self, x) \
	gfx_assertf((x) >= (self)->vx_hdr.vxh_bxmin, "X coord escapes to the left (%" PRIuCRD " < %" PRIuCRD ")", (x), (self)->vx_hdr.vxh_bxmin)
#define gfx_assert_absbounds_xend(self, x) \
	gfx_assertf((x) < (self)->vx_hdr.vxh_bxend, "X coord escapes to the right (%" PRIuCRD " >= %" PRIuCRD ")", (x), (self)->vx_hdr.vxh_bxend)
#define gfx_assert_absbounds_ymin(self, y) \
	gfx_assertf((y) >= (self)->vx_hdr.vxh_bymin, "Y coord escapes to the left (%" PRIuCRD " < %" PRIuCRD ")", (y), (self)->vx_hdr.vxh_bymin)
#define gfx_assert_absbounds_yend(self, y) \
	gfx_assertf((y) < (self)->vx_hdr.vxh_byend, "Y coord escapes to the right (%" PRIuCRD " >= %" PRIuCRD ")", (y), (self)->vx_hdr.vxh_byend)
#define gfx_assert_absbounds_sxend(self, x, sx)                                          \
	(gfx_assert(sx),                                                                     \
	 gfx_assertf((x) + (sx) > (x), "X+SX overflows (%" PRIuCRD "+%" PRIuDIM ")", x, sx), \
	 gfx_assertf((x) + (sx) <= (self)->vx_hdr.vxh_bxend, "X+SX coord escapes to the right (%" PRIuCRD "+%" PRIuCRD "{%" PRIuCRD "} >= %" PRIuCRD ")", x, sx, (x) + (sx), (self)->vx_hdr.vxh_bxend))
#define gfx_assert_absbounds_syend(self, y, sy)                                          \
	(gfx_assert(sy),                                                                     \
	 gfx_assertf((y) + (sy) > (y), "Y+SY overflows (%" PRIuCRD "+%" PRIuDIM ")", y, sy), \
	 gfx_assertf((y) + (sy) <= (self)->vx_hdr.vxh_byend, "Y+SY coord escapes to the right (%" PRIuCRD "+%" PRIuCRD "{%" PRIuCRD "} >= %" PRIuCRD ")", y, sy, (y) + (sy), (self)->vx_hdr.vxh_byend))
#define gfx_assert_absbounds_x(self, x)      (gfx_assert_absbounds_xmin(self, x), gfx_assert_absbounds_xend(self, x))
#define gfx_assert_absbounds_y(self, y)      (gfx_assert_absbounds_ymin(self, y), gfx_assert_absbounds_yend(self, y))
#define gfx_assert_absbounds_xy(self, x, y)  (gfx_assert_absbounds_x(self, x), gfx_assert_absbounds_y(self, y))
#define gfx_assert_absbounds_sx(self, x, sx) (gfx_assert_absbounds_xmin(self, x), gfx_assert_absbounds_sxend(self, x, sx))
#define gfx_assert_absbounds_sy(self, y, sy) (gfx_assert_absbounds_ymin(self, y), gfx_assert_absbounds_syend(self, y, sy))
#define gfx_assert_absbounds_sxy(self, x, y, sx, sy) \
	(gfx_assert_absbounds_sx(self, x, sx), gfx_assert_absbounds_sy(self, y, sy))

#define gfx_assert_imatrix2d(m)                      \
	(gfx_assert(video_imatrix2d_get(m, 0, 0) >= -1), \
	 gfx_assert(video_imatrix2d_get(m, 0, 0) <= 1),  \
	 gfx_assert(video_imatrix2d_get(m, 0, 1) >= -1), \
	 gfx_assert(video_imatrix2d_get(m, 0, 1) <= 1),  \
	 gfx_assert(video_imatrix2d_get(m, 1, 0) >= -1), \
	 gfx_assert(video_imatrix2d_get(m, 1, 0) <= 1),  \
	 gfx_assert(video_imatrix2d_get(m, 1, 1) >= -1), \
	 gfx_assert(video_imatrix2d_get(m, 1, 1) <= 1))

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_DEBUG_H */
