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

#include "api.h"

#include <hybrid/compiler.h>

#include <stdbool.h>
#include <stdint.h>

#include <libvideo/codec/types.h>
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

#if 0
#include <sys/syslog.h>
#define TRACE_START(...) syslog(LOG_DEBUG, "[gfx] start: " __VA_ARGS__)
#define TRACE_END(...)   syslog(LOG_DEBUG, "[gfx] end: " __VA_ARGS__)
#else
#define TRACE_START(...) (void)0
#define TRACE_END(...)   (void)0
#endif

#if defined(NDEBUG) || 1
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
#else /* ... */
#include <assert.h>
#define gfx_assert  assert
#define gfx_assertf assertf
#endif /* !... */

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
#define gfx_assert_absbounds_xy(self, x, y)  (gfx_assert_absbounds_x(self, x), gfx_assert_absbounds_x(self, y))
#define gfx_assert_absbounds_sx(self, x, sx) (gfx_assert_absbounds_xmin(self, x), gfx_assert_absbounds_sxend(self, x, sx))
#define gfx_assert_absbounds_sy(self, y, sy) (gfx_assert_absbounds_ymin(self, y), gfx_assert_absbounds_syend(self, y, sy))
#define gfx_assert_absbounds_sxy(self, x, y, sx, sy) \
	(gfx_assert_absbounds_sx(self, x, sx), gfx_assert_absbounds_sy(self, y, sy))

/* Video GFX internal API wrappers */
#define _video_gfx_x_getcolor(self, x, y) \
	(*(self)->_vx_xops.vgxo_getcolor)(self, x, y)
#define _video_gfx_x_putcolor(self, x, y, color) \
	(*(self)->_vx_xops.vgxo_putcolor)(self, x, y, color)
#define _video_gfx_x_getpixel(self, x, y) \
	(*(self)->_vx_xops.vgxo_getpixel)(self, x, y)
#define _video_gfx_x_setpixel(self, x, y, pixel) \
	(*(self)->_vx_xops.vgxo_setpixel)(self, x, y, pixel)
#define _video_gfx_x_absline_llhh(self, x, y, size_x, size_y, color) \
	(*(self)->_vx_xops.vgxo_absline_llhh)(self, x, y, size_x, size_y, color)
#define _video_gfx_x_absline_lhhl(self, x, y, size_x, size_y, color) \
	(*(self)->_vx_xops.vgxo_absline_lhhl)(self, x, y, size_x, size_y, color)
#define _video_gfx_x_absline_h(self, x, y, length, color) \
	(*(self)->_vx_xops.vgxo_absline_h)(self, x, y, length, color)
#define _video_gfx_x_absline_v(self, x, y, length, color) \
	(*(self)->_vx_xops.vgxo_absline_v)(self, x, y, length, color)
#define _video_gfx_x_absfill(self, x, y, size_x, size_y, color) \
	(*(self)->_vx_xops.vgxo_absfill)(self, x, y, size_x, size_y, color)
#define _video_gfx_x_bitfill(self, dst_x, dst_y, size_x, size_y, color, bm) \
	(*(self)->_vx_xops.vgxo_bitfill)(self, dst_x, dst_y, size_x, size_y, color, bm)
#define _video_gfx_x_bitstretchfill(self, dst_x, dst_y, dst_size_x, dst_size_y, color, src_size_x, src_size_y, bm) \
	(*(self)->_vx_xops.vgxo_bitstretchfill)(self, dst_x, dst_y, dst_size_x, dst_size_y, color, src_size_x, src_size_y, bm)


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
#define video_gfx_x_bitfill(self, dst_x, dst_y, size_x, size_y, color, bm) \
	(gfx_assert_absbounds_sxy(self, dst_x, dst_y, size_x, size_y),         \
	 _video_gfx_x_bitfill(self, dst_x, dst_y, size_x, size_y, color, bm))
#define video_gfx_x_bitstretchfill(self, dst_x, dst_y, dst_size_x, dst_size_y, color, src_size_x, src_size_y, bm) \
	(gfx_assert_absbounds_sxy(self, dst_x, dst_y, dst_size_x, dst_size_y),                                        \
	 gfx_assert(src_size_x), gfx_assert(src_size_y),                                                              \
	 gfx_assertf((dst_size_x) != (src_size_x) || (dst_size_y) != (src_size_y),                                    \
	             "dst/src size identical: {%" PRIuDIM "x%" PRIuDIM "}", dst_size_x, dst_size_y),                  \
	 _video_gfx_x_bitstretchfill(self, dst_x, dst_y, dst_size_x, dst_size_y, color, src_size_x, src_size_y, bm))


/* Video BLIT internal API wrappers */
#define _video_blit_x_blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y) \
	(*(self)->_vb_xops.vbxo_blit)(self, dst_x, dst_y, src_x, src_y, size_x, size_y)
#define _video_blit_x_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y) \
	(*(self)->_vb_xops.vbxo_stretch)(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y)
#define _video_blit_x_bitblit(self, dst_x, dst_y, src_x, src_y, size_x, size_y, bm) \
	(*(self)->_vb_xops.vbxo_bitblit)(self, dst_x, dst_y, src_x, src_y, size_x, size_y, bm)
#define _video_blit_x_bitstretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, bm) \
	(*(self)->_vb_xops.vbxo_bitstretch)(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, bm)

/* Video BLIT internal API wrappers (w/ assertions) */
#define video_blit_x_blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y)  \
	(gfx_assert_absbounds_sxy((self)->vb_dst, dst_x, dst_y, size_x, size_y), \
	 gfx_assert_absbounds_sxy((self)->vb_src, src_x, src_y, size_x, size_y), \
	 _video_blit_x_blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y))
#define video_blit_x_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y) \
	(gfx_assert_absbounds_sxy((self)->vb_dst, dst_x, dst_y, dst_size_x, dst_size_y),                           \
	 gfx_assert_absbounds_sxy((self)->vb_src, src_x, src_y, src_size_x, src_size_y),                           \
	 _video_blit_x_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y))
#define video_blit_x_bitblit(self, dst_x, dst_y, src_x, src_y, size_x, size_y, bm) \
	(gfx_assert_absbounds_sxy((self)->vb_dst, dst_x, dst_y, size_x, size_y),       \
	 gfx_assert_absbounds_sxy((self)->vb_src, src_x, src_y, size_x, size_y),       \
	 _video_blit_x_bitblit(self, dst_x, dst_y, src_x, src_y, size_x, size_y, bm))
#define video_blit_x_bitstretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, bm) \
	(gfx_assert_absbounds_sxy((self)->vb_dst, dst_x, dst_y, dst_size_x, dst_size_y),                                  \
	 gfx_assert_absbounds_sxy((self)->vb_src, src_x, src_y, src_size_x, src_size_y),                                  \
	 _video_blit_x_bitstretch(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y, bm))


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


/* Low-level, Generic, always-valid GFX color functions (using only `vgxo_getpixel' + `vgxo_setpixel') */
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic__getcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic__getcolor_blur(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic__getcolor_with_key(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__putcolor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__putcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
#define DECLARE_libvideo_gfx_generic__putcolor_FOO(name, mode) \
	INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__putcolor_##name(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
GFX_FOREACH_DEDICATED_BLENDMODE(DECLARE_libvideo_gfx_generic__putcolor_FOO)
#undef DECLARE_libvideo_gfx_generic__putcolor_FOO

/* Low-level, Generic, always-valid GFX functions (using only `fxo_getcolor' + `fxo_putcolor') */
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absline_llhh(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absline_lhhl(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absline_llhh_aa(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absline_lhhl_aa(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absline_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absline_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__absfill(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) ATTR_IN(7) void CC libvideo_gfx_generic__bitfill(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(9) void CC libvideo_gfx_generic__bitstretchfill_l(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t color, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(9) void CC libvideo_gfx_generic__bitstretchfill_n(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t color, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blit *CC libvideo_gfx_generic__blitfrom_l(struct video_blit *__restrict ctx);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blit *CC libvideo_gfx_generic__blitfrom_n(struct video_blit *__restrict ctx);

/* Low-level, Generic, always-valid Blit functions (using only `fxo_getcolor' + `fxo_putcolor') */
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__blit(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__stretch_l(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic__stretch_n(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) ATTR_IN(8) void CC libvideo_gfx_generic__bitblit(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(10) void CC libvideo_gfx_generic__bitstretch_l(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(10) void CC libvideo_gfx_generic__bitstretch_n(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) void CC libvideo_gfx_samebuf__blit(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_samebuf__stretch_l(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_samebuf__stretch_n(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) ATTR_IN(8) void CC libvideo_gfx_samebuf__bitblit(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(10) void CC libvideo_gfx_samebuf__bitstretch_l(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(10) void CC libvideo_gfx_samebuf__bitstretch_n(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);


/* Low-level, optimized GFX functions using `struct video_lock' (if available):
 * - *noblend*: Usable only when the relevant GFX's blend-mode is `GFX_BLENDMODE_OVERRIDE' */
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend__absline_llhh(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend__absline_lhhl(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend__absline_h(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend__absline_v(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend__absfill(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) ATTR_IN(7) void CC libvideo_gfx_noblend__bitfill(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(9) void CC libvideo_gfx_noblend__bitstretchfill_n(struct video_gfx const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t color, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend_samefmt__blit(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_noblend_samefmt__stretch_n(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
#define libvideo_gfx_noblend_samefmt__stretch_l libvideo_gfx_generic__stretch_l
INTDEF ATTR_IN(1) ATTR_IN(8) void CC libvideo_gfx_noblend_samefmt__bitblit(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(10) void CC libvideo_gfx_noblend_samefmt__bitstretch_n(struct video_blit const *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
#define libvideo_gfx_noblend_samefmt__bitstretch_l libvideo_gfx_generic__bitstretch_l
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blit *CC libvideo_gfx_noblend__blitfrom_n(struct video_blit *__restrict ctx);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blit *CC libvideo_gfx_noblend__blitfrom_l(struct video_blit *__restrict ctx);


/* Generic GFX operators */
INTDEF ATTR_RETNONNULL ATTR_IN(1) struct video_gfx const *CC libvideo_gfx_generic_noblend(struct video_gfx const *__restrict self);
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic_getcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_generic_getcolor_rdwrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_putcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_putcolor_wrwrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_line(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_line_wrwrap(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_hline_wrwrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_vline_wrwrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_fill(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_fill_wrwrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_rect(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_rect_wrwrap(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) ATTR_IN(7) void CC libvideo_gfx_generic_bitfill(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(7) void CC libvideo_gfx_generic_bitfill_wrwrap(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(9) void CC libvideo_gfx_generic_bitstretchfill(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t color, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(9) void CC libvideo_gfx_generic_bitstretchfill_wrwrap(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t color, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_rdwrap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_wrwrap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_rdwrwrap(void);
#define libvideo_gfx_generic_ops          (*_libvideo_gfx_generic_ops())
#define libvideo_gfx_generic_ops_rdwrap   (*_libvideo_gfx_generic_ops_rdwrap())
#define libvideo_gfx_generic_ops_wrwrap   (*_libvideo_gfx_generic_ops_wrwrap())
#define libvideo_gfx_generic_ops_rdwrwrap (*_libvideo_gfx_generic_ops_rdwrwrap())

/* Generic blit operators */
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_blit(struct video_blit const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_blit_rdwrap(struct video_blit const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_blit_wrap(struct video_blit const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_stretch(struct video_blit const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_stretch_rdwrap(struct video_blit const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_generic_stretch_wrap(struct video_blit const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) ATTR_IN(8) void CC libvideo_gfx_generic_bitblit(struct video_blit const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(8) void CC libvideo_gfx_generic_bitblit_rdwrap(struct video_blit const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(8) void CC libvideo_gfx_generic_bitblit_wrap(struct video_blit const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(10) void CC libvideo_gfx_generic_bitstretch(struct video_blit const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(10) void CC libvideo_gfx_generic_bitstretch_rdwrap(struct video_blit const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(10) void CC libvideo_gfx_generic_bitstretch_wrap(struct video_blit const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blit_ops const *CC _libvideo_blit_generic_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blit_ops const *CC _libvideo_blit_generic_ops_rdwrap(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blit_ops const *CC _libvideo_blit_generic_ops_wrap(void);
#define libvideo_blit_generic_ops        (*_libvideo_blit_generic_ops())
#define libvideo_blit_generic_ops_rdwrap (*_libvideo_blit_generic_ops_rdwrap())
#define libvideo_blit_generic_ops_wrap   (*_libvideo_blit_generic_ops_wrap())



LOCAL ATTR_CONST WUNUSED bool CC
_blendinfo__is_add_or_subtract_or_max(unsigned int func) {
	return func == GFX_BLENDFUNC_ADD ||
	       func == GFX_BLENDFUNC_SUBTRACT ||
	       func == GFX_BLENDFUNC_MAX;
}



INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfxhdr *CC
libvideo_gfxhdr_clip(struct video_gfxhdr *__restrict self,
                     video_offset_t clip_x, video_offset_t clip_y,
                     video_dim_t size_x, video_dim_t size_y);

/* Initialize the clip / I/O rects of `self' to fully represent the underlying buffer fully. */
LOCAL ATTR_INOUT(1) void CC
libvideo_gfx_init_fullclip(struct video_gfx *__restrict self) {
	self->vx_hdr.vxh_bxmin = self->vx_hdr.vxh_cxoff = 0;
	self->vx_hdr.vxh_bymin = self->vx_hdr.vxh_cyoff = 0;
	self->vx_hdr.vxh_bxend = self->vx_hdr.vxh_cxsiz = self->vx_buffer->vb_size_x;
	self->vx_hdr.vxh_byend = self->vx_hdr.vxh_cysiz = self->vx_buffer->vb_size_y;
}

/* libvideo_gfx_populate_generic: fill in all
 * operators (except the get/set pixel)  ones
 * with generic impls.
 *
 * The caller must have already initialized:
 * - self->_vx_xops.vgxo_getpixel
 * - self->_vx_xops.vgxo_setpixel
 * - self->vx_flags
 * - self->vx_colorkey
 * - self->vx_blend
 * - self->vx_buffer
 */
LOCAL ATTR_INOUT(1) void CC
libvideo_gfx_populate_generic(struct video_gfx *__restrict self) {
	/* Select generic operators based on wrapping rules */
	if (self->vx_flags & (VIDEO_GFX_FRDXWRAP | VIDEO_GFX_FRDYWRAP)) {
		if (self->vx_flags & (VIDEO_GFX_FWRXWRAP | VIDEO_GFX_FWRYWRAP)) {
			self->vx_hdr.vxh_ops = &libvideo_gfx_generic_ops_rdwrwrap;
		} else {
			self->vx_hdr.vxh_ops = &libvideo_gfx_generic_ops_rdwrap;
		}
	} else if (self->vx_flags & (VIDEO_GFX_FWRXWRAP | VIDEO_GFX_FWRYWRAP)) {
		self->vx_hdr.vxh_ops = &libvideo_gfx_generic_ops_wrwrap;
	} else {
		self->vx_hdr.vxh_ops = &libvideo_gfx_generic_ops;
	}

	/* Select how colors should be read. */
	if (self->vx_flags & VIDEO_GFX_FBLUR) {
		self->_vx_xops.vgxo_getcolor = &libvideo_gfx_generic__getcolor_blur;
	} else if (!VIDEO_COLOR_ISTRANSPARENT(self->vx_colorkey)) {
		self->_vx_xops.vgxo_getcolor = &libvideo_gfx_generic__getcolor_with_key;
	} else {
		self->_vx_xops.vgxo_getcolor = &libvideo_gfx_generic__getcolor_noblend;
	}

	/* Detect special blend modes. */
	(void)__builtin_expect(self->vx_blend, GFX_BLENDMODE_OVERRIDE);
	(void)__builtin_expect(self->vx_blend, GFX_BLENDMODE_ALPHA);
	switch (self->vx_blend) {
	case GFX_BLENDMODE_OVERRIDE:
		self->_vx_xops.vgxo_putcolor = &libvideo_gfx_generic__putcolor_noblend;
		break;
#define LINK_libvideo_gfx_generic__putcolor_FOO(name, mode)                    \
	case mode:                                                                 \
		self->_vx_xops.vgxo_putcolor = &libvideo_gfx_generic__putcolor_##name; \
		break;
	GFX_FOREACH_DEDICATED_BLENDMODE(LINK_libvideo_gfx_generic__putcolor_FOO)
#undef LINK_libvideo_gfx_generic__putcolor_FOO
	default:
		if (GFX_BLENDMODE_GET_SRCRGB(self->vx_blend) == GFX_BLENDDATA_ONE &&
		    GFX_BLENDMODE_GET_SRCA(self->vx_blend) == GFX_BLENDDATA_ONE &&
		    GFX_BLENDMODE_GET_DSTRGB(self->vx_blend) == GFX_BLENDDATA_ZERO &&
		    GFX_BLENDMODE_GET_DSTA(self->vx_blend) == GFX_BLENDDATA_ZERO &&
		    _blendinfo__is_add_or_subtract_or_max(GFX_BLENDMODE_GET_FUNRGB(self->vx_blend)) &&
		    _blendinfo__is_add_or_subtract_or_max(GFX_BLENDMODE_GET_FUNA(self->vx_blend))) {
			self->_vx_xops.vgxo_putcolor = &libvideo_gfx_generic__putcolor_noblend;
		} else {
			self->_vx_xops.vgxo_putcolor = &libvideo_gfx_generic__putcolor;
		}
		break;
	}

	/* Line/fill operators... */
	if (self->vx_flags & VIDEO_GFX_FAALINES) {
		self->_vx_xops.vgxo_absline_llhh = &libvideo_gfx_generic__absline_llhh_aa;
		self->_vx_xops.vgxo_absline_lhhl = &libvideo_gfx_generic__absline_lhhl_aa;
	} else {
		self->_vx_xops.vgxo_absline_llhh = &libvideo_gfx_generic__absline_llhh;
		self->_vx_xops.vgxo_absline_lhhl = &libvideo_gfx_generic__absline_lhhl;
	}
	self->_vx_xops.vgxo_absline_h = &libvideo_gfx_generic__absline_h;
	self->_vx_xops.vgxo_absline_v = &libvideo_gfx_generic__absline_v;
	self->_vx_xops.vgxo_absfill   = &libvideo_gfx_generic__absfill;
	self->_vx_xops.vgxo_bitfill   = &libvideo_gfx_generic__bitfill;

	/* Linear vs. Nearest blit */
	if (self->vx_flags & VIDEO_GFX_FLINEARBLIT) {
		self->vx_hdr.vxh_blitfrom          = &libvideo_gfx_generic__blitfrom_l;
		self->_vx_xops.vgxo_bitstretchfill = &libvideo_gfx_generic__bitstretchfill_l;
	} else {
		self->vx_hdr.vxh_blitfrom          = &libvideo_gfx_generic__blitfrom_n;
		self->_vx_xops.vgxo_bitstretchfill = &libvideo_gfx_generic__bitstretchfill_n;
	}

	/* Select optimal operator implementations based on requested features. */
	if (self->_vx_xops.vgxo_putcolor == &libvideo_gfx_generic__putcolor_noblend) {
		/* No blending is being done -> link operators that try to make use of direct memory access. */
		self->_vx_xops.vgxo_absline_llhh = &libvideo_gfx_noblend__absline_llhh;
		self->_vx_xops.vgxo_absline_lhhl = &libvideo_gfx_noblend__absline_lhhl;
		self->_vx_xops.vgxo_absline_h    = &libvideo_gfx_noblend__absline_h;
		self->_vx_xops.vgxo_absline_v    = &libvideo_gfx_noblend__absline_v;
		self->_vx_xops.vgxo_absfill      = &libvideo_gfx_noblend__absfill;
		self->_vx_xops.vgxo_bitfill      = &libvideo_gfx_noblend__bitfill;
		if (!(self->vx_flags & VIDEO_GFX_FLINEARBLIT)) {
			self->vx_hdr.vxh_blitfrom          = &libvideo_gfx_noblend__blitfrom_n;
			self->_vx_xops.vgxo_bitstretchfill = &libvideo_gfx_noblend__bitstretchfill_n;
		} else {
			self->vx_hdr.vxh_blitfrom = &libvideo_gfx_noblend__blitfrom_l;
		}
	}

	/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
	if (self->vx_buffer->vb_format.vf_codec->vc_codec == VIDEO_CODEC_RGBA8888) {
		if (self->_vx_xops.vgxo_getcolor == &libvideo_gfx_generic__getcolor_noblend)
			self->_vx_xops.vgxo_getcolor = self->_vx_xops.vgxo_getpixel;
		if (self->_vx_xops.vgxo_putcolor == &libvideo_gfx_generic__putcolor_noblend)
			self->_vx_xops.vgxo_putcolor = self->_vx_xops.vgxo_setpixel;
	}
}

/* Same as `libvideo_gfx_populate_generic()', but load non-blending defaults */
LOCAL ATTR_INOUT(1) void CC
libvideo_gfx_populate_noblend(struct video_gfx *__restrict self) {
	if (self->_vx_xops.vgxo_getcolor != self->_vx_xops.vgxo_getpixel)
		self->_vx_xops.vgxo_getcolor = &libvideo_gfx_generic__getcolor_noblend;
	if (self->_vx_xops.vgxo_putcolor != self->_vx_xops.vgxo_setpixel)
		self->_vx_xops.vgxo_putcolor = &libvideo_gfx_generic__putcolor_noblend;
	if (!(self->vx_flags & VIDEO_GFX_FAALINES)) {
		self->_vx_xops.vgxo_absline_llhh = &libvideo_gfx_noblend__absline_llhh;
		self->_vx_xops.vgxo_absline_lhhl = &libvideo_gfx_noblend__absline_lhhl;
	}
	self->_vx_xops.vgxo_absline_h = &libvideo_gfx_noblend__absline_h;
	self->_vx_xops.vgxo_absline_v = &libvideo_gfx_noblend__absline_v;
	self->_vx_xops.vgxo_absfill   = &libvideo_gfx_noblend__absfill;
	self->_vx_xops.vgxo_bitfill   = &libvideo_gfx_noblend__bitfill;
	if (!(self->vx_flags & VIDEO_GFX_FLINEARBLIT)) {
		self->vx_hdr.vxh_blitfrom          = &libvideo_gfx_noblend__blitfrom_n;
		self->_vx_xops.vgxo_bitstretchfill = &libvideo_gfx_noblend__bitstretchfill_n;
	} else {
		self->vx_hdr.vxh_blitfrom = &libvideo_gfx_noblend__blitfrom_l;
	}
}


/* Select appropriate operators for a video blit operations */
LOCAL ATTR_INOUT(1) void CC
video_blit_setops(struct video_blit *__restrict ctx) {
	/* Select operators based on wrapping flags of src/dst */
	if (ctx->vb_dst->vx_flags & (VIDEO_GFX_FWRXWRAP | VIDEO_GFX_FWRYWRAP)) {
		ctx->vb_ops = &libvideo_blit_generic_ops_wrap;
	} else if (ctx->vb_src->vx_flags & (VIDEO_GFX_FRDXWRAP | VIDEO_GFX_FRDYWRAP)) {
		ctx->vb_ops = &libvideo_blit_generic_ops_rdwrap;
	} else {
		ctx->vb_ops = &libvideo_blit_generic_ops;
	}
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_H */
