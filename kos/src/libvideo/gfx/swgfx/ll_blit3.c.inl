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
#ifndef GUARD_LIBVIDEO_GFX_SWGFX_LL_BLIT3_C_INL
#define GUARD_LIBVIDEO_GFX_SWGFX_LL_BLIT3_C_INL 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <libvideo/color.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/blendcolors.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/surface.h>
#include <libvideo/types.h>

#include "../gfx-utils.h"
#include "../swgfx.h"
#include "ll.h"

DECL_BEGIN

/************************************************************************/
/* GENERIC 3-WAY BLIT OPERATORS                                         */
/************************************************************************/

static_assert(sizeof(struct blt3_swdrv) <= (_VIDEO_BLITTER3_N_DRIVER * sizeof(void (*)(void))),
              "sizeof(struct blt3_swdrv) too large for '_VIDEO_BLITTER3_N_DRIVER'");

INTERN ATTR_PURE WUNUSED ATTR_IN(1) video_color_t BLT3_SWDRV_BLEND_CC
libvideo_swblitter3__blend(struct video_blitter3 const *__restrict self,
                           video_color_t dst, video_color_t src) {
	struct blt3_swdrv const *drv = video_swblitter3_getcdrv(self);
	return gfx_blendcolors(dst, src, drv->bsw3_blendmode);
}

#define DEFINE_libvideo_swblitter3__blend_FOO(name, mode)                           \
	INTERN ATTR_CONST WUNUSED ATTR_IN(1) video_color_t BLT3_SWDRV_BLEND_CC          \
	libvideo_swblitter3__blend_##name(struct video_blitter3 const *__restrict self, \
	                                  video_color_t dst, video_color_t src) {       \
		(void)self;                                                                 \
		return gfx_blendcolors(dst, src, mode);                                     \
	}
GFX_FOREACH_DEDICATED_BLENDMODE(DEFINE_libvideo_swblitter3__blend_FOO)
#undef DEFINE_libvideo_swblitter3__blend_FOO

#define DEFINE_libvideo_swblitter3__blend_FOO(name, mode)                           \
	INTERN ATTR_PURE WUNUSED ATTR_IN(1) video_color_t BLT3_SWDRV_BLEND_CC           \
	libvideo_swblitter3__blend_##name(struct video_blitter3 const *__restrict self, \
	                                  video_color_t dst, video_color_t src) {       \
		struct blt3_swdrv const *drv = video_swblitter3_getcdrv(self);              \
		video_color_t c = GFX_BLENDMODE_GET_COLOR(drv->bsw3_blendmode);             \
		return gfx_blendcolors_constant(dst, src, mode, c);                         \
	}
GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(DEFINE_libvideo_swblitter3__blend_FOO)
#undef DEFINE_libvideo_swblitter3__blend_FOO



#define BLIT_PIXEL(px_out_x, px_out_y, px_dst_x, px_dst_y, px_src_x, px_src_y) \
	{                                                                          \
		video_color_t sc = LL_getcolor(src, px_src_x, px_src_y);               \
		video_color_t dc = LL_getcolor(dst, px_dst_x, px_dst_y);               \
		video_color_t oc = (*blend)(self, dc, sc);                             \
		LL_putcolor(out, px_out_x, px_out_y, oc);                              \
	}
PRIVATE ATTR_IN(1) void CC
libvideo_swblitter3__blit__generic__bypixel(struct video_blitter3 const *__restrict self,
                                            video_coord_t out_x, video_coord_t out_y,
                                            video_coord_t dst_x, video_coord_t dst_y,
                                            video_coord_t src_x, video_coord_t src_y,
                                            video_dim_t size_x, video_dim_t size_y) {
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
	blt3_blend_t blend = video_swblitter3_getcdrv(self)->bsw3_blend;
	GFX_BLIT_FOREACH3(out_x, out_y, dst_x, dst_y, src_x, src_y, size_x, size_y,
	                  BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter3__blit_imatrix__generic__bypixel(struct video_blitter3 const *__restrict self,
                                                    video_coord_t out_x, video_coord_t out_y,
                                                    video_coord_t dst_x, video_coord_t dst_y,
                                                    video_imatrix2d_t dst_matrix,
                                                    video_coord_t src_x, video_coord_t src_y,
                                                    video_dim_t size_x, video_dim_t size_y,
                                                    video_imatrix2d_t src_matrix) {
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
	blt3_blend_t blend = video_swblitter3_getcdrv(self)->bsw3_blend;
	GFX_BLIT_FOREACH3_IMATRIX(out_x, out_y, dst_x, dst_y, dst_matrix,
	                          src_x, src_y, size_x, size_y, src_matrix,
	                          BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter3__stretch__generic_n__bypixel(struct video_blitter3 const *__restrict self,
                                                 video_coord_t out_x, video_coord_t out_y,
                                                 video_coord_t dst_x, video_coord_t dst_y,
                                                 video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                 video_coord_t src_x, video_coord_t src_y,
                                                 video_dim_t src_size_x, video_dim_t src_size_y) {
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
	blt3_blend_t blend = video_swblitter3_getcdrv(self)->bsw3_blend;
	GFX_NEAREST_STRETCH3(out_x, out_y,
	                     dst_x, dst_y, dst_size_x, dst_size_y,
	                     src_x, src_y, src_size_x, src_size_y,
	                     BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter3__stretch_imatrix__generic_n__bypixel(struct video_blitter3 const *__restrict self,
                                                         video_coord_t out_x, video_coord_t out_y,
                                                         video_coord_t dst_x, video_coord_t dst_y,
                                                         video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                         video_imatrix2d_t dst_matrix,
                                                         video_coord_t src_x, video_coord_t src_y,
                                                         video_dim_t src_size_x, video_dim_t src_size_y,
                                                         video_imatrix2d_t src_matrix) {
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
	blt3_blend_t blend = video_swblitter3_getcdrv(self)->bsw3_blend;
	gfx_assert_imatrix2d(&dst_matrix);
	gfx_assert_imatrix2d(&src_matrix);
	GFX_NEAREST_STRETCH3_IMATRIX(out_x, out_y,
	                             dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix,
	                             src_x, src_y, src_size_x, src_size_y, src_matrix,
	                             BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}


PRIVATE ATTR_IN(1) void CC
libvideo_swblitter3__stretch__generic_l__bypixel(struct video_blitter3 const *__restrict self,
                                                 video_coord_t out_x, video_coord_t out_y,
                                                 video_coord_t dst_x, video_coord_t dst_y,
                                                 video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                 video_coord_t src_x, video_coord_t src_y,
                                                 video_dim_t src_size_x, video_dim_t src_size_y) {
	/* TODO */
	libvideo_swblitter3__stretch__generic_n__bypixel(self, out_x, out_y,
	                                                 dst_x, dst_y, dst_size_x, dst_size_y,
	                                                 src_x, src_y, src_size_x, src_size_y);
}


PRIVATE ATTR_IN(1) void CC
libvideo_swblitter3__stretch_imatrix__generic_l__bypixel(struct video_blitter3 const *__restrict self,
                                                         video_coord_t out_x, video_coord_t out_y,
                                                         video_coord_t dst_x, video_coord_t dst_y,
                                                         video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                         video_imatrix2d_t dst_matrix,
                                                         video_coord_t src_x, video_coord_t src_y,
                                                         video_dim_t src_size_x, video_dim_t src_size_y,
                                                         video_imatrix2d_t src_matrix) {
	/* TODO */
	libvideo_swblitter3__stretch_imatrix__generic_n__bypixel(self, out_x, out_y,
	                                                         dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix,
	                                                         src_x, src_y, src_size_x, src_size_y, src_matrix);
}
#undef BLIT_PIXEL






INTERN ATTR_IN(1) void CC
libvideo_swblitter3__blit__generic(struct video_blitter3 const *__restrict self,
                                   video_coord_t out_x, video_coord_t out_y,
                                   video_coord_t dst_x, video_coord_t dst_y,
                                   video_coord_t src_x, video_coord_t src_y,
                                   video_dim_t size_x, video_dim_t size_y) {
	TRACE_START("swblitter3__blit__generic("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            out_x, out_y, dst_x, dst_y, src_x, src_y, size_x, size_y);
	libvideo_swblitter3__blit__generic__bypixel(self, out_x, out_y, dst_x, dst_y,
	                                            src_x, src_y, size_x, size_y);
	TRACE_END("swblitter3__blit__generic()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter3__blit_imatrix__generic(struct video_blitter3 const *__restrict self,
                                           video_coord_t out_x, video_coord_t out_y,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_imatrix2d_t dst_matrix,
                                           video_coord_t src_x, video_coord_t src_y,
                                           video_dim_t size_x, video_dim_t size_y,
                                           video_imatrix2d_t src_matrix) {
	gfx_assert_imatrix2d(&dst_matrix);
	gfx_assert_imatrix2d(&src_matrix);

	TRACE_START("swblitter3__blit_imatrix__generic("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", matrix: {{%d,%d},{%d,%d}}}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", matrix: {{%d,%d},{%d,%d}}}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            out_x, out_y,
	            dst_x, dst_y,
	            (int)video_imatrix2d_get(&dst_matrix, 0, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 0, 1),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 1),
	            src_x, src_y,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1),
	            size_x, size_y);
	libvideo_swblitter3__blit_imatrix__generic__bypixel(self, out_x, out_y, dst_x, dst_y, dst_matrix,
	                                                    src_x, src_y, size_x, size_y, src_matrix);
	TRACE_END("swblitter3__blit_imatrix__generic()\n");
}



INTERN ATTR_IN(1) void CC
libvideo_swblitter3__stretch__generic_n(struct video_blitter3 const *__restrict self,
                                        video_coord_t out_x, video_coord_t out_y,
                                        video_coord_t dst_x, video_coord_t dst_y,
                                        video_dim_t dst_size_x, video_dim_t dst_size_y,
                                        video_coord_t src_x, video_coord_t src_y,
                                        video_dim_t src_size_x, video_dim_t src_size_y) {
	TRACE_START("swblitter3__stretch__generic_n("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            out_x, out_y,
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            src_x, src_y, src_size_x, src_size_y);
	libvideo_swblitter3__stretch__generic_n__bypixel(self, out_x, out_y,
	                                                 dst_x, dst_y, dst_size_x, dst_size_y,
	                                                 src_x, src_y, src_size_x, src_size_y);
	TRACE_END("swblitter3__stretch__generic_n()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter3__stretch_imatrix__generic_n(struct video_blitter3 const *__restrict self,
                                                video_coord_t out_x, video_coord_t out_y,
                                                video_coord_t dst_x, video_coord_t dst_y,
                                                video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                video_imatrix2d_t dst_matrix,
                                                video_coord_t src_x, video_coord_t src_y,
                                                video_dim_t src_size_x, video_dim_t src_size_y,
                                                video_imatrix2d_t src_matrix) {
	gfx_assert_imatrix2d(&dst_matrix);
	gfx_assert_imatrix2d(&src_matrix);

	/* Fast-pass for known matrices */
	if (src_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1) &&
	    dst_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1)) {
		libvideo_swblitter3__stretch__generic_n(self, out_x, out_y,
		                                        dst_x, dst_y, dst_size_x, dst_size_y,
		                                        src_x, src_y, src_size_x, src_size_y);
		return;
	}

	TRACE_START("swblitter3__stretch_imatrix__generic_n("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM ", matrix: {{%d,%d},{%d,%d}}}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM ", matrix: {{%d,%d},{%d,%d}}})\n",
	            out_x, out_y,
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            (int)video_imatrix2d_get(&dst_matrix, 0, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 0, 1),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 1),
	            src_x, src_y, src_size_x, src_size_y,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1));
	libvideo_swblitter3__stretch_imatrix__generic_n__bypixel(self, out_x, out_y,
	                                                         dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix,
	                                                         src_x, src_y, src_size_x, src_size_y, src_matrix);
	TRACE_END("swblitter3__stretch_imatrix__generic_n()\n");
}


INTERN ATTR_IN(1) void CC
libvideo_swblitter3__stretch__generic_l(struct video_blitter3 const *__restrict self,
                                        video_coord_t out_x, video_coord_t out_y,
                                        video_coord_t dst_x, video_coord_t dst_y,
                                        video_dim_t dst_size_x, video_dim_t dst_size_y,
                                        video_coord_t src_x, video_coord_t src_y,
                                        video_dim_t src_size_x, video_dim_t src_size_y) {
	TRACE_START("swblitter3__stretch__generic_l("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            out_x, out_y,
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            src_x, src_y, src_size_x, src_size_y);
	libvideo_swblitter3__stretch__generic_l__bypixel(self, out_x, out_y,
	                                                 dst_x, dst_y, dst_size_x, dst_size_y,
	                                                 src_x, src_y, src_size_x, src_size_y);
	TRACE_END("swblitter3__stretch__generic_l()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter3__stretch_imatrix__generic_l(struct video_blitter3 const *__restrict self,
                                                video_coord_t out_x, video_coord_t out_y,
                                                video_coord_t dst_x, video_coord_t dst_y,
                                                video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                video_imatrix2d_t dst_matrix,
                                                video_coord_t src_x, video_coord_t src_y,
                                                video_dim_t src_size_x, video_dim_t src_size_y,
                                                video_imatrix2d_t src_matrix) {
	gfx_assert_imatrix2d(&dst_matrix);
	gfx_assert_imatrix2d(&src_matrix);

	/* Fast-pass for known matrices */
	if (src_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1) &&
	    dst_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1)) {
		libvideo_swblitter3__stretch__generic_l(self, out_x, out_y,
		                                        dst_x, dst_y, dst_size_x, dst_size_y,
		                                        src_x, src_y, src_size_x, src_size_y);
		return;
	}

	TRACE_START("swblitter3__stretch_imatrix__generic_l("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM ", matrix: {{%d,%d},{%d,%d}}}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM ", matrix: {{%d,%d},{%d,%d}}})\n",
	            out_x, out_y,
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            (int)video_imatrix2d_get(&dst_matrix, 0, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 0, 1),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 1),
	            src_x, src_y, src_size_x, src_size_y,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1));
	libvideo_swblitter3__stretch_imatrix__generic_l__bypixel(self, out_x, out_y,
	                                                         dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix,
	                                                         src_x, src_y, src_size_x, src_size_y, src_matrix);
	TRACE_END("swblitter3__stretch_imatrix__generic_l()\n");
}





/************************************************************************/
/* SINGLE-BLEND, 3-WAY BLITTING                                         */
/************************************************************************/

INTERN ATTR_IN(1) void CC
libvideo_swblitter3__blit__blend1(struct video_blitter3 const *__restrict self,
                                  video_coord_t out_x, video_coord_t out_y,
                                  video_coord_t dst_x, video_coord_t dst_y,
                                  video_coord_t src_x, video_coord_t src_y,
                                  video_dim_t size_x, video_dim_t size_y) {
	struct video_regionlock srclock;
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
	blt3_blend_t blend = video_swblitter3_getcdrv(self)->bsw3_blend;

	TRACE_START("swblitter3__blit__blend1("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            out_x, out_y, dst_x, dst_y, src_x, src_y, size_x, size_y);

	/* Try to acquire video locks to perform blit directly on video memory. */
	if (LL_rlockregion(video_gfx_getbuffer(src), &srclock, src_x, src_y, size_x, size_y)) {
		struct video_regionlock dstlock;
		if (LL_rlockregion(video_gfx_getbuffer(dst), &dstlock, dst_x, dst_y, size_x, size_y)) {
			struct video_regionlock outlock;
			if (LL_wlockregion(video_gfx_getbuffer(out), &outlock, out_x, out_y, size_x, size_y)) {
				byte_t const *srcline = srclock.vrl_lock.vl_data;
				byte_t const *dstline = dstlock.vrl_lock.vl_data;
				byte_t *outline = outlock.vrl_lock.vl_data;
				struct video_surface const *src_surface   = video_gfx_assurface(src);
				struct video_surface const *dst_surface   = video_gfx_assurface(dst);
				struct video_surface const *out_surface   = video_gfx_assurface(out);
				video_codec_getpixel_t src_getpixel       = video_surface_getcodec(src_surface)->vc_getpixel;
				video_codec_pixel2color_t src_pixel2color = video_surface_getcodec(src_surface)->vc_pixel2color;
				video_codec_getpixel_t dst_getpixel       = video_surface_getcodec(dst_surface)->vc_getpixel;
				video_codec_pixel2color_t dst_pixel2color = video_surface_getcodec(dst_surface)->vc_pixel2color;
				video_codec_setpixel_t out_setpixel       = video_surface_getcodec(out_surface)->vc_setpixel;
				video_codec_color2pixel_t out_color2pixel = video_surface_getcodec(out_surface)->vc_color2pixel;
				do {
					video_coord_t x;
					x = 0;
					do {
						video_pixel_t src_pixel = (*src_getpixel)(srcline, srclock.vrl_xbas + x);
						video_color_t src_color = (*src_pixel2color)(src_surface, src_pixel);
						video_pixel_t dst_pixel = (*dst_getpixel)(dstline, dstlock.vrl_xbas + x);
						video_color_t dst_color = (*dst_pixel2color)(dst_surface, dst_pixel);
						video_color_t out_color = (*blend)(self, dst_color, src_color);
						video_pixel_t out_pixel = (*out_color2pixel)(out_surface, out_color);
						(*out_setpixel)(outline, outlock.vrl_xbas + x, out_pixel);
					} while (++x < size_x);
					srcline += srclock.vrl_lock.vl_stride;
					dstline += dstlock.vrl_lock.vl_stride;
					outline += outlock.vrl_lock.vl_stride;
				} while (--size_y);
				LL_unlockregion(video_gfx_getbuffer(out), &outlock);
				LL_unlockregion(video_gfx_getbuffer(dst), &dstlock);
				LL_unlockregion(video_gfx_getbuffer(src), &srclock);
				goto done;
			}
			LL_unlockregion(video_gfx_getbuffer(dst), &dstlock);
		}
		LL_unlockregion(video_gfx_getbuffer(src), &srclock);
	}

	/* Fallback: perform operate pixel-by-pixel */
	libvideo_swblitter3__blit__generic__bypixel(self, out_x, out_y, dst_x, dst_y,
	                                            src_x, src_y, size_x, size_y);
done:
	TRACE_END("swblitter3__blit__blend1()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter3__blit_imatrix__blend1(struct video_blitter3 const *__restrict self,
                                          video_coord_t out_x, video_coord_t out_y,
                                          video_coord_t dst_x, video_coord_t dst_y,
                                          video_imatrix2d_t dst_matrix,
                                          video_coord_t src_x, video_coord_t src_y,
                                          video_dim_t size_x, video_dim_t size_y,
                                          video_imatrix2d_t src_matrix) {
	gfx_assert_imatrix2d(&dst_matrix);
	gfx_assert_imatrix2d(&src_matrix);

	/* Fast-pass for known matrices */
	if (src_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1) &&
	    dst_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1)) {
		libvideo_swblitter3__blit__blend1(self, out_x, out_y, dst_x, dst_y,
		                                  src_x, src_y, size_x, size_y);
		return;
	}

	TRACE_START("swblitter3__blit_imatrix__blend1("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", matrix: {{%d,%d},{%d,%d}}}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", matrix: {{%d,%d},{%d,%d}}}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            out_x, out_y,
	            dst_x, dst_y,
	            (int)video_imatrix2d_get(&dst_matrix, 0, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 0, 1),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 1),
	            src_x, src_y,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1),
	            size_x, size_y);

	/* TODO: Use video locks */
	libvideo_swblitter3__blit_imatrix__generic__bypixel(self, out_x, out_y, dst_x, dst_y, dst_matrix,
	                                                    src_x, src_y, size_x, size_y, src_matrix);
	TRACE_END("swblitter3__blit_imatrix__blend1()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter3__stretch__blend1_n(struct video_blitter3 const *__restrict self,
                                       video_coord_t out_x, video_coord_t out_y,
                                       video_coord_t dst_x, video_coord_t dst_y,
                                       video_dim_t dst_size_x, video_dim_t dst_size_y,
                                       video_coord_t src_x, video_coord_t src_y,
                                       video_dim_t src_size_x, video_dim_t src_size_y) {
	TRACE_START("swblitter3__stretch__blend1_n("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            out_x, out_y,
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            src_x, src_y, src_size_x, src_size_y);

	/* TODO: Use video locks */
	libvideo_swblitter3__stretch__generic_n__bypixel(self, out_x, out_y,
	                                                 dst_x, dst_y, dst_size_x, dst_size_y,
	                                                 src_x, src_y, src_size_x, src_size_y);
	TRACE_END("swblitter3__stretch__blend1_n()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter3__stretch_imatrix__blend1_n(struct video_blitter3 const *__restrict self,
                                               video_coord_t out_x, video_coord_t out_y,
                                               video_coord_t dst_x, video_coord_t dst_y,
                                               video_dim_t dst_size_x, video_dim_t dst_size_y,
                                               video_imatrix2d_t dst_matrix,
                                               video_coord_t src_x, video_coord_t src_y,
                                               video_dim_t src_size_x, video_dim_t src_size_y,
                                               video_imatrix2d_t src_matrix) {
	gfx_assert_imatrix2d(&dst_matrix);
	gfx_assert_imatrix2d(&src_matrix);

	/* Fast-pass for known matrices */
	if (src_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1) &&
	    dst_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1)) {
		libvideo_swblitter3__stretch__blend1_n(self, out_x, out_y,
		                                       dst_x, dst_y, dst_size_x, dst_size_y,
		                                       src_x, src_y, src_size_x, src_size_y);
		return;
	}

	TRACE_START("swblitter3__stretch_imatrix__blend1_n("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM ", matrix: {{%d,%d},{%d,%d}}}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM ", matrix: {{%d,%d},{%d,%d}}})\n",
	            out_x, out_y,
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            (int)video_imatrix2d_get(&dst_matrix, 0, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 0, 1),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 1),
	            src_x, src_y, src_size_x, src_size_y,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1));

	/* TODO: Use video locks */
	libvideo_swblitter3__stretch_imatrix__generic_n__bypixel(self, out_x, out_y,
	                                                         dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix,
	                                                         src_x, src_y, src_size_x, src_size_y, src_matrix);
	TRACE_END("swblitter3__stretch_imatrix__blend1_n()\n");
}


INTERN ATTR_IN(1) void CC
libvideo_swblitter3__stretch__blend1_l(struct video_blitter3 const *__restrict self,
                                       video_coord_t out_x, video_coord_t out_y,
                                       video_coord_t dst_x, video_coord_t dst_y,
                                       video_dim_t dst_size_x, video_dim_t dst_size_y,
                                       video_coord_t src_x, video_coord_t src_y,
                                       video_dim_t src_size_x, video_dim_t src_size_y) {
	TRACE_START("swblitter3__stretch__blend1_l("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            out_x, out_y,
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            src_x, src_y, src_size_x, src_size_y);

	/* TODO: Use video locks */
	libvideo_swblitter3__stretch__generic_l__bypixel(self, out_x, out_y,
	                                                 dst_x, dst_y, dst_size_x, dst_size_y,
	                                                 src_x, src_y, src_size_x, src_size_y);
	TRACE_END("swblitter3__stretch__blend1_l()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter3__stretch_imatrix__blend1_l(struct video_blitter3 const *__restrict self,
                                               video_coord_t out_x, video_coord_t out_y,
                                               video_coord_t dst_x, video_coord_t dst_y,
                                               video_dim_t dst_size_x, video_dim_t dst_size_y,
                                               video_imatrix2d_t dst_matrix,
                                               video_coord_t src_x, video_coord_t src_y,
                                               video_dim_t src_size_x, video_dim_t src_size_y,
                                               video_imatrix2d_t src_matrix) {
	gfx_assert_imatrix2d(&dst_matrix);
	gfx_assert_imatrix2d(&src_matrix);

	/* Fast-pass for known matrices */
	if (src_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1) &&
	    dst_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1)) {
		libvideo_swblitter3__stretch__blend1_l(self, out_x, out_y,
		                                       dst_x, dst_y, dst_size_x, dst_size_y,
		                                       src_x, src_y, src_size_x, src_size_y);
		return;
	}

	TRACE_START("swblitter3__stretch_imatrix__blend1_l("
	            "out: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM ", matrix: {{%d,%d},{%d,%d}}}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM ", matrix: {{%d,%d},{%d,%d}}})\n",
	            out_x, out_y,
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            (int)video_imatrix2d_get(&dst_matrix, 0, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 0, 1),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 0),
	            (int)video_imatrix2d_get(&dst_matrix, 1, 1),
	            src_x, src_y, src_size_x, src_size_y,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1));

	/* TODO: Use video locks */
	libvideo_swblitter3__stretch_imatrix__generic_l__bypixel(self, out_x, out_y,
	                                                         dst_x, dst_y, dst_size_x, dst_size_y, dst_matrix,
	                                                         src_x, src_y, src_size_x, src_size_y, src_matrix);
	TRACE_END("swblitter3__stretch_imatrix__blend1_l()\n");
}

DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_libvideo_swblitter3__blit__mask1msb
#include "ll_blit3-mask1msb.c.inl"
#define DEFINE_libvideo_swblitter3__blit__mask1msb_blend1_samefmt
#include "ll_blit3-mask1msb.c.inl"
#define DEFINE_libvideo_swblitter3__blit__mask1msb_blend1_difffmt
#include "ll_blit3-mask1msb.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_LL_BLIT3_C_INL */
