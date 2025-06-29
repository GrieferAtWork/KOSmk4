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

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <stddef.h>
#include <stdio.h>

#include <libvideo/gfx/buffer.h>

DECL_BEGIN

/************************************************************************/
/* Common format helpers                                                */
/************************************************************************/
enum filefmt {
	FMT_BAD,
#define FMT_FIRST FMT_PNG
	FMT_PNG,
	FMT_JPG,
	FMT_BMP,
	FMT_GIF,
#define FMT_LAST FMT_GIF
};

/* Determine the format named by `format' (returns "FMT_BAD" if unknown) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) enum filefmt CC
filefmt_detect(char const *__restrict format);

/* Write a video buffer */
INTDEF WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_fmt(struct video_buffer *__restrict self,
                         FILE *stream, char const *options,
                         enum filefmt fmt);





/* Various functions  for opening  a file/stream/blob  as an  image  file.
 * The actual file format is  auto-detected, and supported formats  depend
 * on installed 3rd party libraries. By default, BMP and PNG is supported. */
INTDEF WUNUSED REF struct video_buffer *CC
libvideo_buffer_mopen(void const *blob, size_t blob_size);
INTDEF WUNUSED REF struct video_buffer *CC
libvideo_buffer_fopen(FILE *__restrict fp);
INTDEF WUNUSED REF struct video_buffer *CC
libvideo_buffer_fdopen(fd_t fd);
INTDEF WUNUSED REF struct video_buffer *CC
libvideo_buffer_open(char const *filename);


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
 * @return: -1: Error (s.a. `errno') */
INTDEF WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_fsave(struct video_buffer *self, char const *format,
                      FILE *__restrict fp, char const *options);
INTDEF WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_fdsave(struct video_buffer *self, char const *format,
                       fd_t fd, char const *options);
INTDEF /*WUNUSED*/ NONNULL((1, 2)) int CC
libvideo_buffer_save(struct video_buffer *self, char const *filename,
                     char const *options);



/* Various functions for opening a file/stream/blob as an animation file.
 * The actual file format is auto-detected, and supported formats  depend
 * on installed 3rd party libraries. By default, GIF is supported.
 *
 * If the specified blob isn't for an animated video format, the file  is
 * instead opened using `video_buffer_open()', and the returned animation
 * will only have a single frame. */
INTDEF WUNUSED REF struct video_anim *CC
libvideo_anim_mopen(void const *blob, size_t blob_size);
INTDEF WUNUSED REF struct video_anim *CC
libvideo_anim_fopen(FILE *__restrict fp);
INTDEF WUNUSED REF struct video_anim *CC
libvideo_anim_fdopen(fd_t fd);
INTDEF WUNUSED REF struct video_anim *CC
libvideo_anim_open(char const *filename);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_H */
