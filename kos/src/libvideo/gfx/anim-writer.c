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
#ifndef GUARD_LIBVIDEO_GFX_ANIM_WRITER_C
#define GUARD_LIBVIDEO_GFX_ANIM_WRITER_C 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <libvideo/gfx/anim.h>

#include "anim-writer.h"
#include "io.h"

DECL_BEGIN

/* Common video animation writer destroy function (call this from yours last) */
INTERN NONNULL((1)) void
NOTHROW(CC video_anim_writer_destroy_common)(struct video_anim_writer *__restrict self) {
	if (self->vaw_owned_fp) {
		if (self->vaw_release_fp)
			(void)frelease(self->vaw_owned_fp);
		(void)fclose(self->vaw_owned_fp);
	}
	if (self->vaw_outfile) {
		(void)unlink(self->vaw_outfile);
		free(self->vaw_outfile);
	}
	free(self);
}


PRIVATE ATTR_NOINLINE WUNUSED NONNULL((4)) REF struct video_anim_writer *CC
libvideo_anim_fsave_impl(video_dim_t size_x, video_dim_t size_y, enum filefmt fmt,
                         FILE *__restrict fp, char const *options) {
	/* TODO */
	(void)size_x;
	(void)size_y;
	(void)fmt;
	(void)fp;
	(void)options;
	errno = ENOSYS;
	return NULL;
}



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
DEFINE_PUBLIC_ALIAS(video_anim_fsave, libvideo_anim_fsave);
INTERN WUNUSED NONNULL((3, 4)) REF struct video_anim_writer *CC
libvideo_anim_fsave(video_dim_t size_x, video_dim_t size_y,
                    char const *format, FILE *__restrict fp, char const *options) {
	enum filefmt fmt = filefmt_detect(format);
	return libvideo_anim_fsave_impl(size_x, size_y, fmt, fp, options);
}

DEFINE_PUBLIC_ALIAS(video_anim_fdsave, libvideo_anim_fdsave);
INTERN WUNUSED NONNULL((3)) REF struct video_anim_writer *CC
libvideo_anim_fdsave(video_dim_t size_x, video_dim_t size_y,
                     char const *format, fd_t fd, char const *options) {
	REF struct video_anim_writer *result;
	FILE *fp = fdopen(fd, "wb");
	if unlikely(!fp)
		goto err;
	result = libvideo_anim_fsave(size_x, size_y, format, fp, options);
	if unlikely(!result)
		goto err_fp;
	assert(!result->vaw_release_fp);
	assert(!result->vaw_owned_fp);
	assert(!result->vaw_outfile);
	assert(result->vaw_fp == fp);
	result->vaw_release_fp = true;
	result->vaw_owned_fp   = fp; /* Inherit */
	return result;
err_fp:
	(void)frelease(fp);
	(void)fclose(fp);
err:
	return NULL;
}

DEFINE_PUBLIC_ALIAS(video_anim_save, libvideo_anim_save);
INTERN WUNUSED NONNULL((3)) REF struct video_anim_writer *CC
libvideo_anim_save(video_dim_t size_x, video_dim_t size_y,
                   char const *filename, char const *options) {
	REF struct video_anim_writer *result;
	char *filename_dup;
	char const *format;
	FILE *fp;
	format = strrchr(filename, '.');
	if unlikely(!format) {
		errno = EINVAL; /* Missing file extension */
		return NULL;
	}
	++format; /* Skip leading '.' */
	filename_dup = strdup(filename);
	if unlikely(!filename_dup)
		goto err;
	fp = fopen(filename_dup, "wb");
	if unlikely(!fp)
		goto err_filename_dup;
	result = libvideo_anim_fsave(size_x, size_y, format, fp, options);
	if unlikely(!result)
		goto err_filename_dup_fp_unlink;
	assert(!result->vaw_release_fp);
	assert(!result->vaw_owned_fp);
	assert(!result->vaw_outfile);
	assert(result->vaw_fp == fp);
	result->vaw_outfile  = filename_dup; /* Inherit */
	result->vaw_owned_fp = fp;           /* Inherit */
	return result;
err_filename_dup_fp_unlink:
	(void)fclose(fp);
	(void)unlink(filename_dup);
err_filename_dup:
	free(filename_dup);
err:
	return NULL;
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_ANIM_WRITER_C */
