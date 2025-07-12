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
#include <malloc.h>
#include <minmax.h>
#include <string.h>

#include <libvideo/codec/rectutils.h>
#include <libvideo/compositor/compositor.h>
#include <libvideo/gfx/blend.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/gfx.h>

#include "compositor.h"

DECL_BEGIN

#ifndef NDEBUG

PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_window_assert_foreach_cb(void *cookie, struct local_window *window,
                               struct video_rect const *UNUSED(intersect)) {
	unsigned int *flags = (unsigned int *)cookie;
	if (window->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA) {
		*flags |= 1;
	} else {
		*flags |= 2;
	}
	return 0;
}

PRIVATE NONNULL((1)) void LIBVIDEO_GFX_CC
local_window_assert(struct local_window *__restrict me) {
	assert(TAILQ_ISBOUND(me, lw_zorder));
	assert((me->lw_overlay_rgba != NULL) == (me->lw_overlay_rgba_allcount != 0));
	assert((me->lw_overlay_mask != NULL) == (me->lw_overlay_mask_allcount != 0));
	assertf(me->lw_content, "Content buffer must always be allocated");
	if (me->lw_attr.vwa_flags & VIDEO_WINDOW_F_HIDDEN) {
		assertf(!TAILQ_ISBOUND(me, lw_zorder_visi), "Hidden windows can't be in visible Z-order list");
		assertf(!TAILQ_ISBOUND(me, lw_passthru), "Hidden windows can't use passthru buffers");
		assertf(!me->lw_overlay_rgba, "RGBA overlay not needed for hidden window");
		assertf(!me->lw_overlay_mask, "MASK overlay not needed for hidden window");
		assertf(!me->lw_background, "Background buffer isn't needed by hidden window");
		assertf(!me->lw_display, "Display buffer isn't needed by hidden window");
	} else {
		unsigned int above_hits;
		assertf(TAILQ_ISBOUND(me, lw_zorder_visi), "Visible window must be part of visible Z-order list");
		if (me->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA) {
			assert(me->lw_background);
			assert(me->lw_display);
		} else {
			assert(!me->lw_background);
			assert(!me->lw_display);
		}
		assert(TAILQ_ISBOUND(me, lw_zorder_visi));
		above_hits = 0;
		local_compositor_foreach_all_above(local_window_comp(me),
		                                   TAILQ_NEXT(me, lw_zorder_visi),
		                                   &me->lw_attr.vwa_rect,
		                                   &local_window_assert_foreach_cb,
		                                   &above_hits);
		if (above_hits & 1) {
			assertf(me->lw_overlay_rgba, "window has alpha-window above -> need RGBA overlay");
		} else {
			assertf(!me->lw_overlay_rgba, "window has no alpha-window above -> RGBA overlay not needed");
		}
		if (above_hits & 2) {
			assertf(me->lw_overlay_mask, "window has opaque-window above -> need MASK overlay");
		} else {
			assertf(!me->lw_overlay_mask, "window has no opaque-window above -> MASK overlay not needed");
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
	if (dst->lw_overlay_rgba && dst->lw_overlay_rgba_allcount > 1) {
		/* Copy from "dst->lw_overlay_rgba ?? comp->lc_buffer" to "dst->lw_overlay_rgba" */
		struct video_gfx dst_gfx, src_gfx;
		struct video_buffer *src_overlay = src->lw_overlay_rgba;
		if (src_overlay == NULL) {
			src_overlay = comp->lc_buffer;
			src_x = screen_region->vr_xmin;
			src_y = screen_region->vr_ymin;
		}
		video_buffer_getgfx(dst->lw_overlay_rgba, &dst_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(src_overlay, &src_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit(&dst_gfx, dst_x, dst_y,
		                  &src_gfx, src_x, src_y,
		                  screen_region->vr_xdim,
		                  screen_region->vr_ydim);
	}

	/* Copy MASK overlay data */
	if (dst->lw_overlay_mask && dst->lw_overlay_mask_allcount > 1) {
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
 * - Allocation of a passthru buffer failed
 */
PRIVATE ATTR_INOUT(1) void CC
try_convert_window_to_passthru(struct local_window *__restrict self) {
	(void)self;
	/* TODO */
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
		try_convert_window_to_passthru(window);
	}
	return 0;
}


/* Simply draw the intersection of "me" and "screen_rect" to screen. */
PRIVATE ATTR_INOUT(1) ATTR_IN(2) void CC
local_window_draw_rect_to_screen(struct local_window *me,
                                 struct video_rect const *screen_rect) {
	struct video_gfx screen_gfx, dst_gfx, src_gfx;
	struct local_compositor *comp = local_window_comp(me);
	video_offset_t rel_x = screen_rect->vr_xmin - me->lw_attr.vwa_rect.vr_xmin;
	video_offset_t rel_y = screen_rect->vr_ymin - me->lw_attr.vwa_rect.vr_ymin;
	if (me->lw_overlay_rgba) {
		video_buffer_getgfx(me->lw_overlay_rgba, &dst_gfx, GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(comp->lc_buffer, &screen_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		if (me->lw_overlay_mask) {
			/* Update overlay buffer using screen data of masked area */
			struct video_gfx mask_gfx;
			video_buffer_getgfx(me->lw_overlay_mask, &mask_gfx, GFX_BLENDMODE_ONE_MINUS_ALPHAMASK, VIDEO_GFX_F_NORMAL, 0);
			video_gfx_bitblit3(&dst_gfx, rel_x, rel_y,
			                   &mask_gfx, rel_x, rel_y,
			                   &screen_gfx, /* Use screen as source */
			                   screen_rect->vr_xmin, screen_rect->vr_ymin,
			                   screen_rect->vr_xdim, screen_rect->vr_ydim);
		}
		video_gfx_bitblit3(&screen_gfx,
		                   screen_rect->vr_xmin, screen_rect->vr_ymin,
		                   &dst_gfx, rel_x, rel_y,
		                   &src_gfx, rel_x, rel_y,
		                   screen_rect->vr_xdim, screen_rect->vr_ydim);
	} else if (me->lw_overlay_mask) {
		video_buffer_getgfx(comp->lc_buffer, &screen_gfx, GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(me->lw_overlay_mask, &dst_gfx, GFX_BLENDMODE_ALPHAMASK, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&screen_gfx, screen_rect->vr_xmin, screen_rect->vr_ymin,
		                   &dst_gfx, rel_x, rel_y,
		                   &src_gfx, rel_x, rel_y,
		                   screen_rect->vr_xdim, screen_rect->vr_ydim);
	} else {
		video_buffer_getgfx(comp->lc_buffer, &screen_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit(&screen_gfx, screen_rect->vr_xmin, screen_rect->vr_ymin,
		                   &src_gfx, rel_x, rel_y,
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
			                               NULL, &inner_data);
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
	local_compositor_updaterect(comp, intersect);
	return 0;
}

/* Hide a video window.
 * NOTE: The caller is  responsible for revoking  passthru display  access
 *       and (in case pixel data of "lw_content" should be saved), copying
 *       pixel  data from "lw_content" into a separate buffer (so it isn't
 *       being shared with the compositor's output).
 * NOTE: The caller must also set the "VIDEO_WINDOW_F_HIDDEN" flag */
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
		                               NULL, me);
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
		local_compositor_foreach_above(comp, below, &me->lw_attr.vwa_rect,
		                               &local_window_hide__locked_above_cb,
		                               &local_window_hide__locked_above_nohit_cb, &data);
	} else {
		local_compositor_updaterect(comp, &me->lw_attr.vwa_rect);
	}

	/* Free buffers not needed for hidden windows */
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
			/* TODO: cause any future GFX to no-op, and any locks to fail
			 * NOTE: Only really need this for video buffers created by `video_buffer_fromgfx()' */
//			video_buffer_revoke(me->lw_content);
			TAILQ_UNBIND(&comp->lc_passthru, me, lw_passthru);
		}
		local_window_hide__locked(me);
	}
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
                                  struct video_rect const *intersect) {
	struct video_gfx *src_gfx = (struct video_gfx *)cookie;
	assert((window->lw_background != NULL) == (window->lw_display != NULL));
	if (window->lw_background) {
		struct video_gfx background_gfx;
		struct video_gfx display_gfx;
		struct video_gfx content_gfx;
		video_offset_t rel_x = intersect->vr_xmin - window->lw_attr.vwa_rect.vr_xmin;
		video_offset_t rel_y = intersect->vr_ymin - window->lw_attr.vwa_rect.vr_ymin;
		struct local_compositor *comp = local_window_comp(window);
		struct local_window *above;

		/* Update background buffer of window */
		video_buffer_getgfx(window->lw_background, &background_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit(&background_gfx, rel_x, rel_y, src_gfx,
		                  intersect->vr_xmin, intersect->vr_ymin,
		                  intersect->vr_xdim, intersect->vr_ydim);

		/* Update display buffer of window */
		video_gfx_setblend(&background_gfx, GFX_BLENDMODE_ALPHA);
		video_buffer_getgfx(window->lw_display, &display_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(window->lw_content, &content_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&display_gfx, rel_x, rel_y,
		                   &background_gfx, rel_x, rel_y,
		                   &content_gfx, rel_x, rel_y,
		                   intersect->vr_xdim, intersect->vr_ydim);

		/* Recursively update background buffers of other windows in-front of this one */
		above = TAILQ_NEXT(window, lw_zorder_visi);
		if (above) {
			video_gfx_clip(&display_gfx,
			               -window->lw_attr.vwa_rect.vr_xmin,
			               -window->lw_attr.vwa_rect.vr_ymin,
			               window->lw_attr.vwa_rect.vr_xmin + video_gfx_getclipw(&display_gfx),
			               window->lw_attr.vwa_rect.vr_ymin + video_gfx_getcliph(&display_gfx));
			local_compositor_foreach_above(comp, above, intersect,
			                               &local_window_update_background_cb,
			                               NULL, &display_gfx);
		}
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
				                               NULL, &inner_data);
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
	struct video_gfx src_gfx, dst_gfx, out_gfx;
	struct video_rect screen_rect;
	local_compositor_rlock(comp);
	local_window_assert(me);

	/* If our window uses a pass-thru buffer, then we don't have to do anything. */
	if (TAILQ_ISBOUND(me, lw_passthru))
		goto done;

	assert((me->lw_background != NULL) == (me->lw_display != NULL));
	video_buffer_getgfx(me->lw_content, &src_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	if (me->lw_background) {
		video_buffer_getgfx(me->lw_background, &dst_gfx, GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(me->lw_display, &out_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&out_gfx, rect->vr_xmin, rect->vr_ymin,
		                   &dst_gfx, rect->vr_xmin, rect->vr_ymin,
		                   &src_gfx, rect->vr_xmin, rect->vr_ymin,
		                   rect->vr_xdim, rect->vr_ydim);
		src_gfx = out_gfx;
	}

	screen_rect.vr_xmin = me->lw_attr.vwa_rect.vr_xmin + rect->vr_xmin;
	screen_rect.vr_ymin = me->lw_attr.vwa_rect.vr_ymin + rect->vr_ymin;
	screen_rect.vr_xdim = rect->vr_xdim;
	screen_rect.vr_ydim = rect->vr_ydim;
	if (me->lw_overlay_rgba) {
		struct local_window *above;
		video_buffer_getgfx(me->lw_overlay_rgba, &dst_gfx, GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(comp->lc_buffer, &out_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		if (me->lw_overlay_mask) {
			/* Update overlay buffer using screen data of masked area */
			struct video_gfx mask_gfx;
			video_buffer_getgfx(me->lw_overlay_mask, &mask_gfx, GFX_BLENDMODE_ONE_MINUS_ALPHAMASK, VIDEO_GFX_F_NORMAL, 0);
			video_gfx_bitblit3(&dst_gfx, rect->vr_xmin, rect->vr_ymin,
			                   &mask_gfx, rect->vr_xmin, rect->vr_ymin,
			                   &out_gfx, /* Use screen as source */
			                   screen_rect.vr_xmin, screen_rect.vr_ymin,
			                   screen_rect.vr_xdim, screen_rect.vr_ydim);
		}
		video_gfx_bitblit3(&out_gfx,
		                   screen_rect.vr_xmin, screen_rect.vr_ymin,
		                   &dst_gfx, rect->vr_xmin, rect->vr_ymin,
		                   &src_gfx, rect->vr_xmin, rect->vr_ymin,
		                   screen_rect.vr_xdim, screen_rect.vr_ydim);

		/* Must also update the background buffers of windows above */
		above = TAILQ_NEXT(me, lw_zorder_visi);
		if (above) {
			video_gfx_clip(&src_gfx,
			               -me->lw_attr.vwa_rect.vr_xmin,
			               -me->lw_attr.vwa_rect.vr_ymin,
			               me->lw_attr.vwa_rect.vr_xmin + video_gfx_getclipw(&src_gfx),
			               me->lw_attr.vwa_rect.vr_ymin + video_gfx_getcliph(&src_gfx));
			local_compositor_foreach_above(comp, above, &screen_rect,
			                               &local_window_update_background_cb,
			                               NULL, &src_gfx);
		}
	} else if (me->lw_overlay_mask) {
		video_buffer_getgfx(comp->lc_buffer, &out_gfx, GFX_BLENDMODE_ALPHA, VIDEO_GFX_F_NORMAL, 0);
		video_buffer_getgfx(me->lw_overlay_mask, &dst_gfx, GFX_BLENDMODE_ALPHAMASK, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit3(&out_gfx,
		                   screen_rect.vr_xmin,
		                   screen_rect.vr_ymin,
		                   &dst_gfx, rect->vr_xmin, rect->vr_ymin,
		                   &src_gfx, rect->vr_xmin, rect->vr_ymin,
		                   screen_rect.vr_xdim, screen_rect.vr_ydim);
	} else {
		video_buffer_getgfx(comp->lc_buffer, &out_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
		video_gfx_bitblit(&out_gfx,
		                   screen_rect.vr_xmin,
		                   screen_rect.vr_ymin,
		                   &src_gfx, rect->vr_xmin, rect->vr_ymin,
		                   screen_rect.vr_xdim, screen_rect.vr_ydim);
		if (!(me->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA))
			try_convert_window_to_passthru(me);
	}

	/* Must also update the overlay buffers of windows below when our window has an alpha-channel */
	if (me->lw_attr.vwa_flags & VIDEO_WINDOW_F_ALPHA) {
		struct local_window *below = TAILQ_PREV(me, lw_zorder_visi);
		if (below) {
			struct local_window_update_overlay_data data;
			data.lwuod_above_overlay = NULL;
			if (me->lw_overlay_rgba) {
				assert(dst_gfx.vx_buffer == me->lw_overlay_rgba);
				video_gfx_clip(&dst_gfx,
				               -me->lw_attr.vwa_rect.vr_xmin,
				               -me->lw_attr.vwa_rect.vr_ymin,
				               me->lw_attr.vwa_rect.vr_xmin + video_gfx_getclipw(&dst_gfx),
				               me->lw_attr.vwa_rect.vr_ymin + video_gfx_getcliph(&dst_gfx));
				data.lwuod_above_overlay = &dst_gfx;
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
			                               NULL, &data);
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
	assert(rect->vr_xdim);
	assert(rect->vr_ydim);
	for (iter = start; (iter = (*next)(iter)) != NULL;)
		++window_rect_count;
	stack = (struct video_rect *)malloc((window_rect_count * 3 + 1),
	                                    sizeof(struct video_rect));
	if likely(stack) {
		/* "Fast" O(N^2) case: use a buffer of deleted rects
		 * TODO: This can be made faster if windows were stored in a BSP tree */
		size_t stacksz = 1;
		stack[0] = *rect;
		do {
			size_t i;
			assert(stacksz);
			i = stacksz;
			do {
				struct video_rect intersection;
				--i;
				if (video_rect_intersect(&stack[i], &start->lw_attr.vwa_rect, &intersection)) {
					struct video_rect orig;
					temp = (*cb)(cookie, start, &intersection);
					if unlikely(temp < 0) {
						result = temp;
						goto done_stack;
					}
					result += temp;

					/* Update stack of intersecting rects */
					orig = stack[i];
					--stacksz;
					stacksz += video_rect_subtract(&orig, &intersection, &stack[i]);
				}
			} while (i);
			if (!stacksz)
				goto done_stack;
		} while ((start = (*next)(start)) != NULL);
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
				if unlikely(temp < 0)
					return temp;
				result += temp;
				if (x >= rect->vr_xdim)
					break;
			}
		} while (++y < rect->vr_ydim);
	}
	return result;
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) struct local_window *CC
local_window_visi_above(struct local_window *__restrict window) {
	return TAILQ_NEXT(window, lw_zorder_visi);
}

PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) struct local_window *CC
local_window_visi_below(struct local_window *__restrict window) {
	return TAILQ_PREV(window, lw_zorder_visi);
}

INTERN ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_above(struct local_compositor *__restrict self,
                               struct local_window *__restrict start,
                               struct video_rect const *rect,
                               local_compositor_foreach_cb_t cb,          /* [1..1] */
                               local_compositor_foreach_nohit_cb_t nohit, /* [0..1] */
                               void *cookie) {
	return local_compositor_foreach_impl(self, start, rect, cb, nohit, cookie,
	                                     &local_window_visi_above);
}

/* Same as "local_compositor_foreach_above", but cast rays towards Z=0 */
INTERN ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) NONNULL((4)) ssize_t CC
local_compositor_foreach_below(struct local_compositor *__restrict self,
                               struct local_window *__restrict start,
                               struct video_rect const *rect,
                               local_compositor_foreach_cb_t cb,          /* [1..1] */
                               local_compositor_foreach_nohit_cb_t nohit, /* [0..1] */
                               void *cookie) {
	return local_compositor_foreach_impl(self, start, rect, cb, nohit, cookie,
	                                     &local_window_visi_below);
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
local_compositor_updaterect(struct local_compositor *__restrict self,
                            struct video_rect const *screen_rect) {
	struct video_gfx out_gfx;
	struct local_window *last = TAILQ_LAST(&self->lc_zorder_visi);
	video_buffer_getgfx(self->lc_buffer, &out_gfx, GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	if likely(last) {
		local_compositor_render_behind(self, last, screen_rect, &out_gfx);
	} else {
		video_gfx_fill(&out_gfx, screen_rect->vr_xmin, screen_rect->vr_ymin,
		               screen_rect->vr_xdim, screen_rect->vr_ydim,
		               self->lc_background);
	}
}







PRIVATE NONNULL((2)) ATTR_IN(3) ssize_t CC
local_compositor_render_foreach_cb(void *cookie, struct local_window *window,
                                   struct video_rect const *intersect) {
	struct video_gfx *out = (struct video_gfx *)cookie;
	struct video_buffer *src = window->lw_display ? window->lw_display : window->lw_content;
	struct video_gfx src_gfx;
	video_offset_t rel_x = intersect->vr_xmin - window->lw_attr.vwa_rect.vr_xmin;
	video_offset_t rel_y = intersect->vr_ymin - window->lw_attr.vwa_rect.vr_ymin;
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
	                               out);
}


DECL_END

#endif /* !GUARD_LIBVIDEO_COMPOSITOR_COMPOSITOR_C */
