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
#define _KOS_SOURCE 1

#ifdef __INTELLISENSE__
//#define         DEFINE_libvideo_swblitter_blit_wrap
//#define DEFINE_libvideo_swblitter_blit_wrap_imatrix
#define        DEFINE_libvideo_swblitter3_blit_wrap
//#define DEFINE_libvideo_swblitter3_blit_wrap_imatrix
#endif /* __INTELLISENSE__ */

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <stddef.h>
#include <stdint.h>

#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>
/**/

#include "../gfx-utils.h"
#include "../swgfx.h"

#if (defined(DEFINE_libvideo_swblitter_blit_wrap) +         \
     defined(DEFINE_libvideo_swblitter_blit_wrap_imatrix) + \
     defined(DEFINE_libvideo_swblitter3_blit_wrap) +        \
     defined(DEFINE_libvideo_swblitter3_blit_wrap_imatrix)) != 1
#error "Must #define exactly one of these"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_libvideo_swblitter_blit_wrap_imatrix
#define LOCAL_USE_IMATRIX
#elif defined(DEFINE_libvideo_swblitter3_blit_wrap)
#define LOCAL_USE_SWBLITTER3
#elif defined(DEFINE_libvideo_swblitter3_blit_wrap_imatrix)
#define LOCAL_USE_SWBLITTER3
#define LOCAL_USE_IMATRIX
#endif /* DEFINE_libvideo_swblitter_blit_wrap_imatrix */


#ifdef LOCAL_USE_IMATRIX
#define LOCAL_FUNC(x) x##_imatrix
#else /* LOCAL_USE_IMATRIX */
#define LOCAL_FUNC(x) x
#endif /* !LOCAL_USE_IMATRIX */

#ifdef LOCAL_USE_SWBLITTER3
#define LOCAL_struct_video_blitter               struct video_blitter3
#define LOCAL_libvideo_swblitter_blit            LOCAL_FUNC(libvideo_swblitter3_blit)
#define LOCAL_libvideo_swblitter_blit_rdwrap     LOCAL_FUNC(libvideo_swblitter3_blit_rdwrap)
#define LOCAL_libvideo_swblitter_blit_wrap       LOCAL_FUNC(libvideo_swblitter3_blit_wrap)
#define LOCAL_libvideo_swblitter_blit_rdwrap1    LOCAL_FUNC(libvideo_swblitter3_blit_rdwrap1)
#define LOCAL_libvideo_swblitter_blit_wrap1      LOCAL_FUNC(libvideo_swblitter3_blit_wrap1)
#define LOCAL_libvideo_swblitter_stretch         LOCAL_FUNC(libvideo_swblitter3_stretch)
#define LOCAL_libvideo_swblitter_stretch_rdwrap  LOCAL_FUNC(libvideo_swblitter3_stretch_rdwrap)
#define LOCAL_libvideo_swblitter_stretch_wrap    LOCAL_FUNC(libvideo_swblitter3_stretch_wrap)
#define LOCAL_libvideo_swblitter_stretch_rdwrap1 LOCAL_FUNC(libvideo_swblitter3_stretch_rdwrap1)
#define LOCAL_libvideo_swblitter_stretch_wrap1   LOCAL_FUNC(libvideo_swblitter3_stretch_wrap1)
#else /* LOCAL_USE_SWBLITTER3 */
#define LOCAL_struct_video_blitter              struct video_blitter
#define LOCAL_libvideo_swblitter_blit           LOCAL_FUNC(libvideo_swblitter_blit)
#define LOCAL_libvideo_swblitter_blit_rdwrap    LOCAL_FUNC(libvideo_swblitter_blit_rdwrap)
#define LOCAL_libvideo_swblitter_blit_wrap      LOCAL_FUNC(libvideo_swblitter_blit_wrap)
#define LOCAL_libvideo_swblitter_stretch        LOCAL_FUNC(libvideo_swblitter_stretch)
#define LOCAL_libvideo_swblitter_stretch_rdwrap LOCAL_FUNC(libvideo_swblitter_stretch_rdwrap)
#define LOCAL_libvideo_swblitter_stretch_wrap   LOCAL_FUNC(libvideo_swblitter_stretch_wrap)
#endif /* !LOCAL_USE_SWBLITTER3 */



INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter_blit_rdwrap(LOCAL_struct_video_blitter const *__restrict self,
#ifdef LOCAL_USE_SWBLITTER3
                                     video_offset_t out_x, video_offset_t out_y,
#endif /* LOCAL_USE_SWBLITTER3 */
                                     video_offset_t dst_x, video_offset_t dst_y,
                                     video_offset_t src_x, video_offset_t src_y,
                                     video_dim_t size_x, video_dim_t size_y) {
	/* Handle the case where "src" has read-wrapping enabled. */
#ifdef LOCAL_USE_SWBLITTER3
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
#else /* LOCAL_USE_SWBLITTER3 */
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
#endif /* !LOCAL_USE_SWBLITTER3 */
	video_dim_t src_maxsx = size_x; /* # of pixes after src_x before wrap */
	video_dim_t src_maxsy = size_y; /* # of pixes after src_y before wrap */

	if (src->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_dim_t dst_endx;
		/* Do some preliminary clamping on destination coords.
		 * This is needed so  we can properly calculate  tiled
		 * repeated when wrapping is enabled in "src". */
		if unlikely(dst_x < 0) {
			video_dim_t delta = (video_dim_t)-dst_x;
			if (OVERFLOW_USUB(size_x, delta, &size_x))
				return;
#ifdef LOCAL_USE_SWBLITTER3
			out_x += delta;
#endif /* LOCAL_USE_SWBLITTER3 */
			dst_x = 0;
			src_x += delta;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, size_x, &dst_endx) ||
		            dst_endx > dst->vx_hdr.vxh_cxsiz) {
			if unlikely((video_coord_t)dst_x >= dst->vx_hdr.vxh_cxsiz)
				return;
			size_x = dst->vx_hdr.vxh_cxsiz - (video_coord_t)dst_x;
		}
#ifdef LOCAL_USE_SWBLITTER3
		if unlikely(out_x < 0) {
			video_dim_t delta = (video_dim_t)-out_x;
			if (OVERFLOW_USUB(size_x, delta, &size_x))
				return;
			dst_x += delta;
			out_x = 0;
			src_x += delta;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)out_x, size_x, &dst_endx) ||
		            dst_endx > out->vx_hdr.vxh_cxsiz) {
			if unlikely((video_coord_t)out_x >= out->vx_hdr.vxh_cxsiz)
				return;
			size_x = out->vx_hdr.vxh_cxsiz - (video_coord_t)out_x;
		}
#endif /* LOCAL_USE_SWBLITTER3 */
		src_x     = wrap(src_x, src->vx_hdr.vxh_cxsiz);
		src_maxsx = src->vx_hdr.vxh_cxsiz - (video_coord_t)src_x;
	}

	if (src->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_dim_t dst_endy;
		/* Do some preliminary clamping on destination coords.
		 * This is needed so  we can properly calculate  tiled
		 * repeated when wrapping is enabled in "src". */
		if unlikely(dst_y < 0) {
			video_dim_t delta = (video_dim_t)-dst_y;
			if (OVERFLOW_USUB(size_y, delta, &size_y))
				return;
#ifdef LOCAL_USE_SWBLITTER3
			out_y += delta;
#endif /* LOCAL_USE_SWBLITTER3 */
			dst_y = 0;
			src_y += delta;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, size_y, &dst_endy) ||
		            dst_endy > dst->vx_hdr.vxh_cysiz) {
			if unlikely((video_coord_t)dst_y >= dst->vx_hdr.vxh_cysiz)
				return;
			size_y = dst->vx_hdr.vxh_cysiz - (video_coord_t)dst_y;
		}
#ifdef LOCAL_USE_SWBLITTER3
		if unlikely(out_y < 0) {
			video_dim_t delta = (video_dim_t)-out_y;
			if (OVERFLOW_USUB(size_y, delta, &size_y))
				return;
			dst_y += delta;
			out_y = 0;
			src_y += delta;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)out_y, size_y, &dst_endy) ||
		            dst_endy > out->vx_hdr.vxh_cysiz) {
			if unlikely((video_coord_t)out_y >= out->vx_hdr.vxh_cysiz)
				return;
			size_y = out->vx_hdr.vxh_cysiz - (video_coord_t)out_y;
		}
#endif /* LOCAL_USE_SWBLITTER3 */
		src_y     = wrap(src_y, src->vx_hdr.vxh_cysiz);
		src_maxsy = src->vx_hdr.vxh_cysiz - (video_coord_t)src_y;
	}

#ifdef LOCAL_USE_SWBLITTER3
#define LOCAL_blit(dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_)                        \
	LOCAL_libvideo_swblitter_blit(self, out_x + (dst_x_ - dst_x), out_y + (dst_y_ - dst_y), \
	                              dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_)
#define LOCAL_blit2dst(src_x_, src_y_, size_x_, size_y_) \
	LOCAL_libvideo_swblitter_blit(self, out_x, out_y, dst_x, dst_y, src_x_, src_y_, size_x_, size_y_)
#define LOCAL_dst_x_add(v) (dst_x += v, out_x += v)
#define LOCAL_dst_y_add(v) (dst_y += v, out_y += v)
#else /* LOCAL_USE_SWBLITTER3 */
#define LOCAL_blit(dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_) \
	LOCAL_libvideo_swblitter_blit(self, dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_)
#define LOCAL_blit2dst(src_x_, src_y_, size_x_, size_y_) \
	LOCAL_libvideo_swblitter_blit(self, dst_x, dst_y, src_x_, src_y_, size_x_, size_y_)
#define LOCAL_dst_x_add(v) dst_x += v
#define LOCAL_dst_y_add(v) dst_y += v
#endif /* !LOCAL_USE_SWBLITTER3 */
	if ((size_x > src_maxsx) && (size_y > src_maxsy)) {
		video_dim_t iter_size_x;
		video_dim_t iter_size_y;
		video_dim_t iter_dst_x;
		video_dim_t iter_dst_y;
		/* Must render the source graphic multiple times */

#ifndef LOCAL_USE_SWBLITTER3
		/* When  any pixel of "src" is read more than once, and "src" and "dst"
		 * have different pixel formats, then try to convert the accessed pixel
		 * area of "src" into the pixel format of "dst" to cut down on the # of
		 * necessary color format conversions.
		 *
		 * NOTE: Don't convert the entire "src" buffer; only the rect that will
		 *       be accessed below needs to be copied! */
		if ((size_x > src->vx_hdr.vxh_cxsiz || size_y > src->vx_hdr.vxh_cysiz) &&
		    (src->vx_buffer->vb_format.vf_codec != dst->vx_buffer->vb_format.vf_codec ||
		     src->vx_buffer->vb_format.vf_pal != dst->vx_buffer->vb_format.vf_pal)) {
			/* TODO */
		}
#endif /* !LOCAL_USE_SWBLITTER3 */

		iter_size_y = size_y;
		iter_dst_y  = dst_y;

		/* Deal with unaligned tiles near the top */
		if unlikely(src_maxsy < src->vx_hdr.vxh_cysiz) {
			/* Top-left corner */
			LOCAL_blit2dst(src_x, src_y, src_maxsx, src_maxsy);

			/* Top bar */
			iter_size_x = size_x - src_maxsx;
			iter_dst_x = dst_x + src_maxsx;
			while (iter_size_x > src->vx_hdr.vxh_cxsiz) {
				LOCAL_blit(iter_dst_x, iter_dst_y, 0, src_y, src->vx_hdr.vxh_cxsiz, src_maxsy);
				iter_size_x -= src->vx_hdr.vxh_cxsiz;
				iter_dst_x += src->vx_hdr.vxh_cxsiz;
			}

			/* Top-right corner */
			LOCAL_blit(iter_dst_x, iter_dst_y, 0, src_y, iter_size_x, src_maxsy);
			iter_size_y -= src_maxsy;
			iter_dst_y += src_maxsy;
		}

		/* Iterate whole rows */
		while (iter_size_y >= src->vx_hdr.vxh_cysiz) {
			/* Left side */
			LOCAL_blit(dst_x, iter_dst_y, src_x, 0, src_maxsx, src->vx_hdr.vxh_cysiz);

			/* Center */
			iter_size_x = size_x - src_maxsx;
			iter_dst_x = dst_x + src_maxsx;
			while (iter_size_x > src->vx_hdr.vxh_cxsiz) {
				LOCAL_blit(iter_dst_x, iter_dst_y, 0, 0, src->vx_hdr.vxh_cxsiz, src->vx_hdr.vxh_cysiz);
				iter_size_x -= src->vx_hdr.vxh_cxsiz;
				iter_dst_x += src->vx_hdr.vxh_cxsiz;
			}

			/* Right side */
			LOCAL_blit(iter_dst_x, iter_dst_y, 0, 0, iter_size_x, src->vx_hdr.vxh_cysiz);

			iter_size_y -= src->vx_hdr.vxh_cysiz;
			iter_dst_y += src->vx_hdr.vxh_cysiz;
		}

		if likely(!iter_size_y)
			return;

		/* Bottom-left corner */
		LOCAL_blit(dst_x, iter_dst_y, src_x, 0, src_maxsx, iter_size_y);

		/* Bottom bar */
		iter_size_x = size_x - src_maxsx;
		iter_dst_x = dst_x + src_maxsx;
		while (iter_size_x > src->vx_hdr.vxh_cxsiz) {
			LOCAL_blit(iter_dst_x, iter_dst_y, 0, 0, src->vx_hdr.vxh_cxsiz, iter_size_y);
			iter_size_x -= src->vx_hdr.vxh_cxsiz;
			iter_dst_x += src->vx_hdr.vxh_cxsiz;
		}

		/* Bottom-right corner (render via fallthru) */
#ifdef LOCAL_USE_SWBLITTER3
		out_x += (iter_dst_x - dst_x);
		out_y += (iter_dst_y - dst_y);
#endif /* LOCAL_USE_SWBLITTER3 */
		dst_x  = iter_dst_x;
		dst_y  = iter_dst_y;
		src_x  = 0;
		src_y  = 0;
		size_x = iter_size_x;
		size_y = iter_size_y;
	} else if (size_x > src_maxsx) {
		LOCAL_blit2dst(src_x, src_y, src_maxsx, size_y);
		size_x -= src_maxsx;
		LOCAL_dst_x_add(src_maxsx);
		while (size_x > src->vx_hdr.vxh_cxsiz) {
			LOCAL_blit2dst(0, src_y, src->vx_hdr.vxh_cxsiz, size_y);
			size_x -= src->vx_hdr.vxh_cxsiz;
			LOCAL_dst_x_add(src->vx_hdr.vxh_cxsiz);
		}
		src_x = 0; /* Fallthru to render the last part */
	} else if (size_y > src_maxsy) {
		LOCAL_blit2dst(src_x, src_y, size_x, src_maxsy);
		size_y -= src_maxsy;
		LOCAL_dst_y_add(src_maxsy);
		while (size_y > src->vx_hdr.vxh_cysiz) {
			LOCAL_blit2dst(src_x, 0, size_x, src->vx_hdr.vxh_cysiz);
			size_y -= src->vx_hdr.vxh_cysiz;
			LOCAL_dst_y_add(src->vx_hdr.vxh_cysiz);
		}
		src_y = 0; /* Fallthru to render the last part */
	}

	LOCAL_blit2dst(src_x, src_y, size_x, size_y);
#undef LOCAL_blit
#undef LOCAL_blit2dst
#undef LOCAL_dst_x_add
#undef LOCAL_dst_y_add
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter_stretch_rdwrap(LOCAL_struct_video_blitter const *__restrict self,
#ifdef LOCAL_USE_SWBLITTER3
                                        video_offset_t out_x, video_offset_t out_y,
#endif /* LOCAL_USE_SWBLITTER3 */
                                        video_offset_t dst_x, video_offset_t dst_y,
                                        video_dim_t dst_size_x, video_dim_t dst_size_y,
                                        video_offset_t src_x, video_offset_t src_y,
                                        video_dim_t src_size_x, video_dim_t src_size_y) {
	/* Handle the case where "src" has read-wrapping enabled. */
#define xdst2src(x) ((video_coord_t)(((uint64_t)(x) * src_size_x) / dst_size_x))
#define ydst2src(y) ((video_coord_t)(((uint64_t)(y) * src_size_y) / dst_size_y))
#define xsrc2dst(x) ((video_coord_t)(((uint64_t)(x) * dst_size_x) / src_size_x))
#define ysrc2dst(y) ((video_coord_t)(((uint64_t)(y) * dst_size_y) / src_size_y))
#ifdef LOCAL_USE_SWBLITTER3
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
#else /* LOCAL_USE_SWBLITTER3 */
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
#endif /* !LOCAL_USE_SWBLITTER3 */
	video_dim_t src_maxsx = src_size_x; /* # of pixes after src_x before wrap */
	video_dim_t src_maxsy = src_size_y; /* # of pixes after src_y before wrap */

	if (src->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_dim_t dst_endx;
		/* Do some preliminary clamping on destination coords.
		 * This is needed so  we can properly calculate  tiled
		 * repeated when wrapping is enabled in "src". */
		if unlikely(dst_x < 0) {
			video_dim_t delta = (video_dim_t)-dst_x;
			video_dim_t new_dst_size_x;
			if (OVERFLOW_USUB(dst_size_x, delta, &new_dst_size_x))
				return;
			src_size_x -= xdst2src(delta);
			src_x += xdst2src(delta);
			dst_size_x = new_dst_size_x;
#ifdef LOCAL_USE_SWBLITTER3
			out_x += delta;
#endif /* LOCAL_USE_SWBLITTER3 */
			dst_x = 0;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, dst_size_x, &dst_endx) ||
		            dst_endx > dst->vx_hdr.vxh_cxsiz) {
			video_dim_t new_dst_size_x;
			if unlikely((video_coord_t)dst_x >= dst->vx_hdr.vxh_cxsiz)
				return;
			new_dst_size_x = dst->vx_hdr.vxh_cxsiz - (video_coord_t)dst_x;
			src_size_x -= xdst2src(dst_size_x - new_dst_size_x);
			dst_size_x = new_dst_size_x;
		}
#ifdef LOCAL_USE_SWBLITTER3
		if unlikely(out_x < 0) {
			video_dim_t delta = (video_dim_t)-out_x;
			video_dim_t new_dst_size_x;
			if (OVERFLOW_USUB(dst_size_x, delta, &new_dst_size_x))
				return;
			src_size_x -= xdst2src(delta);
			src_x += xdst2src(delta);
			dst_size_x = new_dst_size_x;
			dst_x += delta;
			out_x = 0;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)out_x, dst_size_x, &dst_endx) ||
		            dst_endx > out->vx_hdr.vxh_cxsiz) {
			video_dim_t new_dst_size_x;
			if unlikely((video_coord_t)out_x >= out->vx_hdr.vxh_cxsiz)
				return;
			new_dst_size_x = out->vx_hdr.vxh_cxsiz - (video_coord_t)out_x;
			src_size_x -= xdst2src(dst_size_x - new_dst_size_x);
			dst_size_x = new_dst_size_x;
		}
#endif /* LOCAL_USE_SWBLITTER3 */
		src_x     = wrap(src_x, src->vx_hdr.vxh_cxsiz);
		src_maxsx = src->vx_hdr.vxh_cxsiz - (video_coord_t)src_x;
	}

	if (src->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_dim_t dst_endy;
		/* Do some preliminary clamping on destination coords.
		 * This is needed so  we can properly calculate  tiled
		 * repeated when wrapping is enabled in "src". */
		if unlikely(dst_y < 0) {
			video_dim_t delta = (video_dim_t)-dst_y;
			video_dim_t new_dst_size_y;
			if (OVERFLOW_USUB(dst_size_y, delta, &new_dst_size_y))
				return;
			src_size_y -= ydst2src(delta);
			src_y += ydst2src(delta);
			dst_size_y = new_dst_size_y;
#ifdef LOCAL_USE_SWBLITTER3
			out_y += delta;
#endif /* LOCAL_USE_SWBLITTER3 */
			dst_y = 0;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, dst_size_y, &dst_endy) ||
		            dst_endy > dst->vx_hdr.vxh_cysiz) {
			video_dim_t new_dst_size_y;
			if unlikely((video_coord_t)dst_y >= dst->vx_hdr.vxh_cysiz)
				return;
			new_dst_size_y = dst->vx_hdr.vxh_cysiz - (video_coord_t)dst_y;
			src_size_y -= ydst2src(dst_size_y - new_dst_size_y);
			dst_size_y = new_dst_size_y;
		}
#ifdef LOCAL_USE_SWBLITTER3
		if unlikely(out_y < 0) {
			video_dim_t delta = (video_dim_t)-out_y;
			video_dim_t new_dst_size_y;
			if (OVERFLOW_USUB(dst_size_y, delta, &new_dst_size_y))
				return;
			src_size_y -= ydst2src(delta);
			src_y += ydst2src(delta);
			dst_size_y = new_dst_size_y;
			dst_y += delta;
			out_y = 0;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)out_y, dst_size_y, &dst_endy) ||
		            dst_endy > out->vx_hdr.vxh_cysiz) {
			video_dim_t new_dst_size_y;
			if unlikely((video_coord_t)out_y >= out->vx_hdr.vxh_cysiz)
				return;
			new_dst_size_y = out->vx_hdr.vxh_cysiz - (video_coord_t)out_y;
			src_size_y -= ydst2src(dst_size_y - new_dst_size_y);
			dst_size_y = new_dst_size_y;
		}
#endif /* LOCAL_USE_SWBLITTER3 */
		src_y     = wrap(src_y, src->vx_hdr.vxh_cysiz);
		src_maxsy = src->vx_hdr.vxh_cysiz - (video_coord_t)src_y;
	}

#ifdef LOCAL_USE_SWBLITTER3
#define LOCAL_stretch(dst_x_, dst_y_, dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_) \
	LOCAL_libvideo_swblitter_stretch(self, out_x + (dst_x_ - dst_x), out_y + (dst_y_ - dst_y),            \
	                                 dst_x_, dst_y_, dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_)
#define LOCAL_stretch2dst(dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_) \
	LOCAL_libvideo_swblitter_stretch(self, out_x, out_y, dst_x, dst_y, dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_)
#define LOCAL_dst_x_add(v) (dst_x += v, out_x += v)
#define LOCAL_dst_y_add(v) (dst_y += v, out_y += v)
#else /* LOCAL_USE_SWBLITTER3 */
#define LOCAL_stretch(dst_x_, dst_y_, dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_) \
	LOCAL_libvideo_swblitter_stretch(self, dst_x_, dst_y_, dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_)
#define LOCAL_stretch2dst(dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_) \
	LOCAL_libvideo_swblitter_stretch(self, dst_x, dst_y, dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_)
#define LOCAL_dst_x_add(v) dst_x += v
#define LOCAL_dst_y_add(v) dst_y += v
#endif /* !LOCAL_USE_SWBLITTER3 */
	if ((src_size_x > src_maxsx) && (src_size_y > src_maxsy)) {
		video_dim_t firsttile_dst_size_x = xsrc2dst(src_maxsx);
		video_dim_t firsttile_dst_size_y = ysrc2dst(src_maxsy);
		video_coord_t iter_dst_x;
		video_coord_t iter_dst_size_x;
		video_coord_t iter_src_size_x;
		video_coord_t iter_dst_y;
		video_coord_t iter_dst_size_y;
		video_coord_t iter_src_size_y;
		video_dim_t xwholetiles_count = 0;
		video_dim_t lasttile_dst_size_x = 0;
		video_dim_t wholetiles_dst_size_x = 0;

#ifndef LOCAL_USE_SWBLITTER3
		/* When  any pixel of "src" is read more than once, and "src" and "dst"
		 * have different pixel formats, then try to convert the accessed pixel
		 * area of "src" into the pixel format of "dst" to cut down on the # of
		 * necessary color format conversions.
		 *
		 * NOTE: Don't convert the entire "src" buffer; only the rect that will
		 *       be accessed below needs to be copied! */
		if ((src_size_x > src->vx_hdr.vxh_cxsiz || src_size_y > src->vx_hdr.vxh_cysiz) &&
		    (src->vx_buffer->vb_format.vf_codec != dst->vx_buffer->vb_format.vf_codec ||
		     src->vx_buffer->vb_format.vf_pal != dst->vx_buffer->vb_format.vf_pal)) {
			/* TODO */
		}
#endif /* !LOCAL_USE_SWBLITTER3 */

		/* Deal with unaligned tiles near the top */

		/* Top-left corner */
		LOCAL_stretch2dst(firsttile_dst_size_x, firsttile_dst_size_y,
		                  src_x, src_y, src_maxsx, src_maxsy);

		/* Top bar */
		iter_src_size_x = src_size_x - src_maxsx;
		iter_dst_x      = dst_x + firsttile_dst_size_x;
		iter_dst_size_x = dst_size_x - firsttile_dst_size_x;
		if (iter_src_size_x > src->vx_hdr.vxh_cxsiz) {
			video_coord_t base_dst_x;
			video_coord_t xwholetiles_i;
			xwholetiles_count = iter_src_size_x / src->vx_hdr.vxh_cxsiz;
			lasttile_dst_size_x = xsrc2dst(iter_src_size_x % src->vx_hdr.vxh_cxsiz);
			wholetiles_dst_size_x = iter_dst_size_x - lasttile_dst_size_x;
			base_dst_x = iter_dst_x;
			for (xwholetiles_i = 0; xwholetiles_i < xwholetiles_count; ++xwholetiles_i) {
				video_coord_t next_dst_x;
				next_dst_x = base_dst_x + (wholetiles_dst_size_x * (xwholetiles_i + 1)) / xwholetiles_count;
				LOCAL_stretch(iter_dst_x, dst_y, next_dst_x - iter_dst_x, firsttile_dst_size_y,
				              0, src_y, src->vx_hdr.vxh_cxsiz, src_maxsy);
				iter_dst_x = next_dst_x;
			}
			iter_src_size_x %= src->vx_hdr.vxh_cxsiz;
			iter_dst_size_x = lasttile_dst_size_x;
		}

		/* Top-right corner */
		LOCAL_stretch(iter_dst_x, dst_y, iter_dst_size_x, firsttile_dst_size_y,
		              0, src_y, iter_src_size_x, src_maxsy);

		/* Iterate whole rows */
		iter_src_size_y = src_size_y - src_maxsy;
		iter_dst_y      = dst_y + firsttile_dst_size_y;
		iter_dst_size_y = dst_size_y - firsttile_dst_size_y;
		if likely(iter_src_size_y >= src->vx_hdr.vxh_cysiz) {
			video_coord_t ywholetiles_i;
			video_dim_t ywholetiles_count = iter_src_size_y / src->vx_hdr.vxh_cysiz;
			video_dim_t lasttile_dst_size_y = ysrc2dst(iter_src_size_y % src->vx_hdr.vxh_cysiz);
			video_dim_t wholetiles_dst_size_y = iter_dst_size_y - lasttile_dst_size_y;
			video_coord_t base_dst_y = iter_dst_y;
			for (ywholetiles_i = 0; ywholetiles_i < ywholetiles_count; ++ywholetiles_i) {
				video_coord_t next_dst_y;
				video_dim_t tile_h;
				next_dst_y = base_dst_y + (wholetiles_dst_size_y * (ywholetiles_i + 1)) / ywholetiles_count;
				tile_h = next_dst_y - iter_dst_y;

				/* Left side */
				LOCAL_stretch(dst_x, iter_dst_y, firsttile_dst_size_x, tile_h,
				              src_x, 0, src_maxsx, src->vx_hdr.vxh_cysiz);

				/* Center (whole tiles) */
				iter_src_size_x = src_size_x - src_maxsx;
				iter_dst_x      = dst_x + firsttile_dst_size_x;
				iter_dst_size_x = dst_size_x - firsttile_dst_size_x;
				if (xwholetiles_count) {
					video_coord_t base_dst_x = iter_dst_x;
					video_coord_t xwholetiles_i = 0;
					do {
						video_coord_t next_dst_x;
						next_dst_x = base_dst_x + (wholetiles_dst_size_x * (xwholetiles_i + 1)) / xwholetiles_count;
						LOCAL_stretch(iter_dst_x, iter_dst_y, next_dst_x - iter_dst_x, tile_h,
						              0, 0, src->vx_hdr.vxh_cxsiz, src->vx_hdr.vxh_cysiz);
						iter_dst_x = next_dst_x;
					} while (++xwholetiles_i < xwholetiles_count);
					iter_src_size_x %= src->vx_hdr.vxh_cxsiz;
					iter_dst_size_x = lasttile_dst_size_x;
				}

				/* Right side */
				LOCAL_stretch(iter_dst_x, iter_dst_y, lasttile_dst_size_x, tile_h,
				              0, 0, iter_src_size_x, src->vx_hdr.vxh_cysiz);

				iter_dst_y = next_dst_y;
			}
			iter_src_size_y %= src->vx_hdr.vxh_cysiz;
			iter_dst_size_y = lasttile_dst_size_y;
		}
		if likely(!iter_src_size_y)
			return;

		/* Bottom-left corner */
		LOCAL_stretch(dst_x, iter_dst_y, firsttile_dst_size_x, iter_dst_size_y,
		              src_x, 0, src_maxsx, iter_src_size_y);

		/* Bottom bar */
		iter_src_size_x = src_size_x - src_maxsx;
		iter_dst_x      = dst_x + firsttile_dst_size_x;
		iter_dst_size_x = dst_size_x - firsttile_dst_size_x;
		if (iter_src_size_x > src->vx_hdr.vxh_cxsiz) {
			video_coord_t base_dst_x;
			video_coord_t xwholetiles_i;
			xwholetiles_count = iter_src_size_x / src->vx_hdr.vxh_cxsiz;
			lasttile_dst_size_x = xsrc2dst(iter_src_size_x % src->vx_hdr.vxh_cxsiz);
			wholetiles_dst_size_x = iter_dst_size_x - lasttile_dst_size_x;
			base_dst_x = iter_dst_x;
			for (xwholetiles_i = 0; xwholetiles_i < xwholetiles_count; ++xwholetiles_i) {
				video_coord_t next_dst_x;
				next_dst_x = base_dst_x + (wholetiles_dst_size_x * (xwholetiles_i + 1)) / xwholetiles_count;
				LOCAL_stretch(iter_dst_x, iter_dst_y, next_dst_x - iter_dst_x, iter_dst_size_y,
				              0, 0, src->vx_hdr.vxh_cxsiz, iter_src_size_y);
				iter_dst_x = next_dst_x;
			}
			iter_src_size_x %= src->vx_hdr.vxh_cxsiz;
			iter_dst_size_x = lasttile_dst_size_x;
		}

		/* Bottom-right corner (render via fallthru) */
#ifdef LOCAL_USE_SWBLITTER3
		out_x += (iter_dst_x - dst_x);
		out_y += (iter_dst_y - dst_y);
#endif /* LOCAL_USE_SWBLITTER3 */
		dst_x = iter_dst_x;
		dst_y = iter_dst_y;
		dst_size_x = iter_dst_size_x;
		dst_size_y = iter_dst_size_y;
		src_x = 0;
		src_y = 0;
		src_size_x = iter_src_size_x;
		src_size_y = iter_src_size_y;
	} else if (src_size_x > src_maxsx) {
		video_dim_t firsttile_dst_size_x = xsrc2dst(src_maxsx);
		LOCAL_stretch2dst(firsttile_dst_size_x, dst_size_y,
		                  src_x, src_y, src_maxsx, src_size_y);
		src_size_x -= src_maxsx;
		LOCAL_dst_x_add(firsttile_dst_size_x);
		dst_size_x -= firsttile_dst_size_x;
		if (src_size_x > src->vx_hdr.vxh_cxsiz) {
			/* Whole tiles */
			video_coord_t xwholetiles_i;
			video_dim_t xwholetiles_count = src_size_x / src->vx_hdr.vxh_cxsiz;
			video_dim_t lasttile_dst_size_x = xsrc2dst(src_size_x % src->vx_hdr.vxh_cxsiz);
			video_dim_t wholetiles_dst_size_x = dst_size_x - lasttile_dst_size_x;
			video_coord_t base_dst_x = dst_x;
			for (xwholetiles_i = 0; xwholetiles_i < xwholetiles_count; ++xwholetiles_i) {
				video_coord_t next_dst_x;
				next_dst_x = base_dst_x + (wholetiles_dst_size_x * (xwholetiles_i + 1)) / xwholetiles_count;
				LOCAL_stretch2dst(next_dst_x - dst_x, dst_size_y,
				                  0, src_y, src->vx_hdr.vxh_cxsiz, src_size_y);
#ifdef LOCAL_USE_SWBLITTER3
				out_x += (next_dst_x - dst_x);
#endif /* LOCAL_USE_SWBLITTER3 */
				dst_x = next_dst_x;
			}
			src_size_x %= src->vx_hdr.vxh_cxsiz;
			dst_size_x = lasttile_dst_size_x;
		}
		src_x = 0; /* Fallthru to render the last part */
	} else if (src_size_y > src_maxsy) {
		video_dim_t firsttile_dst_size_y = ysrc2dst(src_maxsy);
		LOCAL_stretch2dst(dst_size_x, firsttile_dst_size_y, src_x, src_y, src_size_x, src_maxsy);
		src_size_y -= src_maxsy;
		LOCAL_dst_y_add(firsttile_dst_size_y);
		dst_size_y -= firsttile_dst_size_y;
		if (src_size_y > src->vx_hdr.vxh_cysiz) {
			/* Whole tiles */
			video_coord_t ywholetiles_i;
			video_dim_t ywholetiles_count = src_size_y / src->vx_hdr.vxh_cysiz;
			video_dim_t lasttile_dst_size_y = ysrc2dst(src_size_y % src->vx_hdr.vxh_cysiz);
			video_dim_t wholetiles_dst_size_y = dst_size_y - lasttile_dst_size_y;
			video_coord_t base_dst_y = dst_y;
			for (ywholetiles_i = 0; ywholetiles_i < ywholetiles_count; ++ywholetiles_i) {
				video_coord_t next_dst_y;
				next_dst_y = base_dst_y + (wholetiles_dst_size_y * (ywholetiles_i + 1)) / ywholetiles_count;
				LOCAL_stretch2dst(dst_size_x, next_dst_y - dst_y,
				                  src_x, 0, src_size_x, src->vx_hdr.vxh_cysiz);
#ifdef LOCAL_USE_SWBLITTER3
				out_y += (next_dst_y - dst_y);
#endif /* LOCAL_USE_SWBLITTER3 */
				dst_y = next_dst_y;
			}
			src_size_y %= src->vx_hdr.vxh_cysiz;
			dst_size_y = lasttile_dst_size_y;
		}
		src_y = 0; /* Fallthru to render the last part */
	}

	LOCAL_stretch2dst(dst_size_x, dst_size_y, src_x, src_y, src_size_x, src_size_y);
#undef LOCAL_stretch
#undef LOCAL_stretch2dst
#undef LOCAL_dst_x_add
#undef LOCAL_dst_y_add
#undef xdst2src
#undef ydst2src
#undef xsrc2dst
#undef ysrc2dst
}



INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter_blit_wrap(LOCAL_struct_video_blitter const *__restrict self,
                                   video_offset_t dst_x, video_offset_t dst_y,
#ifdef LOCAL_USE_SWBLITTER3
                                   video_offset_t rddst_x, video_offset_t rddst_y,
#endif /* LOCAL_USE_SWBLITTER3 */
                                   video_offset_t src_x, video_offset_t src_y,
                                   video_dim_t size_x, video_dim_t size_y) {
	/* Handle the case where "dst" has wrapping enabled. */
#ifdef LOCAL_USE_SWBLITTER3
	struct video_gfx const *dst = self->vbt3_wrdst;
#else /* LOCAL_USE_SWBLITTER3 */
	struct video_gfx const *dst = self->vbt_dst;
#endif /* !LOCAL_USE_SWBLITTER3 */
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = size_x;
	video_dim_t yinb = size_y;
	if (dst->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_coord_t cxend;
		dst_x = wrap(dst_x, dst->vx_hdr.vxh_cxsiz);
		if (size_x > dst->vx_hdr.vxh_cxsiz)
			size_x = dst->vx_hdr.vxh_cxsiz;
		cxend = (video_coord_t)dst_x + size_x;
		if (OVERFLOW_USUB(cxend, dst->vx_hdr.vxh_cxsiz, &xwrap)) {
			xwrap = 0;
		} else {
			xinb = dst->vx_hdr.vxh_cxsiz - (video_coord_t)dst_x;
		}
	}
	if (dst->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_coord_t cyend;
		dst_y = wrap(dst_y, dst->vx_hdr.vxh_cysiz);
		if (size_y > dst->vx_hdr.vxh_cysiz)
			size_y = dst->vx_hdr.vxh_cysiz;
		cyend = (video_coord_t)dst_y + size_y;
		if (OVERFLOW_USUB(cyend, dst->vx_hdr.vxh_cysiz, &ywrap)) {
			ywrap = 0;
		} else {
			yinb = dst->vx_hdr.vxh_cysiz - (video_coord_t)dst_y;
		}
	}
#ifdef LOCAL_USE_SWBLITTER3
#define LOCAL_next(dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_) \
	LOCAL_libvideo_swblitter_blit_rdwrap(self, dst_x_, dst_y_, rddst_x, rddst_y, src_x_, src_y_, size_x_, size_y_)
#else /* LOCAL_USE_SWBLITTER3 */
#define LOCAL_next(dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_) \
	LOCAL_libvideo_swblitter_blit_rdwrap(self, dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_)
#endif /* !LOCAL_USE_SWBLITTER3 */
	if (xwrap && ywrap) /* Must do a partial fill at the top-left */
		LOCAL_next(0, 0, src_x + xinb, src_y + yinb, xwrap, ywrap);
	if (xwrap) /* Must do a partial fill at the left */
		LOCAL_next(0, dst_y, src_x + xinb, src_y, xwrap, size_y);
	if (ywrap) /* Must do a partial fill at the top */
		LOCAL_next(dst_x, 0, src_x, src_y + yinb, size_x, ywrap);
	LOCAL_next(dst_x, dst_y, src_x, src_y, xinb, yinb);
#undef LOCAL_next
}


INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter_stretch_wrap(LOCAL_struct_video_blitter const *__restrict self,
                                      video_offset_t dst_x, video_offset_t dst_y,
#ifdef LOCAL_USE_SWBLITTER3
                                      video_offset_t rddst_x, video_offset_t rddst_y,
#endif /* LOCAL_USE_SWBLITTER3 */
                                      video_dim_t dst_size_x, video_dim_t dst_size_y,
                                      video_offset_t src_x, video_offset_t src_y,
                                      video_dim_t src_size_x, video_dim_t src_size_y) {
	/* Handle the case where "dst" has wrapping enabled. */
#ifdef LOCAL_USE_SWBLITTER3
	struct video_gfx const *dst = self->vbt3_wrdst;
#else /* LOCAL_USE_SWBLITTER3 */
	struct video_gfx const *dst = self->vbt_dst;
#endif /* !LOCAL_USE_SWBLITTER3 */
#define xdst2src(x) ((video_coord_t)(((uint64_t)(x) * src_size_x) / dst_size_x))
#define ydst2src(y) ((video_coord_t)(((uint64_t)(y) * src_size_y) / dst_size_y))
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = dst_size_x;
	video_dim_t yinb = dst_size_y;
	if (dst->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_coord_t cxend;
		dst_x = wrap(dst_x, dst->vx_hdr.vxh_cxsiz);
		if (dst_size_x > dst->vx_hdr.vxh_cxsiz) {
			src_size_x = xdst2src(dst->vx_hdr.vxh_cxsiz);
			dst_size_x = dst->vx_hdr.vxh_cxsiz;
		}
		cxend = (video_coord_t)dst_x + dst_size_x;
		if (OVERFLOW_USUB(cxend, dst->vx_hdr.vxh_cxsiz, &xwrap)) {
			xwrap = 0;
		} else {
			xinb = dst->vx_hdr.vxh_cxsiz - (video_coord_t)dst_x;
		}
	}
	if (dst->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_coord_t cyend;
		dst_y = wrap(dst_y, dst->vx_hdr.vxh_cysiz);
		if (dst_size_y > dst->vx_hdr.vxh_cysiz) {
			src_size_y = ydst2src(dst->vx_hdr.vxh_cysiz);
			dst_size_y = dst->vx_hdr.vxh_cysiz;
		}
		cyend = (video_coord_t)dst_y + dst_size_y;
		if (OVERFLOW_USUB(cyend, dst->vx_hdr.vxh_cysiz, &ywrap)) {
			ywrap = 0;
		} else {
			yinb = dst->vx_hdr.vxh_cysiz - (video_coord_t)dst_y;
		}
	}

#ifdef LOCAL_USE_SWBLITTER3
#define LOCAL_next(dst_x_, dst_y_, dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_) \
	LOCAL_libvideo_swblitter_stretch_rdwrap(self, dst_x_, dst_y_, rddst_x, rddst_y, dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_)
#else /* LOCAL_USE_SWBLITTER3 */
#define LOCAL_next(dst_x_, dst_y_, dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_) \
	LOCAL_libvideo_swblitter_stretch_rdwrap(self, dst_x_, dst_y_, dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_)
#endif /* !LOCAL_USE_SWBLITTER3 */
	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		size_t chunk_src_x      = xdst2src(xinb);
		size_t chunk_src_y      = ydst2src(yinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		size_t chunk_src_size_y = ydst2src(ywrap);
		LOCAL_next(0, 0, xwrap, ywrap,
		           src_x + chunk_src_x, src_y + chunk_src_y,
		           chunk_src_size_x, chunk_src_size_y);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		size_t chunk_src_x      = xdst2src(xinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		LOCAL_next(0, dst_y, xwrap, dst_size_y,
		           src_x + chunk_src_x, src_y,
		           chunk_src_size_x, src_size_y);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		size_t chunk_src_y      = ydst2src(yinb);
		size_t chunk_src_size_y = ydst2src(ywrap);
		LOCAL_next(dst_x, 0, dst_size_x, ywrap,
		           src_x, src_y + chunk_src_y,
		           src_size_x, chunk_src_size_y);
	}
	LOCAL_next(dst_x, dst_y, dst_size_x, dst_size_y,
	           src_x, src_y, src_size_x, src_size_y);
#undef LOCAL_next
#undef xdst2src
#undef ydst2src
}

#ifdef LOCAL_USE_SWBLITTER3
INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter_blit_rdwrap1(LOCAL_struct_video_blitter const *__restrict self,
                                      video_offset_t out_x, video_offset_t out_y,
                                      video_offset_t dst_x, video_offset_t dst_y,
                                      video_offset_t src_x, video_offset_t src_y,
                                      video_dim_t size_x, video_dim_t size_y) {
	/* Handle the case where "rddst" has wrapping enabled. */
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	struct video_gfx const *src = self->vbt3_src;
	video_dim_t dst_maxsx = size_x; /* # of pixes after dst_x before wrap */
	video_dim_t dst_maxsy = size_y; /* # of pixes after dst_y before wrap */

	if (dst->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_dim_t src_endx;
		/* Do some preliminary clamping on destination coords.
		 * This is needed so  we can properly calculate  tiled
		 * repeated when wrapping is enabled in "dst". */
		if unlikely(src_x < 0) {
			video_dim_t delta = (video_dim_t)-src_x;
			if (OVERFLOW_USUB(size_x, delta, &size_x))
				return;
			out_x += delta;
			src_x = 0;
			dst_x += delta;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)src_x, size_x, &src_endx) ||
		            src_endx > src->vx_hdr.vxh_cxsiz) {
			if unlikely((video_coord_t)src_x >= src->vx_hdr.vxh_cxsiz)
				return;
			size_x = src->vx_hdr.vxh_cxsiz - (video_coord_t)src_x;
		}
		if unlikely(out_x < 0) {
			video_dim_t delta = (video_dim_t)-out_x;
			if (OVERFLOW_USUB(size_x, delta, &size_x))
				return;
			src_x += delta;
			out_x = 0;
			dst_x += delta;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)out_x, size_x, &src_endx) ||
		            src_endx > out->vx_hdr.vxh_cxsiz) {
			if unlikely((video_coord_t)out_x >= out->vx_hdr.vxh_cxsiz)
				return;
			size_x = out->vx_hdr.vxh_cxsiz - (video_coord_t)out_x;
		}
		dst_x     = wrap(dst_x, dst->vx_hdr.vxh_cxsiz);
		dst_maxsx = dst->vx_hdr.vxh_cxsiz - (video_coord_t)dst_x;
	}

	if (dst->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_dim_t src_endy;
		/* Do some preliminary clamping on destination coords.
		 * This is needed so  we can properly calculate  tiled
		 * repeated when wrapping is enabled in "dst". */
		if unlikely(src_y < 0) {
			video_dim_t delta = (video_dim_t)-src_y;
			if (OVERFLOW_USUB(size_y, delta, &size_y))
				return;
			out_y += delta;
			src_y = 0;
			dst_y += delta;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)src_y, size_y, &src_endy) ||
		            src_endy > src->vx_hdr.vxh_cysiz) {
			if unlikely((video_coord_t)src_y >= src->vx_hdr.vxh_cysiz)
				return;
			size_y = src->vx_hdr.vxh_cysiz - (video_coord_t)src_y;
		}
		if unlikely(out_y < 0) {
			video_dim_t delta = (video_dim_t)-out_y;
			if (OVERFLOW_USUB(size_y, delta, &size_y))
				return;
			src_y += delta;
			out_y = 0;
			dst_y += delta;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)out_y, size_y, &src_endy) ||
		            src_endy > out->vx_hdr.vxh_cysiz) {
			if unlikely((video_coord_t)out_y >= out->vx_hdr.vxh_cysiz)
				return;
			size_y = out->vx_hdr.vxh_cysiz - (video_coord_t)out_y;
		}
		dst_y     = wrap(dst_y, dst->vx_hdr.vxh_cysiz);
		dst_maxsy = dst->vx_hdr.vxh_cysiz - (video_coord_t)dst_y;
	}

#define LOCAL_blit(src_x_, src_y_, dst_x_, dst_y_, size_x_, size_y_)                        \
	LOCAL_libvideo_swblitter_blit(self, out_x + (src_x_ - src_x), out_y + (src_y_ - src_y), \
	                              dst_x_, dst_y_, src_x_, src_y_, size_x_, size_y_)
#define LOCAL_blit2out(dst_x_, dst_y_, size_x_, size_y_) \
	LOCAL_libvideo_swblitter_blit(self, out_x, out_y, dst_x_, dst_y_, src_x, src_y, size_x_, size_y_)
	if ((size_x > dst_maxsx) && (size_y > dst_maxsy)) {
		video_dim_t iter_size_x;
		video_dim_t iter_size_y;
		video_dim_t iter_src_x;
		video_dim_t iter_src_y;

		/* Must render the rddst graphic multiple times */
		iter_size_y = size_y;
		iter_src_y  = src_y;

		/* Deal with unaligned tiles near the top */
		if unlikely(dst_maxsy < dst->vx_hdr.vxh_cysiz) {
			/* Top-left corner */
			LOCAL_blit2out(dst_x, dst_y, dst_maxsx, dst_maxsy);

			/* Top bar */
			iter_size_x = size_x - dst_maxsx;
			iter_src_x = src_x + dst_maxsx;
			while (iter_size_x > dst->vx_hdr.vxh_cxsiz) {
				LOCAL_blit(iter_src_x, iter_src_y, 0, dst_y, dst->vx_hdr.vxh_cxsiz, dst_maxsy);
				iter_size_x -= dst->vx_hdr.vxh_cxsiz;
				iter_src_x += dst->vx_hdr.vxh_cxsiz;
			}

			/* Top-right corner */
			LOCAL_blit(iter_src_x, iter_src_y, 0, dst_y, iter_size_x, dst_maxsy);
			iter_size_y -= dst_maxsy;
			iter_src_y += dst_maxsy;
		}

		/* Iterate whole rows */
		while (iter_size_y >= dst->vx_hdr.vxh_cysiz) {
			/* Left side */
			LOCAL_blit(src_x, iter_src_y, dst_x, 0, dst_maxsx, dst->vx_hdr.vxh_cysiz);

			/* Center */
			iter_size_x = size_x - dst_maxsx;
			iter_src_x = src_x + dst_maxsx;
			while (iter_size_x > dst->vx_hdr.vxh_cxsiz) {
				LOCAL_blit(iter_src_x, iter_src_y, 0, 0, dst->vx_hdr.vxh_cxsiz, dst->vx_hdr.vxh_cysiz);
				iter_size_x -= dst->vx_hdr.vxh_cxsiz;
				iter_src_x += dst->vx_hdr.vxh_cxsiz;
			}

			/* Right side */
			LOCAL_blit(iter_src_x, iter_src_y, 0, 0, iter_size_x, dst->vx_hdr.vxh_cysiz);

			iter_size_y -= dst->vx_hdr.vxh_cysiz;
			iter_src_y += dst->vx_hdr.vxh_cysiz;
		}

		if likely(!iter_size_y)
			return;

		/* Bottom-left corner */
		LOCAL_blit(src_x, iter_src_y, dst_x, 0, dst_maxsx, iter_size_y);

		/* Bottom bar */
		iter_size_x = size_x - dst_maxsx;
		iter_src_x = src_x + dst_maxsx;
		while (iter_size_x > dst->vx_hdr.vxh_cxsiz) {
			LOCAL_blit(iter_src_x, iter_src_y, 0, 0, dst->vx_hdr.vxh_cxsiz, iter_size_y);
			iter_size_x -= dst->vx_hdr.vxh_cxsiz;
			iter_src_x += dst->vx_hdr.vxh_cxsiz;
		}

		/* Bottom-right corner (render via fallthru) */
#ifdef LOCAL_USE_SWBLITTER3
		out_x += (iter_src_x - src_x);
		out_y += (iter_src_y - src_y);
#endif /* LOCAL_USE_SWBLITTER3 */
		src_x  = iter_src_x;
		src_y  = iter_src_y;
		dst_x  = 0;
		dst_y  = 0;
		size_x = iter_size_x;
		size_y = iter_size_y;
	} else if (size_x > dst_maxsx) {
		LOCAL_blit2out(dst_x, dst_y, dst_maxsx, size_y);
		size_x -= dst_maxsx;
		src_x += dst_maxsx;
		out_x += dst_maxsx;
		while (size_x > dst->vx_hdr.vxh_cxsiz) {
			LOCAL_blit2out(0, dst_y, dst->vx_hdr.vxh_cxsiz, size_y);
			size_x -= dst->vx_hdr.vxh_cxsiz;
			src_x += dst->vx_hdr.vxh_cxsiz;
			out_x += dst->vx_hdr.vxh_cxsiz;
		}
		dst_x = 0; /* Fallthru to render the last part */
	} else if (size_y > dst_maxsy) {
		LOCAL_blit2out(dst_x, dst_y, size_x, dst_maxsy);
		size_y -= dst_maxsy;
		src_y += dst_maxsy;
		out_y += dst_maxsy;
		while (size_y > dst->vx_hdr.vxh_cysiz) {
			LOCAL_blit2out(dst_x, 0, size_x, dst->vx_hdr.vxh_cysiz);
			size_y -= dst->vx_hdr.vxh_cysiz;
			src_y += dst->vx_hdr.vxh_cysiz;
			out_y += dst->vx_hdr.vxh_cysiz;
		}
		dst_y = 0; /* Fallthru to render the last part */
	}

	LOCAL_blit2out(dst_x, dst_y, size_x, size_y);
#undef LOCAL_blit
#undef LOCAL_blit2out
	LOCAL_libvideo_swblitter_blit_rdwrap(self, out_x, out_y, dst_x, dst_y,
	                                     src_x, src_y, size_x, size_y);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter_stretch_rdwrap1(LOCAL_struct_video_blitter const *__restrict self,
                                         video_offset_t out_x, video_offset_t out_y,
                                         video_offset_t dst_x, video_offset_t dst_y,
                                         video_dim_t dst_size_x, video_dim_t dst_size_y,
                                         video_offset_t src_x, video_offset_t src_y,
                                         video_dim_t src_size_x, video_dim_t src_size_y) {
#define xdst2src(x) ((video_coord_t)(((uint64_t)(x) * src_size_x) / dst_size_x))
#define ydst2src(y) ((video_coord_t)(((uint64_t)(y) * src_size_y) / dst_size_y))
#define xsrc2dst(x) ((video_coord_t)(((uint64_t)(x) * dst_size_x) / src_size_x))
#define ysrc2dst(y) ((video_coord_t)(((uint64_t)(y) * dst_size_y) / src_size_y))
	/* Handle the case where "rddst" has wrapping enabled. */
	struct video_gfx const *out = self->vbt3_wrdst;
	struct video_gfx const *dst = self->vbt3_rddst;
	video_dim_t dst_maxsx = dst_size_x; /* # of pixes after dst_x before wrap */
	video_dim_t dst_maxsy = dst_size_y; /* # of pixes after dst_y before wrap */

	if (dst->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_dim_t out_endx;
		/* Do some  preliminary clamping  on output  coords.
		 * This is needed so we can properly calculate tiled
		 * repeated when wrapping is enabled in "rddst". */
		if unlikely(out_x < 0) {
			video_dim_t delta = (video_dim_t)-out_x;
			video_dim_t new_dst_size_x;
			if (OVERFLOW_USUB(dst_size_x, delta, &new_dst_size_x))
				return;
			src_size_x -= xdst2src(delta);
			src_x += xdst2src(delta);
			dst_size_x = new_dst_size_x;
			dst_x += delta;
			out_x = 0;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)out_x, dst_size_x, &out_endx) ||
		            out_endx > out->vx_hdr.vxh_cxsiz) {
			video_dim_t new_dst_size_x;
			if unlikely((video_coord_t)out_x >= out->vx_hdr.vxh_cxsiz)
				return;
			new_dst_size_x = out->vx_hdr.vxh_cxsiz - (video_coord_t)out_x;
			src_size_x -= xdst2src(dst_size_x - new_dst_size_x);
			dst_size_x = new_dst_size_x;
		}
		dst_x     = wrap(dst_x, dst->vx_hdr.vxh_cxsiz);
		dst_maxsx = dst->vx_hdr.vxh_cxsiz - (video_coord_t)dst_x;
	}

	if (dst->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_dim_t out_endy;
		/* Do some  preliminary clamping  on output  coords.
		 * This is needed so we can properly calculate tiled
		 * repeated when wrapping is enabled in "rddst". */
		if unlikely(out_y < 0) {
			video_dim_t delta = (video_dim_t)-out_y;
			video_dim_t new_dst_size_y;
			if (OVERFLOW_USUB(dst_size_y, delta, &new_dst_size_y))
				return;
			src_size_y -= ydst2src(delta);
			src_y += ydst2src(delta);
			dst_size_y = new_dst_size_y;
			dst_y += delta;
			out_y = 0;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)out_y, dst_size_y, &out_endy) ||
		            out_endy > out->vx_hdr.vxh_cysiz) {
			video_dim_t new_dst_size_y;
			if unlikely((video_coord_t)out_y >= out->vx_hdr.vxh_cysiz)
				return;
			new_dst_size_y = out->vx_hdr.vxh_cysiz - (video_coord_t)out_y;
			src_size_y -= ydst2src(dst_size_y - new_dst_size_y);
			dst_size_y = new_dst_size_y;
		}
		dst_y     = wrap(dst_y, dst->vx_hdr.vxh_cysiz);
		dst_maxsy = dst->vx_hdr.vxh_cysiz - (video_coord_t)dst_y;
	}

#define LOCAL_stretch(out_x_, out_y_, dst_x_, dst_y_, dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_) \
	LOCAL_libvideo_swblitter_stretch(self, out_x_, out_y_, dst_x_, dst_y_, dst_size_x_, dst_size_y_, src_x_, src_y_, src_size_x_, src_size_y_)
	if ((dst_size_x > dst_maxsx) && (dst_size_y > dst_maxsy)) {
		video_dim_t firsttile_src_size_x = xdst2src(dst_maxsx);
		video_dim_t firsttile_src_size_y = ydst2src(dst_maxsy);
		video_coord_t iter_out_x;
		video_coord_t iter_out_y;
		video_coord_t iter_src_x;
		video_coord_t iter_src_size_x;
		video_coord_t iter_dst_size_x;
		video_coord_t iter_src_y;
		video_coord_t iter_src_size_y;
		video_coord_t iter_dst_size_y;
		video_dim_t xwholetiles_count = 0;
		video_dim_t lasttile_src_size_x = 0;
		video_dim_t wholetiles_src_size_x = 0;

		/* Deal with unaligned tiles near the top */

		/* Top-left corner */
		LOCAL_stretch(out_x, out_y, dst_x, dst_y, dst_maxsx, dst_maxsy,
		              src_x, src_y, firsttile_src_size_x, firsttile_src_size_y);

		/* Top bar */
		iter_out_x      = out_x + dst_maxsx;
		iter_dst_size_x = dst_size_x - dst_maxsx;
		iter_src_x      = src_x + firsttile_src_size_x;
		iter_src_size_x = src_size_x - firsttile_src_size_x;
		if (iter_dst_size_x > dst->vx_hdr.vxh_cxsiz) {
			video_coord_t base_src_x;
			video_coord_t xwholetiles_i;
			xwholetiles_count = iter_dst_size_x / dst->vx_hdr.vxh_cxsiz;
			lasttile_src_size_x = xdst2src(iter_dst_size_x % dst->vx_hdr.vxh_cxsiz);
			wholetiles_src_size_x = iter_src_size_x - lasttile_src_size_x;
			base_src_x = iter_src_x;
			for (xwholetiles_i = 0; xwholetiles_i < xwholetiles_count; ++xwholetiles_i) {
				video_coord_t next_src_x;
				next_src_x = base_src_x + (wholetiles_src_size_x * (xwholetiles_i + 1)) / xwholetiles_count;
				LOCAL_stretch(iter_out_x, out_y, 0, dst_y, dst->vx_hdr.vxh_cxsiz, dst_maxsy,
				              iter_src_x, src_y, next_src_x - iter_src_x, firsttile_src_size_y);
				iter_src_x = next_src_x;
				iter_out_x += dst->vx_hdr.vxh_cxsiz;
			}
			iter_dst_size_x %= dst->vx_hdr.vxh_cxsiz;
			iter_src_size_x = lasttile_src_size_x;
		}

		/* Top-right corner */
		LOCAL_stretch(iter_out_x, out_y, 0, dst_y, iter_dst_size_x, dst_maxsy,
		              iter_src_x, src_y, iter_src_size_x, firsttile_src_size_y);

		/* Iterate whole rows */
		iter_out_y      = out_y + dst_maxsy;
		iter_dst_size_y = dst_size_y - dst_maxsy;
		iter_src_y      = src_y + firsttile_src_size_y;
		iter_src_size_y = src_size_y - firsttile_src_size_y;
		if likely(iter_dst_size_y >= dst->vx_hdr.vxh_cysiz) {
			video_coord_t ywholetiles_i;
			video_dim_t ywholetiles_count = iter_dst_size_y / dst->vx_hdr.vxh_cysiz;
			video_dim_t lasttile_src_size_y = ydst2src(iter_dst_size_y % dst->vx_hdr.vxh_cysiz);
			video_dim_t wholetiles_src_size_y = iter_src_size_y - lasttile_src_size_y;
			video_coord_t base_src_y = iter_src_y;
			for (ywholetiles_i = 0; ywholetiles_i < ywholetiles_count; ++ywholetiles_i) {
				video_coord_t next_src_y;
				video_dim_t tile_h;
				next_src_y = base_src_y + (wholetiles_src_size_y * (ywholetiles_i + 1)) / ywholetiles_count;
				tile_h = next_src_y - iter_src_y;

				/* Left side */
				LOCAL_stretch(out_x, iter_out_y, dst_x, 0, dst_maxsx, dst->vx_hdr.vxh_cysiz,
				              src_x, iter_src_y, firsttile_src_size_x, tile_h);

				/* Center (whole tiles) */
				iter_out_x      = out_x + dst_maxsx;
				iter_dst_size_x = dst_size_x - dst_maxsx;
				iter_src_x      = src_x + firsttile_src_size_x;
				iter_src_size_x = src_size_x - firsttile_src_size_x;
				if (xwholetiles_count) {
					video_coord_t base_src_x = iter_src_x;
					video_coord_t xwholetiles_i = 0;
					do {
						video_coord_t next_src_x;
						next_src_x = base_src_x + (wholetiles_src_size_x * (xwholetiles_i + 1)) / xwholetiles_count;
						LOCAL_stretch(iter_out_x, iter_out_y,
						              0, 0, dst->vx_hdr.vxh_cxsiz, dst->vx_hdr.vxh_cysiz,
						              iter_src_x, iter_src_y, next_src_x - iter_src_x, tile_h);
						iter_src_x = next_src_x;
						iter_out_x += dst->vx_hdr.vxh_cxsiz;
					} while (++xwholetiles_i < xwholetiles_count);
					iter_dst_size_x %= dst->vx_hdr.vxh_cxsiz;
					iter_src_size_x = lasttile_src_size_x;
				}

				/* Right side */
				LOCAL_stretch(iter_out_x, iter_out_y, 0, 0, iter_dst_size_x, dst->vx_hdr.vxh_cysiz,
				              iter_src_x, iter_src_y, lasttile_src_size_x, tile_h);

				iter_src_y = next_src_y;
				iter_out_y += dst->vx_hdr.vxh_cysiz;
			}
			iter_dst_size_y %= dst->vx_hdr.vxh_cysiz;
			iter_src_size_y = lasttile_src_size_y;
		}
		if likely(!iter_dst_size_y)
			return;

		/* Bottom-left corner */
		LOCAL_stretch(out_x, iter_out_y, dst_x, 0, dst_maxsx, iter_dst_size_y,
		              src_x, iter_src_y, firsttile_src_size_x, iter_src_size_y);

		/* Bottom bar */
		iter_out_x      = out_x + dst_maxsx;
		iter_dst_size_x = dst_size_x - dst_maxsx;
		iter_src_x      = src_x + firsttile_src_size_x;
		iter_src_size_x = src_size_x - firsttile_src_size_x;
		if (iter_dst_size_x > dst->vx_hdr.vxh_cxsiz) {
			video_coord_t base_src_x;
			video_coord_t xwholetiles_i;
			xwholetiles_count = iter_dst_size_x / dst->vx_hdr.vxh_cxsiz;
			lasttile_src_size_x = xdst2src(iter_dst_size_x % dst->vx_hdr.vxh_cxsiz);
			wholetiles_src_size_x = iter_src_size_x - lasttile_src_size_x;
			base_src_x = iter_src_x;
			for (xwholetiles_i = 0; xwholetiles_i < xwholetiles_count; ++xwholetiles_i) {
				video_coord_t next_src_x;
				next_src_x = base_src_x + (wholetiles_src_size_x * (xwholetiles_i + 1)) / xwholetiles_count;
				LOCAL_stretch(iter_out_x, iter_out_y, 0, 0, dst->vx_hdr.vxh_cxsiz, iter_dst_size_y,
				              iter_src_x, iter_src_y, next_src_x - iter_src_x, iter_src_size_y);
				iter_src_x = next_src_x;
				iter_out_x += dst->vx_hdr.vxh_cxsiz;
			}
			iter_dst_size_x %= dst->vx_hdr.vxh_cxsiz;
			iter_src_size_x = lasttile_src_size_x;
		}

		/* Bottom-right corner (render via fallthru) */
		out_x = iter_out_x;
		out_y = iter_out_y;
		src_x = iter_src_x;
		src_y = iter_src_y;
		src_size_x = iter_src_size_x;
		src_size_y = iter_src_size_y;
		dst_x = 0;
		dst_y = 0;
		dst_size_x = iter_dst_size_x;
		dst_size_y = iter_dst_size_y;
	} else if (dst_size_x > dst_maxsx) {
		video_dim_t firsttile_src_size_x = xdst2src(dst_maxsx);
		LOCAL_stretch(out_x, out_y, dst_x, dst_y, dst_maxsx, dst_size_y,
		              src_x, src_y, firsttile_src_size_x, src_size_y);
		dst_size_x -= dst_maxsx;
		out_x += dst_maxsx;
		src_x += firsttile_src_size_x;
		src_size_x -= firsttile_src_size_x;
		if (dst_size_x > dst->vx_hdr.vxh_cxsiz) {
			/* Whole tiles */
			video_coord_t xwholetiles_i;
			video_dim_t xwholetiles_count = dst_size_x / dst->vx_hdr.vxh_cxsiz;
			video_dim_t lasttile_src_size_x = xdst2src(dst_size_x % dst->vx_hdr.vxh_cxsiz);
			video_dim_t wholetiles_src_size_x = src_size_x - lasttile_src_size_x;
			video_coord_t base_src_x = src_x;
			for (xwholetiles_i = 0; xwholetiles_i < xwholetiles_count; ++xwholetiles_i) {
				video_coord_t next_src_x;
				next_src_x = base_src_x + (wholetiles_src_size_x * (xwholetiles_i + 1)) / xwholetiles_count;
				LOCAL_stretch(out_x, out_y, 0, dst_y, dst->vx_hdr.vxh_cxsiz, dst_size_y,
				              src_x, src_y, next_src_x - src_x, src_size_y);
				out_x += (next_src_x - src_x);
				src_x = next_src_x;
			}
			dst_size_x %= dst->vx_hdr.vxh_cxsiz;
			src_size_x = lasttile_src_size_x;
		}
		dst_x = 0; /* Fallthru to render the last part */
	} else if (dst_size_y > dst_maxsy) {
		video_dim_t firsttile_src_size_y = ydst2src(dst_maxsy);
		LOCAL_stretch(out_x, out_y, dst_x, dst_y, dst_size_x, dst_maxsy,
		              src_x, src_y, src_size_x, firsttile_src_size_y);
		dst_size_y -= dst_maxsy;
		out_y += dst_maxsy;
		src_y += firsttile_src_size_y;
		src_size_y -= firsttile_src_size_y;
		if (dst_size_y > dst->vx_hdr.vxh_cysiz) {
			/* Whole tiles */
			video_coord_t ywholetiles_i;
			video_dim_t ywholetiles_count = dst_size_y / dst->vx_hdr.vxh_cysiz;
			video_dim_t lasttile_src_size_y = ydst2src(dst_size_y % dst->vx_hdr.vxh_cysiz);
			video_dim_t wholetiles_src_size_y = src_size_y - lasttile_src_size_y;
			video_coord_t base_src_y = src_y;
			for (ywholetiles_i = 0; ywholetiles_i < ywholetiles_count; ++ywholetiles_i) {
				video_coord_t next_src_y;
				next_src_y = base_src_y + (wholetiles_src_size_y * (ywholetiles_i + 1)) / ywholetiles_count;
				LOCAL_stretch(out_x, out_y, dst_x, 0, dst_size_x, dst->vx_hdr.vxh_cysiz,
				              src_x, src_y, src_size_x, next_src_y - src_y);
				out_y += (next_src_y - src_y);
				src_y = next_src_y;
			}
			dst_size_y %= dst->vx_hdr.vxh_cysiz;
			src_size_y = lasttile_src_size_y;
		}
		dst_y = 0; /* Fallthru to render the last part */
	}

	LOCAL_stretch(out_x, out_y,
	              dst_x, dst_y, dst_size_x, dst_size_y,
	              src_x, src_y, src_size_x, src_size_y);
#undef LOCAL_stretch
#undef xsrc2dst
#undef ysrc2dst
#undef xdst2src
#undef ydst2src
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter_blit_wrap1(LOCAL_struct_video_blitter const *__restrict self,
                                    video_offset_t out_x, video_offset_t out_y,
                                    video_offset_t dst_x, video_offset_t dst_y,
                                    video_offset_t src_x, video_offset_t src_y,
                                    video_dim_t size_x, video_dim_t size_y) {
	/* Handle the case where "wrdst" has wrapping enabled. */
	struct video_gfx const *out = self->vbt3_wrdst;
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = size_x;
	video_dim_t yinb = size_y;
	if (out->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_coord_t cxend;
		out_x = wrap(out_x, out->vx_hdr.vxh_cxsiz);
		if (size_x > out->vx_hdr.vxh_cxsiz)
			size_x = out->vx_hdr.vxh_cxsiz;
		cxend = (video_coord_t)out_x + size_x;
		if (OVERFLOW_USUB(cxend, out->vx_hdr.vxh_cxsiz, &xwrap)) {
			xwrap = 0;
		} else {
			xinb = out->vx_hdr.vxh_cxsiz - (video_coord_t)out_x;
		}
	}
	if (out->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_coord_t cyend;
		out_y = wrap(out_y, out->vx_hdr.vxh_cysiz);
		if (size_y > out->vx_hdr.vxh_cysiz)
			size_y = out->vx_hdr.vxh_cysiz;
		cyend = (video_coord_t)out_y + size_y;
		if (OVERFLOW_USUB(cyend, out->vx_hdr.vxh_cysiz, &ywrap)) {
			ywrap = 0;
		} else {
			yinb = out->vx_hdr.vxh_cysiz - (video_coord_t)out_y;
		}
	}
	if (xwrap && ywrap) /* Must do a partial fill at the top-left */
		LOCAL_libvideo_swblitter_blit_rdwrap1(self, 0, 0, dst_x, dst_y, src_x + xinb, src_y + yinb, xwrap, ywrap);
	if (xwrap) /* Must do a partial fill at the left */
		LOCAL_libvideo_swblitter_blit_rdwrap1(self, 0, out_y, dst_x, dst_y, src_x + xinb, src_y, xwrap, size_y);
	if (ywrap) /* Must do a partial fill at the top */
		LOCAL_libvideo_swblitter_blit_rdwrap1(self, out_x, 0, dst_x, dst_y, src_x, src_y + yinb, size_x, ywrap);
	LOCAL_libvideo_swblitter_blit_rdwrap1(self, out_x, out_y, dst_x, dst_y, src_x, src_y, xinb, yinb);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_swblitter_stretch_wrap1(LOCAL_struct_video_blitter const *__restrict self,
                                       video_offset_t out_x, video_offset_t out_y,
                                       video_offset_t dst_x, video_offset_t dst_y,
                                       video_dim_t dst_size_x, video_dim_t dst_size_y,
                                       video_offset_t src_x, video_offset_t src_y,
                                       video_dim_t src_size_x, video_dim_t src_size_y) {
	/* Handle the case where "wrdst" has wrapping enabled. */
	struct video_gfx const *out = self->vbt3_wrdst;
#define xout2src(x) ((video_coord_t)(((uint64_t)(x) * src_size_x) / dst_size_x))
#define yout2src(y) ((video_coord_t)(((uint64_t)(y) * src_size_y) / dst_size_y))
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = dst_size_x;
	video_dim_t yinb = dst_size_y;
	if (out->vx_flags & VIDEO_GFX_F_XWRAP) {
		video_coord_t cxend;
		out_x = wrap(out_x, out->vx_hdr.vxh_cxsiz);
		if (dst_size_x > out->vx_hdr.vxh_cxsiz) {
			src_size_x = xout2src(out->vx_hdr.vxh_cxsiz);
			dst_size_x = out->vx_hdr.vxh_cxsiz;
		}
		cxend = (video_coord_t)out_x + dst_size_x;
		if (OVERFLOW_USUB(cxend, out->vx_hdr.vxh_cxsiz, &xwrap)) {
			xwrap = 0;
		} else {
			xinb = out->vx_hdr.vxh_cxsiz - (video_coord_t)out_x;
		}
	}
	if (out->vx_flags & VIDEO_GFX_F_YWRAP) {
		video_coord_t cyend;
		out_y = wrap(out_y, out->vx_hdr.vxh_cysiz);
		if (dst_size_y > out->vx_hdr.vxh_cysiz) {
			src_size_y = yout2src(out->vx_hdr.vxh_cysiz);
			dst_size_y = out->vx_hdr.vxh_cysiz;
		}
		cyend = (video_coord_t)out_y + dst_size_y;
		if (OVERFLOW_USUB(cyend, out->vx_hdr.vxh_cysiz, &ywrap)) {
			ywrap = 0;
		} else {
			yinb = out->vx_hdr.vxh_cysiz - (video_coord_t)out_y;
		}
	}

	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		size_t chunk_src_x      = xout2src(xinb);
		size_t chunk_src_y      = yout2src(yinb);
		size_t chunk_src_size_x = xout2src(xwrap);
		size_t chunk_src_size_y = yout2src(ywrap);
		LOCAL_libvideo_swblitter_stretch_wrap(self, 0, 0,
		                                      dst_x, dst_y, xwrap, ywrap,
		                                      src_x + chunk_src_x, src_y + chunk_src_y,
		                                      chunk_src_size_x, chunk_src_size_y);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		size_t chunk_src_x      = xout2src(xinb);
		size_t chunk_src_size_x = xout2src(xwrap);
		LOCAL_libvideo_swblitter_stretch_wrap(self, 0, out_y,
		                                      dst_x, dst_y, xwrap, dst_size_y,
		                                      src_x + chunk_src_x, src_y,
		                                      chunk_src_size_x, src_size_y);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		size_t chunk_src_y      = yout2src(yinb);
		size_t chunk_src_size_y = yout2src(ywrap);
		LOCAL_libvideo_swblitter_stretch_wrap(self, out_x, 0,
		                                      dst_x, dst_y, dst_size_x, ywrap,
		                                      src_x, src_y + chunk_src_y,
		                                      src_size_x, chunk_src_size_y);
	}
	LOCAL_libvideo_swblitter_stretch_wrap(self, out_x, out_y,
	                                      dst_x, dst_y, dst_size_x, dst_size_y,
	                                      src_x, src_y, src_size_x, src_size_y);
#undef LOCAL_next
#undef xout2src
#undef yout2src
}
#endif /* LOCAL_USE_SWBLITTER3 */




/************************************************************************/
/* GENERIC BLIT OPERATORS                                               */
/************************************************************************/

#undef libvideo_swblitter_ops
#undef libvideo_swblitter_ops_imatrix
#undef libvideo_swblitter_ops_rdwrap
#undef libvideo_swblitter_ops_rdwrap_imatrix
#undef libvideo_swblitter_ops_wrap
#undef libvideo_swblitter_ops_wrap_imatrix
#undef libvideo_swblitter3_ops
#undef libvideo_swblitter3_ops_imatrix
#undef libvideo_swblitter3_ops_rdwrap
#undef libvideo_swblitter3_ops_rdwrap_imatrix
#undef libvideo_swblitter3_ops_wrap
#undef libvideo_swblitter3_ops_wrap_imatrix
#undef libvideo_swblitter3_ops_rdwrap1
#undef libvideo_swblitter3_ops_rdwrap1_imatrix
#undef libvideo_swblitter3_ops_wrap1
#undef libvideo_swblitter3_ops_wrap1_imatrix

#ifdef LOCAL_USE_SWBLITTER3
#define LOCAL_struct_video_blitter_ops        struct video_blitter3_ops
#define LOCAL_libvideo_swblitter_ops          LOCAL_FUNC(libvideo_swblitter3_ops)
#define LOCAL_libvideo_swblitter_ops_rdwrap   LOCAL_FUNC(libvideo_swblitter3_ops_rdwrap)
#define LOCAL_libvideo_swblitter_ops_wrap     LOCAL_FUNC(libvideo_swblitter3_ops_wrap)
#define LOCAL_libvideo_swblitter_ops_rdwrap1  LOCAL_FUNC(libvideo_swblitter3_ops_rdwrap1)
#define LOCAL_libvideo_swblitter_ops_wrap1    LOCAL_FUNC(libvideo_swblitter3_ops_wrap1)
#define LOCAL__libvideo_swblitter_ops         LOCAL_FUNC(_libvideo_swblitter3_ops)
#define LOCAL__libvideo_swblitter_ops_rdwrap  LOCAL_FUNC(_libvideo_swblitter3_ops_rdwrap)
#define LOCAL__libvideo_swblitter_ops_wrap    LOCAL_FUNC(_libvideo_swblitter3_ops_wrap)
#define LOCAL__libvideo_swblitter_ops_rdwrap1 LOCAL_FUNC(_libvideo_swblitter3_ops_rdwrap1)
#define LOCAL__libvideo_swblitter_ops_wrap1   LOCAL_FUNC(_libvideo_swblitter3_ops_wrap1)
#define LOCAL_vbto_bitblit                    vbt3o_bitblit
#define LOCAL_vbto_stretch                    vbt3o_stretch
#else /* LOCAL_USE_SWBLITTER3 */
#define LOCAL_struct_video_blitter_ops       struct video_blitter_ops
#define LOCAL_libvideo_swblitter_ops         LOCAL_FUNC(libvideo_swblitter_ops)
#define LOCAL_libvideo_swblitter_ops_rdwrap  LOCAL_FUNC(libvideo_swblitter_ops_rdwrap)
#define LOCAL_libvideo_swblitter_ops_wrap    LOCAL_FUNC(libvideo_swblitter_ops_wrap)
#define LOCAL__libvideo_swblitter_ops        LOCAL_FUNC(_libvideo_swblitter_ops)
#define LOCAL__libvideo_swblitter_ops_rdwrap LOCAL_FUNC(_libvideo_swblitter_ops_rdwrap)
#define LOCAL__libvideo_swblitter_ops_wrap   LOCAL_FUNC(_libvideo_swblitter_ops_wrap)
#define LOCAL_vbto_bitblit                   vbto_bitblit
#define LOCAL_vbto_stretch                   vbto_stretch
#endif /* !LOCAL_USE_SWBLITTER3 */

PRIVATE LOCAL_struct_video_blitter_ops LOCAL_libvideo_swblitter_ops = {};
INTERN ATTR_RETNONNULL WUNUSED LOCAL_struct_video_blitter_ops const *CC
LOCAL__libvideo_swblitter_ops(void) {
	if unlikely(!LOCAL_libvideo_swblitter_ops.LOCAL_vbto_bitblit) {
		LOCAL_libvideo_swblitter_ops.LOCAL_vbto_stretch = &LOCAL_libvideo_swblitter_stretch;
		COMPILER_WRITE_BARRIER();
		LOCAL_libvideo_swblitter_ops.LOCAL_vbto_bitblit = &LOCAL_libvideo_swblitter_blit;
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_libvideo_swblitter_ops;
}

PRIVATE LOCAL_struct_video_blitter_ops LOCAL_libvideo_swblitter_ops_rdwrap = {};
INTERN ATTR_RETNONNULL WUNUSED LOCAL_struct_video_blitter_ops const *CC
LOCAL__libvideo_swblitter_ops_rdwrap(void) {
	if unlikely(!LOCAL_libvideo_swblitter_ops_rdwrap.LOCAL_vbto_bitblit) {
		LOCAL_libvideo_swblitter_ops_rdwrap.LOCAL_vbto_stretch = &LOCAL_libvideo_swblitter_stretch_rdwrap;
		COMPILER_WRITE_BARRIER();
		LOCAL_libvideo_swblitter_ops_rdwrap.LOCAL_vbto_bitblit = &LOCAL_libvideo_swblitter_blit_rdwrap;
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_libvideo_swblitter_ops_rdwrap;
}

PRIVATE LOCAL_struct_video_blitter_ops LOCAL_libvideo_swblitter_ops_wrap = {};
INTERN ATTR_RETNONNULL WUNUSED LOCAL_struct_video_blitter_ops const *CC
LOCAL__libvideo_swblitter_ops_wrap(void) {
	if unlikely(!LOCAL_libvideo_swblitter_ops_wrap.LOCAL_vbto_bitblit) {
		LOCAL_libvideo_swblitter_ops_wrap.LOCAL_vbto_stretch = &LOCAL_libvideo_swblitter_stretch_wrap;
		COMPILER_WRITE_BARRIER();
		LOCAL_libvideo_swblitter_ops_wrap.LOCAL_vbto_bitblit = &LOCAL_libvideo_swblitter_blit_wrap;
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_libvideo_swblitter_ops_wrap;
}

#ifdef LOCAL__libvideo_swblitter_ops_rdwrap1
PRIVATE LOCAL_struct_video_blitter_ops LOCAL_libvideo_swblitter_ops_rdwrap1 = {};
INTERN ATTR_RETNONNULL WUNUSED LOCAL_struct_video_blitter_ops const *CC
LOCAL__libvideo_swblitter_ops_rdwrap1(void) {
	if unlikely(!LOCAL_libvideo_swblitter_ops_rdwrap1.LOCAL_vbto_bitblit) {
		LOCAL_libvideo_swblitter_ops_rdwrap1.LOCAL_vbto_stretch = &LOCAL_libvideo_swblitter_stretch_rdwrap1;
		COMPILER_WRITE_BARRIER();
		LOCAL_libvideo_swblitter_ops_rdwrap1.LOCAL_vbto_bitblit = &LOCAL_libvideo_swblitter_blit_rdwrap1;
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_libvideo_swblitter_ops_rdwrap1;
}
#endif /* LOCAL__libvideo_swblitter_ops_rdwrap1 */

#ifdef LOCAL__libvideo_swblitter_ops_wrap1
PRIVATE LOCAL_struct_video_blitter_ops LOCAL_libvideo_swblitter_ops_wrap1 = {};
INTERN ATTR_RETNONNULL WUNUSED LOCAL_struct_video_blitter_ops const *CC
LOCAL__libvideo_swblitter_ops_wrap1(void) {
	if unlikely(!LOCAL_libvideo_swblitter_ops_wrap1.LOCAL_vbto_bitblit) {
		LOCAL_libvideo_swblitter_ops_wrap1.LOCAL_vbto_stretch = &LOCAL_libvideo_swblitter_stretch_wrap1;
		COMPILER_WRITE_BARRIER();
		LOCAL_libvideo_swblitter_ops_wrap1.LOCAL_vbto_bitblit = &LOCAL_libvideo_swblitter_blit_wrap1;
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_libvideo_swblitter_ops_wrap1;
}
#endif /* LOCAL__libvideo_swblitter_ops_wrap1 */

#undef LOCAL_vbto_bitblit
#undef LOCAL_vbto_stretch
#undef LOCAL_struct_video_blitter_ops
#undef LOCAL_libvideo_swblitter_ops
#undef LOCAL_libvideo_swblitter_ops_rdwrap
#undef LOCAL_libvideo_swblitter_ops_wrap
#undef LOCAL_libvideo_swblitter_ops_rdwrap1
#undef LOCAL_libvideo_swblitter_ops_wrap1
#undef LOCAL__libvideo_swblitter_ops
#undef LOCAL__libvideo_swblitter_ops_rdwrap
#undef LOCAL__libvideo_swblitter_ops_wrap
#undef LOCAL__libvideo_swblitter_ops_rdwrap1
#undef LOCAL__libvideo_swblitter_ops_wrap1

#define libvideo_swblitter_ops                  (*_libvideo_swblitter_ops())                  /* Support: - */
#define libvideo_swblitter_ops_imatrix          (*_libvideo_swblitter_ops_imatrix())          /* Support: src+dst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_swblitter_ops_rdwrap           (*_libvideo_swblitter_ops_rdwrap())           /* Support: src:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_swblitter_ops_rdwrap_imatrix   (*_libvideo_swblitter_ops_rdwrap_imatrix())   /* Support: src:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+dst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_swblitter_ops_wrap             (*_libvideo_swblitter_ops_wrap())             /* Support: src+dst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_swblitter_ops_wrap_imatrix     (*_libvideo_swblitter_ops_wrap_imatrix())     /* Support: src+dst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+dst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_swblitter3_ops                 (*_libvideo_swblitter3_ops())                 /* Support: - */
#define libvideo_swblitter3_ops_imatrix         (*_libvideo_swblitter3_ops_imatrix())         /* Support: src+wrdst+rddst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_swblitter3_ops_rdwrap          (*_libvideo_swblitter3_ops_rdwrap())          /* Support: src:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_swblitter3_ops_rdwrap_imatrix  (*_libvideo_swblitter3_ops_rdwrap_imatrix())  /* Support: src:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+wrdst+rddst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_swblitter3_ops_wrap            (*_libvideo_swblitter3_ops_wrap())            /* Support: src+wrdst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_swblitter3_ops_wrap_imatrix    (*_libvideo_swblitter3_ops_wrap_imatrix())    /* Support: src+wrdst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+wrdst+rddst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_swblitter3_ops_rdwrap1         (*_libvideo_swblitter3_ops_rdwrap1())         /* Support: src+rddst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_swblitter3_ops_rdwrap1_imatrix (*_libvideo_swblitter3_ops_rdwrap1_imatrix()) /* Support: src+rddst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+wrdst+rddst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_swblitter3_ops_wrap1           (*_libvideo_swblitter3_ops_wrap1())           /* Support: src+wrdst+rddst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_swblitter3_ops_wrap1_imatrix   (*_libvideo_swblitter3_ops_wrap1_imatrix())   /* Support: src+wrdst+rddst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+wrdst+rddst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */

#undef LOCAL_libvideo_swblitter_stretch_wrap1
#undef LOCAL_libvideo_swblitter_stretch_rdwrap1
#undef LOCAL_libvideo_swblitter_stretch_wrap
#undef LOCAL_libvideo_swblitter_stretch_rdwrap
#undef LOCAL_libvideo_swblitter_stretch
#undef LOCAL_libvideo_swblitter_blit_wrap1
#undef LOCAL_libvideo_swblitter_blit_rdwrap1
#undef LOCAL_libvideo_swblitter_blit_wrap
#undef LOCAL_libvideo_swblitter_blit_rdwrap
#undef LOCAL_libvideo_swblitter_blit
#undef LOCAL_struct_video_blitter
#undef LOCAL_FUNC
#undef LOCAL_USE_IMATRIX
#undef LOCAL_USE_SWBLITTER3

DECL_END

#undef DEFINE_libvideo_swblitter_blit_wrap
#undef DEFINE_libvideo_swblitter_blit_wrap_imatrix
#undef DEFINE_libvideo_swblitter3_blit_wrap
#undef DEFINE_libvideo_swblitter3_blit_wrap_imatrix
