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
#ifndef _LIBVIDEO_GFX_BLENDCOLORS_H
#define _LIBVIDEO_GFX_BLENDCOLORS_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/__minmax.h>

#include <libvideo/codec/pixel.h>

#include "blend.h"

#ifdef __CC__
__DECL_BEGIN

#if 0 /*< Define as 1 to have the blender round upwards. */
#define _gfx_div256(x) (video_channel_t)(((x) + VIDEO_CHANNEL_MAX - 1) / VIDEO_CHANNEL_MAX)
#else
#define _gfx_div256(x) (video_channel_t)((x) / VIDEO_CHANNEL_MAX)
#endif

#define _gfx_blend_zero(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                                                   /* lhs* */ 0
#define _gfx_blend_one(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                                                       lhs
#define _gfx_blend_src_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                _gfx_div256((video_twochannels_t)lhs * csrc)
#define _gfx_blend_one_minus_src_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)      _gfx_div256((video_twochannels_t)lhs * (0xff - csrc))
#define _gfx_blend_dst_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                _gfx_div256((video_twochannels_t)lhs * cdst)
#define _gfx_blend_one_minus_dst_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)      _gfx_div256((video_twochannels_t)lhs * (0xff - cdst))
#define _gfx_blend_src_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                _gfx_div256((video_twochannels_t)lhs * asrc)
#define _gfx_blend_one_minus_src_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)      _gfx_div256((video_twochannels_t)lhs * (0xff - asrc))
#define _gfx_blend_dst_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                _gfx_div256((video_twochannels_t)lhs * adst)
#define _gfx_blend_one_minus_dst_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)      _gfx_div256((video_twochannels_t)lhs * (0xff - adst))
#define _gfx_blend_src_alpha_saturate(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)       _gfx_div256((video_twochannels_t)lhs * __hybrid_min2(asrc, 0xff - adst))
#define _gfx_blend_constant_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)           _gfx_div256((video_twochannels_t)lhs * cc)
#define _gfx_blend_one_minus_constant_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac) _gfx_div256((video_twochannels_t)lhs * (0xff - cc))
#define _gfx_blend_constant_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)           _gfx_div256((video_twochannels_t)lhs * ac)
#define _gfx_blend_one_minus_constant_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac) _gfx_div256((video_twochannels_t)lhs * (0xff - ac))

#define _GFX_BLENDDATA_SWITCH(kind, callback)                                                                       \
	do {                                                                                                   \
		switch (kind) {                                                                                    \
		case GFX_BLENDMODE_ONE:                      callback(_gfx_blend_one); break;                      \
		case GFX_BLENDMODE_SRC_COLOR:                callback(_gfx_blend_src_color); break;                \
		case GFX_BLENDMODE_ONE_MINUS_SRC_COLOR:      callback(_gfx_blend_one_minus_src_color); break;      \
		case GFX_BLENDMODE_DST_COLOR:                callback(_gfx_blend_dst_color); break;                \
		case GFX_BLENDMODE_ONE_MINUS_DST_COLOR:      callback(_gfx_blend_one_minus_dst_color); break;      \
		case GFX_BLENDMODE_SRC_ALPHA:                callback(_gfx_blend_src_alpha); break;                \
		case GFX_BLENDMODE_ONE_MINUS_SRC_ALPHA:      callback(_gfx_blend_one_minus_src_alpha); break;      \
		case GFX_BLENDMODE_DST_ALPHA:                callback(_gfx_blend_dst_alpha); break;                \
		case GFX_BLENDMODE_ONE_MINUS_DST_ALPHA:      callback(_gfx_blend_one_minus_dst_alpha); break;      \
		case GFX_BLENDMODE_SRC_ALPHA_SATURATE:       callback(_gfx_blend_src_alpha_saturate); break;       \
		case GFX_BLENDMODE_CONSTANT_COLOR:           callback(_gfx_blend_constant_color); break;           \
		case GFX_BLENDMODE_ONE_MINUS_CONSTANT_COLOR: callback(_gfx_blend_one_minus_constant_color); break; \
		case GFX_BLENDMODE_CONSTANT_ALPHA:           callback(_gfx_blend_constant_alpha); break;           \
		case GFX_BLENDMODE_ONE_MINUS_CONSTANT_ALPHA: callback(_gfx_blend_one_minus_constant_alpha); break; \
		default:                                     callback(_gfx_blend_zero); break;                     \
		}                                                                                                  \
	}	__WHILE0

#define _gfx_blendfunc_add(a, b)              a + b
#define _gfx_blendfunc_subtract(a, b)         a - b
#define _gfx_blendfunc_reverse_subtract(a, b) b - a
#define _GFX_BLENDFUNC_SWITCH(kind, callback)                                                  \
	do {                                                                                       \
		switch (kind) {                                                                        \
		case GFX_BLENDFUNC_SUBTRACT:         callback(_gfx_blendfunc_subtract); break;         \
		case GFX_BLENDFUNC_REVERSE_SUBTRACT: callback(_gfx_blendfunc_reverse_subtract); break; \
		case GFX_BLENDFUNC_MIN:              callback(__hybrid_min2); break;                   \
		case GFX_BLENDFUNC_MAX:              callback(__hybrid_max2); break;                   \
		default:                             callback(_gfx_blendfunc_add); break;              \
		}                                                                                      \
	}	__WHILE0




/* Blend 2 colors `dst' and `src' together as per `mode'.
 *
 * This is the master function used for blending the
 * colors of  2 pixels  using a  `struct video_gfx'.
 *
 * This function has been carefully written such that it
 * should be fairly easy  for any compiler to  perfectly
 * optimize calls to it, so-long as "mode" is a compile-
 * time constant.
 *
 * As such, `struct video_gfx' contains dedicated impls
 * for these commonly used blending modes:
 * - GFX_BLENDINFO_ALPHA
 * - GFX_BLENDINFO_OVERRIDE
 *
 * All other moves will obviously work as well, but won't
 * be nearly as fast/efficient. */
__LOCAL __ATTR_CONST __ATTR_WUNUSED video_color_t LIBVIDEO_GFX_CC
gfx_blendcolors(video_color_t dst, video_color_t src, gfx_blendmode_t mode) {
	video_channel_t new_lhs_r, new_lhs_g, new_lhs_b, new_lhs_a;
	video_channel_t new_rhs_r, new_rhs_g, new_rhs_b, new_rhs_a;
	video_channel_t dst_r, dst_g, dst_b, dst_a;
	video_channel_t src_r, src_g, src_b, src_a;
	dst_r = VIDEO_COLOR_GET_RED(dst);
	dst_g = VIDEO_COLOR_GET_GREEN(dst);
	dst_b = VIDEO_COLOR_GET_BLUE(dst);
	dst_a = VIDEO_COLOR_GET_ALPHA(dst);
	src_r = VIDEO_COLOR_GET_RED(src);
	src_g = VIDEO_COLOR_GET_GREEN(src);
	src_b = VIDEO_COLOR_GET_BLUE(src);
	src_a = VIDEO_COLOR_GET_ALPHA(src);
#define _gfx_blend_rgb_src(fun)                                                                                                               \
	{                                                                                                                                         \
		new_lhs_r = (video_channel_t)(fun(src_r, dst_r, src_r, dst_r, src_a, dst_a, GFX_BLENDINFO_GET_CR(mode), GFX_BLENDINFO_GET_CA(mode))); \
		new_lhs_g = (video_channel_t)(fun(src_g, dst_g, src_g, dst_g, src_a, dst_a, GFX_BLENDINFO_GET_CG(mode), GFX_BLENDINFO_GET_CA(mode))); \
		new_lhs_b = (video_channel_t)(fun(src_b, dst_b, src_b, dst_b, src_a, dst_a, GFX_BLENDINFO_GET_CB(mode), GFX_BLENDINFO_GET_CA(mode))); \
	}
#define _gfx_blend_a_src(fun)                                                                                                                 \
	{                                                                                                                                         \
		new_lhs_a = (video_channel_t)(fun(src_a, dst_a, src_a, dst_a, src_a, dst_a, GFX_BLENDINFO_GET_CA(mode), GFX_BLENDINFO_GET_CA(mode))); \
	}
#define _gfx_blend_rgb_dst(fun)                                                                                                               \
	{                                                                                                                                         \
		new_rhs_r = (video_channel_t)(fun(dst_r, src_r, src_r, dst_r, src_a, dst_a, GFX_BLENDINFO_GET_CR(mode), GFX_BLENDINFO_GET_CA(mode))); \
		new_rhs_g = (video_channel_t)(fun(dst_g, src_g, src_g, dst_g, src_a, dst_a, GFX_BLENDINFO_GET_CG(mode), GFX_BLENDINFO_GET_CA(mode))); \
		new_rhs_b = (video_channel_t)(fun(dst_b, src_b, src_b, dst_b, src_a, dst_a, GFX_BLENDINFO_GET_CB(mode), GFX_BLENDINFO_GET_CA(mode))); \
	}
#define _gfx_blend_a_dst(fun)                                                                                                                 \
	{                                                                                                                                         \
		new_rhs_a = (video_channel_t)(fun(dst_a, src_a, src_a, dst_a, src_a, dst_a, GFX_BLENDINFO_GET_CA(mode), GFX_BLENDINFO_GET_CA(mode))); \
	}
	_GFX_BLENDDATA_SWITCH(GFX_BLENDINFO_GET_SRCRGB(mode), _gfx_blend_rgb_src);
	_GFX_BLENDDATA_SWITCH(GFX_BLENDINFO_GET_SRCA(mode), _gfx_blend_a_src);
	_GFX_BLENDDATA_SWITCH(GFX_BLENDINFO_GET_DSTRGB(mode), _gfx_blend_rgb_dst);
	_GFX_BLENDDATA_SWITCH(GFX_BLENDINFO_GET_DSTA(mode), _gfx_blend_a_dst);
#undef _gfx_blend_a_dst
#undef _gfx_blend_rgb_dst
#undef _gfx_blend_a_src
#undef _gfx_blend_rgb_src
#define _gfx_blend_rgb(fun)                                   \
	{                                                         \
		dst_r = (video_channel_t)(fun(new_lhs_r, new_rhs_r)); \
		dst_g = (video_channel_t)(fun(new_lhs_g, new_rhs_g)); \
		dst_b = (video_channel_t)(fun(new_lhs_b, new_rhs_b)); \
	}
#define _gfx_blend_a(fun)                                     \
	{                                                         \
		dst_a = (video_channel_t)(fun(new_lhs_a, new_rhs_a)); \
	}
	_GFX_BLENDFUNC_SWITCH(GFX_BLENDINFO_GET_FUNRGB(mode), _gfx_blend_rgb);
	_GFX_BLENDFUNC_SWITCH(GFX_BLENDINFO_GET_FUNA(mode), _gfx_blend_a);
#undef _gfx_blend_a
#undef _gfx_blend_rgb
	return VIDEO_COLOR_RGBA(dst_r, dst_g, dst_b, dst_a);
}

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_BLENDCOLORS_H */
