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
#ifndef GUARD_LIBVIDEO_GFX_SWGFX_LL_BLIT_C_INL
#define GUARD_LIBVIDEO_GFX_SWGFX_LL_BLIT_C_INL 1
#define __VIDEO_BUFFER_const /* nothing -- TODO: This shouldn't be in this file! */
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/syslog.h>

#include <inttypes.h>
#include <malloca.h>
#include <minmax.h>

#include <libvideo/color.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/surface.h>
#include <libvideo/types.h>

#include "../gfx-debug.h"
#include "../gfx-utils.h"
#include "../ramdomain.h"
#include "../swgfx.h"
#include "ll.h"

DECL_BEGIN

#define BLIT_PIXEL(dst_x, dst_y, src_x, src_y)                \
	{                                                         \
		video_color_t color = LL_getcolor(src, src_x, src_y); \
		LL_putcolor(dst, dst_x, dst_y, color);                \
	}

/************************************************************************/
/* GENERIC BLIT OPERATORS                                               */
/************************************************************************/
INTERN ATTR_IN(1) void CC
libvideo_swblitter_generic__blit(struct video_blitter const *__restrict self,
                                 video_coord_t dst_x_, video_coord_t dst_y_,
                                 video_coord_t src_x_, video_coord_t src_y_,
                                 video_dim_t size_x_, video_dim_t size_y_) {
	struct video_gfx const *src = self->vbt_src;
	struct video_gfx const *dst = self->vbt_dst;
	TRACE_START("generic__blit("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_);
	GFX_BLIT_FOREACH(dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_,
	                 BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
	TRACE_END("generic__blit()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_generic__blit_imatrix(struct video_blitter const *__restrict self,
                                         video_coord_t dst_x_, video_coord_t dst_y_,
                                         video_coord_t src_x_, video_coord_t src_y_,
                                         video_dim_t size_x_, video_dim_t size_y_,
                                         video_imatrix2d_t src_matrix) {
	struct video_gfx const *src = self->vbt_src;
	struct video_gfx const *dst = self->vbt_dst;
	gfx_assert_imatrix2d(&src_matrix);

	/* Fast-pass for known matrices */
	if (src_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1)) {
		libvideo_swblitter_generic__blit(self, dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_);
		return;
	}

	/* TODO: More optimizations for known rotation/mirror matrices */

	TRACE_START("generic__blit_imatrix("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "}, "
	            "matrix: {{%d,%d},{%d,%d}})\n",
	            dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1));
	GFX_BLIT_FOREACH_IMATRIX(dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_, src_matrix,
	                         BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
	TRACE_END("generic__blit_imatrix()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_generic__stretch_l(struct video_blitter const *__restrict self,
                                      video_coord_t dst_x_, video_coord_t dst_y_,
                                      video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                      video_coord_t src_x_, video_coord_t src_y_,
                                      video_dim_t src_size_x_, video_dim_t src_size_y_) {
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y) \
	{                                                                             \
		video_color_t out = LL_getcolor(src, src_x, src_y);                       \
		LL_absfill(dst, dst_x, dst_y, dst_size_x, dst_size_y, out);               \
	}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                       \
		video_color_t src_y0_x0 = LL_getcolor(src, src_x0, src_y);                          \
		video_color_t src_y0_x1 = LL_getcolor(src, src_x1, src_y);                          \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);   \
		LL_absline_v(dst, dst_x, dst_y, dst_size_y, out);                                   \
	}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                       \
		video_color_t src_y0_x0 = LL_getcolor(src, src_x, src_y0);                          \
		video_color_t src_y1_x0 = LL_getcolor(src, src_x, src_y1);                          \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);   \
		LL_absline_h(dst, dst_x, dst_y, dst_size_x, out);                                   \
	}

#define pixel_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                 \
		video_color_t src_y0_x0 = LL_getcolor(src, src_x0, src_y0);                                   \
		video_color_t src_y0_x1 = LL_getcolor(src, src_x1, src_y0);                                   \
		video_color_t src_y1_x0 = LL_getcolor(src, src_x0, src_y1);                                   \
		video_color_t src_y1_x1 = LL_getcolor(src, src_x1, src_y1);                                   \
		video_color_t out = interpolate_2d(src_y0_x0, src_y0_x1,                                      \
		                                   src_y1_x0, src_y1_x1,                                      \
		                                   frac_x0, frac_x1,                                          \
		                                   frac_y0, frac_y1);                                         \
		LL_putcolor(dst, dst_x, dst_y, out);                                                          \
	}

	TRACE_START("generic__stretch_l("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            src_x_, src_y_, src_size_x_, src_size_y_);
	GFX_LINEAR_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                   src_x_, src_y_, src_size_x_, src_size_y_,
	                   pixel_blend_xmin_ymin,
	                   pixel_blend_ymin,
	                   pixel_blend_xmax_ymin,
	                   pixel_blend_xmin,
	                   pixel_blend,
	                   pixel_blend_xmax,
	                   pixel_blend_xmin_ymax,
	                   pixel_blend_ymax,
	                   pixel_blend_xmax_ymax);
	TRACE_END("generic__stretch_l()\n");
#undef pixel_blend_xmin_ymin
#undef pixel_blend_ymin
#undef pixel_blend_xmax_ymin
#undef pixel_blend_xmin
#undef pixel_blend
#undef pixel_blend_xmax
#undef pixel_blend_xmin_ymax
#undef pixel_blend_ymax
#undef pixel_blend_xmax_ymax
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_generic__stretch_imatrix_l(struct video_blitter const *__restrict self,
                                              video_coord_t dst_x_, video_coord_t dst_y_,
                                              video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                              video_coord_t src_x_, video_coord_t src_y_,
                                              video_dim_t src_size_x_, video_dim_t src_size_y_,
                                              video_imatrix2d_t src_matrix) {
#define LOCAL_getcolor(x, y)                                                             \
	({                                                                                   \
		video_coord_t used_src_x = src_x_ + video_imatrix2d_get(&src_matrix, 0, 0) * x + video_imatrix2d_get(&src_matrix, 0, 1) * y; \
		video_coord_t used_src_y = src_y_ + video_imatrix2d_get(&src_matrix, 1, 0) * x + video_imatrix2d_get(&src_matrix, 1, 1) * y; \
		LL_getcolor(src, used_src_x, used_src_y);                                        \
	})
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
	gfx_assert_imatrix2d(&src_matrix);

	/* Fast-pass for known matrices */
	if (src_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1)) {
		libvideo_swblitter_generic__stretch_l(self,
		                                      dst_x_, dst_y_, dst_size_x_, dst_size_y_,
		                                      src_x_, src_y_, src_size_x_, src_size_y_);
		return;
	}

	/* TODO: More optimizations for known rotation/mirror matrices */

#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y) \
	{                                                                             \
		video_color_t out = LOCAL_getcolor(src_x, src_y);                         \
		LL_absfill(dst, dst_x, dst_y, dst_size_x, dst_size_y, out);               \
	}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                       \
		video_color_t src_y0_x0 = LOCAL_getcolor(src_x0, src_y);                            \
		video_color_t src_y0_x1 = LOCAL_getcolor(src_x1, src_y);                            \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);   \
		LL_absline_v(dst, dst_x, dst_y, dst_size_y, out);                                   \
	}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                       \
		video_color_t src_y0_x0 = LOCAL_getcolor(src_x, src_y0);                            \
		video_color_t src_y1_x0 = LOCAL_getcolor(src_x, src_y1);                            \
		video_color_t out       = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);   \
		LL_absline_h(dst, dst_x, dst_y, dst_size_x, out);                                   \
	}

#define pixel_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                 \
		video_color_t src_y0_x0 = LOCAL_getcolor(src_x0, src_y0);                                     \
		video_color_t src_y0_x1 = LOCAL_getcolor(src_x1, src_y0);                                     \
		video_color_t src_y1_x0 = LOCAL_getcolor(src_x0, src_y1);                                     \
		video_color_t src_y1_x1 = LOCAL_getcolor(src_x1, src_y1);                                     \
		video_color_t out = interpolate_2d(src_y0_x0, src_y0_x1,                                      \
		                                   src_y1_x0, src_y1_x1,                                      \
		                                   frac_x0, frac_x1,                                          \
		                                   frac_y0, frac_y1);                                         \
		LL_putcolor(dst, dst_x, dst_y, out);                                                          \
	}
	TRACE_START("generic__stretch_imatrix_l("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "matrix: {{%d,%d},{%d,%d}})\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            src_x_, src_y_, src_size_x_, src_size_y_,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1));
	GFX_LINEAR_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                   0, 0, src_size_x_, src_size_y_,
	                   pixel_blend_xmin_ymin,
	                   pixel_blend_ymin,
	                   pixel_blend_xmax_ymin,
	                   pixel_blend_xmin,
	                   pixel_blend,
	                   pixel_blend_xmax,
	                   pixel_blend_xmin_ymax,
	                   pixel_blend_ymax,
	                   pixel_blend_xmax_ymax);
	TRACE_END("generic__stretch_imatrix_l()\n");
#undef pixel_blend_xmin_ymin
#undef pixel_blend_ymin
#undef pixel_blend_xmax_ymin
#undef pixel_blend_xmin
#undef pixel_blend
#undef pixel_blend_xmax
#undef pixel_blend_xmin_ymax
#undef pixel_blend_ymax
#undef pixel_blend_xmax_ymax
#undef LOCAL_getcolor
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_generic__stretch_n(struct video_blitter const *__restrict self,
                                      video_coord_t dst_x_, video_coord_t dst_y_,
                                      video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                      video_coord_t src_x_, video_coord_t src_y_,
                                      video_dim_t src_size_x_, video_dim_t src_size_y_) {
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
	TRACE_START("generic__stretch_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            src_x_, src_y_, src_size_x_, src_size_y_);
	GFX_NEAREST_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                    src_x_, src_y_, src_size_x_, src_size_y_,
	                    BLIT_PIXEL,
	                    GFX_ROW_NOOP,
	                    GFX_ROW_NOOP);
	TRACE_END("generic__stretch_n()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_generic__stretch_imatrix_n(struct video_blitter const *__restrict self,
                                              video_coord_t dst_x_, video_coord_t dst_y_,
                                              video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                              video_coord_t src_x_, video_coord_t src_y_,
                                              video_dim_t src_size_x_, video_dim_t src_size_y_,
                                              video_imatrix2d_t src_matrix) {
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
	gfx_assert_imatrix2d(&src_matrix);

	/* Fast-pass for known matrices */
	if (src_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1)) {
		libvideo_swblitter_generic__stretch_n(self,
		                                      dst_x_, dst_y_, dst_size_x_, dst_size_y_,
		                                      src_x_, src_y_, src_size_x_, src_size_y_);
		return;
	}
	TRACE_START("generic__stretch_imatrix_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "matrix: {{%d,%d},{%d,%d}})\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            src_x_, src_y_, src_size_x_, src_size_y_,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0), (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0), (int)video_imatrix2d_get(&src_matrix, 1, 1));
	GFX_NEAREST_STRETCH_IMATRIX(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                            src_x_, src_y_, src_size_x_, src_size_y_,
	                            src_matrix, BLIT_PIXEL,
	                            GFX_ROW_NOOP,
	                            GFX_ROW_NOOP);
	TRACE_END("generic__stretch_imatrix_n()\n");
}


PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_generic__blit__rev(struct video_blitter const *__restrict self,
                                      video_coord_t dst_x_, video_coord_t dst_y_,
                                      video_coord_t src_x_, video_coord_t src_y_,
                                      video_dim_t size_x_, video_dim_t size_y_) {
	struct video_gfx const *src = self->vbt_src;
	struct video_gfx const *dst = self->vbt_dst;
	TRACE_START("generic__blit__rev("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_);
	GFX_BLIT_FOREACH_REV(dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_,
	                     BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
	TRACE_END("generic__blit__rev()\n");
}

/* Special impls for when the blit src/dst are identical */
INTERN ATTR_IN(1) void CC
libvideo_swblitter_samebuf__blit(struct video_blitter const *__restrict self,
                                 video_coord_t dst_x, video_coord_t dst_y,
                                 video_coord_t src_x, video_coord_t src_y,
                                 video_dim_t size_x, video_dim_t size_y) {
	if (xy_before_or_equal(dst_x, dst_y, src_x, src_y)) {
		libvideo_swblitter_generic__blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
	} else {
		libvideo_swblitter_generic__blit__rev(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
	}
}

PRIVATE ATTR_NOINLINE ATTR_IN(1) void CC
libvideo_swblitter_samebuf__stretch__with_temporary(struct video_blitter const *__restrict self,
                                                    video_coord_t dst_x, video_coord_t dst_y,
                                                    video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                    video_coord_t src_x, video_coord_t src_y,
                                                    video_dim_t src_size_x, video_dim_t src_size_y) {
	struct video_buffer const *srcbuf = video_gfx_getbuffer(self->vbt_src);
	video_dim_t common_size_x, common_size_y;
	struct video_rambuffer_requirements req;
	struct video_rambuffer rb;
	struct video_blitter blitter;
	struct video_gfx rb_gfx;

	/*rb.vb_refcnt = 1;*/
	common_size_x = min(dst_size_x, src_size_x);
	common_size_y = min(dst_size_y, src_size_y);
	__video_buffer_init_ops(&rb, _rambuffer_ops());
	__video_buffer_init_dim(&rb, common_size_x, common_size_y);
	(*rb.vb_codec->vc_rambuffer_requirements)(common_size_x, common_size_y, &req);
	rb.vb_codec  = video_buffer_getcodec(srcbuf);
	rb.rb_stride = req.vbs_stride;
	rb.rb_data   = (byte_t *)malloca(req.vbs_bufsize);
	if unlikely(!rb.rb_data) {
		/* Well... Nothing we can do about it... :( */
		syslog(LOG_WARN, "[libvideo-gfx] Failed to allocate %" PRIuSIZ " bytes for temporary buffer\n",
		       req.vbs_bufsize);
		return;
	}

	rb_gfx.vg_surf.vs_buffer = &rb;
	rb_gfx.vg_surf.vs_pal    = video_gfx_getpalette(self->vbt_src);
	rb_gfx.vg_surf.vs_flags  = video_gfx_getflags(self->vbt_src);
	/*rb_gfx.vg_surf.vs_colorkey = self->vbt_src->vg_surf.vs_colorkey;*/
	rb_gfx.vg_blend = GFX_BLENDMODE_OVERRIDE;
	blitter.vbt_src = self->vbt_src;
	blitter.vbt_dst = rambuffer__initgfx(&rb_gfx);
	/*(*self->vbt_src->vg_clip.vxh_blitfrom)(&blitter);*/ /* Cheat a bit and skip this part... */

	/* Blit source into temporary buffer... */
	if (src_size_x == video_buffer_getxdim(&rb) &&
	    src_size_y == video_buffer_getydim(&rb)) {
		libvideo_swblitter_noblend_samefmt__blit(&blitter, 0, 0,
		                                         src_x, src_y, src_size_x, src_size_y);
	} else if (video_gfx_getflags(&rb_gfx) & VIDEO_GFX_F_LINEAR) {
		libvideo_swblitter_noblend_samefmt__stretch_l(&blitter, 0, 0,
		                                              video_buffer_getxdim(&rb),
		                                              video_buffer_getydim(&rb),
		                                              src_x, src_y, src_size_x, src_size_y);
	} else {
		libvideo_swblitter_noblend_samefmt__stretch_n(&blitter, 0, 0,
		                                              video_buffer_getxdim(&rb),
		                                              video_buffer_getydim(&rb),
		                                              src_x, src_y, src_size_x, src_size_y);
	}

	/* Blit temporary buffer into target... */
	blitter.vbt_src = blitter.vbt_dst;
	blitter.vbt_dst = self->vbt_dst;
	/*(*rb_gfx.vg_clip.vxh_blitfrom)(&blitter);*/ /* Cheat a bit and skip this part... */
	if (dst_size_x == video_buffer_getxdim(&rb) &&
	    dst_size_y == video_buffer_getydim(&rb)) {
		libvideo_swblitter_noblend_samefmt__blit(&blitter, dst_x, dst_y,
		                                         0, 0, dst_size_x, dst_size_y);
	} else if (video_gfx_getflags(&rb_gfx) & VIDEO_GFX_F_LINEAR) {
		libvideo_swblitter_noblend_samefmt__stretch_l(&blitter, dst_x, dst_y,
		                                              dst_size_x, dst_size_y, 0, 0,
		                                              video_buffer_getxdim(&rb),
		                                              video_buffer_getydim(&rb));
	} else {
		libvideo_swblitter_noblend_samefmt__stretch_n(&blitter, dst_x, dst_y,
		                                              dst_size_x, dst_size_y, 0, 0,
		                                              video_buffer_getxdim(&rb),
		                                              video_buffer_getydim(&rb));
	}

	/* Free temporary buffer... */
	freea(rb.rb_data);
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_generic__stretch_l__rev(struct video_blitter const *__restrict self,
                                           video_coord_t dst_x_, video_coord_t dst_y_,
                                           video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                           video_coord_t src_x_, video_coord_t src_y_,
                                           video_dim_t src_size_x_, video_dim_t src_size_y_) {
	/* TODO */
	libvideo_swblitter_generic__stretch_l(self,
	                                      dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                                      src_x_, src_y_, src_size_x_, src_size_y_);
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_samebuf__stretch_l(struct video_blitter const *__restrict self,
                                      video_coord_t dst_x, video_coord_t dst_y,
                                      video_dim_t dst_size_x, video_dim_t dst_size_y,
                                      video_coord_t src_x, video_coord_t src_y,
                                      video_dim_t src_size_x, video_dim_t src_size_y) {
	video_coord_t dst_xend = dst_x + dst_size_x;
	video_coord_t dst_yend = dst_y + dst_size_y;
	video_coord_t src_xend = src_x + src_size_x;
	video_coord_t src_yend = src_y + src_size_y;
	bool dst_xymin_before_src_xymin = xy_before_or_equal(dst_x, dst_y, src_x, src_y);
	bool dst_xyend_before_src_xyend = xy_before_or_equal(dst_xend, dst_yend, src_xend, src_yend);
	if (dst_xymin_before_src_xymin && dst_xyend_before_src_xyend) {
		libvideo_swblitter_generic__stretch_l(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y);
	} else if (!dst_xymin_before_src_xymin && !dst_xyend_before_src_xyend) {
		libvideo_swblitter_generic__stretch_l__rev(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y);
	} else if (dst_xend <= src_x || dst_yend <= src_y || dst_x >= src_xend || dst_y >= src_yend) {
		libvideo_swblitter_generic__stretch_l(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y);
	} else {
		/* Special case: destination- and source-rect overlap in such a way that
		 * we need a temporary copy of the source rect so-as not to clobber data
		 * that has yet to be read. */
		libvideo_swblitter_samebuf__stretch__with_temporary(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y);
	}
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_generic__stretch_n__rev(struct video_blitter const *__restrict self,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_dim_t dst_size_x, video_dim_t dst_size_y,
                                           video_coord_t src_x, video_coord_t src_y,
                                           video_dim_t src_size_x, video_dim_t src_size_y) {
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
	TRACE_START("generic__stretch_n__rev("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            src_x, src_y, src_size_x, src_size_y);
	GFX_NEAREST_STRETCH_REV(dst_x, dst_y, dst_size_x, dst_size_y,
	                        src_x, src_y, src_size_x, src_size_y,
	                        BLIT_PIXEL,
	                        GFX_ROW_NOOP,
	                        GFX_ROW_NOOP);
	TRACE_END("generic__stretch_n__rev()\n");
}


INTERN ATTR_IN(1) void CC
libvideo_swblitter_samebuf__stretch_n(struct video_blitter const *__restrict self,
                                      video_coord_t dst_x, video_coord_t dst_y,
                                      video_dim_t dst_size_x, video_dim_t dst_size_y,
                                      video_coord_t src_x, video_coord_t src_y,
                                      video_dim_t src_size_x, video_dim_t src_size_y) {
	video_coord_t dst_xend = dst_x + dst_size_x;
	video_coord_t dst_yend = dst_y + dst_size_y;
	video_coord_t src_xend = src_x + src_size_x;
	video_coord_t src_yend = src_y + src_size_y;
	bool dst_xymin_before_src_xymin = xy_before_or_equal(dst_x, dst_y, src_x, src_y);
	bool dst_xyend_before_src_xyend = xy_before_or_equal(dst_xend, dst_yend, src_xend, src_yend);
	if (dst_xymin_before_src_xymin && dst_xyend_before_src_xyend) {
		libvideo_swblitter_generic__stretch_n(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y);
	} else if (!dst_xymin_before_src_xymin && !dst_xyend_before_src_xyend) {
		libvideo_swblitter_generic__stretch_n__rev(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y);
	} else if (dst_xend <= src_x || dst_yend <= src_y || dst_x >= src_xend || dst_y >= src_yend) {
		libvideo_swblitter_generic__stretch_n(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y);
	} else {
		/* Special case: destination- and source-rect overlap in such a way that
		 * we need a temporary copy of the source rect so-as not to clobber data
		 * that has yet to be read. */
		libvideo_swblitter_samebuf__stretch__with_temporary(self, dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y);
	}
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_samebuf__blit_imatrix(struct video_blitter const *__restrict self,
                                         video_coord_t dst_x, video_coord_t dst_y,
                                         video_coord_t src_x, video_coord_t src_y,
                                         video_dim_t size_x, video_dim_t size_y,
                                         video_imatrix2d_t src_matrix) {
	/* TODO: Overlap handling */
	libvideo_swblitter_generic__blit_imatrix(self, dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix);
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_samebuf__stretch_imatrix_l(struct video_blitter const *__restrict self,
                                              video_coord_t dst_x, video_coord_t dst_y,
                                              video_dim_t dst_size_x, video_dim_t dst_size_y,
                                              video_coord_t src_x, video_coord_t src_y,
                                              video_dim_t src_size_x, video_dim_t src_size_y,
                                              video_imatrix2d_t src_matrix) {
	/* TODO: Overlap handling */
	libvideo_swblitter_generic__stretch_imatrix_l(self,
	                                              dst_x, dst_y, dst_size_x, dst_size_y,
	                                              src_x, src_y, src_size_x, src_size_y,
	                                              src_matrix);
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_samebuf__stretch_imatrix_n(struct video_blitter const *__restrict self,
                                              video_coord_t dst_x, video_coord_t dst_y,
                                              video_dim_t dst_size_x, video_dim_t dst_size_y,
                                              video_coord_t src_x, video_coord_t src_y,
                                              video_dim_t src_size_x, video_dim_t src_size_y,
                                              video_imatrix2d_t src_matrix) {
	/* TODO: Overlap handling */
	libvideo_swblitter_generic__stretch_imatrix_n(self,
	                                              dst_x, dst_y, dst_size_x, dst_size_y,
	                                              src_x, src_y, src_size_x, src_size_y,
	                                              src_matrix);
}

#undef BLIT_PIXEL

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_LL_BLIT_C_INL */
