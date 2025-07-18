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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_RAM_C
#define GUARD_LIBVIDEO_GFX_BUFFER_RAM_C 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <malloc.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/palette.h>
#include <libvideo/color.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/blendcolors.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "../buffer.h"
#include "../gfx-utils.h"
#include "../gfx.h"
#include "../swgfx.h"
#include "ram.h"

DECL_BEGIN

static_assert(sizeof(struct old_gfx_ramdrv) <= (_VIDEO_GFX_N_DRIVER * sizeof(void *)),
              "sizeof(struct old_gfx_ramdrv) too large for '_VIDEO_GFX_N_DRIVER'");

#define RAMGFX_DATA   video_old_ramgfx_getdrv(self)->grd_data
#define RAMGFX_STRIDE video_old_ramgfx_getdrv(self)->grd_stride
#define RAMGFX_FORMAT video_old_ramgfx_getdrv(self)->grd_format
#define RAMGFX_CODEC  video_old_ramgfx_getdrv(self)->grd_format->vf_codec


/* GFX functions for memory-based video buffers (without GPU support) */
INTERN ATTR_IN(1) video_color_t CC
libvideo_ramgfx__getcolor_noblend(struct video_gfx const *__restrict self,
                                  video_coord_t x, video_coord_t y) {
	byte_t const *line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	return video_format_getcolor(RAMGFX_FORMAT, line, x);
}

INTERN ATTR_IN(1) video_color_t CC
libvideo_ramgfx__getcolor_with_key(struct video_gfx const *__restrict self,
                                   video_coord_t x, video_coord_t y) {
	byte_t const *line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	video_color_t result = video_format_getcolor(RAMGFX_FORMAT, line, x);
	if (result == self->vx_colorkey)
		result = 0;
	return result;
}

INTERN ATTR_IN(1) void CC
libvideo_ramgfx__putcolor(struct video_gfx const *__restrict self,
                          video_coord_t x, video_coord_t y,
                          video_color_t color) {
	/* Perform full color blending. */
	byte_t *line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	video_color_t o = video_format_getcolor(RAMGFX_FORMAT, line, x);
	video_color_t n = gfx_blendcolors(o, color, self->vx_blend);
	video_format_setcolor(RAMGFX_FORMAT, line, x, n);
}

INTERN ATTR_IN(1) void CC
libvideo_ramgfx__putcolor_noblend(struct video_gfx const *__restrict self,
                                  video_coord_t x, video_coord_t y,
                                  video_color_t color) {
	byte_t *line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	video_format_setcolor(RAMGFX_FORMAT, line, x, color);
}

#define DEFINE_libvideo_ramgfx__putcolor_FOO(name, mode)                      \
	INTERN ATTR_IN(1) void CC                                                 \
	libvideo_ramgfx__putcolor_##name(struct video_gfx const *__restrict self, \
	                                 video_coord_t x, video_coord_t y,        \
	                                 video_color_t color) {                   \
		byte_t *line = RAMGFX_DATA + y * RAMGFX_STRIDE;                       \
		video_color_t o = video_format_getcolor(RAMGFX_FORMAT, line, x);      \
		video_color_t n = gfx_blendcolors(o, color, mode);                    \
		video_format_setcolor(RAMGFX_FORMAT, line, x, n);                     \
	}
GFX_FOREACH_DEDICATED_BLENDMODE(DEFINE_libvideo_ramgfx__putcolor_FOO)
#undef DEFINE_libvideo_ramgfx__putcolor_FOO

#define DEFINE_libvideo_ramgfx__putcolor_FOO(name, mode)                      \
	INTERN ATTR_IN(1) void CC                                                 \
	libvideo_ramgfx__putcolor_##name(struct video_gfx const *__restrict self, \
	                                 video_coord_t x, video_coord_t y,        \
	                                 video_color_t color) {                   \
		byte_t *line = RAMGFX_DATA + y * RAMGFX_STRIDE;                       \
		video_color_t o = video_format_getcolor(RAMGFX_FORMAT, line, x);      \
		video_color_t c = GFX_BLENDMODE_GET_COLOR(self->vx_blend);            \
		video_color_t n = gfx_blendcolors_constant(o, color, mode, c);        \
		video_format_setcolor(RAMGFX_FORMAT, line, x, n);                     \
	}
GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(DEFINE_libvideo_ramgfx__putcolor_FOO)
#undef DEFINE_libvideo_ramgfx__putcolor_FOO

INTERN ATTR_IN(1) video_pixel_t CC
libvideo_ramgfx__getpixel(struct video_gfx const *__restrict self,
                          video_coord_t x, video_coord_t y) {
	byte_t const *line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	return (*RAMGFX_CODEC->vc_getpixel)(line, x);
}

INTERN ATTR_IN(1) void CC
libvideo_ramgfx__setpixel(struct video_gfx const *__restrict self,
                          video_coord_t x, video_coord_t y,
                          video_pixel_t pixel) {
	byte_t *line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	(*RAMGFX_CODEC->vc_setpixel)(line, x, pixel);
}


#ifdef CONFIG_HAVE_OLD_RAMBUFFER_PIXELn_FASTPASS
#define DEFINE_RAMGFX_GETSETPIXELn(n)                                     \
	INTERN ATTR_IN(1) video_pixel_t CC                                    \
	libvideo_ramgfx__getpixel##n(struct video_gfx const *__restrict self, \
	                             video_coord_t x, video_coord_t y) {      \
		byte_t const *line = RAMGFX_DATA + y * RAMGFX_STRIDE;             \
		return ((uint##n##_t const *)line)[x];                            \
	}                                                                     \
	                                                                      \
	INTERN ATTR_IN(1) void CC                                             \
	libvideo_ramgfx__setpixel##n(struct video_gfx const *__restrict self, \
	                             video_coord_t x, video_coord_t y,        \
	                             video_pixel_t pixel) {                   \
		byte_t *line = RAMGFX_DATA + y * RAMGFX_STRIDE;                   \
		((uint##n##_t *)line)[x] = pixel;                                 \
	}
DEFINE_RAMGFX_GETSETPIXELn(8)
DEFINE_RAMGFX_GETSETPIXELn(16)
DEFINE_RAMGFX_GETSETPIXELn(32)
#undef DEFINE_RAMGFX_GETSETPIXELn

union pixel24 {
	video_pixel_t pixel;
	byte_t        bytes[3];
};

INTERN ATTR_IN(1) video_pixel_t CC
libvideo_ramgfx__getpixel24(struct video_gfx const *__restrict self,
                            video_coord_t x, video_coord_t y) {
	union pixel24 result;
	byte_t const *line;
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	line += x * 3;
	result.bytes[0] = line[0];
	result.bytes[1] = line[1];
	result.bytes[2] = line[2];
	result.bytes[3] = 0;
	return result.pixel;
}

INTERN ATTR_IN(1) void CC
libvideo_ramgfx__setpixel24(struct video_gfx const *__restrict self,
                            video_coord_t x, video_coord_t y,
                            video_pixel_t pixel) {
	union pixel24 data;
	byte_t *line;
	line = RAMGFX_DATA + y * RAMGFX_STRIDE;
	line += x * 3;
	data.pixel = pixel;
	line[0] = data.bytes[0];
	line[1] = data.bytes[1];
	line[2] = data.bytes[2];
}
#endif /* CONFIG_HAVE_OLD_RAMBUFFER_PIXELn_FASTPASS */



INTERN NONNULL((1)) void FCC
old_rambuffer_destroy(struct video_buffer *__restrict self) {
	struct old_video_rambuffer *me;
	me = (struct old_video_rambuffer *)self;
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
	free(me->rb_data);
	free(me);
}

INTERN NONNULL((1)) void FCC
old_rambuffer_destroy__for_codec(struct video_buffer *__restrict self) {
	struct old_video_rambuffer__for_codec *me;
	me = (struct old_video_rambuffer__for_codec *)self;
	video_codec_handle_decref(me->rbfc_codec);
	old_rambuffer_destroy(me);
}

INTERN ATTR_INOUT(1) ATTR_OUT(2) int FCC
old_rambuffer_lock(struct video_buffer *__restrict self,
               struct video_lock *__restrict lock) {
	struct old_video_rambuffer *me;
	me = (struct old_video_rambuffer *)self;
	lock->vl_data   = me->rb_data;
	lock->vl_stride = me->rb_stride;
	return 0;
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
old_rambuffer_lockregion(struct video_buffer *__restrict self,
                     struct video_regionlock *__restrict lock) {
	struct old_video_rambuffer *me;
	me = (struct old_video_rambuffer *)self;
	video_regionlock_assert(me, lock);
	lock->vrl_lock.vl_stride = me->rb_stride;
	lock->vrl_lock.vl_data   = me->rb_data + lock->_vrl_rect.vcr_ymin * me->rb_stride;
	lock->vrl_xbas           = lock->_vrl_rect.vcr_xmin;
	return 0;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
old_rambuffer_initgfx(struct video_gfx *__restrict self) {
	struct old_video_rambuffer const *me = (struct old_video_rambuffer *)self->vx_buffer;
	struct old_gfx_ramdrv *drv = video_old_ramgfx_getdrv(self);
	libvideo_gfx_init_fullclip(self);
	old_gfx_ramdrv_init(drv, me);

	/* Default pixel accessors */
	drv->xsw_getpixel = &libvideo_ramgfx__getpixel;
	drv->xsw_setpixel = &libvideo_ramgfx__setpixel;

	/* Load optimized pixel accessors if applicable to the loaded format. */
#ifdef CONFIG_HAVE_OLD_RAMBUFFER_PIXELn_FASTPASS
	switch (me->vb_format.vf_codec->vc_specs.vcs_bpp) {
	case 8:
		drv->xsw_setpixel = &libvideo_ramgfx__setpixel8;
		drv->xsw_getpixel = &libvideo_ramgfx__getpixel8;
		break;
	case 16:
		drv->xsw_setpixel = &libvideo_ramgfx__setpixel16;
		drv->xsw_getpixel = &libvideo_ramgfx__getpixel16;
		break;
	case 24:
		drv->xsw_setpixel = &libvideo_ramgfx__setpixel24;
		drv->xsw_getpixel = &libvideo_ramgfx__getpixel24;
		break;
	case 32:
		drv->xsw_setpixel = &libvideo_ramgfx__setpixel32;
		drv->xsw_getpixel = &libvideo_ramgfx__getpixel32;
		break;
	default: break;
	}
#endif /* CONFIG_HAVE_OLD_RAMBUFFER_PIXELn_FASTPASS */

	/* Load generic operator defaults (overwritten as appropriate below) */
	libvideo_swgfx_populate(self);

	/* Select how colors should be read. */
	if (self->vx_flags & VIDEO_GFX_F_BLUR) {
		drv->xsw_getcolor = &libvideo_swgfx_generic__getcolor_blur;
	} else if (!VIDEO_COLOR_ISTRANSPARENT(self->vx_colorkey)) {
		drv->xsw_getcolor = &libvideo_ramgfx__getcolor_with_key;
	} else {
		drv->xsw_getcolor = &libvideo_ramgfx__getcolor_noblend;
	}

	/* Detect special blend modes. */
	(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_OVERRIDE);
	(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_ALPHA);
	switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
	case GFX_BLENDMODE_OVERRIDE:
		drv->xsw_putcolor = &libvideo_ramgfx__putcolor_noblend;
		break;
#define LINK_libvideo_ramgfx__putcolor_FOO(name, mode)          \
	case mode:                                                  \
		drv->xsw_putcolor = &libvideo_ramgfx__putcolor_##name; \
		break;
	GFX_FOREACH_DEDICATED_BLENDMODE(LINK_libvideo_ramgfx__putcolor_FOO)
	GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(LINK_libvideo_ramgfx__putcolor_FOO)
#undef LINK_libvideo_ramgfx__putcolor_FOO
	default:
		drv->xsw_putcolor = &libvideo_ramgfx__putcolor;
		break;
	}
	switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
#define LINK_libvideo_swgfx_generic__render_preblend_FOO(name, mode, preblend_name, preblend) \
	case mode:                                                                                \
		drv->xsw_putcolor_p = &libvideo_ramgfx__putcolor_##preblend_name;                     \
		break;
GFX_FOREACH_DEDICATED_PREBLENDMODE(LINK_libvideo_swgfx_generic__render_preblend_FOO)
#undef LINK_libvideo_swgfx_generic__render_preblend_FOO
	default:
		drv->xsw_putcolor_p = drv->xsw_putcolor;
		break;
	}

	/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
	if (me->vb_format.vf_codec->vc_codec == VIDEO_CODEC_RGBA8888) {
		if (drv->xsw_getcolor == &libvideo_ramgfx__getcolor_noblend)
			drv->xsw_getcolor = drv->xsw_getpixel;
		if (drv->xsw_putcolor == &libvideo_ramgfx__putcolor_noblend) {
			drv->xsw_putcolor   = drv->xsw_setpixel;
			drv->xsw_putcolor_p = drv->xsw_setpixel;
		}
	}
	/* ... */

	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
old_rambuffer_updategfx(struct video_gfx *__restrict self, unsigned int what) {
	struct old_gfx_ramdrv *drv = video_old_ramgfx_getdrv(self);

	/* Updated generic operators */
	libvideo_swgfx_update(self, what);

	/* Select how colors should be read. */
	if (what & (VIDEO_GFX_UPDATE_FLAGS | VIDEO_GFX_UPDATE_COLORKEY)) {
		if (self->vx_flags & VIDEO_GFX_F_BLUR) {
			drv->xsw_getcolor = &libvideo_swgfx_generic__getcolor_blur;
		} else if (!VIDEO_COLOR_ISTRANSPARENT(self->vx_colorkey)) {
			drv->xsw_getcolor = &libvideo_ramgfx__getcolor_with_key;
		} else {
			drv->xsw_getcolor = &libvideo_ramgfx__getcolor_noblend;
			/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
			if (drv->grd_format->vf_codec->vc_codec == VIDEO_CODEC_RGBA8888)
				drv->xsw_getcolor = drv->xsw_getpixel;
		}
	}

	/* Detect special blend modes. */
	if (what & VIDEO_GFX_UPDATE_BLEND) {
		(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_OVERRIDE);
		(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_ALPHA);
		switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
		case GFX_BLENDMODE_OVERRIDE:
			drv->xsw_putcolor = &libvideo_ramgfx__putcolor_noblend;
			/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
			if (drv->grd_format->vf_codec->vc_codec == VIDEO_CODEC_RGBA8888)
				drv->xsw_putcolor = drv->xsw_setpixel;
			break;
#define LINK_libvideo_ramgfx__putcolor_FOO(name, mode)                        \
		case mode:                                                            \
			drv->xsw_putcolor = &libvideo_ramgfx__putcolor_##name; \
			break;
			GFX_FOREACH_DEDICATED_BLENDMODE(LINK_libvideo_ramgfx__putcolor_FOO)
			GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(LINK_libvideo_ramgfx__putcolor_FOO)
#undef LINK_libvideo_ramgfx__putcolor_FOO
		default:
			drv->xsw_putcolor = &libvideo_ramgfx__putcolor;
			break;
		}
		switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
#define LINK_libvideo_swgfx_generic__render_preblend_FOO(name, mode, preblend_name, preblend) \
		case mode:                                                                            \
			drv->xsw_putcolor_p = &libvideo_ramgfx__putcolor_##preblend_name;                 \
			break;
GFX_FOREACH_DEDICATED_PREBLENDMODE(LINK_libvideo_swgfx_generic__render_preblend_FOO)
#undef LINK_libvideo_swgfx_generic__render_preblend_FOO
		default:
			drv->xsw_putcolor_p = drv->xsw_putcolor;
			break;
		}
	}

	return self;
}

INTERN struct video_buffer_ops old_rambuffer_ops = {};
INTERN struct video_buffer_ops old_rambuffer_ops__for_codec = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _old_rambuffer_ops(void) {
	if unlikely(!old_rambuffer_ops.vi_destroy) {
		video_buffer_ops_set_LOCKOPS_like_RAMBUFFER(&old_rambuffer_ops);
		video_buffer_ops_set_GFXOPS_like_RAMBUFFER(&old_rambuffer_ops);
		COMPILER_WRITE_BARRIER();
		old_rambuffer_ops.vi_destroy = &old_rambuffer_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &old_rambuffer_ops;
}
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _old_rambuffer_ops__for_codec(void) {
	if unlikely(!old_rambuffer_ops__for_codec.vi_destroy) {
		video_buffer_ops_set_LOCKOPS_like_RAMBUFFER(&old_rambuffer_ops__for_codec);
		video_buffer_ops_set_GFXOPS_like_RAMBUFFER(&old_rambuffer_ops__for_codec);
		COMPILER_WRITE_BARRIER();
		old_rambuffer_ops__for_codec.vi_destroy = &old_rambuffer_destroy__for_codec;
		COMPILER_WRITE_BARRIER();
	}
	return &old_rambuffer_ops__for_codec;
}




PRIVATE NONNULL((1)) void FCC
membuffer_destroy(struct video_buffer *__restrict self) {
	struct old_video_membuffer *me = (struct old_video_membuffer *)self;
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
	if (me->vm_release_mem)
		(*me->vm_release_mem)(me->vm_release_mem_cookie, me->rb_data);
	free(me);
}

PRIVATE NONNULL((1)) void FCC
membuffer_destroy__for_codec(struct video_buffer *__restrict self) {
	struct old_video_membuffer__for_codec *me = (struct old_video_membuffer__for_codec *)self;
	video_codec_handle_decref(me->vmfc_codec);
	membuffer_destroy(me);
}


INTERN struct video_buffer_ops old_membuffer_ops = {};
INTERN struct video_buffer_ops old_membuffer_ops__for_codec = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _old_membuffer_ops(void) {
	if unlikely(!old_membuffer_ops.vi_destroy) {
		video_buffer_ops_set_LOCKOPS_like_RAMBUFFER(&old_membuffer_ops);
		video_buffer_ops_set_GFXOPS_like_RAMBUFFER(&old_membuffer_ops);
		COMPILER_WRITE_BARRIER();
		old_membuffer_ops.vi_destroy = &membuffer_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &old_membuffer_ops;
}

INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _old_membuffer_ops__for_codec(void) {
	if unlikely(!old_membuffer_ops__for_codec.vi_destroy) {
		video_buffer_ops_set_LOCKOPS_like_RAMBUFFER(&old_membuffer_ops__for_codec);
		video_buffer_ops_set_GFXOPS_like_RAMBUFFER(&old_membuffer_ops__for_codec);
		COMPILER_WRITE_BARRIER();
		old_membuffer_ops__for_codec.vi_destroy = &membuffer_destroy__for_codec;
		COMPILER_WRITE_BARRIER();
	}
	return &old_membuffer_ops__for_codec;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_RAM_C */
