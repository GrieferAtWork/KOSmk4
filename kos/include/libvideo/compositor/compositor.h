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
#ifndef _LIBVIDEO_COMPOSITOR_COMPOSITOR_H
#define _LIBVIDEO_COMPOSITOR_COMPOSITOR_H 1

#include "api.h"

#include <__stdinc.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/refcnt.h>

#include <libvideo/gfx/display.h>

#include "../color.h"
#include "../rect.h"
#include "../types.h"

__DECL_BEGIN

/* Possible values for `video_window_flag_t' */
#define VIDEO_WINDOW_F_NORMAL   0x0000
#define VIDEO_WINDOW_F_ALPHA    0x0001 /* Enable support for alpha-blending in windows.
                                        * - When set, `VIDEO_WINDOW_F_PASSTHRU' is ignored
                                        * - When set, buffer returned by `video_window_getbuffer' has alpha-support */
#define VIDEO_WINDOW_F_PASSTHRU 0x0002 /* Enable support for video_buffer passthru (when possible) */
/* TODO: "VIDEO_WINDOW_F_PASSTHRU" should be the default -- disallow should be its own flag */
#define VIDEO_WINDOW_F_HIDDEN   0x0004 /* Window is being hidden right now */
#define VIDEO_WINDOW_F_ALL (VIDEO_WINDOW_F_ALPHA | VIDEO_WINDOW_F_PASSTHRU | VIDEO_WINDOW_F_HIDDEN)


/* Possible values for `video_compositor_feature_t' */
#define VIDEO_COMPOSITOR_FEAT_NORMAL   0x0000
#define VIDEO_COMPOSITOR_FEAT_PASSTHRU VIDEO_WINDOW_F_PASSTHRU /* Enable support for video_buffer passthru (when possible) */
#define VIDEO_COMPOSITOR_FEAT_ALL (VIDEO_COMPOSITOR_FEAT_PASSTHRU)


#ifdef __CC__
typedef __uint32_t video_window_flag_t;
typedef __uint32_t video_compositor_feature_t;

struct video_window_ops;
struct video_window;
struct video_buffer;
struct video_compositor;
struct video_compositor_ops;

struct video_window_attr {
	struct video_rect   vwa_rect;  /* Window rect in compositor's buffer */
	video_window_flag_t vwa_flags; /* Window flags */
};

/* Special values for `video_window_position::vwp_over' */
#define VIDEO_WINDOW_MOVE_OVER__UNCHANGED  ((struct video_window *)0)  /* Leave unchanged (in `video_compositor_newwindow()', same as `VIDEO_WINDOW_MOVE_OVER__FOREGROUND') */
#define VIDEO_WINDOW_MOVE_OVER__FOREGROUND ((struct video_window *)-1) /* Place at the top of the Z-stack */
#define VIDEO_WINDOW_MOVE_OVER__BACKGROUND ((struct video_window *)-2) /* Place at the bottom of the Z-stack */
#define VIDEO_WINDOW_MOVE_OVER__FORWARD    ((struct video_window *)-3) /* Move window towards the front by 1 position */
#define VIDEO_WINDOW_MOVE_OVER__BACKWARD   ((struct video_window *)-4) /* Move window towards the back by 1 position */

struct video_window_position {
	struct video_window_attr vwp_attr; /* Window positioning and attributes */
	struct video_window     *vwp_over; /* Window that this one is placed over, or one of `VIDEO_WINDOW_MOVE_OVER__*' */
};

struct video_window_ops {
	struct video_display_ops vwo_display; /* Display operators */

	/* Get window attributes (position & flags)
	 * @return: 0 : Success
	 * @return: -1: Error (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_OUT_T(2) int
	(LIBVIDEO_COMPOSITOR_CC *vwo_getattr)(struct video_window *__restrict __self,
	                                      struct video_window_attr *__restrict __attr);

	/* Update parameters of the window within its compositor. A call to this
	 * function will probably require your to acquire a new buffer from  the
	 * underlying display, using `vwo_display.vdo_getbuffer'.
	 * @return: 0 : Success
	 * @return: -1: Error (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_IN_T(2) int
	(LIBVIDEO_COMPOSITOR_CC *vwo_setposition)(struct video_window *__restrict __self,
	                                          struct video_window_position const *__restrict __position);

	/* TODO: Expand with event handling functionality (User input, but also window events) */
};


#ifdef __INTELLISENSE__
/* Get window attributes (position & flags)
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) int
video_window_getattr(struct video_window *__restrict __self,
                     struct video_window_attr *__restrict __attr);

/* Update parameters of the window within its compositor. A call to this
 * function will probably require your to acquire a new buffer from  the
 * underlying display, using `vwo_display.vdo_getbuffer'.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN(2) int
video_window_setposition(struct video_window *__restrict __self,
                         struct video_window_position const *__restrict __position);

/* s.a. `video_display_getbuffer()' */
extern __ATTR_WUNUSED __ATTR_INOUT((1)) __REF struct video_buffer *
video_window_getbuffer(struct video_window *__restrict __self);

/* s.a. `video_display_updaterect()' */
extern __ATTR_INOUT(1) __ATTR_IN(2) void
video_window_updaterect(struct video_window *__restrict __self,
                        struct video_rect const *__restrict __rect);

/* s.a. `video_display_updaterects()' */
extern __ATTR_INOUT(1) __ATTR_INS(2, 3) void
video_window_updaterects(struct video_window *__restrict __self,
                         struct video_rect const *__restrict __rects,
                         __size_t __n_rects);

#else /* __INTELLISENSE__ */
#define video_window_getattr(self, attr)               (*_video_window_getops(self)->vwo_getattr)(self, attr)
#define video_window_setposition(self, position)       (*_video_window_getops(self)->vwo_setposition)(self, position)
#define video_window_getbuffer(self)                   video_display_getbuffer(video_window_asdisplay(self))
#define video_window_updaterect(self, rect)            video_display_updaterect(video_window_asdisplay(self), rect)
#define video_window_updaterects(self, rects, n_rects) video_display_updaterects(video_window_asdisplay(self), rects, n_rects)
#endif /* !__INTELLISENSE__ */


struct video_window
#ifdef __cplusplus
    : video_display
#define _video_window__vw_display /* nothing */
#define video_window_asdisplay    /* nothing */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct video_display vw_display;
#define _video_window__vw_display vw_display.
#define video_window_asdisplay(self) (&(self)->vw_display)
#endif /* __cplusplus */
	__REF struct video_compositor *vw_compositor; /* [1..1][const] Compositor  */
	/* Extra, compositor-specific fields go here... */
};
#define _video_window_getops(self) \
	((struct video_window_ops const *)(self)->_video_window__vw_display vd_ops)
#define video_window_destroy(self) video_display_destroy(video_window_asdisplay(self))
#define video_window_incref(self)  video_display_incref(video_window_asdisplay(self))
#define video_window_decref(self)  video_display_decref(video_window_asdisplay(self))


struct video_compositor_ops {
	/* Called when the compositor's reference counter hits "0" */
	__ATTR_INOUT_T(1) void
	(LIBVIDEO_COMPOSITOR_CC *vcpo_destroy)(struct video_compositor *__restrict __self);

	/* Create and return a new window
	 * @param: __initial_content: When  non-NULL, this GFX  is stretched to  the size of the
	 *                            produced window, and used to populate it with some initial
	 *                            content (in case  the window is  visible from the  start).
	 *                            When "NULL", the window's initial content is the  pre-init
	 *                            done by `video_buffer_create()'.
	 * @return: * :   The newly created window
	 * @return: NULL: Failed to create window (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_IN_T(2) __ATTR_IN_OPT_T(3) __REF struct video_window *
	(LIBVIDEO_COMPOSITOR_CC *vcpo_newwindow)(struct video_compositor *__restrict __self,
	                                         struct video_window_position const *__restrict __position,
	                                         struct video_gfx const *__initial_content);

	/* Returns a reference to the video display targeted by this compositor. */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __REF struct video_display *
	(LIBVIDEO_COMPOSITOR_CC *vcpo_getdisplay)(struct video_compositor *__restrict __self);

	/* Change the video display targeted by this compositor. This function may
	 * not be available for certain  compositors (namely: when talking to  the
	 * IPC compositor exposed by the window server).
	 *
	 * After a new display has been assigned, a full re-draw of all windows is
	 * performed in the context of the new `__display'.
	 *
	 * @return: 0 : Success
	 * @return: -1: [errno=EPERM] Not allowed to change target display of compositor
	 * @return: -1: [errno=*] Failed to change backing display for some other reason */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_INOUT_T(2) int
	(LIBVIDEO_COMPOSITOR_CC *vcpo_setdisplay)(struct video_compositor *__restrict __self,
	                                          struct video_display *__restrict __display);

	/* Indicates to the compositor that it needs to call `video_display_getbuffer()' to
	 * obtain a new buffer, since the one previously returned by the associated display
	 * may have changed.
	 *
	 * @return: 0 : Success, no-op, or nothing changed
	 * @return: -1: [errno=ENOMEM] Buffer changed, but insufficient memory to propagate changes */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) int
	(LIBVIDEO_COMPOSITOR_CC *vcpo_updatebuffer)(struct video_compositor *__restrict __self);

	/* Return features supported by `__self'
	 * @return: 0 : Success
	 * @return: -1: Failed to get features (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_OUT_T(2) int
	(LIBVIDEO_COMPOSITOR_CC *vcpo_getfeatures)(struct video_compositor *__restrict __self,
	                                           video_compositor_feature_t *__restrict __p_features);

	/* Change features supported by `__self'
	 * @return: 0 : Success
	 * @return: -1: Failed to update features (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) int
	(LIBVIDEO_COMPOSITOR_CC *vcpo_setfeatures)(struct video_compositor *__restrict __self,
	                                           video_compositor_feature_t __features);

	/* Return background color used by `__self'
	 * @return: 0 : Success
	 * @return: -1: Failed to get background color (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_OUT_T(2) int
	(LIBVIDEO_COMPOSITOR_CC *vcpo_getbackground)(struct video_compositor *__restrict __self,
	                                             video_color_t *__restrict __p_background);

	/* Change background color used by `__self'. This is what's
	 * written to pixels that do not intersect with any window.
	 * @return: 0 : Success
	 * @return: -1: Failed to update background color (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) int
	(LIBVIDEO_COMPOSITOR_CC *vcpo_setbackground)(struct video_compositor *__restrict __self,
	                                             video_color_t __background);
};

#ifdef __INTELLISENSE__
/* Create and return a new window
 * @return: * :   The newly created window
 * @return: NULL: Failed to create window (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN(2) __ATTR_IN_OPT(3) __REF struct video_window *LIBVIDEO_COMPOSITOR_CC
video_compositor_newwindow(struct video_compositor *__restrict __self,
                           struct video_window_position const *__restrict __position,
                           struct video_gfx const *__initial_content);

/* Returns a reference to the video buffer targeted by this compositor. */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __REF struct video_buffer *LIBVIDEO_COMPOSITOR_CC
video_compositor_getbuffer(struct video_compositor *__restrict __self);

/* Change the video buffer targeted by this compositor. This function may
 * not  be available for certain compositors (namely: when talking to the
 * IPC compositor exposed by the window server).
 *
 * After a new buffer has been assigned, a full re-draw of all windows is
 * performed in the context of the new `__buffer'.
 *
 * @return: 0 : Success
 * @return: -1: [errno=EPERM] Not allowed to change target buffer of compositor
 * @return: -1: [errno=*] Failed to change backing buffer for some other reason */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_INOUT(2) int LIBVIDEO_COMPOSITOR_CC
video_compositor_setbuffer(struct video_compositor *__restrict __self,
                           struct video_buffer *__restrict __buffer);

/* Change the value of `self->vcp_features'
 * @return: 0 : Success
 * @return: -1: Failed to update features (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) int LIBVIDEO_COMPOSITOR_CC
video_compositor_setfeatures(struct video_compositor *__restrict __self,
                             video_compositor_feature_t __features);

/* Return background color used by `__self'
 * @return: 0 : Success
 * @return: -1: Failed to get background color (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) int LIBVIDEO_COMPOSITOR_CC
video_compositor_getbackground(struct video_compositor *__restrict __self,
                               video_color_t *__restrict __p_background);

/* Change background color used by `__self'. This is what's
 * written to pixels that do not intersect with any window.
 * @return: 0 : Success
 * @return: -1: Failed to update background color (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) int LIBVIDEO_COMPOSITOR_CC
video_compositor_setbackground(struct video_compositor *__restrict __self,
                               video_color_t __background);

#else /* __INTELLISENSE__ */
#define video_compositor_newwindow(self, position, initial_content) \
	(*(self)->vcp_ops->vcpo_newwindow)(self, position, initial_content)
#define video_compositor_getbuffer(self)                   (*(self)->vcp_ops->vcpo_getbuffer)(self)
#define video_compositor_setbuffer(self, buffer)           (*(self)->vcp_ops->vcpo_setbuffer)(self, buffer)
#define video_compositor_setfeatures(self, features)       (*(self)->vcp_ops->vcpo_setfeatures)(self, features)
#define video_compositor_getbackground(self, p_background) (*(self)->vcp_ops->vcpo_getbackground)(self, p_background)
#define video_compositor_setbackground(self, background)   (*(self)->vcp_ops->vcpo_setbackground)(self, background)
#endif /* !__INTELLISENSE__ */


struct video_compositor {
	struct video_compositor_ops const *vcp_ops;    /* [1..1][const] Compositor operators */
	__uintptr_t                        vcp_refcnt; /* Reference counter */
	/* Extra, compositor-specific fields go here... */
};

#define video_compositor_destroy(self) (*(self)->vcp_ops->vcpo_destroy)(self)
#define video_compositor_incref(self) \
	__hybrid_atomic_inc(&(self)->vcp_refcnt, __ATOMIC_SEQ_CST)
#define video_compositor_decref(self)                                         \
	(void)(__hybrid_atomic_decfetch(&(self)->vcp_refcnt, __ATOMIC_SEQ_CST) || \
	       (video_compositor_destroy(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_compositor, vcp_refcnt, video_compositor_destroy)



/* Create a new video compositor for `__display'. The compositor returned
 * by this function will run in the caller's process, meaning it does not
 * impose any `EPERM'-like restrictions.
 * @return: * :   The newly created compositor
 * @return: NULL: [errno=ENOMEM] Out of memory */
typedef __ATTR_WUNUSED_T __ATTR_INOUT_T(1) __REF struct video_compositor *
(LIBVIDEO_COMPOSITOR_CC *PVIDEO_COMPOSITOR_CREATE)(struct video_display *__restrict __display,
                                                   video_compositor_feature_t __features,
                                                   video_color_t __background);
#ifdef LIBVIDEO_COMPOSITOR_WANT_PROTOTYPES
LIBVIDEO_COMPOSITOR_DECL __ATTR_WUNUSED __ATTR_INOUT(1) __REF struct video_compositor *LIBVIDEO_COMPOSITOR_CC
video_compositor_create(struct video_display *__restrict __display,
                        video_compositor_feature_t __features,
                        video_color_t __background);
#endif /* LIBVIDEO_COMPOSITOR_WANT_PROTOTYPES */

#endif /* __CC__ */

__DECL_END

#endif /* !_LIBVIDEO_COMPOSITOR_COMPOSITOR_H */
