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
#ifndef GUARD_LIBVIDEO_GFX_IO_BMP_C_INL
#define GUARD_LIBVIDEO_GFX_IO_BMP_C_INL 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "../api.h"

#include <hybrid/compiler.h>

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include <libvideo/gfx/buffer.h>
/**/

#include "../buffer-io.h"
#include <kos/anno.h>

/**/

DECL_BEGIN

INTERN ATTR_NOINLINE WUNUSED REF struct video_buffer *CC
libvideo_buffer_open_bmp(void const *blob, size_t blob_size) {
	/* TODO */
	(void)blob;
	(void)blob_size;
	COMPILER_IMPURE();
	return VIDEO_BUFFER_WRONG_FMT;
}

INTERN ATTR_NOINLINE WUNUSED NONNULL((1, 2)) int CC
libvideo_buffer_save_bmp(struct video_buffer *__restrict self,
                         FILE *stream, char const *options) {
	(void)self;
	(void)stream;
	(void)options;
	COMPILER_IMPURE();
	errno = ENOSYS; /* TODO */
	return -1;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_BMP_C_INL */
