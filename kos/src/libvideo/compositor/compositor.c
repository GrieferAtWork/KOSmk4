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
#include <syslog.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>

#include <libvideo/codec/codecs.h>
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
	assertf(video_rect_getxdim(&me->lw_attr.vwa_rect), "Window X dimension cannot be 0");
	assertf(video_rect_getydim(&me->lw_attr.vwa_rect), "Window Y dimension cannot be 0");
	if (me->lw_attr.vwa_flags & VIDEO_WINDOW_F_HIDDEN) {
		assertf(!TAILQ_ISBOUND(me, lw_zorder_visi), "Hidden windows can't be in visible Z-order list");
		assertf(!LIST_ISBOUND(me, lw_passthru), "Hidden windows can't use passthru buffers");
		assertf(!me->lw_overlay_rgba, "RGBA overlay not needed for hidden window");
		assertf(!me->lw_overlay_mask, "MASK overlay not needed for hidden window");
		assertf(!me->lw_background, "Background buffer isn't needed by hidden window");
		assertf(!me->lw_display, "Display buffer isn't needed by hidden window");
	} else {
		assertf(TAILQ_ISBOUND(me, lw_zorder_visi), "Visible window must be part of visible Z-order list");
		if (LIST_ISBOUND(me, lw_passthru)) {
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
				                                   NULL, above_hits);
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


PRIVATE NONNULL((1)) ssize_t CC
local_window_hide_update_overlays_below_cb(void *cookie, struct local_window *window,
                                           struct video_rect const *intersect) {
	struct local_window *hideme = (struct local_window *)cookie;
	struct local_compositor *comp = local_window_comp(window);
	video_offset_t window_x = video_rect_getxmin(intersect) - video_rect_getxmin(&window->lw_attr.vwa_rect);
	video_offset_t window_y = video_rect_getymin(intersect) - video_rect_getymin(&window->lw_attr.vwa_rect);
	video_offset_t hideme_x = video_rect_getxmin(intersect) - video_rect_getxmin(&hideme->lw_attr.vwa_rect);
	video_offset_t hideme_y = video_rect_getymin(intersect) - video_rect_getymin(&hideme->lw_attr.vwa_rect);
	assert(comp == local_window_comp(hideme));

	/* Copy RGBA overlay data */
	if (window->lw_overlay_rgba) {
		/* Copy from "hideme" to "window->lw_overlay_rgba" */
		struct video_gfx window_gfx;
		video_buffer_getgfx(window->lw_overlay_rgba, &window_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		if (hideme->lw_overlay_rgba == NULL) {
			/* Window being hidden has no RGBA overlay -> windows underneath don't need one, either. */
			video_gfx_fill(&window_gfx, window_x, window_y,
			               video_rect_getxdim(intersect),
			               video_rect_getydim(intersect),
			               VIDEO_COLOR_RGBA(0, 0, 0, 0));
		} else {
			struct video_gfx hideme_gfx;
			video_buffer_getgfx(hideme->lw_overlay_rgba, &hideme_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
			video_gfx_bitblit(&window_gfx, window_x, window_y,
			                  &hideme_gfx, hideme_x, hideme_y,
			                  video_rect_getxdim(intersect),
			                  video_rect_getydim(intersect));
		}
	}

	/* Copy MASK overlay data */
	if (window->lw_overlay_mask) {
		/* Copy from "hideme->lw_overlay_mask" to "window->lw_overlay_mask" */
		struct video_gfx window_gfx;
		video_buffer_getgfx(window->lw_overlay_mask, &window_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		if (hideme->lw_overlay_mask == NULL) {
			/* Window being hidden has no MASK overlay -> windows underneath don't need one, either. */
			video_gfx_fill(&window_gfx, window_x, window_y,
			               video_rect_getxdim(intersect),
			               video_rect_getydim(intersect),
			               ALPHAMASK_0);
		} else {
			struct video_gfx hideme_gfx;
			video_buffer_getgfx(hideme->lw_overlay_mask, &hideme_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
			video_gfx_bitblit(&window_gfx, window_x, window_y,
			                  &hideme_gfx, hideme_x, hideme_y,
			                  video_rect_getxdim(intersect),
			                  video_rect_getydim(intersect));
		}
	}
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
	if (LIST_ISBOUND(self, lw_passthru))
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
	assert(!LIST_ISBOUND(self, lw_passthru));
	LIST_INSERT_HEAD(&comp->lc_passthru, self, lw_passthru);
	assert(LIST_ISBOUND(self, lw_passthru));
}

PRIVATE NONNULL((1)) ssize_t CC
local_window_hide_impl_below2_rgba_cb(void *UNUSED(cookie), struct local_window *window,
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
local_window_hide_impl_below2_mask_cb(void *UNUSED(cookie), struct local_window *window,
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
	if (LIST_ISBOUND(me, lw_passthru))
		return; /* Passthru already renders directly to screen */

	comp = local_window_comp(me);
	rel_x = video_rect_getxmin(screen_rect)- video_rect_getxmin(&me->lw_attr.vwa_rect);
	rel_y = video_rect_getymin(screen_rect) - video_rect_getymin(&me->lw_attr.vwa_rect);
	video_buffer_getgfx(me->lw_display ? me->lw_display : me->lw_content, &content_gfx,
	                    GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
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
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&overlay_render_gfx, rel_x, rel_y,
		                   &content_gfx, rel_x, rel_y,
		                   &overlay_rgba_gfx, rel_x, rel_y,
		                   video_rect_getxdim(screen_rect),
		                   video_rect_getydim(screen_rect));

		/* Combine "me->lw_overlay_mask" with "me->lw_overlay_rend" and render result to screen */
		video_buffer_getgfx(me->lw_overlay_mask, &overlay_mask_gfx,
		                    GFX_BLENDMODE_ALPHAMASK, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&comp->lc_buffer_gfx_alpha,
		                   video_rect_getxmin(screen_rect),
		                   video_rect_getymin(screen_rect),
		                   &overlay_mask_gfx, rel_x, rel_y,
		                   &overlay_render_gfx, rel_x, rel_y,
		                   video_rect_getxdim(screen_rect),
		                   video_rect_getydim(screen_rect));
	} else if (me->lw_overlay_rgba) {
		struct video_gfx overlay_gfx;
		assert(!me->lw_overlay_mask);
		video_buffer_getgfx(me->lw_overlay_rgba, &overlay_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&comp->lc_buffer_gfx_write,
		                   video_rect_getxmin(screen_rect),
		                   video_rect_getymin(screen_rect),
		                   &content_gfx, rel_x, rel_y,
		                   &overlay_gfx, rel_x, rel_y,
		                   video_rect_getxdim(screen_rect),
		                   video_rect_getydim(screen_rect));
	} else if (me->lw_overlay_mask) {
		struct video_gfx mask_gfx;
		video_buffer_getgfx(me->lw_overlay_mask, &mask_gfx,
		                    GFX_BLENDMODE_ALPHAMASK, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&comp->lc_buffer_gfx_alpha,
		                   video_rect_getxmin(screen_rect),
		                   video_rect_getymin(screen_rect),
		                   &mask_gfx, rel_x, rel_y,
		                   &content_gfx, rel_x, rel_y,
		                   video_rect_getxdim(screen_rect),
		                   video_rect_getydim(screen_rect));
	} else {
		video_gfx_bitblit(&comp->lc_buffer_gfx_write,
		                  video_rect_getxmin(screen_rect),
		                  video_rect_getymin(screen_rect),
		                  &content_gfx, rel_x, rel_y,
		                  video_rect_getxdim(screen_rect),
		                  video_rect_getydim(screen_rect));
		if (!(me->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA))
			try_convert_window_to_passthru(me);
	}
}

struct local_window_hide_update_background_above_data {
	struct video_gfx *lwhuba_src_gfx; /* [0..1] Source GFX */
	bool              lwhuba_render;  /* True if window hits should be rendered to screen */
};

PRIVATE NONNULL((1)) ssize_t CC
local_window_hide_update_background_above_cb(void *cookie, struct local_window *window,
                                             struct video_rect const *intersect) {
	struct local_window_hide_update_background_above_data *data;
	data = (struct local_window_hide_update_background_above_data *)cookie;
	if (window->lw_background) {
		struct local_window *above;
		struct video_gfx background_gfx;
		struct video_gfx display_gfx;
		struct video_gfx content_gfx;
		struct video_gfx *p_src_gfx = data->lwhuba_src_gfx;
		video_offset_t rel_x = video_rect_getxmin(intersect) - video_rect_getxmin(&window->lw_attr.vwa_rect);
		video_offset_t rel_y = video_rect_getymin(intersect) - video_rect_getymin(&window->lw_attr.vwa_rect);
		video_buffer_getgfx(window->lw_background, &background_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		if (p_src_gfx) {
			/* Can just copy from background buffer of window being hidden */
			video_gfx_bitblit(&background_gfx, rel_x, rel_y, p_src_gfx,
			                  video_rect_getxmin(intersect), video_rect_getymin(intersect),
			                  video_rect_getxdim(intersect), video_rect_getydim(intersect));
		} else {
			/* Must manually copy from "lw_display" of video buffers behind "window" */
			struct local_compositor *comp = local_window_comp(window);
			struct local_window *below = TAILQ_PREV(window, lw_zorder_visi);
			video_gfx_clipinfo_t clip;
			video_gfx_saveclip(&background_gfx, &clip);
			video_gfx_clip(&background_gfx, rel_x, rel_y,
			               video_rect_getxdim(intersect),
			               video_rect_getydim(intersect));
			if (below) {
				video_gfx_clip(&background_gfx,
				               -video_rect_getxmin(intersect),
				               -video_rect_getymin(intersect),
				               video_rect_getxdim(intersect),
				               video_rect_getydim(intersect));
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
		                   video_rect_getxdim(intersect),
		                   video_rect_getydim(intersect));

		/* Recursively update background buffers of windows in-front */
		above = TAILQ_NEXT(window, lw_zorder_visi);
		if (above) {
			struct local_compositor *comp = local_window_comp(window);
			struct local_window_hide_update_background_above_data inner_data;
			inner_data.lwhuba_render  = false;
			inner_data.lwhuba_src_gfx = video_gfx_clip(&display_gfx,
			                                           -video_rect_getxmin(&window->lw_attr.vwa_rect),
			                                           -video_rect_getymin(&window->lw_attr.vwa_rect),
			                                           video_rect_getxmin(&window->lw_attr.vwa_rect) + video_gfx_getclipw(&display_gfx),
			                                           video_rect_getymin(&window->lw_attr.vwa_rect) + video_gfx_getcliph(&display_gfx));
			local_compositor_foreach_above(comp, above, intersect,
			                               &local_window_hide_update_background_above_cb,
			                               NULL, &inner_data);
		}
	}

	/* If requested, draw the intersected region to the screen */
	if (data->lwhuba_render)
		local_window_draw_rect_to_screen(window, intersect);
	return 0;
}

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_window_hide_update_background_above_nohit_cb(void *UNUSED(cookie),
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
local_window_hide_impl(struct local_window *__restrict me) {
	struct local_window *below, *above;
	struct local_compositor *comp = local_window_comp(me);
	assert(!(me->lw_attr.vwa_flags & VIDEO_WINDOW_F_HIDDEN));
	assert(TAILQ_ISBOUND(me, lw_zorder_visi));
	assertf(!LIST_ISBOUND(me, lw_passthru), "Must be done by caller **first**");
	below = TAILQ_PREV(me, lw_zorder_visi);
	above = TAILQ_NEXT(me, lw_zorder_visi);
	TAILQ_UNBIND(&comp->lc_zorder_visi, me, lw_zorder_visi);
	if (below) {
		/* Reduce use-counters of overlay buffers of windows below. */
		local_compositor_foreach_all_below(comp, below, &me->lw_attr.vwa_rect,
		                                   (me->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA)
		                                   ? &local_window_hide_impl_below2_rgba_cb
		                                   : &local_window_hide_impl_below2_mask_cb,
		                                   NULL, NULL);
		/* Update overlays in windows underneath ours (that are still in-use) */
		local_compositor_foreach_below(comp, below, &me->lw_attr.vwa_rect,
		                               &local_window_hide_update_overlays_below_cb,
		                               NULL, me);
	}
	if (above) {
		/* Update   background   buffers  of   windows   above  ours.
		 * For this purpose, pixel data can be read from our window's
		 * background-buffer (if we have one), or has to be generated
		 * dynamically (if we don't have one) */
		struct video_gfx src_gfx;
		struct local_window_hide_update_background_above_data data;
		data.lwhuba_src_gfx = NULL;
		if (me->lw_background) {
			data.lwhuba_src_gfx = video_buffer_getgfx(me->lw_background, &src_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
			data.lwhuba_src_gfx = video_gfx_clip(data.lwhuba_src_gfx,
			                                     -video_rect_getxmin(&me->lw_attr.vwa_rect),
			                                     -video_rect_getymin(&me->lw_attr.vwa_rect),
			                                     video_rect_getxmin(&me->lw_attr.vwa_rect) + video_gfx_getclipw(data.lwhuba_src_gfx),
			                                     video_rect_getymin(&me->lw_attr.vwa_rect) + video_gfx_getcliph(data.lwhuba_src_gfx));
		}
		local_compositor_foreach_above(comp, above, &me->lw_attr.vwa_rect,
		                               &local_window_hide_update_background_above_cb,
		                               &local_window_hide_update_background_above_nohit_cb,
		                               &data);
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
		if (LIST_ISBOUND(me, lw_passthru)) {
			video_buffer_region_revoke(me->lw_content);
			LIST_UNBIND(me, lw_passthru);
		}
		local_window_hide_impl(me);
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
	assert(rel_x == video_rect_getxmin(intersect) - video_rect_getxmin(&window->lw_attr.vwa_rect));
	assert(rel_y == video_rect_getymin(intersect) - video_rect_getymin(&window->lw_attr.vwa_rect));
	assert(window->lw_display);

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
		               -video_rect_getxmin(&window->lw_attr.vwa_rect),
		               -video_rect_getymin(&window->lw_attr.vwa_rect),
		               video_rect_getxmin(&window->lw_attr.vwa_rect) + video_gfx_getclipw(&display_gfx),
		               video_rect_getymin(&window->lw_attr.vwa_rect) + video_gfx_getcliph(&display_gfx));
		local_compositor_foreach_above(comp, above, intersect,
		                               &local_window_update_background_cb,
		                               NULL, &display_gfx);
	}
}

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_window_update_background_cb(void *cookie, struct local_window *window,
                                  struct video_rect const *intersect) {
	struct video_gfx *src_gfx = (struct video_gfx *)cookie;
	assert((window->lw_background != NULL) == (window->lw_display != NULL));
	if (window->lw_background) {
		struct video_gfx background_gfx;
		video_offset_t rel_x = video_rect_getxmin(intersect) - video_rect_getxmin(&window->lw_attr.vwa_rect);
		video_offset_t rel_y = video_rect_getymin(intersect) - video_rect_getymin(&window->lw_attr.vwa_rect);

		/* Update background buffer of window */
		video_buffer_getgfx(window->lw_background, &background_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit(&background_gfx, rel_x, rel_y, src_gfx,
		                  video_rect_getxmin(intersect), video_rect_getymin(intersect),
		                  video_rect_getxdim(intersect), video_rect_getydim(intersect));
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
	struct local_compositor *comp = local_window_comp(window);
	struct video_gfx dst_gfx;
	video_offset_t rel_x = video_rect_getxmin(intersect) - video_rect_getxmin(&window->lw_attr.vwa_rect);
	video_offset_t rel_y = video_rect_getymin(intersect) - video_rect_getymin(&window->lw_attr.vwa_rect);
	data = (struct local_window_update_overlay_data const *)cookie;
	assertf(window->lw_overlay_rgba,
	        "We get here from an alpha-enabled window above ours, "
	        "so we the RGBA buffer should always be allocated");
	video_buffer_getgfx(window->lw_overlay_rgba, &dst_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	if (data->lwuod_above_overlay) {
		video_gfx_bitblit3(&dst_gfx, rel_x, rel_y,
		                   data->lwuod_above_overlay,
		                   video_rect_getxmin(intersect), video_rect_getymin(intersect),
		                   &data->lwuod_above_content,
		                   video_rect_getxmin(intersect), video_rect_getymin(intersect),
		                   video_rect_getxdim(intersect), video_rect_getydim(intersect));
	} else {
		video_gfx_bitblit(&dst_gfx, rel_x, rel_y,
		                  &data->lwuod_above_content,
		                  video_rect_getxmin(intersect), video_rect_getymin(intersect),
		                  video_rect_getxdim(intersect), video_rect_getydim(intersect));
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
			               -video_rect_getxmin(&window->lw_attr.vwa_rect),
			               -video_rect_getymin(&window->lw_attr.vwa_rect),
			               video_rect_getxmin(&window->lw_attr.vwa_rect) + video_gfx_getclipw(&dst_gfx),
			               video_rect_getymin(&window->lw_attr.vwa_rect) + video_gfx_getcliph(&dst_gfx));
			video_gfx_clip(&inner_data.lwuod_above_content,
			               -video_rect_getxmin(&window->lw_attr.vwa_rect),
			               -video_rect_getymin(&window->lw_attr.vwa_rect),
			               video_rect_getxmin(&window->lw_attr.vwa_rect) + video_gfx_getclipw(&inner_data.lwuod_above_content),
			               video_rect_getymin(&window->lw_attr.vwa_rect) + video_gfx_getcliph(&inner_data.lwuod_above_content));
			local_compositor_foreach_below(comp, below, intersect,
			                               &local_window_update_overlay_cb,
			                               NULL, &inner_data);
		}
	}
	return 0;
}

/* Bring pixel data for the given "rect" to-screen.
 * Caller  is responsible not to call this function
 * when `me' is making use of a passthru buffer.
 *
 * Caller is also responsible to updaterect within
 * the compositor's output display. */
PRIVATE ATTR_INOUT(1) ATTR_IN(2) void LIBVIDEO_GFX_CC
local_window_updaterect_locked(struct local_window *__restrict me,
                               struct video_rect const *__restrict screen_rect) {
	struct local_compositor *comp = local_window_comp(me);
	struct video_gfx content_gfx;
	video_offset_t rel_x = video_rect_getxmin(screen_rect) - video_rect_getxmin(&me->lw_attr.vwa_rect);
	video_offset_t rel_y = video_rect_getymin(screen_rect) - video_rect_getymin(&me->lw_attr.vwa_rect);
	local_window_assert(me);
	assertf(!LIST_ISBOUND(me, lw_passthru), "Don't call this function for passthru windows!");
	assert((me->lw_background != NULL) == (me->lw_display != NULL));
	video_buffer_getgfx(me->lw_content, &content_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	if (me->lw_background) {
		struct video_gfx display_gfx;
		struct video_gfx background_gfx;
		video_buffer_getgfx(me->lw_background, &background_gfx, GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(me->lw_display, &display_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&display_gfx, rel_x, rel_y,
		                   &background_gfx, rel_x, rel_y,
		                   &content_gfx, rel_x, rel_y,
		                   video_rect_getxdim(screen_rect),
		                   video_rect_getydim(screen_rect));
		content_gfx = display_gfx;
	}

	if (me->lw_overlay_rend) {
		struct video_gfx overlay_render_gfx;
		struct video_gfx overlay_rgba_gfx;
		struct video_gfx overlay_mask_gfx;
		struct video_gfx alpha_content_gfx;
		assert(me->lw_overlay_rgba);
		assert(me->lw_overlay_mask);

		/* Update overlay render display */
		alpha_content_gfx = content_gfx;
		video_gfx_setblend(&alpha_content_gfx, GFX_BLENDMODE_ALPHA);
		video_buffer_getgfx(me->lw_overlay_rend, &overlay_render_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(me->lw_overlay_rgba, &overlay_rgba_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&overlay_render_gfx, rel_x, rel_y,
		                   &alpha_content_gfx, rel_x, rel_y,
		                   &overlay_rgba_gfx, rel_x, rel_y,
		                   video_rect_getxdim(screen_rect),
		                   video_rect_getydim(screen_rect));

		/* Combine "me->lw_overlay_mask" with "me->lw_overlay_rend" and render result to screen */
		video_buffer_getgfx(me->lw_overlay_mask, &overlay_mask_gfx,
		                    GFX_BLENDMODE_ALPHAMASK, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&comp->lc_buffer_gfx_alpha,
		                   video_rect_getxmin(screen_rect),
		                   video_rect_getymin(screen_rect),
		                   &overlay_mask_gfx, rel_x, rel_y,
		                   &overlay_render_gfx, rel_x, rel_y,
		                   video_rect_getxdim(screen_rect),
		                   video_rect_getydim(screen_rect));
	} else if (me->lw_overlay_rgba) {
		struct local_window *above;
		struct video_gfx overlay_gfx;
		struct video_gfx alpha_content_gfx;
		assert(!me->lw_overlay_mask);
		video_buffer_getgfx(me->lw_overlay_rgba, &overlay_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		alpha_content_gfx = content_gfx;
		video_gfx_setblend(&alpha_content_gfx, GFX_BLENDMODE_ALPHA);
		video_gfx_bitblit3(&comp->lc_buffer_gfx_write,
		                   video_rect_getxmin(screen_rect),
		                   video_rect_getymin(screen_rect),
		                   &alpha_content_gfx, rel_x, rel_y,
		                   &overlay_gfx, rel_x, rel_y,
		                   video_rect_getxdim(screen_rect),
		                   video_rect_getydim(screen_rect));

		/* Must also update the background buffers of windows above */
		above = TAILQ_NEXT(me, lw_zorder_visi);
		if (above) {
			video_gfx_clip(&content_gfx,
			               -video_rect_getxmin(&me->lw_attr.vwa_rect),
			               -video_rect_getymin(&me->lw_attr.vwa_rect),
			               video_rect_getxmin(&me->lw_attr.vwa_rect) + video_gfx_getclipw(&content_gfx),
			               video_rect_getymin(&me->lw_attr.vwa_rect) + video_gfx_getcliph(&content_gfx));
			local_compositor_foreach_above(comp, above, screen_rect,
			                               &local_window_update_background_cb,
			                               NULL, &content_gfx);
		}
	} else if (me->lw_overlay_mask) {
		struct video_gfx mask_gfx;
		video_buffer_getgfx(me->lw_overlay_mask, &mask_gfx,
		                    GFX_BLENDMODE_ALPHAMASK, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&comp->lc_buffer_gfx_alpha,
		                   video_rect_getxmin(screen_rect),
		                   video_rect_getymin(screen_rect),
		                   &mask_gfx, rel_x, rel_y,
		                   &content_gfx, rel_x, rel_y,
		                   video_rect_getxdim(screen_rect),
		                   video_rect_getydim(screen_rect));
	} else {
		video_gfx_bitblit(&comp->lc_buffer_gfx_write,
		                  video_rect_getxmin(screen_rect),
		                  video_rect_getymin(screen_rect),
		                  &content_gfx, rel_x, rel_y,
		                  video_rect_getxdim(screen_rect),
		                   video_rect_getydim(screen_rect));
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
				               -video_rect_getxmin(&me->lw_attr.vwa_rect),
				               -video_rect_getymin(&me->lw_attr.vwa_rect),
				               video_rect_getxmin(&me->lw_attr.vwa_rect) + video_gfx_getclipw(&overlay_gfx),
				               video_rect_getymin(&me->lw_attr.vwa_rect) + video_gfx_getcliph(&overlay_gfx));
				data.lwuod_above_overlay = &overlay_gfx;
			}
			video_buffer_getgfx(me->lw_content, &data.lwuod_above_content,
			                    GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
			video_gfx_clip(&data.lwuod_above_content,
			               -video_rect_getxmin(&me->lw_attr.vwa_rect),
			               -video_rect_getymin(&me->lw_attr.vwa_rect),
			               video_rect_getxmin(&me->lw_attr.vwa_rect) + video_gfx_getclipw(&data.lwuod_above_content),
			               video_rect_getymin(&me->lw_attr.vwa_rect) + video_gfx_getcliph(&data.lwuod_above_content));
			local_compositor_foreach_below(comp, below, screen_rect,
			                               &local_window_update_overlay_cb,
			                               NULL, &data);
		}
	}
}

INTERN ATTR_INOUT(1) ATTR_IN(2) void LIBVIDEO_GFX_CC
local_window_updaterect(struct video_display *__restrict self,
                        struct video_rect const *__restrict rect) {
	struct local_window *me = local_window_fromdisplay(self);
	struct local_compositor *comp = local_window_comp(me);
	REF struct video_display *display;
	struct video_rect window_rect;
	struct video_rect update_rect;
	video_rect_setxmin(&window_rect, 0);
	video_rect_setymin(&window_rect, 0);
	local_compositor_rlock(comp);
	local_window_assert(me);
	video_rect_setxdim(&window_rect, video_rect_getxdim(&me->lw_attr.vwa_rect));
	video_rect_setydim(&window_rect, video_rect_getydim(&me->lw_attr.vwa_rect));
	if (!video_rect_intersect_overflow_in_b(&window_rect, rect, &update_rect)) {
		/* Updated area is outside the window's bounds */
		local_compositor_runlock(comp);
		return;
	}

	/* Make "update_rect" be screen-absolute */
	video_rect_addx(&update_rect, video_rect_getxmin(&me->lw_attr.vwa_rect));
	video_rect_addy(&update_rect, video_rect_getymin(&me->lw_attr.vwa_rect));

	/* If not passthru, update window buffers */
	if (!LIST_ISBOUND(me, lw_passthru))
		local_window_updaterect_locked(me, &update_rect);

	/* Load compositor output display */
	display = comp->lc_display;
	video_display_incref(display);

	/* Unlock compositor */
	local_compositor_runlock(comp);

	/* Propagate the rect update request to the display */
	video_display_updaterect(display, &update_rect);
	video_display_decref(display);
}

INTERN ATTR_INOUT(1) ATTR_INS(2, 3) void LIBVIDEO_GFX_CC
local_window_updaterects(struct video_display *__restrict self,
                         struct video_rect const *__restrict rects,
                         size_t n_rects) {
	struct local_window *me = local_window_fromdisplay(self);
	struct local_compositor *comp = local_window_comp(me);
	REF struct video_display *display;
	struct video_rect window_rect;
	struct video_rect update_rect_union;
	if unlikely(!n_rects)
		return;
	video_rect_setxmin(&window_rect, 0);
	video_rect_setymin(&window_rect, 0);
	local_compositor_rlock(comp);
	local_window_assert(me);
	video_rect_setxdim(&window_rect, video_rect_getxdim(&me->lw_attr.vwa_rect));
	video_rect_setydim(&window_rect, video_rect_getydim(&me->lw_attr.vwa_rect));

	/* Skip non-intersecting update rects */
	for (;;) {
		struct video_rect const *rect;
		--n_rects;
		rect = rects++;
		if (video_rect_intersect_overflow_in_b(&window_rect, rect, &update_rect_union))
			break;
		if unlikely(!n_rects) {
			local_compositor_runlock(comp);
			return;
		}
	}

	/* Make "update_rect_union" be screen-absolute */
	video_rect_addx(&update_rect_union, video_rect_getxmin(&me->lw_attr.vwa_rect));
	video_rect_addy(&update_rect_union, video_rect_getymin(&me->lw_attr.vwa_rect));

	/* Update additional rects and form a union */
	if (!LIST_ISBOUND(me, lw_passthru)) {
		/* If not passthru, update window buffers */
		local_window_updaterect_locked(me, &update_rect_union);
		for (; n_rects; --n_rects, ++rects) {
			struct video_rect update_rect;
			if (video_rect_intersect_overflow_in_b(&window_rect, rects, &update_rect)) {
				video_rect_addx(&update_rect, video_rect_getxmin(&me->lw_attr.vwa_rect));
				video_rect_addy(&update_rect, video_rect_getymin(&me->lw_attr.vwa_rect));
				local_window_updaterect_locked(me, &update_rect);
				video_rect_union(&update_rect_union, &update_rect);
			}
		}
	} else {
		for (; n_rects; --n_rects, ++rects) {
			struct video_rect update_rect;
			if (video_rect_intersect_overflow_in_b(&window_rect, rects, &update_rect)) {
				video_rect_addx(&update_rect, video_rect_getxmin(&me->lw_attr.vwa_rect));
				video_rect_addy(&update_rect, video_rect_getymin(&me->lw_attr.vwa_rect));
				video_rect_union(&update_rect_union, &update_rect);
			}
		}
	}

	/* Load compositor output display */
	display = comp->lc_display;
	video_display_incref(display);

	/* Unlock compositor */
	local_compositor_runlock(comp);

	/* Propagate the rect update request to the display */
	video_display_updaterect(display, &update_rect_union);
	video_display_decref(display);}


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

struct local_window_position_update_data {
	struct local_window *lwpud_old_over;     /* [0..1] Window that our's is currently over (or `NULL' if in the background) */
	struct local_window *lwpud_new_over;     /* [0..1] Window to place ours over (or `NULL' to place in background) */
	video_offset_t       lwpud_xoff;         /* X offset applied to old window top-left */
	video_offset_t       lwpud_yoff;         /* Y offset applied to old window top-left */
	struct video_rect    lwpud_acquire_v[4]; /* Screen rects that are now used by the window (within its Z-layer) */
	struct video_rect    lwpud_release_v[4]; /* Screen rects that are no longer used by the window (within its Z-layer) */
	unsigned int         lwpud_acquire_c;    /* # of elements in `lwpud_acquire_v' */
	unsigned int         lwpud_release_c;    /* # of elements in `lwpud_release_v' */
	unsigned int         lwpud_actions;      /* Actions that are being performed (set of `WINDOW_ACTION_*') */
#define WINDOW_ACTION_NONE   0x0000 /* No action */
#define WINDOW_ACTION_MOVE   0x0001 /* `lwpud_xoff', `lwpud_yoff', `lwpud_acquire_c', or `lwpud_release_c' are non-zero */
#define WINDOW_ACTION_ZMOVE  0x0002 /* `lwpud_old_over != lwpud_new_over' */
#define WINDOW_ACTION_RESIZE 0x0004 /* New window size differs from old */
//efine WINDOW_ACTION_       0x0008  * ... */
#define WINDOW_ACTION_HIDE   0x0010 /* Hide window */
#define WINDOW_ACTION_SHOW   0x0020 /* Show window */
#define WINDOW_ACTION_YALPHA 0x0040 /* Add alpha to window */
#define WINDOW_ACTION_NALPHA 0x0080 /* Remove alpha to window */
#define WINDOW_ACTION_YPASS  0x0100 /* Enable passthru for window */
#define WINDOW_ACTION_NPASS  0x0200 /* Disable passthru for window */
};

PRIVATE ATTR_OUT(1) ATTR_IN(2) ATTR_IN(3) void CC
local_window_position_update_data_init(struct local_window_position_update_data *__restrict self,
                                       struct local_window *__restrict window,
                                       struct video_window_position const *__restrict new_position) {
	struct local_compositor *comp = local_window_comp(window);
	video_window_flag_t old_flags = window->lw_attr.vwa_flags;
	video_window_flag_t new_flags = new_position->vwp_attr.vwa_flags;

	/* Calculate position deltas */
	self->lwpud_xoff = video_rect_getxmin(&new_position->vwp_attr.vwa_rect) -
	                   video_rect_getxmin(&window->lw_attr.vwa_rect);
	self->lwpud_yoff = video_rect_getymin(&new_position->vwp_attr.vwa_rect) -
	                   video_rect_getymin(&window->lw_attr.vwa_rect);
	self->lwpud_acquire_c = video_rect_subtract(&new_position->vwp_attr.vwa_rect, &window->lw_attr.vwa_rect, self->lwpud_acquire_v);
	self->lwpud_release_c = video_rect_subtract(&window->lw_attr.vwa_rect, &new_position->vwp_attr.vwa_rect, self->lwpud_release_v);

	/* Calculate new Z-order */
	self->lwpud_old_over = TAILQ_PREV(window, lw_zorder);
	if (new_position->vwp_over == VIDEO_WINDOW_MOVE_OVER__UNCHANGED) {
		self->lwpud_new_over = self->lwpud_old_over;
	} else if (new_position->vwp_over == VIDEO_WINDOW_MOVE_OVER__FOREGROUND) {
		self->lwpud_new_over = TAILQ_LAST(&comp->lc_zorder);
	} else if (new_position->vwp_over == VIDEO_WINDOW_MOVE_OVER__BACKGROUND) {
		self->lwpud_new_over = NULL;
	} else if (new_position->vwp_over == VIDEO_WINDOW_MOVE_OVER__FORWARD) {
		if (self->lwpud_old_over) {
			struct local_window *next = TAILQ_NEXT(self->lwpud_old_over, lw_zorder);
			self->lwpud_new_over = next ? next : self->lwpud_old_over;
		} else {
			self->lwpud_new_over = TAILQ_FIRST(&comp->lc_zorder);
		}
	} else if (new_position->vwp_over == VIDEO_WINDOW_MOVE_OVER__BACKWARD) {
		self->lwpud_new_over = self->lwpud_old_over ? TAILQ_PREV(self->lwpud_old_over, lw_zorder) : NULL;
	} else {
		self->lwpud_new_over = local_window_fromwindow(new_position->vwp_over);
#ifndef NDEBUG
		{
			struct local_window *iter;
			bool exists = false;
			TAILQ_FOREACH (iter, &comp->lc_zorder, lw_zorder) {
				if (iter == self->lwpud_new_over) {
					exists = true;
					break;
				}
			}
			assertf(exists, "Invalid window: %p", self->lwpud_new_over);
		}
#endif /* !NDEBUG */
	}

	/* Determine actions to-be performed */
	self->lwpud_actions = WINDOW_ACTION_NONE;

	/* Check for changes in the window's position/size */
	if (self->lwpud_xoff || self->lwpud_yoff ||
	    self->lwpud_acquire_c || self->lwpud_release_c) {
		self->lwpud_actions |= WINDOW_ACTION_MOVE;
		if (video_rect_getxdim(&window->lw_attr.vwa_rect) != video_rect_getxdim(&new_position->vwp_attr.vwa_rect) ||
		    video_rect_getydim(&window->lw_attr.vwa_rect) != video_rect_getydim(&new_position->vwp_attr.vwa_rect))
			self->lwpud_actions |= WINDOW_ACTION_RESIZE;
	} else {
		assert(video_rect_getxdim(&window->lw_attr.vwa_rect) == video_rect_getxdim(&new_position->vwp_attr.vwa_rect));
		assert(video_rect_getydim(&window->lw_attr.vwa_rect) == video_rect_getydim(&new_position->vwp_attr.vwa_rect));
	}
	if (self->lwpud_new_over != self->lwpud_old_over)
		self->lwpud_actions |= WINDOW_ACTION_ZMOVE;

	/* Check for changes in window flags */
	if (old_flags != new_flags) {
		if ((old_flags & VIDEO_WINDOW_F_PASSTHRU) != (new_flags & VIDEO_WINDOW_F_PASSTHRU)) {
			if (new_flags & VIDEO_WINDOW_F_PASSTHRU) {
				if (!LIST_ISBOUND(window, lw_passthru))
					self->lwpud_actions |= WINDOW_ACTION_YPASS;
			} else {
				if (LIST_ISBOUND(window, lw_passthru))
					self->lwpud_actions |= WINDOW_ACTION_NPASS;
			}
		}
		if ((old_flags & VIDEO_WINDOW_F_ALPHA) != (new_flags & VIDEO_WINDOW_F_ALPHA)) {
			if (new_flags & VIDEO_WINDOW_F_ALPHA) {
				/* Passthru must be disabled for alpha to be enabled */
				self->lwpud_actions &= ~(WINDOW_ACTION_YPASS | WINDOW_ACTION_NPASS);
				if (LIST_ISBOUND(window, lw_passthru))
					self->lwpud_actions |= WINDOW_ACTION_NPASS;
				self->lwpud_actions |= WINDOW_ACTION_YALPHA;
			} else {
				self->lwpud_actions |= WINDOW_ACTION_NALPHA;
			}
		}
		if ((old_flags & VIDEO_WINDOW_F_HIDDEN) != (new_flags & VIDEO_WINDOW_F_HIDDEN)) {
			if (new_flags & VIDEO_WINDOW_F_HIDDEN) {
				/* Passthru must be disabled before the window can be hidden */
				self->lwpud_actions &= ~(WINDOW_ACTION_YPASS | WINDOW_ACTION_NPASS);
				if (LIST_ISBOUND(window, lw_passthru))
					self->lwpud_actions |= WINDOW_ACTION_NPASS;
				self->lwpud_actions |= WINDOW_ACTION_HIDE;
				/* When hiding a window, no need to perform move updates */
				self->lwpud_actions &= ~WINDOW_ACTION_MOVE;
			} else {
				self->lwpud_actions |= WINDOW_ACTION_SHOW;
			}
		}
	}
}


INTERN WUNUSED ATTR_INOUT(1) ATTR_IN(2) int CC
local_window_setposition(struct video_window *__restrict self,
                         struct video_window_position const *__restrict new_position) {
	struct local_window_position_update_data data;
	struct local_window *me = local_window_fromdisplay(self);
	struct local_compositor *comp = local_window_comp(me);
	if ((new_position->vwp_attr.vwa_flags & ~VIDEO_WINDOW_F_ALL) ||
	    (video_rect_getxdim(&new_position->vwp_attr.vwa_rect) <= 0) ||
	    (video_rect_getydim(&new_position->vwp_attr.vwa_rect) <= 0)) {
		errno = EINVAL;
		return -1;
	}
	local_compositor_wlock(comp);
	local_window_assert(me);
	local_window_position_update_data_init(&data, me, new_position);

	/* Check for simple case: no actions are being performed. */
	if unlikely(data.lwpud_actions == WINDOW_ACTION_NONE) {
		local_compositor_wunlock(comp);
		return 0;
	}

#if 1
	/* TODO */
	local_compositor_wunlock(comp);
	errno = ENOSYS;
	return -1;
#else
	if (data.lwpud_actions & (WINDOW_ACTION_YALPHA |
	                          WINDOW_ACTION_NALPHA |
	                          WINDOW_ACTION_YPASS |
	                          WINDOW_ACTION_NPASS |
	                          WINDOW_ACTION_ZMOVE)) {
		/* TODO */
		local_compositor_wunlock(comp);
		errno = ENOSYS;
		return -1;
	}

	/* Perform position updates... */
	if (data.lwpud_actions & WINDOW_ACTION_HIDE) {
		if (data.lwpud_actions & WINDOW_ACTION_RESIZE) {
			/* TODO */
		}
		/* TODO */

	} else if (data.lwpud_actions & WINDOW_ACTION_SHOW) {
		if (data.lwpud_actions & WINDOW_ACTION_RESIZE) {
			/* TODO */
		}

		/* TODO */
	} else if (data.lwpud_actions & WINDOW_ACTION_MOVE) {
	}

	/* Assign new attributes */
	me->lw_attr = new_position->vwp_attr;
	local_compositor_wunlock(comp);
	errno = ENOSYS;
	return -1;
#endif
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
                              local_compositor_foreach_cb_t cb,          /* [1..1] */
                              local_compositor_foreach_nohit_cb_t nohit, /* [0..1] */
                              void *cookie, local_compositor_foreach_next_t next) {
	ssize_t temp, result = 0;
	struct local_window *iter;
	struct video_rect *stack;
	size_t window_rect_count = 1;
	size_t max_stack_sz;
	assert(video_rect_getxdim(rect));
	assert(video_rect_getydim(rect));

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
	for (iter = start; (iter = (*next)(iter)) != NULL;) {
		if (video_rect_intersects(rect, &iter->lw_attr.vwa_rect))
			++window_rect_count;
	}
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
							memcpyc(&stack[stacksz], more + 1, n_more,
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
			video_offset_t used_y = video_rect_getymin(rect) + y;
			video_coord_t x = 0;
			for (;;) {
				struct video_rect intersect;
				video_coord_t hit_x = x;
				struct local_window *hit = local_compositor_windowat(start, next, video_rect_getxmin(rect) + x, used_y);
				while (++x < video_rect_getxdim(rect) &&
				       hit == local_compositor_windowat(start, next, video_rect_getxmin(rect) + x, used_y))
					;
				video_rect_setxmin(&intersect, video_rect_getxmin(rect) + hit_x);
				video_rect_setymin(&intersect, used_y);
				video_rect_setxdim(&intersect, x - hit_x);
				video_rect_setydim(&intersect, 1);
				if (hit) {
					temp = (*cb)(cookie, hit, &intersect);
				} else if (nohit) {
					temp = (*nohit)(cookie, self, &intersect);
				} else {
					temp = 0;
				}
				if unlikely(temp < 0) {
					result = temp;
					goto done_loop;
				}
				result += temp;
				if (x >= video_rect_getxdim(rect))
					break;
			}
		} while (++y < video_rect_getydim(rect));
done_loop:;
	}
	return result;
}

INTERN ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_above(struct local_compositor *__restrict self,
                               struct local_window *__restrict start,
                               struct video_rect const *rect,
                               local_compositor_foreach_cb_t cb,          /* [1..1] */
                               local_compositor_foreach_nohit_cb_t nohit, /* [0..1] */
                               void *cookie) {
	return local_compositor_foreach_impl(self, start, rect, cb, nohit,
	                                     cookie, &local_window_visi_above);
}

/* Same as "local_compositor_foreach_above", but cast rays towards negative Z */
INTERN ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_below(struct local_compositor *__restrict self,
                               struct local_window *__restrict start,
                               struct video_rect const *rect,
                               local_compositor_foreach_cb_t cb,          /* [1..1] */
                               local_compositor_foreach_nohit_cb_t nohit, /* [0..1] */
                               void *cookie) {
	return local_compositor_foreach_impl(self, start, rect, cb, nohit,
	                                     cookie, &local_window_visi_below);
}

/* Like above, but the imaginary "rays" being cast can travel through windows.
 * iow: these functions enumerate **all** windows and their intersections with
 *      the given `rect', even if the same sub-region intersects with multiple
 *      windows. */
INTERN ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_all_above(struct local_compositor *__restrict self,
                                   struct local_window *__restrict start,
                                   struct video_rect const *rect,
                                   local_compositor_foreach_cb_t cb,
                                   local_compositor_foreach_rollback_cb_t rollback, /* [0..1] */
                                   void *cookie) {
	ssize_t temp, result = 0;
	struct local_window *iter = start;
	(void)self;
	do {
		struct video_rect intersect;
		assert(self == local_window_comp(iter));
		if (video_rect_intersect(&iter->lw_attr.vwa_rect, rect, &intersect)) {
			temp = (*cb)(cookie, iter, &intersect);
			if unlikely(temp < 0) {
				if (rollback) {
					while (iter != start) {
						iter = TAILQ_PREV(iter, lw_zorder_visi);
						if (video_rect_intersect(&iter->lw_attr.vwa_rect, rect, &intersect))
							(*rollback)(cookie, iter, &intersect);
					}
				}
				return temp;
			}
			result += temp;
		}
	} while ((iter = TAILQ_NEXT(iter, lw_zorder_visi)) != NULL);
	return result;
}

INTERN ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_all_below(struct local_compositor *__restrict self,
                                   struct local_window *__restrict start,
                                   struct video_rect const *rect,
                                   local_compositor_foreach_cb_t cb,
                                   local_compositor_foreach_rollback_cb_t rollback, /* [0..1] */
                                   void *cookie) {
	ssize_t temp, result = 0;
	struct local_window *iter = start;
	assert(self == local_window_comp(start));
	(void)self;
	do {
		struct video_rect intersect;
		if (video_rect_intersect(&iter->lw_attr.vwa_rect, rect, &intersect)) {
			temp = (*cb)(cookie, iter, &intersect);
			if unlikely(temp < 0) {
				if (rollback) {
					while (iter != start) {
						iter = TAILQ_NEXT(iter, lw_zorder_visi);
						if (video_rect_intersect(&iter->lw_attr.vwa_rect, rect, &intersect))
							(*rollback)(cookie, iter, &intersect);
					}
				}
				return temp;
			}
			result += temp;
		}
	} while ((iter = TAILQ_PREV(iter, lw_zorder_visi)) != NULL);
	return result;
}


/* Force a re-draw of all windows (and the background) that intersect with `screen_rect' */
INTERN ATTR_INOUT(1) ATTR_IN(2) void CC
local_compositor_updaterect__nopropagate(struct local_compositor *__restrict self,
                                         struct video_rect const *screen_rect) {
	struct local_window *last = TAILQ_LAST(&self->lc_zorder_visi);
	if likely(last) {
		local_compositor_render_behind(self, last, screen_rect, &self->lc_buffer_gfx_write);
	} else {
		video_gfx_fill(&self->lc_buffer_gfx_write,
		               video_rect_getxmin(screen_rect),
		               video_rect_getymin(screen_rect),
		               video_rect_getxdim(screen_rect),
		               video_rect_getydim(screen_rect),
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
	if (LIST_ISBOUND(window, lw_passthru))
		return 0;
	out = (struct video_gfx *)cookie;
	src = window->lw_display ? window->lw_display : window->lw_content;
	rel_x = video_rect_getxmin(intersect) - video_rect_getxmin(&window->lw_attr.vwa_rect);
	rel_y = video_rect_getymin(intersect) - video_rect_getymin(&window->lw_attr.vwa_rect);
	video_buffer_getgfx(src, &src_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	video_gfx_bitblit(out, video_rect_getxmin(intersect), video_rect_getymin(intersect),
	                  &src_gfx, rel_x, rel_y,
	                  video_rect_getxdim(intersect), video_rect_getydim(intersect));
	return 0;
}

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_foreach_nohit_cb(void *cookie, struct local_compositor *comp,
                                         struct video_rect const *intersect) {
	struct video_gfx *out = (struct video_gfx *)cookie;
	video_gfx_fill(out, video_rect_getxmin(intersect), video_rect_getymin(intersect),
	               video_rect_getxdim(intersect), video_rect_getydim(intersect),
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
	                               out);
}


PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_rgba_overlay_above_foreach_cb(void *cookie, struct local_window *window,
                                                      struct video_rect const *intersect) {
	struct video_gfx *out_gfx = (struct video_gfx *)cookie;
	struct video_gfx content_gfx;
	video_offset_t rel_x = video_rect_getxmin(intersect) - video_rect_getxmin(&window->lw_attr.vwa_rect);
	video_offset_t rel_y = video_rect_getymin(intersect) - video_rect_getymin(&window->lw_attr.vwa_rect);
	if (window->lw_overlay_rgba) {
		struct video_gfx overlay_gfx;
		video_buffer_getgfx(window->lw_content, &content_gfx, GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(window->lw_overlay_rgba, &overlay_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(out_gfx, video_rect_getxmin(intersect), video_rect_getymin(intersect),
		                   &content_gfx, rel_x, rel_y,
		                   &overlay_gfx, rel_x, rel_y,
		                   video_rect_getxdim(intersect),
		                   video_rect_getydim(intersect));
	} else {
		video_buffer_getgfx(window->lw_content, &content_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit(out_gfx, video_rect_getxmin(intersect), video_rect_getymin(intersect),
		                  &content_gfx, rel_x, rel_y,
		                  video_rect_getxdim(intersect),
		                  video_rect_getydim(intersect));
	}
	return 0;
}

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_rgba_overlay_above_nohit_cb(void *cookie,
                                                    struct local_compositor *UNUSED(comp),
                                                    struct video_rect const *intersect) {
	struct video_gfx *out_gfx = (struct video_gfx *)cookie;
	video_gfx_fill(out_gfx,
	               video_rect_getxmin(intersect), video_rect_getymin(intersect),
	               video_rect_getxdim(intersect), video_rect_getydim(intersect),
	               VIDEO_COLOR_RGBA(0, 0, 0, 0));
	return 0;
}

/* Render RGBA overlay data */
INTERN ATTR_INOUT(1) ATTR_IN(2) ATTR_IN(3) ATTR_INOUT(4) void CC
local_compositor_render_rgba_overlay_above(struct local_compositor *__restrict self,
                                           struct local_window *__restrict start,
                                           struct video_rect const *screen_rect,
                                           struct video_gfx *out,
                                           bool make_nohit_transparent) {
	local_compositor_foreach_above(self, start, screen_rect, &local_compositor_render_rgba_overlay_above_foreach_cb,
	                               make_nohit_transparent ? &local_compositor_render_rgba_overlay_above_nohit_cb
	                                                      : NULL,
	                               out);
}


PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_mask_overlay_above_foreach_cb(void *cookie, struct local_window *window,
                                                      struct video_rect const *intersect) {
	struct video_gfx *out_gfx = (struct video_gfx *)cookie;
	video_color_t color;
	if (window->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA) {
		color = ALPHAMASK_1; /* Render via RGBA mask (must set bitmask to 1 so render can happen at all) */
	} else {
		color = ALPHAMASK_0; /* Obstructed pixels -- don't render */
	}
	video_gfx_fill(out_gfx,
	               video_rect_getxmin(intersect),
	               video_rect_getymin(intersect),
	               video_rect_getxdim(intersect),
	               video_rect_getydim(intersect),
	               color);
	return 0;
}

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_mask_overlay_above_nohit_cb(void *cookie,
                                                    struct local_compositor *UNUSED(comp),
                                                    struct video_rect const *intersect) {
	struct video_gfx *out_gfx = (struct video_gfx *)cookie;
	video_gfx_fill(out_gfx, /* unobstructed pixels -- always render */
	               video_rect_getxmin(intersect), video_rect_getymin(intersect),
	               video_rect_getxdim(intersect), video_rect_getydim(intersect),
	               ALPHAMASK_1);
	return 0;
}



/* Render MASK overlay data */
INTERN ATTR_INOUT(1) ATTR_IN(2) ATTR_IN(3) ATTR_INOUT(4) void CC
local_compositor_render_mask_overlay_above(struct local_compositor *__restrict self,
                                           struct local_window *__restrict start,
                                           struct video_rect const *screen_rect,
                                           struct video_gfx *out,
                                           bool make_nohit_alphamask_1) {
	local_compositor_foreach_above(self, start, screen_rect, &local_compositor_render_mask_overlay_above_foreach_cb,
	                               make_nohit_alphamask_1 ? &local_compositor_render_mask_overlay_above_nohit_cb
	                                                      : NULL,
	                               out);
}

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_mask_overlay_above_nohit_only_foreach_cb(void *UNUSED(cookie),
                                                                 struct local_window *UNUSED(window),
                                                                 struct video_rect const *UNUSED(intersect)) {
	return 0;
}

/* Same as `local_compositor_render_mask_overlay_above(..., true)', but **ONLY** render nohit as 1-bits */
INTERN ATTR_INOUT(1) ATTR_IN(2) ATTR_IN(3) ATTR_INOUT(4) void CC
local_compositor_render_mask_overlay_above_nohit_only(struct local_compositor *__restrict self,
                                                      struct local_window *__restrict start,
                                                      struct video_rect const *screen_rect,
                                                      struct video_gfx *out) {
	local_compositor_foreach_above(self, start, screen_rect,
	                               &local_compositor_render_mask_overlay_above_nohit_only_foreach_cb,
	                               &local_compositor_render_mask_overlay_above_nohit_cb,
	                               out);
}




/************************************************************************/
/* PUBLIC COMPOSITOR API                                                */
/************************************************************************/

INTERN ATTR_INOUT(1) void CC
local_compositor_destroy(struct video_compositor *__restrict self) {
	struct local_compositor *me = video_compositor_aslocal(self);
	assert(me->vcp_ops == &local_compositor_ops);
	assert(me->lc_buffer);
	assert(LIST_EMPTY(&me->lc_passthru));
	assert(TAILQ_EMPTY(&me->lc_zorder));
	assert(TAILQ_EMPTY(&me->lc_zorder_visi));
	video_buffer_decref(me->lc_buffer);
	free(self);
}

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_update_overlay_counts_cb(void *cookie, struct local_window *window,
                                          struct video_rect const *UNUSED(intersect)) {
	struct local_window *me = (struct local_window *)cookie;
	if (window->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA) {
		++me->lw_overlay_rgba_allcount;
	} else {
		++me->lw_overlay_mask_allcount;
	}
	return 0;
}


PRIVATE ATTR_NOINLINE WUNUSED ATTR_INOUT(1) int CC
_local_window_ensure_not_passthru_impl(struct local_window *__restrict self) {
	struct local_compositor *comp = local_window_comp(self);
	REF struct video_buffer *oldbuf = self->lw_content;
	REF struct video_buffer *newbuf;
	struct video_gfx passthru_gfx;
	struct video_gfx distinct_gfx;
	assert(LIST_ISBOUND(self, lw_passthru));
	newbuf = video_domain_newbuffer(comp->lc_domain,
	                                video_rect_getxdim(&self->lw_attr.vwa_rect),
	                                video_rect_getydim(&self->lw_attr.vwa_rect),
	                                &comp->lc_nalpha_format,
	                                VIDEO_DOMAIN_NEWBUFFER_F_NORMAL);
	if unlikely(!newbuf)
		goto err;

	/* Copy video data from the old passthru buffer into the new, distinct buffer */
	video_buffer_getgfx(newbuf, &distinct_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	video_buffer_getgfx(oldbuf, &passthru_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	video_gfx_bitblit(&distinct_gfx, 0, 0,
	                  &passthru_gfx, 0, 0,
	                  video_gfx_getclipw(&passthru_gfx),
	                  video_gfx_getcliph(&passthru_gfx));

	/* Store the new buffer within the window. */
	self->lw_content = newbuf; /* Inherit reference (x2) */

	/* Revoke video access and drop old buffer */
	oldbuf = video_buffer_region_revoke(oldbuf);
	LIST_UNBIND(self, lw_passthru);
	video_buffer_decref(oldbuf);
	return 0;
err:
	return -1;
}

/* Ensure that `window' doesn't make use of a passthru buffer
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno'; probably `ENOMEM') */
PRIVATE WUNUSED ATTR_INOUT(1) int CC
local_window_ensure_not_passthru(struct local_window *__restrict self) {
	if (LIST_ISBOUND(self, lw_passthru))
		return _local_window_ensure_not_passthru_impl(self);
	return 0;
}


/* Increment "window->lw_overlay_rgba_allcount", returning `-1' on error */
PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_inc_overlay_rgba_cb(void *UNUSED(cookie),
                                     struct local_window *window,
                                     struct video_rect const *UNUSED(intersect)) {
	local_window_assert(window);
	if (window->lw_overlay_rgba_allcount == 0) {
		struct local_compositor *comp = local_window_comp(window);
		assert(!window->lw_overlay_rgba);
		window->lw_overlay_rgba = video_domain_newbuffer(comp->lc_domain,
		                                                 video_rect_getxdim(&window->lw_attr.vwa_rect),
		                                                 video_rect_getydim(&window->lw_attr.vwa_rect),
		                                                 &comp->lc_yalpha_format,
		                                                 VIDEO_DOMAIN_NEWBUFFER_F_CALLOC);
		if unlikely(!window->lw_overlay_rgba)
			goto err;
		if unlikely(local_window_ensure_not_passthru(window)) {
			video_buffer_decref(window->lw_overlay_rgba);
			window->lw_overlay_rgba = NULL;
			goto err;
		}
	}
	++window->lw_overlay_rgba_allcount;
	assert(!LIST_ISBOUND(window, lw_passthru));
	return 0;
err:
	return -1;
}

/* Decrement "window->lw_overlay_rgba_allcount" */
PRIVATE ATTR_INOUT(1) void CC
local_compositor_dec_overlay_rgba(struct local_window *__restrict window) {
	local_window_assert(window);
	assert(window->lw_overlay_rgba_allcount);
	if (!--window->lw_overlay_rgba_allcount) {
		REF struct video_buffer *buffer;
		buffer = window->lw_overlay_rgba;
		window->lw_overlay_rgba = NULL;
		video_buffer_decref(buffer);
	}
}


/* Rollback function for `local_compositor_inc_overlay_rgba_cb' */
PRIVATE NONNULL((2)) ATTR_IN(3) void CC
local_compositor_inc_overlay_rgba_rollback_cb(void *UNUSED(cookie), struct local_window *window,
                                              struct video_rect const *UNUSED(intersect)) {
	local_compositor_dec_overlay_rgba(window);
}


/* Increment "window->lw_overlay_mask_allcount", returning `-1' on error */
PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_inc_overlay_mask_cb(void *UNUSED(cookie),
                                     struct local_window *window,
                                     struct video_rect const *intersect) {
	struct video_gfx overlay_mask_gfx;
	local_window_assert(window);
	if (window->lw_overlay_mask_allcount == 0) {
		struct local_compositor *comp = local_window_comp(window);
		assert(!window->lw_overlay_mask);
		window->lw_overlay_mask = video_domain_newbuffer(comp->lc_domain,
		                                                 video_rect_getxdim(&window->lw_attr.vwa_rect),
		                                                 video_rect_getydim(&window->lw_attr.vwa_rect),
		                                                 &comp->lc_a1_format,
		                                                 VIDEO_DOMAIN_NEWBUFFER_F_NORMAL);
		if unlikely(!window->lw_overlay_mask)
			goto err;
		if unlikely(local_window_ensure_not_passthru(window)) {
			video_buffer_decref(window->lw_overlay_mask);
			window->lw_overlay_mask = NULL;
			goto err;
		}
		video_buffer_getgfx(window->lw_overlay_mask, &overlay_mask_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_fillall(&overlay_mask_gfx, ALPHAMASK_1); /* Unobstructed by default */
	} else {
		video_buffer_getgfx(window->lw_overlay_mask, &overlay_mask_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	}
	++window->lw_overlay_mask_allcount;
	assert(!LIST_ISBOUND(window, lw_passthru));

	/* Fill obstructed portion ob bitmask mask with 0-bits */
	video_gfx_fill(&overlay_mask_gfx,
	               video_rect_getxmin(intersect) - video_rect_getxmin(&window->lw_attr.vwa_rect),
	               video_rect_getymin(intersect) - video_rect_getymin(&window->lw_attr.vwa_rect),
	               video_rect_getxdim(intersect), video_rect_getydim(intersect), ALPHAMASK_0);
	return 0;
err:
	return -1;
}

/* Rollback function for `local_compositor_inc_overlay_mask_cb' */
PRIVATE NONNULL((2)) ATTR_IN(3) void CC
local_compositor_inc_overlay_mask_rollback_cb(void *cookie, struct local_window *window,
                                              struct video_rect const *intersect) {
	local_window_assert(window);
	assert(window->lw_overlay_mask_allcount);
	if (!--window->lw_overlay_mask_allcount) {
		REF struct video_buffer *buffer;
		buffer = window->lw_overlay_mask;
		window->lw_overlay_mask = NULL;
		video_buffer_decref(buffer);
	} else {
		/* Must update the overlay mask for the affected region:
		 * - There might be other windows that still intersect! */
		struct local_window *origin_window = (struct local_window *)cookie;
		struct local_compositor *comp = video_compositor_aslocal(window);
		struct video_gfx overlay_mask_gfx;
		struct local_window *above = TAILQ_NEXT(window, lw_zorder_visi);
		video_buffer_getgfx(window->lw_overlay_mask, &overlay_mask_gfx,
		                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_clip(&overlay_mask_gfx,
		               -video_rect_getxmin(intersect), -video_rect_getymin(intersect),
		               video_rect_getxmin(intersect) + video_gfx_getclipw(&overlay_mask_gfx),
		               video_rect_getymin(intersect) + video_gfx_getcliph(&overlay_mask_gfx));
		assertf(above, "If this were the case, then 'lw_overlay_mask_allcount' should be 0 at this point!");
		assert(TAILQ_ISBOUND(origin_window, lw_zorder_visi));
		TAILQ_REMOVE(&comp->lc_zorder_visi, origin_window, lw_zorder_visi); /* Render without this one! */
		local_compositor_render_mask_overlay_above_nohit_only(comp, above, intersect,
		                                                      &overlay_mask_gfx);

		/* For consistency: must re-insert "origin_window" (though it doesn't happen
		 * where we re-insert  it; our  caller will eventually  remove it  anyways). */
		TAILQ_INSERT_AFTER(&comp->lc_zorder_visi, window, origin_window, lw_zorder_visi);
	}
}


INTERN WUNUSED ATTR_INOUT(1) ATTR_IN(2) ATTR_IN_OPT(3) REF struct video_window *CC
local_compositor_newwindow(struct video_compositor *__restrict self,
                           struct video_window_position const *__restrict position,
                           struct video_gfx const *initial_content) {
	struct local_compositor *comp = video_compositor_aslocal(self);
	struct local_window *below, *above;
	struct local_window *below_visible, *above_visible;
	REF struct local_window *result;
	unsigned int content_alloc_flags;
	if ((position->vwp_attr.vwa_flags & ~VIDEO_WINDOW_F_ALL) ||
	    (video_rect_getxdim(&position->vwp_attr.vwa_rect) <= 0) ||
	    (video_rect_getydim(&position->vwp_attr.vwa_rect) <= 0)) {
		errno = EINVAL;
		return NULL;
	}
	local_compositor_wlock(comp);
	if (position->vwp_over == VIDEO_WINDOW_MOVE_OVER__UNCHANGED ||
	    position->vwp_over == VIDEO_WINDOW_MOVE_OVER__FOREGROUND) {
		below = TAILQ_LAST(&comp->lc_zorder);
		above = NULL;
	} else if (position->vwp_over == VIDEO_WINDOW_MOVE_OVER__BACKGROUND) {
		below = NULL;
		above = TAILQ_FIRST(&comp->lc_zorder);
	} else {
		below = local_window_fromwindow(position->vwp_over);
#ifndef NDEBUG
		{
			struct local_window *iter;
			bool exists = false;
			TAILQ_FOREACH (iter, &comp->lc_zorder, lw_zorder) {
				if (iter == below) {
					exists = true;
					break;
				}
			}
			assertf(exists, "Invalid window: %p", below);
		}
#endif /* !NDEBUG */
		above = TAILQ_NEXT(below, lw_zorder);
	}

	/* Allocate controller for resulting window */
	result = (struct local_window *)malloc(sizeof(struct local_window));
	if unlikely(!result)
		goto err_unlock;
	result->lw_attr = position->vwp_attr;

	/* Figure out the closest, visible windows */
	below_visible = NULL;
	above_visible = NULL;
	if (!(result->lw_attr.vwa_flags & VIDEO_WINDOW_F_HIDDEN)) {
		below_visible = below;
		above_visible = above;
		while (below_visible && !TAILQ_ISBOUND(below_visible, lw_zorder_visi))
			below_visible = TAILQ_PREV(below_visible, lw_zorder);
		while (above_visible && !TAILQ_ISBOUND(above_visible, lw_zorder_visi))
			above_visible = TAILQ_NEXT(above_visible, lw_zorder);
	}

	/* Allocate overlay buffers if needed */
	result->lw_overlay_rgba_allcount = 0;
	result->lw_overlay_mask_allcount = 0;
	result->lw_overlay_rgba = NULL;
	result->lw_overlay_mask = NULL;
	result->lw_overlay_rend = NULL;
	if (above_visible) {
		local_compositor_foreach_all_above(comp, above_visible, &result->lw_attr.vwa_rect,
		                                   &local_compositor_update_overlay_counts_cb,
		                                   NULL, result);

		/* Allocate required overlays */
		if (result->lw_overlay_rgba_allcount) {
			struct video_gfx overlay_rgba_gfx;
			result->lw_overlay_rgba = video_domain_newbuffer(comp->lc_domain,
			                                                 video_rect_getxdim(&result->lw_attr.vwa_rect),
			                                                 video_rect_getydim(&result->lw_attr.vwa_rect),
			                                                 &comp->lc_yalpha_format,
			                                                 VIDEO_DOMAIN_NEWBUFFER_F_CALLOC);
			if unlikely(!result->lw_overlay_rgba)
				goto err_unlock_r;

			/* Populate RGBA overlay */
			video_buffer_getgfx(result->lw_overlay_rgba, &overlay_rgba_gfx,
			                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
			video_gfx_clip(&overlay_rgba_gfx,
			               -video_rect_getxmin(&result->lw_attr.vwa_rect),
			               -video_rect_getymin(&result->lw_attr.vwa_rect),
			               video_rect_getxmin(&result->lw_attr.vwa_rect) + video_gfx_getclipw(&overlay_rgba_gfx),
			               video_rect_getymin(&result->lw_attr.vwa_rect) + video_gfx_getcliph(&overlay_rgba_gfx));
			local_compositor_render_rgba_overlay_above(comp, above_visible,
			                                           &result->lw_attr.vwa_rect,
			                                           &overlay_rgba_gfx, false);
		}
		if (result->lw_overlay_mask_allcount) {
			struct video_gfx overlay_mask_gfx;
			result->lw_overlay_mask = video_domain_newbuffer(comp->lc_domain,
			                                                 video_rect_getxdim(&result->lw_attr.vwa_rect),
			                                                 video_rect_getydim(&result->lw_attr.vwa_rect),
			                                                 &comp->lc_a1_format,
			                                                 VIDEO_DOMAIN_NEWBUFFER_F_NORMAL);
			if unlikely(!result->lw_overlay_mask)
				goto err_unlock_r_orgba;

			/* Populate MASK overlay */
			video_buffer_getgfx(result->lw_overlay_mask, &overlay_mask_gfx,
			                    GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
			video_gfx_clip(&overlay_mask_gfx,
			               -video_rect_getxmin(&result->lw_attr.vwa_rect),
			               -video_rect_getymin(&result->lw_attr.vwa_rect),
			               video_rect_getxmin(&result->lw_attr.vwa_rect) + video_gfx_getclipw(&overlay_mask_gfx),
			               video_rect_getymin(&result->lw_attr.vwa_rect) + video_gfx_getcliph(&overlay_mask_gfx));
			local_compositor_render_mask_overlay_above(comp, above_visible,
			                                           &result->lw_attr.vwa_rect,
			                                           &overlay_mask_gfx, true);

			if (result->lw_overlay_rgba) {
				result->lw_overlay_rend = video_domain_newbuffer(comp->lc_domain,
				                                                 video_rect_getxdim(&result->lw_attr.vwa_rect),
				                                                 video_rect_getydim(&result->lw_attr.vwa_rect),
				                                                 &comp->lc_nalpha_format,
				                                                 VIDEO_DOMAIN_NEWBUFFER_F_NORMAL);
				if unlikely(!result->lw_overlay_rend)
					goto err_unlock_r_orgba_omask;
			}
		}
	}

	/* Determine content allocation flags. */
	content_alloc_flags = VIDEO_DOMAIN_NEWBUFFER_F_CALLOC;
	if (initial_content)
		content_alloc_flags = VIDEO_DOMAIN_NEWBUFFER_F_NORMAL;

	/* Allocate the primary "lw_content", "lw_background" and "lw_display" and buffers */
	LIST_ENTRY_UNBOUND_INIT(&result->lw_passthru);
	if (result->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA) {
		/* Need all those pretty, little alpha buffers */
		result->lw_content = video_domain_newbuffer(comp->lc_domain,
		                                            video_rect_getxdim(&result->lw_attr.vwa_rect),
		                                            video_rect_getydim(&result->lw_attr.vwa_rect),
		                                            &comp->lc_yalpha_format, content_alloc_flags);
		if unlikely(!result->lw_content)
			goto err_unlock_r_overlay;
		result->lw_display = video_domain_newbuffer(comp->lc_domain,
		                                            video_rect_getxdim(&result->lw_attr.vwa_rect),
		                                            video_rect_getydim(&result->lw_attr.vwa_rect),
		                                            &comp->lc_nalpha_format, content_alloc_flags);
		if unlikely(!result->lw_display)
			goto err_unlock_r_overlay_content;
		result->lw_background = video_domain_newbuffer(comp->lc_domain,
		                                               video_rect_getxdim(&result->lw_attr.vwa_rect),
		                                               video_rect_getydim(&result->lw_attr.vwa_rect),
		                                               &comp->lc_nalpha_format,
		                                               VIDEO_DOMAIN_NEWBUFFER_F_NORMAL);
		if unlikely(!result->lw_background)
			goto err_unlock_r_overlay_content_display;
	} else {
		result->lw_background = NULL;
		result->lw_display    = NULL;
		if ((result->lw_attr.vwa_flags & (VIDEO_WINDOW_F_PASSTHRU | VIDEO_WINDOW_F_HIDDEN)) == VIDEO_WINDOW_F_PASSTHRU &&
		    (comp->lc_features & VIDEO_COMPOSITOR_FEAT_PASSTHRU) &&
		    (result->lw_overlay_rgba_allcount == 0) &&
		    (result->lw_overlay_mask_allcount == 0)) {
			/* Use a passthru buffer */
			REF struct video_buffer *content;
			content = video_buffer_region_revocable(comp->lc_buffer, &result->lw_attr.vwa_rect);
			if unlikely(!content)
				goto err_unlock_r_overlay;
			result->lw_content = content;
			LIST_INSERT_HEAD(&comp->lc_passthru, result, lw_passthru);
		} else {
			/* Use a regular non-alpha buffer */
			REF struct video_buffer *content;
			content = video_domain_newbuffer(comp->lc_domain,
			                                 video_rect_getxdim(&result->lw_attr.vwa_rect),
			                                 video_rect_getydim(&result->lw_attr.vwa_rect),
			                                 &comp->lc_nalpha_format, content_alloc_flags);
			if unlikely(!content)
				goto err_unlock_r_overlay;
			result->lw_content = content;
		}
	}

	/* Fill in remaining (control) fields */
	result->vd_domain = comp->lc_domain;
	result->vd_ops    = &_local_window_ops()->vwo_display;
	result->vd_refcnt = 1;
	result->vw_compositor = comp; /* reference is created later... */

	/* Insert "result" into the Z-order */
	if (below) {
		TAILQ_INSERT_AFTER(&comp->lc_zorder, below, result, lw_zorder);
	} else {
		TAILQ_INSERT_HEAD(&comp->lc_zorder, result, lw_zorder);
	}

	/* Insert "result" into the Z-order-visible */
	if (!(result->lw_attr.vwa_flags & VIDEO_WINDOW_F_HIDDEN)) {
		if (above_visible) {
			TAILQ_INSERT_BEFORE(above_visible, result, lw_zorder_visi);
		} else if (below_visible) {
			TAILQ_INSERT_AFTER(&comp->lc_zorder_visi, below_visible, result, lw_zorder_visi);
		} else {
			assert(TAILQ_EMPTY(&comp->lc_zorder_visi));
			TAILQ_INSERT_TAIL(&comp->lc_zorder_visi, result, lw_zorder_visi);
		}
	} else {
		TAILQ_ENTRY_UNBOUND_INIT(&result->lw_zorder_visi);
	}

	/* If given, render the initial content of the window */
	if (initial_content) {
		struct video_gfx window_gfx;
		video_buffer_getgfx(result->lw_content, &window_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_stretch(&window_gfx, 0, 0, video_gfx_getclipw(&window_gfx), video_gfx_getcliph(&window_gfx),
		                  initial_content, 0, 0, video_gfx_getclipw(initial_content), video_gfx_getcliph(initial_content));
	}

	/* Update "lw_overlay_rgba_allcount" / "lw_overlay_mask_allcount" of all
	 * windows behind our, as well as allocate/update overlay buffers  where
	 * appropriate. */
	if (below_visible) {
		bool has_alpha = (result->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA) != 0;
		if (local_compositor_foreach_all_below(comp, below_visible, &result->lw_attr.vwa_rect,
		                                       has_alpha ? &local_compositor_inc_overlay_rgba_cb : local_compositor_inc_overlay_mask_cb,
		                                       has_alpha ? &local_compositor_inc_overlay_rgba_rollback_cb : local_compositor_inc_overlay_mask_rollback_cb,
		                                       result) < 0)
			goto err_unlock_r_overlay_contents_zorder;
	}

	/* Reference stored in "result->vw_compositor" */
	video_compositor_incref(comp);

	/* If appropriate, do an initial update and render the window to-screen */
	if (initial_content || !(result->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA)) {
		REF struct video_display *display;
		struct video_rect window_rect = result->lw_attr.vwa_rect;
		if (!LIST_ISBOUND(result, lw_passthru)) {
			/* NOTE: This will also propagate the initial content to overlays of windows underneath */
			local_window_updaterect_locked(result, &window_rect);
		} else if (!initial_content) {
			/* Set initial content to all-black */
			struct video_gfx content_gfx;
			video_buffer_getgfx(result->lw_content, &content_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
			video_gfx_fillall(&content_gfx, VIDEO_COLOR_RGB(0, 0, 0));
		}
		display = comp->lc_display;
		video_display_incref(display);
		local_compositor_wunlock(comp);
		video_display_updaterect(display, &window_rect);
		video_display_decref(display);
	} else {
		local_compositor_wunlock(comp);
	}
	return result;

err_unlock_r_overlay_contents_zorder:
	TAILQ_REMOVE(&comp->lc_zorder, result, lw_zorder);
	if (TAILQ_ISBOUND(result, lw_zorder_visi))
		TAILQ_UNBIND(&comp->lc_zorder_visi, result, lw_zorder_visi);
/*err_unlock_r_overlay_contents:*/
	if (LIST_ISBOUND(result, lw_passthru))
		LIST_UNBIND(result, lw_passthru);
/*err_unlock_r_overlay_content_display_background:*/
	if (result->lw_background)
		video_buffer_decref(result->lw_background);
err_unlock_r_overlay_content_display:
	if (result->lw_display)
		video_buffer_decref(result->lw_display);
err_unlock_r_overlay_content:
	video_buffer_decref(result->lw_content);
err_unlock_r_overlay:
/*err_unlock_r_orgba_omask_orend:*/
	if (result->lw_overlay_rend)
		video_buffer_decref(result->lw_overlay_rend);
err_unlock_r_orgba_omask:
	if (result->lw_overlay_mask)
		video_buffer_decref(result->lw_overlay_mask);
err_unlock_r_orgba:
	if (result->lw_overlay_rgba)
		video_buffer_decref(result->lw_overlay_rgba);
err_unlock_r:
	free(result);
err_unlock:
	local_compositor_wunlock(comp);
/*err:*/
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


PRIVATE ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct video_codec const *CC
add_alpha(struct video_codec const *__restrict codec) {
	video_codec_t id;
	if (codec->vc_specs.vcs_amask)
		return codec;
	switch (codec->vc_codec) {
	case VIDEO_CODEC_P1_MSB:
		id = VIDEO_CODEC_AP11_MSB;
		break;
	case VIDEO_CODEC_P1_LSB:
		id = VIDEO_CODEC_AP11_LSB;
		break;
	case VIDEO_CODEC_P2_MSB:
		id = VIDEO_CODEC_AP22_MSB;
		break;
	case VIDEO_CODEC_P2_LSB:
		id = VIDEO_CODEC_AP22_LSB;
		break;
	case VIDEO_CODEC_P4_MSB:
	case VIDEO_CODEC_P4_LSB:
		id = VIDEO_CODEC_AP44;
		break;
	case VIDEO_CODEC_P8:
		id = VIDEO_CODEC_AP88;
		break;
	case VIDEO_CODEC_L1_MSB:
		id = VIDEO_CODEC_AL11_MSB;
		break;
	case VIDEO_CODEC_L1_LSB:
		id = VIDEO_CODEC_AL11_LSB;
		break;
	case VIDEO_CODEC_L2_MSB:
		id = VIDEO_CODEC_AL22_MSB;
		break;
	case VIDEO_CODEC_L2_LSB:
		id = VIDEO_CODEC_AL22_LSB;
		break;
	case VIDEO_CODEC_L4_MSB:
	case VIDEO_CODEC_L4_LSB:
		id = VIDEO_CODEC_AL44;
		break;
	case VIDEO_CODEC_L8:
		id = VIDEO_CODEC_AP88;
		break;
	case VIDEO_CODEC_RGBX8888:
		id = VIDEO_CODEC_RGBA8888;
		break;
	case VIDEO_CODEC_BGRX8888:
		id = VIDEO_CODEC_BGRA8888;
		break;
	case VIDEO_CODEC_RGB888:
	case VIDEO_CODEC_XRGB8888:
		id = VIDEO_CODEC_ARGB8888;
		break;
	case VIDEO_CODEC_BGR888:
	case VIDEO_CODEC_XBGR8888:
		id = VIDEO_CODEC_ABGR8888;
		break;
	default:
		if (codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL) {
			id = VIDEO_CODEC_AP88;
		} else if (codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_LUM) {
			id = VIDEO_CODEC_AL88;
		} else {
			id = VIDEO_CODEC_RGBA8888;
		}
		break;
	}
	return video_codec_lookup(id);
}

PRIVATE ATTR_INOUT(1) void CC
local_compositor_updatebuffercaches(struct local_compositor *__restrict me) {
	struct video_buffer *buffer = me->lc_buffer;
	me->lc_domain                 = buffer->vb_domain;
	me->lc_nalpha_format.vf_codec = buffer->vb_format.vf_codec;
	me->lc_nalpha_format.vf_pal   = buffer->vb_format.vf_pal;
	me->lc_yalpha_format.vf_codec = add_alpha(buffer->vb_format.vf_codec);
	me->lc_yalpha_format.vf_pal   = buffer->vb_format.vf_pal;

	/* Generate new (pre-cached) GFX contexts */
	DBG_memset(&me->lc_buffer_gfx_write, 0xcc, sizeof(me->lc_buffer_gfx_write));
	DBG_memset(&me->lc_buffer_gfx_alpha, 0xcc, sizeof(me->lc_buffer_gfx_alpha));
	video_buffer_getgfx(buffer, &me->lc_buffer_gfx_write, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	video_buffer_getgfx(buffer, &me->lc_buffer_gfx_alpha, GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
}


/* @return: * :   The previously used buffer
 * @return: NULL: Error (s.a. `errno'; probably `ENOMEM') */
PRIVATE WUNUSED ATTR_INOUT(1) REF struct video_buffer *CC
local_compositor_setbuffer_locked(struct local_compositor *__restrict me,
                                  struct video_buffer *__restrict new_buffer) {
	REF struct video_buffer *old_buffer;

	/* Check for simple case: buffer doesn't actually change */
	if unlikely(new_buffer == me->lc_buffer) {
		video_buffer_incref(new_buffer);
		return new_buffer;
	}

	/* XXX: If the video codec or palette changes, create new video buffers for all windows? */

	/* Must allocate new passthru buffers for all windows that are passthru right now. */
	if (!LIST_EMPTY(&me->lc_passthru)) {
		struct local_window *pt_window;
		LIST_FOREACH (pt_window, &me->lc_passthru, lw_passthru) {
			REF struct video_buffer *new_passthru;
			assert(LIST_ISBOUND(pt_window, lw_passthru));
			local_window_assert(pt_window);
			new_passthru = video_buffer_region_revocable(new_buffer, &pt_window->lw_attr.vwa_rect);
			if unlikely(!new_passthru) {
				struct local_window *rollback;
				/* Rollback already-allocated (new) passthru buffers */
				LIST_FOREACH (rollback, &me->lc_passthru, lw_passthru) {
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
		LIST_FOREACH (pt_window, &me->lc_passthru, lw_passthru) {
			struct video_buffer *obuffer, *nbuffer;
			struct video_gfx ogfx, ngfx;
			assert(LIST_ISBOUND(pt_window, lw_passthru));
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
	local_compositor_updatebuffercaches(me);

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
	old_buffer = local_compositor_setbuffer_locked(me, new_buffer);

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
		status = local_compositor_setbuffer_locked(me, new_buffer);
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
			assert(LIST_EMPTY(&me->lc_passthru));
		} else {
			/* Disable passthru */
			disable_passthru = !LIST_EMPTY(&me->lc_passthru);
		}
	}

	/* Perform actions... */
	if (disable_passthru) {
		struct local_window *pt_window;
		LIST_FOREACH (pt_window, &me->lc_passthru, lw_passthru) {
			REF struct video_buffer *newbuf;
			assert(LIST_ISBOUND(pt_window, lw_passthru));
			local_window_assert(pt_window);
			assert(!pt_window->lw_display); /* Temporarily store new video buffers here */
			newbuf = video_domain_newbuffer(me->lc_domain,
			                                video_rect_getxdim(&pt_window->lw_attr.vwa_rect),
			                                video_rect_getydim(&pt_window->lw_attr.vwa_rect),
			                                &me->lc_nalpha_format,
			                                VIDEO_DOMAIN_NEWBUFFER_F_NORMAL);
			if unlikely(!newbuf) {
				struct local_window *rollback;
				LIST_FOREACH (rollback, &me->lc_passthru, lw_passthru) {
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
		LIST_FOREACH_SAFE (pt_window, &me->lc_passthru, lw_passthru) {
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
			obuffer = video_buffer_region_revoke(obuffer);
			video_buffer_decref(obuffer);
			LIST_UNBIND(pt_window, lw_passthru);
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




PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
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

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
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
			                               &screen_gfx);
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




/* Create a new video compositor  for `display'. The compositor  returned
 * by this function will run in the caller's process, meaning it does not
 * impose any `EPERM'-like restrictions.
 * @return: * :   The newly created compositor
 * @return: NULL: [errno=ENOMEM] Out of memory */
DEFINE_PUBLIC_ALIAS(video_compositor_create, libvideo_compositor_create);
INTERN WUNUSED ATTR_INOUT(1) REF struct video_compositor *CC
libvideo_compositor_create(struct video_display *__restrict display,
                           video_compositor_feature_t features,
                           video_color_t background) {
	REF struct local_compositor *result;
	REF struct video_buffer *buffer;
	if (features & ~VIDEO_COMPOSITOR_FEAT_ALL) {
		errno = EINVAL;
		goto err;
	}

	buffer = video_display_getbuffer(display);
	if unlikely(!buffer)
		goto err;
	result = (REF struct local_compositor *)malloc(sizeof(struct local_compositor));
	if unlikely(!result)
		goto err_buffer;
	result->lc_a1_format.vf_pal = NULL;
	result->lc_a1_format.vf_codec = video_codec_lookup(VIDEO_CODEC_A1_MSB);
	if unlikely(!result->lc_a1_format.vf_codec) {
		errno = ENODEV;
		goto err_buffer;
	}

	result->vcp_ops = _local_compositor_ops();
	result->vcp_refcnt = 1;
	shared_rwlock_init(&result->lc_lock);
	result->lc_display = display;
	video_display_incref(display);
	result->lc_buffer = buffer; /* Inherit reference */
	local_compositor_updatebuffercaches(result);
	LIST_INIT(&result->lc_passthru);
	TAILQ_INIT(&result->lc_zorder);
	TAILQ_INIT(&result->lc_zorder_visi);
	result->lc_background = background;
	result->lc_features = features;
	return result;
err_buffer:
	video_buffer_decref(buffer);
err:
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_COMPOSITOR_COMPOSITOR_C */
