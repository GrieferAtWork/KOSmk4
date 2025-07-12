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
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>

#include <kos/anno.h>

#include <errno.h>
#include <malloc.h>
#include <stddef.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/palette.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "../buffer.h"
#include "../gfx-empty.h"
#include "../gfx.h"
#include "gfx.h"
#include "utils.h"

DECL_BEGIN

#undef SUBREGION_BUFFER_PALREF
#if 0
#define SUBREGION_BUFFER_PALREF
#endif


static_assert(sizeof(struct subregion_buffer) <= sizeof(struct gfx_buffer));
static_assert(offsetof(struct subregion_buffer, srb_base) == offsetof(struct gfx_buffer, gxb_base));
static_assert(offsetof(struct subregion_buffer, srb_xoff) == offsetof(struct gfx_buffer, gxb_cxoff));
static_assert(offsetof(struct subregion_buffer, srb_yoff) == offsetof(struct gfx_buffer, gxb_cyoff));

INTERN NONNULL((1)) void
NOTHROW(FCC subregion_buffer_destroy)(struct video_buffer *__restrict self) {
	struct subregion_buffer *me = (struct subregion_buffer *)self;
#ifdef SUBREGION_BUFFER_PALREF
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
#endif /* SUBREGION_BUFFER_PALREF */
	video_buffer_decref(me->srb_base);
	free(me);
}

PRIVATE ATTR_IN(1) ATTR_INOUT(2) void FCC
subregion_buffer_encodelock(struct subregion_buffer const *__restrict self,
                            struct video_lock *__restrict lock) {
	lock->vl_data += self->srb_yoff * lock->vl_stride;
	lock->vl_data += self->srb_vm_xoff;
}

PRIVATE ATTR_IN(1) ATTR_INOUT(2) void FCC
subregion_buffer_decodelock(struct subregion_buffer const *__restrict self,
                            struct video_lock *__restrict lock) {
	lock->vl_data -= self->srb_yoff * lock->vl_stride;
	lock->vl_data -= self->srb_vm_xoff;
}

INTERN ATTR_INOUT(1) ATTR_OUT(2) int FCC
subregion_buffer_norem_rlock(struct video_buffer *__restrict self,
                             struct video_lock *__restrict lock) {
	struct subregion_buffer *me = (struct subregion_buffer *)self;
	int ok = video_buffer_rlock(me->srb_base, lock);
	subregion_buffer_encodelock(me, lock);
	return ok;
}

INTERN ATTR_INOUT(1) ATTR_OUT(2) int FCC
subregion_buffer_norem_wlock(struct video_buffer *__restrict self,
                             struct video_lock *__restrict lock) {
	struct subregion_buffer *me = (struct subregion_buffer *)self;
	int ok = video_buffer_wlock(me->srb_base, lock);
	subregion_buffer_encodelock(me, lock);
	return ok;
}

INTERN ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC subregion_buffer_norem_unlock)(struct video_buffer *__restrict self,
                                           struct video_lock *__restrict lock) {
	struct subregion_buffer *me = (struct subregion_buffer *)self;
	subregion_buffer_decodelock(me, lock);
	video_buffer_unlock(me->srb_base, lock);
}


PRIVATE ATTR_IN(1) ATTR_INOUT(2) void FCC
subregion_buffer_encoderegionlock(struct subregion_buffer const *__restrict self,
                                  struct video_regionlock *__restrict lock) {
	lock->_vrl_rect.vcr_xmin += self->srb_xoff;
	lock->_vrl_rect.vcr_ymin += self->srb_yoff;
}

PRIVATE ATTR_IN(1) ATTR_INOUT(2) void FCC
subregion_buffer_decoderegionlock(struct subregion_buffer const *__restrict self,
                                  struct video_regionlock *__restrict lock) {
	lock->_vrl_rect.vcr_xmin -= self->srb_xoff;
	lock->_vrl_rect.vcr_ymin -= self->srb_yoff;
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
subregion_buffer_rlockregion(struct video_buffer *__restrict self,
                             struct video_regionlock *__restrict lock) {
	struct subregion_buffer *me = (struct subregion_buffer *)self;
	video_regionlock_assert(me, lock);
	subregion_buffer_encoderegionlock(me, lock);
	return (*me->srb_base->vb_ops->vi_rlockregion)(me->srb_base, lock);
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
subregion_buffer_wlockregion(struct video_buffer *__restrict self,
                             struct video_regionlock *__restrict lock) {
	struct subregion_buffer *me = (struct subregion_buffer *)self;
	video_regionlock_assert(me, lock);
	subregion_buffer_encoderegionlock(me, lock);
	return (*me->srb_base->vb_ops->vi_wlockregion)(me->srb_base, lock);
}

INTERN ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC subregion_buffer_unlockregion)(struct video_buffer *__restrict self,
                                           struct video_regionlock *__restrict lock) {
	struct subregion_buffer *me = (struct subregion_buffer *)self;
	video_regionlock_assert(me, lock);
	video_buffer_unlockregion(me->srb_base, lock);
	subregion_buffer_decoderegionlock(me, lock);
}


INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
subregion_buffer_initgfx(struct video_gfx *__restrict self) {
	struct subregion_buffer *me = (struct subregion_buffer *)self->vx_buffer;
	struct video_buffer *base = me->srb_base;
	self->vx_buffer = base; /* This is allowed! */
	self = (*base->vb_ops->vi_initgfx)(self);
	/* Adjust clip rect so it points at the sub-region */
	self = video_gfx_clip(self,
	                      me->srb_xoff, me->srb_yoff,
	                      me->vb_xdim, me->vb_ydim);
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
subregion_buffer_updategfx(struct video_gfx *__restrict self, unsigned int what) {
	struct subregion_buffer *me = (struct subregion_buffer *)self->vx_buffer;
	struct video_buffer *base = me->srb_base;
	self->vx_buffer = base; /* This is allowed! */
	return (*base->vb_ops->vi_updategfx)(self, what);
}


INTERN struct video_buffer_ops subregion_buffer_ops = {};
INTERN struct video_buffer_ops subregion_buffer_ops_norem = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC
_subregion_buffer_ops(void) {
	if unlikely(!subregion_buffer_ops.vi_destroy) {
		subregion_buffer_ops.vi_rlock        = &libvideo_buffer_notsup_rlock;
		subregion_buffer_ops.vi_wlock        = &libvideo_buffer_notsup_wlock;
		subregion_buffer_ops.vi_unlock       = &libvideo_buffer_noop_unlock;
		subregion_buffer_ops.vi_rlockregion  = &subregion_buffer_rlockregion;
		subregion_buffer_ops.vi_wlockregion  = &subregion_buffer_wlockregion;
		subregion_buffer_ops.vi_unlockregion = &subregion_buffer_unlockregion;
		subregion_buffer_ops.vi_initgfx      = &subregion_buffer_initgfx;
		subregion_buffer_ops.vi_updategfx    = &subregion_buffer_updategfx;
		COMPILER_WRITE_BARRIER();
		subregion_buffer_ops.vi_destroy = &subregion_buffer_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &subregion_buffer_ops;
}

INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC
_subregion_buffer_ops_norem(void) {
	if unlikely(!subregion_buffer_ops_norem.vi_destroy) {
		subregion_buffer_ops_norem.vi_rlockregion  = &subregion_buffer_rlockregion;
		subregion_buffer_ops_norem.vi_wlockregion  = &subregion_buffer_wlockregion;
		subregion_buffer_ops_norem.vi_unlockregion = &subregion_buffer_unlockregion;
		subregion_buffer_ops_norem.vi_rlock        = &subregion_buffer_norem_rlock;
		subregion_buffer_ops_norem.vi_wlock        = &subregion_buffer_norem_wlock;
		subregion_buffer_ops_norem.vi_unlock       = &subregion_buffer_norem_unlock;
		subregion_buffer_ops_norem.vi_initgfx      = &subregion_buffer_initgfx;
		subregion_buffer_ops_norem.vi_updategfx    = &subregion_buffer_updategfx;
		COMPILER_WRITE_BARRIER();
		subregion_buffer_ops_norem.vi_destroy = &subregion_buffer_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &subregion_buffer_ops_norem;
}



PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
gfx_buffer_initgfx(struct video_gfx *__restrict self) {
	struct gfx_buffer *me = (struct gfx_buffer *)self->vx_buffer;
	struct video_buffer *base = me->gxb_base;

	/* Force reconfigure for GFX features of original GFX */
	self->vx_buffer   = base; /* This is allowed! */
	self->vx_flags    = me->gxb_flags;
	self->vx_colorkey = me->gxb_colorkey;
	self = (*base->vb_ops->vi_initgfx)(self);

	/* Restore clip rect */
	/* XXX: directly adjusting the clip rect might break for some buffer types */
	self->vx_hdr.vxh_cxoff = me->gxb_cxoff;
	self->vx_hdr.vxh_cyoff = me->gxb_cyoff;
	self->vx_hdr.vxh_cxsiz = me->vb_xdim;
	self->vx_hdr.vxh_cysiz = me->vb_ydim;
	self->vx_hdr.vxh_bxmin = me->gxb_bxmin;
	self->vx_hdr.vxh_bymin = me->gxb_bymin;
	self->vx_hdr.vxh_bxend = me->gxb_bxend;
	self->vx_hdr.vxh_byend = me->gxb_byend;
	return self;
}

PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
gfx_buffer_updategfx(struct video_gfx *__restrict self, unsigned int what) {
	struct gfx_buffer *me = (struct gfx_buffer *)self->vx_buffer;
	struct video_buffer *base = me->gxb_base;
	self->vx_buffer   = base; /* This is allowed! */
	self->vx_flags    = me->gxb_flags;
	self->vx_colorkey = me->gxb_colorkey;
	return (*base->vb_ops->vi_updategfx)(self, what);
}



INTERN struct video_buffer_ops gfx_buffer_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC
_gfx_buffer_ops(void) {
	if unlikely(!gfx_buffer_ops.vi_destroy) {
		video_buffer_ops_set_LOCKOPS_like_NOTSUP(&gfx_buffer_ops);
		gfx_buffer_ops.vi_initgfx   = &gfx_buffer_initgfx;
		gfx_buffer_ops.vi_updategfx = &gfx_buffer_updategfx;
		COMPILER_WRITE_BARRIER();
		gfx_buffer_ops.vi_destroy = &gfx_buffer_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &gfx_buffer_ops;
}



/* Check if the getpixel operator of "self" is the identity (after potential offsets) */
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) bool
NOTHROW(CC video_gfx_is_getcolor_identity)(struct video_gfx const *__restrict self) {
	return !(self->vx_flags & (VIDEO_GFX_F_XMIRROR | VIDEO_GFX_F_YMIRROR |
	                           VIDEO_GFX_F_XYSWAP | VIDEO_GFX_F_BLUR)) &&
	       VIDEO_COLOR_ISTRANSPARENT(self->vx_colorkey);
}

/* Check if the I/O Rect of `self' covers the entire buffer */
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) bool
NOTHROW(CC video_gfx_is_iorect_identity)(struct video_gfx const *__restrict self) {
	struct video_buffer const *buf = self->vx_buffer;
	return self->vx_hdr.vxh_bxmin == 0 &&
	       self->vx_hdr.vxh_bymin == 0 &&
	       self->vx_hdr.vxh_bxend == buf->vb_xdim &&
	       self->vx_hdr.vxh_byend == buf->vb_ydim;
}

/* Check if the Clip- and I/O Rects of `self' are identical */
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) bool
NOTHROW(CC video_gfx_is_cliprect_eq_iorect)(struct video_gfx const *__restrict self) {
	return self->vx_hdr.vxh_cxoff >= 0 &&
	       self->vx_hdr.vxh_cyoff >= 0 &&
	       self->vx_hdr.vxh_bxmin == (video_coord_t)self->vx_hdr.vxh_cxoff &&
	       self->vx_hdr.vxh_bymin == (video_coord_t)self->vx_hdr.vxh_cyoff &&
	       self->vx_hdr.vxh_bxend == (self->vx_hdr.vxh_bxmin + self->vx_hdr.vxh_cxsiz) &&
	       self->vx_hdr.vxh_byend == (self->vx_hdr.vxh_bymin + self->vx_hdr.vxh_cysiz);
}

/* Check  if `buffer'  is gfx.  If so  re-return "buffer" and
 * initialize `self' such that `libvideo_buffer_fromgfx_fini'
 * does nothing. Else, wrap it using `buffer' and return *it*
 * instead. */
INTERN WUNUSED ATTR_OUT(1) NONNULL((2)) struct video_buffer *CC
libvideo_buffer_fromgfx_init(struct gfx_buffer *self,
                             struct video_gfx const *__restrict gfx) {
	struct video_buffer *src = gfx->vx_buffer;

	/* Check for special case: empty GFX context */
	if unlikely(gfx->vx_hdr.vxh_cxsiz == 0 ||
	            gfx->vx_hdr.vxh_cysiz == 0)
		return &libvideo_emptybuffer;

	/* Deal with  optimizations possible  when no-  or
	 * only linear pixel transformation are being done */
	if (video_gfx_is_getcolor_identity(gfx)) {
		if (video_gfx_is_iorect_identity(gfx)) {
			/* Can just re-use the original video_buffer of `gfx'! */
			return gfx->vx_buffer;
		}

		/* May be able to use a `struct subregion_buffer' */
		if (video_gfx_is_cliprect_eq_iorect(gfx) && src->vb_ops != &gfx_buffer_ops) {
			struct subregion_buffer *result;
			result = (struct subregion_buffer *)self;
			video_codec_xcoord_to_offset(src->vb_format.vf_codec,
			                             (video_coord_t)gfx->vx_hdr.vxh_cxoff,
			                             &result->srb_vm_xoff,
			                             &result->srb_vm_xrem);
			/* We **are** able to use a subregion buffer! */
			result->vb_ops = result->srb_vm_xrem ? _subregion_buffer_ops()
			                                     : _subregion_buffer_ops_norem();
			result->vb_format = src->vb_format;
			result->vb_xdim   = gfx->vx_hdr.vxh_cxsiz;
			result->vb_ydim   = gfx->vx_hdr.vxh_cysiz;
#ifndef NDEBUG
			result->vb_refcnt = 0;
#endif /* !NDEBUG */
			result->srb_base = src;
			result->srb_xoff = gfx->vx_hdr.vxh_cxoff;
			result->srb_yoff = gfx->vx_hdr.vxh_cyoff;
			if (src->vb_ops == &subregion_buffer_ops ||
			    src->vb_ops == &subregion_buffer_ops_norem) {
				/* TODO */
			}
			return result;
		}
	}

	if (src->vb_ops == &gfx_buffer_ops) {
		/* TODO: merge GFX contexts */
	}

	/* Fallback: need to use an entire "struct gfx_buffer" */
	self->vb_ops    = _gfx_buffer_ops();
	self->vb_format = src->vb_format;
	self->vb_xdim   = gfx->vx_hdr.vxh_cxsiz;
	self->vb_ydim   = gfx->vx_hdr.vxh_cysiz;
#ifndef NDEBUG
	self->vb_refcnt = 0;
#endif /* !NDEBUG */
	self->gxb_base  = src;
	self->gxb_cxoff = gfx->vx_hdr.vxh_cxoff;
	self->gxb_cyoff = gfx->vx_hdr.vxh_cyoff;
	self->gxb_bxmin = gfx->vx_hdr.vxh_bxmin;
	self->gxb_bymin = gfx->vx_hdr.vxh_bymin;
	self->gxb_bxend = gfx->vx_hdr.vxh_bxend;
	self->gxb_byend = gfx->vx_hdr.vxh_byend;
	self->gxb_flags = gfx->vx_flags;
	self->gxb_colorkey = gfx->vx_colorkey;
	return self;
}



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
DEFINE_PUBLIC_ALIAS(video_buffer_fromgfx, libvideo_buffer_fromgfx);
INTERN WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_buffer_fromgfx(struct video_gfx const *__restrict self) {
	REF struct gfx_buffer *gx_result;
	struct video_buffer *src = self->vx_buffer;

	/* Check for special case: empty GFX context */
	if unlikely(self->vx_hdr.vxh_cxsiz == 0 ||
	            self->vx_hdr.vxh_cysiz == 0) {
		struct video_buffer *result = &libvideo_emptybuffer;
		video_buffer_incref(result);
		return result;
	}

	/* Deal with  optimizations possible  when no-  or
	 * only linear pixel transformation are being done */
	if (video_gfx_is_getcolor_identity(self)) {
		if (video_gfx_is_iorect_identity(self)) {
			/* Can just re-use the original video_buffer of `gfx'! */
			video_buffer_incref(src);
			return src;
		}

		/* May be able to use a `struct subregion_buffer' */
		if (video_gfx_is_cliprect_eq_iorect(self)) {
			size_t vm_xoff;
			video_coord_t vm_xrem;

			/* We **are** able to use a subregion buffer! */
			video_codec_xcoord_to_offset(src->vb_format.vf_codec,
			                             (video_coord_t)self->vx_hdr.vxh_cxoff,
			                             &vm_xoff, &vm_xrem);
			REF struct subregion_buffer *sr_result;
			sr_result = (REF struct subregion_buffer *)malloc(sizeof(struct subregion_buffer));
			if unlikely(!sr_result)
				goto err;
			if (src->vb_ops == &subregion_buffer_ops ||
				src->vb_ops == &subregion_buffer_ops_norem) {
				/* TODO */
			}
			sr_result->vb_ops    = vm_xrem ? _subregion_buffer_ops()
			                               : _subregion_buffer_ops_norem();
			sr_result->vb_format = src->vb_format;
			sr_result->vb_xdim   = self->vx_hdr.vxh_cxsiz;
			sr_result->vb_ydim   = self->vx_hdr.vxh_cysiz;
			sr_result->vb_refcnt = 1;
			sr_result->srb_base  = src;
			video_buffer_incref(src);
			sr_result->srb_xoff = self->vx_hdr.vxh_cxoff;
			sr_result->srb_yoff = self->vx_hdr.vxh_cyoff;
			sr_result->srb_vm_xoff = vm_xoff;
			sr_result->srb_vm_xrem = vm_xrem;
#ifdef SUBREGION_BUFFER_PALREF
			if (sr_result->vb_format.vf_pal)
				video_palette_incref(sr_result->vb_format.vf_pal);
#endif /* SUBREGION_BUFFER_PALREF */
			return sr_result;
		}
	}

	if (src->vb_ops == &gfx_buffer_ops) {
		/* TODO: merge GFX contexts */
	}

	/* Fallback: need to use an entire "struct gfx_buffer" */
	gx_result = (REF struct gfx_buffer *)malloc(sizeof(struct gfx_buffer));
	if unlikely(!gx_result)
		goto err;
	gx_result->vb_ops    = _gfx_buffer_ops();
	gx_result->vb_format = src->vb_format;
	gx_result->vb_xdim   = self->vx_hdr.vxh_cxsiz;
	gx_result->vb_ydim   = self->vx_hdr.vxh_cysiz;
	gx_result->vb_refcnt = 1;
	gx_result->gxb_base  = src;
	video_buffer_incref(src);
	gx_result->gxb_cxoff = self->vx_hdr.vxh_cxoff;
	gx_result->gxb_cyoff = self->vx_hdr.vxh_cyoff;
	gx_result->gxb_bxmin = self->vx_hdr.vxh_bxmin;
	gx_result->gxb_bymin = self->vx_hdr.vxh_bymin;
	gx_result->gxb_bxend = self->vx_hdr.vxh_bxend;
	gx_result->gxb_byend = self->vx_hdr.vxh_byend;
	gx_result->gxb_flags = self->vx_flags;
	gx_result->gxb_colorkey = self->vx_colorkey;
#ifdef SUBREGION_BUFFER_PALREF
	if (gx_result->vb_format.vf_pal)
		video_palette_incref(gx_result->vb_format.vf_pal);
#endif /* SUBREGION_BUFFER_PALREF */
	return gx_result;
err:
	return NULL;
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_GFX_C */
