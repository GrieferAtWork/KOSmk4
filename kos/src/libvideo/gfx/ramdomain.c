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
#ifndef GUARD_LIBVIDEO_GFX_RAMDOMAIN_C
#define GUARD_LIBVIDEO_GFX_RAMDOMAIN_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>
#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sequence/list.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <malloc.h>
#include <sched.h>
#include <stddef.h>
#include <stdint.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/palette.h>
#include <libvideo/crect.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/buffer/dummy.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "buffer.h"
#include "buffer/dummy.h"
#include "buffer/utils.h"
#include "gfx-empty.h"
#include "ramdomain.h"

DECL_BEGIN


/************************************************************************/
/* RAM DOMAIN OPERATORS                                                 */
/************************************************************************/

static_assert(offsetof(struct video_rambuffer_subsubregion, rbssr_base) == offsetof(struct video_rambuffer_subregion, rbsr_base));
static_assert(offsetof(struct video_rambuffer_formem_subregion, rbfmsr_base) == offsetof(struct video_rambuffer_subregion, rbsr_base));

/* Video buffer types used to represent ram buffers.
 * NOTE: None of these ever look at `video_buffer::vb_domain',
 *       so you're free to  re-use these at the  driver-level! */

/* DESTROY */
INTERN NONNULL((1)) void FCC
rambuffer__destroy(struct video_buffer *__restrict self) {
	struct video_rambuffer *me = (struct video_rambuffer *)self;
	assertf(LIST_EMPTY(&me->rb_subregions_list), "Sub-regions should have been holding references");
	if (me->vb_format.vf_pal)
		video_palette_decref(me->vb_format.vf_pal);
	free(me->rb_data);
	free(me);
}

INTERN NONNULL((1)) void FCC
rambuffer_xcodec__destroy(struct video_buffer *__restrict self) {
	struct video_rambuffer_xcodec *me = (struct video_rambuffer_xcodec *)self;
	video_codec_handle_decref(me->rbxc_codec);
	rambuffer__destroy(me);
}

INTERN NONNULL((1)) void FCC
rambuffer_subregion__destroy(struct video_buffer *__restrict self) {
	struct video_rambuffer_subregion *me = (struct video_rambuffer_subregion *)self;
	REF struct video_rambuffer *base = me->rbsr_base;
	assertf(me->rbrv_gfx.rbrvg_inuse == 0, "Non-zero 'rbrv_gfx.rbrvg_inuse' counter during finalization");
	assertf(LIST_EMPTY(&me->rbrvsr_subsubregions_list), "Sub-sub-regions should have been holding references");
	if (base) {
		atomic_lock_acquire(&base->rb_subregions_lock);
		if (LIST_ISBOUND(me, rbrvsr_chain))
			LIST_REMOVE(me, rbrvsr_chain);
		atomic_lock_release(&base->rb_subregions_lock);
		video_buffer_decref(base);
	}
	video_buffer_dummy_decref(me->rbrv_dummy);
	free(me);
}

INTERN NONNULL((1)) void FCC
rambuffer_subsubregion__destroy(struct video_buffer *__restrict self) {
	struct video_rambuffer_subsubregion *me = (struct video_rambuffer_subsubregion *)self;
	REF struct video_rambuffer_subregion *base = atomic_read(&me->rbssr_base);
	assertf(me->rbrv_gfx.rbrvg_inuse == 0, "Non-zero 'rbrv_gfx.rbrvg_inuse' counter during finalization");
	assertf(LIST_EMPTY(&me->rbrvsr_subsubregions_list), "Sub-sub-regions should have been holding references");
	if (base) {
		atomic_lock_acquire(&base->rbrvsr_subsubregions_lock);
		if (LIST_ISBOUND(me, rbrvsr_chain))
			LIST_REMOVE(me, rbrvsr_chain);
		atomic_lock_release(&base->rbrvsr_subsubregions_lock);
		video_buffer_decref(base);
	}
	video_buffer_dummy_decref(me->rbrv_dummy);
	free(me);
}

INTERN NONNULL((1)) void FCC
rambuffer_formem__destroy(struct video_buffer *__restrict self) {
	struct video_rambuffer_formem *me = (struct video_rambuffer_formem *)self;
	assertf(me->rbrv_gfx.rbrvg_inuse == 0, "Non-zero 'rbrv_gfx.rbrvg_inuse' counter during finalization");
	assertf(LIST_EMPTY(&me->rbfm_subregions_list), "Sub-regions should have been holding references");
	if (me->rbrv_gfx.rbrvg_data != me->rbrv_dummy->vbd_data)
		(*me->rbfm_release_mem)(me->rbfm_release_mem_cookie, me->rbrv_gfx.rbrvg_data);
	video_buffer_dummy_decref(me->rbrv_dummy);
	free(me);
}

INTERN NONNULL((1)) void FCC
rambuffer_formem_xcodec__destroy(struct video_buffer *__restrict self) {
	struct video_rambuffer_formem_xcodec *me = (struct video_rambuffer_formem_xcodec *)self;
	video_codec_handle_decref(me->rbfmxc_codec);
	rambuffer_formem__destroy(me);
}

INTERN NONNULL((1)) void FCC
rambuffer_formem_subregion__destroy(struct video_buffer *__restrict self) {
	struct video_rambuffer_formem_subregion *me = (struct video_rambuffer_formem_subregion *)self;
	REF struct video_rambuffer_formem *base = atomic_read(&me->rbfmsr_base);
	assertf(me->rbrv_gfx.rbrvg_inuse == 0, "Non-zero 'rbrv_gfx.rbrvg_inuse' counter during finalization");
	assertf(LIST_EMPTY(&me->rbrvsr_subsubregions_list), "Sub-regions should have been holding references");
	if (base) {
		atomic_lock_acquire(&base->rbfm_subregions_lock);
		if (LIST_ISBOUND(me, rbrvsr_chain))
			LIST_REMOVE(me, rbrvsr_chain);
		atomic_lock_release(&base->rbfm_subregions_lock);
		video_buffer_decref(base);
	}
	video_buffer_dummy_decref(me->rbrv_dummy);
	free(me);
}


/* REVOKE+SUBREGION */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC rambuffer__revoke)(struct video_buffer *__restrict self) {
	struct video_rambuffer *me = (struct video_rambuffer *)self;
	atomic_lock_acquire(&me->rb_subregions_lock);
	while (!LIST_EMPTY(&me->rb_subregions_list)) {
		struct video_rambuffer_subregion *sr;
		sr = (struct video_rambuffer_subregion *)LIST_FIRST(&me->rb_subregions_list);
		if (!tryincref(sr)) {
			LIST_UNBIND(sr, rbrvsr_chain);
		} else {
			atomic_lock_release(&me->rb_subregions_lock);
			sr = (struct video_rambuffer_subregion *)video_buffer_revoke(sr);
			video_buffer_decref(sr);
			atomic_lock_acquire(&me->rb_subregions_lock);
		}
	}
	atomic_lock_release(&me->rb_subregions_lock);
	return me;
}

PRIVATE ATTR_INOUT(1) void
NOTHROW(FCC rambuffer_revokable__revoke)(struct video_rambuffer_revokable *__restrict me) {
	atomic_write(&me->rbrv_gfx.rbrvg_data, me->rbrv_dummy->vbd_data);
	while (atomic_read(&me->rbrv_gfx.rbrvg_inuse) != 0)
		sched_yield();
}

PRIVATE ATTR_INOUT(1) void
NOTHROW(FCC rambuffer_revokable_subregion__revoke)(struct video_rambuffer_revokable_subregion *__restrict me) {
	atomic_lock_acquire(&me->rbrvsr_subsubregions_lock);
	while (!LIST_EMPTY(&me->rbrvsr_subsubregions_list)) {
		struct video_rambuffer_revokable_subregion *sr;
		sr = (struct video_rambuffer_revokable_subregion *)LIST_FIRST(&me->rbrvsr_subsubregions_list);
		if (!tryincref(sr)) {
			LIST_UNBIND(sr, rbrvsr_chain);
		} else {
			atomic_lock_release(&me->rbrvsr_subsubregions_lock);
			sr = (struct video_rambuffer_revokable_subregion *)video_buffer_revoke(sr);
			video_buffer_decref(sr);
			atomic_lock_acquire(&me->rbrvsr_subsubregions_lock);
		}
	}
	atomic_lock_release(&me->rbrvsr_subsubregions_lock);
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC rambuffer_subregion__revoke)(struct video_buffer *__restrict self) {
	struct video_rambuffer_subregion *me = (struct video_rambuffer_subregion *)self;
	REF struct video_rambuffer *base;
	rambuffer_revokable__revoke(me);
	rambuffer_revokable_subregion__revoke(me);
	base = atomic_xch(&me->rbsr_base, NULL);
	if (base)
		video_buffer_decref(base);
	return me;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC rambuffer_formem__revoke)(struct video_buffer *__restrict self) {
	struct video_rambuffer_formem *me = (struct video_rambuffer_formem *)self;
	byte_t *old_data = atomic_xch(&me->rbrv_gfx.rbrvg_data, me->rbrv_dummy->vbd_data);
	while (atomic_read(&me->rbrv_gfx.rbrvg_inuse) != 0)
		sched_yield();
	if (old_data != me->rbrv_dummy->vbd_data)
		(*me->rbfm_release_mem)(me->rbfm_release_mem_cookie, old_data);
	atomic_lock_acquire(&me->rbfm_subregions_lock);
	while (!LIST_EMPTY(&me->rbfm_subregions_list)) {
		struct video_rambuffer_formem_subregion *sr;
		sr = (struct video_rambuffer_formem_subregion *)LIST_FIRST(&me->rbfm_subregions_list);
		if (!tryincref(sr)) {
			LIST_UNBIND(sr, rbrvsr_chain);
		} else {
			atomic_lock_release(&me->rbfm_subregions_lock);
			sr = (struct video_rambuffer_formem_subregion *)video_buffer_revoke(sr);
			video_buffer_decref(sr);
			atomic_lock_acquire(&me->rbfm_subregions_lock);
		}
	}
	atomic_lock_release(&me->rbfm_subregions_lock);
	return me;
}



#define ASSERT_SUBREGION_RECT(self, rect)                              \
	(assert(((rect)->vcr_xmin + (rect)->vcr_xdim) > (rect)->vcr_xmin), \
	 assert(((rect)->vcr_ymin + (rect)->vcr_ydim) > (rect)->vcr_ymin), \
	 assert(((rect)->vcr_xmin + (rect)->vcr_xdim) <= (self)->vb_xdim), \
	 assert(((rect)->vcr_ymin + (rect)->vcr_ydim) <= (self)->vb_ydim))


/* Common base for creation a sub-region. Caller must still:
 * - Add `return' to the chain of sub-regions of `self' (thus initializing `return->rbrvsr_chain')
 * - Fill in `return->vb_ops'
 * - Fill in `return->rbrvsr_xflags'
 * - Adjust `return->rbrv_gfx.rbrvg_data'
 */
PRIVATE WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_rambuffer_revokable_subregion *FCC
rambuffer__subregion__common(struct video_buffer *__restrict self,
                             struct video_crect const *__restrict rect, size_t self_stride) {
	static_assert(sizeof(struct video_rambuffer_subregion) == sizeof(struct video_rambuffer_subsubregion));
	static_assert(sizeof(struct video_rambuffer_subregion) == sizeof(struct video_rambuffer_formem_subregion));
	static_assert(offsetof(struct video_rambuffer_subregion, rbsr_base) == offsetof(struct video_rambuffer_subsubregion, rbssr_base));
	static_assert(offsetof(struct video_rambuffer_subregion, rbsr_base) == offsetof(struct video_rambuffer_formem_subregion, rbfmsr_base));
	size_t x_byte_offset;
	REF struct video_rambuffer_subregion *result;
	result = (REF struct video_rambuffer_subregion *)malloc(sizeof(struct video_rambuffer_subregion));
	if unlikely(!result)
		goto err;
	result->vb_domain = self->vb_domain;
	result->vb_format = self->vb_format;
	result->vb_xdim   = rect->vcr_xdim;
	result->vb_ydim   = rect->vcr_ydim;
	result->vb_refcnt = 1;
	video_codec_xcoord_to_offset(result->vb_format.vf_codec, rect->vcr_xmin,
	                             &x_byte_offset, &result->rbrvsr_xoff);
	result->rbrv_gfx.rbrvg_data  = (byte_t *)(x_byte_offset + rect->vcr_ymin * self_stride);
	result->rbrv_gfx.rbrvg_inuse = 0;
	result->rbrv_stride = self_stride;
	result->rbrv_dummy  = libvideo_buffer_getdummy(result->vb_ydim * self_stride);
	if unlikely(!result->rbrv_dummy)
		goto err_r;

/*	result->rbrvsr_chain = ...; // Initialized by caller */
	LIST_INIT(&result->rbrvsr_subsubregions_list);
	atomic_lock_init(&result->rbrvsr_subsubregions_lock);
	result->rbsr_base = (REF struct video_rambuffer *)self;

	video_buffer_incref(self); /* for "result->rbsr_base" */
	if (result->vb_format.vf_pal)
		video_palette_incref(result->vb_format.vf_pal);
	return result;
err_r:
	free(result);
err:
	return NULL;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC
rambuffer__subregion(struct video_buffer *__restrict self,
                     struct video_crect const *__restrict rect,
                     gfx_flag_t xor_flags) {
	REF struct video_rambuffer_subregion *result;
	struct video_rambuffer *me = (struct video_rambuffer *)self;
	result = (REF struct video_rambuffer_subregion *)rambuffer__subregion__common(me, rect, me->rb_stride);
	if likely(result) {
		result->rbrv_gfx.rbrvg_data += (uintptr_t)me->rb_data;
		result->rbrvsr_xflags = xor_flags;
		result->vb_ops = result->rbrvsr_xoff ? _rambuffer_subregion_xoff_ops()
		                                     : _rambuffer_subregion_ops();
		atomic_lock_acquire(&me->rb_subregions_lock);
		LIST_INSERT_HEAD((struct video_rambuffer_revokable_subregion_list *)&me->rb_subregions_list,
		                 (struct video_rambuffer_revokable_subregion *)result, rbrvsr_chain);
		atomic_lock_release(&me->rb_subregions_lock);
	}
	return result;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC
rambuffer_subregion__subregion(struct video_buffer *__restrict self,
                               struct video_crect const *__restrict rect,
                               gfx_flag_t xor_flags) {
	REF struct video_rambuffer_subsubregion *result;
	struct video_rambuffer_subregion *me = (struct video_rambuffer_subregion *)self;
	video_rambuffer_revokable_gfx_start(&me->rbrv_gfx);
	result = (REF struct video_rambuffer_subsubregion *)rambuffer__subregion__common(me, rect, me->rbrv_stride);
	if likely(result) {
		result->rbrvsr_xflags = gfx_flag_combine(me->rbrvsr_xflags, xor_flags);
		result->vb_ops = result->rbrvsr_xoff ? _rambuffer_subsubregion_xoff_ops()
		                                     : _rambuffer_subsubregion_ops();
		atomic_lock_acquire(&me->rbrvsr_subsubregions_lock);
		/* Must read data base-pointer only now, in case buffer is being revoked right now */
		result->rbrv_gfx.rbrvg_data += (uintptr_t)video_rambuffer_revokable_gfx_getdata(&me->rbrv_gfx);
		LIST_INSERT_HEAD(&me->rbrvsr_subsubregions_list,
		                 (struct video_rambuffer_revokable_subregion *)result, rbrvsr_chain);
		atomic_lock_release(&me->rbrvsr_subsubregions_lock);
	}
	video_rambuffer_revokable_gfx_end(&me->rbrv_gfx);
	return result;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC
rambuffer_formem__subregion(struct video_buffer *__restrict self,
                            struct video_crect const *__restrict rect,
                            gfx_flag_t xor_flags) {
	REF struct video_rambuffer_formem_subregion *result;
	struct video_rambuffer_formem *me = (struct video_rambuffer_formem *)self;
	video_rambuffer_revokable_gfx_start(&me->rbrv_gfx);
	result = (REF struct video_rambuffer_formem_subregion *)rambuffer__subregion__common(me, rect, me->rbrv_stride);
	if likely(result) {
		result->rbrvsr_xflags = xor_flags;
		result->vb_ops = result->rbrvsr_xoff ? _rambuffer_formem_subregion_xoff_ops()
		                                     : _rambuffer_formem_subregion_ops();
		atomic_lock_acquire(&me->rbfm_subregions_lock);
		/* Must read data base-pointer only now, in case buffer is being revoked right now */
		result->rbrv_gfx.rbrvg_data += (uintptr_t)video_rambuffer_revokable_gfx_getdata(&me->rbrv_gfx);
		LIST_INSERT_HEAD((struct video_rambuffer_revokable_subregion_list *)&me->rbfm_subregions_list,
		                 (struct video_rambuffer_revokable_subregion *)result, rbrvsr_chain);
		atomic_lock_release(&me->rbfm_subregions_lock);
	}
	video_rambuffer_revokable_gfx_end(&me->rbrv_gfx);
	return result;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC
rambuffer_formem_subregion__subregion(struct video_buffer *__restrict self,
                                      struct video_crect const *__restrict rect,
                                      gfx_flag_t xor_flags) {
	REF struct video_rambuffer_formem_subregion *result;
	struct video_rambuffer_formem_subregion *me = (struct video_rambuffer_formem_subregion *)self;
	video_rambuffer_revokable_gfx_start(&me->rbrv_gfx);
	result = (REF struct video_rambuffer_formem_subregion *)rambuffer__subregion__common(me, rect, me->rbrv_stride);
	if likely(result) {
		result->rbrvsr_xflags = gfx_flag_combine(me->rbrvsr_xflags, xor_flags);
		result->vb_ops = result->rbrvsr_xoff ? _rambuffer_formem_subregion_xoff_ops()
		                                     : _rambuffer_formem_subregion_ops();
		atomic_lock_acquire(&me->rbrvsr_subsubregions_lock);
		/* Must read data base-pointer only now, in case buffer is being revoked right now */
		result->rbrv_gfx.rbrvg_data += (uintptr_t)video_rambuffer_revokable_gfx_getdata(&me->rbrv_gfx);
		LIST_INSERT_HEAD((struct video_rambuffer_revokable_subregion_list *)&me->rbrvsr_subsubregions_list,
		                 (struct video_rambuffer_revokable_subregion *)result, rbrvsr_chain);
		atomic_lock_release(&me->rbrvsr_subsubregions_lock);
	}
	video_rambuffer_revokable_gfx_end(&me->rbrv_gfx);
	return result;
}




/* LOCK */
INTERN ATTR_INOUT(1) ATTR_OUT(2) int FCC
rambuffer__lock(struct video_buffer *__restrict self,
                struct video_lock *__restrict lock) {
	struct video_rambuffer *me = (struct video_rambuffer *)self;
	lock->vl_data   = me->rb_data;
	lock->vl_stride = me->rb_stride;
	return 0;
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
rambuffer__lockregion(struct video_buffer *__restrict self,
                      struct video_regionlock *__restrict lock) {
	struct video_rambuffer *me = (struct video_rambuffer *)self;
	lock->vrl_lock.vl_data   = me->rb_data + lock->_vrl_rect.vcr_ymin * me->rb_stride;
	lock->vrl_lock.vl_stride = me->rb_stride;
	lock->vrl_xbas = lock->_vrl_rect.vcr_xmin;
	return 0;
}

INTERN ATTR_INOUT(1) ATTR_OUT(2) int FCC
rambuffer_revokable__lock(struct video_buffer *__restrict self,
                          struct video_lock *__restrict lock) {
	struct video_rambuffer_revokable *me = (struct video_rambuffer_revokable *)self;
	video_rambuffer_revokable_gfx_start(&me->rbrv_gfx);
	lock->vl_data   = video_rambuffer_revokable_gfx_getdata(&me->rbrv_gfx);
	lock->vl_stride = me->rbrv_stride;
	return 0;
}

INTERN ATTR_INOUT(1) NONNULL((2)) void
NOTHROW(FCC rambuffer_revokable__unlock)(struct video_buffer *__restrict self,
                                         struct video_lock *__restrict UNUSED(lock)) {
	struct video_rambuffer_revokable *me = (struct video_rambuffer_revokable *)self;
	video_rambuffer_revokable_gfx_end(&me->rbrv_gfx);
}


INTERN ATTR_INOUT(1) ATTR_OUT(2) int FCC
rambuffer_revokable__lockregion(struct video_buffer *__restrict self,
                                struct video_regionlock *__restrict lock) {
	struct video_rambuffer_revokable *me = (struct video_rambuffer_revokable *)self;
	video_rambuffer_revokable_gfx_start(&me->rbrv_gfx);
	lock->vrl_lock.vl_data = video_rambuffer_revokable_gfx_getdata(&me->rbrv_gfx);
	lock->vrl_lock.vl_data += lock->_vrl_rect.vcr_ymin * me->rbrv_stride;
	lock->vrl_lock.vl_stride = me->rbrv_stride;
	lock->vrl_xbas = lock->_vrl_rect.vcr_xmin;
	return 0;
}

INTERN ATTR_INOUT(1) ATTR_OUT(2) int FCC
rambuffer_revokable_xoff__lockregion(struct video_buffer *__restrict self,
                                     struct video_regionlock *__restrict lock) {
	struct video_rambuffer_revokable_subregion *me = (struct video_rambuffer_revokable_subregion *)self;
	video_rambuffer_revokable_gfx_start(&me->rbrv_gfx);
	lock->vrl_lock.vl_data = video_rambuffer_revokable_gfx_getdata(&me->rbrv_gfx);
	lock->vrl_lock.vl_data += lock->_vrl_rect.vcr_ymin * me->rbrv_stride;
	lock->vrl_lock.vl_stride = me->rbrv_stride;
	lock->vrl_xbas = lock->_vrl_rect.vcr_xmin + me->rbrvsr_xoff;
	return 0;
}

DEFINE_VIDEO_BUFFER_TYPE(rambuffer_ops, rambuffer__destroy,
                         rambuffer__initgfx, rambuffer__updategfx,
                         rambuffer__lock, rambuffer__lock, libvideo_buffer_noop_unlock,
                         rambuffer__lockregion, rambuffer__lockregion, libvideo_buffer_noop_unlockregion,
                         rambuffer__revoke, rambuffer__subregion);
DEFINE_VIDEO_BUFFER_TYPE(rambuffer_xcodec_ops, rambuffer_xcodec__destroy,
                         rambuffer__initgfx, rambuffer__updategfx,
                         rambuffer__lock, rambuffer__lock, libvideo_buffer_noop_unlock,
                         rambuffer__lockregion, rambuffer__lockregion, libvideo_buffer_noop_unlockregion,
                         rambuffer__revoke, rambuffer__subregion);
DEFINE_VIDEO_BUFFER_TYPE(rambuffer_subregion_ops, rambuffer_subregion__destroy,
                         rambuffer_subregion__initgfx, rambuffer_revokable__updategfx,
                         rambuffer_revokable__lock, rambuffer_revokable__lock, libvideo_buffer_noop_unlock,
                         rambuffer_revokable__lockregion, rambuffer_revokable__lockregion, rambuffer_revokable__unlockregion,
                         rambuffer_subregion__revoke, rambuffer_subregion__subregion);
DEFINE_VIDEO_BUFFER_TYPE(rambuffer_subregion_xoff_ops, rambuffer_subregion__destroy,
                         rambuffer_revokable_xoff__initgfx, rambuffer_revokable_xoff__updategfx,
                         libvideo_buffer_notsup_rlock, libvideo_buffer_notsup_wlock, libvideo_buffer_noop_unlock,
                         rambuffer_revokable_xoff__lockregion, rambuffer_revokable_xoff__lockregion, rambuffer_revokable_xoff__unlockregion,
                         rambuffer_subregion__revoke, rambuffer_subregion__subregion);
DEFINE_VIDEO_BUFFER_TYPE(rambuffer_subsubregion_ops, rambuffer_subsubregion__destroy,
                         rambuffer_subregion__initgfx, rambuffer_revokable__updategfx,
                         rambuffer_revokable__lock, rambuffer_revokable__lock, libvideo_buffer_noop_unlock,
                         rambuffer_revokable__lockregion, rambuffer_revokable__lockregion, rambuffer_revokable__unlockregion,
                         rambuffer_subsubregion__revoke, rambuffer_subsubregion__subregion);
DEFINE_VIDEO_BUFFER_TYPE(rambuffer_subsubregion_xoff_ops, rambuffer_subsubregion__destroy,
                         rambuffer_revokable_xoff__initgfx, rambuffer_revokable_xoff__updategfx,
                         libvideo_buffer_notsup_rlock, libvideo_buffer_notsup_wlock, libvideo_buffer_noop_unlock,
                         rambuffer_revokable_xoff__lockregion, rambuffer_revokable_xoff__lockregion, rambuffer_revokable_xoff__unlockregion,
                         rambuffer_subsubregion__revoke, rambuffer_subsubregion__subregion);

DEFINE_VIDEO_BUFFER_TYPE(rambuffer_formem_ops, rambuffer_formem__destroy,
                         rambuffer_revokable__initgfx, rambuffer_revokable__updategfx,
                         rambuffer_revokable__lock, rambuffer_revokable__lock, libvideo_buffer_noop_unlock,
                         rambuffer_revokable__lockregion, rambuffer_revokable__lockregion, rambuffer_revokable__unlockregion,
                         rambuffer_formem__revoke, rambuffer_formem__subregion);
DEFINE_VIDEO_BUFFER_TYPE(rambuffer_formem_xcodec_ops, rambuffer_formem_xcodec__destroy,
                         rambuffer_revokable__initgfx, rambuffer_revokable__updategfx,
                         rambuffer_revokable__lock, rambuffer_revokable__lock, libvideo_buffer_noop_unlock,
                         rambuffer_revokable__lockregion, rambuffer_revokable__lockregion, rambuffer_revokable__unlockregion,
                         rambuffer_formem__revoke, rambuffer_formem__subregion);
DEFINE_VIDEO_BUFFER_TYPE(rambuffer_formem_subregion_ops, rambuffer_formem_subregion__destroy,
                         rambuffer_subregion__initgfx, rambuffer_revokable__updategfx,
                         rambuffer_revokable__lock, rambuffer_revokable__lock, libvideo_buffer_noop_unlock,
                         rambuffer_revokable__lockregion, rambuffer_revokable__lockregion, rambuffer_revokable__unlockregion,
                         rambuffer_formem_subregion__revoke, rambuffer_formem_subregion__subregion);
DEFINE_VIDEO_BUFFER_TYPE(rambuffer_formem_subregion_xoff_ops, rambuffer_formem_subregion__destroy,
                         rambuffer_revokable_xoff__initgfx, rambuffer_revokable_xoff__updategfx,
                         libvideo_buffer_notsup_rlock, libvideo_buffer_notsup_wlock, libvideo_buffer_noop_unlock,
                         rambuffer_revokable_xoff__lockregion, rambuffer_revokable_xoff__lockregion, rambuffer_revokable_xoff__unlockregion,
                         rambuffer_formem_subregion__revoke, rambuffer_formem_subregion__subregion);



#define return_empty_buffer                                      \
	do {                                                         \
		struct video_buffer *_empty_res = &libvideo_emptybuffer; \
		video_buffer_incref(_empty_res);                         \
		return _empty_res;                                       \
	}	__WHILE0

INTERN WUNUSED ATTR_IN(4) NONNULL((1)) REF struct video_buffer *CC
libvideo_ramdomain_newbuffer(struct video_domain const *__restrict self,
                             video_dim_t xdim, video_dim_t ydim,
                             struct video_format const *__restrict format,
                             unsigned int flags) {
	REF struct video_rambuffer *result;
	struct video_rambuffer_requirements req;
	assert(format);
	if unlikely(!xdim || !ydim)
		return_empty_buffer;

	/* Figure out buffer requirements. */
	(*format->vf_codec->vc_rambuffer_requirements)(xdim, ydim, &req);

	/* Allocate heap memory for the buffer */
	result = (REF struct video_rambuffer *)malloc(sizeof(struct video_rambuffer));
	if unlikely(!result)
		goto err;
	result->rb_data = (flags & VIDEO_DOMAIN_NEWBUFFER_F_CALLOC)
	                  ? (byte_t *)calloc(req.vbs_bufsize)
	                  : (byte_t *)malloc(req.vbs_bufsize);
	if unlikely(!result->rb_data)
		goto err_result;
	result->rb_stride = req.vbs_stride;
	LIST_INIT(&result->rb_subregions_list);
	atomic_lock_init(&result->rb_subregions_lock);
	result->vb_ops    = _rambuffer_ops();
	result->vb_domain = self;
	result->vb_refcnt = 1;
	result->vb_format = *format;
	result->vb_xdim   = xdim;
	result->vb_ydim   = ydim;
	if (result->vb_format.vf_pal) {
		if unlikely(!(result->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL)) {
			result->vb_format.vf_pal = NULL;
		} else {
			video_palette_incref(result->vb_format.vf_pal);
		}
	}
	return result;
err_result:
	free(result);
err:
	return NULL;
}

INTERN WUNUSED ATTR_IN(4) NONNULL((1)) REF struct video_buffer *CC
libvideo_ramdomain_newbuffer_ex(struct video_domain const *__restrict self,
                                video_dim_t xdim, video_dim_t ydim,
                                struct video_codec_specs const *__restrict codec_specs,
                                struct video_palette *palette, unsigned int flags) {
	struct video_codec const *codec;
	REF struct video_codec_handle *codec_handle;
	REF struct video_rambuffer_xcodec *result;
	struct video_rambuffer_requirements req;
	assert(codec_specs);
	if unlikely(!xdim || !ydim)
		return_empty_buffer;

	codec = video_codec_fromspecs(codec_specs, &codec_handle);
	if unlikely(!codec)
		goto err;
	if (!(codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL))
		palette = NULL;

	/* Figure out buffer requirements. */
	(*codec->vc_rambuffer_requirements)(xdim, ydim, &req);

	/* Allocate heap memory for the buffer */
	result = (REF struct video_rambuffer_xcodec *)malloc(sizeof(struct video_rambuffer_xcodec));
	if unlikely(!result)
		goto err_codec;
	result->rb_data = (flags & VIDEO_DOMAIN_NEWBUFFER_F_CALLOC)
	                  ? (byte_t *)calloc(req.vbs_bufsize)
	                  : (byte_t *)malloc(req.vbs_bufsize);
	if unlikely(!result->rb_data)
		goto err_codec_result;
	result->rb_stride = req.vbs_stride;
	LIST_INIT(&result->rb_subregions_list);
	atomic_lock_init(&result->rb_subregions_lock);
	result->rbxc_codec = codec_handle;
	result->vb_ops    = _rambuffer_xcodec_ops();
	result->vb_domain = self;
	result->vb_refcnt = 1;
	result->vb_format.vf_codec = codec;
	result->vb_format.vf_pal   = palette;
	result->vb_xdim   = xdim;
	result->vb_ydim   = ydim;
	if (palette) {
		if unlikely(!(codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL)) {
			result->vb_format.vf_pal = NULL;
		} else {
			video_palette_incref(result->vb_format.vf_pal);
		}
	}
	return result;
err_codec_result:
	free(result);
err_codec:
	video_codec_handle_decref(codec_handle);
err:
	return NULL;
}


INTERN WUNUSED ATTR_IN(4) NONNULL((1, 5)) REF struct video_buffer *CC
libvideo_ramdomain_formem(struct video_domain const *__restrict self, video_dim_t xdim, video_dim_t ydim,
                          struct video_format const *format, void *mem, size_t stride,
                          void (CC *release_mem)(void *cookie, void *mem),
                          void *release_mem_cookie, unsigned int flags) {
	REF struct video_rambuffer_formem *result;
	struct video_rambuffer_requirements req;
	assert(format);
	(void)flags;
	if unlikely(!xdim || !ydim)
		return_empty_buffer;

	/* Ensure that the specified stride is great enough */
	(*format->vf_codec->vc_rambuffer_requirements)(xdim, ydim, &req);
	if (stride < req.vbs_stride) {
		errno = EINVAL;
		return NULL;
	}

	/* Allocate heap memory for the buffer */
	result = (REF struct video_rambuffer_formem *)malloc(sizeof(struct video_rambuffer_formem));
	if unlikely(!result)
		goto err;
	result->rbrv_dummy = libvideo_buffer_getdummy(req.vbs_bufsize);
	if unlikely(!result->rbrv_dummy)
		goto err_r;
	result->rbrv_stride          = stride;
	result->rbrv_gfx.rbrvg_data  = (byte_t *)mem;
	result->rbrv_gfx.rbrvg_inuse = 0;
	result->vb_ops      = _rambuffer_formem_ops();
	result->vb_domain   = self;
	result->vb_refcnt   = 1;
	result->vb_format   = *format;
	result->vb_xdim     = xdim;
	result->vb_ydim     = ydim;
	result->rbfm_release_mem        = release_mem;
	result->rbfm_release_mem_cookie = release_mem_cookie;
	LIST_INIT(&result->rbfm_subregions_list);
	atomic_lock_init(&result->rbfm_subregions_lock);

	/* Must use a different, fallback "codec" that can deal with bad alignment */
	if (!IS_ALIGNED(stride, result->vb_format.vf_codec->vc_align) ||
	    !IS_ALIGNED((uintptr_t)mem, result->vb_format.vf_codec->vc_align))
		result->vb_format.vf_codec = result->vb_format.vf_codec->vc_nalgn;
	if (result->vb_format.vf_pal) {
		if unlikely(!(result->vb_format.vf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL)) {
			result->vb_format.vf_pal = NULL;
		} else {
			video_palette_incref(result->vb_format.vf_pal);
		}
	}
	return result;
err_r:
	free(result);
err:
	return NULL;
}

INTERN WUNUSED ATTR_IN(4) NONNULL((1, 6)) REF struct video_buffer *CC
libvideo_ramdomain_formem_ex(struct video_domain const *__restrict self, video_dim_t xdim, video_dim_t ydim,
                             struct video_codec_specs const *__restrict codec_specs,
                             struct video_palette *palette, void *mem, size_t stride,
                             void (CC *release_mem)(void *cookie, void *mem),
                             void *release_mem_cookie, unsigned int flags) {
	struct video_codec const *codec;
	REF struct video_codec_handle *codec_handle;
	REF struct video_rambuffer_formem_xcodec *result;
	struct video_rambuffer_requirements req;
	(void)flags;
	if unlikely(!xdim || !ydim)
		return_empty_buffer;

	codec = video_codec_fromspecs(codec_specs, &codec_handle);
	if unlikely(!codec)
		goto err;

	/* Ensure that the specified stride is great enough */
	(*codec->vc_rambuffer_requirements)(xdim, ydim, &req);
	if (stride < req.vbs_stride) {
		errno = EINVAL;
		goto err_codec;
	}

	/* Allocate heap memory for the buffer */
	result = (REF struct video_rambuffer_formem_xcodec *)malloc(sizeof(struct video_rambuffer_formem_xcodec));
	if unlikely(!result)
		goto err_codec;
	result->rbrv_dummy = libvideo_buffer_getdummy(req.vbs_bufsize);
	if unlikely(!result->rbrv_dummy)
		goto err_codec_r;
	result->rbrv_stride          = stride;
	result->rbrv_gfx.rbrvg_data  = (byte_t *)mem;
	result->rbrv_gfx.rbrvg_inuse = 0;
	result->rbfmxc_codec = codec_handle;
	result->vb_ops    = _rambuffer_formem_xcodec_ops();
	result->vb_domain = self;
	result->vb_refcnt = 1;
	result->vb_format.vf_codec    = codec;
	result->vb_format.vf_pal      = palette;
	result->vb_xdim = xdim;
	result->vb_ydim = ydim;
	result->rbfm_release_mem        = release_mem;
	result->rbfm_release_mem_cookie = release_mem_cookie;
	LIST_INIT(&result->rbfm_subregions_list);
	atomic_lock_init(&result->rbfm_subregions_lock);
	if (palette) {
		if unlikely(!(codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL)) {
			result->vb_format.vf_pal = NULL;
		} else {
			video_palette_incref(result->vb_format.vf_pal);
		}
	}

	/* Must use a different, fallback "codec" that can deal with bad alignment */
	if (!IS_ALIGNED(stride, result->vb_format.vf_codec->vc_align) ||
	    !IS_ALIGNED((uintptr_t)mem, result->vb_format.vf_codec->vc_align))
		result->vb_format.vf_codec = result->vb_format.vf_codec->vc_nalgn;
	return result;
err_codec_r:
	free(result);
err_codec:
	video_codec_handle_decref(codec_handle);
err:
	return NULL;
}

INTERN ATTR_RETNONNULL WUNUSED ATTR_IN(2) NONNULL((1)) struct video_codec const *CC
libvideo_ramdomain_supported_codec(struct video_domain const *__restrict self,
                                   struct video_codec const *__restrict codec) {
	/* Ram buffers support *all* codecs */
	COMPILER_IMPURE();
	(void)self;
	return codec;
}

/************************************************************************/



INTERN struct video_domain libvideo_ramdomain = {};

/* Returns the default, built-in "RAM" video domain.
 *
 * Video buffers allocated by / using this domain are driven
 * by  software-only  (without  any  hardware  acceleration)
 *
 * On the plus side: these buffers are generally able to do
 * much more than buffers from hardware domains, given that
 * they can support **any** video codec. */
DEFINE_PUBLIC_ALIAS(video_ramdomain, _libvideo_ramdomain);
INTERN /*ATTR_CONST*/ ATTR_RETNONNULL WUNUSED
struct video_domain const *CC _libvideo_ramdomain(void) {
	if unlikely(!libvideo_ramdomain.vd_newbuffer) {
		libvideo_ramdomain.vd_supported_codec = &libvideo_ramdomain_supported_codec;
		libvideo_ramdomain.vd_formem_ex       = &libvideo_ramdomain_formem_ex;
		libvideo_ramdomain.vd_formem          = &libvideo_ramdomain_formem;
		libvideo_ramdomain.vd_newbuffer_ex    = &libvideo_ramdomain_newbuffer_ex;
		COMPILER_WRITE_BARRIER();
		libvideo_ramdomain.vd_newbuffer = &libvideo_ramdomain_newbuffer;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_ramdomain;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_RAMDOMAIN_C */
