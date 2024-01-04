/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVIDEO_GFX_FONT_C
#define GUARD_LIBVIDEO_GFX_FONT_C 1
#define _GNU_SOURCE 1
#define _FILE_OFFSET_BITS 64

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <parts/uchar/format-printer.h> /* C32FORMATPRINTER_CC */
#include <sys/mman.h>
#include <sys/stat.h>

#include <alloca.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <format-printer.h> /* FORMATPRINTER_CC */
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <unicode.h>
#include <unistd.h>

#include <libvideo/gfx/font.h>

#include "font.h"
#include "fonts/tlft.h"

DECL_BEGIN


PRIVATE WUNUSED __REF struct video_font *CC
libvideo_font_openfd(fd_t fd) {
	void *base;
	struct stat st;
	__REF struct video_font *result;
	if unlikely(fstat(fd, &st))
		goto err;
#if __SIZEOF_OFF64_T__ > __SIZEOF_SIZE_T__
	if unlikely(st.st_size > SIZE_MAX) {
		errno = EINVAL;
		goto err;
	}
#endif /* __SIZEOF_OFF64_T__ > __SIZEOF_SIZE_T__ */
	/* Map the font file into memory. */
	base = mmap(NULL, (size_t)st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if unlikely(base == MAP_FAILED)
		goto err;
	result = libvideo_font_tryopen_tlft(base, (size_t)st.st_size);
	if (!result)
		goto err_unmap;
	if (result != (__REF struct video_font *)-1)
		return result; /* Success */
	/* Add other file formats here! */
	/* ... */
	errno = EINVAL; /* Bad file format. */
err_unmap:
	munmap(base, (size_t)st.st_size);
err:
	return NULL;
}


PRIVATE WUNUSED __REF struct video_font *CC
libvideo_font_create(char const *__restrict name) {
	__REF struct video_font *result;
	fd_t fd;
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
	fd = open(full_name, O_RDONLY | O_CLOEXEC);
	if unlikely(fd < 0)
		goto err;
	result = libvideo_font_openfd(fd);
	close(fd);
	return result;
err:
	return NULL;
}



/* Lookup and return a reference to a video font, given its name.
 * @param: name: The font's name (the name of a file in `/lib/fonts/')
 *               When `NULL', (try to) return the default system font.
 * @return: NULL:errno=ENOENT: Unknown font `name' */
INTERN WUNUSED __REF struct video_font *CC
libvideo_font_lookup(char const *name) {
	__REF struct video_font *result;
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
INTERN NONNULL((1)) size_t CC
libvideo_fontprintch(struct video_fontprinter_data *__restrict self,
                     char32_t ch) {
	size_t result;
	switch (ch) {

	case '\r':
		self->vfp_curx = self->vfp_lnstart;
		result = 0;
		break;

	case '\n':
		self->vfp_curx = self->vfp_lnstart;
		self->vfp_cury += self->vfp_height;
		result = 0;
		break;

	default: {
again_do_render:
		if (self->vfp_lnstart < self->vfp_lnend) {
			/* Must force wrap-around when a line grows too long. */
			result = self->vfp_font->glyphsize(self->vfp_height, ch);
			if (self->vfp_curx + (intptr_t)result > self->vfp_lnend) {
				self->vfp_curx  = self->vfp_lnstart;
				self->vfp_cury += self->vfp_height;
			}
		}
		/* Can just render text without worrying about anything! */
		result = self->vfp_font->drawglyph(self->vfp_gfx,
		                                   self->vfp_curx,
		                                   self->vfp_cury,
		                                   self->vfp_height,
		                                   ch,
		                                   self->vfp_color);
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


DEFINE_PUBLIC_ALIAS(video_font_lookup, libvideo_font_lookup);
DEFINE_PUBLIC_ALIAS(video_fontprinter, libvideo_fontprinter);
DEFINE_PUBLIC_ALIAS(video_fontprinter32, libvideo_fontprinter32);
DEFINE_PUBLIC_ALIAS(video_fontprintch, libvideo_fontprintch);


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_FONT_C */
