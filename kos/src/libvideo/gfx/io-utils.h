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

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libvideo/gfx/anim.h>
#include <libvideo/gfx/buffer.h>

DECL_BEGIN

/* Returned by `libvideo_buffer_open_*' when the blob doesn't match the specified format. */
#define VIDEO_BUFFER_WRONG_FMT ((REF struct video_buffer *)-1)
#define VIDEO_ANIM_WRONG_FMT   ((REF struct video_anim *)-1)



/* PNG */
INTDEF WUNUSED NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_open_png(struct video_domain const *__restrict domain_hint,
                         void const *blob, size_t blob_size);
INTDEF WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_png(struct video_buffer *__restrict self,
                         FILE *stream, char const *options);
INTDEF WUNUSED NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_open_lodepng(struct video_domain const *__restrict domain_hint,
                             void const *blob, size_t blob_size);
INTDEF WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_lodepng(struct video_buffer *__restrict self,
                             FILE *stream, char const *options);



/* JPG */
INTDEF WUNUSED NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_open_jpg(struct video_domain const *__restrict domain_hint,
                         void const *blob, size_t blob_size);
INTDEF WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_jpg(struct video_buffer *__restrict self,
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
libvideo_buffer_save_bmp(struct video_buffer *__restrict self,
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

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_UTILS_H */
