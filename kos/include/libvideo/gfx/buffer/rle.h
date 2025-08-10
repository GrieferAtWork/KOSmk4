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
#ifndef _LIBVIDEO_GFX_BUFFER_RLE_H
#define _LIBVIDEO_GFX_BUFFER_RLE_H 1

#include "../api.h"
/**/

#ifdef CONFIG_LIBVIDEO_HAVE_RLE
#include <__stdinc.h>

#include <bits/types.h>
#include <kos/anno.h>

#include "../../types.h"
#include "../gfx-flags.h"

#ifdef LIBVIDEO_GFX_EXPOSE_INTERNALS
#ifdef __CC__
__DECL_BEGIN

/* Encoding of RLE'd data:
 * - Pixels are stored as scanlines, but scanlines are variable-length.
 * - Only available for video codecs with BPP>=8 (iow: not supported for codecs with multiple pixels per byte)
 * - Each scanline looks like (depending on `vbrlek_dstcodec'):
 *   - When "vbrlek_dstcodec->vc_specs.vcs_pxsz in [1,2,3]":
 *     >> { u8 skip; u8 copy; u8 data[copy * vbrlek_dstcodec->vc_specs.vcs_pxsz]; }[];
 *     >> u8 skip_eof = 0x00;
 *     >> u8 copy_eof = 0x00;
 *   - When "vbrlek_dstcodec->vc_specs.vcs_pxsz >= 4":
 *     >> { u16 skip; u16 copy; u8 data[copy * vbrlek_dstcodec->vc_specs.vcs_pxsz]; }[];
 *     >> u16 skip_eof = 0x0000;
 *     >> u16 copy_eof = 0x0000;
 *   - When "vbrlek_dstcodec->vc_specs.vcs_pxsz == 8 && __ALIGNOF_INT64__ > __ALIGNOF_INT32__":
 *     >> { u32 skip; u32 copy; u8 data[copy * 8]; }[];
 *     >> u32 skip_eof = 0x00000000;
 *     >> u32 copy_eof = 0x00000000;
 */

struct video_buffer;
struct video_palette;
struct video_codec;

struct video_buffer_rlekey {
	struct video_buffer  *vbrlek_src;      /* [1..1] Source buffer */
	struct video_palette *vbrlek_srcpal;   /* [0..1] Source palette */
	struct video_codec   *vbrlek_dstcodec; /* [1..1] Destination codec */
	struct video_palette *vbrlek_dstpal;   /* [0..1] Destination palette */
	video_gfx_flag_t      vbrlek_srcflags; /* Source flags (set of `VIDEO_GFX_F_COLORKEY | VIDEO_GFX_F_PALOBJ'; other flags must be 0) */
	video_gfx_flag_t      vbrlek_dstflags; /* Destination flags (set of `VIDEO_GFX_F_PALOBJ'; other flags must be 0) */
	video_pixel_t         vbrlek_colorkey; /* [valid_if(vbrlek_srcflags & VIDEO_GFX_F_COLORKEY)] Source color key */
	video_coord_t         vbrlek_ymin;     /* [< video_buffer_getydim(vbrlek_src)] First scanline that we want to access */
	video_dim_t           vbrlek_ydim;     /* [> 0][<= video_buffer_getydim(vbrlek_src) - vbrlek_ymin] # of scanlines that we want to access */
	union {
		struct {
			video_coord_t vbrlek_xmin;     /* [IN] Starting X position */
			video_dim_t   vbrlek_xdim;     /* [IN] Blit X dimension */
		};
		struct {
			video_coord_t vbrlek_xhskip;   /* [OUT] # of leading pixels to skip in each scanline */
			video_dim_t   vbrlek_xtskip;   /* [OUT] # of trailing pixels to skip in each scanline */
		};
	};
};


__DECL_END
#endif /* __CC__ */
#endif /* LIBVIDEO_GFX_EXPOSE_INTERNALS */
#endif /* CONFIG_LIBVIDEO_HAVE_RLE */

#endif /* !_LIBVIDEO_GFX_BUFFER_RLE_H */
