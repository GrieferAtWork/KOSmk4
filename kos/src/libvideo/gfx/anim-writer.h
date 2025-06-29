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
#ifndef GUARD_LIBVIDEO_GFX_ANIM_WRITER_H
#define GUARD_LIBVIDEO_GFX_ANIM_WRITER_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <stdio.h>

#include <libvideo/gfx/anim.h>

DECL_BEGIN

/* Common video animation writer destroy function (call this from yours last) */
INTDEF NONNULL((1)) void
NOTHROW(CC video_anim_writer_destroy_common)(struct video_anim_writer *__restrict self);

/* Various functions for writing a video animation files.
 * @param: size_x:         Animation canvas X dimension
 * @param: size_y:         Animation canvas Y dimension
 * @param: format:         Case-insensitive file format that should be used for output (e.g. "gif" for gif files)
 * @param: fp/fd/filename: Location where animation data should be streamed to
 * @param: options:        Optional format-specific options (','-separated string of "NAME=VALUE"; not documented here)
 * @return: * :   A writer that can be fed with data on each frame of the animation
 * @return: NULL: [errno=EINVAL] Unsupported `format'
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=*] Some other error */
INTDEF WUNUSED NONNULL((3, 4)) REF struct video_anim_writer *CC
libvideo_anim_fsave(video_dim_t size_x, video_dim_t size_y,
                    char const *format, FILE *__restrict fp, char const *options);
INTDEF WUNUSED NONNULL((3)) REF struct video_anim_writer *CC
libvideo_anim_fdsave(video_dim_t size_x, video_dim_t size_y,
                     char const *format, fd_t fd, char const *options);
INTDEF WUNUSED NONNULL((3)) REF struct video_anim_writer *CC
libvideo_anim_save(video_dim_t size_x, video_dim_t size_y,
                   char const *filename, char const *options);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_ANIM_WRITER_H */
