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
#ifndef GUARD_LIBVIDEO_GFX_GFX_PALETTIZE_H
#define GUARD_LIBVIDEO_GFX_GFX_PALETTIZE_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <libvideo/codec/types.h>
#include <libvideo/gfx/gfx.h>

DECL_BEGIN

/* Construct a (visually pleasing) palette from the pixel area denoted
 * by the I/O region of `self'. The produced palette is stored in  the
 * provided buffer `pal' and consists of exactly `palsize' colors.
 * @param: method: How to calculate the palette
 * @return: 0 : Success
 * @return: -1: [errno=ENOMEM] Insufficient memory for temporaries needed during calculation
 * @return: -1: [errno=EINVAL] Attempted to use "VIDEO_GFX_PALETTIZE_METHOD_F_ALPHA" with
 *                             a  palettization method that doesn't support alpha values.
 * @return: -1: [errno=EINVAL] Invalid `method' and/or `palsize' */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUTS(3, 2) int CC
libvideo_gfx_palettize(struct video_gfx const *__restrict self,
                       video_pixel_t palsize, video_color_t *pal,
                       unsigned int method);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_PALETTIZE_H */
