/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef GUARD_LIBVIDEO_GFX_GFX_H
#define GUARD_LIBVIDEO_GFX_GFX_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libvideo/gfx/gfx.h>

DECL_BEGIN


/* Default GFX functions (using get/put pixel) */
INTDEF void CC libvideo_gfx_defaultgfx_line(struct video_buffer_gfx *__restrict self, intptr_t x1, intptr_t y1, intptr_t x2, intptr_t y2, video_color_t color);
INTDEF void CC libvideo_gfx_defaultgfx_vline(struct video_buffer_gfx *__restrict self, uintptr_t x, uintptr_t y1, uintptr_t y2, video_color_t color);
INTDEF void CC libvideo_gfx_defaultgfx_hline(struct video_buffer_gfx *__restrict self, uintptr_t y, uintptr_t x1, uintptr_t x2, video_color_t color);
INTDEF void CC libvideo_gfx_defaultgfx_fill(struct video_buffer_gfx *__restrict self, uintptr_t x, uintptr_t y, size_t size_x, size_t size_y, video_color_t color);
INTDEF void CC libvideo_gfx_defaultgfx_rect(struct video_buffer_gfx *__restrict self, uintptr_t x, uintptr_t y, size_t size_x, size_t size_y, video_color_t color);
INTDEF void CC libvideo_gfx_defaultgfx_blit(struct video_buffer_gfx *__restrict self, intptr_t dst_x, intptr_t dst_y, struct video_buffer_gfx *__restrict src, intptr_t src_x, intptr_t src_y, size_t size_x, size_t size_y);
INTDEF void CC libvideo_gfx_defaultgfx_stretch(struct video_buffer_gfx *__restrict self, intptr_t dst_x, intptr_t dst_y, size_t dst_size_x, size_t dst_size_y, struct video_buffer_gfx *__restrict src, intptr_t src_x, intptr_t src_y, size_t src_size_x, size_t src_size_y);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_H */
