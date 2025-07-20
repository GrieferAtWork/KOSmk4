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

#include <hybrid/compiler.h>

#include <hybrid/__atomic.h>
#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sequence/list.h>
#include <hybrid/typecore.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <stdbool.h>
#include <stddef.h>

#include <libvideo/codec/codecs.h>
#include <libvideo/codec/format.h>
#include <libvideo/codec/palette.h>
#include <libvideo/color.h>
#include <libvideo/gfx/buffer.h>
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
struct video_codec_handle;
struct video_buffer_dummy;

struct video_rambuffer_subregion;
LIST_HEAD(video_rambuffer_subregion_list, video_rambuffer_subregion);
struct video_rambuffer_base: video_buffer {
	/* This type is sufficient for doing simple GFX */
	byte_t *rb_data;   /* [1..1][owned][const] Buffer data */
	size_t  rb_stride; /* [const] Buffer stride */
};

struct video_rambuffer: video_rambuffer_base { /* vb_ops == &rambuffer_ops */
	struct video_rambuffer_subregion_list rb_subregions_list; /* [0..n][lock(rb_subregions_lock)] List of subregions */
	struct atomic_lock                    rb_subregions_lock; /* Lock for `rb_subregions_list' */
};
#define _video_rambuffer_init(self)          \
	(LIST_INIT(&(self)->rb_subregions_list), \
	 atomic_lock_init(&(self)->rb_subregions_lock))

struct video_rambuffer_xcodec: video_rambuffer { /* vb_ops == &rambuffer_xcodec_ops */
	REF struct video_codec_handle *rbxc_codec;   /* [1..1][const] Codec handle */
};

struct video_rambuffer_revokable_gfx {
	__REGISTER_TYPE__ rbrvg_inuse;  /* [lock(ATOMIC)] Non-zero while `rbrv_data' is being accessed */
	byte_t           *rbrvg_data;   /* [1..1][lock(ATOMIC)][valid_if(rbrv_inuse != 0)] Buffer data */
};
#define video_rambuffer_revokable_gfx_start(self)   __hybrid_atomic_inc(&(self)->rbrvg_inuse, __ATOMIC_ACQUIRE)
#define video_rambuffer_revokable_gfx_end(self)     __hybrid_atomic_dec(&(self)->rbrvg_inuse, __ATOMIC_RELEASE)
#define video_rambuffer_revokable_gfx_getdata(self) __hybrid_atomic_load(&(self)->rbrvg_data, __ATOMIC_ACQUIRE)


struct /*abstract*/ video_rambuffer_revokable: video_buffer {
	struct video_rambuffer_revokable_gfx rbrv_gfx;    /* Data shared with GFX */
	size_t                               rbrv_stride; /* [const] Buffer stride */
	REF struct video_buffer_dummy       *rbrv_dummy;  /* [1..1][const] Dummy data exchanged with `rbrv_data' during revoke */
};

struct video_rambuffer_revokable_subregion;
LIST_HEAD(video_rambuffer_revokable_subregion_list, video_rambuffer_revokable_subregion);
struct /*abstract*/ video_rambuffer_revokable_subregion: video_rambuffer_revokable {
	video_coord_t                                   rbrvsr_xoff;   /* [const] Extra X-offset added to all pixel coords */
	gfx_flag_t                                      rbrvsr_xflags; /* [const] Flags to XOR with `video_gfx::vx_flags' during `video_buffer_getgfx()' */
	LIST_ENTRY(video_rambuffer_revokable_subregion) rbrvsr_chain;  /* [lock([:rbsr_base,:rbssr_base,:rbfmsr_base]->rb_subregions_lock)] Link in chain of sub-regions of base */
	struct video_rambuffer_revokable_subregion_list rbrvsr_subsubregions_list; /* [0..n][lock(rbrvsr_subsubregions_lock)] List of sub-subregions */
	struct atomic_lock                              rbrvsr_subsubregions_lock; /* Lock for `rbrvsr_subsubregions_list' */
};

struct video_rambuffer_subregion: video_rambuffer_revokable_subregion { /* vb_ops == &rambuffer_subregion_ops || vb_ops == &rambuffer_subregion_xoff_ops */
	REF struct video_rambuffer *rbsr_base; /* [0..1][lock(ATOMIC && CLEAR_ONCE)] Underlying base buffer */
};

struct video_rambuffer_subsubregion: video_rambuffer_revokable_subregion { /* vb_ops == &rambuffer_subsubregion_ops || vb_ops == &rambuffer_subsubregion_xoff_ops */
	REF struct video_rambuffer_subregion *rbssr_base; /* [0..1][lock(ATOMIC && CLEAR_ONCE)] Underlying base buffer */
};

struct video_rambuffer_formem_subregion;
LIST_HEAD(video_rambuffer_formem_subregion_list, video_rambuffer_formem_subregion);
struct video_rambuffer_formem: video_rambuffer_revokable { /* vb_ops == &rambuffer_formem_ops */
	void (CC *rbfm_release_mem)(void *cookie, void *mem);  /* [1..1][const] Callback invoked the first time `rbrv_dummy' is written to `rbrv_data' */
	void     *rbfm_release_mem_cookie;                     /* [?..?][const] Cookie for `rbfm_release_mem' */
	struct video_rambuffer_formem_subregion_list rbfm_subregions_list; /* [0..n][lock(rbfm_subregions_lock)] List of subregions */
	struct atomic_lock                           rbfm_subregions_lock; /* Lock for `rbfm_subregions_list' */
};

struct video_rambuffer_formem_xcodec: video_rambuffer_formem { /* vb_ops == &rambuffer_formem_xcodec_ops */
	REF struct video_codec_handle *rbfmxc_codec; /* [1..1][const] Codec handle */
};

struct video_rambuffer_formem_subregion: video_rambuffer_revokable_subregion { /* vb_ops == &rambuffer_formem_subregion_ops || vb_ops == &rambuffer_formem_subregion_xoff_ops */
	REF struct video_rambuffer_formem *rbfmsr_base; /* [0..1][lock(ATOMIC && CLEAR_ONCE)] Underlying base buffer */
};


/* Video buffer types used to represent ram buffers.
 * NOTE: None of these ever look at `video_buffer::vb_domain',
 *       so you're free to  re-use these at the  driver-level! */
INTDEF struct video_buffer_ops rambuffer_ops;
INTDEF struct video_buffer_ops rambuffer_xcodec_ops;
INTDEF struct video_buffer_ops rambuffer_subregion_ops;
INTDEF struct video_buffer_ops rambuffer_subregion_xoff_ops;
INTDEF struct video_buffer_ops rambuffer_subsubregion_ops;
INTDEF struct video_buffer_ops rambuffer_subsubregion_xoff_ops;
INTDEF struct video_buffer_ops rambuffer_formem_ops;
INTDEF struct video_buffer_ops rambuffer_formem_xcodec_ops;
INTDEF struct video_buffer_ops rambuffer_formem_subregion_ops;
INTDEF struct video_buffer_ops rambuffer_formem_subregion_xoff_ops;

INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_xcodec_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_subregion_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_subregion_xoff_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_subsubregion_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_subsubregion_xoff_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_formem_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_formem_xcodec_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_formem_subregion_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _rambuffer_formem_subregion_xoff_ops(void);


/************************************************************************/
/* RAMBUFFER OPERATORS                                                  */
/************************************************************************/

/* DESTROY */
INTDEF NONNULL((1)) void FCC rambuffer__destroy(struct video_buffer *__restrict self);
INTDEF NONNULL((1)) void FCC rambuffer_xcodec__destroy(struct video_buffer *__restrict self);
INTDEF NONNULL((1)) void FCC rambuffer_subregion__destroy(struct video_buffer *__restrict self);
INTDEF NONNULL((1)) void FCC rambuffer_subsubregion__destroy(struct video_buffer *__restrict self);
INTDEF NONNULL((1)) void FCC rambuffer_formem__destroy(struct video_buffer *__restrict self);
INTDEF NONNULL((1)) void FCC rambuffer_formem_xcodec__destroy(struct video_buffer *__restrict self);
INTDEF NONNULL((1)) void FCC rambuffer_formem_subregion__destroy(struct video_buffer *__restrict self);

/* REVOKE+SUBREGION */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC rambuffer__revoke)(struct video_buffer *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC rambuffer_subregion__revoke)(struct video_buffer *__restrict self);
#define rambuffer_subsubregion__revoke rambuffer_subregion__revoke
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC rambuffer_formem__revoke)(struct video_buffer *__restrict self);
#define rambuffer_formem_subregion__revoke rambuffer_subregion__revoke
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC rambuffer__subregion(struct video_buffer *__restrict self, struct video_crect const *__restrict rect, gfx_flag_t xor_flags);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC rambuffer_subregion__subregion(struct video_buffer *__restrict self, struct video_crect const *__restrict rect, gfx_flag_t xor_flags);
#define rambuffer_subsubregion__subregion rambuffer_subregion__subregion
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC rambuffer_formem__subregion(struct video_buffer *__restrict self, struct video_crect const *__restrict rect, gfx_flag_t xor_flags);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC rambuffer_formem_subregion__subregion(struct video_buffer *__restrict self, struct video_crect const *__restrict rect, gfx_flag_t xor_flags);

/* LOCK */
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int FCC rambuffer__lock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC rambuffer__lockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int FCC rambuffer_revokable__lock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int FCC rambuffer_revokable__lockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int FCC rambuffer_revokable_xoff__lockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW(FCC rambuffer_revokable__unlock)(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
#define rambuffer_revokable__unlockregion      (*(void NOTHROW_T(FCC *)(struct video_buffer *__restrict, struct video_regionlock *__restrict))&rambuffer_revokable__unlock)
#define rambuffer_revokable_xoff__unlockregion rambuffer_revokable__unlockregion

/* GFX */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer__initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer__updategfx(struct video_gfx *__restrict self, unsigned int what);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer_revokable__initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer_revokable__updategfx(struct video_gfx *__restrict self, unsigned int what);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer_revokable_xoff__initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer_revokable_xoff__updategfx(struct video_gfx *__restrict self, unsigned int what);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC rambuffer_subregion__initgfx(struct video_gfx *__restrict self);

/* Helpers for setting video buffer operators for ram-buffer-compatible buffers */

/* Requires: Derived from "struct video_rambuffer_base" */
#define video_buffer_ops_set_LOCKOPS_like_RAMBUFFER(self)          \
	(void)((self)->vi_rlock        = &rambuffer__lock,             \
	       (self)->vi_wlock        = &rambuffer__lock,             \
	       (self)->vi_unlock       = &libvideo_buffer_noop_unlock, \
	       (self)->vi_rlockregion  = &rambuffer__lockregion,       \
	       (self)->vi_wlockregion  = &rambuffer__lockregion,       \
	       (self)->vi_unlockregion = &libvideo_buffer_noop_unlockregion)

/* Requires: Derived from "struct video_rambuffer_base" */
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
#define video_ramgfx_getdrv_common(self) \
	((struct gfx_ramdrv_common *)(self)->_vx_driver)
#define video_ramgfx_getcdrv_common(self) \
	((struct gfx_ramdrv_common const *)(self)->_vx_driver)
struct gfx_ramdrv_common: gfx_swdrv {
	struct video_format const *grdc_format; /* [const][== &((struct video_rambuffer *):vx_buffer)->vb_format] */
	size_t                     grdc_stride; /* [const][== ((struct video_rambuffer *):vx_buffer)->rb_stride] */
};

#define video_ramgfx_getdrv(self) \
	((struct gfx_ramdrv *)(self)->_vx_driver)
#define video_ramgfx_getcdrv(self) \
	((struct gfx_ramdrv const *)(self)->_vx_driver)
struct gfx_ramdrv: gfx_ramdrv_common {
	byte_t *grd_data;   /* [const][== ((struct video_rambuffer *):vx_buffer)->rb_data] */
};

#define video_ramgfx_getdrv_revokable(self) \
	((struct gfx_ramdrv_revokable *)(self)->_vx_driver)
#define video_ramgfx_getcdrv_revokable(self) \
	((struct gfx_ramdrv_revokable const *)(self)->_vx_driver)
struct gfx_ramdrv_revokable: gfx_ramdrv_common {
	struct video_rambuffer_revokable_gfx *grdrv_gfx; /* [const][== &((struct video_rambuffer_revokable *):vx_buffer)->rbrv_gfx] */
};

#define video_ramgfx_getdrv_revokable_xoff(self) \
	((struct gfx_ramdrv_revokable_xoff *)(self)->_vx_driver)
#define video_ramgfx_getcdrv_revokable_xoff(self) \
	((struct gfx_ramdrv_revokable_xoff const *)(self)->_vx_driver)
struct gfx_ramdrv_revokable_xoff: gfx_ramdrv_revokable {
	video_coord_t grdrvx_xoff; /* [const][== &((struct video_rambuffer_revokable_subregion *):vx_buffer)->rbrvsr_xoff] */
};

INTDEF ATTR_IN(1) video_color_t CC ramgfx__getcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_color_t CC ramgfx__getcolor_withkey(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_color_t CC ramgfx_revokable__getcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_color_t CC ramgfx_revokable__getcolor_withkey(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_color_t CC ramgfx_revokable_xoff__getcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_color_t CC ramgfx_revokable_xoff__getcolor_withkey(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC ramgfx__putcolor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC ramgfx__putcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC ramgfx_revokable__putcolor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC ramgfx_revokable__putcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC ramgfx_revokable_xoff__putcolor(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC ramgfx_revokable_xoff__putcolor_noblend(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
#define DECLARE_ramgfx__putcolor_FOO(name, mode)                                                                                                                 \
	INTDEF ATTR_IN(1) void CC ramgfx__putcolor_##name(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);           \
	INTDEF ATTR_IN(1) void CC ramgfx_revokable__putcolor_##name(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color); \
	INTDEF ATTR_IN(1) void CC ramgfx_revokable_xoff__putcolor_##name(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_color_t color);
GFX_FOREACH_DEDICATED_BLENDMODE(DECLARE_ramgfx__putcolor_FOO)
GFX_FOREACH_DEDICATED_BLENDMODE_FACTOR(DECLARE_ramgfx__putcolor_FOO)
#undef DECLARE_ramgfx__putcolor_FOO
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx__getpixel(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx_revokable__getpixel(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx_revokable_xoff__getpixel(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC ramgfx__setpixel(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx_revokable__setpixel(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx_revokable_xoff__setpixel(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
#ifdef CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx__getpixel8(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx__getpixel16(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx__getpixel24(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx__getpixel32(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx_revokable__getpixel8(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx_revokable__getpixel16(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx_revokable__getpixel24(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx_revokable__getpixel32(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx_revokable_xoff__getpixel8(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx_revokable_xoff__getpixel16(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx_revokable_xoff__getpixel24(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) video_pixel_t CC ramgfx_revokable_xoff__getpixel32(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y);
INTDEF ATTR_IN(1) void CC ramgfx__setpixel8(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx__setpixel16(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx__setpixel24(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx__setpixel32(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx_revokable__setpixel8(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx_revokable__setpixel16(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx_revokable__setpixel24(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx_revokable__setpixel32(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx_revokable_xoff__setpixel8(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx_revokable_xoff__setpixel16(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx_revokable_xoff__setpixel24(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
INTDEF ATTR_IN(1) void CC ramgfx_revokable_xoff__setpixel32(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_pixel_t pixel);
#endif /* CONFIG_HAVE_RAMBUFFER_PIXELn_FASTPASS */





INTDEF WUNUSED ATTR_IN(4) NONNULL((1)) REF struct video_buffer *CC
libvideo_ramdomain_newbuffer(struct video_domain const *__restrict self,
                             video_dim_t xdim, video_dim_t ydim,
                             struct video_format const *format,
                             unsigned int flags);
INTDEF WUNUSED ATTR_IN(4) NONNULL((1)) REF struct video_buffer *CC
libvideo_ramdomain_newbuffer_ex(struct video_domain const *__restrict self,
                                video_dim_t xdim, video_dim_t ydim,
                                struct video_codec_specs const *__restrict codec_specs,
                                struct video_palette *palette, unsigned int flags);
INTDEF WUNUSED ATTR_IN(4) NONNULL((1, 5)) REF struct video_buffer *CC
libvideo_ramdomain_formem(struct video_domain const *__restrict self, video_dim_t xdim, video_dim_t ydim,
                          struct video_format const *format, void *mem, size_t stride,
                          void (CC *release_mem)(void *cookie, void *mem),
                          void *release_mem_cookie, unsigned int flags);
INTDEF WUNUSED ATTR_IN(4) NONNULL((1, 6)) REF struct video_buffer *CC
libvideo_ramdomain_formem_ex(struct video_domain const *__restrict self, video_dim_t xdim, video_dim_t ydim,
                             struct video_codec_specs const *__restrict codec_specs,
                             struct video_palette *palette, void *mem, size_t stride,
                             void (CC *release_mem)(void *cookie, void *mem),
                             void *release_mem_cookie, unsigned int flags);
INTDEF ATTR_RETNONNULL WUNUSED ATTR_IN(2) NONNULL((1)) struct video_codec const *CC
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
