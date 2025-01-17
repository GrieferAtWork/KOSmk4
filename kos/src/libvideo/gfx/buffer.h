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

#include <kos/types.h>

#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

DECL_BEGIN

/* Create a video buffer, or return NULL and set errno if creation failed.
 * NOTE: When the given `size_x' or `size_y' is ZERO(0), an empty buffer is returned
 *       which may not necessarily use the  given, or default `codec' and  `palette'
 * @param: codec:   The preferred video codec, or NULL to use `video_preferred_format()'.
 * @param: palette: The palette to use (only needed if used by `codec') */
INTDEF WUNUSED /*REF*/ struct video_buffer *CC
libvideo_buffer_create(unsigned int type, size_t size_x, size_t size_y,
                       struct video_codec const *codec, struct video_palette *palette);

/* Returns a video buffer for the entire screen (or return NULL and set errno on error)
 * Note that  screen buffer  access  is only  granted to  ROOT  and the  window  server */
INTDEF WUNUSED /*REF*/ struct video_buffer *CC libvideo_buffer_screen(void);

/* Return a handle for the video device driver that is being used.
 * @return: -1:errno=ENODEV: No video driver found */
INTDEF WUNUSED fd_t LIBVIDEO_GFX_CC libvideo_driver(void);


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_H */
