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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_LOCKABLE_H
#define GUARD_LIBVIDEO_GFX_BUFFER_LOCKABLE_H 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-lock.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <stddef.h>

#include <libc/malloc.h>
#include <libvideo/gfx/buffer.h>

DECL_BEGIN

struct lockable_buffer_base: video_buffer {
	REF struct video_buffer *lbb_base;   /* [1..1][const] Underlying video buffer */
	byte_t                  *lbb_data;   /* [0..vl_size][owned][lock(WRITE_ONCE)] Cached video data */
	size_t                   lbb_stride; /* [valid_if(lbb_data)] Scanline width (in bytes) */
	byte_t                  *lbb_edata;  /* [valid_if(lbb_data)] End of lock data */
};

/* Check if `buffer'  is lockable. If  so re-return  "buffer"
 * and initialize `self' such that `lockable_buffer_finibase'
 * does nothing. Else, wrap it using `buffer' and return *it*
 * instead. */
INTDEF WUNUSED ATTR_OUT(1) NONNULL((2)) struct video_buffer *CC
lockable_buffer_initbase(struct lockable_buffer_base *self,
                         struct video_buffer *__restrict buffer);
#define lockable_buffer_finibase(self) __libc_free((self)->lbb_data)



struct lockable_buffer_subregion;
LIST_HEAD(lockable_buffer_subregion_list, lockable_buffer_subregion);
struct lockable_buffer: lockable_buffer_base {
	struct lockable_buffer_subregion_list lb_subregion_list; /* [0..n][lock(lb_subregion_lock)] List of sub-regions */
	struct atomic_lock                    lb_subregion_lock; /* Lock for `lb_subregion_list' */
};
struct lockable_buffer_subregion: lockable_buffer {    /* [OVERRIDE(.lbb_data, [0..1][lock(WRITE_ONCE)][NOT(owned)])]
                                                        * [OVERRIDE(.lbb_base, [NOT(REF)])] */
	video_coord_t                         lbsb_xoff;   /* [const] X offset */
	video_coord_t                         lbsb_yoff;   /* [const] Y offset */
	gfx_flag_t                            lbsb_xor;    /* [const] GFX XOR flags */
	video_coord_t                         lbsb_bxrem;  /* [const] X coord remainder that needs to be added to `lbb_data' */
	size_t                                lbsb_bxoff;  /* [const] X byte offset that needs to be added to `lbb_data->lbb_base' */
	struct lockable_buffer               *lbsb_orig;   /* [1..1][const] Original lockable buffer */
	REF struct lockable_buffer           *lbsb_parent; /* [1..1][const] Parent buffer */
	LIST_ENTRY(lockable_buffer_subregion) lbsb_chain;  /* [0..n][lock(lbsb_parent->lb_subregion_lock)] Entry in chain of sub-region of `lbsb_parent' */
};


/* Lockable buffer operator types */
INTDEF struct video_buffer_ops lockable_buffer_ops;
INTDEF struct video_buffer_ops lockable_buffer_subregion_ops;       /* lbsb_bxrem != 0 */
INTDEF struct video_buffer_ops lockable_buffer_subregion_norem_ops; /* lbsb_bxrem == 0 */

INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _lockable_buffer_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _lockable_buffer_subregion_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _lockable_buffer_subregion_norem_ops(void);


/* Operators for lockable buffers, as seen above */

/* DESTROY */
INTDEF NONNULL((1)) void FCC lockable_buffer__destroy(struct video_buffer *__restrict self);
INTDEF NONNULL((1)) void FCC lockable_buffer_subregion__destroy(struct video_buffer *__restrict self);

/* REVOKE+SUBREGION */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC lockable_buffer__revoke)(struct video_buffer *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC lockable_buffer_subregion__revoke)(struct video_buffer *__restrict self);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC lockable_buffer__subregion(struct video_buffer *__restrict self, struct video_crect const *__restrict rect, gfx_flag_t xor_flags);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC lockable_buffer_subregion__subregion(struct video_buffer *__restrict self, struct video_crect const *__restrict rect, gfx_flag_t xor_flags);

/* LOCK */
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC lockable_buffer__rlock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC lockable_buffer__wlock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW(FCC lockable_buffer__unlock)(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC lockable_buffer__rlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC lockable_buffer__wlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW(FCC lockable_buffer__unlockregion)(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC lockable_buffer_subregion__rlock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC lockable_buffer_subregion__wlock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW(FCC lockable_buffer_subregion__unlock)(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC lockable_buffer_subregion__rlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC lockable_buffer_subregion__wlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW(FCC lockable_buffer_subregion__unlockregion)(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);

/* GFX */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC lockable_buffer__initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC lockable_buffer_subregion__initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC lockable_buffer__updategfx(struct video_gfx *__restrict self, unsigned int what);




/* When `self' isn't  known to unconditionally  support read/write  locks,
 * wrap it using a proxy video buffer that implements these operations as:
 * - Attempt the lock on the underlying buffer.
 * - If that fails:
 *   - Allocate a heap buffer matching requirements of the buffer's codec
 *   - If that fails, return from vi_rlock/vi_wlock with -1,errno=ENOMEM
 *   - On success, use a GFX context to read pixel data and store it in
 *     the heap buffer.
 *   - Return said heap buffer from vi_rlock/vi_wlock
 * - In case `vi_wlock' was called, the matching `vi_unlock' will  then
 *   once again use a GFX context to at least all modified (or possibly
 *   just all) pixels back to the underlying buffer.
 * @param: self:  The video buffer to wrap
 * @return: * :   The video buffer wrapper (having the same codec/dimensions as `self')
 * @return: self: The given `self' is already  known to have vi_rlock/vi_wlock  operators
 *                that either never fail, or can only fail with errno=ENOMEM for the same
 *                reason that the  "lockable" wrapper could  also fail. (generally,  this
 *                means that this is a no-op when  `self' is a ram-buffer, or is  already
 *                a "lockable" video buffer). */
INTDEF WUNUSED ATTR_INOUT(1) REF struct video_buffer *CC
libvideo_buffer_lockable(struct video_buffer *__restrict self);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_LOCKABLE_H */
