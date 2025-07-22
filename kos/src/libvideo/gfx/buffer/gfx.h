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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_GFX_H
#define GUARD_LIBVIDEO_GFX_BUFFER_GFX_H 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

DECL_BEGIN

/* Buffer representing a custom GFX region / format within a larger video buffer */
struct gfx_buffer: video_buffer {
	REF struct video_buffer *gxb_base;  /* [1..1][const] Underlying video buffer */
	video_offset_t           gxb_cxoff; /* [const] s.a. `struct video_gfxhdr::vxh_cxoff' */
	video_offset_t           gxb_cyoff; /* [const] s.a. `struct video_gfxhdr::vxh_cyoff' */
	video_coord_t            gxb_bxmin; /* [const] s.a. `struct video_gfxhdr::vxh_bxmin' */
	video_coord_t            gxb_bymin; /* [const] s.a. `struct video_gfxhdr::vxh_bymin' */
	video_coord_t            gxb_bxend; /* [const] s.a. `struct video_gfxhdr::vxh_bxend' */
	video_coord_t            gxb_byend; /* [const] s.a. `struct video_gfxhdr::vxh_byend' */
	video_gfx_flag_t         gxb_flags; /* [const] s.a. `struct video_gfx::vx_flags' */
};

/* GFX buffer operator types */
INTDEF struct video_buffer_ops gfx_buffer_ops;
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _gfx_buffer_ops(void);


/* Operators for GFX buffers, as seen above */

/* DESTROY */
INTDEF NONNULL((1)) void FCC gfx_buffer_destroy(struct video_buffer *__restrict self);

/* REVOKE+SUBREGION */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC gfx_buffer__revoke)(struct video_buffer *__restrict self);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC gfx_buffer__subregion(struct video_buffer *__restrict self, struct video_crect const *__restrict rect, video_gfx_flag_t gfx_flags);

/* GFX */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC gfx_buffer_initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC gfx_buffer_updategfx(struct video_gfx *__restrict self, unsigned int what);


/* Return a video buffer that simulates the clipping/rotation behavior
 * of the given GFX context `self'. Other GFX pixel modification flags
 * that are unrelated to rotation/mirroring  are also retained by  the
 * returned buffer.
 *
 * Note that the returned buffer only retains:
 * - Clip Rect
 * - I/O Rect
 * - GFX Flags
 *
 * It does not retain:
 * - Blend Mode
 * - Color Key
 *
 * Note that unlike `video_buffer_region()', which still allows for use
 * of video locks being applied to the returned buffer when rotation is
 * being used (with those locks then used to access un-rotated pixels),
 * the  buffer returned by this function REJECTS video locks when pixel
 * data is transformed in any way that cannot be represented using only
 * I/O rects. As such, you may need to use `video_buffer_lockable()' on
 * the returned buffer in order to make it lockable (if you wish to use
 * pixel data in a rotated/mirrored form).
 *
 * NOTE: Revoking pixel access on the returned buffer, or other types
 *       of buffers derived from it may also revoke pixel access from
 *       `self', so use with care.
 *
 * @return: * :   A video buffer representing the given `self'
 * @return: NULL: [errno=ENOMEM] Insufficient memory. */
INTDEF WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_buffer_fromgfx(struct video_gfx const *__restrict self);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_GFX_H */
