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
#ifndef _LIBVIDEO_GFX_FONT_H
#define _LIBVIDEO_GFX_FONT_H 1

#include "api.h"
/**/

#include <hybrid/__atomic.h>
#include <hybrid/typecore.h>

#include <bits/crt/format-printer.h> /* __FORMATPRINTER_CC */
#include <bits/crt/mbstate.h>
#include <bits/crt/uformat-printer.h> /* __C32FORMATPRINTER_CC */
#include <bits/types.h>
#include <kos/anno.h>
#include <kos/refcnt.h>

#include <libvideo/codec/pixel.h> /* video_color_t */
#include <libvideo/codec/types.h>

#ifdef __CC__
__DECL_BEGIN

struct video_gfx;
struct video_font;

struct video_font_ops {
	/* All operators within this structure are [1..1] */

	/* Destroy the given video font object. */
	__ATTR_NONNULL_T((1)) void
	(LIBVIDEO_GFX_CC *vfo_destroy)(struct video_font *__restrict __self);

	/* Draw a single glyph at the given coords and return its width.
	 * If the glyph was not recognized (or when `__height' was `0'), return 0 instead. */
	__ATTR_IN_T(1) __ATTR_IN_T(2) video_dim_t
	(LIBVIDEO_GFX_CC *vfo_drawglyph)(struct video_font const *__restrict __self,
	                                 struct video_gfx const *__restrict __gfx,
	                                 video_offset_t __x, video_offset_t __y,
	                                 video_dim_t __height, __CHAR32_TYPE__ __ord,
	                                 video_color_t __color);

	/* Return the width (in pixels) of a glyph, given its height (in pixels). */
	__ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_IN_T(1) video_dim_t
	(LIBVIDEO_GFX_CC *vfo_glyphsize)(struct video_font const *__restrict __self,
	                                 video_dim_t __height, __CHAR32_TYPE__ __ord);

	/* Same  as  `vfo_drawglyph',  but  uses  a  pair  of  bg/fg colors.
	 * By  default,  `vfo_drawglyph'  simply calls  this  while passing:
	 * >> __bg_fg_colors: { __color & ~VIDEO_COLOR_ALPHA_MASK, __color } */
	__ATTR_IN_T(1) __ATTR_IN_T(2) __ATTR_IN_T(7) video_dim_t
	(LIBVIDEO_GFX_CC *vfo_drawglyph2)(struct video_font const *__restrict __self,
	                                  struct video_gfx const *__restrict __gfx,
	                                  video_offset_t __x, video_offset_t __y,
	                                  video_dim_t __height, __CHAR32_TYPE__ __ord,
	                                  video_color_t const __bg_fg_colors[2]);
};

#define video_font_drawglyph(self, gfx, x, y, height, ord, color) \
	(*(self)->vf_ops->vfo_drawglyph)(self, gfx, x, y, height, ord, color)
#define video_font_drawglyph2(self, gfx, x, y, height, ord, bg_fg_colors) \
	(*(self)->vf_ops->vfo_drawglyph2)(self, gfx, x, y, height, ord, bg_fg_colors)
#define video_font_glyphsize(self, height, ord) \
	(*(self)->vf_ops->vfo_glyphsize)(self, height, ord)


struct video_font {
	__uintptr_t            vf_refcnt; /* Reference counter. */
	struct video_font_ops *vf_ops;    /* [1..1] Operators. */
	/* Remainder of this structure contains type-specific data. */

#ifdef __cplusplus
	/* Draw a single glyph at the given coords and return its width.
	 * If the glyph was not recognized (or when `__height' was `0'), return 0 instead. */
	__CXX_CLASSMEMBER video_dim_t drawglyph(struct video_gfx const *__restrict __gfx,
	                                        video_offset_t __x, video_offset_t __y,
	                                        video_dim_t __height, __CHAR32_TYPE__ __ord,
	                                        video_color_t __color) const {
		return video_font_drawglyph(this, __gfx, __x, __y, __height, __ord, __color);
	}

	__CXX_CLASSMEMBER video_dim_t drawglyph2(struct video_gfx const *__restrict __gfx,
	                                         video_offset_t __x, video_offset_t __y,
	                                         video_dim_t __height, __CHAR32_TYPE__ __ord,
	                                         video_color_t const __bg_fg_colors[2]) const {
		return video_font_drawglyph2(this, __gfx, __x, __y, __height, __ord, __bg_fg_colors);
	}

	/* Return the width (in pixels) of a glyph, given its height (in pixels). */
	__CXX_CLASSMEMBER video_dim_t glyphsize(video_dim_t __height, __CHAR32_TYPE__ __ord) const {
		return video_font_glyphsize(this, __height, __ord);
	}
#endif /* __cplusplus */
};

#define video_font_destroy(self) (*(self)->vf_ops->vfo_destroy)(self)
#define video_font_incref(self) \
	__hybrid_atomic_inc(&(self)->vf_refcnt, __ATOMIC_SEQ_CST)
#define video_font_decref(self)                                              \
	(void)(__hybrid_atomic_decfetch(&(self)->vf_refcnt, __ATOMIC_SEQ_CST) || \
	       (video_font_destroy(self), 0))
__DEFINE_REFCNT_FUNCTIONS(struct video_font, vf_refcnt, video_font_destroy)


/* Lookup and return a reference to a video font, given its name.
 * @param: name: The font's name (the name of a file in `/lib/fonts/')
 *               Else,    you   may   pass   one   of   `VIDEO_FONT_*'
 * @return: NULL:errno=ENOENT: Unknown font `name' */
typedef __ATTR_WUNUSED_T __REF struct video_font *(LIBVIDEO_GFX_CC *PVIDEO_FONT_LOOKUP)(char const *__name);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_WUNUSED __REF struct video_font *LIBVIDEO_GFX_CC video_font_lookup(char const *__name);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

/* Special font names. */
#define VIDEO_FONT_DEFAULT     (__CCAST(char const *)-1) /* Default system font. */
#define VIDEO_FONT_FIXEDWIDTH  (__CCAST(char const *)-2) /* Default fixed-width font. */
/* Check if `x' is a special font name. */
#define VIDEO_FONT_ISPECIAL(x) (__CCAST(__uintptr_t)(x) >= __CCAST(__uintptr_t)-4096)



/* Context descriptor for using the pformatprinter-like `video_fontprinter()'
 * function for rendering text into a graphics context. */
struct video_fontprinter_data {
	struct video_font const *vfp_font;            /* [1..1][const] The font used for printing. */
	struct video_gfx  const *vfp_gfx;             /* [1..1][const] Target graphics context. */
	video_dim_t              vfp_height;          /* Glyph height. */
	video_offset_t           vfp_curx;            /* X coord for the top-left corner of the next glyph */
	video_offset_t           vfp_cury;            /* Y coord for the top-left corner of the next glyph */
	video_offset_t           vfp_lnstart;         /* Starting X coord for additional lines (when >= `vfp_lnend', new lines are disabled) */
	video_offset_t           vfp_lnend;           /* Ending  X coord for additional lines (when `> vfp_lnstart',
	                                               * wrap to a new line when a glyph would exceed this position) */
	video_color_t            vfp_bg_fg_colors[2]; /* Output colors for the next glyph. */
	struct __mbstate         vfp_u8word;          /* Incomplete utf-8 word (used by `format_8to32_data::fd_incomplete') (initialize to 0) */
	/* TODO: Special character attribute flags (underline, cross-out, mirrored?, bold?, cursive?) */
};

/* Print text into a graphics context through use of this pformatprinter-compatible function. */
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t
(__FORMATPRINTER_CC *PVIDEO_FONTPRINTER)(/*struct video_fontprinter_data **/ void *__arg,
                                         /*utf-8*/ char const *__restrict __data,
                                         __size_t __datalen);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_NONNULL((1, 2)) __ssize_t __FORMATPRINTER_CC
video_fontprinter(/*struct video_fontprinter_data **/ void *__arg,
                  /*utf-8*/ char const *__restrict __data, __size_t __datalen);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

/* Same as `video_fontprinter()', but used to directly print UTF-32 text. */
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t
(__C32FORMATPRINTER_CC *PVIDEO_FONTPRINTER32)(/*struct video_fontprinter_data **/ void *__arg,
                                              __CHAR32_TYPE__ const *__restrict __data,
                                              __size_t __datalen);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ssize_t __C32FORMATPRINTER_CC
video_fontprinter32(/*struct video_fontprinter_data **/ void *__arg,
                    __CHAR32_TYPE__ const *__restrict __data, __size_t __datalen);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */

/* Same as `video_fontprinter()', but only print a single UTF-32 character.
 * @return: * : The  width  of  the  printed  character  (unrecognized characters
 *              are replaced with substitution characters, and control characters
 *              such as '\n' will cause `0' to be returned) */
typedef __ATTR_NONNULL_T((1)) video_dim_t
(LIBVIDEO_GFX_CC *PVIDEO_FONTPRINTCH)(struct video_fontprinter_data *__restrict __self,
                                      __CHAR32_TYPE__ __ch);
#ifdef LIBVIDEO_GFX_WANT_PROTOTYPES
LIBVIDEO_GFX_DECL __ATTR_NONNULL((1)) video_dim_t LIBVIDEO_GFX_CC
video_fontprintch(struct video_fontprinter_data *__restrict __self,
                  __CHAR32_TYPE__ __ch);
#endif /* LIBVIDEO_GFX_WANT_PROTOTYPES */




__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIDEO_GFX_FONT_H */
