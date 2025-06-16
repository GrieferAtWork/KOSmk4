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
#ifndef GUARD_LIBVIDEO_CODEC_PALETTE_H
#define GUARD_LIBVIDEO_CODEC_PALETTE_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <stddef.h>

#include <libvideo/codec/palette.h>

DECL_BEGIN

/* Create a new (uninitialized) palette for `count' colors.
 *
 * This function is allowed to allocate a larger palette  than
 * requested if doing  so improves  performances, though  when
 * this is done, all additional palette entries will have been
 * initialized to `0'
 *
 * On success, the caller must initialize:
 * - return->vp_pal[0]
 * - return->vp_pal[1]
 * - ...
 * - return->vp_pal[count - 2]
 * - return->vp_pal[count - 1]
 *
 * @return: * :   The newly created palette
 * @return: NULL: Out of memory */
INTDEF WUNUSED REF struct video_palette *CC
libvideo_palette_create(size_t count);


/* Optimize lookup times for `self', making `self->vp_color2pixel'
 * execute in sub-linear time (if possible). This function must be
 * called whenever `vp_pal' was  modified, and was called  before.
 * Prior  to being called, `self->vp_color2pixel' still works, but
 * executed in linear time (so you really want to call this one to
 * speed up palette lookups)
 *
 * This  function  is NOT  thread-safe,  so `self->vp_color2pixel'
 * must not be called by other threads until this function returns
 * @return: * : The optimized color palette */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_INOUT(1) REF struct video_palette *CC
libvideo_palette_optimize(REF struct video_palette *__restrict self);


DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_PALETTE_H */
