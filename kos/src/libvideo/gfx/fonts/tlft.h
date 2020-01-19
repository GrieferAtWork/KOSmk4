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
#ifndef GUARD_LIBVIDEO_GFX_FONTS_TLFT_H
#define GUARD_LIBVIDEO_GFX_FONTS_TLFT_H 1

#include "../api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <uchar.h>

#include <libvideo/gfx/font.h>
#include <libvideo/gfx/fonts/tlft.h>

DECL_BEGIN

struct tlft_font: video_font {
	TLFT_Hdr      *tf_hdr;        /* [1..tf_siz][owned][const] mmaped file base */
	size_t         tf_siz;        /* [const] mmap-ed file size */
	TLFT_UniGroup *tf_grps;       /* [0..tf_hdr->h_ngroups][const] Unicode groups. */
	byte_t        *tf_ascii;      /* [1..1][const] Ascii character bitmaps (`h_ascii'). */
	byte_t        *tf_chars;      /* [1..1][const] Unicode character bitmaps (`h_chars'). */
	uintptr_t      tf_bestheight; /* [const] Font height for best results. */
};

/* Return the V-table used by `struct tlft_font' */
INTDEF ATTR_RETNONNULL WUNUSED
struct video_font_ops *CC libvideo_tlft_getops(void);

/* Returns `(__REF struct video_font *)-1' if not a tlft file.
 * Upon success, the mmap-ed region `base...+=size' is inherited. */
INTDEF WUNUSED NONNULL((1)) __REF struct video_font *CC
libvideo_font_tryopen_tlft(void *base, size_t size);


DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_FONTS_TLFT_H */
