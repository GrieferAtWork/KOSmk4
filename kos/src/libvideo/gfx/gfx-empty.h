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

INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC
libvideo_gfx_empty__blitto(struct video_blitter *__restrict ctx);

/* Empty GFX operators */
INTDEF ATTR_IN(1) video_color_t CC libvideo_gfx_empty_getcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_IN(1) void CC libvideo_gfx_empty_putcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_empty_line(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_empty_hline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_empty_vline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_empty_fill(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_gfx_empty_rect(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_gfx_empty_gradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) void CC libvideo_gfx_empty_hgradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_gfx_empty_vgradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC libvideo_gfx_empty_fillmask(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC libvideo_gfx_empty_fillstretchmask(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(4) void CC libvideo_gfx_empty_bitblit(struct video_gfx const *__restrict dst, video_offset_t dst_x, video_offset_t dst_y, struct video_gfx const *__restrict src, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_gfx_empty_stretch(struct video_gfx const *__restrict dst, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, struct video_gfx const *__restrict src, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_gfx_empty_ops(void);
#define libvideo_gfx_empty_ops (*_libvideo_gfx_empty_ops())

/* Empty blit operators */
INTDEF ATTR_IN(1) void CC libvideo_blitter_empty_blit(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_blitter_empty_stretch(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_blit_empty_ops(void);
#define libvideo_blit_empty_ops (*_libvideo_blit_empty_ops())

/* Empty video buffer. */
INTDEF WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC libvideo_buffer_empty_lock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
#define libvideo_buffer_empty_lockregion (*(int (FCC *)(struct video_buffer *__restrict, struct video_regionlock *__restrict))&libvideo_buffer_empty_lock)
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC libvideo_buffer_empty_initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC libvideo_buffer_empty_updategfx(struct video_gfx *__restrict self, unsigned int what);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC libvideo_buffer_empty_noblend(struct video_gfx *__restrict self);
INTDEF struct video_buffer_ops libvideo_buffer_empty_ops;
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _libvideo_buffer_empty_ops(void);

INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer *CC _libvideo_buffer_empty(void);
#define libvideo_buffer_empty (*_libvideo_buffer_empty())


/* Assign "empty" operators to "self". Initializes */
LOCAL ATTR_OUT(1) void CC
video_gfxhdr_setempty(struct video_gfxhdr *__restrict self) {
	self->vxh_blitfrom = &libvideo_gfx_empty__blitto;
	self->vxh_ops    = &libvideo_gfx_empty_ops;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_EMPTY_H */
