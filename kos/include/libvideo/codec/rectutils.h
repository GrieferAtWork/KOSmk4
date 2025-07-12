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
#ifndef _LIBVIDEO_CODEC_RECTUTILS_H
#define _LIBVIDEO_CODEC_RECTUTILS_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/__minmax.h>
#include <hybrid/__assert.h>

#include <bits/types.h>

#include "types.h"

#ifdef __CC__
__DECL_BEGIN

/* Check if {x,y} is contained within "self" */
#define video_rect_contains(self, x, y)                                     \
	((x) >= (self)->vr_xmin && (x) < ((self)->vr_xmin + (self)->vr_xdim) && \
	 (y) >= (self)->vr_ymin && (y) < ((self)->vr_ymin + (self)->vr_ydim))


/* Check if "a" and "b" intersect, and if so: store that intersection and return true */
__LOCAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) __BOOL LIBVIDEO_CODEC_CC
video_rect_intersect(struct video_rect const *__restrict a,
                     struct video_rect const *__restrict b,
                     struct video_rect *__restrict intersect) {
	video_offset_t a_xend, a_yend;
	video_offset_t b_xend, b_yend;
	video_offset_t intersect_xend, intersect_yend;
	a_xend = a->vr_xmin + a->vr_xdim;
	a_yend = a->vr_ymin + a->vr_ydim;
	b_xend = b->vr_xmin + b->vr_xdim;
	b_yend = b->vr_ymin + b->vr_ydim;
	intersect_xend = __hybrid_min(a_xend, b_xend);
	intersect_yend = __hybrid_min(a_yend, b_yend);
	intersect->vr_xmin = __hybrid_max(a->vr_xmin, b->vr_xmin);
	intersect->vr_ymin = __hybrid_max(a->vr_ymin, b->vr_ymin);
	if (intersect->vr_xmin < intersect_xend && intersect->vr_ymin < intersect_yend) {
		intersect->vr_xdim = (video_dim_t)(intersect_xend - intersect->vr_xmin);
		intersect->vr_ydim = (video_dim_t)(intersect_yend - intersect->vr_ymin);
		return 1;
	}
	return 0;
}


/* Subtract "small" from "big", producing up to 4 smaller rects stored in "out"
 * @assume(small IS_CONTAINED_INSIDE_OF big);
 * @return: * : The # of rects written to "out". */
__LOCAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) __size_t LIBVIDEO_CODEC_CC
video_rect_subtract(struct video_rect const *__restrict big,
                    struct video_rect const *__restrict small,
                    struct video_rect out[4]) {
	__size_t result = 0;
	video_offset_t big_xend = big->vr_xmin + big->vr_xdim;
	video_offset_t big_yend = big->vr_ymin + big->vr_ydim;
	video_offset_t small_xend = small->vr_xmin + small->vr_xdim;
	video_offset_t small_yend = small->vr_ymin + small->vr_ydim;
	__hybrid_assert(small->vr_xmin >= big->vr_xmin);
	__hybrid_assert(small->vr_ymin >= big->vr_ymin);
	__hybrid_assert(small_xend <= big_xend);
	__hybrid_assert(small_yend <= big_yend);
	__hybrid_assert(small->vr_xdim);
	__hybrid_assert(small->vr_ydim);
	__hybrid_assert(big->vr_xdim);
	__hybrid_assert(big->vr_ydim);

	/* Top row */
	if (small->vr_ymin > big->vr_ymin) {
		out[result].vr_xmin = big->vr_xmin;
		out[result].vr_ymin = big->vr_ymin;
		out[result].vr_xdim = big->vr_xdim;
		out[result].vr_ydim = (video_dim_t)(small->vr_ymin - big->vr_ymin);
		++result;
	}

	/* Bottom row */
	if (small_yend < big_yend) {
		out[result].vr_xmin = big->vr_xmin;
		out[result].vr_ymin = small_yend;
		out[result].vr_xdim = big->vr_xdim;
		out[result].vr_ydim = (video_dim_t)(big_yend - small_yend);
		++result;
	}

	/* Left column (w/ top/bottom row removed) */
	if (small->vr_xmin > big->vr_xmin) {
		out[result].vr_xmin = big->vr_xmin;
		out[result].vr_ymin = small->vr_ymin;
		out[result].vr_xdim = (video_dim_t)(small->vr_xmin - big->vr_xmin);
		out[result].vr_ydim = (video_dim_t)(small_yend - small->vr_ymin);
		++result;
	}

	/* Left column (w/ top/bottom row removed) */
	if (small_xend < big_xend) {
		out[result].vr_xmin = small_xend;
		out[result].vr_ymin = small->vr_ymin;
		out[result].vr_xdim = (video_dim_t)(big_xend - small_xend);
		out[result].vr_ydim = (video_dim_t)(small_yend - small->vr_ymin);
		++result;
	}
	return result;
}




__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_CODEC_RECTUTILS_H */
