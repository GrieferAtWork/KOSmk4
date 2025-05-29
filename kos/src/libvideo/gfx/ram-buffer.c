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
#ifndef GUARD_LIBVIDEO_GFX_RAM_BUFFER_C
#define GUARD_LIBVIDEO_GFX_RAM_BUFFER_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <sys/mman.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>

#include "buffer.h"
#include "gfx-empty.h"
#include "gfx.h"
#include "ram-buffer.h"

/* libstdc++ #undef's min/max (ugh... I'll really have to replace
 * that  library  with  my  own  version  of  it  at  one point).
 * But we want  them as  macros, so  include this  at the  end... */
#include <minmax.h>

DECL_BEGIN

#define PRIdOFF PRIdN(__SIZEOF_VIDEO_OFFSET_T__)
#define PRIxOFF PRIxN(__SIZEOF_VIDEO_OFFSET_T__)
#define PRIuCRD PRIuN(__SIZEOF_VIDEO_COORD_T__)
#define PRIxCRD PRIxN(__SIZEOF_VIDEO_COORD_T__)
#define PRIuDIM PRIuN(__SIZEOF_VIDEO_DIM_T__)
#define PRIxDIM PRIxN(__SIZEOF_VIDEO_DIM_T__)


#define RAMGFX_DATA   (byte_t *)self->vx_driver[VIDEO_BUFFER_RAMGFX_DATA]
#define RAMGFX_STRIDE (size_t)self->vx_driver[VIDEO_BUFFER_RAMGFX_STRIDE]

#if !defined(NDEBUG) && 1
#define ASSERT_ABS_COORDS(self, x, y)                   \
	(assertf((x) >= (self)->vx_xmin &&                  \
	         (x) < (self)->vx_xend,                     \
	         "x       = %" PRIuCRD " (%#" PRIxCRD ")\n" \
	         "vx_xmin = %" PRIuCRD " (%#" PRIxCRD ")\n" \
	         "vx_xend = %" PRIuCRD " (%#" PRIxCRD ")",  \
	         (x), (x),                                  \
	         (self)->vx_xmin, (self)->vx_xmin,          \
	         (self)->vx_xend, (self)->vx_xend),         \
	 assertf((y) >= (self)->vx_ymin &&                  \
	         (y) < (self)->vx_yend,                     \
	         "y       = %" PRIuCRD " (%#" PRIxCRD ")\n" \
	         "vx_ymin = %" PRIuCRD " (%#" PRIxCRD ")\n" \
	         "vx_yend = %" PRIuCRD " (%#" PRIxCRD ")",  \
	         (y), (y),                                  \
	         (self)->vx_ymin, (self)->vx_ymin,          \
	         (self)->vx_yend, (self)->vx_yend))
#else /* !NDEBUG */
#define ASSERT_ABS_COORDS(self, x, y) (void)0
#endif /* NDEBUG */


/* GFX functions for memory-based video buffers (without GPU support) */
INTERN NONNULL((1)) video_color_t CC
libvideo_gfx_ramgfx_getcolor(struct video_gfx const *__restrict self,
                             video_coord_t x, video_coord_t y) {
	byte_t *line;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	return self->vx_buffer->vb_format.getcolor(line, x);
}

INTERN NONNULL((1)) video_color_t CC
libvideo_gfx_ramgfx_getcolor_blur(struct video_gfx const *__restrict self,
                                  video_coord_t x, video_coord_t y) {
	byte_t *line;
	video_color_t result;
	video_color_t colors[8];
	uint32_t r, g, b, a;
	unsigned int i, color_count;
#define MODE_XMIN 0x1
#define MODE_XMAX 0x2
#define MODE_YMIN 0x4
#define MODE_YMAX 0x8
	uint8_t mode = 0x0;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	/* Figure out how we're situated in relation to bounds. */
	if unlikely(x == self->vx_xmin)
		mode |= MODE_XMIN;
	if unlikely(y == self->vx_ymin)
		mode |= MODE_YMIN;
	if unlikely(x == self->vx_xend - 1)
		mode |= MODE_XMAX;
	if unlikely(y == self->vx_yend - 1)
		mode |= MODE_YMAX;
	/* Load colors as needed. */
	switch (__builtin_expect(mode, 0x0)) {
#define GETCOLOR(xoff, yoff) \
		self->vx_buffer->vb_format.getcolor(line + (RAMGFX_STRIDE * (yoff)), x + (xoff))

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
	result = self->vx_buffer->vb_format.getcolor(line, x);
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
	result = VIDEO_COLOR_RGBA((uint8_t)r,
	                          (uint8_t)g,
	                          (uint8_t)b,
	                          (uint8_t)a);
	return result;
}

INTERN NONNULL((1)) video_color_t CC
libvideo_gfx_ramgfx_getcolor_with_key(struct video_gfx const *__restrict self,
                                      video_coord_t x, video_coord_t y) {
	byte_t *line;
	video_color_t result;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	result = self->vx_buffer->vb_format.getcolor(line, x);
	if (result == self->vx_colorkey)
		result = 0;
	return result;
}


#if 0 /*< Define as 1 to have the blender round upwards. */
#define div256(x) ((x)+0xfe)/0xff
#else
#define div256(x) (x)/0xff
#endif

#define blend_zero(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                                       /* lhs* */ 0
#define blend_one(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                                           lhs
#define blend_src_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                div256((uint32_t)lhs * csrc)
#define blend_one_minus_src_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)      div256((uint32_t)lhs * (0xff - csrc))
#define blend_dst_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                div256((uint32_t)lhs * cdst)
#define blend_one_minus_dst_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)      div256((uint32_t)lhs * (0xff - cdst))
#define blend_src_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                div256((uint32_t)lhs * asrc)
#define blend_one_minus_src_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)      div256((uint32_t)lhs * (0xff - asrc))
#define blend_dst_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)                div256((uint32_t)lhs * adst)
#define blend_one_minus_dst_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)      div256((uint32_t)lhs * (0xff - adst))
#define blend_src_alpha_saturate(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)       div256((uint32_t)lhs * min(asrc, 0xff - adst))
#define blend_constant_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)           div256((uint32_t)lhs * cc)
#define blend_one_minus_constant_color(lhs, rhs, csrc, cdst, asrc, adst, cc, ac) div256((uint32_t)lhs * (0xff - cc))
#define blend_constant_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac)           div256((uint32_t)lhs * ac)
#define blend_one_minus_constant_alpha(lhs, rhs, csrc, cdst, asrc, adst, cc, ac) div256((uint32_t)lhs * (0xff - ac))

#define BLEND_SWITCH(kind, callback)                                                                  \
	do {                                                                                              \
		switch (kind) {                                                                               \
		case GFX_BLENDMODE_ONE:                      callback(blend_one); break;                      \
		case GFX_BLENDMODE_SRC_COLOR:                callback(blend_src_color); break;                \
		case GFX_BLENDMODE_ONE_MINUS_SRC_COLOR:      callback(blend_one_minus_src_color); break;      \
		case GFX_BLENDMODE_DST_COLOR:                callback(blend_dst_color); break;                \
		case GFX_BLENDMODE_ONE_MINUS_DST_COLOR:      callback(blend_one_minus_dst_color); break;      \
		case GFX_BLENDMODE_SRC_ALPHA:                callback(blend_src_alpha); break;                \
		case GFX_BLENDMODE_ONE_MINUS_SRC_ALPHA:      callback(blend_one_minus_src_alpha); break;      \
		case GFX_BLENDMODE_DST_ALPHA:                callback(blend_dst_alpha); break;                \
		case GFX_BLENDMODE_ONE_MINUS_DST_ALPHA:      callback(blend_one_minus_dst_alpha); break;      \
		case GFX_BLENDMODE_SRC_ALPHA_SATURATE:       callback(blend_src_alpha_saturate); break;       \
		case GFX_BLENDMODE_CONSTANT_COLOR:           callback(blend_constant_color); break;           \
		case GFX_BLENDMODE_ONE_MINUS_CONSTANT_COLOR: callback(blend_one_minus_constant_color); break; \
		case GFX_BLENDMODE_CONSTANT_ALPHA:           callback(blend_constant_alpha); break;           \
		case GFX_BLENDMODE_ONE_MINUS_CONSTANT_ALPHA: callback(blend_one_minus_constant_alpha); break; \
		default:                                     callback(blend_zero); break;                     \
		}                                                                                             \
	}	__WHILE0

#define func_add(a,b)              a + b
#define func_subtract(a,b)         a - b
#define func_reverse_subtract(a,b) b - a
#define FUNC_SWITCH(kind, callback)                                                  \
	do {                                                                             \
		switch (kind) {                                                              \
		case GFX_BLENDFUNC_SUBTRACT:         callback(func_subtract); break;         \
		case GFX_BLENDFUNC_REVERSE_SUBTRACT: callback(func_reverse_subtract); break; \
		case GFX_BLENDFUNC_MIN:              callback(min); break;                   \
		case GFX_BLENDFUNC_MAX:              callback(max); break;                   \
		default:                             callback(func_add); break;              \
		}                                                                            \
	}	__WHILE0


LOCAL ATTR_CONST WUNUSED video_color_t CC
blend_color(video_color_t dst, video_color_t src, gfx_blendmode_t mode) {
	uint8_t new_lhs_r, new_lhs_g, new_lhs_b, new_lhs_a;
	uint8_t new_rhs_r, new_rhs_g, new_rhs_b, new_rhs_a;
	uint8_t dst_r, dst_g, dst_b, dst_a;
	uint8_t src_r, src_g, src_b, src_a;
	dst_r = VIDEO_COLOR_GET_RED(dst);
	dst_g = VIDEO_COLOR_GET_GREEN(dst);
	dst_b = VIDEO_COLOR_GET_BLUE(dst);
	dst_a = VIDEO_COLOR_GET_ALPHA(dst);
	src_r = VIDEO_COLOR_GET_RED(src);
	src_g = VIDEO_COLOR_GET_GREEN(src);
	src_b = VIDEO_COLOR_GET_BLUE(src);
	src_a = VIDEO_COLOR_GET_ALPHA(src);
#define blend_rgb_src(fun)                                                                                                            \
	{                                                                                                                                 \
		new_lhs_r = (uint8_t)(fun(src_r, dst_r, src_r, dst_r, src_a, dst_a, GFX_BLENDINFO_GET_CR(mode), GFX_BLENDINFO_GET_CA(mode))); \
		new_lhs_g = (uint8_t)(fun(src_g, dst_g, src_g, dst_g, src_a, dst_a, GFX_BLENDINFO_GET_CG(mode), GFX_BLENDINFO_GET_CA(mode))); \
		new_lhs_b = (uint8_t)(fun(src_b, dst_b, src_b, dst_b, src_a, dst_a, GFX_BLENDINFO_GET_CB(mode), GFX_BLENDINFO_GET_CA(mode))); \
	}
#define blend_a_src(fun)                                                                                                              \
	{                                                                                                                                 \
		new_lhs_a = (uint8_t)(fun(src_a, dst_a, src_a, dst_a, src_a, dst_a, GFX_BLENDINFO_GET_CA(mode), GFX_BLENDINFO_GET_CA(mode))); \
	}
#define blend_rgb_dst(fun)                                                                                                            \
	{                                                                                                                                 \
		new_rhs_r = (uint8_t)(fun(dst_r, src_r, src_r, dst_r, src_a, dst_a, GFX_BLENDINFO_GET_CR(mode), GFX_BLENDINFO_GET_CA(mode))); \
		new_rhs_g = (uint8_t)(fun(dst_g, src_g, src_g, dst_g, src_a, dst_a, GFX_BLENDINFO_GET_CG(mode), GFX_BLENDINFO_GET_CA(mode))); \
		new_rhs_b = (uint8_t)(fun(dst_b, src_b, src_b, dst_b, src_a, dst_a, GFX_BLENDINFO_GET_CB(mode), GFX_BLENDINFO_GET_CA(mode))); \
	}
#define blend_a_dst(fun)                                                                                                              \
	{                                                                                                                                 \
		new_rhs_a = (uint8_t)(fun(dst_a, src_a, src_a, dst_a, src_a, dst_a, GFX_BLENDINFO_GET_CA(mode), GFX_BLENDINFO_GET_CA(mode))); \
	}
	BLEND_SWITCH(GFX_BLENDINFO_GET_SRCRGB(mode), blend_rgb_src);
	BLEND_SWITCH(GFX_BLENDINFO_GET_SRCA(mode), blend_a_src);
	BLEND_SWITCH(GFX_BLENDINFO_GET_DSTRGB(mode), blend_rgb_dst);
	BLEND_SWITCH(GFX_BLENDINFO_GET_DSTA(mode), blend_a_dst);
#undef blend_a_dst
#undef blend_rgb_dst
#undef blend_a_src
#undef blend_rgb_src
#define func_rgb(fun)                                 \
	{                                                 \
		dst_r = (uint8_t)(fun(new_lhs_r, new_rhs_r)); \
		dst_g = (uint8_t)(fun(new_lhs_g, new_rhs_g)); \
		dst_b = (uint8_t)(fun(new_lhs_b, new_rhs_b)); \
	}
#define func_a(fun)                                   \
	{                                                 \
		dst_a = (uint8_t)(fun(new_lhs_a, new_rhs_a)); \
	}
	FUNC_SWITCH(GFX_BLENDINFO_GET_FUNRGB(mode), func_rgb);
	FUNC_SWITCH(GFX_BLENDINFO_GET_FUNA(mode), func_a);
#undef func_a
#undef func_rgb
	return VIDEO_COLOR_RGBA(dst_r, dst_g, dst_b, dst_a);
}


INTERN NONNULL((1)) void CC
libvideo_gfx_ramgfx_putcolor(struct video_gfx *__restrict self,
                             video_coord_t x, video_coord_t y,
                             video_color_t color) {
	byte_t *line;
	struct video_buffer *buffer;
	video_color_t o, n;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	buffer = self->vx_buffer;
	/* Perform full color blending. */
	o = buffer->vb_format.getcolor(line, x);
	n = blend_color(o, color, self->vx_blend);
	buffer->vb_format.setcolor(line, x, n);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_ramgfx_putcolor_noblend(struct video_gfx *__restrict self,
                                     video_coord_t x, video_coord_t y,
                                     video_color_t color) {
	byte_t *line;
	struct video_buffer *buffer;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	buffer = self->vx_buffer;
	buffer->vb_format.setcolor(line, x, color);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_ramgfx_putcolor_alphablend(struct video_gfx *__restrict self,
                                        video_coord_t x, video_coord_t y,
                                        video_color_t color) {
	byte_t *line;
	struct video_buffer *buffer;
	video_color_t o, n;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	buffer = self->vx_buffer;
	o = buffer->vb_format.getcolor(line, x);
	n = blend_color(o, color, GFX_BLENDINFO_ALPHA);
	buffer->vb_format.setcolor(line, x, n);
}




PRIVATE struct video_buffer_ops rambuffer_ops = {};

INTERN NONNULL((1)) void CC
rambuffer_destroy(struct video_buffer *__restrict self) {
	struct video_rambuffer *me;
	me = (struct video_rambuffer *)self;
	assert(me->vb_ops == &rambuffer_ops);
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
	free(me->vb_data);
	free(me);
}

INTERN NONNULL((1, 2)) int CC
rambuffer_lock(struct video_buffer *__restrict self,
               struct video_lock *__restrict result) {
	struct video_rambuffer *me;
	me = (struct video_rambuffer *)self;
	result->vl_stride = me->vb_stride;
	result->vl_size   = me->vb_total;
	result->vl_data   = me->vb_data;
	return 0;
}

INTERN NONNULL((1, 2)) void
NOTHROW(CC rambuffer_unlock)(struct video_buffer *__restrict self,
                             struct video_lock *__restrict lock) {
#ifndef NDEBUG
	struct video_rambuffer *me;
	me = (struct video_rambuffer *)self;
	assert(lock->vl_stride == me->vb_stride);
	assert(lock->vl_size == me->vb_total);
	assert(lock->vl_data == me->vb_data);
#endif /* !NDEBUG */
	(void)self;
	(void)lock;
}

LOCAL ATTR_CONST WUNUSED bool CC
is_add_or_subtract_or_max(unsigned int func) {
	return func == GFX_BLENDFUNC_ADD ||
	       func == GFX_BLENDFUNC_SUBTRACT ||
	       func == GFX_BLENDFUNC_MAX;
}


INTERN ATTR_RETNONNULL NONNULL((1, 2)) struct video_gfx *CC
rambuffer_getgfx(struct video_buffer *__restrict self,
                 struct video_gfx *__restrict result,
                 gfx_blendmode_t blendmode, uintptr_t flags,
                 video_color_t colorkey) {
	struct video_rambuffer *me;
	me = (struct video_rambuffer *)self;

	result->vx_buffer   = self;
	result->vx_blend    = blendmode;
	result->vx_flags    = flags;
	result->vx_colorkey = colorkey;
	result->vx_driver[VIDEO_BUFFER_RAMGFX_DATA]   = me->vb_data;
	result->vx_driver[VIDEO_BUFFER_RAMGFX_STRIDE] = (void *)(uintptr_t)me->vb_stride;
	result->vx_offt_x = 0;
	result->vx_offt_y = 0;
	result->vx_xmin   = 0;
	result->vx_ymin   = 0;
	result->vx_xend   = self->vb_size_x;
	result->vx_yend   = self->vb_size_y;

	/* Select how pixels should be read. */
	if (flags & VIDEO_GFX_FBLUR) {
		result->vx_xops.vgxo_getcolor = &libvideo_gfx_ramgfx_getcolor_blur;
	} else if ((colorkey & VIDEO_COLOR_ALPHA_MASK) != 0) {
		result->vx_xops.vgxo_getcolor = &libvideo_gfx_ramgfx_getcolor_with_key;
	} else {
		result->vx_xops.vgxo_getcolor = &libvideo_gfx_ramgfx_getcolor;
	}

	/* Detect special blend modes. */
	if (blendmode == GFX_BLENDINFO_OVERRIDE) {
		result->vx_xops.vgxo_putcolor = &libvideo_gfx_ramgfx_putcolor_noblend;
	} else if (blendmode == GFX_BLENDINFO_ALPHA) {
		result->vx_xops.vgxo_putcolor = &libvideo_gfx_ramgfx_putcolor_alphablend;
	} else if (GFX_BLENDINFO_GET_SRCRGB(blendmode) == GFX_BLENDMODE_ONE &&
	           GFX_BLENDINFO_GET_SRCA(blendmode) == GFX_BLENDMODE_ONE &&
	           GFX_BLENDINFO_GET_DSTRGB(blendmode) == GFX_BLENDMODE_ZERO &&
	           GFX_BLENDINFO_GET_DSTA(blendmode) == GFX_BLENDMODE_ZERO &&
	           is_add_or_subtract_or_max(GFX_BLENDINFO_GET_FUNRGB(blendmode)) &&
	           is_add_or_subtract_or_max(GFX_BLENDINFO_GET_FUNA(blendmode))) {
		result->vx_xops.vgxo_putcolor = &libvideo_gfx_ramgfx_putcolor_noblend;
	} else {
		result->vx_xops.vgxo_putcolor = &libvideo_gfx_ramgfx_putcolor;
	}

	/* Select optimal operator implementations based on requested features. */
	if (result->vx_xops.vgxo_putcolor == &libvideo_gfx_ramgfx_putcolor_noblend) {
		result->vx_xops.vgxo_absline_llhh = &libvideo_gfx_noblend__absline_llhh;
		result->vx_xops.vgxo_absline_lhhl = &libvideo_gfx_noblend__absline_lhhl;
		result->vx_xops.vgxo_absline_h    = &libvideo_gfx_noblend__absline_h;
		result->vx_xops.vgxo_absline_v    = &libvideo_gfx_noblend__absline_v;
		result->vx_xops.vgxo_absfill      = &libvideo_gfx_noblend__absfill;
		result->vx_xops.vgxo_bitfill      = &libvideo_gfx_noblend__bitfill;
		if (flags & VIDEO_GFX_FLINEARBLIT) {
			result->vx_xops.vgxo_blitfrom       = &libvideo_gfx_noblend__blitfrom_l;
			result->vx_xops.vgxo_bitstretchfill = &libvideo_gfx_noblend__bitstretchfill_l;
		} else {
			result->vx_xops.vgxo_blitfrom       = &libvideo_gfx_noblend__blitfrom_n;
			result->vx_xops.vgxo_bitstretchfill = &libvideo_gfx_noblend__bitstretchfill_n;
		}
	} else {
		result->vx_xops.vgxo_absline_llhh = &libvideo_gfx_generic__absline_llhh;
		result->vx_xops.vgxo_absline_lhhl = &libvideo_gfx_generic__absline_lhhl;
		result->vx_xops.vgxo_absline_h    = &libvideo_gfx_generic__absline_h;
		result->vx_xops.vgxo_absline_v    = &libvideo_gfx_generic__absline_v;
		result->vx_xops.vgxo_absfill      = &libvideo_gfx_generic__absfill;
		result->vx_xops.vgxo_bitfill      = &libvideo_gfx_generic__bitfill;
		if (flags & VIDEO_GFX_FLINEARBLIT) {
			result->vx_xops.vgxo_blitfrom       = &libvideo_gfx_generic__blitfrom_l;
			result->vx_xops.vgxo_bitstretchfill = &libvideo_gfx_generic__bitstretchfill_l;
		} else {
			result->vx_xops.vgxo_blitfrom       = &libvideo_gfx_generic__blitfrom_n;
			result->vx_xops.vgxo_bitstretchfill = &libvideo_gfx_generic__bitstretchfill_n;
		}
	}
	if (flags & VIDEO_GFX_FAALINES) {
		result->vx_xops.vgxo_absline_llhh = &libvideo_gfx_generic__absline_llhh_aa;
		result->vx_xops.vgxo_absline_lhhl = &libvideo_gfx_generic__absline_lhhl_aa;
	}
	result->vx_ops = &libvideo_gfx_generic_ops;
	return result;
}

INTERN ATTR_RETNONNULL NONNULL((1)) struct video_gfx *CC
rambuffer_noblend(struct video_gfx *__restrict self) {
	self->vx_flags &= ~(VIDEO_GFX_FBLUR);
	self->vx_colorkey = 0;
	self->vx_xops.vgxo_getcolor = &libvideo_gfx_ramgfx_getcolor;
	self->vx_xops.vgxo_putcolor = &libvideo_gfx_ramgfx_putcolor_noblend;
	if (self->vx_flags & VIDEO_GFX_FAALINES) {
		self->vx_xops.vgxo_absline_llhh = &libvideo_gfx_generic__absline_llhh_aa;
		self->vx_xops.vgxo_absline_lhhl = &libvideo_gfx_generic__absline_lhhl_aa;
	} else {
		self->vx_xops.vgxo_absline_llhh = &libvideo_gfx_noblend__absline_llhh;
		self->vx_xops.vgxo_absline_lhhl = &libvideo_gfx_noblend__absline_lhhl;
	}
	self->vx_xops.vgxo_absline_h = &libvideo_gfx_noblend__absline_h;
	self->vx_xops.vgxo_absline_v = &libvideo_gfx_noblend__absline_v;
	self->vx_xops.vgxo_absfill   = &libvideo_gfx_noblend__absfill;
	self->vx_xops.vgxo_bitfill   = &libvideo_gfx_noblend__bitfill;
	if (self->vx_flags & VIDEO_GFX_FLINEARBLIT) {
		self->vx_xops.vgxo_blitfrom       = &libvideo_gfx_noblend__blitfrom_l;
		self->vx_xops.vgxo_bitstretchfill = &libvideo_gfx_noblend__bitstretchfill_l;
	} else {
		self->vx_xops.vgxo_blitfrom       = &libvideo_gfx_noblend__blitfrom_n;
		self->vx_xops.vgxo_bitstretchfill = &libvideo_gfx_noblend__bitstretchfill_n;
	}
	return self;
}




INTERN ATTR_RETNONNULL WUNUSED
struct video_buffer_ops *CC rambuffer_getops(void) {
	if unlikely(!rambuffer_ops.vi_destroy) {
		rambuffer_ops.vi_rlock       = &rambuffer_lock;
		rambuffer_ops.vi_wlock       = &rambuffer_lock;
		rambuffer_ops.vi_unlock      = &rambuffer_unlock;
		rambuffer_ops.vi_getgfx      = &rambuffer_getgfx;
		rambuffer_ops.vi_gfx_noblend = &rambuffer_noblend;
		COMPILER_WRITE_BARRIER();
		rambuffer_ops.vi_destroy = &rambuffer_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &rambuffer_ops;
}



/* Create a new RAM-based video buffer */
INTERN WUNUSED NONNULL((3)) REF struct video_buffer *CC
libvideo_rambuffer_create(video_dim_t size_x, video_dim_t size_y,
                          struct video_codec const *__restrict codec,
                          struct video_palette *palette) {
	REF struct video_rambuffer *result;
	struct video_rambuffer_requirements req;
	assert(codec);

	/* Figure out buffer requirements. */
	(*codec->vc_rambuffer_requirements)(size_x, size_y, &req);

	/* Allocate heap memory for the buffer */
	result = (REF struct video_rambuffer *)malloc(sizeof(struct video_rambuffer));
	if unlikely(!result)
		goto err;
	result->vb_data = (byte_t *)calloc(1, req.vbs_bufsize);
	if unlikely(!result->vb_data)
		goto err_result;
	result->vb_stride          = req.vbs_stride;
	result->vb_total           = req.vbs_bufsize;
	result->vb_refcnt          = 1;
	result->vb_ops             = rambuffer_getops();
	result->vb_format.vf_codec = codec;
	result->vb_format.vf_pal   = palette;
	result->vb_size_x          = size_x;
	result->vb_size_y          = size_y;
	if (palette)
		video_palette_incref(palette);
	return result;
err_result:
	free(result);
err:
	return NULL;
}



struct video_membuffer: video_rambuffer {
	void (CC *vm_release_mem)(void *cookie, void *mem);
	void     *vm_release_mem_cookie;
};

PRIVATE struct video_buffer_ops membuffer_ops = {};

PRIVATE NONNULL((1)) void CC
membuffer_destroy(struct video_buffer *__restrict self) {
	struct video_membuffer *me = (struct video_membuffer *)self;
	assert(me->vb_ops == &membuffer_ops);
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
	if (me->vm_release_mem)
		(*me->vm_release_mem)(me->vm_release_mem_cookie, me->vb_data);
	free(me);
}


PRIVATE ATTR_RETNONNULL WUNUSED
struct video_buffer_ops *CC membuffer_getops(void) {
	if unlikely(!membuffer_ops.vi_destroy) {
		membuffer_ops.vi_rlock       = &rambuffer_lock;
		membuffer_ops.vi_wlock       = &rambuffer_lock;
		membuffer_ops.vi_unlock      = &rambuffer_unlock;
		membuffer_ops.vi_getgfx      = &rambuffer_getgfx;
		membuffer_ops.vi_gfx_noblend = &rambuffer_noblend;
		COMPILER_WRITE_BARRIER();
		membuffer_ops.vi_destroy = &membuffer_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &membuffer_ops;
}



/* Create a video buffer that interfaces with a pre-existing buffer whose
 * base address is located at `mem' (which consists of  `stride * size_y'
 * bytes). When  non-NULL,  `(*release_mem)(release_mem_cookie, mem)'  is
 * called when the final reference for the returned buffer is dropped.
 *
 * This function can be used to wrap a memory-resident graphics buffer
 * in-place,    without   needing   to    copy   it   anywhere   else.
 * @param: mem:     Base address  of  the  pre-loaded  memory  buffer.
 *                  If this location isn't writable, attempts to write
 *                  pixel  data of the  returned buffer will SEGFAULT.
 * @param: size_x:  Width of returned buffer
 * @param: size_y:  Height of returned buffer
 * @param: stride:  Scanline width in `mem'
 * @param: codec:   The video codec that describes how `mem' is encoded.
 * @param: palette: The palette to use (only needed if used by `codec')
 * @param: release_mem: Optional callback invoked when the returned buffer is destroyed
 * @param: release_mem_cookie: Cookie argument for `release_mem'
 * @return: * :   The newly created video buffer
 * @return: NULL: Error (s.a. `errno') */
DEFINE_PUBLIC_ALIAS(video_buffer_formem, libvideo_buffer_formem);
INTERN WUNUSED NONNULL((5)) REF struct video_buffer *CC
libvideo_buffer_formem(void *mem, video_dim_t size_x, video_dim_t size_y, size_t stride,
                       struct video_codec const *codec, struct video_palette *palette,
                       void (CC *release_mem)(void *cookie, void *mem),
                       void *release_mem_cookie) {
	REF struct video_membuffer *result;
	struct video_rambuffer_requirements req;
	assert(codec);

	/* Ensure that the specified stride is great enough */
	(*codec->vc_rambuffer_requirements)(size_x, size_y, &req);
	if (stride < req.vbs_stride) {
		errno = EINVAL;
		return NULL;
	}

	/* Must use a different, fallback "codec" that can deal with bad alignment */
	if (!IS_ALIGNED(stride, codec->vc_align) ||
	    !IS_ALIGNED((uintptr_t)mem, codec->vc_align))
		codec = codec->vc_nalgn;

	/* Allocate heap memory for the buffer */
	result = (REF struct video_membuffer *)malloc(sizeof(struct video_membuffer));
	if unlikely(!result)
		goto err;
	result->vb_stride             = stride;
	result->vb_total              = stride * size_y;
	result->vb_data               = (byte_t *)mem;
	result->vb_refcnt             = 1;
	result->vb_ops                = membuffer_getops();
	result->vb_format.vf_codec    = codec;
	result->vb_format.vf_pal      = palette;
	result->vb_size_x             = size_x;
	result->vb_size_y             = size_y;
	result->vm_release_mem        = release_mem;
	result->vm_release_mem_cookie = release_mem_cookie;
	if (palette)
		video_palette_incref(palette);
	return result;
err:
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_RAM_BUFFER_C */
