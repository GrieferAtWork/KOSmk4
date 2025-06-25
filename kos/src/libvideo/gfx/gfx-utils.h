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
#ifndef GUARD_LIBVIDEO_GFX_GFX_UTILS_H
#define GUARD_LIBVIDEO_GFX_GFX_UTILS_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/typecore.h>

#include <kos/types.h>
#include <sys/param.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/gfx.h>

#include "gfx.h"


DECL_BEGIN

/************************************************************************/
/* CLAMPING / WRAPPING HELPERS                                          */
/************************************************************************/

/* Wrap  a given "offset" such that values <0
 * or >= dim end up back in the range [0,dim)
 * @assume(dim > 0); */
LOCAL ATTR_CONST WUNUSED video_coord_t CC
wrap(video_offset_t offset, video_dim_t dim) {
#if 1
	offset %= dim;
	if (offset < 0)
		offset += dim - 1;
	return (video_coord_t)offset;
#else
	if unlikely(offset < 0) {
		offset = -offset;
		offset = (video_offset_t)((video_coord_t)offset % dim);
		if likely(offset)
			offset = dim - offset;
	} else if unlikely((video_coord_t)offset > dim) {
		offset = (video_offset_t)((video_coord_t)offset % dim);
	}
	return (video_coord_t)offset;
#endif
}

/* Similar to `wrap', but every even wrap causes returned coords to be mirrored */
LOCAL ATTR_CONST WUNUSED video_coord_t CC
wrap_or_mirror(video_offset_t offset, video_dim_t dim, bool should_mirror) {
	unsigned int mirror;
	mirror = (offset / dim) & 1;
	offset %= dim;
	if (offset < 0)
		offset += dim - 1;
	if (mirror && should_mirror)
		offset = (dim - 1) - offset;
	return (video_coord_t)offset;
}

LOCAL ATTR_CONST WUNUSED video_coord_t CC
uwrap_or_mirror(video_coord_t coord, video_dim_t dim, bool should_mirror) {
	unsigned int mirror;
	mirror = (coord / dim) & 1;
	coord %= dim;
	if (mirror && should_mirror)
		coord = (dim - 1) - coord;
	return (video_coord_t)coord;
}

LOCAL ATTR_CONST WUNUSED video_coord_t CC
mirror(video_offset_t offset, video_dim_t dim) {
	return wrap_or_mirror(offset, dim, true);
}

LOCAL ATTR_CONST WUNUSED video_coord_t CC
umirror(video_coord_t offset, video_dim_t dim) {
	return uwrap_or_mirror(offset, dim, true);
}

LOCAL WUNUSED ATTR_INOUT(4) video_coord_t CC
wrap_or_mirror_imatrix(video_offset_t offset, video_dim_t dim,
                       bool should_mirror, video_imatrix2d_word_t *p_word) {
	unsigned int mirror;
	mirror = (offset / dim) & 1;
	offset %= dim;
	if (offset < 0)
		offset += dim - 1;
	if (mirror && should_mirror)
		*p_word = -1;
	return (video_coord_t)offset;
}





/************************************************************************/
/* BLENDING HELPERS                                                     */
/************************************************************************/

/* Check if `*p_color' must be blended (false), or blending is optional (true),
 * such that behavior would be  the same when `GFX_BLENDMODE_OVERRIDE' were  to
 * be  used. If `*p_color'  has to be modified  before OVERRIDE-blending can be
 * done, then this is done prior to `true' being returned
 *
 * iow: Returns true iff:
 * >> ∀ c ∈ video_color_t: gfx_blendcolors(c, IN(*p_color), self->vx_blend) == OUT(*p_color) */
LOCAL ATTR_PURE WUNUSED ATTR_IN(1) ATTR_INOUT(2) bool CC
libvideo_gfx_allow_noblend(struct video_gfx const *__restrict self,
                           video_color_t *__restrict p_color) {
	gfx_blendmode_t mode = self->vx_blend;
	/* TODO: Do this dynamically for all blending modes */
	if (mode == GFX_BLENDMODE_ALPHA)
		return VIDEO_COLOR_ISOPAQUE(*p_color);
	return false;
}

/* Check if  trying to  blend  `color' is  a  no-op.
 * (e.g. for ALPHA-blending, "color" is transparent)
 *
 * iow: Returns true iff:
 * >> ∀ c ∈ video_color_t: gfx_blendcolors(c, color, self->vx_blend) == c */
LOCAL ATTR_PURE WUNUSED ATTR_IN(1) bool CC
libvideo_gfx_allow_ignore(struct video_gfx const *__restrict self,
                          video_color_t color) {
	gfx_blendmode_t mode = self->vx_blend;

	/* TODO: Do this dynamically for all blending modes */
	if (mode == GFX_BLENDMODE_ALPHA)
		return VIDEO_COLOR_ISTRANSPARENT(color);
	return false;
}



/************************************************************************/
/* LINEAR BLITTING HELPERS                                              */
/************************************************************************/

typedef video_channel_t channel_t;
typedef video_twochannels_t twochannels_t;
#define CHANNEL_MIN VIDEO_CHANNEL_MIN
#define CHANNEL_MAX VIDEO_CHANNEL_MAX

#define BITSOF(x) (sizeof(x) * NBBY)
static_assert(BITSOF(stretch_fp_t) >= BITSOF(video_coord_t) + STRETCH_FP_NFRAC,
              "stretch_fp_t is too small to hold arbitrary video coords + a fractional part");
static_assert(BITSOF(twochannels_t) >= (BITSOF(channel_t) * 2));


/************************************************************************/
/* DISCLAIMER: The linear stretch algorithm is derived from SDL!        */
/* s.a. SDL:/src/video/SDL_stretch.c:scale_mat                          */
/************************************************************************/

/* # of  leading bits  of "STRETCH_FP_NFRAC"  actually used  during
 * linear interpolation. Allowed to be less than "STRETCH_FP_NFRAC"
 * since no as much precision is still needed at that point.
 *
 * Specifically, we need at most "BITSOF(channel_t)" bots of precision,
 * however since for the purpose of blending we also need to be able to
 * represent a fixed-point "1.0", we need  1 extra bit for the  decimal
 * part.  And since we want to be  as efficient as possible, that means
 * we just restrict ourselves to 7 bits.
 *
 * In practice, you won't ever be able to see the difference, since this
 * missing bit of precision only comes  into play in how exactly  pixels
 * are  blended into  each other  during stretching,  having a minuscule
 * effect during color interpolation.
 */
#define LINEAR_FP_BLEND_NFRAC 7
typedef uint_fast8_t linear_fp_blend_t;     /* uint_fast{LINEAR_FP_BLEND_NFRAC+1}_t */
typedef uint_fast16_t linear_fp_twoblend_t; /* uint_fast{(LINEAR_FP_BLEND_NFRAC+1)*2}_t */
#define LINEAR_FP_BLEND(whole)    ((linear_fp_blend_t)(whole) << LINEAR_FP_BLEND_NFRAC)
#define LINEAR_FP_BLEND_WHOLE(fp) ((linear_fp_twoblend_t)(fp) >> LINEAR_FP_BLEND_NFRAC)

/* Return the blend-fraction of a gfx-stretch fixed-point (stretch_fp_t) "fp" value */
#define STRETCH_FP_BLEND_FRAC(fp) \
	((linear_fp_blend_t)((uint32_t)((fp) >> (STRETCH_FP_NFRAC - LINEAR_FP_BLEND_NFRAC)) & ((1 << LINEAR_FP_BLEND_NFRAC) - 1)))
static_assert(LINEAR_FP_BLEND_NFRAC <= STRETCH_FP_NFRAC);


LOCAL ATTR_OUT(3) ATTR_OUT(4) ATTR_OUT(5) ATTR_OUT(6) void CC
calc_linear_stretch_dim(video_dim_t src_dim,     /* in: "src" dimension */
                        video_dim_t dst_dim,     /* in: "dst" dimension */
                        sstretch_fp_t *fp_start, /* out: FP start value for "src" (still includes `*pad_min') */
                        stretch_fp_t *fp_step,   /* out: FP-delta in "src" to add for each pixel */
                        video_dim_t *pad_min,    /* out: # of leading pixels of padding in "dst" */
                        video_dim_t *pad_max) {  /* out: # of trailing pixels of padding in "dst" */
	stretch_fp_t fp_ratio; /* # of "src" pixels for each "dst" pixel */
	sstretch_fp_t fp_iter; /* Must be signed because *pad_min can result in negative values */
	gfx_assert(src_dim >= 1);
	gfx_assert(dst_dim >= 1);

	/* Special case for when the source dimension is so small that no blending can happen.
	 * Without this, we'd get a pixel out-of-bounds assertion fail in the "middle" part of
	 * the linear blender, which would try to access out-of-bounds pixels. */
	if unlikely(src_dim <= 1) {
		*fp_start = 0; /* Could also be left uninitialized */
		*fp_step  = 0; /* Could also be left uninitialized */
		*pad_min  = dst_dim;
		*pad_max  = 0;
		return;
	}

	fp_ratio = STRETCH_FP(src_dim) / dst_dim;

	fp_iter = fp_ratio * STRETCH_FP_FRAC(STRETCH_FP(1) / 2);
	fp_iter = STRETCH_FP_WHOLE(fp_iter + (STRETCH_FP(1) / 2));
	fp_iter -= STRETCH_FP(1) / 2; /* Start in the middle of pixels (this is also the reason why "*pad_min" is needed) */

	*fp_start = fp_iter;
	*fp_step  = fp_ratio;
	*pad_min  = 0;
	*pad_max  = 0;
	do {
		if (fp_iter < 0) {
			*pad_min += 1;
		} else {
			video_coord_t index = STRETCH_FP_WHOLE(fp_iter);
			if (index > src_dim - 2) {
				*pad_max += 1;
			}
		}
		fp_iter += fp_ratio;
	} while (--dst_dim);
}

/* Interpolate "c0" with "c1".
 * NOTE: Make sure that "frac0 + frac1 == LINEAR_FP_BLEND(1)" */
LOCAL ATTR_CONST channel_t CC
interpolate_channel_1d(channel_t c0, channel_t c1,
                       linear_fp_blend_t frac0,
                       linear_fp_blend_t frac1) {
	__builtin_assume(frac0 + frac1 == LINEAR_FP_BLEND(1));
	return (channel_t)LINEAR_FP_BLEND_WHOLE(((linear_fp_twoblend_t)c0 * frac1) +
	                                        ((linear_fp_twoblend_t)c1 * frac0));
}

LOCAL ATTR_CONST channel_t
interpolate_channel_2d(channel_t c_y0_x0, channel_t c_y0_x1,
                       channel_t c_y1_x0, channel_t c_y1_x1,
                       linear_fp_blend_t frac_x0, linear_fp_blend_t frac_x1,
                       linear_fp_blend_t frac_y0, linear_fp_blend_t frac_y1) {
	/* Blend vertically */
	channel_t y0 = interpolate_channel_1d(c_y0_x0, c_y1_x0, frac_y0, frac_y1);
	channel_t y1 = interpolate_channel_1d(c_y0_x1, c_y1_x1, frac_y0, frac_y1);
	/* Blend horizontally */
	return interpolate_channel_1d(y0, y1, frac_x0, frac_x1);
}

LOCAL ATTR_CONST video_color_t CC
interpolate_1d(video_color_t c0, video_color_t c1,
               linear_fp_blend_t frac0, linear_fp_blend_t frac1) {
	channel_t r = interpolate_channel_1d(VIDEO_COLOR_GET_RED(c0), VIDEO_COLOR_GET_RED(c1), frac0, frac1);
	channel_t g = interpolate_channel_1d(VIDEO_COLOR_GET_GREEN(c0), VIDEO_COLOR_GET_GREEN(c1), frac0, frac1);
	channel_t b = interpolate_channel_1d(VIDEO_COLOR_GET_BLUE(c0), VIDEO_COLOR_GET_BLUE(c1), frac0, frac1);
	channel_t a = interpolate_channel_1d(VIDEO_COLOR_GET_ALPHA(c0), VIDEO_COLOR_GET_ALPHA(c1), frac0, frac1);
	return VIDEO_COLOR_RGBA(r, g, b, a);
}

LOCAL ATTR_CONST video_color_t
interpolate_2d(video_color_t c_y0_x0, video_color_t c_y0_x1,
               video_color_t c_y1_x0, video_color_t c_y1_x1,
               linear_fp_blend_t frac_x0, linear_fp_blend_t frac_x1,
               linear_fp_blend_t frac_y0, linear_fp_blend_t frac_y1) {
	/* Blend vertically */
	video_color_t y0 = interpolate_1d(c_y0_x0, c_y1_x0, frac_y0, frac_y1);
	video_color_t y1 = interpolate_1d(c_y0_x1, c_y1_x1, frac_y0, frac_y1);
	/* Blend horizontally */
	return interpolate_1d(y0, y1, frac_x0, frac_x1);
}

/* Macro-implementation of a general-purpose linear stretch algorithm.
 *
 * @param: video_coord_t dst_x:      Destination X coord
 * @param: video_coord_t dst_y:      Destination Y coord
 * @param: video_dim_t   dst_size_x: Destination size in X
 * @param: video_dim_t   dst_size_y: Destination size in Y
 * @param: video_coord_t src_x:      Source X coord
 * @param: video_coord_t src_y:      Source Y coord
 * @param: video_dim_t   src_size_x: Source size in X
 * @param: video_dim_t   src_size_y: Source size in Y
 *
 * Blending implementation callbacks (macros). All of these are expected
 * to fill in a specific portion of the destination GFX using data  from
 * the specified source coords. When appropriate, blending fractions to-
 * be applied to source pixels are also supplied.
 * In all cases, the supplied "src_x/src_y" points to the top-left of a
 * 1x1,  1x2,  2x1 or  2x2  pixel area  from  which data  can  be read.
 *
 * @param: [1x1] "top-left":     void blend_xmin_ymin(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y)
 * @param: [2x1] "top":          void blend_ymin(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_y, video_coord_t src_x0, video_coord_t src_y, video_coord_t src_x1, linear_fp_blend_t frac_x0, linear_fp_blend_t frac_x1)
 * @param: [1x1] "top-right":    void blend_xmax_ymin(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y)
 * @param: [1x2] "left":         void blend_xmin(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_coord_t src_x, video_coord_t src_y0, video_coord_t src_y1, linear_fp_blend_t frac_y0, linear_fp_blend_t frac_y1)
 * @param: [2x2] "center":       void blend(video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x0, video_coord_t src_y0, video_coord_t src_x1, video_coord_t src_y1, linear_fp_blend_t frac_x0, linear_fp_blend_t frac_x1, linear_fp_blend_t frac_y0, linear_fp_blend_t frac_y1)
 * @param: [1x2] "right":        void blend_xmax(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_coord_t src_x, video_coord_t src_y0, video_coord_t src_y1, linear_fp_blend_t frac_y0, linear_fp_blend_t frac_y1)
 * @param: [1x1] "bottom-left":  void blend_xmin_ymax(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y)
 * @param: [2x1] "bottom":       void blend_ymax(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_y, video_coord_t src_x0, video_coord_t src_y, video_coord_t src_x1, linear_fp_blend_t frac_x0, linear_fp_blend_t frac_x1)
 * @param: [1x1] "bottom-right": void blend_xmax_ymax(video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y)
 */
#define GFX_LINEAR_STRETCH(dst_x, dst_y, dst_size_x, dst_size_y,                                                                   \
                           src_x, src_y, src_size_x, src_size_y,                                                                   \
                           blend_xmin_ymin /*(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)*/,                               \
                           blend_ymin /**/ /*(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1)*/,                \
                           blend_xmax_ymin /*(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)*/,                               \
                           blend_xmin /**/ /*(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1)*/,                \
                           blend /*     */ /*(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1)*/, \
                           blend_xmax /**/ /*(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1)*/,                \
                           blend_xmin_ymax /*(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)*/,                               \
                           blend_ymax /**/ /*(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1)*/,                \
                           blend_xmax_ymax /*(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)*/)                               \
	do {                                                                                                                           \
		video_coord_t _rel_dst_y; /* Relative destination Y coord [0,dst_size_y) */                                                \
		video_dim_t _pad_xmin, _pad_xmax;                                                                                          \
		video_dim_t _pad_ymin, _pad_ymax;                                                                                          \
		sstretch_fp_t _fp_src_x;                                                                                                   \
		sstretch_fp_t _fp_src_y;                                                                                                   \
		stretch_fp_t _fp_step_x;                                                                                                   \
		stretch_fp_t _fp_step_y;                                                                                                   \
		video_dim_t _nopad_dst_x; /* # of horizontal pixels that can be written w/o padding */                                     \
		calc_linear_stretch_dim(src_size_x, dst_size_x, &_fp_src_x, &_fp_step_x, &_pad_xmin, &_pad_xmax);                          \
		calc_linear_stretch_dim(src_size_y, dst_size_y, &_fp_src_y, &_fp_step_y, &_pad_ymin, &_pad_ymax);                          \
		_nopad_dst_x = dst_size_x - _pad_xmin - _pad_xmax;                                                                         \
		_fp_src_x += _pad_xmin * _fp_step_x; /* Skip over leading padding */                                                       \
		                                                                                                                           \
		/* Render padding near the top */                                                                                          \
		if (_pad_ymin) {                                                                                                           \
			video_coord_t _used_dst_x = dst_x;                                                                                     \
			video_dim_t _middle;                                                                                                   \
			sstretch_fp_t _row_fp_src_x;                                                                                           \
			if (_pad_xmin) {                                                                                                       \
				blend_xmin_ymin(_used_dst_x, dst_y, _pad_xmin, _pad_ymin, src_x, src_y);                                           \
				_used_dst_x += _pad_xmin;                                                                                          \
			}                                                                                                                      \
			for (_middle = _nopad_dst_x, _row_fp_src_x = _fp_src_x;                                                                \
			     _middle; --_middle, ++_used_dst_x, _row_fp_src_x += _fp_step_x) {                                                 \
				video_coord_t _used_src_x  = src_x + STRETCH_FP_WHOLE(_row_fp_src_x);                                              \
				linear_fp_blend_t _frac_x0 = STRETCH_FP_BLEND_FRAC(_row_fp_src_x);                                                 \
				linear_fp_blend_t _frac_x1 = LINEAR_FP_BLEND(1) - _frac_x0;                                                        \
				blend_ymin(_used_dst_x, dst_y, _pad_ymin, _used_src_x, src_y, (_used_src_x + 1), _frac_x0, _frac_x1);              \
			}                                                                                                                      \
			if (_pad_xmax) {                                                                                                       \
				video_coord_t _used_src_x = src_x + src_size_x - 1;                                                                \
				blend_xmax_ymin(_used_dst_x, dst_y, _pad_xmax, _pad_ymin, _used_src_x, src_y);                                     \
				/*_used_dst_x += left_pad_w;*/                                                                                     \
			}                                                                                                                      \
			_fp_src_y += _fp_step_y * _pad_ymin;                                                                                   \
		}                                                                                                                          \
		                                                                                                                           \
		/* Render the main image */                                                                                                \
		for (_rel_dst_y = _pad_ymin; _rel_dst_y < dst_size_y - _pad_ymax; ++_rel_dst_y, _fp_src_y += _fp_step_y) {                 \
			video_coord_t _used_dst_y = dst_y + _rel_dst_y; /* Absolute destination Y coord [dst_y,dst_y+dst_size_y) */            \
			video_coord_t _used_dst_x;                                                                                             \
			video_coord_t _rel_src_y;                                                                                              \
			linear_fp_blend_t _frac_y0, _frac_y1;                                                                                  \
			video_dim_t _middle;                                                                                                   \
			video_coord_t _used_src_y0, _used_src_y1;                                                                              \
			sstretch_fp_t _row_fp_src_x;                                                                                           \
			_rel_src_y = STRETCH_FP_WHOLE(_fp_src_y);                                                                              \
			_frac_y0   = STRETCH_FP_BLEND_FRAC(_fp_src_y);                                                                         \
			_frac_y1   = LINEAR_FP_BLEND(1) - _frac_y0;                                                                            \
			                                                                                                                       \
			_used_src_y0 = src_y + _rel_src_y; /* Y coord of first src row */                                                      \
			_used_src_y1 = _used_src_y0 + 1;   /* Y coord of second src row */                                                     \
			_used_dst_x  = dst_x;                                                                                                  \
			if (_pad_xmin) {                                                                                                       \
				blend_xmin(_used_dst_x, _used_dst_y, _pad_xmin, src_x, _used_src_y0, _used_src_y1, _frac_y0, _frac_y1);            \
				_used_dst_x += _pad_xmin;                                                                                          \
			}                                                                                                                      \
			for (_middle = _nopad_dst_x, _row_fp_src_x = _fp_src_x;                                                                \
			     _middle; --_middle, ++_used_dst_x, _row_fp_src_x += _fp_step_x) {                                                 \
				video_coord_t _used_src_x  = src_x + STRETCH_FP_WHOLE(_row_fp_src_x);                                              \
				linear_fp_blend_t _frac_x0 = STRETCH_FP_BLEND_FRAC(_row_fp_src_x);                                                 \
				linear_fp_blend_t _frac_x1 = LINEAR_FP_BLEND(1) - _frac_x0;                                                        \
				blend(_used_dst_x, _used_dst_y, _used_src_x, _used_src_y0, (_used_src_x + 1), _used_src_y1,                        \
				      _frac_x0, _frac_x1, _frac_y0, _frac_y1);                                                                     \
			}                                                                                                                      \
			if (_pad_xmax) {                                                                                                       \
				video_coord_t _used_src_x = src_x + src_size_x - 1;                                                                \
				blend_xmin(_used_dst_x, _used_dst_y, _pad_xmax, _used_src_x, _used_src_y0, _used_src_y1, _frac_y0, _frac_y1);      \
				/*_used_dst_x += left_pad_w;*/                                                                                     \
			}                                                                                                                      \
		}                                                                                                                          \
		                                                                                                                           \
		/* Render padding near the bottom */                                                                                       \
		if (_pad_ymax) {                                                                                                           \
			video_coord_t _used_dst_y = dst_y + dst_size_y - _pad_ymax;                                                            \
			video_coord_t _used_dst_x = dst_x;                                                                                     \
			video_dim_t _middle;                                                                                                   \
			video_coord_t _used_src_y = src_y + src_size_y - 1;                                                                    \
			sstretch_fp_t _row_fp_src_x;                                                                                           \
			                                                                                                                       \
			if (_pad_xmin) {                                                                                                       \
				blend_xmin_ymin(_used_dst_x, _used_dst_y, _pad_xmin, _pad_ymax, src_x, _used_src_y);                               \
				_used_dst_x += _pad_xmin;                                                                                          \
			}                                                                                                                      \
			for (_middle = _nopad_dst_x, _row_fp_src_x = _fp_src_x;                                                                \
			     _middle; --_middle, ++_used_dst_x, _row_fp_src_x += _fp_step_x) {                                                 \
				video_coord_t _used_src_x  = src_x + STRETCH_FP_WHOLE(_row_fp_src_x);                                              \
				linear_fp_blend_t _frac_x0 = STRETCH_FP_BLEND_FRAC(_row_fp_src_x);                                                 \
				linear_fp_blend_t _frac_x1 = LINEAR_FP_BLEND(1) - _frac_x0;                                                        \
				blend_ymin(_used_dst_x, _used_dst_y, _pad_ymax, _used_src_x, _used_src_y, (_used_src_x + 1), _frac_x0, _frac_x1);  \
			}                                                                                                                      \
			if (_pad_xmax) {                                                                                                       \
				video_coord_t _used_src_x = src_x + src_size_x - 1;                                                                \
				blend_xmax_ymax(_used_dst_x, _used_dst_y, _pad_xmax, _pad_ymax, _used_src_x, _used_src_y);                         \
				/*_used_dst_x += left_pad_w;*/                                                                                     \
			}                                                                                                                      \
		}                                                                                                                          \
	}	__WHILE0

/************************************************************************/
/************************************************************************/
/************************************************************************/



/* Returns 0 or 1 */
LOCAL ATTR_PURE WUNUSED NONNULL((1)) byte_t CC
bitmask2d_getbit(byte_t const *__restrict bitmask, size_t bitscan,
                 video_coord_t x, video_coord_t y) {
	uintptr_t bitno = (uintptr_t)x + y * bitscan;
	byte_t byte;
	byte  = bitmask[bitno / NBBY];
	bitno = bitno % NBBY;
	return (byte >> ((NBBY - 1) - bitno)) & 1;
}

/* Returns 0 or 255 */
LOCAL ATTR_PURE WUNUSED NONNULL((1)) channel_t CC
bitmask2d_getbit_channel(byte_t const *__restrict bitmask, size_t bitscan,
                         video_coord_t x, video_coord_t y) {
	uintptr_t bitno = (uintptr_t)x + y * bitscan;
	byte_t byte;
	byte  = bitmask[bitno / NBBY];
	bitno = bitno % NBBY;
#if 1
	/* Move the bit we're interested in to the most significant position.
	 * e.g.: when "bitno == 0", then we want bit masked by 0x80
	 *       when "bitno == 3", then we want bit masked by 0x10 */
	byte <<= bitno;
	/* Used signed shift to duplicate the most significant bit into all other bits. */
	byte = (byte_t)((__SBYTE_TYPE__)byte >> (NBBY - 1));
	return byte;
#else
	return ((byte >> (NBBY - 1) - bitno) & 1) ? 0xff : 0;
#endif
}


/* Check if {x1,y1} <= {x2,y2} */
#define xy_before_or_equal(x1, y1, x2, y2) ((y1) < (y2) || ((y1) == (y2) && (x1) <= (x2)))


/* Helpers for I/O Area limits */
#define _GFX_SELF self
#define GFX_BXMIN _GFX_SELF->vx_hdr.vxh_bxmin
#define GFX_BYMIN _GFX_SELF->vx_hdr.vxh_bymin
#define GFX_BXEND _GFX_SELF->vx_hdr.vxh_bxend
#define GFX_BYEND _GFX_SELF->vx_hdr.vxh_byend
#define GFX_BXMAX (_GFX_SELF->vx_hdr.vxh_bxend - 1)
#define GFX_BYMAX (_GFX_SELF->vx_hdr.vxh_byend - 1)

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_UTILS_H */
