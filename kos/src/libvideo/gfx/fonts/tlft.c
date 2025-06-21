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
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define TLFT_NO_LOOKUP 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>
#include <hybrid/sequence/bsearch.h>

#include <kos/anno.h>
#include <sys/mman.h>

#include <malloc.h>
#include <stddef.h>
#include <stdint.h>

#include <libvideo/codec/pixel.h>
#include <libvideo/codec/types.h>
#include <libvideo/gfx/font.h>
#include <libvideo/gfx/fonts/tlft.h>
#include <libvideo/gfx/gfx.h>

/**/
#include "../font.h"
#include "tlft.h"

DECL_BEGIN

/* Destroy the given video font object. */
PRIVATE NONNULL((1)) void CC
libvideo_tlft_destroy(struct video_font *__restrict self) {
	struct tlft_font *me;
	me = (struct tlft_font *)self;
	(void)munmap(me->tf_hdr, me->tf_siz);
	(void)free(me);
}


/* Lookup the bitmap associated with a given character. */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) void *CC
libvideo_tlft_lookup(struct tlft_font const *__restrict self,
                     char16_t ord) {
	uint8_t i;
	if (ord >= 0x0020 && ord <= 0x007e)
		return self->tf_ascii + ((ord - 0x0020) << self->tf_hdr->h_log2chsize);
	BSEARCH_RANGE (i, self->tf_grps, self->tf_hdr->h_ngroups,
	               /*item*/ .ug_minuni,
	               /*item*/ .ug_maxuni,
	               (uint16_t)ord) {
		/* Found it! */
		return self->tf_chars + ((self->tf_grps[i].ug_offset +
		                          ((uint16_t)ord - self->tf_grps[i].ug_minuni))
		                         << self->tf_hdr->h_log2chsize);
	}
	return NULL;
}

/* Return the width (in pixels) of a glyph, given its height (in pixels). */
PRIVATE ATTR_PURE WUNUSED ATTR_IN(1) video_dim_t CC
libvideo_tlft_glyphsize(struct video_font const *__restrict self,
                        video_dim_t height, char32_t UNUSED(ord)) {
	struct tlft_font *me;
	video_dim_t result;
	me = (struct tlft_font *)self;
	if (height == me->tf_bestheight) {
		result = me->tf_hdr->h_chwidth;
	} else {
		result = ((height * me->tf_hdr->h_chwidth) +
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
	void *bm;
	struct video_bitmask bitmask;
	video_dim_t result;
	struct tlft_font *me;
	if unlikely(ord > 0xffff)
		goto unknown;
	me = (struct tlft_font *)self;
	bm = libvideo_tlft_lookup(me, (char16_t)ord);
	if unlikely(!bm)
		goto unknown;
	bitmask.vbm_mask = bm;
	bitmask.vbm_skip = 0;
	if (height == me->tf_bestheight) {
		/* Can just directly blit the glyph */
		result = me->tf_hdr->h_chwidth;
		bitmask.vbm_scan = result;
		video_gfx_absfillmask(/* self:         */ gfx,
		                      /* x:            */ x,
		                      /* y:            */ y,
		                      /* size_x:       */ result,
		                      /* size_y:       */ height,
		                      /* bg_fg_colors: */ bg_fg_colors,
		                      /* bitmask:      */ &bitmask);
	} else {
		/* Must stretch the glyph somehow... */
		result = ((height * me->tf_hdr->h_chwidth) +
		          (me->tf_bestheight / 2)) /
		         me->tf_bestheight;
		if unlikely(!result)
			result = 1;
		bitmask.vbm_scan = me->tf_hdr->h_chwidth;
		video_gfx_absfillstretchmask(/* self:         */ gfx,
		                             /* dst_x:        */ x,
		                             /* dst_y:        */ y,
		                             /* dst_size_x:   */ result,
		                             /* dst_size_y:   */ height,
		                             /* bg_fg_colors: */ bg_fg_colors,
		                             /* src_size_x:   */ me->tf_hdr->h_chwidth,
		                             /* src_size_y:   */ me->tf_bestheight,
		                             /* bitmask:      */ &bitmask);
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



/* Returns `(REF struct video_font *)-1'  if  not  a  tlft  file.
 * Upon success, the mmap-ed region `base...+=size' is inherited. */
INTERN WUNUSED NONNULL((1)) REF struct video_font *CC
libvideo_font_tryopen_tlft(void *base, size_t size) {
	TLFT_Hdr *hdr;
	REF struct tlft_font *result;
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
	result = (REF struct tlft_font *)malloc(sizeof(struct tlft_font));
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
	result->vf_ops    = &libvideo_tlft_ops;
done:
	return result;
err_inval_r:
	free(result);
err_inval:
	return (REF struct video_font *)-1;
}


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_FONTS_TLFT_C */
