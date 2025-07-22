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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_CUSTOM_H
#define GUARD_LIBVIDEO_GFX_BUFFER_CUSTOM_H 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sequence/list.h>
#include <hybrid/typecore.h>

#include <kos/anno.h>

#include <stddef.h>

#include <libvideo/color.h>
#include <libvideo/crect.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/codec/format.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "../swgfx.h"

DECL_BEGIN

struct custom_buffer_subregion;
LIST_HEAD(custom_buffer_subregion_list, custom_buffer_subregion);

struct custom_buffer_common: video_buffer {
	video_buffer_custom_getpixel_t      cbc_getpixel;       /* [1..1][lock(ATOMIC)] ... */
	video_buffer_custom_setpixel_t      cbc_setpixel;       /* [1..1][lock(ATOMIC)] ... */
	video_buffer_custom_lock_t          cbc_rlock;          /* [0..1][lock(ATOMIC)] ... */
	video_buffer_custom_lock_t          cbc_wlock;          /* [0..1][lock(ATOMIC)] ... */
	video_buffer_custom_unlock_t        cbc_unlock;         /* [const] ... */
	video_buffer_custom_lockregion_t    cbc_rlockregion;    /* [0..1][lock(ATOMIC)] ... */
	video_buffer_custom_lockregion_t    cbc_wlockregion;    /* [0..1][lock(ATOMIC)] ... */
	video_buffer_custom_unlockregion_t  cbc_unlockregion;   /* [const] ... */
	void                               *cbc_cookie;         /* [?..?][const] ... */
	__REGISTER_TYPE__                   cbc_inuse;          /* Non-zero while pixel the buffer is considered to be in-use */
	struct custom_buffer_subregion_list cbc_subregion_list; /* [0..n][lock(cb_subregion_lock)] Sub-regions of this custom buffer */
	struct atomic_lock                  cbc_subregion_lock; /* Lock for `cb_subregion_list' */
};

struct custom_buffer: custom_buffer_common {
	video_buffer_custom_destroy_t cb_destroy; /* [0..1][const] ... */
	video_buffer_custom_revoke_t  cb_revoke;  /* [0..1][lock(CLEAR_ONCE)] ... */
};

struct custom_buffer_subregion: custom_buffer_common {
	video_gfx_flag_t                    cbsr_gfx;    /* [const] GFX flags to apply during GFX init */
	video_coord_t                       cbsr_xoff;   /* [const] X-offset to add to all pixel coords */
	video_coord_t                       cbsr_yoff;   /* [const] Y-offset to add to all pixel coords */
	size_t                              cbsr_bxoff;  /* [const] In-scanline byte offset for `cbsr_xoff' */
	video_coord_t                       cbsr_bxrem;  /* [const] Remaining pixel-offset after `cbsr_bxoff' */
	REF struct custom_buffer_common    *cbsr_parent; /* [0..1][lock(CLEAR_ONCE)] Parent buffer */
	LIST_ENTRY(custom_buffer_subregion) cbsr_link;   /* [0..1][lock(cbsr_parent->cbc_subregion_lock)] Link in parent list of sub-regions */
};


/* Custom buffer operator types */
INTDEF struct video_buffer_ops custom_buffer_ops;
INTDEF struct video_buffer_ops custom_buffer_subregion_ops;       /* (cbsr_xoff != 0 || cbsr_yoff != 0) && cbsr_bxrem != 0 */
INTDEF struct video_buffer_ops custom_buffer_subregion_norem_ops; /* (cbsr_xoff == 0 && cbsr_yoff == 0) && cbsr_bxrem == 0 */
INTDEF struct video_buffer_ops custom_buffer_subregion_nooff_ops; /* cbsr_xoff == 0 && cbsr_yoff == 0 */

INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _custom_buffer_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _custom_buffer_subregion_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _custom_buffer_subregion_norem_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _custom_buffer_subregion_nooff_ops(void);


/* Operators for custom buffers, as seen above */

/* DESTROY */
INTDEF NONNULL((1)) void FCC custom_buffer__destroy(struct video_buffer *__restrict self);
INTDEF NONNULL((1)) void FCC custom_buffer_subregion__destroy(struct video_buffer *__restrict self);

/* REVOKE+SUBREGION */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC custom_buffer__revoke)(struct video_buffer *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC custom_buffer_subregion__revoke)(struct video_buffer *__restrict self);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC custom_buffer__subregion(struct video_buffer *__restrict self, struct video_crect const *__restrict rect, video_gfx_flag_t gfx_flags);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC custom_buffer_subregion__subregion(struct video_buffer *__restrict self, struct video_crect const *__restrict rect, video_gfx_flag_t gfx_flags);

/* LOCK */
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC custom_buffer__rlock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC custom_buffer__wlock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW(FCC custom_buffer__unlock)(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC custom_buffer_subregion__rlock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC custom_buffer_subregion__wlock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW(FCC custom_buffer_subregion__unlock)(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC custom_buffer__rlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC custom_buffer__wlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW(FCC custom_buffer__unlockregion)(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC custom_buffer_subregion__rlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC custom_buffer_subregion__wlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW(FCC custom_buffer_subregion__unlockregion)(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);

/* GFX */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC custom_buffer__initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC custom_buffer_subregion__initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC custom_buffer_subregion_nooff__initgfx(struct video_gfx *__restrict self);


/* GFX operators (built on-top of "SWGFX") */
struct gfx_customdrv: gfx_swdrv {
};
#define video_customgfx_getdrv(self) \
	((struct gfx_customdrv *)(self)->_vx_driver)
#define video_customgfx_getcdrv(self) \
	((struct gfx_customdrv const *)(self)->_vx_driver)

INTDEF ATTR_IN(1) video_pixel_t CC custom_gfx__getpixel(struct video_gfx const *__restrict self, video_coord_t abs_x, video_coord_t abs_y);
INTDEF ATTR_IN(1) void CC custom_gfx__setpixel(struct video_gfx const *__restrict self, video_coord_t abs_x, video_coord_t abs_y, video_pixel_t pixel);
INTDEF ATTR_IN(1) video_pixel_t CC custom_gfx_subregion__getpixel(struct video_gfx const *__restrict self, video_coord_t abs_x, video_coord_t abs_y);
INTDEF ATTR_IN(1) void CC custom_gfx_subregion__setpixel(struct video_gfx const *__restrict self, video_coord_t abs_x, video_coord_t abs_y, video_pixel_t pixel);




/* Construct a special video buffer which, rather than being backed by memory
 * or implemented using hardware acceleration,  does all its pixel I/O  using
 * the provided function pointers.
 *
 * WARNING: The  given  `getpixel'  / `setpixel'  callbacks  better be
 *          fast, or any GFX on the returned buffer will take forever!
 *
 * @param: size_x:       X dimension of the returned video buffer
 * @param: size_y:       Y dimension of the returned video buffer
 * @param: format:       [1..1] Video format used for color<=>pixel conversion,
 *                              as well as pixel I/O (when rlock/wlock is given
 *                              and returns `0')
 * @param: palette:      [0..1] Palette to-be used with `codec' (if needed)
 * @param: getpixel:     [1..1] Mandatory pixel read operator (passed coords are absolute and guarantied in-bounds)
 * @param: setpixel:     [1..1] Mandatory pixel write operator (passed coords are absolute and guarantied in-bounds)
 * @param: destroy:      [0..1] Optional callback invoked when the returned buffer is destroyed
 * @param: rlock:        [0..1] Optional callback to lock video memory for reading (when missing, or doesn't return `0', `getpixel' is always used)
 * @param: wlock:        [0..1] Optional callback to lock video memory for writing (when missing, or doesn't return `0', `setpixel' is always used)
 * @param: unlock:       [0..1] Optional callback invoked to release video locks previously acquired by `rlock' or `wlock'
 * @param: rlockregion:  [0..1] Optional extension to `rlock' (when not supplied, implemented in terms of `rlock')
 * @param: wlockregion:  [0..1] Optional extension to `wlock' (when not supplied, implemented in terms of `wlock')
 * @param: unlockregion: [0..1] Optional extension to `unlock' (when not supplied, implemented in terms of `unlock')
 * @param: revoke:       [0..1] Optional callback invoked when the returned buffer is revoked.
 * @param: cookie:       [?..?] Cookie argument passed to all user-supplied operators */
INTDEF WUNUSED NONNULL((3, 4, 5)) REF struct video_buffer *CC
libvideo_buffer_forcustom(video_dim_t size_x, video_dim_t size_y,
                          struct video_format const *__restrict format,
                          video_buffer_custom_getpixel_t getpixel,
                          video_buffer_custom_setpixel_t setpixel,
                          video_buffer_custom_destroy_t destroy,
                          video_buffer_custom_lock_t rlock,
                          video_buffer_custom_lock_t wlock,
                          video_buffer_custom_unlock_t unlock,
                          video_buffer_custom_lockregion_t rlockregion,
                          video_buffer_custom_lockregion_t wlockregion,
                          video_buffer_custom_unlockregion_t unlockregion,
                          video_buffer_custom_revoke_t revoke,
                          void *cookie);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_CUSTOM_H */
