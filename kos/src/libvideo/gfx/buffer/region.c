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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_REGION_C
#define GUARD_LIBVIDEO_GFX_BUFFER_REGION_C 1
#define __VIDEO_BUFFER_const /* nothing */
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>
#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sequence/list.h>

#include <kos/anno.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <malloc.h>
#include <sched.h>
#include <stdbool.h>
#include <stddef.h>

#include <libvideo/color.h>
#include <libvideo/crect.h>
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
#include "region.h"

DECL_BEGIN

#define return_empty_buffer                                      \
	do {                                                         \
		struct video_buffer *_empty_res = &libvideo_emptybuffer; \
		video_buffer_incref(_empty_res);                         \
		return _empty_res;                                       \
	}	__WHILE0



DEFINE_VIDEO_BUFFER_TYPE(region_buffer_ops,
                         region_buffer__destroy, region_buffer__initgfx, region_buffer__updategfx,
                         libvideo_buffer_notsup_rlock, libvideo_buffer_notsup_wlock, libvideo_buffer_noop_unlock,
                         region_buffer__rlockregion, region_buffer__wlockregion, region_buffer__unlockregion,
                         region_buffer__revoke, region_buffer__subregion);
DEFINE_VIDEO_BUFFER_TYPE(region_buffer_subregion_ops,
                         region_buffer_subregion__destroy, region_buffer__initgfx, region_buffer__updategfx,
                         libvideo_buffer_notsup_rlock, libvideo_buffer_notsup_wlock, libvideo_buffer_noop_unlock,
                         region_buffer__rlockregion, region_buffer__wlockregion, region_buffer__unlockregion,
                         region_buffer_subregion__revoke, region_buffer_subregion__subregion);
DEFINE_VIDEO_BUFFER_TYPE(region_buffer_subregion_alias_ops,
                         region_buffer_subregion_alias__destroy, region_buffer_subregion_alias__initgfx, region_buffer_subregion_alias__updategfx,
                         region_buffer_subregion_alias__rlock, region_buffer_subregion_alias__wlock, region_buffer_subregion_alias__unlock,
                         region_buffer_subregion_alias__rlockregion, region_buffer_subregion_alias__wlockregion, region_buffer_subregion_alias__unlockregion,
                         region_buffer_subregion_alias__revoke, region_buffer_subregion_alias__subregion);

#define REGION_GFX_SUBOPS      (_VIDEO_GFX_N_DRIVER - 1)
#define REGION_BLITTER_SUBOPS  (_VIDEO_BLITTER_N_DRIVER - 1)
#define REGION_BLITTER3_SUBOPS (_VIDEO_BLITTER3_N_DRIVER - 1)

/* Operators for region buffers, as seen above */

/* DESTROY */
INTERN NONNULL((1)) void FCC
region_buffer__destroy(struct video_buffer *__restrict self) {
	struct region_buffer *me = (struct region_buffer *)self;
	assert(LIST_EMPTY(&me->rbf_child_list));
	assert(me->rbf_inuse == 0);
	video_buffer_decref(me->rbf_base);
	__video_buffer_fini_common(me);
	free(me);
}

INTERN NONNULL((1)) void FCC
region_buffer_subregion__destroy(struct video_buffer *__restrict self) {
	struct region_buffer_subregion *me = (struct region_buffer_subregion *)self;
	REF struct region_buffer *parent = atomic_read(&me->brbsr_parent);
	if (parent) {
		atomic_lock_acquire(&parent->rbf_child_lock);
		if (LIST_ISBOUND(me, brbsr_chain))
			LIST_REMOVE(me, brbsr_chain);
		atomic_lock_release(&parent->rbf_child_lock);
		video_buffer_decref(parent);
	}
	region_buffer__destroy(me);
}

/* REVOKE+SUBREGION */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC region_buffer__revoke)(struct video_buffer *__restrict self) {
	struct region_buffer *me = (struct region_buffer *)self;
	REF struct video_buffer *new_base, *old_base;
	new_base = &libvideo_emptybuffer;
	video_buffer_incref(new_base);
	old_base = atomic_xch(&me->rbf_base, new_base);
	while (atomic_read(&me->rbf_inuse))
		sched_yield();
	video_buffer_decref(old_base);
	atomic_lock_acquire(&me->rbf_child_lock);
	while (!LIST_EMPTY(&me->rbf_child_list)) {
		struct region_buffer_subregion *child;
		child = LIST_FIRST(&me->rbf_child_list);
		if (!tryincref(child)) {
			LIST_UNBIND(child, brbsr_chain);
		} else {
			atomic_lock_release(&me->rbf_child_lock);
			child = (struct region_buffer_subregion *)video_buffer_revoke(child);
			video_buffer_decref(child);
			atomic_lock_acquire(&me->rbf_child_lock);
		}
	}
	atomic_lock_release(&me->rbf_child_lock);
	return me;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC region_buffer_subregion__revoke)(struct video_buffer *__restrict self) {
	struct region_buffer_subregion *me = (struct region_buffer_subregion *)self;
	REF struct region_buffer *parent = atomic_xch(&me->brbsr_parent, NULL);
	if (parent) {
		atomic_lock_acquire(&parent->rbf_child_lock);
		if (LIST_ISBOUND(me, brbsr_chain))
			LIST_REMOVE(me, brbsr_chain);
		atomic_lock_release(&parent->rbf_child_lock);
		video_buffer_decref(parent);
	}
	return region_buffer__revoke(me);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC region_buffer_subregion_alias__revoke)(struct video_buffer *__restrict self) {
	struct region_buffer_subregion_alias *me = (struct region_buffer_subregion_alias *)self;
	REF struct region_buffer *parent = atomic_xch(&me->brbsr_parent, NULL);
	if (parent) {
		atomic_lock_acquire(&parent->rbf_child_lock);
		if (LIST_ISBOUND(me, brbsr_chain))
			LIST_REMOVE(me, brbsr_chain);
		atomic_lock_release(&parent->rbf_child_lock);
		video_buffer_decref(parent);
	}
	video_buffer_revoke(me->rbf_base);
	return me;
}

#define ASSERT_SUBREGION_RECT(self, rect)                                         \
	(assert(((rect)->vcr_xmin + (rect)->vcr_xdim) > (rect)->vcr_xmin),            \
	 assert(((rect)->vcr_ymin + (rect)->vcr_ydim) > (rect)->vcr_ymin),            \
	 assert(((rect)->vcr_xmin + (rect)->vcr_xdim) <= video_buffer_getxdim(self)), \
	 assert(((rect)->vcr_ymin + (rect)->vcr_ydim) <= video_buffer_getydim(self)))


INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
region_buffer__subregion(struct video_surface const *__restrict self,
                         struct video_crect const *__restrict rect) {
	struct video_rect old_rect, new_rect, result_rect, base_iorect;
	REF struct region_buffer_subregion *result;
	REF struct video_buffer *base;
	struct region_buffer *me = (struct region_buffer *)video_surface_getbuffer(self);
	ASSERT_SUBREGION_RECT(me, rect);
	old_rect.vr_xmin = me->rbf_cxoff;
	old_rect.vr_ymin = me->rbf_cyoff;
	old_rect.vr_xdim = me->vb_xdim;
	old_rect.vr_ydim = me->vb_ydim;
	if (OVERFLOW_SADD(me->rbf_cxoff, rect->vcr_xmin, &new_rect.vr_xmin))
		goto do_return_empty_buffer;
	if (OVERFLOW_SADD(me->rbf_cyoff, rect->vcr_ymin, &new_rect.vr_ymin))
		goto do_return_empty_buffer;
	new_rect.vr_xdim = rect->vcr_xdim;
	new_rect.vr_ydim = rect->vcr_ydim;
	if (!video_rect_intersect_overflow(&old_rect, &new_rect, &result_rect))
		goto do_return_empty_buffer;
	atomic_inc(&me->rbf_inuse);
	base = me->rbf_base;
	video_buffer_incref(base);
	atomic_dec(&me->rbf_inuse);
	assert(!video_rect_isempty(&result_rect));
	base_iorect.vr_xmin = 0;
	base_iorect.vr_ymin = 0;
	base_iorect.vr_xdim = base->vb_xdim;
	base_iorect.vr_ydim = base->vb_ydim;
	if (!video_rect_intersect_overflow(&base_iorect, &result_rect, &base_iorect))
		goto do_return_empty_buffer_base;

	/* Check if this whole thing has once again turned into a sub-region-only buffer.
	 * If it has, then we should create a `region_buffer_subregion_alias_ops' buffer. */
	if (result_rect.vr_xmin == base_iorect.vr_xmin &&
	    result_rect.vr_ymin == base_iorect.vr_ymin &&
	    result_rect.vr_xdim == base_iorect.vr_xdim &&
	    result_rect.vr_ydim == base_iorect.vr_ydim) {
		REF struct video_buffer *result_base;
		REF struct region_buffer_subregion_alias *alias_result;
		result_base = video_buffer_subregion(base, (struct video_crect const *)&base_iorect);
		if unlikely(!result_base)
			goto err_base;
		video_buffer_decref(base);
		base = result_base;
		alias_result = (REF struct region_buffer_subregion_alias *)malloc(sizeof(struct region_buffer_subregion_alias));
		if unlikely(!alias_result)
			goto err_base;
		video_surface_copyattrib(&alias_result->vb_surf, self);
		alias_result->vb_codec  = video_buffer_getcodec(base);
		alias_result->vb_ops    = _region_buffer_subregion_alias_ops();
		alias_result->vb_domain = me->vb_domain;
		alias_result->vb_xdim   = video_buffer_getxdim(base);
		alias_result->vb_ydim   = video_buffer_getydim(base);
		alias_result->vb_refcnt = 1;
		alias_result->rbf_cxoff = 0;
		alias_result->rbf_cyoff = 0;
		alias_result->rbf_base  = base; /* Inherit reference */
		alias_result->rbf_orig  = base;
		alias_result->rbf_inuse = 0;
		LIST_INIT(&alias_result->rbf_child_list);
		atomic_lock_init(&alias_result->rbf_child_lock);
		alias_result->brbsr_parent = me;
		video_buffer_incref(me);
		__video_buffer_init_common(alias_result);
		atomic_lock_acquire(&me->rbf_child_lock);
		LIST_INSERT_HEAD(&me->rbf_child_list, alias_result, brbsr_chain);
		atomic_lock_release(&me->rbf_child_lock);
		return alias_result;
	}

	/* Check if we need to use a sub-region of "base" for the  result
	 * This essentially clamps the buffer I/O Rect if it got smaller. */
	if (base_iorect.vr_xmin > 0 || base_iorect.vr_ymin > 0 ||
	    base_iorect.vr_xdim < base->vb_xdim ||
	    base_iorect.vr_ydim < base->vb_ydim) {
		REF struct video_buffer *result_base;
		result_base = video_buffer_subregion(base, (struct video_crect const *)&base_iorect);
		if unlikely(!result_base)
			goto err_base;
		video_buffer_decref(base);
		base = result_base;
		result_rect.vr_xmin -= base_iorect.vr_xmin;
		result_rect.vr_ymin -= base_iorect.vr_ymin;
	}

	/* Allocate the new sub-region */
	result = (REF struct region_buffer_subregion *)malloc(sizeof(struct region_buffer_subregion));
	if unlikely(!result)
		goto err_base;
	video_surface_copyattrib(&result->vb_surf, self);
	result->vb_codec  = video_buffer_getcodec(base);
	result->vb_ops    = _region_buffer_subregion_ops();
	result->vb_domain = me->vb_domain;
	result->vb_xdim   = result_rect.vr_xdim;
	result->vb_ydim   = result_rect.vr_ydim;
	result->vb_refcnt = 1;
	result->rbf_cxoff = result_rect.vr_xmin;
	result->rbf_cyoff = result_rect.vr_ymin;
	result->rbf_base  = base; /* Inherit reference */
	result->rbf_orig  = base;
	result->rbf_inuse = 0;
	LIST_INIT(&result->rbf_child_list);
	atomic_lock_init(&result->rbf_child_lock);
	result->brbsr_parent = me;
	video_buffer_incref(me);
	__video_buffer_init_common(result);
	atomic_lock_acquire(&me->rbf_child_lock);
	LIST_INSERT_HEAD(&me->rbf_child_list, result, brbsr_chain);
	atomic_lock_release(&me->rbf_child_lock);
	return result;
do_return_empty_buffer_base:
	video_buffer_decref(base);
do_return_empty_buffer:
	/* TODO: This always returns a 0x0 buffer, but we'd  need
	 *       to return one with a custom size given by `rect' */
	return_empty_buffer;
err_base:
	video_buffer_decref(base);
/*err:*/
	return NULL;
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
region_buffer_subregion_alias__subregion(struct video_surface const *__restrict self,
                                         struct video_crect const *__restrict rect) {
	REF struct video_buffer *result_base;
	REF struct region_buffer_subregion_alias *result;
	struct region_buffer_subregion_alias *me = (struct region_buffer_subregion_alias *)video_surface_getbuffer(self);
	result = (REF struct region_buffer_subregion_alias *)malloc(sizeof(struct region_buffer_subregion_alias));
	if unlikely(!result)
		goto err;
	result_base = video_buffer_subregion(me->rbf_base, rect);
	if unlikely(!result_base)
		goto err_r;
	video_surface_copyattrib(&result->vb_surf, self);
	result->vb_codec  = video_buffer_getcodec(result_base);
	result->vb_ops    = me->vb_ops;
	result->vb_domain = me->vb_domain;
	result->vb_xdim   = result_base->vb_xdim;
	result->vb_ydim   = result_base->vb_ydim;
	result->vb_refcnt = 1;
	result->rbf_cxoff = 0;
	result->rbf_cyoff = 0;
	result->rbf_base  = result_base; /* Inherit reference */
	result->rbf_orig  = result_base;
	result->rbf_inuse = 0;
	LIST_INIT(&result->rbf_child_list);
	atomic_lock_init(&result->rbf_child_lock);
	result->brbsr_parent = me;
	video_buffer_incref(me);
	__video_buffer_init_common(result);
	atomic_lock_acquire(&me->rbf_child_lock);
	LIST_INSERT_HEAD(&me->rbf_child_list, result, brbsr_chain);
	atomic_lock_release(&me->rbf_child_lock);
	return result;
err_r:
	free(result);
err:
	return NULL;
}

/* LOCK */
INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
region_buffer__rlockregion(struct video_buffer *__restrict self,
                           struct video_regionlock *__restrict lock) {
	struct region_buffer *me = (struct region_buffer *)self;
	struct video_buffer *base;
	video_coord_t xend, yend;
	assert((lock->_vrl_rect.vcr_xmin + lock->_vrl_rect.vcr_xdim) > lock->_vrl_rect.vcr_xmin);
	assert((lock->_vrl_rect.vcr_ymin + lock->_vrl_rect.vcr_ydim) > lock->_vrl_rect.vcr_ymin);
	assertf((lock->_vrl_rect.vcr_xmin + lock->_vrl_rect.vcr_xdim) <= me->vb_xdim,
	        "X[=%" PRIuCRD "]+SX[=%" PRIuDIM "][=%" PRIuCRD "] exceeds XDIM[=%" PRIuDIM "]",
	        lock->_vrl_rect.vcr_xmin, lock->_vrl_rect.vcr_xdim,
	        lock->_vrl_rect.vcr_xmin + lock->_vrl_rect.vcr_xdim, me->vb_xdim);
	assertf((lock->_vrl_rect.vcr_ymin + lock->_vrl_rect.vcr_ydim) <= me->vb_ydim,
	        "Y[=%" PRIuCRD "]+SY[=%" PRIuDIM "][=%" PRIuCRD "] eyceeds YDIM[=%" PRIuDIM "]",
	        lock->_vrl_rect.vcr_ymin, lock->_vrl_rect.vcr_ydim,
	        lock->_vrl_rect.vcr_ymin + lock->_vrl_rect.vcr_ydim, me->vb_ydim);

	/* Make the region-rect relative to the base buffer. */
	lock->_vrl_rect.vcr_xmin += me->rbf_cxoff;
	lock->_vrl_rect.vcr_ymin += me->rbf_cyoff;
	atomic_inc(&me->rbf_inuse);
	base = atomic_read(&me->rbf_base);
	if (!OVERFLOW_UADD(lock->_vrl_rect.vcr_xmin, lock->_vrl_rect.vcr_xdim, &xend) &&
	    !OVERFLOW_UADD(lock->_vrl_rect.vcr_ymin, lock->_vrl_rect.vcr_ydim, &yend) &&
	    xend <= base->vb_xdim && yend <= base->vb_ydim) {
		int result = (*base->vb_ops->vi_rlockregion)(base, lock);
		if unlikely(result)
			atomic_dec(&me->rbf_inuse);
		return result;
	}
	atomic_dec(&me->rbf_inuse);
	errno = ERANGE;
	return -1;
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
region_buffer__wlockregion(struct video_buffer *__restrict self,
                           struct video_regionlock *__restrict lock) {
	struct region_buffer *me = (struct region_buffer *)self;
	struct video_buffer *base;
	video_coord_t xend, yend;
	assert((lock->_vrl_rect.vcr_xmin + lock->_vrl_rect.vcr_xdim) > lock->_vrl_rect.vcr_xmin);
	assert((lock->_vrl_rect.vcr_ymin + lock->_vrl_rect.vcr_ydim) > lock->_vrl_rect.vcr_ymin);
	assertf((lock->_vrl_rect.vcr_xmin + lock->_vrl_rect.vcr_xdim) <= me->vb_xdim,
	        "X[=%" PRIuCRD "]+SX[=%" PRIuDIM "][=%" PRIuCRD "] exceeds XDIM[=%" PRIuDIM "]",
	        lock->_vrl_rect.vcr_xmin, lock->_vrl_rect.vcr_xdim,
	        lock->_vrl_rect.vcr_xmin + lock->_vrl_rect.vcr_xdim, me->vb_xdim);
	assertf((lock->_vrl_rect.vcr_ymin + lock->_vrl_rect.vcr_ydim) <= me->vb_ydim,
	        "Y[=%" PRIuCRD "]+SY[=%" PRIuDIM "][=%" PRIuCRD "] eyceeds YDIM[=%" PRIuDIM "]",
	        lock->_vrl_rect.vcr_ymin, lock->_vrl_rect.vcr_ydim,
	        lock->_vrl_rect.vcr_ymin + lock->_vrl_rect.vcr_ydim, me->vb_ydim);

	/* Make the region-rect relative to the base buffer. */
	lock->_vrl_rect.vcr_xmin += me->rbf_cxoff;
	lock->_vrl_rect.vcr_ymin += me->rbf_cyoff;
	atomic_inc(&me->rbf_inuse);
	base = atomic_read(&me->rbf_base);
	if (!OVERFLOW_UADD(lock->_vrl_rect.vcr_xmin, lock->_vrl_rect.vcr_xdim, &xend) &&
	    !OVERFLOW_UADD(lock->_vrl_rect.vcr_ymin, lock->_vrl_rect.vcr_ydim, &yend) &&
	    xend <= base->vb_xdim && yend <= base->vb_ydim) {
		int result = (*base->vb_ops->vi_wlockregion)(base, lock);
		if unlikely(result)
			atomic_dec(&me->rbf_inuse);
		return result;
	}
	atomic_dec(&me->rbf_inuse);
	errno = ERANGE;
	return -1;
}

INTERN ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC region_buffer__unlockregion)(struct video_buffer *__restrict self,
                                         struct video_regionlock *__restrict lock) {
	struct region_buffer *me = (struct region_buffer *)self;
	struct video_buffer *base = me->rbf_orig; /* Always release locks on the **original** buffer */
	(*base->vb_ops->vi_unlockregion)(base, lock);
	atomic_dec(&me->rbf_inuse);
	/* Restore original lock rect (in case of further nesting, and caller needs it) */
	lock->_vrl_rect.vcr_ymin -= me->rbf_cyoff;
	lock->_vrl_rect.vcr_xmin -= me->rbf_cxoff;
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
region_buffer_subregion_alias__rlock(struct video_buffer *__restrict self,
                                     struct video_lock *__restrict lock) {
	struct region_buffer_subregion_alias *me = (struct region_buffer_subregion_alias *)self;
	return (*me->rbf_base->vb_ops->vi_rlock)(me->rbf_base, lock);
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
region_buffer_subregion_alias__wlock(struct video_buffer *__restrict self,
                                     struct video_lock *__restrict lock) {
	struct region_buffer_subregion_alias *me = (struct region_buffer_subregion_alias *)self;
	return (*me->rbf_base->vb_ops->vi_wlock)(me->rbf_base, lock);
}

INTERN ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC region_buffer_subregion_alias__unlock)(struct video_buffer *__restrict self,
                                                   struct video_lock *__restrict lock) {
	struct region_buffer_subregion_alias *me = (struct region_buffer_subregion_alias *)self;
	(*me->rbf_base->vb_ops->vi_unlock)(me->rbf_base, lock);
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
region_buffer_subregion_alias__rlockregion(struct video_buffer *__restrict self,
                                           struct video_regionlock *__restrict lock) {
	struct region_buffer_subregion_alias *me = (struct region_buffer_subregion_alias *)self;
	return (*me->rbf_base->vb_ops->vi_rlockregion)(me->rbf_base, lock);
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
region_buffer_subregion_alias__wlockregion(struct video_buffer *__restrict self,
                                           struct video_regionlock *__restrict lock) {
	struct region_buffer_subregion_alias *me = (struct region_buffer_subregion_alias *)self;
	return (*me->rbf_base->vb_ops->vi_wlockregion)(me->rbf_base, lock);
}

INTERN ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC region_buffer_subregion_alias__unlockregion)(struct video_buffer *__restrict self,
                                                         struct video_regionlock *__restrict lock) {
	struct region_buffer_subregion_alias *me = (struct region_buffer_subregion_alias *)self;
	(*me->rbf_base->vb_ops->vi_unlockregion)(me->rbf_base, lock);
}



/* GFX */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
region_buffer__initgfx(struct video_gfx *__restrict self) {
	struct region_buffer *me = (struct region_buffer *)video_gfx_getbuffer(self);
	struct video_buffer *base;
	atomic_inc(&me->rbf_inuse);
	self->vx_surf.vs_buffer = base = atomic_read(&me->rbf_base);
	self->_vx_driver[REGION_GFX_SUBOPS] = NULL;
	self = (*base->vb_ops->vi_initgfx)(self);
	self = (*self->vx_hdr.vxh_ops->vgfo_clip)(self, me->rbf_cxoff, me->rbf_cyoff,
	                                          me->vb_xdim, me->vb_ydim);
	/* FIXME: THIS DOESN'T WORK!!!
	 *
	 * By always re-assigning "me" as buffer of "self", trying to use the GFX as the
	 * source of a blit operation will invoke the memory-locking functions on  "me",
	 * but with coords that are actually meant for "base"!!!
	 *
	 * The only real solution I see here is to:
	 * - still re-assign "vxh_ops" (and backup its original value)
	 * - But use another index in "_vx_driver" when it comes to storing "me",
	 *   since we can't have the GFX context's buffer not actually be the one
	 *   we are wrapping.
	 * - The "rbf_base" field must become  [1..1][const]. Since the real  base-
	 *   buffer always has to be stored and exposed in the GFX context, we must
	 *   also  keep a reference to it around, even if we are revoked. Else, the
	 *   pointer stored in the GFX won't be valid after we were revoked.
	 *
	 * (Thinking about it: is this whole buffer revocation system actually still
	 *  necessary? I mean: there won't be any point to it once multiple processes
	 *  come into play, at  which point I'll just  need some special kernel  file
	 *  that  can be  created to represent  a section of  physical memory, whilst
	 *  having an ioctl(2) to revoke said access by simply replacing all mappings
	 *  of it with /dev/void)
	 *
	 * >> Think about this a little more, but probably get rid of buffer revocation,
	 *    which  would then allow region buffers to  not have to hook GFX operations
	 *    at all!
	 *
	 * This would also mean I could get rid of the `*_distinct' aliases of various
	 * API functions (since  `video_buffer' would once  again be *FULLY*  [const],
	 * meaning there's no point in not having buffer sub-regions be re-used) */
	if likely(self->vx_surf.vs_buffer == base && self->_vx_driver[REGION_GFX_SUBOPS] == NULL) {
		/* GFX-reuse optimizations */
		self->_vx_driver[REGION_GFX_SUBOPS] = (void *)self->vx_hdr.vxh_ops;
		self->vx_hdr.vxh_ops = _region_gfx_subops_ops();
		self->vx_surf.vs_buffer = me;
	} else {
		/* No GFX-reuse optimizations :( */
		self->vx_hdr.vxh_ops = _region_gfx_subgfx_ops();
	}
	atomic_dec(&me->rbf_inuse);
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
region_buffer__updategfx(struct video_gfx *__restrict self, unsigned int what) {
	if (self->vx_hdr.vxh_ops == &region_gfx_subops_ops) {
		struct region_buffer *me = (struct region_buffer *)video_gfx_getbuffer(self);
		struct video_buffer *base;
		atomic_inc(&me->rbf_inuse);
		base = atomic_read(&me->rbf_base);
		if likely(base == me->rbf_orig) {
			self->vx_hdr.vxh_ops = (struct video_gfx_ops *)self->_vx_driver[REGION_GFX_SUBOPS];
			self->_vx_driver[REGION_GFX_SUBOPS] = NULL;
			self->vx_surf.vs_buffer = base;
			self = (*base->vb_ops->vi_updategfx)(self, what);
			if likely(self->vx_surf.vs_buffer == base && self->_vx_driver[REGION_GFX_SUBOPS] == NULL) {
				/* Keep doing GFX-reuse optimizations */
				self->_vx_driver[REGION_GFX_SUBOPS] = (void *)self->vx_hdr.vxh_ops;
				self->vx_hdr.vxh_ops = &region_gfx_subops_ops;
				self->vx_surf.vs_buffer = me;
			} else {
				/* Can no longer do GFX-reuse optimization :( */
				self->vx_hdr.vxh_ops = _region_gfx_subgfx_ops();
			}
		} else {
			self->vx_hdr.vxh_ops = &libvideo_emptygfx_ops;
		}
		atomic_dec(&me->rbf_inuse);
	}
	return self;
}


INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
region_buffer_subregion_alias__initgfx(struct video_gfx *__restrict self) {
	struct region_buffer_subregion_alias *me = (struct region_buffer_subregion_alias *)video_gfx_getbuffer(self);
	self->vx_surf.vs_buffer = me->rbf_base; /* Fast-forward to the underlying buffer */
	self = (*video_gfx_getbuffer(self)->vb_ops->vi_initgfx)(self);
	return self;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
region_buffer_subregion_alias__updategfx(struct video_gfx *__restrict self,
                                         unsigned int what) {
	/* Shouldn't actually get here, but just fix-up the buffer pointer and fast-forward */
	struct region_buffer_subregion_alias *me = (struct region_buffer_subregion_alias *)video_gfx_getbuffer(self);
	assert(me != me->rbf_base);
	self->vx_surf.vs_buffer = me->rbf_base; /* Fast-forward to the underlying buffer */
	return (*video_gfx_getbuffer(self)->vb_ops->vi_updategfx)(self, what);
}




/* GFX-OPERATORS
 *
 * Region buffers implement GFX/BLITTER/BLITTER3 in one of 2 ways:
 * - When the underlying buffer doesn't make use of the last driver
 *   data slot (iow: that slot is `NULL' and GFX init/update), then
 *   that slot is used to store the original GFX  `vx_hdr.vxh_ops':
 *   >> ... // Underlying init
 *   >> if (gfx->_vx_driver[_VIDEO_GFX_N_DRIVER - 1] == NULL) {
 *   >>     gfx->_vx_driver[_VIDEO_GFX_N_DRIVER - 1] = (void *)gfx->vx_hdr.vxh_ops;
 *   >>     gfx->vx_hdr.vxh_ops = &region_gfx_subops_ops;
 *   >> }
 * - Otherwise, if the last driver-slot is non-NULL, a fresh GFX
 *   context needs to be created for every high-level  operation
 *   performed,  and  the  original  (actual)  GFX  goes unused.
 *   >> else {
 *   >>     // In this case, `_vx_driver' (which was already
 *   >>     // initialized by the underlying buffer) goes unused
 *   >>     gfx->vx_hdr.vxh_ops = &region_gfx_subgfx_ops;
 *   >> }
 */
INTERN struct video_gfx_ops region_gfx_subgfx_ops = {};
INTERN struct video_gfx_ops region_gfx_subops_ops = {};
INTERN struct video_blitter_ops region_blitter_subgfx_ops = {};
INTERN struct video_blitter_ops region_blitter_subops_ops = {};
INTERN struct video_blitter3_ops region_blitter3_subgfx_ops = {};
INTERN struct video_blitter3_ops region_blitter3_subops_ops = {};

INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops *CC
_region_gfx_subgfx_ops(void) {
	if (!region_gfx_subgfx_ops.vgfo_blitfrom) {
		region_gfx_subgfx_ops.vgfo_blitfrom3       = &region_gfx_subgfx__blitfrom3;
		region_gfx_subgfx_ops.vgfo_clip            = &libvideo_gfx_clip__generic;
		region_gfx_subgfx_ops.vgfo_offset2coord    = &libvideo_gfx_offset2coord__generic;
		region_gfx_subgfx_ops.vgfo_coord2offset    = &libvideo_gfx_coord2offset__generic;
		region_gfx_subgfx_ops.vgfo_getcolor        = &region_gfx_subgfx__getcolor;
		region_gfx_subgfx_ops.vgfo_putcolor        = &region_gfx_subgfx__putcolor;
		region_gfx_subgfx_ops.vgfo_line            = &region_gfx_subgfx__line;
		region_gfx_subgfx_ops.vgfo_hline           = &region_gfx_subgfx__hline;
		region_gfx_subgfx_ops.vgfo_vline           = &region_gfx_subgfx__vline;
		region_gfx_subgfx_ops.vgfo_fill            = &region_gfx_subgfx__fill;
		region_gfx_subgfx_ops.vgfo_rect            = &region_gfx_subgfx__rect;
		region_gfx_subgfx_ops.vgfo_fillmask        = &region_gfx_subgfx__fillmask;
		region_gfx_subgfx_ops.vgfo_fillstretchmask = &region_gfx_subgfx__fillstretchmask;
		region_gfx_subgfx_ops.vgfo_gradient        = &region_gfx_subgfx__gradient;
		region_gfx_subgfx_ops.vgfo_hgradient       = &region_gfx_subgfx__hgradient;
		region_gfx_subgfx_ops.vgfo_vgradient       = &region_gfx_subgfx__vgradient;
		region_gfx_subgfx_ops.vgfo_bitblit         = &region_gfx_subgfx__bitblit;
		region_gfx_subgfx_ops.vgfo_stretch         = &region_gfx_subgfx__stretch;
		region_gfx_subgfx_ops.vgfo_bitblit3        = &region_gfx_subgfx__bitblit3;
		region_gfx_subgfx_ops.vgfo_stretch3        = &region_gfx_subgfx__stretch3;
		COMPILER_WRITE_BARRIER();
		region_gfx_subgfx_ops.vgfo_blitfrom = &region_gfx_subgfx__blitfrom;
		COMPILER_WRITE_BARRIER();
	}
	return &region_gfx_subgfx_ops;
}

INTERN ATTR_RETNONNULL WUNUSED struct video_gfx_ops *CC
_region_gfx_subops_ops(void) {
	if (!region_gfx_subops_ops.vgfo_blitfrom) {
		region_gfx_subops_ops.vgfo_blitfrom3       = &region_gfx_subops__blitfrom3;
		region_gfx_subops_ops.vgfo_clip            = &region_gfx_subops__clip;
		region_gfx_subops_ops.vgfo_offset2coord    = &region_gfx_subops__offset2coord;
		region_gfx_subops_ops.vgfo_coord2offset    = &region_gfx_subops__coord2offset;
		region_gfx_subops_ops.vgfo_getcolor        = &region_gfx_subops__getcolor;
		region_gfx_subops_ops.vgfo_putcolor        = &region_gfx_subops__putcolor;
		region_gfx_subops_ops.vgfo_line            = &region_gfx_subops__line;
		region_gfx_subops_ops.vgfo_hline           = &region_gfx_subops__hline;
		region_gfx_subops_ops.vgfo_vline           = &region_gfx_subops__vline;
		region_gfx_subops_ops.vgfo_fill            = &region_gfx_subops__fill;
		region_gfx_subops_ops.vgfo_rect            = &region_gfx_subops__rect;
		region_gfx_subops_ops.vgfo_fillmask        = &region_gfx_subops__fillmask;
		region_gfx_subops_ops.vgfo_fillstretchmask = &region_gfx_subops__fillstretchmask;
		region_gfx_subops_ops.vgfo_gradient        = &region_gfx_subops__gradient;
		region_gfx_subops_ops.vgfo_hgradient       = &region_gfx_subops__hgradient;
		region_gfx_subops_ops.vgfo_vgradient       = &region_gfx_subops__vgradient;
		region_gfx_subops_ops.vgfo_bitblit         = &region_gfx_subops__bitblit;
		region_gfx_subops_ops.vgfo_stretch         = &region_gfx_subops__stretch;
		region_gfx_subops_ops.vgfo_bitblit3        = &region_gfx_subops__bitblit3;
		region_gfx_subops_ops.vgfo_stretch3        = &region_gfx_subops__stretch3;
		COMPILER_WRITE_BARRIER();
		region_gfx_subops_ops.vgfo_blitfrom = &region_gfx_subops__blitfrom;
		COMPILER_WRITE_BARRIER();
	}
	return &region_gfx_subops_ops;
}

INTERN ATTR_RETNONNULL WUNUSED struct video_blitter_ops *CC
_region_blitter_subgfx_ops(void) {
	if (!region_blitter_subgfx_ops.vbto_bitblit) {
		region_blitter_subgfx_ops.vbto_stretch = &region_blitter_subgfx__stretch;
		COMPILER_WRITE_BARRIER();
		region_blitter_subgfx_ops.vbto_bitblit = &region_blitter_subgfx__bitblit;
		COMPILER_WRITE_BARRIER();
	}
	return &region_blitter_subgfx_ops;
}

INTERN ATTR_RETNONNULL WUNUSED struct video_blitter_ops *CC
_region_blitter_subops_ops(void) {
	if (!region_blitter_subops_ops.vbto_bitblit) {
		region_blitter_subops_ops.vbto_stretch = &region_blitter_subops__stretch;
		COMPILER_WRITE_BARRIER();
		region_blitter_subops_ops.vbto_bitblit = &region_blitter_subops__bitblit;
		COMPILER_WRITE_BARRIER();
	}
	return &region_blitter_subops_ops;
}

INTERN ATTR_RETNONNULL WUNUSED struct video_blitter3_ops *CC
_region_blitter3_subgfx_ops(void) {
	if (!region_blitter3_subgfx_ops.vbt3o_bitblit) {
		region_blitter3_subgfx_ops.vbt3o_stretch = &region_blitter3_subgfx__stretch;
		COMPILER_WRITE_BARRIER();
		region_blitter3_subgfx_ops.vbt3o_bitblit = &region_blitter3_subgfx__bitblit;
		COMPILER_WRITE_BARRIER();
	}
	return &region_blitter3_subgfx_ops;
}

INTERN ATTR_RETNONNULL WUNUSED struct video_blitter3_ops *CC
_region_blitter3_subops_ops(void) {
	if (!region_blitter3_subops_ops.vbt3o_bitblit) {
		region_blitter3_subops_ops.vbt3o_stretch = &region_blitter3_subops__stretch;
		COMPILER_WRITE_BARRIER();
		region_blitter3_subops_ops.vbt3o_bitblit = &region_blitter3_subops__bitblit;
		COMPILER_WRITE_BARRIER();
	}
	return &region_blitter3_subops_ops;
}



#define SUBGFX_BEGIN(subgfx_name, self)                                               \
	struct video_gfx subgfx_name;                                                     \
	struct region_buffer *_sg_me = (struct region_buffer *)video_gfx_getbuffer(self); \
	struct video_buffer *base;                                                        \
	atomic_inc(&_sg_me->rbf_inuse);                                                   \
	base = atomic_read(&_sg_me->rbf_base);                                            \
	video_buffer_getgfx_ex(base, &subgfx_name,                                        \
	                       video_gfx_getblend(self),                                  \
	                       video_gfx_getpalette(self),                                \
	                       video_gfx_getflags(self),                                  \
	                       video_gfx_getcolorkey(self));                              \
	/* Load I/O and Clip Rects of our own GFX into the underlying GFX */              \
	video_gfx_clip(&subgfx_name,                                                      \
	               (self)->vx_hdr.vxh_bxmin,                                          \
	               (self)->vx_hdr.vxh_bymin,                                          \
	               (self)->vx_hdr.vxh_bxend - (self)->vx_hdr.vxh_bxmin,               \
	               (self)->vx_hdr.vxh_byend - (self)->vx_hdr.vxh_bymin);              \
	video_gfx_clip(&subgfx_name,                                                      \
	               (self)->vx_hdr.vxh_cxoff - (self)->vx_hdr.vxh_bxmin,               \
	               (self)->vx_hdr.vxh_cyoff - (self)->vx_hdr.vxh_bymin,               \
	               (self)->vx_hdr.vxh_cxdim,                                          \
	               (self)->vx_hdr.vxh_cydim)
#define SUBGFX_END() \
	atomic_dec(&_sg_me->rbf_inuse)
#define SUBOPS_BEGIN(self)                                                                            \
	struct video_gfx *_mygfx = (struct video_gfx *)(self);                                            \
	struct video_buffer *_so_base;                                                                    \
	struct region_buffer *_so_me = (struct region_buffer *)video_gfx_getbuffer(_mygfx);               \
	assert(_mygfx->vx_hdr.vxh_ops == &region_gfx_subops_ops);                                         \
	atomic_inc(&_so_me->rbf_inuse);                                                                   \
	_so_base = atomic_read(&_so_me->rbf_base);                                                        \
	if likely(_so_base == _so_me->rbf_orig) {                                                         \
		_mygfx->vx_hdr.vxh_ops = (struct video_gfx_ops const *)_mygfx->_vx_driver[REGION_GFX_SUBOPS]; \
		_mygfx->_vx_driver[REGION_GFX_SUBOPS] = NULL;                                                 \
		_mygfx->vx_surf.vs_buffer = _so_base
#define SUBOPS_END()                                                            \
		assert(_mygfx->vx_surf.vs_buffer == _so_base);                          \
		assert(_mygfx->_vx_driver[REGION_GFX_SUBOPS] == NULL);                  \
		_mygfx->_vx_driver[REGION_GFX_SUBOPS] = (void *)_mygfx->vx_hdr.vxh_ops; \
		_mygfx->vx_hdr.vxh_ops = &region_gfx_subops_ops;                        \
		_mygfx->vx_surf.vs_buffer = _so_me;                                     \
	} else {                                                                    \
		_mygfx->vx_hdr.vxh_ops = &libvideo_emptygfx_ops;                        \
	}                                                                           \
	atomic_dec(&_so_me->rbf_inuse)

INTERN ATTR_RETNONNULL ATTR_INOUT_T(1) struct video_blitter *FCC
region_gfx_subgfx__blitfrom(struct video_blitter *__restrict ctx) {
	ctx->vbt_ops = _region_blitter_subgfx_ops();
	return ctx;
}

INTERN ATTR_RETNONNULL ATTR_INOUT_T(1) struct video_blitter *FCC
region_gfx_subops__blitfrom(struct video_blitter *__restrict ctx) {
	SUBOPS_BEGIN(ctx->vbt_dst);
	ctx->_vbt_driver[REGION_BLITTER_SUBOPS] = NULL;
	ctx = (*ctx->vbt_dst->vx_hdr.vxh_ops->vgfo_blitfrom)(ctx);
	if likely(ctx->_vbt_driver[REGION_BLITTER_SUBOPS] == NULL) {
		ctx->_vbt_driver[REGION_BLITTER_SUBOPS] = (void *)ctx->vbt_ops;
		ctx->vbt_ops = _region_blitter_subops_ops();
	} else {
		ctx->vbt_ops = _region_blitter_subgfx_ops();
	}
	SUBOPS_END();
	return ctx;
}

INTERN ATTR_RETNONNULL ATTR_INOUT_T(1) struct video_blitter3 *FCC
region_gfx_subgfx__blitfrom3(struct video_blitter3 *__restrict ctx) {
	ctx->vbt3_ops = _region_blitter3_subgfx_ops();
	return ctx;
}

INTERN ATTR_RETNONNULL ATTR_INOUT_T(1) struct video_blitter3 *FCC
region_gfx_subops__blitfrom3(struct video_blitter3 *__restrict ctx) {
	SUBOPS_BEGIN(ctx->vbt3_wrdst);
	ctx->_vbt3_driver[REGION_BLITTER3_SUBOPS] = NULL;
	ctx = (*ctx->vbt3_wrdst->vx_hdr.vxh_ops->vgfo_blitfrom3)(ctx);
	if likely(ctx->_vbt3_driver[REGION_BLITTER3_SUBOPS] == NULL) {
		ctx->_vbt3_driver[REGION_BLITTER3_SUBOPS] = (void *)ctx->vbt3_ops;
		ctx->vbt3_ops = _region_blitter3_subops_ops();
	} else {
		ctx->vbt3_ops = _region_blitter3_subgfx_ops();
	}
	SUBOPS_END();
	return ctx;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *CC
region_gfx_subops__clip(struct video_gfx *__restrict self,
                        video_offset_t clip_x, video_offset_t clip_y,
                        video_dim_t size_x, video_dim_t size_y) {
	SUBOPS_BEGIN(self);
	self = _mygfx = (*self->vx_hdr.vxh_ops->vgfo_clip)(self, clip_x, clip_y, size_x, size_y);
	SUBOPS_END();
	return self;
}

INTERN WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC
region_gfx_subops__offset2coord(struct video_gfx const *__restrict self,
                                video_offset_t x, video_offset_t y,
                                video_coord_t coords[2]) {
	bool result;
	SUBOPS_BEGIN(self);
	result = (*self->vx_hdr.vxh_ops->vgfo_offset2coord)(self, x, y, coords);
	SUBOPS_END();
	return result;
}

INTERN WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC
region_gfx_subops__coord2offset(struct video_gfx const *__restrict self,
                                video_coord_t x, video_coord_t y,
                                video_offset_t offsets[2]) {
	bool result;
	SUBOPS_BEGIN(self);
	result = (*self->vx_hdr.vxh_ops->vgfo_coord2offset)(self, x, y, offsets);
	SUBOPS_END();
	return result;
}

INTERN ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC
region_gfx_subgfx__getcolor(struct video_gfx const *__restrict self,
                            video_offset_t x, video_offset_t y) {
	video_color_t result;
	SUBGFX_BEGIN(subgfx, self);
	result = (*subgfx.vx_hdr.vxh_ops->vgfo_getcolor)(&subgfx, x, y);
	SUBGFX_END();
	return result;
}

INTERN ATTR_IN(1) void CC
region_gfx_subgfx__putcolor(struct video_gfx const *__restrict self,
                            video_offset_t x, video_offset_t y,
                            video_color_t color) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_putcolor)(&subgfx, x, y, color);
	SUBGFX_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subgfx__line(struct video_gfx const *__restrict self,
                        video_offset_t x1, video_offset_t y1,
                        video_offset_t x2, video_offset_t y2,
                        video_color_t color) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_line)(&subgfx, x1, y1, x2, y2, color);
	SUBGFX_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subgfx__hline(struct video_gfx const *__restrict self,
                         video_offset_t x, video_offset_t y,
                         video_dim_t length, video_color_t color) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_hline)(&subgfx, x, y, length, color);
	SUBGFX_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subgfx__vline(struct video_gfx const *__restrict self,
                         video_offset_t x, video_offset_t y,
                         video_dim_t length, video_color_t color) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_vline)(&subgfx, x, y, length, color);
	SUBGFX_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subgfx__fill(struct video_gfx const *__restrict self,
                        video_offset_t x, video_offset_t y,
                        video_dim_t size_x, video_dim_t size_y,
                        video_color_t color) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_fill)(&subgfx, x, y, size_x, size_y, color);
	SUBGFX_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subgfx__rect(struct video_gfx const *__restrict self,
                        video_offset_t x, video_offset_t y,
                        video_dim_t size_x, video_dim_t size_y,
                        video_color_t color) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_rect)(&subgfx, x, y, size_x, size_y, color);
	SUBGFX_END();
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC
region_gfx_subgfx__fillmask(struct video_gfx const *__restrict self,
                            video_offset_t x, video_offset_t y,
                            video_dim_t size_x, video_dim_t size_y,
                            video_color_t const bg_fg_colors[2],
                            struct video_bitmask const *__restrict bm) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_fillmask)(&subgfx, x, y, size_x, size_y, bg_fg_colors, bm);
	SUBGFX_END();
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
region_gfx_subgfx__fillstretchmask(struct video_gfx const *__restrict self,
                                   video_offset_t dst_x, video_offset_t dst_y,
                                   video_dim_t dst_size_x, video_dim_t dst_size_y,
                                   video_color_t const bg_fg_colors[2],
                                   video_dim_t src_size_x, video_dim_t src_size_y,
                                   struct video_bitmask const *__restrict bm) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_fillstretchmask)(&subgfx, dst_x, dst_y, dst_size_x, dst_size_y,
	                                               bg_fg_colors, src_size_x, src_size_y, bm);
	SUBGFX_END();
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
region_gfx_subgfx__gradient(struct video_gfx const *__restrict self,
                            video_offset_t x, video_offset_t y,
                            video_dim_t size_x, video_dim_t size_y,
                            video_color_t const colors[2][2]) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_gradient)(&subgfx, x, y, size_x, size_y, colors);
	SUBGFX_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subgfx__hgradient(struct video_gfx const *__restrict self,
                             video_offset_t x, video_offset_t y,
                             video_dim_t size_x, video_dim_t size_y,
                             video_color_t locolor, video_color_t hicolor) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_hgradient)(&subgfx, x, y, size_x, size_y, locolor, hicolor);
	SUBGFX_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subgfx__vgradient(struct video_gfx const *__restrict self,
                             video_offset_t x, video_offset_t y,
                             video_dim_t size_x, video_dim_t size_y,
                             video_color_t locolor, video_color_t hicolor) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_vgradient)(&subgfx, x, y, size_x, size_y, locolor, hicolor);
	SUBGFX_END();
}

INTERN ATTR_IN(1) ATTR_IN(4) void CC
region_gfx_subgfx__bitblit(struct video_gfx const *dst,
                           video_offset_t dst_x, video_offset_t dst_y,
                           struct video_gfx const *src,
                           video_offset_t src_x, video_offset_t src_y,
                           video_dim_t size_x, video_dim_t size_y) {
	SUBGFX_BEGIN(subgfx, dst);
	(*subgfx.vx_hdr.vxh_ops->vgfo_bitblit)(&subgfx, dst_x, dst_y, src, src_x, src_y, size_x, size_y);
	SUBGFX_END();
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
region_gfx_subgfx__stretch(struct video_gfx const *dst,
                           video_offset_t dst_x, video_offset_t dst_y,
                           video_dim_t dst_size_x, video_dim_t dst_size_y,
                           struct video_gfx const *src,
                           video_offset_t src_x, video_offset_t src_y,
                           video_dim_t src_size_x, video_dim_t src_size_y) {
	SUBGFX_BEGIN(subgfx, dst);
	(*subgfx.vx_hdr.vxh_ops->vgfo_stretch)(&subgfx, dst_x, dst_y, dst_size_x, dst_size_y,
	                                       src, src_x, src_y, src_size_x, src_size_y);
	SUBGFX_END();
}

INTERN ATTR_IN(1) ATTR_IN(4) ATTR_IN(7) void CC
region_gfx_subgfx__bitblit3(struct video_gfx const *wrdst,
                            video_offset_t wrdst_x, video_offset_t wrdst_y,
                            struct video_gfx const *rddst,
                            video_offset_t rddst_x, video_offset_t rddst_y,
                            struct video_gfx const *src,
                            video_offset_t src_x, video_offset_t src_y,
                            video_dim_t size_x, video_dim_t size_y) {
	SUBGFX_BEGIN(subgfx, wrdst);
	(*subgfx.vx_hdr.vxh_ops->vgfo_bitblit3)(&subgfx, wrdst_x, wrdst_y, rddst, rddst_x, rddst_y,
	                                        src, src_x, src_y, size_x, size_y);
	SUBGFX_END();
}

INTERN ATTR_IN(1) ATTR_IN(4) ATTR_IN(9) void CC
region_gfx_subgfx__stretch3(struct video_gfx const *wrdst,
                            video_offset_t wrdst_x, video_offset_t wrdst_y,
                            struct video_gfx const *rddst,
                            video_offset_t rddst_x, video_offset_t rddst_y,
                            video_dim_t dst_size_x, video_dim_t dst_size_y,
                            struct video_gfx const *src,
                            video_offset_t src_x, video_offset_t src_y,
                            video_dim_t src_size_x, video_dim_t src_size_y) {
	SUBGFX_BEGIN(subgfx, wrdst);
	(*subgfx.vx_hdr.vxh_ops->vgfo_stretch3)(&subgfx, wrdst_x, wrdst_y, rddst,
	                                        rddst_x, rddst_y, dst_size_x, dst_size_y,
	                                        src, src_x, src_y, src_size_x, src_size_y);
	SUBGFX_END();
}



INTERN ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC
region_gfx_subops__getcolor(struct video_gfx const *__restrict self,
                            video_offset_t x, video_offset_t y) {
	video_color_t result;
	SUBOPS_BEGIN(self);
	result = (*self->vx_hdr.vxh_ops->vgfo_getcolor)(self, x, y);
	SUBOPS_END();
	return result;
}

INTERN ATTR_IN(1) void CC
region_gfx_subops__putcolor(struct video_gfx const *__restrict self,
                            video_offset_t x, video_offset_t y,
                            video_color_t color) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_putcolor)(self, x, y, color);
	SUBOPS_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subops__line(struct video_gfx const *__restrict self,
                        video_offset_t x1, video_offset_t y1,
                        video_offset_t x2, video_offset_t y2,
                        video_color_t color) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_line)(self, x1, y1, x2, y2, color);
	SUBOPS_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subops__hline(struct video_gfx const *__restrict self,
                         video_offset_t x, video_offset_t y,
                         video_dim_t length, video_color_t color) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_hline)(self, x, y, length, color);
	SUBOPS_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subops__vline(struct video_gfx const *__restrict self,
                         video_offset_t x, video_offset_t y,
                         video_dim_t length, video_color_t color) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_vline)(self, x, y, length, color);
	SUBOPS_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subops__fill(struct video_gfx const *__restrict self,
                        video_offset_t x, video_offset_t y,
                        video_dim_t size_x, video_dim_t size_y,
                        video_color_t color) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_fill)(self, x, y, size_x, size_y, color);
	SUBOPS_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subops__rect(struct video_gfx const *__restrict self,
                        video_offset_t x, video_offset_t y,
                        video_dim_t size_x, video_dim_t size_y,
                        video_color_t color) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_rect)(self, x, y, size_x, size_y, color);
	SUBOPS_END();
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC
region_gfx_subops__fillmask(struct video_gfx const *__restrict self,
                            video_offset_t x, video_offset_t y,
                            video_dim_t size_x, video_dim_t size_y,
                            video_color_t const bg_fg_colors[2],
                            struct video_bitmask const *__restrict bm) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_fillmask)(self, x, y, size_x, size_y, bg_fg_colors, bm);
	SUBOPS_END();
}

INTERN ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
region_gfx_subops__fillstretchmask(struct video_gfx const *__restrict self,
                                   video_offset_t dst_x, video_offset_t dst_y,
                                   video_dim_t dst_size_x, video_dim_t dst_size_y,
                                   video_color_t const bg_fg_colors[2],
                                   video_dim_t src_size_x, video_dim_t src_size_y,
                                   struct video_bitmask const *__restrict bm) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_fillstretchmask)(self, dst_x, dst_y, dst_size_x, dst_size_y,
	                                              bg_fg_colors, src_size_x, src_size_y, bm);
	SUBOPS_END();
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
region_gfx_subops__gradient(struct video_gfx const *__restrict self,
                            video_offset_t x, video_offset_t y,
                            video_dim_t size_x, video_dim_t size_y,
                            video_color_t const colors[2][2]) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_gradient)(self, x, y, size_x, size_y, colors);
	SUBOPS_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subops__hgradient(struct video_gfx const *__restrict self,
                             video_offset_t x, video_offset_t y,
                             video_dim_t size_x, video_dim_t size_y,
                             video_color_t locolor, video_color_t hicolor) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_hgradient)(self, x, y, size_x, size_y, locolor, hicolor);
	SUBOPS_END();
}

INTERN ATTR_IN(1) void CC
region_gfx_subops__vgradient(struct video_gfx const *__restrict self,
                             video_offset_t x, video_offset_t y,
                             video_dim_t size_x, video_dim_t size_y,
                             video_color_t locolor, video_color_t hicolor) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_vgradient)(self, x, y, size_x, size_y, locolor, hicolor);
	SUBOPS_END();
}

INTERN ATTR_IN(1) ATTR_IN(4) void CC
region_gfx_subops__bitblit(struct video_gfx const *dst,
                           video_offset_t dst_x, video_offset_t dst_y,
                           struct video_gfx const *src,
                           video_offset_t src_x, video_offset_t src_y,
                           video_dim_t size_x, video_dim_t size_y) {
	SUBOPS_BEGIN(dst);
	(*dst->vx_hdr.vxh_ops->vgfo_bitblit)(dst, dst_x, dst_y, src, src_x, src_y, size_x, size_y);
	SUBOPS_END();
}

INTERN ATTR_IN(1) ATTR_IN(6) void CC
region_gfx_subops__stretch(struct video_gfx const *dst,
                           video_offset_t dst_x, video_offset_t dst_y,
                           video_dim_t dst_size_x, video_dim_t dst_size_y,
                           struct video_gfx const *src,
                           video_offset_t src_x, video_offset_t src_y,
                           video_dim_t src_size_x, video_dim_t src_size_y) {
	SUBOPS_BEGIN(dst);
	(*dst->vx_hdr.vxh_ops->vgfo_stretch)(dst, dst_x, dst_y, dst_size_x, dst_size_y,
	                                     src, src_x, src_y, src_size_x, src_size_y);
	SUBOPS_END();
}

INTERN ATTR_IN(1) ATTR_IN(4) ATTR_IN(7) void CC
region_gfx_subops__bitblit3(struct video_gfx const *wrdst,
                            video_offset_t wrdst_x, video_offset_t wrdst_y,
                            struct video_gfx const *rddst,
                            video_offset_t rddst_x, video_offset_t rddst_y,
                            struct video_gfx const *src,
                            video_offset_t src_x, video_offset_t src_y,
                            video_dim_t size_x, video_dim_t size_y) {
	SUBOPS_BEGIN(wrdst);
	(*wrdst->vx_hdr.vxh_ops->vgfo_bitblit3)(wrdst, wrdst_x, wrdst_y, rddst, rddst_x, rddst_y,
	                                        src, src_x, src_y, size_x, size_y);
	SUBOPS_END();
}

INTERN ATTR_IN(1) ATTR_IN(4) ATTR_IN(9) void CC
region_gfx_subops__stretch3(struct video_gfx const *wrdst,
                            video_offset_t wrdst_x, video_offset_t wrdst_y,
                            struct video_gfx const *rddst,
                            video_offset_t rddst_x, video_offset_t rddst_y,
                            video_dim_t dst_size_x, video_dim_t dst_size_y,
                            struct video_gfx const *src,
                            video_offset_t src_x, video_offset_t src_y,
                            video_dim_t src_size_x, video_dim_t src_size_y) {
	SUBOPS_BEGIN(wrdst);
	(*wrdst->vx_hdr.vxh_ops->vgfo_stretch3)(wrdst, wrdst_x, wrdst_y, rddst,
	                                        rddst_x, rddst_y, dst_size_x, dst_size_y,
	                                        src, src_x, src_y, src_size_x, src_size_y);
	SUBOPS_END();
}


INTERN ATTR_IN_T(1) void CC
region_blitter_subgfx__bitblit(struct video_blitter const *__restrict self,
                              video_offset_t dst_x, video_offset_t dst_y,
                              video_offset_t src_x, video_offset_t src_y,
                              video_dim_t size_x, video_dim_t size_y) {
	SUBGFX_BEGIN(subgfx, self->vbt_dst);
	(*subgfx.vx_hdr.vxh_ops->vgfo_bitblit)(&subgfx, dst_x, dst_y,
	                                       self->vbt_src, src_x, src_y,
	                                       size_x, size_y);
	SUBGFX_END();
}

INTERN ATTR_IN_T(1) void CC
region_blitter_subgfx__stretch(struct video_blitter const *__restrict self,
                              video_offset_t dst_x, video_offset_t dst_y,
                              video_dim_t dst_size_x, video_dim_t dst_size_y,
                              video_offset_t src_x, video_offset_t src_y,
                              video_dim_t src_size_x, video_dim_t src_size_y) {
	SUBGFX_BEGIN(subgfx, self->vbt_dst);
	(*subgfx.vx_hdr.vxh_ops->vgfo_stretch)(&subgfx, dst_x, dst_y, dst_size_x, dst_size_y,
	                                       self->vbt_src, src_x, src_y, src_size_x, src_size_y);
	SUBGFX_END();
}

INTERN ATTR_IN_T(1) void CC
region_blitter3_subgfx__bitblit(struct video_blitter3 const *__restrict self,
                               video_offset_t wrdst_x, video_offset_t wrdst_y,
                               video_offset_t rddst_x, video_offset_t rddst_y,
                               video_offset_t src_x, video_offset_t src_y,
                               video_dim_t size_x, video_dim_t size_y) {
	SUBGFX_BEGIN(subgfx, self->vbt3_wrdst);
	(*subgfx.vx_hdr.vxh_ops->vgfo_bitblit3)(&subgfx, wrdst_x, wrdst_y,
	                                        self->vbt3_rddst, rddst_x, rddst_y,
	                                        self->vbt3_src, src_x, src_y,
	                                        size_x, size_y);
	SUBGFX_END();
}

INTERN ATTR_IN_T(1) void CC
region_blitter3_subgfx__stretch(struct video_blitter3 const *__restrict self,
                               video_offset_t wrdst_x, video_offset_t wrdst_y,
                               video_offset_t rddst_x, video_offset_t rddst_y,
                               video_dim_t dst_size_x, video_dim_t dst_size_y,
                               video_offset_t src_x, video_offset_t src_y,
                               video_dim_t src_size_x, video_dim_t src_size_y) {
	SUBGFX_BEGIN(subgfx, self->vbt3_wrdst);
	(*subgfx.vx_hdr.vxh_ops->vgfo_stretch3)(&subgfx, wrdst_x, wrdst_y,
	                                        self->vbt3_rddst, rddst_x, rddst_y,
	                                        dst_size_x, dst_size_y,
	                                        self->vbt3_src, src_x, src_y,
	                                        src_size_x, src_size_y);
	SUBGFX_END();
}



#define SUBBLIT_BEGIN(self)                                                                         \
	struct video_blitter *_sb_me = (self);                                                          \
	assert(_sb_me->vbt_ops == &region_blitter_subops_ops);                                         \
	_sb_me->vbt_ops = (struct video_blitter_ops const *)_sb_me->_vbt_driver[REGION_BLITTER_SUBOPS]; \
	_sb_me->_vbt_driver[REGION_BLITTER_SUBOPS] = NULL
#define SUBBLIT_END()                                                     \
	assert(_sb_me->_vbt_driver[REGION_BLITTER_SUBOPS] == NULL);           \
	_sb_me->_vbt_driver[REGION_BLITTER_SUBOPS] = (void *)_sb_me->vbt_ops; \
	_sb_me->vbt_ops = &region_blitter_subops_ops

#define SUBBLIT3_BEGIN(self)                                                                              \
	struct video_blitter3 *_sb3_me = (self);                                                              \
	assert(_sb3_me->vbt3_ops == &region_blitter3_subops_ops);                                            \
	_sb3_me->vbt3_ops = (struct video_blitter3_ops const *)_sb3_me->_vbt3_driver[REGION_BLITTER3_SUBOPS]; \
	_sb3_me->_vbt3_driver[REGION_BLITTER3_SUBOPS] = NULL
#define SUBBLIT3_END()                                                         \
	assert(_sb3_me->_vbt3_driver[REGION_BLITTER3_SUBOPS] == NULL);             \
	_sb3_me->_vbt3_driver[REGION_BLITTER3_SUBOPS] = (void *)_sb3_me->vbt3_ops; \
	_sb3_me->vbt3_ops = &region_blitter3_subops_ops


INTERN ATTR_IN_T(1) void CC
region_blitter_subops__bitblit(struct video_blitter const *__restrict self,
                               video_offset_t dst_x, video_offset_t dst_y,
                               video_offset_t src_x, video_offset_t src_y,
                               video_dim_t size_x, video_dim_t size_y) {
	struct video_blitter *me = (struct video_blitter *)self;
	SUBOPS_BEGIN(me->vbt_dst);
	SUBBLIT_BEGIN(me);
	(*me->vbt_ops->vbto_bitblit)(me, dst_x, dst_y, src_x, src_y, size_x, size_y);
	SUBBLIT_END();
	SUBOPS_END();
}

INTERN ATTR_IN_T(1) void CC
region_blitter_subops__stretch(struct video_blitter const *__restrict self,
                               video_offset_t dst_x, video_offset_t dst_y,
                               video_dim_t dst_size_x, video_dim_t dst_size_y,
                               video_offset_t src_x, video_offset_t src_y,
                               video_dim_t src_size_x, video_dim_t src_size_y) {
	struct video_blitter *me = (struct video_blitter *)self;
	SUBOPS_BEGIN(me->vbt_dst);
	SUBBLIT_BEGIN(me);
	(*me->vbt_ops->vbto_stretch)(me, dst_x, dst_y, dst_size_x, dst_size_y,
	                             src_x, src_y, src_size_x, src_size_y);
	SUBBLIT_END();
	SUBOPS_END();
}


INTERN ATTR_IN_T(1) void CC
region_blitter3_subops__bitblit(struct video_blitter3 const *__restrict self,
                                video_offset_t wrdst_x, video_offset_t wrdst_y,
                                video_offset_t rddst_x, video_offset_t rddst_y,
                                video_offset_t src_x, video_offset_t src_y,
                                video_dim_t size_x, video_dim_t size_y) {
	struct video_blitter3 *me = (struct video_blitter3 *)self;
	SUBOPS_BEGIN(me->vbt3_wrdst);
	SUBBLIT3_BEGIN(me);
	(*me->vbt3_ops->vbt3o_bitblit)(me, wrdst_x, wrdst_y, rddst_x, rddst_y, src_x, src_y, size_x, size_y);
	SUBBLIT3_END();
	SUBOPS_END();
}

INTERN ATTR_IN_T(1) void CC
region_blitter3_subops__stretch(struct video_blitter3 const *__restrict self,
                                video_offset_t wrdst_x, video_offset_t wrdst_y,
                                video_offset_t rddst_x, video_offset_t rddst_y,
                                video_dim_t dst_size_x, video_dim_t dst_size_y,
                                video_offset_t src_x, video_offset_t src_y,
                                video_dim_t src_size_x, video_dim_t src_size_y) {
	struct video_blitter3 *me = (struct video_blitter3 *)self;
	SUBOPS_BEGIN(me->vbt3_wrdst);
	SUBBLIT3_BEGIN(me);
	(*me->vbt3_ops->vbt3o_stretch)(me, wrdst_x, wrdst_y,
	                               rddst_x, rddst_y, dst_size_x, dst_size_y,
	                               src_x, src_y, src_size_x, src_size_y);
	SUBBLIT3_END();
	SUBOPS_END();
}








/* Create a new region-relative-proxy of `self', that interacts with the same
 * pixel data, both during GFX operations, as well when creating video locks.
 *
 * You can also use this function to create regions at negative offsets, or
 * ones that are larger than `self'.
 *
 * Then returned buffer always behaves properly when it comes to being able to
 * be  revoked, after which point it will never again make any access to pixel
 * data of `self'.
 *
 * When  the  given `rect'  is actually  a sub-region  of `self',  then this
 * function will simply make use of `video_surface_subregion()' and call the
 * dedicated video buffer operator for creating sub-regions.
 *
 * When the returned buffer isn't created as a true sub-region of  `self',
 * its `vb_domain' will be set to the return value of `video_ramdomain()'.
 *
 * @param: self: Video buffer to create a region of
 * @param: rect: region rect of `self' to-be returned
 * @return: * : The newly created region buffer
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=*] Failed to create region for some other reason */
DEFINE_PUBLIC_ALIAS(video_surface_region, libvideo_surface_region);
DEFINE_PUBLIC_ALIAS(video_surface_region_distinct, libvideo_surface_region_distinct);
INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *CC
libvideo_surface_region(struct video_surface const *__restrict self,
                        struct video_rect const *__restrict rect) {
	if (rect->vr_xmin == 0 && rect->vr_ymin == 0 &&
	    rect->vr_xdim == video_surface_getxdim(self) &&
	    rect->vr_ydim == video_surface_getydim(self) &&
	    video_surface_isdefault(self)) {
		struct video_buffer *buffer = video_surface_getbuffer(self);
		video_buffer_incref(buffer);
		return buffer;
	}
	return libvideo_surface_region_distinct(self, rect);
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *CC
libvideo_surface_region_distinct(struct video_surface const *__restrict self,
                                 struct video_rect const *__restrict rect) {
	struct video_buffer *buffer = video_surface_getbuffer(self);
	REF struct region_buffer *result;
	bool self_is_region;
	struct video_rect buffer_rect = *rect;
	if (video_surface_getflags(self) & VIDEO_GFX_F_XYSWAP) {
		buffer_rect.vr_xmin = rect->vr_ymin;
		buffer_rect.vr_ymin = rect->vr_xmin;
		buffer_rect.vr_xdim = rect->vr_ydim;
		buffer_rect.vr_ydim = rect->vr_xdim;
	}

	/* Check for simple case: can we do this as a sub-region? */
	if (buffer_rect.vr_xmin >= 0 && buffer_rect.vr_ymin >= 0) {
		video_coord_t rect_xend, rect_yend;
		if (!OVERFLOW_UADD((video_coord_t)buffer_rect.vr_xmin, buffer_rect.vr_xdim, &rect_xend) &&
		    !OVERFLOW_UADD((video_coord_t)buffer_rect.vr_ymin, buffer_rect.vr_ydim, &rect_yend) &&
		    rect_xend <= video_buffer_getxdim(buffer) &&
		    rect_yend <= video_buffer_getydim(buffer)) {
			/* Yes! Yes, we can! */
			static_assert(offsetof(struct video_rect, vr_xmin) == offsetof(struct video_crect, vcr_xmin));
			static_assert(offsetof(struct video_rect, vr_ymin) == offsetof(struct video_crect, vcr_ymin));
			static_assert(offsetof(struct video_rect, vr_xdim) == offsetof(struct video_crect, vcr_xdim));
			static_assert(offsetof(struct video_rect, vr_ydim) == offsetof(struct video_crect, vcr_ydim));
			return _video_surface_subregion(self, (struct video_crect const *)&buffer_rect);
		}
	}

	/* Check if "self" is already a region-buffer */
	self_is_region = buffer->vb_ops == &region_buffer_ops &&
	                 buffer->vb_ops == &region_buffer_subregion_ops &&
	                 buffer->vb_ops == &region_buffer_subregion_alias_ops;

	/* Allocate result buffer */
	result = (REF struct region_buffer *)malloc(self_is_region
	                                            ? sizeof(struct region_buffer_subregion)
	                                            : sizeof(struct region_buffer));
	if unlikely(!result)
		goto err;

	/* Start filling in basic data for `result' */
	video_surface_copyattrib(&result->vb_surf, self);
	result->vb_codec  = video_buffer_getcodec(buffer);
	result->vb_domain = _libvideo_ramdomain();
	result->vb_xdim   = buffer_rect.vr_xdim;
	result->vb_ydim   = buffer_rect.vr_ydim;
	result->vb_refcnt = 1;
	result->rbf_cxoff = buffer_rect.vr_xmin;
	result->rbf_cyoff = buffer_rect.vr_ymin;
	result->rbf_inuse = 0;
	LIST_INIT(&result->rbf_child_list);
	atomic_lock_init(&result->rbf_child_lock);

	if (self_is_region) {
		struct region_buffer_subregion *ret = (struct region_buffer_subregion *)result;
		struct region_buffer *me = (struct region_buffer *)self;
		REF struct video_buffer *base;
		struct video_rect me_crect, ret_crect, base_crect;
		struct video_rect base_iorect;
		atomic_inc(&me->rbf_inuse);
		base = atomic_read(&me->rbf_base);
		video_buffer_incref(base);
		atomic_dec(&me->rbf_inuse);

		/* Calculate intersection of 3 rects:
		 * - {{0,0},                           {base->vb_xdim,base->vb_ydim}}
		 * - {{me->rbf_cxoff,me->rbf_cyoff},   {me->vb_xdim,me->vb_ydim}}
		 * - {{me->rbf_cxoff+ret->rbf_cxoff,me->rbf_cyoff+ret->rbf_cyoff}, {ret->vb_xdim,ret->vb_ydim}}
		 *
		 * The  result represents the sub-region (and I/O Rect) of "base" that
		 * needs to be applied for that buffer to correctly usable in "result"
		 *
		 * However, if that rect is identical to the {{0,0}, ...} rect above,
		 * then the I/O Rect doesn't  change after the region operation,  and
		 * "base" can be re-used as-is in "result"
		 *
		 * If those rects don't all intersect, then we can just return an empty
		 * buffer instead. */
		base_crect.vr_xmin = 0;
		base_crect.vr_ymin = 0;
		base_crect.vr_xdim = base->vb_xdim;
		base_crect.vr_ydim = base->vb_ydim;
		me_crect.vr_xmin   = me->rbf_cxoff;
		me_crect.vr_ymin   = me->rbf_cyoff;
		me_crect.vr_xdim   = me->vb_xdim;
		me_crect.vr_ydim   = me->vb_ydim;
		ret_crect.vr_xmin  = me_crect.vr_xmin + ret->rbf_cxoff;
		ret_crect.vr_ymin  = me_crect.vr_ymin + ret->rbf_cyoff;
		ret_crect.vr_xdim  = ret->vb_xdim;
		ret_crect.vr_ydim  = ret->vb_ydim;

		if (!video_rect_intersect_overflow(&me_crect, &ret_crect, &base_iorect))
			goto do_return_empty_buffer_r;
		if (!video_rect_intersect_overflow(&base_iorect, &base_crect, &base_iorect))
			goto do_return_empty_buffer_r;
		assert(!video_rect_isempty(&base_iorect));
		assert(base_iorect.vr_xmin >= 0);
		assert(base_iorect.vr_ymin >= 0);
		assert((base_iorect.vr_xmin + base_iorect.vr_xdim) <= base->vb_xdim);
		assert((base_iorect.vr_ymin + base_iorect.vr_ydim) <= base->vb_ydim);

		/* Populate "ret" based on rect offsets */
		ret->rbf_cxoff = ret_crect.vr_xmin;
		ret->rbf_cyoff = ret_crect.vr_ymin;

		/* Check if we need to create a new sub-region buffer to enforce an I/O Rect */
		if (base_iorect.vr_xmin > 0 || base_iorect.vr_ymin > 0 ||
		    base_iorect.vr_xdim < base->vb_xdim ||
		    base_iorect.vr_xdim < base->vb_ydim) {
			REF struct video_buffer *used_base;
			static_assert(offsetof(struct video_rect, vr_xmin) == offsetof(struct video_crect, vcr_xmin));
			static_assert(offsetof(struct video_rect, vr_ymin) == offsetof(struct video_crect, vcr_ymin));
			static_assert(offsetof(struct video_rect, vr_xdim) == offsetof(struct video_crect, vcr_xdim));
			static_assert(offsetof(struct video_rect, vr_ydim) == offsetof(struct video_crect, vcr_ydim));
			used_base = video_buffer_subregion(base, (struct video_crect const *)&base_iorect);
			video_buffer_decref(base);
			if unlikely(!used_base)
				goto err_r;

			/* Make pixel offsets of "ret" be relative to the new sub-region */
			ret->rbf_cxoff -= base_iorect.vr_xmin;
			ret->rbf_cyoff -= base_iorect.vr_ymin;
			base = used_base;
		}

		ret->vb_ops   = _region_buffer_subregion_ops();
		ret->rbf_base = base; /* Inherit reference */
		ret->rbf_orig = ret->rbf_base;
		ret->brbsr_parent = me;
		video_buffer_incref(me);
		atomic_lock_acquire(&me->rbf_child_lock);
		LIST_INSERT_HEAD(&me->rbf_child_list, ret, brbsr_chain);
		atomic_lock_release(&me->rbf_child_lock);
	} else {
		result->vb_ops   = _region_buffer_ops();
		result->rbf_base = buffer;
		result->rbf_orig = result->rbf_base;
		video_buffer_incref(buffer);
	}

	/* Finish initializing "result" */
	__video_buffer_init_common(result);
	return result;
do_return_empty_buffer_r:
	free(result);
	/* TODO: This always returns a 0x0 buffer, but we'd  need
	 *       to return one with a custom size given by `rect' */
	return_empty_buffer;
err_r:
	free(result);
err:
	return NULL;
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_REGION_C */
