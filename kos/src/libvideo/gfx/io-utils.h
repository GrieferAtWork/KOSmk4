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
#ifndef GUARD_LIBVIDEO_GFX_IO_UTILS_H
#define GUARD_LIBVIDEO_GFX_IO_UTILS_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libvideo/gfx/anim.h>
#include <libvideo/gfx/buffer.h>

#include "anim.h"

DECL_BEGIN

#if 0 /* TODO */
#define LIBPNG_APNG_SUPPORTED
#endif


/* Returned by `libvideo_buffer_open_*' when the blob doesn't match the specified format. */
#define VIDEO_BUFFER_WRONG_FMT ((REF struct video_buffer *)-1)
#define VIDEO_ANIM_WRONG_FMT   ((REF struct video_anim *)-1)
#define VIDEO_ANIM_NOTSUPP     ((REF struct video_anim *)-2) /* Only returned by "libvideo_anim_open_png" */



/* PNG */
INTDEF WUNUSED NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_open_png(struct video_domain const *__restrict domain_hint,
                         void const *blob, size_t blob_size);
INTDEF WUNUSED NONNULL((1, 2)) int CC
libvideo_surface_save_png(struct video_surface const *__restrict self,
                          FILE *stream, char const *options);
INTDEF WUNUSED NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_open_lodepng(struct video_domain const *__restrict domain_hint,
                             void const *blob, size_t blob_size);
INTDEF WUNUSED NONNULL((1, 2)) int CC
libvideo_surface_save_lodepng(struct video_surface const *__restrict self,
                              FILE *stream, char const *options);
#ifdef LIBPNG_APNG_SUPPORTED
INTDEF WUNUSED NONNULL((1)) REF struct video_anim *CC
libvideo_anim_open_png(struct video_domain const *__restrict domain,
                       void const *blob, size_t blob_size,
                       struct mapfile *p_mapfile);
#endif /* LIBPNG_APNG_SUPPORTED */



/* JPG */
INTDEF WUNUSED NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_open_jpg(struct video_domain const *__restrict domain_hint,
                         void const *blob, size_t blob_size);
INTDEF WUNUSED NONNULL((1, 2)) int CC
libvideo_surface_save_jpg(struct video_surface const *__restrict self,
                          FILE *stream, char const *options);



/* BMP
 * @param: p_mapfile: When  non-NULL, the function is allowed to assume
 *                    that the given blob is owned by this mapfile, and
 *                    is also allowed to steal that mapping by doing  a
 *                    bzero on `*p_mapfile' */
INTDEF WUNUSED NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_open_bmp(struct video_domain const *__restrict domain_hint,
                         void const *blob, size_t blob_size,
                         struct mapfile *p_mapfile);
INTDEF WUNUSED NONNULL((1, 2)) int CC
libvideo_surface_save_bmp(struct video_surface const *__restrict self,
                          FILE *stream, char const *options);



/* GIF */
INTDEF WUNUSED NONNULL((1)) REF struct video_anim *CC
libvideo_anim_open_gif(struct video_domain const *__restrict domain,
                       void const *blob, size_t blob_size,
                       struct mapfile *p_mapfile);


/* Lookup a named option "name" in a ','-separated options string "options" */
PRIVATE WUNUSED NONNULL((2)) long CC
libvideo_io_getoptl(char const *options, char const *name, long defval) {
	if (options) {
		size_t namelen = strlen(name);
		for (;;) {
			if (bcmp(options, name, namelen * sizeof(char)) == 0 &&
				options[namelen] == '=') {
				long result;
				options += namelen + 1;
				result = strtol(options, (char **)&options, 0);
				if (*options == '\0' || *options == ',')
					return result;
			}
			options = strchr(options, ',');
			if (!options)
				break;
			++options;
		}
	}
	return defval;
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
	if unlikely(video_buffer_getdomain(self) != domain) {
		REF struct video_buffer *converted;
		struct video_buffer_format result_format;
		struct video_surface const *surf = video_buffer_assurface(self);
		video_buffer_getformat(self, &result_format);
		result_format.vbf_codec = video_domain_supported_codec(domain, result_format.vbf_codec);
		converted = libvideo_surface_convert(surf, domain, &result_format);
		video_buffer_decref(self);
		self = converted;
	}
	return self;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_UTILS_H */
