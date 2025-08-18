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
#ifndef _LIBVIDEO_CLINE_H
#define _LIBVIDEO_CLINE_H 1

#include <__stdinc.h>

#include "types.h"
#include "cpoint.h"

#define __OFFSET_VIDEO_CLINE_P0 0
#define __OFFSET_VIDEO_CLINE_P1 __SIZEOF_VIDEO_CPOINT
#define __SIZEOF_VIDEO_CLINE    (2 * __SIZEOF_VIDEO_CPOINT)
#define __ALIGNOF_VIDEO_CLINE   __ALIGNOF_VIDEO_CPOINT

#ifdef __CC__
__DECL_BEGIN

struct video_cline {
	/* NOTE: Video lines are always sorted such that "vcl_p0" comes
	 *       before "vcl_p1" when interpreted as a line in a linear
	 *       frame buffer (iow: sorting is done as [Y ASC, X ASC])
	 *
	 * @assume(video_cpoint_gety(&vcl_p0) <= video_cpoint_gety(&vcl_p1));
	 * @assume((video_cpoint_getx(&vcl_p0) <= video_cpoint_getx(&vcl_p1)) ||
	 *         (video_cpoint_gety(&vcl_p0) != video_cpoint_gety(&vcl_p1))); */
	struct video_cpoint vcl_p0; /* First line point */
	struct video_cpoint vcl_p1; /* Second line point */
};

#define VIDEO_CLINE_INIT(x0, y0, x1, y1) { { x0, y0 }, { x1, y1 } }

#define video_cline_getp0x(self) ((self)->vcl_p0.vcp_x)
#define video_cline_getp0y(self) ((self)->vcl_p0.vcp_y)
#define video_cline_getp1x(self) ((self)->vcl_p1.vcp_x)
#define video_cline_getp1y(self) ((self)->vcl_p1.vcp_y)

#define video_cline_getxdim(self) (video_dim_t)((video_cline_getp1x(self) >= video_cline_getp0x(self)) ? (video_cline_getp1x(self) - video_cline_getp0x(self)) : (video_cline_getp0x(self) - video_cline_getp1x(self)))
#define video_cline_getydim(self) (video_dim_t)(video_cline_getp1y(self) - video_cline_getp0y(self))

#define video_cline_getxres(self) (video_cline_getp1x(self) - video_cline_getp0x(self))
#define video_cline_getyres(self) (video_cline_getp1y(self) - video_cline_getp0y(self))

/* Find the X value where `__self' intersects with a horizontal plane at `__y' */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t
video_cline_getxat_fast(struct video_cline const *__restrict __self, video_offset_t __y) {
	video_offset_t __yoff = (video_offset_t)video_cline_getp0y(__self) - __y; // -1
	video_dim_t __ydim = video_cline_getydim(__self); // 100
	video_offset_t __result = (video_offset_t)(((__INT_FAST64_TYPE__)__yoff * video_cline_getxres(__self)) / __ydim);
	return video_cline_getp0x(__self) + __result;
}
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t
video_cline_getxat(struct video_cline const *__restrict __self, video_offset_t __y) {
	video_offset_t __yoff = video_cline_getp0y(__self) - __y;
	video_dim_t __ydim = video_cline_getydim(__self);
	video_offset_t __result;
	if __unlikely(__ydim == 0)
		return VIDEO_OFFSET_MAX;
	__result = (video_offset_t)(((__INT_FAST64_TYPE__)__yoff * video_cline_getxres(__self)) / __ydim);
	return video_cline_getp0x(__self) + __result;
}

/* Find the Y value where `__self' intersects with a vertical plane at `__x' */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t
video_cline_getyat(struct video_cline const *__restrict __self, video_offset_t __x) {
	struct video_cpoint const *__lox = &__self->vcl_p0;
	struct video_cpoint const *__hix = &__self->vcl_p1;
	video_offset_t __xoff;
	video_dim_t __xdim;
	if (video_cpoint_getx(__lox) > video_cpoint_getx(__hix)) {
		__lox = &__self->vcl_p1;
		__hix = &__self->vcl_p0;
	} else if (video_cpoint_getx(__lox) == video_cpoint_getx(__hix)) {
		return VIDEO_OFFSET_MAX;
	}
	__xoff = video_cpoint_getx(__lox) - __x;
	__xdim = (video_dim_t)(video_cpoint_getx(__hix) - video_cpoint_getx(__lox));
	return (video_offset_t)(((__INT_FAST64_TYPE__)__xoff * video_cline_getyres(__self)) / __xdim);
}

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_CLINE_H */
