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
#ifndef GUARD_LIBVIDEO_COMPOSITOR_COMPOSITOR_C
#define GUARD_LIBVIDEO_COMPOSITOR_COMPOSITOR_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <malloc.h>
#include <string.h>

#include <libvideo/codec/rectutils.h>
#include <libvideo/compositor/compositor.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "compositor.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#ifndef NDEBUG

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_window_assert_count_above_cb(void *cookie, struct local_window *window,
                                   struct video_rect const *UNUSED(intersect)) {
	size_t *hits = (size_t *)cookie;
	if (window->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA) {
		++hits[1];
	} else {
		++hits[0];
	}
	return 0;
}

PRIVATE NONNULL((1)) void LIBVIDEO_GFX_CC
local_window_assert(struct local_window *__restrict me) {
	assert(TAILQ_ISBOUND(me, lw_zorder));
	assertf((me->lw_overlay_rgba != NULL) == (me->lw_overlay_rgba_allcount != 0),
	        "RGBA overlay must be allocated iff there are ALPHA-windows overtop ours");
	assertf((me->lw_overlay_mask != NULL) == (me->lw_overlay_mask_allcount != 0),
	        "MASK overlay must be allocated iff there are non-ALPHA-windows overtop ours");
	assertf((me->lw_overlay_rend != NULL) == (me->lw_overlay_rgba != NULL && me->lw_overlay_mask != NULL),
	        "RENDER overlay is **ONLY** needed when **BOTH** RGBA and MASK overlays are present");
	assertf(me->lw_content, "Content buffer must always be allocated");
	assertf(!(me->lw_attr.vwa_flags & ~VIDEO_WINDOW_F_ALL), "Window has unknown flags");
	if (me->lw_attr.vwa_flags & VIDEO_WINDOW_F_HIDDEN) {
		assertf(!TAILQ_ISBOUND(me, lw_zorder_visi), "Hidden windows can't be in visible Z-order list");
		assertf(!TAILQ_ISBOUND(me, lw_passthru), "Hidden windows can't use passthru buffers");
		assertf(!me->lw_overlay_rgba, "RGBA overlay not needed for hidden window");
		assertf(!me->lw_overlay_mask, "MASK overlay not needed for hidden window");
		assertf(!me->lw_background, "Background buffer isn't needed by hidden window");
		assertf(!me->lw_display, "Display buffer isn't needed by hidden window");
	} else {
		assertf(TAILQ_ISBOUND(me, lw_zorder_visi), "Visible window must be part of visible Z-order list");
		if (TAILQ_ISBOUND(me, lw_passthru)) {
			assert(me->lw_attr.vwa_flags & VIDEO_WINDOW_F_PASSTHRU);
			assert(!(me->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA));
			assertf(me->lw_overlay_rgba_allcount == 0 && !me->lw_overlay_rgba,
			        "Passthru with RGBA overlay is impossible");
			assertf(me->lw_overlay_mask_allcount == 0 && !me->lw_overlay_mask,
			        /* XXX: Passthru here is possible if unobstructed portion is a rect */
			        "Passthru with MASK overlay is impossible");
			/* Could also assert that `me->lw_content' is revocable */
			assertf(!me->lw_background, "Non-ALPHA (and passthru especially) windows can't have a background");
			assertf(!me->lw_display, "Non-ALPHA (and passthru especially) windows can't have a display cache");
		} else {
			size_t above_hits[2];
			if (me->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA) {
				assertf(me->lw_background, "Need a background buffer for alpha-enabled windows");
				assertf(me->lw_display, "Need a display buffer for alpha-enabled windows");
			} else {
				assertf(!me->lw_background, "Non-alpha windows can't have a background buffer");
				assertf(!me->lw_display, "Non-alpha windows can't have a display buffer");
			}
			above_hits[0] = 0;
			above_hits[1] = 0;
			if (TAILQ_NEXT(me, lw_zorder_visi) != NULL) {
				local_compositor_foreach_all_above(local_window_comp(me),
				                                   TAILQ_NEXT(me, lw_zorder_visi),
				                                   &me->lw_attr.vwa_rect,
				                                   &local_window_assert_count_above_cb,
				                                   above_hits);
			}
			assertf(me->lw_overlay_rgba_allcount == above_hits[1],
			        "Wrong # of alpha-enabled window over this one:\n"
			        "should be %" PRIuSIZ ", but is %" PRIuSIZ,
			        above_hits[1], me->lw_overlay_rgba_allcount);
			assertf(me->lw_overlay_mask_allcount == above_hits[0],
			        "Wrong # of alpha-disabled window over this one:\n"
			        "should be %" PRIuSIZ ", but is %" PRIuSIZ,
			        above_hits[0], me->lw_overlay_mask_allcount);
		}
	}
}
#else /* !NDEBUG */
#define local_window_assert(me) (void)0
#endif /* NDEBUG */


/* Copy lw_overlay_rgba/lw_overlay_mask from "src" into "dst"
 * where  the  2  windows  overlap  as  per  "screen_region". */
PRIVATE NONNULL((1)) void CC
local_window_copy_overlay(struct local_window *__restrict src,
                          struct local_window *__restrict dst,
                          struct video_rect const *screen_region) {
	struct local_compositor *comp = local_window_comp(dst);
	video_offset_t dst_x = screen_region->vr_xmin - dst->lw_attr.vwa_rect.vr_xmin;
	video_offset_t dst_y = screen_region->vr_ymin - dst->lw_attr.vwa_rect.vr_ymin;
	video_offset_t src_x = screen_region->vr_xmin - src->lw_attr.vwa_rect.vr_xmin;
	video_offset_t src_y = screen_region->vr_ymin - src->lw_attr.vwa_rect.vr_ymin;
	assert(comp == local_window_comp(src));

	/* Copy RGBA overlay data */
	if (dst->lw_overlay_rgba) {
		/* Copy from "src" to "dst->lw_overlay_rgba" */
		struct video_gfx dst_gfx;
		video_buffer_getgfx(dst->lw_overlay_rgba, &dst_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		if (src->lw_overlay_rgba == NULL) {
			struct local_window *src_above = TAILQ_NEXT(src, lw_zorder_visi);
			video_color_t nohit_color = VIDEO_COLOR_RGBA(0, 0, 0, 0);
			if (src_above) {
				video_gfx_clip(&dst_gfx,
				               -dst->lw_attr.vwa_rect.vr_xmin,
				               -dst->lw_attr.vwa_rect.vr_ymin,
				               dst->lw_attr.vwa_rect.vr_xmin + video_gfx_getclipw(&dst_gfx),
				               dst->lw_attr.vwa_rect.vr_ymin + video_gfx_getcliph(&dst_gfx));
				/* XXX: This also properly handles MASK overlays, but that isn't actually needed here! */
				local_compositor_render_above(comp, src_above, screen_region,
				                              &dst_gfx, &nohit_color);
			} else {
				video_gfx_fill(&dst_gfx, dst_x, dst_y,
				               screen_region->vr_xdim,
				               screen_region->vr_ydim,
				               nohit_color);
			}
		} else {
			struct video_gfx src_gfx;
			video_buffer_getgfx(src->lw_overlay_rgba, &src_gfx,
			                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
			video_gfx_bitblit(&dst_gfx, dst_x, dst_y,
			                  &src_gfx, src_x, src_y,
			                  screen_region->vr_xdim,
			                  screen_region->vr_ydim);
		}
	}

	/* Copy MASK overlay data */
	if (dst->lw_overlay_mask) {
		struct video_gfx dst_gfx;
		video_buffer_getgfx(dst->lw_overlay_mask, &dst_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		if (src->lw_overlay_mask) {
			/* Copy from "src->lw_overlay_mask" to "dst->lw_overlay_mask" */
			struct video_gfx src_gfx;
			video_buffer_getgfx(src->lw_overlay_mask, &src_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
			video_gfx_bitblit(&dst_gfx, dst_x, dst_y,
			                  &src_gfx, src_x, src_y,
			                  screen_region->vr_xdim,
			                  screen_region->vr_ydim);
		} else {
			/* Set bits in "dst->lw_overlay_mask" */
			video_gfx_fill(&dst_gfx, dst_x, dst_y,
			               screen_region->vr_xdim,
			               screen_region->vr_ydim,
			               ALPHAMASK_1);
		}
	}
}

PRIVATE NONNULL((1)) ssize_t CC
local_window_hide__locked_below_cb(void *cookie, struct local_window *window,
                                   struct video_rect const *intersect) {
	struct local_window *src = (struct local_window *)cookie;
	local_window_copy_overlay(src, window, intersect);
	return 0;
}

/* Try to convert the "self" into a buffer passthru window. No-op if:
 * - Not allowed by compositor / window
 * - Window is (at least partially) obstructed
 * - Allocation of a passthru buffer failed */
PRIVATE ATTR_INOUT(1) void CC
try_convert_window_to_passthru(struct local_window *__restrict self) {
	REF struct video_buffer *old_content;
	REF struct video_buffer *new_content;
	struct local_compositor *comp = local_window_comp(self);
	if ((self->lw_attr.vwa_flags & (VIDEO_WINDOW_F_ALPHA |
	                                VIDEO_WINDOW_F_PASSTHRU |
	                                VIDEO_WINDOW_F_HIDDEN)) !=
	    (VIDEO_WINDOW_F_PASSTHRU))
		return; /* Not allocated by window */
	if (!(comp->lc_features & VIDEO_COMPOSITOR_FEAT_PASSTHRU))
		return; /* Not allocated by compositor */
	if (self->lw_overlay_rgba_allcount || self->lw_overlay_mask_allcount)
		return; /* Not possible for window */
	if (TAILQ_ISBOUND(self, lw_passthru))
		return; /* Already enabled for window */
	assert(self->lw_content);
	assert(!self->lw_background);
	assert(!self->lw_display);
	assert(!self->lw_overlay_rgba);
	assert(!self->lw_overlay_mask);
	assert(!self->lw_overlay_rend);

	/* XXX: Either we need  to disallow partially  (or fully) off-screen  windows
	 *      from using a passthru buffer, or we need some way to force the window
	 *      to  re-draw then-visible display  data after being  moved to be fully
	 *      on-screen. (as it  stands, allowing partially  off-screen windows  to
	 *      use passthru buffers  means that anything  rendered off-screen  won't
	 *      become viewable, even if the window  is moved to be fully  on-screen) */

	/* Allocate passthru buffer */
	new_content = video_buffer_region_revocable(comp->lc_buffer, &self->lw_attr.vwa_rect);
	if unlikely(!new_content)
		return; /* Failed to allocate passthru buffer */

	/* NOTE: No need to transfer video data, since the screen should
	 *       already  show whatever the  window had been displaying. */
	old_content = self->lw_content; /* Inherit reference */
	self->lw_content = new_content; /* Inherit reference */
	video_buffer_decref(old_content);

	/* Remember that this window is now using a passthru buffer */
	assert(!TAILQ_ISBOUND(self, lw_passthru));
	TAILQ_INSERT_TAIL(&comp->lc_passthru, self, lw_passthru);
	assert(TAILQ_ISBOUND(self, lw_passthru));
}

PRIVATE NONNULL((1)) ssize_t CC
local_window_hide__locked_below2_rgba_cb(void *UNUSED(cookie), struct local_window *window,
                                         struct video_rect const *UNUSED(intersect)) {
	assert(window->lw_overlay_rgba_allcount >= 1);
	if ((--window->lw_overlay_rgba_allcount) == 0) {
		REF struct video_buffer *buffer;
		buffer = window->lw_overlay_rgba;
		window->lw_overlay_rgba = NULL;
		video_buffer_decref(buffer);
		if (window->lw_overlay_rend) {
			buffer = window->lw_overlay_rend;
			window->lw_overlay_rend = NULL;
			video_buffer_decref(buffer);
		}
		try_convert_window_to_passthru(window);
	}
	return 0;
}

PRIVATE NONNULL((1)) ssize_t CC
local_window_hide__locked_below2_mask_cb(void *UNUSED(cookie), struct local_window *window,
                                         struct video_rect const *UNUSED(intersect)) {
	assert(window->lw_overlay_mask_allcount >= 1);
	if ((--window->lw_overlay_mask_allcount) == 0) {
		REF struct video_buffer *buffer;
		buffer = window->lw_overlay_mask;
		window->lw_overlay_mask = NULL;
		video_buffer_decref(buffer);
		if (window->lw_overlay_rend) {
			buffer = window->lw_overlay_rend;
			window->lw_overlay_rend = NULL;
			video_buffer_decref(buffer);
		}
		try_convert_window_to_passthru(window);
	}
	return 0;
}



/* Simply draw the intersection of "me" and "screen_rect" to screen. */
PRIVATE ATTR_INOUT(1) ATTR_IN(2) void CC
local_window_draw_rect_to_screen(struct local_window *me,
                                 struct video_rect const *screen_rect) {
	struct video_gfx content_gfx;
	struct local_compositor *comp;
	video_offset_t rel_x, rel_y;
	if (TAILQ_ISBOUND(me, lw_passthru))
		return; /* Passthru already renders directly to screen */

	comp = local_window_comp(me);
	rel_x = screen_rect->vr_xmin - me->lw_attr.vwa_rect.vr_xmin;
	rel_y = screen_rect->vr_ymin - me->lw_attr.vwa_rect.vr_ymin;
	video_buffer_getgfx(me->lw_display ? me->lw_display : me->lw_content,
	                    &content_gfx, GFX_BLENDMODE_OVERRIDE,
	                    VIDEO_GFX_F_NORMAL, 0);
	if (me->lw_overlay_rend) {
		struct video_gfx overlay_render_gfx;
		struct video_gfx overlay_rgba_gfx;
		struct video_gfx overlay_mask_gfx;
		assert(me->lw_overlay_rgba);
		assert(me->lw_overlay_mask);

		/* Update overlay render display */
		video_buffer_getgfx(me->lw_overlay_rend, &overlay_render_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(me->lw_overlay_rgba, &overlay_rgba_gfx,
		                    GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&overlay_render_gfx, rel_x, rel_y,
		                   &overlay_rgba_gfx, rel_x, rel_y,
		                   &content_gfx, rel_x, rel_y,
		                   screen_rect->vr_xdim, screen_rect->vr_ydim);

		/* Combine "me->lw_overlay_mask" with "me->lw_overlay_rend" and render result to screen */
		video_buffer_getgfx(me->lw_overlay_mask, &overlay_mask_gfx,
		                    GFX_BLENDMODE_ALPHAMASK, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&comp->lc_buffer_gfx_alpha,
		                   screen_rect->vr_xmin, screen_rect->vr_ymin,
		                   &overlay_mask_gfx, rel_x, rel_y,
		                   &overlay_render_gfx, rel_x, rel_y,
		                   screen_rect->vr_xdim, screen_rect->vr_ydim);
	} else if (me->lw_overlay_rgba) {
		struct video_gfx overlay_gfx;
		assert(!me->lw_overlay_mask);
		video_buffer_getgfx(me->lw_overlay_rgba, &overlay_gfx,
		                    GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&comp->lc_buffer_gfx_write,
		                   screen_rect->vr_xmin, screen_rect->vr_ymin,
		                   &overlay_gfx, rel_x, rel_y,
		                   &content_gfx, rel_x, rel_y,
		                   screen_rect->vr_xdim, screen_rect->vr_ydim);
	} else if (me->lw_overlay_mask) {
		struct video_gfx mask_gfx;
		video_buffer_getgfx(me->lw_overlay_mask, &mask_gfx,
		                    GFX_BLENDMODE_ALPHAMASK, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&comp->lc_buffer_gfx_alpha,
		                   screen_rect->vr_xmin,
		                   screen_rect->vr_ymin,
		                   &mask_gfx, rel_x, rel_y,
		                   &content_gfx, rel_x, rel_y,
		                   screen_rect->vr_xdim, screen_rect->vr_ydim);
	} else {
		video_gfx_bitblit(&comp->lc_buffer_gfx_write,
		                  screen_rect->vr_xmin,
		                  screen_rect->vr_ymin,
		                  &content_gfx, rel_x, rel_y,
		                  screen_rect->vr_xdim, screen_rect->vr_ydim);
		if (!(me->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA))
			try_convert_window_to_passthru(me);
	}
}

struct local_window_hide__locked_above_data {
	struct video_gfx *lwh_lad_src_gfx; /* [0..1] Source GFX */
	bool              lwh_lad_render;  /* True if window hits should be rendered to screen */
};

PRIVATE NONNULL((1)) ssize_t CC
local_window_hide__locked_above_cb(void *cookie, struct local_window *window,
                                   struct video_rect const *intersect) {
	struct local_window_hide__locked_above_data *data;
	data = (struct local_window_hide__locked_above_data *)cookie;
	if (window->lw_background) {
		struct local_window *above;
		struct video_gfx background_gfx;
		struct video_gfx display_gfx;
		struct video_gfx content_gfx;
		struct video_gfx *p_src_gfx = data->lwh_lad_src_gfx;
		video_offset_t rel_x = intersect->vr_xmin - window->lw_attr.vwa_rect.vr_xmin;
		video_offset_t rel_y = intersect->vr_ymin - window->lw_attr.vwa_rect.vr_ymin;
		video_buffer_getgfx(window->lw_background, &background_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		if (p_src_gfx) {
			/* Can just copy from background buffer of window being hidden */
			video_gfx_bitblit(&background_gfx, rel_x, rel_y, p_src_gfx,
			                  intersect->vr_xmin, intersect->vr_ymin,
			                  intersect->vr_xdim, intersect->vr_ydim);
		} else {
			/* Must manually copy from "lw_display" of video buffers behind "window" */
			struct local_compositor *comp = local_window_comp(window);
			struct local_window *below = TAILQ_PREV(window, lw_zorder_visi);
			video_gfx_clipinfo_t clip;
			video_gfx_saveclip(&background_gfx, &clip);
			video_gfx_clip(&background_gfx, rel_x, rel_y,
			               intersect->vr_xdim, intersect->vr_ydim);
			if (below) {
				video_gfx_clip(&background_gfx, -intersect->vr_xmin, -intersect->vr_ymin,
				               intersect->vr_xdim, intersect->vr_ydim);
				local_compositor_render_behind(comp, below, intersect, &background_gfx);
			} else {
				video_gfx_fillall(&background_gfx, comp->lc_background);
			}
			video_gfx_loadclip(&background_gfx, &clip);
		}

		/* Update display buffer of window */
		video_buffer_getgfx(window->lw_display, &display_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(window->lw_content, &content_gfx, GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&display_gfx, rel_x, rel_y,
		                   &content_gfx, rel_x, rel_y,
		                   &background_gfx, rel_x, rel_y,
		                   intersect->vr_xdim, intersect->vr_ydim);

		/* Recursively update background buffers of windows in-front */
		above = TAILQ_NEXT(window, lw_zorder_visi);
		if (above) {
			struct local_compositor *comp = local_window_comp(window);
			struct local_window_hide__locked_above_data inner_data;
			inner_data.lwh_lad_render  = false;
			inner_data.lwh_lad_src_gfx = video_gfx_clip(&display_gfx,
			                                            -window->lw_attr.vwa_rect.vr_xmin,
			                                            -window->lw_attr.vwa_rect.vr_ymin,
			                                            window->lw_attr.vwa_rect.vr_xmin + video_gfx_getclipw(&display_gfx),
			                                            window->lw_attr.vwa_rect.vr_ymin + video_gfx_getcliph(&display_gfx));
			local_compositor_foreach_above(comp, above, intersect,
			                               &local_window_hide__locked_above_cb,
			                               NULL, NULL, &inner_data);
		}
	}

	/* If requested, draw the intersected region to the screen */
	if (data->lwh_lad_render)
		local_window_draw_rect_to_screen(window, intersect);
	return 0;
}

PRIVATE NONNULL_T((2)) ATTR_IN_T(3) ssize_t CC
local_window_hide__locked_above_nohit_cb(void *UNUSED(cookie),
                                         struct local_compositor *comp,
                                         struct video_rect const *intersect) {
	local_compositor_updaterect__nopropagate(comp, intersect);
	return 0;
}

/* Hide a video window.
 * NOTE: The caller is  responsible for revoking  passthru display  access
 *       and (in case pixel data of "lw_content" should be saved), copying
 *       pixel  data from "lw_content" into a separate buffer (so it isn't
 *       being shared with the compositor's output).
 * NOTE: The caller must also set the "VIDEO_WINDOW_F_HIDDEN" flag
 * NOTE: This function also */
PRIVATE NONNULL((1)) void CC
local_window_hide__locked(struct local_window *__restrict me) {
	struct local_window *below, *above;
	struct local_compositor *comp = local_window_comp(me);
	assert(!(me->lw_attr.vwa_flags & VIDEO_WINDOW_F_HIDDEN));
	assert(TAILQ_ISBOUND(me, lw_zorder_visi));
	assertf(!TAILQ_ISBOUND(me, lw_passthru), "Must be done by caller **first**");
	below = TAILQ_PREV(me, lw_zorder_visi);
	above = TAILQ_NEXT(me, lw_zorder_visi);
	TAILQ_UNBIND(&comp->lc_zorder_visi, me, lw_zorder_visi);
	if (below) {
		/* Reduce use-counters of overlay buffers of windows below. */
		local_compositor_foreach_all_below(comp, below, &me->lw_attr.vwa_rect,
		                                   (me->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA)
		                                   ? &local_window_hide__locked_below2_rgba_cb
		                                   : &local_window_hide__locked_below2_mask_cb,
		                                   NULL);
		/* Update overlays in windows underneath ours (that are still in-use) */
		local_compositor_foreach_below(comp, below, &me->lw_attr.vwa_rect,
		                               &local_window_hide__locked_below_cb,
		                               NULL, NULL, me);
	}
	if (above) {
		/* Update   background   buffers  of   windows   above  ours.
		 * For this purpose, pixel data can be read from our window's
		 * background-buffer (if we have one), or has to be generated
		 * dynamically (if we don't have one) */
		struct video_gfx src_gfx;
		struct local_window_hide__locked_above_data data;
		data.lwh_lad_src_gfx = NULL;
		if (me->lw_background) {
			data.lwh_lad_src_gfx = video_buffer_getgfx(me->lw_background, &src_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
			data.lwh_lad_src_gfx = video_gfx_clip(data.lwh_lad_src_gfx,
			                                      -me->lw_attr.vwa_rect.vr_xmin,
			                                      -me->lw_attr.vwa_rect.vr_ymin,
			                                      me->lw_attr.vwa_rect.vr_xmin + video_gfx_getclipw(data.lwh_lad_src_gfx),
			                                      me->lw_attr.vwa_rect.vr_ymin + video_gfx_getcliph(data.lwh_lad_src_gfx));
		}
		local_compositor_foreach_above(comp, above, &me->lw_attr.vwa_rect,
		                               &local_window_hide__locked_above_cb,
		                               &local_window_hide__locked_above_nohit_cb,
		                               NULL, &data);
	} else {
		local_compositor_updaterect__nopropagate(comp, &me->lw_attr.vwa_rect);
	}

	/* Free buffers not needed for hidden windows */
	if (me->lw_overlay_rend) {
		video_buffer_decref(me->lw_overlay_rend);
		me->lw_overlay_rend = NULL;
	}
	if (me->lw_overlay_rgba) {
		video_buffer_decref(me->lw_overlay_rgba);
		me->lw_overlay_rgba = NULL;
		me->lw_overlay_rgba_allcount = 0;
	}
	if (me->lw_overlay_mask) {
		video_buffer_decref(me->lw_overlay_mask);
		me->lw_overlay_mask = NULL;
		me->lw_overlay_mask_allcount = 0;
	}
	if (me->lw_display) {
		video_buffer_decref(me->lw_display);
		me->lw_display = NULL;
	}
	if (me->lw_background) {
		video_buffer_decref(me->lw_background);
		me->lw_background = NULL;
	}
}

/* Operator callbacks for "struct local_window" */
INTERN NONNULL((1)) void LIBVIDEO_GFX_CC
local_window_destroy(struct video_display *__restrict self) {
	struct local_window *me = local_window_fromdisplay(self);
	struct local_compositor *comp = local_window_comp(me);
	local_compositor_wlock(comp);
	local_window_assert(me);
	if (!(me->lw_attr.vwa_flags & VIDEO_WINDOW_F_HIDDEN)) {
		if (TAILQ_ISBOUND(me, lw_passthru)) {
			video_buffer_region_revoke(me->lw_content);
			TAILQ_UNBIND(&comp->lc_passthru, me, lw_passthru);
		}
		local_window_hide__locked(me);
	}
	assert(!me->lw_overlay_rend);
	assert(!me->lw_overlay_rgba);
	assert(!me->lw_overlay_mask);
	assert(!me->lw_display);
	assert(!me->lw_background);
	assert(me->lw_content);
	video_buffer_decref(me->lw_content);
	local_compositor_wunlock(comp);
	video_compositor_decref(comp);
	free(self);
}

INTERN WUNUSED ATTR_INOUT((1)) REF struct video_buffer *LIBVIDEO_GFX_CC
local_window_getbuffer(struct video_display *__restrict self) {
	REF struct video_buffer *result;
	struct local_window *me = local_window_fromdisplay(self);
	struct local_compositor *comp = local_window_comp(me);
	local_compositor_rlock(comp);
	local_window_assert(me);
	result = me->lw_content;
	video_buffer_incref(result);
	local_compositor_runlock(comp);
	return result;
}

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_window_update_background_cb(void *cookie, struct local_window *window,
                                  struct video_rect const *intersect);

/* Propagate  updates made to {rel_x,rel_y,DIMOF(intersect)} in "background_gfx"
 * to `window's lw_display buffer (by including its lw_content buffer), and then
 * propagating these updates further on ahead to other windows above "window". */
PRIVATE ATTR_IN(1) ATTR_IN(2) void CC
local_window_update_background_propagate(struct local_window *window,
                                         struct video_gfx *background_gfx,
                                         video_offset_t rel_x, video_offset_t rel_y,
                                         struct video_rect const *intersect) {
	struct local_window *above;
	struct video_gfx display_gfx;
	struct video_gfx content_gfx;
	assert(rel_x == intersect->vr_xmin - window->lw_attr.vwa_rect.vr_xmin);
	assert(rel_y == intersect->vr_ymin - window->lw_attr.vwa_rect.vr_ymin);

	/* Update display buffer of window */
	video_gfx_setblend(background_gfx, GFX_BLENDMODE_ALPHA);
	video_buffer_getgfx(window->lw_display, &display_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	video_buffer_getgfx(window->lw_content, &content_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	video_gfx_bitblit3(&display_gfx, rel_x, rel_y,
	                   background_gfx, rel_x, rel_y,
	                   &content_gfx, rel_x, rel_y,
	                   video_rect_getxdim(intersect),
	                   video_rect_getydim(intersect));

	/* Recursively update background buffers of other windows in-front of this one */
	above = TAILQ_NEXT(window, lw_zorder_visi);
	if (above) {
		struct local_compositor *comp = local_window_comp(window);
		video_gfx_clip(&display_gfx,
		               -window->lw_attr.vwa_rect.vr_xmin,
		               -window->lw_attr.vwa_rect.vr_ymin,
		               window->lw_attr.vwa_rect.vr_xmin + video_gfx_getclipw(&display_gfx),
		               window->lw_attr.vwa_rect.vr_ymin + video_gfx_getcliph(&display_gfx));
		local_compositor_foreach_above(comp, above, intersect,
		                               &local_window_update_background_cb,
		                               NULL, NULL, &display_gfx);
	}
}

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_window_update_background_cb(void *cookie, struct local_window *window,
                                  struct video_rect const *intersect) {
	struct video_gfx *src_gfx = (struct video_gfx *)cookie;
	assert((window->lw_background != NULL) == (window->lw_display != NULL));
	if (window->lw_background) {
		struct video_gfx background_gfx;
		video_offset_t rel_x = intersect->vr_xmin - window->lw_attr.vwa_rect.vr_xmin;
		video_offset_t rel_y = intersect->vr_ymin - window->lw_attr.vwa_rect.vr_ymin;

		/* Update background buffer of window */
		video_buffer_getgfx(window->lw_background, &background_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit(&background_gfx, rel_x, rel_y, src_gfx,
		                  intersect->vr_xmin, intersect->vr_ymin,
		                  intersect->vr_xdim, intersect->vr_ydim);
		local_window_update_background_propagate(window, &background_gfx, rel_x, rel_y, intersect);
	}
	return 0;
}

struct local_window_update_overlay_data {
	struct video_gfx  lwuod_above_content; /* Content of the window above (in screen-space) */
	struct video_gfx *lwuod_above_overlay; /* [0..1] Overlay of the window above (in screen-space) */
};

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_window_update_overlay_cb(void *cookie, struct local_window *window,
                               struct video_rect const *intersect) {
	struct local_window_update_overlay_data const *data;
	data = (struct local_window_update_overlay_data const *)cookie;
	if (window->lw_overlay_rgba) {
		struct local_compositor *comp = local_window_comp(window);
		struct video_gfx dst_gfx;
		video_offset_t rel_x = intersect->vr_xmin - window->lw_attr.vwa_rect.vr_xmin;
		video_offset_t rel_y = intersect->vr_ymin - window->lw_attr.vwa_rect.vr_ymin;
		video_buffer_getgfx(window->lw_overlay_rgba, &dst_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		if (data->lwuod_above_overlay) {
			video_gfx_bitblit3(&dst_gfx, rel_x, rel_y,
			                   data->lwuod_above_overlay,
			                   intersect->vr_xmin, intersect->vr_ymin,
			                   &data->lwuod_above_content,
			                   intersect->vr_xmin, intersect->vr_ymin,
			                   intersect->vr_xdim, intersect->vr_ydim);
		} else {
			video_gfx_bitblit(&dst_gfx, rel_x, rel_y,
			                  &data->lwuod_above_content,
			                  intersect->vr_xmin, intersect->vr_ymin,
			                  intersect->vr_xdim, intersect->vr_ydim);
		}

		/* Recursively update overlays of other windows below this one, if this one uses alpha */
		if (window->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA) {
			struct local_window *below = TAILQ_PREV(window, lw_zorder_visi);
			if (below) {
				struct local_window_update_overlay_data inner_data;
				video_gfx_setblend(&dst_gfx, GFX_BLENDMODE_ALPHA);
				inner_data.lwuod_above_overlay = &dst_gfx;
				video_buffer_getgfx(window->lw_content, &inner_data.lwuod_above_content,
				                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
				video_gfx_clip(&dst_gfx,
				               -window->lw_attr.vwa_rect.vr_xmin,
				               -window->lw_attr.vwa_rect.vr_ymin,
				               window->lw_attr.vwa_rect.vr_xmin + video_gfx_getclipw(&dst_gfx),
				               window->lw_attr.vwa_rect.vr_ymin + video_gfx_getcliph(&dst_gfx));
				video_gfx_clip(&inner_data.lwuod_above_content,
				               -window->lw_attr.vwa_rect.vr_xmin,
				               -window->lw_attr.vwa_rect.vr_ymin,
				               window->lw_attr.vwa_rect.vr_xmin + video_gfx_getclipw(&inner_data.lwuod_above_content),
				               window->lw_attr.vwa_rect.vr_ymin + video_gfx_getcliph(&inner_data.lwuod_above_content));
				local_compositor_foreach_below(comp, below, intersect,
				                               &local_window_update_overlay_cb,
				                               NULL, NULL, &inner_data);
			}
		}
	}
	return 0;
}

INTERN ATTR_INOUT(1) ATTR_IN(2) void LIBVIDEO_GFX_CC
local_window_updaterect(struct video_display *__restrict self,
                        struct video_rect const *__restrict rect) {
	struct local_window *me = local_window_fromdisplay(self);
	struct local_compositor *comp = local_window_comp(me);
	struct video_gfx content_gfx;
	struct video_rect screen_rect;
	local_compositor_rlock(comp);
	local_window_assert(me);

	/* If our window uses a pass-thru buffer, then we don't have to do anything. */
	if (TAILQ_ISBOUND(me, lw_passthru))
		goto done;

	assert((me->lw_background != NULL) == (me->lw_display != NULL));
	video_buffer_getgfx(me->lw_content, &content_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	if (me->lw_background) {
		struct video_gfx display_gfx;
		struct video_gfx background_gfx;
		video_buffer_getgfx(me->lw_background, &background_gfx, GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(me->lw_display, &display_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&display_gfx, rect->vr_xmin, rect->vr_ymin,
		                   &background_gfx, rect->vr_xmin, rect->vr_ymin,
		                   &content_gfx, rect->vr_xmin, rect->vr_ymin,
		                   rect->vr_xdim, rect->vr_ydim);
		content_gfx = display_gfx;
	}

	screen_rect.vr_xmin = me->lw_attr.vwa_rect.vr_xmin + rect->vr_xmin;
	screen_rect.vr_ymin = me->lw_attr.vwa_rect.vr_ymin + rect->vr_ymin;
	screen_rect.vr_xdim = rect->vr_xdim;
	screen_rect.vr_ydim = rect->vr_ydim;
	if (me->lw_overlay_rend) {
		struct video_gfx overlay_render_gfx;
		struct video_gfx overlay_rgba_gfx;
		struct video_gfx overlay_mask_gfx;
		assert(me->lw_overlay_rgba);
		assert(me->lw_overlay_mask);

		/* Update overlay render display */
		video_buffer_getgfx(me->lw_overlay_rend, &overlay_render_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(me->lw_overlay_rgba, &overlay_rgba_gfx,
		                    GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&overlay_render_gfx, rect->vr_xmin, rect->vr_ymin,
		                   &overlay_rgba_gfx, rect->vr_xmin, rect->vr_ymin,
		                   &content_gfx, rect->vr_xmin, rect->vr_ymin,
		                   screen_rect.vr_xdim, screen_rect.vr_ydim);

		/* Combine "me->lw_overlay_mask" with "me->lw_overlay_rend" and render result to screen */
		video_buffer_getgfx(me->lw_overlay_mask, &overlay_mask_gfx,
		                    GFX_BLENDMODE_ALPHAMASK, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&comp->lc_buffer_gfx_alpha, screen_rect.vr_xmin, screen_rect.vr_ymin,
		                   &overlay_mask_gfx, rect->vr_xmin, rect->vr_ymin,
		                   &overlay_render_gfx, rect->vr_xmin, rect->vr_ymin,
		                   screen_rect.vr_xdim, screen_rect.vr_ydim);
	} else if (me->lw_overlay_rgba) {
		struct local_window *above;
		struct video_gfx overlay_gfx;
		assert(!me->lw_overlay_mask);
		video_buffer_getgfx(me->lw_overlay_rgba, &overlay_gfx,
		                    GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&comp->lc_buffer_gfx_write,
		                   screen_rect.vr_xmin, screen_rect.vr_ymin,
		                   &overlay_gfx, rect->vr_xmin, rect->vr_ymin,
		                   &content_gfx, rect->vr_xmin, rect->vr_ymin,
		                   screen_rect.vr_xdim, screen_rect.vr_ydim);

		/* Must also update the background buffers of windows above */
		above = TAILQ_NEXT(me, lw_zorder_visi);
		if (above) {
			video_gfx_clip(&content_gfx,
			               -me->lw_attr.vwa_rect.vr_xmin,
			               -me->lw_attr.vwa_rect.vr_ymin,
			               me->lw_attr.vwa_rect.vr_xmin + video_gfx_getclipw(&content_gfx),
			               me->lw_attr.vwa_rect.vr_ymin + video_gfx_getcliph(&content_gfx));
			local_compositor_foreach_above(comp, above, &screen_rect,
			                               &local_window_update_background_cb,
			                               NULL, NULL, &content_gfx);
		}
	} else if (me->lw_overlay_mask) {
		struct video_gfx mask_gfx;
		video_buffer_getgfx(me->lw_overlay_mask, &mask_gfx,
		                    GFX_BLENDMODE_ALPHAMASK, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&comp->lc_buffer_gfx_alpha,
		                   screen_rect.vr_xmin,
		                   screen_rect.vr_ymin,
		                   &mask_gfx, rect->vr_xmin, rect->vr_ymin,
		                   &content_gfx, rect->vr_xmin, rect->vr_ymin,
		                   screen_rect.vr_xdim, screen_rect.vr_ydim);
	} else {
		video_gfx_bitblit(&comp->lc_buffer_gfx_write,
		                  screen_rect.vr_xmin,
		                  screen_rect.vr_ymin,
		                  &content_gfx, rect->vr_xmin, rect->vr_ymin,
		                  screen_rect.vr_xdim, screen_rect.vr_ydim);
		if (!(me->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA))
			try_convert_window_to_passthru(me);
	}

	/* Must also update the overlay buffers of windows below when our window has an alpha-channel */
	if (me->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA) {
		struct local_window *below = TAILQ_PREV(me, lw_zorder_visi);
		if (below) {
			struct local_window_update_overlay_data data;
			struct video_gfx overlay_gfx;
			data.lwuod_above_overlay = NULL;
			if (me->lw_overlay_rgba) {
				video_buffer_getgfx(me->lw_overlay_rgba, &overlay_gfx,
				                    GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
				video_gfx_clip(&overlay_gfx,
				               -me->lw_attr.vwa_rect.vr_xmin,
				               -me->lw_attr.vwa_rect.vr_ymin,
				               me->lw_attr.vwa_rect.vr_xmin + video_gfx_getclipw(&overlay_gfx),
				               me->lw_attr.vwa_rect.vr_ymin + video_gfx_getcliph(&overlay_gfx));
				data.lwuod_above_overlay = &overlay_gfx;
			}
			video_buffer_getgfx(me->lw_content, &data.lwuod_above_content,
			                    GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
			video_gfx_clip(&data.lwuod_above_content,
			               -me->lw_attr.vwa_rect.vr_xmin,
			               -me->lw_attr.vwa_rect.vr_ymin,
			               me->lw_attr.vwa_rect.vr_xmin + video_gfx_getclipw(&data.lwuod_above_content),
			               me->lw_attr.vwa_rect.vr_ymin + video_gfx_getcliph(&data.lwuod_above_content));
			local_compositor_foreach_below(comp, below, &screen_rect,
			                               &local_window_update_overlay_cb,
			                               NULL, NULL, &data);
		}
	}

done:
	local_compositor_runlock(comp);
}

INTERN ATTR_INOUT(1) ATTR_INS(2, 3) void LIBVIDEO_GFX_CC
local_window_updaterects(struct video_display *__restrict self,
                         struct video_rect const *__restrict rects,
                         size_t n_rects) {
	size_t i;
	for (i = 0; i < n_rects; ++i)
		local_window_updaterect(self, &rects[i]);
}


INTERN WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int CC
local_window_getattr(struct video_window *__restrict self,
                     struct video_window_attr *__restrict attr) {
	struct local_window *me = local_window_fromdisplay(self);
	struct local_compositor *comp = local_window_comp(me);
	local_compositor_rlock(comp);
	local_window_assert(me);
	memcpy(attr, &me->lw_attr, sizeof(struct video_window_attr));
	local_compositor_runlock(comp);
	return 0;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_IN(2) int CC
local_window_setposition(struct video_window *__restrict self,
                         struct video_window_position const *__restrict position) {
	/* TODO */
	(void)self;
	(void)position;
	errno = ENOSYS;
	return -1;
}


/************************************************************************/
/* OPERATOR TABLE                                                       */
/************************************************************************/
INTERN struct video_window_ops local_window_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_window_ops *CC _local_window_ops(void) {
	if (!local_window_ops.vwo_display.vdo_destroy) {
		local_window_ops.vwo_getattr                 = &local_window_getattr;
		local_window_ops.vwo_setposition             = &local_window_setposition;
		local_window_ops.vwo_display.vdo_updaterects = &local_window_updaterects;
		local_window_ops.vwo_display.vdo_updaterect  = &local_window_updaterect;
		local_window_ops.vwo_display.vdo_getbuffer   = &local_window_getbuffer;
		COMPILER_WRITE_BARRIER();
		local_window_ops.vwo_display.vdo_destroy = &local_window_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &local_window_ops;
}






/************************************************************************/
/* WINDOW COMPOSITOR                                                    */
/************************************************************************/

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

typedef ATTR_PURE_T WUNUSED_T ATTR_IN_T(1) struct local_window *
(CC *local_compositor_foreach_next_t)(struct local_window *__restrict window);

/* Find the window at {x,y}, with enumeration starts at
 * "start" (inclusive) and moving forward using "next". */
PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) struct local_window *CC
local_compositor_windowat(struct local_window *__restrict start,
                          local_compositor_foreach_next_t next,
                          video_offset_t x, video_offset_t y) {
	do {
		if (video_rect_contains(&start->lw_attr.vwa_rect, x, y))
			return start;
	} while ((start = (*next)(start)) != NULL);
	return NULL;
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) struct local_window *CC
local_window_visi_above(struct local_window *__restrict window) {
	return TAILQ_NEXT(window, lw_zorder_visi);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) struct local_window *CC
local_window_visi_below(struct local_window *__restrict window) {
	return TAILQ_PREV(window, lw_zorder_visi);
}

PRIVATE ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4, 7)) ssize_t CC
local_compositor_foreach_impl(struct local_compositor *__restrict self,
                              struct local_window *__restrict start,
                              struct video_rect const *rect,
                              local_compositor_foreach_cb_t cb,                /* [1..1] */
                              local_compositor_foreach_nohit_cb_t nohit,       /* [0..1] */
                              local_compositor_foreach_rollback_cb_t rollback, /* [0..1] */
                              void *cookie, local_compositor_foreach_next_t next) {
	ssize_t temp, result = 0;
	struct local_window *iter;
	struct video_rect *stack;
	size_t window_rect_count = 1;
	size_t max_stack_sz;
	assert(rect->vr_xdim);
	assert(rect->vr_ydim);

	/* Skip windows that don't intersect with the original rect */
	while (!video_rect_intersects(rect, &start->lw_attr.vwa_rect)) {
		start = (*next)(start);
		if unlikely(!start) {
			if (nohit)
				result = (*nohit)(cookie, self, rect);
			return result;
		}
	}

	/* Count the # of windows that participate with intersections */
	for (iter = start; (iter = (*next)(iter)) != NULL;)
		++window_rect_count;
	max_stack_sz = window_rect_count * 3 + 1;
	stack = (struct video_rect *)malloc(max_stack_sz, sizeof(struct video_rect));
	if likely(stack) {
		/* "Fast" O(N^2) case: use a buffer of deleted rects
		 * XXX: This can be made faster if windows were stored in a BSP tree */
		size_t stacksz = 1;
		stack[0] = *rect;
		iter = start;
		do {
			assert(stacksz);
			/* Quick check: skip windows that don't overlap with the queried rect */
			if (video_rect_intersects(rect, &iter->lw_attr.vwa_rect)) {
				size_t i = 0;
				do {
					struct video_rect intersection;
					if (video_rect_intersect(&stack[i], &iter->lw_attr.vwa_rect, &intersection)) {
						struct video_rect more[4];
						size_t n_more;
						temp = (*cb)(cookie, iter, &intersection);
						if unlikely(temp < 0) {
							result = temp;
							if (rollback) {
								stacksz = 1;
								stack[0] = *rect;
								for (;;) {
									assert(stacksz);
									if (video_rect_intersects(rect, &start->lw_attr.vwa_rect)) {
										size_t j = 0;
										do {
											struct video_rect intersection;
											if (start == iter && j >= i)
												goto done_stack; /* Stop **before** the failing call */
											if (video_rect_intersect(&stack[j], &start->lw_attr.vwa_rect, &intersection)) {
												struct video_rect more[4];
												size_t n_more;
												(*rollback)(cookie, iter, &intersection);
												n_more = video_rect_subtract(&stack[j], &intersection, more);
												if (!n_more) {
													if (!--stacksz)
														goto done_stack;
													memmovedownc(&stack[j], &stack[j + 1],
													             stacksz - j,
													             sizeof(struct video_rect));
												} else {
													stack[j] = more[0];
													--n_more;
													assert((stacksz + n_more) <= max_stack_sz);
													memcpyc(&stack[stacksz], more, n_more,
													        sizeof(struct video_rect));
													stacksz += n_more;
													++j;
												}
											} else {
												++j;
											}
										} while (j < stacksz);
									}
									if (start == iter)
										break;
									start = (*next)(start);
								}
							}
							goto done_stack;
						}
						result += temp;

						/* Update stack of intersecting rects */
						n_more = video_rect_subtract(&stack[i], &intersection, more);
						if (!n_more) {
							if (!--stacksz)
								goto done_stack;
							memmovedownc(&stack[i], &stack[i + 1],
							             stacksz - i,
							             sizeof(struct video_rect));
						} else {
							/* First sub-rect is stored in "stack[i]" */
							stack[i] = more[0];
							--n_more;
							/* Remaining sub-rects are appended to the stack */
							assert((stacksz + n_more) <= max_stack_sz);
							memcpyc(&stack[stacksz], more, n_more,
							        sizeof(struct video_rect));
							stacksz += n_more;
							++i;
						}
					} else {
						++i;
					}
				} while (i < stacksz);
			}
		} while ((iter = (*next)(iter)) != NULL);
		assert(stacksz);
		if (nohit) {
			do {
				--stacksz;
				temp = (*nohit)(cookie, self, &stack[stacksz]);
				if unlikely(temp < 0) {
					result = temp;
					goto done_stack;
				}
				result += temp;
			} while (stacksz);
		}
done_stack:
		free(stack);
	} else {
		/* "Slow" O(W*H*N) case: enumerate each pixel of "rect" and see if it intersects
		 *                       with any  window, then  coalesce horizontally  adjacent
		 *                       pixels that intersect with the same window. */
		video_coord_t y = 0;
		do {
			video_offset_t used_y = rect->vr_ymin + y;
			video_coord_t x = 0;
			for (;;) {
				struct video_rect intersect;
				video_coord_t hit_x = x;
				struct local_window *hit = local_compositor_windowat(start, next, rect->vr_xmin + x, used_y);
				while (++x < rect->vr_xdim &&
				       hit == local_compositor_windowat(start, next, rect->vr_xmin + x, used_y))
					;
				intersect.vr_xmin = rect->vr_xmin + hit_x;
				intersect.vr_ymin = used_y;
				intersect.vr_xdim = x - hit_x;
				intersect.vr_ydim = 1;
				if (hit) {
					temp = (*cb)(cookie, hit, &intersect);
				} else if (nohit) {
					temp = (*nohit)(cookie, self, &intersect);
				} else {
					temp = 0;
				}
				if unlikely(temp < 0) {
					result = temp;
					if (rollback) {
						video_coord_t halt_x = hit_x;
						video_coord_t halt_y = used_y;
						for (y = 0;;) {
							used_y = rect->vr_ymin + y;
							x = 0;
							for (;;) {
								if (halt_x == x && halt_y == y)
									goto done_loop;
								hit_x = x;
								hit = local_compositor_windowat(start, next, rect->vr_xmin + x, used_y);
								while (++x < rect->vr_xdim &&
								       hit == local_compositor_windowat(start, next, rect->vr_xmin + x, used_y))
									;
								intersect.vr_xmin = rect->vr_xmin + hit_x;
								intersect.vr_ymin = used_y;
								intersect.vr_xdim = x - hit_x;
								intersect.vr_ydim = 1;
								if (hit)
									(*rollback)(cookie, hit, &intersect);
								if (x >= rect->vr_xdim)
									break;
							}
							++y;
							assert(y < rect->vr_ydim);
						}
					}
					goto done_loop;
				}
				result += temp;
				if (x >= rect->vr_xdim)
					break;
			}
		} while (++y < rect->vr_ydim);
done_loop:;
	}
	return result;
}

INTERN ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_above(struct local_compositor *__restrict self,
                               struct local_window *__restrict start,
                               struct video_rect const *rect,
                               local_compositor_foreach_cb_t cb,                /* [1..1] */
                               local_compositor_foreach_nohit_cb_t nohit,       /* [0..1] */
                               local_compositor_foreach_rollback_cb_t rollback, /* [0..1] */
                               void *cookie) {
	return local_compositor_foreach_impl(self, start, rect, cb, nohit, rollback,
	                                     cookie, &local_window_visi_above);
}

/* Same as "local_compositor_foreach_above", but cast rays towards negative Z */
INTERN ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_below(struct local_compositor *__restrict self,
                               struct local_window *__restrict start,
                               struct video_rect const *rect,
                               local_compositor_foreach_cb_t cb,                /* [1..1] */
                               local_compositor_foreach_nohit_cb_t nohit,       /* [0..1] */
                               local_compositor_foreach_rollback_cb_t rollback, /* [0..1] */
                               void *cookie) {
	return local_compositor_foreach_impl(self, start, rect, cb, nohit, rollback,
	                                     cookie, &local_window_visi_below);
}

/* Like above, but the imaginary "rays" being cast can travel through windows.
 * iow: these functions enumerate **all** windows and their intersections with
 *      the given `rect', even if the same sub-region intersects with multiple
 *      windows. */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_all_above(struct local_compositor *__restrict self,
                                   struct local_window *__restrict start,
                                   struct video_rect const *rect,
                                   local_compositor_foreach_cb_t cb, void *cookie) {
	ssize_t temp, result = 0;
	struct local_window *iter = start;
	assert(self == local_window_comp(start));
	(void)self;
	do {
		struct video_rect intersect;
		if (video_rect_intersect(&iter->lw_attr.vwa_rect, rect, &intersect)) {
			temp = (*cb)(cookie, iter, &intersect);
			if unlikely(temp < 0)
				return temp;
			result += temp;
		}
	} while ((iter = TAILQ_NEXT(iter, lw_zorder_visi)) != NULL);
	return result;
}

INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_all_below(struct local_compositor *__restrict self,
                                   struct local_window *__restrict start,
                                   struct video_rect const *rect,
                                   local_compositor_foreach_cb_t cb, void *cookie) {
	ssize_t temp, result = 0;
	struct local_window *iter = start;
	assert(self == local_window_comp(start));
	(void)self;
	do {
		struct video_rect intersect;
		if (video_rect_intersect(&iter->lw_attr.vwa_rect, rect, &intersect)) {
			temp = (*cb)(cookie, iter, &intersect);
			if unlikely(temp < 0)
				return temp;
			result += temp;
		}
	} while ((iter = TAILQ_PREV(iter, lw_zorder_visi)) != NULL);
	return result;
}


/* Force a re-draw of all windows (and the background) that intersect with `screen_rect' */
INTDEF ATTR_INOUT(1) ATTR_IN(2) void CC
local_compositor_updaterect__nopropagate(struct local_compositor *__restrict self,
                                         struct video_rect const *screen_rect) {
	struct local_window *last = TAILQ_LAST(&self->lc_zorder_visi);
	if likely(last) {
		local_compositor_render_behind(self, last, screen_rect, &self->lc_buffer_gfx_write);
	} else {
		video_gfx_fill(&self->lc_buffer_gfx_write, screen_rect->vr_xmin, screen_rect->vr_ymin,
		               screen_rect->vr_xdim, screen_rect->vr_ydim,
		               self->lc_background);
	}
}







PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_foreach_cb(void *cookie, struct local_window *window,
                                   struct video_rect const *intersect) {
	struct video_gfx src_gfx, *out;
	struct video_buffer *src;
	video_offset_t rel_x, rel_y;
	local_window_assert(window);

	/* Ignore render requests for passthru windows (those can just do their own thing...) */
	if (TAILQ_ISBOUND(window, lw_passthru))
		return 0;
	out = (struct video_gfx *)cookie;
	src = window->lw_display ? window->lw_display : window->lw_content;
	rel_x = intersect->vr_xmin - window->lw_attr.vwa_rect.vr_xmin;
	rel_y = intersect->vr_ymin - window->lw_attr.vwa_rect.vr_ymin;
	video_buffer_getgfx(src, &src_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	video_gfx_bitblit(out, intersect->vr_xmin, intersect->vr_ymin,
	                  &src_gfx, rel_x, rel_y,
	                  intersect->vr_xdim, intersect->vr_ydim);
	return 0;
}

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_foreach_nohit_cb(void *cookie, struct local_compositor *comp,
                                         struct video_rect const *intersect) {
	struct video_gfx *out = (struct video_gfx *)cookie;
	video_gfx_fill(out, intersect->vr_xmin, intersect->vr_ymin,
	               intersect->vr_xdim, intersect->vr_ydim,
	               comp->lc_background);
	return 0;
}

/* Draw all pixels from windows behind (and including) `start', and intersecting
 * with  `screen_rect'.  Pixels written  to  `out' use  absolute  screen coords. */
INTERN ATTR_INOUT(1) ATTR_IN(2) ATTR_IN(3) ATTR_INOUT(4) void CC
local_compositor_render_behind(struct local_compositor *__restrict self,
                               struct local_window *__restrict start,
                               struct video_rect const *screen_rect,
                               struct video_gfx *out) {
	local_compositor_foreach_below(self, start, screen_rect,
	                               &local_compositor_render_foreach_cb,
	                               &local_compositor_render_foreach_nohit_cb,
	                               NULL, out);
}


struct local_compositor_render_above_masked_foreach_data {
	struct video_gfx const    *lcramfd_out;       /* [1..1] Output GFX */
	struct local_window const *lcramfd_srcwindow; /* [1..1] Window from which to take an overlay */
	struct video_gfx           lcramfd_srcwindow_content_gfx; /* GFX for `lcramfd_srcwindow->lw_content' */
	struct video_gfx           lcramfd_srcwindow_overlay_gfx; /* GFX for `lcramfd_srcwindow->lw_overlay_rgba' (if defined) */
};

PRIVATE ATTR_IN(1) ATTR_IN(2) void CC
local_compositor_render_above_unmasked(struct local_compositor_render_above_masked_foreach_data const *data,
                                       struct video_rect const *intersect) {
	struct local_window const *window = data->lcramfd_srcwindow;
	video_offset_t rel_x = video_rect_getxmin(intersect) - video_rect_getxmin(&window->lw_attr.vwa_rect);
	video_offset_t rel_y = video_rect_getymin(intersect) - video_rect_getymin(&window->lw_attr.vwa_rect);
	if (window->lw_overlay_rgba) {
		/* Need to do 3-ways blending to include the overlay! */
		video_gfx_bitblit3(data->lcramfd_out,
		                   video_rect_getxmin(intersect), video_rect_getymin(intersect),
		                   &data->lcramfd_srcwindow_content_gfx, rel_x, rel_y,
		                   &data->lcramfd_srcwindow_overlay_gfx, rel_x, rel_y,
		                   video_rect_getxdim(intersect), video_rect_getydim(intersect));
	} else {
		/* Simple 2-ways blending between window content and caller's GFX */
		video_gfx_bitblit(data->lcramfd_out,
		                  video_rect_getxmin(intersect), video_rect_getymin(intersect),
		                  &data->lcramfd_srcwindow_content_gfx, rel_x, rel_y,
		                  video_rect_getxdim(intersect), video_rect_getydim(intersect));
	}
}

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_above_masked_foreach_nohit_cb(void *cookie,
                                                      struct local_compositor *UNUSED(comp),
                                                      struct video_rect const *intersect);

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_above_masked_foreach_cb(void *cookie, struct local_window *window,
                                                struct video_rect const *intersect) {
	struct local_compositor_render_above_masked_foreach_data *data;
	data = (struct local_compositor_render_above_masked_foreach_data *)cookie;
	if (window->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA) {
		/* Not the reason why our original window has a MASK-overlay
		 * -> Recursively search of these is a window above this one... */
		struct local_window *above = TAILQ_NEXT(window, lw_zorder_visi);
		if (above) {
			struct local_compositor *comp = local_window_comp(window);
			return local_compositor_foreach_above(comp, above, intersect,
			                                      &local_compositor_render_above_masked_foreach_cb,
			                                      &local_compositor_render_above_masked_foreach_nohit_cb,
			                                      NULL, data);
		}
	}

	/* Found a rect that can't be responsible for our mask-overlay! */
	local_compositor_render_above_unmasked(data, intersect);
	return 0;
}

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_above_masked_foreach_nohit_cb(void *cookie,
                                                      struct local_compositor *UNUSED(comp),
                                                      struct video_rect const *intersect) {
	struct local_compositor_render_above_masked_foreach_data *data;
	data = (struct local_compositor_render_above_masked_foreach_data *)cookie;
	local_compositor_render_above_unmasked(data, intersect);
	return 0;
}

struct local_compositor_render_above_foreach_data {
	struct video_gfx *lcrafd_out;         /* [1..1] Output GFX */
	video_color_t    *lcrafd_nohit_color; /* [0..1] Color to fill unhit areas with */
};

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_above_foreach_cb(void *cookie, struct local_window *window,
                                         struct video_rect const *intersect) {
	struct local_compositor_render_above_foreach_data *data;
	struct local_compositor_render_above_masked_foreach_data inner_data;
	data = (struct local_compositor_render_above_foreach_data *)cookie;
	inner_data.lcramfd_out       = data->lcrafd_out;
	inner_data.lcramfd_srcwindow = window;
	if (window->lw_overlay_rgba) {
		video_buffer_getgfx(window->lw_content, &inner_data.lcramfd_srcwindow_content_gfx,
		                    GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(window->lw_overlay_rgba, &inner_data.lcramfd_srcwindow_overlay_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	} else {
		video_buffer_getgfx(window->lw_content, &inner_data.lcramfd_srcwindow_content_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	}

	if (window->lw_overlay_mask) {
		/* Some pixels may need to be taken from other windows **above** this one */
		struct local_compositor *comp = local_window_comp(window);
		struct local_window *above = TAILQ_NEXT(window, lw_zorder_visi);
		assertf(above, "How can we have an overlay if there are no windows above?");
		local_compositor_foreach_above(comp, above, intersect,
		                               &local_compositor_render_above_masked_foreach_cb,
		                               &local_compositor_render_above_masked_foreach_nohit_cb,
		                               NULL, &inner_data);
	} else {
		local_compositor_render_above_unmasked(&inner_data, intersect);
	}
	return 0;
}

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_above_foreach_nohit_cb(void *cookie,
                                               struct local_compositor *UNUSED(comp),
                                               struct video_rect const *intersect) {
	struct local_compositor_render_above_foreach_data *data;
	data = (struct local_compositor_render_above_foreach_data *)cookie;
	assert(data->lcrafd_nohit_color);
	video_gfx_fill(data->lcrafd_out,
	               video_rect_getxmin(intersect), video_rect_getymin(intersect),
	               video_rect_getxdim(intersect), video_rect_getydim(intersect),
	               *data->lcrafd_nohit_color);
	return 0;
}

INTERN ATTR_INOUT(1) ATTR_IN(2) ATTR_IN(3) ATTR_INOUT(4) void CC
local_compositor_render_above(struct local_compositor *__restrict self,
                              struct local_window *__restrict start,
                              struct video_rect const *screen_rect,
                              struct video_gfx *out,
                              video_color_t *opt_nohit_color) {
	struct local_compositor_render_above_foreach_data data;
	data.lcrafd_out         = out;
	data.lcrafd_nohit_color = opt_nohit_color;
	local_compositor_foreach_above(self, start, screen_rect, &local_compositor_render_above_foreach_cb,
	                               opt_nohit_color ? &local_compositor_render_above_foreach_nohit_cb
	                                               : NULL,
	                               NULL, &data);
}




/************************************************************************/
/* PUBLIC COMPOSITOR API                                                */
/************************************************************************/

INTERN ATTR_INOUT_T(1) void CC
local_compositor_destroy(struct video_compositor *__restrict self) {
	struct local_compositor *me = video_compositor_aslocal(self);
	assert(me->vcp_ops == &local_compositor_ops);
	assert(me->lc_buffer);
	assert(TAILQ_EMPTY(&me->lc_passthru));
	assert(TAILQ_EMPTY(&me->lc_zorder));
	assert(TAILQ_EMPTY(&me->lc_zorder_visi));
	video_buffer_decref(me->lc_buffer);
	free(self);
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_IN(2) REF struct video_window *CC
local_compositor_newwindow(struct video_compositor *__restrict self,
                           struct video_window_position const *__restrict position) {
	struct local_compositor *me = video_compositor_aslocal(self);
	/* TODO */
	(void)me;
	(void)position;
	errno = ENOSYS;
	return NULL;
}

INTERN WUNUSED ATTR_INOUT(1) REF struct video_display *CC
local_compositor_getdisplay(struct video_compositor *__restrict self) {
	REF struct video_display *result;
	struct local_compositor *me = video_compositor_aslocal(self);
	local_compositor_rlock(me);
	result = me->lc_display;
	video_display_incref(result);
	local_compositor_runlock(me);
	return result;
}

/* @return: * :   The previously used buffer
 * @return: NULL: Error (s.a. `errno'; probably `ENOMEM') */
PRIVATE WUNUSED ATTR_INOUT(1) REF struct video_buffer *CC
local_compositor_setbuffer_locked(struct video_compositor *__restrict self,
                                  struct video_buffer *__restrict new_buffer) {
	REF struct video_buffer *old_buffer;
	struct local_compositor *me = video_compositor_aslocal(self);

	/* Check for simple case: buffer doesn't actually change */
	if unlikely(new_buffer == me->lc_buffer) {
		video_buffer_incref(new_buffer);
		return new_buffer;
	}

	/* XXX: If the video codec or palette changes, create new video buffers for all windows? */

	/* Must allocate new passthru buffers for all windows that are passthru right now. */
	if (!TAILQ_EMPTY(&me->lc_passthru)) {
		struct local_window *pt_window;
		TAILQ_FOREACH (pt_window, &me->lc_passthru, lw_passthru) {
			REF struct video_buffer *new_passthru;
			assert(TAILQ_ISBOUND(pt_window, lw_passthru));
			local_window_assert(pt_window);
			new_passthru = video_buffer_region_revocable(new_buffer, &pt_window->lw_attr.vwa_rect);
			if unlikely(!new_passthru) {
				struct local_window *rollback;
				/* Rollback already-allocated (new) passthru buffers */
				TAILQ_FOREACH (rollback, &me->lc_passthru, lw_passthru) {
					if (rollback == pt_window)
						break;
					assert(rollback->lw_display);
					assert(rollback->lw_content);
					assert(rollback->lw_content != rollback->lw_display);
					video_buffer_decref(rollback->lw_content);
					rollback->lw_content = rollback->lw_display;
					rollback->lw_display = NULL;
				}
				goto err;
			}

			assert(!pt_window->lw_display); /* Used as temporary storage for rollback on error */
			pt_window->lw_display = pt_window->lw_content; /* Backup old passthru buffer */
			pt_window->lw_content = new_passthru;          /* New passthru buffer */
		}

		/* ===== POINT OF NO RETURN =====
		 * All passthru windows got their new passthru buffers, so now it's time to
		 * copy display memory into the new buffers, whilst deleting the old  ones. */
		TAILQ_FOREACH (pt_window, &me->lc_passthru, lw_passthru) {
			struct video_buffer *obuffer, *nbuffer;
			struct video_gfx ogfx, ngfx;
			assert(TAILQ_ISBOUND(pt_window, lw_passthru));
			assert(pt_window->lw_content);
			assert(pt_window->lw_display); /* Backup of old passthru buffer */
			assert(pt_window->lw_display != pt_window->lw_content);
			obuffer = pt_window->lw_display;
			nbuffer = pt_window->lw_content;
			pt_window->lw_display = NULL;

			/* Just do a full OVERRIDE blit of all display data represented by the old buffer */
			video_buffer_getgfx(obuffer, &ogfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
			video_buffer_getgfx(nbuffer, &ngfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
			video_gfx_bitblit(&ngfx, 0, 0, &ogfx, 0, 0,
			                  video_gfx_getclipw(&ngfx),
			                  video_gfx_getcliph(&ngfx));
			video_buffer_decref(obuffer);
		}
	}

	/* Assign the new buffer */
	video_buffer_incref(new_buffer);
	old_buffer = me->lc_buffer;
	me->lc_buffer = new_buffer;

	/* Generate new (pre-cached) GFX contexts */
	DBG_memset(&me->lc_buffer_gfx_write, 0xcc, sizeof(me->lc_buffer_gfx_write));
	DBG_memset(&me->lc_buffer_gfx_alpha, 0xcc, sizeof(me->lc_buffer_gfx_alpha));
	video_buffer_getgfx(new_buffer, &me->lc_buffer_gfx_write, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	video_buffer_getgfx(new_buffer, &me->lc_buffer_gfx_alpha, GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);

	/* Do a redraw of the  entire screen (this will  skip
	 * passthru windows, which we already migrated above) */
	{
		struct video_rect whole_screen;
		video_rect_setxmin(&whole_screen, 0);
		video_rect_setymin(&whole_screen, 0);
		video_rect_setxdim(&whole_screen, new_buffer->vb_xdim);
		video_rect_setydim(&whole_screen, new_buffer->vb_ydim);
		local_compositor_updaterect__nopropagate(me, &whole_screen);
	}
	return old_buffer;
err:
	return NULL;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_INOUT(2) int CC
local_compositor_setdisplay(struct video_compositor *__restrict self,
                            struct video_display *__restrict new_display) {
	REF struct video_display *old_display;
	REF struct video_buffer *old_buffer;
	REF struct video_buffer *new_buffer;
	struct local_compositor *me = video_compositor_aslocal(self);
	new_buffer = video_display_getbuffer(new_display);
	if unlikely(!new_buffer)
		return -1;
	video_display_incref(new_display);
	local_compositor_wlock(me);

	/* Assign new display */
	old_display = me->lc_display; /* Inherit reference */
	me->lc_display = new_display; /* Inherit reference */

	/* Assign new display buffer */
	old_buffer = local_compositor_setbuffer_locked(self, new_buffer);

	/* Rollback on error... */
	if unlikely(!old_buffer) {
		me->lc_display = old_display; /* Inherit reference (x2) */
		local_compositor_wunlock(me);
		video_display_decref(new_display);
		video_buffer_decref(new_buffer);
		return -1;
	}

	/* Release locks and drop old references */
	local_compositor_wunlock(me);
	video_display_decref(old_display);
	video_buffer_decref(old_buffer);
	return 0;
}

INTERN WUNUSED ATTR_INOUT(1) int CC
local_compositor_updatebuffer(struct video_compositor *__restrict self) {
	REF struct video_display *display;
	REF struct video_buffer *old_buffer;
	REF struct video_buffer *new_buffer;
	struct local_compositor *me = video_compositor_aslocal(self);

	/* Get reference to current display */
	local_compositor_rlock(me);
	display = me->lc_display;
	video_display_incref(display);
	old_buffer = me->lc_buffer;
	local_compositor_runlock(me);

	/* Ask display for a new buffer */
	new_buffer = video_display_getbuffer(display);
	video_display_decref(display);
	if unlikely(!new_buffer)
		return -1;
	if (new_buffer == old_buffer) {
		video_buffer_decref(new_buffer);
		return 0; /* Nothing changed */
	}

	/* Assign new buffer iff nothing changed */
	local_compositor_wlock(me);
	if likely(me->lc_display == display &&
	          me->lc_buffer == old_buffer) {
		REF struct video_buffer *status;
		status = local_compositor_setbuffer_locked(self, new_buffer);
		if unlikely(!status) {
			local_compositor_wunlock(me);
			video_buffer_decref(new_buffer);
			return -1;
		}
		assert(status == old_buffer);
	}
	local_compositor_wunlock(me);

	/* Release reference to old buffer */
	video_buffer_decref(old_buffer);
	return 0;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int CC
local_compositor_getfeatures(struct video_compositor *__restrict self,
                             video_compositor_feature_t *__restrict p_features) {
	struct local_compositor *me = video_compositor_aslocal(self);
	local_compositor_rlock(me);
	*p_features = me->lc_features;
	local_compositor_runlock(me);
	return 0;
}

INTERN WUNUSED ATTR_INOUT(1) int CC
local_compositor_setfeatures(struct video_compositor *__restrict self,
                             video_compositor_feature_t features) {
	bool enable_passthru = false;
	bool disable_passthru = false;
	struct local_compositor *me = video_compositor_aslocal(self);
	if (features & ~VIDEO_COMPOSITOR_FEAT_ALL) {
		errno = EINVAL;
		return -1;
	}
	local_compositor_wlock(me);

	/* See what changed... */
	if ((me->lc_features & VIDEO_COMPOSITOR_FEAT_PASSTHRU) !=
	    (features & VIDEO_COMPOSITOR_FEAT_PASSTHRU)) {
		/* Passthru enabled changed */
		if (features & VIDEO_COMPOSITOR_FEAT_PASSTHRU) {
			enable_passthru = true; /* Enable passthru */
			assert(TAILQ_EMPTY(&me->lc_passthru));
		} else {
			/* Disable passthru */
			disable_passthru = !TAILQ_EMPTY(&me->lc_passthru);
		}
	}

	/* Perform actions... */
	if (disable_passthru) {
		struct local_window *pt_window;
		TAILQ_FOREACH (pt_window, &me->lc_passthru, lw_passthru) {
			REF struct video_buffer *newbuf;
			assert(TAILQ_ISBOUND(pt_window, lw_passthru));
			local_window_assert(pt_window);
			assert(!pt_window->lw_display); /* Temporarily store new video buffers here */
			newbuf = video_buffer_create(me->lc_vidtyp,
			                             video_rect_getxdim(&pt_window->lw_attr.vwa_rect),
			                             video_rect_getydim(&pt_window->lw_attr.vwa_rect),
			                             me->lc_buffer->vb_format.vf_codec,
			                             me->lc_buffer->vb_format.vf_pal);
			if unlikely(!newbuf) {
				struct local_window *rollback;
				TAILQ_FOREACH (rollback, &me->lc_passthru, lw_passthru) {
					if (rollback == pt_window)
						break;
					assert(rollback->lw_display);
					assert(rollback->lw_content);
					assert(rollback->lw_content != rollback->lw_display);
					video_buffer_decref(rollback->lw_content);
					rollback->lw_content = rollback->lw_display;
					rollback->lw_display = NULL;
				}
				goto err_unlock;
			}
			pt_window->lw_display = pt_window->lw_content;
			pt_window->lw_content = newbuf;
		}
	}

	/* ===== POINT OF NO RETURN ===== */

	if (disable_passthru) {
		struct local_window *pt_window;
		TAILQ_FOREACH_SAFE (pt_window, &me->lc_passthru, lw_passthru) {
			struct video_buffer *obuffer, *nbuffer;
			struct video_gfx ogfx, ngfx;
			assert(pt_window->lw_display);
			assert(pt_window->lw_content);
			assert(pt_window->lw_content != pt_window->lw_display);
			/* Copy display memory from old (passthru) buffer to new (distinct) one */
			obuffer = pt_window->lw_display;
			pt_window->lw_display = NULL;
			nbuffer = pt_window->lw_content;
			video_buffer_getgfx(obuffer, &ogfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
			video_buffer_getgfx(nbuffer, &ngfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
			video_gfx_bitblit(&ngfx, 0, 0, &ogfx, 0, 0,
			                  video_gfx_getclipw(&ngfx),
			                  video_gfx_getcliph(&ngfx));
			video_buffer_decref(obuffer);
			TAILQ_UNBIND(&me->lc_passthru, pt_window, lw_passthru);
		}
	}

	/* Enable passthru for windows where doing so is possible. */
	if (enable_passthru) {
		struct local_window *window;
		TAILQ_FOREACH (window, &me->lc_zorder_visi, lw_zorder_visi) {
			try_convert_window_to_passthru(window);
		}
	}

	me->lc_features = features;
	local_compositor_wunlock(me);
	return 0;
err_unlock:
	local_compositor_wunlock(me);
	return -1;
}

INTERN WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int CC
local_compositor_getbackground(struct video_compositor *__restrict self,
                               video_color_t *__restrict p_background) {
	struct local_compositor *me = video_compositor_aslocal(self);
	local_compositor_rlock(me);
	*p_background = me->lc_background;
	local_compositor_runlock(me);
	return 0;
}




PRIVATE NONNULL_T((2)) ATTR_IN_T(3) ssize_t CC
local_compositor_update_background_foreach_cb(void *UNUSED(cookie),
                                              struct local_window *window,
                                              struct video_rect const *intersect) {
	if (window->lw_background) {
		/* Must update the background of this window */
		struct local_compositor *comp = local_window_comp(window);
		struct video_gfx background_gfx;
		video_offset_t rel_x = video_rect_getxmin(intersect) - video_rect_getxmin(&window->lw_attr.vwa_rect);
		video_offset_t rel_y = video_rect_getymin(intersect) - video_rect_getymin(&window->lw_attr.vwa_rect);
		video_buffer_getgfx(window->lw_background, &background_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_fill(&background_gfx, rel_x, rel_y,
		               video_rect_getxdim(intersect),
		               video_rect_getydim(intersect),
		               comp->lc_background);

		/* Propagate updates to forward */
		local_window_update_background_propagate(window, &background_gfx, rel_x, rel_y, intersect);
	}
	return 0;
}

PRIVATE NONNULL_T((2)) ATTR_IN_T(3) ssize_t CC
local_compositor_update_background_foreach_nohit_cb(void *cookie, struct local_compositor *comp,
                                                    struct video_rect const *nohit_area) {
	struct video_gfx *screen_gfx = (video_gfx *)cookie;
	video_gfx_fill(screen_gfx,
	               video_rect_getxmin(nohit_area),
	               video_rect_getymin(nohit_area),
	               video_rect_getxdim(nohit_area),
	               video_rect_getydim(nohit_area),
	               comp->lc_background);
	return 0;
}

INTERN WUNUSED ATTR_INOUT(1) int CC
local_compositor_setbackground(struct video_compositor *__restrict self,
                               video_color_t background) {
	struct local_compositor *me = video_compositor_aslocal(self);
	local_compositor_wlock(me);
	if (me->lc_background != background) {
		struct video_gfx screen_gfx;
		struct local_window *start = TAILQ_FIRST(&me->lc_zorder_visi);
		video_buffer_getgfx(me->lc_buffer, &screen_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		me->lc_background = background;

		if (start) {
			struct video_rect whole_screen;
			video_rect_setxmin(&whole_screen, 0);
			video_rect_setymin(&whole_screen, 0);
			video_rect_setxdim(&whole_screen, video_gfx_getclipw(&screen_gfx));
			video_rect_setydim(&whole_screen, video_gfx_getcliph(&screen_gfx));
			local_compositor_foreach_above(me, start, &whole_screen,
			                               &local_compositor_update_background_foreach_cb,
			                               &local_compositor_update_background_foreach_nohit_cb,
			                               NULL, &screen_gfx);
		} else {
			video_gfx_fillall(&screen_gfx, background);
		}
	}
	local_compositor_wunlock(me);
	return 0;
}

INTERN struct video_compositor_ops local_compositor_ops = {};
INTERN ATTR_RETNONNULL WUNUSED struct video_compositor_ops *CC
_local_compositor_ops(void) {
	if (!local_compositor_ops.vcpo_destroy) {
		local_compositor_ops.vcpo_newwindow     = &local_compositor_newwindow;
		local_compositor_ops.vcpo_getdisplay    = &local_compositor_getdisplay;
		local_compositor_ops.vcpo_setdisplay    = &local_compositor_setdisplay;
		local_compositor_ops.vcpo_updatebuffer  = &local_compositor_updatebuffer;
		local_compositor_ops.vcpo_getfeatures   = &local_compositor_getfeatures;
		local_compositor_ops.vcpo_setfeatures   = &local_compositor_setfeatures;
		local_compositor_ops.vcpo_getbackground = &local_compositor_getbackground;
		local_compositor_ops.vcpo_setbackground = &local_compositor_setbackground;
		COMPILER_WRITE_BARRIER();
		local_compositor_ops.vcpo_destroy = &local_compositor_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &local_compositor_ops;
}



DECL_END

#endif /* !GUARD_LIBVIDEO_COMPOSITOR_COMPOSITOR_C */
