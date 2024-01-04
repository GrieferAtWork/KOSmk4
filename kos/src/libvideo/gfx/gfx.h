/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVIDEO_GFX_GFX_H
#define GUARD_LIBVIDEO_GFX_GFX_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libvideo/gfx/gfx.h>

DECL_BEGIN

/* Default GFX functions (using safe/unsafe get/put pixel) */
INTDEF NONNULL((1)) void CC libvideo_gfx_defaultgfx_line(struct video_gfx *__restrict self, intptr_t x1, intptr_t y1, intptr_t x2, intptr_t y2, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_defaultgfx_vline(struct video_gfx *__restrict self, intptr_t x, intptr_t y, size_t length, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_defaultgfx_hline(struct video_gfx *__restrict self, intptr_t x, intptr_t y, size_t length, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_defaultgfx_fill(struct video_gfx *__restrict self, intptr_t x, intptr_t y, size_t size_x, size_t size_y, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_defaultgfx_rect(struct video_gfx *__restrict self, intptr_t x, intptr_t y, size_t size_x, size_t size_y, video_color_t color);
INTDEF NONNULL((1, 4)) void CC libvideo_gfx_defaultgfx_blit(struct video_gfx *self, intptr_t dst_x, intptr_t dst_y, struct video_gfx const *src, intptr_t src_x, intptr_t src_y, size_t size_x, size_t size_y);
INTDEF NONNULL((1, 6)) void CC libvideo_gfx_defaultgfx_stretch(struct video_gfx *self, intptr_t dst_x, intptr_t dst_y, size_t dst_size_x, size_t dst_size_y, struct video_gfx const *src, intptr_t src_x, intptr_t src_y, size_t src_size_x, size_t src_size_y);
INTDEF NONNULL((1, 7)) void CC libvideo_gfx_defaultgfx_bitfill(struct video_gfx *__restrict self, intptr_t dst_x, intptr_t dst_y, video_color_t color, size_t dst_size_x, size_t dst_size_y, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);
INTDEF NONNULL((1, 4, 9)) void CC libvideo_gfx_defaultgfx_bitblit(struct video_gfx *self, intptr_t dst_x, intptr_t dst_y, struct video_gfx const *src, intptr_t src_x, intptr_t src_y, size_t size_x, size_t size_y, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);
INTDEF NONNULL((1, 9)) void CC libvideo_gfx_defaultgfx_bitstretchfill(struct video_gfx *__restrict self, intptr_t dst_x, intptr_t dst_y, size_t dst_size_x, size_t dst_size_y, video_color_t color, size_t src_size_x, size_t src_size_y, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);
INTDEF NONNULL((1, 6, 11)) void CC libvideo_gfx_defaultgfx_bitstretchblit(struct video_gfx *self, intptr_t dst_x, intptr_t dst_y, size_t dst_size_x, size_t dst_size_y, struct video_gfx const *src, intptr_t src_x, intptr_t src_y, size_t src_size_x, size_t src_size_y, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);

/* Same as the functions above, but these take `vfx_offt_(x|y)' into account. */
INTDEF NONNULL((1)) void CC libvideo_gfx_defaultgfx_line_o(struct video_gfx *__restrict self, intptr_t x1, intptr_t y1, intptr_t x2, intptr_t y2, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_defaultgfx_vline_o(struct video_gfx *__restrict self, intptr_t x, intptr_t y, size_t length, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_defaultgfx_hline_o(struct video_gfx *__restrict self, intptr_t x, intptr_t y, size_t length, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_defaultgfx_fill_o(struct video_gfx *__restrict self, intptr_t x, intptr_t y, size_t size_x, size_t size_y, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_defaultgfx_rect_o(struct video_gfx *__restrict self, intptr_t x, intptr_t y, size_t size_x, size_t size_y, video_color_t color);
INTDEF NONNULL((1, 4)) void CC libvideo_gfx_defaultgfx_blit_o(struct video_gfx *self, intptr_t dst_x, intptr_t dst_y, struct video_gfx const *src, intptr_t src_x, intptr_t src_y, size_t size_x, size_t size_y);
INTDEF NONNULL((1, 6)) void CC libvideo_gfx_defaultgfx_stretch_o(struct video_gfx *self, intptr_t dst_x, intptr_t dst_y, size_t dst_size_x, size_t dst_size_y, struct video_gfx const *src, intptr_t src_x, intptr_t src_y, size_t src_size_x, size_t src_size_y);
INTDEF NONNULL((1, 7)) void CC libvideo_gfx_defaultgfx_bitfill_o(struct video_gfx *__restrict self, intptr_t dst_x, intptr_t dst_y, video_color_t color, size_t dst_size_x, size_t dst_size_y, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);
INTDEF NONNULL((1, 4, 9)) void CC libvideo_gfx_defaultgfx_bitblit_o(struct video_gfx *self, intptr_t dst_x, intptr_t dst_y, struct video_gfx const *src, intptr_t src_x, intptr_t src_y, size_t size_x, size_t size_y, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);
INTDEF NONNULL((1, 9)) void CC libvideo_gfx_defaultgfx_bitstretchfill_o(struct video_gfx *__restrict self, intptr_t dst_x, intptr_t dst_y, size_t dst_size_x, size_t dst_size_y, video_color_t color, size_t src_size_x, size_t src_size_y, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);
INTDEF NONNULL((1, 6, 11)) void CC libvideo_gfx_defaultgfx_bitstretchblit_o(struct video_gfx *self, intptr_t dst_x, intptr_t dst_y, size_t dst_size_x, size_t dst_size_y, struct video_gfx const *src, intptr_t src_x, intptr_t src_y, size_t src_size_x, size_t src_size_y, void const *__restrict bitmask, uintptr_t bitskip, size_t bitscan);

INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops *CC libvideo_gfx_defaultgfx_getops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops *CC libvideo_gfx_defaultgfx_getops_o(void);


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_H */
