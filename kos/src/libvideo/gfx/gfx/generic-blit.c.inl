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
#ifdef __INTELLISENSE__
#include "../gfx.c"
//#define DEFINE_libvideo_gfx_generic_blit__and__stretch
#define DEFINE_libvideo_gfx_generic_bitblit__and__bitstretch
#endif /* __INTELLISENSE__ */

#include <sys/param.h>

#if (defined(DEFINE_libvideo_gfx_generic_blit__and__stretch) + \
     defined(DEFINE_libvideo_gfx_generic_bitblit__and__bitstretch)) != 1
#error "Must #define exactly one of these macros"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_libvideo_gfx_generic_blit__and__stretch
#define LOCAL_libvideo_gfx_generic_blit           libvideo_gfx_generic_blit
#define LOCAL_libvideo_gfx_generic_blit_rdwrap    libvideo_gfx_generic_blit_rdwrap
#define LOCAL_libvideo_gfx_generic_blit_wrap      libvideo_gfx_generic_blit_wrap
#define LOCAL_libvideo_gfx_generic_stretch        libvideo_gfx_generic_stretch
#define LOCAL_libvideo_gfx_generic_stretch_rdwrap libvideo_gfx_generic_stretch_rdwrap
#define LOCAL_libvideo_gfx_generic_stretch_wrap   libvideo_gfx_generic_stretch_wrap
#define LOCAL_vbxo_blit                           vbxo_blit
#define LOCAL_vbxo_stretch                        vbxo_stretch
#elif defined(DEFINE_libvideo_gfx_generic_bitblit__and__bitstretch)
#define LOCAL_libvideo_gfx_generic_blit           libvideo_gfx_generic_bitblit
#define LOCAL_libvideo_gfx_generic_blit_rdwrap    libvideo_gfx_generic_bitblit_rdwrap
#define LOCAL_libvideo_gfx_generic_blit_wrap      libvideo_gfx_generic_bitblit_wrap
#define LOCAL_libvideo_gfx_generic_stretch        libvideo_gfx_generic_bitstretch
#define LOCAL_libvideo_gfx_generic_stretch_rdwrap libvideo_gfx_generic_bitstretch_rdwrap
#define LOCAL_libvideo_gfx_generic_stretch_wrap   libvideo_gfx_generic_bitstretch_wrap
#define LOCAL_vbxo_blit                           vbxo_bitblit
#define LOCAL_vbxo_stretch                        vbxo_bitstretch
#define LOCAL_HAVE_BITMASK
#endif /* ... */

#ifdef LOCAL_HAVE_BITMASK
#define LOCAL_BITMASK__PARAMS , struct video_bitmask const *__restrict bm
#define LOCAL_BITMASK__ARGS   , bm
#else /* LOCAL_HAVE_BITMASK */
#define LOCAL_BITMASK__PARAMS /* nothing */
#define LOCAL_BITMASK__ARGS   /* nothing */
#endif /* !LOCAL_HAVE_BITMASK */


INTERN NONNULL((1)) void CC
LOCAL_libvideo_gfx_generic_blit(struct video_blit *__restrict self,
                                video_offset_t dst_x, video_offset_t dst_y,
                                video_offset_t src_x, video_offset_t src_y,
                                video_dim_t size_x, video_dim_t size_y
                                LOCAL_BITMASK__PARAMS) {
	struct video_gfx *dst = self->vb_dst;
	struct video_gfx const *src = self->vb_src;
	video_coord_t temp;
	if (!size_x || !size_y)
		return;
	dst_x += dst->vx_cxoff;
	dst_y += dst->vx_cyoff;
	src_x += src->vx_cxoff;
	src_y += src->vx_cyoff;
	if unlikely(dst_x < (video_offset_t)dst->vx_bxmin) {
		dst_x = (video_offset_t)(dst->vx_bxmin - (video_coord_t)dst_x);
		if unlikely((video_coord_t)dst_x >= size_x)
			return;
		src_x += (video_coord_t)dst_x;
		size_x -= (video_coord_t)dst_x;
		dst_x = (video_offset_t)dst->vx_bxmin;
	}
	if unlikely(dst_y < (video_offset_t)dst->vx_bymin) {
		dst_y = (video_offset_t)(dst->vx_bymin - (video_coord_t)dst_y);
		if unlikely((video_coord_t)dst_y >= size_y)
			return;
		src_y += (video_coord_t)dst_y;
		size_y -= (video_coord_t)dst_y;
		dst_y = (video_offset_t)dst->vx_bymin;
	}
	if unlikely(src_x < (video_offset_t)src->vx_bxmin) {
		src_x = (video_offset_t)(src->vx_bxmin - (video_coord_t)src_x);
		if unlikely((video_coord_t)src_x >= size_x)
			return;
		dst_x += (video_coord_t)src_x;
		size_x -= (video_coord_t)src_x;
		src_x = (video_offset_t)src->vx_bxmin;
	}
	if unlikely(src_y < (video_offset_t)src->vx_bymin) {
		src_y = (video_offset_t)(src->vx_bymin - (video_coord_t)src_y);
		if unlikely((video_coord_t)src_y >= size_y)
			return;
		dst_y += (video_coord_t)src_y;
		size_y -= (video_coord_t)src_y;
		src_y = (video_offset_t)src->vx_bymin;
	}

	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, size_x, &temp) || temp > dst->vx_bxend) {
		if unlikely((video_coord_t)dst_x >= dst->vx_bxend)
			return;
		size_x = dst->vx_bxend - (video_coord_t)dst_x;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, size_y, &temp) || temp > dst->vx_byend) {
		if unlikely((video_coord_t)dst_y >= dst->vx_byend)
			return;
		size_y = dst->vx_byend - (video_coord_t)dst_y;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)src_x, size_x, &temp) || temp > src->vx_bxend) {
		if unlikely((video_coord_t)src_x >= src->vx_bxend)
			return;
		size_x = src->vx_bxend - (video_coord_t)src_x;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)src_y, size_y, &temp) || temp > src->vx_byend) {
		if unlikely((video_coord_t)src_y >= src->vx_byend)
			return;
		size_y = src->vx_byend - (video_coord_t)src_y;
	}
	(*self->vb_xops.LOCAL_vbxo_blit)(self, (video_coord_t)dst_x, (video_coord_t)dst_y,
	                                 (video_coord_t)src_x, (video_coord_t)src_y,
	                                 size_x, size_y LOCAL_BITMASK__ARGS);
}

INTERN NONNULL((1)) void CC
LOCAL_libvideo_gfx_generic_stretch(struct video_blit *__restrict self,
                                   video_offset_t dst_x, video_offset_t dst_y,
                                   video_dim_t dst_size_x, video_dim_t dst_size_y,
                                   video_offset_t src_x, video_offset_t src_y,
                                   video_dim_t src_size_x, video_dim_t src_size_y
                                   LOCAL_BITMASK__PARAMS) {
	struct video_gfx *dst = self->vb_dst;
	struct video_gfx const *src = self->vb_src;
	video_coord_t temp;
	if unlikely(!dst_size_x || !dst_size_y || !src_size_x || !src_size_y)
		return;
	dst_x += dst->vx_cxoff;
	dst_y += dst->vx_cyoff;
	src_x += src->vx_cxoff;
	src_y += src->vx_cyoff;
	if unlikely(dst_x < (video_offset_t)dst->vx_bxmin) {
		video_dim_t srcpart;
		dst_x = (video_offset_t)(dst->vx_bxmin - (video_coord_t)dst_x);
		if unlikely((video_coord_t)dst_x >= dst_size_x)
			return;
		srcpart = ((video_coord_t)dst_x * src_size_x) / dst_size_x;
		if unlikely(srcpart >= src_size_x)
			return;
		src_size_x -= srcpart;
		dst_size_x -= (video_coord_t)dst_x;
		src_x += srcpart;
		dst_x = (video_offset_t)dst->vx_bxmin;
	}
	if unlikely(dst_y < (video_offset_t)dst->vx_bymin) {
		video_dim_t srcpart;
		dst_y = (video_offset_t)(dst->vx_bymin - (video_coord_t)dst_y);
		if unlikely((video_coord_t)dst_y >= dst_size_y)
			return;
		srcpart = ((video_coord_t)dst_y * src_size_y) / dst_size_y;
		if unlikely(srcpart >= src_size_y)
			return;
		src_size_y -= srcpart;
		dst_size_y -= (video_coord_t)dst_y;
		src_y += srcpart;
		dst_y = (video_offset_t)dst->vx_bymin;
	}
	if unlikely(src_x < (video_offset_t)src->vx_bxmin) {
		video_dim_t dstpart;
		src_x = (video_offset_t)(src->vx_bxmin - (video_coord_t)src_x);
		if unlikely((video_coord_t)src_x >= src_size_x)
			return;
		dstpart = ((video_coord_t)src_x * dst_size_x) / src_size_x;
		if unlikely(dstpart >= dst_size_x)
			return;
		dst_size_x -= dstpart;
		dst_x += dstpart;
		src_size_x -= (video_coord_t)src_x;
		src_x = (video_offset_t)src->vx_bxmin;
	}
	if unlikely(src_y < (video_offset_t)src->vx_bymin) {
		video_dim_t dstpart;
		src_y = (video_offset_t)(src->vx_bymin - (video_coord_t)src_y);
		src_y = -src_y;
		if unlikely((video_coord_t)src_y >= src_size_y)
			return;
		dstpart = ((video_coord_t)src_y * dst_size_y) / src_size_y;
		if unlikely(dstpart >= dst_size_y)
			return;
		dst_size_y -= dstpart;
		dst_y += dstpart;
		src_size_y -= (video_coord_t)src_y;
		src_y = (video_offset_t)src->vx_bymin;
	}

	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, dst_size_x, &temp) || temp > dst->vx_bxend) {
		video_dim_t newdstsize, overflow;
		if unlikely((video_coord_t)dst_x >= dst->vx_bxend)
			return;
		newdstsize = dst->vx_bxend - (video_coord_t)dst_x;
		overflow   = dst_size_x - newdstsize;
		overflow   = (overflow * src_size_x) / dst_size_x;
		dst_size_x = newdstsize;
		if unlikely(overflow >= src_size_x)
			return;
		src_size_x -= overflow;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, dst_size_y, &temp) || temp > dst->vx_byend) {
		video_dim_t newdstsize, overflow;
		if unlikely((video_coord_t)dst_y >= dst->vx_byend)
			return;
		newdstsize = dst->vx_byend - (video_coord_t)dst_y;
		overflow   = dst_size_y - newdstsize;
		overflow   = (overflow * src_size_y) / dst_size_y;
		dst_size_y = newdstsize;
		if unlikely(overflow >= src_size_y)
			return;
		src_size_y -= overflow;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)src_x, src_size_x, &temp) || temp > src->vx_bxend) {
		video_dim_t newsrcsize, overflow;
		if unlikely((video_coord_t)src_x >= src->vx_bxend)
			return;
		newsrcsize = src->vx_bxend - (video_coord_t)src_x;
		overflow   = src_size_x - newsrcsize;
		overflow   = (overflow * dst_size_x) / src_size_x;
		src_size_x = newsrcsize;
		if unlikely(overflow >= dst_size_x)
			return;
		dst_size_x -= overflow;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)src_y, src_size_y, &temp) || temp > src->vx_byend) {
		video_dim_t newsrcsize, overflow;
		if unlikely((video_coord_t)src_y >= src->vx_byend)
			return;
		newsrcsize = src->vx_byend - (video_coord_t)src_y;
		overflow   = src_size_y - newsrcsize;
		overflow   = (overflow * dst_size_y) / src_size_y;
		src_size_y = newsrcsize;
		if unlikely(overflow >= dst_size_y)
			return;
		dst_size_y -= overflow;
	}

	if (dst_size_x == src_size_x && dst_size_y == src_size_y) {
		/* Can use copy-blit */
		(*self->vb_xops.LOCAL_vbxo_blit)(self,
		                              (video_coord_t)dst_x, (video_coord_t)dst_y,
		                              (video_coord_t)src_x, (video_coord_t)src_y,
		                              dst_size_x, dst_size_y LOCAL_BITMASK__ARGS);
	} else {
		/* Must use stretch-blit */
		(*self->vb_xops.LOCAL_vbxo_stretch)(self,
		                                    (video_coord_t)dst_x, (video_coord_t)dst_y, dst_size_x, dst_size_y,
		                                    (video_coord_t)src_x, (video_coord_t)src_y, src_size_x, src_size_y
		                                    LOCAL_BITMASK__ARGS);
	}
}



INTERN NONNULL((1)) void CC
LOCAL_libvideo_gfx_generic_blit_rdwrap(struct video_blit *__restrict self,
                                       video_offset_t dst_x, video_offset_t dst_y,
                                       video_offset_t src_x, video_offset_t src_y,
                                       video_dim_t size_x, video_dim_t size_y
                                       LOCAL_BITMASK__PARAMS) {
	/* Handle the case where "src" has read-wrapping enabled. */
	struct video_gfx *dst = self->vb_dst;
	struct video_gfx const *src = self->vb_src;
	video_dim_t src_maxsx = size_x; /* # of pixes after src_x before wrap */
	video_dim_t src_maxsy = size_y; /* # of pixes after src_y before wrap */

	if (src->vx_flags & VIDEO_GFX_FRDXWRAP) {
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
		            dst_endx > dst->vx_cxsiz) {
			if unlikely((video_coord_t)dst_x >= dst->vx_cxsiz)
				return;
			size_x = dst->vx_cxsiz - (video_coord_t)dst_x;
		}
		src_x     = wrap(src_x, src->vx_cxsiz);
		src_maxsx = src->vx_cxsiz - (video_coord_t)src_x;
		assert(src_maxsx > 0);
	}

	if (src->vx_flags & VIDEO_GFX_FRDYWRAP) {
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
		            dst_endy > dst->vx_cysiz) {
			if unlikely((video_coord_t)dst_y >= dst->vx_cysiz)
				return;
			size_y = dst->vx_cysiz - (video_coord_t)dst_y;
		}
		src_y     = wrap(src_y, src->vx_cysiz);
		src_maxsy = src->vx_cysiz - (video_coord_t)src_y;
		assert(src_maxsy > 0);
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
		if ((size_x > src->vx_cxsiz || size_y > src->vx_cysiz) &&
		    (src->vx_buffer->vb_format.vf_codec != dst->vx_buffer->vb_format.vf_codec ||
		     src->vx_buffer->vb_format.vf_pal != dst->vx_buffer->vb_format.vf_pal)) {
			/* TODO */
		}

		iter_size_y = size_y;
		iter_dst_y  = dst_y;

		/* Deal with unaligned tiles near the top */
		if unlikely(src_maxsy < src->vx_cysiz) {
			/* Top-left corner */
			LOCAL_libvideo_gfx_generic_blit(self, dst_x, iter_dst_y, src_x, src_y,
			                                src_maxsx, src_maxsy LOCAL_BITMASK__ARGS);

			/* Top bar */
			iter_size_x = size_x - src_maxsx;
			iter_dst_x = dst_x + src_maxsx;
			while (iter_size_x > src->vx_cxsiz) {
				LOCAL_libvideo_gfx_generic_blit(self, iter_dst_x, iter_dst_y, 0, src_y,
				                                src->vx_cxsiz, src_maxsy LOCAL_BITMASK__ARGS);
				iter_size_x -= src->vx_cxsiz;
				iter_dst_x += src->vx_cxsiz;
			}

			/* Top-right corner */
			LOCAL_libvideo_gfx_generic_blit(self, iter_dst_x, iter_dst_y, 0, src_y,
			                                iter_size_x, src_maxsy LOCAL_BITMASK__ARGS);
			iter_size_y -= src_maxsy;
			iter_dst_y  += src_maxsy;
		}

		/* Iterate whole rows */
		while (iter_size_y >= src->vx_cysiz) {
			/* Left side */
			LOCAL_libvideo_gfx_generic_blit(self, dst_x, iter_dst_y, src_x, 0,
			                                src_maxsx, src->vx_cysiz LOCAL_BITMASK__ARGS);

			/* Center */
			iter_size_x = size_x - src_maxsx;
			iter_dst_x = dst_x + src_maxsx;
			while (iter_size_x > src->vx_cxsiz) {
				LOCAL_libvideo_gfx_generic_blit(self, iter_dst_x, iter_dst_y, 0, 0,
				                                src->vx_cxsiz, src->vx_cysiz LOCAL_BITMASK__ARGS);
				iter_size_x -= src->vx_cxsiz;
				iter_dst_x += src->vx_cxsiz;
			}

			/* Right side */
			LOCAL_libvideo_gfx_generic_blit(self, iter_dst_x, iter_dst_y, 0, 0,
			                                iter_size_x, src->vx_cysiz LOCAL_BITMASK__ARGS);

			iter_size_y -= src->vx_cysiz;
			iter_dst_y += src->vx_cysiz;
		}

		if likely(!iter_size_y)
			return;

		/* Bottom-left corner */
		LOCAL_libvideo_gfx_generic_blit(self, dst_x, iter_dst_y, src_x, 0,
		                                src_maxsx, iter_size_y LOCAL_BITMASK__ARGS);

		/* Bottom bar */
		iter_size_x = size_x - src_maxsx;
		iter_dst_x = dst_x + src_maxsx;
		while (iter_size_x > src->vx_cxsiz) {
			LOCAL_libvideo_gfx_generic_blit(self, iter_dst_x, iter_dst_y, 0, 0,
			                                src->vx_cxsiz, iter_size_y LOCAL_BITMASK__ARGS);
			iter_size_x -= src->vx_cxsiz;
			iter_dst_x += src->vx_cxsiz;
		}

		/* Bottom-right corner (render via fallthru) */
		dst_x  = iter_dst_x;
		dst_y  = iter_dst_y;
		src_x  = 0;
		src_y  = 0;
		size_x = iter_size_x;
		size_y = iter_size_y;
	} else if (size_x > src_maxsx) {
		LOCAL_libvideo_gfx_generic_blit(self, dst_x, dst_y, src_x, src_y,
		                                src_maxsx, size_y LOCAL_BITMASK__ARGS);
		size_x -= src_maxsx;
		dst_x += src_maxsx;
		while (size_x > src->vx_cxsiz) {
			LOCAL_libvideo_gfx_generic_blit(self, dst_x, dst_y, 0, src_y,
			                                src->vx_cxsiz, size_y LOCAL_BITMASK__ARGS);
			size_x -= src->vx_cxsiz;
			dst_x += src->vx_cxsiz;
		}
		src_x = 0; /* Fallthru to render the last part */
	} else if (size_y > src_maxsy) {
		LOCAL_libvideo_gfx_generic_blit(self, dst_x, dst_y, src_x, src_y,
		                                size_x, src_maxsy LOCAL_BITMASK__ARGS);
		size_y -= src_maxsy;
		dst_y += src_maxsy;
		while (size_y > src->vx_cysiz) {
			LOCAL_libvideo_gfx_generic_blit(self, dst_x, dst_y, src_x, 0,
			                                size_x, src->vx_cysiz LOCAL_BITMASK__ARGS);
			size_y -= src->vx_cysiz;
			dst_y += src->vx_cysiz;
		}
		src_y = 0; /* Fallthru to render the last part */
	}

	LOCAL_libvideo_gfx_generic_blit(self, dst_x, dst_y, src_x, src_y,
	                                size_x, size_y LOCAL_BITMASK__ARGS);
}

INTERN NONNULL((1)) void CC
LOCAL_libvideo_gfx_generic_stretch_rdwrap(struct video_blit *__restrict self,
                                          video_offset_t dst_x, video_offset_t dst_y,
                                          video_dim_t dst_size_x, video_dim_t dst_size_y,
                                          video_offset_t src_x, video_offset_t src_y,
                                          video_dim_t src_size_x, video_dim_t src_size_y
                                          LOCAL_BITMASK__PARAMS) {
	/* Handle the case where "src" has read-wrapping enabled. */
#define xdst2src(x) ((video_coord_t)(((uint64_t)(x) * src_size_x) / dst_size_x))
#define ydst2src(y) ((video_coord_t)(((uint64_t)(y) * src_size_y) / dst_size_y))
#define xsrc2dst(x) ((video_coord_t)(((uint64_t)(x) * dst_size_x) / src_size_x))
#define ysrc2dst(y) ((video_coord_t)(((uint64_t)(y) * dst_size_y) / src_size_y))
	struct video_gfx *dst = self->vb_dst;
	struct video_gfx const *src = self->vb_src;
	video_dim_t src_maxsx = src_size_x; /* # of pixes after src_x before wrap */
	video_dim_t src_maxsy = src_size_y; /* # of pixes after src_y before wrap */

	if (src->vx_flags & VIDEO_GFX_FRDXWRAP) {
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
		            dst_endx > dst->vx_cxsiz) {
			video_dim_t new_dst_size_x;
			if unlikely((video_coord_t)dst_x >= dst->vx_cxsiz)
				return;
			new_dst_size_x = dst->vx_cxsiz - (video_coord_t)dst_x;
			src_size_x -= xdst2src(dst_size_x - new_dst_size_x);
			dst_size_x = new_dst_size_x;
		}
		src_x     = wrap(src_x, src->vx_cxsiz);
		src_maxsx = src->vx_cxsiz - (video_coord_t)src_x;
		assert(src_maxsx > 0);
	}

	if (src->vx_flags & VIDEO_GFX_FRDYWRAP) {
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
		            dst_endy > dst->vx_cysiz) {
			video_dim_t new_dst_size_y;
			if unlikely((video_coord_t)dst_y >= dst->vx_cysiz)
				return;
			new_dst_size_y = dst->vx_cysiz - (video_coord_t)dst_y;
			src_size_y -= ydst2src(dst_size_y - new_dst_size_y);
			dst_size_y = new_dst_size_y;
		}
		src_y     = wrap(src_y, src->vx_cysiz);
		src_maxsy = src->vx_cysiz - (video_coord_t)src_y;
		assert(src_maxsy > 0);
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
		if ((src_size_x > src->vx_cxsiz || src_size_y > src->vx_cysiz) &&
		    (src->vx_buffer->vb_format.vf_codec != dst->vx_buffer->vb_format.vf_codec ||
		     src->vx_buffer->vb_format.vf_pal != dst->vx_buffer->vb_format.vf_pal)) {
			/* TODO */
		}

		/* Deal with unaligned tiles near the top */

		/* Top-left corner */
		LOCAL_libvideo_gfx_generic_stretch(self, dst_x, dst_y, firsttile_dst_size_x, firsttile_dst_size_y,
		                                   src_x, src_y, src_maxsx, src_maxsy LOCAL_BITMASK__ARGS);

		/* Top bar */
		iter_src_size_x = src_size_x - src_maxsx;
		iter_dst_x      = dst_x + firsttile_dst_size_x;
		iter_dst_size_x = dst_size_x - firsttile_dst_size_x;
		if (iter_src_size_x > src->vx_cxsiz) {
			video_coord_t base_dst_x;
			video_coord_t xwholetiles_i;
			xwholetiles_count = iter_src_size_x / src->vx_cxsiz;
			lasttile_dst_size_x = xsrc2dst(iter_src_size_x % src->vx_cxsiz);
			wholetiles_dst_size_x = iter_dst_size_x - lasttile_dst_size_x;
			base_dst_x = iter_dst_x;
			for (xwholetiles_i = 0; xwholetiles_i < xwholetiles_count; ++xwholetiles_i) {
				video_coord_t next_dst_x;
				next_dst_x = base_dst_x + (wholetiles_dst_size_x * (xwholetiles_i + 1)) / xwholetiles_count;
				LOCAL_libvideo_gfx_generic_stretch(self, iter_dst_x, dst_y, next_dst_x - iter_dst_x, firsttile_dst_size_y,
				                                   0, src_y, src->vx_cxsiz, src_maxsy LOCAL_BITMASK__ARGS);
				iter_dst_x = next_dst_x;
			}
			iter_src_size_x %= src->vx_cxsiz;
			iter_dst_size_x = lasttile_dst_size_x;
		}

		/* Top-right corner */
		LOCAL_libvideo_gfx_generic_stretch(self, iter_dst_x, dst_y, iter_dst_size_x, firsttile_dst_size_y,
		                                   0, src_y, iter_src_size_x, src_maxsy LOCAL_BITMASK__ARGS);

		/* Iterate whole rows */
		iter_src_size_y = src_size_y - src_maxsy;
		iter_dst_y      = dst_y + firsttile_dst_size_y;
		iter_dst_size_y = dst_size_y - firsttile_dst_size_y;
		if likely(iter_src_size_y >= src->vx_cysiz) {
			video_coord_t ywholetiles_i;
			video_dim_t ywholetiles_count = iter_src_size_y / src->vx_cysiz;
			video_dim_t lasttile_dst_size_y = ysrc2dst(iter_src_size_y % src->vx_cysiz);
			video_dim_t wholetiles_dst_size_y = iter_dst_size_y - lasttile_dst_size_y;
			video_coord_t base_dst_y = iter_dst_y;
			for (ywholetiles_i = 0; ywholetiles_i < ywholetiles_count; ++ywholetiles_i) {
				video_coord_t next_dst_y;
				video_dim_t tile_h;
				next_dst_y = base_dst_y + (wholetiles_dst_size_y * (ywholetiles_i + 1)) / ywholetiles_count;
				tile_h = next_dst_y - iter_dst_y;

				/* Left side */
				LOCAL_libvideo_gfx_generic_stretch(self, dst_x, iter_dst_y, firsttile_dst_size_x, tile_h,
				                                   src_x, 0, src_maxsx, src->vx_cysiz LOCAL_BITMASK__ARGS);

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
						LOCAL_libvideo_gfx_generic_stretch(self, iter_dst_x, iter_dst_y, next_dst_x - iter_dst_x, tile_h,
						                                   0, 0, src->vx_cxsiz, src->vx_cysiz LOCAL_BITMASK__ARGS);
						iter_dst_x = next_dst_x;
					} while (++xwholetiles_i < xwholetiles_count);
					iter_src_size_x %= src->vx_cxsiz;
					iter_dst_size_x = lasttile_dst_size_x;
				}

				/* Right side */
				LOCAL_libvideo_gfx_generic_stretch(self, iter_dst_x, iter_dst_y, lasttile_dst_size_x, tile_h,
				                                   0, 0, src_maxsx, src->vx_cysiz LOCAL_BITMASK__ARGS);

				iter_dst_y = next_dst_y;
			}
			iter_src_size_y %= src->vx_cysiz;
			iter_dst_size_y = lasttile_dst_size_y;
		}
		if likely(!iter_src_size_y)
			return;

		/* Bottom-left corner */
		LOCAL_libvideo_gfx_generic_stretch(self, dst_x, iter_dst_y, firsttile_dst_size_x, iter_dst_size_y,
		                                   src_x, 0, src_maxsx, iter_src_size_y LOCAL_BITMASK__ARGS);

		/* Bottom bar */
		iter_src_size_x = src_size_x - src_maxsx;
		iter_dst_x      = dst_x + firsttile_dst_size_x;
		iter_dst_size_x = dst_size_x - firsttile_dst_size_x;
		if (iter_src_size_x > src->vx_cxsiz) {
			video_coord_t base_dst_x;
			video_coord_t xwholetiles_i;
			xwholetiles_count = iter_src_size_x / src->vx_cxsiz;
			lasttile_dst_size_x = xsrc2dst(iter_src_size_x % src->vx_cxsiz);
			wholetiles_dst_size_x = iter_dst_size_x - lasttile_dst_size_x;
			base_dst_x = iter_dst_x;
			for (xwholetiles_i = 0; xwholetiles_i < xwholetiles_count; ++xwholetiles_i) {
				video_coord_t next_dst_x;
				next_dst_x = base_dst_x + (wholetiles_dst_size_x * (xwholetiles_i + 1)) / xwholetiles_count;
				LOCAL_libvideo_gfx_generic_stretch(self, iter_dst_x, iter_dst_y, next_dst_x - iter_dst_x, iter_dst_size_y,
				                                   0, 0, src->vx_cxsiz, iter_src_size_y LOCAL_BITMASK__ARGS);
				iter_dst_x = next_dst_x;
			}
			iter_src_size_x %= src->vx_cxsiz;
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
		LOCAL_libvideo_gfx_generic_stretch(self, dst_x, dst_y, firsttile_dst_size_x, dst_size_y,
		                                   src_x, src_y, src_maxsx, src_size_y
		                                   LOCAL_BITMASK__ARGS);
		src_size_x -= src_maxsx;
		dst_x += firsttile_dst_size_x;
		dst_size_x -= firsttile_dst_size_x;
		if (src_size_x > src->vx_cxsiz) {
			/* Whole tiles */
			video_coord_t xwholetiles_i;
			video_dim_t xwholetiles_count = src_size_x / src->vx_cxsiz;
			video_dim_t lasttile_dst_size_x = xsrc2dst(src_size_x % src->vx_cxsiz);
			video_dim_t wholetiles_dst_size_x = dst_size_x - lasttile_dst_size_x;
			video_coord_t base_dst_x = dst_x;
			for (xwholetiles_i = 0; xwholetiles_i < xwholetiles_count; ++xwholetiles_i) {
				video_coord_t next_dst_x;
				next_dst_x = base_dst_x + (wholetiles_dst_size_x * (xwholetiles_i + 1)) / xwholetiles_count;
				LOCAL_libvideo_gfx_generic_stretch(self, dst_x, dst_y, next_dst_x - dst_x, dst_size_y,
				                                   0, src_y, src->vx_cxsiz, src_size_y
				                                   LOCAL_BITMASK__ARGS);
				dst_x = next_dst_x;
			}
			src_size_x %= src->vx_cxsiz;
			dst_size_x = lasttile_dst_size_x;
		}
		src_x = 0; /* Fallthru to render the last part */
	} else if (src_size_y > src_maxsy) {
		video_dim_t firsttile_dst_size_y = ysrc2dst(src_maxsy);
		LOCAL_libvideo_gfx_generic_stretch(self, dst_x, dst_y, dst_size_x, firsttile_dst_size_y,
		                                   src_x, src_y, src_size_x, src_maxsy
		                                   LOCAL_BITMASK__ARGS);
		src_size_y -= src_maxsy;
		dst_y += firsttile_dst_size_y;
		dst_size_y -= firsttile_dst_size_y;
		if (src_size_y > src->vx_cysiz) {
			/* Whole tiles */
			video_coord_t ywholetiles_i;
			video_dim_t ywholetiles_count = src_size_y / src->vx_cysiz;
			video_dim_t lasttile_dst_size_y = ysrc2dst(src_size_y % src->vx_cysiz);
			video_dim_t wholetiles_dst_size_y = dst_size_y - lasttile_dst_size_y;
			video_coord_t base_dst_y = dst_y;
			for (ywholetiles_i = 0; ywholetiles_i < ywholetiles_count; ++ywholetiles_i) {
				video_coord_t next_dst_y;
				next_dst_y = base_dst_y + (wholetiles_dst_size_y * (ywholetiles_i + 1)) / ywholetiles_count;
				LOCAL_libvideo_gfx_generic_stretch(self, dst_x, dst_y, dst_size_x, next_dst_y - dst_y,
				                                   src_x, 0, src_size_x, src->vx_cysiz
				                                   LOCAL_BITMASK__ARGS);
				dst_y = next_dst_y;
			}
			src_size_y %= src->vx_cysiz;
			dst_size_y = lasttile_dst_size_y;
		}
		src_y = 0; /* Fallthru to render the last part */
	}

	LOCAL_libvideo_gfx_generic_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                   src_x, src_y, src_size_x, src_size_y
	                                   LOCAL_BITMASK__ARGS);
#undef xdst2src
#undef ydst2src
#undef xsrc2dst
#undef ysrc2dst
}



INTERN NONNULL((1)) void CC
LOCAL_libvideo_gfx_generic_blit_wrap(struct video_blit *__restrict self,
                                     video_offset_t dst_x, video_offset_t dst_y,
                                     video_offset_t src_x, video_offset_t src_y,
                                     video_dim_t size_x, video_dim_t size_y
                                     LOCAL_BITMASK__PARAMS) {
	/* Handle the case where "dst" has write-wrapping enabled. */
	struct video_gfx *dst = self->vb_dst;
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = size_x;
	video_dim_t yinb = size_y;
	if (dst->vx_flags & VIDEO_GFX_FWRXWRAP) {
		video_coord_t cxend;
		dst_x = wrap(dst_x, dst->vx_cxsiz);
		if (size_x > dst->vx_cxsiz)
			size_x = dst->vx_cxsiz;
		cxend = (video_coord_t)dst_x + size_x;
		if (OVERFLOW_USUB(cxend, dst->vx_cxsiz, &xwrap)) {
			xwrap = 0;
		} else {
			xinb = dst->vx_cxsiz - (video_coord_t)dst_x;
		}
	}
	if (dst->vx_flags & VIDEO_GFX_FWRYWRAP) {
		video_coord_t cyend;
		dst_y = wrap(dst_y, dst->vx_cysiz);
		if (size_y > dst->vx_cysiz)
			size_y = dst->vx_cysiz;
		cyend = (video_coord_t)dst_y + size_y;
		if (OVERFLOW_USUB(cyend, dst->vx_cysiz, &ywrap)) {
			ywrap = 0;
		} else {
			yinb = dst->vx_cysiz - (video_coord_t)dst_y;
		}
	}
	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		LOCAL_libvideo_gfx_generic_blit_rdwrap(self, 0, 0, src_x + xinb, src_y + yinb,
		                                       xwrap, ywrap LOCAL_BITMASK__ARGS);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		LOCAL_libvideo_gfx_generic_blit_rdwrap(self, 0, dst_y, src_x + xinb, src_y,
		                                       xwrap, size_y LOCAL_BITMASK__ARGS);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		LOCAL_libvideo_gfx_generic_blit_rdwrap(self, dst_x, 0, src_x, src_y + yinb,
		                                       size_x, ywrap LOCAL_BITMASK__ARGS);
	}
	LOCAL_libvideo_gfx_generic_blit_rdwrap(self, dst_x, dst_y, src_x, src_y,
	                                       xinb, yinb LOCAL_BITMASK__ARGS);
}

INTERN NONNULL((1)) void CC
LOCAL_libvideo_gfx_generic_stretch_wrap(struct video_blit *__restrict self,
                                        video_offset_t dst_x, video_offset_t dst_y,
                                        video_dim_t dst_size_x, video_dim_t dst_size_y,
                                        video_offset_t src_x, video_offset_t src_y,
                                        video_dim_t src_size_x, video_dim_t src_size_y
                                        LOCAL_BITMASK__PARAMS) {
	/* Handle the case where "dst" has write-wrapping enabled. */
	struct video_gfx *dst = self->vb_dst;
#define xdst2src(x) ((video_coord_t)(((uint64_t)(x) * src_size_x) / dst_size_x))
#define ydst2src(y) ((video_coord_t)(((uint64_t)(y) * src_size_y) / dst_size_y))
	video_dim_t xwrap = 0;
	video_dim_t ywrap = 0;
	video_dim_t xinb = dst_size_x;
	video_dim_t yinb = dst_size_y;
	if (dst->vx_flags & VIDEO_GFX_FWRXWRAP) {
		video_coord_t cxend;
		dst_x = wrap(dst_x, dst->vx_cxsiz);
		if (dst_size_x > dst->vx_cxsiz) {
			src_size_x = xdst2src(dst->vx_cxsiz);
			dst_size_x = dst->vx_cxsiz;
		}
		cxend = (video_coord_t)dst_x + dst_size_x;
		if (OVERFLOW_USUB(cxend, dst->vx_cxsiz, &xwrap)) {
			xwrap = 0;
		} else {
			xinb = dst->vx_cxsiz - (video_coord_t)dst_x;
		}
	}
	if (dst->vx_flags & VIDEO_GFX_FWRYWRAP) {
		video_coord_t cyend;
		dst_y = wrap(dst_y, dst->vx_cysiz);
		if (dst_size_y > dst->vx_cysiz) {
			src_size_y = ydst2src(dst->vx_cysiz);
			dst_size_y = dst->vx_cysiz;
		}
		cyend = (video_coord_t)dst_y + dst_size_y;
		if (OVERFLOW_USUB(cyend, dst->vx_cysiz, &ywrap)) {
			ywrap = 0;
		} else {
			yinb = dst->vx_cysiz - (video_coord_t)dst_y;
		}
	}

	if (xwrap && ywrap) { /* Must do a partial fill at the top-left */
		size_t chunk_src_x = xdst2src(xinb);
		size_t chunk_src_y = ydst2src(yinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		size_t chunk_src_size_y = ydst2src(ywrap);
		LOCAL_libvideo_gfx_generic_stretch_rdwrap(self, 0, 0, xwrap, ywrap,
		                                          src_x + chunk_src_x, src_y + chunk_src_y,
		                                          chunk_src_size_x, chunk_src_size_y
		                                          LOCAL_BITMASK__ARGS);
	}
	if (xwrap) { /* Must do a partial fill at the left */
		size_t chunk_src_x = xdst2src(xinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		LOCAL_libvideo_gfx_generic_stretch_rdwrap(self, 0, dst_y, xwrap, dst_size_y,
		                                          src_x + chunk_src_x, src_y,
		                                          chunk_src_size_x, src_size_y
		                                          LOCAL_BITMASK__ARGS);
	}
	if (ywrap) { /* Must do a partial fill at the top */
		size_t chunk_src_y = ydst2src(yinb);
		size_t chunk_src_size_y = ydst2src(ywrap);
		LOCAL_libvideo_gfx_generic_stretch_rdwrap(self, dst_x, 0, dst_size_x, ywrap,
		                                          src_x, src_y + chunk_src_y,
		                                          src_size_x, chunk_src_size_y
		                                          LOCAL_BITMASK__ARGS);
	}
	LOCAL_libvideo_gfx_generic_stretch_rdwrap(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                          src_x, src_y, src_size_x, src_size_y
	                                          LOCAL_BITMASK__ARGS);
#undef xdst2src
#undef ydst2src
}

#undef LOCAL_libvideo_gfx_generic_blit
#undef LOCAL_libvideo_gfx_generic_blit_rdwrap
#undef LOCAL_libvideo_gfx_generic_blit_wrap
#undef LOCAL_libvideo_gfx_generic_stretch
#undef LOCAL_libvideo_gfx_generic_stretch_rdwrap
#undef LOCAL_libvideo_gfx_generic_stretch_wrap
#undef LOCAL_vbxo_blit
#undef LOCAL_vbxo_stretch
#undef LOCAL_HAVE_BITMASK
#undef LOCAL_BITMASK__PARAMS
#undef LOCAL_BITMASK__ARGS

DECL_END

#undef DEFINE_libvideo_gfx_generic_blit__and__stretch
#undef DEFINE_libvideo_gfx_generic_bitblit__and__bitstretch
