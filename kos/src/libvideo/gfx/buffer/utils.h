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
#ifndef GUARD_LIBVIDEO_GFX_UTILS_BUFFER_H
#define GUARD_LIBVIDEO_GFX_UTILS_BUFFER_H 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>

#include <stddef.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/types.h>

DECL_BEGIN

/* Try to convert `x' into  a byte-offset then stored in  `*p_xoff'.
 * Make sure that the pixel specified by `x' starts at the beginning
 * of a byte, and that the resulting offset is properly aligned.
 * @return: true:  Success
 * @return: false: Failure */
LOCAL WUNUSED ATTR_IN(1) ATTR_OUT(3) ATTR_OUT(4) void
NOTHROW(CC video_codec_xcoord_to_offset)(struct video_codec const *__restrict self,
                                         video_coord_t x, size_t *__restrict p_xoff,
                                         video_coord_t *__restrict p_xrem) {
	if (self->vc_specs.vcs_pxsz > 1) {
		/* Multi-byte codecs */
		*p_xoff = x * self->vc_specs.vcs_pxsz;
		*p_xrem = 0;
	} else {
		/* Handling for codecs that store multiple pixels in 1 byte */
		switch (self->vc_specs.vcs_bpp) {
		case 1:
			*p_xoff = x >> 3;
			*p_xrem = x & 7;
			break;
		case 2:
			*p_xoff = x >> 2;
			*p_xrem = x & 3;
			break;
		case 4:
			*p_xoff = x >> 1;
			*p_xrem = x & 1;
			break;
		default:
			*p_xoff = x;
			*p_xrem = 0;
			break;
		}
	}
	if (!IS_ALIGNED(*p_xoff, self->vc_align)) {
		size_t byte_delta = FLOOR_ALIGN(*p_xoff, self->vc_align);
		*p_xoff -= byte_delta;
		if (self->vc_specs.vcs_pxsz > 1) {
			*p_xrem += byte_delta / self->vc_specs.vcs_pxsz;
		} else {
			switch (self->vc_specs.vcs_bpp) {
			case 1: *p_xrem += byte_delta * 8; break;
			case 2: *p_xrem += byte_delta * 4; break;
			case 4: *p_xrem += byte_delta * 2; break;
			default: *p_xrem += byte_delta; break;
			}
		}
	}
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_UTILS_BUFFER_H */
