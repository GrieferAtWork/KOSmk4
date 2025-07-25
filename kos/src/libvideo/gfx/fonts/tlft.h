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
#ifndef GUARD_LIBVIDEO_GFX_FONTS_TLFT_H
#define GUARD_LIBVIDEO_GFX_FONTS_TLFT_H 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <bits/crt/mapfile.h>
#include <kos/anno.h>
#include <kos/types.h>

#include <stdint.h>

#include <libvideo/gfx/font.h>
#include <libvideo/gfx/fonts/tlft.h>

DECL_BEGIN

struct video_buffer;
struct tlft_font: video_font {
#define tlft_font_gethdr(self) ((TLFT_Hdr *)(self)->tf_map.mf_addr)
	uintptr_t                tf_weakrefcnt; /* Weak reference counter */
	struct mapfile           tf_map;        /* [const] Memory mapping of tlft file */
	TLFT_UniGroup           *tf_grps;       /* [0..tlft_font_gethdr(this)->h_ngroups][const] Unicode groups. */
	uintptr_t                tf_bestheight; /* [const] Font height for best results, and Y-delta between characters in `tf_'. */
	uintptr_t                tf_nascii;     /* [const][== 95 * tf_bestheight] */
	REF struct video_buffer *tf_chars;      /* [1..1][const] P1_MSB video buffer for font mappings */
};

/* Return the V-table used by `struct tlft_font' */
INTDEF ATTR_RETNONNULL WUNUSED struct video_font_ops *CC _libvideo_tlft_ops(void);
#define libvideo_tlft_ops (*_libvideo_tlft_ops())

/* Returns `(REF struct video_font *)-1' if not a tlft file.
 * Upon  success,  the  mmap-ed  region  `mf'  is inherited. */
INTDEF WUNUSED NONNULL((1, 2)) REF struct video_font *CC
libvideo_font_tryopen_tlft(struct video_domain const *__restrict domain,
                           struct mapfile const *__restrict mf);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_FONTS_TLFT_H */
