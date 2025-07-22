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

#include <stddef.h>
#include <stdint.h>

#include <libvideo/color.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "buffer/old-bitmask.h" /* TODO: Get rid of mask-fill operators */
#include "gfx-utils.h"
#include "swgfx.h"

DECL_BEGIN

static_assert(sizeof(struct gfx_swdrv) <= (_VIDEO_GFX_N_DRIVER * sizeof(void *)),
              "sizeof(struct gfx_swdrv) too large for '_VIDEO_GFX_N_DRIVER'");

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
	struct old_bitmask_buffer temp, *pbuf;
	pbuf = old_bitmask_buffer_init(&temp, size_x, size_y, bm, bg_fg_colors);
	pgfx = video_buffer_getgfx(pbuf, &bm_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	video_gfx_bitblit(self, dst_x, dst_y, pgfx, 0, 0, size_x, size_y);
	old_bitmask_buffer_fini(pbuf);
}


INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
libvideo_swgfx_fillstretchmask_byblit(struct video_gfx const *__restrict self,
                                      video_offset_t dst_x, video_offset_t dst_y,
                                      video_dim_t dst_size_x, video_dim_t dst_size_y,
                                      video_color_t const bg_fg_colors[2],
                                      video_dim_t src_size_x, video_dim_t src_size_y,
                                      struct video_bitmask const *__restrict bm) {
	struct video_gfx bm_gfx, *pgfx;
	struct old_bitmask_buffer temp, *pbuf;
	pbuf = old_bitmask_buffer_init(&temp, src_size_x, src_size_y, bm, bg_fg_colors);
	pgfx = video_buffer_getgfx(pbuf, &bm_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	video_gfx_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                  pgfx, 0, 0, src_size_x, src_size_y);
	old_bitmask_buffer_fini(pbuf);
}

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_libvideo_swgfx_XXX
#include "swgfx/hl_generic.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_HL_C */
