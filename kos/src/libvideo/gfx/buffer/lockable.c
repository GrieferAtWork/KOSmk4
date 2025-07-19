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
#include "old-gfx.h"
#include "lockable.h"
#include "old-ram.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#undef LOCKABLE_BUFFER_PALREF
#if 0
#define LOCKABLE_BUFFER_PALREF
#endif

/* Indices into `struct video_lock::_vl_driver' */
#define LOCKABLE_BUFFER_VLOCK_ISWRITE 0
static_assert(_VIDEO_LOCK__N_DRIVER >= 1);

/* Initialize a mock ram-buffer using the video lock of "self" */
PRIVATE ATTR_OUT(1) ATTR_IN(2) void FCC
lockable_asram(struct old_video_rambuffer *__restrict rb,
               struct lockable_buffer const *__restrict self) {
	rb->vb_ops             = _old_rambuffer_ops();
	rb->vb_format.vf_codec = self->vb_format.vf_codec;
	rb->vb_format.vf_pal   = self->vb_format.vf_pal;
	rb->vb_xdim            = self->vb_xdim;
	rb->vb_ydim            = self->vb_ydim;
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
	struct old_video_rambuffer dst;
	lockable_asram(&dst, self);
	p_srcgfx = video_buffer_getgfx(self->lb_base, &srcgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
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
lockable_writepixels(struct lockable_buffer const *__restrict self) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct old_video_rambuffer src;
	lockable_asram(&src, self);
	p_srcgfx = video_buffer_getgfx(&src, &srcgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	p_dstgfx = video_buffer_getgfx(self->lb_base, &dstgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, 0, 0, p_srcgfx, 0, 0,
	                  video_gfx_getclipw(p_dstgfx),
	                  video_gfx_getcliph(p_dstgfx));
}


/* Read GFX into video lock region */
PRIVATE NONNULL((1, 2)) void FCC
lockable_readpixels_region(struct lockable_buffer const *__restrict self,
                           struct video_regionlock const *__restrict region) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct old_video_rambuffer dst;
	lockable_asram(&dst, self);
	p_srcgfx = video_buffer_getgfx(self->lb_base, &srcgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	p_dstgfx = video_buffer_getgfx(&dst, &dstgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, region->_vrl_rect.vcr_xmin, region->_vrl_rect.vcr_ymin,
	                  p_srcgfx, region->_vrl_rect.vcr_xmin, region->_vrl_rect.vcr_ymin,
	                  video_gfx_getclipw(p_dstgfx),
	                  video_gfx_getcliph(p_dstgfx));
}

/* Write video lock region to GFX */
PRIVATE NONNULL((1, 2)) void FCC
lockable_writepixels_region(struct lockable_buffer const *__restrict self,
                            struct video_regionlock const *__restrict region) {
	struct video_gfx srcgfx, *p_srcgfx;
	struct video_gfx dstgfx, *p_dstgfx;
	struct old_video_rambuffer src;
	lockable_asram(&src, self);
	p_srcgfx = video_buffer_getgfx(&src, &srcgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	p_dstgfx = video_buffer_getgfx(self->lb_base, &dstgfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	assert(p_dstgfx == &dstgfx);
	assert(p_srcgfx == &srcgfx);
	video_gfx_bitblit(p_dstgfx, region->_vrl_rect.vcr_xmin, region->_vrl_rect.vcr_ymin,
	                  p_srcgfx, region->_vrl_rect.vcr_xmin, region->_vrl_rect.vcr_ymin,
	                  region->_vrl_rect.vcr_xdim,
	                  region->_vrl_rect.vcr_ydim);
}


PRIVATE NONNULL((1)) void FCC
lockable_destroy(struct video_buffer *__restrict self) {
	struct lockable_buffer *me = (struct lockable_buffer *)self;
#ifdef LOCKABLE_BUFFER_PALREF
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
#endif /* LOCKABLE_BUFFER_PALREF */
	video_buffer_decref(me->lb_base);
	free(me->lb_data);
	free(me);
}

PRIVATE WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
lockable_lock_fallback(struct lockable_buffer *__restrict self,
                       struct video_lock *__restrict lock) {
	/* If not already done, allocate a buffer */
	lock->vl_data = atomic_read(&self->lb_data);
	if (!lock->vl_data) {
		byte_t *buffer;
		struct video_rambuffer_requirements req;
		(*self->vb_format.vf_codec->vc_rambuffer_requirements)(self->vb_xdim, self->vb_ydim, &req);
		buffer = (byte_t *)calloc(req.vbs_bufsize);
		if unlikely(!buffer)
			goto err;
		self->lb_stride = req.vbs_stride;
		lock->vl_data = buffer;
		if (!atomic_cmpxch(&self->lb_data, NULL, buffer)) {
			lock->vl_data = atomic_read(&self->lb_data);
			assert(lock->vl_data);
			free(buffer);
		}
		self->lb_edata = lock->vl_data + req.vbs_bufsize;
		COMPILER_WRITE_BARRIER();
	}
	lock->vl_stride = self->lb_stride;
	lockable_readpixels(self);
	return 0;
err:
	return -1;
}

PRIVATE WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
lockable_rlock(struct video_buffer *__restrict self,
               struct video_lock *__restrict lock) {
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	int ok = video_buffer_rlock(me->lb_base, lock);
	if (ok != 0 && errno != ENOMEM) {
		ok = lockable_lock_fallback(me, lock);
		lock->_vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)0;
	}
	return ok;
}

PRIVATE WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC
lockable_wlock(struct video_buffer *__restrict self,
               struct video_lock *__restrict lock) {
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	int ok = video_buffer_wlock(me->lb_base, lock);
	if (ok != 0 && errno != ENOMEM) {
		ok = lockable_lock_fallback(me, lock);
		lock->_vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)1;
	}
	return ok;
}

PRIVATE ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC lockable_unlock)(struct video_buffer *__restrict self,
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
	/* If not already done, allocate a buffer */
	lock->vrl_lock.vl_data = atomic_read(&self->lb_data);
	if (!lock->vrl_lock.vl_data) {
		byte_t *buffer;
		struct video_rambuffer_requirements req;
		(*self->vb_format.vf_codec->vc_rambuffer_requirements)(self->vb_xdim, self->vb_ydim, &req);
		buffer = (byte_t *)calloc(req.vbs_bufsize);
		if unlikely(!buffer)
			goto err;
		self->lb_stride = req.vbs_stride;
		lock->vrl_lock.vl_data = buffer;
		if (!atomic_cmpxch(&self->lb_data, NULL, buffer)) {
			lock->vrl_lock.vl_data = atomic_read(&self->lb_data);
			assert(lock->vrl_lock.vl_data);
			free(buffer);
		}
		self->lb_edata = lock->vrl_lock.vl_data + req.vbs_bufsize;
		COMPILER_WRITE_BARRIER();
	}
	lock->vrl_lock.vl_stride = self->lb_stride;
	lock->vrl_lock.vl_data += lock->_vrl_rect.vcr_ymin * lock->vrl_lock.vl_stride;
	lock->vrl_xbas = lock->_vrl_rect.vcr_xmin;
	lockable_readpixels_region(self, lock);
	return 0;
err:
	return -1;
}

PRIVATE WUNUSED ATTR_INOUT(1) NONNULL((2)) int FCC
lockable_rlockregion(struct video_buffer *__restrict self,
                     struct video_regionlock *__restrict lock) {
	int ok;
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	video_regionlock_assert(me, lock);
	ok = (me->lb_base->vb_ops->vi_rlockregion)(me->lb_base, lock);
	if (ok != 0 && errno != ENOMEM) {
		ok = lockable_lockregion_fallback(me, lock);
		lock->vrl_lock._vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)0;
	}
	return ok;
}

PRIVATE WUNUSED ATTR_INOUT(1) NONNULL((2)) int FCC
lockable_wlockregion(struct video_buffer *__restrict self,
                     struct video_regionlock *__restrict lock) {
	int ok;
	struct lockable_buffer *me = (struct lockable_buffer *)self;
	video_regionlock_assert(me, lock);
	ok = (me->lb_base->vb_ops->vi_wlockregion)(me->lb_base, lock);
	if (ok != 0 && errno != ENOMEM) {
		ok = lockable_lockregion_fallback(me, lock);
		lock->vrl_lock._vl_driver[LOCKABLE_BUFFER_VLOCK_ISWRITE] = (void *)1;
	}
	return ok;
}

PRIVATE ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC lockable_unlockregion)(struct video_buffer *__restrict self,
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


PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
lockable_initgfx(struct video_gfx *__restrict self) {
	struct lockable_buffer *me = (struct lockable_buffer *)self->vx_buffer;
	struct video_buffer *base = me->lb_base;
	self->vx_buffer = base; /* This is allowed! */
	return (*base->vb_ops->vi_initgfx)(self);
}

PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
lockable_updategfx(struct video_gfx *__restrict self, unsigned int what) {
	struct lockable_buffer *me = (struct lockable_buffer *)self->vx_buffer;
	struct video_buffer *base = me->lb_base;
	self->vx_buffer = base; /* This is allowed! */
	return (*base->vb_ops->vi_updategfx)(self, what);
}


#undef lockable_ops
PRIVATE struct video_buffer_ops lockable_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _lockable_ops(void) {
	if unlikely(!lockable_ops.vi_destroy) {
		lockable_ops.vi_rlock        = &lockable_rlock;
		lockable_ops.vi_wlock        = &lockable_wlock;
		lockable_ops.vi_unlock       = &lockable_unlock;
		lockable_ops.vi_rlockregion  = &lockable_rlockregion;
		lockable_ops.vi_wlockregion  = &lockable_wlockregion;
		lockable_ops.vi_unlockregion = &lockable_unlockregion;
		lockable_ops.vi_initgfx      = &lockable_initgfx;
		lockable_ops.vi_updategfx    = &lockable_updategfx;
		COMPILER_WRITE_BARRIER();
		lockable_ops.vi_destroy = &lockable_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &lockable_ops;
}


PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) bool CC
video_buffer_islockable(struct video_buffer const *__restrict self) {
	if (self->vb_ops == &lockable_ops)
		goto yes;
	if (self->vb_ops == &old_rambuffer_ops)
		goto yes;
	if (self->vb_ops == &old_rambuffer_ops__for_codec)
		goto yes;
	if (self->vb_ops == &old_membuffer_ops)
		goto yes;
	if (self->vb_ops == &old_membuffer_ops__for_codec)
		goto yes;
	if (self->vb_ops == &old_subregion_buffer_ops_norem) {
		/* Subregion buffers are locked iff the underlying buffer is */
		struct old_subregion_buffer const *me;
		me = (struct old_subregion_buffer const *)self;
		return video_buffer_islockable(me->srb_base);
	}
	return false;
yes:
	return true;
}


/* Check if `buffer' is lockable. If so re-return "buffer" and
 * initialize `self' such that `libvideo_buffer_lockable_fini'
 * does nothing. Else, wrap it using `buffer' and return  *it*
 * instead. */
INTERN WUNUSED ATTR_OUT(1) NONNULL((2)) struct video_buffer *CC
libvideo_buffer_lockable_init(struct lockable_buffer *self,
                              struct video_buffer *__restrict buffer) {
	self->lb_data = NULL;
	if (video_buffer_islockable(buffer))
		return buffer;
	self->vb_ops    = _lockable_ops();
	self->vb_format = buffer->vb_format;
	self->vb_xdim   = buffer->vb_xdim;
	self->vb_ydim   = buffer->vb_ydim;
#ifndef NDEBUG
	self->vb_refcnt = 0;
#endif /* !NDEBUG */
	self->lb_base = buffer;
	self->lb_data = NULL;
	DBG_memset(&self->lb_stride, 0xcc, sizeof(self->lb_stride));
	return self;
}

INTERN NONNULL((1)) void
NOTHROW(CC libvideo_buffer_lockable_fini)(struct lockable_buffer *__restrict self) {
	free(self->lb_data);
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
	result->vb_ops    = _lockable_ops();
	result->vb_format = self->vb_format;
	result->vb_xdim   = self->vb_xdim;
	result->vb_ydim   = self->vb_ydim;
	result->vb_domain = video_buffer_domain_for_wrapper(self);
	result->vb_refcnt = 1;
	video_buffer_incref(self);
	result->lb_base = self;
	result->lb_data = NULL;
#ifdef LOCKABLE_BUFFER_PALREF
	if (result->vb_format.vf_pal)
		video_palette_incref(result->vb_format.vf_pal);
#endif /* LOCKABLE_BUFFER_PALREF */
	DBG_memset(&result->lb_stride, 0xcc, sizeof(result->lb_stride));
	return result;
err:
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_LOCKABLE_C */
