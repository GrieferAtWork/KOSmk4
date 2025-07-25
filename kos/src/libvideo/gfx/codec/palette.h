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
#ifndef GUARD_LIBVIDEO_GFX_CODEC_PALETTE_H
#define GUARD_LIBVIDEO_GFX_CODEC_PALETTE_H 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <libvideo/color.h>
#include <libvideo/gfx/codec/palette.h>

DECL_BEGIN

/* Generic (slow/fallback) pixel->color conversion function */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
libvideo_palette_color2pixel_generic(struct video_palette const *__restrict self,
                                     video_pixel_t n_colors, video_color_t color);

/* Generic palette object creator (used by ramdomain) */
INTDEF WUNUSED NONNULL((1)) REF struct video_palette *CC
libvideo_generic_palette_create(struct video_domain const *__restrict domain,
                                video_pixel_t count);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_CODEC_PALETTE_H */
