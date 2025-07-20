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

#include <stddef.h>

#include <libvideo/color.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

DECL_BEGIN

/* Buffer representing a sub-region of a larger buffer */
struct old_subregion_buffer: video_buffer {
	REF struct video_buffer *srb_base;    /* [1..1][const] Underlying video buffer */
	video_coord_t            srb_xoff;    /* [const] Starting X offset of pixel data in `srb_base' */
	video_coord_t            srb_yoff;    /* [const] Starting Y offset of pixel data in `srb_base' */
	/* HINT: Until this point, we are binary-compatible with `struct old_gfx_buffer' */
	size_t                   srb_vm_xoff; /* [const] Byte   offset   for  `srb_xoff'   in   video  memory
	                                       * (properly  aligned  as  per  `vb_format.vf_codec->vc_align')
	                                       * When this value cannot be calculated, a old_subregion_buffer
	                                       * cannot be used, and  `old_gfx_buffer' must be used  instead. */
	video_coord_t            srb_vm_xrem; /* [const] Remaining X pixels not representable by `srb_vm_xoff' */
};


/* Buffer representing a custom GFX region / format within a larger video buffer */
struct old_gfx_buffer: video_buffer {
	REF struct video_buffer *gxb_base;     /* [1..1][const] Underlying video buffer */
	video_offset_t           gxb_cxoff;    /* [const] s.a. `struct video_gfxhdr::vxh_cxoff' */
	video_offset_t           gxb_cyoff;    /* [const] s.a. `struct video_gfxhdr::vxh_cyoff' */
	/* HINT: Until this point, we are binary-compatible with `struct old_subregion_buffer' */
	video_coord_t            gxb_bxmin;    /* [const] s.a. `struct video_gfxhdr::vxh_bxmin' */
	video_coord_t            gxb_bymin;    /* [const] s.a. `struct video_gfxhdr::vxh_bymin' */
	video_coord_t            gxb_bxend;    /* [const] s.a. `struct video_gfxhdr::vxh_bxend' */
	video_coord_t            gxb_byend;    /* [const] s.a. `struct video_gfxhdr::vxh_byend' */
	video_gfx_flag_t         gxb_flags;    /* [const] s.a. `struct video_gfx::vx_flags' */
	video_color_t            gxb_colorkey; /* [const] s.a. `struct video_gfx::vx_colorkey' */
};

INTDEF NONNULL((1)) void FCC old_subregion_buffer_destroy(struct video_buffer *__restrict self);
#define old_gfx_buffer_destroy old_subregion_buffer_destroy
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int FCC old_subregion_buffer_norem_rlock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int FCC old_subregion_buffer_norem_wlock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) ATTR_IN(2) void NOTHROW(FCC old_subregion_buffer_norem_unlock)(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC old_subregion_buffer_rlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC old_subregion_buffer_wlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) ATTR_IN(2) void NOTHROW(FCC old_subregion_buffer_unlockregion)(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC old_subregion_buffer_initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC old_subregion_buffer_updategfx(struct video_gfx *__restrict self, unsigned int what);

INTDEF struct video_buffer_ops old_subregion_buffer_ops;       /* `srb_vm_xrem != 0' */
INTDEF struct video_buffer_ops old_subregion_buffer_ops_norem; /* `srb_vm_xrem == 0' */
INTDEF struct video_buffer_ops old_gfx_buffer_ops;
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _old_subregion_buffer_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _old_subregion_buffer_ops_norem(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _old_gfx_buffer_ops(void);


/* Check  if  `buffer'  is  gfx.  If  so  re-return  "buffer" and
 * initialize `self' such that `old_libvideo_buffer_fromgfx_fini'
 * does  nothing. Else,  wrap it  using `buffer'  and return *it*
 * instead. */
INTDEF WUNUSED ATTR_OUT(1) NONNULL((2)) struct video_buffer *CC
old_libvideo_buffer_fromgfx_init(struct old_gfx_buffer *self,
                                 struct video_gfx const *__restrict gfx);
#define old_libvideo_buffer_fromgfx_fini(self) (void)0



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
old_libvideo_buffer_fromgfx(struct video_gfx const *__restrict self);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_GFX_H */
