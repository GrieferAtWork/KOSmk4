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
#ifndef GUARD_LIBVIDEO_GFX_SCREEN_H
#define GUARD_LIBVIDEO_GFX_SCREEN_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <libvideo/gfx/screen.h>

DECL_BEGIN

/* Creates+returns  a video buffer for the entire  screen (or return NULL and set
 * errno  on error). Note that screen buffer access requires `CAP_SYS_RAWIO', and
 * only  a single screen buffer can ever exist system-wide. If an attempt is made
 * to create a second screen buffer, this function will block until the first one
 * is destroyed, or the processing owning it exits.
 *
 * @param: hint: Hint regarding the intended video resolution (or "NULL" to  just
 *               use the same video mode as had already been set by whatever came
 *               before us). */
INTDEF WUNUSED REF struct screen_buffer *CC
libvideo_screen_buffer_create(struct screen_buffer_hint *hint);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_SCREEN_H */
