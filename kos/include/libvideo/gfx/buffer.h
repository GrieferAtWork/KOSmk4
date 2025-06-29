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
#ifndef _LIBVIDEO_GFX_BUFFER_H
#define _LIBVIDEO_GFX_BUFFER_H 1

#include "api.h"

#include <__crt.h> /* __FILE */
#include <__stdinc.h>
#include <features.h>

#include <hybrid/__atomic.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/refcnt.h>

#include <libvideo/codec/format.h>
#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>

#include "gfx.h"

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

/* Video buffer types:
 * AUTO: Type doesn't matter, and is even allowed to change randomly
 * RAM:  Ram buffer. GFX ops are software-driven, and execute synchronously
 * GPU:  V-RAM backed, or  otherwise hardware accelerated  (or maybe  not).
 *       The big  semantic difference  is that  GPU operations  can  happen
 *       asynchronously  (and possibly using  hardware). This usually never
 *       shows itself in APIs, since all pixel read-operations will  always
 *       block until any pending writes of that pixel (or buffer) are done,
 *       though since special V-RAM may be used, acquiring a video lock  to
 *       the underlying  memory may  arbitrarily fail  for various  reason. */
#define VIDEO_BUFFER_AUTO 0x0000 /* Type doesn't matter. */
#define VIDEO_BUFFER_RAM  0x0001 /* RAM buffer. */
#define VIDEO_BUFFER_GPU  0x0002 /* GPU buffer. */

#ifdef __CC__
__DECL_BEGIN

struct video_format;
struct video_gfx;

struct video_lock {
	__byte_t *vl_data;   /* [1..vl_size] Memory-mapped video data. */
	__size_t  vl_size;   /* Total image size (>= vl_stride * :vb_ydim) */
	__size_t  vl_stride; /* Scanline width (in bytes) */
#define _VIDEO_LOCK__N_DRIVER 1
	void *_vl_driver[_VIDEO_LOCK__N_DRIVER]; /* Driver-specific data */
};

struct video_buffer_ops {
	/* NOTE: _ALL_ Callbacks are always [1..1] */

	/* Buffer finalization. */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_FCC *vi_destroy)(struct video_buffer *__restrict __self);

	/* Initialize a graphics context for use with the linked buffer.
	 * The caller  of this  operator must  have already  filled  in:
	 * - __self->vx_buffer  (with the buffer on which this operator is then called)
	 * - __self->vx_blend
	 * - __self->vx_flags
	 * - __self->vx_colorkey
	 * NOTE: This operator is allowed to modify any/all of the  above!
	 *       e.g. `video_buffer_lockable()' will change `vx_buffer' to
	 *       the wrapped video buffer.
	 * @return: * : Always re-returns `__self' */
	__ATTR_RETNONNULL_T __ATTR_INOUT_T(1) struct video_gfx *
	(LIBVIDEO_GFX_FCC *vi_initgfx)(struct video_gfx *__restrict __self);

	/* Update operators of `__self' after certain behavioral flags were changed:
	 * - VIDEO_GFX_UPDATE_BLEND:    `__self->vx_blend' may have changed
	 * - VIDEO_GFX_UPDATE_FLAGS:    `__self->vx_flags' may have changed
	 * - VIDEO_GFX_UPDATE_COLORKEY: `__self->vx_colorkey' may have changed
	 * @param: __what: Set of `VIDEO_GFX_UPDATE_*'
	 *
	 * CAUTION: Do not use this operator when `__self' may be used by other threads! */
	__ATTR_RETNONNULL_T __ATTR_INOUT_T(1) struct video_gfx *
	(LIBVIDEO_GFX_FCC *vi_updategfx)(struct video_gfx *__restrict __self,
	                                 unsigned int __what);

	/* Disable blending for `__self', which uses this video buffer. Same as:
	 * >> __self->vx_blend = GFX_BLENDMODE_OVERRIDE;
	 * >> __self->vx_flags &= ~VIDEO_GFX_F_BLUR;
	 * >> __self->vx_colorkey = 0;
	 * >> (*vi_updategfx)(__self, VIDEO_GFX_UPDATE_ALL);
	 *
	 * CAUTION: Do not use this operator when `__self' may be used by other threads! */
	__ATTR_RETNONNULL_T __ATTR_INOUT_T(1) struct video_gfx *
	(LIBVIDEO_GFX_FCC *vi_noblendgfx)(struct video_gfx *__restrict __self);

	void (*_vi_pad1[4])(void);

	/* Lock the video buffer into memory for reading.
	 * WARNING: Attempting to perform "gfx" operations on "this" while  holding
	 *          a  lock to video  memory may block and/or  be much slower until
	 *          said lock is released! The reason for this is that it is unsafe
	 *          to use hardware accelerated 2D operations while a video lock is
	 *          being held!
	 * @return: 0:  Success
	 * @return: -1: Error (s.a. `errno') */
	__ATTR_INOUT_T(1) __ATTR_OUT_T(2) int
	(LIBVIDEO_GFX_FCC *vi_rlock)(struct video_buffer *__restrict __self,
	                             struct video_lock *__restrict __result);

	/* Same as `vi_rlock', but also lock for reading+writing */
	__ATTR_INOUT_T(1) __ATTR_OUT_T(2) int
	(LIBVIDEO_GFX_FCC *vi_wlock)(struct video_buffer *__restrict __self,
	                             struct video_lock *__restrict __result);

	/* Unlock a video buffer that had previously been mapped into memory. */
	__ATTR_INOUT_T(1) __ATTR_IN_T(2) void
	__NOTHROW_T(LIBVIDEO_GFX_FCC *vi_unlock)(struct video_buffer *__restrict __self,
	                                         struct video_lock *__restrict __lock);

	void (*_vi_pad2[3])(void);
};




/************************************************************************/
/* Video GFX helper functions                                           */
/************************************************************************/

/* Convert `__self' into the specified format.
 * @param: type: The type of buffer to-be returned (one of `VIDEO_BUFFER_*'). */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_CONVERT)(struct video_buffer *__restrict __self,
                                         struct video_codec const *__codec,
                                         struct video_palette *__palette,
                                         unsigned int __type);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_convert(struct video_buffer *__restrict __self,
                     struct video_codec const *__codec,
                     struct video_palette *__palette,
                     unsigned int __type);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

/* Same as `video_buffer_convert()', but always return a distinct buffer, even if formats match */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_CONVERT_OR_COPY)(struct video_buffer *__restrict __self,
                                                 struct video_codec const *__codec,
                                                 struct video_palette *__palette,
                                                 unsigned int __type);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_convert_or_copy(struct video_buffer *__restrict __self,
                             struct video_codec const *__codec,
                             struct video_palette *__palette,
                             unsigned int __type);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

#ifdef __INTELLISENSE__
/* Get graphics functions for use with the given buffer
 * @param: blendmode: Pixel blending mode  for graphics operations  targeting this  buffer.
 *                    This  argument   should  be   constructed  using   `GFX_BLENDMODE()'.
 *                    Usually, you will want to use `GFX_BLENDMODE_ALPHA' as blending  mode
 *                    when you wish to make use of alpha-blending. However, if you know for
 *                    certain  that alpha-blending isn't required, graphics performance can
 *                    be improved by passing  `GFX_BLENDMODE_OVERRIDE' in order to  prevent
 *                    any overhead  that would  normally  incur from  blending  operations.
 * @param: flags:     Set of `VIDEO_GFX_F*'
 * @param: colorkey:  A specific color that should always return fully opaque when read
 *                    To disable colorkey-ing, simply pass some color with ALPHA=0  (or
 *                    alternatively, just pass `0' (which would be one such color))
 * @return: * : Always re-returns `__result' */
__ATTR_RETNONNULL __ATTR_INOUT(1) __ATTR_OUT(2) struct video_gfx *
video_buffer_getgfx(struct video_buffer *__self, struct video_gfx *__result,
                    gfx_blendmode_t __blendmode, gfx_flag_t __flags,
                    video_color_t __colorkey);

__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) int
video_buffer_rlock(struct video_buffer *__self, struct video_lock *__lock);
__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) int
video_buffer_wlock(struct video_buffer *__self, struct video_lock *__lock);
__ATTR_INOUT(1) __ATTR_IN(2) void
video_buffer_unlock(struct video_buffer *__self, struct video_lock *__lock);
#else /* __INTELLISENSE__ */
#define video_buffer_getgfx(self, result, blendmode, flags, colorkey)  \
	((result)->vx_colorkey = (colorkey), (result)->vx_flags = (flags), \
	 (result)->vx_blend = (blendmode),                                 \
	 (*((result)->vx_buffer = (self))->vb_ops->vi_initgfx)(result))
#define video_buffer_rlock(self, lock) \
	(*(self)->vb_ops->vi_rlock)(self, lock)
#define video_buffer_wlock(self, lock) \
	(*(self)->vb_ops->vi_wlock)(self, lock)
#define video_buffer_unlock(self, lock) \
	(*(self)->vb_ops->vi_unlock)(self, lock)
#endif /* !__INTELLISENSE__ */


#ifdef __cplusplus
__CXXDECL_BEGIN
#endif /* __cplusplus */

struct video_buffer {
	struct video_buffer_ops const *vb_ops;    /* [1..1][const] Buffer operations. */
	struct video_format            vb_format; /* [const] Buffer format. */
	video_dim_t                    vb_xdim;   /* Buffer dimension in X (in pixels) */
	video_dim_t                    vb_ydim;   /* Buffer dimension in Y (in pixels) */
	__uintptr_t                    vb_refcnt; /* Reference counter. */
	/* Buffer-specific fields go here */

#ifdef __cplusplus
#ifndef GUARD_LIBVIDEO_GFX_API_H
	__CXX_DELETE_CTOR(video_buffer);
	__CXX_DELETE_DTOR(video_buffer);
	__CXX_DELETE_COPY(video_buffer);
	__CXX_DELETE_COPY_ASSIGN(video_buffer);
#endif /* !GUARD_LIBVIDEO_GFX_API_H */
public:

	/* Lock the video buffer into memory for reading.
	 * WARNING: Attempting to perform "gfx" operations on "this" while  holding
	 *          a  lock to video  memory may block and/or  be much slower until
	 *          said lock is released! The reason for this is that it is unsafe
	 *          to use hardware accelerated 2D operations while a video lock is
	 *          being held!
	 * @return: 0:  Success
	 * @return: -1: Error (s.a. `errno') */
	__CXX_CLASSMEMBER __ATTR_WUNUSED int rlock(struct video_lock &__lock) {
		return video_buffer_rlock(this, &__lock);
	}

	/* Same as `vi_rlock', but also lock for reading+writing */
	__CXX_CLASSMEMBER __ATTR_WUNUSED int wlock(struct video_lock &__lock) {
		return video_buffer_wlock(this, &__lock);
	}

	/* Unlock a video buffer that has previously been mapped into memory. */
	__CXX_CLASSMEMBER void unlock(struct video_lock &__lock) {
		video_buffer_unlock(this, &__lock);
	}


	/* Get graphics functions for use with the given buffer
	 * @param: flags: Set of `VIDEO_GFX_F*' */
	__CXX_CLASSMEMBER struct video_gfx &getgfx(struct video_gfx &__result,
	                                           gfx_blendmode_t __blendmode = GFX_BLENDMODE_OVERRIDE,
	                                           __uintptr_t __flags         = VIDEO_GFX_F_NORMAL,
	                                           video_color_t __colorkey    = 0) {
		return *video_buffer_getgfx(this, &__result, __blendmode, __flags, __colorkey);
	}

	/* Get graphics functions for use with the given buffer
	 * @param: flags: Set of `VIDEO_GFX_F*' */
	__CXX_CLASSMEMBER struct video_gfx getgfx(gfx_blendmode_t __blendmode = GFX_BLENDMODE_OVERRIDE,
	                                          __uintptr_t __flags         = VIDEO_GFX_F_NORMAL,
	                                          video_color_t __colorkey    = 0) {
		struct video_gfx __result;
		video_buffer_getgfx(this, &__result, __blendmode, __flags, __colorkey);
		return __result;
	}

#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
	/* Convert `__self' into the specified format.
	 * @param: type: The type of buffer to-be returned (one of `VIDEO_BUFFER_*'). */
	__CXX_CLASSMEMBER __REF struct video_buffer *convert(struct video_codec const *__codec,
	                                                     struct video_palette *__palette,
	                                                     unsigned int __type = VIDEO_BUFFER_AUTO) {
		return video_buffer_convert(this, __codec, __palette, __type);
	}
	__CXX_CLASSMEMBER __REF struct video_buffer *convert(struct video_format const *__format,
	                                                     unsigned int __type = VIDEO_BUFFER_AUTO) {
		return video_buffer_convert(this, __format->vf_codec, __format->vf_pal, __type);
	}
	__CXX_CLASSMEMBER __REF struct video_buffer *convert(struct video_buffer const *__buffer_with_wanted_format,
	                                                     unsigned int __type = VIDEO_BUFFER_AUTO) {
		return video_buffer_convert(this,
		                            __buffer_with_wanted_format->vb_format.vf_codec,
		                            __buffer_with_wanted_format->vb_format.vf_pal,
		                            __type);
	}
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */
#endif /* __cplusplus */
};

#ifdef __cplusplus
__CXXDECL_END
#endif /* __cplusplus */


#define video_buffer_destroy(self) (*(self)->vb_ops->vi_destroy)(self)
#define video_buffer_incref(self) \
	__hybrid_atomic_inc(&(self)->vb_refcnt, __ATOMIC_SEQ_CST)
#define video_buffer_decref(self)                                            \
	(void)(__hybrid_atomic_decfetch(&(self)->vb_refcnt, __ATOMIC_SEQ_CST) || \
	       (video_buffer_destroy(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_buffer, vb_refcnt, video_buffer_destroy)


/* Create a video buffer, or return NULL and set errno if creation failed.
 * NOTE: When the given `size_x' or `size_y' is ZERO(0), an empty buffer is returned
 *       which may not necessarily use the  given, or default `codec' and  `palette'
 * @param: codec:   The preferred video codec, or NULL to use `video_preferred_format()'.
 * @param: palette: The palette to use (only needed if used by `codec') */
typedef __ATTR_WUNUSED_T __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_CREATE)(unsigned int __type, video_dim_t __size_x, video_dim_t __size_y,
                                        struct video_codec const *__codec, struct video_palette *__palette);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_create(unsigned int __type, video_dim_t __size_x, video_dim_t __size_y,
                    struct video_codec const *__codec, struct video_palette *__palette);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Create a video buffer that interfaces with a pre-existing buffer whose
 * base address is located at `mem' (which consists of  `stride * size_y'
 * bytes). When  non-NULL,  `(*release_mem)(release_mem_cookie, mem)'  is
 * called when the final reference for the returned buffer is dropped.
 *
 * This function can be used to wrap a memory-resident graphics buffer
 * in-place,    without   needing   to    copy   it   anywhere   else.
 * @param: mem:     Base address  of  the  pre-loaded  memory  buffer.
 *                  If this location isn't writable, attempts to write
 *                  pixel  data of the  returned buffer will SEGFAULT.
 * @param: size_x:  Width of returned buffer
 * @param: size_y:  Height of returned buffer
 * @param: stride:  Scanline width in `mem'
 * @param: codec:   The video codec that describes how `mem' is encoded.
 * @param: palette: The palette to use (only needed if used by `codec')
 * @param: release_mem: Optional callback invoked when the returned buffer is destroyed
 * @param: release_mem_cookie: Cookie argument for `release_mem'
 * @return: * :   The newly created video buffer
 * @return: NULL: [errno=EINVAL] Given `stride' is too small for `codec' and `size_y'
 * @return: NULL: [errno=ENOMEM] Insufficient memory */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((5)) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_FORMEM)(void *__mem, video_dim_t __size_x, video_dim_t __size_y, __size_t __stride,
                                        struct video_codec const *__codec, struct video_palette *__palette,
                                        void (LIBVIDEO_GFX_CC *__release_mem)(void *__cookie, void *__mem),
                                        void *__release_mem_cookie);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((5)) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_formem(void *__mem, video_dim_t __size_x, video_dim_t __size_y, __size_t __stride,
                    struct video_codec const *__codec, struct video_palette *__palette,
                    void (LIBVIDEO_GFX_CC *__release_mem)(void *__cookie, void *__mem),
                    void *__release_mem_cookie);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */




/* Create a video buffer that represents the pixel data defined by  a
 * given `__bm' (bitmask). This function is primarily used internally
 * by `video_gfx_absfillmask()' and  `video_gfx_absfillstretchmask()'
 * to deal with  GFX contexts  where the bitmask  cannot be  rendered
 * using  the default method,  but has to be  rendered by being blit.
 *
 * @param: __size_x:       Width of the given `__bm' (in pixels)
 * @param: __size_y:       Height of the given `__bm' (in pixels)
 * @param: __bm:           Bitmask whose data should be referenced interpreted
 * @param: __bg_fg_colors: Colors that 0/1 bits of `__bm' should map to
 * @return: * :   The newly created video buffer
 * @return: NULL: [errno=ENOMEM] Insufficient memory (won't happen when
 *                               used internally, where struct is  just
 *                               allocated on-stack) */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(3) __ATTR_IN_T(4) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_FORBITMASK)(video_dim_t __size_x, video_dim_t __size_y,
                                            struct video_bitmask const *__restrict __bm,
                                            video_color_t const __bg_fg_colors[2]);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN(4) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_forbitmask(video_dim_t __size_x, video_dim_t __size_y,
                        struct video_bitmask const *__restrict __bm,
                        video_color_t const __bg_fg_colors[2]);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Callback prototypes for operators accepted by `video_buffer_forcustom()' */
typedef void (LIBVIDEO_GFX_CC *video_buffer_custom_destroy_t)(void *__cookie);
typedef __ATTR_PURE_T __ATTR_WUNUSED_T video_pixel_t (LIBVIDEO_GFX_CC *video_buffer_custom_getpixel_t)(void *__cookie, video_coord_t __x, video_coord_t __y);
typedef void (LIBVIDEO_GFX_CC *video_buffer_custom_setpixel_t)(void *__cookie, video_coord_t __x, video_coord_t __y, video_pixel_t __pixel);
typedef __ATTR_OUT_T(2) int (LIBVIDEO_GFX_CC *video_buffer_custom_lock_t)(void *__cookie, struct video_lock *__restrict __result);
typedef __ATTR_IN_T(2) void __NOTHROW_T(LIBVIDEO_GFX_CC *video_buffer_custom_unlock_t)(void *__cookie, struct video_lock *__restrict __result);


/* Construct a special video buffer which, rather than being backed by memory
 * or implemented using hardware acceleration,  does all its pixel I/O  using
 * the provided function pointers.
 *
 * WARNING: The  given `__getpixel' / `__setpixel' callbacks better be
 *          fast, or any GFX on the returned buffer will take forever!
 *
 * @param: __size_x:   X dimension of the returned video buffer
 * @param: __size_y:   Y dimension of the returned video buffer
 * @param: __codec:    [1..1] Video codec used for color<=>pixel conversion, as
 *                            well  as pixel I/O (when __rlock/__wlock is given
 *                            and returns `0')
 * @param: __palette:  [0..1] Palette to-be used with `__codec' (if needed)
 * @param: __getpixel: [1..1] Mandatory pixel read operator (passed coords are absolute and guarantied in-bounds)
 * @param: __setpixel: [1..1] Mandatory pixel write operator (passed coords are absolute and guarantied in-bounds)
 * @param: __destroy:  [0..1] Optional callback invoked when the returned buffer is destroyed
 * @param: __rlock:    [0..1] Optional callback to lock video memory for reading (when missing, or doesn't return `0', `__getpixel' is always used)
 * @param: __wlock:    [0..1] Optional callback to lock video memory for writing (when missing, or doesn't return `0', `__setpixel' is always used)
 * @param: __unlock:   [0..1] Optional callback invoked to release video locks previously acquired by `__rlock' or `__wlock'
 * @param: __cookie:   [?..?] Cookie argument passed to all user-supplied operators */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((3, 5, 6)) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_FORCUSTOM)(video_dim_t __size_x, video_dim_t __size_y,
                                           struct video_codec const *__codec, struct video_palette *__palette,
                                           video_buffer_custom_getpixel_t __getpixel,
                                           video_buffer_custom_setpixel_t __setpixel,
                                           video_buffer_custom_destroy_t __destroy,
                                           video_buffer_custom_lock_t __rlock,
                                           video_buffer_custom_lock_t __wlock,
                                           video_buffer_custom_unlock_t __unlock,
                                           void *__cookie);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED NONNULL((3, 5, 6)) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_forcustom(video_dim_t __size_x, video_dim_t __size_y,
                       struct video_codec const *__codec, struct video_palette *__palette,
                       video_buffer_custom_getpixel_t __getpixel,
                       video_buffer_custom_setpixel_t __setpixel,
                       video_buffer_custom_destroy_t __destroy,
                       video_buffer_custom_lock_t __rlock,
                       video_buffer_custom_lock_t __wlock,
                       video_buffer_custom_unlock_t __unlock,
                       void *__cookie);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* When `__self' isn't known to unconditionally support read/write  locks,
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
 * @param: __self:  The video buffer to wrap
 * @return: * :     The video buffer wrapper (having the same codec/dimensions as `__self')
 * @return: __self: The given `__self' is already known to have vi_rlock/vi_wlock operators
 *                  that either never fail, or can only fail with errno=ENOMEM for the same
 *                  reason that the  "lockable" wrapper could  also fail. (generally,  this
 *                  means that this is a no-op when `__self' is a ram-buffer, or is already
 *                  a "lockable" video buffer). */
typedef __ATTR_WUNUSED_T __ATTR_INOUT_T(1) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_LOCKABLE)(struct video_buffer *__restrict __self);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_INOUT(1) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_lockable(struct video_buffer *__restrict __self);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Return a video buffer that  will always (forcefully) re-return  `__self'
 * whenever a GFX context is requested. Additionally, video locks will fail
 * when pixels represented by `__self'  cannot represented as a video  lock
 * (e.g.  the Clip-  and I/O-Rects don't  match, or the  Clip Rect's bounds
 * don't end up at some whole-byte boundary,  or don't end up aligned to  a
 * degree that is  sufficient for  the codec  of `__self',  or `__self'  is
 * making using of some rotation/mirror GFX flags).
 *
 * If you want to guaranty that the returned buffer is still lockable, you
 * should wrap it again using `video_buffer_lockable()'.
 *
 * @return: * :   A video buffer representing the Clip Rect of `__self'
 * @return: NULL: [errno=ENOMEM] Insufficient memory. */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_FROMGFX)(struct video_gfx const *__restrict __self);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_fromgfx(struct video_gfx const *__restrict __self);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Various functions  for opening  a file/stream/blob  as an  image  file.
 * The actual file format is  auto-detected, and supported formats  depend
 * on installed 3rd party libraries. By default, BMP and PNG is supported. */
typedef __ATTR_WUNUSED_T __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_MOPEN)(void const *__blob, __size_t __blob_size);
typedef __ATTR_WUNUSED_T __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_FOPEN)(__FILE *__restrict __fp);
typedef __ATTR_WUNUSED_T __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_FDOPEN)(__fd_t __fd);
typedef __ATTR_WUNUSED_T __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_OPEN)(char const *__filename);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_mopen(void const *__blob, __size_t __blob_size);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_fopen(__FILE *__restrict __fp);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_fdopen(__fd_t __fd);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_open(char const *__filename);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Do the inverse of `video_buffer_*open' and save the contents of a video buffer
 * into  a file/memory/stream. The same set of  file formats is supported as also
 * supported by `video_buffer_*open', and the intended file format is  determined
 * by the given `format' argument, which should be the case-insensitive extension
 * (without a leading ".") of the format (e.g. "png" for PNG files).
 * @param: self:     The video buffer to save to a file.
 * @param: format:   The format to use for the output file written.
 * @param: fp/fd:    Output file descriptor / stdio-stream
 * @param: filename: Output filename ("format" is detected from file extension)
 * @param: options:  ","-separated string of format-specific encoding  options.
 *                   Available options are not explicitly document here, so you
 *                   need  to look at  the source to see  what's there. You may
 *                   simply pass `NULL' to use defaults for everything.
 * @return: 0 : Success
 * @return: -1: [errno=ENOTSUP] Unsupported `format'
 * @return: -1: Error (s.a. `errno') */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) int
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_FSAVE)(struct video_buffer *__self, char const *__format,
                                       __FILE *__restrict __fp, char const *__options);
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) int
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_FDSAVE)(struct video_buffer *__self, char const *__format,
                                        __fd_t __fd, char const *__options);
typedef /*__ATTR_WUNUSED_T*/ __ATTR_NONNULL_T((1, 2)) int
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_SAVE)(struct video_buffer *__self, char const *__filename,
                                      char const *__options);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int LIBVIDEO_GFX_CC
video_buffer_fsave(struct video_buffer *__self, char const *__format,
                   __FILE *__restrict __fp, char const *__options);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int LIBVIDEO_GFX_CC
video_buffer_fdsave(struct video_buffer *__self, char const *__format,
                    __fd_t __fd, char const *__options);
LIBVIDEO_GFX_DECL /*__ATTR_WUNUSED*/ __ATTR_NONNULL((1, 2)) int LIBVIDEO_GFX_CC
video_buffer_save(struct video_buffer *__self, char const *__filename,
                  char const *__options);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Return the preferred video format.
 * If  possible, this format will match the format used by the host's graphics card.
 * If no graphics card exists, or the card isn't clear on its preferred format, some
 * other, common format will be returned instead. */
typedef __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_format const *
(LIBVIDEO_GFX_CC *PVIDEO_PREFERRED_FORMAT)(void);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_RETNONNULL __ATTR_WUNUSED struct video_format const *
LIBVIDEO_GFX_CC video_preferred_format(void);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_BUFFER_H */
