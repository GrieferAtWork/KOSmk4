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
#ifndef _LIBVIDEO_LINE_H
#define _LIBVIDEO_LINE_H 1

#include <__stdinc.h>

#include "types.h"
#include "point.h"

#define __OFFSET_VIDEO_LINE_P0 0
#define __OFFSET_VIDEO_LINE_P1 __SIZEOF_VIDEO_POINT
#define __SIZEOF_VIDEO_LINE    (2 * __SIZEOF_VIDEO_POINT)
#define __ALIGNOF_VIDEO_LINE   __ALIGNOF_VIDEO_POINT

#ifdef __CC__
__DECL_BEGIN

struct video_line {
	/* NOTE: Video lines are always sorted such that "vl_p0" comes
	 *       before "vl_p1" when interpreted as a line in a linear
	 *       frame buffer (iow: sorting is done as [Y ASC, X ASC])
	 *
	 * @assume(video_point_gety(&vl_p0) <= video_point_gety(&vl_p1));
	 * @assume((video_point_getx(&vl_p0) <= video_point_getx(&vl_p1)) ||
	 *         (video_point_gety(&vl_p0) != video_point_gety(&vl_p1))); */
	struct video_point vl_p0; /* First line point */
	struct video_point vl_p1; /* Second line point */
};

#define VIDEO_LINE_INIT(x1, y1, x2, y2) { { x1, y1 }, { x2, y2 } }

#define video_line_getp0x(self) ((self)->vl_p0.vp_x)
#define video_line_getp0y(self) ((self)->vl_p0.vp_y)
#define video_line_getp1x(self) ((self)->vl_p1.vp_x)
#define video_line_getp1y(self) ((self)->vl_p1.vp_y)

#define video_line_getxdim(self) (video_dim_t)((video_line_getp1x(self) >= video_line_getp0x(self)) ? (video_line_getp1x(self) - video_line_getp0x(self)) : (video_line_getp0x(self) - video_line_getp1x(self)))
#define video_line_getydim(self) (video_dim_t)(video_line_getp1y(self) - video_line_getp0y(self))

#define video_line_getxres(self) (video_line_getp1x(self) - video_line_getp0x(self))
#define video_line_getyres(self) (video_line_getp1y(self) - video_line_getp0y(self))

/* Find the X value where `__self' intersects with a horizontal plane at `__y' */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t
video_line_getxat_fast(struct video_line const *__restrict __self, video_offset_t __y) {
	video_offset_t __yoff = video_line_getp0y(__self) - __y;
	video_dim_t __ydim = video_line_getydim(__self);
	video_offset_t __result = (video_offset_t)(((__INT_FAST64_TYPE__)__yoff * video_line_getxres(__self)) / __ydim);
	return video_line_getp0x(__self) + __result;
}
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t
video_line_getxat(struct video_line const *__restrict __self, video_offset_t __y) {
	video_offset_t __yoff = video_line_getp0y(__self) - __y;
	video_dim_t __ydim = video_line_getydim(__self);
	video_offset_t __result;
	if __unlikely(__ydim == 0)
		return VIDEO_OFFSET_MAX;
	__result = (video_offset_t)(((__INT_FAST64_TYPE__)__yoff * video_line_getxres(__self)) / __ydim);
	return video_line_getp0x(__self) + __result;
}

/* Find the Y value where `__self' intersects with a vertical plane at `__x' */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t
video_line_getyat(struct video_line const *__restrict __self, video_offset_t __x) {
	struct video_point const *__lox = &__self->vl_p0;
	struct video_point const *__hix = &__self->vl_p1;
	video_offset_t __xoff;
	video_dim_t __xdim;
	if (video_point_getx(__lox) > video_point_getx(__hix)) {
		__lox = &__self->vl_p1;
		__hix = &__self->vl_p0;
	} else if (video_point_getx(__lox) == video_point_getx(__hix)) {
		return VIDEO_OFFSET_MAX;
	}
	__xoff = video_point_getx(__lox) - __x;
	__xdim = (video_dim_t)(video_point_getx(__hix) - video_point_getx(__lox));
	return (video_offset_t)(((__INT_FAST64_TYPE__)__xoff * video_line_getyres(__self)) / __xdim);
}

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_LINE_H */
