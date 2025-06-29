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
#ifndef GUARD_LIBVIDEO_GFX_ANIM_H
#define GUARD_LIBVIDEO_GFX_ANIM_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <libvideo/gfx/anim.h>

DECL_BEGIN

/* Create a single-frame video animation from a given buffer.
 * The  returned  animation object  always  re-return `frame'
 * when a call is made to `video_anim_firstframe', and trying
 * to load any  other frame via  `video_anim_nextframe' is  a
 * no-op.
 * @return: * :   The controller for the single-frame video animation
 * @return: NULL: Out of memory. */
INTDEF WUNUSED ATTR_INOUT(1) REF struct video_anim *CC
libvideo_anim_fromframe(struct video_buffer *__restrict frame);

/* Return  a wrapper  for `self'  that caches  animation frames during
 * the first loop, and simply replays them during any subsequent loop.
 * @param: codec:   When non-null,  animation frames  are converted  into
 *                  this pixel format, rather than being copied verbatim.
 * @param: palette: Used with `codec' (if non-NULL)
 * @param: type:    The type of video buffer to use for cached images. */
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN_OPT(2) ATTR_IN_OPT(3) REF struct video_anim *CC
libvideo_anim_cached(struct video_anim *__restrict self,
                     struct video_codec const *codec,
                     struct video_palette *palette,
                     unsigned int type);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_ANIM_H */
