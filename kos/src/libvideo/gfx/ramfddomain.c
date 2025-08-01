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
#ifndef GUARD_LIBVIDEO_GFX_RAMFDDOMAIN_C
#define GUARD_LIBVIDEO_GFX_RAMFDDOMAIN_C 1
#define __VIDEO_BUFFER_const /* nothing */
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"
/**/

#include <libvideo/gfx/api.h>

#ifdef CONFIG_LIBVIDEO_HAVE_RAMFD
#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <kos/anno.h>
#include <kos/io.h>
#include <kos/ioctl/file.h>
#include <kos/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <libvideo/crect.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/buffer/rambuffer.h>
#include <libvideo/gfx/buffer/ramfdbuffer.h>
#include <libvideo/gfx/codec/codec.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/gfx/surface.h>
#include <libvideo/types.h>

#include "buffer.h"
#include "buffer/utils.h"
#include "codec/palette.h"
#include "gfx-empty.h"
#include "ramdomain.h"
#include "ramfddomain.h"
#include "serial.h"

DECL_BEGIN

/* Ask the kernel to create a sub-region of "fd" */
PRIVATE WUNUSED fd_t CC
file_newsubregion(fd_t fd,
                  /*page-aligned*/ uint64_t minaddr,
                  /*page-aligned*/ uint64_t num_bytes) {
	struct file_subregion sr;
	bzero(&sr, sizeof(sr));
	sr.fsr_minaddr = minaddr;
	if (OVERFLOW_UADD(minaddr, num_bytes - 1, &sr.fsr_maxaddr))
		goto err_range;
	sr.fsr_resfd.of_mode  = OPENFD_MODE_AUTO;
	sr.fsr_resfd.of_flags = IO_CLOEXEC;
	if unlikely(ioctl(fd, FILE_IOC_SUBREGION, &sr) < 0)
		goto err;
	return sr.fsr_resfd.of_hint;
err_range:
	errno = ERANGE;
err:
	return -1;
}


/************************************************************************/
/* RAM DOMAIN OPERATORS                                                 */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(video_ramfdbuffer_ops, _ramfdbuffer_ops);
DEFINE_PUBLIC_ALIAS(video_ramfdbuffer_subregion_ops, _ramfdbuffer_subregion_ops);
DEFINE_PUBLIC_ALIAS(video_ramfdbuffer_subregion_rem_ops, _ramfdbuffer_subregion_rem_ops);

DEFINE_VIDEO_BUFFER_TYPE(ramfdbuffer_ops, ramfdbuffer__destroy,
                         rambuffer__initgfx, rambuffer__updategfx,
                         rambuffer__lock, rambuffer__lock, libvideo_buffer_noop__unlock,
                         rambuffer__lockregion, rambuffer__lockregion, libvideo_buffer_noop__unlockregion,
                         libvideo_buffer_noop__revoke, ramfdbuffer__subregion);
DEFINE_VIDEO_BUFFER_TYPE(ramfdbuffer_subregion_ops, ramfdbuffer__destroy,
                         rambuffer__initgfx, rambuffer__updategfx,
                         rambuffer__lock, rambuffer__lock, libvideo_buffer_noop__unlock,
                         rambuffer__lockregion, rambuffer__lockregion, libvideo_buffer_noop__unlockregion,
                         ramfdbuffer_subregion__revoke, ramfdbuffer__subregion);
DEFINE_VIDEO_BUFFER_TYPE(ramfdbuffer_subregion_rem_ops, ramfdbuffer_subregion_rem__destroy,
                         ramfdbuffer_subregion_rem__initgfx, ramfdbuffer_subregion_rem__updategfx,
                         libvideo_buffer_notsup__rlock, libvideo_buffer_notsup__wlock, libvideo_buffer_noop__unlock,
                         ramfdbuffer_subregion_rem__lockregion, ramfdbuffer_subregion_rem__lockregion, libvideo_buffer_noop__unlockregion,
                         ramfdbuffer_subregion_rem__revoke, ramfdbuffer_subregion_rem__subregion);



/************************************************************************/
/* RAMFDBUFFER OPERATORS                                                */
/************************************************************************/

/* DESTROY */
INTERN NONNULL((1)) void FCC
ramfdbuffer__destroy(struct video_buffer *__restrict self) {
	struct video_ramfdbuffer *me = (struct video_ramfdbuffer *)self;
	(void)munmap(me->rb_data, me->rfdb_total);
	(void)close(me->rfdb_fd);
	__video_buffer_fini_common(me);
	free(me);
}

INTERN NONNULL((1)) void FCC
ramfdbuffer_subregion_rem__destroy(struct video_buffer *__restrict self) {
	struct video_ramfdbuffer_subregion_rem *me;
	me = (struct video_ramfdbuffer_subregion_rem *)self;
	decref_likely(me->rfdbsr_base);
	__video_buffer_fini_common(me);
	free(me);
}

/* REVOKE+SUBREGION */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC ramfdbuffer_subregion__revoke)(struct video_buffer *__restrict self) {
	/* This is where the magic happens: this ioctl causes the kernel to
	 * recursively delete all memory mappings created by the sub-region
	 * or its descendants, and replace them with /dev/void */
	struct video_ramfdbuffer *me = (struct video_ramfdbuffer *)self;
	ioctl(me->rfdb_fd, FILE_IOC_DELREGION);
	return me;
}

INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *
NOTHROW(FCC ramfdbuffer_subregion_rem__revoke)(struct video_buffer *__restrict self) {
	struct video_ramfdbuffer_subregion_rem *me;
	me = (struct video_ramfdbuffer_subregion_rem *)self;
	ramfdbuffer_subregion__revoke(me->rfdbsr_base);
	return me;
}

PRIVATE WUNUSED NONNULL((1)) REF struct video_ramfdbuffer_subregion_rem *FCC
ramfdbuffer__addrem(/*inherit(always)*/REF struct video_ramfdbuffer *__restrict self,
                    video_coord_t xrem) {
	REF struct video_ramfdbuffer_subregion_rem *result;
	result = (REF struct video_ramfdbuffer_subregion_rem *)malloc(sizeof(struct video_ramfdbuffer_subregion_rem));
	if unlikely(!result)
		goto err_self;
	result->vb_surf  = self->vb_surf;
	result->vb_codec = self->vb_codec;
	__video_buffer_init_ops(result, _ramfdbuffer_subregion_rem_ops());
	__video_buffer_init_domain(result, video_buffer_getdomain(self));
	__video_buffer_init_dim(result,
	                        video_buffer_getxdim(self) - xrem,
	                        video_buffer_getydim(self));
	__video_buffer_init_common(result);
	result->rfdbsr_base  = self; /* Inherit reference */
	result->rfdbsr_bxrem = xrem;
	return result;
err_self:
	ramfdbuffer__destroy(self);
	return NULL;
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
ramfdbuffer__subregion(struct video_surface const *__restrict self,
                       struct video_crect const *__restrict rect) {
	size_t ps = getpagesize(), pm = ps - 1;
	REF struct video_ramfdbuffer *result;
	struct video_rambuffer_requirements req;
	struct video_ramfdbuffer *me = (struct video_ramfdbuffer *)video_surface_getbuffer(self);
	struct video_codec *codec = video_buffer_getcodec(me);
	video_coord_t xrem;
	size_t region_offset, region_size;
	size_t aligned_region_offset, aligned_region_size;
	size_t aligned_region_boff;
	video_buffer_assert_rect(me, rect);
	video_codec_xcoord_to_offset(codec, video_crect_getxmin(rect),
	                             &region_offset, &xrem);
	(*codec->vc_rambuffer_requirements)(video_crect_getxdim(rect) + xrem,
	                                    video_crect_getydim(rect), &req);
	region_offset += (uintptr_t)me->rb_data & pm;
	region_offset += video_crect_getymin(rect) * me->rb_stride;
	region_size = ((video_crect_getydim(rect) - 1) * me->rb_stride);
	assert(req.vbs_stride <= me->rb_stride);
	region_size += req.vbs_stride; /* Last scanline doesn't need to be full-length */
	/* region_offset: byte-offset from "me->rfdb_fd" to top-left corner of sub-region,
	 *                though  said sub-region  still needs  to strip  the first "xrem"
	 *                pixels on the left side of the buffer.
	 * region_size:   The total # of bytes that must be mappable by the sub-region, starting at `region_offset' */

	/* Align region parameters to whole pages */
	aligned_region_offset = region_offset;
	/* byte-offset where mapping of sub-region starts (will
	 * re-appear as low N bits of mapping in result buffer) */
	aligned_region_boff = aligned_region_offset & pm;
	aligned_region_offset &= ~pm;
	aligned_region_size = region_size;
	aligned_region_size += aligned_region_boff;
	aligned_region_size += pm;
	aligned_region_size &= ~pm;

	/* Allocate result buffer. */
	result = (REF struct video_ramfdbuffer *)malloc(sizeof(struct video_ramfdbuffer));
	if unlikely(!result)
		goto err;

	/* Create the actual sub-region */
	result->rfdb_fd = file_newsubregion(me->rfdb_fd, aligned_region_offset, aligned_region_size);
	if unlikely(result->rfdb_fd < 0)
		goto err_r;

	/* Map the new sub-region into memory. For this purpose,
	 * have the mapping start at `aligned_region_boff' bytes
	 * from the start of the sub-region (thus accounting for
	 * the necessary sub-page offset) */
	result->rb_data = (byte_t *)mmap(NULL, region_size, PROT_READ | PROT_WRITE,
	                                 MAP_FILE | MAP_SHARED, result->rfdb_fd,
	                                 aligned_region_boff);
	if unlikely(result->rb_data == (byte_t *)MAP_FAILED)
		goto err_r_fd;
	result->rfdb_total = region_size;
	result->rb_stride  = me->rb_stride;

	/* Initialize meta-data & remaining fields */
	__video_buffer_init_subregion(result, self, me, rect);
	__video_buffer_init_ops(result, _ramfdbuffer_subregion_ops());
	__video_buffer_init_common(result);

	/* If there is still some remaining X-offset, then that has to be applied as well */
	if (xrem != 0)
		return ramfdbuffer__addrem(result, xrem);
	return result;
/*
err_r_fd_data:
	(void)munmap(result->rb_data, result->rfdb_total);*/
err_r_fd:
	(void)close(result->rfdb_fd);
err_r:
	free(result);
err:
	return NULL;
}

INTERN WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC
ramfdbuffer_subregion_rem__subregion(struct video_surface const *__restrict self,
                                     struct video_crect const *__restrict rect) {
	struct video_surface used_surface = *self;
	struct video_crect used_rect = *rect;
	struct video_ramfdbuffer_subregion_rem *me;
	me = (struct video_ramfdbuffer_subregion_rem *)video_surface_getbuffer(self);
	video_crect_addx(&used_rect, me->rfdbsr_bxrem);
	used_surface.vs_buffer = me->rfdbsr_base;
	return ramfdbuffer__subregion(&used_surface, rect);
}

/* LOCK */
INTERN ATTR_INOUT(1) NONNULL((2)) int FCC
ramfdbuffer_subregion_rem__lockregion(struct video_buffer *__restrict self,
                                      struct video_regionlock *__restrict lock) {
	struct video_ramfdbuffer_subregion_rem *me;
	me = (struct video_ramfdbuffer_subregion_rem *)self;
	video_crect_addx(&lock->_vrl_rect, me->rfdbsr_bxrem);
	return rambuffer__lockregion(me->rfdbsr_base, lock);
}

/* GFX */
INTERN ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC
ramfdbuffer_subregion_rem__initgfx(struct video_gfx *__restrict self) {
	struct video_ramfdbuffer_subregion_rem *me;
	video_offset_t xrem, yrem;
	me = (struct video_ramfdbuffer_subregion_rem *)video_gfx_getbuffer(self);
	self = (*(self->vg_surf.vs_buffer = me->rfdbsr_base)->vb_ops->vi_initgfx)(self);
	xrem = me->rfdbsr_bxrem;
	yrem = 0;
	if (video_gfx_getflags(self) & VIDEO_GFX_F_XYSWAP) {
		yrem = xrem;
		xrem = 0;
	}
	self = video_gfx_clip(self, xrem, yrem,
	                      video_gfx_getxdim(self),
	                      video_gfx_getydim(self));
	return self;
}

#define return_empty_buffer                                      \
	do {                                                         \
		struct video_buffer *_empty_res = &libvideo_emptybuffer; \
		video_buffer_incref(_empty_res);                         \
		return _empty_res;                                       \
	}	__WHILE0

/* RAMFD DOMAIN OPERATORS */
INTERN WUNUSED NONNULL((1)) ATTR_IN(2) REF struct video_buffer *CC
libvideo_ramfddomain_newbuffer(struct video_domain const *__restrict self,
                               struct video_buffer_format const *__restrict format,
                               video_dim_t xdim, video_dim_t ydim, unsigned int flags) {
	REF struct video_ramfdbuffer *result;
	struct video_rambuffer_requirements req;
	assert(format);
	(void)flags;
	if unlikely(!xdim || !ydim)
		return_empty_buffer;

	/* Figure out buffer requirements. */
	(*format->vbf_codec->vc_rambuffer_requirements)(xdim, ydim, &req);

	/* Allocate heap memory for the buffer */
	result = (REF struct video_ramfdbuffer *)malloc(sizeof(struct video_ramfdbuffer));
	if unlikely(!result)
		goto err;

	/* Initialize meta-data */
	if unlikely(!__video_buffer_init_format(result, format)) {
		errno = EINVAL;
		goto err_r;
	}
	__video_buffer_init_domain(result, self);
	__video_buffer_init_ops(result, _ramfdbuffer_ops());
	__video_buffer_init_dim(result, xdim, ydim);

	/* Allocate+size ramfd file descriptor */
	result->rfdb_fd = memfd_create("vmem", MFD_CLOEXEC);
	if unlikely(result->rfdb_fd < 0)
		goto err_r;
	if unlikely(ftruncate(result->rfdb_fd, req.vbs_bufsize))
		goto err_r_fd;

	/* Map memfd into memory */
	result->rb_data = (byte_t *)mmap(NULL, req.vbs_bufsize, PROT_READ | PROT_WRITE,
	                                 MAP_FILE | MAP_SHARED, result->rfdb_fd, 0);
	if unlikely(result->rb_data == (byte_t *)MAP_FAILED)
		goto err_r_fd;
	result->rfdb_total = req.vbs_bufsize;
	result->rb_stride  = req.vbs_stride;
	__video_buffer_init_common(result);
	return result;
/*
err_r_fd_data:
	(void)munmap(result->rb_data, result->rfdb_total);*/
err_r_fd:
	(void)close(result->rfdb_fd);
err_r:
	free(result);
err:
	return NULL;
}
/************************************************************************/


/* Returns the default, built-in "RAM-FD" video domain. */
INTERN struct video_domain libvideo_ramfddomain = {};
DEFINE_PUBLIC_ALIAS(video_ramfddomain, _libvideo_ramfddomain);
INTERN /*ATTR_CONST*/ ATTR_RETNONNULL WUNUSED struct video_domain const *CC
_libvideo_ramfddomain(void) {
	if unlikely(!libvideo_ramfddomain.vd_newbuffer) {
		libvideo_ramfddomain.vd_newpalette      = &libvideo_generic_palette_create;
		libvideo_ramfddomain.vd_supported_codec = &libvideo_ramdomain_supported_codec;
		libvideo_ramfddomain.vd_formem          = &libvideo_ramdomain_formem;
#ifdef CONFIG_LIBVIDEO_HAVE_SERIALIZATION
		libvideo_ramdomain.vd_deserialize = &libvideo_generic_deserialize;
#endif /* CONFIG_LIBVIDEO_HAVE_SERIALIZATION */
		COMPILER_WRITE_BARRIER();
		libvideo_ramfddomain.vd_newbuffer = &libvideo_ramfddomain_newbuffer;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_ramfddomain;
}

DECL_END
#endif /* CONFIG_LIBVIDEO_HAVE_RAMFD */

#endif /* !GUARD_LIBVIDEO_GFX_RAMFDDOMAIN_C */
