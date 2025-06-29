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
#ifndef _LIBVIDEO_GFX_ANIM_H
#define _LIBVIDEO_GFX_ANIM_H 1

#include "api.h"

#include <__crt.h> /* __FILE */
#include <hybrid/__atomic.h>

#include <bits/os/timeval.h>
#include <bits/types.h>
#include <kos/anno.h>
#include <kos/refcnt.h>

#include <libvideo/codec/types.h>

/* TODO: Support for animations (e.g. .gif):
 * - DON'T do this the way that SDL-image does it (i.e. have 1 buffer for every frame)
 * - Instead, animated video buffers rendered progressively, using a control structure
 *   that (among other things) includes a `struct mapfile' of the raw underlying file.
 * - This structure then exposes a function like `paint_next_frame()' (possibly using
 *   a secondary control structure, such that the original animation can be  rendered
 *   in parallel by multiple threads using individual rendering contexts)
 * - When called, `paint_next_frame()' takes a  video_buffer that is expected to  have
 *   originally  been created by  the animation itself (iow:  its codec/palette may be
 *   assumed to be known to the animation),  as well that the buffer's video  contents
 *   have not been modified since the last call to `paint_next_frame()' (meaning  that
 *   for animation formats where a frame is allowed to consist of only a specific sub-
 *   region of a larger image only has to render said sub-region)
 */

#ifdef __CC__
__DECL_BEGIN

struct video_buffer;
struct video_anim;
typedef __uint32_t video_anim_frame_id;

struct video_anim_frameinfo {
	struct __timeval64  vafi_showfor; /* How long to display the frame before showing the next */
	video_anim_frame_id vafi_frameid; /* ID (# of frames that came before) of the associated frame */
};

struct video_anim_ops {
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_CC *vao_destroy)(struct video_anim *__restrict __self);

	/* Start a new animation cycle and return a video buffer for the first frame.
	 * - The video contents of the returned buffer should NOT be modified.
	 * - Make a call to `vao_nextframe()' to advance to the next frame.
	 *
	 * To render the animation, the caller should do this:
	 * >> struct video_anim_frameinfo info, nextinfo;
	 * >> REF struct video_screen *screen = screen_buffer_create(NULL);
	 * >> REF struct video_anim *anim = video_anim_open("/vat/anim.gif");
	 * >> REF struct video_buffer *frame = video_anim_firstframe(anim, &info);
	 * >> struct video_gfx screen_gfx;
	 * >> struct video_gfx frame_gfx;
	 * >> struct timeval frame_start, frame_end;
	 * >> struct timeval tv_delay, tv_spent;
	 * >> struct timespec ts_delay;
	 * >> video_buffer_getgfx((struct video_buffer *)screen, &screen_gfx,
	 * >>                     GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	 * >> gettimeofday(&frame_start, NULL);
	 * >> for (;;) {
	 * >>
	 * >>     // Display current frame on-screen (here: stretched)
	 * >>     video_buffer_getgfx(frame, &frame_gfx,
	 * >>                         GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	 * >>     video_gfx_stretch(&screen_gfx, 0, 0, VIDEO_DIM_MAX, VIDEO_DIM_MAX,
	 * >>                       &frame_gfx, 0, 0, VIDEO_DIM_MAX, VIDEO_DIM_MAX);
	 * >>     struct screen_rect update_rect = SCREEN_RECT_INIT_WHOLE_SCREEN;
	 * >>     screen_buffer_updaterect(screen, &update_rect);
	 * >>
	 * >>     // Load next frame as part of render delay
	 * >>     nextinfo = info;
	 * >>     video_anim_nextframe(&anim, frame, &nextinfo);
	 * >>
	 * >>     // Wait until the next frame should be rendered
	 * >>     gettimeofday(&frame_end, NULL);
	 * >>     timeval_sub(&tv_spent, &frame_end, &frame_start);
	 * >>     timeval_sub(&tv_delay, &info.vafi_showfor, &tv_spent);
	 * >>     timeval_add(&frame_end, &frame_end, &tv_delay);
	 * >>     TIMEVAL_TO_TIMESPEC(&tv_delay, &ts_delay);
	 * >>     frame_start = frame_end;
	 * >>     info = nextinfo;
	 * >>     if (ts_delay.tv_sec >= 0)
	 * >>         nanosleep(&ts_delay, NULL);
	 * >> }
	 *
	 * @return: * : A video buffer containing the  first frame of the  animation
	 *              If  you do not intend to render  any of the other frame, you
	 *              can simply decref() the animation and use this buffer as you
	 *              would one returned by `video_buffer_open()'
	 * @return: NULL: Failed to load first frame (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_OUT_T(2) __REF struct video_buffer *
	(LIBVIDEO_GFX_CC *vao_firstframe)(struct video_anim const *__restrict __self,
	                                  struct video_anim_frameinfo *__restrict __info);

	/* Update  pixel data of `__buf' to contain the contents of the next frame in line.
	 * For this purpose, assume that on entry, `__buf' was returned by `vao_firstframe'
	 * or  a preceding call to `vao_nextframe', and  currently contains a redner of the
	 * frame identified by `IN(__info->vafi_frameid)'.
	 *
	 * This function may  then update the  contents of `__buf'  and `__info' such  that
	 * upon successful return (return == 0), `__info->vafi_frameid' has been  increment
	 * or reset back to `0',  and `__buf' now contains a  render of the next frame.  It
	 * may also simply return some other video buffer (iow: return != __buf) is allowed
	 *
	 * CAUTION: This function is not thread-safe when `__buf' is simultaneously being
	 *          used by another thread, or if someone is still holding a  video_lock.
	 *          This function is also allowed to  modify `__buf' in way not  normally
	 *          allowed  (including changing its codec and/or palette, as well as the
	 *          memory  used to back any potential video  lock). The only thing it is
	 *          not allowed to changed are the buffer's dimensions.
	 *
	 * CAUTION: The video buffer returned by `vao_firstframe' might contain some extra
	 *          out-of-band data that is then  needed/used by this function to  render
	 *          the next frame. Do **NOT** pass a video buffer that wasn't returned by
	 *          `vao_firstframe',  and do **NOT**  try to skip  frames by changing the
	 *          value in `__info->vafi_frameid' between calls.
	 *
	 * @return: * :   A video buffer with the  same resolution as `__buf' (or  possibly
	 *                just  `__buf' again), that  contains a render  of the next frame.
	 *                In this case,  this function semantically  inherited a  reference
	 *                to the given `__buf' (meaning that if another buffer is returned,
	 *                the call will have video_buffer_decref'd the given `__buf')
	 * @return: NULL: Failed  to render next frame (s.a. `errno'). In this case, no
	 *                reference to  `__buf' has  been inherited,  though the  pixel
	 *                contents  of `__buf' may have been modified and may even look
	 *                corrupted now (though semantically speaking, `__buf' is still
	 *                guarantied to be in a consistent state). */
	__ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_INOUT_T(2) __ATTR_INOUT_T(3) __REF struct video_buffer *
	(LIBVIDEO_GFX_CC *vao_nextframe)(struct video_anim const *__restrict __self,
	                                 /*inherit(on_success)*/ __REF struct video_buffer *__restrict __buf,
	                                 struct video_anim_frameinfo *__restrict __info);
};

#define video_anim_firstframe(self, info) \
	(*(self)->va_ops->vao_firstframe)(self, info)
#define video_anim_nextframe(self, buf, info) \
	(*(self)->va_ops->vao_nextframe)(self, buf, info)

struct video_anim {
	__uintptr_t                  va_refcnt; /* Reference counter. */
	struct video_anim_ops const *va_ops;    /* [1..1][const] Video animation operators */
	video_dim_t                  va_size_x; /* [const] Size in X of the animation buffer */
	video_dim_t                  va_size_y; /* [const] Size in Y of the animation buffer */
	/* Extra animation-specific data goes here... */
};

#define video_anim_destroy(self) (*(self)->va_ops->vao_destroy)(self)
#define video_anim_incref(self) \
	__hybrid_atomic_inc(&(self)->va_refcnt, __ATOMIC_SEQ_CST)
#define video_anim_decref(self)                                              \
	(void)(__hybrid_atomic_decfetch(&(self)->va_refcnt, __ATOMIC_SEQ_CST) || \
	       (video_anim_destroy(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_anim, va_refcnt, video_anim_destroy)


/* Create a single-frame video animation from a given buffer.
 * The returned animation  object always re-return  `__frame'
 * when a call is made to `video_anim_firstframe', and trying
 * to load any  other frame via  `video_anim_nextframe' is  a
 * no-op.
 * @return: * :   The controller for the single-frame video animation
 * @return: NULL: Out of memory. */
typedef __ATTR_WUNUSED_T __ATTR_INOUT_T(1) __REF struct video_anim *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_FROMFRAME)(struct video_buffer *__restrict __frame);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_INOUT(1) __REF struct video_anim *LIBVIDEO_GFX_CC
video_anim_fromframe(struct video_buffer *__restrict __frame);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Return a wrapper for `__self'  that caches animation frames  during
 * the first loop, and simply replays them during any subsequent loop.
 * @param: __codec:   When non-null,  animation frames  are converted  into
 *                    this pixel format, rather than being copied verbatim.
 * @param: __palette: Used with `__codec' (if non-NULL)
 * @param: __type:    The type of video buffer to use for cached images. */
typedef __ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_IN_OPT_T(2) __ATTR_IN_OPT_T(3) __REF struct video_anim *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_CACHED)(struct video_anim *__restrict __self, struct video_codec const *__codec,
                                      struct video_palette *__palette, unsigned int __type);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN_OPT(2) __ATTR_IN_OPT(3) __REF struct video_anim *LIBVIDEO_GFX_CC
video_anim_cached(struct video_anim *__restrict __self, struct video_codec const *__codec,
                  struct video_palette *__palette, unsigned int __type);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Various functions for opening a file/stream/blob as an animation file.
 * The actual file format is auto-detected, and supported formats  depend
 * on installed 3rd party libraries. By default, GIF is supported.
 *
 * If the specified blob isn't for an animated video format, the file  is
 * instead opened using `video_buffer_open()', and the returned animation
 * will only have a single frame. */
typedef __ATTR_WUNUSED_T __REF struct video_anim *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_MOPEN)(void const *__blob, __size_t __blob_size);
typedef __ATTR_WUNUSED_T __REF struct video_anim *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_FOPEN)(__FILE *__restrict __fp);
typedef __ATTR_WUNUSED_T __REF struct video_anim *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_FDOPEN)(__fd_t __fd);
typedef __ATTR_WUNUSED_T __REF struct video_anim *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_OPEN)(char const *__filename);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_anim *LIBVIDEO_GFX_CC
video_anim_mopen(void const *__blob, __size_t __blob_size);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_anim *LIBVIDEO_GFX_CC
video_anim_fopen(__FILE *__restrict __fp);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_anim *LIBVIDEO_GFX_CC
video_anim_fdopen(__fd_t __fd);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_anim *LIBVIDEO_GFX_CC
video_anim_open(char const *__filename);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

/* TODO: Api for saving a video animation */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_ANIM_H */
