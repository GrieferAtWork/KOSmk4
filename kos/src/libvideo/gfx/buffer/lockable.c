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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_LOCKABLE_C
#define GUARD_LIBVIDEO_GFX_BUFFER_LOCKABLE_C 1
#define __VIDEO_BUFFER_const /* nothing */
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sequence/list.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>

#include <libvideo/crect.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/surface.h>
#include <libvideo/types.h>

#include "../buffer.h"
#include "../ramdomain.h"
#include "lockable.h"
#include "utils.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


/* Lockable buffer operator types */
DEFINE_VIDEO_BUFFER_TYPE(lockable_buffer_ops,
                         lockable_buffer__destroy, lockable_buffer__initgfx, lockable_buffer__updategfx,
                         lockable_buffer__rlock, lockable_buffer__wlock, lockable_buffer__unlock,
                         lockable_buffer__rlockregion, lockable_buffer__wlockregion, lockable_buffer__unlockregion,
                         lockable_buffer__revoke, lockable_buffer__subregion);
DEFINE_VIDEO_BUFFER_TYPE(lockable_buffer_subregion_ops,
                         lockable_buffer_subregion__destroy, lockable_buffer_subregion__initgfx, lockable_buffer__updategfx,
                         libvideo_buffer_notsup_rlock, libvideo_buffer_notsup_wlock, libvideo_buffer_noop_unlock,
                         lockable_buffer_subregion__rlockregion, lockable_buffer_subregion__wlockregion, lockable_buffer_subregion__unlockregion,
                         lockable_buffer__revoke, lockable_buffer_subregion__subregion);
DEFINE_VIDEO_BUFFER_TYPE(lockable_buffer_subregion_norem_ops,
                         lockable_buffer_subregion__destroy, lockable_buffer_subregion__initgfx, lockable_buffer__updategfx,
                         lockable_buffer_subregion__rlock, lockable_buffer_subregion__wlock, lockable_buffer_subregion__unlock,
                         lockable_buffer_subregion__rlockregion, lockable_buffer_subregion__wlockregion, lockable_buffer_subregion__unlockregion,
                         lockable_buffer__revoke, lockable_buffer_subregion__subregion);



PRIVATE WUNUSED ATTR_INOUT(1) byte_t *FCC
lockable_getdata(struct lockable_buffer *__restrict self) {
	byte_t *result = atomic_read(&self->lb_data);
	if (!result) {
		struct video_rambuffer_requirements req;
		(*self->vb_codec->vc_rambuffer_requirements)(video_buffer_getxdim(self),
		                                             video_buffer_getydim(self),
		                                             &req);
		result = (byte_t *)calloc(req.vbs_bufsize);
		if unlikely(!result)
			goto err;
		self->lb_stride = req.vbs_stride;
		if (!atomic_cmpxch(&self->lb_data, NULL, result)) {
			byte_t *new_result = atomic_read(&self->lb_data);
			assert(new_result);
			free(result);
			result = new_result;
		}
		self->lb_edata = result + req.vbs_bufsize;
		COMPILER_WRITE_BARRIER();
	}
	return result;
err:
	return NULL;
}


INTERN NONNULL((1)) void FCC
lockable_buffer__destroy(struct video_buffer *__restrict self) {
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	video_buffer_decref(me->lb_base);
	free(me->lb_data);
	__video_buffer_fini_common(me);
	free(me);
}

INTERN NONNULL((1)) void FCC
lockable_buffer_subregion__destroy(struct video_buffer *__restrict self) {
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self;
	video_buffer_decref(me->lbsb_lockable);
	__video_buffer_fini_common(me);
	free(me);
}


INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC lockable_buffer__revoke)(struct video_buffer *__restrict self) {
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	video_buffer_revoke(me->lb_base);
	return me;
}

PRIVATE WUNUSED ATTR_IN(1) ATTR_INOUT(2) ATTR_IN(3) REF struct video_buffer *FCC
lockable_buffer__subregion_impl(struct video_surface const *__restrict surface,
                                struct lockable_buffer *__restrict self,
                                struct video_crect const *__restrict rect,
                                video_coord_t base_xoff,
                                video_coord_t base_yoff) {
	REF struct lockable_buffer_subregion *result;
	video_buffer_assert_rect(self, rect);
	base_xoff += rect->vcr_xmin;
	base_yoff += rect->vcr_ymin;
	result = (REF struct lockable_buffer_subregion *)malloc(sizeof(struct lockable_buffer_subregion));
	if unlikely(!result)
		goto err;
	__video_buffer_init_subregion(result, surface, self, rect);
	result->lb_data   = NULL;
	result->lb_stride = self->lb_stride;
	result->lb_data += base_yoff * result->lb_stride;
	result->lb_data += base_yoff * result->lb_stride;
	video_codec_xcoord_to_offset(video_buffer_getcodec(result), base_xoff,
	                             &result->lbsb_bxoff, &result->lbsb_bxrem);
	result->lbsb_xoff     = base_xoff;
	result->lbsb_yoff     = base_yoff;
	result->lbsb_lockable = self;
	video_buffer_incref(self);
	__video_buffer_init_ops(result, result->lbsb_bxrem ? _lockable_buffer_subregion_ops()
	                                                   : _lockable_buffer_subregion_norem_ops());
	__video_buffer_init_common(result);
	return result;
err:
	return NULL;
}


INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
lockable_buffer__subregion(struct video_surface const *__restrict self,
                           struct video_crect const *__restrict rect) {
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	return lockable_buffer__subregion_impl(self, me, rect, 0, 0);
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
lockable_buffer_subregion__subregion(struct video_surface const *__restrict self,
                                     struct video_crect const *__restrict rect) {
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self;
	return lockable_buffer__subregion_impl(self, me, rect, me->lbsb_xoff, me->lbsb_yoff);
}




/* Indices into `struct video_lock::_vl_driver' */
#define LOCKABLE_BUFFER_VLOCK_ISWRITE 0
static_assert(_VIDEO_LOCK__N_DRIVER >= 1);

/* Initialize a mock ram-buffer using the video lock of "self" */
PRIVATE ATTR_OUT(1) ATTR_IN(2) void FCC
lockable_asram(struct video_rambuffer *__restrict rb,
               struct lockable_buffer const *__restrict self) {
	DBG_memset(&rb->vb_domain, 0xcc, sizeof(rb->vb_domain));
	video_surface_copyattrib(&rb->vb_surf, &self->vb_surf);
	rb->vb_surf.vs_buffer = rb;
	rb->vb_codec = video_buffer_getcodec(self);
	__video_buffer_init_ops(rb, _rambuffer_ops());
	__video_buffer_init_dim(rb, video_buffer_getxdim(self), video_buffer_getydim(self));
#ifndef NDEBUG
	rb->vb_refcnt = 0; /* So someone incref'ing will fault */
#endif /* !NDEBUG */
	rb->rb_stride = self->lb_stride;
	rb->rb_data   = self->lb_data;
}

/* Read GFX into video lock */
PRIVATE NONNULL((1)) void FCC
lockable_readpixels(struct lockable_buffer const *__restrict self) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer dst;
	lockable_asram(&dst, self);
	p_srcgfx = video_buffer_getgfx_ex(self->lb_base, &srcgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(self->lb_base),
	                                  video_buffer_getflags(self->lb_base) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	p_dstgfx = video_buffer_getgfx_ex(&dst, &dstgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(&dst),
	                                  video_buffer_getflags(&dst) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, 0, 0,
	                  p_srcgfx, 0, 0,
	                  video_gfx_getxdim(p_dstgfx),
	                  video_gfx_getydim(p_dstgfx));
}

/* Write video lock to GFX */
PRIVATE NONNULL((1)) void FCC
lockable_writepixels(struct lockable_buffer const *__restrict self) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer src;
	lockable_asram(&src, self);
	p_srcgfx = video_buffer_getgfx_ex(&src, &srcgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(&src),
	                                  video_buffer_getflags(&src) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	p_dstgfx = video_buffer_getgfx_ex(self->lb_base, &dstgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(self->lb_base),
	                                  video_buffer_getflags(self->lb_base) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, 0, 0, p_srcgfx, 0, 0,
	                  video_gfx_getxdim(p_dstgfx),
	                  video_gfx_getydim(p_dstgfx));
}


/* Read GFX into video lock region */
PRIVATE NONNULL((1, 2)) void FCC
lockable_readpixels_region(struct lockable_buffer const *__restrict self,
                           struct video_regionlock const *__restrict region) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer dst;
	lockable_asram(&dst, self);
	p_srcgfx = video_buffer_getgfx_ex(self->lb_base, &srcgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(self->lb_base),
	                                  video_buffer_getflags(self->lb_base) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	p_dstgfx = video_buffer_getgfx_ex(&dst, &dstgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(&dst),
	                                  video_buffer_getflags(&dst) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, region->_vrl_rect.vcr_xmin, region->_vrl_rect.vcr_ymin,
	                  p_srcgfx, region->_vrl_rect.vcr_xmin, region->_vrl_rect.vcr_ymin,
	                  region->_vrl_rect.vcr_xdim,
	                  region->_vrl_rect.vcr_ydim);
}

/* Write video lock region to GFX */
PRIVATE NONNULL((1, 2)) void FCC
lockable_writepixels_region(struct lockable_buffer const *__restrict self,
                            struct video_regionlock const *__restrict region) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer src;
	lockable_asram(&src, self);
	p_srcgfx = video_buffer_getgfx_ex(&src, &srcgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(&src),
	                                  video_buffer_getflags(&src) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	p_dstgfx = video_buffer_getgfx_ex(self->lb_base, &dstgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(self->lb_base),
	                                  video_buffer_getflags(self->lb_base) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, region->_vrl_rect.vcr_xmin, region->_vrl_rect.vcr_ymin,
	                  p_srcgfx, region->_vrl_rect.vcr_xmin, region->_vrl_rect.vcr_ymin,
	                  region->_vrl_rect.vcr_xdim,
	                  region->_vrl_rect.vcr_ydim);
}


PRIVATE WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
lockable_lock_fallback(struct lockable_buffer *__restrict self,
                       struct video_lock *__restrict lock) {
	lock->vl_data = lockable_getdata(self);
	if unlikely(!lock->vl_data)
		goto err;
	lock->vl_stride = self->lb_stride;
	lockable_readpixels(self);
	return 0;
err:
	return -1;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
lockable_buffer__rlock(struct video_buffer *__restrict self,
                       struct video_lock *__restrict lock) {
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	int ok = video_buffer_rlock(me->lb_base, lock);
	if (ok != 0 && (errno != ENOMEM || me->lb_data)) {
		ok = lockable_lock_fallback(me, lock);
		lock->_vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)0;
	}
	return ok;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
lockable_buffer__wlock(struct video_buffer *__restrict self,
                       struct video_lock *__restrict lock) {
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	int ok = video_buffer_wlock(me->lb_base, lock);
	if (ok != 0 && (errno != ENOMEM || me->lb_data)) {
		ok = lockable_lock_fallback(me, lock);
		lock->_vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)1;
	}
	return ok;
}

INTERN ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC lockable_buffer__unlock)(struct video_buffer *__restrict self,
                                     struct video_lock *__restrict lock) {
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	/* Check for special case: lock was created by underlying buffer */
	if (lock->vl_data != me->lb_data) {
		video_buffer_unlock(me->lb_base, lock);
		return;
	}

	/* Lock was created by **us** -- if it's a write-lock, write back pixel data */
	if (lock->_vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE])
		lockable_writepixels(me);
}


PRIVATE WUNUSED ATTR_INOUT(1) NONNULL((2)) int FCC
lockable_lockregion_fallback(struct lockable_buffer *__restrict self,
                             struct video_regionlock *__restrict lock) {
	lock->vrl_lock.vl_data = lockable_getdata(self);
	if unlikely(!lock->vrl_lock.vl_data)
		goto err;
	lock->vrl_lock.vl_stride = self->lb_stride;
	lock->vrl_lock.vl_data += lock->_vrl_rect.vcr_ymin * lock->vrl_lock.vl_stride;
	lock->vrl_xbas = lock->_vrl_rect.vcr_xmin;
	lockable_readpixels_region(self, lock);
	return 0;
err:
	return -1;
}

INTERN WUNUSED ATTR_INOUT(1) NONNULL((2)) int FCC
lockable_buffer__rlockregion(struct video_buffer *__restrict self,
                             struct video_regionlock *__restrict lock) {
	int ok;
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	video_regionlock_assert(me, lock);
	ok = (me->lb_base->vb_ops->vi_rlockregion)(me->lb_base, lock);
	if (ok != 0 && (errno != ENOMEM || me->lb_data)) {
		ok = lockable_lockregion_fallback(me, lock);
		lock->vrl_lock._vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)0;
	}
	return ok;
}

INTERN WUNUSED ATTR_INOUT(1) NONNULL((2)) int FCC
lockable_buffer__wlockregion(struct video_buffer *__restrict self,
                             struct video_regionlock *__restrict lock) {
	int ok;
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	video_regionlock_assert(me, lock);
	ok = (me->lb_base->vb_ops->vi_wlockregion)(me->lb_base, lock);
	if (ok != 0 && (errno != ENOMEM || me->lb_data)) {
		ok = lockable_lockregion_fallback(me, lock);
		lock->vrl_lock._vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)1;
	}
	return ok;
}

INTERN ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC lockable_buffer__unlockregion)(struct video_buffer *__restrict self,
                                           struct video_regionlock *__restrict lock) {
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	video_regionlock_assert(me, lock);

	/* Check for special case: lock was created by underlying buffer */
	if (lock->vrl_lock.vl_data < me->lb_data ||
	    lock->vrl_lock.vl_data >= me->lb_edata) {
		video_buffer_unlockregion(me->lb_base, lock);
		return;
	}

	/* Lock was created by **us** -- if it's a write-lock, write back pixel data */
	if (lock->vrl_lock._vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE])
		lockable_writepixels_region(me, lock);
}



/* Sub-region locks */
/* Initialize a mock ram-buffer using the video lock of "self" */
PRIVATE ATTR_OUT(1) ATTR_IN(2) void FCC
lockable_subregion_asram(struct video_rambuffer *__restrict rb,
                         struct lockable_buffer_subregion const *__restrict self) {
	DBG_memset(&rb->vb_domain, 0xcc, sizeof(rb->vb_domain));
	video_surface_copyattrib(&rb->vb_surf, &self->vb_surf);
	rb->vb_surf.vs_buffer = rb;
	rb->vb_codec = video_buffer_getcodec(self);
	__video_buffer_init_ops(rb, _rambuffer_ops());
	__video_buffer_init_dim(rb,
	                        video_buffer_getxdim(self) + self->lbsb_bxrem,
	                        video_buffer_getydim(self));
#ifndef NDEBUG
	rb->vb_refcnt = 0; /* So someone incref'ing will fault */
#endif /* !NDEBUG */
	rb->rb_stride = self->lb_stride;
	rb->rb_data   = self->lb_data;
}

/* Read GFX into video lock */
PRIVATE NONNULL((1)) void FCC
lockable_subregion_readpixels(struct lockable_buffer_subregion const *__restrict self) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer dst;
	lockable_subregion_asram(&dst, self);
	p_srcgfx = video_buffer_getgfx_ex(self->lb_base, &srcgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(self->lb_base),
	                                  video_buffer_getflags(self->lb_base) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	p_dstgfx = video_buffer_getgfx_ex(&dst, &dstgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(&dst),
	                                  video_buffer_getflags(&dst) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, self->lbsb_bxrem, 0,
	                  p_srcgfx, self->lbsb_xoff, self->lbsb_yoff,
	                  video_gfx_getxdim(p_dstgfx),
	                  video_gfx_getydim(p_dstgfx));
}

/* Write video lock to GFX */
PRIVATE NONNULL((1)) void FCC
lockable_subregion_writepixels(struct lockable_buffer_subregion const *__restrict self) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer src;
	lockable_subregion_asram(&src, self);
	p_srcgfx = video_buffer_getgfx_ex(&src, &srcgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(&src),
	                                  video_buffer_getflags(&src) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	p_dstgfx = video_buffer_getgfx_ex(self->lb_base, &dstgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(self->lb_base),
	                                  video_buffer_getflags(self->lb_base) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, self->lbsb_xoff, self->lbsb_yoff,
	                  p_srcgfx, self->lbsb_bxrem, 0,
	                  video_gfx_getxdim(p_dstgfx),
	                  video_gfx_getydim(p_dstgfx));
}


/* Read GFX into video lock region */
PRIVATE NONNULL((1, 2)) void FCC
lockable_subregion_readpixels_region(struct lockable_buffer_subregion const *__restrict self,
                                     struct video_regionlock const *__restrict region) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer dst;
	lockable_subregion_asram(&dst, self);
	p_srcgfx = video_buffer_getgfx_ex(self->lb_base, &srcgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(self->lb_base),
	                                  video_buffer_getflags(self->lb_base) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	p_dstgfx = video_buffer_getgfx_ex(&dst, &dstgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(&dst),
	                                  video_buffer_getflags(&dst) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx,
	                  region->_vrl_rect.vcr_xmin + self->lbsb_bxrem,
	                  region->_vrl_rect.vcr_ymin,
	                  p_srcgfx,
	                  region->_vrl_rect.vcr_xmin + self->lbsb_xoff,
	                  region->_vrl_rect.vcr_ymin + self->lbsb_yoff,
	                  region->_vrl_rect.vcr_xdim,
	                  region->_vrl_rect.vcr_ydim);
}

/* Write video lock region to GFX */
PRIVATE NONNULL((1, 2)) void FCC
lockable_subregion_writepixels_region(struct lockable_buffer_subregion const *__restrict self,
                                      struct video_regionlock const *__restrict region) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer src;
	lockable_subregion_asram(&src, self);
	p_srcgfx = video_buffer_getgfx_ex(&src, &srcgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(&src),
	                                  video_buffer_getflags(&src) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	p_dstgfx = video_buffer_getgfx_ex(self->lb_base, &dstgfx, GFX_BLENDMODE_OVERRIDE,
	                                  video_buffer_getpalette(self->lb_base),
	                                  video_buffer_getflags(self->lb_base) & VIDEO_GFX_F_PALOBJ,
	                                  0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx,
	                  region->_vrl_rect.vcr_xmin + self->lbsb_xoff,
	                  region->_vrl_rect.vcr_ymin + self->lbsb_yoff,
	                  p_srcgfx,
	                  region->_vrl_rect.vcr_xmin + self->lbsb_bxrem,
	                  region->_vrl_rect.vcr_ymin,
	                  region->_vrl_rect.vcr_xdim,
	                  region->_vrl_rect.vcr_ydim);
}


PRIVATE WUNUSED ATTR_INOUT(1) byte_t *FCC
lockable_subregion_getdata(struct lockable_buffer_subregion *__restrict self) {
	byte_t *result = atomic_read(&self->lb_data);
	if unlikely(!result) {
		result = lockable_getdata(self->lbsb_lockable);
		if unlikely(!result)
			goto err;
		COMPILER_WRITE_BARRIER();
		self->lb_stride = self->lbsb_lockable->lb_stride;
		result += self->lbsb_bxoff;
		result += self->lbsb_yoff * self->lb_stride;
		self->lb_data = result;
		COMPILER_WRITE_BARRIER();
	}
	return result;
err:
	return NULL;
}



PRIVATE WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
lockable_subregion_lock_fallback(struct lockable_buffer_subregion *__restrict self,
                                 struct video_lock *__restrict lock) {
	lock->vl_data = lockable_subregion_getdata(self);
	if unlikely(!lock->vl_data)
		goto err;
	lock->vl_stride = self->lb_stride;
	lockable_subregion_readpixels(self);
	return 0;
err:
	return -1;
}



INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC
lockable_buffer_subregion__rlock(struct video_buffer *__restrict self,
                                 struct video_lock *__restrict lock) {
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self;
	int ok = video_buffer_rlock(me->lb_base, lock);
	assert(me->lbsb_bxrem == 0);
	if (ok == 0) {
		lock->vl_data += me->lbsb_bxoff;
		lock->vl_data += me->lbsb_yoff * lock->vl_stride;
	} else if (errno != ENOMEM) {
		ok = lockable_subregion_lock_fallback(me, lock);
		lock->_vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)0;
	}
	return ok;
}

INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC
lockable_buffer_subregion__wlock(struct video_buffer *__restrict self,
                                 struct video_lock *__restrict lock) {
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self;
	int ok = video_buffer_wlock(me->lb_base, lock);
	assert(me->lbsb_bxrem == 0);
	if (ok == 0) {
		lock->vl_data += me->lbsb_bxoff;
		lock->vl_data += me->lbsb_yoff * lock->vl_stride;
	} else if (errno != ENOMEM) {
		ok = lockable_subregion_lock_fallback(me, lock);
		lock->_vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)1;
	}
	return ok;
}

INTERN ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC lockable_buffer_subregion__unlock)(struct video_buffer *__restrict self,
                                               struct video_lock *__restrict lock) {
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self;
	/* Check for special case: lock was created by underlying buffer */
	if (lock->vl_data != me->lb_data) {
		lock->vl_data -= me->lbsb_yoff * lock->vl_stride;
		lock->vl_data -= me->lbsb_bxoff;
		video_buffer_unlock(me->lb_base, lock);
		return;
	}

	/* Lock was created by **us** -- if it's a write-lock, write back pixel data */
	if (lock->_vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE])
		lockable_subregion_writepixels(me);
}


PRIVATE WUNUSED ATTR_INOUT(1) NONNULL((2)) int FCC
lockable_subregion_lockregion_fallback(struct lockable_buffer_subregion *__restrict self,
                                       struct video_regionlock *__restrict lock) {
	lock->vrl_lock.vl_data = lockable_subregion_getdata(self);
	if unlikely(!lock->vrl_lock.vl_data)
		goto err;
	lock->vrl_lock.vl_stride = self->lb_stride;
	lock->vrl_lock.vl_data += lock->_vrl_rect.vcr_ymin * lock->vrl_lock.vl_stride;
	lock->vrl_xbas = lock->_vrl_rect.vcr_xmin + self->lbsb_bxrem;
	lockable_subregion_readpixels_region(self, lock);
	return 0;
err:
	return -1;
}

INTERN WUNUSED ATTR_INOUT(1) NONNULL((2)) int FCC
lockable_buffer_subregion__rlockregion(struct video_buffer *__restrict self,
                                       struct video_regionlock *__restrict lock) {
	int ok;
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self;
	video_regionlock_assert(me, lock);
	lock->_vrl_rect.vcr_xmin += me->lbsb_xoff;
	lock->_vrl_rect.vcr_ymin += me->lbsb_yoff;
	ok = (me->lb_base->vb_ops->vi_rlockregion)(me->lb_base, lock);
	if (ok != 0 && (errno != ENOMEM || me->lbsb_lockable->lb_data)) {
		lock->_vrl_rect.vcr_xmin -= me->lbsb_xoff;
		lock->_vrl_rect.vcr_ymin -= me->lbsb_yoff;
		ok = lockable_subregion_lockregion_fallback(me, lock);
		lock->vrl_lock._vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)0;
	}
	return ok;
}

INTERN WUNUSED ATTR_INOUT(1) NONNULL((2)) int FCC
lockable_buffer_subregion__wlockregion(struct video_buffer *__restrict self,
                                       struct video_regionlock *__restrict lock) {
	int ok;
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self;
	video_regionlock_assert(me, lock);
	lock->_vrl_rect.vcr_xmin += me->lbsb_xoff;
	lock->_vrl_rect.vcr_ymin += me->lbsb_yoff;
	ok = (me->lb_base->vb_ops->vi_wlockregion)(me->lb_base, lock);
	if (ok != 0 && (errno != ENOMEM || me->lbsb_lockable->lb_data)) {
		lock->_vrl_rect.vcr_xmin -= me->lbsb_xoff;
		lock->_vrl_rect.vcr_ymin -= me->lbsb_yoff;
		ok = lockable_subregion_lockregion_fallback(me, lock);
		lock->vrl_lock._vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)1;
	}
	return ok;
}

INTERN ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC lockable_buffer_subregion__unlockregion)(struct video_buffer *__restrict self,
                                                     struct video_regionlock *__restrict lock) {
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self;

	/* Check for special case: lock was created by underlying buffer */
	if (lock->vrl_lock.vl_data < me->lb_data ||
	    lock->vrl_lock.vl_data >= me->lb_edata) {
		lock->_vrl_rect.vcr_xmin -= me->lbsb_xoff;
		lock->_vrl_rect.vcr_ymin -= me->lbsb_yoff;
		video_regionlock_assert(me, lock);
		video_buffer_unlockregion(me->lb_base, lock);
		return;
	}

	/* Lock was created by **us** -- if it's a write-lock, write back pixel data */
	video_regionlock_assert(me, lock);
	if (lock->vrl_lock._vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE])
		lockable_subregion_writepixels_region(me, lock);
}






INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
lockable_buffer__initgfx(struct video_gfx *__restrict self) {
	struct lockable_buffer *me = (struct lockable_buffer *)video_gfx_getbuffer(self);
	return (*(self->vx_surf.vs_buffer = me->lb_base)->vb_ops->vi_initgfx)(self);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
lockable_buffer_subregion__initgfx(struct video_gfx *__restrict self) {
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)video_gfx_getbuffer(self);
	video_dim_t xdim, ydim;
	self = (*(self->vx_surf.vs_buffer = me->lb_base)->vb_ops->vi_initgfx)(self);
	xdim = video_buffer_getxdim(me);
	ydim = video_buffer_getydim(me);
	if (video_gfx_getflags(self) & VIDEO_GFX_F_XYSWAP) {
		video_dim_t temp = xdim;
		xdim = ydim;
		ydim = temp;
	}
	return video_gfx_clip(self,
	                      me->lbsb_xoff,
	                      me->lbsb_yoff,
	                      xdim, ydim);
}



INTERN ATTR_PURE WUNUSED ATTR_IN(1) bool CC
libvideo_buffer_islockable(struct video_buffer const *__restrict self) {
	/* List of RAM-domain buffers that are known to always be lockable */
	if (video_buffer_getdomain(self) == &libvideo_ramdomain) {
		if (self->vb_ops == &lockable_buffer_ops)
			goto yes;
		if (self->vb_ops == &lockable_buffer_subregion_norem_ops)
			goto yes;
		if (self->vb_ops == &rambuffer_ops)
			goto yes;
		if (self->vb_ops == &rambuffer_subregion_ops)
			goto yes;
		if (self->vb_ops == &rambuffer_formem_ops)
			goto yes;
	}
	return false;
yes:
	return true;
}


/* Wrap `surface' as the surface of a lockable buffer. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_OUT(1) ATTR_IN(2) struct video_surface const *CC
lockable_buffer_init(struct lockable_buffer *self,
                         struct video_surface const *__restrict surface) {
	struct video_buffer *base = video_surface_getbuffer(surface);
	video_surface_copyattrib(&self->vb_surf, surface);
	self->vb_surf.vs_buffer = self;
	self->vb_codec = video_buffer_getcodec(base);
	__video_buffer_init_ops(self, _lockable_buffer_ops());
	__video_buffer_init_dim(self, video_buffer_getxdim(base), video_buffer_getydim(base));
#ifndef NDEBUG
	self->vb_refcnt = 0;
#endif /* !NDEBUG */
	self->lb_base  = base;
	self->lb_data  = NULL;
	self->lb_edata = NULL;
	DBG_memset(&self->lb_stride, 0xcc, sizeof(self->lb_stride));
	return video_buffer_assurface(self);
}


/* When `self' isn't  known to unconditionally  support read/write  locks,
 * wrap it using a proxy video buffer that implements these operations as:
 * - Attempt the lock on the underlying buffer.
 * - If that fails:
 *   - Allocate a heap buffer matching requirements of the buffer's codec
 *   - If that fails, return from vi_rlock/vi_wlock with -1,errno=ENOMEM
 *   - On success, use a GFX context to read pixel data and store it in
 *     the heap buffer.
 *   - Return said heap buffer from vi_rlock/vi_wlock
 * - In case `vi_wlock' was called, the matching `vi_unlock' will  then
 *   once again use a GFX context to at least all modified (or possibly
 *   just all) pixels back to the underlying buffer.
 * @param: self:  The video surface to wrap
 * @return: * :   The video buffer wrapper (having the same codec/dimensions as `self')
 * @return: self: The given `self' is already  known to have vi_rlock/vi_wlock  operators
 *                that either never fail, or can only fail with errno=ENOMEM for the same
 *                reason that the  "lockable" wrapper could  also fail. (generally,  this
 *                means that this is a no-op when  `self' is a ram-buffer, or is  already
 *                a "lockable" video buffer). */
DEFINE_PUBLIC_ALIAS(video_surface_lockable, libvideo_surface_lockable);
DEFINE_PUBLIC_ALIAS(video_surface_lockable_distinct, libvideo_surface_lockable_distinct);
INTERN WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_surface_lockable(struct video_surface const *__restrict self) {
	/* Check for special cases where we can re-return "self" */
	struct video_buffer *buffer = video_surface_getbuffer(self);
	if (libvideo_buffer_islockable(buffer) && video_surface_isdefault(self)) {
		video_buffer_incref(buffer);
		return buffer;
	}
	return libvideo_surface_lockable_distinct(self);
}

INTERN WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_surface_lockable_distinct(struct video_surface const *__restrict self) {
	REF struct lockable_buffer *result;
	struct video_buffer *buffer = video_surface_getbuffer(self);

	/* Allocate the wrapper */
	result = (REF struct lockable_buffer *)malloc(sizeof(struct lockable_buffer));
	if unlikely(!result)
		goto err;
	video_surface_copyattrib(&result->vb_surf, self);
	result->vb_codec  = video_buffer_getcodec(buffer);
	result->vb_domain = _libvideo_ramdomain();
	__video_buffer_init_ops(result, _lockable_buffer_ops());
	__video_buffer_init_dim(result, video_buffer_getxdim(buffer), video_buffer_getydim(buffer));
	video_buffer_incref(buffer);
	result->lb_base  = buffer;
	result->lb_data  = NULL;
	result->lb_edata = NULL;
	DBG_memset(&result->lb_stride, 0xcc, sizeof(result->lb_stride));
	__video_buffer_init_common(result);
	return result;
err:
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_LOCKABLE_C */
