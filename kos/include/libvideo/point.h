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
#ifndef _LIBVIDEO_POINT_H
#define _LIBVIDEO_POINT_H 1

#include <__stdinc.h>

#include "types.h"

#define __OFFSET_VIDEO_POINT_X 0
#define __OFFSET_VIDEO_POINT_Y __SIZEOF_VIDEO_OFFSET_T__
#define __SIZEOF_VIDEO_POINT   (2 * __SIZEOF_VIDEO_OFFSET_T__)
#define __ALIGNOF_VIDEO_POINT  __ALIGNOF_VIDEO_OFFSET_T__

#ifdef __CC__
__DECL_BEGIN

struct video_point {
	video_offset_t vp_x; /* X offset */
	video_offset_t vp_y; /* Y offset */
};

#define VIDEO_POINT_INIT(x, y) { x, y }

#ifdef __INTELLISENSE__
/* Getters for properties of `struct video_point' */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_point_getx(struct video_point const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_offset_t video_point_gety(struct video_point const *__restrict __self);

/* Setters for properties of `struct video_point' */
extern __ATTR_INOUT(1) void video_point_setx(struct video_point *__restrict __self, video_offset_t __v);
extern __ATTR_INOUT(1) void video_point_sety(struct video_point *__restrict __self, video_offset_t __v);

/* Add an X or Y delta offset of `__self' */
extern __ATTR_INOUT(1) void video_point_addx(struct video_point *__restrict __self, video_offset_t __v);
extern __ATTR_INOUT(1) void video_point_addy(struct video_point *__restrict __self, video_offset_t __v);
#else /* __INTELLISENSE__ */
#define video_point_getx(self)    (self)->vp_x
#define video_point_gety(self)    (self)->vp_y
#define video_point_setx(self, v) (void)((self)->vp_x = (v))
#define video_point_sety(self, v) (void)((self)->vp_y = (v))
#define video_point_addx(self, v) (void)((self)->vp_x += (v))
#define video_point_addy(self, v) (void)((self)->vp_y += (v))
#endif /* !__INTELLISENSE__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_POINT_H */
