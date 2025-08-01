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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_CUSTOM_C
#define GUARD_LIBVIDEO_GFX_BUFFER_CUSTOM_C 1
#define __VIDEO_BUFFER_const /* nothing */
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sequence/list.h>

#include <kos/anno.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <malloc.h>
#include <sched.h>
#include <stddef.h>

#include <libvideo/color.h>
#include <libvideo/crect.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/surface-defs.h>
#include <libvideo/gfx/surface.h>
#include <libvideo/types.h>

#include "../buffer.h"
#include "../gfx.h"
#include "../ramdomain.h"
#include "../swgfx.h"
#include "custom.h"

DECL_BEGIN

/* Custom buffer operator types */
DEFINE_VIDEO_BUFFER_TYPE(custom_buffer_ops,
                         custom_buffer__destroy, custom_buffer__initgfx, libvideo_buffer_swgfx_updategfx,
                         custom_buffer__rlock, custom_buffer__wlock, custom_buffer__unlock,
                         custom_buffer__rlockregion, custom_buffer__wlockregion, custom_buffer__unlockregion,
                         custom_buffer__revoke, custom_buffer__subregion);
DEFINE_VIDEO_BUFFER_TYPE(custom_buffer_subregion_ops,
                         custom_buffer_subregion__destroy, custom_buffer_subregion__initgfx, libvideo_buffer_swgfx_updategfx,
                         libvideo_buffer_notsup__rlock, libvideo_buffer_notsup__wlock, libvideo_buffer_noop__unlock,
                         custom_buffer_subregion__rlockregion, custom_buffer_subregion__wlockregion, custom_buffer_subregion__unlockregion,
                         custom_buffer_subregion__revoke, custom_buffer_subregion__subregion);
DEFINE_VIDEO_BUFFER_TYPE(custom_buffer_subregion_norem_ops,
                         custom_buffer_subregion__destroy, custom_buffer_subregion__initgfx, libvideo_buffer_swgfx_updategfx,
                         custom_buffer_subregion__rlock, custom_buffer_subregion__wlock, custom_buffer_subregion__unlock,
                         custom_buffer_subregion__rlockregion, custom_buffer_subregion__wlockregion, custom_buffer_subregion__unlockregion,
                         custom_buffer_subregion__revoke, custom_buffer_subregion__subregion);
DEFINE_VIDEO_BUFFER_TYPE(custom_buffer_subregion_nooff_ops,
                         custom_buffer_subregion__destroy, custom_buffer__initgfx, libvideo_buffer_swgfx_updategfx,
                         custom_buffer__rlock, custom_buffer__wlock, custom_buffer__unlock,
                         custom_buffer__rlockregion, custom_buffer__wlockregion, custom_buffer__unlockregion,
                         custom_buffer_subregion__revoke, custom_buffer_subregion__subregion);


/* Operators for custom buffers, as seen above */

/* DESTROY */
INTERN NONNULL((1)) void FCC
custom_buffer__destroy(struct video_buffer *__restrict self) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	assert(me->cbc_inuse == 0);
	if (me->cb_destroy)
		(*me->cb_destroy)(me->cbc_cookie);
	__video_buffer_fini_common(me);
	free(self);
}

INTERN NONNULL((1)) void FCC
custom_buffer_subregion__destroy(struct video_buffer *__restrict self) {
	struct custom_buffer_subregion *me = (struct custom_buffer_subregion *)self;
	REF struct custom_buffer_common *parent = me->cbsr_parent;
	if (parent) {
		atomic_lock_acquire(&parent->cbc_subregion_lock);
		if (LIST_ISBOUND(me, cbsr_link))
			LIST_UNBIND(me, cbsr_link);
		atomic_lock_release(&parent->cbc_subregion_lock);
		video_buffer_decref(parent);
	}
	__video_buffer_fini_common(me);
	free(me);
}

/* Dummy operators (for use after the buffer was revoked) */
PRIVATE ATTR_PURE WUNUSED video_pixel_t CC
dummy_custom_getpixel(void *UNUSED(cookie),
                      video_coord_t UNUSED(x),
                      video_coord_t UNUSED(y)) {
	COMPILER_IMPURE();
	return 0;
}

PRIVATE void CC
dummy_custom_setpixel(void *UNUSED(cookie),
                      video_coord_t UNUSED(x),
                      video_coord_t UNUSED(y),
                      video_pixel_t UNUSED(pixel)) {
	COMPILER_IMPURE();
}

/* REVOKE+SUBREGION */
PRIVATE ATTR_INOUT(1) void
NOTHROW(FCC custom_buffer__revoke_common)(struct custom_buffer_common *__restrict me) {
	/* Revoke sub-regions */
	atomic_lock_acquire(&me->cbc_subregion_lock);
	while (!LIST_EMPTY(&me->cbc_subregion_list)) {
		REF struct custom_buffer_subregion *sr = LIST_FIRST(&me->cbc_subregion_list);
		if (!tryincref(sr)) {
			LIST_UNBIND(sr, cbsr_link);
		} else {
			atomic_lock_release(&me->cbc_subregion_lock);
			sr = (struct custom_buffer_subregion *)video_buffer_revoke(sr);
			video_buffer_decref(sr);
			atomic_lock_acquire(&me->cbc_subregion_lock);
		}
	}
	atomic_lock_release(&me->cbc_subregion_lock);

	/* Revoke user-defined operator callbacks.
	 * Order of these writes doesn't matter, but writes need to be atomic */
	COMPILER_WRITE_BARRIER();
	atomic_store_explicit(&me->cbc_getpixel, &dummy_custom_getpixel, memory_order_relaxed);
	atomic_store_explicit(&me->cbc_setpixel, &dummy_custom_setpixel, memory_order_relaxed);
	atomic_store_explicit(&me->cbc_rlock, NULL, memory_order_relaxed);
	atomic_store_explicit(&me->cbc_wlock, NULL, memory_order_relaxed);
	atomic_store_explicit(&me->cbc_rlockregion, NULL, memory_order_relaxed);
	atomic_store_explicit(&me->cbc_wlockregion, NULL, memory_order_relaxed);
	COMPILER_WRITE_BARRIER();
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC custom_buffer__revoke)(struct video_buffer *__restrict self) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	video_buffer_custom_revoke_t revoke;
	custom_buffer__revoke_common(me);
	revoke = atomic_xch(&me->cb_revoke, NULL);
	if (revoke)
		(*revoke)(me->cbc_cookie);
	while (atomic_read(&me->cbc_inuse))
		sched_yield();
	return me;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC custom_buffer_subregion__revoke)(struct video_buffer *__restrict self) {
	struct custom_buffer_subregion *me = (struct custom_buffer_subregion *)self;
	REF struct custom_buffer_common *parent = atomic_xch(&me->cbsr_parent, NULL);
	if (parent) {
		atomic_lock_acquire(&parent->cbc_subregion_lock);
		if (LIST_ISBOUND(me, cbsr_link))
			LIST_UNBIND(me, cbsr_link);
		atomic_lock_release(&parent->cbc_subregion_lock);
		video_buffer_decref(parent);
	}
	custom_buffer__revoke_common(me);
	return me;
}

PRIVATE WUNUSED ATTR_IN(1) ATTR_INOUT(2) ATTR_IN(3) REF struct video_buffer *FCC
custom_buffer__subregion_impl(struct video_surface const *__restrict surface,
                              struct custom_buffer_common *__restrict parent,
                              struct video_crect const *__restrict rect,
                              video_coord_t parent_xoff,
                              video_coord_t parent_yoff) {
	REF struct custom_buffer_subregion *result;
	result = (REF struct custom_buffer_subregion *)malloc(sizeof(struct custom_buffer_subregion));
	if unlikely(!result)
		goto err;
	__video_buffer_init_subregion(result, surface, parent, rect);
	result->cbsr_xoff  = parent_xoff + rect->vcr_xmin;
	result->cbsr_yoff  = parent_yoff + rect->vcr_ymin;
	result->cbsr_bxrem = result->cbsr_xoff;
	result->cbsr_bxoff = (*video_buffer_getcodec(result)->vc_coord2bytes)(&result->cbsr_bxrem);
	result->vb_ops = !result->cbsr_xoff && !result->cbsr_yoff
	                 ? _custom_buffer_subregion_nooff_ops()
	                 : result->cbsr_bxrem == 0
	                   ? _custom_buffer_subregion_norem_ops()
	                   : _custom_buffer_subregion_ops();
	result->cbc_inuse        = 0;
	result->cbc_unlock       = parent->cbc_unlock;
	result->cbc_unlockregion = parent->cbc_unlockregion;
	result->cbc_cookie       = parent->cbc_cookie;
	LIST_INIT(&result->cbc_subregion_list);
	atomic_lock_init(&result->cbc_subregion_lock);
	__video_buffer_init_common(result);
	atomic_lock_acquire(&parent->cbc_subregion_lock);
	COMPILER_WRITE_BARRIER();
	result->cbc_getpixel     = atomic_read(&parent->cbc_getpixel);
	result->cbc_setpixel     = atomic_read(&parent->cbc_setpixel);
	result->cbc_rlock        = atomic_read(&parent->cbc_rlock);
	result->cbc_wlock        = atomic_read(&parent->cbc_wlock);
	result->cbc_rlockregion  = atomic_read(&parent->cbc_rlockregion);
	result->cbc_wlockregion  = atomic_read(&parent->cbc_wlockregion);
	COMPILER_WRITE_BARRIER();
	LIST_INSERT_HEAD(&parent->cbc_subregion_list, result, cbsr_link);
	atomic_lock_release(&parent->cbc_subregion_lock);
	return result;
err:
	return NULL;
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
custom_buffer__subregion(struct video_surface const *__restrict self,
                         struct video_crect const *__restrict rect) {
	struct custom_buffer *me = (struct custom_buffer *)video_surface_getbuffer(self);
	return custom_buffer__subregion_impl(self, me, rect, 0, 0);
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
custom_buffer_subregion__subregion(struct video_surface const *__restrict self,
                                   struct video_crect const *__restrict rect) {
	struct custom_buffer_subregion *me = (struct custom_buffer_subregion *)video_surface_getbuffer(self);
	return custom_buffer__subregion_impl(self, me, rect, me->cbsr_xoff, me->cbsr_yoff);
}

/* LOCK */
INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
custom_buffer__rlock(struct video_buffer *__restrict self,
                     struct video_lock *__restrict lock) {
	struct custom_buffer_common *me = (struct custom_buffer_common *)self;
	video_buffer_custom_lock_t rlock;
	atomic_inc(&me->cbc_inuse);
	rlock = atomic_read(&me->cbc_rlock);
	if (rlock) {
		int result = (*rlock)(me->cbc_cookie, lock);
		if unlikely(result)
			atomic_dec(&me->cbc_inuse);
		return result;
	}
	atomic_dec(&me->cbc_inuse);
	errno = ENOTSUP;
	return -1;
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
custom_buffer__wlock(struct video_buffer *__restrict self,
                     struct video_lock *__restrict lock) {
	struct custom_buffer_common *me = (struct custom_buffer_common *)self;
	video_buffer_custom_lock_t wlock;
	atomic_inc(&me->cbc_inuse);
	wlock = atomic_read(&me->cbc_wlock);
	if (wlock) {
		int result = (*wlock)(me->cbc_cookie, lock);
		if unlikely(result)
			atomic_dec(&me->cbc_inuse);
		return result;
	}
	atomic_dec(&me->cbc_inuse);
	errno = ENOTSUP;
	return -1;
}

INTERN ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC custom_buffer__unlock)(struct video_buffer *__restrict self,
                                   struct video_lock *__restrict lock) {
	struct custom_buffer_common *me = (struct custom_buffer_common *)self;
	if (me->cbc_unlock)
		(*me->cbc_unlock)(me->cbc_cookie, lock);
	atomic_dec(&me->cbc_inuse);
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
custom_buffer_subregion__rlock(struct video_buffer *__restrict self,
                               struct video_lock *__restrict lock) {
	struct custom_buffer_subregion *me = (struct custom_buffer_subregion *)self;
	video_buffer_custom_lock_t rlock;
	assert(me->cbsr_bxrem == 0);
	atomic_inc(&me->cbc_inuse);
	rlock = atomic_read(&me->cbc_rlock);
	if (rlock) {
		int result;
		result = (*me->cbc_rlock)(me->cbc_cookie, lock);
		if unlikely(result)
			atomic_dec(&me->cbc_inuse);
		lock->vl_data += me->cbsr_yoff * lock->vl_stride;
		lock->vl_data += me->cbsr_bxoff;
		return result;
	}
	atomic_dec(&me->cbc_inuse);
	errno = ENOTSUP;
	return -1;
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
custom_buffer_subregion__wlock(struct video_buffer *__restrict self,
                               struct video_lock *__restrict lock) {
	struct custom_buffer_subregion *me = (struct custom_buffer_subregion *)self;
	video_buffer_custom_lock_t wlock;
	assert(me->cbsr_bxrem == 0);
	atomic_inc(&me->cbc_inuse);
	wlock = atomic_read(&me->cbc_wlock);
	if (wlock) {
		int result;
		result = (*me->cbc_wlock)(me->cbc_cookie, lock);
		if unlikely(result)
			atomic_dec(&me->cbc_inuse);
		lock->vl_data += me->cbsr_yoff * lock->vl_stride;
		lock->vl_data += me->cbsr_bxoff;
		return result;
	}
	atomic_dec(&me->cbc_inuse);
	errno = ENOTSUP;
	return -1;
}

INTERN ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC custom_buffer_subregion__unlock)(struct video_buffer *__restrict self,
                                             struct video_lock *__restrict lock) {
	struct custom_buffer_subregion *me = (struct custom_buffer_subregion *)self;
	if (me->cbc_unlock) {
		lock->vl_data -= me->cbsr_bxoff;
		lock->vl_data -= me->cbsr_yoff * lock->vl_stride;
		(*me->cbc_unlock)(me->cbc_cookie, lock);
	}
	atomic_dec(&me->cbc_inuse);
}


INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
custom_buffer__rlockregion(struct video_buffer *__restrict self,
                           struct video_regionlock *__restrict lock) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	video_buffer_custom_lockregion_t rlockregion;
	video_buffer_custom_lock_t rlock;
	video_regionlock_assert(me, lock);
	atomic_inc(&me->cbc_inuse);
	rlockregion = atomic_read(&me->cbc_rlockregion);
	if (rlockregion) {
		int result = (*rlockregion)(me->cbc_cookie, lock);
		if unlikely(result)
			atomic_dec(&me->cbc_inuse);
		return result;
	}

	rlock = atomic_read(&me->cbc_rlock);
	if (rlock) {
		int result;
		size_t xoff;
		lock->vrl_xbas = lock->_vrl_rect.vcr_xmin;
		xoff   = (*video_buffer_getcodec(me)->vc_coord2bytes)(&lock->vrl_xbas);
		result = (*rlock)(me->cbc_cookie, &lock->vrl_lock);
		if unlikely(result)
			atomic_dec(&me->cbc_inuse);
		lock->vrl_lock.vl_data += lock->_vrl_rect.vcr_ymin * lock->vrl_lock.vl_stride;
		lock->vrl_lock.vl_data += xoff;
		return result;
	}

	atomic_dec(&me->cbc_inuse);
	errno = ENOTSUP;
	return -1;
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
custom_buffer__wlockregion(struct video_buffer *__restrict self,
                           struct video_regionlock *__restrict lock) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	video_buffer_custom_lockregion_t wlockregion;
	video_buffer_custom_lock_t wlock;
	video_regionlock_assert(me, lock);
	atomic_inc(&me->cbc_inuse);
	wlockregion = atomic_read(&me->cbc_wlockregion);
	if (wlockregion) {
		int result = (*wlockregion)(me->cbc_cookie, lock);
		if unlikely(result)
			atomic_dec(&me->cbc_inuse);
		return result;
	}

	wlock = atomic_read(&me->cbc_wlock);
	if (wlock) {
		int result;
		size_t xoff;
		lock->vrl_xbas = lock->_vrl_rect.vcr_xmin;
		xoff   = (*video_buffer_getcodec(me)->vc_coord2bytes)(&lock->vrl_xbas);
		result = (*wlock)(me->cbc_cookie, &lock->vrl_lock);
		if unlikely(result)
			atomic_dec(&me->cbc_inuse);
		lock->vrl_lock.vl_data += lock->_vrl_rect.vcr_ymin * lock->vrl_lock.vl_stride;
		lock->vrl_lock.vl_data += xoff;
		return result;
	}

	atomic_dec(&me->cbc_inuse);
	errno = ENOTSUP;
	return -1;
}

INTERN ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC custom_buffer__unlockregion)(struct video_buffer *__restrict self,
                                         struct video_regionlock *__restrict lock) {
	struct custom_buffer *me = (struct custom_buffer *)self;
	video_regionlock_assert(me, lock);
	if (me->cbc_unlockregion) {
		(*me->cbc_unlockregion)(me->cbc_cookie, lock);
	} else if (me->cbc_unlock) {
		video_coord_t xrem = lock->_vrl_rect.vcr_xmin;
		size_t xoff = (*video_buffer_getcodec(self)->vc_coord2bytes)(&xrem);
		assert(xrem == video_regionlock_getxbase(lock));
		lock->vrl_lock.vl_data -= lock->_vrl_rect.vcr_ymin * lock->vrl_lock.vl_stride;
		lock->vrl_lock.vl_data -= xoff;
		(*me->cbc_unlock)(me->cbc_cookie, &lock->vrl_lock);
	}
}


INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
custom_buffer_subregion__rlockregion(struct video_buffer *__restrict self,
                                     struct video_regionlock *__restrict lock) {
	struct custom_buffer_subregion *me = (struct custom_buffer_subregion *)self;
	video_buffer_custom_lockregion_t rlockregion;
	video_regionlock_assert(me, lock);
	lock->_vrl_rect.vcr_xmin += me->cbsr_xoff;
	lock->_vrl_rect.vcr_ymin += me->cbsr_yoff;
	atomic_inc(&me->cbc_inuse);
	rlockregion = atomic_read(&me->cbc_rlockregion);
	if (rlockregion) {
		int result = (*rlockregion)(me->cbc_cookie, lock);
		if unlikely(result)
			atomic_dec(&me->cbc_inuse);
		return result;
	}
	atomic_dec(&me->cbc_inuse);
	errno = ENOTSUP;
	return -1;
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
custom_buffer_subregion__wlockregion(struct video_buffer *__restrict self,
                                     struct video_regionlock *__restrict lock) {
	struct custom_buffer_subregion *me = (struct custom_buffer_subregion *)self;
	video_buffer_custom_lockregion_t wlockregion;
	video_regionlock_assert(me, lock);
	lock->_vrl_rect.vcr_xmin += me->cbsr_xoff;
	lock->_vrl_rect.vcr_ymin += me->cbsr_yoff;
	atomic_inc(&me->cbc_inuse);
	wlockregion = atomic_read(&me->cbc_wlockregion);
	if (wlockregion) {
		int result = (*wlockregion)(me->cbc_cookie, lock);
		if unlikely(result)
			atomic_dec(&me->cbc_inuse);
		return result;
	}
	atomic_dec(&me->cbc_inuse);
	errno = ENOTSUP;
	return -1;
}

INTERN ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC custom_buffer_subregion__unlockregion)(struct video_buffer *__restrict self,
                                                   struct video_regionlock *__restrict lock) {
	struct custom_buffer_subregion *me = (struct custom_buffer_subregion *)self;
	if (me->cbc_unlockregion)
		(*me->cbc_unlockregion)(me->cbc_cookie, lock);
	atomic_dec(&me->cbc_inuse);
	lock->_vrl_rect.vcr_ymin -= me->cbsr_yoff;
	lock->_vrl_rect.vcr_xmin -= me->cbsr_xoff;
	video_regionlock_assert(me, lock);
}

/* GFX */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
custom_buffer__initgfx(struct video_gfx *__restrict self) {
	struct gfx_swdrv *drv = video_swgfx_getdrv(self);
	libvideo_gfx_init_fullclip(self);

	/* Default pixel accessors */
	drv->xsw_getpixel = &custom_gfx__getpixel;
	drv->xsw_setpixel = &custom_gfx__setpixel;

	/* Load generic operator defaults */
	libvideo_swgfx_populate(self);
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
custom_buffer_subregion__initgfx(struct video_gfx *__restrict self) {
	struct gfx_swdrv *drv = video_swgfx_getdrv(self);
	libvideo_gfx_init_fullclip(self);

	/* Default pixel accessors */
	drv->xsw_getpixel = &custom_gfx_subregion__getpixel;
	drv->xsw_setpixel = &custom_gfx_subregion__setpixel;

	/* Load generic operator defaults */
	libvideo_swgfx_populate(self);
	return self;
}


INTERN ATTR_IN(1) video_pixel_t CC
custom_gfx__getpixel(struct video_gfx const *__restrict self,
                     video_coord_t abs_x, video_coord_t abs_y) {
	video_pixel_t result;
	struct custom_buffer_common *me = (struct custom_buffer_common *)video_gfx_getbuffer(self);
	video_buffer_custom_getpixel_t getpixel;
	atomic_inc(&me->cbc_inuse);
	getpixel = atomic_read(&me->cbc_getpixel);
	result = (*getpixel)(me->cbc_cookie, abs_x, abs_y);
	atomic_dec(&me->cbc_inuse);
	return result;
}

INTERN ATTR_IN(1) void CC
custom_gfx__setpixel(struct video_gfx const *__restrict self,
                     video_coord_t abs_x, video_coord_t abs_y,
                     video_pixel_t pixel) {
	struct custom_buffer_common *me = (struct custom_buffer_common *)video_gfx_getbuffer(self);
	video_buffer_custom_setpixel_t setpixel;
	atomic_inc(&me->cbc_inuse);
	setpixel = atomic_read(&me->cbc_setpixel);
	(*setpixel)(me->cbc_cookie, abs_x, abs_y, pixel);
	atomic_dec(&me->cbc_inuse);
}

INTERN ATTR_IN(1) video_pixel_t CC
custom_gfx_subregion__getpixel(struct video_gfx const *__restrict self,
                               video_coord_t abs_x, video_coord_t abs_y) {
	video_pixel_t result;
	struct custom_buffer_subregion *me = (struct custom_buffer_subregion *)video_gfx_getbuffer(self);
	video_buffer_custom_getpixel_t getpixel;
	abs_x += me->cbsr_xoff;
	abs_y += me->cbsr_yoff;
	atomic_inc(&me->cbc_inuse);
	getpixel = atomic_read(&me->cbc_getpixel);
	result = (*getpixel)(me->cbc_cookie, abs_x, abs_y);
	atomic_dec(&me->cbc_inuse);
	return result;
}

INTERN ATTR_IN(1) void CC
custom_gfx_subregion__setpixel(struct video_gfx const *__restrict self,
                               video_coord_t abs_x, video_coord_t abs_y,
                               video_pixel_t pixel) {
	struct custom_buffer_subregion *me = (struct custom_buffer_subregion *)video_gfx_getbuffer(self);
	video_buffer_custom_setpixel_t setpixel;
	abs_x += me->cbsr_xoff;
	abs_y += me->cbsr_yoff;
	atomic_inc(&me->cbc_inuse);
	setpixel = atomic_read(&me->cbc_setpixel);
	(*setpixel)(me->cbc_cookie, abs_x, abs_y, pixel);
	atomic_dec(&me->cbc_inuse);
}



/* Construct a special video buffer which, rather than being backed by memory
 * or implemented using hardware acceleration,  does all its pixel I/O  using
 * the provided function pointers.
 *
 * WARNING: The  given  `getpixel'  / `setpixel'  callbacks  better be
 *          fast, or any GFX on the returned buffer will take forever!
 *
 * @param: size_x:       X dimension of the returned video buffer
 * @param: size_y:       Y dimension of the returned video buffer
 * @param: format:       [1..1] Video format used for color<=>pixel conversion,
 *                              as well as pixel I/O (when rlock/wlock is given
 *                              and returns `0')
 * @param: palette:      [0..1] Palette to-be used with `codec' (if needed)
 * @param: getpixel:     [1..1] Mandatory pixel read operator (passed coords are absolute and guarantied in-bounds)
 * @param: setpixel:     [1..1] Mandatory pixel write operator (passed coords are absolute and guarantied in-bounds)
 * @param: destroy:      [0..1] Optional callback invoked when the returned buffer is destroyed
 * @param: rlock:        [0..1] Optional callback to lock video memory for reading (when missing, or doesn't return `0', `getpixel' is always used)
 * @param: wlock:        [0..1] Optional callback to lock video memory for writing (when missing, or doesn't return `0', `setpixel' is always used)
 * @param: unlock:       [0..1] Optional callback invoked to release video locks previously acquired by `rlock' or `wlock'
 * @param: rlockregion:  [0..1] Optional extension to `rlock' (when not supplied, implemented in terms of `rlock')
 * @param: wlockregion:  [0..1] Optional extension to `wlock' (when not supplied, implemented in terms of `wlock')
 * @param: unlockregion: [0..1] Optional extension to `unlock' (when not supplied, implemented in terms of `unlock')
 * @param: revoke:       [0..1] Optional callback invoked when the returned buffer is revoked.
 * @param: cookie:       [?..?] Cookie argument passed to all user-supplied operators */
DEFINE_PUBLIC_ALIAS(video_buffer_forcustom, libvideo_buffer_forcustom);
INTERN WUNUSED NONNULL((3, 4, 5)) REF struct video_buffer *CC
libvideo_buffer_forcustom(video_dim_t size_x, video_dim_t size_y,
                          struct video_buffer_format const *__restrict format,
                          video_buffer_custom_getpixel_t getpixel,
                          video_buffer_custom_setpixel_t setpixel,
                          video_buffer_custom_destroy_t destroy,
                          video_buffer_custom_lock_t rlock,
                          video_buffer_custom_lock_t wlock,
                          video_buffer_custom_unlock_t unlock,
                          video_buffer_custom_lockregion_t rlockregion,
                          video_buffer_custom_lockregion_t wlockregion,
                          video_buffer_custom_unlockregion_t unlockregion,
                          video_buffer_custom_revoke_t revoke,
                          void *cookie) {
	REF struct custom_buffer *result;
	result = (REF struct custom_buffer *)malloc(sizeof(struct custom_buffer));
	if unlikely(!result)
		goto err;
	if unlikely(!__video_buffer_init_format(result, format)) {
		errno = EINVAL;
		goto err_r;
	}
	__video_buffer_init_domain(result, _libvideo_ramdomain());
	__video_buffer_init_ops(result, _custom_buffer_ops());
	__video_buffer_init_dim(result, size_x, size_y);
	result->cbc_getpixel     = getpixel;
	result->cbc_setpixel     = setpixel;
	result->cbc_rlock        = rlock ? rlock : wlock;
	result->cbc_wlock        = wlock;
	result->cbc_unlock       = unlock;
	result->cbc_rlockregion  = rlockregion ? rlockregion : wlockregion;
	result->cbc_wlockregion  = wlockregion;
	result->cbc_unlockregion = unlockregion;
	result->cbc_cookie       = cookie;
	result->cbc_inuse        = 0;
	LIST_INIT(&result->cbc_subregion_list);
	atomic_lock_init(&result->cbc_subregion_lock);
	result->cb_destroy = destroy;
	result->cb_revoke  = revoke;
	__video_buffer_init_common(result);
	return result;
err_r:
	free(result);
err:
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_CUSTOM_C */
