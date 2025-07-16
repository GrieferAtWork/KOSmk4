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
#ifndef GUARD_LIBVIDEO_GFX_FONT_C
#define GUARD_LIBVIDEO_GFX_FONT_C 1
#define _FILE_OFFSET_BITS 64
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <parts/uchar/format-printer.h> /* C32FORMATPRINTER_CC */
#include <sys/mman.h>
#include <sys/types.h>

#include <alloca.h>
#include <assert.h>
#include <errno.h>
#include <format-printer.h> /* FORMATPRINTER_CC */
#include <stddef.h>
#include <string.h>
#include <unicode.h>

#include <libvideo/color.h>
#include <libvideo/gfx/font.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "font.h"
#include "fonts/tlft.h"

DECL_BEGIN

PRIVATE WUNUSED REF struct video_font *CC
libvideo_font_openfile(char const *filename) {
	struct mapfile mf;
	REF struct video_font *result;
	/* Map the font file into memory. */
	if unlikely(mapfile(&mf, filename, 0, 0, (size_t)-1, 0, 0))
		goto err;
	result = libvideo_font_tryopen_tlft(&mf);
	if (!result)
		goto err_unmap;
	if (result != (REF struct video_font *)-1)
		return result; /* Success */

	/* Add other file formats here! */
	/* ... */
	errno = EINVAL; /* Bad file format. */
err_unmap:
	(void)unmapfile(&mf);
err:
	return NULL;
}


PRIVATE WUNUSED REF struct video_font *CC
libvideo_font_create(char const *__restrict name) {
	char *full_name;
	if (strchr(name, '/')) {
		full_name = (char *)name;
	} else {
		size_t namelen;
		PRIVATE char const prefix[] = "/lib/fonts/";
		char *p;
		namelen = strlen(name);
		full_name = (char *)alloca((COMPILER_STRLEN(prefix) + namelen + 1) *
		                           sizeof(char));
		p = (char *)mempcpy(full_name, prefix, COMPILER_STRLEN(prefix) * sizeof(char));
		p = (char *)mempcpy(p, name, namelen * sizeof(char));
		*p = 0;
	}
	return libvideo_font_openfile(full_name);
}



/* Lookup and return a reference to a video font, given its name.
 * @param: name: The font's name (the name of a file in `/lib/fonts/',
 *               or  an absolute path if it contains a `/'). Else, you
 *               may also pass one of `VIDEO_FONT_*'
 * @return: NULL: [errno=ENOENT] Unknown font `name' */
INTERN WUNUSED REF struct video_font *CC
libvideo_font_lookup(char const *name) {
	REF struct video_font *result;
	if (VIDEO_FONT_ISPECIAL(name)) {
		if (name == VIDEO_FONT_DEFAULT ||
		    name == VIDEO_FONT_FIXEDWIDTH) {
			name = "u_vga16";
		} else {
			errno = ENOENT;
			return NULL;
		}
	} else {
		if unlikely(!name) {
			errno = EINVAL;
			return NULL;
		}
	}
	result = libvideo_font_create(name);
	assert(!result || result->vf_ops);
	assert(!result || result->vf_ops->vfo_destroy);
	assert(!result || result->vf_ops->vfo_drawglyph);
	assert(!result || result->vf_ops->vfo_glyphsize);
	return result;
}

/* Print text into a graphics context through use of this pformatprinter-compatible function. */
INTERN NONNULL((1, 2)) ssize_t FORMATPRINTER_CC
libvideo_fontprinter(/*struct video_fontprinter_data **/ void *arg,
                     /*utf-8*/ char const *__restrict data, size_t datalen) {
	struct video_fontprinter_data *context;
	struct format_8to32_data udat;
	context = (struct video_fontprinter_data *)arg;
	udat.fd_arg        = arg;
	udat.fd_incomplete = context->vfp_u8word;
	udat.fd_printer    = &libvideo_fontprinter32;
	format_8to32(&udat, data, datalen);
	context->vfp_u8word = udat.fd_incomplete;
	return (ssize_t)datalen;
}

/* Same as `video_fontprinter()', but used to directly print UTF-32 text. */
INTERN NONNULL((1, 2)) ssize_t C32FORMATPRINTER_CC
libvideo_fontprinter32(/*struct video_fontprinter_data **/ void *arg,
                       char32_t const *__restrict data, size_t datalen) {
	size_t i;
	struct video_fontprinter_data *context;
	context = (struct video_fontprinter_data *)arg;

	/* Print the string one character at a time. */
	for (i = 0; i < datalen; ++i) {
		libvideo_fontprintch(context, data[i]);
	}
	return (ssize_t)datalen;
}


/* Same as `video_fontprinter()', but only print a single UTF-32 character.
 * @return: * : The  width  of  the  printed  character  (unrecognized characters
 *              are replaced with substitution characters, and control characters
 *              such as '\n' will cause `0' to be returned) */
INTERN NONNULL((1)) video_dim_t CC
libvideo_fontprintch(struct video_fontprinter_data *__restrict self,
                     char32_t ch) {
	video_dim_t result;
	switch (ch) {

	case '\r':
		self->vfp_curx = self->vfp_lnstart;
		result = 0;
		break;

	case '\n':
		/* Fill remainder of line with the current background color. */
		if (self->vfp_curx < self->vfp_lnend) {
			video_gfx_fill(self->vfp_gfx, self->vfp_curx, self->vfp_cury,
			               self->vfp_lnend - self->vfp_curx, self->vfp_height,
			               self->vfp_bg_fg_colors[0]);
		}
		self->vfp_curx = self->vfp_lnstart;
		self->vfp_cury += self->vfp_height;
		result = 0;
		break;

	default: {
again_do_render:
		if (self->vfp_lnstart < self->vfp_lnend) {
			/* Must force wrap-around when a line grows too long. */
			result = self->vfp_font->glyphsize(self->vfp_height, ch);
			if (self->vfp_curx + (video_offset_t)result > self->vfp_lnend) {
				self->vfp_curx  = self->vfp_lnstart;
				self->vfp_cury += self->vfp_height;
			}
		}

		/* Can just render text without worrying about anything! */
		result = self->vfp_font->drawglyph2(self->vfp_gfx,
		                                    self->vfp_curx,
		                                    self->vfp_cury,
		                                    self->vfp_height, ch,
		                                    self->vfp_bg_fg_colors);
		if (!result && self->vfp_height != 0) {
			/* Try a bunch of substitution characters */
			switch (ch) {
			default: ch = 0xfffd; goto again_do_render;
			case 0xfffd: ch = 0x1a; goto again_do_render;
			case 0x1a: ch = '?'; goto again_do_render;
			case '?': break;
			}
		}
		self->vfp_curx += result;
	}	break;
	}
	return result;
}




/* Generic implementation for `vfo_drawglyph' that calls `vfo_drawglyph2' */
INTERN ATTR_IN(1) ATTR_IN(2) video_dim_t CC
libvideo_font__drawglyph__with__drawglyph2(struct video_font const *__restrict self,
                                           struct video_gfx const *__restrict gfx,
                                           video_offset_t x, video_offset_t y,
                                           video_dim_t height, char32_t ord,
                                           video_color_t color) {
	video_color_t bg_fg_colors[2];
	bg_fg_colors[0] = color & ~VIDEO_COLOR_ALPHA_MASK;
	bg_fg_colors[1] = color;
	return (*self->vf_ops->vfo_drawglyph2)(self, gfx, x, y, height, ord, bg_fg_colors);
}




DEFINE_PUBLIC_ALIAS(video_font_lookup, libvideo_font_lookup);
DEFINE_PUBLIC_ALIAS(video_fontprinter, libvideo_fontprinter);
DEFINE_PUBLIC_ALIAS(video_fontprinter32, libvideo_fontprinter32);
DEFINE_PUBLIC_ALIAS(video_fontprintch, libvideo_fontprintch);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_FONT_C */
