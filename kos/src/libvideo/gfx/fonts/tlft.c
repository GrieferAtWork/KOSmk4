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
#ifndef GUARD_LIBVIDEO_GFX_FONTS_TLFT_C
#define GUARD_LIBVIDEO_GFX_FONTS_TLFT_C 1
#define TLFT_NO_LOOKUP 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/bsearch.h>

#include <kos/anno.h>
#include <sys/mman.h>

#include <assert.h>
#include <atomic.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>

#include <libvideo/color.h>
#include <libvideo/gfx/buffer.h>
#include <libvideo/gfx/font.h>
#include <libvideo/gfx/fonts/tlft.h>
#include <libvideo/gfx/gfx.h>
#include <libvideo/types.h>

#include "../codec/codec.h"
#include "../codec/palette.h"
#include "../font.h"
#include "tlft.h"

DECL_BEGIN

/* Destroy the given video font object. */

PRIVATE void CC
libvideo_tlft_weakdecref(void *cookie, void *UNUSED(mem)) {
	struct tlft_font *me = (struct tlft_font *)cookie;
	if (atomic_decfetch(&me->tf_weakrefcnt) == 0) {
		(void)unmapfile(&me->tf_map);
		(void)free(me);
	}
}

PRIVATE NONNULL((1)) void CC
libvideo_tlft_destroy(struct video_font *__restrict self) {
	struct tlft_font *me = (struct tlft_font *)self;
	video_buffer_decref(me->tf_chars);
	libvideo_tlft_weakdecref(me, NULL);
}


/* Lookup the bitmap associated with a given character. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_coord_t CC
tlft_locate_glyph_ycoord(struct tlft_font const *__restrict self,
                         char16_t ord) {
	uint8_t i;
	if (ord >= 0x0020 && ord <= 0x007e)
		return (ord - 0x0020) * self->tf_bestheight;
	BSEARCH_RANGE (i, self->tf_grps, tlft_font_gethdr(self)->h_ngroups,
	               /*item*/ .ug_minuni,
	               /*item*/ .ug_maxuni,
	               (uint16_t)ord) {
		/* Found it! */
		return (self->tf_grps[i].ug_offset + 95 +
		        ((uint16_t)ord - self->tf_grps[i].ug_minuni)) *
		       self->tf_bestheight;
	}
	return (video_coord_t)-1;
}

/* Return the width (in pixels) of a glyph, given its height (in pixels). */
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_dim_t CC
libvideo_tlft_glyphsize(struct video_font const *__restrict self,
                        video_dim_t height, char32_t UNUSED(ord)) {
	struct tlft_font *me;
	video_dim_t result;
	me = (struct tlft_font *)self;
	if (height == me->tf_bestheight) {
		result = tlft_font_gethdr(me)->h_chwidth;
	} else {
		result = ((height * tlft_font_gethdr(me)->h_chwidth) +
		          (me->tf_bestheight / 2)) /
		         me->tf_bestheight;
	}
	if unlikely(!result)
		result = 1;
	return result;
}

/* Draw a single glyph at the given coords and return its width.
 * If the glyph was not recognized (or when `HEIGHT' was `0'), return 0 instead. */
PRIVATE ATTR_IN(1) ATTR_IN(2) ATTR_IN(7) video_dim_t CC
libvideo_tlft_drawglyph2(struct video_font const *__restrict self,
                         struct video_gfx const *__restrict gfx,
                         video_offset_t x, video_offset_t y,
                         video_dim_t height, char32_t ord,
                         video_color_t const bg_fg_colors[2]) {
	/* TODO: Re-work the video_font glyph rendering API such that the font itself is
	 *       able to define & mandate the size of a `struct video_font_gfx' context,
	 *       which then replaces what is currently `struct video_fontprinter_data'. */

	video_coord_t glyph_y;
	video_dim_t result;
	struct tlft_font *me = (struct tlft_font *)self;
	struct video_gfx font_gfx;
	if unlikely(ord > 0xffff)
		goto unknown;
	glyph_y = tlft_locate_glyph_ycoord(me, (char16_t)ord);
	if unlikely(glyph_y == (video_coord_t)-1)
		goto unknown;
	video_buffer_getgfx_ex(me->tf_chars, &font_gfx, GFX_BLENDMODE_OVERRIDE,
	                       video_palette_fromcolors(bg_fg_colors),
	                       VIDEO_GFX_F_NORMAL, 0);
	if (height == me->tf_bestheight) {
		/* Can just directly blit the glyph */
		result = tlft_font_gethdr(me)->h_chwidth;
		video_gfx_bitblit(gfx, x, y, &font_gfx,
		                  0, glyph_y, result, height);
	} else {
		/* Must stretch the glyph somehow... */
		result = ((height * tlft_font_gethdr(me)->h_chwidth) +
		          (me->tf_bestheight / 2)) /
		         me->tf_bestheight;
		if unlikely(!result)
			result = 1;
		video_gfx_stretch(gfx, x, y, result, height,
		                  &font_gfx, 0, glyph_y,
		                  tlft_font_gethdr(me)->h_chwidth,
		                  me->tf_bestheight);
	}
	return result;
unknown:
	return 0;
}




/* Return the V-table used by `struct tlft_font' */
#undef libvideo_tlft_ops
PRIVATE struct video_font_ops libvideo_tlft_ops = { NULL, NULL, NULL };
INTERN ATTR_RETNONNULL WUNUSED struct video_font_ops *CC _libvideo_tlft_ops(void) {
	if unlikely(!libvideo_tlft_ops.vfo_destroy) {
		libvideo_tlft_ops.vfo_drawglyph  = &libvideo_font__drawglyph__with__drawglyph2;
		libvideo_tlft_ops.vfo_drawglyph2 = &libvideo_tlft_drawglyph2;
		libvideo_tlft_ops.vfo_glyphsize  = &libvideo_tlft_glyphsize;
		COMPILER_WRITE_BARRIER();
		libvideo_tlft_ops.vfo_destroy = &libvideo_tlft_destroy;
		COMPILER_WRITE_BARRIER();
	}
	return &libvideo_tlft_ops;
}
#define libvideo_tlft_ops (*_libvideo_tlft_ops())


PRIVATE video_color_t const tlft_default_palette[2] = {
	VIDEO_COLOR_BLACK,
	VIDEO_COLOR_WHITE
};


/* Returns `(REF struct video_font *)-1'  if  not  a  tlft  file.
 * Upon success, the mmap-ed region `base...+=size' is inherited. */
INTERN WUNUSED NONNULL((1, 2)) REF struct video_font *CC
libvideo_font_tryopen_tlft(struct video_domain const *__restrict domain,
                           struct mapfile const *__restrict mf) {
	TLFT_Hdr const *hdr;
	REF struct tlft_font *result;
	byte_t const *chrtab, *chrend;
	struct video_buffer_format chr_format;
	hdr = (TLFT_Hdr const *)mf->mf_addr;
	if unlikely(mf->mf_size < sizeof(TLFT_Hdr))
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
	result = (REF struct tlft_font *)malloc(sizeof(struct tlft_font));
	if unlikely(!result)
		goto err;
	result->tf_map = *mf; /* Inherited (on success) */
	if unlikely(!hdr->h_chwidth)
		goto err_inval_r;
	if (OVERFLOW_UADD((uintptr_t)hdr, hdr->h_hdrsize,
	                  (uintptr_t *)&result->tf_grps))
		goto err_inval_r;
	if (OVERFLOW_UADD((uintptr_t)result->tf_grps,
	                  (uintptr_t)hdr->h_ngroups * 8,
	                  (uintptr_t *)&chrtab))
		goto err_inval_r;
	if (OVERFLOW_UADD((uintptr_t)chrtab,
	                  (uintptr_t)95 << hdr->h_log2chsize,
	                  (uintptr_t *)&chrend))
		goto err_inval_r;
	if (OVERFLOW_UADD((uintptr_t)chrtab,
	                  (uintptr_t)hdr->h_nchars << hdr->h_log2chsize,
	                  (uintptr_t *)&chrend))
		goto err_inval_r;
	if unlikely(chrend > ((byte_t const *)hdr + mf->mf_size))
		goto err_inval_r;

	/* Pre-calculate some values. */
	result->tf_bestheight = (((uintptr_t)1 << hdr->h_log2chsize) * 8) / hdr->h_chwidth;

	/* Fill in misc. fields */
	result->vf_ops        = &libvideo_tlft_ops;
	result->vf_refcnt     = 1;
	result->tf_weakrefcnt = 2; /* +1: result, +1: result->tf_chars */
	result->vf_domain     = domain;

	/* Allocate video buffer to interface with character bitmaps */
	chr_format.vbf_codec = libvideo_codec_lookup(VIDEO_CODEC_P1_MSB);
	assertf(chr_format.vbf_codec, "Built-in codec should have been recognized");
	chr_format.vbf_pal   = video_palette_fromcolors(tlft_default_palette);
	chr_format.vbf_flags = VIDEO_GFX_F_NORMAL;
	result->tf_chars = video_domain_formem(domain, &chr_format, hdr->h_chwidth,
	                                       result->tf_bestheight * (95 + hdr->h_nchars),
	                                       (void *)chrtab, CEILDIV(hdr->h_chwidth, 8),
	                                       &libvideo_tlft_weakdecref, result,
	                                       VIDEO_DOMAIN_FORMEM_F_NORMAL);
	if unlikely(!result->tf_chars)
		goto err_r;
	return result;
err_r:
	free(result);
err:
	return NULL;
err_inval_r:
	free(result);
err_inval:
	return (REF struct video_font *)-1;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_FONTS_TLFT_C */
