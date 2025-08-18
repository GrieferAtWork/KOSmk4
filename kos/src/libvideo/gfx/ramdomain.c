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
#define __VIDEO_BUFFER_const /* nothing */
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>

#include <libvideo/crect.h>
#include <libvideo/gfx/api.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/buffer/rambuffer.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/surface.h>
#include <libvideo/types.h>

#include "buffer.h"
#include "buffer/empty.h"
#include "codec/palette.h"
#include "ramdomain.h"
#include "serial.h"

DECL_BEGIN


/************************************************************************/
/* RAM DOMAIN OPERATORS                                                 */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(video_rambuffer_ops, _rambuffer_ops);
DEFINE_PUBLIC_ALIAS(video_rambuffer_formem_ops, _rambuffer_formem_ops);
DEFINE_PUBLIC_ALIAS(video_rambuffer_subregion_ops, _rambuffer_subregion_ops);
DEFINE_PUBLIC_ALIAS(video_rambuffer_subregion_norem_ops, _rambuffer_subregion_norem_ops);

DEFINE_VIDEO_BUFFER_TYPE(rambuffer_ops, &rambuffer__destroy,
                         &rambuffer__initgfx, &rambuffer__updategfx,
                         &rambuffer__lock, &rambuffer__lock, &libvideo_buffer_noop__unlock,
                         &rambuffer__lockregion, &rambuffer__lockregion, &libvideo_buffer_noop__unlockregion,
                         NULL, &libvideo_buffer_noop__revoke, &rambuffer__subregion);
DEFINE_VIDEO_BUFFER_TYPE(rambuffer_formem_ops, &rambuffer_formem__destroy,
                         &rambuffer__initgfx, &rambuffer__updategfx,
                         &rambuffer__lock, &rambuffer__lock, &libvideo_buffer_noop__unlock,
                         &rambuffer__lockregion, &rambuffer__lockregion, &libvideo_buffer_noop__unlockregion,
                         NULL, &libvideo_buffer_noop__revoke, &rambuffer__subregion);
DEFINE_VIDEO_BUFFER_TYPE(rambuffer_subregion_ops, &rambuffer_subregion__destroy,
                         &rambuffer_subregion__initgfx, &rambuffer_subregion__updategfx,
                         &libvideo_buffer_notsup__rlock, &libvideo_buffer_notsup__wlock, &libvideo_buffer_noop__unlock,
                         &rambuffer_subregion__lockregion, &rambuffer_subregion__lockregion, &libvideo_buffer_noop__unlockregion,
                         NULL, &libvideo_buffer_noop__revoke, &rambuffer_subregion__subregion);
DEFINE_VIDEO_BUFFER_TYPE(rambuffer_subregion_norem_ops, &rambuffer_subregion__destroy,
                         &rambuffer_subregion__initgfx, &rambuffer_subregion__updategfx,
                         &rambuffer__lock, &rambuffer__lock, &libvideo_buffer_noop__unlock,
                         &rambuffer__lockregion, &rambuffer__lockregion, &libvideo_buffer_noop__unlockregion,
                         NULL, &libvideo_buffer_noop__revoke, &rambuffer_subregion__subregion);


/* Video buffer types used to represent ram buffers.
 * NOTE: None of these ever look at `video_buffer::vb_domain',
 *       so you're free to  re-use these at the  driver-level! */

/* DESTROY */
INTERN NONNULL((1)) void FCC
rambuffer__destroy(struct video_buffer *__restrict self) {
	struct video_rambuffer *me = (struct video_rambuffer *)self;
	free(me->rb_data);
	__video_buffer_fini_common(me);
	free(me);
}

INTERN NONNULL((1)) void FCC
rambuffer_formem__destroy(struct video_buffer *__restrict self) {
	struct video_rambuffer_formem *me = (struct video_rambuffer_formem *)self;
	(*me->rbfm_release_mem)(me->rbfm_release_mem_cookie, me->rb_data);
	__video_buffer_fini_common(me);
	free(me);
}

INTERN NONNULL((1)) void FCC
rambuffer_subregion__destroy(struct video_buffer *__restrict self) {
	struct video_rambuffer_subregion *me = (struct video_rambuffer_subregion *)self;
	video_buffer_decref(me->rbs_base);
	__video_buffer_fini_common(me);
	free(me);
}


/* REVOKE+SUBREGION */

/* Common base for creation a sub-region. Caller must still:
 * - Add `return' to the chain of sub-regions of `self' (thus initializing `return->rbrvsr_chain')
 * - Fill in `return->vb_ops'
 * - Fill in `return->rbrvsr_xflags'
 * - Adjust `return->rb_data'
 */
PRIVATE WUNUSED ATTR_IN(1) ATTR_INOUT(2) ATTR_IN(3) REF struct video_rambuffer_subregion *FCC
rambuffer__subregion__common(struct video_surface const *__restrict surface,
                             struct video_rambuffer *__restrict self,
                             struct video_crect const *__restrict rect) {
	size_t x_byte_offset;
	REF struct video_rambuffer_subregion *result;
	video_buffer_assert_rect(self, rect);
	result = (REF struct video_rambuffer_subregion *)malloc(sizeof(struct video_rambuffer_subregion));
	if unlikely(!result)
		goto err;
	__video_buffer_init_subregion(result, surface, self, rect);
	result->rbs_bxrem = video_crect_getxmin(rect);
	x_byte_offset = (*video_buffer_getcodec(result)->vc_coord2bytes)(&result->rbs_bxrem);
	__video_buffer_init_ops(result, result->rbs_bxrem ? _rambuffer_subregion_ops()
	                                                  : _rambuffer_subregion_norem_ops());
	result->rb_data   = self->rb_data + x_byte_offset + video_crect_getymin(rect) * self->rb_stride;
	result->rb_stride = self->rb_stride;
	result->rbs_base  = self;
	video_buffer_incref(self);
	result->rbs_xoff = video_crect_getxmin(rect);
	result->rbs_yoff = video_crect_getymin(rect);
	result->rbs_xend = video_crect_getxend(rect);
	result->rbs_yend = video_crect_getyend(rect);
	__video_buffer_init_common(result);
	return result;
err:
	return NULL;
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
rambuffer__subregion(struct video_surface const *__restrict self,
                     struct video_crect const *__restrict rect) {
	struct video_rambuffer *me = (struct video_rambuffer *)video_surface_getbuffer(self);
	return rambuffer__subregion__common(self, me, rect);
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
rambuffer_subregion__subregion(struct video_surface const *__restrict self,
                               struct video_crect const *__restrict rect) {
	struct video_rambuffer_subregion *me = (struct video_rambuffer_subregion *)video_surface_getbuffer(self);
	struct video_crect abs_rect = *rect;
	video_crect_addx(&abs_rect, me->rbs_xoff);
	video_crect_addy(&abs_rect, me->rbs_yoff);
	return rambuffer__subregion__common(self, me->rbs_base, &abs_rect);
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
	video_regionlock_assert(me, lock);
	lock->vrl_lock.vl_data   = me->rb_data + video_crect_getymin(&lock->_vrl_rect) * me->rb_stride;
	lock->vrl_lock.vl_stride = me->rb_stride;
	lock->vrl_xbas = video_crect_getxmin(&lock->_vrl_rect);
	return 0;
}

INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
rambuffer_subregion__lockregion(struct video_buffer *__restrict self,
                                struct video_regionlock *__restrict lock) {
	struct video_rambuffer_subregion *me = (struct video_rambuffer_subregion *)self;
	video_regionlock_assert(me, lock);
	lock->vrl_lock.vl_data   = me->rb_data + video_crect_getymin(&lock->_vrl_rect) * me->rb_stride;
	lock->vrl_lock.vl_stride = me->rb_stride;
	lock->vrl_xbas = video_crect_getxmin(&lock->_vrl_rect) + me->rbs_bxrem;
	return 0;
}



INTERN WUNUSED NONNULL((1)) ATTR_IN(2) REF struct video_buffer *CC
libvideo_ramdomain_newbuffer(struct video_domain const *__restrict self,
                             struct video_buffer_format const *__restrict format,
                             video_dim_t xdim, video_dim_t ydim, unsigned int flags) {
	REF struct video_rambuffer *result;
	struct video_rambuffer_requirements req;
	assert(format);
	if unlikely(!xdim || !ydim)
		return _libvideo_emptybufferref();

	/* Figure out buffer requirements. */
	(*format->vbf_codec->vc_rambuffer_requirements)(xdim, ydim, &req);

	/* Allocate heap memory for the buffer */
	result = (REF struct video_rambuffer *)malloc(sizeof(struct video_rambuffer));
	if unlikely(!result)
		goto err;

	/* Initialize meta-data */
	if unlikely(!__video_buffer_init_format(result, format)) {
		errno = EINVAL;
		goto err_r;
	}
	__video_buffer_init_domain(result, self);
	__video_buffer_init_ops(result, _rambuffer_ops());
	__video_buffer_init_dim(result, xdim, ydim);

	/* Allocate buffer data */
	result->rb_data = (flags & VIDEO_DOMAIN_NEWBUFFER_F_CALLOC)
	                  ? (byte_t *)calloc(req.vbs_bufsize)
	                  : (byte_t *)malloc(req.vbs_bufsize);
	if unlikely(!result->rb_data)
		goto err_r;
	result->rb_stride = req.vbs_stride;
	__video_buffer_init_common(result);
	return result;
/*
err_r_data:
	free(result->rb_data);*/
err_r:
	free(result);
err:
	return NULL;
}

INTERN WUNUSED NONNULL((1, 5)) ATTR_IN(2) REF struct video_buffer *CC
libvideo_ramdomain_formem(struct video_domain const *__restrict self,
                          struct video_buffer_format const *__restrict format,
                          video_dim_t xdim, video_dim_t ydim, void *mem, size_t stride,
                          void (CC *release_mem)(void *cookie, void *mem),
                          void *release_mem_cookie, unsigned int flags) {
	struct video_codec *codec = format->vbf_codec;
	REF struct video_rambuffer_formem *result;
	struct video_rambuffer_requirements req;
	assert(format);
	(void)flags;
	if unlikely(!xdim || !ydim)
		return _libvideo_emptybufferref();

	/* Ensure that the specified stride is great enough */
	(*codec->vc_rambuffer_requirements)(xdim, ydim, &req);
	if (stride < req.vbs_stride) {
		errno = EINVAL;
		return NULL;
	}

	/* Allocate heap memory for the buffer */
	result = (REF struct video_rambuffer_formem *)malloc(sizeof(struct video_rambuffer_formem));
	if unlikely(!result)
		goto err;
	if unlikely(!__video_buffer_init_format(result, format)) {
		errno = EINVAL;
		goto err_r;
	}

	/* Must use a different, fallback "codec" that can deal with bad alignment */
	assert(codec == format->vbf_codec);
	if (!IS_ALIGNED(stride, codec->vc_align) ||
	    !IS_ALIGNED((uintptr_t)mem, codec->vc_align))
		result->vb_codec = codec->vc_nalgn;

	/* Validate palette configuration */
	__video_buffer_init_domain(result, self);
	__video_buffer_init_ops(result, _rambuffer_formem_ops());
	__video_buffer_init_dim(result, xdim, ydim);
	result->rb_data   = (byte_t *)mem;
	result->rb_stride = stride;
	result->rbfm_release_mem        = release_mem;
	result->rbfm_release_mem_cookie = release_mem_cookie;
	__video_buffer_init_common(result);
	return result;
err_r:
	free(result);
err:
	return NULL;
}

INTERN ATTR_RETNONNULL WUNUSED ATTR_IN(2) NONNULL((1)) struct video_codec *CC
libvideo_ramdomain_supported_codec(struct video_domain const *__restrict self,
                                   struct video_codec const *__restrict codec) {
	/* Ram buffers support *all* codecs */
	COMPILER_IMPURE();
	(void)self;
	return (struct video_codec *)codec;
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
		libvideo_ramdomain.vd_newpalette      = &libvideo_generic_palette_create;
		libvideo_ramdomain.vd_supported_codec = &libvideo_ramdomain_supported_codec;
		libvideo_ramdomain.vd_formem          = &libvideo_ramdomain_formem;
#ifdef CONFIG_LIBVIDEO_HAVE_SERIALIZATION
		libvideo_ramdomain.vd_deserialize = &libvideo_generic_deserialize;
#endif /* CONFIG_LIBVIDEO_HAVE_SERIALIZATION */
		COMPILER_WRITE_BARRIER();
		libvideo_ramdomain.vd_newbuffer = &libvideo_ramdomain_newbuffer;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_ramdomain;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_RAMDOMAIN_C */
