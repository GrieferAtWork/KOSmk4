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
#ifndef GUARD_LIBVIDEO_GFX_FONT_H
#define GUARD_LIBVIDEO_GFX_FONT_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <parts/uchar/format-printer.h> /* C32FORMATPRINTER_CC */
#include <sys/types.h>

#include <format-printer.h> /* FORMATPRINTER_CC */
#include <stddef.h>

#include <libvideo/color.h>
#include <libvideo/gfx/font.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

DECL_BEGIN

/* Lookup and return a reference to a video font, given its name.
 * @param: name: The font's name (the name of a file in `/lib/fonts/',
 *               or  an absolute path if it contains a `/'). Else, you
 *               may also pass one of `VIDEO_FONT_*'
 * @return: NULL: [errno=ENOENT] Unknown font `name' */
INTDEF WUNUSED NONNULL((1)) __REF struct video_font *CC
libvideo_font_lookup(struct video_domain const *__restrict domain,
                     char const *name);

/* Print text into a graphics context through use of this pformatprinter-compatible function. */
INTDEF NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libvideo_fontprinter(/*struct video_fontprinter_data **/ void *arg,
                     /*utf-8*/ char const *__restrict data, size_t datalen);

/* Same as `video_fontprinter()', but used to directly print UTF-32 text. */
INTDEF NONNULL((1, 2)) ssize_t C32FORMATPRINTER_CC
libvideo_fontprinter32(/*struct video_fontprinter_data **/ void *arg,
                       char32_t const *__restrict data, size_t datalen);

/* Same as `video_fontprinter()', but only print a single UTF-32 character.
 * @return: * : The  width  of  the  printed  character  (unrecognized characters
 *              are replaced with substitution characters, and control characters
 *              such as '\n' will cause `0' to be returned) */
INTDEF NONNULL((1)) video_dim_t CC
libvideo_fontprintch(struct video_fontprinter_data *__restrict self,
                     char32_t ch);




/* Generic implementation for `vfo_drawglyph' that calls `vfo_drawglyph2' */
INTDEF ATTR_IN(1) ATTR_IN(2) video_dim_t CC
libvideo_font__drawglyph__with__drawglyph2(struct video_font const *__restrict self,
                                           struct video_gfx const *__restrict gfx,
                                           video_offset_t x, video_offset_t y,
                                           video_dim_t height, char32_t ord,
                                           video_color_t color);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_FONT_H */
