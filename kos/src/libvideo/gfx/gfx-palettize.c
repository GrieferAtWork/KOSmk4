/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif(x -> x.startswith("-O"));
// TODO: Enable optimizations
//gcc_opt.append("-O3"); // Force _all_ optimizations because stuff in here is performance-critical
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
#ifndef GUARD_LIBVIDEO_GFX_GFX_PALETTIZE_C
#define GUARD_LIBVIDEO_GFX_GFX_PALETTIZE_C 1
#define LIBVIDEO_GFX_EXPOSE_INTERNALS
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <errno.h>
#include <malloc.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <libvideo/codec/types.h>
#include <libvideo/gfx/gfx.h>

#include "gfx-palettize.h"


#undef HAVE_LOG
#if 1
#include <syslog.h>
#define LOG(...) syslog(LOG_DEBUG, __VA_ARGS__)
#define HAVE_LOG
#else
#define LOG(...) (void)0
#endif

DECL_BEGIN

union color {
	video_color_t c;
	struct {
		video_channel_t r;
		video_channel_t g;
		video_channel_t b;
		video_channel_t a;
	};
};



/************************************************************************/
/* HISTOGRAM PALETTIZATION (adjusted to avg out lost color bits)        */
/* NOTE: Because of memory constraints, only usable without alpha       */
/************************************************************************/
#undef HIST_USE_32BIT_COUNT
#if 1
#define HIST_USE_32BIT_COUNT
#endif

/* # of color bits encoded as index into histogram */
#define HIST_RBITS 5
#define HIST_GBITS 5
#define HIST_BBITS 5

/* # of color bits lost during histogram index encode (aka. quantization) */
#define HIST_RLOST (8 - HIST_RBITS)
#define HIST_GLOST (8 - HIST_GBITS)
#define HIST_BLOST (8 - HIST_BBITS)

/* # of distinct channel values representable in histogram indices. */
#define HIST_RCOUNT (1 << HIST_RBITS)
#define HIST_GCOUNT (1 << HIST_GBITS)
#define HIST_BCOUNT (1 << HIST_BBITS)

/* Quantize / de-quantize color channels */
#define hist_quantize_r(r)   ((r) >> HIST_RLOST)
#define hist_quantize_g(g)   ((g) >> HIST_RLOST)
#define hist_quantize_b(b)   ((b) >> HIST_RLOST)
#define hist_dequantize_r(r) ((r) << HIST_RLOST)
#define hist_dequantize_g(g) ((g) << HIST_RLOST)
#define hist_dequantize_b(b) ((b) << HIST_RLOST)

/* Return the mask of color bits lost during quantization */
#define hist_remainder_r(r) ((r) & ((1 << HIST_RLOST) - 1))
#define hist_remainder_g(g) ((g) & ((1 << HIST_RLOST) - 1))
#define hist_remainder_b(b) ((b) & ((1 << HIST_RLOST) - 1))

struct hist_bin {
#ifdef HIST_USE_32BIT_COUNT
	uint32_t  hb_count;         /* # of times this histogram bucket was used */
#else /* HIST_USE_32BIT_COUNT */
	uint16_t  hb_count;         /* # of times this histogram bucket was used */
#endif /* !HIST_USE_32BIT_COUNT */
	union {
		video_color_t hb_color; /* After histogram generation: the final output color */
		/* NOTE: Your  run-of-the-mill histogram palettization algorithm won't have this
		 *       right here: sums of lost color bits from quantization. -- These will be
		 *       divided `hb_count' and */
		struct {
			uint16_t  hb_rsum;  /* Sum of least significant "HIST_RLOST" bits of this bucket's all "hb_count" uses */
			uint16_t  hb_gsum;  /* Sum of least significant "HIST_GLOST" bits of this bucket's all "hb_count" uses */
			uint16_t  hb_bsum;  /* Sum of least significant "HIST_BLOST" bits of this bucket's all "hb_count" uses */
#ifdef HIST_USE_32BIT_COUNT
			uint16_t _hb_pad;   /* Padding... */
#endif /* HIST_USE_32BIT_COUNT */
		};
	};
};

struct hist {
	union {
		struct hist_bin h_bins[HIST_RCOUNT][HIST_GCOUNT][HIST_BCOUNT];
		struct hist_bin h_colors[HIST_RCOUNT * HIST_GCOUNT * HIST_BCOUNT];
	};
};

PRIVATE WUNUSED NONNULL((1)) int __LIBCCALL
hist_bin_cmp(void const *_lhs, void const *_rhs) {
	struct hist_bin const *lhs = (struct hist_bin const *)_lhs;
	struct hist_bin const *rhs = (struct hist_bin const *)_rhs;
	/* negative compare result, so large bins get sorted to the front */
	if (lhs->hb_count < rhs->hb_count)
		return 1;
	if (lhs->hb_count > rhs->hb_count)
		return -1;
	return 0;
}

/* @param: fail_if_too_many_bins: When the  sum of  pixel counts  from the  most
 *                                significant "palsize" entries of the histogram
 *                                is less than 75% of the source image, fail  by
 *                                returning "1" */
PRIVATE ATTR_NOINLINE WUNUSED ATTR_IN(1) ATTR_OUTS(3, 2) int CC
hist_palettize(struct video_gfx const *__restrict self,
               video_pixel_t palsize, video_color_t *pal,
               bool fail_if_too_many_bins) {
	video_pixel_t x, y;
	struct hist *h = (struct hist *)calloc(sizeof(struct hist));
	if unlikely(!h)
		return -1;
	y = self->vx_hdr.vxh_bymin;
	do {
		x = self->vx_hdr.vxh_bxmin;
		do {
			struct hist_bin *bin;
			union color c;
			c.c = (*self->_vx_xops.vgxo_getcolor)(self, x, y);
			bin = &h->h_bins[hist_quantize_r(c.r)]
			                [hist_quantize_g(c.g)]
			                [hist_quantize_b(c.b)];
			++bin->hb_count;
			bin->hb_rsum += hist_remainder_r(c.r);
			bin->hb_gsum += hist_remainder_r(c.g);
			bin->hb_bsum += hist_remainder_r(c.b);
		} while (++x < self->vx_hdr.vxh_bxend);
	} while (++y < self->vx_hdr.vxh_byend);

	/* Finalize histogram (re-add lost color bits).
	 *
	 * This needs to be done **before** sorting, as  the
	 * high `HIST_{RGB}BITS' bits of each hitogram bin's
	 * color are actually stored in as part of the bin's
	 * index. */
	{
		video_channel_t r, g, b;
		for (r = 0; r < HIST_RCOUNT; ++r) {
			for (g = 0; g < HIST_GCOUNT; ++g) {
				for (b = 0; b < HIST_BCOUNT; ++b) {
					struct hist_bin *bin = &h->h_bins[r][g][b];
					if (bin->hb_count) {
#define round_div(x, y) (((x) + ((y) >> 1)) / (y))
						video_channel_t rlost_avg = round_div(bin->hb_rsum, bin->hb_count);
						video_channel_t glost_avg = round_div(bin->hb_gsum, bin->hb_count);
						video_channel_t blost_avg = round_div(bin->hb_bsum, bin->hb_count);
						video_channel_t final_r = hist_dequantize_r(r) | rlost_avg;
						video_channel_t final_g = hist_dequantize_g(g) | glost_avg;
						video_channel_t final_b = hist_dequantize_b(b) | blost_avg;
						bin->hb_color = VIDEO_COLOR_RGB(final_r, final_g, final_b);
#undef round_div
					}
				}
			}
		}
	}

	/* Sort histogram such that most-used bins come first */
	qsort(h->h_colors, HIST_RCOUNT * HIST_GCOUNT * HIST_BCOUNT,
	      sizeof(struct hist_bin), &hist_bin_cmp);

	/* The first "palsize" entries of the histogram are now the palette */
	if (palsize > (HIST_RCOUNT * HIST_GCOUNT * HIST_BCOUNT))
		palsize = (HIST_RCOUNT * HIST_GCOUNT * HIST_BCOUNT);

	/* Check if the histogram is usable */
	if (fail_if_too_many_bins) {
		video_dim_t io_sx = (self->vx_hdr.vxh_bxend - self->vx_hdr.vxh_bxmin);
		video_dim_t io_sy = (self->vx_hdr.vxh_byend - self->vx_hdr.vxh_bymin);
		size_t io_pixels  = (size_t)io_sx * io_sy;
		video_pixel_t i;
		size_t pal_pixels = 0;
		for (i = 0; i < palsize; ++i)
			pal_pixels += h->h_colors[i].hb_count;

		/* Fail if less than 75% of GFX colors appear in the histogram */
		io_pixels *= 3;
		io_pixels /= 4;
		if (pal_pixels < io_pixels) {
			free(h);
			return 1;
		}
	}

	/* Write the histogram to the output palette */
	{
		video_pixel_t i;
#ifdef HAVE_LOG
		uint64_t pal_pixels_adj;
		size_t pal_pixels = 0;
		video_dim_t io_sx = (self->vx_hdr.vxh_bxend - self->vx_hdr.vxh_bxmin);
		video_dim_t io_sy = (self->vx_hdr.vxh_byend - self->vx_hdr.vxh_bymin);
		size_t io_pixels  = (size_t)io_sx * io_sy;
#endif /* HAVE_LOG */
		for (i = 0; i < palsize; ++i) {
			pal[i] = h->h_colors[i].hb_color;
			LOG("hist[%3u] = {%#.2I8x,%#.2I8x,%#.2I8x} x%u\n",
			    (unsigned int)i,
			    VIDEO_COLOR_GET_RED(pal[i]),
			    VIDEO_COLOR_GET_GREEN(pal[i]),
			    VIDEO_COLOR_GET_BLUE(pal[i]),
			    (unsigned int)h->h_colors[i].hb_count);
#ifdef HAVE_LOG
			pal_pixels += h->h_colors[i].hb_count;
#endif /* HAVE_LOG */
		}
#ifdef HAVE_LOG
		pal_pixels_adj = pal_pixels;
		pal_pixels_adj *= 100 * 10000;
		pal_pixels_adj /= io_pixels;
		LOG("hist:coverage: %u.%04u%% (%u / %u)\n",
		    (unsigned int)(pal_pixels_adj / 10000),
		    (unsigned int)(pal_pixels_adj % 10000),
		    (unsigned int)pal_pixels,
		    (unsigned int)io_pixels);
#endif /* HAVE_LOG */
	}

	free(h);
	return 0;
}






/************************************************************************/
/* MEADIAN-CUT PALETTIZATION                                            */
/************************************************************************/

/* @param: constant_alpha: Constant alpha addend. Either 0 (include alpha in palette),  or
 *                         `VIDEO_COLOR_ALPHA_MASK' (all palette colors have this as their
 *                         alpha) */
PRIVATE ATTR_NOINLINE WUNUSED ATTR_IN(1) ATTR_OUTS(3, 2) int CC
median_cut_palettize(struct video_gfx const *__restrict self,
                     video_pixel_t palsize, video_color_t *pal,
                     video_color_t constant_alpha) {
	(void)constant_alpha;
	/* TODO */
	return hist_palettize(self, palsize, pal, false);
}






/************************************************************************/
/* K-MEANS PALETTIZATION                                                */
/************************************************************************/

/* @param: constant_alpha: Constant alpha addend. Either 0 (include alpha in palette),  or
 *                         `VIDEO_COLOR_ALPHA_MASK' (all palette colors have this as their
 *                         alpha) */
PRIVATE ATTR_NOINLINE WUNUSED ATTR_IN(1) ATTR_OUTS(3, 2) int CC
k_means_palettize(struct video_gfx const *__restrict self,
                  video_pixel_t palsize, video_color_t *pal,
                  video_color_t constant_alpha) {
	(void)constant_alpha;
	/* TODO */
	return hist_palettize(self, palsize, pal, false);
}






/* Construct a (visually pleasing) palette from the pixel area denoted
 * by the I/O region of `self'. The produced palette is stored in  the
 * provided buffer `pal' and consists of exactly `palsize' colors.
 * @param: method: How to calculate the palette
 * @return: 0 : Success
 * @return: -1: [errno=ENOMEM] Insufficient memory for temporaries needed during calculation
 * @return: -1: [errno=EINVAL] Attempted to use "VIDEO_GFX_PALETTIZE_METHOD_F_ALPHA" with
 *                             a  palettization method that doesn't support alpha values.
 * @return: -1: [errno=EINVAL] Invalid `method' */
INTERN WUNUSED ATTR_IN(1) ATTR_OUTS(3, 2) int CC
libvideo_gfx_palettize(struct video_gfx const *__restrict self,
                       video_pixel_t palsize, video_color_t *pal,
                       unsigned int method) {
	/* Check for special case: empty palette / GFX I/O area */
	if unlikely(!palsize)
		goto empty_pal;
	if unlikely(self->vx_hdr.vxh_bxmin >= self->vx_hdr.vxh_bxend)
		goto empty_io;
	if unlikely(self->vx_hdr.vxh_bymin >= self->vx_hdr.vxh_byend)
		goto empty_io;

	switch (method) {
	case VIDEO_GFX_PALETTIZE_METHOD_AUTO: {
		/* When "method" is "AUTO", do this:
		 * - Try to use "VIDEO_GFX_PALETTIZE_METHOD_HISTOGRAM"
		 * - Move on to "VIDEO_GFX_PALETTIZE_METHOD_MEDIAN_CUT" if
		 *   it turns out the histogram  covers too little of  the
		 *   image's color space. */
		int hist_status = hist_palettize(self, palsize, pal, true);
		if (hist_status != 1)
			return hist_status;
	}	ATTR_FALLTHROUGH
	case VIDEO_GFX_PALETTIZE_METHOD_MEDIAN_CUT:
		return median_cut_palettize(self, palsize, pal, VIDEO_COLOR_ALPHA_MASK);

	case VIDEO_GFX_PALETTIZE_METHOD_HISTOGRAM:
		return hist_palettize(self, palsize, pal, false);

		/* Since HIST doesn't support alpha, treat AUTO+ALPHA like MEDIAN_CUT+ALPHA */
	case VIDEO_GFX_PALETTIZE_METHOD_AUTO | VIDEO_GFX_PALETTIZE_METHOD_F_ALPHA:
	case VIDEO_GFX_PALETTIZE_METHOD_MEDIAN_CUT | VIDEO_GFX_PALETTIZE_METHOD_F_ALPHA:
		return median_cut_palettize(self, palsize, pal, 0);

	case VIDEO_GFX_PALETTIZE_METHOD_K_MEANS:
		return k_means_palettize(self, palsize, pal, VIDEO_COLOR_ALPHA_MASK);

	case VIDEO_GFX_PALETTIZE_METHOD_K_MEANS | VIDEO_GFX_PALETTIZE_METHOD_F_ALPHA:
		return k_means_palettize(self, palsize, pal, 0);

	default: break;
	}

	/* Unsupported palettization method. */
	errno = EINVAL;
	return -1;
empty_io:
	bzero(pal, palsize, sizeof(*pal));
empty_pal:
	return 0;
}

DEFINE_PUBLIC_ALIAS(video_gfx_palettize, libvideo_gfx_palettize);

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_GFX_PALETTIZE_C */
