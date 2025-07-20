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

#include "../color.h"
#include "../types.h"

#ifdef __CC__
__DECL_BEGIN

struct video_buffer;
struct video_domain;
struct video_anim;

typedef __uint32_t video_anim_frame_id;

/* Frame data created when the first frame is read, and updated whenever a next frame is read.
 * You must treat this data as READ-ONLY  if you ever intend to call  `video_anim_nextframe()'
 * using this data again. */
struct video_anim_frame {
	__ATTR_NONNULL_T((1)) void /* Destructor callback for frame data */
	(LIBVIDEO_GFX_CC *vaf_fini)(struct video_anim_frame *__restrict __self);
	REF struct video_buffer *vaf_frame;    /* [1..1] Current frame (and previous frame during) */
	struct __timeval64       vaf_showfor;  /* How long to display the frame before showing the next */
	video_anim_frame_id      vaf_frameid;  /* ID of this frame */
	video_color_t            vaf_colorkey; /* Frame color key, or "0" if not needed */

	/* Animation-specific frame data goes here... */
};

#define video_anim_frame_fini(self) ((self)->vaf_fini)(self)


struct video_anim_ops {
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_CC *vao_destroy)(struct video_anim *__restrict __self);

	/* Size of  `struct video_anim_frame' that  the
	 * caller must use with this type of animation. */
	size_t vao_sizeof_frame;

	/* Start a new animation cycle and initialize `__frame' for the first frame.
	 * - The video contents of the buffer included in `__frame'  should NOT be modified.
	 * - Make a call to `vao_nextframe()' to advance to the next frame.
	 * - Once done, finalize frame data using `video_anim_frame_fini(__frame)'
	 * - The given  `__frame' must  be at  least `vao_sizeof_frame'  bytes  large,
	 *   and be aligned according to standard alignment (`alloca()' and `malloc()'
	 *   are both fine for allocating this buffer))
	 *
	 * To render the animation, the caller should do this:
	 * >> struct video_gfx screen_gfx;
	 * >> struct video_gfx frame_gfx;
	 * >> struct timeval frame_start, frame_end;
	 * >> struct timeval tv_delay, tv_spent, showfor;
	 * >> struct timespec ts_delay;
	 * >> REF struct video_screen *screen;
	 * >> REF struct video_anim *anim;
	 * >> struct video_anim_frame *data;
	 * >>
	 * >> screen = screen_buffer_create(NULL);
	 * >> anim = video_anim_open("/var/anim.gif");
	 * >> data = (struct video_anim_frame *)malloca(video_anim_sizeof_frame(anim));
	 * >>
	 * >> video_anim_firstframe(anim, data);
	 * >> video_buffer_getgfx((struct video_buffer *)screen, &screen_gfx,
	 * >>                     GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	 * >> gettimeofday(&frame_start, NULL);
	 * >> for (;;) {
	 * >>
	 * >>     // Display current frame on-screen (here: stretched)
	 * >>     video_buffer_getgfx(data->vaf_frame, &frame_gfx,
	 * >>                         GFX_BLENDMODE_OVERRIDE, VIDEO_GFX_F_NORMAL, 0);
	 * >>     video_gfx_stretch(&screen_gfx, 0, 0, VIDEO_DIM_MAX, VIDEO_DIM_MAX,
	 * >>                       &frame_gfx, 0, 0, VIDEO_DIM_MAX, VIDEO_DIM_MAX);
	 * >>     struct video_crect update_rect = VIDEO_CRECT_INIT_FULL;
	 * >>     screen_buffer_updaterect(screen, &update_rect);
	 * >>
	 * >>     // Load next frame as part of render delay
	 * >>     showfor = data->vaf_showfor;
	 * >>     video_anim_nextframe(&anim, data);
	 * >>
	 * >>     // Wait until the next frame should be rendered
	 * >>     gettimeofday(&frame_end, NULL);
	 * >>     timeval_sub(&tv_spent, &frame_end, &frame_start);
	 * >>     timeval_sub(&tv_delay, &showfor, &tv_spent);
	 * >>     timeval_add(&frame_end, &frame_end, &tv_delay);
	 * >>     TIMEVAL_TO_TIMESPEC(&tv_delay, &ts_delay);
	 * >>     frame_start = frame_end;
	 * >>     if (ts_delay.tv_sec >= 0)
	 * >>         nanosleep(&ts_delay, NULL);
	 * >> }
	 *
	 * @return: 0 : Success: `__frame' was initialized and the caller must eventually finalize it
	 * @return: -1: Failed to load first frame (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_OUT_T(2) int
	(LIBVIDEO_GFX_CC *vao_firstframe)(struct video_anim const *__restrict __self,
	                                  struct video_anim_frame *__restrict __frame);

	/* Update `__frame' (and specifically: `__frame->vaf_frame') to contain the contents
	 * of the next frame in line.
	 *
	 * @return: 0 : Success: `__frame' was updated to contain the next frame.
	 * @return: -1: Failed  to render next frame (s.a. `errno'). In this case, no
	 *              reference to  `__buf' has  been inherited,  though the  pixel
	 *              contents  of `__buf' may have been modified and may even look
	 *              corrupted now (though semantically speaking, `__buf' is still
	 *              guarantied to be in a consistent state). */
	__ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_INOUT_T(2) int
	(LIBVIDEO_GFX_CC *vao_nextframe)(struct video_anim const *__restrict __self,
	                                 struct video_anim_frame *__restrict __frame);
};

#define video_anim_sizeof_frame(self)      ((self)->va_ops->vao_sizeof_frame)
#define video_anim_firstframe(self, frame) (*(self)->va_ops->vao_firstframe)(self, frame)
#define video_anim_nextframe(self, frame)  (*(self)->va_ops->vao_nextframe)(self, frame)

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
 * @param: __domain: When non-null, animation  frames are  cached in  this
 *                   domain, rather than being kept in `__self->va_domain'
 * @param: __format: When non-null,  animation frames  are converted  into
 *                   this pixel format, rather than being copied verbatim. */
typedef __ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_IN_OPT_T(2) __ATTR_IN_OPT_T(3) __REF struct video_anim *
(LIBVIDEO_GFX_CC *PVIDEO_ANIM_CACHED)(struct video_anim *__restrict __self,
                                      struct video_domain const *__domain,
                                      struct video_format const *__format);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN_OPT(2) __ATTR_IN_OPT(3) __REF struct video_anim *LIBVIDEO_GFX_CC
video_anim_cached(struct video_anim *__restrict __self,
                  struct video_domain const *__domain,
                  struct video_format const *__format);
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
