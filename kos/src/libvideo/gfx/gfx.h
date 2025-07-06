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

#include <hybrid/compiler.h>

#include <stdbool.h>

#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

DECL_BEGIN

/* Apply a clipping  rect to "self",  shrinking the  pixel
 * area relative to offsets specified by the given coords.
 *
 * Note that the clip area can  only ever be shrunk. To  go
 * back to the initial clip area, either keep a copy of the
 * original GFX  context, or  create a  new context  (which
 * always starts  out with  its clipping  area set  to  the
 * associated buffer's entire surface)
 *
 * @param: clip_x: Delta to add to the Clip Rect starting X coord.
 *                 When negative, extend clip rect with void-pixels to the left
 * @param: clip_y: Delta to add to the Clip Rect starting Y coord.
 *                 When negative, extend clip rect with void-pixels to the top
 * @param: size_x: New width of the clip rect. When greater than the old  clip
 *                 rect width, extend clip rect with void-pixels to the right.
 * @param: size_y: New height of the clip rect.  When greater than the old  clip
 *                 rect height, extend clip rect with void-pixels to the bottom.
 * @return: * : Always re-returns `self' */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *CC
libvideo_gfx_clip(struct video_gfx *__restrict self,
                  video_offset_t clip_x, video_offset_t clip_y,
                  video_dim_t size_x, video_dim_t size_y);

/* Called after the Clip- or I/O-Rect of `self' was updated
 * (caller must ensure  that I/O rect  is still  non-empty) */
#define _libvideo_gfx_clip_updated(self) (void)0

/* Translate virtual (offset) pixel coords to physical (coord) coords.
 * @param: x:      Virtual pixel X offset
 * @param: y:      Virtual pixel Y offset
 * @param: coords: The absolute (physical) coords of the pixel are stored here
 * @return: true:  Translation was successful
 * @return: false: The given x/y lie outside the I/O Rect of `self' */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC
libvideo_gfx_offset2coord(struct video_gfx const *__restrict self,
                          video_offset_t x, video_offset_t y,
                          video_coord_t coords[2]);

/* Translate physical (coord) pixel coords to virtual (offset) coords.
 * @param: x:       Physical pixel X coord
 * @param: y:       Physical pixel Y coord
 * @param: offsets: The offset (virtual) coords of the pixel are stored here
 * @return: true:  Translation was successful
 * @return: false: The given x/y lie outside the I/O Rect of `self' */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC
libvideo_gfx_coord2offset(struct video_gfx const *__restrict self,
                          video_coord_t x, video_coord_t y,
                          video_offset_t offsets[2]);


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



/* Initialize the clip / I/O rects of `self' to fully represent the underlying buffer fully. */
LOCAL ATTR_INOUT(1) void CC
libvideo_gfx_init_fullclip(struct video_gfx *__restrict self) {
	self->vx_hdr.vxh_bxmin = self->vx_hdr.vxh_cxoff = 0;
	self->vx_hdr.vxh_bymin = self->vx_hdr.vxh_cyoff = 0;
	if (self->vx_flags & VIDEO_GFX_F_XYSWAP) {
		self->vx_hdr.vxh_bxend = self->vx_hdr.vxh_cxsiz = self->vx_buffer->vb_ydim;
		self->vx_hdr.vxh_byend = self->vx_hdr.vxh_cysiz = self->vx_buffer->vb_xdim;
	} else {
		self->vx_hdr.vxh_bxend = self->vx_hdr.vxh_cxsiz = self->vx_buffer->vb_xdim;
		self->vx_hdr.vxh_byend = self->vx_hdr.vxh_cysiz = self->vx_buffer->vb_ydim;
	}
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_H */
