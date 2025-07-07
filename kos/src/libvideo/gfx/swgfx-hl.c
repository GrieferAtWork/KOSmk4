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
#ifndef GUARD_LIBVIDEO_GFX_SWGFX_HL_C
#define GUARD_LIBVIDEO_GFX_SWGFX_HL_C 1
#define _KOS_SOURCE 1

/************************************************************************/
/* HIGH-LEVEL, GENERIC SW-GFX OPERATOR IMPLS                            */
/************************************************************************/

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <assert.h>

#include <libvideo/codec/types.h>
#include <libvideo/gfx/gfx.h>

#include "bitmask-buffer.h"
#include "gfx-empty.h"
#include "gfx-utils.h"
#include "swgfx.h"

DECL_BEGIN

static_assert(sizeof(struct blt_swdrv) <= (_VIDEO_BLITTER_N_DRIVER * sizeof(void (*)(void))),
              "sizeof(struct blt_swdrv) too large for '_VIDEO_BLITTER_N_DRIVER'");
static_assert(sizeof(struct gfx_swdrv) <= (_VIDEO_GFX_N_DRIVER * sizeof(void *)),
              "sizeof(struct gfx_swdrv) too large for '_VIDEO_GFX_N_DRIVER'");

/************************************************************************/
/* BLITTER INITIALIZATION                                               */
/************************************************************************/

LOCAL ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) bool FCC
noblend_blit_compatible(struct video_codec const *dst,
                        struct video_codec const *src) {
	if (dst == src)
		return true;

	/* Certain codecs can still be blit onto each other without color conversion.
	 * This  is possible  whenever all color  channels present in  "dst" are also
	 * present at the same positions in "src".
	 *
	 * This is usually the case when "dst" lacks an alpha-channel and instead
	 * features some unused padding in its place. */
#ifndef __OPTIMIZE_SIZE__
	switch (dst->vc_codec) {
	case VIDEO_CODEC_RGBX8888:
		return src->vc_codec == VIDEO_CODEC_RGBA8888;
	case VIDEO_CODEC_XRGB8888:
		return src->vc_codec == VIDEO_CODEC_ARGB8888;
	case VIDEO_CODEC_XBGR8888:
		return src->vc_codec == VIDEO_CODEC_ABGR8888;
	case VIDEO_CODEC_BGRX8888:
		return src->vc_codec == VIDEO_CODEC_BGRA8888;
	case VIDEO_CODEC_RGBX4444:
		return src->vc_codec == VIDEO_CODEC_RGBA4444;
	case VIDEO_CODEC_XRGB4444:
		return src->vc_codec == VIDEO_CODEC_ARGB4444;
	case VIDEO_CODEC_XBGR4444:
		return src->vc_codec == VIDEO_CODEC_ABGR4444;
	case VIDEO_CODEC_BGRX4444:
		return src->vc_codec == VIDEO_CODEC_BGRA4444;
	case VIDEO_CODEC_RGBX5551:
		return src->vc_codec == VIDEO_CODEC_RGBA5551;
	case VIDEO_CODEC_XRGB1555:
		return src->vc_codec == VIDEO_CODEC_ARGB1555;
	case VIDEO_CODEC_XBGR1555:
		return src->vc_codec == VIDEO_CODEC_ABGR1555;
	case VIDEO_CODEC_BGRX5551:
		return src->vc_codec == VIDEO_CODEC_BGRA5551;
	default:
		break;
	}
#endif /* !__OPTIMIZE_SIZE__ */
	if ((dst->vc_specs.vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM)) ==
	    (src->vc_specs.vcs_flags & (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_LUM))) {
		if ((dst->vc_specs.vcs_rmask == 0 || dst->vc_specs.vcs_rmask == src->vc_specs.vcs_rmask) &&
		    (dst->vc_specs.vcs_gmask == 0 || dst->vc_specs.vcs_gmask == src->vc_specs.vcs_gmask) &&
		    (dst->vc_specs.vcs_bmask == 0 || dst->vc_specs.vcs_bmask == src->vc_specs.vcs_bmask) &&
		    (dst->vc_specs.vcs_amask == 0 || dst->vc_specs.vcs_amask == src->vc_specs.vcs_amask))
			return true;
	}
	return false;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC
libvideo_swgfx_blitfrom(struct video_blitter *__restrict ctx) {
	struct video_gfx const *src_gfx = ctx->vbt_src;
	struct video_gfx const *dst_gfx = ctx->vbt_dst;
	struct video_buffer const *src_buffer = src_gfx->vx_buffer;
	struct video_buffer const *dst_buffer = dst_gfx->vx_buffer;
	struct blt_swdrv *drv = video_swblitter_getdrv(ctx);
	video_swblitter_setops(ctx);

	/* Check for special case: source and target buffers are the same */
	if (video_gfx_getclipw(src_gfx) == 0 || video_gfx_getcliph(src_gfx) == 0) {
		ctx->vbt_ops = &libvideo_emptyblitter_ops;
	} else if (src_buffer == dst_buffer) {
		if (src_gfx->vx_flags & VIDEO_GFX_F_LINEAR) {
			drv->bsw_stretch         = &libvideo_swblitter_samebuf__stretch_l;
			drv->bsw_stretch_imatrix = &libvideo_swblitter_samebuf__stretch_imatrix_l;
		} else {
			drv->bsw_stretch         = &libvideo_swblitter_samebuf__stretch_n;
			drv->bsw_stretch_imatrix = &libvideo_swblitter_samebuf__stretch_imatrix_n;
		}
		if ((src_gfx->vx_flags & VIDEO_GFX_F_BLUR) == 0 &&
		    VIDEO_COLOR_ISTRANSPARENT(src_gfx->vx_colorkey) &&
		    GFX_BLENDMODE_GET_MODE(dst_gfx->vx_blend) == GFX_BLENDMODE_OVERRIDE) {
			drv->bsw_blit         = &libvideo_swblitter_noblend_samebuf__blit;
			drv->bsw_blit_imatrix = &libvideo_swblitter_noblend_samebuf__blit_imatrix;
		} else {
			/* Need to use different impls here that essentially do a "memmove"-style blit,
			 * rather  than the usual  "memcpy"-style one (since in  this case, writing new
			 * pixels in an  incorrect order might  clobber other pixels  that have yet  to
			 * be read) */
			drv->bsw_blit         = &libvideo_swblitter_samebuf__blit;
			drv->bsw_blit_imatrix = &libvideo_swblitter_samebuf__blit_imatrix;
		}
	} else if (GFX_BLENDMODE_GET_MODE(dst_gfx->vx_blend) == GFX_BLENDMODE_OVERRIDE) {
		if ((src_gfx->vx_flags & VIDEO_GFX_F_BLUR) != 0)
			goto set_generic_operators;
		if (!VIDEO_COLOR_ISTRANSPARENT(src_gfx->vx_colorkey))
			goto set_generic_operators;
		if (noblend_blit_compatible(dst_buffer->vb_format.vf_codec,
		                            src_buffer->vb_format.vf_codec) &&
		    src_buffer->vb_format.vf_pal == dst_buffer->vb_format.vf_pal) {
			/* Special optimization when not doing any blending, and both GFX contexts
			 * share the same codec: in this case,  we can try to directly copy  pixel
			 * data, either through video locks, or by directly reading/writing pixels */
			drv->bsw_blit         = &libvideo_swblitter_noblend_samefmt__blit;
			drv->bsw_blit_imatrix = &libvideo_swblitter_noblend_samefmt__blit_imatrix;
			if (src_gfx->vx_flags & VIDEO_GFX_F_LINEAR) {
				drv->bsw_stretch         = &libvideo_swblitter_noblend_samefmt__stretch_l;
				drv->bsw_stretch_imatrix = &libvideo_swblitter_noblend_samefmt__stretch_imatrix_l;
			} else {
				drv->bsw_stretch         = &libvideo_swblitter_noblend_samefmt__stretch_n;
				drv->bsw_stretch_imatrix = &libvideo_swblitter_noblend_samefmt__stretch_imatrix_n;
			}
		} else {
			/* Special optimization when not doing any blending, and both GFX contexts
			 * share the same codec: in this case,  we can try to directly copy  pixel
			 * data, either through video locks, or by directly reading/writing pixels */
			video_converter_init(libvideo_swblitter_generic__conv(ctx),
			                     &src_buffer->vb_format,
			                     &dst_buffer->vb_format);
			drv->bsw_blit         = &libvideo_swblitter_noblend_difffmt__blit;
			drv->bsw_blit_imatrix = &libvideo_swblitter_noblend_difffmt__blit_imatrix;
			if (src_gfx->vx_flags & VIDEO_GFX_F_LINEAR) {
				drv->bsw_stretch         = &libvideo_swblitter_noblend_difffmt__stretch_l;
				drv->bsw_stretch_imatrix = &libvideo_swblitter_noblend_difffmt__stretch_imatrix_l;
			} else {
				drv->bsw_stretch         = &libvideo_swblitter_noblend_difffmt__stretch_n;
				drv->bsw_stretch_imatrix = &libvideo_swblitter_noblend_difffmt__stretch_imatrix_n;
			}
		}
	} else {
set_generic_operators:
		drv->bsw_blit         = &libvideo_swblitter_generic__blit;
		drv->bsw_blit_imatrix = &libvideo_swblitter_generic__blit_imatrix;
		if (src_gfx->vx_flags & VIDEO_GFX_F_LINEAR) {
			drv->bsw_stretch         = &libvideo_swblitter_generic__stretch_l;
			drv->bsw_stretch_imatrix = &libvideo_swblitter_generic__stretch_imatrix_l;
		} else {
			drv->bsw_stretch         = &libvideo_swblitter_generic__stretch_n;
			drv->bsw_stretch_imatrix = &libvideo_swblitter_generic__stretch_imatrix_n;
		}
	}
	return ctx;
}


INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter3 *FCC
libvideo_swgfx_blitfrom3(struct video_blitter3 *__restrict ctx) {
	struct video_gfx const *src_gfx = ctx->vbt3_src;
	struct video_gfx const *rddst_gfx = ctx->vbt3_rddst;
	struct video_gfx const *wrdst_gfx = ctx->vbt3_wrdst;
	struct blt3_swdrv *drv = video_swblitter3_getdrv(ctx);
	video_swblitter3_setops(ctx);
	(void)wrdst_gfx;
	assert(video_gfx_getclipw(wrdst_gfx) != 0);
	assert(video_gfx_getcliph(wrdst_gfx) != 0);
	if (video_gfx_getclipw(src_gfx) == 0 || video_gfx_getcliph(src_gfx) == 0 ||
	    video_gfx_getclipw(rddst_gfx) == 0 || video_gfx_getcliph(rddst_gfx) == 0) {
		ctx->vbt3_ops = &libvideo_emptyblitter3_ops;
	} else {
		drv->bsw3_blendmode = rddst_gfx->vx_blend;
		switch (__builtin_expect(GFX_BLENDMODE_GET_MODE(rddst_gfx->vx_blend),
		                         GFX_BLENDMODE_ALPHA)) {
#define LINK_libvideo_swblt_generic__blend_FOO(name, mode)        \
		case mode:                                                \
			drv->bsw3_blend = &libvideo_swblitter3__blend_##name; \
			break;
		GFX_FOREACH_DEDICATED_BLENDMODE(LINK_libvideo_swblt_generic__blend_FOO)
		GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(LINK_libvideo_swblt_generic__blend_FOO)
#undef LINK_libvideo_swblt_generic__blend_FOO
		default:
			drv->bsw3_blend = &libvideo_swblitter3__blend;
			break;
		}

		/* TODO: Special handling when buffers overlap */
		/* TODO: More dedicated optimizations */

		if likely(GFX_BLENDMODE_GET_MODE(wrdst_gfx->vx_blend) == GFX_BLENDMODE_OVERRIDE) {
			/* Special optimization for likely case where "wrdst_gfx" doesn't do any blending */
			drv->bsw3_blit         = &libvideo_swblitter3__blit__blend1;
			drv->bsw3_blit_imatrix = &libvideo_swblitter3__blit_imatrix__blend1;
			if (src_gfx->vx_flags & VIDEO_GFX_F_LINEAR) {
				drv->bsw3_stretch         = &libvideo_swblitter3__stretch__blend1_l;
				drv->bsw3_stretch_imatrix = &libvideo_swblitter3__stretch_imatrix__blend1_l;
			} else {
				drv->bsw3_stretch         = &libvideo_swblitter3__stretch__blend1_n;
				drv->bsw3_stretch_imatrix = &libvideo_swblitter3__stretch_imatrix__blend1_n;
			}
		} else {
			drv->bsw3_blit         = &libvideo_swblitter3__blit__generic;
			drv->bsw3_blit_imatrix = &libvideo_swblitter3__blit_imatrix__generic;
			if (src_gfx->vx_flags & VIDEO_GFX_F_LINEAR) {
				drv->bsw3_stretch         = &libvideo_swblitter3__stretch__generic_l;
				drv->bsw3_stretch_imatrix = &libvideo_swblitter3__stretch_imatrix__generic_l;
			} else {
				drv->bsw3_stretch         = &libvideo_swblitter3__stretch__generic_n;
				drv->bsw3_stretch_imatrix = &libvideo_swblitter3__stretch_imatrix__generic_n;
			}
		}
	}
	return ctx;
}










/************************************************************************/
/* BIT-MASKED FILL                                                      */
/************************************************************************/
INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC
libvideo_swgfx_fillmask(struct video_gfx const *__restrict self,
                        video_offset_t dst_x, video_offset_t dst_y,
                        video_dim_t size_x, video_dim_t size_y,
                        video_color_t const bg_fg_colors[2],
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
	video_swgfx_x_absfillmask(self,
	                          (video_coord_t)dst_x,
	                          (video_coord_t)dst_y,
	                          size_x, size_y,
	                          bg_fg_colors, bm);
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC
libvideo_swgfx_fillmask_wrap(struct video_gfx const *__restrict self,
                             video_offset_t dst_x, video_offset_t dst_y,
                             video_dim_t size_x, video_dim_t size_y,
                             video_color_t const bg_fg_colors[2],
                             struct video_bitmask const *__restrict bm) {
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = size_x;
	video_dim_t yinb = size_y;
	if (self->vx_flags & VIDEO_GFX_F_XWRAP) {
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
	if (self->vx_flags & VIDEO_GFX_F_YWRAP) {
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
		libvideo_swgfx_fillmask(self, 0, 0, xwrap, ywrap, bg_fg_colors, &chunk_bm);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		struct video_bitmask chunk_bm = *bm;
		chunk_bm.vbm_skip += xinb;
		libvideo_swgfx_fillmask(self, 0, dst_y, xwrap, size_y, bg_fg_colors, &chunk_bm);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		struct video_bitmask chunk_bm = *bm;
		chunk_bm.vbm_skip += yinb * chunk_bm.vbm_scan;
		libvideo_swgfx_fillmask(self, dst_x, 0, size_x, ywrap, bg_fg_colors, &chunk_bm);
	}
	libvideo_swgfx_fillmask(self, dst_x, dst_y, xinb, yinb, bg_fg_colors, bm);
}





/************************************************************************/
/* BIT-MASKED STRETCH FILL                                              */
/************************************************************************/
INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
libvideo_swgfx_fillstretchmask(struct video_gfx const *__restrict self,
                               video_offset_t dst_x, video_offset_t dst_y,
                               video_dim_t dst_size_x, video_dim_t dst_size_y,
                               video_color_t const bg_fg_colors[2],
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
		video_swgfx_x_absfillmask(self, (video_coord_t)dst_x, (video_coord_t)dst_y,
		                          dst_size_x, dst_size_y, bg_fg_colors, bm);
	} else {
		/* Must use stretch-blit */
		video_swgfx_x_absfillstretchmask(self, (video_coord_t)dst_x, (video_coord_t)dst_y,
		                                 dst_size_x, dst_size_y, bg_fg_colors,
		                                 src_size_x, src_size_y, bm);
	}
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
libvideo_swgfx_fillstretchmask_wrap(struct video_gfx const *__restrict self,
                                    video_offset_t dst_x, video_offset_t dst_y,
                                    video_dim_t dst_size_x, video_dim_t dst_size_y,
                                    video_color_t const bg_fg_colors[2],
                                    video_dim_t src_size_x, video_dim_t src_size_y,
                                    struct video_bitmask const *__restrict bm) {
#define xdst2src(x) ((video_coord_t)(((uint64_t)(x) * src_size_x) / dst_size_x))
#define ydst2src(y) ((video_coord_t)(((uint64_t)(y) * src_size_y) / dst_size_y))
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = dst_size_x;
	video_dim_t yinb = dst_size_y;
	if (self->vx_flags & VIDEO_GFX_F_XWRAP) {
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
	if (self->vx_flags & VIDEO_GFX_F_YWRAP) {
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
		libvideo_swgfx_fillstretchmask(self, 0, 0, xwrap, ywrap, bg_fg_colors,
		                               chunk_src_size_x, chunk_src_size_y, &chunk_bm);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		struct video_bitmask chunk_bm = *bm;
		size_t chunk_src_x = xdst2src(xinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		chunk_bm.vbm_skip += chunk_src_x;
		libvideo_swgfx_fillstretchmask(self, 0, dst_y, xwrap, dst_size_y, bg_fg_colors,
		                               chunk_src_size_x, src_size_y, &chunk_bm);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		struct video_bitmask chunk_bm = *bm;
		size_t chunk_src_y = ydst2src(yinb);
		size_t chunk_src_size_y = ydst2src(ywrap);
		chunk_bm.vbm_skip += chunk_src_y * chunk_bm.vbm_scan;
		libvideo_swgfx_fillstretchmask(self, dst_x, 0, dst_size_x, ywrap, bg_fg_colors,
		                               src_size_x, chunk_src_size_y, &chunk_bm);
	}
	libvideo_swgfx_fillstretchmask(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                               bg_fg_colors, src_size_x, src_size_y, bm);
#undef xdst2src
#undef ydst2src
}



INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC
libvideo_swgfx_fillmask_byblit(struct video_gfx const *__restrict self,
                               video_offset_t dst_x, video_offset_t dst_y,
                               video_dim_t size_x, video_dim_t size_y,
                               video_color_t const bg_fg_colors[2],
                               struct video_bitmask const *__restrict bm) {
	struct video_gfx bm_gfx, *pgfx;
	struct bitmask_buffer temp, *pbuf;
	pbuf = bitmask_buffer_init(&temp, size_x, size_y, bm, bg_fg_colors);
	pgfx = video_buffer_getgfx(pbuf, &bm_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	video_gfx_bitblit(self, dst_x, dst_y, pgfx, 0, 0, size_x, size_y);
	bitmask_buffer_fini(pbuf);
}


INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
libvideo_swgfx_fillstretchmask_byblit(struct video_gfx const *__restrict self,
                                      video_offset_t dst_x, video_offset_t dst_y,
                                      video_dim_t dst_size_x, video_dim_t dst_size_y,
                                      video_color_t const bg_fg_colors[2],
                                      video_dim_t src_size_x, video_dim_t src_size_y,
                                      struct video_bitmask const *__restrict bm) {
	struct video_gfx bm_gfx, *pgfx;
	struct bitmask_buffer temp, *pbuf;
	pbuf = bitmask_buffer_init(&temp, src_size_x, src_size_y, bm, bg_fg_colors);
	pgfx = video_buffer_getgfx(pbuf, &bm_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	video_gfx_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                  pgfx, 0, 0, src_size_x, src_size_y);
	bitmask_buffer_fini(pbuf);
}

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_libvideo_swgfx_XXX
#include "swgfx/hl_generic.c.inl"

#define DEFINE_libvideo_swblitter_blit
#include "swgfx/hl_blit-nowrap.c.inl"
#define DEFINE_libvideo_swblitter_stretch
#include "swgfx/hl_blit-nowrap.c.inl"
#define DEFINE_libvideo_swblitter_blit_wrap
#include "swgfx/hl_blit.c.inl"

#define DEFINE_libvideo_swblitter3_blit
#include "swgfx/hl_blit-nowrap.c.inl"
#define DEFINE_libvideo_swblitter3_stretch
#include "swgfx/hl_blit-nowrap.c.inl"
#define DEFINE_libvideo_swblitter3_blit_wrap
#include "swgfx/hl_blit.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_HL_C */
