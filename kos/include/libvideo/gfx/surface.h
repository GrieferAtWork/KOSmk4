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
#include "surface-defs.h"

#ifndef __INTELLISENSE__
#include "../crect.h"
#include "../rect.h"
#include "buffer.h"
#include "codec/codec.h"
#include "codec/palette.h"
#include "gfx.h"
#endif /* !__INTELLISENSE__ */

#ifdef __CC__
__DECL_BEGIN

struct video_codec;
struct video_domain;
struct video_surface;
struct video_palette;
struct video_gfx;
struct video_rect;
struct video_crect;
struct video_buffer;
struct video_buffer_format;

#ifdef __INTELLISENSE__

/* Create/drop  references to reference-counted elements of a video_surface.
 * These can be used to let a `struct video_surface' remain alive even after
 * all caller-held reference to an associated buffer/palette were dropped. */
extern __ATTR_IN(1) void video_surface_incref(struct video_surface const *__restrict __self);
extern __ATTR_IN(1) void video_surface_decref(struct video_surface const *__restrict __self);

/* Check if a given video surface uses the specified format. */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __BOOL
video_surface_hasformat(struct video_surface const *__restrict __self,
                        struct video_buffer_format const *__restrict __format);

/* Fill in `__format' with the format used by `__self' */
extern __ATTR_IN(1) __ATTR_OUT(2) void
video_surface_getformat(struct video_surface const *__restrict __self,
                        struct video_buffer_format *__restrict __format);

/* Fill in `__format' with the default format used by `__self' */
extern __ATTR_IN(1) __ATTR_OUT(2) void
video_surface_getdefaultformat(struct video_surface const *__restrict __self,
                               struct video_buffer_format *__restrict __format);



/* Convenience getter/setter for interacting with a `struct video_surface' */
extern __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct video_domain const *video_surface_getdomain(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct video_codec *video_surface_getcodec(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct video_buffer *video_surface_getbuffer(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_surface_getxdim(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_surface_getydim(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_surface_hasobjpalette(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) struct video_palette *video_surface_getpalette(struct video_surface const *__restrict __self);
extern __ATTR_NONNULL((1, 2)) void video_surface_setpalette(struct video_surface *__restrict __self, struct video_palette const *__palette, __BOOL __isobj);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_gfx_flag_t video_surface_getflags(struct video_surface const *__restrict __self);
extern __ATTR_NONNULL((1)) void video_surface_setflags(struct video_surface *__restrict __self, video_gfx_flag_t __flags);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_pixel_t video_surface_getcolorkey(struct video_surface const *__restrict __self);
extern __ATTR_NONNULL((1)) void video_surface_setcolorkey(struct video_surface *__restrict __self, video_pixel_t __colorkey);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_surface_hascolorkey(struct video_surface const *__restrict __self);
extern __ATTR_NONNULL((1)) void video_surface_enablecolorkey(struct video_surface *__restrict __self, video_pixel_t __colorkey);
extern __ATTR_NONNULL((1)) void video_surface_disablecolorkey(struct video_surface *__restrict __self);

/* Return a lower bound for the # of colors that a palette linked to this surface has to
 * have. If the surface doesn't make use  of palettes, this returns an undefined  value. */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_pixel_t
video_surface_getpalcolorcount(struct video_surface const *__restrict __self);

/* Assign `__colors' to-be used as palette for `__self'. The caller must ensure that this array
 * of  colors remains allocated until a different palette  is assigned, or the surface (and any
 * video buffer created from it) is disposed.
 *
 * Same as:
 * >> video_surface_setpalette(__self, video_palette_fromcolors(__colors), false);
 *
 * CAUTION: By assigning a non-object-based color palette, GFX operations will be drastically
 *          slower, since the palette will have to be re-transmitted to the GPU or the window
 *          manager with every GFX operation. */
extern __ATTR_NONNULL((1, 2)) void
video_surface_setpalcolors(struct video_surface *__restrict __self,
                           video_color_t const __colors[]);

/* Return a pointer to the palette colors used by `__self', or `NULL' if no palette is being used. */
extern __ATTR_WUNUSED __ATTR_IN(1) video_color_t const *
video_surface_getpalcolors(struct video_surface const *__restrict __self);


/* Check if `__self' is the default surface of a `video_buffer' */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_surface_isbuffer(struct video_surface const *__restrict __self);

/* Check if properties of `__self' match the default properties of the associated
 * buffer.  Note that when `video_surface_isbuffer()' is true, this is also true. */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __BOOL video_surface_isdefault(struct video_surface const *__restrict __self);

/* Update attributes of `__self' to match the associated buffer's default attributes */
extern __ATTR_INOUT(1) void video_surface_setdefault(struct video_surface *__restrict __self);

/* Copy all writable  attributes from  `__src' into  `__self'.
 * This will update all fields of `__self', except `vs_buffer' */
extern __ATTR_INOUT(1) __ATTR_IN(2) void
video_surface_copyattrib(struct video_surface *__restrict __self,
                         struct video_surface const *__restrict __src);

/* Same as  `video_surface_getxdim()' /  `video_surface_getydim()',
 * but `VIDEO_GFX_F_XYSWAP' doesn't cause dimensions to be swapped. */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_surface_getbufferxdim(struct video_surface const *__restrict __self);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) video_dim_t video_surface_getbufferydim(struct video_surface const *__restrict __self);


/* Return default surface properties from the associated `struct video_buffer' */
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

/* Same as above, but use the `strct video_surface' wrapped by a given `struct video_gfx' */
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) video_color_t video_gfx_pixel2color(struct video_gfx const *__restrict __self, video_pixel_t __pixel);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) video_pixel_t video_gfx_color2pixel(struct video_gfx const *__restrict __self, video_color_t __color);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) video_pixel_t _video_gfx_getlinepixel(struct video_gfx const *__restrict __self, __byte_t const *__restrict __line, video_coord_t __x);
extern __ATTR_NONNULL((1, 2)) void _video_gfx_setlinepixel(struct video_gfx const *__restrict __self, __byte_t *__restrict __line, video_coord_t __x, video_pixel_t __pixel);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) video_color_t _video_gfx_getlinecolor(struct video_gfx const *__restrict __self, __byte_t const *__restrict __line, video_coord_t __x);
extern __ATTR_NONNULL((1, 2)) void _video_gfx_setlinecolor(struct video_gfx const *__restrict __self, __byte_t *__restrict __line, video_coord_t __x, video_color_t __color);
#ifdef CONFIG_VIDEO_CODEC_HAVE_PIXEL64
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) video_color64_t video_gfx_pixel2color64(struct video_gfx const *__restrict __self, video_pixel64_t __pixel64);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) video_pixel64_t video_gfx_color2pixel64(struct video_gfx const *__restrict __self, video_color64_t __color64);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) video_pixel64_t _video_gfx_getlinepixel64(struct video_gfx const *__restrict __self, __byte_t const *__restrict __line, video_coord_t __x);
extern __ATTR_NONNULL((1, 2)) void _video_gfx_setlinepixel64(struct video_gfx const *__restrict __self, __byte_t *__restrict __line, video_coord_t __x, video_pixel64_t __pixel64);
extern __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) video_color64_t _video_gfx_getlinecolor64(struct video_gfx const *__restrict __self, __byte_t const *__restrict __line, video_coord_t __x);
extern __ATTR_NONNULL((1, 2)) void _video_gfx_setlinecolor64(struct video_gfx const *__restrict __self, __byte_t *__restrict __line, video_coord_t __x, video_color64_t __color64);
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
 * @assume(__rect->vcr_xdim > 0);
 * @assume(__rect->vcr_ydim > 0);
 * @assume((__rect->vcr_xmin + __rect->vcr_xdim) > __rect->vcr_xmin);
 * @assume((__rect->vcr_ymin + __rect->vcr_ydim) > __rect->vcr_ymin);
 * @assume((__rect->vcr_xmin + __rect->vcr_xdim) <= video_surface_getxdim(__self));
 * @assume((__rect->vcr_ymin + __rect->vcr_ydim) <= video_surface_getydim(__self));
 * @assume(__buffer_rect->vcr_xdim > 0);
 * @assume(__buffer_rect->vcr_ydim > 0);
 * @assume((__buffer_rect->vcr_xmin + __buffer_rect->vcr_xdim) > __buffer_rect->vcr_xmin);
 * @assume((__buffer_rect->vcr_ymin + __buffer_rect->vcr_ydim) > __buffer_rect->vcr_ymin);
 * @assume((__buffer_rect->vcr_xmin + __buffer_rect->vcr_xdim) <= video_surface_getbufferxdim(__self));
 * @assume((__buffer_rect->vcr_ymin + __buffer_rect->vcr_ydim) <= video_surface_getbufferydim(__self));
 * @param: __self: Video surface to create a sub-region of (returned
 *                 buffer's format  is derived  from this  surface).
 * @param: __rect/__buffer_rect: Sub-region rect of `__self' (or its buffer) to-be returned
 * @return: * : The newly created sub-region buffer
 * @return: NULL: [errno=ENOMEM] Insufficient memory
 * @return: NULL: [errno=*] Failed to create sub-region for some other reason */
extern __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __REF struct video_buffer *
video_surface_subregion(struct video_surface const *__restrict __self,
                        struct video_crect const *__restrict __rect);
extern __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __REF struct video_buffer *
video_surface_subregion_distinct(struct video_surface const *__restrict __self,
                                 struct video_crect const *__restrict __rect);
extern __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __REF struct video_buffer *
_video_surface_subregion(struct video_surface const *__restrict __self,
                         struct video_crect const *__restrict __buffer_rect);
extern __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __REF struct video_buffer *
_video_surface_subregion_distinct(struct video_surface const *__restrict __self,
                                  struct video_crect const *__restrict __buffer_rect);


/* Helpers wrappers for applying `video_surface' operations directly to `video_buffer' */
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN(2) __REF struct video_buffer *
video_buffer_subregion(struct video_buffer *__restrict __self,
                       struct video_crect const *__restrict __buffer_rect);
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN(2) __REF struct video_buffer *
video_buffer_subregion_distinct(struct video_buffer *__restrict __self,
                                struct video_crect const *__restrict __buffer_rect);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN(2) __REF struct video_buffer *
video_buffer_region(struct video_buffer *__restrict __self,
                    struct video_rect const *__restrict __buffer_rect);
extern __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_IN(2) __REF struct video_buffer *
video_buffer_region_distinct(struct video_buffer *__restrict __self,
                             struct video_rect const *__restrict __buffer_rect);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

/* Do the inverse of `video_buffer_*open' and save the contents of a video buffer
 * into  a file/memory/stream. The same set of  file formats is supported as also
 * supported by `video_buffer_*open', and the intended file format is  determined
 * by the given `format' argument, which should be the case-insensitive extension
 * (without a leading ".") of the format (e.g. "png" for PNG files).
 *
 * If rotation/mirroring/etc.  are specified  by `__self->vb_surf',  information
 * about those is either also stored in the produced image file (if supported by
 * the respective image format), or `__self' is converted into a normalized form
 * first (using `video_buffer_convert()'), and then its pixel data is stored.
 * IOW: GFX-only rotation is included in the produced image file.
 *
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
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
extern __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
video_buffer_fsave(struct video_buffer *__self, char const *__format,
                   __FILE *__restrict __fp, char const *__options);
extern __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
video_buffer_fdsave(struct video_buffer *__self, char const *__format,
                    __fd_t __fd, char const *__options);
extern /*__ATTR_WUNUSED*/ __ATTR_NONNULL((1, 2)) int
video_buffer_save(struct video_buffer *__self, char const *__filename,
                  char const *__options);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Helper wrapper for converting a `video_buffer' into a different format */
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
extern __ATTR_WUNUSED __ATTR_IN(1) __ATTR_NONNULL((2)) __ATTR_IN(3) __REF struct video_buffer *
video_buffer_convert(struct video_buffer *__restrict __self,
                     struct video_domain const *__domain,
                     struct video_buffer_format const *__format);
extern __ATTR_WUNUSED __ATTR_IN(1) __ATTR_NONNULL((2)) __ATTR_IN(3) __REF struct video_buffer *
video_buffer_convert_distinct(struct video_buffer *__restrict __self,
                              struct video_domain const *__domain,
                              struct video_buffer_format const *__format);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */
#else /* __INTELLISENSE__ */
#define video_surface_incref(self)                                    \
	(void)(!(video_surface_getflags(self) & VIDEO_GFX_F_PALOBJ) ||    \
	       (video_palette_incref(video_surface_getpalette(self)), 0), \
	       video_buffer_incref(video_surface_getbuffer(self)))
#define video_surface_decref(self)                                 \
	(void)(video_buffer_decref(video_surface_getbuffer(self)),     \
	       !(video_surface_getflags(self) & VIDEO_GFX_F_PALOBJ) || \
	       (video_palette_decref(video_surface_getpalette(self)), 0))
#define video_surface_hasformat(self, format)                                            \
	(video_surface_getcodec(self) == (format)->vbf_codec &&                              \
	 video_surface_getflags(self) == (format)->vbf_flags &&                              \
	 (!video_surface_getpal(self) || video_surface_getpal(self) == (format)->vbf_pal) && \
	 (!video_surface_hascolorkey(self) || video_surface_getcolorkey(self) == (format)->vbf_colorkey))
#define video_surface_getformat(self, format)                       \
	(void)((format)->vbf_pal      = video_surface_getpalette(self), \
	       (format)->vbf_codec    = video_surface_getcodec(self),   \
	       (format)->vbf_flags    = video_surface_getflags(self),   \
	       (format)->vbf_colorkey = video_surface_getcolorkey(self))
#define video_surface_getdefaultformat(self, format)                       \
	(void)((format)->vbf_pal      = video_surface_getdefaultpalette(self), \
	       (format)->vbf_codec    = video_surface_getcodec(self),          \
	       (format)->vbf_flags    = video_surface_getdefaultflags(self),   \
	       (format)->vbf_colorkey = video_surface_getdefaultcolorkey(self))
#define video_surface_isbuffer(self) \
	(video_buffer_assurface(video_surface_getbuffer(self)) == (self))
#define video_surface_isdefault(self)                                           \
	(video_surface_getpalette(self) == video_surface_getdefaultpalette(self) && \
	 video_surface_getflags(self) == video_surface_getdefaultflags(self) &&     \
	 video_surface_getcolorkey(self) == video_surface_getdefaultcolorkey(self))
#define video_surface_setdefault(self)                                  \
	(void)((self)->vs_pal      = video_surface_getdefaultpalette(self), \
	       (self)->vs_flags    = video_surface_getdefaultflags(self),   \
	       (self)->vs_colorkey = video_surface_getdefaultcolorkey(self))
#define video_surface_copyattrib(self, src)                     \
	(void)((self)->vs_pal      = video_surface_getpalette(src), \
	       (self)->vs_flags    = video_surface_getflags(src),   \
	       (self)->vs_colorkey = video_surface_getcolorkey(src))
#define video_surface_getdomain(self)                  video_buffer_getdomain(video_surface_getbuffer(self))
#define video_surface_getcodec(self)                   video_buffer_getcodec(video_surface_getbuffer(self))
#define video_surface_getbuffer(self)                  (self)->vs_buffer
#define video_surface_getbufferxdim(self)              video_buffer_getxdim(video_surface_getbuffer(self))
#define video_surface_getbufferydim(self)              video_buffer_getydim(video_surface_getbuffer(self))
/* TODO: Change vb_xdim / vb_ydim into vb_dim[2] and use ((flags & VIDEO_GFX_F_XYSWAP) [^ 1]) as index */
#define video_surface_getxdim(self)                    (__unlikely(video_surface_getflags(self) & VIDEO_GFX_F_XYSWAP) ? video_surface_getbufferydim(self) : video_surface_getbufferxdim(self))
#define video_surface_getydim(self)                    (__unlikely(video_surface_getflags(self) & VIDEO_GFX_F_XYSWAP) ? video_surface_getbufferxdim(self) : video_surface_getbufferydim(self))
#define video_surface_hasobjpalette(self)              (((self)->vs_flags & VIDEO_GFX_F_PALOBJ) != 0)
#define video_surface_getpalette(self)                 (self)->vs_pal
#define video_surface_setpalette(self, palette, isobj) (void)((self)->vs_pal = (palette), (self)->vs_flags = ((self)->vs_flags & ~VIDEO_GFX_F_PALOBJ) | ((isobj) ? VIDEO_GFX_F_PALOBJ : 0))
#define video_surface_getflags(self)                   (self)->vs_flags
#define video_surface_setflags(self, flags)            (void)((self)->vs_flags = (flags))
#define video_surface_getcolorkey(self)                (self)->vs_colorkey
#define video_surface_setcolorkey(self, colorkey)      (void)((self)->vs_colorkey = (colorkey))
#define video_surface_hascolorkey(self)                ((video_surface_getflags(self) & VIDEO_GFX_F_COLORKEY) != 0)
#define video_surface_enablecolorkey(self, colorkey)   (void)((self)->vs_colorkey = (colorkey), (self)->vs_flags |= VIDEO_GFX_F_COLORKEY)
#define video_surface_disablecolorkey(self)            (void)((self)->vs_flags &= ~VIDEO_GFX_F_COLORKEY)
#define video_surface_getpalcolorcount(self)           video_codec_getpalcolors(video_surface_getcodec(self))
#define video_surface_setpalcolors(self, colors)       (void)((self)->vs_pal = video_palette_fromcolors(palette), (self)->vs_flags &= ~VIDEO_GFX_F_PALOBJ)
#define video_surface_getpalcolors(self)               video_palette_getcolors(video_surface_getpalette(self))
#define video_surface_getdefaultpalette(self)          video_buffer_getpalette(video_surface_getbuffer(self))
#define video_surface_getdefaultflags(self)            video_buffer_getflags(video_surface_getbuffer(self))
#define video_surface_getdefaultcolorkey(self)         video_buffer_getcolorkey(video_surface_getbuffer(self))
#define video_surface_hasdefaultcolorkey(self)         video_buffer_hascolorkey(video_surface_getbuffer(self))
#define video_surface_hasalpha(self)                            \
	((video_surface_getcodec(self)->vc_specs.vcs_amask != 0) || \
	 (video_surface_getpalette(self) &&                         \
	  (!video_surface_hasobjpalette(self) ||                    \
	   video_palette_asobject(video_surface_getpalette(self))->vp_flags & VIDEO_PALETTE_F_ALPHA)))
#define video_surface_pixel2color(self, pixel)            (*video_surface_getcodec(self)->vc_pixel2color)(self, pixel)
#define video_surface_color2pixel(self, color)            (*video_surface_getcodec(self)->vc_color2pixel)(self, color)
#define _video_surface_getlinepixel(self, line, x)        (*video_surface_getcodec(self)->vc_getpixel)(line, x)
#define _video_surface_setlinepixel(self, line, x, pixel) (*video_surface_getcodec(self)->vc_setpixel)(line, x, pixel)
#define _video_surface_getlinecolor(self, line, x)        video_surface_pixel2color(self, _video_surface_getlinepixel(self, line, x))
#define _video_surface_setlinecolor(self, line, x, color) _video_surface_setlinepixel(self, line, x, video_surface_color2pixel(self, color))
#define video_gfx_pixel2color(self, pixel)                video_surface_pixel2color(video_gfx_assurface(self), pixel)
#define video_gfx_color2pixel(self, color)                video_surface_color2pixel(video_gfx_assurface(self), color)
#define _video_gfx_getlinepixel(self, line, x)            _video_surface_getlinepixel(video_gfx_assurface(self), line, x)
#define _video_gfx_setlinepixel(self, line, x, pixel)     _video_surface_setlinepixel(video_gfx_assurface(self), line, x, pixel)
#define _video_gfx_getlinecolor(self, line, x)            _video_surface_getlinecolor(video_gfx_assurface(self), line, x)
#define _video_gfx_setlinecolor(self, line, x, color)     _video_surface_setlinecolor(video_gfx_assurface(self), line, x, color)
#ifdef CONFIG_VIDEO_CODEC_HAVE_PIXEL64
#define video_surface_pixel2color64(self, pixel64)            (*video_surface_getcodec(self)->vc_pixel2color64)(self, pixel64)
#define video_surface_color2pixel64(self, color64)            (*video_surface_getcodec(self)->vc_color2pixel64)(self, color64)
#define _video_surface_getlinepixel64(self, line, x)          (*video_surface_getcodec(self)->vc_getpixel64)(line, x)
#define _video_surface_setlinepixel64(self, line, x, pixel64) (*video_surface_getcodec(self)->vc_setpixel64)(line, x, pixel64)
#define _video_surface_getlinecolor64(self, line, x)          video_surface_pixel2color64(self, _video_surface_getlinepixel64(self, line, x))
#define _video_surface_setlinecolor64(self, line, x, color64) _video_surface_setlinepixel64(self, line, x, video_surface_color2pixel64(self, color64))
#define video_gfx_pixel2color64(self, pixel64)                video_surface_pixel2color64(video_gfx_assurface(self), pixel64)
#define video_gfx_color2pixel64(self, color64)                video_surface_color2pixel64(video_gfx_assurface(self), color64)
#define _video_gfx_getlinepixel64(self, line, x)              _video_surface_getlinepixel64(video_gfx_assurface(self), line, x)
#define _video_gfx_setlinepixel64(self, line, x, pixel64)     _video_surface_setlinepixel64(video_gfx_assurface(self), line, x, pixel64)
#define _video_gfx_getlinecolor64(self, line, x)              _video_surface_getlinecolor64(video_gfx_assurface(self), line, x)
#define _video_gfx_setlinecolor64(self, line, x, color64)     _video_surface_setlinecolor64(video_gfx_assurface(self), line, x, color64)
#endif /* CONFIG_VIDEO_CODEC_HAVE_PIXEL64 */

#define video_surface_getgfx(self, result, blendmode) \
	((result)->vx_blend = (blendmode),                \
	 (*((result)->vx_surf = *(self)).vs_buffer->vb_ops->vi_initgfx)(result))
#define _video_surface_subregion_distinct(self, buffer_rect) \
	(*video_surface_getbuffer(self)->vb_ops->vi_subregion)(self, buffer_rect)
#define _video_surface_subregion(self, buffer_rect)                   \
	(((buffer_rect)->vcr_xmin == 0 && (buffer_rect)->vcr_ymin == 0 && \
	  (buffer_rect)->vcr_xdim == video_surface_getbufferxdim(self) && \
	  (buffer_rect)->vcr_ydim == video_surface_getbufferydim(self) && \
	  video_surface_isdefault(self))                                  \
	 ? (video_buffer_incref(video_surface_getbuffer(self)),           \
	    video_surface_getbuffer(self))                                \
	 : _video_surface_subregion_distinct(self, buffer_rect))

__LOCAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __REF struct video_buffer *
video_surface_subregion_distinct(struct video_surface const *__restrict __self,
                                 struct video_crect const *__restrict __rect) {
	struct video_crect __buffer_rect;
	if unlikely(video_surface_getflags(__self) & VIDEO_GFX_F_XYSWAP) {
		__buffer_rect.vcr_xmin = __rect->vcr_ymin;
		__buffer_rect.vcr_ymin = __rect->vcr_xmin;
		__buffer_rect.vcr_xdim = __rect->vcr_ydim;
		__buffer_rect.vcr_ydim = __rect->vcr_xdim;
		__rect = &__buffer_rect;
	}
	return _video_surface_subregion_distinct(__self, __rect);
}
#define video_surface_subregion(self, buffer_rect)                    \
	(((buffer_rect)->vcr_xmin == 0 && (buffer_rect)->vcr_ymin == 0 && \
	  (buffer_rect)->vcr_xdim == video_surface_getxdim(self) &&       \
	  (buffer_rect)->vcr_ydim == video_surface_getydim(self) &&       \
	  video_surface_isdefault(self))                                  \
	 ? (video_buffer_incref(video_surface_getbuffer(self)),           \
	    video_surface_getbuffer(self))                                \
	 : video_surface_subregion_distinct(self, buffer_rect))
#define video_buffer_subregion_distinct(self, rect) \
	_video_surface_subregion_distinct(video_buffer_assurface(self), rect)
#define video_buffer_subregion(self, rect)              \
	(((rect)->vcr_xmin == 0 && (rect)->vcr_ymin == 0 && \
	  (rect)->vcr_xdim == video_buffer_getxdim(self) && \
	  (rect)->vcr_ydim == video_buffer_getydim(self))   \
	 ? (video_buffer_incref(self), self)                \
	 : video_buffer_subregion_distinct(self, rect))
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
#define video_buffer_region(self, rect) \
	video_surface_region(video_buffer_assurface(self), rect)
#define video_buffer_region_distinct(self, rect) \
	video_surface_region_distinct(video_buffer_assurface(self), rect)
#define video_buffer_fsave(self, format, fp, options) \
	video_surface_fsave(video_buffer_assurface(self), format, fp, options)
#define video_buffer_fdsave(self, format, fd, options) \
	video_surface_fdsave(video_buffer_assurface(self), format, fd, options)
#define video_buffer_save(self, filename, options) \
	video_surface_save(video_buffer_assurface(self), filename, options)
#define video_buffer_convert(self, domain, format) \
	video_surface_convert(video_buffer_assurface(self), domain, format)
#define video_buffer_convert_distinct(self, domain, format) \
	video_surface_convert_distinct(video_buffer_assurface(self), domain, format)
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */
#endif /* !__INTELLISENSE__ */


/* Convert `__self' into the specified domain and format.
 *
 * If `__self' specifies rotation/etc. in its GFX flags, and that rotation differs
 * from whatever is specified by `__format' (including the case where the state of
 * the `VIDEO_GFX_F_XYSWAP' flag differs, meaning  dimensions of `__self' and  the
 * returned buffer won't match up), that rotation info is materialized, such  that
 * this  function can also  be used to rotate  the actual V-mem  of a video buffer
 * whilst at the same time copying/converting it into a different format.
 *
 * @return: * : The converted video buffer.
 * @return: NULL: [errno=ENOMEM]  Insufficient memory (either regular RAM, or V-RAM)
 * @return: NULL: [errno=ENOTSUP] Given `__format->vbf_codec' is not supported by `__domain ?: video_surface_getdomain(__self)'
 * @return: NULL: [errno=*] Failed to convert buffer for some reason (s.a. `errno') */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) __ATTR_IN_T(3) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_SURFACE_CONVERT)(struct video_surface const *__restrict __self,
                                          struct video_domain const *__domain,
                                          struct video_buffer_format const *__format);
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) __ATTR_IN_T(3) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_SURFACE_CONVERT_DISTINCT)(struct video_surface const *__restrict __self,
                                                   struct video_domain const *__domain,
                                                   struct video_buffer_format const *__format);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_NONNULL((2)) __ATTR_IN(3) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_surface_convert(struct video_surface const *__restrict __self,
                      struct video_domain const *__domain,
                      struct video_buffer_format const *__format);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_NONNULL((2)) __ATTR_IN(3) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_surface_convert_distinct(struct video_surface const *__restrict __self,
                               struct video_domain const *__domain,
                               struct video_buffer_format const *__format);
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
 * @param: __self:  The video surface to wrap
 * @return: * :     The video buffer wrapper (having the same codec/dimensions as `__self')
 * @return: __self: The given `__self' is already known to have vi_rlock/vi_wlock operators
 *                  that either never fail, or can only fail with errno=ENOMEM for the same
 *                  reason that the  "lockable" wrapper could  also fail. (generally,  this
 *                  means that this is a no-op when `__self' is a ram-buffer, or is already
 *                  a "lockable" video buffer). */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_SURFACE_LOCKABLE)(struct video_buffer *__restrict __self);
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_SURFACE_LOCKABLE_DISTINCT)(struct video_buffer *__restrict __self);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_surface_lockable(struct video_surface const *__restrict __self);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_surface_lockable_distinct(struct video_surface const *__restrict __self);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */




/* Create a new region-relative-proxy of `__self', that interacts with the same
 * pixel data, both during GFX operations,  as well when creating video  locks.
 *
 * You can also use this function to create regions at negative offsets, or
 * ones that are larger than `__self'.
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
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_IN_T(2) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *PVIDEO_SURFACE_REGION_DISTINCT)(struct video_surface const *__restrict __self,
                                                  struct video_rect const *__restrict __rect);
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_IN_T(2) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *P_VIDEO_SURFACE_REGION)(struct video_surface const *__restrict __self,
                                          struct video_rect const *__restrict __buffer_rect);
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_IN_T(2) __REF struct video_buffer *
(LIBVIDEO_GFX_CC *P_VIDEO_SURFACE_REGION_DISTINCT)(struct video_surface const *__restrict __self,
                                                   struct video_rect const *__restrict __buffer_rect);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_surface_region(struct video_surface const *__restrict __self,
                     struct video_rect const *__restrict __rect);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_surface_region_distinct(struct video_surface const *__restrict __self,
                              struct video_rect const *__restrict __rect);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __REF struct video_buffer *LIBVIDEO_GFX_CC
_video_surface_region(struct video_surface const *__restrict __self,
                      struct video_rect const *__restrict __buffer_rect);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __REF struct video_buffer *LIBVIDEO_GFX_CC
_video_surface_region_distinct(struct video_surface const *__restrict __self,
                               struct video_rect const *__restrict __buffer_rect);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */



/* Same  as  `video_buffer_*save', but  save pixel
 * data using the palette and GFX flags of `self'.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) int
(LIBVIDEO_GFX_CC *PVIDEO_SURFACE_FSAVE)(struct video_surface const *__self, char const *__format,
                                        __FILE *__restrict __fp, char const *__options);
typedef __ATTR_WUNUSED_T __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) int
(LIBVIDEO_GFX_CC *PVIDEO_SURFACE_FDSAVE)(struct video_surface const *__self, char const *__format,
                                         __fd_t __fd, char const *__options);
typedef /*__ATTR_WUNUSED_T*/ __ATTR_IN_T(1) __ATTR_NONNULL_T((2)) int
(LIBVIDEO_GFX_CC *PVIDEO_SURFACE_SAVE)(struct video_surface const *__self, char const *__filename,
                                       char const *__options);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_NONNULL((2)) int LIBVIDEO_GFX_CC
video_surface_fsave(struct video_surface const *__self, char const *__format,
                    __FILE *__restrict __fp, char const *__options);
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_NONNULL((2)) int LIBVIDEO_GFX_CC
video_surface_fdsave(struct video_surface const *__self, char const *__format,
                     __fd_t __fd, char const *__options);
LIBVIDEO_GFX_DECL /*__ATTR_WUNUSED*/ __ATTR_IN(1) __ATTR_NONNULL((2)) int LIBVIDEO_GFX_CC
video_surface_save(struct video_surface const *__self, char const *__filename,
                   char const *__options);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */


/* Convert `__self' into a distinct (non-shared) `video_buffer' using
 * the surface's properties as its defaults. */
__LOCAL __ATTR_WUNUSED __ATTR_IN(1) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_surface_asbuffer_distinct(struct video_surface const *__restrict __self) {
#ifndef __INTELLISENSE__
	struct video_crect __rect;
	__rect.vcr_xmin = 0;
	__rect.vcr_ymin = 0;
	__rect.vcr_xdim = video_surface_getbufferxdim(__self);
	__rect.vcr_ydim = video_surface_getbufferydim(__self);
	return _video_surface_subregion(__self, &__rect);
#endif /* !__INTELLISENSE__ */
}

/* Same as `video_surface_asbuffer_distinct()', but allow the returned buffer to alias another. */
__LOCAL __ATTR_WUNUSED __ATTR_IN(1) __REF struct video_buffer *LIBVIDEO_GFX_CC
video_surface_asbuffer(struct video_surface const *__restrict __self) {
#ifndef __INTELLISENSE__
	if (video_surface_isdefault(__self)) {
		__REF struct video_buffer *__result = video_surface_getbuffer(__self);
		video_buffer_incref(__result);
		return __result;
	}
	return video_surface_asbuffer_distinct(__self);
#endif /* !__INTELLISENSE__ */
}

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_SURFACE_H */
