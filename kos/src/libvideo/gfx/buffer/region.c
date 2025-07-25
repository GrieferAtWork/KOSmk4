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

#include <kos/anno.h>

#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>

#include <libvideo/crect.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/surface.h>
#include <libvideo/rect.h>
#include <libvideo/types.h>

#include "../buffer.h"
#include "../gfx-empty.h"
#include "../ramdomain.h"
#include "region.h"
#include "../gfx-debug.h"

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

/* Operators for region buffers, as seen above */

/* DESTROY */
INTERN NONNULL((1)) void FCC
region_buffer__destroy(struct video_buffer *__restrict self) {
	struct region_buffer *me = (struct region_buffer *)self;
	video_buffer_decref(me->rbf_base);
	__video_buffer_fini_common(me);
	free(me);
}

/* REVOKE+SUBREGION */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC region_buffer__revoke)(struct video_buffer *__restrict self) {
	struct region_buffer *me = (struct region_buffer *)self;
	video_buffer_revoke(me->rbf_base);
	return me;
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
region_buffer__subregion(struct video_surface const *__restrict self,
                         struct video_crect const *__restrict rect) {
	struct video_rect old_rect, new_rect, result_rect, base_iorect;
	REF struct region_buffer *result;
	struct region_buffer *me = (struct region_buffer *)video_surface_getbuffer(self);
	struct video_buffer *base = me->rbf_base;
	video_buffer_assert_rect(me, rect);
	old_rect.vr_xmin = me->rbf_cxoff;
	old_rect.vr_ymin = me->rbf_cyoff;
	old_rect.vr_xdim = video_buffer_getxdim(me);
	old_rect.vr_ydim = video_buffer_getydim(me);
	if (OVERFLOW_SADD(me->rbf_cxoff, rect->vcr_xmin, &new_rect.vr_xmin))
		goto do_return_empty_buffer;
	if (OVERFLOW_SADD(me->rbf_cyoff, rect->vcr_ymin, &new_rect.vr_ymin))
		goto do_return_empty_buffer;
	new_rect.vr_xdim = rect->vcr_xdim;
	new_rect.vr_ydim = rect->vcr_ydim;
	if (!video_rect_intersect_overflow(&old_rect, &new_rect, &result_rect))
		goto do_return_empty_buffer;
	assert(!video_rect_isempty(&result_rect));
	base_iorect.vr_xmin = 0;
	base_iorect.vr_ymin = 0;
	base_iorect.vr_xdim = video_buffer_getxdim(base);
	base_iorect.vr_ydim = video_buffer_getydim(base);
	if (!video_rect_intersect_overflow(&base_iorect, &result_rect, &base_iorect))
		goto do_return_empty_buffer;

	/* Check if this whole thing has once again turned into a sub-region-only buffer. */
	if (result_rect.vr_xmin == base_iorect.vr_xmin &&
	    result_rect.vr_ymin == base_iorect.vr_ymin &&
	    result_rect.vr_xdim == base_iorect.vr_xdim &&
	    result_rect.vr_ydim == base_iorect.vr_ydim)
		return video_buffer_subregion(base, (struct video_crect const *)&base_iorect);

	/* Check if we need to use a sub-region of "base" for the  result
	 * This essentially clamps the buffer I/O Rect if it got smaller. */
	if (base_iorect.vr_xmin > 0 || base_iorect.vr_ymin > 0 ||
	    base_iorect.vr_xdim < video_buffer_getxdim(base) ||
	    base_iorect.vr_ydim < video_buffer_getydim(base)) {
		base = video_buffer_subregion(base, (struct video_crect const *)&base_iorect);
		if unlikely(!base)
			goto err;
		result_rect.vr_xmin -= base_iorect.vr_xmin;
		result_rect.vr_ymin -= base_iorect.vr_ymin;
	} else {
		video_buffer_incref(base);
	}

	/* Allocate the new sub-region */
	result = (REF struct region_buffer *)malloc(sizeof(struct region_buffer));
	if unlikely(!result)
		goto err_base;
	__video_buffer_init_subregion(result, self, me, rect);
	result->vb_ops    = _region_buffer_ops();
	result->rbf_cxoff = result_rect.vr_xmin;
	result->rbf_cyoff = result_rect.vr_ymin;
	result->rbf_base  = base; /* Inherit reference */
	__video_buffer_init_common(result);
	return result;
do_return_empty_buffer:
	/* TODO: This always returns a 0x0 buffer, but we'd  need
	 *       to return one with a custom size given by `rect' */
	return_empty_buffer;
err_base:
	video_buffer_decref(base);
err:
	return NULL;
}

/* LOCK */
INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
region_buffer__rlockregion(struct video_buffer *__restrict self,
                           struct video_regionlock *__restrict lock) {
	struct region_buffer *me = (struct region_buffer *)self;
	struct video_buffer *base = me->rbf_base;
	video_coord_t xend, yend;
	video_regionlock_assert(me, lock);

	/* Make the region-rect relative to the base buffer. */
	lock->_vrl_rect.vcr_xmin += me->rbf_cxoff;
	lock->_vrl_rect.vcr_ymin += me->rbf_cyoff;
	if (!OVERFLOW_UADD(lock->_vrl_rect.vcr_xmin, lock->_vrl_rect.vcr_xdim, &xend) &&
	    !OVERFLOW_UADD(lock->_vrl_rect.vcr_ymin, lock->_vrl_rect.vcr_ydim, &yend) &&
	    xend <= video_buffer_getxdim(base) && yend <= video_buffer_getydim(base))
		return (*base->vb_ops->vi_rlockregion)(base, lock);
	errno = ERANGE;
	return -1;
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
region_buffer__wlockregion(struct video_buffer *__restrict self,
                           struct video_regionlock *__restrict lock) {
	struct region_buffer *me = (struct region_buffer *)self;
	struct video_buffer *base = me->rbf_base;
	video_coord_t xend, yend;
	video_regionlock_assert(me, lock);

	/* Make the region-rect relative to the base buffer. */
	lock->_vrl_rect.vcr_xmin += me->rbf_cxoff;
	lock->_vrl_rect.vcr_ymin += me->rbf_cyoff;
	if (!OVERFLOW_UADD(lock->_vrl_rect.vcr_xmin, lock->_vrl_rect.vcr_xdim, &xend) &&
	    !OVERFLOW_UADD(lock->_vrl_rect.vcr_ymin, lock->_vrl_rect.vcr_ydim, &yend) &&
	    xend <= video_buffer_getxdim(base) && yend <= video_buffer_getydim(base))
		return (*base->vb_ops->vi_wlockregion)(base, lock);
	errno = ERANGE;
	return -1;
}

INTERN ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC region_buffer__unlockregion)(struct video_buffer *__restrict self,
                                         struct video_regionlock *__restrict lock) {
	struct region_buffer *me = (struct region_buffer *)self;
	struct video_buffer *base = me->rbf_base;
	(*base->vb_ops->vi_unlockregion)(base, lock);
	/* Restore original lock rect (in case of further nesting, and caller needs it) */
	lock->_vrl_rect.vcr_ymin -= me->rbf_cyoff;
	lock->_vrl_rect.vcr_xmin -= me->rbf_cxoff;
	video_regionlock_assert(me, lock);
}



/* GFX */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
region_buffer__initgfx(struct video_gfx *__restrict self) {
	struct region_buffer *me = (struct region_buffer *)video_gfx_getbuffer(self);
	self = (*(self->vx_surf.vs_buffer = me->rbf_base)->vb_ops->vi_initgfx)(self);
	return video_gfx_clip(self, me->rbf_cxoff, me->rbf_cyoff,
	                      video_buffer_getxdim(me),
	                      video_buffer_getydim(me));
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
DEFINE_PUBLIC_ALIAS(_video_surface_region, _libvideo_surface_region);
DEFINE_PUBLIC_ALIAS(_video_surface_region_distinct, _libvideo_surface_region_distinct);
INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *CC
libvideo_surface_region(struct video_surface const *__restrict self,
                        struct video_rect const *__restrict rect) {
	struct video_rect buffer_rect;
	if unlikely(video_surface_getflags(self) & VIDEO_GFX_F_XYSWAP) {
		buffer_rect.vr_xmin = rect->vr_ymin;
		buffer_rect.vr_ymin = rect->vr_xmin;
		buffer_rect.vr_xdim = rect->vr_ydim;
		buffer_rect.vr_ydim = rect->vr_xdim;
		rect = &buffer_rect;
	}
	return _libvideo_surface_region(self, rect);
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *CC
libvideo_surface_region_distinct(struct video_surface const *__restrict self,
                                 struct video_rect const *__restrict rect) {
	struct video_rect buffer_rect;
	if unlikely(video_surface_getflags(self) & VIDEO_GFX_F_XYSWAP) {
		buffer_rect.vr_xmin = rect->vr_ymin;
		buffer_rect.vr_ymin = rect->vr_xmin;
		buffer_rect.vr_xdim = rect->vr_ydim;
		buffer_rect.vr_ydim = rect->vr_xdim;
		rect = &buffer_rect;
	}
	return _libvideo_surface_region_distinct(self, rect);
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *CC
_libvideo_surface_region(struct video_surface const *__restrict self,
                         struct video_rect const *__restrict buffer_rect) {
	struct video_buffer *buffer = video_surface_getbuffer(self);

	/* Check if "self"+"rect" are just aliasing the underlying buffer */
	if (buffer_rect->vr_xmin == 0 && buffer_rect->vr_ymin == 0 &&
	    buffer_rect->vr_xdim == video_buffer_getxdim(buffer) &&
	    buffer_rect->vr_ydim == video_buffer_getydim(buffer) &&
	    video_surface_isdefault(self)) {
		video_buffer_incref(buffer);
		return buffer;
	}
	return _libvideo_surface_region_distinct(self, buffer_rect);
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *CC
_libvideo_surface_region_distinct(struct video_surface const *__restrict self,
                                  struct video_rect const *__restrict buffer_rect) {
	REF struct region_buffer *result;
	struct video_buffer *buffer = video_surface_getbuffer(self);

	/* Check for simple case: can we do this as a sub-region? */
	if (buffer_rect->vr_xmin >= 0 && buffer_rect->vr_ymin >= 0) {
		video_coord_t rect_xend, rect_yend;
		if (!OVERFLOW_UADD((video_coord_t)buffer_rect->vr_xmin, buffer_rect->vr_xdim, &rect_xend) &&
		    !OVERFLOW_UADD((video_coord_t)buffer_rect->vr_ymin, buffer_rect->vr_ydim, &rect_yend) &&
		    rect_xend <= video_buffer_getxdim(buffer) &&
		    rect_yend <= video_buffer_getydim(buffer)) {
			/* Yes! Yes, we can! */
			static_assert(offsetof(struct video_rect, vr_xmin) == offsetof(struct video_crect, vcr_xmin));
			static_assert(offsetof(struct video_rect, vr_ymin) == offsetof(struct video_crect, vcr_ymin));
			static_assert(offsetof(struct video_rect, vr_xdim) == offsetof(struct video_crect, vcr_xdim));
			static_assert(offsetof(struct video_rect, vr_ydim) == offsetof(struct video_crect, vcr_ydim));
			return _video_surface_subregion(self, (struct video_crect const *)buffer_rect);
		}
	}

	/* Allocate result buffer */
	result = (REF struct region_buffer *)malloc(sizeof(struct region_buffer));
	if unlikely(!result)
		goto err;

	/* Start filling in basic data for `result' */
	video_surface_copyattrib(&result->vb_surf, self);
	result->vb_codec  = video_buffer_getcodec(buffer);
	result->vb_domain = _libvideo_ramdomain();
	__video_buffer_init_dim(result, buffer_rect->vr_xdim, buffer_rect->vr_ydim);
	result->rbf_cxoff = buffer_rect->vr_xmin;
	result->rbf_cyoff = buffer_rect->vr_ymin;
	if (buffer->vb_ops == &region_buffer_ops) {
		struct region_buffer *me = (struct region_buffer *)self;
		struct video_buffer *base = me->rbf_base;
		struct video_rect me_crect, ret_crect, base_crect;
		struct video_rect base_iorect;

		/* Calculate intersection of 3 rects:
		 * - {{0,0},                           {video_buffer_getXYdim(base)}}
		 * - {{me->rbf_cxoff,me->rbf_cyoff},   {video_buffer_getXYdim(me)}}
		 * - {{me->rbf_cxoff+result->rbf_cxoff,me->rbf_cyoff+result->rbf_cyoff}, {video_buffer_getXYdim(result)}}
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
		base_crect.vr_xdim = video_buffer_getxdim(base);
		base_crect.vr_ydim = video_buffer_getydim(base);
		me_crect.vr_xmin   = me->rbf_cxoff;
		me_crect.vr_ymin   = me->rbf_cyoff;
		me_crect.vr_xdim   = video_buffer_getxdim(me);
		me_crect.vr_ydim   = video_buffer_getydim(me);
		ret_crect.vr_xmin  = me_crect.vr_xmin + result->rbf_cxoff;
		ret_crect.vr_ymin  = me_crect.vr_ymin + result->rbf_cyoff;
		ret_crect.vr_xdim  = video_buffer_getxdim(result);
		ret_crect.vr_ydim  = video_buffer_getydim(result);

		if (!video_rect_intersect_overflow(&me_crect, &ret_crect, &base_iorect))
			goto do_return_empty_buffer_r;
		if (!video_rect_intersect_overflow(&base_iorect, &base_crect, &base_iorect))
			goto do_return_empty_buffer_r;
		assert(!video_rect_isempty(&base_iorect));
		assert(base_iorect.vr_xmin >= 0);
		assert(base_iorect.vr_ymin >= 0);
		assert((base_iorect.vr_xmin + base_iorect.vr_xdim) <= video_buffer_getxdim(base));
		assert((base_iorect.vr_ymin + base_iorect.vr_ydim) <= video_buffer_getydim(base));

		/* Populate "result" based on rect offsets */
		result->rbf_cxoff = ret_crect.vr_xmin;
		result->rbf_cyoff = ret_crect.vr_ymin;

		/* Check if we need to create a new sub-region buffer to enforce an I/O Rect */
		if (base_iorect.vr_xmin > 0 || base_iorect.vr_ymin > 0 ||
		    base_iorect.vr_xdim < video_buffer_getxdim(base) ||
		    base_iorect.vr_xdim < video_buffer_getydim(base)) {
			REF struct video_buffer *used_base;
			static_assert(offsetof(struct video_rect, vr_xmin) == offsetof(struct video_crect, vcr_xmin));
			static_assert(offsetof(struct video_rect, vr_ymin) == offsetof(struct video_crect, vcr_ymin));
			static_assert(offsetof(struct video_rect, vr_xdim) == offsetof(struct video_crect, vcr_xdim));
			static_assert(offsetof(struct video_rect, vr_ydim) == offsetof(struct video_crect, vcr_ydim));
			used_base = video_buffer_subregion(base, (struct video_crect const *)&base_iorect);
			video_buffer_decref(base);
			if unlikely(!used_base)
				goto err_r;

			/* Make pixel offsets of "result" be relative to the new sub-region */
			result->rbf_cxoff -= base_iorect.vr_xmin;
			result->rbf_cyoff -= base_iorect.vr_ymin;
			base = used_base;
		}
	}
	result->vb_ops   = _region_buffer_ops();
	result->rbf_base = buffer;
	video_buffer_incref(buffer);

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
