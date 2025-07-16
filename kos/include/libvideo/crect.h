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

#define __OFFSET_VIDEO_CRECT_XMIN  0
#define __OFFSET_VIDEO_CRECT_YMIN  __SIZEOF_VIDEO_COORD_T__
#define __OFFSET_VIDEO_CRECT_XDIM  (2 * __SIZEOF_VIDEO_COORD_T__)
#define __OFFSET_VIDEO_CRECT_YDIM  (2 * __SIZEOF_VIDEO_COORD_T__ + __SIZEOF_VIDEO_DIM_T__)
#define __SIZEOF_VIDEO_CRECT_YDIM  (2 * __SIZEOF_VIDEO_COORD_T__ + 2 * __SIZEOF_VIDEO_DIM_T__)
#define __ALIGNOF_VIDEO_CRECT_YDIM (__ALIGNOF_VIDEO_COORD_T__ > __ALIGNOF_VIDEO_DIM_T__ ? __ALIGNOF_VIDEO_COORD_T__ : __ALIGNOF_VIDEO_DIM_T__)

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

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_CRECT_H */
