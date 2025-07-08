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
#ifndef GUARD_LIBVIDEO_GFX_SWGFX_LL_NOBLEND_BLIT_C_INL
#define GUARD_LIBVIDEO_GFX_SWGFX_LL_NOBLEND_BLIT_C_INL 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/wordbits.h>

#include <kos/types.h>

#include <inttypes.h>
#include <stdint.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "../gfx-debug.h"
#include "../gfx-utils.h"
#include "../swgfx.h"
#include "ll.h"

DECL_BEGIN

/* *__bypixel functions from "./ll_noblend.c.inl" */
#ifdef __INTELLISENSE__
PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend__absline_h__bypixel(struct video_gfx const *__restrict self,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_dim_t length, video_pixel_t pixel);
PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend__absline_v__bypixel(struct video_gfx const *__restrict self,
                                           video_coord_t dst_x, video_coord_t dst_y,
                                           video_dim_t length, video_pixel_t pixel);
PRIVATE ATTR_IN(1) void CC
libvideo_swgfx_noblend__absfill__bypixel(struct video_gfx const *__restrict self,
                                         video_coord_t dst_x, video_coord_t dst_y,
                                         video_dim_t size_x, video_dim_t size_y,
                                         video_pixel_t pixel);
#endif /* __INTELLISENSE__ */


/************************************************************************/
/* MASKED FILL/STRETCH                                                  */
/************************************************************************/

PRIVATE ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
libvideo_swgfx_noblend__fillstretchmask_n__bypixel(struct video_gfx const *__restrict self,
                                                   video_coord_t dst_x_, video_coord_t dst_y_,
                                                   video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                                   video_pixel_t const bg_fg_pixels[2],
                                                   video_dim_t src_size_x_, video_dim_t src_size_y_,
                                                   struct video_bitmask const *__restrict bm) {
#define LOCAL_dst_startrow(dst_y, src_y) \
	uintptr_t row_bitno = bm->vbm_skip + src_y * bm->vbm_scan
#define LOCAL_copy_pixel(dst_x, dst_y, src_x, src_y)                \
	{                                                               \
		uintptr_t bitno = row_bitno + src_x;                        \
		byte_t byte = ((byte_t const *)bm->vbm_mask)[bitno / NBBY]; \
		byte_t bit = (byte >> ((NBBY - 1) - (bitno % NBBY))) & 1;   \
		LL_setpixel(self, dst_x, dst_y, bg_fg_pixels[bit]);         \
	}
	GFX_NEAREST_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_, 0, 0, src_size_x_, src_size_y_,
	                    LOCAL_copy_pixel, LOCAL_dst_startrow, GFX_ROW_NOOP);
#undef LOCAL_copy_pixel
#undef LOCAL_dst_startrow
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
libvideo_swgfx_noblend__fillstretchmask_n(struct video_gfx const *__restrict self,
                                          video_coord_t dst_x_, video_coord_t dst_y_,
                                          video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                          video_color_t const bg_fg_colors[2],
                                          video_dim_t src_size_x_, video_dim_t src_size_y_,
                                          struct video_bitmask const *__restrict bm) {
	struct video_regionlock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_color_t bg_fg_pixels[2];
	bg_fg_pixels[0] = video_format_color2pixel(&buffer->vb_format, bg_fg_colors[0]);
	bg_fg_pixels[1] = video_format_color2pixel(&buffer->vb_format, bg_fg_colors[1]);
	TRACE_START("swgfx_noblend__fillstretchmask_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "bg_fg_colors: {%#" PRIxCOL ", %#" PRIxCOL "}, "
	            "src: {%" PRIuDIM "x%" PRIuDIM "}, bm: %p+%" PRIuPTR ")\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            bg_fg_colors[0], bg_fg_colors[1],
	            src_size_x_, src_size_y_, bm->vbm_mask, bm->vbm_skip);
	if likely(LL_wlockregion(buffer, &lock, dst_x_, dst_y_, dst_size_x_, dst_size_y_)) {
		video_codec_setpixel_t vc_setpixel = buffer->vb_format.vf_codec->vc_setpixel;
		byte_t *dst_line = lock.vrl_lock.vl_data;
#define LOCAL_dst_startrow(dst_y, src_y) \
		uintptr_t row_bitno = bm->vbm_skip + src_y * bm->vbm_scan; (void)dst_y
#define LOCAL_copy_pixel(dst_x, dst_y, src_x, src_y)                            \
		{                                                                       \
			uintptr_t bitno = row_bitno + src_x;                                \
			byte_t byte = ((byte_t const *)bm->vbm_mask)[bitno / NBBY];         \
			byte_t bit = (byte >> ((NBBY - 1) - (bitno % NBBY))) & 1;           \
			(*vc_setpixel)(dst_line, lock.vrl_xbas + dst_x, bg_fg_pixels[bit]); \
		}
#define LOCAL_dst_endrow(dst_y, src_y) \
		dst_line += lock.vrl_lock.vl_stride
		GFX_NEAREST_STRETCH((video_coord_t)lock.vrl_xbas, 0, dst_size_x_, dst_size_y_,
		                    0, 0, src_size_x_, src_size_y_,
		                    LOCAL_copy_pixel, LOCAL_dst_startrow, LOCAL_dst_endrow);
#undef LOCAL_dst_endrow
#undef LOCAL_copy_pixel
#undef LOCAL_dst_startrow
		LL_unlockregion(buffer, &lock);
	} else {
		libvideo_swgfx_noblend__fillstretchmask_n__bypixel(self, dst_x_, dst_y_, dst_size_x_, dst_size_y_,
		                                                   bg_fg_pixels, src_size_x_, src_size_y_, bm);
	}
	TRACE_END("swgfx_noblend__fillstretchmask_n()\n");
}

PRIVATE ATTR_IN(1) ATTR_IN(9) void CC
libvideo_swgfx_noblend__fillstretchmask1_n__bypixel(struct video_gfx const *__restrict self,
                                                    video_coord_t dst_x_, video_coord_t dst_y_,
                                                    video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                                    video_pixel_t pixel,
                                                    video_dim_t src_size_x_, video_dim_t src_size_y_,
                                                    struct video_bitmask const *__restrict bm,
                                                    __REGISTER_TYPE__ bm_xor) {
#define LOCAL_dst_startrow(dst_y, src_y) \
	uintptr_t row_bitno = bm->vbm_skip + src_y * bm->vbm_scan
#define LOCAL_copy_pixel(dst_x, dst_y, src_x, src_y)                                 \
	{                                                                                \
		uintptr_t bitno = row_bitno + src_x;                                         \
		byte_t byte = ((byte_t const *)bm->vbm_mask)[bitno / NBBY] ^ (byte_t)bm_xor; \
		byte_t bit = (byte >> ((NBBY - 1) - (bitno % NBBY))) & 1;                    \
		if (bit)                                                                     \
			LL_setpixel(self, dst_x, dst_y, pixel);                                  \
	}
	GFX_NEAREST_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_, 0, 0, src_size_x_, src_size_y_,
	                    LOCAL_copy_pixel, LOCAL_dst_startrow, GFX_ROW_NOOP);
#undef LOCAL_copy_pixel
#undef LOCAL_dst_startrow
}

INTERN ATTR_IN(1) ATTR_IN(9) void CC
libvideo_swgfx_noblend__fillstretchmask1_n(struct video_gfx const *__restrict self,
                                           video_coord_t dst_x_, video_coord_t dst_y_,
                                           video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                           video_color_t color,
                                           video_dim_t src_size_x_, video_dim_t src_size_y_,
                                           struct video_bitmask const *__restrict bm,
                                           __REGISTER_TYPE__ bm_xor) {
	struct video_regionlock lock;
	struct video_buffer *buffer = self->vx_buffer;
	video_pixel_t pixel = video_format_color2pixel(&buffer->vb_format, color);
	TRACE_START("swgfx_noblend__fillstretchmask1_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "color: %#" PRIxCOL ", "
	            "src: {%" PRIuDIM "x%" PRIuDIM "}, bm: %p+%" PRIuPTR "^%#" PRIxPTR ")\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            color, src_size_x_, src_size_y_, bm->vbm_mask,
	            bm->vbm_skip, (uintptr_t)bm_xor);
	if likely(LL_wlockregion(buffer, &lock, dst_x_, dst_y_, dst_size_x_, dst_size_y_)) {
		video_codec_setpixel_t vc_setpixel = buffer->vb_format.vf_codec->vc_setpixel;
		byte_t *dst_line = lock.vrl_lock.vl_data;
#define LOCAL_dst_startrow(dst_y, src_y) \
		uintptr_t row_bitno = bm->vbm_skip + src_y * bm->vbm_scan; (void)dst_y
#define LOCAL_copy_pixel(dst_x, dst_y, src_x, src_y)                    \
		{                                                               \
			uintptr_t bitno = row_bitno + src_x;                        \
			byte_t byte = ((byte_t const *)bm->vbm_mask)[bitno / NBBY]; \
			byte_t bit = (byte >> ((NBBY - 1) - (bitno % NBBY))) & 1;   \
			if (bit)                                                    \
				LL_setpixel(self, dst_x, dst_y, pixel);                 \
		}
#define LOCAL_dst_endrow(dst_y, src_y) \
		dst_line += lock.vrl_lock.vl_stride
		GFX_NEAREST_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_, 0, 0, src_size_x_, src_size_y_,
		                    LOCAL_copy_pixel, LOCAL_dst_startrow, LOCAL_dst_endrow);
#undef LOCAL_dst_endrow
#undef LOCAL_copy_pixel
#undef LOCAL_dst_startrow
		LL_unlockregion(buffer, &lock);
	} else {
		libvideo_swgfx_noblend__fillstretchmask1_n__bypixel(self, dst_x_, dst_y_, dst_size_x_, dst_size_y_,
		                                                    pixel, src_size_x_, src_size_y_, bm, bm_xor);
	}
	TRACE_END("swgfx_noblend__fillstretchmask1_n()\n");
}





/************************************************************************/
/* BLITTER                                                              */
/************************************************************************/

#define BLIT_PIXEL(px_dst_x, px_dst_y, px_src_x, px_src_y) \
	{                                                      \
		video_pixel_t pixel;                               \
		pixel = LL_getpixel(src, px_src_x, px_src_y);      \
		LL_setpixel(dst, px_dst_x, px_dst_y, pixel);       \
	}
PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__blit__bypixel(struct video_blitter const *__restrict self,
                                                  video_coord_t dst_x, video_coord_t dst_y,
                                                  video_coord_t src_x, video_coord_t src_y,
                                                  video_dim_t size_x, video_dim_t size_y) {
	struct video_gfx const *src = self->vbt_src;
	struct video_gfx const *dst = self->vbt_dst;
	GFX_BLIT_FOREACH(dst_x, dst_y, src_x, src_y, size_x, size_y,
	                 BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__blit__bypixel__rev(struct video_blitter const *__restrict self,
                                                       video_coord_t dst_x, video_coord_t dst_y,
                                                       video_coord_t src_x, video_coord_t src_y,
                                                       video_dim_t size_x, video_dim_t size_y) {
	struct video_gfx const *src = self->vbt_src;
	struct video_gfx const *dst = self->vbt_dst;
	GFX_BLIT_FOREACH_REV(dst_x, dst_y, src_x, src_y, size_x, size_y,
	                     BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__blit_imatrix__bypixel(struct video_blitter const *__restrict self,
                                                          video_coord_t dst_x, video_coord_t dst_y,
                                                          video_coord_t src_x, video_coord_t src_y,
                                                          video_dim_t size_x, video_dim_t size_y,
                                                          video_imatrix2d_t src_matrix) {
	struct video_gfx const *src = self->vbt_src;
	struct video_gfx const *dst = self->vbt_dst;
	GFX_BLIT_FOREACH_IMATRIX(dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix,
	                         BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__stretch_n__bypixel(struct video_blitter const *__restrict self,
                                                       video_coord_t dst_x_, video_coord_t dst_y_,
                                                       video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                                       video_coord_t src_x_, video_coord_t src_y_,
                                                       video_dim_t src_size_x_, video_dim_t src_size_y_) {
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
	GFX_NEAREST_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                    src_x_, src_y_, src_size_x_, src_size_y_,
	                    BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__stretch_imatrix_n__bypixel(struct video_blitter const *__restrict self,
                                                               video_coord_t dst_x_, video_coord_t dst_y_,
                                                               video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                                               video_coord_t src_x_, video_coord_t src_y_,
                                                               video_dim_t src_size_x_, video_dim_t src_size_y_,
                                                               video_imatrix2d_t src_matrix) {
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
	GFX_NEAREST_STRETCH_IMATRIX(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                            src_x_, src_y_, src_size_x_, src_size_y_, src_matrix,
	                            BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}
#undef BLIT_PIXEL


INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__blit(struct video_blitter const *__restrict self,
                                         video_coord_t dst_x, video_coord_t dst_y,
                                         video_coord_t src_x, video_coord_t src_y,
                                         video_dim_t size_x, video_dim_t size_y) {
	struct video_regionlock dst_lock;
	struct video_buffer *dst_buffer = self->vbt_dst->vx_buffer;
	TRACE_START("noblend_samefmt__blit("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x, dst_y, src_x, src_y, size_x, size_y);
	if likely(LL_wlockregion(dst_buffer, &dst_lock, dst_x, dst_y, size_x, size_y)) {
		struct video_regionlock src_lock;
		struct video_buffer *src_buffer = self->vbt_src->vx_buffer;
		if likely(LL_rlockregion(src_buffer, &src_lock, src_x, src_y, size_x, size_y)) {
			video_codec_rectcopy_t vc_rectcopy = dst_buffer->vb_format.vf_codec->vc_rectcopy;
			(*vc_rectcopy)(dst_lock.vrl_lock.vl_data, dst_lock.vrl_xbas, dst_lock.vrl_lock.vl_stride,
			               src_lock.vrl_lock.vl_data, src_lock.vrl_xbas, src_lock.vrl_lock.vl_stride,
			               size_x, size_y);
			LL_unlockregion(src_buffer, &src_lock);
			LL_unlockregion(dst_buffer, &dst_lock);
			goto done;
		}
		LL_unlockregion(dst_buffer, &dst_lock);
	}
	/* Use pixel-based rendering */
	libvideo_swblitter_noblend_samefmt__blit__bypixel(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
done:
	TRACE_END("noblend_samefmt__blit()\n");
}


INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__blit_imatrix(struct video_blitter const *__restrict self,
                                                 video_coord_t dst_x, video_coord_t dst_y,
                                                 video_coord_t src_x, video_coord_t src_y,
                                                 video_dim_t size_x, video_dim_t size_y,
                                                 video_imatrix2d_t src_matrix) {
	gfx_assert_imatrix2d(&src_matrix);

	/* Fast-pass for known matrices */
	switch (src_matrix) {
	case VIDEO_IMATRIX2D_INIT(1, 0, 0, 1):
		libvideo_swblitter_noblend_samefmt__blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
		return;
		/* TODO: More optimizations for known rotation/mirror matrices */
	case VIDEO_IMATRIX2D_INIT(1, 0, 0, -1):
		/* TODO: vflip */
		break;
	case VIDEO_IMATRIX2D_INIT(-1, 0, 0, 1):
		/* TODO: hflip */
		break;
	case VIDEO_IMATRIX2D_INIT(0, -1, 1, 0):
		/* TODO: lrot90 */
		break;
	case VIDEO_IMATRIX2D_INIT(0, 1, -1, 0):
		/* TODO: rrot90 */
		break;
	case VIDEO_IMATRIX2D_INIT(-1, 0, 0, -1):
		/* TODO: rot180 */
		break;
	default: break;
	}


	TRACE_START("noblend_samefmt__blit_imatrix("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "}, "
	            "matrix: {{%d,%d},{%d,%d}})\n",
	            dst_x, dst_y, src_x, src_y, size_x, size_y,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1));

	/* TODO: Use video locks if possible */

	/* Blit per-pixel, with pixel format converter */
	libvideo_swblitter_noblend_samefmt__blit_imatrix__bypixel(self, dst_x, dst_y, src_x, src_y,
	                                                          size_x, size_y, src_matrix);
	TRACE_END("noblend_samefmt__blit_imatrix()\n");
}



INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__stretch_n(struct video_blitter const *__restrict self,
                                              video_coord_t dst_x_, video_coord_t dst_y_,
                                              video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                              video_coord_t src_x_, video_coord_t src_y_,
                                              video_dim_t src_size_x_, video_dim_t src_size_y_) {
	struct video_regionlock dst_lock;
	struct video_buffer *dst_buffer = self->vbt_dst->vx_buffer;
	TRACE_START("swblitter_noblend_samefmt__stretch_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            src_x_, src_y_, src_size_x_, src_size_y_);
	if likely(LL_wlockregion(dst_buffer, &dst_lock, dst_x_, dst_y_, dst_size_x_, dst_size_y_)) {
		struct video_regionlock src_lock;
		struct video_buffer *src_buffer = self->vbt_src->vx_buffer;
		if likely(LL_rlockregion(src_buffer, &src_lock, src_x_, src_y_, src_size_x_, src_size_y_)) {
			byte_t *dst_line = dst_lock.vrl_lock.vl_data;
			video_codec_getpixel_t vc_getpixel = src_buffer->vb_format.vf_codec->vc_getpixel;
			video_codec_setpixel_t vc_setpixel = dst_buffer->vb_format.vf_codec->vc_setpixel;
#define LOCAL_dst_startrow(dst_y, src_y) \
			byte_t const *src_line = src_lock.vrl_lock.vl_data + src_y * src_lock.vrl_lock.vl_stride
#define LOCAL_copy_pixel(dst_x, dst_y, src_x, src_y)               \
			{                                                      \
				video_pixel_t s = (*vc_getpixel)(src_line, src_x); \
				(*vc_setpixel)(dst_line, dst_x, s);                \
			}
#define LOCAL_dst_endrow(dst_y, src_y) \
			dst_line += dst_lock.vrl_lock.vl_stride; (void)dst_y
			GFX_NEAREST_STRETCH((video_coord_t)dst_lock.vrl_xbas, 0, dst_size_x_, dst_size_y_,
			                    (video_coord_t)src_lock.vrl_xbas, 0, src_size_x_, src_size_y_,
			                    LOCAL_copy_pixel, LOCAL_dst_startrow, LOCAL_dst_endrow);
#undef LOCAL_dst_endrow
#undef LOCAL_copy_pixel
#undef LOCAL_dst_startrow
			LL_unlockregion(src_buffer, &src_lock);
			LL_unlockregion(dst_buffer, &dst_lock);
			goto done;
		}
		LL_unlockregion(dst_buffer, &dst_lock);
	}
	libvideo_swblitter_noblend_samefmt__stretch_n__bypixel(self,
	                                                       dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                                                       src_x_, src_y_, src_size_x_, src_size_y_);
done:
	TRACE_END("swblitter_noblend_samefmt__stretch_n()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__stretch_imatrix_n(struct video_blitter const *__restrict self,
                                                      video_coord_t dst_x_, video_coord_t dst_y_,
                                                      video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                                      video_coord_t src_x_, video_coord_t src_y_,
                                                      video_dim_t src_size_x_, video_dim_t src_size_y_,
                                                      video_imatrix2d_t src_matrix) {
	struct video_regionlock dst_lock;
	struct video_buffer *dst_buffer = self->vbt_dst->vx_buffer;
	TRACE_START("swblitter_noblend_samefmt__stretch_imatrix_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            src_x_, src_y_, src_size_x_, src_size_y_);
	if likely(LL_wlockregion(dst_buffer, &dst_lock, dst_x_, dst_y_, dst_size_x_, dst_size_y_)) {
		struct video_regionlock src_lock;
		struct video_buffer *src_buffer = self->vbt_src->vx_buffer;
		if likely(LL_rlockregion(src_buffer, &src_lock, src_x_, src_y_, src_size_x_, src_size_y_)) {
			byte_t *dst_line = dst_lock.vrl_lock.vl_data;
			video_codec_getpixel_t vc_getpixel = src_buffer->vb_format.vf_codec->vc_getpixel;
			video_codec_setpixel_t vc_setpixel = dst_buffer->vb_format.vf_codec->vc_setpixel;
#define LOCAL_copy_pixel(dst_x, dst_y, src_x, src_y)                          \
			{                                                                 \
				byte_t const *src_line = src_lock.vrl_lock.vl_data +          \
				                         src_y * src_lock.vrl_lock.vl_stride; \
				video_pixel_t s = (*vc_getpixel)(src_line, src_x);            \
				(*vc_setpixel)(dst_line, dst_x, s);                           \
			}
#define LOCAL_dst_endrow(dst_y) \
			dst_line += dst_lock.vrl_lock.vl_stride; (void)dst_y
			GFX_NEAREST_STRETCH_IMATRIX((video_coord_t)dst_lock.vrl_xbas, 0, dst_size_x_, dst_size_y_,
			                            (video_coord_t)src_lock.vrl_xbas, 0, src_size_x_, src_size_y_,
			                            src_matrix, LOCAL_copy_pixel, GFX_ROW_NOOP, LOCAL_dst_endrow);
#undef LOCAL_dst_endrow
#undef LOCAL_copy_pixel
			LL_unlockregion(src_buffer, &src_lock);
			LL_unlockregion(dst_buffer, &dst_lock);
			goto done;
		}
		LL_unlockregion(dst_buffer, &dst_lock);
	}
	libvideo_swblitter_noblend_samefmt__stretch_imatrix_n__bypixel(self,
	                                                               dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                                                               src_x_, src_y_, src_size_x_, src_size_y_,
	                                                               src_matrix);
done:
	TRACE_END("swblitter_noblend_samefmt__stretch_imatrix_n()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__stretch_l(struct video_blitter const *__restrict self,
                                              video_coord_t dst_x, video_coord_t dst_y,
                                              video_dim_t dst_size_x, video_dim_t dst_size_y,
                                              video_coord_t src_x, video_coord_t src_y,
                                              video_dim_t src_size_x, video_dim_t src_size_y) {
	/* TODO */
	libvideo_swblitter_generic__stretch_l(self,
	                                      dst_x, dst_y, dst_size_x, dst_size_y,
	                                      src_x, src_y, src_size_x, src_size_y);
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__stretch_imatrix_l(struct video_blitter const *__restrict self,
                                                      video_coord_t dst_x, video_coord_t dst_y,
                                                      video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                      video_coord_t src_x, video_coord_t src_y,
                                                      video_dim_t src_size_x, video_dim_t src_size_y,
                                                      video_imatrix2d_t src_matrix) {
	/* TODO */
	libvideo_swblitter_generic__stretch_imatrix_l(self,
	                                              dst_x, dst_y, dst_size_x, dst_size_y,
	                                              src_x, src_y, src_size_x, src_size_y,
	                                              src_matrix);
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt_interp8888__stretch_l(struct video_blitter const *__restrict self,
                                                         video_coord_t dst_x, video_coord_t dst_y,
                                                         video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                         video_coord_t src_x, video_coord_t src_y,
                                                         video_dim_t src_size_x, video_dim_t src_size_y) {
	/* TODO */
	libvideo_swblitter_generic__stretch_l(self,
	                                      dst_x, dst_y, dst_size_x, dst_size_y,
	                                      src_x, src_y, src_size_x, src_size_y);
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt_interp8888__stretch_imatrix_l(struct video_blitter const *__restrict self,
                                                                 video_coord_t dst_x, video_coord_t dst_y,
                                                                 video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                                 video_coord_t src_x, video_coord_t src_y,
                                                                 video_dim_t src_size_x, video_dim_t src_size_y,
                                                                 video_imatrix2d_t src_matrix) {
	/* TODO */
	libvideo_swblitter_generic__stretch_imatrix_l(self,
	                                              dst_x, dst_y, dst_size_x, dst_size_y,
	                                              src_x, src_y, src_size_x, src_size_y,
	                                              src_matrix);
}











/************************************************************************/
/************************************************************************/
/************************************************************************/
/* SAME-BUF BLITTING                                                    */
/************************************************************************/
/************************************************************************/
/************************************************************************/

INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_samebuf__blit(struct video_blitter const *__restrict self,
                                         video_coord_t dst_x, video_coord_t dst_y,
                                         video_coord_t src_x, video_coord_t src_y,
                                         video_dim_t size_x, video_dim_t size_y) {
	struct video_regionlock lock;
	struct video_buffer *dst_buffer = self->vbt_dst->vx_buffer;
	video_coord_t lox = dst_x;
	video_coord_t loy = dst_y;
	video_dim_t lox_size = size_x;
	video_dim_t loy_size = size_y;

	/* Figure out the rect union of dst+src, which
	 * is the region we have to acquire a lock to. */
	range_union_samesize(&lox, &lox_size, src_x);
	range_union_samesize(&loy, &loy_size, src_y);

	TRACE_START("noblend_samebuf__blit("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x, dst_y, src_x, src_y, size_x, size_y);
	if likely(LL_wlockregion(dst_buffer, &lock, lox, loy, lox_size, loy_size)) {
		byte_t *dst_line = lock.vrl_lock.vl_data + (dst_y - loy) * lock.vrl_lock.vl_stride;
		byte_t const *src_line = lock.vrl_lock.vl_data + (src_y - loy) * lock.vrl_lock.vl_stride;
		video_codec_rectmove_t vc_rectmove = dst_buffer->vb_format.vf_codec->vc_rectmove;
		(*vc_rectmove)(dst_line, lock.vrl_xbas + (dst_x - lox),
		               src_line, lock.vrl_xbas + (src_x - lox),
		               lock.vrl_lock.vl_stride, size_x, size_y);
		LL_unlockregion(dst_buffer, &lock);
	} else {
		/* Use pixel-based rendering */
		if (xy_before_or_equal(dst_x, dst_y, src_x, src_y)) {
			libvideo_swblitter_noblend_samefmt__blit__bypixel(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
		} else {
			libvideo_swblitter_noblend_samefmt__blit__bypixel__rev(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
		}
	}
	TRACE_END("noblend_samebuf__blit()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_samebuf__blit_imatrix(struct video_blitter const *__restrict self,
                                                 video_coord_t dst_x, video_coord_t dst_y,
                                                 video_coord_t src_x, video_coord_t src_y,
                                                 video_dim_t size_x, video_dim_t size_y,
                                                 video_imatrix2d_t src_matrix) {
	/* TODO */
	libvideo_swblitter_samebuf__blit_imatrix(self, dst_x, dst_y, src_x, src_y,
	                                         size_x, size_y, src_matrix);
}











/************************************************************************/
/************************************************************************/
/************************************************************************/
/* DIFF-FMT BLITTING                                                    */
/************************************************************************/
/************************************************************************/
/************************************************************************/

#define BLIT_PIXEL(px_dst_x, px_dst_y, px_src_x, px_src_y) \
	{                                                      \
		video_pixel_t pixel;                               \
		pixel = LL_getpixel(src, px_src_x, px_src_y);      \
		pixel = video_converter_mappixel(conv, pixel);     \
		LL_setpixel(dst, px_dst_x, px_dst_y, pixel);       \
	}
PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt__blit__bypixel(struct video_blitter const *__restrict self,
                                                  video_coord_t dst_x, video_coord_t dst_y,
                                                  video_coord_t src_x, video_coord_t src_y,
                                                  video_dim_t size_x, video_dim_t size_y) {
	struct video_gfx const *src  = self->vbt_src;
	struct video_gfx const *dst  = self->vbt_dst;
	struct video_converter const *conv = libvideo_swblitter_generic__cconv(self);
	GFX_BLIT_FOREACH(dst_x, dst_y, src_x, src_y, size_x, size_y,
	                 BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt__blit_imatrix__bypixel(struct video_blitter const *__restrict self,
                                                          video_coord_t dst_x, video_coord_t dst_y,
                                                          video_coord_t src_x, video_coord_t src_y,
                                                          video_dim_t size_x, video_dim_t size_y,
                                                          video_imatrix2d_t src_matrix) {
	struct video_gfx const *src  = self->vbt_src;
	struct video_gfx const *dst  = self->vbt_dst;
	struct video_converter const *conv = libvideo_swblitter_generic__cconv(self);
	GFX_BLIT_FOREACH_IMATRIX(dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix,
	                         BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt__stretch_n__bypixel(struct video_blitter const *__restrict self,
                                                       video_coord_t dst_x_, video_coord_t dst_y_,
                                                       video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                                       video_coord_t src_x_, video_coord_t src_y_,
                                                       video_dim_t src_size_x_, video_dim_t src_size_y_) {
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
	struct video_converter const *conv = libvideo_swblitter_generic__cconv(self);
	GFX_NEAREST_STRETCH(dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                    src_x_, src_y_, src_size_x_, src_size_y_,
	                    BLIT_PIXEL, GFX_ROW_NOOP, GFX_ROW_NOOP);
}
#undef BLIT_PIXEL


INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt__blit(struct video_blitter const *__restrict self,
                                         video_coord_t dst_x, video_coord_t dst_y,
                                         video_coord_t src_x, video_coord_t src_y,
                                         video_dim_t size_x, video_dim_t size_y) {
	struct video_regionlock dst_lock;
	struct video_buffer *dst_buffer = self->vbt_dst->vx_buffer;
	TRACE_START("noblend_difffmt__blit("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x, dst_y, src_x, src_y, size_x, size_y);

	if likely(LL_wlockregion(dst_buffer, &dst_lock, dst_x, dst_y, size_x, size_y)) {
		struct video_regionlock src_lock;
		struct video_buffer *src_buffer = self->vbt_src->vx_buffer;
		if likely(LL_rlockregion(src_buffer, &src_lock, src_x, src_y, size_x, size_y)) {
			struct video_converter const *conv = libvideo_swblitter_generic__cconv(self);
			byte_t *dst_line = dst_lock.vrl_lock.vl_data;
			byte_t const *src_line = src_lock.vrl_lock.vl_data;

			/* Fast-pass for well-known BPPs */
#ifndef __OPTIMIZE_SIZE__
#define getpixel1(p)    (*(uint8_t const *)p)
#define getpixel2(p)    (*(uint16_t const *)p)
#define getpixel3(p)    ENCODE_INT32(p[0], p[1], p[2], 0)
#define getpixel4(p)    (*(uint32_t const *)p)
#define setpixel1(p, v) (*(uint8_t *)p = v)
#define setpixel2(p, v) (*(uint16_t *)p = v)
#define setpixel3(p, v) (p[0] = INT32_I8(v, 0), p[1] = INT32_I8(v, 1), p[2] = INT32_I8(v, 2))
#define setpixel4(p, v) (*(uint32_t *)p = v)
#define BLIT_DIFFFMT_FAST(DSTsz, SRCsz)                                \
			{                                                          \
				dst_line += DSTsz * dst_lock.vrl_xbas;                 \
				src_line += SRCsz * src_lock.vrl_xbas;                 \
				do {                                                   \
					video_dim_t iter_size_x = size_x;                  \
					byte_t *dst_iter = dst_line;                       \
					byte_t const *src_iter = src_line;                 \
					do {                                               \
						video_pixel_t pixel;                           \
						pixel = getpixel##SRCsz(src_iter);             \
						pixel = video_converter_mappixel(conv, pixel); \
						setpixel##DSTsz(dst_iter, pixel);              \
						dst_iter += DSTsz;                             \
						src_iter += SRCsz;                             \
					} while (--iter_size_x);                           \
					dst_line += dst_lock.vrl_lock.vl_stride;           \
					src_line += src_lock.vrl_lock.vl_stride;           \
				} while (--size_y);                                    \
				goto done_unlock_buffers;                              \
			}
			GFX_BLIT_SELECT_BPP_COMBINATION(dst_buffer->vb_format.vf_codec->vc_specs.vcs_bpp,
			                                src_buffer->vb_format.vf_codec->vc_specs.vcs_bpp,
			                                BLIT_DIFFFMT_FAST);
#undef BLIT_DIFFFMT_FAST
#undef getpixel8
#undef getpixel16
#undef getpixel24
#undef getpixel32
#undef setpixel8
#undef setpixel16
#undef setpixel24
#undef setpixel32
#endif /* !__OPTIMIZE_SIZE__ */

			/* Fallback: use general-purpose operators to convert pixels */
			{
				video_codec_getpixel_t vc_getpixel = src_buffer->vb_format.vf_codec->vc_getpixel;
				video_codec_setpixel_t vc_setpixel = dst_buffer->vb_format.vf_codec->vc_setpixel;
				do {
					video_coord_t used_dst_x = dst_lock.vrl_xbas;
					video_coord_t used_src_x = src_lock.vrl_xbas;
					video_dim_t iter_size_x = size_x;
					do {
						video_pixel_t o = (*vc_getpixel)(src_line, used_src_x);
						video_pixel_t n = video_converter_mappixel(conv, o);
						(*vc_setpixel)(dst_line, used_dst_x, n);
						++used_dst_x;
						++used_src_x;
					} while (--iter_size_x);
					src_line += src_lock.vrl_lock.vl_stride;
					dst_line += dst_lock.vrl_lock.vl_stride;
				} while (--size_y);
			}

#ifndef __OPTIMIZE_SIZE__
done_unlock_buffers:
#endif /* !__OPTIMIZE_SIZE__ */
			LL_unlockregion(src_buffer, &src_lock);
			LL_unlockregion(dst_buffer, &dst_lock);
			goto done;
		}
		LL_unlockregion(dst_buffer, &dst_lock);
	}

	/* Blit per-pixel, with pixel format converter */
	libvideo_swblitter_noblend_difffmt__blit__bypixel(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
done:
	TRACE_END("noblend_difffmt__blit()\n");
}


INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt__blit_imatrix(struct video_blitter const *__restrict self,
                                                 video_coord_t dst_x, video_coord_t dst_y,
                                                 video_coord_t src_x, video_coord_t src_y,
                                                 video_dim_t size_x, video_dim_t size_y,
                                                 video_imatrix2d_t src_matrix) {
	gfx_assert_imatrix2d(&src_matrix);

	/* Fast-pass for known matrices */
	if (src_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1)) {
		libvideo_swblitter_noblend_difffmt__blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
		return;
	}

	/* TODO: More optimizations for known rotation/mirror matrices */

	TRACE_START("noblend_difffmt__blit_imatrix("
	            "dst: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD "}, "
	            "dim: {%" PRIuDIM "x%" PRIuDIM "}, "
	            "matrix: {{%d,%d},{%d,%d}})\n",
	            dst_x, dst_y, src_x, src_y, size_x, size_y,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1));

	/* TODO: Use video locks if possible */

	/* Blit per-pixel, with pixel format converter */
	libvideo_swblitter_noblend_difffmt__blit_imatrix__bypixel(self, dst_x, dst_y, src_x, src_y,
	                                                          size_x, size_y, src_matrix);
	TRACE_END("noblend_difffmt__blit_imatrix()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt__stretch_n(struct video_blitter const *__restrict self,
                                              video_coord_t dst_x_, video_coord_t dst_y_,
                                              video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                              video_coord_t src_x_, video_coord_t src_y_,
                                              video_dim_t src_size_x_, video_dim_t src_size_y_) {
	struct video_regionlock dst_lock;
	struct video_buffer *dst_buffer = self->vbt_dst->vx_buffer;
	TRACE_START("swblitter_noblend_difffmt__stretch_n("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	            src_x_, src_y_, src_size_x_, src_size_y_);
	if likely(LL_wlockregion(dst_buffer, &dst_lock, dst_x_, dst_y_, dst_size_x_, dst_size_y_)) {
		struct video_regionlock src_lock;
		struct video_buffer *src_buffer = self->vbt_src->vx_buffer;
		if likely(LL_rlockregion(src_buffer, &src_lock, src_x_, src_y_, src_size_x_, src_size_y_)) {
			struct video_converter const *conv = libvideo_swblitter_generic__cconv(self);
			byte_t *dst_line = dst_lock.vrl_lock.vl_data;
			video_codec_getpixel_t vc_getpixel = src_buffer->vb_format.vf_codec->vc_getpixel;
			video_codec_setpixel_t vc_setpixel = dst_buffer->vb_format.vf_codec->vc_setpixel;
#define LOCAL_dst_startrow(dst_y, src_y) \
			byte_t const *src_line = src_lock.vrl_lock.vl_data + src_y * src_lock.vrl_lock.vl_stride
#define LOCAL_copy_pixel(dst_x, dst_y, src_x, src_y)                 \
			{                                                        \
				video_pixel_t s = (*vc_getpixel)(src_line, src_x);   \
				video_pixel_t o = video_converter_mappixel(conv, s); \
				(*vc_setpixel)(dst_line, dst_x, o);                  \
			}
#define LOCAL_dst_endrow(dst_y, src_y) \
			dst_line += dst_lock.vrl_lock.vl_stride; (void)dst_y
			GFX_NEAREST_STRETCH((video_coord_t)dst_lock.vrl_xbas, 0, dst_size_x_, dst_size_y_,
			                    (video_coord_t)src_lock.vrl_xbas, 0, src_size_x_, src_size_y_,
			                    LOCAL_copy_pixel, LOCAL_dst_startrow, LOCAL_dst_endrow);
#undef LOCAL_dst_endrow
#undef LOCAL_copy_pixel
#undef LOCAL_dst_startrow
			LL_unlockregion(src_buffer, &src_lock);
			LL_unlockregion(dst_buffer, &dst_lock);
			goto done;
		}
		LL_unlockregion(dst_buffer, &dst_lock);
	}
	libvideo_swblitter_noblend_difffmt__stretch_n__bypixel(self,
	                                                       dst_x_, dst_y_, dst_size_x_, dst_size_y_,
	                                                       src_x_, src_y_, src_size_x_, src_size_y_);
done:
	TRACE_END("swblitter_noblend_difffmt__stretch_n()\n");
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt__stretch_imatrix_n(struct video_blitter const *__restrict self,
                                                      video_coord_t dst_x, video_coord_t dst_y,
                                                      video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                      video_coord_t src_x, video_coord_t src_y,
                                                      video_dim_t src_size_x, video_dim_t src_size_y,
                                                      video_imatrix2d_t src_matrix) {
	/* TODO */
	libvideo_swblitter_generic__stretch_imatrix_n(self,
	                                              dst_x, dst_y, dst_size_x, dst_size_y,
	                                              src_x, src_y, src_size_x, src_size_y,
	                                              src_matrix);
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt__stretch_l(struct video_blitter const *__restrict self,
                                              video_coord_t dst_x, video_coord_t dst_y,
                                              video_dim_t dst_size_x, video_dim_t dst_size_y,
                                              video_coord_t src_x, video_coord_t src_y,
                                              video_dim_t src_size_x, video_dim_t src_size_y) {
	/* TODO */
	libvideo_swblitter_generic__stretch_l(self,
	                                      dst_x, dst_y, dst_size_x, dst_size_y,
	                                      src_x, src_y, src_size_x, src_size_y);
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt__stretch_imatrix_l(struct video_blitter const *__restrict self,
                                                      video_coord_t dst_x, video_coord_t dst_y,
                                                      video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                      video_coord_t src_x, video_coord_t src_y,
                                                      video_dim_t src_size_x, video_dim_t src_size_y,
                                                      video_imatrix2d_t src_matrix) {
	/* TODO */
	libvideo_swblitter_generic__stretch_imatrix_l(self,
	                                              dst_x, dst_y, dst_size_x, dst_size_y,
	                                              src_x, src_y, src_size_x, src_size_y,
	                                              src_matrix);
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt_interp8888__stretch_l__bypixel(struct video_blitter const *__restrict self,
                                                                  video_coord_t dst_x_, video_coord_t dst_y_,
                                                                  video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                                                  video_coord_t src_x_, video_coord_t src_y_,
                                                                  video_dim_t src_size_x_, video_dim_t src_size_y_) {
#define LOCAL_getpixel(x, y)                      \
	({                                            \
		video_coord_t used_src_x = src_x_ + x;    \
		video_coord_t used_src_y = src_y_ + y;    \
		LL_getpixel(src, used_src_x, used_src_y); \
	})
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
	struct video_converter const *conv = libvideo_swblitter_generic__cconv(self);
#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)                 \
	{                                                                                             \
		video_pixel_t pxl = LOCAL_getpixel(src_x, src_y);                                         \
		video_pixel_t out = video_converter_mappixel(conv, pxl);                                  \
		libvideo_swgfx_noblend__absfill__bypixel(dst, dst_x, dst_y, dst_size_x, dst_size_y, out); \
	}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                       \
		video_pixel_t src_y0_x0 = LOCAL_getpixel(src_x0, src_y);                            \
		video_pixel_t src_y0_x1 = LOCAL_getpixel(src_x1, src_y);                            \
		video_pixel_t pxl = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);         \
		video_pixel_t out = video_converter_mappixel(conv, pxl);                            \
		libvideo_swgfx_noblend__absline_v__bypixel(dst, dst_x, dst_y, dst_size_y, out);     \
	}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                       \
		video_pixel_t src_y0_x0 = LOCAL_getpixel(src_x, src_y0);                            \
		video_pixel_t src_y1_x0 = LOCAL_getpixel(src_x, src_y1);                            \
		video_pixel_t pxl = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);         \
		video_pixel_t out = video_converter_mappixel(conv, pxl);                            \
		libvideo_swgfx_noblend__absline_h__bypixel(dst, dst_x, dst_y, dst_size_x, out);     \
	}

#define pixel_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                 \
		video_pixel_t src_y0_x0 = LOCAL_getpixel(src_x0, src_y0);                                     \
		video_pixel_t src_y0_x1 = LOCAL_getpixel(src_x1, src_y0);                                     \
		video_pixel_t src_y1_x0 = LOCAL_getpixel(src_x0, src_y1);                                     \
		video_pixel_t src_y1_x1 = LOCAL_getpixel(src_x1, src_y1);                                     \
		video_pixel_t pxl = interpolate_2d(src_y0_x0, src_y0_x1,                                      \
		                                   src_y1_x0, src_y1_x1,                                      \
		                                   frac_x0, frac_x1,                                          \
		                                   frac_y0, frac_y1);                                         \
		video_pixel_t out = video_converter_mappixel(conv, pxl);                                      \
		LL_setpixel(dst, dst_x, dst_y, out);                                                          \
	}
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
#undef pixel_blend_xmin_ymin
#undef pixel_blend_ymin
#undef pixel_blend_xmax_ymin
#undef pixel_blend_xmin
#undef pixel_blend
#undef pixel_blend_xmax
#undef pixel_blend_xmin_ymax
#undef pixel_blend_ymax
#undef pixel_blend_xmax_ymax
#undef LOCAL_getpixel
}


INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt_interp8888__stretch_l(struct video_blitter const *__restrict self,
                                                         video_coord_t dst_x, video_coord_t dst_y,
                                                         video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                         video_coord_t src_x, video_coord_t src_y,
                                                         video_dim_t src_size_x, video_dim_t src_size_y) {
	TRACE_START("swblitter_noblend_difffmt_interp8888__stretch_l("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "})\n",
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            src_x, src_y, src_size_x, src_size_y);
	/* TODO: Use video locks if possible */
	libvideo_swblitter_noblend_difffmt_interp8888__stretch_l__bypixel(self,
	                                                                  dst_x, dst_y, dst_size_x, dst_size_y,
	                                                                  src_x, src_y, src_size_x, src_size_y);
	TRACE_END("swblitter_noblend_difffmt_interp8888__stretch_l()\n");
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt_interp8888__stretch_imatrix_l__bypixel(struct video_blitter const *__restrict self,
                                                                          video_coord_t dst_x_, video_coord_t dst_y_,
                                                                          video_dim_t dst_size_x_, video_dim_t dst_size_y_,
                                                                          video_coord_t src_x_, video_coord_t src_y_,
                                                                          video_dim_t src_size_x_, video_dim_t src_size_y_,
                                                                          video_imatrix2d_t src_matrix) {
#define LOCAL_getpixel(x, y)                                                             \
	({                                                                                   \
		video_coord_t used_src_x = src_x_ + video_imatrix2d_get(&src_matrix, 0, 0) * x + video_imatrix2d_get(&src_matrix, 0, 1) * y; \
		video_coord_t used_src_y = src_y_ + video_imatrix2d_get(&src_matrix, 1, 0) * x + video_imatrix2d_get(&src_matrix, 1, 1) * y; \
		LL_getpixel(src, used_src_x, used_src_y);                                        \
	})
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
	struct video_converter const *conv = libvideo_swblitter_generic__cconv(self);
	gfx_assert_imatrix2d(&src_matrix);
#define pixel_blend_xmax_ymin pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmax_ymax pixel_blend_xmin_ymin
#define pixel_blend_xmin_ymin(dst_x, dst_y, dst_size_x, dst_size_y, src_x, src_y)                 \
	{                                                                                             \
		video_pixel_t pxl = LOCAL_getpixel(src_x, src_y);                                         \
		video_pixel_t out = video_converter_mappixel(conv, pxl);                                  \
		libvideo_swgfx_noblend__absfill__bypixel(dst, dst_x, dst_y, dst_size_x, dst_size_y, out); \
	}

#define pixel_blend_ymax pixel_blend_ymin
#define pixel_blend_ymin(dst_x, dst_y, dst_size_y, src_x0, src_y, src_x1, frac_x0, frac_x1) \
	{                                                                                       \
		video_pixel_t src_y0_x0 = LOCAL_getpixel(src_x0, src_y);                            \
		video_pixel_t src_y0_x1 = LOCAL_getpixel(src_x1, src_y);                            \
		video_pixel_t pxl = interpolate_1d(src_y0_x0, src_y0_x1, frac_x0, frac_x1);         \
		video_pixel_t out = video_converter_mappixel(conv, pxl);                            \
		libvideo_swgfx_noblend__absline_v__bypixel(dst, dst_x, dst_y, dst_size_y, out);     \
	}

#define pixel_blend_xmax pixel_blend_xmin
#define pixel_blend_xmin(dst_x, dst_y, dst_size_x, src_x, src_y0, src_y1, frac_y0, frac_y1) \
	{                                                                                       \
		video_pixel_t src_y0_x0 = LOCAL_getpixel(src_x, src_y0);                            \
		video_pixel_t src_y1_x0 = LOCAL_getpixel(src_x, src_y1);                            \
		video_pixel_t pxl = interpolate_1d(src_y0_x0, src_y1_x0, frac_y0, frac_y1);         \
		video_pixel_t out = video_converter_mappixel(conv, pxl);                            \
		libvideo_swgfx_noblend__absline_h__bypixel(dst, dst_x, dst_y, dst_size_x, out);     \
	}

#define pixel_blend(dst_x, dst_y, src_x0, src_y0, src_x1, src_y1, frac_x0, frac_x1, frac_y0, frac_y1) \
	{                                                                                                 \
		video_pixel_t src_y0_x0 = LOCAL_getpixel(src_x0, src_y0);                                     \
		video_pixel_t src_y0_x1 = LOCAL_getpixel(src_x1, src_y0);                                     \
		video_pixel_t src_y1_x0 = LOCAL_getpixel(src_x0, src_y1);                                     \
		video_pixel_t src_y1_x1 = LOCAL_getpixel(src_x1, src_y1);                                     \
		video_pixel_t pxl = interpolate_2d(src_y0_x0, src_y0_x1,                                      \
		                                   src_y1_x0, src_y1_x1,                                      \
		                                   frac_x0, frac_x1,                                          \
		                                   frac_y0, frac_y1);                                         \
		video_pixel_t out = video_converter_mappixel(conv, pxl);                                      \
		LL_setpixel(dst, dst_x, dst_y, out);                                                          \
	}
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
#undef pixel_blend_xmin_ymin
#undef pixel_blend_ymin
#undef pixel_blend_xmax_ymin
#undef pixel_blend_xmin
#undef pixel_blend
#undef pixel_blend_xmax
#undef pixel_blend_xmin_ymax
#undef pixel_blend_ymax
#undef pixel_blend_xmax_ymax
#undef LOCAL_getpixel
}


INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt_interp8888__stretch_imatrix_l(struct video_blitter const *__restrict self,
                                                                 video_coord_t dst_x, video_coord_t dst_y,
                                                                 video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                                 video_coord_t src_x, video_coord_t src_y,
                                                                 video_dim_t src_size_x, video_dim_t src_size_y,
                                                                 video_imatrix2d_t src_matrix) {
	/* Fast-pass for known matrices */
	if (src_matrix == VIDEO_IMATRIX2D_INIT(1, 0, 0, 1)) {
		libvideo_swblitter_noblend_difffmt_interp8888__stretch_l(self,
		                                                         dst_x, dst_y, dst_size_x, dst_size_y,
		                                                         src_x, src_y, src_size_x, src_size_y);
		return;
	}


	TRACE_START("swblitter_noblend_difffmt_interp8888__stretch_imatrix_l("
	            "dst: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "src: {%" PRIuCRD "x%" PRIuCRD ", %" PRIuDIM "x%" PRIuDIM "}, "
	            "matrix: {{%d,%d},{%d,%d}})\n",
	            dst_x, dst_y, dst_size_x, dst_size_y,
	            src_x, src_y, src_size_x, src_size_y,
	            (int)video_imatrix2d_get(&src_matrix, 0, 0),
	            (int)video_imatrix2d_get(&src_matrix, 0, 1),
	            (int)video_imatrix2d_get(&src_matrix, 1, 0),
	            (int)video_imatrix2d_get(&src_matrix, 1, 1));
	/* TODO: Use video locks if possible */

	libvideo_swblitter_noblend_difffmt_interp8888__stretch_imatrix_l__bypixel(self,
	                                                                          dst_x, dst_y, dst_size_x, dst_size_y,
	                                                                          src_x, src_y, src_size_x, src_size_y,
	                                                                          src_matrix);
	TRACE_END("swblitter_noblend_difffmt_interp8888__stretch_imatrix_l()\n");
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_LL_NOBLEND_BLIT_C_INL */
