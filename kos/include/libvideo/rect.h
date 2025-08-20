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
#ifndef _LIBVIDEO_RECT_H
#define _LIBVIDEO_RECT_H 1

#include <__stdinc.h>

#include <hybrid/__assert.h>
#include <hybrid/__minmax.h>
#include <hybrid/__overflow.h>

#include <bits/types.h>

#include "types.h"

#define __OFFSET_VIDEO_RECT_XMIN 0
#define __OFFSET_VIDEO_RECT_YMIN __SIZEOF_VIDEO_OFFSET_T__
#define __OFFSET_VIDEO_RECT_XDIM (2 * __SIZEOF_VIDEO_OFFSET_T__)
#define __OFFSET_VIDEO_RECT_YDIM (2 * __SIZEOF_VIDEO_OFFSET_T__ + __SIZEOF_VIDEO_DIM_T__)
#define __SIZEOF_VIDEO_RECT      (2 * __SIZEOF_VIDEO_OFFSET_T__ + 2 * __SIZEOF_VIDEO_DIM_T__)
#define __ALIGNOF_VIDEO_RECT     (__ALIGNOF_VIDEO_OFFSET_T__ > __ALIGNOF_VIDEO_DIM_T__ ? __ALIGNOF_VIDEO_OFFSET_T__ : __ALIGNOF_VIDEO_DIM_T__)

#ifdef __CC__
__DECL_BEGIN

struct video_rect {
	video_offset_t vr_xmin; /* Starting X offset */
	video_offset_t vr_ymin; /* Starting Y offset */
	video_dim_t    vr_xdim; /* Rect size in X */
	video_dim_t    vr_ydim; /* Rect size in Y */
};
#define VIDEO_RECT_INIT(xmin, xmax, xdim, ydim) { xmin, xmax, xdim, ydim }
#define VIDEO_RECT_INIT_FULL VIDEO_RECT_INIT(0, 0, VIDEO_DIM_MAX, VIDEO_DIM_MAX)

#ifdef __INTELLISENSE__
/* Getters for properties of `struct video_rect' */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_rect_getxmin(struct video_rect const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_rect_getymin(struct video_rect const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_rect_getxdim(struct video_rect const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_rect_getydim(struct video_rect const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_rect_getxend(struct video_rect const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_rect_getyend(struct video_rect const *__restrict __self);

/* Setters for properties of `struct video_rect' */
extern __ATTR_INOUT(1) void video_rect_setxmin(struct video_rect *__restrict __self, video_offset_t __v);
extern __ATTR_INOUT(1) void video_rect_setymin(struct video_rect *__restrict __self, video_offset_t __v);
extern __ATTR_INOUT(1) void video_rect_setxdim(struct video_rect *__restrict __self, video_dim_t __v);
extern __ATTR_INOUT(1) void video_rect_setydim(struct video_rect *__restrict __self, video_dim_t __v);
extern __ATTR_INOUT(1) void video_rect_setxend(struct video_rect *__restrict __self, video_offset_t __v);
extern __ATTR_INOUT(1) void video_rect_setyend(struct video_rect *__restrict __self, video_offset_t __v);

/* Add an X or Y delta offset of `__self' */
extern __ATTR_INOUT(1) void video_rect_addx(struct video_rect *__restrict __self, video_offset_t __v);
extern __ATTR_INOUT(1) void video_rect_addy(struct video_rect *__restrict __self, video_offset_t __v);

/* Check if `__self' is an empty rect */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_rect_isempty(struct video_rect const *__restrict __self);

/* Check if {__x,__y} is contained within "__self" */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL
video_rect_contains(struct video_rect const *__restrict __self,
                    video_offset_t __x, video_offset_t __y);

/* Check if 2 rects overlap (`video_rect_intersect()' would return true) */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __BOOL
video_rect_intersects(struct video_rect const *__a,
                      struct video_rect const *__b);
#else /* __INTELLISENSE__ */
#define video_rect_getxmin(self)    (self)->vr_xmin
#define video_rect_getymin(self)    (self)->vr_ymin
#define video_rect_getxdim(self)    (self)->vr_xdim
#define video_rect_getydim(self)    (self)->vr_ydim
#define video_rect_getxend(self)    (video_offset_t)((self)->vr_xmin + (self)->vr_xdim)
#define video_rect_getyend(self)    (video_offset_t)((self)->vr_ymin + (self)->vr_ydim)
#define video_rect_setxmin(self, v) (void)((self)->vr_xmin = (v))
#define video_rect_setymin(self, v) (void)((self)->vr_ymin = (v))
#define video_rect_setxdim(self, v) (void)((self)->vr_xdim = (v))
#define video_rect_setydim(self, v) (void)((self)->vr_ydim = (v))
#define video_rect_setxend(self, v) (void)((self)->vr_xdim = (video_dim_t)((v) - (self)->vr_xmin))
#define video_rect_setyend(self, v) (void)((self)->vr_ydim = (video_dim_t)((v) - (self)->vr_ymin))
#define video_rect_addx(self, v)    (void)((self)->vr_xmin += (v))
#define video_rect_addy(self, v)    (void)((self)->vr_ymin += (v))
#define video_rect_isempty(self)    ((self)->vr_xdim == 0 || (self)->vr_ydim == 0)
#define video_rect_contains(self, x, y)                                   \
	((x) >= video_rect_getxmin(self) && (x) < video_rect_getxend(self) && \
	 (y) >= video_rect_getymin(self) && (y) < video_rect_getyend(self))
#define video_rect_intersects(a, b)                                                                    \
	(video_rect_getxmin(a) < video_rect_getxend(b) && video_rect_getxend(a) > video_rect_getxmin(b) && \
	 video_rect_getymin(a) < video_rect_getyend(b) && video_rect_getyend(a) > video_rect_getymin(b))
#endif /* !__INTELLISENSE__ */


/* Check if "a" and "b" intersect, and if so: store that intersection and return true */
__LOCAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) __BOOL
video_rect_intersect(struct video_rect const *__a,
                     struct video_rect const *__b,
                     struct video_rect *__intersect) {
	video_offset_t __a_xend = video_rect_getxend(__a);
	video_offset_t __a_yend = video_rect_getyend(__a);
	video_offset_t __b_xend = video_rect_getxend(__b);
	video_offset_t __b_yend = video_rect_getyend(__b);
	video_offset_t __intersect_xend = __hybrid_min(__a_xend, __b_xend);
	video_offset_t __intersect_yend = __hybrid_min(__a_yend, __b_yend);
	video_rect_setxmin(__intersect, __hybrid_max(video_rect_getxmin(__a), video_rect_getxmin(__b)));
	video_rect_setymin(__intersect, __hybrid_max(video_rect_getymin(__a), video_rect_getymin(__b)));
	if (video_rect_getxmin(__intersect) < __intersect_xend &&
	    video_rect_getymin(__intersect) < __intersect_yend) {
		video_rect_setxend(__intersect, __intersect_xend);
		video_rect_setyend(__intersect, __intersect_yend);
		return 1;
	}
	return 0;
}

/* Same as `video_rect_intersect()', but safely handles overflow in "__b" */
__LOCAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) __BOOL
video_rect_intersect_overflow_in_b(struct video_rect const *__a,
                                   struct video_rect const *__b,
                                   struct video_rect *__intersect) {
	video_offset_t __b_xend, __b_yend, __intersect_xend, __intersect_yend;
	video_offset_t __a_xend = video_rect_getxend(__a);
	video_offset_t __a_yend = video_rect_getyend(__a);
	if (__hybrid_overflow_sadd(video_rect_getxmin(__b), video_rect_getxdim(__b), &__b_xend))
		__b_xend = VIDEO_OFFSET_MAX;
	if (__hybrid_overflow_sadd(video_rect_getymin(__b), video_rect_getydim(__b), &__b_yend))
		__b_yend = VIDEO_OFFSET_MAX;
	__intersect_xend = __hybrid_min(__a_xend, __b_xend);
	__intersect_yend = __hybrid_min(__a_yend, __b_yend);
	video_rect_setxmin(__intersect, __hybrid_max(video_rect_getxmin(__a), video_rect_getxmin(__b)));
	video_rect_setymin(__intersect, __hybrid_max(video_rect_getymin(__a), video_rect_getymin(__b)));
	if (video_rect_getxmin(__intersect) < __intersect_xend && video_rect_getymin(__intersect) < __intersect_yend) {
		video_rect_setxend(__intersect, __intersect_xend);
		video_rect_setyend(__intersect, __intersect_yend);
		return 1;
	}
	return 0;
}


__LOCAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) __BOOL
video_rect_intersect_overflow(struct video_rect const *__a,
                              struct video_rect const *__b,
                              struct video_rect *__intersect) {
	video_offset_t __a_xend, __a_yend, __b_xend, __b_yend, __intersect_xend, __intersect_yend;
	if (__hybrid_overflow_sadd(video_rect_getxmin(__a), video_rect_getxdim(__a), &__a_xend))
		__a_xend = VIDEO_OFFSET_MAX;
	if (__hybrid_overflow_sadd(video_rect_getymin(__a), video_rect_getydim(__a), &__a_yend))
		__a_yend = VIDEO_OFFSET_MAX;
	if (__hybrid_overflow_sadd(video_rect_getxmin(__b), video_rect_getxdim(__b), &__b_xend))
		__b_xend = VIDEO_OFFSET_MAX;
	if (__hybrid_overflow_sadd(video_rect_getymin(__b), video_rect_getydim(__b), &__b_yend))
		__b_yend = VIDEO_OFFSET_MAX;
	__intersect_xend = __hybrid_min(__a_xend, __b_xend);
	__intersect_yend = __hybrid_min(__a_yend, __b_yend);
	video_rect_setxmin(__intersect, __hybrid_max(video_rect_getxmin(__a), video_rect_getxmin(__b)));
	video_rect_setymin(__intersect, __hybrid_max(video_rect_getymin(__a), video_rect_getymin(__b)));
	if (video_rect_getxmin(__intersect) < __intersect_xend && video_rect_getymin(__intersect) < __intersect_yend) {
		video_rect_setxend(__intersect, __intersect_xend);
		video_rect_setyend(__intersect, __intersect_yend);
		return 1;
	}
	return 0;
}


/* Update `__union' by adding `__addme' */
__LOCAL __ATTR_INOUT(1) __ATTR_IN(2) void
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


/* Subtract "__small" from "__big", producing up to 4 smaller rects stored in "___out"
 * @assume(!video_rect_isempty(__big));
 * @assume(!video_rect_isempty(__small));
 * @assume(__small IS_CONTAINED_INSIDE_OF __big);
 * @return: * : The # of rects written to "___out". */
__LOCAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) __size_t
video_rect_subtract(struct video_rect const *__restrict __big,
                    struct video_rect const *__restrict __small,
                    struct video_rect ___out[4]) {
	__size_t __result = 0;
	video_offset_t __big_xend = video_rect_getxend(__big);
	video_offset_t __big_yend = video_rect_getyend(__big);
	video_offset_t __small_xend = video_rect_getxend(__small);
	video_offset_t __small_yend = video_rect_getyend(__small);
	__hybrid_assert(video_rect_getxmin(__small) >= video_rect_getxmin(__big));
	__hybrid_assert(video_rect_getymin(__small) >= video_rect_getymin(__big));
	__hybrid_assert(__small_xend <= __big_xend);
	__hybrid_assert(__small_yend <= __big_yend);
	__hybrid_assert(video_rect_getxdim(__small));
	__hybrid_assert(video_rect_getydim(__small));
	__hybrid_assert(video_rect_getxdim(__big));
	__hybrid_assert(video_rect_getydim(__big));

	/* Top row */
	if (video_rect_getymin(__small) > video_rect_getymin(__big)) {
		video_rect_setxmin(&___out[__result], video_rect_getxmin(__big));
		video_rect_setymin(&___out[__result], video_rect_getymin(__big));
		video_rect_setxdim(&___out[__result], video_rect_getxdim(__big));
		video_rect_setyend(&___out[__result], video_rect_getymin(__small));
		++__result;
	}

	/* Bottom row */
	if (__small_yend < __big_yend) {
		video_rect_setxmin(&___out[__result], video_rect_getxmin(__big));
		video_rect_setymin(&___out[__result], __small_yend);
		video_rect_setxdim(&___out[__result], video_rect_getxdim(__big));
		video_rect_setyend(&___out[__result], __big_yend);
		++__result;
	}

	/* Left column (w/ top/bottom row removed) */
	if (video_rect_getxmin(__small) > video_rect_getxmin(__big)) {
		video_rect_setxmin(&___out[__result], video_rect_getxmin(__big));
		video_rect_setymin(&___out[__result], video_rect_getymin(__small));
		video_rect_setxend(&___out[__result], video_rect_getxmin(__small));
		video_rect_setyend(&___out[__result], __small_yend);
		++__result;
	}

	/* Left column (w/ top/bottom row removed) */
	if (__small_xend < __big_xend) {
		video_rect_setxmin(&___out[__result], __small_xend);
		video_rect_setymin(&___out[__result], video_rect_getymin(__small));
		video_rect_setxend(&___out[__result], __big_xend);
		video_rect_setyend(&___out[__result], __small_yend);
		++__result;
	}
	return __result;
}

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_RECT_H */
