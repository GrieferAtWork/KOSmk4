/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVIDEO_GFX_RAM_BUFFER_H
#define GUARD_LIBVIDEO_GFX_RAM_BUFFER_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include "buffer.h"

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/palette.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

DECL_BEGIN

/* Indices into `video_buffer_gfx::bfx_driver' for RAM gfx buffers. */
#define VIDEO_BUFFER_RAMGFX_DATA   0
#define VIDEO_BUFFER_RAMGFX_STRIDE 1
#define VIDEO_BUFFER_RAMGFX_SIZEX  2
#define VIDEO_BUFFER_RAMGFX_SIZEY  3


struct video_rambuffer: video_buffer {
	size_t  vb_stride; /* [const] Buffer stride */
	size_t  vb_total;  /* [const] Total buffer size */
	byte_t *vb_data;   /* [1..1][owned][const] Buffer data */
};



/* GFX functions for memory-based video buffers (without GPU support) */
INTDEF video_color_t CC libvideo_gfx_ramgfx_getcolor(struct video_buffer_gfx *__restrict self, uintptr_t x, uintptr_t y);
INTDEF video_color_t CC libvideo_gfx_ramgfx_getcolor_with_key(struct video_buffer_gfx *__restrict self, uintptr_t x, uintptr_t y);
INTDEF void CC libvideo_gfx_ramgfx_putcolor(struct video_buffer_gfx *__restrict self, uintptr_t x, uintptr_t y, video_color_t color);
INTDEF void CC libvideo_gfx_ramgfx_line(struct video_buffer_gfx *__restrict self, intptr_t x1, intptr_t y1, intptr_t x2, intptr_t y2, video_color_t color);
INTDEF void CC libvideo_gfx_ramgfx_vline(struct video_buffer_gfx *__restrict self, uintptr_t x, uintptr_t y1, uintptr_t y2, video_color_t color);
INTDEF void CC libvideo_gfx_ramgfx_hline(struct video_buffer_gfx *__restrict self, uintptr_t y, uintptr_t x1, uintptr_t x2, video_color_t color);
INTDEF void CC libvideo_gfx_ramgfx_fill(struct video_buffer_gfx *__restrict self, uintptr_t x, uintptr_t y, size_t size_x, size_t size_y, video_color_t color);
INTDEF void CC libvideo_gfx_ramgfx_rect(struct video_buffer_gfx *__restrict self, uintptr_t x, uintptr_t y, size_t size_x, size_t size_y, video_color_t color);
INTDEF void CC libvideo_gfx_ramgfx_blit(struct video_buffer_gfx *__restrict self, intptr_t dst_x, intptr_t dst_y, struct video_buffer_gfx *__restrict src, intptr_t src_x, intptr_t src_y, size_t size_x, size_t size_y);
INTDEF void CC libvideo_gfx_ramgfx_stretch(struct video_buffer_gfx *__restrict self, intptr_t dst_x, intptr_t dst_y, size_t dst_size_x, size_t dst_size_y, struct video_buffer_gfx *__restrict src, intptr_t src_x, intptr_t src_y, size_t src_size_x, size_t src_size_y);


/* Create a new RAM-based video buffer */
INTDEF WUNUSED /*REF*/ struct video_buffer *CC
libvideo_rambuffer_create(size_t size_x, size_t size_y,
                          struct video_codec *__restrict codec,
                          struct video_palette *palette);


/* Return the preferred video format.
 * If possible, this format will match the format used by the host's graphics card.
 * If no graphics card exists, or the card isn't clear on its preferred format, some
 * other, common format will be returned instead. */
INTDEF ATTR_RETNONNULL struct video_format const *CC libvideo_preferred_format(void);


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_RAM_BUFFER_H */
