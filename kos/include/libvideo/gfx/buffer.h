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

#include "../color.h"
#include "../crect.h"
#include "blend.h"
#include "gfx-flags.h"
#include "surface-defs.h"

#ifdef LIBVIDEO_GFX_EXPOSE_INTERNALS
#ifndef __INTELLISENSE__
#include <hybrid/__assert.h>
#include "codec/codec.h"
#include "codec/palette.h"
#endif /* !__INTELLISENSE__ */
#endif /* LIBVIDEO_GFX_EXPOSE_INTERNALS */

/* Possible values for `video_domain_newbuffer()::__flags' */
#define VIDEO_DOMAIN_NEWBUFFER_F_NORMAL 0x0000 /* Normal flags */
#define VIDEO_DOMAIN_NEWBUFFER_F_CALLOC 0x0001 /* Require pixel data to be zero-initialized */

/* Possible values for `video_domain_formem()::__flags' */
#define VIDEO_DOMAIN_FORMEM_F_NORMAL 0x0000 /* Normal flags */
#define VIDEO_DOMAIN_FORMEM_F_SHARED 0x0002 /* Force creation */

#ifdef __CC__
__DECL_BEGIN

struct video_gfx;
struct video_domain;
struct video_codec;
struct video_palette;
struct video_surface;
struct video_rect;
#ifdef CONFIG_LIBVIDEO_HAVE_RLE
struct video_buffer_rlekey;
#endif /* CONFIG_LIBVIDEO_HAVE_RLE */
#ifdef CONFIG_LIBVIDEO_HAVE_SERIALIZATION
struct video_buffer_fdinfo;
struct video_deserializer_io;

/* Video serialization type ID (one of `VIDEO_SERIAL_PROTO_*') */
typedef __uintptr_t video_serial_proto_t;
#endif /* CONFIG_LIBVIDEO_HAVE_SERIALIZATION */

/* Descriptor for the format of a video buffer */
struct video_buffer_format {
	struct video_palette const *vbf_pal;      /* [0..1][valid_if(vbf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL)] Color palette (if needed by `vbf_codec') */
	struct video_codec         *vbf_codec;    /* [1..1] Video codec. */
	video_gfx_flag_t            vbf_flags;    /* Default GFX flags (set of `VIDEO_GFX_F_*') */
	video_pixel_t               vbf_colorkey; /* [valid_if(vbf_flags & VIDEO_GFX_F_COLORKEY)] Pixel value to skip during blits */
};

#define video_buffer_format_equals(a, b)                               \
	((a)->vbf_codec == (b)->vbf_codec &&                               \
	 (a)->vbf_flags == (b)->vbf_flags &&                               \
	 ((a)->vbf_pal == (b)->vbf_pal ||                                  \
	  !((a)->vbf_codec->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL)) && \
	 ((a)->vbf_colorkey == (b)->vbf_colorkey ||                        \
	  !((a)->vbf_flags & VIDEO_GFX_F_COLORKEY)))


/* Video-domain: Low-level driver interface for creation of video buffers */
struct video_domain {
	/* Create a video buffer, or return NULL and set errno if creation failed.
	 * NOTE: When  the given  `__xdim' or `__ydim'  is ZERO(0), an  empty buffer is
	 *       returned which may not necessarily use the given `codec' and `palette'
	 * @param: __self:   Associated video domain
	 * @param: __xdim:   X Dimension for buffer
	 * @param: __ydim:   Y Dimension for buffer
	 * @param: __format: The used video format.
	 * @param: __flags:  Set of `VIDEO_DOMAIN_NEWBUFFER_F_*'
	 * @return: * :      The newly created video buffer
	 * @return: NULL: [errno=ENOMEM]  Insufficient memory (either regular RAM, or V-RAM)
	 * @return: NULL: [errno=ENOTSUP] Given `__format->vbf_codec' is  not supported by  this
	 *                                domain (only `video_ramdomain()' supports all formats)
	 * @return: NULL: [errno=*] Failed to construct video buffer for some other reason */
	__ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __ATTR_IN_T(2) __REF struct video_buffer *
	(LIBVIDEO_GFX_CC *vd_newbuffer)(struct video_domain const *__restrict __self,
	                                struct video_buffer_format const *__restrict __format,
	                                video_dim_t __xdim, video_dim_t __ydim,
	                                unsigned int __flags);

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
	 * @param: __xdim:   X Dimension for buffer
	 * @param: __ydim:   Y Dimension for buffer
	 * @param: __stride: Scanline width in `mem'
	 * @param: __format: The video codec+palette that describes how `mem' is encoded.
	 * @param: __release_mem: Optional callback invoked when the returned buffer is destroyed
	 * @param: __release_mem_cookie: Cookie argument for `__release_mem'
	 * @param: __flags:  Set of `VIDEO_DOMAIN_FORMEM_F_*'
	 * @return: * :   The newly created video buffer
	 * @return: NULL: [errno=EINVAL] Given `stride' is too small for `codec' and `size_y'
	 * @return: NULL: [errno=ENOMEM] Insufficient memory
	 * @return: NULL: [errno=ENOTSUP] Given `__format->vbf_codec' is  not supported by  this
	 *                                domain (only `video_ramdomain()' supports all formats)
	 * @return: NULL: [errno=EFAULT] `VIDEO_DOMAIN_FORMEM_F_SHARED' was given, but not supported by `__mem'
	 * @return: NULL: [errno=*] Failed to construct video buffer for some other reason */
	__ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 5)) __ATTR_IN_T(2) __REF struct video_buffer *
	(LIBVIDEO_GFX_CC *vd_formem)(struct video_domain const *__restrict __self,
	                             struct video_buffer_format const *__format,
	                             video_dim_t __xdim, video_dim_t __ydim, void *__mem, __size_t __stride,
	                             void (LIBVIDEO_GFX_CC *__release_mem)(void *__cookie, void *__mem),
	                             void *__release_mem_cookie, unsigned int __flags);

	/* Return the closest (by criteria of features and appearance) supported codec to "__codec"
	 * This  function never returns `NULL', even if the domain only supports a single codec, in
	 * which case this function simply always returns that codec.
	 *
	 * HINT: `video_ramdomain()' implements this function by always re-returning `__codec' */
	__ATTR_RETNONNULL_T __ATTR_WUNUSED_T __ATTR_IN_T(2) __ATTR_NONNULL_T((1)) struct video_codec *
	(LIBVIDEO_GFX_CC *vd_supported_codec)(struct video_domain const *__restrict __self,
	                                      struct video_codec const *__restrict __codec);

	/* Create a new palette for at least `__count' colors.
	 *
	 * This function is allowed to allocate a larger palette  than
	 * requested if doing  so improves  performances, though  when
	 * this is done, all additional palette entries will have been
	 * initialized to `0'
	 *
	 * On success, the caller must initialize:
	 * - return->vp_pal[0]
	 * - return->vp_pal[1]
	 * - ...
	 * - return->vp_pal[__count - 2]
	 * - return->vp_pal[__count - 1]
	 *
	 * Once  this is done, the caller must indicate that the palette
	 * has been updated by calling `video_palette_optimize()' on the
	 * returned palette. The  same needs to  be repeated every  time
	 * further changes are made  to `return->vp_pal[x]' in order  to
	 * communicate those changes to the underlying video domain.
	 *
	 * When using the returned video palette with some video_buffer,
	 * or  video_surface, you should always set `VIDEO_GFX_F_PALOBJ'
	 * in order to have the  `video_buffer' hold a reference to  the
	 * palette,  or allow `video_surface'  to do faster color->pixel
	 * conversion (since managed palettes usually have lookup caches
	 * to encode color values more quickly).
	 *
	 * @return: * :   The newly created palette
	 * @return: NULL: Out of memory */
	__ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __REF struct video_palette *
	(LIBVIDEO_GFX_CC *vd_newpalette)(struct video_domain const *__restrict __self,
	                                 video_pixel_t __count);

#ifdef CONFIG_LIBVIDEO_HAVE_SERIALIZATION
	/* Given  a deserialization `__proto' and I/O operators `__io', construct a client-side
	 * `video_buffer* for `__self' that uses `__io' to communicate with a server-side video
	 * serializer
	 * @param: __self:  Video domain in which the  deserialization should happen. This  should
	 *                  usually be the domain define for the purpose of communicating with the
	 *                  server (which might support custom protocols expected by the  server),
	 *                  or `video_ramdomain()' / `video_ramfddomain()', which already supports
	 *                  the default protocols `VIDEO_SERIAL_PROTO_*'.
	 * @param: __io:    I/O operators used by the returned buffer. On success (return != NULL),
	 *                  this operator  table is  inherited, such  that the  destruction of  the
	 *                  returned buffer will invoke its `vdrio_destroy' operator.
	 * @param: __proto: Initial protocol, as communicated by the server (one of `VIDEO_SERIAL_PROTO_*')
	 *                  The  value to pass  here should have already  been given to  you by the server.
	 * @return: * : A video buffer that can be  used like any other, but  GFX
	 *              operations may be serialized and transmitted over `__io'.
	 * @return: NULL: [errno=ENOMEM] Insufficient memory
	 * @return: NULL: [errno=ENOTSUP] Unsupported `__proto'
	 * @return: NULL: [errno=*] Failed to initiate deserialization */
	__ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) __REF struct video_buffer *
	(LIBVIDEO_GFX_CC *vd_deserialize)(struct video_domain const *__restrict __self,
	                                  /*inherit(on_success)*/ struct video_deserializer_io *__restrict __io,
	                                  video_serial_proto_t __proto);
#else /* CONFIG_LIBVIDEO_HAVE_SERIALIZATION */
	void (*_vd_pad1[1])(void); /* ... */
#endif /* !CONFIG_LIBVIDEO_HAVE_SERIALIZATION */

	/* TODO: Function for getting memory usage (for the ram-domain,
	 *       just return regular ram usage info as per `sysinfo(2)) */

	void (*_vd_pad2[11])(void); /* Reserved for future expansion */
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


#ifdef CONFIG_LIBVIDEO_HAVE_RAMFD
/* Same as  `video_ramdomain()', but  video buffers  allocate
 * their  backing  memory using  `memfd_create()'.  Thus, the
 * video buffers created by this domain implement "vi_fdinfo"
 * and  allow for more efficient serialization on connections
 * that support file descriptor sharing.
 *
 * Additionally, `video_buffer_subregion()' for buffers created
 * by this domain will use `FILE_IOC_SUBREGION' to create their
 * buffers, and also  implement `video_buffer_revoke()' by  use
 * of  `FILE_IOC_DELREGION', meaning that their FD being shared
 * between processes will still allow you to delete mappings of
 * said  sub-region in any process that the FD was shared with.
 *
 * For reference, `video_ramdomain()' implements `video_buffer_revoke()' as a no-op. */
typedef __ATTR_CONST_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T
struct video_domain const *(LIBVIDEO_GFX_CC *PVIDEO_RAMFDDOMAIN)(void);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED
struct video_domain const *LIBVIDEO_GFX_CC video_ramfddomain(void);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */
#endif /* CONFIG_LIBVIDEO_HAVE_RAMFD */



#ifdef __INTELLISENSE__
/* Create a video buffer, or return NULL and set errno if creation failed.
 * NOTE: When  the given  `__xdim' or `__ydim'  is ZERO(0), an  empty buffer is
 *       returned which may not necessarily use the given `codec' and `palette'
 * @param: __self:   Associated video domain
 * @param: __xdim:   X Dimension for buffer
 * @param: __ydim:   Y Dimension for buffer
 * @param: __format: The used video format.
 * @param: __flags:  Set of `VIDEO_DOMAIN_NEWBUFFER_F_*'
 * @return: * :   The newly created video buffer
 * @return: NULL: [errno=ENOMEM]  Insufficient memory (either regular RAM, or V-RAM)
 * @return: NULL: [errno=ENOTSUP] Given `__format->vbf_codec' is  not supported by  this
 *                                domain (only `video_ramdomain()' supports all formats)
 * @return: NULL: [errno=*] Failed to construct video buffer for some other reason */
extern __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_IN(2) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_domain_newbuffer(struct video_domain const *__restrict __self,
                       struct video_buffer_format const *__restrict __format,
                       video_dim_t __xdim, video_dim_t __ydim,
                       unsigned int __flags);
extern __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_IN(2) __REF struct video_buffer *LIBVIDEO_GFX_CC
_video_domain_newbuffer(struct video_domain const *__restrict __self,
                        struct video_buffer_format const *__restrict __format,
                        video_dim_t __buffer_xdim, video_dim_t __buffer_ydim,
                        unsigned int __flags);

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
 * @param: __xdim:   X Dimension for buffer
 * @param: __ydim:   Y Dimension for buffer
 * @param: __stride: Scanline width in `mem'
 * @param: __format: The video codec+palette that describes how `mem' is encoded.
 * @param: __release_mem: Optional callback invoked when the returned buffer is destroyed
 * @param: __release_mem_cookie: Cookie argument for `__release_mem'
 * @param: __flags:  Set of `VIDEO_DOMAIN_FORMEM_F_*'
 * @return: * :   The newly created video buffer
 * @return: NULL: [errno=EINVAL] Given `stride' is too small for `codec' and `size_y'
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=ENOTSUP] Given `__format->vbf_codec' is  not supported by  this
 *                                domain (only `video_ramdomain()' supports all formats)
 * @return: NULL: [errno=EFAULT] `VIDEO_DOMAIN_FORMEM_F_SHARED' was given, but not supported by `__mem'
 * @return: NULL: [errno=*] Failed to construct video buffer for some other reason */
extern __ATTR_WUNUSED __ATTR_NONNULL((1, 5)) __ATTR_IN(2) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_domain_formem(struct video_domain const *__restrict __self,
                    struct video_buffer_format const *__format,
                    video_dim_t __xdim, video_dim_t __ydim, void *__mem, __size_t __stride,
                    void (LIBVIDEO_GFX_CC *__release_mem)(void *__cookie, void *__mem),
                    void *__release_mem_cookie, unsigned int __flags);
extern __ATTR_WUNUSED __ATTR_NONNULL((1, 5)) __ATTR_IN(2) __REF struct video_buffer *LIBVIDEO_GFX_CC
_video_domain_formem(struct video_domain const *__restrict __self,
                     struct video_buffer_format const *__format,
                     video_dim_t __buffer_xdim, video_dim_t __buffer_ydim, void *__mem, __size_t __stride,
                     void (LIBVIDEO_GFX_CC *__release_mem)(void *__cookie, void *__mem),
                     void *__release_mem_cookie, unsigned int __flags);

/* Return the closest (by criteria of features and appearance) supported codec to "__codec"
 * This  function never returns `NULL', even if the domain only supports a single codec, in
 * which case this function simply always returns that codec.
 *
 * HINT: `video_ramdomain()' implements this function by always re-returning `__codec' */
extern __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_NONNULL((1)) struct video_codec *LIBVIDEO_GFX_CC
video_domain_supported_codec(struct video_domain const *__restrict __self,
                             struct video_codec const *__restrict __codec);

/* Create a new palette for at least `__count' colors.
 *
 * This function is allowed to allocate a larger palette  than
 * requested if doing  so improves  performances, though  when
 * this is done, all additional palette entries will have been
 * initialized to `0'
 *
 * On success, the caller must initialize:
 * - return->vp_pal[0]
 * - return->vp_pal[1]
 * - ...
 * - return->vp_pal[__count - 2]
 * - return->vp_pal[__count - 1]
 *
 * Once  this is done, the caller must indicate that the palette
 * has been updated by calling `video_palette_optimize()' on the
 * returned palette. The  same needs to  be repeated every  time
 * further changes are made  to `return->vp_pal[x]' in order  to
 * communicate those changes to the underlying video domain.
 *
 * When using the returned video palette with some video_buffer,
 * or  video_surface, you should always set `VIDEO_GFX_F_PALOBJ'
 * in order to have the  `video_buffer' hold a reference to  the
 * palette,  or allow `video_surface'  to do faster color->pixel
 * conversion (since managed palettes usually have lookup caches
 * to encode color values more quickly).
 *
 * @return: * :   The newly created palette
 * @return: NULL: Out of memory */
extern __ATTR_WUNUSED __ATTR_NONNULL((1)) __REF struct video_palette *
video_domain_newpalette(struct video_domain const *__restrict __self,
                        video_pixel_t __count);

#ifdef CONFIG_LIBVIDEO_HAVE_SERIALIZATION
/* Given  a deserialization `__proto' and I/O operators `__io', construct a client-side
 * `video_buffer* for `__self' that uses `__io' to communicate with a server-side video
 * serializer
 * @param: __self:  Video domain in which the  deserialization should happen. This  should
 *                  usually be the domain define for the purpose of communicating with the
 *                  server (which might support custom protocols expected by the  server),
 *                  or `video_ramdomain()' / `video_ramfddomain()', which already supports
 *                  the default protocols `VIDEO_SERIAL_PROTO_*'.
 * @param: __io:    I/O operators used by the returned buffer. On success (return != NULL),
 *                  this operator  table is  inherited, such  that the  destruction of  the
 *                  returned buffer will invoke its `vdrio_destroy' operator.
 * @param: __proto: Initial protocol, as communicated by the server (one of `VIDEO_SERIAL_PROTO_*')
 *                  The  value to pass  here should have already  been given to  you by the server.
 * @return: * : A video buffer that can be  used like any other, but  GFX
 *              operations may be serialized and transmitted over `__io'.
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=ENOTSUP] Unsupported `__proto'
 * @return: NULL: [errno=*] Failed to initiate deserialization */
extern __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) __REF struct video_buffer *
video_domain_deserialize(struct video_domain const *__restrict __self,
                         /*inherit(on_success)*/ struct video_deserializer_io *__restrict __io,
                         video_serial_proto_t __proto);
#endif /* CONFIG_LIBVIDEO_HAVE_SERIALIZATION */

#else /* __INTELLISENSE__ */
#define _video_domain_newbuffer(self, format, buffer_xdim, buffer_ydim, flags) \
	(*(self)->vd_newbuffer)(self, format, buffer_xdim, buffer_ydim, flags)
#define video_domain_newbuffer(self, format, xdim, ydim, flags)                                                       \
	(__likely(!((format)->vbf_flags & VIDEO_GFX_F_XYSWAP)) ? _video_domain_newbuffer(self, format, xdim, ydim, flags) \
	                                                       : _video_domain_newbuffer(self, format, ydim, xdim, flags))
#define _video_domain_formem(self, format, buffer_xdim, buffer_ydim, mem, stride, release_mem, release_mem_cookie, flags) \
	(*(self)->vd_formem)(self, format, buffer_xdim, buffer_ydim, mem, stride, release_mem, release_mem_cookie, flags)
#define video_domain_formem(self, format, xdim, ydim, mem, stride, release_mem, release_mem_cookie, flags)                                                       \
	(__likely(!((format)->vbf_flags & VIDEO_GFX_F_XYSWAP)) ? _video_domain_formem(self, format, xdim, ydim, mem, stride, release_mem, release_mem_cookie, flags) \
	                                                       : _video_domain_formem(self, format, ydim, xdim, mem, stride, release_mem, release_mem_cookie, flags))
#define video_domain_supported_codec(self, codec) \
	(*(self)->vd_supported_codec)(self, codec)
#define video_domain_newpalette(self, count) \
	(*(self)->vd_newpalette)(self, count)
#ifdef CONFIG_LIBVIDEO_HAVE_SERIALIZATION
#define video_domain_deserialize(self, io, proto) \
	(*(self)->vd_deserialize)(self, io, proto)
#endif /* CONFIG_LIBVIDEO_HAVE_SERIALIZATION */
#endif /* !__INTELLISENSE__ */




struct video_lock {
	/* WARNING: DO NOT MODIFY ANYTHING HERE BEFORE `video_buffer_unlock()' */
	__byte_t *vl_data;   /* [1..1] Memory-mapped video dat (never "NULL") */
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

#ifdef __INTELLISENSE__
/* Helpers for getting the raw pointers/offsets into video memory associated with a video lock */
extern __ATTR_RETNONNULL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __byte_t *
video_lock_getdata(struct video_lock const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __size_t
video_lock_getstride(struct video_lock const *__restrict __self);
extern __ATTR_RETNONNULL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __byte_t *
video_lock_getline(struct video_lock const *__restrict __self, video_coord_t __y);

/* Same as above, but for `video_regionlock' */
extern __ATTR_RETNONNULL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __byte_t *
video_regionlock_getdata(struct video_regionlock const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __size_t
video_regionlock_getstride(struct video_regionlock const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_coord_t
video_regionlock_getxbase(struct video_regionlock const *__restrict __self);
extern __ATTR_RETNONNULL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __byte_t *
video_regionlock_getline(struct video_regionlock const *__restrict __self, video_coord_t __y);
#else /* __INTELLISENSE__ */
#define video_lock_getdata(self)          ((__byte_t *)(self)->vl_data)
#define video_lock_getstride(self)        ((__size_t)(self)->vl_stride)
#define video_lock_getline(self, y)       ((self)->vl_data + (y) * (self)->vl_stride)
#define video_regionlock_getdata(self)    ((__byte_t *)(self)->vrl_lock.vl_data)
#define video_regionlock_getstride(self)  ((__size_t)(self)->vrl_lock.vl_stride)
#define video_regionlock_getxbase(self)   ((video_coord_t)(self)->vrl_xbas)
#define video_regionlock_getline(self, y) ((self)->vrl_lock.vl_data + (y) * (self)->vrl_lock.vl_stride)
#endif /* !__INTELLISENSE__ */

struct video_buffer_ops {
	/* NOTE: _ALL_ Callbacks are always [1..1] */

	/* Buffer finalization. */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_FCC *vi_destroy)(struct video_buffer *__restrict __self);

	/* Initialize a graphics context for use with the linked buffer.
	 * The caller  of this  operator must  have already  filled  in:
	 * - __self->vg_surf.vs_buffer  (with the buffer on which this operator is then called)
	 * - __self->vg_blend
	 * - __self->vg_surf.vs_flags
	 * - __self->vg_surf.vs_colorkey
	 * NOTE: This  operator  is  allowed  to  modify  any/all  of  the  above!
	 *       e.g. `video_buffer_lockable()' will change `vg_surf.vs_buffer' to
	 *       the wrapped video buffer.
	 * @return: * : Always re-returns `__self' */
	__ATTR_RETNONNULL_T __ATTR_INOUT_T(1) struct video_gfx *
	(LIBVIDEO_GFX_FCC *vi_initgfx)(struct video_gfx *__restrict __self);

	/* Update operators of `__self' after certain behavioral flags were changed:
	 * - VIDEO_GFX_UPDATE_BLEND:    `__self->vg_blend' may have changed
	 * - VIDEO_GFX_UPDATE_FLAGS:    `__self->vg_surf.vs_flags' may have changed
	 * - VIDEO_GFX_UPDATE_COLORKEY: `__self->vg_surf.vs_colorkey' may have changed
	 * @param: __what: Set of `VIDEO_GFX_UPDATE_*'
	 *
	 * CAUTION: Do not use this operator when `__self' may be used by other threads! */
	__ATTR_RETNONNULL_T __ATTR_INOUT_T(1) struct video_gfx *
	(LIBVIDEO_GFX_FCC *vi_updategfx)(struct video_gfx *__restrict __self,
	                                 unsigned int __what);

	void (*_vi_pad1[4])(void);

#ifdef CONFIG_LIBVIDEO_HAVE_SERIALIZATION
	/* [0..1] Get fd-info about "__self" for use with `VIDEO_SERIAL_PROTO_MEMFD'
	 * When this operator  isn't implemented, "VIDEO_SERIAL_PROTO_MEMFD"  cannot
	 * be used for serialization.
	 *
	 * Note that the file-descriptor written to `__info' is owned by `__self'! */
	__ATTR_INOUT_T(1) __ATTR_OUT_T(2) void
	(LIBVIDEO_GFX_FCC *vi_fdinfo)(struct video_buffer *__restrict __self,
	                              struct video_buffer_fdinfo *__restrict __info);
#else /* CONFIG_LIBVIDEO_HAVE_SERIALIZATION */
	void (*_vi_pad2[1])(void);
#endif /* !CONFIG_LIBVIDEO_HAVE_SERIALIZATION */


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
	 * @assume((__lock->_vrl_rect.vcr_xmin + __lock->_vrl_rect.vcr_xdim) <= video_buffer_getxdim(__self));
	 * @assume((__lock->_vrl_rect.vcr_ymin + __lock->_vrl_rect.vcr_ydim) <= video_buffer_getydim(__self));
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
	 * @assume((__lock->_vrl_rect.vcr_xmin + __lock->_vrl_rect.vcr_xdim) <= video_buffer_getxdim(__self));
	 * @assume((__lock->_vrl_rect.vcr_ymin + __lock->_vrl_rect.vcr_ydim) <= video_buffer_getydim(__self));
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

	/* Create a new hard subregion-proxy of `__self'. The caller is responsible to ensure
	 * that the given  `__rect' does not  exceed `video_buffer_get[xy]dim(__self)'.  Note
	 * that this function  behaves slightly different  from `video_surface_region()',  in
	 * that  the later accepts a signed rect, while also allowing said rect to be greater
	 * than the dimensions of the original buffer.
	 *
	 * On the other hand, this function only works for creating **true** sub-rects, but
	 * since this one is implemented by individual buffers, it is probably faster, too.
	 *
	 * This operator never re-returns `__self'. If such behavior is wanted, such checks
	 * must be performed by the caller.
	 *
	 * @assume(__phys_rect->vcr_xdim > 0);
	 * @assume(__phys_rect->vcr_ydim > 0);
	 * @assume((__phys_rect->vcr_xmin + __phys_rect->vcr_xdim) > __phys_rect->vcr_xmin);
	 * @assume((__phys_rect->vcr_ymin + __phys_rect->vcr_ydim) > __phys_rect->vcr_ymin);
	 * @assume((__phys_rect->vcr_xmin + __phys_rect->vcr_xdim) <= video_surface_getbufferxdim(__self));
	 * @assume((__phys_rect->vcr_ymin + __phys_rect->vcr_ydim) <= video_surface_getbufferydim(__self));
	 * @param: __self:      Video surface to create a sub-region of (returned
	 *                      buffer's format  is derived  from this  surface).
	 * @param: __phys_rect: Sub-region rect of `video_surface_getbuffer(__self)' to-be returned
	 * @return: * :         The newly created sub-region buffer
	 * @return: NULL: [errno=ENOMEM] Insufficient memory
	 * @return: NULL: [errno=*] Failed to create sub-region for some other reason */
	__ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_IN_T(2) __REF struct video_buffer *
	(LIBVIDEO_GFX_FCC *vi_subregion)(struct video_surface const *__restrict __self,
	                                 struct video_crect const *__restrict __phys_rect);


	/* When `__self' is a serializable buffer, or is a wrapper for such a buffer,
	 * revoke any further access to pixel data by replacing all currently-active,
	 * or future memory mappings of  the buffer with `/dev/void'. Similarly,  any
	 * GFX operations performed on the buffer after this call will result in weak
	 * undefined behavior (meaning writes will be lost, and reads yield undefined
	 * pixel values).
	 *
	 * For non-serializable buffers, this function is simply a no-op.
	 *
	 * @return: * : Always re-returns `__self' */
	__ATTR_RETNONNULL_T __ATTR_INOUT_T(1) struct video_buffer *
	__NOTHROW_T(LIBVIDEO_GFX_FCC *vi_revoke)(struct video_buffer *__restrict __self);

#ifdef CONFIG_LIBVIDEO_HAVE_RLE
	/* [0..1] Return RLE-encoded pixel data described by `__self' */
	__ATTR_WUNUSED_T __ATTR_IN_T(1) __byte_t const *
	__NOTHROW_T(LIBVIDEO_GFX_FCC *vi_getrle)(struct video_buffer_rlekey const *__restrict __self);
#endif /* CONFIG_LIBVIDEO_HAVE_RLE */
};




#ifdef __INTELLISENSE__

/* Convenience getters for video buffer attributes */
extern __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct video_surface const *video_buffer_assurface(struct video_buffer const *__restrict __self);
extern __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct video_domain const *video_buffer_getdomain(struct video_buffer const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) struct video_palette *video_buffer_getpalette(struct video_buffer const *__restrict __self);
extern __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct video_codec *video_buffer_getcodec(struct video_buffer const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_gfx_flag_t video_buffer_getflags(struct video_buffer const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_gfx_flag_t video_buffer_getcolorkey(struct video_buffer const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_buffer_hascolorkey(struct video_buffer const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_buffer_getxdim(struct video_buffer const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_buffer_getydim(struct video_buffer const *__restrict __self);

/* Set/Enable/Disable the default color-key of the buffer.
 * This  is pretty much the only thing you can alter about
 * a given video buffer however you please. */
extern __ATTR_INOUT(1) void video_buffer_setcolorkey(struct video_buffer *__restrict __self, video_pixel_t __colorkey);
extern __ATTR_INOUT(1) void video_buffer_enablecolorkey(struct video_buffer *__restrict __self, video_pixel_t __colorkey);
extern __ATTR_INOUT(1) void video_buffer_disablecolorkey(struct video_buffer *__restrict __self);

/* Check if a given video buffer uses the specified format. */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __BOOL
video_buffer_hasformat(struct video_buffer const *__restrict __self,
                       struct video_buffer_format const *__restrict __format);

/* Fill in `__format' with the format used by `__self' */
extern __ATTR_IN(1) __ATTR_OUT(2) void
video_buffer_getformat(struct video_buffer const *__restrict __self,
                       struct video_buffer_format *__restrict __format);


/* Get graphics functions for use with the given buffer
 * @param: blendmode: Pixel blending mode  for graphics operations  targeting this  buffer.
 *                    This  argument   should  be   constructed  using   `GFX_BLENDMODE()'.
 *                    Usually, you will want to use `GFX_BLENDMODE_ALPHA' as blending  mode
 *                    when you wish to make use of alpha-blending. However, if you know for
 *                    certain  that alpha-blending isn't required, graphics performance can
 *                    be improved by passing  `GFX_BLENDMODE_OVERRIDE' in order to  prevent
 *                    any overhead  that would  normally  incur from  blending  operations.
 * @return: * : Always re-returns `__result' */
extern __ATTR_RETNONNULL __ATTR_INOUT(1) __ATTR_OUT(2) struct video_gfx *
video_buffer_getgfx(struct video_buffer *__self,
                    struct video_gfx *__result,
                    gfx_blendmode_t __blendmode);
extern __ATTR_RETNONNULL __ATTR_INOUT(1) __ATTR_OUT(2) struct video_gfx *
video_buffer_getgfx_ex(struct video_buffer *__self, struct video_gfx *__result,
                       gfx_blendmode_t __blendmode, struct video_palette const *__used_palette,
                       video_gfx_flag_t __used_flags, video_pixel_t __used_colorkey);



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
 * @assume((__xmin + __xdim) <= video_buffer_getxdim(__self));
 * @assume((__ymin + __ydim) <= video_buffer_getydim(__self));
 *
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) int
video_buffer_rlockregion(struct video_buffer *__self, struct video_regionlock *__lock,
                         video_coord_t __xmin, video_coord_t __ymin,
                         video_dim_t __xdim, video_dim_t __ydim);
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_INOUT(2) int
_video_buffer_rlockregion(struct video_buffer *__self, struct video_regionlock *__lock);

/* Same as  `video_buffer_wlock', but  possibly more  efficient, as  only  a
 * specific sub-region is being locked, rather than the entire video buffer.
 *
 * Also: this function may succeed in cases where `video_buffer_wlock' fails.
 *
 * @assume(__xdim > 0);
 * @assume(__ydim > 0);
 * @assume((__xmin + __xdim) > __xmin);
 * @assume((__ymin + __ydim) > __ymin);
 * @assume((__xmin + __xdim) <= video_buffer_getxdim(__self));
 * @assume((__ymin + __ydim) <= video_buffer_getydim(__self));
 *
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) int
video_buffer_wlockregion(struct video_buffer *__self, struct video_regionlock *__lock,
                         video_coord_t __xmin, video_coord_t __ymin,
                         video_dim_t __xdim, video_dim_t __ydim);
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_INOUT(2) int
_video_buffer_wlockregion(struct video_buffer *__self, struct video_regionlock *__lock);

/* Release a video  region lock that  had previously been  acquired
 * by `video_buffer_rlockregion()' or `video_buffer_wlockregion()'. */
extern __ATTR_INOUT(1) __ATTR_NONNULL((2)) void
video_buffer_unlockregion(struct video_buffer *__self, struct video_regionlock *__lock);


/* When `__self' is a serializable buffer, or is a wrapper for such a buffer,
 * revoke any further access to pixel data by replacing all currently-active,
 * or future memory mappings of  the buffer with `/dev/void'. Similarly,  any
 * GFX operations performed on the buffer after this call will result in weak
 * undefined behavior (meaning writes will be lost, and reads yield undefined
 * pixel values).
 *
 * For non-serializable buffers, this function is simply a no-op.
 *
 * @return: * : Always re-returns `__self' */
extern __ATTR_RETNONNULL __ATTR_INOUT(1) struct video_buffer *
__NOTHROW(video_buffer_revoke)(struct video_buffer *__restrict __self);

#else /* __INTELLISENSE__ */
/* Convenience getters for video buffer attributes */
#define video_buffer_assurface(self)   (&(self)->vb_surf)
#define video_buffer_getdomain(self)   (self)->vb_domain
#define video_buffer_getpalette(self)  (self)->vb_surf.vs_pal
#define video_buffer_getcodec(self)    (self)->vb_codec
#define video_buffer_getflags(self)    (self)->vb_surf.vs_flags
#define video_buffer_getcolorkey(self) (self)->vb_surf.vs_colorkey
#define video_buffer_hascolorkey(self) ((video_buffer_getflags(self) & VIDEO_GFX_F_COLORKEY) != 0)
#define video_buffer_getxdim(self)     (self)->vb_dim[0]
#define video_buffer_getydim(self)     (self)->vb_dim[1]
#define video_buffer_setcolorkey(self, colorkey) \
	__hybrid_atomic_store((video_pixel_t *)&(self)->vb_surf.vs_colorkey, colorkey, __ATOMIC_RELEASE)
#define video_buffer_enablecolorkey(self, colorkey) \
	(video_buffer_setcolorkey(self, colorkey), __hybrid_atomic_or((video_gfx_flag_t *)&(self)->vb_surf.vs_flags, VIDEO_GFX_F_COLORKEY, __ATOMIC_SEQ_CST))
#define video_buffer_disablecolorkey(self) \
	__hybrid_atomic_and((video_gfx_flag_t *)&(self)->vb_surf.vs_flags, ~VIDEO_GFX_F_COLORKEY, __ATOMIC_SEQ_CST)

#define video_buffer_hasformat(self, format)                                                   \
	(video_buffer_getcodec(self) == (format)->vbf_codec &&                                     \
	 video_buffer_getflags(self) == (format)->vbf_flags &&                                     \
	 (!video_buffer_getpalette(self) || video_buffer_getpalette(self) == (format)->vbf_pal) && \
	 (!video_buffer_hascolorkey(self) || video_buffer_getcolorkey(self) == (format)->vbf_colorkey))
#define video_buffer_getformat(self, format)                       \
	(void)((format)->vbf_pal      = video_buffer_getpalette(self), \
	       (format)->vbf_codec    = video_buffer_getcodec(self),   \
	       (format)->vbf_flags    = video_buffer_getflags(self),   \
	       (format)->vbf_colorkey = video_buffer_getcolorkey(self))
#define video_buffer_getgfx(self, result, blendmode)                 \
	((result)->vg_surf.vs_pal      = video_buffer_getpalette(self),  \
	 (result)->vg_surf.vs_buffer   = (self),                         \
	 (result)->vg_surf.vs_flags    = video_buffer_getflags(self),    \
	 (result)->vg_surf.vs_colorkey = video_buffer_getcolorkey(self), \
	 (result)->vg_blend            = (blendmode),                    \
	 (*((result)->vg_surf.vs_buffer = (self))->vb_ops->vi_initgfx)(result))
#define video_buffer_getgfx_ex(self, result, blendmode, used_palette, used_flags, used_colorkey) \
	((result)->vg_surf.vs_pal      = (used_palette),                                             \
	 (result)->vg_surf.vs_buffer   = (self),                                                     \
	 (result)->vg_surf.vs_flags    = (used_flags),                                               \
	 (result)->vg_surf.vs_colorkey = (used_colorkey),                                            \
	 (result)->vg_blend            = (blendmode),                                                \
	 (*((result)->vg_surf.vs_buffer = (self))->vb_ops->vi_initgfx)(result))
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
#define _video_buffer_rlockregion(self, lock) (*(self)->vb_ops->vi_rlockregion)(self, lock)
#define _video_buffer_wlockregion(self, lock) (*(self)->vb_ops->vi_wlockregion)(self, lock)
#define video_buffer_unlockregion(self, lock) \
	(*(self)->vb_ops->vi_unlockregion)(self, lock)
#define video_buffer_revoke(self) (*(self)->vb_ops->vi_revoke)(self)
#endif /* !__INTELLISENSE__ */

#ifndef __VIDEO_BUFFER_const
#define __VIDEO_BUFFER_const const
#endif /* !__VIDEO_BUFFER_const */

struct video_buffer {
	struct video_surface           __VIDEO_BUFFER_const vb_surf;    /* [const] Buffer surface data (`vs_buffer' is always a self-pointer)
	                                                                 * The following aspects of this surface may be modified  atomically:
	                                                                 * - vs_flags:    all flags except `VIDEO_GFX_F_XYSWAP' and `VIDEO_GFX_F_PALOBJ'
	                                                                 *                `VIDEO_GFX_F_XYSWAP' isn't allowed since another thread may be
	                                                                 *                doing  some logic based on the effective X/Y dimensions of the
	                                                                 *                buffer's default surface,  which might break  if its  X/Y-dims
	                                                                 *                were to randomly swap with each other.
	                                                                 * - vs_colorkey: may be changed as you please
	                                                                 * [[[
	                                                                 * - vs_pal:   Never (technically, allowed if word-aligned reads are
	                                                                 *             atomic, and old pal is static, and new one is static/
	                                                                 *             object, but way too specific to be of any use)
	                                                                 * ]]]
	                                                                 */
	__REF struct video_codec      *__VIDEO_BUFFER_const vb_codec;   /* [1..1][const] Buffer codec. */
	struct video_buffer_ops const *__VIDEO_BUFFER_const vb_ops;     /* [1..1][const] Buffer operations. */
	struct video_domain const     *__VIDEO_BUFFER_const vb_domain;  /* [1..1][const] Buffer domain (generic wrappers use `video_ramdomain()',
	                                                                 * meaning a different value here implies that the buffer was created  by
	                                                                 * that domain's `video_domain_newbuffer()' or `video_domain_formem()') */
	video_dim_t                    __VIDEO_BUFFER_const vb_dim[2];  /* Buffer physical dimension in X and Y (in pixels) */
	__uintptr_t                                         vb_refcnt;  /* Reference counter. */
	/* Buffer-specific fields go here */
};

/* Acquire/release references to sub-objects that any (initialized) buffer must hold */
#ifdef LIBVIDEO_GFX_EXPOSE_INTERNALS
/* Initialize format of `self' from `format'
 * @return: true:  Success
 * @return: false: Error: missing palette */
#define __video_buffer_init_format(self, format)                                           \
	((self)->vb_surf.vs_pal      = (format)->vbf_pal,                                      \
	 (self)->vb_surf.vs_flags    = (format)->vbf_flags,                                    \
	 (self)->vb_surf.vs_colorkey = (format)->vbf_colorkey,                                 \
	 (((self)->vb_codec = (format)->vbf_codec)->vc_specs.vcs_flags & VIDEO_CODEC_FLAG_PAL) \
	 ? ((self)->vb_surf.vs_pal != __NULLPTR)                                               \
	 : ((self)->vb_surf.vs_pal = __NULLPTR, (self)->vb_surf.vs_flags &= ~VIDEO_GFX_F_PALOBJ, 1))
#define __video_buffer_init_domain(self, domain) \
	(void)((self)->vb_domain = (domain))
/* Initialize dimensions of a buffer */
#define __video_buffer_init_dim(self, xdim, ydim) \
	(void)((self)->vb_dim[0] = (xdim), (self)->vb_dim[1] = (ydim))
/* Initialize format+domain+dim for a subregion buffer */
#define __video_buffer_init_subregion(self, parent_surface, parent_buffer, rect) \
	(void)((self)->vb_surf.vs_pal      = (parent_surface)->vs_pal,               \
	       (self)->vb_surf.vs_flags    = (parent_surface)->vs_flags,             \
	       (self)->vb_surf.vs_colorkey = (parent_surface)->vs_colorkey,          \
	       (self)->vb_codec            = (parent_buffer)->vb_codec,              \
	       (self)->vb_domain           = (parent_buffer)->vb_domain,             \
	       __video_buffer_init_dim(self, (rect)->vcr_xdim, (rect)->vcr_ydim))
/* Initialize operators of a buffer */
#define __video_buffer_init_ops(self, ops) \
	(void)((self)->vb_ops = (ops))
#ifdef __INTELLISENSE__
#define __video_buffer_init_common(self) ((self)->vb_surf.vs_buffer = (self))
#define __video_buffer_fini_common(self) (void)(++(self)->vb_surf.vs_buffer)
#else /* __INTELLISENSE__ */
#define __video_buffer_init_common(self)                 \
	(!((self)->vb_surf.vs_flags & VIDEO_GFX_F_PALOBJ) || \
	 (video_palette_incref((self)->vb_surf.vs_pal), 0),  \
	 video_codec_incref((self)->vb_codec),               \
	 (self)->vb_refcnt = 1, (self)->vb_surf.vs_buffer = (self))
#define __video_buffer_fini_common(self)                         \
	(void)(__hybrid_assert((self)->vb_surf.vs_buffer == (self)), \
	       video_codec_decref((self)->vb_codec),                 \
	       !((self)->vb_surf.vs_flags & VIDEO_GFX_F_PALOBJ) ||   \
	       (video_palette_decref((self)->vb_surf.vs_pal), 0))
#endif /* !__INTELLISENSE__ */
#endif /* LIBVIDEO_GFX_EXPOSE_INTERNALS */

#define video_buffer_destroy(self) (*(self)->vb_ops->vi_destroy)(self)
#define video_buffer_incref(self) \
	__hybrid_atomic_inc(&(self)->vb_refcnt, __ATOMIC_SEQ_CST)
#define video_buffer_decref(self)                                            \
	(void)(__hybrid_atomic_decfetch(&(self)->vb_refcnt, __ATOMIC_SEQ_CST) || \
	       (video_buffer_destroy(self), 0))
#define video_buffer_xincref(self) (void)(!(self) || (video_buffer_incref(self), 0))
#define video_buffer_xdecref(self) (void)(!(self) || (video_buffer_decref(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_buffer, vb_refcnt, video_buffer_destroy)


/* Callback prototypes for operators accepted by `video_buffer_forcustom()' */
typedef void (LIBVIDEO_GFX_CC *video_buffer_custom_destroy_t)(void *__cookie);
typedef __ATTR_PURE_T __ATTR_WUNUSED_T video_pixel_t (LIBVIDEO_GFX_CC *video_buffer_custom_getpixel_t)(void *__cookie, video_coord_t __x, video_coord_t __y);
typedef void (LIBVIDEO_GFX_CC *video_buffer_custom_setpixel_t)(void *__cookie, video_coord_t __x, video_coord_t __y, video_pixel_t __pixel);
typedef __ATTR_OUT_T(2) int (LIBVIDEO_GFX_CC *video_buffer_custom_lock_t)(void *__cookie, struct video_lock *__restrict __lock);
typedef __ATTR_IN_T(2) void __NOTHROW_T(LIBVIDEO_GFX_CC *video_buffer_custom_unlock_t)(void *__cookie, struct video_lock *__restrict __lock);
typedef __ATTR_OUT_T(2) int (LIBVIDEO_GFX_CC *video_buffer_custom_lockregion_t)(void *__cookie, struct video_regionlock *__restrict __lock);
typedef __ATTR_IN_T(2) void __NOTHROW_T(LIBVIDEO_GFX_CC *video_buffer_custom_unlockregion_t)(void *__cookie, struct video_regionlock *__restrict __lock);
typedef void __NOTHROW_T(LIBVIDEO_GFX_CC *video_buffer_custom_revoke_t)(void *__cookie);


/* Construct a special video buffer which, rather than being backed by memory
 * or implemented using hardware acceleration,  does all its pixel I/O  using
 * the provided function pointers.
 * NOTE: The returned video buffer exists in the `video_ramdomain()' domain.
 *
 * WARNING: The  given `__getpixel' / `__setpixel' callbacks better be
 *          fast, or any GFX on the returned buffer will take forever!
 *
 * @param: __size_x:       X dimension of the returned video buffer
 * @param: __size_y:       Y dimension of the returned video buffer
 * @param: __format:       [1..1] Video format used for color<=>pixel conversion, as
 *                                well  as pixel I/O  (when __rlock/__wlock is given
 *                                and returns `0')
 * @param: __getpixel:     [1..1] Mandatory pixel read operator (passed coords are absolute and guarantied in-bounds)
 * @param: __setpixel:     [1..1] Mandatory pixel write operator (passed coords are absolute and guarantied in-bounds)
 * @param: __destroy:      [0..1] Optional callback invoked when the returned buffer is destroyed
 * @param: __rlock:        [0..1] Optional callback to lock video memory for reading (when missing, or doesn't return `0', `__getpixel' is always used)
 * @param: __wlock:        [0..1] Optional callback to lock video memory for writing (when missing, or doesn't return `0', `__setpixel' is always used)
 * @param: __unlock:       [0..1] Optional callback invoked to release video locks previously acquired by `__rlock' or `__wlock'
 * @param: __rlockregion:  [0..1] Optional extension to `__rlock' (when not supplied, implemented in terms of `__rlock')
 * @param: __wlockregion:  [0..1] Optional extension to `__wlock' (when not supplied, implemented in terms of `__wlock')
 * @param: __unlockregion: [0..1] Optional extension to `__unlock' (when not supplied, implemented in terms of `__unlock')
 * @param: __revoke:       [0..1] Optional callback invoked when the returned buffer is revoked.
 * @param: __cookie:       [?..?] Cookie argument passed to all user-supplied operators */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((3, 4, 5)) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_BUFFER_FORCUSTOM)(video_dim_t __size_x, video_dim_t __size_y,
                                           struct video_buffer_format const *__restrict __format,
                                           /* TODO: Instead of passing each operator individually,
                                            *       define  a helper struct that packages them all
                                            *       together, and document  that said struct  gets
                                            *       copied (and doesn't need to remain valid) once
                                            *       this call returns. */
                                           video_buffer_custom_getpixel_t __getpixel,
                                           video_buffer_custom_setpixel_t __setpixel,
                                           video_buffer_custom_destroy_t __destroy,
                                           video_buffer_custom_lock_t __rlock,
                                           video_buffer_custom_lock_t __wlock,
                                           video_buffer_custom_unlock_t __unlock,
                                           video_buffer_custom_lockregion_t __rlockregion,
                                           video_buffer_custom_lockregion_t __wlockregion,
                                           video_buffer_custom_unlockregion_t __unlockregion,
                                           video_buffer_custom_revoke_t __revoke,
                                           void *__cookie);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_NONNULL((3, 4, 5)) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_forcustom(video_dim_t __size_x, video_dim_t __size_y,
                       struct video_buffer_format const *__restrict __format,
                       video_buffer_custom_getpixel_t __getpixel,
                       video_buffer_custom_setpixel_t __setpixel,
                       video_buffer_custom_destroy_t __destroy,
                       video_buffer_custom_lock_t __rlock,
                       video_buffer_custom_lock_t __wlock,
                       video_buffer_custom_unlock_t __unlock,
                       video_buffer_custom_lockregion_t __rlockregion,
                       video_buffer_custom_lockregion_t __wlockregion,
                       video_buffer_custom_unlockregion_t __unlockregion,
                       video_buffer_custom_revoke_t __revoke,
                       void *__cookie);
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

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_BUFFER_H */
