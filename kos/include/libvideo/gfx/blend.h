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
#ifndef _LIBVIDEO_GFX_BLEND_H
#define _LIBVIDEO_GFX_BLEND_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <libvideo/codec/pixel.h>

/* Surface blend definitions. */
#define GFX_BLENDDATA_ZERO                                   0x00 /*             0 */
#define GFX_BLENDDATA_ONE                                    0x01 /* {channel} * 1  (max intensity; channel=0xff) */
#define GFX_BLENDDATA_SRC_COLOR                              0x02 /* {channel} * source_color */
#define GFX_BLENDDATA_ONE_MINUS_SRC_COLOR                    0x03 /* {channel} * 1 - source_color */
#define GFX_BLENDDATA_DST_COLOR                              0x04 /* {channel} * destination_color */
#define GFX_BLENDDATA_ONE_MINUS_DST_COLOR                    0x05 /* {channel} * 1 - destination_color */
#define GFX_BLENDDATA_SRC_ALPHA                              0x06 /* {channel} * source_alpha */
#define GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA                    0x07 /* {channel} * 1 - source_alpha */
#define GFX_BLENDDATA_DST_ALPHA                              0x08 /* {channel} * destination_alpha */
#define GFX_BLENDDATA_ONE_MINUS_DST_ALPHA                    0x09 /* {channel} * 1 - destination_alpha */
#define GFX_BLENDDATA_CONSTANT_COLOR                         0x0a /* {channel} * CR/CG/CB */
#define GFX_BLENDDATA_ONE_MINUS_CONSTANT_COLOR               0x0b /* {channel} * 1 - CR/CG/CB */
#define GFX_BLENDDATA_CONSTANT_ALPHA                         0x0c /* {channel} * CA */
#define GFX_BLENDDATA_ONE_MINUS_CONSTANT_ALPHA               0x0d /* {channel} * 1 - CA */
#define GFX_BLENDDATA_SRC_ALPHA_SATURATE                     0x0e /* {channel} * min(source_alpha, 1 - destination_alpha) */
#define GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA_SATURATE           0x0f /* {channel} * 1 - min(source_alpha, 1 - destination_alpha) */
#define GFX_BLENDDATA_SRC_COLOR_MUL_CONSTANT_COLOR           0x10 /* {channel} * (source_color * constant_color) */
#define GFX_BLENDDATA_ONE_MINUS_SRC_COLOR_MUL_CONSTANT_COLOR 0x11 /* {channel} * 1 - (source_color * constant_color) */
#define GFX_BLENDDATA_DST_COLOR_MUL_CONSTANT_COLOR           0x12 /* {channel} * (destination_color * constant_color) */
#define GFX_BLENDDATA_ONE_MINUS_DST_COLOR_MUL_CONSTANT_COLOR 0x13 /* {channel} * 1 - (destination_color * constant_color) */
#define GFX_BLENDDATA_SRC_ALPHA_MUL_CONSTANT_COLOR           0x14 /* {channel} * (source_alpha * constant_color) */
#define GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_COLOR 0x15 /* {channel} * 1 - (source_alpha * constant_color) */
#define GFX_BLENDDATA_DST_ALPHA_MUL_CONSTANT_COLOR           0x16 /* {channel} * (destination_alpha * constant_color) */
#define GFX_BLENDDATA_ONE_MINUS_DST_ALPHA_MUL_CONSTANT_COLOR 0x17 /* {channel} * 1 - (destination_alpha * constant_color) */
#define GFX_BLENDDATA_SRC_COLOR_MUL_CONSTANT_ALPHA           0x18 /* {channel} * (source_color * constant_alpha) */
#define GFX_BLENDDATA_ONE_MINUS_SRC_COLOR_MUL_CONSTANT_ALPHA 0x19 /* {channel} * 1 - (source_color * constant_alpha) */
#define GFX_BLENDDATA_DST_COLOR_MUL_CONSTANT_ALPHA           0x1a /* {channel} * (destination_color * constant_alpha) */
#define GFX_BLENDDATA_ONE_MINUS_DST_COLOR_MUL_CONSTANT_ALPHA 0x1b /* {channel} * 1 - (destination_color * constant_alpha) */
#define GFX_BLENDDATA_SRC_ALPHA_MUL_CONSTANT_ALPHA           0x1c /* {channel} * (source_alpha * constant_alpha) */
#define GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_ALPHA 0x1d /* {channel} * 1 - (source_alpha * constant_alpha) */
#define GFX_BLENDDATA_DST_ALPHA_MUL_CONSTANT_ALPHA           0x1e /* {channel} * (destination_alpha * constant_alpha) */
#define GFX_BLENDDATA_ONE_MINUS_DST_ALPHA_MUL_CONSTANT_ALPHA 0x1f /* {channel} * 1 - (destination_alpha * constant_alpha) */
#define _GFX_BLENDDATA_ONE_MINUS(x) ((x) ^ 1)

#define GFX_BLENDFUNC_ADD                      0x00 /* a + b */
#define GFX_BLENDFUNC_SUBTRACT                 0x01 /* a - b */
#define GFX_BLENDFUNC_REVERSE_SUBTRACT         0x02 /* b - a */
#define GFX_BLENDFUNC_MIN                      0x03 /* a < b ? a : b */
#define GFX_BLENDFUNC_MAX                      0x04 /* a > b ? a : b */
#define GFX_BLENDFUNC_MUL                      0x05 /* a * b   (where "a" and "b" are [0,1]; iow: for [0,0xff], result is divided by 255) */
/*      GFX_BLENDFUNC_...                      0x06  * ... */
/*      GFX_BLENDFUNC_...                      0x07  * ... */

#define _GFX_BLENDMODE_CONSTANT_SHIFT 32 /* Shift for where we store the constant color */
#define _GFX_BLENDMODE_CR_SHIFT (_GFX_BLENDMODE_CONSTANT_SHIFT + VIDEO_COLOR_RED_SHIFT)
#define _GFX_BLENDMODE_CG_SHIFT (_GFX_BLENDMODE_CONSTANT_SHIFT + VIDEO_COLOR_GREEN_SHIFT)
#define _GFX_BLENDMODE_CB_SHIFT (_GFX_BLENDMODE_CONSTANT_SHIFT + VIDEO_COLOR_BLUE_SHIFT)
#define _GFX_BLENDMODE_CA_SHIFT (_GFX_BLENDMODE_CONSTANT_SHIFT + VIDEO_COLOR_ALPHA_SHIFT)

#define GFX_BLENDMODE_GET_SRCRGB(info) (__CCAST(__uint8_t)((info) & 0x1f))         /* Source color (One of `GFX_BLENDDATA_*') */
#define GFX_BLENDMODE_GET_SRCA(info)   (__CCAST(__uint8_t)(((info) >> 5) & 0x1f))  /* Source alpha (One of `GFX_BLENDDATA_*') */
#define GFX_BLENDMODE_GET_DSTRGB(info) (__CCAST(__uint8_t)(((info) >> 10) & 0x1f)) /* Destination color (One of `GFX_BLENDDATA_*') */
#define GFX_BLENDMODE_GET_DSTA(info)   (__CCAST(__uint8_t)(((info) >> 15) & 0x1f)) /* Destination alpha (One of `GFX_BLENDDATA_*') */
#define GFX_BLENDMODE_GET_FUNRGB(info) (__CCAST(__uint8_t)(((info) >> 20) & 0x7))  /* Color blend function (One of `GFX_BLENDFUNC_*') */
#define GFX_BLENDMODE_GET_FUNA(info)   (__CCAST(__uint8_t)(((info) >> 23) & 0x7))  /* Alpha blend function (One of `GFX_BLENDFUNC_*') */
#define GFX_BLENDMODE_GET_MODE(x)      (__CCAST(__UINT32_TYPE__)(x))               /* The actual blending mode config */
#define GFX_BLENDMODE_GET_COLOR(x)     (__CCAST(video_color_t)((x) >> _GFX_BLENDMODE_CONSTANT_SHIFT)) /* Constant color */

/* Helper macros for creating blend modes.
 * @param: src:  Source color/alpha (One of `GFX_BLENDDATA_*')
 * @param: dst:  Destination color/alpha (One of `GFX_BLENDDATA_*')
 * @param: func: Color/alpha blend function (One of `GFX_BLENDFUNC_*') */
#define GFX_BLENDMODE(rgb_src, rgb_fun, rgb_dst, a_src, a_fun, a_dst)                         \
	_GFX_BLENDMODE(GFX_BLENDDATA_##rgb_src, GFX_BLENDFUNC_##rgb_fun, GFX_BLENDDATA_##rgb_dst, \
	               GFX_BLENDDATA_##a_src, GFX_BLENDFUNC_##a_fun, GFX_BLENDDATA_##a_dst)
#define _GFX_BLENDMODE(rgb_src, rgb_fun, rgb_dst, a_src, a_fun, a_dst) \
	_GFX_BLENDMODE_EX(rgb_src, rgb_fun, rgb_dst, a_src, a_fun, a_dst, 0, 0, 0, 0)
#define GFX_BLENDMODE_EX(rgb_src, rgb_fun, rgb_dst, a_src, a_fun, a_dst, cr, cg, cb, ca)         \
	_GFX_BLENDMODE_EX(GFX_BLENDDATA_##rgb_src, GFX_BLENDFUNC_##rgb_fun, GFX_BLENDDATA_##rgb_dst, \
	                  GFX_BLENDDATA_##a_src, GFX_BLENDFUNC_##a_fun, GFX_BLENDDATA_##a_dst, cr, cg, cb, ca)
#define _GFX_BLENDMODE_EX(rgb_src, rgb_fun, rgb_dst,                      \
                          a_src, a_fun, a_dst, cr, cg, cb, ca)            \
	(__CCAST(gfx_blendmode_t)((rgb_src) & 0x1f) |                         \
	 (__CCAST(gfx_blendmode_t)((a_src) & 0x1f) << 5) |                    \
	 (__CCAST(gfx_blendmode_t)((rgb_dst) & 0x1f) << 10) |                 \
	 (__CCAST(gfx_blendmode_t)((a_dst) & 0x1f) << 15) |                   \
	 (__CCAST(gfx_blendmode_t)((rgb_fun) & 0x7) << 20) |                  \
	 (__CCAST(gfx_blendmode_t)((a_fun) & 0x7) << 23) |                    \
	 (__CCAST(gfx_blendmode_t)((cr) & 0xff) << _GFX_BLENDMODE_CR_SHIFT) | \
	 (__CCAST(gfx_blendmode_t)((cg) & 0xff) << _GFX_BLENDMODE_CG_SHIFT) | \
	 (__CCAST(gfx_blendmode_t)((cb) & 0xff) << _GFX_BLENDMODE_CB_SHIFT) | \
	 (__CCAST(gfx_blendmode_t)((ca) & 0xff) << _GFX_BLENDMODE_CA_SHIFT))

#ifdef __CC__
__DECL_BEGIN
typedef __UINT64_TYPE__ gfx_blendmode_t;
__DECL_END
#endif /* __CC__ */

/* NOTE: If you're coming from SDL, the below blending modes correspond as follows:
 * >> SDL_BLENDMODE_NONE                = GFX_BLENDMODE_OVERRIDE
 * >> SDL_BLENDMODE_BLEND               = GFX_BLENDMODE_ALPHA
 * >> SDL_BLENDMODE_BLEND_PREMULTIPLIED = GFX_BLENDMODE_ALPHA_PREMULTIPLIED
 * >> SDL_BLENDMODE_ADD                 = GFX_BLENDMODE_ADD
 * >> SDL_BLENDMODE_ADD_PREMULTIPLIED   = GFX_BLENDMODE_ADD_PREMULTIPLIED
 * >> SDL_BLENDMODE_MOD                 = GFX_BLENDMODE_MOD
 * >> SDL_BLENDMODE_MUL                 = GFX_BLENDMODE_MUL */

/* Override destination (no blending done) */
#define GFX_BLENDMODE_OVERRIDE            \
	GFX_BLENDMODE(/*RGB=*/ONE, ADD, ZERO, \
	              /*A  =*/ONE, ADD, ZERO)

/* Conventional alpha blending:
 * >> RGB = (srcRGB * srcA) + (dstRGB * (1 - srcA));
 * >> A   = (srcA   * 1)    + (dstA   * (1 - srcA)); */
#define GFX_BLENDMODE_ALPHA                                    \
	GFX_BLENDMODE(/*RGB=*/SRC_ALPHA, ADD, ONE_MINUS_SRC_ALPHA, \
	              /*A  =*/ONE, ADD, ONE_MINUS_SRC_ALPHA)

/* Same as `GFX_BLENDMODE_ALPHA', but with an additional constant factor "ca"
 * that gets multiplied in in every calculation (useful for defining "global"
 * alpha values)
 *
 * NOTE: "ca" is the SOURCE-alpha factor (iow: 0xff means "GFX_BLENDMODE_ALPHA") */
#define GFX_BLENDMODE_ALPHA_FACTOR(ca)                                                                  \
	GFX_BLENDMODE_EX(/*RGB=*/SRC_ALPHA_MUL_CONSTANT_ALPHA, ADD, ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_ALPHA, \
	                 /*A  =*/CONSTANT_ALPHA, ADD, ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_ALPHA,               \
	                 0, 0, 0, ca)

/* Same as `GFX_BLENDMODE_ALPHA', but use "ca" instead of source alpha values
 * In  this sense, this is the same as "GFX_BLENDMODE_ALPHA_FACTOR()", but is
 * faster when the source colors always use `VIDEO_CHANNEL_MAX' for alpha.
 *
 * NOTE: "ca" is the SOURCE-alpha factor (iow: 0xff means "GFX_BLENDMODE_OVERRIDE") */
#define GFX_BLENDMODE_ALPHA_OVERRIDE(ca)                                    \
	GFX_BLENDMODE_EX(/*RGB=*/CONSTANT_ALPHA, ADD, ONE_MINUS_CONSTANT_ALPHA, \
	                 /*A  =*/CONSTANT_ALPHA, ADD, ONE_MINUS_CONSTANT_ALPHA, \
	                 0, 0, 0, ca)

/* Pre-multiplied alpha blending (same as "GFX_BLENDMODE_ALPHA",
 * but source color  was already multiplied  with source  alpha) */
#define GFX_BLENDMODE_ALPHA_PREMULTIPLIED                \
	GFX_BLENDMODE(/*RGB=*/ONE, ADD, ONE_MINUS_SRC_ALPHA, \
	              /*A  =*/ONE, ADD, ONE_MINUS_SRC_ALPHA)

/* Additive blending */
#define GFX_BLENDMODE_ADD                      \
	GFX_BLENDMODE(/*RGB=*/SRC_ALPHA, ADD, ONE, \
	              /*A  =*/ZERO, ADD, ONE)

/* Pre-multiplied additive blending (same as "GFX_BLENDMODE_ADD",
 * but source  color was  already multiplied  with source  alpha) */
#define GFX_BLENDMODE_ADD_PREMULTIPLIED  \
	GFX_BLENDMODE(/*RGB=*/ONE, ADD, ONE, \
	              /*A  =*/ZERO, ADD, ONE)

/* Color modulate */
#define GFX_BLENDMODE_MOD                \
	GFX_BLENDMODE(/*RGB=*/ONE, MUL, ONE, \
	              /*A  =*/ZERO, ADD, ONE)

/* Color multiply */
#define GFX_BLENDMODE_MUL                                      \
	GFX_BLENDMODE(/*RGB=*/SRC_COLOR, ADD, ONE_MINUS_SRC_ALPHA, \
	              /*A  =*/ZERO, ADD, ONE)


/* TODO: Define and add fast paths for this mode */
#define GFX_BLENDMODE_ALPHAMASK                 \
	GFX_BLENDMODE(/*RGB=*/DST_ALPHA, ADD, ZERO, \
	              /*A  =*/ONE, MUL, ONE)

#endif /* !_LIBVIDEO_GFX_BLEND_H */
