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
#ifndef GUARD_LIBVIDEO_GFX_GFX_C
#define GUARD_LIBVIDEO_GFX_GFX_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <libvideo/crect.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/rect.h>
#include <libvideo/types.h>

#include "buffer/region.h"
#include "gfx-empty.h"
#include "gfx-utils.h"
#include "gfx.h"

DECL_BEGIN

static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ZERO) == GFX_BLENDDATA_ONE);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE) == GFX_BLENDDATA_ZERO);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_SRC_COLOR) == GFX_BLENDDATA_ONE_MINUS_SRC_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_SRC_COLOR) == GFX_BLENDDATA_SRC_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_DST_COLOR) == GFX_BLENDDATA_ONE_MINUS_DST_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_DST_COLOR) == GFX_BLENDDATA_DST_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_SRC_ALPHA) == GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA) == GFX_BLENDDATA_SRC_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_DST_ALPHA) == GFX_BLENDDATA_ONE_MINUS_DST_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_DST_ALPHA) == GFX_BLENDDATA_DST_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_CONSTANT_COLOR) == GFX_BLENDDATA_ONE_MINUS_CONSTANT_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_CONSTANT_COLOR) == GFX_BLENDDATA_CONSTANT_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_CONSTANT_ALPHA) == GFX_BLENDDATA_ONE_MINUS_CONSTANT_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_CONSTANT_ALPHA) == GFX_BLENDDATA_CONSTANT_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_SRC_ALPHA_SATURATE) == GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA_SATURATE);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA_SATURATE) == GFX_BLENDDATA_SRC_ALPHA_SATURATE);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_SRC_COLOR_MUL_CONSTANT_COLOR) == GFX_BLENDDATA_ONE_MINUS_SRC_COLOR_MUL_CONSTANT_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_SRC_COLOR_MUL_CONSTANT_COLOR) == GFX_BLENDDATA_SRC_COLOR_MUL_CONSTANT_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_DST_COLOR_MUL_CONSTANT_COLOR) == GFX_BLENDDATA_ONE_MINUS_DST_COLOR_MUL_CONSTANT_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_DST_COLOR_MUL_CONSTANT_COLOR) == GFX_BLENDDATA_DST_COLOR_MUL_CONSTANT_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_SRC_ALPHA_MUL_CONSTANT_COLOR) == GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_COLOR) == GFX_BLENDDATA_SRC_ALPHA_MUL_CONSTANT_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_DST_ALPHA_MUL_CONSTANT_COLOR) == GFX_BLENDDATA_ONE_MINUS_DST_ALPHA_MUL_CONSTANT_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_DST_ALPHA_MUL_CONSTANT_COLOR) == GFX_BLENDDATA_DST_ALPHA_MUL_CONSTANT_COLOR);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_SRC_COLOR_MUL_CONSTANT_ALPHA) == GFX_BLENDDATA_ONE_MINUS_SRC_COLOR_MUL_CONSTANT_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_SRC_COLOR_MUL_CONSTANT_ALPHA) == GFX_BLENDDATA_SRC_COLOR_MUL_CONSTANT_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_DST_COLOR_MUL_CONSTANT_ALPHA) == GFX_BLENDDATA_ONE_MINUS_DST_COLOR_MUL_CONSTANT_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_DST_COLOR_MUL_CONSTANT_ALPHA) == GFX_BLENDDATA_DST_COLOR_MUL_CONSTANT_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_SRC_ALPHA_MUL_CONSTANT_ALPHA) == GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_SRC_ALPHA_MUL_CONSTANT_ALPHA) == GFX_BLENDDATA_SRC_ALPHA_MUL_CONSTANT_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_DST_ALPHA_MUL_CONSTANT_ALPHA) == GFX_BLENDDATA_ONE_MINUS_DST_ALPHA_MUL_CONSTANT_ALPHA);
static_assert(_GFX_BLENDDATA_ONE_MINUS(GFX_BLENDDATA_ONE_MINUS_DST_ALPHA_MUL_CONSTANT_ALPHA) == GFX_BLENDDATA_DST_ALPHA_MUL_CONSTANT_ALPHA);

/* Generic GFX operator implementations */
INTERN ATTR_IN(1) ATTR_IN(4) void CC
libvideo_gfx_bitblit__with_blitter(struct video_gfx const *__restrict dst,
                                   video_offset_t dst_x, video_offset_t dst_y,
                                   struct video_gfx const *__restrict src,
                                   video_offset_t src_x, video_offset_t src_y,
                                   video_dim_t size_x, video_dim_t size_y) {
	struct video_blitter blitter, *p_blitter;
	p_blitter = video_gfx_blitfrom(dst, src, &blitter);
	video_blitter_bitblit(p_blitter, dst_x, dst_y,
	                      src_x, src_y, size_x, size_y);
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
libvideo_gfx_stretch__with_blitter(struct video_gfx const *__restrict dst,
                                   video_offset_t dst_x, video_offset_t dst_y,
                                   video_dim_t dst_size_x, video_dim_t dst_size_y,
                                   struct video_gfx const *__restrict src,
                                   video_offset_t src_x, video_offset_t src_y,
                                   video_dim_t src_size_x, video_dim_t src_size_y) {
	struct video_blitter blitter, *p_blitter;
	p_blitter = video_gfx_blitfrom(dst, src, &blitter);
	video_blitter_stretch(p_blitter,
	                      dst_x, dst_y, dst_size_x, dst_size_y,
	                      src_x, src_y, src_size_x, src_size_y);
//	asm("int3");
}

INTERN ATTR_IN(1) ATTR_IN(4) ATTR_IN(7) void CC
libvideo_gfx_bitblit3__with_blitter3(struct video_gfx const *wrdst, video_offset_t wrdst_x, video_offset_t wrdst_y,
                                     struct video_gfx const *rddst, video_offset_t rddst_x, video_offset_t rddst_y,
                                     struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y,
                                     video_dim_t size_x, video_dim_t size_y) {
	struct video_blitter3 blitter, *p_blitter;
	blitter.vbt3_wrdst = wrdst;
	blitter.vbt3_rddst = rddst;
	blitter.vbt3_src   = src;
	p_blitter = (*wrdst->vx_hdr.vxh_ops->vgfo_blitfrom3)(&blitter);
	video_blitter3_bitblit(p_blitter,
	                       wrdst_x, wrdst_y, rddst_x, rddst_y,
	                       src_x, src_y, size_x, size_y);
}

INTERN ATTR_IN(1) ATTR_IN(4) ATTR_IN(9) void CC
libvideo_gfx_stretch3__with_blitter3(struct video_gfx const *wrdst, video_offset_t wrdst_x, video_offset_t wrdst_y,
                                     struct video_gfx const *rddst, video_offset_t rddst_x, video_offset_t rddst_y,
                                     video_dim_t dst_size_x, video_dim_t dst_size_y,
                                     struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y,
                                     video_dim_t src_size_x, video_dim_t src_size_y) {
	struct video_blitter3 blitter, *p_blitter;
	blitter.vbt3_wrdst = wrdst;
	blitter.vbt3_rddst = rddst;
	blitter.vbt3_src   = src;
	p_blitter = (*wrdst->vx_hdr.vxh_ops->vgfo_blitfrom3)(&blitter);
	video_blitter3_stretch(p_blitter, wrdst_x, wrdst_y,
	                       rddst_x, rddst_y, dst_size_x, dst_size_y,
	                       src_x, src_y, src_size_x, src_size_y);
}



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
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *CC
libvideo_gfx_clip__generic(struct video_gfx *__restrict self,
                           video_offset_t clip_x, video_offset_t clip_y,
                           video_dim_t size_x, video_dim_t size_y) {
	video_offset_t cxend, cyend;
	if unlikely(!size_x || !size_y)
		goto empty_clip;

	/* Adjust clip rect */
	self->vx_hdr.vxh_cxoff += clip_x;
	self->vx_hdr.vxh_cyoff += clip_y;
	if (video_gfx_getflags(self) & VIDEO_GFX_F_XMIRROR)
		self->vx_hdr.vxh_cxoff -= 2 * clip_x;
	if (video_gfx_getflags(self) & VIDEO_GFX_F_YMIRROR)
		self->vx_hdr.vxh_cyoff -= 2 * clip_y;
	self->vx_hdr.vxh_cxdim = size_x;
	self->vx_hdr.vxh_cydim = size_y;

	/* Clamp I/O Rect according to new Clip Rect */
	if ((video_offset_t)self->vx_hdr.vxh_bxmin < self->vx_hdr.vxh_cxoff) {
		self->vx_hdr.vxh_bxmin = (video_coord_t)self->vx_hdr.vxh_cxoff;
		if (self->vx_hdr.vxh_bxend <= self->vx_hdr.vxh_bxmin)
			goto empty_clip;
	}
	if ((video_offset_t)self->vx_hdr.vxh_bymin < self->vx_hdr.vxh_cyoff) {
		self->vx_hdr.vxh_bymin = (video_coord_t)self->vx_hdr.vxh_cyoff;
		if (self->vx_hdr.vxh_byend <= self->vx_hdr.vxh_bymin)
			goto empty_clip;
	}

	if (!OVERFLOW_SADD(self->vx_hdr.vxh_cxoff, size_x, &cxend) &&
	    self->vx_hdr.vxh_bxend > (video_coord_t)cxend && cxend > 0) {
		self->vx_hdr.vxh_bxend = (video_coord_t)cxend;
		if (self->vx_hdr.vxh_bxend <= self->vx_hdr.vxh_bxmin)
			goto empty_clip;
	}
	if (!OVERFLOW_SADD(self->vx_hdr.vxh_cyoff, size_y, &cyend) &&
	    self->vx_hdr.vxh_byend > (video_coord_t)cyend && cyend > 0) {
		self->vx_hdr.vxh_byend = (video_coord_t)cyend;
		if (self->vx_hdr.vxh_byend <= self->vx_hdr.vxh_bymin)
			goto empty_clip;
	}
	return self;
empty_clip:
	self->vx_hdr.vxh_ops = &libvideo_emptygfx_ops;
	return self;
}



/* Translate virtual (offset) pixel coords to physical (coord) coords.
 * @param: x:      Virtual pixel X offset
 * @param: y:      Virtual pixel Y offset
 * @param: coords: The absolute (physical) coords of the pixel are stored here
 * @return: true:  Translation was successful
 * @return: false: The given x/y lie outside the I/O Rect of `self' */
INTERN WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC
libvideo_gfx_offset2coord__generic(struct video_gfx const *__restrict self,
                                   video_offset_t x, video_offset_t y,
                                   video_coord_t coords[2]) {
	if (video_gfx_getflags(self) & VIDEO_GFX_F_XMIRROR)
		x = (self->vx_hdr.vxh_cxdim - 1) - x;
	if (video_gfx_getflags(self) & VIDEO_GFX_F_YMIRROR)
		y = (self->vx_hdr.vxh_cydim - 1) - y;
	if (video_gfx_getflags(self) & VIDEO_GFX_F_XWRAP)
		x = wrap(x, self->vx_hdr.vxh_cxdim);
	if (video_gfx_getflags(self) & VIDEO_GFX_F_YWRAP)
		x = wrap(x, self->vx_hdr.vxh_cxdim);
	x += self->vx_hdr.vxh_cxoff;
	y += self->vx_hdr.vxh_cyoff;
	if unlikely((video_coord_t)x < self->vx_hdr.vxh_bxmin)
		goto fail;
	if unlikely((video_coord_t)y < self->vx_hdr.vxh_bymin)
		goto fail;
	if unlikely((video_coord_t)x >= self->vx_hdr.vxh_bxend)
		goto fail;
	if unlikely((video_coord_t)y >= self->vx_hdr.vxh_byend)
		goto fail;
	if (video_gfx_getflags(self) & VIDEO_GFX_F_XYSWAP) {
		video_offset_t temp;
		temp = x;
		x    = y;
		y    = temp;
	}
	coords[0] = (video_coord_t)x;
	coords[1] = (video_coord_t)y;
	return true;
fail:
	return false;
}

/* Translate physical (coord) pixel coords to virtual (offset) coords.
 * @param: x:       Physical pixel X coord
 * @param: y:       Physical pixel Y coord
 * @param: offsets: The offset (virtual) coords of the pixel are stored here
 * @return: true:  Translation was successful
 * @return: false: The given x/y lie outside the I/O Rect of `self' */
INTERN WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC
libvideo_gfx_coord2offset__generic(struct video_gfx const *__restrict self,
                                   video_coord_t x, video_coord_t y,
                                   video_offset_t offsets[2]) {
	if (video_gfx_getflags(self) & VIDEO_GFX_F_XYSWAP) {
		video_coord_t temp;
		temp = x;
		x    = y;
		y    = temp;
	}
	if unlikely(x < self->vx_hdr.vxh_bxmin)
		goto fail;
	if unlikely(y < self->vx_hdr.vxh_bymin)
		goto fail;
	if unlikely(x >= self->vx_hdr.vxh_bxend)
		goto fail;
	if unlikely(y >= self->vx_hdr.vxh_byend)
		goto fail;
	x -= self->vx_hdr.vxh_cxoff;
	y -= self->vx_hdr.vxh_cyoff;
	if (video_gfx_getflags(self) & VIDEO_GFX_F_XMIRROR)
		x = (self->vx_hdr.vxh_cxdim - 1) - x;
	if (video_gfx_getflags(self) & VIDEO_GFX_F_YMIRROR)
		y = (self->vx_hdr.vxh_cydim - 1) - y;
	offsets[0] = (video_offset_t)x;
	offsets[1] = (video_offset_t)y;
	return true;
fail:
	return false;
}






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

LOCAL ATTR_INOUT(1) void FCC
_libvideo_gfx_xyswap(struct video_gfx *__restrict self) {
#define GFX_FLAGS_X_TO_Y_LSHIFT 1
#define GFX_FLAGS_Y_TO_X_RSHIFT GFX_FLAGS_X_TO_Y_LSHIFT
#define GFX_XFLAGS (VIDEO_GFX_F_XWRAP | VIDEO_GFX_F_XMIRROR)
#define GFX_YFLAGS (VIDEO_GFX_F_YWRAP | VIDEO_GFX_F_YMIRROR)
	static_assert((GFX_XFLAGS << GFX_FLAGS_X_TO_Y_LSHIFT) == GFX_YFLAGS);
	static_assert((GFX_YFLAGS >> GFX_FLAGS_Y_TO_X_RSHIFT) == GFX_XFLAGS);
#define Tswap(T, a, b) { T _temp = (a); (a) = (b); (b) = _temp; }
	Tswap(video_offset_t, self->vx_hdr.vxh_cxoff, self->vx_hdr.vxh_cyoff);
	Tswap(video_dim_t, self->vx_hdr.vxh_cxdim, self->vx_hdr.vxh_cydim);
	Tswap(video_coord_t, self->vx_hdr.vxh_bxmin, self->vx_hdr.vxh_bymin);
	Tswap(video_coord_t, self->vx_hdr.vxh_bxend, self->vx_hdr.vxh_byend);
#undef Tswap

	/* Swap axis-specific flags */
	self->vx_surf.vs_flags = (video_gfx_getflags(self) & ~(GFX_XFLAGS | GFX_YFLAGS)) |
	                         ((video_gfx_getflags(self) & GFX_XFLAGS) << GFX_FLAGS_X_TO_Y_LSHIFT) |
	                         ((video_gfx_getflags(self) & GFX_YFLAGS) >> GFX_FLAGS_Y_TO_X_RSHIFT);
#undef GFX_YFLAGS
#undef GFX_XFLAGS
#undef GFX_FLAGS_Y_TO_X_RSHIFT
#undef GFX_FLAGS_X_TO_Y_LSHIFT
}

DEFINE_PUBLIC_ALIAS(video_gfx_xyswap, libvideo_gfx_xyswap);
INTERN ATTR_INOUT(1) struct video_gfx *FCC
libvideo_gfx_xyswap(struct video_gfx *__restrict self) {
	_libvideo_gfx_xyswap(self);
	self->vx_surf.vs_flags ^= VIDEO_GFX_F_XYSWAP;
	return video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS);
}

DEFINE_PUBLIC_ALIAS(video_gfx_hmirror, libvideo_gfx_hmirror);
INTERN ATTR_INOUT(1) struct video_gfx *FCC
libvideo_gfx_hmirror(struct video_gfx *__restrict self) {
	self->vx_surf.vs_flags ^= VIDEO_GFX_F_XMIRROR;
	return video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS);
}

DEFINE_PUBLIC_ALIAS(video_gfx_vmirror, libvideo_gfx_vmirror);
INTERN ATTR_INOUT(1) struct video_gfx *FCC
libvideo_gfx_vmirror(struct video_gfx *__restrict self) {
	self->vx_surf.vs_flags ^= VIDEO_GFX_F_YMIRROR;
	return video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS);
}

DEFINE_PUBLIC_ALIAS(video_gfx_lrot90, libvideo_gfx_lrot90);
INTERN ATTR_INOUT(1) struct video_gfx *FCC
libvideo_gfx_lrot90(struct video_gfx *__restrict self) {
	_libvideo_gfx_xyswap(self);
	self->vx_surf.vs_flags ^= (VIDEO_GFX_F_XYSWAP | VIDEO_GFX_F_YMIRROR);
	return video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS);
}

DEFINE_PUBLIC_ALIAS(video_gfx_rrot90, libvideo_gfx_rrot90);
INTERN ATTR_INOUT(1) struct video_gfx *FCC
libvideo_gfx_rrot90(struct video_gfx *__restrict self) {
	/* When rotated right, the virtual origin
	 * >> vX=0, vY=0
	 * maps to the physical origin at
	 * >> pX=0, pY=video_gfx_getbuffer(self)->vb_ydim-1
	 *
	 * via the formula:
	 * >> pX = vY, pY = (video_gfx_getbuffer(self)->vb_ydim - 1) - vX
	 *
	 * Since mirroring  always  happens  before  X/Y-swap,
	 * and since `_libvideo_gfx_xyswap' already made it so
	 * `self->vx_hdr.vxh_cxdim = video_gfx_getbuffer(self)->vb_ydim-1'
	 * (assuming  no  custom  clip  rect),  we  have  to  toggle   the
	 * XMIRROR   flag   here   (since   mirror   happens   before  X/Y
	 * swapping)
	 *
	 * This also means that rotating the screen 90° right actually
	 * places the physical origin bottom-left -- THAT IS CORRECT!!
	 *
	 * Again: this is because if you  were to physically rotate  your
	 *        screen 90° to the right to match, then the new physical
	 *        origin would also be in the bottom left.
	 *
	 * Again: if you rotate an image right 90°, its physical origin
	 *        will ALSO appears in the bottom-left.
	 *
	 *
	 * If you're still not getting why this here is correct, image
	 * your screen already containing an image. Now you now rotate
	 * the screen to the right, what used to be the bottom-left is
	 * now  the top-left, and the contents of your screen just got
	 * rotate 90° clock-wise.
	 * Now if you keep rendering stuff onto the screen, you're gonna
	 * interact with the  former bottom-left as  the new top-  left!
	 *
	 * IOW: If  you rotate right, you're gonna get a NEW origin in
	 *      the BOTTOM LEFT (even though your old origin is now in
	 *      the top left). */
	_libvideo_gfx_xyswap(self);
	self->vx_surf.vs_flags ^= (VIDEO_GFX_F_XYSWAP | VIDEO_GFX_F_XMIRROR);
	return video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS);
}

DEFINE_PUBLIC_ALIAS(video_gfx_rot180, libvideo_gfx_rot180);
INTERN ATTR_INOUT(1) struct video_gfx *FCC
libvideo_gfx_rot180(struct video_gfx *__restrict self) {
	self->vx_surf.vs_flags ^= (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR);
	return video_gfx_update(self, VIDEO_GFX_UPDATE_FLAGS);
}

DEFINE_PUBLIC_ALIAS(video_gfx_lrot90n, libvideo_gfx_lrot90n);
INTERN ATTR_INOUT(1) struct video_gfx *FCC
libvideo_gfx_lrot90n(struct video_gfx *__restrict self, int n) {
	n %= 4;
	if (n < 0)
		n += 4;
	switch (n) {
	case 0: return self;
	case 1: return libvideo_gfx_lrot90(self);
	case 2: return libvideo_gfx_rot180(self);
	case 3: return libvideo_gfx_rrot90(self);
	default: __builtin_unreachable();
	}
}

DEFINE_PUBLIC_ALIAS(video_gfx_rrot90n, libvideo_gfx_rrot90n);
INTERN ATTR_INOUT(1) struct video_gfx *FCC
libvideo_gfx_rrot90n(struct video_gfx *__restrict self, int n) {
	n %= 4;
	if (n < 0)
		n += 4;
	switch (n) {
	case 0: return self;
	case 1: return libvideo_gfx_rrot90(self);
	case 2: return libvideo_gfx_rot180(self);
	case 3: return libvideo_gfx_lrot90(self);
	default: __builtin_unreachable();
	}
}


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
DEFINE_PUBLIC_ALIAS(video_gfx_asbuffer, libvideo_gfx_asbuffer);
DEFINE_PUBLIC_ALIAS(video_gfx_asbuffer_distinct, libvideo_gfx_asbuffer_distinct);
INTERN WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_gfx_asbuffer_distinct(struct video_gfx const *__restrict self) {
	struct video_surface surface = *video_gfx_assurface(self);
	video_buffer_incref(surface.vs_buffer);
	if (!video_gfx_issurfio(self)) {
		/* Must create a custom sub-region for the I/O-Rect */
		struct video_crect iorect;
		REF struct video_buffer *new_buffer;
		video_gfx_getiorect(self, &iorect);
		new_buffer = video_surface_subregion(&surface, &iorect);
		if unlikely(!new_buffer)
			goto err_surface_buffer;
		video_buffer_decref(surface.vs_buffer);
		surface.vs_buffer = new_buffer;
	}
	if (!video_gfx_isioclip(self)) {
		/* Must create a custom region for the Clip-Rect */
		struct video_rect clipio;
		REF struct video_buffer *new_buffer;
		video_gfx_getiocliprect(self, &clipio);
		new_buffer = libvideo_surface_region(&surface, &clipio);
		if unlikely(!new_buffer)
			goto err_surface_buffer;
		video_buffer_decref(surface.vs_buffer);
		surface.vs_buffer = new_buffer;
	}

	/* If  we're still using the GFX's buffer at this point, force a new one
	 * since we're required to return a distinct buffer, as well as one that
	 * features the currently set palette/flags/color-key of `self'. */
	if unlikely(surface.vs_buffer == video_gfx_getbuffer(self)) {
		struct video_crect surfrect;
		REF struct video_buffer *new_buffer;
		video_gfx_getsurfrect(self, &surfrect);
		new_buffer = video_surface_subregion(&surface, &surfrect);
		if unlikely(!new_buffer)
			goto err_surface_buffer;
		video_buffer_decref(surface.vs_buffer);
		surface.vs_buffer = new_buffer;
	}

	/* Return the new video buffer. */
	return surface.vs_buffer;
err_surface_buffer:
	video_buffer_decref(surface.vs_buffer);
	return NULL;
}

INTERN WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_gfx_asbuffer(struct video_gfx const *__restrict self) {
	/* If the Clip Rect matches the associated surface, then no region shenanigans are needed. */
	if (video_gfx_issurfclip(self))
		return video_surface_asbuffer(video_gfx_assurface(self));

	/* Will always need to create a separate buffer, so
	 * just let the *_distinct variant do all the work. */
	return libvideo_gfx_asbuffer_distinct(self);
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_C */
