/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVIDEO_CODEC_PALETTE_H
#define GUARD_LIBVIDEO_CODEC_PALETTE_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libvideo/codec/palette.h>

DECL_BEGIN

/* Return the best-matching pixel for a given color.
 * For the purpose of determining the best match, this algorithm
 * leans towards emphasizing colors best viewed by the human eye,
 * thus producing the best-looking results for those bipedal fellas.
 * NOTE: If the given `color' is one of `VIDEO_COLOR_*', `vp_colors'
 *       is used to quickly lookup the associated palette index.
 *       If the associated index is set to `(size_t)-1', the index
 *       will be calculated like any other color given would, and
 *       the result will be cached within the `vp_colors' vector. */
INTDEF NONNULL((1)) video_pixel_t CC
libvideo_palette_getpixel(struct video_palette *__restrict self,
                          video_color_t color);


DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_PALETTE_H */
