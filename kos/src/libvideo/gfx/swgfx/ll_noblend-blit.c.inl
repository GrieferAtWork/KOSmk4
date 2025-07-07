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
	GFX_BLIT_FOREACH(dst_x, dst_y, src_x, src_y, size_x, size_y, BLIT_PIXEL);
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__blit__bypixel__rev(struct video_blitter const *__restrict self,
                                                       video_coord_t dst_x, video_coord_t dst_y,
                                                       video_coord_t src_x, video_coord_t src_y,
                                                       video_dim_t size_x, video_dim_t size_y) {
	struct video_gfx const *src = self->vbt_src;
	struct video_gfx const *dst = self->vbt_dst;
	GFX_BLIT_FOREACH_REV(dst_x, dst_y, src_x, src_y, size_x, size_y, BLIT_PIXEL);
}

PRIVATE ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__blit_imatrix__bypixel(struct video_blitter const *__restrict self,
                                                          video_coord_t dst_x, video_coord_t dst_y,
                                                          video_coord_t src_x, video_coord_t src_y,
                                                          video_dim_t size_x, video_dim_t size_y,
                                                          video_imatrix2d_t src_matrix) {
	struct video_gfx const *src = self->vbt_src;
	struct video_gfx const *dst = self->vbt_dst;
	GFX_BLIT_FOREACH_IMATRIX(dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix, BLIT_PIXEL);
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
	GFX_BLIT_FOREACH(dst_x, dst_y, src_x, src_y, size_x, size_y, BLIT_PIXEL);
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
	GFX_BLIT_FOREACH_IMATRIX(dst_x, dst_y, src_x, src_y, size_x, size_y, src_matrix, BLIT_PIXEL);
}
#undef BLIT_PIXEL



static_assert(sizeof(struct video_converter) <= sizeof(((struct video_blitter *)0)->_vbt_driver),
              "This relation is required because `libvideo_swblitter_noblend_difffmt__*' require driver-"
              "specific data to be set-up as a pixel format converter");

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
						video_pixel_t pixel;
						pixel = (*vc_getpixel)(src_line, used_src_x);
						pixel = video_converter_mappixel(conv, pixel);
						(*vc_setpixel)(dst_line, used_dst_x, pixel);
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



INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
libvideo_swgfx_noblend__fillstretchmask_n(struct video_gfx const *__restrict self,
                                          video_coord_t dst_x, video_coord_t dst_y,
                                          video_dim_t dst_size_x, video_dim_t dst_size_y,
                                          video_color_t const bg_fg_colors[2],
                                          video_dim_t src_size_x, video_dim_t src_size_y,
                                          struct video_bitmask const *__restrict bm) {
	/* XXX: Fast-pass? */
	libvideo_swgfx_generic__fillstretchmask_n(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                          bg_fg_colors, src_size_x, src_size_y, bm);
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_samefmt__stretch_n(struct video_blitter const *__restrict self,
                                              video_coord_t dst_x, video_coord_t dst_y,
                                              video_dim_t dst_size_x, video_dim_t dst_size_y,
                                              video_coord_t src_x, video_coord_t src_y,
                                              video_dim_t src_size_x, video_dim_t src_size_y) {
	/* XXX: Fast-pass? */
	libvideo_swblitter_generic__stretch_n(self,
	                                      dst_x, dst_y, dst_size_x, dst_size_y,
	                                      src_x, src_y, src_size_x, src_size_y);
}

INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt__stretch_n(struct video_blitter const *__restrict self,
                                              video_coord_t dst_x, video_coord_t dst_y,
                                              video_dim_t dst_size_x, video_dim_t dst_size_y,
                                              video_coord_t src_x, video_coord_t src_y,
                                              video_dim_t src_size_x, video_dim_t src_size_y) {
	/* XXX: Fast-pass? */
	libvideo_swblitter_generic__stretch_n(self,
	                                      dst_x, dst_y, dst_size_x, dst_size_y,
	                                      src_x, src_y, src_size_x, src_size_y);
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
libvideo_swblitter_noblend_samebuf__blit_imatrix(struct video_blitter const *__restrict self,
                                                 video_coord_t dst_x, video_coord_t dst_y,
                                                 video_coord_t src_x, video_coord_t src_y,
                                                 video_dim_t size_x, video_dim_t size_y,
                                                 video_imatrix2d_t src_matrix) {
	/* TODO */
	libvideo_swblitter_samebuf__blit_imatrix(self, dst_x, dst_y, src_x, src_y,
	                                         size_x, size_y, src_matrix);
}


INTERN ATTR_IN(1) void CC
libvideo_swblitter_noblend_difffmt__stretch_imatrix_n(struct video_blitter const *__restrict self,
                                                      video_coord_t dst_x, video_coord_t dst_y,
                                                      video_dim_t dst_size_x, video_dim_t dst_size_y,
                                                      video_coord_t src_x, video_coord_t src_y,
                                                      video_dim_t src_size_x, video_dim_t src_size_y,
                                                      video_imatrix2d_t src_matrix) {
	/* XXX: Fast-pass? */
	libvideo_swblitter_generic__stretch_imatrix_n(self,
	                                              dst_x, dst_y, dst_size_x, dst_size_y,
	                                              src_x, src_y, src_size_x, src_size_y,
	                                              src_matrix);
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_SWGFX_LL_NOBLEND_BLIT_C_INL */
