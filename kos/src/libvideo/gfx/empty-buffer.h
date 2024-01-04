/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVIDEO_GFX_EMPTY_BUFFER_H
#define GUARD_LIBVIDEO_GFX_EMPTY_BUFFER_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include "buffer.h"

DECL_BEGIN

INTDEF ATTR_CONST NONNULL((1)) video_color_t CC video_gfx_empty_getcolor(struct video_gfx const *__restrict self, uintptr_t x, uintptr_t y);
INTDEF NONNULL((1)) void CC video_gfx_empty_putcolor(struct video_gfx *__restrict self, uintptr_t x, uintptr_t y, video_color_t color);

/* Return GFX operators for an empty video buffer. */
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops *CC libvideo_getemptygfxops(void);

/* Return operators for an empty video buffer. */
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC libvideo_getemptybufferops(void);

/* Return the empty video buffer. */
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer *CC libvideo_getemptybuffer(void);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_EMPTY_BUFFER_H */
