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
#ifndef GUARD_LIBVIDEO_GFX_IO_H
#define GUARD_LIBVIDEO_GFX_IO_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <stddef.h>
#include <stdio.h>

#include <libvideo/gfx/anim.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

DECL_BEGIN

/************************************************************************/
/* Common format helpers                                                */
/************************************************************************/
enum filefmt {
	FMT_BAD,
#define FMT_FIRST FMT_PNG
	FMT_PNG, /* TODO: Enable support for animated PNGs */
	FMT_JPG,
	FMT_BMP,
	FMT_GIF, /* TODO: Writer backend, and support animation writers in general */
	/* TODO: TIFF */
	/* TODO: TGA */
	/* TODO: WEBP */
	/* TODO: PSD (read-only) */
	/* TODO: SVG (read-only)
	 *       Should come with some more, general support for vector  graphics,
	 *       including allowing the caller to specify an intended  resolution,
	 *       as well as allowing them to render to a given buffer, rather than
	 *       having to load the image as its own buffer. */
#define FMT_LAST FMT_GIF
};

/* Determine the format named by `format' (returns "FMT_BAD" if unknown) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) enum filefmt CC
filefmt_detect(char const *__restrict format);

/* Write a video buffer */
INTDEF WUNUSED NONNULL((1, 2)) int CC
libvideo_surface_save_fmt(struct video_surface const *__restrict self,
                          FILE *stream, char const *options,
                          enum filefmt fmt);





/* Various functions  for opening  a file/stream/blob  as an  image  file.
 * The actual file format is  auto-detected, and supported formats  depend
 * on installed 3rd party libraries. By default, BMP and PNG is supported. */
INTDEF WUNUSED ATTR_INS(2, 3) NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_mopen(struct video_domain const *__restrict domain,
                      void const *blob, size_t blob_size);
INTDEF WUNUSED NONNULL((1, 2)) REF struct video_buffer *CC
libvideo_buffer_fopen(struct video_domain const *__restrict domain, FILE *__restrict fp);
INTDEF WUNUSED NONNULL((1)) REF struct video_buffer *CC
libvideo_buffer_fdopen(struct video_domain const *__restrict domain, fd_t fd);
INTDEF WUNUSED NONNULL((1, 2)) REF struct video_buffer *CC
libvideo_buffer_open(struct video_domain const *__restrict domain,
                     char const *filename);


/* Same  as  `video_buffer_*save', but  save pixel
 * data using the palette and GFX flags of `self'.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF WUNUSED ATTR_IN(1) NONNULL((2)) int CC
libvideo_surface_fsave(struct video_surface const *self, char const *format,
                       FILE *__restrict fp, char const *options);
INTDEF WUNUSED ATTR_IN(1) NONNULL((2)) int CC
libvideo_surface_fdsave(struct video_surface const *self, char const *format,
                        fd_t fd, char const *options);
INTDEF /*WUNUSED*/ ATTR_IN(1) NONNULL((2)) int CC
libvideo_surface_save(struct video_surface const *self, char const *filename,
                      char const *options);


/* Same as `video_buffer_*save', but save pixel data from the
 * Clip Rect of `self'. Values written for pixels outside the
 * I/O Rect of `self'  are format-specific, but those  pixels
 * are probably going to be either black, or transparent.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF WUNUSED ATTR_IN(1) NONNULL((2)) int CC
libvideo_gfx_fsave(struct video_gfx const *self, char const *format,
                   FILE *__restrict fp, char const *options);
INTDEF WUNUSED ATTR_IN(1) NONNULL((2)) int CC
libvideo_gfx_fdsave(struct video_gfx const *self, char const *format,
                    fd_t fd, char const *options);
INTDEF /*WUNUSED*/ ATTR_IN(1) NONNULL((2)) int CC
libvideo_gfx_save(struct video_gfx const *self, char const *filename,
                  char const *options);



/* Various functions for opening a file/stream/blob as an animation file.
 * The actual file format is auto-detected, and supported formats  depend
 * on installed 3rd party libraries. By default, GIF is supported.
 *
 * If the specified blob isn't for an animated video format, the file  is
 * instead opened using `video_buffer_open()', and the returned animation
 * will only have a single frame. */
INTDEF WUNUSED ATTR_INS(2, 3) NONNULL((1)) REF struct video_anim *CC
libvideo_anim_mopen(struct video_domain const *__restrict domain,
                    void const *blob, size_t blob_size);
INTDEF WUNUSED NONNULL((1, 2)) REF struct video_anim *CC
libvideo_anim_fopen(struct video_domain const *__restrict domain, FILE *__restrict fp);
INTDEF WUNUSED NONNULL((1)) REF struct video_anim *CC
libvideo_anim_fdopen(struct video_domain const *__restrict domain, fd_t fd);
INTDEF WUNUSED NONNULL((1, 2)) REF struct video_anim *CC
libvideo_anim_open(struct video_domain const *__restrict domain,
                   char const *filename);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_H */
