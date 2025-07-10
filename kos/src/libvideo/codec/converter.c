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
#ifndef GUARD_LIBVIDEO_CODEC_CONVERTER_C
#define GUARD_LIBVIDEO_CODEC_CONVERTER_C 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/byteswap.h>

#include <sys/param.h>

#include <stdint.h>
#include <syslog.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/palette.h>

#include "converter.h"
#include "codec-utils.h"

#ifndef BITSOF
#define BITSOF(x) (sizeof(x) * NBBY)
#endif /* !BITSOF */

DECL_BEGIN

/************************************************************************/
/* PIXEL MAPPERS (COMMON)                                               */
/************************************************************************/
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_identity(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	(void)self;
	COMPILER_IMPURE();
	return from_pixel;
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_x_to_x(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_color_t color = video_format_pixel2color(&self->vcv_from, from_pixel);
	return video_format_color2pixel(&self->vcv_to, color);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_x_to_p(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_color_t color = video_format_pixel2color(&self->vcv_from, from_pixel);
	return video_palette_getpixel(self->vcv_to.vf_pal, color);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_x_to_rgba8888(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return video_format_pixel2color(&self->vcv_from, from_pixel);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_rgba8888_to_p(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return video_palette_getpixel(self->vcv_to.vf_pal, from_pixel);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_rgba8888_to_x(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return video_format_color2pixel(&self->vcv_to, from_pixel);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_rgbx8888_to_p(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_color_t color = from_pixel | VIDEO_COLOR_ALPHA_MASK;
	return video_palette_getpixel(self->vcv_to.vf_pal, color);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_rgbx8888_to_x(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_color_t color = from_pixel | VIDEO_COLOR_ALPHA_MASK;
	return video_format_color2pixel(&self->vcv_to, color);
}


/************************************************************************/
/* PIXEL MAPPERS (PALETTE SOURCE)                                       */
/************************************************************************/
#define video_converter__palmap(self) ((video_pixel_t *)(self)->_vcv_ydriver)
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_p256(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return video_converter__palmap(self)[from_pixel & 0xff];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_p_to_p(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_color_t color = video_palette_getcolor(self->vcv_from.vf_pal, from_pixel);
	return video_palette_getpixel(self->vcv_to.vf_pal, color);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_p_to_x(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_color_t color = video_palette_getcolor(self->vcv_from.vf_pal, from_pixel);
	return video_format_color2pixel(&self->vcv_to, color);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_p_to_rgba8888(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return video_palette_getcolor(self->vcv_from.vf_pal, from_pixel);
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

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_shl8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	return px_shl(from_pixel, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_rol8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	return px_rol(from_pixel, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_shr8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	return px_shr(from_pixel, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_ror8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	return px_ror(from_pixel, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_rol16(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	return px_rol(from_pixel, 16);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_shl8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return px_shl(from_pixel, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_rol8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return px_rol(from_pixel, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_shr8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return px_shr(from_pixel, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_ror8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return px_ror(from_pixel, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_rol16_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return px_rol(from_pixel, 16) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_bswap(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	return px_bswap(from_pixel);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_bswap_shl8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_shl(temp, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_bswap_rol8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_rol(temp, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_bswap_shr8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_shr(temp, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_bswap_ror8(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_ror(temp, 8);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_bswap_rol16(struct video_converter const *__restrict UNUSED(self), video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_rol(temp, 16);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_bswap_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	return px_bswap(from_pixel) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_bswap_shl8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_shl(temp, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_bswap_rol8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_rol(temp, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_bswap_shr8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_shr(temp, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_bswap_ror8_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_ror(temp, 8) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_pixel_t CC
map_bswap_rol16_plus_drv0(struct video_converter const *__restrict self, video_pixel_t from_pixel) {
	video_pixel_t temp = px_bswap(from_pixel);
	return px_rol(temp, 16) | (video_pixel_t)(uintptr_t)self->_vcv_xdriver[0];
}







/************************************************************************/
/* PIXEL CONVERSION INITIALIZERS                                        */
/************************************************************************/

PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *CC
initconv_from_generic(struct video_converter *__restrict self) {
	if (self->vcv_from.vf_codec == self->vcv_to.vf_codec &&
	    self->vcv_from.vf_pal == self->vcv_to.vf_pal) {
		self->vcv_mappixel = &map_identity; /* No conversion is happening */
	} else if (self->vcv_to.vf_codec->vc_color2pixel == &pal_color2pixel) {
		if (self->vcv_from.vf_codec->vc_pixel2color == &identity_pixel2color) {
			self->vcv_mappixel = &map_rgba8888_to_p; /* RGBA8888 to palette */
		} else if (self->vcv_from.vf_codec->vc_pixel2color == &rgbx8888_pixel2color) {
			self->vcv_mappixel = &map_rgbx8888_to_p; /* RGBX8888 to palette */
		} else {
			self->vcv_mappixel = &map_x_to_p; /* Anything to palette */
		}
	} else if (self->vcv_to.vf_codec->vc_color2pixel == &identity_color2pixel) {
		self->vcv_mappixel = &map_x_to_rgba8888; /* Anything to RGBA8888 */
	} else if (self->vcv_from.vf_codec->vc_pixel2color == &identity_pixel2color) {
		self->vcv_mappixel = &map_rgba8888_to_x; /* RGBA8888 to anything */
	} else if (self->vcv_from.vf_codec->vc_pixel2color == &rgbx8888_pixel2color) {
		self->vcv_mappixel = &map_rgbx8888_to_x; /* RGBX8888 to anything */
	} else {
		self->vcv_mappixel = &map_x_to_x; /* Anything to anything */
	}
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *CC
initconv_from_p(struct video_converter *__restrict self) {
	struct video_palette *srcpal;
	if unlikely(self->vcv_from.vf_codec->vc_pixel2color != &pal_pixel2color)
		return initconv_from_generic(self);
	srcpal = self->vcv_from.vf_pal;
	if (srcpal == self->vcv_to.vf_pal) {
		self->vcv_mappixel = &map_identity;
		goto done;
	}

	/* For palettes with indices that fit into a single
	 * byte, we  can precalculate  a conversion  table. */
	if (srcpal->vp_cnt <= 256) {
		/* Precalculate pixel conversion map */
		video_pixel_t srpxl;
		struct video_format dstfmt = self->vcv_to;
		for (srpxl = 0; srpxl < srcpal->vp_cnt; ++srpxl) {
			video_color_t color = srcpal->vp_pal[srpxl];
			video_pixel_t dspxl = video_format_color2pixel(&dstfmt, color);
			video_converter__palmap(self)[srpxl] = dspxl;
		}
		for (; srpxl < 256; ++srpxl)
			video_converter__palmap(self)[srpxl] = 0;
		self->vcv_mappixel = &map_p256;
		goto done;
	}

	/* Fallback for large palettes. */
	if (self->vcv_to.vf_codec->vc_color2pixel == &pal_color2pixel) {
		self->vcv_mappixel = &map_p_to_p;
	} else if (self->vcv_to.vf_codec->vc_color2pixel == &identity_color2pixel) {
		self->vcv_mappixel = &map_p_to_rgba8888;
	} else {
		self->vcv_mappixel = &map_p_to_x;
	}
done:
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *CC
initconv_from_pa(struct video_converter *__restrict self) {
	return initconv_from_generic(self);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *CC
initconv_from_l(struct video_converter *__restrict self) {
	/* TODO: Optimization for conversion to RGB(A) formats */
	/* TODO: Optimization for conversion to other L-formats */
	return initconv_from_generic(self);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *CC
initconv_from_la(struct video_converter *__restrict self) {
	/* TODO: Optimization for conversion to RGB(A) formats */
	/* TODO: Optimization for conversion to other LA-formats */
	return initconv_from_generic(self);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *CC
initconv_from_a(struct video_converter *__restrict self) {
	/* TODO: Optimization for conversion to RGB(A) formats */
	/* TODO: Optimization for conversion to other A-formats */
	return initconv_from_generic(self);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *CC
initconv_from_rgb(struct video_converter *__restrict self) {
	struct video_codec const *from_codec = self->vcv_from.vf_codec;
	struct video_codec const *to_codec = self->vcv_to.vf_codec;

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

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_converter *CC
initconv_from_rgba(struct video_converter *__restrict self) {
	struct video_codec const *from_codec = self->vcv_from.vf_codec;
	struct video_codec const *to_codec = self->vcv_to.vf_codec;

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

#endif /* !GUARD_LIBVIDEO_CODEC_CONVERTER_C */
