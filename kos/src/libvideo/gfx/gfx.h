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
#ifndef GUARD_LIBVIDEO_GFX_GFX_H
#define GUARD_LIBVIDEO_GFX_GFX_H 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/typecore.h>

#include <stdbool.h>
#include <stdint.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

/* List of blend modes for which we provide dedicated implementations.
 * iow: these are the blend modes that are "fast" */
#define GFX_FOREACH_DEDICATED_BLENDMODE(cb /*(name, mode)*/)   \
	cb(alpha, GFX_BLENDMODE_ALPHA)                             \
	cb(alpha_premultiplied, GFX_BLENDMODE_ALPHA_PREMULTIPLIED) \
	cb(add, GFX_BLENDMODE_ADD)                                 \
	cb(add_premultiplied, GFX_BLENDMODE_ADD_PREMULTIPLIED)     \
	cb(mod, GFX_BLENDMODE_MOD)                                 \
	cb(mul, GFX_BLENDMODE_MUL)

#ifndef PRIdOFF
#include <inttypes.h>
#define PRIdOFF PRIdN(__SIZEOF_VIDEO_OFFSET_T__)
#define PRIxOFF PRIxN(__SIZEOF_VIDEO_OFFSET_T__)
#define PRIuCRD PRIuN(__SIZEOF_VIDEO_COORD_T__)
#define PRIxCRD PRIxN(__SIZEOF_VIDEO_COORD_T__)
#define PRIuDIM PRIuN(__SIZEOF_VIDEO_DIM_T__)
#define PRIxDIM PRIxN(__SIZEOF_VIDEO_DIM_T__)
#define PRIxCOL PRIxN(__SIZEOF_VIDEO_COLOR_T__)
#endif /* !PRIdOFF */

#undef GFX_DEBUG
#if !defined(NDEBUG) && 0
#define GFX_DEBUG
#endif

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

#define gfx_assert_absbounds_buffer_x(self, x) \
	gfx_assertf((x) < (self)->vx_buffer->vb_xdim, "X coord is greater than buffer (%" PRIuCRD " >= %" PRIuCRD ")", (x), (self)->vx_buffer->vb_xdim)
#define gfx_assert_absbounds_buffer_y(self, y) \
	gfx_assertf((y) < (self)->vx_buffer->vb_ydim, "Y coord is greater than buffer (%" PRIuCRD " >= %" PRIuCRD ")", (y), (self)->vx_buffer->vb_ydim)
#define gfx_assert_absbounds_buffer(self, x, y) \
	(gfx_assert_absbounds_buffer_x(self, x),    \
	 gfx_assert_absbounds_buffer_y(self, y))

#define gfx_assert_imatrix2d(m)                     \
	(gfx_assert((m)[0][0] >= -1 && (m)[0][0] <= 1), \
	 gfx_assert((m)[0][1] >= -1 && (m)[0][1] <= 1), \
	 gfx_assert((m)[1][0] >= -1 && (m)[1][0] <= 1), \
	 gfx_assert((m)[1][1] >= -1 && (m)[1][1] <= 1))

/* Video GFX internal API wrappers */
#define _video_gfx_x_getcolor(self, x, y) \
	(*(self)->_vx_xops.vgfx_getcolor)(self, x, y)
#define _video_gfx_x_putcolor(self, x, y, color) \
	(*(self)->_vx_xops.vgfx_putcolor)(self, x, y, color)
#define _video_gfx_x_getpixel(self, x, y) \
	(*(self)->_vx_xops.vgfx_getpixel)(self, x, y)
#define _video_gfx_x_setpixel(self, x, y, pixel) \
	(*(self)->_vx_xops.vgfx_setpixel)(self, x, y, pixel)
#define _video_gfx_x_absline_llhh(self, x, y, size_x, size_y, color) \
	(*(self)->_vx_xops.vgfx_absline_llhh)(self, x, y, size_x, size_y, color)
#define _video_gfx_x_absline_lhhl(self, x, y, size_x, size_y, color) \
	(*(self)->_vx_xops.vgfx_absline_lhhl)(self, x, y, size_x, size_y, color)
#define _video_gfx_x_absline_h(self, x, y, length, color) \
	(*(self)->_vx_xops.vgfx_absline_h)(self, x, y, length, color)
#define _video_gfx_x_absline_v(self, x, y, length, color) \
	(*(self)->_vx_xops.vgfx_absline_v)(self, x, y, length, color)
#define _video_gfx_x_absfill(self, x, y, size_x, size_y, color) \
	(*(self)->_vx_xops.vgfx_absfill)(self, x, y, size_x, size_y, color)
#define _video_gfx_x_absfillmask(self, dst_x, dst_y, size_x, size_y, bg_fg_colors, bm) \
	(*(self)->_vx_xops.vgfx_absfillmask)(self, dst_x, dst_y, size_x, size_y, bg_fg_colors, bm)
#define _video_gfx_x_absfillstretchmask(self, dst_x, dst_y, dst_size_x, dst_size_y, bg_fg_colors, src_size_x, src_size_y, bm) \
	(*(self)->_vx_xops.vgfx_absfillstretchmask)(self, dst_x, dst_y, dst_size_x, dst_size_y, bg_fg_colors, src_size_x, src_size_y, bm)
#define _video_gfx_x_absgradient(self, x, y, size_x, size_y, colors) \
	(*(self)->_vx_xops.vgfx_absgradient)(self, x, y, size_x, size_y, colors)
#define _video_gfx_x_absgradient_h(self, x, y, size_x, size_y, locolor, hicolor) \
	(*(self)->_vx_xops.vgfx_absgradient_h)(self, x, y, size_x, size_y, locolor, hicolor)
#define _video_gfx_x_absgradient_v(self, x, y, size_x, size_y, locolor, hicolor) \
	(*(self)->_vx_xops.vgfx_absgradient_v)(self, x, y, size_x, size_y, locolor, hicolor)

#define _video_gfx_x_getcolor_xyswap(self, x, y) \
	(*(self)->_vx_xops.vgfx_getcolor)(self, y, x)
#define _video_gfx_x_putcolor_xyswap(self, x, y, color) \
	(*(self)->_vx_xops.vgfx_putcolor)(self, y, x, color)
#define _video_gfx_x_getpixel_xyswap(self, x, y) \
	(*(self)->_vx_xops.vgfx_getpixel)(self, y, x)
#define _video_gfx_x_setpixel_xyswap(self, x, y, pixel) \
	(*(self)->_vx_xops.vgfx_setpixel)(self, y, x, pixel)
#define _video_gfx_x_absline_llhh_xyswap(self, x, y, size_x, size_y, color) \
	(*(self)->_vx_xops.vgfx_absline_llhh)(self, y, x, size_x, size_y, color)
#define _video_gfx_x_absline_lhhl_xyswap(self, x, y, size_x, size_y, color) \
	(*(self)->_vx_xops.vgfx_absline_lhhl)(self, y, x, size_x, size_y, color)
#define _video_gfx_x_absline_h_xyswap(self, x, y, length, color) \
	(*(self)->_vx_xops.vgfx_absline_v)(self, y, x, length, color)
#define _video_gfx_x_absline_v_xyswap(self, x, y, length, color) \
	(*(self)->_vx_xops.vgfx_absline_h)(self, y, x, length, color)
#define _video_gfx_x_absfill_xyswap(self, x, y, size_x, size_y, color) \
	(*(self)->_vx_xops.vgfx_absfill)(self, y, x, size_y, size_x, color)
#define _video_gfx_x_absfillmask_xyswap(self, dst_x, dst_y, size_x, size_y, bg_fg_colors, bm) \
	(*(self)->_vx_xops.vgfx_absfillmask)(self, dst_y, dst_x, size_y, size_x, bg_fg_colors, bm) /* TODO: Need different impl here (one that swaps coords in bitmap, too) */
#define _video_gfx_x_absfillstretchmask_xyswap(self, dst_x, dst_y, dst_size_x, dst_size_y, bg_fg_colors, src_size_x, src_size_y, bm) \
	(*(self)->_vx_xops.vgfx_absfillstretchmask)(self, dst_y, dst_x, dst_size_y, dst_size_x, bg_fg_colors, src_size_y, src_size_x, bm) /* TODO: Need different impl here (one that swaps coords in bitmap, too) */
#define _video_gfx_x_absgradient_xyswap(self, x, y, size_x, size_y, colors) \
	(*(self)->_vx_xops.vgfx_absgradient)(self, y, x, size_y, size_x, colors)
#define _video_gfx_x_absgradient_h_xyswap(self, x, y, size_x, size_y, locolor, hicolor) \
	(*(self)->_vx_xops.vgfx_absgradient_v)(self, y, x, size_y, size_x, locolor, hicolor)
#define _video_gfx_x_absgradient_v_xyswap(self, x, y, size_x, size_y, locolor, hicolor) \
	(*(self)->_vx_xops.vgfx_absgradient_h)(self, y, x, size_y, size_x, locolor, hicolor)


/* Video GFX internal API wrappers (w/ assertions) */
#define video_gfx_x_getcolor(self, x, y) \
	(gfx_assert_absbounds_xy(self, x, y), _video_gfx_x_getcolor(self, x, y))
#define video_gfx_x_putcolor(self, x, y, color) \
	(gfx_assert_absbounds_xy(self, x, y), _video_gfx_x_putcolor(self, x, y, color))
#define video_gfx_x_getpixel(self, x, y) \
	(gfx_assert_absbounds_xy(self, x, y), _video_gfx_x_getpixel(self, x, y))
#define video_gfx_x_setpixel(self, x, y, pixel) \
	(gfx_assert_absbounds_xy(self, x, y), _video_gfx_x_setpixel(self, x, y, pixel))
#define video_gfx_x_absline_llhh(self, x, y, size_x, size_y, color) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),          \
	 _video_gfx_x_absline_llhh(self, x, y, size_x, size_y, color))
#define video_gfx_x_absline_lhhl(self, x, y, size_x, size_y, color)                       \
	(gfx_assert_absbounds_sx(self, x, size_x),                                            \
	 gfx_assert_absbounds_ymin(self, y),                                                  \
	 gfx_assert(size_y),                                                                  \
	 gfx_assertf(((y) - (self)->vx_hdr.vxh_bymin) >= (size_y) - 1,                        \
	             "Line escapes to the top (start-y: %" PRIuCRD ", size-y: %" PRIuDIM ", " \
	             "min-y: %" PRIuCRD ")",                                                  \
	             (y), size_y, (self)->vx_hdr.vxh_bymin),                                  \
	 _video_gfx_x_absline_lhhl(self, x, y, size_x, size_y, color))
#define video_gfx_x_absline_h(self, x, y, length, color)                        \
	(gfx_assert_absbounds_y(self, y), gfx_assert_absbounds_sx(self, x, length), \
	 _video_gfx_x_absline_h(self, x, y, length, color))
#define video_gfx_x_absline_v(self, x, y, length, color)                        \
	(gfx_assert_absbounds_x(self, x), gfx_assert_absbounds_sy(self, y, length), \
	 _video_gfx_x_absline_v(self, x, y, length, color))
#define video_gfx_x_absfill(self, x, y, size_x, size_y, color) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),     \
	 _video_gfx_x_absfill(self, x, y, size_x, size_y, color))
#define video_gfx_x_absfillmask(self, dst_x, dst_y, size_x, size_y, bg_fg_colors, bm) \
	(gfx_assert_absbounds_sxy(self, dst_x, dst_y, size_x, size_y),                    \
	 _video_gfx_x_absfillmask(self, dst_x, dst_y, size_x, size_y, bg_fg_colors, bm))
#define video_gfx_x_absfillstretchmask(self, dst_x, dst_y, dst_size_x, dst_size_y, bg_fg_colors, src_size_x, src_size_y, bm) \
	(gfx_assert_absbounds_sxy(self, dst_x, dst_y, dst_size_x, dst_size_y),                                                         \
	 gfx_assert(src_size_x), gfx_assert(src_size_y),                                                                               \
	 gfx_assertf((dst_size_x) != (src_size_x) || (dst_size_y) != (src_size_y),                                                     \
	             "dst/src size identical: {%" PRIuDIM "x%" PRIuDIM "}", dst_size_x, dst_size_y),                                   \
	 _video_gfx_x_absfillstretchmask(self, dst_x, dst_y, dst_size_x, dst_size_y, bg_fg_colors, src_size_x, src_size_y, bm))
#define video_gfx_x_absgradient(self, x, y, size_x, size_y, colors) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),          \
	 _video_gfx_x_absgradient(self, x, y, size_x, size_y, colors))
#define video_gfx_x_absgradient_h(self, x, y, size_x, size_y, locolor, hicolor) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                      \
	 _video_gfx_x_absgradient_h(self, x, y, size_x, size_y, locolor, hicolor))
#define video_gfx_x_absgradient_v(self, x, y, size_x, size_y, locolor, hicolor) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                      \
	 _video_gfx_x_absgradient_v(self, x, y, size_x, size_y, locolor, hicolor))

#define video_gfx_x_getcolor_xyswap(self, x, y) \
	(gfx_assert_absbounds_xy(self, x, y), _video_gfx_x_getcolor_xyswap(self, x, y))
#define video_gfx_x_putcolor_xyswap(self, x, y, color) \
	(gfx_assert_absbounds_xy(self, x, y), _video_gfx_x_putcolor_xyswap(self, x, y, color))
#define video_gfx_x_getpixel_xyswap(self, x, y) \
	(gfx_assert_absbounds_xy(self, x, y), _video_gfx_x_getpixel_xyswap(self, x, y))
#define video_gfx_x_setpixel_xyswap(self, x, y, pixel) \
	(gfx_assert_absbounds_xy(self, x, y), _video_gfx_x_setpixel_xyswap(self, x, y, pixel))
#define video_gfx_x_absline_llhh_xyswap(self, x, y, size_x, size_y, color) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                 \
	 _video_gfx_x_absline_llhh_xyswap(self, x, y, size_x, size_y, color))
#define video_gfx_x_absline_lhhl_xyswap(self, x, y, size_x, size_y, color)                \
	(gfx_assert_absbounds_sx(self, x, size_x),                                            \
	 gfx_assert_absbounds_ymin(self, y),                                                  \
	 gfx_assert(size_y),                                                                  \
	 gfx_assertf(((y) - (self)->vx_hdr.vxh_bymin) >= (size_y) - 1,                        \
	             "Line escapes to the top (start-y: %" PRIuCRD ", size-y: %" PRIuDIM ", " \
	             "min-y: %" PRIuCRD ")",                                                  \
	             (y), size_y, (self)->vx_hdr.vxh_bymin),                                  \
	 _video_gfx_x_absline_lhhl_xyswap(self, x, y, size_x, size_y, color))
#define video_gfx_x_absline_h_xyswap(self, x, y, length, color)                 \
	(gfx_assert_absbounds_y(self, y), gfx_assert_absbounds_sx(self, x, length), \
	 _video_gfx_x_absline_h_xyswap(self, x, y, length, color))
#define video_gfx_x_absline_v_xyswap(self, x, y, length, color)                 \
	(gfx_assert_absbounds_x(self, x), gfx_assert_absbounds_sy(self, y, length), \
	 _video_gfx_x_absline_v_xyswap(self, x, y, length, color))
#define video_gfx_x_absfill_xyswap(self, x, y, size_x, size_y, color) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),            \
	 _video_gfx_x_absfill_xyswap(self, x, y, size_x, size_y, color))
#define video_gfx_x_absfillmask_xyswap(self, dst_x, dst_y, size_x, size_y, bg_fg_colors, bm) \
	(gfx_assert_absbounds_sxy(self, dst_x, dst_y, size_x, size_y),                           \
	 _video_gfx_x_absfillmask_xyswap(self, dst_x, dst_y, size_x, size_y, bg_fg_colors, bm))
#define video_gfx_x_absfillstretchmask_xyswap(self, dst_x, dst_y, dst_size_x, dst_size_y, bg_fg_colors, src_size_x, src_size_y, bm) \
	(gfx_assert_absbounds_sxy(self, dst_x, dst_y, dst_size_x, dst_size_y),                                                          \
	 gfx_assert(src_size_x), gfx_assert(src_size_y),                                                                                \
	 gfx_assertf((dst_size_x) != (src_size_x) || (dst_size_y) != (src_size_y),                                                      \
	             "dst/src size identical: {%" PRIuDIM "x%" PRIuDIM "}", dst_size_x, dst_size_y),                                    \
	 _video_gfx_x_absfillstretchmask_xyswap(self, dst_x, dst_y, dst_size_x, dst_size_y, bg_fg_colors, src_size_x, src_size_y, bm))
#define video_gfx_x_absgradient_xyswap(self, x, y, size_x, size_y, colors) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                 \
	 _video_gfx_x_absgradient_xyswap(self, x, y, size_x, size_y, colors))
#define video_gfx_x_absgradient_h_xyswap(self, x, y, size_x, size_y, locolor, hicolor) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                             \
	 _video_gfx_x_absgradient_h_xyswap(self, x, y, size_x, size_y, locolor, hicolor))
#define video_gfx_x_absgradient_v_xyswap(self, x, y, size_x, size_y, locolor, hicolor) \
	(gfx_assert_absbounds_sxy(self, x, y, size_x, size_y),                             \
	 _video_gfx_x_absgradient_v_xyswap(self, x, y, size_x, size_y, locolor, hicolor))


/* Video BLIT internal API wrappers */
#define _video_blitter_x_blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y) \
	(*(self)->_vbt_xops.vbtx_blit)(self, dst_x, dst_y, src_x, src_y, size_x, size_y)
#define _video_blitter_x_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y) \
	(*(self)->_vbt_xops.vbtx_stretch)(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y)
#define _video_blitter_x_blit_imatrix(self, dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix) \
	(*(self)->_vbt_xops.vbtx_blit_imatrix)(self, dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix)
#define _video_blitter_x_stretch_imatrix(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, src_matrix) \
	(*(self)->_vbt_xops.vbtx_stretch_imatrix)(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, src_matrix)

/* Video BLIT internal API wrappers (w/ assertions) */
#define video_blitter_x_blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y) \
	(gfx_assert_absbounds_sxy((self)->vbt_dst, dst_x, dst_y, size_x, size_y),  \
	 gfx_assert_absbounds_sxy((self)->vbt_src, src_x, src_y, size_x, size_y),  \
	 _video_blitter_x_blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y))
#define video_blitter_x_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y) \
	(gfx_assert_absbounds_sxy((self)->vbt_dst, dst_x, dst_y, dst_size_x, dst_size_y),                             \
	 gfx_assert_absbounds_sxy((self)->vbt_src, src_x, src_y, src_size_x, src_size_y),                             \
	 _video_blitter_x_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y))
#define video_blitter_x_blit_imatrix(self, dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix) \
	(/*gfx_assert_absbounds_sxy((self)->vbt_dst, dst_x, dst_y, size_x, size_y),*/                  \
	 /*gfx_assert_absbounds_sxy((self)->vbt_src, src_x, src_y, size_x, size_y),*/                  \
	 _video_blitter_x_blit_imatrix(self, dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix))
#define video_blitter_x_stretch_imatrix(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, src_matrix) \
	(/*gfx_assert_absbounds_sxy((self)->vbt_dst, dst_x, dst_y, dst_size_x, dst_size_y),*/                                             \
	 /*gfx_assert_absbounds_sxy((self)->vbt_src, src_x, src_y, src_size_x, src_size_y),*/                                             \
	 _video_blitter_x_stretch_imatrix(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, src_matrix))


DECL_BEGIN


/* # of bits to use for the fractional part of the fixed-
 * point  numbers used during nearest stretch operations. */
#define STRETCH_FP_NFRAC 16
typedef uint_fast64_t stretch_fp_t;      /* uint_fast{BITSOF(video_coord_t) + STRETCH_FP_NFRAC}_t */
typedef int_fast64_t sstretch_fp_t;      /* int_fast{BITSOF(video_coord_t) + STRETCH_FP_NFRAC}_t */
typedef uint_fast16_t stretch_fp_frac_t; /* uint_fast{STRETCH_FP_NFRAC}_t */
#define STRETCH_FP(whole)    ((stretch_fp_t)(whole) << STRETCH_FP_NFRAC)
#define STRETCH_FP_WHOLE(fp) ((video_coord_t)(fp) >> STRETCH_FP_NFRAC)
#define STRETCH_FP_FRAC(fp)  ((stretch_fp_frac_t)(fp) & (stretch_fp_frac_t)(STRETCH_FP(1) - 1))


/* Low-level, Generic, always-valid GFX color functions (using only `vgfx_getpixel' + `vgfx_setpixel') */
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic__getcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic__getcolor_blur(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic__getcolor_with_key(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__putcolor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__putcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
#define DECLARE_libvideo_gfx_generic__putcolor_FOO(name, mode) \
	INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__putcolor_##name(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
GFX_FOREACH_DEDICATED_BLENDMODE(DECLARE_libvideo_gfx_generic__putcolor_FOO)
#undef DECLARE_libvideo_gfx_generic__putcolor_FOO

/* Low-level, Generic, always-valid GFX functions (using only `vgfo_getcolor' + `vgfo_putcolor') */
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absline_llhh(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absline_lhhl(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absline_llhh_aa(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absline_lhhl_aa(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absline_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absline_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absfill(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_gfx_generic__absgradient(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absgradient_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absgradient_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC libvideo_gfx_generic__fillmask(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_gfx_generic__fillstretchmask_l(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_gfx_generic__fillstretchmask_n(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC libvideo_gfx_generic__blitfrom_l(struct video_blitter *__restrict ctx);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC libvideo_gfx_generic__blitfrom_n(struct video_blitter *__restrict ctx);

/* Low-level, Generic, always-valid Blit functions (using only `vgfo_getcolor' + `vgfo_putcolor') */
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) ATTR_IN(8) void CC libvideo_blitter_generic__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t const src_matrix);
INTDEF ATTR_IN(1) ATTR_IN(10) void CC libvideo_blitter_generic__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t const src_matrix);
INTDEF ATTR_IN(1) ATTR_IN(10) void CC libvideo_blitter_generic__stretch_imatrix_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t const src_matrix);
INTDEF ATTR_IN(1) void CC libvideo_blitter_samebuf__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_samebuf__stretch_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_samebuf__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) ATTR_IN(8) void CC libvideo_blitter_samebuf__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t const src_matrix);
INTDEF ATTR_IN(1) ATTR_IN(10) void CC libvideo_blitter_samebuf__stretch_imatrix_l(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t const src_matrix);
INTDEF ATTR_IN(1) ATTR_IN(10) void CC libvideo_blitter_samebuf__stretch_imatrix_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t const src_matrix);


/* Low-level, optimized GFX functions using `struct video_lock' (if available):
 * - *noblend*: Usable only when the relevant GFX's blend-mode is `GFX_BLENDMODE_OVERRIDE' */
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend__absline_llhh(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend__absline_lhhl(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend__absline_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend__absline_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend__absfill(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_gfx_noblend_interp8888__absgradient(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend_interp8888__absgradient_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend_interp8888__absgradient_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) ATTR_IN(7) void CC libvideo_gfx_noblend__fillmask1(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color, struct video_bitmask const *__restrict bm, __REGISTER_TYPE__ bm_xor);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC libvideo_gfx_noblend__fillmask(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_gfx_noblend__fillstretchmask_n(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) void CC libvideo_blitter_noblend_samebuf__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_noblend_samefmt__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_noblend_samefmt__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
#define libvideo_blitter_noblend_samefmt__stretch_l         libvideo_blitter_generic__stretch_l
#define libvideo_blitter_noblend_samebuf__blit_imatrix      libvideo_blitter_samebuf__blit_imatrix /* TODO */
#define libvideo_blitter_noblend_samefmt__blit_imatrix      libvideo_blitter_generic__blit_imatrix /* TODO */
#define libvideo_blitter_noblend_samefmt__stretch_imatrix_n libvideo_blitter_generic__stretch_imatrix_n
#define libvideo_blitter_noblend_samefmt__stretch_imatrix_l libvideo_blitter_generic__stretch_imatrix_l
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC libvideo_gfx_noblend__blitfrom_n(struct video_blitter *__restrict ctx);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC libvideo_gfx_noblend__blitfrom_l(struct video_blitter *__restrict ctx);

/* The *_difffmt_* operators here "libvideo_blitter_generic__conv" to be initialized */
#define libvideo_blitter_generic__conv(self) ((struct video_converter *)(self)->_vbt_driver)
INTDEF ATTR_IN(1) void CC libvideo_blitter_noblend_difffmt__blit(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_noblend_difffmt__stretch_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) ATTR_IN(8) void CC libvideo_blitter_noblend_difffmt__blit_imatrix(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, video_imatrix2d_t const src_matrix);
INTDEF ATTR_IN(1) ATTR_IN(10) void CC libvideo_blitter_noblend_difffmt__stretch_imatrix_n(struct video_blitter const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, video_imatrix2d_t const src_matrix);
#define libvideo_blitter_noblend_difffmt__stretch_l         libvideo_blitter_generic__stretch_l
#define libvideo_blitter_noblend_difffmt__stretch_imatrix_l libvideo_blitter_generic__stretch_imatrix_l


/* Generic GFX operators */
INTDEF ATTR_RETNONNULL ATTR_IN(1) struct video_gfx const *CC libvideo_gfx_generic_noblend(struct video_gfx const *__restrict self);
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic_getcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic_getcolor_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic_getcolor_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic_getcolor_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic_getcolor_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic_getcolor_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_putcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_putcolor_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_putcolor_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_putcolor_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_putcolor_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_putcolor_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_line(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_line_xyswap(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_line_wrap(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_line_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_line_mirror(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_line_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hline_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hline_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hline_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hline_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hline_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vline_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vline_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vline_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vline_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vline_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_fill(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_fill_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_fill_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_fill_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_fill_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_fill_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_rect(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_rect_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_rect_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_rect_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_rect_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_rect_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_gfx_generic_gradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_gfx_generic_gradient_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_gfx_generic_gradient_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_gfx_generic_gradient_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_gfx_generic_gradient_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_gfx_generic_gradient_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hgradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hgradient_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hgradient_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hgradient_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hgradient_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hgradient_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vgradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vgradient_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vgradient_wrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vgradient_wrap_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vgradient_mirror(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vgradient_mirror_xyswap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC libvideo_gfx_generic_fillmask(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC libvideo_gfx_generic_fillmask_wrap(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC libvideo_gfx_generic_fillmask_mirror(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_gfx_generic_fillstretchmask(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_gfx_generic_fillstretchmask_wrap(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_gfx_generic_fillstretchmask_mirror(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(4) void CC libvideo_gfx_generic_bitblit(struct video_gfx const *__restrict dst, video_offset_t dst_x, video_offset_t dst_y, struct video_gfx const *__restrict src, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_gfx_generic_stretch(struct video_gfx const *__restrict dst, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, struct video_gfx const *__restrict src, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_xyswap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_wrap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_wrap_xyswap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_mirror(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_mirror_xyswap(void);
#define libvideo_gfx_generic_ops                 (*_libvideo_gfx_generic_ops())
#define libvideo_gfx_generic_ops_xyswap          (*_libvideo_gfx_generic_ops_xyswap())
#define libvideo_gfx_generic_ops_wrap            (*_libvideo_gfx_generic_ops_wrap())
#define libvideo_gfx_generic_ops_wrap_xyswap     (*_libvideo_gfx_generic_ops_wrap_xyswap())
#define libvideo_gfx_generic_ops_mirror          (*_libvideo_gfx_generic_ops_mirror())
#define libvideo_gfx_generic_ops_mirror_xyswap   (*_libvideo_gfx_generic_ops_mirror_xyswap())

/* Generic blit operators */
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic_blit(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic_blit_imatrix(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic_blit_rdwrap(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic_blit_rdwrap_imatrix(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic_blit_wrap(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic_blit_wrap_imatrix(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic_stretch(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic_stretch_imatrix(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic_stretch_rdwrap(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic_stretch_rdwrap_imatrix(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic_stretch_wrap(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_generic_stretch_wrap_imatrix(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_blit_generic_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_blit_generic_ops_imatrix(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_blit_generic_ops_rdwrap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_blit_generic_ops_rdwrap_imatrix(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_blit_generic_ops_wrap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_blit_generic_ops_wrap_imatrix(void);
#define libvideo_blit_generic_ops                (*_libvideo_blit_generic_ops())                /* Support: - */
#define libvideo_blit_generic_ops_imatrix        (*_libvideo_blit_generic_ops_imatrix())        /* Support: src+dst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_blit_generic_ops_rdwrap         (*_libvideo_blit_generic_ops_rdwrap())         /* Support: src:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_blit_generic_ops_rdwrap_imatrix (*_libvideo_blit_generic_ops_rdwrap_imatrix()) /* Support: src:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+dst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_blit_generic_ops_wrap           (*_libvideo_blit_generic_ops_wrap())           /* Support: src+dst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_blit_generic_ops_wrap_imatrix   (*_libvideo_blit_generic_ops_wrap_imatrix())   /* Support: src+dst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+dst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */


/* Apply a clipping  rect to "self",  shrinking the  pixel
 * area relative to offsets specified by the given coords.
 *
 * Note that the clip area can  only ever be shrunk. To  go
 * back to the initial clip area, either keep a copy of the
 * original GFX  context, or  create a  new context  (which
 * always starts  out with  its clipping  area set  to  the
 * associated buffer's entire surface)
 *
 * @param: clip_x: Delta to add to the Clip Rect starting X coord.
 *                 When negative, extend clip rect with void-pixels to the left
 * @param: clip_y: Delta to add to the Clip Rect starting Y coord.
 *                 When negative, extend clip rect with void-pixels to the top
 * @param: size_x: New width of the clip rect. When greater than the old  clip
 *                 rect width, extend clip rect with void-pixels to the right.
 * @param: size_y: New height of the clip rect.  When greater than the old  clip
 *                 rect height, extend clip rect with void-pixels to the bottom.
 * @return: * : Always re-returns `self' */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *CC
libvideo_gfx_clip(struct video_gfx *__restrict self,
                  video_offset_t clip_x, video_offset_t clip_y,
                  video_dim_t size_x, video_dim_t size_y);

/* Translate virtual (offset) pixel coords to physical (coord) coords.
 * @param: x:      Virtual pixel X offset
 * @param: y:      Virtual pixel Y offset
 * @param: coords: The absolute (physical) coords of the pixel are stored here
 * @return: true:  Translation was successful
 * @return: false: The given x/y lie outside the I/O Rect of `self' */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC
libvideo_gfx_offset2coord(struct video_gfx const *__restrict self,
                          video_offset_t x, video_offset_t y,
                          video_coord_t coords[2]);

/* Translate physical (coord) pixel coords to virtual (offset) coords.
 * @param: x:       Physical pixel X coord
 * @param: y:       Physical pixel Y coord
 * @param: offsets: The offset (virtual) coords of the pixel are stored here
 * @return: true:  Translation was successful
 * @return: false: The given x/y lie outside the I/O Rect of `self' */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC
libvideo_gfx_coord2offset(struct video_gfx const *__restrict self,
                          video_coord_t x, video_coord_t y,
                          video_offset_t offsets[2]);


/* Perform geometric transformations on the contents of the current  clip
 * rect of `self'. Note that none of these functions alter pixel data  of
 * the underlying buffer; they only affect how the given `self' interacts
 * with pixel data of the underlying buffer.
 *
 * - video_gfx_xyswap:  Swap x/y coords (mirror pixel data along a diagonal starting in the top-left)
 * - video_gfx_hmirror: Mirror pixel data horizontally
 * - video_gfx_vmirror: Mirror pixel data vertically
 * - video_gfx_lrot90:  Rotate pixel data left 90°
 * - video_gfx_rrot90:  Rotate pixel data right 90°
 * - video_gfx_rot180:  Rotate pixel data 180°
 * - video_gfx_nrot90n: Rotate pixel data by left by 90*n°
 * - video_gfx_rrot90n: Rotate pixel data by right by 90*n° */
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_xyswap(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_hmirror(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_vmirror(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_lrot90(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_rrot90(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_rot180(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_lrot90n(struct video_gfx *__restrict self, int n);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_rrot90n(struct video_gfx *__restrict self, int n);




/* Initialize the clip / I/O rects of `self' to fully represent the underlying buffer fully. */
LOCAL ATTR_INOUT(1) void CC
libvideo_gfx_init_fullclip(struct video_gfx *__restrict self) {
	self->vx_hdr.vxh_bxmin = self->vx_hdr.vxh_cxoff = 0;
	self->vx_hdr.vxh_bymin = self->vx_hdr.vxh_cyoff = 0;
	if (self->vx_flags & VIDEO_GFX_F_XYSWAP) {
		self->vx_hdr.vxh_bxend = self->vx_hdr.vxh_cxsiz = self->vx_buffer->vb_ydim;
		self->vx_hdr.vxh_byend = self->vx_hdr.vxh_cysiz = self->vx_buffer->vb_xdim;
	} else {
		self->vx_hdr.vxh_bxend = self->vx_hdr.vxh_cxsiz = self->vx_buffer->vb_xdim;
		self->vx_hdr.vxh_byend = self->vx_hdr.vxh_cysiz = self->vx_buffer->vb_ydim;
	}
}

LOCAL ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC
libvideo_gfx_generic_ops_of(gfx_flag_t flags) {
	if (flags & VIDEO_GFX_F_XYSWAP) {
		if (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR))
			return &libvideo_gfx_generic_ops_mirror_xyswap;
		if (flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP))
			return &libvideo_gfx_generic_ops_wrap_xyswap;
		return &libvideo_gfx_generic_ops_xyswap;
	}
	if (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR))
		return &libvideo_gfx_generic_ops_mirror;
	if (flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP))
		return &libvideo_gfx_generic_ops_wrap;
	return &libvideo_gfx_generic_ops;
}

LOCAL ATTR_CONST WUNUSED bool CC
_blendinfo__is_add_or_subtract_or_max(unsigned int func) {
	return func == GFX_BLENDFUNC_ADD ||
	       func == GFX_BLENDFUNC_SUBTRACT ||
	       func == GFX_BLENDFUNC_MAX;
}

/* Update operator callbacks after the caller changed `what' */
LOCAL ATTR_INOUT(1) void CC
libvideo_gfx_generic_update(struct video_gfx *__restrict self, unsigned int what) {
	/* Update:
	 * - vx_hdr.vxh_ops */
	if (what & VIDEO_GFX_UPDATE_FLAGS) {
		/* Select generic operators based on wrapping rules */
		self->vx_hdr.vxh_ops = libvideo_gfx_generic_ops_of(self->vx_flags);
	}

	/* Update:
	 * - _vx_xops.vgfx_getcolor */
	if (what & (VIDEO_GFX_UPDATE_FLAGS | VIDEO_GFX_UPDATE_COLORKEY)) {
		/* Select how colors should be read. */
		if (self->vx_flags & VIDEO_GFX_F_BLUR) {
			self->_vx_xops.vgfx_getcolor = &libvideo_gfx_generic__getcolor_blur;
		} else if (!VIDEO_COLOR_ISTRANSPARENT(self->vx_colorkey)) {
			self->_vx_xops.vgfx_getcolor = &libvideo_gfx_generic__getcolor_with_key;
		} else if (self->vx_buffer->vb_format.vf_codec->vc_codec == VIDEO_CODEC_RGBA8888) {
			/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
			self->_vx_xops.vgfx_getcolor = self->_vx_xops.vgfx_getpixel;
		} else {
			self->_vx_xops.vgfx_getcolor = &libvideo_gfx_generic__getcolor_noblend;
		}
	}

	/* Update:
	 * - _vx_xops.vgfx_putcolor
	 * - _vx_xops.vgfx_absline_h
	 * - _vx_xops.vgfx_absline_v
	 * - _vx_xops.vgfx_absfill
	 * - _vx_xops.vgfx_absfillmask
	 * - _vx_xops.vgfx_absgradient
	 * - _vx_xops.vgfx_absgradient_h
	 * - _vx_xops.vgfx_absgradient_v */
	if (what & VIDEO_GFX_UPDATE_BLEND) {
		(void)__builtin_expect(self->vx_blend, GFX_BLENDMODE_OVERRIDE);
		(void)__builtin_expect(self->vx_blend, GFX_BLENDMODE_ALPHA);

		/* Detect special blend modes. */
		switch (self->vx_blend) {
		default:
			if (!(GFX_BLENDMODE_GET_SRCRGB(self->vx_blend) == GFX_BLENDDATA_ONE &&
			      GFX_BLENDMODE_GET_SRCA(self->vx_blend) == GFX_BLENDDATA_ONE &&
			      GFX_BLENDMODE_GET_DSTRGB(self->vx_blend) == GFX_BLENDDATA_ZERO &&
			      GFX_BLENDMODE_GET_DSTA(self->vx_blend) == GFX_BLENDDATA_ZERO &&
			      _blendinfo__is_add_or_subtract_or_max(GFX_BLENDMODE_GET_FUNRGB(self->vx_blend)) &&
			      _blendinfo__is_add_or_subtract_or_max(GFX_BLENDMODE_GET_FUNA(self->vx_blend)))) {
				/* Actual, custom blending */
				self->_vx_xops.vgfx_putcolor = &libvideo_gfx_generic__putcolor;
				break;
			}
			self->vx_blend = GFX_BLENDMODE_OVERRIDE; /* It essentially behaves the same, so... */
			ATTR_FALLTHROUGH
		case GFX_BLENDMODE_OVERRIDE:
			/* No blending is being done -> link operators that try to make use of direct memory access. */

			/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
			if (self->vx_buffer->vb_format.vf_codec->vc_codec == VIDEO_CODEC_RGBA8888) {
				self->_vx_xops.vgfx_putcolor = self->_vx_xops.vgfx_setpixel;
			} else {
				self->_vx_xops.vgfx_putcolor = &libvideo_gfx_generic__putcolor_noblend;
			}
			self->_vx_xops.vgfx_absline_h   = &libvideo_gfx_noblend__absline_h;
			self->_vx_xops.vgfx_absline_v   = &libvideo_gfx_noblend__absline_v;
			self->_vx_xops.vgfx_absfill     = &libvideo_gfx_noblend__absfill;
			self->_vx_xops.vgfx_absfillmask = &libvideo_gfx_noblend__fillmask;
			if (self->vx_buffer->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) {
				self->_vx_xops.vgfx_absgradient   = &libvideo_gfx_noblend_interp8888__absgradient;
				self->_vx_xops.vgfx_absgradient_h = &libvideo_gfx_noblend_interp8888__absgradient_h;
				self->_vx_xops.vgfx_absgradient_v = &libvideo_gfx_noblend_interp8888__absgradient_v;
			} else {
				self->_vx_xops.vgfx_absgradient   = &libvideo_gfx_generic__absgradient;
				self->_vx_xops.vgfx_absgradient_h = &libvideo_gfx_generic__absgradient_h;
				self->_vx_xops.vgfx_absgradient_v = &libvideo_gfx_generic__absgradient_v;
			}
			goto after_blend;

#define LINK_libvideo_gfx_generic__putcolor_FOO(name, mode)                        \
		case mode:                                                                 \
			self->_vx_xops.vgfx_putcolor = &libvideo_gfx_generic__putcolor_##name; \
			break;
		GFX_FOREACH_DEDICATED_BLENDMODE(LINK_libvideo_gfx_generic__putcolor_FOO)
#undef LINK_libvideo_gfx_generic__putcolor_FOO
		}
		/* Generic GFX operators that **do** have support for blending */
		self->_vx_xops.vgfx_absline_h     = &libvideo_gfx_generic__absline_h;
		self->_vx_xops.vgfx_absline_v     = &libvideo_gfx_generic__absline_v;
		self->_vx_xops.vgfx_absfill       = &libvideo_gfx_generic__absfill;
		self->_vx_xops.vgfx_absfillmask   = &libvideo_gfx_generic__fillmask;
		self->_vx_xops.vgfx_absgradient   = &libvideo_gfx_generic__absgradient;
		self->_vx_xops.vgfx_absgradient_h = &libvideo_gfx_generic__absgradient_h;
		self->_vx_xops.vgfx_absgradient_v = &libvideo_gfx_generic__absgradient_v;
after_blend:;
	}

	/* Update:
	 * - vx_hdr.vxh_blitfrom
	 * - _vx_xops.vgfx_absfillstretchmask
	 * - _vx_xops.vgfx_absline_llhh
	 * - _vx_xops.vgfx_absline_lhhl */
	if (what & (VIDEO_GFX_UPDATE_FLAGS | VIDEO_GFX_UPDATE_BLEND)) {
		/* Linear vs. Nearest blit */
		if (self->vx_blend == GFX_BLENDMODE_OVERRIDE) {
			if (!(self->vx_flags & VIDEO_GFX_F_LINEARBLIT)) {
				self->vx_hdr.vxh_blitfrom              = &libvideo_gfx_noblend__blitfrom_n;
				self->_vx_xops.vgfx_absfillstretchmask = &libvideo_gfx_noblend__fillstretchmask_n;
			} else {
				self->vx_hdr.vxh_blitfrom              = &libvideo_gfx_noblend__blitfrom_l;
				self->_vx_xops.vgfx_absfillstretchmask = &libvideo_gfx_generic__fillstretchmask_l;
			}
		} else {
			if (self->vx_flags & VIDEO_GFX_F_LINEARBLIT) {
				self->vx_hdr.vxh_blitfrom              = &libvideo_gfx_generic__blitfrom_l;
				self->_vx_xops.vgfx_absfillstretchmask = &libvideo_gfx_generic__fillstretchmask_l;
			} else {
				self->vx_hdr.vxh_blitfrom              = &libvideo_gfx_generic__blitfrom_n;
				self->_vx_xops.vgfx_absfillstretchmask = &libvideo_gfx_generic__fillstretchmask_n;
			}
		}

		/* Diagonal line drawing functions */
		if (self->vx_flags & VIDEO_GFX_F_AALINES) {
			self->_vx_xops.vgfx_absline_llhh = &libvideo_gfx_generic__absline_llhh_aa;
			self->_vx_xops.vgfx_absline_lhhl = &libvideo_gfx_generic__absline_lhhl_aa;
		} else if (self->vx_blend == GFX_BLENDMODE_OVERRIDE) {
			self->_vx_xops.vgfx_absline_llhh = &libvideo_gfx_noblend__absline_llhh;
			self->_vx_xops.vgfx_absline_lhhl = &libvideo_gfx_noblend__absline_lhhl;
		} else {
			self->_vx_xops.vgfx_absline_llhh = &libvideo_gfx_generic__absline_llhh;
			self->_vx_xops.vgfx_absline_lhhl = &libvideo_gfx_generic__absline_lhhl;
		}
	}
}

/* libvideo_gfx_generic_populate: fill in all
 * operators (except the get/set pixel)  ones
 * with generic impls.
 *
 * The caller must have already initialized:
 * - self->_vx_xops.vgfx_getpixel
 * - self->_vx_xops.vgfx_setpixel
 * - self->vx_flags
 * - self->vx_colorkey
 * - self->vx_blend
 * - self->vx_buffer */
LOCAL ATTR_INOUT(1) void CC
libvideo_gfx_generic_populate(struct video_gfx *__restrict self) {
	/* Line/fill operators... */
	libvideo_gfx_generic_update(self, VIDEO_GFX_UPDATE_ALL);
}

/* Same as `libvideo_gfx_generic_populate()', but load non-blending defaults */
LOCAL ATTR_INOUT(1) void CC
libvideo_gfx_generic_populate_noblend(struct video_gfx *__restrict self) {
	if (self->_vx_xops.vgfx_getcolor != self->_vx_xops.vgfx_getpixel)
		self->_vx_xops.vgfx_getcolor = &libvideo_gfx_generic__getcolor_noblend;
	if (self->_vx_xops.vgfx_putcolor != self->_vx_xops.vgfx_setpixel)
		self->_vx_xops.vgfx_putcolor = &libvideo_gfx_generic__putcolor_noblend;
	if (!(self->vx_flags & VIDEO_GFX_F_AALINES)) {
		self->_vx_xops.vgfx_absline_llhh = &libvideo_gfx_noblend__absline_llhh;
		self->_vx_xops.vgfx_absline_lhhl = &libvideo_gfx_noblend__absline_lhhl;
	}
	self->_vx_xops.vgfx_absline_h   = &libvideo_gfx_noblend__absline_h;
	self->_vx_xops.vgfx_absline_v   = &libvideo_gfx_noblend__absline_v;
	self->_vx_xops.vgfx_absfill     = &libvideo_gfx_noblend__absfill;
	self->_vx_xops.vgfx_absfillmask = &libvideo_gfx_noblend__fillmask;
	if (self->vx_buffer->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) {
		self->_vx_xops.vgfx_absgradient   = &libvideo_gfx_noblend_interp8888__absgradient;
		self->_vx_xops.vgfx_absgradient_h = &libvideo_gfx_noblend_interp8888__absgradient_h;
		self->_vx_xops.vgfx_absgradient_v = &libvideo_gfx_noblend_interp8888__absgradient_v;
	}
	if (!(self->vx_flags & VIDEO_GFX_F_LINEARBLIT)) {
		self->vx_hdr.vxh_blitfrom          = &libvideo_gfx_noblend__blitfrom_n;
		self->_vx_xops.vgfx_absfillstretchmask = &libvideo_gfx_noblend__fillstretchmask_n;
	} else {
		self->vx_hdr.vxh_blitfrom = &libvideo_gfx_noblend__blitfrom_l;
	}
}


/* Select appropriate operators for a video blit operations */
LOCAL ATTR_INOUT(1) void CC
video_blit_setops(struct video_blitter *__restrict ctx) {
	/* Select operators based on wrapping flags of src/dst */
	gfx_flag_t flags = ctx->vbt_dst->vx_flags | ctx->vbt_src->vx_flags;
	if (ctx->vbt_dst->vx_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
		ctx->vbt_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
		               ? &libvideo_blit_generic_ops_wrap_imatrix
		               : &libvideo_blit_generic_ops_wrap;
	} else if (ctx->vbt_src->vx_flags & (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_YWRAP)) {
		ctx->vbt_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
		               ? &libvideo_blit_generic_ops_rdwrap_imatrix
		               : &libvideo_blit_generic_ops_rdwrap;
	} else {
		ctx->vbt_ops = (flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP))
		               ? &libvideo_blit_generic_ops_imatrix
		               : &libvideo_blit_generic_ops;
	}
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_H */
