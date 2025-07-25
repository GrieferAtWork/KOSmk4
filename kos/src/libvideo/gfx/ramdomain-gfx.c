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
#ifndef GUARD_LIBVIDEO_GFX_RAMDOMAIN_GFX_C
#define GUARD_LIBVIDEO_GFX_RAMDOMAIN_GFX_C 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libvideo/color.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/blendcolors.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/surface.h>
#include <libvideo/types.h>

#include "gfx-utils.h"
#include "gfx.h"
#include "ramdomain.h"
#include "swgfx.h"

DECL_BEGIN

#define LINK_LOCAL_ramgfx__putcolor_FOO(name, mode)   \
	case mode:                                        \
		drv->xsw_putcolor = &ramgfx__putcolor_##name; \
		break;
#define LINK_LOCAL_ramgfx__putcolor_preblend_FOO(name, mode, preblend_name, preblend) \
	case mode:                                                                        \
		drv->xsw_putcolor_p = &ramgfx__putcolor_##preblend_name;                      \
		break;

PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
rambuffer__initgfx_common(struct video_gfx *__restrict self) {
	static_assert(sizeof(struct gfx_ramdrv) <= (_VIDEO_GFX_N_DRIVER * sizeof(void *)));
	struct video_rambuffer *me = (struct video_rambuffer *)video_gfx_getbuffer(self);
	struct gfx_ramdrv *drv = video_ramgfx_getdrv(self);
	drv->grd_codec  = video_buffer_getcodec(me);
	drv->grd_stride = me->rb_stride;
	drv->grd_data   = me->rb_data;

	/* Default pixel accessors */
	drv->xsw_getpixel = &ramgfx__getpixel;
	drv->xsw_setpixel = &ramgfx__setpixel;

	/* Load optimized pixel accessors if applicable to the loaded format. */
#ifdef CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS
	switch (video_buffer_getcodec(me)->vc_specs.vcs_bpp) {
	case 8:
		drv->xsw_setpixel = &ramgfx__setpixel8;
		drv->xsw_getpixel = &ramgfx__getpixel8;
		break;
	case 16:
		drv->xsw_setpixel = &ramgfx__setpixel16;
		drv->xsw_getpixel = &ramgfx__getpixel16;
		break;
	case 24:
		drv->xsw_setpixel = &ramgfx__setpixel24;
		drv->xsw_getpixel = &ramgfx__getpixel24;
		break;
	case 32:
		drv->xsw_setpixel = &ramgfx__setpixel32;
		drv->xsw_getpixel = &ramgfx__getpixel32;
		break;
	default: break;
	}
#endif /* CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS */

	/* Load generic operator defaults (overwritten as appropriate below) */
	libvideo_swgfx_populate(self);

	/* Select how colors should be read. */
	drv->xsw_getcolor = &ramgfx__getcolor;

	/* Detect special blend modes. */
	(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_OVERRIDE);
	(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_ALPHA);
	switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
	case GFX_BLENDMODE_OVERRIDE:
		drv->xsw_putcolor = &ramgfx__putcolor_noblend;
		break;
	GFX_FOREACH_DEDICATED_BLENDMODE(LINK_LOCAL_ramgfx__putcolor_FOO)
	GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(LINK_LOCAL_ramgfx__putcolor_FOO)
	default: drv->xsw_putcolor = &ramgfx__putcolor; break;
	}
	switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
	GFX_FOREACH_DEDICATED_PREBLENDMODE(LINK_LOCAL_ramgfx__putcolor_preblend_FOO)
	default: drv->xsw_putcolor_p = drv->xsw_putcolor; break;
	}

	/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
	if (video_buffer_getcodec(me)->vc_codec == VIDEO_CODEC_RGBA8888) {
		if (drv->xsw_getcolor == &ramgfx__getcolor)
			drv->xsw_getcolor = drv->xsw_getpixel;
		if (drv->xsw_putcolor == &ramgfx__putcolor_noblend) {
			drv->xsw_putcolor   = drv->xsw_setpixel;
			drv->xsw_putcolor_p = drv->xsw_setpixel;
		}
	}
	/* ... */

	return self;
}

/* GFX */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
rambuffer__initgfx(struct video_gfx *__restrict self) {
	/* Initialize GFX as a full clip */
	libvideo_gfx_init_fullclip(self);
	return rambuffer__initgfx_common(self);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
rambuffer__updategfx(struct video_gfx *__restrict self, unsigned int what) {
	struct gfx_ramdrv *drv = video_ramgfx_getdrv(self);

	/* Updated generic operators */
	libvideo_swgfx_update(self, what);

	/* Select how colors should be read. */
	if (what & (VIDEO_GFX_UPDATE_FLAGS | VIDEO_GFX_UPDATE_COLORKEY)) {
		drv->xsw_getcolor = &ramgfx__getcolor;
		/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
		if (drv->grd_codec->vc_codec == VIDEO_CODEC_RGBA8888)
			drv->xsw_getcolor = drv->xsw_getpixel;
	}

	/* Detect special blend modes. */
	if (what & VIDEO_GFX_UPDATE_BLEND) {
		(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_OVERRIDE);
		(void)__builtin_expect(GFX_BLENDMODE_GET_MODE(self->vx_blend), GFX_BLENDMODE_ALPHA);
		switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
		case GFX_BLENDMODE_OVERRIDE:
			drv->xsw_putcolor = &ramgfx__putcolor_noblend;
			/* Special optimization for "VIDEO_CODEC_RGBA8888": no color conversion needed */
			if (drv->grd_codec->vc_codec == VIDEO_CODEC_RGBA8888)
				drv->xsw_putcolor = drv->xsw_setpixel;
			break;
		GFX_FOREACH_DEDICATED_BLENDMODE(LINK_LOCAL_ramgfx__putcolor_FOO)
		GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(LINK_LOCAL_ramgfx__putcolor_FOO)
		default: drv->xsw_putcolor = &ramgfx__putcolor; break;
		}
		switch (GFX_BLENDMODE_GET_MODE(self->vx_blend)) {
		GFX_FOREACH_DEDICATED_PREBLENDMODE(LINK_LOCAL_ramgfx__putcolor_preblend_FOO)
		default: drv->xsw_putcolor_p = drv->xsw_putcolor; break;
		}
	}

	return self;
}



INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
rambuffer_subregion__initgfx(struct video_gfx *__restrict self) {
	struct video_rambuffer_subregion *me = (struct video_rambuffer_subregion *)video_gfx_getbuffer(self);
	self->vx_surf.vs_buffer = me->rbs_base;
	if unlikely(video_gfx_getflags(self) & VIDEO_GFX_F_XYSWAP) {
		self->vx_hdr.vxh_cxoff = me->rbs_yoff;
		self->vx_hdr.vxh_cyoff = me->rbs_xoff;
		self->vx_hdr.vxh_cxdim = video_buffer_getydim(me);
		self->vx_hdr.vxh_cydim = video_buffer_getxdim(me);
		self->vx_hdr.vxh_bxmin = me->rbs_yoff;
		self->vx_hdr.vxh_bymin = me->rbs_xoff;
		self->vx_hdr.vxh_bxend = me->rbs_yend;
		self->vx_hdr.vxh_byend = me->rbs_xend;
	} else {
		self->vx_hdr.vxh_cxoff = me->rbs_xoff;
		self->vx_hdr.vxh_cyoff = me->rbs_yoff;
		self->vx_hdr.vxh_cxdim = video_buffer_getxdim(me);
		self->vx_hdr.vxh_cydim = video_buffer_getydim(me);
		self->vx_hdr.vxh_bxmin = me->rbs_xoff;
		self->vx_hdr.vxh_bymin = me->rbs_yoff;
		self->vx_hdr.vxh_bxend = me->rbs_xend;
		self->vx_hdr.vxh_byend = me->rbs_yend;
	}
	return rambuffer__initgfx_common(self);
}

#define RAMGFX_DATA    video_ramgfx_getcdrv(self)->grd_data
#define RAMGFX_CODEC   video_ramgfx_getcdrv(self)->grd_codec
#define RAMGFX_STRIDE  video_ramgfx_getcdrv(self)->grd_stride
#define RAMGFX_LINE(y) (RAMGFX_DATA + (y) * RAMGFX_STRIDE)

/* GFX functions for memory-based video buffers (without GPU support) */
INTERN ATTR_IN(1) video_color_t CC
ramgfx__getcolor(struct video_gfx const *__restrict self,
                 video_coord_t x, video_coord_t y) {
	video_pixel_t pixel = (*RAMGFX_CODEC->vc_getpixel)(RAMGFX_LINE(y), x);
	return (*RAMGFX_CODEC->vc_pixel2color)(video_gfx_assurface(self), pixel);
}

INTERN ATTR_IN(1) void CC
ramgfx__putcolor(struct video_gfx const *__restrict self,
                       video_coord_t x, video_coord_t y,
                       video_color_t color) {
	/* Perform full color blending. */
	byte_t *line = RAMGFX_LINE(y);
	video_pixel_t op = (*RAMGFX_CODEC->vc_getpixel)(line, x);
	video_color_t oc = (*RAMGFX_CODEC->vc_pixel2color)(video_gfx_assurface(self), op);
	video_color_t nc = gfx_blendcolors(oc, color, self->vx_blend);
	video_pixel_t np = (*RAMGFX_CODEC->vc_color2pixel)(video_gfx_assurface(self), nc);
	(*RAMGFX_CODEC->vc_setpixel)(line, x, np);
}

INTERN ATTR_IN(1) void CC
ramgfx__putcolor_noblend(struct video_gfx const *__restrict self,
                         video_coord_t x, video_coord_t y,
                         video_color_t color) {
	video_pixel_t pixel = (*RAMGFX_CODEC->vc_color2pixel)(video_gfx_assurface(self), color);
	(*RAMGFX_CODEC->vc_setpixel)(RAMGFX_LINE(y), x, pixel);
}

#define DEFINE_ramgfx__putcolor_FOO(name, mode)                                            \
	INTERN ATTR_IN(1) void CC                                                              \
	ramgfx__putcolor_##name(struct video_gfx const *__restrict self,                       \
	                        video_coord_t x, video_coord_t y, video_color_t color) {       \
		byte_t *line     = RAMGFX_LINE(y);                                                 \
		video_pixel_t op = (*RAMGFX_CODEC->vc_getpixel)(line, x);                          \
		video_color_t oc = (*RAMGFX_CODEC->vc_pixel2color)(video_gfx_assurface(self), op); \
		video_color_t nc = gfx_blendcolors(oc, color, mode);                               \
		video_pixel_t np = (*RAMGFX_CODEC->vc_color2pixel)(video_gfx_assurface(self), nc); \
		(*RAMGFX_CODEC->vc_setpixel)(line, x, np);                                         \
	}
GFX_FOREACH_DEDICATED_BLENDMODE(DEFINE_ramgfx__putcolor_FOO)
#undef DEFINE_ramgfx__putcolor_FOO
#define DEFINE_ramgfx__putcolor_FOO(name, mode)                                            \
	INTERN ATTR_IN(1) void CC                                                              \
	ramgfx__putcolor_##name(struct video_gfx const *__restrict self,                       \
	                        video_coord_t x, video_coord_t y, video_color_t color) {       \
		byte_t *line     = RAMGFX_LINE(y);                                                 \
		video_pixel_t op = (*RAMGFX_CODEC->vc_getpixel)(line, x);                          \
		video_color_t oc = (*RAMGFX_CODEC->vc_pixel2color)(video_gfx_assurface(self), op); \
		video_color_t cc = GFX_BLENDMODE_GET_COLOR(self->vx_blend);                        \
		video_color_t nc = gfx_blendcolors_constant(oc, color, mode, cc);                  \
		video_pixel_t np = (*RAMGFX_CODEC->vc_color2pixel)(video_gfx_assurface(self), nc); \
		(*RAMGFX_CODEC->vc_setpixel)(line, x, np);                                         \
	}
GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(DEFINE_ramgfx__putcolor_FOO)
#undef DEFINE_ramgfx__putcolor_FOO
;


INTERN ATTR_IN(1) video_pixel_t CC
ramgfx__getpixel(struct video_gfx const *__restrict self,
                 video_coord_t x, video_coord_t y) {
	return (*RAMGFX_CODEC->vc_getpixel)(RAMGFX_LINE(y), x);
}

INTERN ATTR_IN(1) void CC
ramgfx__setpixel(struct video_gfx const *__restrict self,
                 video_coord_t x, video_coord_t y, video_pixel_t pixel) {
	(*RAMGFX_CODEC->vc_setpixel)(RAMGFX_LINE(y), x, pixel);
}

#ifdef CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS
#define DEFINE_RAMGFX_GETSETPIXELn(n)                            \
	INTERN ATTR_IN(1) video_pixel_t CC                           \
	ramgfx__getpixel##n(struct video_gfx const *__restrict self, \
	                    video_coord_t x, video_coord_t y) {      \
		return ((uint##n##_t const *)RAMGFX_LINE(y))[x];         \
	}                                                            \
	INTERN ATTR_IN(1) void CC                                    \
	ramgfx__setpixel##n(struct video_gfx const *__restrict self, \
	                    video_coord_t x, video_coord_t y,        \
	                    video_pixel_t pixel) {                   \
		((uint##n##_t *)RAMGFX_LINE(y))[x] = pixel;              \
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
ramgfx__getpixel24(struct video_gfx const *__restrict self,
                   video_coord_t x, video_coord_t y) {
	union pixel24 result;
	byte_t const *vmem = RAMGFX_LINE(y) + x * 3;
	result.bytes[0] = vmem[0];
	result.bytes[1] = vmem[1];
	result.bytes[2] = vmem[2];
	result.bytes[3] = 0;
	return result.pixel;
}

INTERN ATTR_IN(1) void CC
ramgfx__setpixel24(struct video_gfx const *__restrict self,
                   video_coord_t x, video_coord_t y,
                   video_pixel_t pixel) {
	union pixel24 data;
	byte_t *vmem = RAMGFX_LINE(y) + x * 3;
	data.pixel = pixel;
	vmem[0] = data.bytes[0];
	vmem[1] = data.bytes[1];
	vmem[2] = data.bytes[2];
}
#endif /* CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS */

#undef RAMGFX_DATA
#undef RAMGFX_CODEC
#undef RAMGFX_STRIDE
#undef RAMGFX_LINE

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_RAMDOMAIN_GFX_C */
