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
#ifndef GUARD_LIBVIDEO_GFX_DISPLAY_C
#define GUARD_LIBVIDEO_GFX_DISPLAY_C 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <malloc.h>
#include <stddef.h>

#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/display.h>
#include <libvideo/gfx/gfx.h>

#include "display.h"

DECL_BEGIN

PRIVATE NONNULL((1)) void CC
dummy_display_destroy(struct video_display *__restrict self) {
	struct dummy_display *me = (struct dummy_display *)self;
	video_buffer_decref(me->dd_buffer);
	free(self);
}

PRIVATE WUNUSED ATTR_INOUT((1)) REF struct video_buffer *CC
dummy_display_getbuffer(struct video_display *__restrict self) {
	struct dummy_display *me = (struct dummy_display *)self;
	REF struct video_buffer *result = me->dd_buffer;
	video_buffer_incref(result);
	return result;
}

PRIVATE ATTR_INOUT(1) ATTR_IN(2) void CC
dummy_display_updaterect(struct video_display *__restrict self,
                         struct video_rect const *__restrict rect) {
	/* no-op */
	(void)self;
	(void)rect;
	COMPILER_IMPURE();
}

PRIVATE ATTR_INOUT(1) ATTR_INS(2, 3) void CC
dummy_display_updaterects(struct video_display *__restrict self,
                          struct video_rect const *__restrict rects,
                          size_t n_rects) {
	/* no-op */
	(void)self;
	(void)rects;
	(void)n_rects;
	COMPILER_IMPURE();
}


INTERN struct video_display_ops dummy_display_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_display_ops *CC
_dummy_display_ops(void) {
	if (!dummy_display_ops.vdo_destroy) {
		dummy_display_ops.vdo_getbuffer   = &dummy_display_getbuffer;
		dummy_display_ops.vdo_updaterect  = &dummy_display_updaterect;
		dummy_display_ops.vdo_updaterects = &dummy_display_updaterects;
		COMPILER_WRITE_BARRIER();
		dummy_display_ops.vdo_destroy = &dummy_display_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &dummy_display_ops;
}


/* Create a video_display wrapper for a simple video buffer.
 * - `video_display_getbuffer()' always returns `buffer' and never fails
 * - `video_display_updaterect()' is a no-op
 * - `video_display_updaterects()' is a no-op
 *
 * @return: * :   The display wrapper for `buffer'
 * @return: NULL: [errno=ENOMEM] Out of memory. */
DEFINE_PUBLIC_ALIAS(video_display_forbuffer, libvideo_display_forbuffer);
INTERN WUNUSED ATTR_INOUT(1) REF struct video_display *CC
libvideo_display_forbuffer(struct video_buffer *__restrict buffer) {
	REF struct dummy_display *result;
	result = (REF struct dummy_display *)malloc(sizeof(struct dummy_display));
	if unlikely(!result)
		goto err;
	result->vd_domain = video_buffer_getdomain(buffer);
	result->vd_ops    = _dummy_display_ops();
	result->vd_refcnt = 1;
	result->dd_buffer = buffer;
	video_buffer_incref(buffer);
	return result;
err:
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_DISPLAY_C */
