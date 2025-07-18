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
#ifdef __INTELLISENSE__
#include "ramdomain.c"
//#define DEFINE_rambuffer__initgfx
//#define DEFINE_rambuffer_revokable__initgfx
#define DEFINE_rambuffer_revokable_xoff__initgfx
#endif /* __INTELLISENSE__ */

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <atomic.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/color.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/blendcolors.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "buffer/ram.h"
#include "gfx-utils.h"
#include "gfx.h"
#include "ramdomain.h"
#include "swgfx.h"

#if (defined(DEFINE_rambuffer__initgfx) +           \
     defined(DEFINE_rambuffer_revokable__initgfx) + \
     defined(DEFINE_rambuffer_revokable_xoff__initgfx)) != 1
#error "Must #define exactly one of these"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_rambuffer__initgfx
#define LOCAL_rambuffer__initgfx   rambuffer__initgfx
#define LOCAL_rambuffer__updategfx rambuffer__updategfx
#define LOCAL_ramgfx__(x)          ramgfx__##x
#elif defined(DEFINE_rambuffer_revokable__initgfx)
#define LOCAL_rambuffer__initgfx   rambuffer_revokable__initgfx
#define LOCAL_rambuffer__updategfx rambuffer_revokable__updategfx
#define LOCAL_ramgfx__(x)          ramgfx_revokable__##x
#elif defined(DEFINE_rambuffer_revokable_xoff__initgfx)
#define LOCAL_rambuffer__initgfx   rambuffer_revokable_xoff__initgfx
#define LOCAL_rambuffer__updategfx rambuffer_revokable_xoff__updategfx
#define LOCAL_ramgfx__(x)          ramgfx_revokable_xoff__##x
#else /* ... */
#error "Invalid configuration"
#endif /* !... */

#define LOCAL_ramgfx__getcolor_noblend LOCAL_ramgfx__(getcolor_noblend)
#define LOCAL_ramgfx__getcolor_withkey LOCAL_ramgfx__(getcolor_withkey)
#define LOCAL_ramgfx__putcolor         LOCAL_ramgfx__(putcolor)
#define LOCAL_ramgfx__putcolor_noblend LOCAL_ramgfx__(putcolor_noblend)
#define LOCAL_ramgfx__getpixel         LOCAL_ramgfx__(getpixel)
#define LOCAL_ramgfx__setpixel         LOCAL_ramgfx__(setpixel)
#ifdef CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS
#define LOCAL_ramgfx__getpixel8  LOCAL_ramgfx__(getpixel8)
#define LOCAL_ramgfx__getpixel16 LOCAL_ramgfx__(getpixel16)
#define LOCAL_ramgfx__getpixel24 LOCAL_ramgfx__(getpixel24)
#define LOCAL_ramgfx__getpixel32 LOCAL_ramgfx__(getpixel32)
#define LOCAL_ramgfx__setpixel8  LOCAL_ramgfx__(setpixel8)
#define LOCAL_ramgfx__setpixel16 LOCAL_ramgfx__(setpixel16)
#define LOCAL_ramgfx__setpixel24 LOCAL_ramgfx__(setpixel24)
#define LOCAL_ramgfx__setpixel32 LOCAL_ramgfx__(setpixel32)
#endif /* CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS */


#define LINK_LOCAL_ramgfx__putcolor_FOO(name, mode)           \
	case mode:                                                \
		drv->xsw_putcolor = &LOCAL_ramgfx__(putcolor_##name); \
		break;
#define LINK_LOCAL_ramgfx__putcolor_preblend_FOO(name, mode, preblend_name, preblend) \
	case mode:                                                                        \
		drv->xsw_putcolor_p = &LOCAL_ramgfx__(putcolor_##preblend_name);              \
		break;

/* GFX */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
LOCAL_rambuffer__initgfx(struct video_gfx *__restrict self) {
#ifdef DEFINE_rambuffer__initgfx
	static_assert(sizeof(struct gfx_ramdrv) <= (_VIDEO_GFX_N_DRIVER * sizeof(void *)));
	struct video_rambuffer *me = (struct video_rambuffer *)self->vx_buffer;
	struct gfx_ramdrv *drv = video_ramgfx_getdrv(self);
	drv->grdc_format = &me->vb_format;
	drv->grdc_stride = me->rb_stride;
	drv->grd_data    = me->rb_data;
#elif defined(DEFINE_rambuffer_revokable__initgfx)
	static_assert(sizeof(struct gfx_ramdrv_revokable) <= (_VIDEO_GFX_N_DRIVER * sizeof(void *)));
	struct video_rambuffer_revokable *me = (struct video_rambuffer_revokable *)self->vx_buffer;
	struct gfx_ramdrv_revokable *drv = video_ramgfx_getdrv_revokable(self);
	drv->grdc_format = &me->vb_format;
	drv->grdc_stride = me->rbrv_stride;
	drv->grdrv_gfx   = &me->rbrv_gfx;
#elif defined(DEFINE_rambuffer_revokable_xoff__initgfx)
	static_assert(sizeof(struct gfx_ramdrv_revokable_xoff) <= (_VIDEO_GFX_N_DRIVER * sizeof(void *)));
	struct video_rambuffer_revokable_subregion *me = (struct video_rambuffer_revokable_subregion *)self->vx_buffer;
	struct gfx_ramdrv_revokable_xoff *drv = video_ramgfx_getdrv_revokable_xoff(self);
	drv->grdc_format = &me->vb_format;
	drv->grdc_stride = me->rbrv_stride;
	drv->grdrv_gfx   = &me->rbrv_gfx;
	drv->grdrvx_xoff = me->rbrvsr_xoff;
#endif /* !DEFINE_rambuffer__initgfx */

	/* Initialize GFX as a full clip */
	libvideo_gfx_init_fullclip(self);

	/* Default pixel accessors */
	drv->xsw_getpixel = &LOCAL_ramgfx__getpixel;
	drv->xsw_setpixel = &LOCAL_ramgfx__setpixel;

	/* Load optimized pixel accessors if applicable to the loaded format. */
#ifdef CONFIG_HAVE_OLD_RAMBUFFER_PIXELn_FASTPASS
	switch (me->vb_format.vf_codec->vc_specs.vcs_bpp) {
	case 8:
		drv->xsw_setpixel = &LOCAL_ramgfx__setpixel8;
		drv->xsw_getpixel = &LOCAL_ramgfx__getpixel8;
		break;
	case 16:
		drv->xsw_setpixel = &LOCAL_ramgfx__setpixel16;
		drv->xsw_getpixel = &LOCAL_ramgfx__getpixel16;
		break;
	case 24:
		drv->xsw_setpixel = &LOCAL_ramgfx__setpixel24;
		drv->xsw_getpixel = &LOCAL_ramgfx__getpixel24;
		break;
	case 32:
		drv->xsw_setpixel = &LOCAL_ramgfx__setpixel32;
		drv->xsw_getpixel = &LOCAL_ramgfx__getpixel32;
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
		drv->xsw_getcolor = &LOCAL_ramgfx__getcolor_withkey;
	} else {
		drv->xsw_getcolor = &LOCAL_ramgfx__getcolor_noblend;
	}

	/* Detect special blend modes. */
	(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_OVERRIDE);
	(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_ALPHA);
	switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
	case GFX_BLENDMODE_OVERRIDE:
		drv->xsw_putcolor = &LOCAL_ramgfx__putcolor_noblend;
		break;
	GFX_FOREACH_DEDICATED_BLENDMODE(LINK_LOCAL_ramgfx__putcolor_FOO)
	GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(LINK_LOCAL_ramgfx__putcolor_FOO)
	default: drv->xsw_putcolor = &LOCAL_ramgfx__putcolor; break;
	}
	switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
	GFX_FOREACH_DEDICATED_PREBLENDMODE(LINK_LOCAL_ramgfx__putcolor_preblend_FOO)
	default: drv->xsw_putcolor_p = drv->xsw_putcolor; break;
	}

	/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
	if (me->vb_format.vf_codec->vc_codec == VIDEO_CODEC_RGBA8888) {
		if (drv->xsw_getcolor == &LOCAL_ramgfx__getcolor_noblend)
			drv->xsw_getcolor = drv->xsw_getpixel;
		if (drv->xsw_putcolor == &LOCAL_ramgfx__putcolor_noblend) {
			drv->xsw_putcolor   = drv->xsw_setpixel;
			drv->xsw_putcolor_p = drv->xsw_setpixel;
		}
	}
	/* ... */

	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
LOCAL_rambuffer__updategfx(struct video_gfx *__restrict self, unsigned int what) {
	struct gfx_ramdrv_common *drv = video_ramgfx_getdrv_common(self);

	/* Updated generic operators */
	libvideo_swgfx_update(self, what);

	/* Select how colors should be read. */
	if (what & (VIDEO_GFX_UPDATE_FLAGS | VIDEO_GFX_UPDATE_COLORKEY)) {
		if (self->vx_flags & VIDEO_GFX_F_BLUR) {
			drv->xsw_getcolor = &libvideo_swgfx_generic__getcolor_blur;
		} else if (!VIDEO_COLOR_ISTRANSPARENT(self->vx_colorkey)) {
			drv->xsw_getcolor = &LOCAL_ramgfx__getcolor_withkey;
		} else {
			drv->xsw_getcolor = &LOCAL_ramgfx__getcolor_noblend;
			/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
			if (drv->grdc_format->vf_codec->vc_codec == VIDEO_CODEC_RGBA8888)
				drv->xsw_getcolor = drv->xsw_getpixel;
		}
	}

	/* Detect special blend modes. */
	if (what & VIDEO_GFX_UPDATE_BLEND) {
		(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_OVERRIDE);
		(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_ALPHA);
		switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
		case GFX_BLENDMODE_OVERRIDE:
			drv->xsw_putcolor = &LOCAL_ramgfx__putcolor_noblend;
			/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
			if (drv->grdc_format->vf_codec->vc_codec == VIDEO_CODEC_RGBA8888)
				drv->xsw_putcolor = drv->xsw_setpixel;
			break;
		GFX_FOREACH_DEDICATED_BLENDMODE(LINK_LOCAL_ramgfx__putcolor_FOO)
		GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(LINK_LOCAL_ramgfx__putcolor_FOO)
		default: drv->xsw_putcolor = &LOCAL_ramgfx__putcolor; break;
		}
		switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
		GFX_FOREACH_DEDICATED_PREBLENDMODE(LINK_LOCAL_ramgfx__putcolor_preblend_FOO)
		default: drv->xsw_putcolor_p = drv->xsw_putcolor; break;
		}
	}

	return self;
}



#ifdef DEFINE_rambuffer__initgfx
#define LOCAL_GFX_LOCK()   (void)0
#define LOCAL_GFX_UNLOCK() (void)0
#define LOCAL_GFX_DATA     video_ramgfx_getcdrv(self)->grd_data
#else /* DEFINE_rambuffer__initgfx */
#define LOCAL_GFX_LOCK()   atomic_inc(&video_ramgfx_getcdrv_revokable(self)->grdrv_gfx->rbrvg_inuse)
#define LOCAL_GFX_UNLOCK() atomic_dec(&video_ramgfx_getcdrv_revokable(self)->grdrv_gfx->rbrvg_inuse)
#define LOCAL_GFX_DATA     atomic_read(&video_ramgfx_getcdrv_revokable(self)->grdrv_gfx->rbrvg_data)
#endif /* !DEFINE_rambuffer__initgfx */
#define LOCAL_GFX_STRIDE video_ramgfx_getcdrv_common(self)->grdc_stride
#define LOCAL_GFX_FORMAT video_ramgfx_getcdrv_common(self)->grdc_format
#ifdef DEFINE_rambuffer_revokable_xoff__initgfx
#define LOCAL_GFX_XOFF video_ramgfx_getcdrv_revokable_xoff(self)->grdrvx_xoff
#else /* DEFINE_rambuffer_revokable_xoff__initgfx */
#define LOCAL_GFX_XOFF 0
#endif /* !DEFINE_rambuffer_revokable_xoff__initgfx */

/* GFX functions for memory-based video buffers (without GPU support) */
INTERN ATTR_IN(1) video_color_t CC
LOCAL_ramgfx__getcolor_noblend(struct video_gfx const *__restrict self,
                               video_coord_t x, video_coord_t y) {
	video_color_t result;
	byte_t const *line;
	LOCAL_GFX_LOCK();
	line   = LOCAL_GFX_DATA + y * LOCAL_GFX_STRIDE;
	result = video_format_getcolor(LOCAL_GFX_FORMAT, line, x + LOCAL_GFX_XOFF);
	LOCAL_GFX_UNLOCK();
	return result;
}

INTERN ATTR_IN(1) video_color_t CC
LOCAL_ramgfx__getcolor_withkey(struct video_gfx const *__restrict self,
                               video_coord_t x, video_coord_t y) {
	byte_t const *line;
	video_color_t result;
	LOCAL_GFX_LOCK();
	line   = LOCAL_GFX_DATA + y * LOCAL_GFX_STRIDE;
	result = video_format_getcolor(LOCAL_GFX_FORMAT, line, x + LOCAL_GFX_XOFF);
	LOCAL_GFX_UNLOCK();
	if (result == self->vx_colorkey)
		result = 0;
	return result;
}

INTERN ATTR_IN(1) void CC
LOCAL_ramgfx__putcolor(struct video_gfx const *__restrict self,
                       video_coord_t x, video_coord_t y,
                       video_color_t color) {
	/* Perform full color blending. */
	video_color_t o, n;
	byte_t *line;
	x += LOCAL_GFX_XOFF;
	LOCAL_GFX_LOCK();
	line = LOCAL_GFX_DATA + y * LOCAL_GFX_STRIDE;
	o    = video_format_getcolor(LOCAL_GFX_FORMAT, line, x);
	n    = gfx_blendcolors(o, color, self->vx_blend);
	video_format_setcolor(LOCAL_GFX_FORMAT, line, x, n);
	LOCAL_GFX_UNLOCK();
}

INTERN ATTR_IN(1) void CC
LOCAL_ramgfx__putcolor_noblend(struct video_gfx const *__restrict self,
                               video_coord_t x, video_coord_t y,
                               video_color_t color) {
	byte_t *line;
	LOCAL_GFX_LOCK();
	line = LOCAL_GFX_DATA + y * LOCAL_GFX_STRIDE;
	video_format_setcolor(LOCAL_GFX_FORMAT, line, x + LOCAL_GFX_XOFF, color);
	LOCAL_GFX_UNLOCK();
}

#define DEFINE_LOCAL_ramgfx__putcolor_FOO(name, mode)                        \
	INTERN ATTR_IN(1) void CC                                                \
	LOCAL_ramgfx__(putcolor_##name)(struct video_gfx const *__restrict self, \
	                                video_coord_t x, video_coord_t y,        \
	                                video_color_t color) {                   \
		byte_t *line;                                                        \
		video_color_t o, n;                                                  \
		x += LOCAL_GFX_XOFF;                                                 \
		LOCAL_GFX_LOCK();                                                    \
		line = LOCAL_GFX_DATA + y * LOCAL_GFX_STRIDE;                        \
		o    = video_format_getcolor(LOCAL_GFX_FORMAT, line, x);             \
		n    = gfx_blendcolors(o, color, mode);                              \
		video_format_setcolor(LOCAL_GFX_FORMAT, line, x, n);                 \
		LOCAL_GFX_UNLOCK();                                                  \
	}
GFX_FOREACH_DEDICATED_BLENDMODE(DEFINE_LOCAL_ramgfx__putcolor_FOO)
#undef DEFINE_LOCAL_ramgfx__putcolor_FOO

#define DEFINE_LOCAL_ramgfx__putcolor_FOO(name, mode)                        \
	INTERN ATTR_IN(1) void CC                                                \
	LOCAL_ramgfx__(putcolor_##name)(struct video_gfx const *__restrict self, \
	                                video_coord_t x, video_coord_t y,        \
	                                video_color_t color) {                   \
		byte_t *line;                                                        \
		video_color_t o, c, n;                                               \
		x += LOCAL_GFX_XOFF;                                                 \
		LOCAL_GFX_LOCK();                                                    \
		line = LOCAL_GFX_DATA + y * LOCAL_GFX_STRIDE;                        \
		o    = video_format_getcolor(LOCAL_GFX_FORMAT, line, x);             \
		c    = GFX_BLENDMODE_GET_COLOR(self->vx_blend);                      \
		n    = gfx_blendcolors_constant(o, color, mode, c);                  \
		video_format_setcolor(LOCAL_GFX_FORMAT, line, x, n);                 \
		LOCAL_GFX_UNLOCK();                                                  \
	}
GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(DEFINE_LOCAL_ramgfx__putcolor_FOO)
#undef DEFINE_LOCAL_ramgfx__putcolor_FOO
;

INTERN ATTR_IN(1) video_pixel_t CC
LOCAL_ramgfx__getpixel(struct video_gfx const *__restrict self,
                       video_coord_t x, video_coord_t y) {
	video_pixel_t result;
	byte_t const *line;
	LOCAL_GFX_LOCK();
	line   = LOCAL_GFX_DATA + y * LOCAL_GFX_STRIDE;
	result = (*LOCAL_GFX_FORMAT->vf_codec->vc_getpixel)(line, x + LOCAL_GFX_XOFF);
	LOCAL_GFX_UNLOCK();
	return result;
}

INTERN ATTR_IN(1) void CC
LOCAL_ramgfx__setpixel(struct video_gfx const *__restrict self,
                       video_coord_t x, video_coord_t y,
                       video_pixel_t pixel) {
	byte_t *line;
	LOCAL_GFX_LOCK();
	line = LOCAL_GFX_DATA + y * LOCAL_GFX_STRIDE;
	(*LOCAL_GFX_FORMAT->vf_codec->vc_setpixel)(line, x + LOCAL_GFX_XOFF, pixel);
	LOCAL_GFX_UNLOCK();
}


#ifdef CONFIG_HAVE_OLD_RAMBUFFER_PIXELn_FASTPASS
#define DEFINE_RAMGFX_GETSETPIXELn(n)                                  \
	INTERN ATTR_IN(1) video_pixel_t CC                                 \
	LOCAL_ramgfx__getpixel##n(struct video_gfx const *__restrict self, \
	                          video_coord_t x, video_coord_t y) {      \
		uint##n##_t result;                                            \
		byte_t const *line;                                            \
		LOCAL_GFX_LOCK();                                              \
		line   = LOCAL_GFX_DATA + y * LOCAL_GFX_STRIDE;                \
		result = ((uint##n##_t const *)line)[x + LOCAL_GFX_XOFF];      \
		LOCAL_GFX_UNLOCK();                                            \
		return result;                                                 \
	}                                                                  \
	                                                                   \
	INTERN ATTR_IN(1) void CC                                          \
	LOCAL_ramgfx__setpixel##n(struct video_gfx const *__restrict self, \
	                          video_coord_t x, video_coord_t y,        \
	                          video_pixel_t pixel) {                   \
		byte_t *line;                                                  \
		LOCAL_GFX_LOCK();                                              \
		line = LOCAL_GFX_DATA + y * LOCAL_GFX_STRIDE;                  \
		((uint##n##_t *)line)[x + LOCAL_GFX_XOFF] = pixel;             \
		LOCAL_GFX_UNLOCK();                                            \
	}
DEFINE_RAMGFX_GETSETPIXELn(8)
DEFINE_RAMGFX_GETSETPIXELn(16)
DEFINE_RAMGFX_GETSETPIXELn(32)
#undef DEFINE_RAMGFX_GETSETPIXELn

#ifndef UNION_PIXEL24_DEFINED
#define UNION_PIXEL24_DEFINED
union pixel24 {
	video_pixel_t pixel;
	byte_t        bytes[3];
};
#endif /* !UNION_PIXEL24_DEFINED */

INTERN ATTR_IN(1) video_pixel_t CC
LOCAL_ramgfx__getpixel24(struct video_gfx const *__restrict self,
                         video_coord_t x, video_coord_t y) {
	union pixel24 result;
	byte_t const *line;
	LOCAL_GFX_LOCK();
	line = LOCAL_GFX_DATA + y * LOCAL_GFX_STRIDE;
	line += (x + LOCAL_GFX_XOFF) * 3;
	result.bytes[0] = line[0];
	result.bytes[1] = line[1];
	result.bytes[2] = line[2];
	result.bytes[3] = 0;
	LOCAL_GFX_UNLOCK();
	return result.pixel;
}

INTERN ATTR_IN(1) void CC
LOCAL_ramgfx__setpixel24(struct video_gfx const *__restrict self,
                         video_coord_t x, video_coord_t y,
                         video_pixel_t pixel) {
	union pixel24 data;
	byte_t *line;
	LOCAL_GFX_LOCK();
	line = LOCAL_GFX_DATA + y * LOCAL_GFX_STRIDE;
	line += (x + LOCAL_GFX_XOFF) * 3;
	data.pixel = pixel;
	line[0] = data.bytes[0];
	line[1] = data.bytes[1];
	line[2] = data.bytes[2];
	LOCAL_GFX_UNLOCK();
}
#endif /* CONFIG_HAVE_OLD_RAMBUFFER_PIXELn_FASTPASS */


#undef LOCAL_GFX_LOCK
#undef LOCAL_GFX_UNLOCK
#undef LOCAL_GFX_DATA
#undef LOCAL_GFX_STRIDE
#undef LOCAL_GFX_FORMAT
#undef LOCAL_GFX_XOFF

#undef LINK_LOCAL_ramgfx__putcolor_FOO
#undef LINK_LOCAL_ramgfx__putcolor_preblend_FOO

#undef LOCAL_rambuffer__initgfx
#undef LOCAL_rambuffer__updategfx
#undef LOCAL_ramgfx__
#undef LOCAL_ramgfx__getcolor_noblend
#undef LOCAL_ramgfx__getcolor_withkey
#undef LOCAL_ramgfx__putcolor
#undef LOCAL_ramgfx__putcolor_noblend
#undef LOCAL_ramgfx__getpixel
#undef LOCAL_ramgfx__setpixel
#undef LOCAL_ramgfx__getpixel8
#undef LOCAL_ramgfx__getpixel16
#undef LOCAL_ramgfx__getpixel24
#undef LOCAL_ramgfx__getpixel32
#undef LOCAL_ramgfx__setpixel8
#undef LOCAL_ramgfx__setpixel16
#undef LOCAL_ramgfx__setpixel24
#undef LOCAL_ramgfx__setpixel32

DECL_END

#undef DEFINE_rambuffer_revokable_xoff__initgfx
#undef DEFINE_rambuffer_revokable__initgfx
#undef DEFINE_rambuffer__initgfx
