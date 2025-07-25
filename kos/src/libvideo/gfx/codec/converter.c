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
#ifndef GUARD_LIBVIDEO_GFX_CODEC_CONVERTER_C
#define GUARD_LIBVIDEO_GFX_CODEC_CONVERTER_C 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/byteswap.h>

#include <sys/param.h>

#include <stdint.h>

#include <libvideo/color.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/codec/converter.h>
#include <libvideo/gfx/codec/palette.h>
#include <libvideo/gfx/surface-defs.h>
#include <libvideo/gfx/surface.h>

#include "codec-utils.h"
#include "converter.h"
#include "palette.h"

#ifndef BITSOF
#define BITSOF(x) (sizeof(x) * NBBY)
#endif /* !BITSOF */

DECL_BEGIN

#define getdrv(T)  ((T *)self->_vcv_ydriver)
#define getcdrv(T) ((T const *)self->_vcv_ydriver)

/************************************************************************/
/* PIXEL MAPPERS (COMMON)                                               */
/************************************************************************/
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_identity(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	(void)self;
	COMPILER_IMPURE();
	return from_pixel;
}

/* X to X */
struct data__map_x_to_x {
	struct video_surface mx2x_from;
	struct video_surface mx2x_to;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_x_to_x(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_x_to_x const *drv = getcdrv(struct data__map_x_to_x);
	video_color_t color = video_surface_pixel2color(&drv->mx2x_from, from_pixel);
	return video_surface_color2pixel(&drv->mx2x_to, color);
}

/* X to P(obj) */
struct data__map_x_to_po {
	struct video_surface        mx2po_from;
	struct video_palette const *mx2po_to;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_x_to_po(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_x_to_po const *drv = getcdrv(struct data__map_x_to_po);
	video_color_t color = video_surface_pixel2color(&drv->mx2po_from, from_pixel);
	return video_palette_color2pixel(drv->mx2po_to, color);
}

/* X to P(raw) */
struct data__map_x_to_pr {
	struct video_surface        mx2pr_from;
	struct video_palette const *mx2pr_to;
	video_pixel_t               mx2pr_to_n_colors;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_x_to_pr(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_x_to_pr const *drv = getcdrv(struct data__map_x_to_pr);
	video_color_t color = video_surface_pixel2color(&drv->mx2pr_from, from_pixel);
	return libvideo_palette_color2pixel_generic(drv->mx2pr_to, drv->mx2pr_to_n_colors, color);
}

/* X to RGBA8888 */
struct data__map_x_to_rgba8888 {
	struct video_surface mx2rgba8888_from;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_x_to_rgba8888(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_x_to_rgba8888 const *drv = getcdrv(struct data__map_x_to_rgba8888);
	return video_surface_pixel2color(&drv->mx2rgba8888_from, from_pixel);
}

/* RGBA8888 to P(obj) */
struct data__map_rgba8888_to_po {
	struct video_palette const *mrgba88882po_to;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_rgba8888_to_po(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_rgba8888_to_po const *drv = getcdrv(struct data__map_rgba8888_to_po);
	return video_palette_color2pixel(drv->mrgba88882po_to, from_pixel);
}

/* RGBA8888 to P(raw) */
struct data__map_rgba8888_to_pr {
	struct video_palette const *mrgba88882pr_to;
	video_pixel_t               mrgba88882pr_n_colors;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_rgba8888_to_pr(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_rgba8888_to_pr const *drv = getcdrv(struct data__map_rgba8888_to_pr);
	return libvideo_palette_color2pixel_generic(drv->mrgba88882pr_to, drv->mrgba88882pr_n_colors, from_pixel);
}

/* RGBA8888 to X */
struct data__map_rgba8888_to_x {
	struct video_surface mrgba88882x_to;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_rgba8888_to_x(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_rgba8888_to_x const *drv = getcdrv(struct data__map_rgba8888_to_x);
	return video_surface_color2pixel(&drv->mrgba88882x_to, from_pixel);
}

/* RGBX8888 to P(obj) */
struct data__map_rgbx8888_to_po {
	struct video_palette const *mrgbx88882po_to;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_rgbx8888_to_po(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_rgbx8888_to_po const *drv = getcdrv(struct data__map_rgbx8888_to_po);
	video_color_t color = from_pixel | VIDEO_COLOR_ALPHA_MASK;
	return video_palette_color2pixel(drv->mrgbx88882po_to, color);
}

/* RGBX8888 to P(raw) */
struct data__map_rgbx8888_to_pr {
	struct video_palette const *mrgbx88882pr_to;
	video_pixel_t               mrgbx88882pr_n_colors;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_rgbx8888_to_pr(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_rgbx8888_to_pr const *drv = getcdrv(struct data__map_rgbx8888_to_pr);
	video_color_t color = from_pixel | VIDEO_COLOR_ALPHA_MASK;
	return libvideo_palette_color2pixel_generic(drv->mrgbx88882pr_to, drv->mrgbx88882pr_n_colors, color);
}

/* RGBX8888 to X */
struct data__map_rgbx8888_to_x {
	struct video_surface mrgbx88882x_to;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_rgbx8888_to_x(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_rgbx8888_to_x const *drv = getcdrv(struct data__map_rgbx8888_to_x);
	video_color_t color = from_pixel | VIDEO_COLOR_ALPHA_MASK;
	return video_surface_color2pixel(&drv->mrgbx88882x_to, color);
}


/************************************************************************/
/* PIXEL MAPPERS (PALETTE SOURCE)                                       */
/************************************************************************/

struct data__map_p256 {
	video_pixel_t mp256_pixels[256];
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_p256(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_p256 const *drv = getcdrv(struct data__map_p256);
	codec_assert(from_pixel < 256);
	return drv->mp256_pixels[from_pixel];
}

struct data__map_p2po {
	struct video_palette const *mp2po_from;
	struct video_palette const *mp2po_to;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_p_to_po(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_p2po const *drv = getcdrv(struct data__map_p2po);
	video_color_t color = video_palette_pixel2color(drv->mp2po_from, from_pixel);
	return video_palette_color2pixel(drv->mp2po_to, color);
}

struct data__map_p2pr {
	struct video_palette const *mp2pr_from;
	struct video_palette const *mp2pr_to;
	video_pixel_t               mp2pr_to_n_colors;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_p_to_pr(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_p2pr const *drv = getcdrv(struct data__map_p2pr);
	video_color_t color = video_palette_pixel2color(drv->mp2pr_from, from_pixel);
	return libvideo_palette_color2pixel_generic(drv->mp2pr_to, drv->mp2pr_to_n_colors, color);
}

struct data__map_p2x {
	struct video_palette const *mp2x_from;
	struct video_surface        mp2x_to;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_p_to_x(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_p2x const *drv = getcdrv(struct data__map_p2x);
	video_color_t color = video_palette_pixel2color(drv->mp2x_from, from_pixel);
	return video_surface_color2pixel(&drv->mp2x_to, color);
}

struct data__map_p2rgba8888 {
	struct video_palette const *mp2x_from;
};
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_p_to_rgba8888(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	struct data__map_p2rgba8888 const *drv = getcdrv(struct data__map_p2rgba8888);
	return video_palette_pixel2color(drv->mp2x_from, from_pixel);
}


/************************************************************************/
/* PIXEL MAPPERS (RGB(A) SOURCE)                                        */
/************************************************************************/
#if __SIZEOF_VIDEO_PIXEL_T__ == 4
#define PIXEL_BITS  32
#define px_bswap(x) BSWAP32(x)
#else /* __SIZEOF_VIDEO_PIXEL_T__ == ... */
#define PIXEL_BITS BITSOF(video_pixel_t)
#error "Unsupported '__SIZEOF_VIDEO_PIXEL_T__'"
#endif /* __SIZEOF_VIDEO_PIXEL_T__ != ... */
#define px_shl(x, n) ((video_pixel_t)(x) << (n))
#define px_shr(x, n) ((video_pixel_t)(x) >> (n))
#define px_rol(x, n) (((video_pixel_t)(x) << (n)) | ((video_pixel_t)(x) >> (PIXEL_BITS - (n))))
#define px_ror(x, n) (((video_pixel_t)(x) >> (n)) | ((video_pixel_t)(x) << (PIXEL_BITS - (n))))

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_shl8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	return px_shl(from_pixel, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_rol8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	return px_rol(from_pixel, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_shr8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	return px_shr(from_pixel, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_ror8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	return px_ror(from_pixel, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_rol16(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	return px_rol(from_pixel, 16);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_shl8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return px_shl(from_pixel, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_rol8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return px_rol(from_pixel, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_shr8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return px_shr(from_pixel, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_ror8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return px_ror(from_pixel, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_rol16_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return px_rol(from_pixel, 16) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_bswap(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	return px_bswap(from_pixel);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_bswap_shl8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_shl(temp, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_bswap_rol8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_rol(temp, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_bswap_shr8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_shr(temp, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_bswap_ror8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_ror(temp, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_bswap_rol16(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_rol(temp, 16);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_bswap_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return px_bswap(from_pixel) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_bswap_shl8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_shl(temp, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_bswap_rol8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_rol(temp, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_bswap_shr8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_shr(temp, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_bswap_ror8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_ror(temp, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t FCC
map_bswap_rol16_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_rol(temp, 16) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}







/************************************************************************/
/* PIXEL CONVERSION INITIALIZERS                                        */
/************************************************************************/

PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC
initconv_from_generic(struct video_converter *__restrict self) {
	struct video_surface const *from = self->vcv_from;
	struct video_surface const *to = self->vcv_to;
	struct video_codec const *from_codec = video_surface_getcodec(from);
	struct video_codec const *to_codec = video_surface_getcodec(to);
	if (from_codec == to_codec && (video_surface_getpalette(from) ==
	                               video_surface_getpalette(to))) {
		self->vcv_mappixel = &map_identity; /* No conversion is happening */
	} else if (from_codec->vc_specs.vcs_bpp <= 8) {
		/* Use map256 conversion */
		video_pixel_t i, count = 1 << from_codec->vc_specs.vcs_bpp;
		struct data__map_p256 *drv = getdrv(struct data__map_p256);
		self->vcv_mappixel = &map_p256;
		for (i = 0; i < count; ++i) {
			video_color_t color = video_surface_pixel2color(from, i);
			video_pixel_t pixel = video_surface_color2pixel(to, color);
			drv->mp256_pixels[i] = pixel;
		}
	} else if (to_codec->vc_color2pixel == &pal_color2pixel) {
		if (from_codec->vc_pixel2color == &identity_pixel2color) {
			if (video_surface_hasobjpalette(to)) {
				struct data__map_rgba8888_to_po *drv = getdrv(struct data__map_rgba8888_to_po);
				drv->mrgba88882po_to = video_surface_getpalette(to);
				self->vcv_mappixel = &map_rgba8888_to_po; /* RGBA8888 to palette(obj) */
			} else {
				struct data__map_rgba8888_to_pr *drv = getdrv(struct data__map_rgba8888_to_pr);
				drv->mrgba88882pr_to       = video_surface_getpalette(to);
				drv->mrgba88882pr_n_colors = video_codec_getpalcolors(to_codec);
				self->vcv_mappixel = &map_rgba8888_to_pr; /* RGBA8888 to palette(raw) */
			}
		} else if (from_codec->vc_pixel2color == &rgbx8888_pixel2color) {
			if (video_surface_hasobjpalette(to)) {
				struct data__map_rgbx8888_to_po *drv = getdrv(struct data__map_rgbx8888_to_po);
				drv->mrgbx88882po_to = video_surface_getpalette(to);
				self->vcv_mappixel = &map_rgbx8888_to_po; /* RGBX8888 to palette(obj) */
			} else {
				struct data__map_rgbx8888_to_pr *drv = getdrv(struct data__map_rgbx8888_to_pr);
				drv->mrgbx88882pr_to       = video_surface_getpalette(to);
				drv->mrgbx88882pr_n_colors = video_codec_getpalcolors(to_codec);
				self->vcv_mappixel = &map_rgbx8888_to_pr; /* RGBX8888 to palette(raw) */
			}
		} else if (video_surface_hasobjpalette(to)) {
			struct data__map_x_to_po *drv = getdrv(struct data__map_x_to_po);
			drv->mx2po_from = *from, drv->mx2po_to = video_surface_getpalette(to);
			self->vcv_mappixel = &map_x_to_po; /* Anything to palette(obj) */
		} else {
			struct data__map_x_to_pr *drv = getdrv(struct data__map_x_to_pr);
			drv->mx2pr_from        = *from;
			drv->mx2pr_to          = video_surface_getpalette(to);
			drv->mx2pr_to_n_colors = video_codec_getpalcolors(to_codec);
			self->vcv_mappixel = &map_x_to_pr; /* Anything to palette(raw) */
		}
	} else if (to_codec->vc_color2pixel == &identity_color2pixel) {
		struct data__map_x_to_rgba8888 *drv = getdrv(struct data__map_x_to_rgba8888);
		drv->mx2rgba8888_from = *from;
		self->vcv_mappixel = &map_x_to_rgba8888; /* Anything to RGBA8888 */
	} else if (from_codec->vc_pixel2color == &identity_pixel2color) {
		struct data__map_rgba8888_to_x *drv = getdrv(struct data__map_rgba8888_to_x);
		drv->mrgba88882x_to = *to;
		self->vcv_mappixel = &map_rgba8888_to_x; /* RGBA8888 to anything */
	} else if (from_codec->vc_pixel2color == &rgbx8888_pixel2color) {
		struct data__map_rgbx8888_to_x *drv = getdrv(struct data__map_rgbx8888_to_x);
		drv->mrgbx88882x_to = *to;
		self->vcv_mappixel = &map_rgbx8888_to_x; /* RGBX8888 to anything */
	} else {
		struct data__map_x_to_x *drv = getdrv(struct data__map_x_to_x);
		drv->mx2x_from = *from, drv->mx2x_to = *to;
		self->vcv_mappixel = &map_x_to_x; /* Anything to anything */
	}
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC
initconv_from_p(struct video_converter *__restrict self) {
	struct video_surface const *from = self->vcv_from;
	struct video_surface const *to = self->vcv_to;
	struct video_codec const *from_codec = video_surface_getcodec(from);
	struct video_codec const *to_codec = video_surface_getcodec(to);
	struct video_palette const *from_pal = video_surface_getpalette(from);
	if unlikely(from_codec->vc_pixel2color != &pal_pixel2color ||
	            from_codec->vc_specs.vcs_bpp <= 8) /* Let generic conversion do map256 */
		return initconv_from_generic(self);
	if (from_pal == video_surface_getpalette(to)) {
		self->vcv_mappixel = &map_identity;
		goto done;
	}

	/* Fallback for large palettes. */
	if (to_codec->vc_color2pixel == &pal_color2pixel) {
		if (video_surface_hasobjpalette(to)) {
			struct data__map_p2po *drv = getdrv(struct data__map_p2po);
			drv->mp2po_from = from_pal;
			drv->mp2po_to = video_surface_getpalette(to);
			self->vcv_mappixel = &map_p_to_po;
		} else {
			struct data__map_p2pr *drv = getdrv(struct data__map_p2pr);
			drv->mp2pr_from = from_pal;
			drv->mp2pr_to          = video_surface_getpalette(to);
			drv->mp2pr_to_n_colors = video_codec_getpalcolors(to_codec);
			self->vcv_mappixel = &map_p_to_pr;
		}
	} else if (to_codec->vc_color2pixel == &identity_color2pixel) {
		struct data__map_p2rgba8888 *drv = getdrv(struct data__map_p2rgba8888);
		drv->mp2x_from = from_pal;
		self->vcv_mappixel = &map_p_to_rgba8888;
	} else {
		struct data__map_p2x *drv = getdrv(struct data__map_p2x);
		drv->mp2x_from = from_pal, drv->mp2x_to = *to;
		self->vcv_mappixel = &map_p_to_x;
	}
done:
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC
initconv_from_pa(struct video_converter *__restrict self) {
	return initconv_from_generic(self);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC
initconv_from_l(struct video_converter *__restrict self) {
	/* TODO: Optimization for conversion to RGB(A) formats */
	/* TODO: Optimization for conversion to other L-formats */
	return initconv_from_generic(self);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC
initconv_from_la(struct video_converter *__restrict self) {
	/* TODO: Optimization for conversion to RGB(A) formats */
	/* TODO: Optimization for conversion to other LA-formats */
	return initconv_from_generic(self);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC
initconv_from_a(struct video_converter *__restrict self) {
	/* TODO: Optimization for conversion to RGB(A) formats */
	/* TODO: Optimization for conversion to other A-formats */
	return initconv_from_generic(self);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC
initconv_from_rgb(struct video_converter *__restrict self) {
	struct video_codec const *from_codec = video_surface_getcodec(self->vcv_from);
	struct video_codec const *to_codec = video_surface_getcodec(self->vcv_to);

	/* Optimizations for similar direct-color codecs, where pixels can  be
	 * converted using simple bit operations like bswap and shift / rotate */
	if (!(to_codec->vc_specs.vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM))) {
		self->_vcv_xdriver[0] = (void *)(uintptr_t)to_codec->vc_specs.vcs_amask;
		if (px_shl(from_codec->vc_specs.vcs_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
		    px_shl(from_codec->vc_specs.vcs_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
		    px_shl(from_codec->vc_specs.vcs_bmask, 8) == to_codec->vc_specs.vcs_bmask) {
			self->vcv_mappixel = self->_vcv_xdriver[0] ? &map_shl8_plus_drv0 : &map_shl8;
			goto done;
		} else if (px_shr(from_codec->vc_specs.vcs_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
		           px_shr(from_codec->vc_specs.vcs_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
		           px_shr(from_codec->vc_specs.vcs_bmask, 8) == to_codec->vc_specs.vcs_bmask) {
			self->vcv_mappixel = self->_vcv_xdriver[0] ? &map_shr8_plus_drv0 : &map_shr8;
			goto done;
		} else if (px_rol(from_codec->vc_specs.vcs_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
		           px_rol(from_codec->vc_specs.vcs_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
		           px_rol(from_codec->vc_specs.vcs_bmask, 8) == to_codec->vc_specs.vcs_bmask) {
			self->vcv_mappixel = self->_vcv_xdriver[0] ? &map_rol8_plus_drv0 : &map_rol8;
			goto done;
		} else if (px_ror(from_codec->vc_specs.vcs_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
		           px_ror(from_codec->vc_specs.vcs_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
		           px_ror(from_codec->vc_specs.vcs_bmask, 8) == to_codec->vc_specs.vcs_bmask) {
			self->vcv_mappixel = self->_vcv_xdriver[0] ? &map_ror8_plus_drv0 : &map_ror8;
			goto done;
		} else if (px_rol(from_codec->vc_specs.vcs_rmask, 16) == to_codec->vc_specs.vcs_rmask &&
		           px_rol(from_codec->vc_specs.vcs_gmask, 16) == to_codec->vc_specs.vcs_gmask &&
		           px_rol(from_codec->vc_specs.vcs_bmask, 16) == to_codec->vc_specs.vcs_bmask) {
			self->vcv_mappixel = self->_vcv_xdriver[0] ? &map_rol16_plus_drv0 : &map_rol16;
			goto done;
		} else {
			video_pixel_t sw_from_rmask = px_bswap((video_pixel_t)from_codec->vc_specs.vcs_rmask);
			video_pixel_t sw_from_gmask = px_bswap((video_pixel_t)from_codec->vc_specs.vcs_gmask);
			video_pixel_t sw_from_bmask = px_bswap((video_pixel_t)from_codec->vc_specs.vcs_bmask);
			if (sw_from_rmask == to_codec->vc_specs.vcs_rmask &&
			    sw_from_gmask == to_codec->vc_specs.vcs_gmask &&
			    sw_from_bmask == to_codec->vc_specs.vcs_bmask) {
				self->vcv_mappixel = self->_vcv_xdriver[0] ? &map_bswap_plus_drv0 : &map_bswap;
				goto done;
			} else if (px_shl(sw_from_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
			           px_shl(sw_from_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
			           px_shl(sw_from_bmask, 8) == to_codec->vc_specs.vcs_bmask) {
				self->vcv_mappixel = self->_vcv_xdriver[0] ? &map_bswap_shl8_plus_drv0 : &map_bswap_shl8;
				goto done;
			} else if (px_shr(sw_from_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
			           px_shr(sw_from_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
			           px_shr(sw_from_bmask, 8) == to_codec->vc_specs.vcs_bmask) {
				self->vcv_mappixel = self->_vcv_xdriver[0] ? &map_bswap_shr8_plus_drv0 : &map_bswap_shr8;
				goto done;
			} else if (px_rol(sw_from_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
			           px_rol(sw_from_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
			           px_rol(sw_from_bmask, 8) == to_codec->vc_specs.vcs_bmask) {
				self->vcv_mappixel = self->_vcv_xdriver[0] ? &map_bswap_rol8_plus_drv0 : &map_bswap_rol8;
				goto done;
			} else if (px_ror(sw_from_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
			           px_ror(sw_from_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
			           px_ror(sw_from_bmask, 8) == to_codec->vc_specs.vcs_bmask) {
				self->vcv_mappixel = self->_vcv_xdriver[0] ? &map_bswap_ror8_plus_drv0 : &map_bswap_ror8;
				goto done;
			} else if (px_rol(sw_from_rmask, 16) == to_codec->vc_specs.vcs_rmask &&
			           px_rol(sw_from_gmask, 16) == to_codec->vc_specs.vcs_gmask &&
			           px_rol(sw_from_bmask, 16) == to_codec->vc_specs.vcs_bmask) {
				self->vcv_mappixel = self->_vcv_xdriver[0] ? &map_bswap_rol16_plus_drv0 : &map_bswap_rol16;
				goto done;
			}
		}
	}

	return initconv_from_generic(self);
done:
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *FCC
initconv_from_rgba(struct video_converter *__restrict self) {
	struct video_codec const *from_codec = video_surface_getcodec(self->vcv_from);
	struct video_codec const *to_codec = video_surface_getcodec(self->vcv_to);

	/* Optimizations for similar direct-color codecs, where pixels can  be
	 * converted using simple bit operations like bswap and shift / rotate */
	if (!(to_codec->vc_specs.vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM))) {
		if (px_shl(from_codec->vc_specs.vcs_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
		    px_shl(from_codec->vc_specs.vcs_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
		    px_shl(from_codec->vc_specs.vcs_bmask, 8) == to_codec->vc_specs.vcs_bmask &&
		    px_shl(from_codec->vc_specs.vcs_amask, 8) == to_codec->vc_specs.vcs_amask) {
			self->vcv_mappixel = &map_shl8;
			goto done;
		} else if (px_shr(from_codec->vc_specs.vcs_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
		           px_shr(from_codec->vc_specs.vcs_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
		           px_shr(from_codec->vc_specs.vcs_bmask, 8) == to_codec->vc_specs.vcs_bmask &&
		           px_shr(from_codec->vc_specs.vcs_amask, 8) == to_codec->vc_specs.vcs_amask) {
			self->vcv_mappixel = &map_shr8;
			goto done;
		} else if (px_rol(from_codec->vc_specs.vcs_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
		           px_rol(from_codec->vc_specs.vcs_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
		           px_rol(from_codec->vc_specs.vcs_bmask, 8) == to_codec->vc_specs.vcs_bmask &&
		           px_rol(from_codec->vc_specs.vcs_amask, 8) == to_codec->vc_specs.vcs_amask) {
			self->vcv_mappixel = &map_rol8;
			goto done;
		} else if (px_ror(from_codec->vc_specs.vcs_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
		           px_ror(from_codec->vc_specs.vcs_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
		           px_ror(from_codec->vc_specs.vcs_bmask, 8) == to_codec->vc_specs.vcs_bmask &&
		           px_ror(from_codec->vc_specs.vcs_amask, 8) == to_codec->vc_specs.vcs_amask) {
			self->vcv_mappixel = &map_ror8;
			goto done;
		} else if (px_rol(from_codec->vc_specs.vcs_rmask, 16) == to_codec->vc_specs.vcs_rmask &&
		           px_rol(from_codec->vc_specs.vcs_gmask, 16) == to_codec->vc_specs.vcs_gmask &&
		           px_rol(from_codec->vc_specs.vcs_bmask, 16) == to_codec->vc_specs.vcs_bmask &&
		           px_rol(from_codec->vc_specs.vcs_amask, 16) == to_codec->vc_specs.vcs_amask) {
			self->vcv_mappixel = &map_rol16;
			goto done;
		} else {
			video_pixel_t sw_from_rmask = px_bswap((video_pixel_t)from_codec->vc_specs.vcs_rmask);
			video_pixel_t sw_from_gmask = px_bswap((video_pixel_t)from_codec->vc_specs.vcs_gmask);
			video_pixel_t sw_from_bmask = px_bswap((video_pixel_t)from_codec->vc_specs.vcs_bmask);
			video_pixel_t sw_from_amask = px_bswap((video_pixel_t)from_codec->vc_specs.vcs_amask);
			if (sw_from_rmask == to_codec->vc_specs.vcs_rmask &&
			    sw_from_gmask == to_codec->vc_specs.vcs_gmask &&
			    sw_from_bmask == to_codec->vc_specs.vcs_bmask &&
			    sw_from_amask == to_codec->vc_specs.vcs_amask) {
				self->vcv_mappixel = &map_bswap;
				goto done;
			} else if (px_shl(sw_from_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
			           px_shl(sw_from_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
			           px_shl(sw_from_bmask, 8) == to_codec->vc_specs.vcs_bmask &&
			           px_shl(sw_from_amask, 8) == to_codec->vc_specs.vcs_amask) {
				self->vcv_mappixel = &map_bswap_shl8;
				goto done;
			} else if (px_shr(sw_from_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
			           px_shr(sw_from_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
			           px_shr(sw_from_bmask, 8) == to_codec->vc_specs.vcs_bmask &&
			           px_shr(sw_from_amask, 8) == to_codec->vc_specs.vcs_amask) {
				self->vcv_mappixel = &map_bswap_shr8;
				goto done;
			} else if (px_rol(sw_from_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
			           px_rol(sw_from_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
			           px_rol(sw_from_bmask, 8) == to_codec->vc_specs.vcs_bmask &&
			           px_rol(sw_from_amask, 8) == to_codec->vc_specs.vcs_amask) {
				self->vcv_mappixel = &map_bswap_rol8;
				goto done;
			} else if (px_ror(sw_from_rmask, 8) == to_codec->vc_specs.vcs_rmask &&
			           px_ror(sw_from_gmask, 8) == to_codec->vc_specs.vcs_gmask &&
			           px_ror(sw_from_bmask, 8) == to_codec->vc_specs.vcs_bmask &&
			           px_ror(sw_from_amask, 8) == to_codec->vc_specs.vcs_amask) {
				self->vcv_mappixel = &map_bswap_ror8;
				goto done;
			} else if (px_rol(sw_from_rmask, 16) == to_codec->vc_specs.vcs_rmask &&
			           px_rol(sw_from_gmask, 16) == to_codec->vc_specs.vcs_gmask &&
			           px_rol(sw_from_bmask, 16) == to_codec->vc_specs.vcs_bmask &&
			           px_rol(sw_from_amask, 16) == to_codec->vc_specs.vcs_amask) {
				self->vcv_mappixel = &map_bswap_rol16;
				goto done;
			}
		}
	}
	return initconv_from_generic(self);
done:
	return self;
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_CODEC_CONVERTER_C */
