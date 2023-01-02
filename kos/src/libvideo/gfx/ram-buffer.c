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
#ifndef GUARD_LIBVIDEO_GFX_RAM_BUFFER_C
#define GUARD_LIBVIDEO_GFX_RAM_BUFFER_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <sys/mman.h>

#include <assert.h>
#include <inttypes.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>

#include "buffer.h"
#include "empty-buffer.h"
#include "gfx.h"
#include "ram-buffer.h"

/* libstdc++ #undef's min/max (ugh... I'll really have to replace
 * that  library  with  my  own  version  of  it  at  one point).
 * But we want  them as  macros, so  include this  at the  end... */
#include <minmax.h>

DECL_BEGIN


#define RAMGFX_DATA   (byte_t *)self->vx_driver[VIDEO_BUFFER_RAMGFX_DATA]
#define RAMGFX_STRIDE (size_t)self->vx_driver[VIDEO_BUFFER_RAMGFX_STRIDE]

#if !defined(NDEBUG) && 1
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
#endif /* NDEBUG */


/* GFX functions for memory-based video buffers (without GPU support) */
INTERN NONNULL((1)) video_color_t CC
libvideo_gfx_ramgfx_getcolor(struct video_gfx const *__restrict self,
                             uintptr_t x, uintptr_t y) {
	byte_t *line;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	return self->vx_buffer->vb_format.getcolor(line, x);
}

INTERN NONNULL((1)) video_color_t CC
libvideo_gfx_ramgfx_getcolor_blur(struct video_gfx const *__restrict self,
                                  uintptr_t x, uintptr_t y) {
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
                                      uintptr_t x, uintptr_t y) {
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
                             uintptr_t x, uintptr_t y, video_color_t color) {
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
                                     uintptr_t x, uintptr_t y, video_color_t color) {
	byte_t *line;
	struct video_buffer *buffer;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	buffer = self->vx_buffer;
	buffer->vb_format.setcolor(line, x, color);
}

INTERN NONNULL((1)) void CC
libvideo_gfx_ramgfx_putcolor_alphablend(struct video_gfx *__restrict self,
                                        uintptr_t x, uintptr_t y, video_color_t color) {
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




PRIVATE struct video_buffer_ops rambuffer_ops;
PRIVATE struct video_buffer_ops rambuffer_ops_munmap;

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

INTERN NONNULL((1)) void CC
rambuffer_destroy_munmap(struct video_buffer *__restrict self) {
	struct video_rambuffer *me;
	me = (struct video_rambuffer *)self;
	assert(me->vb_ops == &rambuffer_ops_munmap);
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
	munmap(me->vb_data, me->vb_total);
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
                             struct video_lock const *__restrict lock) {
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


LOCAL NONNULL((1)) void CC
rambuffer_gfx_select_gfxops(struct video_gfx *__restrict self) {
	self->vx_xmin = self->vx_offt_x <= 0 ? (uintptr_t)0 : (uintptr_t)self->vx_offt_x;
	self->vx_ymin = self->vx_offt_y <= 0 ? (uintptr_t)0 : (uintptr_t)self->vx_offt_y;
	/* Compare < because empty clip rects aren't allowed / are
	 * handled separately by setting stub/empty GFX pixel ops. */
	assertf(self->vx_xmin < self->vx_xend,
	        "self->vx_xmin = %" PRIuPTR " (%#" PRIxPTR ")\n"
	        "self->vx_xend = %" PRIuPTR " (%#" PRIxPTR ")",
	        self->vx_xmin, self->vx_xmin,
	        self->vx_xend, self->vx_xend);
	assertf(self->vx_ymin < self->vx_yend,
	        "self->vx_ymin = %" PRIuPTR " (%#" PRIxPTR ")\n"
	        "self->vx_yend = %" PRIuPTR " (%#" PRIxPTR ")",
	        self->vx_ymin, self->vx_ymin,
	        self->vx_yend, self->vx_yend);
	assertf(self->vx_xend <= self->vx_buffer->vb_size_x,
	        "self->vx_xend              = %" PRIuPTR " (%#" PRIxPTR ")\n"
	        "self->vx_buffer->vb_size_x = %" PRIuSIZ " (%#" PRIxSIZ ")",
	        self->vx_xend, self->vx_xend,
	        self->vx_buffer->vb_size_x,
	        self->vx_buffer->vb_size_x);
	assertf(self->vx_yend <= self->vx_buffer->vb_size_y,
	        "self->vx_yend              = %" PRIuPTR " (%#" PRIxPTR ")\n"
	        "self->vx_buffer->vb_size_y = %" PRIuSIZ " (%#" PRIxSIZ ")",
	        self->vx_yend, self->vx_yend,
	        self->vx_buffer->vb_size_y,
	        self->vx_buffer->vb_size_y);

	/* TODO: Add optimizations for same-codec blits */
	/* TODO: Add optimizations `vc_linefill()' and `vc_linecopy()'
	 * NOTE: `vc_linecopy()' can only  be used when  no blending might  ever
	 *       be required  during same-codec  blit  operations. This  can  be
	 *       determined by the  combination of `blendmode',  as well as  the
	 *       selected video codec/palette (e.g. with generic alpha-blending,
	 *       a palette-based codec, and a palette with all colors specifying
	 *       an alpha-channel set to 255, `vc_linecopy()' can still be  used
	 *       as  though  `GFX_BLENDINFO_OVERRIDE'  was given  (at  least for
	 *       same-codec blit operations)) */

	/* Select the best matching GFX operations V-table */
	if likely(self->vx_offt_x == 0 && self->vx_offt_y == 0) {
		self->vx_ops = libvideo_gfx_defaultgfx_getops();
	} else {
		self->vx_ops = libvideo_gfx_defaultgfx_getops_o();
	}
}

PRIVATE NONNULL((1, 2)) void CC
rambuffer_getgfx(struct video_buffer *__restrict self,
                 struct video_gfx *__restrict result,
                 gfx_blendmode_t blendmode, uintptr_t flags,
                 video_color_t colorkey,
                 struct video_buffer_rect const *clip) {
	struct video_rambuffer *me;
	me = (struct video_rambuffer *)self;

	result->vx_buffer                             = self;
	result->vx_blend                              = blendmode;
	result->vx_flags                              = flags;
	result->vx_colorkey                           = colorkey;
	result->vx_driver[VIDEO_BUFFER_RAMGFX_DATA]   = me->vb_data;
	result->vx_driver[VIDEO_BUFFER_RAMGFX_STRIDE] = (void *)(uintptr_t)me->vb_stride;
	if (clip) {
		result->vx_offt_x = clip->vbr_startx;
		result->vx_offt_y = clip->vbr_starty;
		if unlikely(!clip->vbr_sizex || !clip->vbr_sizey)
			goto empty_clip;
		if unlikely(OVERFLOW_UADD(result->vx_offt_x, clip->vbr_sizex, &result->vx_xend) ||
		            result->vx_xend > self->vb_size_x) {
			if unlikely(result->vx_offt_x >= (intptr_t)self->vb_size_x ||
			            (result->vx_offt_x < 0 && ((uintptr_t)-result->vx_offt_x >= clip->vbr_sizex)))
				goto empty_clip;
			result->vx_xend = self->vb_size_x;
		}
		if unlikely(OVERFLOW_UADD(result->vx_offt_y, clip->vbr_sizey, &result->vx_yend) ||
		            result->vx_yend > self->vb_size_y) {
			if unlikely(result->vx_offt_y >= (intptr_t)self->vb_size_y ||
			            (result->vx_offt_y < 0 && ((uintptr_t)-result->vx_offt_y >= clip->vbr_sizey)))
				goto empty_clip;
			result->vx_yend = self->vb_size_y;
		}
		if unlikely(!result->vx_xend || !result->vx_yend)
			goto empty_clip;
	} else {
		result->vx_offt_x = 0;
		result->vx_offt_y = 0;
		result->vx_xend   = self->vb_size_x;
		result->vx_yend   = self->vb_size_y;
	}

	/* Select how pixels should be read. */
	if (flags & VIDEO_GFX_FBLUR) {
		result->vx_pxops.fxo_getcolor = &libvideo_gfx_ramgfx_getcolor_blur;
	} else if ((colorkey & VIDEO_COLOR_ALPHA_MASK) != 0) {
		result->vx_pxops.fxo_getcolor = &libvideo_gfx_ramgfx_getcolor_with_key;
	} else {
		result->vx_pxops.fxo_getcolor = &libvideo_gfx_ramgfx_getcolor;
	}

	/* Detect special blend modes. */
	if (blendmode == GFX_BLENDINFO_OVERRIDE) {
		result->vx_pxops.fxo_putcolor = &libvideo_gfx_ramgfx_putcolor_noblend;
	} else if (blendmode == GFX_BLENDINFO_ALPHA) {
		result->vx_pxops.fxo_putcolor = &libvideo_gfx_ramgfx_putcolor_alphablend;
	} else if (GFX_BLENDINFO_GET_SRCRGB(blendmode) == GFX_BLENDMODE_ONE &&
	           GFX_BLENDINFO_GET_SRCA(blendmode) == GFX_BLENDMODE_ONE &&
	           GFX_BLENDINFO_GET_DSTRGB(blendmode) == GFX_BLENDMODE_ZERO &&
	           GFX_BLENDINFO_GET_DSTA(blendmode) == GFX_BLENDMODE_ZERO &&
	           is_add_or_subtract_or_max(GFX_BLENDINFO_GET_FUNRGB(blendmode)) &&
	           is_add_or_subtract_or_max(GFX_BLENDINFO_GET_FUNA(blendmode))) {
		result->vx_pxops.fxo_putcolor = &libvideo_gfx_ramgfx_putcolor_noblend;
	} else {
		result->vx_pxops.fxo_putcolor = &libvideo_gfx_ramgfx_putcolor;
	}
	/* Select the best-fitting GFX operations table. */
	rambuffer_gfx_select_gfxops(result);
	return;
empty_clip:
	result->vx_pxops.fxo_getcolor = &video_gfx_empty_getcolor;
	result->vx_pxops.fxo_putcolor = &video_gfx_empty_putcolor;
	result->vx_ops                = libvideo_getemptygfxops();
	result->vx_offt_x             = 0;
	result->vx_offt_y             = 0;
	result->vx_xmin               = 0;
	result->vx_ymin               = 0;
	result->vx_xend               = 0;
	result->vx_yend               = 0;
}

PRIVATE NONNULL((1, 2)) void CC
rambuffer_clipgfx(struct video_gfx const *gfx,
                  struct video_gfx *result,
                  intptr_t start_x, intptr_t start_y,
                  size_t size_x, size_t size_y) {
	size_t old_size_x, old_size_y;
	old_size_x = video_gfx_sizex(gfx);
	old_size_y = video_gfx_sizey(gfx);
	if (result != gfx)
		memcpy(result, gfx, sizeof(struct video_gfx));
	result->vx_offt_x += start_x;
	result->vx_offt_y += start_y;
	if unlikely(!size_x || !size_y)
		goto empty_clip;
	if unlikely(OVERFLOW_UADD(result->vx_offt_x, size_x, &result->vx_xend) ||
	            result->vx_xend > old_size_x) {
		if unlikely(result->vx_offt_x >= (intptr_t)old_size_x ||
		            (result->vx_offt_x < 0 && ((uintptr_t)-result->vx_offt_x >= size_x)))
			goto empty_clip;
		result->vx_xend = old_size_x;
	}
	if unlikely(OVERFLOW_UADD(result->vx_offt_y, size_y, &result->vx_yend) ||
	            result->vx_yend > old_size_y) {
		if unlikely(result->vx_offt_y >= (intptr_t)old_size_y ||
		            (result->vx_offt_y < 0 && ((uintptr_t)-result->vx_offt_y >= size_y)))
			goto empty_clip;
		result->vx_yend = old_size_y;
	}
	if unlikely(!result->vx_xend || !result->vx_yend)
		goto empty_clip;
	/* Select the best-fitting GFX operations table. */
	rambuffer_gfx_select_gfxops(result);
	return;
empty_clip:
	result->vx_pxops.fxo_getcolor = &video_gfx_empty_getcolor;
	result->vx_pxops.fxo_putcolor = &video_gfx_empty_putcolor;
	result->vx_ops                = libvideo_getemptygfxops();
	result->vx_offt_x             = 0;
	result->vx_offt_y             = 0;
	result->vx_xmin               = 0;
	result->vx_ymin               = 0;
	result->vx_xend               = 0;
	result->vx_yend               = 0;
}



INTERN ATTR_RETNONNULL WUNUSED
struct video_buffer_ops *CC rambuffer_getops(void) {
	if unlikely(!rambuffer_ops.vi_destroy) {
		rambuffer_ops.vi_lock    = &rambuffer_lock;
		rambuffer_ops.vi_unlock  = &rambuffer_unlock;
		rambuffer_ops.vi_getgfx  = &rambuffer_getgfx;
		rambuffer_ops.vi_clipgfx = &rambuffer_clipgfx;
		COMPILER_WRITE_BARRIER();
		rambuffer_ops.vi_destroy = &rambuffer_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &rambuffer_ops;
}

INTERN ATTR_RETNONNULL WUNUSED
struct video_buffer_ops *CC rambuffer_getops_munmap(void) {
	if unlikely(!rambuffer_ops.vi_destroy) {
		rambuffer_ops.vi_lock    = &rambuffer_lock;
		rambuffer_ops.vi_unlock  = &rambuffer_unlock;
		rambuffer_ops.vi_getgfx  = &rambuffer_getgfx;
		rambuffer_ops.vi_clipgfx = &rambuffer_clipgfx;
		COMPILER_WRITE_BARRIER();
		rambuffer_ops.vi_destroy = &rambuffer_destroy_munmap;
		COMPILER_WRITE_BARRIER();
	}
	return &rambuffer_ops;
}



/* Create a new RAM-based video buffer */
INTERN WUNUSED NONNULL((3)) /*REF*/ struct video_buffer *CC
libvideo_rambuffer_create(size_t size_x, size_t size_y,
                          struct video_codec const *__restrict codec,
                          struct video_palette *palette) {
	/*REF*/ struct video_rambuffer *result;
	struct video_rambuffer_requirements req;
	assert(codec);
	/* Figure out buffer requirements. */
	(*codec->vc_rambuffer_requirements)(size_x, size_y, &req);

	/* Allocate heap memory for the buffer */
	result = (/*REF*/ struct video_rambuffer *)malloc(sizeof(struct video_rambuffer));
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




DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_RAM_BUFFER_C */
