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
#ifndef GUARD_LIBVIDEO_GFX_GFX_EMPTY_H
#define GUARD_LIBVIDEO_GFX_GFX_EMPTY_H 1

#include "api.h"

#include <hybrid/compiler.h>
#include <libvideo/codec/types.h>

#include "buffer.h"

DECL_BEGIN

INTDEF ATTR_CONST NONNULL((1)) video_color_t CC libvideo_gfx_empty__getcolor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty__putcolor(struct video_gfx *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty__absline_llhh(struct video_gfx *__restrict self, video_coord_t x, video_coord_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty__absline_lhhl(struct video_gfx *__restrict self, video_coord_t x, video_coord_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty__absline_h(struct video_gfx *__restrict self, video_coord_t x, video_coord_t y, video_dim_t length, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty__absline_v(struct video_gfx *__restrict self, video_coord_t x, video_coord_t y, video_dim_t length, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty__absfill(struct video_gfx *__restrict self, video_coord_t x, video_coord_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF NONNULL((1, 7)) void CC libvideo_gfx_empty__bitfill(struct video_gfx *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color, struct video_bitmask const *__restrict bm);
INTDEF NONNULL((1, 9)) void CC libvideo_gfx_empty__bitstretchfill(struct video_gfx *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t color, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_RETNONNULL NONNULL((1)) struct video_blit *CC libvideo_gfx_empty__blitfrom(struct video_blit *__restrict ctx);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty__blit(struct video_blit *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty__stretch(struct video_blit *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF NONNULL((1, 8)) void CC libvideo_gfx_empty__bitblit(struct video_blit *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_coord_t src_x, video_coord_t src_y, video_dim_t size_x, video_dim_t size_y, struct video_bitmask const *__restrict bm);
INTDEF NONNULL((1, 10)) void CC libvideo_gfx_empty__bitstretch(struct video_blit *__restrict self, video_coord_t dst_x, video_coord_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_coord_t src_x, video_coord_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);

/* Empty GFX operators */
INTDEF NONNULL((1)) video_color_t CC libvideo_gfx_empty_getcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty_putcolor(struct video_gfx *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty_line(struct video_gfx *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty_hline(struct video_gfx *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty_vline(struct video_gfx *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty_fill(struct video_gfx *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty_rect(struct video_gfx *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF NONNULL((1, 7)) void CC libvideo_gfx_empty_bitfill(struct video_gfx *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t color, struct video_bitmask const *__restrict bm);
INTDEF NONNULL((1, 9)) void CC libvideo_gfx_empty_bitstretchfill(struct video_gfx *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t color, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_empty_ops(void);
#define libvideo_gfx_empty_ops (*_libvideo_gfx_empty_ops())

/* Empty blit operators */
INTDEF NONNULL((1)) void CC libvideo_gfx_empty_blit(struct video_blit *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF NONNULL((1)) void CC libvideo_gfx_empty_stretch(struct video_blit *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF NONNULL((1, 8)) void CC libvideo_gfx_empty_bitblit(struct video_blit *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y, struct video_bitmask const *__restrict bm);
INTDEF NONNULL((1, 10)) void CC libvideo_gfx_empty_bitstretch(struct video_blit *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blit_ops const *CC _libvideo_blit_empty_ops(void);
#define libvideo_blit_empty_ops (*_libvideo_blit_empty_ops())

/* Empty video buffer. */
INTDEF NONNULL((1, 2)) int CC libvideo_buffer_empty_lock(struct video_buffer *__restrict self, struct video_lock *__restrict result);
INTDEF NONNULL((1, 2)) void NOTHROW(CC libvideo_buffer_empty_unlock)(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_RETNONNULL NONNULL((1)) struct video_gfx *CC libvideo_buffer_empty_noblend(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) struct video_gfx *CC libvideo_buffer_empty_getgfx(struct video_buffer *__restrict self, struct video_gfx *__restrict result, gfx_blendmode_t blendmode, uintptr_t flags, video_color_t colorkey);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _libvideo_buffer_empty_ops(void);
#define libvideo_buffer_empty_ops (*_libvideo_buffer_empty_ops())

INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer *CC _libvideo_buffer_empty(void);
#define libvideo_buffer_empty (*_libvideo_buffer_empty())


/* Assign "empty" operators to "self". Initializes:
 * - self->vx_xops.*
 * - self->vx_ops
 * - self->vx_offt_x
 * - self->vx_offt_y
 * - self->vx_xmin
 * - self->vx_ymin
 * - self->vx_xend
 * - self->vx_yend */
INTDEF NONNULL((1)) void CC libvideo_gfx_setempty(struct video_gfx *__restrict self);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_EMPTY_H */
