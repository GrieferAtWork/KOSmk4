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
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <kos/anno.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <malloc.h>
#include <sched.h>
#include <stdbool.h>
#include <stddef.h>

#include <libvideo/codec/palette.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "../buffer.h"
#include "../gfx-empty.h"
#include "gfx.h"
#include "region.h"
#include "utils.h"

DECL_BEGIN

static_assert(offsetof(struct bigregion_buffer_r, brbr_orig) == offsetof(struct subregion_buffer_r, srbr_orig));
static_assert(offsetof(struct bigregion_buffer_r, brbr_inuse) == offsetof(struct subregion_buffer_r, srbr_inuse));
#define bigregion_buffer_r_startuse(self) atomic_inc(&(self)->brbr_inuse)
#define bigregion_buffer_r_enduse(self)   atomic_dec(&(self)->brbr_inuse)
#define subregion_buffer_r_startuse(self) atomic_inc(&(self)->srbr_inuse)
#define subregion_buffer_r_enduse(self)   atomic_dec(&(self)->srbr_inuse)


static_assert(offsetof(struct bigregion_buffer, brb_base) == offsetof(struct subregion_buffer, srb_base));
#define bigregion_buffer_destroy         subregion_buffer_destroy
#define subregion_buffer_r_destroy       bigregion_buffer_r_destroy
#define subregion_buffer_norem_r_destroy bigregion_buffer_r_destroy
#define basregion_buffer_r_destroy       bigregion_buffer_r_destroy
PRIVATE NONNULL((1)) void
NOTHROW(FCC bigregion_buffer_r_destroy)(struct video_buffer *__restrict self) {
	struct bigregion_buffer *me = (struct bigregion_buffer *)self;
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
	video_buffer_decref(me->brb_base);
	free(me);
}

#define bigregion_buffer_rlock    libvideo_buffer_notsup_rlock
#define bigregion_buffer_wlock    libvideo_buffer_notsup_wlock
#define bigregion_buffer_unlock   libvideo_buffer_noop_unlock
#define bigregion_buffer_r_rlock  libvideo_buffer_notsup_rlock
#define bigregion_buffer_r_wlock  libvideo_buffer_notsup_wlock
#define bigregion_buffer_r_unlock libvideo_buffer_noop_unlock

PRIVATE ATTR_INOUT(1) NONNULL((2)) int FCC
bigregion_buffer_rlockregion(struct video_buffer *__restrict self,
                             struct video_regionlock *__restrict lock) {
	video_coord_t xend, yend;
	struct bigregion_buffer *me = (struct bigregion_buffer *)self;
	struct video_buffer *base = me->brb_base; /* non-atomic read OK because not revokable */
	lock->_vrl_rect.vcr_xmin += me->brb_xoff;
	lock->_vrl_rect.vcr_ymin += me->brb_yoff;
	if (!OVERFLOW_UADD(lock->_vrl_rect.vcr_xmin, lock->_vrl_rect.vcr_xdim, &xend) &&
	    !OVERFLOW_UADD(lock->_vrl_rect.vcr_ymin, lock->_vrl_rect.vcr_ydim, &yend) &&
	    xend <= base->vb_xdim && yend <= base->vb_ydim)
		return (*base->vb_ops->vi_rlockregion)(base, lock);
	errno = ERANGE;
	return -1;
}

PRIVATE ATTR_INOUT(1) NONNULL((2)) int FCC
bigregion_buffer_wlockregion(struct video_buffer *__restrict self,
                             struct video_regionlock *__restrict lock) {
	video_coord_t xend, yend;
	struct bigregion_buffer *me = (struct bigregion_buffer *)self;
	struct video_buffer *base = me->brb_base; /* non-atomic read OK because not revokable */
	lock->_vrl_rect.vcr_xmin += me->brb_xoff;
	lock->_vrl_rect.vcr_ymin += me->brb_yoff;
	if (!OVERFLOW_UADD(lock->_vrl_rect.vcr_xmin, lock->_vrl_rect.vcr_xdim, &xend) &&
	    !OVERFLOW_UADD(lock->_vrl_rect.vcr_ymin, lock->_vrl_rect.vcr_ydim, &yend) &&
	    xend <= base->vb_xdim && yend <= base->vb_ydim)
		return (*base->vb_ops->vi_wlockregion)(base, lock);
	errno = ERANGE;
	return -1;
}

PRIVATE ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC bigregion_buffer_unlockregion)(struct video_buffer *__restrict self,
                                           struct video_regionlock *__restrict lock) {
	struct bigregion_buffer *me = (struct bigregion_buffer *)self;
	struct video_buffer *base = me->brb_base; /* non-atomic read OK because not revokable */
	(*base->vb_ops->vi_unlockregion)(base, lock);
	lock->_vrl_rect.vcr_ymin -= me->brb_yoff;
	lock->_vrl_rect.vcr_xmin -= me->brb_xoff;
}


PRIVATE ATTR_INOUT(1) NONNULL((2)) int FCC
bigregion_buffer_r_rlockregion(struct video_buffer *__restrict self,
                               struct video_regionlock *__restrict lock) {
	video_coord_t xend, yend;
	struct bigregion_buffer_r *me = (struct bigregion_buffer_r *)self;
	struct video_buffer *base;
	atomic_inc(&me->brbr_inuse);
	base = atomic_read(&me->brb_base);
	lock->_vrl_rect.vcr_xmin += me->brb_xoff;
	lock->_vrl_rect.vcr_ymin += me->brb_yoff;
	if (!OVERFLOW_UADD(lock->_vrl_rect.vcr_xmin, lock->_vrl_rect.vcr_xdim, &xend) &&
	    !OVERFLOW_UADD(lock->_vrl_rect.vcr_ymin, lock->_vrl_rect.vcr_ydim, &yend) &&
	    xend <= base->vb_xdim && yend <= base->vb_ydim) {
		int result;
		result = (*base->vb_ops->vi_rlockregion)(base, lock);
		if unlikely(result)
			atomic_dec(&me->brbr_inuse);
		return result;
	}
	atomic_dec(&me->brbr_inuse);
	errno = ERANGE;
	return -1;
}

PRIVATE ATTR_INOUT(1) NONNULL((2)) int FCC
bigregion_buffer_r_wlockregion(struct video_buffer *__restrict self,
                               struct video_regionlock *__restrict lock) {
	video_coord_t xend, yend;
	struct bigregion_buffer_r *me = (struct bigregion_buffer_r *)self;
	struct video_buffer *base;
	atomic_inc(&me->brbr_inuse);
	base = atomic_read(&me->brb_base);
	lock->_vrl_rect.vcr_xmin += me->brb_xoff;
	lock->_vrl_rect.vcr_ymin += me->brb_yoff;
	if (!OVERFLOW_UADD(lock->_vrl_rect.vcr_xmin, lock->_vrl_rect.vcr_xdim, &xend) &&
	    !OVERFLOW_UADD(lock->_vrl_rect.vcr_ymin, lock->_vrl_rect.vcr_ydim, &yend) &&
	    xend <= base->vb_xdim && yend <= base->vb_ydim) {
		int result;
		result = (*base->vb_ops->vi_wlockregion)(base, lock);
		if unlikely(result)
			atomic_dec(&me->brbr_inuse);
		return result;
	}
	atomic_dec(&me->brbr_inuse);
	errno = ERANGE;
	return -1;
}

PRIVATE ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC bigregion_buffer_r_unlockregion)(struct video_buffer *__restrict self,
                                             struct video_regionlock *__restrict lock) {
	/* During revoke, `libvideo_emptybuffer' is assigned as buffer, whose  lock
	 * operations always fail. As such, the only way to get here is if the lock
	 * was created by the **ORIGINAL** video buffer. */
	struct bigregion_buffer_r *me = (struct bigregion_buffer_r *)self;
	struct video_buffer *base     = me->brbr_orig;
	(*base->vb_ops->vi_unlockregion)(base, lock);
	atomic_dec(&me->brbr_inuse);
	lock->_vrl_rect.vcr_ymin -= me->brb_yoff;
	lock->_vrl_rect.vcr_xmin -= me->brb_xoff;
}


#define subregion_buffer_r_rlock  libvideo_buffer_notsup_rlock
#define subregion_buffer_r_wlock  libvideo_buffer_notsup_wlock
#define subregion_buffer_r_unlock libvideo_buffer_noop_unlock

PRIVATE ATTR_INOUT(1) ATTR_OUT(2) int FCC
subregion_buffer_norem_r_rlock(struct video_buffer *__restrict self,
                               struct video_lock *__restrict lock) {
	int ok;
	struct subregion_buffer_r *me = (struct subregion_buffer_r *)self;
	struct video_buffer *base;
	subregion_buffer_r_startuse(me);
	base = atomic_read(&me->srb_base);
	ok = (*base->vb_ops->vi_rlock)(base, lock);
	if unlikely(ok) {
		subregion_buffer_r_enduse(me);
		return ok;
	}
	lock->vl_data += me->srb_yoff * lock->vl_stride;
	lock->vl_data += me->srb_vm_xoff;
	return ok;
}

PRIVATE ATTR_INOUT(1) ATTR_OUT(2) int FCC
subregion_buffer_norem_r_wlock(struct video_buffer *__restrict self,
                               struct video_lock *__restrict lock) {
	int ok;
	struct subregion_buffer_r *me = (struct subregion_buffer_r *)self;
	struct video_buffer *base;
	subregion_buffer_r_startuse(me);
	base = atomic_read(&me->srb_base);
	ok = (*base->vb_ops->vi_wlock)(base, lock);
	if unlikely(ok) {
		subregion_buffer_r_enduse(me);
		return ok;
	}
	lock->vl_data += me->srb_yoff * lock->vl_stride;
	lock->vl_data += me->srb_vm_xoff;
	return ok;
}

PRIVATE ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC subregion_buffer_norem_r_unlock)(struct video_buffer *__restrict self,
                                             struct video_lock *__restrict lock) {
	/* During revoke, `libvideo_emptybuffer' is assigned as buffer, whose  lock
	 * operations always fail. As such, the only way to get here is if the lock
	 * was created by the **ORIGINAL** video buffer. */
	struct subregion_buffer_r *me = (struct subregion_buffer_r *)self;
	struct video_buffer *base = me->srbr_orig;
	lock->vl_data -= me->srb_vm_xoff;
	lock->vl_data -= me->srb_yoff * lock->vl_stride;
	(*base->vb_ops->vi_unlock)(base, lock);
	subregion_buffer_r_enduse(me);
}

#define subregion_buffer_norem_r_rlockregion  subregion_buffer_r_rlockregion
#define subregion_buffer_norem_r_wlockregion  subregion_buffer_r_wlockregion
#define subregion_buffer_norem_r_unlockregion subregion_buffer_r_unlockregion

PRIVATE ATTR_INOUT(1) NONNULL((2)) int FCC
subregion_buffer_r_rlockregion(struct video_buffer *__restrict self,
                               struct video_regionlock *__restrict lock) {
	int result;
	struct subregion_buffer_r *me = (struct subregion_buffer_r *)self;
	struct video_buffer *base;
	lock->_vrl_rect.vcr_xmin += me->srb_xoff;
	lock->_vrl_rect.vcr_ymin += me->srb_yoff;
	subregion_buffer_r_startuse(me);
	base = atomic_read(&me->srb_base);
	result = (*base->vb_ops->vi_rlockregion)(base, lock);
	if unlikely(result)
		subregion_buffer_r_enduse(me);
	return result;
}

PRIVATE ATTR_INOUT(1) NONNULL((2)) int FCC
subregion_buffer_r_wlockregion(struct video_buffer *__restrict self,
                               struct video_regionlock *__restrict lock) {
	int result;
	struct subregion_buffer_r *me = (struct subregion_buffer_r *)self;
	struct video_buffer *base;
	lock->_vrl_rect.vcr_xmin += me->srb_xoff;
	lock->_vrl_rect.vcr_ymin += me->srb_yoff;
	subregion_buffer_r_startuse(me);
	base = atomic_read(&me->srb_base);
	result = (*base->vb_ops->vi_wlockregion)(base, lock);
	if unlikely(result)
		subregion_buffer_r_enduse(me);
	return result;
}

PRIVATE ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC subregion_buffer_r_unlockregion)(struct video_buffer *__restrict self,
                                             struct video_regionlock *__restrict lock) {
	/* During revoke, `libvideo_emptybuffer' is assigned as buffer, whose  lock
	 * operations always fail. As such, the only way to get here is if the lock
	 * was created by the **ORIGINAL** video buffer. */
	struct subregion_buffer_r *me = (struct subregion_buffer_r *)self;
	struct video_buffer *base     = me->srbr_orig;
	(*base->vb_ops->vi_unlockregion)(base, lock);
	subregion_buffer_r_enduse(me);
	lock->_vrl_rect.vcr_ymin -= me->srb_yoff;
	lock->_vrl_rect.vcr_xmin -= me->srb_xoff;
}



PRIVATE ATTR_INOUT(1) ATTR_OUT(2) int FCC
basregion_buffer_r_rlock(struct video_buffer *__restrict self,
                         struct video_lock *__restrict lock) {
	int ok;
	struct subregion_buffer_r *me = (struct subregion_buffer_r *)self;
	struct video_buffer *base;
	subregion_buffer_r_startuse(me);
	base = atomic_read(&me->srb_base);
	ok = (*base->vb_ops->vi_rlock)(base, lock);
	if unlikely(ok)
		subregion_buffer_r_enduse(me);
	return ok;
}

PRIVATE ATTR_INOUT(1) ATTR_OUT(2) int FCC
basregion_buffer_r_wlock(struct video_buffer *__restrict self,
                         struct video_lock *__restrict lock) {
	int ok;
	struct subregion_buffer_r *me = (struct subregion_buffer_r *)self;
	struct video_buffer *base;
	subregion_buffer_r_startuse(me);
	base = atomic_read(&me->srb_base);
	ok = (*base->vb_ops->vi_wlock)(base, lock);
	if unlikely(ok)
		subregion_buffer_r_enduse(me);
	return ok;
}

PRIVATE ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC basregion_buffer_r_unlock)(struct video_buffer *__restrict self,
                                       struct video_lock *__restrict lock) {
	/* During revoke, `libvideo_emptybuffer' is assigned as buffer, whose  lock
	 * operations always fail. As such, the only way to get here is if the lock
	 * was created by the **ORIGINAL** video buffer. */
	struct subregion_buffer_r *me = (struct subregion_buffer_r *)self;
	struct video_buffer *base = me->srbr_orig;
	(*base->vb_ops->vi_unlock)(base, lock);
	subregion_buffer_r_enduse(me);
}

PRIVATE ATTR_INOUT(1) NONNULL((2)) int FCC
basregion_buffer_r_rlockregion(struct video_buffer *__restrict self,
                               struct video_regionlock *__restrict lock) {
	int result;
	struct subregion_buffer_r *me = (struct subregion_buffer_r *)self;
	struct video_buffer *base;
	subregion_buffer_r_startuse(me);
	base = atomic_read(&me->srb_base);
	result = (*base->vb_ops->vi_rlockregion)(base, lock);
	if unlikely(result)
		subregion_buffer_r_enduse(me);
	return result;
}

PRIVATE ATTR_INOUT(1) NONNULL((2)) int FCC
basregion_buffer_r_wlockregion(struct video_buffer *__restrict self,
                               struct video_regionlock *__restrict lock) {
	int result;
	struct subregion_buffer_r *me = (struct subregion_buffer_r *)self;
	struct video_buffer *base;
	subregion_buffer_r_startuse(me);
	base = atomic_read(&me->srb_base);
	result = (*base->vb_ops->vi_wlockregion)(base, lock);
	if unlikely(result)
		subregion_buffer_r_enduse(me);
	return result;
}

PRIVATE ATTR_INOUT(1) ATTR_IN(2) void
NOTHROW(FCC basregion_buffer_r_unlockregion)(struct video_buffer *__restrict self,
                                             struct video_regionlock *__restrict lock) {
	/* During revoke, `libvideo_emptybuffer' is assigned as buffer, whose  lock
	 * operations always fail. As such, the only way to get here is if the lock
	 * was created by the **ORIGINAL** video buffer. */
	struct subregion_buffer_r *me = (struct subregion_buffer_r *)self;
	struct video_buffer *base     = me->srbr_orig;
	(*base->vb_ops->vi_unlockregion)(base, lock);
	subregion_buffer_r_enduse(me);
}


static_assert(offsetof(struct bigregion_buffer, brb_base) == offsetof(struct subregion_buffer, srb_base));
static_assert(sizeof_field(struct bigregion_buffer, brb_base) == sizeof_field(struct subregion_buffer, srb_base));
static_assert(offsetof(struct bigregion_buffer, brb_xoff) == offsetof(struct subregion_buffer, srb_xoff));
static_assert(sizeof_field(struct bigregion_buffer, brb_xoff) == sizeof_field(struct subregion_buffer, srb_xoff));
static_assert(offsetof(struct bigregion_buffer, brb_yoff) == offsetof(struct subregion_buffer, srb_yoff));
static_assert(sizeof_field(struct bigregion_buffer, brb_yoff) == sizeof_field(struct subregion_buffer, srb_yoff));
#define bigregion_buffer_initgfx   subregion_buffer_initgfx
#define bigregion_buffer_updategfx subregion_buffer_updategfx


#define REGION_GFX_SUBOPS      (_VIDEO_GFX_N_DRIVER - 1)
#define REGION_BLITTER_SUBOPS  (_VIDEO_BLITTER_N_DRIVER - 1)
#define REGION_BLITTER3_SUBOPS (_VIDEO_BLITTER3_N_DRIVER - 1)

INTERN struct video_blitter_ops region_blitter_ops_subgfx = {}; /* Creates a temporary sub-gfx during every call */
INTERN struct video_blitter_ops region_blitter_ops_subops = {}; /* Original operators are stored in `_vbt_driver[REGION_BLITTER_SUBOPS]' (which was "NULL" before) */
INTERN struct video_blitter3_ops region_blitter3_ops_subgfx = {}; /* Creates a temporary sub-gfx during every call */
INTERN struct video_blitter3_ops region_blitter3_ops_subops = {}; /* Original operators are stored in `_vbt3_driver[REGION_BLITTER3_SUBOPS]' (which was "NULL" before) */

INTERN struct video_gfx_ops region_gfx_ops_subgfx = {}; /* Creates a temporary sub-gfx during every call */
INTERN struct video_gfx_ops region_gfx_ops_subops = {}; /* Original operators are stored in `_vx_driver[REGION_GFX_SUBOPS]' (which was "NULL" before) */

PRIVATE ATTR_RETNONNULL WUNUSED struct video_blitter_ops *CC _region_blitter_ops_subgfx(void);
PRIVATE ATTR_RETNONNULL WUNUSED struct video_blitter_ops *CC _region_blitter_ops_subops(void);
PRIVATE ATTR_RETNONNULL WUNUSED struct video_blitter3_ops *CC _region_blitter3_ops_subgfx(void);
PRIVATE ATTR_RETNONNULL WUNUSED struct video_blitter3_ops *CC _region_blitter3_ops_subops(void);
PRIVATE ATTR_RETNONNULL WUNUSED struct video_gfx_ops *CC _region_gfx_ops_subgfx(void);
PRIVATE ATTR_RETNONNULL WUNUSED struct video_gfx_ops *CC _region_gfx_ops_subops(void);

#define SUBGFX_BEGIN(subgfx_name, self)                                                 \
	struct video_gfx subgfx_name;                                                       \
	struct bigregion_buffer_r *_sg_me = (struct bigregion_buffer_r *)(self)->vx_buffer; \
	struct video_buffer *base;                                                          \
	atomic_inc(&_sg_me->brbr_inuse);                                                    \
	base = atomic_read(&_sg_me->brb_base);                                              \
	video_buffer_getgfx(base, &subgfx_name,                                             \
	                    (self)->vx_blend,                                               \
	                    (self)->vx_flags,                                               \
	                    (self)->vx_colorkey);                                           \
	/* Load I/O and Clip Rects of our own GFX into the underlying GFX */                \
	video_gfx_clip(&subgfx_name,                                                        \
	               (self)->vx_hdr.vxh_bxmin - subgfx_name.vx_hdr.vxh_cxoff,             \
	               (self)->vx_hdr.vxh_bymin - subgfx_name.vx_hdr.vxh_cyoff,             \
	               (self)->vx_hdr.vxh_bxend - (self)->vx_hdr.vxh_bxmin,                 \
	               (self)->vx_hdr.vxh_byend - (self)->vx_hdr.vxh_bymin);                \
	video_gfx_clip(&subgfx_name,                                                        \
	               (self)->vx_hdr.vxh_cxoff - (self)->vx_hdr.vxh_bxmin,                 \
	               (self)->vx_hdr.vxh_cyoff - (self)->vx_hdr.vxh_bymin,                 \
	               (self)->vx_hdr.vxh_cxsiz,                                            \
	               (self)->vx_hdr.vxh_cysiz)
#define SUBGFX_END() \
	atomic_dec(&_sg_me->brbr_inuse)
#define SUBOPS_BEGIN(self)                                                                            \
	struct video_gfx *_mygfx = (struct video_gfx *)(self);                                            \
	struct video_buffer *_so_base;                                                                    \
	struct bigregion_buffer_r *_so_me = (struct bigregion_buffer_r *)_mygfx->vx_buffer;               \
	assert(_mygfx->vx_hdr.vxh_ops == &region_gfx_ops_subops);                                         \
	atomic_inc(&_so_me->brbr_inuse);                                                                  \
	_so_base = atomic_read(&_so_me->brb_base);                                                        \
	if likely(_so_base == _so_me->brbr_orig) {                                                        \
		_mygfx->vx_hdr.vxh_ops = (struct video_gfx_ops const *)_mygfx->_vx_driver[REGION_GFX_SUBOPS]; \
		_mygfx->_vx_driver[REGION_GFX_SUBOPS] = NULL;                                                 \
		_mygfx->vx_buffer = _so_base
#define SUBOPS_END()                                                            \
		assert(_mygfx->vx_buffer == _so_base);                                  \
		assert(_mygfx->_vx_driver[REGION_GFX_SUBOPS] == NULL);                  \
		_mygfx->_vx_driver[REGION_GFX_SUBOPS] = (void *)_mygfx->vx_hdr.vxh_ops; \
		_mygfx->vx_hdr.vxh_ops = &region_gfx_ops_subops;                        \
		_mygfx->vx_buffer = _so_me;                                             \
	} else {                                                                    \
		_mygfx->vx_hdr.vxh_ops = &libvideo_emptygfx_ops;                        \
	}                                                                           \
	atomic_dec(&_so_me->brbr_inuse)

PRIVATE ATTR_RETNONNULL ATTR_INOUT_T(1) struct video_blitter *FCC
region_gfx_ops_subgfx_blitfrom(struct video_blitter *__restrict ctx) {
	ctx->vbt_ops = _region_blitter_ops_subgfx();
	return ctx;
}

PRIVATE ATTR_RETNONNULL ATTR_INOUT_T(1) struct video_blitter *FCC
region_gfx_ops_subops_blitfrom(struct video_blitter *__restrict ctx) {
	SUBOPS_BEGIN(ctx->vbt_dst);
	ctx->_vbt_driver[REGION_BLITTER_SUBOPS] = NULL;
	ctx = (*ctx->vbt_dst->vx_hdr.vxh_ops->vgfo_blitfrom)(ctx);
	if likely(ctx->_vbt_driver[REGION_BLITTER_SUBOPS] == NULL) {
		ctx->_vbt_driver[REGION_BLITTER_SUBOPS] = (void *)ctx->vbt_ops;
		ctx->vbt_ops = _region_blitter_ops_subops();
	} else {
		ctx->vbt_ops = _region_blitter_ops_subgfx();
	}
	SUBOPS_END();
	return ctx;
}

PRIVATE ATTR_RETNONNULL ATTR_INOUT_T(1) struct video_blitter3 *FCC
region_gfx_ops_subgfx_blitfrom3(struct video_blitter3 *__restrict ctx) {
	ctx->vbt3_ops = _region_blitter3_ops_subgfx();
	return ctx;
}

PRIVATE ATTR_RETNONNULL ATTR_INOUT_T(1) struct video_blitter3 *FCC
region_gfx_ops_subops_blitfrom3(struct video_blitter3 *__restrict ctx) {
	SUBOPS_BEGIN(ctx->vbt3_wrdst);
	ctx->_vbt3_driver[REGION_BLITTER3_SUBOPS] = NULL;
	ctx = (*ctx->vbt3_wrdst->vx_hdr.vxh_ops->vgfo_blitfrom3)(ctx);
	if likely(ctx->_vbt3_driver[REGION_BLITTER3_SUBOPS] == NULL) {
		ctx->_vbt3_driver[REGION_BLITTER3_SUBOPS] = (void *)ctx->vbt3_ops;
		ctx->vbt3_ops = _region_blitter3_ops_subops();
	} else {
		ctx->vbt3_ops = _region_blitter3_ops_subgfx();
	}
	SUBOPS_END();
	return ctx;
}

#define region_gfx_ops_subgfx_clip libvideo_gfx_clip__generic

PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *CC
region_gfx_ops_subops_clip(struct video_gfx *__restrict self,
                           video_offset_t clip_x, video_offset_t clip_y,
                           video_dim_t size_x, video_dim_t size_y) {
	SUBOPS_BEGIN(self);
	self = _mygfx = (*self->vx_hdr.vxh_ops->vgfo_clip)(self, clip_x, clip_y, size_x, size_y);
	SUBOPS_END();
	return self;
}

#define region_gfx_ops_subgfx_offset2coord libvideo_gfx_offset2coord__generic
#define region_gfx_ops_subops_offset2coord libvideo_gfx_offset2coord__generic
#define region_gfx_ops_subgfx_coord2offset libvideo_gfx_coord2offset__generic
#define region_gfx_ops_subops_coord2offset libvideo_gfx_coord2offset__generic

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC
region_gfx_ops_subgfx_getcolor(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y) {
	video_color_t result;
	SUBGFX_BEGIN(subgfx, self);
	result = (*subgfx.vx_hdr.vxh_ops->vgfo_getcolor)(&subgfx, x, y);
	SUBGFX_END();
	return result;
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subgfx_putcolor(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y,
                               video_color_t color) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_putcolor)(&subgfx, x, y, color);
	SUBGFX_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subgfx_line(struct video_gfx const *__restrict self,
                           video_offset_t x1, video_offset_t y1,
                           video_offset_t x2, video_offset_t y2,
                           video_color_t color) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_line)(&subgfx, x1, y1, x2, y2, color);
	SUBGFX_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subgfx_hline(struct video_gfx const *__restrict self,
                            video_offset_t x, video_offset_t y,
                            video_dim_t length, video_color_t color) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_hline)(&subgfx, x, y, length, color);
	SUBGFX_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subgfx_vline(struct video_gfx const *__restrict self,
                            video_offset_t x, video_offset_t y,
                            video_dim_t length, video_color_t color) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_vline)(&subgfx, x, y, length, color);
	SUBGFX_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subgfx_fill(struct video_gfx const *__restrict self,
                           video_offset_t x, video_offset_t y,
                           video_dim_t size_x, video_dim_t size_y,
                           video_color_t color) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_fill)(&subgfx, x, y, size_x, size_y, color);
	SUBGFX_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subgfx_rect(struct video_gfx const *__restrict self,
                           video_offset_t x, video_offset_t y,
                           video_dim_t size_x, video_dim_t size_y,
                           video_color_t color) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_rect)(&subgfx, x, y, size_x, size_y, color);
	SUBGFX_END();
}

PRIVATE ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC
region_gfx_ops_subgfx_fillmask(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y,
                               video_dim_t size_x, video_dim_t size_y,
                               video_color_t const bg_fg_colors[2],
                               struct video_bitmask const *__restrict bm) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_fillmask)(&subgfx, x, y, size_x, size_y, bg_fg_colors, bm);
	SUBGFX_END();
}

PRIVATE ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
region_gfx_ops_subgfx_fillstretchmask(struct video_gfx const *__restrict self,
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

PRIVATE ATTR_IN(1) ATTR_IN(6) void CC
region_gfx_ops_subgfx_gradient(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y,
                               video_dim_t size_x, video_dim_t size_y,
                               video_color_t const colors[2][2]) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_gradient)(&subgfx, x, y, size_x, size_y, colors);
	SUBGFX_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subgfx_hgradient(struct video_gfx const *__restrict self,
                                video_offset_t x, video_offset_t y,
                                video_dim_t size_x, video_dim_t size_y,
                                video_color_t locolor, video_color_t hicolor) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_hgradient)(&subgfx, x, y, size_x, size_y, locolor, hicolor);
	SUBGFX_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subgfx_vgradient(struct video_gfx const *__restrict self,
                                video_offset_t x, video_offset_t y,
                                video_dim_t size_x, video_dim_t size_y,
                                video_color_t locolor, video_color_t hicolor) {
	SUBGFX_BEGIN(subgfx, self);
	(*subgfx.vx_hdr.vxh_ops->vgfo_vgradient)(&subgfx, x, y, size_x, size_y, locolor, hicolor);
	SUBGFX_END();
}

PRIVATE ATTR_IN(1) ATTR_IN(4) void CC
region_gfx_ops_subgfx_bitblit(struct video_gfx const *dst,
                              video_offset_t dst_x, video_offset_t dst_y,
                              struct video_gfx const *src,
                              video_offset_t src_x, video_offset_t src_y,
                              video_dim_t size_x, video_dim_t size_y) {
	SUBGFX_BEGIN(subgfx, dst);
	(*subgfx.vx_hdr.vxh_ops->vgfo_bitblit)(&subgfx, dst_x, dst_y, src, src_x, src_y, size_x, size_y);
	SUBGFX_END();
}

PRIVATE ATTR_IN(1) ATTR_IN(6) void CC
region_gfx_ops_subgfx_stretch(struct video_gfx const *dst,
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

PRIVATE ATTR_IN(1) ATTR_IN(4) ATTR_IN(7) void CC
region_gfx_ops_subgfx_bitblit3(struct video_gfx const *wrdst,
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

PRIVATE ATTR_IN(1) ATTR_IN(4) ATTR_IN(9) void CC
region_gfx_ops_subgfx_stretch3(struct video_gfx const *wrdst,
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



PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC
region_gfx_ops_subops_getcolor(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y) {
	video_color_t result;
	SUBOPS_BEGIN(self);
	result = (*self->vx_hdr.vxh_ops->vgfo_getcolor)(self, x, y);
	SUBOPS_END();
	return result;
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subops_putcolor(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y,
                               video_color_t color) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_putcolor)(self, x, y, color);
	SUBOPS_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subops_line(struct video_gfx const *__restrict self,
                           video_offset_t x1, video_offset_t y1,
                           video_offset_t x2, video_offset_t y2,
                           video_color_t color) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_line)(self, x1, y1, x2, y2, color);
	SUBOPS_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subops_hline(struct video_gfx const *__restrict self,
                            video_offset_t x, video_offset_t y,
                            video_dim_t length, video_color_t color) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_hline)(self, x, y, length, color);
	SUBOPS_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subops_vline(struct video_gfx const *__restrict self,
                            video_offset_t x, video_offset_t y,
                            video_dim_t length, video_color_t color) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_vline)(self, x, y, length, color);
	SUBOPS_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subops_fill(struct video_gfx const *__restrict self,
                           video_offset_t x, video_offset_t y,
                           video_dim_t size_x, video_dim_t size_y,
                           video_color_t color) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_fill)(self, x, y, size_x, size_y, color);
	SUBOPS_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subops_rect(struct video_gfx const *__restrict self,
                           video_offset_t x, video_offset_t y,
                           video_dim_t size_x, video_dim_t size_y,
                           video_color_t color) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_rect)(self, x, y, size_x, size_y, color);
	SUBOPS_END();
}

PRIVATE ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC
region_gfx_ops_subops_fillmask(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y,
                               video_dim_t size_x, video_dim_t size_y,
                               video_color_t const bg_fg_colors[2],
                               struct video_bitmask const *__restrict bm) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_fillmask)(self, x, y, size_x, size_y, bg_fg_colors, bm);
	SUBOPS_END();
}

PRIVATE ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC
region_gfx_ops_subops_fillstretchmask(struct video_gfx const *__restrict self,
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

PRIVATE ATTR_IN(1) ATTR_IN(6) void CC
region_gfx_ops_subops_gradient(struct video_gfx const *__restrict self,
                               video_offset_t x, video_offset_t y,
                               video_dim_t size_x, video_dim_t size_y,
                               video_color_t const colors[2][2]) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_gradient)(self, x, y, size_x, size_y, colors);
	SUBOPS_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subops_hgradient(struct video_gfx const *__restrict self,
                                video_offset_t x, video_offset_t y,
                                video_dim_t size_x, video_dim_t size_y,
                                video_color_t locolor, video_color_t hicolor) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_hgradient)(self, x, y, size_x, size_y, locolor, hicolor);
	SUBOPS_END();
}

PRIVATE ATTR_IN(1) void CC
region_gfx_ops_subops_vgradient(struct video_gfx const *__restrict self,
                                video_offset_t x, video_offset_t y,
                                video_dim_t size_x, video_dim_t size_y,
                                video_color_t locolor, video_color_t hicolor) {
	SUBOPS_BEGIN(self);
	(*self->vx_hdr.vxh_ops->vgfo_vgradient)(self, x, y, size_x, size_y, locolor, hicolor);
	SUBOPS_END();
}

PRIVATE ATTR_IN(1) ATTR_IN(4) void CC
region_gfx_ops_subops_bitblit(struct video_gfx const *dst,
                              video_offset_t dst_x, video_offset_t dst_y,
                              struct video_gfx const *src,
                              video_offset_t src_x, video_offset_t src_y,
                              video_dim_t size_x, video_dim_t size_y) {
	SUBOPS_BEGIN(dst);
	(*dst->vx_hdr.vxh_ops->vgfo_bitblit)(dst, dst_x, dst_y, src, src_x, src_y, size_x, size_y);
	SUBOPS_END();
}

PRIVATE ATTR_IN(1) ATTR_IN(6) void CC
region_gfx_ops_subops_stretch(struct video_gfx const *dst,
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

PRIVATE ATTR_IN(1) ATTR_IN(4) ATTR_IN(7) void CC
region_gfx_ops_subops_bitblit3(struct video_gfx const *wrdst,
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

PRIVATE ATTR_IN(1) ATTR_IN(4) ATTR_IN(9) void CC
region_gfx_ops_subops_stretch3(struct video_gfx const *wrdst,
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


PRIVATE ATTR_IN_T(1) void CC
region_blitter_subgfx_bitblit(struct video_blitter const *__restrict self,
                              video_offset_t dst_x, video_offset_t dst_y,
                              video_offset_t src_x, video_offset_t src_y,
                              video_dim_t size_x, video_dim_t size_y) {
	SUBGFX_BEGIN(subgfx, self->vbt_dst);
	(*subgfx.vx_hdr.vxh_ops->vgfo_bitblit)(&subgfx, dst_x, dst_y,
	                                       self->vbt_src, src_x, src_y,
	                                       size_x, size_y);
	SUBGFX_END();
}

PRIVATE ATTR_IN_T(1) void CC
region_blitter_subgfx_stretch(struct video_blitter const *__restrict self,
                              video_offset_t dst_x, video_offset_t dst_y,
                              video_dim_t dst_size_x, video_dim_t dst_size_y,
                              video_offset_t src_x, video_offset_t src_y,
                              video_dim_t src_size_x, video_dim_t src_size_y) {
	SUBGFX_BEGIN(subgfx, self->vbt_dst);
	(*subgfx.vx_hdr.vxh_ops->vgfo_stretch)(&subgfx, dst_x, dst_y, dst_size_x, dst_size_y,
	                                       self->vbt_src, src_x, src_y, src_size_x, src_size_y);
	SUBGFX_END();
}

PRIVATE ATTR_IN_T(1) void CC
region_blitter3_subgfx_bitblit(struct video_blitter3 const *__restrict self,
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

PRIVATE ATTR_IN_T(1) void CC
region_blitter3_subgfx_stretch(struct video_blitter3 const *__restrict self,
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
	assert(_sb_me->vbt_ops == &region_blitter_ops_subops);                                          \
	_sb_me->vbt_ops = (struct video_blitter_ops const *)_sb_me->_vbt_driver[REGION_BLITTER_SUBOPS]; \
	_sb_me->_vbt_driver[REGION_BLITTER_SUBOPS] = NULL
#define SUBBLIT_END()                                                     \
	assert(_sb_me->_vbt_driver[REGION_BLITTER_SUBOPS] == NULL);           \
	_sb_me->_vbt_driver[REGION_BLITTER_SUBOPS] = (void *)_sb_me->vbt_ops; \
	_sb_me->vbt_ops = &region_blitter_ops_subops

#define SUBBLIT3_BEGIN(self)                                                                              \
	struct video_blitter3 *_sb3_me = (self);                                                              \
	assert(_sb3_me->vbt3_ops == &region_blitter3_ops_subops);                                             \
	_sb3_me->vbt3_ops = (struct video_blitter3_ops const *)_sb3_me->_vbt3_driver[REGION_BLITTER3_SUBOPS]; \
	_sb3_me->_vbt3_driver[REGION_BLITTER3_SUBOPS] = NULL
#define SUBBLIT3_END()                                                         \
	assert(_sb3_me->_vbt3_driver[REGION_BLITTER3_SUBOPS] == NULL);             \
	_sb3_me->_vbt3_driver[REGION_BLITTER3_SUBOPS] = (void *)_sb3_me->vbt3_ops; \
	_sb3_me->vbt3_ops = &region_blitter3_ops_subops


PRIVATE ATTR_IN_T(1) void CC
region_blitter_subops_bitblit(struct video_blitter const *__restrict self,
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

PRIVATE ATTR_IN_T(1) void CC
region_blitter_subops_stretch(struct video_blitter const *__restrict self,
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


PRIVATE ATTR_IN_T(1) void CC
region_blitter3_subops_bitblit(struct video_blitter3 const *__restrict self,
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

PRIVATE ATTR_IN_T(1) void CC
region_blitter3_subops_stretch(struct video_blitter3 const *__restrict self,
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





PRIVATE ATTR_RETNONNULL WUNUSED struct video_blitter_ops *CC
_region_blitter_ops_subgfx(void) {
	if (!region_blitter_ops_subgfx.vbto_bitblit) {
		region_blitter_ops_subgfx.vbto_stretch = &region_blitter_subgfx_stretch;
		COMPILER_WRITE_BARRIER();
		region_blitter_ops_subgfx.vbto_bitblit = &region_blitter_subgfx_bitblit;
		COMPILER_WRITE_BARRIER();
	}
	return &region_blitter_ops_subgfx;
}

PRIVATE ATTR_RETNONNULL WUNUSED struct video_blitter_ops *CC
_region_blitter_ops_subops(void) {
	if (!region_blitter_ops_subops.vbto_bitblit) {
		region_blitter_ops_subops.vbto_stretch = &region_blitter_subops_stretch;
		COMPILER_WRITE_BARRIER();
		region_blitter_ops_subops.vbto_bitblit = &region_blitter_subops_bitblit;
		COMPILER_WRITE_BARRIER();
	}
	return &region_blitter_ops_subops;
}

PRIVATE ATTR_RETNONNULL WUNUSED struct video_blitter3_ops *CC
_region_blitter3_ops_subgfx(void) {
	if (!region_blitter3_ops_subgfx.vbt3o_bitblit) {
		region_blitter3_ops_subgfx.vbt3o_stretch = &region_blitter3_subgfx_stretch;
		COMPILER_WRITE_BARRIER();
		region_blitter3_ops_subgfx.vbt3o_bitblit = &region_blitter3_subgfx_bitblit;
		COMPILER_WRITE_BARRIER();
	}
	return &region_blitter3_ops_subgfx;
}

PRIVATE ATTR_RETNONNULL WUNUSED struct video_blitter3_ops *CC
_region_blitter3_ops_subops(void) {
	if (!region_blitter3_ops_subops.vbt3o_bitblit) {
		region_blitter3_ops_subops.vbt3o_stretch = &region_blitter3_subops_stretch;
		COMPILER_WRITE_BARRIER();
		region_blitter3_ops_subops.vbt3o_bitblit = &region_blitter3_subops_bitblit;
		COMPILER_WRITE_BARRIER();
	}
	return &region_blitter3_ops_subops;
}


PRIVATE ATTR_RETNONNULL WUNUSED struct video_gfx_ops *CC
_region_gfx_ops_subgfx(void) {
	if (!region_gfx_ops_subgfx.vgfo_blitfrom) {
		region_gfx_ops_subgfx.vgfo_blitfrom3       = &region_gfx_ops_subgfx_blitfrom3;
		region_gfx_ops_subgfx.vgfo_clip            = &region_gfx_ops_subgfx_clip;
		region_gfx_ops_subgfx.vgfo_offset2coord    = &region_gfx_ops_subgfx_offset2coord;
		region_gfx_ops_subgfx.vgfo_coord2offset    = &region_gfx_ops_subgfx_coord2offset;
		region_gfx_ops_subgfx.vgfo_getcolor        = &region_gfx_ops_subgfx_getcolor;
		region_gfx_ops_subgfx.vgfo_putcolor        = &region_gfx_ops_subgfx_putcolor;
		region_gfx_ops_subgfx.vgfo_line            = &region_gfx_ops_subgfx_line;
		region_gfx_ops_subgfx.vgfo_hline           = &region_gfx_ops_subgfx_hline;
		region_gfx_ops_subgfx.vgfo_vline           = &region_gfx_ops_subgfx_vline;
		region_gfx_ops_subgfx.vgfo_fill            = &region_gfx_ops_subgfx_fill;
		region_gfx_ops_subgfx.vgfo_rect            = &region_gfx_ops_subgfx_rect;
		region_gfx_ops_subgfx.vgfo_fillmask        = &region_gfx_ops_subgfx_fillmask;
		region_gfx_ops_subgfx.vgfo_fillstretchmask = &region_gfx_ops_subgfx_fillstretchmask;
		region_gfx_ops_subgfx.vgfo_gradient        = &region_gfx_ops_subgfx_gradient;
		region_gfx_ops_subgfx.vgfo_hgradient       = &region_gfx_ops_subgfx_hgradient;
		region_gfx_ops_subgfx.vgfo_vgradient       = &region_gfx_ops_subgfx_vgradient;
		region_gfx_ops_subgfx.vgfo_bitblit         = &region_gfx_ops_subgfx_bitblit;
		region_gfx_ops_subgfx.vgfo_stretch         = &region_gfx_ops_subgfx_stretch;
		region_gfx_ops_subgfx.vgfo_bitblit3        = &region_gfx_ops_subgfx_bitblit3;
		region_gfx_ops_subgfx.vgfo_stretch3        = &region_gfx_ops_subgfx_stretch3;
		COMPILER_WRITE_BARRIER();
		region_gfx_ops_subgfx.vgfo_blitfrom = &region_gfx_ops_subgfx_blitfrom;
		COMPILER_WRITE_BARRIER();
	}
	return &region_gfx_ops_subgfx;
}

PRIVATE ATTR_RETNONNULL WUNUSED struct video_gfx_ops *CC
_region_gfx_ops_subops(void) {
	if (!region_gfx_ops_subops.vgfo_blitfrom) {
		region_gfx_ops_subops.vgfo_blitfrom3       = &region_gfx_ops_subops_blitfrom3;
		region_gfx_ops_subops.vgfo_clip            = &region_gfx_ops_subops_clip;
		region_gfx_ops_subops.vgfo_offset2coord    = &region_gfx_ops_subops_offset2coord;
		region_gfx_ops_subops.vgfo_coord2offset    = &region_gfx_ops_subops_coord2offset;
		region_gfx_ops_subops.vgfo_getcolor        = &region_gfx_ops_subops_getcolor;
		region_gfx_ops_subops.vgfo_putcolor        = &region_gfx_ops_subops_putcolor;
		region_gfx_ops_subops.vgfo_line            = &region_gfx_ops_subops_line;
		region_gfx_ops_subops.vgfo_hline           = &region_gfx_ops_subops_hline;
		region_gfx_ops_subops.vgfo_vline           = &region_gfx_ops_subops_vline;
		region_gfx_ops_subops.vgfo_fill            = &region_gfx_ops_subops_fill;
		region_gfx_ops_subops.vgfo_rect            = &region_gfx_ops_subops_rect;
		region_gfx_ops_subops.vgfo_fillmask        = &region_gfx_ops_subops_fillmask;
		region_gfx_ops_subops.vgfo_fillstretchmask = &region_gfx_ops_subops_fillstretchmask;
		region_gfx_ops_subops.vgfo_gradient        = &region_gfx_ops_subops_gradient;
		region_gfx_ops_subops.vgfo_hgradient       = &region_gfx_ops_subops_hgradient;
		region_gfx_ops_subops.vgfo_vgradient       = &region_gfx_ops_subops_vgradient;
		region_gfx_ops_subops.vgfo_bitblit         = &region_gfx_ops_subops_bitblit;
		region_gfx_ops_subops.vgfo_stretch         = &region_gfx_ops_subops_stretch;
		region_gfx_ops_subops.vgfo_bitblit3        = &region_gfx_ops_subops_bitblit3;
		region_gfx_ops_subops.vgfo_stretch3        = &region_gfx_ops_subops_stretch3;
		COMPILER_WRITE_BARRIER();
		region_gfx_ops_subops.vgfo_blitfrom = &region_gfx_ops_subops_blitfrom;
		COMPILER_WRITE_BARRIER();
	}
	return &region_gfx_ops_subops;
}



#define subregion_buffer_r_initgfx       bigregion_buffer_r_initgfx
#define subregion_buffer_norem_r_initgfx bigregion_buffer_r_initgfx
PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
bigregion_buffer_r_initgfx(struct video_gfx *__restrict self) {
	struct bigregion_buffer_r *me = (struct bigregion_buffer_r *)self->vx_buffer;
	struct video_buffer *base;
	bigregion_buffer_r_startuse(me);
	self->vx_buffer = base = atomic_read(&me->brb_base);
	self->_vx_driver[REGION_GFX_SUBOPS] = NULL;
	self = (*base->vb_ops->vi_initgfx)(self);
	self = (*self->vx_hdr.vxh_ops->vgfo_clip)(self, me->brb_xoff, me->brb_yoff,
	                                          me->vb_xdim, me->vb_ydim);
	if likely(self->vx_buffer == base && self->_vx_driver[REGION_GFX_SUBOPS] == NULL) {
		/* GFX-reuse optimizations */
		self->_vx_driver[REGION_GFX_SUBOPS] = (void *)self->vx_hdr.vxh_ops;
		self->vx_hdr.vxh_ops = _region_gfx_ops_subops();
		self->vx_buffer = me;
	} else {
		/* No GFX-reuse optimizations :( */
		self->vx_hdr.vxh_ops = _region_gfx_ops_subgfx();
	}
	bigregion_buffer_r_enduse(me);
	return self;
}

PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
basregion_buffer_r_initgfx(struct video_gfx *__restrict self) {
	struct bigregion_buffer_r *me = (struct bigregion_buffer_r *)self->vx_buffer;
	struct video_buffer *base;
	bigregion_buffer_r_startuse(me);
	self->vx_buffer = base = atomic_read(&me->brb_base);
	self->_vx_driver[REGION_GFX_SUBOPS] = NULL;
	self = (*base->vb_ops->vi_initgfx)(self);
	if likely(self->vx_buffer == base && self->_vx_driver[REGION_GFX_SUBOPS] == NULL) {
		/* GFX-reuse optimizations */
		self->_vx_driver[REGION_GFX_SUBOPS] = (void *)self->vx_hdr.vxh_ops;
		self->vx_hdr.vxh_ops = _region_gfx_ops_subops();
		self->vx_buffer = me;
	} else {
		/* No GFX-reuse optimizations :( */
		self->vx_hdr.vxh_ops = _region_gfx_ops_subgfx();
	}
	bigregion_buffer_r_enduse(me);
	return self;
}

#define subregion_buffer_r_updategfx       bigregion_buffer_r_updategfx
#define subregion_buffer_norem_r_updategfx bigregion_buffer_r_updategfx
#define basregion_buffer_r_updategfx       bigregion_buffer_r_updategfx
PRIVATE ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
bigregion_buffer_r_updategfx(struct video_gfx *__restrict self, unsigned int what) {
	if (self->vx_hdr.vxh_ops == &region_gfx_ops_subops) {
		struct bigregion_buffer_r *me = (struct bigregion_buffer_r *)self->vx_buffer;
		struct video_buffer *base;
		bigregion_buffer_r_startuse(me);
		base = atomic_read(&me->brb_base);
		if likely(base == me->brbr_orig) {
			self->vx_hdr.vxh_ops = (struct video_gfx_ops *)self->_vx_driver[REGION_GFX_SUBOPS];
			self->_vx_driver[REGION_GFX_SUBOPS] = NULL;
			self->vx_buffer = base;
			self = (*base->vb_ops->vi_updategfx)(self, what);
			if likely(self->vx_buffer == base && self->_vx_driver[REGION_GFX_SUBOPS] == NULL) {
				/* Keep doing GFX-reuse optimizations */
				self->_vx_driver[REGION_GFX_SUBOPS] = (void *)self->vx_hdr.vxh_ops;
				self->vx_hdr.vxh_ops = &region_gfx_ops_subops;
				self->vx_buffer = me;
			} else {
				/* Can no longer do GFX-reuse optimization :( */
				self->vx_hdr.vxh_ops = _region_gfx_ops_subgfx();
			}
		} else {
			self->vx_hdr.vxh_ops = &libvideo_emptygfx_ops;
		}
		bigregion_buffer_r_enduse(me);
	}
	return self;
}






INTERN struct video_buffer_ops bigregion_buffer_ops = {};
INTERN struct video_buffer_ops bigregion_buffer_ops_r = {};
INTERN struct video_buffer_ops subregion_buffer_ops_r = {};
INTERN struct video_buffer_ops subregion_buffer_ops_norem_r = {};
INTERN struct video_buffer_ops basregion_buffer_ops_r = {};

INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC
_bigregion_buffer_ops(void) {
	if (!bigregion_buffer_ops.vi_destroy) {
		bigregion_buffer_ops.vi_rlock        = &bigregion_buffer_rlock;
		bigregion_buffer_ops.vi_wlock        = &bigregion_buffer_wlock;
		bigregion_buffer_ops.vi_unlock       = &bigregion_buffer_unlock;
		bigregion_buffer_ops.vi_rlockregion  = &bigregion_buffer_rlockregion;
		bigregion_buffer_ops.vi_wlockregion  = &bigregion_buffer_wlockregion;
		bigregion_buffer_ops.vi_unlockregion = &bigregion_buffer_unlockregion;
		bigregion_buffer_ops.vi_initgfx      = &bigregion_buffer_initgfx;
		bigregion_buffer_ops.vi_updategfx    = &bigregion_buffer_updategfx;
		COMPILER_WRITE_BARRIER();
		bigregion_buffer_ops.vi_destroy = &bigregion_buffer_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &bigregion_buffer_ops;
}

INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC
_bigregion_buffer_ops_r(void) {
	if (!bigregion_buffer_ops_r.vi_destroy) {
		bigregion_buffer_ops_r.vi_rlock        = &bigregion_buffer_r_rlock;
		bigregion_buffer_ops_r.vi_wlock        = &bigregion_buffer_r_wlock;
		bigregion_buffer_ops_r.vi_unlock       = &bigregion_buffer_r_unlock;
		bigregion_buffer_ops_r.vi_rlockregion  = &bigregion_buffer_r_rlockregion;
		bigregion_buffer_ops_r.vi_wlockregion  = &bigregion_buffer_r_wlockregion;
		bigregion_buffer_ops_r.vi_unlockregion = &bigregion_buffer_r_unlockregion;
		bigregion_buffer_ops_r.vi_initgfx      = &bigregion_buffer_r_initgfx;
		bigregion_buffer_ops_r.vi_updategfx    = &bigregion_buffer_r_updategfx;
		COMPILER_WRITE_BARRIER();
		bigregion_buffer_ops_r.vi_destroy = &bigregion_buffer_r_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &bigregion_buffer_ops_r;
}

INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC
_subregion_buffer_ops_r(void) {
	if (!subregion_buffer_ops_r.vi_destroy) {
		subregion_buffer_ops_r.vi_rlock        = &subregion_buffer_r_rlock;
		subregion_buffer_ops_r.vi_wlock        = &subregion_buffer_r_wlock;
		subregion_buffer_ops_r.vi_unlock       = &subregion_buffer_r_unlock;
		subregion_buffer_ops_r.vi_rlockregion  = &subregion_buffer_r_rlockregion;
		subregion_buffer_ops_r.vi_wlockregion  = &subregion_buffer_r_wlockregion;
		subregion_buffer_ops_r.vi_unlockregion = &subregion_buffer_r_unlockregion;
		subregion_buffer_ops_r.vi_initgfx      = &subregion_buffer_r_initgfx;
		subregion_buffer_ops_r.vi_updategfx    = &subregion_buffer_r_updategfx;
		COMPILER_WRITE_BARRIER();
		subregion_buffer_ops_r.vi_destroy = &subregion_buffer_r_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &subregion_buffer_ops_r;
}

INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC
_subregion_buffer_ops_norem_r(void) {
	if (!subregion_buffer_ops_norem_r.vi_destroy) {
		subregion_buffer_ops_norem_r.vi_rlock        = &subregion_buffer_norem_r_rlock;
		subregion_buffer_ops_norem_r.vi_wlock        = &subregion_buffer_norem_r_wlock;
		subregion_buffer_ops_norem_r.vi_unlock       = &subregion_buffer_norem_r_unlock;
		subregion_buffer_ops_norem_r.vi_rlockregion  = &subregion_buffer_norem_r_rlockregion;
		subregion_buffer_ops_norem_r.vi_wlockregion  = &subregion_buffer_norem_r_wlockregion;
		subregion_buffer_ops_norem_r.vi_unlockregion = &subregion_buffer_norem_r_unlockregion;
		subregion_buffer_ops_norem_r.vi_initgfx      = &subregion_buffer_norem_r_initgfx;
		subregion_buffer_ops_norem_r.vi_updategfx    = &subregion_buffer_norem_r_updategfx;
		COMPILER_WRITE_BARRIER();
		subregion_buffer_ops_norem_r.vi_destroy = &subregion_buffer_norem_r_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &subregion_buffer_ops_norem_r;
}

INTERN ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC
_basregion_buffer_ops_r(void) {
	if (!basregion_buffer_ops_r.vi_destroy) {
		basregion_buffer_ops_r.vi_rlock        = &basregion_buffer_r_rlock;
		basregion_buffer_ops_r.vi_wlock        = &basregion_buffer_r_wlock;
		basregion_buffer_ops_r.vi_unlock       = &basregion_buffer_r_unlock;
		basregion_buffer_ops_r.vi_rlockregion  = &basregion_buffer_r_rlockregion;
		basregion_buffer_ops_r.vi_wlockregion  = &basregion_buffer_r_wlockregion;
		basregion_buffer_ops_r.vi_unlockregion = &basregion_buffer_r_unlockregion;
		basregion_buffer_ops_r.vi_initgfx      = &basregion_buffer_r_initgfx;
		basregion_buffer_ops_r.vi_updategfx    = &basregion_buffer_r_updategfx;
		COMPILER_WRITE_BARRIER();
		basregion_buffer_ops_r.vi_destroy = &basregion_buffer_r_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &basregion_buffer_ops_r;
}



PRIVATE WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *CC
libvideo_buffer_region_impl(struct video_buffer *__restrict self,
                            struct video_rect const *__restrict rect,
                            bool revokable) {
	bool is_subregion = rect->vr_xmin >= 0 && rect->vr_ymin >= 0 &&
	                    (rect->vr_xmin + rect->vr_xdim) <= self->vb_xdim &&
	                    (rect->vr_ymin + rect->vr_ydim) <= self->vb_ydim;

	/* TODO: Better integration when "self" is a GFX-buffer */

	/* TODO: Inline offsets when "self" is one of the following:
	 * >> bigregion_buffer_ops
	 * >> bigregion_buffer_ops_r
	 * >> subregion_buffer_ops
	 * >> subregion_buffer_ops_norem
	 * >> subregion_buffer_ops_r
	 * >> subregion_buffer_ops_norem_r
	 */

	if (!is_subregion) {
		struct bigregion_buffer_r *result;
		size_t struct_size = revokable ? sizeof(struct bigregion_buffer_r)
		                               : sizeof(struct bigregion_buffer_r);
		result = (struct bigregion_buffer_r *)malloc(struct_size);
		if unlikely(!result)
			goto err;
		result->vb_ops = revokable ? _bigregion_buffer_ops_r()
		                           : _bigregion_buffer_ops();
		result->vb_format = self->vb_format;
		if (result->vb_format.vf_pal)
			video_palette_incref(result->vb_format.vf_pal);
		result->vb_xdim = rect->vr_xdim;
		result->vb_ydim = rect->vr_ydim;
		result->vb_refcnt = 1;
		video_buffer_incref(self);
		result->brb_base = self;
		result->brb_xoff = rect->vr_xmin;
		result->brb_yoff = rect->vr_ymin;
		if (revokable) {
			result->brbr_orig  = self;
			result->brbr_inuse = 0;
		}
		return result;
	} else {
		struct subregion_buffer_r *result;
		size_t struct_size = revokable ? sizeof(struct subregion_buffer_r)
		                               : sizeof(struct subregion_buffer_r);
		result = (struct subregion_buffer_r *)malloc(struct_size);
		if unlikely(!result)
			goto err;
		video_codec_xcoord_to_offset(self->vb_format.vf_codec,
		                             (video_coord_t)rect->vr_xmin,
		                             &result->srb_vm_xoff,
		                             &result->srb_vm_xrem);

		if (rect->vr_xmin == 0 && rect->vr_ymin == 0 &&
		    rect->vr_xdim == self->vb_xdim &&
		    rect->vr_ydim == self->vb_ydim && revokable) {
			/* Special case optimization: same dimensions as base buffer.
			 * This has a special optimization since this happens when an
			 * app is given fullscreen, passthru access to display memory */
			result->vb_ops = _basregion_buffer_ops_r();
		} else if (result->srb_vm_xrem) {
			result->vb_ops = revokable ? _subregion_buffer_ops_r()
			                           : _subregion_buffer_ops();
		} else {
			result->vb_ops = revokable ? _subregion_buffer_ops_norem_r()
			                           : _subregion_buffer_ops_norem();
		}
		result->vb_format = self->vb_format;
		if (result->vb_format.vf_pal)
			video_palette_incref(result->vb_format.vf_pal);
		result->vb_xdim = rect->vr_xdim;
		result->vb_ydim = rect->vr_ydim;
		result->vb_refcnt = 1;
		video_buffer_incref(self);
		result->srb_base = self;
		result->srb_xoff = rect->vr_xmin;
		result->srb_yoff = rect->vr_ymin;
		if (revokable) {
			result->srbr_orig  = self;
			result->srbr_inuse = 0;
		}
		return result;
	}
	__builtin_unreachable();
err:
	return NULL;
}

/* Create a wrapper video buffer for `self' that can only ever be used to access
 * the intersection of pixels from `rect' and `self' (trying a GFX context  will
 * always start out with the I/O rect set to "rect", but the clip rect still set
 * to the buffer's base dimensions, and trying to lock OOB regions always fails)
 *
 * NOTE: Starting coords in `rect' are allowed to be negative, and its dimensions
 *       are allowed to be greater than those of `self', too!
 *
 * `video_buffer_region_revocable()' does the same,  but the returned video  buffer
 * is also "revocable" (s.a. `libvideo_buffer_region_revoke()'), meaning it can  be
 * detached from the original buffer (and turned into a no-op) at any point in time
 * (blocking if a video lock is held in `libvideo_buffer_region_revoke()').
 *
 * @return: * :   The wrapper video buffer
 * @return: NULL: Failed to create video buffer (s.a. `errno') */
DEFINE_PUBLIC_ALIAS(video_buffer_region, libvideo_buffer_region);
INTERN WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *CC
libvideo_buffer_region(struct video_buffer *__restrict self,
                       struct video_rect const *__restrict rect) {
	/* Check for special case: "rect" is the full buffer */
	if (rect->vr_xmin == 0 && rect->vr_ymin == 0 &&
	    rect->vr_xdim == self->vb_xdim &&
	    rect->vr_ydim == self->vb_ydim) {
		video_buffer_incref(self);
		return self;
	}
	return libvideo_buffer_region_impl(self, rect, false);
}

DEFINE_PUBLIC_ALIAS(video_buffer_region_revocable, libvideo_buffer_region_revocable);
INTERN WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *CC
libvideo_buffer_region_revocable(struct video_buffer *__restrict self,
                                 struct video_rect const *__restrict rect) {
	struct video_buffer *me = self;

	/* Check for special case: "self" is already revocable
	 * -> In this case, can  just create a non-revocable  wrapper
	 *    that `libvideo_buffer_region_revoke()' will just unwrap */
	while (me->vb_ops == &bigregion_buffer_ops ||
	       me->vb_ops == &subregion_buffer_ops ||
	       me->vb_ops == &subregion_buffer_ops_norem)
		me = ((struct bigregion_buffer_r *)me)->brb_base;
	if (me->vb_ops == &bigregion_buffer_ops_r ||
	    me->vb_ops == &subregion_buffer_ops_r ||
	    me->vb_ops == &subregion_buffer_ops_norem_r)
		return libvideo_buffer_region(self, rect);

	/* Create a new region buffer with revocation support */
	return libvideo_buffer_region_impl(self, rect, true);
}


/* Revoke  access  to the  underlying  video buffer,  given  a video
 * buffer that was returned by `libvideo_buffer_region_revocable()'.
 * If the buffer had already been revoked, this is a no-op.
 *
 * >> DO NOT CALL THIS FUNCTION FOR BUFFERS OBTAINED FROM SOMETHING
 * >> OTHER THAN `libvideo_buffer_region_revocable()' !!!
 *
 * @return: * : Always re-returns `self' */
DEFINE_PUBLIC_ALIAS(video_buffer_region_revoke, libvideo_buffer_region_revoke);
INTERN ATTR_INOUT(1) struct video_buffer *CC
libvideo_buffer_region_revoke(struct video_buffer *__restrict self) {
	struct bigregion_buffer_r *me = (struct bigregion_buffer_r *)self;
	struct video_buffer *obuf, *empty;
	static_assert(offsetof(struct bigregion_buffer_r, brbr_inuse) ==
	              offsetof(struct subregion_buffer_r, srbr_inuse));
	/* Unwrap region wrappers without revoke support. */
	while (me->vb_ops == &bigregion_buffer_ops ||
	       me->vb_ops == &subregion_buffer_ops ||
	       me->vb_ops == &subregion_buffer_ops_norem)
		me = (struct bigregion_buffer_r *)me->brb_base;
	assertf(me->vb_ops == &bigregion_buffer_ops_r ||
	        me->vb_ops == &subregion_buffer_ops_r ||
	        me->vb_ops == &subregion_buffer_ops_norem_r,
	        "Not a revokable buffer!");

	/* Load replacement buffer (for this: always use the "empty" buffer) */
	empty = &libvideo_emptybuffer;
	video_buffer_incref(empty);

	/* Load the replace buffer into the reference slot */
	obuf = atomic_xch(&me->brb_base, empty);

	/* Wait until anyone that might potentially still
	 * be using the old buffer has stopped doing  so. */
	while (atomic_read(&me->brbr_inuse) != 0)
		sched_yield();

	/* Drop reference to old buffer. */
	video_buffer_decref(obuf);
	return me;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_REGION_C */
