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
#ifndef GUARD_LIBVIDEO_GFX_FONTS_TLFT_C
#define GUARD_LIBVIDEO_GFX_FONTS_TLFT_C 1

#include "tlft.h"

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>

#include <kos/types.h>
#include <sys/mman.h>

#include <assert.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <uchar.h>
#include <unicode.h>

#include <libvideo/gfx/font.h>
#include <libvideo/gfx/gfx.h>

#include "../api.h"

DECL_BEGIN

/* Destroy the given video font object. */
PRIVATE void CC
libvideo_tlft_destroy(struct video_font *__restrict self) {
	struct tlft_font *me;
	me = (struct tlft_font *)self;
	munmap(me->tf_hdr, me->tf_siz);
	free(me);
}

/* Lookup the bitmap associated with a given character. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) void *CC
libvideo_tlft_lookup(struct tlft_font const *__restrict self,
                     char16_t ord) {
	uint8_t i, step;
	if (ord >= 0x0020 && ord <= 0x007e)
		return self->tf_ascii + ((ord - 0x0020) << self->tf_hdr->h_log2chsize);
	/* bsearch-style lookup */
	for (i = self->tf_hdr->h_ngroups / 2, step = i / 2;; step = (step + 1) / 2) {
		if (ord < self->tf_grps[i].ug_minuni) {
			if (OVERFLOW_USUB(i, step, &i))
				break;
			continue;
		}
		if (ord > self->tf_grps[i].ug_minuni) {
			if (OVERFLOW_UADD(i, step, &i) || i >= self->tf_hdr->h_ngroups)
				break;
			continue;
		}
		return self->tf_chars + (self->tf_grps[i].ug_offset << self->tf_hdr->h_log2chsize);
	}
	return NULL;
}

/* Draw a single glyph at the given coords and return its width.
 * If the glyph was not recognized (or when `HEIGHT' was `0'), return 0 instead. */
PRIVATE uintptr_t CC
libvideo_tlft_drawglyph(struct video_font *__restrict self,
                        struct video_gfx *__restrict gfx,
                        intptr_t x, intptr_t y,
                        uintptr_t height, char32_t ord,
                        video_color_t color) {
	void *bm;
	uintptr_t result;
	struct tlft_font *me;
	if unlikely(ord > 0xffff)
		goto unknown;
	me = (struct tlft_font *)self;
	bm = libvideo_tlft_lookup(me, (char16_t)ord);
	if unlikely(!bm)
		goto unknown;
	if (height == me->tf_bestheight) {
		/* Can just directly blit the glyph */
		result = me->tf_hdr->h_chwidth;
		gfx->bitfill(x, y, result, height, color, bm);
	} else {
		/* Must stretch the glyph somehow... */
		result = (height * me->tf_hdr->h_chwidth) / me->tf_bestheight;
		gfx->bitstretchfill(x, y, result, height, color,
		                    me->tf_hdr->h_chwidth,
		                    me->tf_bestheight, bm);
	}
	return result;
unknown:
	return 0;
}

/* Return the width (in pixels) of a glyph, given its height (in pixels). */
PRIVATE ATTR_PURE uintptr_t CC
libvideo_tlft_glyphsize(struct video_font *__restrict self,
                        uintptr_t height, char32_t UNUSED(ord)) {
	struct tlft_font *me;
	me = (struct tlft_font *)self;
	return (height * me->tf_hdr->h_chwidth) / me->tf_bestheight;
}


PRIVATE struct video_font_ops libvideo_tlft_ops = { NULL, NULL, NULL };

/* Return the V-table used by `struct tlft_font' */
INTERN ATTR_RETNONNULL WUNUSED
struct video_font_ops *CC libvideo_tlft_getops(void) {
	if unlikely(!libvideo_tlft_ops.vfo_destroy) {
		libvideo_tlft_ops.vfo_drawglyph = &libvideo_tlft_drawglyph;
		libvideo_tlft_ops.vfo_glyphsize = &libvideo_tlft_glyphsize;
		COMPILER_WRITE_BARRIER();
		libvideo_tlft_ops.vfo_destroy = &libvideo_tlft_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_tlft_ops;
}



/* Returns `(__REF struct video_font *)-1' if not a tlft file.
 * Upon success, the mmap-ed region `base...+=size' is inherited. */
INTERN WUNUSED __REF struct video_font *CC
libvideo_font_tryopen_tlft(void *base, size_t size) {
	TLFT_Hdr *hdr;
	__REF struct tlft_font *result;
	uintptr_t chend;
	hdr = (TLFT_Hdr *)base;
	if unlikely(size < sizeof(TLFT_Hdr))
		goto err_inval;
	/* Verify the magic header. */
	if (hdr->h_ident[TI_MAG0] != TLFTMAG0)
		goto err_inval;
	if (hdr->h_ident[TI_MAG1] != TLFTMAG1)
		goto err_inval;
	if (hdr->h_ident[TI_MAG2] != TLFTMAG2)
		goto err_inval;
	if (hdr->h_ident[TI_MAG3] != TLFTMAG3)
		goto err_inval;
	if (hdr->h_ident[TI_MAG4] != TLFTMAG4)
		goto err_inval;
	/* Verify the version number. */
	if (hdr->h_ident[TI_VERS] != TLFTVERSION)
		goto err_inval;
	if (hdr->h_hdrsize & 1) /* Must be aligned by 2 */
		goto err_inval;
	if (hdr->h_nchars > 0xffa1) /* Too many characters */
		goto err_inval;
	/* Allocate the font descriptor. */
	result = (__REF struct tlft_font *)malloc(sizeof(struct tlft_font));
	if unlikely(!result)
		goto done;
	result->tf_hdr = hdr; /* Inherited (on success) */
	result->tf_siz = size;
	if unlikely(!hdr->h_chwidth)
		goto err_inval_r;
	if (OVERFLOW_UADD((uintptr_t)hdr, hdr->h_hdrsize,
	                  (uintptr_t *)&result->tf_grps))
		goto err_inval_r;
	if (OVERFLOW_UADD((uintptr_t)result->tf_grps,
	                  (uintptr_t)hdr->h_ngroups * 8,
	                  (uintptr_t *)&result->tf_ascii))
		goto err_inval_r;
	if (OVERFLOW_UADD((uintptr_t)result->tf_ascii,
	                  (uintptr_t)95 << hdr->h_log2chsize,
	                  (uintptr_t *)&result->tf_chars))
		goto err_inval_r;
	/* Make sure that unicode character bitmaps don't overflow the actual file size. */
	if (OVERFLOW_UADD((uintptr_t)result->tf_chars,
	                  (uintptr_t)hdr->h_nchars << hdr->h_log2chsize,
	                  &chend))
		goto err_inval_r;
	if unlikely(chend > ((uintptr_t)base + size))
		goto err_inval_r;
	/* Pre-calculate some values. */
	result->tf_bestheight = (((uintptr_t)1 << hdr->h_log2chsize) * 8) / hdr->h_chwidth;
	/* All right! everything seems to be ok. -> Fill in V-table and refcnt. */
	result->vf_refcnt = 1;
	result->vf_ops    = libvideo_tlft_getops();
done:
	return result;
err_inval_r:
	free(result);
err_inval:
	return (__REF struct video_font *)-1;
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_FONTS_TLFT_C */
