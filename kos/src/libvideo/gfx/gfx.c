/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif(x -> x.startswith("-O"));
gcc_opt.append("-O3"); // Force _all_ optimizations because stuff in here is performance-critical
]]]*/
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
#ifndef GUARD_LIBVIDEO_GFX_GFX_C
#define GUARD_LIBVIDEO_GFX_GFX_C 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/bit.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <kos/types.h>
#include <sys/param.h>

#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/blendcolors.h>
#include <libvideo/gfx/gfx.h>
/**/

#include "gfx-empty.h"
#include "gfx-utils.h"
#include "gfx.h"

DECL_BEGIN

static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ZERO) == GFX_BLENDDATA_ONE);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE) == GFX_BLENDDATA_ZERO);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_SRC_COLOR) == GFX_BLENDDATA_ONE_MINUS_SRC_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_SRC_COLOR) == GFX_BLENDDATA_SRC_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_DST_COLOR) == GFX_BLENDDATA_ONE_MINUS_DST_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_DST_COLOR) == GFX_BLENDDATA_DST_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_SRC_ALPHA) == GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA) == GFX_BLENDDATA_SRC_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_DST_ALPHA) == GFX_BLENDDATA_ONE_MINUS_DST_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_DST_ALPHA) == GFX_BLENDDATA_DST_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_CONSTANT_COLOR) == GFX_BLENDDATA_ONE_MINUS_CONSTANT_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_CONSTANT_COLOR) == GFX_BLENDDATA_CONSTANT_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_CONSTANT_ALPHA) == GFX_BLENDDATA_ONE_MINUS_CONSTANT_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_CONSTANT_ALPHA) == GFX_BLENDDATA_CONSTANT_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_SRC_ALPHA_SATURATE) == GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA_SATURATE);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA_SATURATE) == GFX_BLENDDATA_SRC_ALPHA_SATURATE);

static_assert(sizeof(struct video_blitter_xops) == (_VIDEO_BLIT_XOPS__N_INTERNAL * sizeof(void (*)(void))),
              "sizeof(struct video_blitter_xops) doesn't match '_VIDEO_BLIT_XOPS__N_INTERNAL'");
static_assert(sizeof(struct video_gfx_xops) == (_VIDEO_GFX_XOPS__N_INTERNAL * sizeof(void (*)(void))),
              "sizeof(struct video_gfx_xops) doesn't match '_VIDEO_GFX_XOPS__N_INTERNAL'");

#ifndef PRIdOFF
#define PRIdOFF PRIdN(__SIZEOF_VIDEO_OFFSET_T__)
#define PRIxOFF PRIxN(__SIZEOF_VIDEO_OFFSET_T__)
#define PRIuCRD PRIuN(__SIZEOF_VIDEO_COORD_T__)
#define PRIxCRD PRIxN(__SIZEOF_VIDEO_COORD_T__)
#define PRIuDIM PRIuN(__SIZEOF_VIDEO_DIM_T__)
#define PRIxDIM PRIxN(__SIZEOF_VIDEO_DIM_T__)
#define PRIxCOL PRIxN(__SIZEOF_VIDEO_COLOR_T__)
#endif /* !PRIdOFF */

#define _GFX_SELF self
#define GFX_BXMIN _GFX_SELF->vx_hdr.vxh_bxmin
#define GFX_BYMIN _GFX_SELF->vx_hdr.vxh_bymin
#define GFX_BXEND _GFX_SELF->vx_hdr.vxh_bxend
#define GFX_BYEND _GFX_SELF->vx_hdr.vxh_byend
#define GFX_BXMAX (_GFX_SELF->vx_hdr.vxh_bxend - 1)
#define GFX_BYMAX (_GFX_SELF->vx_hdr.vxh_byend - 1)


/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/*                                                                      */
/* INTERNAL API                                                         */
/*                                                                      */
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/


/* Low-level, Generic, always-valid GFX color functions (using only `vgxo_getpixel' + `vgxo_setpixel') */
INTERN ATTR_IN(1) video_color_t CC
libvideo_gfx_generic__getcolor_noblend(struct video_gfx const *__restrict self,
                                       video_coord_t x, video_coord_t y) {
	video_pixel_t pixel = _video_gfx_x_getpixel(self, x, y);
	return self->vx_buffer->vb_format.pixel2color(pixel);
}

INTERN ATTR_IN(1) video_color_t CC
libvideo_gfx_generic__getcolor_blur(struct video_gfx const *__restrict self,
                                    video_coord_t x, video_coord_t y) {
	video_color_t result;
	video_color_t colors[8];
	video_twochannels_t r, g, b, a;
	uint_fast8_t i, color_count;
#define MODE_XMIN 0x1
#define MODE_XMAX 0x2
#define MODE_YMIN 0x4
#define MODE_YMAX 0x8
	uint_fast8_t mode = 0x0;
	/* Figure out how we're situated in relation to bounds. */
	if unlikely(x == self->vx_hdr.vxh_bxmin)
		mode |= MODE_XMIN;
	if unlikely(y == self->vx_hdr.vxh_bymin)
		mode |= MODE_YMIN;
	if unlikely(x == self->vx_hdr.vxh_bxend - 1)
		mode |= MODE_XMAX;
	if unlikely(y == self->vx_hdr.vxh_byend - 1)
		mode |= MODE_YMAX;
	/* Load colors as needed. */
	switch (__builtin_expect(mode, 0x0)) {
#define GETCOLOR(xoff, yoff) \
		libvideo_gfx_generic__getcolor_noblend(self, x + (xoff), y + (yoff))

	case 0x0:
		/* +++ */
		/* +.+ */
		/* +++ */
		color_count = 8;
		colors[0] = GETCOLOR(-1, -1);
		colors[1] = GETCOLOR(0, -1);
		colors[2] = GETCOLOR(1, -1);

		colors[3] = GETCOLOR(-1, 0);
		colors[4] = GETCOLOR(1, 0);

		colors[5] = GETCOLOR(-1, 1);
		colors[6] = GETCOLOR(0, 1);
		colors[7] = GETCOLOR(1, 1);
		break;

	case MODE_XMIN:
		/* -++ */
		/* -.+ */
		/* -++ */
		color_count = 5;
		colors[0] = GETCOLOR(0, -1);
		colors[1] = GETCOLOR(1, -1);

		colors[2] = GETCOLOR(1, 0);

		colors[3] = GETCOLOR(0, 1);
		colors[4] = GETCOLOR(1, 1);
		break;

	case MODE_XMAX:
		/* ++- */
		/* +.- */
		/* ++- */
		color_count = 5;
		colors[0] = GETCOLOR(-1, -1);
		colors[1] = GETCOLOR(0, -1);

		colors[2] = GETCOLOR(-1, 0);

		colors[3] = GETCOLOR(-1, 1);
		colors[4] = GETCOLOR(0, 1);
		break;

	case MODE_YMIN:
		/* --- */
		/* +.+ */
		/* +++ */
		color_count = 5;
		colors[0] = GETCOLOR(-1, 0);
		colors[1] = GETCOLOR(1, 0);
		colors[2] = GETCOLOR(-1, 1);
		colors[3] = GETCOLOR(0, 1);
		colors[4] = GETCOLOR(1, 1);
		break;

	case MODE_YMAX:
		/* +++ */
		/* +.+ */
		/* --- */
		color_count = 5;
		colors[0] = GETCOLOR(-1, -1);
		colors[1] = GETCOLOR(0, -1);
		colors[2] = GETCOLOR(1, -1);
		colors[3] = GETCOLOR(-1, 0);
		colors[4] = GETCOLOR(1, 0);
		break;

	case MODE_YMIN | MODE_YMAX:
		/* --- */
		/* +.+ */
		/* --- */
		color_count = 2;
		colors[0] = GETCOLOR(-1, 0);
		colors[1] = GETCOLOR(1, 0);
		break;

	case MODE_XMIN | MODE_XMAX:
		/* -+- */
		/* -.- */
		/* -+- */
		color_count = 2;
		colors[0] = GETCOLOR(0, -1);
		colors[1] = GETCOLOR(0, 1);
		break;

	case MODE_YMIN | MODE_XMIN:
		/* --- */
		/* -.+ */
		/* -++ */
		color_count = 3;
		colors[0] = GETCOLOR(1, 0);
		colors[1] = GETCOLOR(0, 1);
		colors[2] = GETCOLOR(1, 1);
		break;

	case MODE_YMIN | MODE_XMAX:
		/* --- */
		/* +.- */
		/* ++- */
		color_count = 3;
		colors[0] = GETCOLOR(-1, 0);
		colors[1] = GETCOLOR(-1, 1);
		colors[2] = GETCOLOR(0, 1);
		break;

	case MODE_YMAX | MODE_XMIN:
		/* -++ */
		/* -.+ */
		/* --- */
		color_count = 3;
		colors[0] = GETCOLOR(0, -1);
		colors[1] = GETCOLOR(1, -1);
		colors[2] = GETCOLOR(1, 0);
		break;

	case MODE_YMAX | MODE_XMAX:
		/* ++- */
		/* +.- */
		/* --- */
		color_count = 3;
		colors[0] = GETCOLOR(-1, -1);
		colors[1] = GETCOLOR(0, -1);
		colors[2] = GETCOLOR(-1, 0);
		break;

	case MODE_XMIN | MODE_XMAX | MODE_YMIN:
		/* --- */
		/* -.- */
		/* -+- */
		color_count = 1;
		colors[0] = GETCOLOR(0, 1);
		break;

	case MODE_XMIN | MODE_XMAX | MODE_YMAX:
		/* -+- */
		/* -.- */
		/* --- */
		color_count = 1;
		colors[0] = GETCOLOR(0, -1);
		break;

	case MODE_YMIN | MODE_YMAX | MODE_XMIN:
		/* --- */
		/* -.+ */
		/* --- */
		color_count = 1;
		colors[0] = GETCOLOR(1, 0);
		break;

	case MODE_YMIN | MODE_YMAX | MODE_XMAX:
		/* --- */
		/* +.- */
		/* --- */
		color_count = 1;
		colors[0] = GETCOLOR(-1, 0);
		break;

	case MODE_XMIN | MODE_YMIN | MODE_XMAX | MODE_YMAX:
		/* --- */
		/* -.- */
		/* --- */
		color_count = 0;
		break;

#undef GETCOLOR
	default: __builtin_unreachable();
	}
#undef MODE_XMIN
#undef MODE_XMAX
#undef MODE_YMIN
#undef MODE_YMAX
	result = libvideo_gfx_generic__getcolor_noblend(self, x, y);
	r = VIDEO_COLOR_GET_RED(result);
	g = VIDEO_COLOR_GET_GREEN(result);
	b = VIDEO_COLOR_GET_BLUE(result);
	a = VIDEO_COLOR_GET_ALPHA(result);
	for (i = 0; i < color_count; ++i) {
		r += VIDEO_COLOR_GET_RED(colors[i]);
		g += VIDEO_COLOR_GET_GREEN(colors[i]);
		b += VIDEO_COLOR_GET_BLUE(colors[i]);
		a += VIDEO_COLOR_GET_ALPHA(colors[i]);
	}
	++color_count;
	r /= color_count;
	g /= color_count;
	b /= color_count;
	a /= color_count;
	result = VIDEO_COLOR_RGBA((video_channel_t)r,
	                          (video_channel_t)g,
	                          (video_channel_t)b,
	                          (video_channel_t)a);
	return result;
}

INTERN ATTR_IN(1) video_color_t CC
libvideo_gfx_generic__getcolor_with_key(struct video_gfx const *__restrict self,
                                        video_coord_t x, video_coord_t y) {
	video_pixel_t pixel = _video_gfx_x_getpixel(self, x, y);
	video_color_t result = self->vx_buffer->vb_format.pixel2color(pixel);
	if (result == self->vx_colorkey)
		result = 0;
	return result;
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic__putcolor(struct video_gfx const *__restrict self,
                               video_coord_t x, video_coord_t y,
                               video_color_t color) {
	video_pixel_t o_pixel = _video_gfx_x_getpixel(self, x, y);
	video_color_t o_color = self->vx_buffer->vb_format.pixel2color(o_pixel);
	video_color_t n_color = gfx_blendcolors(o_color, color, self->vx_blend);
	video_pixel_t n_pixel = self->vx_buffer->vb_format.color2pixel(n_color);
	_video_gfx_x_setpixel(self, x, y, n_pixel);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic__putcolor_noblend(struct video_gfx const *__restrict self,
                                       video_coord_t x, video_coord_t y,
                                       video_color_t color) {
	video_pixel_t n_pixel = self->vx_buffer->vb_format.color2pixel(color);
	_video_gfx_x_setpixel(self, x, y, n_pixel);
}

#define DEFINE_libvideo_gfx_generic__putcolor_FOO(name, mode)                      \
	INTERN ATTR_IN(1) void CC                                                      \
	libvideo_gfx_generic__putcolor_##name(struct video_gfx const *__restrict self, \
	                                      video_coord_t x, video_coord_t y,        \
	                                      video_color_t color) {                   \
		video_pixel_t o_pixel = _video_gfx_x_getpixel(self, x, y);                 \
		video_color_t o_color = self->vx_buffer->vb_format.pixel2color(o_pixel);   \
		video_color_t n_color = gfx_blendcolors(o_color, color, mode);             \
		video_pixel_t n_pixel = self->vx_buffer->vb_format.color2pixel(n_color);   \
		_video_gfx_x_setpixel(self, x, y, n_pixel);                                \
	}
GFX_FOREACH_DEDICATED_BLENDMODE(DEFINE_libvideo_gfx_generic__putcolor_FOO)
#undef DEFINE_libvideo_gfx_generic__putcolor_FOO





/* Generic, always-valid GFX functions (using only `vx_pxops') */
INTERN ATTR_IN(1) void CC
libvideo_gfx_generic__absline_llhh(struct video_gfx const *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_dim_t size_x, video_dim_t size_y,
                                   video_color_t color) {
	video_dim_t step;
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend__absline_llhh(self, dst_x, dst_y, size_x, size_y, color);
		return;
	}
	gfx_assert(size_x > 0);
	gfx_assert(size_y > 0);
	step = 0;
	if (size_x > size_y) {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y + (video_dim_t)(((uint64_t)size_y * step) / size_x);
			video_gfx_x_putcolor(self, line_x, line_y, color);
		} while (++step != size_x);
	} else if (size_x < size_y) {
		do {
			video_coord_t line_x = dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y);
			video_coord_t line_y = dst_y + step;
			video_gfx_x_putcolor(self, line_x, line_y, color);
		} while (++step != size_y);
	} else {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y + step;
			video_gfx_x_putcolor(self, line_x, line_y, color);
		} while (++step != size_x);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic__absline_lhhl(struct video_gfx const *__restrict self,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_dim_t size_x, video_dim_t size_y,
                                   video_color_t color) {
	video_dim_t step;
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend__absline_lhhl(self, dst_x, dst_y, size_x, size_y, color);
		return;
	}
	gfx_assert(size_x > 0);
	gfx_assert(size_y > 0);
	step = 0;
	if (size_x > size_y) {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y - (video_dim_t)(((uint64_t)size_y * step) / size_x);
			video_gfx_x_putcolor(self, line_x, line_y, color);
		} while (++step != size_x);
	} else if (size_x < size_y) {
		do {
			video_coord_t line_x = dst_x + (video_dim_t)(((uint64_t)size_x * step) / size_y);
			video_coord_t line_y = dst_y - step;
			video_gfx_x_putcolor(self, line_x, line_y, color);
		} while (++step != size_y);
	} else {
		do {
			video_coord_t line_x = dst_x + step;
			video_coord_t line_y = dst_y - step;
			video_gfx_x_putcolor(self, line_x, line_y, color);
		} while (++step != size_x);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic__absline_llhh_aa(struct video_gfx const *__restrict self,
                                      video_coord_t dst_x, video_coord_t dst_y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      video_color_t color) {
	/* TODO: anti-aliased line drawing */
	libvideo_gfx_generic__absline_llhh(self, dst_x, dst_y, size_x, size_y, color);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic__absline_lhhl_aa(struct video_gfx const *__restrict self,
                                      video_coord_t dst_x, video_coord_t dst_y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      video_color_t color) {
	/* TODO: anti-aliased line drawing */
	libvideo_gfx_generic__absline_lhhl(self, dst_x, dst_y, size_x, size_y, color);
}



INTERN ATTR_IN(1) void CC
libvideo_gfx_generic__absline_h(struct video_gfx const *__restrict self,
                                video_coord_t dst_x, video_coord_t dst_y,
                                video_dim_t length, video_color_t color) {
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend__absline_h(self, dst_x, dst_y, length, color);
		return;
	}
	do {
		video_gfx_x_putcolor(self, dst_x, dst_y, color);
		++dst_x;
	} while (--length);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic__absline_v(struct video_gfx const *__restrict self,
                                video_coord_t dst_x, video_coord_t dst_y,
                                video_dim_t length, video_color_t color) {
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend__absline_v(self, dst_x, dst_y, length, color);
		return;
	}
	do {
		video_gfx_x_putcolor(self, dst_x, dst_y, color);
		++dst_y;
	} while (--length);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic__absfill(struct video_gfx const *__restrict self,
                              video_coord_t dst_x, video_coord_t dst_y,
                              video_dim_t size_x, video_dim_t size_y,
                              video_color_t color) {
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend__absfill(self, dst_x, dst_y, size_x, size_y, color);
		return;
	}
	do {
		video_gfx_x_absline_h(self, dst_x, dst_y, size_x, color);
		++dst_y;
	} while (--size_y);
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
libvideo_gfx_generic__absgradient(struct video_gfx const *__restrict self,
                                  video_coord_t dst_x_, video_coord_t dst_y_,
                                  video_dim_t size_x_, video_dim_t size_y_,
                                  video_color_t colors[2][2]) {
	struct video_gfx noblend;
	video_color_t noblend_colors[2][2];

	/* Check for special case: not actually a 4-color gradient */
	if (colors[0][0] == colors[0][1] && colors[1][0] == colors[1][1]) {
		libvideo_gfx_generic__absgradient_v(self, dst_x_, dst_y_, size_x_, size_y_,
		                                    colors[0][0], colors[1][0]);
		return;
	} else if (colors[0][0] == colors[1][0] && colors[0][1] == colors[1][1]) {
		libvideo_gfx_generic__absgradient_h(self, dst_x_, dst_y_, size_x_, size_y_,
		                                    colors[0][0], colors[0][1]);
		return;
	}

	/* Check for special case: can blending be disabled? */
	if ((self->vx_buffer->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) &&
	    (noblend_colors[0][0] = colors[0][0], libvideo_gfx_allow_noblend(self, &noblend_colors[0][0])) &&
	    (noblend_colors[0][1] = colors[0][1], libvideo_gfx_allow_noblend(self, &noblend_colors[0][1])) &&
	    (noblend_colors[1][0] = colors[1][0], libvideo_gfx_allow_noblend(self, &noblend_colors[1][0])) &&
	    (noblend_colors[1][1] = colors[1][1], libvideo_gfx_allow_noblend(self, &noblend_colors[1][1]))) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend_interp8888__absgradient(self, dst_x_, dst_y_, size_x_, size_y_, noblend_colors);
		return;
	}
#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y) \
	{                                                                             \
		video_color_t out = colors[src_y][src_x];                                 \
		video_gfx_x_absfill(self, dst_x, dst_y, dst_size_x, dst_size_y, out);     \
	}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                       \
		video_color_t src_y0_x0 = colors[src_y][src_x0];                                    \
		video_color_t src_y0_x1 = colors[src_y][src_x1];                                    \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);   \
		video_gfx_x_absline_v(self, dst_x, dst_y, dst_size_y, out);                         \
	}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                       \
		video_color_t src_y0_x0 = colors[src_y0][src_x];                                    \
		video_color_t src_y1_x0 = colors[src_y1][src_x];                                    \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);   \
		video_gfx_x_absline_h(self, dst_x, dst_y, dst_size_x, out);                         \
	}

#define pixel_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                 \
		video_color_t src_y0_x0 = colors[src_y0][src_x0];                                             \
		video_color_t src_y0_x1 = colors[src_y0][src_x1];                                             \
		video_color_t src_y1_x0 = colors[src_y1][src_x0];                                             \
		video_color_t src_y1_x1 = colors[src_y1][src_x1];                                             \
		video_color_t out = interpolate_2d(src_y0_x0, src_y0_x1,                                      \
		                                   src_y1_x0, src_y1_x1,                                      \
		                                   frac_x0, frac_x1,                                          \
		                                   frac_y0, frac_y1);                                         \
		video_gfx_x_putcolor(self, dst_x, dst_y, out);                                                \
	}

	TRACE_START("generic__absgradient("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {{%#" PRIxCOL ", %#" PRIxCOL "}, {%#" PRIxCOL ", %#" PRIxCOL "}})\n",
	            dst_x_, dst_y_, size_x_, size_y_,
	            colors[0][0], colors[0][1], colors[1][0], colors[1][1]);
	GFX_LINEAR_STRETCH(dst_x_, dst_y_, size_x_, size_y_,
	                   0, 0, 2, 2,
	                   pixel_blend_xmin_ymin,
	                   pixel_blend_ymin,
	                   pixel_blend_xmax_ymin,
	                   pixel_blend_xmin,
	                   pixel_blend,
	                   pixel_blend_xmax,
	                   pixel_blend_xmin_ymax,
	                   pixel_blend_ymax,
	                   pixel_blend_xmax_ymax);
	TRACE_END("generic__absgradient()\n");
#undef pixel_blend_xmin_ymin
#undef pixel_blend_ymin
#undef pixel_blend_xmax_ymin
#undef pixel_blend_xmin
#undef pixel_blend
#undef pixel_blend_xmax
#undef pixel_blend_xmin_ymax
#undef pixel_blend_ymax
#undef pixel_blend_xmax_ymax
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic__absgradient_h(struct video_gfx const *__restrict self,
                                    video_coord_t dst_x, video_coord_t dst_y,
                                    video_dim_t size_x, video_dim_t size_y,
                                    video_color_t locolor, video_color_t hicolor) {
	video_dim_t pad_xmin, pad_xmax;
	sstretch_fp_t fp_src_x;
	stretch_fp_t fp_step_x;
	struct video_gfx noblend;
	video_color_t noblend_colors[2];

	/* Check for special case: not actually a gradient */
	if (locolor == hicolor) {
		libvideo_gfx_generic__absfill(self, dst_x, dst_y, size_x, size_y, locolor);
		return;
	}

	/* Check for special case: can blending be disabled? */
	if ((self->vx_buffer->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) &&
	    (noblend_colors[0] = locolor, libvideo_gfx_allow_noblend(self, &noblend_colors[0])) &&
	    (noblend_colors[1] = hicolor, libvideo_gfx_allow_noblend(self, &noblend_colors[1]))) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend_interp8888__absgradient_h(self, dst_x, dst_y, size_x, size_y,
		                                               noblend_colors[0], noblend_colors[1]);
		return;
	}
	TRACE_START("generic__absgradient_h("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {%#" PRIxCOL ", %#" PRIxCOL "})\n",
	            dst_x, dst_y, size_x, size_y,
	            locolor, hicolor);
	calc_linear_stretch_dim(2, size_x, &fp_src_x, &fp_step_x, &pad_xmin, &pad_xmax);
	if (pad_xmin) {
		video_gfx_x_absfill(self, dst_x, dst_y, pad_xmin, size_y, locolor);
		dst_x += pad_xmin;
		size_x -= pad_xmin;
		fp_src_x += pad_xmin * fp_step_x;
	}
	if (pad_xmax) {
		size_x -= pad_xmax;
		video_gfx_x_absfill(self, dst_x + size_x, dst_y, pad_xmax, size_y, hicolor);
	}
	for (; size_x; --size_x, ++dst_x, fp_src_x += fp_step_x) {
		linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_x);
		linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
		video_color_t color = interpolate_1d(locolor, hicolor, frac0, frac1);
		video_gfx_x_absline_v(self, dst_x, dst_y, size_y, color);
	}
	TRACE_END("generic__absgradient_h()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic__absgradient_v(struct video_gfx const *__restrict self,
                                    video_coord_t dst_x, video_coord_t dst_y,
                                    video_dim_t size_x, video_dim_t size_y,
                                    video_color_t locolor, video_color_t hicolor) {
	video_dim_t pad_ymin, pad_ymax;
	sstretch_fp_t fp_src_y;
	stretch_fp_t fp_step_y;
	struct video_gfx noblend;
	video_color_t noblend_colors[2];

	/* Check for special case: not actually a gradient */
	if (locolor == hicolor) {
		libvideo_gfx_generic__absfill(self, dst_x, dst_y, size_x, size_y, locolor);
		return;
	}

	/* Check for special case: can blending be disabled? */
	if ((self->vx_buffer->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_INTERP8888) &&
	    (noblend_colors[0] = locolor, libvideo_gfx_allow_noblend(self, &noblend_colors[0])) &&
	    (noblend_colors[1] = hicolor, libvideo_gfx_allow_noblend(self, &noblend_colors[1]))) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend_interp8888__absgradient_v(self, dst_x, dst_y, size_x, size_y,
		                                               noblend_colors[0], noblend_colors[1]);
		return;
	}
	TRACE_START("generic__absgradient_v("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "colors: {%#" PRIxCOL ", %#" PRIxCOL "})\n",
	            dst_x, dst_y, size_x, size_y,
	            locolor, hicolor);
	calc_linear_stretch_dim(2, size_y, &fp_src_y, &fp_step_y, &pad_ymin, &pad_ymax);
	if (pad_ymin) {
		video_gfx_x_absfill(self, dst_x, dst_y, size_x, pad_ymin, locolor);
		dst_y += pad_ymin;
		size_y -= pad_ymin;
		fp_src_y += pad_ymin * fp_step_y;
	}
	if (pad_ymax) {
		size_y -= pad_ymax;
		video_gfx_x_absfill(self, dst_x, dst_y + size_y, size_x, pad_ymax, hicolor);
	}
	for (; size_y; --size_y, ++dst_y, fp_src_y += fp_step_y) {
		linear_fp_blend_t frac0 = STRETCH_FP_BLEND_FRAC(fp_src_y);
		linear_fp_blend_t frac1 = LINEAR_FP_BLEND(1) - frac0;
		video_color_t color = interpolate_1d(locolor, hicolor, frac0, frac1);
		video_gfx_x_absline_h(self, dst_x, dst_y, size_x, color);
	}
	TRACE_END("generic__absgradient_v()\n");
}




/************************************************************************/
/* BIT-MASKED FILL                                                      */
/************************************************************************/

INTERN ATTR_IN(1) ATTR_IN(7) void CC
libvideo_gfx_generic__bitfill(struct video_gfx const *__restrict self,
                              video_coord_t dst_x, video_coord_t dst_y,
                              video_dim_t size_x, video_dim_t size_y,
                              video_color_t color,
                              struct video_bitmask const *__restrict bm) {
	byte_t const *bitmask;
	uintptr_t bitskip;
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
		libvideo_gfx_noblend__bitfill(self, dst_x, dst_y, size_x, size_y,
		                              color, bm);
		return;
	}
	TRACE_START("generic__bitfill("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", bm: %p+%" PRIuPTR ")\n",
	            dst_x, dst_y, size_x, size_y, color, bm->vbm_mask, bm->vbm_skip);
	bitmask = (byte_t const *)bm->vbm_mask;
	bitskip = bm->vbm_skip;
	bitmask += bitskip / NBBY;
	bitskip = bitskip % NBBY;
#ifndef __OPTIMIZE_SIZE__
	if likely(bitskip == 0 && !(bm->vbm_scan & 7)) {
		size_t bm_scanline = bm->vbm_scan >> 3;
		switch (size_x) {
#define DO_FIXED_WORD_RENDER(N)                                         \
			do {                                                        \
				video_dim_t x = dst_x;                                  \
				uint##N##_t word = UNALIGNED_GET##N(bitmask);           \
				while (word) {                                          \
					shift_t bits;                                       \
					bits = CLZ((uint##N##_t)word);                      \
					x += bits;                                          \
					word <<= bits;                                      \
					bits = CLZ((uint##N##_t) ~word);                    \
					gfx_assert(bits > 0);                               \
					video_gfx_x_absline_h(self, x, dst_y, bits, color); \
					x += bits;                                          \
					word <<= bits;                                      \
				}                                                       \
				++dst_y;                                                \
				bitmask += bm_scanline;                                 \
			} while (--size_y)
		case 0 ... 8:
			DO_FIXED_WORD_RENDER(8);
			goto done;
		case 9 ... 16:
			DO_FIXED_WORD_RENDER(16);
			goto done;
		case 17 ... 32:
			DO_FIXED_WORD_RENDER(32);
			goto done;
#if __SIZEOF_REGISTER__ >= 8
		case 33 ... 64:
			DO_FIXED_WORD_RENDER(64);
			goto done;
#endif /* __SIZEOF_REGISTER__ >= 8 */
		default: break;
#undef DO_FIXED_WORD_RENDER
		}
	}
#endif /* !__OPTIMIZE_SIZE__ */
	do {
		video_dim_t x;
		uintptr_t row_bitskip;
		byte_t const *row;
		x = 0;
		row_bitskip = bitskip;
		row = bitmask;
		do {
			video_dim_t count;
			byte_t byte = *row;
			shift_t bits = NBBY - row_bitskip;

			/* Skip over 0-bits */
			for (;;) {
				--bits;
				++row_bitskip;
				if (byte & ((byte_t)1 << bits))
					break;
				++x;
				if (x >= size_x)
					goto next_row;
				if (!bits) {
					byte = *++row;
					row_bitskip = 0;
					bits = NBBY;
				}
			}

			/* Count consecutive 1-bits */
			count = 1;
			while ((x + count) < size_x) {
				if (!bits) {
					byte = *++row;
					row_bitskip = 0;
					bits = NBBY;
				}
				--bits;
				if (!(byte & ((byte_t)1 << bits)))
					break;
				++row_bitskip;
				++count;
			}
			video_gfx_x_absline_h(self, dst_x + x, dst_y, count, color);
			x += count;
		} while (x < size_x);
next_row:
		bitskip += bm->vbm_scan;
		bitmask += bitskip / NBBY;
		bitskip = bitskip % NBBY;
		++dst_y;
	} while (--size_y);
#ifndef __OPTIMIZE_SIZE__
done:
#endif /* !__OPTIMIZE_SIZE__ */
	TRACE_END("generic__bitfill()\n");
}

INTERN ATTR_IN(1) ATTR_IN(9) void CC
libvideo_gfx_generic__bitstretchfill_l(struct video_gfx const *__restrict self,
                                       video_coord_t dst_x_, video_coord_t dst_y_,
                                       video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                       video_color_t color,
                                       video_dim_t src_size_x_, video_dim_t src_size_y_,
                                       struct video_bitmask const *__restrict bm) {
	uintptr_t bitskip_ = bm->vbm_skip;
	byte_t const *bitmask = (byte_t const *)bm->vbm_mask;
	video_color_t raw_color = color & ~VIDEO_COLOR_ALPHA_MASK;
	channel_t raw_alpha = VIDEO_COLOR_GET_ALPHA(color);
#define makealpha(alpha_chan) (channel_t)(((twochannels_t)raw_alpha * (alpha_chan)) / CHANNEL_MAX)
#define makecolor(alpha_chan) (raw_color | ((video_color_t)makealpha(alpha_chan) << VIDEO_COLOR_ALPHA_SHIFT))
	bitmask += bitskip_ / NBBY;
	bitskip_ = bitskip_ % NBBY;

#define getbit(src_x, src_y) bitmask2d_getbit(bitmask, bm->vbm_scan, src_x, src_y)

#define bitmask_blend_xmax_ymin bitmask_blend_xmin_ymin
#define bitmask_blend_xmin_ymax bitmask_blend_xmin_ymin
#define bitmask_blend_xmax_ymax bitmask_blend_xmin_ymin
#define bitmask_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y) \
	{                                                                               \
		if (getbit(src_x, src_y))                                                   \
			video_gfx_x_absfill(self, dst_x, dst_y, dst_size_x, dst_size_y, color); \
	}

#define bitmask_blend_ymax bitmask_blend_ymin
#define bitmask_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                         \
		channel_t src_y0_x0 = getbit(src_x0, src_y);                                          \
		channel_t src_y0_x1 = getbit(src_x1, src_y);                                          \
		channel_t chan = interpolate_channel_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);      \
		if (chan) {                                                                           \
			video_color_t out = makecolor(chan);                                              \
			video_gfx_x_absline_v(self, dst_x, dst_y, dst_size_y, out);                       \
		}                                                                                     \
	}

#define bitmask_blend_xmax bitmask_blend_xmin
#define bitmask_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                         \
		channel_t src_y0_x0 = getbit(src_x, src_y0);                                          \
		channel_t src_y1_x0 = getbit(src_x, src_y1);                                          \
		channel_t chan = interpolate_channel_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);      \
		if (chan) {                                                                           \
			video_color_t out = makecolor(chan);                                              \
			video_gfx_x_absline_h(self, dst_x, dst_y, dst_size_x, out);                       \
		}                                                                                     \
	}

#define bitmask_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                   \
		channel_t src_y0_x0 = getbit(src_x0, src_y0);                                                   \
		channel_t src_y0_x1 = getbit(src_x1, src_y0);                                                   \
		channel_t src_y1_x0 = getbit(src_x0, src_y1);                                                   \
		channel_t src_y1_x1 = getbit(src_x1, src_y1);                                                   \
		channel_t chan = interpolate_channel_2d(src_y0_x0, src_y0_x1,                                   \
		                                        src_y1_x0, src_y1_x1,                                   \
		                                        frac_x0, frac_x1,                                       \
		                                        frac_y0, frac_y1);                                      \
		if (chan) {                                                                                     \
			video_color_t out = makecolor(chan);                                                        \
			video_gfx_x_putcolor(self, dst_x, dst_y, out);                                              \
		}                                                                                               \
	}

	TRACE_START("generic__bitstretchfill_l("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", "
	            "src: {%" PRIuDIM "x%" PRIuDIM "}, bm: %p+%" PRIuPTR ")\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            color, src_size_x_, src_size_y_, bm->vbm_mask, bm->vbm_skip);
	GFX_LINEAR_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                   bitskip_, 0, src_size_x_, src_size_y_,
	                   bitmask_blend_xmin_ymin,
	                   bitmask_blend_ymin,
	                   bitmask_blend_xmax_ymin,
	                   bitmask_blend_xmin,
	                   bitmask_blend,
	                   bitmask_blend_xmax,
	                   bitmask_blend_xmin_ymax,
	                   bitmask_blend_ymax,
	                   bitmask_blend_xmax_ymax);
	TRACE_END("generic__bitstretchfill_l()\n");
#undef bitmask_blend_xmin_ymin
#undef bitmask_blend_ymin
#undef bitmask_blend_xmax_ymin
#undef bitmask_blend_xmin
#undef bitmask_blend
#undef bitmask_blend_xmax
#undef bitmask_blend_xmin_ymax
#undef bitmask_blend_ymax
#undef bitmask_blend_xmax_ymax

#undef getbit
#undef makealpha
#undef makecolor
}

INTERN ATTR_IN(1) ATTR_IN(9) void CC
libvideo_gfx_generic__bitstretchfill_n(struct video_gfx const *__restrict self,
                                       video_coord_t dst_x, video_coord_t dst_y,
                                       video_dim_t dst_size_x, video_dim_t dst_size_y,
                                       video_color_t color,
                                       video_dim_t src_size_x, video_dim_t src_size_y,
                                       struct video_bitmask const *__restrict bm) {
	video_dim_t y;
	stretch_fp_t step_x, step_y, src_pos_y;
	struct video_gfx noblend;
	if (libvideo_gfx_allow_noblend(self, &color)) {
		noblend = *self;
		self = video_gfx_noblend(&noblend);
	}
	if ((src_size_x < (dst_size_x >> 1)) &&
	    (src_size_y < (dst_size_y >> 1))) {
		/* TODO: Iterate across "src"  and use  "video_gfx_x_absfill"
		 *       to fill rects associated with visible source pixels. */
	}
	TRACE_START("generic__bitstretchfill_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", "
	            "src: {%" PRIuDIM "x%" PRIuDIM "}, bm: %p+%" PRIuPTR ")\n",
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            color, src_size_x, src_size_y, bm->vbm_mask, bm->vbm_skip);
	step_x = STRETCH_FP(src_size_x) / dst_size_x;
	step_y = STRETCH_FP(src_size_y) / dst_size_y;
	src_pos_y = step_y >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
	y = 0;
	do {
		video_coord_t row_dst_y = dst_y + y;
		video_coord_t row_src_y = STRETCH_FP_WHOLE(src_pos_y);
		stretch_fp_t src_pos_x = step_x >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
		video_dim_t x = 0;
		uintptr_t row_bitno = bm->vbm_skip + row_src_y * bm->vbm_scan;
		do {
			video_coord_t row_src_x = STRETCH_FP_WHOLE(src_pos_x);
			uintptr_t bitno = row_bitno + row_src_x;
			if (((byte_t const *)bm->vbm_mask)[bitno / NBBY] & ((byte_t)1 << ((NBBY - 1) - (bitno % NBBY))))
				video_gfx_x_putcolor(self, dst_x + x, row_dst_y, color);
			src_pos_x += step_x;
			++x;
		} while (x < dst_size_x);
		++y;
		src_pos_y += step_y;
	} while (y < dst_size_y);
	TRACE_END("generic__bitstretchfill_n()\n");
}

/************************************************************************/
/* GENERIC BLIT OPERATORS                                               */
/************************************************************************/
INTERN ATTR_IN(1) void CC
libvideo_blitter_generic__blit(struct video_blitter const *__restrict self,
                           video_coord_t dst_x, video_coord_t dst_y,
                           video_coord_t src_x, video_coord_t src_y,
                           video_dim_t size_x, video_dim_t size_y) {
	video_dim_t x, y;
	struct video_gfx const *src = self->vbt_src;
	struct video_gfx const *dst = self->vbt_dst;
	TRACE_START("generic__blit("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x, dst_y, src_x, src_y, size_x, size_y);
	for (y = 0; y < size_y; ++y) {
		for (x = 0; x < size_x; ++x) {
			video_color_t color;
			color = video_gfx_x_getcolor(src, src_x + x, src_y + y);
			video_gfx_x_putcolor(dst, dst_x + x, dst_y + y, color);
		}
	}
	TRACE_END("generic__blit()\n");
}


INTERN ATTR_IN(1) void CC
libvideo_blitter_generic__stretch_l(struct video_blitter const *__restrict self,
                                    video_coord_t dst_x_, video_coord_t dst_y_,
                                    video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                    video_coord_t src_x_, video_coord_t src_y_,
                                    video_dim_t src_size_x_, video_dim_t src_size_y_) {
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y) \
	{                                                                             \
		video_color_t out = video_gfx_x_getcolor(src, src_x, src_y);              \
		video_gfx_x_absfill(dst, dst_x, dst_y, dst_size_x, dst_size_y, out);      \
	}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                       \
		video_color_t src_y0_x0 = video_gfx_x_getcolor(src, src_x0, src_y);                 \
		video_color_t src_y0_x1 = video_gfx_x_getcolor(src, src_x1, src_y);                 \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);   \
		video_gfx_x_absline_v(dst, dst_x, dst_y, dst_size_y, out);                          \
	}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                       \
		video_color_t src_y0_x0 = video_gfx_x_getcolor(src, src_x, src_y0);                 \
		video_color_t src_y1_x0 = video_gfx_x_getcolor(src, src_x, src_y1);                 \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);   \
		video_gfx_x_absline_h(dst, dst_x, dst_y, dst_size_x, out);                          \
	}

#define pixel_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                 \
		video_color_t src_y0_x0 = video_gfx_x_getcolor(src, src_x0, src_y0);                          \
		video_color_t src_y0_x1 = video_gfx_x_getcolor(src, src_x1, src_y0);                          \
		video_color_t src_y1_x0 = video_gfx_x_getcolor(src, src_x0, src_y1);                          \
		video_color_t src_y1_x1 = video_gfx_x_getcolor(src, src_x1, src_y1);                          \
		video_color_t out = interpolate_2d(src_y0_x0, src_y0_x1,                                      \
		                                   src_y1_x0, src_y1_x1,                                      \
		                                   frac_x0, frac_x1,                                          \
		                                   frac_y0, frac_y1);                                         \
		video_gfx_x_putcolor(dst, dst_x, dst_y, out);                                                 \
	}

	TRACE_START("generic__stretch_l("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            src_x_, src_y_, src_size_x_, src_size_y_);
	GFX_LINEAR_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                   src_x_, src_y_, src_size_x_, src_size_y_,
	                   pixel_blend_xmin_ymin,
	                   pixel_blend_ymin,
	                   pixel_blend_xmax_ymin,
	                   pixel_blend_xmin,
	                   pixel_blend,
	                   pixel_blend_xmax,
	                   pixel_blend_xmin_ymax,
	                   pixel_blend_ymax,
	                   pixel_blend_xmax_ymax);
	TRACE_END("generic__stretch_l()\n");
#undef pixel_blend_xmin_ymin
#undef pixel_blend_ymin
#undef pixel_blend_xmax_ymin
#undef pixel_blend_xmin
#undef pixel_blend
#undef pixel_blend_xmax
#undef pixel_blend_xmin_ymax
#undef pixel_blend_ymax
#undef pixel_blend_xmax_ymax
}

INTERN ATTR_IN(1) void CC
libvideo_blitter_generic__stretch_n(struct video_blitter const *__restrict self,
                                    video_coord_t dst_x, video_coord_t dst_y,
                                    video_dim_t dst_size_x, video_dim_t dst_size_y,
                                    video_coord_t src_x, video_coord_t src_y,
                                    video_dim_t src_size_x, video_dim_t src_size_y) {
	video_dim_t y;
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
	stretch_fp_t step_x, step_y, src_pos_y;
	TRACE_START("generic__stretch_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            src_x, src_y, src_size_x, src_size_y);
	step_x = STRETCH_FP(src_size_x) / dst_size_x;
	step_y = STRETCH_FP(src_size_y) / dst_size_y;
	src_pos_y  = step_y >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
	y = 0;
	do {
		video_coord_t row_dst_y = dst_y + y;
		video_coord_t row_src_y = src_y + STRETCH_FP_WHOLE(src_pos_y);
		stretch_fp_t src_pos_x = step_x >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
		video_dim_t x = 0;
		src_pos_x += STRETCH_FP(src_x);
		do {
			video_color_t color;
			video_coord_t row_src_x = STRETCH_FP_WHOLE(src_pos_x);
			color = video_gfx_x_getcolor(src, row_src_x, row_src_y);
			video_gfx_x_putcolor(dst, dst_x + x, row_dst_y, color);
			src_pos_x += step_x;
			++x;
		} while (x < dst_size_x);
		++y;
		src_pos_y += step_y;
	} while (y < dst_size_y);
	TRACE_END("generic__stretch_n()\n");
}


/* Special impls for when the blit src/dst are identical */
INTERN ATTR_IN(1) void CC
libvideo_blitter_samebuf__blit(struct video_blitter const *__restrict self,
                               video_coord_t dst_x, video_coord_t dst_y,
                               video_coord_t src_x, video_coord_t src_y,
                               video_dim_t size_x, video_dim_t size_y) {
	/* TODO */
	libvideo_blitter_generic__blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
}

INTERN ATTR_IN(1) void CC
libvideo_blitter_samebuf__stretch_l(struct video_blitter const *__restrict self,
                                    video_coord_t dst_x, video_coord_t dst_y,
                                    video_dim_t dst_size_x, video_dim_t dst_size_y,
                                    video_coord_t src_x, video_coord_t src_y,
                                    video_dim_t src_size_x, video_dim_t src_size_y) {
	/* TODO */
	libvideo_blitter_generic__stretch_l(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y);
}

INTERN ATTR_IN(1) void CC
libvideo_blitter_samebuf__stretch_n(struct video_blitter const *__restrict self,
                                    video_coord_t dst_x, video_coord_t dst_y,
                                    video_dim_t dst_size_x, video_dim_t dst_size_y,
                                    video_coord_t src_x, video_coord_t src_y,
                                    video_dim_t src_size_x, video_dim_t src_size_y) {
	/* TODO */
	libvideo_blitter_generic__stretch_n(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y);
}






/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/*                                                                      */
/* PUBLIC API                                                           */
/*                                                                      */
/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/




/************************************************************************/
/* GETCOLOR()                                                           */
/************************************************************************/
INTERN ATTR_IN(1) video_color_t CC
libvideo_gfx_generic_getcolor(struct video_gfx const *__restrict self,
                              video_offset_t x, video_offset_t y) {
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if likely((video_coord_t)x >= GFX_BXMIN && (video_coord_t)x < GFX_BXEND &&
	          (video_coord_t)y >= GFX_BYMIN && (video_coord_t)y < GFX_BYEND)
		return _video_gfx_x_getcolor(self, (video_coord_t)x, (video_coord_t)y);
	return 0;
}

INTERN ATTR_IN(1) video_color_t CC
libvideo_gfx_generic_getcolor_rdwrap(struct video_gfx const *__restrict self,
                                     video_offset_t x, video_offset_t y) {
	if (self->vx_flags & VIDEO_GFX_FRDXWRAP)
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
	if (self->vx_flags & VIDEO_GFX_FRDYWRAP)
		y = wrap(y, self->vx_hdr.vxh_cysiz);
	return libvideo_gfx_generic_getcolor(self, x, y);
}



/************************************************************************/
/* PUTCOLOR()                                                           */
/************************************************************************/
INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_putcolor(struct video_gfx const *__restrict self,
                              video_offset_t x, video_offset_t y,
                              video_color_t color) {
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if likely((video_coord_t)x >= GFX_BXMIN && (video_coord_t)x < GFX_BXEND &&
	          (video_coord_t)y >= GFX_BYMIN && (video_coord_t)y < GFX_BYEND)
		_video_gfx_x_putcolor(self, (video_coord_t)x, (video_coord_t)y, color);
}
INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_putcolor_wrwrap(struct video_gfx const *__restrict self,
                                     video_offset_t x, video_offset_t y,
                                     video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP)
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP)
		y = wrap(y, self->vx_hdr.vxh_cysiz);
	libvideo_gfx_generic_putcolor(self, x, y, color);
}


/************************************************************************/
/* LINE()                                                               */
/************************************************************************/
INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_line(struct video_gfx const *__restrict self,
                          video_offset_t x1, video_offset_t y1,
                          video_offset_t x2, video_offset_t y2,
                          video_color_t color) {
	/* >> Cohen-Sutherland algorithm
	 * https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm */
	int outcode0, outcode1, outcodeOut;
	video_offset_t temp, x, y;
#define COHSUTH_INSIDE 0 /* 0000 */
#define COHSUTH_XMIN   1 /* 0001 */
#define COHSUTH_XMAX   2 /* 0010 */
#define COHSUTH_YMIN   4 /* 0100 */
#define COHSUTH_YMAX   8 /* 1000 */
	x1 += self->vx_hdr.vxh_cxoff;
	y1 += self->vx_hdr.vxh_cyoff;
	x2 += self->vx_hdr.vxh_cxoff;
	y2 += self->vx_hdr.vxh_cyoff;
#define COHSUTH_COMPUTEOUTCODE(x, y, result)           \
	do {                                               \
		(result) = COHSUTH_INSIDE;                     \
		if ((x) < (video_offset_t)GFX_BXMIN) {         \
			(result) |= COHSUTH_XMIN;                  \
		} else if ((x) >= (video_offset_t)GFX_BXEND) { \
			(result) |= COHSUTH_XMAX;                  \
		}                                              \
		if ((y) < (video_offset_t)GFX_BYMIN) {         \
			(result) |= COHSUTH_YMIN;                  \
		} else if ((y) >= (video_offset_t)GFX_BYEND) { \
			(result) |= COHSUTH_YMAX;                  \
		}                                              \
	}	__WHILE0
	COHSUTH_COMPUTEOUTCODE(x1, y1, outcode0);
	COHSUTH_COMPUTEOUTCODE(x2, y2, outcode1);
	while ((outcode0 | outcode1) != 0) {
		if ((outcode0 & outcode1) != 0)
			return;
		outcodeOut = outcode0 ? outcode0 : outcode1;
		if ((outcodeOut & COHSUTH_YMAX) != 0) {
			x = x1 + (x2 - x1) * ((video_offset_t)GFX_BYMAX - y1) / (y2 - y1);
			y = (video_offset_t)GFX_BYMAX;
		} else if ((outcodeOut & COHSUTH_YMIN) != 0) {
			x = x1 + (x2 - x1) * ((video_offset_t)GFX_BYMIN - y1) / (y2 - y1);
			y = (video_offset_t)GFX_BYMIN;
		} else if ((outcodeOut & COHSUTH_XMAX) != 0) {
			y = y1 + (y2 - y1) * ((video_offset_t)GFX_BXMAX - x1) / (x2 - x1);
			x = (video_offset_t)GFX_BXMAX;
		} else /*if ((outcodeOut & COHSUTH_XMIN) != 0)*/ {
			y = y1 + (y2 - y1) * ((video_offset_t)GFX_BXMIN - x1) / (x2 - x1);
			x = (video_offset_t)GFX_BXMIN;
		}
		if (outcodeOut == outcode0) {
			x1 = x;
			y1 = y;
			COHSUTH_COMPUTEOUTCODE(x1, y1, outcode0);
		} else {
			x2 = x;
			y2 = y;
			COHSUTH_COMPUTEOUTCODE(x2, y2, outcode1);
		}
	}
	gfx_assert_absbounds_xy(self, (video_coord_t)x1, (video_coord_t)y1);
	gfx_assert_absbounds_xy(self, (video_coord_t)x2, (video_coord_t)y2);

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
			video_gfx_x_putcolor(self,
			                      (video_coord_t)x1,
			                      (video_coord_t)y1,
			                      color);
			return;
		}
		video_gfx_x_absline_v(self, (video_coord_t)x1, (video_coord_t)y1,
		                      (video_dim_t)((video_coord_t)y2 - (video_coord_t)y1) + 1,
		                      color);
		return;
	}
	gfx_assert(x2 > x1);
	if (y2 > y1) {
		video_dim_t sx = (video_dim_t)((video_coord_t)x2 - (video_coord_t)x1) + 1;
		video_dim_t sy = (video_dim_t)((video_coord_t)y2 - (video_coord_t)y1) + 1;
		video_gfx_x_absline_llhh(self, (video_coord_t)x1, (video_coord_t)y1, sx, sy, color);
	} else if (y2 < y1) {
		video_dim_t sx = (video_dim_t)((video_coord_t)x2 - (video_coord_t)x1) + 1;
		video_dim_t sy = (video_dim_t)((video_coord_t)y1 - (video_coord_t)y2) + 1;
		video_gfx_x_absline_lhhl(self, (video_coord_t)x1, (video_coord_t)y1, sx, sy, color);
	} else {
		video_dim_t length = (video_dim_t)((video_coord_t)x2 - (video_coord_t)x1) + 1;
		video_gfx_x_absline_h(self, (video_coord_t)x1, (video_coord_t)y1, length, color);
	}
#undef COHSUTH_COMPUTEOUTCODE
#undef COHSUTH_INSIDE
#undef COHSUTH_XMIN
#undef COHSUTH_XMAX
#undef COHSUTH_YMIN
#undef COHSUTH_YMAX
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_line_wrwrap(struct video_gfx const *__restrict self,
                                 video_offset_t x1, video_offset_t y1,
                                 video_offset_t x2, video_offset_t y2,
                                 video_color_t color) {
	/* TODO */
	libvideo_gfx_generic_line(self, x1, y1, x2, y2, color);
}



/************************************************************************/
/* HLINE()                                                              */
/************************************************************************/
INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_hline(struct video_gfx const *__restrict self,
                           video_offset_t x, video_offset_t y,
                           video_dim_t length, video_color_t color) {
	video_coord_t temp;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(y < (video_offset_t)GFX_BYMIN)
		return;
	if unlikely(y >= (video_offset_t)GFX_BYEND)
		return;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(length <= off)
			return;
		length -= off;
		x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, length, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		length = GFX_BXEND - (video_coord_t)x;
	}

	video_gfx_x_absline_h(self, (video_coord_t)x, (video_coord_t)y, length, color);
}


INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_hline_wrwrap(struct video_gfx const *__restrict self,
                                  video_offset_t x, video_offset_t y,
                                  video_dim_t length, video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP)
		y = wrap(y, self->vx_hdr.vxh_cysiz);
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP) {
		video_coord_t cxend;
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
		if (OVERFLOW_UADD((video_coord_t)x, length, &cxend) || length >= self->vx_hdr.vxh_cxsiz) {
			x = 0;
			length = self->vx_hdr.vxh_cxsiz;
		} else if (cxend > self->vx_hdr.vxh_cxsiz) {
			libvideo_gfx_generic_hline(self, 0, y, cxend - self->vx_hdr.vxh_cxsiz, color);
		}
	}
	libvideo_gfx_generic_hline(self, x, y, length, color);
}



/************************************************************************/
/* VLINE()                                                              */
/************************************************************************/
INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_vline(struct video_gfx const *__restrict self,
                           video_offset_t x, video_offset_t y,
                           video_dim_t length, video_color_t color) {
	video_coord_t temp;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN)
		return;
	if unlikely(x >= (video_offset_t)GFX_BXEND)
		return;
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(length <= off)
			return;
		length -= off;
		y = (video_offset_t)GFX_BYMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, length, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		length = GFX_BYEND - (video_coord_t)y;
	}
	video_gfx_x_absline_v(self, (video_coord_t)x, (video_coord_t)y, length, color);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_vline_wrwrap(struct video_gfx const *__restrict self,
                                  video_offset_t x, video_offset_t y,
                                  video_dim_t length, video_color_t color) {
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP)
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP) {
		video_coord_t cyend;
		y = wrap(y, self->vx_hdr.vxh_cysiz);
		if (OVERFLOW_UADD((video_coord_t)y, length, &cyend) || length >= self->vx_hdr.vxh_cysiz) {
			y = 0;
			length = self->vx_hdr.vxh_cysiz;
		} else if (cyend > self->vx_hdr.vxh_cysiz) {
			libvideo_gfx_generic_vline(self, x, 0, cyend - self->vx_hdr.vxh_cysiz, color);
		}
	}
	libvideo_gfx_generic_vline(self, x, y, length, color);
}



/************************************************************************/
/* FILL()                                                               */
/************************************************************************/
INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_fill(struct video_gfx const *__restrict self,
                          video_offset_t x, video_offset_t y,
                          video_dim_t size_x, video_dim_t size_y,
                          video_color_t color) {
	video_coord_t temp;
	if unlikely(!size_x || !size_y)
		return;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(size_x <= off)
			return;
		size_x -= off;
		x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(size_y <= off)
			return;
		size_y -= off;
		y = (video_offset_t)GFX_BYMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, size_x, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		size_x = GFX_BXEND - (video_coord_t)x;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, size_y, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		size_y = GFX_BYEND - (video_coord_t)y;
	}
	video_gfx_x_absfill(self, (video_coord_t)x, (video_coord_t)y,
	                    size_x, size_y, color);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_fill_wrwrap(struct video_gfx const *__restrict self,
                                 video_offset_t x, video_offset_t y,
                                 video_dim_t size_x, video_dim_t size_y,
                                 video_color_t color) {
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP) {
		video_coord_t cxend;
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
		if (OVERFLOW_UADD((video_coord_t)x, size_x, &cxend) || size_x >= self->vx_hdr.vxh_cxsiz) {
			x = 0;
			size_x = self->vx_hdr.vxh_cxsiz;
		} else {
			/* # of pixels that go beyond the right clip-edge */
			if (OVERFLOW_USUB(cxend, self->vx_hdr.vxh_cxsiz, &xwrap))
				xwrap = 0;
		}
	}
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP) {
		video_coord_t cyend;
		y = wrap(y, self->vx_hdr.vxh_cysiz);
		if (OVERFLOW_UADD((video_coord_t)y, size_y, &cyend) || size_y >= self->vx_hdr.vxh_cysiz) {
			y = 0;
			size_y = self->vx_hdr.vxh_cysiz;
		} else {
			/* # of pixels that go beyond the bottom clip-edge */
			if (OVERFLOW_USUB(cyend, self->vx_hdr.vxh_cysiz, &ywrap))
				ywrap = 0;
		}
	}
	if (xwrap && ywrap) /* Must do a partial fill at the top-left */
		libvideo_gfx_generic_fill(self, 0, 0, xwrap, ywrap, color);
	if (xwrap) /* Must do a partial fill at the left */
		libvideo_gfx_generic_fill(self, 0, y, xwrap, size_y, color);
	if (ywrap) /* Must do a partial fill at the top */
		libvideo_gfx_generic_fill(self, x, 0, size_x, ywrap, color);
	libvideo_gfx_generic_fill(self, x, y, size_x, size_y, color);
}



/************************************************************************/
/* RECT()                                                               */
/************************************************************************/
INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_rect(struct video_gfx const *__restrict self,
                          video_offset_t x, video_offset_t y,
                          video_dim_t size_x, video_dim_t size_y,
                          video_color_t color) {
	video_dim_t temp;
#define LINE_XMIN 0x1
#define LINE_YMIN 0x2
#define LINE_XMAX 0x4
#define LINE_YMAX 0x8
	uint8_t draw_lines;
	if unlikely(!size_x || !size_y)
		return;
	draw_lines = 0xf;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(size_x <= off)
			return;
		size_x -= off;
		x = (video_offset_t)GFX_BXMIN;
		draw_lines &= ~LINE_XMIN;
	}
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(size_y <= off)
			return;
		size_y -= off;
		y = (video_offset_t)GFX_BYMIN;
		draw_lines &= ~LINE_YMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, size_x, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		size_x = GFX_BXEND - (video_coord_t)x;
		draw_lines &= ~LINE_XMAX;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, size_y, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		size_y = GFX_BYEND - (video_coord_t)y;
		draw_lines &= ~LINE_YMAX;
	}
#define HLINE(x, y, length) video_gfx_x_absline_h(self, x, y, length, color)
#define VLINE(x, y, length) video_gfx_x_absline_v(self, x, y, length, color)
	switch (draw_lines) {

		/* All 4 lines */
	case LINE_XMIN | LINE_YMIN | LINE_XMAX | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
			if (size_y >= 3) {
				VLINE((video_coord_t)x, (video_coord_t)y + 1, size_y - 2); /* XMIN */
				if (size_x >= 2)
					VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y + 1, size_y - 2); /* XMAX */
			}
		}
		break;

		/* 3-line combinations */
	case LINE_YMIN | LINE_YMAX | LINE_XMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
			if (size_y >= 3)
				VLINE((video_coord_t)x, (video_coord_t)y + 1, size_y - 2); /* XMIN */
		}
		break;

	case LINE_YMIN | LINE_YMAX | LINE_XMAX:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
			if (size_y >= 3)
				VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y + 1, size_y - 2); /* XMAX */
		}
		break;

	case LINE_XMIN | LINE_XMAX | LINE_YMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2) {
			VLINE((video_coord_t)x, (video_coord_t)y + 1, size_y - 1); /* XMIN */
			if (size_x >= 2)
				VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y + 1, size_y - 1); /* XMAX */
		}
		break;

	case LINE_XMIN | LINE_XMAX | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
		if (size_y >= 2) {
			VLINE((video_coord_t)x, (video_coord_t)y, size_y - 1); /* XMIN */
			if (size_x >= 2)
				VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y, size_y - 1); /* XMAX */
		}
		break;

		/* Adjacent lines */
	case LINE_XMIN | LINE_YMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2)
			VLINE((video_coord_t)x, (video_coord_t)y + 1, size_y - 1); /* XMIN */
		break;

	case LINE_XMAX | LINE_YMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2)
			VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y + 1, size_y - 1); /* XMAX */
		break;

	case LINE_XMIN | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
		if (size_y >= 2)
			VLINE((video_coord_t)x, (video_coord_t)y, size_y - 1); /* XMIN */
		break;

	case LINE_XMAX | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
		if (size_y >= 2)
			VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y, size_y - 1); /* XMAX */
		break;


		/* Opposing lines */
	case LINE_XMIN | LINE_XMAX:
		VLINE((video_coord_t)x, (video_coord_t)y, size_y); /* XMIN */
		if (size_x >= 2)
			VLINE((video_coord_t)x + size_x - 1, (video_coord_t)y, size_y); /* XMAX */
		break;

	case LINE_YMIN | LINE_YMAX:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN */
		if (size_y >= 2)
			HLINE((video_coord_t)x, (video_coord_t)y + size_y - 1, size_x); /* YMAX */
		break;

		/* Single lines */
	case LINE_XMAX:
		x += size_x - 1;
		ATTR_FALLTHROUGH
	case LINE_XMIN:
		VLINE((video_coord_t)x, (video_coord_t)y, size_y); /* XMIN / XMAX */
		break;

	case LINE_YMAX:
		y += size_y - 1;
		ATTR_FALLTHROUGH
	case LINE_YMIN:
		HLINE((video_coord_t)x, (video_coord_t)y, size_x); /* YMIN / YMAX */
		break;

	case 0: /* Completely out-of-bounds */
		break;

	default:
		__builtin_unreachable();
	}
#undef VLINE
#undef HLINE
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_rect_wrwrap(struct video_gfx const *__restrict self,
                                 video_offset_t x, video_offset_t y,
                                 video_dim_t size_x, video_dim_t size_y,
                                 video_color_t color) {
	if (size_x <= 1) {
		if unlikely(!size_x)
			return;
		libvideo_gfx_generic_vline_wrwrap(self, x, y, size_y, color);
	} else if (size_y <= 1) {
		if unlikely(!size_y)
			return;
		libvideo_gfx_generic_hline_wrwrap(self, x, y, size_x, color);
	} else {
		video_offset_t ymax = y + size_y - 1;
		libvideo_gfx_generic_hline_wrwrap(self, x, y, size_x, color);
		libvideo_gfx_generic_hline_wrwrap(self, x, ymax, size_x, color);
		if (size_y > 2) {
			video_offset_t xmax = x + size_x - 1;
			libvideo_gfx_generic_vline_wrwrap(self, x, y + 1, size_y - 2, color);
			libvideo_gfx_generic_vline_wrwrap(self, xmax, y + 1, size_y - 2, color);
		}
	}
}




/************************************************************************/
/* FILLGRADIENT()                                                       */
/************************************************************************/
INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_gradient(struct video_gfx const *__restrict self,
                              video_offset_t x, video_offset_t y,
                              video_dim_t size_x, video_dim_t size_y,
                              video_color_t colors[2][2]) {
	video_coord_t temp;
	video_color_t fixed_colors[2][2];
	if unlikely(!size_x || !size_y)
		return;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(size_x <= off)
			return;
		frac0 = (off * LINEAR_FP_BLEND(1)) / size_x;
		frac1 = LINEAR_FP_BLEND(1) - frac0;
		size_x -= off;
		x = (video_offset_t)GFX_BXMIN;
		colors = (video_color_t (*)[2])memcpy(fixed_colors, colors, sizeof(fixed_colors));
		fixed_colors[0][0] = interpolate_1d(fixed_colors[0][0], fixed_colors[0][1], frac0, frac1);
		fixed_colors[1][0] = interpolate_1d(fixed_colors[1][0], fixed_colors[1][1], frac0, frac1);
	}
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(size_y <= off)
			return;
		frac0 = (off * LINEAR_FP_BLEND(1)) / size_y;
		frac1 = LINEAR_FP_BLEND(1) - frac0;
		size_y -= off;
		y = (video_offset_t)GFX_BYMIN;
		colors = (video_color_t (*)[2])memcpy(fixed_colors, colors, sizeof(fixed_colors));
		fixed_colors[0][0] = interpolate_1d(fixed_colors[0][0], fixed_colors[1][0], frac0, frac1);
		fixed_colors[0][1] = interpolate_1d(fixed_colors[0][1], fixed_colors[1][1], frac0, frac1);
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, size_x, &temp) || temp > GFX_BXEND) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off;
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		off = temp - GFX_BXEND;
		frac1 = (off * LINEAR_FP_BLEND(1)) / size_x;
		frac0 = LINEAR_FP_BLEND(1) - frac1;
		size_x = GFX_BXEND - (video_coord_t)x;
		colors = (video_color_t (*)[2])memcpy(fixed_colors, colors, sizeof(fixed_colors));
		fixed_colors[0][1] = interpolate_1d(fixed_colors[0][0], fixed_colors[0][1], frac1, frac0);
		fixed_colors[1][1] = interpolate_1d(fixed_colors[1][0], fixed_colors[1][1], frac1, frac0);
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, size_y, &temp) || temp > GFX_BYEND) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off;
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		off = temp - GFX_BYEND;
		frac1 = (off * LINEAR_FP_BLEND(1)) / size_y;
		frac0 = LINEAR_FP_BLEND(1) - frac1;
		size_y = GFX_BYEND - (video_coord_t)y;
		colors = (video_color_t (*)[2])memcpy(fixed_colors, colors, sizeof(fixed_colors));
		fixed_colors[1][0] = interpolate_1d(fixed_colors[0][0], fixed_colors[1][0], frac1, frac0);
		fixed_colors[1][1] = interpolate_1d(fixed_colors[0][1], fixed_colors[1][1], frac1, frac0);
	}
	video_gfx_x_absgradient(self, (video_coord_t)x, (video_coord_t)y,
	                        size_x, size_y, colors);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_gradient_wrwrap(struct video_gfx const *__restrict self,
                                     video_offset_t x, video_offset_t y,
                                     video_dim_t size_x, video_dim_t size_y,
                                     video_color_t colors[2][2]) {
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP) {
		video_coord_t cxend;
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
		if (OVERFLOW_UADD((video_coord_t)x, size_x, &cxend) || size_x >= self->vx_hdr.vxh_cxsiz) {
			x = 0;
			size_x = self->vx_hdr.vxh_cxsiz;
		} else {
			/* # of pixels that go beyond the right clip-edge */
			if (OVERFLOW_USUB(cxend, self->vx_hdr.vxh_cxsiz, &xwrap))
				xwrap = 0;
		}
	}
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP) {
		video_coord_t cyend;
		y = wrap(y, self->vx_hdr.vxh_cysiz);
		if (OVERFLOW_UADD((video_coord_t)y, size_y, &cyend) || size_y >= self->vx_hdr.vxh_cysiz) {
			y = 0;
			size_y = self->vx_hdr.vxh_cysiz;
		} else {
			/* # of pixels that go beyond the bottom clip-edge */
			if (OVERFLOW_USUB(cyend, self->vx_hdr.vxh_cysiz, &ywrap))
				ywrap = 0;
		}
	}
	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		linear_fp_blend_t xfrac0, xfrac1;
		linear_fp_blend_t yfrac0, yfrac1;
		video_color_t fixed_colors[2][2];
		xfrac0 = (xwrap * LINEAR_FP_BLEND(1)) / size_x;
		xfrac1 = LINEAR_FP_BLEND(1) - xfrac0;
		yfrac0 = (ywrap * LINEAR_FP_BLEND(1)) / size_y;
		yfrac1 = LINEAR_FP_BLEND(1) - yfrac0;
		fixed_colors[0][0] = interpolate_2d(colors[0][0], colors[0][1], colors[1][0], colors[1][1],
		                                    xfrac1, xfrac0, yfrac1, yfrac0);
		fixed_colors[1][0] = interpolate_1d(colors[1][0], colors[1][1], xfrac1, xfrac0);
		fixed_colors[0][1] = interpolate_1d(colors[0][1], colors[1][1], yfrac1, yfrac0);
		fixed_colors[1][1] = colors[1][1];
		libvideo_gfx_generic_gradient(self, 0, 0, xwrap, ywrap, fixed_colors);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		linear_fp_blend_t xfrac0, xfrac1;
		video_color_t fixed_colors[2][2];
		xfrac0 = (xwrap * LINEAR_FP_BLEND(1)) / size_x;
		xfrac1 = LINEAR_FP_BLEND(1) - xfrac0;
		fixed_colors[0][0] = interpolate_1d(colors[0][0], colors[0][1], xfrac1, xfrac0);
		fixed_colors[1][0] = interpolate_1d(colors[1][0], colors[1][1], xfrac1, xfrac0);
		fixed_colors[0][1] = colors[0][1];
		fixed_colors[1][1] = colors[1][1];
		libvideo_gfx_generic_gradient(self, 0, y, xwrap, size_y, fixed_colors);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		linear_fp_blend_t yfrac0, yfrac1;
		video_color_t fixed_colors[2][2];
		yfrac0 = (ywrap * LINEAR_FP_BLEND(1)) / size_y;
		yfrac1 = LINEAR_FP_BLEND(1) - yfrac0;
		fixed_colors[0][0] = interpolate_1d(colors[0][0], colors[1][0], yfrac1, yfrac0);
		fixed_colors[1][0] = colors[1][0];
		fixed_colors[0][1] = interpolate_1d(colors[0][1], colors[1][1], yfrac1, yfrac0);
		fixed_colors[1][1] = colors[1][1];
		libvideo_gfx_generic_gradient(self, x, 0, size_x, ywrap, fixed_colors);
	}
	libvideo_gfx_generic_gradient(self, x, y, size_x, size_y, colors);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_hgradient(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y,
                               video_dim_t size_x, video_dim_t size_y,
                               video_color_t locolor, video_color_t hicolor) {
	video_coord_t temp;
	if unlikely(!size_x || !size_y)
		return;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(size_x <= off)
			return;
		frac0 = (off * LINEAR_FP_BLEND(1)) / size_x;
		frac1 = LINEAR_FP_BLEND(1) - frac0;
		size_x -= off;
		x = (video_offset_t)GFX_BXMIN;
		locolor = interpolate_1d(locolor, hicolor, frac0, frac1);
	}
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(size_y <= off)
			return;
		size_y -= off;
		y = (video_offset_t)GFX_BYMIN;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, size_x, &temp) || temp > GFX_BXEND) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off;
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		off = temp - GFX_BXEND;
		frac1 = (off * LINEAR_FP_BLEND(1)) / size_x;
		frac0 = LINEAR_FP_BLEND(1) - frac1;
		size_x = GFX_BXEND - (video_coord_t)x;
		hicolor = interpolate_1d(locolor, hicolor, frac1, frac0);
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, size_y, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		size_y = GFX_BYEND - (video_coord_t)y;
	}
	video_gfx_x_absgradient_h(self, (video_coord_t)x, (video_coord_t)y,
	                          size_x, size_y, locolor, hicolor);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_hgradient_wrwrap(struct video_gfx const *__restrict self,
                                      video_offset_t x, video_offset_t y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      video_color_t locolor, video_color_t hicolor) {
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP) {
		video_coord_t cxend;
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
		if (OVERFLOW_UADD((video_coord_t)x, size_x, &cxend) || size_x >= self->vx_hdr.vxh_cxsiz) {
			x = 0;
			size_x = self->vx_hdr.vxh_cxsiz;
		} else {
			/* # of pixels that go beyond the right clip-edge */
			if (OVERFLOW_USUB(cxend, self->vx_hdr.vxh_cxsiz, &xwrap))
				xwrap = 0;
		}
	}
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP) {
		video_coord_t cyend;
		y = wrap(y, self->vx_hdr.vxh_cysiz);
		if (OVERFLOW_UADD((video_coord_t)y, size_y, &cyend) || size_y >= self->vx_hdr.vxh_cysiz) {
			y = 0;
			size_y = self->vx_hdr.vxh_cysiz;
		} else {
			/* # of pixels that go beyond the bottom clip-edge */
			if (OVERFLOW_USUB(cyend, self->vx_hdr.vxh_cysiz, &ywrap))
				ywrap = 0;
		}
	}
	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		linear_fp_blend_t xfrac0, xfrac1;
		video_color_t fixed_locolor;
		xfrac0 = (xwrap * LINEAR_FP_BLEND(1)) / size_x;
		xfrac1 = LINEAR_FP_BLEND(1) - xfrac0;
		fixed_locolor = interpolate_1d(locolor, hicolor, xfrac1, xfrac0);
		libvideo_gfx_generic_hgradient(self, 0, 0, xwrap, ywrap, fixed_locolor, hicolor);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		linear_fp_blend_t xfrac0, xfrac1;
		video_color_t fixed_locolor;
		xfrac0 = (xwrap * LINEAR_FP_BLEND(1)) / size_x;
		xfrac1 = LINEAR_FP_BLEND(1) - xfrac0;
		fixed_locolor = interpolate_1d(locolor, hicolor, xfrac1, xfrac0);
		libvideo_gfx_generic_hgradient(self, 0, y, xwrap, size_y, fixed_locolor, hicolor);
	}
	if (ywrap) /* Must do a partial fill at the top */
		libvideo_gfx_generic_hgradient(self, x, 0, size_x, ywrap, locolor, hicolor);
	libvideo_gfx_generic_hgradient(self, x, y, size_x, size_y, locolor, hicolor);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_vgradient(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y,
                               video_dim_t size_x, video_dim_t size_y,
                               video_color_t locolor, video_color_t hicolor) {
	video_coord_t temp;
	if unlikely(!size_x || !size_y)
		return;
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely(x < (video_offset_t)GFX_BXMIN) {
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BXMIN - x);
		if unlikely(size_x <= off)
			return;
		size_x -= off;
		x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(y < (video_offset_t)GFX_BYMIN) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off = (video_dim_t)((video_offset_t)GFX_BYMIN - y);
		if unlikely(size_y <= off)
			return;
		frac0 = (off * LINEAR_FP_BLEND(1)) / size_y;
		frac1 = LINEAR_FP_BLEND(1) - frac0;
		size_y -= off;
		y = (video_offset_t)GFX_BYMIN;
		locolor = interpolate_1d(locolor, hicolor, frac0, frac1);
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)x, size_x, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)x >= GFX_BXEND)
			return;
		size_x = GFX_BXEND - (video_coord_t)x;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)y, size_y, &temp) || temp > GFX_BYEND) {
		linear_fp_blend_t frac0, frac1;
		video_dim_t off;
		if unlikely((video_coord_t)y >= GFX_BYEND)
			return;
		off = temp - GFX_BYEND;
		frac1 = (off * LINEAR_FP_BLEND(1)) / size_y;
		frac0 = LINEAR_FP_BLEND(1) - frac1;
		size_y = GFX_BYEND - (video_coord_t)y;
		hicolor = interpolate_1d(locolor, hicolor, frac1, frac0);
	}
	video_gfx_x_absgradient_v(self, (video_coord_t)x, (video_coord_t)y,
	                          size_x, size_y, locolor, hicolor);
}

INTERN ATTR_IN(1) void CC
libvideo_gfx_generic_vgradient_wrwrap(struct video_gfx const *__restrict self,
                                      video_offset_t x, video_offset_t y,
                                      video_dim_t size_x, video_dim_t size_y,
                                      video_color_t locolor, video_color_t hicolor) {
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP) {
		video_coord_t cxend;
		x = wrap(x, self->vx_hdr.vxh_cxsiz);
		if (OVERFLOW_UADD((video_coord_t)x, size_x, &cxend) || size_x >= self->vx_hdr.vxh_cxsiz) {
			x = 0;
			size_x = self->vx_hdr.vxh_cxsiz;
		} else {
			/* # of pixels that go beyond the right clip-edge */
			if (OVERFLOW_USUB(cxend, self->vx_hdr.vxh_cxsiz, &xwrap))
				xwrap = 0;
		}
	}
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP) {
		video_coord_t cyend;
		y = wrap(y, self->vx_hdr.vxh_cysiz);
		if (OVERFLOW_UADD((video_coord_t)y, size_y, &cyend) || size_y >= self->vx_hdr.vxh_cysiz) {
			y = 0;
			size_y = self->vx_hdr.vxh_cysiz;
		} else {
			/* # of pixels that go beyond the bottom clip-edge */
			if (OVERFLOW_USUB(cyend, self->vx_hdr.vxh_cysiz, &ywrap))
				ywrap = 0;
		}
	}
	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		linear_fp_blend_t yfrac0, yfrac1;
		video_color_t fixed_locolor;
		yfrac0 = (ywrap * LINEAR_FP_BLEND(1)) / size_y;
		yfrac1 = LINEAR_FP_BLEND(1) - yfrac0;
		fixed_locolor = interpolate_1d(locolor, hicolor, yfrac1, yfrac0);
		libvideo_gfx_generic_vgradient(self, 0, 0, xwrap, ywrap, fixed_locolor, hicolor);
	}
	if (xwrap) /* Must do a partial fill at the left */
		libvideo_gfx_generic_vgradient(self, 0, y, xwrap, size_y, locolor, hicolor);
	if (ywrap) { /* Must do a partial fill at the top */
		linear_fp_blend_t yfrac0, yfrac1;
		video_color_t fixed_locolor;
		yfrac0 = (ywrap * LINEAR_FP_BLEND(1)) / size_y;
		yfrac1 = LINEAR_FP_BLEND(1) - yfrac0;
		fixed_locolor = interpolate_1d(locolor, hicolor, yfrac1, yfrac0);
		libvideo_gfx_generic_vgradient(self, x, 0, size_x, ywrap, fixed_locolor, hicolor);
	}
	libvideo_gfx_generic_vgradient(self, x, y, size_x, size_y, locolor, hicolor);
}






/************************************************************************/
/* BIT-MASKED FILL                                                      */
/************************************************************************/

INTERN ATTR_IN(1) ATTR_IN(7) void CC
libvideo_gfx_generic_bitfill(struct video_gfx const *__restrict self,
                             video_offset_t dst_x, video_offset_t dst_y,
                             video_dim_t size_x, video_dim_t size_y,
                             video_color_t color,
                             struct video_bitmask const *__restrict bm) {
	struct video_bitmask fixed_bm;
	video_coord_t temp;
	if (!size_x || !size_y)
		return;
	dst_x += self->vx_hdr.vxh_cxoff;
	dst_y += self->vx_hdr.vxh_cyoff;
	if unlikely(dst_x < (video_offset_t)GFX_BXMIN) {
		dst_x = (video_offset_t)(GFX_BXMIN - (video_coord_t)dst_x);
		if unlikely((video_coord_t)dst_x >= size_x)
			return;
		fixed_bm = *bm;
		bm = &fixed_bm;
		fixed_bm.vbm_skip += (video_coord_t)dst_x;
		size_x -= (video_coord_t)dst_x;
		dst_x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(dst_y < (video_offset_t)GFX_BYMIN) {
		dst_y = (video_offset_t)(GFX_BYMIN - (video_coord_t)dst_y);
		if unlikely((video_coord_t)dst_y >= size_y)
			return;
		fixed_bm = *bm;
		bm = &fixed_bm;
		fixed_bm.vbm_skip += ((video_coord_t)dst_y) * fixed_bm.vbm_scan;
		size_y -= (video_coord_t)dst_y;
		dst_y = (video_offset_t)GFX_BYMIN;
	}
	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, size_x, &temp) || temp > GFX_BXEND) {
		if unlikely((video_coord_t)dst_x >= GFX_BXEND)
			return;
		size_x = GFX_BXEND - (video_coord_t)dst_x;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, size_y, &temp) || temp > GFX_BYEND) {
		if unlikely((video_coord_t)dst_y >= GFX_BYEND)
			return;
		size_y = GFX_BYEND - (video_coord_t)dst_y;
	}
	video_gfx_x_bitfill(self,
	                    (video_coord_t)dst_x,
	                    (video_coord_t)dst_y,
	                    size_x, size_y, color, bm);
}

INTERN ATTR_IN(1) ATTR_IN(7) void CC
libvideo_gfx_generic_bitfill_wrwrap(struct video_gfx const *__restrict self,
                                    video_offset_t dst_x, video_offset_t dst_y,
                                    video_dim_t size_x, video_dim_t size_y,
                                    video_color_t color,
                                    struct video_bitmask const *__restrict bm) {
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = size_x;
	video_dim_t yinb = size_y;
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP) {
		video_coord_t cxend;
		dst_x = wrap(dst_x, self->vx_hdr.vxh_cxsiz);
		if (size_x > self->vx_hdr.vxh_cxsiz)
			size_x = self->vx_hdr.vxh_cxsiz;
		cxend = (video_coord_t)dst_x + size_x;
		if (OVERFLOW_USUB(cxend, self->vx_hdr.vxh_cxsiz, &xwrap)) {
			xwrap = 0;
		} else {
			xinb = self->vx_hdr.vxh_cxsiz - (video_coord_t)dst_x;
		}
	}
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP) {
		video_coord_t cyend;
		dst_y = wrap(dst_y, self->vx_hdr.vxh_cysiz);
		if (size_y > self->vx_hdr.vxh_cysiz)
			size_y = self->vx_hdr.vxh_cysiz;
		cyend = (video_coord_t)dst_y + size_y;
		if (OVERFLOW_USUB(cyend, self->vx_hdr.vxh_cysiz, &ywrap)) {
			ywrap = 0;
		} else {
			yinb = self->vx_hdr.vxh_cysiz - (video_coord_t)dst_y;
		}
	}
	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		struct video_bitmask chunk_bm = *bm;
		chunk_bm.vbm_skip += xinb + (yinb * chunk_bm.vbm_scan);
		libvideo_gfx_generic_bitfill(self, 0, 0, xwrap, ywrap, color, &chunk_bm);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		struct video_bitmask chunk_bm = *bm;
		chunk_bm.vbm_skip += xinb;
		libvideo_gfx_generic_bitfill(self, 0, dst_y, xwrap, size_y, color, &chunk_bm);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		struct video_bitmask chunk_bm = *bm;
		chunk_bm.vbm_skip += yinb * chunk_bm.vbm_scan;
		libvideo_gfx_generic_bitfill(self, dst_x, 0, size_x, ywrap, color, &chunk_bm);
	}
	libvideo_gfx_generic_bitfill(self, dst_x, dst_y, xinb, yinb, color, bm);
}

INTERN ATTR_IN(1) ATTR_IN(9) void CC
libvideo_gfx_generic_bitstretchfill(struct video_gfx const *__restrict self,
                                    video_offset_t dst_x, video_offset_t dst_y,
                                    video_dim_t dst_size_x, video_dim_t dst_size_y,
                                    video_color_t color,
                                    video_dim_t src_size_x, video_dim_t src_size_y,
                                    struct video_bitmask const *__restrict bm) {
	struct video_bitmask fixed_bm;
	video_coord_t temp;
	if unlikely(!dst_size_x || !dst_size_y || !src_size_x || !src_size_y)
		return;
	dst_x += self->vx_hdr.vxh_cxoff;
	dst_y += self->vx_hdr.vxh_cyoff;
	if unlikely(dst_x < (video_offset_t)GFX_BXMIN) {
		video_dim_t srcpart;
		dst_x = (video_offset_t)(GFX_BXMIN - (video_coord_t)dst_x);
		if unlikely((video_coord_t)dst_x >= dst_size_x)
			return;
		srcpart = ((video_coord_t)dst_x * src_size_x) / dst_size_x;
		if unlikely(srcpart >= src_size_x)
			return;
		src_size_x -= srcpart;
		dst_size_x -= (video_coord_t)dst_x;
		fixed_bm = *bm;
		bm = &fixed_bm;
		fixed_bm.vbm_skip += srcpart;
		dst_x = (video_offset_t)GFX_BXMIN;
	}
	if unlikely(dst_y < (video_offset_t)GFX_BYMIN) {
		video_dim_t srcpart;
		dst_y = (video_offset_t)(GFX_BYMIN - (video_coord_t)dst_y);
		if unlikely((video_coord_t)dst_y >= dst_size_y)
			return;
		srcpart = ((video_coord_t)dst_y * src_size_y) / dst_size_y;
		if unlikely(srcpart >= src_size_y)
			return;
		src_size_y -= srcpart;
		dst_size_y -= (video_coord_t)dst_y;
		fixed_bm = *bm;
		bm = &fixed_bm;
		fixed_bm.vbm_skip += srcpart * fixed_bm.vbm_scan;
		dst_y = (video_offset_t)GFX_BYMIN;
	}

	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, dst_size_x, &temp) || temp > GFX_BXEND) {
		video_dim_t newdstsize, overflow;
		if unlikely((video_coord_t)dst_x >= GFX_BXEND)
			return;
		newdstsize = GFX_BXEND - (video_coord_t)dst_x;
		overflow   = dst_size_x - newdstsize;
		overflow   = (overflow * src_size_x) / dst_size_x;
		dst_size_x = newdstsize;
		if unlikely(overflow >= src_size_x)
			return;
		src_size_x -= overflow;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, dst_size_y, &temp) || temp > GFX_BYEND) {
		video_dim_t newdstsize, overflow;
		if unlikely((video_coord_t)dst_y >= GFX_BYEND)
			return;
		newdstsize = GFX_BYEND - (video_coord_t)dst_y;
		overflow   = dst_size_y - newdstsize;
		overflow   = (overflow * src_size_y) / dst_size_y;
		dst_size_y = newdstsize;
		if unlikely(overflow >= src_size_y)
			return;
		src_size_y -= overflow;
	}
	if (dst_size_x == src_size_x && dst_size_y == src_size_y) {
		/* Can use copy-blit */
		video_gfx_x_bitfill(self, (video_coord_t)dst_x, (video_coord_t)dst_y,
		                    dst_size_x, dst_size_y, color, bm);
	} else {
		/* Must use stretch-blit */
		video_gfx_x_bitstretchfill(self, (video_coord_t)dst_x, (video_coord_t)dst_y,
		                           dst_size_x, dst_size_y, color,
		                           src_size_x, src_size_y, bm);
	}
}

INTERN ATTR_IN(1) ATTR_IN(9) void CC
libvideo_gfx_generic_bitstretchfill_wrwrap(struct video_gfx const *__restrict self,
                                           video_offset_t dst_x, video_offset_t dst_y,
                                           video_dim_t dst_size_x, video_dim_t dst_size_y,
                                           video_color_t color,
                                           video_dim_t src_size_x, video_dim_t src_size_y,
                                           struct video_bitmask const *__restrict bm) {
#define xdst2src(x) ((video_coord_t)(((uint64_t)(x) * src_size_x) / dst_size_x))
#define ydst2src(y) ((video_coord_t)(((uint64_t)(y) * src_size_y) / dst_size_y))
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = dst_size_x;
	video_dim_t yinb = dst_size_y;
	if (self->vx_flags & VIDEO_GFX_FWRXWRAP) {
		video_coord_t cxend;
		dst_x = wrap(dst_x, self->vx_hdr.vxh_cxsiz);
		if (dst_size_x > self->vx_hdr.vxh_cxsiz) {
			src_size_x = xdst2src(self->vx_hdr.vxh_cxsiz);
			dst_size_x = self->vx_hdr.vxh_cxsiz;
		}
		cxend = (video_coord_t)dst_x + dst_size_x;
		if (OVERFLOW_USUB(cxend, self->vx_hdr.vxh_cxsiz, &xwrap)) {
			xwrap = 0;
		} else {
			xinb = self->vx_hdr.vxh_cxsiz - (video_coord_t)dst_x;
		}
	}
	if (self->vx_flags & VIDEO_GFX_FWRYWRAP) {
		video_coord_t cyend;
		dst_y = wrap(dst_y, self->vx_hdr.vxh_cysiz);
		if (dst_size_y > self->vx_hdr.vxh_cysiz) {
			src_size_y = ydst2src(self->vx_hdr.vxh_cysiz);
			dst_size_y = self->vx_hdr.vxh_cysiz;
		}
		cyend = (video_coord_t)dst_y + dst_size_y;
		if (OVERFLOW_USUB(cyend, self->vx_hdr.vxh_cysiz, &ywrap)) {
			ywrap = 0;
		} else {
			yinb = self->vx_hdr.vxh_cysiz - (video_coord_t)dst_y;
		}
	}

	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		struct video_bitmask chunk_bm = *bm;
		size_t chunk_src_x = xdst2src(xinb);
		size_t chunk_src_y = ydst2src(yinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		size_t chunk_src_size_y = ydst2src(ywrap);
		chunk_bm.vbm_skip += chunk_src_x + (chunk_src_y * chunk_bm.vbm_scan);
		libvideo_gfx_generic_bitstretchfill(self, 0, 0, xwrap, ywrap, color,
		                                    chunk_src_size_x, chunk_src_size_y, &chunk_bm);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		struct video_bitmask chunk_bm = *bm;
		size_t chunk_src_x = xdst2src(xinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		chunk_bm.vbm_skip += chunk_src_x;
		libvideo_gfx_generic_bitstretchfill(self, 0, dst_y, xwrap, dst_size_y, color,
		                                    chunk_src_size_x, src_size_y, &chunk_bm);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		struct video_bitmask chunk_bm = *bm;
		size_t chunk_src_y = ydst2src(yinb);
		size_t chunk_src_size_y = ydst2src(ywrap);
		chunk_bm.vbm_skip += chunk_src_y * chunk_bm.vbm_scan;
		libvideo_gfx_generic_bitstretchfill(self, dst_x, 0, dst_size_x, ywrap, color,
		                                    src_size_x, chunk_src_size_y, &chunk_bm);
	}
	libvideo_gfx_generic_bitstretchfill(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                    color, src_size_x, src_size_y, bm);
#undef xdst2src
#undef ydst2src
}



#undef libvideo_gfx_generic_ops
#undef libvideo_gfx_generic_ops_rdwrap
#undef libvideo_gfx_generic_ops_wrwrap
#undef libvideo_gfx_generic_ops_rdwrwrap
PRIVATE struct video_gfx_ops libvideo_gfx_generic_ops = {};
PRIVATE struct video_gfx_ops libvideo_gfx_generic_ops_rdwrap = {};
PRIVATE struct video_gfx_ops libvideo_gfx_generic_ops_wrwrap = {};
PRIVATE struct video_gfx_ops libvideo_gfx_generic_ops_rdwrwrap = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops(void) {
	if unlikely(!libvideo_gfx_generic_ops.fxo_getcolor) {
		libvideo_gfx_generic_ops.fxo_vgradient      = &libvideo_gfx_generic_vgradient;
		libvideo_gfx_generic_ops.fxo_hgradient      = &libvideo_gfx_generic_hgradient;
		libvideo_gfx_generic_ops.fxo_gradient       = &libvideo_gfx_generic_gradient;
		libvideo_gfx_generic_ops.fxo_bitstretchfill = &libvideo_gfx_generic_bitstretchfill;
		libvideo_gfx_generic_ops.fxo_bitfill        = &libvideo_gfx_generic_bitfill;
		libvideo_gfx_generic_ops.fxo_rect           = &libvideo_gfx_generic_rect;
		libvideo_gfx_generic_ops.fxo_fill           = &libvideo_gfx_generic_fill;
		libvideo_gfx_generic_ops.fxo_vline          = &libvideo_gfx_generic_vline;
		libvideo_gfx_generic_ops.fxo_hline          = &libvideo_gfx_generic_hline;
		libvideo_gfx_generic_ops.fxo_line           = &libvideo_gfx_generic_line;
		libvideo_gfx_generic_ops.fxo_putcolor       = &libvideo_gfx_generic_putcolor;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_generic_ops.fxo_getcolor = &libvideo_gfx_generic_getcolor;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_gfx_generic_ops;
}
INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_rdwrap(void) {
	if unlikely(!libvideo_gfx_generic_ops_rdwrap.fxo_getcolor) {
		libvideo_gfx_generic_ops_rdwrap.fxo_vgradient      = &libvideo_gfx_generic_vgradient;
		libvideo_gfx_generic_ops_rdwrap.fxo_hgradient      = &libvideo_gfx_generic_hgradient;
		libvideo_gfx_generic_ops_rdwrap.fxo_gradient       = &libvideo_gfx_generic_gradient;
		libvideo_gfx_generic_ops_rdwrap.fxo_bitstretchfill = &libvideo_gfx_generic_bitstretchfill;
		libvideo_gfx_generic_ops_rdwrap.fxo_bitfill        = &libvideo_gfx_generic_bitfill;
		libvideo_gfx_generic_ops_rdwrap.fxo_rect           = &libvideo_gfx_generic_rect;
		libvideo_gfx_generic_ops_rdwrap.fxo_fill           = &libvideo_gfx_generic_fill;
		libvideo_gfx_generic_ops_rdwrap.fxo_vline          = &libvideo_gfx_generic_vline;
		libvideo_gfx_generic_ops_rdwrap.fxo_hline          = &libvideo_gfx_generic_hline;
		libvideo_gfx_generic_ops_rdwrap.fxo_line           = &libvideo_gfx_generic_line;
		libvideo_gfx_generic_ops_rdwrap.fxo_putcolor       = &libvideo_gfx_generic_putcolor;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_generic_ops_rdwrap.fxo_getcolor = &libvideo_gfx_generic_getcolor_rdwrap;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_gfx_generic_ops_rdwrap;
}
INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_wrwrap(void) {
	if unlikely(!libvideo_gfx_generic_ops_wrwrap.fxo_getcolor) {
		libvideo_gfx_generic_ops_wrwrap.fxo_vgradient      = &libvideo_gfx_generic_vgradient_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_hgradient      = &libvideo_gfx_generic_hgradient_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_gradient       = &libvideo_gfx_generic_gradient_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_bitstretchfill = &libvideo_gfx_generic_bitstretchfill_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_bitfill        = &libvideo_gfx_generic_bitfill_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_rect           = &libvideo_gfx_generic_rect_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_fill           = &libvideo_gfx_generic_fill_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_vline          = &libvideo_gfx_generic_vline_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_hline          = &libvideo_gfx_generic_hline_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_line           = &libvideo_gfx_generic_line_wrwrap;
		libvideo_gfx_generic_ops_wrwrap.fxo_putcolor       = &libvideo_gfx_generic_putcolor_wrwrap;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_generic_ops_wrwrap.fxo_getcolor = &libvideo_gfx_generic_getcolor;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_gfx_generic_ops_wrwrap;
}
INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops_rdwrwrap(void) {
	if unlikely(!libvideo_gfx_generic_ops_rdwrwrap.fxo_getcolor) {
		libvideo_gfx_generic_ops_rdwrwrap.fxo_vgradient      = &libvideo_gfx_generic_vgradient_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_hgradient      = &libvideo_gfx_generic_hgradient_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_gradient       = &libvideo_gfx_generic_gradient_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_bitstretchfill = &libvideo_gfx_generic_bitstretchfill_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_bitfill        = &libvideo_gfx_generic_bitfill_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_rect           = &libvideo_gfx_generic_rect_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_fill           = &libvideo_gfx_generic_fill_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_vline          = &libvideo_gfx_generic_vline_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_hline          = &libvideo_gfx_generic_hline_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_line           = &libvideo_gfx_generic_line_wrwrap;
		libvideo_gfx_generic_ops_rdwrwrap.fxo_putcolor       = &libvideo_gfx_generic_putcolor_wrwrap;
		COMPILER_WRITE_BARRIER();
		libvideo_gfx_generic_ops_rdwrwrap.fxo_getcolor = &libvideo_gfx_generic_getcolor_rdwrap;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_gfx_generic_ops_rdwrwrap;
}
#define libvideo_gfx_generic_ops          (*_libvideo_gfx_generic_ops())
#define libvideo_gfx_generic_ops_rdwrap   (*_libvideo_gfx_generic_ops_rdwrap())
#define libvideo_gfx_generic_ops_wrwrap   (*_libvideo_gfx_generic_ops_wrwrap())
#define libvideo_gfx_generic_ops_rdwrwrap (*_libvideo_gfx_generic_ops_rdwrwrap())



/************************************************************************/
/* GENERIC BLIT OPERATORS                                               */
/************************************************************************/

#undef libvideo_blit_generic_ops
#undef libvideo_blit_generic_ops_rdwrap
#undef libvideo_blit_generic_ops_wrap
PRIVATE struct video_blitter_ops libvideo_blit_generic_ops = {};
PRIVATE struct video_blitter_ops libvideo_blit_generic_ops_rdwrap = {};
PRIVATE struct video_blitter_ops libvideo_blit_generic_ops_wrap = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_blit_generic_ops(void) {
	if unlikely(!libvideo_blit_generic_ops.vbo_blit) {
		libvideo_blit_generic_ops.vbo_stretch = &libvideo_blitter_generic_stretch;
		COMPILER_WRITE_BARRIER();
		libvideo_blit_generic_ops.vbo_blit = &libvideo_blitter_generic_blit;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_blit_generic_ops;
}
INTERN ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_blit_generic_ops_rdwrap(void) {
	if unlikely(!libvideo_blit_generic_ops_rdwrap.vbo_blit) {
		libvideo_blit_generic_ops_rdwrap.vbo_stretch = &libvideo_blitter_generic_stretch_rdwrap;
		COMPILER_WRITE_BARRIER();
		libvideo_blit_generic_ops_rdwrap.vbo_blit = &libvideo_blitter_generic_blit_rdwrap;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_blit_generic_ops_rdwrap;
}
INTERN ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_blit_generic_ops_wrap(void) {
	if unlikely(!libvideo_blit_generic_ops_wrap.vbo_blit) {
		libvideo_blit_generic_ops_wrap.vbo_stretch = &libvideo_blitter_generic_stretch_wrap;
		COMPILER_WRITE_BARRIER();
		libvideo_blit_generic_ops_wrap.vbo_blit = &libvideo_blitter_generic_blit_wrap;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_blit_generic_ops_wrap;
}
#define libvideo_blit_generic_ops        (*_libvideo_blit_generic_ops())
#define libvideo_blit_generic_ops_rdwrap (*_libvideo_blit_generic_ops_rdwrap())
#define libvideo_blit_generic_ops_wrap   (*_libvideo_blit_generic_ops_wrap())

/************************************************************************/
/* CLIP()                                                               */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(video_gfxhdr_clip, libvideo_gfxhdr_clip);
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfxhdr *CC
libvideo_gfxhdr_clip(struct video_gfxhdr *__restrict self,
                     video_offset_t clip_x, video_offset_t clip_y,
                     video_dim_t size_x, video_dim_t size_y) {
	video_offset_t cxend, cyend;
	if unlikely(!size_x || !size_y)
		goto empty_clip;

	/* Adjust clip rect */
	self->vxh_cxoff += clip_x;
	self->vxh_cyoff += clip_y;
	self->vxh_cxsiz = size_x;
	self->vxh_cysiz = size_y;

	/* Clamp buffer rect according to new clip rect */
	if ((video_offset_t)self->vxh_bxmin < self->vxh_cxoff) {
		self->vxh_bxmin = (video_coord_t)self->vxh_cxoff;
		if (self->vxh_bxend <= self->vxh_bxmin)
			goto empty_clip;
//		self->vxh_bxsiz = self->vxh_bxend - self->vxh_bxmin;
	}
	if ((video_offset_t)self->vxh_bymin < self->vxh_cyoff) {
		self->vxh_bymin = (video_coord_t)self->vxh_cyoff;
		if (self->vxh_byend <= self->vxh_bymin)
			goto empty_clip;
//		self->vxh_bysiz = self->vxh_byend - self->vxh_bymin;
	}

	if (!OVERFLOW_SADD(self->vxh_cxoff, size_x, &cxend) &&
	    self->vxh_bxend > (video_coord_t)cxend && cxend > 0) {
		self->vxh_bxend = (video_coord_t)cxend;
		if (self->vxh_bxend <= self->vxh_bxmin)
			goto empty_clip;
//		self->vxh_bxsiz = self->vxh_bxend - self->vxh_bxmin;
	}
	if (!OVERFLOW_SADD(self->vxh_cyoff, size_y, &cyend) &&
	    self->vxh_byend > (video_coord_t)cyend && cyend > 0) {
		self->vxh_byend = (video_coord_t)cyend;
		if (self->vxh_byend <= self->vxh_bymin)
			goto empty_clip;
//		self->vxh_bysiz = self->vxh_byend - self->vxh_bymin;
	}
	return self;
empty_clip:
	video_gfxhdr_setempty(self);
	return self;
}

DECL_END

#ifndef __INTELLISENSE__
#include "gfx/hl_blit.c.inl"
#include "gfx/ll_noblend.c.inl"
/**/

#define DEFINE_libvideo_gfx__blitfrom_n
#include "gfx/hl_blitfrom.c.inl"
#define DEFINE_libvideo_gfx__blitfrom_l
#include "gfx/hl_blitfrom.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBVIDEO_GFX_GFX_C */
