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
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <malloc.h>
#include <stddef.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/palette.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/blendcolors.h>

#include "gfx.h"
#include "ram-buffer.h"

DECL_BEGIN

#define PRIdOFF PRIdN(__SIZEOF_VIDEO_OFFSET_T__)
#define PRIxOFF PRIxN(__SIZEOF_VIDEO_OFFSET_T__)
#define PRIuCRD PRIuN(__SIZEOF_VIDEO_COORD_T__)
#define PRIxCRD PRIxN(__SIZEOF_VIDEO_COORD_T__)
#define PRIuDIM PRIuN(__SIZEOF_VIDEO_DIM_T__)
#define PRIxDIM PRIxN(__SIZEOF_VIDEO_DIM_T__)


#define RAMGFX_DATA   (byte_t *)self->vx_driver[RAMGFX_DRIVER__DATA]
#define RAMGFX_STRIDE (size_t)self->vx_driver[RAMGFX_DRIVER__STRIDE]

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
libvideo_ramgfx__getcolor_noblend(struct video_gfx const *__restrict self,
                                      video_coord_t x, video_coord_t y) {
	byte_t *line;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	return self->vx_buffer->vb_format.getcolor(line, x);
}

INTERN NONNULL((1)) video_color_t CC
libvideo_ramgfx__getcolor_blur(struct video_gfx const *__restrict self,
                                   video_coord_t x, video_coord_t y) {
	byte_t *line;
	video_color_t result;
	video_color_t colors[8];
	video_twochannels_t r, g, b, a;
	uint_fast8_t i, color_count;
#define MODE_XMIN 0x1
#define MODE_XMAX 0x2
#define MODE_YMIN 0x4
#define MODE_YMAX 0x8
	uint_fast8_t mode = 0x0;
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
	result = VIDEO_COLOR_RGBA((video_channel_t)r,
	                          (video_channel_t)g,
	                          (video_channel_t)b,
	                          (video_channel_t)a);
	return result;
}

INTERN NONNULL((1)) video_color_t CC
libvideo_ramgfx__getcolor_with_key(struct video_gfx const *__restrict self,
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

INTERN NONNULL((1)) void CC
libvideo_ramgfx__putcolor(struct video_gfx *__restrict self,
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
	n = gfx_blendcolors(o, color, self->vx_blend);
	buffer->vb_format.setcolor(line, x, n);
}

INTERN NONNULL((1)) void CC
libvideo_ramgfx__putcolor_noblend(struct video_gfx *__restrict self,
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
libvideo_ramgfx__putcolor_alphablend(struct video_gfx *__restrict self,
                                         video_coord_t x, video_coord_t y,
                                         video_color_t color) {
	byte_t *line;
	struct video_buffer *buffer;
	video_color_t o, n;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	buffer = self->vx_buffer;
	o = buffer->vb_format.getcolor(line, x);
	n = gfx_blendcolors(o, color, GFX_BLENDINFO_ALPHA);
	buffer->vb_format.setcolor(line, x, n);
}

INTERN NONNULL((1)) video_pixel_t CC
libvideo_ramgfx__getpixel(struct video_gfx const *__restrict self,
                              video_coord_t x, video_coord_t y) {
	byte_t const *line;
	struct video_buffer *buffer;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	buffer = self->vx_buffer;
	return buffer->vb_format.getpixel(line, x);
}

INTERN NONNULL((1)) void CC
libvideo_ramgfx__setpixel(struct video_gfx *__restrict self,
                              video_coord_t x, video_coord_t y,
                              video_pixel_t pixel) {
	byte_t *line;
	struct video_buffer *buffer;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	buffer = self->vx_buffer;
	buffer->vb_format.setpixel(line, x, pixel);
}


#ifdef CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS
#define DEFINE_RAMGFX_GETSETPIXELn(n)                                         \
	INTERN NONNULL((1)) video_pixel_t CC                                      \
	libvideo_ramgfx__getpixel##n(struct video_gfx const *__restrict self, \
	                                video_coord_t x, video_coord_t y) {       \
		byte_t *line;                                                         \
		ASSERT_ABS_COORDS(self, x, y);                                        \
		line = RAMGFX_DATA + y * RAMGFX_STRIDE;                               \
		return ((uint##n##_t const *)line)[x];                                \
	}                                                                         \
	                                                                          \
	INTERN NONNULL((1)) void CC                                               \
	libvideo_ramgfx__setpixel##n(struct video_gfx *__restrict self,       \
	                                video_coord_t x, video_coord_t y,         \
	                                video_pixel_t pixel) {                    \
		byte_t *line;                                                         \
		ASSERT_ABS_COORDS(self, x, y);                                        \
		line = RAMGFX_DATA + y * RAMGFX_STRIDE;                               \
		((uint##n##_t *)line)[x] = pixel;                                     \
	}
DEFINE_RAMGFX_GETSETPIXELn(8)
DEFINE_RAMGFX_GETSETPIXELn(16)
DEFINE_RAMGFX_GETSETPIXELn(32)
#undef DEFINE_RAMGFX_GETSETPIXELn

union pixel24 {
	video_pixel_t pixel;
	byte_t        bytes[3];
};

INTERN NONNULL((1)) video_pixel_t CC
libvideo_ramgfx__getpixel24(struct video_gfx const *__restrict self,
                                video_coord_t x, video_coord_t y) {
	union pixel24 result;
	byte_t const *line;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	line += x * 3;
	result.bytes[0] = line[0];
	result.bytes[1] = line[1];
	result.bytes[2] = line[2];
	result.bytes[3] = 0;
	return result.pixel;
}

INTERN NONNULL((1)) void CC
libvideo_ramgfx__setpixel24(struct video_gfx *__restrict self,
                                video_coord_t x, video_coord_t y,
                                video_pixel_t pixel) {
	union pixel24 data;
	byte_t *line;
	ASSERT_ABS_COORDS(self, x, y);
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	line += x * 3;
	data.pixel = pixel;
	line[0] = data.bytes[0];
	line[1] = data.bytes[1];
	line[2] = data.bytes[2];
}
#endif /* CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS */



INTERN NONNULL((1)) void CC
rambuffer_destroy(struct video_buffer *__restrict self) {
	struct video_rambuffer *me;
	me = (struct video_rambuffer *)self;
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

INTERN ATTR_RETNONNULL NONNULL((1, 2)) struct video_gfx *CC
rambuffer_getgfx(struct video_buffer *__restrict self,
                 struct video_gfx *__restrict result,
                 gfx_blendmode_t blendmode, uintptr_t flags,
                 video_color_t colorkey) {
	struct video_rambuffer *me;
	me = (struct video_rambuffer *)self;
	result->vx_buffer   = me;
	result->vx_blend    = blendmode;
	result->vx_flags    = flags;
	result->vx_colorkey = colorkey;
	result->vx_driver[RAMGFX_DRIVER__DATA]   = me->vb_data;
	result->vx_driver[RAMGFX_DRIVER__STRIDE] = (void *)(uintptr_t)me->vb_stride;
	result->vx_offt_x = 0;
	result->vx_offt_y = 0;
	result->vx_xmin   = 0;
	result->vx_ymin   = 0;
	result->vx_xend   = me->vb_size_x;
	result->vx_yend   = me->vb_size_y;

	/* Load generic operator defaults (overwritten as appropriate below) */
	libvideo_gfx_populate_generic(result);

	/* Select how colors should be read. */
	if (flags & VIDEO_GFX_FBLUR) {
		result->vx_xops.vgxo_getcolor = &libvideo_ramgfx__getcolor_blur;
	} else if (!VIDEO_COLOR_ISTRANSPARENT(colorkey)) {
		result->vx_xops.vgxo_getcolor = &libvideo_ramgfx__getcolor_with_key;
	} else {
		result->vx_xops.vgxo_getcolor = &libvideo_ramgfx__getcolor_noblend;
	}

	/* Detect special blend modes. */
	if (blendmode == GFX_BLENDINFO_OVERRIDE) {
		result->vx_xops.vgxo_putcolor = &libvideo_ramgfx__putcolor_noblend;
	} else if (blendmode == GFX_BLENDINFO_ALPHA) {
		result->vx_xops.vgxo_putcolor = &libvideo_ramgfx__putcolor_alphablend;
	} else if (GFX_BLENDINFO_GET_SRCRGB(blendmode) == GFX_BLENDMODE_ONE &&
	           GFX_BLENDINFO_GET_SRCA(blendmode) == GFX_BLENDMODE_ONE &&
	           GFX_BLENDINFO_GET_DSTRGB(blendmode) == GFX_BLENDMODE_ZERO &&
	           GFX_BLENDINFO_GET_DSTA(blendmode) == GFX_BLENDMODE_ZERO &&
	           _blendinfo__is_add_or_subtract_or_max(GFX_BLENDINFO_GET_FUNRGB(blendmode)) &&
	           _blendinfo__is_add_or_subtract_or_max(GFX_BLENDINFO_GET_FUNA(blendmode))) {
		result->vx_xops.vgxo_putcolor = &libvideo_ramgfx__putcolor_noblend;
	} else {
		result->vx_xops.vgxo_putcolor = &libvideo_ramgfx__putcolor;
	}

	/* Default pixel accessors */
	result->vx_xops.vgxo_getpixel = &libvideo_ramgfx__getpixel;
	result->vx_xops.vgxo_setpixel = &libvideo_ramgfx__setpixel;

	/* Load optimized pixel accessors if applicable to the loaded format. */
#ifdef CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS
	switch (me->vb_format.vf_codec->vc_specs.vcs_bpp) {
	case 8:
		result->vx_xops.vgxo_setpixel = &libvideo_ramgfx__setpixel8;
		result->vx_xops.vgxo_getpixel = &libvideo_ramgfx__getpixel8;
		break;
	case 16:
		result->vx_xops.vgxo_setpixel = &libvideo_ramgfx__setpixel16;
		result->vx_xops.vgxo_getpixel = &libvideo_ramgfx__getpixel16;
		break;
	case 24:
		result->vx_xops.vgxo_setpixel = &libvideo_ramgfx__setpixel24;
		result->vx_xops.vgxo_getpixel = &libvideo_ramgfx__getpixel24;
		break;
	case 32:
		result->vx_xops.vgxo_setpixel = &libvideo_ramgfx__setpixel32;
		result->vx_xops.vgxo_getpixel = &libvideo_ramgfx__getpixel32;
		break;
	default: break;
	}
#endif /* CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS */
	/* ... */

	return result;
}

INTERN ATTR_RETNONNULL NONNULL((1)) struct video_gfx *CC
rambuffer_noblend(struct video_gfx *__restrict self) {
	self->vx_flags &= ~(VIDEO_GFX_FBLUR);
	self->vx_colorkey = 0;
	libvideo_gfx_populate_noblend(self);
	self->vx_xops.vgxo_getcolor = &libvideo_ramgfx__getcolor_noblend;
	self->vx_xops.vgxo_putcolor = &libvideo_ramgfx__putcolor_noblend;
	return self;
}


#undef rambuffer_ops
PRIVATE struct video_buffer_ops rambuffer_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _rambuffer_ops(void) {
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
#define rambuffer_ops (*_rambuffer_ops())



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
	result->vb_ops             = &rambuffer_ops;
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
