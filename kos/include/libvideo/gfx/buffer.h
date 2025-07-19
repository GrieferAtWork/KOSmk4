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
/**/

#include <__crt.h> /* __FILE */
#include <__stdinc.h>

#include <hybrid/__atomic.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/refcnt.h>

#include <libvideo/codec/format.h>

#include "../color.h"
#include "../crect.h"
#include "blend.h"
#include "gfx.h"

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

/* Possible values for `video_domain_newbuffer()::__flags' */
#define VIDEO_DOMAIN_NEWBUFFER_F_NORMAL 0x0000 /* Normal flags */
#define VIDEO_DOMAIN_NEWBUFFER_F_CALLOC 0x0001 /* Require pixel data to be zero-initialized */

/* Possible values for `video_domain_formem()::__flags' */
#define VIDEO_DOMAIN_FORMEM_F_NORMAL 0x0000 /* Normal flags */
#define VIDEO_DOMAIN_FORMEM_F_SHARED 0x0002 /* Force creation */

#ifdef __CC__
__DECL_BEGIN

struct video_format;
struct video_gfx;
struct video_domain;
struct video_codec;
struct video_palette;
struct video_rect;


/* Video-domain: Low-level driver interface for creation of video buffers */
struct video_domain {
	/* Create a video buffer, or return NULL and set errno if creation failed.
	 * NOTE: When  the given  `__xdim' or `__ydim'  is ZERO(0), an  empty buffer is
	 *       returned which may not necessarily use the given `codec' and `palette'
	 * @param: __self:   Associated video domain
	 * @param: __xdim:   X Dimension
	 * @param: __ydim:   Y Dimension
	 * @param: __format: The used video format.
	 * @param: __flags:  Set of `VIDEO_DOMAIN_NEWBUFFER_F_*'
	 * @return: * :   The newly created video buffer
	 * @return: NULL: [errno=ENOMEM]  Insufficient memory (either regular RAM, or V-RAM)
	 * @return: NULL: [errno=ENOTSUP] Given `__format->vf_codec'  is not  supported by  this
	 *                                domain (only `video_ramdomain()' supports all formats)
	 * @return: NULL: [errno=*] Failed to construct video buffer for some other reason */
	__ATTR_WUNUSED_T __ATTR_IN_T(4) __ATTR_NONNULL_T((1)) __REF struct video_buffer *
	(LIBVIDEO_GFX_CC *vd_newbuffer)(struct video_domain const *__restrict __self,
	                                video_dim_t __xdim, video_dim_t __ydim,
	                                struct video_format const *__restrict __format,
	                                unsigned int __flags);
	__ATTR_WUNUSED_T __ATTR_IN_T(4) __ATTR_NONNULL_T((1)) __REF struct video_buffer *
	(LIBVIDEO_GFX_CC *vd_newbuffer_ex)(struct video_domain const *__restrict __self,
	                                   video_dim_t __xdim, video_dim_t __ydim,
	                                   struct video_codec_specs const *__restrict __codec_specs,
	                                   struct video_palette *__palette, unsigned int __flags);

	/* Create  a video buffer  that interfaces with  a pre-existing buffer whose
	 * base address is located at `mem' (which consists of `__stride * __size_y'
	 * bytes). When non-NULL, `(*__release_mem)(__release_mem_cookie, __mem)' is
	 * called when `__mem' is no longer needed. This happens in 2 cases:
	 * - When the video domain  can make use of  regular RAM, or `__mem'  points
	 *   into an area of memory that is  being managed by the this domain  (iow:
	 *   is a fixed host mapping of V-RAM), then the returned video buffer *may*
	 *   actually reference this memory directly.
	 *   - In this case, `__release_mem' is only called once all referenced to the
	 *     returned video buffer have been released.
	 *   - If this behavior is required, you can pass `VIDEO_DOMAIN_FORMEM_F_SHARED'
	 *     to have this function fail if the given `__mem' cannot be directly worked
	 *     with by the video domain `__self'.
	 * - Otherwise, this function simply creates a new buffer using `vd_newbuffer',
	 *   before copying `__mem' into that buffer that calling `__release_mem' prior
	 *   to returning normally.
	 *
	 * @param: __self:   Associated video domain
	 * @param: __mem:    Base address of the pre-loaded memory buffer.
	 *                   If this location isn't writable, and the returned buffer
	 *                   ends up sharing memory with this blob, attempts to write
	 *                   pixel data of the returned buffer *may* SEGFAULT.
	 * @param: __xdim:   Width of returned buffer
	 * @param: __ydim:   Height of returned buffer
	 * @param: __stride: Scanline width in `mem'
	 * @param: __format: The video codec+palette that describes how `mem' is encoded.
	 * @param: __release_mem: Optional callback invoked when the returned buffer is destroyed
	 * @param: __release_mem_cookie: Cookie argument for `__release_mem'
	 * @param: __flags:  Set of `VIDEO_DOMAIN_FORMEM_F_*'
	 * @return: * :   The newly created video buffer
	 * @return: NULL: [errno=EINVAL] Given `stride' is too small for `codec' and `size_y'
	 * @return: NULL: [errno=ENOMEM] Insufficient memory
	 * @return: NULL: [errno=ENOTSUP] Given `__format->vf_codec'  is not  supported by  this
	 *                                domain (only `video_ramdomain()' supports all formats)
	 * @return: NULL: [errno=EFAULT] `VIDEO_DOMAIN_FORMEM_F_SHARED' was given, but not supported by `__mem'
	 * @return: NULL: [errno=*] Failed to construct video buffer for some other reason */
	__ATTR_WUNUSED_T __ATTR_IN_T(4) __ATTR_NONNULL_T((1, 5)) __REF struct video_buffer *
	(LIBVIDEO_GFX_CC *vd_formem)(struct video_domain const *__restrict __self, video_dim_t __xdim, video_dim_t __ydim,
	                             struct video_format const *__format, void *__mem, __size_t __stride,
	                             void (LIBVIDEO_GFX_CC *__release_mem)(void *__cookie, void *__mem),
	                             void *__release_mem_cookie, unsigned int __flags);
	__ATTR_WUNUSED_T __ATTR_IN_T(4) __ATTR_NONNULL_T((1, 6)) __REF struct video_buffer *
	(LIBVIDEO_GFX_CC *vd_formem_ex)(struct video_domain const *__restrict __self, video_dim_t __xdim, video_dim_t __ydim,
	                                struct video_codec_specs const *__restrict __codec_specs,
	                                struct video_palette *__palette, void *__mem, __size_t __stride,
	                                void (LIBVIDEO_GFX_CC *__release_mem)(void *__cookie, void *__mem),
	                                void *__release_mem_cookie, unsigned int __flags);

	/* Return the closest (by criteria of features and appearance) supported codec to "__codec"
	 * This  function never returns `NULL', even if the domain only supports a single codec, in
	 * which case this function simply always returns that codec.
	 *
	 * HINT: `video_ramdomain()' implements this function by always re-returning `__codec' */
	__ATTR_RETNONNULL_T __ATTR_WUNUSED_T __ATTR_IN_T(2) __ATTR_NONNULL_T((1)) struct video_codec const *
	(LIBVIDEO_GFX_CC *vd_supported_codec)(struct video_domain const *__restrict __self,
	                                      struct video_codec const *__restrict __codec);

	void (*_vd_pad[11])(void); /* Reserved for future expansion */

	/* TODO: Function for getting memory usage (for the ram-domain,
	 *       just return regular ram usage info as per `sysinfo(2)) */

	/* TODO: Function  for creating video palettes also need  to go here (so translation data
	 *       can be stored server-side in case of a window server, or in V-RAM so-as to speed
	 *       up palette conversion blits) */
};


/* Returns the default, built-in "RAM" video domain.
 *
 * Video buffers allocated by / using this domain are driven
 * by  software-only  (without  any  hardware  acceleration)
 *
 * On the plus side: these buffers are generally able to do
 * much more than buffers from hardware domains, given that
 * they can support **any** video codec. */
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T
struct video_domain const *(LIBVIDEO_GFX_CC *PVIDEO_RAMDOMAIN)(void);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED
struct video_domain const *LIBVIDEO_GFX_CC video_ramdomain(void);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


#ifdef __INTELLISENSE__
/* Create a video buffer, or return NULL and set errno if creation failed.
 * NOTE: When  the given  `__xdim' or `__ydim'  is ZERO(0), an  empty buffer is
 *       returned which may not necessarily use the given `codec' and `palette'
 * @param: __self:   Associated video domain
 * @param: __xdim:   X Dimension
 * @param: __ydim:   Y Dimension
 * @param: __format: The used video format.
 * @param: __flags:  Set of `VIDEO_DOMAIN_NEWBUFFER_F_*'
 * @return: * :   The newly created video buffer
 * @return: NULL: [errno=ENOMEM]  Insufficient memory (either regular RAM, or V-RAM)
 * @return: NULL: [errno=ENOTSUP] Given `__format->vf_codec'  is not  supported by  this
 *                                domain (only `video_ramdomain()' supports all formats)
 * @return: NULL: [errno=*] Failed to construct video buffer for some other reason */
extern __ATTR_WUNUSED __ATTR_IN(4) __ATTR_NONNULL((1)) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_domain_newbuffer(struct video_domain const *__restrict __self,
                       video_dim_t __xdim, video_dim_t __ydim,
                       struct video_format const *__restrict __format,
                       unsigned int __flags);
extern __ATTR_WUNUSED __ATTR_IN(4) __ATTR_NONNULL((1)) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_domain_newbuffer_ex(struct video_domain const *__restrict __self,
                          video_dim_t __xdim, video_dim_t __ydim,
                          struct video_codec_specs const *__restrict __codec_specs,
                          struct video_palette *__palette, unsigned int __flags);

/* Create  a video buffer  that interfaces with  a pre-existing buffer whose
 * base address is located at `mem' (which consists of `__stride * __size_y'
 * bytes). When non-NULL, `(*__release_mem)(__release_mem_cookie, __mem)' is
 * called when `__mem' is no longer needed. This happens in 2 cases:
 * - When the video domain  can make use of  regular RAM, or `__mem'  points
 *   into an area of memory that is  being managed by the this domain  (iow:
 *   is a fixed host mapping of V-RAM), then the returned video buffer *may*
 *   actually reference this memory directly.
 *   - In this case, `__release_mem' is only called once all referenced to the
 *     returned video buffer have been released.
 *   - If this behavior is required, you can pass `VIDEO_DOMAIN_FORMEM_F_SHARED'
 *     to have this function fail if the given `__mem' cannot be directly worked
 *     with by the video domain `__self'.
 * - Otherwise, this  function  simply  creates a  new  buffer  using
 *   `video_domain_newbuffer',  before  copying  `__mem'  into   that
 *   buffer that calling `__release_mem' prior to returning normally.
 *
 * @param: __self:   Associated video domain
 * @param: __mem:    Base address of the pre-loaded memory buffer.
 *                   If this location isn't writable, and the returned buffer
 *                   ends up sharing memory with this blob, attempts to write
 *                   pixel data of the returned buffer *may* SEGFAULT.
 * @param: __xdim:   Width of returned buffer
 * @param: __ydim:   Height of returned buffer
 * @param: __stride: Scanline width in `mem'
 * @param: __format: The video codec+palette that describes how `mem' is encoded.
 * @param: __release_mem: Optional callback invoked when the returned buffer is destroyed
 * @param: __release_mem_cookie: Cookie argument for `__release_mem'
 * @param: __flags:  Set of `VIDEO_DOMAIN_FORMEM_F_*'
 * @return: * :   The newly created video buffer
 * @return: NULL: [errno=EINVAL] Given `stride' is too small for `codec' and `size_y'
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=ENOTSUP] Given `__format->vf_codec'  is not  supported by  this
 *                                domain (only `video_ramdomain()' supports all formats)
 * @return: NULL: [errno=EFAULT] `VIDEO_DOMAIN_FORMEM_F_SHARED' was given, but not supported by `__mem'
 * @return: NULL: [errno=*] Failed to construct video buffer for some other reason */
extern __ATTR_WUNUSED __ATTR_IN(4) __ATTR_NONNULL((1, 5)) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_domain_formem(struct video_domain const *__restrict __self, video_dim_t __xdim, video_dim_t __ydim,
                    struct video_format const *__format, void *__mem, __size_t __stride,
                    void (LIBVIDEO_GFX_CC *__release_mem)(void *__cookie, void *__mem),
                    void *__release_mem_cookie, unsigned int __flags);
extern __ATTR_WUNUSED __ATTR_IN(4) __ATTR_NONNULL((1, 6)) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_domain_formem_ex(struct video_domain const *__restrict __self, video_dim_t __xdim, video_dim_t __ydim,
                       struct video_codec_specs const *__restrict __codec_specs,
                       struct video_palette *__palette, void *__mem, __size_t __stride,
                       void (LIBVIDEO_GFX_CC *__release_mem)(void *__cookie, void *__mem),
                       void *__release_mem_cookie, unsigned int __flags);

/* Return the closest (by criteria of features and appearance) supported codec to "__codec"
 * This  function never returns `NULL', even if the domain only supports a single codec, in
 * which case this function simply always returns that codec.
 *
 * HINT: `video_ramdomain()' implements this function by always re-returning `__codec' */
extern __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_NONNULL((1)) struct video_codec const *LIBVIDEO_GFX_CC
video_domain_supported_codec(struct video_domain const *__restrict __self,
                             struct video_codec const *__restrict __codec);
#else /* __INTELLISENSE__ */
#define video_domain_newbuffer(self, xdim, ydim, format, flags) \
	(*(self)->vd_newbuffer)(self, xdim, ydim, format, flags)
#define video_domain_newbuffer_ex(self, xdim, ydim, codec_specs, palette, flags) \
	(*(self)->vd_newbuffer_ex)(self, xdim, ydim, codec_specs, palette, flags)
#define video_domain_formem(self, xdim, ydim, format, mem, stride, release_mem, release_mem_cookie, flags) \
	(*(self)->vd_formem)(self, xdim, ydim, format, mem, stride, release_mem, release_mem_cookie, flags)
#define video_domain_formem_ex(self, xdim, ydim, codec_specs, palette, mem, stride, release_mem, release_mem_cookie, flags) \
	(*(self)->vd_formem_ex)(self, xdim, ydim, codec_specs, palette, mem, stride, release_mem, release_mem_cookie, flags)
#define video_domain_supported_codec(self, codec) \
	(*(self)->vd_supported_codec)(self, codec)
#endif /* !__INTELLISENSE__ */




struct video_lock {
	/* WARNING: DO NOT MODIFY ANYTHING HERE BEFORE `video_buffer_unlock()' */
	__byte_t *vl_data;   /* [1..vl_size] Memory-mapped video dat (never "NULL") */
	__size_t  vl_stride; /* Scanline width (in bytes) */
#define _VIDEO_LOCK__N_DRIVER 1
	void *_vl_driver[_VIDEO_LOCK__N_DRIVER]; /* Driver-specific data */
};

struct video_regionlock {
	/* WARNING: DO NOT MODIFY ANYTHING HERE BEFORE `video_buffer_unlockregion()' */
	struct video_lock   vrl_lock; /* [out] Underlying video lock */
	video_coord_t       vrl_xbas; /* [out] X-offset added to start of every scanline */
	struct video_crect _vrl_rect; /* [in][const] Region */
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

	void (*_vi_pad1[5])(void);

	/* Lock the video buffer into memory for reading.
	 * WARNING: Attempting to perform "gfx" operations on "this" while  holding
	 *          a  lock to video  memory may block and/or  be much slower until
	 *          said lock is released! The reason for this is that it is unsafe
	 *          to use hardware accelerated 2D operations while a video lock is
	 *          being held!
	 * @return: 0:  Success
	 * @return: -1: Error (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_OUT_T(2) int
	(LIBVIDEO_GFX_FCC *vi_rlock)(struct video_buffer *__restrict __self,
	                             struct video_lock *__restrict __lock);

	/* Same as `vi_rlock', but also lock for reading+writing */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_OUT_T(2) int
	(LIBVIDEO_GFX_FCC *vi_wlock)(struct video_buffer *__restrict __self,
	                             struct video_lock *__restrict __lock);

	/* Unlock a video buffer that had previously been mapped into memory. */
	__ATTR_INOUT_T(1) __ATTR_IN_T(2) void
	__NOTHROW_T(LIBVIDEO_GFX_FCC *vi_unlock)(struct video_buffer *__restrict __self,
	                                         struct video_lock *__restrict __lock);

	/* Same as `vi_rlock', but possibly more efficient, as only a specific
	 * sub-region is being  locked, rather than  the entire video  buffer.
	 *
	 * Also: this function may succeed in cases where `vi_rlock' fails.
	 *
	 * @assume(__lock->_vrl_rect.vcr_xdim > 0);
	 * @assume(__lock->_vrl_rect.vcr_ydim > 0);
	 * @assume((__lock->_vrl_rect.vcr_xmin + __lock->_vrl_rect.vcr_xdim) > __lock->_vrl_rect.vcr_xmin);
	 * @assume((__lock->_vrl_rect.vcr_ymin + __lock->_vrl_rect.vcr_ydim) > __lock->_vrl_rect.vcr_ymin);
	 * @assume((__lock->_vrl_rect.vcr_xmin + __lock->_vrl_rect.vcr_xdim) <= __self->vb_xdim);
	 * @assume((__lock->_vrl_rect.vcr_ymin + __lock->_vrl_rect.vcr_ydim) <= __self->vb_ydim);
	 *
	 * @return: 0:  Success
	 * @return: -1: Error (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_INOUT_T(2) int
	(LIBVIDEO_GFX_FCC *vi_rlockregion)(struct video_buffer *__restrict __self,
	                                   struct video_regionlock *__restrict __lock);

	/* Same as `vi_wlock', but possibly more efficient, as only a specific
	 * sub-region is being  locked, rather than  the entire video  buffer.
	 *
	 * Also: this function may succeed in cases where `vi_wlock' fails.
	 *
	 * @assume(__lock->_vrl_rect.vcr_xdim > 0);
	 * @assume(__lock->_vrl_rect.vcr_ydim > 0);
	 * @assume((__lock->_vrl_rect.vcr_xmin + __lock->_vrl_rect.vcr_xdim) > __lock->_vrl_rect.vcr_xmin);
	 * @assume((__lock->_vrl_rect.vcr_ymin + __lock->_vrl_rect.vcr_ydim) > __lock->_vrl_rect.vcr_ymin);
	 * @assume((__lock->_vrl_rect.vcr_xmin + __lock->_vrl_rect.vcr_xdim) <= __self->vb_xdim);
	 * @assume((__lock->_vrl_rect.vcr_ymin + __lock->_vrl_rect.vcr_ydim) <= __self->vb_ydim);
	 *
	 * @return: 0:  Success
	 * @return: -1: Error (s.a. `errno') */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_INOUT_T(2) int
	(LIBVIDEO_GFX_FCC *vi_wlockregion)(struct video_buffer *__restrict __self,
	                                   struct video_regionlock *__restrict __lock);

	/* Release a video region lock that had previously been acquired using the above operators. */
	__ATTR_INOUT_T(1) __ATTR_NONNULL_T((2)) void
	__NOTHROW_T(LIBVIDEO_GFX_FCC *vi_unlockregion)(struct video_buffer *__restrict __self,
	                                               struct video_regionlock *__restrict __lock);


	/* Buffer revocation / sub-region operators */

	/* Revoke access to non-anonymous pixel data (and maybe even anonymous) of this video buffer.
	 * Access  to pixel data of any sub-region created from `__self' (or recursively created form
	 * one of those buffers) is also revoked.
	 *
	 * All types of video buffers can have their access revoked, except for buffers returned by
	 * `video_domain_newbuffer[_ex]()' (though sub-region buffers of those can be revoked,  and
	 * calling this function for one such buffer will do exactly that).
	 *
	 * @return: * : Always re-returns `__self' */
	__ATTR_RETNONNULL_T __ATTR_INOUT_T(1) struct video_buffer *
	__NOTHROW_T(LIBVIDEO_GFX_FCC *vi_revoke)(struct video_buffer *__restrict __self);


	/* Create a new hard subregion-proxy of `__self'. The caller is responsible to  ensure
	 * that the given `__rect' does not exceed `__self->vb_xdim' / `__self->vb_ydim'. Note
	 * that this function behaves slightly different from `video_buffer_region()', in that
	 * the  later accepts a signed rect, while also  allowing said rect to be greater than
	 * the dimensions of the original buffer.
	 *
	 * On the other hand, this function only works for creating **true** sub-rects, but
	 * since this one is implemented by individual buffers, it is probably faster, too.
	 *
	 * Buffers returned by this function are guarantied to share pixel access with `__self',
	 * and `vi_revoke' is to `__self' will also revoke access for `return' (either directly,
	 * by keeping a list of sub-region buffers  in `__self', or indirectly, by having  every
	 * access to pixel-data in `return' check if `__self' has been revoked).
	 *
	 * NOTE: This function will never re-return `__self', even if `__rect' is the  full
	 *       rect of `__self', and `__xor_flags == 0'. This is because doing also cause
	 *       `vi_revoke' invoked on the returned buffer to revoke `__self'.
	 *
	 * @assume(__rect->vcr_xdim > 0);
	 * @assume(__rect->vcr_ydim > 0);
	 * @assume((__rect->vcr_xmin + __rect->vcr_xdim) > __rect->vcr_xmin);
	 * @assume((__rect->vcr_ymin + __rect->vcr_ydim) > __rect->vcr_ymin);
	 * @assume((__rect->vcr_xmin + __rect->vcr_xdim) <= __self->vb_xdim);
	 * @assume((__rect->vcr_ymin + __rect->vcr_ydim) <= __self->vb_ydim);
	 * @param: __self: Video buffer to create a sub-region of
	 * @param: __rect: Sub-region rect of `__self' to-be returned
	 * @param: __xor_flags: Flags to xor- toggle in GFX contexts created on `return'.
	 *                      These flags are NOT applied  to `__rect', but they  still
	 *                      allow you to create  sub-region buffers that will  appear
	 *                      to be  natively rotated  in `struct video_gfx'  contexts.
	 *                      Only the following flags *should* be used here. All other
	 *                      flags can still be used, but many not necessarily produce
	 *                      expected results:
	 *                      - VIDEO_GFX_F_XMIRROR
	 *                      - VIDEO_GFX_F_YMIRROR
	 *                      - VIDEO_GFX_F_XYSWAP
	 * @return: * : The newly created sub-region buffer
	 * @return: NULL: [errno=ENOMEM] Insufficient memory
	 * @return: NULL: [errno=*] Failed to create sub-region for some other reason */
	__ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_IN_T(2) __REF struct video_buffer *
	(LIBVIDEO_GFX_FCC *vi_subregion)(struct video_buffer *__restrict __self,
	                                 struct video_crect const *__restrict __rect,
	                                 gfx_flag_t __xor_flags);
};




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
extern __ATTR_RETNONNULL __ATTR_INOUT(1) __ATTR_OUT(2) struct video_gfx *
video_buffer_getgfx(struct video_buffer *__self, struct video_gfx *__result,
                    gfx_blendmode_t __blendmode, gfx_flag_t __flags,
                    video_color_t __colorkey);



/* Lock the video buffer into memory for reading.
 * WARNING: Attempting to perform "gfx" operations on "this" while  holding
 *          a  lock to video  memory may block and/or  be much slower until
 *          said lock is released! The reason for this is that it is unsafe
 *          to use hardware accelerated 2D operations while a video lock is
 *          being held!
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) int
video_buffer_rlock(struct video_buffer *__self, struct video_lock *__lock);

/* Same as `vi_rlock', but also lock for reading+writing */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) int
video_buffer_wlock(struct video_buffer *__self, struct video_lock *__lock);

/* Unlock a video buffer that had previously been mapped into memory. */
extern __ATTR_INOUT(1) __ATTR_IN(2) void
video_buffer_unlock(struct video_buffer *__self, struct video_lock *__lock);



/* Same as  `video_buffer_rlock', but  possibly more  efficient, as  only  a
 * specific sub-region is being locked, rather than the entire video buffer.
 *
 * Also: this function may succeed in cases where `video_buffer_rlock' fails.
 *
 * @assume(__xdim > 0);
 * @assume(__ydim > 0);
 * @assume((__xmin + __xdim) > __xmin);
 * @assume((__ymin + __ydim) > __ymin);
 * @assume((__xmin + __xdim) <= __self->vb_xdim);
 * @assume((__ymin + __ydim) <= __self->vb_ydim);
 *
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) int
video_buffer_rlockregion(struct video_buffer *__self, struct video_regionlock *__lock,
                         video_coord_t __xmin, video_coord_t __ymin,
                         video_dim_t __xdim, video_dim_t __ydim);

/* Same as  `video_buffer_wlock', but  possibly more  efficient, as  only  a
 * specific sub-region is being locked, rather than the entire video buffer.
 *
 * Also: this function may succeed in cases where `video_buffer_wlock' fails.
 *
 * @assume(__xdim > 0);
 * @assume(__ydim > 0);
 * @assume((__xmin + __xdim) > __xmin);
 * @assume((__ymin + __ydim) > __ymin);
 * @assume((__xmin + __xdim) <= __self->vb_xdim);
 * @assume((__ymin + __ydim) <= __self->vb_ydim);
 *
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) int
video_buffer_wlockregion(struct video_buffer *__self, struct video_regionlock *__lock,
                         video_coord_t __xmin, video_coord_t __ymin,
                         video_dim_t __xdim, video_dim_t __ydim);

/* Release a video  region lock that  had previously been  acquired
 * by `video_buffer_rlockregion()' or `video_buffer_wlockregion()'. */
extern __ATTR_INOUT(1) __ATTR_NONNULL((2)) void
video_buffer_unlockregion(struct video_buffer *__self, struct video_regionlock *__lock);
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
#define video_buffer_rlockregion(self, lock, xmin, ymin, xdim, ydim)           \
	((lock)->_vrl_rect.vcr_xmin = (xmin), (lock)->_vrl_rect.vcr_ymin = (ymin), \
	 (lock)->_vrl_rect.vcr_xdim = (xdim), (lock)->_vrl_rect.vcr_ydim = (ydim), \
	 (*(self)->vb_ops->vi_rlockregion)(self, lock))
#define video_buffer_wlockregion(self, lock, xmin, ymin, xdim, ydim)           \
	((lock)->_vrl_rect.vcr_xmin = (xmin), (lock)->_vrl_rect.vcr_ymin = (ymin), \
	 (lock)->_vrl_rect.vcr_xdim = (xdim), (lock)->_vrl_rect.vcr_ydim = (ydim), \
	 (*(self)->vb_ops->vi_wlockregion)(self, lock))
#define video_buffer_unlockregion(self, lock) \
	(*(self)->vb_ops->vi_unlockregion)(self, lock)
#endif /* !__INTELLISENSE__ */


#ifdef __cplusplus
__CXXDECL_BEGIN
#endif /* __cplusplus */

struct video_buffer {
	struct video_buffer_ops const *vb_ops;    /* [1..1][const] Buffer operations. */
	struct video_domain const     *vb_domain; /* [1..1][const] Buffer domain. */
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


#if 1 /* TODO: BEGIN DEPRECATED */

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

#endif /* TODO: END DEPRECATED */


/* Convert `__self' into the specified domain and format. */
typedef __ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_NONNULL_T((2)) __ATTR_IN_T(3) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_CONVERT)(struct video_buffer *__restrict __self,
                                         struct video_domain const *__domain,
                                         struct video_format const *__format);
typedef __ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_NONNULL_T((2)) __ATTR_IN_T(3) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_CONVERT_OR_COPY)(struct video_buffer *__restrict __self,
                                                 struct video_domain const *__domain,
                                                 struct video_format const *__format);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_NONNULL((2)) __ATTR_IN(3) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_convert(struct video_buffer *__restrict __self,
                     struct video_domain const *__domain,
                     struct video_format const *__format);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_NONNULL((2)) __ATTR_IN(3) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_convert_or_copy(struct video_buffer *__restrict __self,
                             struct video_domain const *__domain,
                             struct video_format const *__format);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Callback prototypes for operators accepted by `video_buffer_forcustom()' */
typedef void (LIBVIDEO_GFX_CC *video_buffer_custom_destroy_t)(void *__cookie);
typedef __ATTR_PURE_T __ATTR_WUNUSED_T video_pixel_t (LIBVIDEO_GFX_CC *video_buffer_custom_getpixel_t)(void *__cookie, video_coord_t __x, video_coord_t __y);
typedef void (LIBVIDEO_GFX_CC *video_buffer_custom_setpixel_t)(void *__cookie, video_coord_t __x, video_coord_t __y, video_pixel_t __pixel);
typedef __ATTR_OUT_T(2) int (LIBVIDEO_GFX_CC *video_buffer_custom_lock_t)(void *__cookie, struct video_lock *__restrict __lock);
typedef __ATTR_IN_T(2) void __NOTHROW_T(LIBVIDEO_GFX_CC *video_buffer_custom_unlock_t)(void *__cookie, struct video_lock *__restrict __lock);
typedef __ATTR_OUT_T(2) int (LIBVIDEO_GFX_CC *video_buffer_custom_lockregion_t)(void *__cookie, struct video_regionlock *__restrict __lock);
typedef __ATTR_IN_T(2) void __NOTHROW_T(LIBVIDEO_GFX_CC *video_buffer_custom_unlockregion_t)(void *__cookie, struct video_regionlock *__restrict __lock);


/* Construct a special video buffer which, rather than being backed by memory
 * or implemented using hardware acceleration,  does all its pixel I/O  using
 * the provided function pointers.
 * NOTE: The returned video buffer exists in the `video_ramdomain()' domain.
 *
 * WARNING: The  given `__getpixel' / `__setpixel' callbacks better be
 *          fast, or any GFX on the returned buffer will take forever!
 *
 * @param: __size_x:   X dimension of the returned video buffer
 * @param: __size_y:   Y dimension of the returned video buffer
 * @param: __codec:    [1..1] Video codec used for color<=>pixel conversion, as
 *                            well  as pixel I/O (when __rlock/__wlock is given
 *                            and returns `0')
 * @param: __palette:      [0..1] Palette to-be used with `__codec' (if needed)
 * @param: __getpixel:     [1..1] Mandatory pixel read operator (passed coords are absolute and guarantied in-bounds)
 * @param: __setpixel:     [1..1] Mandatory pixel write operator (passed coords are absolute and guarantied in-bounds)
 * @param: __destroy:      [0..1] Optional callback invoked when the returned buffer is destroyed
 * @param: __rlock:        [0..1] Optional callback to lock video memory for reading (when missing, or doesn't return `0', `__getpixel' is always used)
 * @param: __wlock:        [0..1] Optional callback to lock video memory for writing (when missing, or doesn't return `0', `__setpixel' is always used)
 * @param: __unlock:       [0..1] Optional callback invoked to release video locks previously acquired by `__rlock' or `__wlock'
 * @param: __rlockregion:  [0..1] Optional extension to `__rlock' (when not supplied, implemented in terms of `__rlock')
 * @param: __wlockregion:  [0..1] Optional extension to `__wlock' (when not supplied, implemented in terms of `__wlock')
 * @param: __unlockregion: [0..1] Optional extension to `__unlock' (when not supplied, implemented in terms of `__unlock')
 * @param: __cookie:       [?..?] Cookie argument passed to all user-supplied operators */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((3, 5, 6)) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_FORCUSTOM)(video_dim_t __size_x, video_dim_t __size_y,
                                           struct video_codec const *__codec, struct video_palette *__palette,
                                           video_buffer_custom_getpixel_t __getpixel,
                                           video_buffer_custom_setpixel_t __setpixel,
                                           video_buffer_custom_destroy_t __destroy,
                                           video_buffer_custom_lock_t __rlock,
                                           video_buffer_custom_lock_t __wlock,
                                           video_buffer_custom_unlock_t __unlock,
                                           video_buffer_custom_lockregion_t __rlockregion,
                                           video_buffer_custom_lockregion_t __wlockregion,
                                           video_buffer_custom_unlockregion_t __unlockregion,
                                           void *__cookie);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((3, 5, 6)) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_forcustom(video_dim_t __size_x, video_dim_t __size_y,
                       struct video_codec const *__codec, struct video_palette *__palette,
                       video_buffer_custom_getpixel_t __getpixel,
                       video_buffer_custom_setpixel_t __setpixel,
                       video_buffer_custom_destroy_t __destroy,
                       video_buffer_custom_lock_t __rlock,
                       video_buffer_custom_lock_t __wlock,
                       video_buffer_custom_unlock_t __unlock,
                       video_buffer_custom_lockregion_t __rlockregion,
                       video_buffer_custom_lockregion_t __wlockregion,
                       video_buffer_custom_unlockregion_t __unlockregion,
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
(LIBVIDEO_GFX_CC *POLD_VIDEO_BUFFER_FROMGFX)(struct video_gfx const *__restrict __self);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __REF struct video_buffer *LIBVIDEO_GFX_CC
old_video_buffer_fromgfx(struct video_gfx const *__restrict __self);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Create  a wrapper video buffer for `__self' that can only ever be used to access
 * the intersection of pixels from `__rect' and `__self' (trying a GFX context will
 * always  start out with the I/O rect set to "__rect", but the clip rect still set
 * to the buffer's base dimensions, and trying to lock OOB regions always fails)
 *
 * NOTE: Starting coords in `__rect' are allowed to be negative, and its dimensions
 *       are allowed to be greater than those of `__self', too!
 *
 * `old_video_buffer_region_revocable()' does the same, but the returned video buffer
 * is also "revocable" (s.a.  `old_video_buffer_region_revoke()'), meaning it can  be
 * detached  from the original buffer (and turned into  a no-op) at any point in time
 * (blocking if a video lock is held in `old_video_buffer_region_revoke()').
 *
 * @return: * :   The wrapper video buffer
 * @return: NULL: Failed to create video buffer (s.a. `errno') */
typedef __ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_IN_T(2) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *POLD_VIDEO_BUFFER_REGION)(struct video_buffer *__restrict __self,
                                            struct video_rect const *__restrict __rect);
typedef __ATTR_WUNUSED_T __ATTR_INOUT_T(1) __ATTR_IN_T(2) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *POLD_VIDEO_BUFFER_REGION_REVOCABLE)(struct video_buffer *__restrict __self,
                                                      struct video_rect const *__restrict __rect);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN(2) __REF struct video_buffer *LIBVIDEO_GFX_CC
old_video_buffer_region(struct video_buffer *__restrict __self,
                        struct video_rect const *__restrict __rect);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN(2) __REF struct video_buffer *LIBVIDEO_GFX_CC
old_video_buffer_region_revocable(struct video_buffer *__restrict __self,
                                  struct video_rect const *__restrict __rect);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Revoke access  to  the  underlying video  buffer,  given  a  video
 * buffer that was returned by `old_video_buffer_region_revocable()'.
 * If the buffer had already been revoked, this is a no-op.
 *
 * >> DO NOT CALL THIS FUNCTION FOR BUFFERS OBTAINED FROM SOMETHING
 * >> OTHER THAN `old_video_buffer_region_revocable()' !!!
 *
 * @return: * : Always re-returns `__self' */
typedef __ATTR_INOUT_T(1) struct video_buffer *
(LIBVIDEO_GFX_CC *POLD_VIDEO_BUFFER_REGION_REVOKE)(struct video_buffer *__restrict __self);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_INOUT(1) struct video_buffer *LIBVIDEO_GFX_CC
old_video_buffer_region_revoke(struct video_buffer *__restrict __self);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */



/* Various functions  for opening  a file/stream/blob  as an  image  file.
 * The actual file format is  auto-detected, and supported formats  depend
 * on installed 3rd party libraries. By default, BMP and PNG is supported. */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __ATTR_INS_T(2, 3) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_MOPEN)(struct video_domain const *__restrict __domain,
                                       void const *__blob, __size_t __blob_size);
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_FOPEN)(struct video_domain const *__restrict __domain,
                                       __FILE *__restrict __fp);
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_FDOPEN)(struct video_domain const *__restrict __domain, __fd_t __fd);
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_OPEN)(struct video_domain const *__restrict __domain, char const *__filename);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_INS(2, 3) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_mopen(struct video_domain const *__restrict __domain, void const *__blob, __size_t __blob_size);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_fopen(struct video_domain const *__restrict __domain, __FILE *__restrict __fp);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_fdopen(struct video_domain const *__restrict __domain, __fd_t __fd);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_open(struct video_domain const *__restrict __domain, char const *__filename);
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


/* Same as `video_buffer_*save', but  save pixel data from  the
 * Clip Rect of `__self'. Values written for pixels outside the
 * I/O Rect of `__self'  are format-specific, but those  pixels
 * are probably going to be either black, or transparent.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) int
(LIBVIDEO_GFX_CC *PVIDEO_GFX_FSAVE)(struct video_gfx const *__self, char const *__format,
                                    __FILE *__restrict __fp, char const *__options);
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) int
(LIBVIDEO_GFX_CC *PVIDEO_GFX_FDSAVE)(struct video_gfx const *__self, char const *__format,
                                     __fd_t __fd, char const *__options);
typedef /*__ATTR_WUNUSED_T*/ __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) int
(LIBVIDEO_GFX_CC *PVIDEO_GFX_SAVE)(struct video_gfx const *__self, char const *__filename,
                                   char const *__options);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_NONNULL((2)) int LIBVIDEO_GFX_CC
video_gfx_fsave(struct video_gfx const *__self, char const *__format,
                __FILE *__restrict __fp, char const *__options);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_NONNULL((2)) int LIBVIDEO_GFX_CC
video_gfx_fdsave(struct video_gfx const *__self, char const *__format,
                 __fd_t __fd, char const *__options);
LIBVIDEO_GFX_DECL /*__ATTR_WUNUSED*/ __ATTR_IN(1) __ATTR_NONNULL((2)) int LIBVIDEO_GFX_CC
video_gfx_save(struct video_gfx const *__self, char const *__filename,
               char const *__options);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_BUFFER_H */
