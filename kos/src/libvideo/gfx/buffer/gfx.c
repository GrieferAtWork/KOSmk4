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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_GFX_C
#define GUARD_LIBVIDEO_GFX_BUFFER_GFX_C 1
#define __VIDEO_BUFFER_const /* nothing */
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <assert.h>
#include <malloc.h>
#include <stddef.h>

#include <libvideo/color.h>
#include <libvideo/crect.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/surface-defs.h>
#include <libvideo/gfx/surface.h>
#include <libvideo/rect.h>
#include <libvideo/types.h>

#include "../buffer.h"
#include "../gfx-empty.h"
#include "../gfx.h"
#include "../ramdomain.h"
#include "gfx.h"
#include "region.h"

DECL_BEGIN

/* GFX buffer operator types */
DEFINE_VIDEO_BUFFER_TYPE(gfx_buffer_ops,
                         gfx_buffer_destroy, gfx_buffer_initgfx, gfx_buffer_updategfx,
                         libvideo_buffer_notsup_rlock, libvideo_buffer_notsup_wlock, libvideo_buffer_noop_unlock,
                         libvideo_buffer_notsup_rlockregion, libvideo_buffer_notsup_wlockregion, libvideo_buffer_noop_unlockregion,
                         gfx_buffer__revoke, gfx_buffer__subregion)

/* Operators for GFX buffers, as seen above */

/* DESTROY */
INTERN NONNULL((1)) void FCC
gfx_buffer_destroy(struct video_buffer *__restrict self) {
	struct gfx_buffer *me = (struct gfx_buffer *)self;
	video_buffer_decref(me->gxb_base);
	__video_buffer_fini_common(me);
	free(me);
}

/* REVOKE+SUBREGION */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC gfx_buffer__revoke)(struct video_buffer *__restrict self) {
	struct gfx_buffer *me = (struct gfx_buffer *)self;
	video_buffer_revoke(me->gxb_base);
	return me;
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
gfx_buffer__subregion(struct video_surface const *__restrict self,
                      struct video_crect const *__restrict rect) {
	/* NOTE: This  could be written much more efficiently, but this function isn't
	 *       expected to be used all-too-often, so we're just not going to put any
	 *       extra effort into it... */
	struct video_gfx subgfx, *p_subgfx;
	p_subgfx = video_surface_getgfx(self, &subgfx, GFX_BLENDMODE_OVERRIDE);
	p_subgfx = video_gfx_clip(p_subgfx, rect->vcr_xmin, rect->vcr_ymin, rect->vcr_xdim, rect->vcr_ydim);
	return libvideo_buffer_fromgfx(p_subgfx);
}


/* GFX */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
gfx_buffer_initgfx(struct video_gfx *__restrict self) {
	struct gfx_buffer *me = (struct gfx_buffer *)video_gfx_getbuffer(self);
	struct video_buffer *base = me->gxb_base;
	self->vx_surf.vs_buffer = base; /* This is allowed! */
	self = (*base->vb_ops->vi_initgfx)(self);

	/* Adjust clip rect to re-create expected Clip- / I/O Rect */
	self = video_gfx_clip(self,
	                      me->gxb_bxmin, me->gxb_bymin,
	                      me->gxb_bxend - me->gxb_bxmin,
	                      me->gxb_byend - me->gxb_bymin);
	self = video_gfx_clip(self,
	                      me->gxb_cxoff - me->gxb_bxmin,
	                      me->gxb_cyoff - me->gxb_bymin,
	                      me->vb_xdim, me->vb_ydim);
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
gfx_buffer_updategfx(struct video_gfx *__restrict self, unsigned int what) {
	struct gfx_buffer *me = (struct gfx_buffer *)video_gfx_getbuffer(self);
	struct video_buffer *base = me->gxb_base;
	self->vx_surf.vs_buffer = base; /* This is allowed! */
	return (*base->vb_ops->vi_updategfx)(self, what);
}


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
DEFINE_PUBLIC_ALIAS(video_buffer_fromgfx, libvideo_buffer_fromgfx);
INTDEF WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_buffer_fromgfx(struct video_gfx const *__restrict self) {
	REF struct video_buffer *result;
	struct video_surface const *surface = video_gfx_getsurface(self);
	struct video_crect io_rect;
	struct video_rect clip_rect_after_io;
	bool must_apply_io;
	bool must_apply_clip;
	bool must_use_gfx_buffer;

	io_rect.vcr_xmin = self->vx_hdr.vxh_bxmin;
	io_rect.vcr_ymin = self->vx_hdr.vxh_bymin;
	io_rect.vcr_xdim = self->vx_hdr.vxh_bxend - self->vx_hdr.vxh_bxmin;
	io_rect.vcr_ydim = self->vx_hdr.vxh_byend - self->vx_hdr.vxh_bymin;

	/* Check for special case: empty buffer */
	if unlikely(!io_rect.vcr_xdim || !io_rect.vcr_ydim) {
		struct video_buffer *result = &libvideo_emptybuffer;
		video_buffer_incref(result);
		return result;
	}
	assert((io_rect.vcr_xmin + io_rect.vcr_xdim) > io_rect.vcr_xmin);
	assert((io_rect.vcr_ymin + io_rect.vcr_ydim) > io_rect.vcr_ymin);
	assert((io_rect.vcr_xmin + io_rect.vcr_xdim) <= video_surface_getxdim(surface));
	assert((io_rect.vcr_ymin + io_rect.vcr_ydim) <= video_surface_getydim(surface));

	/* Check if GFX contains flags that require use of a `struct gfx_buffer' */
	must_use_gfx_buffer = (video_surface_getflags(surface) &
	                       (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR | VIDEO_GFX_F_XYSWAP));
	if (must_use_gfx_buffer) {
		/* NOTE: Technically,  the buffer here  could also be  represented using 2 nestings
		 *       of `libvideo_surface_region()' (first for I/O-Rect, second for Clip-Rect),
		 *       but we don't / can't do this for 2 reasons:
		 * - We  can't do it because the resulting  buffer would still be lockable, and
		 *   further still: its pixel data would represent the buffer's contents BEFORE
		 *   transformations as per `flags' were applied.
		 * - We don't do it because the result would be 2 nested buffer types, which is
		 *   less efficient (and more complicated)  than having only a single  wrapper. */
		REF struct gfx_buffer *result;
		result = (REF struct gfx_buffer *)malloc(sizeof(struct gfx_buffer));
		if unlikely(!result)
			goto err;
		result->vb_ops    = _gfx_buffer_ops();
		result->vb_domain = _libvideo_ramdomain();
		result->vb_format.vbf_codec    = video_surface_getcodec(surface);
		result->vb_format.vbf_pal      = video_surface_getpalette(surface);
		result->vb_format.vbf_flags    = video_surface_getflags(surface);
		result->vb_format.vbf_colorkey = video_surface_getcolorkey(surface);
		result->vb_xdim   = self->vx_hdr.vxh_cxsiz;
		result->vb_ydim   = self->vx_hdr.vxh_cysiz;
		result->vb_refcnt = 1;
		result->gxb_base  = video_surface_getbuffer(surface);
		video_buffer_incref(result->gxb_base);
		result->gxb_cxoff = self->vx_hdr.vxh_cxoff;
		result->gxb_cyoff = self->vx_hdr.vxh_cyoff;
		result->gxb_bxmin = self->vx_hdr.vxh_bxmin;
		result->gxb_bymin = self->vx_hdr.vxh_bymin;
		result->gxb_bxend = self->vx_hdr.vxh_bxend;
		result->gxb_byend = self->vx_hdr.vxh_byend;
		__video_buffer_init_common(result);
		return result;
	}

	/* Check if an I/O Rect needs to be applied */
	must_apply_io = io_rect.vcr_xmin > 0 ||
	                io_rect.vcr_ymin > 0 ||
	                io_rect.vcr_xdim < video_surface_getxdim(surface) ||
	                io_rect.vcr_ydim < video_surface_getydim(surface);

	/* Calculate Clip Rect (after I/O) */
	clip_rect_after_io.vr_xmin = self->vx_hdr.vxh_cxoff - io_rect.vcr_xmin;
	clip_rect_after_io.vr_ymin = self->vx_hdr.vxh_cyoff - io_rect.vcr_ymin;
	clip_rect_after_io.vr_xdim = self->vx_hdr.vxh_cxsiz;
	clip_rect_after_io.vr_ydim = self->vx_hdr.vxh_cysiz;

	/* Check if a Clip Rect needs to be applied */
	must_apply_clip = clip_rect_after_io.vr_xmin != 0 ||
	                  clip_rect_after_io.vr_ymin != 0 ||
	                  clip_rect_after_io.vr_xdim != io_rect.vcr_xdim ||
	                  clip_rect_after_io.vr_ydim != io_rect.vcr_ydim;

	/* Apply transformations */
	result = video_surface_getbuffer(surface);
	video_buffer_incref(result);
	if (must_apply_io || (!must_apply_clip && (video_surface_getflags(surface) !=
	                                           video_buffer_getflags(result)))) {
		REF struct video_buffer *new_buffer;
		new_buffer = video_surface_subregion(surface, &io_rect);
		if unlikely(!new_buffer)
			goto err_result;
		video_buffer_decref(result);
		result = new_buffer;
	}
	if (must_apply_clip) {
		REF struct video_buffer *new_buffer;
		new_buffer = libvideo_surface_region(surface, &clip_rect_after_io);
		if unlikely(!new_buffer)
			goto err_result;
		video_buffer_decref(result);
		result = new_buffer;
	}
	return result;
err_result:
	video_buffer_decref(result);
err:
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_GFX_C */
