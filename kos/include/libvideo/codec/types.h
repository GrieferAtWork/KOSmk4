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

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include "api.h"

#define __SIZEOF_VIDEO_OFFSET_T__ __SIZEOF_INT_FAST32_T__
#define __SIZEOF_VIDEO_COORD_T__  __SIZEOF_INT_FAST32_T__
#define __SIZEOF_VIDEO_DIM_T__    __SIZEOF_INT_FAST32_T__

#ifdef __CC__
__DECL_BEGIN

typedef __INT_FAST32_TYPE__ video_offset_t; /* Pixel offset (usually relative to some GFX context) */
typedef __UINT_FAST32_TYPE__ video_coord_t; /* Pixel coordinate (usually absolute) */
typedef __UINT_FAST32_TYPE__ video_dim_t;   /* Graphic dimension (in pixels) */
#define VIDEO_DIM_MAX ((video_dim_t)-1)

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_CODEC_TYPES_H */
