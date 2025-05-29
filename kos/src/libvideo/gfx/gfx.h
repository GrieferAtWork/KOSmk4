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
#ifndef GUARD_LIBVIDEO_GFX_GFX_H
#define GUARD_LIBVIDEO_GFX_GFX_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libvideo/codec/types.h>
#include <libvideo/gfx/gfx.h>

DECL_BEGIN

/* Low-level, Generic, always-valid GFX functions (using only `fxo_getcolor' + `fxo_putcolor') */
INTDEF NONNULL((1)) void CC libvideo_gfx_generic__absline_llhh(struct video_gfx *__restrict self, video_coord_t x, video_coord_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_generic__absline_lhhl(struct video_gfx *__restrict self, video_coord_t x, video_coord_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_generic__absline_h(struct video_gfx *__restrict self, video_coord_t x, video_coord_t y, video_dim_t length, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_generic__absline_v(struct video_gfx *__restrict self, video_coord_t x, video_coord_t y, video_dim_t length, video_color_t color);
INTDEF NONNULL((1, 7)) void CC libvideo_gfx_generic__bitfill(struct video_gfx *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);
INTDEF NONNULL((1, 9)) void CC libvideo_gfx_generic__bitstretchfill(struct video_gfx *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t color, video_dim_t src_size_x, video_dim_t src_size_y, void const *__restrict bitmask, uintptr_t bitskip, video_dim_t bitmask_size_x, video_dim_t bitmask_size_y);
INTDEF ATTR_RETNONNULL NONNULL((1)) struct video_blit *CC libvideo_gfx_generic__blitfrom(struct video_blit *__restrict ctx);

/* Low-level, Generic, always-valid Blit functions (using only `fxo_getcolor' + `fxo_putcolor') */
INTDEF NONNULL((1)) void CC libvideo_gfx_generic__blit(struct video_blit *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1)) void CC libvideo_gfx_generic__stretch(struct video_blit *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF NONNULL((1, 8)) void CC libvideo_gfx_generic__bitblit(struct video_blit *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);
INTDEF NONNULL((1, 10)) void CC libvideo_gfx_generic__bitstretch(struct video_blit *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, void const *__restrict bitmask, uintptr_t bitskip, video_dim_t bitmask_size_x, video_dim_t bitmask_size_y);


/* Generic GFX operators */
INTDEF ATTR_RETNONNULL NONNULL((1)) struct video_gfx *CC libvideo_gfx_generic_clip(struct video_gfx *__restrict self, video_offset_t clip_x, video_offset_t clip_y, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1)) video_color_t CC libvideo_gfx_generic_getcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF NONNULL((1)) void CC libvideo_gfx_generic_putcolor(struct video_gfx *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_generic_line(struct video_gfx *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_generic_hline(struct video_gfx *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_generic_vline(struct video_gfx *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_generic_fill(struct video_gfx *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_generic_rect(struct video_gfx *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF NONNULL((1, 7)) void CC libvideo_gfx_generic_bitfill(struct video_gfx *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);
INTDEF NONNULL((1, 9)) void CC libvideo_gfx_generic_bitstretchfill(struct video_gfx *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t color, video_dim_t src_size_x, video_dim_t src_size_y, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_generic_ops(void);
#define libvideo_gfx_generic_ops (*_libvideo_gfx_generic_ops())

/* Generic blit operators */
INTDEF NONNULL((1)) void CC libvideo_gfx_generic_blit(struct video_blit *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1)) void CC libvideo_gfx_generic_stretch(struct video_blit *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF NONNULL((1, 8)) void CC libvideo_gfx_generic_bitblit(struct video_blit *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);
INTDEF NONNULL((1, 10)) void CC libvideo_gfx_generic_bitstretch(struct video_blit *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blit_ops const *CC _libvideo_blit_generic_ops(void);
#define libvideo_blit_generic_ops (*_libvideo_blit_generic_ops())


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_H */
