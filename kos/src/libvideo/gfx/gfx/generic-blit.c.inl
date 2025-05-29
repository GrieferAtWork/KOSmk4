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
#define LOCAL_libvideo_gfx_generic__blit    libvideo_gfx_generic__blit
#define LOCAL_libvideo_gfx_generic__stretch libvideo_gfx_generic__stretch
#define LOCAL_libvideo_gfx_generic_blit     libvideo_gfx_generic_blit
#define LOCAL_libvideo_gfx_generic_stretch  libvideo_gfx_generic_stretch
#define LOCAL_copy_perpixel_fixed           generic_blit__copy_perpixel_fixed
#define LOCAL_vbxo_blit                     vbxo_blit
#define LOCAL_vbxo_stretch                  vbxo_stretch
#elif defined(DEFINE_libvideo_gfx_generic_bitblit__and__bitstretch)
#define LOCAL_libvideo_gfx_generic__blit    libvideo_gfx_generic__bitblit
#define LOCAL_libvideo_gfx_generic__stretch libvideo_gfx_generic__bitstretch
#define LOCAL_libvideo_gfx_generic_blit     libvideo_gfx_generic_bitblit
#define LOCAL_libvideo_gfx_generic_stretch  libvideo_gfx_generic_bitstretch
#define LOCAL_copy_perpixel_fixed           generic_bitblit__copy_perpixel_fixed
#define LOCAL_vbxo_blit                     vbxo_bitblit
#define LOCAL_vbxo_stretch                  vbxo_bitstretch
#define LOCAL_HAVE_BITMASK
#endif /* ... */

#ifdef LOCAL_HAVE_BITMASK
#define LOCAL_IF_HAVE_BITMASK(...) __VA_ARGS__
#define LOCAL_BITMASK__PARAMS      , void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan
#define LOCAL_BITMASK__ARGS        , bitmask, bitskip, bitscan
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
	if (!size_x || !size_y)
		return;
	dst_x += dst->vx_offt_x;
	dst_y += dst->vx_offt_y;
	src_x += src->vx_offt_x;
	src_y += src->vx_offt_y;
	if unlikely(dst_x < (video_offset_t)dst->vx_xmin) {
		dst_x = (video_offset_t)(dst->vx_xmin - (video_coord_t)dst_x);
		if unlikely((video_coord_t)dst_x >= size_x)
			return;
		LOCAL_IF_HAVE_BITMASK(bitskip += (video_coord_t)dst_x);
		src_x += (video_coord_t)dst_x;
		size_x -= (video_coord_t)dst_x;
		dst_x = (video_offset_t)dst->vx_xmin;
	}
	if unlikely(dst_y < (video_offset_t)dst->vx_ymin) {
		dst_y = (video_offset_t)(dst->vx_ymin - (video_coord_t)dst_y);
		if unlikely((video_coord_t)dst_y >= size_y)
			return;
		LOCAL_IF_HAVE_BITMASK(bitskip += ((video_coord_t)dst_y) * bitscan);
		src_y += (video_coord_t)dst_y;
		size_y -= (video_coord_t)dst_y;
		dst_y = (video_offset_t)dst->vx_ymin;
	}
	if unlikely(src_x < (video_offset_t)src->vx_xmin) {
		src_x = (video_offset_t)(src->vx_xmin - (video_coord_t)src_x);
		if unlikely((video_coord_t)src_x >= size_x)
			return;
		LOCAL_IF_HAVE_BITMASK(bitskip += (video_coord_t)src_x);
		dst_x += (video_coord_t)src_x;
		size_x -= (video_coord_t)src_x;
		src_x = (video_offset_t)src->vx_xmin;
	}
	if unlikely(src_y < (video_offset_t)src->vx_ymin) {
		src_y = (video_offset_t)(src->vx_ymin - (video_coord_t)src_y);
		if unlikely((video_coord_t)src_y >= size_y)
			return;
		LOCAL_IF_HAVE_BITMASK(bitskip += ((video_coord_t)src_y) * bitscan);
		dst_y += (video_coord_t)src_y;
		size_y -= (video_coord_t)src_y;
		src_y = (video_offset_t)src->vx_ymin;
	}

	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, size_x, &temp) || temp > dst->vx_xend) {
		if unlikely((video_coord_t)dst_x >= dst->vx_xend)
			return;
		size_x = dst->vx_xend - (video_coord_t)dst_x;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, size_y, &temp) || temp > dst->vx_yend) {
		if unlikely((video_coord_t)dst_y >= dst->vx_yend)
			return;
		size_y = dst->vx_yend - (video_coord_t)dst_y;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)src_x, size_x, &temp) || temp > src->vx_xend) {
		if unlikely((video_coord_t)src_x >= src->vx_xend)
			return;
		size_x = src->vx_xend - (video_coord_t)src_x;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)src_y, size_y, &temp) || temp > src->vx_yend) {
		if unlikely((video_coord_t)src_y >= src->vx_yend)
			return;
		size_y = src->vx_yend - (video_coord_t)src_y;
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
	LOCAL_IF_HAVE_BITMASK(video_dim_t bitmask_size_y);
	if unlikely(!dst_size_x || !dst_size_y || !src_size_x || !src_size_y)
		return;
	dst_x += dst->vx_offt_x;
	dst_y += dst->vx_offt_y;
	LOCAL_IF_HAVE_BITMASK(bitmask_size_y = src_size_y);
	src_x += src->vx_offt_x;
	src_y += src->vx_offt_y;
	if unlikely(dst_x < (video_offset_t)dst->vx_xmin) {
		video_dim_t srcpart;
		dst_x = (video_offset_t)(dst->vx_xmin - (video_coord_t)dst_x);
		if unlikely((video_coord_t)dst_x >= dst_size_x)
			return;
		srcpart = ((video_coord_t)dst_x * src_size_x) / dst_size_x;
		if unlikely(srcpart >= src_size_x)
			return;
		src_size_x -= srcpart;
		dst_size_x -= (video_coord_t)dst_x;
		LOCAL_IF_HAVE_BITMASK(bitskip += srcpart);
		src_x += srcpart;
		dst_x = (video_offset_t)dst->vx_xmin;
	}
	if unlikely(dst_y < (video_offset_t)dst->vx_ymin) {
		video_dim_t srcpart;
		dst_y = (video_offset_t)(dst->vx_ymin - (video_coord_t)dst_y);
		if unlikely((video_coord_t)dst_y >= dst_size_y)
			return;
		srcpart = ((video_coord_t)dst_y * src_size_y) / dst_size_y;
		if unlikely(srcpart >= src_size_y)
			return;
		src_size_y -= srcpart;
		dst_size_y -= (video_coord_t)dst_y;
		LOCAL_IF_HAVE_BITMASK(bitskip += srcpart * bitscan);
		src_y += srcpart;
		dst_y = (video_offset_t)dst->vx_ymin;
	}
	if unlikely(src_x < (video_offset_t)src->vx_xmin) {
		video_dim_t dstpart;
		src_x = (video_offset_t)(src->vx_xmin - (video_coord_t)src_x);
		if unlikely((video_coord_t)src_x >= src_size_x)
			return;
		dstpart = ((video_coord_t)src_x * dst_size_x) / src_size_x;
		if unlikely(dstpart >= dst_size_x)
			return;
		dst_size_x -= dstpart;
		dst_x += dstpart;
		LOCAL_IF_HAVE_BITMASK(bitskip += (video_coord_t)src_x);
		src_size_x -= (video_coord_t)src_x;
		src_x = (video_offset_t)src->vx_xmin;
	}
	if unlikely(src_y < (video_offset_t)src->vx_ymin) {
		video_dim_t dstpart;
		src_y = (video_offset_t)(src->vx_ymin - (video_coord_t)src_y);
		src_y = -src_y;
		if unlikely((video_coord_t)src_y >= src_size_y)
			return;
		dstpart = ((video_coord_t)src_y * dst_size_y) / src_size_y;
		if unlikely(dstpart >= dst_size_y)
			return;
		dst_size_y -= dstpart;
		dst_y += dstpart;
		LOCAL_IF_HAVE_BITMASK(bitskip += ((video_coord_t)-src_y) * bitscan);
		src_size_y -= (video_coord_t)src_y;
		src_y = (video_offset_t)src->vx_ymin;
	}

	/* Truncate copy-rect to src/dst buffer limits (out-of-bounds pixels aren't rendered) */
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_x, dst_size_x, &temp) || temp > dst->vx_xend) {
		video_dim_t newdstsize, overflow;
		if unlikely((video_coord_t)dst_x >= dst->vx_xend)
			return;
		newdstsize = dst->vx_xend - (video_coord_t)dst_x;
		overflow   = dst_size_x - newdstsize;
		overflow   = (overflow * src_size_x) / dst_size_x;
		dst_size_x = newdstsize;
		if unlikely(overflow >= src_size_x)
			return;
		src_size_x -= overflow;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)dst_y, dst_size_y, &temp) || temp > dst->vx_yend) {
		video_dim_t newdstsize, overflow;
		if unlikely((video_coord_t)dst_y >= dst->vx_yend)
			return;
		newdstsize = dst->vx_yend - (video_coord_t)dst_y;
		overflow   = dst_size_y - newdstsize;
		overflow   = (overflow * src_size_y) / dst_size_y;
		dst_size_y = newdstsize;
		if unlikely(overflow >= src_size_y)
			return;
		src_size_y -= overflow;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)src_x, src_size_x, &temp) || temp > src->vx_xend) {
		video_dim_t newsrcsize, overflow;
		if unlikely((video_coord_t)src_x >= src->vx_xend)
			return;
		newsrcsize = src->vx_xend - (video_coord_t)src_x;
		overflow   = src_size_x - newsrcsize;
		overflow   = (overflow * dst_size_x) / src_size_x;
		src_size_x = newsrcsize;
		if unlikely(overflow >= dst_size_x)
			return;
		dst_size_x -= overflow;
	}
	if unlikely(OVERFLOW_UADD((video_coord_t)src_y, src_size_y, &temp) || temp > src->vx_yend) {
		video_dim_t newsrcsize, overflow;
		if unlikely((video_coord_t)src_y >= src->vx_yend)
			return;
		newsrcsize = src->vx_yend - (video_coord_t)src_y;
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
		                                    LOCAL_IF_HAVE_BITMASK(, bitmask, bitskip, bitscan, bitmask_size_y));
	}
}

#undef LOCAL_libvideo_gfx_generic__blit
#undef LOCAL_libvideo_gfx_generic__stretch
#undef LOCAL_libvideo_gfx_generic_blit
#undef LOCAL_libvideo_gfx_generic_stretch
#undef LOCAL_copy_perpixel_fixed
#undef LOCAL_vbxo_blit
#undef LOCAL_vbxo_stretch
#undef LOCAL_HAVE_BITMASK
#undef LOCAL_IF_HAVE_BITMASK
#undef LOCAL_BITMASK__PARAMS
#undef LOCAL_BITMASK__ARGS

DECL_END

#undef DEFINE_libvideo_gfx_generic_blit__and__stretch
#undef DEFINE_libvideo_gfx_generic_bitblit__and__bitstretch
