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
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#ifdef __INTELLISENSE__
//#define DEFINE_libvideo_blitter_generic_blit_wrap
#define DEFINE_libvideo_blitter_generic_blit_wrap_imatrix
#endif /* __INTELLISENSE__ */

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <stddef.h>
#include <stdint.h>

#include <libvideo/codec/types.h>
#include <libvideo/gfx/gfx.h>
/**/

#include "../gfx-utils.h"
#include "../gfx.h"

#if (defined(DEFINE_libvideo_blitter_generic_blit_wrap) + \
     defined(DEFINE_libvideo_blitter_generic_blit_wrap_imatrix)) != 1
#error "Must #define exactly one of these"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_libvideo_blitter_generic_blit_wrap_imatrix
#define LOCAL_USE_IMATRIX
#endif /* DEFINE_libvideo_blitter_generic_blit_wrap_imatrix */

#ifdef LOCAL_USE_IMATRIX
#define LOCAL_FUNC(x) x##_imatrix
#else /* LOCAL_USE_IMATRIX */
#define LOCAL_FUNC(x) x
#endif /* !LOCAL_USE_IMATRIX */

#define LOCAL_libvideo_blitter_generic_blit           LOCAL_FUNC(libvideo_blitter_generic_blit)
#define LOCAL_libvideo_blitter_generic_blit_rdwrap    LOCAL_FUNC(libvideo_blitter_generic_blit_rdwrap)
#define LOCAL_libvideo_blitter_generic_blit_wrap      LOCAL_FUNC(libvideo_blitter_generic_blit_wrap)
#define LOCAL_libvideo_blitter_generic_stretch        LOCAL_FUNC(libvideo_blitter_generic_stretch)
#define LOCAL_libvideo_blitter_generic_stretch_rdwrap LOCAL_FUNC(libvideo_blitter_generic_stretch_rdwrap)
#define LOCAL_libvideo_blitter_generic_stretch_wrap   LOCAL_FUNC(libvideo_blitter_generic_stretch_wrap)



INTERN ATTR_IN(1) void CC
LOCAL_libvideo_blitter_generic_blit_rdwrap(struct video_blitter const *__restrict self,
                                           video_offset_t dst_x, video_offset_t dst_y,
                                           video_offset_t src_x, video_offset_t src_y,
                                           video_dim_t size_x, video_dim_t size_y) {
	/* Handle the case where "src" has read-wrapping enabled. */
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
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
			dst_x = 0;
			src_x += delta;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, size_x, &dst_endx) ||
		            dst_endx > dst->vx_hdr.vxh_cxsiz) {
			if unlikely((video_coord_t)dst_x >= dst->vx_hdr.vxh_cxsiz)
				return;
			size_x = dst->vx_hdr.vxh_cxsiz - (video_coord_t)dst_x;
		}
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
			dst_y = 0;
			src_y += delta;
		}
		if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, size_y, &dst_endy) ||
		            dst_endy > dst->vx_hdr.vxh_cysiz) {
			if unlikely((video_coord_t)dst_y >= dst->vx_hdr.vxh_cysiz)
				return;
			size_y = dst->vx_hdr.vxh_cysiz - (video_coord_t)dst_y;
		}
		src_y     = wrap(src_y, src->vx_hdr.vxh_cysiz);
		src_maxsy = src->vx_hdr.vxh_cysiz - (video_coord_t)src_y;
	}

	if ((size_x > src_maxsx) && (size_y > src_maxsy)) {
		video_dim_t iter_size_x;
		video_dim_t iter_size_y;
		video_dim_t iter_dst_x;
		video_dim_t iter_dst_y;
		/* Must render the source graphic multiple times */

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

		iter_size_y = size_y;
		iter_dst_y  = dst_y;

		/* Deal with unaligned tiles near the top */
		if unlikely(src_maxsy < src->vx_hdr.vxh_cysiz) {
			/* Top-left corner */
			LOCAL_libvideo_blitter_generic_blit(self, dst_x, iter_dst_y, src_x, src_y,
			                                    src_maxsx, src_maxsy);

			/* Top bar */
			iter_size_x = size_x - src_maxsx;
			iter_dst_x = dst_x + src_maxsx;
			while (iter_size_x > src->vx_hdr.vxh_cxsiz) {
				LOCAL_libvideo_blitter_generic_blit(self, iter_dst_x, iter_dst_y, 0, src_y,
				                                    src->vx_hdr.vxh_cxsiz, src_maxsy);
				iter_size_x -= src->vx_hdr.vxh_cxsiz;
				iter_dst_x += src->vx_hdr.vxh_cxsiz;
			}

			/* Top-right corner */
			LOCAL_libvideo_blitter_generic_blit(self, iter_dst_x, iter_dst_y, 0, src_y,
			                                    iter_size_x, src_maxsy);
			iter_size_y -= src_maxsy;
			iter_dst_y  += src_maxsy;
		}

		/* Iterate whole rows */
		while (iter_size_y >= src->vx_hdr.vxh_cysiz) {
			/* Left side */
			LOCAL_libvideo_blitter_generic_blit(self, dst_x, iter_dst_y, src_x, 0,
			                                    src_maxsx, src->vx_hdr.vxh_cysiz);

			/* Center */
			iter_size_x = size_x - src_maxsx;
			iter_dst_x = dst_x + src_maxsx;
			while (iter_size_x > src->vx_hdr.vxh_cxsiz) {
				LOCAL_libvideo_blitter_generic_blit(self, iter_dst_x, iter_dst_y, 0, 0,
				                                    src->vx_hdr.vxh_cxsiz, src->vx_hdr.vxh_cysiz);
				iter_size_x -= src->vx_hdr.vxh_cxsiz;
				iter_dst_x += src->vx_hdr.vxh_cxsiz;
			}

			/* Right side */
			LOCAL_libvideo_blitter_generic_blit(self, iter_dst_x, iter_dst_y, 0, 0,
			                                    iter_size_x, src->vx_hdr.vxh_cysiz);

			iter_size_y -= src->vx_hdr.vxh_cysiz;
			iter_dst_y += src->vx_hdr.vxh_cysiz;
		}

		if likely(!iter_size_y)
			return;

		/* Bottom-left corner */
		LOCAL_libvideo_blitter_generic_blit(self, dst_x, iter_dst_y, src_x, 0,
		                                    src_maxsx, iter_size_y);

		/* Bottom bar */
		iter_size_x = size_x - src_maxsx;
		iter_dst_x = dst_x + src_maxsx;
		while (iter_size_x > src->vx_hdr.vxh_cxsiz) {
			LOCAL_libvideo_blitter_generic_blit(self, iter_dst_x, iter_dst_y, 0, 0,
			                                    src->vx_hdr.vxh_cxsiz, iter_size_y);
			iter_size_x -= src->vx_hdr.vxh_cxsiz;
			iter_dst_x += src->vx_hdr.vxh_cxsiz;
		}

		/* Bottom-right corner (render via fallthru) */
		dst_x  = iter_dst_x;
		dst_y  = iter_dst_y;
		src_x  = 0;
		src_y  = 0;
		size_x = iter_size_x;
		size_y = iter_size_y;
	} else if (size_x > src_maxsx) {
		LOCAL_libvideo_blitter_generic_blit(self, dst_x, dst_y, src_x, src_y,
		                                    src_maxsx, size_y);
		size_x -= src_maxsx;
		dst_x += src_maxsx;
		while (size_x > src->vx_hdr.vxh_cxsiz) {
			LOCAL_libvideo_blitter_generic_blit(self, dst_x, dst_y, 0, src_y,
			                                    src->vx_hdr.vxh_cxsiz, size_y);
			size_x -= src->vx_hdr.vxh_cxsiz;
			dst_x += src->vx_hdr.vxh_cxsiz;
		}
		src_x = 0; /* Fallthru to render the last part */
	} else if (size_y > src_maxsy) {
		LOCAL_libvideo_blitter_generic_blit(self, dst_x, dst_y, src_x, src_y,
		                                    size_x, src_maxsy);
		size_y -= src_maxsy;
		dst_y += src_maxsy;
		while (size_y > src->vx_hdr.vxh_cysiz) {
			LOCAL_libvideo_blitter_generic_blit(self, dst_x, dst_y, src_x, 0,
			                                    size_x, src->vx_hdr.vxh_cysiz);
			size_y -= src->vx_hdr.vxh_cysiz;
			dst_y += src->vx_hdr.vxh_cysiz;
		}
		src_y = 0; /* Fallthru to render the last part */
	}

	LOCAL_libvideo_blitter_generic_blit(self, dst_x, dst_y, src_x, src_y, size_x, size_y);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_blitter_generic_stretch_rdwrap(struct video_blitter const *__restrict self,
                                              video_offset_t dst_x, video_offset_t dst_y,
                                              video_dim_t dst_size_x, video_dim_t dst_size_y,
                                              video_offset_t src_x, video_offset_t src_y,
                                              video_dim_t src_size_x, video_dim_t src_size_y) {
	/* Handle the case where "src" has read-wrapping enabled. */
#define xdst2src(x) ((video_coord_t)(((uint64_t)(x) * src_size_x) / dst_size_x))
#define ydst2src(y) ((video_coord_t)(((uint64_t)(y) * src_size_y) / dst_size_y))
#define xsrc2dst(x) ((video_coord_t)(((uint64_t)(x) * dst_size_x) / src_size_x))
#define ysrc2dst(y) ((video_coord_t)(((uint64_t)(y) * dst_size_y) / src_size_y))
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
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
		src_y     = wrap(src_y, src->vx_hdr.vxh_cysiz);
		src_maxsy = src->vx_hdr.vxh_cysiz - (video_coord_t)src_y;
	}

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

		/* Deal with unaligned tiles near the top */

		/* Top-left corner */
		LOCAL_libvideo_blitter_generic_stretch(self, dst_x, dst_y, firsttile_dst_size_x, firsttile_dst_size_y,
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
				LOCAL_libvideo_blitter_generic_stretch(self, iter_dst_x, dst_y, next_dst_x - iter_dst_x, firsttile_dst_size_y,
				                                       0, src_y, src->vx_hdr.vxh_cxsiz, src_maxsy);
				iter_dst_x = next_dst_x;
			}
			iter_src_size_x %= src->vx_hdr.vxh_cxsiz;
			iter_dst_size_x = lasttile_dst_size_x;
		}

		/* Top-right corner */
		LOCAL_libvideo_blitter_generic_stretch(self, iter_dst_x, dst_y, iter_dst_size_x, firsttile_dst_size_y,
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
				LOCAL_libvideo_blitter_generic_stretch(self, dst_x, iter_dst_y, firsttile_dst_size_x, tile_h,
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
						LOCAL_libvideo_blitter_generic_stretch(self, iter_dst_x, iter_dst_y, next_dst_x - iter_dst_x, tile_h,
						                                       0, 0, src->vx_hdr.vxh_cxsiz, src->vx_hdr.vxh_cysiz);
						iter_dst_x = next_dst_x;
					} while (++xwholetiles_i < xwholetiles_count);
					iter_src_size_x %= src->vx_hdr.vxh_cxsiz;
					iter_dst_size_x = lasttile_dst_size_x;
				}

				/* Right side */
				LOCAL_libvideo_blitter_generic_stretch(self, iter_dst_x, iter_dst_y, lasttile_dst_size_x, tile_h,
				                                       0, 0, iter_src_size_x, src->vx_hdr.vxh_cysiz);

				iter_dst_y = next_dst_y;
			}
			iter_src_size_y %= src->vx_hdr.vxh_cysiz;
			iter_dst_size_y = lasttile_dst_size_y;
		}
		if likely(!iter_src_size_y)
			return;

		/* Bottom-left corner */
		LOCAL_libvideo_blitter_generic_stretch(self, dst_x, iter_dst_y, firsttile_dst_size_x, iter_dst_size_y,
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
				LOCAL_libvideo_blitter_generic_stretch(self, iter_dst_x, iter_dst_y, next_dst_x - iter_dst_x, iter_dst_size_y,
				                                       0, 0, src->vx_hdr.vxh_cxsiz, iter_src_size_y);
				iter_dst_x = next_dst_x;
			}
			iter_src_size_x %= src->vx_hdr.vxh_cxsiz;
			iter_dst_size_x = lasttile_dst_size_x;
		}

		/* Bottom-right corner (render via fallthru) */
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
		LOCAL_libvideo_blitter_generic_stretch(self, dst_x, dst_y, firsttile_dst_size_x, dst_size_y,
		                                       src_x, src_y, src_maxsx, src_size_y);
		src_size_x -= src_maxsx;
		dst_x += firsttile_dst_size_x;
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
				LOCAL_libvideo_blitter_generic_stretch(self, dst_x, dst_y, next_dst_x - dst_x, dst_size_y,
				                                       0, src_y, src->vx_hdr.vxh_cxsiz, src_size_y);
				dst_x = next_dst_x;
			}
			src_size_x %= src->vx_hdr.vxh_cxsiz;
			dst_size_x = lasttile_dst_size_x;
		}
		src_x = 0; /* Fallthru to render the last part */
	} else if (src_size_y > src_maxsy) {
		video_dim_t firsttile_dst_size_y = ysrc2dst(src_maxsy);
		LOCAL_libvideo_blitter_generic_stretch(self, dst_x, dst_y, dst_size_x, firsttile_dst_size_y,
		                                       src_x, src_y, src_size_x, src_maxsy);
		src_size_y -= src_maxsy;
		dst_y += firsttile_dst_size_y;
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
				LOCAL_libvideo_blitter_generic_stretch(self, dst_x, dst_y, dst_size_x, next_dst_y - dst_y,
				                                       src_x, 0, src_size_x, src->vx_hdr.vxh_cysiz);
				dst_y = next_dst_y;
			}
			src_size_y %= src->vx_hdr.vxh_cysiz;
			dst_size_y = lasttile_dst_size_y;
		}
		src_y = 0; /* Fallthru to render the last part */
	}

	LOCAL_libvideo_blitter_generic_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                       src_x, src_y, src_size_x, src_size_y);
#undef xdst2src
#undef ydst2src
#undef xsrc2dst
#undef ysrc2dst
}



INTERN ATTR_IN(1) void CC
LOCAL_libvideo_blitter_generic_blit_wrap(struct video_blitter const *__restrict self,
                                         video_offset_t dst_x, video_offset_t dst_y,
                                         video_offset_t src_x, video_offset_t src_y,
                                         video_dim_t size_x, video_dim_t size_y) {
	/* Handle the case where "dst" has write-wrapping enabled. */
	struct video_gfx const *dst = self->vbt_dst;
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
	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		LOCAL_libvideo_blitter_generic_blit_rdwrap(self, 0, 0, src_x + xinb, src_y + yinb,
		                                           xwrap, ywrap);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		LOCAL_libvideo_blitter_generic_blit_rdwrap(self, 0, dst_y, src_x + xinb, src_y,
		                                           xwrap, size_y);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		LOCAL_libvideo_blitter_generic_blit_rdwrap(self, dst_x, 0, src_x, src_y + yinb,
		                                           size_x, ywrap);
	}
	LOCAL_libvideo_blitter_generic_blit_rdwrap(self, dst_x, dst_y, src_x, src_y,
	                                           xinb, yinb);
}

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_blitter_generic_stretch_wrap(struct video_blitter const *__restrict self,
                                            video_offset_t dst_x, video_offset_t dst_y,
                                            video_dim_t dst_size_x, video_dim_t dst_size_y,
                                            video_offset_t src_x, video_offset_t src_y,
                                            video_dim_t src_size_x, video_dim_t src_size_y) {
	/* Handle the case where "dst" has write-wrapping enabled. */
	struct video_gfx const *dst = self->vbt_dst;
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

	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		size_t chunk_src_x      = xdst2src(xinb);
		size_t chunk_src_y      = ydst2src(yinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		size_t chunk_src_size_y = ydst2src(ywrap);
		LOCAL_libvideo_blitter_generic_stretch_rdwrap(self, 0, 0, xwrap, ywrap,
		                                              src_x + chunk_src_x, src_y + chunk_src_y,
		                                              chunk_src_size_x, chunk_src_size_y);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		size_t chunk_src_x      = xdst2src(xinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		LOCAL_libvideo_blitter_generic_stretch_rdwrap(self, 0, dst_y, xwrap, dst_size_y,
		                                              src_x + chunk_src_x, src_y,
		                                              chunk_src_size_x, src_size_y);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		size_t chunk_src_y      = ydst2src(yinb);
		size_t chunk_src_size_y = ydst2src(ywrap);
		LOCAL_libvideo_blitter_generic_stretch_rdwrap(self, dst_x, 0, dst_size_x, ywrap,
		                                              src_x, src_y + chunk_src_y,
		                                              src_size_x, chunk_src_size_y);
	}
	LOCAL_libvideo_blitter_generic_stretch_rdwrap(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                              src_x, src_y, src_size_x, src_size_y);
#undef xdst2src
#undef ydst2src
}


/************************************************************************/
/* GENERIC BLIT OPERATORS                                               */
/************************************************************************/

#undef libvideo_blit_generic_ops
#undef libvideo_blit_generic_ops_imatrix
#undef libvideo_blit_generic_ops_rdwrap
#undef libvideo_blit_generic_ops_rdwrap_imatrix
#undef libvideo_blit_generic_ops_wrap
#undef libvideo_blit_generic_ops_wrap_imatrix
PRIVATE struct video_blitter_ops LOCAL_FUNC(libvideo_blit_generic_ops) = {};
PRIVATE struct video_blitter_ops LOCAL_FUNC(libvideo_blit_generic_ops_rdwrap) = {};
PRIVATE struct video_blitter_ops LOCAL_FUNC(libvideo_blit_generic_ops_wrap) = {};

INTERN ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC
LOCAL_FUNC(_libvideo_blit_generic_ops)(void) {
	if unlikely(!LOCAL_FUNC(libvideo_blit_generic_ops).vbto_bitblit) {
		LOCAL_FUNC(libvideo_blit_generic_ops).vbto_stretch = &LOCAL_FUNC(libvideo_blitter_generic_stretch);
		COMPILER_WRITE_BARRIER();
		LOCAL_FUNC(libvideo_blit_generic_ops).vbto_bitblit = &LOCAL_FUNC(libvideo_blitter_generic_blit);
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_FUNC(libvideo_blit_generic_ops);
}

INTERN ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC
LOCAL_FUNC(_libvideo_blit_generic_ops_rdwrap)(void) {
	if unlikely(!LOCAL_FUNC(libvideo_blit_generic_ops_rdwrap).vbto_bitblit) {
		LOCAL_FUNC(libvideo_blit_generic_ops_rdwrap).vbto_stretch = &LOCAL_FUNC(libvideo_blitter_generic_stretch_rdwrap);
		COMPILER_WRITE_BARRIER();
		LOCAL_FUNC(libvideo_blit_generic_ops_rdwrap).vbto_bitblit = &LOCAL_FUNC(libvideo_blitter_generic_blit_rdwrap);
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_FUNC(libvideo_blit_generic_ops_rdwrap);
}

INTERN ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC
LOCAL_FUNC(_libvideo_blit_generic_ops_wrap)(void) {
	if unlikely(!LOCAL_FUNC(libvideo_blit_generic_ops_wrap).vbto_bitblit) {
		LOCAL_FUNC(libvideo_blit_generic_ops_wrap).vbto_stretch = &LOCAL_FUNC(libvideo_blitter_generic_stretch_wrap);
		COMPILER_WRITE_BARRIER();
		LOCAL_FUNC(libvideo_blit_generic_ops_wrap).vbto_bitblit = &LOCAL_FUNC(libvideo_blitter_generic_blit_wrap);
		COMPILER_WRITE_BARRIER();
	}
	return &LOCAL_FUNC(libvideo_blit_generic_ops_wrap);
}
#define libvideo_blit_generic_ops                (*_libvideo_blit_generic_ops())                /* Support: - */
#define libvideo_blit_generic_ops_imatrix        (*_libvideo_blit_generic_ops_imatrix())        /* Support: src+dst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_blit_generic_ops_rdwrap         (*_libvideo_blit_generic_ops_rdwrap())         /* Support: src:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_blit_generic_ops_rdwrap_imatrix (*_libvideo_blit_generic_ops_rdwrap_imatrix()) /* Support: src:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+dst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */
#define libvideo_blit_generic_ops_wrap           (*_libvideo_blit_generic_ops_wrap())           /* Support: src+dst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP */
#define libvideo_blit_generic_ops_wrap_imatrix   (*_libvideo_blit_generic_ops_wrap_imatrix())   /* Support: src+dst:VIDEO_GFX_F_XWRAP|VIDEO_GFX_F_YWRAP, src+dst:VIDEO_GFX_F_XMIRROR|VIDEO_GFX_F_YMIRROR|VIDEO_GFX_F_XYSWAP */

#undef LOCAL_libvideo_blitter_generic_stretch_wrap
#undef LOCAL_libvideo_blitter_generic_stretch_rdwrap
#undef LOCAL_libvideo_blitter_generic_stretch
#undef LOCAL_libvideo_blitter_generic_blit_wrap
#undef LOCAL_libvideo_blitter_generic_blit_rdwrap
#undef LOCAL_libvideo_blitter_generic_blit
#undef LOCAL_FUNC
#undef LOCAL_USE_IMATRIX

DECL_END

#undef DEFINE_libvideo_blitter_generic_blit_wrap
#undef DEFINE_libvideo_blitter_generic_blit_wrap_imatrix
