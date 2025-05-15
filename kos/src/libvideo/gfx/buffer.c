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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_C
#define GUARD_LIBVIDEO_GFX_BUFFER_C 1
#define _KOS_SOURCE 1

#include "buffer.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "empty-buffer.h"
#include "gfx.h"
#include "ram-buffer.h"

DECL_BEGIN

/* Create a video buffer, or return NULL and set errno if creation failed.
 * NOTE: When the given `size_x' or `size_y' is ZERO(0), an empty buffer is returned
 *       which may not necessarily use the  given, or default `codec' and  `palette'
 * @param: codec:   The preferred video codec, or NULL to use `video_preferred_format()'.
 * @param: palette: The palette to use (only needed if used by `codec') */
INTERN WUNUSED /*REF*/ struct video_buffer *CC
libvideo_buffer_create(unsigned int type, size_t size_x, size_t size_y,
                       struct video_codec const *codec, struct video_palette *palette) {
	struct video_buffer *result;
	/* Check for special case: empty video buffer. */
	if unlikely(!size_x || !size_y)
		return incref(libvideo_getemptybuffer());
	if (!codec) {
		/* Lookup the default format. */
		struct video_format const *default_format;
		default_format = libvideo_preferred_format();
		codec          = default_format->vf_codec;
		palette        = default_format->vf_pal;
	}
	switch (type) {

	case VIDEO_BUFFER_AUTO:
	case VIDEO_BUFFER_RAM:
		result = libvideo_rambuffer_create(size_x, size_y,
		                                   codec, palette);
		break;

//TODO:	case VIDEO_BUFFER_GPU:
//TODO:		break;

	default:
		/* Unknown buffer type. */
		errno = EINVAL;
		result = NULL;
		break;
	}
	return result;
}


#if 0
PRIVATE NONNULL((1)) void LIBVIDEO_CODEC_CC
screen_pal_destroy(struct video_palette *__restrict self) {
	free(self->vp_cache);
	free(self);
}

PRIVATE struct video_rambuffer *screen_buffer = NULL;
#endif


/* Returns a video buffer for the entire screen (or return NULL and set errno on error)
 * Note that  screen buffer  access  is only  granted to  ROOT  and the  window  server */
INTERN WUNUSED /*REF*/ struct video_buffer *CC
libvideo_buffer_screen(void) {
#if 1
	/* TODO: Re-implement for svga */
	errno = ENOSYS;
	return NULL;
#else
	fd_t driver;
	struct video_rambuffer *result;
	struct vd_format format;
	result = screen_buffer; /* TODO: This needs a lock! */
	if likely(result) {
		incref(result);
		return result;
	}
	driver = libvideo_driver();
	if unlikely(driver < 0)
		goto err;
	if (ioctl(driver, VIDEOIO_GETFORMAT, &format) < 0)
		goto err;

	/* Allocate the video buffer. */
	result = (struct video_rambuffer *)malloc(sizeof(struct video_rambuffer));
	if unlikely(!result)
		goto err;
	result->vb_format.vf_pal = NULL;

	/* Lookup the video format described by the codec. */
	result->vb_format.vf_codec = video_codec_lookup(format.vdf_codec);
	if unlikely(!result->vb_format.vf_codec) {
		errno = ENOTSUP;
		goto err_r;
	}

	/* Construct a palette (if necessary) */
	if (VIDEO_CODEC_HASPAL(format.vdf_codec)) {
		struct video_palette *pal;
		struct vd_pal_struct getpal;
		size_t count = VIDEO_CODEC_PALSIZ(format.vdf_codec);
		pal = (struct video_palette *)malloc(offsetof(struct video_palette, vp_pal.vdp_pal) +
		                                     (count * sizeof(vd_color_t)));
		if unlikely(!pal)
			goto err_r;
		result->vb_format.vf_pal = pal;
		pal->vp_destroy = &screen_pal_destroy;
		pal->vp_refcnt  = 1;
		pal->vp_cache   = NULL;
		pal->vp_cnt = count;
		/* Load the current palette. */
		getpal.vp_codec = format.vdf_codec;
		getpal.vp_pal   = &pal->vp_pal;
		if (ioctl(driver, VIDEOIO_GETPAL, &getpal) < 0)
			goto err;
	}
	result->vb_stride = format.vdf_scan;
	result->vb_refcnt = 1;
	result->vb_ops    = rambuffer_getops_munmap();
	result->vb_size_x = format.vdf_resx;
	result->vb_size_y = format.vdf_resy;
	result->vb_total  = format.vdf_scan * format.vdf_resy;
	result->vb_data = (byte_t *)mmap(NULL, result->vb_total,
	                                 PROT_READ | PROT_WRITE,
	                                 MAP_PRIVATE | MAP_FILE,
	                                 driver, 0);
	if (result->vb_data == (byte_t *)MAP_FAILED)
		goto err_r;
	if (!atomic_cmpxch(&screen_buffer, NULL, result)) { /* TODO: This needs a lock! */
		(*result->vb_ops->vi_destroy)(result);
		result = screen_buffer;
	}
	incref(result);
	return result;
err_r:
	free(result->vb_format.vf_pal);
	free(result);
err:
	return NULL;
#endif
}


PRIVATE struct video_format preferred_video_format;

/* Return the preferred video format.
 * If  possible, this format will match the format used by the host's graphics card.
 * If no graphics card exists, or the card isn't clear on its preferred format, some
 * other, common format will be returned instead. */
INTERN ATTR_RETNONNULL WUNUSED struct video_format const *CC
libvideo_preferred_format(void) {
	struct video_format *result;
	result = &preferred_video_format;
	if (!result->vf_codec) {
		struct video_codec const *codec;
		/* TODO: Ask the bound video driver for its preferred format. */
		COMPILER_IMPURE();
		codec = video_codec_lookup(VIDEO_CODEC_RGBA8888);
		result->vf_pal = NULL;
		assert(codec != NULL);
		COMPILER_WRITE_BARRIER();
		result->vf_codec = codec;
	}
	return result;
}


PRIVATE fd_t libvideo_driver_fd = -1;

/* Return a handle for the video device driver that is being used.
 * @return: -1:errno=ENODEV: No video driver found */
INTERN WUNUSED fd_t LIBVIDEO_GFX_CC libvideo_driver(void) {
	fd_t result;
	char const *vd_driver;
	result = libvideo_driver_fd;
	if likely(result >= 0)
		return result;
	if unlikely(result == -2) {
		/* Special case: No video driver could be found. */
		errno = ENODEV;
		return -1;
	}
	vd_driver = getenv("VD_DRIVER");
	if (vd_driver) {
		result = open(vd_driver, O_RDONLY | O_CLOEXEC);
		if (result >= 0)
			goto done;
	}
	result = open("/dev/video", O_RDONLY | O_CLOEXEC);
	if (result >= 0)
		goto done;
	/* Only use stdin as fallback!
	 * By  default, we should  check for environment variables,
	 * as well as try to make use of `/dev/video', which should
	 * be the default video driver. */
	result = STDIN_FILENO;
done:
	if (!atomic_cmpxch(&libvideo_driver_fd, -1, result)) {
		close(result);
		COMPILER_READ_BARRIER();
		result = libvideo_driver_fd;
	}
	return result;
}



DEFINE_PUBLIC_ALIAS(video_buffer_create, libvideo_buffer_create);
DEFINE_PUBLIC_ALIAS(video_buffer_screen, libvideo_buffer_screen);
DEFINE_PUBLIC_ALIAS(video_preferred_format, libvideo_preferred_format);
DEFINE_PUBLIC_ALIAS(video_driver, libvideo_driver);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_C */
