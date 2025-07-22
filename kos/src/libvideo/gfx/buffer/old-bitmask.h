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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_BITMASK_H
#define GUARD_LIBVIDEO_GFX_BUFFER_BITMASK_H 1

/* TODO: REMOVE THIS FILE */

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <stdint.h>

#include <libvideo/color.h>
#include <libvideo/gfx/api.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/codec/palette.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

DECL_BEGIN

/* TODO: ALL THE STUFF IN HERE IS DEPRECATED !!! */

struct video_palette2 {
	ATTR_PURE_T WUNUSED_T ATTR_IN_T(1) video_pixel_t
	NOTHROW_T(LIBVIDEO_GFX_FCC *vp_color2pixel)(struct video_palette const *__restrict self,
	                                             video_color_t color);
	NONNULL_T((1)) void
	NOTHROW_T(LIBVIDEO_GFX_FCC *vp_destroy)(struct video_palette *__restrict self);
	uintptr_t                              vp_refcnt;
	struct video_palette_tree            *_vp_tree;
	video_palette_flag_t                   vp_flags;
	video_pixel_t                          vp_cnt;    /* == 2 */
	video_color_t                          vp_pal[2];
};


struct old_bitmask_buffer: video_buffer {
	struct video_bitmask  bmb_bm;  /* Bitmask representing this video buffer */
	struct video_palette2 bmb_pal; /* Palette */
};


/* Initialize a "struct old_bitmask_buffer"
 * @return: * : Always re-returns `self' */
INTDEF ATTR_RETNONNULL ATTR_OUT(1) ATTR_IN(4) ATTR_IN(5) struct old_bitmask_buffer *CC
old_bitmask_buffer_init(struct old_bitmask_buffer *__restrict self,
                        video_dim_t size_x, video_dim_t size_y,
                        struct video_bitmask const *__restrict bm,
                        video_color_t const bg_fg_colors[2]);
#define old_bitmask_buffer_fini(self) (void)0

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_BITMASK_H */
