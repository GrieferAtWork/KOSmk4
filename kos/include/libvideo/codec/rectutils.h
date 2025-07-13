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

#include <hybrid/__assert.h>
#include <hybrid/__minmax.h>
#include <hybrid/__overflow.h>

#include <bits/types.h>

#include "types.h"

#ifdef __CC__
__DECL_BEGIN

#define video_rect_getxmin(self) (self)->vr_xmin
#define video_rect_getymin(self) (self)->vr_ymin
#define video_rect_getxdim(self) (self)->vr_xdim
#define video_rect_getydim(self) (self)->vr_ydim
#define video_rect_getxend(self) ((self)->vr_xmin + (self)->vr_xdim)
#define video_rect_getyend(self) ((self)->vr_ymin + (self)->vr_ydim)

#define video_rect_setxmin(self, v) (void)((self)->vr_xmin = (v))
#define video_rect_setymin(self, v) (void)((self)->vr_ymin = (v))
#define video_rect_setxdim(self, v) (void)((self)->vr_xdim = (v))
#define video_rect_setydim(self, v) (void)((self)->vr_ydim = (v))
#define video_rect_setxend(self, v) (void)((self)->vr_xdim = (video_dim_t)((v) - (self)->vr_xmin))
#define video_rect_setyend(self, v) (void)((self)->vr_ydim = (video_dim_t)((v) - (self)->vr_ymin))

#define video_rect_addx(self, v) (void)((self)->vr_xmin += (v))
#define video_rect_addy(self, v) (void)((self)->vr_ymin += (v))

/* Check if {x,y} is contained within "self" */
#define video_rect_contains(self, x, y)                                   \
	((x) >= video_rect_getxmin(self) && (x) < video_rect_getxend(self) && \
	 (y) >= video_rect_getymin(self) && (y) < video_rect_getyend(self))

/* Check if 2 rects overlap (`video_rect_intersect()' would return true) */
#define video_rect_intersects(a, b)                                                                    \
	(video_rect_getxmin(a) < video_rect_getxend(b) && video_rect_getxend(a) > video_rect_getxmin(b) && \
	 video_rect_getymin(a) < video_rect_getyend(b) && video_rect_getyend(a) > video_rect_getymin(b))

/* Check if "a" and "b" intersect, and if so: store that intersection and return true */
__LOCAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) __BOOL LIBVIDEO_CODEC_CC
video_rect_intersect(struct video_rect const *__restrict a,
                     struct video_rect const *__restrict b,
                     struct video_rect *__restrict intersect) {
	video_offset_t a_xend = video_rect_getxend(a);
	video_offset_t a_yend = video_rect_getyend(a);
	video_offset_t b_xend = video_rect_getxend(b);
	video_offset_t b_yend = video_rect_getyend(b);
	video_offset_t intersect_xend = __hybrid_min(a_xend, b_xend);
	video_offset_t intersect_yend = __hybrid_min(a_yend, b_yend);
	video_rect_setxmin(intersect, __hybrid_max(video_rect_getxmin(a), video_rect_getxmin(b)));
	video_rect_setymin(intersect, __hybrid_max(video_rect_getymin(a), video_rect_getymin(b)));
	if (video_rect_getxmin(intersect) < intersect_xend && video_rect_getymin(intersect) < intersect_yend) {
		video_rect_setxend(intersect, intersect_xend);
		video_rect_setyend(intersect, intersect_yend);
		return 1;
	}
	return 0;
}

/* Same as `video_rect_intersect()', but safely handles overflow in "b" */
__LOCAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) __BOOL LIBVIDEO_CODEC_CC
video_rect_intersect_overflow_in_b(struct video_rect const *__restrict a,
                                   struct video_rect const *__restrict b,
                                   struct video_rect *__restrict intersect) {
	video_offset_t a_xend = video_rect_getxend(a);
	video_offset_t a_yend = video_rect_getyend(a);
	video_offset_t b_xend, b_yend;
	video_offset_t intersect_xend = __hybrid_min(a_xend, b_xend);
	video_offset_t intersect_yend = __hybrid_min(a_yend, b_yend);
	if (__hybrid_overflow_sadd(video_rect_getxmin(b), video_rect_getxdim(b), &b_xend))
		b_xend = VIDEO_OFFSET_MAX;
	if (__hybrid_overflow_sadd(video_rect_getymin(b), video_rect_getydim(b), &b_yend))
		b_yend = VIDEO_OFFSET_MAX;
	video_rect_setxmin(intersect, __hybrid_max(video_rect_getxmin(a), video_rect_getxmin(b)));
	video_rect_setymin(intersect, __hybrid_max(video_rect_getymin(a), video_rect_getymin(b)));
	if (video_rect_getxmin(intersect) < intersect_xend && video_rect_getymin(intersect) < intersect_yend) {
		video_rect_setxend(intersect, intersect_xend);
		video_rect_setyend(intersect, intersect_yend);
		return 1;
	}
	return 0;
}


/* Update `__union' by adding `__addme' */
__LOCAL __ATTR_INOUT(1) __ATTR_IN(2) void LIBVIDEO_CODEC_CC
video_rect_union(struct video_rect *__restrict __union,
                 struct video_rect const *__restrict __addme) {
	if (video_rect_getxmin(__union) > video_rect_getxmin(__addme))
		video_rect_setxmin(__union, video_rect_getxmin(__addme));
	if (video_rect_getymin(__union) > video_rect_getymin(__addme))
		video_rect_setymin(__union, video_rect_getymin(__addme));
	if (video_rect_getxend(__union) < video_rect_getxend(__addme))
		video_rect_setxend(__union, video_rect_getxend(__addme));
	if (video_rect_getyend(__union) < video_rect_getyend(__addme))
		video_rect_setyend(__union, video_rect_getyend(__addme));
}


/* Subtract "small" from "big", producing up to 4 smaller rects stored in "out"
 * @assume(small IS_CONTAINED_INSIDE_OF big);
 * @return: * : The # of rects written to "out". */
__LOCAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) __size_t LIBVIDEO_CODEC_CC
video_rect_subtract(struct video_rect const *__restrict big,
                    struct video_rect const *__restrict small,
                    struct video_rect out[4]) {
	__size_t result = 0;
	video_offset_t big_xend = video_rect_getxend(big);
	video_offset_t big_yend = video_rect_getyend(big);
	video_offset_t small_xend = video_rect_getxend(small);
	video_offset_t small_yend = video_rect_getyend(small);
	__hybrid_assert(video_rect_getxmin(small) >= video_rect_getxmin(big));
	__hybrid_assert(video_rect_getymin(small) >= video_rect_getymin(big));
	__hybrid_assert(small_xend <= big_xend);
	__hybrid_assert(small_yend <= big_yend);
	__hybrid_assert(video_rect_getxdim(small));
	__hybrid_assert(video_rect_getydim(small));
	__hybrid_assert(video_rect_getxdim(big));
	__hybrid_assert(video_rect_getydim(big));

	/* Top row */
	if (video_rect_getymin(small) > video_rect_getymin(big)) {
		video_rect_setxmin(&out[result], video_rect_getxmin(big));
		video_rect_setymin(&out[result], video_rect_getymin(big));
		video_rect_setxdim(&out[result], video_rect_getxdim(big));
		video_rect_setyend(&out[result], video_rect_getymin(small));
		++result;
	}

	/* Bottom row */
	if (small_yend < big_yend) {
		video_rect_setxmin(&out[result], video_rect_getxmin(big));
		video_rect_setymin(&out[result], small_yend);
		video_rect_setxdim(&out[result], video_rect_getxdim(big));
		video_rect_setyend(&out[result], big_yend);
		++result;
	}

	/* Left column (w/ top/bottom row removed) */
	if (video_rect_getxmin(small) > video_rect_getxmin(big)) {
		video_rect_setxmin(&out[result], video_rect_getxmin(big));
		video_rect_setymin(&out[result], video_rect_getymin(small));
		video_rect_setxend(&out[result], video_rect_getxmin(small));
		video_rect_setyend(&out[result], small_yend);
		++result;
	}

	/* Left column (w/ top/bottom row removed) */
	if (small_xend < big_xend) {
		video_rect_setxmin(&out[result], small_xend);
		video_rect_setymin(&out[result], video_rect_getymin(small));
		video_rect_setxend(&out[result], big_xend);
		video_rect_setyend(&out[result], small_yend);
		++result;
	}
	return result;
}




__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_CODEC_RECTUTILS_H */
