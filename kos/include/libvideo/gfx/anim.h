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
/**/

#include <__crt.h> /* __FILE */

#include <hybrid/__atomic.h>

#include <bits/os/timeval.h>
#include <bits/types.h>
#include <kos/anno.h>
#include <kos/refcnt.h>

#include "../types.h"

#ifdef __CC__
__DECL_BEGIN

struct video_buffer;
struct video_domain;
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
	 * >>     struct video_crect update_rect = VIDEO_CRECT_INIT_FULL;
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
	struct video_anim_ops const *va_ops;    /* [1..1][const] Video animation operators */
	struct video_domain const   *va_domain; /* [1..1][const] Video domain */
	video_dim_t                  va_xdim;   /* [const] X pixel dimension of animation frames */
	video_dim_t                  va_ydim;   /* [const] Y pixel dimension of animation frames */
	__uintptr_t                  va_refcnt; /* Reference counter. */
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
 * @param: __format: When non-null,  animation frames  are converted  into
 *                   this pixel format, rather than being copied verbatim.
 * @param: __type:   The type of video buffer to use for cached images. */
typedef __ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_IN_OPT_T(2) __REF struct video_anim *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_CACHED)(struct video_anim *__restrict __self,
                                      struct video_format const *__format);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN_OPT(2) __REF struct video_anim *LIBVIDEO_GFX_CC
video_anim_cached(struct video_anim *__restrict __self, struct video_format const *__format);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Various functions for opening a file/stream/blob as an animation file.
 * The actual file format is auto-detected, and supported formats  depend
 * on installed 3rd party libraries. By default, GIF is supported.
 *
 * If the specified blob isn't for an animated video format, the file  is
 * instead opened using `video_buffer_open()', and the returned animation
 * will only have a single frame. */
typedef __ATTR_WUNUSED_T __ATTR_INS_T(2, 3) __ATTR_NONNULL_T((1)) __REF struct video_anim *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_MOPEN)(struct video_domain const *__restrict __domain,
                                     void const *__blob, __size_t __blob_size);
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) __REF struct video_anim *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_FOPEN)(struct video_domain const *__restrict __domain, __FILE *__restrict __fp);
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __REF struct video_anim *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_FDOPEN)(struct video_domain const *__restrict __domain, __fd_t __fd);
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) __REF struct video_anim *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_OPEN)(struct video_domain const *__restrict __domain, char const *__filename);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __REF struct video_anim *LIBVIDEO_GFX_CC
video_anim_mopen(struct video_domain const *__restrict __domain,
                 void const *__blob, __size_t __blob_size);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __REF struct video_anim *LIBVIDEO_GFX_CC
video_anim_fopen(struct video_domain const *__restrict __domain, __FILE *__restrict __fp);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __REF struct video_anim *LIBVIDEO_GFX_CC
video_anim_fdopen(struct video_domain const *__restrict __domain, __fd_t __fd);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __REF struct video_anim *LIBVIDEO_GFX_CC
video_anim_open(struct video_domain const *__restrict __domain, char const *__filename);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */



/************************************************************************/
/* VIDEO ANIMATION WRITER API                                           */
/************************************************************************/

struct video_anim_writer;
struct video_anim_writer_ops {
	/* Called to destroy the animation writer.
	 *
	 * When called before `vawo_finish', and `video_anim_save' was used to
	 * write  the animation to a filesystem location, the output file will
	 * be deleted by this call (though this failing is silently ignored). */
	__ATTR_NONNULL_T((1)) void
	__NOTHROW_T(LIBVIDEO_GFX_CC *vawo_destroy)(struct video_anim_writer *__restrict __self);

	/* Write a single  `__frame' to  the animation. During  playback, said  frame
	 * will be shown for the closest representable delay to `__self->vaw_showfor'
	 * The actual frame data  written is the Clip  Rect of `__frame', with  pixel
	 * data blended with any preceding frame as per `GFX_BLENDMODE_OVERRIDE'  for
	 * all  pixels within the I/O rect, with  all pixels outside simply not being
	 * altered (the initial state of this "background" is format-specific, but it
	 * is probably either all-black, or transparent).
	 *
	 * This function will automatically check what actually changed during  some
	 * frame and (depending on output format), will probably only write actually
	 * changed regions.
	 *
	 * @return: 0 : Success
	 * @return: -1: [errno=EINVAL]  Clip rect of `__frame' has wrong dimensions
	 * @return: -1: [errno=ENOTSUP] Max  # of frames  supported by output format
	 *                              has  been reached. Generally,  if you try to
	 *                              write an animation to a using a non-animated
	 *                              image format, you can only write 1 frame.
	 * @return: -1: Frame generation failed (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_IN_T(2) int
	(LIBVIDEO_GFX_CC *vawo_putframe)(struct video_anim_writer *__restrict __self,
	                                 struct video_gfx const *__restrict __frame);

	/* Finish writing animation data. Must be called at the very end to  finalize
	 * the generated file, once `vawo_putframe' will no longer be invoked. Trying
	 * to call `vawo_putframe' after this has been called results in undefined
	 * behavior:
	 *
	 * @return: 0 : Success
	 * @return: -1: Error; probably I/O-related (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) int
	(LIBVIDEO_GFX_CC *vawo_finish)(struct video_anim_writer *__restrict __self);

	/* Format-specific operators go here... */
};

#ifdef __INTELLISENSE__
/* Called to destroy the animation writer.
 *
 * When called before  `video_anim_writer_finish', and `video_anim_save'  was
 * used to write the animation to a filesystem location, the output file will
 * be deleted by this call (though this failing is silently ignored). */
extern __ATTR_NONNULL((1)) void
__NOTHROW(video_anim_writer_destroy)(struct video_anim_writer *__restrict __self);

/* Write a single  `__frame' to  the animation. During  playback, said  frame
 * will be shown for the closest representable delay to `__self->vaw_showfor'
 * The actual frame data  written is the Clip  Rect of `__frame', with  pixel
 * data blended with any preceding frame as per `GFX_BLENDMODE_OVERRIDE'  for
 * all  pixels within the I/O rect, with  all pixels outside simply not being
 * altered (and starting out as all-black for the first frame).
 *
 * This function will automatically check what actually changed during  some
 * frame and (depending on output format), will probably only write actually
 * changed regions.
 *
 * @return: 0 : Success
 * @return: -1: Frame generation failed (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN(2) int
video_anim_writer_putframe(struct video_anim_writer *__restrict __self,
                           struct video_gfx const *__restrict __frame);

/* Finish writing animation data. Must be called at the very end to  finalize
 * the generated file, once `vawo_putframe' will no longer be invoked. Trying
 * to call `vawo_putframe' after this has been called results in undefined
 * behavior:
 *
 * @return: 0 : Success
 * @return: -1: Error; probably I/O-related (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) int
video_anim_writer_finish(struct video_anim_writer *__restrict __self);
#else /* __INTELLISENSE__ */
#define video_anim_writer_destroy(self)         (*(self)->vaw_ops->vawo_destroy)(self)
#define video_anim_writer_putframe(self, frame) (*(self)->vaw_ops->vawo_putframe)(self, frame)
#define video_anim_writer_finish(self)          (*(self)->vaw_ops->vawo_finish)(self)
#endif /* !__INTELLISENSE__ */

struct video_anim_writer {
	struct video_anim_writer_ops const *vaw_ops;     /* [1..1][const] Animation writer operators */
	struct __timeval64                  vaw_showfor; /* How long the next frame in the next call to `vawo_putframe' should be shown for */
	video_dim_t                         vaw_xdim;    /* [const] Animation canvas size in X */
	video_dim_t                         vaw_ydim;    /* [const] Animation canvas size in X */
#ifdef LIBVIDEO_GFX_EXPOSE_INTERNALS
	char   *vaw_outfile;    /* [0..1][owned] File to delete in `vawo_destroy', or `NULL' if not a file output-stream, or `vawo_finish' was called */
	__FILE *vaw_owned_fp;   /* [0..1][owned] Owned file stream (closed in `vawo_destroy' when non-NULL) */
	__FILE *vaw_fp;         /* [1..1][const] Output file stream for writing image data */
	__BOOL  vaw_release_fp; /* [const] Must call "frelease(vaw_owned_fp)" in `vawo_destroy' */
#endif /* LIBVIDEO_GFX_EXPOSE_INTERNALS */
	/* Format-specific fields go here... */
};


/* Various functions for writing a video animation files.
 * @param: __size_x:             Animation canvas X dimension
 * @param: __size_y:             Animation canvas Y dimension
 * @param: __format:             Case-insensitive file format that should be used for output (e.g. "gif" for gif files)
 * @param: __fp/__fd/__filename: Location where animation data should be streamed to
 * @param: __options:            Optional format-specific options (','-separated string of "NAME=VALUE"; not documented here)
 * @return: * :   A writer that can be fed with data on each frame of the animation
 * @return: NULL: [errno=EINVAL] Unsupported `__format'
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=*] Some other error */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((3, 4)) __REF struct video_anim_writer *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_FSAVE)(video_dim_t __size_x, video_dim_t __size_y,
                                     char const *__format, __FILE *__restrict __fp, char const *__options);
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((3)) __REF struct video_anim_writer *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_FDSAVE)(video_dim_t __size_x, video_dim_t __size_y,
                                      char const *__format, __fd_t __fd, char const *__options);
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((3)) __REF struct video_anim_writer *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_SAVE)(video_dim_t __size_x, video_dim_t __size_y,
                                    char const *__filename, char const *__options);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) __REF struct video_anim_writer *LIBVIDEO_GFX_CC
video_anim_fsave(video_dim_t __size_x, video_dim_t __size_y,
                 char const *__format, __FILE *__restrict __fp, char const *__options);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((3)) __REF struct video_anim_writer *LIBVIDEO_GFX_CC
video_anim_fdsave(video_dim_t __size_x, video_dim_t __size_y,
                  char const *__format, __fd_t __fd, char const *__options);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((3)) __REF struct video_anim_writer *LIBVIDEO_GFX_CC
video_anim_save(video_dim_t __size_x, video_dim_t __size_y,
                char const *__filename, char const *__options);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_ANIM_H */
