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
#ifndef _LIBVIDEO_GFX_SURFACE_DEFS_H
#define _LIBVIDEO_GFX_SURFACE_DEFS_H 1

#include "api.h"
/**/

#include "../color.h"
#include "gfx-flags.h"

#ifdef __CC__
__DECL_BEGIN

struct video_palette;
struct video_buffer;

/* Wrapper around  `struct video_buffer'  that  allows  users  to
 * directly override the palette and color key of a video buffer. */
struct video_surface {
	struct video_palette *vs_pal;      /* [0..1] Used color palette */
	struct video_buffer  *vs_buffer;   /* [1..1] Video buffer. */
	video_gfx_flag_t      vs_flags;    /* Special buffer flags */
	video_pixel_t         vs_colorkey; /* [valid_if(vs_flags & VIDEO_GFX_F_COLORKEY)] Color key */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_SURFACE_DEFS_H */
