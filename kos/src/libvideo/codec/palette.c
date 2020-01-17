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
#ifndef GUARD_LIBVIDEO_CODEC_PALETTE_C
#define GUARD_LIBVIDEO_CODEC_PALETTE_C 1

#include "palette.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <assert.h>

#include <libvideo/codec/palette.h>

DECL_BEGIN

LOCAL size_t CC diff(uint8_t a, uint8_t b) {
	if (a > b) {
		return a - b;
	}
	return b - a;
}

LOCAL size_t CC
color_delta(uint8_t r1, uint8_t g1, uint8_t b1,
            uint8_t r2, uint8_t g2, uint8_t b2) {
	size_t result;
	result  = diff(r1, r2);
	result += diff(g1, g2) * 2; /* Put double the weight on green */
	result += diff(b1, b2);
	return result;
}

LOCAL video_pixel_t CC
calculate_best_matching_palette_pixel(struct video_palette const *__restrict self,
                                      video_color_t color) {
	video_pixel_t result = 0, i;
	size_t best_delta = (size_t)-1;
	uint8_t r = (uint8_t)((color & VIDEO_COLOR_RED_MASK) >> VIDEO_COLOR_RED_SHIFT);
	uint8_t g = (uint8_t)((color & VIDEO_COLOR_GREEN_MASK) >> VIDEO_COLOR_GREEN_SHIFT);
	uint8_t b = (uint8_t)((color & VIDEO_COLOR_BLUE_MASK) >> VIDEO_COLOR_BLUE_SHIFT);
	assert(self->vp_cnt != 0);
	for (i = 0; i < self->vp_cnt; ++i) {
		size_t delta;
		video_color_t color2;
		uint8_t r2, g2, b2;
		color2 = self->vp_pal.vdp_pal[i];
		r2     = (uint8_t)((color2 & VIDEO_COLOR_RED_MASK) >> VIDEO_COLOR_RED_SHIFT);
		g2     = (uint8_t)((color2 & VIDEO_COLOR_GREEN_MASK) >> VIDEO_COLOR_GREEN_SHIFT);
		b2     = (uint8_t)((color2 & VIDEO_COLOR_BLUE_MASK) >> VIDEO_COLOR_BLUE_SHIFT);
		delta  = color_delta(r, g, b, r2, g2, b2);
		if (best_delta > delta) {
			best_delta = delta;
			result = i;
		}
	}
	return result;
}




LOCAL int CC
get_known_color_index(video_color_t color) {
	int result;
	switch (color | VIDEO_COLOR_ALPHA_MASK) {
	case VIDEO_COLOR_BLACK:   result = VIDEO_PALCOLOR_BLACK; break;
	case VIDEO_COLOR_NAVY:    result = VIDEO_PALCOLOR_NAVY; break;
	case VIDEO_COLOR_GREEN:   result = VIDEO_PALCOLOR_GREEN; break;
	case VIDEO_COLOR_TEAL:    result = VIDEO_PALCOLOR_TEAL; break;
	case VIDEO_COLOR_MAROON:  result = VIDEO_PALCOLOR_MAROON; break;
	case VIDEO_COLOR_PURPLE:  result = VIDEO_PALCOLOR_PURPLE; break;
	case VIDEO_COLOR_OLIVE:   result = VIDEO_PALCOLOR_OLIVE; break;
	case VIDEO_COLOR_SILVER:  result = VIDEO_PALCOLOR_SILVER; break;
	case VIDEO_COLOR_GREY:    result = VIDEO_PALCOLOR_GREY; break;
	case VIDEO_COLOR_BLUE:    result = VIDEO_PALCOLOR_BLUE; break;
	case VIDEO_COLOR_LIME:    result = VIDEO_PALCOLOR_LIME; break;
	case VIDEO_COLOR_AQUA:    result = VIDEO_PALCOLOR_AQUA; break;
	case VIDEO_COLOR_RED:     result = VIDEO_PALCOLOR_RED; break;
	case VIDEO_COLOR_FUCHSIA: result = VIDEO_PALCOLOR_FUCHSIA; break;
	case VIDEO_COLOR_YELLOW:  result = VIDEO_PALCOLOR_YELLOW; break;
	case VIDEO_COLOR_WHITE:   result = VIDEO_PALCOLOR_WHITE; break;
	default:
		result = -1;
		break;
	}
	return result;
}


/* Return the best-matching pixel for a given color.
 * For the purpose of determining the best match, this algorithm
 * leans towards emphasizing colors best viewed by the human eye,
 * thus producing the best-looking results for those bipedal fellas.
 * NOTE: If the given `color' is one of `VIDEO_COLOR_*', `vp_colors'
 *       is used to quickly lookup the associated palette index.
 *       If the associated index is set to `(size_t)-1', the index
 *       will be calculated like any other color given would, and
 *       the result will be cached within the `vp_colors' vector. */
INTERN NONNULL((1)) video_pixel_t CC
libvideo_palette_getpixel(struct video_palette *__restrict self,
                          video_color_t color) {
	video_pixel_t result;
	int known = get_known_color_index(color);
	if (known >= 0) {
		/* Check the known color cache. */
		result = self->vp_colors[known];
		if (result != (video_pixel_t)-1)
			return result;
	}
	result = calculate_best_matching_palette_pixel(self, color);
	if (known >= 0) {
		/* Save the known color cache. */
		self->vp_colors[known] = result;
	}
	return result;
}


DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_PALETTE_C */
