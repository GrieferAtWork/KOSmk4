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
#ifndef _LIBVIDEO_CODEC_TYPES_H
#define _LIBVIDEO_CODEC_TYPES_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/limitcore.h>
#include <hybrid/typecore.h>

/* Sizes of video types. */
#define __SIZEOF_VIDEO_OFFSET_T__ 4
#define __SIZEOF_VIDEO_COORD_T__  4
#define __SIZEOF_VIDEO_DIM_T__    4

/* The max possible value for a graphics dimension.
 *
 * This value should  be used as  "size_x" /  "size_y"
 * argument in graphics operations, when the operation
 * should reach the  right/bottom edge  of the  active
 * clip region. */
#define VIDEO_DIM_MAX    __UINT32_MAX__
#define VIDEO_COORD_MAX  __UINT32_MAX__
#define VIDEO_OFFSET_MAX __INT32_MAX__

#ifdef __CC__
__DECL_BEGIN

typedef __INT32_TYPE__ video_offset_t; /* Pixel offset (usually relative to some GFX context) */
typedef __UINT32_TYPE__ video_coord_t; /* Pixel coordinate (usually absolute) */
typedef __UINT32_TYPE__ video_dim_t;   /* Graphic dimension (in pixels) */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_CODEC_TYPES_H */
