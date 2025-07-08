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

#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/blendcolors.h>
#include <libvideo/gfx/gfx.h>

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
	GFX_BLIT_FOREACH3(out_x, out_y, dst_x, dst_y, src_x, src_y, size_x, size_y, BLIT_PIXEL);
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
	                          BLIT_PIXEL);
}
#undef BLIT_PIXEL


PRIVATE ATTR_IN(1) void CC
libvideo_swblitter3__stretch__generic_n__bypixel(struct video_blitter3 const *__restrict self,
                                                 video_coord_t out_x, video_coord_t out_y,
                                                 video_coord_t dst_x, video_coord_t dst_y,
                                                 video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                 video_coord_t src_x, video_coord_t src_y,
                                                 video_dim_t src_size_x, video_dim_t src_size_y) {
	video_dim_t y;
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
	blt3_blend_t blend = video_swblitter3_getcdrv(self)->bsw3_blend;
	stretch_fp_t step_x, step_y, src_pos_y;
	step_x = STRETCH_FP(src_size_x) / dst_size_x;
	step_y = STRETCH_FP(src_size_y) / dst_size_y;
	src_pos_y = step_y >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
	y = 0;
	do {
		video_coord_t row_dst_y = dst_y + y;
		video_coord_t row_out_y = out_y + y;
		video_coord_t row_src_y = src_y + STRETCH_FP_WHOLE(src_pos_y);
		stretch_fp_t src_pos_x = step_x >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
		video_dim_t x = 0;
		src_pos_x += STRETCH_FP(src_x);
		do {
			video_coord_t row_src_x = STRETCH_FP_WHOLE(src_pos_x);
			video_color_t sc = LL_getcolor(src, row_src_x, row_src_y);
			video_color_t dc = LL_getcolor(dst, dst_x + x, row_dst_y);
			video_color_t oc = (*blend)(self, dc, sc);
			LL_putcolor(out, out_x + x, row_out_y, oc);
			src_pos_x += step_x;
			++x;
		} while (x < dst_size_x);
		++y;
		src_pos_y += step_y;
	} while (y < dst_size_y);
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
	video_dim_t y;
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
	blt3_blend_t blend = video_swblitter3_getcdrv(self)->bsw3_blend;
	stretch_fp_t step_x, step_y, src_pos_y;
	gfx_assert_imatrix2d(&dst_matrix);
	gfx_assert_imatrix2d(&src_matrix);

	step_x = STRETCH_FP(src_size_x) / dst_size_x;
	step_y = STRETCH_FP(src_size_y) / dst_size_y;
	src_pos_y = step_y >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
	y = 0;
	do {
		video_coord_t row_out_y = out_y + y;
		video_coord_t row_dst_y = dst_y + y;
		video_coord_t row_src_y = STRETCH_FP_WHOLE(src_pos_y);
		stretch_fp_t src_pos_x = step_x >> 1; /* Start half-a-step ahead, thus rounding by 0.5 pixels */
		video_offset_t delta_src_x = src_x + video_imatrix2d_get(&src_matrix, 0, 1) * row_src_y;
		video_offset_t delta_src_y = src_y + video_imatrix2d_get(&src_matrix, 1, 1) * row_src_y;
		video_offset_t delta_dst_x = dst_x + video_imatrix2d_get(&dst_matrix, 0, 1) * row_dst_y;
		video_offset_t delta_dst_y = dst_y + video_imatrix2d_get(&dst_matrix, 1, 1) * row_dst_y;
		video_dim_t x = 0;
		do {
			video_coord_t row_src_x = STRETCH_FP_WHOLE(src_pos_x);
			video_coord_t used_src_x = delta_src_x + video_imatrix2d_get(&src_matrix, 0, 0) * row_src_x;
			video_coord_t used_src_y = delta_src_y + video_imatrix2d_get(&src_matrix, 1, 0) * row_src_x;
			video_coord_t used_dst_x = delta_dst_x + video_imatrix2d_get(&dst_matrix, 0, 0) * x;
			video_coord_t used_dst_y = delta_dst_y + video_imatrix2d_get(&dst_matrix, 1, 0) * x;
			video_coord_t used_out_x = out_x + x;
			video_coord_t used_out_y = row_out_y;
			video_color_t sc = LL_getcolor(src, used_src_x, used_src_y);
			video_color_t dc = LL_getcolor(dst, used_dst_x, used_dst_y);
			video_color_t oc = (*blend)(self, dc, sc);
			LL_putcolor(out, used_out_x, used_out_y, oc);
			src_pos_x += step_x;
			++x;
		} while (x < dst_size_x);
		++y;
		src_pos_y += step_y;
	} while (y < dst_size_y);
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
	if (LL_rlockregion(src->vx_buffer, &srclock, src_x, src_y, size_x, size_y)) {
		struct video_regionlock dstlock;
		if (LL_rlockregion(dst->vx_buffer, &dstlock, dst_x, dst_y, size_x, size_y)) {
			struct video_regionlock outlock;
			if (LL_wlockregion(out->vx_buffer, &outlock, out_x, out_y, size_x, size_y)) {
				byte_t const *srcline = srclock.vrl_lock.vl_data;
				byte_t const *dstline = dstlock.vrl_lock.vl_data;
				byte_t *outline = outlock.vrl_lock.vl_data;
				struct video_format const *src_format = &src->vx_buffer->vb_format;
				struct video_format const *dst_format = &dst->vx_buffer->vb_format;
				struct video_format const *out_format = &out->vx_buffer->vb_format;
				video_codec_getpixel_t src_getpixel       = src_format->vf_codec->vc_getpixel;
				video_codec_pixel2color_t src_pixel2color = src_format->vf_codec->vc_pixel2color;
				video_codec_getpixel_t dst_getpixel       = dst_format->vf_codec->vc_getpixel;
				video_codec_pixel2color_t dst_pixel2color = dst_format->vf_codec->vc_pixel2color;
				video_codec_setpixel_t out_setpixel       = out_format->vf_codec->vc_setpixel;
				video_codec_color2pixel_t out_color2pixel = out_format->vf_codec->vc_color2pixel;
				do {
					video_coord_t x;
					x = 0;
					do {
						video_pixel_t src_pixel = (*src_getpixel)(srcline, srclock.vrl_xbas + x);
						video_color_t src_color = (*src_pixel2color)(src_format, src_pixel);
						video_pixel_t dst_pixel = (*dst_getpixel)(dstline, dstlock.vrl_xbas + x);
						video_color_t dst_color = (*dst_pixel2color)(dst_format, dst_pixel);
						video_color_t out_color = (*blend)(self, dst_color, src_color);
						video_pixel_t out_pixel = (*out_color2pixel)(out_format, out_color);
						(*out_setpixel)(outline, outlock.vrl_xbas + x, out_pixel);
					} while (++x < size_x);
					srcline += srclock.vrl_lock.vl_stride;
					dstline += dstlock.vrl_lock.vl_stride;
					outline += outlock.vrl_lock.vl_stride;
				} while (--size_y);
				LL_unlockregion(out->vx_buffer, &outlock);
				LL_unlockregion(dst->vx_buffer, &dstlock);
				LL_unlockregion(src->vx_buffer, &srclock);
				goto done;
			}
			LL_unlockregion(dst->vx_buffer, &dstlock);
		}
		LL_unlockregion(src->vx_buffer, &srclock);
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

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_LL_BLIT3_C_INL */
