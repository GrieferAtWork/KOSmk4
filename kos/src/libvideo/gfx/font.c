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
#ifndef GUARD_LIBVIDEO_GFX_FONT_C
#define GUARD_LIBVIDEO_GFX_FONT_C 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <stddef.h>
#include <unicode.h>

#include <libvideo/gfx/font.h>

#include "font.h"

DECL_BEGIN

/* Lookup and return a reference to a video font, given its name.
 * NOTE: This function maintains an internal cache of loaded fonts,
 *       such that consecutive calls are quite acceptable.
 * @param: NAME: The font's name (the name of a file in `/lib/fonts/')
 *               When `NULL', (try to) return the default system font.
 * @return: NULL:errno=ENOENT: Unknown font `NAME' */
INTERN WUNUSED __REF struct video_font *CC
libvideo_font_lookup(char const *name) {
	COMPILER_IMPURE();
	(void)name;
	/* TODO */
	return NULL;
}

/* Print text into a graphics context through use of this pformatprinter-compatible function. */
INTERN ssize_t __LIBCCALL
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
INTERN ssize_t __LIBCCALL
libvideo_fontprinter32(/*struct video_fontprinter_data **/ void *arg,
                       char32_t const *__restrict data, size_t datalen) {
	size_t i;
	struct video_fontprinter_data *context;
	context = (struct video_fontprinter_data *)arg;
	/* Print the string one character at a time. */
	for (i = 0; i < datalen; ++i) {
		libvideo_fontprinterch(context, data[i]);
	}
	return (ssize_t)datalen;
}


/* Same as `video_fontprinter()', but only print a single UTF-32 character.
 * @return: * : The width of the printed character (unrecognized characters
 *              are replaced with substitution characters, and control characters
 *              such as '\n' will cause `0' to be returned) */
INTERN NONNULL((1)) uintptr_t CC
libvideo_fontprinterch(struct video_fontprinter_data *__restrict self,
                       char32_t ch) {
	switch (ch) {

	case '\r':
		/* TODO */
		break;

	case '\n':
		/* TODO */
		break;

	default: {
		if (self->vfp_lnstart < self->vfp_lnend) {
			/* Must force wrap-around when a line grows too long. */
			COMPILER_IMPURE();
			/* TODO */
		} else {
			/* Can just render text without worrying about anything! */
			/* TODO */
		}
	}	break;
	}
	return 0;
}


DEFINE_PUBLIC_ALIAS(video_font_lookup, libvideo_font_lookup);
DEFINE_PUBLIC_ALIAS(video_fontprinter, libvideo_fontprinter);
DEFINE_PUBLIC_ALIAS(video_fontprinter32, libvideo_fontprinter32);
DEFINE_PUBLIC_ALIAS(video_fontprinterch, libvideo_fontprinterch);


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_FONT_C */
