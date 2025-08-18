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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_EMPTY_H
#define GUARD_LIBVIDEO_GFX_BUFFER_EMPTY_H 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include "../buffer.h"

#include <libvideo/gfx/buffer/empty.h>
#include <libvideo/types.h>

DECL_BEGIN

/* Empty GFX operators */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter *FCC libvideo_emptygfx__blitfrom(struct video_blitter *__restrict ctx);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_blitter3 *FCC libvideo_emptygfx__blitfrom3(struct video_blitter3 *__restrict ctx);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *CC libvideo_emptygfx__clip(struct video_gfx *__restrict self, video_offset_t clip_x, video_offset_t clip_y, video_dim_t size_x, video_dim_t size_y);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC libvideo_emptygfx__coord2offset(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_offset_t coords[2]) ASMNAME("libvideo_emptygfx__offset2coord");
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC libvideo_emptygfx__offset2coord(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_coord_t coords[2]);
INTDEF ATTR_IN(1) video_color_t CC libvideo_emptygfx__getcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_IN(1) void CC libvideo_emptygfx__putcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_emptygfx__line(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_emptygfx__hline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_emptygfx__vline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_emptygfx__fill(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_emptygfx__rect(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_emptygfx__gradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) void CC libvideo_emptygfx__hgradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC libvideo_emptygfx__vgradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) ATTR_IN(4) void CC libvideo_emptygfx__bitblit(struct video_gfx const *dst, video_offset_t dst_x, video_offset_t dst_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC libvideo_emptygfx__stretch(struct video_gfx const *dst, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) ATTR_IN(4) ATTR_IN(7) void CC libvideo_emptygfx__bitblit3(struct video_gfx const *wrdst, video_offset_t wrdst_x, video_offset_t wrdst_y, struct video_gfx const *rddst, video_offset_t rddst_x, video_offset_t rddst_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) ATTR_IN(4) ATTR_IN(9) void CC libvideo_emptygfx__stretch3(struct video_gfx const *wrdst, video_offset_t wrdst_x, video_offset_t wrdst_y, struct video_gfx const *rddst, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);

/* Empty blit operators */
INTDEF ATTR_IN(1) void CC libvideo_emptyblitter__blit(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_emptyblitter__stretch(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);

/* Empty blit3 operators */
INTDEF ATTR_IN(1) void CC libvideo_emptyblitter3__blit(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) void CC libvideo_emptyblitter3__stretch(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);

/* Empty video buffer. */
INTDEF WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC libvideo_emptybuffer__lock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int FCC libvideo_emptybuffer__lockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC libvideo_emptybuffer__subregion(struct video_surface const *__restrict self, struct video_crect const *__restrict phys_rect);
#define libvideo_emptybuffer__revoke libvideo_buffer_noop__revoke
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC libvideo_emptybuffer__initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC libvideo_emptybuffer__updategfx(struct video_gfx *__restrict self, unsigned int what);

/* Operator tables for video components representing 0 pixels */
INTDEF struct video_gfx_ops libvideo_emptygfx_ops;
INTDEF struct video_buffer_ops libvideo_emptybuffer_ops;
INTDEF struct video_blitter_ops libvideo_emptyblitter_ops;
INTDEF struct video_blitter3_ops libvideo_emptyblitter3_ops;
INTDEF struct video_buffer libvideo_emptybuffer;
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops const *CC _libvideo_emptygfx_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _libvideo_emptybuffer_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops const *CC _libvideo_emptyblitter_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter3_ops const *CC _libvideo_emptyblitter3_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer *CC _libvideo_emptybuffer(void);
INTDEF ATTR_RETNONNULL WUNUSED REF struct video_buffer *CC _libvideo_emptybufferref(void);

/* Construct (or re-using an existing) empty video buffer with the given dimension
 * The returned buffer always uses `video_ramdomain(3V)' as its associated domain.
 * @param: buffer_xdim, buffer_ydim: Dimensions of the returned buffer (**NOT** swapped if VIDEO_GFX_F_XYSWAP is set)
 * @return: * : A reference to a video buffer without any backing
 *              storage, and  dimensions  matching  those  given.
 * @return: NULL: [errno=ENOMEM] Out of memory. */
INTDEF WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_makeemptybuffer(struct video_buffer_format const *__restrict format,
                         video_dim_t xdim, video_dim_t ydim);
INTDEF WUNUSED ATTR_IN(1) REF struct video_buffer *CC
libvideo_makeemptybuffer_like(struct video_surface const *__restrict surf,
                              video_dim_t xdim, video_dim_t ydim);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_EMPTY_H */
