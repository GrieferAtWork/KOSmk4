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

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/palette.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/types.h>

#include "buffer/ram.h"
#include "gfx-empty.h"
#include "ramdomain.h"

DECL_BEGIN


/************************************************************************/
/* RAM DOMAIN OPERATORS                                                 */
/************************************************************************/

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
	assert(self == &libvideo_ramdomain_);
	assert(format);
	(void)self;
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
	result->vb_ops    = _rambuffer_ops();
	result->vb_domain = &libvideo_ramdomain_;
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
	REF struct video_rambuffer__for_codec *result;
	struct video_rambuffer_requirements req;
	assert(self == &libvideo_ramdomain_);
	assert(codec_specs);
	(void)self;
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
	result = (REF struct video_rambuffer__for_codec *)malloc(sizeof(struct video_rambuffer__for_codec));
	if unlikely(!result)
		goto err_codec;
	result->rb_data = (flags & VIDEO_DOMAIN_NEWBUFFER_F_CALLOC)
	                  ? (byte_t *)calloc(req.vbs_bufsize)
	                  : (byte_t *)malloc(req.vbs_bufsize);
	if unlikely(!result->rb_data)
		goto err_codec_result;
	result->rb_stride = req.vbs_stride;
	result->rbfc_codec = codec_handle;
	result->vb_ops    = _rambuffer_ops__for_codec();
	result->vb_domain = &libvideo_ramdomain_;
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
	REF struct video_membuffer *result;
	struct video_rambuffer_requirements req;
	assert(self == &libvideo_ramdomain_);
	assert(format);
	(void)self;
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
	result = (REF struct video_membuffer *)malloc(sizeof(struct video_membuffer));
	if unlikely(!result)
		goto err;
	result->rb_stride = stride;
	result->rb_data   = (byte_t *)mem;
	result->vb_ops    = _membuffer_ops();
	result->vb_domain = &libvideo_ramdomain_;
	result->vb_refcnt = 1;
	result->vb_format = *format;
	result->vb_xdim   = xdim;
	result->vb_ydim   = ydim;
	result->vm_release_mem        = release_mem;
	result->vm_release_mem_cookie = release_mem_cookie;

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
	REF struct video_membuffer__for_codec *result;
	struct video_rambuffer_requirements req;
	assert(self == &libvideo_ramdomain_);
	(void)self;
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
	result = (REF struct video_membuffer__for_codec *)malloc(sizeof(struct video_membuffer__for_codec));
	if unlikely(!result)
		goto err_codec;
	result->rb_stride             = stride;
	result->rb_data               = (byte_t *)mem;
	result->vmfc_codec            = codec_handle;
	result->vb_ops                = _membuffer_ops();
	result->vb_domain             = &libvideo_ramdomain_;
	result->vb_refcnt             = 1;
	result->vb_format.vf_codec    = codec;
	result->vb_format.vf_pal      = palette;
	result->vb_xdim               = xdim;
	result->vb_ydim               = ydim;
	result->vm_release_mem        = release_mem;
	result->vm_release_mem_cookie = release_mem_cookie;
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
/*
err_codec_result:
	free(result);*/
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



INTERN struct video_domain libvideo_ramdomain_ = {};

/* Returns the default, built-in "RAM" video domain.
 *
 * Video buffers allocated by / using this domain are driven
 * by  software-only  (without  any  hardware  acceleration)
 *
 * On the plus side: these buffers are generally able to do
 * much more than buffers from hardware domains, given that
 * they can support **any** video codec. */
DEFINE_PUBLIC_ALIAS(video_ramdomain, libvideo_ramdomain);
INTERN /*ATTR_CONST*/ ATTR_RETNONNULL WUNUSED
struct video_domain const *CC libvideo_ramdomain(void) {
	if unlikely(!libvideo_ramdomain_.vd_newbuffer) {
		libvideo_ramdomain_.vd_supported_codec = &libvideo_ramdomain_supported_codec;
		libvideo_ramdomain_.vd_formem_ex       = &libvideo_ramdomain_formem_ex;
		libvideo_ramdomain_.vd_formem          = &libvideo_ramdomain_formem;
		libvideo_ramdomain_.vd_newbuffer_ex    = &libvideo_ramdomain_newbuffer_ex;
		COMPILER_WRITE_BARRIER();
		libvideo_ramdomain_.vd_newbuffer = &libvideo_ramdomain_newbuffer;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_ramdomain_;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_RAMDOMAIN_C */
