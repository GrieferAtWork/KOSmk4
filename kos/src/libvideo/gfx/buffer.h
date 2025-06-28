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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_H
#define GUARD_LIBVIDEO_GFX_BUFFER_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

DECL_BEGIN

/* Generic implementations for video buffer operators. */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_buffer_generic_updategfx(struct video_gfx *__restrict self, unsigned int what);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
libvideo_buffer_generic_noblend(struct video_gfx *__restrict self);



/* Convert `self' into the specified format.
 * @param: type: The type of buffer to-be returned (one of `VIDEO_BUFFER_*'). */
INTDEF WUNUSED NONNULL((1, 2)) REF struct video_buffer *CC
libvideo_buffer_convert(struct video_buffer *__restrict self,
                        struct video_codec const *codec,
                        struct video_palette *palette,
                        unsigned int type);

/* Create a video buffer, or return NULL and set errno if creation failed.
 * NOTE: When the given `size_x' or `size_y' is ZERO(0), an empty buffer is returned
 *       which may not necessarily use the  given, or default `codec' and  `palette'
 * @param: codec:   The preferred video codec, or NULL to use `video_preferred_format()'.
 * @param: palette: The palette to use (only needed if used by `codec') */
INTDEF WUNUSED REF struct video_buffer *CC
libvideo_buffer_create(unsigned int type, video_dim_t size_x, video_dim_t size_y,
                       struct video_codec const *codec, struct video_palette *palette);

/* Return the preferred video format.
 * If  possible, this format will match the format used by the host's graphics card.
 * If no graphics card exists, or the card isn't clear on its preferred format, some
 * other, common format will be returned instead. */
INTDEF ATTR_RETNONNULL WUNUSED struct video_format const *CC libvideo_preferred_format(void);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_H */
