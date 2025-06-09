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
#define LOCAL_IF_HAVE_BITMASK(...) __VA_ARGS__
#define LOCAL_BITMASK__PARAMS      , struct video_bitmask const *__restrict bm
#define LOCAL_BITMASK__ARGS        , bm
#else /* LOCAL_HAVE_BITMASK */
#define LOCAL_IF_HAVE_BITMASK(...) /* nothing */
#define LOCAL_BITMASK__PARAMS      /* nothing */
#define LOCAL_BITMASK__ARGS        /* nothing */
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
	LOCAL_IF_HAVE_BITMASK(struct video_bitmask fixed_bm);
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
		LOCAL_IF_HAVE_BITMASK(fixed_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(bm = &fixed_bm);
		LOCAL_IF_HAVE_BITMASK(fixed_bm.vbm_skip += (video_coord_t)dst_x);
		src_x += (video_coord_t)dst_x;
		size_x -= (video_coord_t)dst_x;
		dst_x = (video_offset_t)dst->vx_bxmin;
	}
	if unlikely(dst_y < (video_offset_t)dst->vx_bymin) {
		dst_y = (video_offset_t)(dst->vx_bymin - (video_coord_t)dst_y);
		if unlikely((video_coord_t)dst_y >= size_y)
			return;
		LOCAL_IF_HAVE_BITMASK(fixed_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(bm = &fixed_bm);
		LOCAL_IF_HAVE_BITMASK(fixed_bm.vbm_skip += ((video_coord_t)dst_y) * fixed_bm.vbm_scan);
		src_y += (video_coord_t)dst_y;
		size_y -= (video_coord_t)dst_y;
		dst_y = (video_offset_t)dst->vx_bymin;
	}
	if unlikely(src_x < (video_offset_t)src->vx_bxmin) {
		src_x = (video_offset_t)(src->vx_bxmin - (video_coord_t)src_x);
		if unlikely((video_coord_t)src_x >= size_x)
			return;
		LOCAL_IF_HAVE_BITMASK(fixed_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(bm = &fixed_bm);
		LOCAL_IF_HAVE_BITMASK(fixed_bm.vbm_skip += (video_coord_t)src_x);
		dst_x += (video_coord_t)src_x;
		size_x -= (video_coord_t)src_x;
		src_x = (video_offset_t)src->vx_bxmin;
	}
	if unlikely(src_y < (video_offset_t)src->vx_bymin) {
		src_y = (video_offset_t)(src->vx_bymin - (video_coord_t)src_y);
		if unlikely((video_coord_t)src_y >= size_y)
			return;
		LOCAL_IF_HAVE_BITMASK(fixed_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(bm = &fixed_bm);
		LOCAL_IF_HAVE_BITMASK(fixed_bm.vbm_skip += ((video_coord_t)src_y) * fixed_bm.vbm_scan);
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
	LOCAL_IF_HAVE_BITMASK(struct video_bitmask fixed_bm);
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
		LOCAL_IF_HAVE_BITMASK(fixed_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(bm = &fixed_bm);
		LOCAL_IF_HAVE_BITMASK(fixed_bm.vbm_skip += srcpart);
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
		LOCAL_IF_HAVE_BITMASK(fixed_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(bm = &fixed_bm);
		LOCAL_IF_HAVE_BITMASK(fixed_bm.vbm_skip += srcpart * fixed_bm.vbm_scan);
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
		LOCAL_IF_HAVE_BITMASK(fixed_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(bm = &fixed_bm);
		LOCAL_IF_HAVE_BITMASK(fixed_bm.vbm_skip += (video_coord_t)src_x);
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
		LOCAL_IF_HAVE_BITMASK(fixed_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(bm = &fixed_bm);
		LOCAL_IF_HAVE_BITMASK(fixed_bm.vbm_skip += ((video_coord_t)-src_y) * fixed_bm.vbm_scan);
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
	struct video_gfx *dst = self->vb_dst;
	struct video_gfx const *src = self->vb_src;
	/* TODO */
	(void)dst;
	(void)src;
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
	struct video_gfx *dst = self->vb_dst;
	struct video_gfx const *src = self->vb_src;
	/* TODO */
	(void)dst;
	(void)src;
	LOCAL_libvideo_gfx_generic_stretch(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                   src_x, src_y, src_size_x, src_size_y
	                                   LOCAL_BITMASK__ARGS);
}



INTERN NONNULL((1)) void CC
LOCAL_libvideo_gfx_generic_blit_wrap(struct video_blit *__restrict self,
                                     video_offset_t dst_x, video_offset_t dst_y,
                                     video_offset_t src_x, video_offset_t src_y,
                                     video_dim_t size_x, video_dim_t size_y
                                     LOCAL_BITMASK__PARAMS) {
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
		LOCAL_IF_HAVE_BITMASK(struct video_bitmask chunk_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(chunk_bm.vbm_skip += xinb + (yinb * chunk_bm.vbm_scan));
		LOCAL_libvideo_gfx_generic_blit_rdwrap(self, 0, 0, src_x + xinb, src_y + yinb,
		                                       xwrap, ywrap LOCAL_IF_HAVE_BITMASK(, &chunk_bm));
	}
	if (xwrap) { /* Must do a partial fill at the left */
		LOCAL_IF_HAVE_BITMASK(struct video_bitmask chunk_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(chunk_bm.vbm_skip += xinb);
		LOCAL_libvideo_gfx_generic_blit_rdwrap(self, 0, dst_y, src_x + xinb, src_y,
		                                       xwrap, size_y LOCAL_IF_HAVE_BITMASK(, &chunk_bm));
	}
	if (ywrap) { /* Must do a partial fill at the top */
		LOCAL_IF_HAVE_BITMASK(struct video_bitmask chunk_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(chunk_bm.vbm_skip += yinb * chunk_bm.vbm_scan);
		LOCAL_libvideo_gfx_generic_blit_rdwrap(self, dst_x, 0, src_x, src_y + yinb,
		                                       size_x, ywrap LOCAL_IF_HAVE_BITMASK(, &chunk_bm));
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
		LOCAL_IF_HAVE_BITMASK(struct video_bitmask chunk_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(chunk_bm.vbm_skip += chunk_src_x + (chunk_src_y * chunk_bm.vbm_scan));
		LOCAL_libvideo_gfx_generic_stretch_rdwrap(self, 0, 0, xwrap, ywrap,
		                                          src_x + chunk_src_x, src_y + chunk_src_y,
		                                          chunk_src_size_x, chunk_src_size_y
		                                          LOCAL_IF_HAVE_BITMASK(, &chunk_bm));
	}
	if (xwrap) { /* Must do a partial fill at the left */
		size_t chunk_src_x = xdst2src(xinb);
		size_t chunk_src_size_x = xdst2src(xwrap);
		LOCAL_IF_HAVE_BITMASK(struct video_bitmask chunk_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(chunk_bm.vbm_skip += chunk_src_x);
		LOCAL_libvideo_gfx_generic_stretch_rdwrap(self, 0, dst_y, xwrap, dst_size_y,
		                                          src_x + chunk_src_x, src_y,
		                                          chunk_src_size_x, src_size_y
		                                          LOCAL_IF_HAVE_BITMASK(, &chunk_bm));
	}
	if (ywrap) { /* Must do a partial fill at the top */
		size_t chunk_src_y = ydst2src(yinb);
		size_t chunk_src_size_y = ydst2src(ywrap);
		LOCAL_IF_HAVE_BITMASK(struct video_bitmask chunk_bm = *bm);
		LOCAL_IF_HAVE_BITMASK(chunk_bm.vbm_skip += chunk_src_y * chunk_bm.vbm_scan);
		LOCAL_libvideo_gfx_generic_stretch_rdwrap(self, dst_x, 0, dst_size_x, ywrap,
		                                          src_x, src_y + chunk_src_y,
		                                          src_size_x, chunk_src_size_y
		                                          LOCAL_IF_HAVE_BITMASK(, &chunk_bm));
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
#undef LOCAL_IF_HAVE_BITMASK
#undef LOCAL_BITMASK__PARAMS
#undef LOCAL_BITMASK__ARGS

DECL_END

#undef DEFINE_libvideo_gfx_generic_blit__and__stretch
#undef DEFINE_libvideo_gfx_generic_bitblit__and__bitstretch
