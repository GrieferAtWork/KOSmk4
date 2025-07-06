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
#ifndef GUARD_LIBVIDEO_GFX_BITMASK_BUFFER_H
#define GUARD_LIBVIDEO_GFX_BITMASK_BUFFER_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <stdint.h>

#include <libvideo/codec/palette.h>
#include <libvideo/gfx/buffer.h>

#include "gfx.h"

DECL_BEGIN

struct video_palette2 {
	ATTR_PURE_T WUNUSED_T ATTR_IN_T(1) video_pixel_t
	NOTHROW_T(LIBVIDEO_CODEC_CC *vp_color2pixel)(struct video_palette const *__restrict self,
	                                             video_color_t color);
	NONNULL_T((1)) void
	NOTHROW_T(LIBVIDEO_CODEC_CC *vp_destroy)(struct video_palette *__restrict self);
	uintptr_t                              vp_refcnt;
	struct video_palette_tree            *_vp_tree;
	video_pixel_t                          vp_cnt;    /* == 2 */
	video_color_t                          vp_pal[2];
};


struct bitmask_buffer: video_buffer {
	struct video_bitmask  bmb_bm;  /* Bitmask representing this video buffer */
	struct video_palette2 bmb_pal; /* Palette */
};


/* Initialize a "struct bitmask_buffer"
 * @return: * : Always re-returns `self' */
INTDEF ATTR_RETNONNULL ATTR_OUT(1) ATTR_IN(4) ATTR_IN(5) struct bitmask_buffer *CC
bitmask_buffer_init(struct bitmask_buffer *__restrict self,
                    video_dim_t size_x, video_dim_t size_y,
                    struct video_bitmask const *__restrict bm,
                    video_color_t const bg_fg_colors[2]);
#define bitmask_buffer_fini(self) (void)0


/* Create a video buffer that represents the pixel data defined by  a
 * given `__bm' (bitmask). This function is primarily used internally
 * by `video_gfx_absfillmask()' and  `video_gfx_absfillstretchmask()'
 * to deal with  GFX contexts  where the bitmask  cannot be  rendered
 * using  the default method,  but has to be  rendered by being blit.
 *
 * @param: __size_x:       Width of the given `__bm' (in pixels)
 * @param: __size_y:       Height of the given `__bm' (in pixels)
 * @param: __bm:           Bitmask whose data should be referenced interpreted
 * @param: __bg_fg_colors: Colors that 0/1 bits of `__bm' should map to
 * @return: * :   The newly created video buffer
 * @return: NULL: [errno=ENOMEM] Insufficient memory (won't happen when
 *                               used internally, where struct is  just
 *                               allocated on-stack) */
INTDEF WUNUSED ATTR_IN(3) ATTR_IN(4) REF struct video_buffer *CC
libvideo_buffer_forbitmask(video_dim_t size_x, video_dim_t size_y,
                           struct video_bitmask const *__restrict bm,
                           video_color_t const bg_fg_colors[2]);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BITMASK_BUFFER_H */
