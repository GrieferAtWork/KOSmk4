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
#ifndef GUARD_LIBVIDEO_CODEC_PALETTE_C
#define GUARD_LIBVIDEO_CODEC_PALETTE_C 1
#define _KOS_SOURCE 1

#include "palette.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <assert.h>
#include <atomic.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>

#include <libvideo/codec/palette.h>

DECL_BEGIN

LOCAL ATTR_CONST size_t CC
diff(uint8_t a, uint8_t b) {
	if (a > b) {
		return a - b;
	}
	return b - a;
}

LOCAL ATTR_CONST size_t CC
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
                                      uint8_t r, uint8_t g, uint8_t b) {
	video_pixel_t result = 0, i;
	size_t best_delta = (size_t)-1;
	assert(self->vp_cnt != 0);
	for (i = 0; i < self->vp_cnt; ++i) {
		size_t delta;
		video_color_t color2;
		uint8_t r2, g2, b2;
		color2 = self->vp_pal[i];
		r2     = VIDEO_COLOR_GET_RED(color2);
		g2     = VIDEO_COLOR_GET_GREEN(color2);
		b2     = VIDEO_COLOR_GET_BLUE(color2);
		delta  = color_delta(r, g, b, r2, g2, b2);
		if (best_delta > delta) {
			best_delta = delta;
			result = i;
		}
	}
	return result;
}


#define VPC_SIZE     8
#define VPC_SIGRBITS 2
#define VPC_SIGGBITS 3 /* Give a bit more bits to green. */
#define VPC_SIGBBITS 2

union video_palette_cachepair {
	struct {
		uint8_t cp_r; /* Color R */
		uint8_t cp_g; /* Color G */
		uint8_t cp_b; /* Color B */
		uint8_t cp_i; /* Palette index */
	};
	uint32_t cp_word;
};

struct video_palette_cacheset {
	union video_palette_cachepair cs_pairs[VPC_SIZE];
};

struct video_palette_cache {
	struct video_palette_cacheset vpc_sets[/*r:*/ 1 << VPC_SIGRBITS]
	                                      [/*g:*/ 1 << VPC_SIGGBITS]
	                                      [/*b:*/ 1 << VPC_SIGBBITS];
};

/* Return the best-matching pixel for a given color.
 * For  the purpose  of determining  the best  match, this algorithm
 * leans towards emphasizing  colors best viewed  by the human  eye,
 * thus producing the best-looking results for those bipedal fellas.
 * NOTE: This function may lazily allocate `self->vp_cache', meaning
 *       that once  used, the  caller is  responsible to  eventually
 *       cleanup that field using `free(self->vp_cache)'. */
INTERN WUNUSED NONNULL((1)) video_pixel_t CC
libvideo_palette_getpixel(struct video_palette *__restrict self,
                          video_color_t color) {
	video_pixel_t result;
	struct video_palette_cache *cache;
	struct video_palette_cacheset *cs;
	uint8_t r, g, b;
	r = VIDEO_COLOR_GET_RED(color);
	g = VIDEO_COLOR_GET_GREEN(color);
	b = VIDEO_COLOR_GET_BLUE(color);
#if 0 /* TODO: Palette index caching support for larger palettes? */
	if unlikely(self->vp_cnt > 0xff) {
	}
#endif
	cache = self->vp_cache;
	if likely(cache) {
		unsigned int i;
		/* Search the cache for know translations. */
		cs = &cache->vpc_sets[r >> (8 - VPC_SIGRBITS)]
		                     [g >> (8 - VPC_SIGGBITS)]
		                     [b >> (8 - VPC_SIGBBITS)];
		for (i = 0; i < VPC_SIZE; ++i) {
			union video_palette_cachepair ent;
			ent.cp_word = atomic_read(&cs->cs_pairs[i].cp_word);
			if (ent.cp_r == r &&
			    ent.cp_g == g &&
			    ent.cp_b == b)
				return ent.cp_i;
		}
	} else {
		cache = (struct video_palette_cache *)calloc(1, sizeof(struct video_palette_cache));
		if unlikely(!cache) {
			result = calculate_best_matching_palette_pixel(self, r, g, b);
			goto done;
		}
		COMPILER_WRITE_BARRIER();
		if unlikely(!atomic_cmpxch(&self->vp_cache, NULL, cache)) {
			free(cache);
			cache = self->vp_cache;
			assert(cache);
		}
		cs = &cache->vpc_sets[r >> (8 - VPC_SIGRBITS)]
		                     [g >> (8 - VPC_SIGGBITS)]
		                     [b >> (8 - VPC_SIGBBITS)];
	}
	result = calculate_best_matching_palette_pixel(self, r, g, b);
	if likely(result <= 0xff) {
		/* Remember the result. */
		union video_palette_cachepair ent;
		ent.cp_r = r;
		ent.cp_g = g;
		ent.cp_b = b;
		ent.cp_i = (uint8_t)result;
		memmoveup(cs->cs_pairs + 1, cs->cs_pairs, VPC_SIZE - 1,
		          sizeof(union video_palette_cachepair));
		atomic_write(&cs->cs_pairs[0].cp_word, ent.cp_word);
	}
done:
	return result;
}

DEFINE_PUBLIC_ALIAS(video_palette_getpixel, libvideo_palette_getpixel);

DECL_END

#endif /* !GUARD_LIBVIDEO_CODEC_PALETTE_C */
