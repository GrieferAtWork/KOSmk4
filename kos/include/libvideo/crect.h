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
#ifndef _LIBVIDEO_CRECT_H
#define _LIBVIDEO_CRECT_H 1

#include <__stdinc.h>

#include "types.h"

#define __OFFSET_VIDEO_CRECT_XMIN 0
#define __OFFSET_VIDEO_CRECT_YMIN __SIZEOF_VIDEO_COORD_T__
#define __OFFSET_VIDEO_CRECT_XDIM (2 * __SIZEOF_VIDEO_COORD_T__)
#define __OFFSET_VIDEO_CRECT_YDIM (2 * __SIZEOF_VIDEO_COORD_T__ + __SIZEOF_VIDEO_DIM_T__)
#define __SIZEOF_VIDEO_CRECT      (2 * __SIZEOF_VIDEO_COORD_T__ + 2 * __SIZEOF_VIDEO_DIM_T__)
#define __ALIGNOF_VIDEO_CRECT     (__ALIGNOF_VIDEO_COORD_T__ > __ALIGNOF_VIDEO_DIM_T__ ? __ALIGNOF_VIDEO_COORD_T__ : __ALIGNOF_VIDEO_DIM_T__)

#ifdef __CC__
__DECL_BEGIN

struct video_crect {
	video_coord_t vcr_xmin; /* Starting X coord */
	video_coord_t vcr_ymin; /* Starting Y coord */
	video_dim_t   vcr_xdim; /* Rect size in X */
	video_dim_t   vcr_ydim; /* Rect size in Y */
};

#define VIDEO_CRECT_INIT(xmin, xmax, xdim, ydim) { xmin, xmax, xdim, ydim }
#define VIDEO_CRECT_INIT_FULL VIDEO_CRECT_INIT(0, 0, VIDEO_DIM_MAX, VIDEO_DIM_MAX)

#ifdef __INTELLISENSE__
/* Getters for properties of `struct video_crect' */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_crect_getxmin(struct video_crect const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_crect_getymin(struct video_crect const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_crect_getxdim(struct video_crect const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_crect_getydim(struct video_crect const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_crect_getxend(struct video_crect const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_crect_getyend(struct video_crect const *__restrict __self);

/* Setters for properties of `struct video_crect' */
extern __ATTR_INOUT(1) void video_crect_setxmin(struct video_crect *__restrict __self, video_offset_t __v);
extern __ATTR_INOUT(1) void video_crect_setymin(struct video_crect *__restrict __self, video_offset_t __v);
extern __ATTR_INOUT(1) void video_crect_setxdim(struct video_crect *__restrict __self, video_dim_t __v);
extern __ATTR_INOUT(1) void video_crect_setydim(struct video_crect *__restrict __self, video_dim_t __v);
extern __ATTR_INOUT(1) void video_crect_setxend(struct video_crect *__restrict __self, video_offset_t __v);
extern __ATTR_INOUT(1) void video_crect_setyend(struct video_crect *__restrict __self, video_offset_t __v);

/* Add an X or Y delta offset of `__self' */
extern __ATTR_INOUT(1) void video_crect_addx(struct video_crect *__restrict __self, video_offset_t __v);
extern __ATTR_INOUT(1) void video_crect_addy(struct video_crect *__restrict __self, video_offset_t __v);

/* Check if `__self' is an empty rect */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_crect_isempty(struct video_crect const *__restrict __self);

/* Check if {__x,__y} is contained within "__self" */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL
video_crect_contains(struct video_crect const *__restrict __self,
                    video_offset_t __x, video_offset_t __y);

/* Check if 2 rects overlap (`video_crect_intersect()' would return true) */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __BOOL
video_crect_intersects(struct video_crect const *__a,
                      struct video_crect const *__b);
#else /* __INTELLISENSE__ */
#define video_crect_getxmin(self)    (self)->vcr_xmin
#define video_crect_getymin(self)    (self)->vcr_ymin
#define video_crect_getxdim(self)    (self)->vcr_xdim
#define video_crect_getydim(self)    (self)->vcr_ydim
#define video_crect_getxend(self)    ((self)->vcr_xmin + (self)->vcr_xdim)
#define video_crect_getyend(self)    ((self)->vcr_ymin + (self)->vcr_ydim)
#define video_crect_setxmin(self, v) (void)((self)->vcr_xmin = (v))
#define video_crect_setymin(self, v) (void)((self)->vcr_ymin = (v))
#define video_crect_setxdim(self, v) (void)((self)->vcr_xdim = (v))
#define video_crect_setydim(self, v) (void)((self)->vcr_ydim = (v))
#define video_crect_setxend(self, v) (void)((self)->vcr_xdim = (video_dim_t)((v) - (self)->vcr_xmin))
#define video_crect_setyend(self, v) (void)((self)->vcr_ydim = (video_dim_t)((v) - (self)->vcr_ymin))
#define video_crect_addx(self, v)    (void)((self)->vcr_xmin += (v))
#define video_crect_addy(self, v)    (void)((self)->vcr_ymin += (v))
#define video_crect_isempty(self)    ((self)->vcr_xdim == 0 || (self)->vcr_ydim == 0)
#define video_crect_contains(self, x, y)                                    \
	((x) >= video_crect_getxmin(self) && (x) < video_crect_getxend(self) && \
	 (y) >= video_crect_getymin(self) && (y) < video_crect_getyend(self))
#define video_crect_intersects(a, b)                                                                       \
	(video_crect_getxmin(a) < video_crect_getxend(b) && video_crect_getxend(a) > video_crect_getxmin(b) && \
	 video_crect_getymin(a) < video_crect_getyend(b) && video_crect_getyend(a) > video_crect_getymin(b))
#endif /* !__INTELLISENSE__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_CRECT_H */
