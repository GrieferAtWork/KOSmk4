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
#ifndef _LIBVIDEO_GFX_SURFACE_H
#define _LIBVIDEO_GFX_SURFACE_H 1

#include "api.h"
/**/

#include <__crt.h> /* __FILE */
#include <__stdinc.h>

#include <bits/types.h>
#include <kos/anno.h>

#include "../color.h"
#include "../types.h"
#include "blend.h"
#include "gfx-flags.h"

#ifndef __INTELLISENSE__
#include "buffer.h"
#include "codec/codec.h"
#include "codec/palette.h"
#include "surface-defs.h"
#endif /* !__INTELLISENSE__ */

#ifdef __CC__
__DECL_BEGIN

struct video_codec;
struct video_domain;
struct video_surface;
struct video_palette;
struct video_crect;
struct video_buffer;

#ifdef __INTELLISENSE__

/* Helper for initializing a `video_surface' from a `video_buffer' */
extern __ATTR_OUT(1) __ATTR_NONNULL((2)) void
video_surface_frombuffer(struct video_surface *__restrict __self,
                         struct video_buffer *__restrict __buffer);

/* Convenience getter/setter for interacting with a `struct video_surface' */
extern __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct video_domain const *video_surface_getdomain(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct video_codec *video_surface_getcodec(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct video_buffer *video_surface_getbuffer(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_surface_getxdim(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_surface_getydim(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) struct video_palette *video_surface_getpalette(struct video_surface const *__restrict __self);
extern __ATTR_NONNULL((1, 2)) void video_surface_setpalette(struct video_surface *__restrict __self, struct video_palette *__palette);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_gfx_flag_t video_surface_getflags(struct video_surface const *__restrict __self);
extern __ATTR_NONNULL((1)) void video_surface_setflags(struct video_surface *__restrict __self, video_gfx_flag_t __flags);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_pixel_t video_surface_getcolorkey(struct video_surface const *__restrict __self);
extern __ATTR_NONNULL((1)) void video_surface_setcolorkey(struct video_surface *__restrict __self, video_pixel_t __colorkey);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_surface_hascolorkey(struct video_surface const *__restrict __self);
extern __ATTR_NONNULL((1)) void video_surface_enablecolorkey(struct video_surface *__restrict __self, video_pixel_t __colorkey);
extern __ATTR_NONNULL((1)) void video_surface_disablecolorkey(struct video_surface *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) struct video_palette *video_surface_getdefaultpalette(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_gfx_flag_t video_surface_getdefaultflags(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_pixel_t video_surface_getdefaultcolorkey(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_surface_hasdefaultcolorkey(struct video_surface const *__restrict __self);

/* Check if the given video-surface can yield colors with a non-0xff alpha channel */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_surface_hasalpha(struct video_surface const *__restrict __self);

/* Convert between color and pixel values. */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) video_color_t video_surface_pixel2color(struct video_surface const *__restrict __self, video_pixel_t __pixel);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) video_pixel_t video_surface_color2pixel(struct video_surface const *__restrict __self, video_color_t __color);
#ifdef CONFIG_VIDEO_CODEC_HAVE_PIXEL64
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) video_color64_t video_surface_pixel2color64(struct video_surface const *__restrict __self, video_pixel64_t __pixel64);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) video_pixel64_t video_surface_color2pixel64(struct video_surface const *__restrict __self, video_color64_t __color64);
#endif /* CONFIG_VIDEO_CODEC_HAVE_PIXEL64 */

/* Convenience wrappers to get/set the pixel/color of a specific pixel within a memory-mapped line of pixel data */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) video_pixel_t _video_surface_getlinepixel(struct video_surface const *__restrict __self, __byte_t const *__restrict __line, video_coord_t __x);
extern __ATTR_NONNULL((1, 2)) void _video_surface_setlinepixel(struct video_surface const *__restrict __self, __byte_t *__restrict __line, video_coord_t __x, video_pixel_t __pixel);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) video_color_t _video_surface_getlinecolor(struct video_surface const *__restrict __self, __byte_t const *__restrict __line, video_coord_t __x);
extern __ATTR_NONNULL((1, 2)) void _video_surface_setlinecolor(struct video_surface const *__restrict __self, __byte_t *__restrict __line, video_coord_t __x, video_color_t __color);
#ifdef CONFIG_VIDEO_CODEC_HAVE_PIXEL64
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) video_pixel64_t _video_surface_getlinepixel64(struct video_surface const *__restrict __self, __byte_t const *__restrict __line, video_coord_t __x);
extern __ATTR_NONNULL((1, 2)) void _video_surface_setlinepixel64(struct video_surface const *__restrict __self, __byte_t *__restrict __line, video_coord_t __x, video_pixel64_t __pixel64);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) video_color64_t _video_surface_getlinecolor64(struct video_surface const *__restrict __self, __byte_t const *__restrict __line, video_coord_t __x);
extern __ATTR_NONNULL((1, 2)) void _video_surface_setlinecolor64(struct video_surface const *__restrict __self, __byte_t *__restrict __line, video_coord_t __x, video_color64_t __color64);
#endif /* CONFIG_VIDEO_CODEC_HAVE_PIXEL64 */


/* Get graphics functions for use with the given surface.
 * CAUTION: Palette and color key are copied into the GFX context at the time this function
 *          is called. Any further modifications made to either of them must be mirrored in
 *          the created GFX context.
 * @param: blendmode: Pixel blending mode for  graphics operations targeting this  surface.
 *                    This  argument   should  be   constructed  using   `GFX_BLENDMODE()'.
 *                    Usually, you will want to use `GFX_BLENDMODE_ALPHA' as blending  mode
 *                    when you wish to make use of alpha-blending. However, if you know for
 *                    certain  that alpha-blending isn't required, graphics performance can
 *                    be improved by passing  `GFX_BLENDMODE_OVERRIDE' in order to  prevent
 *                    any overhead  that would  normally  incur from  blending  operations.
 * @return: * : Always re-returns `__result' */
extern __ATTR_RETNONNULL __ATTR_IN(1) __ATTR_OUT(2) struct video_gfx *
video_surface_getgfx(struct video_surface const *__self,
                     struct video_gfx *__result,
                     gfx_blendmode_t __blendmode);

/* Create  a new hard subregion-proxy of `__self'.  The caller is responsible to ensure
 * that  the given `__rect' does not exceed `__self->vb_xdim' / `__self->vb_ydim'. Note
 * that this function behaves slightly different from `video_surface_region()', in that
 * the later accepts a signed  rect, while also allowing said  rect to be greater  than
 * the dimensions of the original buffer.
 *
 * On the other hand, this function only works for creating **true** sub-rects, but
 * since this one is implemented by individual buffers, it is probably faster, too.
 *
 * Buffers  returned by this function are guarantied  to share pixel access with `__self',
 * and `video_buffer_revoke' is to `__self' will  also revoke access for `return'  (either
 * directly, by keeping a list of sub-region buffers in `__self', or indirectly, by having
 * every access to pixel-data in `return' check if `__self' has been revoked).
 *
 * NOTE: This function will never re-return `__self', even if `__rect' is the  full
 *       rect of `__self', and `__self' describes the buffer's default format. This
 *       is because doing also cause `vi_revoke' invoked on the returned buffer  to
 *       revoke `__self'.
 *
 * @assume(__rect->vcr_xdim > 0);
 * @assume(__rect->vcr_ydim > 0);
 * @assume((__rect->vcr_xmin + __rect->vcr_xdim) > __rect->vcr_xmin);
 * @assume((__rect->vcr_ymin + __rect->vcr_ydim) > __rect->vcr_ymin);
 * @assume((__rect->vcr_xmin + __rect->vcr_xdim) <= __self->vb_xdim);
 * @assume((__rect->vcr_ymin + __rect->vcr_ydim) <= __self->vb_ydim);
 * @param: __self: Video surface to create a sub-region of (returned
 *                 buffer's format  is derived  from this  surface).
 * @param: __rect: Sub-region rect of `__self' to-be returned
 * @return: * : The newly created sub-region buffer
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=*] Failed to create sub-region for some other reason */
extern __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __REF struct video_buffer *
video_surface_subregion(struct video_surface const *__restrict __self,
                        struct video_crect const *__restrict __rect);
#else /* __INTELLISENSE__ */
#define video_surface_frombuffer(self, buffer)                    \
	(void)((self)->vs_pal      = video_buffer_getpalette(buffer), \
	       (self)->vs_buffer   = (buffer),                        \
	       (self)->vs_flags    = video_buffer_getflags(buffer),   \
	       (self)->vs_colorkey = video_buffer_getcolorkey(buffer))
#define video_surface_getdomain(self)                video_buffer_getdomain(video_surface_getbuffer(self))
#define video_surface_getcodec(self)                 video_buffer_getcodec(video_surface_getbuffer(self))
#define video_surface_getbuffer(self)                (self)->vs_buffer
#define video_surface_getxdim(self)                  video_buffer_getxdim(video_surface_getbuffer(self))
#define video_surface_getydim(self)                  video_buffer_getydim(video_surface_getbuffer(self))
#define video_surface_getpalette(self)               (self)->vs_pal
#define video_surface_setpalette(self, palette)      (void)((self)->vs_pal = (palette))
#define video_surface_getflags(self)                 (self)->vs_flags
#define video_surface_setflags(self, flags)          (void)((self)->vs_flags = (flags))
#define video_surface_getcolorkey(self)              (self)->vs_colorkey
#define video_surface_setcolorkey(self, colorkey)    (void)((self)->vs_colorkey = (colorkey))
#define video_surface_hascolorkey(self)              ((video_surface_getflags(self) & VIDEO_GFX_F_COLORKEY) != 0)
#define video_surface_enablecolorkey(self, colorkey) (void)((self)->vs_colorkey = (colorkey), (self)->vs_flags |= VIDEO_GFX_F_COLORKEY)
#define video_surface_disablecolorkey(self)          (void)((self)->vs_flags &= ~VIDEO_GFX_F_COLORKEY)
#define video_surface_getdefaultpalette(self)        video_buffer_getpalette(video_surface_getbuffer(self))
#define video_surface_getdefaultflags(self)          video_buffer_getflags(video_surface_getbuffer(self))
#define video_surface_getdefaultcolorkey(self)       video_buffer_getcolorkey(video_surface_getbuffer(self))
#define video_surface_hasdefaultcolorkey(self)       video_buffer_hascolorkey(video_surface_getbuffer(self))
#define video_surface_hasalpha(self)                            \
	((video_surface_getcodec(self)->vc_specs.vcs_amask != 0) || \
	 (video_surface_getpalette(self) && (video_surface_getpalette(self)->vp_flags & VIDEO_PALETTE_F_ALPHA)))
#define video_surface_pixel2color(self, pixel)            (*video_surface_getcodec(self)->vc_pixel2color)(self, pixel)
#define video_surface_color2pixel(self, color)            (*video_surface_getcodec(self)->vc_color2pixel)(self, color)
#define _video_surface_getlinepixel(self, line, x)        (*video_surface_getcodec(self)->vc_getpixel)(line, x)
#define _video_surface_setlinepixel(self, line, x, pixel) (*video_surface_getcodec(self)->vc_setpixel)(line, x, pixel)
#define _video_surface_getlinecolor(self, line, x)        video_surface_pixel2color(self, _video_surface_getlinepixel(self, line, x))
#define _video_surface_setlinecolor(self, line, x, color) _video_surface_setlinepixel(self, line, x, video_surface_color2pixel(self, color))
#ifdef CONFIG_VIDEO_CODEC_HAVE_PIXEL64
#define video_surface_pixel2color64(self, pixel64)            (*video_surface_getcodec(self)->vc_pixel2color64)(self, pixel64)
#define video_surface_color2pixel64(self, color64)            (*video_surface_getcodec(self)->vc_color2pixel64)(self, color64)
#define _video_surface_getlinepixel64(self, line, x)          (*video_surface_getcodec(self)->vc_getpixel64)(line, x)
#define _video_surface_setlinepixel64(self, line, x, pixel64) (*video_surface_getcodec(self)->vc_setpixel64)(line, x, pixel64)
#define _video_surface_getlinecolor64(self, line, x)          video_surface_pixel2color64(self, _video_surface_getlinepixel64(self, line, x))
#define _video_surface_setlinecolor64(self, line, x, color64) _video_surface_setlinepixel64(self, line, x, video_surface_color2pixel64(self, color64))
#endif /* CONFIG_VIDEO_CODEC_HAVE_PIXEL64 */

#define video_surface_getgfx(self, result, blendmode) \
	((result)->vx_blend = (blendmode),                \
	 (*((result)->vx_surf = *(self)).vs_buffer->vb_ops->vi_initgfx)(result))
#define video_surface_subregion(self, rect) \
	(*video_surface_getbuffer(self)->vb_ops->vi_subregion)(self, rect)
#endif /* !__INTELLISENSE__ */


/* Create a new region-relative-proxy of `__self', that interacts with the same
 * pixel data, both during GFX operations,  as well when creating video  locks.
 *
 * You can also use  this function to create  regions at negative offsets,  or
 * ones that are larger than `__self'. In this case, the returned buffer  will
 * not be lockable, except when using `video_buffer_r/wlockregion' for regions
 * that  contain actual pixel  data. Similarly, GFX  operations for pixel data
 * outside  the true pixel area (which is enforced  by the I/O Rect of any GFX
 * created using the returned  buffer), will yield "0"  during read, and be  a
 * no-op during write.
 *
 * Then returned buffer always behaves properly when it comes to being able to
 * be  revoked, after which point it will never again make any access to pixel
 * data of `__self'.
 *
 * When the given `__rect' is actually  a sub-region of `__self', then  this
 * function will simply make use of `video_surface_subregion()' and call the
 * dedicated video buffer operator for creating sub-regions.
 *
 * When the returned buffer isn't created as a true sub-region of `__self',
 * its  `vb_domain' will be set to the return value of `video_ramdomain()'.
 *
 * @param: __self: Video buffer to create a region of
 * @param: __rect: region rect of `__self' to-be returned
 * @return: * : The newly created region buffer
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=*] Failed to create region for some other reason */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_IN_T(2) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_SURFACE_REGION)(struct video_surface const *__restrict __self,
                                         struct video_rect const *__restrict __rect);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_surface_region(struct video_surface const *__restrict __self,
                     struct video_rect const *__restrict __rect);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */
/* TODO: Change `video_surface_region()' to take an extra "region_flags" argument,
 *       that can be used to select  how the sub-region/flags should be  enforced:
 *       - TRANSFORM_GFXONLY (current behavior: rotation only appears within video_gfx)
 *       - TRANSFORM_ALWAYS  (region/flags are always enforced. video locks will either
 *                            fail, or expose properly rotated/clipped pixel data)
 *       Another flag:
 *       - REVOKE_SHAREABLE  (allow `video_buffer_revoke(return)' to also revoke the
 *                            original buffer, though this behavior is not mandatory) */
/* With all of the above TODOs implemented, this function can be removed and its current
 * semantics can be implemented as:
 * >> temp = video_surface_region(video_gfx_getbuffer(self), IO_RECT_OF(self), video_gfx_getflags(self), TRANSFORM_ALWAYS | REVOKE_SHAREABLE);
 * >> return video_surface_region(temp, CLIP_RECT_RELATIVE_TO_IO_OF(self), 0, REVOKE_SHAREABLE); */



/* Same  as  `video_buffer_*save', but  save pixel
 * data using the palette and GFX flags of `self'.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) int /* TODO */
(LIBVIDEO_GFX_CC *PVIDEO_SURFACE_FSAVE)(struct video_surface const *__self, char const *__format,
                                        __FILE *__restrict __fp, char const *__options);
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) int /* TODO */
(LIBVIDEO_GFX_CC *PVIDEO_SURFACE_FDSAVE)(struct video_surface const *__self, char const *__format,
                                         __fd_t __fd, char const *__options);
typedef /*__ATTR_WUNUSED_T*/ __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) int /* TODO */
(LIBVIDEO_GFX_CC *PVIDEO_SURFACE_SAVE)(struct video_surface const *__self, char const *__filename,
                                       char const *__options);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_NONNULL((2)) int LIBVIDEO_GFX_CC /* TODO */
video_surface_fsave(struct video_surface const *__self, char const *__format,
                    __FILE *__restrict __fp, char const *__options);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_NONNULL((2)) int LIBVIDEO_GFX_CC /* TODO */
video_surface_fdsave(struct video_surface const *__self, char const *__format,
                     __fd_t __fd, char const *__options);
LIBVIDEO_GFX_DECL /*__ATTR_WUNUSED*/ __ATTR_IN(1) __ATTR_NONNULL((2)) int LIBVIDEO_GFX_CC /* TODO */
video_surface_save(struct video_surface const *__self, char const *__filename,
                   char const *__options);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
__LOCAL __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN(2) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_buffer_region(struct video_buffer *__restrict __self,
                    struct video_rect const *__restrict __rect) {
	struct video_surface __self_surf;
	video_surface_frombuffer(&__self_surf, __self);
	return video_surface_region(&__self_surf, __rect);
}
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_SURFACE_H */
