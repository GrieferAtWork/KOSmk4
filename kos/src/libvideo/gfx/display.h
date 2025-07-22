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
#ifndef GUARD_LIBVIDEO_GFX_DISPLAY_H
#define GUARD_LIBVIDEO_GFX_DISPLAY_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/display.h>

DECL_BEGIN

/* "libvideo-gfx" only supplies  the dummy wrapper  impl for video  displays.
 * The proper (big) impls of "video_display" are provided by other libraries:
 * - video_window:  libvideo-compositor
 * - video_monitor: libvideo-driver
 */

struct dummy_display: video_display {
	REF struct video_buffer *dd_buffer; /* [1..1][const] Buffer used to drive this dummy display */
};

INTDEF struct video_display_ops dummy_display_ops;
INTDEF ATTR_RETNONNULL WUNUSED struct video_display_ops *CC _dummy_display_ops(void);

/* Create a video_display wrapper for a simple video buffer.
 * - `video_display_getbuffer()' always returns `buffer' and never fails
 * - `video_display_updaterect()' is a no-op
 * - `video_display_updaterects()' is a no-op
 *
 * @return: * :   The display wrapper for `buffer'
 * @return: NULL: [errno=ENOMEM] Out of memory. */
INTDEF WUNUSED ATTR_INOUT(1) REF struct video_display *CC
libvideo_display_forbuffer(struct video_buffer *__restrict buffer);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_DISPLAY_H */
