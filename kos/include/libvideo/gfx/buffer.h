/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBVIDEO_GFX_BUFFER_H
#define _LIBVIDEO_GFX_BUFFER_H 1

#include "api.h"

#include <__stdinc.h>
#include <features.h>

#include <hybrid/atomic.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/refcnt.h>

#include <libvideo/codec/format.h>
#include <libvideo/codec/pixel.h>

#include "gfx.h"

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

__DECL_BEGIN

#ifdef __CC__
struct video_format;

struct video_lock {
	__size_t  vl_stride; /* Scanline width (in bytes) */
	__size_t  vl_size;   /* Total image size (>= vl_stride * :vb_size_y) */
	__byte_t *vl_data;   /* [1..vl_size] Memory-mapped video data. */
};

struct video_buffer_rect {
	__uintptr_t vbr_startx; /* Starting X */
	__uintptr_t vbr_starty; /* Starting Y */
	__uintptr_t vbr_sizex;  /* Rect size in X */
	__uintptr_t vbr_sizey;  /* Rect size in Y */
};

struct video_buffer_ops {
	/* [1..1] Buffer finalization. */
	void (LIBVIDEO_GFX_CC *vi_destroy)(struct video_buffer *__restrict self);

	/* [1..1] Lock the video buffer into memory.
	 * @return: 0:  Success
	 * @return: -1: Error (s.a. `errno') */
	__ATTR_NONNULL((1, 2))
	int (LIBVIDEO_GFX_CC *vi_lock)(struct video_buffer *__restrict self,
	                               struct video_lock *__restrict result);

	/* [1..1] Unlock a video buffer that has previously been mapped into memory. */
	__ATTR_NONNULL((1, 2))
	void (LIBVIDEO_GFX_CC *vi_unlock)(struct video_buffer *__restrict self,
	                                  struct video_lock const *__restrict lock);

	/* All of the following functions can optionally be implemented by drivers.
	 * When not implemented, they are substituted during the driver installation
	 * process.
	 * In other words, then actually used, all of these functions are [1..1],
	 * but when a video driver needs to provide this interface, it can leave
	 * out these functions and have them filled automatically once the driver
	 * registers its video API. */

	/* Get graphics functions for use with the given buffer
	 * @param: blendmode: Pixel blending mode for graphics operations targeting this buffer.
	 *                    This argument should be constructed using `GFX_BLENDINFO()'.
	 *                    Usually, you will want to use `GFX_BLENDINFO_ALPHA' as blending mode
	 *                    when you wish to make use of alpha-blending. However, if you know for
	 *                    certain that alpha-blending isn't required, graphics performance can
	 *                    be improved by passing `GFX_BLENDINFO_OVERRIDE' in order to prevent
	 *                    any overhead that would normally incur from blending operations.
	 * @param: flags:     Set of `VIDEO_GFX_F*'
	 * @param: colorkey:  A specific color that should always return fully opaque when read
	 *                    To disable colorkey-ing, simply pass some color with ALPHA=0 (or
	 *                    alternatively, just pass `0' (which would be one such color))
	 * @param: clip:      When non-NULL, specify a clip-rect to which drawing should be restricted.
	 *                    All canvas coords will be relative to this rectangle, and and attempt to
	 *                    access a pixel outside this rect will be a no-op / appear to be fully opaque. */
	void (LIBVIDEO_GFX_CC *vi_getgfx)(struct video_buffer *__restrict self,
	                                  struct video_gfx *__restrict result,
	                                  gfx_blendmode_t blendmode, __uintptr_t flags,
	                                  video_color_t colorkey,
	                                  struct video_buffer_rect *clip);
};
#endif /* __CC__ */



#ifdef __CC__
struct video_buffer {
	__uintptr_t              vb_refcnt; /* Reference counter. */
	struct video_buffer_ops *vb_ops;    /* [1..1][const] Buffer operations. */
	struct video_format      vb_format; /* [const] Buffer format. */
	__uintptr_t              vb_size_x; /* Buffer size in X */
	__uintptr_t              vb_size_y; /* Buffer size in Y */
	/* Buffer-specific fields go here */

#ifdef __cplusplus
#ifndef GUARD_LIBVIDEO_GFX_API_H
	__CXX_DELETE_CTOR(video_buffer);
	__CXX_DELETE_DTOR(video_buffer);
	__CXX_DELETE_COPY(video_buffer);
	__CXX_DELETE_COPY_ASSIGN(video_buffer);
#endif /* !GUARD_LIBVIDEO_GFX_API_H */
public:

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("lock")
#pragma push_macro("unlock")
#pragma push_macro("gfx")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef lock
#undef unlock
#undef gfx

	/* Lock the video buffer into memory.
	 * @return: 0:  Success
	 * @return: -1: Error (s.a. `errno') */
	__CXX_CLASSMEMBER __ATTR_NONNULL((1))
	int LIBVIDEO_GFX_CC lock(struct video_lock &__lock) {
		return (*vb_ops->vi_lock)(this,&__lock);
	}

	/* Unlock a video buffer that has previously been mapped into memory. */
	__CXX_CLASSMEMBER __ATTR_NONNULL((1))
	void LIBVIDEO_GFX_CC unlock(struct video_lock const &__lock) {
		(*vb_ops->vi_unlock)(this, &__lock);
	}


	/* Get graphics functions for use with the given buffer
	 * @param: flags: Set of `VIDEO_GFX_F*' */
	__CXX_CLASSMEMBER struct video_gfx &LIBVIDEO_GFX_CC
	gfx(struct video_gfx &__result,
	    gfx_blendmode_t __blendmode    = GFX_BLENDINFO_ALPHA,
	    __uintptr_t __flags            = VIDEO_GFX_FNORMAL,
	    video_color_t __colorkey       = 0,
		struct video_buffer_rect *clip = __NULLPTR) {
		(*vb_ops->vi_getgfx)(this, &__result, __blendmode, __flags, __colorkey, clip);
		return __result;
	}

	/* Get graphics functions for use with the given buffer
	 * @param: flags: Set of `VIDEO_GFX_F*' */
	__CXX_CLASSMEMBER struct video_gfx LIBVIDEO_GFX_CC
	gfx(gfx_blendmode_t __blendmode    = GFX_BLENDINFO_ALPHA,
	    __uintptr_t __flags            = VIDEO_GFX_FNORMAL,
	    video_color_t __colorkey       = 0,
		struct video_buffer_rect *clip = __NULLPTR) {
		struct video_gfx __result;
		gfx(__result, __blendmode, __flags, __colorkey, clip);
		return __result;
	}

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("gfx")
#pragma pop_macro("unlock")
#pragma pop_macro("lock")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __cplusplus */
};

#define video_buffer_destroy(self) (*(self)->vb_ops->vi_destroy)(self)
#define video_buffer_incref(self) \
	__hybrid_atomic_fetchinc((self)->vb_refcnt, __ATOMIC_SEQ_CST)
#define video_buffer_decref(self)                                     \
	(__hybrid_atomic_decfetch((self)->vb_refcnt, __ATOMIC_SEQ_CST) || \
	 (video_buffer_destroy(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_buffer, vb_refcnt, video_buffer_destroy)
#endif /* __CC__ */


/* Video buffer types. */
#define VIDEO_BUFFER_AUTO 0x0000  /* Type doesn't matter. */
#define VIDEO_BUFFER_RAM  0x0001  /* RAM buffer. */
#define VIDEO_BUFFER_GPU  0x0002  /* GPU buffer. */


#ifdef __CC__

/* Create a video buffer, or return NULL and set errno if creation failed.
 * NOTE: When the given `size_x' or `size_y' is ZERO(0), an empty buffer is returned
 *       which may not necessarily use the given, or default `codec' and `palette'
 * @param: codec:   The preferred video codec, or NULL to use `video_preferred_format()'.
 * @param: palette: The palette to use (only needed if used by `codec') */
typedef __ATTR_WUNUSED __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_CREATE)(unsigned int type, __size_t size_x, __size_t size_y,
                                        struct video_codec *codec, struct video_palette *palette);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_create(unsigned int type, __size_t size_x, __size_t size_y,
                    struct video_codec *codec, struct video_palette *palette);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

/* Returns a video buffer for the entire screen (or return NULL and set errno on error)
 * Note that screen buffer access is only granted to ROOT and the window server */
typedef __ATTR_WUNUSED __REF struct video_buffer *(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_SCREEN)(void);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_buffer *LIBVIDEO_GFX_CC video_buffer_screen(void);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

/* Return the preferred video format.
 * If possible, this format will match the format used by the host's graphics card.
 * If no graphics card exists, or the card isn't clear on its preferred format, some
 * other, common format will be returned instead. */
typedef __ATTR_WUNUSED __ATTR_RETNONNULL struct video_format const *(LIBVIDEO_GFX_CC *PVIDEO_PREFERRED_FORMAT)(void);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_RETNONNULL struct video_format const *LIBVIDEO_GFX_CC video_preferred_format(void);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

/* Return a handle for the video device driver that is being used.
 * @return: -1:errno=ENODEV: No video driver found */
typedef __ATTR_WUNUSED __fd_t (LIBVIDEO_GFX_CC *PVIDEO_DRIVER)(void);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __fd_t LIBVIDEO_GFX_CC video_driver(void);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

#endif /* __CC__ */



__DECL_END

#endif /* !_LIBVIDEO_GFX_BUFFER_H */
