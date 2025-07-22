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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_REGION_H
#define GUARD_LIBVIDEO_GFX_BUFFER_REGION_H 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/sched/atomic-lock.h>
#include <hybrid/sequence/list.h>
#include <hybrid/typecore.h>

#include <kos/anno.h>

#include <libvideo/color.h>
#include <libvideo/crect.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "../gfx.h"

DECL_BEGIN

struct video_rect;
struct region_buffer;
struct region_buffer_subregion;
LIST_HEAD(region_buffer_subregion_list, region_buffer_subregion);

struct region_buffer: video_buffer {     /* vb_ops == &region_buffer_ops || vb_ops == &region_buffer_xoff_ops */
	video_offset_t           rbf_cxoff; /* [const] Starting X offset of Clip Rect in `rbf_base' */
	video_offset_t           rbf_cyoff; /* [const] Starting Y offset of Clip Rect in `rbf_base' */
	video_gfx_flag_t         rbf_gfx;   /* [const] GFX flags to apply during GFX init */
	REF struct video_buffer *rbf_base;  /* [1..1][lock(READ(ATOMIC), WRITE(ATOMIC && OLD_VALUE_VALID_UNTIL(rbf_inuse == 0)))])]
	                                     * Underlying video buffer.  Set to `libvideo_emptybuffer'  when revoking access.  When
	                                     * creating for a GFX context with an I/O Rect that differs from its Clip Rect, this is
	                                     * actually  a sub-region of  the original buffer, and  `rbf_cxoff' and `rbf_cyoff' are
	                                     * probably negative (to expand the Clip Rect to the top-left) */
	struct video_buffer     *rbf_orig;  /* [1..1][valid_if(rbf_inuse > 0 && rbf_base == rbf_orig)]
	                                     * The original video buffer (for releasing video locks  when
	                                     * `rbf_base' was revoked by another thread in the mean time) */
	__REGISTER_TYPE__        rbf_inuse; /* [lock(ATOMIC)] when  non-zero, any value ever assigned to "rbf_base" must remain valid
	                                     * In  practice, this counter is non-zero while video locks are held, or when doing pixel
	                                     * I/O. In turn, buffer revoke sets `rbf_base' to an empty buffer, then yields until this
	                                     * becomes "0". */
	struct region_buffer_subregion_list
	                         rbf_child_list; /* [0..n][lock(rbf_child_lock)] Sub-regions created from this "region_buffer" */
	struct atomic_lock       rbf_child_lock; /* Lock for `rbf_child_list' */
};

struct region_buffer_subregion: region_buffer {
	LIST_ENTRY(region_buffer_subregion) brbsr_chain;  /* [0..1][lock(brbsr_parent->rbf_child_lock)] Link in list of parent region sub-regions */
	REF struct region_buffer           *brbsr_parent; /* [0..1][lock(ATOMIC && CLEAR_ONCE)] Parent region buffer */
};

struct region_buffer_subregion_alias: region_buffer_subregion {
	/* Special sub-region that behaves a little different:
	 * >> rbf_base         [1..1][const]
	 * >> rbf_inuse        [UNUSED]
	 * >> rbf_cxoff == 0
	 * >> rbf_cyoff == 0
	 * >> rbf_gfx == 0
	 * >> vb_xdim == rbf_base->vb_xdim
	 * >> vb_ydim == rbf_base->vb_ydim
	 *
	 * This type of sub-region is simply aliasing the wrapped
	 * base-buffer, whilst  forwarding all  requests to  said
	 * buffer,   and  only  existing  to  enforce  revocation
	 * propagation when the parent region is revoked.
	 */
};


INTDEF struct video_buffer_ops region_buffer_ops;
INTDEF struct video_buffer_ops region_buffer_subregion_ops;
INTDEF struct video_buffer_ops region_buffer_subregion_alias_ops;

INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _region_buffer_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _region_buffer_subregion_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_buffer_ops const *CC _region_buffer_subregion_alias_ops(void);


/* Operators for region buffers, as seen above */

/* DESTROY */
INTDEF NONNULL((1)) void FCC region_buffer__destroy(struct video_buffer *__restrict self);
INTDEF NONNULL((1)) void FCC region_buffer_subregion__destroy(struct video_buffer *__restrict self);
#define region_buffer_subregion_alias__destroy region_buffer_subregion__destroy

/* REVOKE+SUBREGION */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC region_buffer__revoke)(struct video_buffer *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC region_buffer_subregion__revoke)(struct video_buffer *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_buffer *NOTHROW(FCC region_buffer_subregion_alias__revoke)(struct video_buffer *__restrict self);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC region_buffer__subregion(struct video_buffer *__restrict self, struct video_crect const *__restrict rect, video_gfx_flag_t gfx_flags);
#define region_buffer_subregion__subregion region_buffer__subregion
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *FCC region_buffer_subregion_alias__subregion(struct video_buffer *__restrict self, struct video_crect const *__restrict rect, video_gfx_flag_t gfx_flags);

/* LOCK */
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC region_buffer__rlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC region_buffer__wlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW(FCC region_buffer__unlockregion)(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC region_buffer_subregion_alias__rlock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC region_buffer_subregion_alias__wlock(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW(FCC region_buffer_subregion_alias__unlock)(struct video_buffer *__restrict self, struct video_lock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC region_buffer_subregion_alias__rlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) int FCC region_buffer_subregion_alias__wlockregion(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW(FCC region_buffer_subregion_alias__unlockregion)(struct video_buffer *__restrict self, struct video_regionlock *__restrict lock);

/* GFX */
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC region_buffer__initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC region_buffer__updategfx(struct video_gfx *__restrict self, unsigned int what);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC region_buffer_subregion_alias__initgfx(struct video_gfx *__restrict self);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *FCC region_buffer_subregion_alias__updategfx(struct video_gfx *__restrict self, unsigned int what);


/* GFX-OPERATORS
 *
 * Region buffers implement GFX/BLITTER/BLITTER3 in one of 2 ways:
 * - When the underlying buffer doesn't make use of the last driver
 *   data slot (iow: that slot is `NULL' and GFX init/update), then
 *   that slot is used to store the original GFX  `vx_hdr.vxh_ops':
 *   >> ... // Underlying init
 *   >> if (gfx->_vx_driver[_VIDEO_GFX_N_DRIVER - 1] == NULL) {
 *   >>     gfx->_vx_driver[_VIDEO_GFX_N_DRIVER - 1] = (void *)gfx->vx_hdr.vxh_ops;
 *   >>     gfx->vx_hdr.vxh_ops = &region_gfx_subops_ops;
 *   >> }
 * - Otherwise, if the last driver-slot is non-NULL, a fresh GFX
 *   context needs to be created for every high-level  operation
 *   performed,  and  the  original  (actual)  GFX  goes unused.
 *   >> else {
 *   >>     // In this case, `_vx_driver' (which was already
 *   >>     // initialized by the underlying buffer) goes unused
 *   >>     gfx->vx_hdr.vxh_ops = &region_gfx_subgfx_ops;
 *   >> }
 */
INTDEF struct video_gfx_ops region_gfx_subgfx_ops;
INTDEF struct video_gfx_ops region_gfx_subops_ops;
INTDEF struct video_blitter_ops region_blitter_subgfx_ops;
INTDEF struct video_blitter_ops region_blitter_subops_ops;
INTDEF struct video_blitter3_ops region_blitter3_subgfx_ops;
INTDEF struct video_blitter3_ops region_blitter3_subops_ops;

INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops *CC _region_gfx_subgfx_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_gfx_ops *CC _region_gfx_subops_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops *CC _region_blitter_subgfx_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter_ops *CC _region_blitter_subops_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter3_ops *CC _region_blitter3_subgfx_ops(void);
INTDEF ATTR_RETNONNULL WUNUSED struct video_blitter3_ops *CC _region_blitter3_subops_ops(void);

INTDEF ATTR_RETNONNULL ATTR_INOUT_T(1) struct video_blitter *FCC region_gfx_subgfx__blitfrom(struct video_blitter *__restrict ctx);
INTDEF ATTR_RETNONNULL ATTR_INOUT_T(1) struct video_blitter *FCC region_gfx_subops__blitfrom(struct video_blitter *__restrict ctx);
INTDEF ATTR_RETNONNULL ATTR_INOUT_T(1) struct video_blitter3 *FCC region_gfx_subgfx__blitfrom3(struct video_blitter3 *__restrict ctx);
INTDEF ATTR_RETNONNULL ATTR_INOUT_T(1) struct video_blitter3 *FCC region_gfx_subops__blitfrom3(struct video_blitter3 *__restrict ctx);
#define region_gfx_subgfx__clip libvideo_gfx_clip__generic
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) struct video_gfx *CC region_gfx_subops__clip(struct video_gfx *__restrict self, video_offset_t clip_x, video_offset_t clip_y, video_dim_t size_x, video_dim_t size_y);
#define region_gfx_subgfx__offset2coord libvideo_gfx_offset2coord__generic
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC region_gfx_subops__offset2coord(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_coord_t coords[2]);
#define region_gfx_subgfx__coord2offset libvideo_gfx_coord2offset__generic
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(4) bool CC region_gfx_subops__coord2offset(struct video_gfx const *__restrict self, video_coord_t x, video_coord_t y, video_offset_t offsets[2]);

INTDEF ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC region_gfx_subgfx__getcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_IN(1) void CC region_gfx_subgfx__putcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC region_gfx_subgfx__line(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC region_gfx_subgfx__hline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC region_gfx_subgfx__vline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC region_gfx_subgfx__fill(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC region_gfx_subgfx__rect(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC region_gfx_subgfx__fillmask(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC region_gfx_subgfx__fillstretchmask(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC region_gfx_subgfx__gradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) void CC region_gfx_subgfx__hgradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC region_gfx_subgfx__vgradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) ATTR_IN(4) void CC region_gfx_subgfx__bitblit(struct video_gfx const *dst, video_offset_t dst_x, video_offset_t dst_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC region_gfx_subgfx__stretch(struct video_gfx const *dst, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) ATTR_IN(4) ATTR_IN(7) void CC region_gfx_subgfx__bitblit3(struct video_gfx const *wrdst, video_offset_t wrdst_x, video_offset_t wrdst_y, struct video_gfx const *rddst, video_offset_t rddst_x, video_offset_t rddst_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) ATTR_IN(4) ATTR_IN(9) void CC region_gfx_subgfx__stretch3(struct video_gfx const *wrdst, video_offset_t wrdst_x, video_offset_t wrdst_y, struct video_gfx const *rddst, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);

INTDEF ATTR_PURE WUNUSED ATTR_IN(1) video_color_t CC region_gfx_subops__getcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y);
INTDEF ATTR_IN(1) void CC region_gfx_subops__putcolor(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_color_t color);
INTDEF ATTR_IN(1) void CC region_gfx_subops__line(struct video_gfx const *__restrict self, video_offset_t x1, video_offset_t y1, video_offset_t x2, video_offset_t y2, video_color_t color);
INTDEF ATTR_IN(1) void CC region_gfx_subops__hline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC region_gfx_subops__vline(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t length, video_color_t color);
INTDEF ATTR_IN(1) void CC region_gfx_subops__fill(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) void CC region_gfx_subops__rect(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t color);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(7) void CC region_gfx_subops__fillmask(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const bg_fg_colors[2], struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) ATTR_IN(9) void CC region_gfx_subops__fillstretchmask(struct video_gfx const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_color_t const bg_fg_colors[2], video_dim_t src_size_x, video_dim_t src_size_y, struct video_bitmask const *__restrict bm);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC region_gfx_subops__gradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t const colors[2][2]);
INTDEF ATTR_IN(1) void CC region_gfx_subops__hgradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) void CC region_gfx_subops__vgradient(struct video_gfx const *__restrict self, video_offset_t x, video_offset_t y, video_dim_t size_x, video_dim_t size_y, video_color_t locolor, video_color_t hicolor);
INTDEF ATTR_IN(1) ATTR_IN(4) void CC region_gfx_subops__bitblit(struct video_gfx const *dst, video_offset_t dst_x, video_offset_t dst_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) ATTR_IN(6) void CC region_gfx_subops__stretch(struct video_gfx const *dst, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN(1) ATTR_IN(4) ATTR_IN(7) void CC region_gfx_subops__bitblit3(struct video_gfx const *wrdst, video_offset_t wrdst_x, video_offset_t wrdst_y, struct video_gfx const *rddst, video_offset_t rddst_x, video_offset_t rddst_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN(1) ATTR_IN(4) ATTR_IN(9) void CC region_gfx_subops__stretch3(struct video_gfx const *wrdst, video_offset_t wrdst_x, video_offset_t wrdst_y, struct video_gfx const *rddst, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, struct video_gfx const *src, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);

INTDEF ATTR_IN_T(1) void CC region_blitter_subgfx__bitblit(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN_T(1) void CC region_blitter_subgfx__stretch(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN_T(1) void CC region_blitter3_subgfx__bitblit(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN_T(1) void CC region_blitter3_subgfx__stretch(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);

INTDEF ATTR_IN_T(1) void CC region_blitter_subops__bitblit(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN_T(1) void CC region_blitter_subops__stretch(struct video_blitter const *__restrict self, video_offset_t dst_x, video_offset_t dst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);
INTDEF ATTR_IN_T(1) void CC region_blitter3_subops__bitblit(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_offset_t src_x, video_offset_t src_y, video_dim_t size_x, video_dim_t size_y);
INTDEF ATTR_IN_T(1) void CC region_blitter3_subops__stretch(struct video_blitter3 const *__restrict self, video_offset_t wrdst_x, video_offset_t wrdst_y, video_offset_t rddst_x, video_offset_t rddst_y, video_dim_t dst_size_x, video_dim_t dst_size_y, video_offset_t src_x, video_offset_t src_y, video_dim_t src_size_x, video_dim_t src_size_y);








/* Create a new region-relative-proxy of `self', that interacts with the same
 * pixel data, both during GFX operations, as well when creating video locks.
 *
 * You can also use  this function to create  regions at negative offsets,  or
 * ones that are larger  than `self'. In this  case, the returned buffer  will
 * not be lockable, except when using `video_buffer_r/wlockregion' for regions
 * that  contain actual pixel  data. Similarly, GFX  operations for pixel data
 * outside  the true pixel area (which is enforced  by the I/O Rect of any GFX
 * created using the returned  buffer), will yield "0"  during read, and be  a
 * no-op during write.
 *
 * Then returned buffer always behaves properly when it comes to being able to
 * be  revoked, after which point it will never again make any access to pixel
 * data of `self'.
 *
 * When the given  `rect' is  actually a  sub-region of  `self', then  this
 * function will simply make use of `video_buffer_subregion()' and call the
 * dedicated video buffer operator for creating sub-regions.
 *
 * When the returned buffer isn't created as a true sub-region of  `self',
 * its `vb_domain' will be set to the return value of `video_ramdomain()'.
 *
 * @param: self: Video buffer to create a region of
 * @param: rect: region rect of `self' to-be returned
 * @param: gfx_flags: Flags to xor- toggle in GFX contexts created on  `return'.
 *                    These flags  are NOT  applied to  `rect', but  they  still
 *                    allow  you to create region buffers that will appear to be
 *                    natively  rotated in `struct video_gfx' contexts. Only the
 *                    following flags *should* be used here. All other flags can
 *                    still be used, but  many not necessarily produce  expected
 *                    results:
 *                    - VIDEO_GFX_F_XMIRROR
 *                    - VIDEO_GFX_F_YMIRROR
 *                    - VIDEO_GFX_F_XYSWAP
 * @return: * : The newly created region buffer
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=*] Failed to create region for some other reason */
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_buffer *CC
libvideo_buffer_region(struct video_buffer *__restrict self,
                       struct video_rect const *__restrict rect,
                       video_gfx_flag_t gfx_flags);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_REGION_H */
