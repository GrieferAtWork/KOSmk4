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
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/palette.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "../buffer.h"
#include "../ramdomain.h"
#include "lockable.h"
#include "region.h"
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
                         lockable_buffer_subregion__revoke, lockable_buffer_subregion__subregion);
DEFINE_VIDEO_BUFFER_TYPE(lockable_buffer_subregion_norem_ops,
                         lockable_buffer_subregion__destroy, lockable_buffer_subregion__initgfx, lockable_buffer__updategfx,
                         lockable_buffer_subregion__rlock, lockable_buffer_subregion__wlock, lockable_buffer_subregion__unlock,
                         lockable_buffer_subregion__rlockregion, lockable_buffer_subregion__wlockregion, lockable_buffer_subregion__unlockregion,
                         lockable_buffer_subregion__revoke, lockable_buffer_subregion__subregion);



PRIVATE WUNUSED ATTR_INOUT(1) byte_t *FCC
lockable_getdata(struct lockable_buffer_base *__restrict self) {
	byte_t *result = atomic_read(&self->lbb_data);
	if (!result) {
		struct video_rambuffer_requirements req;
		(*self->vb_format.vf_codec->vc_rambuffer_requirements)(self->vb_xdim, self->vb_ydim, &req);
		result = (byte_t *)calloc(req.vbs_bufsize);
		if unlikely(!result)
			goto err;
		self->lbb_stride = req.vbs_stride;
		if (!atomic_cmpxch(&self->lbb_data, NULL, result)) {
			byte_t *new_result = atomic_read(&self->lbb_data);
			assert(new_result);
			free(result);
			result = new_result;
		}
		self->lbb_edata = result + req.vbs_bufsize;
		COMPILER_WRITE_BARRIER();
	}
	return result;
err:
	return NULL;
}


INTERN NONNULL((1)) void FCC
lockable_buffer__destroy(struct video_buffer *__restrict self) {
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	assert(LIST_EMPTY(&me->lb_subregion_list));
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
	video_buffer_decref(me->lbb_base);
	free(me->lbb_data);
	free(me);
}

INTERN NONNULL((1)) void FCC
lockable_buffer_subregion__destroy(struct video_buffer *__restrict self) {
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self;
	assert(LIST_EMPTY(&me->lb_subregion_list));
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
	video_buffer_decref(me->lbsb_parent);
	free(me);
}


PRIVATE ATTR_INOUT(1) void
NOTHROW(FCC lockable_buffer__revoke_common)(struct lockable_buffer *__restrict self) {
	atomic_lock_acquire(&self->lb_subregion_lock);
	while (!LIST_EMPTY(&self->lb_subregion_list)) {
		REF struct lockable_buffer_subregion *sr = LIST_FIRST(&self->lb_subregion_list);
		if (!tryincref(sr)) {
			LIST_UNBIND(sr, lbsb_chain);
		} else {
			atomic_lock_release(&self->lb_subregion_lock);
			sr = (REF struct lockable_buffer_subregion *)video_buffer_revoke(sr);
			video_buffer_decref(sr);
			atomic_lock_acquire(&self->lb_subregion_lock);
		}
	}
	atomic_lock_release(&self->lb_subregion_lock);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC lockable_buffer__revoke)(struct video_buffer *__restrict self) {
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	video_buffer_revoke(me->lbb_base);
	lockable_buffer__revoke_common(me);
	return me;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC lockable_buffer_subregion__revoke)(struct video_buffer *__restrict self) {
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self;
	struct lockable_buffer *parent = me->lbsb_parent;
	atomic_lock_acquire(&parent->lb_subregion_lock);
	if (LIST_ISBOUND(me, lbsb_chain))
		LIST_UNBIND(me, lbsb_chain);
	atomic_lock_release(&parent->lb_subregion_lock);
	lockable_buffer__revoke_common(me);
	return me;
}

PRIVATE WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC
lockable_buffer__subregion_impl(struct lockable_buffer *__restrict self,
                                struct video_crect const *__restrict rect,
                                gfx_flag_t xor_flags,
                                video_coord_t base_xoff,
                                video_coord_t base_yoff) {
	REF struct lockable_buffer_subregion *result;
	base_xoff += rect->vcr_xmin;
	base_yoff += rect->vcr_ymin;
	result = (REF struct lockable_buffer_subregion *)malloc(sizeof(struct lockable_buffer_subregion));
	if unlikely(!result)
		goto err;
	result->lbb_data   = NULL;
	result->vb_domain  = _libvideo_ramdomain();
	result->vb_format  = self->vb_format;
	result->vb_xdim    = rect->vcr_xdim;
	result->vb_ydim    = rect->vcr_ydim;
	result->vb_refcnt  = 1;
	result->lbb_stride = self->lbb_stride;
	result->lbb_data += base_yoff * result->lbb_stride;
	result->lbb_data += base_yoff * result->lbb_stride;
	video_codec_xcoord_to_offset(result->vb_format.vf_codec, base_xoff,
	                             &result->lbsb_bxoff, &result->lbsb_bxrem);
	result->lbsb_xoff   = base_xoff;
	result->lbsb_yoff   = base_yoff;
	result->lbsb_xor    = xor_flags;
	result->lbsb_parent = self;
	video_buffer_incref(self);
	if (result->vb_format.vf_pal)
		video_palette_incref(result->vb_format.vf_pal);
	result->vb_ops = result->lbsb_bxrem ? _lockable_buffer_subregion_ops()
	                                    : _lockable_buffer_subregion_norem_ops();
	atomic_lock_acquire(&self->lb_subregion_lock);
	LIST_INSERT_HEAD(&self->lb_subregion_list, result, lbsb_chain);
	atomic_lock_release(&self->lb_subregion_lock);
	return result;
err:
	return NULL;
}


INTERN WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC
lockable_buffer__subregion(struct video_buffer *__restrict self,
                           struct video_crect const *__restrict rect,
                           gfx_flag_t xor_flags) {
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	return lockable_buffer__subregion_impl(me, rect, xor_flags, 0, 0);
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC
lockable_buffer_subregion__subregion(struct video_buffer *__restrict self,
                                     struct video_crect const *__restrict rect,
                                     gfx_flag_t xor_flags) {
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self;
	return lockable_buffer__subregion_impl(me, rect,
	                                       gfx_flag_combine(me->lbsb_xor, xor_flags),
	                                       me->lbsb_xoff, me->lbsb_yoff);
}




/* Indices into `struct video_lock::_vl_driver' */
#define LOCKABLE_BUFFER_VLOCK_ISWRITE 0
static_assert(_VIDEO_LOCK__N_DRIVER >= 1);

/* Initialize a mock ram-buffer using the video lock of "self" */
PRIVATE ATTR_OUT(1) ATTR_IN(2) void FCC
lockable_asram(struct video_rambuffer_base *__restrict rb,
               struct lockable_buffer_base const *__restrict self) {
	DBG_memset(&rb->vb_domain, 0xcc, sizeof(rb->vb_domain));
	rb->vb_ops    = _rambuffer_ops();
	rb->vb_format = self->vb_format;
	rb->vb_xdim   = self->vb_xdim;
	rb->vb_ydim   = self->vb_ydim;
#ifndef NDEBUG
	rb->vb_refcnt = 0; /* So someone incref'ing will fault */
#endif /* !NDEBUG */
	rb->rb_stride = self->lbb_stride;
	rb->rb_data   = self->lbb_data;
}

/* Read GFX into video lock */
PRIVATE NONNULL((1)) void FCC
lockable_readpixels(struct lockable_buffer_base const *__restrict self) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer_base dst;
	lockable_asram(&dst, self);
	p_srcgfx = video_buffer_getgfx(self->lbb_base, &srcgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	p_dstgfx = video_buffer_getgfx(&dst, &dstgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, 0, 0,
	                  p_srcgfx, 0, 0,
	                  video_gfx_getclipw(p_dstgfx),
	                  video_gfx_getcliph(p_dstgfx));
}

/* Write video lock to GFX */
PRIVATE NONNULL((1)) void FCC
lockable_writepixels(struct lockable_buffer_base const *__restrict self) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer_base src;
	lockable_asram(&src, self);
	p_srcgfx = video_buffer_getgfx(&src, &srcgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	p_dstgfx = video_buffer_getgfx(self->lbb_base, &dstgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, 0, 0, p_srcgfx, 0, 0,
	                  video_gfx_getclipw(p_dstgfx),
	                  video_gfx_getcliph(p_dstgfx));
}


/* Read GFX into video lock region */
PRIVATE NONNULL((1, 2)) void FCC
lockable_readpixels_region(struct lockable_buffer_base const *__restrict self,
                           struct video_regionlock const *__restrict region) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer_base dst;
	lockable_asram(&dst, self);
	p_srcgfx = video_buffer_getgfx(self->lbb_base, &srcgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	p_dstgfx = video_buffer_getgfx(&dst, &dstgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, region->_vrl_rect.vcr_xmin, region->_vrl_rect.vcr_ymin,
	                  p_srcgfx, region->_vrl_rect.vcr_xmin, region->_vrl_rect.vcr_ymin,
	                  region->_vrl_rect.vcr_xdim,
	                  region->_vrl_rect.vcr_ydim);
}

/* Write video lock region to GFX */
PRIVATE NONNULL((1, 2)) void FCC
lockable_writepixels_region(struct lockable_buffer_base const *__restrict self,
                            struct video_regionlock const *__restrict region) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer_base src;
	lockable_asram(&src, self);
	p_srcgfx = video_buffer_getgfx(&src, &srcgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	p_dstgfx = video_buffer_getgfx(self->lbb_base, &dstgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, region->_vrl_rect.vcr_xmin, region->_vrl_rect.vcr_ymin,
	                  p_srcgfx, region->_vrl_rect.vcr_xmin, region->_vrl_rect.vcr_ymin,
	                  region->_vrl_rect.vcr_xdim,
	                  region->_vrl_rect.vcr_ydim);
}


PRIVATE WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
lockable_lock_fallback(struct lockable_buffer_base *__restrict self,
                       struct video_lock *__restrict lock) {
	lock->vl_data = lockable_getdata(self);
	if unlikely(!lock->vl_data)
		goto err;
	lock->vl_stride = self->lbb_stride;
	lockable_readpixels(self);
	return 0;
err:
	return -1;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
lockable_buffer__rlock(struct video_buffer *__restrict self,
                       struct video_lock *__restrict lock) {
	struct lockable_buffer_base *me = (struct lockable_buffer_base *)self;
	int ok = video_buffer_rlock(me->lbb_base, lock);
	if (ok != 0 && (errno != ENOMEM || me->lbb_data)) {
		ok = lockable_lock_fallback(me, lock);
		lock->_vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)0;
	}
	return ok;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
lockable_buffer__wlock(struct video_buffer *__restrict self,
                       struct video_lock *__restrict lock) {
	struct lockable_buffer_base *me = (struct lockable_buffer_base *)self;
	int ok = video_buffer_wlock(me->lbb_base, lock);
	if (ok != 0 && (errno != ENOMEM || me->lbb_data)) {
		ok = lockable_lock_fallback(me, lock);
		lock->_vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)1;
	}
	return ok;
}

INTERN ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC lockable_buffer__unlock)(struct video_buffer *__restrict self,
                                     struct video_lock *__restrict lock) {
	struct lockable_buffer_base *me = (struct lockable_buffer_base *)self;
	/* Check for special case: lock was created by underlying buffer */
	if (lock->vl_data != me->lbb_data) {
		video_buffer_unlock(me->lbb_base, lock);
		return;
	}

	/* Lock was created by **us** -- if it's a write-lock, write back pixel data */
	if (lock->_vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE])
		lockable_writepixels(me);
}


PRIVATE WUNUSED ATTR_INOUT(1) NONNULL((2)) int FCC
lockable_lockregion_fallback(struct lockable_buffer_base *__restrict self,
                             struct video_regionlock *__restrict lock) {
	lock->vrl_lock.vl_data = lockable_getdata(self);
	if unlikely(!lock->vrl_lock.vl_data)
		goto err;
	lock->vrl_lock.vl_stride = self->lbb_stride;
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
	struct lockable_buffer_base *me = (struct lockable_buffer_base *)self;
	video_regionlock_assert(me, lock);
	ok = (me->lbb_base->vb_ops->vi_rlockregion)(me->lbb_base, lock);
	if (ok != 0 && (errno != ENOMEM || me->lbb_data)) {
		ok = lockable_lockregion_fallback(me, lock);
		lock->vrl_lock._vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)0;
	}
	return ok;
}

INTERN WUNUSED ATTR_INOUT(1) NONNULL((2)) int FCC
lockable_buffer__wlockregion(struct video_buffer *__restrict self,
                             struct video_regionlock *__restrict lock) {
	int ok;
	struct lockable_buffer_base *me = (struct lockable_buffer_base *)self;
	video_regionlock_assert(me, lock);
	ok = (me->lbb_base->vb_ops->vi_wlockregion)(me->lbb_base, lock);
	if (ok != 0 && (errno != ENOMEM || me->lbb_data)) {
		ok = lockable_lockregion_fallback(me, lock);
		lock->vrl_lock._vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)1;
	}
	return ok;
}

INTERN ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC lockable_buffer__unlockregion)(struct video_buffer *__restrict self,
                                           struct video_regionlock *__restrict lock) {
	struct lockable_buffer_base *me = (struct lockable_buffer_base *)self;
	video_regionlock_assert(me, lock);

	/* Check for special case: lock was created by underlying buffer */
	if (lock->vrl_lock.vl_data < me->lbb_data ||
	    lock->vrl_lock.vl_data >= me->lbb_edata) {
		video_buffer_unlockregion(me->lbb_base, lock);
		return;
	}

	/* Lock was created by **us** -- if it's a write-lock, write back pixel data */
	if (lock->vrl_lock._vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE])
		lockable_writepixels_region(me, lock);
}



/* Sub-region locks */
/* Initialize a mock ram-buffer using the video lock of "self" */
PRIVATE ATTR_OUT(1) ATTR_IN(2) void FCC
lockable_subregion_asram(struct video_rambuffer_base *__restrict rb,
                         struct lockable_buffer_subregion const *__restrict self) {
	DBG_memset(&rb->vb_domain, 0xcc, sizeof(rb->vb_domain));
	rb->vb_ops    = _rambuffer_ops();
	rb->vb_format = self->vb_format;
	rb->vb_xdim   = self->vb_xdim + self->lbsb_bxrem;
	rb->vb_ydim   = self->vb_ydim;
#ifndef NDEBUG
	rb->vb_refcnt = 0; /* So someone incref'ing will fault */
#endif /* !NDEBUG */
	rb->rb_stride = self->lbb_stride;
	rb->rb_data   = self->lbb_data;
}

/* Read GFX into video lock */
PRIVATE NONNULL((1)) void FCC
lockable_subregion_readpixels(struct lockable_buffer_subregion const *__restrict self) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer_base dst;
	lockable_subregion_asram(&dst, self);
	p_srcgfx = video_buffer_getgfx(self->lbb_base, &srcgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	p_dstgfx = video_buffer_getgfx(&dst, &dstgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, self->lbsb_bxrem, 0,
	                  p_srcgfx, self->lbsb_xoff, self->lbsb_yoff,
	                  video_gfx_getclipw(p_dstgfx),
	                  video_gfx_getcliph(p_dstgfx));
}

/* Write video lock to GFX */
PRIVATE NONNULL((1)) void FCC
lockable_subregion_writepixels(struct lockable_buffer_subregion const *__restrict self) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer_base src;
	lockable_subregion_asram(&src, self);
	p_srcgfx = video_buffer_getgfx(&src, &srcgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	p_dstgfx = video_buffer_getgfx(self->lbb_base, &dstgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, self->lbsb_xoff, self->lbsb_yoff,
	                  p_srcgfx, self->lbsb_bxrem, 0,
	                  video_gfx_getclipw(p_dstgfx),
	                  video_gfx_getcliph(p_dstgfx));
}


/* Read GFX into video lock region */
PRIVATE NONNULL((1, 2)) void FCC
lockable_subregion_readpixels_region(struct lockable_buffer_subregion const *__restrict self,
                                     struct video_regionlock const *__restrict region) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct video_rambuffer_base dst;
	lockable_subregion_asram(&dst, self);
	p_srcgfx = video_buffer_getgfx(self->lbb_base, &srcgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	p_dstgfx = video_buffer_getgfx(&dst, &dstgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
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
	struct video_rambuffer_base src;
	lockable_subregion_asram(&src, self);
	p_srcgfx = video_buffer_getgfx(&src, &srcgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	p_dstgfx = video_buffer_getgfx(self->lbb_base, &dstgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
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
	byte_t *result = atomic_read(&self->lbb_data);
	if unlikely(!result) {
		result = lockable_getdata(self->lbsb_orig);
		if unlikely(!result)
			goto err;
		COMPILER_WRITE_BARRIER();
		self->lbb_stride = self->lbsb_orig->lbb_stride;
		result += self->lbsb_bxoff;
		result += self->lbsb_yoff * self->lbb_stride;
		self->lbb_data = result;
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
	lock->vl_stride = self->lbb_stride;
	lockable_subregion_readpixels(self);
	return 0;
err:
	return -1;
}



INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC
lockable_buffer_subregion__rlock(struct video_buffer *__restrict self,
                                 struct video_lock *__restrict lock) {
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self;
	int ok = video_buffer_rlock(me->lbb_base, lock);
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
	int ok = video_buffer_wlock(me->lbb_base, lock);
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
	if (lock->vl_data != me->lbb_data) {
		lock->vl_data -= me->lbsb_yoff * lock->vl_stride;
		lock->vl_data -= me->lbsb_bxoff;
		video_buffer_unlock(me->lbb_base, lock);
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
	lock->vrl_lock.vl_stride = self->lbb_stride;
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
	ok = (me->lbb_base->vb_ops->vi_rlockregion)(me->lbb_base, lock);
	if (ok != 0 && (errno != ENOMEM || me->lbsb_orig->lbb_data)) {
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
	ok = (me->lbb_base->vb_ops->vi_wlockregion)(me->lbb_base, lock);
	if (ok != 0 && (errno != ENOMEM || me->lbsb_orig->lbb_data)) {
		ok = lockable_subregion_lockregion_fallback(me, lock);
		lock->vrl_lock._vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)1;
	}
	return ok;
}

INTERN ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC lockable_buffer_subregion__unlockregion)(struct video_buffer *__restrict self,
                                                     struct video_regionlock *__restrict lock) {
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self;
	video_regionlock_assert(me, lock);

	/* Check for special case: lock was created by underlying buffer */
	if (lock->vrl_lock.vl_data < me->lbb_data ||
	    lock->vrl_lock.vl_data >= me->lbb_edata) {
		video_buffer_unlockregion(me->lbb_base, lock);
		return;
	}

	/* Lock was created by **us** -- if it's a write-lock, write back pixel data */
	if (lock->vrl_lock._vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE])
		lockable_subregion_writepixels_region(me, lock);
}






INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
lockable_buffer__initgfx(struct video_gfx *__restrict self) {
	struct lockable_buffer_base *me = (struct lockable_buffer_base *)self->vx_buffer;
	struct video_buffer *base = me->lbb_base;
	self->vx_buffer = base; /* This is allowed! */
	return (*base->vb_ops->vi_initgfx)(self);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
lockable_buffer_subregion__initgfx(struct video_gfx *__restrict self) {
	struct lockable_buffer_subregion *me = (struct lockable_buffer_subregion *)self->vx_buffer;
	struct video_buffer *base = me->lbb_base;
	self->vx_flags = gfx_flag_combine(me->lbsb_xor, self->vx_flags);
	self->vx_buffer = base; /* This is allowed! */
	self = (*base->vb_ops->vi_initgfx)(self);
	/* Set clip rect to our relevant sub-region */
	return video_gfx_clip(self, me->lbsb_xoff, me->lbsb_yoff,
	                      me->vb_xdim, me->vb_ydim);
}


INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
lockable_buffer__updategfx(struct video_gfx *__restrict self, unsigned int what) {
	struct lockable_buffer_base *me = (struct lockable_buffer_base *)self->vx_buffer;
	struct video_buffer *base = me->lbb_base;
	self->vx_buffer = base; /* This is allowed! */
	return (*base->vb_ops->vi_updategfx)(self, what);
}



PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) bool CC
video_buffer_islockable(struct video_buffer const *__restrict self) {
	/* List of RAM-domain buffers that are known to always be lockable */
	if (self->vb_domain == &libvideo_ramdomain) {
		if (self->vb_ops == &lockable_buffer_ops)
			goto yes;
		if (self->vb_ops == &lockable_buffer_subregion_norem_ops)
			goto yes;
		if (self->vb_ops == &rambuffer_ops)
			goto yes;
		if (self->vb_ops == &rambuffer_xcodec_ops)
			goto yes;
		if (self->vb_ops == &rambuffer_subregion_ops)
			goto yes;
		if (self->vb_ops == &rambuffer_subsubregion_ops)
			goto yes;
		if (self->vb_ops == &rambuffer_formem_ops)
			goto yes;
		if (self->vb_ops == &rambuffer_formem_xcodec_ops)
			goto yes;
		if (self->vb_ops == &rambuffer_formem_subregion_ops)
			goto yes;
		if (self->vb_ops == &region_buffer_subregion_alias_ops) {
			/* Region alias buffers are locked iff the underlying buffer is.
			 * Note that other region buffers are never lockable, since they
			 * always contain at least 1 pixel that is out-of-bounds of some
			 * base buffer (meaning not **all** pixels are lockable) */
			struct region_buffer_subregion_alias const *me;
			me = (struct region_buffer_subregion_alias const *)self;
			return video_buffer_islockable(me->rbf_base);
		}
	}
	return false;
yes:
	return true;
}


/* Check if `buffer'  is lockable. If  so re-return  "buffer"
 * and initialize `self' such that `lockable_buffer_finibase'
 * does nothing. Else, wrap it using `buffer' and return *it*
 * instead. */
INTERN WUNUSED ATTR_OUT(1) NONNULL((2)) struct video_buffer *CC
lockable_buffer_initbase(struct lockable_buffer_base *self,
                         struct video_buffer *__restrict buffer) {
	if (video_buffer_islockable(buffer))
		return buffer;
	self->vb_ops    = _lockable_buffer_ops();
	self->vb_format = buffer->vb_format;
	self->vb_xdim   = buffer->vb_xdim;
	self->vb_ydim   = buffer->vb_ydim;
#ifndef NDEBUG
	self->vb_refcnt = 0;
#endif /* !NDEBUG */
	self->lbb_base  = buffer;
	self->lbb_data  = NULL;
	self->lbb_edata = NULL;
	DBG_memset(&self->lbb_stride, 0xcc, sizeof(self->lbb_stride));
	return self;
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
 * @param: self:  The video buffer to wrap
 * @return: * :   The video buffer wrapper (having the same codec/dimensions as `self')
 * @return: self: The given `self' is already  known to have vi_rlock/vi_wlock  operators
 *                that either never fail, or can only fail with errno=ENOMEM for the same
 *                reason that the  "lockable" wrapper could  also fail. (generally,  this
 *                means that this is a no-op when  `self' is a ram-buffer, or is  already
 *                a "lockable" video buffer). */
DEFINE_PUBLIC_ALIAS(video_buffer_lockable, libvideo_buffer_lockable);
INTERN WUNUSED ATTR_INOUT(1) REF struct video_buffer *CC
libvideo_buffer_lockable(struct video_buffer *__restrict self) {
	REF struct lockable_buffer *result;

	/* Check for special cases where we can re-return "self" */
	if (video_buffer_islockable(self)) {
		video_buffer_incref(self);
		return self;
	}

	/* Allocate the wrapper */
	result = (REF struct lockable_buffer *)malloc(sizeof(struct lockable_buffer));
	if unlikely(!result)
		goto err;
	result->vb_ops    = _lockable_buffer_ops();
	result->vb_domain = _libvideo_ramdomain();
	result->vb_format = self->vb_format;
	result->vb_xdim   = self->vb_xdim;
	result->vb_ydim   = self->vb_ydim;
	result->vb_refcnt = 1;
	video_buffer_incref(self);
	result->lbb_base  = self;
	result->lbb_data  = NULL;
	result->lbb_edata = NULL;
	if (result->vb_format.vf_pal)
		video_palette_incref(result->vb_format.vf_pal);
	DBG_memset(&result->lbb_stride, 0xcc, sizeof(result->lbb_stride));
	LIST_INIT(&result->lb_subregion_list);
	atomic_lock_init(&result->lb_subregion_lock);
	return result;
err:
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_LOCKABLE_C */
