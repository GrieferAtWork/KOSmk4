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
#ifndef GUARD_LIBVIDEO_GFX_GFX_H
#define GUARD_LIBVIDEO_GFX_GFX_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <stdbool.h>

#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

DECL_BEGIN

/* Generic GFX operator implementations */
INTDEF ATTR_IN(1) ATTR_IN(4) void CC libvideo_gfx_bitblit__with_blitter(struct video_gfx const *dst, video_offset_t dst_x, video_offset_t dst_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_gfx_stretch__with_blitter(struct video_gfx const *dst, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) ATTR_IN(4) ATTR_IN(7) void CC libvideo_gfx_bitblit3__with_blitter3(struct video_gfx const *wrdst, video_offset_t wrdst_x, video_offset_t wrdst_y, struct video_gfx const *rddst, video_offset_t rddst_x, video_offset_t rddst_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) ATTR_IN(4) ATTR_IN(9) void CC libvideo_gfx_stretch3__with_blitter3(struct video_gfx const *wrdst, video_offset_t wrdst_x, video_offset_t wrdst_y, struct video_gfx const *rddst, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *CC libvideo_gfx_clip__generic(struct video_gfx *__restrict self, video_offset_t clip_x, video_offset_t clip_y, video_dim_t size_x, video_dim_t size_y);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC libvideo_gfx_offset2coord__generic(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_coord_t coords[2]);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC libvideo_gfx_coord2offset__generic(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_offset_t offsets[2]);



/* Perform geometric transformations on the contents of the current  clip
 * rect of `self'. Note that none of these functions alter pixel data  of
 * the underlying buffer; they only affect how the given `self' interacts
 * with pixel data of the underlying buffer.
 *
 * - video_gfx_xyswap:  Swap x/y coords (mirror pixel data along a diagonal starting in the top-left)
 * - video_gfx_hmirror: Mirror pixel data horizontally
 * - video_gfx_vmirror: Mirror pixel data vertically
 * - video_gfx_lrot90:  Rotate pixel data left 90°
 * - video_gfx_rrot90:  Rotate pixel data right 90°
 * - video_gfx_rot180:  Rotate pixel data 180°
 * - video_gfx_nrot90n: Rotate pixel data by left by 90*n°
 * - video_gfx_rrot90n: Rotate pixel data by right by 90*n° */
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_xyswap(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_hmirror(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_vmirror(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_lrot90(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_rrot90(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_rot180(struct video_gfx *__restrict self);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_lrot90n(struct video_gfx *__restrict self, int n);
INTDEF ATTR_INOUT(1) struct video_gfx *FCC libvideo_gfx_rrot90n(struct video_gfx *__restrict self, int n);


/* Wrapper  around `video_buffer_region()' that produces a buffer which,
 * when used to instantiate a GFX context, replicates an effective Clip-
 * and  I/O-Rect that matches  `self', as well as  has its buffer format
 * initialized to reflect the current  palette, flags and color key,  as
 * set in `self' at the time of this function being called.
 *
 * CAUTION: Just like with `video_buffer_region()', pixel  data
 *          of the returned buffer will be rotated in GFX-only!
 *
 * NOTE: `video_gfx_asbuffer_distinct()' never returns `video_gfx_getbuffer()',
 *       even  if the GFX  context isn't doing anything  that would require the
 *       creation of a separate sub-buffer.
 *
 * @return: * : The video buffer representing a wrapped and const-i-fied copy of `self'
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=*] Failed to create wrapper for some other reason */
INTDEF WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_gfx_asbuffer(struct video_gfx const *__restrict self);
INTDEF WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_gfx_asbuffer_distinct(struct video_gfx const *__restrict self);





/* Initialize the clip / I/O rects of `self' to fully represent the underlying buffer fully. */
LOCAL ATTR_INOUT(1) void CC
libvideo_gfx_init_fullclip(struct video_gfx *__restrict self) {
	self->vx_hdr.vxh_bxmin = self->vx_hdr.vxh_cxoff = 0;
	self->vx_hdr.vxh_bymin = self->vx_hdr.vxh_cyoff = 0;
	if (video_gfx_getflags(self) & VIDEO_GFX_F_XYSWAP) {
		self->vx_hdr.vxh_bxend = self->vx_hdr.vxh_cxdim = video_gfx_getbuffer(self)->vb_ydim;
		self->vx_hdr.vxh_byend = self->vx_hdr.vxh_cydim = video_gfx_getbuffer(self)->vb_xdim;
	} else {
		self->vx_hdr.vxh_bxend = self->vx_hdr.vxh_cxdim = video_gfx_getbuffer(self)->vb_xdim;
		self->vx_hdr.vxh_byend = self->vx_hdr.vxh_cydim = video_gfx_getbuffer(self)->vb_ydim;
	}
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_H */
