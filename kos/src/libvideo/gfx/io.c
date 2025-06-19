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
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>
#include <sys/mman.h>

#include <errno.h>
#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <libiberty.h>
#include <libvideo/gfx/buffer.h>
/**/

#include "io.h"
#include "io-utils.h"

/**/

/* Pull in individual format I/O impl */
#ifndef __INTELLISENSE__
#include "io/bmp.c.inl"
#include "io/jpg.c.inl"
#include "io/png-lodepng.c.inl"
#include "io/png.c.inl"
#endif /* !__INTELLISENSE__ */

DECL_BEGIN

enum fmt {
	FMT_BAD,
#define FMT_FIRST FMT_PNG
	FMT_PNG,
	FMT_JPG,
	FMT_BMP,
#define FMT_LAST FMT_BMP
};

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) enum fmt CC
detect_format(char const *name) {
	if (strcasecmp(name, "png") == 0)
		return FMT_PNG;
	if (strcasecmp(name, "jpg") == 0 ||
	    strcasecmp(name, "jpeg") == 0)
		return FMT_JPG;
	if (strcasecmp(name, "bmp") == 0)
		return FMT_BMP;
	return FMT_BAD;
}

PRIVATE ATTR_NOINLINE WUNUSED REF struct video_buffer *CC
libvideo_buffer_open_fmt(void const *blob, size_t blob_size,
                         struct mapfile *p_mapfile, enum fmt fmt) {
	switch (fmt) {
	case FMT_BAD:
		break;
	case FMT_PNG:
		return libvideo_buffer_open_png(blob, blob_size);
	case FMT_JPG:
		return libvideo_buffer_open_jpg(blob, blob_size);
	case FMT_BMP:
		return libvideo_buffer_open_bmp(blob, blob_size, p_mapfile);
	default: __builtin_unreachable();
	}
	errno = ENOTSUP;
	return NULL;
}

PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_fmt(struct video_buffer *__restrict self,
                         FILE *stream, char const *options,
                         enum fmt fmt) {
	switch (fmt) {
	case FMT_BAD:
		break;
	case FMT_PNG:
		return libvideo_buffer_save_png(self, stream, options);
	case FMT_JPG:
		return libvideo_buffer_save_jpg(self, stream, options);
	case FMT_BMP:
		return libvideo_buffer_save_bmp(self, stream, options);
	default: __builtin_unreachable();
	}
	errno = ENOTSUP;
	return -1;
}



PRIVATE ATTR_NOINLINE WUNUSED REF struct video_buffer *CC
libvideo_buffer_open_impl(void const *blob, size_t blob_size,
                          char const *format_hint, struct mapfile *p_mapfile) {
	REF struct video_buffer *result;
	enum fmt used_format, hinted_format = FMT_BAD;
	if (format_hint != NULL) {
		hinted_format = detect_format(format_hint);
		if (hinted_format != FMT_BAD) {
			result = libvideo_buffer_open_fmt(blob, blob_size, p_mapfile, hinted_format);
			if (result != VIDEO_BUFFER_WRONG_FMT)
				return result;
		}
	}
	for (used_format = FMT_FIRST;
	     (unsigned int)used_format <= (unsigned int)FMT_LAST;
	     used_format = (enum fmt)((unsigned int)used_format + 1)) {
		if (used_format == hinted_format)
			continue; /* Already tried this one... */
		result = libvideo_buffer_open_fmt(blob, blob_size, p_mapfile, used_format);
		if (result != VIDEO_BUFFER_WRONG_FMT)
			return result;
	}
	/* Unsupported file format, or not an image file */
	errno = ENOTSUP;
	return NULL;
}

PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1, 2, 3)) int CC
libvideo_buffer_save_impl(struct video_buffer *__restrict self,
                          char const *format,
                          FILE *stream, char const *options) {
	enum fmt used_format = detect_format(format);
	return libvideo_buffer_save_fmt(self, stream, options, used_format);
}



/* Various functions  for opening  a file/stream/blob  as an  image  file.
 * The actual file format is  auto-detected, and supported formats  depend
 * on installed 3rd party libraries. By default, BMP and PNG is supported. */
DEFINE_PUBLIC_ALIAS(video_buffer_mopen, libvideo_buffer_mopen);
INTERN WUNUSED REF struct video_buffer *CC
libvideo_buffer_mopen(void const *blob, size_t blob_size) {
	return libvideo_buffer_open_impl(blob, blob_size, NULL, NULL);
}

DEFINE_PUBLIC_ALIAS(video_buffer_fopen, libvideo_buffer_fopen);
INTERN WUNUSED REF struct video_buffer *CC
libvideo_buffer_fopen(FILE *__restrict fp) {
	struct mapfile mf;
	REF struct video_buffer *result;
	if (ffmapfile(&mf, fp, 0, 0, (size_t)-1, 0, 0))
		return NULL;
	result = libvideo_buffer_open_impl(mf.mf_addr, mf.mf_size, NULL, &mf);
	(void)unmapfile(&mf);
	return result;
}

DEFINE_PUBLIC_ALIAS(video_buffer_fdopen, libvideo_buffer_fdopen);
INTERN WUNUSED REF struct video_buffer *CC
libvideo_buffer_fdopen(fd_t fd) {
	struct mapfile mf;
	REF struct video_buffer *result;
	if (fmapfile(&mf, fd, 0, 0, (size_t)-1, 0, 0))
		return NULL;
	result = libvideo_buffer_open_impl(mf.mf_addr, mf.mf_size, NULL, &mf);
	(void)unmapfile(&mf);
	return result;
}

DEFINE_PUBLIC_ALIAS(video_buffer_open, libvideo_buffer_open);
INTERN WUNUSED REF struct video_buffer *CC
libvideo_buffer_open(char const *filename) {
	struct mapfile mf;
	char const *format_hint;
	REF struct video_buffer *result;
	if (mapfile(&mf, filename, 0, 0,
	            (size_t)-1, 0, 0))
		return NULL;
	format_hint = strrchr(filename, '.');
	if (format_hint)
		++format_hint;
	result = libvideo_buffer_open_impl(mf.mf_addr, mf.mf_size, format_hint, &mf);
	(void)unmapfile(&mf);
	return result;
}



/* Do the inverse of `video_buffer_*open' and save the contents of a video buffer
 * into  a file/memory/stream. The same set of  file formats is supported as also
 * supported by `video_buffer_*open', and the intended file format is  determined
 * by the given `format' argument, which should be the case-insensitive extension
 * (without a leading ".") of the format (e.g. "png" for PNG files).
 * @param: self:     The video buffer to save to a file.
 * @param: format:   The format to use for the output file written.
 * @param: fp/fd:    Output file descriptor / stdio-stream
 * @param: filename: Output filename ("format" is detected from file extension)
 * @param: options:  ","-separated string of format-specific encoding  options.
 *                   Available options are not explicitly document here, so you
 *                   need  to look at  the source to see  what's there. You may
 *                   simply pass `NULL' to use defaults for everything.
 * @return: 0 : Success
 * @return: -1: [errno=ENOTSUP] Unsupported `format'
 * @return: -1: [errno=ENOTSUP] Unsupported parameter in `options'
 * @return: -1: Error (s.a. `errno') */
DEFINE_PUBLIC_ALIAS(video_buffer_fsave, libvideo_buffer_fsave);
INTERN WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_fsave(struct video_buffer *self, char const *format,
                      FILE *__restrict fp, char const *options) {
	return libvideo_buffer_save_impl(self, format, fp, options);
}

DEFINE_PUBLIC_ALIAS(video_buffer_fdsave, libvideo_buffer_fdsave);
INTERN WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_fdsave(struct video_buffer *self, char const *format,
                       fd_t fd, char const *options) {
	int result;
	FILE *stream = fdopen(fd, "wb");
	if unlikely(!stream)
		return -1;
	unlock_stream(stream);
	result = libvideo_buffer_save_impl(self, format, stream, options);
	(void)frelease(stream);
	(void)fclose(stream);
	return result;
}

DEFINE_PUBLIC_ALIAS(video_buffer_save, libvideo_buffer_save);
INTERN /*WUNUSED*/ NONNULL((1, 2)) int CC
libvideo_buffer_save(struct video_buffer *self,
                     char const *filename,
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
	result = libvideo_buffer_save_impl(self, format, stream, options);
	(void)fclose(stream);
	if (result != 0) /* Delete broken file on error. */
		(void)unlink(filename);
	return result;
}



DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_C */
