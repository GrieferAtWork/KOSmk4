/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif(x -> x.startswith("-O"));
gcc_opt.append("-O3"); // Force _all_ optimizations because stuff in here is performance-critical
]]]*/
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
#ifndef GUARD_LIBVIDEO_CODEC_CODECS_EXTRA_C
#define GUARD_LIBVIDEO_CODEC_CODECS_EXTRA_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <stddef.h>

#include <libvideo/codec/codecs-extra.h>
#include <libvideo/codec/pixel.h>

#include "codec-utils.h"
#include "converter.h"

DECL_BEGIN

#ifdef VIDEO_CODEC_X_VBE16
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) video_pixel_t CC
x_vbe16_getpixel(byte_t const *__restrict line, video_coord_t x) {
	shift_t shift;
	line += ((x >> 3) << 2);
	shift = 7 - (x & 7);
	return (((line[0] >> shift) & 1) << 0) |
	       (((line[1] >> shift) & 1) << 1) |
	       (((line[2] >> shift) & 1) << 2) |
	       (((line[3] >> shift) & 1) << 3);
}

PRIVATE NONNULL((1)) void CC
x_vbe16_setpixel(byte_t *__restrict line, video_coord_t x, video_pixel_t pixel) {
	byte_t mask;
	line += ((x >> 3) << 2);
	mask = (byte_t)1 << (7 - (x & 7));
	line[0] = (line[0] & ~mask) | (mask * ((pixel >> 0) & 1));
	line[1] = (line[1] & ~mask) | (mask * ((pixel >> 1) & 1));
	line[2] = (line[2] & ~mask) | (mask * ((pixel >> 2) & 1));
	line[3] = (line[3] & ~mask) | (mask * ((pixel >> 3) & 1));
}

PRIVATE NONNULL((3)) void CC
x_vbe16_requirements(video_dim_t size_x, video_dim_t size_y,
                     struct video_rambuffer_requirements *__restrict result) {
	result->vbs_stride  = CEIL_ALIGN(size_x, 4) / 2;
	result->vbs_bufsize = size_y * result->vbs_stride;
}

DEFINE_GENERIC_linefill__with__setpixel(x_vbe16_linefill, x_vbe16_setpixel)
DEFINE_GENERIC_vertfill__with__setpixel(x_vbe16_vertfill, x_vbe16_setpixel)
DEFINE_GENERIC_rectfill__with__linefill(x_vbe16_rectfill, x_vbe16_linefill)
DEFINE_GENERIC_rectcopy__with__getpixel__and__setpixel(x_vbe16_rectcopy, x_vbe16_getpixel, x_vbe16_setpixel)
DEFINE_GENERIC_rectmove__with__getpixel__and__setpixel(x_vbe16_rectmove, x_vbe16_getpixel, x_vbe16_setpixel)
DEFINE_GENERIC_setpixel3__with__setpixel(rp3_x_vbe16_setpixel, x_vbe16_setpixel)
DEFINE_PIXEL64_IO_WRAPPERS__WITH_PREFIX(PRIVATE, x_vbe16_)

#define unaligned_x_vbe16_getpixel x_vbe16_getpixel
#define unaligned_x_vbe16_setpixel x_vbe16_setpixel
#define unaligned_x_vbe16_rectcopy x_vbe16_rectcopy
#define unaligned_x_vbe16_rectmove x_vbe16_rectmove
#define unaligned_x_vbe16_linefill x_vbe16_linefill
#define unaligned_x_vbe16_vertfill x_vbe16_vertfill
#define unaligned_x_vbe16_rectfill x_vbe16_rectfill
#endif /* VIDEO_CODEC_X_VBE16 */



/* Same as `libvideo_codec_lookup()', but used for "extra" codecs */
INTERN /*ATTR_CONST*/ WUNUSED struct video_codec const *CC
libvideo_codec_lookup_extra(video_codec_t codec) {
	struct video_codec const *result;
	switch (codec) {

#ifdef VIDEO_CODEC_X_VBE16
	case VIDEO_CODEC_X_VBE16: {
		_DEFINE_CODEC_AL1(x_vbe16, VIDEO_CODEC_X_VBE16,
		                  (VIDEO_CODEC_FLAG_PAL | VIDEO_CODEC_FLAG_SPECIAL,
		                   /* vcs_bpp   */ 4,
		                   /* vcs_cbits */ 4,
		                   /* vcs_rmask */ 0,
		                   /* vcs_gmask */ 0,
		                   /* vcs_bmask */ 0,
		                   /* vcs_amask */ 0),
		                  x_vbe16_requirements,
		                  x_vbe16_getpixel, x_vbe16_setpixel, x_vbe16_rectcopy, x_vbe16_rectmove,
		                  x_vbe16_linefill, x_vbe16_vertfill, x_vbe16_rectfill,
		                  pal_pixel2color, pal_color2pixel, initconv_from_p);
		result = &x_vbe16;
	}	break;
#endif /* VIDEO_CODEC_X_VBE16 */

	default:
		result = NULL;
		break;
	}
	return result;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_CODECS_EXTRA_C */
