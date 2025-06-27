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
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

//#define         DEFINE_libvideo_blitter_generic_blit
//#define      DEFINE_libvideo_blitter_generic_stretch
//#define DEFINE_libvideo_blitter_generic_blit_imatrix
#define DEFINE_libvideo_blitter_generic_stretch_imatrix
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

#if (defined(DEFINE_libvideo_blitter_generic_blit) +         \
     defined(DEFINE_libvideo_blitter_generic_stretch) +      \
     defined(DEFINE_libvideo_blitter_generic_blit_imatrix) + \
     defined(DEFINE_libvideo_blitter_generic_stretch_imatrix)) != 1
#error "Must #define exactly one of these"
#endif /* ... */

DECL_BEGIN

#ifdef DEFINE_libvideo_blitter_generic_blit
#define LOCAL_libvideo_blitter_generic_blit libvideo_blitter_generic_blit
#elif defined(DEFINE_libvideo_blitter_generic_stretch)
#define LOCAL_libvideo_blitter_generic_blit libvideo_blitter_generic_stretch
#define LOCAL_IS_STRETCH
#elif defined(DEFINE_libvideo_blitter_generic_blit_imatrix)
#define LOCAL_libvideo_blitter_generic_blit libvideo_blitter_generic_blit_imatrix
#define LOCAL_USE_IMATRIX
#elif defined(DEFINE_libvideo_blitter_generic_stretch_imatrix)
#define LOCAL_libvideo_blitter_generic_blit libvideo_blitter_generic_stretch_imatrix
#define LOCAL_USE_IMATRIX
#define LOCAL_IS_STRETCH
#else /* ... */
#error "Invalid configuration"
#endif /* !... */

#ifdef LOCAL_IS_STRETCH
#define LOCAL_IF_STRETCH(x)           x
#define LOCAL_IF_STRETCH_ELSE(tt, ff) tt
#else /* LOCAL_IS_STRETCH */
#define LOCAL_IF_STRETCH(x)           /* nothing */
#define LOCAL_IF_STRETCH_ELSE(tt, ff) ff
#endif /* !LOCAL_IS_STRETCH */

#ifdef LOCAL_USE_IMATRIX
#define LOCAL_IF_IMATRIX(x)           x
#define LOCAL_IF_IMATRIX_ELSE(tt, ff) tt
#else /* LOCAL_USE_IMATRIX */
#define LOCAL_IF_IMATRIX(x)           /* nothing */
#define LOCAL_IF_IMATRIX_ELSE(tt, ff) ff
#endif /* !LOCAL_USE_IMATRIX */

INTERN ATTR_IN(1) void CC
LOCAL_libvideo_blitter_generic_blit(struct video_blitter const *__restrict self
                                    , video_offset_t dst_x, video_offset_t dst_y
#ifdef LOCAL_IS_STRETCH
                                    , video_dim_t dst_size_x, video_dim_t dst_size_y
#endif /* LOCAL_IS_STRETCH */
                                    , video_offset_t src_x, video_offset_t src_y
#ifdef LOCAL_IS_STRETCH
                                    , video_dim_t src_size_x, video_dim_t src_size_y
#else /* LOCAL_IS_STRETCH */
                                    , video_dim_t size_x, video_dim_t size_y
#endif /* !LOCAL_IS_STRETCH */
                                    ) {
#ifdef LOCAL_IS_STRETCH
#define LOCAL_dst_size_x dst_size_x
#define LOCAL_dst_size_y dst_size_y
#define LOCAL_src_size_x src_size_x
#define LOCAL_src_size_y src_size_y
#else /* LOCAL_IS_STRETCH */
#define LOCAL_dst_size_x size_x
#define LOCAL_dst_size_y size_y
#define LOCAL_src_size_x size_x
#define LOCAL_src_size_y size_y
#endif /* !LOCAL_IS_STRETCH */
#ifdef LOCAL_USE_IMATRIX
	video_imatrix2d_t src_matrix;
	gfx_flag_t src_flags;
#endif /* LOCAL_USE_IMATRIX */
	struct video_gfx const *dst = self->vbt_dst;
	struct video_gfx const *src = self->vbt_src;
	video_coord_t temp;
#if 0
	syslog(LOG_DEBUG, PP_STR(LOCAL_libvideo_blitter_generic_blit) "("
#ifdef LOCAL_IS_STRETCH
	                  "dst: {%dx%d, %ux%u}, src: {%dx%d, %ux%u}"
#else /* LOCAL_IS_STRETCH */
	                  "dst: {%dx%d}, src: {%dx%d}, dim: {%ux%u}"
#endif /* !LOCAL_IS_STRETCH */
	                  ")\n",
#ifdef LOCAL_IS_STRETCH
	       dst_x, dst_y, dst_size_x, dst_size_y,
	       src_x, src_y, src_size_x, src_size_y
#else /* LOCAL_IS_STRETCH */
	       dst_x, dst_y, src_x, src_y, size_x, size_y
#endif /* !LOCAL_IS_STRETCH */
	       );
#endif

	/* Check for empty blit source/destination */
	if unlikely(LOCAL_IF_STRETCH_ELSE(!dst_size_x || !dst_size_y ||
	                                  !src_size_x || !src_size_y,
	                                  !size_x || !size_y))
		return;

	/* Apply mirror rules to destination coords */
#ifdef LOCAL_USE_IMATRIX
	if (dst->vx_flags & VIDEO_GFX_F_XMIRROR)
		dst_x = (dst->vx_hdr.vxh_cxsiz - LOCAL_dst_size_x) - dst_x;
	if (dst->vx_flags & VIDEO_GFX_F_YMIRROR)
		dst_y = (dst->vx_hdr.vxh_cysiz - LOCAL_dst_size_y) - dst_y;
#endif /* LOCAL_USE_IMATRIX */

	/* Apply destination clip rect offsets */
	dst_x += dst->vx_hdr.vxh_cxoff;
	dst_y += dst->vx_hdr.vxh_cyoff;

	/* Clamp destination I/O rect x.min */
	if unlikely(dst_x < (video_offset_t)dst->vx_hdr.vxh_bxmin) {
		video_dim_t dstpart;
		LOCAL_IF_STRETCH(video_dim_t srcpart);
		dstpart = dst->vx_hdr.vxh_bxmin - (video_coord_t)dst_x;
		if unlikely(dstpart >= LOCAL_dst_size_x)
			return;
		LOCAL_IF_STRETCH(srcpart = (dstpart * src_size_x) / dst_size_x);
		LOCAL_IF_STRETCH(if unlikely(srcpart >= src_size_x) return);
		LOCAL_IF_STRETCH(src_size_x -= srcpart);
		LOCAL_dst_size_x -= dstpart;
		dst_x = (video_offset_t)dst->vx_hdr.vxh_bxmin;
		src_x += LOCAL_IF_STRETCH_ELSE(srcpart, dstpart);
	}

	/* Clamp destination I/O rect y.min */
	if unlikely(dst_y < (video_offset_t)dst->vx_hdr.vxh_bymin) {
		video_dim_t dstpart;
		LOCAL_IF_STRETCH(video_dim_t srcpart);
		dstpart = dst->vx_hdr.vxh_bymin - (video_coord_t)dst_y;
		if unlikely(dstpart >= LOCAL_dst_size_y)
			return;
		LOCAL_IF_STRETCH(srcpart = (dstpart * src_size_y) / dst_size_y);
		LOCAL_IF_STRETCH(if unlikely(srcpart >= src_size_y) return);
		LOCAL_IF_STRETCH(src_size_y -= srcpart);
		LOCAL_dst_size_y -= dstpart;
		dst_y = (video_offset_t)dst->vx_hdr.vxh_bymin;
		src_y += LOCAL_IF_STRETCH_ELSE(srcpart, dstpart);
	}

	/* Clamp destination I/O rect x.end */
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, LOCAL_dst_size_x, &temp) ||
	            temp > dst->vx_hdr.vxh_bxend) {
		if unlikely((video_coord_t)dst_x >= dst->vx_hdr.vxh_bxend)
			return;
#ifdef LOCAL_IS_STRETCH
		{
			video_dim_t newdstsize, overflow;
			newdstsize = dst->vx_hdr.vxh_bxend - (video_coord_t)dst_x;
			overflow   = dst_size_x - newdstsize;
			overflow   = (overflow * src_size_x) / dst_size_x;
			dst_size_x = newdstsize;
			if unlikely(overflow >= src_size_x)
				return;
			src_size_x -= overflow;
		}
#else /* LOCAL_IS_STRETCH */
		size_x = dst->vx_hdr.vxh_bxend - (video_coord_t)dst_x;
#endif /* !LOCAL_IS_STRETCH */
	}

	/* Clamp destination I/O rect y.end */
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, LOCAL_dst_size_y, &temp) ||
	            temp > dst->vx_hdr.vxh_byend) {
		if unlikely((video_coord_t)dst_y >= dst->vx_hdr.vxh_byend)
			return;
#ifdef LOCAL_IS_STRETCH
		{
			video_dim_t newdstsize, overflow;
			newdstsize = dst->vx_hdr.vxh_byend - (video_coord_t)dst_y;
			overflow   = dst_size_y - newdstsize;
			overflow   = (overflow * src_size_y) / dst_size_y;
			dst_size_y = newdstsize;
			if unlikely(overflow >= src_size_y)
				return;
			src_size_y -= overflow;
		}
#else /* LOCAL_IS_STRETCH */
		size_y = dst->vx_hdr.vxh_byend - (video_coord_t)dst_y;
#endif /* !LOCAL_IS_STRETCH */
	}


	/* Apply source clip rect offsets */
	src_x += src->vx_hdr.vxh_cxoff;
	src_y += src->vx_hdr.vxh_cyoff;

	/* Clamp source I/O rect x.min */
	if unlikely(src_x < (video_offset_t)src->vx_hdr.vxh_bxmin) {
		video_dim_t srcpart;
		LOCAL_IF_STRETCH(video_dim_t dstpart);
		srcpart = src->vx_hdr.vxh_bxmin - (video_coord_t)src_x;
		if unlikely(srcpart >= LOCAL_src_size_x)
			return;
		LOCAL_IF_STRETCH(dstpart = (srcpart * dst_size_x) / src_size_x);
		LOCAL_IF_STRETCH(if unlikely(dstpart >= dst_size_x) return);
		LOCAL_IF_STRETCH(dst_size_x -= dstpart);
		dst_x += LOCAL_IF_STRETCH_ELSE(dstpart, srcpart);
		LOCAL_src_size_x -= srcpart;
		src_x = (video_offset_t)src->vx_hdr.vxh_bxmin;
	}

	/* Clamp source I/O rect y.min */
	if unlikely(src_y < (video_offset_t)src->vx_hdr.vxh_bymin) {
		video_dim_t srcpart;
		LOCAL_IF_STRETCH(video_dim_t dstpart);
		srcpart = src->vx_hdr.vxh_bymin - (video_coord_t)src_y;
		if unlikely(srcpart >= LOCAL_src_size_y)
			return;
		LOCAL_IF_STRETCH(dstpart = (srcpart * dst_size_y) / src_size_y);
		LOCAL_IF_STRETCH(if unlikely(dstpart >= dst_size_y) return);
		LOCAL_IF_STRETCH(dst_size_y -= dstpart);
		dst_y += LOCAL_IF_STRETCH_ELSE(dstpart, srcpart);
		LOCAL_src_size_y -= srcpart;
		src_y = (video_offset_t)src->vx_hdr.vxh_bymin;
	}

	/* Clamp source I/O rect x.end */
	if unlikely(OVERFLOW_UADD((video_coord_t)src_x, LOCAL_src_size_x, &temp) ||
	            temp > src->vx_hdr.vxh_bxend) {
		if unlikely((video_coord_t)src_x >= src->vx_hdr.vxh_bxend)
			return;
#ifdef LOCAL_IS_STRETCH
		{
			video_dim_t newsrcsize, overflow;
			newsrcsize = src->vx_hdr.vxh_bxend - (video_coord_t)src_x;
			overflow   = src_size_x - newsrcsize;
			overflow   = (overflow * dst_size_x) / src_size_x;
			src_size_x = newsrcsize;
			if unlikely(overflow >= dst_size_x)
				return;
			dst_size_x -= overflow;
		}
#else /* LOCAL_IS_STRETCH */
		size_x = src->vx_hdr.vxh_bxend - (video_coord_t)src_x;
#endif /* !LOCAL_IS_STRETCH */
	}

	/* Clamp source I/O rect y.end */
	if unlikely(OVERFLOW_UADD((video_coord_t)src_y, LOCAL_src_size_y, &temp) ||
	            temp > src->vx_hdr.vxh_byend) {
		if unlikely((video_coord_t)src_y >= src->vx_hdr.vxh_byend)
			return;
#ifdef LOCAL_IS_STRETCH
		{
			video_dim_t newsrcsize, overflow;
			newsrcsize = src->vx_hdr.vxh_byend - (video_coord_t)src_y;
			overflow   = src_size_y - newsrcsize;
			overflow   = (overflow * dst_size_y) / src_size_y;
			src_size_y = newsrcsize;
			if unlikely(overflow >= dst_size_y)
				return;
			dst_size_y -= overflow;
		}
#else /* LOCAL_IS_STRETCH */
		size_y = src->vx_hdr.vxh_byend - (video_coord_t)src_y;
#endif /* !LOCAL_IS_STRETCH */
	}


	/* Construct source pixel transformation matrix */
#ifdef LOCAL_USE_IMATRIX
	/* Load identity matrix */
	src_matrix[0][0] = 1;
	src_matrix[0][1] = 0;
	src_matrix[1][0] = 0;
	src_matrix[1][1] = 1;

	/* Because pixel transformation flags happen in order:
	 * - src: VIDEO_GFX_F_XYSWAP
	 * - src: VIDEO_GFX_F_XMIRROR/VIDEO_GFX_F_YMIRROR
	 * - dst: VIDEO_GFX_F_XMIRROR/VIDEO_GFX_F_YMIRROR
	 * - dst: VIDEO_GFX_F_XYSWAP
	 *
	 * We need to invert X/Y-mirror flags of "src" because
	 * code below necessarily has to operate on an  order:
	 * - src: VIDEO_GFX_F_XMIRROR/VIDEO_GFX_F_YMIRROR
	 * - src: VIDEO_GFX_F_XYSWAP
	 * - dst: VIDEO_GFX_F_XMIRROR/VIDEO_GFX_F_YMIRROR
	 * - dst: VIDEO_GFX_F_XYSWAP */
	src_flags = src->vx_flags;
	if (src_flags & VIDEO_GFX_F_XYSWAP) {
#define XMIRROR_TO_YMIRROR_LSHIFT 1
		static_assert((VIDEO_GFX_F_XMIRROR << XMIRROR_TO_YMIRROR_LSHIFT) == VIDEO_GFX_F_YMIRROR);
		src_flags = (src_flags & ~(VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR)) |
		            ((src_flags & VIDEO_GFX_F_XMIRROR) << XMIRROR_TO_YMIRROR_LSHIFT) |
		            ((src_flags & VIDEO_GFX_F_YMIRROR) >> XMIRROR_TO_YMIRROR_LSHIFT);
	}
	if (src_flags & VIDEO_GFX_F_XMIRROR) {
		src_x -= src->vx_hdr.vxh_bxmin;
		src_x = ((src->vx_hdr.vxh_bxend - src->vx_hdr.vxh_bxmin) - LOCAL_src_size_x) - src_x;
		src_x += src->vx_hdr.vxh_bxmin;
	}
	if (src_flags & VIDEO_GFX_F_YMIRROR) {
		src_y -= src->vx_hdr.vxh_bymin;
		src_y = ((src->vx_hdr.vxh_byend - src->vx_hdr.vxh_bymin) - LOCAL_src_size_y) - src_y;
		src_y += src->vx_hdr.vxh_bymin;
	}
	if ((src_flags ^ dst->vx_flags) & VIDEO_GFX_F_XMIRROR) {
		src_matrix[0][0] = -1;
		src_x += LOCAL_src_size_x - 1;
	}
	if ((src_flags ^ dst->vx_flags) & VIDEO_GFX_F_YMIRROR) {
		src_matrix[1][1] = -1;
		src_y += LOCAL_src_size_y - 1;
	}

	/* Apply X/Y-swap rules and finalize src_x/src_y coords */
#define Tswap(T, a, b) ({ typeof(a) _temp = (a); (a) = (b); (b) = _temp; })
	if (src_flags & VIDEO_GFX_F_XYSWAP) {
		Tswap(video_imatrix2d_word_t, src_matrix[0][0], src_matrix[1][0]);
		Tswap(video_imatrix2d_word_t, src_matrix[1][1], src_matrix[0][1]);
		Tswap(video_offset_t, src_x, src_y);
	}
	if (dst->vx_flags & VIDEO_GFX_F_XYSWAP) {
		Tswap(video_imatrix2d_word_t, src_matrix[0][0], src_matrix[0][1]);
		Tswap(video_imatrix2d_word_t, src_matrix[1][1], src_matrix[1][0]);
		Tswap(video_offset_t, dst_x, dst_y);
		Tswap(video_dim_t, LOCAL_dst_size_x, LOCAL_dst_size_y);
#ifdef LOCAL_IS_STRETCH
		Tswap(video_dim_t, LOCAL_src_size_x, LOCAL_src_size_y);
#endif /* LOCAL_IS_STRETCH */
	}
#undef Tswap
#endif /* LOCAL_USE_IMATRIX */


	/* Check if we have to use stretch-blitting */
#ifdef LOCAL_IS_STRETCH
	if (dst_size_x != src_size_x || dst_size_y != src_size_y) {
#ifdef LOCAL_USE_IMATRIX
		video_blitter_x_stretch_imatrix(self,
		                                (video_coord_t)dst_x, (video_coord_t)dst_y, dst_size_x, dst_size_y,
		                                (video_coord_t)src_x, (video_coord_t)src_y, src_size_x, src_size_y,
		                                src_matrix);
#else /* LOCAL_USE_IMATRIX */
		video_blitter_x_stretch(self,
		                        (video_coord_t)dst_x, (video_coord_t)dst_y, dst_size_x, dst_size_y,
		                        (video_coord_t)src_x, (video_coord_t)src_y, src_size_x, src_size_y);
#endif /* !LOCAL_USE_IMATRIX */
		return;
	}
#endif /* LOCAL_IS_STRETCH */

	/* Can use copy-blit */
#ifdef LOCAL_USE_IMATRIX
	video_blitter_x_blit_imatrix(self,
	                             (video_coord_t)dst_x, (video_coord_t)dst_y,
	                             (video_coord_t)src_x, (video_coord_t)src_y,
	                             LOCAL_dst_size_x, LOCAL_dst_size_y,
	                             src_matrix);
#else /* LOCAL_USE_IMATRIX */
	video_blitter_x_blit(self,
	                     (video_coord_t)dst_x, (video_coord_t)dst_y,
	                     (video_coord_t)src_x, (video_coord_t)src_y,
	                     LOCAL_dst_size_x, LOCAL_dst_size_y);
#endif /* !LOCAL_USE_IMATRIX */
#undef LOCAL_dst_size_x
#undef LOCAL_dst_size_y
#undef LOCAL_src_size_x
#undef LOCAL_src_size_y
#undef LOCAL_lo_src_x
#undef LOCAL_lo_src_y
}

#undef LOCAL_IF_STRETCH
#undef LOCAL_IF_STRETCH_ELSE
#undef LOCAL_IF_IMATRIX
#undef LOCAL_IF_IMATRIX_ELSE
#undef LOCAL_USE_IMATRIX
#undef LOCAL_IS_STRETCH
#undef LOCAL_libvideo_blitter_generic_blit

DECL_END

#undef DEFINE_libvideo_blitter_generic_stretch_imatrix
#undef DEFINE_libvideo_blitter_generic_blit_imatrix
#undef DEFINE_libvideo_blitter_generic_stretch
#undef DEFINE_libvideo_blitter_generic_blit
