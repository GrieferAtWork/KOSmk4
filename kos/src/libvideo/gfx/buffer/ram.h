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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_RAM_H
#define GUARD_LIBVIDEO_GFX_BUFFER_RAM_H 1

#include "../api.h"

#include <hybrid/compiler.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/palette.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "../buffer.h"
#include "../swgfx.h"

/* Define and link  optimized fast-pass  pixel
 * accessors for 8,16,24,32-bit pixel formats. */
#undef CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS
#define CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS

DECL_BEGIN

struct video_rambuffer: video_buffer {
	size_t  rb_stride; /* [const] Buffer stride */
	byte_t *rb_data;   /* [1..1][owned][const] Buffer data */
};

struct video_rambuffer__for_codec: video_rambuffer {
	REF struct video_codec_handle *rbfc_codec; /* [1..1][const] Codec handle */
};

struct video_membuffer: video_rambuffer {
	void (CC *vm_release_mem)(void *cookie, void *mem);
	void     *vm_release_mem_cookie;
};

struct video_membuffer__for_codec: video_membuffer {
	REF struct video_codec_handle *vmfc_codec; /* [1..1][const] Codec handle */
};

/* Ram-buffer operator callbacks. */
INTDEF NONNULL((1)) void FCC rambuffer_destroy__for_codec(struct video_buffer *__restrict self);
INTDEF NONNULL((1)) void FCC rambuffer_destroy(struct video_buffer *__restrict self);
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int FCC rambuffer_lock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC rambuffer_lockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer_initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer_updategfx(struct video_gfx *__restrict self, unsigned int what);
#define rambuffer_rlock       rambuffer_lock
#define rambuffer_wlock       rambuffer_lock
#define rambuffer_rlockregion rambuffer_lockregion
#define rambuffer_wlockregion rambuffer_lockregion

#define video_buffer_ops_set_LOCKOPS_like_RAMBUFFER(self)          \
	(void)((self)->vi_rlock        = &rambuffer_rlock,             \
	       (self)->vi_wlock        = &rambuffer_wlock,             \
	       (self)->vi_unlock       = &libvideo_buffer_noop_unlock, \
	       (self)->vi_rlockregion  = &rambuffer_rlockregion,       \
	       (self)->vi_wlockregion  = &rambuffer_wlockregion,       \
	       (self)->vi_unlockregion = &libvideo_buffer_noop_unlockregion)
#define video_buffer_ops_set_GFXOPS_like_RAMBUFFER(self) \
	(void)((self)->vi_initgfx   = &rambuffer_initgfx,    \
	       (self)->vi_updategfx = &rambuffer_updategfx)

INTDEF struct video_buffer_ops rambuffer_ops;
INTDEF struct video_buffer_ops rambuffer_ops__for_codec;
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_ops__for_codec(void);

INTDEF struct video_buffer_ops membuffer_ops;
INTDEF struct video_buffer_ops membuffer_ops__for_codec;
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _membuffer_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops *CC _membuffer_ops__for_codec(void);





/* This is the layout of `video_gfx::_vx_driver' expected by generic RAM-based GFX */
struct gfx_ramdrv: gfx_swdrv {
	byte_t                    *grd_data;   /* [const][== ((struct video_rambuffer *):vx_buffer)->rb_data] */
	size_t                     grd_stride; /* [const][== ((struct video_rambuffer *):vx_buffer)->rb_stride] */
	struct video_format const *grd_format; /* [const][== &((struct video_rambuffer *):vx_buffer)->vb_format] */
};
#define gfx_ramdrv_init(self, buffer)                \
	(void)((self)->grd_data   = (buffer)->rb_data,   \
	       (self)->grd_stride = (buffer)->rb_stride, \
	       (self)->grd_format = &(buffer)->vb_format)
#define video_ramgfx_getdrv(self) \
	((struct gfx_ramdrv *)(self)->_vx_driver)


/* GFX functions for memory-based video buffers (without GPU support) */
INTDEF ATTR_IN(1) video_color_t CC libvideo_ramgfx__getcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_color_t CC libvideo_ramgfx__getcolor_with_key(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC libvideo_ramgfx__putcolor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC libvideo_ramgfx__putcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
#define DECLARE_libvideo_ramgfx__putcolor_FOO(name, mode) \
	INTDEF ATTR_IN(1) void CC libvideo_ramgfx__putcolor_##name(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
GFX_FOREACH_DEDICATED_BLENDMODE(DECLARE_libvideo_ramgfx__putcolor_FOO)
GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(DECLARE_libvideo_ramgfx__putcolor_FOO)
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

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_RAM_H */
