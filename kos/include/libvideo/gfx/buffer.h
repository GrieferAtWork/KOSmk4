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

/* Video buffer types. */
#define VIDEO_BUFFER_AUTO 0x0000 /* Type doesn't matter. */
#define VIDEO_BUFFER_RAM  0x0001 /* RAM buffer. */
#define VIDEO_BUFFER_GPU  0x0002 /* GPU buffer. */

#ifdef __CC__
__DECL_BEGIN

struct video_format;

struct video_lock {
	__byte_t *vl_data;      /* [1..vl_size] Memory-mapped video data. */
	__size_t  vl_size;      /* Total image size (>= vl_stride * :vb_size_y) */
	__size_t  vl_stride;    /* Scanline width (in bytes) */
	void     *vl_driver[1]; /* Driver-specific data */
};

struct video_buffer_rect {
	video_offset_t vbr_startx; /* Starting X coord */
	video_offset_t vbr_starty; /* Starting Y coord */
	video_dim_t    vbr_sizex;  /* Rect size in X */
	video_dim_t    vbr_sizey;  /* Rect size in Y */
};

struct video_buffer_ops {
	/* NOTE: _ALL_ Callbacks are always [1..1] */

	/* Buffer finalization. */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_CC *vi_destroy)(struct video_buffer *__restrict __self);

	/* Get graphics functions for use with the given buffer
	 * @param: blendmode: Pixel blending mode  for graphics operations  targeting this  buffer.
	 *                    This  argument   should  be   constructed  using   `GFX_BLENDINFO()'.
	 *                    Usually, you will want to use `GFX_BLENDINFO_ALPHA' as blending  mode
	 *                    when you wish to make use of alpha-blending. However, if you know for
	 *                    certain  that alpha-blending isn't required, graphics performance can
	 *                    be improved by passing  `GFX_BLENDINFO_OVERRIDE' in order to  prevent
	 *                    any overhead  that would  normally  incur from  blending  operations.
	 * @param: flags:     Set of `VIDEO_GFX_F*'
	 * @param: colorkey:  A specific color that should always return fully opaque when read
	 *                    To disable colorkey-ing, simply pass some color with ALPHA=0  (or
	 *                    alternatively, just pass `0' (which would be one such color))
	 * @return: * : Always re-returns `__result' */
	__ATTR_RETNONNULL __ATTR_NONNULL_T((1, 2)) struct video_gfx *
	(LIBVIDEO_GFX_CC *vi_getgfx)(struct video_buffer *__restrict __self,
	                             struct video_gfx *__restrict __result,
	                             gfx_blendmode_t __blendmode, __uintptr_t __flags,
	                             video_color_t __colorkey);

	/* Disable blending for `self', which uses this video buffer.
	 * CAUTION: Only use this operator on a freshly copied/created GFX  context.
	 *          If the given context is already in use (especially if by another
	 *          thread), use of this function may result in a crash. */
	__ATTR_NONNULL_T((1)) struct video_gfx *
	(LIBVIDEO_GFX_CC *vi_gfx_noblend)(struct video_gfx *__restrict __self);

	void (*_vi_pad1[5])(void);

	/* Lock the video buffer into memory for reading.
	 * WARNING: Attempting to perform "gfx" operations on "this" while  holding
	 *          a  lock to video  memory may block and/or  be much slower until
	 *          said lock is released! The reason for this is that it is unsafe
	 *          to use hardware accelerated 2D operations while a video lock is
	 *          being held!
	 * @return: 0:  Success
	 * @return: -1: Error (s.a. `errno') */
	__ATTR_NONNULL_T((1, 2)) int
	(LIBVIDEO_GFX_CC *vi_rlock)(struct video_buffer *__restrict __self,
	                            struct video_lock *__restrict __result);

	/* Same as `vi_rlock', but also lock for reading+writing */
	__ATTR_NONNULL_T((1, 2)) int
	(LIBVIDEO_GFX_CC *vi_wlock)(struct video_buffer *__restrict __self,
	                            struct video_lock *__restrict __result);

	/* Unlock a video buffer that had previously been mapped into memory. */
	__ATTR_NONNULL_T((1, 2)) void
	__NOTHROW_T(LIBVIDEO_GFX_CC *vi_unlock)(struct video_buffer *__restrict __self,
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


#ifdef __cplusplus
__CXXDECL_BEGIN
#endif /* __cplusplus */

struct video_buffer {
	__uintptr_t              vb_refcnt; /* Reference counter. */
	struct video_buffer_ops *vb_ops;    /* [1..1][const] Buffer operations. */
	struct video_format      vb_format; /* [const] Buffer format. */
	video_dim_t              vb_size_x; /* Buffer size in X (in pixels) */
	video_dim_t              vb_size_y; /* Buffer size in Y (in pixels) */
	/* Buffer-specific fields go here */

#define video_buffer_rlock(self, lock) \
	(*(self)->vb_ops->vi_rlock)(self, lock)
#define video_buffer_wlock(self, lock) \
	(*(self)->vb_ops->vi_wlock)(self, lock)
#define video_buffer_unlock(self, lock) \
	(*(self)->vb_ops->vi_unlock)(self, lock)
#define video_buffer_getgfx(self, result, blendmode, flags, colorkey) \
	(*(self)->vb_ops->vi_getgfx)(self, result, blendmode, flags, colorkey)

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
	__CXX_CLASSMEMBER __ATTR_WUNUSED __ATTR_NONNULL_CXX((1))
	int LIBVIDEO_GFX_CC rlock(struct video_lock &__lock) {
		return video_buffer_rlock(this, &__lock);
	}

	/* Same as `vi_rlock', but also lock for reading+writing */
	__CXX_CLASSMEMBER __ATTR_WUNUSED __ATTR_NONNULL_CXX((1))
	int LIBVIDEO_GFX_CC wlock(struct video_lock &__lock) {
		return video_buffer_wlock(this, &__lock);
	}

	/* Unlock a video buffer that has previously been mapped into memory. */
	__CXX_CLASSMEMBER __ATTR_NONNULL_CXX((1))
	void LIBVIDEO_GFX_CC unlock(struct video_lock &__lock) {
		video_buffer_unlock(this, &__lock);
	}


	/* Get graphics functions for use with the given buffer
	 * @param: flags: Set of `VIDEO_GFX_F*' */
	__CXX_CLASSMEMBER struct video_gfx &LIBVIDEO_GFX_CC
	getgfx(struct video_gfx &__result,
	       gfx_blendmode_t __blendmode = GFX_BLENDINFO_OVERRIDE,
	       __uintptr_t __flags         = VIDEO_GFX_FNORMAL,
	       video_color_t __colorkey    = 0) {
		return *video_buffer_getgfx(this, &__result, __blendmode, __flags, __colorkey);
	}

	/* Get graphics functions for use with the given buffer
	 * @param: flags: Set of `VIDEO_GFX_F*' */
	__CXX_CLASSMEMBER struct video_gfx LIBVIDEO_GFX_CC
	getgfx(gfx_blendmode_t __blendmode = GFX_BLENDINFO_OVERRIDE,
	       __uintptr_t __flags         = VIDEO_GFX_FNORMAL,
	       video_color_t __colorkey    = 0) {
		struct video_gfx __result;
		video_buffer_getgfx(this, &__result, __blendmode, __flags, __colorkey);
		return __result;
	}

#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
	/* Convert `__self' into the specified format.
	 * @param: type: The type of buffer to-be returned (one of `VIDEO_BUFFER_*'). */
	__CXX_CLASSMEMBER __REF struct video_buffer *LIBVIDEO_GFX_CC
	convert(struct video_codec const *__codec, struct video_palette *__palette,
	        unsigned int __type = VIDEO_BUFFER_AUTO) {
		return video_buffer_convert(this, __codec, __palette, __type);
	}
	__CXX_CLASSMEMBER __REF struct video_buffer *LIBVIDEO_GFX_CC
	convert(struct video_format const *__format,
	        unsigned int __type = VIDEO_BUFFER_AUTO) {
		return video_buffer_convert(this, __format->vf_codec, __format->vf_pal, __type);
	}
	__CXX_CLASSMEMBER __REF struct video_buffer *LIBVIDEO_GFX_CC
	convert(struct video_buffer const *__buffer_with_wanted_format,
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
 * @return: -1: [errno=ENOTSUP] Unsupported parameter in `options'
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
typedef __ATTR_RETNONNULL_T __ATTR_WUNUSED_T struct video_format const *(LIBVIDEO_GFX_CC *PVIDEO_PREFERRED_FORMAT)(void);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_RETNONNULL __ATTR_WUNUSED struct video_format const *LIBVIDEO_GFX_CC video_preferred_format(void);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_BUFFER_H */
