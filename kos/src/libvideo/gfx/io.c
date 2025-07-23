/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif(x -> x.startswith("-O"));
gcc_opt.append("-O3"); // Force _all_ optimizations because stuff in here is performance-critical
]]]*/
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
#ifndef GUARD_LIBVIDEO_GFX_IO_C
#define GUARD_LIBVIDEO_GFX_IO_C 1
#define __VIDEO_BUFFER_const /*nothing */
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>
#include <sys/mman.h>

#include <errno.h>
#include <malloca.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <libvideo/gfx/anim.h>
#include <libvideo/gfx/buffer.h>

#include "anim.h"
#include "buffer.h"
#include "io-utils.h"
#include "io.h"

/* Pull in individual format I/O impl */
#ifndef __INTELLISENSE__
#include "io/bmp.c.inl"
#include "io/gif.c.inl"
#include "io/jpg.c.inl"
#include "io/png-lodepng.c.inl"
#include "io/png.c.inl"
#endif /* !__INTELLISENSE__ */

/* FIXME: <libiberty.h> defines "free()" in a way that is incompatible if <stdlib.h> is included later */
#include <libiberty.h>

DECL_BEGIN

INTERN ATTR_PURE WUNUSED NONNULL((1)) enum filefmt CC
filefmt_detect(char const *__restrict format) {
	if (strcasecmp(format, "png") == 0)
		return FMT_PNG;
	if (strcasecmp(format, "jpg") == 0 ||
	    strcasecmp(format, "jpeg") == 0)
		return FMT_JPG;
	if (strcasecmp(format, "bmp") == 0)
		return FMT_BMP;
	if (strcasecmp(format, "gif") == 0)
		return FMT_GIF;
	return FMT_BAD;
}

PRIVATE ATTR_NOINLINE REF struct video_buffer *CC
anim2frame(REF struct video_anim *anim) {
	REF struct video_buffer *result;
	struct video_anim_frame *frame;
	if (!anim || anim == VIDEO_ANIM_WRONG_FMT)
		return (REF struct video_buffer *)anim;

	/* Create temp. buffer for animation frame */
	frame = (struct video_anim_frame *)malloca(video_anim_sizeof_frame(anim));
	if unlikely(!frame)
		goto err;

	/* Load first animation frame */
	if unlikely(video_anim_firstframe(anim, frame))
		goto err_frame;

	/* Take first frame */
	result = frame->vaf_frame;
	video_buffer_incref(result);

	/* Finalize frame reader and animation */
	video_anim_frame_fini(frame);
	freea(frame);
	video_anim_decref(anim);

	/* Return first frame */
	return result;
err_frame:
	freea(frame);
err:
	return NULL;
}

PRIVATE REF struct video_anim *CC
frame2anim(REF struct video_buffer *frame) {
	REF struct video_anim *result;
	if (!frame || frame == VIDEO_BUFFER_WRONG_FMT)
		return (REF struct video_anim *)frame;
	result = libvideo_anim_fromframe(frame);
	video_buffer_decref(frame);
	return result;
}

PRIVATE WUNUSED NONNULL((1, 2)) REF struct video_buffer *CC
convert_to_wanted_domain(struct video_domain const *__restrict domain,
                         /*inherit(always)*/ REF struct video_buffer *__restrict self) {
	if unlikely(self->vb_domain != domain) {
		REF struct video_buffer *converted;
		struct video_buffer_format result_format;
		video_buffer_getformat(self, &result_format);
		result_format.vbf_codec = video_domain_supported_codec(domain, result_format.vbf_codec);
		converted = libvideo_surface_convert(video_buffer_assurface(self), domain, &result_format);
		video_buffer_decref(self);
		self = converted;
	}
	return self;
}

PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1)) ATTR_INS(2, 3) REF struct video_buffer *CC
libvideo_buffer_open_fmt(struct video_domain const *__restrict domain,
                         void const *blob, size_t blob_size,
                         struct mapfile *p_mapfile, enum filefmt fmt) {
	REF struct video_buffer *result;
	switch (fmt) {
	case FMT_PNG:
		result = libvideo_buffer_open_png(domain, blob, blob_size);
		break;
	case FMT_JPG:
		result = libvideo_buffer_open_jpg(domain, blob, blob_size);
		break;
	case FMT_BMP:
		result = libvideo_buffer_open_bmp(domain, blob, blob_size, p_mapfile);
		break;
	case FMT_GIF:
		result = anim2frame(libvideo_anim_open_gif(domain, blob, blob_size, p_mapfile));
		break;
	default:
		errno = ENOTSUP;
		return NULL;
	}
	if (result && result != VIDEO_BUFFER_WRONG_FMT)
		result = convert_to_wanted_domain(domain, result);
	return result;
}

PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1)) REF struct video_anim *CC
libvideo_anim_open_fmt(struct video_domain const *__restrict domain,
                       void const *blob, size_t blob_size,
                       struct mapfile *p_mapfile, enum filefmt fmt) {
	REF struct video_buffer *frame;
	switch (fmt) {
	case FMT_PNG:
		/* TODO: Use the (now-apng-patched) libpng to support animated PNG files */
		frame = libvideo_buffer_open_png(domain, blob, blob_size);
		break;
	case FMT_JPG:
		frame = libvideo_buffer_open_jpg(domain, blob, blob_size);
		break;
	case FMT_BMP:
		frame = libvideo_buffer_open_bmp(domain, blob, blob_size, p_mapfile);
		break;
	case FMT_GIF:
		return libvideo_anim_open_gif(domain, blob, blob_size, p_mapfile);
	default:
		errno = ENOTSUP;
		return NULL;
	}
	if (frame && frame != VIDEO_BUFFER_WRONG_FMT)
		frame = convert_to_wanted_domain(domain, frame);
	return frame2anim(frame);
}

INTERN ATTR_NOINLINE WUNUSED NONNULL((1, 2)) int CC
libvideo_surface_save_fmt(struct video_surface const *__restrict self,
                          FILE *stream, char const *options,
                          enum filefmt fmt) {
	switch (fmt) {
	case FMT_PNG:
		return libvideo_surface_save_png(self, stream, options);
	case FMT_JPG:
		return libvideo_surface_save_jpg(self, stream, options);
	case FMT_BMP:
		return libvideo_surface_save_bmp(self, stream, options);
		/* TODO: GIF */
	default: break;
	}
	errno = ENOTSUP;
	return -1;
}



PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1)) ATTR_INS(2, 3) REF struct video_buffer *CC
libvideo_buffer_open_impl(struct video_domain const *__restrict domain,
                          void const *blob, size_t blob_size,
                          char const *format_hint, struct mapfile *p_mapfile) {
	REF struct video_buffer *result;
	enum filefmt used_format, hinted_format = FMT_BAD;
	if (format_hint != NULL) {
		hinted_format = filefmt_detect(format_hint);
		if (hinted_format != FMT_BAD) {
			result = libvideo_buffer_open_fmt(domain, blob, blob_size, p_mapfile, hinted_format);
			if (result != VIDEO_BUFFER_WRONG_FMT)
				return result;
		}
	}
	for (used_format = FMT_FIRST;
	     (unsigned int)used_format <= (unsigned int)FMT_LAST;
	     used_format = (enum filefmt)((unsigned int)used_format + 1)) {
		if (used_format == hinted_format)
			continue; /* Already tried this one... */
		result = libvideo_buffer_open_fmt(domain, blob, blob_size, p_mapfile, used_format);
		if (result != VIDEO_BUFFER_WRONG_FMT)
			return result;
	}
	/* Unsupported file format, or not an image file */
	errno = ENOTSUP;
	return NULL;
}

PRIVATE ATTR_NOINLINE ATTR_INS(2, 3) NONNULL((1)) WUNUSED REF struct video_anim *CC
libvideo_anim_open_impl(struct video_domain const *__restrict domain,
                        void const *blob, size_t blob_size,
                        char const *format_hint, struct mapfile *p_mapfile) {
	REF struct video_anim *result;
	enum filefmt used_format, hinted_format = FMT_BAD;
	if (format_hint != NULL) {
		hinted_format = filefmt_detect(format_hint);
		if (hinted_format != FMT_BAD) {
			result = libvideo_anim_open_fmt(domain, blob, blob_size, p_mapfile, hinted_format);
			if (result != VIDEO_ANIM_WRONG_FMT)
				return result;
		}
	}
	for (used_format = FMT_FIRST;
	     (unsigned int)used_format <= (unsigned int)FMT_LAST;
	     used_format = (enum filefmt)((unsigned int)used_format + 1)) {
		if (used_format == hinted_format)
			continue; /* Already tried this one... */
		result = libvideo_anim_open_fmt(domain, blob, blob_size, p_mapfile, used_format);
		if (result != VIDEO_ANIM_WRONG_FMT)
			return result;
	}
	/* Unsupported file format, or not an image file */
	errno = ENOTSUP;
	return NULL;
}



/* Various functions  for opening  a file/stream/blob  as an  image  file.
 * The actual file format is  auto-detected, and supported formats  depend
 * on installed 3rd party libraries. By default, BMP and PNG is supported. */
DEFINE_PUBLIC_ALIAS(video_buffer_mopen, libvideo_buffer_mopen);
INTERN WUNUSED ATTR_INS(2, 3) NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_mopen(struct video_domain const *__restrict domain,
                      void const *blob, size_t blob_size) {
	return libvideo_buffer_open_impl(domain, blob, blob_size, NULL, NULL);
}

DEFINE_PUBLIC_ALIAS(video_buffer_fopen, libvideo_buffer_fopen);
INTERN WUNUSED NONNULL((1, 2)) REF struct video_buffer *CC
libvideo_buffer_fopen(struct video_domain const *__restrict domain, FILE *__restrict fp) {
	struct mapfile mf;
	REF struct video_buffer *result;
	if (ffmapfile(&mf, fp, 0, 0, (size_t)-1, 0, 0))
		return NULL;
	result = libvideo_buffer_open_impl(domain, mf.mf_addr, mf.mf_size, NULL, &mf);
	(void)unmapfile(&mf);
	return result;
}

DEFINE_PUBLIC_ALIAS(video_buffer_fdopen, libvideo_buffer_fdopen);
INTERN WUNUSED NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_fdopen(struct video_domain const *__restrict domain, fd_t fd) {
	struct mapfile mf;
	REF struct video_buffer *result;
	if (fmapfile(&mf, fd, 0, 0, (size_t)-1, 0, 0))
		return NULL;
	result = libvideo_buffer_open_impl(domain, mf.mf_addr, mf.mf_size, NULL, &mf);
	(void)unmapfile(&mf);
	return result;
}

DEFINE_PUBLIC_ALIAS(video_buffer_open, libvideo_buffer_open);
INTERN WUNUSED NONNULL((1, 2)) REF struct video_buffer *CC
libvideo_buffer_open(struct video_domain const *__restrict domain, char const *filename) {
	struct mapfile mf;
	char const *format_hint;
	REF struct video_buffer *result;
	if (mapfile(&mf, filename, 0, 0,
	            (size_t)-1, 0, 0))
		return NULL;
	format_hint = strrchr(filename, '.');
	if (format_hint)
		++format_hint;
	result = libvideo_buffer_open_impl(domain, mf.mf_addr, mf.mf_size, format_hint, &mf);
	(void)unmapfile(&mf);
	return result;
}




/* Same  as  `video_buffer_*save', but  save pixel
 * data using the palette and GFX flags of `self'.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
DEFINE_PUBLIC_ALIAS(video_surface_fsave, libvideo_surface_fsave);
INTERN ATTR_NOINLINE WUNUSED ATTR_IN(1) NONNULL((2)) int CC
libvideo_surface_fsave(struct video_surface const *self, char const *format,
                       FILE *__restrict fp, char const *options) {
	enum filefmt used_format = filefmt_detect(format);
	return libvideo_surface_save_fmt(self, fp, options, used_format);
}

DEFINE_PUBLIC_ALIAS(video_surface_fdsave, libvideo_surface_fdsave);
INTERN WUNUSED ATTR_IN(1) NONNULL((2)) int CC
libvideo_surface_fdsave(struct video_surface const *self, char const *format,
                        fd_t fd, char const *options) {
	int result;
	FILE *stream = fdopen(fd, "wb");
	if unlikely(!stream)
		return -1;
	unlock_stream(stream);
	result = libvideo_surface_fsave(self, format, stream, options);
	(void)frelease(stream);
	(void)fclose(stream);
	return result;
}

DEFINE_PUBLIC_ALIAS(video_surface_save, libvideo_surface_save);
INTERN /*WUNUSED*/ ATTR_IN(1) NONNULL((2)) int CC
libvideo_surface_save(struct video_surface const *self, char const *filename,
                      char const *options) {
	int result;
	char const *format;
	FILE *stream;
	format = strrchr(filename, '.');
	if unlikely(!format) {
		errno = EINVAL; /* Missing file extension */
		return -1;
	}
	++format;
	stream = fopen(filename, "wb");
	if unlikely(!stream)
		return -1;
	unlock_stream(stream);
	result = libvideo_surface_fsave(self, format, stream, options);
	(void)fclose(stream);
	if (result != 0) /* Delete broken file on error. */
		(void)unlink(filename);
	return result;
}




/* Same as `video_buffer_*save', but save pixel data from the
 * Clip Rect of `self'. Values written for pixels outside the
 * I/O Rect of `self'  are format-specific, but those  pixels
 * are probably going to be either black, or transparent.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
DEFINE_PUBLIC_ALIAS(video_gfx_fsave, libvideo_gfx_fsave);
INTERN WUNUSED ATTR_IN(1) NONNULL((2)) int CC
libvideo_gfx_fsave(struct video_gfx const *self, char const *format,
                   FILE *__restrict fp, char const *options) {
	int result;
	REF struct video_buffer *buffer;
	buffer = libvideo_gfx_asbuffer(self);
	if unlikely(!buffer)
		goto err;
	result = libvideo_surface_fsave(video_buffer_assurface(buffer),
	                                format, fp, options);
	video_buffer_decref(buffer);
	return result;
err:
	return -1;
}

DEFINE_PUBLIC_ALIAS(video_gfx_fdsave, libvideo_gfx_fdsave);
INTERN WUNUSED ATTR_IN(1) NONNULL((2)) int CC
libvideo_gfx_fdsave(struct video_gfx const *self, char const *format,
                    fd_t fd, char const *options) {
	int result;
	REF struct video_buffer *buffer;
	buffer = libvideo_gfx_asbuffer(self);
	if unlikely(!buffer)
		goto err;
	result = libvideo_surface_fdsave(video_buffer_assurface(buffer),
	                                 format, fd, options);
	video_buffer_decref(buffer);
	return result;
err:
	return -1;
}

DEFINE_PUBLIC_ALIAS(video_gfx_save, libvideo_gfx_save);
INTERN /*WUNUSED*/ ATTR_IN(1) NONNULL((2)) int CC
libvideo_gfx_save(struct video_gfx const *self, char const *filename,
                  char const *options) {
	int result;
	REF struct video_buffer *buffer;
	buffer = libvideo_gfx_asbuffer(self);
	if unlikely(!buffer)
		goto err;
	result = libvideo_surface_save(video_buffer_assurface(buffer),
	                               filename, options);
	video_buffer_decref(buffer);
	return result;
err:
	return -1;
}




/* Various functions for opening a file/stream/blob as an animation file.
 * The actual file format is auto-detected, and supported formats  depend
 * on installed 3rd party libraries. By default, GIF is supported.
 *
 * If the specified blob isn't for an animated video format, the file  is
 * instead opened using `video_buffer_open()', and the returned animation
 * will only have a single frame. */
DEFINE_PUBLIC_ALIAS(video_anim_mopen, libvideo_anim_mopen);
INTERN WUNUSED ATTR_INS(2, 3) NONNULL((1)) REF struct video_anim *CC
libvideo_anim_mopen(struct video_domain const *__restrict domain,
                    void const *blob, size_t blob_size) {
	return libvideo_anim_open_impl(domain, blob, blob_size, NULL, NULL);
}

DEFINE_PUBLIC_ALIAS(video_anim_fopen, libvideo_anim_fopen);
INTERN WUNUSED NONNULL((1, 2)) REF struct video_anim *CC
libvideo_anim_fopen(struct video_domain const *__restrict domain, FILE *__restrict fp) {
	struct mapfile mf;
	REF struct video_anim *result;
	if (ffmapfile(&mf, fp, 0, 0, (size_t)-1, 0, 0))
		return NULL;
	result = libvideo_anim_open_impl(domain, mf.mf_addr, mf.mf_size, NULL, &mf);
	(void)unmapfile(&mf);
	return result;
}

DEFINE_PUBLIC_ALIAS(video_anim_fdopen, libvideo_anim_fdopen);
INTERN WUNUSED NONNULL((1)) REF struct video_anim *CC
libvideo_anim_fdopen(struct video_domain const *__restrict domain, fd_t fd) {
	struct mapfile mf;
	REF struct video_anim *result;
	if (fmapfile(&mf, fd, 0, 0, (size_t)-1, 0, 0))
		return NULL;
	result = libvideo_anim_open_impl(domain, mf.mf_addr, mf.mf_size, NULL, &mf);
	(void)unmapfile(&mf);
	return result;
}

DEFINE_PUBLIC_ALIAS(video_anim_open, libvideo_anim_open);
INTERN WUNUSED NONNULL((1, 2)) REF struct video_anim *CC
libvideo_anim_open(struct video_domain const *__restrict domain, char const *filename) {
	struct mapfile mf;
	char const *format_hint;
	REF struct video_anim *result;
	if (mapfile(&mf, filename, 0, 0,
	            (size_t)-1, 0, 0))
		return NULL;
	format_hint = strrchr(filename, '.');
	if (format_hint)
		++format_hint;
	result = libvideo_anim_open_impl(domain, mf.mf_addr, mf.mf_size, format_hint, &mf);
	(void)unmapfile(&mf);
	return result;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_C */
