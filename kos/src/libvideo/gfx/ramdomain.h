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
#ifndef GUARD_LIBVIDEO_GFX_RAMDOMAIN_H
#define GUARD_LIBVIDEO_GFX_RAMDOMAIN_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <sys/types.h>

#include <stdbool.h>
#include <stddef.h>

#include <libvideo/color.h>
#include <libvideo/crect.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/buffer/rambuffer.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "buffer.h"
#include "gfx-utils.h"
#include "swgfx.h"

DECL_BEGIN

/* Define and link  optimized fast-pass  pixel
 * accessors for 8,16,24,32-bit pixel formats. */
#undef CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS
#define CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS


/************************************************************************/
/* RAM DOMAIN                                                           */
/************************************************************************/

/* Video buffer types used to represent ram buffers.
 * NOTE: None of these ever look at `video_buffer::vb_domain',
 *       so you're free to  re-use these at the  driver-level! */
INTDEF struct video_buffer_ops rambuffer_ops;
INTDEF struct video_buffer_ops rambuffer_formem_ops;
INTDEF struct video_buffer_ops rambuffer_subregion_ops;
INTDEF struct video_buffer_ops rambuffer_subregion_norem_ops;

INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_formem_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_subregion_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_subregion_norem_ops(void);


/************************************************************************/
/* RAMBUFFER OPERATORS                                                  */
/************************************************************************/

/* DESTROY */
INTDEF NONNULL((1)) void FCC rambuffer__destroy(struct video_buffer *__restrict self);
INTDEF NONNULL((1)) void FCC rambuffer_formem__destroy(struct video_buffer *__restrict self);
INTDEF NONNULL((1)) void FCC rambuffer_subregion__destroy(struct video_buffer *__restrict self);

/* REVOKE+SUBREGION */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC rambuffer__revoke)(struct video_buffer *__restrict self); /* TODO: Generalize as a no-op revoke function */
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC rambuffer__subregion(struct video_surface const *__restrict self, struct video_crect const *__restrict rect);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) REF struct video_buffer *FCC rambuffer_subregion__subregion(struct video_surface const *__restrict self, struct video_crect const *__restrict rect);

/* LOCK */
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int FCC rambuffer__lock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC rambuffer__lockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC rambuffer_subregion__lockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);

/* GFX */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer__initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer__updategfx(struct video_gfx *__restrict self, unsigned int what);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer_subregion__initgfx(struct video_gfx *__restrict self);
#define rambuffer_subregion__updategfx (*(struct video_gfx *(FCC *)(struct video_gfx *__restrict, unsigned int))(void *)-1)

/* Helpers for setting video buffer operators for ram-buffer-compatible buffers */

/* Requires: Derived from "struct video_rambuffer" */
#define video_buffer_ops_set_LOCKOPS_like_RAMBUFFER(self)          \
	(void)((self)->vi_rlock        = &rambuffer__lock,             \
	       (self)->vi_wlock        = &rambuffer__lock,             \
	       (self)->vi_unlock       = &libvideo_buffer_noop_unlock, \
	       (self)->vi_rlockregion  = &rambuffer__lockregion,       \
	       (self)->vi_wlockregion  = &rambuffer__lockregion,       \
	       (self)->vi_unlockregion = &libvideo_buffer_noop_unlockregion)

/* Requires: Derived from "struct video_rambuffer" */
#define video_buffer_ops_set_GFXOPS_like_RAMBUFFER(self) \
	(void)((self)->vi_initgfx   = &rambuffer__initgfx,   \
	       (self)->vi_updategfx = &rambuffer__updategfx)

/* Requires: Derived from "struct video_rambuffer" */
#define video_buffer_ops_set_SUBREGION_like_RAMBUFFER(self) \
	(void)((self)->vi_revoke    = &rambuffer__revoke,       \
	       (self)->vi_subregion = &rambuffer__subregion)


/************************************************************************/
/* RAMBUFFER GFX OPERATORS                                              */
/************************************************************************/
#define video_ramgfx_getdrv(self)  ((struct gfx_ramdrv *)(self)->_vg_driver)
#define video_ramgfx_getcdrv(self) ((struct gfx_ramdrv const *)(self)->_vg_driver)
struct gfx_ramdrv: gfx_swdrv {
	struct video_codec const *grd_codec;  /* [const][== video_gfx_getcodec(:this)] */
	byte_t                   *grd_data;   /* [const][== ((struct video_rambuffer *)video_gfx_getbuffer(:this))->rb_data] */
	size_t                    grd_stride; /* [const][== ((struct video_rambuffer *)video_gfx_getbuffer(:this))->rb_stride] */
};

INTDEF ATTR_IN(1) video_color_t CC ramgfx__getcolor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC ramgfx__putcolor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC ramgfx__putcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
#define DECLARE_ramgfx__putcolor_FOO(name, mode) \
	INTDEF ATTR_IN(1) void CC ramgfx__putcolor_##name(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
GFX_FOREACH_DEDICATED_BLENDMODE(DECLARE_ramgfx__putcolor_FOO)
GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(DECLARE_ramgfx__putcolor_FOO)
#undef DECLARE_ramgfx__putcolor_FOO
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx__getpixel(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC ramgfx__setpixel(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
#ifdef CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx__getpixel8(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx__getpixel16(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx__getpixel24(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx__getpixel32(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC ramgfx__setpixel8(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx__setpixel16(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx__setpixel24(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx__setpixel32(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
#endif /* CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS */




/* RAM DOMAIN OPERATORS */
INTDEF WUNUSED NONNULL((1)) ATTR_IN(2) REF struct video_buffer *CC
libvideo_ramdomain_newbuffer(struct video_domain const *__restrict self,
                             struct video_buffer_format const *__restrict format,
                             video_dim_t xdim, video_dim_t ydim, unsigned int flags);
INTDEF WUNUSED NONNULL((1, 5)) ATTR_IN(2) REF struct video_buffer *CC
libvideo_ramdomain_formem(struct video_domain const *__restrict self,
                          struct video_buffer_format const *__restrict format,
                          video_dim_t xdim, video_dim_t ydim, void *mem, size_t stride,
                          void (CC *release_mem)(void *cookie, void *mem),
                          void *release_mem_cookie, unsigned int flags);
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(2) NONNULL((1)) struct video_codec *CC
libvideo_ramdomain_supported_codec(struct video_domain const *__restrict self,
                                   struct video_codec const *__restrict codec);
/************************************************************************/





/* Returns the default, built-in "RAM" video domain.
 *
 * Video buffers allocated by / using this domain are driven
 * by  software-only  (without  any  hardware  acceleration)
 *
 * On the plus side: these buffers are generally able to do
 * much more than buffers from hardware domains, given that
 * they can support **any** video codec. */
INTDEF /*ATTR_CONST*/ ATTR_RETNONNULL WUNUSED struct video_domain const *CC _libvideo_ramdomain(void);
INTDEF struct video_domain libvideo_ramdomain;

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_RAMDOMAIN_H */
