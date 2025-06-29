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
#ifndef GUARD_LIBVIDEO_GFX_GFX_BUFFER_H
#define GUARD_LIBVIDEO_GFX_GFX_BUFFER_H 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>
#include <stddef.h>

#include <libvideo/gfx/buffer.h>

DECL_BEGIN

/* Buffer representing a sub-region of a larger buffer */
struct subregion_buffer: video_buffer {
	REF struct video_buffer *srb_base;    /* [1..1][const] Underlying video buffer */
	video_coord_t            srb_xoff;    /* [const] Starting X offset of pixel data in `srb_base' */
	video_coord_t            srb_yoff;    /* [const] Starting Y offset of pixel data in `srb_base' */
	/* HINT: Until this point, we are binary-compatible with `struct gfx_buffer' */
	size_t                   srb_vm_xoff; /* [const] Byte  offset  for  `srb_xoff'  in  video  memory
	                                       * (properly aligned as per `vb_format.vf_codec->vc_align')
	                                       * When this value cannot be calculated, a subregion_buffer
	                                       * cannot be used, and  `gfx_buffer' must be used  instead. */
	video_dim_t              srb_vm_ylos; /* [const] # of lines lost in translation */
};


/* Buffer representing a custom GFX region / format within a larger video buffer */
struct gfx_buffer: video_buffer {
	REF struct video_buffer *gxb_base;     /* [1..1][const] Underlying video buffer */
	video_offset_t           gxb_cxoff;    /* [const] s.a. `struct video_gfxhdr::vxh_cxoff' */
	video_offset_t           gxb_cyoff;    /* [const] s.a. `struct video_gfxhdr::vxh_cyoff' */
	/* HINT: Until this point, we are binary-compatible with `struct subregion_buffer' */
	video_coord_t            gxb_bxmin;    /* [const] s.a. `struct video_gfxhdr::vxh_bxmin' */
	video_coord_t            gxb_bymin;    /* [const] s.a. `struct video_gfxhdr::vxh_bymin' */
	video_coord_t            gxb_bxend;    /* [const] s.a. `struct video_gfxhdr::vxh_bxend' */
	video_coord_t            gxb_byend;    /* [const] s.a. `struct video_gfxhdr::vxh_byend' */
	gfx_flag_t               gxb_flags;    /* [const] s.a. `struct video_gfx::vx_flags' */
	video_color_t            gxb_colorkey; /* [const] s.a. `struct video_gfx::vx_colorkey' */
};

INTDEF struct video_buffer_ops subregion_buffer_ops;
INTDEF struct video_buffer_ops gfx_buffer_ops;


/* Check  if `buffer'  is gfx.  If so  re-return "buffer" and
 * initialize `self' such that `libvideo_buffer_fromgfx_fini'
 * does nothing. Else, wrap it using `buffer' and return *it*
 * instead. */
INTDEF WUNUSED ATTR_OUT(1) NONNULL((2)) struct video_buffer *CC
libvideo_buffer_fromgfx_init(struct gfx_buffer *self,
                             struct video_gfx const *__restrict gfx);
#define libvideo_buffer_fromgfx_fini(self) (void)0



/* Return  a video  buffer that  will always  (forcefully) re-return `self'
 * whenever a GFX context is requested. Additionally, video locks will fail
 * when pixels represented  by `self'  cannot represented as  a video  lock
 * (e.g.  the Clip-  and I/O-Rects don't  match, or the  Clip Rect's bounds
 * don't end up at some whole-byte boundary,  or don't end up aligned to  a
 * degree that  is  sufficient  for  the codec  of  `self',  or  `self'  is
 * making using of some rotation/mirror GFX flags).
 *
 * If you want to guaranty that the returned buffer is still lockable, you
 * should wrap it again using `video_buffer_lockable()'.
 *
 * @return: * :   A video buffer representing the Clip Rect of `self'
 * @return: NULL: [errno=ENOMEM] Insufficient memory. */
INTDEF WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_buffer_fromgfx(struct video_gfx const *__restrict self);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_BUFFER_H */
