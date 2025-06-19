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
#ifndef GUARD_LIBVIDEO_GFX_IO_GIF_C_INL
#define GUARD_LIBVIDEO_GFX_IO_GIF_C_INL 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <sys/mman.h>

#include <stdbool.h>
#include <stddef.h>

#include <libvideo/gfx/anim.h>
/**/

#include "../io-utils.h"

DECL_BEGIN

/* GIF */
INTERN WUNUSED REF struct video_anim *CC
libvideo_anim_open_gif(void const *blob, size_t blob_size,
                       struct mapfile *p_mapfile) {
	/* TODO */
	COMPILER_IMPURE();
	(void)blob;
	(void)blob_size;
	(void)p_mapfile;
	return VIDEO_ANIM_WRONG_FMT;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_IO_GIF_C_INL */
