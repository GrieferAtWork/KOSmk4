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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_REGION_H
#define GUARD_LIBVIDEO_GFX_BUFFER_REGION_H 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>

#include "gfx.h" /* struct subregion_buffer */

DECL_BEGIN

struct video_buffer;

/* Buffer used to represent a region of `brb_base' containing unmappable pixels */
struct bigregion_buffer: video_buffer {
	REF struct video_buffer *brb_base; /* [1..1][const] Underlying video buffer */
	video_offset_t           brb_xoff; /* [const] Starting X offset of pixel data in `brb_base' */
	video_offset_t           brb_yoff; /* [const] Starting Y offset of pixel data in `brb_base' */
};

typedef unsigned int revokable_inuse_t;

struct bigregion_buffer_r: bigregion_buffer {
	/* [OVERRIDE(.brb_base, [lock(READ(ATOMIC), WRITE(ATOMIC && OLD_VALUE_VALID_UNTIL(brbr_inuse == 0)))])] */
	size_t              _brbr_pad1; /* ... */
	video_coord_t       _brbr_pad2; /* ... */
	struct video_buffer *brbr_orig;  /* [1..1][valid_if(brbr_inuse > 0)] The original video buffer (for releasing video locks) */
	revokable_inuse_t    brbr_inuse; /* [lock(ATOMIC)] when  non-zero, any value ever assigned to "brb_base" must remain valid
	                                  * In  practice, this counter is non-zero while video locks are held, or when doing pixel
	                                  * I/O. In turn, buffer revoke sets `brb_base' to an empty buffer, then yields until this
	                                  * becomes "0". */
};

struct subregion_buffer_r: subregion_buffer {
	/* [OVERRIDE(.srb_base, [lock(READ(ATOMIC), WRITE(ATOMIC && OLD_VALUE_VALID_UNTIL(srbr_inuse == 0)))])] */
	struct video_buffer *srbr_orig;  /* [1..1][valid_if(srbr_inuse > 0)] The original video buffer (for releasing video locks) */
	revokable_inuse_t    srbr_inuse; /* [lock(ATOMIC)] s.a. `struct bigregion_buffer_r::brbr_inuse' */
};

INTDEF struct video_buffer_ops bigregion_buffer_ops;
INTDEF struct video_buffer_ops bigregion_buffer_ops_r;
//TDEF struct video_buffer_ops subregion_buffer_ops;         /* `srb_vm_xrem != 0' */
//TDEF struct video_buffer_ops subregion_buffer_ops_norem;   /* `srb_vm_xrem == 0' */
INTDEF struct video_buffer_ops subregion_buffer_ops_r;       /* `srb_vm_xrem != 0' */
INTDEF struct video_buffer_ops subregion_buffer_ops_norem_r; /* `srb_vm_xrem == 0' */
INTDEF struct video_buffer_ops basregion_buffer_ops_r;       /* Same dimensions as base-buffer */
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _bigregion_buffer_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _bigregion_buffer_ops_r(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _subregion_buffer_ops_r(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _subregion_buffer_ops_norem_r(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _basregion_buffer_ops_r(void);


/* Create a wrapper video buffer for `self' that can only ever be used to access
 * the intersection of pixels from `rect' and `self' (trying a GFX context  will
 * always start out with the I/O rect set to "rect", but the clip rect still set
 * to the buffer's base dimensions, and trying to lock OOB regions always fails)
 *
 * NOTE: Starting coords in `rect' are allowed to be negative, and its dimensions
 *       are allowed to be greater than those of `self', too!
 *
 * `video_buffer_region_revocable()' does the same,  but the returned video  buffer
 * is also "revocable" (s.a. `libvideo_buffer_region_revoke()'), meaning it can  be
 * detached from the original buffer (and turned into a no-op) at any point in time
 * (blocking if a video lock is held in `libvideo_buffer_region_revoke()').
 *
 * @return: * :   The wrapper video buffer
 * @return: NULL: Failed to create video buffer (s.a. `errno') */
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *CC
libvideo_buffer_region(struct video_buffer *__restrict self,
                       struct video_rect const *__restrict rect);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *CC
libvideo_buffer_region_revocable(struct video_buffer *__restrict self,
                                 struct video_rect const *__restrict rect);


/* Revoke  access  to the  underlying  video buffer,  given  a video
 * buffer that was returned by `libvideo_buffer_region_revocable()'.
 * If the buffer had already been revoked, this is a no-op.
 *
 * >> DO NOT CALL THIS FUNCTION FOR BUFFERS OBTAINED FROM SOMETHING
 * >> OTHER THAN `libvideo_buffer_region_revocable()' !!!
 *
 * @return: * : Always re-returns `self' */
INTDEF ATTR_INOUT(1) struct video_buffer *CC
libvideo_buffer_region_revoke(struct video_buffer *__restrict self);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_REGION_H */
