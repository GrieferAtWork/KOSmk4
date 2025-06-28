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
#ifndef GUARD_LIBVIDEO_GFX_RAM_BUFFER_H
#define GUARD_LIBVIDEO_GFX_RAM_BUFFER_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/palette.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "buffer.h"
#include "gfx.h"

/* Define and link  optimized fast-pass  pixel
 * accessors for 8,16,24,32-bit pixel formats. */
#undef CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS
#define CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS

DECL_BEGIN

struct video_rambuffer: video_buffer {
	size_t  rb_stride; /* [const] Buffer stride */
	size_t  rb_total;  /* [const] Total buffer size */
	byte_t *rb_data;   /* [1..1][owned][const] Buffer data */
};

/* Ram-buffer operator callbacks. */
INTDEF NONNULL((1)) void FCC rambuffer_destroy(struct video_buffer *__restrict self);
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int FCC rambuffer_lock(struct video_buffer *__restrict self, struct video_lock *__restrict result);
INTDEF ATTR_INOUT(1) ATTR_IN(2) void NOTHROW(FCC rambuffer_unlock)(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer_initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer_updategfx(struct video_gfx *__restrict self, unsigned int what);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer_noblend(struct video_gfx *__restrict self);
#define rambuffer_rlock rambuffer_lock
#define rambuffer_wlock rambuffer_lock

INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_ops(void);
#define rambuffer_ops (*_rambuffer_ops())


/* Indices into `video_gfx::bfx_driver' for RAM gfx buffers. */
#define RAMGFX_DRIVER__DATA   0
#define RAMGFX_DRIVER__STRIDE 1

/* GFX functions for memory-based video buffers (without GPU support) */
INTDEF ATTR_IN(1) video_color_t CC libvideo_ramgfx__getcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_ramgfx__getcolor_with_key(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC libvideo_ramgfx__putcolor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_ramgfx__putcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
#define DECLARE_libvideo_ramgfx__putcolor_FOO(name, mode) \
	INTDEF ATTR_IN(1) void CC libvideo_ramgfx__putcolor_##name(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
GFX_FOREACH_DEDICATED_BLENDMODE(DECLARE_libvideo_ramgfx__putcolor_FOO)
#undef DECLARE_libvideo_ramgfx__putcolor_FOO
INTDEF ATTR_IN(1) video_pixel_t CC libvideo_ramgfx__getpixel(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC libvideo_ramgfx__setpixel(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
#ifdef CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS
INTDEF ATTR_IN(1) video_pixel_t CC libvideo_ramgfx__getpixel8(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC libvideo_ramgfx__setpixel8(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) video_pixel_t CC libvideo_ramgfx__getpixel16(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC libvideo_ramgfx__setpixel16(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) video_pixel_t CC libvideo_ramgfx__getpixel24(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC libvideo_ramgfx__setpixel24(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) video_pixel_t CC libvideo_ramgfx__getpixel32(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC libvideo_ramgfx__setpixel32(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
#endif /* CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS */


/* Create a new RAM-based video buffer */
INTDEF WUNUSED NONNULL((3)) /*REF*/ struct video_buffer *CC
libvideo_rambuffer_create(video_dim_t size_x, video_dim_t size_y,
                          struct video_codec const *__restrict codec,
                          struct video_palette *palette);

/* Create a video buffer that interfaces with a pre-existing buffer whose
 * base address is located at `mem' (which consists of  `stride * size_y'
 * bytes). When  non-NULL,  `(*release_mem)(release_mem_cookie, mem)'  is
 * called when the final reference for the returned buffer is dropped.
 *
 * This function can be used to wrap a memory-resident graphics buffer
 * in-place,    without   needing   to    copy   it   anywhere   else.
 * @param: mem:     Base address  of  the  pre-loaded  memory  buffer.
 *                  If this location isn't writable, attempts to write
 *                  pixel  data of the  returned buffer will SEGFAULT.
 * @param: size_x:  Width of returned buffer
 * @param: size_y:  Height of returned buffer
 * @param: stride:  Scanline width in `mem'
 * @param: codec:   The video codec that describes how `mem' is encoded.
 * @param: palette: The palette to use (only needed if used by `codec')
 * @param: release_mem: Optional callback invoked when the returned buffer is destroyed
 * @param: release_mem_cookie: Cookie argument for `release_mem'
 * @return: * :   The newly created video buffer
 * @return: NULL: Error (s.a. `errno') */
INTDEF WUNUSED NONNULL((5)) REF struct video_buffer *CC
libvideo_buffer_formem(void *mem, video_dim_t size_x, video_dim_t size_y, size_t stride,
                       struct video_codec const *codec, struct video_palette *palette,
                       void (CC *release_mem)(void *cookie, void *mem),
                       void *release_mem_cookie);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_RAM_BUFFER_H */
