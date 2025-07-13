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
#ifndef GUARD_LIBVIDEO_COMPOSITOR_COMPOSITOR_H
#define GUARD_LIBVIDEO_COMPOSITOR_COMPOSITOR_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-lock.h>

#include <kos/anno.h>
#include <kos/sched/shared-rwlock.h>
#include <sys/types.h>

#include <stdbool.h>
#include <stddef.h>

#include <libvideo/compositor/compositor.h>

DECL_BEGIN

/* ============= Window compositing mock-up =============
 *
 * - Background buffer (RGB buffer that represents the full what lies behind the window)
 *                      This buffer only exists when "Overlay buffer" is RGBA (else, it
 *                      can be left as NULL)
 * - Content buffer    (RGB/RGBA buffer of window contents as exposed to programs)
 * - Display buffer    (RGB buffer that is always the result of GFX_BLENDMODE_ALPHA-blending
 *                      "Content buffer" on-top  of "Background buffer".  This buffer  only
 *                      exists when "Overlay buffer" is RGBA (else, it can be left as NULL)
 * - Overlay buffer    (RGBA buffer that is GFX_BLENDMODE_ALPHA-blended on-top "Display buffer",
 *                      thereby representing data of windows with alpha channels that appear
 *                      over this one).
 * - Every window has a list of overlapping windows with a > Z-order
 * - Every window has a list of overlapping windows with a < Z-order
 *
 * A window then tells the compositor that it has updated a "copy-rect" in "Content buffer"
 * - if "Content buffer" is RGBA:
 *   - GFX_BLENDMODE_ALPHA-blend "copy-rect" of "Content" onto "Background" and store result in "Display buffer"
 *   - Use "Display buffer" as "Composited buffer" below
 *   else:
 *   - Use "Content buffer" as "Composited buffer" below
 * - GFX_BLENDMODE_ALPHA-blend "Composited buffer" with relevant region of "Overlay" and show result on-screen
 *   - Possible optimization here: if all relevant pixels from "Overlay" are opaque, no need to blit to screen
 * - Iterate over list of windows with a > Z-order in ascending order:
 *   - Truncate "copy-rect" to intersection with window
 *   - if "Content buffer" is RGB, don't recursively iterate intersection
 *   - GFX_BLENDMODE_OVERRIDE-blend "Composited buffer" to "Background buffer" of window
 *   - if last window in list, exit loop
 *   - if "Composited buffer" is still the "Content buffer" of the original window, copy it now
 *   - GFX_BLENDMODE_ALPHA-blend "Content buffer" of window onto "Composited buffer"
 *   - continue with next window in stack
 * - Iterate over list of windows with a < Z-order in descending order:
 *   - GFX_BLENDMODE_ALPHA-blend "Overlay buffer" of window at Z-order+1 onto "Content buffer"
 *     of  window  at  Z-order, and  store  result in  Overlay  buffer of  window  at Z-order.
 *   - Possible optimization here: if all relevant pixels from "Content buffer" are opaque, exit loop
 *   - continue with next window at Z-order-1
 *
 * [*] Locking omitted from above code
 */

/* Colors corresponding to 0/1 bits in `lw_overlay_mask' */
#define ALPHAMASK_0 VIDEO_COLOR_RGBA(VIDEO_CHANNEL_MIN, VIDEO_CHANNEL_MIN, VIDEO_CHANNEL_MIN, VIDEO_CHANNEL_MIN)
#define ALPHAMASK_1 VIDEO_COLOR_RGBA(VIDEO_CHANNEL_MIN, VIDEO_CHANNEL_MIN, VIDEO_CHANNEL_MIN, VIDEO_CHANNEL_MAX)


/************************************************************************/
/* LOCAL COMPOSITOR WINDOW                                              */
/************************************************************************/

/* Local compositor */
struct local_window;
TAILQ_HEAD(local_window_tailq, local_window);
struct local_window: video_window {
	struct video_window_attr   lw_attr;         /* [lock(local_window_comp(this)->lc_lock)] Window attributes (empty windows aren't allowed!) */
	REF struct video_buffer   *lw_content;      /* [1..1][lock(local_window_comp(this)->lc_lock)]
	                                             * - RGB/RGBA Content buffer (returned by `video_window_getbuffer()')
	                                             * - Alternatively, when `lw_passthru' is bound,  this is a revocable region  in
	                                             *   `local_window_comp(this)->lc_buffer' (s.a. `video_buffer_region_revoke()'). */
	TAILQ_ENTRY(local_window)  lw_passthru;     /* [0..1][lock(local_window_comp(this)->lc_lock)] Entry in the list of windows with passthru buffers */
	TAILQ_ENTRY(local_window)  lw_zorder;       /* [1..1][lock(local_window_comp(this)->lc_lock)] Entry in the list of all windows */
	TAILQ_ENTRY(local_window)  lw_zorder_visi;  /* [0..1][lock(local_window_comp(this)->lc_lock)] Entry in the list of all visible windows */
	REF struct video_buffer   *lw_background;   /* [0..1][(== NULL) == !(lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA)][lock(local_window_comp(this)->lc_lock)]
	                                             * - RGB Background buffer representing whatever lies behind this window.
	                                             * - Only present on windows that support an alpha-channel (VIDEO_WINDOW_F_ALPHA).
	                                             * - If the window doesn't support `VIDEO_WINDOW_F_ALPHA', this is always `NULL'.
	                                             * - During a rect update, "lw_content" is rendered onto  this
	                                             *   buffer, with the result then being stored in "lw_display" */
	REF struct video_buffer   *lw_display;      /* [0..1][(== NULL) == !(lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA)][lock(local_window_comp(this)->lc_lock)]
	                                             * - RGB buffer used to cache the ALPHABLEND-composite of `lw_content' rendered onto `lw_background'
	                                             * - Only present on windows that support an alpha-channel (VIDEO_WINDOW_F_ALPHA).
	                                             * - If the window doesn't support `VIDEO_WINDOW_F_ALPHA', this is always `NULL'. */
	/* TODO: when "lw_overlay_rgba_allcount == 1", lw_overlay_rgba can just be a subregion of the overlapping window's `lw_content' */
	REF struct video_buffer   *lw_overlay_rgba; /* [0..1][lock(local_window_comp(this)->lc_lock)]
	                                             * - RGBA buffer that gets blended over-top `lw_display' (or `lw_content' when this
	                                             *   window doesn't have an alpha-channel), prior  to the result being rendered  to
	                                             *   the compositor's output buffer.
	                                             * - Must be used during rect updates when `LOCAL_WINDOW_OVERLAY_RGBA'
	                                             * - Must be allocated  if there  exists a window  somewhere above  this
	                                             *   (doesn't  even need  to be in  `lw_winabove'; only needs  to have a
	                                             *   greater Z-order and intersect) that supports `VIDEO_WINDOW_F_ALPHA'
	                                             * - If none of the  windows that obscure  the pixels of  this one have  `VIDEO_WINDOW_F_ALPHA',
	                                             *   this buffer goes unused (but see `lw_overlay_mask', which (if present) must be used instead
	                                             *   or- or in addition to this overlay) */
	REF struct video_buffer   *lw_overlay_mask; /* [0..1][lock(local_window_comp(this)->lc_lock)]
	                                             * - `VIDEO_CODEC_A1_MSB'-buffer with 1-bits indicating pixels that are fully obscured  by
	                                             *   some other window with `VIDEO_WINDOW_F_ALPHA' disabled (overlapping windows that have
	                                             *   `VIDEO_WINDOW_F_ALPHA' enabled do not contribute to this mask)
	                                             * - Must be allocated  if there  exists a window  somewhere above  this
	                                             *   (doesn't  even need  to be in  `lw_winabove'; only needs  to have a
	                                             *   greater Z-order and intersect) that supports `VIDEO_WINDOW_F_ALPHA'
	                                             * - Must be used during rect updates when `LOCAL_WINDOW_OVERLAY_MASK' is set,
	                                             *   and `LOCAL_WINDOW_OVERLAY_RGBA' isn't set.
	                                             * - To use, this  buffer can used  to directly  `GFX_BLENDMODE_ALPHAMASK'-
	                                             *   blend `lw_display' (or `lw_content') to the compositors output buffer. */
	REF struct video_buffer   *lw_overlay_rend; /* [0..1][(!= NULL) == (lw_overlay_rgba && lw_overlay_mask)][lock(local_window_comp(this)->lc_lock)]
	                                             * - RGB overlay-render buffer that combines "lw_display" (or "lw_content") with "lw_overlay_rgba"
	                                             * - This buffer (when present) is then combined once again with `lw_overlay_mask' to produce the final render output.
	                                             * - This buffer is also **ONLY** allocated when **BOTH** `lw_overlay_rgba' and `lw_overlay_mask' are, too. */
	size_t lw_overlay_rgba_allcount; /* # of intersecting VIDEO_WINDOW_F_ALPHA-windows with > Z-order (including windows **above** prior intersections) */
	size_t lw_overlay_mask_allcount; /* # of intersecting non-VIDEO_WINDOW_F_ALPHA-windows with > Z-order (including windows **above** prior intersections) */
	/* TODO: Pre-cache GFX contexts for video buffers above */
};

#define local_window_comp(self) \
	video_compositor_aslocal((self)->vw_compositor)
#define local_window_fromdisplay(/*struct video_display*/ self) ((struct local_window *)(self))
#define local_window_fromwindow(/*struct video_window*/ self)   ((struct local_window *)(self))

/* Operator callbacks for "struct local_window" */
INTDEF NONNULL((1)) void LIBVIDEO_GFX_CC
local_window_destroy(struct video_display *__restrict self);
INTDEF WUNUSED ATTR_INOUT((1)) REF struct video_buffer *LIBVIDEO_GFX_CC
local_window_getbuffer(struct video_display *__restrict self);
INTDEF ATTR_INOUT(1) ATTR_IN(2) void LIBVIDEO_GFX_CC
local_window_updaterect(struct video_display *__restrict self,
                        struct video_rect const *__restrict rect);
INTDEF ATTR_INOUT(1) ATTR_INS(2, 3) void LIBVIDEO_GFX_CC
local_window_updaterects(struct video_display *__restrict self,
                         struct video_rect const *__restrict rects,
                         size_t n_rects);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int CC
local_window_getattr(struct video_window *__restrict self,
                     struct video_window_attr *__restrict attr);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) int CC
local_window_setposition(struct video_window *__restrict self,
                         struct video_window_position const *__restrict position);

INTDEF struct video_window_ops local_window_ops;
INTDEF ATTR_RETNONNULL WUNUSED struct video_window_ops *CC _local_window_ops(void);






/************************************************************************/
/* LOCAL COMPOSITOR CONTROLLER                                          */
/************************************************************************/

struct local_compositor: video_compositor {
	struct shared_rwlock       lc_lock;             /* Compositor lock */
	REF struct video_display  *lc_display;          /* [1..1][const] Output buffer */
	REF struct video_buffer   *lc_buffer;           /* [1..1][lock(lc_lock)] Output buffer */
	struct video_gfx           lc_buffer_gfx_write; /* [lock(lc_lock)] Pre-calculated GFX content for `lc_buffer' (with GFX_BLENDMODE_OVERRIDE) */
	struct video_gfx           lc_buffer_gfx_alpha; /* [lock(lc_lock)] Pre-calculated GFX content for `lc_buffer' (with GFX_BLENDMODE_ALPHA) */
	struct local_window_tailq  lc_passthru;         /* [0..n][lock(lc_lock)] List of windows where `lw_content' is a passthru to `lc_buffer' */
	struct local_window_tailq  lc_zorder;           /* [0..n][lock(lc_lock)] List of all windows */
	struct local_window_tailq  lc_zorder_visi;      /* [0..n][lock(lc_lock)] List of visible windows */
	/* TODO: "lc_zorder_visi" needs to use spatial partitioning (BSP tree) */
	video_color_t              lc_background;       /* [lock(lc_lock)] Background color */
	video_compositor_feature_t lc_features;         /* [lock(lc_lock)] Compositor features */
	unsigned int               lc_vidtyp;           /* [lock(lc_lock)] Buffer type used for new buffers (e.g. `VIDEO_BUFFER_AUTO') */
};

#define video_compositor_aslocal(self) ((struct local_compositor *)(self))
#define local_compositor_rlock(self)   shared_rwlock_read(&(self)->lc_lock)
#define local_compositor_runlock(self) shared_rwlock_endread(&(self)->lc_lock)
#define local_compositor_wlock(self)   shared_rwlock_write(&(self)->lc_lock)
#define local_compositor_wunlock(self) shared_rwlock_endwrite(&(self)->lc_lock)




typedef NONNULL_T((2)) ATTR_IN_T(3) ssize_t
(CC *local_compositor_foreach_cb_t)(void *cookie, struct local_window *window,
                                    struct video_rect const *intersect);
typedef NONNULL_T((2)) ATTR_IN_T(3) ssize_t
(CC *local_compositor_foreach_nohit_cb_t)(void *cookie, struct local_compositor *comp,
                                          struct video_rect const *nohit_area);
typedef NONNULL_T((2)) ATTR_IN_T(3) void
(CC *local_compositor_foreach_rollback_cb_t)(void *cookie, struct local_window *window,
                                             struct video_rect const *intersect);

/* Enumerate intersections of windows  with `rect', starting with  `window'
 * and moving  forward in  ascending Z-order.  Only the  first (resp.)  hit
 * with some window, that also overlaps with `rect', is enumerated, meaning
 * that the `intersect' rects passed to `cb' never overlap:
 *
 * >>   Y
 * >>   ^
 * >> 16|                  "start"
 * >> 15| `rect'           Window1        Window2       Window3        Window4
 * >> 14|               (partial hit)   (full hit)     (no hit)       (2 hits)
 * >> 13|
 * >> 12|                     |
 * >> 11|                     |                           |
 * >> 10|                     |                           |
 * >>  9|    |----------------|                           |
 * >>  8|    |----------------|
 * >>  7|    |------------------------------------------------------------------------...
 * >>  6|    |------------------------------------------------------------|
 * >>  5|    |------------------------------|                             |
 * >>  4|    |------------------------------|                             |
 * >>  3|    |------------------------------------------------------------|
 * >>  2|    |------------------------------------------------------------------------...
 * >>  1|
 * >>  0+------------------------------------------------------------------------------------>Z
 * >>                      "start"      "start+1"      "start+2"      "start+3"
 * >>  [depth (not displayed for simplicity) would be "X"; aka. window width]
 *
 * In  the above  example, `cb' would  be called as  follows (X-axis omitted):
 * >> (*cb)(cookie, Window1, { vr_ymin: 8, vr_ydim: 2 }); // "partial hit"
 * >> (*cb)(cookie, Window2, { vr_ymin: 4, vr_ydim: 2 }); // "full hit"
 * >> (*cb)(cookie, Window4, { vr_ymin: 3, vr_ydim: 1 }); // "2 hits" (part 1)
 * >> (*cb)(cookie, Window4, { vr_ymin: 6, vr_ydim: 1 }); // "2 hits" (part 2)
 * >> (*nohit)(cookie, self, { vr_ymin: 2, vr_ydim: 1 });
 * >> (*nohit)(cookie, self, { vr_ymin: 7, vr_ydim: 1 });
 *
 * @return: >= 0: Sum of return values of `cb'
 * @return: < 0 : First negative return values of `cb' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_above(struct local_compositor *__restrict self,
                               struct local_window *__restrict start,
                               struct video_rect const *rect,
                               local_compositor_foreach_cb_t cb,                /* [1..1] */
                               local_compositor_foreach_nohit_cb_t nohit,       /* [0..1] */
                               local_compositor_foreach_rollback_cb_t rollback, /* [0..1] */
                               void *cookie);

/* Same as "local_compositor_foreach_above", but cast rays towards negative Z */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_below(struct local_compositor *__restrict self,
                               struct local_window *__restrict start,
                               struct video_rect const *rect,
                               local_compositor_foreach_cb_t cb,                /* [1..1] */
                               local_compositor_foreach_nohit_cb_t nohit,       /* [0..1] */
                               local_compositor_foreach_rollback_cb_t rollback, /* [0..1] */
                               void *cookie);

/* Like above, but the imaginary "rays" being cast can travel through windows.
 * iow: these functions enumerate **all** windows and their intersections with
 *      the given `rect', even if the same sub-region intersects with multiple
 *      windows. */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_all_above(struct local_compositor *__restrict self,
                                   struct local_window *__restrict start,
                                   struct video_rect const *rect,
                                   local_compositor_foreach_cb_t cb, void *cookie);
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_all_below(struct local_compositor *__restrict self,
                                   struct local_window *__restrict start,
                                   struct video_rect const *rect,
                                   local_compositor_foreach_cb_t cb, void *cookie);


/* Force a re-draw of all windows (and the background) that intersect with `screen_rect' */
INTDEF ATTR_INOUT(1) ATTR_IN(2) void CC
local_compositor_updaterect__nopropagate(struct local_compositor *__restrict self,
                                         struct video_rect const *screen_rect);

/* Draw all pixels from windows behind (and including) `start', and intersecting
 * with  `screen_rect'.  Pixels written  to  `out' use  absolute  screen coords. */
INTDEF ATTR_INOUT(1) ATTR_IN(2) ATTR_IN(3) ATTR_INOUT(4) void CC
local_compositor_render_behind(struct local_compositor *__restrict self,
                               struct local_window *__restrict start,
                               struct video_rect const *screen_rect,
                               struct video_gfx *out);

/* Render RGBA data from window contents (and their overlays) into "out".
 * When non-NULL, `opt_nohit_color' is used to fill areas where there are
 * no other windows. */
INTDEF ATTR_INOUT(1) ATTR_IN(2) ATTR_IN(3) ATTR_INOUT(4) void CC
local_compositor_render_above(struct local_compositor *__restrict self,
                              struct local_window *__restrict start,
                              struct video_rect const *screen_rect,
                              struct video_gfx *out,
                              video_color_t *opt_nohit_color);



/* Local compositor API functions */
INTDEF ATTR_INOUT_T(1) void CC
local_compositor_destroy(struct video_compositor *__restrict self);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_window *CC
local_compositor_newwindow(struct video_compositor *__restrict self,
                           struct video_window_position const *__restrict position);
INTDEF WUNUSED ATTR_INOUT(1) REF struct video_display *CC
local_compositor_getdisplay(struct video_compositor *__restrict self);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) int CC
local_compositor_setdisplay(struct video_compositor *__restrict self,
                            struct video_display *__restrict display);
INTDEF WUNUSED ATTR_INOUT(1) int CC
local_compositor_updatebuffer(struct video_compositor *__restrict self);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int CC
local_compositor_getfeatures(struct video_compositor *__restrict self,
                             video_compositor_feature_t *__restrict p_features);
INTDEF WUNUSED ATTR_INOUT(1) int CC
local_compositor_setfeatures(struct video_compositor *__restrict self,
                             video_compositor_feature_t features);
INTDEF WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int CC
local_compositor_getbackground(struct video_compositor *__restrict self,
                               video_color_t *__restrict p_background);
INTDEF WUNUSED ATTR_INOUT(1) int CC
local_compositor_setbackground(struct video_compositor *__restrict self,
                               video_color_t background);

INTDEF struct video_compositor_ops local_compositor_ops;
INTDEF ATTR_RETNONNULL WUNUSED struct video_compositor_ops *CC _local_compositor_ops(void);



/* Create a new video compositor  for `display'. The compositor  returned
 * by this function will run in the caller's process, meaning it does not
 * impose any `EPERM'-like restrictions.
 * @return: * :   The newly created compositor
 * @return: NULL: [errno=ENOMEM] Out of memory */
INTDEF ATTR_INOUT(1) REF struct video_compositor *CC
libvideo_compositor_create(struct video_display *__restrict display,
                           video_compositor_feature_t features,
                           video_color_t background);

DECL_END

#endif /* !GUARD_LIBVIDEO_COMPOSITOR_COMPOSITOR_H */
